// =====================================================================
// sub_140021DB0 @ 0x140021DB0
// Installs std::bad_alloc vftable into qword_141133780 and registers
// the singleton with unknown_libname_1 (atexit-style registration).
// =====================================================================

// qword_141133780 holds a pointer to the bad_alloc vftable; treat as void*.
#ifndef __PE_DECL___qword_141133780
#define __PE_DECL___qword_141133780
static void*& __qword_141133780 = *(void**)0x141133780;
#endif
#define qword_141133780 __qword_141133780

#ifndef __PE_DECL___unknown_libname_1
#define __PE_DECL___unknown_libname_1
typedef __attribute__((ms_abi)) __int64 t_unknown_libname_1(void*);
static t_unknown_libname_1& __unknown_libname_1 = *(t_unknown_libname_1*)0x14001837C;
#endif
#define unknown_libname_1 __unknown_libname_1

PROBE_DECL(__sub_140021DB0)
__attribute__((ms_abi)) void __sub_140021DB0() {
  PROBE_HIT(__sub_140021DB0);
  qword_141133780 = (void*)0x140022990; // &std::bad_alloc::`vftable'
  unknown_libname_1(&qword_141133780);
}

#undef qword_141133780
#undef unknown_libname_1
