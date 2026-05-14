#pragma once
#include "util.hpp"
#include "pe_image.hpp"
#include "elf_types.hpp"
#include "elf_plan.hpp"

// ---------------------------------------------------------------------------
// Builder: constructs all ELF in-memory content from a PeImage and Plan
// ---------------------------------------------------------------------------
struct Builder {
  PeImage& image;
  const Plan& plan;
  const std::string& shim_name;
  const std::string& interp;
  bool strip_pdata;

  // Synthetic section content
  std::vector<uint8_t>   interp_data;
  std::vector<uint8_t>   dynstr_data;
  std::vector<Elf64_Sym> dynsym_data;
  std::vector<Elf64_Rela> rela_data;
  std::vector<Elf64_Dyn>  dynamic_data;
  std::vector<uint8_t>   trampoline_data;

  // IAT section with slots zeroed
  std::vector<uint8_t> rdata_patched;

  // ELF structural tables
  std::vector<Elf64_Phdr> phdrs;
  std::vector<Elf64_Shdr> shdrs;
  std::vector<uint8_t>    shstrtab_data;

  static constexpr size_t DT_ENTRY_COUNT = 12;

  uint32_t dynstr_shim_off  = 0;
  uint32_t dynstr_rpath_off = 0;

  Builder(PeImage& img, const Plan& p,
          const std::string& shim, const std::string& itp, bool sp)
    : image(img), plan(p), shim_name(shim), interp(itp), strip_pdata(sp) {}

  void build_synthetic_sections() {
    interp_data.assign(interp.begin(), interp.end());
    interp_data.push_back(0);

    dynstr_data.push_back(0);
    dynstr_shim_off = (uint32_t)dynstr_data.size();
    for( char c : shim_name )
      dynstr_data.push_back((uint8_t)c);
    dynstr_data.push_back(0);
    dynstr_rpath_off = (uint32_t)dynstr_data.size();
    for( char c : std::string("$ORIGIN") )
      dynstr_data.push_back((uint8_t)c);
    dynstr_data.push_back(0);

    std::vector<std::string> unique_names;
    for( auto &ie : image.imports ) {
      bool found = false;
      for( size_t k = 0; k<unique_names.size(); ++k ) {
        if( unique_names[k]==ie.func_name ) {
          ie.sym_index = (uint32_t)(k+1);
          found = true;
          break;
        }
      }
      if( !found ) {
        ie.sym_index = (uint32_t)(unique_names.size()+1);
        unique_names.push_back(ie.func_name);
      }
    }

    dynsym_data.push_back(Elf64_Sym{});
    for( auto &name : unique_names ) {
      uint32_t str_off = (uint32_t)dynstr_data.size();
      for( char c : name )
        dynstr_data.push_back((uint8_t)c);
      dynstr_data.push_back(0);
      Elf64_Sym sym{};
      sym.st_name  = str_off;
      sym.st_info  = (uint8_t)((STB_GLOBAL<<4)|STT_FUNC);
      sym.st_shndx = SHN_UNDEF;
      dynsym_data.push_back(sym);
    }

    for( auto &ie : image.imports ) {
      Elf64_Rela r{};
      r.r_offset = image.image_base+ie.iat_rva;
      r.r_info   = ELF64_R_INFO(ie.sym_index, R_X86_64_64);
      rela_data.push_back(r);
    }
  }

  bool build_trampoline() {
    uint64_t pe_entry      = image.image_base+image.ep_rva;
    uint64_t jmp_instr_end = plan.trampoline_va+4+5;
    int64_t  d             = (int64_t)(pe_entry-jmp_instr_end);
    if( d != (int32_t)d ) {
      fprintf(stderr, "Error: trampoline rel32 out of range "
              "(PE entry 0x%llx too far from synthetic segment)\n",
              (unsigned long long)pe_entry);
      return false;
    }
    int32_t rel32 = (int32_t)d;
    trampoline_data = {0x48, 0x83, 0xec, 0x08,    // sub rsp, 8
                       0xe9,
                       (uint8_t)(rel32),
                       (uint8_t)(rel32>>8),
                       (uint8_t)(rel32>>16),
                       (uint8_t)(rel32>>24)};
    while( trampoline_data.size()<kTrampolineSize )
      trampoline_data.push_back(0x90);
    return true;
  }

  void build_dynamic() {
    auto dyn = [&](int64_t tag, uint64_t val) {
      Elf64_Dyn d{}; d.d_tag = tag; d.d_un.d_val = val;
      dynamic_data.push_back(d);
    };
    dyn(DT_NEEDED,  dynstr_shim_off);
    dyn(DT_RUNPATH, dynstr_rpath_off);
    dyn(DT_STRTAB,  plan.dynstr_va);
    dyn(DT_STRSZ,   dynstr_data.size());
    dyn(DT_SYMTAB,  plan.dynsym_va);
    dyn(DT_SYMENT,  sizeof(Elf64_Sym));
    dyn(DT_RELA,    plan.rela_va);
    dyn(DT_RELASZ,  rela_data.size()*sizeof(Elf64_Rela));
    dyn(DT_RELAENT, sizeof(Elf64_Rela));
    dyn(DT_DEBUG,   0);
    dyn(DT_FLAGS_1, DF_1_NOW);
    dyn(DT_NULL,    0);
    assert(dynamic_data.size()==DT_ENTRY_COUNT);
  }

  void patch_rdata() {
    if( image.rdata_sec_idx<0 )
      return;
    auto &sec = image.secmap.secs[image.rdata_sec_idx];
    size_t raw_size = sec.rawsz;
    if( sec.raw>=image.buf.size() ) {
      rdata_patched.assign(raw_size, 0);
    } else {
      size_t avail = image.buf.size()-sec.raw;
      if( avail>raw_size ) avail = raw_size;
      rdata_patched.assign(image.buf.data.data()+sec.raw,
                           image.buf.data.data()+sec.raw+avail);
      rdata_patched.resize(raw_size, 0);
    }
    for( auto &ie : image.imports ) {
      if( image.secmap.section_of(ie.iat_rva)!=image.rdata_sec_idx )
        continue;
      uint32_t slot_off = ie.iat_rva-sec.va;
      if( slot_off+8<=raw_size )
        memset(rdata_patched.data()+slot_off, 0, 8);
    }
  }

  void build_phdrs(uint64_t /*shoff*/) {
    phdrs.clear();
    uint32_t n_pe_secs = (uint32_t)image.secmap.secs.size();

    // PT_PHDR — filesz/memsz patched at end
    {
      Elf64_Phdr p{};
      p.p_type   = PT_PHDR;
      p.p_flags  = PF_R;
      p.p_offset = sizeof(Elf64_Ehdr);
      p.p_vaddr  = plan.synth_va+sizeof(Elf64_Ehdr);
      p.p_paddr  = p.p_vaddr;
      p.p_align  = 8;
      phdrs.push_back(p);
    }
    {
      Elf64_Phdr p{};
      p.p_type   = PT_INTERP;
      p.p_flags  = PF_R;
      p.p_offset = plan.interp_foff;
      p.p_vaddr  = plan.interp_va;
      p.p_paddr  = plan.interp_va;
      p.p_filesz = interp_data.size();
      p.p_memsz  = interp_data.size();
      p.p_align  = 1;
      phdrs.push_back(p);
    }
    {
      uint64_t syn_filesz = plan.trampoline_foff+trampoline_data.size();
      Elf64_Phdr p{};
      p.p_type   = PT_LOAD;
      p.p_flags  = PF_R|PF_W|PF_X;
      p.p_offset = plan.synth_foff;
      p.p_vaddr  = plan.synth_va;
      p.p_paddr  = plan.synth_va;
      p.p_filesz = syn_filesz;
      p.p_memsz  = syn_filesz;
      p.p_align  = kPageSize;
      phdrs.push_back(p);
    }
    {
      Elf64_Phdr p{};
      p.p_type   = PT_DYNAMIC;
      p.p_flags  = PF_R|PF_W;
      p.p_offset = plan.dynamic_foff;
      p.p_vaddr  = plan.dynamic_va;
      p.p_paddr  = plan.dynamic_va;
      p.p_filesz = dynamic_data.size()*sizeof(Elf64_Dyn);
      p.p_memsz  = p.p_filesz;
      p.p_align  = 8;
      phdrs.push_back(p);
    }

    int relro_sec_idx = -1;
    for( uint32_t i = 0; i<n_pe_secs; ++i ) {
      auto &sec = image.secmap.secs[i];
      uint32_t ch = sec.characteristics;
      if( strip_pdata&&memcmp(sec.name, ".pdata", 6)==0 )
        continue;
      uint32_t flags = 0;
      if( ch&PE_SCN_MEM_READ )    flags |= PF_R;
      if( ch&PE_SCN_MEM_WRITE )   flags |= PF_W;
      if( ch&PE_SCN_MEM_EXECUTE ) flags |= PF_X;
      if( (int)i==image.rdata_sec_idx ) {
        flags |= PF_W;
        relro_sec_idx = (int)i;
      }
      Elf64_Phdr p{};
      p.p_type   = PT_LOAD;
      p.p_flags  = flags;
      p.p_offset = sec.elf_foff;
      p.p_vaddr  = image.image_base+sec.va;
      p.p_paddr  = image.image_base+sec.va;
      p.p_filesz = sec.rawsz;
      p.p_memsz  = std::max((uint64_t)sec.virtsz, (uint64_t)sec.rawsz);
      p.p_align  = kPageSize;
      phdrs.push_back(p);
    }

    if( relro_sec_idx>=0 ) {
      auto &sec = image.secmap.secs[relro_sec_idx];
      Elf64_Phdr p{};
      p.p_type   = PT_GNU_RELRO;
      p.p_flags  = PF_R;
      p.p_offset = sec.elf_foff;
      p.p_vaddr  = image.image_base+sec.va;
      p.p_paddr  = image.image_base+sec.va;
      p.p_filesz = sec.rawsz;
      p.p_memsz  = sec.rawsz;
      p.p_align  = 1;
      phdrs.push_back(p);
    }
    {
      Elf64_Phdr p{};
      p.p_type  = PT_GNU_STACK;
      p.p_flags = PF_R|PF_W;
      p.p_align = 0x10;
      phdrs.push_back(p);
    }
    {
      Elf64_Phdr p{};
      p.p_type   = PT_LOAD;
      p.p_flags  = PF_R;
      p.p_offset = plan.pe_hdr_foff;
      p.p_vaddr  = image.image_base;
      p.p_paddr  = image.image_base;
      p.p_filesz = image.oh->SizeOfHeaders;
      p.p_memsz  = align_up(image.oh->SizeOfHeaders, kPageSize);
      p.p_align  = kPageSize;
      phdrs.push_back(p);
    }

    phdrs[0].p_filesz = phdrs.size()*sizeof(Elf64_Phdr);
    phdrs[0].p_memsz  = phdrs[0].p_filesz;
  }

  uint32_t add_shstrtab(const char* name) {
    uint32_t off = (uint32_t)shstrtab_data.size();
    while( *name ) shstrtab_data.push_back((uint8_t)*name++);
    shstrtab_data.push_back(0);
    return off;
  }

  void build_shdrs(uint64_t shstrtab_foff, uint64_t shstrtab_va) {
    shdrs.clear();
    shstrtab_data.clear();
    shstrtab_data.push_back(0);

    shdrs.push_back(Elf64_Shdr{}); // [0] NULL

    auto add = [&](const char* name, uint32_t type, uint64_t flags,
                   uint64_t addr, uint64_t off, uint64_t size,
                   uint32_t link, uint32_t info, uint64_t align, uint64_t entsize) {
      Elf64_Shdr s{};
      s.sh_name      = add_shstrtab(name);
      s.sh_type      = type;
      s.sh_flags     = flags;
      s.sh_addr      = addr;
      s.sh_offset    = off;
      s.sh_size      = size;
      s.sh_link      = link;
      s.sh_info      = info;
      s.sh_addralign = align;
      s.sh_entsize   = entsize;
      shdrs.push_back(s);
    };

    uint32_t dynsym_shidx = (uint32_t)shdrs.size();
    add(".dynsym", SHT_DYNSYM, SHF_ALLOC,
        plan.dynsym_va, plan.dynsym_foff, dynsym_data.size()*sizeof(Elf64_Sym),
        dynsym_shidx+1, 1, 8, sizeof(Elf64_Sym));

    add(".dynstr", SHT_STRTAB, SHF_ALLOC,
        plan.dynstr_va, plan.dynstr_foff, dynstr_data.size(),
        0, 0, 1, 0);


    add(".rela.dyn", SHT_RELA, SHF_ALLOC,
        plan.rela_va, plan.rela_foff, rela_data.size()*sizeof(Elf64_Rela),
        dynsym_shidx, 0, 8, sizeof(Elf64_Rela));

    add(".dynamic", SHT_DYNAMIC, SHF_ALLOC|SHF_WRITE,
        plan.dynamic_va, plan.dynamic_foff, dynamic_data.size()*sizeof(Elf64_Dyn),
        dynsym_shidx+1, 0, 8, sizeof(Elf64_Dyn));

    add(".interp", SHT_PROGBITS, SHF_ALLOC,
        plan.interp_va, plan.interp_foff, interp_data.size(),
        0, 0, 1, 0);

    for( uint32_t i = 0; i<image.secmap.secs.size(); ++i ) {
      auto &sec = image.secmap.secs[i];
      uint32_t ch = sec.characteristics;
      uint64_t sh_flags = SHF_ALLOC;
      if( ch&PE_SCN_MEM_WRITE )   sh_flags |= SHF_WRITE;
      if( ch&PE_SCN_MEM_EXECUTE ) sh_flags |= SHF_EXECINSTR;
      bool all_bss = (sec.rawsz==0);
      uint32_t sh_type   = all_bss ? SHT_NOBITS   : SHT_PROGBITS;
      uint64_t sh_offset = all_bss ? 0             : sec.elf_foff;
      uint64_t sh_size   = all_bss ? sec.virtsz    : sec.rawsz;
      add(sec.name_str.c_str(), sh_type, sh_flags,
          image.image_base+sec.va, sh_offset, sh_size,
          0, 0, 0x1000, 0);
    }

    add(".shstrtab", SHT_STRTAB, 0, shstrtab_va, shstrtab_foff,
        0, 0, 0, 1, 0);
    (void)shstrtab_va;
  }
};
