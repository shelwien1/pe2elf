// sub_40E590 @ 0x0040E590 — __thiscall
// Extracted from BMF.cpp:12363-12536 by extract.py per incdec.md.

typedef int t_sub_40E590_dword_4394E0[0x10000];
static t_sub_40E590_dword_4394E0& __sub_40E590_dword_4394E0 = *(t_sub_40E590_dword_4394E0*)(blob1 + 0x004394E0 - BMF_BLOB_BASE);
typedef int t_sub_40E590_dword_4394E4[0x10000];
static t_sub_40E590_dword_4394E4& __sub_40E590_dword_4394E4 = *(t_sub_40E590_dword_4394E4*)(blob1 + 0x004394E4 - BMF_BLOB_BASE);
typedef int t_sub_40E590_dword_4394E8[0x10000];
static t_sub_40E590_dword_4394E8& __sub_40E590_dword_4394E8 = *(t_sub_40E590_dword_4394E8*)(blob1 + 0x004394E8 - BMF_BLOB_BASE);
typedef int t_sub_40E590_dword_4394EC[13];
static t_sub_40E590_dword_4394EC& __sub_40E590_dword_4394EC = *(t_sub_40E590_dword_4394EC*)(blob1 + 0x004394EC - BMF_BLOB_BASE);
typedef __int128 t_sub_40E590_xmmword_439520;
static t_sub_40E590_xmmword_439520& __sub_40E590_xmmword_439520 = *(t_sub_40E590_xmmword_439520*)(blob1 + 0x00439520 - BMF_BLOB_BASE);
typedef __int128 t_sub_40E590_xmmword_439530;
static t_sub_40E590_xmmword_439530& __sub_40E590_xmmword_439530 = *(t_sub_40E590_xmmword_439530*)(blob1 + 0x00439530 - BMF_BLOB_BASE);


// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#define FILE FILE1

PROBE_DECL(__sub_40E590)
BMF_REALIGN BMF_SSE __attribute__((thiscall)) _DWORD *__sub_40E590(_DWORD *_this, int i, char a3)
{
  PROBE_HIT(__sub_40E590);
  int v4; // eax
  int v5; // ecx
  int v6; // edx
  int n3; // edx
  unsigned int n0x200; // edi
  _DWORD *v9; // ecx
  BOOL v10; // eax
  int v11; // ebx
  BOOL v12; // eax
  _DWORD *v13; // eax
  void *v14; // eax
  int v15; // ecx
  unsigned int n0x400_2; // edx
  unsigned int n0x400_4; // ecx
  int v18; // eax
  __m128i si128; // xmm1
  unsigned int n0x400; // ecx
  __m128i v21; // xmm0
  __m128i v22; // xmm0
  __m128i v23; // xmm0
  __m128i v24; // xmm0
  int j; // eax
  unsigned int n0x400_3; // eax
  unsigned int n0x400_5; // edx
  __m128i v28; // xmm1
  unsigned int n0x400_1; // edx
  __m128i v30; // xmm0
  __m128i v31; // xmm0
  __m128i v32; // xmm0
  __m128i v33; // xmm0
  _DWORD *this_1; // [esp+0h] [ebp-20h]
  int v36; // [esp+4h] [ebp-1Ch]

  v4 = 0;
  do
  {
    v36 = v4;
    this_1 = _this;
    v5 = 1040 * v4;
    *(_DWORD *)((char *)_this + v5 + 108) = __sub_40E590_dword_4394E0[4 * v4];
    *(_DWORD *)((char *)_this + v5 + 112) = __sub_40E590_dword_4394E4[4 * v4];
    v6 = __sub_40E590_dword_4394EC[4 * v4];
    *(_DWORD *)((char *)_this + v5 + 116) = __sub_40E590_dword_4394E8[4 * v4];
    *(_DWORD *)((char *)_this + v5 + 120) = v6;
    n3 = 0;
    n0x200 = 0;
    v9 = _this + 260 * v4;
    do
    {
      v10 = n3 <= 3 && 2 * n0x200 == v9[n3 + 27];
      v11 = n3 + v10;
      *((_BYTE *)v9 + 2 * n0x200 + 124) = n3 + v10 + 1;
      v12 = n3 + v10 <= 3 && 2 * n0x200 + 1 == v9[v11 + 27];
      n3 = v11 + v12;
      *((_BYTE *)v9 + 2 * n0x200++ + 125) = v11 + v12 + 1;
    }
    while ( n0x200 < 0x200 );
    _this = this_1;
    v4 = v36 + 1;
  }
  while ( (unsigned int)(v36 + 1) < 4 );
  v13 = __op_new(8 * i + 8);
  this_1[24] = v13;
  v13 += 2;
  this_1[23] = v13;
  this_1[22] = 0;
  this_1[21] = 0;
  *(v13 - 2) = 0;
  *(v13 - 1) = this_1[22];
  this_1[19] = __op_new(i + 2);
  v14 = __op_new(i + 2);
  v15 = this_1[19];
  this_1[20] = v14;
  this_1[17] = v15 + 2;
  *(_BYTE *)(v15 + 1) = a3;
  *(_BYTE *)this_1[19] = a3;
  this_1[9] = -384;
  this_1[15] = -384;
  this_1[2] = -384;
  this_1[8] = -384;
  n0x400_2 = (unsigned __int8)this_1 & 0xF;
  if ( ((unsigned __int8)this_1 & 0xF) != 0 )
  {
    if ( ((unsigned __int8)this_1 & 3) != 0 )
    {
      n0x400 = 0;
      goto LABEL_17;
    }
    n0x400_2 = (16 - n0x400_2) >> 2;
    n0x400_4 = 0;
    v18 = 0;
    do
    {
      this_1[n0x400_4 + 1068] = v18 + 1023;
      --v18;
      ++n0x400_4;
    }
    while ( n0x400_4 < n0x400_2 );
  }
  si128 = _mm_load_si128((const __m128i *)&__sub_40E590_xmmword_439520);
  n0x400 = 1024 - (-(char)n0x400_2 & 0xF);
  v21 = _mm_unpacklo_epi64(
          _mm_unpacklo_epi32(_mm_cvtsi32_si128(1023 - n0x400_2), _mm_cvtsi32_si128(1022 - n0x400_2)),
          _mm_unpacklo_epi32(_mm_cvtsi32_si128(1021 - n0x400_2), _mm_cvtsi32_si128(1020 - n0x400_2)));
  do
  {
    *(__m128i *)&this_1[n0x400_2 + 1068] = v21;
    v22 = _mm_add_epi32(v21, si128);
    *(__m128i *)&this_1[n0x400_2 + 1072] = v22;
    v23 = _mm_add_epi32(v22, si128);
    *(__m128i *)&this_1[n0x400_2 + 1076] = v23;
    v24 = _mm_add_epi32(v23, si128);
    *(__m128i *)&this_1[n0x400_2 + 1080] = v24;
    v21 = _mm_add_epi32(v24, si128);
    n0x400_2 += 16;
  }
  while ( n0x400_2 < n0x400 );
LABEL_17:
  for ( j = -n0x400; n0x400 < 0x400; ++n0x400 )
  {
    this_1[n0x400 + 1068] = j + 1023;
    --j;
  }
  n0x400_3 = ((_BYTE)this_1 + 12) & 0xF;
  if ( (((_BYTE)this_1 + 12) & 0xF) != 0 )
  {
    if ( (((_BYTE)this_1 + 12) & 3) != 0 )
    {
      n0x400_1 = 0;
      goto LABEL_25;
    }
    n0x400_3 = (16 - n0x400_3) >> 2;
    n0x400_5 = 0;
    do
    {
      this_1[n0x400_5 + 2091] = n0x400_5;
      ++n0x400_5;
    }
    while ( n0x400_5 < n0x400_3 );
  }
  v28 = _mm_load_si128((const __m128i *)&__sub_40E590_xmmword_439530);
  n0x400_1 = 1024 - (-n0x400_3 & 0xF);
  v30 = _mm_unpacklo_epi64(
          _mm_unpacklo_epi32(_mm_cvtsi32_si128(n0x400_3), _mm_cvtsi32_si128(n0x400_3 + 1)),
          _mm_unpacklo_epi32(_mm_cvtsi32_si128(n0x400_3 + 2), _mm_cvtsi32_si128(n0x400_3 + 3)));
  do
  {
    *(__m128i *)&this_1[n0x400_3 + 2091] = v30;
    v31 = _mm_add_epi32(v30, v28);
    *(__m128i *)&this_1[n0x400_3 + 2095] = v31;
    v32 = _mm_add_epi32(v31, v28);
    *(__m128i *)&this_1[n0x400_3 + 2099] = v32;
    v33 = _mm_add_epi32(v32, v28);
    *(__m128i *)&this_1[n0x400_3 + 2103] = v33;
    v30 = _mm_add_epi32(v33, v28);
    n0x400_3 += 16;
  }
  while ( n0x400_3 < n0x400_1 );
LABEL_25:
  while ( n0x400_1 < 0x400 )
  {
    this_1[n0x400_1 + 2091] = n0x400_1;
    ++n0x400_1;
  }
  return this_1;
}

#undef FILE
