# BMFC — BMF 2.01, decompiled, as a program you can build

BMF is a lossless image compressor by Dmitry Shkarin, published in 2009 as a
32-bit Windows binary with no source. This is that binary recovered as C++:
143 functions decompiled with Hex-Rays and corrected against the disassembly
until the output matched, plus a runtime written from scratch to replace the
one that was statically linked into the executable.

It builds and runs on Linux and on Windows, and on every test image it produces
**compressed streams byte-identical to the original's**. Not merely
"compresses about as well" — the same bytes.

```sh
./build.sh                 # -> bmf      (32-bit ELF)
./build-mingw.sh           # -> bmf.exe  (Win32, cross-compiled)
./test.sh ./bmf            # round-trip gate
./test.sh --wine ./bmf.exe # same, Windows binary under wine
```

or `make`, `make bmf.exe`, `make test`, `make test-wine`.

Usage is BMF's own:

```sh
./bmf -S -Q9 image.bmp     # compress -> image.bmf
./bmf image.bmf            # decompress
./bmf                      # the switch list
```

## What is here

| Path | |
|---|---|
| `bmf.cpp` | The whole program as one translation unit — it includes everything below in order. |
| `inc/*.inc` | The 143 decompiled function bodies, one per file, byte for byte as the extractor emitted them. This is the recovered program. |
| `bmfhead.h` | The vocabulary those bodies are written in: Hex-Rays' type conventions, MSVC's `__m128` unions mapped onto GCC's vector types, the Win32 structures the file handling names. |
| `bmfdefs.h` | Hex-Rays' own `defs.h`, verbatim — `LOBYTE`, `BYTEn`, `__ROLn__`, `qmemcpy` and the rest, with the semantics the decompiler assumed. |
| `blob.inc` | BMF's data segment: 64 KB of `.rdata`/`.data`/`.trace` lifted out of the original executable. |
| `crt.cpp` | The C runtime and the ten kernel32 imports. |
| `main.cpp` | The entry point, and the two things MSVC's startup did that nothing else does. |

One translation unit, because the bodies are not independent: they share
globals by address, several are entered through calling conventions that only
exist within a file (`thiscall`, `fastcall`), and the include order is
callees-before-callers so no forward declarations are needed.

Everything except `bmfhead.h` is copied unmodified from the working tree in
[`../incdec/bmf`](../incdec/bmf), by `../incdec/bmf/standalone/mkbmfc.py`.
That tree is where the decompilation happened and is the place to change
anything; re-run the generator afterwards.

## The two things that are not decompiled

**The data.** BMF reaches its globals by absolute address — the decompilation
says `*(int *)0x00441040`, and the same address is an `int` to one function and
a `char[]` to the next, so turning 845 of them into named objects is a much
larger job than it sounds. Instead the original's data segment is carried
whole, as `blob1` in `blob.inc`, and each global is a reference into it at its
original offset:

```cpp
static t_main_bmp_& __main_bmp_ = *(t_main_bmp_*)(blob1 + 0x00441040 - BMF_BLOB_BASE);
```

The array can live anywhere — the absolute pointers *inside* the data are
rebased once at startup, so the Linux binary is an ordinary PIE.

**The runtime.** BMF was linked against the MSVC CRT and the Intel C++ runtime,
both statically, so a third of the original image is somebody else's code.
None of it is decompiled. `crt.cpp` supplies what the bodies call:

* 32 CRT entries — `fopen`, `fread`, `printf`, `_access`, `_filelength`, … —
  which are the host's on both targets.
* The ten kernel32 imports. On Windows they are the real ones and that half of
  the file is ten declarations. On POSIX they are written out against
  `open`/`opendir`/`futimens`; about 150 lines.
* `operator new`/`delete` as `malloc`/`free` — MSVC's return null on failure
  and BMF tests for that, where C++'s would throw.
* Intel's `memcpy`/`memset` dispatchers, which are `memcpy` and `memset`.
* `__libm_sse2_log` and `__svml_log2`, which are `log` — despite the name, the
  Intel routine returns the *natural* log, which is why every call site
  multiplies by 1/ln 2. Substituting glibc's changes nothing observable: the
  streams stay byte-identical.

`main.cpp` adds what MSVC's startup used to do: publish `argv` where
`sub_429DB0` reads it, and run BMF's one C++ static initialiser. Skipping the
latter does not crash — it leaves the filter tables full of zeroes and costs
244 bytes on 8bpp images, which is the kind of bug this project spent a while
learning to find.

## Building

32-bit only. The decompilation casts pointers to `int` throughout, because the
original does.

The compiler flags in the build scripts are not stylistic. `-msse2
-mfpmath=sse` because the donor is Intel C++ output that kept `float` and
`double` at 32 and 64 bits, where gcc's i386 default would evaluate them with
x87's 80-bit intermediates and change the arithmetic. `-fno-strict-aliasing`
because the decompiler reads the same storage through several types.
`-fpermissive` because it also converts between pointer types without casts.
The Windows build additionally needs `-static`, or the `.exe` will not start
without `libgcc_s_dw2-1.dll` beside it.

Requirements: `g++` with 32-bit support (`gcc-multilib` / `g++-multilib`) for
the native build; `g++-mingw-w64-i686` for the Windows one; `wine` and `wine32`
to run that under Linux.

## The gate

`test.sh` compresses each test image with `-S -Q9`, decompresses it, and
requires the result to be byte-identical to the input over the whole file. It
also compares the compressed stream against the reference the original BMF.exe
produced, which is the sharper check and the one that says this is the same
program rather than merely a working one.

Six images: 1bpp bilevel, 8bpp grayscale, 8bpp palette, 24bpp RGB, 32bpp RGBA,
and a real 1728×2339 scan — because BMF takes a different path through the
filters and the context model for each, and a mistake that is fatal for one can
be invisible in the others.

The corpus lives in `../incdec/bmf` rather than here, since it is a development
artifact rather than part of the program; `BMF_TESTDIR` points elsewhere.

## Provenance

BMF is Dmitry Shkarin's work. This directory is a recovery of it, not a
reimplementation: the algorithms, the constants and the file format are the
original's, and the bodies in `inc/` are machine translations of the shipped
binary rather than anything written here. The method — moving one function at a
time out of a running copy of the original, with a compress/decompress gate on
every step — is written up in [`../incdec/incdec.md`](../incdec/incdec.md),
and how it went for this binary in
[`../incdec/bmf/README.md`](../incdec/bmf/README.md).
