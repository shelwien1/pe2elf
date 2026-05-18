// =====================================================================
// sub_140014894 @ 0x140014894
// =====================================================================

#define FILE FILE1

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___qword_1411337D0
#define __PE_DECL___qword_1411337D0
typedef PVOID t_qword_1411337D0;
static t_qword_1411337D0& __qword_1411337D0 = *(t_qword_1411337D0*)0x1411337D0;
#endif
#define qword_1411337D0 __qword_1411337D0

PROBE_DECL(__sub_140014894)
__attribute__((ms_abi)) void __sub_140014894(void *a1) {
  PROBE_HIT(__sub_140014894);
  qword_1411337D0 = a1;
}

// ---- Cleanup --------------------------------------------------------
#undef qword_1411337D0
#undef FILE
