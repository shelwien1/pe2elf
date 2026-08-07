// sub_424D90 @ 0x00424D90 — __cdecl
// Extracted from BMF.c:30485-30963 by extract.py per incdec.md.

typedef char t_sub_424D90_byte_44339D[0x10000];
static t_sub_424D90_byte_44339D& __sub_424D90_byte_44339D = *(t_sub_424D90_byte_44339D*)0x0044339D;
typedef char t_sub_424D90_byte_44339E[0x10000];
static t_sub_424D90_byte_44339E& __sub_424D90_byte_44339E = *(t_sub_424D90_byte_44339E*)0x0044339E;
typedef char t_sub_424D90_byte_44339F[0x10000];
static t_sub_424D90_byte_44339F& __sub_424D90_byte_44339F = *(t_sub_424D90_byte_44339F*)0x0044339F;
typedef char t_sub_424D90_byte_4433AD[16];
static t_sub_424D90_byte_4433AD& __sub_424D90_byte_4433AD = *(t_sub_424D90_byte_4433AD*)0x004433AD;
typedef char t_sub_424D90_byte_4433BD[15];
static t_sub_424D90_byte_4433BD& __sub_424D90_byte_4433BD = *(t_sub_424D90_byte_4433BD*)0x004433BD;
typedef int t_sub_424D90_dword_4433A0[0x10000];
static t_sub_424D90_dword_4433A0& __sub_424D90_dword_4433A0 = *(t_sub_424D90_dword_4433A0*)0x004433A0;
typedef int t_sub_424D90_dword_4433A4[0x10000];
static t_sub_424D90_dword_4433A4& __sub_424D90_dword_4433A4 = *(t_sub_424D90_dword_4433A4*)0x004433A4;
typedef int t_sub_424D90_dword_4433A8[0x10000];
static t_sub_424D90_dword_4433A8& __sub_424D90_dword_4433A8 = *(t_sub_424D90_dword_4433A8*)0x004433A8;
typedef char t_sub_424D90_n3_0;
static t_sub_424D90_n3_0& __sub_424D90_n3_0 = *(t_sub_424D90_n3_0*)0x004433CD;
typedef int t_sub_424D90_n4_5;
static t_sub_424D90_n4_5& __sub_424D90_n4_5 = *(t_sub_424D90_n4_5*)0x00443394;

#ifndef __PE_DECL___sub_414F60
#define __PE_DECL___sub_414F60
typedef char * t_sub_414F60();
static t_sub_414F60& __sub_414F60 = *(t_sub_414F60*)0x00414F60;
#endif
#define sub_414F60 __sub_414F60
static inline int __fwd_sub_424D90_sub_4135A0(void *a0, int a1, int a2, int a3) { return __sub_4135A0((unsigned __int16 *)a0, a1, a2, a3); }
#define sub_4135A0 __fwd_sub_424D90_sub_4135A0
#define sub_414CE0 __sub_414CE0
static inline void ** __fwd_sub_424D90_sub_4244A0(void *a0, char a1) { return __sub_4244A0((void **)a0, a1); }
#define sub_4244A0 __fwd_sub_424D90_sub_4244A0
static inline int __fwd_sub_424D90_sub_4248D0(void *a0, void *a1, int a2) { return __sub_4248D0((unsigned __int8 **)a0, (_DWORD *)a1, a2); }
#define sub_4248D0 __fwd_sub_424D90_sub_4248D0
static inline int * __fwd_sub_424D90_sub_4256F0(void *a0, int a1, int a2, int a3) { return __sub_4256F0((int *)a0, a1, a2, a3); }
#define sub_4256F0 __fwd_sub_424D90_sub_4256F0
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

PROBE_DECL(__sub_424D90)
int __sub_424D90(unsigned __int16 *p_i, int a2)
{
  PROBE_HIT(__sub_424D90);
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
  int v15; // edi
  int v16; // esi
  int v17; // ebp
  unsigned int v19; // edx
  int i_3; // esi
  int n4_1; // edi
  int n4_2; // ecx
  int v23; // eax
  int v24; // esi
  int v25; // ebx
  int v26; // ebp
  int v27; // edi
  int v28; // edx
  unsigned __int8 *v29; // ebx
  unsigned __int8 *v30; // ebp
  int v31; // edi
  int v32; // esi
  int v33; // edi
  int v34; // esi
  int v35; // edi
  int v36; // esi
  int v37; // edi
  int v38; // esi
  int v39; // edi
  int v40; // esi
  int v41; // edi
  int v42; // esi
  int v43; // edi
  int v44; // esi
  int v45; // edi
  int v46; // edx
  int v47; // esi
  int v48; // edi
  int v49; // esi
  unsigned __int8 *v50; // esi
  int n5_9; // eax
  int n5_7; // ebx
  unsigned __int8 v53; // dl
  int n5_2; // edi
  int n5_1; // edx
  int v56; // eax
  int n16; // ecx
  int v58; // ebx
  int v59; // edx
  unsigned __int8 v60; // cl
  unsigned __int8 **v61; // ebx
  char v62; // di
  int v63; // ecx
  int v64; // esi
  int v65; // edi
  int n16_1; // esi
  int n5_3; // eax
  __int64 v68; // rax
  int v69; // ebx
  unsigned __int8 **v70; // esi
  char v71; // di
  int n5_4; // edx
  int v73; // edi
  int v74; // eax
  int n16_2; // ecx
  __int64 v76; // rax
  int v77; // ebx
  int n3; // ebx
  unsigned __int8 v79; // al
  unsigned __int8 **v80; // esi
  char v81; // cl
  int n5_5; // edx
  char v83; // di
  int v84; // ecx
  int n16_3; // edi
  __int64 v86; // rax
  int n4_3; // eax
  int n4_4; // ebx
  void **v89; // ecx
  char v90; // [esp+0h] [ebp-80h]
  unsigned int v91; // [esp+4h] [ebp-7Ch]
  unsigned int v92; // [esp+4h] [ebp-7Ch]
  int v93; // [esp+8h] [ebp-78h]
  int v94; // [esp+8h] [ebp-78h]
  int v95; // [esp+Ch] [ebp-74h]
  int v96; // [esp+10h] [ebp-70h]
  char v97; // [esp+14h] [ebp-6Ch]
  int v98; // [esp+18h] [ebp-68h]
  int v99; // [esp+1Ch] [ebp-64h]
  int n5_8; // [esp+20h] [ebp-60h]
  void *Block; // [esp+24h] [ebp-5Ch]
  unsigned __int8 **v102; // [esp+28h] [ebp-58h]
  unsigned __int8 **v103; // [esp+2Ch] [ebp-54h]
  unsigned __int8 **v104; // [esp+30h] [ebp-50h]
  int v105; // [esp+34h] [ebp-4Ch]
  int v106; // [esp+38h] [ebp-48h]
  unsigned int i_1; // [esp+3Ch] [ebp-44h]
  int v108; // [esp+40h] [ebp-40h]
  int v109; // [esp+44h] [ebp-3Ch]
  unsigned int i_4; // [esp+48h] [ebp-38h]
  int v111; // [esp+4Ch] [ebp-34h]
  int v112; // [esp+50h] [ebp-30h]
  int v113; // [esp+54h] [ebp-2Ch]
  int v114; // [esp+58h] [ebp-28h]
  int v115; // [esp+5Ch] [ebp-24h]
  int n5_6; // [esp+60h] [ebp-20h]
  int v117; // [esp+64h] [ebp-1Ch]
  int v118; // [esp+68h] [ebp-18h]
  int n5; // [esp+6Ch] [ebp-14h]

  i = *p_i;
  v3 = p_i[1];
  i_1 = i;
  if ( __sub_424D90_n4_5 > 0 )
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
    while ( n4 < __sub_424D90_n4_5 );
  }
  v8 = 16 * (unsigned __int8)__sub_424D90_byte_4433AD[0];
  v9 = 16 * (unsigned __int8)__sub_424D90_byte_4433BD[0];
  v10 = 16 * (unsigned __int8)__sub_424D90_n3_0;
  v11 = __sub_424D90_byte_44339E[v8];
  v12 = __sub_424D90_byte_44339E[v9];
  v13 = __sub_424D90_byte_44339E[v10];
  v14 = (unsigned __int8)__sub_424D90_byte_44339F[v9];
  LOBYTE(v10) = __sub_424D90_byte_44339F[v10];
  v105 = (unsigned __int8)__sub_424D90_byte_44339F[v8];
  v106 = v14;
  v15 = v11 & 8;
  v90 = v10;
  v16 = v12 & 8;
  v17 = v13 & 8;
  sub_414F60();
  if ( v3 > 0 )
  {
    v96 = v17;
    v19 = 0;
    v108 = v16;
    i_3 = i_1;
    v109 = v15;
    n4_1 = __sub_424D90_n4_5;
    do
    {
      if ( n4_1 > 0 )
      {
        v91 = v19;
        n4_2 = 0;
        v93 = v3;
        v95 = a2;
        do
        {
          ++n4_2;
          v23 = *(&n5_8 + n4_2);
          **(_WORD **)(v23 + 196) = *(_WORD *)(*(_DWORD *)(v23 + 196) - 2);
          *(_WORD *)(*(_DWORD *)(v23 + 196) + 2) = *(_WORD *)(*(_DWORD *)(v23 + 196) - 4);
          *(_WORD *)(*(_DWORD *)(v23 + 196) + 4) = *(_WORD *)(*(_DWORD *)(v23 + 196) - 6);
          *(_WORD *)(*(_DWORD *)(v23 + 196) + 6) = *(_WORD *)(*(_DWORD *)(v23 + 196) - 8);
          *(_WORD *)(*(_DWORD *)(v23 + 196) + 8) = *(_WORD *)(*(_DWORD *)(v23 + 196) - 10);
          *(_WORD *)(*(_DWORD *)(v23 + 196) + 10) = *(_WORD *)(*(_DWORD *)(v23 + 196) - 12);
          v24 = *(_DWORD *)(v23 + 192);
          v25 = *(_DWORD *)(v23 + 188);
          v26 = *(_DWORD *)(v23 + 184);
          v27 = *(_DWORD *)(v23 + 180);
          v28 = *(_DWORD *)(v23 + 176);
          *(_DWORD *)(v23 + 192) = v25;
          *(_DWORD *)(v23 + 188) = v26;
          *(_DWORD *)(v23 + 184) = v27;
          *(_DWORD *)(v23 + 180) = v28;
          *(_DWORD *)(v23 + 176) = v24;
          v24 += 8;
          *(_DWORD *)(v23 + 196) = v24;
          v28 += 8;
          *(_DWORD *)(v23 + 200) = v28;
          *(_DWORD *)(v23 + 204) = v27 + 8;
          *(_DWORD *)(v23 + 208) = v26 + 8;
          *(_DWORD *)(v23 + 212) = v25 + 8;
          *(_WORD *)(v24 - 8) = *(_WORD *)(v28 + 6);
          *(_WORD *)(*(_DWORD *)(v23 + 196) - 6) = *(_WORD *)(*(_DWORD *)(v23 + 200) + 4);
          *(_WORD *)(*(_DWORD *)(v23 + 196) - 4) = *(_WORD *)(*(_DWORD *)(v23 + 200) + 2);
          *(_WORD *)(*(_DWORD *)(v23 + 196) - 2) = **(_WORD **)(v23 + 200);
          v29 = *(unsigned __int8 **)(v23 + 204);
          v30 = *(unsigned __int8 **)(v23 + 212);
          *(_DWORD *)(v23 + 20) = 0;
          *(_DWORD *)(v23 + 24) = 0;
          *(_DWORD *)(v23 + 28) = 0;
          v31 = *(v29 - 3);
          *(_DWORD *)(v23 + 24) = v31;
          v32 = *(v29 - 1);
          *(_DWORD *)(v23 + 28) = v32;
          v33 = *(v30 - 3) + v31;
          *(_DWORD *)(v23 + 24) = v33;
          v34 = *(v30 - 1) + v32;
          *(_DWORD *)(v23 + 28) = v34;
          v35 = v29[1] + v33;
          *(_DWORD *)(v23 + 24) = v35;
          v36 = v29[3] + v34;
          *(_DWORD *)(v23 + 28) = v36;
          v37 = v30[1] + v35;
          *(_DWORD *)(v23 + 24) = v37;
          v38 = v30[3] + v36;
          *(_DWORD *)(v23 + 28) = v38;
          v39 = v29[5] + v37;
          *(_DWORD *)(v23 + 24) = v39;
          v40 = v29[7] + v38;
          *(_DWORD *)(v23 + 28) = v40;
          v41 = v30[5] + v39;
          *(_DWORD *)(v23 + 24) = v41;
          v42 = v30[7] + v40;
          *(_DWORD *)(v23 + 28) = v42;
          v43 = v29[9] + v41;
          *(_DWORD *)(v23 + 24) = v43;
          v44 = v29[11] + v42;
          *(_DWORD *)(v23 + 28) = v44;
          v45 = v30[9] + v43;
          v46 = *(_DWORD *)(v23 + 196);
          *(_DWORD *)(v23 + 24) = v45;
          v47 = v30[11] + v44;
          *(_DWORD *)(v23 + 28) = v47;
          v48 = *(unsigned __int8 *)(v46 - 7) + v45;
          *(_DWORD *)(v23 + 24) = v48;
          v49 = *(unsigned __int8 *)(v46 - 5) + v47;
          *(_DWORD *)(v23 + 28) = v49;
          *(_DWORD *)(v23 + 24) = *(unsigned __int8 *)(v46 - 3) + v48;
          *(_DWORD *)(v23 + 28) = *(unsigned __int8 *)(v46 - 1) + v49;
          n4_1 = __sub_424D90_n4_5;
        }
        while ( n4_2 < __sub_424D90_n4_5 );
        v19 = v91;
        v3 = v93;
        i_3 = i_1;
        a2 = v95;
      }
      if ( i_3 > 0 )
      {
        v92 = v19;
        i_4 = 0;
        v94 = v3;
        do
        {
          v50 = (unsigned __int8 *)Block;
          n5_9 = *(unsigned __int8 *)(a2 + (unsigned __int8)__sub_424D90_byte_44339D[0]);
          v114 = (unsigned __int8)__sub_424D90_byte_44339D[0];
          n5_6 = n5_9;
          sub_4248D0((unsigned __int8 **)Block, nullptr, 0);
          n5_7 = n5_6;
          v53 = v50[8];
          v112 = (unsigned __int8)(n5_6 - v53);
          n5_2 = v50[v112 + 984];
          n5_1 = (unsigned __int8)(v50[n5_2 + 1496] + v53);
          v56 = (unsigned __int8)(n5_1 + *(_BYTE *)(a2 + v114) - n5_6);
          n16 = *(unsigned __int8 *)(a2 + v114) - v56;
          if ( n16 < -16 || n16 > 16 )
          {
            n5_2 = v50[v112 + 1240];
          }
          else
          {
            n5_6 = n5_1;
            *(_BYTE *)(a2 + v114) = v56;
            n5_7 = n5_1;
          }
          sub_4135A0((unsigned __int16 *)&v50[16 * *((_DWORD *)v50 + 3) + 3800], n5_1, *((_DWORD *)v50 + 4), n5_2);
          v58 = n5_7 - *((_DWORD *)v50 + 2);
          **((_BYTE **)v50 + 49) = n5_6;
          *(_BYTE *)(*((_DWORD *)v50 + 49) + 1) = abs32(v58);
          *(_DWORD *)&v50[4 * *((_DWORD *)v50 + 5) + 24] = *(_DWORD *)&v50[4 * *((_DWORD *)v50 + 5) + 24]
                                                         + *(unsigned __int8 *)(*((_DWORD *)v50 + 49) + 1)
                                                         - *(unsigned __int8 *)(*((_DWORD *)v50 + 49) - 7)
                                                         - (*(unsigned __int8 *)(*((_DWORD *)v50 + 53) - 3)
                                                          - *(unsigned __int8 *)(*((_DWORD *)v50 + 53) + 13)
                                                          + *(unsigned __int8 *)(*((_DWORD *)v50 + 51) - 3)
                                                          - *(unsigned __int8 *)(*((_DWORD *)v50 + 51) + 13));
          v59 = 16 * *((_DWORD *)v50 + 3);
          *((_DWORD *)v50 + 5) = *((_DWORD *)v50 + 5) == 0;
          if ( *(unsigned __int16 *)&v50[v59 + 3800] < 0x4000u )
            sub_4259F0((int)v50);
          *((_DWORD *)v50 + 49) += 2;
          *((_DWORD *)v50 + 50) += 2;
          *((_DWORD *)v50 + 51) += 2;
          *((_DWORD *)v50 + 52) += 2;
          *((_DWORD *)v50 + 53) += 2;
          v60 = *(_BYTE *)(a2 + (unsigned __int8)__sub_424D90_byte_4433AD[0]);
          v113 = (unsigned __int8)__sub_424D90_byte_4433AD[0];
          if ( v109 )
            v60 = v60 - v105 - *(_BYTE *)((unsigned __int8)__sub_424D90_byte_44339D[0] + a2);
          v61 = v102;
          v118 = v60;
          sub_4248D0(v102, Block, 0);
          v62 = *((_BYTE *)v61 + 8);
          v63 = (unsigned __int8)(v118 - v62);
          n5 = *((unsigned __int8 *)v61 + v63 + 984);
          v64 = *(unsigned __int8 *)(a2 + v113);
          v65 = (unsigned __int8)(*((_BYTE *)v61 + n5 + 1496) + v62);
          v111 = (unsigned __int8)(v65 + *(_BYTE *)(a2 + v113) - v118);
          n16_1 = v64 - v111;
          n5_3 = n5;
          if ( n16_1 < -16 || n16_1 > 16 )
          {
            n5_3 = *((unsigned __int8 *)v61 + v63 + 1240);
          }
          else
          {
            *(_BYTE *)(a2 + v113) = v111;
            v118 = v65;
          }
          sub_4135A0((unsigned __int16 *)&v61[4 * (_DWORD)v61[3] + 950], 16 * (_DWORD)v61[3], (int)v61[4], n5_3);
          v68 = v118 - (int)v61[2];
          *v61[49] = v118;
          v61[49][1] = (BYTE4(v68) ^ v68) - BYTE4(v68);
          v61[(_DWORD)v61[5] + 6] = &v61[(_DWORD)v61[5] + 6][v61[49][1]
                                                           - *(v61[49] - 7)
                                                           - (*(v61[53] - 3)
                                                            - v61[53][13])
                                                           - (*(v61[51] - 3)
                                                            - v61[51][13])];
          LODWORD(v68) = 16 * (_DWORD)v61[3];
          v61[5] = (unsigned __int8 *)(v61[5] == nullptr);
          if ( *(unsigned __int16 *)((char *)v61 + v68 + 3800) < 0x4000u )
            sub_4259F0((int)v61);
          v61[49] += 2;
          v61[50] += 2;
          v61[51] += 2;
          v61[52] += 2;
          v61[53] += 2;
          v69 = *(unsigned __int8 *)((unsigned __int8)__sub_424D90_byte_4433BD[0] + a2);
          v117 = (unsigned __int8)__sub_424D90_byte_4433BD[0];
          if ( v108 )
            v69 = (unsigned __int8)(v69
                                  - v106
                                  - ((__sub_424D90_dword_4433A0[4 * (unsigned __int8)__sub_424D90_byte_4433BD[0]]
                                    * *(unsigned __int8 *)((unsigned __int8)__sub_424D90_byte_44339D[0] + a2)
                                    + __sub_424D90_dword_4433A4[4 * (unsigned __int8)__sub_424D90_byte_4433BD[0]]
                                    * (unsigned int)*(unsigned __int8 *)((unsigned __int8)__sub_424D90_byte_4433AD[0] + a2)
                                    + 40) >> 7));
          v70 = v103;
          sub_4248D0(v103, (_DWORD *)v102, (int)Block);
          v71 = *((_BYTE *)v70 + 8);
          v115 = (unsigned __int8)(v69 - v71);
          n5_4 = *((unsigned __int8 *)v70 + v115 + 984);
          v73 = (unsigned __int8)(*((_BYTE *)v70 + n5_4 + 1496) + v71);
          v74 = (unsigned __int8)(v73 + *(_BYTE *)(v117 + a2) - v69);
          n16_2 = *(unsigned __int8 *)(v117 + a2) - v74;
          if ( n16_2 < -16 || n16_2 > 16 )
          {
            n5_4 = *((unsigned __int8 *)v70 + v115 + 1240);
          }
          else
          {
            v69 = v73;
            *(_BYTE *)(v117 + a2) = v74;
          }
          sub_4135A0((unsigned __int16 *)&v70[4 * (_DWORD)v70[3] + 950], n5_4, (int)v70[4], n5_4);
          v76 = v69 - (int)v70[2];
          *v70[49] = v69;
          v70[49][1] = (BYTE4(v76) ^ v76) - BYTE4(v76);
          v70[(_DWORD)v70[5] + 6] = &v70[(_DWORD)v70[5] + 6][v70[49][1]
                                                           - *(v70[49] - 7)
                                                           - (*(v70[53] - 3)
                                                            - v70[53][13])
                                                           - (*(v70[51] - 3)
                                                            - v70[51][13])];
          v77 = 4 * (_DWORD)v70[3];
          v70[5] = (unsigned __int8 *)(v70[5] == nullptr);
          if ( LOWORD(v70[v77 + 950]) < 0x4000u )
            sub_4259F0((int)v70);
          v70[49] += 2;
          v70[50] += 2;
          v70[51] += 2;
          v70[52] += 2;
          v70[53] += 2;
          n4_1 = __sub_424D90_n4_5;
          if ( __sub_424D90_n4_5 >= 4 )
          {
            n3 = (unsigned __int8)__sub_424D90_n3_0;
            if ( v96 )
              v79 = *(_BYTE *)((unsigned __int8)__sub_424D90_n3_0 + a2)
                  - v90
                  - ((__sub_424D90_dword_4433A4[4 * (unsigned __int8)__sub_424D90_n3_0] * *(unsigned __int8 *)((unsigned __int8)__sub_424D90_n3_0 + a2 - 2)
                    + __sub_424D90_dword_4433A0[4 * (unsigned __int8)__sub_424D90_n3_0] * *(unsigned __int8 *)((unsigned __int8)__sub_424D90_n3_0 + a2 - 3)
                    + __sub_424D90_dword_4433A8[4 * (unsigned __int8)__sub_424D90_n3_0] * *(unsigned __int8 *)((unsigned __int8)__sub_424D90_n3_0 + a2 - 1)
                    + 64) >> 7);
            else
              v79 = *(_BYTE *)((unsigned __int8)__sub_424D90_n3_0 + a2);
            v80 = v104;
            v99 = v79;
            sub_4248D0(v104, (_DWORD *)v103, (int)v102);
            v81 = *((_BYTE *)v80 + 8);
            n5_5 = *((unsigned __int8 *)v80 + (unsigned __int8)(v99 - v81) + 984);
            v98 = (unsigned __int8)(v99 - v81);
            v83 = *((_BYTE *)v80 + n5_5 + 1496);
            n5_8 = n5_5;
            v84 = (unsigned __int8)(v83 + v81);
            n16_3 = *(unsigned __int8 *)(n3 + a2) - (unsigned __int8)(v84 + *(_BYTE *)(n3 + a2) - v99);
            v97 = v84 + *(_BYTE *)(n3 + a2) - v99;
            if ( n16_3 < -16 || n16_3 > 16 )
            {
              n5_5 = *((unsigned __int8 *)v80 + v98 + 1240);
            }
            else
            {
              v99 = v84;
              *(_BYTE *)(n3 + a2) = v97;
            }
            sub_4135A0((unsigned __int16 *)&v80[4 * (_DWORD)v80[3] + 950], n5_5, (int)v80[4], n5_5);
            v86 = v99 - (int)v80[2];
            *v80[49] = v99;
            v80[49][1] = (BYTE4(v86) ^ v86) - BYTE4(v86);
            v80[(_DWORD)v80[5] + 6] = &v80[(_DWORD)v80[5] + 6][v80[49][1]
                                                             - *(v80[49] - 7)
                                                             - (*(v80[53] - 3)
                                                              - v80[53][13])
                                                             - (*(v80[51] - 3)
                                                              - v80[51][13])];
            LODWORD(v86) = 16 * (_DWORD)v80[3];
            v80[5] = (unsigned __int8 *)(v80[5] == nullptr);
            if ( *(unsigned __int16 *)((char *)v80 + v86 + 3800) < 0x4000u )
              sub_4259F0((int)v80);
            v80[49] += 2;
            v80[50] += 2;
            v80[51] += 2;
            v80[52] += 2;
            v80[53] += 2;
            n4_1 = __sub_424D90_n4_5;
          }
          a2 += n4_1;
          ++i_4;
        }
        while ( i_4 < i_1 );
        v19 = v92;
        v3 = v94;
        i_3 = i_1;
      }
      ++v19;
    }
    while ( v19 < v3 );
  }
  sub_414CE0();
  n4_3 = __sub_424D90_n4_5;
  if ( __sub_424D90_n4_5 > 0 )
  {
    n4_4 = 0;
    do
    {
      v89 = (void **)*(&Block + n4_4);
      if ( v89 )
      {
        sub_4244A0(v89, 1);
        n4_3 = __sub_424D90_n4_5;
      }
      ++n4_4;
    }
    while ( n4_4 < n4_3 );
  }
  return n4_3;
}

#undef FILE
#undef sub_4135A0
#undef sub_414CE0
#undef sub_414F60
#undef sub_4244A0
#undef sub_4248D0
#undef sub_4256F0
#undef sub_4259F0
