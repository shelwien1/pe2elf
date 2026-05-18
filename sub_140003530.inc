// =====================================================================
// sub_140003530 @ 0x140003530
// Arithmetic-coder flush / frame writer.  Takes a callback (PrintStats)
// invoked via Win64 ABI, so the function-pointer parameter must be
// typed with __attribute__((ms_abi)) -- without it the call site uses
// SysV (RDI/RSI) and corrupts the PE callee's register state.
//
// The 4-xmmword zeroing loop in the donor body is a Hex-Rays expansion
// of `memset((char*)0x140029540, 0, 0x400)` (asm: pxor xmm0,xmm0 +
// movaps stream).  Reproducing it via __int128 array indexing across
// four overlapping 16-byte symbols is fragile under g++; replaced with
// a direct memset against the contiguous region.
// =====================================================================

#define FILE FILE1

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___PPMblock_size
#define __PE_DECL___PPMblock_size
static __int64& __PPMblock_size = *(__int64*)0x141133548;
#endif
#define PPMblock_size __PPMblock_size
#ifndef __PE_DECL___dword_14010A158
#define __PE_DECL___dword_14010A158
typedef int t_dword_14010A158[256];
static t_dword_14010A158& __dword_14010A158 = *(t_dword_14010A158*)0x14010A158;
#endif
#define dword_14010A158 __dword_14010A158
#ifndef __PE_DECL___dword_14113365C
#define __PE_DECL___dword_14113365C
static int& __dword_14113365C = *(int*)0x14113365C;
#endif
#define dword_14113365C __dword_14113365C
#ifndef __PE_DECL___dword_141133664
#define __PE_DECL___dword_141133664
static int& __dword_141133664 = *(int*)0x141133664;
#endif
#define dword_141133664 __dword_141133664
#ifndef __PE_DECL___dword_141133668
#define __PE_DECL___dword_141133668
static int& __dword_141133668 = *(int*)0x141133668;
#endif
#define dword_141133668 __dword_141133668
#ifndef __PE_DECL___dword_14113366C
#define __PE_DECL___dword_14113366C
static int& __dword_14113366C = *(int*)0x14113366C;
#endif
#define dword_14113366C __dword_14113366C
#ifndef __PE_DECL___dword_141133670
#define __PE_DECL___dword_141133670
static int& __dword_141133670 = *(int*)0x141133670;
#endif
#define dword_141133670 __dword_141133670
#ifndef __PE_DECL___qword_141133640
#define __PE_DECL___qword_141133640
static __int64& __qword_141133640 = *(__int64*)0x141133640;
#endif
#define qword_141133640 __qword_141133640

// ---- PE-internal function references --------------------------------
#ifndef __PE_DECL___flsbuf
#define __PE_DECL___flsbuf
typedef __attribute__((ms_abi)) int t_flsbuf(int Ch, FILE *File);
static t_flsbuf& __flsbuf = *(t_flsbuf*)0x14001323C;
#endif
#define flsbuf __flsbuf
#ifndef __PE_DECL___sub_1400037A0
#define __PE_DECL___sub_1400037A0
typedef __attribute__((ms_abi)) int t_sub_1400037A0(FILE *a1, FILE *a2);
static t_sub_1400037A0& __sub_1400037A0 = *(t_sub_1400037A0*)0x1400037A0;
#endif
#define sub_1400037A0 __sub_1400037A0
#ifndef __PE_DECL___sub_140010A40
#define __PE_DECL___sub_140010A40
typedef __attribute__((ms_abi)) __int64 t_sub_140010A40(int a1);
static t_sub_140010A40& __sub_140010A40 = *(t_sub_140010A40*)0x140010A40;
#endif
#define sub_140010A40 __sub_140010A40
#ifndef __PE_DECL___sub_14001D7A0
#define __PE_DECL___sub_14001D7A0
typedef __attribute__((ms_abi)) __int64 t_sub_14001D7A0(int *a1, unsigned __int8 a2, __int64 a3);
static t_sub_14001D7A0& __sub_14001D7A0 = *(t_sub_14001D7A0*)0x14001D7A0;
#endif
#define sub_14001D7A0 __sub_14001D7A0

PROBE_DECL(__sub_140003530)
__attribute__((ms_abi)) __int64 __sub_140003530(
    FILE *File,
    FILE *a2,
    __attribute__((ms_abi)) __int64 (*a3)(FILE *, FILE *, __int64),
    int a4) {
  PROBE_HIT(__sub_140003530);
  int v8;      // r13d
  __int64 v10; // rcx
  int v11;     // r13d
  int v12;     // edi
  __int64 v14; // r12
  int v15;     // r12d
  int v16;     // ecx

  if(!PPMblock_size)
    return 0;
  if(dword_14113365C) {
    dword_14113365C = 0;
    dword_141133664 = 1;
  } else {
    qword_141133640 = 0;
    dword_141133668 = 0;
    dword_141133670 = -1;
    dword_14113366C = 0;
    sub_140010A40(a4);
  }
  while(1) {
    sub_1400037A0(File, a2);
    if(dword_141133664)
      break;
    if(a3)
      v8 = a3(a2, File, 0);
    else
      v8 = -1;
    dword_141133664 = v8;
    // Original asm: pxor xmm0,xmm0 + 4 movaps streams clearing 1024
    // bytes starting at 0x140029540 (= xmmword_140029500 + 4 slots).
    memset((void*)0x140029540, 0, 0x400);
    sub_14001D7A0(dword_14010A158, 0, 3072);
    if(!v8) {
      dword_14113365C = 1;
      return 0;
    }
  }
  v10 = qword_141133640;
  v11 = 0;
  v12 = dword_14113366C;
  do {
    if((v10 ^ 0xFF000000LL) <= 0xFFFFFF) {
      dword_14113366C = ++v12;
    } else {
      if(--File->_cnt < 0) {
        flsbuf(dword_141133668 + HIDWORD(v10), File);
        LODWORD(v10) = qword_141133640;
        v14 = qword_141133640 >> 32;
      } else {
        v14 = v10 >> 32;
        *File->_ptr++ = BYTE4(v10) + dword_141133668;
      }
      v15 = v14 + 255;
      if(v12) {
        do {
          v16 = File->_cnt - 1;
          File->_cnt = v16;
          if(v16 < 0)
            flsbuf(v15, File);
          else
            *File->_ptr++ = v15;
          dword_14113366C = --v12;
        } while(v12);
        LODWORD(v10) = qword_141133640;
      }
      dword_141133668 = BYTE3(v10);
    }
    v10 = (unsigned int)((_DWORD)v10 << 8);
    qword_141133640 = v10;
    ++v11;
  } while(v11 < 5);
  if(a3)
    a3(a2, File, 1);
  return 1;
}

#undef PPMblock_size
#undef dword_14010A158
#undef dword_14113365C
#undef dword_141133664
#undef dword_141133668
#undef dword_14113366C
#undef dword_141133670
#undef qword_141133640
#undef flsbuf
#undef sub_1400037A0
#undef sub_140010A40
#undef sub_14001D7A0
#undef FILE
