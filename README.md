# pe2elf

Converts PE32+ (Windows x64) executables to ELF64 (Linux x86-64) binaries
that run natively under `ld-linux-x86-64.so.2` with a companion WinAPI shim.

## How it works

`pe2elf` rewrites the file format without touching the PE code or data:

1. **ELF wrapper** — an ELF header, program headers, and a small synthetic
   segment are prepended below `ImageBase`. The synthetic segment holds
   `.interp`, `.dynsym`, `.dynstr`, `.rela.dyn`, `.dynamic`, and a
   9-byte trampoline (`sub rsp, 8 ; jmp pe_entry`) that reconciles the
   SysV vs MSVC stack-alignment convention.

2. **IAT patching** — IAT slots in the `.rdata` section are zeroed and
   covered by `R_X86_64_64` relocations in `.rela.dyn`. At load time
   `ld.so` fills each slot with the address of the matching symbol from
   `winapi_shim.so`.

3. **PE headers preserved** — the original PE headers are mapped at
   `ImageBase` so the MSVC CRT can walk data directories at startup.

4. **`winapi_shim.so`** — a companion shared library that implements
   ~100 Windows API functions using `__attribute__((ms_abi))`, translating
   Win32 calls into POSIX equivalents at runtime.

The resulting binary loads and executes without Wine or a kernel module.

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
| `winapi_shim.so` | WinAPI shim — silent, for production use |
| `winapi_shim_dbg.so` | WinAPI shim — full call logging to `/tmp/shimlog.txt` and stderr |
| `dummy.so` | Example injection library (prints `Hello, world!!!` at startup) |

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

The output ELF embeds `DT_RUNPATH=$ORIGIN`, so `ld.so` looks for the shim
next to the ELF at runtime. Place `winapi_shim.so` (or `winapi_shim_dbg.so`)
in the same directory as the converted binary before running it.

### Example

```sh
# Convert and run
./pe2elf program.exe program.elf
cp winapi_shim.so /path/to/program/
./program.elf

# Convert with debug logging
./pe2elf program.exe program.elf --dbg
cp winapi_shim_dbg.so /path/to/program/
./program.elf
# WinAPI calls are traced to /tmp/shimlog.txt and stderr

# Inject an extra shared library at startup
./pe2elf program.exe program.elf --inject=dummy.so
cp winapi_shim.so dummy.so /path/to/program/
./program.elf
```

## Logging

Build `winapi_shim_dbg.so` is compiled with `-DWINAPI_LOG_ENABLED`. It traces
every shim call to `/tmp/shimlog.txt` and to stderr. Use `--dbg` when converting
to bind the output ELF to the debug build:

```sh
./pe2elf program.exe program.elf --dbg
./program.elf 2>/dev/null   # trace goes to /tmp/shimlog.txt
```

The production `winapi_shim.so` contains no logging code at all.

## Limitations

- **Named imports only** — ordinal imports are not supported; `pe2elf`
  exits with an error if any are present.
- **No ASLR / base relocation** — the PE must load at its preferred
  `ImageBase`. Binaries that require relocation (`.reloc` directory
  populated, no `IMAGE_FILE_RELOCS_STRIPPED`) may not work correctly.
- **No TLS** — binaries using `__declspec(thread)` / `IMAGE_TLS_DIRECTORY`
  will malfunction silently.
- **Single IAT section** — split IAT layouts (IAT slots spanning more
  than one PE section) are rejected with an error.
- **AMD64 only** — both the converter and the shim target x86-64
  exclusively.

## Source layout

| File | Purpose |
|---|---|
| `pe2elf.cpp` | Entry point and CLI; orchestrates parse → plan → build → write |
| `util.hpp` | `Buffer`, `OutBuf`, `align_up` |
| `pe_types.hpp` | PE structs and constants (`#pragma pack`) |
| `elf_types.hpp` | ELF structs and constants |
| `pe_image.hpp` | `PeImage`: PE parsing, section map, import collection |
| `elf_plan.hpp` | `compute_plan()`: VA and file-offset layout |
| `elf_build.hpp` | `Builder`: synthetic sections, program headers, section headers |
| `elf_write.hpp` | `Writer`: ELF serialization and file output |
| `shim.cpp` | `winapi_shim.so` / `winapi_shim_dbg.so` implementation |
| `shim_types.h` | Win32 type definitions for the shim |
| `shim.map` | Linker version script (controls symbol visibility) |
| `dummy.cpp` | Example injection library built as `dummy.so` |
