# dll32/ — 32-bit side DLLs for ordinal-import resolution

`pe2elf32` routes every import to a `dll_Function` symbol in
`winapi_shim32.so`, so an import by *ordinal* has to be translated to the name
the exporting DLL would have advertised for that slot. The converter does that
by parsing the export table of a copy of the DLL dropped in this directory
(`dll32/<lowercase-name>.dll`, e.g. `dll32/oleaut32.dll`); nothing is loaded or
executed, only the export directory is read.

This is deliberately separate from the 64-bit tool's `dll/`: **an x86 DLL
exports a different ordinal-to-name mapping than its x64 sibling**, so mixing
them would silently resolve ordinals to the wrong functions. Put 32-bit builds
here and 64-bit builds in `dll/`.

The directory is empty because no redistributable Windows DLLs ship with this
repo. If a conversion fails with

    Error: cannot resolve ordinal import (DLL 'OLEAUT32.dll' ordinal 2)
           — put a matching dll32/OLEAUT32.dll file alongside the binary

copy the named 32-bit DLL here and re-run. Binaries that import everything by
name need nothing in this directory.
