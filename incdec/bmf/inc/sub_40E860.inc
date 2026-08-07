// sub_40E860 @ 0x0040E860 — __userpurge
// Extracted from BMF.cpp:12539-13252 by extract.py per incdec.md.

typedef int t_sub_40E860_buf[0x10000];
static t_sub_40E860_buf& __sub_40E860_buf = *(t_sub_40E860_buf*)0x00443380;
typedef int t_sub_40E860_n2;
static t_sub_40E860_n2& __sub_40E860_n2 = *(t_sub_40E860_n2*)0x00443360;
typedef int t_sub_40E860_n256_0[0x10000];
static t_sub_40E860_n256_0& __sub_40E860_n256_0 = *(t_sub_40E860_n256_0*)0x00443398;
typedef __int128 t_sub_40E860_xmmword_439540;
static t_sub_40E860_xmmword_439540& __sub_40E860_xmmword_439540 = *(t_sub_40E860_xmmword_439540*)0x00439540;
typedef __int128 t_sub_40E860_xmmword_439550;
static t_sub_40E860_xmmword_439550& __sub_40E860_xmmword_439550 = *(t_sub_40E860_xmmword_439550*)0x00439550;
typedef __int128 t_sub_40E860_xmmword_439560;
static t_sub_40E860_xmmword_439560& __sub_40E860_xmmword_439560 = *(t_sub_40E860_xmmword_439560*)0x00439560;
typedef __int128 t_sub_40E860_xmmword_439570;
static t_sub_40E860_xmmword_439570& __sub_40E860_xmmword_439570 = *(t_sub_40E860_xmmword_439570*)0x00439570;
typedef __int128 t_sub_40E860_xmmword_439580;
static t_sub_40E860_xmmword_439580& __sub_40E860_xmmword_439580 = *(t_sub_40E860_xmmword_439580*)0x00439580;

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980

PROBE_DECL(__sub_40E860)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) char * __sub_40E860(int Blocka, char a2, char *a3, int a4, int a5, _BYTE *a6)
{
  alignas(16) unsigned char __hexrays_frame[896];   // original frame, ebp-0x370..ebp+0x0
  int &n128_1 = *(int *)(__hexrays_frame + 0);
  int &v143 = *(int *)(__hexrays_frame + 0);
  char &v144 = *(char *)(__hexrays_frame + 4);
  int &v145 = *(int *)(__hexrays_frame + 4);
  unsigned int &v146 = *(unsigned int *)(__hexrays_frame + 8);
  int &v147 = *(int *)(__hexrays_frame + 8);
  int &v148 = *(int *)(__hexrays_frame + 8);
  int &n128_12 = *(int *)(__hexrays_frame + 12);
  int &v150 = *(int *)(__hexrays_frame + 12);
  _BYTE (&v151)[512] = *(_BYTE (*)[512])(__hexrays_frame + 16);
  _BYTE * &v152 = *(_BYTE * *)(__hexrays_frame + 528);
  _BYTE * &v153 = *(_BYTE * *)(__hexrays_frame + 532);
  unsigned int &v154 = *(unsigned int *)(__hexrays_frame + 536);
  int &v155 = *(int *)(__hexrays_frame + 540);
  int &n128_10 = *(int *)(__hexrays_frame + 544);
  int &n128_3 = *(int *)(__hexrays_frame + 548);
  int &v158 = *(int *)(__hexrays_frame + 552);
  int &v159 = *(int *)(__hexrays_frame + 556);
  _BYTE (&v160)[255] = *(_BYTE (*)[255])(__hexrays_frame + 560);
  char &v161 = *(char *)(__hexrays_frame + 815);
  int &Blocka_2 = *(int *)(__hexrays_frame + 816);
  _BYTE * &v163 = *(_BYTE * *)(__hexrays_frame + 820);
  char * &v164 = *(char * *)(__hexrays_frame + 824);
  int &v165 = *(int *)(__hexrays_frame + 828);
  unsigned __int8 * &v166 = *(unsigned __int8 * *)(__hexrays_frame + 832);
  int &v167 = *(int *)(__hexrays_frame + 836);
  _DWORD * &v168 = *(_DWORD * *)(__hexrays_frame + 840);
  int &v169 = *(int *)(__hexrays_frame + 844);
  int &v170 = *(int *)(__hexrays_frame + 848);
  int &v171 = *(int *)(__hexrays_frame + 852);
  int &v172 = *(int *)(__hexrays_frame + 856);
  int &v173 = *(int *)(__hexrays_frame + 860);
  int &v174 = *(int *)(__hexrays_frame + 864);
  PROBE_HIT(__sub_40E860);
  int Blocka_1; // ebx
  int n256; // edi
  int n128_2; // esi
  __m128i si128; // xmm3
  __m128i v10; // xmm2
  __m128i v11; // xmm1
  __m128i v12; // xmm0
  unsigned int n0x70; // eax
  __m128i v14; // xmm4
  __m128i v15; // xmm5
  unsigned int i; // ebx
  int n128_4; // edx
  int v18; // eax
  char v19; // bl
  char v20; // cl
  char v21; // bl
  int __sub_40E860_n2; // eax
  __m128i v23; // xmm1
  __m128i v24; // xmm0
  unsigned int j; // eax
  __m128i v26; // xmm0
  __m128i v27; // xmm0
  __m128i v28; // xmm0
  __m128i v29; // xmm0
  __m128i v30; // xmm0
  __m128i v31; // xmm0
  __m128i v32; // xmm0
  int n256_1; // eax
  int v34; // ecx
  char v35; // dl
  char v36; // al
  unsigned int v37; // eax
  int v38; // esi
  int n128; // ecx
  int v40; // edx
  int v41; // edx
  unsigned int v42; // eax
  int v43; // esi
  int n128_11; // edi
  int n128_8; // ecx
  int n128_9; // edi
  bool v47; // zf
  int v48; // esi
  int n128_7; // edi
  int v50; // edx
  unsigned int k; // ecx
  int n128_6; // edi
  int n128_5; // ebx
  char v54; // al
  unsigned int m; // eax
  char v56; // al
  char *v57; // ecx
  _BYTE *v58; // esi
  char v59; // al
  char v60; // al
  int n16; // edx
  int v62; // edx
  int v63; // eax
  _BYTE *v64; // eax
  int v65; // edx
  int v66; // ecx
  char *result; // eax
  _BYTE *v68; // esi
  char v69; // dl
  char v70; // dl
  int n16_1; // edi
  char v72; // al
  char *v73; // ecx
  int v74; // eax
  char v75; // dl
  int v76; // edx
  _DWORD *v77; // edi
  int v78; // edi
  int v79; // edx
  unsigned __int8 *v80; // edx
  int v81; // eax
  int v82; // ecx
  int v83; // eax
  int v84; // edi
  unsigned __int8 *v85; // ebx
  int v86; // esi
  int v87; // esi
  int v88; // edi
  int v89; // eax
  _DWORD *v90; // ebx
  int v91; // ecx
  int v92; // edi
  int v93; // ecx
  int v94; // edi
  int v95; // esi
  int v96; // ecx
  int v97; // eax
  int v98; // esi
  _DWORD *v99; // edi
  int v100; // eax
  int v101; // ecx
  int v102; // ecx
  int v103; // esi
  int v104; // ebx
  int v105; // eax
  int v106; // edx
  int v107; // esi
  int v108; // eax
  int v109; // esi
  int v110; // eax
  int v111; // eax
  int v112; // esi
  int v113; // edx
  int v114; // eax
  int v115; // edx
  int v116; // ecx
  int v117; // eax
  int v118; // esi
  int v119; // esi
  char v120; // di
  char v121; // cl
  char v122; // al
  int n16_2; // edx
  unsigned __int8 *v124; // edi
  int v125; // edx
  int v126; // esi
  int v127; // eax
  unsigned __int8 *v128; // ecx
  int v129; // esi
  int v130; // ecx
  int v131; // eax
  int n6; // esi
  _BYTE *v133; // edi
  int v134; // edx
  char v135; // al
  int v136; // edi
  int v137; // esi
  int v138; // ecx
  int v139; // esi
  int v140; // esi
  char *v141; // ecx

  Blocka_1 = Blocka;
  n256 = __sub_40E860_n256_0[0];
  n128_2 = 2 * __sub_40E860_n256_0[0] + 1;
  if ( ::__sub_40E860_n2 )
  {
    si128 = _mm_load_si128((const __m128i *)&__sub_40E860_xmmword_439560);
    v10 = _mm_load_si128((const __m128i *)&__sub_40E860_xmmword_439540);
    v11 = _mm_load_si128((const __m128i *)&__sub_40E860_xmmword_439570);
    v12 = _mm_load_si128((const __m128i *)&__sub_40E860_xmmword_439580);
    n0x70 = 0;
    v160[0] = 0;
    v161 = 0x80;
    do
    {
      v14 = v11;
      v15 = v11;
      v11 = _mm_add_epi8(v11, si128);
      *(__m128i *)&v160[2 * n0x70 + 1] = _mm_unpacklo_epi8(v14, v12);
      *(__m128i *)&v160[2 * n0x70 + 17] = _mm_unpackhi_epi8(v15, v12);
      v12 = _mm_add_epi8(v12, v10);
      n0x70 += 16;
    }
    while ( n0x70 < 0x70 );
    Blocka_2 = Blocka;
    for ( i = 0; i < 7; ++i )
    {
      v160[4 * i + 225] = -2 * i - 113;
      v160[4 * i + 226] = 2 * i + 113;
      v160[4 * i + 227] = -2 * i - 114;
      v160[4 * i + 228] = 2 * i + 114;
    }
    Blocka_1 = Blocka_2;
    v160[253] = -127;
    v160[254] = 127;
    if ( !n256 || (n128_4 = n128_2, n128_2 >= 128) )
    {
LABEL_21:
      v151[0] = 0;
      v151[128] = -1;
      if ( n256 <= 0 )
      {
        n128 = 1;
      }
      else
      {
        if ( n256 / 2 )
        {
          n128_3 = n128_2;
          Blocka_2 = Blocka_1;
          v37 = 0;
          v38 = 0;
          do
          {
            v151[v38 + 255] = 0;
            v151[2 * v37 + 1] = 0;
            v151[v38 + 254] = 0;
            n128 = 2 * v37 + 3;
            v38 -= 2;
            v151[2 * v37++ + 2] = 0;
          }
          while ( v37 < n256 / 2 );
          n128_2 = n128_3;
          Blocka_1 = Blocka_2;
          v40 = 2 * v37 + 1;
        }
        else
        {
          n128 = 1;
          v40 = 1;
        }
        if ( n256 > (unsigned int)(v40 - 1) )
        {
          v151[-v40 + 256] = 0;
          n128 = v40 + 1;
          v151[v40] = 0;
        }
        if ( n128 >= 128 )
          goto LABEL_53;
      }
      n128_12 = 1;
      v146 = 128 - n128;
      v41 = 0;
      v154 = (128 - n128) / 2;
      if ( v154 )
      {
        n128_1 = n128;
        v42 = 0;
        n128_3 = n128_2;
        v43 = 0;
        Blocka_2 = Blocka_1;
        v153 = &v151[n128];
        v152 = &v151[-n128];
        n128_11 = 1;
        do
        {
          n128_8 = n128_3;
          n128_9 = n128_11 - 1;
          if ( n128_9 )
            n128_8 = n128_9;
          n128_10 = n128_8;
          if ( !n128_9 )
            ++v41;
          v144 = 2 * v41;
          v153[2 * v42] = 2 * v41;
          v155 = (unsigned __int8)(2 * v41 - 1);
          n128_11 = n128_10 - 1;
          v47 = n128_10 == 1;
          v152[v43 + 256] = v155;
          if ( v47 )
          {
            n128_11 = n128_3;
            v144 = 2 * ++v41;
            v155 = (unsigned __int8)(2 * v41 - 1);
          }
          v153[2 * v42++ + 1] = v144;
          v152[v43 + 255] = v155;
          v43 -= 2;
        }
        while ( v42 < v154 );
        n128 = n128_1;
        Blocka_1 = Blocka_2;
        n128_12 = n128_11;
        v48 = 2 * v42 + 1;
      }
      else
      {
        v48 = 1;
      }
      if ( v48 - 1 < v146 )
      {
        Blocka_2 = Blocka_1;
        if ( n128_12 == 1 )
          LOBYTE(v41) = v41 + 1;
        v151[n128 - 1 + v48] = 2 * v41;
        v151[-n128 - v48 + 257] = 2 * v41 - 1;
        Blocka_1 = Blocka_2;
      }
      goto LABEL_53;
    }
    n128_3 = n128_2;
    v18 = 1;
    do
    {
      v19 = v160[2 * v18];
      v160[2 * v18] = v160[2 * n128_4];
      v20 = v160[2 * n128_4 - 1];
      v160[2 * n128_4] = v19;
      v21 = v160[2 * v18 - 1];
      v160[2 * v18 - 1] = v20;
      v160[2 * n128_4 - 1] = v21;
      n128_4 += n128_3;
      ++v18;
    }
    while ( n128_4 < 128 );
    n128_2 = n128_3;
    Blocka_1 = Blocka_2;
    __sub_40E860_n2 = ::__sub_40E860_n2;
  }
  else
  {
    v23 = _mm_load_si128((const __m128i *)&__sub_40E860_xmmword_439540);
    v24 = _mm_load_si128((const __m128i *)&__sub_40E860_xmmword_439550);
    for ( j = 0; j < 0x100; j += 128 )
    {
      *(__m128i *)&v160[j] = v24;
      v26 = _mm_add_epi8(v24, v23);
      *(__m128i *)&v160[j + 16] = v26;
      v27 = _mm_add_epi8(v26, v23);
      *(__m128i *)&v160[j + 32] = v27;
      v28 = _mm_add_epi8(v27, v23);
      *(__m128i *)&v160[j + 48] = v28;
      v29 = _mm_add_epi8(v28, v23);
      *(__m128i *)&v160[j + 64] = v29;
      v30 = _mm_add_epi8(v29, v23);
      *(__m128i *)&v160[j + 80] = v30;
      v31 = _mm_add_epi8(v30, v23);
      *(__m128i *)&v160[j + 96] = v31;
      v32 = _mm_add_epi8(v31, v23);
      *(__m128i *)&v160[j + 112] = v32;
      v24 = _mm_add_epi8(v32, v23);
    }
    n256_1 = n256;
    v34 = 0;
    if ( n256 < 256 )
    {
      do
      {
        v35 = v160[v34];
        v160[v34++] = v160[n256];
        v160[n256] = v35;
        n256 += n128_2;
      }
      while ( n256 < 256 );
      n256_1 = __sub_40E860_n256_0[0];
    }
    if ( n256 - n256_1 < 256 )
    {
      v36 = v160[v34];
      v160[v34] = v161;
      v161 = v36;
    }
    __sub_40E860_n2 = ::__sub_40E860_n2;
  }
  if ( __sub_40E860_n2 )
  {
    n256 = __sub_40E860_n256_0[0];
    goto LABEL_21;
  }
  Blocka_2 = Blocka_1;
  n128_7 = n128_2 + 1;
  v50 = 0;
  for ( k = 0; k < 0x80; ++k )
  {
    n128_6 = n128_7 - 1;
    n128_5 = n128_2;
    if ( n128_6 )
      n128_5 = n128_6;
    else
      ++v50;
    v54 = v50;
    v151[2 * k] = v50;
    n128_7 = n128_5 - 1;
    if ( n128_5 == 1 )
    {
      n128_7 = n128_2;
      v54 = ++v50;
    }
    v151[2 * k + 1] = v54;
  }
  Blocka_1 = Blocka_2;
LABEL_53:
  for ( m = 0; m < 0x80; ++m )
  {
    v151[(unsigned __int8)v160[2 * m] + 256] = 2 * m;
    v151[(unsigned __int8)v160[2 * m + 1] + 256] = 2 * m + 1;
  }
  v56 = *a3;
  v163 = a6 + 1;
  *a6 = v56;
  v164 = a3 + 1;
  if ( a4 <= 1 )
  {
    v64 = *(_BYTE **)(Blocka_1 + 68);
  }
  else
  {
    v57 = a3 + 1;
    v58 = v163;
    v147 = 1;
    do
    {
      v59 = *(v58 - 1);
      v164 = v57;
      v145 = (unsigned __int8)(*v57 - v59);
      v150 = (unsigned __int8)v151[v145];
      v60 = v160[v150] + v59;
      n16 = (unsigned __int8)*v58 - (unsigned __int8)(v60 + *v58 - *v57);
      if ( n16 < -16 || n16 > 16 )
      {
        LOBYTE(v150) = v151[v145 + 256];
        *v58 = *v57;
      }
      else
      {
        *v58 = v60;
      }
      *v57 = v150;
      **(_BYTE **)(Blocka_1 + 68) = *v58;
      v62 = *(_DWORD *)(Blocka_1
                      + 4
                      * (**(unsigned __int8 **)(Blocka_1 + 68) - *(unsigned __int8 *)(*(_DWORD *)(Blocka_1 + 68) - 1))
                      + 8364);
      *(_DWORD *)(*(_DWORD *)(Blocka_1 + 92) + 4) = v62;
      **(_DWORD **)(Blocka_1 + 92) = v62;
      v63 = *(_DWORD *)(Blocka_1 + 68);
      ++v57;
      *(_DWORD *)(Blocka_1 + 92) += 8;
      ++v147;
      ++v58;
      v64 = (_BYTE *)(v63 + 1);
      *(_DWORD *)(Blocka_1 + 68) = v64;
    }
    while ( v147 < a4 );
    v164 = v57;
    v163 = v58;
  }
  v65 = (unsigned __int8)*(v64 - 1);
  *v64 = v65;
  v66 = *(_DWORD *)(Blocka_1 + 92);
  *(_DWORD *)(Blocka_1 + 64) = v65;
  *(_DWORD *)(Blocka_1 + 84) = *(_DWORD *)(v66 - 8);
  *(_DWORD *)(Blocka_1 + 88) = *(_DWORD *)(v66 - 4);
  result = sub_434980(*(char **)(Blocka_1 + 80),*(char **)(Blocka_1 + 76),a4 + 2);
  if ( a5 != 1 )
  {
    v143 = a5 - 1;
    v68 = v163;
    v155 = Blocka_1 + 1148;
    n128_3 = Blocka_1 + 2188;
    v154 = Blocka_1 + 3228;
    n128_10 = Blocka_1 + 108;
    do
    {
      v69 = v68[-a4];
      v148 = (unsigned __int8)(*v164 - v69);
      v70 = v160[(unsigned __int8)v151[v148]] + v69;
      n16_1 = (unsigned __int8)*v68 - (unsigned __int8)(v70 + *v68 - *v164);
      v72 = v151[v148];
      if ( n16_1 < -16 || n16_1 > 16 )
      {
        *v68 = *v164;
        v72 = v151[v148 + 256];
      }
      else
      {
        *v68 = v70;
      }
      v73 = v164;
      *v164 = v72;
      v74 = (unsigned __int8)*v68;
      v75 = *(_BYTE *)(Blocka_1 + 64);
      *(_BYTE *)(*(_DWORD *)(Blocka_1 + 68) - 1) = v75;
      **(_BYTE **)(Blocka_1 + 68) = v75;
      v76 = *(_DWORD *)(Blocka_1 + 92);
      *(_DWORD *)(v76 - 8) = *(_DWORD *)(Blocka_1 + 84);
      *(_DWORD *)(v76 - 4) = *(_DWORD *)(Blocka_1 + 88);
      v77 = *(_DWORD **)(Blocka_1 + 92);
      *v77 = *(v77 - 2);
      v77[1] = *(v77 - 1);
      v78 = *(_DWORD *)(Blocka_1 + 76);
      v79 = *(_DWORD *)(Blocka_1 + 80);
      *(_DWORD *)(Blocka_1 + 76) = v79;
      *(_DWORD *)(Blocka_1 + 80) = v78;
      v79 += 2;
      *(_DWORD *)(Blocka_1 + 68) = v79;
      *(_DWORD *)(Blocka_1 + 72) = v78 + 2;
      *(_DWORD *)(Blocka_1 + 64) = v74;
      *(_BYTE *)(v79 - 2) = v74;
      v80 = *(unsigned __int8 **)(Blocka_1 + 72);
      *(_DWORD *)(Blocka_1 + 92) = *(_DWORD *)(Blocka_1 + 96) + 8;
      v81 = -*(_DWORD *)(Blocka_1 + 4 * (v74 - *(v80 - 1)) + 8364);
      *(_DWORD *)(Blocka_1 + 88) = 0;
      *(_DWORD *)(Blocka_1 + 84) = v81;
      v164 = v73 + 1;
      ++v68;
      if ( a4 != 1 )
      {
        v165 = a4 - 1;
        v163 = v68;
        while ( 1 )
        {
          v82 = *(_DWORD *)(Blocka_1 + 64);
          v83 = *v80;
          v84 = *(v80 - 1);
          Blocka_2 = Blocka_1;
          v85 = *(unsigned __int8 **)(Blocka_1 + 68);
          v86 = *v85;
          v167 = v82;
          v87 = v84 + v86;
          v88 = v80[1];
          v171 = v83;
          v166 = v85;
          v89 = v82 + v83;
          v172 = (16 * (v89 + v88) + -3 * (v87 - *(v85 - 2)) + 8 * v89 + 4 * v82 - v171 + 31) >> 6;
          v90 = *(_DWORD **)(Blocka_2 + 92);
          v91 = *(v90 - 2) + *(_DWORD *)(Blocka_2 + 84);
          v92 = v90[2] + *v90;
          v168 = v90;
          Blocka_1 = Blocka_2;
          v93 = v92 + v91;
          v94 = v172;
          if ( v93 <= 0 )
          {
            v158 = -v93;
            *(_DWORD *)(Blocka_2 + 100) = v155;
            v96 = v158;
            v95 = v167 + ((*v80 - *(v80 - 1) + 2) >> 2);
          }
          else
          {
            v158 = v93;
            *(_DWORD *)(Blocka_2 + 100) = n128_10;
            v95 = *v80 + ((v89 - v87 + 4) >> 3);
            v96 = v158;
          }
          v173 = v89;
          *(_DWORD *)(Blocka_1 + 12) = v94;
          *(_DWORD *)(Blocka_1 + 28) = v95;
          v97 = (v94 + v95) >> 1;
          *(_DWORD *)(Blocka_1 + 20) = v97;
          *(_DWORD *)(Blocka_1 + 16) = (v97 + v94) >> 1;
          v98 = (v97 + v95) >> 1;
          v99 = v168;
          v100 = v173;
          *(_DWORD *)(Blocka_1 + 24) = v98;
          v101 = *(unsigned __int8 *)(*(_DWORD *)(Blocka_1 + 100) + v96 + 16);
          *(_DWORD *)Blocka_1 = v101;
          v102 = *(_DWORD *)(Blocka_1 + 4 * v101 + 8);
          v103 = *(_DWORD *)(Blocka_1 + 88) + v99[3] + v99[1];
          if ( v103 < 0 )
          {
            v159 = -v103;
            *(_DWORD *)(Blocka_1 + 104) = v154;
            v112 = *(v80 - 1);
            v113 = *(v80 - 2);
            v170 = 2 * v102;
            v114 = 2 * v112 - *(v166 - 1) + v100 - 2 * v102 - v113 + 2;
            v109 = v159;
            v110 = v114 >> 2;
          }
          else
          {
            Blocka_2 = Blocka_1;
            v159 = v103;
            *(_DWORD *)(Blocka_1 + 104) = n128_3;
            v104 = *(v80 - 1);
            v105 = v80[1];
            v106 = *v80;
            v170 = 2 * v102;
            v107 = 2 * v105 - 2 * v102 - v166[1] - (v104 - v105);
            Blocka_1 = Blocka_2;
            v108 = v107 + v106 + 4;
            v109 = v159;
            v110 = v108 >> 3;
          }
          v111 = v102 + v110;
          *(_DWORD *)(Blocka_1 + 40) = v102;
          *(_DWORD *)(Blocka_1 + 56) = v111;
          v115 = v102 + v111 + 1;
          *(_DWORD *)(Blocka_1 + 44) = (v115 + v170) >> 2;
          *(_DWORD *)(Blocka_1 + 48) = v115 >> 1;
          v116 = v115 + 2 * v111;
          v117 = *(_DWORD *)(Blocka_1 + 104);
          *(_DWORD *)(Blocka_1 + 52) = v116 >> 2;
          v118 = *(unsigned __int8 *)(v117 + v109 + 16);
          *(_DWORD *)(Blocka_1 + 4) = v118;
          LOBYTE(v116) = *(_BYTE *)(Blocka_1 + 4 * v118 + 36);
          v169 = (unsigned __int8)*v164;
          v119 = (unsigned __int8)(v169 - v116);
          v120 = v160[(unsigned __int8)v151[v119]];
          v174 = (unsigned __int8)v151[v119];
          v121 = v120 + v116;
          v122 = v174;
          n16_2 = (unsigned __int8)*v163 - (unsigned __int8)(v121 + *v163 - v169);
          if ( n16_2 < -16 || n16_2 > 16 )
          {
            *v163 = v169;
            v122 = v151[v119 + 256];
          }
          else
          {
            *v163 = v121;
          }
          v124 = v163;
          *v164 = v122;
          v125 = *v124;
          v126 = *(_DWORD *)(Blocka_1 + 92);
          *(_DWORD *)(v126 - 8) = *(_DWORD *)(Blocka_1 + 84);
          *(_DWORD *)(v126 - 4) = *(_DWORD *)(Blocka_1 + 88);
          v127 = *(_DWORD *)(Blocka_1 + 64);
          v128 = *(unsigned __int8 **)(Blocka_1 + 72);
          *(_DWORD *)(Blocka_1 + 84) = *(_DWORD *)(Blocka_1 + 4 * (v125 - v127) + 8364)
                                     - *(_DWORD *)(Blocka_1 + 4 * (v125 - *v128) + 8364);
          v129 = *(_DWORD *)(Blocka_1 + 4 * (v125 - *(v128 - 1)) + 8364)
               - *(_DWORD *)(Blocka_1 + 4 * (v125 - v128[1]) + 8364);
          v130 = *(_DWORD *)(Blocka_1 + 68);
          *(_DWORD *)(Blocka_1 + 88) = v129;
          *(_BYTE *)(v130 - 1) = v127;
          v131 = *(_DWORD *)(Blocka_1 + 4);
          *(_DWORD *)(Blocka_1 + 64) = v125;
          ++*(_DWORD *)(Blocka_1 + 68);
          ++*(_DWORD *)(Blocka_1 + 72);
          *(_DWORD *)(Blocka_1 + 92) += 8;
          n6 = *(_DWORD *)(Blocka_1 + 4 * (v125 - *(_DWORD *)(Blocka_1 + 4 * v131 + 36)) + 8364);
          if ( n6 >= 6 )
          {
            v133 = *(_BYTE **)Blocka_1;
            v152 = (_BYTE *)(*(_DWORD *)(Blocka_1 + 4 * (v125 - *(_DWORD *)(Blocka_1 + 40)) + 8364) - 1);
            v153 = v133;
            if ( (int)v152 <= *(_DWORD *)(Blocka_1 + 4 * (v125 - *(_DWORD *)(Blocka_1 + 4 * (_DWORD)v133 + 4)) + 8364) )
            {
              if ( (int)v152 <= *(_DWORD *)(Blocka_1 + 4 * (v125 - *(_DWORD *)(Blocka_1 + 4 * (_DWORD)v153 + 12)) + 8364) )
              {
                v137 = n6 - 1;
                if ( v137 <= *(_DWORD *)(Blocka_1 + 4 * (v125 - *(_DWORD *)(Blocka_1 + 4 * v131 + 32)) + 8364) )
                {
                  if ( v137 > *(_DWORD *)(Blocka_1 + 4 * (v125 - *(_DWORD *)(Blocka_1 + 4 * v131 + 40)) + 8364) )
                  {
                    v138 = *(_DWORD *)(Blocka_1 + 104);
                    v139 = *(_DWORD *)(v138 + 4 * v131 - 4) - 1;
                    *(_DWORD *)(v138 + 4 * v131 - 4) = v139;
                    *(_BYTE *)(*(_DWORD *)(Blocka_1 + 104) + v139 + 16) = v131 + 1;
                  }
                }
                else
                {
                  *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(Blocka_1 + 104) + 4 * v131 - 8) + *(_DWORD *)(Blocka_1 + 104) + 16) = v131 - 1;
                  ++*(_DWORD *)(*(_DWORD *)(Blocka_1 + 104) + 4 * *(_DWORD *)(Blocka_1 + 4) - 8);
                }
              }
              else
              {
                v134 = *(_DWORD *)(Blocka_1 + 100);
                v135 = (_BYTE)v153 + 1;
                v136 = *(_DWORD *)(v134 + 4 * (_DWORD)v153 - 4) - 1;
                *(_DWORD *)(v134 + 4 * (_DWORD)v153 - 4) = v136;
                *(_BYTE *)(*(_DWORD *)(Blocka_1 + 100) + v136 + 16) = v135;
              }
            }
            else
            {
              *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(Blocka_1 + 100) + 4 * (_DWORD)v153 - 8)
                       + *(_DWORD *)(Blocka_1 + 100)
                       + 16) = (_BYTE)v153 - 1;
              ++*(_DWORD *)(*(_DWORD *)(Blocka_1 + 100) + 4 * *(_DWORD *)Blocka_1 - 8);
            }
          }
          v140 = v165;
          v141 = v164 + 1;
          ++*(_DWORD *)&__sub_40E860_buf[4 * (unsigned __int8)*v164];
          v164 = v141;
          ++v163;
          v165 = v140 - 1;
          if ( v140 == 1 )
            break;
          v80 = *(unsigned __int8 **)(Blocka_1 + 72);
        }
        v68 = v163;
      }
      result = (char *)--v143;
    }
    while ( v143 );
  }
  return result;
}

// __userpurge thunk for sub_40E860 @ 0x0040E860: reads the register arguments the
// caller passes, calls the moved body as cdecl, and pops 16 bytes of
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_40E860()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $24, %esp\n"
    "mov %ecx, 8(%esp)\n"
    "fnstsw %ax\n"
    "mov %eax, 12(%esp)\n"
    "push 20(%ebp)\n"
    "push 16(%ebp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "push 28(%esp)\n"
    "push 28(%esp)\n"
    "call __sub_40E860\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret $16\n"
  );
}

#undef sub_434980
