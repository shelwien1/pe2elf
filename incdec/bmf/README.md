# incdec working tree for BMF.exe

An application of [`../incdec.md`](../incdec.md) to `exe32/BMF.exe`: function
bodies are moved out of the Hex-Rays decompilation into `dummy32.so` one at a
time, each gated on a `-S -Q9` compress/decompress round-trip.

**Status: 12 of 63 called functions redirected, gate green.**

## Layout

| Path | Role |
|---|---|
| `BMF.c` | Hex-Rays donor. **Not committed** (1.2 MB of decompiled third-party code); drop it here to re-run the pipeline. |
| `sites.txt` | 113 function definitions found in `BMF.c`: VA, name, calling convention, source line. |
| `symbols.txt` | 305 globals: VA, name, type, extent. |
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
./test.sh --baseline      # capture ref.bmf from the un-injected binary
python3 drive.py extractable.txt
./build.sh && ./test.sh   # PASS
```

`test.sh` compresses `test.bmp` with `-S -Q9`, requires the compressed stream
to be byte-identical to `ref.bmf`, then decompresses and requires the image
back byte-identical. Both halves matter: comparing only the round-trip would
accept a build that silently encodes differently but still decodes.

## Finding the called set

`incdec.md` §3 warns that a function with probe count 0 passes the test
trivially. Rather than discover that one function at a time, `trace32.cpp`
answers it up front: it writes `0xCC` over the first byte of all 113 entries
and catches `SIGTRAP`. On the first hit for a site it records the name,
restores the byte and rewinds `EIP`, so each function traps exactly once and
the run continues at full speed — and, being one byte, it needs no
instruction-length decoding the way a JMP hook would. The round-trip still
verifies with the tracer installed.

Result: **67 of 113 called**, of which 4 are `__usercall`/`__userpurge`
(no g++ equivalent, §4) leaving 63 candidates.

## Why only 12 of 63

`incdec.md` §2 lists `BMF.txt` (a symbol/address table) as a required
artifact. It does not exist for this target, so the only addresses available
are the ones encoded in Hex-Rays' own names — `dword_441A20` is the sole
evidence that the global sits at `0x441A20` — plus the
`// <addr>: using guessed type <type> <name>;` comments after each body,
which `symbols.txt` harvests and which crucially cover globals whose names
carry no address (`n0x800000`, `n256_0`, …).

Everything else is unreachable, and `extract.py` refuses rather than emit
something that mislinks. The breakdown in `fail.txt`:

| Cause | Count | Notes |
|---|---|---|
| Globals with no recoverable address | 13 | `buf`, `buf_0`, `n256_1` are declared in `BMF.c` but appear in no address-bearing comment. Unblocked by a real symbol table. |
| BMF's static CRT | 28 (pre-filtered) | `fopen`/`fread`/`fwrite`/`operator new`… are linked *into* the image, so they have no import to bind to and no symbol. §6.5 forbids letting the stateful ones fall through to glibc — BMF's `FILE*` and heap blocks belong to its own private runtime. |
| `n256_*` array/scalar typing | 4 | Declared `int n256_0[]`; some bodies use it as a scalar. Needs per-site typing. |
| SSE vector idioms | 4 | e.g. `xmmword_X = 0LL` (a `pxor`), MSVC's `__m128i` union members (`.m128i_i32`), which GCC's vector type does not have. §8.4. |
| `_EAX` / `@<reg>` leftovers | 2 | Pseudo-registers in bodies Hex-Rays could not fully lift. |

All five are recoverable with a symbol table and per-function hand-editing —
which is what §3 expects anyway; `extract.py` is scaffolding, not a finished
`.inc` (§8.5).

## Caveats

* `inc/sub_4248D0.inc` compiles with `-Wint-to-pointer-cast`: Hex-Rays typed
  a byte load as a pointer. The function is exercised 921,600 times per
  compress run and the output stays byte-identical, so the behaviour matches
  the original, but the typing is wrong and should be cleaned up by hand.
* `extract.py` derives calling conventions from the donor signature per §4 —
  no attribute for `__cdecl` (gcc's i386 default), `__attribute__((thiscall))`
  / `((fastcall))` / `((stdcall))` otherwise. It renames `this` (a C++
  keyword) to `_this`.
