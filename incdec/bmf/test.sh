#!/usr/bin/env bash
# test.sh — the incdec validation gate (incdec.md §9), specialised to the
# "-S -Q9" round-trip the goal asks for.
#
#   ./test.sh --baseline   regenerate ref.bmf from the un-injected binary
#   ./test.sh              validate the current dummy32.so
#
# Passes when the injected build produces a byte-identical compressed stream
# AND decompresses back to the original image.
set -u
cd "$(dirname "$0")"

FLAGS=${BMF_FLAGS:--S -Q9}
IMG=test.bmp
WORK=run
PE2ELF=../../pe2elf32
BMFEXE=../../exe32/BMF.exe

rm -rf "$WORK"; mkdir -p "$WORK"
cp winapi_shim32.so "$WORK/"
[ -f "$IMG" ] || python3 ../../exe32/mkbmp32.py "$IMG" 320 240 >/dev/null
cp "$IMG" "$WORK/"

if [ "${1:-}" = "--baseline" ]; then
  "$PE2ELF" "$BMFEXE" "$WORK/BMF.elf" >/dev/null || exit 1
  ( cd "$WORK" && ./BMF.elf $FLAGS "$IMG" >/dev/null 2>&1 ) || exit 1
  cp "$WORK/test.bmf" ref.bmf
  echo "baseline: ref.bmf = $(stat -c%s ref.bmf) bytes  (flags: $FLAGS)"
  exit 0
fi

cp dummy32.so "$WORK/" || exit 1
"$PE2ELF" "$BMFEXE" "$WORK/BMF.elf" --inject=dummy32.so >/dev/null || exit 1

(
  cd "$WORK"
  export BMF_PROBE_OUT=probe.txt
  ./BMF.elf $FLAGS "$IMG" >compress.log 2>&1        || { echo "COMPRESS FAILED (rc=$?)"; exit 1; }
  [ -s test.bmf ]                                    || { echo "NO .bmf PRODUCED"; exit 1; }
  cmp -s test.bmf ../ref.bmf                         || { echo "STREAM DIFFERS from ref.bmf"; exit 1; }
  mv "$IMG" orig.bmp
  ./BMF.elf test.bmf >decompress.log 2>&1           || { echo "DECOMPRESS FAILED (rc=$?)"; exit 1; }
  cmp -s orig.bmp "$IMG"                             || { echo "ROUND-TRIP MISMATCH"; exit 1; }
  exit 0
)
rc=$?
if [ $rc -ne 0 ]; then echo "FAIL"; exit 1; fi
echo "PASS"
exit 0
