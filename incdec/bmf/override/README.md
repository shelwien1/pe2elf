# Hand-written `.inc` overrides

`extract.py <name>` copies `override/<name>.inc` verbatim into `inc/<name>.inc`
when it exists, instead of generating one from `BMF.cpp`. Everything downstream —
`accepted.txt`, `build.sh`, `drive.py`, the gate — is unchanged; an override is
just a different way of producing the same file.

`incdec.md` §4 requires a redirected function to be *behaviourally* identical to
the original, not textually derived from the Hex-Rays output. An override is the
right tool when the decompilation is not translatable C at all — most often
because the function is inline assembly the decompiler surfaced as `__asm { … }`
plus reads of its `_EAX`/`_ECX`/`_EDX` pseudo-registers, which have no g++
equivalent.

An override must still:

* define the moved function as `__<name>` with the calling convention from
  `sites.txt` (nothing for `__cdecl` — gcc's i386 default);
* carry `PROBE_DECL(__<name>)` / `PROBE_HIT(__<name>)`, so §9's "was it actually
  called?" check still applies to it;
* declare any PE globals it touches at their absolute VA and `#undef` the alias
  at the end, the same way a generated `.inc` does — the file is `#include`d
  into one big translation unit alongside every other accepted function.

## Current overrides

| Function | Why |
|---|---|
| `sub_434A30` | Intel C++ runtime CPU dispatch init. Built from `__asm { cpuid }` / `__asm { xgetbv }` with the results read back out of `_EAX`/`_ECX`/`_EDX`, and Hex-Rays additionally mis-attributes the XGETBV result to a variable it had already used for the CPUID EDX. Rewritten from its expected results per the classification table in the file. Verified to produce the same level code as the original: `0x20000` on this host, read out of `0x00445B5C` after a run of the un-redirected binary. |
| `exit_402E40` | BMF's "print message N and quit". IDA typed it `void __stdcall exit_402E40(int Code, char ArgList)`; `lea eax, [esp+8]` at `0x00402E44` is a `va_list`, so the donor is `__cdecl exit_402E40(int Code, ...)` — wrong in both halves, and no C signature Hex-Rays could have printed would have been right. The body needs `va_start`, which is why it is an override rather than a fixup; `fixups.txt` carries the corrected definition line (so `sites.txt` records `cdecl`) and restores the arguments at all thirty call sites. Verified against the un-injected binary: same usage screen, same error messages. |
| `sub_436BD0` | Intel cache-descriptor detection (CPUID leaf 2). Same problem: `__asm { cpuid }` plus reads of `_EAX`/`_EBX`/`_ECX`/`_EDX`. Transcribed literally otherwise, including the `> 2` in the third block-count test where every other one is `> 1`. Verified against the un-injected binary: cache size 0, line size 0, level 2 on this host — leaf 2 reports descriptor `0xFF` here, so the walk stops on the first byte. |

## `__usercall` overrides

An override for a `__usercall`/`__userpurge` function supplies only the body,
with the signature `incdec.md` §4.2 expects — an ordinary cdecl function taking
every argument, `extern "C"`, hidden visibility. `extract.py` appends the
generated entry-point thunk, so there is no hand-written assembly to keep in
step with the signature.
