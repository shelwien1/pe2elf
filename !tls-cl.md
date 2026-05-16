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

`shim.cpp:1044` (`__attribute__((constructor)) shim_init`) drives all TLS
setup in this order:

1. `init_fake_peb()` — builds a global 4 KiB fake PEB with a self-referential
   empty `PEB_LDR_DATA`, minimal `RTL_USER_PROCESS_PARAMETERS`, and a
   hard-coded `ImageBaseAddress = 0x400000` at `PEB+0x10`.
2. `discover_image_base()` — captures the real ELF base.
3. `handles_init()` — fills the 4096-entry `g_handles[]` slot table; slots
   0/1/2 are pre-bound to stdin/stdout/stderr.
4. `shim_init_teb()` — initializes the main thread's fake TEB and points
   `GS` at it (see next section).
5. `discover_tls_callbacks()` — locates the PE TLS directory by reading
   `/proc/self/exe` via raw `SYS_pread64` and scanning the `.tls` ELF
   section.
6. Pre-allocates the *static* TLS slot index, writes it to
   `*AddressOfIndex`, and calls `tls_static_init_thread()` so the main
   thread sees its initialized static TLS block.
7. `run_tls_callbacks(1)` — invokes each PE TLS callback with
   `DLL_PROCESS_ATTACH`.

### `discover_tls_callbacks` (`shim.cpp:916–1007`)

The function:

- Reads the ELF header from `/proc/self/exe`, finds the section table,
  locates a section named `.tls` (`shim.cpp:964`).
- Scans the in-memory `.tls` section in 8-byte steps, treating every
  40-byte window as a candidate `IMAGE_TLS_DIRECTORY64` and accepting the
  first one whose fields look plausible:

  ```cpp
  if( start >= tls_va && start <= tls_va + tls_sz &&
      end >= start && cbs != 0 ) {
    uint64_t* arr = (uint64_t*)cbs;
    if( *arr != 0 ) { ... record and return ... }
  }
  ```

- Stores `g_tls_callbacks_va`, `g_tls_template_va`, `g_tls_template_sz`,
  and `g_tls_index_addr`.

### Static-TLS index pre-allocation (`shim.cpp:1055–1069`)

Before any application code runs, the constructor walks the 64-bit
`g_tls_alloc_used` bitset, claims the first free slot, stores its number
in `g_tls_static_idx`, writes that DWORD to `*AddressOfIndex`, and calls
`tls_static_init_thread()` to populate the main thread's static block:

```cpp
size_t sz = g_tls_template_sz ? g_tls_template_sz : 64;
void* buf = calloc(1, sz);
if( g_tls_template_va && g_tls_template_sz )
    memcpy(buf, (void*)g_tls_template_va, g_tls_template_sz);
slots[g_tls_static_idx] = buf;
```

This matches the indirected MSVC access pattern
`gs:[0x58] → array → [idx]*8 → block`.

Note: `slots` is itself per-thread (it's `gs:[0x58]` of *this* thread),
so different threads write to different memory; this is not a shared
location and there is no inter-thread race on `slots[g_tls_static_idx]`.

---

## TEB emulation

```cpp
static __thread uint8_t fake_teb[0x2000];     // shim.cpp:93 — 8 KiB per thread
static uint8_t          fake_peb[0x1000];     // shim.cpp:146 — process-global
```

`shim_init_teb()` (`shim.cpp:219–249`) populates per-thread fields:

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
destructor is `free` (`shim.cpp:96–98`), so the *array* is reclaimed
when the thread exits — *except* when the array gets overwritten
mid-attach (see the double-attach bug below). The pointers *inside*
the array (static-TLS buffer, any `TlsSetValue` values) are not touched
by the destructor.

---

## `kernel32_CreateThread` and the two trampolines

There are two completely separate thread trampolines in this shim, and
this is where most of the trouble lives.

### Trampoline A: `thread_trampoline` (CreateThread's own)

In `shim_kernel32_sync.hpp:297–309`:

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

`kernel32_CreateThread` (`shim_kernel32_sync.hpp:311–342`):

1. `calloc`s a `ThreadObj` (refcount=1, mutex+cond initialized).
2. Allocates a `ThreadStart` carrying `{fn, param, obj}`.
3. Allocates an H_THREAD handle pointing at `ThreadObj`.
4. Calls `pthread_create(&obj->tid, …, thread_trampoline, ts)`.

The pthread TID is stored on the `ThreadObj` so that
`sync_obj_destroy` can join or detach it.

### Trampoline B: the `pthread_create` override (`shim.cpp:280–293`)

The shim *also* overrides `pthread_create` itself with default visibility
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

### The double-attach problem

Because `kernel32_CreateThread` calls `pthread_create`, and the shim's
own `pthread_create` is the visible symbol, every `CreateThread` thread
goes through *both* trampolines:

```
kernel32_CreateThread
  → pthread_create (our override)
      → real pthread_create with shim_thread_trampoline
          [new thread]
          → shim_thread_trampoline
              → shim_init_teb()                # first init
              → thread_trampoline               # the original fn
                  → shim_init_teb()             # second init
                  → run_tls_callbacks(2)
                  → tls_static_init_thread()
                  → fn(...)
```

`shim_init_teb` is called twice. Each call does:

```cpp
memset(fake_teb, 0, sizeof(fake_teb));
…
void** tls_slots = (void**)calloc(64, sizeof(void*));
*(void**)(fake_teb+0x58) = tls_slots;
pthread_setspecific(g_tls_slots_key, tls_slots);
```

Consequences:

- **Memory leak per CreateThread thread.** The first `calloc(64, 8) = 512
  bytes` is dropped on the floor; `pthread_setspecific` overwrites the
  key value without running the previous value's destructor (POSIX
  doesn't run the destructor on overwrite). The first slot block becomes
  unreachable until process exit.
- **GS is re-bound to the same `fake_teb` address** — harmless but
  wasted syscall.
- **Any state written between the two `shim_init_teb` calls would be
  silently zeroed.** Currently nothing is written there, but anything
  added later (e.g. an attempt to record thread arguments in the TEB)
  would be destroyed by the second `memset`.

This affects `_beginthreadex` too (`shim_msvcrt.hpp:535`), which just
wraps `kernel32_CreateThread`.

### Threads that bypass `kernel32_CreateThread`

If the PE binary calls `pthread_create` directly (e.g. statically linked
pthreads-win32 code paths, or a port that uses POSIX threads), only
Trampoline B runs. Those threads get:

- a fake TEB ✓
- TLS slot array at `gs:[0x58]` ✓
- **no** `DLL_THREAD_ATTACH` callback ✗
- **no** static TLS block ✗
- **no** `DLL_THREAD_DETACH` callback ✗ (no post-fn hook in Trampoline B)

This is also the path taken by anything that ends up routed to
`pthread_create` rather than `CreateThread` — most relevantly, MSVC
STL `std::thread` when compiled targeting a POSIX threading model, or
any DLL whose own thread-creation glue calls `pthread_create` directly.

The `tls_example.txt` mingw runtime is the kind of code that breaks
here: its `_dyn_tls_dtor` / `_mingw_TLScallback` chain installs a
per-thread key-destructor table on attach and runs it on detach. A
thread that skips both attach and detach leaves its key state
uninitialized and any registered key destructors un-run.

### Threads with no trampoline at all

Threads created via raw `clone(2)`, or threads spawned by a library
loaded by `dlopen` that does not route through `pthread_create`, will
have **no fake TEB** at all. Subsequent inlined `gs:[…]` accesses from
PE code on that thread read whatever the underlying glibc left in
`GS` — almost certainly not a Windows TEB, so reads of LastError, TLS
slots, etc. return garbage or fault. In practice rare; possible.

---

## `kernel32_Tls*` functions

All four live in `shim.cpp:2031–2074`. They are backed by the same
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

`tls_get_slots()` (`shim.cpp:665`) is a single `mov %gs:0x58, %0`.

### Issues

1. **Hard 64-slot ceiling.** Windows guarantees a minimum of 64
   (`TLS_MINIMUM_AVAILABLE`) but actually provides 1088 via the
   expansion array at `TEB+0x1780`. PE binaries that consume more than
   64 slots — common when multiple statically-linked DLLs each grab a
   handful — will see `TlsAlloc` returning `0xFFFFFFFF` and likely
   crash.
2. **The static-TLS slot competes with `TlsAlloc`.** `shim_init`
   reserves `g_tls_static_idx` from the same bitset, so only 63
   dynamic slots remain after startup. Good for safety; surprising for
   capacity.
3. **`TlsFree` does not zero the slot in any thread.** Windows
   guarantees the slot is reset to 0 in all threads when freed. The
   shim only clears the bitset. If the slot is later reissued by
   another `TlsAlloc`, the new owner can observe stale per-thread
   values (anything any thread last `TlsSetValue`'d into that index).
4. **`TlsGetValue` does not validate against the bitset.** On Windows
   `TlsGetValue` on a freed index returns 0 with no error; the shim
   returns whatever stale pointer was last written. In practice this
   plus #3 means a freed-then-realloced slot leaks data across
   subscribers.
5. **No memory barrier or `std::atomic`** on the bitset; only the
   mutex serializes. That is fine in practice but means `TlsAlloc` /
   `TlsFree` racing with `TlsGetValue` / `TlsSetValue` on a different
   slot rely on the mutex's release-acquire semantics, which is OK.
6. **Inline-TLS ABI mismatch.** MSVC's `TlsGetValue`/`TlsSetValue` are
   sometimes inlined as direct `gs:[0x1480 + idx*8]` reads/writes
   (slots 0–63 live inside the TEB on Windows, *not* indirected through
   `+0x58`). The shim's fake TEB is `0x2000` bytes so those addresses
   land inside the array and don't fault — but they read/write
   uninitialized zero bytes in `fake_teb`, not the `kernel32_TlsSetValue`
   storage. A binary that mixes inlined and out-of-line access patterns
   sees two different views of "the same" slot. The only reliable path
   today is calling the kernel32 exports.
7. **`g_tls_static_idx == 0xFFFFFFFF` is still written to
   `*AddressOfIndex`** if the startup scan finds no free slot
   (`shim.cpp:1065`). That degenerate case turns every static-TLS
   access into `gs:[0x58][0xFFFFFFFF]` and is fatal. The bitset is
   empty at startup so the for-loop will always find slot 0, but the
   safety check is missing.

### FLS (Fiber Local Storage) — same family, separate storage

`kernel32_FlsAlloc`/`Free`/`Get`/`SetValue` (`shim.cpp:2705–2751`) are
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

### `WaitForSingleObject` (`shim_kernel32_sync.hpp:82–170`)

For thread waits:

```cpp
case H_THREAD: {
  ThreadObj* t = (ThreadObj*)ptr;
  pthread_mutex_lock(&t->mu);
  int r = 0;
  while( !t->done && r == 0 ) {
    r = inf ? pthread_cond_wait(&t->cv, &t->mu)
            : pthread_cond_timedwait(&t->cv, &t->mu, &ts);
  }
  if( t->done ) ret = WAIT_OBJECT_0;
  …
}
```

The lookup/refcount bump is atomic under `g_handles_mu` (line 84–97).
The decrement+destroy at the bottom (line 160–167) is also under
`g_handles_mu`. The `H_MUTEX` exit path correctly unlocks the mutex
before destroying when refcount reaches zero, avoiding POSIX UB on
`pthread_mutex_destroy` of a locked mutex — but only for the case
where Wait's own decrement was the one that hit zero (see issue 2
below).

### `kernel32_CloseHandle` (`shim.cpp:1380–1411`)

For sync handles it reads `kind` and `ptr` under `g_handles_mu`,
marks the slot `H_FREE`, then decrements the refcount under the same
mutex. Only when the refcount hits zero does it call
`sync_obj_destroy(kind, ptr)`. This is the core invariant that lets
`WaitForSingleObject` finish safely even if `CloseHandle` runs while a
wait is in flight.

### Thread-handle destruction (`shim_kernel32_sync.hpp:50–62`)

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
`GetCurrentThread()` creates for unmanaged threads (`shim.cpp:3214`);
join/detach is skipped there.

### Issues

1. **TOCTOU in the non-wait sync APIs.** `ReleaseMutex` (line 191),
   `SetEvent` (line 227), `ResetEvent` (line 236), `ReleaseSemaphore`
   (line 262), `GetExitCodeThread` (`shim.cpp:3350`), and
   `signal_handle` (line 366) all read `g_handles[idx].kind` and
   `g_handles[idx].ptr` **without holding `g_handles_mu`**. A
   concurrent `CloseHandle` from another thread can drop the refcount
   to zero between the load and the dereference, freeing the object
   through `sync_obj_destroy` and turning the dereference into a
   use-after-free. None of these paths bump the refcount first.
2. **`CloseHandle` on a held mutex destroys a locked mutex.** Scenario:
   thread A `WaitForSingleObject(mutex, INFINITE)` returns
   `WAIT_OBJECT_0` (mutex locked, refcount back to 1 after Wait's own
   decrement); thread B then calls `CloseHandle(mutex)`, dropping the
   refcount to 0; `CloseHandle`'s destroy path calls
   `pthread_mutex_destroy` on a still-locked mutex (POSIX UB).
   Thread A's later `ReleaseMutex` finds the slot now `H_FREE` and
   returns `FALSE` with `ERROR_INVALID_HANDLE`. Wait's own exit path
   has an explicit `pthread_mutex_unlock` before destroy
   (`shim_kernel32_sync.hpp:164–165`); `CloseHandle`'s destroy path
   does not. The application is misusing the API, but the resulting
   UB is in shim code, not application code.
3. **`GetCurrentThread()` pseudo-handle (`-2`).** `DuplicateHandle`
   special-cases it (`shim.cpp:3210`). Most other thread APIs do not.
   `GetExitCodeThread(GetCurrentThread(), …)` returns `FALSE` with
   `ERROR_INVALID_HANDLE`, and `WaitForSingleObject(GetCurrentThread(),
   0)` returns `WAIT_FAILED`. Real Windows accepts the pseudo-handle in
   both.
4. **`CreateThread` returns `INVALID_HANDLE_VALUE` (`-1`) on failure**
   (`shim_kernel32_sync.hpp:315, 322, 329, 338`). Real Windows
   returns `NULL`. Code that checks `if (h == NULL)` will think a
   failed `CreateThread` succeeded.
5. **`CreateThread`'s `flags` (incl. `CREATE_SUSPENDED`) and `stack`
   size are ignored.** Threads always start immediately at default
   stack. The matching `ResumeThread` (`shim.cpp:3155`) is a stub
   returning 1, so binaries that suspend-and-resume during init silently
   skip whatever was supposed to happen before resume.
6. **Mutexes are recursive** (`shim_kernel32_sync.hpp:182`). Windows
   mutex objects *are* recursive, so this is right, but the
   `ReleaseMutex`-without-lock TOCTOU above is more dangerous on a
   recursive mutex because a buggy double-release on a freed object is
   even harder to diagnose.

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
`ExitThread`. For mingw-runtime binaries this means
`_mingwthr_run_key_dtors_part_0` never runs for those threads — TLS-key
destructors don't fire, and any resources keyed off them leak.

### Per-thread static TLS buffer leaks on thread exit

`tls_static_init_thread` allocates a buffer with `calloc(1, sz)` and
stores its pointer in `slots[g_tls_static_idx]`. At thread exit, the
pthread-key destructor (`shim.cpp:98`) frees `slots` itself but does
not iterate it. The static-TLS buffer (and any pointer ever written
through `TlsSetValue` to a value the *shim itself* allocated) leaks at
thread exit. For long-lived processes that create and join many
threads this is unbounded.

A correct teardown would walk the slots array in the destructor,
freeing `slots[g_tls_static_idx]` and any other entries the shim
itself allocated. Untouched `TlsSetValue` values that came from the
application stay the application's responsibility (Windows doesn't
free them either).

### Scanning `/proc/self/exe` is the wrong layer — pe2elf should pass the TLS directory explicitly

The whole `discover_tls_callbacks` design is upside-down. The pe2elf
converter has full, authoritative knowledge of the
`IMAGE_TLS_DIRECTORY64` at conversion time — every field, exact byte
offsets, the size of each callback array, the alignment requirement,
SizeOfZeroFill, all of it. The shim then throws that knowledge away
and tries to *rediscover* it at runtime by:

- opening `/proc/self/exe` and re-parsing ELF section headers via raw
  `SYS_pread64`,
- looking for an ELF section literally named `.tls` (which depends on
  the converter preserving that name through the ELF emit path),
- and then **heuristically scanning** the section in 8-byte steps for
  a 40-byte window whose fields look plausible:

  ```cpp
  for( uint64_t off = 0; off + 40 <= tls_sz; off += 8 ) {
    ...
    if( start >= tls_va && start <= tls_va + tls_sz &&
        end >= start && cbs != 0 ) {
      uint64_t* arr = (uint64_t*)cbs;
      if( *arr != 0 ) { …record and return… }
    }
  }
  ```

That guess-the-struct loop is the root cause of the three issues
below (no-callbacks → abort; SizeOfZeroFill ignored; Characteristics
ignored): the scan only inspects the first 24 bytes of each candidate
because going further would multiply the false-positive surface, and
it requires a non-empty callback array because that's the only field
distinctive enough to anchor the match.

The right shape is for pe2elf to emit a small startup thunk that calls
into the shim with the directory contents passed by value (or by
pointer to a known-layout struct), e.g.

```cpp
// In shim.cpp — replaces discover_tls_callbacks entirely.
extern "C" void shim_register_tls(
    const void* template_va,   // StartAddressOfRawData
    size_t      template_sz,   // End - Start
    size_t      zero_fill,     // SizeOfZeroFill
    uint32_t    align_chars,   // Characteristics (IMAGE_SCN_ALIGN_*)
    uint32_t*   index_va,      // AddressOfIndex
    const void* const* callbacks); // NULL-terminated, may be NULL or empty
```

The converter emits exactly one call to `shim_register_tls(...)` at
the top of the generated `_start` thunk (or, equivalently, inside a
`.init_array` entry that runs *before* the shim constructor — order
controllable via `init_priority`). The shim constructor then has
nothing to discover: it reads the globals the thunk wrote and proceeds
to per-thread init and `run_tls_callbacks(1)`.

Benefits, beyond just being honest about who knows what:

- No `/proc/self/exe` open, no ELF parsing, no `SYS_pread64`, no
  reliance on the `.tls` section name. Works under chroot, under
  `LD_PRELOAD`-wrapped sandboxes, on stripped binaries, and on PIE
  builds where the section's runtime address differs from `sh_addr`.
- The "no callbacks" case is handled trivially: the thunk passes
  `callbacks = nullptr` or a pointer to a single null entry, and the
  shim records it correctly instead of bailing out (issue below).
- `SizeOfZeroFill` and alignment are both passed in. The shim
  allocates `posix_memalign(align, template_sz + zero_fill)` and the
  static-TLS buffer is sized and aligned correctly first-try.
- The scan's false-positive risk goes away — there's no scan.
- Multi-binary scenarios (if ever needed) become a matter of calling
  `shim_register_tls` more than once, instead of having to teach the
  scanner about additional modules.

The three subsections that follow are all symptoms of the
scan-based design and would simply not exist with explicit
registration.

### `discover_tls_callbacks` aborts when there are no callbacks

```cpp
uint64_t* arr = (uint64_t*)cbs;
if( *arr != 0 ) { …record… return; }
```

If the binary has a TLS directory with static data but `AddressOfCallBacks`
pointing at a single null entry (no callbacks at all — perfectly legal),
the scan keeps stepping forward looking for a "better" match. Since the
test is also "is this 40-byte window a plausible directory", the loop
will most likely fall off the end and the shim ends up with no static-TLS
template, no `g_tls_index_addr`, and PE code that does
`__declspec(thread) int x` will read whatever happens to be at offset
0 inside an uninitialized slot.

### `SizeOfZeroFill` is ignored

The IMAGE_TLS_DIRECTORY layout has at offset +32 a `DWORD SizeOfZeroFill`
specifying *additional* uninitialized bytes that should follow the
copied template. The scan (`shim.cpp:982–985`) only reads fields up to
offset +24 and `tls_static_init_thread` only allocates
`end - start` bytes:

```cpp
size_t sz = g_tls_template_sz ? g_tls_template_sz : 64;
```

For binaries that declare `__declspec(thread)` BSS data, those zero-fill
bytes live *past* the buffer and any write to them corrupts the
following heap chunk.

### `Characteristics` (alignment) is ignored

The `calloc` for the static TLS block has malloc-grade alignment (16 on
glibc x86_64). PE TLS templates with alignment requirements > 16
(SSE arrays, etc.) get under-aligned blocks; loads can fault or run
slowly depending on the instruction.

### `LoadLibrary` is a dummy — worth a comment saying so

`discover_tls_callbacks` opens `/proc/self/exe` and only handles the
main executable's TLS directory. `kernel32_LoadLibraryExW`
(`shim.cpp:1839`) just does `dlopen(..., RTLD_LAZY|RTLD_GLOBAL)` and
returns a handle slot:

```cpp
void* h = dlopen(posix, dlflags);
if( h ) { HANDLE hret = handle_alloc_module(h); … return hret; }
```

This is by design — the converter resolves all PE imports at conversion
time, so `LoadLibrary` exists only to satisfy explicit runtime lookups
and the result is mostly used as a token for subsequent
`GetProcAddress` calls into the shim's own exports. Loading a real PE
DLL on Linux is out of scope.

The single-module assumption is baked into the global TLS state
(`g_tls_callbacks_va`, `g_tls_index_addr`, `g_tls_static_idx`) — there
is nowhere to record additional modules' TLS state. Implementing full
TLS for `LoadLibrary`-loaded modules would mean (a) reading a PE
file from disk, (b) scanning *its* TLS directory, (c) allocating a new
per-module TLS index, and (d) running its callbacks on every existing
thread — none of which is worth doing when the converter has already
flattened the import graph.

What *is* worth doing is annotating the `LoadLibrary*` and
`FreeLibrary` functions with a leading comment to that effect, so
future readers don't reach for `discover_tls_callbacks` thinking the
TLS machinery should generalize. Something like:

```cpp
// LoadLibraryExW is a dummy: PE DLLs cannot be loaded at runtime on
// Linux. The converter resolves all PE imports statically; this
// function exists so explicit runtime LoadLibrary("kernel32.dll")
// style calls succeed and return a handle that GetProcAddress can
// dispatch into the shim's own exports. We do NOT scan the loaded
// module for a PE TLS directory, run TLS callbacks, or allocate
// per-module TLS slots — none of that is reachable in practice.
```

The same note belongs on `kernel32_LoadLibraryA` (`shim.cpp:2588`),
`kernel32_GetModuleHandle*`, and `kernel32_FreeLibrary`.

### No `DLL_PROCESS_DETACH`

`run_tls_callbacks(1)` is invoked from the constructor; there is no
matching `__attribute__((destructor))` or `atexit(run_tls_callbacks_0)`.
The `tls_example.txt` mingw runtime relies on
`DLL_PROCESS_DETACH` to:
- `_mingwthr_run_key_dtors_part_0()` (run pending TLS dtors)
- free the per-process linked list at `qword_4373E0`
- `DeleteCriticalSection(&CriticalSection)`

None of that runs at process exit. The kernel reclaims the address
space, so this is mostly cosmetic for the main process, but a parent
that monitors child cleanup behaviour will see the difference.

### No fault isolation around TLS callbacks

`run_tls_callbacks` (`shim.cpp:1011–1021`) calls each callback directly
with no SEH wrapping, no `sigsetjmp`, no `try/catch`. The Windows
loader installs an exception filter around TLS-callback invocation so
a faulting callback doesn't kill process init. Here, a faulting
callback escapes through `run_tls_callbacks` into the constructor,
which has no handler either, and the process dies via the installed
`crash_handler`. (The TLS callback ABI is `ms_abi`, so a C++ exception
thrown out of one would also be undefined behaviour at the ABI
boundary.)

### `fake_teb` is 0x2000 bytes; real TEB is bigger

A real Win10 x64 TEB is around 0x1840 + the TEB-extension area, but
common offsets accessed by ucrtbase and mingw runtimes include:

- `TEB+0x1480` — `TlsSlots[64]` (inline TLS, see #6 in the Tls section)
- `TEB+0x1780` — `TlsExpansionSlots`
- `TEB+0x17C8` — `GdiBatchCount` etc.

`0x1780` and `0x17C8` fit inside `0x2000`, so accesses don't fault, but
all of those fields are zero. Inline reads of expansion-slot TLS,
GDI/Win32k state, or the activation context stack get NULL. The first
two are the relevant ones for a binary doing TLS work.

### Stack-bounds fields are zero

`TEB+0x08 StackBase` and `TEB+0x10 StackLimit` are both 0. Any code that
checks the stack range (CRT stack-overflow probes, SEH unwind hints,
fiber bookkeeping) will see degenerate bounds.

### Hard-coded `ImageBaseAddress = 0x400000`

`init_fake_peb` always writes `0x400000` into `PEB+0x10`. If the ELF was
linked at a different base, code that walks `GetModuleHandle(NULL) ==
PEB.ImageBaseAddress` against the actual loaded base will mis-identify
its own module. The `discover_image_base()` call exists for exactly
this but its result isn't fed back into the PEB.

### Empty loader list

`shim_init_teb` writes `fake_peb` into every thread's `TEB+0x60`
(one PEB per process — correct). The fake `PEB_LDR_DATA` lists are
empty self-referencing rings, so a thread walking the loader's module
list to find DLLs (which mingw runtime startup occasionally does) sees
no modules. The PE binary itself isn't in the list.

### The pthread_create override is a one-way trapdoor

`pthread_create` resolves `dlsym(RTLD_NEXT, "pthread_create")` on first
call and caches it in a non-atomic static (`shim.cpp:282–284`). Two
threads racing the first call may both run `dlsym`. `dlsym` itself is
thread-safe and idempotent here, and the write is a single pointer
store, so the race is benign in practice — but it's a race.

### `fake_teb` may not be page-aligned

`__thread uint8_t fake_teb[0x2000]` gets default alignment (16 on x86_64
glibc). Windows TEBs are page-aligned and some inline code uses
`and rax, ~0xFFF` to round down to TEB base from any pointer into the
TEB. That pattern fails here.

### `kernel32_GetCurrentThreadId` calls `gettid()` every time

`shim.cpp:1099` does `(DWORD)syscall(SYS_gettid)` per call. The fake TEB
already caches the TID at `+0x48`. A hot loop calling
`GetCurrentThreadId()` will syscall on every iteration when it could
just read `gs:[0x48]`.

### `tls_static_init_thread` idempotency hinges on the slot staying NULL

```cpp
if( slots[g_tls_static_idx] ) return;
```

If anything writes a non-NULL value into the static slot before
`tls_static_init_thread` runs for that thread — e.g. a stray
`TlsSetValue(g_tls_static_idx, …)` from PE code that found the index in
`*AddressOfIndex` and decided to "TlsSetValue" through it — the static
template never gets copied and reads of the variable hit whatever value
was stored. `g_tls_alloc_used` has the bit set so `TlsAlloc` won't
hand it out, but the PE code can still call `TlsSetValue` on a known
index. Defensive programming would zero-check by allocating the buffer
first and then CAS-installing.

### `DuplicateHandle` of `-2` from main thread leaks on subsequent calls

`shim.cpp:3210–3242`: each `DuplicateHandle(GetCurrentThread())` from a
thread that has no `g_thread_obj_key`-tracked `ThreadObj` allocates a
fresh `ThreadObj` (`done=true`, `tid=0`). The new `ThreadObj` is
*not* stored in `g_thread_obj_key`, so the next call from the same
thread allocates another one. Each `DuplicateHandle` from the main
thread is a fresh allocation, never deduped.

---

## Summary of severity

| Severity | Item |
|---|---|
| Architecture | TLS directory is rediscovered at runtime by scanning `/proc/self/exe` for the `.tls` section and heuristic-matching a 40-byte window — pe2elf already knows the directory at conversion time and should emit a startup thunk that calls `shim_register_tls(...)` with the exact fields. Fixes the three discovery-related symptoms below. |
| Functional bug | 64-slot ceiling: PE binaries with >63 dynamic TLS slots fail. |
| Functional bug | `SizeOfZeroFill` ignored — static-TLS BSS overflows the allocated buffer. |
| Functional bug | No `DLL_PROCESS_DETACH` — mingw thread runtime never tears down. |
| Functional bug | `ExitThread` (and therefore `_endthreadex`) bypasses `DLL_THREAD_DETACH`. |
| Functional bug | Direct `pthread_create` threads skip `DLL_THREAD_ATTACH`/`DETACH` and static-TLS init. |
| Functional bug | TLS-discovery aborts when callback array is empty (binary has only static TLS). |
| Documentation | `LoadLibrary*` is a dummy by design (PE DLLs aren't loaded at runtime on Linux) — should carry a comment saying so, so its lack of TLS handling isn't misread as an oversight. |
| Functional bug | `FlsAlloc` callback parameter is silently discarded. |
| Functional bug | `TlsFree` doesn't zero slots; `TlsGetValue` doesn't validate bitset → stale data across reuse. |
| ABI bug | Inline `gs:[0x1480+idx*8]` slot reads/writes don't see `kernel32_Tls*` storage and vice versa. |
| ABI bug | `CreateThread` returns `INVALID_HANDLE_VALUE` (`-1`) on failure instead of `NULL`. |
| ABI bug | `GetCurrentThread()` pseudo-handle (`-2`) only honored by `DuplicateHandle`. |
| ABI bug | `TEB+0x08`/`+0x10` (StackBase/StackLimit) are zero; PEB has empty loader list and hard-coded ImageBase. |
| Race / UAF | `ReleaseMutex`, `SetEvent`, `ResetEvent`, `ReleaseSemaphore`, `GetExitCodeThread` read handle state without `g_handles_mu` and skip refcount bump. |
| Race / UAF | `CloseHandle` on a held mutex calls `pthread_mutex_destroy` on a locked mutex (POSIX UB); Wait's own exit path guards this, `CloseHandle`'s does not. |
| Leak | Every `CreateThread` leaks a 512-byte slot block via double `shim_init_teb`. |
| Leak | Per-thread static TLS buffer is never freed at thread exit (pthread-key dtor frees the slots *array* but not its contents). |
| Leak | Every `DuplicateHandle(GetCurrentThread())` from an unmanaged thread allocates a new untracked `ThreadObj`. |
| Robustness | TLS callbacks run with no SEH/`try` isolation — a faulting callback aborts process init. |
| Stub | `CREATE_SUSPENDED`, `SuspendThread`, `ResumeThread`, `GetThreadContext`, `SetThreadContext`, `SetThreadPriority` are all no-ops. |
| Cosmetic | `GetCurrentThreadId` syscalls every call instead of reading `gs:[0x48]`. |
