// sub_42CBB0 @ 0x0042CBB0 — __cdecl
// Extracted from BMF.cpp:37179-37187 by extract.py per incdec.md.

typedef int t_sub_42CBB0_psub_402E30;
static t_sub_42CBB0_psub_402E30& __sub_42CBB0_psub_402E30 = *(t_sub_42CBB0_psub_402E30*)0x00445930;


PROBE_DECL(__sub_42CBB0)
__attribute__((force_align_arg_pointer)) int __sub_42CBB0(int sub_402E30)
{
  PROBE_HIT(__sub_42CBB0);
  int __sub_42CBB0_psub_402E30; // eax

  __sub_42CBB0_psub_402E30 = ::__sub_42CBB0_psub_402E30;
  ::__sub_42CBB0_psub_402E30 = sub_402E30;
  return __sub_42CBB0_psub_402E30;
}

