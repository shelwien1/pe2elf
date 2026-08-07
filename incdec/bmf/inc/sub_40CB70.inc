// sub_40CB70 @ 0x0040CB70 — __cdecl
// Extracted from BMF.cpp:10575-10645 by extract.py per incdec.md.

typedef int t_sub_40CB70_buf_1;
static t_sub_40CB70_buf_1& __sub_40CB70_buf_1 = *(t_sub_40CB70_buf_1*)0x00443430;
typedef int t_sub_40CB70_dword_442EE0[0x10000];
static t_sub_40CB70_dword_442EE0& __sub_40CB70_dword_442EE0 = *(t_sub_40CB70_dword_442EE0*)0x00442EE0;
typedef int t_sub_40CB70_dword_443428;
static t_sub_40CB70_dword_443428& __sub_40CB70_dword_443428 = *(t_sub_40CB70_dword_443428*)0x00443428;
typedef int t_sub_40CB70_dword_44342C;
static t_sub_40CB70_dword_44342C& __sub_40CB70_dword_44342C = *(t_sub_40CB70_dword_44342C*)0x0044342C;
typedef __int128 t_sub_40CB70_xmmword_442EA0;
static t_sub_40CB70_xmmword_442EA0& __sub_40CB70_xmmword_442EA0 = *(t_sub_40CB70_xmmword_442EA0*)0x00442EA0;


PROBE_DECL(__sub_40CB70)
BMF_REALIGN int __sub_40CB70()
{
  PROBE_HIT(__sub_40CB70);
  int v0; // ecx
  int n4; // eax
  int *v2; // edx
  int v3; // ebx
  int v4; // edi
  int v5; // ebp
  int v6; // eax
  int v7; // eax
  int n4_1; // [esp+4h] [ebp-18h]
  char v9; // [esp+Ch] [ebp-10h]

  v0 = 1;
  if ( *(int *)(__sub_40CB70_dword_44342C + 4) < 0 )
  {
    do
    {
      ++v0;
      n4 = 4 * v0;
      v2 = (int *)(__sub_40CB70_dword_44342C + 4 * v0);
    }
    while ( *v2 < 0 );
  }
  else
  {
    n4 = 4;
    v2 = (int *)(__sub_40CB70_dword_44342C + 4);
  }
  v3 = (1 << (v0 & 31)) - 1;
  if ( v3 >= 0 )
  {
    v4 = __sub_40CB70_buf_1;
    v5 = __sub_40CB70_dword_443428;
    __sub_40CB70_dword_44342C = (int)v2;
    v9 = v0;
    n4_1 = n4;
    do
    {
      v6 = *v2;
      *(_WORD *)(v4 + 4 * v6) = v5 | ((_WORD)v3 << ((((unsigned int)((char *)v2 - (char *)&__sub_40CB70_xmmword_442EA0) >> 2) - v9) & 31));
      v7 = __sub_40CB70_dword_442EE0[v6];
      *v2 = v7;
      if ( v7 < 0 )
      {
        if ( --v3 >= 0 )
        {
          do
          {
            __sub_40CB70_dword_443428 = v5 | (v3 << ((((unsigned int)(__sub_40CB70_dword_44342C - (_DWORD)&__sub_40CB70_xmmword_442EA0) >> 2) - v9) & 31));
            __sub_40CB70();
            --v3;
          }
          while ( v3 >= 0 );
          v2 = (int *)__sub_40CB70_dword_44342C;
        }
        __sub_40CB70_dword_443428 = v5;
      }
      --v3;
    }
    while ( v3 >= 0 );
    n4 = n4_1;
  }
  __sub_40CB70_dword_44342C = (int)v2 - n4;
  return n4;
}

