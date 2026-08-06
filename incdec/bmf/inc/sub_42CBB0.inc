// sub_42CBB0 @ 0x0042CBB0 — __cdecl
// Extracted from BMF.c:37124-37133 by extract.py per incdec.md.

typedef int t_sub_42CBB0_dword_445930;
static t_sub_42CBB0_dword_445930& __sub_42CBB0_dword_445930 = *(t_sub_42CBB0_dword_445930*)0x00445930;
#define dword_445930 __sub_42CBB0_dword_445930


PROBE_DECL(__sub_42CBB0)
int __sub_42CBB0(int a1)
{
  PROBE_HIT(__sub_42CBB0);
  int result; // eax

  result = dword_445930;
  dword_445930 = a1;
  return result;
}

#undef dword_445930
