#!/usr/bin/env python3
"""
extract_fn.py NAME [--out FILE]

Extract a Hex-Rays decompiled function from PPMonstr.cpp into a .inc
scaffold ready to drop into dummy.cpp per the incdec.md protocol.

For each external identifier the body references, the tool:
- looks up the address in PPMonstr.txt,
- looks up a prototype in PPMonstr.cpp (forward declarations, data
  definitions, WinAPI import comments),
- emits a typed `__attribute__((ms_abi))` reference at that address,
- adds a `#define <orig> __<orig>` mapping so the body stays verbatim.

Identifiers that can't be resolved are listed as `// TODO` at the top
of the output -- they typically are local variables, language keywords,
SSE intrinsics, or names the donor source spelled differently than
PPMonstr.txt. Fix them by hand.

Limitations:
- Prototypes are inferred from the donor source; sometimes Hex-Rays
  emits `// ...; weak` for library names. The tool uses those when
  present, otherwise falls back to a `void(...)` placeholder.
- `_BitScanForward`, `_mm_*`, `(__m128i)0LL`, FILE-layout fields and
  similar MSVC quirks are *not* rewritten. They get a TODO note.
- The body is NOT scanned for the "inter-local pointer arithmetic"
  pattern (Hex-Rays expanding memcpy into writes across named locals).
  When you see `*(T*)((char*)&local_a + var_offset)`, treat it as
  memmove and rewrite by hand. See incdec.md.
"""

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).parent
CPP_PATH = ROOT / "PPMonstr.cpp"
TXT_PATH = ROOT / "PPMonstr.txt"

# Identifiers that are language constructs / built-ins / handled elsewhere.
SKIP = {
    # C/C++ keywords
    "if", "else", "while", "do", "for", "switch", "case", "default",
    "break", "continue", "return", "goto", "nullptr", "sizeof", "NULL",
    "true", "false", "static_cast", "reinterpret_cast", "const_cast",
    "dynamic_cast", "new", "delete", "this", "operator",
    # types
    "int", "char", "short", "long", "unsigned", "signed", "void", "bool",
    "float", "double", "auto", "const", "volatile", "struct", "union",
    "enum", "typedef", "extern", "static", "register", "inline", "wchar_t",
    "size_t", "clock_t", "errno_t",
    "__int8", "__int16", "__int32", "__int64", "__int128",
    "_BYTE", "_WORD", "_DWORD", "_QWORD", "_BOOL1", "_BOOL2", "_BOOL4",
    "uint8", "uint16", "uint32", "uint64", "int8", "int16", "int32", "int64",
    "sint8", "sint16", "sint32", "sint64",
    "uchar", "ushort", "uint", "ulong",
    # Win types from PPMonstr.h
    "PVOID", "LPVOID", "HANDLE", "BOOL", "DWORD", "WORD", "BYTE", "CHAR",
    "LPSTR", "LPCSTR", "LPWORD", "LPFILETIME", "LPWIN32_FIND_DATAA",
    "LPSECURITY_ATTRIBUTES", "FILE", "FILETIME", "_FILETIME",
    "_WIN32_FIND_DATAA", "_SECURITY_ATTRIBUTES", "__m128i",
    # Hex-Rays helper macros (defs.h)
    "LOBYTE", "HIBYTE", "LOWORD", "HIWORD", "LODWORD", "HIDWORD",
    "BYTE0", "BYTE1", "BYTE2", "BYTE3", "BYTE4", "BYTE5", "BYTE6", "BYTE7",
    "WORD0", "WORD1", "WORD2", "WORD3", "WORD4", "WORD5", "WORD6", "WORD7",
    "BYTEn", "WORDn", "DWORDn", "SBYTEn", "SWORDn", "SDWORDn",
    "SLOBYTE", "SLOWORD", "SLODWORD", "SHIBYTE", "SHIWORD", "SHIDWORD",
    # SSE / MSVC intrinsics: handled with macros / x86intrin.h
    "_mm_getcsr", "_mm_setcsr", "_mm_movemask_epi8", "_mm_cmpeq_epi8",
    "_mm_setzero_si128", "_mm_unpacklo_epi64", "_mm_stream_si128",
    "_mm_sfence", "_mm_prefetch", "_BitScanForward",
    # MSVC keywords
    "__noreturn", "__stdcall", "__cdecl", "__fastcall", "__thiscall",
    "__declspec", "__attribute__", "ms_abi",
}

# Glibc primitives we accept without a typed ref (no PE-state side effects).
# strcpy / memcpy / memset have no MSVC-CRT-private state.
GLIBC_OK = {"strcpy", "memcpy", "memset", "strlen", "strcmp"}

# Hex-Rays types: map to the typedef text we need in the C++ signature.
TYPE_PASSTHROUGH = (
    "FILE *", "FILE*", "void *", "void*", "char *", "char*",
    "const char *", "const char*", "wchar_t *", "wchar_t*",
)

WINAPI_RE = re.compile(
    r"//\s*extern\s+(\S.*?)\s*\(\s*__stdcall\s*\*\s*(\w+)\s*\)\s*\((.*?)\);",
    re.DOTALL,
)
PROTO_CMT_RE = re.compile(r"^//\s*([^/].*?);\s*(?://.*)?$")
PROTO_DEF_RE = re.compile(r"^(\S[^;{]*?\b(\w+)\s*\([^;]*\)\s*);\s*(?://.*)?$")
DATA_DEF_RE = re.compile(r"^([A-Za-z_].*?\b(\w+)\s*(?:\[[^\]]*\])?)\s*(?:=|;)")
SECTION_DELIM = re.compile(
    r"^//-+\s*\(([0-9A-Fa-f]+)\)\s*-+\s*$", re.MULTILINE
)


def load_addrs():
    addrs = {}
    for line in TXT_PATH.read_text().splitlines():
        m = re.match(r"^([0-9A-Fa-f]+)\s+(\S+)$", line)
        if m:
            addrs[m.group(2)] = int(m.group(1), 16)
    return addrs


def split_cpp(cpp):
    """Return (header_text, [(addr, body_text), ...])."""
    parts = SECTION_DELIM.split(cpp)
    # parts: [header, addr1, body1, addr2, body2, ...]
    header = parts[0]
    bodies = []
    for i in range(1, len(parts), 2):
        bodies.append((int(parts[i], 16), parts[i + 1]))
    return header, bodies


def find_function(bodies, name):
    """Return (addr, body_text_after_delimiter)."""
    name_re = re.compile(rf"\b{re.escape(name)}\s*\(")
    for addr, body in bodies:
        # First non-blank line typically holds the signature
        for line in body.splitlines():
            if line.strip():
                if name_re.search(line):
                    return addr, body
                break
    return None, None


def parse_prototypes(header):
    """Return dict name -> prototype string (without trailing ';')."""
    protos = {}
    for raw in header.splitlines():
        line = raw.rstrip()
        # commented-out prototype: "// int printf(const char *const Format, ...);"
        m = PROTO_CMT_RE.match(line)
        if m:
            decl = m.group(1).strip()
            n = _proto_name(decl)
            if n:
                protos.setdefault(n, decl)
                continue
        # plain prototype
        m = PROTO_DEF_RE.match(line)
        if m:
            decl = m.group(1).strip()
            n = m.group(2)
            protos.setdefault(n, decl)
    return protos


def _proto_name(decl):
    m = re.search(r"\b(\w+)\s*\([^)]*\)\s*$", decl)
    return m.group(1) if m else None


def parse_data_defs(header):
    """name -> (type_text, was_array_or_pointer)."""
    data = {}
    for raw in header.splitlines():
        line = raw.rstrip()
        if not line or line.startswith("//"):
            continue
        m = DATA_DEF_RE.match(line)
        if not m:
            continue
        full = m.group(1).strip()
        n = m.group(2)
        if n in data:
            continue
        # Reconstruct: split into [type, name] -- take everything except trailing
        # identifier and optional [N] suffix as the type.
        decl = full
        # strip array size from name component
        decl = re.sub(rf"\b{re.escape(n)}\b\s*(?:\[[^\]]*\])?\s*$", "", decl).strip()
        # detect array
        is_array = bool(re.search(rf"\b{re.escape(n)}\s*\[", full))
        array_sz_m = re.search(rf"\b{re.escape(n)}\s*\[\s*(\d+)\s*\]", full)
        array_sz = int(array_sz_m.group(1)) if array_sz_m else None
        data[n] = (decl, is_array, array_sz)
    return data


def parse_winapi(header):
    """name -> (return_type, arg_list_text)."""
    winapi = {}
    for m in WINAPI_RE.finditer(header):
        ret = m.group(1).strip()
        name = m.group(2)
        args = re.sub(r"\s+", " ", m.group(3)).strip()
        winapi[name] = (ret, args)
    return winapi


def get_body_tokens(body, exclude_strings=True):
    """Return list of (kind, text) where kind in {'call', 'ident'}."""
    if exclude_strings:
        body = re.sub(r'"(?:\\.|[^"\\])*"', '""', body)
        body = re.sub(r"'(?:\\.|[^'\\])*'", "''", body)
        body = re.sub(r"//[^\n]*", "", body)
        body = re.sub(r"/\*.*?\*/", "", body, flags=re.DOTALL)
    calls = set(re.findall(r"\b([A-Za-z_]\w*)\s*\(", body))
    idents = set(re.findall(r"\b([A-Za-z_]\w*)\b", body))
    return calls, idents


def collect_locals(body, params):
    """Identifiers declared inside the function body's variable-decl prologue,
    plus the function parameters."""
    locals_set = set(params)
    in_body = False
    for line in body.splitlines():
        s = line.strip()
        if not s:
            if in_body:
                break
            continue
        if not in_body:
            if "{" in s:
                in_body = True
            continue
        # Stop at first non-declaration statement.
        m = re.match(r"^[A-Za-z_].*?\b(\w+)\s*(?:\[[^\]]*\])?\s*;", s)
        if not m:
            break
        locals_set.add(m.group(1))
    return locals_set


def parse_params(params_text):
    """Pull identifier names out of a comma-separated parameter list."""
    out = []
    if not params_text or params_text.strip() in ("", "void"):
        return out
    for part in re.split(r",(?![^(]*\))", params_text):
        # Take the LAST identifier in the part (the parameter name)
        m = re.findall(r"\b([A-Za-z_]\w*)\b", part)
        if m:
            out.append(m[-1])
    return out


def addr_for(name, addrs):
    """Look up name in PPMonstr.txt, trying common Hex-Rays prefix strips."""
    if name in addrs:
        return addrs[name]
    for prefix in ("_", "__"):
        if (prefix + name) in addrs:
            return addrs[prefix + name]
    return None


def signature_line(body):
    """Return the function signature line (the first non-blank)."""
    for line in body.splitlines():
        if line.strip():
            return line.rstrip()
    return ""


def split_signature(sig):
    """Return (return_type, name, params)."""
    # Allow body to follow on same line: "{ ... }"
    m = re.match(r"^(.*?)\b(\w+)\s*\((.*?)\)\s*(?:\{.*)?$", sig)
    if not m:
        return None, None, None
    return m.group(1).strip(), m.group(2), m.group(3)


def function_body_text(body):
    """Everything from the opening '{' onwards, including locals."""
    i = body.find("{")
    return body[i:] if i >= 0 else body


def emit_inc(fn_name, addr, body, addrs, protos, data_defs, winapi):
    sig = signature_line(body)
    ret, name, params = split_signature(sig)
    if name is None:
        sys.exit(f"could not parse signature: {sig!r}")
    if name != fn_name:
        # Allow alias (sub_<addr> vs symbolic name)
        pass

    calls, idents = get_body_tokens(function_body_text(body))
    locals_set = collect_locals(body, parse_params(params))

    # Resolve each external (with underscore-prefix fallback) and record the
    # canonical name in PPMonstr.txt so we always patch the right address.
    resolved = {}  # name_in_body -> (addr, canonical_name_in_txt)
    for c in sorted(calls | idents):
        if c in SKIP or c in locals_set:
            continue
        addr_ = addr_for(c, addrs)
        if addr_ is None:
            continue
        canonical = c if c in addrs else (
            "_" + c if "_" + c in addrs else "__" + c
        )
        resolved[c] = (addr_, canonical)

    pe_calls = []
    iat_calls = []
    todo_calls = []
    for c in sorted(calls):
        if c in SKIP or c in locals_set:
            continue
        if c in resolved and c in winapi:
            iat_calls.append(c)
        elif c in resolved:
            pe_calls.append(c)
        elif c in GLIBC_OK:
            continue
        else:
            todo_calls.append(c)
    glibc_calls = sorted(c for c in calls if c in GLIBC_OK)

    pe_data = []
    todo_idents = []
    for t in sorted(idents):
        if t in SKIP or t in calls or t in locals_set:
            continue
        if t in resolved and t in data_defs:
            pe_data.append(t)

    out = []
    out.append(f"// =====================================================================")
    out.append(f"// {fn_name} @ 0x{addr:X}")
    out.append(f"// Auto-extracted scaffold. REVIEW: see TODO comments below.")
    out.append(f"// =====================================================================")
    out.append("")
    out.append("#define FILE FILE1")
    out.append("")
    out.append("#define _BitScanForward(idx_ptr, mask_val) \\")
    out.append("  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)")
    out.append("")

    if todo_calls or todo_idents:
        out.append("// ---- TODO: unresolved identifiers (locals, intrinsics, or typos) ----")
        for c in todo_calls:
            out.append(f"//   call:  {c}")
        for t in todo_idents:
            out.append(f"//   ident: {t}")
        out.append("")

    # ---- Suspicious-pattern warnings ----
    body_clean = function_body_text(body)
    warnings = []
    if "(__m128i)0LL" in body_clean:
        warnings.append("(__m128i)0LL  ->  rewrite as _mm_setzero_si128()")
    if re.search(r"\(__m128i\)\([^)]+\)\s*v\d+\b", body_clean):
        warnings.append("(__m128i)(uint64)scalar  ->  rewrite via _mm_cvtsi64_si128/_mm_set_epi64x")
    if "operator new" in body_clean:
        warnings.append("operator new(N)  ->  call __op_new (or chosen typed ref); the C++ keyword is not macro-replaceable")
    # Detect inter-local pointer arithmetic: *(T*)((char*)&local_a + var)
    if re.search(r"\(\s*char\s*\*\s*\)\s*&\s*\w+\s*\+\s*v\d+", body_clean):
        warnings.append("`(char*)&<local> + v<N>` -- Hex-Rays expanded a memcpy "
                        "into pointer arithmetic across adjacent locals. g++ "
                        "does NOT preserve that layout. Rewrite as memmove "
                        "against the conceptual source struct.")
    if warnings:
        out.append("// ---- WARNING: patterns that need manual rewrite ----")
        for w in warnings:
            out.append(f"//   {w}")
        out.append("")

    # ---- Data refs ----
    # Guards (__PE_DECL___<sym>) prevent "redefinition of static ref" errors
    # when two .inc files in the same TU reference the same PE global.
    if pe_data:
        out.append("// ---- Data references ------------------------------------------------")
        for d in pe_data:
            type_text, is_array, sz = data_defs.get(d, ("void*", False, None))
            guard = f"__PE_DECL___{d}"
            out.append(f"#ifndef {guard}")
            out.append(f"#define {guard}")
            if is_array:
                tname = f"t_{d}"
                base = type_text.strip()
                size = sz if sz else 1
                out.append(f"typedef {base} {tname}[{size}];")
                out.append(f"static {tname}& __{d} = *({tname}*)0x{resolved[d][0]:X};")
            else:
                out.append(f"static {type_text}& __{d} = *({type_text}*)0x{resolved[d][0]:X};")
            out.append(f"#endif")
            out.append(f"#define {d} __{d}")
        out.append("")

    # ---- PE function refs ----
    # Same guard scheme: typedef name is t_<sym> (stable, not per-caller) so
    # a second .inc that calls the same PE function reuses the same typedef.
    if pe_calls:
        out.append("// ---- PE-internal function references --------------------------------")
        for c in pe_calls:
            guard = f"__PE_DECL___{c}"
            tname = f"t_{c}"
            proto = protos.get(c)
            out.append(f"#ifndef {guard}")
            out.append(f"#define {guard}")
            if proto is None:
                out.append(f"// TODO: prototype for {c} not found; placeholder void(...) used.")
                out.append(f"typedef __attribute__((ms_abi)) void {tname}(...);")
            else:
                pm = re.match(r"^(.*?)\b" + re.escape(c) + r"\s*\((.*)\)\s*$", proto)
                if pm:
                    ret_t = pm.group(1).strip()
                    args_t = pm.group(2).strip()
                else:
                    ret_t, args_t = "void", "..."
                out.append(f"typedef __attribute__((ms_abi)) {ret_t} {tname}({args_t});")
            out.append(f"static {tname}& __{c} = *({tname}*)0x{resolved[c][0]:X};")
            out.append(f"#endif")
            out.append(f"#define {c} __{c}")
        out.append("")

    # ---- WinAPI IAT slots ----
    if iat_calls:
        out.append("// ---- WinAPI imports via IAT slots -----------------------------------")
        for c in iat_calls:
            ret_t, args_t = winapi[c]
            out.append(
                f"typedef __attribute__((ms_abi)) {ret_t} (*pfn_{c})({args_t});"
            )
            out.append(f"static pfn_{c}& {c} = *(pfn_{c}*)0x{resolved[c][0]:X};")
        out.append("")

    if glibc_calls:
        out.append(f"// glibc fall-throughs (no MSVC-CRT state): {', '.join(glibc_calls)}")
        out.append("")

    # ---- Body ----
    new_name = f"__{fn_name}"
    if new_name == "____main":  # paranoia
        new_name = "__pe_main"
    out.append(f"PROBE_DECL({new_name})")
    # Build new signature with ms_abi
    new_sig = f"__attribute__((ms_abi)) {ret} {new_name}({params}) {{"
    # Replace first line
    body_text = function_body_text(body)
    # Insert PROBE_HIT after the opening '{' line
    body_text = re.sub(r"^\{", f"{{\n  PROBE_HIT({new_name});", body_text, count=1)
    out.append(new_sig)
    out.append(body_text.lstrip("{").rstrip())
    out.append("")

    # ---- Cleanup #undef ----
    out.append("// ---- Cleanup --------------------------------------------------------")
    for d in pe_data:
        out.append(f"#undef {d}")
    for c in pe_calls:
        out.append(f"#undef {c}")
    out.append("#undef _BitScanForward")
    out.append("#undef FILE")

    return "\n".join(out) + "\n"


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("name", help="function name as it appears in PPMonstr.cpp")
    ap.add_argument("--out", help="output .inc path (default: <name>.inc)")
    args = ap.parse_args()

    addrs = load_addrs()
    cpp = CPP_PATH.read_text()
    header, bodies = split_cpp(cpp)
    protos = parse_prototypes(header)
    data_defs = parse_data_defs(header)
    winapi = parse_winapi(header)

    addr, body = find_function(bodies, args.name)
    if addr is None:
        sys.exit(f"function {args.name!r} not found in {CPP_PATH}")

    text = emit_inc(args.name, addr, body, addrs, protos, data_defs, winapi)
    out_path = Path(args.out) if args.out else ROOT / f"{args.name}.inc"
    out_path.write_text(text)
    print(f"wrote {out_path} ({addr:#x}, {len(text)} bytes)")
