// sub_422DB0 @ 0x00422DB0 — __userpurge
// Extracted from BMF.cpp:28958-29397 by extract.py per incdec.md.

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980
static inline int __fwd_sub_422DB0_sub_414620(void *a0, int a1) { return __sub_414620((unsigned __int16 *)a0, a1); }
#define sub_414620 __fwd_sub_422DB0_sub_414620
#define sub_414920 __sub_414920
#define sub_4149C0 __sub_4149C0
static inline int __fwd_sub_422DB0_sub_41A130(void *a0, const __m128 &a1, const __m128 &a2, void *a3, void *a4) { return __sub_41A130((__m128 *)a0, a1, a2, (_DWORD *)a3, (_DWORD *)a4); }
#define sub_41A130 __fwd_sub_422DB0_sub_41A130
#define sub_41CAB0 __sub_41CAB0

PROBE_DECL(__sub_422DB0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) void __sub_422DB0(int lpAddress, char ArgList, const __m128 &a3__ref, const __m128 &a4__ref, _BYTE *a5, int i, int a7)
{
  alignas(16) unsigned char __hexrays_frame[44];   // original frame, ebp-0x1c..ebp+0x0
  int &v95 = *(int *)(__hexrays_frame + 0);
  unsigned int &v96 = *(unsigned int *)(__hexrays_frame + 0);
  _BYTE * &v97 = *(_BYTE * *)(__hexrays_frame + 8);
  PROBE_HIT(__sub_422DB0);
  __m128 a3 = a3__ref;
  __m128 a4 = a4__ref;
  char v9; // fps
  int i_1; // esi
  int v11; // eax
  int v12; // ecx
  int v13; // esi
  __int16 v14; // dx
  _WORD *v15; // edi
  __int64 v16; // rax
  bool v17; // cc
  int v18; // edi
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int v23; // edi
  __int16 v24; // ax
  int v25; // eax
  int v26; // ecx
  int v27; // edi
  int v28; // edx
  int v29; // ecx
  int v30; // edi
  int v31; // eax
  int v32; // eax
  int v33; // edi
  int v34; // ecx
  int v35; // edx
  int v36; // edi
  int v37; // edx
  int v38; // ecx
  int v39; // edi
  int v40; // ecx
  int v41; // edi
  int v42; // ecx
  int v43; // edi
  int v44; // ecx
  char v45; // fps
  char v46; // fps
  __m128 v47; // xmm0
  int v48; // esi
  int v49; // edi
  int *v50; // edx
  int v51; // ecx
  int v52; // esi
  _OWORD *v53; // edx
  int v54; // edx
  int v55; // esi
  int v56; // edi
  int v57; // eax
  int v58; // eax
  int v59; // esi
  int v60; // edi
  int v61; // edx
  int v62; // edi
  int v63; // esi
  int v64; // edx
  int v65; // eax
  int v66; // esi
  int v67; // eax
  int v68; // edx
  int v69; // ecx
  int v70; // edi
  int v71; // eax
  int v72; // edx
  int v73; // esi
  int v74; // eax
  int v75; // ecx
  int v76; // edi
  int v77; // eax
  int v78; // edx
  int v79; // esi
  int v80; // edi
  int v81; // edx
  int v82; // ecx
  int v83; // edi
  int v84; // eax
  int v85; // ecx
  int v86; // esi
  int v87; // eax
  int v88; // edx
  int v89; // esi
  int v90; // edi
  unsigned int j; // esi
  int v92; // ebp
  int v93; // eax
  int v94; // edx

  sub_4149C0(ArgList);
  i_1 = i;
  v11 = *(_DWORD *)(lpAddress + 278736);
  v12 = v11;
  if ( i > 0 )
  {
    v95 = 0;
    while ( 1 )
    {
      v13 = *(__int16 *)(v11 - 18) >> 4;
      *(_DWORD *)(lpAddress + 278708) = *(_DWORD *)(lpAddress + 278704) + *(_DWORD *)(lpAddress + 4 * v13 + 278960);
      *(_DWORD *)(lpAddress + 278712) = *(_DWORD *)(lpAddress + 278704) + *(_DWORD *)(lpAddress + 4 * v13 + 278944);
      v14 = (unsigned __int8)((*(unsigned __int16 *)(*(_DWORD *)(lpAddress + 278736) - 18) >> 4)
                            + *(_BYTE *)(sub_414620(
                                           (unsigned __int16 *)(lpAddress
                                                              + 8
                                                              * (*(_DWORD *)(lpAddress + 278704)
                                                               + *(_DWORD *)(lpAddress
                                                                           + 4
                                                                           * ((*(__int16 *)(v12 - 18) <= *(__int16 *)(v12 - 36))
                                                                            + (*(__int16 *)(v12 - 18) < *(__int16 *)(v12 - 36)))
                                                                           + 278828)
                                                               + *(_DWORD *)(lpAddress
                                                                           + 4 * *(unsigned __int8 *)(v12 - 20)
                                                                           + 278812)
                                                               + *(_DWORD *)(lpAddress
                                                                           + 4 * *(unsigned __int8 *)(v12 - 2)
                                                                           + 278796)
                                                               + *(_DWORD *)(lpAddress
                                                                           + 4
                                                                           * (((unsigned int)(v13 - 115) >> 31)
                                                                            + ((unsigned int)(v13 - 17) >> 31))
                                                                           + 278780)
                                                               + *(_DWORD *)(lpAddress + 278848))
                                                              + 940072),
                                           lpAddress + 278708)
                                       + lpAddress
                                       + 280496));
      *a5 = v14;
      v14 *= 16;
      **(_WORD **)(lpAddress + 278736) = v14;
      ++a5;
      *(_WORD *)(*(_DWORD *)(lpAddress + 278736) + 2) = v14;
      v15 = *(_WORD **)(lpAddress + 278736);
      v16 = (__int16)(*v15 - *(v15 - 9));
      v15[2] = v16;
      LOWORD(v16) = (WORD2(v16) ^ v16) - WORD2(v16);
      *(_WORD *)(*(_DWORD *)(lpAddress + 278736) + 6) = v16;
      *(_WORD *)(*(_DWORD *)(lpAddress + 278736) + 14) = v16;
      *(_WORD *)(*(_DWORD *)(lpAddress + 278736) + 12) = v16;
      *(_WORD *)(*(_DWORD *)(lpAddress + 278736) + 10) = v16;
      *(_WORD *)(*(_DWORD *)(lpAddress + 278736) + 8) = (unsigned int)*(__int16 *)(*(_DWORD *)(lpAddress + 278736) + 10) >> 1;
      *(_BYTE *)(*(_DWORD *)(lpAddress + 278736) + 17) = 2;
      *(_BYTE *)(*(_DWORD *)(lpAddress + 278736) + 16) = (*(__int16 *)(*(_DWORD *)(lpAddress + 278736) + 4) <= 0)
                                                       + (*(__int16 *)(*(_DWORD *)(lpAddress + 278736) + 4) < 0);
      v11 = *(_DWORD *)(lpAddress + 278736) + 18;
      v17 = v95 + 1 < i;
      *(_DWORD *)(lpAddress + 278736) = v11;
      ++v95;
      if ( !v17 )
        break;
      v12 = *(_DWORD *)(lpAddress + 278736);
    }
    i_1 = i;
  }
  v18 = *(_DWORD *)(v11 - 14);
  v19 = *(_DWORD *)(v11 - 10);
  *(_DWORD *)v11 = *(_DWORD *)(v11 - 18);
  v20 = *(_DWORD *)(v11 - 6);
  *(_DWORD *)(v11 + 4) = v18;
  LOWORD(v18) = *(_WORD *)(v11 - 2);
  *(_DWORD *)(v11 + 8) = v19;
  *(_DWORD *)(v11 + 12) = v20;
  *(_WORD *)(v11 + 16) = v18;
  v21 = *(_DWORD *)(lpAddress + 278736);
  v22 = *(_DWORD *)(v21 - 10);
  v23 = *(_DWORD *)(v21 - 6);
  *(_DWORD *)(v21 + 18) = *(_DWORD *)(v21 - 18);
  *(_DWORD *)(v21 + 22) = *(_DWORD *)(v21 - 14);
  v24 = *(_WORD *)(v21 - 2);
  *(_DWORD *)(v21 + 26) = v22;
  *(_DWORD *)(v21 + 30) = v23;
  *(_WORD *)(v21 + 34) = v24;
  v25 = *(_DWORD *)(lpAddress + 278736);
  v26 = *(_DWORD *)(v25 - 10);
  v27 = *(_DWORD *)(v25 - 6);
  *(_DWORD *)(v25 + 36) = *(_DWORD *)(v25 - 18);
  *(_DWORD *)(v25 + 40) = *(_DWORD *)(v25 - 14);
  LOWORD(v21) = *(_WORD *)(v25 - 2);
  *(_DWORD *)(v25 + 44) = v26;
  *(_DWORD *)(v25 + 48) = v27;
  *(_WORD *)(v25 + 52) = v21;
  v28 = *(_DWORD *)(lpAddress + 278736);
  v29 = *(_DWORD *)(v28 - 14);
  v30 = *(_DWORD *)(v28 - 10);
  *(_DWORD *)(v28 + 54) = *(_DWORD *)(v28 - 18);
  v31 = *(_DWORD *)(v28 - 6);
  *(_DWORD *)(v28 + 58) = v29;
  LOWORD(v29) = *(_WORD *)(v28 - 2);
  *(_DWORD *)(v28 + 62) = v30;
  *(_DWORD *)(v28 + 66) = v31;
  *(_WORD *)(v28 + 70) = v29;
  v32 = *(_DWORD *)(lpAddress + 278736);
  v33 = *(_DWORD *)(v32 - 14);
  v34 = *(_DWORD *)(v32 - 6);
  *(_DWORD *)(v32 + 72) = *(_DWORD *)(v32 - 18);
  v35 = *(_DWORD *)(v32 - 10);
  *(_DWORD *)(v32 + 76) = v33;
  LOWORD(v33) = *(_WORD *)(v32 - 2);
  *(_DWORD *)(v32 + 80) = v35;
  *(_DWORD *)(v32 + 84) = v34;
  *(_WORD *)(v32 + 88) = v33;
  v36 = *(_DWORD *)(lpAddress + 278736);
  v37 = -18 * i_1;
  *(_DWORD *)(v36 + v37 - 18) = *(_DWORD *)(v36 - 18 * i_1);
  *(_DWORD *)(v36 + v37 - 14) = *(_DWORD *)(v36 - 18 * i_1 + 4);
  *(_DWORD *)(v36 + v37 - 10) = *(_DWORD *)(v36 - 18 * i_1 + 8);
  *(_DWORD *)(v36 + v37 - 6) = *(_DWORD *)(v36 - 18 * i_1 + 12);
  *(_WORD *)(v36 + v37 - 2) = *(_WORD *)(v36 - 18 * i_1 + 16);
  v38 = *(_DWORD *)(lpAddress + 278736);
  *(_DWORD *)(v38 + v37 - 36) = *(_DWORD *)(v38 - 18 * i_1 + 18);
  *(_DWORD *)(v38 + v37 - 32) = *(_DWORD *)(v38 - 18 * i_1 + 22);
  *(_DWORD *)(v38 + v37 - 28) = *(_DWORD *)(v38 - 18 * i_1 + 26);
  *(_DWORD *)(v38 + v37 - 24) = *(_DWORD *)(v38 - 18 * i_1 + 30);
  *(_WORD *)(v38 + v37 - 20) = *(_WORD *)(v38 - 18 * i_1 + 34);
  v39 = *(_DWORD *)(lpAddress + 278736);
  *(_DWORD *)(v39 + v37 - 54) = *(_DWORD *)(v39 - 18 * i_1 + 36);
  *(_DWORD *)(v39 + v37 - 50) = *(_DWORD *)(v39 - 18 * i_1 + 40);
  *(_DWORD *)(v39 + v37 - 46) = *(_DWORD *)(v39 - 18 * i_1 + 44);
  *(_DWORD *)(v39 + v37 - 42) = *(_DWORD *)(v39 - 18 * i_1 + 48);
  *(_WORD *)(v39 + v37 - 38) = *(_WORD *)(v39 - 18 * i_1 + 52);
  v40 = *(_DWORD *)(lpAddress + 278736);
  *(_DWORD *)(v40 + v37 - 72) = *(_DWORD *)(v40 - 18 * i_1 + 54);
  *(_DWORD *)(v40 + v37 - 68) = *(_DWORD *)(v40 - 18 * i_1 + 58);
  *(_DWORD *)(v40 + v37 - 64) = *(_DWORD *)(v40 - 18 * i_1 + 62);
  *(_DWORD *)(v40 + v37 - 60) = *(_DWORD *)(v40 - 18 * i_1 + 66);
  *(_WORD *)(v40 + v37 - 56) = *(_WORD *)(v40 - 18 * i_1 + 70);
  v41 = *(_DWORD *)(lpAddress + 278736);
  *(_DWORD *)(v41 + v37 - 90) = *(_DWORD *)(v41 - 18 * i_1 + 72);
  *(_DWORD *)(v41 + v37 - 86) = *(_DWORD *)(v41 - 18 * i_1 + 76);
  *(_DWORD *)(v41 + v37 - 82) = *(_DWORD *)(v41 - 18 * i_1 + 80);
  *(_DWORD *)(v41 + v37 - 78) = *(_DWORD *)(v41 - 18 * i_1 + 84);
  *(_WORD *)(v41 + v37 - 74) = *(_WORD *)(v41 - 18 * i_1 + 88);
  v42 = *(_DWORD *)(lpAddress + 278736);
  *(_DWORD *)(v42 + v37 - 108) = *(_DWORD *)(v42 - 18 * i_1 + 90);
  *(_DWORD *)(v42 + v37 - 104) = *(_DWORD *)(v42 - 18 * i_1 + 94);
  *(_DWORD *)(v42 + v37 - 100) = *(_DWORD *)(v42 - 18 * i_1 + 98);
  *(_DWORD *)(v42 + v37 - 96) = *(_DWORD *)(v42 - 18 * i_1 + 102);
  *(_WORD *)(v42 + v37 - 92) = *(_WORD *)(v42 - 18 * i_1 + 106);
  v43 = *(_DWORD *)(lpAddress + 278736);
  *(_DWORD *)(v43 + v37 - 126) = *(_DWORD *)(v43 - 18 * i_1 + 108);
  *(_DWORD *)(v43 + v37 - 122) = *(_DWORD *)(v43 - 18 * i_1 + 112);
  *(_DWORD *)(v43 + v37 - 118) = *(_DWORD *)(v43 - 18 * i_1 + 116);
  *(_DWORD *)(v43 + v37 - 114) = *(_DWORD *)(v43 - 18 * i_1 + 120);
  *(_WORD *)(v43 + v37 - 110) = *(_WORD *)(v43 - 18 * i_1 + 124);
  v44 = *(_DWORD *)(lpAddress + 278736);
  *(_DWORD *)(v44 + v37 - 144) = *(_DWORD *)(v44 - 18 * i_1 + 126);
  *(_DWORD *)(v44 + v37 - 140) = *(_DWORD *)(v44 - 18 * i_1 + 130);
  *(_DWORD *)(v44 + v37 - 136) = *(_DWORD *)(v44 - 18 * i_1 + 134);
  *(_DWORD *)(v44 + v37 - 132) = *(_DWORD *)(v44 - 18 * i_1 + 138);
  *(_WORD *)(v44 + v37 - 128) = *(_WORD *)(v44 - 18 * i_1 + 142);
  sub_434980(*(char **)(lpAddress + 278760),*(char **)(lpAddress + 278756),18 * i_1 + 234);
  sub_434980(*(char **)(lpAddress + 278764),*(char **)(lpAddress + 278756),18 * i_1 + 234);
  sub_434980(*(char **)(lpAddress + 278768),*(char **)(lpAddress + 278756),18 * i_1 + 234);
  if ( a7 > 1 )
  {
    v96 = 0;
    v47 = 0;
    do
    {
      v48 = *(_DWORD *)(lpAddress + 278668);
      v49 = *(_DWORD *)(v48 - 4);
      v97 = a5;
      *(_DWORD *)(v48 + 4) = v49;
      **(_DWORD **)(lpAddress + 278668) = v49;
      v50 = *(int **)(lpAddress + 278660);
      v51 = *(_DWORD *)(lpAddress + 278664);
      *(_DWORD *)(lpAddress + 278660) = v51;
      *(_DWORD *)(lpAddress + 278664) = v50;
      v51 += 8;
      v50 += 2;
      *(_DWORD *)(lpAddress + 278668) = v51;
      *(_DWORD *)(lpAddress + 278672) = v50;
      v52 = *v50;
      *(_DWORD *)(v51 - 4) = *v50;
      *(_DWORD *)(*(_DWORD *)(lpAddress + 278668) - 8) = v52;
      *(_QWORD *)(lpAddress + 278528) = v47.m128_u64[0];
      *(_DWORD *)(lpAddress + 278536) = 0;
      *(_WORD *)(lpAddress + 278540) = 0;
      v53 = (_OWORD *)((lpAddress + 278543) & 0xFFFFFFF0);
      *(_BYTE *)(lpAddress + 278542) = 0;
      *(_QWORD *)(lpAddress + 278640) = v47.m128_u64[0];
      *(_QWORD *)(lpAddress + 278648) = v47.m128_u64[0];
      *v53 = v47;
      v53[1] = v47;
      v53[2] = v47;
      v53[3] = v47;
      v53[4] = v47;
      v53[5] = v47;
      v53[6] = v47;
      v54 = *(_DWORD *)(lpAddress + 278736);
      v55 = *(_DWORD *)(v54 - 14);
      v56 = *(_DWORD *)(v54 - 10);
      v57 = *(_DWORD *)(v54 - 6);
      *(_DWORD *)v54 = *(_DWORD *)(v54 - 18);
      LOWORD(v51) = *(_WORD *)(v54 - 2);
      *(_DWORD *)(v54 + 4) = v55;
      *(_DWORD *)(v54 + 8) = v56;
      *(_DWORD *)(v54 + 12) = v57;
      *(_WORD *)(v54 + 16) = v51;
      v58 = *(_DWORD *)(lpAddress + 278736);
      v59 = *(_DWORD *)(v58 - 32);
      v60 = *(_DWORD *)(v58 - 28);
      LOWORD(v51) = *(_WORD *)(v58 - 20);
      *(_DWORD *)(v58 + 18) = *(_DWORD *)(v58 - 36);
      v61 = *(_DWORD *)(v58 - 24);
      *(_DWORD *)(v58 + 22) = v59;
      *(_DWORD *)(v58 + 26) = v60;
      *(_DWORD *)(v58 + 30) = v61;
      *(_WORD *)(v58 + 34) = v51;
      v62 = *(_DWORD *)(lpAddress + 278736);
      v63 = *(_DWORD *)(v62 - 50);
      v64 = *(_DWORD *)(v62 - 42);
      LOWORD(v51) = *(_WORD *)(v62 - 38);
      *(_DWORD *)(v62 + 36) = *(_DWORD *)(v62 - 54);
      v65 = *(_DWORD *)(v62 - 46);
      *(_DWORD *)(v62 + 40) = v63;
      *(_DWORD *)(v62 + 44) = v65;
      *(_DWORD *)(v62 + 48) = v64;
      *(_WORD *)(v62 + 52) = v51;
      v66 = *(_DWORD *)(lpAddress + 278736);
      v67 = *(_DWORD *)(v66 - 64);
      v68 = *(_DWORD *)(v66 - 60);
      LOWORD(v51) = *(_WORD *)(v66 - 56);
      *(_DWORD *)(v66 + 54) = *(_DWORD *)(v66 - 72);
      *(_DWORD *)(v66 + 58) = *(_DWORD *)(v66 - 68);
      *(_DWORD *)(v66 + 62) = v67;
      *(_DWORD *)(v66 + 66) = v68;
      *(_WORD *)(v66 + 70) = v51;
      v69 = *(_DWORD *)(lpAddress + 278736);
      v70 = *(_DWORD *)(v69 - 82);
      v71 = *(_DWORD *)(v69 - 78);
      LOWORD(v68) = *(_WORD *)(v69 - 74);
      *(_DWORD *)(v69 + 72) = *(_DWORD *)(v69 - 90);
      *(_DWORD *)(v69 + 76) = *(_DWORD *)(v69 - 86);
      *(_DWORD *)(v69 + 80) = v70;
      *(_DWORD *)(v69 + 84) = v71;
      *(_WORD *)(v69 + 88) = v68;
      v72 = *(_DWORD *)(lpAddress + 278768);
      v73 = *(_DWORD *)(lpAddress + 278772);
      v74 = *(_DWORD *)(lpAddress + 278764);
      v75 = *(_DWORD *)(lpAddress + 278760);
      v76 = *(_DWORD *)(lpAddress + 278756);
      *(_DWORD *)(lpAddress + 278772) = v72;
      *(_DWORD *)(lpAddress + 278768) = v74;
      *(_DWORD *)(lpAddress + 278764) = v75;
      *(_DWORD *)(lpAddress + 278756) = v73;
      *(_DWORD *)(lpAddress + 278760) = v76;
      v73 += 144;
      *(_DWORD *)(lpAddress + 278736) = v73;
      v76 += 144;
      *(_DWORD *)(lpAddress + 278740) = v76;
      *(_DWORD *)(lpAddress + 278744) = v75 + 144;
      *(_DWORD *)(lpAddress + 278748) = v74 + 144;
      *(_DWORD *)(lpAddress + 278752) = v72 + 144;
      *(_DWORD *)(v73 - 18) = *(_DWORD *)v76;
      *(_DWORD *)(v73 - 14) = *(_DWORD *)(v76 + 4);
      *(_DWORD *)(v73 - 10) = *(_DWORD *)(v76 + 8);
      *(_DWORD *)(v73 - 6) = *(_DWORD *)(v76 + 12);
      *(_WORD *)(v73 - 2) = *(_WORD *)(v76 + 16);
      v77 = *(_DWORD *)(lpAddress + 278736);
      v78 = *(_DWORD *)(lpAddress + 278740);
      *(_DWORD *)(v77 - 36) = *(_DWORD *)(v78 + 18);
      *(_DWORD *)(v77 - 32) = *(_DWORD *)(v78 + 22);
      *(_DWORD *)(v77 - 28) = *(_DWORD *)(v78 + 26);
      *(_DWORD *)(v77 - 24) = *(_DWORD *)(v78 + 30);
      *(_WORD *)(v77 - 20) = *(_WORD *)(v78 + 34);
      v79 = *(_DWORD *)(lpAddress + 278736);
      v80 = *(_DWORD *)(lpAddress + 278740);
      *(_DWORD *)(v79 - 54) = *(_DWORD *)(v80 + 36);
      *(_DWORD *)(v79 - 50) = *(_DWORD *)(v80 + 40);
      *(_DWORD *)(v79 - 46) = *(_DWORD *)(v80 + 44);
      *(_DWORD *)(v79 - 42) = *(_DWORD *)(v80 + 48);
      *(_WORD *)(v79 - 38) = *(_WORD *)(v80 + 52);
      v81 = *(_DWORD *)(lpAddress + 278736);
      v82 = *(_DWORD *)(lpAddress + 278740);
      *(_DWORD *)(v81 - 72) = *(_DWORD *)(v82 + 54);
      *(_DWORD *)(v81 - 68) = *(_DWORD *)(v82 + 58);
      *(_DWORD *)(v81 - 64) = *(_DWORD *)(v82 + 62);
      *(_DWORD *)(v81 - 60) = *(_DWORD *)(v82 + 66);
      *(_WORD *)(v81 - 56) = *(_WORD *)(v82 + 70);
      v83 = *(_DWORD *)(lpAddress + 278736);
      v84 = *(_DWORD *)(lpAddress + 278740);
      *(_DWORD *)(v83 - 90) = *(_DWORD *)(v84 + 72);
      *(_DWORD *)(v83 - 86) = *(_DWORD *)(v84 + 76);
      *(_DWORD *)(v83 - 82) = *(_DWORD *)(v84 + 80);
      *(_DWORD *)(v83 - 78) = *(_DWORD *)(v84 + 84);
      *(_WORD *)(v83 - 74) = *(_WORD *)(v84 + 88);
      v85 = *(_DWORD *)(lpAddress + 278736);
      v86 = *(_DWORD *)(lpAddress + 278740);
      *(_DWORD *)(v85 - 108) = *(_DWORD *)(v86 + 90);
      *(_DWORD *)(v85 - 104) = *(_DWORD *)(v86 + 94);
      *(_DWORD *)(v85 - 100) = *(_DWORD *)(v86 + 98);
      *(_DWORD *)(v85 - 96) = *(_DWORD *)(v86 + 102);
      *(_WORD *)(v85 - 92) = *(_WORD *)(v86 + 106);
      v87 = *(_DWORD *)(lpAddress + 278736);
      v88 = *(_DWORD *)(lpAddress + 278740);
      *(_DWORD *)(v87 - 126) = *(_DWORD *)(v88 + 108);
      *(_DWORD *)(v87 - 122) = *(_DWORD *)(v88 + 112);
      *(_DWORD *)(v87 - 118) = *(_DWORD *)(v88 + 116);
      *(_DWORD *)(v87 - 114) = *(_DWORD *)(v88 + 120);
      *(_WORD *)(v87 - 110) = *(_WORD *)(v88 + 124);
      v89 = *(_DWORD *)(lpAddress + 278736);
      v90 = *(_DWORD *)(lpAddress + 278740);
      *(_DWORD *)(v89 - 144) = *(_DWORD *)(v90 + 126);
      *(_DWORD *)(v89 - 140) = *(_DWORD *)(v90 + 130);
      *(_DWORD *)(v89 - 136) = *(_DWORD *)(v90 + 134);
      *(_DWORD *)(v89 - 132) = *(_DWORD *)(v90 + 138);
      *(_WORD *)(v89 - 128) = *(_WORD *)(v90 + 142);
      *(_WORD *)(*(_DWORD *)(lpAddress + 278736) + 2) = 0;
      if ( i > 0 )
      {
        for ( j = 0; j < i; ++j )
        {
          v92 = sub_41A130((__m128 *)lpAddress, v47, a3, nullptr, nullptr);
          v93 = sub_414620(
                  (unsigned __int16 *)(lpAddress + 8 * *(_DWORD *)(lpAddress + 278704) + 940072),
                  lpAddress + 278708);
          v94 = (unsigned __int8)(v92 + *(_BYTE *)(v93 + lpAddress + 280496));
          v97[j] = v94;
          sub_41CAB0(lpAddress, a4, v94, v93, v94 - v92);
          a5 = &v97[j + 1];
        }
        v47 = 0;
      }
      ++v96;
    }
    while ( v96 < a7 - 1 );
  }
  sub_414920();
}

#ifndef BMF_STANDALONE
// __userpurge thunk for sub_422DB0 @ 0x00422DB0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and pops 12 bytes of
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_422DB0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $52, %esp\n"
    "mov %ecx, 4(%esp)\n"
    "mov %esi, 8(%esp)\n"
    "movups %xmm1, 20(%esp)\n"
    "movups %xmm3, 36(%esp)\n"
    "push 16(%ebp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "lea 48(%esp), %eax\n"
    "push %eax\n"
    "lea 36(%esp), %eax\n"
    "push %eax\n"
    "push 28(%esp)\n"
    "push 28(%esp)\n"
    "call __sub_422DB0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret $12\n"
  );
}
#endif

#undef sub_414620
#undef sub_414920
#undef sub_4149C0
#undef sub_41A130
#undef sub_41CAB0
#undef sub_434980
