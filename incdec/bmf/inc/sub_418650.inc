// sub_418650 @ 0x00418650 — __thiscall
// Extracted from BMF.c:22636-23555 by extract.py per incdec.md.

typedef char t_sub_418650_buf_0[0x10000];
static t_sub_418650_buf_0& __sub_418650_buf_0 = *(t_sub_418650_buf_0*)0x00443440;
#define buf_0 __sub_418650_buf_0
typedef char t_sub_418650_byte_445440[544];
static t_sub_418650_byte_445440& __sub_418650_byte_445440 = *(t_sub_418650_byte_445440*)0x00445440;
#define byte_445440 __sub_418650_byte_445440
typedef char t_sub_418650_byte_445700;
static t_sub_418650_byte_445700& __sub_418650_byte_445700 = *(t_sub_418650_byte_445700*)0x00445700;
#define byte_445700 __sub_418650_byte_445700
typedef int t_sub_418650_dword_44573C[0x10000];
static t_sub_418650_dword_44573C& __sub_418650_dword_44573C = *(t_sub_418650_dword_44573C*)0x0044573C;
#define dword_44573C __sub_418650_dword_44573C
typedef int t_sub_418650_n0x2000;
static t_sub_418650_n0x2000& __sub_418650_n0x2000 = *(t_sub_418650_n0x2000*)0x004456FC;
#define n0x2000 __sub_418650_n0x2000
typedef int t_sub_418650_n0x2000_0;
static t_sub_418650_n0x2000_0& __sub_418650_n0x2000_0 = *(t_sub_418650_n0x2000_0*)0x004456F8;
#define n0x2000_0 __sub_418650_n0x2000_0
typedef int t_sub_418650_n0x2000_1;
static t_sub_418650_n0x2000_1& __sub_418650_n0x2000_1 = *(t_sub_418650_n0x2000_1*)0x004456F4;
#define n0x2000_1 __sub_418650_n0x2000_1
typedef int t_sub_418650_n0x88;
static t_sub_418650_n0x88& __sub_418650_n0x88 = *(t_sub_418650_n0x88*)0x00445704;
#define n0x88 __sub_418650_n0x88
typedef int t_sub_418650_n15;
static t_sub_418650_n15& __sub_418650_n15 = *(t_sub_418650_n15*)0x00445748;
#define n15 __sub_418650_n15
typedef int t_sub_418650_n15_0;
static t_sub_418650_n15_0& __sub_418650_n15_0 = *(t_sub_418650_n15_0*)0x0044574C;
#define n15_0 __sub_418650_n15_0
typedef int t_sub_418650_n4_3;
static t_sub_418650_n4_3& __sub_418650_n4_3 = *(t_sub_418650_n4_3*)0x00445744;
#define n4_3 __sub_418650_n4_3
typedef int t_sub_418650_n4_4;
static t_sub_418650_n4_4& __sub_418650_n4_4 = *(t_sub_418650_n4_4*)0x00445740;
#define n4_4 __sub_418650_n4_4

#ifndef __PE_DECL___sub_412E60
#define __PE_DECL___sub_412E60
typedef __attribute__((fastcall)) int t_sub_412E60(_DWORD *a1);
static t_sub_412E60& __sub_412E60 = *(t_sub_412E60*)0x00412E60;
#endif
#define sub_412E60 __sub_412E60
#define sub_412280 __sub_412280
#define sub_412300 __sub_412300
#define sub_412340 __sub_412340
#define sub_412850 __sub_412850
#define sub_4148F0 __sub_4148F0
#define sub_416860 __sub_416860

PROBE_DECL(__sub_418650)
__attribute__((thiscall)) int __sub_418650(_DWORD *_this, int a2)
{
  PROBE_HIT(__sub_418650);
  unsigned __int16 *n15_9; // edi
  int n4_8; // ebp
  unsigned __int16 *v4; // esi
  int n4_7; // eax
  int n15_6; // edx
  int n15_7; // ecx
  int v8; // edx
  int v9; // ebx
  int v10; // edx
  _DWORD *this_2; // ebx
  int v12; // edx
  int v13; // eax
  __int16 v14; // cx
  int v15; // ecx
  unsigned __int16 *v16; // edx
  int n4_9; // eax
  int n15; // eax
  bool v19; // zf
  _WORD *n4_10; // edx
  int v21; // edx
  int v22; // ecx
  int v23; // eax
  int n4_11; // ebp
  int v25; // ebp
  int v26; // ebx
  int v27; // ebp
  _DWORD *this_3; // ebx
  int v29; // ebp
  int n15_10; // edi
  int v31; // ebp
  int n0xFFFF; // edx
  int v33; // eax
  int n0xFFFF_1; // ebp
  int n53248; // ecx
  int v36; // eax
  int n4_12; // edx
  _BYTE *v38; // eax
  unsigned __int8 *v39; // ecx
  int v40; // ebp
  int n15_11; // esi
  int n8; // edx
  int n15_12; // edi
  BOOL v44; // eax
  int n4_22; // ecx
  int v46; // edx
  int n15_14; // eax
  int n15_18; // ebp
  int v49; // esi
  int v50; // ebx
  int v51; // eax
  int n4_13; // eax
  int v53; // edi
  int v54; // ecx
  int v55; // edx
  int v56; // edi
  int v57; // esi
  _WORD *v58; // edi
  int *v59; // esi
  int v60; // ecx
  int v61; // esi
  int n15_13; // edi
  __int16 n4_14; // ax
  unsigned int n4_16; // edx
  unsigned int n4_15; // ebp
  int v66; // esi
  int v67; // edx
  int n15_15; // esi
  _BYTE *n15_16; // ebp
  char v70; // dl
  char v71; // cl
  char v72; // di
  char v73; // al
  char v74; // dl
  char v75; // cl
  _BYTE *v76; // ebp
  int n15_17; // ebp
  int n4_17; // edi
  int v80; // edx
  int v81; // ebp
  unsigned __int16 *n4_3; // esi
  int v83; // eax
  signed int v84; // eax
  int v85; // edx
  int n4; // ebp
  int n256_2; // ecx
  int n15_1; // eax
  int n256_1; // edx
  unsigned __int16 *v90; // eax
  char v91; // cl
  int n15_23; // edi
  int n4_19; // eax
  int n4_20; // ebp
  unsigned __int16 *v95; // esi
  int n4_5; // edi
  unsigned __int16 *v97; // edx
  int n4_6; // ebp
  int n15_5; // eax
  unsigned __int16 *v100; // esi
  int this_4; // edi
  int v102; // ebp
  int v103; // eax
  int v104; // esi
  int v105; // edx
  unsigned __int16 *v106; // edi
  int v107; // ebp
  int v108; // eax
  int v109; // esi
  unsigned __int16 *v110; // esi
  int v111; // edx
  int v112; // ebp
  int v113; // edx
  int v114; // ebp
  int v115; // edx
  int v116; // ebp
  int v117; // edx
  int v118; // ebp
  int v119; // edx
  int v120; // ebp
  unsigned __int16 *v121; // ebp
  int v122; // edx
  int v123; // eax
  int v124; // edx
  int v125; // edi
  int v126; // eax
  int v127; // ebp
  BOOL v128; // eax
  int n32; // eax
  int n15_25; // ebp
  int n4_21; // edi
  int v132; // eax
  int v133; // ecx
  _DWORD **v134; // eax
  int v135; // eax
  unsigned int v136; // edx
  unsigned int v137; // ecx
  unsigned int v138; // ebx
  unsigned int v139; // eax
  unsigned int v140; // ebp
  int n256; // ecx
  _QWORD *v142; // eax
  int v143; // edx
  int n4_18; // ebp
  int n15_19; // edi
  __int16 v146; // cx
  int n15_20; // ebp
  int v148; // edi
  int v149; // ebp
  int v150; // ebx
  int v151; // eax
  int v152; // ebp
  int v153; // ebx
  unsigned __int16 v154; // cx
  int v155; // edx
  int n15_21; // ebx
  char *v157; // ebp
  int v158; // ebx
  int v159; // eax
  __int16 v160; // cx
  int v161; // edi
  unsigned __int16 v162; // cx
  signed int v163; // eax
  int v164; // edx
  int n4_2; // ebp
  int n15_22; // eax
  int n256_4; // edx
  int n256_5; // ecx
  __int16 n15_4; // ax
  unsigned __int16 *v170; // ecx
  _WORD *v171; // ebp
  unsigned int v172; // ecx
  unsigned int v173; // eax
  unsigned __int16 v174; // bx
  unsigned int v175; // eax
  unsigned int v176; // edx
  unsigned int v177; // esi
  int n256_3; // ecx
  int n15_2; // eax
  int n15_8; // [esp+0h] [ebp-94h] BYREF
  int n4_1; // [esp+4h] [ebp-90h]
  int n4_4; // [esp+8h] [ebp-8Ch]
  int n15_3; // [esp+Ch] [ebp-88h]
  unsigned __int16 *v184; // [esp+10h] [ebp-84h]
  _DWORD *this_1; // [esp+14h] [ebp-80h]
  int v186; // [esp+18h] [ebp-7Ch]
  int v187; // [esp+1Ch] [ebp-78h]
  int v188; // [esp+20h] [ebp-74h]
  int v189; // [esp+24h] [ebp-70h]
  int v190; // [esp+28h] [ebp-6Ch]
  int v191; // [esp+2Ch] [ebp-68h]
  int v192; // [esp+30h] [ebp-64h]
  int v193; // [esp+34h] [ebp-60h]
  int v194; // [esp+38h] [ebp-5Ch]
  int v195; // [esp+3Ch] [ebp-58h]
  int v196; // [esp+40h] [ebp-54h]
  int v197; // [esp+44h] [ebp-50h]
  int v198; // [esp+48h] [ebp-4Ch]
  int v199; // [esp+4Ch] [ebp-48h]
  int v200; // [esp+50h] [ebp-44h]
  int v201; // [esp+54h] [ebp-40h]
  int v202; // [esp+58h] [ebp-3Ch]
  int v203; // [esp+5Ch] [ebp-38h]
  int v204; // [esp+60h] [ebp-34h]
  int v205; // [esp+64h] [ebp-30h]
  int v206; // [esp+68h] [ebp-2Ch]
  int v207; // [esp+6Ch] [ebp-28h]
  int v208; // [esp+70h] [ebp-24h]
  int v209; // [esp+74h] [ebp-20h]
  int v210; // [esp+78h] [ebp-1Ch]
  int v211; // [esp+7Ch] [ebp-18h]
  int n15_24; // [esp+80h] [ebp-14h]

  n15_9 = (unsigned __int16 *)*(_this + 20);
  n4_8 = *n15_9;
  v4 = (unsigned __int16 *)*(_this + 19);
  n4_7 = *(v4 - 4);
  n15_6 = n15_9[4];
  this_1 = _this;
  n15_7 = *(n15_9 - 4);
  n15_8 = n4_8;
  ::n4_4 = n4_8;
  n4_1 = n4_7;
  ::n4_3 = n4_7;
  n15_3 = n15_6;
  ::n15 = n15_6;
  v8 = *((unsigned __int8 *)n15_9 + 3) + 4 * (n15_6 == n15_7);
  v9 = *((unsigned __int8 *)n15_9 + 11);
  n4_4 = n15_7;
  n15_0 = n15_7;
  v10 = 2 * *((unsigned __int8 *)v4 - 6) + 8 * v9 + v8;
  this_2 = this_1;
  v12 = 32 * *((unsigned __int8 *)v4 - 4) + 16 * *((unsigned __int8 *)v4 - 2) + v10;
  if ( n4_8 == n4_7 )
  {
    if ( n15_3 == n15_8 )
    {
      v14 = *((_WORD *)this_1 + n4_8 + 3029720);
      if ( n4_8 == n4_4 )
        v13 = (unsigned __int16)(v14 - *(v4 - 8));
      else
        v13 = (unsigned __int16)(v14 - n4_4);
    }
    else
    {
      v13 = (unsigned __int16)(*((_WORD *)this_1 + n4_8 + 3029720) - n15_3);
    }
  }
  else
  {
    v13 = (unsigned __int16)(*((_WORD *)this_1 + n4_8 + 3029720) - n4_1);
  }
  this_1[1514858] = &this_1[4 * v13 + 269674];
  v15 = *((unsigned __int8 *)this_2 + v12 + 1078244);
  this_2[9] = v15;
  v16 = (unsigned __int16 *)&this_2[0x10000 * v15 + 531818 + v13];
  this_2[1514859] = v16;
  n4_9 = *v16;
  if ( n4_9 == n15_8 )
  {
    n15 = 15;
  }
  else if ( n4_9 == n4_1 )
  {
    n15 = 30;
  }
  else if ( n4_9 == n15_3 )
  {
    n15 = 45;
  }
  else
  {
    v19 = n4_9 == n4_4;
    n15 = 60;
    if ( !v19 )
      n15 = 0;
  }
  n4_10 = (_WORD *)v16[1];
  if ( n4_10 == (_WORD *)n15_8 )
  {
    n15 += 75;
  }
  else if ( n4_10 == (_WORD *)n4_1 )
  {
    n15 += 150;
  }
  else if ( n4_10 == (_WORD *)n15_3 )
  {
    n15 += 225;
  }
  else if ( n4_10 == (_WORD *)n4_4 )
  {
    n15 += 300;
  }
  v21 = this_2[22];
  n15_3 = (int)n15_9;
  v22 = *((unsigned __int8 *)this_2 + v15 + n15 + 1078308);
  v23 = this_2[21];
  this_2[10] = v22;
  n4_11 = *((unsigned __int8 *)n15_9 + 2);
  v184 = v4;
  this_1 = this_2;
  n4_4 = n4_11;
  v25 = this_2[23];
  v26 = *((unsigned __int8 *)v4 - 5);
  v186 = v25;
  v27 = 8 * *((unsigned __int8 *)v4 - 12) + 4 * *((unsigned __int8 *)v4 - 9) + v26 + 2 * *((unsigned __int8 *)v4 - 10);
  this_3 = this_1;
  v29 = ((unsigned __int8)(*(_BYTE *)(v186 + 2) & *(_BYTE *)(v21 + 2) & n4_4 & *(_BYTE *)(v23 + 2)) << 9)
      + ((unsigned __int8)(*(_BYTE *)(v186 + 3) & *(_BYTE *)(v21 + 3) & *(_BYTE *)(v23 + 3) & *((_BYTE *)n15_9 + 3)) << 8)
      + (v22 << 10)
      + v27;
  n15_10 = n15_3;
  v31 = ((*((_BYTE *)this_1 + 1078695) == 0) << 7)
      + ((*((_BYTE *)this_1 + 1078694) == 0) << 6)
      + 32 * (*((_BYTE *)this_1 + 1078693) == 0)
      + 16 * (*((_BYTE *)this_1 + 1078692) == 0)
      + v29;
  n0xFFFF = *((unsigned __int16 *)this_1 + v31 + 3037912);
  if ( n0xFFFF == 0xFFFF )
  {
    *((_WORD *)this_1 + v31 + 3037912) = this_1[5];
    n15_10 = this_3[20];
    v4 = (unsigned __int16 *)this_3[19];
    ++this_3[5];
    n0xFFFF = *((unsigned __int16 *)this_3 + v31 + 3037912);
    n4_4 = *(unsigned __int8 *)(n15_10 + 2);
  }
  v33 = *((unsigned __int8 *)v4 - 1) + 4 * *(unsigned __int8 *)(n15_10 + 13) + 2 * n4_4 + 8 * n0xFFFF;
  n0xFFFF_1 = *((unsigned __int16 *)this_3 + v33 + 3230424);
  if ( n0xFFFF_1 == 0xFFFF )
  {
    *((_WORD *)this_3 + v33 + 3230424) = this_3[6]++;
    n0xFFFF_1 = *((unsigned __int16 *)this_3 + v33 + 3230424);
  }
  if ( (int)this_3[4] < 32 )
  {
    n53248 = this_3[7];
    n4_1 = 16 * n0xFFFF_1 + (n4_1 & 0xF);
    v36 = (int)this_3 + 2 * n4_1;
    n0xFFFF_1 = *(unsigned __int16 *)(v36 + 6678448);
    if ( n0xFFFF_1 == 0xFFFF )
    {
      n4_12 = n4_1;
      if ( n53248 > 53248 )
        n4_12 = n4_1 | 0xF;
      v36 = (int)this_3 + 2 * n4_12;
      n0xFFFF_1 = *(unsigned __int16 *)(v36 + 6678448);
    }
    if ( n0xFFFF_1 >= n53248 )
    {
      *(_WORD *)(v36 + 6678448) = n53248;
      ++this_3[7];
      n0xFFFF_1 = *(unsigned __int16 *)(v36 + 6678448);
    }
  }
  if ( (*(_BYTE *)(this_3[19] - 5) & *(_BYTE *)(this_3[19] - 6)) != 0 )
  {
    v38 = (_BYTE *)this_3[20];
    v39 = (unsigned __int8 *)this_3[21];
    if ( ((unsigned __int8)(v39[19] & v39[11] & v39[3] & v38[27] & v38[19] & v38[11] & v38[3] & v38[2] & *(v38 - 5))
        & v39[27]) != 0 )
    {
      v40 = v39[2];
      n15_11 = 1;
      if ( *this_3 - a2 <= 1 )
      {
        n8 = 8;
      }
      else
      {
        n4_1 = *this_3 - a2;
        this_1 = this_3;
        while ( 1 )
        {
          n8 = 8 * n15_11;
          if ( (v38[8 * n15_11 + 19] & v38[8 * n15_11 + 18]) == 0 )
            break;
          v40 = (unsigned __int8)(v39[n8 + 2] & v40);
          if ( ++n15_11 >= n4_1 )
          {
            this_3 = this_1;
            n8 = 8 * n15_11;
            goto LABEL_42;
          }
        }
        this_3 = this_1;
      }
LABEL_42:
      n15_12 = *(unsigned __int8 *)(this_3[269671] + n15_11);
      v44 = sub_412850(
              (unsigned __int16 *)&this_3[12 * n15_12
                                        + 269089
                                        + 6 * (unsigned __int8)(v39[n8 + 27] & v39[n8 + 19])
                                        + 3 * v40]
            + 3 * *(unsigned __int8 *)(this_3[269672] + n15_8)
            + 1,
              (unsigned __int16 *)this_3 + 538176);
      n4_22 = ::n4_4;
      v46 = this_3[269672];
      this_3[8] = v44;
      *(_BYTE *)(v46 + n4_22) = v44;
      n15_14 = this_3[8];
      if ( n15_14 )
      {
        n15_18 = n15_11;
      }
      else
      {
        n15_18 = 0;
        if ( n15_11 == 1 )
          goto LABEL_57;
        n15_3 = n15_11;
        n15_8 = n15_12;
        this_1 = this_3;
        n15_18 = 0;
        v49 = 1 << n15_12;
        v50 = 0;
        do
        {
          if ( (v49 | v50) < n15_3 )
          {
            v51 = *((unsigned __int16 *)&this_1[24 * (v50 == 0) + 269473 + 24 * (n15_12 == n15_8)] + 3 * n15_12 + 1);
            n4_4 = (int)&this_1[24 * (v50 == 0) + 269473 + 24 * (n15_12 == n15_8)] + 6 * n15_12 + 2;
            n4_1 = sub_412340(
                     v51,
                     *((unsigned __int16 *)&this_1[24 * (v50 == 0) + 269474 + 24 * (n15_12 == n15_8)] + 3 * n15_12));
            if ( *((unsigned __int16 *)&this_1[24 * (v50 == 0) + 269474 + 24 * (n15_12 == n15_8)] + 3 * n15_12 + 1) < (unsigned int)n0x88 )
              sub_4148F0((_WORD *)n4_4);
            n4_13 = n4_1;
            *(_WORD *)(n4_4 + 2 * n4_1) += 8;
            if ( n4_13 )
              n15_18 |= v49;
            v50 |= n15_18 & v49;
          }
          --n15_12;
          v49 >>= 1;
        }
        while ( v49 );
        this_3 = this_1;
      }
      if ( n15_18 )
        *(_WORD *)(this_3[19] + 8 * n15_18 - 8) = *(_WORD *)(this_3[19] - 8);
      n15_14 = this_3[8];
LABEL_57:
      if ( n15_18 > n15_14 )
      {
        v53 = this_3[21];
        this_3[20] = this_3[20] + 8 * n15_18 - 8 * n15_14;
        v54 = this_3[22];
        v55 = v53 + 8 * n15_18;
        v56 = this_3[23];
        this_3[21] = v55 - 8 * n15_14;
        this_3[22] = v54 + 8 * n15_18 - 8 * n15_14;
        v57 = this_3[19];
        this_3[23] = v56 + 8 * n15_18 - 8 * n15_14;
        *(_DWORD *)(v57 + 4) = 16843009;
        *(_DWORD *)this_3[19] = 16843009;
        v58 = (_WORD *)this_3[1514859];
        LOWORD(v55) = ::n4_4;
        LOWORD(v54) = *v58;
        n4_1 = ::n4_4;
        v58[1] = v54;
        *(_WORD *)this_3[19] = v55;
        *(_WORD *)this_3[1514859] = v55;
        v59 = (int *)this_3[19];
        v60 = v59[1];
        n15_3 = *v59;
        v61 = (int)(v59 + 2);
        this_3[19] = v61;
        if ( n15_18 - n15_14 != 1 )
        {
          n4_4 = (n15_18 - n15_14 - 1) / 2;
          if ( n4_4 )
          {
            n15_13 = n15_3;
            n15_8 = n15_14;
            n4_14 = n4_1;
            n4_16 = 0;
            n15_24 = n15_18;
            n4_15 = n4_4;
            do
            {
              *(_WORD *)(this_3[1514859] + 2) = n4_14;
              *(_DWORD *)this_3[19] = n15_13;
              *(_DWORD *)(this_3[19] + 4) = v60;
              v66 = this_3[1514859];
              this_3[19] += 8;
              *(_WORD *)(v66 + 2) = n4_14;
              *(_DWORD *)this_3[19] = n15_13;
              *(_DWORD *)(this_3[19] + 4) = v60;
              v61 = this_3[19] + 8;
              this_3[19] = v61;
              ++n4_16;
            }
            while ( n4_16 < n4_15 );
            n15_14 = n15_8;
            n15_18 = n15_24;
            v67 = 2 * n4_16 + 1;
          }
          else
          {
            v67 = 1;
          }
          if ( n15_18 - n15_14 - 1 > (unsigned int)(v67 - 1) )
          {
            n15_15 = n15_3;
            *(_WORD *)(this_3[1514859] + 2) = n4_1;
            *(_DWORD *)this_3[19] = n15_15;
            *(_DWORD *)(this_3[19] + 4) = v60;
            v61 = this_3[19] + 8;
            this_3[19] = v61;
          }
        }
        n15_24 = n15_18;
        n15_16 = (_BYTE *)this_3[20];
        v70 = *(n15_16 - 22);
        v71 = *(n15_16 - 14);
        v72 = n15_16[18];
        v73 = n15_16[26];
        n15_8 = (int)n15_16;
        v74 = v71 + v70;
        v75 = n15_16[34];
        v76 = (_BYTE *)this_3[21];
        *((_BYTE *)this_3 + 1078692) = v73 + v72 + v74 + v75 - 5;
        *((_BYTE *)this_3 + 1078693) = v76[26]
                                     + v76[18]
                                     + v76[10]
                                     + v76[2]
                                     + *(v76 - 6)
                                     + *(v76 - 14)
                                     + *(v76 - 22)
                                     + v76[34]
                                     - 8;
        n15_17 = n15_8;
        *((_BYTE *)this_3 + 1078694) = *(_BYTE *)(v61 - 29) + *(_BYTE *)(v61 - 21) - 2;
        n4_17 = n4_1;
        *((_BYTE *)this_3 + 1078695) = *(_BYTE *)(v61 - 38)
                                     + *(_BYTE *)(v61 - 46)
                                     + *(_BYTE *)(v61 - 54)
                                     + *(_BYTE *)(v61 - 30)
                                     - 4;
        *(_BYTE *)(v61 - 2) = n4_17 == *(unsigned __int16 *)(n15_17 + 8);
        n15_18 = n15_24;
        *(_BYTE *)(this_3[19] - 1) = n4_17 == *(unsigned __int16 *)(this_3[20] + 16);
        n15_14 = this_3[8];
      }
      if ( n15_14 )
        return n15_18;
      goto LABEL_86;
    }
  }
  v80 = (int)&this_3[4 * this_3[10] + 24];
  v184 = (unsigned __int16 *)v80;
  v81 = 4 * n0xFFFF_1;
  n4_3 = (unsigned __int16 *)&this_3[v81 + 776];
  v83 = HIWORD(this_3[v81 + 778]);
  if ( HIWORD(this_3[v81 + 778]) )
  {
    if ( v83 == 1 )
    {
      v142 = (_QWORD *)v80;
      v143 = *(unsigned __int8 *)(v80 + 15);
      n4_18 = v143 * LOWORD(this_3[v81 + 777]);
      n15_19 = v143 * n4_3[3];
      n4_1 = v143 * *n4_3;
      v146 = v143 * n4_3[1];
      n4_4 = n4_18;
      n15_20 = v143 * n4_3[4];
      n15_8 = n15_19;
      n15_3 = n15_20;
      *(_QWORD *)n4_3 = *v142;
      *((_QWORD *)n4_3 + 1) = v142[1];
      v148 = n4_3[5];
      v149 = *n4_3;
      *((_BYTE *)n4_3 + 14) *= 8;
      this_1 = this_3;
      v150 = 21 * n4_3[1];
      n4_1 += (21 * v149 + v148 - 1) / v148;
      *n4_3 = n4_1;
      v151 = (v150 + v148 - 1) / v148;
      v152 = 21 * n4_3[2];
      v153 = n4_3[3];
      v154 = v151 + v146;
      n4_3[1] = v154;
      v155 = 21 * v153;
      n15_21 = n15_8;
      v157 = (char *)((v152 + v148 - 1) / v148 + n4_4);
      n4_3[2] = (unsigned __int16)v157;
      v158 = (v155 + v148 - 1) / v148 + n15_21;
      v159 = 21 * n4_3[4];
      n4_3[3] = v158;
      v160 = v158 + (_WORD)v157 + v154;
      this_3 = this_1;
      v161 = (v159 + v148 - 1) / v148 + n15_3;
      n4_3[4] = v161;
      v162 = n4_1 + v161 + v160;
      v83 = v162;
      n4_3[5] = v162;
    }
    n0x2000 = v83;
    v84 = sub_412280();
    v85 = *n4_3;
    if ( v85 <= v84 )
    {
      v85 += n4_3[1];
      if ( v85 <= v84 )
      {
        v85 += n4_3[2];
        if ( v85 <= v84 )
        {
          v85 += n4_3[3];
          if ( v85 <= v84 )
          {
            v85 += n4_3[4];
            n4 = 4;
          }
          else
          {
            n4 = 3;
          }
        }
        else
        {
          n4 = 2;
        }
      }
      else
      {
        n4 = 1;
      }
    }
    else
    {
      n4 = 0;
    }
    n256_2 = n4_3[6];
    n0x2000_0 = v85;
    n15_1 = *((unsigned __int8 *)n4_3 + 15);
    n0x2000_1 = v85 - n4_3[n4];
    n256_1 = n4_3[5];
    if ( n256_1 > n256_2 && (n4_3[n4] + n15_1 + 8 < n256_1 || n4_3[5] > 0x4000u) )
    {
      v136 = n4_3[2];
      n15_8 = n256_2;
      v137 = n4_3[1];
      this_1 = this_3;
      v138 = *n4_3;
      n4_1 = n4;
      n4_4 = n15_1;
      LOWORD(v138) = v138 - (v138 >> 1);
      *n4_3 = v138;
      LOWORD(v137) = v137 - (v137 >> 1);
      n4_3[1] = v137;
      LOWORD(v136) = v136 - (v136 >> 1);
      v139 = n4_3[3];
      n4_3[2] = v136;
      LOWORD(v139) = v139 - (v139 >> 1);
      v140 = n4_3[4];
      n4_3[3] = v139;
      LOWORD(v140) = v140 - (v140 >> 1);
      n4_3[4] = v140;
      LOWORD(v137) = v139 + v136 + v137;
      n15_1 = n4_4;
      LOWORD(v140) = v138 + v140;
      this_3 = this_1;
      n256_1 = (unsigned __int16)(v140 + v137);
      n256 = n15_8;
      n4 = n4_1;
      n4_3[5] = n256_1;
      if ( n256 < 256 && !*((_BYTE *)n4_3 + 14) )
      {
        n256 = 256;
        n4_3[6] = 256;
      }
      if ( n256_1 > n256 )
      {
        if ( n15_1 < 15 )
          LOWORD(n15_1) = 15;
        *((_BYTE *)n4_3 + 15) = n15_1;
      }
    }
    n4_3[5] = n15_1 + n256_1;
    n4_3[n4] += n15_1;
    sub_412300();
    this_3[8] = n4;
    if ( *((_BYTE *)n4_3 + 14) )
    {
      --*((_BYTE *)n4_3 + 14);
      v90 = v184;
      ++v184[5];
      ++v90[n4];
      n4 = this_3[8];
    }
  }
  else
  {
    n0x2000 = *(unsigned __int16 *)(v80 + 10);
    v163 = sub_412280();
    v164 = *v184;
    if ( v164 <= v163 )
    {
      v164 += v184[1];
      if ( v164 <= v163 )
      {
        v164 += v184[2];
        if ( v164 <= v163 )
        {
          v164 += v184[3];
          if ( v164 <= v163 )
          {
            v164 += v184[4];
            n4_2 = 4;
          }
          else
          {
            n4_2 = 3;
          }
        }
        else
        {
          n4_2 = 2;
        }
      }
      else
      {
        n4_2 = 1;
      }
    }
    else
    {
      n4_2 = 0;
    }
    n15_22 = *((unsigned __int8 *)v184 + 15);
    n0x2000_0 = v164;
    n0x2000_1 = v164 - v184[n4_2];
    n256_4 = v184[5];
    n256_5 = v184[6];
    n15_3 = n15_22;
    if ( n256_4 > n256_5 && (v184[n4_2] + n15_3 + 8 < n256_4 || n256_4 > 0x4000) )
    {
      n15_8 = n256_5;
      this_1 = this_3;
      n4_1 = (int)n4_3;
      n4_4 = n4_2;
      v171 = v184;
      v172 = v184[1];
      v173 = v184[2];
      v174 = *v184 - (*v184 >> 1);
      *v184 = v174;
      LOWORD(v172) = v172 - (v172 >> 1);
      v171[1] = v172;
      v175 = v173 - (v173 >> 1);
      v176 = (unsigned __int16)v171[3];
      v171[2] = v175;
      LOWORD(v176) = v176 - (v176 >> 1);
      v177 = (unsigned __int16)v171[4];
      v171[3] = v176;
      LOWORD(v177) = v177 - (v177 >> 1);
      v171[4] = v177;
      LOWORD(v177) = v174 + v177;
      this_3 = this_1;
      n256_4 = (unsigned __int16)(v177 + v176 + v175 + v172);
      n256_3 = n15_8;
      n4_3 = (unsigned __int16 *)n4_1;
      v171[5] = n256_4;
      n4_2 = n4_4;
      if ( n256_3 < 256 && !*((_BYTE *)v184 + 14) )
      {
        n256_3 = 256;
        v184[6] = 256;
      }
      if ( n256_4 > n256_3 )
      {
        n15_2 = n15_3;
        if ( n15_3 < 15 )
          n15_2 = 15;
        n15_3 = n15_2;
        *((_BYTE *)v184 + 15) = n15_2;
      }
    }
    n15_4 = n15_3;
    v170 = v184;
    v184[5] = n15_3 + n256_4;
    v170[n4_2] += n15_4;
    sub_412300();
    this_3[8] = n4_2;
    n4_3[5] = n4_3[n4_2]++ != 0;
    n4 = this_3[8];
  }
  if ( n4 )
  {
    *(_WORD *)this_3[19] = dword_44573C[n4];
    return 1;
  }
  n15_18 = 0;
LABEL_86:
  v91 = byte_445700;
  n15_23 = ::n15;
  n4_19 = ::n4_4;
  n15_24 = n15_18;
  n4_20 = ::n4_3;
  buf_0[n15_0] = byte_445700;
  v95 = (unsigned __int16 *)this_3[1514859];
  buf_0[n15_23] = v91;
  buf_0[n4_20] = v91;
  buf_0[n4_19] = v91;
  byte_445440[0] = v91;
  this_3[269554] = 0;
  n4_5 = v95[1];
  n15_8 = *v95;
  v97 = (unsigned __int16 *)this_3[1514858];
  n4_6 = *v97;
  n15_5 = v97[1];
  v100 = (unsigned __int16 *)v97[2];
  n4_1 = n4_5;
  this_4 = v97[3];
  n4_4 = n4_6;
  v102 = v97[4];
  n15_3 = n15_5;
  v103 = v97[5];
  v184 = v100;
  v104 = v97[6];
  v105 = v97[7];
  this_1 = (_DWORD *)this_4;
  v106 = (unsigned __int16 *)this_3[20];
  v186 = v102;
  v107 = v106[8];
  v187 = v103;
  v108 = this_3[19];
  v188 = v104;
  v109 = *(unsigned __int16 *)(v108 - 16);
  v189 = v105;
  v190 = v109;
  v110 = (unsigned __int16 *)this_3[21];
  v111 = v110[4];
  v191 = v107;
  v112 = *v110;
  v192 = v111;
  v113 = *(v106 - 8);
  v193 = v112;
  v114 = *(v110 - 4);
  v194 = v113;
  v115 = *(unsigned __int16 *)(v108 - 24);
  v195 = v114;
  v116 = v106[12];
  v196 = v115;
  v117 = v106[16];
  v197 = v116;
  v118 = *(unsigned __int16 *)(v108 - 32);
  v198 = v117;
  v119 = *(v106 - 12);
  v199 = v118;
  v120 = v110[8];
  v200 = v119;
  v201 = v120;
  v121 = (unsigned __int16 *)this_3[22];
  v202 = *v121;
  v203 = *(v110 - 8);
  v122 = *(unsigned __int16 *)(v108 - 40);
  v123 = *(unsigned __int16 *)(v108 - 56);
  v204 = v122;
  v205 = v121[4];
  v124 = v106[20];
  v125 = v106[28];
  v206 = v124;
  v207 = *(unsigned __int16 *)this_3[23];
  v208 = v123;
  v209 = *(v121 - 4);
  v126 = v110[12];
  this_3[11] = 0;
  v210 = v125;
  v211 = v126;
  do
  {
    v127 = sub_416860(this_3, &n15_8);
    if ( v127 >= 0 )
    {
      v128 = sub_412850(
               (unsigned __int16 *)this_3 + 3 * this_3[13] + 525888,
               (unsigned __int16 *)this_3 + 3 * this_3[12] + 525840);
      *(_WORD *)this_3[19] = v127;
      if ( v128 )
        return n15_24 + 1;
      buf_0[v127] = byte_445700;
    }
    n32 = this_3[11] + 1;
    this_3[11] = n32;
  }
  while ( n32 < 32 );
  n15_25 = n15_24;
  n4_21 = ::n4_4;
  v132 = this_3[269552];
  this_3[269554] = this_3[269553] + 24 * ::n4_3;
  v133 = v132 + 24 * n4_21;
  v134 = (_DWORD **)this_3[269558];
  this_3[269555] = v133;
  while ( 1 )
  {
    if ( !(*v134)[1] )
      goto LABEL_95;
    v135 = sub_412E60(*v134);
    *(_WORD *)this_3[19] = v135;
    if ( v135 >= 0 )
      return n15_25 + 1;
    v134 = (_DWORD **)this_3[269558];
LABEL_95:
    this_3[269558] = ++v134;
  }
}

#undef buf_0
#undef byte_445440
#undef byte_445700
#undef dword_44573C
#undef n0x2000
#undef n0x2000_0
#undef n0x2000_1
#undef n0x88
#undef n15
#undef n15_0
#undef n4_3
#undef n4_4
#undef sub_412280
#undef sub_412300
#undef sub_412340
#undef sub_412850
#undef sub_412E60
#undef sub_4148F0
#undef sub_416860
