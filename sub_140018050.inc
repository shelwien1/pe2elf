// =====================================================================
// sub_140018050 @ 0x140018050
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___qword_141133DC0
#define __PE_DECL___qword_141133DC0
static __int64& __qword_141133DC0 = *(__int64*)0x141133DC0;
#endif
#define qword_141133DC0 __qword_141133DC0

PROBE_DECL(__sub_140018050)
__attribute__((ms_abi)) void __sub_140018050(__int64 a1) {

  PROBE_HIT(__sub_140018050); qword_141133DC0 = a1; }
// 141133DC0: using guessed type __int64 qword_141133DC0;

// ---- Cleanup --------------------------------------------------------
#undef qword_141133DC0
#undef FILE
