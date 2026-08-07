// sub_424500 @ 0x00424500 — __cdecl
// Extracted from BMF.c:30111-30124 by extract.py per incdec.md.

#ifndef __PE_DECL___sub_424550
#define __PE_DECL___sub_424550
typedef __attribute__((thiscall)) void t_sub_424550(int _this, void *, void *);
static t_sub_424550& __sub_424550 = *(t_sub_424550*)0x00424550;
#endif
#define sub_424550 __sub_424550
static inline void ** __fwd_sub_424500_sub_4244A0(void *a0, char a1) { return __sub_4244A0((void **)a0, a1); }
#define sub_4244A0 __fwd_sub_424500_sub_4244A0
static inline int * __fwd_sub_424500_sub_4256F0(void *a0, int a1, int a2, int a3) { return __sub_4256F0((int *)a0, a1, a2, a3); }
#define sub_4256F0 __fwd_sub_424500_sub_4256F0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#define FILE FILE1

PROBE_DECL(__sub_424500)
void __sub_424500(_BYTE *a1, int i, int a3, _BYTE *a4)
{
  PROBE_HIT(__sub_424500);
  int *v4; // eax
  void **v5; // esi

  v4 = (int *)__op_new(0x99D4D8u);
  if ( v4 )
    v5 = (void **)sub_4256F0(v4, i, a3, 0);
  else
    v5 = nullptr;
  sub_424550((int)v5, a1, a4);
  if ( v5 )
    sub_4244A0(v5, 1);
}

#undef FILE
#undef sub_4244A0
#undef sub_424550
#undef sub_4256F0
