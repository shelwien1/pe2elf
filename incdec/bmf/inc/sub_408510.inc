// sub_408510 @ 0x00408510 — __cdecl
// Extracted from BMF.cpp:6815-8700 by extract.py per incdec.md.

typedef int t_sub_408510_Buffer_0;
static t_sub_408510_Buffer_0& __sub_408510_Buffer_0 = *(t_sub_408510_Buffer_0*)0x00443378;
typedef int t_sub_408510_Buffer_1;
static t_sub_408510_Buffer_1& __sub_408510_Buffer_1 = *(t_sub_408510_Buffer_1*)0x00443374;
typedef int t_sub_408510_Src_0;
static t_sub_408510_Src_0& __sub_408510_Src_0 = *(t_sub_408510_Src_0*)0x00443400;
typedef int t_sub_408510_Src_1;
static t_sub_408510_Src_1& __sub_408510_Src_1 = *(t_sub_408510_Src_1*)0x00443404;
typedef int t_sub_408510_buf_2;
static t_sub_408510_buf_2& __sub_408510_buf_2 = *(t_sub_408510_buf_2*)0x004433FC;
typedef unsigned char t_sub_408510_byte_438A00[252];
static t_sub_408510_byte_438A00& __sub_408510_byte_438A00 = *(t_sub_408510_byte_438A00*)0x00438A00;
typedef unsigned char t_sub_408510_byte_439408[0x10000];
static t_sub_408510_byte_439408& __sub_408510_byte_439408 = *(t_sub_408510_byte_439408*)0x00439408;
typedef unsigned char t_sub_408510_byte_439409[15];
static t_sub_408510_byte_439409& __sub_408510_byte_439409 = *(t_sub_408510_byte_439409*)0x00439409;
typedef unsigned char t_sub_408510_byte_439418[16];
static t_sub_408510_byte_439418& __sub_408510_byte_439418 = *(t_sub_408510_byte_439418*)0x00439418;
typedef int t_sub_408510_dword_438920[24];
static t_sub_408510_dword_438920& __sub_408510_dword_438920 = *(t_sub_408510_dword_438920*)0x00438920;
typedef int t_sub_408510_dword_438980[32];
static t_sub_408510_dword_438980& __sub_408510_dword_438980 = *(t_sub_408510_dword_438980*)0x00438980;
typedef int t_sub_408510_dword_438B00[0x10000];
static t_sub_408510_dword_438B00& __sub_408510_dword_438B00 = *(t_sub_408510_dword_438B00*)0x00438B00;
typedef int t_sub_408510_dword_438B04[23];
static t_sub_408510_dword_438B04& __sub_408510_dword_438B04 = *(t_sub_408510_dword_438B04*)0x00438B04;
typedef int t_sub_408510_dword_439300[24];
static t_sub_408510_dword_439300& __sub_408510_dword_439300 = *(t_sub_408510_dword_439300*)0x00439300;
typedef int t_sub_408510_dword_439480[6];
static t_sub_408510_dword_439480& __sub_408510_dword_439480 = *(t_sub_408510_dword_439480*)0x00439480;
typedef int t_sub_408510_dword_442BB8;
static t_sub_408510_dword_442BB8& __sub_408510_dword_442BB8 = *(t_sub_408510_dword_442BB8*)0x00442BB8;
typedef int t_sub_408510_dword_442BBC;
static t_sub_408510_dword_442BBC& __sub_408510_dword_442BBC = *(t_sub_408510_dword_442BBC*)0x00442BBC;
typedef int t_sub_408510_dword_442BC4[0x10000];
static t_sub_408510_dword_442BC4& __sub_408510_dword_442BC4 = *(t_sub_408510_dword_442BC4*)0x00442BC4;
typedef int t_sub_408510_dword_442BC8[13];
static t_sub_408510_dword_442BC8& __sub_408510_dword_442BC8 = *(t_sub_408510_dword_442BC8*)0x00442BC8;
typedef int t_sub_408510_dword_442BFC[2];
static t_sub_408510_dword_442BFC& __sub_408510_dword_442BFC = *(t_sub_408510_dword_442BFC*)0x00442BFC;
typedef int t_sub_408510_dword_442C04;
static t_sub_408510_dword_442C04& __sub_408510_dword_442C04 = *(t_sub_408510_dword_442C04*)0x00442C04;
typedef int t_sub_408510_dword_442C80[78];
static t_sub_408510_dword_442C80& __sub_408510_dword_442C80 = *(t_sub_408510_dword_442C80*)0x00442C80;
typedef int t_sub_408510_dword_442DC4[6];
static t_sub_408510_dword_442DC4& __sub_408510_dword_442DC4 = *(t_sub_408510_dword_442DC4*)0x00442DC4;
typedef int t_sub_408510_dword_442DE0;
static t_sub_408510_dword_442DE0& __sub_408510_dword_442DE0 = *(t_sub_408510_dword_442DE0*)0x00442DE0;
typedef int t_sub_408510_dword_442DE4[0x10000];
static t_sub_408510_dword_442DE4& __sub_408510_dword_442DE4 = *(t_sub_408510_dword_442DE4*)0x00442DE4;
typedef int t_sub_408510_dword_442DE8[21];
static t_sub_408510_dword_442DE8& __sub_408510_dword_442DE8 = *(t_sub_408510_dword_442DE8*)0x00442DE8;
typedef int t_sub_408510_dword_442E44[0x10000];
static t_sub_408510_dword_442E44& __sub_408510_dword_442E44 = *(t_sub_408510_dword_442E44*)0x00442E44;
typedef int t_sub_408510_dword_442E48[3];
static t_sub_408510_dword_442E48& __sub_408510_dword_442E48 = *(t_sub_408510_dword_442E48*)0x00442E48;
typedef int t_sub_408510_dword_442E68;
static t_sub_408510_dword_442E68& __sub_408510_dword_442E68 = *(t_sub_408510_dword_442E68*)0x00442E68;
typedef int t_sub_408510_dword_442E6C;
static t_sub_408510_dword_442E6C& __sub_408510_dword_442E6C = *(t_sub_408510_dword_442E6C*)0x00442E6C;
typedef int t_sub_408510_dword_443364;
static t_sub_408510_dword_443364& __sub_408510_dword_443364 = *(t_sub_408510_dword_443364*)0x00443364;
typedef int t_sub_408510_dword_443388;
static t_sub_408510_dword_443388& __sub_408510_dword_443388 = *(t_sub_408510_dword_443388*)0x00443388;
typedef int t_sub_408510_dword_4433F8;
static t_sub_408510_dword_4433F8& __sub_408510_dword_4433F8 = *(t_sub_408510_dword_4433F8*)0x004433F8;
typedef int t_sub_408510_dword_443408;
static t_sub_408510_dword_443408& __sub_408510_dword_443408 = *(t_sub_408510_dword_443408*)0x00443408;
typedef int t_sub_408510_m[0x10000];
static t_sub_408510_m& __sub_408510_m = *(t_sub_408510_m*)0x00442BC0;
typedef int t_sub_408510_n0xFFFFFF;
static t_sub_408510_n0xFFFFFF& __sub_408510_n0xFFFFFF = *(t_sub_408510_n0xFFFFFF*)0x004433E0;
typedef int t_sub_408510_n2;
static t_sub_408510_n2& __sub_408510_n2 = *(t_sub_408510_n2*)0x00443360;
typedef int t_sub_408510_n256;
static t_sub_408510_n256& __sub_408510_n256 = *(t_sub_408510_n256*)0x0044336C;
typedef int t_sub_408510_n256_2[0x10000];
static t_sub_408510_n256_2& __sub_408510_n256_2 = *(t_sub_408510_n256_2*)0x0044338C;
typedef int t_sub_408510_n2_3;
static t_sub_408510_n2_3& __sub_408510_n2_3 = *(t_sub_408510_n2_3*)0x004433E4;
typedef int t_sub_408510_n3;
static t_sub_408510_n3& __sub_408510_n3 = *(t_sub_408510_n3*)0x004433E8;
typedef int t_sub_408510_n4_1;
static t_sub_408510_n4_1& __sub_408510_n4_1 = *(t_sub_408510_n4_1*)0x004433DC;
typedef int t_sub_408510_n4_2;
static t_sub_408510_n4_2& __sub_408510_n4_2 = *(t_sub_408510_n4_2*)0x004433EC;
typedef int t_sub_408510_n5;
static t_sub_408510_n5& __sub_408510_n5 = *(t_sub_408510_n5*)0x004433F0;
typedef int t_sub_408510_n633;
static t_sub_408510_n633& __sub_408510_n633 = *(t_sub_408510_n633*)0x00442E40;
typedef int t_sub_408510_n8;
static t_sub_408510_n8& __sub_408510_n8 = *(t_sub_408510_n8*)0x00443368;
typedef void * t_sub_408510_off_4410C0[0x10000];
static t_sub_408510_off_4410C0& __sub_408510_off_4410C0 = *(t_sub_408510_off_4410C0*)0x004410C0;
typedef int t_sub_408510_p_n2;
static t_sub_408510_p_n2& __sub_408510_p_n2 = *(t_sub_408510_p_n2*)0x004433F4;

#ifndef __PE_DECL___sub_411700
#define __PE_DECL___sub_411700
typedef int t_sub_411700(int a1, int n2);
static t_sub_411700& __sub_411700 = *(t_sub_411700*)0x00411700;
#endif
#define sub_411700 __sub_411700
#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980
#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0
static inline int __fwd_sub_408510_sub_40A8A0(void *a0, int a1, void *a2, int a3, int a4, int a5) { return __sub_40A8A0((_DWORD *)a0, a1, (unsigned int *)a2, a3, a4, a5); }
#define sub_40A8A0 __fwd_sub_408510_sub_40A8A0
static inline int __fwd_sub_408510_sub_40AE10(void *a0, int a1) { return __sub_40AE10((_DWORD *)a0, a1); }
#define sub_40AE10 __fwd_sub_408510_sub_40AE10
static inline _DWORD * __fwd_sub_408510_sub_40AF40(void *a0, int a1, int a2, int a3, int a4) { return __sub_40AF40((_DWORD *)a0, a1, a2, a3, a4); }
#define sub_40AF40 __fwd_sub_408510_sub_40AF40
static inline unsigned int __fwd_sub_408510_sub_40B330(void *a0, void *a1) { return __sub_40B330((_DWORD *)a0, (_DWORD *)a1); }
#define sub_40B330 __fwd_sub_408510_sub_40B330
#define sub_40BEE0 __sub_40BEE0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#ifndef __PE_DECL___op_delete
#define __PE_DECL___op_delete
typedef void t_op_delete(void *);       // ??3@YAXPAX@Z
static t_op_delete& __op_delete = *(t_op_delete*)0x0042CF18;
#endif
#define FILE FILE1

PROBE_DECL(__sub_408510)
__attribute__((force_align_arg_pointer)) BMF_SSE void __sub_408510(int Src, int n0x20000, int i)
{
  alignas(16) unsigned char __hexrays_frame[1348];   // original frame, ebp-0x534..ebp+0x0
  int &n12360 = *(int *)(__hexrays_frame + 0);
  int &n633_1 = *(int *)(__hexrays_frame + 4);
  unsigned int &n11 = *(unsigned int *)(__hexrays_frame + 8);
  int * &v306 = *(int * *)(__hexrays_frame + 12);
  unsigned __int8 * &Src_15 = *(unsigned __int8 * *)(__hexrays_frame + 16);
  unsigned int &Src_16 = *(unsigned int *)(__hexrays_frame + 20);
  __int32 &v309 = *(__int32 *)(__hexrays_frame + 24);
  int &v310 = *(int *)(__hexrays_frame + 28);
  _DWORD (&v311)[8] = *(_DWORD (*)[8])(__hexrays_frame + 36);
  int &n64_1 = *(int *)(__hexrays_frame + 68);
  int &v313 = *(int *)(__hexrays_frame + 72);
  __m128i &v314 = *(__m128i *)(__hexrays_frame + 1060);
  int &v315 = *(int *)(__hexrays_frame + 1076);
  int &v316 = *(int *)(__hexrays_frame + 1080);
  int &v317 = *(int *)(__hexrays_frame + 1084);
  int &v318 = *(int *)(__hexrays_frame + 1088);
  int &v319 = *(int *)(__hexrays_frame + 1092);
  int &v320 = *(int *)(__hexrays_frame + 1096);
  int &v321 = *(int *)(__hexrays_frame + 1100);
  int &v322 = *(int *)(__hexrays_frame + 1104);
  int * &m_5 = *(int * *)(__hexrays_frame + 1108);
  int &v324 = *(int *)(__hexrays_frame + 1112);
  int &v325 = *(int *)(__hexrays_frame + 1116);
  unsigned int &v326 = *(unsigned int *)(__hexrays_frame + 1120);
  int &v327 = *(int *)(__hexrays_frame + 1124);
  int &v328 = *(int *)(__hexrays_frame + 1128);
  int &v329 = *(int *)(__hexrays_frame + 1132);
  int &v330 = *(int *)(__hexrays_frame + 1136);
  unsigned int &v331 = *(unsigned int *)(__hexrays_frame + 1140);
  int &n24_8 = *(int *)(__hexrays_frame + 1144);
  int &n2_5 = *(int *)(__hexrays_frame + 1148);
  unsigned __int8 * &Src_2 = *(unsigned __int8 * *)(__hexrays_frame + 1152);
  int &v335 = *(int *)(__hexrays_frame + 1156);
  int &v336 = *(int *)(__hexrays_frame + 1160);
  unsigned int &Src_18 = *(unsigned int *)(__hexrays_frame + 1164);
  unsigned int &Src_12 = *(unsigned int *)(__hexrays_frame + 1168);
  int &n4 = *(int *)(__hexrays_frame + 1172);
  int &n0xFFFFFF_2 = *(int *)(__hexrays_frame + 1176);
  void * &kk_2 = *(void * *)(__hexrays_frame + 1180);
  unsigned int &Src_8 = *(unsigned int *)(__hexrays_frame + 1184);
  unsigned __int8 * &Src_7 = *(unsigned __int8 * *)(__hexrays_frame + 1188);
  int &v344 = *(int *)(__hexrays_frame + 1192);
  int &n2_7 = *(int *)(__hexrays_frame + 1196);
  int &n24 = *(int *)(__hexrays_frame + 1200);
  int &n2_8 = *(int *)(__hexrays_frame + 1204);
  int &v348 = *(int *)(__hexrays_frame + 1208);
  int &n224 = *(int *)(__hexrays_frame + 1212);
  int &n4_4 = *(int *)(__hexrays_frame + 1216);
  int * &m_1 = *(int * *)(__hexrays_frame + 1220);
  int &v352 = *(int *)(__hexrays_frame + 1224);
  char * &v353 = *(char * *)(__hexrays_frame + 1228);
  int &n6_1 = *(int *)(__hexrays_frame + 1232);
  unsigned int &v355 = *(unsigned int *)(__hexrays_frame + 1236);
  int &v356 = *(int *)(__hexrays_frame + 1240);
  unsigned int &v357 = *(unsigned int *)(__hexrays_frame + 1244);
  int &n2_2 = *(int *)(__hexrays_frame + 1248);
  int &kk_1 = *(int *)(__hexrays_frame + 1252);
  void * &Block = *(void * *)(__hexrays_frame + 1256);
  unsigned int &n0x20000_1 = *(unsigned int *)(__hexrays_frame + 1260);
  int &v362 = *(int *)(__hexrays_frame + 1264);
  int &v363 = *(int *)(__hexrays_frame + 1268);
  int &v364 = *(int *)(__hexrays_frame + 1272);
  unsigned __int8 * &Src_5 = *(unsigned __int8 * *)(__hexrays_frame + 1276);
  int &v366 = *(int *)(__hexrays_frame + 1280);
  int &n2_1 = *(int *)(__hexrays_frame + 1284);
  int &v368 = *(int *)(__hexrays_frame + 1288);
  int &v369 = *(int *)(__hexrays_frame + 1292);
  int &v370 = *(int *)(__hexrays_frame + 1296);
  _DWORD * &buf_4 = *(_DWORD * *)(__hexrays_frame + 1300);
  int &v372 = *(int *)(__hexrays_frame + 1304);
  PROBE_HIT(__sub_408510);
  int __sub_408510_n0xFFFFFF; // eax
  int i_1; // ebx
  int v5; // ecx
  int v6; // esi
  int v7; // edx
  int v8; // eax
  int n64; // ebx
  char *v10; // esi
  int v11; // edi
  char *buf; // esi
  char v13; // fps
  int n0x4000_1; // edx
  int j; // eax
  int n0x4000; // ebx
  unsigned __int8 *__sub_408510_Src_1; // esi
  char *v18; // eax
  char v19; // fps
  int __sub_408510_n256; // edx
  char v21; // fps
  _DWORD *v22; // edx
  unsigned int v23; // ecx
  int n240; // eax
  __m128i v25; // xmm0
  bool v26; // zf
  _DWORD *v27; // eax
  int n15; // edi
  _DWORD *v29; // edi
  unsigned int n7; // eax
  char v31; // bl
  int n7_1; // edx
  char v33; // cl
  _BYTE *v34; // edx
  unsigned int n633_7; // edx
  unsigned int n11_1; // ebx
  char *v37; // ecx
  char *v38; // esi
  unsigned __int8 v39; // dl
  int v40; // eax
  _BYTE *v41; // ecx
  int v42; // ebx
  char v43; // dl
  int n256_1; // edi
  char *v45; // ebx
  char *v46; // esi
  char *buf_1; // eax
  char v48; // fps
  int __sub_408510_buf_2; // ebx
  unsigned int n0x8000_1; // eax
  unsigned int n0x8000_2; // edx
  unsigned int v52; // ecx
  unsigned int n0x8000; // edx
  __m128i v54; // xmm0
  __m128i v55; // xmm0
  __m128i v56; // xmm0
  __m128i v57; // xmm0
  _OWORD *v58; // edx
  char *n633_8; // ecx
  int __sub_408510_n5; // eax
  unsigned int k; // edx
  int n11_2; // ecx
  int v63; // eax
  __int32 v64; // edi
  int n633_9; // esi
  char *n633_10; // esi
  int v67; // ebx
  int n11_3; // esi
  int v69; // ebx
  unsigned __int8 *Src_3; // esi
  int v71; // ecx
  unsigned int __sub_408510_m; // edx
  int v73; // edi
  int *v74; // eax
  unsigned int __sub_408510_n633; // edx
  int *v76; // edi
  unsigned int n11_4; // ecx
  unsigned __int32 v78; // eax
  unsigned int v79; // ecx
  int v80; // eax
  int v81; // edi
  char v82; // fps
  void *v83; // edx
  int n633_2; // ebx
  unsigned int n9; // eax
  int v86; // ecx
  int v87; // esi
  int v88; // edx
  int v89; // ebx
  unsigned int n; // eax
  char *v91; // edi
  int v92; // ebx
  int n633_3; // esi
  int v94; // edx
  __int32 v95; // ecx
  __int16 v96; // bx
  unsigned __int8 *Src_4; // eax
  __int16 v98; // di
  _DWORD *buf_3; // ebx
  int v100; // edi
  int v101; // ecx
  int __sub_408510_n2; // ecx
  int n0xFFFFFF_1; // edx
  int n6_2; // edi
  unsigned int Src_11; // ebx
  int n12; // eax
  int v107; // eax
  int v108; // edx
  _DWORD *buf_12; // edx
  _DWORD *v110; // ecx
  int kk_10; // ebx
  int v112; // eax
  int v113; // esi
  int v114; // ecx
  int v115; // ebx
  int v116; // esi
  char *v117; // ebx
  int v118; // ecx
  int v119; // esi
  char *v120; // eax
  int v121; // edx
  unsigned int v122; // edi
  void *v123; // edx
  char *v124; // eax
  int v125; // edi
  int v126; // edx
  unsigned int v127; // ecx
  unsigned int v128; // edx
  int v129; // edx
  _DWORD *v130; // edx
  int v131; // esi
  int kk_11; // ecx
  int n64_2; // eax
  int v134; // edi
  int v135; // edx
  int v136; // eax
  _DWORD *buf_6; // edx
  __int16 v138; // ax
  int v139; // esi
  int v140; // ecx
  _DWORD *buf_7; // edi
  int n4_7; // edx
  int n24_3; // esi
  int n2_4; // edx
  int n2_6; // eax
  bool v146; // cc
  int v147; // edx
  int __sub_408510_n4_1; // eax
  _DWORD *buf_8; // eax
  int v150; // edi
  int __sub_408510_n4_2; // edi
  int v152; // eax
  int v153; // eax
  unsigned __int8 *v154; // eax
  int v155; // esi
  int v156; // ecx
  int v157; // ebx
  int v158; // edi
  int v159; // ebx
  int v160; // ecx
  int *v161; // eax
  int v162; // esi
  int v163; // edx
  _DWORD *v164; // esi
  int v165; // eax
  _WORD *kk_5; // ecx
  int n2_11; // ebx
  int n2_12; // ecx
  __int16 v169; // si
  int kk_6; // eax
  int n24_4; // esi
  _DWORD *__sub_408510_p_n2; // ebx
  int v173; // ebx
  int v174; // ecx
  int v175; // ebx
  int kk_7; // eax
  unsigned int v177; // eax
  int v178; // ecx
  unsigned int v179; // ebx
  int v180; // esi
  int *m_4; // eax
  int v182; // ecx
  int v183; // edx
  int *m_6; // ebx
  int v185; // ecx
  _DWORD *buf_9; // eax
  int *m_3; // edx
  int v188; // esi
  int v189; // edi
  int *m_7; // eax
  int v191; // ecx
  int v192; // eax
  int *v193; // ebx
  int *ii; // ecx
  int v195; // ebx
  int v196; // eax
  int v197; // eax
  _DWORD *buf_11; // esi
  int v199; // edx
  _WORD *kk_9; // ecx
  int v201; // edx
  int v202; // edi
  int v203; // ecx
  int v204; // edx
  int v205; // esi
  char *n633_4; // edx
  _DWORD *n24_6; // eax
  _DWORD *n24_7; // eax
  _DWORD *buf_10; // edi
  int v210; // ecx
  __int16 v211; // si
  _WORD *kk_8; // eax
  int v213; // edx
  int n24_1; // ecx
  _DWORD *n24_5; // edx
  unsigned __int8 *Src_17; // edi
  int n4_9; // esi
  unsigned int Src_13; // edx
  int n2_9; // eax
  signed int n4_8; // ebx
  int v221; // ebx
  int *m_2; // esi
  int n4_5; // ecx
  int v224; // edx
  int v225; // ebx
  int v226; // edi
  unsigned __int8 *Src_14; // eax
  int n4_3; // ecx
  int v229; // ebx
  int n2_10; // eax
  int n4_6; // edx
  int v232; // edx
  char *v233; // eax
  int v234; // edi
  char *jj_1; // edx
  int jj; // edi
  int v237; // eax
  int __sub_408510_n2_3; // ecx
  int v239; // ebx
  unsigned __int8 *Src_9; // eax
  unsigned __int8 *Src_10; // esi
  int v242; // ecx
  int kk_12; // edi
  int *v244; // ebx
  int n633_6; // ecx
  unsigned int n11_6; // ebx
  int v247; // ecx
  int v248; // ecx
  int v249; // ecx
  unsigned int n11_5; // edx
  int v251; // edx
  int n633_5; // edi
  int v253; // eax
  int v254; // eax
  _DWORD *v255; // ecx
  int v256; // edi
  _WORD *kk_13; // eax
  char v258; // fps
  unsigned int v259; // ebx
  int __sub_408510_n8; // edx
  int __sub_408510_n256_2; // ebx
  int kk; // eax
  unsigned int v263; // edi
  int n24_2; // edi
  int v265; // ecx
  int v266; // esi
  char n8_2; // cl
  int v268; // ebx
  int v269; // eax
  int v270; // edx
  int v271; // eax
  int v272; // edx
  int n8_1; // edi
  unsigned int v274; // esi
  int v275; // esi
  int v276; // esi
  unsigned int v277; // esi
  unsigned int n0x18; // eax
  int v279; // ebx
  __int32 v280; // esi
  int v281; // ebx
  int n6; // edx
  unsigned __int8 *Src_6; // edi
  int n276; // eax
  int v285; // eax
  unsigned int v286; // ecx
  int v287; // eax
  int v288; // edx
  int v289; // eax
  int v290; // edx
  int v291; // eax
  __int32 v292; // ecx
  int v293; // eax
  int v294; // ecx
  int v295; // eax
  _DWORD *v296; // ebx
  int v297; // eax
  int kk_3; // ecx
  _DWORD *buf_5; // ebx
  int v300; // eax
  int v301; // ecx
  int kk_4; // eax

  if ( ::__sub_408510_n2 )
  {
    ::__sub_408510_n4_1 = 4;
    __sub_408510_n0xFFFFFF = -1;
  }
  else
  {
    ::__sub_408510_n4_1 = 3;
    __sub_408510_n0xFFFFFF = 0xFFFFFF;
  }
  i_1 = i;
  ::__sub_408510_n2_3 = 2;
  v5 = 1;
  v6 = -1;
  __sub_408510_n3 = 3;
  ::__sub_408510_n0xFFFFFF = __sub_408510_n0xFFFFFF;
  ::__sub_408510_n4_2 = 4;
  __sub_408510_dword_442DC4[0] = 0;
  n633_1 = 0;
  ::__sub_408510_n5 = 5;
  ::__sub_408510_p_n2 = (int)&::__sub_408510_n2_3;
  __sub_408510_dword_4433F8 = 0;
  n64_1 = 0;
  while ( 1 )
  {
    *(&n633_1 + v5) = i_1 + *(&n12360 + v5);
    v7 = v5 + v6;
    v8 = v5;
    if ( v5 >= 0 )
      break;
LABEL_13:
    --v6;
    ++v5;
  }
  n64 = n64_1;
  v313 = v6;
  while ( 1 )
  {
    v10 = (char *)*(&n633_1 + v8);
    __sub_408510_dword_442BC4[2 * n64] = 0;
    ::__sub_408510_m[2 * n64] = (int)&v10[v7];
    if ( ++n64 == 64 )
      break;
    if ( v8 != v5 )
    {
      if ( v8 )
      {
        v11 = v313;
        __sub_408510_dword_442BC4[2 * n64] = 0;
        ::__sub_408510_m[2 * n64++] = (int)&v10[v8 + v11];
        if ( n64 == 64 )
          break;
      }
    }
    ++v7;
    if ( --v8 < 0 )
    {
      v6 = v313;
      n64_1 = n64;
      i_1 = i;
      goto LABEL_13;
    }
  }
  buf = (char *)__op_new(0x4000u);
  sub_4349F0(buf,0,0x4000);
  n0x4000_1 = 0;
  for ( j = 0; j < 64; ++j )
  {
    n0x4000 = ::__sub_408510_m[2 * j];
    if ( n0x4000 <= 0 || n0x4000 >= 0x4000 || buf[n0x4000] )
    {
      do
        ++n0x4000_1;
      while ( buf[n0x4000_1] );
      ::__sub_408510_m[2 * j] = n0x4000_1;
      n0x4000 = n0x4000_1;
    }
    buf[n0x4000] = 1;
  }
  __op_delete(buf);
  __sub_408510_Src_1 = (unsigned __int8 *)Src;
  n0x20000_1 = n0x20000;
  sub_40AF40(&Src_15, Src, i, n0x20000, 1);
  kk_2 = __op_new(2 * n0x20000_1 + 8);
  kk_1 = (int)kk_2;
  v18 = (char *)__op_new(0x40A00u);
  Block = v18;
  if ( v18 )
  {
    __sub_408510_n256 = 256;
    if ( __sub_408510_dword_443364 )
      __sub_408510_n256 = 4096;
    ::__sub_408510_n256_2[0] = __sub_408510_n256;
    sub_4349F0(v18 + 198912,0,65792);
    v22 = Block;
    v23 = ((unsigned int)Block + 198671) & 0xFFFFFFF0;
    v314 = 0;
    *((_QWORD *)Block + 24832) = 0;
    v22[49666] = 0;
    *((_WORD *)v22 + 99334) = 0;
    *((_BYTE *)v22 + 198670) = 0;
    *((_QWORD *)v22 + 24862) = 0;
    *((_QWORD *)v22 + 24863) = 0;
    n240 = 240;
    do
    {
      v25 = _mm_load_si128(&v314);
      *(__m128i *)(v23 + n240 - 16) = v25;
      *(__m128i *)(v23 + n240 - 32) = v25;
      *(__m128i *)(v23 + n240 - 48) = v25;
      *(__m128i *)(v23 + n240 - 64) = v25;
      *(__m128i *)(v23 + n240 - 80) = v25;
      n240 -= 80;
    }
    while ( n240 );
    v26 = __sub_408510_dword_443364 == 0;
    v27 = Block;
    *(_DWORD *)Block = 63;
    if ( v26 )
    {
      v27[1] = 0;
      n15 = 0;
    }
    else
    {
      v29 = v27;
      v27[1] = 30;
      n7 = 0;
      Src_2 = (unsigned __int8 *)Src;
      do
      {
        v31 = __sub_408510_byte_439409[2 * n7];
        n7_1 = n7;
        LOBYTE(v29[n7_1 + 2]) = __sub_408510_byte_439408[2 * n7];
        v33 = 2 * n7 + 1;
        *((_BYTE *)v29 + 2 * n7 + 520) = 2 * n7;
        BYTE1(v29[n7_1 + 2]) = n7_1 * 2;
        BYTE2(v29[n7_1 + 2]) = v31;
        *((_BYTE *)v29 + 2 * n7 + 521) = v33;
        HIBYTE(v29[n7_1 + 2]) = v33;
        ++n7;
      }
      while ( n7 < 7 );
      __sub_408510_Src_1 = Src_2;
      v34 = Block;
      *((_BYTE *)Block + 36) = 1;
      v34[534] = 14;
      v34[37] = 14;
      n15 = 15;
    }
    n633_7 = 256 - n15;
    n11 = (unsigned int)(256 - n15) >> 1;
    if ( n11 )
    {
      n633_1 = 256 - n15;
      Src_2 = __sub_408510_Src_1;
      n11_1 = 0;
      v37 = (char *)Block + n15;
      v38 = (char *)Block + 2 * n15;
      do
      {
        v38[4 * n11_1 + 8] = 0;
        v39 = n15 + 2 * n11_1;
        v37[2 * n11_1 + 520] = v39;
        *(_WORD *)&v38[4 * n11_1 + 9] = v39++;
        v37[2 * n11_1 + 521] = v39;
        v38[4 * n11_1++ + 11] = v39;
      }
      while ( n11_1 < n11 );
      n633_7 = n633_1;
      __sub_408510_Src_1 = Src_2;
      v40 = 2 * n11_1 + 1;
    }
    else
    {
      v40 = 1;
    }
    if ( n633_7 > v40 - 1 )
    {
      v41 = Block;
      v42 = v40 + n15;
      *((_BYTE *)Block + 2 * v42 + 6) = 0;
      v43 = v40 + n15 - 1;
      v41[n15 + 519 + v40] = v43;
      v41[2 * v42 + 7] = v43;
    }
    Src_2 = __sub_408510_Src_1;
    n256_1 = 1;
    v45 = (char *)Block + 776;
    v46 = (char *)Block;
    do
    {
      sub_434980(v45,v46,776);
      v45 += 776;
      ++n256_1;
    }
    while ( n256_1 < 256 );
    __sub_408510_Src_1 = Src_2;
  }
  else
  {
    Block = nullptr;
    v314 = 0;
  }
  buf_1 = (char *)__op_new(0x342FCu);
  __sub_408510_buf_2 = (int)buf_1;
  if ( buf_1 )
    sub_4349F0(buf_1,0,213756);
  else
    __sub_408510_buf_2 = 0;
  ::__sub_408510_buf_2 = (void *)__sub_408510_buf_2;
  n0x8000_1 = __sub_408510_buf_2 & 0xF;
  if ( (__sub_408510_buf_2 & 0xF) != 0 )
  {
    if ( (__sub_408510_buf_2 & 3) != 0 )
    {
      n0x8000 = 0;
      goto LABEL_52;
    }
    n0x8000_1 = (16 - n0x8000_1) >> 2;
    n0x8000_2 = 0;
    v52 = (unsigned int)(__sub_408510_Src_1 - 0x4000);
    do
      *(_DWORD *)(__sub_408510_buf_2 + 4 * n0x8000_2++ + 0x10000) = v52;
    while ( n0x8000_2 < n0x8000_1 );
  }
  else
  {
    v52 = (unsigned int)(__sub_408510_Src_1 - 0x4000);
  }
  n0x8000 = 0x8000 - (-n0x8000_1 & 0xF);
  v54 = _mm_cvtsi32_si128(v52);
  v55 = _mm_unpacklo_epi32(v54, v54);
  v56 = _mm_unpacklo_epi64(v55, v55);
  do
  {
    *(__m128i *)(__sub_408510_buf_2 + 4 * n0x8000_1 + 0x10000) = v56;
    *(__m128i *)(__sub_408510_buf_2 + 4 * n0x8000_1 + 65552) = v56;
    *(__m128i *)(__sub_408510_buf_2 + 4 * n0x8000_1 + 65568) = v56;
    *(__m128i *)(__sub_408510_buf_2 + 4 * n0x8000_1 + 65584) = v56;
    n0x8000_1 += 16;
  }
  while ( n0x8000_1 < n0x8000 );
LABEL_52:
  while ( n0x8000 < 0x8000 )
    *(_DWORD *)(__sub_408510_buf_2 + 4 * n0x8000++ + 0x10000) = __sub_408510_Src_1 - 0x4000;
  sub_4349F0((char *)(__sub_408510_buf_2 + 196608),255,0x4000);
  v57 = _mm_load_si128(&v314);
  *(_QWORD *)(__sub_408510_buf_2 + 213692) = v57.m128i_i64[0];
  v58 = (_OWORD *)((__sub_408510_buf_2 + 213707) & 0xFFFFFFF0);
  *(_DWORD *)(__sub_408510_buf_2 + 213700) = 0;
  *(_WORD *)(__sub_408510_buf_2 + 213704) = 0;
  *(_BYTE *)(__sub_408510_buf_2 + 213706) = 0;
  *(_QWORD *)(__sub_408510_buf_2 + 213740) = v57.m128i_i64[0];
  *(_QWORD *)(__sub_408510_buf_2 + 213748) = v57.m128i_i64[0];
  *v58 = v57;
  v58[1] = v57;
  v58[2] = v57;
  v314.m128i_i32[1] = __sub_408510_buf_2;
  Src_2 = __sub_408510_Src_1;
  n633_8 = nullptr;
  __sub_408510_n5 = 5;
  for ( k = 0; k < 0x20; ++k )
  {
    n633_1 = (int)n633_8;
    n11_2 = ::__sub_408510_m[4 * k];
    *(_BYTE *)(n11_2 + v314.m128i_i32[1] + 196608) = 2 * k;
    n11 = n11_2;
    v63 = __sub_408510_n5 - ((int)(2 * k) >= 1 << ((7 - __sub_408510_n5) & 31));
    v64 = v314.m128i_i32[1];
    n633_9 = n633_1;
    *(_BYTE *)(v314.m128i_i32[1] + 2 * k + 212992) = v63;
    if ( n11_2 < n633_9 )
      n11_2 = n633_9;
    n633_10 = (char *)__sub_408510_dword_442BC8[4 * k];
    n11 = n11_2;
    n633_1 = (int)n633_10;
    v67 = 2 * k + 1;
    n633_10[v64 + 196608] = v67;
    n11_3 = n11;
    __sub_408510_n5 = v63 - (v67 >= 1 << ((7 - v63) & 31));
    *(_BYTE *)(v314.m128i_i32[1] + 2 * k + 212993) = __sub_408510_n5;
    n633_8 = (char *)n633_1;
    if ( n633_1 < n11_3 )
      n633_8 = (char *)n11_3;
  }
  v69 = v314.m128i_i32[1];
  Src_3 = Src_2;
  __sub_408510_Src_0 = (int)&n633_8[(_DWORD)Src_2];
  v71 = 0;
  for ( __sub_408510_m = 0; __sub_408510_m < 0xC; ++__sub_408510_m )
  {
    v73 = ::__sub_408510_m[4 * __sub_408510_m];
    if ( v73 < v71 )
      v73 = v71;
    v71 = v73;
    if ( __sub_408510_dword_442BC8[4 * __sub_408510_m] >= v73 )
      v71 = __sub_408510_dword_442BC8[4 * __sub_408510_m];
  }
  n11 = 0;
  ::__sub_408510_Src_1 = (int)&Src_2[v71];
  v74 = __sub_408510_dword_438980;
  if ( ::__sub_408510_n2 == 2 )
    v74 = __sub_408510_dword_438920;
  __sub_408510_n633 = 633;
  if ( ::__sub_408510_n2 == 2 )
    __sub_408510_n633 = 277;
  v306 = v74;
  if ( __sub_408510_n633 >> 1 )
  {
    v76 = v74;
    v314.m128i_i32[0] = __sub_408510_n633 >> 1;
    n11_4 = n11;
    v78 = 0;
    n633_1 = __sub_408510_n633;
    do
    {
      v79 = (2 * v78 == v76[n11_4 + 1]) + n11_4;
      *(_BYTE *)(v69 + 2 * v78 + 213056) = v79;
      n11_4 = (2 * v78 + 1 == v76[v79 + 1]) + v79;
      *(_BYTE *)(v69 + 2 * v78++ + 213057) = n11_4;
    }
    while ( v78 < v314.m128i_i32[0] );
    __sub_408510_n633 = n633_1;
    Src_3 = Src_2;
    n11 = n11_4;
    v80 = 2 * v78 + 1;
  }
  else
  {
    v80 = 1;
  }
  if ( __sub_408510_n633 > v80 - 1 )
    *(_BYTE *)(v80 + v69 + 213055) = (v80 - 1 == v306[n11 + 1]) + n11;
  n12360 = 12360;
  v81 = (unsigned __int8)__sub_408510_byte_438A00[Src_3[3]]
      ^ (8
       * ((unsigned __int8)__sub_408510_byte_438A00[Src_3[2]]
        ^ (8 * ((unsigned __int8)__sub_408510_byte_438A00[Src_3[1]] ^ (8 * (unsigned __int8)__sub_408510_byte_438A00[*Src_3])))));
  __sub_408510_dword_443408 = __op_new(0x3048u);
  __sub_408510_dword_442DE0 = __op_new(0x23B4u);
  n633_1 = (int)__op_new(0x23B4u);
  ::__sub_408510_n633 = (void *)n633_1;
  sub_4349F0((char *)n633_1,0,9140);
  v83 = __sub_408510_dword_442DE0;
  v314.m128i_i32[1] = v69;
  n633_2 = n633_1;
  n9 = 0;
  Src_2 = Src_3;
  do
  {
    v86 = __sub_408510_dword_438B00[2 * n9];
    v87 = __sub_408510_dword_438B04[2 * n9];
    v88 = (int)v83 + 4 * v86;
    v89 = n633_2 + 4 * v86;
    __sub_408510_dword_442DE4[2 * n9] = v88;
    __sub_408510_dword_442E44[2 * n9] = v89;
    v83 = (void *)(v88 + 4 * v87);
    __sub_408510_dword_442DE8[2 * n9] = (int)v83;
    n633_2 = v89 + 4 * v87;
    __sub_408510_dword_442E48[2 * n9++] = n633_2;
  }
  while ( n9 < 9 );
  v368 = v81;
  for ( n = 0; n < 0xC; ++n )
  {
    if ( __sub_408510_dword_438B00[n] > 0 )
    {
      v91 = (char *)__sub_408510_off_4410C0[n];
      v92 = (int)*(&::__sub_408510_n633 + n);
      n633_1 = __sub_408510_dword_438B00[n];
      n633_3 = 0;
      n11 = (unsigned __int8)__sub_408510_byte_439418[n];
      do
      {
        v94 = 1 << ((n11 - v91[n633_3++]) & 31);
        v95 = v314.m128i_i32[1];
        *(_DWORD *)(v92 + 4 * n633_3 - 4) = v94;
        *(_DWORD *)(v95 + 4 * n + 213692) += v94;
      }
      while ( n633_3 < n633_1 );
    }
  }
  v96 = (unsigned __int8)__sub_408510_byte_438A00[Src_2[4]];
  Src_4 = Src_2;
  n0x20000_1 += (unsigned int)Src_2;
  v98 = v96 ^ (8 * v368);
  buf_3 = ::__sub_408510_buf_2;
  buf_4 = ::__sub_408510_buf_2;
  Src_5 = Src_2;
  v100 = v98 & 0x7FFF;
  v101 = *((_DWORD *)::__sub_408510_buf_2 + v100 + 0x4000);
  v368 = v100;
  *((_DWORD *)::__sub_408510_buf_2 + ((unsigned __int16)Src_2 & 0x3FFF)) = v101;
  __sub_408510_n2 = ::__sub_408510_n2;
  n0xFFFFFF_1 = ::__sub_408510_n0xFFFFFF;
  buf_3[v100 + 0x4000] = Src_4;
  n2_1 = __sub_408510_n2;
  n4 = ::__sub_408510_n4_1;
  n0xFFFFFF_2 = n0xFFFFFF_1;
  Src_12 = __sub_408510_Src_0;
  Src_18 = ::__sub_408510_Src_1;
  v336 = __sub_408510_dword_442E68;
  v335 = __sub_408510_dword_442E6C;
  n6_1 = 1;
  n6_2 = 1;
  n2_7 = 0;
  n24 = 0;
  n2_2 = 1;
  v362 = 1;
LABEL_84:
  while ( 2 )
  {
    if ( n2_1 == 2 )
    {
      v280 = v309;
      v281 = v310;
      Src_8 = Src_16;
      Src_7 = Src_15;
      v344 = __sub_408510_dword_443364;
      n6 = n6_2;
      Src_6 = Src_5;
      while ( 1 )
      {
        Src_6 += n6;
        n276 = n0x20000_1 - (_DWORD)Src_6;
        if ( (int)(n0x20000_1 - (_DWORD)Src_6) < 6 )
          break;
        if ( *(_DWORD *)Src_6 || *((_WORD *)Src_6 + 2) )
        {
          v108 = v344;
          Src_5 = Src_6;
          goto LABEL_94;
        }
        if ( n276 > 276 )
          n276 = 276;
        n6 = 6;
        if ( n276 <= 6 )
          goto LABEL_356;
        do
        {
          if ( Src_6[n6] )
            break;
          ++n6;
        }
        while ( n6 < n276 );
        if ( n6 <= 8 )
        {
LABEL_356:
          n6_1 = n6;
          v285 = sub_40A8A0(Block, (int)Src_6, (unsigned int *)&Src_15, n6, -1, 0);
          n6 = n6_1;
          if ( !v285 )
          {
            v108 = v344;
            Src_5 = Src_6;
            goto LABEL_94;
          }
        }
        if ( v344 )
        {
          if ( (unsigned int)Src_6 <= Src_8 )
          {
            v293 = *(Src_6 - 1);
            v324 = v293;
            if ( Src_6 <= Src_7 )
            {
              v325 = v281;
              v324 = v311[v293] | (2 * (v293 & 1)) | v293 & 1;
            }
            else
            {
              v294 = v293;
              v295 = Src_6[v280];
              v314.m128i_i32[0] = v280;
              v325 = v281;
              v324 = v295 & 1
                   | *(_DWORD *)((char *)v311 + ((v295 + Src_6[v280 + 1] + v294 + Src_6[v280 - 1]) & 0xFFFFFFFC))
                   | (2 * (v294 & 1));
            }
          }
          else
          {
            v286 = Src_6[v280];
            v287 = *(Src_6 - 1);
            v314.m128i_i64[0] = __PAIR64__(v286, v280);
            n6_1 = n6;
            v288 = Src_6[v281 + 1];
            v324 = v287;
            v289 = Src_6[v281] + Src_6[v280 + 2] + v288 + *(Src_6 - 2);
            v290 = *(Src_6 - 4);
            v314.m128i_i32[2] = v289;
            v291 = *(Src_6 - 3);
            v314.m128i_i32[3] = v324 + v286;
            v292 = Src_6[v281 + 3]
                 + Src_6[v281 + 2]
                 + Src_6[v281 - 2]
                 + Src_6[v314.m128i_i32[0] - 3]
                 + Src_6[v314.m128i_i32[0] + 4]
                 + Src_6[v281 - 1]
                 + Src_6[v280 + 3]
                 + Src_6[v280 - 2]
                 + 3 * (Src_6[v280 + 1] + Src_6[v280 - 1])
                 + v290
                 + v291
                 + 4 * (v324 + v286)
                 + 2 * v314.m128i_i32[2];
            n6 = n6_1;
            v324 = v314.m128i_i8[4] & 1 | v311[v292 >> 5] | (2 * (v324 & 1));
          }
        }
        else
        {
          v324 = *(Src_6 - 1);
        }
        v325 = v281;
        v296 = Block;
        v297 = *((_DWORD *)Block + 194 * v324);
        ++*((_DWORD *)Block + v297 + 49664);
        ++v296[257 * v297 + 49728];
        kk_3 = kk_1;
        buf_5 = buf_4;
        *(_WORD *)kk_1 = v297 + 12;
        v300 = *((unsigned __int8 *)buf_5 + n6 + 213056);
        ++buf_5[53434];
        ++*(_DWORD *)(v335 + 4 * v300);
        *(_WORD *)(kk_3 + 2) = ((_WORD)v300 << 7) | 0xB;
        v281 = v325;
        v26 = __sub_408510_dword_439300[v300] == 0;
        kk_1 = kk_3 + 4;
        if ( !v26 )
        {
          v301 = n6 - __sub_408510_dword_438920[v300];
          kk_4 = kk_1;
          *(_WORD *)kk_1 = v301;
          kk_1 = kk_4 + 2;
        }
      }
      v108 = v344;
      Src_5 = Src_6;
      if ( n276 )
        goto LABEL_94;
      __sub_408510_n2_3 = n2_2;
      v239 = v362;
      Src_9 = Src_6;
      Src_10 = Src_2;
      goto LABEL_271;
    }
    Src_11 = (unsigned int)Src_5;
    v357 = 4 * n2_2;
    v356 = n2_2 - 1;
    v355 = ((_WORD)n2_2 - 1) | 0xFFFF0080;
    while ( 1 )
    {
      n12 = n0x20000_1 - Src_11 - n6_2;
      if ( n12 >= 12 )
      {
        v369 = 0;
        LOWORD(v136) = v368;
        goto LABEL_118;
      }
      if ( n12 <= 4 )
        break;
      v369 = -1;
      LOWORD(v136) = v368;
      do
      {
LABEL_118:
        buf_6 = buf_4;
        v138 = (unsigned __int8)__sub_408510_byte_438A00[*(unsigned __int8 *)(++Src_11 + 4)] ^ (unsigned __int16)(8 * v136);
        v372 = *(unsigned __int8 *)(Src_11 + 4);
        v136 = v138 & 0x7FFF;
        --n6_2;
        buf_4[Src_11 & 0x3FFF] = buf_4[v136 + 0x4000];
        buf_6[v136 + 0x4000] = Src_11;
      }
      while ( n6_2 );
      v139 = *(_DWORD *)Src_11;
      v368 = v136;
      LOWORD(v140) = Src_11;
      if ( v362 )
      {
        n6_1 = 0;
        buf_7 = buf_6;
        while ( 1 )
        {
          v140 = buf_7[v140 & 0x3FFF];
          n4_7 = Src_11 - v140;
          if ( Src_11 - v140 >= 0x4000 )
            break;
          if ( *((unsigned __int8 *)buf_7 + n4_7 + 196608) < 0x40u && v139 == *(_DWORD *)v140 )
            goto LABEL_124;
        }
        v108 = __sub_408510_dword_443364;
        Src_5 = (unsigned __int8 *)Src_11;
        goto LABEL_94;
      }
      buf_8 = buf_6;
      n6_1 = 0;
      while ( 1 )
      {
        v140 = buf_8[v140 & 0x3FFF];
        n4_7 = Src_11 - v140;
        if ( Src_11 - v140 >= 0x4000 )
          break;
        if ( v139 == *(_DWORD *)v140 )
        {
          if ( *((unsigned __int8 *)buf_8 + n4_7 + 196608) < 0x40u )
          {
LABEL_124:
            v327 = v139;
            if ( Src_11 < Src_12 )
            {
              n24_3 = *((unsigned __int8 *)buf_4 + n4_7 + 196608);
              n2_4 = *((unsigned __int8 *)buf_4 + n24_3 + 212992);
              n2_6 = n2_4 + 1;
              v146 = n2_4 < n2_2;
              if ( n2_4 >= n2_2 )
                n2_4 = n2_2;
              n2_5 = n2_4;
              if ( !v146 )
                n2_6 = n2_2;
              v147 = n0x20000_1 - Src_11;
              if ( __sub_408510_dword_439480[n2_6] < (int)(n0x20000_1 - Src_11) )
                v147 = __sub_408510_dword_439480[n2_6];
              __sub_408510_n4_1 = 4;
              if ( *(unsigned __int8 *)(v140 + 4) == v372 )
              {
                n24_8 = n24_3;
                while ( ++__sub_408510_n4_1 < v147 )
                {
                  if ( *(unsigned __int8 *)(__sub_408510_n4_1 + Src_11) != *(unsigned __int8 *)(__sub_408510_n4_1 + v140) )
                    goto LABEL_137;
                  if ( ++__sub_408510_n4_1 >= v147 )
                    break;
                  if ( *(unsigned __int8 *)(__sub_408510_n4_1 + Src_11) != *(unsigned __int8 *)(__sub_408510_n4_1 + v140) )
                  {
LABEL_137:
                    n24_3 = n24_8;
                    goto LABEL_138;
                  }
                }
                n24_3 = n24_8;
              }
LABEL_138:
              if ( __sub_408510_n4_1 <= n6_1 && (__sub_408510_n4_1 != n6_1 || n24_3 >= n24) )
              {
                v139 = v327;
                buf_8 = buf_4;
                continue;
              }
              v26 = __sub_408510_n4_1 == __sub_408510_dword_439480[v357 / 4];
              n6_1 = __sub_408510_n4_1;
              n24 = n24_3;
              n2_7 = n2_5;
              if ( !v26 || n24_3 )
              {
                v139 = v327;
                buf_8 = buf_4;
                v369 = -1;
                continue;
              }
              __sub_408510_n4_2 = __sub_408510_n4_1;
              v152 = v356;
              Src_5 = (unsigned __int8 *)Src_11;
              goto LABEL_155;
            }
            __sub_408510_n4_2 = n6_1;
            Src_5 = (unsigned __int8 *)Src_11;
            n4_9 = __sub_408510_dword_439480[v357 / 4];
            Src_13 = Src_11;
            n2_8 = n2_2;
            n2_9 = n2_2;
            m_1 = ::__sub_408510_m;
            n4_8 = n0x20000_1 - Src_11;
            if ( n4_9 < n4_8 )
              n4_8 = n4_9;
            n4_4 = n4_8;
            v370 = *(_DWORD *)(Src_13 + 1);
            v352 = 1;
            v221 = 1 << ((7 - n2_2) & 31);
            m_2 = m_1;
            n4_5 = n4_4;
            while ( 2 )
            {
              v224 = ::__sub_408510_m[2 * v221];
              ::__sub_408510_m[2 * v221] = 0;
              m_2 -= 2;
              v329 = v224;
              v328 = v221;
              v225 = v327;
              n4_4 = n4_5;
              n2_8 = n2_9;
              n6_1 = __sub_408510_n4_2;
              v226 = v352;
              while ( 1 )
              {
                do
                {
                  do
                  {
LABEL_227:
                    m_2 += 2;
                    Src_14 = &Src_5[-*m_2];
                    if ( v225 == *(_DWORD *)Src_14 )
                      break;
                    m_2 += 2;
                    Src_14 = &Src_5[-*m_2];
                    if ( v225 == *(_DWORD *)Src_14 )
                      break;
                    m_2 += 2;
                    Src_14 = &Src_5[-*m_2];
                  }
                  while ( v225 != *(_DWORD *)Src_14 );
                }
                while ( v370 != *(_DWORD *)&Src_14[v226] );
                if ( Src_14 == Src_5 )
                  break;
                if ( Src_14[4] == v372 )
                {
                  m_1 = m_2;
                  v352 = v226;
                  n4_3 = 4;
                  do
                  {
                    if ( ++n4_3 >= n4_4 )
                      break;
                    if ( Src_5[n4_3] != Src_14[n4_3] )
                      break;
                    if ( ++n4_3 >= n4_4 )
                      break;
                    if ( Src_5[n4_3] != Src_14[n4_3] )
                      break;
                    if ( ++n4_3 >= n4_4 )
                      break;
                    if ( Src_5[n4_3] != Src_14[n4_3] )
                      break;
                    if ( ++n4_3 >= n4_4 )
                      break;
                  }
                  while ( Src_5[n4_3] == Src_14[n4_3] );
                  m_2 = m_1;
                  v226 = v352;
                  v225 = v327;
                  if ( n4_3 <= n6_1 )
                    goto LABEL_227;
                }
                else
                {
                  if ( n6_1 >= 4 )
                    goto LABEL_227;
                  n4_3 = 4;
                }
                n6_1 = n4_3;
                n2_7 = n2_8;
                n24 = ((char *)m_2 - (char *)::__sub_408510_m) >> 3;
                if ( n4_3 >= n4_4 )
                {
                  __sub_408510_n4_2 = n6_1;
                  v152 = v356;
                  ::__sub_408510_m[2 * v328] = v329;
                  goto LABEL_155;
                }
                v226 = n4_3 - 3;
                v370 = *(_DWORD *)&Src_5[n4_3 - 3];
              }
              v229 = v328;
              n4_5 = n4_4;
              n2_10 = n2_8;
              v352 = v226;
              __sub_408510_n4_2 = n6_1;
              *m_2 = v329;
              if ( n2_10 != 1 )
              {
                n4_6 = __sub_408510_dword_439480[n2_10];
                if ( n4_5 <= n4_6 || (n4_5 = __sub_408510_dword_439480[n2_10], __sub_408510_n4_2 < n4_6) )
                {
                  n2_9 = n2_10 - 1;
                  v221 = 2 * v229;
                  continue;
                }
              }
              break;
            }
            v152 = v356;
LABEL_155:
            if ( v362 )
            {
              v153 = ::__sub_408510_m[2 * n24];
              v326 = 8 * n24;
              v154 = &Src_5[-v153];
              if ( (__sub_408510_n4_2 != 6
                 || (unsigned int)(Src_5 + 11) > n0x20000_1
                 || *(_DWORD *)(Src_5 + 7) != *(_DWORD *)(v154 + 7)
                 || Src_5[6] != v154[6])
                && !sub_40A8A0(Block, (int)Src_5, (unsigned int *)&Src_15, __sub_408510_n4_2, n24, 0) )
              {
                v108 = __sub_408510_dword_443364;
                goto LABEL_94;
              }
              if ( __sub_408510_dword_443364 )
              {
                if ( (unsigned int)Src_5 <= Src_16 )
                {
                  v161 = (int *)*(Src_5 - 1);
                  v306 = v161;
                  if ( Src_5 <= Src_15 )
                  {
                    v160 = (unsigned __int8)v161 & 1 | v311[(_DWORD)v161] | (2 * ((unsigned __int8)v161 & 1));
                  }
                  else
                  {
                    v162 = Src_5[v309];
                    v163 = Src_5[v309 + 1];
                    n11 = Src_5[v309 - 1];
                    v160 = v162 & 1
                         | *(_DWORD *)((char *)v311 + (((unsigned int)v306 + n11 + v163 + v162) & 0xFFFFFFFC))
                         | (2 * ((unsigned __int8)v306 & 1));
                    if ( n2_1 == 1 )
                    {
                      v195 = v160 < v311[(_DWORD)v306] || v160 < v311[v163] || v160 < v311[n11];
                      v160 |= (v195 << 7) | (8 * (n11 & 1)) | (4 * (v163 & 1));
                    }
                  }
                }
                else
                {
                  v155 = Src_5[v309];
                  v156 = *(Src_5 - 1);
                  v157 = Src_5[v309 + 1];
                  n6_1 = __sub_408510_n4_2;
                  v318 = v155;
                  v317 = v156;
                  v315 = Src_5[v309 - 1];
                  v158 = Src_5[v310 + 1];
                  v316 = v157;
                  v319 = Src_5[v310] + Src_5[v309 + 2] + v158 + *(Src_5 - 2);
                  v159 = *(Src_5 - 3);
                  v320 = v156 + v155;
                  __sub_408510_n4_2 = n6_1;
                  v160 = v155 & 1
                       | v311[(Src_5[v310 + 3]
                             + Src_5[v310 + 2]
                             + Src_5[v310 - 2]
                             + Src_5[v309 - 3]
                             + Src_5[v309 + 4]
                             + Src_5[v310 - 1]
                             + Src_5[v309 + 3]
                             + Src_5[v309 - 2]
                             + 3 * (v316 + v315)
                             + *(Src_5 - 4)
                             + v159
                             + 4 * (v156 + v155)
                             + 2 * v319) >> 5]
                       | (2 * (v156 & 1));
                  if ( n2_1 == 1 )
                  {
                    v196 = v160 < v311[v317] || v160 < v311[v316] || v160 < v311[v315];
                    v160 |= (v196 << 7) | (8 * (v315 & 1)) | (4 * (v316 & 1));
                  }
                }
              }
              else
              {
                v160 = *(Src_5 - 1);
              }
              v164 = Block;
              v165 = *((_DWORD *)Block + 194 * v160);
              ++*((_DWORD *)Block + v165 + 49664);
              kk_5 = (_WORD *)kk_1;
              ++v164[257 * v165 + 49728];
              *kk_5 = v165 + 12;
              v362 = 0;
              kk_1 = (int)(kk_5 + 1);
            }
            else
            {
              n2_11 = n2_7;
              ++buf_4[v152 + 53423];
              n2_12 = n2_11 + 1;
              ++*((_DWORD *)*(&::__sub_408510_n633 + v152) + n2_11 + 1);
              v169 = v152 | (((_WORD)n2_11 + 1) << 7);
              kk_6 = kk_1;
              *(_WORD *)kk_1 = v169;
              kk_1 = kk_6 + 2;
              if ( n2_11 == n2_2 )
              {
                v326 = 8 * n24;
              }
              else
              {
                n24_4 = n24;
                __sub_408510_p_n2 = (_DWORD *)(::__sub_408510_p_n2 - 4);
                *__sub_408510_p_n2 = n2_2;
                ::__sub_408510_p_n2 = (int)__sub_408510_p_n2;
                n2_2 = n2_7;
                n2_7 = n2_12;
                n2_1 = ::__sub_408510_n2;
                v326 = 8 * n24_4;
                v357 = 4 * n2_2;
              }
            }
            v173 = *((unsigned __int8 *)buf_4 + __sub_408510_n4_2 + 213056);
            n6_2 = __sub_408510_dword_438980[v173];
            v174 = n2_7 + 4;
            v175 = ((unsigned __int8)(n24 << (n2_7 & 31)) | (unsigned __int8)v173) & 0x7F;
            ++buf_4[v174 + 53423];
            ++*((_DWORD *)*(&::__sub_408510_n633 + v174) + v175);
            kk_7 = kk_1;
            *(_WORD *)kk_1 = v174 | ((_WORD)v175 << 7);
            kk_1 = kk_7 + 2;
            if ( n6_2 >= __sub_408510_dword_439480[v357 / 4] && n2_2 < 5 )
            {
              n2_2 = *(_DWORD *)::__sub_408510_p_n2;
              ::__sub_408510_p_n2 += 4;
            }
            v177 = v326;
            v178 = n6_2 + __sub_408510_dword_442BC4[v326 / 4];
            v26 = n24 == 0;
            __sub_408510_dword_442BC4[v326 / 4] = v178;
            if ( !v26 && v178 > *(int *)((char *)&__sub_408510_dword_442BBC + v177) )
            {
              v179 = v177;
              v180 = *(int *)((char *)::__sub_408510_m + v177);
              v322 = *(int *)((char *)__sub_408510_dword_442BC4 + v177);
              m_4 = (int *)((char *)&__sub_408510_dword_442BB8 + v177);
              v182 = *m_4;
              v183 = m_4[1];
              m_5 = m_4;
              *(int *)((char *)::__sub_408510_m + v179) = v182;
              *(int *)((char *)__sub_408510_dword_442BC4 + v179) = v183;
              ++*((_BYTE *)buf_4 + v182 + 196608);
              if ( m_4 != ::__sub_408510_m )
              {
                m_6 = m_4;
                v185 = v322;
                buf_9 = buf_4;
                v321 = v180;
                n6_1 = n6_2;
                do
                {
                  m_3 = m_6 - 2;
                  v188 = *(m_6 - 1);
                  if ( v188 >= v185 )
                    break;
                  v189 = *m_3;
                  *m_6 = *m_3;
                  m_6[1] = v188;
                  m_6 -= 2;
                  ++*((_BYTE *)buf_9 + v189 + 196608);
                }
                while ( m_3 != ::__sub_408510_m );
                v180 = v321;
                n6_2 = n6_1;
                m_5 = m_6;
              }
              m_7 = m_5;
              v191 = v322;
              *m_5 = v180;
              m_7[1] = v191;
              *((_BYTE *)buf_4 + v180 + 196608) = (unsigned int)((char *)m_7 - (char *)::__sub_408510_m) >> 3;
              if ( __sub_408510_dword_442BFC[0] - __sub_408510_dword_442C04 > 20 )
              {
                v192 = __sub_408510_dword_442BC4[0];
                v193 = __sub_408510_dword_442BC8;
                for ( ii = ::__sub_408510_m; v192; v193 += 2 )
                {
                  ii[1] = v192 >> 1;
                  v192 = v193[1];
                  ii += 2;
                }
              }
            }
            goto LABEL_84;
          }
          if ( !v369
            && *(_DWORD *)(v140 + 8) == *(_DWORD *)(Src_11 + 8)
            && *(_DWORD *)(v140 + 4) == *(_DWORD *)(Src_11 + 4) )
          {
            v150 = v369;
            if ( n4_7 >= 4 )
              v150 = Src_11 - v140;
            v369 = v150;
          }
        }
      }
      v197 = v369;
      __sub_408510_n4_2 = n6_1;
      if ( n6_1 )
      {
        v152 = v356;
        Src_5 = (unsigned __int8 *)Src_11;
        goto LABEL_155;
      }
      if ( v369 <= 0 )
      {
        v205 = n0xFFFFFF_2 & v139;
        n633_4 = (char *)__sub_408510_dword_442C80[0];
        __sub_408510_dword_442C80[0] = 0;
        n24 = (int)&__sub_408510_dword_442BB8;
        if ( Src_11 <= Src_18 )
        {
          n633_1 = (int)n633_4;
          n24_5 = (_DWORD *)n24;
          do
          {
            do
            {
              n24_5 += 2;
              Src_17 = (unsigned __int8 *)(Src_11 - *n24_5);
            }
            while ( Src_17 < Src_2 );
          }
          while ( v205 != (n0xFFFFFF_2 & *(_DWORD *)Src_17) );
          n24 = (int)n24_5;
          n633_4 = (char *)n633_1;
        }
        else
        {
          n24_6 = (_DWORD *)n24;
          while ( 1 )
          {
            n24_7 = n24_6 + 2;
            if ( v205 == (n0xFFFFFF_2 & *(_DWORD *)(Src_11 - *n24_7)) )
              break;
            n24_7 += 2;
            if ( v205 == (n0xFFFFFF_2 & *(_DWORD *)(Src_11 - *n24_7)) )
              break;
            n24_6 = n24_7 + 2;
            if ( v205 == (n0xFFFFFF_2 & *(_DWORD *)(Src_11 - *n24_6)) )
            {
              n24 = (int)n24_6;
              goto LABEL_212;
            }
          }
          n24 = (int)n24_7;
        }
LABEL_212:
        __sub_408510_dword_442C80[0] = (int)n633_4;
        n24 = (n24 - (int)::__sub_408510_m) >> 3;
        if ( n24 == 24 || !sub_40A8A0(Block, Src_11, (unsigned int *)&Src_15, n4, n24, n2_2) )
        {
          v107 = v356;
          Src_5 = (unsigned __int8 *)Src_11;
          goto LABEL_91;
        }
        buf_10 = buf_4;
        v210 = (int)*(&::__sub_408510_n633 + v356);
        v211 = v355;
        kk_8 = (_WORD *)kk_1;
        ++buf_4[v356 + 53423];
        v213 = v336;
        *kk_8 = v211;
        ++*(_DWORD *)(v210 + 4);
        n24_1 = n24;
        ++buf_10[53433];
        n6_2 = n4;
        ++*(_DWORD *)(v213 + 4 * n24_1);
        kk_8[1] = ((_WORD)n24_1 << 7) | 0xA;
        kk_1 = (int)(kk_8 + 2);
      }
      else
      {
        buf_11 = buf_4;
        v199 = (int)*(&::__sub_408510_n633 + v356);
        kk_9 = (_WORD *)kk_1;
        ++buf_4[v356 + 53423];
        *kk_9 = v355;
        ++*(_DWORD *)(v199 + 4);
        v201 = v336;
        v202 = (v197 >> 11) + 24;
        ++buf_11[53433];
        ++*(_DWORD *)(v201 + 4 * v202);
        kk_9[1] = ((_WORD)v202 << 7) | 0xA;
        kk_9[2] = v197 & 0x7FF;
        kk_1 = (int)(kk_9 + 3);
        v203 = __sub_408510_dword_4433F8;
        v204 = 63 - (__sub_408510_dword_4433F8 & 3);
        *((_BYTE *)buf_11 + v197 + 196608) = v204;
        __sub_408510_dword_4433F8 = v203 + 1;
        n6_2 = 12;
        *((_BYTE *)buf_11 + ::__sub_408510_m[2 * v204] + 196608) = -1;
        ::__sub_408510_m[2 * v204] = v197;
      }
    }
    v107 = v356;
    Src_5 = (unsigned __int8 *)(n6_2 + Src_11);
    if ( n6_2 + Src_11 != n0x20000_1 )
    {
      if ( v362 )
      {
        v108 = __sub_408510_dword_443364;
        goto LABEL_94;
      }
LABEL_91:
      buf_12 = buf_4;
      v110 = *(&::__sub_408510_n633 + v107);
      kk_10 = kk_1;
      *(_WORD *)kk_1 = v107;
      ++buf_12[v107 + 53423];
      kk_1 = kk_10 + 2;
      ++*v110;
      if ( n2_2 == 1 )
      {
        v108 = __sub_408510_dword_443364;
        v362 = 1;
      }
      else
      {
        ::__sub_408510_p_n2 -= 4;
        *(_DWORD *)::__sub_408510_p_n2 = n2_2;
        v108 = __sub_408510_dword_443364;
        n2_1 = ::__sub_408510_n2;
        v362 = 1;
        n2_2 = 1;
      }
LABEL_94:
      if ( v108 )
      {
        if ( (unsigned int)Src_5 <= Src_16 )
        {
          v113 = *(Src_5 - 1);
          if ( Src_5 <= Src_15 )
          {
            v112 = v113 & 1 | v311[v113] | (2 * (v113 & 1));
          }
          else
          {
            v114 = Src_5[v309];
            v115 = Src_5[v309 - 1];
            v348 = Src_5[v309 + 1];
            v112 = v114 & 1 | *(_DWORD *)((char *)v311 + ((v348 + v114 + v113 + v115) & 0xFFFFFFFC)) | (2 * (v113 & 1));
            if ( n2_1 == 1 )
            {
              v232 = v112 < v311[v113] || v112 < v311[v348] || v112 < v311[v115];
              v112 |= (v232 << 7) | (8 * (v115 & 1)) | (4 * (v348 & 1));
            }
          }
        }
        else
        {
          v112 = sub_40AE10(&Src_15, (int)Src_5);
        }
      }
      else
      {
        v112 = *(Src_5 - 1);
      }
      v116 = *Src_5;
      v364 = 776 * v112;
      v117 = (char *)Block + 776 * v112;
      v118 = *(_DWORD *)v117;
      v119 = (unsigned __int8)v117[v116 + 520];
      v120 = &v117[2 * v119];
      v121 = (unsigned __int8)v120[8] + 1;
      v120[8] = v121;
      v366 = v121;
      if ( v119 )
      {
        v353 = &v117[2 * v119];
        if ( (unsigned __int8)v120[6] <= (int)(unsigned __int8)v366 )
        {
          v122 = *((unsigned __int16 *)v353 + 3);
          v331 = *((unsigned __int16 *)v353 + 4);
          v123 = Block;
          *((_WORD *)v353 + 4) = v122;
          ++v117[(v122 >> 8) + 520];
          v124 = &v117[2 * v119 + 6];
          v125 = (int)v123 + v364 + 8;
          if ( v124 != (char *)v125 )
          {
            v126 = (unsigned __int8)v331;
            v330 = v118;
            do
            {
              if ( (unsigned __int8)*(v124 - 2) > v126 )
                break;
              v127 = *((unsigned __int16 *)v124 - 1);
              *(_WORD *)v124 = v127;
              v124 -= 2;
              ++v117[(v127 >> 8) + 520];
            }
            while ( v124 != (char *)v125 );
            v118 = v330;
          }
          v128 = v331;
          *(_WORD *)v124 = v331;
          v117[(v128 >> 8) + 520] = (unsigned int)&v124[-v125] >> 1;
        }
      }
      v129 = *((_DWORD *)v117 + 1);
      v363 = v129 + 1;
      *((_DWORD *)v117 + 1) = v129 + 1;
      if ( (((_BYTE)v129 + 1) & 0x1F) == 0 )
      {
        n224 = (unsigned __int8)v117[8];
        if ( n224 >= 8 )
        {
          *(_DWORD *)v117 = 0;
          n64_2 = 0;
          v134 = (8 * v129 + 8 - v363) >> 3;
          while ( 1 )
          {
            v135 = (unsigned __int8)v117[2 * n64_2++ + 8];
            v134 -= v135;
            if ( v134 < 0 )
              break;
            *(_DWORD *)v117 = n64_2;
          }
          *(_DWORD *)v117 = n64_2 < 64 ? n64_2 : 63;
          if ( n224 >= 224 || v363 >= ::__sub_408510_n256_2[0] )
          {
            v233 = (char *)Block;
            v234 = v364;
            *((_DWORD *)v117 + 1) = 0;
            jj_1 = &v233[v234 + 8];
            for ( jj = (int)&v233[v234 + 520]; jj_1 != (char *)jj; jj_1 += 2 )
            {
              if ( !*jj_1 )
                break;
              v237 = (unsigned __int8)*jj_1 >> 1;
              *jj_1 = v237;
              *((_DWORD *)v117 + 1) += v237;
            }
          }
        }
      }
      v130 = Block;
      ++*((_DWORD *)Block + v118 + 49664);
      v131 = v119 + 1;
      n6_2 = 1;
      ++v130[257 * v118 + 49728 + v131];
      LOWORD(v131) = (v118 + 12) | ((_WORD)v131 << 7);
      kk_11 = kk_1;
      *(_WORD *)kk_1 = v131;
      kk_1 = kk_11 + 2;
      continue;
    }
    break;
  }
  __sub_408510_n2_3 = n2_2;
  v239 = v362;
  Src_9 = Src_5;
  Src_10 = Src_2;
  v108 = __sub_408510_dword_443364;
LABEL_271:
  if ( !v239 )
  {
    v242 = __sub_408510_n2_3 - 1;
    ++buf_4[v242 + 53423];
    ++*(_DWORD *)*(&::__sub_408510_n633 + v242);
    kk_12 = kk_1;
    *(_WORD *)kk_1 = v242;
    kk_1 = kk_12 + 2;
  }
  if ( v108 )
  {
    if ( (unsigned int)Src_9 <= Src_16 )
    {
      n11_5 = *(Src_9 - 1);
      n11 = n11_5;
      if ( Src_9 <= Src_15 )
      {
        v249 = n11_5 & 1 | v311[n11_5] | (2 * (n11_5 & 1));
      }
      else
      {
        v251 = Src_9[v309];
        n633_5 = Src_9[v309 - 1];
        v253 = Src_9[v309 + 1];
        n633_1 = n633_5;
        v249 = v251 & 1 | *(_DWORD *)((char *)v311 + ((v253 + v251 + n11 + n633_5) & 0xFFFFFFFC)) | (2 * (n11 & 1));
        if ( n2_1 == 1 )
        {
          v272 = v249 < v311[n11] || v249 < v311[v253] || v249 < v311[n633_1];
          v249 |= (v272 << 7) | (8 * (n633_1 & 1)) | (4 * (v253 & 1));
        }
      }
    }
    else
    {
      v244 = (int *)*(Src_9 - 1);
      n633_6 = Src_9[v309 - 1];
      Src_2 = Src_10;
      v314.m128i_i32[0] = Src_9[v309];
      v306 = v244;
      n11_6 = Src_9[v309 + 1];
      n633_1 = n633_6;
      v247 = *(Src_9 - 2);
      n11 = n11_6;
      v314.m128i_i32[1] = Src_9[v310] + Src_9[v309 + 2] + Src_9[v310 + 1] + v247;
      v248 = *(Src_9 - 3);
      v314.m128i_i32[2] = (__int32)v306 + v314.m128i_i32[0];
      v249 = v314.m128i_i8[0] & 1
           | v311[(int)(Src_9[v310 + 3]
                      + Src_9[v310 + 2]
                      + Src_9[v310 - 2]
                      + Src_9[v309 - 3]
                      + Src_9[v309 + 4]
                      + Src_9[v310 - 1]
                      + Src_9[v309 + 3]
                      + Src_9[v309 - 2]
                      + 3 * (n11_6 + n633_1)
                      + *(Src_9 - 4)
                      + v248
                      + 4 * ((_DWORD)v306 + v314.m128i_i32[0])
                      + 2 * v314.m128i_i32[1]) >> 5]
           | (2 * ((unsigned __int8)v306 & 1));
      if ( n2_1 == 1 )
      {
        v271 = v249 < v311[(_DWORD)v306] || v249 < v311[n11] || v249 < v311[n633_1];
        v249 |= (v271 << 7) | (8 * (n633_1 & 1)) | (4 * (n11 & 1));
      }
    }
  }
  else
  {
    v249 = *(Src_9 - 1);
  }
  v254 = 776 * v249;
  v255 = Block;
  v256 = *(_DWORD *)((char *)Block + v254);
  kk_13 = (_WORD *)kk_1;
  ++*((_DWORD *)Block + v256 + 49664);
  ++v255[257 * v256 + 49728];
  *kk_13 = v256 + 12;
  kk_1 = (int)(kk_13 + 1);
  sub_40B330(v255, buf_4);
  if ( __sub_408510_dword_443388 )
  {
    v268 = 0;
    while ( 1 )
    {
      v269 = sub_411700((int)*(&::__sub_408510_n633 + v268), __sub_408510_dword_438B00[v268]);
      v270 = v269 + ::__sub_408510_n256_2[0];
      if ( ++v268 >= 12 )
        break;
      ::__sub_408510_n256_2[0] += v269;
    }
    n0x18 = 0;
    if ( ::__sub_408510_n2 == 2 )
    {
      do
      {
        v279 = *(_DWORD *)(__sub_408510_dword_442E6C + 4 * n0x18) * __sub_408510_dword_439300[n0x18];
        ++n0x18;
        v270 += v279;
      }
      while ( n0x18 < 0x18 );
      ::__sub_408510_n256_2[0] = v270;
    }
    else
    {
      do
        v270 += 11 * *(_DWORD *)(__sub_408510_dword_442E68 + 4 * n0x18++ + 96);
      while ( n0x18 < 8 );
      ::__sub_408510_n256_2[0] = v270;
    }
  }
  else
  {
    sub_40BEE0(v258);
    v259 = *Src_10;
    if ( ::__sub_408510_n8 < 8 )
    {
      *(_DWORD *)__sub_408510_Buffer_1 = ::__sub_408510_n256 | (2 * (v259 << ((31 - ::__sub_408510_n8) & 31)));
      __sub_408510_Buffer_1 = __sub_408510_Buffer_0;
      __sub_408510_n256_2 = v259 >> (::__sub_408510_n8 & 31);
      __sub_408510_Buffer_0 += 4;
      ::__sub_408510_n256 = __sub_408510_n256_2;
      __sub_408510_n8 = ::__sub_408510_n8 + 24;
      ::__sub_408510_n8 += 24;
    }
    else
    {
      __sub_408510_n8 = ::__sub_408510_n8 - 8;
      __sub_408510_n256_2 = ::__sub_408510_n256 | (v259 << (-(char)::__sub_408510_n8 & 31));
      ::__sub_408510_n256 = __sub_408510_n256_2;
      ::__sub_408510_n8 -= 8;
    }
    kk_1 = (kk_1 - (int)kk_2) >> 1;
    if ( kk_1 > 0 )
    {
      for ( kk = 0; kk < kk_1; ++kk )
      {
        v263 = *((unsigned __int16 *)kk_2 + kk);
        n11 = buf_4[*((_WORD *)kk_2 + kk) & 0x7F];
        n24_2 = v263 >> 7;
        v265 = *((_DWORD *)*(&__sub_408510_dword_442DE0 + n11) + n24_2);
        v266 = (unsigned __int16)v265;
        n633_1 = BYTE2(v265);
        if ( __sub_408510_n8 < BYTE2(v265) )
        {
          *(_DWORD *)__sub_408510_Buffer_1 = (2 * ((unsigned __int16)v265 << ((31 - __sub_408510_n8) & 31))) | __sub_408510_n256_2;
          __sub_408510_Buffer_1 = __sub_408510_Buffer_0;
          __sub_408510_Buffer_0 += 4;
          __sub_408510_n256_2 = (unsigned __int16)v265 >> (::__sub_408510_n8 & 31);
          __sub_408510_n8 = ::__sub_408510_n8 - n633_1 + 32;
        }
        else
        {
          n8_2 = __sub_408510_n8;
          __sub_408510_n8 -= n633_1;
          __sub_408510_n256_2 |= v266 << (-n8_2 & 31);
        }
        if ( n11 == 10 )
        {
          if ( n24_2 >= 24 )
          {
            ++kk;
            if ( __sub_408510_n8 < 11 )
            {
              v277 = *((unsigned __int16 *)kk_2 + kk);
              ::__sub_408510_n8 = __sub_408510_n8;
              *(_DWORD *)__sub_408510_Buffer_1 = (2 * (v277 << ((31 - __sub_408510_n8) & 31))) | __sub_408510_n256_2;
              __sub_408510_Buffer_1 = __sub_408510_Buffer_0;
              __sub_408510_Buffer_0 += 4;
              __sub_408510_n256_2 = v277 >> (::__sub_408510_n8 & 31);
              __sub_408510_n8 = ::__sub_408510_n8 + 21;
              ::__sub_408510_n8 += 21;
            }
            else
            {
              v276 = *((unsigned __int16 *)kk_2 + kk) << (-(char)__sub_408510_n8 & 31);
              __sub_408510_n8 -= 11;
              ::__sub_408510_n8 = __sub_408510_n8;
              __sub_408510_n256_2 |= v276;
            }
            ::__sub_408510_n256 = __sub_408510_n256_2;
            continue;
          }
        }
        else if ( n11 == 11 )
        {
          n8_1 = __sub_408510_dword_439300[n24_2];
          if ( n8_1 )
          {
            ++kk;
            v274 = *((unsigned __int16 *)kk_2 + kk);
            if ( __sub_408510_n8 < n8_1 )
            {
              ::__sub_408510_n8 = __sub_408510_n8;
              *(_DWORD *)__sub_408510_Buffer_1 = (2 * (v274 << ((31 - __sub_408510_n8) & 31))) | __sub_408510_n256_2;
              __sub_408510_Buffer_1 = __sub_408510_Buffer_0;
              __sub_408510_Buffer_0 += 4;
              __sub_408510_n256_2 = v274 >> (::__sub_408510_n8 & 31);
              ::__sub_408510_n256 = v274 >> (::__sub_408510_n8 & 31);
              __sub_408510_n8 = ::__sub_408510_n8 - n8_1 + 32;
              ::__sub_408510_n8 = __sub_408510_n8;
            }
            else
            {
              v275 = v274 << (-(char)__sub_408510_n8 & 31);
              __sub_408510_n8 -= n8_1;
              ::__sub_408510_n8 = __sub_408510_n8;
              __sub_408510_n256_2 |= v275;
              ::__sub_408510_n256 = __sub_408510_n256_2;
            }
            continue;
          }
        }
        ::__sub_408510_n8 = __sub_408510_n8;
        ::__sub_408510_n256 = __sub_408510_n256_2;
      }
    }
  }
  __op_delete(Block);
  __op_delete(kk_2);
  __op_delete(__sub_408510_dword_443408);
  __op_delete(__sub_408510_dword_442DE0);
  __op_delete(::__sub_408510_n633);
  __op_delete(::__sub_408510_buf_2);
}

#undef FILE
#undef sub_40A8A0
#undef sub_40AE10
#undef sub_40AF40
#undef sub_40B330
#undef sub_40BEE0
#undef sub_411700
#undef sub_434980
#undef sub_4349F0
