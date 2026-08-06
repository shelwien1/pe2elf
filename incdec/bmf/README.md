# incdec working tree for BMF.exe

An application of [`../incdec.md`](../incdec.md) to `exe32/BMF.exe`: function
bodies are moved out of the Hex-Rays decompilation into `dummy32.so` one at a
time, each gated on a `-S -Q9` compress/decompress round-trip.

**Status: 41 of 64 called functions redirected, gate green on both test images.**

## Layout

| Path | Role |
|---|---|
| `BMF.c` | Hex-Rays donor. **Not committed** (1.2 MB of decompiled third-party code); drop it here to re-run the pipeline. |
| `BMF.asm` | IDA disassembly. **Not committed** (3.5 MB); the source of `symbols.txt`/`funcs.txt`/`winapi.txt`. |
| `defs.h` | Hex-Rays' own `defs.h`, the header `BMF.c` includes. Supplies the `LOBYTE`/`BYTEn`/`SBYTEn`/`__ROLn__`/`__PAIRn__`/`abs32`/`qmemcpy`/`COERCE_*`/`_UNKNOWN` vocabulary with the semantics the decompiler assumed. |
| `funcs.txt` | 354 code symbols from `BMF.asm`, including the statically-linked CRT entries. |
| `winapi.txt` | 59 WinAPI IAT slots read from the PE import directory. |
| `sites.txt` | 148 function bodies located in `BMF.c`: VA, name, calling convention, first and last source line. |
| `symbols.txt` | 844 globals: VA, name, type, extent. |
| `called.txt` / `targets.txt` | What a `-S -Q9` round-trip actually executes (§ below). |
| `extractable.txt` / `noextract.txt` | Targets whose every external reference resolves, and the ones that refuse with the reason. |
| `accepted.txt` | The moved set, callees-first — drives `build.sh`. |
| `fail.txt` | Extractable candidates that did not survive the gate, with the build error or test result. |
| `inc/*.inc` | One moved function each — exactly the accepted set. |
| `override/*.inc` | Hand-written replacements for bodies the decompiler could not lift into C; see [`override/README.md`](override/README.md). |
| `trace32.cpp` | INT3 first-call tracer (see below). |
| `dummy32_head.cpp` | incdec infrastructure: probe registry, `patch_jmp`, IAT hook (`incdec.md` §5, §7), plus the SSE and Win32 vocabulary `defs.h` does not cover. |
| `extract.py` | `.inc` generator, BMF/i386-targeted. |
| `drive.py` | The incremental loop: extract → build → test → keep or revert. |
| `build.sh` / `test.sh` | Assemble+compile `dummy32.so`; run the gate. |

## Running it

```sh
./test.sh --baseline      # capture ref_*.bmf from the un-injected binary
python3 drive.py extractable.txt
./build.sh && ./test.sh   # PASS
```

For each of the two images, `test.sh` compresses with `-S -Q9`, requires the
stream to be byte-identical to that image's reference, then decompresses and
requires the pixels back identical. Both halves matter: comparing only the
round-trip would accept a build that silently encodes differently but still
decodes.

Comparison starts at each file's `bfOffBits`, not byte 0, because BMF does not
preserve every BMP header field — it drops `biXPelsPerMeter`/`biYPelsPerMeter`
on 24bpp and `biClrUsed`/`biClrImportant` on 1bpp. The **un-injected** binary
loses them too, so a whole-file comparison would fail against BMF itself.

Each invocation runs under `timeout 60`; a hang is not a failure unless
something makes it one, and two candidates do hang.

## Finding the called set

`incdec.md` §3 warns that a function with probe count 0 passes the test
trivially. Rather than discover that one function at a time, `trace32.cpp`
answers it up front: it writes `0xCC` over the first byte of all 148 entries
and catches `SIGTRAP`. On the first hit for a site it records the name,
restores the byte and rewinds `EIP`, so each function traps exactly once and
the run continues at full speed — and, being one byte, it needs no
instruction-length decoding the way a JMP hook would. The round-trip still
verifies with the tracer installed.

Two images are traced, because they do not overlap: the 24bpp one drives the
truecolour path and the 1bpp one the bilevel path. Union: **89 of 148 called**,
of which 25 are `__usercall`/`__userpurge` (no g++ equivalent, §4), leaving
**64 candidates**. Exactly one function — `sub_4148F0` — is reached *only* by
the 1bpp image, and its probe confirms it (473 calls per 1bpp run, 0 on the
24bpp runs).

### Locating the bodies

`sites.txt` is built from Hex-Rays' own `//----- (004XXXXX) --------` banners,
not from a scan for definition lines, and it records an explicit **end** line
per function. This matters more than it sounds: a regex over definition lines
misses every `__usercall` function, because its name is followed by `@<eax>`
rather than by `(`. 38 of the 151 banners were missed that way, and each
missed body was silently swallowed by the span of the function *before* it —
so the extractor was emitting up to ten concatenated function bodies as one
`.inc`. That is where the stray `@` characters an earlier `fail.txt` blamed on
the decompiler actually came from.

Of the 151 banners, 148 parse; the three that do not are an `#error` Hex-Rays
emitted in place of a body it could not analyse, and two `_atodbl` variants
whose definitions it printed without a body.

## Resolving addresses

`incdec.md` §2 lists a symbol/address table as a required artifact, and
`BMF.asm` supplies it. Three tables are derived from it:

* **`symbols.txt`** — 844 globals. 305 come from the
  `// <addr>: using guessed type <type> <name>;` comments Hex-Rays appends to
  each body (the only source for globals whose names carry no address, like
  `n0x800000`); `BMF.asm` adds the other 539, including `buf`, `buf_0` and
  `n256_1`, which were previously unreachable.
* **`funcs.txt`** — 354 code symbols. The statically-linked CRT shows up as
  IDA "COLLAPSED FUNCTION" entries (`_fopen` at `0x0042CDB9`, `_fread` at
  `0x0042CDCC`, …), which is what makes §6.5's routing rule enforceable:
  BMF's `FILE*` objects and heap blocks belong to its private runtime, so
  every stateful stdio call in a moved body is bound to the PE's own entry
  rather than glibc's. Bodies spell these without the leading underscore, so
  the extractor tries `n`, `_n`, `__n` — the fallback §6.5 describes.
* **`winapi.txt`** — 59 IAT slots read from the PE import directory, for the
  handful of bodies that call `VirtualAlloc`/`VirtualFree` directly (§6.4).

`operator new` / `operator delete` have no label at all. Their addresses came
from the call sites instead: every `call` in `BMF.asm` is an `E8 rel32` whose
target can be decoded straight out of the image, giving `0x0042CF0A` and
`0x0042CF18`. That resolver was cross-checked against the 180 call targets
that *do* have labels — **zero disagreements** — before being trusted for the
two that do not.

Six of the 64 candidates still refuse to extract; `noextract.txt` records why.
Five reach an Intel CRT helper (`__svml_log2`, `__intel_sse2_strlen`) that
takes its arguments in registers, and Hex-Rays recovered neither their count
nor their types — `__svml_log2()` is printed with no arguments at all — so a
redirect built on that signature would pass garbage. `main` reaches a global
(`FindFileData`) that appears in no `using guessed type` comment and has no
address in its name, so there is nothing to bind it to.

## Typing the globals

A global's C type is decided **per body**, from three sources in order:

1. the body's own trailing `// 443398: using guessed type int n256_0;`
   comment, which is the decompiler's view of *that* function;
2. otherwise the `// Data declarations` section, which is the union of every
   use across the image;
3. otherwise the prefix of the auto-generated name (`dword_` → `int`, …).

Indexing in the body always forces an array type on top of that. The union
view and the per-body view routinely disagree — `int n256_0[];` in the
declaration section, plain `int` in the body that writes `4 * n256_0` — and
the disagreement is not symmetric: demoting a declared array to a scalar
because *this* body never wrote a `[` turns `buf = buf_0;` from an array
decaying to a pointer into a one-byte read of the image, which compiles and
silently produces wrong output.

Each alias is scoped to the function that uses it (`__sub_416C90_buf_0`), not
shared behind an include guard. Sharing lets whichever body is included first
fix the type for every other one, and since the type is derived per body, that
is routinely the wrong one.

## Why 41 and not 58

Extraction is not acceptance: 17 candidates produce a `.inc` that then fails to
compile or fails the gate. `fail.txt` records each with its build error or test
result.

**Four fail to build** — all the same shape: Hex-Rays emits C that is not valid
C++. It types two locals differently and then assigns one to the other
(`_WORD *n256_1; char *n256; … n256_1 = n256;`), which C accepts with a warning
and C++ rejects outright. `-fpermissive` does not cover pointer conversions.

**Thirteen fail the gate**, and only a running test finds them:

* `sub_413430`, `sub_413900` and `sub_424550` build, run, and produce a
  *different compressed stream*. `sub_413430` passed when the gate used one
  image; adding the 1bpp image caught it.
* `sub_424500` and `sub_4256F0` used to hang forever; both now pass, and the
  `timeout 60` that was added for them stays, because without it the driver
  simply stops making progress.
* The rest abort during compression or decompression.

These are exactly the cases §3 step 7 is about, and they are the reason the
protocol insists on a green test per function rather than a batch conversion.

## Caveats

* Every accepted function has a non-zero probe count summed over the four runs
  (24bpp compress/decompress, 1bpp compress/decompress), so none is accepted
  on the strength of never being called (§9).
* `accepted.txt` is re-sorted callees-first and the whole set re-emitted on
  every acceptance. Both are required: §6.3 turns a call to an already-moved
  function into a bare `#define`, which needs the callee's include to come
  first, and a caller moved *before* its callee otherwise keeps declaring that
  callee at its PE address — which collides with the real definition once the
  callee moves too.
* `extract.py` derives calling conventions from the donor signature per §4 —
  no attribute for `__cdecl` (gcc's i386 default), `__attribute__((thiscall))`
  / `((fastcall))` / `((stdcall))` otherwise. It renames `this` (a C++
  keyword) to `_this`, and any local that collides with a type name.
* SSE is off for the translation unit as a whole and switched on per body with
  `__attribute__((target(...)))`, so enabling it for one function cannot
  change the code generated for any other.
