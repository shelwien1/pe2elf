// sub_40BEE0 @ 0x0040BEE0 — __usercall
// Extracted from BMF.c:9819-10572 by extract.py per incdec.md.

typedef int t_sub_40BEE0_Buffer_0;
static t_sub_40BEE0_Buffer_0& __sub_40BEE0_Buffer_0 = *(t_sub_40BEE0_Buffer_0*)0x00443378;
typedef int t_sub_40BEE0_Buffer_1;
static t_sub_40BEE0_Buffer_1& __sub_40BEE0_Buffer_1 = *(t_sub_40BEE0_Buffer_1*)0x00443374;
typedef int t_sub_40BEE0_buf_1;
static t_sub_40BEE0_buf_1& __sub_40BEE0_buf_1 = *(t_sub_40BEE0_buf_1*)0x00443430;
typedef int t_sub_40BEE0_dword_438AFC[0x10000];
static t_sub_40BEE0_dword_438AFC& __sub_40BEE0_dword_438AFC = *(t_sub_40BEE0_dword_438AFC*)0x00438AFC;
typedef int t_sub_40BEE0_dword_438B00[0x10000];
static t_sub_40BEE0_dword_438B00& __sub_40BEE0_dword_438B00 = *(t_sub_40BEE0_dword_438B00*)0x00438B00;
typedef int t_sub_40BEE0_dword_43949C[0x10000];
static t_sub_40BEE0_dword_43949C& __sub_40BEE0_dword_43949C = *(t_sub_40BEE0_dword_43949C*)0x0043949C;
typedef int t_sub_40BEE0_dword_4394A0[4];
static t_sub_40BEE0_dword_4394A0& __sub_40BEE0_dword_4394A0 = *(t_sub_40BEE0_dword_4394A0*)0x004394A0;
typedef int t_sub_40BEE0_dword_4394B0[12];
static t_sub_40BEE0_dword_4394B0& __sub_40BEE0_dword_4394B0 = *(t_sub_40BEE0_dword_4394B0*)0x004394B0;
typedef int t_sub_40BEE0_dword_4410BC[0x10000];
static t_sub_40BEE0_dword_4410BC& __sub_40BEE0_dword_4410BC = *(t_sub_40BEE0_dword_4410BC*)0x004410BC;
typedef int t_sub_40BEE0_dword_442DDC[0x10000];
static t_sub_40BEE0_dword_442DDC& __sub_40BEE0_dword_442DDC = *(t_sub_40BEE0_dword_442DDC*)0x00442DDC;
typedef int t_sub_40BEE0_dword_442E3C[0x10000];
static t_sub_40BEE0_dword_442E3C& __sub_40BEE0_dword_442E3C = *(t_sub_40BEE0_dword_442E3C*)0x00442E3C;
typedef int t_sub_40BEE0_dword_442E88;
static t_sub_40BEE0_dword_442E88& __sub_40BEE0_dword_442E88 = *(t_sub_40BEE0_dword_442E88*)0x00442E88;
typedef int t_sub_40BEE0_dword_442EE0[0x10000];
static t_sub_40BEE0_dword_442EE0& __sub_40BEE0_dword_442EE0 = *(t_sub_40BEE0_dword_442EE0*)0x00442EE0;
typedef int t_sub_40BEE0_dword_442EE4[262];
static t_sub_40BEE0_dword_442EE4& __sub_40BEE0_dword_442EE4 = *(t_sub_40BEE0_dword_442EE4*)0x00442EE4;
typedef int t_sub_40BEE0_dword_443428;
static t_sub_40BEE0_dword_443428& __sub_40BEE0_dword_443428 = *(t_sub_40BEE0_dword_443428*)0x00443428;
typedef int t_sub_40BEE0_dword_44342C;
static t_sub_40BEE0_dword_44342C& __sub_40BEE0_dword_44342C = *(t_sub_40BEE0_dword_44342C*)0x0044342C;
typedef int t_sub_40BEE0_n2;
static t_sub_40BEE0_n2& __sub_40BEE0_n2 = *(t_sub_40BEE0_n2*)0x00443360;
typedef int t_sub_40BEE0_n256;
static t_sub_40BEE0_n256& __sub_40BEE0_n256 = *(t_sub_40BEE0_n256*)0x0044336C;
typedef int t_sub_40BEE0_n8;
static t_sub_40BEE0_n8& __sub_40BEE0_n8 = *(t_sub_40BEE0_n8*)0x00443368;
typedef __int128 t_sub_40BEE0_xmmword_442EA0;
static t_sub_40BEE0_xmmword_442EA0& __sub_40BEE0_xmmword_442EA0 = *(t_sub_40BEE0_xmmword_442EA0*)0x00442EA0;
typedef __int128 t_sub_40BEE0_xmmword_442EB0;
static t_sub_40BEE0_xmmword_442EB0& __sub_40BEE0_xmmword_442EB0 = *(t_sub_40BEE0_xmmword_442EB0*)0x00442EB0;
typedef __int128 t_sub_40BEE0_xmmword_442EC0;
static t_sub_40BEE0_xmmword_442EC0& __sub_40BEE0_xmmword_442EC0 = *(t_sub_40BEE0_xmmword_442EC0*)0x00442EC0;
typedef __int128 t_sub_40BEE0_xmmword_442ED0;
static t_sub_40BEE0_xmmword_442ED0& __sub_40BEE0_xmmword_442ED0 = *(t_sub_40BEE0_xmmword_442ED0*)0x00442ED0;

#ifndef __PE_DECL___sub_411700
#define __PE_DECL___sub_411700
typedef int t_sub_411700(int a1, int n2);
static t_sub_411700& __sub_411700 = *(t_sub_411700*)0x00411700;
#endif
#define sub_411700 __sub_411700
#define sub_40CB70 __sub_40CB70
#define sub_40CC50 __sub_40CC50

PROBE_DECL(__sub_40BEE0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) int __sub_40BEE0(char a1)
{
  alignas(16) unsigned char __hexrays_frame[2544];   // original frame, ebp-0x9e0..ebp+0x0
  unsigned int &v101 = *(unsigned int *)(__hexrays_frame + 0);
  int &n4_2 = *(int *)(__hexrays_frame + 0);
  int &n4_3 = *(int *)(__hexrays_frame + 0);
  unsigned int &v104 = *(unsigned int *)(__hexrays_frame + 4);
  unsigned int &n0x15_1 = *(unsigned int *)(__hexrays_frame + 4);
  int &n256_1 = *(int *)(__hexrays_frame + 4);
  int &v107 = *(int *)(__hexrays_frame + 8);
  int &n4 = *(int *)(__hexrays_frame + 8);
  _BYTE (&k_2)[2288] = *(_BYTE (*)[2288])(__hexrays_frame + 12);
  _DWORD (&v110)[3] = *(_DWORD (*)[3])(__hexrays_frame + 2300);
  char &v111 = *(char *)(__hexrays_frame + 2314);
  int &v112 = *(int *)(__hexrays_frame + 2316);
  int (&v113)[4] = *(int (*)[4])(__hexrays_frame + 2320);
  __int128 &v114 = *(__int128 *)(__hexrays_frame + 2336);
  __int128 &v115 = *(__int128 *)(__hexrays_frame + 2352);
  __int128 &v116 = *(__int128 *)(__hexrays_frame + 2368);
  __int128 &v117 = *(__int128 *)(__hexrays_frame + 2384);
  int &v118 = *(int *)(__hexrays_frame + 2400);
  int &v119 = *(int *)(__hexrays_frame + 2404);
  int &v120 = *(int *)(__hexrays_frame + 2408);
  int &n11_1 = *(int *)(__hexrays_frame + 2412);
  int &n11_2 = *(int *)(__hexrays_frame + 2416);
  int &v123 = *(int *)(__hexrays_frame + 2420);
  unsigned int &v124 = *(unsigned int *)(__hexrays_frame + 2424);
  int &v125 = *(int *)(__hexrays_frame + 2428);
  _BYTE * &k_4 = *(_BYTE * *)(__hexrays_frame + 2432);
  int &v127 = *(int *)(__hexrays_frame + 2436);
  unsigned int &v128 = *(unsigned int *)(__hexrays_frame + 2440);
  int &v129 = *(int *)(__hexrays_frame + 2444);
  int &j_2 = *(int *)(__hexrays_frame + 2448);
  int &v131 = *(int *)(__hexrays_frame + 2452);
  int &v132 = *(int *)(__hexrays_frame + 2456);
  _DWORD * &v133 = *(_DWORD * *)(__hexrays_frame + 2460);
  int &v134 = *(int *)(__hexrays_frame + 2464);
  int &v135 = *(int *)(__hexrays_frame + 2468);
  int &n14_5 = *(int *)(__hexrays_frame + 2472);
  unsigned int &v137 = *(unsigned int *)(__hexrays_frame + 2476);
  int &v138 = *(int *)(__hexrays_frame + 2480);
  int &v139 = *(int *)(__hexrays_frame + 2484);
  int &v140 = *(int *)(__hexrays_frame + 2488);
  int &n14_2 = *(int *)(__hexrays_frame + 2492);
  _DWORD * &v142 = *(_DWORD * *)(__hexrays_frame + 2496);
  int &__sub_40BEE0_buf_1 = *(int *)(__hexrays_frame + 2500);
  _BYTE * &k_1 = *(_BYTE * *)(__hexrays_frame + 2504);
  PROBE_HIT(__sub_40BEE0);
  int v1; // eax
  unsigned int i; // ebx
  int v3; // edx
  int v4; // ecx
  bool v5; // zf
  char v6; // dl
  int n11; // esi
  int n11_3; // ebx
  char *buf; // edi
  _DWORD *v10; // edx
  int j_1; // esi
  _BYTE *k_3; // edx
  int v13; // ecx
  int n14_1; // eax
  int v15; // edx
  int n14; // ebx
  unsigned int v17; // esi
  int v18; // ebx
  int v19; // edx
  int v20; // esi
  _BYTE *k_6; // edi
  int v22; // ebx
  int v23; // edi
  int v24; // ebx
  _BYTE *k_7; // esi
  _BYTE *k_5; // esi
  char v27; // cl
  _BYTE *k_8; // ebx
  int n14_3; // edi
  int n14_4; // esi
  int v31; // ebx
  int v32; // edx
  int v33; // ebx
  int v34; // eax
  int v35; // eax
  int v36; // edx
  unsigned int v37; // ecx
  unsigned int v38; // eax
  int n0x15_2; // eax
  char v40; // cc
  unsigned int n0x15; // ecx
  unsigned int v42; // eax
  int v43; // ebx
  int v44; // ecx
  int v45; // ecx
  int v46; // ebx
  int v47; // edx
  int v48; // esi
  int v49; // ecx
  int v50; // eax
  char *v51; // edx
  int v52; // esi
  int v53; // eax
  int v54; // ebx
  int v55; // ebx
  int v56; // ecx
  int v57; // ebx
  int v58; // esi
  unsigned int v59; // edi
  int v60; // ecx
  int j; // edx
  int k_9; // eax
  int n11_4; // esi
  int n4_1; // edx
  int __sub_40BEE0_n256; // ebx
  int v66; // ecx
  unsigned int v67; // esi
  int buf_2; // edx
  unsigned int v69; // edi
  int v70; // ecx
  int v71; // eax
  int v72; // eax
  int v73; // ecx
  int v74; // esi
  int v75; // ecx
  int v76; // ecx
  char *v77; // esi
  int buf_3; // eax
  int v79; // ebx
  int v80; // edx
  int v81; // edx
  int v82; // esi
  int buf_4; // eax
  unsigned int v84; // edi
  int v85; // edi
  int __sub_40BEE0_n8; // edx
  unsigned int v87; // ebx
  unsigned int v88; // edi
  int v89; // edi
  _BYTE *k_10; // eax
  unsigned int v91; // esi
  int v92; // esi
  int n8_1; // edx
  int n256_2; // ebx
  int k; // esi
  int v96; // edi
  int k_11; // ecx
  int v98; // edi
  int n8_2; // edi
  int v100; // edi

  v1 = 0;
  for ( i = 0; i < 7; ++i )
  {
    v3 = v1 + 1;
    v4 = 2 * i + 1;
    if ( 2 * i != __sub_40BEE0_dword_4394A0[v1] )
      v3 = v1;
    v5 = v4 == __sub_40BEE0_dword_4394A0[v3];
    *((_BYTE *)v110 + 2 * i) = v3;
    v1 = v3 + v5;
    *((_BYTE *)v110 + v4) = v3 + v5;
  }
  v6 = v3 + v5 + 1;
  if ( __sub_40BEE0_dword_4394A0[v1] == 14 )
    LOBYTE(v1) = v6;
  n11 = 11;
  v111 = v1;
  k_1 = k_2;
  if ( __sub_40BEE0_n2 != 2 )
    n11 = 0;
  v101 = 0;
  n11_1 = n11;
  n11_2 = n11;
  v120 = -(int)k_2;
  v134 = 0;
  v124 = 4 * n11;
  n11_3 = n11;
  v123 = 0;
  while ( 1 )
  {
    ++n11_3;
    buf = (char *)__sub_40BEE0_dword_442DDC[v123 + 1 + v124 / 4];
    v10 = (_DWORD *)__sub_40BEE0_dword_442E3C[v123 + 1 + v124 / 4];
    j_1 = __sub_40BEE0_dword_438AFC[++v123 + v124 / 4];
    v133 = v10;
    sub_40CC50(j_1, v10, buf, a1);
    if ( n11_3 == 19 )
      break;
    *(_OWORD *)v113 = 0;
    v114 = 0;
    v115 = 0;
    v116 = 0;
    v117 = 0;
    v118 = _mm_cvtsi128_si32((__m128i)0LL);
    v125 = v120;
    k_3 = k_1;
    v131 = 0;
    if ( j_1 > 0 )
    {
      v132 = 0;
      v112 = 0;
      v13 = -1;
      v129 = __sub_40BEE0_dword_4410BC[v123 + v124 / 4];
      n14_1 = 0;
      k_4 = k_1;
      v15 = 0;
      j_2 = j_1;
      __sub_40BEE0_buf_1 = (int)buf;
      n11_1 = n11_3;
      do
      {
        n14_5 = n14_1;
        n14 = j_2 - v15;
        if ( j_2 - v15 >= 14 )
          n14 = 14;
        v140 = v15 + v129;
        if ( n14_1 < n14 )
        {
          v127 = 0;
          v138 = n14_1 + v15 + v129;
          v137 = n14 - n14_1;
          v17 = 0;
          v132 = v15;
          v18 = __sub_40BEE0_buf_1 + 4 * (v15 + n14_1);
          do
          {
            v19 = (*(_BYTE *)(v17 + v138) - *(_BYTE *)(v18 + 4 * v17 + 2)) & 0xF;
            if ( v19 != v13 )
              break;
            n14_1 = v17 + n14_5 + 1;
            ++v17;
          }
          while ( v17 < v137 );
          v134 = v19;
          v15 = v132;
        }
        if ( n14_1 <= 1 )
        {
          if ( n14_1 == 1 )
          {
            k_5 = k_4;
            --v125;
            *k_4 = v13;
            ++v113[(unsigned __int8)v13];
            k_4 = k_5 + 1;
          }
        }
        else
        {
          v20 = *((unsigned __int8 *)v110 + n14_1);
          k_6 = k_4;
          --v125;
          v22 = (unsigned __int8)(v20 + 16);
          ++v113[v22];
          *k_6 = v22;
          k_4 = k_6 + 1;
          v23 = __sub_40BEE0_dword_4394B0[v20];
          if ( v23 )
          {
            v131 -= v23;
            v24 = n14_1 - __sub_40BEE0_dword_43949C[v20];
            k_7 = k_4;
            *k_4 = v24;
            --v125;
            k_4 = k_7 + 1;
          }
        }
        if ( v13 != v134 )
        {
          v27 = v134;
          k_8 = k_4;
          ++v113[v134];
          ++n14_1;
          --v125;
          *k_8 = v27;
          k_4 = k_8 + 1;
        }
        v132 = v15;
        n14_2 = n14_1;
        n14_3 = n14_1;
        n14_4 = 0;
        v142 = &v133[v15];
        v31 = __sub_40BEE0_buf_1 + 4 * v15;
        v32 = v131;
        v139 = v31;
        v33 = 0;
        do
        {
          v34 = v142[n14_4] * (*(unsigned __int8 *)(n14_4 + v140) - *(unsigned __int8 *)(v139 + 4 * n14_4 + 2));
          ++n14_4;
          v32 += v34;
          n14_1 = v33 + n14_3 - 1;
          --v33;
        }
        while ( n14_4 < n14_2 );
        v13 = v134;
        v131 = v32;
        v15 = n14_4 + v132;
      }
      while ( n14_4 + v132 < j_2 );
      k_3 = k_4;
      j_1 = j_2;
      buf = (char *)__sub_40BEE0_buf_1;
      n11_3 = n11_1;
    }
    k_4 = k_3;
    v35 = sub_411700((int)v113, 21);
    if ( v131 - v35 - ((int)&k_4[v120 + 1] >> 1) <= 0 )
    {
      v40 = j_1 <= 0;
      if ( j_1 <= 0 )
        goto LABEL_49;
      v60 = __sub_40BEE0_dword_4410BC[v123 + v124 / 4];
      for ( j = 0; j < j_1; buf[4 * j - 2] = *(_BYTE *)(j + v60 - 1) )
        ++j;
      goto LABEL_48;
    }
    k_1 = k_4;
    v36 = __sub_40BEE0_dword_442E88;
    v120 = v125;
    v101 |= 1 << (n11_3 + 31);
    v37 = __sub_40BEE0_dword_442E88 & 0xF;
    if ( (__sub_40BEE0_dword_442E88 & 0xF) != 0 )
    {
      if ( (__sub_40BEE0_dword_442E88 & 3) != 0 )
      {
        n0x15_2 = 0;
        n0x15_1 = 0;
        goto LABEL_44;
      }
      n11_1 = n11_3;
      v37 = (16 - v37) >> 2;
      v38 = 0;
      do
      {
        *(_DWORD *)(v36 + 4 * v38) += v113[v38];
        ++v38;
      }
      while ( v38 < v37 );
      n11_3 = n11_1;
    }
    v104 = 21 - ((1 - (_BYTE)v37) & 3);
    if ( ((unsigned __int8)&v113[v37] & 0xF) != 0 )
    {
      n0x15_2 = 21 - ((1 - (_BYTE)v37) & 3);
      do
      {
        *(__m128i *)(v36 + 4 * v37) = _mm_add_epi32(
                                        _mm_loadu_si128((const __m128i *)&v113[v37]),
                                        *(__m128i *)(v36 + 4 * v37));
        v37 += 4;
      }
      while ( v37 < v104 );
    }
    else
    {
      n0x15_2 = 21 - ((1 - (_BYTE)v37) & 3);
      do
      {
        *(__m128i *)(v36 + 4 * v37) = _mm_add_epi32(
                                        _mm_load_si128((const __m128i *)(v36 + 4 * v37)),
                                        *(__m128i *)&v113[v37]);
        v37 += 4;
      }
      while ( v37 < v104 );
    }
    n0x15_1 = n0x15_2;
LABEL_44:
    if ( n0x15_1 < 0x15 )
    {
      n0x15 = n0x15_2;
      do
      {
        *(_DWORD *)(v36 + 4 * n0x15) += v113[n0x15];
        ++n0x15;
      }
      while ( n0x15 < 0x15 );
LABEL_48:
      v40 = j_1 <= 0;
      goto LABEL_49;
    }
    v40 = j_1 <= 0;
LABEL_49:
    ::__sub_40BEE0_buf_1 = (int)buf;
    __sub_40BEE0_xmmword_442EA0 = -1;
    __sub_40BEE0_xmmword_442EB0 = -1;
    __sub_40BEE0_xmmword_442EC0 = -1;
    __sub_40BEE0_xmmword_442ED0 = -1;
    if ( !v40 )
    {
      if ( j_1 / 2 )
      {
        j_2 = j_1;
        n11_1 = n11_3;
        v42 = 0;
        do
        {
          v43 = 2 * v42;
          v44 = (unsigned __int8)buf[8 * v42 + 2];
          __sub_40BEE0_dword_442EE0[v43] = *((_DWORD *)&__sub_40BEE0_xmmword_442EA0 + v44);
          *((_DWORD *)&__sub_40BEE0_xmmword_442EA0 + v44) = 2 * v42;
          v45 = (unsigned __int8)buf[8 * v42 + 6];
          __sub_40BEE0_dword_442EE4[v43] = *((_DWORD *)&__sub_40BEE0_xmmword_442EA0 + v45);
          v46 = 2 * v42++ + 1;
          *((_DWORD *)&__sub_40BEE0_xmmword_442EA0 + v45) = v46;
        }
        while ( v42 < j_1 / 2 );
        j_1 = j_2;
        n11_3 = n11_1;
        v47 = 2 * v42 + 1;
      }
      else
      {
        v47 = 1;
      }
      if ( j_1 > (unsigned int)(v47 - 1) )
      {
        v48 = (unsigned __int8)buf[4 * v47 - 2];
        *((_DWORD *)&__sub_40BEE0_xmmword_442ED0 + v47 + 3) = *((_DWORD *)&__sub_40BEE0_xmmword_442EA0 + v48);
        *((_DWORD *)&__sub_40BEE0_xmmword_442EA0 + v48) = v47 - 1;
      }
    }
    if ( SDWORD1(__sub_40BEE0_xmmword_442EA0) < 0 )
    {
      v49 = 1;
      do
        v50 = v49++;
      while ( *((int *)&__sub_40BEE0_xmmword_442EA0 + v50 + 1) < 0 );
    }
    else
    {
      v49 = 1;
    }
    v51 = (char *)(4 * v49 + 4468384);
    v52 = 4 * v49;
    v53 = (1 << v49) - 1;
    if ( v53 < 0 )
    {
      __sub_40BEE0_dword_443428 = 0;
    }
    else
    {
      __sub_40BEE0_dword_44342C = 4 * v49 + 4468384;
      v119 = 4 * v49;
      v135 = v49;
      n11_1 = n11_3;
      do
      {
        v54 = *(_DWORD *)v51;
        *(_WORD *)&buf[4 * v54] = v53 << (((unsigned int)(v51 - (char *)&__sub_40BEE0_xmmword_442EA0) >> 2) - v135);
        v55 = __sub_40BEE0_dword_442EE0[v54];
        *(_DWORD *)v51 = v55;
        if ( v55 < 0 )
        {
          v56 = v53;
          v57 = --v53;
          if ( v53 >= 0 )
          {
            v128 = v56;
            __sub_40BEE0_buf_1 = (int)buf;
            v58 = 0;
            v59 = 0;
            do
            {
              __sub_40BEE0_dword_443428 = (v57 - v59) << (((unsigned int)(__sub_40BEE0_dword_44342C - (_DWORD)&__sub_40BEE0_xmmword_442EA0) >> 2) - v135);
              sub_40CB70();
              v53 = v58 + v57 - 1;
              --v58;
              ++v59;
            }
            while ( v59 < v128 );
            buf = (char *)__sub_40BEE0_buf_1;
            v51 = (char *)__sub_40BEE0_dword_44342C;
          }
        }
        --v53;
      }
      while ( v53 >= 0 );
      v52 = v119;
      n11_3 = n11_1;
      __sub_40BEE0_dword_443428 = 0;
    }
    n11_2 = n11_3;
    __sub_40BEE0_dword_44342C = (int)&v51[-v52];
  }
  k_9 = (int)k_1;
  n11_4 = n11_2;
  __sub_40BEE0_buf_1 = (int)buf;
  if ( ::__sub_40BEE0_n8 < 18 )
  {
    *(_DWORD *)__sub_40BEE0_Buffer_1 = ::__sub_40BEE0_n256 | (2 * (v101 << (31 - ::__sub_40BEE0_n8)));
    __sub_40BEE0_Buffer_1 = __sub_40BEE0_Buffer_0;
    __sub_40BEE0_Buffer_0 += 4;
    __sub_40BEE0_n256 = v101 >> ::__sub_40BEE0_n8;
    n4_1 = ::__sub_40BEE0_n8 + 14;
    ::__sub_40BEE0_n8 += 14;
  }
  else
  {
    n4_1 = ::__sub_40BEE0_n8 - 18;
    __sub_40BEE0_n256 = ::__sub_40BEE0_n256 | (v101 << (-(char)::__sub_40BEE0_n8 & 31));
    ::__sub_40BEE0_n8 -= 18;
  }
  if ( v101 )
  {
    v66 = __sub_40BEE0_dword_438B00[n11_4];
    __sub_40BEE0_xmmword_442EA0 = -1;
    __sub_40BEE0_xmmword_442EB0 = -1;
    __sub_40BEE0_xmmword_442EC0 = -1;
    __sub_40BEE0_xmmword_442ED0 = -1;
    ::__sub_40BEE0_buf_1 = __sub_40BEE0_buf_1;
    if ( v66 > 0 )
    {
      v67 = v66 / 2;
      if ( v66 / 2 )
      {
        k_1 = (_BYTE *)k_9;
        n4_2 = n4_1;
        buf_2 = __sub_40BEE0_buf_1;
        v107 = v66;
        v69 = 0;
        do
        {
          v70 = 2 * v69;
          v71 = *(unsigned __int8 *)(buf_2 + 8 * v69 + 2);
          __sub_40BEE0_dword_442EE0[v70] = *((_DWORD *)&__sub_40BEE0_xmmword_442EA0 + v71);
          *((_DWORD *)&__sub_40BEE0_xmmword_442EA0 + v71) = 2 * v69;
          v72 = *(unsigned __int8 *)(buf_2 + 8 * v69 + 6);
          __sub_40BEE0_dword_442EE4[v70] = *((_DWORD *)&__sub_40BEE0_xmmword_442EA0 + v72);
          v73 = 2 * v69++ + 1;
          *((_DWORD *)&__sub_40BEE0_xmmword_442EA0 + v72) = v73;
        }
        while ( v69 < v67 );
        k_9 = (int)k_1;
        v66 = v107;
        __sub_40BEE0_buf_1 = buf_2;
        v74 = 2 * v69 + 1;
        n4_1 = n4_2;
      }
      else
      {
        v74 = 1;
      }
      if ( v66 > (unsigned int)(v74 - 1) )
      {
        k_1 = (_BYTE *)k_9;
        v75 = *(unsigned __int8 *)(__sub_40BEE0_buf_1 + 4 * v74 - 2);
        *((_DWORD *)&__sub_40BEE0_xmmword_442ED0 + v74 + 3) = *((_DWORD *)&__sub_40BEE0_xmmword_442EA0 + v75);
        k_9 = (int)k_1;
        *((_DWORD *)&__sub_40BEE0_xmmword_442EA0 + v75) = v74 - 1;
      }
    }
    v76 = 1;
    if ( SDWORD1(__sub_40BEE0_xmmword_442EA0) < 0 )
    {
      do
        ++v76;
      while ( *((int *)&__sub_40BEE0_xmmword_442EA0 + v76) < 0 );
      n4 = 4 * v76;
    }
    else
    {
      n4 = 4;
    }
    v77 = (char *)&__sub_40BEE0_xmmword_442EA0 + n4;
    if ( (1 << v76) - 1 < 0 )
    {
      __sub_40BEE0_dword_443428 = 0;
    }
    else
    {
      ::__sub_40BEE0_n256 = __sub_40BEE0_n256;
      __sub_40BEE0_dword_44342C = (int)&__sub_40BEE0_xmmword_442EA0 + n4;
      k_1 = (_BYTE *)k_9;
      buf_3 = __sub_40BEE0_buf_1;
      n4_3 = n4_1;
      n256_1 = __sub_40BEE0_n256;
      v79 = (1 << v76) - 1;
      v110[0] = v76;
      do
      {
        v80 = *(_DWORD *)v77;
        *(_WORD *)(buf_3 + 4 * v80) = v79 << (((unsigned int)(v77 - (char *)&__sub_40BEE0_xmmword_442EA0) >> 2) - LOBYTE(v110[0]));
        v81 = __sub_40BEE0_dword_442EE0[v80];
        *(_DWORD *)v77 = v81;
        if ( v81 < 0 && --v79 >= 0 )
        {
          v100 = v110[0];
          __sub_40BEE0_buf_1 = buf_3;
          do
          {
            __sub_40BEE0_dword_443428 = v79 << (((unsigned int)(__sub_40BEE0_dword_44342C - (_DWORD)&__sub_40BEE0_xmmword_442EA0) >> 2) - v100);
            sub_40CB70();
            --v79;
          }
          while ( v79 >= 0 );
          buf_3 = __sub_40BEE0_buf_1;
          v77 = (char *)__sub_40BEE0_dword_44342C;
          v110[0] = v100;
        }
        --v79;
      }
      while ( v79 >= 0 );
      n4_1 = n4_3;
      __sub_40BEE0_n256 = n256_1;
      __sub_40BEE0_dword_443428 = 0;
      __sub_40BEE0_buf_1 = buf_3;
      k_9 = (int)k_1;
    }
    __sub_40BEE0_dword_44342C = (int)&v77[-n4];
    v82 = 0;
    k_1 = (_BYTE *)k_9;
    buf_4 = __sub_40BEE0_buf_1;
    while ( 1 )
    {
      v84 = *(unsigned __int8 *)(buf_4 + 8 * v82 + 2);
      if ( n4_1 < 4 )
      {
        *(_DWORD *)__sub_40BEE0_Buffer_1 = (2 * (v84 << (31 - n4_1))) | __sub_40BEE0_n256;
        __sub_40BEE0_Buffer_1 = __sub_40BEE0_Buffer_0;
        __sub_40BEE0_Buffer_0 += 4;
        v87 = v84 >> ::__sub_40BEE0_n8;
        __sub_40BEE0_n8 = ::__sub_40BEE0_n8 + 28;
      }
      else
      {
        v85 = v84 << (-(char)n4_1 & 31);
        __sub_40BEE0_n8 = n4_1 - 4;
        v87 = v85 | __sub_40BEE0_n256;
      }
      v88 = *(unsigned __int8 *)(buf_4 + 8 * v82 + 6);
      if ( __sub_40BEE0_n8 < 4 )
      {
        ::__sub_40BEE0_n8 = __sub_40BEE0_n8;
        *(_DWORD *)__sub_40BEE0_Buffer_1 = (2 * (v88 << (31 - __sub_40BEE0_n8))) | v87;
        __sub_40BEE0_Buffer_1 = __sub_40BEE0_Buffer_0;
        __sub_40BEE0_Buffer_0 += 4;
        __sub_40BEE0_n256 = v88 >> ::__sub_40BEE0_n8;
        n4_1 = ::__sub_40BEE0_n8 + 28;
      }
      else
      {
        v89 = v88 << (-(char)__sub_40BEE0_n8 & 31);
        n4_1 = __sub_40BEE0_n8 - 4;
        __sub_40BEE0_n256 = v89 | v87;
      }
      if ( (unsigned int)++v82 >= 0xA )
        break;
      ::__sub_40BEE0_n8 = n4_1;
    }
    __sub_40BEE0_buf_1 = buf_4;
    k_10 = k_1;
    v91 = *(unsigned __int8 *)(__sub_40BEE0_buf_1 + 82);
    if ( n4_1 < 4 )
    {
      ::__sub_40BEE0_n8 = n4_1;
      *(_DWORD *)__sub_40BEE0_Buffer_1 = (2 * (v91 << (31 - n4_1))) | __sub_40BEE0_n256;
      __sub_40BEE0_Buffer_1 = __sub_40BEE0_Buffer_0;
      __sub_40BEE0_Buffer_0 += 4;
      n256_2 = v91 >> ::__sub_40BEE0_n8;
      n8_1 = ::__sub_40BEE0_n8 + 28;
      ::__sub_40BEE0_n8 += 28;
      ::__sub_40BEE0_n256 = n256_2;
    }
    else
    {
      v92 = v91 << (-(char)n4_1 & 31);
      n8_1 = n4_1 - 4;
      n256_2 = v92 | __sub_40BEE0_n256;
      ::__sub_40BEE0_n256 = n256_2;
      ::__sub_40BEE0_n8 = n8_1;
    }
    k_9 = k_10 - k_2;
    if ( k_9 > 0 )
    {
      k_1 = (_BYTE *)k_9;
      for ( k = 0; k < (int)k_1; ++k )
      {
        v96 = (unsigned __int8)k_2[k];
        k_11 = *(_DWORD *)(__sub_40BEE0_buf_1 + 4 * v96);
        k_9 = (unsigned __int16)k_11;
        if ( n8_1 < BYTE2(k_11) )
        {
          *(_DWORD *)__sub_40BEE0_Buffer_1 = (2 * ((unsigned __int16)k_11 << (31 - n8_1))) | n256_2;
          __sub_40BEE0_Buffer_1 = __sub_40BEE0_Buffer_0;
          __sub_40BEE0_Buffer_0 += 4;
          n256_2 = (unsigned __int16)k_11 >> ::__sub_40BEE0_n8;
          n8_1 = ::__sub_40BEE0_n8 - BYTE2(k_11) + 32;
        }
        else
        {
          LOBYTE(k_11) = n8_1;
          n8_1 -= BYTE2(k_11);
          k_9 <<= -(char)k_11;
          n256_2 |= k_9;
        }
        v40 = (v96 - 16 < 0) ^ __OFADD__(-16, v96);
        v98 = v96 - 16;
        if ( !v40 && (n8_2 = __sub_40BEE0_dword_4394B0[v98]) != 0 )
        {
          k_9 = (unsigned __int8)k_2[++k];
          if ( n8_1 < n8_2 )
          {
            ::__sub_40BEE0_n8 = n8_1;
            *(_DWORD *)__sub_40BEE0_Buffer_1 = (2 * (k_9 << (31 - n8_1))) | n256_2;
            __sub_40BEE0_Buffer_1 = __sub_40BEE0_Buffer_0;
            __sub_40BEE0_Buffer_0 += 4;
            n256_2 = (unsigned int)k_9 >> ::__sub_40BEE0_n8;
            ::__sub_40BEE0_n256 = (unsigned int)k_9 >> ::__sub_40BEE0_n8;
            n8_1 = ::__sub_40BEE0_n8 - n8_2 + 32;
          }
          else
          {
            k_9 <<= -(char)n8_1;
            n8_1 -= n8_2;
            n256_2 |= k_9;
            ::__sub_40BEE0_n256 = n256_2;
          }
          ::__sub_40BEE0_n8 = n8_1;
        }
        else
        {
          ::__sub_40BEE0_n8 = n8_1;
          ::__sub_40BEE0_n256 = n256_2;
        }
      }
    }
  }
  else
  {
    ::__sub_40BEE0_n256 = __sub_40BEE0_n256;
  }
  return k_9;
}

// __usercall thunk for sub_40BEE0 @ 0x0040BEE0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_40BEE0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $28, %esp\n"
    "fnstsw %ax\n"
    "mov %eax, 12(%esp)\n"
    "push 12(%esp)\n"
    "call __sub_40BEE0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef sub_40CB70
#undef sub_40CC50
#undef sub_411700
