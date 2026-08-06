// sub_414620 @ 0x00414620 — __thiscall
// Extracted from BMF.c:18804-18931 by extract.py per incdec.md.

typedef int t_sub_414620_Buffer_0;
static t_sub_414620_Buffer_0& __sub_414620_Buffer_0 = *(t_sub_414620_Buffer_0*)0x00443378;
#define Buffer_0 __sub_414620_Buffer_0
typedef char t_sub_414620_byte_4456F0;
static t_sub_414620_byte_4456F0& __sub_414620_byte_4456F0 = *(t_sub_414620_byte_4456F0*)0x004456F0;
#define byte_4456F0 __sub_414620_byte_4456F0
typedef int t_sub_414620_dword_4456E8;
static t_sub_414620_dword_4456E8& __sub_414620_dword_4456E8 = *(t_sub_414620_dword_4456E8*)0x004456E8;
#define dword_4456E8 __sub_414620_dword_4456E8
typedef int t_sub_414620_n0x2000;
static t_sub_414620_n0x2000& __sub_414620_n0x2000 = *(t_sub_414620_n0x2000*)0x004456FC;
#define n0x2000 __sub_414620_n0x2000
typedef int t_sub_414620_n0x2000_0;
static t_sub_414620_n0x2000_0& __sub_414620_n0x2000_0 = *(t_sub_414620_n0x2000_0*)0x004456F8;
#define n0x2000_0 __sub_414620_n0x2000_0
typedef int t_sub_414620_n0x2000_1;
static t_sub_414620_n0x2000_1& __sub_414620_n0x2000_1 = *(t_sub_414620_n0x2000_1*)0x004456F4;
#define n0x2000_1 __sub_414620_n0x2000_1
typedef int t_sub_414620_n0x7F800000;
static t_sub_414620_n0x7F800000& __sub_414620_n0x7F800000 = *(t_sub_414620_n0x7F800000*)0x004456E4;
#define n0x7F800000 __sub_414620_n0x7F800000
typedef int t_sub_414620_n0x800000;
static t_sub_414620_n0x800000& __sub_414620_n0x800000 = *(t_sub_414620_n0x800000*)0x004456E0;
#define n0x800000 __sub_414620_n0x800000
typedef int t_sub_414620_n256_1;
static t_sub_414620_n256_1& __sub_414620_n256_1 = *(t_sub_414620_n256_1*)0x00445708;
#define n256_1 __sub_414620_n256_1

#ifndef __PE_DECL___sub_414060
#define __PE_DECL___sub_414060
typedef __attribute__((thiscall)) int t_sub_414060(...);
static t_sub_414060& __sub_414060 = *(t_sub_414060*)0x00414060;
#endif
#define sub_414060 __sub_414060

PROBE_DECL(__sub_414620)
__attribute__((thiscall)) int __sub_414620(unsigned __int16 *_this, int a2)
{
  PROBE_HIT(__sub_414620);
  unsigned int n0x800000; // ebp
  unsigned int n0x7F800000; // ebx
  unsigned int v4; // edx
  unsigned __int8 *v5; // esi
  int v6; // ebx
  signed int v7; // eax
  signed int v8; // edx
  _WORD *v9; // esi
  int v10; // ecx
  unsigned int v11; // eax
  int v12; // edx
  int n0x800000_1; // ebp
  signed int n0x4000; // eax
  int n32; // edx
  int v16; // esi
  unsigned int v18; // ebp
  unsigned int v19; // eax
  unsigned int v20; // [esp+0h] [ebp-20h]
  int v21; // [esp+4h] [ebp-1Ch]
  int v23; // [esp+8h] [ebp-18h]
  unsigned __int16 *v24; // [esp+8h] [ebp-18h]
  int v25; // [esp+Ch] [ebp-14h]

  n0x800000 = ::n0x800000;
  v23 = *(_this + 3);
  v21 = *(_this + 2) + *(_this + 1);
  n0x7F800000 = ::n0x7F800000;
  v20 = v23 + v21;
  n0x2000 = v23 + v21;
  if ( (unsigned int)::n0x800000 <= 0x800000 )
  {
    LOBYTE(v4) = byte_4456F0;
    v5 = (unsigned __int8 *)Buffer_0;
    do
    {
      v6 = (unsigned __int8)((_BYTE)v4 << 7) | (n0x7F800000 << 8);
      v4 = *v5++;
      Buffer_0 = (int)v5;
      n0x7F800000 = (v4 >> 1) | v6;
      n0x800000 <<= 8;
    }
    while ( n0x800000 <= 0x800000 );
    byte_4456F0 = v4;
  }
  v25 = n0x800000 / v20;
  dword_4456E8 = n0x800000 / v20;
  v7 = n0x7F800000 / (n0x800000 / v20);
  if ( v7 >= v20 )
    v7 = v23 + v21 - 1;
  v8 = *(_this + 1);
  if ( v7 >= v8 )
  {
    if ( v7 >= v21 )
    {
      v8 = v21;
      n0x2000_1 = v21;
      v9 = _this + 3;
    }
    else
    {
      n0x2000_1 = *(_this + 1);
      v9 = _this + 2;
    }
    v24 = _this + 1;
  }
  else
  {
    n0x2000_1 = 0;
    v9 = _this + 1;
    v8 = 0;
    v24 = _this + 1;
  }
  v10 = (unsigned __int16)*v9;
  v11 = v8 + v10;
  v12 = v25 * v8;
  n0x2000_0 = v11;
  ::n0x7F800000 = n0x7F800000 - v12;
  n0x800000_1 = n0x800000 - v12;
  if ( v11 < v20 )
    n0x800000_1 = v10 * v25;
  n0x4000 = (unsigned __int16)*v9;
  ::n0x800000 = n0x800000_1;
  if ( n0x4000 > 0x4000 )
  {
    v18 = *(_this + 2);
    v19 = *(_this + 3);
    *(_this + 1) -= *(_this + 1) >> 1;
    n32 = *_this;
    *(_this + 2) = v18 - (v18 >> 1);
    *(_this + 3) = v19 - (v19 >> 1);
    if ( n32 <= 256 )
    {
      if ( n32 <= 32 )
        n0x4000 = ((unsigned int)(16 - n32) >> 30) & 0xFFFFFFFE;
      else
        LOWORD(n0x4000) = 32;
      LOWORD(n32) = n32 - n0x4000;
      *_this = n32;
      LOWORD(n0x4000) = *v9;
    }
    else
    {
      n32 = (unsigned int)n32 >> 1;
      *_this = n32;
      LOWORD(n0x4000) = *v9;
    }
  }
  else
  {
    LOWORD(n32) = *_this;
  }
  *v9 = n32 + n0x4000;
  v16 = v9 - v24;
  if ( v16 )
    return v16 + 2 * sub_414060((unsigned __int16 *)n256_1 + 254 * *(_DWORD *)(a2 + 4 * (v16 & 1)));
  else
    return 0;
}

#undef Buffer_0
#undef byte_4456F0
#undef dword_4456E8
#undef n0x2000
#undef n0x2000_0
#undef n0x2000_1
#undef n0x7F800000
#undef n0x800000
#undef n256_1
#undef sub_414060
