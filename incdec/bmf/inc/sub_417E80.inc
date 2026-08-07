// sub_417E80 @ 0x00417E80 — __thiscall
// Extracted from BMF.c:22076-22633 by extract.py per incdec.md.

typedef unsigned char t_sub_417E80_byte_439860[32];
static t_sub_417E80_byte_439860& __sub_417E80_byte_439860 = *(t_sub_417E80_byte_439860*)0x00439860;

#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0
static inline unsigned int __fwd_sub_417E80_sub_414860(void *a0, int a1, int a2, int a3) { return __sub_414860((int *)a0, a1, a2, a3); }
#define sub_414860 __fwd_sub_417E80_sub_414860
#define sub_414920 __sub_414920
#define sub_4149C0 __sub_4149C0
#define sub_416C90 __sub_416C90
static inline int __fwd_sub_417E80_sub_418650(void *a0, int a1) { return __sub_418650((_DWORD *)a0, a1); }
#define sub_418650 __fwd_sub_417E80_sub_418650
static inline void __fwd_sub_417E80_sub_419430(void *a0) { __sub_419430((_DWORD *)a0); }
#define sub_419430 __fwd_sub_417E80_sub_419430

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

PROBE_DECL(__sub_417E80)
__attribute__((force_align_arg_pointer)) __attribute__((thiscall)) void __sub_417E80(_DWORD *_this, char *Src)
{
  alignas(16) unsigned char __hexrays_frame[100];   // original frame, ebp-0x54..ebp+0x0
  int &Size = *(int *)(__hexrays_frame + 0);
  int &v82 = *(int *)(__hexrays_frame + 8);
  int &n4 = *(int *)(__hexrays_frame + 8);
  int &v84 = *(int *)(__hexrays_frame + 8);
  char * &v85 = *(char * *)(__hexrays_frame + 12);
  int &v86 = *(int *)(__hexrays_frame + 12);
  int &v87 = *(int *)(__hexrays_frame + 12);
  int &v88 = *(int *)(__hexrays_frame + 16);
  char * &ArgList_1 = *(char * *)(__hexrays_frame + 20);
  char * &ArgList_5 = *(char * *)(__hexrays_frame + 20);
  int &n6_3 = *(int *)(__hexrays_frame + 20);
  char * &v92 = *(char * *)(__hexrays_frame + 24);
  int &v93 = *(int *)(__hexrays_frame + 28);
  int &v94 = *(int *)(__hexrays_frame + 32);
  int &v95 = *(int *)(__hexrays_frame + 36);
  int &ArgList_4 = *(int *)(__hexrays_frame + 40);
  char * &Src_1 = *(char * *)(__hexrays_frame + 44);
  _DWORD * &this_1 = *(_DWORD * *)(__hexrays_frame + 48);
  int &v99 = *(int *)(__hexrays_frame + 52);
  int &v100 = *(int *)(__hexrays_frame + 56);
  int &v101 = *(int *)(__hexrays_frame + 60);
  int &v102 = *(int *)(__hexrays_frame + 64);
  PROBE_HIT(__sub_417E80);
  int v3; // esi
  char *ArgList; // esi
  int v5; // edx
  int v6; // eax
  _DWORD *this_2; // ebx
  int v8; // ebp
  char *v9; // ebx
  int n5; // edx
  int v11; // ebx
  _DWORD *this_3; // eax
  _DWORD *v13; // ebx
  int v14; // ebp
  int v15; // esi
  int v16; // ecx
  int v17; // ecx
  int v18; // eax
  int v19; // edi
  __int16 v20; // cx
  int n0x10000; // ecx
  _DWORD *v22; // eax
  char *ArgList_2; // esi
  int this_4; // ebx
  char *buf; // eax
  char v26; // fps
  int v27; // ebp
  int v28; // edi
  int v29; // edx
  int v30; // ebp
  _DWORD *v31; // eax
  _DWORD *i_1; // eax
  _DWORD *i; // edx
  int v34; // ebp
  _DWORD *v35; // eax
  _DWORD *j_1; // eax
  _DWORD *j; // edx
  bool v38; // cc
  int v39; // edi
  int v40; // edx
  char *ArgList_3; // ebp
  int n4_1; // edx
  int v43; // eax
  int v44; // edi
  int v45; // esi
  int v46; // ecx
  int v47; // ebp
  int v48; // eax
  _BYTE *v49; // esi
  _BYTE *v50; // ecx
  int v51; // edx
  int v52; // eax
  int v53; // ebp
  int v54; // esi
  _DWORD *ArgList_7; // ecx
  int v56; // ebp
  int v57; // edx
  int v58; // esi
  _DWORD *ArgList_6; // edx
  int v60; // ecx
  int v61; // ebp
  int v62; // ecx
  char *ArgList_9; // edx
  int v64; // eax
  int v65; // ecx
  int v66; // esi
  int n6; // esi
  int v68; // ecx
  int v69; // eax
  int n6_4; // ecx
  char *ArgList_10; // ebx
  int n6_1; // edi
  int v73; // edx
  char *Src_2; // edx
  int n6_2; // edi
  int v76; // ecx
  char *v77; // ebp
  int v78; // eax
  char *ArgList_8; // ebp
  int v80; // ecx

  v3 = *(_this + 2) < 8;
  Src_1 = Src;
  ArgList = &Src[-v3];
  sub_4149C0((char)ArgList);
  sub_419430(_this);
  ArgList_1 = ArgList;
  this_1 = _this;
  v102 = 0;
  v5 = 0;
  do
  {
    v6 = (unsigned __int8)__sub_417E80_byte_439860[v5];
    this_2 = this_1;
    *((_BYTE *)this_1 + v6 + 1078244) = v5;
    v100 = 0;
    v82 = v5;
    v92 = (char *)this_2 + v5;
    v88 = v6 & 4;
    v99 = v6 & 2;
    v95 = v6 & 0x10;
    v8 = 0;
    v93 = v6 & 1;
    v9 = (char *)this_2 + v5;
    ArgList_4 = v6 & 0x20;
    v94 = v6 & 8;
    do
    {
      v100 = v8;
      n5 = 0;
      v85 = &v9[15 * v8];
      do
      {
        v11 = v102;
        this_3 = this_1;
        v85[75 * n5 + 1078308] = v102;
        v101 = this_3[4];
        v13 = &this_3[4 * v11];
        *((_WORD *)v13 + 49) = 2;
        *((_WORD *)v13 + 50) = 2;
        *((_WORD *)v13 + 51) = 2;
        *((_WORD *)v13 + 52) = 2;
        if ( v88 )
        {
          v14 = (unsigned __int16)(*((_WORD *)v13 + 52) + *((_WORD *)v13 + 51));
          *((_WORD *)v13 + 51) = v14;
          v15 = 0;
          *((_WORD *)v13 + 52) = 0;
        }
        else
        {
          v14 = *((unsigned __int16 *)v13 + 51);
          v15 = *((unsigned __int16 *)v13 + 52);
        }
        if ( v99 )
        {
          v16 = (unsigned __int16)(v15 + *((_WORD *)v13 + 50));
          *((_WORD *)v13 + 50) = v16;
          v15 = 0;
          *((_WORD *)v13 + 52) = 0;
        }
        else
        {
          v16 = *((unsigned __int16 *)v13 + 50);
        }
        if ( v95 )
        {
          v16 = (unsigned __int16)(v14 + v16);
          *((_WORD *)v13 + 50) = v16;
          v14 = 0;
          *((_WORD *)v13 + 51) = 0;
        }
        if ( v93 )
        {
          *((_WORD *)v13 + 49) += v15;
          v15 = 0;
          *((_WORD *)v13 + 52) = 0;
        }
        if ( v94 )
        {
          *((_WORD *)v13 + 49) += v14;
          v14 = 0;
          *((_WORD *)v13 + 51) = 0;
        }
        if ( ArgList_4 )
        {
          *((_WORD *)v13 + 49) += v16;
          v16 = 0;
          *((_WORD *)v13 + 50) = 0;
        }
        v17 = (v14 != 0) + (v16 != 0) + (v15 != 0) + 2;
        if ( v17 <= v101 )
        {
          *((_BYTE *)v13 + 110) = v17;
          *((_WORD *)v13 + 48) = 2;
        }
        else
        {
          LOBYTE(v17) = v17 - 1;
          *((_BYTE *)v13 + 110) = v17;
          *((_WORD *)v13 + 48) = 0;
        }
        if ( *((_WORD *)v13 + v100 + 48) && *((_WORD *)v13 + n5 + 48) && (unsigned __int8)v17 <= v101 )
        {
          v19 = v100;
          v18 = 1;
          v20 = (unsigned __int8)(1 << (5 - v17));
          *((_BYTE *)v13 + 111) = v20;
          *((_WORD *)v13 + 54) = v20 << 6;
          *((_WORD *)v13 + v19 + 48) += v20;
          *((_WORD *)v13 + n5 + 48) += *((unsigned __int8 *)v13 + 111);
          *((_WORD *)v13 + 53) = *((_WORD *)v13 + 48)
                               + *((_WORD *)v13 + 52)
                               + *((_WORD *)v13 + 51)
                               + *((_WORD *)v13 + 50)
                               + *((_WORD *)v13 + 49);
        }
        else
        {
          v18 = 0;
        }
        v102 += v18;
        ++n5;
      }
      while ( n5 < 5 );
      v9 = v92;
      v8 = v100 + 1;
    }
    while ( v100 + 1 < 5 );
    n0x10000 = 0;
    v22 = &this_1[0x10000 * v82];
    do
    {
      LOWORD(v22[n0x10000 + 531818]) = 0x2000;
      HIWORD(v22[n0x10000++ + 531818]) = 0x2000;
    }
    while ( n0x10000 < 0x10000 );
    v5 = v82 + 1;
  }
  while ( v82 + 1 < 15 );
  ArgList_2 = ArgList_1;
  this_4 = (int)this_1;
  buf = (char *)__op_new(this_1[4]);
  Size = this_1[4];
  this_1[269672] = buf;
  sub_4349F0(buf,1,Size);
  v27 = *(_DWORD *)(this_4 + 100);
  v28 = *(_DWORD *)(this_4 + 104);
  *(_DWORD *)(this_4 + 1051664) = *(_DWORD *)(this_4 + 96);
  v29 = *(_DWORD *)(this_4 + 108);
  *(_DWORD *)(this_4 + 1051668) = v27;
  *(_DWORD *)(this_4 + 1051672) = v28;
  *(_DWORD *)(this_4 + 1051676) = v29;
  *(_DWORD *)(this_4 + 1078224) = this_4 + 1078184;
  sub_414860((int *)(this_4 + 1078184), this_4, *(_DWORD *)(this_4 + 16), 1);
  *(_DWORD *)(this_4 + 1078232) = this_4 + 1078216;
  v30 = *(_DWORD *)(this_4 + 16);
  v31 = __op_new(24 * v30 + 4);
  if ( v31 )
  {
    *v31 = v30;
    i_1 = v31 + 1;
    for ( i = i_1; v30; --v30 )
    {
      i_1[5] = 0;
      i_1 += 6;
    }
  }
  else
  {
    i = nullptr;
  }
  v34 = *(_DWORD *)(this_4 + 16);
  *(_DWORD *)(this_4 + 1078208) = i;
  v35 = __op_new(24 * v34 + 4);
  if ( v35 )
  {
    *v35 = v34;
    j_1 = v35 + 1;
    for ( j = j_1; v34; --v34 )
    {
      j_1[5] = 0;
      j_1 += 6;
    }
  }
  else
  {
    j = nullptr;
  }
  v38 = *(_DWORD *)(this_4 + 16) <= 0;
  *(_DWORD *)(this_4 + 1078212) = j;
  if ( !v38 )
  {
    v39 = 0;
    do
    {
      sub_414860((int *)(*(_DWORD *)(this_4 + 1078208) + 24 * v39), this_4, 99, 0);
      sub_414860((int *)(*(_DWORD *)(this_4 + 1078212) + 24 * v39++), this_4, 33, 0);
    }
    while ( v39 < *(_DWORD *)(this_4 + 16) );
  }
  v40 = *(_DWORD *)(this_4 + 8);
  if ( v40 == *(_DWORD *)(this_4 + 12) )
  {
    ArgList_3 = nullptr;
  }
  else
  {
    ArgList_2 = (char *)__op_new(*(_DWORD *)(this_4 + 4) * *(_DWORD *)this_4 + 3);
    v40 = *(_DWORD *)(this_4 + 8);
    ArgList_3 = ArgList_2;
  }
  n4_1 = (v40 + 7) >> 3;
  if ( *(int *)(this_4 + 4) > 0 )
  {
    n4 = n4_1;
    ArgList_4 = (int)ArgList_3;
    ArgList_5 = ArgList_2;
    v43 = 0;
    while ( 1 )
    {
      v86 = v43;
      *(_BYTE *)(*(_DWORD *)(this_4 + 76) + 3) = *(_WORD *)(*(_DWORD *)(this_4 + 76) - 8) == 0;
      *(_BYTE *)(*(_DWORD *)(this_4 + 76) + 5) = *(_WORD *)(*(_DWORD *)(this_4 + 80) - 8) == 0;
      v44 = *(_DWORD *)(this_4 + 72);
      v45 = *(_DWORD *)(this_4 + 68);
      v46 = *(_DWORD *)(this_4 + 64);
      v47 = *(_DWORD *)(this_4 + 60);
      v48 = *(_DWORD *)(this_4 + 56);
      *(_DWORD *)(this_4 + 72) = v45;
      *(_DWORD *)(this_4 + 68) = v46;
      *(_DWORD *)(this_4 + 64) = v47;
      *(_DWORD *)(this_4 + 60) = v48;
      *(_DWORD *)(this_4 + 56) = v44;
      v44 += 56;
      *(_DWORD *)(this_4 + 76) = v44;
      v48 += 56;
      *(_DWORD *)(this_4 + 80) = v48;
      *(_DWORD *)(this_4 + 84) = v47 + 56;
      *(_DWORD *)(this_4 + 88) = v46 + 56;
      *(_DWORD *)(this_4 + 92) = v45 + 56;
      LOBYTE(v48) = *(unsigned __int16 *)(v48 + 8) == 0;
      *(_BYTE *)(v44 + 4) = v48;
      *(_BYTE *)(*(_DWORD *)(this_4 + 76) - 2) = v48;
      *(_BYTE *)(*(_DWORD *)(this_4 + 76) - 9) = v48;
      LOBYTE(v46) = *(_WORD *)(*(_DWORD *)(this_4 + 80) + 16) == 0;
      *(_BYTE *)(*(_DWORD *)(this_4 + 76) + 6) = v46;
      *(_BYTE *)(*(_DWORD *)(this_4 + 76) - 1) = v46;
      *(_BYTE *)(*(_DWORD *)(this_4 + 76) + 7) = *(_WORD *)(*(_DWORD *)(this_4 + 80) + 24) == 0;
      v49 = *(_BYTE **)(this_4 + 80);
      v50 = *(_BYTE **)(this_4 + 84);
      *(_DWORD *)(this_4 + 76) += 8;
      v49 += 8;
      *(_DWORD *)(this_4 + 88) += 8;
      *(_DWORD *)(this_4 + 80) = v49;
      v50 += 8;
      *(_DWORD *)(this_4 + 84) = v50;
      *(_DWORD *)(this_4 + 92) += 8;
      *(_BYTE *)(this_4 + 1078692) = v49[26] + v49[18] + v49[10] + v49[2] + v49[34] - 5;
      LOBYTE(v47) = v50[2];
      LOBYTE(v44) = v50[10];
      LOBYTE(v48) = v50[18];
      LOBYTE(v49) = v50[26];
      LOBYTE(v50) = v50[34];
      *(_BYTE *)(this_4 + 1078695) = 0;
      *(_BYTE *)(this_4 + 1078694) = 0;
      v51 = *(_DWORD *)this_4;
      *(_BYTE *)(this_4 + 1078693) = (_BYTE)v49 + v48 + v44 + v47 + (_BYTE)v50 - 5;
      v52 = v86;
      if ( v51 <= 0 )
        break;
      v53 = 0;
      do
      {
        v54 = sub_418650((_DWORD *)this_4, v53);
        sub_416C90(this_4);
        v51 = *(_DWORD *)this_4;
        v53 += v54;
      }
      while ( v53 < *(_DWORD *)this_4 );
      v52 = v86;
      if ( n4 != 4 )
        goto LABEL_53;
      if ( v51 > 0 )
      {
        ArgList_6 = (_DWORD *)ArgList_5;
        v65 = 0;
        do
          *ArgList_6++ = *(_DWORD *)(*(_DWORD *)(this_4 + 1078240)
                                   + 4 * *(unsigned __int16 *)(*(_DWORD *)(this_4 + 56) + 8 * v65++ + 64));
        while ( v65 < *(_DWORD *)this_4 );
        goto LABEL_73;
      }
LABEL_74:
      v43 = v52 + 1;
      if ( v43 >= *(_DWORD *)(this_4 + 4) )
      {
        ArgList_3 = (char *)ArgList_4;
        goto LABEL_76;
      }
    }
    if ( n4 == 4 )
      goto LABEL_74;
LABEL_53:
    if ( n4 == 3 )
    {
      if ( v51 > 0 )
      {
        ArgList_7 = (_DWORD *)ArgList_5;
        v56 = 0;
        do
        {
          v57 = *(_DWORD *)(this_4 + 1078240);
          v58 = *(unsigned __int16 *)(*(_DWORD *)(this_4 + 56) + 8 * v56 + 64);
          *(_WORD *)ArgList_7 = *(_WORD *)(v57 + 4 * v58);
          *((_BYTE *)ArgList_7 + 2) = *(_BYTE *)(v57 + 4 * v58 + 2);
          ++v56;
          ArgList_7 = (_DWORD *)((char *)ArgList_7 + 3);
        }
        while ( v56 < *(_DWORD *)this_4 );
        ArgList_5 = (char *)ArgList_7;
      }
      goto LABEL_74;
    }
    if ( n4 != 2 )
    {
      if ( *(_DWORD *)(this_4 + 8) == 8 )
      {
        if ( v51 > 0 )
        {
          ArgList_8 = ArgList_5;
          v80 = 0;
          do
            *ArgList_8++ = *(_BYTE *)(*(_DWORD *)(this_4 + 1078240)
                                    + 4 * *(unsigned __int16 *)(*(_DWORD *)(this_4 + 56) + 8 * v80++ + 64));
          while ( v80 < *(_DWORD *)this_4 );
          ArgList_5 = ArgList_8;
        }
      }
      else if ( v51 > 0 )
      {
        v87 = v52;
        v61 = 0;
        v62 = 0;
        ArgList_9 = ArgList_5;
        do
        {
          v64 = *(_DWORD *)(this_4 + 8);
          v62 -= v64;
          if ( v62 < 0 )
          {
            v62 = 8 - v64;
            *++ArgList_9 = *(_DWORD *)(*(_DWORD *)(this_4 + 1078240)
                                     + 4 * *(unsigned __int16 *)(*(_DWORD *)(this_4 + 56) + 8 * v61 + 64)) << (8 - v64);
          }
          else
          {
            *ArgList_9 |= *(_DWORD *)(*(_DWORD *)(this_4 + 1078240)
                                    + 4 * *(unsigned __int16 *)(*(_DWORD *)(this_4 + 56) + 8 * v61 + 64)) << v62;
          }
          ++v61;
        }
        while ( v61 < *(_DWORD *)this_4 );
        v52 = v87;
        ArgList_5 = ArgList_9;
      }
      goto LABEL_74;
    }
    if ( v51 > 0 )
    {
      ArgList_6 = (_DWORD *)ArgList_5;
      v60 = 0;
      do
      {
        *(_WORD *)ArgList_6 = *(_DWORD *)(*(_DWORD *)(this_4 + 1078240)
                                        + 4 * *(unsigned __int16 *)(*(_DWORD *)(this_4 + 56) + 8 * v60++ + 64));
        ArgList_6 = (_DWORD *)((char *)ArgList_6 + 2);
      }
      while ( v60 < *(_DWORD *)this_4 );
LABEL_73:
      ArgList_5 = (char *)ArgList_6;
      goto LABEL_74;
    }
    goto LABEL_74;
  }
LABEL_76:
  sub_414920();
  v66 = *(_DWORD *)(this_4 + 12);
  if ( v66 != *(_DWORD *)(this_4 + 8) )
  {
    n6 = (v66 + 7) >> 3;
    if ( n6 <= 0 )
    {
      v68 = *(_DWORD *)(this_4 + 4) * *(_DWORD *)this_4;
    }
    else
    {
      n6_3 = 0;
      v68 = *(_DWORD *)(this_4 + 4) * *(_DWORD *)this_4;
      v69 = v68 / n6;
      if ( n6 >= 6 )
      {
        v84 = *(_DWORD *)(this_4 + 4) * *(_DWORD *)this_4;
        n6_4 = 0;
        this_1 = (_DWORD *)this_4;
        ArgList_10 = ArgList_3;
        do
        {
          (&v92)[n6_4] = ArgList_10;
          ArgList_10 += 5 * v69;
          *(&v93 + n6_4) = (int)&ArgList_3[v69 * (n6_4 + 1)];
          *(&v94 + n6_4) = (int)&ArgList_3[v69 * (n6_4 + 2)];
          *(&v95 + n6_4) = (int)&ArgList_3[v69 * (n6_4 + 3)];
          *(&ArgList_4 + n6_4) = (int)&ArgList_3[v69 * (n6_4 + 4)];
          n6_4 += 5;
        }
        while ( n6_4 <= n6 - 6 );
        this_4 = (int)this_1;
        n6_3 = n6_4;
        v68 = v84;
      }
      n6_1 = n6_3;
      v73 = v69 * n6_3;
      this_1 = (_DWORD *)this_4;
      do
      {
        (&v92)[n6_1] = &ArgList_3[v73];
        v73 += v69;
        ++n6_1;
      }
      while ( n6_1 < n6 );
      this_4 = (int)this_1;
    }
    if ( v68 > 0 )
    {
      Src_2 = Src_1;
      ArgList_4 = (int)ArgList_3;
      n6_2 = 0;
      v76 = 0;
      do
      {
        v77 = (&v92)[n6_2];
        *Src_2 = *v77;
        v78 = *(_DWORD *)(this_4 + 4) * *(_DWORD *)this_4;
        ++Src_2;
        (&v92)[n6_2++] = v77 + 1;
        if ( n6_2 == n6 )
          n6_2 = 0;
        ++v76;
      }
      while ( v76 < v78 );
      ArgList_3 = (char *)ArgList_4;
    }
    __op_delete(ArgList_3);
  }
}

#undef FILE
#undef sub_414860
#undef sub_414920
#undef sub_4149C0
#undef sub_416C90
#undef sub_418650
#undef sub_419430
#undef sub_4349F0
