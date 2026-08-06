// sub_414060 @ 0x00414060 — __thiscall
// Extracted from BMF.c:18362-18574 by extract.py per incdec.md.

#ifndef __PE_DECL___Buffer_0
#define __PE_DECL___Buffer_0
typedef int t_Buffer_0;
static t_Buffer_0& __Buffer_0 = *(t_Buffer_0*)0x00443378;
#endif
#define Buffer_0 __Buffer_0
#ifndef __PE_DECL___byte_4456F0
#define __PE_DECL___byte_4456F0
typedef char t_byte_4456F0;
static t_byte_4456F0& __byte_4456F0 = *(t_byte_4456F0*)0x004456F0;
#endif
#define byte_4456F0 __byte_4456F0
#ifndef __PE_DECL___byte_445714
#define __PE_DECL___byte_445714
typedef unsigned char t_byte_445714[0x10000];
static t_byte_445714& __byte_445714 = *(t_byte_445714*)0x00445714;
#endif
#define byte_445714 __byte_445714
#ifndef __PE_DECL___byte_445715
#define __PE_DECL___byte_445715
typedef unsigned char t_byte_445715[0x10000];
static t_byte_445715& __byte_445715 = *(t_byte_445715*)0x00445715;
#endif
#define byte_445715 __byte_445715
#ifndef __PE_DECL___byte_445716
#define __PE_DECL___byte_445716
typedef unsigned char t_byte_445716[0x10000];
static t_byte_445716& __byte_445716 = *(t_byte_445716*)0x00445716;
#endif
#define byte_445716 __byte_445716
#ifndef __PE_DECL___dword_4456E8
#define __PE_DECL___dword_4456E8
typedef int t_dword_4456E8;
static t_dword_4456E8& __dword_4456E8 = *(t_dword_4456E8*)0x004456E8;
#endif
#define dword_4456E8 __dword_4456E8
#ifndef __PE_DECL___dword_4456F4
#define __PE_DECL___dword_4456F4
typedef int t_dword_4456F4;
static t_dword_4456F4& __dword_4456F4 = *(t_dword_4456F4*)0x004456F4;
#endif
#define dword_4456F4 __dword_4456F4
#ifndef __PE_DECL___n0x2000
#define __PE_DECL___n0x2000
typedef int t_n0x2000;
static t_n0x2000& __n0x2000 = *(t_n0x2000*)0x004456FC;
#endif
#define n0x2000 __n0x2000
#ifndef __PE_DECL___n0x2000_0
#define __PE_DECL___n0x2000_0
typedef int t_n0x2000_0;
static t_n0x2000_0& __n0x2000_0 = *(t_n0x2000_0*)0x004456F8;
#endif
#define n0x2000_0 __n0x2000_0
#ifndef __PE_DECL___n0x7F800000
#define __PE_DECL___n0x7F800000
typedef int t_n0x7F800000;
static t_n0x7F800000& __n0x7F800000 = *(t_n0x7F800000*)0x004456E4;
#endif
#define n0x7F800000 __n0x7F800000
#ifndef __PE_DECL___n0x800000
#define __PE_DECL___n0x800000
typedef int t_n0x800000;
static t_n0x800000& __n0x800000 = *(t_n0x800000*)0x004456E0;
#endif
#define n0x800000 __n0x800000
#ifndef __PE_DECL___n0x88
#define __PE_DECL___n0x88
typedef int t_n0x88;
static t_n0x88& __n0x88 = *(t_n0x88*)0x00445704;
#endif
#define n0x88 __n0x88
#ifndef __PE_DECL___n8_0
#define __PE_DECL___n8_0
typedef int t_n8_0;
static t_n8_0& __n8_0 = *(t_n8_0*)0x00445710;
#endif
#define n8_0 __n8_0
#ifndef __PE_DECL___n8_1
#define __PE_DECL___n8_1
typedef int t_n8_1;
static t_n8_1& __n8_1 = *(t_n8_1*)0x0044570C;
#endif
#define n8_1 __n8_1


PROBE_DECL(__sub_414060)
__attribute__((thiscall)) int __sub_414060(unsigned __int16 *_this)
{
  PROBE_HIT(__sub_414060);
  unsigned int n0x800000; // ebx
  unsigned int n0x7F800000; // ebp
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

  n0x800000 = ::n0x800000;
  n0x7F800000 = ::n0x7F800000;
  v39 = *_this;
  n0x2000 = v39;
  if ( (unsigned int)::n0x800000 <= 0x800000 )
  {
    LOBYTE(v3) = byte_4456F0;
    v4 = (unsigned __int8 *)Buffer_0;
    do
    {
      v5 = (unsigned __int8)((_BYTE)v3 << 7) | (n0x7F800000 << 8);
      v3 = *v4++;
      Buffer_0 = (int)v4;
      n0x7F800000 = (v3 >> 1) | v5;
      n0x800000 <<= 8;
    }
    while ( n0x800000 <= 0x800000 );
    byte_4456F0 = v3;
  }
  n0x2000_0 = 0;
  n2 = 0;
  v6 = n0x800000 / v39;
  v7 = n0x7F800000 / (n0x800000 / v39);
  dword_4456E8 = n0x800000 / v39;
  if ( v7 >= v39 )
    v7 = v39 - 1;
  v8 = _this + 2;
  v9 = *(_this + 2);
  n0x2000_0 = v9;
  if ( v9 <= v7 )
  {
    n2_1 = 0;
    do
    {
      ++v8;
      ++n2_1;
      v9 += *v8;
      n0x2000_0 = v9;
    }
    while ( v9 <= v7 );
    n2 = n2_1;
    v6 = n0x800000 / v39;
  }
  v37 = v8;
  v11 = v9 - *v8;
  v12 = v11 * v6;
  dword_4456F4 = v11;
  n0x7F800000_1 = n0x7F800000 - v11 * v6;
  n0x800000_2 = (v9 - v11) * v6;
  n0x800000_1 = n0x800000 - v12;
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
    if ( v36 <= 4 * n8_1 )
      v16 = v36 - 4 * (v36 > n8_1);
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
    ::n0x800000 = n0x800000_1;
    ::n0x7F800000 = n0x7F800000_1;
    return n2;
  }
  else
  {
    v38 = (unsigned __int8)byte_445715[4 * n2];
    v40 = 0;
    v43 = 1;
    do
    {
      v17 = _this + 2 * (unsigned __int8)byte_445716[4 * n2] + 2 * v43 + 2 * v40 + 8;
      v18 = *v17;
      v44 = v17[1];
      if ( n0x800000_1 <= 0x800000 )
      {
        LOBYTE(v19) = byte_4456F0;
        v20 = (unsigned __int8 *)Buffer_0;
        do
        {
          v21 = (unsigned __int8)((_BYTE)v19 << 7) | (n0x7F800000_1 << 8);
          v19 = *v20++;
          Buffer_0 = (int)v20;
          n0x7F800000_1 = (v19 >> 1) | v21;
          n0x800000_1 <<= 8;
        }
        while ( n0x800000_1 <= 0x800000 );
        byte_4456F0 = v19;
      }
      n0x88 = v18 + v44;
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
      v17[v23] = n8_0 + n0x4000;
      v38 >>= 1;
      v43 *= 2;
      v25 = v23 + 2 * v40;
      v40 = v25;
    }
    while ( v38 );
    ::n0x800000 = n0x800000_1;
    v26 = (unsigned __int8)byte_445714[4 * n2];
    ::n0x7F800000 = n0x7F800000_1;
    return v25 + v26;
  }
}

#undef Buffer_0
#undef byte_4456F0
#undef byte_445714
#undef byte_445715
#undef byte_445716
#undef dword_4456E8
#undef dword_4456F4
#undef n0x2000
#undef n0x2000_0
#undef n0x7F800000
#undef n0x800000
#undef n0x88
#undef n8_0
#undef n8_1
