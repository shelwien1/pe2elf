// sub_414060 @ 0x00414060 — __thiscall
// Extracted from BMF.cpp:18421-18631 by extract.py per incdec.md.

typedef int t_sub_414060_Buffer_0;
static t_sub_414060_Buffer_0& __sub_414060_Buffer_0 = *(t_sub_414060_Buffer_0*)0x00443378;
typedef char t_sub_414060_byte_4456F0;
static t_sub_414060_byte_4456F0& __sub_414060_byte_4456F0 = *(t_sub_414060_byte_4456F0*)0x004456F0;
typedef unsigned char t_sub_414060_byte_445714[0x10000];
static t_sub_414060_byte_445714& __sub_414060_byte_445714 = *(t_sub_414060_byte_445714*)0x00445714;
typedef unsigned char t_sub_414060_byte_445715[0x10000];
static t_sub_414060_byte_445715& __sub_414060_byte_445715 = *(t_sub_414060_byte_445715*)0x00445715;
typedef unsigned char t_sub_414060_byte_445716[0x10000];
static t_sub_414060_byte_445716& __sub_414060_byte_445716 = *(t_sub_414060_byte_445716*)0x00445716;
typedef int t_sub_414060_dword_4456E8;
static t_sub_414060_dword_4456E8& __sub_414060_dword_4456E8 = *(t_sub_414060_dword_4456E8*)0x004456E8;
typedef int t_sub_414060_n0x2000;
static t_sub_414060_n0x2000& __sub_414060_n0x2000 = *(t_sub_414060_n0x2000*)0x004456FC;
typedef int t_sub_414060_n0x2000_0;
static t_sub_414060_n0x2000_0& __sub_414060_n0x2000_0 = *(t_sub_414060_n0x2000_0*)0x004456F8;
typedef int t_sub_414060_n0x2000_1;
static t_sub_414060_n0x2000_1& __sub_414060_n0x2000_1 = *(t_sub_414060_n0x2000_1*)0x004456F4;
typedef int t_sub_414060_n0x7F800000;
static t_sub_414060_n0x7F800000& __sub_414060_n0x7F800000 = *(t_sub_414060_n0x7F800000*)0x004456E4;
typedef int t_sub_414060_n0x800000;
static t_sub_414060_n0x800000& __sub_414060_n0x800000 = *(t_sub_414060_n0x800000*)0x004456E0;
typedef int t_sub_414060_n0x88;
static t_sub_414060_n0x88& __sub_414060_n0x88 = *(t_sub_414060_n0x88*)0x00445704;
typedef int t_sub_414060_n8_0;
static t_sub_414060_n8_0& __sub_414060_n8_0 = *(t_sub_414060_n8_0*)0x00445710;
typedef int t_sub_414060_n8_1;
static t_sub_414060_n8_1& __sub_414060_n8_1 = *(t_sub_414060_n8_1*)0x0044570C;


PROBE_DECL(__sub_414060)
BMF_REALIGN __attribute__((thiscall)) int __sub_414060(unsigned __int16 *_this)
{
  PROBE_HIT(__sub_414060);
  unsigned int __sub_414060_n0x800000; // ebx
  unsigned int __sub_414060_n0x7F800000; // ebp
  unsigned int v3; // edx
  unsigned __int8 *v4; // esi
  int v5; // ebp
  int v6; // edi
  unsigned int v7; // eax
  unsigned __int16 *v8; // edx
  unsigned int v9; // esi
  int n2_1; // edi
  int v11; // edx
  int v12; // eax
  unsigned int n0x7F800000_1; // ebp
  int n0x800000_2; // edi
  unsigned int n0x800000_1; // ebx
  unsigned __int16 v16; // si
  unsigned __int16 *v17; // ecx
  int v18; // esi
  unsigned int v19; // edx
  unsigned __int8 *v20; // edi
  int v21; // ebp
  unsigned int n0x7F800000_2; // esi
  BOOL v23; // edx
  unsigned __int16 n0x4000; // si
  int v25; // edx
  int v26; // eax
  unsigned __int16 v28; // si
  unsigned int v29; // edi
  unsigned __int16 v30; // si
  __int16 v31; // si
  unsigned __int16 v32; // si
  __int16 v33; // si
  unsigned __int16 v34; // si
  unsigned int v35; // eax
  int v36; // esi
  _WORD *v37; // [esp+0h] [ebp-28h]
  int v38; // [esp+0h] [ebp-28h]
  unsigned int v39; // [esp+4h] [ebp-24h]
  int v40; // [esp+4h] [ebp-24h]
  int n2; // [esp+Ch] [ebp-1Ch]
  int v43; // [esp+10h] [ebp-18h]
  int v44; // [esp+14h] [ebp-14h]

  __sub_414060_n0x800000 = ::__sub_414060_n0x800000;
  __sub_414060_n0x7F800000 = ::__sub_414060_n0x7F800000;
  v39 = *_this;
  __sub_414060_n0x2000 = v39;
  if ( (unsigned int)::__sub_414060_n0x800000 <= 0x800000 )
  {
    LOBYTE(v3) = __sub_414060_byte_4456F0;
    v4 = (unsigned __int8 *)__sub_414060_Buffer_0;
    do
    {
      v5 = (unsigned __int8)((_BYTE)v3 << 7) | (__sub_414060_n0x7F800000 << 8);
      v3 = *v4++;
      __sub_414060_Buffer_0 = (int)v4;
      __sub_414060_n0x7F800000 = (v3 >> 1) | v5;
      __sub_414060_n0x800000 <<= 8;
    }
    while ( __sub_414060_n0x800000 <= 0x800000 );
    __sub_414060_byte_4456F0 = v3;
  }
  __sub_414060_n0x2000_0 = 0;
  n2 = 0;
  v6 = __sub_414060_n0x800000 / v39;
  v7 = __sub_414060_n0x7F800000 / (__sub_414060_n0x800000 / v39);
  __sub_414060_dword_4456E8 = __sub_414060_n0x800000 / v39;
  if ( v7 >= v39 )
    v7 = v39 - 1;
  v8 = _this + 2;
  v9 = *(_this + 2);
  __sub_414060_n0x2000_0 = v9;
  if ( v9 <= v7 )
  {
    n2_1 = 0;
    do
    {
      ++v8;
      ++n2_1;
      v9 += *v8;
      __sub_414060_n0x2000_0 = v9;
    }
    while ( v9 <= v7 );
    n2 = n2_1;
    v6 = __sub_414060_n0x800000 / v39;
  }
  v37 = v8;
  v11 = v9 - *v8;
  v12 = v11 * v6;
  __sub_414060_n0x2000_1 = v11;
  n0x7F800000_1 = __sub_414060_n0x7F800000 - v11 * v6;
  n0x800000_2 = (v9 - v11) * v6;
  n0x800000_1 = __sub_414060_n0x800000 - v12;
  if ( v9 < v39 )
    n0x800000_1 = n0x800000_2;
  if ( *_this > 0x4000u )
  {
    v28 = *(_this + 2) - (*(_this + 2) >> 1);
    v29 = *(_this + 3);
    *(_this + 2) = v28;
    LOWORD(v29) = v29 - (v29 >> 1);
    *(_this + 3) = v29;
    LOWORD(v29) = v28 + v29;
    v30 = *(_this + 4) - (*(_this + 4) >> 1);
    *(_this + 4) = v30;
    v31 = v29 + v30;
    LOWORD(v29) = *(_this + 5) - (*(_this + 5) >> 1);
    *(_this + 5) = v29;
    LOWORD(v29) = v31 + v29;
    v32 = *(_this + 6) - (*(_this + 6) >> 1);
    *(_this + 6) = v32;
    v33 = v29 + v32;
    LOWORD(v29) = *(_this + 7) - (*(_this + 7) >> 1);
    *(_this + 7) = v29;
    LOWORD(v29) = v33 + v29;
    v34 = *(_this + 8) - (*(_this + 8) >> 1);
    v35 = *(_this + 9);
    *(_this + 8) = v34;
    LOWORD(v35) = v35 - (v35 >> 1);
    *(_this + 9) = v35;
    LOWORD(v35) = v29 + v34 + v35;
    v36 = *(_this + 1);
    *_this = v35;
    if ( v36 <= 4 * __sub_414060_n8_1 )
      v16 = v36 - 4 * (v36 > __sub_414060_n8_1);
    else
      v16 = v36 - 16;
    *(_this + 1) = v16;
  }
  else
  {
    v16 = *(_this + 1);
  }
  *v37 += v16;
  *_this += *(_this + 1);
  if ( n2 < 2 )
  {
    ::__sub_414060_n0x800000 = n0x800000_1;
    ::__sub_414060_n0x7F800000 = n0x7F800000_1;
    return n2;
  }
  else
  {
    v38 = (unsigned __int8)__sub_414060_byte_445715[4 * n2];
    v40 = 0;
    v43 = 1;
    do
    {
      v17 = _this + 2 * (unsigned __int8)__sub_414060_byte_445716[4 * n2] + 2 * v43 + 2 * v40 + 8;
      v18 = *v17;
      v44 = v17[1];
      if ( n0x800000_1 <= 0x800000 )
      {
        LOBYTE(v19) = __sub_414060_byte_4456F0;
        v20 = (unsigned __int8 *)__sub_414060_Buffer_0;
        do
        {
          v21 = (unsigned __int8)((_BYTE)v19 << 7) | (n0x7F800000_1 << 8);
          v19 = *v20++;
          __sub_414060_Buffer_0 = (int)v20;
          n0x7F800000_1 = (v19 >> 1) | v21;
          n0x800000_1 <<= 8;
        }
        while ( n0x800000_1 <= 0x800000 );
        __sub_414060_byte_4456F0 = v19;
      }
      __sub_414060_n0x88 = v18 + v44;
      n0x7F800000_2 = n0x800000_1 / (v18 + v44) * v18;
      v23 = n0x7F800000_1 >= n0x7F800000_2;
      if ( n0x7F800000_1 >= n0x7F800000_2 )
      {
        n0x800000_1 -= n0x7F800000_2;
        n0x7F800000_1 -= n0x7F800000_2;
      }
      else
      {
        n0x800000_1 = n0x7F800000_2;
      }
      n0x4000 = v17[v23];
      if ( n0x4000 > 0x4000u )
      {
        *v17 -= *v17 >> 1;
        v17[1] -= v17[1] >> 1;
        n0x4000 = v17[v23];
      }
      v17[v23] = __sub_414060_n8_0 + n0x4000;
      v38 >>= 1;
      v43 *= 2;
      v25 = v23 + 2 * v40;
      v40 = v25;
    }
    while ( v38 );
    ::__sub_414060_n0x800000 = n0x800000_1;
    v26 = (unsigned __int8)__sub_414060_byte_445714[4 * n2];
    ::__sub_414060_n0x7F800000 = n0x7F800000_1;
    return v25 + v26;
  }
}

