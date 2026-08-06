#pragma once
#include "util.hpp"
#include "pe_image32.hpp"
#include "elf_types32.hpp"

// ---------------------------------------------------------------------------
// Layout plan: all VAs and file offsets, computed before any bytes are emitted
// ---------------------------------------------------------------------------
struct Plan {
  // Synthetic segment (ELF headers + auxiliary sections + trampoline)
  uint64_t synth_va = 0;
  uint64_t synth_foff = 0; // always 0
  uint64_t synth_end_va = 0;

  // Synthetic section file offsets (also VA relative to synth_va)
  uint64_t interp_foff = 0;
  uint64_t dynsym_foff = 0;
  uint64_t dynstr_foff = 0;
  uint64_t hash_foff = 0;   // only used in --so mode (SysV DT_HASH)
  uint64_t rel_foff = 0;
  uint64_t dynamic_foff = 0;
  uint64_t trampoline_foff = 0;

  // Synthetic section virtual addresses
  uint64_t interp_va = 0;
  uint64_t dynsym_va = 0;
  uint64_t dynstr_va = 0;
  uint64_t hash_va = 0;
  uint64_t rel_va = 0;
  uint64_t dynamic_va = 0;
  uint64_t trampoline_va = 0;

  // PE section and header placement
  uint64_t pe_data_foff = 0;
  uint64_t pe_hdr_foff = 0;
};

// Trampoline layout (both the ET_EXEC and the PIC variant use the same
// offsets for the tail so finalize_tls_call() doesn't need to know which
// one was emitted):
//   +0   code (20 bytes absolute / 27 bytes PIC), padded with NOPs
//   +32  slot        4 bytes   R_386_32 → shim_register_tls
//   +40  ShimTlsInfo 24 bytes  6 × uint32
static constexpr size_t   kTrampSlotOff     = 32;
static constexpr size_t   kTrampInfoOff     = 40;
static constexpr size_t   kTrampolineSize   = 64;
static constexpr size_t   kPhdrsMaxCount    = 20;
static constexpr uint64_t kSynthMargin      = 0x10000;
// Comfortably above the usual mmap_min_addr (0x10000) and far below the
// 0x400000 default PE32 ImageBase.
static constexpr uint64_t kSynthFallbackVa  = 0x200000;

// ---------------------------------------------------------------------------
// Compute the layout plan from a parsed PeImage and pre-built section content.
// ---------------------------------------------------------------------------
inline Plan compute_plan(PeImage& image,
                         size_t interp_size,
                         size_t dynsym_count,
                         size_t dynstr_size,
                         size_t rel_count,
                         size_t dt_entry_count,
                         size_t hash_size = 0)
{
  Plan p;

  uint64_t syn_size_needed =
    align_up(interp_size, 8) +
    align_up(dynsym_count * sizeof(Elf32_Sym), 8) +
    align_up(dynstr_size, 8) +
    align_up(hash_size, 8) +
    align_up(rel_count * sizeof(Elf32_Rel), 8) +
    align_up(dt_entry_count * sizeof(Elf32_Dyn), 8) +
    kTrampolineSize;

  uint64_t hdrs_size = sizeof(Elf32_Ehdr) + kPhdrsMaxCount*sizeof(Elf32_Phdr);
  syn_size_needed += hdrs_size;
  syn_size_needed = align_up(syn_size_needed, kPageSize);

  if( image.image_base < syn_size_needed + kSynthMargin )
    p.synth_va = kSynthFallbackVa;
  else
    p.synth_va = (image.image_base - syn_size_needed - kPageSize) & ~(kPageSize-1);

  p.synth_foff = 0;

  // Upper-bound phdr count for header block sizing
  uint32_t n_pe_secs = (uint32_t)image.secmap.secs.size();
  uint32_t n_phdrs_max = 4 + n_pe_secs + 2 + 1;
  uint64_t hdr_file_end = align_up(sizeof(Elf32_Ehdr) + n_phdrs_max*sizeof(Elf32_Phdr), 8);

  uint64_t cur_va   = p.synth_va + hdr_file_end;
  uint64_t cur_foff = hdr_file_end;

  p.interp_va   = cur_va;
  p.interp_foff = cur_foff;
  cur_va   += align_up(interp_size, 8);
  cur_foff += align_up(interp_size, 8);

  p.dynsym_va   = cur_va;
  p.dynsym_foff = cur_foff;
  cur_va   += align_up(dynsym_count * sizeof(Elf32_Sym), 8);
  cur_foff += align_up(dynsym_count * sizeof(Elf32_Sym), 8);

  p.dynstr_va   = cur_va;
  p.dynstr_foff = cur_foff;
  cur_va   += align_up(dynstr_size, 8);
  cur_foff += align_up(dynstr_size, 8);

  p.hash_va   = cur_va;
  p.hash_foff = cur_foff;
  cur_va   += align_up(hash_size, 8);
  cur_foff += align_up(hash_size, 8);

  p.rel_va   = cur_va;
  p.rel_foff = cur_foff;
  cur_va   += align_up(rel_count * sizeof(Elf32_Rel), 8);
  cur_foff += align_up(rel_count * sizeof(Elf32_Rel), 8);

  p.dynamic_va   = cur_va;
  p.dynamic_foff = cur_foff;
  cur_va   += align_up(dt_entry_count * sizeof(Elf32_Dyn), 8);
  cur_foff += align_up(dt_entry_count * sizeof(Elf32_Dyn), 8);

  p.trampoline_va   = cur_va;
  p.trampoline_foff = cur_foff;
  cur_va   += kTrampolineSize;
  cur_foff += kTrampolineSize;

  p.synth_end_va = align_up(cur_va, kPageSize);

  // PE section file offsets (page-aligned)
  p.pe_data_foff = align_up(cur_foff, kPageSize);
  uint64_t sec_cur = p.pe_data_foff;
  for( auto &sec : image.secmap.secs ) {
    sec.elf_foff = sec_cur;
    sec_cur = align_up(sec_cur + sec.rawsz, kPageSize);
  }
  p.pe_hdr_foff = sec_cur;

  return p;
}
