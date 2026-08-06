#!/usr/bin/env python3
"""drive.py — run the incdec loop over a candidate list.

For each candidate, in callees-before-callers order: extract the .inc, append
it to accepted.txt, rebuild, and run the -S -Q9 round-trip gate.  Green keeps
it; red reverts and records the reason in fail.txt.  incdec.md §3 step 7 —
never proceed with a red test.

A build failure counts as a failure: incdec.md §7.4 warns that a stale
dummy32.so otherwise sails through the test with the previous build's
redirects still installed, which is a false positive.
"""
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
os.chdir(HERE)


def run(cmd, **kw):
    return subprocess.run(cmd, shell=isinstance(cmd, str), capture_output=True,
                          text=True, **kw)


def load_candidates(path):
    out = []
    for l in open(path):
        if l.strip():
            va, name, conv = l.split('\t')[:3]
            out.append((va, name, conv.strip()))
    return out


def call_graph(cands):
    """name -> set(callees within the candidate set), for topological order."""
    src = open('BMF.c', errors='replace').read().split('\n')
    sites = sorted((int(l.split('\t')[3]), l.split('\t')[1])
                   for l in open('sites.txt') if l.strip())
    spans = {}
    for i, (ln, nm) in enumerate(sites):
        end = sites[i + 1][0] - 1 if i + 1 < len(sites) else len(src)
        spans[nm] = (ln, end)
    names = {c[1] for c in cands}
    g = {}
    for _, n, _ in cands:
        a, b = spans[n]
        body = '\n'.join(src[a - 1:b])
        g[n] = {c for c in re.findall(r'\b(sub_[0-9A-Fa-f]{6})\s*\(', body)
                if c in names and c != n}
    return g


def toposort(cands, g):
    order, seen, stack = [], set(), set()
    byname = {c[1]: c for c in cands}

    def visit(n):
        if n in seen:
            return
        if n in stack:          # recursion cycle: emit anyway, order is moot
            return
        stack.add(n)
        for c in sorted(g.get(n, ())):
            visit(c)
        stack.discard(n)
        seen.add(n)
        order.append(byname[n])

    for _, n, _ in cands:
        visit(n)
    return order


def main():
    cands = load_candidates(sys.argv[1] if len(sys.argv) > 1 else 'extractable.txt')
    order = toposort(cands, call_graph(cands))
    print(f"{len(order)} candidates, callees-first order\n")

    accepted = [l.rstrip('\n') for l in open('accepted.txt')] if os.path.exists('accepted.txt') else []
    accepted = [l for l in accepted if l.strip()]
    done = {l.split()[1] for l in accepted}
    fails = []

    for i, (va, name, conv) in enumerate(order, 1):
        if name in done:
            continue
        tag = f"[{i}/{len(order)}] {name} ({conv})"
        r = run([sys.executable, 'extract.py', name])
        if r.returncode != 0:
            print(f"{tag}: SKIP - {r.stderr.strip().splitlines()[-1][:100]}")
            fails.append((name, 'extract: ' + r.stderr.strip().splitlines()[-1][:90]))
            continue

        saved = list(accepted)
        accepted.append(f"{va} {name} {conv}")
        open('accepted.txt', 'w').write('\n'.join(accepted) + '\n')

        b = run('./build.sh')
        if b.returncode != 0:
            err = [l for l in b.stderr.splitlines() if ' error' in l]
            reason = 'build: ' + (err[0][:120] if err else b.stderr.strip()[:120])
            print(f"{tag}: BUILD FAIL - {reason}")
            fails.append((name, reason))
            accepted = saved
            open('accepted.txt', 'w').write('\n'.join(accepted) + ('\n' if accepted else ''))
            run('./build.sh')
            continue

        t = run('./test.sh')
        if t.returncode != 0 or 'PASS' not in t.stdout:
            reason = 'test: ' + (t.stdout.strip().splitlines()[0][:110] if t.stdout.strip() else 'failed')
            print(f"{tag}: TEST FAIL - {reason}")
            fails.append((name, reason))
            accepted = saved
            open('accepted.txt', 'w').write('\n'.join(accepted) + ('\n' if accepted else ''))
            run('./build.sh')
            continue

        done.add(name)
        print(f"{tag}: OK ({len(accepted)} accepted)")

    open('fail.txt', 'w').write('\n'.join(f"{n}\t{r}" for n, r in fails) + ('\n' if fails else ''))
    print(f"\naccepted {len(accepted)}, failed {len(fails)}")


if __name__ == '__main__':
    main()
