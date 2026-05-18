// =====================================================================
// sub_140003370 @ 0x140003370
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___PPMblock
#define __PE_DECL___PPMblock
static void *& __PPMblock = *(void **)0x141133578;
#endif
#define PPMblock __PPMblock
#ifndef __PE_DECL___PPMblock_size
#define __PE_DECL___PPMblock_size
static __int64& __PPMblock_size = *(__int64*)0x141133548;
#endif
#define PPMblock_size __PPMblock_size
#ifndef __PE_DECL___dword_141133648
#define __PE_DECL___dword_141133648
static int& __dword_141133648 = *(int*)0x141133648;
#endif
#define dword_141133648 __dword_141133648
#ifndef __PE_DECL___dword_14113364C
#define __PE_DECL___dword_14113364C
static int& __dword_14113364C = *(int*)0x14113364C;
#endif
#define dword_14113364C __dword_14113364C
#ifndef __PE_DECL___dword_141133650
#define __PE_DECL___dword_141133650
static int& __dword_141133650 = *(int*)0x141133650;
#endif
#define dword_141133650 __dword_141133650
#ifndef __PE_DECL___qword_141133550
#define __PE_DECL___qword_141133550
static __int64& __qword_141133550 = *(__int64*)0x141133550;
#endif
#define qword_141133550 __qword_141133550
#ifndef __PE_DECL___qword_141133558
#define __PE_DECL___qword_141133558
static __int64& __qword_141133558 = *(__int64*)0x141133558;
#endif
#define qword_141133558 __qword_141133558
#ifndef __PE_DECL___qword_141133560
#define __PE_DECL___qword_141133560
static __int64& __qword_141133560 = *(__int64*)0x141133560;
#endif
#define qword_141133560 __qword_141133560

// ---- PE-internal function references --------------------------------
#ifndef __PE_DECL___free
#define __PE_DECL___free
typedef __attribute__((ms_abi)) void t_free(void *Block);
static t_free& __free = *(t_free*)0x14001373C;
#endif
#define free __free

PROBE_DECL(__sub_140003370)
__attribute__((ms_abi)) __int64 __sub_140003370() {

  PROBE_HIT(__sub_140003370);
  __int64 v0;          // rbx
  void *v1;            // rcx
  unsigned __int64 v2; // rax
  __int64 v3;          // rax

  v0 = PPMblock_size;
  if(!PPMblock_size)
    return 0;
  if(dword_141133648 == 1) {
    v1 = PPMblock;
    if(!(dword_141133650 + dword_14113364C)) {
      if((qword_141133558 + (unsigned __int64)(108 * (unsigned int)(PPMblock_size / 0x78uLL)) - qword_141133550) / 9 <= qword_141133560 - (__int64)PPMblock)
        v2 = qword_141133560 - (_QWORD)PPMblock;
      else
        v2 = (qword_141133558 + (unsigned __int64)(108 * (unsigned int)(PPMblock_size / 0x78uLL)) - qword_141133550) / 9;
      v3 = 5 * v2;
      if(PPMblock_size > (unsigned __int64)(2 * v3 + 12))
        v0 = 2 * v3 + 12;
    }
  } else {
    v1 = PPMblock;
  }
  PPMblock_size = 0;
  free(v1);
  return (unsigned int)((unsigned __int64)(v0 + 0xFFFFF) >> 20);
}
// 141133548: using guessed type __int64 qword_141133548;
// 141133550: using guessed type __int64 qword_141133550;
// 141133558: using guessed type __int64 qword_141133558;
// 141133560: using guessed type __int64 qword_141133560;
// 141133648: using guessed type int dword_141133648;
// 14113364C: using guessed type int dword_14113364C;
// 141133650: using guessed type int dword_141133650;

// ---- Cleanup --------------------------------------------------------
#undef PPMblock
#undef PPMblock_size
#undef dword_141133648
#undef dword_14113364C
#undef dword_141133650
#undef qword_141133550
#undef qword_141133558
#undef qword_141133560
#undef free
#undef _BitScanForward
#undef FILE
