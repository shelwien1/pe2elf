// sub_417980 @ 0x00417980 — __fastcall
// Extracted from BMF.cpp:21828-22030 by extract.py per incdec.md.

typedef char t_sub_417980_buf_0[0x10000];
static t_sub_417980_buf_0& __sub_417980_buf_0 = *(t_sub_417980_buf_0*)0x00443440;
typedef char t_sub_417980_byte_445700;
static t_sub_417980_byte_445700& __sub_417980_byte_445700 = *(t_sub_417980_byte_445700*)0x00445700;

#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#define FILE FILE1

PROBE_DECL(__sub_417980)
__attribute__((force_align_arg_pointer)) BMF_SSE __attribute__((fastcall)) int __sub_417980(int a1, int a2, int i, int a4, int a5)
{
  PROBE_HIT(__sub_417980);
  int i_1; // eax
  int j; // esi
  char *v8; // eax
  int v9; // edx
  _BYTE *v10; // eax
  char v11; // fps
  char v12; // cl
  int v13; // edx
  int n0x2000_4; // edx
  unsigned int n0x2000_2; // eax
  unsigned int n0x2000_5; // ecx
  unsigned int n0x2000; // ecx
  unsigned int k; // eax
  __int16 v19; // si
  int k_1; // ecx
  unsigned int m; // edx
  unsigned int n0x2000_3; // edx
  unsigned int n0x2000_6; // eax
  unsigned int n0x2000_1; // eax
  __m128i si128; // xmm1
  __m128i v26; // xmm2
  __m128i v27; // xmm3
  char v28; // fps
  char v29; // fps
  char v30; // fps
  char v31; // fps
  char v32; // fps
  unsigned int n; // edx
  unsigned int n8; // eax
  int v35; // esi
  unsigned int n0x18; // ebx
  char v37; // fps
  int v38; // ecx

  i_1 = i;
  __sub_417980_byte_445700 = 1;
  *(_DWORD *)a1 = i;
  *(_DWORD *)(a1 + 4) = a4;
  *(_DWORD *)(a1 + 8) = a5;
  *(_DWORD *)(a1 + 12) = a5;
  *(_DWORD *)(a1 + 1078204) = 0;
  *(_DWORD *)(a1 + 1078240) = 0;
  for ( j = 0; j < 5; ++j )
  {
    v8 = (char *)__op_new(8 * i_1 + 128);
    *(_DWORD *)(a1 + 4 * j + 56) = v8;
    *(_DWORD *)(a1 + 4 * j + 76) = v8 + 64;
    i_1 = *(_DWORD *)a1;
    if ( *(int *)a1 > -16 )
    {
      v9 = 0;
      do
      {
        *(_WORD *)(*(_DWORD *)(a1 + 4 * j + 56) + 8 * v9) = 0;
        *(_BYTE *)(*(_DWORD *)(a1 + 4 * j + 56) + 8 * v9 + 7) = 1;
        *(_BYTE *)(*(_DWORD *)(a1 + 4 * j + 56) + 8 * v9 + 6) = 1;
        *(_BYTE *)(*(_DWORD *)(a1 + 4 * j + 56) + 8 * v9 + 5) = 1;
        *(_BYTE *)(*(_DWORD *)(a1 + 4 * j + 56) + 8 * v9 + 4) = 1;
        *(_BYTE *)(*(_DWORD *)(a1 + 4 * j + 56) + 8 * v9 + 3) = 1;
        *(_BYTE *)(*(_DWORD *)(a1 + 4 * j + 56) + 8 * v9 + 2) = 1;
        i_1 = *(_DWORD *)a1;
        ++v9;
      }
      while ( v9 < *(_DWORD *)a1 + 16 );
    }
  }
  v10 = __op_new(i_1 + 1);
  *(_DWORD *)(a1 + 1078684) = v10;
  *v10 = 0;
  if ( *(int *)a1 > 0 )
  {
    v12 = 0;
    v13 = 0;
    do
    {
      v12 += v13 == 2 << v12;
      *(_BYTE *)(*(_DWORD *)(a1 + 1078684) + v13++ + 1) = v12;
    }
    while ( v13 < *(_DWORD *)a1 );
  }
  n0x2000_4 = a1 & 0xF;
  n0x2000_2 = n0x2000_4;
  if ( (a1 & 0xF) != 0 )
  {
    if ( (n0x2000_4 & 1) != 0 )
    {
      n0x2000 = 0;
      goto LABEL_15;
    }
    n0x2000_2 = (unsigned int)(16 - n0x2000_4) >> 1;
    n0x2000_5 = 0;
    do
      *(_WORD *)(a1 + 2 * n0x2000_5++ + 6059440) = 0;
    while ( n0x2000_5 < n0x2000_2 );
  }
  n0x2000 = 0x2000 - (-n0x2000_2 & 0x1F);
  do
  {
    *(_OWORD *)(a1 + 2 * n0x2000_2 + 6059440) = 0;
    *(_OWORD *)(a1 + 2 * n0x2000_2 + 6059456) = 0;
    *(_OWORD *)(a1 + 2 * n0x2000_2 + 6059472) = 0;
    *(_OWORD *)(a1 + 2 * n0x2000_2 + 6059488) = 0;
    n0x2000_2 += 32;
  }
  while ( n0x2000_2 < n0x2000 );
LABEL_15:
  while ( n0x2000 < 0x2000 )
    *(_WORD *)(a1 + 2 * n0x2000++ + 6059440) = 0;
  for ( k = 0; k < 0x2000; ++k )
  {
    v19 = *(_WORD *)(a1 + 2 * k + 6059440);
    k_1 = k;
    for ( m = 0; m < 0xD; ++m )
    {
      v19 += v19 + (k_1 & 1);
      k_1 >>= 1;
    }
    *(_WORD *)(a1 + 2 * k + 6059440) = v19;
  }
  n0x2000_3 = a1 & 0xF;
  if ( (a1 & 0xF) != 0 )
  {
    if ( (a1 & 1) != 0 )
    {
      n0x2000_1 = 0;
      goto LABEL_26;
    }
    n0x2000_3 = (16 - (a1 & 0xFu)) >> 1;
    n0x2000_6 = 0;
    do
      *(_WORD *)(a1 + 2 * n0x2000_6++ + 6059440) *= 8;
    while ( n0x2000_6 < n0x2000_3 );
  }
  n0x2000_1 = 0x2000 - (-n0x2000_3 & 0x1F);
  do
  {
    si128 = _mm_load_si128((const __m128i *)(a1 + 2 * n0x2000_3 + 6059456));
    v26 = _mm_load_si128((const __m128i *)(a1 + 2 * n0x2000_3 + 6059472));
    v27 = _mm_load_si128((const __m128i *)(a1 + 2 * n0x2000_3 + 6059488));
    *(__m128i *)(a1 + 2 * n0x2000_3 + 6059440) = _mm_slli_epi16(
                                                   _mm_load_si128((const __m128i *)(a1 + 2 * n0x2000_3 + 6059440)),
                                                   3u);
    *(__m128i *)(a1 + 2 * n0x2000_3 + 6059456) = _mm_slli_epi16(si128, 3u);
    *(__m128i *)(a1 + 2 * n0x2000_3 + 6059472) = _mm_slli_epi16(v26, 3u);
    *(__m128i *)(a1 + 2 * n0x2000_3 + 6059488) = _mm_slli_epi16(v27, 3u);
    n0x2000_3 += 32;
  }
  while ( n0x2000_3 < n0x2000_1 );
LABEL_26:
  while ( n0x2000_1 < 0x2000 )
    *(_WORD *)(a1 + 2 * n0x2000_1++ + 6059440) *= 8;
  sub_4349F0((char *)(a1 + 3104),0,0x100000);
  *(_DWORD *)(a1 + 28) = 0;
  *(_DWORD *)(a1 + 24) = 0;
  *(_DWORD *)(a1 + 20) = 0;
  sub_4349F0((char *)(a1 + 6075824),255,385024);
  sub_4349F0((char *)(a1 + 6460848),255,217600);
  sub_4349F0((char *)(a1 + 6678448),255,1424000);
  sub_4349F0(__sub_417980_buf_0,0,8193);
  *(_QWORD *)(a1 + 1078216) = 0;
  *(_QWORD *)(a1 + 1078224) = 0;
  for ( n = 0; n < 0x40000; ++n )
  {
    *(_WORD *)(a1 + 4 * n + 1078696) = 0x2000;
    *(_WORD *)(a1 + 4 * n + 1078698) = 0x2000;
  }
  n8 = 0;
  do
  {
    v35 = 6 * n8;
    *(_WORD *)(a1 + 2 * v35 + 1051680) = 40;
    ++n8;
    *(_WORD *)(a1 + 2 * v35 + 1051682) = 16;
    *(_WORD *)(a1 + 2 * v35 + 1051684) = 512;
    *(_WORD *)(a1 + 2 * v35 + 1051686) = 40;
    *(_WORD *)(a1 + 2 * v35 + 1051688) = 16;
    *(_WORD *)(a1 + 2 * v35 + 1051690) = 512;
  }
  while ( n8 < 8 );
  n0x18 = 0;
  sub_4349F0((char *)(a1 + 1051776),0,24576);
  *(_DWORD *)(a1 + 1078236) = __op_new(2 * *(_DWORD *)(a1 + 4) * *(_DWORD *)a1);
  *(_WORD *)(a1 + 1076352) = 4;
  *(_WORD *)(a1 + 1076354) = 4;
  *(_WORD *)(a1 + 1076356) = 72;
  sub_4349F0((char *)(a1 + 1076358),0,1536);
  do
  {
    v38 = 6 * n0x18;
    *(_WORD *)(a1 + 2 * v38 + 1077894) = 4;
    ++n0x18;
    *(_WORD *)(a1 + 2 * v38 + 1077896) = 4;
    *(_WORD *)(a1 + 2 * v38 + 1077898) = 72;
    *(_WORD *)(a1 + 2 * v38 + 1077900) = 4;
    *(_WORD *)(a1 + 2 * v38 + 1077902) = 4;
    *(_WORD *)(a1 + 2 * v38 + 1077904) = 72;
  }
  while ( n0x18 < 0x18 );
  return a1;
}

#undef FILE
#undef sub_4349F0
