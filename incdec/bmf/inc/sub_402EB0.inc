// sub_402EB0 @ 0x00402EB0 — __cdecl
// Extracted from BMF.c:2503-2514 by extract.py per incdec.md.


// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#define FILE FILE1

PROBE_DECL(__sub_402EB0)
_DWORD *__sub_402EB0(int n256, int a2)
{
  PROBE_HIT(__sub_402EB0);
  unsigned int v2; // esi
  _DWORD *result; // eax

  v2 = (a2 + (a2 == 0) + 3) & 0xFFFFFFFC;
  result = __op_new(v2 + 8);
  *result = n256;
  result[1] = v2;
  *(_DWORD *)((char *)result + v2 + 4) = 0;
  return result;
}

#undef FILE
