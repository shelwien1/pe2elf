# PPMonstr Incremental Decompilation Protocol

## 0. Goal

Produce a working, standalone C++ source for `PPMonstr.exe` by **incrementally
moving function bodies** out of the Hex-Rays output (`PPMonstr.cpp`) into a
companion shared library (`dummy.so`), one function at a time.

After each function is moved, the binary must still pass its functional test.
Once every in-scope function has been moved and the test still passes, the
collected `.inc` files form a complete, self-contained reimplementation of the
original program.

## 1. Scope (which functions to decompile)

Decompile **only** the program's own functions:

- `main`
- `Alloc_PPMblock`
- `PrintStats`
- Every `sub_14*` listed in `PPMonstr.cpp`

Everything else (C runtime, C++ runtime, Win32 API, `unknown_libname_*`,
intrinsics, etc.) is a **library function**: do not rewrite it. Reference it
from its known address (see §6.2) and leave the original code in place.

## 2. Toolchain and artifacts

| Artifact | Role |
|---|---|
| `PPMonstr.exe` | Original Windows PE binary, the source of truth. |
| `PPMonstr.cpp` | Hex-Rays decompilation, used as the donor for function bodies. |
| `PPMonstr.h`   | Hex-Rays type declarations included by `dummy.cpp`. |
| `PPMonstr.txt` | Symbol-to-address table (`<8-hex VA>  <name>`, one per line). |
| `pe2elf`       | Converter: `./pe2elf --inject=dummy.so PPMonstr.exe PPMonstr.elf` produces an ELF whose `DT_NEEDED` list contains `dummy.so`, so it is loaded at startup. |
| `dummy.cpp`    | The growing shared library; built into `dummy.so` by `make`. |
| `dummy_init()` | `__attribute__((constructor))` in `dummy.cpp`; runs once at process start, before `main`. This is where redirection patches are installed. |
| `sub_XXXXXXXX.inc` | One file per moved function (see §4). |

`dummy.so` is built at a **fixed preferred base address** below 4 GB
(`0xF0000000`), so it is always within ±2 GB of the PPMonstr image (which
loads at `0x140000000`). That range is what an `E9 rel32` near-jump can
reach, which is what makes the 5-byte patching in §5 possible.

Required linker flags in the `dummy.so` rule of `Makefile`:

```
-Wl,-Ttext-segment=0xF0000000 -Wl,-z,max-page-size=0x1000
```

This is a *preferred* base — glibc's `ld-linux` honors a non-zero
`p_vaddr` on `ET_DYN` objects as long as the range is free and ASLR does
not collide. The PPMonstr image occupies `0x140000000+`; nothing else in
this project maps the `0xF0000000` window, so the request is honored in
practice. `dummy_init()` must sanity-check the assumption at runtime by
comparing the address of one of its own functions against the expected
window and aborting with a clear message if the loader placed it elsewhere
(then the build flag, not the protocol, is wrong).

Build / run loop after any change to `dummy.cpp` or its includes:

```sh
make dummy.so
./pe2elf --inject=dummy.so PPMonstr.exe PPMonstr.elf
cp winapi_shim.so dummy.so /path/to/run/
./PPMonstr.elf <test inputs>     # verification: must succeed
```

## 3. Per-function workflow

For each function `sub_XXXXXXXX` (or `main` / `Alloc_PPMblock` / `PrintStats`),
do the following in order. Do not batch multiple functions per iteration — the
whole point of the protocol is that **every step ends with a green test**.

1. **Pick the next function.** Start with leaves (functions that only call
   library code) and work upward toward `main`. This keeps the dependency
   chain inside `dummy.so` acyclic and easy to debug.

2. **Locate the body** in `PPMonstr.cpp`. Grep for the definition
   (`^<rettype> <name>\b` or `^void <name>\b`), not the forward declaration.

3. **Look up the original VA** of the function:
   - Preferred source: `PPMonstr.txt`. Each line has the form
     `<8-hex VA>  <name>`, e.g. `014001A5C0  sub_14001A5C0`. The VA is the
     full 64-bit image VA (Hex-Rays prints leading zeros).
   - For names of the form `sub_<hex>` the hex digits after `sub_` are the
     VA in lowercase nibbles (`sub_14001A5C0` ⇒ `0x000000014001A5C0`). Use
     `PPMonstr.txt` as the authoritative source; the name is a fallback only.

4. **Create `<name>.inc`** in the repo root (e.g. `sub_14001A5C0.inc`). Copy
   the function body into it verbatim, then make two textual changes:
   - **Rename the function** by adding a double-underscore prefix
     (`sub_14001A5C0` ⇒ `__sub_14001A5C0`). This avoids ODR / linker
     collisions with the still-present original symbol inside `PPMonstr.elf`
     and any not-yet-moved sibling declarations.
   - **Resolve dependencies** as described in §6. Each external name the
     function references must appear in the `.inc` as a typed reference to
     its known address. Do **not** copy data definitions or unrelated
     function bodies into the `.inc`.

5. **Wire it into `dummy.cpp`.** Add, after the standard-library / `defs.h` /
   `PPMonstr.h` includes:

   ```cpp
   #include "sub_14001A5C0.inc"
   ```

   Order of `#include` lines must respect inter-`.inc` dependencies (if
   `__A` calls `__B`, include `B.inc` first).

6. **Install the redirect** inside `dummy_init()` (see §5). After this step,
   any call to the original VA in `PPMonstr.elf` jumps to the `__`-prefixed
   reimplementation in `dummy.so`.

7. **Rebuild and re-test** (§2). If the test fails, the bug is in this single
   function or in its `.inc` dependency block — bisect there, not in earlier
   `.inc` files. Do **not** proceed to the next function until the test is
   green.

8. **Commit** the new `.inc`, the `#include` line, and the `dummy_init()`
   patch entry as one atomic change.

## 4. `.inc` file conventions

- One function per file. Filename matches the **original** name without the
  `__` prefix: `sub_14001A5C0.inc`.
- The function inside is `__sub_14001A5C0` (double-underscore prefix).
- The `.inc` is a fragment, not a translation unit: no `#pragma once`, no
  include guards, no `#include` lines (those belong in `dummy.cpp`). It is
  textually inserted into `dummy.cpp` and compiled as part of it.
- **The function definition must carry `__attribute__((ms_abi))`.** PPMonstr
  is a Win64 binary and every call into a decompiled body — whether through
  the patched JMP or through a moved-callee direct call — uses the
  Microsoft x64 calling convention (RCX, RDX, R8, R9; 32-byte shadow space;
  callee-saved RSI/RDI). `dummy.so` itself is built as SysV. Without
  `ms_abi`, arguments are read from the wrong registers and the body silently
  consumes garbage. **A no-argument or write-only-to-globals function may
  appear to work without `ms_abi` — that is luck, not correctness.** Apply
  the attribute unconditionally to every `__sub_*` (and to any function
  pointer that will be installed in an IAT slot, see §7).
- Order inside the file:
  1. Typed references for data symbols this function reads/writes (§6.1).
  2. Typed references for functions this function calls — *only* for
     functions not yet moved into `dummy.so` (§6.2). Once a callee has its
     own `.inc`, drop its reference here and rely on the `__`-prefixed C++
     symbol instead (and update call sites accordingly).
  3. `PROBE_DECL(__sub_XXXXXXXX)` — registers a counter for this function
     in the global probe list. The `PROBE_DECL` / `PROBE_HIT` macros and
     the `Probe` registry live in `dummy.cpp` (§7).
  4. The function body, with signature changed only by adding the `__`
     prefix and the `ms_abi` attribute; argument and return types stay
     byte-identical to the `PPMonstr.cpp` declaration. The first statement
     in the body is `PROBE_HIT(__sub_XXXXXXXX);`.

Template for a freshly extracted function:

```cpp
// data and function typedef-refs go here, then:

PROBE_DECL(__sub_14001A5C0)
__attribute__((ms_abi)) void __sub_14001A5C0() {
  PROBE_HIT(__sub_14001A5C0);
  // ... original body, with external names already rewritten ...
}
```

## 5. Redirection: patching a JMP at the original VA

`dummy_init()` runs in the ELF's process **after** the loader has mapped the
original `PPMonstr.exe` code pages at their image VAs but **before** `main`.
For each moved function, `dummy_init()` overwrites the first **5 bytes** of
the original function with a near jump to the new implementation:

```
E9 dd dd dd dd             jmp rel32     ; rel32 = target - (orig + 5)
```

Five bytes is small enough to fit inside even short Hex-Rays stubs (e.g.
`void sub_14001A5C0() { dword_141134C28 = 0; }`, ~11 bytes of code) without
bleeding into the next function. A 14-byte absolute trampoline would not be
safe here.

This works only because `dummy.so` is pinned at `0xF0000000` (§2): the
displacement between any byte of PPMonstr (`0x140000000`–`~0x14120????`)
and any byte of `dummy.so` (`0xF0000000`–`0xF0??????`) is in the range
roughly `-0x51200000`…`-0x4FFFF000`, well within signed 32-bit. If the
preferred base is ever rejected by the loader, the rel32 may overflow and
the patch will silently jump to nonsense — therefore each `patch_jmp` must
compute the displacement, sign-check it against `INT32_MIN`/`INT32_MAX`,
and abort the process on overflow rather than truncate.

Steps for each redirect (encapsulated in `patch_jmp(orig, repl)`, called
from `dummy_init()`):

1. `void *orig = (void*)0x<VA>;` — the address from `PPMonstr.txt`.
2. `int64_t disp = (int64_t)repl - ((int64_t)orig + 5);`
   `assert(disp >= INT32_MIN && disp <= INT32_MAX);`
3. Make the page writable:
   `mprotect(page_align(orig), len, PROT_READ|PROT_WRITE|PROT_EXEC);`
   where `page_align` rounds down to the system page size and `len` covers
   the 5 bytes (handle the rare case where the patch straddles two pages
   by extending `len` accordingly).
4. Write `E9` followed by `disp` as a little-endian `int32_t`.
5. Restore protection to `PROT_READ|PROT_EXEC` (optional but advised).
6. Flush the instruction cache for the patched range
   (`__builtin___clear_cache(orig, (char*)orig + 5)`).

With the helper in place, each redirect is a one-liner:

```cpp
patch_jmp((void*)0x14001A5C0, (void*)&__sub_14001A5C0);
```

`dummy_init()` is therefore a list of `patch_jmp(...)` calls — one per
moved function — in any order.

**Edge case: function smaller than 5 bytes.** A function whose entire body
is shorter than the 5-byte JMP cannot be patched in place without
overwriting the next function's prologue. None of the in-scope PPMonstr
functions are known to be that small, but if one is encountered, do not
patch it — leave the original in place and call the reimplementation
explicitly from its (moved) callers instead. Document the exception in a
comment in `dummy_init()`.

## 6. Dependency cookbook

A moved function must compile and link without dragging the rest of
`PPMonstr.cpp` along. Replace every external name it touches with a **typed
reference at a fixed address**. Never copy global definitions across.

### 6.1 Data symbols

Given a data definition in `PPMonstr.cpp`:

```cpp
int arch_hdr[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // weak
```

and the matching line in `PPMonstr.txt`:

```
0140028E50  arch_hdr
```

emit in the `.inc`:

```cpp
typedef int t_arch_hdr[16];
static t_arch_hdr& arch_hdr = *(t_arch_hdr*)0x140028E50;
```

Rules:
- The `typedef` names the *array/object type*, not a pointer to it.
- The reference is `static` so two `.inc` files can each declare the same
  symbol without ODR conflict.
- The address is taken **verbatim** from `PPMonstr.txt`. Do not guess from
  the name (`dword_140028E14` is not always at `0x140028E14` — confirm).
- For scalar types use the same pattern:
  `static int& f_LOG = *(int*)0x140028E4C;`.

### 6.2 Function symbols (callees that stay in the original binary)

Given a call site in the donor body:

```cpp
v3 = unknown_libname_22(4, v20);
```

Find the prototype in `PPMonstr.cpp`:

```cpp
// __int64 unknown_libname_22(_QWORD, _QWORD); weak
```

and the address in `PPMonstr.txt`:

```
0140021696  unknown_libname_22
```

Emit in the `.inc`:

```cpp
typedef __attribute__((ms_abi)) __int64 t_unknown_libname_22(_QWORD, _QWORD);
static t_unknown_libname_22& unknown_libname_22 = *(t_unknown_libname_22*)0x140021696;
```

Rules:
- `typedef` the **function type**, then bind a reference (not a pointer) to
  the address. Calling `unknown_libname_22(...)` then resolves to a direct
  call through the typed reference.
- **The function-type `typedef` must carry `__attribute__((ms_abi))`** —
  the target is Win64-ABI code inside `PPMonstr.exe`, so the call site
  needs to marshal arguments into RCX/RDX/R8/R9 and reserve the 32-byte
  shadow space. Without it, the call corrupts the stack and/or passes
  arguments in the wrong registers. This applies even to "library"
  callees like `unknown_libname_*` because they too live in the PE image.
- Argument and return types must match the prototype in `PPMonstr.cpp` byte
  for byte (widths, `_QWORD` vs `void*`, etc.).
- Use the address of the **function entry**, not of any thunk or IAT slot.
  `PPMonstr.txt` already lists entries.

### 6.3 Function symbols (callees already moved to `dummy.so`)

If the callee has its own `.inc` and is therefore present as
`__sub_YYYYYYYY` in the same translation unit, **do not** add a typed
reference for it. Instead, rewrite the call site in the current `.inc` to
use `__sub_YYYYYYYY(...)` directly. This keeps the dependency graph among
`.inc` files explicit and removes one round-trip through the patched JMP.

Order `#include "<callee>.inc"` before `#include "<caller>.inc"` in
`dummy.cpp` so the C++ name is in scope.

## 7. `dummy.cpp` infrastructure (probe registry + ExitProcess hook)

`dummy.cpp` provides three pieces of infrastructure that every `.inc` relies
on. None of this needs to be reinvented per function; the snippets below
already live in the file.

### 7.1 Probe registry

Each decompiled function declares a `Probe` via `PROBE_DECL` and bumps its
counter on entry via `PROBE_HIT`. The registry is a singly-linked list built
at static-init time:

```cpp
struct Probe {
  Probe* next;
  const char* name;
  unsigned long long count;
  Probe(const char* n);
};
static Probe* g_probes = nullptr;
Probe::Probe(const char* n) : next(g_probes), name(n), count(0) { g_probes = this; }

#define PROBE_DECL(sym) static Probe sym##_probe(#sym);
#define PROBE_HIT(sym)  __sync_fetch_and_add(&sym##_probe.count, 1ULL)
```

`PROBE_HIT` is an atomic increment so it is safe under any threading the
program does. The counter pattern is mandatory for every `.inc` — it is the
only built-in way to confirm that the rel32 redirect is actually being
taken at runtime (a function that is never called cannot tell us if its
patch is wrong).

### 7.2 ExitProcess IAT hook

`dummy.cpp` cannot rely on `__attribute__((destructor))` or `atexit()` to
dump the counters. The shim's `kernel32_ExitProcess` calls `_exit()` (see
`shim.cpp:1136`), which bypasses both DT_FINI and the atexit chain. The
program's normal termination path goes
`main → MS CRT → ExitProcess → _exit`, so by the time glibc's exit
machinery would have run, the process is already gone.

Workaround: overwrite the **IAT slot** for `ExitProcess` so PPMonstr calls
our wrapper instead. The slot is at the address listed for `ExitProcess` in
`PPMonstr.txt` (currently `0x140022068`):

```cpp
static __attribute__((ms_abi)) void my_ExitProcess(unsigned int code) {
  fprintf(stderr, "[probe] ExitProcess(%u), call counts:\n", code);
  for (Probe* p = g_probes; p; p = p->next)
    fprintf(stderr, "[probe]   %-32s %llu\n", p->name, p->count);
  fflush(stderr);
  _exit((int)code);
}
```

Notes:
- The wrapper **must** be `ms_abi`. The call site uses Win64 (first arg in
  RCX, not RDI). A SysV-ABI wrapper here will read garbage and `_exit`
  with a nonsense code — the exact symptom that exposed why every
  decompiled body also needs `ms_abi` (see §4).
- Patching uses a separate helper `patch_iat_slot(slot, repl)` that just
  `mprotect`s the page, writes a pointer, and restores. No rel32 reach
  problem because we are writing data, not code.
- Output goes to **stderr** so the file-comparison part of the test
  (`cmp 1.pmm 1.ppm`) is unaffected.

### 7.3 `dummy_init()` checklist

Order of operations in the constructor:

1. Print `&dummy_init` and assert it falls inside `[0xF0000000,
   0x100000000)` (see §2). Abort if not — every `patch_jmp` would
   silently produce wrong displacements.
2. One `patch_jmp((void*)0x<VA>, (void*)&__sub_XXXXXXXX);` per moved
   function.
3. `patch_iat_slot((void*)<ExitProcess slot VA>, (void*)&my_ExitProcess);`
   exactly once. (Other IAT hooks may be added later in the same way.)

## 8. Verification

The "test" referenced throughout this document is a **fixed, reproducible
end-to-end run** of `PPMonstr.elf`: compress a known input, then compare
byte-for-byte against the reference output produced by the un-injected
baseline.

Baseline (run once, captures `1.ppm` as the reference):

```sh
make && ./pe2elf PPMonstr.exe PPMonstr.elf \
  && rm -v 1.ppm \
  && ./PPMonstr.elf e -o128 -m1 -r1 -f1.ppm rar550.exe
```

Validation (run after every `.inc` change):

```sh
make && ./pe2elf --inject=dummy.so PPMonstr.exe PPMonstr.elf \
  && rm -v 1.pmm \
  && ./PPMonstr.elf e -o128 -m1 -r1 -f1.pmm rar550.exe \
  && cmp 1.pmm 1.ppm
```

The validation command is the sole gate for promoting an `.inc` from
"drafted" to "accepted". Note the deliberate filename split: the baseline
writes `1.ppm`, the injected build writes `1.pmm`, and `cmp` enforces
equality. Re-run the baseline only when `PPMonstr.exe`, `rar550.exe`, the
encoder flags, or `pe2elf` itself change.

After a green run, the stderr line `[probe] ExitProcess(0), call counts:`
plus the per-probe counts confirms which decompiled bodies were actually
exercised by this corpus. A counter of `0` means the test does not cover
that function — extend the corpus (or accept the gap explicitly) before
treating that `.inc` as verified.

If the test ever fails:
1. The breakage is in the most recently added `.inc` or its redirect.
2. Revert that single commit, re-run the test to confirm green baseline,
   then re-attempt the function with the discrepancy isolated.

## 9. Completion criterion

The decompilation is complete when:

- Every function listed in §1 has its own `.inc` file.
- `dummy.cpp` `#include`s all of them.
- `dummy_init()` patches a redirect for each one.
- The test passes.
- Every probe in the ExitProcess dump reports a non-zero count, **or** the
  zero-count function is explicitly listed as not exercised by the chosen
  corpus (and a corpus extension is filed as future work).

At that point the bodies in `PPMonstr.cpp` are dead code (every entry has
been overwritten by a JMP at runtime), and the `.inc` set is a standalone
reimplementation that can be compiled into a native binary without the
`PPMonstr.exe` donor.
