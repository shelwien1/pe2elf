// =====================================================================
// sub_14000B750 @ 0x14000B750
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___arch_hdr
#define __PE_DECL___arch_hdr
typedef int t_arch_hdr[16];
static t_arch_hdr& __arch_hdr = *(t_arch_hdr*)0x140028E50;
#endif
#define arch_hdr __arch_hdr
#ifndef __PE_DECL___dword_141133654
#define __PE_DECL___dword_141133654
static int& __dword_141133654 = *(int*)0x141133654;
#endif
#define dword_141133654 __dword_141133654
#ifndef __PE_DECL___dword_141133690
#define __PE_DECL___dword_141133690
static int& __dword_141133690 = *(int*)0x141133690;
#endif
#define dword_141133690 __dword_141133690
#ifndef __PE_DECL___qword_141133570
#define __PE_DECL___qword_141133570
static __int64& __qword_141133570 = *(__int64*)0x141133570;
#endif
#define qword_141133570 __qword_141133570
#ifndef __PE_DECL___qword_141133588
#define __PE_DECL___qword_141133588
static __int64& __qword_141133588 = *(__int64*)0x141133588;
#endif
#define qword_141133588 __qword_141133588
#ifndef __PE_DECL___qword_141133610
#define __PE_DECL___qword_141133610
static __int64& __qword_141133610 = *(__int64*)0x141133610;
#endif
#define qword_141133610 __qword_141133610
#ifndef __PE_DECL___xmmword_140028F00
#define __PE_DECL___xmmword_140028F00
typedef __int128 t_xmmword_140028F00[1];
static t_xmmword_140028F00& __xmmword_140028F00 = *(t_xmmword_140028F00*)0x140028F00;
#endif
#define xmmword_140028F00 __xmmword_140028F00
#ifndef __PE_DECL___xmmword_141133520
#define __PE_DECL___xmmword_141133520
static __int128& __xmmword_141133520 = *(__int128*)0x141133520;
#endif
#define xmmword_141133520 __xmmword_141133520

PROBE_DECL(__sub_14000B750)
__attribute__((ms_abi)) __int64 __sub_14000B750(unsigned __int8 *a1) {

  PROBE_HIT(__sub_14000B750);
  int v2;               // r9d
  __int64 v3;           // rsi
  __int64 v4;           // rbp
  unsigned int v5;      // r11d
  int v6;               // r10d
  char v7;              // cl
  int v8;               // edx
  int v9;               // r8d
  int v10;              // r10d
  __int64 v11;          // rax
  __int16 v12;          // r13
  int v13;              // r14d
  int v14;              // r12d
  unsigned __int8 *v15; // rax
  unsigned __int8 *v16; // rdx
  int v17;              // r12d
  unsigned __int8 *i;   // r12
  int v19;              // r14d
  __int64 result;       // rax
  unsigned __int8 v21;  // r10
  __int64 v22;          // r8
  __int64 v23;          // r10
  unsigned __int8 v24;  // al
  unsigned int v25;     // r9d
  __int64 v26;          // rax
  __int64 v27;          // r11
  unsigned int v28;     // edx
  __int64 v29;          // r12
  _DWORD *v30;          // r11
  __int64 v31;          // r12
  unsigned __int8 *v32; // r9
  __int64 v33;          // r9
  unsigned int v34;     // r9d
  unsigned int v35;     // r13d
  int v36;              // r12d
  __int64 v37;          // r11
  unsigned int v38;     // r12d
  __int64 v39;          // r11
  __int64 v40;          // r9
  int v41;              // edx
  _DWORD *v42;          // r8
  __int64 v43;          // r12
  _DWORD *v44;          // rax
  int v45;              // r10d
  __int64 v46;          // r13
  __int64 v47;          // rdx
  unsigned int v48;     // r10d
  unsigned int v49;     // r12d
  unsigned int v50;     // r9d
  __int64 v51;          // rax
  _DWORD *v52;          // r8
  __int64 v53;          // r15
  _DWORD *v54;          // r9
  int v55;              // r14d
  __int64 v56;          // r8
  unsigned int v57;     // r10d
  unsigned int v58;     // r15d
  unsigned int v59;     // r11d
  unsigned int v60;     // r8d
  __int64 v61;          // r15
  __int64 v62;          // r9
  __int64 v63;          // r10
  unsigned int v64;     // r10d
  unsigned int v65;     // r9d
  int v66;              // r12d
  __int64 v67;          // r11
  unsigned int v68;     // r9d
  __int64 v69;          // r10
  __int64 v70;          // r9
  int v71;              // r8d
  _DWORD *v72;          // rbp
  __int64 v73;          // r11
  int v74;              // edx
  __int64 v75;          // r13
  __int64 v76;          // r10
  __int64 v77;          // r8
  unsigned int v78;     // r9d
  __int64 v79;          // r13
  __int64 v80;          // r12
  unsigned __int8 *j;   // r11
  __int64 v82;          // r11
  unsigned int v83;     // r12d
  unsigned int v84;     // r11d
  int v85;              // r14d
  __int64 v86;          // r13
  unsigned int v87;     // r11d
  __int64 v88;          // r11
  __int64 v89;          // r8
  int v90;              // r9d
  _DWORD *v91;          // rbp
  __int64 v92;          // r12
  int v93;              // r10d
  unsigned int v94;     // edx
  unsigned __int16 v95; // [rsp+28h] [rbp-40h]
  int v96;              // [rsp+2Ah] [rbp-3Eh]

  v2 = *a1;
  v3 = qword_141133588;
  v4 = *((unsigned int *)a1 + 1);
  v5 = v2 + 1;
  v6 = (unsigned __int8)(a1[1] & 0x40) >> 6;
  v7 = v6 + 1;
  v8 = 2 * v6 + 2;
  v9 = (1 << (v6 + 1)) - 1;
  v10 = -v6;
  if(dword_141133690 != dword_141133654)
    v10 = v8;
  v11 = qword_141133610;
  if(qword_141133610 != qword_141133588 + v4) {
    do {
      v12 = *(_WORD *)v11;
      v13 = *(_DWORD *)(v11 + 2);
      v14 = *(_DWORD *)(v11 - 4);
      *(_WORD *)v11 = *(_WORD *)(v11 - 6);
      *(_DWORD *)(v11 + 2) = v14;
      *(_WORD *)(v11 - 6) = v12;
      *(_DWORD *)(v11 - 4) = v13;
      v11 -= 6;
    } while(v11 != v3 + *((unsigned int *)a1 + 1));
  }
  v15 = (unsigned __int8 *)(v11 + 6LL * v5);
  v16 = v15 - 6;
  a1[1] = 0;
  *((_WORD *)a1 + 1) = 0;
  do {
    v15 -= 6;
    v17 = (v10 + v9 * v15[1]) >> v7;
    v15[1] = v17;
    *((_WORD *)a1 + 1) += (unsigned __int8)v17;
    if(v15[1]) {
      a1[1] |= *((_BYTE *)xmmword_140028F00 + *v15);
    } else {
      for(i = v15; i < v16; i += 6) {
        v19 = *((_DWORD *)i + 2);
        *(_WORD *)i = *((_WORD *)i + 3);
        *(_DWORD *)(i + 2) = v19;
      }
      i[1] = 0;
    }
    --v5;
  } while(v5);
  result = v16[1];
  if(v16[1]) {
    v94 = *((_DWORD *)a1 + 1);
  LABEL_61:
    a1[1] |= 0x40u;
    qword_141133610 = v94 + v3;
    return result;
  }
  do {
    LOBYTE(v5) = v5 + 1;
    v16 -= 6;
  } while(!v16[1]);
  v21 = *a1 - v5;
  *a1 = v21;
  if(v21) {
    v46 = *((unsigned int *)a1 + 1);
    v47 = v3 + v46;
    v48 = v21 + 2;
    v49 = *((unsigned __int8 *)&arch_hdr[11] + ((unsigned int)(v2 + 2) >> 1) + 3);
    result = (v48 >> 1) - 1;
    v50 = *((unsigned __int8 *)&arch_hdr[12] + result);
    if(v49 != v50) {
      v51 = qword_141133570;
      v52 = (_DWORD *)(qword_141133570 + 12LL * v50);
      if(*v52) {
        v53 = (unsigned int)v52[1];
        v54 = (_DWORD *)(v3 + v53);
        v52[1] = *(_DWORD *)(v3 + v53 + 4);
        *(_DWORD *)(*(unsigned int *)(v3 + v53 + 4) + v3 + 8) = (_DWORD)v52 - v3;
        v55 = v3 + v53;
        --*v52;
        v56 = v3 + v46;
        if(((v48 >> 1) & 1) != 0) {
          *v54 = *(_DWORD *)v47;
          v54[1] = *(_DWORD *)(v47 + 4);
          v54[2] = *(_DWORD *)(v47 + 8);
          v54 = (_DWORD *)(v3 + v53 + 12);
          v56 = v3 + v46 + 12;
        }
        v57 = v48 >> 2;
        if(v57) {
          v58 = 0;
          v59 = 0;
          do {
            v54[v59] = *(_DWORD *)(v56 + v59 * 4);
            ++v58;
            v54[v59 + 1] = *(_DWORD *)(v56 + v59 * 4 + 4);
            v54[v59 + 2] = *(_DWORD *)(v56 + v59 * 4 + 8);
            v54[v59 + 3] = *(_DWORD *)(v56 + v59 * 4 + 12);
            v54[v59 + 4] = *(_DWORD *)(v56 + v59 * 4 + 16);
            v54[v59 + 5] = *(_DWORD *)(v56 + v59 * 4 + 20);
            v59 += 6;
          } while(v58 < v57);
        }
        v60 = *((unsigned __int8 *)&xmmword_141133520 + v49);
        v61 = *((unsigned __int8 *)&xmmword_141133520 + v49);
        if(*(unsigned __int8 *)(12 * v61 + v47 + 1) == 255) {
          v62 = 12 * v61;
          do {
            *(_DWORD *)(*(unsigned int *)(v62 + v47 + 4) + v3 + 8) = *(_DWORD *)(v62 + v47 + 8);
            *(_DWORD *)(*(unsigned int *)(v62 + v47 + 8) + v3 + 4) = *(_DWORD *)(v62 + v47 + 4);
            v63 = 12LL * *((unsigned __int8 *)&arch_hdr[11] + *(unsigned __int8 *)(v62 + v47) + 3);
            --*(_DWORD *)(v63 + v51);
            v60 += *(unsigned __int8 *)(v47 + v62);
            v62 = 12LL * v60;
          } while(*(unsigned __int8 *)(v62 + v47 + 1) == 255);
          v64 = v60;
          if(v60 > 0x80) {
            v65 = 0;
            v66 = 0;
            v67 = -((__int64)(((unsigned __int64)((1LL - v60) >> 6) >> 57) - v60 + 1) >> 7);
            do {
              v60 = v66 + v64 - 128;
              v66 -= 128;
              ++v65;
            } while(v65 < (unsigned int)v67);
            v68 = 0;
            do {
              *(_BYTE *)(v47 + 1) = -1;
              *(_DWORD *)(v47 + 8) = v51 - v3 + 444;
              ++v68;
              *(_BYTE *)v47 = 0x80;
              *(_DWORD *)(v47 + 4) = *(_DWORD *)(v51 + 448);
              *(_DWORD *)(*(unsigned int *)(v51 + 448) + v3 + 8) = v46;
              ++*(_DWORD *)(v51 + 444);
              *(_DWORD *)(v51 + 448) = v46;
              v46 += 1536;
              v47 += 1536;
            } while(v68 < (unsigned int)v67);
          }
          v69 = *((unsigned __int8 *)&arch_hdr[11] + v60 + 3);
          LODWORD(v70) = *((unsigned __int8 *)&xmmword_141133520 + v69);
          if(v60 != (_DWORD)v70) {
            v69 = (unsigned int)(v69 - 1);
            v70 = *((unsigned __int8 *)&xmmword_141133520 + v69);
            v71 = v60 - v70;
            v72 = (_DWORD *)(v51 + 12LL * (unsigned int)(v71 - 1));
            v73 = v47 + 12 * v70;
            *(_BYTE *)(v73 + 1) = -1;
            *(_BYTE *)v73 = v71;
            *(_DWORD *)(v73 + 8) = (_DWORD)v72 - v3;
            *(_DWORD *)(v73 + 4) = v72[1];
            LODWORD(v73) = v73 - v3;
            *(_DWORD *)((unsigned int)v72[1] + v3 + 8) = v73;
            v72[1] = v73;
            ++*v72;
          }
          *(_BYTE *)(v47 + 1) = -1;
          result = 12 * v69 + v51;
          *(_BYTE *)v47 = v70;
          *(_DWORD *)(v47 + 8) = result - v3;
          *(_DWORD *)(v47 + 4) = *(_DWORD *)(result + 4);
          v74 = v47 - v3;
          *(_DWORD *)(*(unsigned int *)(result + 4) + v3 + 8) = v74;
          *(_DWORD *)(result + 4) = v74;
          ++*(_DWORD *)result;
        } else {
          *(_BYTE *)(v47 + 1) = -1;
          result = 12LL * v49 + v51;
          *(_BYTE *)v47 = v60;
          *(_DWORD *)(v47 + 8) = result - v3;
          *(_DWORD *)(v47 + 4) = *(_DWORD *)(result + 4);
          *(_DWORD *)(*(unsigned int *)(result + 4) + v3 + 8) = v46;
          *(_DWORD *)(result + 4) = v46;
          ++*(_DWORD *)result;
        }
        LODWORD(v47) = v55;
      } else {
        v75 = *((unsigned __int8 *)&xmmword_141133520 + v50);
        v76 = v47 + 12 * v75;
        v77 = v76 - v3;
        v78 = *((unsigned __int8 *)&xmmword_141133520 + v49) - (_DWORD)v75;
        v79 = v78;
        v80 = 12LL * v78;
        for(j = (unsigned __int8 *)(v76 + v80); *(unsigned __int8 *)(v76 + v80 + 1) == 255; j = (unsigned __int8 *)(v76 + v80)) {
          *(_DWORD *)(*((unsigned int *)j + 1) + v3 + 8) = *((_DWORD *)j + 2);
          *(_DWORD *)(*((unsigned int *)j + 2) + v3 + 4) = *((_DWORD *)j + 1);
          v82 = 12LL * *((unsigned __int8 *)&arch_hdr[11] + *j + 3);
          --*(_DWORD *)(v82 + v51);
          v78 += *(unsigned __int8 *)(v76 + v80);
          v79 = v78;
          v80 = 12LL * v78;
        }
        v83 = v78;
        if(v78 > 0x80) {
          v84 = 0;
          v85 = 0;
          v86 = -((__int64)(((unsigned __int64)((1 - v79) >> 6) >> 57) - v79 + 1) >> 7);
          do {
            v78 = v85 + v83 - 128;
            v85 -= 128;
            ++v84;
          } while(v84 < (unsigned int)v86);
          v87 = 0;
          do {
            *(_BYTE *)(v76 + 1) = -1;
            *(_DWORD *)(v76 + 8) = v51 - v3 + 444;
            ++v87;
            *(_BYTE *)v76 = 0x80;
            *(_DWORD *)(v76 + 4) = *(_DWORD *)(v51 + 448);
            *(_DWORD *)(*(unsigned int *)(v51 + 448) + v3 + 8) = v77;
            ++*(_DWORD *)(v51 + 444);
            *(_DWORD *)(v51 + 448) = v77;
            v77 += 1536;
            v76 += 1536;
          } while(v87 < (unsigned int)v86);
        }
        v88 = *((unsigned __int8 *)&arch_hdr[11] + v78 + 3);
        LODWORD(v89) = *((unsigned __int8 *)&xmmword_141133520 + v88);
        if(v78 != (_DWORD)v89) {
          v88 = (unsigned int)(v88 - 1);
          v89 = *((unsigned __int8 *)&xmmword_141133520 + v88);
          v90 = v78 - v89;
          v91 = (_DWORD *)(v51 + 12LL * (unsigned int)(v90 - 1));
          v92 = v76 + 12 * v89;
          *(_BYTE *)(v92 + 1) = -1;
          *(_BYTE *)v92 = v90;
          *(_DWORD *)(v92 + 8) = (_DWORD)v91 - v3;
          *(_DWORD *)(v92 + 4) = v91[1];
          LODWORD(v92) = v92 - v3;
          *(_DWORD *)((unsigned int)v91[1] + v3 + 8) = v92;
          v91[1] = v92;
          ++*v91;
        }
        *(_BYTE *)(v76 + 1) = -1;
        result = 12 * v88 + v51;
        *(_BYTE *)v76 = v89;
        *(_DWORD *)(v76 + 8) = result - v3;
        *(_DWORD *)(v76 + 4) = *(_DWORD *)(result + 4);
        v93 = v76 - v3;
        *(_DWORD *)(*(unsigned int *)(result + 4) + v3 + 8) = v93;
        *(_DWORD *)(result + 4) = v93;
        ++*(_DWORD *)result;
      }
    }
    v94 = v47 - v3;
    *((_DWORD *)a1 + 1) = v94;
    goto LABEL_61;
  }
  v22 = *((unsigned int *)a1 + 1);
  v23 = v3 + v22;
  v95 = *(_WORD *)(v3 + v22);
  v96 = *(_DWORD *)(v3 + v22 + 2);
  v24 = (v2 + ((v95 >> 7) & 0xFFFFFFFE)) / (__int64)(v2 + 1);
  v25 = v2 + 2;
  if(v24 >= 0x2Cu)
    v24 = 44;
  HIBYTE(v95) = v24;
  v26 = qword_141133570;
  v27 = *((unsigned __int8 *)&arch_hdr[11] + (v25 >> 1) + 3);
  v28 = *((unsigned __int8 *)&xmmword_141133520 + v27);
  v29 = *((unsigned __int8 *)&xmmword_141133520 + v27);
  if(*(unsigned __int8 *)(12 * v29 + v23 + 1) == 255) {
    v31 = 12 * v29;
    v32 = (unsigned __int8 *)(v23 + v31);
    do {
      *(_DWORD *)(*((unsigned int *)v32 + 1) + v3 + 8) = *((_DWORD *)v32 + 2);
      *(_DWORD *)(*((unsigned int *)v32 + 2) + v3 + 4) = *((_DWORD *)v32 + 1);
      v33 = 12LL * *((unsigned __int8 *)&arch_hdr[11] + *v32 + 3);
      --*(_DWORD *)(v33 + v26);
      v28 += *(unsigned __int8 *)(v23 + v31);
      v31 = 12LL * v28;
      v32 = (unsigned __int8 *)(v23 + v31);
    } while(*(unsigned __int8 *)(v23 + v31 + 1) == 255);
    v34 = v28;
    if(v28 > 0x80) {
      v35 = 0;
      v36 = 0;
      v37 = -((__int64)(((unsigned __int64)((1LL - v28) >> 6) >> 57) - v28 + 1) >> 7);
      do {
        v28 = v36 + v34 - 128;
        v36 -= 128;
        ++v35;
      } while(v35 < (unsigned int)v37);
      v38 = 0;
      do {
        *(_BYTE *)(v23 + 1) = -1;
        *(_DWORD *)(v23 + 8) = v26 - v3 + 444;
        ++v38;
        *(_BYTE *)v23 = 0x80;
        *(_DWORD *)(v23 + 4) = *(_DWORD *)(v26 + 448);
        *(_DWORD *)(*(unsigned int *)(v26 + 448) + v3 + 8) = v22;
        ++*(_DWORD *)(v26 + 444);
        *(_DWORD *)(v26 + 448) = v22;
        v22 += 1536;
        v23 += 1536;
      } while(v38 < (unsigned int)v37);
    }
    v39 = *((unsigned __int8 *)&arch_hdr[11] + v28 + 3);
    LODWORD(v40) = *((unsigned __int8 *)&xmmword_141133520 + v39);
    if(v28 != (_DWORD)v40) {
      v39 = (unsigned int)(v39 - 1);
      v40 = *((unsigned __int8 *)&xmmword_141133520 + v39);
      v41 = v28 - v40;
      v42 = (_DWORD *)(v26 + 12LL * (unsigned int)(v41 - 1));
      v43 = v23 + 12 * v40;
      *(_BYTE *)(v43 + 1) = -1;
      *(_BYTE *)v43 = v41;
      *(_DWORD *)(v43 + 8) = (_DWORD)v42 - v3;
      *(_DWORD *)(v43 + 4) = v42[1];
      LODWORD(v43) = v43 - v3;
      *(_DWORD *)((unsigned int)v42[1] + v3 + 8) = v43;
      v42[1] = v43;
      ++*v42;
    }
    *(_BYTE *)(v23 + 1) = -1;
    v44 = (_DWORD *)(12 * v39 + v26);
    *(_BYTE *)v23 = v40;
    *(_DWORD *)(v23 + 8) = (_DWORD)v44 - v3;
    *(_DWORD *)(v23 + 4) = v44[1];
    v45 = v23 - v3;
    *(_DWORD *)((unsigned int)v44[1] + v3 + 8) = v45;
    v44[1] = v45;
    ++*v44;
  } else {
    *(_BYTE *)(v23 + 1) = -1;
    v30 = (_DWORD *)(v26 + 12 * v27);
    *(_BYTE *)v23 = v28;
    *(_DWORD *)(v23 + 8) = (_DWORD)v30 - v3;
    *(_DWORD *)(v23 + 4) = v30[1];
    *(_DWORD *)((unsigned int)v30[1] + v3 + 8) = v22;
    v30[1] = v22;
    ++*v30;
  }
  qword_141133610 = (__int64)(a1 + 2);
  *((_WORD *)a1 + 1) = v95;
  *((_DWORD *)a1 + 1) = v96;
  a1[1] = *((_BYTE *)xmmword_140028F00 + (unsigned __int8)v95);
  return v95;
}
// 140028E50: using guessed type int arch_hdr[16];
// 140028F00: using guessed type __int128 xmmword_140028F00[];
// 141133520: using guessed type __int128 xmmword_141133520;
// 141133570: using guessed type __int64 qword_141133570;
// 141133588: using guessed type __int64 qword_141133588;
// 141133610: using guessed type __int64 qword_141133610;
// 141133654: using guessed type int dword_141133654;
// 141133690: using guessed type int dword_141133690;

// ---- Cleanup --------------------------------------------------------
#undef arch_hdr
#undef dword_141133654
#undef dword_141133690
#undef qword_141133570
#undef qword_141133588
#undef qword_141133610
#undef xmmword_140028F00
#undef xmmword_141133520
#undef FILE
