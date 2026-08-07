// sub_411700 @ 0x00411700 — __cdecl
// Extracted from BMF.cpp:15571-15653 by extract.py per incdec.md.

typedef __int128 t_sub_411700_xmmword_4397A0;
static t_sub_411700_xmmword_4397A0& __sub_411700_xmmword_4397A0 = *(t_sub_411700_xmmword_4397A0*)0x004397A0;

#define sub_436E10 __sub_436E10

PROBE_DECL(__sub_411700)
BMF_REALIGN BMF_SSE int __sub_411700(int a1, int n2)
{
  PROBE_HIT(__sub_411700);
  unsigned int n2_1; // ecx
  unsigned int v3; // esi
  __m128i v4; // xmm2
  __m128i v5; // xmm5
  unsigned int n2_4; // eax
  double v7; // xmm1_8
  double v8; // xmm3_8
  unsigned int n2_3; // ebx
  unsigned int n2_2; // edi
  int v11; // edx
  __m128d v13; // [esp+0h] [ebp-50h]
  double v14; // [esp+8h] [ebp-48h]
  __m128d v15; // [esp+10h] [ebp-40h]
  double v16; // [esp+10h] [ebp-40h]
  __m128 v17; // [esp+20h] [ebp-30h]
  __m128 v18; // [esp+30h] [ebp-20h]

  n2_1 = n2;
  if ( n2 <= 0 )
  {
    v7 = 0;
    v8 = 0.0;
  }
  else
  {
    if ( n2 < 2 )
    {
      n2_4 = 0;
      v7 = 0;
      v8 = 0;
    }
    else
    {
      v13 = 0;
      v15 = 0;
      v3 = 0;
      do
      {
        v4 = _mm_loadl_epi64((const __m128i *)(a1 + 4 * v3));
        v17 = (__m128)_mm_cvtepi32_pd(v4);
        v5 = _mm_cmpeq_epi32((__m128i)0LL, v4);
        v18 = (__m128)_mm_unpacklo_epi32(v5, v5);
        v13 = _mm_add_pd(v13, (__m128d)_mm_andnot_ps(v18, v17));
        __m128d v19 = sub_436E10((__m128d)v17, (__m128d)_mm_xor_si128((__m128i)__sub_411700_xmmword_4397A0, (__m128i)v18));
        v3 += 2;
        v15 = _mm_add_pd(v15, (__m128d)_mm_andnot_ps(v18, (__m128)_mm_mul_pd((__m128d)v17, v19)));
      }
      while ( v3 < n2 - (n2 & 1u) );
      n2_1 = n2;
      n2_4 = n2 - (n2 & 1);
      v7 = v15.m128d_f64[0] + M128D(_mm_unpackhi_pd(v15, v15)).m128d_f64[0];
      v8 = v13.m128d_f64[0] + M128D(_mm_unpackhi_pd(v13, v13)).m128d_f64[0];
    }
    if ( n2_4 < n2_1 )
    {
      v14 = v7;
      v16 = v8;
      n2_3 = n2_4;
      n2_2 = n2_1;
      do
      {
        v11 = *(_DWORD *)(a1 + 4 * n2_3);
        if ( v11 )
        {
          v16 = v16 + (double)v11;
          v14 = v14 + (double)v11 * __svml_log2((__m128i)_mm_set1_pd((double)v11)).m128d_f64[0];
        }
        ++n2_3;
      }
      while ( n2_3 < n2_2 );
      v7 = v14;
      v8 = v16;
    }
    if ( v8 != 0.0 )
      v8 = v8 * __libm_sse2_log(v8);
  }
  return (int)((v8 - v7) * 1.442695040888963);
}

#undef sub_436E10
