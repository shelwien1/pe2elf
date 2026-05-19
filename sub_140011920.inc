// =====================================================================
// sub_140011920 @ 0x140011920
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

PROBE_DECL(__sub_140011920)
__attribute__((ms_abi)) char * __sub_140011920(__int64 a1, unsigned int a2) {

  PROBE_HIT(__sub_140011920);
  __int64 v2;         // r9
  __int64 v3;         // r10
  __int64 v4;         // rbp
  __int64 v5;         // rax
  __int64 v6;         // r14
  unsigned __int8 *i; // r11
  __int64 v8;         // r15
  unsigned int v9;    // r14d
  unsigned int v10;   // r11d
  int v11;            // r15d
  __int64 v12;        // rax
  int v13;            // r11d
  unsigned int v14;   // r15d
  __int64 v15;        // rbp
  __int64 v16;        // rax
  int v17;            // edx
  _DWORD *v18;        // r8
  __int64 v19;        // r11
  _DWORD *v20;        // r9
  int v21;            // r11d
  int v23;            // ecx

  v2 = qword_141133570;
  v3 = qword_141133588;
  v4 = a1 - qword_141133588;
  v5 = a2;
  v6 = 12LL * a2;
  for(i = (unsigned __int8 *)(a1 + v6); *(unsigned __int8 *)(a1 + v6 + 1) == 255; i = (unsigned __int8 *)(a1 + v6)) {
    *(_DWORD *)(*((unsigned int *)i + 1) + v3 + 8) = *((_DWORD *)i + 2);
    *(_DWORD *)(*((unsigned int *)i + 2) + v3 + 4) = *((_DWORD *)i + 1);
    v8 = 12LL * *((unsigned __int8 *)&arch_hdr[11] + *i + 3);
    --*(_DWORD *)(v8 + v2);
    a2 += *(unsigned __int8 *)(a1 + v6);
    v5 = a2;
    v6 = 12LL * a2;
  }
  v9 = a2;
  if(a2 > 0x80) {
    v10 = 0;
    v11 = 0;
    v12 = -((__int64)(((unsigned __int64)((1 - v5) >> 6) >> 57) - v5 + 1) >> 7);
    do {
      a2 = v11 + v9 - 128;
      v11 -= 128;
      ++v10;
    } while(v10 < (unsigned int)v12);
    v13 = *(_DWORD *)(v2 + 448);
    v14 = 0;
    do {
      *(_BYTE *)(a1 + 1) = -1;
      *(_DWORD *)(a1 + 8) = v2 - v3 + 444;
      *(_DWORD *)(a1 + 4) = v13;
      v13 = v4;
      *(_BYTE *)a1 = 0x80;
      v4 += 1536;
      a1 += 1536;
      *(_DWORD *)(v3 + *(unsigned int *)(v2 + 448) + 8) = v13;
      ++*(_DWORD *)(v2 + 444);
      *(_DWORD *)(v2 + 448) = v13;
      ++v14;
    } while(v14 < (unsigned int)v12);
  }
  v15 = *((unsigned __int8 *)&arch_hdr[11] + a2 + 3);
  LODWORD(v16) = *((unsigned __int8 *)&xmmword_141133520 + v15);
  if(a2 != (_DWORD)v16) {
    v15 = (unsigned int)(v15 - 1);
    v16 = *((unsigned __int8 *)&xmmword_141133520 + v15);
    v17 = a2 - v16;
    v18 = (_DWORD *)(v2 + 12LL * (unsigned int)(v17 - 1));
    v19 = a1 + 12 * v16;
    *(_BYTE *)(v19 + 1) = -1;
    *(_BYTE *)v19 = v17;
    *(_DWORD *)(v19 + 8) = v2 + 12 * (v17 - 1) - v3;
    *(_DWORD *)(v19 + 4) = v18[1];
    LODWORD(v19) = v19 - v3;
    *(_DWORD *)((unsigned int)v18[1] + v3 + 8) = v19;
    v18[1] = v19;
    ++*v18;
  }
  *(_BYTE *)(a1 + 1) = -1;
  v20 = (_DWORD *)(12 * v15 + v2);
  v21 = v20[1];
  *(_BYTE *)a1 = v16;
  *(_DWORD *)(a1 + 8) = (_DWORD)v20 - v3;
  *(_DWORD *)(a1 + 4) = v21;
  v23 = a1 - v3;
  *(_DWORD *)((unsigned int)v20[1] + v3 + 8) = v23;
  v20[1] = v23;
  ++*v20;
  return (char *)v20 - v3;
}
// 140028E50: using guessed type int arch_hdr[16];
// 141133520: using guessed type __int128 xmmword_141133520;
// 141133570: using guessed type __int64 qword_141133570;
// 141133588: using guessed type __int64 qword_141133588;

// ---- Cleanup --------------------------------------------------------
#undef arch_hdr
#undef qword_141133570
#undef qword_141133588
#undef xmmword_141133520
#undef _BitScanForward
#undef FILE
