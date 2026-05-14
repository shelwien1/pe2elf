# shim.cpp — Cleanup, Modular Redesign, and Refactoring Plan

Consolidated from eight independent reviews and verified against the actual
source (`shim.cpp` 2023 lines, `shim_types.h` 198 lines). Claims that the
source contradicts have been dropped; claims the source confirms carry a line
reference; bugs found in the source but missed by every reviewer are flagged
**(new)**.

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

## 2. Bugs and Correctness Issues

Severity is operational impact, not difficulty of fix.

### 2.1 High severity

**B1 — Buffer overflow in `build_env_block`** (line 458).
```c
for( char** e = environ; *e; ++e ) {
    int len = utf8_to_wchar(*e, wp, total);   /* total never shrinks */
    wp += len+1;
}
```
The destination capacity `total` is passed every iteration even though `wp`
keeps advancing. Last variables can write past the end of `g_env_block_w`
(`total * sizeof(uint16_t)` bytes).
Fix: `utf8_to_wchar(*e, wp, total - (size_t)(wp - g_env_block_w))`. Also free
`g_env_block` on the `g_env_block_w` allocation failure path (line 454).

Note: the allocation size `wsize = total * 2` (line 452) is *correct* in
bytes — worst case is ASCII (1 source byte → 2 wide bytes). A reviewer's
suggestion that surrogates can blow this out is wrong: 4-byte UTF-8 → 2
UTF-16 code units = 4 bytes, equal to source. The bug is the per-iteration
capacity argument, not the allocation size.

**B2 — Handle-table data races.**
Three coupled issues:
- `alloc_handle` (line 262) takes the mutex, marks the slot non-free, releases
  the mutex, and returns the index. Callers then write `.fd` / `.find` /
  `.dlhandle` *outside the lock* (e.g. line 783, 974, 1127). Between the
  unlock and the field write another thread can observe a half-initialised
  slot via `lookup()` or close it via `CloseHandle()`.
- `lookup` (line 275) and `get_fd` (line 284) read `g_handles[idx].kind`
  without taking the mutex.
- `CloseHandle` (line 787) and `FindClose` (line 1017) read kind, call
  `closedir`/`free`/`dlclose`, and clear the slot — all outside the mutex.

Fix: take `g_handles_mu` for the entire read-modify sequence. Reshape the API
to `handle_alloc_file(fd) → HANDLE`, `handle_alloc_find(ctx) → HANDLE`,
`handle_alloc_module(dlh) → HANDLE`, populating the payload while the lock is
held. Returns `INVALID_HANDLE_VALUE` on exhaustion.

**B3 — Memory leak in `GetCurrentDirectoryA`** (line 1793).
```c
return (DWORD)(strlen(getcwd(NULL, 0))+1);
```
`getcwd(NULL, 0)` allocates with `malloc`; the pointer is dropped. Also
`getcwd` can return NULL, in which case `strlen()` dereferences NULL.
Fix: save the pointer, NULL-check, compute the length, `free()`.

**B4 — `SetFileAttributesA` uses uninitialised `stat`** (lines 1784-1786).
```c
struct stat st;
stat(posix, &st);                              /* return value ignored */
chmod(posix, st.st_mode & ~(S_IWUSR|...));     /* garbage on stat failure */
```
Fix: check `stat` return and set `tls_last_error` on failure.

**B5 — `utf8_to_wchar` mishandles 4-byte sequences** (lines 367-370).
```c
} else {
    cp = '?';
    s++;                          /* consumes only the leading byte */
}
```
The 4-byte UTF-8 prefix `0xF0–0xF7` falls through to this else; the three
trailing continuation bytes (`0x80`–`0xBF`) are re-parsed as new code points
and produce garbage. Fix: after the `?`, skip continuation bytes
`while ((*s & 0xC0) == 0x80) s++;`. Any non-BMP code point (most emoji, CJK
Ext-B) currently corrupts the rest of the string.

**B6 — `WideCharToMultiByte` ignores `srclen`** (line 1384).
`(void)srclen;` is literal. Non-NUL-terminated wide buffers cause over-reads;
explicit-length callers get wrong output. Fix: when `srclen >= 0`, honour it.

**B7 — `CompareStringW` ignores `n1` / `n2`** (lines 1446-1447).
`(void)n1; (void)n2;`. Same shape as B6. Fix: honour both lengths in the
comparison loop.

**B8 — `FindFirstFileExW` / `FindNextFileW` use `WIN32_FIND_DATAA*`**
(lines 910, 984).
The `W`-suffixed functions are declared with the *narrow* struct in their
signatures, and they fill `cFileName` with raw `ent->d_name` bytes
(lines 965, 1010). Callers compiled against the real Windows headers expect
`WIN32_FIND_DATAW` with `wchar_t cFileName[260]`; they read garbage into
filename slots. Fix: add a real `WIN32_FIND_DATAW` type, populate
`cFileName` with UTF-16 converted from the POSIX `dirent` name, and split
the fill helper.

**B9 — `VirtualFree` semantics** (lines 627-634).
```c
if( type & MEM_RELEASE ) {
    munmap(addr, size);                                 /* size from caller */
} else if( type & MEM_DECOMMIT ) {
    mmap(addr, size, PROT_NONE,
         MAP_FIXED|MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);   /* return ignored */
}
```
- Windows requires `size == 0` for `MEM_RELEASE`; the caller's size is the
  reserved region. Forwarding to `munmap` can fail with `EINVAL` (size 0) or
  partially unmap, leaving torn mappings.
- `MEM_DECOMMIT` via `MAP_FIXED` silently replaces any existing mapping; the
  return value is dropped. A `mprotect(addr, size, PROT_NONE) +
  madvise(addr, size, MADV_DONTNEED)` pair is the closer match.

Fix: maintain an `mmap` tracker (sorted `(base, size)`) populated by
`VirtualAlloc` so `MEM_RELEASE` can find the original region; reject
`MEM_RELEASE` with non-zero `size`.

### 2.2 Medium severity

**B10 — `WriteConsoleW` ignores `nChars` and over-reports** (lines 1062-1073).
```c
char utf8[65536];
int nbytes = wchar_to_utf8((const uint16_t*)wbuf, utf8, sizeof(utf8)-1);
(void)nChars;                                /* nChars dropped */
DWORD written = 0;
BOOL r = WriteFile(h, utf8, (DWORD)nbytes, &written, NULL);
if( pWritten ) *pWritten = nChars;           /* over-reports on short writes */
```
- `nChars` is the wide-char count from the caller; `wchar_to_utf8` runs to
  NUL or the destination cap. If the input is not NUL-terminated within
  `nChars`, the conversion over-reads.
- `*pWritten` is set unconditionally to `nChars` whether `WriteFile` wrote
  fewer bytes (partial pipe write) or none. The reported count is wrong.
- The 64 KB stack buffer is large but bounded (`wchar_to_utf8` checks
  `i+4 < dstsz`), so no overflow. Acceptable for now but documents the
  truncation behaviour.

Fix: bound the conversion by `nChars`, compute the actual wide-char count
from the bytes written, and report that count via `*pWritten`.

**B11 — `HeapReAlloc` size==0** (lines 667-680).
`realloc(ptr, 0)` is implementation-defined: glibc historically frees `ptr`
and returns NULL or a unique pointer. The shim treats NULL as failure
(line 678). Fix: handle size==0 by returning a minimum-size allocation.

**B12 — `prot_from_protect` default returns RW** (lines 608-609).
Unknown `PAGE_*` flags (`PAGE_GUARD`, `PAGE_NOCACHE`, …) fall through to
`PROT_READ|PROT_WRITE`. Fix: return `PROT_NONE` for unrecognised flags.

**B13 — `g_image_base` is never updated** (line 392).
```c
static void* g_image_base = (void*)0x400000;     /* default; "overridden if needed" */
```
The comment says "overridden if needed" but nothing in the file does so.
`GetModuleHandleW(NULL)` (line 1084) returns this placeholder. PE code that
walks its own headers from this base reads kernel-mapped or unrelated memory.
Same root cause as the PEB `ImageBaseAddress` at line 138.
Fix: in the constructor, call `dl_iterate_phdr()` to find the main
executable's load address; write it into both `g_image_base` and the fake
PEB.

**B14 — Module-handle namespace conflation** (lines 1150-1165).
`GetProcAddress` distinguishes only `FAKE_WIN_MODULE` and NULL explicitly;
everything else goes through `handle_to_idx`. If the handle is
`g_image_base` (returned by `GetModuleHandleW(NULL)`, line 1084),
`handle_to_idx` returns -1 (because 0x400000 ≥ `MAX_HANDLES`) and the code
falls through to `RTLD_DEFAULT`. Symbols resolve from the whole address
space rather than from the main image. Fix: define a typed pseudo-handle
for the main image and recognise it explicitly in `GetProcAddress` and
`FreeLibrary`.

**B15 — `SetStdHandle` does not redirect underlying fds** (lines 713-733).
```c
g_handles[idx].fd = new_fd;        /* shim table only */
```
The CRT continues to use the original stdout/stderr fds via `printf` /
`fwrite`. Fix: also `dup2(new_fd, idx)` for `idx` in `{0,1,2}`.

**B16 — Last error is not visible at `gs:[0x68]`.**
`shim_init_teb` (line 198) populates the fake TEB with self-pointer (+0x30),
PEB (+0x60), PID (+0x40), TID (+0x48), TLS slots (+0x58), but **does not
populate +0x68 (LastErrorValue)**. Inlined MSVC code reading `gs:[0x68]`
sees zero, while exported `GetLastError` (line 582) returns the FS-relative
`tls_last_error`. Fix: store last error at TEB+0x68 and either also keep
`tls_last_error` mirrored or read directly from the TEB.

**B17 — Large-file support is implicit** (line 855).
`SetFilePointerEx` uses `lseek64` / `off64_t`. On 64-bit Linux this works,
but the dependency on the glibc `_LARGEFILE64_SOURCE` family is invisible
and breaks under stricter feature-test settings. `SetFilePointer` (line 1829)
and `SetEndOfFile` (line 1843, 1848) use plain `lseek` / `off_t` /
`ftruncate`. Fix: set `_FILE_OFFSET_BITS=64` globally and use `lseek` /
`off_t` everywhere — they are 64-bit under that macro on 64-bit Linux.

**B18a — `GetModuleFileNameA` size==0 underflow** (line 1803).
```c
ssize_t n = readlink("/proc/self/exe", buf, size-1);
```
With `size == 0`, `size - 1` underflows to `(DWORD)-1` and `readlink` gets a
huge length. Fix: explicit `size == 0` guard.

(The `W` variant on line 1106 uses an internal `tmp[PATH_MAX]` buffer with
`sizeof(tmp)-1`, so it does **not** have the same underflow. Reviewers that
asserted both variants had it were wrong about the wide version.)

**B18b — Both `GetModuleFileName{A,W}` ignore module handle** (lines 1103, 1801).
`(void)h;` then `readlink("/proc/self/exe", …)` regardless of which module
was asked for. Loaded shared objects cannot be identified. Fix: when `h` is
non-null and not the main image, resolve via `dladdr` against a stored
module-to-handle table; otherwise the current behaviour.

**B19 — `LoadLibraryExW` / `GetModuleHandleW` bypass path translation**
(lines 1086, 1117-1118).
Both convert the wide string to UTF-8 and hand it straight to `dlopen()`.
`C:\dir\foo.dll` is fed verbatim to the dynamic linker. Fix: route loader
paths through the same `win_path_to_posix` as the file APIs.

### 2.3 Lower severity / design

**B20 — `FlsFree` is a no-op** (line 1933).
```c
extern "C" EXPORT BOOL FlsFree(DWORD idx) { (void)idx; return TRUE; }
```
`g_fls_next` only increments (line 1927). After 64 allocations every
subsequent `FlsAlloc` returns `0xFFFFFFFF`, often making CRT init fail
silently. Note that the allocator itself *is* mutex-protected
(`g_fls_mu`, line 1926) — a reviewer that asserted otherwise was wrong;
the issue is just that slots never come back. Fix: free bitset.

**B21 — Hardcoded PPMonstr debug range in `RtlCaptureContext`**
(lines 1564-1566). A test-binary-specific heuristic baked into a "general"
API. Fix: remove, or replace with a generic "address inside the main
image's `.text`" check via `dl_iterate_phdr`.

**B22 — `tls_last_error = 4` magic constant** (lines 780, 971, 1684, 1723).
Four occurrences of the literal `4` in handle-exhaustion paths; the
constant is already named `ERROR_TOO_MANY_OPEN_FILES` in `shim_types.h`.

**B23 — `GetEnvironmentStringsW` cache becomes stale** (line 1204).
`build_env_block` runs once in the constructor (line 509). Subsequent
`SetEnvironmentVariableW` (line 1220) calls `setenv`/`unsetenv` but does
not invalidate `g_env_block_w`. Callers see stale data. Fix: regenerate
on demand or maintain a dirty flag.

**B24 — `HeapFree` low-pointer guard** (line 658).
```c
if( (uintptr_t)ptr<0x10000 && ptr!=NULL ) { ... return FALSE; }
```
A non-portable heuristic that rejects valid low-address allocations. Fix:
drop the guard; rely on `free()` to detect invalid frees.

**B25 — `win_path_to_posix` minimal sanitisation** (line 294).
Strips drive letters and `\\?\` prefixes; does not normalise `..`
traversal. Document the policy explicitly and either reject escaping `..`
or accept it deliberately.

**B26 — `Sleep` does not restart on `EINTR`** (line 1628-1631).
A signal during `nanosleep` returns short. Fix: loop with
`clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, …)`.

**B27 — `GetStringTypeW` / `GetStringTypeA` zero output** (lines 1438-1439,
1605-1606). Callers asking for character categories receive nothing. Fix:
at minimum, classify ASCII via `<ctype.h>` and add a small table for the
common Unicode ranges.

**B28 — `ReadConsoleInputA` always returns FALSE / 0 events** (line 2018).
Anything reading interactive console input fails. Fix: thin `INPUT_RECORD`
packer over `read(STDIN_FILENO, …)` with line-mode `tcgetattr`.

**B29 — `IsProcessorFeaturePresent` is a hardcoded table** (lines 560-577).
Should query `cpuid` (x86-64) or `getauxval(AT_HWCAP)`.

**B30 — `FormatMessageA` drops `va_list*`** (line 1981).
`(void)args;` is explicit. Parameterised messages produce only their static
text. Fix: emulate Windows positional escapes (`%1!s!`) against the
supplied `va_list`.

**B31 — `FileTimeToDosDateTime` underflow** (line 1894).
```c
*fatdate = (WORD)(((tm.tm_year-80)<<9) | ...);
```
No guard for `tm.tm_year < 80`; pre-1980 timestamps produce negative
intermediate values that wrap when cast to `WORD`. Fix: clamp or fail.

**B32 — `GetConsoleMode` returns hardcoded `0x1F`** (line 1046).
Should call `tcgetattr` and translate `c_lflag` to console-mode flags.

**B33 — `SetFileTime` ignores creation time** (line 1878).
`(void)ctime;`. Linux has no portable per-file btime API. Acceptable as a
limitation; document it explicitly rather than silently dropping.

**B34 — `TlsAlloc` returns raw `pthread_key_t`** (line 1292).
Cast to `DWORD`. Guest code expecting small contiguous Windows TLS slot
indices may index undersized arrays. Fix: indirection table mapping small
DWORD slot indices to `pthread_key_t`.

**B35 — `errno_to_win32` default returns 87** (line 113).
`ERROR_INVALID_PARAMETER` for everything unmapped squashes useful
distinctions. Add at least: `EAGAIN`/`EWOULDBLOCK` → `ERROR_BUSY`,
`EBUSY` → `ERROR_LOCK_VIOLATION`, `ETIMEDOUT` → `ERROR_TIMEOUT`,
`EINTR` → `ERROR_OPERATION_ABORTED`. `ENOSPC` is already mapped to 112.

**B36 — `UnhandledExceptionFilter` always returns
`EXCEPTION_EXECUTE_HANDLER`** (line 1510). Hides fatal bugs. Fix:
either terminate after the log or chain to the previous handler.

**B37 — `RtlCaptureContext` issues** (lines 1545-1570).
- The `lea (%%rip), %0` syntax has been rejected by some older toolchains;
  the portable form is `lea 0(%%rip), %0`. Verify against the current build
  matrix before assuming it doesn't build.
- Stack scan with hardcoded `0x140001000–0x140030000` (PPMonstr range, see
  B21) is a debug artifact, not a captured-context implementation.
- Hardcoded `CONTEXT` field offsets `+152`, `+160`, `+248` — should be
  `offsetof` against a real `CONTEXT` struct (which `shim_types.h` does not
  define).

**B38 — Crash-handler `vsnprintf` is not async-signal-safe** (lines 56, 471).
POSIX does not list `vsnprintf` as AS-safe. glibc happens to behave for
simple format strings, but the crash path should use `write(2, lit,
sizeof(lit)-1)` for fixed banner lines and a minimal `itoa` helper for
register dumps.

**B39 — `MAP_FIXED_NOREPLACE` is Linux 4.17+** (line 618).
Used unconditionally in `VirtualAlloc` when `addr` is non-NULL. Guard with
`#ifdef MAP_FIXED_NOREPLACE` and fall back to `mmap` plus post-checking the
returned address.

**B40 — `RtlUnwindEx` aborts** (lines 1513-1523).
Uses `fprintf(stderr, ...)` plus `abort()`. Any guest binary that invokes
SEH unwinding (which MSVC `__try`/`__except` lowers to) dies hard. Fix:
either implement a walk over a fake SEH chain or, more honestly, surface
a structured error to the caller rather than `abort`.

### 2.4 New bugs (not in any review)

**N1 — `tls_slots[64]` is `static`, not `__thread`** (line 208).
```c
static void* tls_slots[64] = {0};
*(void**)(fake_teb+0x58) = tls_slots;
```
`fake_teb` itself is `__thread` (line 124), but the array installed at
TEB+0x58 is function-static and process-global. All threads that ever call
`shim_init_teb()` install the same `tls_slots` pointer into their TEB+0x58.
Inlined `__readgsqword(0x58)` returns the same buffer for every thread.
Real Windows would have a per-thread array here. Fix: either `__thread`
the array, or `calloc` per call and let the per-thread fake TEB own its
own pointer.

**N2 — `<sys/utsname.h>` is unused** (line 29). No `uname()` call exists.
Remove alongside `<sys/prctl.h>`, `<sys/uio.h>`, `<wchar.h>`.

---

## 3. Design and Quality Improvements

**I1 — Extract `fill_find_data`.**
`FindFirstFileExW` (lines 952-965), `FindNextFileW` (lines 997-1010), and
`find_first_posix` (lines 1666-1679) all open-code the same `memset` +
`stat` + attribute + time + name-copy block. Factor out
`static void fill_find_data(WIN32_FIND_DATAA*, const char* fullpath, const char* name);`
plus a wide analogue once `WIN32_FIND_DATAW` exists.

(Note on `cFileName` termination: because each call-site `memset`s the
output struct to zero before `strncpy(..., 259)`, the 260-byte buffer is
guaranteed NUL-terminated even when `d_name` is exactly 259 characters.
A reviewer suggesting the field needs explicit termination was wrong about
*this* code; the safety comes from the prior `memset`. The helper should
preserve that property.)

**I2 — Extract `make_open_flags`.**
`CreateFileW` (lines 745-768) and `CreateFileA` (lines 1731-1753) build
POSIX `oflags` from `access` and `disp` with identical code. Extract
`static int make_open_flags(DWORD access, DWORD disp);`. Guard against the
`O_RDONLY | O_TRUNC` combination (rejected by Linux `open(2)` with
`EINVAL`); resolve to `O_RDWR | O_TRUNC` or fail explicitly.

**I3 — `FindFirstFileExW` should call through `find_first_posix`.**
After path conversion, hand off to the shared helper instead of keeping a
third copy of the dir/glob/opendir/readdir loop. `FindFirstFileA` (line 1696)
already does this; the W variant should match. (`FindNextFileA` at
line 1702 already forwards to `FindNextFileW`, which is fine.)

**I4 — Logging conventions.**
Three entry points are mixed today (`LOG`, `log_always`, `log_write`).
`log_always` is currently `#define log_always log_write` (line 68) — i.e.
identical to `log_write` and a no-op in release builds (line 76). A
reviewer's claim that `log_always` "always goes to stderr in release" is
wrong. Settle on: `LOG` for routine entry tracing, `log_always` for events
(crashes, abnormal paths), `log_write` as the in-handler primitive. Make
the destination switch on a runtime env-var (`WINAPI_SHIM_LOG`) so a
release shim does not need rebuilding for log capture.

**I5 — Move `path_join` next to other path utilities.**
Currently embedded in section 7.6 at line 902. Belongs with
`win_path_to_posix` and the encoding helpers.

**I6 — Name the `LCMAP_*` flags.**
`LCMapStringW` tests `flags & 0x200` (uppercase, line 1402) and
`flags & 0x100` (lowercase, line 1410); `LCMapStringA` does the same
(line 1614). `CompareStringW` tests `flags & 0x1` (line 1457). Add
`LCMAP_UPPERCASE 0x200`, `LCMAP_LOWERCASE 0x100`, `NORM_IGNORECASE 0x1`
(and the `CSTR_*` return values 1/2/3) to `shim_types.h` and use the
names.

**I7 — `CRITICAL_SECTION` size assertion.**
`CRITICAL_SECTION` is `uint8_t opaque[40]` in `shim_types.h`; the code
casts to `pthread_mutex_t*` at line 1261. On glibc x86-64
`sizeof(pthread_mutex_t) == 40`, which fits exactly — a fragile
coincidence. Add
`static_assert(sizeof(pthread_mutex_t) <= sizeof(CRITICAL_SECTION), …);`
and similar checks for `FILETIME`, `LARGE_INTEGER`, `STARTUPINFOA/W`, and
the find-data structs.

**I8 — Worker-thread TEB.**
`shim_init_teb` is called only from the `__attribute__((constructor))`
(line 506). Worker threads spawned by the PE binary never have GS set;
any inlined `__readgsqword()` traps. See also N1 — even fixing the call
site requires fixing the per-thread `tls_slots`. Proper fix: intercept
`pthread_create` (`dlsym(RTLD_NEXT, ...)`) with a wrapper that calls
`shim_thread_attach()`. At minimum, document the limitation where the
constructor lives.

**I9 — Replace raw globals with subsystem state structs.**
Group the scattered globals (`g_handles`, `g_handles_mu`, `g_cmdline`,
`g_env_block`, `g_image_base`, `g_unhandled_filter`, `g_log_fd`,
`g_fls_next`, …) into named structs: `ShimProcessState`,
`ShimHandleTable`, `ShimLogger`, `ShimRuntimeConfig`. They remain
singletons; the goal is one declared owner per resource and a single
init order.

**I10 — Thin exports.**
Each `EXPORT` function: validate, call a helper, translate result, set
last-error. Implementation moves to its named subsystem TU.

**I11 — Centralise error translation.**
`errno_to_win32` lives in one TU; every POSIX wrapper routes through it.

**I12 — Typed internal handles.**
Public surface keeps `HANDLE`; internally use distinct `FileHandle`,
`FindHandle`, `ModuleHandle` (still implemented as small indices, but
the C++ types prevent cross-subsystem reuse and make `H_KIND` checks
mechanical).

**I13 — Symbol visibility.**
The file already does `#pragma GCC visibility push(hidden)` (line 39)
between the internal helpers and the exports, and `EXPORT` carries
`visibility("default")`. Keep this; combined with a versioned `shim.map`
the dynamic symbol set is fully explicit.

---

## 4. Rare / Unusual `#include`s — Justification and Disposition

| Header | Status | Reason |
|---|---|---|
| `<asm/prctl.h>` | **Keep** (x86_64) | Defines `ARCH_SET_GS`. The shim repoints GS to the fake TEB via `syscall(SYS_arch_prctl, ARCH_SET_GS, …)` (line 212) so inlined MSVC code reading `gs:[0x30]` / `gs:[0x60]` / `gs:[0x68]` sees the right values. glibc provides no user-space wrapper. |
| `<sys/prctl.h>` (line 24) | **Remove** | No `prctl()` call exists. `ARCH_SET_GS` comes from `<asm/prctl.h>`. |
| `<sys/syscall.h>` (line 26) | **Keep** | Provides `SYS_arch_prctl` and `SYS_gettid` (line 206, 532). `gettid()` entered glibc only in 2.30; older distros still need the raw syscall. |
| `<ucontext.h>` (line 31) | **Keep** (x86_64) | Crash handler inspects `ucontext_t → mcontext_t → gregs[REG_RIP]` etc. (lines 470-476). Wrap in `#ifdef __x86_64__`; the names are glibc-specific. |
| `<execinfo.h>` (line 11) | **Keep** (GNU) | `backtrace()` in `log_backtrace` (line 542). Guard with `#ifdef __GLIBC__`; link with `-rdynamic`. |
| `<fnmatch.h>` (line 13) | **Keep** | `fnmatch()` for `FindFirstFile*` wildcard matching (lines 949, 994, 1664) with `FNM_NOESCAPE`. |
| `<malloc.h>` (line 16) | **Keep** (GNU) | `malloc_usable_size()` in `HeapSize` (line 685) and `HeapReAlloc` zero-fill (line 670). No POSIX equivalent. Provide a shadow allocation-size table for musl. |
| `<sys/uio.h>` (line 28) | **Remove** | No `readv` / `writev` / `iovec` use. |
| `<sys/utsname.h>` (line 29) | **Remove** **(new)** | No `uname()` call. Missed by every reviewer. |
| `<wchar.h>` (line 33) | **Remove** | Shim defines its own UTF-16 type (`uint16_t`); no `wcs*` call. |
| `<locale.h>` (line 15) | **Keep** | `setlocale(LC_ALL, "")` in the constructor (line 503). |

The rest of the includes (`<dlfcn.h>`, `<pthread.h>`, `<signal.h>`,
`<sys/mman.h>`, `<sys/stat.h>`, `<dirent.h>`, `<fcntl.h>`, `<unistd.h>`,
`<time.h>`, `<errno.h>`, `<stdarg.h>`, `<stdio.h>`, `<stdlib.h>`,
`<string.h>`, `<limits.h>`, `<sys/types.h>`) are unsurprising and stay.

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

## 9. Out of Scope

- Thread-creation hook beyond a basic `pthread_create` interceptor. Real
  Windows TEB initialisation also touches the LDR list and structured
  exception chain.
- `CreateProcess` / `ShellExecute`. PE programs that spawn child processes
  cannot be supported without a full PE loader; polite failure is the
  current target.
- Registry stubs (`RegOpenKeyEx`, …). A stub returning `ERROR_FILE_NOT_FOUND`
  would silence most MSVC CRT locale-init failures.
- `GetSystemInfo` / `GetNativeSystemInfo` — map to
  `sysconf(_SC_NPROCESSORS_*)` etc.
- Real SEH unwinding via PE `.pdata`. Architecturally feasible if
  pe2elf-emitted code preserves `.pdata`, but a sizable subsystem on its
  own.
- Async I/O / `OVERLAPPED` / IOCP. Internal interfaces should leave room
  for `pread`/`pwrite`-shaped operations so the door is not closed.

---

## 10. Reviewer-Claim Verification Summary

Items that *did not match* the source and were dropped or corrected:

- "`cFileName` is left unterminated" — wrong. The `memset(pfd, 0, sizeof(*pfd))`
  before each `strncpy(..., 259)` guarantees byte [259] is NUL.
- "`wsize = total * 2` is too small because of surrogates" — wrong.
  UTF-16-from-UTF-8 worst case is 2 bytes wide per source byte (ASCII case),
  so the allocation is sufficient. The real bug at the same site is B1.
- "`LoadLibraryExW` leaks `dlopen` handles on alloc failure" — wrong. Line
  1130 does `dlclose(h)` on that path.
- "`GetModuleFileNameW` underflows on `size == 0`" — wrong for the W
  variant (it uses an internal `tmp[PATH_MAX]` buffer with `sizeof(tmp)-1`);
  the bug exists in the A variant only (B18a).
- "FLS allocation is not synchronised" — wrong. `g_fls_mu` (line 1922)
  protects `g_fls_next` (B20 acknowledges this).
- "`log_always` always prints in release builds" — wrong. It is
  `#define log_always log_write`, and `log_write` is a no-op outside
  `WINAPI_LOG_ENABLED`.
- Various specific typo claims ("missing dereference in `wchar_to_utf8`
  surrogate check at line 328", "`while( p++ )` typo in `LCMapStringW`",
  "`total2` undeclared in `build_env_block`", "`&` `&` spacing artifacts")
  — none of these are present in the source.
- "`environ` requires an explicit `extern char**` declaration" —
  build-environment dependent; on the toolchains the file already compiles
  under (it includes `<stdlib.h>` and `<unistd.h>`), `environ` is reachable.
  Mention if porting to a stricter feature-test profile, otherwise drop.

Items found in the source that no review caught: N1 (shared `tls_slots`
array across threads), N2 (`<sys/utsname.h>` unused).

---

*End of document.*
