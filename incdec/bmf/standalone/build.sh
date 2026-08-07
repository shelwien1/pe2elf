#!/usr/bin/env bash
# build.sh — assemble and link the standalone BMF: the same moved bodies as
# dummy32.so, but with no PE anywhere in the picture.
#
# The hybrid build injects dummy32.so into the running BMF.exe and redirects
# each moved entry point with a jmp (../build.sh).  This one links the bodies
# into an ordinary ELF executable.  Three things replace what the PE used to
# supply:
#
#   crt.cpp       the MSVC CRT and the ten kernel32 imports, on POSIX
#   blob.inc      BMF's .rdata/.data/.trace, as one array
#   main.cpp      a real main(), plus sub_402E30
#
# The data is the part that cannot be dropped: the bodies reach their globals
# at the offsets the decompilation gives them, as references into `blob1` (see
# mkdata.py).  It goes in first, so the array is defined before the head and
# the bodies that name it.  Where the linker puts it does not matter — the
# absolute pointers inside it are rebased at startup — so this needs no
# --section-start and no fixed load address.
set -eu
cd "$(dirname "$0")"

ACCEPTED=${ACCEPTED:-../accepted.txt}
OUT=${OUT:-bmf}

[ -f blob.inc ] || python3 mkdata.py

{
  echo "#define BMF_STANDALONE 1"
  cat blob.inc
  echo
  sed 's#"defs.h"#"../defs.h"#' ../dummy32_head.cpp
  echo
  cat crt.cpp
  echo
  echo "// ---- moved function bodies (callees before callers) ----"
  while read -r va name conv; do
    [ -z "${name:-}" ] && continue
    echo "#include \"../inc/${name}.inc\""
  done < "$ACCEPTED"
  echo
  cat main.cpp
} > bmf_standalone.cpp

# Same code-generation flags as the hybrid, for the same reasons (../build.sh):
# -msse2 -mfpmath=sse because the donor is ICC output that kept float and
# double at 32 and 64 bits, and -fno-strict-aliasing because Hex-Rays reads the
# same storage through several types.  Dropped here: -fPIC and -shared, which
# were for an injected .so; -fvisibility=hidden, which was for the thunks'
# text relocations, and the thunks are gone.
# No link-time placement either: an ordinary executable at whatever address
# the toolchain defaults to, because nothing depends on the data landing at
# 0x00438000 any more.  -Wl,-z,noexecstack because the file has no
# executable-stack marking of its own once the naked asm is gone.
g++ ${CXXEXTRA:-} ${CXXABI:--msse2 -mfpmath=sse} -O2 -m32 -std=c++17 -fpermissive \
    ${CXXALIAS:--fno-strict-aliasing} \
    -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 \
    -Wno-narrowing -Wno-write-strings -Wno-unused-variable \
    -Wno-unused-but-set-variable -Wno-parentheses \
    -o "$OUT" bmf_standalone.cpp -Wl,-z,noexecstack -lm
