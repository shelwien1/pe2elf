# nz.exe conversion plan

## Binary overview

- PE32+, x86-64, 7 sections, ~589 KB
- `ImageBase=0x400000` (no ASLR; 0 base relocs — all addresses are hardcoded)
- 100 IAT entries across kernel32 + msvcrt
- Test command: `./nz.elf a -cc archive "*.exe"`

## Missing shims

### kernel32 — synchronisation / threading (most complex)

| Symbol | Implementation |
|---|---|
| `CreateThread` | `pthread_create`; store `pthread_t` in handle table as `H_THREAD` |
| `ExitThread` | `pthread_exit` |
| `GetExitCodeThread` | join (non-blocking via `pthread_tryjoin_np`) or stored exit code |
| `CreateMutexA` | `pthread_mutex_t` heap-allocated, handle as `H_MUTEX` |
| `ReleaseMutex` | `pthread_mutex_unlock` |
| `CreateEventA` | `pthread_cond_t` + `pthread_mutex_t` + bool state, handle as `H_EVENT` |
| `CreateSemaphoreA` | `sem_t` heap-allocated, handle as `H_SEMAPHORE` |
| `ReleaseSemaphore` | `sem_post` |
| `WaitForSingleObject` | dispatch on handle kind: mutex→trylock+lock, event→condwait, semaphore→sem_timedwait, thread→pthread_join |
| `SignalObjectAndWait` | signal first object (ReleaseMutex/SetEvent), then WaitForSingleObject on second |
| `RtlAddFunctionTable` | stub returning 1 (we don't do SEH unwind for JIT code) |

`WaitForSingleObject` is the central dispatcher — implement it first since Mutex/Event/Semaphore all depend on it.

Timeout mapping: `INFINITE (0xFFFFFFFF)` → block forever; otherwise convert ms to `struct timespec` via `clock_gettime(CLOCK_REALTIME)`.

### kernel32 — file / memory / info

| Symbol | Implementation |
|---|---|
| `CreateDirectoryA` | `mkdir(posix, 0777)` after `win_path_to_posix` |
| `GetFileAttributesA` | `stat()` → FILE_ATTRIBUTE_DIRECTORY or FILE_ATTRIBUTE_NORMAL; INVALID_FILE_ATTRIBUTES on error |
| `FileTimeToSystemTime` | convert 100-ns ticks since 1601 to `SYSTEMTIME` struct |
| `GlobalAlloc` | `malloc` / `calloc` (GMEM_ZEROINIT flag) |
| `GlobalFree` | `free` |
| `GlobalMemoryStatus` | fill `MEMORYSTATUS` from `/proc/meminfo` or `sysinfo()` |
| `GetSystemInfo` | fill `SYSTEM_INFO` from `sysconf` / `get_nprocs` |

### msvcrt — data variables

| Symbol | Kind | Value |
|---|---|---|
| `msvcrt__acmdln` | `char*` | pointer to same g_cmdline used by GetCommandLineA |

### msvcrt — CRT lifecycle

| Symbol | Implementation |
|---|---|
| `msvcrt___dllonexit` | store fn in atexit-style list; call on exit (or just call `atexit` wrapper) |
| `msvcrt__onexit` | same as `__dllonexit` |
| `msvcrt___lconv_init` | no-op (locale conv already zeroed) |

### msvcrt — time

| Symbol | Implementation |
|---|---|
| `msvcrt__time64` | `time(t)` (already 64-bit on Linux) |
| `msvcrt__gmtime64` | `gmtime` → `struct tm*` |
| `msvcrt__localtime64` | `localtime` → `struct tm*` |
| `msvcrt__mktime64` | `mktime` |
| `msvcrt_strftime` | pass through to libc `strftime` |

### msvcrt — stdio / string

| Symbol | Implementation |
|---|---|
| `msvcrt_printf` | `ms_vfprintf_fd(STDOUT_FILENO, fmt, ap)` via `__builtin_ms_va_start` |
| `msvcrt_sprintf` | manual MS ABI sprintf using same format parser writing to buffer |
| `msvcrt_puts` | `puts` pass-through |
| `msvcrt_putchar` | `putchar` pass-through |
| `msvcrt_fgets` | `fgets((char*)buf, n, (FILE*)win_file_to_fd_as_stream(f))` — needs fd→FILE* lookup |
| `msvcrt_fwrite` | `write(win_file_to_fd(f), buf, size*count)` |
| `msvcrt_memmove` | `memmove` pass-through |
| `msvcrt_memset` | `memset` pass-through |
| `msvcrt_strcmp` | `strcmp` pass-through |
| `msvcrt_remove` | `remove` / `unlink` pass-through |
| `msvcrt_tolower` | `tolower` pass-through |

## Handle table extensions

Current `HKind` enum needs new entries:
```
H_THREAD, H_MUTEX, H_EVENT, H_SEMAPHORE
```
Each handle stores a pointer to a heap-allocated struct with the pthread primitive(s).

## shim_kernel32_sync.hpp

Put all threading/sync shims in a new `shim_kernel32_sync.hpp` included from `shim.cpp` just before `shim_msvcrt.hpp`.

## Implementation order

1. Extend `HKind` and handle structs
2. `WaitForSingleObject` (skeleton — needed by everything)
3. `CreateMutexA` / `ReleaseMutex`
4. `CreateEventA` / `SetEvent` / `ResetEvent` (if needed)
5. `CreateSemaphoreA` / `ReleaseSemaphore`
6. `CreateThread` / `ExitThread` / `GetExitCodeThread`
7. `SignalObjectAndWait`
8. Simple kernel32 stubs (CreateDirectoryA, GetFileAttributesA, etc.)
9. msvcrt additions (time, stdio, string)
10. Build, test, iterate

## Test

```
make winapi_shim.so && ./pe2elf nz.exe nz.elf
LD_LIBRARY_PATH=. ./nz.elf a -cc archive "*.exe"
```

Expected: nz archives the .exe files and prints compression stats.
