// =====================================================================
// sub_1400126F8 @ 0x1400126F8
// =====================================================================

#define FILE FILE1

// bad_alloc constructor: store vftable, then tail-call unknown_libname_1(this).
// Assembly: lea rax,??_7bad_alloc; mov [rcx],rax; jmp unknown_libname_1
// Hex-Rays shows unknown_libname_1() with no args but the tail call passes rcx=a1.

#ifndef __PE_DECL___unknown_libname_1
#define __PE_DECL___unknown_libname_1
typedef __attribute__((ms_abi)) __int64 t_unknown_libname_1(void*);
static t_unknown_libname_1& __unknown_libname_1 = *(t_unknown_libname_1*)0x14001837C;
#endif
#define unknown_libname_1 __unknown_libname_1

PROBE_DECL(__sub_1400126F8)
__attribute__((ms_abi)) __int64 __sub_1400126F8(_QWORD *a1) {
  PROBE_HIT(__sub_1400126F8);
  *a1 = (void*)0x140022990;  // &std::bad_alloc::`vftable'
  return unknown_libname_1(a1);
}

#undef unknown_libname_1
#undef FILE
