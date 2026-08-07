// sub_40E4D0 @ 0x0040E4D0 — __cdecl
// Extracted from BMF.cpp:12287-12360 by extract.py per incdec.md.

typedef int t_sub_40E4D0_dword_442EE0[0x10000];
static t_sub_40E4D0_dword_442EE0& __sub_40E4D0_dword_442EE0 = *(t_sub_40E4D0_dword_442EE0*)0x00442EE0;
typedef int t_sub_40E4D0_dword_44342C;
static t_sub_40E4D0_dword_44342C& __sub_40E4D0_dword_44342C = *(t_sub_40E4D0_dword_44342C*)0x0044342C;
typedef int t_sub_40E4D0_dword_443434;
static t_sub_40E4D0_dword_443434& __sub_40E4D0_dword_443434 = *(t_sub_40E4D0_dword_443434*)0x00443434;
typedef int t_sub_40E4D0_dword_443438;
static t_sub_40E4D0_dword_443438& __sub_40E4D0_dword_443438 = *(t_sub_40E4D0_dword_443438*)0x00443438;


PROBE_DECL(__sub_40E4D0)
__attribute__((force_align_arg_pointer)) int *__sub_40E4D0()
{
  PROBE_HIT(__sub_40E4D0);
  int v0; // ecx
  int n4; // ebx
  int *v2; // edx
  int *v3; // edi
  int v4; // eax
  int *result; // eax
  int v6; // ebp
  int v7; // ecx
  int v8; // ecx

  v0 = 1;
  if ( *(int *)(__sub_40E4D0_dword_44342C + 4) < 0 )
  {
    do
    {
      ++v0;
      n4 = 4 * v0;
      v2 = (int *)(__sub_40E4D0_dword_44342C + 4 * v0);
    }
    while ( *v2 < 0 );
  }
  else
  {
    n4 = 4;
    v2 = (int *)(__sub_40E4D0_dword_44342C + 4);
  }
  v3 = (int *)__sub_40E4D0_dword_443434;
  v4 = __sub_40E4D0_dword_443438;
  *(_DWORD *)(__sub_40E4D0_dword_443434 + 4) = v0;
  *v3 = (v4 - (int)v3) >> 3;
  __sub_40E4D0_dword_443438 = v4 + 8 * (1 << (v0 & 31));
  result = (int *)(__sub_40E4D0_dword_443438 - 8);
  v6 = (1 << (v0 & 31)) - 1;
  if ( v6 >= 0 )
  {
    __sub_40E4D0_dword_44342C = (int)v2;
    do
    {
      v7 = *v2;
      result[1] = 0;
      *result = v7;
      v8 = __sub_40E4D0_dword_442EE0[v7];
      *v2 = v8;
      if ( v8 < 0 )
      {
        result -= 2;
        if ( --v6 >= 0 )
        {
          do
          {
            __sub_40E4D0_dword_443434 = (int)result;
            __sub_40E4D0();
            result = (int *)(__sub_40E4D0_dword_443434 - 8);
            --v6;
          }
          while ( v6 >= 0 );
          v2 = (int *)__sub_40E4D0_dword_44342C;
        }
      }
      result -= 2;
      --v6;
    }
    while ( v6 >= 0 );
  }
  __sub_40E4D0_dword_443434 = (int)v3;
  __sub_40E4D0_dword_44342C = (int)&v2[n4 / 0xFFFFFFFC];
  return result;
}

