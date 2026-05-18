// =====================================================================
// sub_14001A5C0 @ 0x14001A5C0
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---- Data references ------------------------------------------------
static int& __dword_141134C28 = *(int*)0x141134C28;
#define dword_141134C28 __dword_141134C28

PROBE_DECL(__sub_14001A5C0)
__attribute__((ms_abi)) void __sub_14001A5C0() {

  PROBE_HIT(__sub_14001A5C0); dword_141134C28 = 0; }
// 141134C28: using guessed type int dword_141134C28;

// ---- Cleanup --------------------------------------------------------
#undef dword_141134C28
#undef _BitScanForward
#undef FILE
