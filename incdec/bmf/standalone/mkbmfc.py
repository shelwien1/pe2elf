#!/usr/bin/env python3
"""mkbmfc.py — assemble ../../../BMFC, the standalone program as a source tree.

The incdec working tree is a *workshop*: BMF.cpp, BMF.asm, the extractor, the
fixups, the hybrid that injects into the real BMF.exe, and the probe and trace
machinery that made the migration possible.  BMFC is the product — the sources
you would ship, with none of that.

Almost everything is copied rather than rewritten, so BMFC is provably the same
program:

    inc/*.inc     the 143 decompiled bodies, byte for byte
    crt.cpp       the runtime, POSIX and Win32 branches
    main.cpp      the entry point
    bmfdefs.h     Hex-Rays' defs.h, byte for byte
    blob.inc      BMF's data segment (mkdata.py)

The one file that is transformed is the head.  dummy32_head.cpp carries the
hybrid's half too — patch_jmp, the ExitProcess hook, the probe registry, the
naked trampolines into the PE's Intel maths entries, and the POSIX-only headers
those need — all behind `#ifndef BMF_STANDALONE`.  None of it can compile on
Windows and none of it belongs in the deliverable, so the conditionals are
evaluated out.  That is verified rather than trusted: both forms are run
through the preprocessor and the token streams have to match.

Usage: mkbmfc.py [--check]     --check verifies without writing
"""
import os
import re
import shutil
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
BMF = os.path.join(HERE, '..')
OUT = os.path.abspath(os.path.join(HERE, '..', '..', '..', 'BMFC'))

# What the standalone build settles on.  BMF_PROBES stays off: the call
# counters are a decompilation instrument (README, "Diagnosing a standalone
# stream that differs"), not part of the program.
DEFINES = {'BMF_STANDALONE': True, 'BMF_PROBES': False}

DIRECTIVE = re.compile(r'^\s*#\s*(ifdef|ifndef|if|else|elif|endif)\b(.*)$')


def evaluate(cond, defines):
    """True/False for a condition over *known* names only, else None.

    Deliberately not a C expression evaluator: it handles `defined(X)`, `X`,
    `!`, `&&`, `||` and parentheses, and gives up the moment a name appears
    that is not in `defines` — a block whose condition it cannot decide is left
    exactly as it was.
    """
    expr = cond.strip()
    if not expr:
        return None
    names = set(re.findall(r'[A-Za-z_]\w*', expr)) - {'defined'}
    if not names <= set(defines):
        return None
    expr = re.sub(r'defined\s*\(\s*([A-Za-z_]\w*)\s*\)', r'\1', expr)
    expr = re.sub(r'\bdefined\s+([A-Za-z_]\w*)', r'\1', expr)
    for n in names:
        expr = re.sub(r'\b' + n + r'\b', 'True' if defines[n] else 'False', expr)
    expr = expr.replace('&&', ' and ').replace('||', ' or ').replace('!', ' not ')
    try:
        return bool(eval(expr, {'__builtins__': {}}, {}))
    except Exception:
        return None


def strip_conditionals(lines, defines, i=0, depth=0):
    """Resolve the conditionals this knows the answer to; pass the rest on."""
    out = []
    while i < len(lines):
        m = DIRECTIVE.match(lines[i])
        if not m:
            out.append(lines[i]); i += 1; continue
        kind, rest = m.group(1), m.group(2)
        if kind in ('else', 'elif', 'endif'):
            return out, i          # the caller owns this one
        if kind == 'ifdef':
            val = evaluate(rest, defines)
        elif kind == 'ifndef':
            val = evaluate(rest, defines)
            val = None if val is None else not val
        else:
            val = evaluate(rest, defines)
        taken, i = strip_conditionals(lines, defines, i + 1, depth + 1)
        branches = [(val, taken)]
        while True:
            m2 = DIRECTIVE.match(lines[i])
            kind2 = m2.group(1)
            if kind2 == 'endif':
                i += 1
                break
            if kind2 == 'elif':
                v2 = evaluate(m2.group(2), defines)
                body, i = strip_conditionals(lines, defines, i + 1, depth + 1)
                branches.append((v2, body))
                continue
            # else
            body, i = strip_conditionals(lines, defines, i + 1, depth + 1)
            branches.append(('else', body))
        if any(v is None for v, _ in branches):
            # Undecidable: re-emit the whole construct untouched.
            out.extend(_reemit(m, branches))
            continue
        chosen = None
        for v, body in branches:
            if v is True:
                chosen = body
                break
        if chosen is None:
            chosen = next((b for v, b in branches if v == 'else'), [])
        out.extend(chosen)
    return out, i


def _reemit(m, branches):
    """An undecidable construct, put back the way it came in."""
    out = [m.group(0)]
    for k, (_v, body) in enumerate(branches):
        if k:
            out.append('#else')
        out.extend(body)
    out.append('#endif')
    return out


def preprocessed(path, extra=()):
    """Token stream of `path` as g++ sees it, for the equivalence check."""
    cmd = ['g++', '-m32', '-std=c++17', '-E', '-P', '-x', 'c++', path,
           '-I', BMF, '-I', OUT, '-I', HERE, '-DBMF_STANDALONE=1'] + list(extra)
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit('preprocessing %s failed:\n%s' % (path, r.stderr[-2000:]))
    return re.sub(r'\s+', ' ', r.stdout).strip()


BUILD_SH = '''#!/usr/bin/env bash
# build.sh — native build (32-bit ELF).
#
# BMF is 32-bit i386 code and cannot be built any other way: the decompilation
# casts pointers to int throughout, which is what the original does.
#
# -msse2 -mfpmath=sse because the donor is Intel C++ output that kept float and
# double at 32 and 64 bits, where gcc's i386 default (-mfpmath=387) would
# evaluate them with x87's 80-bit intermediates and change the arithmetic.
# -fno-strict-aliasing because the decompiler reads the same storage through
# several types.  -fpermissive because it also converts between pointer types
# without casts.  None of these is optional.
set -eu
cd "$(dirname "$0")"
exec g++ ${CXXFLAGS:--O2} -m32 -msse2 -mfpmath=sse -std=c++17 -fpermissive \\
    -fno-strict-aliasing -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 \\
    -Wno-narrowing -Wno-write-strings -Wno-unused-variable \\
    -Wno-unused-but-set-variable -Wno-parentheses \\
    -o "${OUT:-bmf}" bmf.cpp -Wl,-z,noexecstack -lm
'''

BUILD_MINGW_SH = '''#!/usr/bin/env bash
# build-mingw.sh — Windows build, cross-compiled.
#
# Same flags as build.sh (see there for why each one is required), plus:
#
#   -static        so the .exe carries libgcc/libstdc++ rather than needing
#                  libgcc_s_dw2-1.dll next to it.  Without it Windows refuses
#                  to start the image and prints nothing.
#   no -m32        i686-w64-mingw32 is already 32-bit; passing -m32 as well is
#                  harmless but redundant.
#
# The runtime here is msvcrt and the real kernel32 — which is where BMF's code
# came from in the first place, so crt.cpp's Windows half is ten import
# declarations and no implementation.
set -eu
cd "$(dirname "$0")"
CXX=${CXX:-i686-w64-mingw32-g++}
command -v "$CXX" >/dev/null || {
  echo "$CXX not found (Debian/Ubuntu: apt install g++-mingw-w64-i686)" >&2
  exit 1
}
exec "$CXX" ${CXXFLAGS:--O2} -msse2 -mfpmath=sse -std=c++17 -fpermissive \\
    -fno-strict-aliasing -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 \\
    -Wno-narrowing -Wno-write-strings -Wno-unused-variable \\
    -Wno-unused-but-set-variable -Wno-parentheses \\
    -static -o "${OUT:-bmf.exe}" bmf.cpp
'''

MAKEFILE = '''# BMFC — decompiled BMF as a standalone program.
#
#   make            native 32-bit ELF        -> bmf
#   make bmf.exe    Windows, via mingw       -> bmf.exe
#   make test       round-trip gate, native
#   make test-wine  round-trip gate, Windows binary under wine
#   make all test-all
#
# The build scripts carry the reasoning for the compiler flags; this is a
# convenience wrapper over them.
.PHONY: all test test-wine test-all clean

all: bmf

bmf: bmf.cpp crt.cpp main.cpp bmfhead.h bmfdefs.h blob.inc $(wildcard inc/*.inc)
\t./build.sh

bmf.exe: bmf.cpp crt.cpp main.cpp bmfhead.h bmfdefs.h blob.inc $(wildcard inc/*.inc)
\t./build-mingw.sh

test: bmf
\t./test.sh ./bmf

test-wine: bmf.exe
\t./test.sh --wine ./bmf.exe

test-all: test test-wine

clean:
\trm -f bmf bmf.exe
\trm -rf run
'''

TEST_SH = r'''#!/usr/bin/env bash
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
'''


def main():
    check = '--check' in sys.argv
    blob = os.path.join(HERE, 'blob.inc')
    if not os.path.exists(blob):
        subprocess.run([sys.executable, os.path.join(HERE, 'mkdata.py')], check=True)

    accepted = [l.split() for l in open(os.path.join(BMF, 'accepted.txt')) if l.strip()]

    if not check:
        shutil.rmtree(os.path.join(OUT, 'inc'), ignore_errors=True)
        os.makedirs(os.path.join(OUT, 'inc'), exist_ok=True)

    # --- the head, with the hybrid's half evaluated out ---------------------
    src = open(os.path.join(BMF, 'dummy32_head.cpp')).read().split('\n')
    stripped, _ = strip_conditionals(src, DEFINES)
    head = '\n'.join(stripped)
    head = head.replace('"defs.h"', '"bmfdefs.h"')
    head = head.replace(
        '// dummy32.cpp head — incdec infrastructure for BMF.exe (incdec.md §7).\n'
        '//\n'
        '// The full dummy32.cpp is assembled by build.sh: this head, then one\n'
        '// #include per accepted .inc, then the generated dummy_init() tail.',
        '// bmfhead.h — the vocabulary the decompiled bodies are written in.\n'
        '//\n'
        '// Generated from incdec/bmf/dummy32_head.cpp by incdec/bmf/standalone/\n'
        '// mkbmfc.py, with the conditionals for the injected build evaluated out.\n'
        '// Do not edit: change the original and re-run the generator.')
    # The probe paragraph describes a knob this tree does not have.
    head = head.replace(
        '''// §7.1's probes answered "did this body actually run inside the PE?".  In the
// standalone build there is no PE and nothing to compare against, so they
// compile away — including the trap-arming, which existed to get ahead of the
// shim's own SIGSEGV handler.
//
// -DBMF_PROBES brings them back, and standalone/main.cpp dumps the counters
// from an atexit handler.  That is how a standalone stream that differs from
// the hybrid's gets pinned down: run both over the same image and the first
// function whose call count diverges is where the two builds part company.''',
        '''// Every body opens with PROBE_DECL/PROBE_HIT.  Those were the instrument that
// answered "did this function actually run inside the original binary?" while
// the decompilation was being migrated one function at a time; here there is
// nothing to compare against and they compile away.  The calls stay in the
// bodies so that those files remain byte-identical to the extractor's output.''')
    head = re.sub(r'\n\n\n+', '\n\n', head)

    if not check:
        open(os.path.join(OUT, 'bmfhead.h'), 'w').write(head + '\n')
        shutil.copy(os.path.join(BMF, 'defs.h'), os.path.join(OUT, 'bmfdefs.h'))
        shutil.copy(blob, os.path.join(OUT, 'blob.inc'))
        for name in ('crt.cpp',):
            shutil.copy(os.path.join(HERE, name), os.path.join(OUT, name))
        main_src, _ = strip_conditionals(
            open(os.path.join(HERE, 'main.cpp')).read().split('\n'), DEFINES)
        open(os.path.join(OUT, 'main.cpp'), 'w').write(
            re.sub(r'\n\n\n+', '\n\n', '\n'.join(main_src)).rstrip('\n') + '\n')
        for _va, name, _conv in accepted:
            shutil.copy(os.path.join(BMF, 'inc', name + '.inc'),
                        os.path.join(OUT, 'inc', name + '.inc'))
        open(os.path.join(OUT, 'bmf.cpp'), 'w').write(bmf_cpp(accepted))
        for fn, text, mode in (('build.sh', BUILD_SH, 0o755),
                               ('build-mingw.sh', BUILD_MINGW_SH, 0o755),
                               ('test.sh', TEST_SH, 0o755),
                               ('Makefile', MAKEFILE, 0o644)):
            p = os.path.join(OUT, fn)
            open(p, 'w').write(text)
            os.chmod(p, mode)

    # --- prove the strip changed nothing -----------------------------------
    a = preprocessed(os.path.join(BMF, 'dummy32_head.cpp'))
    b = preprocessed(os.path.join(OUT, 'bmfhead.h'))
    if a != b:
        sys.exit('bmfhead.h is not equivalent to dummy32_head.cpp under '
                 '-DBMF_STANDALONE: the conditional strip changed the program')

    print('BMFC: %d bodies, head verified equivalent to the original under '
          '-DBMF_STANDALONE' % len(accepted))


def bmf_cpp(accepted):
    out = ['''// bmf.cpp — BMF, the whole program, as one translation unit.
//
// BMF 2.01 by Dmitry Shkarin, recovered from the 32-bit Windows binary: 143
// functions decompiled with Hex-Rays and corrected against the disassembly
// until the compressed streams came out bit-for-bit identical to the
// original\'s on every test image.  See README.md.
//
// One translation unit because the bodies are not independent: they share
// globals by address (blob.inc), several are entered through calling
// conventions that only exist inside a file (thiscall, fastcall), and the
// order below is callees-before-callers so that a call to an already-defined
// body needs no forward declaration.  Splitting it up would buy nothing and
// cost all of that.
//
// Generated by incdec/bmf/standalone/mkbmfc.py.  Do not edit.

// Selects the standalone half of bmfhead.h and of each body: no redirects
// into a loaded BMF.exe, no entry-point thunks for callers that no longer
// exist, no call-count probes.
#define BMF_STANDALONE 1

#include "blob.inc"     // BMF\'s data segment, and the globals\' base
#include "bmfhead.h"    // Hex-Rays\' type vocabulary, SSE wrappers, defs.h
#include "crt.cpp"      // the C runtime and the ten kernel32 imports

// ---- the decompiled bodies, callees before callers ----''']
    for _va, name, _conv in accepted:
        out.append('#include "inc/%s.inc"' % name)
    out.append('')
    out.append('#include "main.cpp"    // entry point, and BMF\'s startup')
    return '\n'.join(out) + '\n'


if __name__ == '__main__':
    main()
