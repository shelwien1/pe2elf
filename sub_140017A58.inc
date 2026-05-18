// =====================================================================
// sub_140017A58 @ 0x140017A58
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___qword_140025600
#define __PE_DECL___qword_140025600
static __int64& __qword_140025600 = *(__int64*)0x140025600;
#endif
#define qword_140025600 __qword_140025600

PROBE_DECL(__sub_140017A58)
__attribute__((ms_abi)) void __sub_140017A58() {

  PROBE_HIT(__sub_140017A58);
  void (**i)(void); // rbx

  for(i = (void (**)(void))&qword_140025600; i < (void (**)(void))&qword_140025600; ++i) {
    if(*i)
      (*i)();
  }
}
// 140025600: using guessed type __int64 qword_140025600;

// ---- Cleanup --------------------------------------------------------
#undef qword_140025600
#undef _BitScanForward
#undef FILE
