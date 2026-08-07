// sub_4244A0 @ 0x004244A0 — __thiscall
// Extracted from BMF.cpp:30098-30108 by extract.py per incdec.md.


// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_delete
#define __PE_DECL___op_delete
typedef void t_op_delete(void *);       // ??3@YAXPAX@Z
static t_op_delete& __op_delete = *(t_op_delete*)0x0042CF18;
#endif
#define FILE FILE1

PROBE_DECL(__sub_4244A0)
__attribute__((force_align_arg_pointer)) __attribute__((thiscall)) void **__sub_4244A0(void **Block, char a2)
{
  PROBE_HIT(__sub_4244A0);
  __op_delete(*(Block + 44));
  __op_delete(*(Block + 45));
  __op_delete(*(Block + 46));
  __op_delete(*(Block + 47));
  __op_delete(*(Block + 48));
  if ( (a2 & 1) != 0 )
    __op_delete(Block);
  return Block;
}

#undef FILE
