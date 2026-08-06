// sub_42B830 @ 0x0042B830 — __cdecl
// Extracted from BMF.c:35919-36014 by extract.py per incdec.md.

#ifndef __PE_DECL___a1
#define __PE_DECL___a1
typedef int t_a1[0x10000];
static t_a1& __a1 = *(t_a1*)0x00439BFC;
#endif
#define a1 __a1
#ifndef __PE_DECL___n5
#define __PE_DECL___n5
typedef int t_n5;
static t_n5& __n5 = *(t_n5*)0x004433F0;
#endif
#define n5 __n5

#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef int t_sub_4349F0(...);
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#define FILE FILE1

PROBE_DECL(__sub_42B830)
int *__sub_42B830(int a1, int a2, int n5, int a4, int a5)
{
  PROBE_HIT(__sub_42B830);
  unsigned int v5; // eax
  int n4; // ebp
  int v7; // esi
  int v8; // eax
  int v9; // edi
  int v10; // ebp
  int Size; // ebx
  int *result; // eax
  char v13; // fps
  char *buf; // edx
  int *v15; // [esp+0h] [ebp-14h]

  LOWORD(v5) = a1;
  n4 = n5;
  v7 = (unsigned __int8)n5 << 16;
  if ( n5 >= 5 && n5 <= 7 )
    goto LABEL_19;
  if ( n5 == 3 )
  {
    n4 = 4;
  }
  else
  {
    if ( !a5 )
    {
      n4 = 4;
      if ( n5 > 4 )
        n4 = n5;
    }
    if ( n4 >= 8 )
      goto LABEL_18;
  }
  if ( !a5 )
  {
    if ( n4 == 4 )
    {
      v5 = ((a1 + 7) >> 1) & 0xFFFFFFFC;
LABEL_19:
      v9 = (unsigned __int16)v5;
      goto LABEL_20;
    }
LABEL_18:
    LOWORD(v5) = ((n4 + 7) >> 3) * a1;
    goto LABEL_19;
  }
  if ( n4 == 1 )
  {
    v8 = (int)(((unsigned int)((a1 + 7) >> 2) >> 29) + a1 + 7) >> 3;
  }
  else if ( n4 == 2 )
  {
    v8 = (int)(((unsigned int)((a1 + 3) >> 1) >> 30) + a1 + 3) >> 2;
  }
  else
  {
    v8 = (int)(a1 + ((unsigned int)(a1 + 1) >> 31) + 1) >> 1;
  }
  v7 = ((unsigned __int8)n5 << 16) | 0x40000000;
  v9 = (unsigned __int16)v8;
LABEL_20:
  v10 = v9 * a2;
  if ( a4 )
  {
    Size = 3 << n5;
    if ( n5 > 8 )
      Size = 0;
    else
      v7 = ((BYTE2(v7) | 0xFFFF0080) << 16) | v7 & 0xFF00FFFF;
  }
  else
  {
    Size = 0;
  }
  result = (int *)__op_new(v10 + Size + 19);
  if ( !result )
    return nullptr;
  *result = (a2 << 16) | (unsigned __int16)a1;
  result[1] = v9;
  result[2] = v7;
  result[3] = v10;
  if ( Size )
  {
    if ( (*((_BYTE *)result + 10) & 0x80) != 0 )
      buf = (char *)result + result[3] + 16;
    else
      buf = nullptr;
    v15 = result;
    sub_4349F0(Size, v13, buf, 0, Size);
    return v15;
  }
  return result;
}

#undef FILE
#undef a1
#undef n5
#undef sub_4349F0
