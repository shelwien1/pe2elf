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
                    r'|BYTE\d|WORD\d|SLOBYTE|SLOWORD|SHIDWORD|COERCE_|abs32'
                    r'|alloca|qmemcpy|memset32|sizeof|_BitScanForward)')
CTRL = {'if', 'for', 'while', 'switch', 'return', 'do', 'else', 'sizeof'}


def load():
    lines = open(SRC, errors='replace').read().split('\n')
    # --- function definition spans -----------------------------------------
    sites = []
    for ln in open(os.path.join(HERE, 'sites.txt')):
        va, name, conv, line = ln.rstrip('\n').split('\t')
        sites.append((int(line), name, va, conv))
    sites.sort()
    spans = {}
    for i, (line, name, va, conv) in enumerate(sites):
        end = sites[i + 1][0] - 1 if i + 1 < len(sites) else len(lines)
        spans[name] = (line, end, va, conv)

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
    globals_ = {}
    for l in open(os.path.join(HERE, 'symbols.txt')):
        addr, name, base, ext = (l.rstrip('\n').split('\t') + [''])[:4]
        globals_[name] = (int(addr, 16), base, ext)

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
            elif not re.fullmatch(r'(?:' + GLOBAL_RE + r')', name):
                # Declared in the data section but with no address anywhere:
                # not in the "using guessed type" comments and no address in
                # the name.  Nothing can be referenced at a known VA.
                noaddr.add(name)
        i += 1
    return lines, spans, protos, globals_, noaddr


def array_used(lines, spans, name):
    """True if any body indexes this global — decides array vs scalar typedef."""
    pat = re.compile(re.escape(name) + r'\s*\[')
    for (a, b, _, _) in spans.values():
        if pat.search('\n'.join(lines[a - 1:b])):
            return True
    return False


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('name')
    ap.add_argument('--accepted', default=os.path.join(HERE, 'accepted.txt'))
    ap.add_argument('--out', default=None)
    args = ap.parse_args()

    lines, spans, protos, globals_, noaddr = load()
    if args.name not in spans:
        sys.exit(f"no such function: {args.name}")
    a, b, va, conv = spans[args.name]
    if conv in ('usercall', 'userpurge'):
        sys.exit(f"{args.name} is __{conv}: no g++ equivalent (incdec.md §4)")

    body_lines = lines[a - 1:b]
    # The span runs to the line before the next definition, which sweeps up
    # that definition's "//----- (004123 40) ----" banner and any blank lines.
    # Cut back to the last line of actual code.
    while body_lines and (not body_lines[-1].strip()
                          or re.match(r'^//-+\s*\(?[0-9A-Fa-f]*\)?\s*-*$', body_lines[-1].strip())
                          or body_lines[-1].lstrip().startswith('//')):
        body_lines.pop()
    body_raw = '\n'.join(body_lines)
    # Reference detection must look at code only.  Hex-Rays appends
    # "// <addr>: using guessed type <t> <name>;" lines to each body, so a
    # comment-only mention would otherwise register as a real reference —
    # and, for an address-less name, wrongly refuse the whole function.
    body = re.sub(r'//[^\n]*', '', body_raw)

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
    locals_ = set()
    for l in body_lines[1:]:
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
    called = set(re.findall(r'\b(' + SUB_RE + r')\s*\(', body))
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
    for m in re.finditer(r'\b([A-Za-z_]\w*)\s*\(', body):
        n = m.group(1)
        if n in CTRL or INTRIN.match(n) or n in PURE_LIBC:
            continue
        if re.fullmatch(SUB_RE, n) or re.fullmatch(r'[A-Za-z_]\w*_4[0-9A-Fa-f]{5}', n):
            continue
        unresolved.add(n)
    if re.search(r'\bnew\b|\bdelete\b', body):
        unresolved.add('operator new/delete')
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
        if ext in ('', '[]'):
            # "[]" (unspecified bound) cannot be used as *(T*)addr, and an
            # indexed global needs an array type; pick a bound large enough
            # that indexing is unconstrained — no storage is created, the
            # type only reinterprets the PE image.
            ext = '[0x10000]' if (ext == '[]' or array_used(lines, spans, g)) else '' 
        if not base:
            base = PREFIX_TYPE.get(g.split('_')[0], 'unsigned char')
        t = f"t_{g}"
        out.append(f"#ifndef __PE_DECL___{g}")
        out.append(f"#define __PE_DECL___{g}")
        out.append(f"typedef {base} {t}{ext};")
        out.append(f"static {t}& __{g} = *({t}*)0x{addr:08X};")
        out.append("#endif")
        out.append(f"#define {g} __{g}")
    if refd_globals:
        out.append("")

    # --- callees still living in the PE (§6.2) ------------------------------
    ext_calls = sorted(c for c in called if c != args.name and c not in already)
    for c in ext_calls:
        addr = int(c.split('_')[-1], 16)
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

    # --- the body -----------------------------------------------------------
    out.append(f"PROBE_DECL(__{args.name})")
    sig_line = body_lines[0]
    for k, attr in (('__thiscall', '__attribute__((thiscall)) '),
                    ('__fastcall', '__attribute__((fastcall)) '),
                    ('__stdcall', '__attribute__((stdcall)) '),
                    ('__cdecl', '')):
        if k in sig_line:
            sig_line = sig_line.replace(k + ' ', '').replace(k, '')
            sig_line = attr + sig_line.lstrip()
            break
    sig_line = sig_line.replace('__noreturn ', '')
    sig_line = re.sub(r'\b' + re.escape(args.name) + r'\b', f'__{args.name}', sig_line, count=1)
    rest = body_lines[1:]
    # PROBE_HIT goes after the opening brace of the function.
    joined = [sig_line] + rest
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
    vec = {g for g in refd_globals if globals_[g][1] in ('__int128', '_OWORD', '__m128i', '__m128', '__m128d')}
    if vec:
        pat = re.compile(r'\b(' + '|'.join(re.escape(v) for v in vec) + r')(\[[^\]]*\])?\s*=\s*0(LL|i64)?\s*;')
        joined = [pat.sub(lambda m: f"{m.group(1)}{m.group(2) or ''} = _mm_setzero_si128();", l)
                  for l in joined]
    out.extend(joined)
    out.append("")

    # --- close the macro scope (§6.5) ---------------------------------------
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


if __name__ == '__main__':
    main()
