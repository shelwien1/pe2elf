# pe2elf32 — Plan for a PE32/i386 → ELF32 Converter and 32-bit Shim

Status: design document. Nothing here is implemented yet.

Goal: build a **from-scratch** `pe2elf32` converter and a companion
`winapi_shim32.so`, mirroring every feature of the existing 64-bit
`pe2elf` / `winapi_shim.so` pipeline but targeting **32-bit PE (PE32,
`IMAGE_FILE_MACHINE_I386`) → 32-bit ELF (ELFCLASS32, `EM_386`)** running
natively under `/lib/ld-linux.so.2`.

We are **not** adding PE32 support to the existing `pe2elf`. The 64-bit
tool bakes 8-byte pointers, `RELA`, `IMAGE_REL_BASED_DIR64`, `ms_abi`,
GS-based TEB, and table-based (`.pdata`) SEH into every layer. A 32-bit
mode would be `#ifdef` noise in files that are currently clean. The
cleaner path is a parallel tree that shares the *architecture* but not the
*code*, so both stay readable. This document is the blueprint for that
tree.

---

## 0. TL;DR — what actually changes

The **pipeline shape is identical** (parse PE → plan layout → build
synthetic ELF wrapper → zero the IAT and cover it with relocations → write
ELF; the shim fills the IAT at load time and translates WinAPI → POSIX).
Only the width- and ABI-specific details change. In rough order of effort:

| Rank | Area | Why it's hard on 32-bit |
|---|---|---|
| 1 | **SEH** | x86 SEH is the FS:[0] stack chain, a *completely different mechanism* from x64's `.pdata` tables. The current shim stubs x64 SEH; a real x86 dispatcher is a new component. |
| 2 | **Calling conventions** | One `ms_abi` becomes **three**: `stdcall` (WinAPI), `cdecl` (CRT + variadics), `thiscall` (COM vtables). Variadic functions *must* be cdecl. |
| 3 | **TEB via FS segment** | x64 sets GS base with one `arch_prctl`. x86 must build a GDT descriptor with `set_thread_area` and load `%fs`, per thread. All TEB/PEB offsets differ. |
| 4 | **Trampoline** | No RIP-relative addressing on i386. The startup thunk needs a get-PC (`call/pop`) construction for the PIE/`--so` path. |
| 5 | **REL vs RELA** | i386 uses `Elf32_Rel` with **in-place addends**, not `Elf32_Rela`. Base relocs need no explicit addend and no zeroing. |
| 6 | **Struct widths** | STARTUPINFO, `_iobuf` (32 not 48 bytes), EXCEPTION_RECORD, CONTEXT, `jmp_buf`, RTL_USER_PROCESS_PARAMETERS, PEB_LDR_DATA all re-laid-out. |
| 7 | **Build** | `-m32` everywhere for the shim; `-D_FILE_OFFSET_BITS=64` becomes load-bearing (not cosmetic); 32-bit side-DLLs for ordinal resolution. |

Two facts verified in this environment while writing this plan:

* On **i386 ELF**, `__attribute__((stdcall))` does **not** decorate
  symbols — `kernel32_GetLastError` stays `kernel32_GetLastError`, no
  `@N` suffix. So the converter's existing `dll_Func` → `kernel32_Func`
  symbol-naming scheme carries over unchanged. (This is a PE/COFF-only
  decoration; ELF i386 never applies it.)
* This box has 32-bit **codegen** (`g++ -m32` compiles bare code) but is
  **missing the 32-bit dev headers/libs** (`bits/wordsize.h`,
  `bits/c++config.h` absent). Building the shim (which includes system
  headers) needs `gcc-multilib g++-multilib libc6-dev-i386` installed
  first. See §7.

---

## 1. Converter: `pe2elf32`

The converter is a **host tool** — it parses a 32-bit PE and emits ELF32
bytes. It does **not** itself need to be a 32-bit binary; build it native
like today's `pe2elf`. Everything below is a new file paralleling the
existing one.

### 1.1 `pe_types32.hpp` (from `pe_types.hpp`)

The DOS header and `pe_header` (COFF file header) are width-independent —
reuse verbatim. What changes:

* **`pe32_optional_header`** replaces `pe64_optional_header`:
  * `Magic == 0x10B` (PE32) not `0x20B` (PE32+).
  * `ImageBase` is **`uint32_t`** (default `0x400000`), not `uint64_t`.
  * Adds a **`BaseOfData` `uint32_t`** field right after `BaseOfCode`
    (PE32+ dropped it). This shifts every subsequent field by 4 bytes.
  * `SizeOfStackReserve/Commit`, `SizeOfHeapReserve/Commit` are
    **`uint32_t`** not `uint64_t`.
  * The data directory array still starts at `opt_off + 96` for PE32
    (the existing `OrdinalResolver` already hard-codes this offset for
    the PE32 branch — see `pe_image.hpp:113-119` — proof the layout is
    understood).
* **Machine check**: accept `Machine == 0x14C` (`IMAGE_FILE_MACHINE_I386`),
  reject others. (64-bit tool checks `0x8664`.)
* **`pe_tls32`** replaces `pe_tls64`: `StartAddressOfRawData`,
  `EndAddressOfRawData`, `AddressOfIndex`, `AddressOfCallBacks` are all
  **`uint32_t`** (32-bit VAs), then `SizeOfZeroFill` + `Characteristics`
  as `uint32_t`. Total 24 bytes vs 40.
* **Base reloc type constant**: the relevant fixup is
  `IMAGE_REL_BASED_HIGHLOW == 3` (a 32-bit fixup) instead of
  `IMAGE_REL_BASED_DIR64 == 10`. `pe_base_reloc` (block header) is
  unchanged.
* Data-directory indices and section characteristics are identical.

### 1.2 `elf_types32.hpp` (from `elf_types.hpp`)

Swap every `Elf64_*` for `Elf32_*`. Non-obvious differences:

* **`Elf32_Sym` field order differs from `Elf64_Sym`**:
  `st_name(4) st_value(4) st_size(4) st_info(1) st_other(1) st_shndx(2)`.
  (On 64-bit `st_info`/`st_other`/`st_shndx` come *before* `st_value`.)
  Get this wrong and every symbol is garbage.
* **REL, not RELA.** The i386 psABI uses `Elf32_Rel`
  (`r_offset(4) r_info(4)`) with the **addend stored in-place** at the
  target. There is no `r_addend` field. This ripples through the whole
  builder (§1.5) and the dynamic section (`DT_REL`/`DT_RELSZ`/`DT_RELENT`
  instead of `DT_RELA*`).
* **`ELF32_R_INFO(s,t) = (s<<8) | (t&0xff)`** — 24-bit symbol index,
  8-bit type (vs `<<32` on 64-bit).
* Machine/constants: `EM_386 = 3`, `e_ident[EI_CLASS] = ELFCLASS32 (1)`.
  Relocation types: **`R_386_32 = 1`** (absolute, S+A) and
  **`R_386_RELATIVE = 8`** (B+A). (`R_386_JMP_SLOT`/`GLOB_DAT` not
  needed — we don't build a PLT/GOT.)
* Header/entry sizes shrink: `Elf32_Ehdr` 52, `Elf32_Phdr` 32,
  `Elf32_Shdr` 40, `Elf32_Sym` 16, `Elf32_Rel` 8, `Elf32_Dyn` 8. Update
  every `sizeof` and `static_assert`.
* `DT_*` tags are identical values; use `DT_REL(17)`, `DT_RELSZ(18)`,
  `DT_RELENT(19)` in place of the RELA trio.

### 1.3 `pe_image32.hpp` (from `pe_image.hpp`)

`PeImage` parsing logic is structurally the same; the deltas:

* Parse the **PE32 optional header**; store `image_base` as a 32-bit
  value widened to `uint64_t` internally (keeps arithmetic simple).
* **`collect_imports`**: IAT/ILT entries are **4 bytes**. The
  ordinal-vs-name flag is **bit 31 (`0x80000000`)**, ordinal in the low
  16 bits; named entries point at a hint/name via the low 31 bits. Slot
  stride is 4. Everything else (split-IAT detection, `rdata_sec_idx`) is
  unchanged.
* **`collect_relocs`**: walk the same block structure but accept
  **type 3 (HIGHLOW)** and read/keep a **32-bit** value at the site.
  Because i386 relocations are REL with in-place addends (§1.5), the
  `BaseRelocEntry` only needs the site VA — the "addend" is already the
  32-bit preferred pointer sitting at that address; we don't copy it out.
* **`collect_tls`**: read `pe_tls32`; fields are 32-bit.
* **`rebase`**: patch **4-byte** values in place (`delta` added to a
  `uint32_t` at each HIGHLOW site).
* **`OrdinalResolver`**: already dual-mode (handles `0x10B`), so the code
  is reusable as-is. The catch is *data*: x86 DLLs export different
  ordinals than x64 DLLs, so the files under the side-DLL directory must
  be the **32-bit** builds. Use a separate **`dll32/`** directory so the
  two toolchains don't clobber each other (§7).

### 1.4 `elf_plan32.hpp` (from `elf_plan.hpp`)

Mostly arithmetic width changes:

* Synthetic-segment sizing uses `Elf32_*` sizes; `Elf32_Rel` (8 bytes)
  where `Elf32_Rela` would be 12.
* Page size stays `0x1000`. Default `ImageBase` `0x400000` leaves ample
  room below for the synthetic segment; the `kSynthFallbackVa` (currently
  `0x200000`) is still valid and comfortably above `mmap_min_addr`
  (`0x10000`).
* `kTrampolineSize` grows (the i386 PIC trampoline is longer — §1.5);
  budget ~48 bytes and pad.

### 1.5 `elf_build32.hpp` (from `elf_build.hpp`) — the load-bearing changes

**Relocations (REL, in-place addends).** This is the single most
important converter change and it actually *simplifies* two paths:

* **IAT slots** → `R_386_32` against the shim symbol. We still zero each
  slot (so the in-place addend `A = 0`) and the loader writes `S + 0 = S`
  = the shim function address. Same net effect as the 64-bit `R_X86_64_64`
  path.
* **Base relocations (`--pie`/`--so`)** → `R_386_RELATIVE`. Here the i386
  REL convention pays off: the loader computes `*site += load_bias`, and
  the site already holds the **absolute preferred VA** (we leave the PE
  bytes untouched). So — unlike the 64-bit path, which carries an explicit
  `r_addend` — we emit *only* the `r_offset`, store **no** addend, and do
  **not** zero the site. `load_bias = actual_load_addr − lowest_p_vaddr`,
  and since our `p_vaddr`s equal the preferred VAs, `preferred + bias` is
  the correct runtime address.
* Consequence: the `Elf32_Rel` writer takes the addend from memory, so
  the builder never stores a separate addend vector for RELATIVE entries.
  The IAT `R_386_32` entries rely on the zeroed slot for `A = 0`.

**Dynamic section.** Replace `DT_RELA/DT_RELASZ/DT_RELAENT` with
`DT_REL(0x11)/DT_RELSZ(0x12)/DT_RELENT(0x13)`. `DT_RELENT =
sizeof(Elf32_Rel) = 8`. Keep `DT_NEEDED`, `DT_RUNPATH=$ORIGIN`,
`DT_STRTAB/STRSZ/SYMTAB/SYMENT`, `DT_HASH` (for `--so`), `DT_DEBUG`,
`DT_FLAGS_1=DF_1_NOW`, `DT_NULL`. `DT_SYMENT = sizeof(Elf32_Sym) = 16`.

**The startup trampoline** — no RIP-relative addressing on i386, so the
64-bit `lea rdi,[rip+..]; call [rip+..]` construction is impossible. Two
variants:

* **Keep the exported name `shim_register_tls`** (no `32` suffix). The
  32-bit shim is a separate `.so` with its own symbol namespace, so there
  is no collision with the 64-bit build — only the *soname* differs. This
  also keeps the converter's UND symbol name identical between the two
  trees. Declare it **`__stdcall`** (one pointer arg) so the callee pops
  the argument and the trampoline needs no `add esp,4`.

* **ET_EXEC (default, non-PIE)** — addresses are fixed at link time, so
  use absolute forms:

  ```
        and  esp, -16     ; esp ≡ 0 (mod 16)
        push imm32        ; &ShimTlsInfo (absolute VA, known at build time)
        call [imm32]      ; [slot]; stdcall callee pops the arg → esp ≡ 0
        push eax          ; dummy return address     → esp ≡ 12 (mod 16)
        jmp  rel32        ; → PE entry, entered as if by CALL
  slot: .long 0           ; R_386_32 → shim_register_tls
  info: ShimTlsInfo       ; 6 × uint32 = 24 bytes
  ```
  `call [disp32]` (`FF 15 <abs32>`) reads the slot the loader populated.
  The immediates need no relocation because ET_EXEC loads at its link
  address.

* **PIE / `--so`** — immediates would need runtime fixups, so use a
  get-PC thunk to anchor addressing on the real load address:

  ```
        call 0f           ; pushes address of label 0
    0:  pop  ecx          ; ecx = runtime VA of label 0
        and  esp, -16     ; esp ≡ 0 (mod 16)
        lea  eax, [ecx + (info-0b)]
        push eax          ; &ShimTlsInfo, load-relative
        call [ecx + (slot-0b)]  ; stdcall callee pops the arg → esp ≡ 0
        push eax          ; dummy return address     → esp ≡ 12 (mod 16)
        jmp  rel32        ; → PE entry
  slot: .long 0           ; R_386_32 → shim_register_tls
  info: ShimTlsInfo       ; 6 × uint32
  ```
  The final `jmp rel32` needs **no relocation even under PIE**: the
  trampoline and the PE code shift by the same load bias, so their
  relative displacement is a link-time constant. (`ecx` and `eax` are
  caller-saved under both stdcall and cdecl, so clobbering them is safe.)

  The slot is `R_386_32` (loader writes the absolute resolved address).
  The three **VA fields inside `ShimTlsInfo`** (`template_va`,
  `index_va`, `callbacks_va`) are absolute preferred VAs and must be
  fixed up under PIE, exactly as the 64-bit `--so` path does — emit an
  `R_386_RELATIVE` for each (in-place addend = the preferred VA already
  written there). `finalize_tls_call` patches all the `r_offset`s once
  `trampoline_va` is known, same as today.

  **Note `ShimTlsInfo` is now 6 × `uint32` = 24 bytes** (not 48), and the
  field offsets the shim reads change accordingly (§2.4).

**Stack alignment — what the `push eax` is for.** On Windows the PE entry
point is reached via a `CALL` (from `BaseThreadInitThunk`), so it expects
a return address on top of the stack. The dummy `push` reproduces that
frame shape, and combined with the preceding `and esp,-16` it leaves
`esp ≡ 12 (mod 16)` — exactly what a function entered by `CALL` from a
16-byte-aligned call site sees. This mirrors the 64-bit trampoline's
`push rax` (which lands on `rsp ≡ 8 (mod 16)`, the x64 equivalent).

Note the alignment requirement is **weaker** on x86 than on x64: the
Win32 ABI mandates only 4-byte stack alignment, and MSVC realigns its own
frames (`and esp,-16` in the prologue) when a function needs SSE-aligned
locals. So this is about matching the expected frame shape and being
maximally compatible, not about satisfying a hard ABI rule. Verify the
resulting alignment against a real CRT-linked binary rather than assuming.

**Caveat (`--so`)**: `and esp,-16` discards the caller's stack frame, so
`_entrypoint` can never return normally to `load32`. This is already true
of the 64-bit `--so` path and is harmless in practice — the PE entry
terminates via `ExitProcess` rather than returning.

**`find_safe_entry` (`--so`)** — scan executable sections for a `0xC3`
(RET) byte. Byte value is architecture-independent; reuse as-is.

**Phdrs/Shdrs** — same set (`PT_PHDR/INTERP/LOAD×N/DYNAMIC/GNU_RELRO/
GNU_STACK`, plus the header-preserving `PT_LOAD` at `ImageBase`). Section
names identical. Only the entry *sizes* change. `.rela.dyn` becomes
`.rel.dyn` (`SHT_REL(9)` not `SHT_RELA(4)`, `sh_entsize = 8`).

### 1.6 `elf_write32.hpp` (from `elf_write.hpp`)

* `e_ident[EI_CLASS] = ELFCLASS32`, `e_machine = EM_386`.
* Serialize `Elf32_Ehdr`/`Phdr`/`Shdr`/`Sym`/`Rel`/`Dyn`.
* `e_type = ET_EXEC` by default, `ET_DYN` for `--pie`/`--so`. `e_entry`,
  `e_phoff`, sizing fields all 32-bit. Everything else (padding, section
  emission, `chmod 0755`) is unchanged.

### 1.7 `pe2elf32.cpp` (from `pe2elf.cpp`)

* Default `--interp` = **`/lib/ld-linux.so.2`** (the 32-bit dynamic
  linker; on some distros `/lib/i386-linux-gnu/ld-linux.so.2` — expose it
  as a flag, default to the LSB path).
* Default `--shim-soname` = **`winapi_shim32.so`**; `--dbg` →
  `winapi_shim32_dbg.so`.
* CLI flags identical: `--interp --shim-soname --dbg --inject=
  --strip-pdata --no-shdr --pie --so --base=`. Keep `--strip-pdata`
  accepted for CLI parity, but expect it never to match: `.pdata` is an
  x64/IA64/ARM unwind-table section that 32-bit x86 PEs do not carry.
* Orchestration (`parse → collect_imports → collect_relocs → rebase? →
  collect_tls → build → plan → finalize → write`) is line-for-line the
  same call sequence.

---

## 2. Shim: `winapi_shim32.so`

This is the bulk of the work. The shim keeps its one-TU design
(`shim32.cpp` + `shim32_*.hpp` per-feature headers + `shim32_types.h` +
`shim32.map`). The WinAPI *logic* is almost entirely reusable — POSIX
translation is width-independent. What changes is the **ABI boundary** and
the **low-level machinery** (TEB, SEH, TLS access, varargs, structure
layouts).

### 2.1 Calling conventions — `WINAPI`, `CDECL`, `THISCALL`

The x64 shim defines exactly one macro: `#define WINAPI
__attribute__((ms_abi))` and applies it to *everything*. On x86 that
collapses three distinct conventions into a bug. Define:

```c
#define WINAPI   __attribute__((stdcall))   // kernel32/user32/advapi32/shell32/...
#define CDECLAPI __attribute__((cdecl))     // msvcrt CRT entry points
#define THISCALL __attribute__((thiscall))  // COM vtable methods (IMalloc, ...)
```

Rules:

* **Almost all Win32 API** functions are `__stdcall` (callee pops args).
  The `EXPORT` macro becomes `visibility("default") + stdcall`.
* **Variadic functions cannot be stdcall** (the callee can't know how many
  bytes to pop). Every `...` function — `msvcrt_printf`, `_sprintf`,
  `fprintf`, `scanf`, `sscanf`, and the user32 `wsprintfA/W` /
  `wvsprintf` — **must be `cdecl`**. On x64 these were `ms_abi` and
  "worked" only because x64 has one convention; on x86 getting this wrong
  corrupts the stack on the first printf.
* **COM vtable methods are `__thiscall`** (`this` in `ECX`, remaining args
  on stack, callee cleans). The `g_imalloc_vtable` methods in
  `shim_shell32.hpp` (`imalloc_Alloc/Realloc/Free/...`) must be
  `thiscall`, and the vtable slot stride is **4 bytes** not 8.
* **Symbol names are unaffected.** Empirically checked for `stdcall` and
  `cdecl` on this host (both emit bare `kernel32_GetLastError` /
  `msvcrt_printf`); `thiscall` follows the same rule, since `@N`
  decoration is a PE/COFF convention that i386 ELF never applies. So the
  `kernel32_*` / `msvcrt_*` / `user32_*` names — and thus the version
  script and the converter's symbol mapping — are unchanged.

Because `EXPORT` (`shim.cpp:45`) is `visibility("default") + WINAPI`,
flipping the one `WINAPI` macro re-colors the entire export surface at
once. But the **callback function-pointer typedefs** must each pick their
convention individually — they are *not* covered by the macro flip:

| Typedef | File:line | x86 convention |
|---|---|---|
| `win_thread_fn` (LPTHREAD_START_ROUTINE) | `shim_kernel32_sync.hpp:329` | stdcall |
| `beginthreadex_fn` | `shim_msvcrt.hpp:576` | stdcall |
| `tls_callback_fn` (PIMAGE_TLS_CALLBACK) | `shim.cpp:1132` | stdcall |
| `unhandled_filter_t` (TLEF) | `shim_kernel32_except.hpp:12` | stdcall |
| `vectored_handler_t` (VEH) | `shim_kernel32_veh.hpp:10` | stdcall |
| `fls_callback_t` | `shim_kernel32_fls.hpp:20` | stdcall |
| `PHANDLER_ROUTINE` (console ctrl) | `shim_kernel32_tail.hpp:237` | stdcall |
| `crt_fn_t` (`_initterm` table) | `shim_msvcrt.hpp:164` | **cdecl** (CRT initializers) |
| `win_sighandler_t` (CRT signal) | `shim_msvcrt.hpp:227` | **cdecl** |
| `ms_cmp_fn` (qsort comparator) | `shim_msvcrt.hpp:473` | **cdecl** |
| IMalloc vtable methods ×9 | `shim_shell32.hpp:19-29` | **thiscall** |

### 2.2 Variadic formatting — use the native i386 `va_list`

The x64 shim hand-rolls `ms_vformat` over a `char*` "MS ABI va_list"
advanced **8 bytes per argument** (`MSVA_ARG_*` in `shim_msvcrt.hpp:20-23`),
because the MS x64 va_list differs from the SysV x64 va_list. **On i386
there is only one va_list**, so this entire mechanism collapses:

* Declare the variadic shims `cdecl` and use standard `va_start` /
  `va_arg` / `va_end`. Keep the existing format-spec *parser* (it handles
  `%S` wide strings, `%I64`, `%ls`, width/precision `*`), but feed it
  `va_arg(ap, T)` instead of the 8-byte-stride pointer bumps.
* i386 stack-arg promotion: `int`/pointer/`long` = 4 bytes, `long long`/
  `double` = 8 bytes. `va_arg` handles this natively — no manual stride.
* This is a net **simplification**: `MSVA_ARG_LL/ULL/DBL/PTR` and the
  `__builtin_ms_va_*` calls all disappear.

### 2.3 TEB/PEB via the `%fs` segment

x64: the shim points `%gs` base at `fake_teb` with a single
`arch_prctl(ARCH_SET_GS, fake_teb)` and reads TEB fields via `%gs:off`.
x86 needs a different mechanism *and* a different offset map.

**Segment setup.** On Linux i386, glibc uses `%gs` for its own TLS, so
`%fs` is free — and Windows x86 code reads the TEB through `%fs` anyway.
Per thread:

1. Build a `struct user_desc` with `base_addr = (unsigned)fake_teb`,
   `limit = 0xfffff`, `seg_32bit = 1`, `limit_in_pages = 1`,
   `contents = 0` (data), `read_exec_only = 0`, `useable = 1`,
   `entry_number = -1` (let the kernel allocate a free GDT TLS slot).
2. `syscall(SYS_set_thread_area, &desc)` → fills `desc.entry_number`.
3. Load `%fs` with selector `(entry_number << 3) | 3` (GDT, RPL 3):
   `asm volatile("movw %0, %%fs" :: "r"((uint16_t)sel))`.

The kernel reloads `%fs` from this per-thread TLS entry on every context
switch, so it survives scheduling. Each new thread (main + every
`CreateThread`/`pthread_create`) must repeat this in `shim_thread_attach`
with its **own** `fake_teb` (the per-thread `__thread` block, as today).

(`modify_ldt` with an LDT selector `TI=1` is a fallback if a
`set_thread_area` slot can't be had, but `set_thread_area` is the clean
path.)

**Win32 TEB offsets (32-bit)** — the fake TEB must be laid out with the
x86 offsets, which differ from the x64 ones the current code uses:

| Field | x86 off | x64 off (current) |
|---|---|---|
| `ExceptionList` (SEH chain head) | **`+0x00`** | n/a (x64 is table-based) |
| `StackBase` | `+0x04` | `+0x08` |
| `StackLimit` | `+0x08` | `+0x10` |
| `Self` (TEB linear addr) | `+0x18` | `+0x30` |
| `ClientId.ProcessId` | `+0x20` | `+0x40` |
| `ClientId.ThreadId` | `+0x24` | `+0x48` |
| `ThreadLocalStoragePointer` | `+0x2C` | `+0x58` |
| `ProcessEnvironmentBlock` (PEB) | `+0x30` | `+0x60` |
| `LastErrorValue` | `+0x34` | `+0x68` |
| `TlsSlots[64]` | `+0xE10` | `+0x1480` |
| `TlsExpansionSlots` | `+0xF94` | `+0x1780` |

So `SET_LAST_ERROR` mirrors to `fake_teb+0x34` (not `+0x68`), the TLS
slot pointer lives at `+0x2C`, and `shim_init_teb` writes the self-pointer
at `+0x18`. The `fake_teb` size can stay `0x1000`+ but must extend past
`0xE10` if any binary uses the inline `TlsSlots` array directly (keep
`0x2000` to cover `TlsExpansionSlots` reads too, matching today).

**Win32 PEB offsets (32-bit)**:

| Field | x86 off | x64 off (current) |
|---|---|---|
| `BeingDebugged` | `+0x02` | `+0x02` |
| `ImageBaseAddress` | `+0x08` | `+0x10` |
| `Ldr` (PEB_LDR_DATA*) | `+0x0C` | `+0x18` |
| `ProcessParameters` | `+0x10` | `+0x20` |
| `ProcessHeap` | `+0x18` | `+0x30` |

**PEB_LDR_DATA (32-bit)**: `Length@0x00`, `Initialized@0x04`,
`InLoadOrderModuleList@0x0C`, `InMemoryOrderModuleList@0x14`,
`InInitializationOrderModuleList@0x1C` (each `LIST_ENTRY` is **8 bytes**,
not 16). Self-referencing empty lists as today, at the new offsets.

**RTL_USER_PROCESS_PARAMETERS (32-bit)**: `MaximumLength@0x00`,
`Length@0x04`, `Flags@0x08`, `ConsoleHandle@0x10`, `StandardInput@0x18`,
`StandardOutput@0x1C`, `StandardError@0x20`, `CurrentDirectory@0x24`,
`DllPath@0x30`, `ImagePathName@0x38`, `CommandLine@0x40`,
`Environment@0x48`. Each `UNICODE_STRING` is **8 bytes** (`Length` WORD,
`MaximumLength` WORD, `Buffer` 4-byte pointer at `+0x04`).

`init_fake_peb` and `shim_init_teb` are effectively rewritten around these
tables. The rest of those functions (stdio handles, empty wide strings,
`pthread_getattr_np` stack bounds) is logic-preserving.

**`tls_get_slots`** inline asm changes from `movq %%gs:0x58,%0` to
`movl %%fs:0x2C,%0`.

### 2.4 PE TLS directory — `shim_register_tls`

* Declare it **`__stdcall`** (one arg) to match the trampoline, and keep
  the name unsuffixed (§1.5).
* `ShimTlsInfo` is **6 × `uint32`** (24 bytes). The field reads
  (`template_va`, `template_sz`, `zero_fill`, `align_chars`, `index_va`,
  `callbacks_va`) become 4-byte loads; `finalize_tls_call` uses offsets
  `0,4,8,12,16,20` and relocates fields 0/4/5 (template/index/callbacks)
  under `--so`.
* `tls_callback_fn` typedef becomes `__stdcall` (`void __stdcall(void*,
  uint32_t, void*)`).
* The 64-slot allocator bitmask (`uint64_t g_tls_alloc_used`, `1ULL<<i`)
  needs **no change**. It is read-modify-written with plain `|=`/`&=`
  under `g_tls_alloc_mu` (`shim.cpp:1112-1120`,
  `shim_kernel32_critsec.hpp:52-83`, `shim_kernel32_fls.hpp:52-90`), not
  with atomics, so on i386 GCC simply emits two 32-bit operations. No
  libatomic dependency (see §7).

### 2.5 SEH — the hard part (x86 FS:[0] chain dispatcher)

This is where x86 diverges most from the current shim. x64 SEH is
table-driven: the current `shim_kernel32_except.hpp` stubs
`RtlLookupFunctionEntry`/`RtlVirtualUnwind`/`RtlUnwindEx` (all return
NULL / log-and-return) because a real table walk was out of scope. **x86
SEH is chain-driven and genuinely implementable**, which is both an
opportunity and an obligation (real 32-bit binaries with `__try/__except`
depend on it).

How x86 SEH works, and what the shim must provide:

* **Registration is free.** MSVC `__try` inlines
  `push handler; push fs:[0]; mov fs:[0], esp`, building an
  `EXCEPTION_REGISTRATION_RECORD { prev; handler }` on the stack and
  linking it at `TEB.ExceptionList (fs:[0])`. Because our fake TEB
  provides a writable `fs:[0]`, this needs **zero shim support** — the PE
  code manages the chain itself. `__try/__except` blocks that never fault
  already work once the TEB is valid.
* **Dispatch on hardware fault is the shim's job.** When a CPU exception
  fires, Windows' `KiUserExceptionDispatcher` walks the `fs:[0]` chain
  calling each `handler(EXCEPTION_RECORD*, EstablisherFrame, CONTEXT*,
  DispatcherContext)` (a **`cdecl`** function returning
  `EXCEPTION_DISPOSITION`). We must replicate this **from our POSIX signal
  handler**:
  1. `crash_handler` (SIGSEGV/SIGILL/SIGFPE/SIGBUS) builds an
     `EXCEPTION_RECORD` (i386 layout) from `siginfo_t` and a `CONTEXT`
     (i386 layout) from the `ucontext_t` `gregs`.
  2. Walk `TEB.ExceptionList`; for each record, call `handler` with the
     four args. Honor the return:
     * `ExceptionContinueExecution (0)` → write the (possibly handler-
       modified) `CONTEXT` back into the `ucontext` and return from the
       signal handler to resume.
     * `ExceptionContinueSearch (1)` → advance to `record->prev`.
     * (Collided-unwind / nested dispositions: log and continue for now.)
  3. If the chain is exhausted, fall through to VEH → top-level filter →
     terminate (existing order).
* **Unwinding.** `__except` filters that select a handler trigger a global
  unwind (`RtlUnwind` — the **4-arg x86** form, or msvcrt
  `_global_unwind2`/`_local_unwind2`). A minimal but correct `RtlUnwind`
  that walks the chain up to the target frame, calling each handler with
  `EXCEPTION_UNWINDING` set, is needed for `__finally` blocks to run. The
  msvcrt frame handlers `_except_handler3`/`_except_handler4` (scope-table
  interpreters) are what MSVC-compiled `__try` actually registers; the
  shim may need real-ish implementations of these if imported (they
  interpret a scope table hung off the registration record).
* **`__C_specific_handler` is x64/IA64-only.** The current
  `msvcrt___C_specific_handler` stub (`shim_msvcrt.hpp:184`) has no i386
  equivalent — drop it and provide `_except_handler3`/`_except_handler4`
  (and `_local_unwind2`/`_global_unwind2`) instead. Also drop the x64-only
  `RtlAddFunctionTable` stub (`shim_kernel32_sysinfo.hpp:121`); i386 has no
  dynamic function-table registration.
* **`UnhandledExceptionFilter`** reads `ExceptionAddress` at
  `excRec+0x10` (`shim_kernel32_except.hpp:28`) — a Win64 offset; on i386
  `EXCEPTION_RECORD.ExceptionAddress` is at `+0x0C`.

**Risk & staging.** This is the highest-risk component. Stage it:

* **v0**: valid `fs:[0]` + `__try/__except` with no fault (works for free).
* **v1**: signal-driven dispatch through the chain with
  `ContinueExecution`/`ContinueSearch` (catches AVs).
* **v2**: `RtlUnwind` + `_except_handler3/4` for `__finally` and filter-
  driven handler selection.

Many test targets (rar, etc.) may only need v0–v1; measure before
committing to v2.

### 2.6 `RtlCaptureContext` / CONTEXT (i386)

The i386 `CONTEXT` is ~716 bytes (`0x2CC`) with integer regs at:
`Edi@0x9C, Esi@0xA0, Ebx@0xA4, Edx@0xA8, Ecx@0xAC, Eax@0xB0, Ebp@0xB4,
Eip@0xB8, SegCs@0xBC, EFlags@0xC0, Esp@0xC4, SegSs@0xC8`. `RtlCaptureContext`
fills `Eip/Esp/Ebp` (and ideally the rest) via inline asm reading
`%esp/%ebp` and a `call/pop` for `%eip`. The x64 version's fixed offsets
(`Rsp@152, Rbp@160, Rip@248`) and `memset(ctx,0,1232)` are all replaced.

### 2.7 `crash_handler` / signal register access

`mcontext_t` gregs on i386 use `REG_EIP, REG_ESP, REG_EBP, REG_EAX,
REG_EBX, REG_ECX, REG_EDX, REG_ESI, REG_EDI, REG_EFL`. Rewrite the
register dump accordingly. The AS-safe `crash_write_*` helpers and the
libgcc backtrace are width-independent. This handler also becomes the
entry point for the SEH dispatcher (§2.5).

### 2.8 `setjmp` / `longjmp` (i386 naked asm)

Rewrite the two `naked` functions for the i386 `_JUMP_BUFFER`. Args arrive
on the **stack** (cdecl), not in registers. MSVC x86 `_setjmp` saves
`Ebp, Ebx, Edi, Esi, Esp, Eip` and the SEH `Registration`/`TryLevel`
(`fs:[0]`); a common layout is `Ebp@0x00, Ebx@0x04, Edi@0x08, Esi@0x0C,
Esp@0x10, Eip@0x14, Registration@0x18, TryLevel@0x1C, Cookie@0x20`.
Provide `msvcrt__setjmp` / `msvcrt__setjmp3` (the `setjmp3` variadic
variant is what modern MSVC emits) and `msvcrt_longjmp`. The x64
integer-only 11-slot layout is discarded.

### 2.9 Thread start routines & the `CreateThread` trampoline

* `LPTHREAD_START_ROUTINE` = `DWORD __stdcall(void*)`;
  `_beginthreadex` start routine = `unsigned __stdcall(void*)`. Change the
  `win_thread_fn` / `beginthreadex_fn` typedefs from `ms_abi` to
  `stdcall`.
* The `pthread_create` interceptor and the `CreateThread` trampoline are
  logic-identical, but the trampoline must **set up `%fs`/TEB via
  `set_thread_area`** (§2.3) before calling the (stdcall) user routine,
  and re-run `tls_static_init_thread`.
* `msvcrt_signal` trampoline: the x64 version bridges SysV→ms_abi for the
  Windows CRT signal handler (`win_sighandler_t` is `ms_abi`). On x86 the
  Windows CRT signal handler is `__cdecl(int)`; a Linux signal handler is
  also effectively cdecl(int) — so the ABI bridge **collapses** and the
  handler can (almost) be registered directly. Keep the Windows↔Linux
  **signal-number** remap (SIGABRT 22→6 etc.); drop the ABI trampoline.

### 2.10 `shim32_types.h` — struct re-layouts

| Struct | Change |
|---|---|
| `WINAPI` macro | `stdcall` (see §2.1); add `CDECLAPI`, `THISCALL` |
| `STARTUPINFOA/W` | five pointer/handle members → 4 bytes each; struct shrinks **104 → 68 bytes**; `cb` value differs |
| MEMORY_BASIC_INFORMATION (in `VirtualQuery`) | Win64 48-byte → Win32 **28-byte** layout (§2.11) |
| `WIN32_FIND_DATAA/W` | **unchanged** — no pointers, still 320 bytes; the `static_assert(...==320)` holds |
| `CRITICAL_SECTION` | overlay `pthread_mutex_t` (**24 bytes** on i386); `opaque[24]` suffices, re-assert `sizeof(pthread_mutex_t) <= sizeof(CRITICAL_SECTION)` |
| `LARGE_INTEGER`, `FILETIME`, `SYSTEMTIME`, `CPINFO` | unchanged (fixed-width fields) |
| `SECURITY_ATTRIBUTES` | pointer field → 4 bytes |
| fake `_iobuf` | **32 bytes** per entry (not 48); `_ptr@0 _cnt@4 _base@8 _flag@0xC _file@0x10 _charbuf@0x14 _bufsiz@0x18 _tmpfname@0x1C`; `win_file_to_fd` uses 32-byte stride, reads `_file` at `+0x10`; array is 3×32 = 96 bytes (was 144) |
| `EXCEPTION_RECORD` (in `RaiseException`) | `code@0 flags@4 record@8 addr@0xC nparams@0x10 params[15]@0x14` (**4-byte** params, not 8) |
| `EXCEPTION_POINTERS` | `{record*, context*}` = 8 bytes |
| `CONTEXT` | i386 layout (§2.6) |
| Any `uint64_t` holding a pointer/handle in a signature | narrow to pointer-width; note most such uses are the x64-only `Rtl*Unwind` SEH funcs being replaced anyway |

### 2.11 Runtime Win64-isms hiding in "portable" headers

These are easy to miss because they live in feature headers that are
otherwise width-clean, but each bakes in a Win64 layout or an x64-gated
path and will silently corrupt data on i386:

* **`VirtualQuery` MEMORY_BASIC_INFORMATION** (`shim_kernel32_misc.hpp:
  67-82`) is written with Win64 field offsets (48-byte struct,
  `RegionSize@24`, pointer fields 8 bytes). Win32 MBI is **28 bytes**
  (`BaseAddress@0, AllocationBase@4, AllocationProtect@8, RegionSize@12,
  State@16, Protect@20, Type@24`). The `uintptr_t` writes become 4-byte on
  i386, so the offsets must be re-laid-out, not just recompiled.
* **`LoadString` PE-resource walk** (`shim_user32.hpp:106-108`) hard-codes
  the **PE32+** optional-header magic `0x020B` and the resource
  data-directory at `opt+112`. For PE32 this is magic `0x010B` and
  data-directory at **`opt+96`**. This is a *runtime* PE32-vs-PE32+ bug,
  independent of the converter's parsing.
* **Affinity masks** — `GetProcessAffinityMask`/`SetProcessAffinityMask`
  (`shim_kernel32_thread.hpp:94,103`) take `uint64_t*`/`uint64_t`, but
  Win32 affinity is `ULONG_PTR` = **32-bit**. Narrow the signatures or the
  caller writes 8 bytes into a 4-byte slot.
* **`GetCurrentThreadId`** (`shim_kernel32_proc.hpp:27`) reads the cached
  TID via `movl %%gs:0x48` — becomes `movl %%fs:0x24` on i386 (or just
  fall through to `SYS_gettid`).
* **`IsProcessorFeaturePresent`/CPUID** (`shim_kernel32_proc.hpp:84-95`)
  is wrapped in `#ifdef __x86_64__`; `cpuid` works identically on i386, so
  **un-gate** it for the 32-bit build rather than losing the feature.
* **`FormatMessageA/W`** positional-arg expander (`shim_kernel32_locale.hpp:
  37-46`, `shim_kernel32_misc.hpp:98`) pre-fetches args with
  `va_arg(ap, void*)` under an "x86-64 ABI safe" comment — re-verify the
  fetch width under the i386 cdecl va_list.

### 2.12 What is reusable **unchanged** (the good news)

The large majority of the shim is POSIX-translation logic that does not
care about pointer width or convention (beyond the `WINAPI` macro flip):
file I/O, directory search, `FindFirst/Next` + `WIN32_FIND_DATA`, console
(`tcgetattr`), memory (`mmap`/`Heap*`), path translation, UTF-8↔UTF-16,
handle table, sync primitives (mutex/event/semaphore/`WaitFor*`), FLS/TLS
*slot* logic, registry/crypto/security stubs, locale, env block, cmdline
parsing, image-base discovery (`dl_iterate_phdr` — width-independent),
resource-directory walking for `LoadString`. These headers port by:
recompiling `-m32`, flipping `WINAPI`→stdcall, and fixing the handful of
`uint64_t`-as-pointer spots the compiler flags. Budget most of the porting
*effort* on §2.1–2.9, not these.

---

## 3. `load32.cpp` (from `load.cpp`)

The `--so` loader helper. Build `-m32`; the `shim_reload_cmdline` /
`WINAPI_SHIM_CMDLINE` mechanism is width-independent and carries over
verbatim.

**Declare `winmain_t` `__cdecl`.** The convention is very nearly
irrelevant here — the generated `_entrypoint` trampoline ignores its
arguments entirely and never returns (§1.5) — but `cdecl` is the correct
choice because the *caller* then owns argument cleanup. A `stdcall`
declaration would promise a `ret N` the trampoline does not perform.

**Keep the `-l:winapi_shim32.so` DT_NEEDED link.** The reason is
unchanged *in substance*: the shim's `initial-exec` `__thread` variables
must be allocated from the static TLS block at program startup, which
only happens if the shim is a load-time dependency rather than arriving
via `dlopen`. Note, though, that the *other* justification in the 64-bit
source (`shim.cpp:91-97` — avoiding `__tls_get_addr`, whose call sequence
clobbers `RDI`, callee-saved under `ms_abi`) is **x86-64-specific** and
does not carry over; on i386 the argument register is `EAX`, which is
caller-saved under both stdcall and cdecl. Keep `initial-exec` for the
load-order reason alone.

---

## 4. Linker version script `shim32.map`

Structurally identical to `shim.map` (a `global:`/`local:` list). The
symbol **names are unchanged** (stdcall doesn't decorate on ELF), so the
list can start as a copy of `shim.map` and be pruned/extended as the
32-bit surface settles. Keep `pthread_create`, `shim_register_tls`, and
`shim_reload_cmdline` exported. (Symbol names stay unsuffixed — see
§1.5 — so only the soname distinguishes the two shims.)

---

## 5. Tests — `t32.sh`, `exe32/`, `dll32/`

* **`exe32/`**: 32-bit PE test binaries (32-bit builds of the same tools
  the 64-bit suite uses — rar, ppmonstr, nz, rz — where 32-bit versions
  exist). The x64 `exe/` binaries won't parse (wrong machine).
* **`dll32/`**: 32-bit side-DLLs for ordinal resolution (x86 `oleaut32.dll`
  etc.) — ordinals differ from the x64 exports.
* **`t32.sh`**: same harness as `t.sh` (convert → run
  `./x.elf a -m5 archive *.so` → assert exit 0 + `Done` + non-empty
  `.rar`), pointed at `pe2elf32` / `winapi_shim32.so` / `exe32/`.
* A **hello-world smoke test** first: a tiny 32-bit PE that calls
  `GetStdHandle`/`WriteFile`/`ExitProcess` (no CRT, no SEH, no threads) is
  the right Milestone-1 gate — it exercises the converter, FS-TEB setup,
  stdcall dispatch, and the IAT/reloc path in isolation.

---

## 6. `pedump.cpp`

Optional. The standalone inspector already reads both PE32 and PE32+ in
places (the `OrdinalResolver` does). If a 32-bit-aware dump is wanted,
either teach `pedump` the PE32 optional header or fork `pedump32.cpp`.
Not on the critical path for conversion.

---

## 7. Build integration (`Makefile`)

New targets, paralleling the existing ones:

```make
# Host tool — native build, just emits ELF32 bytes. No -m32 needed.
PE2ELF32_OUT   = pe2elf32
PE2ELF32_SRCS  = pe2elf32.cpp
PE2ELF32_FLAGS = -O2 -std=c++17 -Wall -Wextra -Wno-unused-parameter -static

# 32-bit shim — MUST be -m32.
SHIM32_FLAGS = -O2 -fPIC -shared -m32 -std=c++17 -fvisibility=hidden \
               -Wall -Wextra -Wno-unused-parameter \
               -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -I.
SHIM32_LDFLAGS = -lpthread -ldl \
                 -Wl,--version-script=shim32.map \
                 -Wl,-z,now -Wl,-soname,winapi_shim32.so
# load32 also -m32, DT_NEEDED against the 32-bit shim.
```

Notes:

* **No `-latomic` needed.** Audited: every `__atomic_*` in the shim
  operates on a pointer or an `int` (`shim.cpp:320-323`,
  `shim_kernel32_except.hpp:18,50`, `shim_kernel32_thread.hpp:36,59,62`) —
  all 4 bytes on i386, all inlined. The only 64-bit word is the TLS
  bitmask, which is mutex-protected rather than atomic (§2.4). Add
  `-latomic` only if a future change introduces a genuine 64-bit atomic.
* **`-D_FILE_OFFSET_BITS=64`** becomes **load-bearing** on this build. On
  x86-64 it is a no-op (`off_t` is already 64-bit); on i386 it is what
  makes `off_t` 64-bit and redirects `lseek`/`stat`/`open` to their
  `*64` variants. Dropping it would silently cap file sizes at 2 GB —
  fatal for an archiver test suite.
* **Toolchain prerequisite (blocking):** this environment currently has
  32-bit *codegen* but **not** the 32-bit dev headers/libs — including
  `<pthread.h>` under `-m32` fails on a missing `bits/wordsize.h`. Install
  `gcc-multilib g++-multilib libc6-dev-i386` (Debian/Ubuntu) or
  `glibc-devel.i686 libstdc++-devel.i686` (Fedora) before the shim can
  build. The converter (`pe2elf32`, native) builds today with no extra
  packages.
* Keep the debug build (`winapi_shim32_dbg.so`, `-DWINAPI_LOG_ENABLED
  -O0 -g`) and the `dummy32.so` injection example (`-m32`, adjust
  `-Wl,-Ttext-segment` to a 32-bit-friendly address like `0x30000000`).

---

## 8. Milestones & risk

| Milestone | Deliverable | Gates |
|---|---|---|
| **M1 — converter + minimal shim** | `pe2elf32` converts a hand-written no-CRT 32-bit PE (GetStdHandle/WriteFile/ExitProcess); FS-TEB + stdcall + IAT/`R_386_32` + REL base relocs proven | ELF runs under `ld-linux.so.2`, prints, exits 0 |
| **M2 — CRT startup** | msvcrt surface: `__getmainargs`, `_initterm`, cdecl `printf`/`sprintf` (native va_list), `__iob_func` (32-byte iob), argv/cmdline, static TLS via trampoline | a CRT-linked 32-bit PE reaches `main` and does formatted I/O |
| **M3 — SEH v1** | i386 CONTEXT + `RtlCaptureContext`; signal-driven `fs:[0]` chain dispatch (`ContinueExecution`/`ContinueSearch`); VEH | `__try/__except` catches an AV |
| **M4 — full parity** | threads (FS setup per thread), sync, `_beginthreadex`, `setjmp/longjmp`, COM thiscall vtable, unwinding (`RtlUnwind`/`_except_handler3/4` as needed) | `t32.sh` (rar) passes |

**Risk register**

| Risk | Likelihood | Mitigation |
|---|---|---|
| x86 SEH dispatcher (§2.5) complexity | High | Stage v0→v2; measure what targets actually need; x86 SEH is well-documented (unlike x64 tables) |
| Trampoline stack-alignment for modern MSVC CRT (§1.5) | Medium | Verify `esp%16==12` at PE entry; tune the `and esp,-16`/pad sequence against a real CRT |
| Per-thread `%fs` setup races / signal-safety (§2.3) | Medium | Set FS in the thread trampoline before any user code; ensure signal handlers don't assume FS on foreign threads |
| `set_thread_area` GDT-slot exhaustion | Low | `modify_ldt` fallback |
| stdcall symbol decoration | **Resolved** | Verified undecorated on i386 ELF |
| REL in-place-addend correctness for `--pie` | Low | Leave PE reloc sites untouched; unit-check a rebased load |
| `-m32` toolchain availability | Low (env-specific) | Document the package prerequisite (§7) |

---

## 9. File-by-file map (existing 64-bit → new 32-bit)

| Existing | New | Nature of change |
|---|---|---|
| `pe2elf.cpp` | `pe2elf32.cpp` | interp/soname defaults; same orchestration |
| `pe_types.hpp` | `pe_types32.hpp` | PE32 opt header (+`BaseOfData`, 32-bit base/stack/heap), `pe_tls32`, HIGHLOW reloc type, machine `0x14C` |
| `elf_types.hpp` | `elf_types32.hpp` | `Elf32_*` (note `Elf32_Sym` field order + REL), `EM_386`, `R_386_*`, `DT_REL*` |
| `pe_image.hpp` | `pe_image32.hpp` | 4-byte IAT/ILT, ordinal bit 31, HIGHLOW relocs, `pe_tls32`, 32-bit rebase; `OrdinalResolver` reusable (needs `dll32/`) |
| `elf_plan.hpp` | `elf_plan32.hpp` | `Elf32_*` sizes, larger `kTrampolineSize` |
| `elf_build.hpp` | `elf_build32.hpp` | REL + in-place addends, i386 trampoline (abs + get-PC PIC), 24-byte `ShimTlsInfo`, `DT_REL*`, `.rel.dyn` |
| `elf_write.hpp` | `elf_write32.hpp` | `ELFCLASS32`, `EM_386`, `Elf32_*` serialization |
| `util.hpp` | *shared* | width-independent; reuse as-is |
| `shim.cpp` | `shim32.cpp` | FS/`set_thread_area` TEB, x86 TEB/PEB offsets, i386 crash regs + SEH dispatch, stdcall macro |
| `shim_types.h` | `shim32_types.h` | stdcall/cdecl/thiscall macros, 32-bit struct layouts (§2.10) |
| `shim.map` | `shim32.map` | copy; same symbol names |
| `shim_msvcrt.hpp` | `shim32_msvcrt.hpp` | cdecl + native va_list, 32-byte iob, i386 setjmp/longjmp, stdcall thread typedefs |
| `shim_kernel32_except.hpp` | `shim32_kernel32_except.hpp` | **rewrite**: x86 `RtlUnwind` (4-arg), `_except_handler3/4`, i386 `RtlCaptureContext`; drop x64 table stubs |
| `shim_kernel32_veh.hpp` | `shim32_kernel32_veh.hpp` | stdcall handler typedef; logic identical |
| `shim_kernel32_thread.hpp` | `shim32_kernel32_thread.hpp` | stdcall thread routines, FS setup in trampoline |
| `shim_kernel32_critsec.hpp` | `shim32_kernel32_critsec.hpp` | `fs:0x2C` TLS slot read; 24-byte CS |
| `shim_shell32.hpp` | `shim32_shell32.hpp` | **thiscall** IMalloc vtable, 4-byte slots |
| `shim_user32.hpp` | `shim32_user32.hpp` | cdecl `wsprintf*`; rest stdcall |
| all other `shim_*.hpp` | `shim32_*.hpp` | recompile `-m32`, `WINAPI`→stdcall, fix `uint64_t`-as-pointer spots; logic preserved |
| `load.cpp` | `load32.cpp` | `-m32`, stdcall entry typedef, `-l:winapi_shim32.so` |
| `Makefile` | *extend* | `pe2elf32` (native), `winapi_shim32.so` (`-m32`), `load32`, `dummy32.so` (`-Ttext-segment` lowered into the 3 GB user range) |
| `t.sh`, `exe/`, `dll/` | `t32.sh`, `exe32/`, `dll32/` | 32-bit test binaries + side-DLLs |

---

*End of document.*
