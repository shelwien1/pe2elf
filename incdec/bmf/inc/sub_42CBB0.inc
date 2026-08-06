// sub_42CBB0 @ 0x0042CBB0 — __cdecl
// Extracted from BMF.c:37124-37134 by extract.py per incdec.md.

#ifndef __PE_DECL___a1
#define __PE_DECL___a1
typedef int t_a1[0x10000];
static t_a1& __a1 = *(t_a1*)0x00439BFC;
#endif
#define a1 __a1
#ifndef __PE_DECL___dword_445930
#define __PE_DECL___dword_445930
typedef int t_dword_445930;
static t_dword_445930& __dword_445930 = *(t_dword_445930*)0x00445930;
#endif
#define dword_445930 __dword_445930


PROBE_DECL(__sub_42CBB0)
int __sub_42CBB0(int a1)
{
  PROBE_HIT(__sub_42CBB0);
  int result; // eax

  result = dword_445930;
  dword_445930 = a1;
  return result;
}

#undef a1
#undef dword_445930
