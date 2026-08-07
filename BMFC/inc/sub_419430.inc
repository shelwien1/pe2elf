// sub_419430 @ 0x00419430 — __thiscall
// Extracted from BMF.cpp:23558-23702 by extract.py per incdec.md.

#define sub_4123E0 __sub_4123E0
static inline int __fwd_sub_419430_sub_412E60(void *a0) { return __sub_412E60((_DWORD *)a0); }
#define sub_412E60 __fwd_sub_419430_sub_412E60
static inline unsigned int __fwd_sub_419430_sub_414860(void *a0, int a1, int a2, int a3) { return __sub_414860((int *)a0, a1, a2, a3); }
#define sub_414860 __fwd_sub_419430_sub_414860

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

PROBE_DECL(__sub_419430)
BMF_REALIGN __attribute__((thiscall)) void __sub_419430(_DWORD *_this)
{
  alignas(16) unsigned char __hexrays_frame[420];   // original frame, ebp-0x194..ebp+0x0
  _QWORD (&v28)[2] = *(_QWORD (*)[2])(__hexrays_frame + 0);
  int &v29 = *(int *)(__hexrays_frame + 16);
  _DWORD (&v30)[91] = *(_DWORD (*)[91])(__hexrays_frame + 20);
  _DWORD (&v31)[5] = *(_DWORD (*)[5])(__hexrays_frame + 384);
  PROBE_HIT(__sub_419430);
  int n8; // edx
  unsigned int j_2; // ebp
  int v4; // edi
  unsigned int i; // eax
  int v6; // ecx
  unsigned int n8193; // ecx
  unsigned int v8; // eax
  int v9; // edi
  _DWORD *v10; // ebp
  int n16_1; // ebx
  void *v12; // eax
  unsigned int j_1; // edx
  unsigned int j; // eax
  unsigned int v15; // ebp
  int v16; // edx
  unsigned int v17; // eax
  unsigned int v18; // ebp
  unsigned int v19; // esi
  unsigned int v20; // eax
  unsigned int v21; // edi
  _DWORD *v22; // ebp
  int n16; // ebx
  bool v24; // zf
  int v25; // edi
  unsigned int v26; // ebp
  int v27; // eax

  n8 = *(_this + 2);
  j_2 = 0xFFFFFFFF >> (-*((_BYTE *)_this + 8) & 31);
  v4 = (n8 + 7) >> 3;
  for ( i = 0; i < 8; ++i )
  {
    v6 = 12 * i;
    v30[v6] = 0;
    v30[v6 + 6] = 0;
  }
  n8193 = j_2 + 1;
  if ( n8 > 8 )
    n8193 = 8193;
  v8 = sub_4123E0(n8193);
  *(_this + 4) = v8 + 1;
  if ( (int)(v8 + 1) <= 0x2000 )
  {
    v12 = __op_new(4 * v8 + 4);
    j_1 = *(_this + 4);
    *(_this + 269560) = v12;
    if ( j_1 )
    {
      for ( j = 0; j < j_1; ++j )
      {
        *(_DWORD *)(*(_this + 269560) + 4 * j) = j;
        j_1 = *(_this + 4);
      }
    }
    if ( (int)*(_this + 2) > 8 )
    {
      if ( 4 * v4 )
      {
        v15 = 0;
        do
          sub_414860((int *)&v28[3 * v15++], (int)_this, 256, 1);
        while ( v15 < 4 * v4 );
        j_1 = *(_this + 4);
      }
      if ( j_1 )
      {
        v16 = *(_this + 269560);
        v17 = 0;
        v18 = 0;
        do
        {
          *(_DWORD *)(v16 + 4 * v18) = 0;
          if ( v4 )
          {
            v31[0] = v4;
            v19 = 0;
            do
            {
              v20 = sub_412E60((_DWORD *)&v28[12 * v19 + 3 * v17]);
              v21 = v20 << ((8 * v19) & 31);
              v17 = v20 >> 6;
              *(_DWORD *)(*(_this + 269560) + 4 * v18) += v21;
              ++v19;
            }
            while ( v19 < v31[0] );
            v4 = v31[0];
          }
          v16 = *(_this + 269560);
          v17 = *(unsigned __int8 *)(v16 + 4 * v18++) >> 7;
        }
        while ( v18 < *(_this + 4) );
      }
    }
    else if ( j_1 <= j_2 )
    {
      sub_414860((int *)v28, (int)_this, j_2 - j_1 + 2, 1);
      v24 = *(_this + 4) == 0;
      v29 = 19 * LODWORD(v28[0]);
      if ( !v24 )
      {
        v25 = 0;
        v26 = 0;
        do
        {
          v27 = sub_412E60(v28);
          *(_DWORD *)(*(_this + 269560) + 4 * v26) = v27 + v25;
          v25 += v27 + 1;
          ++v26;
        }
        while ( v26 < *(_this + 4) );
      }
    }
    v22 = v31;
    n16 = 16;
    do
    {
      v22 -= 6;
      __op_delete((void *)v22[5]);
      --n16;
    }
    while ( n16 );
  }
  else
  {
    v9 = *(_this + 1) * v4;
    *(_this + 2) = 8;
    *(_this + 1) = v9;
    __sub_419430(_this);
    v10 = v31;
    n16_1 = 16;
    do
    {
      v10 -= 6;
      __op_delete((void *)v10[5]);
      --n16_1;
    }
    while ( n16_1 );
  }
}

#undef FILE
#undef sub_4123E0
#undef sub_412E60
#undef sub_414860
