// =====================================================================
// sub_14000C0E0 @ 0x14000C0E0
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___byte_1400227C0
#define __PE_DECL___byte_1400227C0
typedef char t_byte_1400227C0[36];
static t_byte_1400227C0& __byte_1400227C0 = *(t_byte_1400227C0*)0x1400227C0;
#endif
#define byte_1400227C0 __byte_1400227C0
#ifndef __PE_DECL___qword_141133588
#define __PE_DECL___qword_141133588
static __int64& __qword_141133588 = *(__int64*)0x141133588;
#endif
#define qword_141133588 __qword_141133588

// ---- PE-internal function references --------------------------------
#define sub_14000C0E0 __sub_14000C0E0

PROBE_DECL(__sub_14000C0E0)
__attribute__((ms_abi)) __int64 __sub_14000C0E0(unsigned __int8 *a1) {

  PROBE_HIT(__sub_14000C0E0);
  __int64 v2;           // r14
  int v3;               // edi
  int v4;               // r12d
  unsigned __int8 *v5;  // r15
  unsigned __int8 *v6;  // rbx
  __int64 v7;           // rax
  __int64 v8;           // rbp
  unsigned __int8 *i;   // rcx
  int v10;              // edx
  unsigned __int8 *j;   // rax
  unsigned int v12;     // r9d
  int v13;              // r8d
  unsigned int v14;     // ecx
  unsigned int v15;     // r9d
  int v16;              // edx
  int v17;              // esi
  int v18;              // esi
  int v19;              // eax
  unsigned int v20;     // ebx
  unsigned __int8 v21;  // si
  unsigned int v22;     // ebp
  __int64 v23;          // rax
  __int16 v24;          // cx
  int v25;              // ebx
  int v26;              // edx
  unsigned __int8 *v27; // r15

  v2 = qword_141133588;
  v3 = *a1;
  v4 = v3 + 1;
  v5 = (unsigned __int8 *)(qword_141133588 + *((unsigned int *)a1 + 1) + 6LL * (a1[1] & 0xF));
  v6 = (unsigned __int8 *)(qword_141133588 + *((unsigned int *)a1 + 2));
  v7 = *((unsigned int *)v6 + 1);
  v8 = *v6;
  for(i = (unsigned __int8 *)(qword_141133588 + v7 + 6 * v8); !i[1]; i = (unsigned __int8 *)(qword_141133588 + v7 + 6 * v8)) {
    if(*i != *v5)
      break;
    v6 = (unsigned __int8 *)(qword_141133588 + *((unsigned int *)v6 + 2));
    v7 = *((unsigned int *)v6 + 1);
    v8 = *v6;
  }
  if(!*(_BYTE *)(v7 + qword_141133588 + 6LL * (v6[1] & 0xF) + 1)) {
    sub_14000C0E0(v6);
    v7 = *((unsigned int *)v6 + 1);
  }
  v10 = *v5;
  for(j = (unsigned __int8 *)(v2 + v7); *j != v10; j += 6)
    ;
  v12 = j[1];
  v13 = *((unsigned __int16 *)a1 + 1);
  v14 = v13 - v12 + 2 * v8 + 2 + *((unsigned __int16 *)v6 + 1);
  if(v12 >= 6)
    v15 = v12 - 1;
  else
    v15 = ((3 - v12) >> 30) | 1;
  v16 = 4 * v3 + 4;
  v17 = v8 + 1 - v16;
  if(v17 < -4) {
    v19 = 0;
  } else {
    v18 = v17 + 4;
    v19 = 16 * v4;
    if(v18 < 16 * v4)
      v19 = v18;
  }
  v20 = 3 * (v19 + v13 + v16) * v15 / v14;
  if(v20 >= 0x24) {
    v21 = 11;
  } else {
    v21 = byte_1400227C0[v20];
    if(v20 <= 0x21) {
    LABEL_18:
      v5[1] = v21;
      goto LABEL_26;
    }
  }
  if(v13 >= 32 * v4)
    goto LABEL_18;
  v22 = 23;
  if(v13 >= 2 * (3 * v3 + 3))
    v22 = 7;
  if(v20 / 6 - 4 < v22)
    v22 = v20 / 6 - 4;
  v21 += v22;
  v5[1] = v21;
LABEL_26:
  v23 = *((unsigned int *)a1 + 1);
  for(*((_WORD *)a1 + 1) = v21 + (_WORD)v13; v5 != (unsigned __int8 *)(v2 + v23); v5 -= 6) {
    if(v5[1] <= *(v5 - 5) + 1)
      break;
    v24 = *(_WORD *)v5;
    v25 = *(_DWORD *)(v5 + 2);
    v26 = *((_DWORD *)v5 - 1);
    *(_WORD *)v5 = *((_WORD *)v5 - 3);
    *(_DWORD *)(v5 + 2) = v26;
    *((_WORD *)v5 - 3) = v24;
    *((_DWORD *)v5 - 1) = v25;
    v23 = *((unsigned int *)a1 + 1);
  }
  v27 = &v5[-v23 - v2];
  a1[1] = ((__int64)v27 / 6) | a1[1] & 0xF0;
  return 0x2AAAAAAAAAAAAAABLL * (_QWORD)v27;
}
// 141133588: using guessed type __int64 qword_141133588;

// ---- Cleanup --------------------------------------------------------
#undef byte_1400227C0
#undef qword_141133588
#undef sub_14000C0E0
#undef _BitScanForward
#undef FILE
