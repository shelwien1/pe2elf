#!/usr/bin/env bash
# t.sh — end-to-end pe2elf + shim smoke test.
#
# Builds pe2elf and the shim, then for each PE in the EXE_TARGETS list
# converts it to ELF and runs it as `<elf> a -m5 <archive> *.so`.  Each
# binary passes when the run exits 0 AND its stdout contains "Done".

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

# Run one binary end-to-end: convert exe/<name>.exe, then archive *.so.
# Args: <exe-stem> e.g. "rar390"
run_target() {
  local stem="$1"
  local exe="exe/${stem}.exe"
  local elf="${stem}.elf"
  local arc="archive_${stem}"

  rm -f "$elf" "${arc}.rar"

  step "convert ${stem}" ./pe2elf "$exe" "$elf" || return 1
  chmod +x "$elf"
  if [ ! -x "$elf" ]; then
    echo "FAIL: ${elf} not present or not executable after conversion"
    FAIL=$((FAIL+1))
    return 1
  fi

  echo
  echo "=== run ${stem} ==="
  echo "+ ./${elf} a -m5 ${arc} *.so"
  local out rc
  out=$(./"$elf" a -m5 "$arc" *.so 2>&1)
  rc=$?
  echo "$out"
  echo "(exit $rc)"

  if [ "$rc" -ne 0 ]; then
    echo "FAIL: ${elf} exited $rc (expected 0)"
    FAIL=$((FAIL+1))
  elif ! echo "$out" | grep -q "Done"; then
    echo "FAIL: ${elf} output did not contain 'Done'"
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
step "clean" rm -f pe2elf winapi_shim.so winapi_shim_dbg.so dummy.so \
                rar*.elf archive*.rar || exit 1

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
