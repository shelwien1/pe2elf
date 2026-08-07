#!/usr/bin/env bash
# build-mingw.sh — Windows build, cross-compiled.
#
# Same flags as build.sh (see there for why each one is required), plus:
#
#   -static        so the .exe carries libgcc/libstdc++ rather than needing
#                  libgcc_s_dw2-1.dll next to it.  Without it Windows refuses
#                  to start the image and prints nothing.
#   no -m32        i686-w64-mingw32 is already 32-bit; passing -m32 as well is
#                  harmless but redundant.
#
# The runtime here is msvcrt and the real kernel32 — which is where BMF's code
# came from in the first place, so crt.cpp's Windows half is ten import
# declarations and no implementation.
set -eu
cd "$(dirname "$0")"
CXX=${CXX:-i686-w64-mingw32-g++}
command -v "$CXX" >/dev/null || {
  echo "$CXX not found (Debian/Ubuntu: apt install g++-mingw-w64-i686)" >&2
  exit 1
}
exec "$CXX" ${CXXFLAGS:--O2} -msse2 -mfpmath=sse -std=c++17 -fpermissive \
    -fno-strict-aliasing -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 \
    -Wno-narrowing -Wno-write-strings -Wno-unused-variable \
    -Wno-unused-but-set-variable -Wno-parentheses \
    -static -o "${OUT:-bmf.exe}" bmf.cpp
