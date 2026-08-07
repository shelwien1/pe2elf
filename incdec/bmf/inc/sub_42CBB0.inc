// sub_42CBB0 @ 0x0042CBB0 — __cdecl
// Extracted from BMF.cpp:37179-37187 by extract.py per incdec.md.

typedef int t_sub_42CBB0_psub_402E30;
static t_sub_42CBB0_psub_402E30& __sub_42CBB0_psub_402E30 = *(t_sub_42CBB0_psub_402E30*)(blob1 + 0x00445930 - BMF_BLOB_BASE);

#ifndef __PE_DECL___sub_402E30
#define __PE_DECL___sub_402E30
// No decompiled body — IDA's call analysis failed on it. Only its address is used.
typedef void t_sub_402E30();
static t_sub_402E30& __sub_402E30 = *(t_sub_402E30*)0x00402E30;
#endif
#define sub_402E30 __sub_402E30

PROBE_DECL(__sub_42CBB0)
BMF_REALIGN int __sub_42CBB0(int sub_402E30)
{
  PROBE_HIT(__sub_42CBB0);
  int __sub_42CBB0_psub_402E30; // eax

  __sub_42CBB0_psub_402E30 = ::__sub_42CBB0_psub_402E30;
  ::__sub_42CBB0_psub_402E30 = sub_402E30;
  return __sub_42CBB0_psub_402E30;
}

#undef sub_402E30
