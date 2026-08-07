// sub_412850 @ 0x00412850 — __thiscall
// Extracted from BMF.c:16675-16829 by extract.py per incdec.md.

typedef int t_sub_412850_Buffer_0;
static t_sub_412850_Buffer_0& __sub_412850_Buffer_0 = *(t_sub_412850_Buffer_0*)0x00443378;
typedef char t_sub_412850_byte_4456F0;
static t_sub_412850_byte_4456F0& __sub_412850_byte_4456F0 = *(t_sub_412850_byte_4456F0*)0x004456F0;
typedef int t_sub_412850_n0x7F800000;
static t_sub_412850_n0x7F800000& __sub_412850_n0x7F800000 = *(t_sub_412850_n0x7F800000*)0x004456E4;
typedef int t_sub_412850_n0x800000;
static t_sub_412850_n0x800000& __sub_412850_n0x800000 = *(t_sub_412850_n0x800000*)0x004456E0;
typedef int t_sub_412850_n0x88;
static t_sub_412850_n0x88& __sub_412850_n0x88 = *(t_sub_412850_n0x88*)0x00445704;


PROBE_DECL(__sub_412850)
__attribute__((force_align_arg_pointer)) __attribute__((thiscall)) BOOL __sub_412850(unsigned __int16 *_this, unsigned __int16 *a2)
{
  PROBE_HIT(__sub_412850);
  int v2; // ebp
  int v3; // esi
  unsigned int __sub_412850_n0x7F800000; // ebx
  unsigned int v5; // eax
  unsigned __int8 *v6; // edi
  unsigned int n0x800000_1; // edx
  int v8; // ebx
  unsigned int __sub_412850_n0x88; // esi
  unsigned int n0x7F800000_1; // ebp
  BOOL result; // eax
  int n0x4000; // edx
  int v13; // ebx
  int v14; // ebp
  unsigned int v15; // eax
  unsigned __int8 *v16; // esi
  int n0x7F800000_3; // edx
  unsigned int n0x800000_3; // ecx
  int v19; // edx
  unsigned int n0x88_1; // ebp
  unsigned int n0x7F800000_4; // ebx
  int n0x4000_1; // ebx
  unsigned int v23; // edi
  int v24; // edi
  unsigned int v25; // esi
  int v26; // esi
  unsigned int v27; // ebp
  unsigned int __sub_412850_n0x800000; // [esp+0h] [ebp-1Ch]
  unsigned int n0x800000_2; // [esp+0h] [ebp-1Ch]
  unsigned int n0x7F800000_2; // [esp+4h] [ebp-18h]
  unsigned __int16 *this_1; // [esp+8h] [ebp-14h]

  v2 = *_this;
  if ( *_this )
  {
    v3 = *(_this + 1);
    if ( !*(_this + 1) )
    {
      v24 = *a2;
      v25 = v24 + a2[1];
      *_this = (v25 + (v24 << 6) - 64) / v25;
      *(_this + 1) = ((a2[1] << 6) + v25 - 64) / v25;
      *(_this + v2 - 1) += 4;
      *(_this + 2) = 512;
      v26 = a2[v2 - 1];
      a2[v2 - 1] = -3 * ((unsigned int)(3 - v26) >> 31) + v26;
      v2 = *_this;
      v3 = *(_this + 1);
    }
    __sub_412850_n0x7F800000 = ::__sub_412850_n0x7F800000;
    __sub_412850_n0x800000 = ::__sub_412850_n0x800000;
    if ( (unsigned int)::__sub_412850_n0x800000 <= 0x800000 )
    {
      LOBYTE(v5) = __sub_412850_byte_4456F0;
      v6 = (unsigned __int8 *)__sub_412850_Buffer_0;
      n0x800000_1 = ::__sub_412850_n0x800000;
      do
      {
        v8 = (unsigned __int8)((_BYTE)v5 << 7) | (__sub_412850_n0x7F800000 << 8);
        v5 = *v6++;
        __sub_412850_Buffer_0 = (int)v6;
        __sub_412850_n0x7F800000 = (v5 >> 1) | v8;
        n0x800000_1 <<= 8;
      }
      while ( n0x800000_1 <= 0x800000 );
      __sub_412850_n0x800000 = n0x800000_1;
      __sub_412850_byte_4456F0 = v5;
      ::__sub_412850_n0x7F800000 = __sub_412850_n0x7F800000;
    }
    __sub_412850_n0x88 = v2 + v3;
    ::__sub_412850_n0x88 = __sub_412850_n0x88;
    n0x7F800000_1 = __sub_412850_n0x800000 / __sub_412850_n0x88 * v2;
    result = __sub_412850_n0x7F800000 >= n0x7F800000_1;
    if ( __sub_412850_n0x7F800000 >= n0x7F800000_1 )
    {
      ::__sub_412850_n0x800000 = __sub_412850_n0x800000 - n0x7F800000_1;
      ::__sub_412850_n0x7F800000 = __sub_412850_n0x7F800000 - n0x7F800000_1;
    }
    else
    {
      ::__sub_412850_n0x800000 = n0x7F800000_1;
    }
    n0x4000 = *(_this + 2);
    if ( __sub_412850_n0x88 > n0x4000 )
    {
      v23 = *(_this + 1);
      *_this -= *_this >> 1;
      *(_this + 1) = v23 - (v23 >> 1);
      if ( n0x4000 < 0x4000 )
        *(_this + 2) = n0x4000 + 64;
    }
    *(_this + result) += 8;
    a2[result] += (unsigned int)::__sub_412850_n0x88 < 0x88;
  }
  else
  {
    v13 = *a2;
    v14 = a2[1];
    n0x800000_2 = ::__sub_412850_n0x800000;
    n0x7F800000_2 = ::__sub_412850_n0x7F800000;
    if ( (unsigned int)::__sub_412850_n0x800000 <= 0x800000 )
    {
      LOBYTE(v15) = __sub_412850_byte_4456F0;
      v16 = (unsigned __int8 *)__sub_412850_Buffer_0;
      n0x7F800000_3 = ::__sub_412850_n0x7F800000;
      this_1 = _this;
      n0x800000_3 = ::__sub_412850_n0x800000;
      do
      {
        v19 = (unsigned __int8)((_BYTE)v15 << 7) | (n0x7F800000_3 << 8);
        v15 = *v16++;
        __sub_412850_Buffer_0 = (int)v16;
        n0x7F800000_3 = (v15 >> 1) | v19;
        n0x800000_3 <<= 8;
      }
      while ( n0x800000_3 <= 0x800000 );
      n0x7F800000_2 = n0x7F800000_3;
      n0x800000_2 = n0x800000_3;
      _this = this_1;
      __sub_412850_byte_4456F0 = v15;
      ::__sub_412850_n0x7F800000 = n0x7F800000_3;
    }
    n0x88_1 = v13 + v14;
    ::__sub_412850_n0x88 = n0x88_1;
    n0x7F800000_4 = n0x800000_2 / n0x88_1 * v13;
    result = n0x7F800000_4 <= n0x7F800000_2;
    if ( n0x7F800000_4 <= n0x7F800000_2 )
    {
      ::__sub_412850_n0x800000 = n0x800000_2 - n0x7F800000_4;
      ::__sub_412850_n0x7F800000 = n0x7F800000_2 - n0x7F800000_4;
    }
    else
    {
      ::__sub_412850_n0x800000 = n0x7F800000_4;
    }
    n0x4000_1 = a2[2];
    if ( n0x88_1 > n0x4000_1 )
    {
      v27 = a2[1];
      *a2 -= *a2 >> 1;
      a2[1] = v27 - (v27 >> 1);
      if ( n0x4000_1 < 0x4000 )
        a2[2] = n0x4000_1 + 64;
    }
    a2[result] += 8;
    *_this = result + 1;
  }
  return result;
}

