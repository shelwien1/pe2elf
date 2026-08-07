// sub_405CF0 @ 0x00405CF0 — __usercall
// Extracted from BMF.c:4986-5950 by extract.py per incdec.md.

typedef unsigned char t_sub_405CF0_byte_44339C[0x10000];
static t_sub_405CF0_byte_44339C& __sub_405CF0_byte_44339C = *(t_sub_405CF0_byte_44339C*)0x0044339C;
typedef unsigned char t_sub_405CF0_byte_44339D[0x10000];
static t_sub_405CF0_byte_44339D& __sub_405CF0_byte_44339D = *(t_sub_405CF0_byte_44339D*)0x0044339D;
typedef unsigned char t_sub_405CF0_byte_44339F[0x10000];
static t_sub_405CF0_byte_44339F& __sub_405CF0_byte_44339F = *(t_sub_405CF0_byte_44339F*)0x0044339F;
typedef unsigned char t_sub_405CF0_byte_4433AC[0x10000];
static t_sub_405CF0_byte_4433AC& __sub_405CF0_byte_4433AC = *(t_sub_405CF0_byte_4433AC*)0x004433AC;
typedef unsigned char t_sub_405CF0_byte_4433AD[16];
static t_sub_405CF0_byte_4433AD& __sub_405CF0_byte_4433AD = *(t_sub_405CF0_byte_4433AD*)0x004433AD;
typedef char t_sub_405CF0_byte_4433CF;
static t_sub_405CF0_byte_4433CF& __sub_405CF0_byte_4433CF = *(t_sub_405CF0_byte_4433CF*)0x004433CF;
typedef int t_sub_405CF0_dword_441090;
static t_sub_405CF0_dword_441090& __sub_405CF0_dword_441090 = *(t_sub_405CF0_dword_441090*)0x00441090;
typedef int t_sub_405CF0_dword_443388;
static t_sub_405CF0_dword_443388& __sub_405CF0_dword_443388 = *(t_sub_405CF0_dword_443388*)0x00443388;
typedef int t_sub_405CF0_dword_4433A0[0x10000];
static t_sub_405CF0_dword_4433A0& __sub_405CF0_dword_4433A0 = *(t_sub_405CF0_dword_4433A0*)0x004433A0;
typedef int t_sub_405CF0_dword_4433A4[0x10000];
static t_sub_405CF0_dword_4433A4& __sub_405CF0_dword_4433A4 = *(t_sub_405CF0_dword_4433A4*)0x004433A4;
typedef int t_sub_405CF0_n191;
static t_sub_405CF0_n191& __sub_405CF0_n191 = *(t_sub_405CF0_n191*)0x004433D0;
typedef int t_sub_405CF0_n191_0;
static t_sub_405CF0_n191_0& __sub_405CF0_n191_0 = *(t_sub_405CF0_n191_0*)0x004433D4;
typedef int t_sub_405CF0_n191_1;
static t_sub_405CF0_n191_1& __sub_405CF0_n191_1 = *(t_sub_405CF0_n191_1*)0x004433D8;
typedef int t_sub_405CF0_n256_2[0x10000];
static t_sub_405CF0_n256_2& __sub_405CF0_n256_2 = *(t_sub_405CF0_n256_2*)0x0044338C;
typedef char t_sub_405CF0_n3_0;
static t_sub_405CF0_n3_0& __sub_405CF0_n3_0 = *(t_sub_405CF0_n3_0*)0x004433CD;
typedef char t_sub_405CF0_n3_1;
static t_sub_405CF0_n3_1& __sub_405CF0_n3_1 = *(t_sub_405CF0_n3_1*)0x004433CC;
typedef int t_sub_405CF0_n4_5;
static t_sub_405CF0_n4_5& __sub_405CF0_n4_5 = *(t_sub_405CF0_n4_5*)0x00443394;
typedef int t_sub_405CF0_n7_0;
static t_sub_405CF0_n7_0& __sub_405CF0_n7_0 = *(t_sub_405CF0_n7_0*)0x0044109C;

#ifndef __PE_DECL___sub_411700
#define __PE_DECL___sub_411700
typedef int t_sub_411700(int a1, int n2);
static t_sub_411700& __sub_411700 = *(t_sub_411700*)0x00411700;
#endif
#define sub_411700 __sub_411700
#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0
#define sub_407460 __sub_407460

PROBE_DECL(__sub_405CF0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) int __sub_405CF0(int a1, int n3, char a3)
{
  alignas(16) unsigned char __hexrays_frame[41456];   // original frame, ebp-0xa1e0..ebp+0x0
  int &v174 = *(int *)(__hexrays_frame + 0);
  int &v175 = *(int *)(__hexrays_frame + 4);
  int &v176 = *(int *)(__hexrays_frame + 8);
  char (&buf)[4] = *(char (*)[4])(__hexrays_frame + 16);
  int (&v178)[1024] = *(int (*)[1024])(__hexrays_frame + 4112);
  int (&v179)[1024] = *(int (*)[1024])(__hexrays_frame + 8208);
  int (&v180)[5120] = *(int (*)[5120])(__hexrays_frame + 12304);
  char (&buf_3)[4] = *(char (*)[4])(__hexrays_frame + 32784);
  char (&buf_1)[4] = *(char (*)[4])(__hexrays_frame + 34832);
  int &v183 = *(int *)(__hexrays_frame + 34836);
  int &v184 = *(int *)(__hexrays_frame + 34840);
  int &v185 = *(int *)(__hexrays_frame + 34844);
  unsigned __int8 * &v186 = *(unsigned __int8 * *)(__hexrays_frame + 34848);
  unsigned __int8 * &v187 = *(unsigned __int8 * *)(__hexrays_frame + 34852);
  int &v188 = *(int *)(__hexrays_frame + 34856);
  int &v189 = *(int *)(__hexrays_frame + 34860);
  unsigned __int8 * &v190 = *(unsigned __int8 * *)(__hexrays_frame + 34864);
  int &v191 = *(int *)(__hexrays_frame + 34868);
  int &v192 = *(int *)(__hexrays_frame + 34872);
  int &v193 = *(int *)(__hexrays_frame + 34876);
  unsigned __int8 * &v194 = *(unsigned __int8 * *)(__hexrays_frame + 34880);
  unsigned __int8 * &v195 = *(unsigned __int8 * *)(__hexrays_frame + 34884);
  int &v196 = *(int *)(__hexrays_frame + 34888);
  int &v197 = *(int *)(__hexrays_frame + 34892);
  unsigned __int8 * &v198 = *(unsigned __int8 * *)(__hexrays_frame + 34896);
  int &v199 = *(int *)(__hexrays_frame + 34900);
  char (&buf_4)[4] = *(char (*)[4])(__hexrays_frame + 36880);
  char (&buf_2)[4] = *(char (*)[4])(__hexrays_frame + 38928);
  __m128i &v202 = *(__m128i *)(__hexrays_frame + 40976);
  __m128i &v203 = *(__m128i *)(__hexrays_frame + 40992);
  __m128i &v204 = *(__m128i *)(__hexrays_frame + 41008);
  __m128i &v205 = *(__m128i *)(__hexrays_frame + 41024);
  __m128i &v206 = *(__m128i *)(__hexrays_frame + 41040);
  __m128i &v207 = *(__m128i *)(__hexrays_frame + 41056);
  __int64 &v208 = *(__int64 *)(__hexrays_frame + 41072);
  __int64 &v209 = *(__int64 *)(__hexrays_frame + 41080);
  double &v210 = *(double *)(__hexrays_frame + 41088);
  double &v211 = *(double *)(__hexrays_frame + 41096);
  double &v212 = *(double *)(__hexrays_frame + 41104);
  double &v213 = *(double *)(__hexrays_frame + 41112);
  int (&v214)[4] = *(int (*)[4])(__hexrays_frame + 41120);
  _QWORD (&v215)[5] = *(_QWORD (*)[5])(__hexrays_frame + 41136);
  double &v216 = *(double *)(__hexrays_frame + 41176);
  int (&v217)[16] = *(int (*)[16])(__hexrays_frame + 41184);
  char (&v218)[64] = *(char (*)[64])(__hexrays_frame + 41248);
  char (&v219)[64] = *(char (*)[64])(__hexrays_frame + 41312);
  __int64 &v220 = *(__int64 *)(__hexrays_frame + 41376);
  double &v221 = *(double *)(__hexrays_frame + 41384);
  double &v222 = *(double *)(__hexrays_frame + 41392);
  unsigned __int8 * &v223 = *(unsigned __int8 * *)(__hexrays_frame + 41400);
  unsigned int &v224 = *(unsigned int *)(__hexrays_frame + 41404);
  int &__sub_405CF0_n191_1 = *(int *)(__hexrays_frame + 41408);
  unsigned __int8 * &v226 = *(unsigned __int8 * *)(__hexrays_frame + 41412);
  unsigned int &v227 = *(unsigned int *)(__hexrays_frame + 41416);
  int &v228 = *(int *)(__hexrays_frame + 41424);
  PROBE_HIT(__sub_405CF0);
  void *v3; // esp
  int n4; // esi
  int v5; // edx
  int v6; // ecx
  char v7; // fps
  int n192; // eax
  unsigned int v9; // ebx
  char v10; // al
  int v11; // edi
  char v12; // dl
  int v13; // edx
  int v14; // edx
  unsigned int v15; // edi
  char v16; // fps
  unsigned int v17; // ebx
  char v18; // fps
  bool v19; // zf
  BOOL n2_3; // edi
  __m128i v21; // xmm0
  char v22; // fps
  int n2; // eax
  int n16; // edx
  int *v25; // eax
  unsigned int v26; // ebx
  int n128_1; // ecx
  int n128; // edi
  unsigned __int8 *v29; // eax
  int v30; // ebx
  int v31; // esi
  int v32; // ecx
  int v33; // edi
  int v34; // edx
  int v35; // esi
  unsigned int v36; // edx
  int n0x4000; // edx
  unsigned int v38; // ebx
  unsigned int v39; // eax
  bool n2_4; // cf
  int n2_1; // eax
  bool v42; // cc
  __int32 v43; // ebx
  char *v44; // eax
  int n0x100; // edi
  __m128i v46; // xmm1
  __m128i v47; // xmm1
  int v48; // ecx
  int v49; // ebx
  char n0x100_1; // dl
  __m128i v51; // xmm1
  int i; // edx
  int n255; // eax
  __m128i v54; // xmm1
  int j_1; // ebx
  int j; // ecx
  int v57; // esi
  int n128_2; // eax
  int v59; // edi
  int n128_3; // eax
  int v61; // ecx
  int v62; // edx
  int v63; // edx
  unsigned __int8 *v64; // eax
  double v65; // xmm2_8
  double v66; // xmm1_8
  unsigned int v67; // ecx
  double v68; // xmm3_8
  double v69; // xmm5_8
  double v70; // xmm0_8
  int v71; // ebx
  double v72; // xmm3_8
  double v73; // xmm4_8
  double v74; // xmm0_8
  double v75; // xmm6_8
  double v76; // xmm0_8
  int __sub_405CF0_n191; // ebx
  int n191_2; // ebx
  int n191_3; // esi
  unsigned int v80; // eax
  int v81; // ebx
  int v82; // edi
  int v83; // esi
  int v84; // esi
  int v85; // ebx
  __int32 v86; // edi
  int v87; // esi
  int v88; // edi
  int v89; // ebx
  int v90; // esi
  int v91; // esi
  __int16 v92; // ax
  __int32 v93; // edx
  int v94; // ecx
  int v95; // edx
  __int32 v96; // eax
  unsigned __int8 *v97; // esi
  int v98; // edi
  int v99; // edx
  int v100; // ebx
  int v101; // edx
  int v102; // edi
  unsigned int v103; // eax
  unsigned int v104; // edi
  unsigned int v105; // eax
  bool v106; // cf
  int n191_4; // eax
  unsigned int v108; // eax
  int n2_2; // edx
  unsigned int v110; // eax
  int __sub_405CF0_n3_1; // edx
  int *v112; // edx
  __m128i v113; // xmm0
  __m128i v114; // xmm0
  int v115; // ebx
  int v116; // esi
  char k; // cl
  int v118; // ecx
  int v119; // edx
  int v120; // ebx
  unsigned __int8 *v121; // edx
  unsigned __int8 *v122; // eax
  unsigned __int8 *v123; // ecx
  int v124; // edi
  int v125; // eax
  int v126; // ecx
  int v127; // esi
  int v128; // ecx
  unsigned int v129; // eax
  int v130; // ecx
  int v131; // ecx
  int v132; // edx
  int v133; // ebx
  unsigned __int8 *v134; // edx
  unsigned __int8 *v135; // eax
  unsigned __int8 *v136; // ecx
  int v137; // edi
  int v138; // eax
  int v139; // ecx
  int v140; // esi
  int v141; // ecx
  unsigned int v142; // eax
  int v143; // edx
  int n192_1; // esi
  int n192_2; // edi
  int n192_4; // ecx
  int n192_3; // edx
  int v148; // ecx
  int v149; // edx
  int v150; // ebx
  unsigned __int8 *v151; // edx
  int v152; // eax
  unsigned __int8 *v153; // ecx
  int v154; // edi
  int v155; // eax
  int v156; // ecx
  __int32 v157; // esi
  int v158; // ecx
  unsigned int v159; // eax
  int n192_5; // ecx
  int v161; // ecx
  int v162; // edx
  int v163; // ebx
  unsigned __int8 *v164; // edx
  int v165; // eax
  unsigned __int8 *v166; // ecx
  int v167; // edi
  int v168; // eax
  int v169; // ecx
  __int32 v170; // esi
  int v171; // ecx
  unsigned int v172; // eax
  int n192_6; // edx

  v228 = a1;
  v3 = alloca(41424);
  n4 = __sub_405CF0_n4_5;
  v5 = *(unsigned __int16 *)(a1 + 4);
  v6 = *(_DWORD *)(a1 + 12);
  v226 = (unsigned __int8 *)a1;
  __sub_405CF0_dword_443388 = 1;
  LODWORD(v208) = v5;
  v227 = a1 + v6 + 16;
  sub_4349F0(buf,0,0x8000);
  n192 = 192;
  do
  {
    *(_OWORD *)((char *)&v215[4] + n192) = 0;
    *(_OWORD *)((char *)&v215[2] + n192) = 0;
    *(_OWORD *)((char *)v215 + n192) = 0;
    *(_OWORD *)((char *)v214 + n192) = 0;
    n192 -= 64;
  }
  while ( n192 );
  if ( n4 > 0 )
  {
    if ( n4 / 2 )
    {
      v9 = 0;
      do
      {
        v10 = 2 * v9;
        v11 = 32 * v9;
        __sub_405CF0_byte_44339D[v11] = 2 * v9;
        v12 = 2 * v9++ + 1;
        __sub_405CF0_byte_44339C[v11] = v10;
        __sub_405CF0_byte_4433AD[v11] = v12;
        __sub_405CF0_byte_4433AC[v11] = v12;
      }
      while ( v9 < n4 / 2 );
      v13 = 2 * v9 + 1;
    }
    else
    {
      v13 = 1;
    }
    n192 = v13 - 1;
    if ( n4 > (unsigned int)(v13 - 1) )
    {
      v14 = 4 * v13;
      BYTE1(__sub_405CF0_n256_2[v14]) = n192;
      LOBYTE(__sub_405CF0_n256_2[v14]) = n192;
    }
    if ( n4 >= 3 )
    {
      v15 = sub_407460(v226, nullptr, (int)v217, v7, v174, v175, v176, (int)&v214[2]);
      v17 = sub_407460(v226, (unsigned __int8 *)1, (int)v218, v16, v174, v175, v176, (int)&v214[2]);
      v19 = v17 >= v15;
      if ( v17 >= v15 )
        v17 = v15;
      n2_3 = !v19;
      v205.m128i_i32[2] = n2_3;
      v21 = 0;
      n2_4 = sub_407460(v226, (unsigned __int8 *)2, (int)v219, v18, v174, v175, v176, (int)&v214[2]) < v17;
      n2 = n2_3;
      if ( n2_4 )
        n2 = 2;
      v205.m128i_i32[2] = n2;
      n16 = 16;
      v25 = &v217[16 * n2];
      do
      {
        *(_QWORD *)(n16 * 4 + 4469652) = *(_QWORD *)&v25[n16 - 2];
        *(_QWORD *)(n16 * 4 + 4469644) = *(_QWORD *)&v25[n16 - 4];
        *(_QWORD *)(n16 * 4 + 4469636) = *(_QWORD *)&v25[n16 - 6];
        *(_QWORD *)(n16 * 4 + 4469628) = *(_QWORD *)&v25[n16 - 8];
        n16 -= 8;
      }
      while ( n16 * 4 );
      v26 = v214[4 * v205.m128i_i32[2] + 2];
      v205.m128i_i32[1] = 16 * v205.m128i_i32[2];
      LODWORD(v209) = (unsigned __int8)__sub_405CF0_byte_44339D[0] - v205.m128i_i32[2];
      n128_1 = __sub_405CF0_dword_4433A4[4 * v205.m128i_i32[2]];
      HIDWORD(v208) = (unsigned __int8)__sub_405CF0_byte_4433AD[0] - v205.m128i_i32[2];
      n128 = __sub_405CF0_dword_4433A0[4 * v205.m128i_i32[2]];
      if ( __sub_405CF0_dword_441090 || (unsigned int)__sub_405CF0_n7_0 > 7 )
      {
        LODWORD(v210) = n128_1;
        v207.m128i_i32[3] = n128;
        HIDWORD(v209) = n4;
        v202.m128i_i32[1] = (__sub_405CF0_n7_0 + 5) / 3u;
        v184 = n128 - 1;
        v57 = n128 - 1;
        v192 = n128_1 - 1;
        n128_2 = n128;
        v59 = n128_1 - 1;
        v183 = n128_2 - v202.m128i_i32[1];
        n128_3 = n128_1;
        v61 = v183;
        *(_DWORD *)buf_1 = n128_3 - v202.m128i_i32[1];
        v202.m128i_i32[0] = (__int32)&v226[v205.m128i_i32[2]];
        v62 = n128_3 - v202.m128i_i32[1];
        while ( 1 )
        {
          if ( v57 <= v61 )
          {
            if ( v59 <= v62 )
            {
              v203.m128i_i32[0] = v207.m128i_i32[3] + 1;
              n192_1 = v207.m128i_i32[3] + 1;
              v205.m128i_i32[3] = LODWORD(v210) + 1;
              n192_2 = LODWORD(v210) + 1;
              v202.m128i_i32[3] = v207.m128i_i32[3] + v202.m128i_i32[1];
              n192_4 = v207.m128i_i32[3] + v202.m128i_i32[1];
              v202.m128i_i32[2] = LODWORD(v210) + v202.m128i_i32[1];
              n192_3 = LODWORD(v210) + v202.m128i_i32[1];
              while ( 1 )
              {
                if ( n192_1 >= n192_4 )
                {
                  if ( n192_2 >= n192_3 )
                  {
                    n128_1 = LODWORD(v210);
                    n128 = v207.m128i_i32[3];
                    n4 = HIDWORD(v209);
                    v21 = 0;
                    goto LABEL_19;
                  }
                  if ( n192_1 >= n192_4 )
                    goto LABEL_109;
                }
                if ( n192_1 < 192 )
                {
                  v202.m128i_i32[2] = n192_3;
                  sub_4349F0(buf_1,0,2048);
                  v148 = *(unsigned __int16 *)v226 * (*((unsigned __int16 *)v226 + 1) - 1);
                  v149 = *((unsigned __int16 *)v226 + 2);
                  v205.m128i_i32[3] = n192_2;
                  v203.m128i_i32[0] = n192_1;
                  v203.m128i_i32[1] = v148 - 1;
                  v205.m128i_i32[0] = v26;
                  v204.m128i_i32[1] = -v149;
                  v150 = -__sub_405CF0_n4_5;
                  v204.m128i_i32[0] = -v149 - __sub_405CF0_n4_5;
                  v203.m128i_i32[3] = v202.m128i_i32[0] - v204.m128i_i32[0] + 16;
                  v203.m128i_i32[2] = v209 + v202.m128i_i32[0] - v204.m128i_i32[0] + 16;
                  v151 = (unsigned __int8 *)v203.m128i_i32[2];
                  v152 = HIDWORD(v208) + v202.m128i_i32[0] - v204.m128i_i32[0] + 16;
                  v153 = (unsigned __int8 *)v203.m128i_i32[3];
                  do
                  {
                    v154 = v153[v204.m128i_i32[0]];
                    v203.m128i_i64[1] = __PAIR64__((unsigned int)v153, (unsigned int)v151);
                    v204.m128i_i32[2] = v152;
                    v155 = v154 + *v153 - v153[v204.m128i_i32[1]] - v153[v150];
                    v156 = *v151;
                    v204.m128i_i32[3] = v155;
                    v152 = v204.m128i_i32[2] - v150;
                    v157 = v203.m128i_i32[1];
                    v158 = (v204.m128i_i16[6]
                          - (unsigned __int16)((v203.m128i_i32[0]
                                              * (v151[v204.m128i_i32[0]] + v156 - v151[v204.m128i_i32[1]] - v151[v150])
                                              + LODWORD(v210)
                                              * (*(unsigned __int8 *)(v204.m128i_i32[2] + v204.m128i_i32[0])
                                               + *(unsigned __int8 *)v204.m128i_i32[2]
                                               - *(unsigned __int8 *)(v204.m128i_i32[2] + v204.m128i_i32[1])
                                               - (unsigned int)*(unsigned __int8 *)(v204.m128i_i32[2] + v150))
                                              + 40) >> 7)
                          - 256)
                         & 0x1FF;
                    ++*(_DWORD *)&buf_1[4 * v158];
                    v151 -= v150;
                    v153 = (unsigned __int8 *)(v203.m128i_i32[3] - v150);
                    v203.m128i_i32[1] = v157 - 1;
                  }
                  while ( v157 != 1 );
                  n192_2 = v205.m128i_i32[3];
                  n192_1 = v203.m128i_i32[0];
                  v26 = v205.m128i_i32[0];
                  v159 = sub_411700((int)buf_1, 512);
                  n192_3 = v202.m128i_i32[2];
                  n192_5 = v207.m128i_i32[3];
                  if ( v159 < v26 )
                  {
                    v26 = v159;
                    n192_5 = n192_1;
                  }
                  v207.m128i_i32[3] = n192_5;
                  n192_4 = v202.m128i_i32[1] + n192_5;
                }
                if ( n192_2 < n192_3 )
                {
LABEL_109:
                  if ( n192_2 < 192 )
                  {
                    v202.m128i_i32[3] = n192_4;
                    sub_4349F0(buf_2,0,2048);
                    v161 = *(unsigned __int16 *)v226 * (*((unsigned __int16 *)v226 + 1) - 1);
                    v162 = *((unsigned __int16 *)v226 + 2);
                    v205.m128i_i32[3] = n192_2;
                    v203.m128i_i32[0] = n192_1;
                    v206.m128i_i32[0] = v161 - 1;
                    v205.m128i_i32[0] = v26;
                    v207.m128i_i32[0] = -v162;
                    v163 = -__sub_405CF0_n4_5;
                    v206.m128i_i32[3] = -v162 - __sub_405CF0_n4_5;
                    v206.m128i_i32[2] = v202.m128i_i32[0] - v206.m128i_i32[3] + 16;
                    v164 = (unsigned __int8 *)(v209 + v202.m128i_i32[0] - v206.m128i_i32[3] + 16);
                    v206.m128i_i32[1] = (__int32)v164;
                    v165 = HIDWORD(v208) + v202.m128i_i32[0] - v206.m128i_i32[3] + 16;
                    v166 = (unsigned __int8 *)v206.m128i_i32[2];
                    do
                    {
                      v167 = v166[v206.m128i_i32[3]];
                      *(__int64 *)((char *)v206.m128i_i64 + 4) = __PAIR64__((unsigned int)v166, (unsigned int)v164);
                      v207.m128i_i32[1] = v165;
                      v168 = v167 + *v166 - v166[v207.m128i_i32[0]] - v166[v163];
                      v169 = *v164;
                      v207.m128i_i32[2] = v168;
                      v165 = v207.m128i_i32[1] - v163;
                      v170 = v206.m128i_i32[0];
                      v171 = (v207.m128i_i16[4]
                            - (unsigned __int16)((v207.m128i_i32[3]
                                                * (v164[v206.m128i_i32[3]] + v169 - v164[v207.m128i_i32[0]] - v164[v163])
                                                + v205.m128i_i32[3]
                                                * (*(unsigned __int8 *)(v207.m128i_i32[1] + v206.m128i_i32[3])
                                                 + *(unsigned __int8 *)v207.m128i_i32[1]
                                                 - *(unsigned __int8 *)(v207.m128i_i32[1] + v207.m128i_i32[0])
                                                 - (unsigned int)*(unsigned __int8 *)(v207.m128i_i32[1] + v163))
                                                + 40) >> 7)
                            - 256)
                           & 0x1FF;
                      ++*(_DWORD *)&buf_2[4 * v171];
                      v164 -= v163;
                      v166 = (unsigned __int8 *)(v206.m128i_i32[2] - v163);
                      v206.m128i_i32[0] = v170 - 1;
                    }
                    while ( v170 != 1 );
                    n192_2 = v205.m128i_i32[3];
                    n192_1 = v203.m128i_i32[0];
                    v26 = v205.m128i_i32[0];
                    v172 = sub_411700((int)buf_2, 512);
                    n192_4 = v202.m128i_i32[3];
                    n192_6 = LODWORD(v210);
                    if ( v172 < v26 )
                    {
                      v26 = v172;
                      n192_6 = n192_2;
                    }
                    LODWORD(v210) = n192_6;
                    n192_3 = v202.m128i_i32[1] + n192_6;
                  }
                }
                ++n192_1;
                ++n192_2;
              }
            }
            if ( v57 <= v61 )
              goto LABEL_55;
          }
          if ( v57 >= -64 )
          {
            *(_DWORD *)buf_1 = v62;
            sub_4349F0(buf_3,0,2048);
            v118 = *(unsigned __int16 *)v226 * (*((unsigned __int16 *)v226 + 1) - 1);
            v119 = *((unsigned __int16 *)v226 + 2);
            v192 = v59;
            v184 = v57;
            v185 = v118 - 1;
            v205.m128i_i32[0] = v26;
            v189 = -v119;
            v120 = -__sub_405CF0_n4_5;
            v188 = -v119 - __sub_405CF0_n4_5;
            v187 = (unsigned __int8 *)(v202.m128i_i32[0] - v188 + 16);
            v186 = (unsigned __int8 *)(v209 + v202.m128i_i32[0] - v188 + 16);
            v121 = v186;
            v122 = (unsigned __int8 *)(HIDWORD(v208) + v202.m128i_i32[0] - v188 + 16);
            v123 = v187;
            do
            {
              v124 = v123[v188];
              v186 = v121;
              v187 = v123;
              v190 = v122;
              v125 = v124 + *v123 - v123[v189] - v123[v120];
              v126 = *v121;
              v191 = v125;
              v122 = &v190[-v120];
              v127 = v185;
              v128 = ((_WORD)v191
                    - (unsigned __int16)((v184 * (v121[v188] + v126 - v121[v189] - v121[v120])
                                        + LODWORD(v210) * (v190[v188] + *v190 - v190[v189] - (unsigned int)v190[v120])
                                        + 40) >> 7)
                    - 256)
                   & 0x1FF;
              ++*(_DWORD *)&buf_3[4 * v128];
              v121 -= v120;
              v123 = &v187[-v120];
              v185 = v127 - 1;
            }
            while ( v127 != 1 );
            v59 = v192;
            v57 = v184;
            v26 = v205.m128i_i32[0];
            v129 = sub_411700((int)buf_3, 512);
            v62 = *(_DWORD *)buf_1;
            v130 = v207.m128i_i32[3];
            if ( v129 < v26 )
            {
              v26 = v129;
              v130 = v57;
            }
            v207.m128i_i32[3] = v130;
            v61 = v130 - v202.m128i_i32[1];
          }
          if ( v59 > v62 )
          {
LABEL_55:
            if ( v59 >= -64 )
            {
              v183 = v61;
              sub_4349F0(buf_4,0,2048);
              v131 = *(unsigned __int16 *)v226 * (*((unsigned __int16 *)v226 + 1) - 1);
              v132 = *((unsigned __int16 *)v226 + 2);
              v192 = v59;
              v184 = v57;
              v193 = v131 - 1;
              v205.m128i_i32[0] = v26;
              v197 = -v132;
              v133 = -__sub_405CF0_n4_5;
              v196 = -v132 - __sub_405CF0_n4_5;
              v195 = (unsigned __int8 *)(v202.m128i_i32[0] - v196 + 16);
              v134 = (unsigned __int8 *)(v209 + v202.m128i_i32[0] - v196 + 16);
              v194 = v134;
              v135 = (unsigned __int8 *)(HIDWORD(v208) + v202.m128i_i32[0] - v196 + 16);
              v136 = v195;
              do
              {
                v137 = v136[v196];
                v194 = v134;
                v195 = v136;
                v198 = v135;
                v138 = v137 + *v136 - v136[v197] - v136[v133];
                v139 = *v134;
                v199 = v138;
                v135 = &v198[-v133];
                v140 = v193;
                v141 = ((_WORD)v199
                      - (unsigned __int16)((v207.m128i_i32[3] * (v134[v196] + v139 - v134[v197] - v134[v133])
                                          + v192 * (v198[v196] + *v198 - v198[v197] - (unsigned int)v198[v133])
                                          + 40) >> 7)
                      - 256)
                     & 0x1FF;
                ++*(_DWORD *)&buf_4[4 * v141];
                v134 -= v133;
                v136 = &v195[-v133];
                v193 = v140 - 1;
              }
              while ( v140 != 1 );
              v59 = v192;
              v57 = v184;
              v26 = v205.m128i_i32[0];
              v142 = sub_411700((int)buf_4, 512);
              v61 = v183;
              v143 = LODWORD(v210);
              if ( v142 < v26 )
              {
                v26 = v142;
                v143 = v59;
              }
              LODWORD(v210) = v143;
              v62 = v143 - v202.m128i_i32[1];
            }
          }
          --v57;
          --v59;
        }
      }
LABEL_19:
      v29 = &v226[v208 + 16 + n4 + v205.m128i_i32[2]];
      if ( (unsigned int)v29 < v227 )
      {
        LODWORD(v210) = n128_1;
        v207.m128i_i32[3] = n128;
        v205.m128i_i32[0] = v26;
        HIDWORD(v209) = n4;
        do
        {
          v30 = v29[HIDWORD(v208)];
          v31 = v30 * LODWORD(v210);
          v32 = v29[v209];
          v33 = v32 * v207.m128i_i32[3];
          ++v180[v30 - v32 + 1280];
          v34 = *v29 + 512;
          v29 += HIDWORD(v209);
          v35 = ((_WORD)v34 - (unsigned __int16)((unsigned int)(v31 + v33 + 40) >> 7)) & 0x3FF;
          ++*(_DWORD *)&buf[4 * v35];
          ++v178[v34 - v32];
          ++v179[v34 - v30];
          v36 = v34 - ((unsigned int)(((v32 + v30) << 6) + 40) >> 7);
          ++v180[v36];
        }
        while ( (unsigned int)v29 < v227 );
        n128_1 = LODWORD(v210);
        n128 = v207.m128i_i32[3];
        v26 = v205.m128i_i32[0];
        n4 = HIDWORD(v209);
      }
      n0x4000 = v26 >> 7;
      if ( v26 >> 7 >= 0x4000 )
        n0x4000 = 0x4000;
      v38 = n0x4000 + v26;
      v39 = *(int *)((char *)&v214[3] + v205.m128i_i32[1]);
      n2_4 = v39 < v38;
      if ( v39 < v38 )
      {
        v38 = *(int *)((char *)&v214[3] + v205.m128i_i32[1]);
        n128 = 128;
        n128_1 = 0;
      }
      n2_1 = n2_4;
      if ( *(_DWORD *)((char *)v215 + v205.m128i_i32[1]) < v38 )
      {
        v38 = *(_DWORD *)((char *)v215 + v205.m128i_i32[1]);
        n2_1 = 2;
        n128 = 0;
        n128_1 = 128;
      }
      v42 = v38 <= *(_DWORD *)((char *)v215 + v205.m128i_i32[1] + 4);
      if ( v38 > *(_DWORD *)((char *)v215 + v205.m128i_i32[1] + 4) )
        n2_1 = 3;
      v43 = v205.m128i_i32[1];
      if ( !v42 )
      {
        n128 = 64;
        n128_1 = 64;
      }
      *(int *)((char *)__sub_405CF0_dword_4433A0 + v205.m128i_i32[1]) = n128;
      *(int *)((char *)__sub_405CF0_dword_4433A4 + v43) = n128_1;
      v44 = &buf[4096 * n2_1];
      n0x100 = (unsigned __int8)v44 & 0xF;
      v46 = _mm_cvtsi32_si128(0);
      do
      {
        v46 = _mm_add_epi32(
                _mm_add_epi32(
                  _mm_add_epi32(_mm_add_epi32(v46, *(__m128i *)&v44[4 * n0x100]), *(__m128i *)&v44[4 * n0x100 + 16]),
                  *(__m128i *)&v44[4 * n0x100 + 32]),
                *(__m128i *)&v44[4 * n0x100 + 48]);
        n0x100 += 16;
      }
      while ( (unsigned int)n0x100 < 0x100 );
      v47 = _mm_add_epi32(v46, _mm_srli_si128(v46, 8));
      v48 = _mm_cvtsi128_si32(_mm_add_epi32(v47, _mm_srli_si128(v47, 4)));
      v49 = v48;
      n0x100_1 = -1;
      if ( n0x100 < 1024 )
      {
        HIDWORD(v209) = n4;
        do
        {
          v48 = *(_DWORD *)&v44[4 * n0x100] + v48 - *(_DWORD *)&v44[4 * n0x100 - 1024];
          if ( v48 >= v49 )
          {
            n0x100_1 = n0x100;
            v49 = v48;
          }
          ++n0x100;
        }
        while ( n0x100 < 1024 );
        n4 = HIDWORD(v209);
      }
      v51 = v21;
      __sub_405CF0_byte_44339F[v205.m128i_i32[1]] = n0x100_1 + 1;
      for ( i = 0; (unsigned int)i < 0x100; i += 16 )
        v51 = _mm_add_epi32(
                _mm_add_epi32(
                  _mm_add_epi32(_mm_add_epi32(v51, *(__m128i *)&v180[i + 1024]), *(__m128i *)&v180[i + 1028]),
                  *(__m128i *)&v180[i + 1032]),
                *(__m128i *)&v180[i + 1036]);
      n255 = 255;
      v54 = _mm_add_epi32(v51, _mm_srli_si128(v51, 8));
      j_1 = _mm_cvtsi128_si32(_mm_add_epi32(v54, _mm_srli_si128(v54, 4)));
      for ( j = j_1; i < 512; ++i )
      {
        j = v180[i + 1024] + j - v180[i + 768];
        if ( j >= j_1 )
        {
          n255 = i;
          j_1 = j;
        }
      }
      n192 = n255 + 1;
      __sub_405CF0_byte_44339F[16 * HIDWORD(v208) + v205.m128i_i32[1]] = n192;
      if ( n4 >= 4 )
      {
        v202 = v21;
        v203 = v21;
        v204 = v21;
        v205 = v21;
        v206 = v21;
        v207 = v21;
        sub_4349F0(buf,0,0x8000);
        v223 = &v226[v208];
        v63 = (int)(v227 - 17 - (_DWORD)&v226[v208]) / 4;
        v64 = &v226[v208 + 20];
        if ( v227 <= (unsigned int)v64 )
        {
          v72 = *(double *)&v202.m128i_i64[1];
          v73 = *(double *)v203.m128i_i64;
          v74 = *(double *)&v204.m128i_i64[1];
          v209 = v202.m128i_i64[1];
          v208 = v204.m128i_i64[1];
          v216 = *(double *)v202.m128i_i64;
          v220 = v206.m128i_i64[1];
          v75 = *(double *)v203.m128i_i64;
        }
        else
        {
          v65 = *(double *)v206.m128i_i64;
          v66 = *(double *)v204.m128i_i64;
          v220 = v206.m128i_i64[1];
          v216 = *(double *)v202.m128i_i64;
          v221 = *(double *)&v202.m128i_i64[1];
          v212 = *(double *)v203.m128i_i64;
          v222 = *(double *)&v204.m128i_i64[1];
          v213 = *(double *)v207.m128i_i64;
          v211 = *(double *)&v207.m128i_i64[1];
          LODWORD(v210) = &v226[v208 + 20];
          v67 = 0;
          v224 = (int)(v227 - 17 - (_DWORD)&v226[v208]) / 4;
          do
          {
            v68 = (double)(v226[4 * v67 + 16] + v223[4 * v67 + 20] - (v226[4 * v67 + 20] + v223[4 * v67 + 16]));
            v69 = (double)(v226[4 * v67 + 17] + v223[4 * v67 + 21] - (v226[4 * v67 + 21] + v223[4 * v67 + 17]));
            v70 = (double)(v226[4 * v67 + 18] + v223[4 * v67 + 22] - (v226[4 * v67 + 22] + v223[4 * v67 + 18]));
            v71 = v226[4 * v67 + 19] + v223[4 * v67 + 23] - (v226[4 * v67 + 23] + v223[4 * v67 + 19]);
            v216 = v216 + v68 * v68;
            ++v67;
            v221 = v221 + v68 * v69;
            v212 = v212 + v68 * v70;
            v66 = v66 + v69 * v69;
            v222 = v222 + v69 * v70;
            v65 = v65 + v70 * v70;
            *(double *)&v220 = *(double *)&v220 + v68 * (double)v71;
            v213 = v213 + v69 * (double)v71;
            v211 = v211 + v70 * (double)v71;
          }
          while ( v67 < v224 );
          v72 = v221;
          v73 = v212;
          v74 = v222;
          v64 = (unsigned __int8 *)LODWORD(v210);
          v63 = v224;
          *(double *)&v207.m128i_i64[1] = v211;
          *(double *)v207.m128i_i64 = v213;
          v206.m128i_i64[1] = v220;
          *(double *)v206.m128i_i64 = v65;
          *(double *)&v204.m128i_i64[1] = v222;
          *(double *)v204.m128i_i64 = v66;
          *(double *)v203.m128i_i64 = v212;
          *(double *)&v202.m128i_i64[1] = v221;
          *(double *)v202.m128i_i64 = v216;
          v75 = v212;
          *(double *)&v208 = v222;
          *(double *)&v209 = v221;
        }
        v221 = v72;
        v222 = v74;
        v210 = v75;
        *(double *)&v203.m128i_i64[1] = v72;
        *(double *)v205.m128i_i64 = v73;
        *(double *)&v205.m128i_i64[1] = v74;
        v211 = v216 * *(double *)v206.m128i_i64 - v75 * v73;
        v212 = 0.0 - v216 * v74 + v73 * *(double *)&v209;
        v213 = v75 * v74 - *(double *)&v209 * *(double *)v206.m128i_i64;
        v76 = 128.0 / (*(double *)v204.m128i_i64 * v211 + *(double *)&v208 * v212 + v72 * v213 + 0.1);
        *(double *)v214 = v76;
        __sub_405CF0_n191 = (int)(((v73 * *(double *)&v208 - v72 * *(double *)v206.m128i_i64) * *(double *)v207.m128i_i64
                    + (0.0 - v73 * *(double *)v204.m128i_i64 + v72 * v222) * *(double *)&v207.m128i_i64[1]
                    + (*(double *)v206.m128i_i64 * *(double *)v204.m128i_i64 - v222 * *(double *)&v208)
                    * *(double *)&v220)
                   * v76);
        if ( __sub_405CF0_n191 >= 191 )
          __sub_405CF0_n191 = 191;
        if ( __sub_405CF0_n191 < -64 )
          __sub_405CF0_n191 = -64;
        __sub_405CF0_n191_1 = __sub_405CF0_n191;
        n191_2 = (int)((v211 * *(double *)v207.m128i_i64 + v212 * *(double *)&v207.m128i_i64[1]
                                                         + v213 * *(double *)&v220)
                     * v76);
        if ( n191_2 >= 191 )
          n191_2 = 191;
        if ( n191_2 < -64 )
          n191_2 = -64;
        n191_3 = (int)(*(double *)v214
                     * ((v216 * *(double *)&v207.m128i_i64[1] - v210 * *(double *)&v220) * *(double *)v204.m128i_i64
                      + (0.0 - v216 * *(double *)v207.m128i_i64 + *(double *)&v220 * *(double *)&v209)
                      * *(double *)&v208
                      + (v210 * *(double *)v207.m128i_i64 - *(double *)&v209 * *(double *)&v207.m128i_i64[1]) * v221));
        if ( n191_3 >= 191 )
          n191_3 = 191;
        if ( n191_3 < -64 )
          n191_3 = -64;
        if ( (unsigned int)v64 < v227 )
        {
          v202.m128i_i64[0] = __PAIR64__(n191_3, n191_2);
          v224 = v63;
          v80 = 0;
          do
          {
            v81 = v226[4 * v80 + 20];
            v82 = v226[4 * v80 + 16] + v223[4 * v80 + 20];
            v83 = v223[4 * v80 + 16];
            v202.m128i_i32[2] = v80;
            v84 = v81 + v83;
            v85 = v223[4 * v80 + 21];
            v86 = v82 - v84;
            v87 = v223[4 * v80 + 17];
            v202.m128i_i32[3] = v86;
            v88 = v226[4 * v80 + 22];
            v89 = v226[4 * v80 + 17] + v85 - (v226[4 * v80 + 21] + v87);
            v90 = v223[4 * v80 + 22];
            v203.m128i_i32[0] = v89;
            v91 = v226[4 * v80 + 18] + v90 - (v88 + v223[4 * v80 + 18]);
            LOWORD(v89) = v226[4 * v80 + 19] + v223[4 * v80 + 23] - v223[4 * v80 + 19] - v226[4 * v80 + 23];
            v92 = v203.m128i_i16[0];
            LOWORD(v89) = v89 - 512;
            v93 = v203.m128i_i32[0] * v202.m128i_i32[0] + v202.m128i_i32[3] * __sub_405CF0_n191_1;
            v94 = v91 * v202.m128i_i32[1];
            ++v178[((_WORD)v89 - v202.m128i_i16[6]) & 0x3FF];
            v95 = ((_WORD)v89 - (unsigned __int16)((unsigned int)(v93 + v94 + 63) >> 7)) & 0x3FF;
            ++*(_DWORD *)&buf[4 * v95];
            ++v179[((_WORD)v89 - v92) & 0x3FF];
            LOWORD(v89) = v89 - v91;
            v96 = v202.m128i_i32[2];
            v97 = v223;
            ++v180[v89 & 0x3FF];
            v98 = v97[4 * v96 + 23] + 256;
            v99 = ((_WORD)v98
                 - (unsigned __int16)((v202.m128i_i32[0] * v97[4 * v96 + 21]
                                     + __sub_405CF0_n191_1 * v97[4 * v96 + 20]
                                     + v202.m128i_i32[1] * (unsigned int)v97[4 * v96 + 22]
                                     + 63) >> 7)
                 + 256)
                & 0x3FF;
            ++v180[v99 + 1024];
            v100 = v98 - v97[4 * v96 + 20];
            ++v180[v100 + 2048];
            v101 = v98 - v97[4 * v96 + 21];
            ++v180[v101 + 3072];
            v102 = v98 - v97[4 * v96 + 22];
            ++v180[v102 + 4096];
            v80 = v96 + 1;
          }
          while ( v80 < v224 );
          n191_3 = v202.m128i_i32[1];
          n191_2 = v202.m128i_i32[0];
        }
        v103 = sub_411700((int)buf, 1024);
        v104 = (v103 >> 7) + v103;
        v105 = sub_411700((int)v178, 1024);
        v106 = v105 < v104;
        if ( v105 < v104 )
          v104 = v105;
        n191_4 = __sub_405CF0_n191_1;
        if ( v106 )
        {
          n191_4 = 128;
          n191_3 = 0;
          n191_2 = 0;
        }
        __sub_405CF0_n191_1 = n191_4;
        v202.m128i_i32[0] = v106;
        v108 = sub_411700((int)v179, 1024);
        n2_2 = v202.m128i_i32[0];
        if ( v108 < v104 )
        {
          v104 = v108;
          n2_2 = 2;
          n191_2 = 128;
          n191_3 = 0;
          __sub_405CF0_n191_1 = 0;
        }
        v202.m128i_i32[0] = n2_2;
        v110 = sub_411700((int)v180, 1024);
        __sub_405CF0_n3_1 = v202.m128i_i32[0];
        if ( v110 < v104 )
        {
          __sub_405CF0_n3_1 = 3;
          n191_3 = 128;
          n191_2 = 0;
          __sub_405CF0_n191_1 = 0;
        }
        ::__sub_405CF0_n191 = __sub_405CF0_n191_1;
        __sub_405CF0_n191_0 = n191_2;
        ::__sub_405CF0_n191_1 = n191_3;
        __sub_405CF0_n3_0 = 3;
        ::__sub_405CF0_n3_1 = 3;
        v112 = &v180[1024 * __sub_405CF0_n3_1 + 1024];
        n192 = (unsigned __int8)v112 & 0xF;
        v113 = _mm_cvtsi32_si128(0);
        do
        {
          v113 = _mm_add_epi32(
                   _mm_add_epi32(
                     _mm_add_epi32(_mm_add_epi32(v113, *(__m128i *)&v112[n192]), *(__m128i *)&v112[n192 + 4]),
                     *(__m128i *)&v112[n192 + 8]),
                   *(__m128i *)&v112[n192 + 12]);
          n192 += 16;
        }
        while ( (unsigned int)n192 < 0x100 );
        v114 = _mm_add_epi32(v113, _mm_srli_si128(v113, 8));
        v115 = _mm_cvtsi128_si32(_mm_add_epi32(v114, _mm_srli_si128(v114, 4)));
        v116 = v115;
        for ( k = -1; n192 < 1024; ++n192 )
        {
          v115 = v112[n192] + v115 - v112[n192 - 256];
          if ( v115 >= v116 )
          {
            k = n192;
            v116 = v115;
          }
        }
        __sub_405CF0_byte_4433CF = k + 1;
      }
    }
  }
  return n192;
}

// __usercall thunk for sub_405CF0 @ 0x00405CF0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_405CF0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $20, %esp\n"
    "mov %eax, 4(%esp)\n"
    "mov %ebx, 8(%esp)\n"
    "fnstsw %ax\n"
    "mov %eax, 12(%esp)\n"
    "push 12(%esp)\n"
    "push 12(%esp)\n"
    "push 12(%esp)\n"
    "call __sub_405CF0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef sub_407460
#undef sub_411700
#undef sub_4349F0
