// =====================================================================
// sub_140018098 @ 0x140018098
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___qword_141133DD0
#define __PE_DECL___qword_141133DD0
static PVOID& __qword_141133DD0 = *(PVOID*)0x141133DD0;
#endif
#define qword_141133DD0 __qword_141133DD0

PROBE_DECL(__sub_140018098)
__attribute__((ms_abi)) void __sub_140018098(void *a1) {

  PROBE_HIT(__sub_140018098); qword_141133DD0 = a1; }

// ---- Cleanup --------------------------------------------------------
#undef qword_141133DD0
#undef FILE
