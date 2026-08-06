# Hand-written `.inc` overrides

`extract.py <name>` copies `override/<name>.inc` verbatim into `inc/<name>.inc`
when it exists, instead of generating one from `BMF.c`. Everything downstream —
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
