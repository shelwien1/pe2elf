#!/usr/bin/env python3
"""Generate list.txt: all non-library function definitions in PPMonstr.cpp."""
import re

FN_NAME = re.compile(r'\b(main|Alloc_PPMblock|PrintStats|sub_14[0-9A-Fa-f]+)\b')

def main():
    with open('PPMonstr.cpp') as f:
        lines = f.readlines()

    fns = []
    seen = set()
    depth = 0       # curly-brace depth
    i = 0

    while i < len(lines):
        line = lines[i]

        # Check for a function definition at global scope (depth == 0).
        # A definition header: matches our name pattern and either
        #   (a) contains '{' on this line, or
        #   (b) the next non-blank line contains '{' as the first non-space char.
        if depth == 0:
            m = FN_NAME.search(line)
            if m:
                name = m.group(1)
                # Make sure this is a definition, not a forward declaration ending in ';'
                # Look ahead up to 3 lines for the opening brace.
                lookahead = line + ''.join(lines[i+1:i+4])
                first_semi = lookahead.find(';')
                first_brace = lookahead.find('{')
                is_defn = (first_brace >= 0) and (first_semi < 0 or first_brace < first_semi)
                if is_defn and name not in seen:
                    seen.add(name)
                    fns.append(name)

        # Update brace depth for subsequent lines.
        depth += line.count('{') - line.count('}')
        if depth < 0:
            depth = 0
        i += 1

    with open('list.txt', 'w') as f:
        for name in fns:
            f.write(name + '\n')

    print(f"Found {len(fns)} functions, written to list.txt:")
    for name in fns:
        print(f"  {name}")

if __name__ == '__main__':
    main()
