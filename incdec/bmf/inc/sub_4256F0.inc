// sub_4256F0 @ 0x004256F0 — __thiscall
// Extracted from BMF.c:30966-31095 by extract.py per incdec.md.

typedef char t_sub_4256F0_byte_439BC0[8];
static t_sub_4256F0_byte_439BC0& __sub_4256F0_byte_439BC0 = *(t_sub_4256F0_byte_439BC0*)0x00439BC0;
#define byte_439BC0 __sub_4256F0_byte_439BC0
typedef char t_sub_4256F0_byte_439BC8[8];
static t_sub_4256F0_byte_439BC8& __sub_4256F0_byte_439BC8 = *(t_sub_4256F0_byte_439BC8*)0x00439BC8;
#define byte_439BC8 __sub_4256F0_byte_439BC8
typedef char t_sub_4256F0_byte_439BD0[8];
static t_sub_4256F0_byte_439BD0& __sub_4256F0_byte_439BD0 = *(t_sub_4256F0_byte_439BD0*)0x00439BD0;
#define byte_439BD0 __sub_4256F0_byte_439BD0

static inline unsigned int __fwd_sub_4256F0_sub_4118A0(void *a0, void *a1) { return __sub_4118A0((_BYTE *)a0, (char *)a1); }
#define sub_4118A0 __fwd_sub_4256F0_sub_4118A0
static inline _WORD * __fwd_sub_4256F0_sub_413560(void *a0) { return __sub_413560((_WORD *)a0); }
#define sub_413560 __fwd_sub_4256F0_sub_413560

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#define FILE FILE1

PROBE_DECL(__sub_4256F0)
__attribute__((thiscall)) int *__sub_4256F0(int *_this, int i, int a3, int n4)
{
  PROBE_HIT(__sub_4256F0);
  unsigned int n0x99C60; // edi
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // edi
  int v10; // eax
  bool v11; // zf
  int v12; // ebx
  int v13; // edx
  unsigned int n0x80; // edi
  int v15; // ebp
  int v16; // ecx
  int v17; // ebp
  BOOL v18; // edx
  unsigned int n5; // edi
  int v20; // ecx
  int v21; // edi
  int v22; // edi
  int v23; // eax
  int v24; // edx
  int v25; // edi
  int v27; // [esp+0h] [ebp-20h]
  int v28; // [esp+4h] [ebp-1Ch]

  n0x99C60 = 0;
  *_this = i;
  *(_this + 1) = a3;
  do
    sub_413560((_WORD *)_this + 8 * n0x99C60++ + 1900);
  while ( n0x99C60 < 0x99C60 );
  *(_this + 2) = 0;
  v6 = 0;
  v7 = 0;
  v8 = 0;
  v27 = n4 << 8;
  do
  {
    v9 = (unsigned __int8)byte_439BC0[v6];
    v28 = v8;
    *((_BYTE *)_this + 2 * v8 + 216) = v6;
    v10 = (2 * v8 == v9) + v6;
    *(_this + 2 * v8 + 438) = v27 | v7;
    v11 = 2 * v8 == (unsigned __int8)byte_439BC8[v7];
    *((_BYTE *)_this + 2 * v8 + 217) = v10;
    v12 = 2 * v8 + 1;
    v13 = v11 + v7;
    v6 = (v12 == (unsigned __int8)byte_439BC0[v10]) + v10;
    *(_this + 2 * v8 + 439) = v13 | v27;
    v7 = (v12 == (unsigned __int8)byte_439BC8[v13]) + v13;
    ++v8;
  }
  while ( (unsigned int)(v28 + 1) < 0x100 );
  n0x80 = 0;
  v15 = 0;
  do
  {
    v16 = (unsigned __int8)byte_439BD0[v15];
    *((_BYTE *)_this + 2 * n0x80 + 728) = 8 * v15;
    v17 = (2 * n0x80 == v16) + v15;
    *((_BYTE *)_this + 2 * n0x80 + 729) = 8 * v17;
    v18 = 2 * n0x80++ + 1 == (unsigned __int8)byte_439BD0[v17];
    v15 = v18 + v17;
  }
  while ( n0x80 < 0x80 );
  *(_this + 10) = 32;
  *(_this + 41) = 0;
  *(_this + 37) = 0;
  *(_this + 11) = 64;
  *(_this + 33) = 0;
  *(_this + 29) = 0;
  *(_this + 25) = 0;
  *(_this + 14) = 96;
  *(_this + 21) = 0;
  *(_this + 17) = 0;
  *(_this + 13) = 0;
  *(_this + 15) = 192;
  *(_this + 9) = 0;
  n5 = 0;
  *(_this + 18) = 288;
  *(_this + 19) = 576;
  *(_this + 22) = 864;
  *(_this + 23) = 1728;
  *(_this + 26) = 2592;
  *(_this + 27) = 5184;
  *(_this + 30) = 7776;
  *(_this + 31) = 15552;
  *(_this + 34) = 23328;
  *(_this + 35) = 46656;
  *(_this + 38) = 69984;
  *(_this + 39) = 139968;
  *(_this + 42) = 209952;
  *(_this + 43) = 419904;
  do
    *(_this + n5++ + 44) = (int)__op_new(2 * *_this + 20);
  while ( n5 < 5 );
  sub_4118A0((_BYTE *)_this + 984, (char *)_this + 1496);
  v20 = *_this;
  if ( *_this > -10 )
  {
    v21 = 0;
    do
    {
      *(_BYTE *)(*(_this + 48) + 2 * v21) = 72;
      *(_BYTE *)(*(_this + 47) + 2 * v21) = 72;
      *(_BYTE *)(*(_this + 46) + 2 * v21) = 72;
      *(_BYTE *)(*(_this + 45) + 2 * v21) = 72;
      *(_BYTE *)(*(_this + 44) + 2 * v21) = 72;
      *(_BYTE *)(*(_this + 48) + 2 * v21 + 1) = 0;
      *(_BYTE *)(*(_this + 47) + 2 * v21 + 1) = 0;
      *(_BYTE *)(*(_this + 46) + 2 * v21 + 1) = 0;
      *(_BYTE *)(*(_this + 45) + 2 * v21 + 1) = 0;
      *(_BYTE *)(*(_this + 44) + 2 * v21 + 1) = 0;
      v20 = *_this;
      ++v21;
    }
    while ( v21 < *_this + 10 );
  }
  v22 = *(_this + 45);
  *(_this + 49) = *(_this + 44) + 2 * v20 + 8;
  v23 = *(_this + 46);
  *(_this + 50) = v22 + 2 * v20 + 8;
  v24 = *(_this + 47);
  *(_this + 51) = v23 + 2 * v20 + 8;
  v25 = *(_this + 48);
  *(_this + 52) = v24 + 2 * v20 + 8;
  *(_this + 53) = v25 + 2 * v20 + 8;
  return _this;
}

#undef FILE
#undef byte_439BC0
#undef byte_439BC8
#undef byte_439BD0
#undef sub_4118A0
#undef sub_413560
