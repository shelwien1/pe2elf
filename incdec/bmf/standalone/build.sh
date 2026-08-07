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
#   bmfdata.S     BMF's .rdata/.data/.trace, at their original addresses
#   main.cpp      a real main(), plus sub_402E30
#
# The data image is the part that cannot be dropped.  The bodies reach their
# globals by absolute address — `*(int *)0x00441040` — because that is what the
# decompilation says (see mkdata.py); so the linker is told to put those 64 KB
# exactly where BMF.exe had them and the bodies do not have to change at all.
set -eu
cd "$(dirname "$0")"

ACCEPTED=${ACCEPTED:-../accepted.txt}
OUT=${OUT:-bmf}

[ -f bmfdata.S ] || python3 mkdata.py
. ./bmfdata.mk

{
  echo "#define BMF_STANDALONE 1"
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
#
# -no-pie and --section-start put .bmfdata at 0x00438000.  It is far below the
# i386 default text base, so it lands in its own PT_LOAD; nothing else in the
# image wants that range.  -Wl,-z,noexecstack because the file has no
# executable-stack marking of its own once the naked asm is gone.
g++ ${CXXEXTRA:-} ${CXXABI:--msse2 -mfpmath=sse} -O2 -m32 -std=c++17 -fpermissive \
    ${CXXALIAS:--fno-strict-aliasing} \
    -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 \
    -Wno-narrowing -Wno-write-strings -Wno-unused-variable \
    -Wno-unused-but-set-variable -Wno-parentheses \
    -no-pie -o "$OUT" bmf_standalone.cpp bmfdata.S \
    -Wl,--section-start=.bmfdata="$BMFDATA_START" -Wl,-z,noexecstack -lm
