// =====================================================================
// sub_140002AD0 @ 0x140002AD0
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---- TODO: unresolved identifiers (locals, intrinsics, or typos) ----
//   call:  _mm_add_epi32
//   call:  _mm_add_epi8
//   call:  _mm_and_si128
//   call:  _mm_andnot_si128
//   call:  _mm_cmpeq_epi32
//   call:  _mm_cvtsi32_si128
//   call:  _mm_load_si128
//   call:  _mm_or_si128
//   call:  _mm_slli_epi32
//   call:  _mm_unpacklo_epi16
//   call:  _mm_unpacklo_epi32
//   call:  _mm_unpacklo_epi8
//   call:  _mm_xor_si128

// ---- WARNING: patterns that need manual rewrite ----
//   (__m128i)0LL  ->  rewrite as _mm_setzero_si128()
//   `(char*)&<local> + v<N>` -- Hex-Rays expanded a memcpy into pointer arithmetic across adjacent locals. g++ does NOT preserve that layout. Rewrite as memmove against the conceptual source struct.

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___arch_hdr
#define __PE_DECL___arch_hdr
typedef int t_arch_hdr[16];
static t_arch_hdr& __arch_hdr = *(t_arch_hdr*)0x140028E50;
#endif
#define arch_hdr __arch_hdr
#ifndef __PE_DECL___byte_140022900
#define __PE_DECL___byte_140022900
typedef char t_byte_140022900[16];
static t_byte_140022900& __byte_140022900 = *(t_byte_140022900*)0x140022900;
#endif
#define byte_140022900 __byte_140022900
#ifndef __PE_DECL___byte_140022910
#define __PE_DECL___byte_140022910
typedef char t_byte_140022910[16];
static t_byte_140022910& __byte_140022910 = *(t_byte_140022910*)0x140022910;
#endif
#define byte_140022910 __byte_140022910
#ifndef __PE_DECL___byte_140022920
#define __PE_DECL___byte_140022920
typedef char t_byte_140022920[8];
static t_byte_140022920& __byte_140022920 = *(t_byte_140022920*)0x140022920;
#endif
#define byte_140022920 __byte_140022920
#ifndef __PE_DECL___byte_140022928
#define __PE_DECL___byte_140022928
typedef char t_byte_140022928[8];
static t_byte_140022928& __byte_140022928 = *(t_byte_140022928*)0x140022928;
#endif
#define byte_140022928 __byte_140022928
#ifndef __PE_DECL___byte_140029000
#define __PE_DECL___byte_140029000
typedef char t_byte_140029000[1];
static t_byte_140029000& __byte_140029000 = *(t_byte_140029000*)0x140029000;
#endif
#define byte_140029000 __byte_140029000
#ifndef __PE_DECL___byte_140029240
#define __PE_DECL___byte_140029240
typedef char t_byte_140029240[126];
static t_byte_140029240& __byte_140029240 = *(t_byte_140029240*)0x140029240;
#endif
#define byte_140029240 __byte_140029240
#ifndef __PE_DECL___byte_1400292C0
#define __PE_DECL___byte_1400292C0
static _UNKNOWN& __byte_1400292C0 = *(_UNKNOWN*)0x1400292C0;
#endif
#define byte_1400292C0 __byte_1400292C0
#ifndef __PE_DECL___byte_1400293C0
#define __PE_DECL___byte_1400293C0
typedef char t_byte_1400293C0[128];
static t_byte_1400293C0& __byte_1400293C0 = *(t_byte_1400293C0*)0x1400293C0;
#endif
#define byte_1400293C0 __byte_1400293C0
#ifndef __PE_DECL___byte_140029440
#define __PE_DECL___byte_140029440
typedef char t_byte_140029440[1];
static t_byte_140029440& __byte_140029440 = *(t_byte_140029440*)0x140029440;
#endif
#define byte_140029440 __byte_140029440
#ifndef __PE_DECL___xmmword_140022850
#define __PE_DECL___xmmword_140022850
static __int128& __xmmword_140022850 = *(__int128*)0x140022850;
#endif
#define xmmword_140022850 __xmmword_140022850
#ifndef __PE_DECL___xmmword_140022860
#define __PE_DECL___xmmword_140022860
static __int128& __xmmword_140022860 = *(__int128*)0x140022860;
#endif
#define xmmword_140022860 __xmmword_140022860
#ifndef __PE_DECL___xmmword_140022870
#define __PE_DECL___xmmword_140022870
static __int128& __xmmword_140022870 = *(__int128*)0x140022870;
#endif
#define xmmword_140022870 __xmmword_140022870
#ifndef __PE_DECL___xmmword_140022880
#define __PE_DECL___xmmword_140022880
static __int128& __xmmword_140022880 = *(__int128*)0x140022880;
#endif
#define xmmword_140022880 __xmmword_140022880
#ifndef __PE_DECL___xmmword_140022890
#define __PE_DECL___xmmword_140022890
static __int128& __xmmword_140022890 = *(__int128*)0x140022890;
#endif
#define xmmword_140022890 __xmmword_140022890
#ifndef __PE_DECL___xmmword_1400228A0
#define __PE_DECL___xmmword_1400228A0
static __int128& __xmmword_1400228A0 = *(__int128*)0x1400228A0;
#endif
#define xmmword_1400228A0 __xmmword_1400228A0
#ifndef __PE_DECL___xmmword_1400228B0
#define __PE_DECL___xmmword_1400228B0
static __int128& __xmmword_1400228B0 = *(__int128*)0x1400228B0;
#endif
#define xmmword_1400228B0 __xmmword_1400228B0
#ifndef __PE_DECL___xmmword_1400228C0
#define __PE_DECL___xmmword_1400228C0
static __int128& __xmmword_1400228C0 = *(__int128*)0x1400228C0;
#endif
#define xmmword_1400228C0 __xmmword_1400228C0
#ifndef __PE_DECL___xmmword_1400228D0
#define __PE_DECL___xmmword_1400228D0
static __int128& __xmmword_1400228D0 = *(__int128*)0x1400228D0;
#endif
#define xmmword_1400228D0 __xmmword_1400228D0
#ifndef __PE_DECL___xmmword_1400228E0
#define __PE_DECL___xmmword_1400228E0
static __int128& __xmmword_1400228E0 = *(__int128*)0x1400228E0;
#endif
#define xmmword_1400228E0 __xmmword_1400228E0
#ifndef __PE_DECL___xmmword_140028F00
#define __PE_DECL___xmmword_140028F00
typedef __int128 t_xmmword_140028F00[1];
static t_xmmword_140028F00& __xmmword_140028F00 = *(t_xmmword_140028F00*)0x140028F00;
#endif
#define xmmword_140028F00 __xmmword_140028F00
#ifndef __PE_DECL___xmmword_140028F10
#define __PE_DECL___xmmword_140028F10
typedef __int128 t_xmmword_140028F10[1];
static t_xmmword_140028F10& __xmmword_140028F10 = *(t_xmmword_140028F10*)0x140028F10;
#endif
#define xmmword_140028F10 __xmmword_140028F10
#ifndef __PE_DECL___xmmword_140028F20
#define __PE_DECL___xmmword_140028F20
typedef __int128 t_xmmword_140028F20[1];
static t_xmmword_140028F20& __xmmword_140028F20 = *(t_xmmword_140028F20*)0x140028F20;
#endif
#define xmmword_140028F20 __xmmword_140028F20
#ifndef __PE_DECL___xmmword_140028F30
#define __PE_DECL___xmmword_140028F30
typedef __int128 t_xmmword_140028F30[1];
static t_xmmword_140028F30& __xmmword_140028F30 = *(t_xmmword_140028F30*)0x140028F30;
#endif
#define xmmword_140028F30 __xmmword_140028F30
#ifndef __PE_DECL___xmmword_140029100
#define __PE_DECL___xmmword_140029100
typedef __int128 t_xmmword_140029100[1];
static t_xmmword_140029100& __xmmword_140029100 = *(t_xmmword_140029100*)0x140029100;
#endif
#define xmmword_140029100 __xmmword_140029100
#ifndef __PE_DECL___xmmword_140029110
#define __PE_DECL___xmmword_140029110
static _UNKNOWN& __xmmword_140029110 = *(_UNKNOWN*)0x140029110;
#endif
#define xmmword_140029110 __xmmword_140029110
#ifndef __PE_DECL___xmmword_140029120
#define __PE_DECL___xmmword_140029120
typedef __int128 t_xmmword_140029120[1];
static t_xmmword_140029120& __xmmword_140029120 = *(t_xmmword_140029120*)0x140029120;
#endif
#define xmmword_140029120 __xmmword_140029120
#ifndef __PE_DECL___xmmword_140029130
#define __PE_DECL___xmmword_140029130
typedef __int128 t_xmmword_140029130[1];
static t_xmmword_140029130& __xmmword_140029130 = *(t_xmmword_140029130*)0x140029130;
#endif
#define xmmword_140029130 __xmmword_140029130
#ifndef __PE_DECL___xmmword_140029200
#define __PE_DECL___xmmword_140029200
typedef __int128 t_xmmword_140029200[1];
static t_xmmword_140029200& __xmmword_140029200 = *(t_xmmword_140029200*)0x140029200;
#endif
#define xmmword_140029200 __xmmword_140029200
#ifndef __PE_DECL___xmmword_141133520
#define __PE_DECL___xmmword_141133520
static __int128& __xmmword_141133520 = *(__int128*)0x141133520;
#endif
#define xmmword_141133520 __xmmword_141133520

PROBE_DECL(__sub_140002AD0)
__attribute__((ms_abi)) __int64 __sub_140002AD0() {

  PROBE_HIT(__sub_140002AD0);
  unsigned int v0;   // esi
  char v1;           // dl
  int v2;            // ebx
  unsigned int v3;   // ebp
  int v4;            // edi
  int v5;            // ebx
  unsigned int v6;   // ecx
  unsigned int v7;   // eax
  unsigned int v8;   // r9d
  unsigned int i;    // r8d
  __m128i si128;     // xmm1
  unsigned int v11;  // eax
  __m128i v12;       // xmm2
  unsigned int v13;  // edx
  unsigned int v14;  // ecx
  unsigned int v15;  // ebx
  unsigned int v16;  // ebp
  unsigned int v17;  // esi
  unsigned int v18;  // edi
  unsigned int v19;  // r8d
  unsigned int v20;  // r9d
  unsigned int v21;  // r10d
  unsigned int v22;  // r11d
  unsigned int v23;  // r12d
  unsigned int v24;  // r13d
  unsigned int v25;  // r14d
  unsigned int v26;  // r15d
  unsigned int v27;  // eax
  __m128i v28;       // xmm3
  unsigned int v29;  // edx
  __m128i v30;       // xmm5
  __m128i v31;       // xmm4
  __m128i v32;       // xmm2
  unsigned int v33;  // edi
  __m128i v34;       // xmm2
  unsigned int v35;  // ebp
  unsigned int j;    // ebx
  int v37;           // ebp
  unsigned int v38;  // edx
  unsigned int v39;  // r8d
  unsigned int v40;  // ebx
  unsigned int k;    // ecx
  __m128i v42;       // xmm1
  unsigned int v43;  // eax
  unsigned int v44;  // edx
  unsigned int v45;  // ecx
  unsigned int v46;  // ebx
  unsigned int v47;  // ebp
  unsigned int v48;  // esi
  unsigned int v49;  // edi
  unsigned int v50;  // r8d
  unsigned int v51;  // r9d
  unsigned int v52;  // r10d
  unsigned int v53;  // r11d
  unsigned int v54;  // r12d
  unsigned int v55;  // r13d
  unsigned int v56;  // r14d
  unsigned int v57;  // r15d
  __m128i v58;       // xmm2
  unsigned int v59;  // eax
  __m128i v60;       // xmm3
  __m128i v61;       // xmm2
  __m128i v62;       // xmm6
  __m128i v63;       // xmm3
  __m128i v64;       // xmm0
  unsigned int v65;  // r8d
  unsigned int v66;  // ecx
  __m128i v67;       // xmm2
  int v68;           // ecx
  unsigned int m;    // esi
  unsigned int v70;  // edx
  unsigned int n;    // eax
  __m128i v72;       // xmm0
  __int64 v73;       // rdx
  __int64 v74;       // rsi
  char v75;          // bp
  int v76;           // ebx
  __int64 result;    // rax
  int v78;           // ecx
  unsigned int ii;   // edx
  __m128i v80;       // xmm0
  __int64 v81;       // rcx
  __m128i v82;       // xmm6
  __m128i v83;       // xmm5
  __m128i v84;       // xmm0
  __m128i v85;       // xmm2
  __m128i v86;       // xmm3
  __m128i v87;       // xmm4
  unsigned int v88;  // edx
  __m128i v89;       // xmm1
  __m128i v90;       // xmm13
  __m128i v91;       // xmm10
  __m128i v92;       // xmm9
  __m128i v93;       // xmm11
  __m128i v94;       // xmm8
  __m128i v95;       // xmm10
  unsigned int v96;  // ecx
  int v97;           // edx
  int v98;           // esi
  unsigned int v99;  // ecx
  int v100;          // edx
  int v101;          // esi
  unsigned int v102; // ecx
  int v103;          // edx
  int v104;          // ebp
  unsigned int v105; // ecx
  int v106;          // edx
  int v107;          // ebp
  unsigned int v108; // eax
  int v109;          // [rsp+30h] [rbp-C8h]
  unsigned int v110; // [rsp+30h] [rbp-C8h]
  unsigned int v111; // [rsp+38h] [rbp-C0h]
  int v112;          // [rsp+38h] [rbp-C0h]
  unsigned int v113; // [rsp+40h] [rbp-B8h]
  unsigned int v114; // [rsp+40h] [rbp-B8h]
  unsigned int v115; // [rsp+48h] [rbp-B0h]
  unsigned int v116; // [rsp+48h] [rbp-B0h]
  unsigned int v117; // [rsp+50h] [rbp-A8h]
  unsigned int v118; // [rsp+50h] [rbp-A8h]
  unsigned int v119; // [rsp+58h] [rbp-A0h]
  unsigned int v120; // [rsp+58h] [rbp-A0h]
  int v121;          // [rsp+60h] [rbp-98h]
  unsigned int v122; // [rsp+68h] [rbp-90h]

  LODWORD(xmmword_141133520) = 0x4030201;
  BYTE4(xmmword_141133520) = 5;
  v108 = 0;
  v0 = 5;
  do {
    v1 = 2 * v108 + 7;
    v2 = 2 * v108++ + 9;
    *((_BYTE *)&xmmword_141133520 + v0++) = v1;
    v3 = v0;
  } while(v108 < 3);
  v109 = v2;
  v4 = v2 + 1;
  v5 = v2 + 1;
  if(v0 < 0xB) {
    v6 = 11 - v0;
    v7 = ((_BYTE)v0 + (unsigned __int8)&xmmword_141133520) & 0xF;
    if((((_BYTE)v0 + (unsigned __int8)&xmmword_141133520) & 0xF) != 0)
      v7 = 16 - (((_BYTE)v0 + (unsigned __int8)&xmmword_141133520) & 0xF);
    if(v6 < v7 + 16) {
      v29 = 0;
    } else {
      v8 = 0;
      for(i = v0; v8 < v7; ++v8) {
        *((_BYTE *)&xmmword_141133520 + i) = v4;
        v4 += 3;
        ++i;
      }
      si128 = _mm_load_si128((const __m128i *)&xmmword_140022850);
      v111 = v7;
      v119 = v0;
      v113 = 11 - v0;
      v115 = v6 - (((_BYTE)v6 - (_BYTE)v7) & 0xF);
      v11 = 3 * v7 + v109 + 1;
      v117 = v0;
      v12 = _mm_cvtsi32_si128(v11);
      v121 = v5;
      v13 = v11 + 3;
      v14 = v11 + 6;
      v15 = v11 + 9;
      v16 = v11 + 12;
      v17 = v11 + 15;
      v18 = v11 + 18;
      v19 = v11 + 21;
      v20 = v11 + 24;
      v21 = v11 + 27;
      v22 = v11 + 30;
      v23 = v11 + 33;
      v24 = v11 + 36;
      v25 = v11 + 39;
      v122 = v11 + 42;
      v26 = v11 + 45;
      v27 = v111;
      v28 = _mm_cvtsi32_si128(v13);
      v29 = v115;
      v30 = _mm_unpacklo_epi8(_mm_cvtsi32_si128(v14), _mm_cvtsi32_si128(v15));
      v5 = v121;
      v6 = v113;
      v31 = _mm_cvtsi32_si128(v16);
      v3 = v117;
      v32 = _mm_unpacklo_epi32(_mm_unpacklo_epi16(_mm_unpacklo_epi8(v12, v28), v30), _mm_unpacklo_epi16(_mm_unpacklo_epi8(v31, _mm_cvtsi32_si128(v17)), _mm_unpacklo_epi8(_mm_cvtsi32_si128(v18), _mm_cvtsi32_si128(v19))));
      v33 = v119 + v111;
      v34 = _mm_unpacklo_epi64(v32, _mm_unpacklo_epi32(_mm_unpacklo_epi16(_mm_unpacklo_epi8(_mm_cvtsi32_si128(v20), _mm_cvtsi32_si128(v21)), _mm_unpacklo_epi8(_mm_cvtsi32_si128(v22), _mm_cvtsi32_si128(v23))), _mm_unpacklo_epi16(_mm_unpacklo_epi8(_mm_cvtsi32_si128(v24), _mm_cvtsi32_si128(v25)), _mm_unpacklo_epi8(_mm_cvtsi32_si128(v122), _mm_cvtsi32_si128(v26)))));
      do {
        *(__int128 *)((char *)&xmmword_141133520 + v33) = (__int128)v34;
        v34 = _mm_add_epi8(v34, si128);
        v33 += 16;
        v27 += 16;
      } while(v27 < v115);
      v0 = v27 + v119;
      v4 = 3 * v27 + v109 + 1;
    }
    v35 = v29 + v3;
    for(j = 3 * v29 + v5; v29 < v6; ++v35) {
      *((_BYTE *)&xmmword_141133520 + v35) = j;
      v0 = v35 + 1;
      v4 = j + 3;
      ++v29;
      j += 3;
    }
  }
  v37 = v4 + 1;
  if(v0 < 0x26) {
    v38 = 38 - v0;
    v39 = ((_BYTE)v0 + (unsigned __int8)&xmmword_141133520) & 0xF;
    if((((_BYTE)v0 + (unsigned __int8)&xmmword_141133520) & 0xF) != 0)
      v39 = 16 - (((_BYTE)v0 + (unsigned __int8)&xmmword_141133520) & 0xF);
    if(v38 < v39 + 16) {
      v59 = 0;
    } else {
      v40 = 0;
      for(k = v0; v40 < v39; ++v40) {
        *((_BYTE *)&xmmword_141133520 + k++) = v37;
        v37 += 4;
      }
      v42 = _mm_load_si128((const __m128i *)&xmmword_140022860);
      v110 = v39;
      v120 = v0;
      v112 = v4;
      v114 = 38 - v0;
      v116 = v38 - (((_BYTE)v38 - (_BYTE)v39) & 0xF);
      v43 = 4 * v39 + v4 + 1;
      v44 = 4 * v39 + v4 + 5;
      v45 = 4 * v39 + v4 + 9;
      v46 = 4 * v39 + v4 + 13;
      v47 = 4 * v39 + v4 + 17;
      v48 = 4 * v39 + v4 + 21;
      v49 = 4 * v39 + v4 + 25;
      v50 = v43 + 28;
      v51 = v43 + 32;
      v52 = v43 + 36;
      v53 = v43 + 40;
      v54 = v43 + 44;
      v55 = v43 + 48;
      v56 = v43 + 52;
      v118 = v43 + 56;
      v57 = v43 + 60;
      v58 = _mm_cvtsi32_si128(v43);
      v59 = v116;
      v60 = _mm_cvtsi32_si128(v44);
      v38 = v114;
      v61 = _mm_unpacklo_epi16(_mm_unpacklo_epi8(v58, v60), _mm_unpacklo_epi8(_mm_cvtsi32_si128(v45), _mm_cvtsi32_si128(v46)));
      v62 = _mm_cvtsi32_si128(v48);
      v0 = v120;
      v63 = _mm_cvtsi32_si128(v49);
      v4 = v112;
      v64 = _mm_cvtsi32_si128(v50);
      v65 = v110;
      v66 = v120 + v110;
      v67 = _mm_unpacklo_epi64(_mm_unpacklo_epi32(v61, _mm_unpacklo_epi16(_mm_unpacklo_epi8(_mm_cvtsi32_si128(v47), v62), _mm_unpacklo_epi8(v63, v64))), _mm_unpacklo_epi32(_mm_unpacklo_epi16(_mm_unpacklo_epi8(_mm_cvtsi32_si128(v51), _mm_cvtsi32_si128(v52)), _mm_unpacklo_epi8(_mm_cvtsi32_si128(v53), _mm_cvtsi32_si128(v54))), _mm_unpacklo_epi16(_mm_unpacklo_epi8(_mm_cvtsi32_si128(v55), _mm_cvtsi32_si128(v56)), _mm_unpacklo_epi8(_mm_cvtsi32_si128(v118), _mm_cvtsi32_si128(v57)))));
      do {
        *(__int128 *)((char *)&xmmword_141133520 + v66) = (__int128)v67;
        v67 = _mm_add_epi8(v67, v42);
        v66 += 16;
        v65 += 16;
      } while(v65 < v116);
    }
    v68 = 4 * v59 + v4 + 1;
    for(m = v59 + v0; v59 < v38; ++v59) {
      *((_BYTE *)&xmmword_141133520 + m++) = v68;
      v68 += 4;
    }
  }
  v70 = 0;
  for(n = 0; n < 0x80; ++n) {
    v70 += *((unsigned __int8 *)&xmmword_141133520 + v70) < n + 1;
    *((_BYTE *)&arch_hdr[12] + n) = v70;
  }
  xmmword_140028F00[0] = 0;
  xmmword_140028F10[0] = 0;
  xmmword_140028F20[0] = 0;
  xmmword_140028F30[0] = 0;
  v72 = _mm_load_si128((const __m128i *)&xmmword_1400228D0);
  v73 = 12;
  do {
    xmmword_140028F30[v73] = (__int128)v72;
    xmmword_140028F20[v73] = (__int128)v72;
    xmmword_140028F10[v73] = (__int128)v72;
    xmmword_140028F00[v73] = (__int128)v72;
    v73 -= 4;
  } while(v73 * 16);
  byte_140029000[0] = 1;
  v74 = 2;
  v75 = 2;
  MEMORY[0x140029001] = 2;
  v76 = 1;
  result = 1;
  v78 = 1;
  for(ii = 2; ii < 0x100; ++ii) {
    byte_140029000[v74] = v75 + 1;
    if(!--v78) {
      ++v75;
      v78 = ++v76;
    }
    v74 = ii + 1;
  }
  MEMORY[0x1400290FF] = 24;
  BYTE2(xmmword_140029100[0]) = 2;
  LOWORD(xmmword_140029100[0]) = 512;
  *(_QWORD *)((char *)xmmword_140029100 + 3) = 0x404040404040404LL;
  *(_QWORD *)((char *)xmmword_140029100 + 11) = 0x404040404040404LL;
  MEMORY[0x140029113] = 0x404040404040404LL;
  MEMORY[0x14002911B] = 67372036;
  MEMORY[0x14002911F] = 4;
  LODWORD(xmmword_140029120[0]) = 67372036;
  WORD2(xmmword_140029120[0]) = 1028;
  v80 = _mm_load_si128((const __m128i *)&xmmword_1400228E0);
  v81 = 12;
  do {
    xmmword_140029130[v81] = (__int128)v80;
    xmmword_140029120[v81] = (__int128)v80;
    *(__m128i *)((char *)&xmmword_140029110 + v81 * 16) = v80;
    xmmword_140029100[v81] = (__int128)v80;
    v81 -= 4;
  } while(v81 * 16);
  *(_QWORD *)((char *)xmmword_140029120 + 6) = v80.m128i_i64[0];
  *(_QWORD *)((char *)xmmword_140029120 + 14) = v80.m128i_i64[0];
  *(_QWORD *)((char *)xmmword_140029130 + 6) = v80.m128i_i64[0];
  HIWORD(xmmword_140029130[0]) = 1542;
  v82 = _mm_load_si128((const __m128i *)&xmmword_140022870);
  v83 = _mm_load_si128((const __m128i *)&xmmword_140022880);
  v84 = _mm_load_si128((const __m128i *)&xmmword_140022890);
  v85 = _mm_load_si128((const __m128i *)&xmmword_1400228A0);
  v86 = _mm_load_si128((const __m128i *)&xmmword_1400228B0);
  v87 = _mm_load_si128((const __m128i *)&xmmword_1400228C0);
  v88 = 0;
  v89 = 0;
  do {
    v90 = _mm_cmpeq_epi32(_mm_and_si128(v83, v84), v84);
    v91 = _mm_cmpeq_epi32(_mm_and_si128(v83, v82), (__m128i)0LL);
    v92 = _mm_cmpeq_epi32(_mm_and_si128(v83, v85), (__m128i)0LL);
    v93 = _mm_and_si128(v90, v91);
    v83 = _mm_add_epi32(v83, v82);
    v94 = _mm_or_si128(_mm_xor_si128((__m128i)-1LL, v90), v91);
    v95 = _mm_andnot_si128(v91, v90);
    v89 = _mm_and_si128(_mm_or_si128(_mm_and_si128(v86, v93), _mm_andnot_si128(v93, _mm_or_si128(_mm_and_si128(_mm_or_si128(_mm_and_si128(v89, _mm_or_si128(v94, v92)), _mm_and_si128(_mm_andnot_si128(v92, v95), v84)), _mm_or_si128(v94, _mm_xor_si128((__m128i)-1LL, v92))), _mm_and_si128(_mm_and_si128(v95, v92), v87)))), v90);
    xmmword_140029200[v88++] = (__int128)_mm_slli_epi32(v89, 9u);
  } while(v88 < 4);
  v96 = 0;
  v97 = 0;
  do {
    byte_140029240[v96] = v97 + 1;
    v98 = v96++ == (unsigned __int8)byte_140022900[v97];
    v97 += v98;
  } while(v96 < 0x80);
  v99 = 0;
  v100 = 0;
  do {
    byte_1400292C0[v99] = v100 + 1;
    v101 = v99++ == (unsigned __int8)byte_140022910[v100];
    v100 += v101;
  } while(v99 < 0x100);
  v102 = 0;
  v103 = 0;
  do {
    byte_1400293C0[v102] = v103;
    v104 = v102++ == (unsigned __int8)byte_140022920[v103];
    v103 += v104;
  } while(v102 < 0x80);
  v105 = 0;
  v106 = 0;
  do {
    byte_140029440[v105] = v106;
    v107 = v105++ == (unsigned __int8)byte_140022928[v106];
    v106 += v107;
  } while(v105 < 0x100);
  return result;
}
// 140022850: using guessed type __int128 xmmword_140022850;
// 140022860: using guessed type __int128 xmmword_140022860;
// 140022870: using guessed type __int128 xmmword_140022870;
// 140022880: using guessed type __int128 xmmword_140022880;
// 140022890: using guessed type __int128 xmmword_140022890;
// 1400228A0: using guessed type __int128 xmmword_1400228A0;
// 1400228B0: using guessed type __int128 xmmword_1400228B0;
// 1400228C0: using guessed type __int128 xmmword_1400228C0;
// 1400228D0: using guessed type __int128 xmmword_1400228D0;
// 1400228E0: using guessed type __int128 xmmword_1400228E0;
// 140028E50: using guessed type int arch_hdr[16];
// 140028F00: using guessed type __int128 xmmword_140028F00[];
// 140028F10: using guessed type __int128 xmmword_140028F10[];
// 140028F20: using guessed type __int128 xmmword_140028F20[];
// 140028F30: using guessed type __int128 xmmword_140028F30[];
// 140029001: using guessed type char byte_140029001;
// 1400290FF: using guessed type char byte_1400290FF;
// 140029100: using guessed type __int128 xmmword_140029100[];
// 140029113: using guessed type __int64 qword_140029113;
// 14002911B: using guessed type int dword_14002911B;
// 14002911F: using guessed type char byte_14002911F;
// 140029120: using guessed type __int128 xmmword_140029120[];
// 140029130: using guessed type __int128 xmmword_140029130[];
// 140029200: using guessed type __int128 xmmword_140029200[];
// 141133520: using guessed type __int128 xmmword_141133520;

// ---- Cleanup --------------------------------------------------------
#undef arch_hdr
#undef byte_140022900
#undef byte_140022910
#undef byte_140022920
#undef byte_140022928
#undef byte_140029000
#undef byte_140029240
#undef byte_1400292C0
#undef byte_1400293C0
#undef byte_140029440
#undef xmmword_140022850
#undef xmmword_140022860
#undef xmmword_140022870
#undef xmmword_140022880
#undef xmmword_140022890
#undef xmmword_1400228A0
#undef xmmword_1400228B0
#undef xmmword_1400228C0
#undef xmmword_1400228D0
#undef xmmword_1400228E0
#undef xmmword_140028F00
#undef xmmword_140028F10
#undef xmmword_140028F20
#undef xmmword_140028F30
#undef xmmword_140029100
#undef xmmword_140029110
#undef xmmword_140029120
#undef xmmword_140029130
#undef xmmword_140029200
#undef xmmword_141133520
#undef _BitScanForward
#undef FILE
