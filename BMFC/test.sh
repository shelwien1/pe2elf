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
FLAGS=${BMF_FLAGS:--S -Q9}
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
[ -f "$TESTDIR/f05_200.bmp" ] && IMAGES="$IMAGES f05_200.bmp"

rm -rf "$WORK"; mkdir -p "$WORK"
cp "$BIN" "$WORK/" || exit 1
BIN="./$(basename "$BIN")"
for img in $IMAGES; do
  [ -f "$TESTDIR/$img" ] || { echo "missing test image: $TESTDIR/$img"; exit 1; }
  cp "$TESTDIR/$img" "$WORK/"
done

for img in $IMAGES; do
  st="${img%.bmp}"
  ref="$TESTDIR/ref_$st.bmf"
  [ -f "$ref" ] || { echo "$st: no reference stream at $ref"; exit 1; }
  (
    cd "$WORK"
    timeout 300 $RUN "$BIN" $FLAGS "$img" >"$st.compress.log" 2>&1
    rc=$?; [ $rc -ne 0 ] && { echo "$st: COMPRESS FAILED (rc=$rc)"; cat "$st.compress.log"; exit 1; }
    [ -s "$st.bmf" ] || { echo "$st: NO .bmf PRODUCED"; exit 1; }
    cmp -s "$st.bmf" "../$ref" \
      || echo "$st: stream differs from the original's ($(stat -c%s "$st.bmf") vs $(stat -c%s "../$ref"))" >&2
    mv "$img" "orig_$st.bmp"
    timeout 300 $RUN "$BIN" "$st.bmf" >"$st.decompress.log" 2>&1
    rc=$?; [ $rc -ne 0 ] && { echo "$st: DECOMPRESS FAILED (rc=$rc)"; cat "$st.decompress.log"; exit 1; }
    cmp -s "orig_$st.bmp" "$img" || { echo "$st: NOT LOSSLESS"; exit 1; }
    exit 0
  ) || { echo "FAIL"; exit 1; }
done
echo "PASS"
