# pe2elf

Converts PE32+ (Windows x64) executables to ELF64 (Linux x86-64) binaries
that run natively under `ld-linux-x86-64.so.2` with a companion WinAPI shim
— no Wine, no kernel module, no emulation.

The converter leaves the original PE code and data untouched; it only
rewrites the file wrapper (ELF header, program headers, dynamic section)
and zeroes the IAT so the dynamic linker can fill it from `winapi_shim.so`.
The shim implements ~360 Windows API entry points using `__attribute__((ms_abi))`
and translates them to POSIX equivalents at runtime.

End-to-end this is enough to convert and run real-world tools — `t.sh`
exercises rar390, rar550a, and rar701a, each invoked as
`./rar.elf a -m5 archive *.so` and checked for `Done` + a non-empty `.rar`.

A parallel 32-bit pipeline — `pe2elf32` + `winapi_shim32.so` — does the same
for **PE32 / `IMAGE_FILE_MACHINE_I386`** input, producing ELFCLASS32 / `EM_386`
binaries that run under `/lib/ld-linux.so.2`. It is a separate tree rather
than a mode of `pe2elf`, because the two differ in almost every low-level
detail: `REL` with in-place addends instead of `RELA`, three calling
conventions (`stdcall`/`cdecl`/`thiscall`) instead of one `ms_abi`, a TEB
reached through a `%fs` GDT descriptor instead of a `GS` base, and
chain-based `fs:[0]` SEH instead of x64's `.pdata` unwind tables. See
[`!pe2elf32-plan.md`](!pe2elf32-plan.md) and [the 32-bit section](#32-bit-pe32--elf32)
below.

## How it works

1. **ELF wrapper** — an ELF header, program headers, and a small synthetic
   segment are prepended below `ImageBase`. The synthetic segment holds
   `.interp`, `.dynsym`, `.dynstr`, `.rela.dyn`, `.dynamic`, and a
   9-byte trampoline (`sub rsp, 8 ; jmp pe_entry`) that reconciles the
   SysV vs MSVC stack-alignment convention before transferring control to
   the PE entry point.

2. **IAT patching** — every IAT slot in `.rdata` is zeroed and covered by
   an `R_X86_64_64` relocation in `.rela.dyn`. At load time `ld.so` fills
   each slot with the address of the matching `kernel32_`/`user32_`/…
   prefixed symbol exported by `winapi_shim.so`.

3. **Ordinal imports** — PE binaries that import by ordinal rather than
   by name are resolved by parsing the matching DLL file kept under
   `dll/<lowercase-name>.dll`. The converter walks the DLL's export
   directory once to build an ordinal → name map, then writes a normal
   named import.

4. **TLS** — the PE `IMAGE_TLS_DIRECTORY` is preserved as-is in `.tls`.
   At runtime the shim's `shim_register_tls` (invoked by an ELF
   constructor that the converter injects into the entry trampoline)
   reads the template, allocates per-thread storage, and runs PE TLS
   callbacks with `DLL_PROCESS_ATTACH`/`DLL_THREAD_ATTACH` as appropriate.

5. **PE headers preserved** — the original PE headers stay mapped at
   `ImageBase` so the MSVC CRT can walk data directories at startup
   (`cmp WORD PTR [rax], 'MZ'` in `_acrt_initialize`).

6. **Base relocs** — applied either at conversion time (`--base=<addr>`
   to rebase) or via `R_X86_64_RELATIVE` in `.rela.dyn` (`--pie` to
   produce ASLR-compatible ET_DYN output).

7. **`winapi_shim.so`** — the companion shared library. Exports are
   prefixed with the originating DLL name (`kernel32_GetLastError`,
   `oleaut32_SysAllocString`, …) so converter-generated IAT relocations
   land on the right function unambiguously. Runtime
   `GetProcAddress(LoadLibraryW(L"kernel32"), "GetLastError")` is
   routed by per-handle prefix sentinels — each Windows DLL name we
   recognize gets a unique pseudo-handle that records which prefix
   `GetProcAddress` should stamp onto the looked-up name.

## Requirements

- Linux x86-64
- `g++` with C++17 support
- `ld-linux-x86-64.so.2` (standard glibc dynamic linker)
- `libpthread`, `libdl` (for `winapi_shim.so`)

## Build

```sh
make
```

Produces:

| Output | Description |
|---|---|
| `pe2elf` | The converter (statically linked) |
| `winapi_shim.so` | WinAPI shim — production build, logging disabled by default |
| `winapi_shim_dbg.so` | Same shim, built with `-DWINAPI_LOG_ENABLED -O0 -g`; logs to `/tmp/shimlog.txt` unconditionally |
| `dummy.so` | Example injection library (prints `Hello, world!!!` at startup) |
| `load` | Helper that dlopens a `pe2elf --so`-converted `.so` and invokes its `_entrypoint` symbol with the MSVC WinMain prototype (ms_abi). |

`make pe2elf winapi_shim.so` skips the debug build and `dummy.so`.

## 32-bit (PE32 → ELF32)

```sh
make all32
```

Produces `pe2elf32`, `winapi_shim32.so`, `winapi_shim32_dbg.so`, `dummy32.so`
and `load32` — the same roles as the 64-bit outputs. The converter is a native
host tool (it only emits ELF32 bytes, it never runs them); everything else is
built `-m32`, which needs the 32-bit dev headers and libraries:

```sh
# Debian/Ubuntu
sudo apt-get install gcc-multilib g++-multilib libc6-dev-i386
# Fedora
sudo dnf install glibc-devel.i686 libstdc++-devel.i686
```

32-bit *codegen* alone is not enough — the shim includes system headers.

Usage mirrors the 64-bit tool, with 32-bit defaults (`--interp
/lib/ld-linux.so.2`, `--shim-soname winapi_shim32.so`, ordinal-import DLLs
read from `dll32/` rather than `dll/`):

```sh
./pe2elf32 exe32/1c.exe 1c.elf && ./1c.elf
./pe2elf32 exe32/1c.exe 1c.so --so && ./load32 ./1c.so
```

`--strip-pdata` is accepted for CLI parity but never matches: `.pdata` is an
x64/IA64/ARM unwind-table section that 32-bit x86 PEs do not carry.

`--inject=<soname>` adds a second `DT_NEEDED`, so an arbitrary shared library
loads with the converted binary and its ELF constructors run *before* the PE
entry point. `dummy32.so` is the worked example (it just prints
`Hello, world!!!` from a constructor):

```sh
./pe2elf32 exe32/BMF.exe BMF.elf --inject=dummy32.so
./BMF.elf image.bmp
# Hello, world!!!          <- dummy32.so constructor
# BMF lossless image compressor, v.2.01 ...
```

It is linked at `-Ttext-segment=0x30000000`, which keeps it inside the 3 GB
i386 user range and clear of both the PE image at `0x400000` and the mmap
region the shim and libc land in — worth caring about here in a way it is not
at 64-bit, where the address space is empty enough that any choice works.

Notes specific to this pipeline:

- **`--pie` needs base relocations.** ET_DYN images are relocated by the
  kernel, so a PE built with `IMAGE_FILE_RELOCS_STRIPPED` can only run at its
  preferred base. The converter prints a note when it sees this; `--so` still
  works, because `dlopen` honours the `p_vaddr` hint. (This is not a
  32-bit-specific rule, but it bites sooner here: the address space is packed
  enough that a mis-sized mapping lands on something.)
- **`-D_FILE_OFFSET_BITS=64` is load-bearing**, not cosmetic. On x86-64 it is
  a no-op; on i386 it is what makes `off_t` 64-bit and redirects
  `lseek`/`stat`/`open` to their `*64` variants.
- **x86 SEH works.** `__try`/`__except` registration needs no shim support at
  all (the fake TEB gives the PE a writable `fs:[0]`), and hardware faults are
  dispatched through that chain from the POSIX signal handler, so a handler
  can return `ExceptionContinueExecution` and resume. `_except_handler4` is
  the exception: its scope table is XOR-obfuscated with the image's
  `__security_cookie`, which the shim cannot reach, so it declines rather than
  decode it wrong.

## Usage

```
pe2elf <input.exe> <output.elf> [options]
```

| Option | Default | Description |
|---|---|---|
| `--interp <path>` | `/lib64/ld-linux-x86-64.so.2` | ELF interpreter path |
| `--shim-soname <name>` | `winapi_shim.so` | `DT_NEEDED` name for the WinAPI shim |
| `--dbg` | off | Use `winapi_shim_dbg.so` instead (enables full call logging) |
| `--inject=<soname>` | — | Add a second `DT_NEEDED` entry (e.g. a custom injection library) |
| `--strip-pdata` | off | Drop the `.pdata` section (saves space; disables Windows-style SEH unwinding) |
| `--no-shdr` | off | Omit section headers (slightly smaller output) |
| `--pie` | off | Emit `ET_DYN` (PIE/ASLR-capable) instead of `ET_EXEC` |
| `--so` | off | Emit a dlopen-able `.so`. Exports `_entrypoint` (the real startup trampoline) and points the ELF entry at a safe `RET` byte inside the PE code so accidental direct execution doesn't run the PE. Implies `--pie`. |
| `--base=<addr>` | — | Rebase to `<addr>`, patching relocs in-place. Errors if the original base differs and no `.reloc` data is present. |

The output ELF embeds `DT_RUNPATH=$ORIGIN`, so `ld.so` looks for the shim
next to the ELF at runtime. Place `winapi_shim.so` (or `winapi_shim_dbg.so`)
in the same directory as the converted binary before running it.

### Example

```sh
# Convert and run
./pe2elf program.exe program.elf
cp winapi_shim.so /path/to/program/
./program.elf

# Convert as a dlopen-able shared object, then run via the load helper:
./pe2elf program.exe program.so --so
cp winapi_shim.so program.so load /path/to/dir/
cd /path/to/dir/
./load ./program.so [args...]
# load is linked DT_NEEDED against winapi_shim.so (so the shim's
# initial-exec TLS gets its static block at startup, before the .so is
# dlopen'd), sets WINAPI_SHIM_CMDLINE to "<so-path> <joined-args>" so the
# PE's GetCommandLine and argv start at its own program name, and calls
# shim_reload_cmdline (exported by the shim) so the override takes
# effect after the constructor has already run.

# Convert with debug logging
./pe2elf program.exe program.elf --dbg
cp winapi_shim_dbg.so /path/to/program/
./program.elf
# WinAPI calls trace to /tmp/shimlog.txt

# Inject an extra shared library at startup
./pe2elf program.exe program.elf --inject=dummy.so
cp winapi_shim.so dummy.so /path/to/program/
./program.elf
```

### Ordinal imports

If the PE imports functions by ordinal, drop the matching DLL under
`dll/<lowercase-name>.dll` so the converter can parse its export
directory:

```sh
# rar701a imports SysAllocString/SysFreeString/VariantClear by ordinal
cp /path/to/oleaut32.dll dll/oleaut32.dll
./pe2elf exe/rar701a.exe rar701a.elf
```

A missing or wrong-version DLL is reported with the expected location
in the error message rather than silently producing a broken ELF.

## Logging

`winapi_shim.so` (production build) ships with a runtime-toggleable trace:

```sh
WINAPI_SHIM_LOG=stderr        ./program.elf       # trace to stderr
WINAPI_SHIM_LOG=/tmp/x.log    ./program.elf       # trace to a file
./program.elf                                     # no trace, no overhead
```

`winapi_shim_dbg.so` (`make winapi_shim_dbg.so`) is compiled with
`-DWINAPI_LOG_ENABLED -O0 -g`. It writes to `/tmp/shimlog.txt`
unconditionally and is built for diagnosis under gdb, not production.
Use `--dbg` when converting to bind the ELF to the debug build.

## Tests

`t.sh` runs the full end-to-end smoke test against three RAR builds:

```sh
./t.sh
```

For each target it converts `exe/<name>.exe → <name>.elf`, runs
`./<name>.elf a -m5 archive_<name> *.so`, and asserts the run exits 0,
stdout contains `Done`, and the resulting `.rar` is non-empty.
Default targets: `rar390 rar550a rar701a` (8.0+ versions still TBD).

`t32.sh` is the 32-bit counterpart. It builds `pe2elf32`, the 32-bit shim and
`load32`, then converts each fixture in `exe32/` twice — once as a plain
ET_EXEC and once with `--so` (run via `./load32`) — and checks both exit 0 and
print the expected marker:

```sh
./t32.sh
```

| Fixture | What it gates |
|---|---|
| `1b.exe` | No-CRT PE32 (GetStdHandle/WriteFile/ExitProcess): the converter, the `%fs` TEB, stdcall dispatch, and the IAT `R_386_32` + `REL` base-reloc paths |
| `1c.exe` | MSVCRT-linked PE32: CRT startup — `__getmainargs`, `_initterm`, cdecl `printf` over the native `va_list`, the 32-byte `_iobuf`, and the `fs:[0]` `__try` MSVC wraps `main` in |
| `seh.exe` | Faults through a null pointer inside a hand-built `fs:[0]` frame whose handler rewrites `CONTEXT.Eip`: the signal-driven x86 SEH dispatcher. Regenerate with `exe32/mkseh32.sh` |
| `BMF.exe` | BMF 2.01, Dmitry Shkarin's lossless image compressor — a real-world target, statically linked against the MSVC CRT (it imports *nothing* from msvcrt.dll, so it exercises a different surface from `1c`: heap, file I/O, `RtlUnwind`, `GetStringType`/`LCMapString`, console mode) |

`t32.sh` also converts `seh.exe` with `--inject=dummy32.so` and asserts both
the injected constructor and the PE ran, in that order.

The first three fixtures are checked for a string in stdout. BMF is checked
for **correctness**: `t32.sh` generates a BMP (`exe32/mkbmp32.py`), compresses
it, decompresses it, and asserts the pixel data comes back identical — in both
ET_EXEC and `--so` modes, which also confirms the two startup trampolines
agree (they produce byte-identical compressed output).

The archiver targets `t.sh` uses are not covered: `exe/` holds x64 builds,
which `pe2elf32` correctly rejects on machine type. Drop 32-bit builds into
`exe32/` (and their 32-bit side DLLs into `dll32/`) to extend it.

## Supported features

- **Named and ordinal imports** — ordinal lookup needs the matching
  side-DLL under `dll/`.
- **Base relocations** — applied at conversion via `--base=<addr>`
  (rebase) or emitted as `R_X86_64_RELATIVE` via `--pie`.
- **PE TLS directory** — template, callbacks, and TLS index are all
  hooked. Per-thread TLS storage uses a pthread key; static TLS slots
  reuse the same per-thread block.
- **Fiber Local Storage (FLS)** — `FlsAlloc`/`FlsGetValue`/`FlsSetValue`/
  `FlsFree` share the slot namespace with `TlsAlloc`. Per-slot
  destructors run on thread exit (required by the MSVC CRT PTD lifecycle).
- **CRITICAL_SECTION** — recursive `pthread_mutex_t` underneath.
- **Vectored exception handlers** — `AddVectoredExceptionHandler`,
  `RemoveVectoredExceptionHandler`, and `SetUnhandledExceptionFilter` are
  honored on POSIX-signal-converted exceptions.
- **`__try`/`__except` SEH** — minimal support via `RtlVirtualUnwind`,
  `RtlLookupFunctionEntry`, `RtlUnwindEx`, `RaiseException`. Requires
  `.pdata` (do NOT pass `--strip-pdata`).
- **Backtraces on crash** — the shim installs SIGSEGV/SIGBUS/SIGILL/SIGFPE
  handlers that dump RIP/RSP/RBP, register state, and a libgcc-based
  unwind backtrace.
- **TEB/PEB at GS:[0]** — a fake TEB is allocated per thread and pointed
  to via `arch_prctl(ARCH_SET_GS)` so `__readgsqword` PE code works.

## Limitations

- **Single IAT section** — split IAT layouts (IAT slots spanning more
  than one PE section) are rejected.
- **AMD64 only** — both the converter and the shim target x86-64
  exclusively. AArch64 has a partial TEB-equivalent (`x18`), no exports.
- **Subset of WinAPI** — the shim covers what the test binaries (rar,
  ppmonstr, nz, rz, etc.) need. Many functions are stubs that return
  sensible defaults; see `!shim-plan.md` for the full surface map.
- **No DLL loading at runtime** — `LoadLibraryExW` of an actual Windows
  DLL fails (returns NULL for `*-ms-win-*` API sets, a prefix sentinel
  for known DLLs); the PE import graph must be resolved at conversion.

## Source layout

### Converter

| File | Purpose |
|---|---|
| `pe2elf.cpp` | Entry point and CLI; orchestrates parse → plan → build → write |
| `util.hpp` | `Buffer`, `OutBuf`, `align_up` |
| `pe_types.hpp` | PE structs and constants (`#pragma pack`) |
| `elf_types.hpp` | ELF structs and constants |
| `pe_image.hpp` | `PeImage`: PE parsing, section map, import collection, **`OrdinalResolver`** |
| `elf_plan.hpp` | `compute_plan()`: VA and file-offset layout |
| `elf_build.hpp` | `Builder`: synthetic sections, program headers, section headers |
| `elf_write.hpp` | `Writer`: ELF serialization and file output |
| `pedump.cpp` | Standalone PE inspector (not part of the conversion pipeline) |

The 32-bit converter is a parallel set of files with the same roles —
`pe2elf32.cpp`, `pe_types32.hpp`, `elf_types32.hpp`, `pe_image32.hpp`,
`elf_plan32.hpp`, `elf_build32.hpp`, `elf_write32.hpp` — sharing only
`util.hpp`, which is width-independent. The parts worth reading for the
differences are `elf_types32.hpp` (`Elf32_Sym` reorders its fields and
`Elf32_Phdr` puts `p_flags` last) and `elf_build32.hpp` (`REL` with in-place
addends, and the two startup trampolines — absolute for ET_EXEC, a `call`/`pop`
get-PC thunk for ET_DYN, since i386 has no RIP-relative addressing).

### Shim

| File | Purpose |
|---|---|
| `shim.cpp` | Top-level shim: TEB/PEB setup, handle table, fake heap, logging, signal handlers, TLS callbacks. Includes the per-feature headers. |
| `shim_types.h` | Win32 type and constant definitions for the shim |
| `shim.map` | Linker version script (`global:`/`local:`) controlling exported symbols |
| `shim_kernel32_*.hpp` | kernel32 surface split per feature: `proc`, `mem`, `file`, `console`, `module`, `startup`, `critsec`, `string`, `except`, `fls`, `locale`, `sync`, `sysinfo`, `thread`, `veh`, `tail`, … |
| `shim_advapi32.hpp` | Registry, crypto, security descriptor, privileges |
| `shim_shell32.hpp` | `SHFileOperation`, `SHGetMalloc` (IMalloc vtable), `SHGetPathFromIDList`, … |
| `shim_user32.hpp` | `MessageBox`, `CharLower`, `CharToOem`, … |
| `shim_msvcrt.hpp` | C runtime entry points (`printf`, `sprintf`, `strcmp`, `_beginthreadex`, `_setjmp`/`longjmp`, …) |
| `shim_misc_dlls.hpp` | ole32, oleaut32 (BSTR/VARIANT), powrprof |
| `!shim-plan.md` | Architecture map: every shim section, what it implements, what's stubbed |
| `dummy.cpp` | Example injection library, built as `dummy.so` (64-bit) and `dummy32.so` (32-bit); the source is architecture-independent, only the link address differs |

`shim32.cpp` / `shim32_*.hpp` / `shim32.map` mirror the same split for the
32-bit shim. Most of it is the 64-bit logic recompiled `-m32` — POSIX
translation does not care about pointer width — with the ABI boundary and the
low-level machinery reworked: `shim32_types.h` defines `WINAPI`/`CDECLAPI`/
`THISCALL` instead of one `ms_abi`, `shim32.cpp` builds the TEB at the x86
offsets and installs it with `set_thread_area` + a `%fs` load per thread, and
`shim32_kernel32_except.hpp` is a rewrite: the x86 `fs:[0]` chain dispatcher,
a 4-argument `RtlUnwind`, i386 `CONTEXT`/`RtlCaptureContext`, and the msvcrt
`_except_handler3` scope-table interpreter with `_local_unwind2`/`_global_unwind2`.

### Repo data

| Path | Purpose |
|---|---|
| `exe/` | Windows test binaries (rar390, rar550a, rar701a, …) |
| `dll/` | Side-loaded Windows DLLs used only for ordinal-to-name resolution at conversion time |
| `t.sh` | End-to-end smoke test: build, convert, run, check `Done` + non-empty `.rar` |
| `exe32/` | 32-bit PE test fixtures (`1b`, `1c`, `seh`) plus the sources and generator for `seh.exe` |
| `dll32/` | 32-bit side-loaded DLLs for ordinal-to-name resolution (x86 DLLs export different ordinals than their x64 siblings, so this is separate from `dll/`) |
| `t32.sh` | End-to-end smoke test for the 32-bit pipeline, in both ET_EXEC and `--so` modes |
