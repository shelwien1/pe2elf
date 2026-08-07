// sub_427740 @ 0x00427740 — __cdecl
// Extracted from BMF.c:32034-32445 by extract.py per incdec.md.

typedef unsigned char t_sub_427740_byte_44339D[0x10000];
static t_sub_427740_byte_44339D& __sub_427740_byte_44339D = *(t_sub_427740_byte_44339D*)0x0044339D;
typedef unsigned char t_sub_427740_byte_44339E[0x10000];
static t_sub_427740_byte_44339E& __sub_427740_byte_44339E = *(t_sub_427740_byte_44339E*)0x0044339E;
typedef unsigned char t_sub_427740_byte_44339F[0x10000];
static t_sub_427740_byte_44339F& __sub_427740_byte_44339F = *(t_sub_427740_byte_44339F*)0x0044339F;
typedef unsigned char t_sub_427740_byte_4433AD[16];
static t_sub_427740_byte_4433AD& __sub_427740_byte_4433AD = *(t_sub_427740_byte_4433AD*)0x004433AD;
typedef unsigned char t_sub_427740_byte_4433BD[15];
static t_sub_427740_byte_4433BD& __sub_427740_byte_4433BD = *(t_sub_427740_byte_4433BD*)0x004433BD;
typedef int t_sub_427740_dword_4433A0[0x10000];
static t_sub_427740_dword_4433A0& __sub_427740_dword_4433A0 = *(t_sub_427740_dword_4433A0*)0x004433A0;
typedef int t_sub_427740_dword_4433A4[0x10000];
static t_sub_427740_dword_4433A4& __sub_427740_dword_4433A4 = *(t_sub_427740_dword_4433A4*)0x004433A4;
typedef int t_sub_427740_dword_4433A8[0x10000];
static t_sub_427740_dword_4433A8& __sub_427740_dword_4433A8 = *(t_sub_427740_dword_4433A8*)0x004433A8;
typedef char t_sub_427740_n3_0;
static t_sub_427740_n3_0& __sub_427740_n3_0 = *(t_sub_427740_n3_0*)0x004433CD;
typedef int t_sub_427740_n4_5;
static t_sub_427740_n4_5& __sub_427740_n4_5 = *(t_sub_427740_n4_5*)0x00443394;

static inline int __fwd_sub_427740_sub_413E60(void *a0, int a1, int a2) { return __sub_413E60((_WORD *)a0, a1, a2); }
#define sub_413E60 __fwd_sub_427740_sub_413E60
#define sub_414920 __sub_414920
#define sub_4149C0 __sub_4149C0
static inline void ** __fwd_sub_427740_sub_4244A0(void *a0, char a1) { return __sub_4244A0((void **)a0, a1); }
#define sub_4244A0 __fwd_sub_427740_sub_4244A0
static inline int __fwd_sub_427740_sub_4248D0(void *a0, void *a1, int a2) { return __sub_4248D0((unsigned __int8 **)a0, (_DWORD *)a1, a2); }
#define sub_4248D0 __fwd_sub_427740_sub_4248D0
static inline int * __fwd_sub_427740_sub_4256F0(void *a0, int a1, int a2, int a3) { return __sub_4256F0((int *)a0, a1, a2, a3); }
#define sub_4256F0 __fwd_sub_427740_sub_4256F0
#define sub_4259F0 __sub_4259F0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#define FILE FILE1

PROBE_DECL(__sub_427740)
__attribute__((force_align_arg_pointer)) int __sub_427740(unsigned __int16 *p_i, int Src)
{
  alignas(16) unsigned char __hexrays_frame[116];   // original frame, ebp-0x64..ebp+0x0
  _DWORD * &v83 = *(_DWORD * *)(__hexrays_frame + 0);
  void * &v84 = *(void * *)(__hexrays_frame + 4);
  int &v85 = *(int *)(__hexrays_frame + 8);
  unsigned int &v86 = *(unsigned int *)(__hexrays_frame + 12);
  unsigned int &v87 = *(unsigned int *)(__hexrays_frame + 12);
  int &v88 = *(int *)(__hexrays_frame + 16);
  int &v89 = *(int *)(__hexrays_frame + 16);
  int &Src_1 = *(int *)(__hexrays_frame + 20);
  int &v91 = *(int *)(__hexrays_frame + 24);
  int &v92 = *(int *)(__hexrays_frame + 28);
  void * &Block = *(void * *)(__hexrays_frame + 32);
  _DWORD * &v94 = *(_DWORD * *)(__hexrays_frame + 36);
  unsigned __int8 ** &v95 = *(unsigned __int8 ** *)(__hexrays_frame + 40);
  unsigned __int8 ** &v96 = *(unsigned __int8 ** *)(__hexrays_frame + 44);
  int &v97 = *(int *)(__hexrays_frame + 48);
  int &v98 = *(int *)(__hexrays_frame + 52);
  unsigned int &i_1 = *(unsigned int *)(__hexrays_frame + 56);
  int &ArgList_1 = *(int *)(__hexrays_frame + 60);
  int &v101 = *(int *)(__hexrays_frame + 64);
  unsigned int &i_4 = *(unsigned int *)(__hexrays_frame + 68);
  int &v103 = *(int *)(__hexrays_frame + 72);
  int &v104 = *(int *)(__hexrays_frame + 76);
  int &v105 = *(int *)(__hexrays_frame + 80);
  PROBE_HIT(__sub_427740);
  int i; // edx
  int v3; // ebx
  int i_2; // esi
  int n4; // ebp
  int *v6; // eax
  int *v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  char v11; // di
  char v12; // si
  char v13; // bp
  int v14; // edx
  int v15; // eax
  int v16; // edi
  int ArgList; // esi
  int v18; // ebp
  unsigned int v20; // edx
  int i_3; // esi
  int n4_1; // edi
  int n4_2; // ecx
  int v24; // eax
  int v25; // esi
  int v26; // ebx
  int v27; // ebp
  int v28; // edi
  int v29; // edx
  unsigned __int8 *v30; // ebx
  unsigned __int8 *v31; // ebp
  int v32; // edi
  int v33; // esi
  int v34; // edi
  int v35; // esi
  int v36; // edi
  int v37; // esi
  int v38; // edi
  int v39; // esi
  int v40; // edi
  int v41; // esi
  int v42; // edi
  int v43; // esi
  int v44; // edi
  int v45; // esi
  int v46; // edi
  int v47; // edx
  int v48; // esi
  int v49; // edi
  int v50; // esi
  _DWORD *v51; // ebx
  int v52; // edx
  int v53; // edx
  int v54; // eax
  _BYTE *v55; // esi
  int v56; // ecx
  int v57; // eax
  char v58; // al
  int v59; // ebx
  int v60; // edx
  int v61; // edx
  int v62; // eax
  _BYTE *v63; // esi
  int v64; // ecx
  int v65; // eax
  unsigned __int8 **v66; // ebx
  int v67; // edx
  int v68; // edx
  unsigned __int8 *v69; // eax
  unsigned __int8 *v70; // esi
  int v71; // ecx
  int v72; // eax
  unsigned __int8 **v73; // ebx
  int v74; // edx
  int v75; // edx
  unsigned __int8 *v76; // eax
  unsigned __int8 *v77; // esi
  int v78; // ecx
  int v79; // eax
  int n4_3; // eax
  int n4_4; // ebx
  void **v82; // ecx

  i = *p_i;
  v3 = p_i[1];
  i_1 = i;
  if ( __sub_427740_n4_5 > 0 )
  {
    i_2 = i;
    n4 = 0;
    do
    {
      v6 = (int *)__op_new(0x99D4D8u);
      if ( v6 )
        v7 = sub_4256F0(v6, i_2, v3, n4);
      else
        v7 = nullptr;
      *(&Block + n4++) = v7;
    }
    while ( n4 < __sub_427740_n4_5 );
  }
  v8 = 16 * (unsigned __int8)__sub_427740_byte_4433AD[0];
  v9 = 16 * (unsigned __int8)__sub_427740_byte_4433BD[0];
  v10 = 16 * (unsigned __int8)__sub_427740_n3_0;
  v11 = __sub_427740_byte_44339E[v8];
  v12 = __sub_427740_byte_44339E[v9];
  v13 = __sub_427740_byte_44339E[v10];
  v14 = (unsigned __int8)__sub_427740_byte_44339F[v9];
  v15 = (unsigned __int8)__sub_427740_byte_44339F[v10];
  v97 = (unsigned __int8)__sub_427740_byte_44339F[v8];
  v98 = v14;
  v16 = v11 & 8;
  v85 = v15;
  ArgList = v12 & 8;
  v18 = v13 & 8;
  sub_4149C0(ArgList);
  if ( v3 > 0 )
  {
    v91 = v18;
    v20 = 0;
    ArgList_1 = ArgList;
    i_3 = i_1;
    v101 = v16;
    n4_1 = __sub_427740_n4_5;
    do
    {
      if ( n4_1 > 0 )
      {
        v86 = v20;
        n4_2 = 0;
        v88 = v3;
        Src_1 = Src;
        do
        {
          ++n4_2;
          v24 = *(&v92 + n4_2);
          **(_WORD **)(v24 + 196) = *(_WORD *)(*(_DWORD *)(v24 + 196) - 2);
          *(_WORD *)(*(_DWORD *)(v24 + 196) + 2) = *(_WORD *)(*(_DWORD *)(v24 + 196) - 4);
          *(_WORD *)(*(_DWORD *)(v24 + 196) + 4) = *(_WORD *)(*(_DWORD *)(v24 + 196) - 6);
          *(_WORD *)(*(_DWORD *)(v24 + 196) + 6) = *(_WORD *)(*(_DWORD *)(v24 + 196) - 8);
          *(_WORD *)(*(_DWORD *)(v24 + 196) + 8) = *(_WORD *)(*(_DWORD *)(v24 + 196) - 10);
          *(_WORD *)(*(_DWORD *)(v24 + 196) + 10) = *(_WORD *)(*(_DWORD *)(v24 + 196) - 12);
          v25 = *(_DWORD *)(v24 + 192);
          v26 = *(_DWORD *)(v24 + 188);
          v27 = *(_DWORD *)(v24 + 184);
          v28 = *(_DWORD *)(v24 + 180);
          v29 = *(_DWORD *)(v24 + 176);
          *(_DWORD *)(v24 + 192) = v26;
          *(_DWORD *)(v24 + 188) = v27;
          *(_DWORD *)(v24 + 184) = v28;
          *(_DWORD *)(v24 + 180) = v29;
          *(_DWORD *)(v24 + 176) = v25;
          v25 += 8;
          *(_DWORD *)(v24 + 196) = v25;
          v29 += 8;
          *(_DWORD *)(v24 + 200) = v29;
          *(_DWORD *)(v24 + 204) = v28 + 8;
          *(_DWORD *)(v24 + 208) = v27 + 8;
          *(_DWORD *)(v24 + 212) = v26 + 8;
          *(_WORD *)(v25 - 8) = *(_WORD *)(v29 + 6);
          *(_WORD *)(*(_DWORD *)(v24 + 196) - 6) = *(_WORD *)(*(_DWORD *)(v24 + 200) + 4);
          *(_WORD *)(*(_DWORD *)(v24 + 196) - 4) = *(_WORD *)(*(_DWORD *)(v24 + 200) + 2);
          *(_WORD *)(*(_DWORD *)(v24 + 196) - 2) = **(_WORD **)(v24 + 200);
          v30 = *(unsigned __int8 **)(v24 + 204);
          v31 = *(unsigned __int8 **)(v24 + 212);
          *(_DWORD *)(v24 + 20) = 0;
          *(_DWORD *)(v24 + 24) = 0;
          *(_DWORD *)(v24 + 28) = 0;
          v32 = *(v30 - 3);
          *(_DWORD *)(v24 + 24) = v32;
          v33 = *(v30 - 1);
          *(_DWORD *)(v24 + 28) = v33;
          v34 = *(v31 - 3) + v32;
          *(_DWORD *)(v24 + 24) = v34;
          v35 = *(v31 - 1) + v33;
          *(_DWORD *)(v24 + 28) = v35;
          v36 = v30[1] + v34;
          *(_DWORD *)(v24 + 24) = v36;
          v37 = v30[3] + v35;
          *(_DWORD *)(v24 + 28) = v37;
          v38 = v31[1] + v36;
          *(_DWORD *)(v24 + 24) = v38;
          v39 = v31[3] + v37;
          *(_DWORD *)(v24 + 28) = v39;
          v40 = v30[5] + v38;
          *(_DWORD *)(v24 + 24) = v40;
          v41 = v30[7] + v39;
          *(_DWORD *)(v24 + 28) = v41;
          v42 = v31[5] + v40;
          *(_DWORD *)(v24 + 24) = v42;
          v43 = v31[7] + v41;
          *(_DWORD *)(v24 + 28) = v43;
          v44 = v30[9] + v42;
          *(_DWORD *)(v24 + 24) = v44;
          v45 = v30[11] + v43;
          *(_DWORD *)(v24 + 28) = v45;
          v46 = v31[9] + v44;
          v47 = *(_DWORD *)(v24 + 196);
          *(_DWORD *)(v24 + 24) = v46;
          v48 = v31[11] + v45;
          *(_DWORD *)(v24 + 28) = v48;
          v49 = *(unsigned __int8 *)(v47 - 7) + v46;
          *(_DWORD *)(v24 + 24) = v49;
          v50 = *(unsigned __int8 *)(v47 - 5) + v48;
          *(_DWORD *)(v24 + 28) = v50;
          *(_DWORD *)(v24 + 24) = *(unsigned __int8 *)(v47 - 3) + v49;
          *(_DWORD *)(v24 + 28) = *(unsigned __int8 *)(v47 - 1) + v50;
          n4_1 = __sub_427740_n4_5;
        }
        while ( n4_2 < __sub_427740_n4_5 );
        v20 = v86;
        v3 = v88;
        i_3 = i_1;
        Src = Src_1;
      }
      if ( i_3 > 0 )
      {
        v87 = v20;
        i_4 = 0;
        v89 = v3;
        do
        {
          v51 = Block;
          sub_4248D0((unsigned __int8 **)Block, nullptr, 0);
          v53 = sub_413E60(&v51[4 * v51[3] + 950], v52, v51[4]);
          v54 = v51[2];
          v55 = (_BYTE *)v51[49];
          v56 = (unsigned __int8)(v54 + *((_BYTE *)v51 + v53 + 1496));
          v103 = v56;
          *v55 = v56;
          *(_BYTE *)(v51[49] + 1) = abs32(v56 - v54);
          v51[v51[5] + 6] = v51[v51[5] + 6]
                          + *(unsigned __int8 *)(v51[49] + 1)
                          - *(unsigned __int8 *)(v51[49] - 7)
                          - (*(unsigned __int8 *)(v51[53] - 3)
                           - *(unsigned __int8 *)(v51[53] + 13)
                           + *(unsigned __int8 *)(v51[51] - 3)
                           - *(unsigned __int8 *)(v51[51] + 13));
          v57 = 4 * v51[3];
          v51[5] = v51[5] == 0;
          if ( LOWORD(v51[v57 + 950]) < 0x4000u )
            sub_4259F0((int)v51);
          v58 = v103;
          v51[49] += 2;
          v51[50] += 2;
          v51[51] += 2;
          v51[52] += 2;
          v51[53] += 2;
          v59 = (int)v94;
          *(_BYTE *)((unsigned __int8)__sub_427740_byte_44339D[0] + Src) = v58;
          sub_4248D0((unsigned __int8 **)v59, Block, 0);
          v61 = sub_413E60((_WORD *)(v59 + 16 * *(_DWORD *)(v59 + 12) + 3800), v60, *(_DWORD *)(v59 + 16));
          v62 = *(_DWORD *)(v59 + 8);
          v63 = *(_BYTE **)(v59 + 196);
          v64 = (unsigned __int8)(v62 + *(_BYTE *)(v61 + v59 + 1496));
          v104 = v64;
          *v63 = v64;
          *(_BYTE *)(*(_DWORD *)(v59 + 196) + 1) = abs32(v64 - v62);
          *(_DWORD *)(v59 + 4 * *(_DWORD *)(v59 + 20) + 24) = *(_DWORD *)(v59 + 4 * *(_DWORD *)(v59 + 20) + 24)
                                                            + *(unsigned __int8 *)(*(_DWORD *)(v59 + 196) + 1)
                                                            - *(unsigned __int8 *)(*(_DWORD *)(v59 + 196) - 7)
                                                            - (*(unsigned __int8 *)(*(_DWORD *)(v59 + 212) - 3)
                                                             - *(unsigned __int8 *)(*(_DWORD *)(v59 + 212) + 13)
                                                             + *(unsigned __int8 *)(*(_DWORD *)(v59 + 204) - 3)
                                                             - *(unsigned __int8 *)(*(_DWORD *)(v59 + 204) + 13));
          v65 = 16 * *(_DWORD *)(v59 + 12);
          *(_DWORD *)(v59 + 20) = *(_DWORD *)(v59 + 20) == 0;
          if ( *(unsigned __int16 *)(v65 + v59 + 3800) < 0x4000u )
            sub_4259F0(v59);
          *(_DWORD *)(v59 + 196) += 2;
          *(_DWORD *)(v59 + 200) += 2;
          *(_DWORD *)(v59 + 204) += 2;
          *(_DWORD *)(v59 + 208) += 2;
          *(_DWORD *)(v59 + 212) += 2;
          if ( v101 )
            v104 += v97 + *(unsigned __int8 *)((unsigned __int8)__sub_427740_byte_44339D[0] + Src);
          v66 = v95;
          v84 = Block;
          v83 = v94;
          *(_BYTE *)(Src + (unsigned __int8)__sub_427740_byte_4433AD[0]) = v104;
          sub_4248D0(v66, v83, (int)v84);
          v68 = sub_413E60(&v66[4 * (_DWORD)v66[3] + 950], v67, (int)v66[4]);
          v69 = v66[2];
          v70 = v66[49];
          v71 = (unsigned __int8)((_BYTE)v69 + *((_BYTE *)v66 + v68 + 1496));
          v105 = v71;
          *v70 = v71;
          v66[49][1] = abs32(v71 - (_DWORD)v69);
          v66[(_DWORD)v66[5] + 6] = &v66[(_DWORD)v66[5] + 6][v66[49][1]
                                                           - *(v66[49] - 7)
                                                           - (*(v66[53] - 3)
                                                            - v66[53][13])
                                                           - (*(v66[51] - 3)
                                                            - v66[51][13])];
          v72 = 4 * (_DWORD)v66[3];
          v66[5] = (unsigned __int8 *)(v66[5] == nullptr);
          if ( LOWORD(v66[v72 + 950]) < 0x4000u )
            sub_4259F0((int)v66);
          v66[49] += 2;
          v66[50] += 2;
          v66[51] += 2;
          v66[52] += 2;
          v66[53] += 2;
          if ( ArgList_1 )
            *(_BYTE *)((unsigned __int8)__sub_427740_byte_4433BD[0] + Src) = ((__sub_427740_dword_4433A0[4 * (unsigned __int8)__sub_427740_byte_4433BD[0]]
                                                                * *(unsigned __int8 *)((unsigned __int8)__sub_427740_byte_44339D[0]
                                                                                     + Src)
                                                                + __sub_427740_dword_4433A4[4 * (unsigned __int8)__sub_427740_byte_4433BD[0]]
                                                                * (unsigned int)*(unsigned __int8 *)((unsigned __int8)__sub_427740_byte_4433AD[0] + Src)
                                                                + 40) >> 7)
                                                              + v98
                                                              + v105;
          else
            *(_BYTE *)((unsigned __int8)__sub_427740_byte_4433BD[0] + Src) = v105;
          n4_1 = __sub_427740_n4_5;
          if ( __sub_427740_n4_5 >= 4 )
          {
            v73 = v96;
            sub_4248D0(v96, v95, (int)v94);
            v75 = sub_413E60(&v73[4 * (_DWORD)v73[3] + 950], v74, (int)v73[4]);
            v76 = v73[2];
            v77 = v73[49];
            v78 = (unsigned __int8)((_BYTE)v76 + *((_BYTE *)v73 + v75 + 1496));
            v92 = v78;
            *v77 = v78;
            v73[49][1] = abs32(v78 - (_DWORD)v76);
            v73[(_DWORD)v73[5] + 6] = &v73[(_DWORD)v73[5] + 6][v73[49][1]
                                                             - *(v73[49] - 7)
                                                             - (*(v73[53] - 3)
                                                              - v73[53][13])
                                                             - (*(v73[51] - 3)
                                                              - v73[51][13])];
            v79 = 4 * (_DWORD)v73[3];
            v73[5] = (unsigned __int8 *)(v73[5] == nullptr);
            if ( LOWORD(v73[v79 + 950]) < 0x4000u )
              sub_4259F0((int)v73);
            v73[49] += 2;
            v73[50] += 2;
            v73[51] += 2;
            v73[52] += 2;
            v73[53] += 2;
            if ( v91 )
              v92 += ((__sub_427740_dword_4433A4[4 * (unsigned __int8)__sub_427740_n3_0] * *(unsigned __int8 *)((unsigned __int8)__sub_427740_n3_0 + Src - 2)
                     + __sub_427740_dword_4433A0[4 * (unsigned __int8)__sub_427740_n3_0] * *(unsigned __int8 *)((unsigned __int8)__sub_427740_n3_0 + Src - 3)
                     + __sub_427740_dword_4433A8[4 * (unsigned __int8)__sub_427740_n3_0] * *(unsigned __int8 *)((unsigned __int8)__sub_427740_n3_0 + Src - 1)
                     + 64) >> 7)
                   + v85;
            *(_BYTE *)((unsigned __int8)__sub_427740_n3_0 + Src) = v92;
            n4_1 = __sub_427740_n4_5;
          }
          Src += n4_1;
          ++i_4;
        }
        while ( i_4 < i_1 );
        v20 = v87;
        v3 = v89;
        i_3 = i_1;
      }
      ++v20;
    }
    while ( v20 < v3 );
  }
  sub_414920();
  n4_3 = __sub_427740_n4_5;
  if ( __sub_427740_n4_5 > 0 )
  {
    n4_4 = 0;
    do
    {
      v82 = (void **)*(&Block + n4_4);
      if ( v82 )
      {
        sub_4244A0(v82, 1);
        n4_3 = __sub_427740_n4_5;
      }
      ++n4_4;
    }
    while ( n4_4 < n4_3 );
  }
  return n4_3;
}

#undef FILE
#undef sub_413E60
#undef sub_414920
#undef sub_4149C0
#undef sub_4244A0
#undef sub_4248D0
#undef sub_4256F0
#undef sub_4259F0
