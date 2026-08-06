# incdec working tree for BMF.exe

An application of [`../incdec.md`](../incdec.md) to `exe32/BMF.exe`: function
bodies are moved out of the Hex-Rays decompilation into `dummy32.so` one at a
time, each gated on a `-S -Q9` compress/decompress round-trip.

**Status: 21 of 64 called functions redirected, gate green on both test images.**

## Layout

| Path | Role |
|---|---|
| `BMF.c` | Hex-Rays donor. **Not committed** (1.2 MB of decompiled third-party code); drop it here to re-run the pipeline. |
| `BMF.asm` | IDA disassembly. **Not committed** (3.5 MB); the source of `symbols.txt`/`funcs.txt`/`winapi.txt`. |
| `funcs.txt` | 354 code symbols from `BMF.asm`, including the statically-linked CRT entries. |
| `winapi.txt` | 59 WinAPI IAT slots read from the PE import directory. |
| `sites.txt` | 113 function definitions found in `BMF.c`: VA, name, calling convention, source line. |
| `symbols.txt` | 844 globals: VA, name, type, extent. |
| `called.txt` / `targets.txt` | What a `-S -Q9` round-trip actually executes (§ below). |
| `extractable.txt` | Targets whose every external reference resolves. |
| `accepted.txt` | The moved set, in include order — drives `build.sh`. |
| `fail.txt` | Everything not moved, grouped by root cause. |
| `inc/*.inc` | One moved function each. |
| `trace32.cpp` | INT3 first-call tracer (see below). |
| `dummy32_head.cpp` | incdec infrastructure: probe registry, `patch_jmp`, IAT hook (`incdec.md` §5, §7). |
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

Each invocation runs under `timeout 60`; see below for why.

## Finding the called set

`incdec.md` §3 warns that a function with probe count 0 passes the test
trivially. Rather than discover that one function at a time, `trace32.cpp`
answers it up front: it writes `0xCC` over the first byte of all 113 entries
and catches `SIGTRAP`. On the first hit for a site it records the name,
restores the byte and rewinds `EIP`, so each function traps exactly once and
the run continues at full speed — and, being one byte, it needs no
instruction-length decoding the way a JMP hook would. The round-trip still
verifies with the tracer installed.

Two images are traced, because they do not overlap: the 24bpp one drives the
truecolour path and the 1bpp one the bilevel path. Union: **68 of 113
called** (67 from 24bpp, 44 from 1bpp), of which 4 are
`__usercall`/`__userpurge` (no g++ equivalent, §4), leaving 64 candidates.
Exactly one function — `sub_4148F0` — is reached *only* by the 1bpp image,
and its probe confirms it (473 calls per 1bpp run, 0 on the 24bpp runs).

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

Result: **62 of 64 candidates extract**, up from 35 before the disassembly.

## Why 21 and not 62

Extraction is not acceptance: 41 candidates produce a `.inc` that then fails
to compile, fails the gate, or hangs. `fail.txt` groups them; the largest
buckets are Hex-Rays constructs g++ will not take (`@<reg>` annotations and
`_EAX` pseudo-registers in bodies the decompiler could not fully lift, MSVC's
`__m128i` union members, `BYTE4`/`abs32` helpers), plus extractor gaps in
local-vs-global name resolution and array-vs-scalar typing.

Three failures are worth calling out because only a *running* test finds
them:

* **`sub_413430` builds, runs, and produces a different compressed stream.**
  It passed when the gate used one image; adding the 1bpp image caught it.
* **`sub_424500` and `sub_4256F0` hang** — the decompiled body loops forever.
  The gate now runs each invocation under `timeout 60`, without which the
  driver simply stopped making progress (a hang is not a failure unless
  something makes it one).

These are exactly the cases §3 step 7 is about, and they are the reason the
protocol insists on a green test per function rather than a batch conversion.

## Caveats

* Every accepted function has a non-zero probe count over the four runs
  (24bpp compress/decompress, 1bpp compress/decompress), so none is accepted
  on the strength of never being called (§9).
* `sub_4248D0` was accepted under the single-image gate but fails the
  two-image one and is no longer in `accepted.txt`.
* `extract.py` derives calling conventions from the donor signature per §4 —
  no attribute for `__cdecl` (gcc's i386 default), `__attribute__((thiscall))`
  / `((fastcall))` / `((stdcall))` otherwise. It renames `this` (a C++
  keyword) to `_this`.
