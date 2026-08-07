// sub_412110 @ 0x00412110 — __cdecl
// Extracted from BMF.c:16165-16268 by extract.py per incdec.md.

typedef int t_sub_412110_Buffer_0;
static t_sub_412110_Buffer_0& __sub_412110_Buffer_0 = *(t_sub_412110_Buffer_0*)0x00443378;
typedef char t_sub_412110_byte_4456F0;
static t_sub_412110_byte_4456F0& __sub_412110_byte_4456F0 = *(t_sub_412110_byte_4456F0*)0x004456F0;
typedef int t_sub_412110_dword_4456E8;
static t_sub_412110_dword_4456E8& __sub_412110_dword_4456E8 = *(t_sub_412110_dword_4456E8*)0x004456E8;
typedef int t_sub_412110_dword_4456EC;
static t_sub_412110_dword_4456EC& __sub_412110_dword_4456EC = *(t_sub_412110_dword_4456EC*)0x004456EC;
typedef int t_sub_412110_n0x2000;
static t_sub_412110_n0x2000& __sub_412110_n0x2000 = *(t_sub_412110_n0x2000*)0x004456FC;
typedef int t_sub_412110_n0x2000_0;
static t_sub_412110_n0x2000_0& __sub_412110_n0x2000_0 = *(t_sub_412110_n0x2000_0*)0x004456F8;
typedef int t_sub_412110_n0x2000_1;
static t_sub_412110_n0x2000_1& __sub_412110_n0x2000_1 = *(t_sub_412110_n0x2000_1*)0x004456F4;
typedef int t_sub_412110_n0x7F800000;
static t_sub_412110_n0x7F800000& __sub_412110_n0x7F800000 = *(t_sub_412110_n0x7F800000*)0x004456E4;
typedef int t_sub_412110_n0x800000;
static t_sub_412110_n0x800000& __sub_412110_n0x800000 = *(t_sub_412110_n0x800000*)0x004456E0;


PROBE_DECL(__sub_412110)
__attribute__((force_align_arg_pointer)) int __sub_412110(int __sub_412110_n0x2000, unsigned int n8193)
{
  PROBE_HIT(__sub_412110);
  int n0x2000_3; // esi
  unsigned int n8193_1; // ebp
  unsigned int __sub_412110_n0x800000; // ecx
  unsigned int n0x2000_2; // ebx
  int v6; // ebx
  int n0x7F800000_1; // esi
  unsigned int v8; // edi
  int v9; // ebp
  int v10; // eax
  unsigned int v11; // edx
  _BYTE *v12; // ecx
  int v13; // edx
  int n0x800000_3; // eax
  int n0x800000_2; // ecx
  int __sub_412110_n0x7F800000; // [esp+0h] [ebp-20h]
  unsigned int __sub_412110_n0x2000_1; // [esp+4h] [ebp-1Ch]
  unsigned int n0x800000_1; // [esp+4h] [ebp-1Ch]
  char v19; // [esp+8h] [ebp-18h]
  int v20; // [esp+Ch] [ebp-14h]

  n0x2000_3 = __sub_412110_n0x2000;
  n8193_1 = n8193;
  __sub_412110_n0x800000 = ::__sub_412110_n0x800000;
  ::__sub_412110_n0x2000 = n8193;
  ::__sub_412110_n0x2000_1 = __sub_412110_n0x2000;
  __sub_412110_n0x7F800000 = ::__sub_412110_n0x7F800000;
  n0x2000_2 = __sub_412110_n0x2000 + 1;
  __sub_412110_n0x2000_0 = __sub_412110_n0x2000 + 1;
  if ( (unsigned int)::__sub_412110_n0x800000 > 0x800000 )
  {
    __sub_412110_n0x2000_1 = ::__sub_412110_n0x2000;
    goto LABEL_16;
  }
  v6 = __sub_412110_dword_4456E8;
  n0x7F800000_1 = ::__sub_412110_n0x7F800000;
  v20 = __sub_412110_dword_4456EC;
  do
  {
    ++v20;
    v8 = v6;
    v9 = v6;
    if ( (unsigned int)n0x7F800000_1 < 0x7F800000 )
    {
      v19 = 0;
    }
    else
    {
      if ( n0x7F800000_1 >= 0 )
      {
        __sub_412110_dword_4456E8 = ++v6;
        goto LABEL_14;
      }
      v19 = 1;
    }
    *(_BYTE *)__sub_412110_Buffer_0 = v19 + __sub_412110_byte_4456F0;
    v10 = ++__sub_412110_Buffer_0;
    if ( v6 )
    {
      n0x800000_1 = __sub_412110_n0x800000;
      v11 = 0;
      v12 = (_BYTE *)v10;
      do
      {
        *v12 = v19 - 1;
        v12 = (_BYTE *)++__sub_412110_Buffer_0;
        v6 = v9 - v11++ - 1;
      }
      while ( v11 < v8 );
      __sub_412110_n0x800000 = n0x800000_1;
      __sub_412110_dword_4456E8 = v9 - v8;
    }
    __sub_412110_byte_4456F0 = (unsigned int)n0x7F800000_1 >> 23;
LABEL_14:
    __sub_412110_n0x800000 <<= 8;
    n0x7F800000_1 = (n0x7F800000_1 << 8) & 0x7FFFFFFF;
  }
  while ( __sub_412110_n0x800000 <= 0x800000 );
  n8193_1 = ::__sub_412110_n0x2000;
  n0x2000_2 = __sub_412110_n0x2000_0;
  __sub_412110_n0x7F800000 = n0x7F800000_1;
  n0x2000_3 = ::__sub_412110_n0x2000_1;
  __sub_412110_dword_4456EC = v20;
  __sub_412110_n0x2000_1 = ::__sub_412110_n0x2000;
LABEL_16:
  v13 = __sub_412110_n0x800000 / __sub_412110_n0x2000_1 * n0x2000_3;
  n0x800000_3 = (n0x2000_2 - n0x2000_3) * (__sub_412110_n0x800000 / __sub_412110_n0x2000_1);
  n0x800000_2 = __sub_412110_n0x800000 - v13;
  if ( n0x2000_2 < n8193_1 )
    n0x800000_2 = n0x800000_3;
  ::__sub_412110_n0x7F800000 = __sub_412110_n0x7F800000 + v13;
  ::__sub_412110_n0x800000 = n0x800000_2;
  return n0x800000_3;
}

