// sub_402E70 @ 0x00402E70 — __thiscall
// Extracted from BMF.c:2492-2500 by extract.py per incdec.md.


// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_delete
#define __PE_DECL___op_delete
typedef void t_op_delete(void *);       // ??3@YAXPAX@Z
static t_op_delete& __op_delete = *(t_op_delete*)0x0042CF18;
#endif
#define FILE FILE1

PROBE_DECL(__sub_402E70)
__attribute__((thiscall)) void **__sub_402E70(void **Blockb, char a2)
{
  PROBE_HIT(__sub_402E70);
  __op_delete(*(Blockb + 24));
  __op_delete(*(Blockb + 19));
  __op_delete(*(Blockb + 20));
  if ( (a2 & 1) != 0 )
    __op_delete(Blockb);
  return Blockb;
}

#undef FILE
