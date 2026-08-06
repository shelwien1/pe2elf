#!/usr/bin/env bash
# test.sh — the incdec validation gate (incdec.md §9), specialised to a
# "-S -Q9" round-trip over both test images.
#
#   ./test.sh --baseline   regenerate the reference .bmf streams
#   ./test.sh              validate the current dummy32.so
#
# Two images, because they exercise different code: the 24bpp one drives the
# truecolour path, the 1bpp one drives the bilevel path and is the only thing
# that reaches sub_4148F0.
#
# Each image must (a) compress to a byte-identical stream and (b) decompress
# back to identical *pixel* data.  Only the pixels: BMF does not preserve
# every BMP header field — it drops biXPelsPerMeter/biYPelsPerMeter on 24bpp
# and biClrUsed/biClrImportant on 1bpp — and the un-injected binary loses
# them too, so requiring the whole file to match would fail against BMF
# itself.  Comparison therefore starts at each file's own bfOffBits.
set -u
cd "$(dirname "$0")"

FLAGS=${BMF_FLAGS:--S -Q9}
IMAGES=${BMF_IMAGES:-"test.bmp f05_200.bmp"}
WORK=run
PE2ELF=../../pe2elf32
BMFEXE=../../exe32/BMF.exe

# bfOffBits: where pixel data starts in a BMP.
pixoff() { od -A n -t u4 -j 10 -N 4 "$1" | tr -d ' '; }

[ -f test.bmp ] || python3 ../../exe32/mkbmp32.py test.bmp 320 240 >/dev/null

rm -rf "$WORK"; mkdir -p "$WORK"
cp winapi_shim32.so "$WORK/"
for img in $IMAGES; do
  [ -f "$img" ] || { echo "missing test image: $img"; exit 1; }
  cp "$img" "$WORK/"
done

if [ "${1:-}" = "--baseline" ]; then
  "$PE2ELF" "$BMFEXE" "$WORK/BMF.elf" >/dev/null || exit 1
  for img in $IMAGES; do
    st="${img%.bmp}"
    ( cd "$WORK" && timeout 120 ./BMF.elf $FLAGS "$img" >/dev/null 2>&1 ) || exit 1
    cp "$WORK/$st.bmf" "ref_$st.bmf"
    echo "baseline: ref_$st.bmf = $(stat -c%s "ref_$st.bmf") bytes  (flags: $FLAGS)"
  done
  exit 0
fi

cp dummy32.so "$WORK/" || exit 1
"$PE2ELF" "$BMFEXE" "$WORK/BMF.elf" --inject=dummy32.so >/dev/null || exit 1

for img in $IMAGES; do
  st="${img%.bmp}"
  off=$(pixoff "$img")
  (
    cd "$WORK"
    export BMF_PROBE_OUT=probe.txt
    timeout 60 ./BMF.elf $FLAGS "$img" >"$st.compress.log" 2>&1
    rc=$?; [ $rc -eq 124 ] && { echo "$st: COMPRESS TIMED OUT"; exit 1; }
    [ $rc -ne 0 ] && { echo "$st: COMPRESS FAILED (rc=$rc)"; exit 1; }
    [ -s "$st.bmf" ]                     || { echo "$st: NO .bmf PRODUCED"; exit 1; }
    cmp -s "$st.bmf" "../ref_$st.bmf"    || { echo "$st: STREAM DIFFERS from reference"; exit 1; }
    mv "$img" "orig_$st.bmp"
    timeout 60 ./BMF.elf "$st.bmf" >"$st.decompress.log" 2>&1
    rc=$?; [ $rc -eq 124 ] && { echo "$st: DECOMPRESS TIMED OUT"; exit 1; }
    [ $rc -ne 0 ] && { echo "$st: DECOMPRESS FAILED (rc=$rc)"; exit 1; }
    cmp -s -i "$off" "orig_$st.bmp" "$img" || { echo "$st: PIXEL MISMATCH"; exit 1; }
    exit 0
  ) || { echo "FAIL"; exit 1; }
done
echo "PASS"
exit 0
