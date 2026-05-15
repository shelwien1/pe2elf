#pragma once
#include "util.hpp"
#include "pe_image.hpp"
#include "elf_types.hpp"
#include "elf_plan.hpp"
#include "elf_build.hpp"

// ---------------------------------------------------------------------------
// Writer: serializes ELF content from Builder+Plan+PeImage to a file
// ---------------------------------------------------------------------------
struct Writer {
  const PeImage& image;
  const Plan& plan;
  const Builder& build;
  bool keep_shdr;
  bool pie;

  Writer(const PeImage& img, const Plan& p, const Builder& b, bool ks, bool pie_ = false)
    : image(img), plan(p), build(b), keep_shdr(ks), pie(pie_) {}

  bool write(const char* out_path, uint64_t shoff, uint64_t shstrtab_foff) {
    Elf64_Ehdr ehdr{};
    ehdr.e_ident[0] = 0x7f;
    ehdr.e_ident[1] = 'E';
    ehdr.e_ident[2] = 'L';
    ehdr.e_ident[3] = 'F';
    ehdr.e_ident[4] = 2; // ELFCLASS64
    ehdr.e_ident[5] = 1; // ELFDATA2LSB
    ehdr.e_ident[6] = 1; // EV_CURRENT
    ehdr.e_ident[7] = 0; // ELFOSABI_NONE
    ehdr.e_type = pie ? ET_DYN : ET_EXEC;
    ehdr.e_machine = EM_X86_64;
    ehdr.e_version = 1;
    ehdr.e_entry = plan.trampoline_va;
    ehdr.e_phoff = sizeof(Elf64_Ehdr);
    ehdr.e_shoff = keep_shdr ? shoff : 0;
    ehdr.e_flags = 0;
    ehdr.e_ehsize = sizeof(Elf64_Ehdr);
    ehdr.e_phentsize = sizeof(Elf64_Phdr);
    ehdr.e_phnum = (uint16_t)build.phdrs.size();
    ehdr.e_shentsize = sizeof(Elf64_Shdr);
    ehdr.e_shnum = keep_shdr ? (uint16_t)build.shdrs.size() : 0;
    ehdr.e_shstrndx = keep_shdr ? (uint16_t)(build.shdrs.size()-1) : 0;

    OutBuf out;

    out.append(&ehdr, sizeof(ehdr));
    for( auto &p : build.phdrs )
      out.append(&p, sizeof(p));

    out.pad_to_size(plan.interp_foff);
    out.append(build.interp_data.data(), build.interp_data.size());
    out.pad_to_size(plan.dynsym_foff);
    out.append(build.dynsym_data.data(), build.dynsym_data.size()*sizeof(Elf64_Sym));
    out.pad_to_size(plan.dynstr_foff);
    out.append(build.dynstr_data.data(), build.dynstr_data.size());
    out.pad_to_size(plan.rela_foff);
    out.append(build.rela_data.data(), build.rela_data.size()*sizeof(Elf64_Rela));
    out.pad_to_size(plan.dynamic_foff);
    out.append(build.dynamic_data.data(), build.dynamic_data.size()*sizeof(Elf64_Dyn));
    out.pad_to_size(plan.trampoline_foff);
    out.append(build.trampoline_data.data(), build.trampoline_data.size());

    for( uint32_t i = 0; i<image.secmap.secs.size(); ++i ) {
      auto &sec = image.secmap.secs[i];
      out.pad_to_size(sec.elf_foff);
      if( (int)i==image.rdata_sec_idx&&!build.rdata_patched.empty() ) {
        out.append(build.rdata_patched.data(), build.rdata_patched.size());
      } else {
        if( sec.raw+sec.rawsz<=image.buf.size() ) {
          out.append(image.buf.data.data()+sec.raw, sec.rawsz);
        } else {
          size_t avail = (sec.raw<image.buf.size()) ? image.buf.size()-sec.raw : 0;
          if( avail>0 )
            out.append(image.buf.data.data()+sec.raw, avail);
          for( size_t z = avail; z<sec.rawsz; ++z )
            out.append_val<uint8_t>(0);
        }
      }
    }

    out.pad_to_size(plan.pe_hdr_foff);
    {
      uint32_t hdr_size = image.oh->SizeOfHeaders;
      if( hdr_size>image.buf.size() )
        hdr_size = (uint32_t)image.buf.size();
      out.append(image.buf.data.data(), hdr_size);
    }

    if( keep_shdr ) {
      out.pad_to_size(shstrtab_foff);
      out.append(build.shstrtab_data.data(), build.shstrtab_data.size());
      out.pad_to_size(shoff);
      for( auto &s : build.shdrs )
        out.append(&s, sizeof(s));
    }

    FILE* f = fopen(out_path, "wb");
    if( !f ) {
      fprintf(stderr, "Cannot create: %s\n", out_path);
      return false;
    }
    size_t written = fwrite(out.data.data(), 1, out.data.size(), f);
    fclose(f);
    if( written!=out.data.size() ) {
      fprintf(stderr, "Write error\n");
      return false;
    }
#ifndef _WIN32
    chmod(out_path, 0755);
#endif

    printf("Written %zu bytes to %s\n", out.data.size(), out_path);
    printf("Entry point: 0x%llx\n", (unsigned long long)(image.image_base+image.ep_rva));
    printf("Synthetic segment VA: 0x%llx\n", (unsigned long long)plan.synth_va);
    printf("Program headers: %u\n", (uint32_t)build.phdrs.size());
    if( keep_shdr )
      printf("Section headers: %u\n", (uint32_t)build.shdrs.size());
    return true;
  }
};
