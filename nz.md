# nz.exe conversion plan

## Binary overview

- PE32+, x86-64, 7 sections, ~589 KB
- `ImageBase=0x400000` (no ASLR; 0 base relocs — all addresses are hardcoded)
- 100 IAT entries across kernel32 + msvcrt
- Test command: `./nz.elf a -cc archive "*.exe"`

## Missing shims — synchronisation / threading

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
| `WaitForSingleObject` | dispatch on handle kind: mutex→lock, event→condwait, semaphore→sem_timedwait, thread→pthread_join |
| `SignalObjectAndWait` | signal first object (ReleaseMutex/SetEvent), then WaitForSingleObject on second |

`WaitForSingleObject` is the central dispatcher — implement it first.

Timeout mapping: `INFINITE (0xFFFFFFFF)` → block forever; otherwise convert ms to `struct timespec` via `clock_gettime(CLOCK_REALTIME)`.

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
4. `CreateEventA`
5. `CreateSemaphoreA` / `ReleaseSemaphore`
6. `CreateThread` / `ExitThread` / `GetExitCodeThread`
7. `SignalObjectAndWait`

## Test

```
make winapi_shim.so && ./pe2elf nz.exe nz.elf
LD_LIBRARY_PATH=. ./nz.elf a -cc archive "*.exe"
```

Expected: nz archives the .exe files and prints compression stats.
