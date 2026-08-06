#!/usr/bin/env bash
# t32.sh — end-to-end pe2elf32 + winapi_shim32 smoke test.
#
# Builds pe2elf32, the 32-bit shim and load32, then for each PE under exe32/
# converts it twice — once as a plain ET_EXEC (`pe2elf32 in.exe out.elf`) and
# once as a dlopen-able shared object (`--so`, run via ./load32) — and checks
# that both exit 0 and print the expected marker.
#
# The counterpart of t.sh, which drives the 64-bit pipeline against the
# archiver binaries in exe/.  Those won't parse here (wrong machine type), so
# this harness runs the 32-bit fixtures in exe32/ instead:
#
#   1b   no-CRT PE32: GetStdHandle/WriteFile/ExitProcess only.  Gates the
#        converter, the FS-based TEB, stdcall dispatch and the IAT/R_386_32
#        and REL base-reloc paths in isolation.
#   1c   MSVCRT-linked PE32.  Gates CRT startup: __getmainargs, _initterm,
#        cdecl printf over the native va_list, the 32-byte _iobuf, and the
#        fs:[0] __try registration MSVC emits around main.
#   seh  Faults through a null pointer inside a hand-built fs:[0] frame whose
#        handler rewrites CONTEXT.Eip and returns ExceptionContinueExecution.
#        Gates the signal-driven x86 SEH dispatcher.  Rebuild it with
#        exe32/mkseh32.sh.
#
# Then a real-world target: BMF 2.01, Dmitry Shkarin's lossless image
# compressor.  It is statically linked against the MSVC CRT (no msvcrt.dll
# imports at all), so it exercises a very different surface from 1c —
# heap, file I/O, RtlUnwind, GetStringType/LCMapString, console mode — and
# the round-trip is checked for pixel-exactness rather than for a string in
# stdout, which makes it the first end-to-end correctness test here.
#
# Drop 32-bit builds of the archiver tools into exe32/ and add them to the
# target list to extend coverage; anything needing ordinal imports also needs
# the matching 32-bit DLLs under dll32/.

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

# Run one binary through both output modes.
# Args: <exe-stem> <expected-substring>
run_target() {
  local stem="$1" expect="$2"
  local exe="exe32/${stem}.exe"
  local elf="${stem}.elf"
  local so="${stem}.so"

  rm -f "$elf" "$so"

  # --- ET_EXEC ------------------------------------------------------------
  step "convert ${stem} (ET_EXEC)" ./pe2elf32 "$exe" "$elf" || return 1
  echo
  echo "=== run ${stem} (ET_EXEC) ==="
  echo "+ ./${elf}"
  local out rc
  out=$(./"$elf" 2>&1); rc=$?
  echo "$out"
  echo "(exit $rc)"
  if [ "$rc" -ne 0 ]; then
    echo "FAIL: ./${elf} exited $rc (expected 0)"
    FAIL=$((FAIL+1))
  elif ! echo "$out" | grep -qF "$expect"; then
    echo "FAIL: ${elf} output did not contain '${expect}'"
    FAIL=$((FAIL+1))
  else
    echo "ok: run ${stem} ET_EXEC (exit 0, output contains '${expect}')"
    PASS=$((PASS+1))
  fi

  # --- --so via load32 ----------------------------------------------------
  step "convert ${stem} (--so)" ./pe2elf32 "$exe" "$so" --so || return 1
  echo
  echo "=== run ${stem} (--so) ==="
  echo "+ ./load32 ./${so}"
  out=$(./load32 ./"$so" 2>&1); rc=$?
  echo "$out"
  echo "(exit $rc)"
  if [ "$rc" -ne 0 ]; then
    echo "FAIL: ./load32 ./${so} exited $rc (expected 0)"
    FAIL=$((FAIL+1))
  elif ! echo "$out" | grep -qF "$expect"; then
    echo "FAIL: ${so} output did not contain '${expect}'"
    FAIL=$((FAIL+1))
  else
    echo "ok: run ${stem} --so (exit 0, output contains '${expect}')"
    PASS=$((PASS+1))
  fi
}

# 1. Clean slate.
step "clean" rm -f pe2elf32 winapi_shim32.so winapi_shim32_dbg.so load32 \
                *.elf 1b.so 1c.so seh.so || exit 1

# 2. Build.  Needs the 32-bit dev headers/libs — see the Makefile comment.
step "make" make -j"$(nproc)" pe2elf32 winapi_shim32.so load32 || exit 1

for f in pe2elf32 winapi_shim32.so load32; do
  if [ ! -f "$f" ]; then
    echo "FAIL: make did not produce $f"
    FAIL=$((FAIL+1))
    exit 1
  fi
done

# BMF round-trip: compress a generated BMP and decompress it again, asserting
# the pixel data comes back identical.  Runs in a scratch directory because
# BMF writes its output next to its input.
#
# Args: <label> <files-to-copy> <command...>
#   files-to-copy is one space-separated word (the shim is copied anyway);
#   command is run from inside the scratch dir with the image appended.
run_bmf_roundtrip() {
  local label="$1" copies="$2"; shift 2
  local work="bmf_work_$$"
  rm -rf "$work"; mkdir -p "$work"
  cp winapi_shim32.so "$work/" || return 1
  local f
  for f in $copies; do
    cp "$f" "$work/" || { echo "FAIL: cannot stage $f"; FAIL=$((FAIL+1)); rm -rf "$work"; return 1; }
  done

  if ! python3 exe32/mkbmp32.py "$work/test.bmp" 256 192 >/dev/null; then
    echo "FAIL: could not generate test.bmp"; FAIL=$((FAIL+1)); rm -rf "$work"; return 1
  fi

  echo
  echo "=== BMF round-trip ($label) ==="
  echo "+ $* test.bmp"
  local out rc
  out=$( cd "$work"
    "$@" test.bmp 2>&1 || exit 1
    [ -s test.bmf ] || { echo "no test.bmf produced"; exit 1; }
    echo "compressed: $(stat -c%s test.bmp) -> $(stat -c%s test.bmf) bytes"
    mv test.bmp orig.bmp
    "$@" test.bmf 2>&1 || exit 1
    [ -s test.bmp ] || { echo "no test.bmp produced on decompress"; exit 1; }
    # BMF does not store the BMP DPI fields, so a header-only difference is
    # expected in general; mkbmp32.py zeroes them, so this should be exact.
    if cmp -s orig.bmp test.bmp; then
      echo "round-trip byte-exact"
    else
      pd=$(cmp -l orig.bmp test.bmp 2>/dev/null | awk '$1>54' | wc -l)
      [ "$pd" = 0 ] && echo "round-trip pixel-exact (header metadata differs)" \
                    || { echo "PIXELS DIFFER: $pd bytes"; exit 1; }
    fi )
  rc=$?
  echo "$out"
  rm -rf "$work"
  if [ "$rc" -ne 0 ] || ! echo "$out" | grep -q "round-trip"; then
    echo "FAIL: BMF round-trip ($label)"
    FAIL=$((FAIL+1))
    return 1
  fi
  echo "ok: BMF round-trip ($label)"
  PASS=$((PASS+1))
}

# 3. Each target: convert + run + verify, in both output modes.
run_target 1b  "Hello, world!!!"
run_target 1c  "Hello, world!!!"
run_target seh "SEH caught the AV and resumed"

# 4. Real-world target: BMF, checked for a correct compress/decompress
# round-trip rather than for a string in stdout.
if [ -f exe32/BMF.exe ]; then
  step "convert BMF (ET_EXEC)" ./pe2elf32 exe32/BMF.exe BMF.elf \
    && run_bmf_roundtrip "ET_EXEC" "BMF.elf" ./BMF.elf
  step "convert BMF (--so)" ./pe2elf32 exe32/BMF.exe BMF.so --so \
    && run_bmf_roundtrip "--so via load32" "BMF.so load32" ./load32 ./BMF.so
else
  echo
  echo "skip: exe32/BMF.exe not present"
fi

echo
echo "=== summary ==="
echo "passed: $PASS"
echo "failed: $FAIL"
[ "$FAIL" -eq 0 ]
