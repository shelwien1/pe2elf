// sub_4229E0 @ 0x004229E0 — __thiscall
// Extracted from BMF.cpp:28782-28939 by extract.py per incdec.md.

typedef unsigned char t_sub_4229E0_byte_439890[16];
static t_sub_4229E0_byte_439890& __sub_4229E0_byte_439890 = *(t_sub_4229E0_byte_439890*)(blob1 + 0x00439890 - BMF_BLOB_BASE);
typedef unsigned char t_sub_4229E0_byte_4398A0[32];
static t_sub_4229E0_byte_4398A0& __sub_4229E0_byte_4398A0 = *(t_sub_4229E0_byte_4398A0*)(blob1 + 0x004398A0 - BMF_BLOB_BASE);
typedef unsigned char t_sub_4229E0_byte_44339D[0x10000];
static t_sub_4229E0_byte_44339D& __sub_4229E0_byte_44339D = *(t_sub_4229E0_byte_44339D*)(blob1 + 0x0044339D - BMF_BLOB_BASE);
typedef unsigned char t_sub_4229E0_byte_44339E[0x10000];
static t_sub_4229E0_byte_44339E& __sub_4229E0_byte_44339E = *(t_sub_4229E0_byte_44339E*)(blob1 + 0x0044339E - BMF_BLOB_BASE);
typedef int t_sub_4229E0_dword_4458E0;
static t_sub_4229E0_dword_4458E0& __sub_4229E0_dword_4458E0 = *(t_sub_4229E0_dword_4458E0*)(blob1 + 0x004458E0 - BMF_BLOB_BASE);
typedef int t_sub_4229E0_dword_4458E4;
static t_sub_4229E0_dword_4458E4& __sub_4229E0_dword_4458E4 = *(t_sub_4229E0_dword_4458E4*)(blob1 + 0x004458E4 - BMF_BLOB_BASE);
typedef int t_sub_4229E0_dword_4458E8;
static t_sub_4229E0_dword_4458E8& __sub_4229E0_dword_4458E8 = *(t_sub_4229E0_dword_4458E8*)(blob1 + 0x004458E8 - BMF_BLOB_BASE);
typedef int t_sub_4229E0_dword_4458EC;
static t_sub_4229E0_dword_4458EC& __sub_4229E0_dword_4458EC = *(t_sub_4229E0_dword_4458EC*)(blob1 + 0x004458EC - BMF_BLOB_BASE);
typedef int t_sub_4229E0_dword_4458F0;
static t_sub_4229E0_dword_4458F0& __sub_4229E0_dword_4458F0 = *(t_sub_4229E0_dword_4458F0*)(blob1 + 0x004458F0 - BMF_BLOB_BASE);
typedef int t_sub_4229E0_dword_4458F4;
static t_sub_4229E0_dword_4458F4& __sub_4229E0_dword_4458F4 = *(t_sub_4229E0_dword_4458F4*)(blob1 + 0x004458F4 - BMF_BLOB_BASE);
typedef int t_sub_4229E0_n256_0;
static t_sub_4229E0_n256_0& __sub_4229E0_n256_0 = *(t_sub_4229E0_n256_0*)(blob1 + 0x00443398 - BMF_BLOB_BASE);

#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0
static inline unsigned int __fwd_sub_4229E0_sub_4118A0(void *a0, void *a1) { return __sub_4118A0((_BYTE *)a0, (char *)a1); }
#define sub_4118A0 __fwd_sub_4229E0_sub_4118A0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#define FILE FILE1

PROBE_DECL(__sub_4229E0)
BMF_REALIGN __attribute__((thiscall)) int __sub_4229E0(int _this, int i, int n4)
{
  PROBE_HIT(__sub_4229E0);
  unsigned int j; // eax
  unsigned int k; // ecx
  unsigned int n0x1E60; // esi
  int v7; // edi
  int v8; // esi
  int v9; // edx
  void *v10; // eax
  unsigned int m_1; // eax
  unsigned int m; // edx
  int v13; // eax
  unsigned int n5; // esi
  int Size; // edi
  char v16; // fps
  int v17; // eax
  int v18; // ecx
  unsigned int n0x82; // esi
  int v20; // eax
  int v21; // ecx
  int v22; // ebp
  BOOL v23; // eax
  int v24; // eax
  unsigned int n; // edx
  int v26; // edi
  int v27; // eax
  int v28; // esi
  BOOL v29; // edi

  *(_DWORD *)(_this + 278728) = n4;
  for ( j = 0; j < 0x14000; ++j )
  {
    *(_WORD *)(_this + 8 * j + 284714) = 0;
    *(_WORD *)(_this + 8 * j + 284718) = 0;
  }
  for ( k = 0; k < 0x14000; ++k )
  {
    *(_BYTE *)(_this + 8 * k + 284712) = 5;
    *(_BYTE *)(_this + 8 * k + 284713) = 2;
    *(_BYTE *)(_this + 8 * k + 284716) = 5;
    *(_BYTE *)(_this + 8 * k + 284717) = 2;
  }
  n0x1E60 = 0;
  do
  {
    v7 = 16 * n0x1E60;
    *(_WORD *)(_this + v7 + 940074) = 2048;
    ++n0x1E60;
    *(_WORD *)(_this + v7 + 940076) = 2816;
    *(_WORD *)(_this + v7 + 940078) = 2816;
    *(_WORD *)(_this + v7 + 940072) = 4096;
    *(_WORD *)(_this + v7 + 940082) = 2048;
    *(_WORD *)(_this + v7 + 940084) = 2816;
    *(_WORD *)(_this + v7 + 940086) = 2816;
    *(_WORD *)(_this + v7 + 940080) = 4096;
  }
  while ( n0x1E60 < 0x1E60 );
  v8 = 4 * __sub_4229E0_n256_0 + 1;
  v9 = 16 * __sub_4229E0_n256_0;
  *(_DWORD *)(_this + 278732) = (unsigned __int8)(__sub_4229E0_byte_44339E[16
                                                           * (unsigned __int8)__sub_4229E0_byte_44339D[16
                                                                                        * *(_DWORD *)(_this + 278728)]]
                                               & 8) >> 3;
  __sub_4229E0_dword_4458F0 = v8;
  __sub_4229E0_dword_4458F4 = -v8;
  *(_DWORD *)(_this + 278720) = -v9 - 7;
  *(_DWORD *)(_this + 278724) = v9 + 8;
  *(_DWORD *)(_this + 278660) = __op_new(4 * i + 16);
  v10 = __op_new(4 * i + 16);
  *(_DWORD *)(_this + 232) = 1065353216;
  *(_DWORD *)(_this + 278664) = v10;
  *(_DWORD *)(_this + 278668) = *(_DWORD *)(_this + 278660) + 4 * i + 8;
  if ( i > -4 )
  {
    m_1 = (i + 4) / 2;
    if ( m_1 )
    {
      for ( m = 0; m < m_1; ++m )
      {
        *(_DWORD *)(*(_DWORD *)(_this + 278664) + 8 * m) = _this;
        *(_DWORD *)(*(_DWORD *)(_this + 278660) + 8 * m) = _this;
        *(_DWORD *)(*(_DWORD *)(_this + 278664) + 8 * m + 4) = _this;
        *(_DWORD *)(*(_DWORD *)(_this + 278660) + 8 * m + 4) = _this;
      }
      v13 = 2 * m + 1;
    }
    else
    {
      v13 = 1;
    }
    if ( i + 4 > (unsigned int)(v13 - 1) )
    {
      *(_DWORD *)(*(_DWORD *)(_this + 278664) + 4 * v13 - 4) = _this;
      *(_DWORD *)(*(_DWORD *)(_this + 278660) + 4 * v13 - 4) = _this;
    }
  }
  n5 = 0;
  Size = 18 * i + 234;
  do
    *(_DWORD *)(_this + 4 * n5++ + 278756) = __op_new(Size);
  while ( n5 < 5 );
  sub_4349F0(*(char **)(_this + 278756),0,Size);
  v17 = *(_DWORD *)(_this + 278756);
  __sub_4229E0_dword_4458EC = 0;
  v18 = 0;
  __sub_4229E0_dword_4458E8 = 0;
  __sub_4229E0_dword_4458E4 = 0;
  n0x82 = 0;
  __sub_4229E0_dword_4458E0 = 0;
  *(_DWORD *)(_this + 278736) = v17 + 144;
  do
  {
    v20 = (unsigned __int8)__sub_4229E0_byte_439890[v18];
    *(_DWORD *)(_this + 8 * n0x82 + 278944) = (*(_DWORD *)(_this + 278728) << 8) | (16 * v18);
    v21 = (2 * n0x82 == v20) + v18;
    v22 = (unsigned __int8)__sub_4229E0_byte_439890[v21];
    *(_DWORD *)(_this + 8 * n0x82 + 278948) = (*(_DWORD *)(_this + 278728) << 8) | (16 * v21);
    v23 = 2 * n0x82++ + 1 == v22;
    v18 = v23 + v21;
  }
  while ( n0x82 < 0x82 );
  v24 = 0;
  for ( n = 0; n < 0x3C; ++n )
  {
    v26 = (unsigned __int8)__sub_4229E0_byte_4398A0[v24];
    *(_BYTE *)(_this + 2 * n + 280752) = v24;
    v27 = (2 * n == v26) + v24;
    v28 = (unsigned __int8)__sub_4229E0_byte_4398A0[v27];
    *(_BYTE *)(_this + 2 * n + 280753) = v27;
    v29 = 2 * n + 1 == v28;
    v24 = v29 + v27;
  }
  *(_DWORD *)(_this + 278704) = 15;
  sub_4118A0((_BYTE *)(_this + 279984), (char *)(_this + 280496));
  *(_DWORD *)(_this + 278844) = 0;
  *(_DWORD *)(_this + 278784) = 64;
  *(_DWORD *)(_this + 278828) = 0;
  *(_DWORD *)(_this + 278788) = 128;
  *(_DWORD *)(_this + 278812) = 0;
  *(_DWORD *)(_this + 278800) = 192;
  *(_DWORD *)(_this + 278796) = 0;
  *(_DWORD *)(_this + 278804) = 384;
  *(_DWORD *)(_this + 278780) = 0;
  *(_DWORD *)(_this + 278816) = 576;
  *(_DWORD *)(_this + 278820) = 1152;
  *(_DWORD *)(_this + 278832) = 1728;
  *(_DWORD *)(_this + 278836) = 3456;
  *(_DWORD *)(_this + 278848) = 5184;
  *(_DWORD *)(_this + 278852) = 10368;
  return _this;
}

#undef FILE
#undef sub_4118A0
#undef sub_4349F0
