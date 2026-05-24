#!/usr/bin/env bash
# t.sh — end-to-end pe2elf + shim smoke test.
#
# Builds pe2elf and the shim, converts exe/rar390.exe to an ELF, then runs
# that ELF to create a small RAR archive of the *.so files.  Passes when
# the run exits 0 AND its stdout contains "Done".

set -u
cd "$(dirname "$0")"

PASS=0
FAIL=0

step() {
  local name="$1"; shift
  echo
  echo "=== $name ==="
  echo "+ $*"
  "$@"
  local rc=$?
  if [ "$rc" -ne 0 ]; then
    echo "FAIL: $name exited $rc"
    FAIL=$((FAIL+1))
    return 1
  fi
  echo "ok: $name"
  PASS=$((PASS+1))
  return 0
}

# 1. Clean slate — remove previous build artifacts and any leftover archive.
step "clean" rm -f pe2elf winapi_shim.so winapi_shim_dbg.so dummy.so \
                rar390.elf archive.rar || exit 1

# 2. Build pe2elf + shim.  The default 'all' target also builds dummy.so,
# which needs a defs.h that lives outside the repo; build only what the
# test needs.
step "make" make -j"$(nproc)" pe2elf winapi_shim.so || exit 1

# Sanity: required outputs exist.
for f in pe2elf winapi_shim.so; do
  if [ ! -f "$f" ]; then
    echo "FAIL: make did not produce $f"
    FAIL=$((FAIL+1))
    exit 1
  fi
done

# 3. Convert rar390.exe → rar390.elf.
step "convert" ./pe2elf exe/rar390.exe rar390.elf || exit 1
chmod +x rar390.elf
if [ ! -x rar390.elf ]; then
  echo "FAIL: rar390.elf not present or not executable after conversion"
  FAIL=$((FAIL+1))
  exit 1
fi

# 4. Run the converted binary — archive *.so with rar -m5.
echo
echo "=== run ==="
echo "+ ./rar390.elf a -m5 archive *.so"
OUT=$(./rar390.elf a -m5 archive *.so 2>&1)
RC=$?
echo "$OUT"
echo "(exit $RC)"

if [ "$RC" -ne 0 ]; then
  echo "FAIL: rar390.elf exited $RC (expected 0)"
  FAIL=$((FAIL+1))
elif ! echo "$OUT" | grep -q "Done"; then
  echo "FAIL: rar390.elf output did not contain 'Done'"
  FAIL=$((FAIL+1))
else
  echo "ok: run (exit 0, output contains 'Done')"
  PASS=$((PASS+1))
fi

# 5. Verify the archive was actually produced.
if [ -f archive.rar ] && [ -s archive.rar ]; then
  echo "ok: archive.rar produced ($(stat -c%s archive.rar) bytes)"
  PASS=$((PASS+1))
else
  echo "FAIL: archive.rar missing or empty"
  FAIL=$((FAIL+1))
fi

echo
echo "=== summary ==="
echo "passed: $PASS"
echo "failed: $FAIL"
[ "$FAIL" -eq 0 ]
