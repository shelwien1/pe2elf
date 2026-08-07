// sub_40B330 @ 0x0040B330 — __thiscall
// Extracted from BMF.cpp:9195-9674 by extract.py per incdec.md.

typedef int t_sub_40B330_Buffer_0;
static t_sub_40B330_Buffer_0& __sub_40B330_Buffer_0 = *(t_sub_40B330_Buffer_0*)0x00443378;
typedef int t_sub_40B330_Buffer_1;
static t_sub_40B330_Buffer_1& __sub_40B330_Buffer_1 = *(t_sub_40B330_Buffer_1*)0x00443374;
typedef int t_sub_40B330_Src;
static t_sub_40B330_Src& __sub_40B330_Src = *(t_sub_40B330_Src*)0x00442E70;
typedef unsigned char t_sub_40B330_byte_439418[16];
static t_sub_40B330_byte_439418& __sub_40B330_byte_439418 = *(t_sub_40B330_byte_439418*)0x00439418;
typedef int t_sub_40B330_dword_438B00[0x10000];
static t_sub_40B330_dword_438B00& __sub_40B330_dword_438B00 = *(t_sub_40B330_dword_438B00*)0x00438B00;
typedef int t_sub_40B330_dword_442E74;
static t_sub_40B330_dword_442E74& __sub_40B330_dword_442E74 = *(t_sub_40B330_dword_442E74*)0x00442E74;
typedef int t_sub_40B330_dword_443388;
static t_sub_40B330_dword_443388& __sub_40B330_dword_443388 = *(t_sub_40B330_dword_443388*)0x00443388;
typedef int t_sub_40B330_dword_44340C[0x10000];
static t_sub_40B330_dword_44340C& __sub_40B330_dword_44340C = *(t_sub_40B330_dword_44340C*)0x0044340C;
typedef int t_sub_40B330_dword_443420;
static t_sub_40B330_dword_443420& __sub_40B330_dword_443420 = *(t_sub_40B330_dword_443420*)0x00443420;
typedef int t_sub_40B330_dword_443424;
static t_sub_40B330_dword_443424& __sub_40B330_dword_443424 = *(t_sub_40B330_dword_443424*)0x00443424;
typedef int t_sub_40B330_n14;
static t_sub_40B330_n14& __sub_40B330_n14 = *(t_sub_40B330_n14*)0x00443414;
typedef int t_sub_40B330_n24;
static t_sub_40B330_n24& __sub_40B330_n24 = *(t_sub_40B330_n24*)0x00443410;
typedef int t_sub_40B330_n256;
static t_sub_40B330_n256& __sub_40B330_n256 = *(t_sub_40B330_n256*)0x0044336C;
typedef int t_sub_40B330_n256_2[0x10000];
static t_sub_40B330_n256_2& __sub_40B330_n256_2 = *(t_sub_40B330_n256_2*)0x0044338C;
typedef int t_sub_40B330_n633;
static t_sub_40B330_n633& __sub_40B330_n633 = *(t_sub_40B330_n633*)0x00442E40;
typedef int t_sub_40B330_n7;
static t_sub_40B330_n7& __sub_40B330_n7 = *(t_sub_40B330_n7*)0x0044341C;
typedef int t_sub_40B330_n8;
static t_sub_40B330_n8& __sub_40B330_n8 = *(t_sub_40B330_n8*)0x00443368;
typedef int t_sub_40B330_n9;
static t_sub_40B330_n9& __sub_40B330_n9 = *(t_sub_40B330_n9*)0x00443418;
typedef void * t_sub_40B330_off_4410C0[0x10000];
static t_sub_40B330_off_4410C0& __sub_40B330_off_4410C0 = *(t_sub_40B330_off_4410C0*)0x004410C0;

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980
#define sub_40BBC0 __sub_40BBC0
#define sub_411700 __sub_411700

PROBE_DECL(__sub_40B330)
BMF_REALIGN BMF_SSE __attribute__((thiscall)) unsigned int __sub_40B330(_DWORD *_this, _DWORD *buf)
{
  alignas(16) unsigned char __hexrays_frame[2176];   // original frame, ebp-0x870..ebp+0x0
  int &v79 = *(int *)(__hexrays_frame + 0);
  int &v80 = *(int *)(__hexrays_frame + 0);
  int &v81 = *(int *)(__hexrays_frame + 0);
  int &v82 = *(int *)(__hexrays_frame + 0);
  int &v83 = *(int *)(__hexrays_frame + 0);
  int &v84 = *(int *)(__hexrays_frame + 4);
  int &v85 = *(int *)(__hexrays_frame + 4);
  int &v86 = *(int *)(__hexrays_frame + 4);
  int &v87 = *(int *)(__hexrays_frame + 4);
  int &v88 = *(int *)(__hexrays_frame + 4);
  int &v89 = *(int *)(__hexrays_frame + 8);
  int &v90 = *(int *)(__hexrays_frame + 8);
  int &v91 = *(int *)(__hexrays_frame + 8);
  int &v92 = *(int *)(__hexrays_frame + 8);
  int &v93 = *(int *)(__hexrays_frame + 8);
  int &__sub_40B330_Src = *(int *)(__hexrays_frame + 16);
  int &Src_4 = *(int *)(__hexrays_frame + 20);
  int &Src_8 = *(int *)(__hexrays_frame + 24);
  _OWORD (&v97)[63] = *(_OWORD (*)[63])(__hexrays_frame + 32);
  int &v98 = *(int *)(__hexrays_frame + 1040);
  char (&v99)[16] = *(char (*)[16])(__hexrays_frame + 1044);
  _OWORD (&v100)[63] = *(_OWORD (*)[63])(__hexrays_frame + 1060);
  int &v101 = *(int *)(__hexrays_frame + 2068);
  int (&v102)[6] = *(int (*)[6])(__hexrays_frame + 2072);
  int &v103 = *(int *)(__hexrays_frame + 2096);
  int &v104 = *(int *)(__hexrays_frame + 2100);
  int &v105 = *(int *)(__hexrays_frame + 2104);
  int &v106 = *(int *)(__hexrays_frame + 2108);
  int &v107 = *(int *)(__hexrays_frame + 2112);
  int &v108 = *(int *)(__hexrays_frame + 2116);
  int &v109 = *(int *)(__hexrays_frame + 2120);
  int &v110 = *(int *)(__hexrays_frame + 2124);
  int &v111 = *(int *)(__hexrays_frame + 2128);
  unsigned int &n5_2 = *(unsigned int *)(__hexrays_frame + 2132);
  int &v113 = *(int *)(__hexrays_frame + 2136);
  _DWORD * &this_1 = *(_DWORD * *)(__hexrays_frame + 2140);
  PROBE_HIT(__sub_40B330);
  unsigned int i; // eax
  int v3; // esi
  char *v4; // edi
  int v5; // edx
  int v6; // ebx
  _DWORD *this_2; // ecx
  unsigned int n0x40_1; // edx
  signed int n28672; // ebx
  unsigned int n0x40_2; // eax
  unsigned int n0x40; // eax
  __m128i v12; // xmm0
  __m128i v13; // xmm0
  int v14; // edx
  int Src_1; // ebx
  char *v16; // ecx
  int v17; // esi
  int v18; // edx
  unsigned int n0x80; // eax
  int v20; // edi
  int Src_2; // ebx
  int v22; // eax
  int Src_3; // edx
  int v24; // edx
  int v25; // ecx
  unsigned int n0x20; // ebx
  int v27; // edx
  int v28; // esi
  int v29; // eax
  unsigned int v30; // eax
  unsigned int n6; // eax
  int __sub_40B330_n8; // edx
  int n5; // esi
  int Src_5; // ebx
  unsigned int n0x3F; // edi
  int v36; // eax
  int v37; // edx
  int Src_6; // ebx
  char *v39; // ecx
  int v40; // esi
  int v41; // edx
  unsigned int n0x80_1; // eax
  int v43; // edi
  int Src_7; // ebx
  int v45; // eax
  char v46; // fps
  int Src_9; // edx
  int v48; // ebx
  unsigned int n5_1; // edi
  int v50; // ebx
  char v51; // fps
  int v52; // eax
  int v53; // esi
  int v54; // edi
  int v55; // esi
  int v56; // edi
  char v57; // fps
  int v58; // edi
  char v59; // fps
  int v60; // edi
  char v61; // fps
  int v62; // edi
  char v63; // fps
  int v64; // eax
  int v65; // edx
  unsigned int n0x100; // eax
  int v67; // edx
  __m128i v68; // xmm3
  __m128i v69; // xmm7
  __m128i si128; // xmm5
  __m128i v71; // xmm1
  __m128i v72; // xmm3
  __m128i v73; // xmm5
  __m128i v74; // xmm0
  char v75; // fps
  unsigned int n5_3; // ecx
  int v77; // eax
  int v78; // edx

  this_1 = _this;
  for ( i = 0; i < 0xC; ++i )
  {
    if ( __sub_40B330_dword_438B00[i] > 0 )
    {
      v3 = (int)*(&__sub_40B330_n633 + i);
      v4 = (char *)__sub_40B330_off_4410C0[i];
      v5 = __sub_40B330_dword_438B00[i];
      v6 = 0;
      Src_4 = (unsigned __int8)__sub_40B330_byte_439418[i];
      __sub_40B330_Src = i;
      do
      {
        ++v6;
        *(_DWORD *)(v3 + 4 * v6 - 4) -= 1 << ((Src_4 - v4[v6 - 1]) & 31);
      }
      while ( v6 < v5 );
      i = __sub_40B330_Src;
    }
  }
  this_2 = this_1;
  v113 = (int)(this_1 + 49664);
  n0x40_1 = (unsigned int)(this_1 + 49664) & 0xF;
  if ( n0x40_1 )
  {
    n28672 = 0;
    if ( (n0x40_1 & 3) != 0 )
    {
      n0x40 = 0;
      goto LABEL_16;
    }
    n0x40_1 = (16 - n0x40_1) >> 2;
    n0x40_2 = 0;
    do
      n28672 += this_1[n0x40_2++ + 49664];
    while ( n0x40_2 < n0x40_1 );
  }
  else
  {
    n28672 = 0;
  }
  n0x40 = 64 - (-n0x40_1 & 3);
  v12 = _mm_cvtsi32_si128(n28672);
  do
  {
    v12 = _mm_add_epi32(v12, *(__m128i *)&this_1[n0x40_1 + 49664]);
    n0x40_1 += 4;
  }
  while ( n0x40_1 < n0x40 );
  v13 = _mm_add_epi32(v12, _mm_srli_si128(v12, 8));
  n28672 = _mm_cvtsi128_si32(_mm_add_epi32(v13, _mm_srli_si128(v13, 4)));
LABEL_16:
  while ( n0x40 < 0x40 )
    n28672 += this_1[n0x40++ + 49664];
  __sub_40B330_dword_44340C[0] = 64;
  __sub_40B330_dword_443424 = 0;
  if ( n28672 < 28672 && !__sub_40B330_dword_443388 )
  {
    __sub_40B330_n24 = 24;
    __sub_40B330_n14 = 14;
    __sub_40B330_Src = 0;
    __sub_40B330_n9 = 9;
    __sub_40B330_n7 = 7;
    __sub_40B330_dword_443420 = 0;
    do
    {
      v14 = __sub_40B330_dword_44340C[__sub_40B330_Src];
      Src_1 = v14 - 1;
      if ( v14 - 1 >= *(&__sub_40B330_n24 + __sub_40B330_Src) )
      {
        v16 = (&::__sub_40B330_Src)[__sub_40B330_Src];
        Src_8 = *(&__sub_40B330_n24 + __sub_40B330_Src);
        v17 = 0;
        v18 = (int)&this_1[257 * v14 + 49471];
        do
        {
          Src_4 = Src_1;
          ++v17;
          n0x80 = 0;
          v20 = v18 - 1028 * v17;
          do
          {
            *(_DWORD *)&v16[8 * n0x80] += *(_DWORD *)(v20 + 8 * n0x80 + 1028);
            *(_DWORD *)&v16[8 * n0x80 + 4] += *(_DWORD *)(v20 + 8 * n0x80 + 1032);
            ++n0x80;
          }
          while ( n0x80 < 0x80 );
          Src_2 = Src_4;
          *((_DWORD *)v16 + 256) += *(_DWORD *)(v20 + 2052);
          Src_1 = Src_2 - 1;
        }
        while ( Src_1 >= Src_8 );
      }
      v22 = sub_411700((int)(&::__sub_40B330_Src)[__sub_40B330_Src], 257);
      Src_3 = __sub_40B330_Src;
      v102[__sub_40B330_Src] = v22;
      __sub_40B330_Src = Src_3 + 1;
    }
    while ( (unsigned int)(Src_3 + 1) < 6 );
    v24 = __sub_40B330_dword_443388;
    goto LABEL_28;
  }
  n5 = 5;
  __sub_40B330_Src = (n28672 + 3) / 6;
  Src_5 = __sub_40B330_Src;
  n0x3F = 0;
  v36 = 0;
  do
  {
    Src_5 -= this_2[n0x3F + 49665];
    if ( Src_5 < 0 || n5 >= v36 + 62 )
    {
      Src_5 += __sub_40B330_Src;
      --v36;
      __sub_40B330_dword_44340C[n5] = ++n0x3F;
      if ( !--n5 )
        break;
    }
    else
    {
      --v36;
      ++n0x3F;
    }
  }
  while ( n0x3F < 0x3F );
  v106 = (int)(this_2 + 49728);
  this_1 = this_2;
  __sub_40B330_Src = 0;
  do
  {
    v37 = __sub_40B330_dword_44340C[__sub_40B330_Src];
    Src_6 = v37 - 1;
    if ( v37 - 1 >= *(&__sub_40B330_n24 + __sub_40B330_Src) )
    {
      v39 = (&::__sub_40B330_Src)[__sub_40B330_Src];
      Src_8 = *(&__sub_40B330_n24 + __sub_40B330_Src);
      v40 = 0;
      v41 = (int)&this_1[257 * v37 + 49471];
      do
      {
        Src_4 = Src_6;
        ++v40;
        n0x80_1 = 0;
        v43 = v41 - 1028 * v40;
        do
        {
          *(_DWORD *)&v39[8 * n0x80_1] += *(_DWORD *)(v43 + 8 * n0x80_1 + 1028);
          *(_DWORD *)&v39[8 * n0x80_1 + 4] += *(_DWORD *)(v43 + 8 * n0x80_1 + 1032);
          ++n0x80_1;
        }
        while ( n0x80_1 < 0x80 );
        Src_7 = Src_4;
        *((_DWORD *)v39 + 256) += *(_DWORD *)(v43 + 2052);
        Src_6 = Src_7 - 1;
      }
      while ( Src_6 >= Src_8 );
    }
    v45 = sub_411700((int)(&::__sub_40B330_Src)[__sub_40B330_Src], 257);
    Src_9 = __sub_40B330_Src;
    v102[__sub_40B330_Src] = v45;
    __sub_40B330_Src = Src_9 + 1;
  }
  while ( (unsigned int)(Src_9 + 1) < 6 );
  v48 = v106;
  while ( 2 )
  {
    v106 = v48;
    n5_1 = 0;
    v110 = 0;
    do
    {
      v50 = *(&__sub_40B330_n24 + n5_1);
      v111 = __sub_40B330_dword_44340C[n5_1];
      if ( v111 == v50 + 1 )
      {
        v52 = 0;
        goto LABEL_62;
      }
      sub_434980((char *)&__sub_40B330_Src,(&::__sub_40B330_Src)[n5_1],1028);
      sub_434980(v99,(&__sub_40B330_dword_442E74)[n5_1],1028);
      v52 = 0;
      v109 = v102[n5_1 + 1] + v102[n5_1];
      if ( v50 + 1 >= v111 )
        goto LABEL_62;
      v107 = 0;
      n5_2 = n5_1;
      v53 = 0;
      v108 = (int)&this_1[257 * v50 + 49728];
      while ( 1 )
      {
        ++v53;
        if ( !*(_DWORD *)(v113 + 4 * v50) )
          goto LABEL_58;
        n0x100 = 0;
        v67 = v108 + 1028 * v53;
        do
        {
          v68 = _mm_loadu_si128((const __m128i *)&v99[4 * n0x100]);
          v69 = _mm_loadu_si128((const __m128i *)&v100[n0x100 / 4]);
          si128 = _mm_load_si128((const __m128i *)&v97[n0x100 / 4]);
          *(__m128i *)(&__sub_40B330_Src + n0x100) = _mm_sub_epi32(
                                          _mm_load_si128((const __m128i *)(&__sub_40B330_Src + n0x100)),
                                          _mm_loadu_si128((const __m128i *)(v67 + 4 * n0x100 - 1028)));
          v71 = _mm_load_si128((const __m128i *)&v97[n0x100 / 4 + 1]);
          *(__m128i *)&v99[4 * n0x100] = _mm_add_epi32(v68, _mm_loadu_si128((const __m128i *)(v67 + 4 * n0x100 - 1028)));
          v72 = _mm_loadu_si128((const __m128i *)&v100[n0x100 / 4 + 1]);
          v97[n0x100 / 4] = _mm_sub_epi32(si128, _mm_loadu_si128((const __m128i *)(v67 + 4 * n0x100 - 1012)));
          v73 = _mm_load_si128((const __m128i *)&v97[n0x100 / 4 + 2]);
          v100[n0x100 / 4] = _mm_add_epi32(v69, _mm_loadu_si128((const __m128i *)(v67 + 4 * n0x100 - 1012)));
          v74 = _mm_loadu_si128((const __m128i *)&v100[n0x100 / 4 + 2]);
          v97[n0x100 / 4 + 1] = _mm_sub_epi32(v71, _mm_loadu_si128((const __m128i *)(v67 + 4 * n0x100 - 996)));
          v100[n0x100 / 4 + 1] = _mm_add_epi32(v72, _mm_loadu_si128((const __m128i *)(v67 + 4 * n0x100 - 996)));
          v97[n0x100 / 4 + 2] = _mm_sub_epi32(v73, _mm_loadu_si128((const __m128i *)(v67 + 4 * n0x100 - 980)));
          v100[n0x100 / 4 + 2] = _mm_add_epi32(v74, _mm_loadu_si128((const __m128i *)(v67 + 4 * n0x100 - 980)));
          n0x100 += 16;
        }
        while ( n0x100 < 0x100 );
        v98 -= *(_DWORD *)(v67 - 4);
        v101 += *(_DWORD *)(v67 - 4);
        v105 = sub_411700((int)&__sub_40B330_Src, 257);
        v104 = sub_411700((int)v99, 257);
        v103 = v105 + v104;
        if ( v105 + v104 > v109 + 4096 )
          break;
        if ( v105 + v104 < v109 )
        {
          sub_434980((&::__sub_40B330_Src)[n5_2],(char *)&__sub_40B330_Src,1028);
          sub_434980((&__sub_40B330_dword_442E74)[n5_2],v99,1028);
          n5_3 = n5_2;
          v77 = v104;
          v102[n5_2] = v105;
          v78 = v103;
          v102[n5_3 + 1] = v77;
          v109 = v78;
          v107 = 1;
          *(&__sub_40B330_n24 + n5_3) = ++v50;
          goto LABEL_59;
        }
LABEL_58:
        ++v50;
LABEL_59:
        if ( v50 + 1 >= __sub_40B330_dword_44340C[n5_2] )
        {
          v52 = v107;
          n5_1 = n5_2;
          goto LABEL_62;
        }
      }
      v52 = v107;
      n5_1 = n5_2;
LABEL_62:
      v110 |= v52;
      ++n5_1;
    }
    while ( n5_1 < 5 );
    v54 = v110;
    v48 = v106;
    v55 = v113;
    v56 = sub_40BBC0(0, (int)v102, v106, v46, v79, v84, v89, v113) | v54;
    v58 = sub_40BBC0(1, (int)v102, v48, v57, v80, v85, v90, v55) | v56;
    v60 = sub_40BBC0(2, (int)v102, v48, v59, v81, v86, v91, v55) | v58;
    v62 = sub_40BBC0(3, (int)v102, v48, v61, v82, v87, v92, v55) | v60;
    v64 = sub_40BBC0(4, (int)v102, v48, v63, v83, v88, v93, v55);
    v24 = __sub_40B330_dword_443388;
    if ( v64 | v62 )
    {
      if ( __sub_40B330_dword_443388 )
        goto LABEL_65;
      continue;
    }
    break;
  }
LABEL_28:
  if ( v24 )
  {
LABEL_65:
    v65 = 0;
    for ( n6 = 0; n6 < 6; ++n6 )
      v65 += v102[n6];
    __sub_40B330_n256_2[0] = v65;
  }
  else
  {
    *buf = 0;
    v25 = 0;
    n0x20 = 0;
    buf[1] = 1;
    v27 = 0;
    buf[2] = 2;
    buf[3] = 3;
    buf[4] = 4;
    buf[5] = 5;
    buf[6] = 6;
    buf[7] = 7;
    buf[8] = 8;
    buf[9] = 9;
    buf[10] = 10;
    buf[11] = 11;
    do
    {
      v28 = v25 + 12;
      buf[v27 + 75] = v25 + 12;
      v29 = *(&__sub_40B330_n24 + v25);
      if ( v29 == v27 + 63 )
      {
        ++v25;
        v29 = *(&__sub_40B330_n24 + v25);
        v28 = v25 + 12;
      }
      buf[v27 + 74] = v28;
      if ( v29 == v27 + 62 )
        ++v25;
      v27 -= 2;
      ++n0x20;
    }
    while ( n0x20 < 0x20 );
    v30 = (__sub_40B330_dword_443420 << 24) | (__sub_40B330_n7 << 18) | (__sub_40B330_n9 << 12) | __sub_40B330_n24 | (__sub_40B330_n14 << 6);
    if ( ::__sub_40B330_n8 < 30 )
    {
      *(_DWORD *)__sub_40B330_Buffer_1 = __sub_40B330_n256 | (2 * (v30 << ((31 - ::__sub_40B330_n8) & 31)));
      __sub_40B330_Buffer_1 = __sub_40B330_Buffer_0;
      n6 = v30 >> (::__sub_40B330_n8 & 31);
      __sub_40B330_Buffer_0 += 4;
      __sub_40B330_n256 = n6;
      __sub_40B330_n8 = ::__sub_40B330_n8 + 2;
    }
    else
    {
      n6 = v30 << (-(char)::__sub_40B330_n8 & 31);
      __sub_40B330_n8 = ::__sub_40B330_n8 - 30;
      __sub_40B330_n256 |= n6;
    }
    ::__sub_40B330_n8 = __sub_40B330_n8;
  }
  return n6;
}

#undef sub_40BBC0
#undef sub_411700
#undef sub_434980
