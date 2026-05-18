// =====================================================================
// sub_140018048 @ 0x140018048
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___qword_141133DB0
#define __PE_DECL___qword_141133DB0
static __int64& __qword_141133DB0 = *(__int64*)0x141133DB0;
#endif
#define qword_141133DB0 __qword_141133DB0

PROBE_DECL(__sub_140018048)
__attribute__((ms_abi)) void __sub_140018048(__int64 a1) {

  PROBE_HIT(__sub_140018048); qword_141133DB0 = a1; }
// 141133DB0: using guessed type __int64 qword_141133DB0;

// ---- Cleanup --------------------------------------------------------
#undef qword_141133DB0
#undef _BitScanForward
#undef FILE
