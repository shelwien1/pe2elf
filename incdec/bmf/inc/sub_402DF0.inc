// sub_402DF0 @ 0x00402DF0 — __thiscall
// Extracted from BMF.c:2393-2401 by extract.py per incdec.md.

#ifndef __PE_DECL___Block
#define __PE_DECL___Block
typedef int t_Block[0x10000];
static t_Block& __Block = *(t_Block*)0x00445988;
#endif
#define Block __Block

#ifndef __PE_DECL___sub_402FB0
#define __PE_DECL___sub_402FB0
typedef __attribute__((thiscall)) int t_sub_402FB0(...);
static t_sub_402FB0& __sub_402FB0 = *(t_sub_402FB0*)0x00402FB0;
#endif
#define sub_402FB0 __sub_402FB0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_delete
#define __PE_DECL___op_delete
typedef void t_op_delete(void *);       // ??3@YAXPAX@Z
static t_op_delete& __op_delete = *(t_op_delete*)0x0042CF18;
#endif
#define FILE FILE1

PROBE_DECL(__sub_402DF0)
__attribute__((thiscall)) FILE **__sub_402DF0(FILE **Block, char a2)
{
  PROBE_HIT(__sub_402DF0);
  sub_402FB0(Block);
  if ( (a2 & 1) != 0 )
    __op_delete(Block);
  return Block;
}

#undef FILE
#undef Block
#undef sub_402FB0
