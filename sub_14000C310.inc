// =====================================================================
// sub_14000C310 @ 0x14000C310
// Auto-extracted scaffold. REVIEW: see TODO comments below.
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
#ifndef __PE_DECL___dword_141133670
#define __PE_DECL___dword_141133670
static int& __dword_141133670 = *(int*)0x141133670;
#endif
#define dword_141133670 __dword_141133670
#ifndef __PE_DECL___dword_141133710
#define __PE_DECL___dword_141133710
static int& __dword_141133710 = *(int*)0x141133710;
#endif
#define dword_141133710 __dword_141133710
#ifndef __PE_DECL___xmmword_140029500
#define __PE_DECL___xmmword_140029500
typedef __int128 t_xmmword_140029500[1];
static t_xmmword_140029500& __xmmword_140029500 = *(t_xmmword_140029500*)0x140029500;
#endif
#define xmmword_140029500 __xmmword_140029500
#ifndef __PE_DECL___xmmword_140029510
#define __PE_DECL___xmmword_140029510
typedef __int128 t_xmmword_140029510[1];
static t_xmmword_140029510& __xmmword_140029510 = *(t_xmmword_140029510*)0x140029510;
#endif
#define xmmword_140029510 __xmmword_140029510
#ifndef __PE_DECL___xmmword_140029520
#define __PE_DECL___xmmword_140029520
typedef __int128 t_xmmword_140029520[1];
static t_xmmword_140029520& __xmmword_140029520 = *(t_xmmword_140029520*)0x140029520;
#endif
#define xmmword_140029520 __xmmword_140029520
#ifndef __PE_DECL___xmmword_140029530
#define __PE_DECL___xmmword_140029530
typedef __int128 t_xmmword_140029530[1];
static t_xmmword_140029530& __xmmword_140029530 = *(t_xmmword_140029530*)0x140029530;
#endif
#define xmmword_140029530 __xmmword_140029530

// ---- PE-internal function references --------------------------------
#ifndef __PE_DECL___filbuf
#define __PE_DECL___filbuf
typedef __attribute__((ms_abi)) int t_filbuf(FILE *File);
static t_filbuf& __filbuf = *(t_filbuf*)0x1400133CC;
#endif
#define filbuf __filbuf
#define sub_14000C560 __sub_14000C560
#define sub_140010A40 __sub_140010A40
#define sub_14001D7A0 __sub_14001D7A0

PROBE_DECL(__sub_14000C310)
__attribute__((ms_abi)) __int64 __sub_14000C310(FILE *a1, FILE *a2, __attribute__((ms_abi)) __int64(*a3_printstats)(FILE *, FILE *, __int64), int a4) {

  PROBE_HIT(__sub_14000C310);
  int v9;      // esi
  __int64 v10; // rax
  int cnt;     // edx
  int v12;     // edx
  int v13;     // ebx
  int v14;     // edx
  int v15;     // eax
  int v16;     // ebx
  int v17;     // edx
  int v18;     // eax
  int v19;     // ebx
  int v20;     // edx
  int v21;     // eax
  int v22;     // ebx
  int v23;     // edx
  int v24;     // eax

  if(!PPMblock_size)
    return 0;
  if(dword_14113365C) {
    dword_14113365C = 0;
    dword_141133664 = 1;
  } else {
    cnt = a2->_cnt;
    dword_141133670 = -1;
    v12 = cnt - 1;
    a2->_cnt = v12;
    if(v12 < 0) {
      dword_141133710 = 0;
      v13 = filbuf(a2);
      v12 = a2->_cnt;
    } else {
      v13 = *(unsigned __int8 *)a2->_ptr++;
    }
    v14 = v12 - 1;
    a2->_cnt = v14;
    if(v14 < 0) {
      dword_141133710 = v13;
      v15 = filbuf(a2);
      v14 = a2->_cnt;
    } else {
      v15 = *(unsigned __int8 *)a2->_ptr++;
    }
    v16 = v15 | (v13 << 8);
    v17 = v14 - 1;
    a2->_cnt = v17;
    if(v17 < 0) {
      dword_141133710 = v16;
      v18 = filbuf(a2);
      v17 = a2->_cnt;
    } else {
      v18 = *(unsigned __int8 *)a2->_ptr++;
    }
    v19 = v18 | (v16 << 8);
    v20 = v17 - 1;
    a2->_cnt = v20;
    if(v20 < 0) {
      dword_141133710 = v19;
      v21 = filbuf(a2);
      v20 = a2->_cnt;
    } else {
      v21 = *(unsigned __int8 *)a2->_ptr++;
    }
    v22 = v21 | (v19 << 8);
    v23 = v20 - 1;
    a2->_cnt = v23;
    if(v23 < 0) {
      dword_141133710 = v22;
      v24 = filbuf(a2);
    } else {
      v24 = *(unsigned __int8 *)a2->_ptr++;
    }
    dword_141133710 = v24 | (v22 << 8);
    sub_140010A40(a4);
  }
  while(1) {
    sub_14000C560(a1, a2);
    if(dword_141133664)
      break;
    if(a3_printstats)
      v9 = a3_printstats(a1, a2, 0);
    else
      v9 = -1;
    dword_141133664 = v9;
    v10 = 64;
    do {
      xmmword_140029530[v10] = 0;
      xmmword_140029520[v10] = 0;
      xmmword_140029510[v10] = 0;
      xmmword_140029500[v10] = 0;
      v10 -= 4;
    } while(v10 * 16);
    sub_14001D7A0(dword_14010A158, 0, 3072);
    if(!v9) {
      dword_14113365C = 1;
      return 0;
    }
  }
  if(a3_printstats)
    a3_printstats(a1, a2, 1);
  return 1;
}
// 140029500: using guessed type __int128 xmmword_140029500[];
// 140029510: using guessed type __int128 xmmword_140029510[];
// 140029520: using guessed type __int128 xmmword_140029520[];
// 140029530: using guessed type __int128 xmmword_140029530[];
// 14010A158: using guessed type int dword_14010A158[256];
// 141133548: using guessed type __int64 PPMblock_size;
// 14113365C: using guessed type int dword_14113365C;
// 141133664: using guessed type int dword_141133664;
// 141133670: using guessed type int dword_141133670;
// 141133710: using guessed type int dword_141133710;

// ---- Cleanup --------------------------------------------------------
#undef PPMblock_size
#undef dword_14010A158
#undef dword_14113365C
#undef dword_141133664
#undef dword_141133670
#undef dword_141133710
#undef xmmword_140029500
#undef xmmword_140029510
#undef xmmword_140029520
#undef xmmword_140029530
#undef filbuf
#undef sub_14000C560
#undef sub_140010A40
#undef sub_14001D7A0
#undef FILE
