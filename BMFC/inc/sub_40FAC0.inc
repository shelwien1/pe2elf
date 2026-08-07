// sub_40FAC0 @ 0x0040FAC0 — __userpurge
// Extracted from BMF.cpp:13668-14183 by extract.py per incdec.md.

typedef int t_sub_40FAC0_n2;
static t_sub_40FAC0_n2& __sub_40FAC0_n2 = *(t_sub_40FAC0_n2*)(blob1 + 0x00443360 - BMF_BLOB_BASE);
typedef int t_sub_40FAC0_n256_0;
static t_sub_40FAC0_n256_0& __sub_40FAC0_n256_0 = *(t_sub_40FAC0_n256_0*)(blob1 + 0x00443398 - BMF_BLOB_BASE);
typedef __int128 t_sub_40FAC0_xmmword_4395D0;
static t_sub_40FAC0_xmmword_4395D0& __sub_40FAC0_xmmword_4395D0 = *(t_sub_40FAC0_xmmword_4395D0*)(blob1 + 0x004395D0 - BMF_BLOB_BASE);
typedef __int128 t_sub_40FAC0_xmmword_4395E0;
static t_sub_40FAC0_xmmword_4395E0& __sub_40FAC0_xmmword_4395E0 = *(t_sub_40FAC0_xmmword_4395E0*)(blob1 + 0x004395E0 - BMF_BLOB_BASE);
typedef __int128 t_sub_40FAC0_xmmword_4395F0;
static t_sub_40FAC0_xmmword_4395F0& __sub_40FAC0_xmmword_4395F0 = *(t_sub_40FAC0_xmmword_4395F0*)(blob1 + 0x004395F0 - BMF_BLOB_BASE);
typedef __int128 t_sub_40FAC0_xmmword_439600;
static t_sub_40FAC0_xmmword_439600& __sub_40FAC0_xmmword_439600 = *(t_sub_40FAC0_xmmword_439600*)(blob1 + 0x00439600 - BMF_BLOB_BASE);
typedef __int128 t_sub_40FAC0_xmmword_439610;
static t_sub_40FAC0_xmmword_439610& __sub_40FAC0_xmmword_439610 = *(t_sub_40FAC0_xmmword_439610*)(blob1 + 0x00439610 - BMF_BLOB_BASE);

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980

PROBE_DECL(__sub_40FAC0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) char * __sub_40FAC0(int *Blockb, char a2, int Src, int i, int a5)
{
  PROBE_HIT(__sub_40FAC0);
  int Src_1; // eax
  int n256; // esi
  int n128_1; // ecx
  __m128i si128; // xmm3
  __m128i v10; // xmm2
  __m128i v11; // xmm1
  __m128i v12; // xmm0
  unsigned int n0x70; // edx
  __m128i v14; // xmm4
  __m128i v15; // xmm5
  unsigned int j; // esi
  int n128; // esi
  int v18; // edx
  char v19; // cl
  char v20; // bl
  char v21; // al
  __m128i v22; // xmm1
  __m128i v23; // xmm0
  unsigned int k; // edx
  __m128i v25; // xmm0
  __m128i v26; // xmm0
  __m128i v27; // xmm0
  __m128i v28; // xmm0
  __m128i v29; // xmm0
  __m128i v30; // xmm0
  __m128i v31; // xmm0
  int n256_1; // edx
  int v33; // edi
  char v34; // bl
  char v35; // dl
  unsigned int v36; // edx
  unsigned int m_1; // esi
  unsigned int m; // edi
  char v39; // cl
  int v40; // edx
  int v41; // edx
  int v42; // ecx
  int v43; // edx
  _BYTE *v44; // ecx
  int v45; // esi
  char v46; // dl
  int v47; // edi
  int v48; // ecx
  int v49; // eax
  int v50; // ecx
  char *result; // eax
  int v52; // esi
  int v53; // edx
  int v54; // edi
  char v55; // al
  int v56; // edi
  _DWORD *v57; // edi
  int v58; // edi
  int v59; // eax
  unsigned __int8 *v60; // edi
  int v61; // edx
  int v62; // eax
  int v63; // esi
  unsigned __int8 *v64; // ebx
  int v65; // ecx
  int v66; // ecx
  int v67; // esi
  int v68; // eax
  _DWORD *v69; // ebx
  int v70; // edx
  int v71; // esi
  int v72; // edx
  int v73; // esi
  int v74; // ecx
  int v75; // edx
  int v76; // eax
  int v77; // ecx
  _DWORD *v78; // esi
  int v79; // eax
  int v80; // edx
  int v81; // edx
  int v82; // ecx
  int v83; // ebx
  int v84; // eax
  int v85; // edi
  int v86; // ecx
  int v87; // eax
  int v88; // ecx
  int v89; // eax
  int v90; // eax
  int v91; // ecx
  int v92; // edi
  int v93; // eax
  int v94; // esi
  int v95; // edx
  int v96; // eax
  int v97; // edi
  char *v98; // eax
  int v99; // edx
  int v100; // edi
  int v101; // ecx
  int v102; // eax
  unsigned __int8 *v103; // ecx
  int v104; // esi
  int v105; // ecx
  int v106; // eax
  int n6; // esi
  int v108; // edx
  int v109; // edi
  int v110; // esi
  int v111; // ecx
  int v112; // esi
  int n128_2; // [esp+0h] [ebp-160h]
  int v114; // [esp+0h] [ebp-160h]
  int v115; // [esp+0h] [ebp-160h]
  int v116; // [esp+8h] [ebp-158h]
  int v117; // [esp+Ch] [ebp-154h]
  alignas(16) _BYTE v118[255]; // [esp+10h] [ebp-150h]
  char v119; // [esp+10Fh] [ebp-51h]
  int *v120; // [esp+110h] [ebp-50h]
  int *v121; // [esp+114h] [ebp-4Ch]
  int *v122; // [esp+118h] [ebp-48h]
  int *v123; // [esp+11Ch] [ebp-44h]
  int v124; // [esp+120h] [ebp-40h]
  int v125; // [esp+124h] [ebp-3Ch]
  int Blockb_1; // [esp+128h] [ebp-38h]
  char *v127; // [esp+12Ch] [ebp-34h]
  int v128; // [esp+130h] [ebp-30h]
  unsigned __int8 *v129; // [esp+134h] [ebp-2Ch]
  int v130; // [esp+138h] [ebp-28h]
  _DWORD *v131; // [esp+13Ch] [ebp-24h]
  int v132; // [esp+140h] [ebp-20h]
  int v133; // [esp+144h] [ebp-1Ch]
  int v134; // [esp+148h] [ebp-18h]
  int v135; // [esp+14Ch] [ebp-14h]

  Src_1 = Src;
  n256 = __sub_40FAC0_n256_0;
  v127 = (char *)(Src + 1);
  n128_1 = 2 * __sub_40FAC0_n256_0 + 1;
  if ( __sub_40FAC0_n2 )
  {
    si128 = _mm_load_si128((const __m128i *)&__sub_40FAC0_xmmword_4395F0);
    v10 = _mm_load_si128((const __m128i *)&__sub_40FAC0_xmmword_4395D0);
    v11 = _mm_load_si128((const __m128i *)&__sub_40FAC0_xmmword_439600);
    v12 = _mm_load_si128((const __m128i *)&__sub_40FAC0_xmmword_439610);
    n0x70 = 0;
    v118[0] = 0;
    v119 = 0x80;
    do
    {
      v14 = v11;
      v15 = v11;
      v11 = _mm_add_epi8(v11, si128);
      *(__m128i *)&v118[2 * n0x70 + 1] = _mm_unpacklo_epi8(v14, v12);
      *(__m128i *)&v118[2 * n0x70 + 17] = _mm_unpackhi_epi8(v15, v12);
      v12 = _mm_add_epi8(v12, v10);
      n0x70 += 16;
    }
    while ( n0x70 < 0x70 );
    Blockb_1 = (int)Blockb;
    for ( j = 0; j < 7; ++j )
    {
      v118[4 * j + 225] = -2 * j - 113;
      v118[4 * j + 227] = -2 * j - 114;
      v118[4 * j + 226] = 2 * j + 113;
      v118[4 * j + 228] = 2 * j + 114;
    }
    Blockb = (int *)Blockb_1;
    v118[253] = -127;
    v118[254] = 127;
    if ( __sub_40FAC0_n256_0 )
    {
      n128 = n128_1;
      if ( n128_1 < 128 )
      {
        n128_2 = n128_1;
        v18 = 1;
        do
        {
          v19 = v118[2 * v18];
          v118[2 * v18] = v118[2 * n128];
          v20 = v118[2 * n128 - 1];
          v118[2 * n128] = v19;
          v21 = v118[2 * v18 - 1];
          v118[2 * v18 - 1] = v20;
          v118[2 * n128 - 1] = v21;
          n128 += n128_2;
          ++v18;
        }
        while ( n128 < 128 );
        Src_1 = Src;
        Blockb = (int *)Blockb_1;
      }
    }
  }
  else
  {
    v22 = _mm_load_si128((const __m128i *)&__sub_40FAC0_xmmword_4395D0);
    v23 = _mm_load_si128((const __m128i *)&__sub_40FAC0_xmmword_4395E0);
    for ( k = 0; k < 0x100; k += 128 )
    {
      *(__m128i *)&v118[k] = v23;
      v25 = _mm_add_epi8(v23, v22);
      *(__m128i *)&v118[k + 16] = v25;
      v26 = _mm_add_epi8(v25, v22);
      *(__m128i *)&v118[k + 32] = v26;
      v27 = _mm_add_epi8(v26, v22);
      *(__m128i *)&v118[k + 48] = v27;
      v28 = _mm_add_epi8(v27, v22);
      *(__m128i *)&v118[k + 64] = v28;
      v29 = _mm_add_epi8(v28, v22);
      *(__m128i *)&v118[k + 80] = v29;
      v30 = _mm_add_epi8(v29, v22);
      *(__m128i *)&v118[k + 96] = v30;
      v31 = _mm_add_epi8(v30, v22);
      *(__m128i *)&v118[k + 112] = v31;
      v23 = _mm_add_epi8(v31, v22);
    }
    v114 = 0;
    n256_1 = n256;
    if ( n256 < 256 )
    {
      v33 = 0;
      Blockb_1 = (int)Blockb;
      do
      {
        v34 = v118[v33];
        v118[v33++] = v118[n256];
        v118[n256] = v34;
        n256 += n128_1;
      }
      while ( n256 < 256 );
      Blockb = (int *)Blockb_1;
      n256_1 = __sub_40FAC0_n256_0;
      v114 = v33;
    }
    if ( n256 - n256_1 < 256 )
    {
      v35 = v118[v114];
      v118[v114] = v119;
      v119 = v35;
    }
  }
  if ( i <= 1 )
  {
    v44 = (_BYTE *)Blockb[17];
  }
  else
  {
    v36 = i - 1;
    m_1 = (i - 1) / 2;
    if ( m_1 )
    {
      for ( m = 0; m < m_1; ++m )
      {
        v39 = v118[*(unsigned __int8 *)(Src_1 + 2 * m + 1)] + *(_BYTE *)(Src_1 + 2 * m);
        *(_BYTE *)(Src_1 + 2 * m + 1) = v39;
        *(_BYTE *)Blockb[17] = v39;
        v40 = Blockb[*(unsigned __int8 *)Blockb[17] - *(unsigned __int8 *)(Blockb[17] - 1) + 2091];
        *(_DWORD *)(Blockb[23] + 4) = v40;
        *(_DWORD *)Blockb[23] = v40;
        ++Blockb[17];
        Blockb[23] += 8;
        LOBYTE(v40) = v118[*(unsigned __int8 *)(Src_1 + 2 * m + 2)] + *(_BYTE *)(Src_1 + 2 * m + 1);
        *(_BYTE *)(Src_1 + 2 * m + 2) = v40;
        *(_BYTE *)Blockb[17] = v40;
        v41 = Blockb[*(unsigned __int8 *)Blockb[17] - *(unsigned __int8 *)(Blockb[17] - 1) + 2091];
        *(_DWORD *)(Blockb[23] + 4) = v41;
        *(_DWORD *)Blockb[23] = v41;
        v42 = Blockb[17];
        Blockb[23] += 8;
        v43 = Src_1 + 2 * m + 3;
        v44 = (_BYTE *)(v42 + 1);
        Blockb[17] = (int)v44;
      }
      v127 = (char *)v43;
      v36 = i - 1;
      v45 = 2 * m + 1;
    }
    else
    {
      v45 = 1;
      v44 = nullptr;
    }
    if ( v36 > v45 - 1 )
    {
      v46 = v118[*(unsigned __int8 *)(v45 + Src_1)] + *(_BYTE *)(v45 + Src_1 - 1);
      *(_BYTE *)(v45 + Src_1) = v46;
      *(_BYTE *)Blockb[17] = v46;
      v47 = Blockb[*(unsigned __int8 *)Blockb[17] - *(unsigned __int8 *)(Blockb[17] - 1) + 2091];
      *(_DWORD *)(Blockb[23] + 4) = v47;
      *(_DWORD *)Blockb[23] = v47;
      v48 = Blockb[17];
      Blockb[23] += 8;
      v44 = (_BYTE *)(v48 + 1);
      Blockb[17] = (int)v44;
      v127 = (char *)(Src_1 + v45 + 1);
    }
  }
  v49 = (unsigned __int8)*(v44 - 1);
  *v44 = v49;
  v50 = Blockb[23];
  Blockb[16] = v49;
  Blockb[21] = *(_DWORD *)(v50 - 8);
  Blockb[22] = *(_DWORD *)(v50 - 4);
  result = sub_434980((char *)Blockb[20],(char *)Blockb[19],i + 2);
  v52 = a5 - 1;
  if ( a5 != 1 )
  {
    v120 = Blockb + 807;
    v121 = Blockb + 287;
    result = v127;
    v122 = Blockb + 547;
    v123 = Blockb + 27;
    do
    {
      while ( 1 )
      {
        v53 = (unsigned __int8)(result[-i] + v118[(unsigned __int8)*result]);
        *result = v53;
        v54 = Blockb[17];
        v127 = result + 1;
        v55 = *((_BYTE *)Blockb + 64);
        *(_BYTE *)(v54 - 1) = v55;
        *(_BYTE *)Blockb[17] = v55;
        v56 = Blockb[23];
        *(_DWORD *)(v56 - 8) = Blockb[21];
        *(_DWORD *)(v56 - 4) = Blockb[22];
        v57 = (_DWORD *)Blockb[23];
        *v57 = *(v57 - 2);
        v57[1] = *(v57 - 1);
        v58 = Blockb[19];
        v59 = Blockb[20];
        Blockb[19] = v59;
        Blockb[20] = v58;
        v59 += 2;
        Blockb[17] = v59;
        Blockb[18] = v58 + 2;
        Blockb[16] = v53;
        *(_BYTE *)(v59 - 2) = v53;
        Blockb[23] = Blockb[24] + 8;
        v60 = (unsigned __int8 *)Blockb[18];
        result = v127;
        Blockb[21] = -Blockb[v53 - *(v60 - 1) + 2091];
        Blockb[22] = 0;
        if ( i != 1 )
          break;
        if ( !--v52 )
          return result;
      }
      v128 = i - 1;
      v115 = v52;
      v127 = result;
      while ( 1 )
      {
        v61 = Blockb[16];
        v62 = *v60;
        v63 = *(v60 - 1);
        Blockb_1 = (int)Blockb;
        v64 = (unsigned __int8 *)Blockb[17];
        v65 = *v64;
        v130 = v61;
        v66 = v63 + v65;
        v67 = v60[1];
        v133 = v62;
        v129 = v64;
        v68 = v61 + v62;
        v134 = (16 * (v68 + v67) + -3 * (v66 - *(v64 - 2)) + 8 * v68 + 4 * v61 - v133 + 31) >> 6;
        v69 = *(_DWORD **)(Blockb_1 + 92);
        v70 = *(v69 - 2) + *(_DWORD *)(Blockb_1 + 84);
        v71 = v69[2] + *v69;
        v131 = v69;
        Blockb = (int *)Blockb_1;
        v72 = v71 + v70;
        v73 = v134;
        if ( v72 <= 0 )
        {
          v124 = -v72;
          *(_DWORD *)(Blockb_1 + 100) = v121;
          v75 = v124;
          v74 = v130 + ((*v60 - *(v60 - 1) + 2) >> 2);
        }
        else
        {
          v124 = v72;
          *(_DWORD *)(Blockb_1 + 100) = v123;
          v74 = *v60 + ((v68 - v66 + 4) >> 3);
          v75 = v124;
        }
        v135 = v68;
        Blockb[3] = v73;
        Blockb[7] = v74;
        v76 = (v73 + v74) >> 1;
        Blockb[5] = v76;
        Blockb[4] = (v76 + v73) >> 1;
        v77 = (v76 + v74) >> 1;
        v78 = v131;
        v79 = v135;
        Blockb[6] = v77;
        v80 = *(unsigned __int8 *)(Blockb[25] + v75 + 16);
        *Blockb = v80;
        v81 = Blockb[v80 + 2];
        v82 = Blockb[22] + v78[3] + v78[1];
        if ( v82 < 0 )
        {
          v125 = -v82;
          Blockb[26] = (int)v120;
          v91 = *(v60 - 1);
          v92 = *(v60 - 2);
          v132 = 2 * v81;
          v93 = 2 * v91 - *(v129 - 1) + v79 - 2 * v81 - v92 + 2;
          v88 = v125;
          v89 = v93 >> 2;
        }
        else
        {
          Blockb_1 = (int)Blockb;
          v125 = v82;
          Blockb[26] = (int)v122;
          v83 = *(v60 - 1);
          v84 = v60[1];
          v85 = *v60;
          v132 = 2 * v81;
          v86 = 2 * v84 - 2 * v81 - v129[1] - (v83 - v84);
          Blockb = (int *)Blockb_1;
          v87 = v86 + v85 + 4;
          v88 = v125;
          v89 = v87 >> 3;
        }
        v90 = v81 + v89;
        Blockb[10] = v81;
        Blockb[14] = v90;
        v94 = v81 + v90 + 1;
        Blockb[11] = (v94 + v132) >> 2;
        Blockb[12] = v94 >> 1;
        v95 = v94 + 2 * v90;
        v96 = Blockb[26];
        Blockb[13] = v95 >> 2;
        v97 = *(unsigned __int8 *)(v96 + v88 + 16);
        v98 = v127;
        Blockb[1] = v97;
        v99 = (unsigned __int8)(LOBYTE(Blockb[v97 + 9]) + v118[(unsigned __int8)*v98]);
        *v98 = v99;
        v100 = Blockb[23];
        v101 = Blockb[21];
        v127 = v98 + 1;
        *(_DWORD *)(v100 - 8) = v101;
        *(_DWORD *)(v100 - 4) = Blockb[22];
        v102 = Blockb[16];
        v103 = (unsigned __int8 *)Blockb[18];
        Blockb[21] = Blockb[v99 - v102 + 2091] - Blockb[v99 - *v103 + 2091];
        v104 = Blockb[v99 - *(v103 - 1) + 2091] - Blockb[v99 - v103[1] + 2091];
        v105 = Blockb[17];
        Blockb[22] = v104;
        *(_BYTE *)(v105 - 1) = v102;
        v106 = Blockb[1];
        ++Blockb[17];
        Blockb[16] = v99;
        ++Blockb[18];
        Blockb[23] += 8;
        n6 = Blockb[v99 - Blockb[v106 + 9] + 2091];
        if ( n6 >= 6 )
        {
          v116 = Blockb[v99 - Blockb[10] + 2091] - 1;
          v117 = *Blockb;
          if ( v116 <= Blockb[v99 - Blockb[v117 + 1] + 2091] )
          {
            if ( v116 <= Blockb[v99 - Blockb[v117 + 3] + 2091] )
            {
              v110 = n6 - 1;
              if ( v110 <= Blockb[v99 - Blockb[v106 + 8] + 2091] )
              {
                if ( v110 > Blockb[v99 - Blockb[v106 + 10] + 2091] )
                {
                  v111 = Blockb[26];
                  v112 = *(_DWORD *)(v111 + 4 * v106 - 4) - 1;
                  *(_DWORD *)(v111 + 4 * v106 - 4) = v112;
                  *(_BYTE *)(Blockb[26] + v112 + 16) = v106 + 1;
                }
              }
              else
              {
                *(_BYTE *)(*(_DWORD *)(Blockb[26] + 4 * v106 - 8) + Blockb[26] + 16) = v106 - 1;
                ++*(_DWORD *)(Blockb[26] + 4 * Blockb[1] - 8);
              }
            }
            else
            {
              v108 = Blockb[25];
              v109 = *(_DWORD *)(v108 + 4 * v117 - 4) - 1;
              *(_DWORD *)(v108 + 4 * v117 - 4) = v109;
              *(_BYTE *)(Blockb[25] + v109 + 16) = v117 + 1;
            }
          }
          else
          {
            *(_BYTE *)(*(_DWORD *)(Blockb[25] + 4 * v117 - 8) + Blockb[25] + 16) = v117 - 1;
            ++*(_DWORD *)(Blockb[25] + 4 * *Blockb - 8);
          }
        }
        if ( !--v128 )
          break;
        v60 = (unsigned __int8 *)Blockb[18];
      }
      result = v127;
      v52 = v115 - 1;
    }
    while ( v115 != 1 );
  }
  return result;
}

#ifndef BMF_STANDALONE
// __userpurge thunk for sub_40FAC0 @ 0x0040FAC0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and pops 12 bytes of
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_40FAC0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $28, %esp\n"
    "mov %ecx, 12(%esp)\n"
    "fnstsw %ax\n"
    "mov %eax, 16(%esp)\n"
    "push 16(%ebp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "push 28(%esp)\n"
    "push 28(%esp)\n"
    "call __sub_40FAC0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret $12\n"
  );
}
#endif

#undef sub_434980
