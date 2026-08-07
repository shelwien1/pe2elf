// sub_4159E0 @ 0x004159E0 — __thiscall
// Extracted from BMF.c:20063-20971 by extract.py per incdec.md.

typedef char t_sub_4159E0_buf_0[0x10000];
static t_sub_4159E0_buf_0& __sub_4159E0_buf_0 = *(t_sub_4159E0_buf_0*)0x00443440;
typedef unsigned char t_sub_4159E0_byte_445440[544];
static t_sub_4159E0_byte_445440& __sub_4159E0_byte_445440 = *(t_sub_4159E0_byte_445440*)0x00445440;
typedef char t_sub_4159E0_byte_445700;
static t_sub_4159E0_byte_445700& __sub_4159E0_byte_445700 = *(t_sub_4159E0_byte_445700*)0x00445700;
typedef int t_sub_4159E0_n0x2000;
static t_sub_4159E0_n0x2000& __sub_4159E0_n0x2000 = *(t_sub_4159E0_n0x2000*)0x004456FC;
typedef int t_sub_4159E0_n0x2000_0;
static t_sub_4159E0_n0x2000_0& __sub_4159E0_n0x2000_0 = *(t_sub_4159E0_n0x2000_0*)0x004456F8;
typedef int t_sub_4159E0_n0x2000_1;
static t_sub_4159E0_n0x2000_1& __sub_4159E0_n0x2000_1 = *(t_sub_4159E0_n0x2000_1*)0x004456F4;
typedef int t_sub_4159E0_n0x88;
static t_sub_4159E0_n0x88& __sub_4159E0_n0x88 = *(t_sub_4159E0_n0x88*)0x00445704;
typedef int t_sub_4159E0_n15;
static t_sub_4159E0_n15& __sub_4159E0_n15 = *(t_sub_4159E0_n15*)0x00445748;
typedef int t_sub_4159E0_n15_0;
static t_sub_4159E0_n15_0& __sub_4159E0_n15_0 = *(t_sub_4159E0_n15_0*)0x0044574C;
typedef int t_sub_4159E0_n4_3;
static t_sub_4159E0_n4_3& __sub_4159E0_n4_3 = *(t_sub_4159E0_n4_3*)0x00445744;
typedef int t_sub_4159E0_n4_4;
static t_sub_4159E0_n4_4& __sub_4159E0_n4_4 = *(t_sub_4159E0_n4_4*)0x00445740;

#define sub_411E90 __sub_411E90
#define sub_411FD0 __sub_411FD0
static inline int __fwd_sub_4159E0_sub_412490(void *a0, void *a1, int a2) { return __sub_412490((unsigned __int16 *)a0, (unsigned __int16 *)a1, a2); }
#define sub_412490 __fwd_sub_4159E0_sub_412490
static inline int __fwd_sub_4159E0_sub_412B10(void *a0, int a1) { return __sub_412B10((unsigned int *)a0, a1); }
#define sub_412B10 __fwd_sub_4159E0_sub_412B10
static inline int __fwd_sub_4159E0_sub_4148F0(void *a0) { return __sub_4148F0((_WORD *)a0); }
#define sub_4148F0 __fwd_sub_4159E0_sub_4148F0
static inline int __fwd_sub_4159E0_sub_416860(void *a0, void *a1) { return __sub_416860((int *)a0, (_DWORD *)a1); }
#define sub_416860 __fwd_sub_4159E0_sub_416860

PROBE_DECL(__sub_4159E0)
__attribute__((thiscall)) int __sub_4159E0(int *_this, int a2)
{
  alignas(16) unsigned char __hexrays_frame[164];   // original frame, ebp-0x94..ebp+0x0
  int &p_n15 = *(int *)(__hexrays_frame + 0);
  int &n2_1 = *(int *)(__hexrays_frame + 4);
  _WORD * &n2_4 = *(_WORD * *)(__hexrays_frame + 8);
  int &n15_20 = *(int *)(__hexrays_frame + 12);
  int &n15_31 = *(int *)(__hexrays_frame + 16);
  int &n15_2 = *(int *)(__hexrays_frame + 20);
  int &n15_4 = *(int *)(__hexrays_frame + 24);
  int * &this_1 = *(int * *)(__hexrays_frame + 28);
  int &n15_3 = *(int *)(__hexrays_frame + 32);
  unsigned __int16 * &v185 = *(unsigned __int16 * *)(__hexrays_frame + 36);
  int &n15_7 = *(int *)(__hexrays_frame + 40);
  int &v187 = *(int *)(__hexrays_frame + 44);
  int &v188 = *(int *)(__hexrays_frame + 48);
  int &v189 = *(int *)(__hexrays_frame + 52);
  int &v190 = *(int *)(__hexrays_frame + 56);
  int &v191 = *(int *)(__hexrays_frame + 60);
  int &v192 = *(int *)(__hexrays_frame + 64);
  int &v193 = *(int *)(__hexrays_frame + 68);
  int &v194 = *(int *)(__hexrays_frame + 72);
  int &v195 = *(int *)(__hexrays_frame + 76);
  int &v196 = *(int *)(__hexrays_frame + 80);
  int &v197 = *(int *)(__hexrays_frame + 84);
  int &v198 = *(int *)(__hexrays_frame + 88);
  int &v199 = *(int *)(__hexrays_frame + 92);
  int &v200 = *(int *)(__hexrays_frame + 96);
  int &v201 = *(int *)(__hexrays_frame + 100);
  int &v202 = *(int *)(__hexrays_frame + 104);
  int &v203 = *(int *)(__hexrays_frame + 108);
  int &v204 = *(int *)(__hexrays_frame + 112);
  int &v205 = *(int *)(__hexrays_frame + 116);
  int &v206 = *(int *)(__hexrays_frame + 120);
  int &v207 = *(int *)(__hexrays_frame + 124);
  int &n15_14 = *(int *)(__hexrays_frame + 128);
  PROBE_HIT(__sub_4159E0);
  unsigned __int16 *n2_7; // edi
  int n4; // ebp
  _WORD *n2_8; // esi
  int n4_1; // eax
  int __sub_4159E0_n15; // ebx
  int n15_1; // ecx
  int v8; // edx
  int v9; // ebx
  int v10; // edx
  bool v11; // zf
  int *this_2; // ebp
  int v13; // eax
  __int16 v14; // cx
  int v15; // ecx
  int *v16; // edx
  int n15_6; // eax
  int n15_5; // eax
  int n15_8; // edx
  int v20; // edx
  int v21; // ecx
  int v22; // eax
  int p_n15_1; // ebx
  char v24; // di
  int n15_30; // ebx
  int v26; // ebp
  int v27; // ebx
  int *this_3; // ebp
  int v29; // ebx
  int n0xFFFF; // edx
  int n2_9; // edi
  int v32; // eax
  int n0xFFFF_1; // edx
  int n53248; // ebx
  int v35; // ecx
  char *v36; // eax
  unsigned __int16 *v37; // eax
  int v38; // ecx
  int v39; // ebx
  _BYTE *p_n15_3; // ecx
  unsigned __int8 *v41; // esi
  int v42; // eax
  int p_n15_2; // ebx
  int n15_42; // ebx
  int n8; // edx
  int v46; // edi
  int n15_32; // eax
  int n15_12; // ebx
  int n15_9; // edx
  int v50; // esi
  unsigned __int16 *v51; // edi
  int v52; // edi
  int v53; // esi
  int p_n15_4; // ecx
  unsigned int v55; // edx
  int n2_10; // ecx
  unsigned int v57; // edi
  __int16 n15_10; // ax
  int v59; // ebx
  _WORD *n2_11; // ebx
  int v61; // edx
  _WORD *n2_12; // ecx
  int v63; // esi
  char v64; // dl
  char v65; // cl
  char v66; // di
  char v67; // al
  char v68; // dl
  _BYTE *v69; // edi
  _WORD *n2_13; // edx
  int n15_11; // edi
  int n15_13; // eax
  int n4_2; // ecx
  int v74; // edx
  int n15_33; // ebp
  int n15_35; // edi
  int n15_34; // esi
  int n15_15; // ebx
  unsigned __int16 *n2_14; // ecx
  int n2_15; // eax
  int v82; // eax
  int n15_36; // ecx
  int *n2_3; // esi
  int __sub_4159E0_n0x2000; // edx
  int n15_16; // eax
  int v87; // eax
  int n2; // ebx
  int p_n15_5; // ecx
  int p_n15_7; // edx
  int n15_17; // eax
  int n15_38; // eax
  char v93; // al
  int n15_22; // esi
  int __sub_4159E0_n4_3; // edx
  int __sub_4159E0_n4_4; // ecx
  unsigned __int16 *v97; // esi
  unsigned __int16 *v98; // ecx
  int p_n15_11; // eax
  int n2_5; // edx
  _WORD *n2_6; // edi
  int n15_41; // esi
  int n15_23; // eax
  int n15_24; // edx
  int n15_25; // edi
  int *this_4; // eax
  int n15_26; // esi
  unsigned __int16 *v108; // ecx
  int v109; // edx
  int n15_27; // edi
  unsigned __int16 *v111; // eax
  int v112; // esi
  unsigned __int16 *v113; // edi
  int v114; // ecx
  int v115; // esi
  int v116; // ecx
  int v117; // esi
  int v118; // ecx
  int v119; // esi
  int v120; // ecx
  int v121; // esi
  int v122; // ecx
  int v123; // esi
  unsigned __int16 *v124; // esi
  int v125; // ecx
  int v126; // edx
  int v127; // ecx
  int v128; // eax
  int v129; // ebx
  BOOL n15_28; // edi
  int n32; // eax
  int n15_29; // ebx
  int n4_5; // edi
  int v134; // eax
  int v135; // ecx
  unsigned int **v136; // eax
  unsigned int v137; // edx
  unsigned int p_n15_12; // ecx
  unsigned int v139; // ebx
  unsigned int v140; // eax
  unsigned int v141; // ebp
  int p_n15_6; // ecx
  int *v143; // eax
  int v144; // edx
  int n2_16; // ebx
  int n2_17; // edi
  __int16 v147; // cx
  int n15_37; // ebx
  int v149; // edi
  int v150; // ebx
  int v151; // eax
  int v152; // ebp
  unsigned __int16 v153; // cx
  int v154; // eax
  int v155; // ebp
  char *v156; // ebp
  int v157; // eax
  __int16 v158; // cx
  unsigned __int16 *v159; // edx
  int n15_18; // eax
  int v161; // eax
  int n2_2; // ebx
  int p_n15_10; // edx
  int p_n15_8; // ecx
  __int16 n15_21; // ax
  int n15_40; // ecx
  _WORD *n15_39; // ebp
  unsigned int v168; // ecx
  unsigned int v169; // eax
  __int16 v170; // bx
  unsigned int v171; // eax
  unsigned int v172; // edx
  unsigned int v173; // esi
  int p_n15_9; // ecx
  int n15_19; // eax

  n2_7 = (unsigned __int16 *)*(_this + 20);
  n4 = *n2_7;
  n2_8 = (_WORD *)*(_this + 19);
  n4_1 = (unsigned __int16)*(n2_8 - 4);
  __sub_4159E0_n15 = n2_7[4];
  this_1 = _this;
  n15_1 = *(n2_7 - 4);
  n15_3 = n4;
  ::__sub_4159E0_n4_4 = n4;
  n15_7 = n4_1;
  ::__sub_4159E0_n4_3 = n4_1;
  n15_4 = __sub_4159E0_n15;
  ::__sub_4159E0_n15 = __sub_4159E0_n15;
  v8 = *((unsigned __int8 *)n2_7 + 3) + 4 * (__sub_4159E0_n15 == n15_1);
  v9 = *((unsigned __int8 *)n2_7 + 11);
  n15_2 = n15_1;
  __sub_4159E0_n15_0 = n15_1;
  v10 = 32 * *((unsigned __int8 *)n2_8 - 4)
      + 16 * *((unsigned __int8 *)n2_8 - 2)
      + 2 * *((unsigned __int8 *)n2_8 - 6)
      + 8 * v9
      + v8;
  v11 = n4 == n4_1;
  this_2 = this_1;
  if ( v11 )
  {
    if ( n15_3 == n15_4 )
    {
      v14 = *((_WORD *)this_1 + n15_3 + 3029720);
      if ( n15_3 == n15_2 )
        v13 = (unsigned __int16)(v14 - *(n2_8 - 8));
      else
        v13 = (unsigned __int16)(v14 - n15_2);
    }
    else
    {
      v13 = (unsigned __int16)(*((_WORD *)this_1 + n15_3 + 3029720) - n15_4);
    }
  }
  else
  {
    v13 = (unsigned __int16)(*((_WORD *)this_1 + n15_3 + 3029720) - n15_7);
  }
  this_1[1514858] = (int)&this_1[4 * v13 + 269674];
  v15 = *((unsigned __int8 *)this_2 + v10 + 1078244);
  this_2[9] = v15;
  v16 = &this_2[0x10000 * v15 + 531818 + v13];
  this_2[1514859] = (int)v16;
  n15_6 = *(unsigned __int16 *)v16;
  if ( n15_6 == n15_3 )
  {
    n15_5 = 15;
  }
  else if ( n15_6 == n15_7 )
  {
    n15_5 = 30;
  }
  else if ( n15_6 == n15_4 )
  {
    n15_5 = 45;
  }
  else
  {
    v11 = n15_6 == n15_2;
    n15_5 = 60;
    if ( !v11 )
      n15_5 = 0;
  }
  n15_8 = *((unsigned __int16 *)v16 + 1);
  if ( n15_8 == n15_3 )
  {
    n15_5 += 75;
  }
  else if ( n15_8 == n15_7 )
  {
    n15_5 += 150;
  }
  else if ( n15_8 == n15_4 )
  {
    n15_5 += 225;
  }
  else if ( n15_8 == n15_2 )
  {
    n15_5 += 300;
  }
  v20 = this_2[22];
  n2_1 = (int)n2_7;
  v21 = *((unsigned __int8 *)this_2 + v15 + n15_5 + 1078308);
  v22 = this_2[21];
  this_2[10] = v21;
  p_n15_1 = *((unsigned __int8 *)n2_7 + 2);
  v24 = *((_BYTE *)n2_7 + 3);
  n2_4 = n2_8;
  this_1 = this_2;
  p_n15 = p_n15_1;
  n15_30 = this_2[23];
  v26 = *((unsigned __int8 *)n2_8 - 5);
  n15_20 = n15_30;
  v27 = 8 * *((unsigned __int8 *)n2_8 - 12)
      + 4 * *((unsigned __int8 *)n2_8 - 9)
      + v26
      + 2 * *((unsigned __int8 *)n2_8 - 10);
  this_3 = this_1;
  v29 = ((*((_BYTE *)this_1 + 1078695) == 0) << 7)
      + ((*((_BYTE *)this_1 + 1078694) == 0) << 6)
      + 32 * (*((_BYTE *)this_1 + 1078693) == 0)
      + 16 * (*((_BYTE *)this_1 + 1078692) == 0)
      + ((unsigned __int8)(*(_BYTE *)(n15_20 + 2) & *(_BYTE *)(v20 + 2) & p_n15 & *(_BYTE *)(v22 + 2)) << 9)
      + ((unsigned __int8)(*(_BYTE *)(n15_20 + 3) & *(_BYTE *)(v20 + 3) & *(_BYTE *)(v22 + 3) & v24) << 8)
      + (v21 << 10)
      + v27;
  n0xFFFF = *((unsigned __int16 *)this_1 + v29 + 3037912);
  n2_9 = n2_1;
  if ( n0xFFFF == 0xFFFF )
  {
    *((_WORD *)this_1 + v29 + 3037912) = this_1[5];
    n2_9 = this_3[20];
    n2_8 = (_WORD *)this_3[19];
    ++this_3[5];
    n0xFFFF = *((unsigned __int16 *)this_3 + v29 + 3037912);
    p_n15 = *(unsigned __int8 *)(n2_9 + 2);
  }
  v32 = *((unsigned __int8 *)n2_8 - 1) + 4 * *(unsigned __int8 *)(n2_9 + 13) + 2 * p_n15 + 8 * n0xFFFF;
  n0xFFFF_1 = *((unsigned __int16 *)this_3 + v32 + 3230424);
  if ( n0xFFFF_1 == 0xFFFF )
  {
    *((_WORD *)this_3 + v32 + 3230424) = this_3[6]++;
    n0xFFFF_1 = *((unsigned __int16 *)this_3 + v32 + 3230424);
  }
  if ( this_3[4] < 32 )
  {
    n53248 = this_3[7];
    v35 = 16 * n0xFFFF_1 + (n15_7 & 0xF);
    v36 = (char *)this_3 + 2 * v35;
    n0xFFFF_1 = *((unsigned __int16 *)v36 + 3339224);
    if ( n0xFFFF_1 == 0xFFFF )
    {
      if ( n53248 > 53248 )
        v35 |= 0xFu;
      v36 = (char *)this_3 + 2 * v35;
      n0xFFFF_1 = *((unsigned __int16 *)v36 + 3339224);
    }
    if ( n0xFFFF_1 >= n53248 )
    {
      *((_WORD *)v36 + 3339224) = n53248;
      ++this_3[7];
      n0xFFFF_1 = *((unsigned __int16 *)v36 + 3339224);
    }
  }
  v37 = (unsigned __int16 *)this_3[19];
  v38 = *((unsigned __int8 *)v37 - 5);
  v39 = *((unsigned __int8 *)v37 - 6);
  v185 = v37;
  if ( (v38 & v39) != 0
    && (p_n15_3 = (_BYTE *)this_3[20],
        v41 = (unsigned __int8 *)this_3[21],
        ((unsigned __int8)(v41[19]
                         & v41[11]
                         & v41[3]
                         & p_n15_3[27]
                         & p_n15_3[19]
                         & p_n15_3[11]
                         & p_n15_3[3]
                         & p_n15_3[2]
                         & *(p_n15_3 - 5))
       & v41[27]) != 0) )
  {
    v42 = v41[2];
    p_n15_2 = *this_3 - a2;
    n15_31 = 1;
    if ( p_n15_2 <= 1 )
    {
      n8 = 8;
    }
    else
    {
      p_n15 = p_n15_2;
      n15_42 = 1;
      this_1 = this_3;
      while ( 1 )
      {
        n8 = 8 * n15_42;
        if ( (p_n15_3[8 * n15_42 + 19] & p_n15_3[8 * n15_42 + 18]) == 0 )
          break;
        v42 = (unsigned __int8)(v41[n8 + 2] & v42);
        if ( ++n15_42 >= p_n15 )
        {
          this_3 = this_1;
          n15_31 = n15_42;
          n8 = 8 * n15_42;
          goto LABEL_42;
        }
      }
      this_3 = this_1;
      n15_31 = n15_42;
    }
LABEL_42:
    v46 = (unsigned __int8)(v41[n8 + 27] & v41[n8 + 19]);
    n15_2 = *(unsigned __int8 *)(this_3[269671] + n15_31);
    n15_32 = *(unsigned __int8 *)(this_3[269672] + n15_3) + 8 * n15_2 + 4 * v46 + 2 * v42;
    n15_12 = 0;
    if ( *v185 == n15_3 )
    {
      p_n15 = (int)p_n15_3;
      this_1 = this_3;
      do
        ++n15_12;
      while ( n15_12 < n15_31 && v185[4 * n15_12] == n15_3 );
      this_3 = this_1;
      p_n15_3 = (_BYTE *)p_n15;
    }
    n15_9 = n15_12 == n15_31;
    n15_4 = n15_9;
    if ( n15_12 > n15_9 )
    {
      this_3[20] = (int)&p_n15_3[8 * n15_12 + -8 * n15_9];
      this_3[21] = (int)&v41[8 * n15_12 + -8 * n15_9];
      v50 = this_3[23];
      this_3[22] = this_3[22] + 8 * n15_12 - 8 * n15_9;
      v51 = v185;
      this_3[23] = v50 + 8 * n15_12 - 8 * n15_9;
      *((_DWORD *)v51 + 1) = 16843009;
      *(_DWORD *)this_3[19] = 16843009;
      *(_WORD *)(this_3[1514859] + 2) = *(_WORD *)this_3[1514859];
      LOWORD(v51) = n15_3;
      *(_WORD *)this_3[19] = n15_3;
      *(_WORD *)this_3[1514859] = (_WORD)v51;
      v52 = this_3[19];
      v53 = *(_DWORD *)v52;
      n2_1 = *(_DWORD *)(v52 + 4);
      n2_4 = (_WORD *)(v52 + 8);
      this_3[19] = v52 + 8;
      if ( n15_12 - n15_9 != 1 )
      {
        p_n15_4 = n15_12 - n15_9 - 1;
        v55 = p_n15_4 / 2;
        if ( p_n15_4 / 2 )
        {
          p_n15 = p_n15_4;
          n2_10 = n2_1;
          n15_14 = n15_12;
          v57 = 0;
          n15_20 = n15_32;
          n15_10 = n15_3;
          do
          {
            *(_WORD *)(this_3[1514859] + 2) = n15_10;
            *(_DWORD *)this_3[19] = v53;
            *(_DWORD *)(this_3[19] + 4) = n2_10;
            v59 = this_3[1514859];
            this_3[19] += 8;
            *(_WORD *)(v59 + 2) = n15_10;
            *(_DWORD *)this_3[19] = v53;
            *(_DWORD *)(this_3[19] + 4) = n2_10;
            n2_11 = (_WORD *)(this_3[19] + 8);
            this_3[19] = (int)n2_11;
            ++v57;
          }
          while ( v57 < v55 );
          p_n15_4 = p_n15;
          n15_32 = n15_20;
          n2_4 = n2_11;
          n15_12 = n15_14;
          v61 = 2 * v57 + 1;
        }
        else
        {
          v61 = 1;
        }
        if ( p_n15_4 > (unsigned int)(v61 - 1) )
        {
          *(_WORD *)(this_3[1514859] + 2) = n15_3;
          *(_DWORD *)this_3[19] = v53;
          *(_DWORD *)(this_3[19] + 4) = n2_1;
          n2_12 = (_WORD *)(this_3[19] + 8);
          this_3[19] = (int)n2_12;
          n2_4 = n2_12;
        }
      }
      v63 = this_3[20];
      v64 = *(_BYTE *)(v63 - 14);
      v65 = *(_BYTE *)(v63 + 18);
      v66 = *(_BYTE *)(v63 + 34);
      n15_20 = n15_32;
      v67 = *(_BYTE *)(v63 - 22);
      n15_14 = n15_12;
      v68 = *(_BYTE *)(v63 + 26) + v65 + v64 + v67 + v66 - 5;
      v69 = (_BYTE *)this_3[21];
      *((_BYTE *)this_3 + 1078692) = v68;
      n2_13 = n2_4;
      *((_BYTE *)this_3 + 1078693) = v69[26]
                                   + v69[18]
                                   + v69[10]
                                   + v69[2]
                                   + *(v69 - 6)
                                   + *(v69 - 14)
                                   + *(v69 - 22)
                                   + v69[34]
                                   - 8;
      *((_BYTE *)this_3 + 1078694) = *((_BYTE *)n2_13 - 29) + *((_BYTE *)n2_13 - 21) - 2;
      n15_11 = n15_3;
      *((_BYTE *)this_3 + 1078695) = *((_BYTE *)n2_13 - 38)
                                   + *((_BYTE *)n2_13 - 46)
                                   + *((_BYTE *)n2_13 - 54)
                                   + *((_BYTE *)n2_13 - 30)
                                   - 4;
      *((_BYTE *)n2_13 - 2) = n15_11 == *(unsigned __int16 *)(v63 + 8);
      n15_32 = n15_20;
      *(_BYTE *)(this_3[19] - 1) = n15_11 == *(unsigned __int16 *)(this_3[20] + 16);
      n15_12 = n15_14;
    }
    sub_412490((unsigned __int16 *)this_3 + 3 * n15_32 + 538179, (unsigned __int16 *)this_3 + 538176, n15_4);
    n15_13 = n15_4;
    n4_2 = ::__sub_4159E0_n4_4;
    v74 = this_3[269672];
    this_3[8] = n15_4;
    *(_BYTE *)(v74 + n4_2) = n15_13;
    if ( !n15_13 && n15_31 != 1 )
    {
      n15_14 = n15_12;
      p_n15 = n15_2;
      this_1 = this_3;
      n15_33 = n15_31;
      n15_35 = 1 << n15_2;
      n15_34 = 0;
      n15_15 = n15_2;
      do
      {
        if ( n15_33 > (n15_35 | n15_34) )
        {
          n15_20 = n15_34;
          n2_14 = (unsigned __int16 *)&this_1[24 * (n15_34 == 0) + 269473 + 24 * (n15_15 == p_n15)] + 3 * n15_15 + 1;
          n2_4 = n2_14;
          n2_1 = n15_14 & n15_35;
          sub_411FD0(*n2_14, n2_14[1], (n15_14 & n15_35) != 0);
          if ( *((unsigned __int16 *)&this_1[24 * (n15_34 == 0) + 269474 + 24 * (n15_15 == p_n15)] + 3 * n15_15 + 1) < (unsigned int)__sub_4159E0_n0x88 )
            sub_4148F0(n2_4);
          n2_15 = n2_1;
          n15_31 = n15_35;
          n2_4[n2_1 != 0] += 8;
          n15_34 |= n2_15;
          n15_35 = n15_31;
        }
        --n15_15;
        n15_35 >>= 1;
      }
      while ( n15_35 );
      n15_12 = n15_14;
      this_3 = this_1;
    }
    if ( this_3[8] )
      return n15_12;
  }
  else
  {
    v82 = 4 * this_3[10];
    n15_36 = (int)&this_3[v82 + 24];
    n15_31 = n15_36;
    n2_3 = &this_3[4 * n0xFFFF_1 + 776];
    __sub_4159E0_n0x2000 = HIWORD(this_3[4 * n0xFFFF_1 + 778]);
    if ( __sub_4159E0_n0x2000 )
    {
      if ( __sub_4159E0_n0x2000 == 1 )
      {
        v143 = &this_3[v82 + 24];
        v144 = *(unsigned __int8 *)(n15_36 + 15);
        n2_16 = v144 * *((unsigned __int16 *)n2_3 + 2);
        n2_17 = v144 * *((unsigned __int16 *)n2_3 + 3);
        p_n15 = v144 * *(unsigned __int16 *)n2_3;
        v147 = v144 * *((_WORD *)n2_3 + 1);
        n2_1 = n2_16;
        n15_37 = v144 * *((unsigned __int16 *)n2_3 + 4);
        n2_4 = (_WORD *)n2_17;
        n15_20 = n15_37;
        *(_QWORD *)n2_3 = *(_QWORD *)v143;
        *((_QWORD *)n2_3 + 1) = *((_QWORD *)v143 + 1);
        v149 = *((unsigned __int16 *)n2_3 + 5);
        *((_BYTE *)n2_3 + 14) *= 8;
        this_1 = this_3;
        v150 = 21 * *((unsigned __int16 *)n2_3 + 1);
        p_n15 += (21 * *(unsigned __int16 *)n2_3 + v149 - 1) / v149;
        *(_WORD *)n2_3 = p_n15;
        v151 = (v150 + v149 - 1) / v149;
        LOWORD(v150) = n2_1;
        v152 = 21 * *((unsigned __int16 *)n2_3 + 2);
        v153 = v151 + v147;
        *((_WORD *)n2_3 + 1) = v153;
        v154 = (v152 + v149 - 1) / v149;
        v155 = 21 * *((unsigned __int16 *)n2_3 + 3);
        LOWORD(v150) = v154 + v150;
        *((_WORD *)n2_3 + 2) = v150;
        v156 = (char *)n2_4 + (v155 + v149 - 1) / v149;
        v157 = 21 * *((unsigned __int16 *)n2_3 + 4);
        *((_WORD *)n2_3 + 3) = (_WORD)v156;
        v158 = (_WORD)v156 + v150 + v153;
        this_3 = this_1;
        LOWORD(v149) = (v157 + v149 - 1) / v149 + n15_20;
        *((_WORD *)n2_3 + 4) = v149;
        __sub_4159E0_n0x2000 = (unsigned __int16)(p_n15 + v149 + v158);
        *((_WORD *)n2_3 + 5) = __sub_4159E0_n0x2000;
        v185 = (unsigned __int16 *)this_3[19];
      }
      n15_16 = *v185;
      ::__sub_4159E0_n0x2000 = __sub_4159E0_n0x2000;
      if ( n15_16 == n15_3 )
      {
        v87 = *(unsigned __int16 *)n2_3;
        n2 = 1;
      }
      else if ( n15_16 == n15_7 )
      {
        v87 = *(unsigned __int16 *)n2_3 + *((unsigned __int16 *)n2_3 + 1);
        n2 = 2;
      }
      else if ( n15_16 == n15_4 )
      {
        v87 = *(unsigned __int16 *)n2_3 + *((unsigned __int16 *)n2_3 + 2) + *((unsigned __int16 *)n2_3 + 1);
        n2 = 3;
      }
      else if ( n15_16 == n15_2 )
      {
        v87 = *((unsigned __int16 *)n2_3 + 5) - *((unsigned __int16 *)n2_3 + 4);
        n2 = 4;
      }
      else
      {
        v87 = 0;
        n2 = 0;
      }
      p_n15_5 = *((unsigned __int16 *)n2_3 + 6);
      __sub_4159E0_n0x2000_1 = v87;
      __sub_4159E0_n0x2000_0 = *((unsigned __int16 *)n2_3 + n2) + v87;
      p_n15_7 = *((unsigned __int16 *)n2_3 + 5);
      n15_17 = *((unsigned __int8 *)n2_3 + 15);
      if ( p_n15_7 > p_n15_5
        && (*((unsigned __int16 *)n2_3 + n2) + n15_17 + 8 < p_n15_7 || *((unsigned __int16 *)n2_3 + 5) > 0x4000u) )
      {
        v137 = *((unsigned __int16 *)n2_3 + 2);
        p_n15 = p_n15_5;
        p_n15_12 = *((unsigned __int16 *)n2_3 + 1);
        this_1 = this_3;
        n2_1 = n2;
        v139 = *(unsigned __int16 *)n2_3;
        n2_4 = (_WORD *)n15_17;
        LOWORD(v139) = v139 - (v139 >> 1);
        *(_WORD *)n2_3 = v139;
        LOWORD(p_n15_12) = p_n15_12 - (p_n15_12 >> 1);
        *((_WORD *)n2_3 + 1) = p_n15_12;
        LOWORD(v137) = v137 - (v137 >> 1);
        v140 = *((unsigned __int16 *)n2_3 + 3);
        *((_WORD *)n2_3 + 2) = v137;
        LOWORD(v140) = v140 - (v140 >> 1);
        v141 = *((unsigned __int16 *)n2_3 + 4);
        *((_WORD *)n2_3 + 3) = v140;
        LOWORD(v141) = v141 - (v141 >> 1);
        *((_WORD *)n2_3 + 4) = v141;
        LOWORD(p_n15_12) = v140 + v137 + p_n15_12;
        n15_17 = (int)n2_4;
        LOWORD(p_n15_12) = v139 + v141 + p_n15_12;
        n2 = n2_1;
        this_3 = this_1;
        p_n15_7 = (unsigned __int16)p_n15_12;
        p_n15_6 = p_n15;
        *((_WORD *)n2_3 + 5) = p_n15_7;
        if ( p_n15_6 < 256 && !*((_BYTE *)n2_3 + 14) )
        {
          p_n15_6 = 256;
          *((_WORD *)n2_3 + 6) = 256;
        }
        if ( p_n15_7 > p_n15_6 )
        {
          if ( n15_17 < 15 )
            LOWORD(n15_17) = 15;
          *((_BYTE *)n2_3 + 15) = n15_17;
        }
      }
      *((_WORD *)n2_3 + 5) = n15_17 + p_n15_7;
      *((_WORD *)n2_3 + n2) += n15_17;
      sub_411E90();
      this_3[8] = n2;
      if ( *((_BYTE *)n2_3 + 14) )
      {
        --*((_BYTE *)n2_3 + 14);
        n15_38 = n15_31;
        ++*(_WORD *)(n15_31 + 10);
        ++*(_WORD *)(n15_38 + 2 * n2);
        n2 = this_3[8];
      }
    }
    else
    {
      v159 = (unsigned __int16 *)&this_3[v82 + 24];
      n15_18 = *v185;
      ::__sub_4159E0_n0x2000 = *(unsigned __int16 *)(n15_36 + 10);
      if ( n15_18 == n15_3 )
      {
        v161 = *v159;
        n2_2 = 1;
      }
      else if ( n15_18 == n15_7 )
      {
        v161 = *v159 + v159[1];
        n2_2 = 2;
      }
      else if ( n15_18 == n15_4 )
      {
        v161 = *v159 + v159[2] + v159[1];
        n2_2 = 3;
      }
      else if ( n15_18 == n15_2 )
      {
        v161 = v159[5] - v159[4];
        n2_2 = 4;
      }
      else
      {
        v161 = 0;
        n2_2 = 0;
      }
      __sub_4159E0_n0x2000_1 = v161;
      __sub_4159E0_n0x2000_0 = *(unsigned __int16 *)(n15_31 + 2 * n2_2) + v161;
      p_n15_10 = *(unsigned __int16 *)(n15_31 + 10);
      p_n15_8 = *(unsigned __int16 *)(n15_31 + 12);
      n15_20 = *(unsigned __int8 *)(n15_31 + 15);
      if ( p_n15_10 > p_n15_8 && (*(unsigned __int16 *)(n15_31 + 2 * n2_2) + n15_20 + 8 < p_n15_10 || p_n15_10 > 0x4000) )
      {
        p_n15 = p_n15_8;
        this_1 = this_3;
        n15_39 = (_WORD *)n15_31;
        v168 = *(unsigned __int16 *)(n15_31 + 2);
        v169 = *(unsigned __int16 *)(n15_31 + 4);
        n2_1 = (int)n2_3;
        n2_4 = (_WORD *)n2_2;
        v170 = *(_WORD *)n15_31 - (*(_WORD *)n15_31 >> 1);
        *(_WORD *)n15_31 = v170;
        LOWORD(v168) = v168 - (v168 >> 1);
        n15_39[1] = v168;
        v171 = v169 - (v169 >> 1);
        v172 = (unsigned __int16)n15_39[3];
        n15_39[2] = v171;
        LOWORD(v172) = v172 - (v172 >> 1);
        v173 = (unsigned __int16)n15_39[4];
        n15_39[3] = v172;
        LOWORD(v173) = v173 - (v173 >> 1);
        n15_39[4] = v173;
        LOWORD(v173) = v170 + v173;
        n2_2 = (int)n2_4;
        p_n15_10 = (unsigned __int16)(v173 + v172 + v171 + v168);
        p_n15_9 = p_n15;
        n2_3 = (int *)n2_1;
        n15_39[5] = p_n15_10;
        this_3 = this_1;
        if ( p_n15_9 < 256 && !*(_BYTE *)(n15_31 + 14) )
        {
          p_n15_9 = 256;
          *(_WORD *)(n15_31 + 12) = 256;
        }
        if ( p_n15_10 > p_n15_9 )
        {
          n15_19 = n15_20;
          if ( n15_20 < 15 )
            n15_19 = 15;
          n15_20 = n15_19;
          *(_BYTE *)(n15_31 + 15) = n15_19;
        }
      }
      n15_21 = n15_20;
      n15_40 = n15_31;
      *(_WORD *)(n15_31 + 10) = n15_20 + p_n15_10;
      *(_WORD *)(n15_40 + 2 * n2_2) += n15_21;
      sub_411E90();
      this_3[8] = n2_2;
      *((_WORD *)n2_3 + 5) = (*((_WORD *)n2_3 + n2_2))++ != 0;
      n2 = this_3[8];
    }
    if ( n2 )
      return 1;
    n15_12 = 0;
  }
  v93 = __sub_4159E0_byte_445700;
  n15_22 = ::__sub_4159E0_n15;
  __sub_4159E0_n4_3 = ::__sub_4159E0_n4_3;
  __sub_4159E0_n4_4 = ::__sub_4159E0_n4_4;
  __sub_4159E0_buf_0[__sub_4159E0_n15_0] = __sub_4159E0_byte_445700;
  __sub_4159E0_buf_0[n15_22] = v93;
  v97 = (unsigned __int16 *)this_3[1514859];
  __sub_4159E0_buf_0[__sub_4159E0_n4_3] = v93;
  __sub_4159E0_buf_0[__sub_4159E0_n4_4] = v93;
  v98 = (unsigned __int16 *)this_3[1514858];
  __sub_4159E0_byte_445440[0] = v93;
  n15_14 = n15_12;
  this_3[269554] = 0;
  p_n15_11 = *v97;
  n2_5 = v97[1];
  n2_6 = (_WORD *)*v98;
  n15_41 = v98[2];
  p_n15 = p_n15_11;
  n15_23 = v98[1];
  n2_1 = n2_5;
  n15_24 = v98[3];
  n2_4 = n2_6;
  n15_25 = v98[4];
  n15_20 = n15_23;
  this_4 = (int *)v98[5];
  n15_31 = n15_41;
  n15_26 = v98[6];
  v108 = (unsigned __int16 *)v98[7];
  n15_2 = n15_24;
  v109 = this_3[19];
  n15_4 = n15_25;
  n15_27 = *(unsigned __int16 *)(v109 - 16);
  this_1 = this_4;
  v111 = (unsigned __int16 *)this_3[20];
  n15_3 = n15_26;
  v112 = v111[8];
  v185 = v108;
  n15_7 = n15_27;
  v113 = (unsigned __int16 *)this_3[21];
  v114 = v113[4];
  v187 = v112;
  v115 = *v113;
  v188 = v114;
  v116 = *(v111 - 8);
  v189 = v115;
  v117 = *(v113 - 4);
  v190 = v116;
  v118 = *(unsigned __int16 *)(v109 - 24);
  v191 = v117;
  v119 = v111[12];
  v192 = v118;
  v120 = v111[16];
  v193 = v119;
  v121 = *(unsigned __int16 *)(v109 - 32);
  v194 = v120;
  v122 = *(v111 - 12);
  v195 = v121;
  v123 = v113[8];
  v196 = v122;
  v197 = v123;
  v124 = (unsigned __int16 *)this_3[22];
  v198 = *v124;
  v199 = *(v113 - 8);
  v125 = *(unsigned __int16 *)(v109 - 40);
  v126 = *(unsigned __int16 *)(v109 - 56);
  v200 = v125;
  v201 = v124[4];
  v127 = v111[20];
  v128 = v111[28];
  v202 = v127;
  v203 = *(unsigned __int16 *)this_3[23];
  v204 = v126;
  v205 = *(v124 - 4);
  v206 = v128;
  v207 = v113[12];
  this_3[11] = 0;
  do
  {
    v129 = sub_416860(this_3, &p_n15);
    if ( v129 >= 0 )
    {
      n15_28 = v129 == *(unsigned __int16 *)this_3[19];
      sub_412490(
        (unsigned __int16 *)this_3 + 3 * this_3[13] + 525888,
        (unsigned __int16 *)this_3 + 3 * this_3[12] + 525840,
        n15_28);
      if ( n15_28 )
        return n15_14 + 1;
      __sub_4159E0_buf_0[v129] = __sub_4159E0_byte_445700;
    }
    n32 = this_3[11] + 1;
    this_3[11] = n32;
  }
  while ( n32 < 32 );
  n15_29 = n15_14;
  n4_5 = ::__sub_4159E0_n4_4;
  v134 = this_3[269552];
  this_3[269554] = this_3[269553] + 24 * ::__sub_4159E0_n4_3;
  v135 = v134 + 24 * n4_5;
  v136 = (unsigned int **)this_3[269558];
  this_3[269555] = v135;
  while ( 1 )
  {
    if ( !(*v136)[1] )
      goto LABEL_94;
    if ( sub_412B10(*v136, *(unsigned __int16 *)this_3[19]) )
      return n15_29 + 1;
    v136 = (unsigned int **)this_3[269558];
LABEL_94:
    this_3[269558] = (int)++v136;
  }
}

#undef sub_411E90
#undef sub_411FD0
#undef sub_412490
#undef sub_412B10
#undef sub_4148F0
#undef sub_416860
