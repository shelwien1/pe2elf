// sub_413E60 @ 0x00413E60 — __fastcall
// Extracted from BMF.cpp:18298-18418 by extract.py per incdec.md.

typedef int t_sub_413E60_Buffer_0;
static t_sub_413E60_Buffer_0& __sub_413E60_Buffer_0 = *(t_sub_413E60_Buffer_0*)0x00443378;
typedef char t_sub_413E60_byte_4456F0;
static t_sub_413E60_byte_4456F0& __sub_413E60_byte_4456F0 = *(t_sub_413E60_byte_4456F0*)0x004456F0;
typedef int t_sub_413E60_dword_4456E8;
static t_sub_413E60_dword_4456E8& __sub_413E60_dword_4456E8 = *(t_sub_413E60_dword_4456E8*)0x004456E8;
typedef int t_sub_413E60_n0x2000;
static t_sub_413E60_n0x2000& __sub_413E60_n0x2000 = *(t_sub_413E60_n0x2000*)0x004456FC;
typedef int t_sub_413E60_n0x2000_0;
static t_sub_413E60_n0x2000_0& __sub_413E60_n0x2000_0 = *(t_sub_413E60_n0x2000_0*)0x004456F8;
typedef int t_sub_413E60_n0x2000_1;
static t_sub_413E60_n0x2000_1& __sub_413E60_n0x2000_1 = *(t_sub_413E60_n0x2000_1*)0x004456F4;
typedef int t_sub_413E60_n0x7F800000;
static t_sub_413E60_n0x7F800000& __sub_413E60_n0x7F800000 = *(t_sub_413E60_n0x7F800000*)0x004456E4;
typedef int t_sub_413E60_n0x800000;
static t_sub_413E60_n0x800000& __sub_413E60_n0x800000 = *(t_sub_413E60_n0x800000*)0x004456E0;
typedef int t_sub_413E60_n256_1;
static t_sub_413E60_n256_1& __sub_413E60_n256_1 = *(t_sub_413E60_n256_1*)0x00445708;

static inline int __fwd_sub_413E60_sub_414060(void *a0) { return __sub_414060((unsigned __int16 *)a0); }
#define sub_414060 __fwd_sub_413E60_sub_414060

PROBE_DECL(__sub_413E60)
BMF_REALIGN __attribute__((fastcall)) int __sub_413E60(_WORD *a1, int a2, int a3)
{
  PROBE_HIT(__sub_413E60);
  unsigned int __sub_413E60_n0x800000; // ebp
  unsigned int __sub_413E60_n0x2000; // ebx
  unsigned int v5; // edx
  unsigned __int8 *v6; // esi
  int n0x7F800000_1; // edi
  int v8; // edi
  int v9; // edi
  unsigned int __sub_413E60_n0x2000_1; // eax
  _WORD *v11; // esi
  unsigned int n0x2000_2; // edx
  int v13; // eax
  int n0x800000_2; // edi
  int n0x800000_1; // ebp
  __int16 v16; // bx
  int n5; // esi
  _WORD *v19; // ebx
  int n256; // edx
  bool v21; // cf
  unsigned __int16 *v22; // eax
  __int16 v23; // ax
  unsigned int v24; // [esp+8h] [ebp-18h]
  unsigned int __sub_413E60_n0x7F800000; // [esp+Ch] [ebp-14h]

  __sub_413E60_n0x800000 = ::__sub_413E60_n0x800000;
  __sub_413E60_n0x2000 = *a1 & 0x7FFF;
  ::__sub_413E60_n0x2000 = __sub_413E60_n0x2000;
  __sub_413E60_n0x7F800000 = ::__sub_413E60_n0x7F800000;
  if ( (unsigned int)::__sub_413E60_n0x800000 <= 0x800000 )
  {
    LOBYTE(v5) = __sub_413E60_byte_4456F0;
    v6 = (unsigned __int8 *)__sub_413E60_Buffer_0;
    n0x7F800000_1 = ::__sub_413E60_n0x7F800000;
    do
    {
      v8 = (unsigned __int8)((_BYTE)v5 << 7) | (n0x7F800000_1 << 8);
      v5 = *v6++;
      __sub_413E60_Buffer_0 = (int)v6;
      n0x7F800000_1 = (v5 >> 1) | v8;
      __sub_413E60_n0x800000 <<= 8;
    }
    while ( __sub_413E60_n0x800000 <= 0x800000 );
    __sub_413E60_n0x7F800000 = n0x7F800000_1;
    __sub_413E60_byte_4456F0 = v5;
  }
  __sub_413E60_n0x2000_0 = 0;
  v9 = __sub_413E60_n0x800000 / __sub_413E60_n0x2000;
  __sub_413E60_n0x2000_1 = __sub_413E60_n0x7F800000 / (__sub_413E60_n0x800000 / __sub_413E60_n0x2000);
  __sub_413E60_dword_4456E8 = __sub_413E60_n0x800000 / __sub_413E60_n0x2000;
  if ( __sub_413E60_n0x2000_1 >= __sub_413E60_n0x2000 )
    __sub_413E60_n0x2000_1 = __sub_413E60_n0x2000 - 1;
  v11 = a1 + 1;
  n0x2000_2 = (unsigned __int16)a1[1];
  v24 = (unsigned int)(a1 + 1);
  for ( __sub_413E60_n0x2000_0 = n0x2000_2; n0x2000_2 <= __sub_413E60_n0x2000_1; __sub_413E60_n0x2000_0 = n0x2000_2 )
    n0x2000_2 += (unsigned __int16)*++v11;
  ::__sub_413E60_n0x2000_1 = n0x2000_2 - (unsigned __int16)*v11;
  v13 = ::__sub_413E60_n0x2000_1 * v9;
  n0x800000_2 = (n0x2000_2 - ::__sub_413E60_n0x2000_1) * v9;
  ::__sub_413E60_n0x7F800000 = __sub_413E60_n0x7F800000 - v13;
  n0x800000_1 = __sub_413E60_n0x800000 - v13;
  if ( n0x2000_2 < __sub_413E60_n0x2000 )
    n0x800000_1 = n0x800000_2;
  ::__sub_413E60_n0x800000 = n0x800000_1;
  if ( __sub_413E60_n0x2000 > 0x2000 )
  {
    *a1 = 0x8000;
    v19 = a1 + 7;
    n256 = 256;
    v21 = (unsigned int)(a1 + 7) < v24;
    v22 = a1 + 7;
    if ( (unsigned int)(a1 + 7) >= v24 )
    {
      do
      {
        if ( *v22 < n256 )
          n256 = *v22;
        --v22;
      }
      while ( (unsigned int)v22 >= v24 );
      v21 = (unsigned int)v19 < v24;
    }
    if ( !v21 )
    {
      do
      {
        if ( (unsigned __int16)n256 <= 1u )
          v23 = *v19 - (*v19 >> 1);
        else
          v23 = ((unsigned __int16)*v19 + 2) / 3;
        *v19 = v23;
        *a1 += v23;
        --v19;
      }
      while ( (unsigned int)v19 >= v24 );
    }
  }
  *v11 += 32;
  v16 = *a1 + 32;
  *a1 = v16;
  n5 = (int)((int)v11 - v24) >> 1;
  if ( n5 >= 5 )
    n5 += 2
        * sub_414060(
            (unsigned __int16 *)__sub_413E60_n256_1
          + 32512 * (n5 & 1)
          + 254
          * ((((unsigned __int16)a1[1] + (v16 & 0x7FFF) + 96 - 2 * (unsigned int)(unsigned __int16)a1[n5 + 1]) >> 25)
           & 0xFFFFFFC0)
          + 254 * a3);
  return n5;
}

#undef sub_414060
