// =====================================================================
// Alloc_PPMblock @ 0x140003480
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
#ifndef __PE_DECL___dword_141133654
#define __PE_DECL___dword_141133654
static int& __dword_141133654 = *(int*)0x141133654;
#endif
#define dword_141133654 __dword_141133654
#ifndef __PE_DECL___dword_141133658
#define __PE_DECL___dword_141133658
static int& __dword_141133658 = *(int*)0x141133658;
#endif
#define dword_141133658 __dword_141133658
#ifndef __PE_DECL___dword_14113365C
#define __PE_DECL___dword_14113365C
static int& __dword_14113365C = *(int*)0x14113365C;
#endif
#define dword_14113365C __dword_14113365C
#ifndef __PE_DECL___dword_141133660
#define __PE_DECL___dword_141133660
static int& __dword_141133660 = *(int*)0x141133660;
#endif
#define dword_141133660 __dword_141133660

// ---- PE-internal function references --------------------------------
#ifndef __PE_DECL___malloc
#define __PE_DECL___malloc
typedef __attribute__((ms_abi)) void * t_malloc(size_t Size);
static t_malloc& __malloc = *(t_malloc*)0x14001377C;
#endif
#define malloc __malloc

PROBE_DECL(__Alloc_PPMblock)
__attribute__((ms_abi)) __int64 __Alloc_PPMblock(unsigned int memsize_mb, int a2_order, int a3) {

  PROBE_HIT(__Alloc_PPMblock);
  int v4;           // r14d
  size_t memsize_b; // r13

  v4 = a2_order;
  if(!memsize_mb)
    return 0;
  if(memsize_mb > 0xFFF)
    return 0;
  if(a2_order < 2)
    return 0;
  if(a2_order > 16)
    return 0;
  if(PPMblock_size)
    return 0;
  memsize_b = memsize_mb << 20;
  PPMblock = malloc(memsize_b);
  if(!PPMblock)
    return 0;
  dword_141133660 = -100;
  PPMblock_size = memsize_b;
  dword_141133648 = 0;
  dword_141133658 = a3;
  dword_14113365C = 0;
  if(v4 > 12)
    v4 = 16 << ((v4 + 19) & 31); // x86 shl masks shift count mod 32
  dword_141133654 = v4;
  return 1;
}
// 141133548: using guessed type __int64 PPMblock_size;
// 141133648: using guessed type int dword_141133648;
// 141133654: using guessed type int dword_141133654;
// 141133658: using guessed type int dword_141133658;
// 14113365C: using guessed type int dword_14113365C;
// 141133660: using guessed type int dword_141133660;

// ---- Cleanup --------------------------------------------------------
#undef PPMblock
#undef PPMblock_size
#undef dword_141133648
#undef dword_141133654
#undef dword_141133658
#undef dword_14113365C
#undef dword_141133660
#undef malloc
#undef _BitScanForward
#undef FILE
