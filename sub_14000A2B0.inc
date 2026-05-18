// =====================================================================
// sub_14000A2B0 @ 0x14000A2B0
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---- Data references ------------------------------------------------
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
#ifndef __PE_DECL___qword_141133620
#define __PE_DECL___qword_141133620
static __int64& __qword_141133620 = *(__int64*)0x141133620;
#endif
#define qword_141133620 __qword_141133620
#ifndef __PE_DECL___xmmword_140028F00
#define __PE_DECL___xmmword_140028F00
typedef __int128 t_xmmword_140028F00[1];
static t_xmmword_140028F00& __xmmword_140028F00 = *(t_xmmword_140028F00*)0x140028F00;
#endif
#define xmmword_140028F00 __xmmword_140028F00

// ---- PE-internal function references --------------------------------
#ifndef __PE_DECL___sub_140011240
#define __PE_DECL___sub_140011240
typedef __attribute__((ms_abi)) __int64 t_sub_140011240(unsigned int a1);
static t_sub_140011240& __sub_140011240 = *(t_sub_140011240*)0x140011240;
#endif
#define sub_140011240 __sub_140011240

PROBE_DECL(__sub_14000A2B0)
__attribute__((ms_abi)) __int64 __sub_14000A2B0(int a1, unsigned __int64 a2, __int64 a3) {

  PROBE_HIT(__sub_14000A2B0);
  __int64 v3;           // r11
  unsigned int v4;      // r10d
  unsigned __int64 v5;  // r9
  int v6;               // ebp
  unsigned int v7;      // ebp
  unsigned __int8 *v8;  // rax
  unsigned int v9;      // r8d
  __int64 v10;          // rbx
  int v11;              // ebp
  unsigned __int8 *i;   // rsi
  int v13;              // r8d
  unsigned __int64 v14; // rdx
  unsigned __int64 v15; // rdi
  int v16;              // ebp
  unsigned __int8 *v17; // r10
  unsigned __int64 v18; // rbx
  int v19;              // r14d
  _DWORD *v20;          // rsi
  __int64 v21;          // r13
  __int64 v22;          // r12
  _DWORD *v23;          // rdx
  __int64 result;       // rax
  int v25;              // [rsp+40h] [rbp-28h]
  int v26;              // [rsp+44h] [rbp-24h]

  v3 = qword_141133588;
  v4 = *(_DWORD *)(*(_QWORD *)a2 + 2LL);
  v5 = a2;
  while(1) {
    v6 = *(_DWORD *)(*(_QWORD *)v5 + 2LL);
    if(v6 != v4) {
      LODWORD(a3) = qword_141133588 + v6;
      goto LABEL_15;
    }
    v7 = *(_DWORD *)(a3 + 8);
    v5 += 8LL;
    if(!v7)
      goto LABEL_15;
    if(v5 >= qword_141133620)
      break;
    a3 = qword_141133588 + v7;
  }
  v8 = (unsigned __int8 *)qword_141133610;
  v9 = *(_DWORD *)(a3 + 8);
  while(1) {
    v10 = v3 + v9;
    if(*(_BYTE *)v10) {
      v11 = *v8;
      for(i = (unsigned __int8 *)(v3 + *(unsigned int *)(v10 + 4)); *i != v11; i += 6)
        ;
    } else {
      i = (unsigned __int8 *)(v3 + v9 + 2);
    }
    v13 = *(_DWORD *)(i + 2);
    if(v13 != v4)
      break;
    v9 = *(_DWORD *)(v10 + 8);
    *(_QWORD *)v5 = i;
    v5 += 8LL;
    if(!v9) {
      LODWORD(a3) = v10;
      goto LABEL_15;
    }
  }
  LODWORD(a3) = v3 + v13;
LABEL_15:
  v14 = a2 + 8LL * a1;
  if(v5 == v14)
    return (unsigned int)(a3 - v3);
  v15 = v14;
  v16 = a3;
  LOBYTE(v25) = 0;
  v17 = (unsigned __int8 *)(v3 + v4);
  HIWORD(v25) = *v17;
  v26 = (_DWORD)v17 - v3 + 1;
  v18 = v5;
  BYTE1(v25) = *((_BYTE *)xmmword_140028F00 + *v17);
  v19 = qword_141133570 - v3;
  v20 = (_DWORD *)qword_141133570;
  v21 = qword_141133550;
  v22 = v3;
  while(1) {
    if(v21 == qword_141133558) {
      if(*v20) {
        v23 = (_DWORD *)(v22 + (unsigned int)v20[2]);
        v20[2] = v23[2];
        *(_DWORD *)((unsigned int)v23[2] + v22 + 4) = v19;
        --*v20;
      } else {
        v23 = (_DWORD *)sub_140011240(0);
      }
    } else {
      v21 -= 12;
      qword_141133550 = v21;
      v23 = (_DWORD *)v21;
    }
    if(!v23)
      break;
    *v23 = v25;
    v23[1] = v26;
    v23[2] = v16 - v22;
    v16 = (int)v23;
    result = (unsigned int)((_DWORD)v23 - v22);
    v18 -= 8LL;
    *(_DWORD *)(*(_QWORD *)v18 + 2LL) = result;
    if(v18 == v15)
      return result;
  }
  return 0;
}
// 140028F00: using guessed type __int128 xmmword_140028F00[];
// 141133550: using guessed type __int64 qword_141133550;
// 141133558: using guessed type __int64 qword_141133558;
// 141133570: using guessed type __int64 qword_141133570;
// 141133588: using guessed type __int64 qword_141133588;
// 141133610: using guessed type __int64 qword_141133610;
// 141133620: using guessed type __int64 qword_141133620;

// ---- Cleanup --------------------------------------------------------
#undef qword_141133550
#undef qword_141133558
#undef qword_141133570
#undef qword_141133588
#undef qword_141133610
#undef qword_141133620
#undef xmmword_140028F00
#undef sub_140011240
#undef _BitScanForward
#undef FILE
