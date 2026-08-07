// sub_42BA40 @ 0x0042BA40 — __thiscall
// Extracted from BMF.c:36123-36189 by extract.py per incdec.md.

#ifndef __PE_DECL___sub_428BE0
#define __PE_DECL___sub_428BE0
typedef int t_sub_428BE0(...);
static t_sub_428BE0& __sub_428BE0 = *(t_sub_428BE0*)0x00428BE0;
#endif
#define sub_428BE0 __sub_428BE0

PROBE_DECL(__sub_42BA40)
__attribute__((thiscall)) unsigned int __sub_42BA40(_WORD *_this, int a2, int sub_428BE0, int n5, int a5)
{
  PROBE_HIT(__sub_42BA40);
  unsigned int v5; // eax
  int n5_1; // ebx
  unsigned int result; // eax

  LOWORD(v5) = a2;
  n5_1 = n5;
  *_this = a2;
  *(_this + 1) = sub_428BE0;
  *(_this + 4) = 0;
  *(_this + 3) = 0;
  *((_BYTE *)_this + 10) = n5;
  if ( n5 >= 5 && n5 <= 7 )
  {
    *((_BYTE *)_this + 11) = 0;
LABEL_21:
    v5 = (unsigned __int16)v5;
    *(_this + 2) = v5;
    goto LABEL_22;
  }
  if ( n5 == 3 )
  {
    n5_1 = 4;
  }
  else
  {
    if ( !a5 && n5 <= 4 )
      n5_1 = 4;
    if ( n5_1 >= 8 )
    {
      *((_BYTE *)_this + 11) = 0;
      goto LABEL_20;
    }
  }
  if ( !a5 )
  {
    *((_BYTE *)_this + 11) = 0;
    if ( n5_1 == 4 )
    {
      v5 = ((a2 + 7) >> 1) & 0xFFFFFFFC;
      goto LABEL_21;
    }
LABEL_20:
    LOWORD(v5) = ((n5_1 + 7) >> 3) * a2;
    goto LABEL_21;
  }
  if ( n5_1 == 1 )
  {
    v5 = (int)(((unsigned int)((a2 + 7) >> 2) >> 29) + a2 + 7) >> 3;
  }
  else if ( n5_1 == 2 )
  {
    v5 = (int)(((unsigned int)((a2 + 3) >> 1) >> 30) + a2 + 3) >> 2;
  }
  else
  {
    v5 = (int)(a2 + ((unsigned int)(a2 + 1) >> 31) + 1) >> 1;
  }
  *((_BYTE *)_this + 11) = 64;
  v5 = (unsigned __int16)v5;
  *(_this + 2) = v5;
LABEL_22:
  result = sub_428BE0 * v5;
  *((_DWORD *)_this + 3) = result;
  return result;
}

#undef sub_428BE0
