// =====================================================================
// sub_1400032F0 @ 0x1400032F0
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___PPMblock_size
#define __PE_DECL___PPMblock_size
static __int64& __PPMblock_size = *(__int64*)0x141133548;
#endif
#define PPMblock_size __PPMblock_size
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
#ifndef __PE_DECL___xmmword_141133520
#define __PE_DECL___xmmword_141133520
static __int128& __xmmword_141133520 = *(__int128*)0x141133520;
#endif
#define xmmword_141133520 __xmmword_141133520

PROBE_DECL(__sub_1400032F0)
__attribute__((ms_abi)) __int64 __sub_1400032F0() {

  PROBE_HIT(__sub_1400032F0);
  __int64 result; // rax
  __int64 v1;     // r10
  unsigned int i; // ecx
  int v3;         // r11d

  if(!PPMblock_size)
    return 0;
  v1 = 0;
  LODWORD(result) = qword_141133560 - qword_141133568 + qword_141133558 + PPMblock_size - qword_141133550;
  for(i = 0; i < 0x26; ++i) {
    v3 = *(_DWORD *)(qword_141133570 + 12 * v1) * 12 * *((unsigned __int8 *)&xmmword_141133520 + v1);
    v1 = i + 1;
    result = (unsigned int)(result - v3);
  }
  return result;
}
// 141133520: using guessed type __int128 xmmword_141133520;
// 141133548: using guessed type __int64 qword_141133548;
// 141133550: using guessed type __int64 qword_141133550;
// 141133558: using guessed type __int64 qword_141133558;
// 141133560: using guessed type __int64 qword_141133560;
// 141133568: using guessed type __int64 qword_141133568;
// 141133570: using guessed type __int64 qword_141133570;

// ---- Cleanup --------------------------------------------------------
#undef PPMblock_size
#undef qword_141133550
#undef qword_141133558
#undef qword_141133560
#undef qword_141133568
#undef qword_141133570
#undef xmmword_141133520
#undef _BitScanForward
#undef FILE
