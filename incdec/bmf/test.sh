#!/usr/bin/env bash
# test.sh — the incdec validation gate (incdec.md §9), specialised to a
# "-S -Q9" compress/decompress round-trip over the whole test image set.
#
#   ./test.sh --baseline   rebuild the test images and the reference streams
#   ./test.sh              validate the current dummy32.so
#
# Five pixel formats, because BMF takes a different path through the filters
# and the context model for each, and a redirect that is wrong for one of them
# can be perfectly correct for the others: 1bpp bilevel, 8bpp grayscale, 8bpp
# palette, 24bpp RGB, 32bpp RGBA — all with the old-style 40-byte
# BITMAPINFOHEADER, which is what BMF writes back.  mkbmps.py generates them
# deterministically.  f05_200.bmp, a real 1728x2339 1bpp scan, is included as a
# sixth when it is present.
#
# --baseline puts each image through one round-trip of the *un-injected*
# binary first and keeps the result.  BMF does not preserve every BMP header
# field — it zeroes biClrUsed and biClrImportant — so a freshly generated image
# is not a fixed point, and a whole-file comparison against it would fail
# against BMF itself.  After one round-trip it is: verified for all six images,
# a second round-trip is byte-identical end to end.  That is what lets the gate
# below be a plain `cmp` with no excluded ranges.
#
# The gate is two conditions per image:
#
#   1. the round-trip is lossless — decompressed output byte-identical to the
#      input, whole file;
#   2. the compressed stream is no larger than the reference.
#
# Byte-identity of the *stream* is reported but does not fail the run: the
# goal is a lossless codec that compresses no worse than BMF, not one that
# reproduces BMF's output bit for bit.  A run whose streams all match prints
# nothing extra; one that diverges says where, so it stays visible.
set -u
cd "$(dirname "$0")"

FLAGS=${BMF_FLAGS:--S -Q9}
WORK=run
PE2ELF=../../pe2elf32
BMFEXE=../../exe32/BMF.exe

DEFAULT_IMAGES="t1.bmp t8g.bmp t8p.bmp t24.bmp t32.bmp"
[ -f f05_200.bmp ] && DEFAULT_IMAGES="$DEFAULT_IMAGES f05_200.bmp"
IMAGES=${BMF_IMAGES:-$DEFAULT_IMAGES}

if [ "${1:-}" = "--baseline" ]; then
  rm -rf "$WORK"; mkdir -p "$WORK"
  cp winapi_shim32.so "$WORK/"
  "$PE2ELF" "$BMFEXE" "$WORK/BMF.elf" >/dev/null || exit 1
  python3 mkbmps.py "$WORK" >/dev/null || exit 1
  [ -f f05_200.bmp ] && cp f05_200.bmp "$WORK/"
  rc=0
  for img in $IMAGES; do
    st="${img%.bmp}"
    (
      cd "$WORK"
      timeout 120 ./BMF.elf $FLAGS "$img" >/dev/null 2>&1 || exit 1
      rm -f "$img"
      timeout 120 ./BMF.elf "$st.bmf"    >/dev/null 2>&1 || exit 1
      cp "$img" "settled_$st.bmp"
      # Confirm the settled image really is a fixed point before adopting it.
      rm -f "$st.bmf"
      timeout 120 ./BMF.elf $FLAGS "$img" >/dev/null 2>&1 || exit 1
      rm -f "$img"
      timeout 120 ./BMF.elf "$st.bmf"    >/dev/null 2>&1 || exit 1
      cmp -s "settled_$st.bmp" "$img"
    ) || { echo "baseline: $st does not settle after one round-trip"; rc=1; continue; }
    cp "$WORK/$img" "$img"
    cp "$WORK/$st.bmf" "ref_$st.bmf"
    echo "baseline: $img settled, ref_$st.bmf = $(stat -c%s "ref_$st.bmf") bytes  (flags: $FLAGS)"
  done
  exit $rc
fi

rm -rf "$WORK"; mkdir -p "$WORK"
cp winapi_shim32.so "$WORK/"
for img in $IMAGES; do
  [ -f "$img" ] || { echo "missing test image: $img (run ./test.sh --baseline)"; exit 1; }
  cp "$img" "$WORK/"
done
cp dummy32.so "$WORK/" || exit 1
"$PE2ELF" "$BMFEXE" "$WORK/BMF.elf" --inject=dummy32.so >/dev/null || exit 1

bigger=0
for img in $IMAGES; do
  st="${img%.bmp}"
  [ -f "ref_$st.bmf" ] || { echo "$st: no reference (run ./test.sh --baseline)"; exit 1; }
  refsz=$(stat -c%s "ref_$st.bmf")
  (
    cd "$WORK"
    export BMF_PROBE_OUT=probe.txt
    timeout 60 ./BMF.elf $FLAGS "$img" >"$st.compress.log" 2>&1
    rc=$?; [ $rc -eq 124 ] && { echo "$st: COMPRESS TIMED OUT"; exit 1; }
    [ $rc -ne 0 ] && { echo "$st: COMPRESS FAILED (rc=$rc)"; exit 1; }
    [ -s "$st.bmf" ] || { echo "$st: NO .bmf PRODUCED"; exit 1; }
    sz=$(stat -c%s "$st.bmf")
    [ "$sz" -gt "$refsz" ] && { echo "$st: LARGER THAN REFERENCE ($sz > $refsz)"; exit 1; }
    cmp -s "$st.bmf" "../ref_$st.bmf" || echo "$st: stream differs from reference ($sz vs $refsz bytes)" >&2
    mv "$img" "orig_$st.bmp"
    timeout 60 ./BMF.elf "$st.bmf" >"$st.decompress.log" 2>&1
    rc=$?; [ $rc -eq 124 ] && { echo "$st: DECOMPRESS TIMED OUT"; exit 1; }
    [ $rc -ne 0 ] && { echo "$st: DECOMPRESS FAILED (rc=$rc)"; exit 1; }
    cmp -s "orig_$st.bmp" "$img" || { echo "$st: NOT LOSSLESS"; exit 1; }
    exit 0
  ) || { echo "FAIL"; exit 1; }
done
echo "PASS"
exit 0
