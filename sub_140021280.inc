// =====================================================================
// sub_140021280 @ 0x140021280
// CPUID-based CPU feature detection. Calls unknown_libname_21 (CPUID
// wrapper) and unknown_libname_22 (multi-leaf CPUID enumerator).
//
// §8.4 fix: Hex-Rays split the 4-dword CPUID output buffer into
//   _DWORD v31[2] + int v32 + int v33 (adjacent on MSVC stack).
// g++ does not preserve that layout. Merged into _DWORD v31[4].
// =====================================================================

#define FILE FILE1

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___dword_1400285E0
#define __PE_DECL___dword_1400285E0
typedef int t_dword_1400285E0[1];
static t_dword_1400285E0& __dword_1400285E0 = *(t_dword_1400285E0*)0x1400285E0;
#endif
#define dword_1400285E0 __dword_1400285E0
#ifndef __PE_DECL___dword_1400285E8
#define __PE_DECL___dword_1400285E8
typedef int t_dword_1400285E8[1];
static t_dword_1400285E8& __dword_1400285E8 = *(t_dword_1400285E8*)0x1400285E8;
#endif
#define dword_1400285E8 __dword_1400285E8
#ifndef __PE_DECL___dword_1400285EC
#define __PE_DECL___dword_1400285EC
typedef int t_dword_1400285EC[1];
static t_dword_1400285EC& __dword_1400285EC = *(t_dword_1400285EC*)0x1400285EC;
#endif
#define dword_1400285EC __dword_1400285EC
#ifndef __PE_DECL___dword_1400285F0
#define __PE_DECL___dword_1400285F0
typedef int t_dword_1400285F0[521];
static t_dword_1400285F0& __dword_1400285F0 = *(t_dword_1400285F0*)0x1400285F0;
#endif
#define dword_1400285F0 __dword_1400285F0
#ifndef __PE_DECL___dword_140028E14
#define __PE_DECL___dword_140028E14
static int& __dword_140028E14 = *(int*)0x140028E14;
#endif
#define dword_140028E14 __dword_140028E14
#ifndef __PE_DECL___dword_141134C20
#define __PE_DECL___dword_141134C20
static int& __dword_141134C20 = *(int*)0x141134C20;
#endif
#define dword_141134C20 __dword_141134C20
#ifndef __PE_DECL___dword_141134C24
#define __PE_DECL___dword_141134C24
static int& __dword_141134C24 = *(int*)0x141134C24;
#endif
#define dword_141134C24 __dword_141134C24

// ---- PE-internal function references --------------------------------
#ifndef __PE_DECL___strcmp
#define __PE_DECL___strcmp
typedef __attribute__((ms_abi)) int t_strcmp(const char *Str1, const char *Str2);
static t_strcmp& __strcmp = *(t_strcmp*)0x14001AD80;
#endif
#define strcmp __strcmp
#ifndef __PE_DECL___unknown_libname_21
#define __PE_DECL___unknown_libname_21
typedef __attribute__((ms_abi)) __int64 t_unknown_libname_21(_QWORD, _QWORD);
static t_unknown_libname_21& __unknown_libname_21 = *(t_unknown_libname_21*)0x140021670;
#endif
#define unknown_libname_21 __unknown_libname_21
#ifndef __PE_DECL___unknown_libname_22
#define __PE_DECL___unknown_libname_22
typedef __attribute__((ms_abi)) __int64 t_unknown_libname_22(_QWORD, _QWORD);
static t_unknown_libname_22& __unknown_libname_22 = *(t_unknown_libname_22*)0x140021696;
#endif
#define unknown_libname_22 __unknown_libname_22

// strcpy: no MSVC-CRT state, fall through to glibc

PROBE_DECL(__sub_140021280)
__attribute__((ms_abi)) __int64 __sub_140021280() {

  PROBE_HIT(__sub_140021280);
  unsigned int v0;  // ebp
  int v1;           // ebx
  int v2;           // esi
  int v3;           // eax
  unsigned int v4;  // ecx
  int v5;           // edx
  __int64 v6;       // rsi
  int v7;           // r8d
  int v8;           // r10d
  int v9;           // r9d
  int v10;          // r8d
  int v11;          // r9d
  unsigned int v12; // edx
  int v13;          // eax
  unsigned int v14; // edx
  __int64 v15;      // rax
  __int64 v16;      // rbp
  unsigned int v17; // ebp
  int v19;          // ecx
  _BYTE v20[1024];  // [rsp+20h] [rbp-4B8h] BYREF
  char Str2[16];    // [rsp+430h] [rbp-A8h] BYREF
  char v22[16];     // [rsp+440h] [rbp-98h] BYREF
  char Str1[4];     // [rsp+450h] [rbp-88h] BYREF
  int v24;          // [rsp+454h] [rbp-84h]
  int v25;          // [rsp+458h] [rbp-80h]
  char v26;         // [rsp+45Ch] [rbp-7Ch]
  __int128 v27;     // [rsp+460h] [rbp-78h] BYREF
  __int128 v28;     // [rsp+470h] [rbp-68h] BYREF
  __int128 v29;     // [rsp+480h] [rbp-58h] BYREF
  __int128 v30;     // [rsp+490h] [rbp-48h] BYREF
  // §8.4: v31[2]+v32+v33 are four adjacent dwords; CPUID writes all four.
  _DWORD v31[4];    // [rsp+4A4h] [rbp-34h] BYREF  (eax,ebx,ecx,edx)
#define v32 v31[2]
#define v33 v31[3]

  strcpy(Str2, "GenuineIntel");
  v0 = 0;
  strcpy(v22, "AuthenticAMD");
  v27 = 0;
  v28 = 0;
  v29 = 0;
  v30 = 0;
  unknown_libname_21(1, v31);
  v1 = v33;
  unknown_libname_21(0, v31);
  v2 = v31[0];
  *(_DWORD *)Str1 = v31[1];
  v26 = 0;
  v24 = v33;
  v25 = v32;
  if(strcmp(Str1, Str2)) {
    dword_141134C20 = 0;
    v17 = 0;
    if(!strcmp(Str1, v22)) {
      v17 = (v1 & 0x800000u) >> 23;
      unknown_libname_21(0x80000000LL, v31);
      if(v31[0] >= 0x80000006) {
        unknown_libname_21(0x80000006LL, v31);
        dword_141134C20 = HIWORD(v32) << 10;
      }
    }
    goto LABEL_36;
  }
  if(v2 >= 4) {
    v3 = unknown_libname_22(4, v20);
    v4 = 0;
    if(v3 > 0) {
      v5 = dword_141134C24;
      do {
        v6 = (int)(4 * v4);
        v7 = ((*(_DWORD *)&v20[4 * v6 + 4] >> 12) & 0x3FF) + 1;
        v8 = v7 * ((*(_DWORD *)&v20[4 * v6 + 4] & 0xFFF) + 1);
        v9 = *(_DWORD *)&v20[4 * v6 + 4] >> 22;
        v10 = v9 * v7;
        v11 = v8 * v9;
        if(v8 >= v5)
          v5 = v8;
        ++v4;
        if(*(_DWORD *)&v20[4 * v6 + 8] * (v11 + v8) + v8 + v10 * ((*(_DWORD *)&v20[4 * v6 + 4] & 0xFFFu) + 1) > v0)
          v0 = *(_DWORD *)&v20[4 * v6 + 8] * (v11 + v8) + v8 + v10 * ((*(_DWORD *)&v20[4 * v6 + 4] & 0xFFF) + 1);
      } while(v4 < v3);
      dword_141134C24 = v5;
    }
    goto LABEL_13;
  }
  if(v2 >= 2) {
  LABEL_13:
    unknown_libname_21(2, &v27);
    if((unsigned __int8)v27 > 1u) {
      unknown_libname_21(2, &v28);
      if((unsigned __int8)v28 > 2u) {
        unknown_libname_21(2, &v29);
        if((unsigned __int8)v29 > 3u)
          unknown_libname_21(2, &v30);
      }
    }
  }
  v12 = 0;
  LOBYTE(v27) = 0;
  LOBYTE(v28) = 0;
  LOBYTE(v29) = 0;
  LOBYTE(v30) = 0;
  v13 = 0;
  do {
    if((*((_BYTE *)&v27 + v13 + 3) & 0x80) != 0) {
      *((_BYTE *)&v27 + v13) = 0;
      *((_BYTE *)&v27 + v13 + 1) = 0;
      *((_BYTE *)&v27 + v13 + 2) = 0;
      *((_BYTE *)&v27 + v13 + 3) = 0;
    }
    v13 += 4;
    ++v12;
  } while(v12 < 0x10);
  v14 = 0;
  if(v0) {
    dword_141134C20 = v0;
  } else {
    v15 = 0;
    while(*((unsigned __int8 *)&v27 + v15) != 255) {
      v16 = 0;
      while(*((unsigned __int8 *)&v27 + v15) != dword_1400285E0[v16]) {
        v16 += 5;
        if(v16 >= 525)
          goto LABEL_28;
      }
      if(dword_1400285E8[v16] > v14) {
        v14 = dword_1400285E8[v16];
        v19 = dword_1400285EC[v16];
        if(dword_1400285F0[v16] == 1)
          v19 *= 2;
        dword_141134C24 = v19;
      }
    LABEL_28:
      if(++v15 >= 64)
        goto LABEL_29;
    }
    dword_141134C24 = 0;
    v14 = 0;
  LABEL_29:
    dword_141134C20 = v14 << 10;
  }
  if((v1 & 0x4000000) != 0)
    v17 = 2;
  else
    v17 = (v1 & 0x800000u) >> 23;
LABEL_36:
  dword_140028E14 = v17;
  return v17;
#undef v32
#undef v33
}

// ---- Cleanup --------------------------------------------------------
#undef dword_1400285E0
#undef dword_1400285E8
#undef dword_1400285EC
#undef dword_1400285F0
#undef dword_140028E14
#undef dword_141134C20
#undef dword_141134C24
#undef strcmp
#undef unknown_libname_21
#undef unknown_libname_22
#undef FILE
