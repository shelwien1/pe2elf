// sub_4135A0 @ 0x004135A0 — __fastcall
// Extracted from BMF.cpp:17716-17932 by extract.py per incdec.md.

typedef int t_sub_4135A0_Buffer_0;
static t_sub_4135A0_Buffer_0& __sub_4135A0_Buffer_0 = *(t_sub_4135A0_Buffer_0*)(blob1 + 0x00443378 - BMF_BLOB_BASE);
typedef char t_sub_4135A0_byte_4456F0;
static t_sub_4135A0_byte_4456F0& __sub_4135A0_byte_4456F0 = *(t_sub_4135A0_byte_4456F0*)(blob1 + 0x004456F0 - BMF_BLOB_BASE);
typedef int t_sub_4135A0_dword_4456E8;
static t_sub_4135A0_dword_4456E8& __sub_4135A0_dword_4456E8 = *(t_sub_4135A0_dword_4456E8*)(blob1 + 0x004456E8 - BMF_BLOB_BASE);
typedef int t_sub_4135A0_dword_4456EC;
static t_sub_4135A0_dword_4456EC& __sub_4135A0_dword_4456EC = *(t_sub_4135A0_dword_4456EC*)(blob1 + 0x004456EC - BMF_BLOB_BASE);
typedef int t_sub_4135A0_n0x2000;
static t_sub_4135A0_n0x2000& __sub_4135A0_n0x2000 = *(t_sub_4135A0_n0x2000*)(blob1 + 0x004456FC - BMF_BLOB_BASE);
typedef int t_sub_4135A0_n0x2000_0;
static t_sub_4135A0_n0x2000_0& __sub_4135A0_n0x2000_0 = *(t_sub_4135A0_n0x2000_0*)(blob1 + 0x004456F8 - BMF_BLOB_BASE);
typedef int t_sub_4135A0_n0x2000_1;
static t_sub_4135A0_n0x2000_1& __sub_4135A0_n0x2000_1 = *(t_sub_4135A0_n0x2000_1*)(blob1 + 0x004456F4 - BMF_BLOB_BASE);
typedef int t_sub_4135A0_n0x7F800000;
static t_sub_4135A0_n0x7F800000& __sub_4135A0_n0x7F800000 = *(t_sub_4135A0_n0x7F800000*)(blob1 + 0x004456E4 - BMF_BLOB_BASE);
typedef int t_sub_4135A0_n0x800000;
static t_sub_4135A0_n0x800000& __sub_4135A0_n0x800000 = *(t_sub_4135A0_n0x800000*)(blob1 + 0x004456E0 - BMF_BLOB_BASE);
typedef void * t_sub_4135A0_n256_1;
static t_sub_4135A0_n256_1& __sub_4135A0_n256_1 = *(t_sub_4135A0_n256_1*)(blob1 + 0x00445708 - BMF_BLOB_BASE);

static inline int __fwd_sub_4135A0_sub_413900(void *a0, int a1) { return __sub_413900((unsigned __int16 *)a0, a1); }
#define sub_413900 __fwd_sub_4135A0_sub_413900

PROBE_DECL(__sub_4135A0)
BMF_REALIGN BMF_SSE __attribute__((fastcall)) int __sub_4135A0(unsigned __int16 *a1, int n5, int a3, int n5a)
{
  PROBE_HIT(__sub_4135A0);
  __int16 v4; // di
  int n5a_1; // eax
  unsigned int __sub_4135A0_n0x2000; // edi
  unsigned int n5a_3; // esi
  unsigned int n5a_4; // eax
  __m128i v9; // xmm1
  __m128i v10; // xmm1
  int n0x2000_2; // ecx
  unsigned __int16 *v12; // edi
  unsigned int __sub_4135A0_n0x800000; // ebx
  int v14; // esi
  int n0x7F800000_1; // edi
  unsigned int v16; // ebx
  int v17; // ecx
  int v18; // eax
  unsigned int v19; // edx
  _BYTE *v20; // edi
  unsigned int n0x800000_2; // eax
  int v22; // eax
  int v23; // esi
  int n0x800000_3; // ebx
  int n0x800000_4; // eax
  int result; // eax
  unsigned __int16 *v27; // edi
  int n256; // edx
  bool v29; // cf
  unsigned __int16 *v30; // eax
  unsigned __int16 v31; // ax
  unsigned int __sub_4135A0_n0x2000_1; // [esp+0h] [ebp-40h]
  unsigned int n0x2000_3; // [esp+0h] [ebp-40h]
  int n5a_2; // [esp+8h] [ebp-38h]
  unsigned __int16 *v35; // [esp+Ch] [ebp-34h]
  unsigned __int16 *v37; // [esp+14h] [ebp-2Ch]
  unsigned int n0x2000_4; // [esp+18h] [ebp-28h]
  char v39; // [esp+18h] [ebp-28h]
  int __sub_4135A0_n0x7F800000; // [esp+1Ch] [ebp-24h]
  int n0x7F800000_2; // [esp+1Ch] [ebp-24h]
  int v42; // [esp+20h] [ebp-20h]
  int n0x800000_1; // [esp+24h] [ebp-1Ch]

  v4 = *a1;
  ::__sub_4135A0_n0x2000_1 = 0;
  n5a_1 = 6 - (n5a & 1);
  if ( n5a < 5 )
    n5a_1 = n5a;
  n5a_2 = n5a_1;
  v37 = a1 + 1;
  v35 = a1 + 1;
  __sub_4135A0_n0x2000 = v4 & 0x7FFF;
  ::__sub_4135A0_n0x2000 = __sub_4135A0_n0x2000;
  if ( n5a_1 )
  {
    if ( n5a_1 < 4 )
    {
      n0x2000_2 = 0;
      n5a_3 = 0;
    }
    else
    {
      n5a_3 = n5a_1 - (n5a_1 & 3);
      n5a_4 = 0;
      v9 = 0;
      do
      {
        v9 = _mm_add_epi32(v9, _mm_unpacklo_epi16(_mm_loadl_epi64((const __m128i *)&v37[n5a_4]), (__m128i)0LL));
        n5a_4 += 4;
      }
      while ( n5a_4 < n5a_3 );
      v35 = &a1[n5a_4 + 1];
      v10 = _mm_add_epi32(v9, _mm_srli_si128(v9, 8));
      n0x2000_2 = _mm_cvtsi128_si32(_mm_add_epi32(v10, _mm_srli_si128(v10, 4)));
    }
    if ( n5a_3 < n5a_2 )
    {
      __sub_4135A0_n0x2000_1 = __sub_4135A0_n0x2000;
      do
      {
        n0x2000_2 += v37[n5a_3];
        v12 = &a1[n5a_3++ + 2];
      }
      while ( n5a_3 < n5a_2 );
      v35 = v12;
      __sub_4135A0_n0x2000 = __sub_4135A0_n0x2000_1;
    }
    ::__sub_4135A0_n0x2000_1 = n0x2000_2;
  }
  else
  {
    n0x2000_2 = 0;
  }
  __sub_4135A0_n0x800000 = ::__sub_4135A0_n0x800000;
  __sub_4135A0_n0x7F800000 = ::__sub_4135A0_n0x7F800000;
  n0x2000_3 = n0x2000_2 + *v35;
  __sub_4135A0_n0x2000_0 = n0x2000_3;
  if ( (unsigned int)::__sub_4135A0_n0x800000 > 0x800000 )
  {
    n0x2000_4 = ::__sub_4135A0_n0x2000;
    goto LABEL_29;
  }
  v14 = __sub_4135A0_dword_4456E8;
  n0x7F800000_1 = ::__sub_4135A0_n0x7F800000;
  v42 = __sub_4135A0_dword_4456EC;
  n0x800000_1 = ::__sub_4135A0_n0x800000;
  do
  {
    ++v42;
    v16 = v14;
    v17 = v14;
    if ( (unsigned int)n0x7F800000_1 < 0x7F800000 )
    {
      v39 = 0;
    }
    else
    {
      if ( n0x7F800000_1 >= 0 )
      {
        __sub_4135A0_dword_4456E8 = ++v14;
        goto LABEL_27;
      }
      v39 = 1;
    }
    *(_BYTE *)__sub_4135A0_Buffer_0 = v39 + __sub_4135A0_byte_4456F0;
    v18 = ++__sub_4135A0_Buffer_0;
    if ( v14 )
    {
      n0x7F800000_2 = n0x7F800000_1;
      v19 = 0;
      v20 = (_BYTE *)v18;
      do
      {
        *v20 = v39 - 1;
        v20 = (_BYTE *)++__sub_4135A0_Buffer_0;
        v14 = v17 - v19++ - 1;
      }
      while ( v19 < v16 );
      n0x7F800000_1 = n0x7F800000_2;
      __sub_4135A0_dword_4456E8 = v17 - v16;
    }
    __sub_4135A0_byte_4456F0 = (unsigned int)n0x7F800000_1 >> 23;
LABEL_27:
    n0x800000_2 = n0x800000_1 << 8;
    n0x800000_1 = n0x800000_2;
    n0x7F800000_1 = (n0x7F800000_1 << 8) & 0x7FFFFFFF;
  }
  while ( n0x800000_2 <= 0x800000 );
  __sub_4135A0_n0x800000 = n0x800000_2;
  n0x2000_2 = ::__sub_4135A0_n0x2000_1;
  __sub_4135A0_n0x7F800000 = n0x7F800000_1;
  __sub_4135A0_n0x2000 = ::__sub_4135A0_n0x2000;
  __sub_4135A0_dword_4456EC = v42;
  n0x2000_4 = ::__sub_4135A0_n0x2000;
  n0x2000_3 = __sub_4135A0_n0x2000_0;
LABEL_29:
  v22 = __sub_4135A0_n0x800000 / n0x2000_4;
  v23 = __sub_4135A0_n0x800000 / n0x2000_4 * n0x2000_2;
  n0x800000_3 = __sub_4135A0_n0x800000 - v23;
  ::__sub_4135A0_n0x7F800000 = __sub_4135A0_n0x7F800000 + v23;
  n0x800000_4 = (n0x2000_3 - n0x2000_2) * v22;
  if ( n0x2000_3 < __sub_4135A0_n0x2000 )
    n0x800000_3 = n0x800000_4;
  ::__sub_4135A0_n0x800000 = n0x800000_3;
  if ( __sub_4135A0_n0x2000 > 0x2000 )
  {
    *a1 = 0x8000;
    v27 = a1 + 7;
    n256 = 256;
    v29 = a1 + 7 < v37;
    v30 = a1 + 7;
    if ( a1 + 7 >= v37 )
    {
      do
      {
        if ( *v30 < n256 )
          n256 = *v30;
        --v30;
      }
      while ( v30 >= v37 );
      v29 = v27 < v37;
    }
    if ( !v29 )
    {
      do
      {
        if ( (unsigned __int16)n256 <= 1u )
          v31 = *v27 - (*v27 >> 1);
        else
          v31 = (*v27 + 2) / 3;
        *v27 = v31;
        *a1 += v31;
        --v27;
      }
      while ( v27 >= v37 );
    }
  }
  *v35 += 32;
  result = *a1 + 32;
  *a1 = result;
  if ( n5a_2 >= 5 )
    return sub_413900(
             (unsigned __int16 *)__sub_4135A0_n256_1
           + 32512 * (n5a_2 & 1)
           + 254 * (((a1[1] + (result & 0x7FFF) + 96 - 2 * (unsigned int)a1[n5a_2 + 1]) >> 25) & 0xFFFFFFC0)
           + 254 * a3,
             (n5a - 5) >> 1);
  return result;
}

#undef sub_413900
