#!/usr/bin/env python3
"""extract.py — generate a .inc scaffold for one BMF function.

The BMF-targeted counterpart of incdec/extract_fn.py (which is still written
for the x64 PPMonstr target — see incdec.md §8.5).  Differences that matter:

  * Emits the i386 calling convention Hex-Rays printed for the function
    (nothing at all for __cdecl, which is gcc's i386 default), not a blanket
    ms_abi.  incdec.md §4.
  * Resolves every external symbol from its own auto-generated name: BMF has
    no symbol table shipped with it, so `dword_441A20` is the *only* evidence
    that the global lives at 0x441A20.  A body referencing anything else
    (named CRT entries, operator new/delete) cannot be resolved and the
    function is refused rather than silently mis-linked.
  * Uses the declared type + extent from BMF.cpp's data-declaration section
    where available, falling back to a usage-derived guess.

Usage: extract.py <name> [--accepted accepted.txt] [--out inc/<name>.inc]
"""
import argparse
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
SRC = os.path.join(HERE, 'BMF.cpp')

GLOBAL_RE = r'(?:dword|byte|word|unk|off|flt|dbl|qword|xmmword|asc)_[0-9A-Fa-f]{6}'
SUB_RE = r'sub_[0-9A-Fa-f]{6}'

# Prefix -> base type, used when the data-declaration section has no entry.
PREFIX_TYPE = {
    'dword': 'int', 'byte': 'unsigned char', 'word': 'unsigned short',
    'qword': 'long long', 'flt': 'float', 'dbl': 'double',
    'xmmword': '__m128i', 'unk': 'unsigned char', 'off': 'void *',
    'asc': 'char',
}

# Stateless libc that incdec.md §6.5 permits falling through to glibc.
PURE_LIBC = {'strcpy', 'strncpy', 'strcat', 'strrchr', 'strchr', 'memset', 'memcpy',
             'memcmp', 'strlen', 'strcmp', 'toupper', 'tolower', 'isspace',
             'isdigit', 'abs', 'fminf', 'fmaxf', 'sqrtf', 'atoi'}

INTRIN = re.compile(r'^(_mm_|_m_|__|LOBYTE|HIBYTE|LOWORD|HIWORD|LODWORD|HIDWORD'
                    r'|BYTE\d+|WORD\d+|DWORD\d+|SBYTE\d+|SWORD\d+|SDWORD\d+'
                    r'|SLOBYTE|SLOWORD|SLODWORD|SHIBYTE|SHIWORD|SHIDWORD|COERCE_|abs\d+'
                    r'|alloca|qmemcpy|memset32|sizeof|_BitScanForward|_fxsave)')
# Checked *before* INTRIN, whose `__` branch would otherwise swallow these.
# They are real functions in the image, not compiler helpers.  The ones with a
# recovered signature are listed in CRT_PROTO and resolve like any other static
# CRT entry; the rest take their arguments in SSE registers and Hex-Rays
# recovered nothing — `__svml_log2()` and `__libm_sse2_log()` are printed with
# no arguments at all, at call sites that plainly compute one — so a redirect
# built on that signature would pass garbage.  Refuse those.
INTEL_CRT = re.compile(r'^(__svml_|__intel_|__libm_)')
# Intel CRT maths entries that take and return their argument in xmm0.  There
# is no i386 C convention for that, so dummy32_head.cpp supplies a naked
# trampoline plus an inline wrapper for each; the body's call resolves to the
# wrapper and nothing has to be declared here.  Hex-Rays printed both with an
# empty argument list, so a body that calls one has to have the argument put
# back by hand (fixups.txt) — see sub_40A8A0.
XMM0_CRT = {'__svml_log2', '__libm_sse2_log', '__intel_sse2_strlen'}
CTRL = {'if', 'for', 'while', 'switch', 'return', 'do', 'else', 'sizeof',
        # Type names, which appear followed by '(' in casts to function
        # pointers — `(void (__cdecl *)(int))` reads as a call to `void`.
        'void', 'int', 'char', 'short', 'long', 'float', 'double', 'signed',
        'unsigned', 'bool', 'struct', 'union', 'enum', 'const', 'static',
        '_BYTE', '_WORD', '_DWORD', '_QWORD', '_OWORD', '_UNKNOWN', '_BOOL1',
        '_BOOL2', '_BOOL4', 'size_t', 'FILE', 'Stream'}

# Callees Hex-Rays prints as __usercall/__userpurge whose "register arguments"
# are not arguments at all.
#
# Both of these are the Intel CRT's dispatch stubs — `sub_4349F0` tests n1024
# (the CPU level sub_434A30 computes) and jumps to the matching memset variant,
# `sub_434980` does the same for memcpy — and IDA's own frame for each declares
# exactly three plain stack arguments (`buf = dword ptr 4`, `Val = dword ptr 8`,
# `Size = dword ptr 0Ch`).  The `@<ebx>` and `@<fpstat>` annotations come from
# the *chunks* the dispatcher jumps into, not from the interface: the value
# printed for the `@<ebx>` slot is `0` at eight call sites and a pointer at
# others, which no real argument would be.  So call them as cdecl and drop the
# two pseudo-arguments from the call site.
#
# Every other __usercall/__userpurge callee is refused: their register
# arguments are real (`@<ecx>`, `@<xmm1>`, `@<xmm3>`) or nonsensical on i386
# (`@<sil>`), and g++ has no way to target them — it silently ignores an
# `__attribute__((usercall))`, so the call compiles and passes everything on
# the stack.
USERCALL_STACK_ONLY = {
    'sub_4349F0': ('void *', 'void *, int, unsigned int', 2),          # memset
    'sub_434980': ('void *', 'void *, const void *, unsigned int', 2), # memcpy
}

# Type names the head defines that a body may also use as a variable name.
# Hex-Rays invented the struct `Stream` for fopen's return value, and then
# happily declares `Stream *Stream;` — legal in its own output, but the second
# such declaration in a scope no longer parses once the name is a variable.
HEAD_TYPES = {'Stream'}

# Signatures for the statically-linked CRT entries the bodies call.  All are
# __cdecl, so no attribute (incdec.md §4).
CRT_PROTO = {
    'fopen':  ('FILE1 *', 'const char *, const char *'),
    'fclose': ('int', 'FILE1 *'),
    'fread':  ('unsigned int', 'void *, unsigned int, unsigned int, FILE1 *'),
    'fwrite': ('unsigned int', 'const void *, unsigned int, unsigned int, FILE1 *'),
    'fseek':  ('int', 'FILE1 *, long, int'),
    'ftell':  ('long', 'FILE1 *'),
    'feof':   ('int', 'FILE1 *'),
    'ferror': ('int', 'FILE1 *'),
    'fgetc':  ('int', 'FILE1 *'),
    'fgets':  ('char *', 'char *, int, FILE1 *'),
    'fflush': ('int', 'FILE1 *'),
    'flsall': ('int', 'int'),
    'exit':   ('void', 'int'),
    'memcpy_0': ('void *', 'void *, const void *, unsigned int'),
    'irc__print':   ('int', 'const char *, ...'),
    # The rest of the statically-linked CRT the file-handling paths reach.
    'fputc':       ('int', 'int, FILE1 *'),
    'fputs':       ('int', 'const char *, FILE1 *'),
    'remove':      ('int', 'const char *'),
    'rename':      ('int', 'const char *, const char *'),
    'tmpnam':      ('char *', 'char *'),
    '_access':     ('int', 'const char *, int'),
    '_filelength': ('long', 'int'),
    '_fileno':     ('int', 'FILE1 *'),
    '_getch':      ('int', 'void'),
    # Intel CRT, __fastcall — the one register-argument helper whose signature
    # Hex-Rays does recover, and whose call sites agree with it.
    'irc__get_msg': ('char *', 'int, int, void *'),
    '_strcmpi': ('int', 'const char *, const char *'),
}
# Variadic CRT entries: declared with ... so the call sites type-check.
CRT_VARIADIC = {'printf': ('int', 'const char *, ...'),
                'sprintf': ('int', 'char *, const char *, ...'),
                'sscanf': ('int', 'const char *, const char *, ...'),
                'fprintf': ('int', 'FILE1 *, const char *, ...'),
                'fscanf': ('int', 'FILE1 *, const char *, ...'),
                'vprintf': ('int', 'const char *, void *')}
CRT_PROTO.update(CRT_VARIADIC)

# WinAPI imports live behind a 4-byte IAT slot, not at an entry point, and
# every Win32 entry is __stdcall (incdec.md §6.4).
WINAPI_PROTO = {
    'VirtualAlloc': ('void *', 'void *, unsigned int, unsigned int, unsigned int'),
    'VirtualFree':  ('int', 'void *, unsigned int, unsigned int'),
    'GetLastError': ('unsigned int', 'void'),
    'CloseHandle':  ('int', 'void *'),
    'DeleteFileA':  ('int', 'const char *'),
    'MoveFileA':    ('int', 'const char *, const char *'),
    'SetFileAttributesA': ('int', 'const char *, unsigned int'),
    'GetFileAttributesA': ('unsigned int', 'const char *'),
    'CreateFileA': ('void *', 'const char *, unsigned int, unsigned int, void *, '
                              'unsigned int, unsigned int, void *'),
    'SetFileTime': ('int', 'void *, const void *, const void *, const void *'),
    'DosDateTimeToFileTime': ('int', 'unsigned short, unsigned short, void *'),
    'FileTimeToDosDateTime': ('int', 'const void *, unsigned short *, unsigned short *'),
    'GetFileTime': ('int', 'void *, void *, void *, void *'),
    'FindFirstFileA': ('void *', 'const char *, void *'),
    'FindNextFileA':  ('int', 'void *, void *'),
    'FindClose':      ('int', 'void *'),
}


def load():
    lines = open(SRC, errors='replace').read().split('\n')
    # --- function definition spans -----------------------------------------
    # sites.txt carries an explicit end line per function, derived from
    # Hex-Rays' own "//----- (004XXXXX) -----" banners rather than from a
    # scan for definition lines.  A regex over definition lines silently
    # misses every __usercall function (its name is followed by @<eax>, not
    # by '('), and the preceding function's span then swallows the whole
    # missed body — which is where stray '@' characters in a .inc come from.
    spans = {}
    for ln in open(os.path.join(HERE, 'sites.txt')):
        va, name, conv, dline, end = ln.rstrip('\n').split('\t')
        spans[name] = (int(dline), int(end), va, conv)

    # --- prototypes from the declaration block ------------------------------
    protos = {}
    for l in lines[:200]:
        s = l.strip()
        if not s.endswith(';') or s.startswith('//'):
            continue
        m = re.search(r'\b(' + SUB_RE + r'|main|[A-Za-z_]\w*_4[0-9A-Fa-f]{5})\s*\(', s)
        if m:
            protos[m.group(1)] = s

    # --- globals: name -> (address, base type, extent) ----------------------
    # Source of truth is symbols.txt, harvested from the
    #   "// <ADDR>: using guessed type <type> <name>;"
    # comments Hex-Rays emits after each body.  That is the only symbol table
    # BMF ships with, and crucially it covers globals whose names carry no
    # address (n0x800000, n2_4, ...) as well as the auto-named ones.
    winapi = {}
    for l in open(os.path.join(HERE, 'winapi.txt')):
        a, n = l.rstrip('\n').split('\t')
        winapi[n] = int(a, 16)

    # Per-function literal substitutions; see fixups.txt.
    fixups = {}
    fx = os.path.join(HERE, 'fixups.txt')
    if os.path.exists(fx):
        for l in open(fx):
            if l.startswith('#') or not l.strip():
                continue
            fn, find, repl, _why = l.rstrip('\n').split('\t', 3)
            fixups.setdefault(fn, []).append((find, repl))

    funcs = {}
    for l in open(os.path.join(HERE, 'funcs.txt')):
        a, n = l.rstrip('\n').split('\t')
        funcs[n] = int(a, 16)

    globals_ = {}
    for l in open(os.path.join(HERE, 'symbols.txt')):
        addr, name, base, ext = (l.rstrip('\n').split('\t') + [''])[:4]
        globals_[name] = (int(addr, 16), base, ext)

    # BMF.cpp's own "// 4456F4: using guessed type int n0x2000_1;" comments win
    # over symbols.txt.  symbols.txt is keyed by name, and Hex-Rays' names are
    # generated per run: re-decompiling the same binary renumbered the
    # `n0x2000*` family, so a name that resolved last time can be absent or —
    # worse — carry a *stale* address this time.  The comments come from the
    # decompilation being extracted, so they are always in step with it.
    for l in lines:
        gm = re.match(r'^\s*//\s*([0-9A-Fa-f]+):\s*using guessed type\s+'
                      r'(.+?)\s+([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*;\s*$', l)
        if gm and '(' not in gm.group(2):        # skip function declarations
            globals_[gm.group(3)] = (int(gm.group(1), 16), gm.group(2).strip(),
                                     gm.group(4) or '')

    # Declared extents from the data-declaration section refine the guesses.
    gstart = next(i for i, l in enumerate(lines) if l.startswith('// Data declarations'))
    noaddr = set()
    i = gstart
    while i < len(lines):
        l = lines[i]
        if re.match(r'^//-+$', l) and i > gstart + 2:
            break
        m = re.match(r'^([A-Za-z_][\w\s\*]*?)\s+([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*(;|=)', l)
        if m:
            name, ext = m.group(2), m.group(3) or ''
            if name in globals_:
                addr, base, old = globals_[name]
                globals_[name] = (addr, m.group(1).strip(), ext or old)
            elif not (re.fullmatch(r'(?:' + GLOBAL_RE + r')', name)
                      or re.fullmatch(SUB_RE, name) or name in funcs
                      or '_' + name in funcs or '__' + name in funcs):
                # Declared in the data section but with no address anywhere:
                # not in the "using guessed type" comments and no address in
                # the name.  Nothing can be referenced at a known VA.
                noaddr.add(name)
        i += 1
    return lines, spans, protos, globals_, noaddr, funcs, winapi, fixups


SSE_MEMBER_RE = re.compile(r'\.m(128i|128d|128|64)_[a-z]\w*')
SSE_WRAPPER = {'128': 'M128F', '128i': 'M128I', '128d': 'M128D', '64': 'M64'}


def wrap_intrinsic_members(line):
    """`_mm_shuffle_ps(v, v, 1).m128_f32[0]` -> `M128F(_mm_shuffle_ps(...)).m128_f32[0]`.

    An intrinsic returns GCC's bare vector type, which has no members; only the
    M128* wrappers do.  Hex-Rays reads a lane straight off a result often
    enough that rewriting the call site is worth it — the alternative, an
    overload of every intrinsic returning a wrapper, cannot be spelled (C++
    does not overload on return type).
    """
    pos = 0
    while True:
        m = SSE_MEMBER_RE.search(line, pos)
        if not m:
            return line
        pos, i = m.end(), m.start()
        if i == 0 or line[i - 1] != ')':
            continue
        depth, j = 0, i - 1               # walk back to the matching '('
        while j >= 0:
            if line[j] == ')':
                depth += 1
            elif line[j] == '(':
                depth -= 1
                if depth == 0:
                    break
            j -= 1
        if j < 0:
            continue
        k = j                             # ... and past the callee's name
        while k > 0 and (line[k - 1].isalnum() or line[k - 1] == '_'):
            k -= 1
        if not line[k:j].startswith('_mm_'):
            continue
        wrapper = SSE_WRAPPER[m.group(1)]
        line = line[:k] + wrapper + '(' + line[k:i] + ')' + line[i:]
        pos += len(wrapper) + 2


# --- __usercall / __userpurge -----------------------------------------------
# Hex-Rays prints these with an explicit register for the return value and for
# some of the arguments:
#
#     unsigned int __userpurge sub_414860@<eax>(int *a1@<ecx>, int a2@<ebx>, int a3, int a4)
#
# g++ has no attribute for that, and §4's advice — leave it alone — stops being
# an option once the goal is a binary that runs none of the original code.  So
# generate the thunk §4 mentions instead: the body is moved out as an ordinary
# cdecl function taking *all* of the arguments, and the original entry point is
# patched to a naked stub that reads the register arguments, lays them out as a
# cdecl call, and puts the result back where the caller expects it.
#
# This needs no judgement about which register arguments are "real".  If one is
# genuine the thunk forwards the caller's value; if Hex-Rays invented it (it
# does — see the memset dispatcher in USERCALL_STACK_ONLY) the thunk forwards
# whatever was in the register, which is exactly what the original body read.

GPR = {'eax': '%eax', 'ebx': '%ebx', 'ecx': '%ecx', 'edx': '%edx',
       'esi': '%esi', 'edi': '%edi', 'ebp': '%ebp'}
# 8- and 16-bit names Hex-Rays uses; the callee takes the low byte/word of the
# 4-byte slot either way, so the whole register is forwarded.
SUBREG = {'al': 'eax', 'ah': 'eax', 'ax': 'eax', 'bl': 'ebx', 'bh': 'ebx',
          'bx': 'ebx', 'cl': 'ecx', 'ch': 'ecx', 'cx': 'ecx', 'dl': 'edx',
          'dh': 'edx', 'dx': 'edx', 'si': 'esi', 'di': 'edi',
          # There is no SIL on i386; IDA means the low byte of ESI.
          'sil': 'esi', 'dil': 'edi'}
XMM = {f'xmm{i}': i for i in range(8)}
VEC_TYPES = ('__m128i', '__m128d', '__m128', '__m64', '_OWORD', '__int128')


def join_signature(body_lines):
    """Return (signature text, number of lines it spans).  Hex-Rays wraps long
    parameter lists, and every __usercall signature here is a candidate."""
    sig, n = '', 0
    for l in body_lines:
        sig += (' ' if sig else '') + l.strip()
        n += 1
        if sig.count('(') and sig.count('(') == sig.count(')'):
            return sig, n
    return body_lines[0], 1


def split_params(inner):
    """Split a parameter list on top-level commas."""
    out, depth, start = [], 0, 0
    for i, ch in enumerate(inner):
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        elif ch == ',' and depth == 0:
            out.append(inner[start:i]); start = i + 1
    if inner[start:].strip():
        out.append(inner[start:])
    return [p.strip() for p in out]


def parse_signature(sig, name):
    """-> (ret_reg or None, [(decl_without_annotation, argname, reg or None)])."""
    m = re.search(r'\b' + re.escape(name) + r'\s*(?:@<(\w+)>)?\s*\(', sig)
    ret_reg = m.group(1) if m else None
    inner = sig[m.end():sig.rindex(')')]
    params = []
    if inner.strip() and inner.strip() != 'void':
        for i, p in enumerate(split_params(inner)):
            rm = re.search(r'@<(\w+)>', p)
            reg = rm.group(1) if rm else None
            decl = re.sub(r'@<\w+>', '', p).strip()
            nm = re.search(r'([A-Za-z_]\w*)\s*(\[[^\]]*\])?$', decl)
            nm = nm.group(1) if nm else None
            if nm is None or nm in ('void',):
                nm = f'reg_arg_{i}'
                decl = decl + ' ' + nm
            params.append((decl, nm, reg))
    return ret_reg, params


MEMBER_BEFORE = re.compile(r'(?:\.|->)\s*$')

# --- stack frame reassembly -------------------------------------------------
# Hex-Rays gives every stack local its frame offset:
#
#     __m128 *v275; // [esp+Ch] [ebp-B4h] BYREF
#     __int16 *v276; // [esp+10h] [ebp-B0h]
#
# and it splits a stack *array* into consecutive scalars like that.  Usually
# harmless — but when the address of the first one escapes (BYREF) into a
# function that indexes onward, the callee is reading v276, v277, ... as
# elements.  Compiled as ordinary locals they are no longer neighbours, and the
# callee dereferences whatever happens to follow: here it faulted on a null
# three frames away, inside PE code, with nothing pointing back at the cause.
#
# So when a function has a BYREF stack local, lay all of its stack locals out
# in one buffer at exactly the offsets Hex-Rays recorded, and declare each as a
# reference into it.  That restores the original layout, which is the only
# thing the escaping address depends on.
FRAME_DECL = re.compile(
    r'^\s*(?P<type>[A-Za-z_][\w\s\*]*?)\s*\b(?P<name>[A-Za-z_]\w*)\s*'
    r'(?P<ext>\[[^\]]*\])?\s*;\s*//\s*\[esp[-+][0-9A-Fa-f]+h\]\s*'
    r'\[ebp(?P<sign>[-+])(?P<off>[0-9A-Fa-f]+)h\](?P<rest>.*)$')
BASE_SIZE = [('__m128i', 16), ('__m128d', 16), ('__m128', 16), ('_OWORD', 16),
             ('__int128', 16), ('__m64', 8), ('_QWORD', 8), ('__int64', 8),
             ('double', 8), ('long long', 8), ('_DWORD', 4), ('__int32', 4),
             ('float', 4), ('int', 4), ('long', 4), ('_WORD', 2),
             ('__int16', 2), ('short', 2), ('_BYTE', 1), ('__int8', 1),
             ('char', 1), ('bool', 1)]


def type_size(ty):
    if '*' in ty:
        return 4
    for pat, sz in BASE_SIZE:
        if re.search(r'\b' + re.escape(pat) + r'\b', ty):
            return sz
    return 4


def frame_locals(body_lines, start):
    """[(index, offset, type, name, extent)] for the stack locals, or []."""
    out = []
    for i in range(start, len(body_lines)):
        t = body_lines[i].rstrip()
        if not t.strip():
            continue
        m = FRAME_DECL.match(t)
        if m:
            off = int(m.group('off'), 16) * (1 if m.group('sign') == '+' else -1)
            out.append((i, off, m.group('type').strip(), m.group('name'),
                        m.group('ext') or '', 'BYREF' in m.group('rest')))
        elif re.match(r'^\s*[A-Za-z_][\w\s\*]*\b[A-Za-z_]\w*\s*(\[[^\]]*\])?\s*;', t):
            continue                     # a register local; keep scanning
        else:
            break                        # first statement
    return out


ASM = os.path.join(HERE, 'BMF.asm')
_ASM_RANGES = None

# Anything that computes in double precision, or converts between the two.
DOUBLE_OP = re.compile(
    r'^\s*(?:addsd|subsd|mulsd|divsd|sqrtsd|minsd|maxsd|comisd|ucomisd'
    r'|cvtss2sd|cvtsd2ss|cvtsi2sd|cvtsd2si|cvttsd2si|cvtps2pd|cvtpd2ps'
    r'|addpd|subpd|mulpd|divpd|movsd|movapd|movupd|unpcklpd|shufpd'
    r'|fld|fadd|fsub|fmul|fdiv|fstp|fild|fistp)\b', re.I)


def single_precision(name):
    """True if `name`'s machine code has no double-precision float in it.

    Hex-Rays prints every floating constant as a decimal `double` literal —
    `* 0.001`, `+ 576.0` — even where the instruction is `mulss`/`addss` and
    the constant in .rdata is a four-byte float.  Under C's usual arithmetic
    conversions `float * double` is computed in double and rounded back, which
    is a different result from the single-precision multiply the original did.
    In a compressor that shows up as a slightly worse stream rather than a
    crash, which is why it survives every correctness check.

    Reading it back off the disassembly rather than guessing: if the function
    contains no `*sd`, no `cvt*` between the two widths and no x87, then every
    floating literal in its body is a float.
    """
    global _ASM_RANGES
    if _ASM_RANGES is None:
        _ASM_RANGES = {}
        # Loudly, not silently: without the disassembly this returns False for
        # every function and the float-literal correction quietly stops
        # happening, which costs compression ratio and nothing else — exactly
        # the kind of failure that takes days to notice.
        lines = open(ASM, errors='replace').read().split('\n')
        start = {}
        for i, l in enumerate(lines):
            m = re.match(r'^[0-9A-F]{8}\s+(\S+)\s+proc\s+near', l)
            if m:
                start[m.group(1)] = i
                continue
            m = re.match(r'^[0-9A-F]{8}\s+(\S+)\s+endp\b', l)
            if m and m.group(1) in start:
                _ASM_RANGES[m.group(1)] = (start.pop(m.group(1)), i)
        _ASM_RANGES['__lines'] = lines
    lines = _ASM_RANGES.get('__lines') or []
    rng = _ASM_RANGES.get(name)
    if not rng:
        return False                      # unknown: leave the body alone
    a, b = rng
    for l in lines[a:b]:
        # Strip the address column and IDA's trailing comment.
        if DOUBLE_OP.match(l[16:].split(';')[0]):
            return False
    return True


FLOAT_LIT = re.compile(r'(?<![\w.])(\d+\.\d*(?:[eE][-+]?\d+)?|\.\d+(?:[eE][-+]?\d+)?)'
                       r'(?![\w.])')


def floatify(text):
    """Suffix every floating literal with `f`.  Skips string/char literals."""
    lit = [(m.start(), m.end()) for m in
           re.finditer(r'"(?:[^"\\]|\\.)*"' + r"|'(?:[^'\\]|\\.)*'", text)]
    out, pos = [], 0
    for m in FLOAT_LIT.finditer(text):
        if any(a <= m.start() < b for a, b in lit):
            continue
        out.append(text[pos:m.end()]); out.append('f'); pos = m.end()
    out.append(text[pos:])
    return ''.join(out)


def addr_taken(body_lines, locs):
    """True if the body takes the address of one of its stack locals.

    Hex-Rays' `BYREF` marker only appears when the address is *passed* to
    something.  When the function instead walks the frame itself —

        void *Block;              // [esp+24h] [ebp-5Ch]
        unsigned __int8 **v102;   // [esp+28h] [ebp-58h]
        ...
        *(&Block + n4++) = v7;    // four consecutive slots, one array

    — there is no marker, but the neighbours matter exactly as much: the
    locals are one stack array Hex-Rays split into scalars, and compiled as
    ordinary locals they stop being neighbours.  Treat any `&local` as a
    reason to reassemble the frame.
    """
    if not locs:
        return False
    start = max(i for i, *_ in locs) + 1
    text = '\n'.join(body_lines[start:])
    for _i, _o, _t, nm, _e, _b in locs:
        for m in re.finditer(r'&\s*' + re.escape(nm) + r'\b', text):
            before = text[:m.start()].rstrip()
            # `a & b` is a bitwise and, `f(&b)` and `*(&b + 1)` are not.
            if before and (before[-1].isalnum() or before[-1] in '_)]&'):
                continue
            return True
    return False


def build_frame(locs):
    """-> (lines declaring the buffer and the references, set of indices to drop)."""
    lo = min(o for _, o, *_ in locs)
    hi = 0
    for _, o, ty, nm, ext, _by in locs:
        n = 1
        if ext:
            m = re.match(r'\[\s*([0-9]+)\s*\]', ext)
            n = int(m.group(1)) if m else 1
        hi = max(hi, o + n * type_size(ty))
    size = hi - lo + 16
    out = [f"  alignas(16) unsigned char __hexrays_frame[{size}];   "
           f"// original frame, ebp{lo:+#x}..ebp{hi:+#x}"]
    for _, o, ty, nm, ext, _by in locs:
        at = f"__hexrays_frame + {o - lo}"
        if ext:
            out.append(f"  {ty} (&{nm}){ext} = *({ty} (*){ext})({at});")
        else:
            out.append(f"  {ty} &{nm} = *({ty} *)({at});")
    return out, {i for i, *_ in locs}



def fix_hex_escapes(line):
    r"""Terminate a `\xHH` escape that is followed by another hex digit.

    Hex-Rays merges adjacent .rdata strings into one literal and prints
    non-printable bytes as `\x`.  Where the next byte happens to be an ASCII
    hex digit the two run together, and C's `\x` escape is *greedy* — it eats
    every hex digit it can reach:

        fwrite("\x81\x8A20\x81\x9020a+b", 4u, 1u, f)

    is `\x8A20`, one escape with the value 0x8A20, which does not fit in a
    char.  g++ warns and truncates, so the four bytes written are `81 20 81 0a`
    rather than the `81 8A 32 30` the compressor's file header needs — and the
    only symptom is that nothing can read the archive back.

    An empty string literal ends the escape and concatenates away.
    """
    lit = [(m.start(), m.end()) for m in
           re.finditer(r'"(?:[^"\\]|\\.)*"' + r"|'(?:[^'\\]|\\.)*'", line)]
    if not lit:
        return line
    out, pos = [], 0
    for m in re.finditer(r'\\x[0-9A-Fa-f]{2}(?=[0-9A-Fa-f])', line):
        if not any(a <= m.start() < b for a, b in lit):
            continue
        out.append(line[pos:m.end()]); out.append('""'); pos = m.end()
    out.append(line[pos:])
    return ''.join(out)


PTR_LOCAL = re.compile(r'^\s*([A-Za-z_][\w\s]*?\*)\s*(\w+)\s*;')


def launder_pointer_counters(body):
    """Step a pointer that is also tested for truth through `uintptr_t`.

    Hex-Rays types a *register*, so a register that holds a pointer somewhere
    in the function is typed as one everywhere — including where it is a plain
    loop counter:

        char *v112;
        ...
        v112 = v105;            // a byte count
        do { ...; --v112; } while ( v112 );

    Subtracting from a pointer cannot produce a null pointer in C, so g++
    folds the test to `true`: the loop's back edge becomes an unconditional
    `jmp` with no test at all and the body walks off the end of whatever it is
    copying.  Nothing warns, and no `-fno-…` switch turns the inference off.

    Rewriting the *step* rather than the test is what actually works.  A
    pointer produced by casting an integer may legitimately be null, so once
    the arithmetic goes through `uintptr_t` there is nothing left for g++ to
    infer.  On i386 it is the same `dec`.

    Only variables that are both stepped and truth-tested are touched, which
    is seven of them across four functions here; `*p++` in an expression is
    left alone, since a pointer being dereferenced is not the one at risk.
    """
    text = '\n'.join(body)
    ptr = {}
    for l in body:
        m = PTR_LOCAL.match(l)
        if m:
            ptr[m.group(2)] = m.group(1).strip()
    out = list(body)
    for v, ty in sorted(ptr.items()):
        e = re.escape(v)
        if not re.search(r'(?:while|if)\s*\(\s*!?\s*' + e + r'\s*\)', text):
            continue
        step = type_size(ty[:-1].strip())
        scale = '' if step == 1 else f' * {step}'
        subs = [
            (re.compile(r'^(\s*)(?:--\s*' + e + r'|' + e + r'\s*--)\s*;\s*$'),
             lambda m: f"{m.group(1)}{v} = ({ty})((uintptr_t){v} - {step});"),
            (re.compile(r'^(\s*)(?:\+\+\s*' + e + r'|' + e + r'\s*\+\+)\s*;\s*$'),
             lambda m: f"{m.group(1)}{v} = ({ty})((uintptr_t){v} + {step});"),
            (re.compile(r'^(\s*)' + e + r'\s*([-+])=\s*(.+);\s*$'),
             lambda m: f"{m.group(1)}{v} = ({ty})((uintptr_t){v} {m.group(2)} "
                       f"({m.group(3)}){scale});"),
            # The form Hex-Rays uses when the step is in bytes but the pointer
            # is not a `char *`: `v43 = (unsigned __int16 *)((char *)v43 - 1)`.
            (re.compile(r'^(\s*)' + e + r'\s*=\s*\(([^()]*\*)\)\(\(char \*\)'
                        + e + r'\s*([-+])\s*([^;]+)\);\s*$'),
             lambda m: f"{m.group(1)}{v} = ({m.group(2)})((uintptr_t){v} "
                       f"{m.group(3)} ({m.group(4)}));"),
        ]
        for i, l in enumerate(out):
            for pat, rep in subs:
                m = pat.match(l)
                if m:
                    out[i] = rep(m)
                    break
    return out


def mask_shift_counts(line):
    """`x >> n` -> `x >> (n & 31)` for every count that is not a literal.

    x86 masks a variable shift count to five bits; C++ leaves a count outside
    0..31 undefined; and Hex-Rays prints exactly what the instruction computes.
    Three shapes come out of that, all of them undefined and all of them
    silently miscompiled:

        0xFFFFFFFF >> -*((_BYTE *)this + 8)   neg ecx; shr ebp, cl
        1 << (n + 31)                         lea ecx, [edi+1Fh]; shl ebx, cl
        3 << v91                              a plain byte from a file header

    The third is the reason this is applied to every non-literal count rather
    than to the two recognisable idioms.  `v91` is a header byte whose low six
    bits are the pixel depth and whose top bit is a flag: `0x81` for a 1bpp
    image with a palette.  `3 << 0x81` is `3 << 1` on the hardware — six bytes
    of palette — and g++ made it 0, so the palette was never skipped, the next
    header read landed in the middle of the file, and BMF reported "bad file!"
    after writing an image whose second palette entry was black.

    Masking is a no-op wherever the count is already in range: g++ knows x86
    masks and emits the same `shl %cl`.  So there is no reason to be selective,
    and being selective is what let the third shape through.

    The count of a shift is an additive-expression — `* / % + -` bind tighter,
    everything else binds looser — so the term ends at the first `< > = ! & ^ |
    ? : , ;` that is a *binary* operator at paren depth zero.

    Only correct for 32-bit shifts.  Every variable-count shift in this donor
    is one; a 64-bit shift would need `& 63` and there are none to check for.
    """
    lit = [(m.start(), m.end()) for m in
           re.finditer(r'"(?:[^"\\]|\\.)*"' + r"|'(?:[^'\\]|\\.)*'", line)]
    cut = len(line)
    for m in re.finditer(r'//', line):
        if not any(a <= m.start() < b for a, b in lit):
            cut = m.start()
            break
    out, i, n = [], 0, len(line)
    pat = re.compile(r'(<<|>>)=?')
    while True:
        m = pat.search(line, i)
        if not m or m.start() >= cut:
            out.append(line[i:])
            return ''.join(out)
        if any(a <= m.start() < b for a, b in lit):
            out.append(line[i:m.end()]); i = m.end(); continue
        j = m.end()
        while j < n and line[j] == ' ':
            j += 1
        start, depth = j, 0
        while j < cut:
            c = line[j]
            if c in '([':
                depth += 1
            elif c in ')]':
                if depth == 0:
                    break
                depth -= 1
            elif depth == 0 and c in '<>=!&^|?:,;':
                if c == ':' and (line[j:j + 2] == '::' or
                                 (j and line[j - 1] == ':')):
                    j += 1
                    continue
                # A *binary* operator ends the term.  `&x`, `->y` and a unary
                # `!` follow an operator or an opening bracket, not an operand.
                k = j - 1
                while k >= start and line[k] == ' ':
                    k -= 1
                if k < start or not (line[k].isalnum() or line[k] in '_)]'):
                    j += 1
                    continue
                break
            j += 1
        term = line[start:j].rstrip()
        if not term or re.fullmatch(r'(?:0[xX][0-9A-Fa-f]+|\d+)[uUlL]*', term):
            out.append(line[i:start + len(term)])
            i = start + len(term)
            continue
        out.append(line[i:m.end()])
        out.append(' (' + term + ' & 31)')
        i = start + len(term)

def rename_ident(text, name, repl):
    """Rename `name` to `repl`, but not where it is a struct member.

    A `#define name repl` cannot tell `dwLowDateTime` the global from
    `FileTime.dwLowDateTime` the member, and BMF has several globals whose
    names collide with a field of a Win32 struct the same body uses.  The
    qualified form `::name` is renamed — that is the global, spelled explicitly
    because a local shadows it.
    """
    # Positions inside a string or character literal are off limits: a global
    # whose name also appears in one of BMF's messages would otherwise have the
    # message rewritten along with the code.
    lit = []
    for m in re.finditer(r'"(?:[^"\\]|\\.)*"' + r"|'(?:[^'\\]|\\.)*'", text):
        lit.append((m.start(), m.end()))
    out, pos = [], 0
    for m in re.finditer(r'\b' + re.escape(name) + r'\b', text):
        if any(a <= m.start() < b for a, b in lit):
            continue
        if MEMBER_BEFORE.search(text[max(0, m.start() - 4):m.start()]):
            continue
        out.append(text[pos:m.start()]); out.append(repl); pos = m.end()
    out.append(text[pos:])
    return ''.join(out)


def split_decl(decl):
    """`_DWORD *a1` -> ('_DWORD *', 'a1');  `int` -> ('int', None)."""
    m = re.match(r'^(.*?[\s\*])([A-Za-z_]\w*)$', decl.strip())
    return (m.group(1).strip(), m.group(2)) if m else (decl.strip(), None)


def callee_signature(lines, spans, fixups, name):
    """A callee's own signature, with that callee's fixups applied.

    A fixup can correct the *signature* — sub_402EF0 is typed `__stdcall` by
    IDA and actually takes a third argument in ecx (§8.2.4.1) — and every
    reader of that signature has to see the correction, not just the body it
    is emitted into.  Reading the raw donor line here builds a forwarder with
    the wrong arity and the call goes out one slot short.
    """
    a, b = spans[name][0], spans[name][1]
    src = '\n'.join(lines[a - 1:b])
    for find, repl in fixups.get(name, []):
        src = src.replace(find, repl)
    return join_signature(src.split('\n'))


def moved_callee_wrapper(caller, callee, sig, ret_reg, params):
    """A `void *`-taking forwarder for a call to an already-moved function.

    §6.3 maps the call straight onto the moved body, which then type-checks
    against the callee's *own* signature — and Hex-Rays routinely spells the
    same pointer differently at the call site (`unsigned char **` there,
    `_DWORD *` in the definition).  Relaxing the parameter to `void *` and
    casting inside accepts every spelling and reaches the callee unchanged.
    Non-pointer parameters keep their type, so nothing is promoted.
    """
    ret = sig[:sig.index(callee)]
    for k in ('__usercall', '__userpurge', '__cdecl', '__stdcall',
              '__fastcall', '__thiscall', '__noreturn'):
        ret = ret.replace(k, '')
    ret = ' '.join(ret.split()) or 'int'
    # Same rewrite as the parameters below: the moved callee is declared with
    # FILE1, so a forwarder returning `FILE **` does not match it.
    ret = re.sub(r'\bFILE\b', 'FILE1', ret)
    ret = re.sub(r'\bStream\b', 'FILE1', ret)
    args, casts = [], []
    for i, (decl, nm, reg) in enumerate(params):
        t, _ = split_decl(decl)
        # The forwarder sits outside the `#define FILE FILE1` scope, and
        # `Stream` is Hex-Rays' invented name for the same struct.
        t = re.sub(r'\bFILE\b', 'FILE1', t)
        t = re.sub(r'\bStream\b', 'FILE1', t)
        a = f"a{i}"
        if reg in XMM:
            # §4.2 passes a vector register argument by reference so the
            # thunk's stack slot stays four bytes; the forwarder has to
            # match that, and there is nothing to relax.
            args.append(f"const {t} &{a}"); casts.append(a)
        elif '*' in t and '(' not in t:
            args.append(f"void *{a}"); casts.append(f"({t}){a}")
        else:
            args.append(f"{t} {a}"); casts.append(a)
    call = f"__{callee}({', '.join(casts)})"
    body = f"{'' if ret == 'void' else 'return '}{call};"
    return [f"static inline {ret} __fwd_{caller}_{callee}({', '.join(args) or 'void'})"
            f" {{ {body} }}",
            f"#define {callee} __fwd_{caller}_{callee}"]


def make_thunk(name, va, conv, params, ret_reg):
    """Emit the naked stub that goes at the original entry point."""
    stack = [p for p in params if p[2] is None]
    pop = 4 * len(stack) if conv == 'userpurge' else 0

    # Scratch frame: one 4-byte slot per register argument, 16 per vector.
    slot, size = {}, 0
    for decl, nm, reg in params:
        if reg is None:
            continue
        if reg in XMM:
            size = (size + 15) & ~15
            slot[nm] = size; size += 16
        else:
            slot[nm] = size; size += 4
    size = (size + 15) & ~15
    # The i386 ABI wants esp 16-byte aligned at the call, and code compiled for
    # it assumes that — a moved body that spills an __m128 to the stack uses an
    # aligned store.  Nothing in the PE maintains that, so the thunk imposes it
    # with `and $-16` and then pads so the argument pushes land back on 16.
    pad = (-4 * len(params)) % 16
    frame = size + pad          # both multiples of 4; `and` already aligned esp

    a = ["push %ebp", "mov %esp, %ebp", "push %ebx", "push %esi", "push %edi",
         "and $-16, %esp"]
    if frame:
        a.append(f"sub ${frame}, %esp")

    # Scratch is esp-relative, so every offset has to account for the pushes
    # made since: `at(nm, p)` is where slot nm sits after p pushes.
    def at(nm, p):
        return f"{pad + slot[nm] + 4 * p}(%esp)"

    # Capture before anything is clobbered.  EAX goes first because fnstsw
    # needs it, and the XMM captures come after the general registers.
    caps = [(nm, reg) for _, nm, reg in params if reg]
    for nm, reg in sorted(caps, key=lambda t: (t[1] != 'eax', t[1] in XMM,
                                               t[1] == 'fpstat')):
        g = GPR.get(SUBREG.get(reg, reg))
        if g:
            a.append(f"mov {g}, {at(nm, 0)}")
        elif reg in XMM:
            a.append(f"movups %xmm{XMM[reg]}, {at(nm, 0)}")
        elif reg == 'fpstat':
            a.append("fnstsw %ax")
            a.append(f"mov %eax, {at(nm, 0)}")
        else:
            raise SystemExit(f"{name}: no way to read argument register @<{reg}>")

    # Push right to left.  Stack arguments are still in the caller's frame at
    # [ebp+8+4i] and are reached through ebp, which the pushes do not move.
    # A vector argument is passed by reference, so every slot stays four bytes
    # and the 16-byte alignment __m128-by-value would need never arises.
    si, p = len(stack) - 1, 0
    for decl, nm, reg in reversed(params):
        if reg is None:
            a.append(f"push {8 + 4 * si}(%ebp)"); si -= 1
        elif reg in XMM:
            a.append(f"lea {at(nm, p)}, %eax")
            a.append("push %eax")
        else:
            a.append(f"push {at(nm, p)}")
        p += 1
    a.append(f"call __{name}")
    a.append("lea -12(%ebp), %esp")
    a.append("pop %edi"); a.append("pop %esi"); a.append("pop %ebx")
    a.append("leave")
    a.append(f"ret ${pop}" if pop else "ret")

    body = '\n'.join(f'    "{i}\\n"' for i in a)
    return [
        f"// __{conv} thunk for {name} @ 0x{va}: reads the register arguments the",
        f"// caller passes, calls the moved body as cdecl, "
        + (f"and pops {pop} bytes of" if pop else "and lets the caller clean the"),
        f"// stack on return.",
        f"BMF_SSE __attribute__((naked)) static void __thunk_{name}()",
        "{",
        "  __asm__ volatile(",
        body,
        "  );",
        "}",
        "",
    ]


def drop_leading_args(text, name, n):
    """`sub_4349F0(a, b, X, Y, Z)` -> `sub_4349F0(X, Y, Z)`, calls may span lines."""
    out, pos = [], 0
    for m in re.finditer(r'\b' + re.escape(name) + r'\s*\(', text):
        if m.start() < pos:
            continue
        i = m.end()
        depth, start, args = 1, i, []
        while i < len(text) and depth:
            ch = text[i]
            if ch in '([':
                depth += 1
            elif ch in ')]':
                depth -= 1
                if not depth:
                    args.append(text[start:i])
                    break
            elif ch == ',' and depth == 1:
                args.append(text[start:i])
                start = i + 1
            i += 1
        if depth or len(args) <= n:
            continue                      # unbalanced or too few: leave alone
        out.append(text[pos:m.end()])
        out.append(','.join(a.strip() for a in args[n:]))
        pos = i
    out.append(text[pos:])
    return ''.join(out)


def array_used(body, name, shadowed=False):
    """True if *this* body indexes the global — decides array vs scalar typedef.

    Per body, not across all of BMF.cpp.  A global with no declared extent that
    some other function indexes is still a plain scalar as far as this one is
    concerned, and typing it `int[0x10000]` here makes every use of it a
    non-lvalue array ("invalid operands of types 'int' and 'int [65536]'").

    \\b matters: without it `p_n15[3]` — a *parameter* Hex-Rays named after the
    global it usually receives — counts as indexing the global n15.  And when a
    local shadows the global outright (`unsigned __int16 *n4_3;` alongside
    `::n4_3 = n4_7;`), only the qualified uses are the global's.
    """
    pat = (r'::\s*' if shadowed else r'\b') + re.escape(name) + r'\s*\['
    return re.search(pat, body) is not None


def emit(args, cache=None):
    # A hand-written override wins over the Hex-Rays body.  incdec.md §4 only
    # requires the redirected function to be *behaviourally* identical, not
    # textually derived from the decompilation, and a few bodies are inline
    # asm the decompiler could not lift into C at all (see override/README).
    ovr = os.path.join(HERE, 'override', args.name + '.inc')
    if os.path.exists(ovr):
        dest = args.out or os.path.join(HERE, 'inc', args.name + '.inc')
        os.makedirs(os.path.dirname(dest), exist_ok=True)
        text = open(ovr).read()
        # A __usercall override still needs its entry-point thunk, and there is
        # no reason to hand-write that: the override supplies the body with the
        # signature §4.2 expects, and the generated stub goes on the end.
        lines, spans, protos, _g, _na, _f, _w, fixups = cache or load()
        if args.name in spans and spans[args.name][3] in ('usercall', 'userpurge'):
            a, b, va, conv = spans[args.name]
            # Through fixups.txt like any other body: a corrected *signature*
            # is exactly what an override is often for, and the thunk has to
            # be built from the corrected one.
            sig, _n = callee_signature(lines, spans, fixups, args.name)
            ret_reg, sig_params = parse_signature(sig, args.name)
            text += '\n' + '\n'.join(make_thunk(args.name, va, conv,
                                                 sig_params, ret_reg)) + '\n'
        open(dest, 'w').write(text)
        print(f"{dest}: hand-written override ({ovr})")
        return

    lines, spans, protos, globals0, noaddr, funcs, winapi, fixups = cache or load()
    globals_ = dict(globals0)   # emit() adds address-derived entries; keep the
                                # cache clean for the next name in a batch.
    if args.name not in spans:
        sys.exit(f"no such function: {args.name}")
    a, b, va, conv = spans[args.name]

    body_lines = lines[a - 1:b]
    # Hex-Rays closes each body with its own per-function view of the globals it
    # touched:  "// 443398: using guessed type int n256_0;".  That is the
    # authoritative typing for *this* body and it can disagree with the
    # declaration section, which is the union of every use across the image —
    # `int n256_0[];` there, but plain `int` here, and the array form does not
    # compile against `4 * n256_0`.  Collected before the trailing comments are
    # trimmed off below.
    per_body = {}
    for l in body_lines:
        gm = re.match(r'^\s*//\s*[0-9A-Fa-f]+:\s*using guessed type\s+'
                      r'(.+?)\s+([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*;\s*$', l)
        if gm:
            per_body[gm.group(2)] = (gm.group(1).strip(), gm.group(3) or '')
    # The span runs to the line before the next definition, which sweeps up
    # that definition's "//----- (004123 40) ----" banner and any blank lines.
    # Cut back to the last line of actual code.
    while body_lines and (not body_lines[-1].strip()
                          or re.match(r'^//-+\s*\(?[0-9A-Fa-f]*\)?\s*-*$', body_lines[-1].strip())
                          or body_lines[-1].lstrip().startswith('//')):
        body_lines.pop()
    # Literal substitutions from fixups.txt, applied against the donor text so
    # the `find` strings can be grepped for in BMF.cpp.  A fixup that no longer
    # matches is an error, not a silent no-op: the donor gets re-decompiled and
    # a stale one would quietly stop being applied.
    for find, repl in fixups.get(args.name, ()):
        hit = sum(l.count(find) for l in body_lines)
        if not hit:
            sys.exit(f"{args.name}: fixups.txt entry no longer matches the "
                     f"donor body: {find!r}")
        body_lines = [l.replace(find, repl) for l in body_lines]
    body_raw = '\n'.join(body_lines)
    # Reference detection must look at code only.  Hex-Rays appends
    # "// <addr>: using guessed type <t> <name>;" lines to each body, so a
    # comment-only mention would otherwise register as a real reference —
    # and, for an address-less name, wrongly refuse the whole function.
    body = re.sub(r'//[^\n]*', '', body_raw)
    # Drop string and character literals too — BMF's messages contain things
    # like "function(" and the scan below would read them as calls.
    body = re.sub(r'"(?:[^"\\]|\\.)*"', '""', body)
    body = re.sub(r"'(?:[^'\\]|\\.)*'", "' '", body)

    already = set()
    if os.path.exists(args.accepted):
        for l in open(args.accepted):
            if l.strip():
                already.add(l.split()[1])

    # --- locals -------------------------------------------------------------
    # Hex-Rays declares every local right after the opening brace, one per
    # line, with a register/stack comment.  A name declared there is NOT a
    # global reference even when a same-named global exists — BMF has several
    # such collisions (n256_0, buf_0, n0x800000, ...).  The exception is an
    # explicit `::name`, which reaches past the local to the global; in that
    # case both are renamed together and the qualification still resolves.
    # The parameter list counts: BMF has globals named Count, Destination,
    # Buffer, Str, ... and Hex-Rays reuses exactly those names for parameters.
    # Without this, `#define Destination __Destination` rewrites the parameter
    # in the signature and the function is redefined against a global instead.
    locals_ = set()
    sig_text, nsig = join_signature(body_lines)
    ret_reg, sig_params = parse_signature(sig_text, args.name)
    for _decl, _nm, _reg in sig_params:
        locals_.add(_nm)
    for l in body_lines[nsig:]:
        t = l.strip()
        if not t or t == '{':
            continue
        if t.startswith('//'):
            continue
        m = re.match(r'^[A-Za-z_][\w\s\*]*?\b([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*;\s*(//.*)?$', t)
        if not m:
            # Function-pointer locals — `void (__cdecl *sub_42BB20_1)(int, int);`
            # — do not match the plain form, and breaking here would lose every
            # local declared after one of them.
            m = re.match(r'^[A-Za-z_][\w\s\*]*\(\s*[\w\s]*\*\s*([A-Za-z_]\w*)\s*\)'
                         r'\s*\([^;]*\)\s*;\s*(//.*)?$', t)
        if m:
            locals_.add(m.group(1))
        else:
            break          # first statement: declarations are over
    def is_global_ref(n):
        if n not in locals_:
            return True
        return re.search(r'::\s*' + re.escape(n) + r'\b', body) is not None

    # --- classify every external reference ---------------------------------
    # Callees are not all `sub_XXXXXX`: Hex-Rays also names functions after
    # what they do plus their address (`exit_402E40`, `nullsub_1_401000`), and
    # those need the same PE-address typedef.  Data symbols share the shape, so
    # exclude anything matching the auto-named-global pattern.
    called = set(re.findall(r'\b(' + SUB_RE + r')\s*\(', body))
    called |= {c for c in re.findall(r'\b([A-Za-z_]\w*_4[0-9A-Fa-f]{5})\s*\(', body)
               if not re.fullmatch(GLOBAL_RE, c)}
    # A function is not always referenced by calling it.  Hex-Rays passes them
    # as pointers (`(void (__cdecl *)(int, int, int, int))::sub_42BB20`), and
    # it also names *locals* after the function they hold — `void *sub_428BE0;`
    # next to `::sub_428BE0` — so the name has to be declared either way for
    # the qualified form to resolve.
    called |= {c for c in re.findall(r'\b([A-Za-z_]\w*)\b', body)
               if c in spans and c != args.name}
    # And a function IDA could not decompile at all still has to be declared:
    # sub_402E30 is `push 7; call exit_402E40` — two instructions, the
    # out-of-memory handler — and Hex-Rays emitted `#error "call analysis
    # failed"` in place of a body, so it is in funcs.txt but not in sites.txt.
    # main hands its address to the CRT's set_new_handler.
    no_body = sorted(c for c in set(re.findall(r'\b(' + SUB_RE + r')\b', body))
                     if c not in spans and c != args.name and c in funcs)
    refd_globals = {g for g in globals_
                    if re.search(r'\b' + re.escape(g) + r'\b', body) and is_global_ref(g)}
    for g in set(re.findall(r'\b(' + GLOBAL_RE + r')\b', body)):
        if not is_global_ref(g):
            continue
        if g not in globals_:
            globals_[g] = (int(g.split('_')[-1], 16),
                           PREFIX_TYPE.get(g.split('_')[0], 'unsigned char'), '')
        refd_globals.add(g)
    hit_noaddr = sorted(n for n in noaddr
                        if re.search(r'\b' + re.escape(n) + r'\b', body) and is_global_ref(n))
    unresolved = set()
    win = {}
    crt = {}                      # body name -> (asm name, addr)
    for m in re.finditer(r'\b([A-Za-z_]\w*)\s*\(', body):
        n = m.group(1)
        if n == args.name:
            continue          # the definition line itself, or a recursive call
        if n in locals_ and not re.search(r'::\s*' + re.escape(n) + r'\b', body):
            continue          # indirect call through a local function pointer
        if INTEL_CRT.match(n) and n not in spans:
            # `n in spans` means it is a real BMF function with a decompiled
            # body — __svml_log2_w is `call ___svml_log2; retn`, and once moved
            # it is an ordinary moved callee, not a CRT entry to declare.
            # Resolve here rather than falling through: INTRIN's `__` branch
            # below would otherwise swallow these before they reach the CRT
            # lookup.
            if n in XMM0_CRT:
                continue                  # supplied by dummy32_head.cpp
            hit = next((c for c in (n, '_' + n, '__' + n) if c in funcs), None)
            if n in CRT_PROTO and hit:
                crt[n] = (hit, funcs[hit])
            else:
                unresolved.add(n + ' (register-argument Intel CRT helper, '
                                   'no signature recovered)')
            continue
        if n in CTRL or INTRIN.match(n) or n in PURE_LIBC:
            continue
        if re.fullmatch(SUB_RE, n) or re.fullmatch(r'[A-Za-z_]\w*_4[0-9A-Fa-f]{5}', n):
            continue
        if n in ('operator', 'new', 'delete'):
            continue              # operator new/delete, handled below
        if n in winapi and n in WINAPI_PROTO:
            win[n] = winapi[n]
            continue
        hit = next((c for c in (n, '_' + n, '__' + n) if c in funcs), None)
        if hit and n in CRT_PROTO:
            crt[n] = (hit, funcs[hit])
        else:
            unresolved.add(n)
    # operator new / delete are keyword pairs the preprocessor cannot rename,
    # so the call sites are rewritten to plain identifiers (§8.4-B).
    uses_new = re.search(r'\boperator new\b', body) is not None
    uses_del = re.search(r'\boperator delete\b', body) is not None
    if (uses_new and '??2@YAPAXI@Z' not in funcs) or (uses_del and '??3@YAXPAX@Z' not in funcs):
        unresolved.add('operator new/delete')
    # A __usercall callee is fine once it has been moved: the call then goes to
    # the cdecl body directly (§6.3) and the thunk at the original entry point
    # is only there for callers still living in the PE.  Until then it is not,
    # and g++ gives no warning that would tell you.
    bad_conv = sorted(c for c in called
                      if c != args.name and c not in already
                      and spans.get(c, (0, 0, 0, ''))[3] in ('usercall', 'userpurge')
                      and c not in USERCALL_STACK_ONLY)
    if bad_conv:
        sys.exit(f"{args.name} calls __usercall/__userpurge functions that have "
                 f"not been moved yet, whose register arguments g++ cannot "
                 f"target (the attribute is silently ignored and everything "
                 f"goes on the stack): {bad_conv}")
    if hit_noaddr:
        sys.exit(f"{args.name} references globals with no recoverable address "
                 f"(declared in BMF.cpp but absent from the 'using guessed type' "
                 f"comments): {hit_noaddr}")
    if unresolved:
        sys.exit(f"{args.name} references unresolvable symbols "
                 f"(no symbol table for BMF's static CRT): {sorted(unresolved)}")

    out = []
    out.append(f"// {args.name} @ 0x{va} — __{conv}")
    out.append(f"// Extracted from BMF.cpp:{a}-{b} by extract.py per incdec.md.")
    out.append("")

    # --- globals (§6.1) -----------------------------------------------------
    for g in sorted(refd_globals):
        addr, base, ext = globals_[g]
        # This body's own "using guessed type" comment wins over the declaration
        # section (see above).  Indexing in the body overrides both: `(__m128)
        # xmmword_445760[6 * n2]` needs an array however the object was
        # declared.  What must *not* happen is demoting a declared array to a
        # scalar on the strength of "this body never wrote a [": `buf = buf_0;`
        # is the array decaying to a pointer, and as a scalar it silently reads
        # one byte of image instead.
        if re.fullmatch(GLOBAL_RE, g):
            # An auto-generated name states its own width, and Hex-Rays picks
            # the name by how *this* body accesses the address: `byte_445714`
            # is a byte load even where the declaration section calls the same
            # address an int.  symbols.txt, harvested from the disassembly,
            # types every one of these `int` — 369 of them — so it must not
            # win.  Getting this wrong is silent: `byte_445714[4 * v3]` typed
            # `int[]` reads four bytes at four times the stride, which is not a
            # crash, just wrong data.
            base = PREFIX_TYPE.get(g.split('_')[0], base)
        if g in per_body:
            base, ext = per_body[g]
        if array_used(body, g, g in locals_):
            # An unspecified bound cannot be used as *(T*)addr; pick one large
            # enough to leave indexing unconstrained.  No storage is created —
            # the type only reinterprets the PE image.
            if ext in ('', '[]'):
                ext = '[0x10000]'
        elif ext == '[]':
            ext = '[0x10000]'
        elif ext and g not in per_body:
            # The mirror of the widening above, and for the same reason: an
            # extent symbols.txt got from *another* body is not this one's.
            # `dword_4410A4` is `int[6]` to main, which writes `dword_4410A4[0]`,
            # and a plain scalar to sub_4043E0, which writes
            # `dword_4410A4 = (n4_5 << 16) | ...` and reads `HIWORD(dword_4410A4)`.
            # Same four bytes; only one of the two spellings compiles against a
            # given declaration.
            ext = ''
        if not base:
            base = PREFIX_TYPE.get(g.split('_')[0], 'unsigned char')
        # The alias is scoped to this function, not shared across the
        # translation unit.  A shared `__<g>` behind an include guard lets
        # whichever body is included first fix the type for all of them, and
        # since the type is derived per body that is routinely the wrong one —
        # `n256` is `char[]` to one function and `unsigned short *` to the next,
        # and `xmmword_445760` is a scalar in one body and an array in another.
        t = f"t_{args.name}_{g}"
        out.append(f"typedef {base} {t}{ext};")
        out.append(f"static {t}& __{args.name}_{g} = *({t}*)0x{addr:08X};")
        # Renamed in the body below rather than with a #define: the
        # preprocessor would also rewrite `FileTime.dwLowDateTime`.
    if refd_globals:
        out.append("")

    # --- callees still living in the PE (§6.2) ------------------------------
    for c in no_body:
        out.append(f"#ifndef __PE_DECL___{c}")
        out.append(f"#define __PE_DECL___{c}")
        out.append(f"// No decompiled body — IDA's call analysis failed on it. "
                   f"Only its address is used.")
        out.append(f"typedef void t_{c}();")
        out.append(f"static t_{c}& __{c} = *(t_{c}*)0x{funcs[c]:08X};")
        out.append("#endif")
        out.append(f"#define {c} __{c}")
    ext_calls = sorted(c for c in called if c != args.name and c not in already)
    for c in ext_calls:
        addr = int(c.split('_')[-1], 16)
        if c in USERCALL_STACK_ONLY:
            ret, argl, _ = USERCALL_STACK_ONLY[c]
            t = f"t_{c}"
            out.append(f"#ifndef __PE_DECL___{c}")
            out.append(f"#define __PE_DECL___{c}")
            out.append(f"typedef {ret} {t}({argl});   // stack arguments only")
            out.append(f"static {t}& __{c} = *({t}*)0x{addr:08X};")
            out.append("#endif")
            out.append(f"#define {c} __{c}")
            continue
        # The callee's own definition is the authoritative signature.  The
        # forward-declaration block is not: BMF.cpp has none at all for several
        # functions (sub_41C4B0, sub_413430, ...), and the fallback used to be
        # `(...)`.  For a __thiscall or __fastcall callee that is silently
        # fatal — gcc ignores the convention attribute on a variadic function,
        # so `this` goes on the stack instead of ECX and the callee reads
        # garbage.  It cost a null-pointer fault inside PE code three levels
        # away from the call before it was found.
        ret = argl = None
        if c in spans and spans[c][3] not in ('usercall', 'userpurge'):
            csig, _n = callee_signature(lines, spans, fixups, c)
            mm = re.match(r'^(.*?)\b' + re.escape(c) + r'\s*\((.*)\)\s*$', csig, re.S)
            if mm:
                ret, argl = mm.group(1).strip(), mm.group(2).strip()
                argl = re.sub(r'\bthis\b', '_this', argl)
        if ret is None:
            proto = protos.get(c)
            if proto:
                sig = proto.rstrip(';')
                sig = re.sub(r'//.*$', '', sig).strip()
                mm = re.match(r'^(.*?)\b' + re.escape(c) + r'\s*\((.*)\)\s*$', sig, re.S)
                ret, argl = (mm.group(1).strip(), mm.group(2).strip()) if mm else (None, None)
        cconv = spans[c][3] if c in spans else 'cdecl'
        if ret is None:
            if cconv != 'cdecl':
                sys.exit(f"{args.name} calls {c}, a __{cconv} function whose "
                         f"parameter list could not be recovered; declaring it "
                         f"variadic would silently drop the convention")
            ret, argl = 'int', '...'
        for k in ('__cdecl', '__stdcall', '__fastcall', '__thiscall', '__noreturn'):
            ret = ret.replace(k, '')
        ret = ' '.join(ret.split()) or 'int'
        # Every *pointer* parameter is declared `void *`.  Hex-Rays types a
        # pointer differently at the call site than in the callee's own
        # signature all the time — `unsigned char **` here, `_DWORD *` there —
        # and C++ rejects the mismatch where C would shrug.  A pointer is a
        # pointer: four bytes, passed identically, and `T *` converts to
        # `void *` implicitly, so relaxing the parameter accepts every spelling
        # without changing what reaches the callee.  The return type is left
        # alone: `void *` would not convert *back*.
        argl = ', '.join('void *' if '*' in prm else prm
                         for prm in split_params(argl)) if argl.strip() else argl
        attr = '' if cconv == 'cdecl' else f'__attribute__(({cconv})) '
        t = f"t_{c}"
        out.append(f"#ifndef __PE_DECL___{c}")
        out.append(f"#define __PE_DECL___{c}")
        argl = re.sub(r'\bthis\b', '_this', argl)
        out.append(f"typedef {attr}{ret} {t}({argl});")
        out.append(f"static {t}& __{c} = *({t}*)0x{addr:08X};")
        out.append("#endif")
        out.append(f"#define {c} __{c}")
    # Callees already moved: §6.3.  A forwarder rather than a bare #define
    # wherever the callee takes a pointer, so that the call site's spelling of
    # that pointer does not have to agree with the callee's.
    for c in sorted(called & already):
        if c == args.name:
            continue
        csig, cparams, cret = None, None, None
        # __usercall / __userpurge callees included: §4.2 gives their moved
        # body an ordinary cdecl signature taking every argument in order, so
        # a forwarder can be built for it the same way — the only difference
        # is that a vector argument is by reference there, and stays that way
        # here rather than being relaxed to `void *`.
        if c in spans:
            csig, _n = callee_signature(lines, spans, fixups, c)
            try:
                cret, cparams = parse_signature(csig, c)
            except Exception:
                cparams = None
        if cparams and any('*' in split_decl(d)[0] and '(' not in split_decl(d)[0]
                           for d, _, _ in cparams):
            out.extend(moved_callee_wrapper(args.name, c, csig, cret, cparams))
        else:
            out.append(f"#define {c} __{c}")
    if called:
        out.append("")

    # --- statically-linked CRT entries (§6.2, §6.5) -------------------------
    if crt or uses_new or uses_del or win:
        out.append("// BMF links the MSVC CRT into the image, so these route to the PE's")
        out.append("// own implementations — its FILE* objects and heap blocks belong to")
        out.append("// that private runtime, not to glibc (§6.5).")
    for n in sorted(win):
        ret, argl = WINAPI_PROTO[n]
        out.append(f"#ifndef __PE_DECL___{n}")
        out.append(f"#define __PE_DECL___{n}")
        out.append(f"typedef __attribute__((stdcall)) {ret} (*pfn_{n})({argl});")
        out.append(f"static pfn_{n}& {n} = *(pfn_{n}*)0x{win[n]:08X};   // IAT slot")
        out.append("#endif")
    for n in sorted(crt):
        asm_name, addr = crt[n]
        ret, argl, *cc = CRT_PROTO[n]
        attr = f'__attribute__(({cc[0]})) ' if cc else ''
        t = f"t_{n}"
        out.append(f"#ifndef __PE_DECL___{n}")
        out.append(f"#define __PE_DECL___{n}")
        out.append(f"typedef {attr}{ret} {t}({argl});   // {asm_name}")
        out.append(f"static {t}& __{n} = *({t}*)0x{addr:08X};")
        out.append("#endif")
        out.append(f"#define {n} __{n}")
    if uses_new:
        out.append("#ifndef __PE_DECL___op_new")
        out.append("#define __PE_DECL___op_new")
        out.append("typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z")
        out.append(f"static t_op_new& __op_new = *(t_op_new*)0x{funcs['??2@YAPAXI@Z']:08X};")
        out.append("#endif")
    if uses_del:
        out.append("#ifndef __PE_DECL___op_delete")
        out.append("#define __PE_DECL___op_delete")
        out.append("typedef void t_op_delete(void *);       // ??3@YAXPAX@Z")
        out.append(f"static t_op_delete& __op_delete = *(t_op_delete*)0x{funcs['??3@YAXPAX@Z']:08X};")
        out.append("#endif")
    if crt or uses_new or uses_del:
        out.append("#define FILE FILE1")
        out.append("")

    # --- the body -----------------------------------------------------------
    out.append(f"PROBE_DECL(__{args.name})")
    if conv in ('usercall', 'userpurge'):
        # Ordinary cdecl taking every argument, register ones included; a
        # vector register argument becomes a reference so that each argument
        # stays one four-byte slot and the thunk needs no 16-byte alignment
        # dance (the i386 ABI passes __m128 by value on a 16-byte boundary).
        decls, vec_copies = [], []
        for decl, nm, reg in sig_params:
            if reg in XMM and any(t in decl for t in VEC_TYPES):
                # By reference so the slot stays four bytes (§4.2), but the
                # body gets a *copy*: the original took this in a register, so
                # a write to it is local.  Binding the reference to a moved
                # caller's lvalue and letting the body write through it would
                # clobber the caller's variable — which the PE-side callers
                # never see, because the thunk points the reference at its own
                # scratch, so it would only ever go wrong once both ends moved.
                ty = re.sub(r'\b' + re.escape(nm) + r'\s*$', '', decl).strip()
                # const: a call site is free to pass a temporary —
                # `sub_41CAB0(x, (__m128)xmmword_439B60, ...)` — and a
                # non-const reference will not bind to one.
                decl = f"const {ty} &{nm}__ref"
                vec_copies.append(f"  {ty} {nm} = {nm}__ref;")
            decls.append(decl)
        ret = sig_text[:sig_text.index(args.name)]
        for k in ('__usercall', '__userpurge', '__noreturn'):
            ret = ret.replace(k, '')
        ret = ' '.join(ret.split()) or 'int'
        if ret_reg in XMM:
            # A result in xmm0 is what g++ does for a *raw* vector type and
            # only for that.  The M128* unions of §8.2 are class types, and
            # i386 returns every aggregate through a hidden pointer — which
            # would leave the thunk returning nothing in xmm0 and the PE caller
            # reading whatever was there.  Name the underlying vector instead;
            # the wrappers convert to it implicitly, so the body is unchanged.
            ret = re.sub(r'\b__m128(i|d)?\b', lambda m: '__gnu_m128' + (m.group(1) or ''),
                         ret)
            ret = re.sub(r'\b__m64\b', '__gnu_m64', ret)
        # extern "C" so the thunk's `call __<name>` in inline asm names the
        # same symbol the compiler emits; a mangled name would leave the call
        # referencing an undefined symbol, which in a shared object links
        # quietly and becomes a text relocation.
        # extern "C" so the thunk's `call __<name>` in inline asm names the
        # symbol the compiler actually emits — a mangled name would leave the
        # call referencing an undefined one, which in a shared object links
        # quietly and turns into a text relocation.  hidden visibility on the
        # same declaration keeps that call from needing a PLT entry, which is
        # the other half of the same problem.  Per function, not
        # -fvisibility=hidden: the flag applied to the whole translation unit
        # breaks the round-trip.
        sig_line = (f'extern "C" __attribute__((visibility("hidden"))) '
                    f'{ret} __{args.name}'
                    f"({', '.join(decls) if decls else 'void'})")
        rest = body_lines[nsig:]
        if vec_copies:
            # After the opening brace, ahead of Hex-Rays' own declarations.
            k = next((i for i, l in enumerate(rest) if l.strip() == '{'), -1)
            rest = rest[:k + 1] + vec_copies + rest[k + 1:]
        joined = [sig_line] + rest
        thunk = make_thunk(args.name, va, conv, sig_params, ret_reg)
    else:
        sig_line = body_lines[0]
        thunk = None
    for k, attr in (('__thiscall', '__attribute__((thiscall)) '),
                    ('__fastcall', '__attribute__((fastcall)) '),
                    ('__stdcall', '__attribute__((stdcall)) '),
                    ('__cdecl', '')):
        if thunk is None and k in sig_line:
            sig_line = sig_line.replace(k + ' ', '').replace(k, '')
            sig_line = attr + sig_line.lstrip()
            break
    sig_line = sig_line.replace('__noreturn ', '')
    # build.sh deliberately leaves SSE off for the translation unit as a whole,
    # so that turning it on for one body cannot change the code generated for
    # any other.  A body that uses the intrinsics or the register types asks
    # for it here instead.
    if re.search(r'\b_mm_|\b__m128|\b__m64\b|\b_fxsave\b|\b_fxrstor\b', body_raw):
        # After the linkage specifier, not before it: an attribute ahead of
        # `extern "C"` attaches to nothing, and the only symptom is g++
        # complaining that it could not inline an always_inline intrinsic.
        if sig_line.startswith('extern "C" '):
            sig_line = 'extern "C" BMF_SSE ' + sig_line[len('extern "C" '):]
        else:
            sig_line = 'BMF_SSE ' + sig_line
    if thunk is None:
        # A moved function is entered straight from PE code, which — being
        # compiled to the Microsoft i386 ABI — only guarantees 4-byte stack
        # alignment at a call.  g++ assumes 16, and spills SSE locals with
        # `movaps ...,N(%esp)`; on an odd caller that faults.  Realigning in
        # the prologue is exactly what this attribute is for.  Per function
        # rather than -mstackrealign: applied to the whole translation unit it
        # breaks the round-trip, and the internal gcc-to-gcc calls never need
        # it anyway.  Thunked entry points do their own `and $-16,%esp`
        # (§4.2), so they are left alone.
        sig_line = '__attribute__((force_align_arg_pointer)) ' + sig_line
        sig_line = re.sub(r'\b' + re.escape(args.name) + r'\b',
                          f'__{args.name}', sig_line, count=1)
        joined = [sig_line] + body_lines[1:]
    else:
        joined[0] = sig_line
    # PROBE_HIT goes after the opening brace of the function.
    for i, l in enumerate(joined):
        if l.strip() == '{':
            joined.insert(i + 1, f"  PROBE_HIT(__{args.name});")
            break
        if l.rstrip().endswith('{') and i == 0:
            joined.insert(1, f"  PROBE_HIT(__{args.name});")
            break
    # `this` is a C++ keyword; Hex-Rays uses it as the first parameter name of
    # every __thiscall function.  Rename it (and its uses) whole-word — the
    # sibling locals this_1/this_3/... are distinct identifiers and unaffected.
    # Reassemble the stack frame when the address of a stack local escapes.
    _k = next((i for i, l in enumerate(joined) if l.strip() == '{'), 0)
    _k += 1
    while _k < len(joined) and re.match(r'\s*(PROBE_HIT|__m128\w* \w+ = \w+__ref;)', joined[_k]):
        _k += 1
    locs = frame_locals(joined, _k)
    if any(by for *_x, by in locs) or addr_taken(joined, locs):
        frame, drop = build_frame(locs)
        kept = [l for i, l in enumerate(joined) if i not in drop]
        k = next((i for i, l in enumerate(kept) if l.strip() == '{'), 0)
        joined = kept[:k + 1] + frame + kept[k + 1:]
    elif re.search(r'\b_mm_|\b__m128', body_raw):
        # The original's frame was 16-byte aligned and Hex-Rays' locals sit at
        # fixed offsets in it, so a body that casts a local array to
        # `__m128i *` and stores through it — `*(__m128i *)&v31[k + 1] = v7`,
        # an aligned store — is relying on that.  Hex-Rays declares the array
        # `_BYTE v31[272]`, alignment 1; where it lands is then up to g++, and
        # it faults (#GP, delivered as SIGSEGV with si_addr 0) whenever the
        # frame layout happens to put it on an odd 16.  Ask for the alignment
        # the original had rather than depending on luck.
        for i, l in enumerate(joined[_k:len(joined)], _k):
            if not l.strip():
                continue
            if not re.match(r'^\s*[A-Za-z_][\w\s\*]*\b[A-Za-z_]\w*\s*\[[^\]]*\]\s*;', l):
                if re.match(r'^\s*[A-Za-z_][\w\s\*]*\b[A-Za-z_]\w*\s*;', l):
                    continue             # a scalar local; keep scanning
                break                    # first statement
            joined[i] = re.sub(r'^(\s*)', r'\1alignas(16) ', l, count=1)
    joined = [re.sub(r'\bthis\b', '_this', l) for l in joined]
    # A recursive call still spells the PE name; point it at the moved body
    # (the signature above was already renamed, and `__name` does not re-match).
    joined = [re.sub(r'\b' + re.escape(args.name) + r'\b', f'__{args.name}', l)
              for l in joined]
    # A local or parameter that collides with a type the head declares.
    for t in sorted(HEAD_TYPES & locals_):
        joined = [re.sub(r'\b' + re.escape(t) + r'\b(?!\s*\*)', t + '_v', l) for l in joined]
    stack_only = sorted(called & set(USERCALL_STACK_ONLY))
    if stack_only:
        text = '\n'.join(joined)
        for c in stack_only:
            text = drop_leading_args(text, c, USERCALL_STACK_ONLY[c][2])
        joined = text.split('\n')
    for g in sorted(refd_globals):
        joined = [rename_ident(l, g, f"__{args.name}_{g}") for l in joined]
    joined = [fix_hex_escapes(l) for l in joined]
    joined = launder_pointer_counters(joined)
    joined = [mask_shift_counts(l) for l in joined]
    if single_precision(args.name):
        joined = [floatify(l) for l in joined]
    joined = [wrap_intrinsic_members(l) for l in joined]
    joined = [re.sub(r'\boperator new\s*\(', '__op_new(', l) for l in joined]
    joined = [re.sub(r'\boperator delete\s*\(', '__op_delete(', l) for l in joined]
    # `xmmword_441120 = 0;` and `(__m128i)0LL` need no rewriting: the M128*
    # wrappers in the head construct from a scalar by zero-extending it, which
    # is what the MOVD/MOVQ behind them does.
    out.extend(joined)
    out.append("")
    if thunk:
        out.extend(thunk)

    # --- close the macro scope (§6.5) ---------------------------------------
    if crt or uses_new or uses_del:
        out.append("#undef FILE")
    for n in sorted(crt):
        out.append(f"#undef {n}")
    for c in sorted(set(called) | set(no_body)):
        if c != args.name:
            out.append(f"#undef {c}")

    dest = args.out or os.path.join(HERE, 'inc', args.name + '.inc')
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    open(dest, 'w').write('\n'.join(out) + '\n')
    print(f"{dest}: {b - a + 1} body lines, {len(refd_globals)} globals, "
          f"{len(ext_calls)} PE callees, {len(called & already)} moved callees")


class _Args:
    def __init__(self, name, accepted, out):
        self.name, self.accepted, self.out = name, accepted, out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('name', nargs='*')
    ap.add_argument('--accepted', default=os.path.join(HERE, 'accepted.txt'))
    ap.add_argument('--out', default=None)
    ap.add_argument('--all-accepted', action='store_true',
                    help="re-emit every name in --accepted, in file order")
    a = ap.parse_args()

    names = list(a.name)
    if a.all_accepted:
        names += [l.split()[1] for l in open(a.accepted) if l.strip()]
    if not names:
        ap.error('nothing to extract')
    if a.out and len(names) > 1:
        ap.error('--out takes a single name')

    # One load() for the whole batch: BMF.cpp is 1.2 MB and drive.py re-emits the
    # entire accepted set on every acceptance (see below), so parsing it once
    # per name would dominate the loop.
    cache = load()
    for n in names:
        emit(_Args(n, a.accepted, a.out), cache)


if __name__ == '__main__':
    main()
