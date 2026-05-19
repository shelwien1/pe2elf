// =====================================================================
// sub_140009620 @ 0x140009620
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___arch_hdr
#define __PE_DECL___arch_hdr
typedef int t_arch_hdr[16];
static t_arch_hdr& __arch_hdr = *(t_arch_hdr*)0x140028E50;
#endif
#define arch_hdr __arch_hdr
#ifndef __PE_DECL___byte_1400227B0
#define __PE_DECL___byte_1400227B0
typedef char t_byte_1400227B0[16];
static t_byte_1400227B0& __byte_1400227B0 = *(t_byte_1400227B0*)0x1400227B0;
#endif
#define byte_1400227B0 __byte_1400227B0
#ifndef __PE_DECL___dword_14113364C
#define __PE_DECL___dword_14113364C
static int& __dword_14113364C = *(int*)0x14113364C;
#endif
#define dword_14113364C __dword_14113364C
#ifndef __PE_DECL___dword_141133650
#define __PE_DECL___dword_141133650
static int& __dword_141133650 = *(int*)0x141133650;
#endif
#define dword_141133650 __dword_141133650
#ifndef __PE_DECL___dword_141133654
#define __PE_DECL___dword_141133654
static int& __dword_141133654 = *(int*)0x141133654;
#endif
#define dword_141133654 __dword_141133654
#ifndef __PE_DECL___dword_141133658
#define __PE_DECL___dword_141133658
static int& __dword_141133658 = *(int*)0x141133658;
#endif
#define dword_141133658 __dword_141133658
#ifndef __PE_DECL___dword_141133690
#define __PE_DECL___dword_141133690
static int& __dword_141133690 = *(int*)0x141133690;
#endif
#define dword_141133690 __dword_141133690
#ifndef __PE_DECL___dword_1411336D8
#define __PE_DECL___dword_1411336D8
static int& __dword_1411336D8 = *(int*)0x1411336D8;
#endif
#define dword_1411336D8 __dword_1411336D8
#ifndef __PE_DECL___qword_14025F220
#define __PE_DECL___qword_14025F220
typedef __int64 t_qword_14025F220[1];
static t_qword_14025F220& __qword_14025F220 = *(t_qword_14025F220*)0x14025F220;
#endif
#define qword_14025F220 __qword_14025F220
#ifndef __PE_DECL___qword_141133550
#define __PE_DECL___qword_141133550
static __int64& __qword_141133550 = *(__int64*)0x141133550;
#endif
#define qword_141133550 __qword_141133550
#ifndef __PE_DECL___qword_141133558
#define __PE_DECL___qword_141133558
static __int64& __qword_141133558 = *(__int64*)0x141133558;
#endif
#define qword_141133558 __qword_141133558
#ifndef __PE_DECL___qword_141133560
#define __PE_DECL___qword_141133560
static __int64& __qword_141133560 = *(__int64*)0x141133560;
#endif
#define qword_141133560 __qword_141133560
#ifndef __PE_DECL___qword_141133568
#define __PE_DECL___qword_141133568
static __int64& __qword_141133568 = *(__int64*)0x141133568;
#endif
#define qword_141133568 __qword_141133568
#ifndef __PE_DECL___qword_141133570
#define __PE_DECL___qword_141133570
static __int64& __qword_141133570 = *(__int64*)0x141133570;
#endif
#define qword_141133570 __qword_141133570
#ifndef __PE_DECL___qword_141133580
#define __PE_DECL___qword_141133580
static __int64& __qword_141133580 = *(__int64*)0x141133580;
#endif
#define qword_141133580 __qword_141133580
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
#ifndef __PE_DECL___qword_141133620
#define __PE_DECL___qword_141133620
static __int64& __qword_141133620 = *(__int64*)0x141133620;
#endif
#define qword_141133620 __qword_141133620
#ifndef __PE_DECL___qword_141133638
#define __PE_DECL___qword_141133638
static __int64& __qword_141133638 = *(__int64*)0x141133638;
#endif
#define qword_141133638 __qword_141133638
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

// ---- PE-internal function references --------------------------------
#define sub_14000A2B0 __sub_14000A2B0
#define sub_14000A4B0 __sub_14000A4B0
#define sub_140010A40 __sub_140010A40
#define sub_140011240 __sub_140011240

PROBE_DECL(__sub_140009620)
__attribute__((ms_abi)) __int64 __sub_140009620() {

  PROBE_HIT(__sub_140009620);
  __int64 v0;            // r15
  unsigned __int8 *v1;   // rdi
  int v2;                // r13d
  int v3;                // r14d
  unsigned int v4;       // eax
  unsigned __int8 *v5;   // rbx
  char v6;               // r9
  unsigned int v7;       // eax
  __int64 result;        // rax
  __int64 v9;            // r10
  __int64 v10;           // rsi
  unsigned __int64 v11;  // rdx
  __int64 v12;           // r12
  unsigned int v13;      // r11d
  __int64 v14;           // rbp
  __int64 v15;           // rcx
  __int64 v16;           // rdx
  __int64 v17;           // rdi
  int v18;               // eax
  char v19;              // r15
  unsigned int v20;      // r9d
  unsigned int v21;      // r12d
  __int64 v22;           // r13
  _DWORD *v23;           // rdi
  unsigned int v24;      // r14d
  unsigned int v25;      // edx
  __int64 v26;           // rcx
  __int64 v27;           // r10
  _DWORD *v28;           // rcx
  _DWORD *v29;           // rax
  unsigned __int64 v30;  // r11
  bool v31;              // zf
  _DWORD *v32;           // rcx
  __int64 v33;           // r10
  unsigned int v34;      // r11d
  unsigned int v35;      // ebx
  unsigned int v36;      // ecx
  __int64 v37;           // r10
  _DWORD *v38;           // rdx
  __int64 v39;           // r10
  __int64 v40;           // rdx
  unsigned int v41;      // r14d
  unsigned int v42;      // r10d
  int v43;               // edx
  unsigned int v44;      // edx
  __int64 v45;           // r13
  __int64 v46;           // r10
  int v47;               // ecx
  _DWORD *v48;           // rdx
  _DWORD *v49;           // r10
  _DWORD *v50;           // rdx
  int v51;               // edi
  unsigned int v52;      // edi
  __int64 v53;           // rdx
  unsigned __int64 v54;  // rcx
  int v55;               // edi
  _DWORD *v56;           // r12
  __int64 v57;           // rcx
  __int64 v58;           // rdi
  bool v59;              // zf
  int v60;               // edx
  int v61;               // edx
  char v62;              // r12
  __int64 v63;           // r10
  signed __int64 v64;    // rcx
  unsigned __int64 v65;  // rdx
  int v66;               // ecx
  __int64 v67;           // r8
  __int64 *v68;          // r15
  unsigned __int8 *v69;  // rbx
  unsigned int v70;      // eax
  __int64 v71;           // rsi
  unsigned int v72;      // edx
  __int64 v73;           // rdi
  __int64 v74;           // r8
  _DWORD *v75;           // r9
  int v76;               // r10d
  __int64 v77;           // rbp
  __int64 v78;           // r14
  __int64 v79;           // rdx
  _BOOL8 v80;            // r15
  unsigned int v81;      // eax
  __int64 v82;           // r12
  __int64 v83;           // r15
  unsigned int v84;      // ebx
  unsigned int v85;      // r12d
  int v86;               // r15d
  __int64 v87;           // r13
  unsigned int v88;      // r12d
  __int64 v89;           // r12
  __int64 v90;           // r14
  int v91;               // eax
  _DWORD *v92;           // r13
  __int64 v93;           // r15
  _DWORD *v94;           // r12
  int v95;               // edx
  __int64 v96;           // rax
  int v97;               // eax
  int v98;               // [rsp+20h] [rbp-B8h]
  unsigned int v99;      // [rsp+20h] [rbp-B8h]
  __int64 v100;          // [rsp+20h] [rbp-B8h]
  unsigned int v101;     // [rsp+28h] [rbp-B0h]
  unsigned __int8 *v102; // [rsp+28h] [rbp-B0h]
  unsigned __int8 v103;  // [rsp+30h] [rbp-A8h]
  __int64 *v104;         // [rsp+30h] [rbp-A8h]
  char v105;             // [rsp+38h] [rbp-A0h]
  char v106;             // [rsp+38h] [rbp-A0h]
  unsigned int v107;     // [rsp+40h] [rbp-98h]
  unsigned int v108;     // [rsp+40h] [rbp-98h]
  unsigned int v109;     // [rsp+40h] [rbp-98h]
  unsigned int v110;     // [rsp+40h] [rbp-98h]
  unsigned __int8 *v111; // [rsp+48h] [rbp-90h]
  unsigned __int8 *v112; // [rsp+48h] [rbp-90h]
  unsigned __int8 *v113; // [rsp+48h] [rbp-90h]
  __int64 v114;          // [rsp+50h] [rbp-88h]
  __int64 v115;          // [rsp+50h] [rbp-88h]
  __int64 v116;          // [rsp+50h] [rbp-88h]
  int v117;              // [rsp+58h] [rbp-80h]
  __int64 v118;          // [rsp+60h] [rbp-78h]
  unsigned __int64 v119; // [rsp+68h] [rbp-70h]
  __int64 v120;          // [rsp+70h] [rbp-68h]
  __int64 v121;          // [rsp+78h] [rbp-60h]
  __int64 v122;          // [rsp+80h] [rbp-58h]
  __int16 v123;          // [rsp+88h] [rbp-50h]

  v0 = qword_141133638;
  v1 = (unsigned __int8 *)qword_141133610;
  v2 = dword_141133690;
  v3 = dword_141133654;
  v4 = *(_DWORD *)(qword_141133610 + 2);
  v123 = *(_WORD *)qword_141133610;
  v5 = (unsigned __int8 *)qword_141133638;
  v122 = qword_141133638;
  v6 = *((_BYTE *)xmmword_140028F00 + (unsigned __int8)*(_WORD *)qword_141133610);
  if(dword_141133690 == dword_141133654 && v4) {
    v7 = sub_14000A2B0(1, (unsigned __int64)qword_14025F220, qword_141133580);
    *(_DWORD *)(v1 + 2) = v7;
    if(v7) {
      result = qword_141133588 + v7;
      qword_141133638 = result;
      qword_141133580 = result;
      return result;
    }
    goto LABEL_73;
  }
  v9 = qword_141133560;
  v10 = qword_141133588;
  *(_BYTE *)qword_141133560 = *(_WORD *)qword_141133610;
  v11 = qword_141133568;
  v12 = v9 + 1;
  qword_141133560 = v9 + 1;
  v13 = v9 + 1 - v10;
  if(v9 + 1 >= (unsigned __int64)qword_141133568)
    goto LABEL_73;
  *(_BYTE *)(v9 + 1) = 0;
  if(!v4) {
    v14 = qword_141133580;
    v65 = qword_141133620;
    v66 = *v1;
    v112 = v5;
    v67 = qword_141133580;
    v115 = v0;
    v68 = qword_14025F220;
    while(1) {
      if((unsigned __int64)v68 >= v65) {
        if(*(_BYTE *)v67) {
          v69 = (unsigned __int8 *)(v10 + *(unsigned int *)(v67 + 4));
          if(*v69 != v66) {
            do {
              v97 = v69[6];
              v69 += 6;
            } while(v66 != v97);
          }
        } else {
          v69 = (unsigned __int8 *)(v67 + 2);
        }
        *v68++ = (__int64)v69;
      } else {
        v69 = (unsigned __int8 *)*v68++;
      }
      v4 = *(_DWORD *)(v69 + 2);
      if(v4)
        break;
      *(_DWORD *)(v69 + 2) = v13;
      v70 = *(_DWORD *)(v67 + 8);
      dword_141133690 = --v2;
      if(!v70) {
        v5 = v112;
        v0 = v115;
        v4 = v67 - v10;
        goto LABEL_9;
      }
      v67 = v10 + v70;
    }
    v102 = v69;
    v5 = v112;
    v104 = v68;
    v0 = v115;
    if(v4 <= v13) {
      v100 = v9;
      v110 = v9 + 1 - v10;
      v106 = v6;
      v4 = sub_14000A2B0(0, (unsigned __int64)(v104 - 1), v67);
      v6 = v106;
      v13 = v110;
      v9 = v100;
      *(_DWORD *)(v102 + 2) = v4;
    }
    if(v2 == v3 - 1 && v14 == v115) {
      *(_DWORD *)(v1 + 2) = v4;
      v4 = *(_DWORD *)(v102 + 2);
      v12 = v9;
      qword_141133560 = v9;
    }
  LABEL_9:
    if(v4) {
      v15 = v4;
      goto LABEL_11;
    }
  LABEL_73:
    if(!dword_141133658)
      return sub_140010A40(2);
    if(*(_BYTE *)v0 == 1) {
      v71 = qword_141133570;
      if(!*v5 && (unsigned __int8 *)v0 != v5) {
        v73 = qword_141133588;
        v74 = LOBYTE(arch_hdr[12]);
        v116 = v0;
        v75 = (_DWORD *)(qword_141133570 + 12LL * LOBYTE(arch_hdr[12]));
        v76 = qword_141133570 + 12 * LOBYTE(arch_hdr[12]) - qword_141133588;
        v98 = qword_141133570 - qword_141133588 + 444;
        v77 = v122;
        do {
          v78 = *(unsigned int *)(v77 + 4);
          v79 = v73 + v78;
          v80 = *(unsigned __int8 *)(v73 + v78) != v5[2];
          *(_BYTE *)(v77 + 1) = *((_BYTE *)xmmword_140028F00 + *(unsigned __int8 *)(v73 + v78 + 6 * v80));
          *(_BYTE *)(v73 + v78 + 6 * v80 + 1) = ((unsigned int)*(unsigned __int8 *)(v73 + v78 + 6 * v80 + 1) + 3) >> 2;
          *(_WORD *)(v77 + 2) = *(_WORD *)(v73 + v78 + 6 * v80);
          *(_DWORD *)(v77 + 4) = *(_DWORD *)(v73 + v78 + 6 * v80 + 2);
          v81 = *((unsigned __int8 *)&xmmword_141133520 + v74);
          *(_BYTE *)v77 = 0;
          if(*(unsigned __int8 *)(12LL * v81 + v73 + v78 + 1) == 255) {
            v82 = 12LL * v81;
            do {
              *(_DWORD *)(*(unsigned int *)(v82 + v79 + 4) + v73 + 8) = *(_DWORD *)(v82 + v79 + 8);
              *(_DWORD *)(*(unsigned int *)(v82 + v79 + 8) + v73 + 4) = *(_DWORD *)(v82 + v79 + 4);
              v83 = 12LL * *((unsigned __int8 *)&arch_hdr[11] + *(unsigned __int8 *)(v82 + v79) + 3);
              --*(_DWORD *)(v83 + v71);
              v81 += *(unsigned __int8 *)(v79 + v82);
              v82 = 12LL * v81;
            } while(*(unsigned __int8 *)(v82 + v79 + 1) == 255);
            if(v81 > 0x80) {
              v113 = v5;
              v84 = v81;
              v85 = 0;
              v86 = 0;
              v87 = -((__int64)(((unsigned __int64)((1LL - v81) >> 6) >> 57) - v81 + 1) >> 7);
              do {
                v81 = v86 + v84 - 128;
                v86 -= 128;
                ++v85;
              } while(v85 < (unsigned int)v87);
              v88 = 0;
              do {
                *(_BYTE *)(v79 + 1) = -1;
                *(_DWORD *)(v79 + 8) = v98;
                ++v88;
                *(_BYTE *)v79 = 0x80;
                *(_DWORD *)(v79 + 4) = *(_DWORD *)(v71 + 448);
                *(_DWORD *)(v73 + *(unsigned int *)(v71 + 448) + 8) = v78;
                ++*(_DWORD *)(v71 + 444);
                *(_DWORD *)(v71 + 448) = v78;
                v78 += 1536;
                v79 += 1536;
              } while(v88 < (unsigned int)v87);
              v5 = v113;
            }
            v89 = *((unsigned __int8 *)&arch_hdr[11] + v81 + 3);
            LODWORD(v90) = *((unsigned __int8 *)&xmmword_141133520 + v89);
            if(v81 != (_DWORD)v90) {
              v89 = (unsigned int)(v89 - 1);
              v90 = *((unsigned __int8 *)&xmmword_141133520 + v89);
              v91 = v81 - v90;
              v92 = (_DWORD *)(v71 + 12LL * (unsigned int)(v91 - 1));
              v93 = v79 + 12 * v90;
              *(_BYTE *)(v93 + 1) = -1;
              *(_BYTE *)v93 = v91;
              *(_DWORD *)(v93 + 8) = v71 + 12 * (v91 - 1) - v73;
              *(_DWORD *)(v93 + 4) = v92[1];
              LODWORD(v93) = v93 - v73;
              *(_DWORD *)((unsigned int)v92[1] + v73 + 8) = v93;
              v92[1] = v93;
              ++*v92;
            }
            *(_BYTE *)(v79 + 1) = -1;
            v94 = (_DWORD *)(v71 + 12 * v89);
            *(_BYTE *)v79 = v90;
            *(_DWORD *)(v79 + 8) = (_DWORD)v94 - v73;
            *(_DWORD *)(v79 + 4) = v94[1];
            v95 = v79 - v73;
            *(_DWORD *)((unsigned int)v94[1] + v73 + 8) = v95;
            v94[1] = v95;
            ++*v94;
          } else {
            *(_BYTE *)(v79 + 1) = -1;
            *(_BYTE *)v79 = v81;
            *(_DWORD *)(v79 + 8) = v76;
            *(_DWORD *)(v79 + 4) = v75[1];
            *(_DWORD *)((unsigned int)v75[1] + v73 + 8) = v78;
            v75[1] = v78;
            ++*v75;
          }
          v77 = v73 + *(unsigned int *)(v77 + 8);
        } while((unsigned __int8 *)v77 != v5);
        v0 = v116;
      }
    } else {
      v71 = qword_141133570;
    }
    v72 = *(_DWORD *)(v0 + 8);
    if(v72) {
      do {
        v0 = qword_141133588 + v72;
        v72 = *(_DWORD *)(v0 + 8);
      } while(v72);
      qword_141133638 = v0;
    }
    result = sub_14000A4B0((unsigned __int8 *)v0, 0);
    ++dword_14113364C;
    dword_141133650 = 0;
    qword_141133560 = v71 + 456;
    qword_141133580 = v0;
    dword_141133690 = 0;
    return result;
  }
  v14 = qword_141133580;
  v15 = v4;
  if(v11 > v10 + (unsigned __int64)v4) {
    v107 = v9 + 1 - v10;
    v105 = v6;
    v4 = sub_14000A2B0(0, (unsigned __int64)qword_14025F220, qword_141133580);
    v6 = v105;
    v13 = v107;
    goto LABEL_9;
  }
LABEL_11:
  v16 = v10 + v15;
  v17 = *(unsigned int *)(v10 + v15 + 8);
  dword_141133690 = v2 + 1;
  _mm_prefetch((const char *)(v17 + v10), 1);
  if(dword_141133690 == v3) {
    v13 = v4;
    qword_141133560 = v12 - (v0 != v14);
  }
  result = *(unsigned int *)(v15 + v10 + 4);
  _mm_prefetch((const char *)(result + v10), 1);
  if(v0 != v14) {
    v119 = qword_141133550;
    v18 = dword_1411336D8 + 8;
    v120 = qword_141133570;
    v121 = v10 + v15;
    v114 = v0;
    if(dword_1411336D8 + 8 >= 14)
      v18 = 14;
    if(v18 < 0)
      v18 = 0;
    v19 = v6;
    v117 = qword_141133570 - v10 + 444;
    v118 = v18;
    v20 = v13;
    while(1) {
      v21 = *v5 + 1;
      if(*v5) {
        if((v21 & 1) != 0) {
          v53 = *((unsigned int *)v5 + 1);
        } else {
          v22 = *((unsigned int *)v5 + 1);
          v23 = (_DWORD *)(v10 + v22);
          v24 = v21 >> 1;
          v25 = *((unsigned __int8 *)&arch_hdr[11] + (v21 >> 1) + 3);
          v26 = v21 >> 1;
          if(v25 != *((unsigned __int8 *)&arch_hdr[12] + v26)) {
            v27 = *((unsigned __int8 *)&arch_hdr[12] + v26);
            v28 = (_DWORD *)(v120 + 12 * v27);
            if(*v28) {
              v29 = (_DWORD *)(v10 + (unsigned int)v28[1]);
              v28[1] = v29[1];
              *(_DWORD *)((unsigned int)v29[1] + v10 + 8) = (_DWORD)v28 - v10;
              --*v28;
            } else {
              v29 = (_DWORD *)qword_141133558;
              v30 = 12 * (unsigned int)*((unsigned __int8 *)&xmmword_141133520 + v27);
              v31 = qword_141133558 + v30 == v119;
              if(qword_141133558 + v30 > v119) {
                v99 = *((unsigned __int8 *)&arch_hdr[11] + v24 + 3);
                v108 = v20;
                v29 = (_DWORD *)sub_140011240(v27);
                v20 = v108;
                v25 = v99;
              } else {
                qword_141133558 += v30;
                if(!v31)
                  v29[v30 / 4] = 0;
              }
            }
            if(v29) {
              v32 = v29;
              v33 = v10 + v22;
              if((v21 & 2) != 0) {
                *v29 = *v23;
                v29[1] = v23[1];
                v29[2] = v23[2];
                v32 = v29 + 3;
                v33 = v10 + v22 + 12;
              }
              if((v24 & 0xFFFFFFFE) != 0) {
                v111 = v5;
                v34 = 0;
                v35 = 0;
                do {
                  v32[v35] = *(_DWORD *)(v33 + v35 * 4);
                  ++v34;
                  v32[v35 + 1] = *(_DWORD *)(v33 + v35 * 4 + 4);
                  v32[v35 + 2] = *(_DWORD *)(v33 + v35 * 4 + 8);
                  v32[v35 + 3] = *(_DWORD *)(v33 + v35 * 4 + 12);
                  v32[v35 + 4] = *(_DWORD *)(v33 + v35 * 4 + 16);
                  v32[v35 + 5] = *(_DWORD *)(v33 + v35 * 4 + 20);
                  v35 += 6;
                } while(v34 < v21 >> 2);
                v5 = v111;
              }
              v36 = *((unsigned __int8 *)&xmmword_141133520 + v25);
              v37 = *((unsigned __int8 *)&xmmword_141133520 + v25);
              if(BYTE1(v23[3 * v37]) == 255) {
                v39 = 3 * v37;
                do {
                  *(_DWORD *)((unsigned int)v23[v39 + 1] + v10 + 8) = v23[v39 + 2];
                  *(_DWORD *)((unsigned int)v23[v39 + 2] + v10 + 4) = v23[v39 + 1];
                  v40 = 12LL * *((unsigned __int8 *)&arch_hdr[11] + LOBYTE(v23[v39]) + 3);
                  --*(_DWORD *)(v40 + v120);
                  v36 += LOBYTE(v23[v39]);
                  v39 = 3LL * v36;
                } while(BYTE1(v23[v39]) == 255);
                v41 = v36;
                if(v36 > 0x80) {
                  v42 = 0;
                  v101 = -(int)((__int64)(((unsigned __int64)((1LL - v36) >> 6) >> 57) - v36 + 1) >> 7);
                  v43 = 0;
                  do {
                    v36 = v43 + v41 - 128;
                    v43 -= 128;
                    ++v42;
                  } while(v42 < v101);
                  v44 = 0;
                  do {
                    *((_BYTE *)v23 + 1) = -1;
                    v23[2] = v117;
                    ++v44;
                    *(_BYTE *)v23 = 0x80;
                    v23[1] = *(_DWORD *)(v120 + 448);
                    *(_DWORD *)(*(unsigned int *)(v120 + 448) + v10 + 8) = v22;
                    ++*(_DWORD *)(v120 + 444);
                    *(_DWORD *)(v120 + 448) = v22;
                    v22 += 1536;
                    v23 += 384;
                  } while(v44 < v101);
                }
                v45 = *((unsigned __int8 *)&arch_hdr[11] + v36 + 3);
                v103 = *((_BYTE *)&xmmword_141133520 + v45);
                if(v36 != v103) {
                  v45 = (unsigned int)(v45 - 1);
                  v46 = *((unsigned __int8 *)&xmmword_141133520 + v45);
                  v103 = *((_BYTE *)&xmmword_141133520 + v45);
                  v47 = v36 - v46;
                  v48 = (_DWORD *)(v120 + 12LL * (unsigned int)(v47 - 1));
                  v49 = &v23[3 * v46];
                  *((_BYTE *)v49 + 1) = -1;
                  *(_BYTE *)v49 = v47;
                  v49[2] = (_DWORD)v48 - v10;
                  v49[1] = v48[1];
                  LODWORD(v49) = (_DWORD)v49 - v10;
                  *(_DWORD *)((unsigned int)v48[1] + v10 + 8) = (_DWORD)v49;
                  ++*v48;
                  v48[1] = (_DWORD)v49;
                }
                *((_BYTE *)v23 + 1) = -1;
                v50 = (_DWORD *)(v120 + 12 * v45);
                *(_BYTE *)v23 = v103;
                v23[2] = (_DWORD)v50 - v10;
                v23[1] = v50[1];
                v51 = (_DWORD)v23 - v10;
                *(_DWORD *)((unsigned int)v50[1] + v10 + 8) = v51;
                ++*v50;
                v50[1] = v51;
              } else {
                *((_BYTE *)v23 + 1) = -1;
                v38 = (_DWORD *)(v120 + 12LL * v25);
                *(_BYTE *)v23 = v36;
                v23[2] = (_DWORD)v38 - v10;
                v23[1] = v38[1];
                *(_DWORD *)((unsigned int)v38[1] + v10 + 8) = v22;
                ++*v38;
                v38[1] = v22;
              }
            }
            v23 = v29;
          }
          if(!v23)
            goto LABEL_99;
          v52 = (_DWORD)v23 - v10;
          v53 = v52;
          *((_DWORD *)v5 + 1) = v52;
        }
        v54 = v53 + v10 + 6LL * v21;
        if(v54 > v10 + v53 + 42) {
          do {
            v55 = *(_DWORD *)(v54 - 4);
            *(_WORD *)v54 = *(_WORD *)(v54 - 6);
            *(_DWORD *)(v54 + 2) = v55;
            v54 -= 6LL;
          } while(v54 > v10 + (unsigned __int64)*((unsigned int *)v5 + 1) + 42);
        }
      } else {
        v56 = (_DWORD *)(v120 + 12LL * LOBYTE(arch_hdr[12]));
        if(*v56) {
          v57 = v10 + (unsigned int)v56[1];
          v56[1] = *(_DWORD *)(v57 + 4);
          *(_DWORD *)(*(unsigned int *)(v57 + 4) + v10 + 8) = (_DWORD)v56 - v10;
          --*v56;
        } else {
          v57 = qword_141133558;
          v58 = 12 * (unsigned int)*((unsigned __int8 *)&xmmword_141133520 + LOBYTE(arch_hdr[12]));
          v59 = qword_141133558 + v58 == v119;
          if(qword_141133558 + v58 > v119) {
            v109 = v20;
            v96 = sub_140011240(LOBYTE(arch_hdr[12]));
            v20 = v109;
            v57 = v96;
          } else {
            qword_141133558 += v58;
            if(!v59)
              *(_DWORD *)(v58 + v57) = 0;
          }
        }
        if(!v57) {
        LABEL_99:
          v0 = v114;
          goto LABEL_73;
        }
        *(_WORD *)v57 = *((_WORD *)v5 + 1);
        v60 = byte_1400227B0[v118];
        *(_DWORD *)(v57 + 2) = *((_DWORD *)v5 + 1);
        *((_DWORD *)v5 + 1) = v57 - v10;
        v61 = 4 * *(unsigned __int8 *)(v57 + 1) + v60;
        if(v61 >= 238)
          v61 = 238;
        if(v61 < 2)
          LOBYTE(v61) = 2;
        *(_BYTE *)(v57 + 1) = v61;
        v54 = v57 + 6;
        *((_WORD *)v5 + 1) = (unsigned __int8)v61;
      }
      *(_BYTE *)(v54 + 1) = 0;
      *(_DWORD *)(v54 + 2) = v20;
      *(_BYTE *)v54 = v123;
      v62 = v5[1] & 0xF0;
      v63 = v10 + *((unsigned int *)v5 + 1);
      ++*v5;
      v64 = v54 - v63;
      result = 0x2AAAAAAAAAAAAAABLL * v64;
      v5[1] = v19 | (v64 / 6) | v62;
      v5 = (unsigned __int8 *)(v10 + *((unsigned int *)v5 + 2));
      if(v5 == (unsigned __int8 *)v14) {
        v16 = v121;
        break;
      }
    }
  }
  qword_141133580 = v16;
  qword_141133638 = v16;
  return result;
}
// 140028E50: using guessed type int arch_hdr[16];
// 140028F00: using guessed type __int128 xmmword_140028F00[];
// 14025F220: using guessed type __int64 qword_14025F220[];
// 141133520: using guessed type __int128 xmmword_141133520;
// 141133550: using guessed type __int64 qword_141133550;
// 141133558: using guessed type __int64 qword_141133558;
// 141133560: using guessed type __int64 qword_141133560;
// 141133568: using guessed type __int64 qword_141133568;
// 141133570: using guessed type __int64 qword_141133570;
// 141133580: using guessed type __int64 qword_141133580;
// 141133588: using guessed type __int64 qword_141133588;
// 141133610: using guessed type __int64 qword_141133610;
// 141133620: using guessed type __int64 qword_141133620;
// 141133638: using guessed type __int64 qword_141133638;
// 14113364C: using guessed type int dword_14113364C;
// 141133650: using guessed type int dword_141133650;
// 141133654: using guessed type int dword_141133654;
// 141133658: using guessed type int dword_141133658;
// 141133690: using guessed type int dword_141133690;
// 1411336D8: using guessed type int dword_1411336D8;

// ---- Cleanup --------------------------------------------------------
#undef arch_hdr
#undef byte_1400227B0
#undef dword_14113364C
#undef dword_141133650
#undef dword_141133654
#undef dword_141133658
#undef dword_141133690
#undef dword_1411336D8
#undef qword_14025F220
#undef qword_141133550
#undef qword_141133558
#undef qword_141133560
#undef qword_141133568
#undef qword_141133570
#undef qword_141133580
#undef qword_141133588
#undef qword_141133610
#undef qword_141133620
#undef qword_141133638
#undef xmmword_140028F00
#undef xmmword_141133520
#undef sub_14000A2B0
#undef sub_14000A4B0
#undef sub_140010A40
#undef sub_140011240
#undef FILE
