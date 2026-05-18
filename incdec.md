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
- Order inside the file:
  1. Typed references for data symbols this function reads/writes (§6.1).
  2. Typed references for functions this function calls — *only* for
     functions not yet moved into `dummy.so` (§6.2). Once a callee has its
     own `.inc`, drop its reference here and rely on the `__`-prefixed C++
     symbol instead (and update call sites accordingly).
  3. The function body, with signature changed only by the `__` prefix on
     the name; argument and return types stay byte-identical to the
     `PPMonstr.cpp` declaration.

## 5. Redirection: patching a JMP at the original VA

`dummy_init()` runs in the ELF's process **after** the loader has mapped the
original `PPMonstr.exe` code pages at their image VAs but **before** `main`.
For each moved function, `dummy_init()` overwrites the first bytes of the
original function with an absolute jump to the new implementation.

Use the 14-byte RIP-relative absolute jump, which works regardless of where
`dummy.so` is loaded relative to the original image:

```
FF 25 00 00 00 00          jmp qword ptr [rip+0]
<8 bytes: target address>
```

Steps for each redirect (do all of these inside `dummy_init()`):

1. Compute `void *orig = (void*)0x<VA>;` — the address from `PPMonstr.txt`.
2. Make the page writable:
   `mprotect(page_align(orig), len, PROT_READ|PROT_WRITE|PROT_EXEC);`
   where `page_align` rounds down to the system page size and `len` covers
   the 14 bytes (handle the case where the patch straddles two pages).
3. Write the 14-byte trampoline with `target = (uint64_t)&__sub_XXXXXXXX;`.
4. Restore protection to `PROT_READ|PROT_EXEC` (optional but advised).
5. Flush the instruction cache for the patched range (`__builtin___clear_cache`).

A single helper in `dummy.cpp`, e.g. `patch_jmp(void *orig, void *repl)`,
should encapsulate all of the above so each redirect is a one-liner:

```cpp
patch_jmp((void*)0x14001A5C0, (void*)&__sub_14001A5C0);
```

`dummy_init()` is therefore a list of `patch_jmp(...)` calls — one per moved
function — in any order.

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
typedef __int64 t_unknown_libname_22(_QWORD, _QWORD);
static t_unknown_libname_22& unknown_libname_22 = *(t_unknown_libname_22*)0x140021696;
```

Rules:
- `typedef` the **function type**, then bind a reference (not a pointer) to
  the address. Calling `unknown_libname_22(...)` then resolves to a direct
  call through the typed reference.
- Argument and return types must match the prototype in `PPMonstr.cpp` byte
  for byte (calling convention, widths, `_QWORD` vs `void*`, etc.).
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

## 7. Verification

The "test" referenced throughout this document is a **fixed, reproducible
end-to-end run** of `PPMonstr.elf` — typically compression + decompression of
a known corpus followed by a byte-for-byte comparison against the expected
output. The exact command line is project-defined; what matters is that the
same command runs after every step and is the sole gate for promoting an
`.inc` from "drafted" to "accepted".

If the test ever fails:
1. The breakage is in the most recently added `.inc` or its redirect.
2. Revert that single commit, re-run the test to confirm green baseline,
   then re-attempt the function with the discrepancy isolated.

## 8. Completion criterion

The decompilation is complete when:

- Every function listed in §1 has its own `.inc` file.
- `dummy.cpp` `#include`s all of them.
- `dummy_init()` patches a redirect for each one.
- The test passes.

At that point the bodies in `PPMonstr.cpp` are dead code (every entry has
been overwritten by a JMP at runtime), and the `.inc` set is a standalone
reimplementation that can be compiled into a native binary without the
`PPMonstr.exe` donor.
