// =====================================================================
// sub_140017DC8 @ 0x140017DC8
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___qword_141133D98
#define __PE_DECL___qword_141133D98
static PVOID& __qword_141133D98 = *(PVOID*)0x141133D98;
#endif
#define qword_141133D98 __qword_141133D98

// ---- PE-internal function references --------------------------------
#ifndef __PE_DECL___DecodePointer
#define __PE_DECL___DecodePointer
typedef __attribute__((ms_abi)) PVOID t_DecodePointer(PVOID Ptr);
static t_DecodePointer& __DecodePointer = *(t_DecodePointer*)0x140015718;
#endif
#define DecodePointer __DecodePointer

PROBE_DECL(__sub_140017DC8)
__attribute__((ms_abi)) PVOID __sub_140017DC8() {
  PROBE_HIT(__sub_140017DC8);
  return DecodePointer(qword_141133D98);
}

// ---- Cleanup --------------------------------------------------------
#undef qword_141133D98
#undef DecodePointer
#undef _BitScanForward
#undef FILE
