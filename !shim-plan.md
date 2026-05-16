# shim.cpp — Cleanup, Modular Redesign, and Refactoring Plan

Assumptions: little-endian host; primary target glibc on Linux x86-64 with
graceful degradation toward musl/aarch64 where cheap.

---

## 1. Current State

`shim.cpp` is a single translation unit organised internally into numbered
sections (7.1 process/identity, 7.2 error state, 7.3 memory, 7.4 file I/O,
7.5 file times, 7.6 directory search, 7.7 console, 7.8 module/library,
7.9 startup/cmdline/env, 7.10 time, 7.11 sync, 7.13 string, 7.14 pointer
encoding, 7.15 exception, plus a trailing "misc stubs" and an A-variant
block). It exports `EXPORT`-attributed functions in the `ms_abi` calling
convention. `shim_types.h` carries Windows-shaped type definitions, error
constants, and a few inline `FILETIME` helpers.

The breadth is the proximate reason the file is hard to navigate and audit.

---

## 5. Proposed Modular Layout

Flat, name-prefix discipline.

| File | Owns |
|---|---|
| `shim_types.h` | Windows types, error codes, struct layouts (existing) |
| `shim_internal.h` | Internal-only types, globals, forward declarations |
| `shim_log.h` | Logging macros, included by every `shim_*.cpp` |
| `shim.map` | Export filter (existing) |
| `shim_init.cpp` | Constructor, fake TEB/PEB, signal handler, future `shim_thread_attach` |
| `shim_handles.cpp` | Thread-safe handle table, typed alloc/lookup/release |
| `shim_path.cpp` | Win32 ↔ POSIX path translation, UTF-8 ↔ UTF-16, `path_join` |
| `shim_process.cpp` | Process identity, command line, environment block |
| `shim_memory.cpp` | `VirtualAlloc`/`VirtualFree` (+ mmap tracker), `Heap*` |
| `shim_file.cpp` | `CreateFile`, `ReadFile`, `WriteFile`, seek/truncate/time/attribute |
| `shim_dir.cpp` | `FindFirst*`, `FindNext*`, `FindClose` (A and W) |
| `shim_console.cpp` | Console mode, code pages, console I/O |
| `shim_module.cpp` | `LoadLibrary*`, `FreeLibrary`, `GetProcAddress`, `GetModuleHandle*` |
| `shim_time.cpp` | `GetSystemTimeAsFileTime`, `QPC`, `GetTickCount`, `SetFileTime`, `DosDateTime*` |
| `shim_sync.cpp` | Critical sections, TLS/FLS, `InitializeSListHead` |
| `shim_string.cpp` | `MultiByteToWideChar`, `WideCharToMultiByte`, `CompareStringW`, `LCMapStringW` |
| `shim_except.cpp` | `SetUnhandledExceptionFilter`, `RtlCaptureContext`, `RaiseException`, crash handler |
| `shim_misc.cpp` | Anything that doesn't fit cleanly above; should stay small |

Each unit compiles to a hidden-visibility object; only `EXPORT` symbols
appear in the dynamic table.

---

## 6. Shared Internal Header (`shim_internal.h`)

```c
#pragma once
#include "shim_types.h"
#include "shim_log.h"

/* Handle table */
#define MAX_HANDLES 4096
enum HandleKind { H_FREE, H_FILE, H_FIND, H_MODULE };
struct FindCtx   { DIR* dir; char glob[260]; char dirpath[PATH_MAX]; };
struct HandleSlot {
    HandleKind kind;
    union { int fd; FindCtx* find; void* dlhandle; };
};
extern HandleSlot       g_handles[MAX_HANDLES];
extern pthread_mutex_t  g_handles_mu;

HANDLE      handle_alloc_file (int fd);          /* alloc + populate atomically */
HANDLE      handle_alloc_find (FindCtx* ctx);
HANDLE      handle_alloc_module(void* dlh);
HandleSlot* handle_lookup     (HANDLE h, HandleKind expect);
int         handle_get_fd     (HANDLE h);
void        handle_close_slot (int idx);         /* caller holds g_handles_mu */

/* Path / encoding */
void win_path_to_posix(const char* in, char* out, size_t outsz);
int  wchar_to_utf8 (const uint16_t* src, char* dst, size_t dstsz);
int  utf8_to_wchar (const char* src, uint16_t* dst, size_t dstsz);
void path_join     (char* dst, size_t dst_sz, const char* dir, const char* name);

/* Process state */
extern char      g_cmdline[];
extern char      g_cmdline_w[];
extern char*     g_env_block;
extern uint16_t* g_env_block_w;
extern void*     g_image_base;
extern __thread uint32_t tls_last_error;

/* Errno mapping */
uint32_t errno_to_win32(int e);
void     set_errno_error(void);
```

Notes:

- The `HandleSlot` union mixes pointer and integer payloads. On a
  little-endian 64-bit target this is safe because `kind` disambiguates;
  do not access fields without first checking `kind`.
- The fake TEB / PEB stay file-local to `shim_init.cpp`; the only public
  surface is `shim_init_teb()` and (later) `shim_thread_attach()`. Per N1,
  the per-thread TLS slot array must move from `static` to a per-call
  allocation (or `__thread`).

---

## 7. Build Integration

```make
SHIM_OBJS = shim_init.o shim_handles.o shim_path.o \
            shim_process.o shim_memory.o shim_file.o shim_dir.o \
            shim_console.o shim_module.o shim_time.o \
            shim_sync.o shim_string.o shim_except.o shim_misc.o

CFLAGS   += -fPIC -fvisibility=hidden -D_FILE_OFFSET_BITS=64
LDFLAGS  += -shared -Wl,--version-script=shim.map -rdynamic

$(SHIM_OUT):     $(SHIM_OBJS) shim.map
	$(CC) $(LDFLAGS) -o $@ $(SHIM_OBJS) $(SHIM_LDFLAGS)

$(SHIM_DBG_OUT): $(SHIM_OBJS_DBG) shim.map
	$(CC) $(LDFLAGS) -DWINAPI_LOG_ENABLED -o $@ $(SHIM_OBJS_DBG) $(SHIM_DBG_LDFLAGS)
```

`shim.map` keeps the dynamic symbol set explicit and version-stamped.

---

## 8. Refactoring Phases

Each phase is independently buildable.

### Phase 1 — Emergency correctness

| # | Task |
|---|---|
| R1  | B1 — fix `build_env_block` overflow; free `g_env_block` on the wide-allocation failure path |
| R2  | B2 — `handle_alloc_*` populate under lock, return `HANDLE`; `lookup`/`get_fd`/`CloseHandle`/`FindClose` take the mutex for the read-modify sequence |
| R3  | B3 — fix `GetCurrentDirectoryA` leak (NULL-check, free) |
| R4  | B4 — check `stat` return in `SetFileAttributesA` |
| R5  | B5 — `utf8_to_wchar` skips continuation bytes after `?` |
| R6  | B6 — `WideCharToMultiByte` honours `srclen` |
| R7  | B7 — `CompareStringW` honours `n1` / `n2` |
| R8  | B8 — introduce real `WIN32_FIND_DATAW`, fix `FindFirstFileExW` / `FindNextFileW` signatures and `cFileName` conversion |
| R9  | B9 — `VirtualFree(MEM_RELEASE)` requires `size == 0`; add mmap tracker; switch decommit to `mprotect` + `madvise` |
| R10 | B10 — bound `WriteConsoleW` by `nChars`; report actual wide-char count |
| R11 | B18a — guard `size == 0` in `GetModuleFileNameA` |
| R12 | N1 — make TEB+0x58 TLS array per-thread |
| R13 | B21 — remove PPMonstr address hardcode |
| R14 | B22 — replace `tls_last_error = 4` with `ERROR_TOO_MANY_OPEN_FILES` |
| R15 | Header hygiene: remove `<sys/prctl.h>`, `<sys/uio.h>`, `<sys/utsname.h>`, `<wchar.h>` |

### Phase 2 — Modular extraction

| # | Task |
|---|---|
| R16 | Extract `shim_log` with runtime-configurable destination |
| R17 | Extract `shim_path` (`win_path_to_posix`, encoding, `path_join`) — fixes I5 |
| R18 | Extract `shim_handles` with the new typed-allocator API |
| R19 | Extract `shim_init` (TEB/PEB, signal handler, constructor) |
| R20 | Split per-section files (`shim_file`, `shim_dir`, `shim_memory`, `shim_module`, `shim_process`, `shim_console`, `shim_time`, `shim_sync`, `shim_string`, `shim_except`, `shim_misc`) |
| R21 | I1 — `fill_find_data` helper; I2 — `make_open_flags` helper |
| R22 | I3 — `FindFirstFileExW` routes through `find_first_posix` |
| R23 | I6 — name `LCMAP_*` / `NORM_*` / `CSTR_*` constants in `shim_types.h` |
| R24 | I7 — `static_assert` size checks |
| R25 | I4 — apply logging conventions uniformly |

### Phase 3 — Semantic hardening

| # | Task |
|---|---|
| R26 | B13 — discover image base via `dl_iterate_phdr`; update PEB+0x10 and `g_image_base` |
| R27 | B14 — typed module pseudo-handle; `GetProcAddress` / `FreeLibrary` recognise it explicitly |
| R28 | B15 — `SetStdHandle` calls `dup2` for the three standard streams |
| R29 | B16 — last-error in fake TEB at +0x68 |
| R30 | B17 — `_FILE_OFFSET_BITS=64`; replace `lseek64` / `off64_t` with `lseek` / `off_t` |
| R31 | B18b — loaded-module path resolution via `dladdr` against a stored table |
| R32 | B19 — loader paths through `win_path_to_posix` |
| R33 | B20 — `FlsAlloc` / `FlsFree` use a free bitset |
| R34 | B23 — invalidate `g_env_block_w` on env mutation |
| R35 | B35 — expand `errno_to_win32` coverage |
| R36 | B36 — `UnhandledExceptionFilter` terminates or chains |
| R37 | B37 / B38 — `RtlCaptureContext` portability; AS-safe crash banner |
| R38 | I8 — `shim_thread_attach()` and `pthread_create` interceptor |
| R39 | B11 / B12 — `HeapReAlloc(size=0)` and `prot_from_protect` defaults |
| R40 | B39 — `MAP_FIXED_NOREPLACE` fallback |
| R41 | B40 — `RtlUnwindEx` returns a structured failure instead of `abort()` |

### Phase 4 — Compatibility extensions

| # | Task |
|---|---|
| R42 | B28 — real `ReadConsoleInputA` over `read(STDIN, …)` and termios |
| R43 | B32 — `GetConsoleMode` from `tcgetattr` |
| R44 | B27 — useful `GetStringTypeW` / `GetStringTypeA` |
| R45 | B29 — CPU feature query at runtime |
| R46 | B30 — positional escapes in `FormatMessageA` |
| R47 | B31 — `FileTimeToDosDateTime` underflow guard |
| R48 | musl compatibility: shadow allocation-size table for `malloc_usable_size`; `libunwind` for `backtrace`; alternate signal-context layout |
| R49 | Optional `mimalloc` / `jemalloc` for `Heap*` |
| R50 | aarch64 TEB strategy (reserved register or inlined `NtCurrentTeb`) |

---

*End of document.*
