
## Incremental decompilation manual

0. The project is to decompile PPMonstr.exe to C++ source which compiles and works.
"Working" is verified after each step (like redirecting a function from PPMonstr.elf to dummy.so)

1. we need to decompile only main,Alloc_PPMblock,PrintStats,sub_14* - others are library functions.

2. "./pe2elf --inject=dummy.so PPMonstr.exe PPMonstr.elf" can be used to inject an extra dll into a program.
See dummy.cpp for dummy.so source.
the idea is to move function bodies from PPMonstr.cpp to dummy.cpp one by one
(incremental decompilation), then redirect the usage from function code in PPMonstr.elf to their
versions in dummy.so (by patching a JMP instruction to dummy version into function's code). 
Once all relevant functions are moved and program still passes the test, it means we can 
build a standalone version of original program from the set of dummy functions.

3. actually write each function (after extraction from PPMonstr.cpp) into its own file, then #include that file in dummy.cpp.
For example, put source of sub_14001A5C0() into sub_14001A5C0.inc, then #include "sub_14001A5C0.inc" into dummy.cpp
after standard libraries. Let's also rename it by adding two underscores as prefix, to avoid name collisions.

4. to redirect function usage from PPMonstr.elf code to dummy.so, we'd need dummy_init() to patch in a JMP instruction
at function's original address to new address of that function. Original address can be found either from the name
of the function (eg. sub_14001A5C0), or from PPMonstr.txt file. 
Note that patching the code would require first getting write access to that memory.

5. Missing dependencies have to be added to function's file, in form of references;
For example, if function uses "arch_hdr", and we see in .cpp it defined like this:
  int arch_hdr[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
then we don't copy this full definition, but make a reference instead:
typedef int (t_arch_hdr)[16]; t_arch_hdr& arch_hdr = \*(t_arch_hdr\*)0x140028E50;
Address can be found by name from PPMonstr.txt file, which looks like this:
...
0140028E48  f_ENC
0140028E4C  f_LOG
0140028E50  arch_hdr
0140028EFF  byte_140028EFF
...
Same for functions:
we see this in decompiled code: "    v3 = unknown_libname_22(4, v20);", 
we look up it's prototype in PPMonstr.cpp: "__int64 unknown_libname_22(_QWORD, _QWORD);",
also look up it's address in PPMonstr.txt: "0140021696  unknown_libname_22"
then define a reference:
typedef __int64 t_unknown_libname_22(_QWORD, _QWORD); 
t_unknown_libname_22& unknown_libname_22 = \*(t_unknown_libname_22\*)0x140021696;

