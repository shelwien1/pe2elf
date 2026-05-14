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

Produces `pe2elf` and `winapi_shim.so`.

## Usage

```
pe2elf <input.exe> <output.elf> [options]
```

| Option | Default | Description |
|---|---|---|
| `--interp <path>` | `/lib64/ld-linux-x86-64.so.2` | ELF interpreter path |
| `--shim-soname <name>` | `winapi_shim.so` | `DT_NEEDED` name for the WinAPI shim |
| `--strip-pdata` | off | Drop the `.pdata` section (saves space; disables Windows-style SEH unwinding) |
| `--no-shdr` | off | Omit section headers (slightly smaller output) |

The converter must be run from the directory that contains `winapi_shim.so`,
or `winapi_shim.so` must be on `LD_LIBRARY_PATH`, because pe2elf embeds
`DT_RUNPATH=$ORIGIN` so the dynamic linker looks next to the ELF at runtime.

### Example

```sh
./pe2elf program.exe program.elf
./program.elf
```

## Logging

Set `WINAPI_LOG=1` before running to enable call tracing to `/tmp/shimlog.txt`:

```sh
WINAPI_LOG=1 ./program.elf
```

Set `WINAPI_LOG_FILTER=<substring>` to limit logging to functions whose
names contain the given string:

```sh
WINAPI_LOG=1 WINAPI_LOG_FILTER=File ./program.elf
```

## Supported WinAPI functions

The shim currently implements:

`CloseHandle` · `CompareStringW` · `CreateFileA` · `CreateFileW` ·
`DecodePointer` · `DeleteCriticalSection` · `DeleteFileA` ·
`DosDateTimeToFileTime` · `EncodePointer` · `EnterCriticalSection` ·
`ExitProcess` · `FileTimeToDosDateTime` · `FindClose` ·
`FindFirstFileA` · `FindFirstFileExW` · `FindNextFileA` · `FindNextFileW` ·
`FlsAlloc` · `FlsFree` · `FlsGetValue` · `FlsSetValue` ·
`FlushFileBuffers` · `FormatMessageA` · `FreeEnvironmentStringsA` ·
`FreeEnvironmentStringsW` · `FreeLibrary` · `GetACP` · `GetCPInfo` ·
`GetCommandLineA` · `GetCommandLineW` · `GetConsoleCP` · `GetConsoleMode` ·
`GetConsoleOutputCP` · `GetCurrentDirectoryA` · `GetCurrentProcess` ·
`GetCurrentProcessId` · `GetCurrentThreadId` · `GetEnvironmentStrings` ·
`GetEnvironmentStringsW` · `GetFileType` · `GetLastError` ·
`GetLocaleInfoA` · `GetModuleFileNameA` · `GetModuleFileNameW` ·
`GetModuleHandleExW` · `GetModuleHandleW` · `GetOEMCP` · `GetProcAddress` ·
`GetProcessHeap` · `GetStartupInfoA` · `GetStartupInfoW` · `GetStdHandle` ·
`GetStringTypeA` · `GetStringTypeW` · `GetSystemTimeAsFileTime` ·
`GetTickCount` · `HeapAlloc` · `HeapCreate` · `HeapFree` · `HeapReAlloc` ·
`HeapSetInformation` · `HeapSize` · `InitializeCriticalSection` ·
`InitializeCriticalSectionAndSpinCount` · `InitializeSListHead` ·
`IsDebuggerPresent` · `IsProcessorFeaturePresent` · `IsValidCodePage` ·
`LCMapStringA` · `LCMapStringW` · `LeaveCriticalSection` · `LoadLibraryA` ·
`LoadLibraryExW` · `MultiByteToWideChar` · `QueryPerformanceCounter` ·
`QueryPerformanceFrequency` · `RaiseException` · `ReadConsoleInputA` ·
`ReadFile` · `RtlCaptureContext` · `RtlLookupFunctionEntry` ·
`RtlPcToFileHeader` · `RtlUnwindEx` · `RtlVirtualUnwind` ·
`SetConsoleMode` · `SetEndOfFile` · `SetEnvironmentVariableW` ·
`SetFileAttributesA` · `SetFilePointer` · `SetFilePointerEx` ·
`SetFileTime` · `SetHandleCount` · `SetLastError` · `SetStdHandle` ·
`SetUnhandledExceptionFilter` · `Sleep` · `TerminateProcess` · `TlsAlloc` ·
`TlsFree` · `TlsGetValue` · `TlsSetValue` · `UnhandledExceptionFilter` ·
`VirtualAlloc` · `VirtualFree` · `WideCharToMultiByte` · `WriteConsoleA` ·
`WriteConsoleW` · `WriteFile`

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
| `shim.cpp` | `winapi_shim.so` implementation |
| `shim_types.h` | Win32 type definitions for the shim |
| `shim.map` | Linker version script (controls symbol visibility) |
