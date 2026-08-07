// sub_4108C0 @ 0x004108C0 — __cdecl
// Extracted from BMF.cpp:14623-14784 by extract.py per incdec.md.

typedef int t_sub_4108C0_buf[0x10000];
static t_sub_4108C0_buf& __sub_4108C0_buf = *(t_sub_4108C0_buf*)0x00443380;
typedef __int128 t_sub_4108C0_xmmword_4396C0;
static t_sub_4108C0_xmmword_4396C0& __sub_4108C0_xmmword_4396C0 = *(t_sub_4108C0_xmmword_4396C0*)0x004396C0;
typedef __int128 t_sub_4108C0_xmmword_4396D0;
static t_sub_4108C0_xmmword_4396D0& __sub_4108C0_xmmword_4396D0 = *(t_sub_4108C0_xmmword_4396D0*)0x004396D0;
typedef __int128 t_sub_4108C0_xmmword_4396E0;
static t_sub_4108C0_xmmword_4396E0& __sub_4108C0_xmmword_4396E0 = *(t_sub_4108C0_xmmword_4396E0*)0x004396E0;
typedef __int128 t_sub_4108C0_xmmword_4396F0;
static t_sub_4108C0_xmmword_4396F0& __sub_4108C0_xmmword_4396F0 = *(t_sub_4108C0_xmmword_4396F0*)0x004396F0;


PROBE_DECL(__sub_4108C0)
BMF_REALIGN BMF_SSE unsigned int __sub_4108C0(int Src, int i, int a3)
{
  PROBE_HIT(__sub_4108C0);
  _BYTE *v3; // edx
  _BYTE *v4; // edi
  unsigned int j; // esi
  __m128i si128; // xmm1
  __m128i v7; // xmm0
  unsigned int k; // eax
  int v9; // eax
  unsigned int m; // esi
  char v11; // cl
  int i_1; // ebx
  __m128i v13; // xmm1
  __m128i v14; // xmm0
  unsigned int n15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // ebx
  int v20; // esi
  int v21; // ecx
  int v22; // ecx
  unsigned int v23; // edi
  int v24; // ebx
  unsigned int v25; // esi
  char v26; // cl
  int v27; // ebx
  _BYTE *v28; // edx
  int v29; // [esp+0h] [ebp-120h]
  unsigned int n15_1; // [esp+0h] [ebp-120h]
  alignas(16) _BYTE v31[272]; // [esp+10h] [ebp-110h]

  v31[0] = 0;
  v3 = (_BYTE *)(Src + a3 * i);
  v4 = &v3[-i];
  v31[128] = -1;
  for ( j = 0; j < 7; ++j )
  {
    v31[2 * j + 1] = 4 * j + 2;
    v31[2 * j + 2] = 4 * j + 4;
  }
  si128 = _mm_load_si128((const __m128i *)&__sub_4108C0_xmmword_4396C0);
  v7 = _mm_load_si128((const __m128i *)&__sub_4108C0_xmmword_4396D0);
  v31[15] = 30;
  for ( k = 15; k < 0x7F; k += 16 )
  {
    *(__m128i *)&v31[k + 1] = v7;
    v7 = _mm_add_epi8(v7, si128);
  }
  v9 = 0;
  for ( m = 0; m < 7; ++m )
  {
    v31[2 * m + 129] = 2 * v9 - 3;
    v11 = 2 * v9 - 5;
    v9 -= 2;
    v31[2 * m + 130] = v11;
  }
  i_1 = i;
  v13 = _mm_load_si128((const __m128i *)&__sub_4108C0_xmmword_4396E0);
  v14 = _mm_load_si128((const __m128i *)&__sub_4108C0_xmmword_4396F0);
  n15 = 15;
  v31[143] = -31;
  do
  {
    *(__m128i *)&v31[n15 + 129] = v14;
    v14 = _mm_add_epi8(v14, v13);
    n15 += 16;
  }
  while ( n15 < 0x7F );
  v16 = a3 - 1;
  if ( a3 == 1 )
    goto LABEL_24;
  do
  {
    v17 = i - 1;
    if ( i_1 == 1 )
      goto LABEL_23;
    v29 = v16;
    do
    {
      v18 = (unsigned __int8)*--v4;
      v19 = (unsigned __int8)*(--v3 - 1);
      v20 = (unsigned __int8)v3[-i - 1];
      if ( v19 < v18 )
      {
        if ( v20 < v19 )
        {
          LOBYTE(v19) = *v4;
          goto LABEL_21;
        }
        if ( v20 <= v18 )
LABEL_20:
          LOBYTE(v19) = v18 + v19 - v20;
      }
      else
      {
        if ( v20 > v19 )
        {
          LOBYTE(v19) = *v4;
          goto LABEL_21;
        }
        if ( v20 >= v18 )
          goto LABEL_20;
      }
LABEL_21:
      v21 = (unsigned __int8)v31[(unsigned __int8)(*v3 - v19)];
      *v3 = v21;
      ++*(_DWORD *)&__sub_4108C0_buf[4 * v21];
      --v17;
    }
    while ( v17 );
    v16 = v29;
    i_1 = i;
LABEL_23:
    --v4;
    --v3;
    n15 = (unsigned __int8)v31[(unsigned __int8)(*v3 - v3[-i_1])];
    *v3 = n15;
    ++*(_DWORD *)&__sub_4108C0_buf[4 * n15];
    --v16;
  }
  while ( v16 );
LABEL_24:
  if ( i_1 != 1 )
  {
    n15 = i_1 - 1;
    v22 = (i_1 - 1) / 2;
    if ( v22 )
    {
      n15_1 = i_1 - 1;
      v23 = 0;
      v24 = 0;
      v25 = v22;
      do
      {
        v26 = v3[v24 - 2];
        ++v23;
        v3[v24 - 1] = v31[(unsigned __int8)(v3[v24 - 1] - v26)];
        v3[v24 - 2] = v31[(unsigned __int8)(v26 - v3[v24 - 3])];
        v24 -= 2;
      }
      while ( v23 < v25 );
      n15 = n15_1;
      v27 = 2 * v23 + 1;
    }
    else
    {
      v27 = 1;
    }
    if ( n15 > v27 - 1 )
    {
      v28 = &v3[-v27];
      n15 = (unsigned __int8)(*v28 - *(v28 - 1));
      *v28 = v31[(unsigned __int8)n15];
    }
  }
  return n15;
}

