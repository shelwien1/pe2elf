// sub_40AF40 @ 0x0040AF40 — __thiscall
// Extracted from BMF.c:8964-9192 by extract.py per incdec.md.

typedef int t_sub_40AF40_Buffer_0;
static t_sub_40AF40_Buffer_0& __sub_40AF40_Buffer_0 = *(t_sub_40AF40_Buffer_0*)0x00443378;
#define Buffer_0 __sub_40AF40_Buffer_0
typedef int t_sub_40AF40_Buffer_1;
static t_sub_40AF40_Buffer_1& __sub_40AF40_Buffer_1 = *(t_sub_40AF40_Buffer_1*)0x00443374;
#define Buffer_1 __sub_40AF40_Buffer_1
typedef int t_sub_40AF40_buf[0x10000];
static t_sub_40AF40_buf& __sub_40AF40_buf = *(t_sub_40AF40_buf*)0x00443380;
#define buf __sub_40AF40_buf
typedef int t_sub_40AF40_dword_443364;
static t_sub_40AF40_dword_443364& __sub_40AF40_dword_443364 = *(t_sub_40AF40_dword_443364*)0x00443364;
#define dword_443364 __sub_40AF40_dword_443364
typedef int t_sub_40AF40_n2;
static t_sub_40AF40_n2& __sub_40AF40_n2 = *(t_sub_40AF40_n2*)0x00443360;
#define n2 __sub_40AF40_n2
typedef int t_sub_40AF40_n256;
static t_sub_40AF40_n256& __sub_40AF40_n256 = *(t_sub_40AF40_n256*)0x0044336C;
#define n256 __sub_40AF40_n256
typedef int t_sub_40AF40_n8;
static t_sub_40AF40_n8& __sub_40AF40_n8 = *(t_sub_40AF40_n8*)0x00443368;
#define n8 __sub_40AF40_n8


PROBE_DECL(__sub_40AF40)
BMF_SSE __attribute__((thiscall)) _DWORD *__sub_40AF40(_DWORD *_this, int Src, int i, int n0x20000, int a5)
{
  PROBE_HIT(__sub_40AF40);
  _DWORD *this_1; // esi
  BOOL v6; // eax
  unsigned int v7; // ebx
  int v8; // eax
  int n256_3; // edi
  unsigned int v10; // edx
  int n8; // ebx
  int n256_5; // eax
  bool v13; // sf
  int n256_1; // ecx
  unsigned int v15; // ecx
  unsigned int v16; // esi
  int v17; // edx
  _DWORD *v18; // ebx
  int v19; // esi
  unsigned int k_3; // ebx
  _DWORD *v21; // edi
  unsigned int k_1; // ecx
  unsigned int k_2; // eax
  unsigned int v24; // edi
  unsigned int k; // ebx
  __m128i v26; // xmm0
  __m128i v27; // xmm0
  __m128i v28; // xmm0
  int v29; // edx
  int v30; // edi
  unsigned int j; // edx
  unsigned int v32; // ebx
  int v33; // eax
  int v34; // edi
  int n256; // eax
  unsigned int k_4; // [esp+0h] [ebp-2Ch]
  unsigned int v38; // [esp+0h] [ebp-2Ch]
  int n256_2; // [esp+4h] [ebp-28h]
  unsigned int v40; // [esp+4h] [ebp-28h]
  unsigned int v41; // [esp+8h] [ebp-24h]
  _DWORD *v42; // [esp+8h] [ebp-24h]
  signed int v43; // [esp+8h] [ebp-24h]
  unsigned int v45; // [esp+14h] [ebp-18h]
  signed int v46; // [esp+14h] [ebp-18h]
  int n256_4; // [esp+18h] [ebp-14h]
  char v48; // [esp+1Ch] [ebp-10h]

  this_1 = _this;
  *_this = Src + i;
  *(_this + 4) = 0;
  *(_this + 1) = Src + 2 * i + 1;
  if ( dword_443364 )
  {
    *(_this + 2) = -i;
    *(_this + 3) = -2 * i;
    v6 = n2 == 2;
    v7 = 2 * v6 + 8;
    v8 = 2 * v6 + 6;
    if ( n0x20000 < 0x20000 )
      v7 = v8;
    if ( a5 )
    {
      v46 = v7 - 1;
      v40 = (n0x20000 - i + v7 - 1) / v7;
      v30 = v40;
      v43 = 0;
      for ( j = 0; j < 0x80; ++j )
      {
        v32 = 2 * j;
        v33 = 16 * v43;
        *(_this + 2 * j + 5) = 16 * v43;
        v34 = v30 - *(_DWORD *)&buf[8 * j];
        if ( v34 <= 0 && v43 < v46 )
        {
          v34 += v40;
          ++v43;
          if ( ::n8 < 8 )
          {
            *(_DWORD *)Buffer_1 = ::n256 | (2 * (v32 << (31 - ::n8)));
            Buffer_1 = Buffer_0;
            Buffer_0 += 4;
            n256 = v32 >> ::n8;
            ::n8 += 24;
            ::n256 = n256;
          }
          else
          {
            ::n256 |= v32 << -(char)::n8;
            ::n8 -= 8;
          }
          v33 = 16 * v43;
        }
        *(_this + 2 * j + 6) = v33;
        v30 = v34 - *(_DWORD *)&buf[8 * j + 4];
        if ( v30 <= 0 && v43 < v46 )
        {
          v30 += v40;
          ++v43;
          if ( ::n8 < 8 )
          {
            *(_DWORD *)Buffer_1 = ::n256 | (2 * ((2 * j + 1) << (31 - ::n8)));
            Buffer_1 = Buffer_0;
            ::n256 = (2 * j + 1) >> ::n8;
            Buffer_0 += 4;
            ::n8 += 24;
          }
          else
          {
            ::n256 |= (2 * j + 1) << -(char)::n8;
            ::n8 -= 8;
          }
        }
      }
      return this_1;
    }
    n256_3 = 0;
    v45 = v7 - 1;
    v10 = 0;
    do
    {
      n8 = ::n8;
      n256_4 = n256_3;
      n256_5 = n256_3;
      v13 = ::n8 - 8 < 0;
      v48 = ::n8 - 8;
      ::n8 -= 8;
      if ( v13 )
      {
        v38 = *(_DWORD *)Buffer_0;
        Buffer_0 += 4;
        ::n8 = n8 + 24;
        n256_1 = ::n256 | (unsigned __int8)(v38 << n8);
        ::n256 = v38 >> -v48;
      }
      else
      {
        n256_1 = (unsigned __int8)::n256;
        ::n256 = (unsigned int)::n256 >> 8;
      }
      if ( n256_3 <= n256_1 )
      {
        if ( (n256_1 - n256_3 + 1) / 2 )
        {
          v41 = v10;
          n256_2 = n256_1;
          v15 = (n256_1 - n256_3 + 1) / 2;
          v16 = 0;
          v17 = 16 * v10;
          v18 = _this + n256_3;
          do
          {
            v18[2 * v16 + 5] = v17;
            v18[2 * v16 + 6] = v17;
            n256_3 = n256_5 + 2 * v16++ + 2;
          }
          while ( v16 < v15 );
          v10 = v41;
          n256_1 = n256_2;
          v19 = 2 * v16 + 1;
        }
        else
        {
          v19 = 1;
        }
        if ( n256_1 - n256_4 + 1 > (unsigned int)(v19 - 1) )
        {
          n256_3 = v19 + n256_5;
          *(_this + v19 + n256_5 + 4) = 16 * v10;
        }
      }
      ++v10;
    }
    while ( v10 < v45 );
    this_1 = _this;
    if ( n256_3 >= 256 )
      return this_1;
    k_3 = 256 - n256_3;
    v21 = _this + n256_3;
    k_1 = ((_BYTE)v21 + 4) & 0xF;
    v42 = v21;
    if ( (((_BYTE)v21 + 4) & 0xF) != 0 )
    {
      if ( (((_BYTE)v21 + 4) & 3) != 0 )
        goto LABEL_38;
      k_1 = (16 - k_1) >> 2;
    }
    if ( (int)k_3 >= (int)(k_1 + 4) )
    {
      k_2 = k_3 - (((_BYTE)k_3 - (_BYTE)k_1) & 3);
      v24 = 16 * v10;
      if ( k_1 )
      {
        k_4 = k_3;
        for ( k = 0; k < k_1; ++k )
          v42[k + 5] = v24;
        k_3 = k_4;
        this_1 = _this;
      }
      v26 = _mm_cvtsi32_si128(v24);
      v27 = _mm_unpacklo_epi32(v26, v26);
      v28 = _mm_unpacklo_epi64(v27, v27);
      do
      {
        *(__m128i *)&v42[k_1 + 5] = v28;
        k_1 += 4;
      }
      while ( k_1 < k_2 );
      goto LABEL_27;
    }
LABEL_38:
    k_2 = 0;
LABEL_27:
    if ( k_2 < k_3 )
    {
      v29 = 16 * v10;
      do
        v42[k_2++ + 5] = v29;
      while ( k_2 < k_3 );
    }
    return this_1;
  }
  *(_this + 2) = -1;
  *(_this + 3) = -i;
  return _this;
}

#undef Buffer_0
#undef Buffer_1
#undef buf
#undef dword_443364
#undef n2
#undef n256
#undef n8
