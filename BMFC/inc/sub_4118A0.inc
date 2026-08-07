// sub_4118A0 @ 0x004118A0 — __cdecl
// Extracted from BMF.cpp:15656-15985 by extract.py per incdec.md.

typedef int t_sub_4118A0_n2;
static t_sub_4118A0_n2& __sub_4118A0_n2 = *(t_sub_4118A0_n2*)(blob1 + 0x00443360 - BMF_BLOB_BASE);
typedef int t_sub_4118A0_n256_0[0x10000];
static t_sub_4118A0_n256_0& __sub_4118A0_n256_0 = *(t_sub_4118A0_n256_0*)(blob1 + 0x00443398 - BMF_BLOB_BASE);
typedef __int128 t_sub_4118A0_xmmword_4397B0;
static t_sub_4118A0_xmmword_4397B0& __sub_4118A0_xmmword_4397B0 = *(t_sub_4118A0_xmmword_4397B0*)(blob1 + 0x004397B0 - BMF_BLOB_BASE);


PROBE_DECL(__sub_4118A0)
BMF_REALIGN BMF_SSE unsigned int __sub_4118A0(_BYTE *a1, char *a2)
{
  PROBE_HIT(__sub_4118A0);
  int n128_1; // ebx
  unsigned int n0x100_1; // ecx
  unsigned int n0x100_2; // eax
  __m128i si128; // xmm2
  unsigned int n0x100; // eax
  __m128i v7; // xmm1
  int v8; // esi
  int v9; // edx
  char *v10; // edi
  int v11; // eax
  char *v12; // esi
  char v13; // cl
  char *v14; // edi
  char *v15; // esi
  char v16; // cl
  char v17; // dl
  char *v18; // ecx
  char *v19; // edx
  unsigned int j; // eax
  unsigned int k; // ecx
  unsigned int i; // eax
  int n128; // edi
  int v24; // ecx
  char v25; // dl
  char v26; // al
  char v27; // dl
  int n128_6; // edx
  int v29; // ecx
  int v30; // esi
  int n128_5; // edi
  unsigned int v32; // eax
  int v33; // ebx
  int n128_3; // edx
  int n128_4; // edi
  int v36; // ecx
  int n128_10; // ecx
  int v38; // edx
  unsigned int m; // eax
  int n128_8; // edi
  int n128_9; // ecx
  char v42; // bl
  unsigned int n0x80; // eax
  char *v44; // [esp+0h] [ebp-40h]
  int v45; // [esp+0h] [ebp-40h]
  int n128_11; // [esp+0h] [ebp-40h]
  int v47; // [esp+4h] [ebp-3Ch]
  char v48; // [esp+4h] [ebp-3Ch]
  unsigned int v49; // [esp+8h] [ebp-38h]
  _BYTE *v50; // [esp+Ch] [ebp-34h]
  _BYTE *v51; // [esp+10h] [ebp-30h]
  unsigned int v52; // [esp+14h] [ebp-2Ch]
  char v53; // [esp+18h] [ebp-28h]
  int n128_2; // [esp+2Ch] [ebp-14h]
  int n128_7; // [esp+2Ch] [ebp-14h]

  n128_1 = 2 * __sub_4118A0_n256_0[0] + 1;
  if ( !__sub_4118A0_n2 )
  {
    n0x100_1 = (unsigned __int8)a2 & 0xF;
    if ( ((unsigned __int8)a2 & 0xF) != 0 )
    {
      n0x100_1 = 16 - n0x100_1;
      n0x100_2 = 0;
      do
      {
        a2[n0x100_2] = n0x100_2;
        ++n0x100_2;
      }
      while ( n0x100_2 < n0x100_1 );
    }
    si128 = _mm_load_si128((const __m128i *)&__sub_4118A0_xmmword_4397B0);
    n0x100 = 256 - (-n0x100_1 & 0xF);
    v7 = _mm_unpacklo_epi64(
           _mm_unpacklo_epi32(
             _mm_unpacklo_epi16(
               _mm_unpacklo_epi8(_mm_cvtsi32_si128(n0x100_1), _mm_cvtsi32_si128(n0x100_1 + 1)),
               _mm_unpacklo_epi8(_mm_cvtsi32_si128(n0x100_1 + 2), _mm_cvtsi32_si128(n0x100_1 + 3))),
             _mm_unpacklo_epi16(
               _mm_unpacklo_epi8(_mm_cvtsi32_si128(n0x100_1 + 4), _mm_cvtsi32_si128(n0x100_1 + 5)),
               _mm_unpacklo_epi8(_mm_cvtsi32_si128(n0x100_1 + 6), _mm_cvtsi32_si128(n0x100_1 + 7)))),
           _mm_unpacklo_epi32(
             _mm_unpacklo_epi16(
               _mm_unpacklo_epi8(_mm_cvtsi32_si128(n0x100_1 + 8), _mm_cvtsi32_si128(n0x100_1 + 9)),
               _mm_unpacklo_epi8(_mm_cvtsi32_si128(n0x100_1 + 10), _mm_cvtsi32_si128(n0x100_1 + 11))),
             _mm_unpacklo_epi16(
               _mm_unpacklo_epi8(_mm_cvtsi32_si128(n0x100_1 + 12), _mm_cvtsi32_si128(n0x100_1 + 13)),
               _mm_unpacklo_epi8(_mm_cvtsi32_si128(n0x100_1 + 14), _mm_cvtsi32_si128(n0x100_1 + 15)))));
    do
    {
      *(__m128i *)&a2[n0x100_1] = v7;
      v7 = _mm_add_epi8(v7, si128);
      n0x100_1 += 16;
    }
    while ( n0x100_1 < n0x100 );
    for ( ; n0x100 < 0x100; ++n0x100 )
      a2[n0x100] = n0x100;
    v8 = __sub_4118A0_n256_0[0];
    v9 = __sub_4118A0_n256_0[0];
    if ( __sub_4118A0_n256_0[0] >= 256 )
    {
      v11 = 0;
LABEL_29:
      if ( v9 - v8 < 256 )
      {
        v17 = a2[v11];
        a2[v11] = a2[255];
        a2[255] = v17;
      }
      goto LABEL_47;
    }
    v44 = &a2[__sub_4118A0_n256_0[0]];
    if ( n128_1 <= 0 )
    {
      v47 = (n128_1 - (__int64)__sub_4118A0_n256_0[0] + 255) / n128_1;
      goto LABEL_26;
    }
    v47 = (n128_1 - (__int64)__sub_4118A0_n256_0[0] + 255) / n128_1;
    if ( a2 >= v44 || __sub_4118A0_n256_0[0] < (unsigned int)v47 )
    {
      if ( n128_1 > 1 || a2 <= v44 || -__sub_4118A0_n256_0[0] < (unsigned int)(v47 * n128_1) )
        goto LABEL_26;
    }
    else if ( n128_1 > 1 || a2 <= v44 )
    {
LABEL_20:
      if ( a2 < v44 && __sub_4118A0_n256_0[0] >= (unsigned int)v47 )
        goto LABEL_22;
LABEL_26:
      v14 = a2;
      v45 = __sub_4118A0_n256_0[0];
      v11 = 0;
      v15 = &a2[__sub_4118A0_n256_0[0]];
      do
      {
        v16 = *v14;
        *v14 = *v15;
        *v15 = v16;
        v15 += n128_1;
        ++v14;
        ++v11;
      }
      while ( v11 < v47 );
      goto LABEL_28;
    }
    if ( -__sub_4118A0_n256_0[0] >= (unsigned int)(v47 * n128_1) )
    {
LABEL_22:
      v10 = a2;
      v45 = __sub_4118A0_n256_0[0];
      v11 = 0;
      v12 = &a2[__sub_4118A0_n256_0[0]];
      do
      {
        v13 = *v10;
        *v10 = *v12;
        *v12 = v13;
        v12 += n128_1;
        ++v10;
        ++v11;
      }
      while ( v11 < v47 );
LABEL_28:
      v9 = v45 + v11 * n128_1;
      v8 = __sub_4118A0_n256_0[0];
      goto LABEL_29;
    }
    goto LABEL_20;
  }
  *a2 = 0;
  v18 = a2 + 2;
  v19 = a2 + 1;
  a2[255] = 0x80;
  if ( (a2 + 1 <= a2 + 2 || (unsigned int)(v19 - v18) < 0xFE) && (v18 <= v19 || (unsigned int)(v18 - v19) < 0xFE) )
  {
    for ( i = 0; i < 0x3F; ++i )
    {
      a2[4 * i + 2] = 2 * i + 1;
      a2[4 * i + 1] = -2 * i - 1;
      a2[4 * i + 4] = 2 * i + 2;
      a2[4 * i + 3] = -2 * i - 2;
    }
    a2[254] = 127;
    a2[253] = -127;
  }
  else
  {
    for ( j = 0; j < 0x3F; ++j )
    {
      a2[4 * j + 2] = 2 * j + 1;
      a2[4 * j + 4] = 2 * j + 2;
    }
    a2[254] = 127;
    for ( k = 0; k < 0x3F; ++k )
    {
      a2[4 * k + 1] = -2 * k - 1;
      a2[4 * k + 3] = -2 * k - 2;
    }
    a2[253] = -127;
  }
  if ( __sub_4118A0_n256_0[0] )
  {
    n128 = n128_1;
    if ( n128_1 < 128 )
    {
      v24 = 1;
      do
      {
        v25 = a2[2 * v24];
        a2[2 * v24] = a2[2 * n128];
        v26 = a2[2 * n128 - 1];
        a2[2 * n128] = v25;
        v27 = a2[2 * v24 - 1];
        a2[2 * v24 - 1] = v26;
        a2[2 * n128 - 1] = v27;
        ++v24;
        n128 += n128_1;
      }
      while ( n128 < 128 );
    }
  }
LABEL_47:
  if ( __sub_4118A0_n2 )
  {
    *a1 = 0;
    n128_6 = 1;
    a1[128] = -1;
    if ( __sub_4118A0_n256_0[0] <= 0 )
      goto LABEL_52;
    v29 = -1;
    do
    {
      a1[v29 + 256] = 0;
      a1[n128_6] = 0;
      --v29;
      ++n128_6;
    }
    while ( n128_6 <= __sub_4118A0_n256_0[0] );
    if ( n128_6 < 128 )
    {
LABEL_52:
      v49 = 128 - n128_6;
      v52 = (128 - n128_6) / 2;
      v30 = 0;
      n128_5 = 1;
      if ( v52 )
      {
        n128_11 = n128_6;
        v32 = 0;
        n128_2 = n128_1;
        v33 = 0;
        v50 = &a1[n128_6];
        v51 = &a1[-n128_6];
        do
        {
          n128_3 = n128_2;
          n128_4 = n128_5 - 1;
          if ( n128_4 )
            n128_3 = n128_4;
          else
            ++v30;
          v48 = 2 * v30;
          v50[2 * v32] = 2 * v30;
          v53 = 2 * v30 - 1;
          n128_5 = n128_3 - 1;
          v51[v33 + 256] = v53;
          if ( n128_3 == 1 )
          {
            n128_5 = n128_2;
            v48 = 2 * ++v30;
            v53 = 2 * v30 - 1;
          }
          v50[2 * v32++ + 1] = v48;
          v51[v33 + 255] = v53;
          v33 -= 2;
        }
        while ( v32 < v52 );
        n128_6 = n128_11;
        v36 = 2 * v32 + 1;
      }
      else
      {
        v36 = 1;
      }
      if ( v36 - 1 < v49 )
      {
        if ( n128_5 == 1 )
          LOBYTE(v30) = v30 + 1;
        a1[n128_6 - 1 + v36] = 2 * v30;
        a1[-n128_6 - v36 + 257] = 2 * v30 - 1;
      }
    }
  }
  else
  {
    n128_7 = n128_1;
    n128_10 = n128_1 + 1;
    v38 = 0;
    for ( m = 0; m < 0x80; ++m )
    {
      n128_8 = n128_7;
      n128_9 = n128_10 - 1;
      if ( n128_9 )
        n128_8 = n128_9;
      else
        ++v38;
      v42 = v38;
      a1[2 * m] = v38;
      n128_10 = n128_8 - 1;
      if ( n128_8 == 1 )
      {
        n128_10 = n128_7;
        v42 = ++v38;
      }
      a1[2 * m + 1] = v42;
    }
  }
  for ( n0x80 = 0; n0x80 < 0x80; ++n0x80 )
  {
    a1[(unsigned __int8)a2[2 * n0x80] + 256] = 2 * n0x80;
    a1[(unsigned __int8)a2[2 * n0x80 + 1] + 256] = 2 * n0x80 + 1;
  }
  return n0x80;
}

