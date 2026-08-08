#!/usr/bin/env bash
# test.sh — the incdec validation gate (incdec.md §9): a compress/decompress
# round-trip over the whole test image set, in every compression mode.
#
#   ./test.sh --baseline   rebuild the test images and the reference streams
#   ./test.sh              validate the current dummy32.so
#
# Five pixel formats, because BMF takes a different path through the filters
# and the context model for each, and a redirect that is wrong for one of them
# can be perfectly correct for the others: 1bpp bilevel, 8bpp grayscale, 8bpp
# palette, 24bpp RGB, 32bpp RGBA — all with the old-style 40-byte
# BITMAPINFOHEADER, which is what BMF writes back.  mkbmps.py generates them
# deterministically.  f05_200.bmp, a real 1728x2339 scan, is included as a
# sixth when it is present, and DLRAW.bmp, a 4bpp image, as a seventh.
#
# Three *modes*, because the switch that looked like a speed/ratio knob selects
# a different compressor.  `-S` ("use Slow, but efficient compression") is not
# the same code with more effort spent: it is roughly twenty functions that the
# default path does not call at all.  Gating on `-S -Q9` alone left 53 of the
# 143 accepted functions never once executed, and the whole default mode
# broken — it crashed on every image, in both directions, and nothing said so.
# A mode is a dimension of the corpus, exactly like a pixel format.
#
# --baseline puts each image through one round-trip of the *un-injected*
# binary first and keeps the result.  BMF does not preserve every BMP header
# field — it zeroes biClrUsed and biClrImportant — so a freshly generated image
# is not a fixed point, and a whole-file comparison against it would fail
# against BMF itself.  After one round-trip it is: verified for all images,
# a second round-trip is byte-identical end to end.  That is what lets the gate
# below be a plain `cmp` with no excluded ranges.
#
# The gate is two conditions per image and mode:
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

WORK=run
PE2ELF=../../pe2elf32
BMFEXE=../../exe32/BMF.exe

# tag:flags.  The tag names the reference stream, so a mode can be added here
# and picked up by --baseline without touching anything else.
# Flags are comma-separated inside a spec, since the specs are whitespace-
# separated.  `-Q9` is worth its own entry: it changes nothing under `-S` (the
# slow path picks filters exhaustively) but it does change the default path,
# which is exactly the half that was never tested.
DEFAULT_MODES="default: Q9:-Q9 S:-S SQ9:-S,-Q9"
MODES=${BMF_MODES:-$DEFAULT_MODES}

DEFAULT_IMAGES="t1.bmp t8g.bmp t8p.bmp t24.bmp t32.bmp"
for extra in f05_200.bmp DLRAW.bmp; do
  [ -f "$extra" ] && DEFAULT_IMAGES="$DEFAULT_IMAGES $extra"
done
IMAGES=${BMF_IMAGES:-$DEFAULT_IMAGES}

if [ "${1:-}" = "--baseline" ]; then
  rm -rf "$WORK"; mkdir -p "$WORK"
  cp winapi_shim32.so "$WORK/"
  "$PE2ELF" "$BMFEXE" "$WORK/BMF.elf" >/dev/null || exit 1
  python3 mkbmps.py "$WORK" >/dev/null || exit 1
  for extra in f05_200.bmp DLRAW.bmp; do
    [ -f "$extra" ] && cp "$extra" "$WORK/"
  done
  rc=0
  for img in $IMAGES; do
    st="${img%.bmp}"
    # Settling is a property of the image, not of the mode: any lossless
    # round-trip normalises the same header fields.  Use the default mode.
    (
      cd "$WORK"
      timeout 300 ./BMF.elf "$img" >/dev/null 2>&1 || exit 1
      rm -f "$img"
      timeout 300 ./BMF.elf "$st.bmf" >/dev/null 2>&1 || exit 1
      cp "$img" "settled_$st.bmp"
      rm -f "$st.bmf"
      timeout 300 ./BMF.elf "$img" >/dev/null 2>&1 || exit 1
      rm -f "$img"
      timeout 300 ./BMF.elf "$st.bmf" >/dev/null 2>&1 || exit 1
      cmp -s "settled_$st.bmp" "$img"
    ) || { echo "baseline: $st does not settle after one round-trip"; rc=1; continue; }
    cp "$WORK/$img" "$img"
    line="baseline: $img settled"
    for spec in $MODES; do
      tag="${spec%%:*}"; flags="$(echo "${spec#*:}" | tr ',' ' ')"
      ( cd "$WORK" && rm -f "$st.bmf" && timeout 300 ./BMF.elf $flags "$img" >/dev/null 2>&1 ) \
        || { echo "baseline: $st failed in mode $tag"; rc=1; continue; }
      cp "$WORK/$st.bmf" "ref_${tag}_$st.bmf"
      line="$line, $tag=$(stat -c%s "ref_${tag}_$st.bmf")"
    done
    echo "$line"
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

for spec in $MODES; do
  tag="${spec%%:*}"; flags="$(echo "${spec#*:}" | tr ',' ' ')"
  for img in $IMAGES; do
    st="${img%.bmp}"
    ref="ref_${tag}_$st.bmf"
    [ -f "$ref" ] || { echo "$st/$tag: no reference (run ./test.sh --baseline)"; exit 1; }
    refsz=$(stat -c%s "$ref")
    (
      cd "$WORK"
      export BMF_PROBE_OUT=probe.txt
      # in_$st.bmf, not $st.bmf: the input is copied under a distinct name so
      # the original survives for the losslessness compare, and BMF derives the
      # archive name from it.  Removing the wrong one leaves the previous
      # mode's archive in place, and BMF *appends* to an existing one — which
      # shows up as a stream exactly twice the reference's size.
      rm -f "in_$st.bmf"; cp "$img" "in_$st.bmp"
      timeout 300 ./BMF.elf $flags "in_$st.bmp" >"$st.$tag.compress.log" 2>&1
      rc=$?; [ $rc -eq 124 ] && { echo "$st/$tag: COMPRESS TIMED OUT"; exit 1; }
      [ $rc -ne 0 ] && { echo "$st/$tag: COMPRESS FAILED (rc=$rc)"; exit 1; }
      [ -s "in_$st.bmf" ] || { echo "$st/$tag: NO .bmf PRODUCED"; exit 1; }
      sz=$(stat -c%s "in_$st.bmf")
      [ "$sz" -gt "$refsz" ] && { echo "$st/$tag: LARGER THAN REFERENCE ($sz > $refsz)"; exit 1; }
      cmp -s "in_$st.bmf" "../$ref" \
        || echo "$st/$tag: stream differs from reference ($sz vs $refsz bytes)" >&2
      rm -f "in_$st.bmp"
      timeout 300 ./BMF.elf "in_$st.bmf" >"$st.$tag.decompress.log" 2>&1
      rc=$?; [ $rc -eq 124 ] && { echo "$st/$tag: DECOMPRESS TIMED OUT"; exit 1; }
      [ $rc -ne 0 ] && { echo "$st/$tag: DECOMPRESS FAILED (rc=$rc)"; exit 1; }
      cmp -s "../$img" "in_$st.bmp" || { echo "$st/$tag: NOT LOSSLESS"; exit 1; }
      exit 0
    ) || { echo "FAIL"; exit 1; }
  done
done
echo "PASS"
exit 0
