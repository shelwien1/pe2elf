# shim — Current Architecture and Outstanding Work

Assumptions: little-endian host; primary target glibc on Linux x86-64 with
graceful degradation toward musl/aarch64 where cheap.

---

## 1. Current Layout

The shim is not a single translation unit, but it is close to one: `shim.cpp`
holds the bulk of the code and `#include`s two large helper headers near the
end so they share file-scope statics rather than going through declarations.

| File | Role | Approx. size |
|---|---|---|
| `shim.cpp` | Main TU. Constructor, fake TEB/PEB, handle table, path/encoding helpers, mmap tracker, signal handler, image-base discovery, PE TLS directory, and the bulk of `kernel32_*` / `advapi32_*` / `shell32_*` / `shlwapi_*` / `user32_*` / `winmm_*` exports. | 4 561 lines, 269 `EXPORT` functions + `pthread_create` + `shim_register_tls` |
| `shim_kernel32_sync.hpp` | `#include`d near the end of `shim.cpp`. Owns the generic sync handle allocator, `WaitForSingleObject` dispatcher, and the `CreateMutex` / `CreateEvent` / `CreateSemaphore` / `CreateThread` / `ExitThread` / `GetExitCodeThread` / `SignalObjectAndWait` family, plus `undo_wait_acquire` for `WaitForMultipleObjects` rollback. | 518 lines, 13 `EXPORT` functions |
| `shim_msvcrt.hpp` | `#include`d at the very bottom of `shim.cpp`. Owns the `msvcrt_*` surface: MS-ABI variadic formatter, `__getmainargs` / `__wgetmainargs`, fake `__iob_func`, `_initterm`, CRT locking, `_time64` family, `qsort`, `scanf`, `_beginthreadex`/`_endthreadex`, MS-ABI `_setjmp`/`longjmp`. | 600 lines, 65 `EXPORT` + 2 naked `_setjmp`/`longjmp` + 4 data variables (`_commode`, `_fmode`, `__initenv`, `_acmdln`) |
| `shim_types.h` | Windows-shaped primitive types, struct layouts (`FILETIME`, `SYSTEMTIME`, `LARGE_INTEGER`, `CRITICAL_SECTION`, `WIN32_FIND_DATA{A,W}`, `STARTUPINFO{A,W}`, `CPINFO`), error codes, file/heap/mem/page/exception flags, `LCMAP_*` / `NORM_*` / `CSTR_*` / `CT_CTYPE*` / `C1_*` constants, and inline `FILETIME` ↔ `uint64_t` helpers. | 236 lines |
| `shim.map` | Linker version script. Lists every dynamic export by name; everything else is `local: *`. | 368 lines, 355 symbols |

Everything is built with `-fvisibility=hidden`; `EXPORT` re-promotes only the
WinAPI surface, and the version script narrows it further. Two outputs are
produced from the same sources: `winapi_shim.so` (release) and
`winapi_shim_dbg.so` (`-DWINAPI_LOG_ENABLED`, `-O0 -g`).

The original plan envisioned a 16-file modular split. That split was not
performed; the existing arrangement keeps cohesion (file-scope statics shared
between sections without a separate header dance), and the two `.hpp`
extractions absorbed the parts that were genuinely separable. Treat the
section banners inside `shim.cpp` as navigation markers; numbered headings
(7.1 – 7.15) match the original WinAPI category grouping and unnumbered
banners cover features added since.

---

## 2. Section Map (shim.cpp)

Pre-export infrastructure (file-scope, hidden visibility):

| Lines | Section |
|---|---|
| 41 – 88   | Visibility, logging (`WINAPI_SHIM_LOG=path|stderr`, `WINAPI_LOG_ENABLED` build flag) |
| 90 – 155  | TLS last-error, per-thread `tls_slots` allocator with `pthread_key` destructor (N1 fix), `SET_LAST_ERROR` macro mirroring TEB+0x68 (B16/R29), `errno_to_win32`, compile-time size assertions (I7) |
| 157 – 232 | Fake PEB construction (`init_fake_peb`): PEB_LDR_DATA empty lists, RTL_USER_PROCESS_PARAMETERS with stdio handles, ProcessHeap stub |
| 236 – 294 | `shim_init_teb` / `shim_thread_attach`: per-thread TEB, GS register on x86-64 / x18 on aarch64, real stack bounds via `pthread_getattr_np` |
| 300 – 335 | `pthread_create` interceptor (I8): trampoline that calls `shim_thread_attach` before user fn |
| 337 – 506 | Handle table — `H_FREE`/`H_FILE`/`H_FIND`/`H_MODULE`/`H_MUTEX`/`H_EVENT`/`H_SEMAPHORE`/`H_THREAD`; refcounted `FindCtx`, refcounted sync structs; `handle_alloc_*` populate atomically under `g_handles_mu` |
| 508 – 627 | Path translation (`win_path_to_posix`, `posix_to_win_path`, `path_join`) and UTF-8 ↔ UTF-16 (`wchar_to_utf8`, `utf8_to_wchar` with continuation-byte skip — B5) |
| 629 – 658 | `make_open_flags` (I2) — Windows access/disposition → POSIX `O_*` |
| 660 – 696 | mmap tracker for `VirtualAlloc`/`VirtualFree` (B9/R9), max 4 096 mappings |
| 698 – 802 | Process state — cmdline parsed from `/proc/self/cmdline` with shell-style quoting, env block (UTF-8 + UTF-16 caches with on-demand regen, B23/R34), image-base discovery (R26 via `dl_iterate_phdr` + PE-header scan), `g_pe_base` for resource lookup |
| 804 – 848 | msvcrt CRT state — `g_main_argc`/`g_main_argv` (built from `/proc/self/cmdline`), fake Windows `_iobuf` array for `__iob_func` |
| 850 – 937 | Signal/crash handler — AS-safe `crash_write_*` helpers via raw `SYS_write`, register/backtrace dump, signal table (`SIGSEGV`, `SIGILL`, `SIGFPE`, `SIGBUS`, `SIGABRT`, `SIGUSR1` for `SuspendThread`) |
| 939 – 976 | Image base discovery via `dl_iterate_phdr` PT_LOAD scan (B13/R26) |
| 978 – 1082 | PE TLS directory — `shim_register_tls` (called by pe2elf startup thunk before `PE_ENTRY`), `run_tls_callbacks` (DLL_PROCESS/THREAD_ATTACH/DETACH), `tls_static_init_thread` (per-thread static-TLS block) |
| 1084 – 1105 | `__attribute__((constructor)) shim_init` and `__attribute__((destructor)) shim_fini` |

Exported WinAPI surface (`ms_abi`, default visibility):

| Lines | Banner | Notable behaviour |
|---|---|---|
| 1113 – 1200 | 7.1 Process / Identity | `GetCurrentThreadId` reads TEB+0x48 directly; `IsProcessorFeaturePresent` uses CPUID at runtime (R45) |
| 1202 – 1212 | 7.2 Error State | `GetLastError`/`SetLastError` via `tls_last_error` + TEB+0x68 mirror |
| 1214 – 1346 | 7.3 Memory | `VirtualAlloc` with `MAP_FIXED_NOREPLACE` + `MAP_FIXED` fallback (R40); `Heap*` over libc malloc; `HeapReAlloc(size=0)` clamps to 1 (R39); `HeapFree` rejects ptr <0x10000 |
| 1348 – 1530 | 7.4 File I/O | `CreateFileW`/`CreateFileA` with `CONIN$`/`CONOUT$`/`CON` console-device mapping; `SetStdHandle` does `dup2` so CRT printf follows (B15/R28) |
| 1532 – 1540 | 7.5 File Times | `GetSystemTimeAsFileTime` |
| 1542 – 1744 | 7.6 Directory / File Search | `find_ctx_open` shared between A/W variants, `win_fnmatch` (FAT-compat `*.foo` ↔ extensionless), `stat_to_win_attrs` (no dotfile-hidden by design) |
| 1746 – 1806 | 7.7 Console I/O | `GetConsoleMode` derived from `tcgetattr` (R43); `WriteConsoleW` bounded by `nChars` (B10/R10) |
| 1808 – 1936 | 7.8 Module / Library | `FAKE_WIN_MODULE` / `MAIN_IMAGE_MODULE` typed pseudo-handles (B14/R27); `GetModuleFileNameW` resolves loaded `.so` via `dladdr` (B18b/R31); `LoadLibrary*` paths through `win_path_to_posix` (B19/R32) |
| 1938 – 2014 | 7.9 Startup / Command Line / Environment | `GetCommandLine{A,W}`; `GetEnvironmentStrings{A,W}` with cache invalidation on `SetEnvironmentVariableW` (B23/R34) |
| 2016 – 2035 | 7.10 Time / Performance | QPC/QPF/GetTickCount |
| 2037 – 2138 | 7.11 Synchronization | CRITICAL_SECTION as recursive `pthread_mutex`; TLS slots backed by per-thread array at GS:[0x58] |
| 2140 – 2143 | 7.12 SListHead stubs | |
| 2144 – 2312 | 7.13 String / Code Page | `MultiByte/WideChar` honour explicit `srclen` (B6/R6); `CompareStringW` honours `n1`/`n2` (B7/R7); `LCMapStringW` covers `LCMAP_UPPERCASE`/`LOWERCASE`; `GetStringTypeW` returns CT_CTYPE1 (R44) |
| 2314 – 2323 | 7.14 Pointer Encoding | identity stubs |
| 2325 – 2436 | 7.15 Exception / SEH | `UnhandledExceptionFilter` logs + terminates (B36/R36); `RtlUnwindEx` logs + returns instead of abort (B40/R41); `RtlCaptureContext` fills `Rsp`/`Rbp`/`Rip` (B37/R37); `RaiseException(EXCEPTION_NONCONTINUABLE)` exits |
| 2438 – 2484 | Misc stubs (`GetStringTypeA`, `LCMapStringA`, `Sleep` with absolute-time clock_nanosleep) |
| 2486 – 2658 | A-variant file/directory: `CreateFileA`, `DeleteFileA`, `SetFileAttributes{A,W}`, `GetCurrentDirectory{A,W}`, `GetModuleFileNameA`, `LoadLibraryA` |
| 2660 – 2761 | `SetFilePointer` (non-Ex), `SetFileTime`, `SetEndOfFile`, `FileTimeToDosDateTime` (pre-1980 underflow guard — B31/R47), `DosDateTimeToFileTime` |
| 2763 – 2870 | FLS — shares slot bitset with TLS; per-thread destructor armed via pthread_key (R33) |
| 2872 – 2898 | `GetLocaleInfo{A,W}` |
| 2900 – 2974 | `FormatMessageA` with positional escapes `%N!fmt!` (B30/R46) |
| 2976 – 3036 | Console misc — `ReadConsoleW`, `ReadConsoleInput{A,W}` over termios `read()` (B28/R42), `SetHandleCount` |
| 3037 – 3156 | Additional KERNEL32: `GetModuleHandleA`, `VirtualProtect`, `VirtualQuery` (parses `/proc/self/maps`), `CreateDirectoryW`, `FindFirstFileW`, `FormatMessageW`, `GetFullPathNameW`, `LocalFree` |
| 3157 | `#include "shim_kernel32_sync.hpp"` |
| 3159 – 3197 | Global memory / heap, file attributes |
| 3199 – 3222 | `FileTimeToSystemTime` |
| 3224 – 3275 | `GetSystemInfo`, `GlobalMemoryStatus` (via `sysinfo()`), `RtlAddFunctionTable` stub |
| 3277 – 3517 | Thread pseudo-handle, affinity, context, `GetProcessTimes`, handle info, `DuplicateHandle` (with pseudo-handle `-2` translation), `TryEnterCriticalSection`, `WaitForMultipleObjects` with rollback |
| 3519 – 3557 | Console extras (title, screen buffer info, `OutputDebugString{A,W}`) |
| 3559 – 3641 | VEH stubs, temp path/file, `SetCurrentDirectoryW`, `FileTimeToLocalFileTime` |
| 3642 – 3667 | `GlobalMemoryStatusEx` (echoes caller's `dwLength`) |
| 3669 – 3745 | shell32 / shlwapi / winmm: `CommandLineToArgvW`, `PathMatchSpec{A,W}`, `timeGetTime` |
| 3747 – 3778 | `SetConsoleCtrlHandler` over `signal(SIGINT)` |
| 3780 – 3812 | `DeleteFileW`, `RemoveDirectoryW`, `MoveFileW`, `CreateHardLink{A,W}` |
| 3814 – 3855 | `GetFileInformationByHandle`, `GetFileTime` |
| 3857 – 3917 | `GetSystemTime`, `SystemTimeToFileTime`, tz-specific conversions, `LocalFileTimeToFileTime` |
| 3919 – 3995 | `GetVersionExW` (reports Windows 7 SP1 x64), `GetSystemDirectory{A,W}`, `GetVolumeInformation{A,W}`, `GetDiskFreeSpaceEx{A,W}`, `GetDriveTypeW` |
| 3997 – 4067 | `GetFullPathNameA`, `GetLongPathName{A,W}`/`GetShortPathName{A,W}` identity stubs, `ExpandEnvironmentStrings{A,W}` |
| 4069 – 4113 | `FoldString{A,W}`, `CompareStringA` |
| 4115 – 4129 | `CreateEventW`/`CreateSemaphoreW`/`WaitForSingleObjectEx`/`LoadLibraryW` wrappers |
| 4131 – 4155 | `SetEnvironmentVariableA`, error-mode / priority / thread-execution / backup stubs, `DeviceIoControl` |
| 4157 – 4209 | advapi32 — token, sid, security descriptor, registry stubs, `CryptGenRandom` via `/dev/urandom` |
| 4211 – 4251 | shell32 stubs incl. `SHGetMalloc` returning a minimal IMalloc COM vtable |
| 4253 – 4303 | user32 — `CharLower`/`CharUpper`, `CharToOem` / `OemToChar` (passthrough; UTF-8 round-trip), `ExitWindowsEx` |
| 4304 – 4399 | Resource directory parsing (RT_STRING) for `LoadString{A,W}`, `MessageBeep` |
| 4404 – 4408 | `user32_CharUpperA` |
| 4410 – 4518 | kernel32 A-variant wrappers (`MoveFileA`, `RemoveDirectoryA`, `SetCurrentDirectoryA`, `ExpandEnvironmentStringsA`, `LoadLibraryExA`, drive/volume A variants, `GetVersion`, `GetVersionExA`, `ReadConsoleA`, `RtlFillMemory`, `RtlCompareMemory`) |
| 4520 – 4548 | advapi32 A-variant stubs |
| 4550 – 4559 | shell32 A-variant stubs |
| 4561 | `#include "shim_msvcrt.hpp"` |

---

## 3. Build Integration (actual)

From `Makefile`:

```make
SHIM_FLAGS   = -O2 -fPIC -shared -m64 -std=c++17 \
               -fvisibility=hidden \
               -Wall -Wextra -Wno-unused-parameter \
               -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -I.
SHIM_LDFLAGS = -lpthread -ldl \
               -Wl,--version-script=shim.map \
               -Wl,-z,now -Wl,-soname,winapi_shim.so

$(SHIM_OUT): $(SHIM_SRCS) shim_types.h shim.map
        $(CC) $(SHIM_FLAGS) -o $@ $(SHIM_SRCS) $(SHIM_LDFLAGS)

$(SHIM_DBG_OUT): $(SHIM_SRCS) shim_types.h shim.map
        $(CC) $(SHIM_DBG_FLAGS) -DWINAPI_LOG_ENABLED -o $@ $(SHIM_SRCS) $(SHIM_DBG_LDFLAGS)
```

Both build targets compile `shim.cpp` as a single TU. `_FILE_OFFSET_BITS=64`
is on, so `lseek`/`off_t` are 64-bit (B17/R30); the source no longer uses
`lseek64`/`off64_t`. The Makefile comments call out `-DUSE_MIMALLOC` /
`-DUSE_JEMALLOC` as opt-in replacements for `Heap*` backing (R49 path).

---

## 4. Status of the Original Refactoring Phases

### Phase 1 — Emergency correctness — landed

| # | Task | Where |
|---|---|---|
| R1  | B1 — `build_env_block` frees `g_env_block` on wide-allocation failure | `shim.cpp:789-794` |
| R2  | B2 — `handle_alloc_*` populate under `g_handles_mu`; lookups take the mutex; refcounted `FindCtx` / sync objects | `shim.cpp:416-506`, `shim_kernel32_sync.hpp:18-31` |
| R3  | B3 — `GetCurrentDirectoryA` no longer leaks; uses fixed stack buffer | `shim.cpp:2607-2617` |
| R4  | B4 — `SetFileAttributesA` checks `stat` return | `shim.cpp:2587` |
| R5  | B5 — `utf8_to_wchar` skips continuation bytes after `?` | `shim.cpp:611-613` |
| R6  | B6 — `WideCharToMultiByte` honours `srclen` | `shim.cpp:2209-2213` |
| R7  | B7 — `CompareStringW` honours `n1`/`n2` | `shim.cpp:2291-2300` |
| R8  | B8 — distinct `WIN32_FIND_DATAW`; `FindFirstFileExW` / `FindNextFileW` use `fill_find_data_w` | `shim_types.h:77-88`, `shim.cpp:1589-1592` |
| R9  | B9 — `VirtualFree(MEM_RELEASE)` requires `size==0`; mmap tracker; `MEM_DECOMMIT` uses `mprotect`+`madvise` | `shim.cpp:1265-1279` |
| R10 | B10 — `WriteConsoleW` bounded by `nChars` | `shim.cpp:1793-1796` |
| R11 | B18a — `GetModuleFileNameA` guards `size==0` | `shim.cpp:2632` |
| R12 | N1 — per-thread TLS array (pthread-key destructor) | `shim.cpp:96-110, 250-253` |
| R13 | B21 — no PPMonstr hardcode in current source | n/a |
| R14 | B22 — `ERROR_TOO_MANY_OPEN_FILES` named everywhere | shim.cpp throughout |
| R15 | Header hygiene — `<sys/prctl.h>` (replaced by `<asm/prctl.h>`), `<sys/uio.h>`, `<sys/utsname.h>`, `<wchar.h>` not included | `shim.cpp:7-39` |

### Phase 2 — Modular extraction — partially landed differently

The wholesale per-section split was not done. Internal cohesion (file-scope
statics shared across sections without forward-declaration ceremony) was
preferred over file-count. The split that did land:

| Done | Where |
|---|---|
| `shim_kernel32_sync.hpp` extracted from `shim.cpp` | `shim_kernel32_sync.hpp` |
| `shim_msvcrt.hpp` extracted from `shim.cpp` | `shim_msvcrt.hpp` |
| Runtime-configurable logging via `WINAPI_SHIM_LOG=path|stderr` | `shim.cpp:50-65` |
| `fill_find_data_common` template + `fill_find_data_{a,w}` (I1) | `shim.cpp:1575-1597` |
| `make_open_flags` helper (I2) | `shim.cpp:632-658` |
| Shared `find_ctx_open` + `find_first_posix` (I3) | `shim.cpp:1624-1674, 2489-2503` |
| Named `LCMAP_*` / `NORM_*` / `CSTR_*` / `CT_CTYPE*` / `C1_*` constants (I6) | `shim_types.h:217-236` |
| `static_assert` size checks (I7) | `shim.cpp:151-155` |

Deferred (kept inlined in `shim.cpp`):

| Not done | Reason |
|---|---|
| Separate `shim_log.cpp`, `shim_path.cpp`, `shim_handles.cpp`, `shim_init.cpp`, `shim_file.cpp`, `shim_dir.cpp`, `shim_console.cpp`, `shim_module.cpp`, `shim_time.cpp`, `shim_sync.cpp`, `shim_string.cpp`, `shim_except.cpp`, `shim_misc.cpp` | Single-TU build is fast; helpers share file-scope statics; cost of adding a `shim_internal.h` API surface outweighed benefit |
| Uniform logging conventions (I4) | Still mixed: some paths use `LOG(name, fmt, …)` (compiled out unless `WINAPI_LOG_ENABLED`), others use `log_always(...)` (writes to `WINAPI_SHIM_LOG` whenever set) |
| Hidden-visibility per-TU objects | All sources compile to one shared object; visibility is enforced by the `EXPORT` macro and `shim.map` instead |

### Phase 3 — Semantic hardening — landed

| # | Task | Where |
|---|---|---|
| R26 | B13 — image base via `dl_iterate_phdr` + PT_LOAD scan; also caches PE-header base for resource lookup | `shim.cpp:942-976` |
| R27 | B14 — typed `FAKE_WIN_MODULE` / `MAIN_IMAGE_MODULE` pseudo-handles | `shim.cpp:1816-1819` |
| R28 | B15 — `SetStdHandle` calls `dup2(new_fd, idx)` | `shim.cpp:1381` |
| R29 | B16 — last-error mirrored to TEB+0x68 via `SET_LAST_ERROR` | `shim.cpp:116-119` |
| R30 | B17 — `_FILE_OFFSET_BITS=64` on; `lseek` / `off_t` everywhere | `Makefile:12`, `shim.cpp:1489, 2671, 2685, …` |
| R31 | B18b — `GetModuleFileNameW`/`A` resolve loaded modules via `dlsym("_init")` + `dladdr` | `shim.cpp:1856-1871, 2638-2647` |
| R32 | B19 — `LoadLibrary*` paths through `win_path_to_posix` | `shim.cpp:1886-1887` |
| R33 | B20 — `FlsAlloc`/`FlsFree` allocate from shared TLS bitset; per-thread destructor armed via `pthread_key` | `shim.cpp:2768-2870` |
| R34 | B23 — `SetEnvironmentVariableW` invalidates both `g_env_block_w` and `g_env_block` | `shim.cpp:2009-2012` |
| R35 | B35 — `errno_to_win32` covers `EEXIST`, `EMFILE`, `ENOSPC`, `ENOTEMPTY`, `EAGAIN`, `EBUSY`, `ETIMEDOUT`, `EINTR`, `ENAMETOOLONG`, `ENOSYS`, `ENOTSUP` | `shim.cpp:121-143` |
| R36 | B36 — `UnhandledExceptionFilter` logs and terminates instead of returning | `shim.cpp:2335-2356` |
| R37 | B37 — `RtlCaptureContext` portable inline asm; B38 — AS-safe crash banner via raw `SYS_write` + `crash_write_{int,hex,lit}` | `shim.cpp:854-915, 2395-2415` |
| R38 | I8 — `pthread_create` interceptor wraps every thread with `shim_thread_attach` | `shim.cpp:300-335` |
| R39 | B11 — `HeapReAlloc(size=0)` clamps to 1; B12 — `prot_from_protect` logs unknown bits and defaults to RW | `shim.cpp:1217-1234, 1312-1332` |
| R40 | B39 — `MAP_FIXED_NOREPLACE` with `MAP_FIXED` fallback | `shim.cpp:1242-1254` |
| R41 | B40 — `RtlUnwindEx` / `RtlUnwind` log + return instead of `abort()` | `shim.cpp:2358-2373` |

### Phase 4 — Compatibility extensions — landed

| # | Task | Where |
|---|---|---|
| R42 | B28 — `ReadConsoleInput{A,W}` build `INPUT_RECORD` from `read(fd, …)` | `shim.cpp:3008-3031` |
| R43 | B32 — `GetConsoleMode` derives flags from `tcgetattr` | `shim.cpp:1757-1776` |
| R44 | B27 — `GetStringTypeW`/`A` return CT_CTYPE1 via `classify_ctype1` | `shim.cpp:2256-2286, 2441-2452` |
| R45 | B29 — `IsProcessorFeaturePresent` reads CPUID leaves 1 and 0x80000001 | `shim.cpp:1168-1200` |
| R46 | B30 — `FormatMessageA` expands `%N!fmt!` positional escapes | `shim.cpp:2902-2974` |
| R47 | B31 — `FileTimeToDosDateTime` returns FALSE for pre-1980 timestamps | `shim.cpp:2737-2741` |
| R48 | musl path — `malloc_usable_size` stub when not glibc; libc backtrace gated on `__GLIBC__` | `shim.cpp:16-19, 1141-1153` |
| R49 | mimalloc/jemalloc — Makefile comment documents `-DUSE_MIMALLOC -lmimalloc` / `-DUSE_JEMALLOC -ljemalloc` opt-in | `Makefile:14-15` |
| R50 | aarch64 — TEB pointer stashed in reserved `x18` register | `shim.cpp:282-283` |

---

## 5. Features Added Beyond the Original Plan

These were not in the original document but exist in the current code; track
them so they don't get re-proposed.

| Area | Detail | Where |
|---|---|---|
| PE TLS directory | `shim_register_tls` called by pe2elf trampoline before `PE_ENTRY`; allocates static TLS slot, populates per-thread block from template VA, fires DLL_PROCESS_ATTACH callbacks; `tls_static_init_thread` re-runs for every new thread; destructor fires DLL_PROCESS_DETACH | `shim.cpp:978-1082, 1087-1089` |
| Sync primitives (full) | `CreateMutex` / `CreateEvent` / `CreateSemaphore` / `CreateThread` / `ExitThread` / `GetExitCodeThread` with refcounted lifetimes; `WaitForSingleObject` dispatches over `pthread_mutex_timedlock` / `pthread_cond_timedwait` / `sem_timedwait`; `WaitForMultipleObjects` polls with rollback on partial acquisition; `SignalObjectAndWait` | `shim_kernel32_sync.hpp` |
| `SuspendThread`/`ResumeThread` | `SIGUSR1` handler with per-thread `sem_t suspend_sem`; transitions guarded by `__atomic` on `suspend_count` so multiple suspend/resume pairs nest correctly | `shim.cpp:3284-3331, shim_kernel32_sync.hpp:351-356` |
| `DuplicateHandle` | Translates `GetCurrentThread()` pseudo-handle (`-2`) into a real `H_THREAD` slot caching a `ThreadObj`; refcount-shares non-file handles | `shim.cpp:3379-3452` |
| `_beginthreadex` / `_endthreadex` | Thin wrappers around `CreateThread` / `ExitThread` | `shim_msvcrt.hpp:545-555` |
| `_setjmp` / `longjmp` | Hand-written `naked` MS-ABI versions matching Windows x64 `JUMP_BUFFER` layout | `shim_msvcrt.hpp:562-600` |
| `qsort` | Custom intro-style sort calling the `ms_abi` comparator directly (avoids SYSV wrapper round-trip) | `shim_msvcrt.hpp:451-504` |
| `scanf` | Single `read(STDIN_FILENO, …)` + minimal `%d`/`%s`/`%c` parser | `shim_msvcrt.hpp:509-538` |
| `printf` / `sprintf` / `fprintf` / `vfprintf` | `ms_vformat` parses `%[flags][width][.prec][len]conv` against MS-ABI `va_list` (which is `char*` on x86-64, advanced 8 bytes per arg) | `shim_msvcrt.hpp:28-107, 325-342` |
| CRT locking | 32 recursive `pthread_mutex_t` per lock ID | `shim_msvcrt.hpp:128-154` |
| `__getmainargs` / `__wgetmainargs` | argv built from `/proc/self/cmdline`; wide envp synthesised from `environ` | `shim_msvcrt.hpp:171-178, 245-274` |
| `__iob_func` | Fake Windows `_iobuf[3]` array with `(fd, flag)` for stdin/stdout/stderr; `win_file_to_fd` translates pointers back into POSIX fds | `shim.cpp:813-848, shim_msvcrt.hpp:9-16` |
| `_time64` family | All `_time64`/`_gmtime64`/`_localtime64`/`_mktime64` route to libc; `strftime` passthrough | `shim_msvcrt.hpp:300-320` |
| Resource directory parsing | `LoadString{A,W}` walks PE `.rsrc` (RT_STRING = 6); handles named/id directories, first language | `shim.cpp:4304-4398` |
| `VirtualQuery` | Reads `/proc/self/maps` to fill MEMORY_BASIC_INFORMATION | `shim.cpp:3061-3096` |
| `CommandLineToArgvW` | Two-pass parse with quote handling; returns a single `malloc`’d block (caller `LocalFree`s) | `shim.cpp:3676-3720` |
| `PathMatchSpec{A,W}` | Wraps `win_fnmatch` on basename | `shim.cpp:3722-3738` |
| `SetConsoleCtrlHandler` | Up to 8 handlers, `signal(SIGINT)` invokes them LIFO | `shim.cpp:3747-3778` |
| `CryptGenRandom` | Reads `/dev/urandom` | `shim.cpp:4204-4208` |
| `SHGetMalloc` | Minimal IMalloc COM vtable (9 slots, all `ms_abi`); `Alloc`/`Realloc`/`Free` route to libc | `shim.cpp:4220-4248` |
| `RtlPcToFileHeader` | Resolves via `dladdr` | `shim.cpp:2417-2427` |
| `GetVersionExW` / `GetVersionExA` / `GetVersion` | Report Windows 7 SP1 x64 (6.1.7601, Service Pack 1) | `shim.cpp:3924-3942, 4482-4503` |
| `GlobalMemoryStatus` / `GlobalMemoryStatusEx` | Backed by `sysinfo()`; Ex echoes caller’s `dwLength` | `shim.cpp:3256-3270, 3645-3667` |
| `GetDiskFreeSpace{,Ex}{A,W}` | Backed by `statvfs("/")`; clusters scaled into sane 32-bit ranges | `shim.cpp:3979-3994, 4461-4481` |
| `posix_to_win_path` | Prefixes `C:` and switches `/` → `\\` so callers doing `wcsrchr(path, '\\')` find a separator; `win_path_to_posix` reverses it for opens | `shim.cpp:551-561` |
| `SetUnhandledExceptionFilter` | Stores filter pointer but never invokes (cannot safely call `ms_abi` from a signal handler) | `shim.cpp:853, 2328-2356` |

---

## 6. Open / Deferred

Nothing on the original Phase 1 list is open. Items still worth keeping in
mind:

| Topic | Current state |
|---|---|
| Unified logging conventions (I4) | Mixed `LOG()` / `log_always()` usage across sections |
| Per-section file split (R17 – R20) | Deliberately deferred; revisit if `shim.cpp` exceeds ~7 000 lines or if multiple contributors collide on it |
| `SetUnhandledExceptionFilter` callback | Filter pointer is recorded but never called; calling `ms_abi` from a fatal signal context is unsafe — needs a deferred-execution helper if anyone genuinely needs Windows-style top-level filter chaining |
| `LoadLibrary` of arbitrary Windows DLLs | Out of scope — pe2elf flattens the import graph at conversion time; `FAKE_WIN_MODULE` sentinel routes `GetProcAddress` to `RTLD_DEFAULT` over the shim’s own exports |
| `RtlUnwindEx` / SEH | Logs and returns; real SEH unwind not implemented. C++ EH from MSVC code that genuinely throws across the shim boundary will likely terminate |
| `GetThreadContext` / `SetThreadContext` | Stubbed to return `FALSE` with `ERROR_INVALID_FUNCTION` |
| Vectored Exception Handlers | Stubs only (no VEH equivalent on Linux without a full signal-handler reroute) |
| aarch64 | TEB stashed in `x18` but no `__readgsqword` shim wired up; MSVC PE inlined TEB accesses won’t work without per-port asm helpers |
| musl backtrace | `log_backtrace` is empty when not glibc; consider `libunwind` if backtraces matter on musl |

---

*End of document.*
