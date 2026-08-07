// sub_410AC0 @ 0x00410AC0 — __cdecl
// Extracted from BMF.c:14787-15238 by extract.py per incdec.md.

typedef int t_sub_410AC0_buf[0x10000];
static t_sub_410AC0_buf& __sub_410AC0_buf = *(t_sub_410AC0_buf*)0x00443380;
typedef int t_sub_410AC0_n2;
static t_sub_410AC0_n2& __sub_410AC0_n2 = *(t_sub_410AC0_n2*)0x00443360;
typedef int t_sub_410AC0_n256_0[0x10000];
static t_sub_410AC0_n256_0& __sub_410AC0_n256_0 = *(t_sub_410AC0_n256_0*)0x00443398;
typedef __int128 t_sub_410AC0_xmmword_439700;
static t_sub_410AC0_xmmword_439700& __sub_410AC0_xmmword_439700 = *(t_sub_410AC0_xmmword_439700*)0x00439700;
typedef __int128 t_sub_410AC0_xmmword_439710;
static t_sub_410AC0_xmmword_439710& __sub_410AC0_xmmword_439710 = *(t_sub_410AC0_xmmword_439710*)0x00439710;
typedef __int128 t_sub_410AC0_xmmword_439720;
static t_sub_410AC0_xmmword_439720& __sub_410AC0_xmmword_439720 = *(t_sub_410AC0_xmmword_439720*)0x00439720;
typedef __int128 t_sub_410AC0_xmmword_439730;
static t_sub_410AC0_xmmword_439730& __sub_410AC0_xmmword_439730 = *(t_sub_410AC0_xmmword_439730*)0x00439730;
typedef __int128 t_sub_410AC0_xmmword_439740;
static t_sub_410AC0_xmmword_439740& __sub_410AC0_xmmword_439740 = *(t_sub_410AC0_xmmword_439740*)0x00439740;


PROBE_DECL(__sub_410AC0)
BMF_SSE _BYTE *__sub_410AC0(_BYTE *Src, int i, int a3, _BYTE *a4)
{
  alignas(16) unsigned char __hexrays_frame[848];   // original frame, ebp-0x340..ebp+0x0
  _BYTE * &v80 = *(_BYTE * *)(__hexrays_frame + 0);
  int &v81 = *(int *)(__hexrays_frame + 4);
  int &v82 = *(int *)(__hexrays_frame + 4);
  char &v83 = *(char *)(__hexrays_frame + 8);
  int &v84 = *(int *)(__hexrays_frame + 8);
  int &v85 = *(int *)(__hexrays_frame + 8);
  int &n128_11 = *(int *)(__hexrays_frame + 12);
  int &v87 = *(int *)(__hexrays_frame + 12);
  _BYTE (&v88)[512] = *(_BYTE (*)[512])(__hexrays_frame + 16);
  _BYTE * &v89 = *(_BYTE * *)(__hexrays_frame + 528);
  _BYTE * &v90 = *(_BYTE * *)(__hexrays_frame + 532);
  unsigned int &v91 = *(unsigned int *)(__hexrays_frame + 536);
  unsigned __int8 * &v92 = *(unsigned __int8 * *)(__hexrays_frame + 540);
  int &n128_9 = *(int *)(__hexrays_frame + 544);
  int &n128_2 = *(int *)(__hexrays_frame + 548);
  _BYTE (&v96)[255] = *(_BYTE (*)[255])(__hexrays_frame + 560);
  char &v97 = *(char *)(__hexrays_frame + 815);
  PROBE_HIT(__sub_410AC0);
  int n256; // esi
  int n128_1; // eax
  __m128i si128; // xmm3
  __m128i v7; // xmm2
  __m128i v8; // xmm1
  __m128i v9; // xmm0
  unsigned int n0x70; // edx
  __m128i v11; // xmm4
  __m128i v12; // xmm5
  unsigned int j; // edi
  int n128_3; // ecx
  int v15; // edx
  char v16; // bl
  char v17; // al
  char v18; // bl
  int __sub_410AC0_n2; // edx
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
  char v32; // cl
  char v33; // cl
  unsigned int v34; // ebx
  int v35; // edi
  int n128; // edx
  int v37; // ecx
  unsigned int v38; // esi
  int v39; // ebx
  unsigned int v40; // ecx
  int v41; // esi
  int n128_10; // edi
  int n128_7; // eax
  int n128_8; // edi
  bool v45; // zf
  int v46; // ecx
  int n128_6; // ecx
  int v48; // ebx
  unsigned int m; // esi
  int n128_5; // ecx
  int n128_4; // edi
  char v52; // dl
  unsigned int n; // eax
  _BYTE *v54; // esi
  _BYTE *result; // eax
  _BYTE *v56; // ebx
  char v57; // dl
  int v58; // ecx
  char v59; // dl
  int n16; // edi
  unsigned __int8 *v61; // ecx
  char v62; // bl
  char v63; // dl
  char v64; // dl
  int n16_1; // edi
  int v66; // edi
  int v67; // ebx
  int v68; // edx
  char v69; // cl
  bool v70; // cc
  char v71; // cl
  char v72; // dl
  unsigned int v73; // ecx
  int v74; // edi
  char v75; // bl
  int n16_2; // edi
  unsigned __int8 *v77; // ecx
  unsigned int v78; // edx
  _BYTE *v79; // edi

  n256 = __sub_410AC0_n256_0[0];
  n128_1 = 2 * __sub_410AC0_n256_0[0] + 1;
  if ( ::__sub_410AC0_n2 )
  {
    si128 = _mm_load_si128((const __m128i *)&__sub_410AC0_xmmword_439720);
    v7 = _mm_load_si128((const __m128i *)&__sub_410AC0_xmmword_439700);
    v8 = _mm_load_si128((const __m128i *)&__sub_410AC0_xmmword_439730);
    v9 = _mm_load_si128((const __m128i *)&__sub_410AC0_xmmword_439740);
    n0x70 = 0;
    v96[0] = 0;
    v97 = 0x80;
    do
    {
      v11 = v8;
      v12 = v8;
      v8 = _mm_add_epi8(v8, si128);
      *(__m128i *)&v96[2 * n0x70 + 1] = _mm_unpacklo_epi8(v11, v9);
      *(__m128i *)&v96[2 * n0x70 + 17] = _mm_unpackhi_epi8(v12, v9);
      v9 = _mm_add_epi8(v9, v7);
      n0x70 += 16;
    }
    while ( n0x70 < 0x70 );
    for ( j = 0; j < 7; ++j )
    {
      v96[4 * j + 225] = -2 * j - 113;
      v96[4 * j + 226] = 2 * j + 113;
      v96[4 * j + 227] = -2 * j - 114;
      v96[4 * j + 228] = 2 * j + 114;
    }
    v96[253] = -127;
    v96[254] = 127;
    if ( !n256 || (n128_3 = n128_1, n128_1 >= 128) )
    {
LABEL_21:
      v88[0] = 0;
      v88[128] = -1;
      if ( n256 <= 0 )
      {
        n128 = 1;
      }
      else
      {
        if ( n256 / 2 )
        {
          n128_2 = n128_1;
          v34 = 0;
          v35 = 0;
          do
          {
            v88[v35 + 255] = 0;
            v88[2 * v34 + 1] = 0;
            v88[v35 + 254] = 0;
            n128 = 2 * v34 + 3;
            v35 -= 2;
            v88[2 * v34++ + 2] = 0;
          }
          while ( v34 < n256 / 2 );
          n128_1 = n128_2;
          v37 = 2 * v34 + 1;
        }
        else
        {
          n128 = 1;
          v37 = 1;
        }
        if ( n256 > (unsigned int)(v37 - 1) )
        {
          v88[-v37 + 256] = 0;
          v88[v37] = 0;
          n128 = v37 + 1;
        }
        if ( n128 >= 128 )
          goto LABEL_52;
      }
      n128_11 = 1;
      v38 = 128 - n128;
      v91 = (128 - n128) / 2;
      v39 = 0;
      if ( v91 )
      {
        v40 = 0;
        v41 = 0;
        v90 = &v88[n128];
        n128_2 = n128_1;
        v89 = &v88[-n128];
        n128_10 = 1;
        do
        {
          n128_7 = n128_2;
          n128_8 = n128_10 - 1;
          if ( n128_8 )
            n128_7 = n128_8;
          n128_9 = n128_7;
          if ( !n128_8 )
            ++v39;
          v83 = 2 * v39;
          v90[2 * v40] = 2 * v39;
          v92 = (unsigned __int8 *)(unsigned __int8)(2 * v39 - 1);
          n128_10 = n128_9 - 1;
          v45 = n128_9 == 1;
          v89[v41 + 256] = (_BYTE)v92;
          if ( v45 )
          {
            n128_10 = n128_2;
            v83 = 2 * ++v39;
            v92 = (unsigned __int8 *)(unsigned __int8)(2 * v39 - 1);
          }
          v90[2 * v40++ + 1] = v83;
          v89[v41 + 255] = (_BYTE)v92;
          v41 -= 2;
        }
        while ( v40 < v91 );
        v38 = 128 - n128;
        n128_11 = n128_10;
        v46 = 2 * v40 + 1;
      }
      else
      {
        v46 = 1;
      }
      if ( v38 > v46 - 1 )
      {
        if ( n128_11 == 1 )
          LOBYTE(v39) = v39 + 1;
        v88[n128 - 1 + v46] = 2 * v39;
        v88[-n128 - v46 + 257] = 2 * v39 - 1;
      }
      goto LABEL_52;
    }
    n128_2 = n128_1;
    v15 = 1;
    do
    {
      v16 = v96[2 * v15];
      v96[2 * v15] = v96[2 * n128_3];
      v17 = v96[2 * n128_3 - 1];
      v96[2 * n128_3] = v16;
      v18 = v96[2 * v15 - 1];
      v96[2 * v15 - 1] = v17;
      v96[2 * n128_3 - 1] = v18;
      n128_3 += n128_2;
      ++v15;
    }
    while ( n128_3 < 128 );
    n128_1 = n128_2;
    __sub_410AC0_n2 = ::__sub_410AC0_n2;
  }
  else
  {
    v20 = _mm_load_si128((const __m128i *)&__sub_410AC0_xmmword_439700);
    v21 = _mm_load_si128((const __m128i *)&__sub_410AC0_xmmword_439710);
    for ( k = 0; k < 0x100; k += 128 )
    {
      *(__m128i *)&v96[k] = v21;
      v23 = _mm_add_epi8(v21, v20);
      *(__m128i *)&v96[k + 16] = v23;
      v24 = _mm_add_epi8(v23, v20);
      *(__m128i *)&v96[k + 32] = v24;
      v25 = _mm_add_epi8(v24, v20);
      *(__m128i *)&v96[k + 48] = v25;
      v26 = _mm_add_epi8(v25, v20);
      *(__m128i *)&v96[k + 64] = v26;
      v27 = _mm_add_epi8(v26, v20);
      *(__m128i *)&v96[k + 80] = v27;
      v28 = _mm_add_epi8(v27, v20);
      *(__m128i *)&v96[k + 96] = v28;
      v29 = _mm_add_epi8(v28, v20);
      *(__m128i *)&v96[k + 112] = v29;
      v21 = _mm_add_epi8(v29, v20);
    }
    n256_1 = n256;
    v31 = 0;
    if ( n256 < 256 )
    {
      do
      {
        v32 = v96[v31];
        v96[v31++] = v96[n256];
        v96[n256] = v32;
        n256 += n128_1;
      }
      while ( n256 < 256 );
      n256_1 = __sub_410AC0_n256_0[0];
    }
    if ( n256 - n256_1 < 256 )
    {
      v33 = v96[v31];
      v96[v31] = v97;
      __sub_410AC0_n2 = ::__sub_410AC0_n2;
      v97 = v33;
    }
    else
    {
      __sub_410AC0_n2 = ::__sub_410AC0_n2;
    }
  }
  if ( __sub_410AC0_n2 )
  {
    n256 = __sub_410AC0_n256_0[0];
    goto LABEL_21;
  }
  n128_6 = n128_1 + 1;
  v48 = 0;
  for ( m = 0; m < 0x80; ++m )
  {
    n128_5 = n128_6 - 1;
    n128_4 = n128_1;
    if ( n128_5 )
      n128_4 = n128_5;
    else
      ++v48;
    v52 = v48;
    v88[2 * m] = v48;
    n128_6 = n128_4 - 1;
    if ( n128_4 == 1 )
    {
      n128_6 = n128_1;
      v52 = ++v48;
    }
    v88[2 * m + 1] = v52;
  }
LABEL_52:
  for ( n = 0; n < 0x80; ++n )
  {
    v88[(unsigned __int8)v96[2 * n] + 256] = 2 * n;
    v88[(unsigned __int8)v96[2 * n + 1] + 256] = 2 * n + 1;
  }
  *a4 = *Src;
  v54 = a4 + 1;
  result = Src + 1;
  v56 = (_BYTE *)(i - 1);
  if ( i != 1 )
  {
    v84 = i - 1;
    do
    {
      v57 = *(v54 - 1);
      v58 = (unsigned __int8)v88[(unsigned __int8)(*result - v57)];
      v81 = (unsigned __int8)(*result - v57);
      v59 = v96[v58] + v57;
      n16 = (unsigned __int8)*v54 - (unsigned __int8)(v59 + *v54 - *result);
      if ( n16 < -16 || n16 > 16 )
      {
        LOBYTE(v58) = v88[v81 + 256];
        *v54 = *result;
      }
      else
      {
        *v54 = v59;
      }
      *result++ = v58;
      ++v54;
      --v84;
    }
    while ( v84 );
    v56 = (_BYTE *)(i - 1);
  }
  v61 = &v54[-i];
  if ( a3 != 1 )
  {
    v82 = a3 - 1;
    v80 = v56;
    do
    {
      v62 = *result;
      v92 = v61;
      v63 = v54[-i];
      v85 = (unsigned __int8)(v62 - v63);
      v87 = (unsigned __int8)v88[v85];
      v64 = v96[v87] + v63;
      n16_1 = (unsigned __int8)*v54 - (unsigned __int8)(v64 + *v54 - v62);
      if ( n16_1 < -16 || n16_1 > 16 )
      {
        v87 = (unsigned __int8)v88[v85 + 256];
        *v54 = v62;
      }
      else
      {
        *v54 = v64;
      }
      *result++ = v87;
      ++v61;
      ++v54;
      ++*(_DWORD *)&__sub_410AC0_buf[4 * v87];
      if ( i != 1 )
      {
        v89 = v80;
        do
        {
          v66 = (unsigned __int8)*(v54 - 1);
          v67 = *v61;
          v68 = (unsigned __int8)v54[-i - 1];
          if ( v66 < v67 )
          {
            if ( v68 >= v66 )
            {
              v92 = v61;
              v71 = v66 + v67 - v68;
              v70 = v68 <= v67;
              LOBYTE(v67) = v66;
              if ( v70 )
                LOBYTE(v67) = v71;
              v61 = v92;
            }
          }
          else if ( v68 <= v66 )
          {
            v92 = v61;
            v69 = v66 + v67 - v68;
            v70 = v68 < v67;
            LOBYTE(v67) = v66;
            if ( !v70 )
              LOBYTE(v67) = v69;
            v61 = v92;
          }
          v72 = *result;
          v92 = v61;
          v73 = (unsigned __int8)v88[(unsigned __int8)(v72 - v67)];
          v90 = (_BYTE *)(unsigned __int8)(v72 - v67);
          v74 = (unsigned __int8)*v54;
          v91 = v73;
          v75 = v96[v73] + v67;
          n16_2 = v74 - (unsigned __int8)(v75 + v74 - v72);
          v77 = v92;
          if ( n16_2 < -16 || n16_2 > 16 )
          {
            v91 = (unsigned __int8)v88[(_DWORD)v90 + 256];
            *v54 = v72;
          }
          else
          {
            *v54 = v75;
          }
          v78 = v91;
          v79 = v89;
          *result++ = v91;
          v61 = v77 + 1;
          ++*(_DWORD *)&__sub_410AC0_buf[4 * v78];
          ++v54;
          v89 = v79 - 1;
        }
        while ( v79 != (_BYTE *)1 );
      }
      --v82;
    }
    while ( v82 );
  }
  return result;
}

