// =====================================================================
// sub_140010850 @ 0x140010850
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// Guard prevents sub_14000C560.inc's typedef+static-ref from conflicting
// with this C++ function definition.
#define __PE_DECL___sub_140010850

PROBE_DECL(__sub_140010850)
__attribute__((ms_abi)) __int64 __sub_140010850(__int64 a1) {

  PROBE_HIT(__sub_140010850);
  int v2;           // ebp
  int v3;           // edi
  int v4;           // r11d
  unsigned int v5;  // r10d
  char v6;          // cl
  unsigned int v7;  // r9d
  int v8;           // r15d
  unsigned int v9;  // edi
  int v10;          // r8d
  unsigned int v11; // edi
  __int64 result;   // rax
  int v13;          // edi
  unsigned int v14; // ebp
  int v15;          // ebp
  BOOL v16;         // r15d
  int v17;          // r10d

  v2 = *(unsigned __int16 *)(a1 + 6);
  v3 = HIWORD(*(_DWORD *)a1);
  v4 = (unsigned __int16)*(_DWORD *)a1;
  v5 = *(unsigned __int16 *)(a1 + 4);
  v6 = 1;
  v7 = ((v5 >> 1) + (v4 << 15)) / v5;
  if(v7 >= 0x7FFF)
    v7 = 0x7FFF;
  if(v7 <= 1)
    v7 = 1;
  v8 = (v3 - v7) * (v3 - v7);
  v9 = (0x10000 - (v7 + v3)) * (v7 + v3);
  v10 = 4096;
  if(v2 < 4096)
    v10 = v2;
  v11 = (v2 * (v9 >> 11)) >> 4;
  if(v10 <= 24 || v10 == 4096)
    v6 = 14;
  if(2 * v8 <= 3 * v11) {
    result = v10 * (((v11 >> v6) + 5 * v8) / v11 + 1);
    if((unsigned int)result >= 0x2000)
      result = 0x2000;
  } else {
    result = 0x2000;
  }
  if((unsigned __int16)result <= 0x40u && (unsigned __int16)result <= (unsigned int)v2) {
    if((unsigned __int16)result <= 0x20u)
      LOWORD(v13) = result - ((1 - (unsigned int)(unsigned __int16)result) >> 31) - ((24 - (unsigned int)(unsigned __int16)result) >> 31);
    else
      LOWORD(v13) = result - 8;
    *(_WORD *)(a1 + 6) = v13;
  } else {
    v13 = (unsigned __int16)result >> 1;
    *(_WORD *)(a1 + 6) = v13;
  }
  if((unsigned __int16)v13 <= 2u) {
    v15 = 17 * (8 * v4 < v5);
    v16 = 8 * (v5 - v4) < v5;
    v17 = 2 * v5;
    result = (unsigned int)(1431655766 * v17);
    v14 = (-6 * v16 + v15 + 2 * v4) / 3u;
    *(_WORD *)(a1 + 4) = (unsigned)v17 / 3u;
  } else {
    *(_WORD *)(a1 + 4) = v5 >> 1;
    v14 = (unsigned int)(v4 + -12 * (6 * (v5 - v4) < v5) + 16 * (unsigned int)(4 * v4 < v5)) >> 1;
  }
  *(_DWORD *)a1 = (v7 << 16) | v14;
  return result;
}

// ---- Cleanup --------------------------------------------------------
#undef _BitScanForward
#undef FILE
