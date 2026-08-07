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
  * Uses the declared type + extent from BMF.c's data-declaration section
    where available, falling back to a usage-derived guess.

Usage: extract.py <name> [--accepted accepted.txt] [--out inc/<name>.inc]
"""
import argparse
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
SRC = os.path.join(HERE, 'BMF.c')

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
PURE_LIBC = {'strcpy', 'strncpy', 'strrchr', 'strchr', 'memset', 'memcpy',
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
    '__intel_sse2_strlen': ('int', 'unsigned int, const void *', 'fastcall'),
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

    # BMF.c's own "// 4456F4: using guessed type int n0x2000_1;" comments win
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

    Per body, not across all of BMF.c.  A global with no declared extent that
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
        open(dest, 'w').write(open(ovr).read())
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
    # the `find` strings can be grepped for in BMF.c.  A fixup that no longer
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
    body = re.sub(r'"(?:[^"\\\\]|\\\\.)*"', '""', body)
    body = re.sub(r"'(?:[^'\\\\]|\\\\.)*'", "' '", body)

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
        if INTEL_CRT.match(n):
            # Resolve here rather than falling through: INTRIN's `__` branch
            # below would otherwise swallow these before they reach the CRT
            # lookup.
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
                 f"(declared in BMF.c but absent from the 'using guessed type' "
                 f"comments): {hit_noaddr}")
    if unresolved:
        sys.exit(f"{args.name} references unresolvable symbols "
                 f"(no symbol table for BMF's static CRT): {sorted(unresolved)}")

    out = []
    out.append(f"// {args.name} @ 0x{va} — __{conv}")
    out.append(f"// Extracted from BMF.c:{a}-{b} by extract.py per incdec.md.")
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
        out.append(f"#define {g} __{args.name}_{g}")
    if refd_globals:
        out.append("")

    # --- callees still living in the PE (§6.2) ------------------------------
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
        proto = protos.get(c)
        if proto:
            sig = proto.rstrip(';')
            sig = re.sub(r'//.*$', '', sig).strip()
            mm = re.match(r'^(.*?)\b' + re.escape(c) + r'\s*\((.*)\)\s*$', sig, re.S)
            ret, argl = (mm.group(1).strip(), mm.group(2).strip()) if mm else ('int', '...')
        else:
            ret, argl = 'int', '...'
        cconv = spans[c][3] if c in spans else 'cdecl'
        for k in ('__cdecl', '__stdcall', '__fastcall', '__thiscall', '__noreturn'):
            ret = ret.replace(k, '')
        ret = ' '.join(ret.split()) or 'int'
        attr = '' if cconv == 'cdecl' else f'__attribute__(({cconv})) '
        t = f"t_{c}"
        out.append(f"#ifndef __PE_DECL___{c}")
        out.append(f"#define __PE_DECL___{c}")
        argl = re.sub(r'\bthis\b', '_this', argl)
        out.append(f"typedef {attr}{ret} {t}({argl});")
        out.append(f"static {t}& __{c} = *({t}*)0x{addr:08X};")
        out.append("#endif")
        out.append(f"#define {c} __{c}")
    # Callees already moved: just map the name onto the C++ symbol (§6.3).
    for c in sorted(called & already):
        if c != args.name:
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
        decls = []
        for decl, nm, reg in sig_params:
            if reg in XMM and any(t in decl for t in VEC_TYPES):
                decl = re.sub(r'\b' + re.escape(nm) + r'\s*$', '&' + nm, decl)
            decls.append(decl)
        ret = sig_text[:sig_text.index(args.name)]
        for k in ('__usercall', '__userpurge', '__noreturn'):
            ret = ret.replace(k, '')
        ret = ' '.join(ret.split()) or 'int'
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
    for g in sorted(refd_globals):
        out.append(f"#undef {g}")
    for c in sorted(called):
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

    # One load() for the whole batch: BMF.c is 1.2 MB and drive.py re-emits the
    # entire accepted set on every acceptance (see below), so parsing it once
    # per name would dominate the loop.
    cache = load()
    for n in names:
        emit(_Args(n, a.accepted, a.out), cache)


if __name__ == '__main__':
    main()
