// =====================================================================
// sub_1400183E4 @ 0x1400183E4
// Scalar deleting destructor for type_info.
// Restores vftable, calls destructor body (unknown_libname_2 = type_info dtor),
// then conditionally frees Block.
// =====================================================================

// ---- PE-internal function references --------------------------------
#ifndef __PE_DECL___unknown_libname_2
#define __PE_DECL___unknown_libname_2
typedef __attribute__((ms_abi)) __int64 t_unknown_libname_2(void);
static t_unknown_libname_2& __unknown_libname_2 = *(t_unknown_libname_2*)0x14001C798;
#endif
#define unknown_libname_2 __unknown_libname_2

// j_free — per-caller typedef to avoid conflict with main.inc's __j_free
typedef __attribute__((ms_abi)) void t_j_free_1400183E4(void*);
static t_j_free_1400183E4& __j_free_1400183E4 = *(t_j_free_1400183E4*)0x140012FBC;
#define j_free __j_free_1400183E4

PROBE_DECL(__sub_1400183E4)
__attribute__((ms_abi)) _QWORD * __sub_1400183E4(_QWORD *Block, char a2) {
  PROBE_HIT(__sub_1400183E4);
  *Block = (_QWORD)0x140023198ULL; // &type_info::`vftable' (??_7type_info@@6B@)
  unknown_libname_2();
  if((a2 & 1) != 0)
    j_free(Block);
  return Block;
}

#undef unknown_libname_2
#undef j_free
