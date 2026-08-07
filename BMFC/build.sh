#!/usr/bin/env bash
# build.sh — native build (32-bit ELF).
#
# BMF is 32-bit i386 code and cannot be built any other way: the decompilation
# casts pointers to int throughout, which is what the original does.
#
# -msse2 -mfpmath=sse because the donor is Intel C++ output that kept float and
# double at 32 and 64 bits, where gcc's i386 default (-mfpmath=387) would
# evaluate them with x87's 80-bit intermediates and change the arithmetic.
# -fno-strict-aliasing because the decompiler reads the same storage through
# several types.  -fpermissive because it also converts between pointer types
# without casts.  None of these is optional.
set -eu
cd "$(dirname "$0")"
exec g++ ${CXXFLAGS:--O2} -m32 -msse2 -mfpmath=sse -std=c++17 -fpermissive \
    -fno-strict-aliasing -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 \
    -Wno-narrowing -Wno-write-strings -Wno-unused-variable \
    -Wno-unused-but-set-variable -Wno-parentheses \
    -o "${OUT:-bmf}" bmf.cpp -Wl,-z,noexecstack -lm
