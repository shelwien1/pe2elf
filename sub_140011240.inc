// =====================================================================
// sub_140011240 @ 0x140011240
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___PPMblock
#define __PE_DECL___PPMblock
static void *& __PPMblock = *(void **)0x141133578;
#endif
#define PPMblock __PPMblock
#ifndef __PE_DECL___PPMblock_size
#define __PE_DECL___PPMblock_size
static __int64& __PPMblock_size = *(__int64*)0x141133548;
#endif
#define PPMblock_size __PPMblock_size
#ifndef __PE_DECL___arch_hdr
#define __PE_DECL___arch_hdr
typedef int t_arch_hdr[16];
static t_arch_hdr& __arch_hdr = *(t_arch_hdr*)0x140028E50;
#endif
#define arch_hdr __arch_hdr
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
#ifndef __PE_DECL___qword_141133588
#define __PE_DECL___qword_141133588
static __int64& __qword_141133588 = *(__int64*)0x141133588;
#endif
#define qword_141133588 __qword_141133588
#ifndef __PE_DECL___xmmword_141133520
#define __PE_DECL___xmmword_141133520
static __int128& __xmmword_141133520 = *(__int128*)0x141133520;
#endif
#define xmmword_141133520 __xmmword_141133520

// ---- PE-internal function references --------------------------------
// Self-reference: __sub_140011240 IS the C++ function defined below.
// Set the guard so callers' typedef+static-ref blocks are skipped.
#define __PE_DECL___sub_140011240
#define sub_140011240 __sub_140011240

PROBE_DECL(__sub_140011240)
__attribute__((ms_abi)) __int64 __sub_140011240(unsigned int a1) {

  PROBE_HIT(__sub_140011240);
  __int64 v1;           // rbp
  __int64 v2;           // r12
  unsigned int v3;      // r13d
  _DWORD *v4;           // rdx
  __int64 v5;           // r8
  __int64 result;       // rax
  int v7;               // ecx
  __int64 v8;           // r10
  __int64 v9;           // rdx
  unsigned int v10;     // ecx
  __int64 v11;          // r13
  __int64 v12;          // r12
  unsigned __int8 *i;   // r11
  __int64 v14;          // r14
  unsigned int v15;     // r11d
  unsigned int v16;     // r12d
  int v17;              // r14d
  __int64 v18;          // r13
  int v19;              // r11d
  unsigned int v20;     // r14d
  __int64 v21;          // r11
  __int64 v22;          // rdx
  int v23;              // ecx
  _DWORD *v24;          // r9
  int v25;              // r15d
  __int64 v26;          // r12
  _DWORD *v27;          // rbp
  int v28;              // r11d
  int v29;              // r10d
  __int64 v30;          // r13
  char *v31;            // rdx
  __int64 v32;          // r10
  int v33;              // ecx
  __int64 v34;          // r15
  unsigned int v35;     // r8d
  int v36;              // eax
  _DWORD *v37;          // rsi
  int v38;              // r11d
  int v39;              // edi
  __int64 v40;          // r11
  char *v41;            // r11
  __int64 v42;          // rbx
  unsigned int v43;     // r15d
  __int64 v44;          // r12
  _DWORD *v45;          // rbx
  int v46;              // r14d
  int v47;              // r11d
  unsigned __int8 *v48; // r13
  __int64 v49;          // rbx
  __int64 v50;          // r14
  unsigned int v51;     // r9d
  unsigned int v52;     // ebx
  int v53;              // r14d
  __int64 v54;          // r12
  int v55;              // r14d
  unsigned int v56;     // ebx
  __int64 v57;          // rbx
  __int64 v58;          // r13
  int v59;              // r15d
  _DWORD *v60;          // r12
  unsigned __int8 *v61; // r14
  _DWORD *v62;          // rbx
  int v63;              // r14d
  int v64;              // r11d
  int v65;              // eax
  __int64 v66;          // r8
  _DWORD *v67;          // rbp
  __int64 v68;          // rcx
  bool v69;             // zf
  int v70;              // [rsp+20h] [rbp-68h]
  __int64 v71;          // [rsp+28h] [rbp-60h]
  __int64 v72;          // [rsp+38h] [rbp-50h]

  v1 = qword_141133570;
  v2 = a1;
  v3 = *((unsigned __int8 *)&xmmword_141133520 + a1);
  while(++a1 != 38) {
    v4 = (_DWORD *)(qword_141133570 + 12LL * a1);
    if(*v4) {
      v5 = qword_141133588;
      result = qword_141133588 + (unsigned int)v4[1];
      v4[1] = *(_DWORD *)(result + 4);
      *(_DWORD *)(v5 + *(unsigned int *)(result + 4) + 8) = (_DWORD)v4 - v5;
      v7 = *((unsigned __int8 *)&xmmword_141133520 + a1);
      --*v4;
      v8 = result + 12LL * v3;
      v9 = v8 - v5;
      v10 = v7 - v3;
      v11 = v10;
      v12 = 12LL * v10;
      for(i = (unsigned __int8 *)(v8 + v12); *(unsigned __int8 *)(v8 + v12 + 1) == 255; i = (unsigned __int8 *)(v8 + v12)) {
        *(_DWORD *)(*((unsigned int *)i + 1) + v5 + 8) = *((_DWORD *)i + 2);
        *(_DWORD *)(*((unsigned int *)i + 2) + v5 + 4) = *((_DWORD *)i + 1);
        v14 = 12LL * *((unsigned __int8 *)&arch_hdr[11] + *i + 3);
        --*(_DWORD *)(v14 + v1);
        v10 += *(unsigned __int8 *)(v8 + v12);
        v11 = v10;
        v12 = 12LL * v10;
      }
      v15 = v10;
      if(v10 > 0x80) {
        v16 = 0;
        v17 = 0;
        v18 = -((__int64)(((unsigned __int64)((1 - v11) >> 6) >> 57) - v11 + 1) >> 7);
        do {
          v10 = v17 + v15 - 128;
          v17 -= 128;
          ++v16;
        } while(v16 < (unsigned int)v18);
        v19 = *(_DWORD *)(v1 + 448);
        v20 = 0;
        do {
          *(_BYTE *)(v8 + 1) = -1;
          *(_DWORD *)(v8 + 8) = v1 - v5 + 444;
          *(_DWORD *)(v8 + 4) = v19;
          v19 = v9;
          *(_BYTE *)v8 = 0x80;
          v9 += 1536;
          v8 += 1536;
          *(_DWORD *)(v5 + *(unsigned int *)(v1 + 448) + 8) = v19;
          ++*(_DWORD *)(v1 + 444);
          *(_DWORD *)(v1 + 448) = v19;
          ++v20;
        } while(v20 < (unsigned int)v18);
      }
      v21 = *((unsigned __int8 *)&arch_hdr[11] + v10 + 3);
      LODWORD(v22) = *((unsigned __int8 *)&xmmword_141133520 + v21);
      if(v10 != (_DWORD)v22) {
        v21 = (unsigned int)(v21 - 1);
        v22 = *((unsigned __int8 *)&xmmword_141133520 + v21);
        v23 = v10 - v22;
        v24 = (_DWORD *)(v1 + 12LL * (unsigned int)(v23 - 1));
        v25 = v24[1];
        v26 = v8 + 12 * v22;
        *(_BYTE *)v26 = v23;
        *(_BYTE *)(v26 + 1) = -1;
        *(_DWORD *)(v26 + 8) = (_DWORD)v24 - v5;
        *(_DWORD *)(v26 + 4) = v25;
        LODWORD(v26) = v26 - v5;
        *(_DWORD *)((unsigned int)v24[1] + v5 + 8) = v26;
        v24[1] = v26;
        ++*v24;
      }
      *(_BYTE *)(v8 + 1) = -1;
      v27 = (_DWORD *)(12 * v21 + v1);
      v28 = v27[1];
      *(_BYTE *)v8 = v22;
      *(_DWORD *)(v8 + 8) = (_DWORD)v27 - v5;
      *(_DWORD *)(v8 + 4) = v28;
      v29 = v8 - v5;
      *(_DWORD *)((unsigned int)v27[1] + v5 + 8) = v29;
      v27[1] = v29;
      ++*v27;
      return result;
    }
  }
  if(dword_141133650) {
    if(dword_14113364C)
      return 0;
    v30 = 12 * v3;
    if(qword_141133568 - v30 <= (unsigned __int64)qword_141133560) {
      return 0;
    } else {
      result = qword_141133568 - v30;
      qword_141133568 -= v30;
    }
  } else {
    v31 = (char *)PPMblock + PPMblock_size - 12;
    v32 = qword_141133588;
    v70 = *((_DWORD *)v31 + 2);
    v71 = *(_QWORD *)v31;
    v33 = (_DWORD)PPMblock + PPMblock_size - 12 - qword_141133588;
    v72 = v2;
    v34 = 0;
    v35 = 0;
    v36 = qword_141133570 - qword_141133588 + 444;
    do {
      v31[1] = -2;
      v37 = (_DWORD *)(v1 + 12 * v34);
      v38 = v37[1];
      *v31 = 1;
      v39 = v1 + 12 * v34 - v32;
      *((_DWORD *)v31 + 2) = v39;
      *((_DWORD *)v31 + 1) = v38;
      *(_DWORD *)((unsigned int)v37[1] + v32 + 8) = v33;
      v40 = (unsigned int)v37[2];
      ++*v37;
      v37[1] = v33;
      v41 = (char *)(v32 + v40);
      v37[2] = *((_DWORD *)v41 + 2);
      *(_DWORD *)(*((unsigned int *)v41 + 2) + v32 + 4) = v39;
      --*v37;
      for(; v41 != v31; --*v37) {
        v42 = *((unsigned __int8 *)&arch_hdr[11] + (unsigned int)(unsigned __int8)*v41 + 3);
        _mm_prefetch((const char *)(*(unsigned int *)((unsigned int)v37[2] + v32 + 8) + v32 + 4), 1);
        v43 = *((unsigned __int8 *)&xmmword_141133520 + v42);
        v44 = *((unsigned __int8 *)&xmmword_141133520 + v42);
        if((unsigned __int8)v41[12 * v44 + 1] == 255) {
          v48 = (unsigned __int8 *)&v41[-v32];
          v49 = 12 * v44;
          do {
            *(_DWORD *)(*(unsigned int *)&v41[v49 + 4] + v32 + 8) = *(_DWORD *)&v41[v49 + 8];
            *(_DWORD *)(*(unsigned int *)&v41[v49 + 8] + v32 + 4) = *(_DWORD *)&v41[v49 + 4];
            v50 = 12LL * *((unsigned __int8 *)&arch_hdr[11] + (unsigned __int8)v41[v49] + 3);
            --*(_DWORD *)(v50 + v1);
            v43 += (unsigned __int8)v41[v49];
            v49 = 12LL * v43;
          } while((unsigned __int8)v41[v49 + 1] == 255);
          if(v43 > 0x80) {
            v51 = v43;
            v52 = 0;
            v53 = 0;
            v54 = -((__int64)(((unsigned __int64)((1LL - v43) >> 6) >> 57) - v43 + 1) >> 7);
            do {
              v43 = v53 + v51 - 128;
              v53 -= 128;
              ++v52;
            } while(v52 < (unsigned int)v54);
            v55 = *(_DWORD *)(v1 + 448);
            v56 = 0;
            do {
              v41[1] = -1;
              *((_DWORD *)v41 + 2) = v36;
              *((_DWORD *)v41 + 1) = v55;
              v55 = (int)v48;
              *v41 = 0x80;
              v48 += 1536;
              v41 += 1536;
              *(_DWORD *)(v32 + *(unsigned int *)(v1 + 448) + 8) = v55;
              ++*(_DWORD *)(v1 + 444);
              *(_DWORD *)(v1 + 448) = v55;
              ++v56;
            } while(v56 < (unsigned int)v54);
          }
          v57 = *((unsigned __int8 *)&arch_hdr[11] + v43 + 3);
          LODWORD(v58) = *((unsigned __int8 *)&xmmword_141133520 + v57);
          if(v43 != (_DWORD)v58) {
            v57 = (unsigned int)(v57 - 1);
            v58 = *((unsigned __int8 *)&xmmword_141133520 + v57);
            v59 = v43 - v58;
            v60 = (_DWORD *)(v1 + 12LL * (unsigned int)(v59 - 1));
            v61 = (unsigned __int8 *)&v41[12 * v58];
            v61[1] = -1;
            *v61 = v59;
            *((_DWORD *)v61 + 2) = v1 + 12 * (v59 - 1) - v32;
            *((_DWORD *)v61 + 1) = v60[1];
            LODWORD(v61) = (_DWORD)v61 - v32;
            *(_DWORD *)((unsigned int)v60[1] + v32 + 8) = (_DWORD)v61;
            v60[1] = (_DWORD)v61;
            ++*v60;
          }
          v41[1] = -1;
          v62 = (_DWORD *)(v1 + 12 * v57);
          v63 = v62[1];
          *v41 = v58;
          *((_DWORD *)v41 + 2) = (_DWORD)v62 - v32;
          *((_DWORD *)v41 + 1) = v63;
          v64 = (_DWORD)v41 - v32;
          *(_DWORD *)((unsigned int)v62[1] + v32 + 8) = v64;
          v62[1] = v64;
          ++*v62;
        } else {
          v41[1] = -1;
          v45 = (_DWORD *)(v1 + 12 * v42);
          v46 = v45[1];
          *v41 = v43;
          *((_DWORD *)v41 + 2) = (_DWORD)v45 - v32;
          *((_DWORD *)v41 + 1) = v46;
          v47 = (_DWORD)v41 - v32;
          *(_DWORD *)((unsigned int)v45[1] + v32 + 8) = v47;
          v45[1] = v47;
          ++*v45;
        }
        v41 = (char *)(v32 + (unsigned int)v37[2]);
        v37[2] = *((_DWORD *)v41 + 2);
        *(_DWORD *)(*((unsigned int *)v41 + 2) + v32 + 4) = v39;
      }
      v34 = ++v35;
    } while(v35 < 0x26);
    *(_QWORD *)v31 = v71;
    *((_DWORD *)v31 + 2) = v70;
    v65 = *((unsigned __int8 *)&xmmword_141133520 + v72);
    dword_141133650 = 1;
    v66 = *((unsigned __int8 *)&arch_hdr[12] + (unsigned int)(v65 - 1));
    v67 = (_DWORD *)(12 * v66 + v1);
    if(*v67) {
      result = v32 + (unsigned int)v67[1];
      v67[1] = *(_DWORD *)(result + 4);
      *(_DWORD *)(*(unsigned int *)(result + 4) + v32 + 8) = (_DWORD)v67 - v32;
      --*v67;
    } else {
      result = qword_141133558;
      v68 = 12 * (unsigned int)*((unsigned __int8 *)&xmmword_141133520 + v66);
      v69 = qword_141133558 + v68 == qword_141133550;
      if(qword_141133558 + v68 > (unsigned __int64)qword_141133550) {
        return sub_140011240((unsigned int)v66);
      } else {
        qword_141133558 += v68;
        if(!v69)
          *(_DWORD *)(v68 + result) = 0;
      }
    }
  }
  return result;
}
// 140028E50: using guessed type int arch_hdr[16];
// 141133520: using guessed type __int128 xmmword_141133520;
// 141133548: using guessed type __int64 qword_141133548;
// 141133550: using guessed type __int64 qword_141133550;
// 141133558: using guessed type __int64 qword_141133558;
// 141133560: using guessed type __int64 qword_141133560;
// 141133568: using guessed type __int64 qword_141133568;
// 141133570: using guessed type __int64 qword_141133570;
// 141133588: using guessed type __int64 qword_141133588;
// 14113364C: using guessed type int dword_14113364C;
// 141133650: using guessed type int dword_141133650;

// ---- Cleanup --------------------------------------------------------
#undef PPMblock
#undef PPMblock_size
#undef arch_hdr
#undef dword_14113364C
#undef dword_141133650
#undef qword_141133550
#undef qword_141133558
#undef qword_141133560
#undef qword_141133568
#undef qword_141133570
#undef qword_141133588
#undef xmmword_141133520
#undef sub_140011240
#undef _BitScanForward
#undef FILE
