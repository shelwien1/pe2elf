#!/usr/bin/env bash
# t.sh — end-to-end pe2elf + shim smoke test (--so / load variant).
#
# Builds pe2elf, the shim, and the load helper, then for each PE in the
# EXE_TARGETS list converts it to a .so (pe2elf --so) and runs it via
# `./load <pe.so> a -m5 <archive> *.so`.  Each binary passes when the
# run exits 0 AND its stdout contains "Done".

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

# Run one binary end-to-end: convert exe/<name>.exe → .so, then archive *.so via load.
# Args: <exe-stem> e.g. "rar390"
run_target() {
  local stem="$1"
  local exe="exe/${stem}.exe"
  local so="${stem}.so"
  local arc="archive_${stem}"

  rm -f "$so" "${arc}.rar"

  step "convert ${stem} (--so)" ./pe2elf "$exe" "$so" --so || return 1
  if [ ! -f "$so" ]; then
    echo "FAIL: ${so} not present after conversion"
    FAIL=$((FAIL+1))
    return 1
  fi

  echo
  echo "=== run ${stem} ==="
  echo "+ ./load ./${so} a -m5 ${arc} *.so"
  local out rc
  out=$(./load ./"$so" a -m5 "$arc" *.so 2>&1)
  rc=$?
  echo "$out"
  echo "(exit $rc)"

  if [ "$rc" -ne 0 ]; then
    echo "FAIL: ./load ./${so} exited $rc (expected 0)"
    FAIL=$((FAIL+1))
  elif ! echo "$out" | grep -q "Done"; then
    echo "FAIL: ${so} output did not contain 'Done'"
    FAIL=$((FAIL+1))
  else
    echo "ok: run ${stem} (exit 0, output contains 'Done')"
    PASS=$((PASS+1))
  fi

  if [ -f "${arc}.rar" ] && [ -s "${arc}.rar" ]; then
    echo "ok: ${arc}.rar produced ($(stat -c%s "${arc}.rar") bytes)"
    PASS=$((PASS+1))
  else
    echo "FAIL: ${arc}.rar missing or empty"
    FAIL=$((FAIL+1))
  fi
}

# 1. Clean slate — remove previous build artifacts and any leftover archive.
step "clean" rm -f pe2elf winapi_shim.so winapi_shim_dbg.so dummy.so load \
                rar*.so archive*.rar || exit 1

# 2. Build pe2elf + shim + load.  The default 'all' target also builds dummy.so,
# which needs a defs.h that lives outside the repo; build only what the
# test needs.
step "make" make -j"$(nproc)" pe2elf winapi_shim.so load || exit 1

# Sanity: required outputs exist.
for f in pe2elf winapi_shim.so load; do
  if [ ! -f "$f" ]; then
    echo "FAIL: make did not produce $f"
    FAIL=$((FAIL+1))
    exit 1
  fi
done

# 3. Each target: convert + run + verify.
EXE_TARGETS=(rar390 rar550a rar701a)
for t in "${EXE_TARGETS[@]}"; do
  run_target "$t"
done

echo
echo "=== summary ==="
echo "passed: $PASS"
echo "failed: $FAIL"
[ "$FAIL" -eq 0 ]
