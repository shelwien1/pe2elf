// sub_410310 @ 0x00410310 — __cdecl
// Extracted from BMF.c:14186-14447 by extract.py per incdec.md.

typedef int t_sub_410310_n2;
static t_sub_410310_n2& __sub_410310_n2 = *(t_sub_410310_n2*)0x00443360;
#define n2 __sub_410310_n2
typedef int t_sub_410310_n256_0;
static t_sub_410310_n256_0& __sub_410310_n256_0 = *(t_sub_410310_n256_0*)0x00443398;
#define n256_0 __sub_410310_n256_0
typedef __int128 t_sub_410310_xmmword_439620;
static t_sub_410310_xmmword_439620& __sub_410310_xmmword_439620 = *(t_sub_410310_xmmword_439620*)0x00439620;
#define xmmword_439620 __sub_410310_xmmword_439620
typedef __int128 t_sub_410310_xmmword_439630;
static t_sub_410310_xmmword_439630& __sub_410310_xmmword_439630 = *(t_sub_410310_xmmword_439630*)0x00439630;
#define xmmword_439630 __sub_410310_xmmword_439630
typedef __int128 t_sub_410310_xmmword_439640;
static t_sub_410310_xmmword_439640& __sub_410310_xmmword_439640 = *(t_sub_410310_xmmword_439640*)0x00439640;
#define xmmword_439640 __sub_410310_xmmword_439640
typedef __int128 t_sub_410310_xmmword_439650;
static t_sub_410310_xmmword_439650& __sub_410310_xmmword_439650 = *(t_sub_410310_xmmword_439650*)0x00439650;
#define xmmword_439650 __sub_410310_xmmword_439650
typedef __int128 t_sub_410310_xmmword_439660;
static t_sub_410310_xmmword_439660& __sub_410310_xmmword_439660 = *(t_sub_410310_xmmword_439660*)0x00439660;
#define xmmword_439660 __sub_410310_xmmword_439660


PROBE_DECL(__sub_410310)
BMF_SSE _BYTE *__sub_410310(int Src, int i, int a3)
{
  PROBE_HIT(__sub_410310);
  int Src_1; // edi
  int n256; // esi
  _BYTE *result; // eax
  int n128_1; // ecx
  __m128i si128; // xmm3
  __m128i v8; // xmm2
  __m128i v9; // xmm1
  __m128i v10; // xmm0
  unsigned int n0x70; // edx
  __m128i v12; // xmm4
  __m128i v13; // xmm5
  unsigned int j; // esi
  int n128; // ebx
  int v16; // edx
  char v17; // cl
  char v18; // al
  char v19; // cl
  __m128i v20; // xmm1
  __m128i v21; // xmm0
  unsigned int k; // edx
  __m128i v23; // xmm0
  __m128i v24; // xmm0
  __m128i v25; // xmm0
  __m128i v26; // xmm0
  __m128i v27; // xmm0
  __m128i v28; // xmm0
  __m128i v29; // xmm0
  int n256_1; // edx
  int v31; // ebx
  int n128_2; // edi
  char v33; // cl
  char v34; // dl
  int i_1; // edx
  unsigned int v36; // ebx
  unsigned int m_1; // ecx
  unsigned int m; // esi
  char v39; // dl
  char v40; // al
  int v41; // ecx
  int v42; // esi
  _BYTE *v43; // edi
  unsigned int v44; // ecx
  int v45; // ebx
  int v46; // edx
  int v47; // esi
  int v48; // [esp+0h] [ebp-120h]
  int n128_3; // [esp+4h] [ebp-11Ch]
  unsigned int v50; // [esp+4h] [ebp-11Ch]
  _BYTE v52[255]; // [esp+10h] [ebp-110h]
  char v53; // [esp+10Fh] [ebp-11h]

  Src_1 = Src;
  n256 = n256_0;
  result = (_BYTE *)(Src + 1);
  n128_1 = 2 * n256_0 + 1;
  if ( n2 )
  {
    si128 = _mm_load_si128((const __m128i *)&xmmword_439640);
    v8 = _mm_load_si128((const __m128i *)&xmmword_439620);
    v9 = _mm_load_si128((const __m128i *)&xmmword_439650);
    v10 = _mm_load_si128((const __m128i *)&xmmword_439660);
    n0x70 = 0;
    v52[0] = 0;
    v53 = 0x80;
    do
    {
      v12 = v9;
      v13 = v9;
      v9 = _mm_add_epi8(v9, si128);
      *(__m128i *)&v52[2 * n0x70 + 1] = _mm_unpacklo_epi8(v12, v10);
      *(__m128i *)&v52[2 * n0x70 + 17] = _mm_unpackhi_epi8(v13, v10);
      v10 = _mm_add_epi8(v10, v8);
      n0x70 += 16;
    }
    while ( n0x70 < 0x70 );
    for ( j = 0; j < 7; ++j )
    {
      v52[4 * j + 225] = -2 * j - 113;
      v52[4 * j + 227] = -2 * j - 114;
      v52[4 * j + 226] = 2 * j + 113;
      v52[4 * j + 228] = 2 * j + 114;
    }
    Src_1 = Src;
    v52[253] = -127;
    v52[254] = 127;
    if ( n256_0 )
    {
      n128 = n128_1;
      if ( n128_1 < 128 )
      {
        n128_3 = n128_1;
        v16 = 1;
        do
        {
          v17 = v52[2 * v16];
          v52[2 * v16] = v52[2 * n128];
          v18 = v52[2 * n128 - 1];
          v52[2 * n128] = v17;
          v19 = v52[2 * v16 - 1];
          v52[2 * v16 - 1] = v18;
          v52[2 * n128 - 1] = v19;
          n128 += n128_3;
          ++v16;
        }
        while ( n128 < 128 );
        result = (_BYTE *)(Src + 1);
        Src_1 = Src;
      }
    }
  }
  else
  {
    v20 = _mm_load_si128((const __m128i *)&xmmword_439620);
    v21 = _mm_load_si128((const __m128i *)&xmmword_439630);
    for ( k = 0; k < 0x100; k += 128 )
    {
      *(__m128i *)&v52[k] = v21;
      v23 = _mm_add_epi8(v21, v20);
      *(__m128i *)&v52[k + 16] = v23;
      v24 = _mm_add_epi8(v23, v20);
      *(__m128i *)&v52[k + 32] = v24;
      v25 = _mm_add_epi8(v24, v20);
      *(__m128i *)&v52[k + 48] = v25;
      v26 = _mm_add_epi8(v25, v20);
      *(__m128i *)&v52[k + 64] = v26;
      v27 = _mm_add_epi8(v26, v20);
      *(__m128i *)&v52[k + 80] = v27;
      v28 = _mm_add_epi8(v27, v20);
      *(__m128i *)&v52[k + 96] = v28;
      v29 = _mm_add_epi8(v28, v20);
      *(__m128i *)&v52[k + 112] = v29;
      v21 = _mm_add_epi8(v29, v20);
    }
    n256_1 = n256;
    v31 = 0;
    if ( n256 < 256 )
    {
      n128_2 = n128_1;
      do
      {
        v33 = v52[v31];
        v52[v31++] = v52[n256];
        v52[n256] = v33;
        n256 += n128_2;
      }
      while ( n256 < 256 );
      Src_1 = Src;
      n256_1 = n256_0;
    }
    if ( n256 - n256_1 < 256 )
    {
      v34 = v52[v31];
      v52[v31] = v53;
      v53 = v34;
    }
  }
  i_1 = i;
  if ( i == 1 )
  {
    v42 = a3 - 1;
    if ( a3 == 1 )
      return result;
    v36 = 0;
    goto LABEL_29;
  }
  v36 = i - 1;
  m_1 = (i - 1) / 2;
  if ( m_1 )
  {
    for ( m = 0; m < m_1; ++m )
    {
      v39 = *(_BYTE *)(Src_1 + 2 * m) + v52[*(unsigned __int8 *)(Src_1 + 2 * m + 1)];
      v40 = v52[*(unsigned __int8 *)(Src_1 + 2 * m + 2)];
      *(_BYTE *)(Src_1 + 2 * m + 1) = v39;
      *(_BYTE *)(Src_1 + 2 * m + 2) = v39 + v40;
      result = (_BYTE *)(Src_1 + 2 * m + 3);
    }
    i_1 = i;
    v41 = 2 * m + 1;
  }
  else
  {
    v41 = 1;
  }
  if ( v36 > v41 - 1 )
  {
    *(_BYTE *)(v41 + Src_1) = *(_BYTE *)(v41 + Src_1 - 1) + v52[*(unsigned __int8 *)(v41 + Src_1)];
    result = (_BYTE *)(Src_1 + v41 + 1);
    v42 = a3 - 1;
    if ( a3 == 1 )
      return result;
    goto LABEL_29;
  }
  v42 = a3 - 1;
  if ( a3 != 1 )
  {
LABEL_29:
    v50 = v36;
    v43 = &result[-i_1];
    do
    {
      while ( 1 )
      {
        ++v43;
        *result = v52[(unsigned __int8)*result] + result[-i_1];
        v44 = v50;
        ++result;
        if ( i_1 != 1 )
          break;
        if ( !--v42 )
          return result;
      }
      v48 = v42;
      do
      {
        v45 = (unsigned __int8)*(result - 1);
        v46 = (unsigned __int8)*v43;
        v47 = (unsigned __int8)result[-i - 1];
        if ( v45 < v46 )
        {
          if ( v47 < v45 )
          {
            LOBYTE(v45) = *v43;
            goto LABEL_41;
          }
          if ( v47 <= v46 )
LABEL_40:
            LOBYTE(v45) = v46 + v45 - v47;
        }
        else
        {
          if ( v47 > v45 )
          {
            LOBYTE(v45) = *v43;
            goto LABEL_41;
          }
          if ( v47 >= v46 )
            goto LABEL_40;
        }
LABEL_41:
        *result = v45 + v52[(unsigned __int8)*result];
        ++v43;
        ++result;
        --v44;
      }
      while ( v44 );
      i_1 = i;
      v42 = v48 - 1;
    }
    while ( v48 != 1 );
  }
  return result;
}

#undef n2
#undef n256_0
#undef xmmword_439620
#undef xmmword_439630
#undef xmmword_439640
#undef xmmword_439650
#undef xmmword_439660
