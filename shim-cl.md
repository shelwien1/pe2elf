# shim.cpp — Cleanup, Modular Redesign, and Refactoring Plan

## 1. Current State

`shim.cpp` is a single 2023-line file implementing a WinAPI-to-Linux shim for PE→ELF
converted binaries.  The structure is already reasonably organised into numbered sections
(7.1–7.15 + misc), but everything lives in one translation unit, correctness issues are
present, and several abstractions are duplicated or missing.

---

## 2. Bugs and Correctness Issues

Ordered by severity.

### B1 — Buffer overflow in `build_env_block` (HIGH)

```c
uint16_t* wp = g_env_block_w;
for( char** e = environ; *e; ++e ) {
    int len = utf8_to_wchar(*e, wp, total);   // BUG: total never shrinks
    wp += len+1;
}
```

`total` is the byte count of the entire narrow env block and is passed as the
`dstsz` limit to `utf8_to_wchar` on every iteration.  After the first few env
variables are written `wp` has advanced into the buffer, but the capacity limit
stays fixed at `total`.  The last env vars can write past the end of
`g_env_block_w` (size `total * sizeof(uint16_t)` bytes).

**Fix:** pass remaining capacity: `utf8_to_wchar(*e, wp, total - (size_t)(wp - g_env_block_w))`.

---

### B2 — Handle table data races (HIGH)

Three separate issues in the handle table:

**a) Slot populated outside the lock.**  `alloc_handle` grabs the mutex, marks the
slot `kind != H_FREE`, releases the mutex, and returns the index.  The caller
then writes `.fd` or `.find` *without holding the lock*.  Between the unlock and
the field write another thread can call `lookup()` or `CloseHandle()` on the same
handle and see a partially-initialised slot.

**b) `lookup` and `get_fd` read `g_handles` without the mutex.**  Any concurrent
`alloc_handle` or `CloseHandle` is a data race.

**c) `CloseHandle` does not hold the mutex** while reading `g_handles[idx].kind`,
calling `closedir()`/`free()`, and setting `kind = H_FREE`.

**Fix:** take `g_handles_mu` for the duration of every read+modify sequence.
`alloc_handle` should fill the payload fields while the lock is held and return
the `HANDLE` (not the index), removing the unsafe window entirely.

---

### B3 — Memory leak in `GetCurrentDirectoryA` (MEDIUM)

```c
return (DWORD)(strlen(getcwd(NULL, 0))+1);
```

`getcwd(NULL, 0)` allocates a buffer with `malloc`; the return value is
immediately passed to `strlen` and the pointer is lost.

**Fix:**
```c
char* cwd = getcwd(NULL, 0);
if( !cwd ) return 0;
DWORD n = (DWORD)(strlen(cwd)+1);
free(cwd);
return n;
```

---

### B4 — `SetFileAttributesA` uses uninitialised `stat` on failure (MEDIUM)

```c
stat(posix, &st);          // return value ignored
chmod(posix, st.st_mode&~(...));
```

If `stat` fails, `st.st_mode` is uninitialised; `chmod` is called with a garbage
mode.

**Fix:** check the return value of `stat` and set `tls_last_error` on failure.

---

### B5 — `utf8_to_wchar` drops 4-byte UTF-8 sequences (MEDIUM)

The else branch advances `s` by only 1 byte and emits `'?'`:

```c
} else {
    cp = '?';
    s++;          // consumes only the leading byte of a 4-byte sequence
}
```

The 3 continuation bytes (0x80–0xBF) are then re-parsed as new code points,
producing garbage output.

**Fix:** advance `s` past all continuation bytes:
```c
} else {
    cp = '?';
    s++;
    while( (*s&0xC0)==0x80 ) s++;
}
```

---

### B6 — `WideCharToMultiByte` ignores `srclen` (MEDIUM)

```c
(void)srclen;
```

The Windows API contract is that when `srclen > 0` only that many wide characters
are converted.  Callers that pass an explicit length (without a NUL terminator)
get incorrect results.

**Fix:** when `srclen >= 0`, copy `srclen` wide chars into a temporary NUL-terminated
buffer before converting, or add an explicit length parameter to `wchar_to_utf8`.

---

### B7 — `CompareStringW` ignores `n1`/`n2` (MEDIUM)

```c
(void)n1;
(void)n2;
// Minimal: compare up to NUL
```

Callers that pass explicit lengths (common in CRT string operations) get
NUL-terminated comparison instead of bounded comparison.  This can produce wrong
results and infinite loops if the strings are not NUL-terminated within `n`
characters.

**Fix:** honour `n1`/`n2` by limiting the comparison loop.

---

### B8 — `FlsFree` is a no-op; slots are never recycled (LOW)

`g_fls_next` only ever increments.  Once 64 slots are exhausted, every subsequent
`FlsAlloc` returns `0xFFFFFFFF`, and the program's CRT initialisation typically
fails silently.

**Fix:** maintain a simple free-list or bitset so `FlsFree` actually releases the
slot.

---

### B9 — `g_image_base` is never updated (LOW)

```c
static void* g_image_base = (void*)0x400000;
```

`GetModuleHandleW(NULL)` returns this placeholder.  The real PE image base is
available at load time via the `PT_PHDR`/`PT_LOAD` program headers or the ELF
`dl_phdr_info` callback.  PE code that reads its own base via `GetModuleHandle(NULL)`
and then walks the PE headers will get wrong results.

**Fix:** call `dl_iterate_phdr` in `shim_init` to find the main executable's load
address, or expose a symbol that `pe2elf`-generated code sets at startup.

---

### B10 — `VirtualFree(MEM_DECOMMIT)` ignores `mmap` failure (LOW)

```c
mmap(addr, size, PROT_NONE, MAP_FIXED|MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
```

`MAP_FIXED` silently replaces any existing mapping at that address.  If the address
range is not currently mapped this creates a new anonymous mapping.  The return
value is not checked.

---

### B11 — Hardcoded PPMonstr text range in `RtlCaptureContext` (LOW)

```c
if( val>=0x140001000&&val<0x140030000 )
    log_always("...*** PPMonstr addr\n");
```

This is a debugging artifact specific to one test binary.  It should be removed or
replaced with a generic "within .text of main executable" heuristic using
`dl_iterate_phdr`.

---

### B12 — `tls_last_error = 4` magic constant (LOW)

Three places use `tls_last_error = 4` directly (handle exhaustion path in
`FindFirstFileExW`, `find_first_posix`, `CreateFileA`).  The constant 4 is
`ERROR_TOO_MANY_OPEN_FILES`, which is already defined in `shim_types.h`.

---

## 3. Design and Quality Improvements

### I1 — Duplicate `fill_find_data` logic

`FindFirstFileExW`, `FindNextFileW`, and `find_first_posix` all contain identical
blocks:

```c
memset(pfd, 0, sizeof(*pfd));
if( stat(fullpath, &st)==0 ) {
    pfd->dwFileAttributes = ...;
    uint64_t mtime = ...;
    pfd->ftLastWriteTime = u64_to_ft(mtime);
    ...
}
strncpy(pfd->cFileName, ent->d_name, 259);
```

Extract as:
```c
static void fill_find_data(WIN32_FIND_DATAA* pfd, const char* fullpath, const char* name);
```

---

### I2 — Duplicate `open_flags_from_access_disp` logic

`CreateFileW` and `CreateFileA` both build `oflags` from `access` and `disp` with
identical code.  Extract as:
```c
static int make_open_flags(DWORD access, DWORD disp);
```

---

### I3 — `find_first_posix` duplicates `FindFirstFileExW`

The two functions share the same dir/glob split, opendir, readdir, fill loop, and
alloc_handle sequence.  `FindFirstFileExW` should call `find_first_posix` (after
converting the wide pattern to posix) the same way `FindFirstFileA` does, or they
should share a single common implementation.

---

### I4 — Logging inconsistency: `LOG` vs `log_always` vs `log_write`

Three logging entry points are used with no clear rule:
- `LOG("name", "fmt", ...)` — adds `[pid] name(...)` wrapper, used in `GetCurrentProcess`, `TlsAlloc`, etc.
- `log_always("[SHIM] func(...)...")` — used in most `ExitProcess`, `TerminateProcess`, file ops, etc.
- `log_write` — used internally in the crash handler.

`LOG` should be used consistently for function-entry tracing; `log_always` for
events (crashes, abnormal paths).  The current mix makes it hard to grep logs.

---

### I5 — `path_join` placement

`path_join` is a path utility but was inserted inline in section 7.6 because it
was added as a warning fix.  It belongs with the other path utilities (section
just above `win_path_to_posix`).

---

### I6 — `LCMapStringW` / `LCMapStringA` use magic flag values

```c
if( flags&0x200 ) { // LCMAP_UPPERCASE
if( flags&0x100 ) { // LCMAP_LOWERCASE
```

These constants should be named (`#define LCMAP_LOWERCASE 0x100`, etc.) and placed
in `shim_types.h`.

---

### I7 — `CRITICAL_SECTION` size / layout assumption

The code casts `CRITICAL_SECTION*` to `pthread_mutex_t*`:
```c
pthread_mutex_init((pthread_mutex_t*)cs, &a);
```

`CRITICAL_SECTION` is declared as `uint8_t opaque[40]`.  On Linux x86-64,
`pthread_mutex_t` is 40 bytes, which fits exactly, but this is a fragile
coincidence.  A `static_assert(sizeof(pthread_mutex_t) <= sizeof(CRITICAL_SECTION))`
would make the assumption explicit.

---

### I8 — Thread safety of `shim_init_teb`

`shim_init_teb` is called only from the `__attribute__((constructor))` and sets
GS for the main thread only.  Worker threads created by the PE would not have GS
set, causing a crash on any `NtCurrentTeb()` / `__readgsqword()` call.  Properly
fixing this requires hooking thread creation (e.g., intercepting `pthread_create`),
but at minimum a comment should document the known limitation.

---

### I9 — `log_write` in crash/signal handler is not async-signal-safe

`vsnprintf` is not listed as async-signal-safe in POSIX.  In practice glibc's
implementation is safe for the format strings used, but this is technically
undefined behaviour.  Use a custom minimal formatter for the crash path, or simply
call `write(2, literal, sizeof(literal)-1)` for the fixed crash-header line.

---

### I10 — `WriteConsoleW` reports wrong byte count

```c
if( pWritten )
    *pWritten = nChars; // report wide chars written
```

`WriteConsoleW`'s `lpNumberOfCharsWritten` output should report the number of wide
characters written.  `nChars` is already in wide chars, so reporting it is correct
only when the entire buffer is written.  If `WriteFile` writes fewer bytes (e.g.,
partial write due to pipe), `*pWritten` is still set to `nChars`.  Fix by
computing wide chars from the actual bytes written.

---

## 4. Modular Redesign

The goal is to split `shim.cpp` into focused files that can be reviewed and
extended independently, while keeping a minimal shared header for internal
declarations.

```
shim_types.h          (existing) — Windows types, error codes, struct layouts
shim_internal.h       (new)      — internal-only types and forward declarations
shim_log.h            (new)      — logging macros; included by all shim_*.cpp
shim.map              (existing) — export filter (unchanged)

shim_init.cpp         (new)      — constructor, TEB/PEB, signal handling, cmdline/env
shim_handles.cpp      (new)      — handle table (alloc/free/lookup, thread-safe)
shim_path.cpp         (new)      — path translation, UTF-8↔UTF-16, path_join
shim_process.cpp      (new)      — §7.1 process/identity, §7.2 error state
shim_memory.cpp       (new)      — §7.3 memory/heap
shim_file.cpp         (new)      — §7.4 file I/O (CreateFile, Read/WriteFile, seek, etc.)
shim_dir.cpp          (new)      — §7.6 directory search (Find*), file metadata
shim_sync.cpp         (new)      — §7.11 CriticalSection, TLS/FLS
shim_string.cpp       (new)      — §7.13 MultiByteToWideChar, LCMap, Compare
shim_module.cpp       (new)      — §7.8 LoadLibrary, GetProcAddress, GetModuleHandle
shim_except.cpp       (new)      — §7.15 SEH stubs, RtlCapture/Unwind, RaiseException
shim_misc.cpp         (new)      — §7.7 console, §7.9 startup/env, §7.10 time, misc
```

### `shim_internal.h` — shared internal state

All internal globals currently scattered across `shim.cpp` need a single header:

```c
// shim_internal.h
#pragma once
#include "shim_types.h"
#include "shim_log.h"

// Handle table
#define MAX_HANDLES 4096
enum HandleKind { H_FREE, H_FILE, H_FIND, H_MODULE };
struct FindCtx { DIR* dir; char glob[260]; char dirpath[PATH_MAX]; };
struct HandleSlot { HandleKind kind; union { int fd; FindCtx* find; void* dlhandle; }; };
extern HandleSlot g_handles[MAX_HANDLES];
extern pthread_mutex_t g_handles_mu;

HANDLE  handle_alloc_file(int fd);      // allocate + fill atomically
HANDLE  handle_alloc_find(FindCtx* ctx);
HANDLE  handle_alloc_module(void* dlh);
HandleSlot* handle_lookup(HANDLE h, HandleKind expect);
int         handle_get_fd(HANDLE h);
void        handle_close_slot(int idx); // called with lock held

// Path
void win_path_to_posix(const char* in, char* out, size_t outsz);
int  wchar_to_utf8(const uint16_t* src, char* dst, size_t dstsz);
int  utf8_to_wchar(const char* src, uint16_t* dst, size_t dstsz);
void path_join(char* dst, size_t dst_sz, const char* dir, const char* name);

// Process state
extern char     g_cmdline[];
extern char     g_cmdline_w[];
extern char*    g_env_block;
extern uint16_t* g_env_block_w;
extern void*    g_image_base;
extern __thread uint32_t tls_last_error;

// Errno
uint32_t errno_to_win32(int e);
void     set_errno_error(void);
```

### Makefile changes

```makefile
SHIM_OBJS = shim_init.o shim_handles.o shim_path.o \
            shim_process.o shim_memory.o shim_file.o shim_dir.o \
            shim_sync.o shim_string.o shim_module.o shim_except.o shim_misc.o

$(SHIM_OUT): $(SHIM_OBJS) shim.map
    $(CC) -shared ... -o $@ $(SHIM_OBJS) $(SHIM_LDFLAGS)

$(SHIM_DBG_OUT): $(SHIM_OBJS_DBG) shim.map
    $(CC) -shared ... -DWINAPI_LOG_ENABLED -o $@ $(SHIM_OBJS_DBG) $(SHIM_DBG_LDFLAGS)
```

---

## 5. Refactoring Checklist (sequential)

Each step is independently compilable and testable.

| # | Task | Risk |
|---|------|------|
| R1 | Fix B1: `build_env_block` buffer overflow | Low |
| R2 | Fix B2: handle table locking — `handle_alloc_*` fills atomically | Medium |
| R3 | Fix B3: `GetCurrentDirectoryA` memory leak | Low |
| R4 | Fix B4: `SetFileAttributesA` ignores `stat` failure | Low |
| R5 | Fix B5: `utf8_to_wchar` 4-byte sequence handling | Low |
| R6 | Fix B6: `WideCharToMultiByte` honours `srclen` | Medium |
| R7 | Fix B7: `CompareStringW` honours `n1`/`n2` | Medium |
| R8 | Fix B8: `FlsFree` — implement a free-list for FLS slots | Low |
| R9 | Fix B9: `g_image_base` via `dl_iterate_phdr` in `shim_init` | Medium |
| R10 | Fix B11: remove PPMonstr address hardcode from `RtlCaptureContext` | Trivial |
| R11 | Fix B12: replace magic `4` with `ERROR_TOO_MANY_OPEN_FILES` | Trivial |
| R12 | I1: extract `fill_find_data()` helper | Low |
| R13 | I2: extract `make_open_flags()` helper; unify CreateFileA/W | Low |
| R14 | I3: make `FindFirstFileExW` call through `find_first_posix` | Low |
| R15 | I5: move `path_join` to path utilities section | Trivial |
| R16 | I6: add `LCMAP_UPPERCASE/LOWERCASE` to `shim_types.h` | Trivial |
| R17 | I7: add `static_assert` for `pthread_mutex_t` size | Trivial |
| R18 | I4: standardise logging — `LOG` for entry, `log_always` for events | Low |
| R19 | Split into modules per section 4 | Medium |

---

## 6. Out of Scope / Future Work

- **Thread creation hook**: Intercept `pthread_create` to call `shim_init_teb` on
  each new thread so GS is set for worker threads.
- **`CreateProcess` / `ShellExecute`**: Not implemented; PE programs that spawn
  child processes will fail.
- **Registry stubs**: `RegOpenKeyEx`, `RegQueryValueEx` etc. — common in MSVC CRT
  locale init; a minimal stub returning `ERROR_FILE_NOT_FOUND` would silence most
  failures.
- **`GetSystemInfo` / `GetNativeSystemInfo`**: CPU topology information; useful for
  programs that size thread pools from processor count.
- **Proper SEH**: `RtlUnwindEx` currently aborts; real unwinding through PE `.pdata`
  tables is architecturally feasible now that `pe2elf` preserves `.pdata`.
