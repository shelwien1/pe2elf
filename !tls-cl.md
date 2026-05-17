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
  if( !info ) return;
  g_tls_template_va  = (uintptr_t)info->template_va;
  g_tls_template_sz  = (size_t)info->template_sz;
  g_tls_zero_fill    = (size_t)info->zero_fill;
  g_tls_index_addr   = info->index_va  ? (uint32_t*)(uintptr_t)info->index_va  : nullptr;
  g_tls_callbacks_va = info->callbacks_va ? (uint64_t*)(uintptr_t)info->callbacks_va : nullptr;
  (void)info->align_chars; // TODO: posix_memalign when Characteristics alignment > 16
  if( g_tls_index_addr ) {
    // claim first free slot from g_tls_alloc_used, write to *AddressOfIndex
    pthread_mutex_lock(&g_tls_alloc_mu);
    for( DWORD i = 0; i < 64; i++ ) {
      if( !(g_tls_alloc_used & (1ULL<<i)) ) {
        g_tls_alloc_used |= (1ULL<<i);
        g_tls_static_idx = i;
        break;
      }
    }
    pthread_mutex_unlock(&g_tls_alloc_mu);
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
void* buf = calloc(1, sz); // calloc zeros; zero_fill requires no explicit memset
if( !buf ) return;
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
3. **Inline-TLS ABI mismatch.** MSVC's `TlsGetValue`/`TlsSetValue` are
   sometimes inlined as direct `gs:[0x1480 + idx*8]` reads/writes
   (slots 0–63 live inside the TEB on Windows, *not* indirected through
   `+0x58`). The shim's fake TEB is `0x2000` bytes so those addresses
   land inside the array and don't fault — but they read/write
   uninitialized zero bytes in `fake_teb`, not the `kernel32_TlsSetValue`
   storage. A binary that mixes inlined and out-of-line access patterns
   sees two different views of "the same" slot.

### FLS (Fiber Local Storage) — same family, separate storage

`kernel32_FlsAlloc`/`Free`/`Get`/`SetValue` (`shim.cpp`) are
backed by `static __thread void* g_fls[64]` and a global
`g_fls_used` bitset. Note this is a *different* per-thread array from
the TLS slots — FLS uses glibc `__thread` (FS-based), TLS uses the fake
TEB (GS-based).

`FlsAlloc(callback)` stores the callback in a global `g_fls_callbacks[]`
array. `FlsFree` invokes it for the calling thread's non-NULL value.
A pthread-key destructor (`fls_thread_exit`) iterates all slots at thread
exit and calls callbacks for non-NULL values of live slots. Full
cross-thread callback invocation at `FlsFree` time (Windows guarantee:
the callback fires for every thread with a non-NULL value) is not
implemented, as it would require iterating all live threads' `__thread`
arrays.

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

1. **`CloseHandle` on a held mutex destroys a locked mutex.** Scenario:
   thread A `WaitForSingleObject(mutex, INFINITE)` returns
   `WAIT_OBJECT_0` (mutex locked, refcount back to 1 after Wait's own
   decrement); thread B then calls `CloseHandle(mutex)`, dropping the
   refcount to 0; `CloseHandle`'s destroy path calls
   `pthread_mutex_destroy` on a still-locked mutex (POSIX UB).
   Thread A's later `ReleaseMutex` finds the slot now `H_FREE` and
   returns `FALSE` with `ERROR_INVALID_HANDLE`. The application is
   misusing the API, but the resulting UB is in shim code.
2. **`CREATE_SUSPENDED` is not implemented.** Passing the flag to
   `kernel32_CreateThread` now calls `abort()` with a diagnostic message
   rather than silently starting the thread immediately. Full
   suspend/resume support is a future work item.
3. **Mutexes are recursive** (`shim_kernel32_sync.hpp`). Windows
   mutex objects *are* recursive, so this is right.

---

## Bugs and gaps beyond what's already noted

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

### Empty loader list

The fake `PEB_LDR_DATA` lists are empty self-referencing rings, so a
thread walking the loader's module list to find DLLs sees no modules.
The PE binary itself isn't in the list.

### `fake_teb` may not be page-aligned

`__thread uint8_t fake_teb[0x2000]` gets default alignment (16 on x86_64
glibc). Windows TEBs are page-aligned and some inline code uses
`and rax, ~0xFFF` to round down to TEB base from any pointer into the
TEB. That pattern fails here.

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

---

## Summary of severity

| Severity | Item |
|---|---|
| Functional bug | 64-slot ceiling: PE binaries with >63 dynamic TLS slots fail. |
| Functional bug | Direct `pthread_create` threads skip `DLL_THREAD_ATTACH`/`DETACH` and static-TLS init. |
| ABI bug | Inline `gs:[0x1480+idx*8]` slot reads/writes don't see `kernel32_Tls*` storage and vice versa. |
| ABI bug | PEB has empty loader list — threads walking the module list see no modules. |
| Race / UAF | `CloseHandle` on a held mutex calls `pthread_mutex_destroy` on a locked mutex (POSIX UB); Wait's own exit path guards this, `CloseHandle`'s does not. |
| Robustness | TLS callbacks run with no SEH/`try` isolation — a faulting callback aborts the process. |
| Stub (DELAY) | `CREATE_SUSPENDED`: `kernel32_CreateThread` now aborts with a diagnostic when the flag is passed. Full suspend/resume support (`SuspendThread`/`ResumeThread`/`GetThreadContext`/`SetThreadContext`) is a future work item. |
| Robustness | `fake_teb` is `__thread`-aligned (16 bytes), not page-aligned; `and rax,~0xFFF` round-down patterns fail. |
| Correctness | `tls_static_init_thread` idempotency guard (`if slots[idx]`) can be defeated by a `TlsSetValue` on the static index before init runs. |
| Partial | FLS: per-slot callbacks fire at `FlsFree` and at thread exit for the calling thread; cross-thread callback invocation at `FlsFree` time (full Windows guarantee) is not implemented. |
