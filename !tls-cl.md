# TLS support in `shim.cpp`

This document describes how `shim.cpp` emulates the Windows Thread Local
Storage model for PE→ELF converted binaries, and enumerates the bugs, races,
and ABI mismatches in that emulation.

The PE TLS model has two distinct mechanisms (both backed by the TEB):

| | Static TLS (`__declspec(thread)`) | Dynamic TLS (`Tls*` API) |
|---|---|---|
| Index source | `*IMAGE_TLS_DIRECTORY.AddressOfIndex` | returned by `TlsAlloc` |
| Storage location | indirected through `TEB+0x58` (ThreadLocalStoragePointer) → array → block | direct slots at `TEB+0x1480` (slots 0–63) and `TEB+0x1780` (expansion, 64–1087) |
| Code pattern | `mov rax, gs:[0x58]; mov rax,[rax+idx*8]; mov v,[rax+off]` | `kernel32!TlsGetValue` call, or inline `gs:[0x1480+idx*8]` |
| Init by loader | template copied per thread | slots zeroed per thread |

The shim implements only the `TEB+0x58` indirection and reuses the same
64-slot array for both purposes. The implications are discussed at the end.

---

## Startup: `shim_init` constructor

`shim.cpp` (`__attribute__((constructor)) shim_init`) drives general
initialization in this order:

1. `init_fake_peb()` — builds a global 4 KiB fake PEB with a self-referential
   empty `PEB_LDR_DATA`, minimal `RTL_USER_PROCESS_PARAMETERS`, and a
   hard-coded `ImageBaseAddress = 0x400000` at `PEB+0x10`.
2. `discover_image_base()` — captures the real ELF base.
3. `handles_init()` — fills the 4096-entry `g_handles[]` slot table; slots
   0/1/2 are pre-bound to stdin/stdout/stderr.
4. `shim_init_teb()` — initializes the main thread's fake TEB and points
   `GS` at it (see next section).
5. `log_init()`, `rebuild_cmdline()`, `build_env_block()`, `build_argv()`,
   `init_fake_iob()`, `install_signal_handlers()`.

TLS registration, static-slot allocation, and `DLL_PROCESS_ATTACH` callbacks
are **not** performed here. They are handled by `shim_register_tls()`, which
is called from the pe2elf-generated startup thunk before PE_ENTRY runs.

---

## Startup thunk and `shim_register_tls`

The pe2elf converter emits a small startup thunk as the ELF entry point
(`e_entry`). The thunk runs after the dynamic linker has finished (so
`shim_init` has already run) and before the PE entry point:

```asm
; trampoline layout (kTrampolineSize = 80 bytes)
+0:  lea rdi,[rip+0x19]      ; → ShimTlsInfo struct at +32
+7:  call [rip+0x0b]         ; → slot@+24 (filled by RELA R_X86_64_64 shim_register_tls)
+13: and rsp,-16             ; realign stack
+17: push rax                ; RSP%16 → 8: simulate PE entry via CALL
+18: jmp rel32               ; → PE_ENTRY
+24: [8-byte slot]            R_X86_64_64 → shim_register_tls (filled at load time)
+32: ShimTlsInfo             6×uint64: template_va, template_sz, zero_fill,
                              align_chars, index_va, callbacks_va
```

`shim_register_tls` (`shim.cpp`) receives one argument — a pointer to the
embedded `ShimTlsInfo` struct — and performs all static TLS setup:

```cpp
extern "C" void shim_register_tls(const ShimTlsInfo* info) {
  g_tls_template_va  = info->template_va;
  g_tls_template_sz  = info->template_sz;
  g_tls_zero_fill    = info->zero_fill;
  g_tls_index_addr   = info->index_va  ? (uint32_t*)info->index_va  : nullptr;
  g_tls_callbacks_va = info->callbacks_va ? (uint64_t*)info->callbacks_va : nullptr;
  (void)info->align_chars; // TODO: posix_memalign when alignment > 16
  if( g_tls_index_addr ) {
    // claim first free slot from g_tls_alloc_used, write to *AddressOfIndex
    *g_tls_index_addr = g_tls_static_idx;
    tls_static_init_thread();   // populate main thread's static block
  }
  run_tls_callbacks(1);         // DLL_PROCESS_ATTACH
}
```

`tls_static_init_thread` (`shim.cpp`) allocates `template_sz + zero_fill`
bytes via `calloc` (which zeros the zero-fill portion automatically), copies
the template, and stores the pointer at `slots[g_tls_static_idx]`:

```cpp
size_t sz = g_tls_template_sz + g_tls_zero_fill;
if( sz == 0 ) sz = 64;
void* buf = calloc(1, sz);
if( g_tls_template_va && g_tls_template_sz )
    memcpy(buf, (void*)g_tls_template_va, g_tls_template_sz);
slots[g_tls_static_idx] = buf;
```

This matches the indirected MSVC access pattern
`gs:[0x58] → array → [idx]*8 → block`.

The pe2elf converter reads the TLS directory fields **after** `rebase()` runs,
so the VAs in `ShimTlsInfo` are always in the final address space.

---

## TEB emulation

```cpp
static __thread uint8_t fake_teb[0x2000];     // shim.cpp — 8 KiB per thread
static uint8_t          fake_peb[0x1000];     // shim.cpp — process-global
```

`shim_init_teb()` (`shim.cpp`) is idempotent: it checks the self-pointer
at `+0x30` and returns immediately if already initialized, preventing
double-init when both the `pthread_create` interceptor and
`thread_trampoline` call it on the same thread.

Populated per-thread fields:

| Offset | Field | Source |
|---|---|---|
| `+0x30` | `NtTib.Self` | `&fake_teb[0]` |
| `+0x40` | `ClientId.UniqueProcess` (written as `uint32_t`) | `getpid()` |
| `+0x48` | `ClientId.UniqueThread` (written as `uint32_t`) | `gettid()` |
| `+0x58` | `ThreadLocalStoragePointer` | `calloc(64, 8)` |
| `+0x60` | `ProcessEnvironmentBlock` | `&fake_peb[0]` |
| `+0x68` | `LastErrorValue` | mirrored from `tls_last_error` via `SET_LAST_ERROR` macro |

The TEB is published to user code by
`arch_prctl(ARCH_SET_GS, fake_teb)` so that MSVC-generated
`mov rax, gs:[0x68]` for `GetLastError`, `gs:[0x30]` for `NtCurrentTeb`,
and `gs:[0x58]` for TLS access all work.

Each thread's slot array is registered with a `pthread_key_t` whose
destructor is `free` (`shim.cpp`), so the *array* is reclaimed
when the thread exits — but the pointers *inside* the array (static-TLS
buffer, any `TlsSetValue` values) are not touched by the destructor
(see leak note below).

---

## `kernel32_CreateThread` and the two trampolines

There are two completely separate thread trampolines in this shim.

### Trampoline A: `thread_trampoline` (CreateThread's own)

In `shim_kernel32_sync.hpp`:

```cpp
static void* thread_trampoline(void* arg) {
  ThreadStart ts = *(ThreadStart*)arg;
  free(arg);
  shim_init_teb();
  run_tls_callbacks(2);      // DLL_THREAD_ATTACH
  tls_static_init_thread();  // populate static TLS block
  pthread_once(&g_thread_key_once, thread_key_init);
  pthread_setspecific(g_thread_obj_key, ts.obj);
  uint32_t ret = ts.fn(ts.param);
  run_tls_callbacks(3);      // DLL_THREAD_DETACH
  thread_finish(ts.obj, (int64_t)(uint32_t)ret);
  return nullptr;
}
```

With respect to the Windows model this is correct in the *normal-return*
case — TEB, callbacks, static block, then user fn, then detach
callbacks. The exit-via-`ExitThread` case bypasses the post-fn steps
(see below).

`kernel32_CreateThread` (`shim_kernel32_sync.hpp`):

1. `calloc`s a `ThreadObj` (refcount=1, mutex+cond initialized).
2. Allocates a `ThreadStart` carrying `{fn, param, obj}`.
3. Allocates an H_THREAD handle pointing at `ThreadObj`.
4. Calls `pthread_create(&obj->tid, …, thread_trampoline, ts)`.

The pthread TID is stored on the `ThreadObj` so that
`sync_obj_destroy` can join or detach it.

### Trampoline B: the `pthread_create` override (`shim.cpp`)

The shim also overrides `pthread_create` itself with default visibility
so any direct pthread call from the PE binary funnels through:

```cpp
static void* shim_thread_trampoline(void* p) {
  ShimThreadArgs* ta = (ShimThreadArgs*)p;
  void* (*fn)(void*) = ta->fn;
  void* arg = ta->arg;
  free(ta);
  shim_thread_attach();     // == shim_init_teb()
  return fn(arg);
}
```

This trampoline only sets up the fake TEB — it does **not** call TLS
callbacks and does **not** populate the static TLS block.

### The double-call path

Because `kernel32_CreateThread` calls `pthread_create`, and the shim's
own `pthread_create` is the visible symbol, every `CreateThread` thread
goes through *both* trampolines:

```
kernel32_CreateThread
  → pthread_create (our override)
      → real pthread_create with shim_thread_trampoline
          [new thread]
          → shim_thread_trampoline
              → shim_init_teb()                # first call
              → thread_trampoline               # the original fn
                  → shim_init_teb()             # second call — no-op (idempotent)
                  → run_tls_callbacks(2)
                  → tls_static_init_thread()
                  → fn(...)
```

`shim_init_teb` is idempotent: it checks `*(void**)(fake_teb+0x30) ==
fake_teb` and returns immediately on the second call, so no memory is
leaked and the TEB is not re-zeroed. The double-call is otherwise
harmless.

### Threads that bypass `kernel32_CreateThread`

If the PE binary calls `pthread_create` directly, only Trampoline B runs.
Those threads get:

- a fake TEB ✓
- TLS slot array at `gs:[0x58]` ✓
- **no** `DLL_THREAD_ATTACH` callback ✗
- **no** static TLS block ✗
- **no** `DLL_THREAD_DETACH` callback ✗ (no post-fn hook in Trampoline B)

This affects MSVC STL `std::thread` when compiled targeting a POSIX threading
model, or any code that calls `pthread_create` directly.

### Threads with no trampoline at all

Threads created via raw `clone(2)`, or threads spawned by a library
loaded by `dlopen` that does not route through `pthread_create`, will
have **no fake TEB** at all. Subsequent inlined `gs:[…]` accesses from
PE code on that thread read whatever the underlying glibc left in
`GS` — almost certainly not a Windows TEB, so reads of LastError, TLS
slots, etc. return garbage or fault. In practice rare; possible.

---

## `kernel32_Tls*` functions

All four live in `shim.cpp`. They are backed by the same
per-thread 64-slot array at `gs:[0x58]` and the same global bitset:

```cpp
static pthread_mutex_t g_tls_alloc_mu = PTHREAD_MUTEX_INITIALIZER;
static uint64_t        g_tls_alloc_used = 0;
```

| Function | Behavior |
|---|---|
| `TlsAlloc()` | Scan `g_tls_alloc_used`, claim first clear bit, return its index; `0xFFFFFFFF` if all 64 are taken. |
| `TlsFree(idx)` | Clear the bit; return `TRUE`. |
| `TlsGetValue(idx)` | `slots = gs:[0x58]; return slots[idx];` clears LastError to 0 first. |
| `TlsSetValue(idx, v)` | `slots[idx] = v;` |

`tls_get_slots()` (`shim.cpp`) is a single `mov %gs:0x58, %0`.

### Issues

1. **Hard 64-slot ceiling.** Windows guarantees a minimum of 64
   (`TLS_MINIMUM_AVAILABLE`) but actually provides 1088 via the
   expansion array at `TEB+0x1780`. PE binaries that consume more than
   64 slots — common when multiple statically-linked DLLs each grab a
   handful — will see `TlsAlloc` returning `0xFFFFFFFF` and likely
   crash.
2. **The static-TLS slot competes with `TlsAlloc`.** `shim_register_tls`
   reserves `g_tls_static_idx` from the same bitset, so only 63
   dynamic slots remain. Good for safety; surprising for capacity.
3. **`TlsFree` does not zero the slot in any thread.** Windows
   guarantees the slot is reset to 0 in all threads when freed. The
   shim only clears the bitset. If the slot is later reissued by
   another `TlsAlloc`, the new owner can observe stale per-thread
   values.
4. **`TlsGetValue` does not validate against the bitset.** On Windows
   `TlsGetValue` on a freed index returns 0 with no error; the shim
   returns whatever stale pointer was last written. Combined with #3,
   a freed-then-realloced slot leaks data across subscribers.
5. **Inline-TLS ABI mismatch.** MSVC's `TlsGetValue`/`TlsSetValue` are
   sometimes inlined as direct `gs:[0x1480 + idx*8]` reads/writes
   (slots 0–63 live inside the TEB on Windows, *not* indirected through
   `+0x58`). The shim's fake TEB is `0x2000` bytes so those addresses
   land inside the array and don't fault — but they read/write
   uninitialized zero bytes in `fake_teb`, not the `kernel32_TlsSetValue`
   storage. A binary that mixes inlined and out-of-line access patterns
   sees two different views of "the same" slot.
6. **`Characteristics` (alignment) is ignored.** The `calloc` for the
   static TLS block has malloc-grade alignment (16 on glibc x86_64).
   PE TLS templates with alignment requirements > 16 (SSE arrays, etc.)
   get under-aligned blocks. The `align_chars` field is received by
   `shim_register_tls` but currently discarded with a `TODO`.
7. **`g_tls_static_idx == 0xFFFFFFFF` is written to `*AddressOfIndex`**
   if the startup scan finds no free slot. That degenerate case turns
   every static-TLS access into `gs:[0x58][0xFFFFFFFF]` and is fatal.
   The bitset is empty at startup so the for-loop will always find slot
   0, but the safety check is missing.

### FLS (Fiber Local Storage) — same family, separate storage

`kernel32_FlsAlloc`/`Free`/`Get`/`SetValue` (`shim.cpp`) are
backed by `static __thread void* g_fls[64]` and a global
`g_fls_used` bitset. Note this is a *different* per-thread array from
the TLS slots — FLS uses glibc `__thread` (FS-based), TLS uses the fake
TEB (GS-based).

`FlsAlloc(callback)` **silently discards its `callback` argument**
(`(void)callback;`). On Windows, that callback is invoked at thread
exit for every non-NULL FLS value the thread set, and at `FlsFree`
time for every thread that has a non-NULL value. The shim never stores
or invokes it. Any code relying on FLS callbacks for resource cleanup
(notably ucrtbase's per-thread destructor chain, which uses FLS
internally) will leak.

---

## `kernel32_CloseHandle` and `WaitForSingleObject` interaction

The shim refcounts sync objects (`refcount` is the first field of
`MutexObj`/`EventObj`/`SemaphoreObj`/`ThreadObj` so it can be reached
generically as `*(int*)ptr`).

### `WaitForSingleObject` (`shim_kernel32_sync.hpp`)

The lookup/refcount bump is atomic under `g_handles_mu`. The
decrement+destroy at the bottom is also under `g_handles_mu`. The
`H_MUTEX` exit path correctly unlocks the mutex before destroying when
refcount reaches zero, avoiding POSIX UB on `pthread_mutex_destroy` of
a locked mutex.

### `kernel32_CloseHandle` (`shim.cpp`)

For sync handles it reads `kind` and `ptr` under `g_handles_mu`,
marks the slot `H_FREE`, then decrements the refcount under the same
mutex. Only when the refcount hits zero does it call
`sync_obj_destroy(kind, ptr)`. This is the core invariant that lets
`WaitForSingleObject` finish safely even if `CloseHandle` runs while a
wait is in flight.

### `kernel32_ReleaseMutex` (`shim_kernel32_sync.hpp`)

Correctly bumps the refcount under `g_handles_mu` before releasing the
lock, performs the unlock, then decrements the refcount and calls
`sync_obj_destroy` if it reaches zero — matching the `WaitForSingleObject`
pattern.

### Thread-handle destruction (`shim_kernel32_sync.hpp`)

```cpp
case H_THREAD: {
  ThreadObj* t = (ThreadObj*)ptr;
  pthread_mutex_lock(&t->mu);
  bool done = t->done;
  pthread_mutex_unlock(&t->mu);
  if( t->tid ) {
    if( done ) pthread_join(t->tid, nullptr);
    else        pthread_detach(t->tid);
  }
  pthread_mutex_destroy(&t->mu); pthread_cond_destroy(&t->cv); free(t);
  break;
}
```

`tid == 0` marks the synthetic `H_THREAD` that `DuplicateHandle` of
`GetCurrentThread()` creates for unmanaged threads; join/detach is skipped
there.

### Issues

1. **TOCTOU in the remaining non-wait sync APIs.** `SetEvent`,
   `ResetEvent`, `ReleaseSemaphore`, `GetExitCodeThread`, and
   `signal_handle` all read `g_handles[idx].kind` and
   `g_handles[idx].ptr` **without holding `g_handles_mu`** and without
   bumping the refcount. A concurrent `CloseHandle` from another thread
   can drop the refcount to zero between the load and the dereference,
   freeing the object through `sync_obj_destroy` and turning the
   dereference into a use-after-free.
2. **`CloseHandle` on a held mutex destroys a locked mutex.** Scenario:
   thread A `WaitForSingleObject(mutex, INFINITE)` returns
   `WAIT_OBJECT_0` (mutex locked, refcount back to 1 after Wait's own
   decrement); thread B then calls `CloseHandle(mutex)`, dropping the
   refcount to 0; `CloseHandle`'s destroy path calls
   `pthread_mutex_destroy` on a still-locked mutex (POSIX UB).
   Thread A's later `ReleaseMutex` finds the slot now `H_FREE` and
   returns `FALSE` with `ERROR_INVALID_HANDLE`. The application is
   misusing the API, but the resulting UB is in shim code.
3. **`GetCurrentThread()` pseudo-handle (`-2`).** `DuplicateHandle`
   special-cases it. Most other thread APIs do not.
   `GetExitCodeThread(GetCurrentThread(), …)` returns `FALSE` with
   `ERROR_INVALID_HANDLE`, and `WaitForSingleObject(GetCurrentThread(),
   0)` returns `WAIT_FAILED`. Real Windows accepts the pseudo-handle in
   both.
4. **`CreateThread` returns `INVALID_HANDLE_VALUE` (`-1`) on failure**.
   Real Windows returns `NULL`. Code that checks `if (h == NULL)` will
   think a failed `CreateThread` succeeded.
5. **`CreateThread`'s `flags` (incl. `CREATE_SUSPENDED`) and `stack`
   size are ignored.** Threads always start immediately at default
   stack. The matching `ResumeThread` is a stub returning 1, so binaries
   that suspend-and-resume during init silently skip whatever was
   supposed to happen before resume.
6. **Mutexes are recursive** (`shim_kernel32_sync.hpp`). Windows
   mutex objects *are* recursive, so this is right.

---

## Bugs and gaps beyond what's already noted

### `ExitThread` skips `DLL_THREAD_DETACH`

```cpp
extern "C" EXPORT void kernel32_ExitThread(DWORD code) {
  pthread_once(&g_thread_key_once, thread_key_init);
  thread_finish((ThreadObj*)pthread_getspecific(g_thread_obj_key),
                (int64_t)(uint32_t)code);
  pthread_exit(nullptr);
}
```

The corresponding sequence in `thread_trampoline` is:

```cpp
uint32_t ret = ts.fn(ts.param);
run_tls_callbacks(3);     // DLL_THREAD_DETACH
thread_finish(...);
```

If `fn()` calls `ExitThread` (directly or via the CRT `_endthreadex`,
which wraps `ExitThread`), the post-`fn` steps in `thread_trampoline`
are never reached: `pthread_exit` unwinds through them. So
`DLL_THREAD_DETACH` is silently skipped for any thread that exits via
`ExitThread`.

### Per-thread static TLS buffer leaks on thread exit

`tls_static_init_thread` allocates a buffer with `calloc(1, sz)` and
stores its pointer in `slots[g_tls_static_idx]`. At thread exit, the
pthread-key destructor (`shim.cpp`) frees `slots` itself but does
not iterate it. The static-TLS buffer (and any pointer ever written
through `TlsSetValue` to a value the *shim itself* allocated) leaks at
thread exit. For long-lived processes that create and join many
threads this is unbounded.

A correct teardown would walk the slots array in the destructor,
freeing `slots[g_tls_static_idx]` and any other entries the shim
itself allocated. Untouched `TlsSetValue` values that came from the
application stay the application's responsibility (Windows doesn't
free them either).

### `LoadLibrary` is a dummy — worth a comment saying so

`kernel32_LoadLibraryExW` (`shim.cpp`) just does
`dlopen(..., RTLD_LAZY|RTLD_GLOBAL)` and returns a handle slot. This
is by design — the converter resolves all PE imports at conversion
time, so `LoadLibrary` exists only to satisfy explicit runtime lookups
and the result is mostly used as a token for subsequent
`GetProcAddress` calls into the shim's own exports. Loading a real PE
DLL on Linux is out of scope.

The single-module assumption is baked into the global TLS state
(`g_tls_callbacks_va`, `g_tls_index_addr`, `g_tls_static_idx`) — there
is nowhere to record additional modules' TLS state. Implementing full
TLS for `LoadLibrary`-loaded modules is out of scope given that the
converter has already flattened the import graph.

What is worth doing is annotating the `LoadLibrary*` and
`FreeLibrary` functions with a comment to that effect, so future
readers don't reach for the TLS machinery thinking it should generalize.

### No `DLL_PROCESS_DETACH`

`run_tls_callbacks(1)` is invoked from `shim_register_tls`; there is no
matching `__attribute__((destructor))` or `atexit(run_tls_callbacks_0)`.
The mingw runtime relies on `DLL_PROCESS_DETACH` to run pending TLS
destructors and clean up its critical section. None of that runs at
process exit. The kernel reclaims the address space, so this is mostly
cosmetic for the main process, but a parent monitoring child cleanup
behaviour will see the difference.

### No fault isolation around TLS callbacks

`run_tls_callbacks` (`shim.cpp`) calls each callback directly
with no SEH wrapping, no `sigsetjmp`, no `try/catch`. The Windows
loader installs an exception filter around TLS-callback invocation so
a faulting callback doesn't kill process init. Here, a faulting
callback escapes through `run_tls_callbacks` into the thunk context
and the process dies. (The TLS callback ABI is `ms_abi`, so a C++
exception thrown out of one would also be undefined behaviour at the
ABI boundary.)

### `fake_teb` is 0x2000 bytes; real TEB is bigger

A real Win10 x64 TEB is around 0x1840 + the TEB-extension area, but
common offsets accessed by ucrtbase and mingw runtimes include:

- `TEB+0x1480` — `TlsSlots[64]` (inline TLS, see #5 in the Tls section)
- `TEB+0x1780` — `TlsExpansionSlots`
- `TEB+0x17C8` — `GdiBatchCount` etc.

`0x1780` and `0x17C8` fit inside `0x2000`, so accesses don't fault, but
all of those fields are zero. Inline reads of expansion-slot TLS,
GDI/Win32k state, or the activation context stack get NULL.

### Stack-bounds fields are zero

`TEB+0x08 StackBase` and `TEB+0x10 StackLimit` are both 0. Any code that
checks the stack range (CRT stack-overflow probes, SEH unwind hints,
fiber bookkeeping) will see degenerate bounds.

### Hard-coded `ImageBaseAddress = 0x400000`

`init_fake_peb` always writes `0x400000` into `PEB+0x10`. If the ELF was
linked at a different base (e.g. via `--base=`), code that walks
`GetModuleHandle(NULL) == PEB.ImageBaseAddress` against the actual loaded
base will mis-identify its own module. The `discover_image_base()` call
exists for exactly this but its result isn't fed back into the PEB.

### Empty loader list

The fake `PEB_LDR_DATA` lists are empty self-referencing rings, so a
thread walking the loader's module list to find DLLs sees no modules.
The PE binary itself isn't in the list.

### The pthread_create override has a benign initialization race

`pthread_create` resolves `dlsym(RTLD_NEXT, "pthread_create")` on first
call and caches it in a non-atomic static. Two threads racing the first
call may both run `dlsym`. `dlsym` itself is thread-safe and idempotent
here, and the write is a single pointer store, so the race is benign in
practice — but it's technically a data race.

### `fake_teb` may not be page-aligned

`__thread uint8_t fake_teb[0x2000]` gets default alignment (16 on x86_64
glibc). Windows TEBs are page-aligned and some inline code uses
`and rax, ~0xFFF` to round down to TEB base from any pointer into the
TEB. That pattern fails here.

### `kernel32_GetCurrentThreadId` calls `gettid()` every time

`shim.cpp` does `(DWORD)syscall(SYS_gettid)` per call. The fake TEB
already caches the TID at `+0x48`. A hot loop calling
`GetCurrentThreadId()` will syscall on every iteration when it could
just read `gs:[0x48]`.

### `tls_static_init_thread` idempotency hinges on the slot staying NULL

```cpp
if( slots[g_tls_static_idx] ) return;
```

If anything writes a non-NULL value into the static slot before
`tls_static_init_thread` runs for that thread, the static
template never gets copied and reads of the variable hit whatever value
was stored. `g_tls_alloc_used` has the bit set so `TlsAlloc` won't
hand it out, but the PE code can still call `TlsSetValue` on a known
index.

### `DuplicateHandle` of `-2` from main thread leaks on subsequent calls

Each `DuplicateHandle(GetCurrentThread())` from a thread that has no
`g_thread_obj_key`-tracked `ThreadObj` allocates a fresh `ThreadObj`
(`done=true`, `tid=0`). The new `ThreadObj` is *not* stored in
`g_thread_obj_key`, so the next call from the same thread allocates
another one. Each `DuplicateHandle` from the main thread is a fresh
allocation, never deduped.

---

## Summary of severity

| Severity | Item |
|---|---|
| Functional bug | 64-slot ceiling: PE binaries with >63 dynamic TLS slots fail. |
| Functional bug | No `DLL_PROCESS_DETACH` — mingw thread runtime never tears down. |
| Functional bug | `ExitThread` (and therefore `_endthreadex`) bypasses `DLL_THREAD_DETACH`. |
| Functional bug | Direct `pthread_create` threads skip `DLL_THREAD_ATTACH`/`DETACH` and static-TLS init. |
| Functional bug | `FlsAlloc` callback parameter is silently discarded. |
| Functional bug | `TlsFree` doesn't zero slots; `TlsGetValue` doesn't validate bitset → stale data across reuse. |
| Functional bug | `Characteristics` (alignment) ignored in static-TLS block allocation — SSE-aligned TLS templates get malloc-grade alignment. |
| Documentation | `LoadLibrary*` is a dummy by design — should carry a comment so its lack of TLS handling isn't misread as an oversight. |
| ABI bug | Inline `gs:[0x1480+idx*8]` slot reads/writes don't see `kernel32_Tls*` storage and vice versa. |
| ABI bug | `CreateThread` returns `INVALID_HANDLE_VALUE` (`-1`) on failure instead of `NULL`. |
| ABI bug | `GetCurrentThread()` pseudo-handle (`-2`) only honored by `DuplicateHandle`. |
| ABI bug | `TEB+0x08`/`+0x10` (StackBase/StackLimit) are zero; PEB has empty loader list and hard-coded ImageBase. |
| Race / UAF | `SetEvent`, `ResetEvent`, `ReleaseSemaphore`, `GetExitCodeThread` read handle state without `g_handles_mu` and skip refcount bump. |
| Race / UAF | `CloseHandle` on a held mutex calls `pthread_mutex_destroy` on a locked mutex (POSIX UB); Wait's own exit path guards this, `CloseHandle`'s does not. |
| Leak | Per-thread static TLS buffer is never freed at thread exit (pthread-key dtor frees the slots *array* but not its contents). |
| Leak | Every `DuplicateHandle(GetCurrentThread())` from an unmanaged thread allocates a new untracked `ThreadObj`. |
| Robustness | TLS callbacks run with no SEH/`try` isolation — a faulting callback aborts the process. |
| Stub | `CREATE_SUSPENDED`, `SuspendThread`, `ResumeThread`, `GetThreadContext`, `SetThreadContext`, `SetThreadPriority` are all no-ops. |
| Cosmetic | `GetCurrentThreadId` syscalls every call instead of reading `gs:[0x48]`. |
