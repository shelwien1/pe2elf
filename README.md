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
| `dummy.cpp` | Example injection library built as `dummy.so` |

### Repo data

| Path | Purpose |
|---|---|
| `exe/` | Windows test binaries (rar390, rar550a, rar701a, …) |
| `dll/` | Side-loaded Windows DLLs used only for ordinal-to-name resolution at conversion time |
| `t.sh` | End-to-end smoke test: build, convert, run, check `Done` + non-empty `.rar` |
