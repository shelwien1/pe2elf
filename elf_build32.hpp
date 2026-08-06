#pragma once
#include "util.hpp"
#include "pe_image32.hpp"
#include "elf_types32.hpp"
#include "elf_plan32.hpp"

// ---------------------------------------------------------------------------
// Builder: constructs all ELF32 in-memory content from a PeImage and Plan
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
  std::vector<Elf32_Sym> dynsym_data;
  std::vector<Elf32_Rel> rel_data;
  std::vector<Elf32_Dyn> dynamic_data;
  std::vector<uint8_t>   trampoline_data;
  std::vector<uint8_t>   hash_data; // only populated in --so mode

  // IAT section with slots zeroed
  std::vector<uint8_t> rdata_patched;

  // ELF structural tables
  std::vector<Elf32_Phdr> phdrs;
  std::vector<Elf32_Shdr> shdrs;
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
  size_t shim_reg_tls_sym_idx = 0; // dynsym index of shim_register_tls (UND)
  size_t shim_reg_tls_rel_idx = 0; // rel index for the call slot

  // ET_DYN output (--pie / --so).  Selects the position-independent
  // trampoline (get-PC thunk) and makes the ShimTlsInfo VA fields
  // load-bias-relocated.
  bool pie_mode = false;
  // --so mode: emit a dlopen-able .so. We export `_entrypoint` (the
  // startup trampoline) and point e_entry at a 0xC3 byte inside the PE
  // code so anything that accidentally lands on it just RETs.
  bool so_mode = false;
  uint64_t safe_entry_va = 0;        // first 0xC3 in any X section; filled by find_safe_entry
  size_t entrypoint_sym_idx = 0;     // dynsym index of `_entrypoint` (defined)
  // REL indices for the three VA fields of ShimTlsInfo in the trampoline
  // (template, index, callbacks). SIZE_MAX = no reloc emitted for that field.
  size_t tls_va_rel_idx[3] = {SIZE_MAX, SIZE_MAX, SIZE_MAX};

  size_t dt_entry_count() const {
    // base 12 + DT_NEEDED for inject + DT_HASH for --so mode
    return 12 + (inject_name.empty() ? 0 : 1) + (so_mode ? 1 : 0);
  }

  // SysV ELF hash (used by DT_HASH).
  static uint32_t elf_sysv_hash(const char* name) {
    uint32_t h = 0, g;
    while( *name ) {
      h = (h<<4) + (unsigned char)*name++;
      g = h & 0xf0000000u;
      if( g ) h ^= g>>24;
      h &= ~g;
    }
    return h;
  }

  // Build the DT_HASH table over dynsym_data. Required for dlsym lookups
  // on the .so. Layout: nbucket | nchain | buckets[nbucket] | chain[nchain].
  void build_hash() {
    uint32_t nchain  = (uint32_t)dynsym_data.size();
    uint32_t nbucket = nchain ? nchain : 1;
    std::vector<uint32_t> buckets(nbucket, 0);
    std::vector<uint32_t> chain(nchain, 0);
    for( uint32_t i = 1; i<nchain; ++i ) {
      uint32_t name_off = dynsym_data[i].st_name;
      if( name_off>=dynstr_data.size() ) continue;
      const char* name = (const char*)dynstr_data.data()+name_off;
      uint32_t bucket = elf_sysv_hash(name) % nbucket;
      chain[i] = buckets[bucket];
      buckets[bucket] = i;
    }
    hash_data.clear();
    auto push32 = [&](uint32_t v) {
      for( int i = 0; i<4; ++i )
        hash_data.push_back((uint8_t)(v>>(i*8)));
    };
    push32(nbucket);
    push32(nchain);
    for( uint32_t b : buckets ) push32(b);
    for( uint32_t c : chain   ) push32(c);
  }

  Builder(PeImage& img, const Plan& p,
          const std::string& shim, const std::string& itp, bool sp,
          const std::string& inj)
    : image(img), plan(p), shim_name(shim), interp(itp), strip_pdata(sp), inject_name(inj) {}

  // Convert "KERNEL32.dll" + "GetModuleHandleA" → "kernel32_GetModuleHandleA".
  // stdcall does not decorate symbols on i386 ELF, so the naming scheme is
  // byte-for-byte the same as the 64-bit tool's.
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

    dynsym_data.push_back(Elf32_Sym{});
    for( auto &name : unique_names ) {
      uint32_t str_off = (uint32_t)dynstr_data.size();
      for( char c : name )
        dynstr_data.push_back((uint8_t)c);
      dynstr_data.push_back(0);
      Elf32_Sym sym{};
      sym.st_name  = str_off;
      sym.st_info  = (uint8_t)((STB_GLOBAL<<4)|STT_FUNC);
      sym.st_shndx = SHN_UNDEF;
      dynsym_data.push_back(sym);
    }

    // IAT slots: R_386_32 against the shim symbol.  patch_rdata() zeroes
    // each slot so the in-place addend is 0 and the loader stores S+0 = S.
    for( auto &ie : image.imports ) {
      Elf32_Rel r{};
      r.r_offset = (uint32_t)(image.image_base+ie.iat_rva);
      r.r_info   = ELF32_R_INFO(ie.sym_index, R_386_32);
      rel_data.push_back(r);
    }

    // PE base relocations: R_386_RELATIVE.  The site still holds the
    // absolute preferred VA written by the linker, which is exactly the
    // addend the loader adds the load bias to — so nothing to store and
    // nothing to zero.
    for( auto &re : image.relocs ) {
      Elf32_Rel r{};
      r.r_offset = (uint32_t)re.va;
      r.r_info   = ELF32_R_INFO(0, R_386_RELATIVE);
      rel_data.push_back(r);
    }

    // Add shim_register_tls as an undefined import symbol; the dynamic linker
    // resolves it from winapi_shim32.so and writes its address into the call
    // slot inside the startup trampoline (see build_trampoline).
    shim_reg_tls_sym_idx = dynsym_data.size();
    {
      uint32_t str_off = (uint32_t)dynstr_data.size();
      const char* sym_name = "shim_register_tls";
      for( const char* p = sym_name; *p; ++p )
        dynstr_data.push_back((uint8_t)*p);
      dynstr_data.push_back(0);
      Elf32_Sym sym{};
      sym.st_name  = str_off;
      sym.st_info  = (uint8_t)((STB_GLOBAL<<4)|STT_FUNC);
      sym.st_shndx = SHN_UNDEF;
      dynsym_data.push_back(sym);
    }
    // Placeholder REL for the call slot; r_offset fixed by finalize_tls_call().
    shim_reg_tls_rel_idx = rel_data.size();
    {
      Elf32_Rel r{};
      r.r_info = ELF32_R_INFO((uint32_t)shim_reg_tls_sym_idx, R_386_32);
      rel_data.push_back(r);
    }

    if( so_mode ) {
      // Export `_entrypoint` so a loader can dlsym it and invoke the PE.
      // st_value is patched by finalize_tls_call once trampoline_va is known.
      entrypoint_sym_idx = dynsym_data.size();
      uint32_t str_off = (uint32_t)dynstr_data.size();
      const char* sym_name = "_entrypoint";
      for( const char* p = sym_name; *p; ++p )
        dynstr_data.push_back((uint8_t)*p);
      dynstr_data.push_back(0);
      Elf32_Sym sym{};
      sym.st_name  = str_off;
      sym.st_info  = (uint8_t)((STB_GLOBAL<<4)|STT_FUNC);
      // Any non-UNDEF, non-ABS index works at dlsym time — ld.so just does
      // l_addr + st_value. Use 1 (.dynsym) so a defined section index is set.
      sym.st_shndx = 1;
      sym.st_value = 0;
      sym.st_size  = kTrampolineSize;
      dynsym_data.push_back(sym);
    }

    if( pie_mode ) {
      // ShimTlsInfo lives inside the trampoline; its three VA fields are
      // absolute preferred VAs and must track the runtime load base, so
      // emit an R_386_RELATIVE for each.  The addend is the preferred VA
      // already written into the trampoline bytes.  r_offset is patched in
      // finalize_tls_call once trampoline_va is known.
      auto add_tls_va_reloc = [&](size_t which, uint64_t va) {
        if( !va ) return;
        tls_va_rel_idx[which] = rel_data.size();
        Elf32_Rel r{};
        r.r_info = ELF32_R_INFO(0, R_386_RELATIVE);
        rel_data.push_back(r);
      };
      add_tls_va_reloc(0, tls_template_va);
      add_tls_va_reloc(1, tls_index_va);
      add_tls_va_reloc(2, tls_callbacks_va);
    }

    if( so_mode ) {
      // Hash over the now-complete dynsym (must include _entrypoint).
      build_hash();
    }
  }

  void finalize_tls_call(uint64_t slot_va) {
    if( shim_reg_tls_rel_idx < rel_data.size() )
      rel_data[shim_reg_tls_rel_idx].r_offset = (uint32_t)slot_va;
    uint64_t tramp_va = slot_va - kTrampSlotOff;
    if( so_mode && entrypoint_sym_idx < dynsym_data.size() )
      dynsym_data[entrypoint_sym_idx].st_value = (uint32_t)tramp_va;
    // Field offsets within ShimTlsInfo (6 × uint32): 0,4,8,12,16,20
    uint64_t info_va = tramp_va + kTrampInfoOff;
    if( tls_va_rel_idx[0] < rel_data.size() )
      rel_data[tls_va_rel_idx[0]].r_offset = (uint32_t)(info_va + 0);  // template_va
    if( tls_va_rel_idx[1] < rel_data.size() )
      rel_data[tls_va_rel_idx[1]].r_offset = (uint32_t)(info_va + 16); // index_va
    if( tls_va_rel_idx[2] < rel_data.size() )
      rel_data[tls_va_rel_idx[2]].r_offset = (uint32_t)(info_va + 20); // callbacks_va
  }

  // Locate the first 0xC3 (RET) byte inside any executable PE section,
  // used as e_entry in --so mode so accidental execution just returns.
  uint64_t find_safe_entry() const {
    for( auto &sec : image.secmap.secs ) {
      if( !(sec.characteristics & PE_SCN_MEM_EXECUTE) ) continue;
      size_t avail = (sec.raw < image.buf.size())
                     ? (image.buf.size() - sec.raw) : 0;
      size_t scan  = std::min((size_t)sec.rawsz, avail);
      for( size_t i = 0; i < scan; ++i ) {
        if( image.buf.data[sec.raw + i] == 0xC3 )
          return image.image_base + sec.va + i;
      }
    }
    return 0;
  }

  // The startup trampoline.  i386 has no RIP-relative addressing, so the
  // ET_EXEC form uses absolute immediates (valid because an ET_EXEC loads at
  // its link address) and the ET_DYN form anchors itself with a call/pop
  // get-PC thunk.
  //
  // Stack shape: `and esp,-16` gives esp ≡ 0 (mod 16); pushing the argument
  // and letting the stdcall callee pop it leaves esp ≡ 0 again; the dummy
  // `push eax` then lands at esp ≡ 12 (mod 16) — exactly what a function
  // entered by CALL from a 16-byte-aligned call site sees, which is the
  // frame shape BaseThreadInitThunk hands the PE entry point on Windows.
  bool build_trampoline() {
    uint64_t pe_entry = image.image_base+image.ep_rva;
    uint64_t slot_va  = plan.trampoline_va + kTrampSlotOff;
    uint64_t info_va  = plan.trampoline_va + kTrampInfoOff;

    auto push8  = [&](uint8_t v) { trampoline_data.push_back(v); };
    auto push32 = [&](uint32_t v) {
      for( int i = 0; i < 4; ++i )
        trampoline_data.push_back((uint8_t)(v >> (i*8)));
    };

    trampoline_data.clear();
    uint64_t jmp_end;   // VA just past the jmp rel32 (the rel32 origin)

    if( !pie_mode ) {
      // +0   83 E4 F0            and  esp,-16
      // +3   68 <info_va>        push imm32          → &ShimTlsInfo
      // +8   FF 15 <slot_va>     call [slot_va]      → shim_register_tls
      // +14  50                  push eax            → dummy return address
      // +15  E9 <rel32>          jmp  PE entry
      jmp_end = plan.trampoline_va + 20;
      push8(0x83); push8(0xE4); push8(0xF0);
      push8(0x68); push32((uint32_t)info_va);
      push8(0xFF); push8(0x15); push32((uint32_t)slot_va);
      push8(0x50);
    } else {
      // +0   E8 00 00 00 00      call next            (get-PC thunk)
      // +5   59                  pop  ecx             → ecx = tramp_va+5
      // +6   83 E4 F0            and  esp,-16
      // +9   8D 81 <disp32>      lea  eax,[ecx+disp]  → &ShimTlsInfo
      // +15  50                  push eax             → the argument
      // +16  FF 91 <disp32>      call [ecx+disp]      → shim_register_tls
      // +22  50                  push eax             → dummy return address
      // +23  E9 <rel32>          jmp  PE entry
      // ecx and eax are caller-saved under both stdcall and cdecl.
      jmp_end = plan.trampoline_va + 28;
      push8(0xE8); push32(0);
      push8(0x59);
      push8(0x83); push8(0xE4); push8(0xF0);
      push8(0x8D); push8(0x81); push32((uint32_t)(kTrampInfoOff - 5));
      push8(0x50);
      push8(0xFF); push8(0x91); push32((uint32_t)(kTrampSlotOff - 5));
      push8(0x50);
    }

    // The jmp needs no relocation even under PIE: the trampoline and the PE
    // code shift by the same load bias, so their displacement is a link-time
    // constant.
    int64_t d = (int64_t)(pe_entry - jmp_end);
    if( d != (int32_t)d ) {
      fprintf(stderr, "Error: trampoline rel32 out of range "
              "(PE entry 0x%llx too far from synthetic segment)\n",
              (unsigned long long)pe_entry);
      return false;
    }
    push8(0xE9); push32((uint32_t)(int32_t)d);

    while( trampoline_data.size() < kTrampSlotOff )
      push8(0x90);
    push32(0);                                  // slot (R_386_32 → shim_register_tls)
    while( trampoline_data.size() < kTrampInfoOff )
      push8(0x90);
    push32((uint32_t)tls_template_va);           // +0
    push32((uint32_t)tls_template_sz);           // +4
    push32((uint32_t)tls_zero_fill);             // +8
    push32((uint32_t)tls_align_chars);           // +12
    push32((uint32_t)tls_index_va);              // +16
    push32((uint32_t)tls_callbacks_va);          // +20
    while( trampoline_data.size() < kTrampolineSize )
      push8(0x90);
    return true;
  }

  void build_dynamic() {
    auto dyn = [&](int32_t tag, uint32_t val) {
      Elf32_Dyn d{}; d.d_tag = tag; d.d_un.d_val = val;
      dynamic_data.push_back(d);
    };
    dyn(DT_NEEDED,  dynstr_shim_off);
    if( !inject_name.empty() )
      dyn(DT_NEEDED, dynstr_inject_off);
    dyn(DT_RUNPATH, dynstr_rpath_off);
    dyn(DT_STRTAB,  (uint32_t)plan.dynstr_va);
    dyn(DT_STRSZ,   (uint32_t)dynstr_data.size());
    dyn(DT_SYMTAB,  (uint32_t)plan.dynsym_va);
    dyn(DT_SYMENT,  sizeof(Elf32_Sym));
    if( so_mode )
      dyn(DT_HASH,  (uint32_t)plan.hash_va);
    dyn(DT_REL,     (uint32_t)plan.rel_va);
    dyn(DT_RELSZ,   (uint32_t)(rel_data.size()*sizeof(Elf32_Rel)));
    dyn(DT_RELENT,  sizeof(Elf32_Rel));
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
      if( slot_off+4<=raw_size )
        memset(rdata_patched.data()+slot_off, 0, 4);
    }
  }

  void build_phdrs(uint64_t /*shoff*/) {
    phdrs.clear();
    uint32_t n_pe_secs = (uint32_t)image.secmap.secs.size();

    // PT_LOAD entries are collected separately and emitted in ascending
    // p_vaddr order, as the ELF spec requires.  This is load-bearing for
    // ET_DYN (--pie/--so): glibc reserves the whole image with one mmap
    // sized `last_load.allocend - first_load.mapstart`, so an out-of-order
    // list under-reserves and the trailing segments get MAP_FIXED on top of
    // whatever else the loader had already placed there.
    std::vector<Elf32_Phdr> loads;

    // PT_PHDR — filesz/memsz patched at end
    {
      Elf32_Phdr p{};
      p.p_type   = PT_PHDR;
      p.p_flags  = PF_R;
      p.p_offset = sizeof(Elf32_Ehdr);
      p.p_vaddr  = (uint32_t)(plan.synth_va+sizeof(Elf32_Ehdr));
      p.p_paddr  = p.p_vaddr;
      p.p_align  = 4;
      phdrs.push_back(p);
    }
    {
      Elf32_Phdr p{};
      p.p_type   = PT_INTERP;
      p.p_flags  = PF_R;
      p.p_offset = (uint32_t)plan.interp_foff;
      p.p_vaddr  = (uint32_t)plan.interp_va;
      p.p_paddr  = p.p_vaddr;
      p.p_filesz = (uint32_t)interp_data.size();
      p.p_memsz  = (uint32_t)interp_data.size();
      p.p_align  = 1;
      phdrs.push_back(p);
    }
    {
      uint64_t syn_filesz = plan.trampoline_foff+trampoline_data.size();
      Elf32_Phdr p{};
      p.p_type   = PT_LOAD;
      p.p_flags  = PF_R|PF_W|PF_X;
      p.p_offset = (uint32_t)plan.synth_foff;
      p.p_vaddr  = (uint32_t)plan.synth_va;
      p.p_paddr  = p.p_vaddr;
      p.p_filesz = (uint32_t)syn_filesz;
      p.p_memsz  = (uint32_t)syn_filesz;
      p.p_align  = kPageSize;
      loads.push_back(p);
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
      // Any section with R_386_RELATIVE relocation targets must be writable
      // during dynamic linking so the loader can patch the addresses.
      uint64_t sec_va_start = image.image_base + sec.va;
      uint64_t sec_va_end   = sec_va_start + std::max((uint64_t)sec.virtsz, (uint64_t)sec.rawsz);
      for( auto &re : image.relocs ) {
        if( re.va >= sec_va_start && re.va < sec_va_end ) {
          flags |= PF_W;
          break;
        }
      }
      Elf32_Phdr p{};
      p.p_type   = PT_LOAD;
      p.p_flags  = flags;
      p.p_offset = (uint32_t)sec.elf_foff;
      p.p_vaddr  = (uint32_t)(image.image_base+sec.va);
      p.p_paddr  = p.p_vaddr;
      p.p_filesz = sec.rawsz;
      p.p_memsz  = std::max(sec.virtsz, sec.rawsz);
      p.p_align  = kPageSize;
      loads.push_back(p);
    }

    // The PE headers, kept mapped at ImageBase so runtime code that walks its
    // own image (resource lookups, GetModuleHandle-style checks) finds an MZ.
    {
      Elf32_Phdr p{};
      p.p_type   = PT_LOAD;
      p.p_flags  = PF_R;
      p.p_offset = (uint32_t)plan.pe_hdr_foff;
      p.p_vaddr  = (uint32_t)image.image_base;
      p.p_paddr  = p.p_vaddr;
      p.p_filesz = image.oh->SizeOfHeaders;
      p.p_memsz  = (uint32_t)align_up(image.oh->SizeOfHeaders, kPageSize);
      p.p_align  = kPageSize;
      loads.push_back(p);
    }

    std::stable_sort(loads.begin(), loads.end(),
                     [](const Elf32_Phdr& a, const Elf32_Phdr& b) {
                       return a.p_vaddr < b.p_vaddr;
                     });
    phdrs.insert(phdrs.end(), loads.begin(), loads.end());

    {
      Elf32_Phdr p{};
      p.p_type   = PT_DYNAMIC;
      p.p_flags  = PF_R|PF_W;
      p.p_offset = (uint32_t)plan.dynamic_foff;
      p.p_vaddr  = (uint32_t)plan.dynamic_va;
      p.p_paddr  = p.p_vaddr;
      p.p_filesz = (uint32_t)(dynamic_data.size()*sizeof(Elf32_Dyn));
      p.p_memsz  = p.p_filesz;
      p.p_align  = 4;
      phdrs.push_back(p);
    }
    if( relro_sec_idx>=0 ) {
      auto &sec = image.secmap.secs[relro_sec_idx];
      Elf32_Phdr p{};
      p.p_type   = PT_GNU_RELRO;
      p.p_flags  = PF_R;
      p.p_offset = (uint32_t)sec.elf_foff;
      p.p_vaddr  = (uint32_t)(image.image_base+sec.va);
      p.p_paddr  = p.p_vaddr;
      p.p_filesz = sec.rawsz;
      p.p_memsz  = sec.rawsz;
      p.p_align  = 1;
      phdrs.push_back(p);
    }
    {
      Elf32_Phdr p{};
      p.p_type  = PT_GNU_STACK;
      p.p_flags = PF_R|PF_W;
      p.p_align = 0x10;
      phdrs.push_back(p);
    }

    phdrs[0].p_filesz = (uint32_t)(phdrs.size()*sizeof(Elf32_Phdr));
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

    shdrs.push_back(Elf32_Shdr{}); // [0] NULL

    auto add = [&](const char* name, uint32_t type, uint32_t flags,
                   uint64_t addr, uint64_t off, uint64_t size,
                   uint32_t link, uint32_t info, uint32_t align, uint32_t entsize) {
      Elf32_Shdr s{};
      s.sh_name      = add_shstrtab(name);
      s.sh_type      = type;
      s.sh_flags     = flags;
      s.sh_addr      = (uint32_t)addr;
      s.sh_offset    = (uint32_t)off;
      s.sh_size      = (uint32_t)size;
      s.sh_link      = link;
      s.sh_info      = info;
      s.sh_addralign = align;
      s.sh_entsize   = entsize;
      shdrs.push_back(s);
    };

    uint32_t dynsym_shidx = (uint32_t)shdrs.size();
    add(".dynsym", SHT_DYNSYM, SHF_ALLOC,
        plan.dynsym_va, plan.dynsym_foff, dynsym_data.size()*sizeof(Elf32_Sym),
        dynsym_shidx+1, 1, 4, sizeof(Elf32_Sym));

    add(".dynstr", SHT_STRTAB, SHF_ALLOC,
        plan.dynstr_va, plan.dynstr_foff, dynstr_data.size(),
        0, 0, 1, 0);

    if( !hash_data.empty() ) {
      add(".hash", SHT_HASH, SHF_ALLOC,
          plan.hash_va, plan.hash_foff, hash_data.size(),
          dynsym_shidx, 0, 4, 4);
    }

    add(".rel.dyn", SHT_REL, SHF_ALLOC,
        plan.rel_va, plan.rel_foff, rel_data.size()*sizeof(Elf32_Rel),
        dynsym_shidx, 0, 4, sizeof(Elf32_Rel));

    add(".dynamic", SHT_DYNAMIC, SHF_ALLOC|SHF_WRITE,
        plan.dynamic_va, plan.dynamic_foff, dynamic_data.size()*sizeof(Elf32_Dyn),
        dynsym_shidx+1, 0, 4, sizeof(Elf32_Dyn));

    add(".interp", SHT_PROGBITS, SHF_ALLOC,
        plan.interp_va, plan.interp_foff, interp_data.size(),
        0, 0, 1, 0);

    for( uint32_t i = 0; i<image.secmap.secs.size(); ++i ) {
      auto &sec = image.secmap.secs[i];
      uint32_t ch = sec.characteristics;
      uint32_t sh_flags = SHF_ALLOC;
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
