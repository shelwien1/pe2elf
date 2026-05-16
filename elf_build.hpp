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
  const std::string& inject_name; // extra DT_NEEDED, or empty

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

  uint32_t dynstr_shim_off   = 0;
  uint32_t dynstr_rpath_off  = 0;
  uint32_t dynstr_inject_off = 0;

  // TLS directory fields (set from PeImage before build_synthetic_sections)
  uint64_t tls_template_va  = 0;
  uint64_t tls_template_sz  = 0;
  uint64_t tls_zero_fill    = 0;
  uint64_t tls_align_chars  = 0;
  uint64_t tls_index_va     = 0;
  uint64_t tls_callbacks_va = 0;
  size_t shim_reg_tls_sym_idx  = 0; // dynsym index of shim_register_tls (UND)
  size_t shim_reg_tls_rela_idx = 0; // rela index for the call slot

  size_t dt_entry_count() const { return 12 + (inject_name.empty() ? 0 : 1); }

  Builder(PeImage& img, const Plan& p,
          const std::string& shim, const std::string& itp, bool sp,
          const std::string& inj)
    : image(img), plan(p), shim_name(shim), interp(itp), strip_pdata(sp), inject_name(inj) {}

  // Convert "KERNEL32.dll" + "GetModuleHandleA" → "kernel32_GetModuleHandleA"
  static std::string make_elf_sym_name(const std::string& dll, const std::string& fn) {
    std::string prefix = dll;
    auto dot = prefix.rfind('.');
    if( dot!=std::string::npos ) prefix = prefix.substr(0, dot);
    for( char& c : prefix ) c = (char)std::tolower((unsigned char)c);
    return prefix + "_" + fn;
  }

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
    if( !inject_name.empty() ) {
      dynstr_inject_off = (uint32_t)dynstr_data.size();
      for( char c : inject_name )
        dynstr_data.push_back((uint8_t)c);
      dynstr_data.push_back(0);
    }

    std::vector<std::string> unique_names;
    for( auto &ie : image.imports ) {
      std::string sym = make_elf_sym_name(ie.dll_name, ie.func_name);
      bool found = false;
      for( size_t k = 0; k<unique_names.size(); ++k ) {
        if( unique_names[k]==sym ) {
          ie.sym_index = (uint32_t)(k+1);
          found = true;
          break;
        }
      }
      if( !found ) {
        ie.sym_index = (uint32_t)(unique_names.size()+1);
        unique_names.push_back(sym);
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

    for( auto &re : image.relocs ) {
      Elf64_Rela r{};
      r.r_offset = re.va;
      r.r_info   = ELF64_R_INFO(0, R_X86_64_RELATIVE);
      r.r_addend = re.addend;
      rela_data.push_back(r);
    }

    // Add shim_register_tls as an undefined import symbol; the dynamic linker
    // resolves it from winapi_shim.so and writes its address into the call slot
    // inside the startup trampoline (see build_trampoline).
    shim_reg_tls_sym_idx = dynsym_data.size();
    {
      uint32_t str_off = (uint32_t)dynstr_data.size();
      const char* sym_name = "shim_register_tls";
      for( const char* p = sym_name; *p; ++p )
        dynstr_data.push_back((uint8_t)*p);
      dynstr_data.push_back(0);
      Elf64_Sym sym{};
      sym.st_name  = str_off;
      sym.st_info  = (uint8_t)((STB_GLOBAL<<4)|STT_FUNC);
      sym.st_shndx = SHN_UNDEF;
      dynsym_data.push_back(sym);
    }
    // Placeholder RELA for the call slot; r_offset fixed by finalize_tls_call().
    shim_reg_tls_rela_idx = rela_data.size();
    {
      Elf64_Rela r{};
      r.r_info = ELF64_R_INFO((uint32_t)shim_reg_tls_sym_idx, R_X86_64_64);
      rela_data.push_back(r);
    }
  }

  void finalize_tls_call(uint64_t slot_va) {
    if( shim_reg_tls_rela_idx < rela_data.size() )
      rela_data[shim_reg_tls_rela_idx].r_offset = slot_va;
  }

  bool build_trampoline() {
    uint64_t pe_entry = image.image_base+image.ep_rva;
    // Layout:
    //  +0  lea rdi,[rip+0x19] (7)  rip_after=+7,  tls_info at +32, disp=25
    //  +7  call [rip+0x0b]    (6)  rip_after=+13, slot at +24, disp=11
    //  +13 and rsp,-16        (4)  align to 16 bytes
    //  +17 push rax           (1)  RSP % 16 → 8: simulates PE entry via CALL
    //  +18 jmp rel32          (5)  rip_after=+23
    //  +23 nop                (1)
    //  +24 slot (8 bytes)          R_X86_64_64 → shim_register_tls
    //  +32 ShimTlsInfo (48 bytes)  6×uint64 TLS directory fields
    uint64_t jmp_end = plan.trampoline_va + 23;
    int64_t  d       = (int64_t)(pe_entry - jmp_end);
    if( d != (int32_t)d ) {
      fprintf(stderr, "Error: trampoline rel32 out of range "
              "(PE entry 0x%llx too far from synthetic segment)\n",
              (unsigned long long)pe_entry);
      return false;
    }
    int32_t rel32 = (int32_t)d;
    trampoline_data = {
      0x48, 0x8d, 0x3d, 0x19,0x00,0x00,0x00, // lea rdi,[rip+25] → tls_info@+32
      0xff, 0x15, 0x0b,0x00,0x00,0x00,        // call [rip+11]    → slot@+24
      0x48, 0x83, 0xe4, 0xf0,                 // and rsp,-16
      0x50,                                   // push rax (RSP % 16 → 8)
      0xe9,                                   // jmp rel32
        (uint8_t)(rel32),
        (uint8_t)(rel32>>8),
        (uint8_t)(rel32>>16),
        (uint8_t)(rel32>>24),
      0x90,                                   // nop (pad to +24)
      // slot at +24 (8 bytes, filled by RELA R_X86_64_64 shim_register_tls)
      0,0,0,0, 0,0,0,0,
    };
    // ShimTlsInfo at +32 (6×uint64_t = 48 bytes)
    auto push64 = [&](uint64_t v) {
      for( int i = 0; i < 8; ++i )
        trampoline_data.push_back((uint8_t)(v >> (i*8)));
    };
    push64(tls_template_va);
    push64(tls_template_sz);
    push64(tls_zero_fill);
    push64(tls_align_chars);
    push64(tls_index_va);
    push64(tls_callbacks_va);
    while( trampoline_data.size() < kTrampolineSize )
      trampoline_data.push_back(0x90);
    return true;
  }

  void build_dynamic() {
    auto dyn = [&](int64_t tag, uint64_t val) {
      Elf64_Dyn d{}; d.d_tag = tag; d.d_un.d_val = val;
      dynamic_data.push_back(d);
    };
    dyn(DT_NEEDED,  dynstr_shim_off);
    if( !inject_name.empty() )
      dyn(DT_NEEDED, dynstr_inject_off);
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
    assert(dynamic_data.size()==dt_entry_count());
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
      // Any section with R_X86_64_RELATIVE relocation targets must be writable
      // during dynamic linking so the loader can patch the addresses.
      uint64_t sec_va_start = image.image_base + sec.va;
      uint64_t sec_va_end   = sec_va_start + std::max((uint64_t)sec.virtsz, (uint64_t)sec.rawsz);
      for( auto &re : image.relocs ) {
        if( re.va >= sec_va_start && re.va < sec_va_end ) {
          flags |= PF_W;
          break;
        }
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
  }
};
