// =====================================================================
// sub_14000A4B0 @ 0x14000A4B0
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
#ifndef __PE_DECL___dword_141133654
#define __PE_DECL___dword_141133654
static int& __dword_141133654 = *(int*)0x141133654;
#endif
#define dword_141133654 __dword_141133654
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
#ifndef __PE_DECL___qword_141133588
#define __PE_DECL___qword_141133588
static __int64& __qword_141133588 = *(__int64*)0x141133588;
#endif
#define qword_141133588 __qword_141133588
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
// (self-reference for the recursive call is intentionally omitted; the
// body refers to sub_14000A4B0 which the #define below maps to the
// real C++ function symbol __sub_14000A4B0.)
#define sub_14000A4B0 __sub_14000A4B0
#ifndef __PE_DECL___sub_140011920
#define __PE_DECL___sub_140011920
typedef __attribute__((ms_abi)) char * t_sub_140011920(__int64 a1, unsigned int a2);
static t_sub_140011920& __sub_140011920 = *(t_sub_140011920*)0x140011920;
#endif
#define sub_140011920 __sub_140011920

PROBE_DECL(__sub_14000A4B0)
__attribute__((ms_abi)) __int64 __sub_14000A4B0(unsigned __int8 *a1, unsigned int a2) {

  PROBE_HIT(__sub_14000A4B0);
  unsigned __int8 *v3;   // r12
  __int64 v4;            // rsi
  int v5;                // r8d
  unsigned __int64 v6;   // rcx
  int v7;                // r13d
  int v8;                // eax
  _DWORD *v9;            // rdi
  _DWORD *v10;           // rbp
  unsigned __int8 *v11;  // rcx
  unsigned int v12;      // ebx
  __int64 v13;           // rax
  __int64 v14;           // r15
  unsigned int v15;      // r9d
  unsigned int v16;      // r8d
  int v17;               // edx
  __int64 v18;           // rax
  unsigned int v19;      // r8d
  __int64 v20;           // rdx
  __int64 v21;           // rax
  int v22;               // ebx
  __int64 v23;           // rcx
  _DWORD *v24;           // r14
  unsigned __int8 *v25;  // r11
  _DWORD *v26;           // rdi
  int v27;               // r12d
  _DWORD *v29;           // rax
  int v30;               // r12d
  unsigned __int8 *v31;  // rbx
  unsigned int v32;      // ebp
  __int64 v33;           // rdx
  __int64 v34;           // r14
  unsigned int v35;      // edi
  unsigned int v36;      // ecx
  int v37;               // edx
  __int64 v38;           // r8
  unsigned int v39;      // ecx
  __int64 v40;           // rcx
  __int64 v41;           // rdx
  int v42;               // ebp
  __int64 v43;           // rbx
  _DWORD *v44;           // r13
  unsigned __int8 *v45;  // r10
  _DWORD *v46;           // rax
  int v47;               // r12d
  unsigned __int8 v48;   // r14
  __int64 v49;           // r13
  unsigned __int8 *v50;  // rbp
  __int64 v51;           // r10
  const char *v52;       // rcx
  unsigned __int8 *v53;  // rax
  __int64 v54;           // rdx
  int v55;               // ebx
  unsigned int v56;      // r11d
  unsigned int v57;      // ecx
  __int64 v58;           // r14
  unsigned __int64 v59;  // r13
  unsigned __int8 *v60;  // r14
  __int16 v61;           // r10
  int v62;               // r9d
  int v63;               // edx
  signed int v64;        // r8d
  _DWORD *v65;           // rax
  __int64 v66;           // r14
  unsigned int v67;      // edx
  __int64 v68;           // rcx
  __int64 v69;           // r9
  _DWORD *v70;           // r10
  __int64 v71;           // r11
  unsigned __int8 *v72;  // r9
  __int64 v73;           // r13
  unsigned int v74;      // r11d
  unsigned int v75;      // r10d
  int v76;               // r8d
  __int64 v77;           // r9
  __int64 v78;           // r14
  unsigned int v79;      // r8d
  __int64 v80;           // r10
  __int64 v81;           // r9
  int v82;               // edx
  _DWORD *v83;           // r8
  unsigned __int8 *v84;  // r11
  _DWORD *v85;           // rcx
  int v86;               // ebp
  unsigned int v87;      // r9d
  unsigned int v88;      // r8d
  unsigned int v89;      // eax
  __int64 v90;           // r10
  _DWORD *v91;           // rcx
  __int64 v92;           // r11
  _DWORD *v93;           // rax
  unsigned __int8 *v94;  // rcx
  unsigned int v95;      // r9d
  unsigned int v96;      // r13d
  unsigned int v97;      // r11d
  unsigned int v98;      // eax
  __int64 v99;           // r13
  _DWORD *v100;          // r10
  __int64 v101;          // r11
  unsigned __int8 *v102; // r8
  __int64 v103;          // r13
  unsigned int v104;     // r11d
  unsigned int v105;     // r9d
  int v106;              // edx
  __int64 v107;          // r8
  __int64 v108;          // r14
  unsigned int v109;     // edx
  __int64 v110;          // r9
  __int64 v111;          // r8
  int v112;              // eax
  _DWORD *v113;          // rdx
  unsigned __int8 *v114; // r11
  _DWORD *v115;          // r10
  int v116;              // ebp
  int v117;              // r8d
  unsigned __int8 v118;  // r15
  int v119;              // ecx
  unsigned int v120;     // r8d
  unsigned int v121;     // r9d
  __int64 v122;          // rax
  __int64 v123;          // r9
  __int64 v124;          // r13
  _DWORD *v125;          // r8
  __int64 v126;          // r8
  unsigned int v127;     // r11d
  unsigned int v128;     // r14d
  unsigned int v129;     // ecx
  unsigned int v130;     // edx
  __int64 v131;          // r10
  unsigned __int8 *v132; // rcx
  __int64 v133;          // r11
  unsigned int v134;     // r11d
  unsigned int v135;     // r10d
  int v136;              // ecx
  __int64 v137;          // r8
  __int64 v138;          // r14
  unsigned int v139;     // ecx
  __int64 v140;          // r9
  __int64 v141;          // r8
  int v142;              // edx
  _DWORD *v143;          // rcx
  unsigned __int8 *v144; // r10
  _DWORD *v145;          // r13
  int v146;              // ebp
  char *v147;            // r15
  char *v148;            // rbp
  __int64 v149;          // rcx
  __int64 v150;          // rcx
  unsigned int v151;     // ebx
  __int64 v152;          // r8
  _DWORD *v153;          // r8
  __int64 v154;          // rcx
  unsigned __int8 *v155; // rdi
  __int64 v156;          // r14
  unsigned int v157;     // r8d
  unsigned int v158;     // edi
  int v159;              // ecx
  __int64 v160;          // rdx
  __int64 v161;          // r10
  unsigned int v162;     // edi
  __int64 v163;          // rcx
  __int64 v164;          // rdx
  int v165;              // ebx
  __int64 v166;          // rdi
  _DWORD *v167;          // r14
  unsigned __int8 *v168; // r11
  _DWORD *v169;          // r8
  int v170;              // ebp
  __int64 v171;          // [rsp+20h] [rbp-58h]
  __int64 v172;          // [rsp+28h] [rbp-50h]

  v3 = a1;
  v4 = qword_141133588;
  v5 = *a1;
  if(*a1) {
    v48 = a1[1];
    v172 = *((unsigned int *)a1 + 1);
    v49 = (unsigned int)(v5 + 1);
    v50 = (unsigned __int8 *)(qword_141133588 + v172);
    v51 = (unsigned int)(2 * v5 + 2);
    v52 = (const char *)(v51 + qword_141133588 + v172);
    _mm_prefetch((const char *)(qword_141133588 + v172 + v49), 1);
    _mm_prefetch(v52, 1);
    _mm_prefetch(&v52[v49], 1);
    _mm_prefetch(&v52[v51], 1);
    _mm_prefetch(&v52[v51 + v49], 1);
    _mm_prefetch(&v52[v51 - 1 + v51], 1);
    v53 = v50;
    v54 = (__int64)v50;
    v55 = v5;
    v56 = v5 + 2;
    v57 = (unsigned int)(v5 + 2) >> 1;
    v58 = 3LL * (v48 & 0xF);
    if(!v50[2 * v58 + 1]) {
      v50[2 * v58 + 1] = 8;
      *((_WORD *)v3 + 1) += 8;
    }
    v59 = qword_141133568;
    v60 = v50;
    do {
      if(v59 > v4 + (unsigned __int64)*(unsigned int *)(v53 + 2)) {
        *(_DWORD *)(v53 + 2) = 0;
        --v55;
      } else {
        if(v53 != v60) {
          v61 = *(_WORD *)v60;
          v62 = *(_DWORD *)(v60 + 2);
          *(_WORD *)v60 = *(_WORD *)v53;
          *(_DWORD *)(v60 + 2) = *(_DWORD *)(v53 + 2);
          *(_WORD *)v53 = v61;
          *(_DWORD *)(v53 + 2) = v62;
        }
        _mm_prefetch((const char *)(*(unsigned int *)(v60 + 2) + v4), 1);
        v60 += 6;
      }
      v53 += 6;
      --v5;
    } while(v5 >= 0);
    if(v55 == *v3 || !a2) {
      v122 = *((unsigned __int8 *)&arch_hdr[11] + v57 + 3);
      v123 = *((unsigned __int8 *)&xmmword_141133520 + v122);
      if(v50[12 * v123 + 1] == 255 && (v124 = qword_141133570, v125 = (_DWORD *)(qword_141133570 + 12 * v122), *v125)) {
        v171 = (unsigned int)v125[1];
        v65 = (_DWORD *)(v4 + v171);
        v125[1] = *(_DWORD *)(v4 + v171 + 4);
        *(_DWORD *)(*(unsigned int *)(v4 + v171 + 4) + v4 + 8) = (_DWORD)v125 - v4;
        --*v125;
        v126 = v4 + v171;
        if((v57 & 1) != 0) {
          *v65 = *(_DWORD *)v50;
          v65[1] = *((_DWORD *)v50 + 1);
          v65[2] = *((_DWORD *)v50 + 2);
          v126 = v4 + v171 + 12;
          v54 = v4 + v172 + 12;
        }
        v127 = v56 >> 2;
        if(v127) {
          v128 = 0;
          v129 = 0;
          do {
            *(_DWORD *)(v129 + v126) = *(_DWORD *)(v54 + v129);
            ++v128;
            *(_DWORD *)(v129 + v126 + 4) = *(_DWORD *)(v54 + v129 + 4);
            *(_DWORD *)(v129 + v126 + 8) = *(_DWORD *)(v54 + v129 + 8);
            *(_DWORD *)(v129 + v126 + 12) = *(_DWORD *)(v54 + v129 + 12);
            *(_DWORD *)(v129 + v126 + 16) = *(_DWORD *)(v54 + v129 + 16);
            *(_DWORD *)(v129 + v126 + 20) = *(_DWORD *)(v54 + v129 + 20);
            v129 += 24;
          } while(v128 < v127);
        }
        v130 = v123;
        if(v50[12 * v123 + 1] == 255) {
          v131 = 12 * v123;
          v132 = &v50[12 * v123];
          do {
            *(_DWORD *)(*((unsigned int *)v132 + 1) + v4 + 8) = *((_DWORD *)v132 + 2);
            *(_DWORD *)(*((unsigned int *)v132 + 2) + v4 + 4) = *((_DWORD *)v132 + 1);
            v133 = 12LL * *((unsigned __int8 *)&arch_hdr[11] + *v132 + 3);
            --*(_DWORD *)(v133 + v124);
            v130 += v50[v131];
            v123 = v130;
            v131 = 12LL * v130;
            v132 = &v50[v131];
          } while(v50[v131 + 1] == 255);
        }
        v134 = v130;
        if(v130 > 0x80) {
          v135 = 0;
          v136 = 0;
          v137 = -((__int64)(((unsigned __int64)((1 - v123) >> 6) >> 57) - v123 + 1) >> 7);
          do {
            v130 = v136 + v134 - 128;
            v136 -= 128;
            ++v135;
          } while(v135 < (unsigned int)v137);
          v138 = v172;
          v139 = 0;
          do {
            v50[1] = -1;
            *((_DWORD *)v50 + 2) = v124 - v4 + 444;
            ++v139;
            *v50 = 0x80;
            *((_DWORD *)v50 + 1) = *(_DWORD *)(v124 + 448);
            *(_DWORD *)(*(unsigned int *)(v124 + 448) + v4 + 8) = v138;
            ++*(_DWORD *)(v124 + 444);
            *(_DWORD *)(v124 + 448) = v138;
            v138 += 1536;
            v50 += 1536;
          } while(v139 < (unsigned int)v137);
        }
        v140 = *((unsigned __int8 *)&arch_hdr[11] + v130 + 3);
        LODWORD(v141) = *((unsigned __int8 *)&xmmword_141133520 + v140);
        if(v130 != (_DWORD)v141) {
          v140 = (unsigned int)(v140 - 1);
          v141 = *((unsigned __int8 *)&xmmword_141133520 + v140);
          v142 = v130 - v141;
          v143 = (_DWORD *)(v124 + 12LL * (unsigned int)(v142 - 1));
          v144 = &v50[12 * v141];
          *v144 = v142;
          v144[1] = -1;
          *((_DWORD *)v144 + 2) = (_DWORD)v143 - v4;
          *((_DWORD *)v144 + 1) = v143[1];
          LODWORD(v144) = (_DWORD)v144 - v4;
          *(_DWORD *)((unsigned int)v143[1] + v4 + 8) = (_DWORD)v144;
          ++*v143;
          v143[1] = (_DWORD)v144;
        }
        v50[1] = -1;
        v145 = (_DWORD *)(12 * v140 + v124);
        *v50 = v141;
        *((_DWORD *)v50 + 2) = (_DWORD)v145 - v4;
        *((_DWORD *)v50 + 1) = v145[1];
        v146 = (_DWORD)v50 - v4;
        *(_DWORD *)((unsigned int)v145[1] + v4 + 8) = v146;
        v145[1] = v146;
        ++*v145;
      } else {
        v65 = (_DWORD *)v50;
      }
      *((_DWORD *)v3 + 1) = (_DWORD)v65 - v4;
    } else {
      *v3 = v55;
      if(v55 < 0) {
        v150 = *((unsigned __int8 *)&arch_hdr[11] + v57 + 3);
        v151 = *((unsigned __int8 *)&xmmword_141133520 + v150);
        v152 = *((unsigned __int8 *)&xmmword_141133520 + v150);
        v29 = (_DWORD *)qword_141133570;
        if(v50[12 * v152 + 1] == 255) {
          v154 = 12 * v152;
          v155 = &v50[12 * v152];
          do {
            *(_DWORD *)(*((unsigned int *)v155 + 1) + v4 + 8) = *((_DWORD *)v155 + 2);
            *(_DWORD *)(*((unsigned int *)v155 + 2) + v4 + 4) = *((_DWORD *)v155 + 1);
            v156 = *((unsigned __int8 *)&arch_hdr[11] + *v155 + 3);
            --v29[3 * v156];
            v151 += v50[v154];
            v154 = 12LL * v151;
            v155 = &v50[v154];
          } while(v50[v154 + 1] == 255);
          v157 = v151;
          if(v151 > 0x80) {
            v158 = 0;
            v159 = 0;
            v160 = -((__int64)(((unsigned __int64)((1LL - v151) >> 6) >> 57) - v151 + 1) >> 7);
            do {
              v151 = v159 + v157 - 128;
              v159 -= 128;
              ++v158;
            } while(v158 < (unsigned int)v160);
            v161 = v172;
            v162 = 0;
            do {
              v50[1] = -1;
              *((_DWORD *)v50 + 2) = (_DWORD)v29 - v4 + 444;
              ++v162;
              *v50 = 0x80;
              *((_DWORD *)v50 + 1) = v29[112];
              *(_DWORD *)((unsigned int)v29[112] + v4 + 8) = v161;
              ++v29[111];
              v29[112] = v161;
              v161 += 1536;
              v50 += 1536;
            } while(v162 < (unsigned int)v160);
          }
          v163 = *((unsigned __int8 *)&arch_hdr[11] + v151 + 3);
          LODWORD(v164) = *((unsigned __int8 *)&xmmword_141133520 + v163);
          if(v151 != (_DWORD)v164) {
            v163 = (unsigned int)(v163 - 1);
            v164 = *((unsigned __int8 *)&xmmword_141133520 + v163);
            v165 = v151 - v164;
            v166 = (unsigned int)(v165 - 1);
            v167 = &v29[3 * v166];
            v168 = &v50[12 * v164];
            *v168 = v165;
            v168[1] = -1;
            *((_DWORD *)v168 + 2) = (_DWORD)v29 + 12 * v166 - v4;
            *((_DWORD *)v168 + 1) = v167[1];
            LODWORD(v168) = (_DWORD)v168 - v4;
            *(_DWORD *)((unsigned int)v167[1] + v4 + 8) = (_DWORD)v168;
            ++*v167;
            v167[1] = (_DWORD)v168;
          }
          v50[1] = -1;
          v169 = &v29[3 * v163];
          *v50 = v164;
          *((_DWORD *)v50 + 2) = (_DWORD)v29 + 12 * v163 - v4;
          *((_DWORD *)v50 + 1) = v169[1];
          v170 = (_DWORD)v50 - v4;
          *(_DWORD *)((unsigned int)v169[1] + v4 + 8) = v170;
          v169[1] = v170;
          ++*v169;
        } else {
          v50[1] = -1;
          v153 = &v29[3 * v150];
          *v50 = v151;
          *((_DWORD *)v50 + 2) = (_DWORD)v29 + 12 * v150 - v4;
          *((_DWORD *)v50 + 1) = v153[1];
          *(_DWORD *)((unsigned int)v153[1] + v4 + 8) = v172;
          v153[1] = v172;
          ++*v153;
        }
        goto LABEL_23;
      }
      if(v55) {
        v87 = (v55 + 2) >> 1;
        v88 = *((unsigned __int8 *)&arch_hdr[11] + v57 + 3);
        v89 = *((unsigned __int8 *)&arch_hdr[11] + v87 + 3);
        if(v88 != v89) {
          v90 = qword_141133570;
          v91 = (_DWORD *)(qword_141133570 + 12LL * *((unsigned __int8 *)&arch_hdr[11] + v87 + 3));
          if(*v91) {
            v92 = (unsigned int)v91[1];
            v93 = (_DWORD *)(v4 + v92);
            v91[1] = *(_DWORD *)(v4 + v92 + 4);
            *(_DWORD *)(*(unsigned int *)(v4 + v92 + 4) + v4 + 8) = (_DWORD)v91 - v4;
            --*v91;
            v94 = (unsigned __int8 *)(v4 + v92);
            if((v87 & 1) != 0) {
              *v93 = *(_DWORD *)v50;
              v93[1] = *((_DWORD *)v50 + 1);
              v93[2] = *((_DWORD *)v50 + 2);
              v93 = (_DWORD *)(v4 + v92 + 12);
              v54 = v4 + v172 + 12;
            }
            v95 = v87 >> 1;
            if(v95) {
              v96 = 0;
              v97 = 0;
              do {
                v93[v97] = *(_DWORD *)(v54 + v97 * 4);
                ++v96;
                v93[v97 + 1] = *(_DWORD *)(v54 + v97 * 4 + 4);
                v93[v97 + 2] = *(_DWORD *)(v54 + v97 * 4 + 8);
                v93[v97 + 3] = *(_DWORD *)(v54 + v97 * 4 + 12);
                v93[v97 + 4] = *(_DWORD *)(v54 + v97 * 4 + 16);
                v93[v97 + 5] = *(_DWORD *)(v54 + v97 * 4 + 20);
                v97 += 6;
              } while(v96 < v95);
            }
            v98 = *((unsigned __int8 *)&xmmword_141133520 + v88);
            v99 = *((unsigned __int8 *)&xmmword_141133520 + v88);
            if(v50[12 * v99 + 1] == 255) {
              v101 = 12 * v99;
              v102 = &v50[12 * v99];
              do {
                *(_DWORD *)(*((unsigned int *)v102 + 1) + v4 + 8) = *((_DWORD *)v102 + 2);
                *(_DWORD *)(*((unsigned int *)v102 + 2) + v4 + 4) = *((_DWORD *)v102 + 1);
                v103 = 12LL * *((unsigned __int8 *)&arch_hdr[11] + *v102 + 3);
                --*(_DWORD *)(v103 + v90);
                v98 += v50[v101];
                v101 = 12LL * v98;
                v102 = &v50[v101];
              } while(v50[v101 + 1] == 255);
              v104 = v98;
              if(v98 > 0x80) {
                v105 = 0;
                v106 = 0;
                v107 = -((__int64)(((unsigned __int64)((1LL - v98) >> 6) >> 57) - v98 + 1) >> 7);
                do {
                  v98 = v106 + v104 - 128;
                  v106 -= 128;
                  ++v105;
                } while(v105 < (unsigned int)v107);
                v108 = v172;
                v109 = 0;
                do {
                  v50[1] = -1;
                  *((_DWORD *)v50 + 2) = v90 - v4 + 444;
                  ++v109;
                  *v50 = 0x80;
                  *((_DWORD *)v50 + 1) = *(_DWORD *)(v90 + 448);
                  *(_DWORD *)(*(unsigned int *)(v90 + 448) + v4 + 8) = v108;
                  ++*(_DWORD *)(v90 + 444);
                  *(_DWORD *)(v90 + 448) = v108;
                  v108 += 1536;
                  v50 += 1536;
                } while(v109 < (unsigned int)v107);
              }
              v110 = *((unsigned __int8 *)&arch_hdr[11] + v98 + 3);
              LODWORD(v111) = *((unsigned __int8 *)&xmmword_141133520 + v110);
              if(v98 != (_DWORD)v111) {
                v110 = (unsigned int)(v110 - 1);
                v111 = *((unsigned __int8 *)&xmmword_141133520 + v110);
                v112 = v98 - v111;
                v113 = (_DWORD *)(v90 + 12LL * (unsigned int)(v112 - 1));
                v114 = &v50[12 * v111];
                *v114 = v112;
                v114[1] = -1;
                *((_DWORD *)v114 + 2) = (_DWORD)v113 - v4;
                *((_DWORD *)v114 + 1) = v113[1];
                LODWORD(v114) = (_DWORD)v114 - v4;
                *(_DWORD *)((unsigned int)v113[1] + v4 + 8) = (_DWORD)v114;
                ++*v113;
                v113[1] = (_DWORD)v114;
              }
              v50[1] = -1;
              v115 = (_DWORD *)(12 * v110 + v90);
              *v50 = v111;
              *((_DWORD *)v50 + 2) = (_DWORD)v115 - v4;
              *((_DWORD *)v50 + 1) = v115[1];
              v116 = (_DWORD)v50 - v4;
              *(_DWORD *)((unsigned int)v115[1] + v4 + 8) = v116;
              v115[1] = v116;
              ++*v115;
            } else {
              v50[1] = -1;
              v100 = (_DWORD *)(12LL * v88 + v90);
              *v50 = v98;
              *((_DWORD *)v50 + 2) = (_DWORD)v100 - v4;
              *((_DWORD *)v50 + 1) = v100[1];
              *(_DWORD *)((unsigned int)v100[1] + v4 + 8) = v172;
              v100[1] = v172;
              ++*v100;
            }
            v50 = v94;
          } else {
            sub_140011920((__int64)&v50[12 * *((unsigned __int8 *)&xmmword_141133520 + v89)], *((unsigned __int8 *)&xmmword_141133520 + v88) - *((unsigned __int8 *)&xmmword_141133520 + v89));
          }
        }
        v117 = *((unsigned __int16 *)v3 + 1);
        v118 = v3[1];
        v65 = (_DWORD *)v50;
        *((_DWORD *)v3 + 1) = (_DWORD)v50 - v4;
        v119 = v117 > 16 * v55;
        v3[1] = (((_BYTE)v119 << 6) & v118) + *((_BYTE *)xmmword_140028F00 + *v50);
        v120 = (v119 + (unsigned int)v50[1]) >> v119;
        v50[1] = v120;
        *((_WORD *)v3 + 1) = (unsigned __int8)v120;
        do {
          v50 += 6;
          v3[1] |= *((_BYTE *)xmmword_140028F00 + *v50);
          v121 = (v119 + (unsigned int)v50[1]) >> v119;
          v50[1] = v121;
          *((_WORD *)v3 + 1) += (unsigned __int8)v121;
          --v55;
        } while(v55);
        v55 = *v3;
      } else {
        v3[1] = *((_BYTE *)xmmword_140028F00 + *v53);
        v63 = v50[1];
        v64 = *((unsigned __int16 *)v3 + 1) - (v63 - 1) + 19;
        if(v64 < 2 * v63 - 2)
          LOBYTE(v64) = (v63 - 1) / v64 + 2;
        else
          v64 = (unsigned int)(v64 - (3 * v63 - 3)) >> 31;
        v50[1] = v64 + 1;
        v65 = (_DWORD *)(v3 + 2);
        *((_WORD *)v3 + 1) = *(_WORD *)v50;
        *((_DWORD *)v3 + 1) = *(_DWORD *)(v50 + 2);
        v66 = *((unsigned __int8 *)&arch_hdr[11] + v57 + 3);
        v67 = *((unsigned __int8 *)&xmmword_141133520 + v66);
        v68 = qword_141133570;
        v69 = *((unsigned __int8 *)&xmmword_141133520 + v66);
        if(v50[12 * v69 + 1] == 255) {
          v71 = 12 * v69;
          v72 = &v50[12 * v69];
          do {
            *(_DWORD *)(*((unsigned int *)v72 + 1) + v4 + 8) = *((_DWORD *)v72 + 2);
            *(_DWORD *)(*((unsigned int *)v72 + 2) + v4 + 4) = *((_DWORD *)v72 + 1);
            v73 = 12LL * *((unsigned __int8 *)&arch_hdr[11] + *v72 + 3);
            --*(_DWORD *)(v73 + v68);
            v67 += v50[v71];
            v71 = 12LL * v67;
            v72 = &v50[v71];
          } while(v50[v71 + 1] == 255);
          v74 = v67;
          if(v67 > 0x80) {
            v75 = 0;
            v76 = 0;
            v77 = -((__int64)(((unsigned __int64)((1LL - v67) >> 6) >> 57) - v67 + 1) >> 7);
            do {
              v67 = v76 + v74 - 128;
              v76 -= 128;
              ++v75;
            } while(v75 < (unsigned int)v77);
            v78 = v172;
            v79 = 0;
            do {
              v50[1] = -1;
              *((_DWORD *)v50 + 2) = v68 - v4 + 444;
              ++v79;
              *v50 = 0x80;
              *((_DWORD *)v50 + 1) = *(_DWORD *)(v68 + 448);
              *(_DWORD *)(*(unsigned int *)(v68 + 448) + v4 + 8) = v78;
              ++*(_DWORD *)(v68 + 444);
              *(_DWORD *)(v68 + 448) = v78;
              v78 += 1536;
              v50 += 1536;
            } while(v79 < (unsigned int)v77);
          }
          v80 = *((unsigned __int8 *)&arch_hdr[11] + v67 + 3);
          LODWORD(v81) = *((unsigned __int8 *)&xmmword_141133520 + v80);
          if(v67 != (_DWORD)v81) {
            v80 = (unsigned int)(v80 - 1);
            v81 = *((unsigned __int8 *)&xmmword_141133520 + v80);
            v82 = v67 - v81;
            v83 = (_DWORD *)(v68 + 12LL * (unsigned int)(v82 - 1));
            v84 = &v50[12 * v81];
            *v84 = v82;
            v84[1] = -1;
            *((_DWORD *)v84 + 2) = (_DWORD)v83 - v4;
            *((_DWORD *)v84 + 1) = v83[1];
            LODWORD(v84) = (_DWORD)v84 - v4;
            *(_DWORD *)((unsigned int)v83[1] + v4 + 8) = (_DWORD)v84;
            ++*v83;
            v83[1] = (_DWORD)v84;
          }
          v50[1] = -1;
          v85 = (_DWORD *)(12 * v80 + v68);
          *v50 = v81;
          *((_DWORD *)v50 + 2) = (_DWORD)v85 - v4;
          *((_DWORD *)v50 + 1) = v85[1];
          v86 = (_DWORD)v50 - v4;
          *(_DWORD *)((unsigned int)v85[1] + v4 + 8) = v86;
          v85[1] = v86;
          ++*v85;
        } else {
          v50[1] = -1;
          v70 = (_DWORD *)(v68 + 12 * v66);
          *v50 = v67;
          *((_DWORD *)v50 + 2) = v68 + 12 * v66 - v4;
          *((_DWORD *)v50 + 1) = v70[1];
          *(_DWORD *)((unsigned int)v70[1] + v4 + 8) = v172;
          v70[1] = v172;
          ++*v70;
        }
      }
    }
    v7 = dword_141133654;
    v147 = (char *)v65 + 6 * v55;
    v148 = v147 - 6;
    if(a2 < dword_141133654) {
      while(1) {
        v149 = v4 + *(unsigned int *)(v147 + 2);
        _mm_prefetch((const char *)(*(unsigned int *)(v149 + 4) + v4), 1);
        *(_DWORD *)(v147 + 2) = sub_14000A4B0(v149, a2 + 1);
        if(--v55 < 0)
          break;
        v147 = v148;
        v148 -= 6;
      }
    } else {
      *(_DWORD *)(v147 + 2) = 0;
      while(--v55 >= 0) {
        *(_DWORD *)(v148 + 2) = 0;
        v148 -= 6;
      }
    }
    goto LABEL_7;
  }
  v6 = qword_141133588 + *((unsigned int *)a1 + 1);
  if(v6 >= qword_141133568) {
    v7 = dword_141133654;
    if(a2 < dword_141133654) {
      _mm_prefetch((const char *)(*(unsigned int *)(v6 + 4) + qword_141133588), 1);
      v8 = sub_14000A4B0(v6, a2 + 1);
      *((_DWORD *)v3 + 1) = v8;
      if(v8)
        goto LABEL_7;
    } else {
      *((_DWORD *)v3 + 1) = 0;
    }
    if(a2 < 9) {
    LABEL_7:
      if(a2 == v7 && v3[13] == 255) {
        v9 = (_DWORD *)qword_141133570;
        if(*(_DWORD *)qword_141133570) {
          v10 = (_DWORD *)(v4 + *(unsigned int *)(qword_141133570 + 8));
          *(_DWORD *)(qword_141133570 + 8) = v10[2];
          *(_DWORD *)((unsigned int)v10[2] + v4 + 4) = (_DWORD)v9 - v4;
          v11 = &v3[-v4];
          v12 = 1;
          --*v9;
          *v10 = *(_DWORD *)v3;
          v10[1] = *((_DWORD *)v3 + 1);
          v10[2] = *((_DWORD *)v3 + 2);
          if(v3[13] == 255) {
            v13 = 12;
            do {
              *(_DWORD *)(*(unsigned int *)&v3[v13 + 4] + v4 + 8) = *(_DWORD *)&v3[v13 + 8];
              *(_DWORD *)(*(unsigned int *)&v3[v13 + 8] + v4 + 4) = *(_DWORD *)&v3[v13 + 4];
              v14 = *((unsigned __int8 *)&arch_hdr[11] + v3[v13] + 3);
              --v9[3 * v14];
              v12 += v3[v13];
              v13 = 12LL * v12;
            } while(v3[v13 + 1] == 255);
            v15 = v12;
            if(v12 > 0x80) {
              v16 = 0;
              v17 = 0;
              v18 = -((__int64)(((unsigned __int64)((1LL - v12) >> 6) >> 57) - v12 + 1) >> 7);
              do {
                v12 = v17 + v15 - 128;
                v17 -= 128;
                ++v16;
              } while(v16 < (unsigned int)v18);
              v19 = 0;
              do {
                v3[1] = -1;
                *((_DWORD *)v3 + 2) = (_DWORD)v9 - v4 + 444;
                ++v19;
                *v3 = 0x80;
                *((_DWORD *)v3 + 1) = v9[112];
                *(_DWORD *)((unsigned int)v9[112] + v4 + 8) = (_DWORD)v11;
                ++v9[111];
                v9[112] = (_DWORD)v11;
                v11 += 1536;
                v3 += 1536;
              } while(v19 < (unsigned int)v18);
            }
          }
          v20 = *((unsigned __int8 *)&arch_hdr[11] + v12 + 3);
          LODWORD(v21) = *((unsigned __int8 *)&xmmword_141133520 + v20);
          if(v12 != (_DWORD)v21) {
            v20 = (unsigned int)(v20 - 1);
            v21 = *((unsigned __int8 *)&xmmword_141133520 + v20);
            v22 = v12 - v21;
            v23 = (unsigned int)(v22 - 1);
            v24 = &v9[3 * v23];
            v25 = &v3[12 * v21];
            *v25 = v22;
            v25[1] = -1;
            *((_DWORD *)v25 + 2) = (_DWORD)v9 + 12 * v23 - v4;
            *((_DWORD *)v25 + 1) = v24[1];
            LODWORD(v25) = (_DWORD)v25 - v4;
            *(_DWORD *)((unsigned int)v24[1] + v4 + 8) = (_DWORD)v25;
            ++*v24;
            v24[1] = (_DWORD)v25;
          }
          v3[1] = -1;
          v26 = &v9[3 * v20];
          *v3 = v21;
          *((_DWORD *)v3 + 2) = (_DWORD)v26 - v4;
          *((_DWORD *)v3 + 1) = v26[1];
          v27 = (_DWORD)v3 - v4;
          *(_DWORD *)((unsigned int)v26[1] + v4 + 8) = v27;
          v26[1] = v27;
          ++*v26;
          LODWORD(v3) = (_DWORD)v10;
        }
      }
      return (unsigned int)((_DWORD)v3 - v4);
    }
  }
  v29 = (_DWORD *)qword_141133570;
LABEL_23:
  if(v3[13] == 255) {
    v31 = &v3[-v4];
    v32 = 1;
    v33 = 12;
    do {
      *(_DWORD *)(*(unsigned int *)&v3[v33 + 4] + v4 + 8) = *(_DWORD *)&v3[v33 + 8];
      *(_DWORD *)(*(unsigned int *)&v3[v33 + 8] + v4 + 4) = *(_DWORD *)&v3[v33 + 4];
      v34 = *((unsigned __int8 *)&arch_hdr[11] + v3[v33] + 3);
      --v29[3 * v34];
      v32 += v3[v33];
      v33 = 12LL * v32;
    } while(v3[v33 + 1] == 255);
    v35 = v32;
    if(v32 > 0x80) {
      v36 = 0;
      v37 = 0;
      v38 = -((__int64)(((unsigned __int64)((1LL - v32) >> 6) >> 57) - v32 + 1) >> 7);
      do {
        v32 = v37 + v35 - 128;
        v37 -= 128;
        ++v36;
      } while(v36 < (unsigned int)v38);
      v39 = 0;
      do {
        v3[1] = -1;
        *((_DWORD *)v3 + 2) = (_DWORD)v29 - v4 + 444;
        ++v39;
        *v3 = 0x80;
        *((_DWORD *)v3 + 1) = v29[112];
        *(_DWORD *)((unsigned int)v29[112] + v4 + 8) = (_DWORD)v31;
        ++v29[111];
        v29[112] = (_DWORD)v31;
        v31 += 1536;
        v3 += 1536;
      } while(v39 < (unsigned int)v38);
    }
    v40 = *((unsigned __int8 *)&arch_hdr[11] + v32 + 3);
    LODWORD(v41) = *((unsigned __int8 *)&xmmword_141133520 + v40);
    if(v32 != (_DWORD)v41) {
      v40 = (unsigned int)(v40 - 1);
      v41 = *((unsigned __int8 *)&xmmword_141133520 + v40);
      v42 = v32 - v41;
      v43 = (unsigned int)(v42 - 1);
      v44 = &v29[3 * v43];
      v45 = &v3[12 * v41];
      *v45 = v42;
      v45[1] = -1;
      *((_DWORD *)v45 + 2) = (_DWORD)v29 + 12 * v43 - v4;
      *((_DWORD *)v45 + 1) = v44[1];
      LODWORD(v45) = (_DWORD)v45 - v4;
      *(_DWORD *)((unsigned int)v44[1] + v4 + 8) = (_DWORD)v45;
      ++*v44;
      v44[1] = (_DWORD)v45;
    }
    v3[1] = -1;
    v46 = &v29[3 * v40];
    *v3 = v41;
    *((_DWORD *)v3 + 2) = (_DWORD)v46 - v4;
    *((_DWORD *)v3 + 1) = v46[1];
    v47 = (_DWORD)v3 - v4;
    *(_DWORD *)((unsigned int)v46[1] + v4 + 8) = v47;
    v46[1] = v47;
    ++*v46;
  } else {
    v3[1] = -1;
    *((_DWORD *)v3 + 1) = (_DWORD)v29 - v4;
    *v3 = 1;
    *((_DWORD *)v3 + 2) = v29[2];
    v30 = (_DWORD)v3 - v4;
    *(_DWORD *)((unsigned int)v29[2] + v4 + 4) = v30;
    v29[2] = v30;
    ++*v29;
  }
  return 0;
}
// 140028E50: using guessed type int arch_hdr[16];
// 140028F00: using guessed type __int128 xmmword_140028F00[];
// 141133520: using guessed type __int128 xmmword_141133520;
// 141133568: using guessed type __int64 qword_141133568;
// 141133570: using guessed type __int64 qword_141133570;
// 141133588: using guessed type __int64 qword_141133588;
// 141133654: using guessed type int dword_141133654;

// ---- Cleanup --------------------------------------------------------
#undef arch_hdr
#undef dword_141133654
#undef qword_141133568
#undef qword_141133570
#undef qword_141133588
#undef xmmword_140028F00
#undef xmmword_141133520
#undef sub_14000A4B0
#undef sub_140011920
#undef _BitScanForward
#undef FILE
