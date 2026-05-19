// =====================================================================
// sub_140018058 @ 0x140018058
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___qword_141133DC8
#define __PE_DECL___qword_141133DC8
static __int64& __qword_141133DC8 = *(__int64*)0x141133DC8;
#endif
#define qword_141133DC8 __qword_141133DC8

PROBE_DECL(__sub_140018058)
__attribute__((ms_abi)) void __sub_140018058(__int64 a1) {

  PROBE_HIT(__sub_140018058); qword_141133DC8 = a1; }
// 141133DC8: using guessed type __int64 qword_141133DC8;

// ---- Cleanup --------------------------------------------------------
#undef qword_141133DC8
#undef FILE
