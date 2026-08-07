#!/usr/bin/env bash
# test.sh — the round-trip gate, against a native binary or a Windows one.
#
#   ./test.sh ./bmf                 native
#   ./test.sh --wine ./bmf.exe      under wine
#
# For each image: compress with -S -Q9, decompress, and require the result to
# be byte-identical to the input, whole file.  The compressed stream is also
# compared against the reference the original BMF.exe produced — that is the
# real check, and it passes: this program's output is bit-for-bit the donor's.
#
# The corpus lives in the incdec working tree, since it is a development
# artifact rather than part of the program.  Point BMF_TESTDIR elsewhere if you
# have moved it.
set -u
cd "$(dirname "$0")"

TESTDIR=${BMF_TESTDIR:-../incdec/bmf}
WORK=run

RUN=""
if [ "${1:-}" = "--wine" ]; then
  shift
  RUN=${WINE:-$(command -v wine || echo /usr/lib/wine/wine)}
  [ -x "$RUN" ] || { echo "no wine (Debian/Ubuntu: apt install wine wine32)"; exit 1; }
  export WINEDEBUG=${WINEDEBUG:--all}
  : "${WINEPREFIX:=$PWD/.wine}"
  export WINEPREFIX
fi
BIN=${1:-./bmf}
[ -x "$BIN" ] || { echo "no $BIN (run ./build.sh or ./build-mingw.sh)"; exit 1; }

IMAGES=${BMF_IMAGES:-"t1.bmp t8g.bmp t8p.bmp t24.bmp t32.bmp"}
for extra in f05_200.bmp DLRAW.bmp; do
  [ -f "$TESTDIR/$extra" ] && IMAGES="$IMAGES $extra"
done

# tag:flags, flags comma-separated.  `-S` is not a speed knob: it selects a
# different compressor, about twenty functions the default path never calls.
# Testing one mode leaves the other untested, which is how a whole broken mode
# went unnoticed here for a long time.
MODES=${BMF_MODES:-"default: Q9:-Q9 S:-S SQ9:-S,-Q9"}

rm -rf "$WORK"; mkdir -p "$WORK"
cp "$BIN" "$WORK/" || exit 1
BIN="./$(basename "$BIN")"
for img in $IMAGES; do
  [ -f "$TESTDIR/$img" ] || { echo "missing test image: $TESTDIR/$img"; exit 1; }
  cp "$TESTDIR/$img" "$WORK/"
done

for spec in $MODES; do
  tag="${spec%%:*}"; flags="$(echo "${spec#*:}" | tr ',' ' ')"
  for img in $IMAGES; do
    st="${img%.bmp}"
    ref="$TESTDIR/ref_${tag}_$st.bmf"
    [ -f "$ref" ] || { echo "$st/$tag: no reference stream at $ref"; exit 1; }
    (
      cd "$WORK"
      rm -f "in_$st.bmf"; cp "$img" "in_$st.bmp"
      timeout 300 $RUN "$BIN" $flags "in_$st.bmp" >"$st.$tag.compress.log" 2>&1
      rc=$?; [ $rc -ne 0 ] && { echo "$st/$tag: COMPRESS FAILED (rc=$rc)"; cat "$st.$tag.compress.log"; exit 1; }
      [ -s "in_$st.bmf" ] || { echo "$st/$tag: NO .bmf PRODUCED"; exit 1; }
      cmp -s "in_$st.bmf" "../$ref" \
        || echo "$st/$tag: stream differs from the original's ($(stat -c%s "in_$st.bmf") vs $(stat -c%s "../$ref"))" >&2
      rm -f "in_$st.bmp"
      timeout 300 $RUN "$BIN" "in_$st.bmf" >"$st.$tag.decompress.log" 2>&1
      rc=$?; [ $rc -ne 0 ] && { echo "$st/$tag: DECOMPRESS FAILED (rc=$rc)"; cat "$st.$tag.decompress.log"; exit 1; }
      cmp -s "$img" "in_$st.bmp" || { echo "$st/$tag: NOT LOSSLESS"; exit 1; }
      exit 0
    ) || { echo "FAIL"; exit 1; }
  done
done
echo "PASS"
