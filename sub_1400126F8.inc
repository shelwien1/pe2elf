// =====================================================================
// sub_1400126F8 @ 0x1400126F8
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

PROBE_DECL(__sub_1400126F8)
__attribute__((ms_abi)) __int64 __sub_1400126F8(_QWORD *a1) {

  PROBE_HIT(__sub_1400126F8); *a1 = &std::bad_alloc::`vftable'; return unknown_libname_1(); }
// 14001837C: using guessed type __int64 unknown_libname_1(void);
// 140022990: using guessed type void *std::bad_alloc::`vftable';

// ---- Cleanup --------------------------------------------------------
#undef _BitScanForward
#undef FILE
