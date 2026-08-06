// sub_410650 @ 0x00410650 — __cdecl
// Extracted from BMF.c:14450-14620 by extract.py per incdec.md.

typedef int t_sub_410650_n2;
static t_sub_410650_n2& __sub_410650_n2 = *(t_sub_410650_n2*)0x00443360;
#define n2 __sub_410650_n2
typedef int t_sub_410650_n256_0;
static t_sub_410650_n256_0& __sub_410650_n256_0 = *(t_sub_410650_n256_0*)0x00443398;
#define n256_0 __sub_410650_n256_0
typedef __int128 t_sub_410650_xmmword_439670;
static t_sub_410650_xmmword_439670& __sub_410650_xmmword_439670 = *(t_sub_410650_xmmword_439670*)0x00439670;
#define xmmword_439670 __sub_410650_xmmword_439670
typedef __int128 t_sub_410650_xmmword_439680;
static t_sub_410650_xmmword_439680& __sub_410650_xmmword_439680 = *(t_sub_410650_xmmword_439680*)0x00439680;
#define xmmword_439680 __sub_410650_xmmword_439680
typedef __int128 t_sub_410650_xmmword_439690;
static t_sub_410650_xmmword_439690& __sub_410650_xmmword_439690 = *(t_sub_410650_xmmword_439690*)0x00439690;
#define xmmword_439690 __sub_410650_xmmword_439690
typedef __int128 t_sub_410650_xmmword_4396A0;
static t_sub_410650_xmmword_4396A0& __sub_410650_xmmword_4396A0 = *(t_sub_410650_xmmword_4396A0*)0x004396A0;
#define xmmword_4396A0 __sub_410650_xmmword_4396A0
typedef __int128 t_sub_410650_xmmword_4396B0;
static t_sub_410650_xmmword_4396B0& __sub_410650_xmmword_4396B0 = *(t_sub_410650_xmmword_4396B0*)0x004396B0;
#define xmmword_4396B0 __sub_410650_xmmword_4396B0


PROBE_DECL(__sub_410650)
BMF_SSE void __sub_410650(unsigned int Src, int i, int a3)
{
  PROBE_HIT(__sub_410650);
  int n256; // ecx
  int n256_1; // ebx
  int n128_1; // edx
  __m128i si128; // xmm3
  __m128i v7; // xmm2
  __m128i v8; // xmm1
  __m128i v9; // xmm0
  unsigned int n0x70; // eax
  __m128i v11; // xmm4
  __m128i v12; // xmm5
  unsigned int j; // eax
  int n128; // ecx
  int v15; // eax
  char v16; // bl
  char v17; // dl
  char v18; // bl
  __m128i v19; // xmm1
  __m128i v20; // xmm0
  unsigned int k; // eax
  __m128i v22; // xmm0
  __m128i v23; // xmm0
  __m128i v24; // xmm0
  __m128i v25; // xmm0
  __m128i v26; // xmm0
  __m128i v27; // xmm0
  __m128i v28; // xmm0
  int v29; // eax
  int n256_2; // esi
  char v31; // cl
  char v32; // cl
  int v33; // ecx
  unsigned int v34; // eax
  int v35; // edi
  int v36; // eax
  int n128_2; // [esp+8h] [ebp-118h]
  _BYTE v39[255]; // [esp+10h] [ebp-110h]
  char v40; // [esp+10Fh] [ebp-11h]

  n256 = n256_0;
  n256_1 = n256_0;
  if ( n256_0 )
  {
    n128_1 = 2 * n256_0 + 1;
    if ( n2 )
    {
      si128 = _mm_load_si128((const __m128i *)&xmmword_439690);
      v7 = _mm_load_si128((const __m128i *)&xmmword_439670);
      v8 = _mm_load_si128((const __m128i *)&xmmword_4396A0);
      v9 = _mm_load_si128((const __m128i *)&xmmword_4396B0);
      n0x70 = 0;
      v39[0] = 0;
      v40 = 0x80;
      do
      {
        v11 = v8;
        v12 = v8;
        v8 = _mm_add_epi8(v8, si128);
        *(__m128i *)&v39[2 * n0x70 + 1] = _mm_unpacklo_epi8(v11, v9);
        *(__m128i *)&v39[2 * n0x70 + 17] = _mm_unpackhi_epi8(v12, v9);
        v9 = _mm_add_epi8(v9, v7);
        n0x70 += 16;
      }
      while ( n0x70 < 0x70 );
      for ( j = 0; j < 7; ++j )
      {
        v39[4 * j + 225] = -2 * j - 113;
        v39[4 * j + 227] = -2 * j - 114;
        v39[4 * j + 226] = 2 * j + 113;
        v39[4 * j + 228] = 2 * j + 114;
      }
      v39[253] = -127;
      n128 = n128_1;
      v39[254] = 127;
      if ( n128_1 < 128 )
      {
        n128_2 = n128_1;
        v15 = 1;
        do
        {
          v16 = v39[2 * v15];
          v39[2 * v15] = v39[2 * n128];
          v17 = v39[2 * n128 - 1];
          v39[2 * n128] = v16;
          v18 = v39[2 * v15 - 1];
          v39[2 * v15 - 1] = v17;
          v39[2 * n128 - 1] = v18;
          n128 += n128_2;
          ++v15;
        }
        while ( n128 < 128 );
      }
    }
    else
    {
      v19 = _mm_load_si128((const __m128i *)&xmmword_439670);
      v20 = _mm_load_si128((const __m128i *)&xmmword_439680);
      for ( k = 0; k < 0x100; k += 128 )
      {
        *(__m128i *)&v39[k] = v20;
        v22 = _mm_add_epi8(v20, v19);
        *(__m128i *)&v39[k + 16] = v22;
        v23 = _mm_add_epi8(v22, v19);
        *(__m128i *)&v39[k + 32] = v23;
        v24 = _mm_add_epi8(v23, v19);
        *(__m128i *)&v39[k + 48] = v24;
        v25 = _mm_add_epi8(v24, v19);
        *(__m128i *)&v39[k + 64] = v25;
        v26 = _mm_add_epi8(v25, v19);
        *(__m128i *)&v39[k + 80] = v26;
        v27 = _mm_add_epi8(v26, v19);
        *(__m128i *)&v39[k + 96] = v27;
        v28 = _mm_add_epi8(v27, v19);
        *(__m128i *)&v39[k + 112] = v28;
        v20 = _mm_add_epi8(v28, v19);
      }
      v29 = 0;
      if ( n256 < 256 )
      {
        n256_2 = n256;
        do
        {
          v31 = v39[v29];
          v39[v29++] = v39[n256_2];
          v39[n256_2] = v31;
          n256_2 += n128_1;
        }
        while ( n256_2 < 256 );
        n256_1 = n256_0;
        n256 = n256_2;
      }
      if ( n256 - n256_1 < 256 )
      {
        v32 = v39[v29];
        v39[v29] = v40;
        v40 = v32;
      }
    }
    v33 = a3 * i;
    if ( Src < Src + a3 * i )
    {
      if ( v33 / 2 )
      {
        v34 = 0;
        do
        {
          v35 = *(unsigned __int8 *)(Src + 2 * v34 + 1);
          *(_BYTE *)(Src + 2 * v34) = v39[*(unsigned __int8 *)(Src + 2 * v34)];
          *(_BYTE *)(Src + 2 * v34++ + 1) = v39[v35];
        }
        while ( v34 < v33 / 2 );
        v36 = 2 * v34 + 1;
      }
      else
      {
        v36 = 1;
      }
      if ( v33 > (unsigned int)(v36 - 1) )
        *(_BYTE *)(Src + v36 - 1) = v39[*(unsigned __int8 *)(Src + v36 - 1)];
    }
  }
}

#undef n2
#undef n256_0
#undef xmmword_439670
#undef xmmword_439680
#undef xmmword_439690
#undef xmmword_4396A0
#undef xmmword_4396B0
