# BMF Incremental Decompilation Protocol

## 0. Goal

Produce a working, standalone C++ source for `BMF.exe` by **incrementally
moving function bodies** out of the Hex-Rays output (`BMF.cpp`) into a
companion shared library (`dummy32.so`), one function at a time.

After each function is moved, the binary must still pass its functional test.
Once every in-scope function has been moved and the test still passes, the
collected `.inc` files form a complete, self-contained reimplementation of the
original program.

`BMF.exe` is a **32-bit PE (PE32 / `IMAGE_FILE_MACHINE_I386`)**, so this
protocol runs on the `pe2elf32` / `winapi_shim32.so` pipeline. Almost
everything below differs in detail from the x64 protocol this document was
derived from — calling conventions, pointer widths, IAT slot size, the reach
of a `jmp rel32` — and those differences are called out where they bite.

## 1. Scope (which functions to decompile)

Decompile **only** the program's own functions:

- `main` (at `0x00401000`, see §9.1)
- Every `sub_4*` listed in `BMF.cpp` that is not part of the C runtime

Everything else (C runtime, Win32 API, `unknown_libname_*`, intrinsics, etc.)
is a **library function**: do not rewrite it. Reference it from its known
address (see §6.2) and leave the original code in place.

**Telling application code from runtime code is harder here than in a
dynamically-linked binary.** `BMF.exe` is statically linked against the MSVC
CRT, so `printf`, `fopen`, `malloc` and friends live inside the image at
ordinary `sub_4*`-style addresses rather than behind an import. The image
layout is:

| Section | VA range | Contents |
|---|---|---|
| `.text`   | `0x00401000`–`0x00437B59` | code (application **and** static CRT) |
| `.rdata`  | `0x00438000`–`0x00440554` | IAT at `0x00438000`, read-only data |
| `.data`   | `0x00441000`–`0x00447518` | writable data |
| `.trace`  | `0x00448000`–`0x00448164` | |

Working heuristic: application code sits low in `.text` (`main` is at the very
start, `0x00401000`) and the CRT occupies the upper part — the entry point is
`0x0042D53A`, and every function the startup path calls *other than `main`
itself* lies above `0x0042D000`. Treat that as a hint, not a rule: confirm
each candidate against `BMF.txt` / `BMF.asm` before deciding it is
application code. A CRT function accidentally
"decompiled" will usually still pass the test (the reimplementation is
correct-by-construction from Hex-Rays output) but it wastes an iteration and
inflates the completion criterion in §10.

## 2. Toolchain and artifacts

| Artifact | Role |
|---|---|
| `BMF.exe` | Original Windows PE32 binary, the source of truth. |
| `BMF.cpp` | Hex-Rays decompilation, used as the donor for function bodies. |
| `BMF.h`   | Hex-Rays type declarations included by `dummy32.cpp`. |
| `BMF.txt` | Symbol-to-address table (`<8-hex VA>  <name>`, one per line). |
| `BMF.asm` | Full disassembly with symbols. Use this as a reference when the Hex-Rays output is ambiguous, when a decompiled function produces wrong output, or when `cmp` fails and the root cause is not obvious from the C pseudocode alone. Unlike raw `objdump` output, this listing retains named labels (function names, data symbols) which make it far easier to trace control flow and identify the intended operation. |
| `pe2elf32`     | Converter: `./pe2elf32 --inject=dummy32.so BMF.exe BMF.elf` produces an ELF whose `DT_NEEDED` list contains `dummy32.so`, so it is loaded at startup. |
| `dummy32.cpp`  | The growing shared library; built into `dummy32.so` by `make`. |
| `dummy_init()` | `__attribute__((constructor))` in `dummy32.cpp`; runs once at process start, before `main`. This is where redirection patches are installed. |
| `sub_XXXXXX.inc` | One file per moved function (see §4). |

`dummy32.so` is built at a **fixed preferred base address** of `0x30000000`.
Unlike the x64 case, this is *not* about reach — see §5, where a `jmp rel32`
turns out to cover the entire i386 address space. It is about **predictable
placement**: `0x30000000` is comfortably above the PE image
(`0x00400000`–`0x00449000`) and comfortably below the region where
`ld-linux.so.2`, `libc` and `winapi_shim32.so` land (around `0xF7xxxxxx`), so
the request is honored and nothing collides. A 32-bit address space is packed
enough that picking an address at random is a real risk.

Required linker flags in the `dummy32.so` rule of `Makefile`:

```
-m32 -Wl,-Ttext-segment=0x30000000 -Wl,-z,max-page-size=0x1000
```

This is a *preferred* base — glibc's `ld-linux.so.2` honors a non-zero
`p_vaddr` on `ET_DYN` objects as long as the range is free. `dummy_init()`
should still print its own address at startup so a surprise placement is
visible immediately rather than showing up as mysterious wrong behavior.

Build / run loop after any change to `dummy32.cpp` or its includes:

```sh
make dummy32.so
./pe2elf32 --inject=dummy32.so BMF.exe BMF.elf
cp winapi_shim32.so dummy32.so /path/to/run/
./BMF.elf <test inputs>          # verification: must succeed
```

## 3. Per-function workflow

For each function `sub_XXXXXX` (or `main`), do the following in order. Do not
batch multiple functions per iteration — the whole point of the protocol is
that **every step ends with a green test**.

1. **Pick the next function.** Start with leaves (functions that only call
   library code) and work upward toward `main`. This keeps the dependency
   chain inside `dummy32.so` acyclic and easy to debug. Prefer functions that
   are reachable on the hot path of the validation test (i.e., ones likely
   to have a non-zero probe count after a successful run); a function with
   probe count 0 passes the test trivially — the redirect may be wrong but
   there is no execution to expose it. If a newly wired function shows
   probe count 0, treat it as unverified and immediately continue to the
   next candidate rather than stopping.

2. **Locate the body** in `BMF.cpp`. Grep for the definition
   (`^<rettype> __cdecl <name>\b`, `^<rettype> __stdcall <name>\b`, …), not
   the forward declaration. **Note the calling convention Hex-Rays printed —
   it is part of the signature and §4 depends on it.**

   If you are automating this, do **not** derive the body's extent from a
   scan for definition lines: it misses every `__usercall`/`__userpurge`
   function, because those are printed as `sub_4022C0@<eax>(…)` — the name is
   followed by `@`, not by `(`. Each miss is worse than it looks, because the
   *preceding* function's span then runs on and swallows the missed body
   whole; in `BMF.c` that was 38 of 151 functions, and one `.inc` came out
   holding ten concatenated bodies. Use the `//----- (004XXXXX) --------`
   banner Hex-Rays prints ahead of every function, and record an explicit end
   line per function.

   The symptom of getting this wrong is stray `@<reg>` annotations and
   `_EAX`-style pseudo-registers appearing in bodies that do not contain any —
   which is easily misread as "the decompiler could not lift this function"
   when the real answer is "the extractor handed the compiler two functions".

   Names are per-run too.  Hex-Rays numbers its auto-generated globals from
   scratch each time it decompiles, so re-decompiling the *same binary*
   renumbered the `n0x2000*` family here.  Any symbol table keyed by name goes
   stale across that — a name can vanish, or worse, keep resolving to the
   address it had last time.  Prefer the `// <addr>: using guessed type …`
   comments in the decompilation you are actually extracting from.

3. **Look up the original VA** of the function:
   - Preferred source: `BMF.txt`. Each line has the form
     `<8-hex VA>  <name>`, e.g. `00401000  main`. The VA is the full 32-bit
     image VA.
   - For names of the form `sub_<hex>` the hex digits after `sub_` are the
     VA in lowercase nibbles (`sub_4093A0` ⇒ `0x004093A0`). Use `BMF.txt` as
     the authoritative source; the name is a fallback only.

4. **Create `<name>.inc`** in the repo root (e.g. `sub_4093A0.inc`).
   Two paths:

   - **Recommended (once the tool is retargeted — see §8.5):** run
     `python3 extract_fn.py <name>`. It writes `<name>.inc` with every typed
     reference, `#define` mapping, and probe registration already in place,
     plus a TODO block for anything it could not resolve. Then read §8 and
     apply any rewrites called out in the `WARNING` block.
   - By hand: copy the function body into it verbatim, then make two
     textual changes:
     - **Rename the function** by adding a double-underscore prefix
       (`sub_4093A0` ⇒ `__sub_4093A0`). This avoids ODR / linker
       collisions with the still-present original symbol inside
       `BMF.elf` and any not-yet-moved sibling declarations.
     - **Resolve dependencies** as described in §6. Each external name
       the function references must appear in the `.inc` as a typed
       reference to its known address. Do **not** copy data definitions
       or unrelated function bodies into the `.inc`.

5. **Wire it into `dummy32.cpp`.** Add, after the standard-library / `defs.h` /
   `BMF.h` includes:

   ```cpp
   #include "sub_4093A0.inc"
   ```

   Order of `#include` lines must respect inter-`.inc` dependencies (if
   `__A` calls `__B`, include `B.inc` first).

6. **Install the redirect** inside `dummy_init()` (see §5). After this step,
   any call to the original VA in `BMF.elf` jumps to the `__`-prefixed
   reimplementation in `dummy32.so`.

6a. **Retroactive cleanup in existing `.inc` files.** Search every already-
    committed `.inc` for a typedef+ref pair targeting the same VA as the
    function just decompiled:

    ```sh
    grep -rn "0x<VA>\|<name>" *.inc
    ```

    For each hit in an existing caller's `.inc`, delete the
    `typedef … t_<name>(…);` line and the
    `static t_<name>& __<name> = *(…*)0x<VA>;` line (see §6.3).
    Ensure the newly created `<name>.inc` is `#include`d before the caller's
    `.inc` in `dummy32.cpp`. Failure to do this causes a "redeclared as
    different kind of entity" compile error.

7. **Rebuild and re-test** (§2). If the test fails, the bug is in this single
   function or in its `.inc` dependency block — bisect there, not in earlier
   `.inc` files. Do **not** proceed to the next function until the test is
   green. If the failure is hard to isolate, restore the last known-good
   sources from the backup (see step 7a) and start over.

7a. **Backup on green.** Immediately after the test passes, snapshot
    the current `dummy32.cpp` and all `.inc` files:

    ```sh
    tar Jcf backup dummy32.cpp *.inc
    ```

    This produces a single `backup` file (xz-compressed tar) that captures
    exactly the source state that is known good. The backup is overwritten
    on every successful iteration, so it always reflects the latest verified
    state. To restore after a failed attempt:

    ```sh
    tar Jxf backup
    ```

    This overwrites `dummy32.cpp` and every `.inc` back to the last green
    snapshot. **Important:** `tar` preserves the original file timestamps,
    so `make` may see `dummy32.so` as newer than the restored sources and
    skip the rebuild entirely, leaving the broken binary in place. Always
    force a rebuild immediately after restoring:

    ```sh
    tar Jxf backup && touch dummy32.cpp *.inc && make dummy32.so
    ```

    Re-test to confirm the restored state is still clean before
    reattempting the broken function.

8. **Commit** the new `.inc`, the `#include` line, and the `dummy_init()`
   patch entry as one atomic change.

9. **Update tracking files** (`list.txt` and `fail.txt`).

   - `list.txt` — generated by `python3 make_list.py`; lists every
     non-library function definition found in the donor (all `sub_4*` plus
     `main`). Regenerate any time `BMF.cpp` changes. Some entries are thin
     library wrappers, and with a statically-linked CRT many entries are the
     CRT itself (§1); those may be skipped or left to the end of the
     iteration order. **The shipped script still scans `PPMonstr.cpp` for
     `sub_14*` — see §8.5.**
   - `fail.txt` — maintained by hand; one line per function that was
     attempted and either caused a crash or produced wrong output but whose
     root cause is not yet identified. Format:
     `<name>  <short reason / symptom>`.
     When a function is eventually fixed and passes, remove it from
     `fail.txt`.

## 4. `.inc` file conventions

- One function per file. Filename matches the **original** name without the
  `__` prefix: `sub_4093A0.inc`.
- The function inside is `__sub_4093A0` (double-underscore prefix).
- The `.inc` is a fragment, not a translation unit: no `#pragma once`, no
  include guards, no `#include` lines (those belong in `dummy32.cpp`). It is
  textually inserted into `dummy32.cpp` and compiled as part of it.
- **The function definition must carry the same calling convention Hex-Rays
  printed for it.** This is the single biggest difference from the x64
  protocol, where one blanket `__attribute__((ms_abi))` was correct
  everywhere. On i386 there are four conventions in play and the *default*
  case needs no attribute at all:

  | Hex-Rays signature | Attribute on `__sub_*` | Argument passing |
  |---|---|---|
  | `__cdecl` (or nothing) | **none** — gcc's i386 default is already cdecl | all on stack, caller pops |
  | `__stdcall` | `__attribute__((stdcall))` | all on stack, callee pops (`ret N`) |
  | `__fastcall` | `__attribute__((fastcall))` | ECX, EDX, rest on stack, callee pops |
  | `__thiscall` | `__attribute__((thiscall))` | `this` in ECX, rest on stack, callee pops |

  Getting this wrong is not subtle in one direction and silent in the other:
  a stdcall/cdecl mismatch leaks or over-pops the stack on **every** call, so
  the process usually dies quickly. A fastcall/cdecl mismatch reads arguments
  from the wrong place and behaves like the x64 `ms_abi` bug — wrong output,
  no crash. Mirror the donor signature exactly; do not apply an attribute
  "just in case", because adding `stdcall` to a cdecl function is just as
  wrong as omitting it from a stdcall one.

  **`__usercall` / `__userpurge`.** Hex-Rays emits these when the optimizer
  produced a function with a non-standard register/stack signature — common
  in optimized 32-bit MSVC code, and something the x64 protocol rarely had to
  face. There is no g++ attribute for them. Either leave such a function
  alone (it stays library code), or write a small `naked` assembly thunk that
  marshals the custom convention into a normal cdecl call. Record the choice
  in `fail.txt` if you defer it.

  **The same rule applies to *calling* one, and there it is much easier to
  miss, because it compiles.** `__attribute__((usercall))` is not a GCC
  attribute: g++ emits `warning: 'usercall' attribute directive ignored` and
  then generates an ordinary cdecl call with every argument on the stack,
  while the callee reads them out of `ebx`, `xmm1`, `xmm3`. Nothing fails at
  build time, and if the call sits on a path the test does not reach, nothing
  fails at test time either. On this target that produced a function correct on
  24bpp and 32bpp images and silently corrupting on anything with a palette —
  its only `__usercall` call was the `memset` that clears the palette. **Refuse
  a body that calls a `__usercall`/`__userpurge` function**, at extraction
  time, before a build and test cycle is spent on it.

  There is one exception worth looking for. Hex-Rays sometimes attaches
  register arguments to a function that has none — typically a *chunked*
  function, where it picks up a register read from one of the chunks the entry
  jumps into. Check IDA's stack frame for the callee: if it declares exactly
  the stack arguments and nothing else (`buf = dword ptr 4`, `Val = dword ptr
  8`, `Size = dword ptr 0Ch`), and the value printed in the register slot
  varies arbitrarily between call sites — `0` at some, a pointer at others —
  then it is not an argument. Call the function as cdecl and drop the
  pseudo-arguments from the call site. Both of the Intel CRT's dispatch stubs
  (`memset` and `memcpy`, which test the CPU-level global and jump to the
  matching variant) are this case.

### 4.2 Moving a `__usercall` function: the thunk

Leaving `__usercall` functions alone stops being an option the moment the goal
is a binary that runs none of the original code — on this target they are 28 of
the 92 functions a round-trip executes, and they sit in the middle of the call
graph, so every caller is blocked behind them.

Write the thunk. The body moves out as an **ordinary cdecl function taking
every argument**, register ones included, and the original entry point is
patched to a naked stub that reads the register arguments, lays them out as a
cdecl call, and puts the result back where the caller expects it:

```
push %ebp
mov  %esp, %ebp          ; stack arguments are at 8(%ebp), 12(%ebp), ...
push %ebx ; push %esi ; push %edi
and  $-16, %esp          ; see "alignment" below
sub  $frame, %esp        ; scratch: 4 bytes per GPR argument, 16 per vector
mov  %ecx, ...(%esp)     ; capture the register arguments before anything
movups %xmm1, ...(%esp)  ;   clobbers them; EAX first, it is the only scratch
fnstsw %ax               ;   register the captures themselves need
...
push 12(%ebp)            ; push right to left: stack arguments through EBP,
push ...(%esp)           ;   register ones out of the scratch
call __sub_XXXXXX
lea  -12(%ebp), %esp
pop  %edi ; pop %esi ; pop %ebx
leave
ret                      ; __usercall: caller cleans
ret  $N                  ; __userpurge: callee cleans, N from the original's `retn N`
```

The important property is that **this needs no judgement about which register
arguments are real**. If one is genuine the thunk forwards the caller's value;
if Hex-Rays invented it, the thunk forwards whatever was in the register, which
is exactly what the original body read. The alternative — deciding case by case
— is the analysis in §4 above, and it does not scale past the two or three
functions where the evidence is unambiguous.

Five things will bite you, in the order they bit here:

1. **Patch the entry point to the thunk, not to the body.** `patch_jmp` is
   driven by a table; give it the convention so it can pick. Sending PE callers
   straight to the cdecl body is the whole bug the thunk exists to prevent, and
   it fails silently in exactly the way §4 describes.
2. **Alignment.** The i386 ABI wants `esp` 16-byte aligned at the call, and gcc
   assumes it — a moved body that spills an `__m128` uses an aligned store.
   Nothing in the PE maintains it. `and $-16, %esp`, then pad so the argument
   pushes land back on a multiple of 16.
3. **Vector arguments by `const` reference.** `__m128` by value is passed on
   the stack on a 16-byte boundary, and emulating that layout in hand-written
   asm for an arbitrary mix of argument types is not worth it. Rewrite the
   moved body's vector parameters as references; every argument slot is then
   four bytes and the thunk stays uniform. `const`, because once the *caller*
   is moved too it calls the body directly and is free to pass a temporary —
   `sub_41CAB0(x, (__m128)xmmword_439B60, …)` — which will not bind to a
   non-const reference. The body copies the reference into a local on entry
   anyway (the original took the value in a register, so a write to it is
   local), so there is nothing to lose. The §6.3 forwarder for an
   already-moved callee has to spell the parameter the same way.
4. **`extern "C"` on the moved body.** The thunk's `call __sub_XXXXXX` is
   assembly and names the unmangled symbol. Against a C++ function that symbol
   does not exist — and in a *shared object* an undefined symbol is not a link
   error, so the call quietly becomes a text relocation and the library stops
   loading, with nothing pointing at the cause.
5. **Hidden visibility on that declaration, per function.** Otherwise the call
   needs a PLT entry, which is the other half of the same text relocation.
   Apply it to the declaration, not as `-fvisibility=hidden` for the whole
   translation unit — the flag broke a round-trip here that was green before
   and after.

Verify the thunk on its own before trusting it in the loop: a twenty-line test
program that defines a stub body, calls the generated thunk with the register
convention from inline asm, and checks the arguments arrived, the return value
came back, and the stack is balanced. When the round-trip failed here it took
one such test to establish that the thunk was correct and the fault was in the
patch table.

- Order inside the file:
  1. Typed references for data symbols this function reads/writes (§6.1).
  2. Typed references for functions this function calls — *only* for
     functions not yet moved into `dummy32.so` (§6.2). Once a callee has its
     own `.inc`, drop its reference here and rely on the `__`-prefixed C++
     symbol instead (and update call sites accordingly).
  3. `PROBE_DECL(__sub_XXXXXX)` — registers a counter for this function
     in the global probe list. The `PROBE_DECL` / `PROBE_HIT` macros and
     the `Probe` registry live in `dummy32.cpp` (§7).
  4. The function body, with signature changed only by adding the `__`
     prefix and (where required) the convention attribute; argument and
     return types stay byte-identical to the `BMF.cpp` declaration. The
     first statement in the body is `PROBE_HIT(__sub_XXXXXX);`.

Template for a freshly extracted function (a `__cdecl` one — the common case,
note the absence of any attribute):

```cpp
// data and function typedef-refs go here, then:

PROBE_DECL(__sub_4093A0)
int __sub_4093A0(int a1, char *a2) {
  PROBE_HIT(__sub_4093A0);
  // ... original body, with external names already rewritten ...
}
```

and a `__stdcall` one:

```cpp
PROBE_DECL(__sub_40B120)
__attribute__((stdcall)) int __sub_40B120(int a1) {
  PROBE_HIT(__sub_40B120);
  // ...
}
```

### 4.1 Hand-written replacements

A redirected function has to be *behaviourally* identical to the original.
Nothing requires it to be textually derived from the decompilation, and for a
few bodies it cannot be: the ones Hex-Rays rendered as `__asm { cpuid }` plus
reads of its `_EAX`/`_ECX`/`_EDX` pseudo-registers have no C form at all, and
the decompiler will happily mis-attribute one instruction's result to a
variable it used for another's.

For those, write the `.inc` by hand from what the routine is *for*, and keep
it beside the generated ones so the same build, probe and gate machinery
applies. Verify it against the original rather than against the pseudocode:
for a routine whose whole output is one global, run the un-injected binary
with a shim that prints that global at exit, and compare.

## 5. Redirection: patching a JMP at the original VA

`dummy_init()` runs in the ELF's process **after** the loader has mapped the
original `BMF.exe` code pages at their image VAs but **before** `main`.
For each moved function, `dummy_init()` overwrites the first **5 bytes** of
the original function with a near jump to the new implementation:

```
E9 dd dd dd dd             jmp rel32     ; rel32 = target - (orig + 5)
```

Five bytes is small enough to fit inside even short Hex-Rays stubs without
bleeding into the next function.

**Reach is a non-issue on i386, unlike x64.** The x64 protocol had to pin
`dummy.so` within ±2 GB of the image and sign-check every displacement
against `INT32_MIN`/`INT32_MAX`, because a 64-bit address space can easily
put the two more than 2 GB apart. Here the entire address space *is* 32 bits
and the CPU computes `EIP + rel32` modulo 2^32, so the displacement computed
in 32-bit arithmetic is always exact and `E9 rel32` can reach any target from
any origin. There is nothing to range-check — a check would be vacuous, and
writing one that "fails" would mean the arithmetic was done in the wrong
width. In practice the numbers are not even close to the edge: with the
image at `0x00400000` and `dummy32.so` at `0x30000000` the displacement is
about `+0x2FC00000`.

Steps for each redirect (encapsulated in `patch_jmp(orig, repl)`, called
from `dummy_init()`):

1. `void *orig = (void*)0x<VA>;` — the address from `BMF.txt`.
2. `uint32_t disp = (uint32_t)((uintptr_t)repl - ((uintptr_t)orig + 5));`
3. Make the page writable:
   `mprotect(page_align(orig), len, PROT_READ|PROT_WRITE|PROT_EXEC);`
   where `page_align` rounds down to the system page size and `len` covers
   the 5 bytes (handle the rare case where the patch straddles two pages
   by extending `len` accordingly).
4. Write `E9` followed by `disp` as a little-endian `uint32_t`.
5. Restore protection to `PROT_READ|PROT_EXEC` (optional but advised).
6. Flush the instruction cache for the patched range
   (`__builtin___clear_cache(orig, (char*)orig + 5)`).

With the helper in place, each redirect is a one-liner:

```cpp
patch_jmp((void*)0x004093A0, (void*)&__sub_4093A0);
```

`dummy_init()` is therefore a list of `patch_jmp(...)` calls — one per
moved function — in any order.

**Edge case: function smaller than 5 bytes.** A function whose entire body
is shorter than the 5-byte JMP cannot be patched in place without
overwriting the next function's prologue. If one is encountered, do not
patch it — leave the original in place and call the reimplementation
explicitly from its (moved) callers instead. Document the exception in a
comment in `dummy_init()`.

## 6. Dependency cookbook

A moved function must compile and link without dragging the rest of
`BMF.cpp` along. Replace every external name it touches with a **typed
reference at a fixed address**. Never copy global definitions across.

### 6.1 Data symbols

Given a data definition in `BMF.cpp`:

```cpp
int dword_441A20[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // weak
```

and the matching line in `BMF.txt`:

```
00441A20  dword_441A20
```

emit in the `.inc`, with the alias **scoped to the function**:

```cpp
typedef int t_sub_412B10_dword_441A20[16];
static t_sub_412B10_dword_441A20& __sub_412B10_dword_441A20 =
    *(t_sub_412B10_dword_441A20*)0x00441A20;
#define dword_441A20 __sub_412B10_dword_441A20
```

All `.inc` files are textually included into one translation unit
(`dummy32.cpp`), so two functions referencing the same PE global would
otherwise collide. The obvious fix — one shared `__<sym>` behind an
`#ifndef __PE_DECL___<sym>` guard — is worse than the collision it prevents:
the type is derived per body (see below), so the guard silently gives every
body whichever type the *first* `.inc` in the file happened to pick. Naming
the alias after the function removes the collision without sharing the type.
The `#define <orig> __<fn>_<orig>` mapping is closed by a matching `#undef` at
the bottom of the file.

**Deciding the type is per body, and it is where the silent wrong answers
live.** Take it from, in order:

1. the body's own trailing `// 443398: using guessed type int n256_0;`
   comment, which is the decompiler's view of *that* function;
2. otherwise the `// Data declarations` section, which is the union of every
   use across the image;
3. otherwise the prefix of the auto-generated name (`dword_` → `int`, …).

Indexing in the body forces an array type on top of that. The union view and
the per-body view routinely disagree — `int n256_0[];` in the declaration
section, plain `int` in the body that writes `4 * n256_0`, which does not
compile against an array type. But do **not** run the rule the other way and
demote a declared array to a scalar because this body never wrote a `[`:
`buf = buf_0;` is an array decaying to a pointer, and as a scalar it compiles
fine and reads one byte of image instead. Wrong output, no diagnostic.

When matching a global's name in a body, anchor it. `p_n15[3]` is a parameter
Hex-Rays named after the global it usually receives, not the global; and when
a local shadows the global outright (`unsigned __int16 *n4_3;` alongside
`::n4_3 = n4_7;`), only the `::`-qualified uses are the global's.

Rules:
- The `typedef` names the *array/object type*, not a pointer to it. For
  scalars, no `typedef` is needed: `static int& __f_LOG = *(int*)0x00441A1C;`.
- The `__` prefix on the variable name follows the same convention as §6.5
  (avoid shadowing libc names at global scope).
- The address is taken **verbatim** from `BMF.txt`. Do not guess from
  the name (`dword_441A20` is not always at `0x441A20` — confirm).
- **Pointer-sized data is 4 bytes here.** A global that Hex-Rays typed as
  `_QWORD` in an x64 body would be `_DWORD` in a 32-bit one; take the width
  from `BMF.cpp`, and be suspicious of any `_QWORD` that is being used as a
  pointer.

### 6.2 Function symbols (callees that stay in the original binary)

Given a call site in the donor body:

```cpp
v3 = unknown_libname_22(4, v20);
```

Find the prototype in `BMF.cpp`:

```cpp
// int __cdecl unknown_libname_22(int, int); weak
```

and the address in `BMF.txt`:

```
0042A696  unknown_libname_22
```

Emit in the `.inc`:

```cpp
#ifndef __PE_DECL___unknown_libname_22
#define __PE_DECL___unknown_libname_22
typedef int t_unknown_libname_22(int, int);
static t_unknown_libname_22& __unknown_libname_22 = *(t_unknown_libname_22*)0x0042A696;
#endif
#define unknown_libname_22 __unknown_libname_22
```

Apply the same `#ifndef __PE_DECL___<sym>` guard as for data symbols (§6.1):
two `.inc` files may each call the same PE function, and the guard prevents
the "redefinition of …" compile error. The typedef name is `t_<sym>` (stable,
no per-caller suffix) so the guarded block is identical across all callers
and the first inclusion wins.

Rules:
- `typedef` the **function type**, then bind a reference (not a pointer) to
  the address. Calling `unknown_libname_22(...)` then resolves to a direct
  call through the typed reference.
- **The function-type `typedef` must carry the callee's calling convention**
  (§4) — `__attribute__((stdcall))`, `((fastcall))` or `((thiscall))` as
  printed by Hex-Rays, and *nothing* for `__cdecl`. Since the whole static
  CRT lives in the image, most of these callees are `__cdecl` and need no
  attribute; the ones that do are usually Win32-facing helpers.
- Argument and return types must match the prototype in `BMF.cpp` byte
  for byte (widths, `_DWORD` vs `void*`, etc.).
- Use the address of the **function entry**, not of any thunk or IAT slot.
  `BMF.txt` already lists entries.

### 6.3 Function symbols (callees already moved to `dummy32.so`)

If the callee has its own `.inc` and is therefore present as
`__sub_YYYYYY` in the same translation unit, **do not** add a typed
reference for it. Instead, rewrite the call site in the current `.inc` to
use `__sub_YYYYYY(...)` directly. This keeps the dependency graph among
`.inc` files explicit and removes one round-trip through the patched JMP.

Order `#include "<callee>.inc"` before `#include "<caller>.inc"` in
`dummy32.cpp` so the C++ name is in scope.

**Retroactive cleanup — when a callee is decompiled after its caller.**
`extract_fn.py` writes a typedef + static ref for every callee it finds at
the time of extraction. If you later decompile callee `F`, its `.inc`
defines `__F` as an actual C++ function; the old typedef+ref in
`caller.inc` then produces a "redeclared as different kind of entity" error.
Fix: in `caller.inc`, delete the two lines:

```cpp
typedef <rettype> t_F(<args>);
static t_F& __F = *(t_F*)0x<VA>;
```

Leave the `#define F __F` and `#undef F` lines in place — the body still
refers to `F` by its original name, and those macros map it to the now-real
`__F` symbol. Ensure `F.inc` is `#include`d before `caller.inc` in
`dummy32.cpp`.

**Automating it.** If the driver regenerates `.inc` files, the cleanest form
of this cleanup is to re-emit the *whole* accepted set on every acceptance,
and to re-sort the accepted list callees-first at the same time. Both are
needed and for different reasons: re-emitting flips already-moved callers from
the §6.2 form to the §6.3 form, and re-sorting puts the callee's `#include`
ahead of the caller's, which the §6.3 form requires. Ordering alone does not
help — a caller accepted in an earlier run is not reordered by a
callees-first traversal of the *new* candidates — and re-emitting alone leaves
`__F` used before it is defined.

**The forwarder applies to `__usercall` callees too.** §4.2 gives a moved
`__usercall`/`__userpurge` body an ordinary cdecl signature taking every
argument in order, so the same `void *`-relaxing forwarder works for it — with
the one exception that a vector argument is a `const` reference there and stays
one here, since there is nothing about it to relax.

**Call-site cast after cleanup.** After removing the typedef+static-ref, scan
the caller body for C-style casts that pass a function pointer as this
parameter. If the target parameter type carries a calling-convention
attribute, the cast expression must include it too, or g++ emits a
`-fpermissive` warning about mismatched calling-convention attributes:

```cpp
// wrong — strips stdcall, triggers warning:
sub_403530(f, g, (int(*)(FILE*, FILE*, int))PrintStats, 0);

// correct:
sub_403530(f, g, (__attribute__((stdcall)) int(*)(FILE*, FILE*, int))PrintStats, 0);
```

For plain `__cdecl` targets the cast needs no attribute — which is the
common case here, and one fewer thing to get wrong than on x64.

### 6.4 WinAPI imports (via PE IAT slots)

WinAPI functions are *not* present at their entry point inside `BMF.exe`
— what lives at the listed address is a **4-byte IAT slot** (a dword, not the
qword of a Win64 image) that the loader fills with a pointer to the shim's
resolved function. Calls in the PE code go `call dword ptr [IAT_slot]`, i.e.
one extra indirection.

`BMF.exe` imports 59 kernel32 functions; the IAT occupies
`0x00438000`–`0x004380F0`. Useful slots:

| Slot VA | Import |
|---|---|
| `0x0043800C` | `CreateFileA` |
| `0x00438020` | `VirtualFree` |
| `0x00438024` | `VirtualAlloc` |
| `0x00438030` | `ExitProcess` |
| `0x0043803C` | `GetCommandLineA` |
| `0x00438058` | `ReadFile` |
| `0x0043805C` | `HeapFree` |
| `0x00438060` | `HeapAlloc` |
| `0x00438064` | `WriteFile` |

The Hex-Rays header marks these with commented-out
`extern HANDLE (__stdcall *CreateFileA)(...)` lines; the address in `BMF.txt`
is the slot, not the function. Build the ref as a function-pointer reference
(note the `*` and extra parens). **Win32 API functions are `__stdcall`**, so
unlike most in-image callees these do need the attribute:

```cpp
typedef __attribute__((stdcall)) HANDLE (*pfn_CreateFileA)(
    LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
static pfn_CreateFileA& CreateFileA = *(pfn_CreateFileA*)0x0043800C;
```

By the time `dummy_init()` (and any patched body) runs, the loader has
populated the IAT, so dereferencing the slot at static-init or call time
yields the live function pointer. No `#define` mapping is needed because
the typed ref already uses the canonical name.

A few Win pointer typedefs are not present in `BMF.h` and must be
declared locally before any signature that mentions them:

```cpp
typedef _WIN32_FIND_DATAA    *LPWIN32_FIND_DATAA;
typedef FILETIME             *LPFILETIME;
typedef _SECURITY_ATTRIBUTES *LPSECURITY_ATTRIBUTES;
```

### 6.5 Naming convention for typed references

Every typed reference to a PE-resident symbol gets a `__` prefix and a
`#define <original> __<original>` mapping. The mapping lets the donor body
remain textually unchanged. Two reasons:

- **Avoid shadowing libc.** Without the prefix, a `static int& printf =
  *(...);` at namespace scope would shadow glibc's `printf` for the rest
  of the translation unit (including `dummy_init` and `my_ExitProcess`).
- **Side-effect routing.** Any function with hidden state — `fopen`,
  `printf`, `fread`, `clock`, `errno`, anything that touches the MSVC CRT's
  `_iobuf` table, the heap, or the locale — *must* go through the PE's
  implementation, because the PE-side state and glibc's state are
  independent and incompatible. This matters more here than in a
  dynamically-linked target: `BMF.exe` carries its **entire CRT inside the
  image**, so every `FILE*`, every heap block and every `errno` the program
  touches belongs to that private runtime. A single accidental `fopen`
  against glibc would return a `glibc FILE *` that the PE's `fread` then
  dereferences with the MSVC `_iobuf` layout (§8.3). The `__` prefix +
  `#define` makes routing the default; you have to go out of your way to
  call glibc.
- **Hex-Rays sometimes strips a leading underscore.** `BMF.txt` may list
  `_fread`, `_filbuf`, `_ftol`; the donor source spells them `fread`,
  `filbuf`, `ftol`. The script (`extract_fn.py`, §8.5) handles this fallback
  automatically; if writing by hand, look up *both* spellings in `BMF.txt`.

Pure utility functions with no hidden state (`strcpy`, `memcpy`, `memset`,
`strlen`, `strcmp`) may fall through to glibc — they have identical
semantics on both runtimes and are not always present in `BMF.txt`
anyway. Document each glibc fall-through in a comment.

End the `.inc` with one `#undef` per `#define`, so the macros do not
leak into the next `#include`d body.

## 7. `dummy32.cpp` infrastructure (probe registry + ExitProcess hook)

`dummy32.cpp` provides three pieces of infrastructure that every `.inc` relies
on. None of this needs to be reinvented per function; the snippets below
already live in the file. **The whole of §7 has been verified to work against
`BMF.exe`** — see §9.1 for the transcript.

Note that the stock `dummy32.so` in this repo is built from the shared
one-line `dummy.cpp`; this protocol replaces that with its own
`dummy32.cpp` (§7.4).

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

A 64-bit atomic on a 32-bit target needs the `cmpxchg8b` instruction (i586
and later). The default `-march=i686` provides it and g++ inlines the
increment with no library call, so no `-latomic` is required. If the build is
ever retargeted to `-march=i386`/`i486`, either link `-latomic` or narrow the
counter to `unsigned long` — call counts do not need 64 bits.

### 7.2 ExitProcess IAT hook

`dummy32.cpp` cannot rely on `__attribute__((destructor))` or `atexit()` to
dump the counters. The shim's `kernel32_ExitProcess` calls `_exit()` (see
`shim32_kernel32_proc.hpp`), which bypasses both DT_FINI and the atexit
chain. The program's normal termination path goes
`main → MS CRT → ExitProcess → _exit`, so by the time glibc's exit
machinery would have run, the process is already gone.

Workaround: overwrite the **IAT slot** for `ExitProcess` so BMF calls
our wrapper instead. The slot is at `0x00438030` (§6.4):

```cpp
static __attribute__((stdcall)) void my_ExitProcess(unsigned int code) {
  fprintf(stderr, "[probe] ExitProcess(%u), call counts:\n", code);
  for (Probe* p = g_probes; p; p = p->next)
    fprintf(stderr, "[probe]   %-32s %llu\n", p->name, p->count);
  fflush(stderr);
  _exit((int)code);
}
```

Notes:
- The wrapper **must** be `stdcall` — every Win32 API entry point is, so the
  callee is expected to pop its own argument. A cdecl wrapper here leaves the
  4-byte argument on the stack on return; since the wrapper never returns it
  happens not to matter in this one case, but the attribute costs nothing and
  removes the exception.
- Patching uses a separate helper `patch_iat_slot(slot, repl)` that just
  `mprotect`s the page, writes a **4-byte** pointer, and restores. No reach
  problem because we are writing data, not code.
- Output goes to **stderr** so the file-comparison part of the test
  (§9) is unaffected.
- **Anything a decompiled body prints to glibc `stdout` must be flushed
  explicitly.** `_exit()` in the wrapper skips glibc's stdio flush, so
  buffered output is silently discarded — the message simply never appears,
  with no error. This is the same class of hazard as §6.5 and it bites in
  practice (see §9.1). Prefer `stderr`, or `fflush(stdout)` before returning.

### 7.3 `dummy_init()` checklist

Order of operations in the constructor:

1. Print `&dummy_init` and confirm it falls inside the `0x30000000` window
   (see §2). A surprise placement will not break the JMPs the way it would
   on x64 (§5), but it means the loader ignored the preferred base, which is
   worth knowing before debugging anything else.
2. One `patch_jmp((void*)0x<VA>, (void*)&__sub_XXXXXX);` per moved function.
3. `patch_iat_slot((void*)0x00438030, (void*)&my_ExitProcess);`
   exactly once. (Other IAT hooks may be added later in the same way.)

### 7.4 Makefile dependency on `.inc` files

`dummy32.so` is built from `dummy32.cpp` alone, but it textually includes
every `.inc`. The Makefile rule must list the `.inc` files (and the headers
they depend on) as prerequisites; otherwise edits to a `.inc` silently fail to
trigger a rebuild and the validation test runs against stale code (which
typically still passes because the redirect was already installed from the
previous build — a particularly nasty false positive):

```make
DUMMY32_SRCS = dummy32.cpp

$(DUMMY32_OUT): $(DUMMY32_SRCS) $(wildcard *.inc) $(wildcard *.h)
        $(CC) $(DUMMY32_FLAGS) -o $@ $(DUMMY32_SRCS) $(DUMMY32_LDFLAGS)
```

(The repo's stock rule builds `dummy32.so` from the shared `dummy.cpp` with
no `.inc` prerequisites; point it at `dummy32.cpp` and add the wildcards
before starting a decompilation run.)

## 8. Translating Hex-Rays output to g++

`BMF.cpp` is MSVC-flavored output from Hex-Rays. A handful of constructs do
not compile under g++ as-is; the patterns and remedies are listed here so the
same wheel is not reinvented per function.

### 8.1 Build flags

Add to `DUMMY32_FLAGS` in `Makefile`:

```
-m32 -fpermissive -Wno-narrowing -Wno-write-strings
```

Note what is *not* there: any `-msse*`. Turning SSE on for the whole
translation unit would change the code generated for every body in it, not
just the ones that use intrinsics. Put `__attribute__((target("mmx,sse4.2")))`
on the individual bodies that need it instead, so enabling it for one function
cannot perturb another.

Hex-Rays output relies on MSVC's lenient C-style casts between pointers
and integers (e.g. `(unsigned __int8)v54` where `v54` is `const char*` —
intended as "low byte of the pointer value"). g++ rejects these in C++17
unless `-fpermissive` downgrades them to warnings. `-Wno-narrowing` and
`-Wno-write-strings` silence the noise from struct-initializer narrowing
and string-literal-to-`char*` conversions that appear throughout.

`-m32` is not optional and not merely about pointer width: it also selects
the i386 calling conventions §4 depends on, and makes `long`/`size_t`
4 bytes so the donor body's implicit assumptions hold.

### 8.2 Hex-Rays' own `defs.h`, and MSVC intrinsics

Start from the real thing. `BMF.c` opens with `#include <defs.h>`, and that
header ships with IDA: it defines `LOBYTE`/`BYTEn`/`WORDn`/`SBYTEn`,
`__ROLn__`/`__RORn__`, `__PAIRn__`/`__SPAIRn__`, `__CFADD__`/`__OFSUB__`,
`abs8`…`abs64`, `qmemcpy`, `COERCE_FLOAT`, `_UNKNOWN`, and the `__intN`
aliases — with the exact semantics the decompiler assumed when it emitted
them, and with a `#if defined(__GNUC__)` branch already in place. Copy it into
the working tree and include it; hand-rolling the subset a given body happens
to use is how `BYTE4` and `abs32` end up as "missing helper" build failures a
week later.

Two things it will not do for you:

* **`_WINDOWS_`.** `defs.h` keys `BYTE`/`WORD`/`DWORD`/`LONG`/`BOOL` off
  whether windows.h has been seen, and defines them as *signed* types if it
  has not (`typedef int8 BYTE`, `int8` being plain `char`). The donor was
  compiled against the real windows.h, where they are unsigned. Define
  `_WINDOWS_` and supply the windows.h spellings yourself; letting `defs.h`
  win silently sign-extends every `BYTE` the bodies touch.
* **`__int128` on i386.** There is none. The only things typed that way are
  16-byte `xmmword` globals, so alias it to the SSE register type.

| MSVC construct                              | g++ remedy                                                   |
|---------------------------------------------|--------------------------------------------------------------|
| `_BitScanForward(idx, mask)`                | Macro using `__builtin_ctz`; emit `_BitScanForward` itself.  |
| `_mm_*` SSE intrinsics                      | `#include <immintrin.h>` once in `dummy32.cpp`, plus a per-body `target` attribute (§8.1). |
| `v.m128i_i32[k]`, `q.m64_u64`               | Wrapper unions; see below.                                   |
| `(__m128i)0LL` (compound C-style cast)      | A converting constructor on the wrapper union that zero-extends the scalar — which is what the MOVD/MOVQ behind it does. |
| `(__m128i)(unsigned __int64)scalar`         | Same. **Not** `_mm_cvtsi64_si128`, which is x86-64 only.     |
| `__declspec(align(N))`                      | `#define __declspec(x) __attribute__((x))` + `#define align(n) aligned(n)` scoped around the `#include "BMF.h"`. |
| `__declspec(noreturn)`                      | Already handled by `defs.h` for GCC.                         |

**`__m128i` union members.** Hex-Rays writes `v.m128i_i32[1]`,
`q.m128_f32[0]`, `w.m64_u64`, because on Windows `__m128i`/`__m128`/`__m128d`/
`__m64` are *unions* with those members. GCC's `__m128i` is a bare vector type
with no members at all, and no header changes that — `<intrin.h>` does not,
because on GCC it is just an `x86intrin.h` alias, so the Intel-compiler
spelling it provides on Windows never arrives.

Wrap them instead: one union per register type, holding the vector plus the
MSVC member arrays, with conversions in both directions, and then redirect the
`__m128*` / `__m64` names onto the wrappers *after* the intrinsic headers are
done with the originals. The conversions carry a wrapper through the
intrinsics unchanged (`_mm_mul_ps(a, b)` takes its arguments by
`operator __m128&`, and its result lands back in the wrapper through the
converting constructor), and reinterpreting casts between the four —
`(__m128)xmmword_441120`, which Hex-Rays emits freely — become cross-type
constructors that copy the bits. The unions stay layout-compatible with the
vector types, which is what keeps `*(__m128i *)ptr` addressing a real register
image.

Two follow-on cases need handling:

* The memory-operand intrinsics take a pointer to the *vector* type, and the
  body now casts to the wrapper. Overload them for the wrapper pointer.
* An intrinsic *result* has no members, so `_mm_shuffle_ps(v, v, 1).m128_f32[0]`
  does not compile. Rewrite the call site to wrap the result. This cannot be
  fixed with an overload — C++ does not overload on return type.

The `_BitScanForward` macro (place near the top of each body that uses it):

```cpp
#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)
```

**64-bit arithmetic helpers.** On i386 the MSVC compiler lowers `__int64`
division, modulo, shifts and float conversions to CRT helper routines
(`__alldiv`, `__aulldiv`, `__allshr`, `__ftol`, …). These appear in `BMF.txt`
and may show up as call sites in the donor body. They are library functions —
reference them per §6.2, do not reimplement them. g++ generates its own
inline sequences or libgcc calls for the same expressions written in C, so a
body that Hex-Rays rendered as plain `a / b` on `__int64` needs no special
handling; only an *explicit* `__alldiv(...)` call site does.

### 8.2.1 When Hex-Rays emits C that C++ will not take

A residue of cases are neither an intrinsic nor a convention problem: the
decompiler's own type model is internally inconsistent, and C++ refuses what C
would merely warn about. It types two objects differently and assigns one to
the other (`_WORD *n256_1; char *n256; … n256_1 = n256;`), passes an argument
whose type disagrees with the callee's own signature, subtracts a pointer from
an integer, or dereferences a global it typed as `int`. `-fpermissive` does not
cover pointer conversions.

On i386 every one of these is a 4-byte-to-4-byte reinterpretation, so an
explicit cast is faithful — it changes no code, only what the front end will
accept. Do not hand-edit the `.inc`: it is regenerated. Keep the substitutions
in a data file (one `function / find / replace / why` row each), apply them to
the donor text so the `find` string can be grepped for in the decompilation,
and **fail loudly when one stops matching** — otherwise a re-decompilation
turns a fixup into a silent no-op.

Keep the bar at "reinterpreting cast". Anything that would change behaviour is
a hand-written replacement (§4.1), not a fixup.

### 8.2.2 Two systemic fixes worth reaching for before writing fixups

Most of what looks like a long tail of per-function type errors is two problems
wearing many hats. Fix them once:

**Relax pointer parameters on callee declarations.** Hex-Rays types the same
pointer differently at the call site and in the callee's own signature, all the
time. Declaring every pointer parameter of a *not-yet-moved* callee as `void *`
accepts every spelling and reaches the callee unchanged — a pointer is four
bytes and passed identically, and `T *` converts to `void *` implicitly. Leave
the return type alone; `void *` would not convert back. For an *already-moved*
callee the declaration is the real C++ function and cannot be relaxed, so emit
a `static inline` forwarder that takes `void *` and casts inside. Between them
these cleared eight functions here that had been queued up as individual casts.

**Detect a function reference, not just a call.** A scan for `name` followed by
`(` misses the pointer forms — `(void (__cdecl *)(int, int))::sub_42BB20` — and
misses the case where Hex-Rays names a *local* after the function it holds
(`void *sub_428BE0;` alongside `::sub_428BE0`), where the name still has to be
declared for the qualified form to resolve. Scan for any known function name.

And a warning about the scan itself: it looks for an identifier followed by
`(`, so blank out string and character literals first — help text contains
things like `function(`. Get the escape handling right. A regex that required
two backslashes for an escape meant every string containing `\n` failed to
match, the search ran on to a later quote, and the code *between* two string
literals disappeared from the scan. The symptom was an undeclared identifier a
hundred lines from the cause, and it hid real references for several passes.

### 8.2.3 Stack alignment, which bites from two directions

Neither of these produces a compile error, and neither is deterministic: they
are latent until some unrelated change moves a stack frame, at which point a
function that had been green for weeks starts faulting. Both surface as
`SIGSEGV` with `si_addr == 0` — an unaligned `movaps`/`movdqa` raises `#GP`,
not `#PF`, and Linux reports `#GP` with a null fault address. **A null
`si_addr` at a store whose operand is obviously a valid pointer means
misalignment, not a null pointer.** That one fact saves a lot of time.

**Incoming: the PE caller does not align the stack.** g++ for i386 assumes
`%esp` is 16-byte aligned at function entry and spills SSE locals with
`movaps ...,N(%esp)`. The Microsoft ABI only promises 4. A moved function is
entered by a `jmp` patched over the original's first instruction, so its caller
is whatever PE code was there before, and every SSE-using entry point is one
odd call away from a fault. Put
`__attribute__((force_align_arg_pointer))` on every moved entry point. Not
`-mstackrealign`: applied to the whole translation unit it broke the round-trip
here, and internal g++-to-g++ calls never need it. `__usercall` thunks (§4.2)
already do their own `and $-16, %esp`, so they are exempt.

**Outgoing: Hex-Rays' locals have lost their alignment.** The original frame
was 16-byte aligned and Hex-Rays' locals sit at fixed offsets in it, so a body
that stores through a cast into a local array —

```c
_BYTE v31[272];                     // [esp+10h] [ebp-110h]
...
*(__m128i *)&v31[k + 1] = v7;       // k = 15, 31, 47, ...  aligned in the original
```

— is relying on `v31` being 16-byte aligned, which the declaration Hex-Rays
wrote does not say and g++ has no reason to arrange. Give every local array in
an SSE-using body `alignas(16)`. It is free where it is not needed, and the
frame-reassembly buffer of §4 already does the same thing for the same reason.

### 8.2.3.1 Shift counts, and the bug that only makes the output bigger

x86 masks a variable shift count to five bits. C++ leaves a count of 32 or more
undefined, and Hex-Rays prints what the instruction computes, so both of the
idioms that rely on the masking come out as undefined behaviour:

| Hex-Rays writes | the instruction is | what it means |
|---|---|---|
| `x >> -n` | `neg ecx; shr eax, cl` | `x >> ((-n) & 31)` |
| `1 << (n + 31)` | `lea ecx, [edi+1Fh]; shl ebx, cl` | `1 << (n - 1)`, the rounding constant before `sar` by `n` |

Mask both. The mask is free where the count is already in range — g++ knows
x86 masks and emits the same `shl %cl` — so there is no reason to be selective.

The second one is worth calling out on its own, because it is the only defect
in this whole exercise that produced **no wrong answer at all**. Every image
still round-tripped losslessly; the compressed stream was just twenty bytes
bigger. A compressor's model can be wrong without its coder being wrong, so
"decompresses to the original" is not a strong enough check — the size
comparison in the gate is what caught it. `sub_41CAB0` had 86 of them.

### 8.2.4 A pointer that is really a counter, and the loop g++ deletes

Hex-Rays types a *register*, not a value, so a register that holds a pointer
somewhere in the function is typed as one everywhere — including where it is
being used as a plain loop counter. That is harmless until the counter is
tested against zero:

```c
v43 = (unsigned __int16 *)v32[1];      // a count, e.g. 2 — `mov edi, [ecx+4]`
do {
  ...
  v43 = (unsigned __int16 *)((char *)v43 - 1);   // `dec edi`
} while ( v43 );                                 // `jnz`
```

Subtracting from a pointer can never produce a null pointer in C — the result
would have to be outside the object, which is undefined — so g++ folds
`while (v43)` to `while (1)`. The loop back-edge in the generated code becomes
an unconditional `jmp` with the test gone entirely, and the body walks off the
end of the array it is sorting. Nothing warns, `-O0` hides it, and no single
`-fno-…` switch disables the inference.

Launder the arithmetic through an integer, so the pointer is
integer-derived — a value that *may* legitimately be null — rather than
object-derived:

```c
v43 = (unsigned __int16 *)((uintptr_t)v43 - 1);
```

On i386 that is the same `dec`; only the inference g++ is allowed to draw
changes. Worth grepping for across the whole donor: any `while (p)` /
`if (p)` on a local that the same body steps with `(char *)p ± k`.

### 8.3 MSVC `FILE` layout

Hex-Rays bodies access MSVC `_iobuf` internals: `v17->_cnt`, `v17->_ptr`,
`v17->_flag`. glibc's `FILE` has none of these fields. `BMF.h`
defines the MSVC `_iobuf` under the typedef name `FILE`, which `dummy32.cpp`
renames to `FILE1` via `#define FILE FILE1` around the include.

The Win32 `_iobuf` is **32 bytes**, half the size of the Win64 one, and every
member is at a different offset:

```
_ptr @0x00   _cnt @0x04   _base @0x08   _flag @0x0C
_file@0x10   _charbuf@0x14  _bufsiz@0x18  _tmpfname@0x1C
```

Any hand-written offset arithmetic against a `FILE*` — and any `_iobuf`
table indexing, which strides by 32 here rather than 48 — must use these.

Inside the `.inc`, re-enable the MSVC layout for the body:

```cpp
#define FILE FILE1
// ... typed refs, body ...
#undef FILE
```

All typed refs that take `FILE *` (`fopen`, `fread`, `setvbuf`, …)
are inside this `#define` scope, so they typedef-resolve to `FILE1*` —
matching what the PE's MSVC CRT actually expects.

### 8.4 Anti-patterns to recognize and rewrite

Hex-Rays sometimes emits code that compiles but means something different
under g++ than under MSVC. Several patterns to watch for:

**A. Inter-local pointer arithmetic (Hex-Rays expansion of memcpy).**

```cpp
v26 = 320;
do {
  *(_DWORD *)&v130[v26 - 4] = *(HANDLE *)((char *)&hFindFile + v26);
  *(int *)((char *)&v128 + v26) = *(int *)((char *)&v152 + v26);
  ...
} while(v26);
```

These multi-stream loops are Hex-Rays' representation of a single block
copy that the original asm did with `rep movsd`. They depend on the
named locals being laid out **contiguously in a specific order** in
the stack frame. g++ does not preserve that order — it lays out locals
however it wants (often grouped by alignment class) — so the writes
land on the wrong memory.

**Remedy:** identify the semantic intent (almost always a memcpy of N
bytes from a struct to a heap object) and rewrite as a single
`memmove(dst, src, N)`. Document the original loop in a comment so the
intent is preserved. The script in §8.5 flags this pattern.

**Why not "wrap the locals in a struct"?** That preserves the *relative*
order of named members, but the original stack frame had compiler-chosen
gaps (other locals, alignment padding) between them. The Hex-Rays code
uses *specific numeric offsets* (e.g. `&v130 + 312`) that include those
gaps. Reproducing the exact frame in a portable C++ struct is brittle
and undocumented; `memmove` against the conceptual source is both
clearer and correct.

The same UB pattern appears for **zeroing** (not just copying). The original
asm uses `pxor xmm0,xmm0` followed by a stream of `movaps` to zero a
contiguous region. Hex-Rays lifts this as a loop over overlapping `__int128`
(xmmword) arrays with large, compiler-dependent offsets:

```cpp
// Hex-Rays zeroing expansion — DO NOT use:
xmmword_442500[64] = 0;
xmmword_442510[63] = 0;
xmmword_442520[62] = 0;
xmmword_442530[61] = 0;
```

Replace with a direct `memset` against the region's base address and byte
count (both readable from the asm):

```cpp
memset((void*)0x00442540, 0, 0x400);
```

**B. `operator new`.**

```cpp
v25 = (void **)operator new(328u);
```

`operator new` is a C++ keyword pair, not an identifier — the
preprocessor cannot replace it with a `#define`. Declare the typed ref
with a plain identifier name (e.g. `__op_new`) and rewrite the call
sites in the body:

```cpp
typedef void* t_op_new(size_t);
static t_op_new& __op_new = *(t_op_new*)0x<VA of ??2@YAPAXI@Z>;
// in body:  v25 = (void **)__op_new(328u);
```

(Note the 32-bit MSVC mangling `??2@YAPAXI@Z`, not the x64 `??2@YAPEAX_K@Z`.)
`BMF.exe` is a C program, so it may not have `operator new` at all — this
pattern is listed for completeness.

**C. Missing calling-convention attribute on callback / function-pointer
parameters.**

Hex-Rays represents callback parameters as plain C function pointers,
carrying the convention only in the comment or the `__stdcall` spelling:

```cpp
int sub_403530(FILE *f, FILE *g, int (__stdcall *a3)(FILE *, FILE *, int), int a4)
```

If the target is `__stdcall`, the parameter type must carry
`__attribute__((stdcall))`:

```cpp
int __sub_403530(
    FILE *f, FILE *g,
    __attribute__((stdcall)) int (*a3)(FILE *, FILE *, int),
    int a4)
```

Without it the caller pops arguments the callee already popped, and the stack
unwinds by 4·N too much — usually a prompt crash rather than the silent
garbage the x64 equivalent produced. For `__cdecl` callbacks (the majority
here) no attribute is needed on either side. (See also §6.3 for the
corresponding call-site cast rule.)

**D. Vftable address syntax.**

Hex-Rays emits vftable addresses using MSVC decorated-name syntax that g++
cannot parse:

```cpp
dword_441780 = &std::bad_alloc::`vftable';   // syntax error in g++
```

Look up the vftable address in `BMF.txt` (the symbol will be listed
under the mangled name, e.g. `??_7bad_alloc@std@@6B@`) and replace with a
numeric cast:

```cpp
dword_441780 = (void*)0x00438990;   // &std::bad_alloc::`vftable'
```

### 8.5 `extract_fn.py` — automated `.inc` scaffolding

> **Status: not yet retargeted.** `extract_fn.py` and `make_list.py` were
> written for the x64 PPMonstr target and still assume it in three places:
> they read `PPMonstr.cpp` / `PPMonstr.txt` by hardcoded filename
> (`extract_fn.py:38-39`, `make_list.py:8`); `make_list.py` matches
> `sub_14[0-9A-Fa-f]+` plus the PPMonstr-specific names `Alloc_PPMblock`
> and `PrintStats` (`make_list.py:5`), which will find nothing in a BMF
> donor whose functions are `sub_4xxxxx`; and `extract_fn.py` emits
> `__attribute__((ms_abi))` unconditionally on every typedef and definition
> (`extract_fn.py:405,413,425,440`), which is wrong for **every** i386
> convention including the common cdecl case (§4).
>
> Retargeting is three small edits (filenames, the name regex, and deriving
> the convention from the donor signature instead of hardcoding one), but
> until they are made, extract the first few functions **by hand** per §4
> and §6 rather than trusting the scaffold. The rest of this section
> describes the tool's behaviour as designed.

Usage:

```sh
python3 extract_fn.py <function_name> [--out path]
```

It reads the donor `.cpp` + `.txt`, locates the function, then for
every external identifier the body touches it emits a typed reference at
the looked-up address (with `__` prefix and `#define` mapping per §6.5).
It distinguishes PE-internal functions, MSVC CRT entries, WinAPI IAT
slots, and globals; falls back to underscore-prefixed lookups when the
body name differs from the symbol-table name; and prefixes the body with
`PROBE_DECL` / `PROBE_HIT`. Every static ref declaration is wrapped in a
`#ifndef __PE_DECL___<sym>` guard (§6.1) so that two `.inc` files
referencing the same PE global or function compile cleanly in the same TU.

What it does **not** do:

- Translate the §8.2 / §8.4 anti-patterns. The tool *flags* them in a
  `// ---- WARNING: patterns that need manual rewrite ----` block at the
  top of the output; you still rewrite by hand.
- Infer prototypes that aren't present in `BMF.cpp` as forward
  declarations. The tool emits a TODO and a placeholder `void(...)` typedef.
- Generate the `patch_jmp` call in `dummy32.cpp` — add that by hand.
- Detect self-recursive functions. For a function that calls itself,
  the tool sees the recursive call as just another external callee and
  emits a typedef + static ref pointing at the function's own VA. That
  ref conflicts with the actual C++ definition and produces a
  "redeclared as different kind of entity" compile error. Remove the
  auto-generated typedef + static ref block for the function itself;
  keep only the `#define name __name` line — the recursive call resolves
  directly to the C++ symbol.

Until the retarget in the note above lands, every generated signature must be
re-read against `BMF.cpp`: strip the emitted `ms_abi` and substitute the
convention from §4 — most of the time that means removing the attribute
entirely (cdecl), not replacing it.

## 9. Verification

The "test" referenced throughout this document is a **fixed, reproducible
end-to-end run** of `BMF.elf`: compress a known image, decompress it again,
and compare the result byte-for-byte against the original.

BMF is a lossless compressor, so the round-trip is self-checking — no
separate reference run against an un-injected baseline is needed for the
image data itself. Compare the `.bmf` too, so a change that alters the
compressed stream (but still decodes) is caught.

Baseline (run once, captures the reference `.bmf`):

```sh
make dummy32.so && ./pe2elf32 BMF.exe BMF.elf \
  && rm -f test.bmf ref.bmf \
  && ./BMF.elf test.bmp \
  && mv test.bmf ref.bmf
```

Validation (run after every `.inc` change):

```sh
make dummy32.so && ./pe2elf32 --inject=dummy32.so BMF.exe BMF.elf \
  && rm -f test.bmf \
  && ./BMF.elf test.bmp        `# compress: test.bmp -> test.bmf` \
  && cmp test.bmf ref.bmf      `# encoder output unchanged` \
  && mv test.bmp orig.bmp      `# BMF decompresses back onto test.bmp` \
  && ./BMF.elf test.bmf        `# decompress: test.bmf -> test.bmp` \
  && cmp orig.bmp test.bmp     `# round-trip lossless`
```

`test.bmp` can be generated reproducibly with `python3 exe32/mkbmp32.py
test.bmp 256 192`; `t32.sh` uses the same image for its BMF stage.

**Make the test corpus a fixed point first.** BMF does not preserve every BMP
header field, so a freshly generated image is not one, and a whole-file
comparison against it fails against the *original* binary. The fix is not to
exclude byte ranges from the comparison — that is how the palette went
unchecked here for a while. Put each image through one round-trip of the
un-injected binary and keep the result: from then on the gate is a plain `cmp`
with no exclusions. Verify the settled image really is a fixed point (a second
round-trip must be byte-identical end to end) rather than assuming it.

**Decide what the gate is actually for.** Requiring the compressed stream to be
byte-identical to the original's is the strictest possible check and the right
default while the redirects are unverified. But if the goal is a codec that
replaces the original rather than reproduces it, that requirement rejects work
for the wrong reason. The weaker gate that still has teeth is: the round-trip is
lossless *and* the compressed output is no larger than the reference. Keep
reporting stream divergence — it is information — but do not fail on it. Doing
this here reclassified three failures from "produces a different stream" to
"compresses 5% worse" and "decompresses to garbage", which is the difference
between a formatting difference and a bug.

**One image is not a gate — use one per pixel format.** BMF takes a different
path through the filters and the context model for 1bpp, 8bpp grayscale, 8bpp
palette, 24bpp RGB and 32bpp RGBA, so a redirect that is wrong for one of them
can be perfectly correct for the others and sail through a 24bpp-only test.
Measured on this target: of the twenty candidates that fail the gate, eleven
fail *first* on the 1bpp or 8bpp-grayscale image. Give every format an old-style
40-byte `BITMAPINFOHEADER` — that is what BMF writes back — and generate them
from a fixed PRNG so they are byte-reproducible.

**Compare everything the format round-trips, not just the pixels.** It is
tempting to start the comparison at `bfOffBits` and be done with it, but on an
8bpp image that skips the entire 1 KB palette. Find out what the *un-injected*
binary actually preserves and exclude exactly that: here it is four header
fields (`biXPelsPerMeter`, `biYPelsPerMeter`, `biClrUsed`, `biClrImportant`,
bytes 38..53), which BMF writes back as zero — and nothing else, palette
included.

The validation command is the sole gate for promoting an `.inc` from
"drafted" to "accepted". Re-run the baseline only when `BMF.exe`, the test
image, the encoder flags, or `pe2elf32` itself change.

After a green run, the stderr line `[probe] ExitProcess(0), call counts:`
plus the per-probe counts confirms which decompiled bodies were actually
exercised by this corpus. The per-iteration rule is:

- **Probe count > 0 and both `cmp`s clean:** the function is verified. Stop
  this iteration and commit.
- **Probe count = 0 and `cmp`s clean:** the redirect is wired but never
  taken. The implementation is unverified — do not stop. Continue
  immediately to the next candidate function without committing a new
  iteration boundary (or commit with an explicit note that the function is
  unverified). Such a function is eventually verified when a richer corpus
  exercises it, or it stays in the "accepted gap" list in §10.
- **Either `cmp` fails:** the function is broken. Revert and debug before
  proceeding.

If the test ever fails:
1. The breakage is in the most recently added `.inc` or its redirect.
2. Restore the last known-good snapshot: `tar Jxf backup` (see §3 step 7a),
   then rebuild and re-test to confirm the baseline is clean again.
3. Re-attempt the function with the discrepancy isolated. Alternatively,
   revert the git commit for that function instead of using the tar backup —
   both return you to the same known-good state.
4. If the Hex-Rays pseudocode alone does not explain the discrepancy, consult
   `BMF.asm`. It contains the full disassembly with named symbols, which
   makes it straightforward to cross-check control flow, spot arithmetic the
   decompiler mis-typed, find byte-level constants, or verify which branch
   path is actually taken. `objdump` on the ELF lacks these symbol names and
   is a poor substitute.

### 9.1 Worked example: the infrastructure, verified

The §5/§7 machinery has been exercised against `BMF.exe` end to end, with
`main` as the moved function. `main` is at **`0x00401000`** and the CRT calls
it as `__cdecl`: the disassembly at the call site is

```
0042d5dc:  50                       push   eax                ; envp
0042d5dd:  ff 35 54 59 44 00        push   ds:0x445954        ; argv
0042d5e3:  ff 35 50 59 44 00        push   ds:0x445950        ; argc
0042d5e9:  e8 12 3a fd ff           call   0x401000
0042d5ee:  83 c4 0c                 add    esp,0xc            ; caller pops -> cdecl
```

so the reimplementation takes **no** convention attribute:

```cpp
PROBE_DECL(__main)
static int __main(int argc, char** argv, char** envp) {
  PROBE_HIT(__main);
  printf("__main: argc=%d argv[0]=%s\n", argc, argc > 0 ? argv[0] : "(none)");
  fflush(stdout);                 // see §7.2 — _exit() skips glibc's flush
  (void)envp;
  return 0;
}

__attribute__((constructor)) static void dummy_init() {
  fprintf(stderr, "[incdec] dummy32.so loaded at %p\n", (void*)&dummy_init);
  patch_jmp((void*)0x00401000, (void*)&__main);
  patch_iat_slot((void*)0x00438030, (void*)&my_ExitProcess);
}
```

Running `./BMF.elf somefile.bmp` produces:

```
[incdec] dummy32.so loaded at 0x30001140
[incdec] patch_jmp 0x401000 -> 0x30001330 (rel32 2fc0032b)
[incdec] patch_iat 0x438030 -> 0x300013b0
__main: argc=2 argv[0]=./BMF.elf
[probe] ExitProcess(0), call counts:
[probe]   __main                           1
```

Every claim in §2, §5 and §7 is visible here: the library landed in the
`0x30000000` window, the rel32 displacement is `+0x2FC0032B`, the argument
marshalling is correct with no attribute, the probe counted the call, and the
IAT hook dumped on exit with the right code.

The `fflush(stdout)` is load-bearing. Without it, the first run of this
example printed the two `[incdec]` lines and the probe dump but **not**
`__main:` — glibc had buffered it and `_exit()` discarded the buffer. Nothing
reported an error; the output simply was not there.

## 10. Completion criterion

The decompilation is complete when:

- Every function listed in §1 has its own `.inc` file.
- `dummy32.cpp` `#include`s all of them.
- `dummy_init()` patches a redirect for each one.
- The test passes.
- Every probe in the ExitProcess dump reports a non-zero count, **or** the
  zero-count function is explicitly listed as not exercised by the chosen
  corpus (and a corpus extension is filed as future work).

At that point the bodies in `BMF.cpp` are dead code (every entry has
been overwritten by a JMP at runtime), and the `.inc` set is a standalone
reimplementation that can be compiled into a native binary without the
`BMF.exe` donor.
