// =====================================================================
// sub_14001D730 @ 0x14001D730
// memmove wrapper — CRT fallback path from j_memmove.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

PROBE_DECL(__sub_14001D730)
__attribute__((ms_abi)) void* __sub_14001D730(void *a1, const void *a2, size_t a3) {
  PROBE_HIT(__sub_14001D730);
  return memmove(a1, a2, a3);
}

// ---- Cleanup --------------------------------------------------------
#undef _BitScanForward
#undef FILE
