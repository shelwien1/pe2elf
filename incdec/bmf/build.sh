#!/usr/bin/env bash
# build.sh — assemble dummy32.cpp from the accepted .inc set and build it.
#
# accepted.txt drives everything: one "<VA> <name> <conv>" line per function
# that has been moved into dummy32.so, in include order (callees first).
set -eu
cd "$(dirname "$0")"

ACCEPTED=${ACCEPTED:-accepted.txt}
OUT=${OUT:-dummy32.so}

{
  cat dummy32_head.cpp
  echo
  echo "// ---- moved function bodies (callees before callers) ----"
  while read -r va name conv; do
    [ -z "${name:-}" ] && continue
    echo "#include \"inc/${name}.inc\""
  done < "$ACCEPTED"
  echo
  echo "__attribute__((constructor)) static void dummy_init() {"
  while read -r va name conv; do
    [ -z "${name:-}" ] && continue
    echo "  patch_jmp((void*)0x${va}, (void*)&__${name});"
  done < "$ACCEPTED"
  echo "  patch_iat_slot((void*)IAT_ExitProcess, (void*)&my_ExitProcess);"
  echo "}"
} > dummy32.cpp

g++ -O2 -fPIC -shared -m32 -std=c++17 -fpermissive \
    -Wno-narrowing -Wno-write-strings -Wno-unused-variable \
    -Wno-unused-but-set-variable -Wno-parentheses \
    -o "$OUT" dummy32.cpp \
    -Wl,-soname,"$OUT" -Wl,-Ttext-segment=0x30000000 -Wl,-z,max-page-size=0x1000
