// pe2elf32.cpp - PE32 (i386) to ELF32 (EM_386) converter
// Standalone, no external dependencies. C++17.
// See !pe2elf32-plan.md for design rationale.
//
// Built natively (not -m32): this is a host tool that only *emits* ELF32
// bytes, it never executes them.

#include "pe_image32.hpp"
#include "elf_types32.hpp"
#include "elf_plan32.hpp"
#include "elf_build32.hpp"
#include "elf_write32.hpp"

// ---------------------------------------------------------------------------
// Main converter
// ---------------------------------------------------------------------------
struct Converter {
  PeImage image;
  Plan plan;

  std::string interp = "/lib/ld-linux.so.2";
  std::string shim_name = "winapi_shim32.so";
  std::string inject_name;
  bool keep_shdr = true;
  bool strip_pdata = false;
  bool pie = false;
  bool so_mode = false;
  uint64_t rebase_to = 0; // 0 = no explicit rebase

  bool convert(const char* in_path, const char* out_path) {
    if( !image.parse(in_path) )
      return false;

    // --so emits an ET_DYN shared object loadable via dlopen, so it needs
    // R_386_RELATIVE-style relocations like --pie.
    if( so_mode )
      pie = true;

    printf("PE32 ImageBase=0x%llx EP_RVA=0x%x sections=%u\n",
           (unsigned long long)image.image_base, image.ep_rva,
           (uint32_t)image.secmap.secs.size());

    if( !image.collect_imports() )
      return false;
    printf("Imports: %u IAT entries\n", (uint32_t)image.imports.size());

    if( !image.collect_relocs() )
      return false;
    printf("Base relocs: %u HIGHLOW entries\n", (uint32_t)image.relocs.size());

    if( rebase_to && !image.rebase(rebase_to) )
      return false;

    if( pie && image.relocs.empty() && image.ep_rva )
      printf("Note: no base relocations present; the image can only load at "
             "its preferred base 0x%llx\n", (unsigned long long)image.image_base);

    if( !image.collect_tls() )
      return false;

    Builder build(image, plan, shim_name, interp, strip_pdata, inject_name);
    build.pie_mode         = pie;
    build.so_mode          = so_mode;
    build.tls_template_va  = image.tls_template_va;
    build.tls_template_sz  = image.tls_template_sz;
    build.tls_zero_fill    = image.tls_zero_fill;
    build.tls_align_chars  = image.tls_align_chars;
    build.tls_index_va     = image.tls_index_va;
    build.tls_callbacks_va = image.tls_callbacks_va;
    build.build_synthetic_sections();
    plan = compute_plan(image, build.interp_data.size(), build.dynsym_data.size(),
                        build.dynstr_data.size(), build.rel_data.size(),
                        build.dt_entry_count(), build.hash_data.size());
    // Fix up REL r_offset for the shim_register_tls call slot and (for --so)
    // the _entrypoint symbol value + the ShimTlsInfo VA reloc r_offsets.
    build.finalize_tls_call(plan.trampoline_va + kTrampSlotOff);
    if( so_mode ) {
      build.safe_entry_va = build.find_safe_entry();
      if( !build.safe_entry_va ) {
        fprintf(stderr, "Error: --so: no 0xC3 (RET) byte found in any executable section\n");
        return false;
      }
      printf("--so: _entrypoint=0x%llx safe e_entry=0x%llx\n",
             (unsigned long long)plan.trampoline_va,
             (unsigned long long)build.safe_entry_va);
    }
    if( !build.build_trampoline() )
      return false;
    build.build_dynamic();
    build.patch_rdata();

    uint64_t last_end = plan.pe_data_foff;
    for( auto &sec : image.secmap.secs )
      last_end = std::max(last_end, sec.elf_foff+sec.rawsz);
    last_end = std::max(last_end, plan.pe_hdr_foff+image.oh->SizeOfHeaders);
    uint64_t shstrtab_foff = align_up(last_end, 8);
    uint64_t shoff = 0;

    build.build_phdrs(shoff);

    if( keep_shdr ) {
      build.build_shdrs(shstrtab_foff, plan.synth_va+shstrtab_foff);
      build.shdrs.back().sh_size = (uint32_t)build.shstrtab_data.size();
      shoff = align_up(shstrtab_foff+build.shstrtab_data.size(), 8);
    }

    Writer writer(image, plan, build, keep_shdr, pie);
    return writer.write(out_path, shoff, shstrtab_foff);
  }
};

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------
static void usage(const char* prog) {
  fprintf(stderr,
          "Usage: %s <input.exe> <output.elf>\n"
          "  [--interp <path>]       (default: /lib/ld-linux.so.2)\n"
          "  [--shim-soname <name>]  (default: winapi_shim32.so)\n"
          "  [--dbg]                 use winapi_shim32_dbg.so (logging enabled)\n"
          "  [--inject=<soname>]     add a second DT_NEEDED library\n"
          "  [--strip-pdata]         drop .pdata section (x64-only section;\n"
          "                          accepted for CLI parity, never matches on i386)\n"
          "  [--no-shdr]             omit section headers\n"
          "  [--pie]                 emit ET_DYN (PIE/ASLR) instead of ET_EXEC\n"
          "  [--so]                  emit a dlopen-able .so with _entrypoint export\n"
          "                          (implies --pie; e_entry points at a safe RET byte)\n"
          "  [--base=<addr>]         rebase to <addr> (patches relocs in-place;\n"
          "                          errors if original base differs and no relocs)\n",
          prog);
}

int main(int argc, char** argv) {
  if( argc<3 ) {
    usage(argv[0]);
    return 1;
  }

  Converter conv;
  const char* in_path = nullptr;
  const char* out_path = nullptr;

  for( int i = 1; i<argc; ++i ) {
    if( !strcmp(argv[i], "--interp")&&i+1<argc ) {
      conv.interp = argv[++i];
    } else if( !strcmp(argv[i], "--shim-soname")&&i+1<argc ) {
      conv.shim_name = argv[++i];
    } else if( !strcmp(argv[i], "--dbg") ) {
      conv.shim_name = "winapi_shim32_dbg.so";
    } else if( !strncmp(argv[i], "--inject=", 9) ) {
      conv.inject_name = argv[i]+9;
    } else if( !strcmp(argv[i], "--strip-pdata") ) {
      conv.strip_pdata = true;
    } else if( !strcmp(argv[i], "--no-shdr") ) {
      conv.keep_shdr = false;
    } else if( !strcmp(argv[i], "--pie") ) {
      conv.pie = true;
    } else if( !strcmp(argv[i], "--so") ) {
      conv.so_mode = true;
    } else if( !strncmp(argv[i], "--base=", 7) ) {
      char* endp;
      conv.rebase_to = strtoull(argv[i]+7, &endp, 0);
      if( *endp ) {
        fprintf(stderr, "Invalid base address: %s\n", argv[i]+7);
        return 1;
      }
    } else if( !in_path ) {
      in_path = argv[i];
    } else if( !out_path ) {
      out_path = argv[i];
    } else {
      fprintf(stderr, "Unknown argument: %s\n", argv[i]);
      usage(argv[0]);
      return 1;
    }
  }

  if( !in_path||!out_path ) {
    usage(argv[0]);
    return 1;
  }

  return conv.convert(in_path, out_path) ? 0 : 1;
}
