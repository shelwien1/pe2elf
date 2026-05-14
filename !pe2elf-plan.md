# `pe2elf.cpp` — Consolidated Refactoring & Redesign Plan

This document integrates the seven independent reviews of `pe2elf.cpp`
into one plan. Every claim was cross-checked against the actual source;
items that didn't survive verification are listed in §3 with reasons.

Constraints honored throughout:

- Little-endian host is assumed (no byteswap layer needed).
- Diagnostics go to `stderr` via `fprintf`; no `<iostream>`.
- Source files stay flat — module separation by filename prefix only.
- No external test framework; no unit tests in the deliverable.

---

## 1. What the program does

`pe2elf.cpp` is a 1226-line single-file C++17 program that converts
PE32+ (Windows x64) executables into ELF64 (Linux x86-64) images that
can be run under `ld-linux-x86-64.so.2` with a companion
`winapi_shim.so`. The image is self-contained — only libc is needed.

The design is reasonable:

- a synthetic `PT_LOAD` placed below `ImageBase` holds `.interp`,
  `.dynsym`, `.dynstr`, `.rela.dyn`, `.dynamic`, and a small trampoline;
- IAT slots in the IAT-bearing section (usually `.rdata`) are zeroed,
  and `R_X86_64_64` entries in `.rela.dyn` ask `ld.so` to fill them at
  load time from `winapi_shim.so`;
- a 9-byte trampoline `sub rsp,8 ; jmp pe_entry` reconciles the SysV
  AMD64 vs MSVC stack-alignment mismatch;
- a `PT_LOAD` for the PE headers themselves at `ImageBase` keeps any
  MSVC-CRT data-directory walk happy;
- optional section headers are emitted for debuggability.

The *implementation* is a single ~600-line `Converter` struct with
roughly 30 members of intermediate layout state — that's where the real
problems live.

---

## 2. Verified defects

Ordered by severity. Line numbers are against the file as shipped.

### Correctness (real bugs)

**D1. `PT_PHDR.p_filesz` is wrong when phdrs are conditionally skipped.**
`build_phdrs` precomputes `n_phdrs_total = 4 + n_pe_secs + 2 + 1`
(line 789) and writes that into `PT_PHDR.p_filesz` / `p_memsz`
(line 799). The actual phdr count differs whenever:

- `--strip-pdata` skips a PE-section `PT_LOAD` (line 856), or
- no `.rdata` is identified, so the `PT_GNU_RELRO` block is omitted
  (line 885).

`ehdr.e_phnum = phdrs.size()` (line 1086) is correct, so the kernel
loads the right count, but `PT_PHDR.p_filesz` overstates the table.
Tools that consult `PT_PHDR` to locate the program header table (e.g.
to relocate `_DYNAMIC`) read past the valid entries.

*Fix:* build the phdr vector first, then write
`PT_PHDR.p_filesz = phdrs.size() * sizeof(Elf64_Phdr)` at the end.

**D2. PE-headers `PT_LOAD` can have `p_filesz > p_memsz`.**
Lines 922–923:

```cpp
p.p_filesz = oh->SizeOfHeaders;
p.p_memsz  = 0x1000;
```

`SizeOfHeaders` is usually ≤ 0x400, but the PE spec only requires it to
be a multiple of `FileAlignment`. With `FileAlignment = 0x1000` and a
generous number of data dirs / sections it can exceed one page.
`p_filesz > p_memsz` is illegal and rejected by the Linux kernel
loader.

*Fix:* `p.p_memsz = align_up(oh->SizeOfHeaders, 0x1000);`.

**D3. Bounds-unchecked read in `patch_rdata`.** Line 664:

```cpp
rdata_patched.assign(pe.data.data()+sec.raw,
                     pe.data.data()+sec.raw+raw_size);
```

If `sec.raw + sec.rawsz > pe.size()` (truncated or malformed PE), this
reads past the input buffer. The serialization path at line 1122 does
guard this case; `patch_rdata` runs earlier, unguarded.

*Fix:* clamp `raw_size` to `pe.size() - sec.raw` (handling
`sec.raw >= pe.size()` separately), zero-fill the remainder.

**D4. `dynamic_size_max = 12` is hand-synchronized with `build_dynamic`.**
`compute_layout` reserves `12 * sizeof(Elf64_Dyn)` (line 744);
`build_dynamic` happens to emit exactly 12 entries (lines 642–653).
Adding or removing one `dyn(...)` call silently corrupts the file
layout — the trampoline (and downstream offsets) drift into or out of
the reserved range.

*Fix:* call `build_dynamic` *before* layout, using only data-dependent
inputs (`dynstr` sizes etc.) — the entry **count** doesn't depend on
VAs even though the **values** do; you can fill values with placeholders,
count, reserve, then re-emit with real VAs. Alternatively, the cheapest
correct fix: introduce `static constexpr size_t DT_ENTRY_COUNT = 12;`,
use it in both places, and `assert(dynamic_data.size() == DT_ENTRY_COUNT)`.

**D5. `rdata_sec_idx` is decided by `imports[0]` only.** Line 531:

```cpp
rdata_sec_idx = secmap.section_of(imports[0].iat_rva);
```

Most MSVC binaries place all IAT slots in `.rdata`, but split layouts
(`.idata` + `.rdata`) do exist. Then:

- `patch_rdata` zeroes slots only in the chosen section; slots in the
  other section keep their original FirstThunk RVA bytes. `ld.so`
  writes the resolved address through the `R_X86_64_64` entry, but the
  pre-existing bytes can collide with adjacent data depending on the
  binary;
- `PT_GNU_RELRO` covers only the chosen section, leaving the other
  IAT-bearing section writable post-relocation.

*Fix:* collect the *set* of sections containing any IAT slot, patch
each of them, and emit one `PT_GNU_RELRO` per RELRO-eligible section.
For now an explicit error on split IAT layouts would be acceptable.

**D6. Import with `iat_rva == 0` creates a relocation at the PE header.**
A malformed import descriptor with `ImportAddressTableRVA == 0`
produces a `.rela.dyn` entry with `r_offset = image_base + 0`
(`build_synthetic_sections` line 597). `ld.so` then writes the resolved
address over the PE header, breaking any MSVC-CRT data-directory walk.

*Fix:* in `collect_imports`, skip (or reject) descriptors with zero
IAT RVA. Also validate that every individual IAT slot RVA resolves to a
mapped, writable section.

### Hardening (malformed / hostile input)

**D7. `NumberOfRvaAndSize` / `NumberOfSections` are trusted blindly.**
`parse_pe` (lines 452–457) reads `num_dd = oh->NumberOfRvaAndSize` and
loops `peh->NumberOfSections` times. A crafted PE with `NumberOfRvaAndSize
= 0xFFFFFFFF` overflows `dd_off + num_dd * sizeof(pe_data_directory)`;
the section-table base then wraps. `NumberOfSections = 0xFFFF` doesn't
overflow but produces megabytes of garbage section entries.

*Fix:* cap both at reasonable upper bounds (e.g. 96 data dirs, 96
sections), validate that the implied byte ranges fit in the file, fail
fast otherwise.

**D8. `collect_imports` outer loop has no upper bound.** Line 483
(`for (uint32_t idx = 0;; ++idx)`) terminates only on `pe.at()`
returning null or an all-zero descriptor. Pathological input can iterate
up to (file size / 20) descriptors.

*Fix:* derive the descriptor count from the IMPORT data-directory's
`Size` field, or cap at a constant (4096 descriptors is generous).

**D9. `NameRVA == 0` yields a runaway DLL-name string.**
`secmap.rva_to_offset(0)` returns 0; `pe.str(0)` then scans from the
DOS header for the next zero byte. In typical PEs this finds something
short, but a crafted file without an early zero byte returns a
multi-kilobyte garbage string that ends up in `.dynstr` and as a
`DT_NEEDED` entry.

*Fix:* require `NameRVA` to resolve to a non-zero offset inside a
mapped section; bound string reads with an explicit max length (256 is
plenty for a DLL name).

**D10. `rva_to_offset` uses `0` as both "not found" and "valid offset 0".**
Line 179 returns `0` on failure. File offset 0 (the DOS header) is
never a sensible RVA target, but the `if (!ilt_off) continue;` check at
line 496 still conflates the two states.

*Fix:* return `std::optional<uint32_t>` or use `UINT32_MAX` as the
sentinel; update both call sites.

**D11. Section-table offset derived from `NumberOfRvaAndSize`.**
`sec_off = dd_off + num_dd*sizeof(pe_data_directory)` (line 456) works
for conforming PEs but the COFF-spec-correct expression is
`opt_off + peh->SizeOfOptionalHeader`. Using the latter is robust
against PEs where `NumberOfRvaAndSize` and `SizeOfOptionalHeader`
disagree.

*Fix:* compute from `SizeOfOptionalHeader`, then validate (paired with
D7).

### Portability

**D12. `chmod(out_path, 0755)` is POSIX-only.** Line 1164. Build
failure on MinGW / native Windows. Trivial fix:

```cpp
#ifndef _WIN32
chmod(out_path, 0755);
#endif
```

### Lower-severity / robustness

**D13. Trampoline `rel32` not range-checked.** Line 621 truncates to
`int32_t` silently. In practice the trampoline lives within a few KB of
`image_base + ep_rva` so the gap is well under ±2 GiB, but a defensive
`int64_t d = jmp_target - jmp_instr_end; if (d != (int32_t)d) error;`
costs nothing and documents the precondition.

**D14. Redundant `sh_link` patch in `build_shdrs`.** Lines 969 and 976
assign the same value. Likely left over from an earlier `add(...)`
without a `link` parameter. Pick one site; remove the other.

**D15. Long PE section names (`/N` form) not resolved.** COFF supports
long section names via `/<offset>` referencing the string table at
`peh->PointerToSymbolTable + peh->NumberOfSymbols * 18`. The current
code copies the raw 8 bytes verbatim, so a long-named section appears
in the ELF as literally `/123`. Not a crash, just ugly and bad for
debugging.

**D16. Ordinal imports become `_ord<N>`.** Lines 506–510. The names
aren't DLL-qualified (collision risk across DLLs sharing ordinals), and
the shim almost certainly does not export `_ord<N>` symbols, so dynamic
linking fails at runtime. Three options, in order of effort:

- reject ordinal imports up front with a clear error;
- prefix the symbol name (`_ord_kernel32_15`) and document that the
  shim must export them;
- maintain an ordinal→name lookup (per DLL) and resolve at convert
  time.

**D17. `dynstr_shim_off` / `dynstr_rpath_off` declared mid-class.**
Lines 632–633 sit between two method bodies. Legal C++, but it obscures
the member layout. Move them to the member section near the top of the
struct.

**D18. `Buffer::str` is `O(n)` per call.** Correct (it does bound the
scan), but called many times during import enumeration. Low priority;
worth fixing only if profiling shows it.

**D19. Magic numbers scattered.** `0x1000`, `0x10000`, `0x200000`,
`0x20B`, `12`, `16`, `20` (the phdr-budget upper bound at line 688)
should become named `constexpr` constants. Same for the PE/ELF
characteristic flags.

---

## 3. Claims from the reviews that don't hold up

These came up across multiple reviews; recording them so they don't
get re-litigated:

**"`v & 0x7FFFFFFF` truncates valid Hint/Name RVAs above 2 GiB"** —
*incorrect*. Per the Microsoft PE/COFF spec (Import Lookup Table, 64-bit
form), bit 63 is the ordinal flag, bits 62–31 must be zero, and bits
30–0 hold the Hint/Name RVA (31 bits). `0x7FFFFFFF` is the correct
mask. The line could defensively check that bits 62–31 are indeed zero
and error out otherwise, but the mask itself is right.

**"`v & 0xFFFF` ordinal mask should be `v & 0x7FFFFFFFULL`"** —
*incorrect*. The PE spec specifies that only the low 16 bits encode the
ordinal number. `v & 0xFFFF` is correct.

**"`Buffer::str` returns a non-null-terminated pointer on missing
terminator"** — *incorrect*. The function returns `""` when no zero
byte is found within the buffer (line 51). The behavior is safe; the
only fair criticism is stylistic (returning `std::string_view` with an
explicit length would be cleaner).

**"`dynstr_shim_off` / `dynstr_rpath_off` are undeclared, the file
doesn't compile"** — *incorrect*. They are declared at lines 632–633.
The position is awkward (see D17) but the code compiles. Same answer
to the "`& &` / `st d::` / `Elf6 4_Sym` syntax errors" claim — those
were viewing artifacts in one reviewer's transcript, not bugs in the
file.

**"`build_shdrs` lambda body is truncated / fields uninitialized"** —
*incorrect*. The lambda at lines 953–966 is complete and initializes
every field it sets.

**"Endianness awareness missing"** — out of scope by constraint; LE
host is fine.

**"Strict aliasing UB from `reinterpret_cast<const T*>` on byte
arrays"** — *theoretically true* but, in practice, GCC/Clang/MSVC all
treat `reinterpret_cast` through `uint8_t*` as defined under their
documented relaxations of the strict-aliasing rule, and the structs are
`#pragma pack(1)` so alignment is also explicit. Worth a future
`memcpy`-into-aligned-locals pass if the project ever targets a stricter
compiler, but not a correctness issue today.

---

## 4. Proposed module layout

Flat directory, prefix-separated. Headers and sources side by side:

```
util.hpp                 // Buffer, OutBuf, align_up, diag::error/info
pe_types.hpp             // PE structs + constants (single #pragma pack region)
elf_types.hpp            // ELF structs + constants
pe_image.hpp / .cpp      // PeImage: parse, RVA map, import collection
elf_plan.hpp / .cpp      // Plan: pure VA/file-offset computation
elf_build.hpp / .cpp     // Synthetic content, trampoline, phdrs, shdrs
elf_write.hpp / .cpp     // Final serialization
main.cpp                 // CLI parsing, orchestration
```

`Plan` is the single shared data class — a POD describing every region's
VA, file offset, and size. Everything else flows through pure functions
that take a `const PeImage&`, a `const Config&`, and either return a
`Plan` or write bytes into an `OutBuf`. This kills the god-struct
without introducing parallel class hierarchies; the data flow is the
one already present in the current code, just unfolded.

Key shape changes:

- **`PeImage`** owns the input `Buffer`, the parsed headers (`dos`,
  `peh`, `oh`), the section map, and the imports vector. Const
  accessors only. No ELF knowledge.
- **`elf_plan::compute(const PeImage&, const Config&) -> Plan`** is a
  pure function. No buffer ownership, no I/O.
- **`elf_build`** produces in-memory content for `interp_data`,
  `dynsym_data`, etc., plus the phdr / shdr vectors, given a `Plan`
  and a `PeImage`.
- **`elf_write::write(plan, built, pe_image, out_path)`** emits the
  byte stream.
- **`main.cpp`** becomes load → parse → plan → build → write,
  roughly 30 lines.

`diag::error(fmt, ...)` and `diag::info(fmt, ...)` in `util.hpp` are
thin wrappers over `fprintf(stderr, ...)` / `fprintf(stdout, ...)` so
the `--verbose` flag can gate the chatty messages without touching the
call sites.

---

## 5. Staged refactoring

Each stage leaves the program working and produces output that's
byte-identical (or near-identical, modulo intentional fixes) to the
previous stage. `cmp` between stages is a useful sanity check.

**Stage 0 — preconditions.** A small smoke-test script that converts
one or two known PEs and `cmp`s the result against a golden file.
Stash the golden bytes. Add a "convert twice, `cmp` the two outputs"
determinism check.

**Stage 1 — extract pure data.** Move PE structs into `pe_types.hpp`,
ELF structs into `elf_types.hpp`. Move `Buffer`, `OutBuf`, `align_up`
into `util.hpp`. Add `static_assert(sizeof(Elf64_Ehdr) == 64)` etc. so
that `#pragma pack` breakage gets caught at compile time. No logic
change; byte-identical output.

**Stage 2 — split parsing from building.** Extract `parse_pe`,
`collect_imports`, `PESectionMap` into a `PeImage` class in
`pe_image.{hpp,cpp}`. Fix D7, D8, D9, D10, D11 here while the parsing
code is the focus.

**Stage 3 — introduce `Plan` and `elf_plan`.** Move `compute_layout`
into `elf_plan::compute(...) -> Plan`. Fix D4 (DT count constant +
assert, or build-dynamic-first).

**Stage 4 — extract `elf_build`.** Move `build_synthetic_sections`,
`build_trampoline`, `build_dynamic`, `build_phdrs`, `build_shdrs`,
`patch_rdata` into `elf_build.{hpp,cpp}`. Fix D1 (count `PT_PHDR` from
the final vector), D2 (`memsz ≥ filesz`), D3 (bounds-clamped
`patch_rdata`), D5 (multi-section IAT / RELRO), D6 (validate `iat_rva
!= 0`), D13 (`rel32` range check), D14 (drop the dead patch).

**Stage 5 — extract `elf_write`.** Move the serialization tail of
`convert()` into `elf_write::write(...)`. Wrap `chmod` (D12).

**Stage 6 — polish.** Replace C casts with `static_cast` /
`reinterpret_cast` where it clarifies. Const-correct the `PeImage`
accessors. Promote magic numbers to named `constexpr` (D19). Move the
stray member declarations (D17). Resolve long section names (D15).

---

## 6. Proposed improvements

### Robustness

- **Validate `SectionAlignment ≥ 0x1000`** in `parse_pe` — the entire
  layout assumes page granularity.
- **Reject TLS-using binaries** until a TLS path is implemented;
  `__declspec(thread)` data otherwise breaks silently.
- **Reject ASLR-required images** (`IMAGE_FILE_RELOCS_STRIPPED == 0` and
  a populated `.reloc` directory) unless `.reloc` is honored — see
  features below. The current converter quietly assumes the binary loads
  at its preferred `ImageBase`.

### Features

- **`.reloc` application** (data dir 5): walk the base-relocation
  directory and, optionally with `--rebase <addr>`, fix up the image at
  convert time. Removes the implicit "PE must load at its preferred
  base" precondition.
- **Delayed imports** (data dir 13): handle the same way as ordinary
  imports.
- **TLS** (data dir 9): emit `PT_TLS` from the PE TLS directory; the
  shim handles `_tls_index` / `_tls_array`.
- **`.pdata` → `.eh_frame`** (data dir 3): optional translation so
  backtraces and `_Unwind_*` work, instead of the current
  `--strip-pdata` workaround.
- **Per-DLL `DT_NEEDED`**: instead of forcing everything into a single
  `winapi_shim.so`, group imports by source DLL and emit one
  `DT_NEEDED` per shim (`kernel32_shim.so`, `user32_shim.so`, …).
- **Symbol manifest**: emit a sidecar `.txt` listing every
  `(dll, symbol)` pair, so the shim build can be regenerated
  mechanically.

### Quality-of-life

- `--verbose` to gate per-section / per-import logging behind a flag;
  default should be a single summary line.
- `--dry-run` to print the computed `Plan` and exit without writing.
- `--base <addr>` to override `ImageBase` (paired with `.reloc`
  handling).
- `--version` embedding the git SHA at build time.
- Diagnostics include file offsets:
  `"Bad PE signature at 0x%zx"` not `"Bad PE signature"`.

### Build

- A `CMakeLists.txt` with `-Wall -Wextra -Wpedantic -Werror`, plus a
  `Debug` config that turns on `-fsanitize=address,undefined`. D3 and
  D7–D9 trip ASan immediately on bad input, which makes the fixes easy
  to verify by hand against a corpus of malformed PEs.

---

## 7. Suggested priority order

If the work happens incrementally rather than as one refactor:

1. D2 (`PT_LOAD` `p_filesz > p_memsz` — kernel-rejecting).
2. D1 (`PT_PHDR.p_filesz` lies).
3. D6 (zero-IAT relocation overwrites PE header).
4. D5 (split-IAT layout — error out at minimum).
5. D3, D7, D8, D9 (bounds and validation cluster).
6. D4 (DT-entry-count constant).
7. D12 (`chmod` portability).
8. Module split (Stages 1–5 above).
9. D13–D19 (polish, robustness, feature gaps).
10. `.reloc` and TLS support, once the converter is restructured
    enough to absorb new passes cleanly.

---

## 8. Open questions

> Answers quoted below.

- Are ordinal imports actually used by the targeted binaries, or are
  they all named? Drives effort on D16.
> They are normally all names. But PE ordinal parsing is still necessary, for now can exit with error when asked to convert PE with ordinal imports.

- One-shot binary, or library that other tooling links against? The
  proposed layout supports either; only the public-API shape changes.
> No libraries and no need for separately compiled modules at all - different source files are useful for navigation, but for compiling they should be #include'd into one source file.
> Btw, define all methods in classes, .h/.cpp duplication of class structure is redundant and hard to edit.

- Is "always load at preferred `ImageBase`" acceptable, or is full
  ASLR-capable PE handling required? This single decision drives
  whether `.reloc` work is mandatory.
> It's acceptable and preferable, not but always possible. Yes, relocation support is necessary, at least for basic types used on x64.

- Is `winapi_shim.so` expected to evolve alongside the converter
  (versioned together), or be a stable external dependency? Affects
  whether the converter should emit a shim manifest.
> Of course it would have to evolve, and we'd add some version check (via some getversion function though, not manifest), but it's low priority, ignore it for now.

- Should the multi-shim split (one `*_shim.so` per source DLL) be the
  default, or stay opt-in behind a flag?
> It's more convenient to use one .so, but it makes sense to add support for multiple libraries. Would need dllname prefixes for names in shim.cpp to avoid collisions, and maybe pe2elf could load winapi_shim.so itself to check which imports it has. Get pe2elf to accept one or more .so files on commandline to link with?








