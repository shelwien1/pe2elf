// sub_402E10 @ 0x00402E10 — __thiscall
// Extracted from BMF.c:2472-2478 by extract.py per incdec.md.

static inline int __fwd_sub_402E10_sub_42C090(void *a0) { return __sub_42C090((FILE1 **)a0); }
#define sub_42C090 __fwd_sub_402E10_sub_42C090

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_delete
#define __PE_DECL___op_delete
typedef void t_op_delete(void *);       // ??3@YAXPAX@Z
static t_op_delete& __op_delete = *(t_op_delete*)0x0042CF18;
#endif
#define FILE FILE1

PROBE_DECL(__sub_402E10)
__attribute__((thiscall)) FILE **__sub_402E10(FILE **Block, char a2)
{
  PROBE_HIT(__sub_402E10);
  sub_42C090(Block);
  if ( (a2 & 1) != 0 )
    __op_delete(Block);
  return Block;
}

#undef FILE
#undef sub_42C090
