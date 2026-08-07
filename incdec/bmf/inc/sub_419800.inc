// sub_419800 @ 0x00419800 — __userpurge
// Extracted from BMF.cpp:23806-24275 by extract.py per incdec.md.

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980
static inline int __fwd_sub_419800_sub_414390(void *a0, int a1, int a2) { return __sub_414390((unsigned __int16 *)a0, a1, a2); }
#define sub_414390 __fwd_sub_419800_sub_414390
#define sub_414CE0 __sub_414CE0
#define sub_414F60 __sub_414F60
static inline int __fwd_sub_419800_sub_41A130(void *a0, const __m128 &a1, const __m128 &a2, void *a3, void *a4) { return __sub_41A130((__m128 *)a0, a1, a2, (_DWORD *)a3, (_DWORD *)a4); }
#define sub_41A130 __fwd_sub_419800_sub_41A130
#define sub_41CAB0 __sub_41CAB0

PROBE_DECL(__sub_419800)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) void __sub_419800(__m128 *lpAddress, const __m128 &a2__ref, const __m128 &a3__ref, _BYTE *a4, int i, int a6, _BYTE *a7)
{
  alignas(16) unsigned char __hexrays_frame[68];   // original frame, ebp-0x34..ebp+0x0
  int &j = *(int *)(__hexrays_frame + 0);
  unsigned int &v102 = *(unsigned int *)(__hexrays_frame + 0);
  _BYTE * &v103 = *(_BYTE * *)(__hexrays_frame + 4);
  int &v104 = *(int *)(__hexrays_frame + 8);
  _BYTE * &v105 = *(_BYTE * *)(__hexrays_frame + 8);
  __int8 * &v106 = *(__int8 * *)(__hexrays_frame + 12);
  char &v107 = *(char *)(__hexrays_frame + 16);
  __m128 * &lpAddress_1 = *(__m128 * *)(__hexrays_frame + 20);
  _BYTE * &v109 = *(_BYTE * *)(__hexrays_frame + 24);
  unsigned __int8 &v110 = *(unsigned __int8 *)(__hexrays_frame + 32);
  PROBE_HIT(__sub_419800);
  __m128 a2 = a2__ref;
  __m128 a3 = a3__ref;
  _BYTE *v8; // ebx
  char v10; // fps
  __int32 v11; // eax
  int v12; // eax
  int v13; // ebx
  char v14; // al
  int n16; // ecx
  __int32 v16; // edi
  int v17; // ebx
  _WORD *v18; // ebx
  __int64 v19; // rax
  int v20; // edi
  int v21; // edx
  int v22; // ecx
  __int32 v23; // edx
  int v24; // ecx
  int v25; // edi
  __int16 v26; // ax
  __int32 v27; // eax
  int v28; // ecx
  int v29; // edi
  __int32 v30; // edx
  int v31; // ecx
  int v32; // edi
  int v33; // eax
  __int32 v34; // eax
  int v35; // edi
  int v36; // ecx
  int v37; // edx
  __int32 v38; // edi
  int v39; // edx
  __int32 v40; // ecx
  __int32 v41; // edi
  __int32 v42; // ecx
  __int32 v43; // edi
  __int32 v44; // ecx
  __int32 v45; // edi
  __int32 v46; // ecx
  int Size; // edi
  char v48; // fps
  char v49; // fps
  __m128 v50; // xmm0
  __int32 v51; // edi
  int v52; // eax
  int *v53; // ecx
  __int32 v54; // ebp
  int v55; // edi
  _OWORD *v56; // eax
  __int32 v57; // edx
  int v58; // ebp
  int v59; // edi
  int v60; // eax
  __int32 v61; // eax
  int v62; // ebp
  int v63; // edi
  int v64; // edx
  __int32 v65; // edi
  int v66; // ebp
  int v67; // edx
  int v68; // eax
  __int32 v69; // ebp
  int v70; // eax
  int v71; // edx
  __int32 v72; // ecx
  int v73; // edi
  int v74; // eax
  __int32 v75; // edx
  __int32 v76; // ebp
  __int32 v77; // eax
  __int32 v78; // ecx
  __int32 v79; // edi
  __int32 v80; // eax
  __int32 v81; // edx
  __int32 v82; // ebp
  __int32 v83; // edi
  __int32 v84; // edx
  __int32 v85; // ecx
  __int32 v86; // edi
  __int32 v87; // eax
  __int32 v88; // ecx
  __int32 v89; // ebp
  __int32 v90; // eax
  __int32 v91; // edx
  __int32 v92; // ebp
  __int32 v93; // edi
  unsigned int k; // edi
  int v95; // ebx
  int v96; // edx
  char v97; // al
  int n16_1; // esi
  int v99; // edx
  int v100; // eax

  v8 = a4;
  sub_414F60();
  v11 = lpAddress[17421].m128_i32[0];
  if ( i > 0 )
  {
    v103 = a4;
    for ( j = 0; j < i; ++j )
    {
      v12 = *(unsigned __int16 *)(v11 - 18) >> 4;
      v13 = (unsigned __int8)(*v103 - v12);
      v104 = lpAddress[17499].m128_u8[v13];
      v14 = lpAddress[17531].m128_i8[v104] + v12;
      n16 = (unsigned __int8)*a7 - (unsigned __int8)(v14 + *a7 - *v103);
      if ( n16 < -16 || n16 > 16 )
      {
        *a7 = *v103;
        v104 = lpAddress[17515].m128_u8[v13];
      }
      else
      {
        *a7 = v14;
      }
      v16 = lpAddress[17421].m128_i32[0];
      v17 = *(__int16 *)(v16 - 18) >> 4;
      lpAddress[17419].m128_i32[1] = lpAddress[17419].m128_i32[0] + lpAddress[17435].m128_i32[v17];
      lpAddress[17419].m128_i32[2] = lpAddress[17419].m128_i32[0] + lpAddress[17434].m128_i32[v17];
      sub_414390(
        &lpAddress[58754].m128_u16[4 * lpAddress[17419].m128_i32[0]
                                 + 4
                                 + 4
                                 * lpAddress[17426].m128_i32[(*(__int16 *)(v16 - 18) <= *(__int16 *)(v16 - 36))
                                                           + 3
                                                           + (*(__int16 *)(v16 - 18) < *(__int16 *)(v16 - 36))]
                                 + 4 * lpAddress[17425].m128_i32[*(unsigned __int8 *)(v16 - 20) + 3]
                                 + 4 * lpAddress[17424].m128_i32[*(unsigned __int8 *)(v16 - 2) + 3]
                                 + 4
                                 * lpAddress[17423].m128_i32[((unsigned int)(v17 - 115) >> 31)
                                                           + 3
                                                           + ((unsigned int)(v17 - 17) >> 31)]
                                 + 4 * lpAddress[17428].m128_i32[0]],
        (int)&lpAddress[17419].m128_i32[1],
        v104);
      ++v103;
      LOWORD(v16) = 16 * (unsigned __int8)*a7;
      *(_WORD *)lpAddress[17421].m128_i32[0] = v16;
      *(_WORD *)(lpAddress[17421].m128_i32[0] + 2) = v16;
      ++a7;
      v18 = (_WORD *)lpAddress[17421].m128_i32[0];
      v19 = (__int16)(*v18 - *(v18 - 9));
      v18[2] = v19;
      LOWORD(v19) = (WORD2(v19) ^ v19) - WORD2(v19);
      *(_WORD *)(lpAddress[17421].m128_i32[0] + 6) = v19;
      *(_WORD *)(lpAddress[17421].m128_i32[0] + 14) = v19;
      *(_WORD *)(lpAddress[17421].m128_i32[0] + 12) = v19;
      *(_WORD *)(lpAddress[17421].m128_i32[0] + 10) = v19;
      *(_WORD *)(lpAddress[17421].m128_i32[0] + 8) = (unsigned int)*(__int16 *)(lpAddress[17421].m128_i32[0] + 10) >> 1;
      *(_BYTE *)(lpAddress[17421].m128_i32[0] + 17) = 2;
      *(_BYTE *)(lpAddress[17421].m128_i32[0] + 16) = (*(__int16 *)(lpAddress[17421].m128_i32[0] + 4) <= 0)
                                                    + (*(__int16 *)(lpAddress[17421].m128_i32[0] + 4) < 0);
      v11 = lpAddress[17421].m128_i32[0] + 18;
      lpAddress[17421].m128_i32[0] = v11;
    }
    v8 = v103;
  }
  v20 = *(_DWORD *)(v11 - 14);
  v21 = *(_DWORD *)(v11 - 10);
  *(_DWORD *)v11 = *(_DWORD *)(v11 - 18);
  v22 = *(_DWORD *)(v11 - 6);
  *(_DWORD *)(v11 + 4) = v20;
  LOWORD(v20) = *(_WORD *)(v11 - 2);
  *(_DWORD *)(v11 + 8) = v21;
  *(_DWORD *)(v11 + 12) = v22;
  *(_WORD *)(v11 + 16) = v20;
  v23 = lpAddress[17421].m128_i32[0];
  v24 = *(_DWORD *)(v23 - 10);
  v25 = *(_DWORD *)(v23 - 6);
  *(_DWORD *)(v23 + 18) = *(_DWORD *)(v23 - 18);
  *(_DWORD *)(v23 + 22) = *(_DWORD *)(v23 - 14);
  v26 = *(_WORD *)(v23 - 2);
  *(_DWORD *)(v23 + 26) = v24;
  *(_DWORD *)(v23 + 30) = v25;
  *(_WORD *)(v23 + 34) = v26;
  v27 = lpAddress[17421].m128_i32[0];
  v28 = *(_DWORD *)(v27 - 10);
  v29 = *(_DWORD *)(v27 - 6);
  *(_DWORD *)(v27 + 36) = *(_DWORD *)(v27 - 18);
  *(_DWORD *)(v27 + 40) = *(_DWORD *)(v27 - 14);
  LOWORD(v23) = *(_WORD *)(v27 - 2);
  *(_DWORD *)(v27 + 44) = v28;
  *(_DWORD *)(v27 + 48) = v29;
  *(_WORD *)(v27 + 52) = v23;
  v30 = lpAddress[17421].m128_i32[0];
  v31 = *(_DWORD *)(v30 - 14);
  v32 = *(_DWORD *)(v30 - 10);
  *(_DWORD *)(v30 + 54) = *(_DWORD *)(v30 - 18);
  v33 = *(_DWORD *)(v30 - 6);
  *(_DWORD *)(v30 + 58) = v31;
  LOWORD(v31) = *(_WORD *)(v30 - 2);
  *(_DWORD *)(v30 + 62) = v32;
  *(_DWORD *)(v30 + 66) = v33;
  *(_WORD *)(v30 + 70) = v31;
  v34 = lpAddress[17421].m128_i32[0];
  v35 = *(_DWORD *)(v34 - 14);
  v36 = *(_DWORD *)(v34 - 6);
  *(_DWORD *)(v34 + 72) = *(_DWORD *)(v34 - 18);
  v37 = *(_DWORD *)(v34 - 10);
  *(_DWORD *)(v34 + 76) = v35;
  LOWORD(v35) = *(_WORD *)(v34 - 2);
  *(_DWORD *)(v34 + 80) = v37;
  *(_DWORD *)(v34 + 84) = v36;
  *(_WORD *)(v34 + 88) = v35;
  v38 = lpAddress[17421].m128_i32[0];
  v39 = -18 * i;
  *(_DWORD *)(v38 + v39 - 18) = *(_DWORD *)(v38 - 18 * i);
  *(_DWORD *)(v38 + v39 - 14) = *(_DWORD *)(v38 + v39 + 4);
  *(_DWORD *)(v38 + v39 - 10) = *(_DWORD *)(v38 + v39 + 8);
  *(_DWORD *)(v38 + v39 - 6) = *(_DWORD *)(v38 + v39 + 12);
  *(_WORD *)(v38 + v39 - 2) = *(_WORD *)(v38 + v39 + 16);
  v40 = lpAddress[17421].m128_i32[0];
  *(_DWORD *)(v40 + v39 - 36) = *(_DWORD *)(v40 + v39 + 18);
  *(_DWORD *)(v40 + v39 - 32) = *(_DWORD *)(v40 + v39 + 22);
  *(_DWORD *)(v40 + v39 - 28) = *(_DWORD *)(v40 + v39 + 26);
  *(_DWORD *)(v40 + v39 - 24) = *(_DWORD *)(v40 + v39 + 30);
  *(_WORD *)(v40 + v39 - 20) = *(_WORD *)(v40 + v39 + 34);
  v41 = lpAddress[17421].m128_i32[0];
  *(_DWORD *)(v41 + v39 - 54) = *(_DWORD *)(v41 + v39 + 36);
  *(_DWORD *)(v41 + v39 - 50) = *(_DWORD *)(v41 + v39 + 40);
  *(_DWORD *)(v41 + v39 - 46) = *(_DWORD *)(v41 + v39 + 44);
  *(_DWORD *)(v41 + v39 - 42) = *(_DWORD *)(v41 + v39 + 48);
  *(_WORD *)(v41 + v39 - 38) = *(_WORD *)(v41 + v39 + 52);
  v42 = lpAddress[17421].m128_i32[0];
  *(_DWORD *)(v42 + v39 - 72) = *(_DWORD *)(v42 + v39 + 54);
  *(_DWORD *)(v42 + v39 - 68) = *(_DWORD *)(v42 + v39 + 58);
  *(_DWORD *)(v42 + v39 - 64) = *(_DWORD *)(v42 + v39 + 62);
  *(_DWORD *)(v42 + v39 - 60) = *(_DWORD *)(v42 + v39 + 66);
  *(_WORD *)(v42 + v39 - 56) = *(_WORD *)(v42 + v39 + 70);
  v43 = lpAddress[17421].m128_i32[0];
  *(_DWORD *)(v43 + v39 - 90) = *(_DWORD *)(v43 + v39 + 72);
  *(_DWORD *)(v43 + v39 - 86) = *(_DWORD *)(v43 + v39 + 76);
  *(_DWORD *)(v43 + v39 - 82) = *(_DWORD *)(v43 + v39 + 80);
  *(_DWORD *)(v43 + v39 - 78) = *(_DWORD *)(v43 + v39 + 84);
  *(_WORD *)(v43 + v39 - 74) = *(_WORD *)(v43 + v39 + 88);
  v44 = lpAddress[17421].m128_i32[0];
  *(_DWORD *)(v44 + v39 - 108) = *(_DWORD *)(v44 + v39 + 90);
  *(_DWORD *)(v44 + v39 - 104) = *(_DWORD *)(v44 + v39 + 94);
  *(_DWORD *)(v44 + v39 - 100) = *(_DWORD *)(v44 + v39 + 98);
  *(_DWORD *)(v44 + v39 - 96) = *(_DWORD *)(v44 + v39 + 102);
  *(_WORD *)(v44 + v39 - 92) = *(_WORD *)(v44 + v39 + 106);
  v45 = lpAddress[17421].m128_i32[0];
  *(_DWORD *)(v45 + v39 - 126) = *(_DWORD *)(v45 + v39 + 108);
  *(_DWORD *)(v45 + v39 - 122) = *(_DWORD *)(v45 + v39 + 112);
  *(_DWORD *)(v45 + v39 - 118) = *(_DWORD *)(v45 + v39 + 116);
  *(_DWORD *)(v45 + v39 - 114) = *(_DWORD *)(v45 + v39 + 120);
  *(_WORD *)(v45 + v39 - 110) = *(_WORD *)(v45 + v39 + 124);
  v46 = lpAddress[17421].m128_i32[0];
  *(_DWORD *)(v46 + v39 - 144) = *(_DWORD *)(v46 + v39 + 126);
  *(_DWORD *)(v46 + v39 - 140) = *(_DWORD *)(v46 + v39 + 130);
  *(_DWORD *)(v46 + v39 - 136) = *(_DWORD *)(v46 + v39 + 134);
  *(_DWORD *)(v46 + v39 - 132) = *(_DWORD *)(v46 + v39 + 138);
  *(_WORD *)(v46 + v39 - 128) = *(_WORD *)(v46 + v39 + 142);
  Size = 18 * i + 234;
  sub_434980((char *)lpAddress[17422].m128_i32[2],(char *)lpAddress[17422].m128_i32[1],Size);
  sub_434980((char *)lpAddress[17422].m128_i32[3],(char *)lpAddress[17422].m128_i32[1],Size);
  sub_434980((char *)lpAddress[17423].m128_i32[0],(char *)lpAddress[17422].m128_i32[1],Size);
  if ( a6 > 1 )
  {
    v106 = &lpAddress[17419].m128_i8[4];
    v105 = a7;
    v50 = 0;
    v102 = 0;
    do
    {
      v51 = lpAddress[17416].m128_i32[3];
      v52 = *(_DWORD *)(v51 - 4);
      v109 = v8;
      *(_DWORD *)(v51 + 4) = v52;
      *(_DWORD *)lpAddress[17416].m128_i32[3] = v52;
      v53 = (int *)lpAddress[17416].m128_i32[1];
      v54 = lpAddress[17416].m128_i32[2];
      lpAddress[17416].m128_i32[1] = v54;
      lpAddress[17416].m128_i32[2] = (__int32)v53;
      v54 += 8;
      lpAddress[17416].m128_i32[3] = v54;
      v53 += 2;
      lpAddress[17417].m128_i32[0] = (__int32)v53;
      v55 = *v53;
      *(_DWORD *)(v54 - 4) = *v53;
      *(_DWORD *)(lpAddress[17416].m128_i32[3] - 8) = v55;
      lpAddress[17408].m128_u64[0] = v50.m128_u64[0];
      lpAddress[17408].m128_i32[2] = 0;
      lpAddress[17408].m128_i16[6] = 0;
      lpAddress[17408].m128_i8[14] = 0;
      lpAddress[17415].m128_u64[0] = v50.m128_u64[0];
      lpAddress[17415].m128_u64[1] = v50.m128_u64[0];
      v56 = (_OWORD *)(((unsigned int)&lpAddress[17408].m128_u32[3] + 3) & 0xFFFFFFF0);
      *v56 = v50;
      v56[1] = v50;
      v56[2] = v50;
      v56[3] = v50;
      v56[4] = v50;
      v56[5] = v50;
      v56[6] = v50;
      v57 = lpAddress[17421].m128_i32[0];
      v58 = *(_DWORD *)(v57 - 14);
      v59 = *(_DWORD *)(v57 - 10);
      v60 = *(_DWORD *)(v57 - 6);
      *(_DWORD *)v57 = *(_DWORD *)(v57 - 18);
      LOWORD(v53) = *(_WORD *)(v57 - 2);
      *(_DWORD *)(v57 + 4) = v58;
      *(_DWORD *)(v57 + 8) = v59;
      *(_DWORD *)(v57 + 12) = v60;
      *(_WORD *)(v57 + 16) = (_WORD)v53;
      v61 = lpAddress[17421].m128_i32[0];
      v62 = *(_DWORD *)(v61 - 32);
      v63 = *(_DWORD *)(v61 - 28);
      LOWORD(v53) = *(_WORD *)(v61 - 20);
      *(_DWORD *)(v61 + 18) = *(_DWORD *)(v61 - 36);
      v64 = *(_DWORD *)(v61 - 24);
      *(_DWORD *)(v61 + 22) = v62;
      *(_DWORD *)(v61 + 26) = v63;
      *(_DWORD *)(v61 + 30) = v64;
      *(_WORD *)(v61 + 34) = (_WORD)v53;
      v65 = lpAddress[17421].m128_i32[0];
      v66 = *(_DWORD *)(v65 - 50);
      v67 = *(_DWORD *)(v65 - 42);
      LOWORD(v53) = *(_WORD *)(v65 - 38);
      *(_DWORD *)(v65 + 36) = *(_DWORD *)(v65 - 54);
      v68 = *(_DWORD *)(v65 - 46);
      *(_DWORD *)(v65 + 40) = v66;
      *(_DWORD *)(v65 + 44) = v68;
      *(_DWORD *)(v65 + 48) = v67;
      *(_WORD *)(v65 + 52) = (_WORD)v53;
      v69 = lpAddress[17421].m128_i32[0];
      v70 = *(_DWORD *)(v69 - 64);
      v71 = *(_DWORD *)(v69 - 60);
      LOWORD(v53) = *(_WORD *)(v69 - 56);
      *(_DWORD *)(v69 + 54) = *(_DWORD *)(v69 - 72);
      *(_DWORD *)(v69 + 58) = *(_DWORD *)(v69 - 68);
      *(_DWORD *)(v69 + 62) = v70;
      *(_DWORD *)(v69 + 66) = v71;
      *(_WORD *)(v69 + 70) = (_WORD)v53;
      v72 = lpAddress[17421].m128_i32[0];
      v73 = *(_DWORD *)(v72 - 82);
      v74 = *(_DWORD *)(v72 - 78);
      LOWORD(v71) = *(_WORD *)(v72 - 74);
      *(_DWORD *)(v72 + 72) = *(_DWORD *)(v72 - 90);
      *(_DWORD *)(v72 + 76) = *(_DWORD *)(v72 - 86);
      *(_DWORD *)(v72 + 80) = v73;
      *(_DWORD *)(v72 + 84) = v74;
      *(_WORD *)(v72 + 88) = v71;
      v75 = lpAddress[17423].m128_i32[0];
      v76 = lpAddress[17423].m128_i32[1];
      v77 = lpAddress[17422].m128_i32[3];
      v78 = lpAddress[17422].m128_i32[2];
      v79 = lpAddress[17422].m128_i32[1];
      lpAddress[17423].m128_i32[1] = v75;
      lpAddress[17423].m128_i32[0] = v77;
      lpAddress[17422].m128_i32[3] = v78;
      lpAddress[17422].m128_i32[1] = v76;
      lpAddress[17422].m128_i32[2] = v79;
      v76 += 144;
      lpAddress[17421].m128_i32[0] = v76;
      v79 += 144;
      lpAddress[17421].m128_i32[1] = v79;
      lpAddress[17421].m128_i32[2] = v78 + 144;
      lpAddress[17421].m128_i32[3] = v77 + 144;
      lpAddress[17422].m128_i32[0] = v75 + 144;
      *(_DWORD *)(v76 - 18) = *(_DWORD *)v79;
      *(_DWORD *)(v76 - 14) = *(_DWORD *)(v79 + 4);
      *(_DWORD *)(v76 - 10) = *(_DWORD *)(v79 + 8);
      *(_DWORD *)(v76 - 6) = *(_DWORD *)(v79 + 12);
      *(_WORD *)(v76 - 2) = *(_WORD *)(v79 + 16);
      v80 = lpAddress[17421].m128_i32[0];
      v81 = lpAddress[17421].m128_i32[1];
      *(_DWORD *)(v80 - 36) = *(_DWORD *)(v81 + 18);
      *(_DWORD *)(v80 - 32) = *(_DWORD *)(v81 + 22);
      *(_DWORD *)(v80 - 28) = *(_DWORD *)(v81 + 26);
      *(_DWORD *)(v80 - 24) = *(_DWORD *)(v81 + 30);
      *(_WORD *)(v80 - 20) = *(_WORD *)(v81 + 34);
      v82 = lpAddress[17421].m128_i32[0];
      v83 = lpAddress[17421].m128_i32[1];
      *(_DWORD *)(v82 - 54) = *(_DWORD *)(v83 + 36);
      *(_DWORD *)(v82 - 50) = *(_DWORD *)(v83 + 40);
      *(_DWORD *)(v82 - 46) = *(_DWORD *)(v83 + 44);
      *(_DWORD *)(v82 - 42) = *(_DWORD *)(v83 + 48);
      *(_WORD *)(v82 - 38) = *(_WORD *)(v83 + 52);
      v84 = lpAddress[17421].m128_i32[0];
      v85 = lpAddress[17421].m128_i32[1];
      *(_DWORD *)(v84 - 72) = *(_DWORD *)(v85 + 54);
      *(_DWORD *)(v84 - 68) = *(_DWORD *)(v85 + 58);
      *(_DWORD *)(v84 - 64) = *(_DWORD *)(v85 + 62);
      *(_DWORD *)(v84 - 60) = *(_DWORD *)(v85 + 66);
      *(_WORD *)(v84 - 56) = *(_WORD *)(v85 + 70);
      v86 = lpAddress[17421].m128_i32[0];
      v87 = lpAddress[17421].m128_i32[1];
      *(_DWORD *)(v86 - 90) = *(_DWORD *)(v87 + 72);
      *(_DWORD *)(v86 - 86) = *(_DWORD *)(v87 + 76);
      *(_DWORD *)(v86 - 82) = *(_DWORD *)(v87 + 80);
      *(_DWORD *)(v86 - 78) = *(_DWORD *)(v87 + 84);
      *(_WORD *)(v86 - 74) = *(_WORD *)(v87 + 88);
      v88 = lpAddress[17421].m128_i32[0];
      v89 = lpAddress[17421].m128_i32[1];
      *(_DWORD *)(v88 - 108) = *(_DWORD *)(v89 + 90);
      *(_DWORD *)(v88 - 104) = *(_DWORD *)(v89 + 94);
      *(_DWORD *)(v88 - 100) = *(_DWORD *)(v89 + 98);
      *(_DWORD *)(v88 - 96) = *(_DWORD *)(v89 + 102);
      *(_WORD *)(v88 - 92) = *(_WORD *)(v89 + 106);
      v90 = lpAddress[17421].m128_i32[0];
      v91 = lpAddress[17421].m128_i32[1];
      *(_DWORD *)(v90 - 126) = *(_DWORD *)(v91 + 108);
      *(_DWORD *)(v90 - 122) = *(_DWORD *)(v91 + 112);
      *(_DWORD *)(v90 - 118) = *(_DWORD *)(v91 + 116);
      *(_DWORD *)(v90 - 114) = *(_DWORD *)(v91 + 120);
      *(_WORD *)(v90 - 110) = *(_WORD *)(v91 + 124);
      v92 = lpAddress[17421].m128_i32[0];
      v93 = lpAddress[17421].m128_i32[1];
      *(_DWORD *)(v92 - 144) = *(_DWORD *)(v93 + 126);
      *(_DWORD *)(v92 - 140) = *(_DWORD *)(v93 + 130);
      *(_DWORD *)(v92 - 136) = *(_DWORD *)(v93 + 134);
      *(_DWORD *)(v92 - 132) = *(_DWORD *)(v93 + 138);
      *(_WORD *)(v92 - 128) = *(_WORD *)(v93 + 142);
      *(_WORD *)(lpAddress[17421].m128_i32[0] + 2) = 0;
      if ( i > 0 )
      {
        lpAddress_1 = lpAddress;
        for ( k = 0; k < i; ++k )
        {
          v95 = sub_41A130(lpAddress_1, v50, a2, nullptr, nullptr);
          v107 = v109[k];
          v96 = (unsigned __int8)(v107 - v95);
          v97 = v95 + lpAddress_1[17531].m128_i8[lpAddress_1[17499].m128_u8[v96]];
          n16_1 = (unsigned __int8)v105[k] - (unsigned __int8)(v97 + v105[k] - v107);
          v99 = lpAddress_1[17499].m128_u8[v96];
          if ( n16_1 < -16 || n16_1 > 16 )
          {
            v105[k] = v107;
            v99 = lpAddress_1[17515].m128_u8[(unsigned __int8)(v107 - v95)];
          }
          else
          {
            v105[k] = v97;
          }
          v110 = v99;
          sub_414390(&lpAddress_1[58754].m128_u16[4 * lpAddress_1[17419].m128_i32[0] + 4], (int)v106, v99);
          sub_41CAB0((int)lpAddress_1, a3, (unsigned __int8)v105[k], v110, (unsigned __int8)v105[k] - v95);
          v8 = &v109[k + 1];
          v100 = (int)&v105[k + 1];
        }
        lpAddress = lpAddress_1;
        v105 = (_BYTE *)v100;
        v50 = 0;
      }
      ++v102;
    }
    while ( v102 < a6 - 1 );
  }
  sub_414CE0();
}

// __userpurge thunk for sub_419800 @ 0x00419800: reads the register arguments the
// caller passes, calls the moved body as cdecl, and pops 16 bytes of
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_419800()
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
    "movups %xmm1, 20(%esp)\n"
    "movups %xmm3, 36(%esp)\n"
    "push 20(%ebp)\n"
    "push 16(%ebp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "lea 52(%esp), %eax\n"
    "push %eax\n"
    "lea 40(%esp), %eax\n"
    "push %eax\n"
    "push 28(%esp)\n"
    "call __sub_419800\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret $16\n"
  );
}

#undef sub_414390
#undef sub_414CE0
#undef sub_414F60
#undef sub_41A130
#undef sub_41CAB0
#undef sub_434980
