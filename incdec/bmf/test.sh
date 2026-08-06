#!/usr/bin/env bash
# test.sh — the incdec validation gate (incdec.md §9), specialised to a
# "-S -Q9" round-trip over the whole test image set.
#
#   ./test.sh --baseline   regenerate the reference .bmf streams
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
# Each image must (a) compress to a byte-identical stream and (b) decompress
# back to an identical file.  Both halves matter: comparing only the round-trip
# would accept a build that silently encodes differently but still decodes.
#
# "Identical" excludes bytes 38..53 of the BITMAPINFOHEADER —
# biXPelsPerMeter, biYPelsPerMeter, biClrUsed, biClrImportant — which BMF does
# not store and writes back as zero.  The un-injected binary loses them too, so
# requiring the whole file to match would fail against BMF itself.  Everything
# else is compared, *including the palette*: verified against the un-injected
# binary, all 256 entries survive a round-trip on both 8bpp images, so skipping
# to bfOffBits would leave 1 KB of each unchecked.
set -u
cd "$(dirname "$0")"

FLAGS=${BMF_FLAGS:--S -Q9}
WORK=run
PE2ELF=../../pe2elf32
BMFEXE=../../exe32/BMF.exe

[ -f t24.bmp ] || python3 mkbmps.py >/dev/null
DEFAULT_IMAGES="t1.bmp t8g.bmp t8p.bmp t24.bmp t32.bmp"
[ -f f05_200.bmp ] && DEFAULT_IMAGES="$DEFAULT_IMAGES f05_200.bmp"
IMAGES=${BMF_IMAGES:-$DEFAULT_IMAGES}

# Everything but the four header fields BMF drops.
same() { cmp -s -n 38 "$1" "$2" && cmp -s -i 54 "$1" "$2"; }

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
  [ -f "ref_$st.bmf" ] || { echo "$st: no reference (run ./test.sh --baseline)"; exit 1; }
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
    cmp -s -n 38 "orig_$st.bmp" "$img" && cmp -s -i 54 "orig_$st.bmp" "$img" \
      || { echo "$st: IMAGE MISMATCH"; exit 1; }
    exit 0
  ) || { echo "FAIL"; exit 1; }
done
echo "PASS"
exit 0
