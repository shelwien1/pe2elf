# shim — Current Architecture and Outstanding Work

Assumptions: little-endian host; primary target glibc on Linux x86-64 with
graceful degradation toward musl/aarch64 where cheap.

---

## 1. Current Layout

The shim builds as a single translation unit: `shim.cpp` holds the
pre-export infrastructure (fake TEB/PEB, handle table, path encoding,
mmap tracker, signal handler, image-base discovery, PE TLS directory,
constructor) and `#include`s a series of per-feature headers that
contribute the WinAPI export surface.  Headers share file-scope statics
with `shim.cpp` directly — no `shim_internal.h` indirection.

| File | Role | Lines |
|---|---|---|
| `shim.cpp` | Pre-export infrastructure + the orchestration sequence of `#include`s.  All Windows-side exports live in the per-feature headers below. | ~1 240 |
| `shim_types.h` | Windows-shaped primitive types, struct layouts (`FILETIME`, `SYSTEMTIME`, `LARGE_INTEGER`, `CRITICAL_SECTION`, `WIN32_FIND_DATA{A,W}`, `STARTUPINFO{A,W}`, `CPINFO`), error codes, file/heap/mem/page/exception flags, `LCMAP_*` / `NORM_*` / `CSTR_*` / `CT_CTYPE*` / `C1_*` constants, and inline `FILETIME` ↔ `uint64_t` helpers. | 236 |
| `shim.map` | Linker version script.  Lists every dynamic export by name; everything else is `local: *`. | 368, 355 symbols |
| `shim_kernel32_proc.hpp` | 7.1 Process / Identity: GetCurrentProcess/ProcessId/ThreadId (TEB+0x48 read), ExitProcess, TerminateProcess, IsDebuggerPresent, IsProcessorFeaturePresent (CPUID), plus the `log_backtrace` helper (glibc `backtrace()` or libgcc `_Unwind_Backtrace`). | ~115 |
| `shim_kernel32_smallstubs.hpp` | 7.2 Error State (GetLastError/SetLastError), 7.10 Time/Performance (QPC/QPF/GetTickCount), 7.14 Pointer Encoding (Encode/DecodePointer identity stubs). | ~50 |
| `shim_kernel32_mem.hpp` | 7.3 Memory: `VirtualAlloc` / `VirtualFree` (mmap tracker, `MAP_FIXED_NOREPLACE` fallback), `Heap*` over libc malloc. | ~140 |
| `shim_kernel32_file.hpp` | 7.4 File I/O + 7.5 File Times + 7.6 Directory/File Search.  Owns the shared `stat_to_win_attrs`, `fill_find_data_*`, `win_fnmatch`, `find_ctx_open` helpers used by both the W- and A-variants. | ~410 |
| `shim_kernel32_console.hpp` | 7.7 Console I/O: GetConsoleCP/OutputCP, GetConsoleMode (tcgetattr), WriteConsoleA/W. | ~67 |
| `shim_kernel32_module.hpp` | 7.8 Module/Library: `FAKE_WIN_MODULE` / `MAIN_IMAGE_MODULE` pseudo-handles, GetModuleHandle / GetModuleFileName (dladdr-based), LoadLibraryExW, FreeLibrary, GetProcAddress. | ~140 |
| `shim_kernel32_startup.hpp` | 7.9 Startup/Command Line/Environment: GetCommandLine{A,W}, GetStartupInfo{A,W}, GetEnvironmentStrings{A,W} (with cache invalidation), FreeEnvironmentStrings{A,W}, SetEnvironmentVariableW. | ~80 |
| `shim_kernel32_critsec.hpp` | 7.11 Synchronization (in-process): CRITICAL_SECTION as recursive pthread_mutex, TlsAlloc/Free/Get/Set (GS:[0x58] per-thread slot array), InitializeSListHead. | ~109 |
| `shim_kernel32_string.hpp` | 7.13 String/Code Page: GetACP/OEMCP, IsValidCodePage, GetCPInfo, MultiByte/WideChar, LCMapStringW (UPPER/LOWERCASE), classify_ctype1 + GetStringTypeW, CompareStringW. | ~171 |
| `shim_kernel32_except.hpp` | 7.15 Exception/SEH: SetUnhandledExceptionFilter (atomic), UnhandledExceptionFilter (dispatches VEH chain + top-level filter), RtlUnwind/RtlUnwindEx (log+return), RtlVirtualUnwind / RtlLookupFunctionEntry stubs, RtlCaptureContext (Rsp/Rbp/Rip), RtlPcToFileHeader (dladdr), RaiseException (synthesises EXCEPTION_POINTERS + VEH dispatch). | ~164 |
| `shim_kernel32_miscstubs.hpp` | GetStringTypeA, LCMapStringA, Sleep. | ~49 |
| `shim_kernel32_file_a.hpp` | A-variant file/directory: FindFirstFile{A,Ex}/FindNextFileA (reuse `find_ctx_open`), CreateFileA (with CON/CONIN$/CONOUT$ console-alias mapping), DeleteFileA, SetFileAttributes{A,W}, GetCurrentDirectory{A,W}, GetModuleFileNameA, LoadLibraryA. | ~185 |
| `shim_kernel32_filetime.hpp` | SetFilePointer (non-Ex), SetFileTime, SetEndOfFile, FILETIME ↔ DOS date/time. | ~106 |
| `shim_kernel32_fls.hpp` | FLS: shares the slot bitset with TLS; `shim_thread_exit` (single pthread_key destructor for the per-thread slots array, forward-declared in shim.cpp and defined here so it can see `g_fls_callbacks`). | ~111 |
| `shim_kernel32_locale.hpp` | GetLocaleInfoA/W (tiny synthesised locale), FormatMessageA + `format_message_expand` for `%N!fmt!` positional escapes. | ~109 |
| `shim_kernel32_console_misc.hpp` | ReadConsoleW, ReadConsoleInput{A,W} over termios+read(), SetHandleCount. | ~63 |
| `shim_kernel32_misc.hpp` | GetModuleHandleA, IsDBCSLeadByteEx, VirtualProtect, VirtualQuery (parses /proc/self/maps), CreateDirectoryW, FindFirstFileW (delegates to ExW), FormatMessageW, GetFullPathNameW, LocalFree. | ~130 |
| `shim_kernel32_sync.hpp` | Sync-handle surface: generic handle allocator, `WaitForSingleObject` dispatcher, CreateMutex / CreateEvent / CreateSemaphore / CreateThread (+ trampoline that wires shim_init_teb / run_tls_callbacks / tls_static_init_thread) / ExitThread / GetExitCodeThread, `undo_wait_acquire`, SignalObjectAndWait. | 518 |
| `shim_kernel32_sysinfo.hpp` | GlobalAlloc/Free, GetFileAttributes{A,W}, CreateDirectoryA, FileTimeToSystemTime, GetSystemInfo, GlobalMemoryStatus, RtlAddFunctionTable stub. | ~124 |
| `shim_kernel32_thread.hpp` | GetCurrentThread (-2 pseudo-handle), Suspend/ResumeThread (SIGUSR1 + per-ThreadObj sem_t), GetThreadPriority/Context (current-thread delegates to RtlCaptureContext), GetProcessAffinityMask, GetProcessTimes, GetHandleInformation, DuplicateHandle (with pseudo-handle -2 translation), TryEnterCriticalSection, WaitForMultipleObjects with rollback. | ~268 |
| `shim_kernel32_console_extras.hpp` | GetConsoleTitle{A,W}, SetConsoleTitle{A,W}, GetConsoleScreenBufferInfo, OutputDebugString{A,W}. | ~42 |
| `shim_kernel32_veh.hpp` | Vectored Exception Handler: doubly-linked handler list, Add/Remove (head/tail insertion per `First` flag, membership-checked remove), `run_vectored_handlers` snapshot + dispatch. | ~79 |
| `shim_kernel32_tail.hpp` | Big late-included bundle: Temp file/path, SetCurrentDirectoryW, FileTimeToLocalFileTime, GlobalMemoryStatusEx, shell32/shlwapi/winmm (CommandLineToArgvW, PathMatchSpec, timeGetTime), SetConsoleCtrlHandler, DeleteFileW/RemoveDirectoryW/MoveFileW/CreateHardLink{A,W}, GetFileInformationByHandle, GetFileTime, GetSystemTime + SystemTimeToFileTime + tz, LocalFileTimeToFileTime, GetVersionExW, GetSystemDirectory{A,W} / GetVolumeInformation{A,W} / GetDiskFreeSpaceEx{A,W} / GetDriveTypeW, GetFullPathNameA, GetLongPathName{A,W} / GetShortPathName{A,W}, ExpandEnvironmentStringsW, FoldString{A,W}, CompareStringA, CreateEventW / CreateSemaphoreW / WaitForSingleObjectEx / LoadLibraryW wrappers, SetEnvironmentVariableA + IsDBCSLeadByte / SetErrorMode / SetPriorityClass / SetThreadExecutionState / BackupRead / BackupSeek / DeviceIoControl stubs. | ~614 |
| `shim_advapi32.hpp` | advapi32 surface: token / SID / security-descriptor / registry stubs, CryptGenRandom via /dev/urandom, A- and W-variants both. | ~90 |
| `shim_shell32.hpp` | shell32 surface: SHFileOperation / SHGetPathFromIDList stubs, SHGetMalloc with a minimal IMalloc COM vtable, A- and W-variants both. | ~61 |
| `shim_user32.hpp` | user32 surface: CharLower/Upper{A,W}, CharToOem/OemToChar{A,W,BuffA,BuffW}, ExitWindowsEx, LoadString{A,W} backed by PE-resource directory parsing, MessageBeep. | ~160 |
| `shim_kernel32_a.hpp` | kernel32 A-variant wrappers and tail-end stubs: MoveFileA, RemoveDirectoryA, SetCurrentDirectoryA, ExpandEnvironmentStringsA, LoadLibraryExA, GetDriveTypeA, GetDiskFreeSpace{A,W}, GetVersionExA, GetVersion, ReadConsoleA, RtlFillMemory, RtlCompareMemory. | ~118 |
| `shim_msvcrt.hpp` | `msvcrt_*` surface: MS-ABI variadic formatter, `__getmainargs` / `__wgetmainargs`, fake `__iob_func`, `_initterm`, CRT locking, `_time64` family, `qsort`, `scanf`, `_beginthreadex`/`_endthreadex`, MS-ABI `_setjmp`/`longjmp`.  Always the last `#include` in shim.cpp. | 600 |

Everything is built with `-fvisibility=hidden`; `EXPORT` re-promotes only the
WinAPI surface, and the version script narrows it further.  Two outputs are
produced from the same sources: `winapi_shim.so` (release) and
`winapi_shim_dbg.so` (`-DWINAPI_LOG_ENABLED`, `-O0 -g`).

The original plan deferred a per-section file split.  That deferral has now
been lifted — `shim.cpp` shrank from ~4 690 lines to ~1 240, and 27 per-feature
headers carry the rest.  All static state stays defined in `shim.cpp` and the
headers reference it directly; no `shim_internal.h` was introduced (the per-TU
visibility argument never applied because everything is still one TU).
Include order in `shim.cpp` is significant: helpers needed by later headers
(e.g. `find_ctx_open`, `kernel32_WriteFile`, `kernel32_WaitForSingleObject`,
`kernel32_LoadLibraryExW`) are defined in earlier headers.

---

## 2. Section Map (shim.cpp)

`shim.cpp` is now divided into two parts: pre-export infrastructure
(file-scope statics, helpers, the constructor) and an orchestration tail
(a sequence of `#include`s that pull in the per-feature WinAPI headers).
Treat each header for its content; the file table in §1 lists what each
provides.

### Pre-export infrastructure (file-scope, hidden visibility)

| Lines | Section |
|---|---|
| 41 – 85   | Visibility, logging (`WINAPI_SHIM_LOG=path|stderr`, `WINAPI_LOG_ENABLED` build flag forces the file open + extra `RtlCaptureContext` stack dump) |
| 87 – 148  | TLS last-error, per-thread `tls_slots` allocator with single `pthread_key` destructor (`shim_thread_exit`, forward-declared here, defined in `shim_kernel32_fls.hpp`), `SET_LAST_ERROR` macro mirroring TEB+0x68 (B16/R29), `errno_to_win32`, compile-time size assertions (I7) |
| 150 – 225 | Fake PEB construction (`init_fake_peb`): PEB_LDR_DATA empty lists, RTL_USER_PROCESS_PARAMETERS with stdio handles, ProcessHeap stub |
| 227 – 285 | `shim_init_teb` / `shim_thread_attach`: per-thread TEB, GS register on x86-64 / x18 on aarch64, real stack bounds via `pthread_getattr_np` |
| 288 – 326 | `pthread_create` interceptor (I8): trampoline that calls `shim_thread_attach` before user fn |
| 328 – 497 | Handle table — `H_FREE`/`H_FILE`/`H_FIND`/`H_MODULE`/`H_MUTEX`/`H_EVENT`/`H_SEMAPHORE`/`H_THREAD`; refcounted `FindCtx`, refcounted sync structs; `handle_alloc_*` populate atomically under `g_handles_mu` |
| 499 – 618 | Path translation (`win_path_to_posix`, `posix_to_win_path`, `path_join`) and UTF-8 ↔ UTF-16 (`wchar_to_utf8`, `utf8_to_wchar` with continuation-byte skip — B5) |
| 620 – 649 | `make_open_flags` (I2) — Windows access/disposition → POSIX `O_*` |
| 651 – 687 | mmap tracker for `VirtualAlloc`/`VirtualFree` (B9/R9), max 4 096 mappings |
| 689 – 793 | Process state — cmdline parsed from `/proc/self/cmdline` with shell-style quoting, env block (UTF-8 + UTF-16 caches with on-demand regen, B23/R34), image-base discovery (R26 via `dl_iterate_phdr` + PE-header scan), `g_pe_base` for resource lookup |
| 795 – 839 | msvcrt CRT state — `g_main_argc`/`g_main_argv` (built from `/proc/self/cmdline`), fake Windows `_iobuf` array for `__iob_func` |
| 841 – 928 | Signal/crash handler — AS-safe `crash_write_*` helpers via raw `SYS_write`, register/backtrace dump, signal table (`SIGSEGV`, `SIGILL`, `SIGFPE`, `SIGBUS`, `SIGABRT`, `SIGUSR1` for `SuspendThread`) |
| 930 – 967 | Image base discovery via `dl_iterate_phdr` PT_LOAD scan (B13/R26) |
| 969 – 1073 | PE TLS directory — `shim_register_tls` (called by pe2elf startup thunk before `PE_ENTRY`), `run_tls_callbacks` (DLL_PROCESS/THREAD_ATTACH/DETACH), `tls_static_init_thread` (per-thread static-TLS block) |
| 1075 – 1102 | `__attribute__((constructor)) shim_init` and `__attribute__((destructor)) shim_fini` |

### Orchestration: header includes (in file order)

| Header | Purpose (see §1 for full surface) |
|---|---|
| `shim_kernel32_proc.hpp` | 7.1 Process / Identity + `log_backtrace` |
| `shim_kernel32_smallstubs.hpp` | 7.2 Error State + 7.10 Time/Performance + 7.14 Pointer Encoding |
| `shim_kernel32_mem.hpp` | 7.3 Memory |
| `shim_kernel32_file.hpp` | 7.4 File I/O + 7.5 File Times + 7.6 Directory/File Search (provides helpers reused by file_a) |
| `shim_kernel32_console.hpp` | 7.7 Console I/O |
| `shim_kernel32_module.hpp` | 7.8 Module / Library |
| `shim_kernel32_startup.hpp` | 7.9 Startup / Command Line / Environment |
| `shim_kernel32_critsec.hpp` | 7.11 Synchronization (CRITICAL_SECTION + TLS + SListHead) |
| `shim_kernel32_string.hpp` | 7.13 String / Code Page |
| `shim_kernel32_except.hpp` | 7.15 Exception / SEH (declares run_vectored_handlers forward) |
| `shim_kernel32_miscstubs.hpp` | Sleep, GetStringTypeA, LCMapStringA |
| `shim_kernel32_file_a.hpp` | A-variant file/directory (requires file.hpp's helpers) |
| `shim_kernel32_filetime.hpp` | SetFilePointer / SetFileTime / SetEndOfFile / DOS date-time |
| `shim_kernel32_fls.hpp` | FLS + `shim_thread_exit` definition |
| `shim_kernel32_locale.hpp` | GetLocaleInfo, FormatMessageA |
| `shim_kernel32_console_misc.hpp` | ReadConsoleW, ReadConsoleInput, SetHandleCount |
| `shim_kernel32_misc.hpp` | GetModuleHandleA, VirtualQuery (proc/self/maps), CreateDirectoryW, FindFirstFileW, FormatMessageW, GetFullPathNameW, LocalFree |
| `shim_kernel32_sync.hpp` | CreateMutex/Event/Semaphore/Thread family + WaitForSingleObject (relied on by `shim_kernel32_thread.hpp`) |
| `shim_kernel32_sysinfo.hpp` | GlobalAlloc/Free, file attrs, FileTimeToSystemTime, GetSystemInfo, GlobalMemoryStatus, RtlAddFunctionTable |
| `shim_kernel32_thread.hpp` | Thread pseudo-handle, Suspend/Resume, DuplicateHandle, TryEnterCriticalSection, WaitForMultipleObjects |
| `shim_kernel32_console_extras.hpp` | Console title / screen buffer / OutputDebugString |
| `shim_kernel32_veh.hpp` | Vectored Exception Handler (defines `run_vectored_handlers` forward-declared in except.hpp) |
| `shim_kernel32_tail.hpp` | Big bundle: Temp file/path, SetCurrentDirectoryW, FileTimeToLocalFileTime, GlobalMemoryStatusEx, shell32/shlwapi/winmm, SetConsoleCtrlHandler, file ops, system info, paths, FoldString, CompareStringA, Event/Sem wrappers, misc stubs |
| `shim_advapi32.hpp` | advapi32 (main + A-variants) |
| `shim_shell32.hpp` | shell32 (main + IMalloc + A-variants) |
| `shim_user32.hpp` | user32 + LoadString resource walk |
| `shim_kernel32_a.hpp` | kernel32 A-variant wrappers |
| `shim_msvcrt.hpp` | msvcrt_* surface (last include) |

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
| R1  | B1 — `build_env_block` frees `g_env_block` on wide-allocation failure | `shim.cpp` (process state section) |
| R2  | B2 — `handle_alloc_*` populate under `g_handles_mu`; lookups take the mutex; refcounted `FindCtx` / sync objects | `shim.cpp` (handle table), `shim_kernel32_sync.hpp` |
| R3  | B3 — `GetCurrentDirectoryA` no longer leaks; uses fixed stack buffer | `shim_kernel32_file_a.hpp` |
| R4  | B4 — `SetFileAttributesA` checks `stat` return | `shim_kernel32_file_a.hpp` |
| R5  | B5 — `utf8_to_wchar` skips continuation bytes after `?` | `shim.cpp` (path translation) |
| R6  | B6 — `WideCharToMultiByte` honours `srclen` | `shim_kernel32_string.hpp` |
| R7  | B7 — `CompareStringW` honours `n1`/`n2` | `shim_kernel32_string.hpp` |
| R8  | B8 — distinct `WIN32_FIND_DATAW`; `FindFirstFileExW` / `FindNextFileW` use `fill_find_data_w` | `shim_types.h:77-88`, `shim_kernel32_file.hpp` |
| R9  | B9 — `VirtualFree(MEM_RELEASE)` requires `size==0`; mmap tracker; `MEM_DECOMMIT` uses `mprotect`+`madvise` | `shim_kernel32_mem.hpp` |
| R10 | B10 — `WriteConsoleW` bounded by `nChars` | `shim_kernel32_console.hpp` |
| R11 | B18a — `GetModuleFileNameA` guards `size==0` | `shim_kernel32_file_a.hpp` |
| R12 | N1 — per-thread TLS array (pthread-key destructor) | `shim.cpp:93-106` (TLS state), `shim.cpp:251-254` (shim_init_teb alloc) |
| R13 | B21 — no PPMonstr hardcode in current source | n/a |
| R14 | B22 — `ERROR_TOO_MANY_OPEN_FILES` named everywhere | shim.cpp throughout |
| R15 | Header hygiene — `<sys/prctl.h>` (replaced by `<asm/prctl.h>`), `<sys/uio.h>`, `<sys/utsname.h>`, `<wchar.h>` not included | `shim.cpp:7-39` |

### Phase 2 — Modular extraction — landed

The per-section split is done.  Rather than the originally-proposed
`shim_log.cpp` / `shim_path.cpp` / … layout (separate TUs gated by a
`shim_internal.h` API), the project uses the inverse: `shim.cpp` keeps
all file-scope statics + helpers + the constructor, and `#include`s a
collection of per-feature headers that share that scope directly.  The
build is still one TU; visibility is enforced by the `EXPORT` macro and
the version script.

| Done | Where |
|---|---|
| Per-feature header split | 27 `shim_*.hpp` headers cited in §1; `shim.cpp` shrank from ~4 690 lines to ~1 240 |
| Runtime-configurable logging via `WINAPI_SHIM_LOG=path|stderr` | `shim.cpp:50-65` |
| Single `log_always` logging entrypoint (I4) | `shim.cpp:81-85` — the dead `LOG()` macro was removed |
| `fill_find_data_common` template + `fill_find_data_{a,w}` (I1) | `shim_kernel32_file.hpp` |
| `make_open_flags` helper (I2) | `shim.cpp:620-649` |
| Shared `find_ctx_open` + `find_first_posix` (I3) | `shim_kernel32_file.hpp`, `shim_kernel32_file_a.hpp` |
| Named `LCMAP_*` / `NORM_*` / `CSTR_*` / `CT_CTYPE*` / `C1_*` constants (I6) | `shim_types.h:217-236` |
| `static_assert` size checks (I7) | `shim.cpp:148` |

Notable structural choices kept:

| Choice | Rationale |
|---|---|
| One TU (the `.hpp`s are `#include`d, not compiled separately) | File-scope statics can be shared without a `shim_internal.h` declaration layer; visibility is still enforced via `EXPORT` + version script |
| `shim_kernel32_sync.hpp` carries the legacy `.hpp` extension because it was extracted before the wider split | Functionally identical to the newer headers |
| `shim_kernel32_tail.hpp` is intentionally large (~600 lines) | Groups otherwise non-cohesive tail items by file position so include order stays clear |

### Phase 3 — Semantic hardening — landed

| # | Task | Where |
|---|---|---|
| R26 | B13 — image base via `dl_iterate_phdr` + PT_LOAD scan; also caches PE-header base for resource lookup | `shim.cpp` (image-base discovery) |
| R27 | B14 — typed `FAKE_WIN_MODULE` / `MAIN_IMAGE_MODULE` pseudo-handles | `shim_kernel32_module.hpp` |
| R28 | B15 — `SetStdHandle` calls `dup2(new_fd, idx)` | `shim_kernel32_file.hpp` |
| R29 | B16 — last-error mirrored to TEB+0x68 via `SET_LAST_ERROR` | `shim.cpp:111-119` |
| R30 | B17 — `_FILE_OFFSET_BITS=64` on; `lseek` / `off_t` everywhere | `Makefile:12`, `shim_kernel32_file.hpp`, `shim_kernel32_filetime.hpp` |
| R31 | B18b — `GetModuleFileNameW`/`A` resolve loaded modules via `dlsym("_init")` + `dladdr` | `shim_kernel32_module.hpp`, `shim_kernel32_file_a.hpp` |
| R32 | B19 — `LoadLibrary*` paths through `win_path_to_posix` | `shim_kernel32_module.hpp` |
| R33 | B20 — `FlsAlloc`/`FlsFree` allocate from shared TLS bitset; per-thread cleanup is now `shim_thread_exit` (single pthread-key destructor; see also the post-plan crash fix) | `shim_kernel32_fls.hpp` |
| R34 | B23 — `SetEnvironmentVariableW` invalidates both `g_env_block_w` and `g_env_block` | `shim_kernel32_startup.hpp` |
| R35 | B35 — `errno_to_win32` covers `EEXIST`, `EMFILE`, `ENOSPC`, `ENOTEMPTY`, `EAGAIN`, `EBUSY`, `ETIMEDOUT`, `EINTR`, `ENAMETOOLONG`, `ENOSYS`, `ENOTSUP` | `shim.cpp:117-138` |
| R36 | B36 — `UnhandledExceptionFilter` invokes registered top-level filter (and VEH chain) then terminates if filter doesn't request resume | `shim_kernel32_except.hpp` |
| R37 | B37 — `RtlCaptureContext` portable inline asm; B38 — AS-safe crash banner via raw `SYS_write` + `crash_write_{int,hex,lit}` | `shim.cpp:841-928` (crash handler), `shim_kernel32_except.hpp` (RtlCaptureContext) |
| R38 | I8 — `pthread_create` interceptor wraps every thread with `shim_thread_attach` | `shim.cpp:288-326` |
| R39 | B11 — `HeapReAlloc(size=0)` clamps to 1; B12 — `prot_from_protect` logs unknown bits and defaults to RW | `shim_kernel32_mem.hpp` |
| R40 | B39 — `MAP_FIXED_NOREPLACE` with `MAP_FIXED` fallback | `shim_kernel32_mem.hpp` |
| R41 | B40 — `RtlUnwindEx` / `RtlUnwind` log + return instead of `abort()` | `shim_kernel32_except.hpp` |

### Phase 4 — Compatibility extensions — landed

| # | Task | Where |
|---|---|---|
| R42 | B28 — `ReadConsoleInput{A,W}` build `INPUT_RECORD` from `read(fd, …)` | `shim_kernel32_console_misc.hpp` |
| R43 | B32 — `GetConsoleMode` derives flags from `tcgetattr` | `shim_kernel32_console.hpp` |
| R44 | B27 — `GetStringTypeW`/`A` return CT_CTYPE1 via `classify_ctype1` | `shim_kernel32_string.hpp`, `shim_kernel32_miscstubs.hpp` |
| R45 | B29 — `IsProcessorFeaturePresent` reads CPUID leaves 1 and 0x80000001 | `shim_kernel32_proc.hpp` |
| R46 | B30 — `FormatMessageA` expands `%N!fmt!` positional escapes | `shim_kernel32_locale.hpp` |
| R47 | B31 — `FileTimeToDosDateTime` returns FALSE for pre-1980 timestamps | `shim_kernel32_filetime.hpp` |
| R48 | musl path — `malloc_usable_size` stub when not glibc; libc backtrace via libgcc `_Unwind_Backtrace` | `shim.cpp:16-19` (gated include), `shim_kernel32_proc.hpp` (log_backtrace) |
| R49 | mimalloc/jemalloc — Makefile comment documents `-DUSE_MIMALLOC -lmimalloc` / `-DUSE_JEMALLOC -ljemalloc` opt-in | `Makefile:14-15` |
| R50 | aarch64 — TEB pointer stashed in reserved `x18` register | `shim.cpp:271-274` |

---

## 5. Features Added Beyond the Original Plan

These were not in the original document but exist in the current code; track
them so they don't get re-proposed.

| Area | Detail | Where |
|---|---|---|
| PE TLS directory | `shim_register_tls` called by pe2elf trampoline before `PE_ENTRY`; allocates static TLS slot, populates per-thread block from template VA, fires DLL_PROCESS_ATTACH callbacks; `tls_static_init_thread` re-runs for every new thread; destructor fires DLL_PROCESS_DETACH | `shim.cpp:969-1073, 1075-1102` |
| Sync primitives (full) | `CreateMutex` / `CreateEvent` / `CreateSemaphore` / `CreateThread` / `ExitThread` / `GetExitCodeThread` with refcounted lifetimes; `WaitForSingleObject` dispatches over `pthread_mutex_timedlock` / `pthread_cond_timedwait` / `sem_timedwait`; `WaitForMultipleObjects` polls with rollback on partial acquisition; `SignalObjectAndWait` | `shim_kernel32_sync.hpp` |
| `SuspendThread`/`ResumeThread` | `SIGUSR1` handler with per-thread `sem_t suspend_sem`; transitions guarded by `__atomic` on `suspend_count` so multiple suspend/resume pairs nest correctly | `shim_kernel32_thread.hpp`, `shim_kernel32_sync.hpp` (`suspend_signal_handler`) |
| `DuplicateHandle` | Translates `GetCurrentThread()` pseudo-handle (`-2`) into a real `H_THREAD` slot caching a `ThreadObj`; refcount-shares non-file handles | `shim_kernel32_thread.hpp` |
| `_beginthreadex` / `_endthreadex` | Thin wrappers around `CreateThread` / `ExitThread` | `shim_msvcrt.hpp:545-555` |
| `_setjmp` / `longjmp` | Hand-written `naked` MS-ABI versions matching Windows x64 `JUMP_BUFFER` layout | `shim_msvcrt.hpp:562-600` |
| `qsort` | Custom intro-style sort calling the `ms_abi` comparator directly (avoids SYSV wrapper round-trip) | `shim_msvcrt.hpp:451-504` |
| `scanf` | Single `read(STDIN_FILENO, …)` + minimal `%d`/`%s`/`%c` parser | `shim_msvcrt.hpp:509-538` |
| `printf` / `sprintf` / `fprintf` / `vfprintf` | `ms_vformat` parses `%[flags][width][.prec][len]conv` against MS-ABI `va_list` (which is `char*` on x86-64, advanced 8 bytes per arg) | `shim_msvcrt.hpp:28-107, 325-342` |
| CRT locking | 32 recursive `pthread_mutex_t` per lock ID | `shim_msvcrt.hpp:128-154` |
| `__getmainargs` / `__wgetmainargs` | argv built from `/proc/self/cmdline`; wide envp synthesised from `environ` | `shim_msvcrt.hpp:171-178, 245-274` |
| `__iob_func` | Fake Windows `_iobuf[3]` array with `(fd, flag)` for stdin/stdout/stderr; `win_file_to_fd` translates pointers back into POSIX fds | `shim.cpp:795-839` (state), `shim_msvcrt.hpp:9-16` (`win_file_to_fd`) |
| `_time64` family | All `_time64`/`_gmtime64`/`_localtime64`/`_mktime64` route to libc; `strftime` passthrough | `shim_msvcrt.hpp:300-320` |
| Resource directory parsing | `LoadString{A,W}` walks PE `.rsrc` (RT_STRING = 6); handles named/id directories, first language | `shim_user32.hpp` |
| `VirtualQuery` | Reads `/proc/self/maps` to fill MEMORY_BASIC_INFORMATION | `shim_kernel32_misc.hpp` |
| `CommandLineToArgvW` | Two-pass parse with quote handling; returns a single `malloc`’d block (caller `LocalFree`s) | `shim_kernel32_tail.hpp` |
| `PathMatchSpec{A,W}` | Wraps `win_fnmatch` on basename | `shim_kernel32_tail.hpp` |
| `SetConsoleCtrlHandler` | Up to 8 handlers, `signal(SIGINT)` invokes them LIFO | `shim_kernel32_tail.hpp` |
| `CryptGenRandom` | Reads `/dev/urandom` | `shim_advapi32.hpp` |
| `SHGetMalloc` | Minimal IMalloc COM vtable (9 slots, all `ms_abi`); `Alloc`/`Realloc`/`Free` route to libc | `shim_shell32.hpp` |
| `RtlPcToFileHeader` | Resolves via `dladdr` | `shim_kernel32_except.hpp` |
| `GetVersionExW` / `GetVersionExA` / `GetVersion` | Report Windows 7 SP1 x64 (6.1.7601, Service Pack 1) | `shim_kernel32_tail.hpp` (W), `shim_kernel32_a.hpp` (A) |
| `GlobalMemoryStatus` / `GlobalMemoryStatusEx` | Backed by `sysinfo()`; Ex echoes caller’s `dwLength` | `shim_kernel32_sysinfo.hpp`, `shim_kernel32_tail.hpp` |
| `GetDiskFreeSpace{,Ex}{A,W}` | Backed by `statvfs("/")`; clusters scaled into sane 32-bit ranges | `shim_kernel32_tail.hpp`, `shim_kernel32_a.hpp` |
| `posix_to_win_path` | Prefixes `C:` and switches `/` → `\\` so callers doing `wcsrchr(path, '\\')` find a separator; `win_path_to_posix` reverses it for opens | `shim.cpp:542-552` |
| `SetUnhandledExceptionFilter` | Stores filter pointer; the filter is invoked from `UnhandledExceptionFilter` (ms_abi → ms_abi, ABI-safe).  Not invoked from `crash_handler` because POSIX signal-handler context can't safely call ms_abi user code | `shim_kernel32_except.hpp` (filter dispatch), `shim.cpp:844` (`g_unhandled_filter`) |

---

## 6. Open / Deferred

Nothing on the original Phase 1 list is open. Items still worth keeping in
mind:

| Topic | Current state |
|---|---|
| Unified logging conventions (I4) | Landed — the dead `LOG()` macro (used in exactly one place) was removed and that call rewritten to `log_always`.  Single logging entrypoint now, runtime-gated on `WINAPI_SHIM_LOG`.  `WINAPI_LOG_ENABLED` (debug build) still forces the file open and unlocks the extra RtlCaptureContext stack dump |
| Per-section file split (R17 – R20) | Landed via the inverse design — `shim.cpp` keeps file-scope statics and `#include`s 27 per-feature headers (see §1, §2).  No `shim_internal.h` was needed because the build is still one TU |
| `SetUnhandledExceptionFilter` callback | Landed — `UnhandledExceptionFilter` now actually invokes the registered top-level filter (ms_abi → ms_abi, ABI-safe from this entrypoint), honours `EXCEPTION_CONTINUE_EXECUTION` / `EXECUTE_HANDLER` / `CONTINUE_SEARCH`.  The plan's "deferred-execution helper" concern only applied to dispatching from `crash_handler` (still not done — would need a real-stack hand-off because POSIX signal handlers can't safely call ms_abi user code) |
| `LoadLibrary` of arbitrary Windows DLLs | Out of scope — pe2elf flattens the import graph at conversion time; `FAKE_WIN_MODULE` sentinel routes `GetProcAddress` to `RTLD_DEFAULT` over the shim's own exports |
| `RtlUnwindEx` / SEH | Logs and returns; real SEH unwind not implemented. C++ EH from MSVC code that genuinely throws across the shim boundary will likely terminate |
| `GetThreadContext` / `SetThreadContext` | `GetThreadContext` now handles the current-thread pseudo-handle (-2) by delegating to `RtlCaptureContext`; cross-thread capture would need SIGUSR1 + `ucontext` save and isn't implemented.  `SetThreadContext` still stubbed (would need `ptrace` or signal-handler hand-off) |
| Vectored Exception Handlers | Landed (mostly) — `AddVectoredExceptionHandler` / `RemoveVectoredExceptionHandler` maintain a real doubly-linked list with `First`-flag insertion semantics; `run_vectored_handlers` snapshots the list and invokes each handler in order.  Dispatched from `UnhandledExceptionFilter` and `RaiseException`, never from the POSIX signal handler |
| aarch64 | TEB stashed in `x18` but no `__readgsqword` shim wired up; MSVC PE inlined TEB accesses won't work without per-port asm helpers |
| musl backtrace | Landed — non-glibc `log_backtrace` now uses libgcc's `_Unwind_Backtrace` (no external dependency; same primitive glibc's `backtrace()` builds on).  Only walks frames with DWARF unwind info, so PE / shim frames still drop after the first non-unwindable boundary |

---

*End of document.*
