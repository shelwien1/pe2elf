// =====================================================================
// sub_140010730 @ 0x140010730
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___qword_141133580
#define __PE_DECL___qword_141133580
static __int64& __qword_141133580 = *(__int64*)0x141133580;
#endif
#define qword_141133580 __qword_141133580

PROBE_DECL(__sub_140010730)
__attribute__((ms_abi)) __int64 __sub_140010730(__int64 a1) {

  PROBE_HIT(__sub_140010730);
  unsigned int v1; // r9d
  unsigned int v2; // r10d
  unsigned int v3; // edi
  unsigned int v4; // r11d
  unsigned int v5; // eax
  unsigned int v6; // edi
  unsigned int v7; // eax
  __int64 result;  // rax
  unsigned int v9; // edi
  __int16 v10;     // r8

  v1 = *(unsigned __int16 *)(a1 + 4);
  v2 = *(unsigned __int16 *)(a1 + 6) * (*(_DWORD *)a1 / (11 * v1) + 1);
  if(v2 >= 0x800)
    LOWORD(v2) = 2048;
  v3 = *(unsigned __int8 *)qword_141133580 + 1;
  v4 = *(unsigned __int16 *)(a1 + 4) / v3;
  v5 = (256 - v3) * *(unsigned __int16 *)(qword_141133580 + 2) / v3;
  v6 = 16 * v3;
  v7 = v4 * v5;
  if(*(_DWORD *)a1 < v7)
    v7 = *(_DWORD *)a1;
  if(v1 > v6)
    v6 = *(unsigned __int16 *)(a1 + 4);
  result = v7 - (v7 >> 1);
  v9 = v6 - (v6 >> 1);
  if((unsigned __int16)v2 <= 0x400u) {
    *(_WORD *)(a1 + 4) = v9;
    *(_DWORD *)a1 = result;
    if((unsigned __int16)v2 <= 0x200u) {
      if((unsigned __int16)v2 <= 0x40u) {
        result = (32 - (unsigned int)(unsigned __int16)v2) >> 31;
        v10 = v2 - result;
      } else {
        v10 = v2 - 32;
      }
      *(_WORD *)(a1 + 6) = v10;
    } else {
      *(_WORD *)(a1 + 6) = v2 - 128;
    }
  } else {
    *(_DWORD *)a1 = result - ((unsigned int)result >> 1);
    *(_WORD *)(a1 + 4) = v9 - ((unsigned __int16)v9 >> 1);
    *(_WORD *)(a1 + 6) = (unsigned __int16)v2 >> 1;
    return (unsigned __int16)v9 >> 1;
  }
  return result;
}
// 141133580: using guessed type __int64 qword_141133580;

// ---- Cleanup --------------------------------------------------------
#undef qword_141133580
#undef FILE
