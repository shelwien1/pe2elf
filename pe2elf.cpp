// pe2elf.cpp - PE32+ (x64) to ELF64 (x86-64) converter
// Standalone, no external dependencies. C++17.
// See !pe2elf-plan.md for design rationale.

#include "pe_image.hpp"
#include "elf_types.hpp"
#include "elf_plan.hpp"
#include "elf_build.hpp"
#include "elf_write.hpp"

// ---------------------------------------------------------------------------
// Main converter
// ---------------------------------------------------------------------------
struct Converter {
  PeImage image;
  Plan plan;

  std::string interp = "/lib64/ld-linux-x86-64.so.2";
  std::string shim_name = "winapi_shim.so";
  std::string inject_name;
  bool keep_shdr = true;
  bool strip_pdata = false;
  bool pie = false;
  uint64_t rebase_to = 0; // 0 = no explicit rebase

  bool convert(const char* in_path, const char* out_path) {
    if( !image.parse(in_path) )
      return false;

    printf("PE32+ ImageBase=0x%llx EP_RVA=0x%x sections=%u\n",
           (unsigned long long)image.image_base, image.ep_rva,
           (uint32_t)image.secmap.secs.size());

    if( !image.collect_imports() )
      return false;
    printf("Imports: %u IAT entries\n", (uint32_t)image.imports.size());

    if( !image.collect_relocs() )
      return false;
    printf("Base relocs: %u DIR64 entries\n", (uint32_t)image.relocs.size());

    if( rebase_to && !image.rebase(rebase_to) )
      return false;

    if( !image.collect_tls() )
      return false;

    Builder build(image, plan, shim_name, interp, strip_pdata, inject_name);
    build.tls_template_va  = image.tls_template_va;
    build.tls_template_sz  = image.tls_template_sz;
    build.tls_zero_fill    = image.tls_zero_fill;
    build.tls_align_chars  = image.tls_align_chars;
    build.tls_index_va     = image.tls_index_va;
    build.tls_callbacks_va = image.tls_callbacks_va;
    build.build_synthetic_sections();
    plan = compute_plan(image, build.interp_data.size(), build.dynsym_data.size(),
                        build.dynstr_data.size(), build.rela_data.size(),
                        build.dt_entry_count());
    // Fix up RELA r_offset for shim_register_tls call slot (trampoline+24)
    build.finalize_tls_call(plan.trampoline_va + 24);
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
      build.shdrs.back().sh_size = build.shstrtab_data.size();
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
          "  [--interp <path>]       (default: /lib64/ld-linux-x86-64.so.2)\n"
          "  [--shim-soname <name>]  (default: winapi_shim.so)\n"
          "  [--dbg]                 use winapi_shim_dbg.so (logging enabled)\n"
          "  [--inject=<soname>]     add a second DT_NEEDED library\n"
          "  [--strip-pdata]         drop .pdata section\n"
          "  [--no-shdr]             omit section headers\n"
          "  [--pie]                 emit ET_DYN (PIE/ASLR) instead of ET_EXEC\n"
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
      conv.shim_name = "winapi_shim_dbg.so";
    } else if( !strncmp(argv[i], "--inject=", 9) ) {
      conv.inject_name = argv[i]+9;
    } else if( !strcmp(argv[i], "--strip-pdata") ) {
      conv.strip_pdata = true;
    } else if( !strcmp(argv[i], "--no-shdr") ) {
      conv.keep_shdr = false;
    } else if( !strcmp(argv[i], "--pie") ) {
      conv.pie = true;
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
