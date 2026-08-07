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
  # A __usercall/__userpurge function's entry point goes to its thunk, not to
  # the moved body: callers still living in the PE pass arguments in registers,
  # and the body is an ordinary cdecl function.  Everything else is patched
  # straight to the body.
  while read -r va name conv; do
    [ -z "${name:-}" ] && continue
    case "$conv" in
      usercall|userpurge) echo "  patch_jmp((void*)0x${va}, (void*)&__thunk_${name});" ;;
      *)                  echo "  patch_jmp((void*)0x${va}, (void*)&__${name});" ;;
    esac
  done < "$ACCEPTED"
  echo "  patch_iat_slot((void*)IAT_ExitProcess, (void*)&my_ExitProcess);"
  echo "}"
} > dummy32.cpp

# -fvisibility=hidden: the __usercall thunks reach their moved body with a
# plain `call` from inline asm.  With default visibility that symbol is
# preemptible, so the assembler's R_386_PC32 turns into a text relocation
# (DT_TEXTREL) and the injected .so no longer loads.  Hidden visibility binds
# it at static-link time.  Unlike `static` it does not make the function local,
# so gcc cannot give it a private calling convention — which would break the
# patched entry point for every *non*-thunked function.
# -msse2 -mfpmath=sse for the whole translation unit.  gcc's i386 default is
# -mfpmath=387, which evaluates scalar float and double arithmetic with x87's
# 80-bit intermediates; the donor is ICC output that used SSE throughout and
# kept everything at 32 or 64 bits.  (It cannot go in the per-body `target`
# attribute: `fpmath=` there makes gcc consider the options mismatched for the
# always_inline intrinsics and refuse to inline them.)
#
# Deliberately *not* -mincoming-stack-boundary=2, and not
# __attribute__((ms_abi)).  The one place the MS and SysV i386 ABIs really
# differ is that SysV requires esp 16-byte aligned at a call and gcc assumes it
# on entry, while MSVC guarantees only 4 — and patch_jmp sends PE callers
# straight into a moved body.  But BMF is ICC output and does keep esp 16-byte
# aligned, so the assumption holds: measured, telling gcc otherwise makes it
# realign and *breaks* a round-trip that is green without it.  ms_abi would not
# have helped either way — on i386 it is very nearly a no-op (verified: same
# code, same alignment assumptions), unlike x86-64 where it selects a different
# register convention entirely.  The per-function conventions that do matter
# here — stdcall / fastcall / thiscall — are on the individual bodies, §4.
g++ ${CXXEXTRA:-} ${CXXABI:--msse2 -mfpmath=sse} -O2 -fPIC -shared -m32 -std=c++17 -fpermissive \
    ${CXXALIAS:--fno-strict-aliasing} \
    -Wno-narrowing -Wno-write-strings -Wno-unused-variable \
    -Wno-unused-but-set-variable -Wno-parentheses \
    -o "$OUT" dummy32.cpp \
    -Wl,-soname,"$OUT" -Wl,-Ttext-segment=0x30000000 -Wl,-z,max-page-size=0x1000
