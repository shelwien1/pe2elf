// sub_4111B0 @ 0x004111B0 — __cdecl
// Extracted from BMF.cpp:15241-15568 by extract.py per incdec.md.

typedef int t_sub_4111B0_n2;
static t_sub_4111B0_n2& __sub_4111B0_n2 = *(t_sub_4111B0_n2*)0x00443360;
typedef int t_sub_4111B0_n256_0[0x10000];
static t_sub_4111B0_n256_0& __sub_4111B0_n256_0 = *(t_sub_4111B0_n256_0*)0x00443398;
typedef __int128 t_sub_4111B0_xmmword_439750;
static t_sub_4111B0_xmmword_439750& __sub_4111B0_xmmword_439750 = *(t_sub_4111B0_xmmword_439750*)0x00439750;
typedef __int128 t_sub_4111B0_xmmword_439760;
static t_sub_4111B0_xmmword_439760& __sub_4111B0_xmmword_439760 = *(t_sub_4111B0_xmmword_439760*)0x00439760;
typedef __int128 t_sub_4111B0_xmmword_439770;
static t_sub_4111B0_xmmword_439770& __sub_4111B0_xmmword_439770 = *(t_sub_4111B0_xmmword_439770*)0x00439770;
typedef __int128 t_sub_4111B0_xmmword_439780;
static t_sub_4111B0_xmmword_439780& __sub_4111B0_xmmword_439780 = *(t_sub_4111B0_xmmword_439780*)0x00439780;
typedef __int128 t_sub_4111B0_xmmword_439790;
static t_sub_4111B0_xmmword_439790& __sub_4111B0_xmmword_439790 = *(t_sub_4111B0_xmmword_439790*)0x00439790;


PROBE_DECL(__sub_4111B0)
BMF_REALIGN BMF_SSE unsigned int __sub_4111B0(_BYTE *Src, int i, int a3, _BYTE *a4)
{
  alignas(16) unsigned char __hexrays_frame[848];   // original frame, ebp-0x340..ebp+0x0
  char &v57 = *(char *)(__hexrays_frame + 0);
  char &v58 = *(char *)(__hexrays_frame + 4);
  _BYTE * &Src_2 = *(_BYTE * *)(__hexrays_frame + 8);
  _BYTE * &Src_3 = *(_BYTE * *)(__hexrays_frame + 8);
  _BYTE * &Src_4 = *(_BYTE * *)(__hexrays_frame + 8);
  int &n128_11 = *(int *)(__hexrays_frame + 16);
  _BYTE (&v63)[512] = *(_BYTE (*)[512])(__hexrays_frame + 24);
  _BYTE * &v64 = *(_BYTE * *)(__hexrays_frame + 536);
  _BYTE * &v65 = *(_BYTE * *)(__hexrays_frame + 540);
  unsigned int &v66 = *(unsigned int *)(__hexrays_frame + 544);
  int &v67 = *(int *)(__hexrays_frame + 548);
  int &n128_9 = *(int *)(__hexrays_frame + 552);
  int &n128_2 = *(int *)(__hexrays_frame + 556);
  _BYTE (&v70)[255] = *(_BYTE (*)[255])(__hexrays_frame + 560);
  char &v71 = *(char *)(__hexrays_frame + 815);
  _BYTE * &Src_5 = *(_BYTE * *)(__hexrays_frame + 816);
  PROBE_HIT(__sub_4111B0);
  _BYTE *Src_1; // edi
  int n256; // ecx
  int n128_1; // edx
  __m128i si128; // xmm3
  __m128i v8; // xmm2
  __m128i v9; // xmm1
  __m128i v10; // xmm0
  unsigned int n0x70; // eax
  __m128i v12; // xmm4
  __m128i v13; // xmm5
  unsigned int j; // esi
  int n128_3; // ebx
  int v16; // eax
  char v17; // cl
  char v18; // dl
  char v19; // cl
  int __sub_4111B0_n2; // eax
  __m128i v21; // xmm1
  __m128i v22; // xmm0
  unsigned int k; // eax
  __m128i v24; // xmm0
  __m128i v25; // xmm0
  __m128i v26; // xmm0
  __m128i v27; // xmm0
  __m128i v28; // xmm0
  __m128i v29; // xmm0
  __m128i v30; // xmm0
  int n256_1; // eax
  int v32; // ebx
  int v33; // esi
  char v34; // al
  char v35; // al
  unsigned int v36; // eax
  int v37; // edi
  int n128; // ebx
  int v39; // esi
  int v40; // ecx
  unsigned int v41; // eax
  int n128_10; // edi
  int v43; // esi
  int n128_7; // edx
  int n128_8; // edi
  bool v46; // zf
  int v47; // edx
  int n128_6; // esi
  int v49; // ebx
  unsigned int m; // ecx
  int n128_5; // esi
  int n128_4; // edi
  char v53; // al
  unsigned int n0x80; // eax
  int n64; // esi

  Src_1 = Src;
  n256 = __sub_4111B0_n256_0[0];
  Src_5 = &Src[a3 * i];
  n128_1 = 2 * __sub_4111B0_n256_0[0] + 1;
  if ( ::__sub_4111B0_n2 )
  {
    si128 = _mm_load_si128((const __m128i *)&__sub_4111B0_xmmword_439770);
    v8 = _mm_load_si128((const __m128i *)&__sub_4111B0_xmmword_439750);
    v9 = _mm_load_si128((const __m128i *)&__sub_4111B0_xmmword_439780);
    v10 = _mm_load_si128((const __m128i *)&__sub_4111B0_xmmword_439790);
    n0x70 = 0;
    v70[0] = 0;
    v71 = 0x80;
    do
    {
      v12 = v9;
      v13 = v9;
      v9 = _mm_add_epi8(v9, si128);
      *(__m128i *)&v70[2 * n0x70 + 1] = _mm_unpacklo_epi8(v12, v10);
      *(__m128i *)&v70[2 * n0x70 + 17] = _mm_unpackhi_epi8(v13, v10);
      v10 = _mm_add_epi8(v10, v8);
      n0x70 += 16;
    }
    while ( n0x70 < 0x70 );
    for ( j = 0; j < 7; ++j )
    {
      v70[4 * j + 225] = -2 * j - 113;
      v70[4 * j + 227] = -2 * j - 114;
      v70[4 * j + 226] = 2 * j + 113;
      v70[4 * j + 228] = 2 * j + 114;
    }
    v70[253] = -127;
    v70[254] = 127;
    if ( !n256 || (n128_3 = n128_1, n128_1 >= 128) )
    {
LABEL_22:
      v63[0] = 0;
      v63[128] = -1;
      if ( n256 <= 0 )
      {
        n128 = 1;
      }
      else
      {
        if ( n256 / 2 )
        {
          n128_2 = n128_1;
          Src_2 = Src_1;
          v36 = 0;
          v37 = 0;
          do
          {
            v63[v37 + 255] = 0;
            v63[2 * v36 + 1] = 0;
            v63[v37 + 254] = 0;
            n128 = 2 * v36 + 3;
            v37 -= 2;
            v63[2 * v36++ + 2] = 0;
          }
          while ( v36 < n256 / 2 );
          n128_1 = n128_2;
          Src_1 = Src_2;
          v39 = 2 * v36 + 1;
        }
        else
        {
          n128 = 1;
          v39 = 1;
        }
        if ( n256 > (unsigned int)(v39 - 1) )
        {
          v63[-v39 + 256] = 0;
          v63[v39] = 0;
          n128 = v39 + 1;
        }
        if ( n128 >= 128 )
          goto LABEL_54;
      }
      n128_11 = 1;
      v40 = 0;
      v66 = (128 - n128) / 2;
      if ( v66 )
      {
        v41 = 0;
        n128_2 = n128_1;
        Src_3 = Src_1;
        n128_10 = 1;
        v65 = &v63[n128];
        v64 = &v63[-n128];
        v43 = 0;
        do
        {
          n128_7 = n128_2;
          n128_8 = n128_10 - 1;
          if ( n128_8 )
            n128_7 = n128_8;
          n128_9 = n128_7;
          if ( !n128_8 )
            ++v40;
          v58 = 2 * v40;
          v65[2 * v41] = 2 * v40;
          v67 = (unsigned __int8)(2 * v40 - 1);
          n128_10 = n128_9 - 1;
          v46 = n128_9 == 1;
          v64[v43 + 256] = v67;
          if ( v46 )
          {
            n128_10 = n128_2;
            v58 = 2 * ++v40;
            v67 = (unsigned __int8)(2 * v40 - 1);
          }
          v65[2 * v41++ + 1] = v58;
          v64[v43 + 255] = v67;
          v43 -= 2;
        }
        while ( v41 < v66 );
        n128_11 = n128_10;
        Src_1 = Src_3;
        v47 = 2 * v41 + 1;
      }
      else
      {
        v47 = 1;
      }
      if ( v47 - 1 < (unsigned int)(128 - n128) )
      {
        if ( n128_11 == 1 )
          LOBYTE(v40) = v40 + 1;
        v63[n128 - 1 + v47] = 2 * v40;
        v63[-n128 - v47 + 257] = 2 * v40 - 1;
      }
      goto LABEL_54;
    }
    n128_2 = n128_1;
    v16 = 1;
    do
    {
      v17 = v70[2 * v16];
      v70[2 * v16] = v70[2 * n128_3];
      v18 = v70[2 * n128_3 - 1];
      v70[2 * n128_3] = v17;
      v19 = v70[2 * v16 - 1];
      v70[2 * v16 - 1] = v18;
      v70[2 * n128_3 - 1] = v19;
      n128_3 += n128_2;
      ++v16;
    }
    while ( n128_3 < 128 );
    n128_1 = n128_2;
    Src_1 = Src;
    __sub_4111B0_n2 = ::__sub_4111B0_n2;
  }
  else
  {
    v21 = _mm_load_si128((const __m128i *)&__sub_4111B0_xmmword_439750);
    v22 = _mm_load_si128((const __m128i *)&__sub_4111B0_xmmword_439760);
    for ( k = 0; k < 0x100; k += 128 )
    {
      *(__m128i *)&v70[k] = v22;
      v24 = _mm_add_epi8(v22, v21);
      *(__m128i *)&v70[k + 16] = v24;
      v25 = _mm_add_epi8(v24, v21);
      *(__m128i *)&v70[k + 32] = v25;
      v26 = _mm_add_epi8(v25, v21);
      *(__m128i *)&v70[k + 48] = v26;
      v27 = _mm_add_epi8(v26, v21);
      *(__m128i *)&v70[k + 64] = v27;
      v28 = _mm_add_epi8(v27, v21);
      *(__m128i *)&v70[k + 80] = v28;
      v29 = _mm_add_epi8(v28, v21);
      *(__m128i *)&v70[k + 96] = v29;
      v30 = _mm_add_epi8(v29, v21);
      *(__m128i *)&v70[k + 112] = v30;
      v22 = _mm_add_epi8(v30, v21);
    }
    n256_1 = n256;
    v32 = 0;
    if ( n256 < 256 )
    {
      v33 = 0;
      do
      {
        v34 = v70[v33];
        v70[v33++] = v70[n256];
        v70[n256] = v34;
        n256 += n128_1;
      }
      while ( n256 < 256 );
      n256_1 = __sub_4111B0_n256_0[0];
      v32 = v33;
    }
    if ( n256 - n256_1 < 256 )
    {
      v35 = v70[v32];
      v70[v32] = v71;
      v71 = v35;
    }
    __sub_4111B0_n2 = ::__sub_4111B0_n2;
  }
  if ( __sub_4111B0_n2 )
  {
    n256 = __sub_4111B0_n256_0[0];
    goto LABEL_22;
  }
  Src_4 = Src_1;
  n128_6 = n128_1 + 1;
  v49 = 0;
  for ( m = 0; m < 0x80; ++m )
  {
    n128_5 = n128_6 - 1;
    n128_4 = n128_1;
    if ( n128_5 )
      n128_4 = n128_5;
    else
      ++v49;
    v53 = v49;
    v63[2 * m] = v49;
    n128_6 = n128_4 - 1;
    if ( n128_4 == 1 )
    {
      n128_6 = n128_1;
      v53 = ++v49;
    }
    v63[2 * m + 1] = v53;
  }
  Src_1 = Src_4;
LABEL_54:
  for ( n0x80 = 0; n0x80 < 0x80; ++n0x80 )
  {
    v63[(unsigned __int8)v70[2 * n0x80] + 256] = 2 * n0x80;
    v63[(unsigned __int8)v70[2 * n0x80 + 1] + 256] = 2 * n0x80 + 1;
  }
  for ( ; Src_1 < Src_5; ++a4 )
  {
    n0x80 = (unsigned __int8)v63[(unsigned __int8)*Src_1];
    v57 = v70[n0x80];
    n64 = (unsigned __int8)*a4 - (unsigned __int8)(*a4 + v57 - *Src_1);
    if ( n64 < -64 || n64 > 64 )
    {
      *a4 = *Src_1;
      n0x80 = (unsigned __int8)v63[(unsigned __int8)*Src_1 + 256];
    }
    else
    {
      *a4 = v57;
    }
    *Src_1++ = n0x80;
  }
  return n0x80;
}

