#!/usr/bin/env bash
# test.sh — the same gate as ../test.sh, run against the standalone binary.
#
# Identical conditions, so the two are directly comparable: for each image,
# compress with the given flags, check the stream is no larger than the
# reference the un-injected BMF.exe produced, decompress, and require the
# result to be byte-identical to the input.  Stream inequality is reported but
# does not fail — the goal is a lossless codec that compresses no worse than
# BMF, not one that reproduces its output bit for bit.
set -u
cd "$(dirname "$0")"

FLAGS=${BMF_FLAGS:--S -Q9}
WORK=run
BMF=./bmf

DEFAULT_IMAGES="t1.bmp t8g.bmp t8p.bmp t24.bmp t32.bmp"
[ -f ../f05_200.bmp ] && DEFAULT_IMAGES="$DEFAULT_IMAGES f05_200.bmp"
IMAGES=${BMF_IMAGES:-$DEFAULT_IMAGES}

[ -x "$BMF" ] || { echo "no $BMF (run ./build.sh)"; exit 1; }

rm -rf "$WORK"; mkdir -p "$WORK"
cp "$BMF" "$WORK/bmf"
for img in $IMAGES; do
  [ -f "../$img" ] || { echo "missing test image: ../$img (run ../test.sh --baseline)"; exit 1; }
  cp "../$img" "$WORK/"
done

same=0
for img in $IMAGES; do
  st="${img%.bmp}"
  [ -f "../ref_$st.bmf" ] || { echo "$st: no reference (run ../test.sh --baseline)"; exit 1; }
  refsz=$(stat -c%s "../ref_$st.bmf")
  (
    cd "$WORK"
    timeout 60 ./bmf $FLAGS "$img" >"$st.compress.log" 2>&1
    rc=$?; [ $rc -eq 124 ] && { echo "$st: COMPRESS TIMED OUT"; exit 1; }
    [ $rc -ne 0 ] && { echo "$st: COMPRESS FAILED (rc=$rc)"; exit 1; }
    [ -s "$st.bmf" ] || { echo "$st: NO .bmf PRODUCED"; exit 1; }
    sz=$(stat -c%s "$st.bmf")
    [ "$sz" -gt "$refsz" ] && { echo "$st: LARGER THAN REFERENCE ($sz > $refsz)"; exit 1; }
    cmp -s "$st.bmf" "../../ref_$st.bmf" || echo "$st: stream differs from reference ($sz vs $refsz bytes)" >&2
    mv "$img" "orig_$st.bmp"
    timeout 60 ./bmf "$st.bmf" >"$st.decompress.log" 2>&1
    rc=$?; [ $rc -eq 124 ] && { echo "$st: DECOMPRESS TIMED OUT"; exit 1; }
    [ $rc -ne 0 ] && { echo "$st: DECOMPRESS FAILED (rc=$rc)"; exit 1; }
    cmp -s "orig_$st.bmp" "$img" || { echo "$st: NOT LOSSLESS"; exit 1; }
    exit 0
  ) || { echo "FAIL"; exit 1; }
done
echo "PASS"
exit 0
