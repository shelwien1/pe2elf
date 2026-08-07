// sub_413900 @ 0x00413900 — __thiscall
// Extracted from BMF.cpp:17935-18295 by extract.py per incdec.md.

typedef int t_sub_413900_Buffer_0;
static t_sub_413900_Buffer_0& __sub_413900_Buffer_0 = *(t_sub_413900_Buffer_0*)(blob1 + 0x00443378 - BMF_BLOB_BASE);
typedef char t_sub_413900_byte_4456F0;
static t_sub_413900_byte_4456F0& __sub_413900_byte_4456F0 = *(t_sub_413900_byte_4456F0*)(blob1 + 0x004456F0 - BMF_BLOB_BASE);
typedef unsigned char t_sub_413900_byte_445714[0x10000];
static t_sub_413900_byte_445714& __sub_413900_byte_445714 = *(t_sub_413900_byte_445714*)(blob1 + 0x00445714 - BMF_BLOB_BASE);
typedef unsigned char t_sub_413900_byte_445715[0x10000];
static t_sub_413900_byte_445715& __sub_413900_byte_445715 = *(t_sub_413900_byte_445715*)(blob1 + 0x00445715 - BMF_BLOB_BASE);
typedef unsigned char t_sub_413900_byte_445716[0x10000];
static t_sub_413900_byte_445716& __sub_413900_byte_445716 = *(t_sub_413900_byte_445716*)(blob1 + 0x00445716 - BMF_BLOB_BASE);
typedef int t_sub_413900_dword_445660[32];
static t_sub_413900_dword_445660& __sub_413900_dword_445660 = *(t_sub_413900_dword_445660*)(blob1 + 0x00445660 - BMF_BLOB_BASE);
typedef int t_sub_413900_dword_4456E8;
static t_sub_413900_dword_4456E8& __sub_413900_dword_4456E8 = *(t_sub_413900_dword_4456E8*)(blob1 + 0x004456E8 - BMF_BLOB_BASE);
typedef int t_sub_413900_dword_4456EC;
static t_sub_413900_dword_4456EC& __sub_413900_dword_4456EC = *(t_sub_413900_dword_4456EC*)(blob1 + 0x004456EC - BMF_BLOB_BASE);
typedef int t_sub_413900_n0x2000;
static t_sub_413900_n0x2000& __sub_413900_n0x2000 = *(t_sub_413900_n0x2000*)(blob1 + 0x004456FC - BMF_BLOB_BASE);
typedef int t_sub_413900_n0x2000_0;
static t_sub_413900_n0x2000_0& __sub_413900_n0x2000_0 = *(t_sub_413900_n0x2000_0*)(blob1 + 0x004456F8 - BMF_BLOB_BASE);
typedef int t_sub_413900_n0x2000_1;
static t_sub_413900_n0x2000_1& __sub_413900_n0x2000_1 = *(t_sub_413900_n0x2000_1*)(blob1 + 0x004456F4 - BMF_BLOB_BASE);
typedef int t_sub_413900_n0x7F800000;
static t_sub_413900_n0x7F800000& __sub_413900_n0x7F800000 = *(t_sub_413900_n0x7F800000*)(blob1 + 0x004456E4 - BMF_BLOB_BASE);
typedef int t_sub_413900_n0x800000;
static t_sub_413900_n0x800000& __sub_413900_n0x800000 = *(t_sub_413900_n0x800000*)(blob1 + 0x004456E0 - BMF_BLOB_BASE);
typedef int t_sub_413900_n0x88;
static t_sub_413900_n0x88& __sub_413900_n0x88 = *(t_sub_413900_n0x88*)(blob1 + 0x00445704 - BMF_BLOB_BASE);
typedef int t_sub_413900_n8_0;
static t_sub_413900_n8_0& __sub_413900_n8_0 = *(t_sub_413900_n8_0*)(blob1 + 0x00445710 - BMF_BLOB_BASE);
typedef int t_sub_413900_n8_1;
static t_sub_413900_n8_1& __sub_413900_n8_1 = *(t_sub_413900_n8_1*)(blob1 + 0x0044570C - BMF_BLOB_BASE);


PROBE_DECL(__sub_413900)
BMF_REALIGN BMF_SSE __attribute__((thiscall)) int __sub_413900(unsigned __int16 *_this, int n2)
{
  PROBE_HIT(__sub_413900);
  int n4; // edx
  unsigned __int16 *v3; // ebx
  unsigned int n4_2; // edx
  unsigned int n4_3; // eax
  __m128i v6; // xmm1
  __m128i v7; // xmm1
  int v8; // esi
  int v9; // edi
  int __sub_413900_n0x7F800000; // edi
  unsigned int __sub_413900_n0x800000; // ebx
  int v12; // edx
  unsigned int v13; // esi
  int v14; // ebx
  int v15; // eax
  unsigned int v16; // ecx
  _BYTE *v17; // edi
  unsigned int n0x800000_2; // eax
  int v19; // eax
  int v20; // edx
  int n0x800000_6; // ebx
  int n0x7F800000_6; // edx
  int n0x800000_5; // eax
  __int16 v24; // di
  int v25; // edi
  unsigned __int16 *v26; // ecx
  BOOL v27; // ebx
  int v28; // esi
  int v29; // eax
  int n0x7F800000_3; // esi
  unsigned int v31; // edx
  int v32; // ecx
  int v33; // ebx
  unsigned int v34; // edi
  _BYTE *v35; // esi
  unsigned int n0x800000_4; // esi
  unsigned __int16 n0x4000; // dx
  unsigned int v38; // edx
  unsigned __int16 v39; // di
  unsigned int v40; // edx
  unsigned __int16 v41; // di
  __int16 v42; // di
  unsigned int v43; // esi
  unsigned int v44; // edi
  unsigned int v45; // esi
  int v46; // edx
  bool v47; // cc
  unsigned int v48; // [esp+0h] [ebp-44h]
  unsigned __int16 *v49; // [esp+0h] [ebp-44h]
  int v50; // [esp+0h] [ebp-44h]
  unsigned __int16 *v51; // [esp+4h] [ebp-40h]
  unsigned int v52; // [esp+8h] [ebp-3Ch]
  int v53; // [esp+8h] [ebp-3Ch]
  unsigned int v54; // [esp+Ch] [ebp-38h]
  char v55; // [esp+Ch] [ebp-38h]
  int v56; // [esp+Ch] [ebp-38h]
  int n0x7F800000_1; // [esp+10h] [ebp-34h]
  int n0x7F800000_2; // [esp+10h] [ebp-34h]
  int v59; // [esp+10h] [ebp-34h]
  int v60; // [esp+14h] [ebp-30h]
  int i; // [esp+14h] [ebp-30h]
  unsigned __int16 *this_1; // [esp+18h] [ebp-2Ch]
  unsigned __int16 *this_2; // [esp+18h] [ebp-2Ch]
  unsigned int n4_1; // [esp+1Ch] [ebp-28h]
  int v65; // [esp+20h] [ebp-24h]
  int v66; // [esp+24h] [ebp-20h]
  int n0x7F800000_5; // [esp+28h] [ebp-1Ch]
  int n0x7F800000_4; // [esp+28h] [ebp-1Ch]
  int n0x7F800000_7; // [esp+28h] [ebp-1Ch]
  char v70; // [esp+2Ch] [ebp-18h]
  int n0x800000_1; // [esp+30h] [ebp-14h]
  unsigned int n0x800000_3; // [esp+30h] [ebp-14h]
  int v73; // [esp+34h] [ebp-10h]

  n4 = *((unsigned __int8 *)__sub_413900_dword_445660 + n2);
  n4_1 = n4;
  v3 = _this + 2;
  __sub_413900_n0x2000_1 = 0;
  v51 = _this + 2;
  if ( n4 )
  {
    if ( n4 < 4 )
    {
      v8 = 0;
      n4_2 = 0;
    }
    else
    {
      n4_2 = n4 - (n4 & 3);
      n4_3 = 0;
      v6 = 0;
      do
      {
        v6 = _mm_add_epi32(v6, _mm_unpacklo_epi16(_mm_loadl_epi64((const __m128i *)&v3[n4_3]), (__m128i)0LL));
        n4_3 += 4;
      }
      while ( n4_3 < n4_2 );
      v51 = _this + n4_3 + 2;
      v7 = _mm_add_epi32(v6, _mm_srli_si128(v6, 8));
      v8 = _mm_cvtsi128_si32(_mm_add_epi32(v7, _mm_srli_si128(v7, 4)));
    }
    if ( n4_2 < n4_1 )
    {
      do
      {
        v8 += v3[n4_2];
        v9 = (int)&v3[++n4_2];
      }
      while ( n4_2 < n4_1 );
      v51 = (unsigned __int16 *)v9;
    }
    __sub_413900_n0x2000_1 = v8;
  }
  else
  {
    v8 = 0;
  }
  __sub_413900_n0x7F800000 = ::__sub_413900_n0x7F800000;
  __sub_413900_n0x800000 = ::__sub_413900_n0x800000;
  n0x7F800000_1 = ::__sub_413900_n0x7F800000;
  v52 = v8 + *v51;
  __sub_413900_n0x2000_0 = v52;
  v48 = *_this;
  __sub_413900_n0x2000 = v48;
  if ( (unsigned int)::__sub_413900_n0x800000 > 0x800000 )
  {
    v54 = __sub_413900_n0x2000;
    goto LABEL_26;
  }
  v12 = __sub_413900_dword_4456E8;
  n0x800000_1 = ::__sub_413900_n0x800000;
  v60 = __sub_413900_dword_4456EC;
  this_1 = _this;
  do
  {
    ++v60;
    v13 = v12;
    v14 = v12;
    if ( (unsigned int)__sub_413900_n0x7F800000 < 0x7F800000 )
    {
      v55 = 0;
    }
    else
    {
      if ( __sub_413900_n0x7F800000 >= 0 )
      {
        __sub_413900_dword_4456E8 = ++v12;
        goto LABEL_24;
      }
      v55 = 1;
    }
    *(_BYTE *)__sub_413900_Buffer_0 = v55 + __sub_413900_byte_4456F0;
    v15 = ++__sub_413900_Buffer_0;
    if ( v12 )
    {
      n0x7F800000_2 = __sub_413900_n0x7F800000;
      v16 = 0;
      v17 = (_BYTE *)v15;
      do
      {
        *v17 = v55 - 1;
        v17 = (_BYTE *)++__sub_413900_Buffer_0;
        v12 = v14 - v16++ - 1;
      }
      while ( v16 < v13 );
      __sub_413900_n0x7F800000 = n0x7F800000_2;
      __sub_413900_dword_4456E8 = v14 - v13;
    }
    __sub_413900_byte_4456F0 = (unsigned int)__sub_413900_n0x7F800000 >> 23;
LABEL_24:
    n0x800000_2 = n0x800000_1 << 8;
    n0x800000_1 = n0x800000_2;
    __sub_413900_n0x7F800000 = (__sub_413900_n0x7F800000 << 8) & 0x7FFFFFFF;
  }
  while ( n0x800000_2 <= 0x800000 );
  __sub_413900_n0x800000 = n0x800000_2;
  _this = this_1;
  n0x7F800000_1 = __sub_413900_n0x7F800000;
  __sub_413900_dword_4456EC = v60;
  v8 = __sub_413900_n0x2000_1;
  v52 = __sub_413900_n0x2000_0;
  v48 = __sub_413900_n0x2000;
  v54 = __sub_413900_n0x2000;
LABEL_26:
  v19 = __sub_413900_n0x800000 / v54;
  v20 = __sub_413900_n0x800000 / v54 * v8;
  n0x800000_6 = __sub_413900_n0x800000 - v20;
  n0x7F800000_6 = n0x7F800000_1 + v20;
  n0x800000_5 = (v52 - v8) * v19;
  if ( v52 < v48 )
    n0x800000_6 = n0x800000_5;
  if ( *_this > 0x4000u )
  {
    n0x7F800000_7 = n0x7F800000_6;
    v39 = *(_this + 2) - (*(_this + 2) >> 1);
    v40 = *(_this + 3);
    *(_this + 2) = v39;
    LOWORD(v40) = v40 - (v40 >> 1);
    *(_this + 3) = v40;
    LOWORD(v40) = v39 + v40;
    v41 = *(_this + 4) - (*(_this + 4) >> 1);
    *(_this + 4) = v41;
    v42 = v40 + v41;
    LOWORD(v40) = *(_this + 5) - (*(_this + 5) >> 1);
    v43 = *(_this + 6);
    *(_this + 5) = v40;
    LOWORD(v43) = v43 - (v43 >> 1);
    *(_this + 6) = v43;
    LOWORD(v43) = v42 + v40 + v43;
    LOWORD(v40) = *(_this + 7) - (*(_this + 7) >> 1);
    v44 = *(_this + 8);
    *(_this + 7) = v40;
    LOWORD(v40) = v43 + v40;
    LOWORD(v44) = v44 - (v44 >> 1);
    v45 = *(_this + 9);
    *(_this + 8) = v44;
    LOWORD(v44) = v40 + v44;
    LOWORD(v45) = v45 - (v45 >> 1);
    v46 = *(_this + 1);
    v50 = v46;
    *(_this + 9) = v45;
    *_this = v44 + v45;
    v47 = v46 <= 4 * __sub_413900_n8_1;
    n0x7F800000_6 = n0x7F800000_7;
    if ( v47 )
    {
      n0x800000_5 = 4 * (v50 > __sub_413900_n8_1);
      v24 = v50 - n0x800000_5;
      *(_this + 1) = v50 - n0x800000_5;
    }
    else
    {
      v24 = v50 - 16;
      *(_this + 1) = v50 - 16;
    }
  }
  else
  {
    v24 = *(_this + 1);
  }
  *v51 += v24;
  *_this += *(_this + 1);
  if ( n2 >= 2 )
  {
    n0x7F800000_5 = n0x7F800000_6;
    v66 = (unsigned __int8)__sub_413900_byte_445715[4 * n4_1];
    v56 = n2 - (unsigned __int8)__sub_413900_byte_445714[4 * n4_1];
    v59 = 0;
    n0x800000_3 = n0x800000_6;
    this_2 = _this;
    for ( i = 1; ; i *= 2 )
    {
      v25 = (int)&this_2[2 * (unsigned __int8)__sub_413900_byte_445716[4 * n4_1] + 8];
      v26 = (unsigned __int16 *)(v25 + 4 * (i + v59));
      v65 = v26[1];
      v27 = (v66 & v56) != 0;
      v28 = *v26;
      if ( n0x800000_3 > 0x800000 )
        goto LABEL_46;
      v29 = __sub_413900_dword_4456E8;
      v53 = *v26;
      n0x7F800000_3 = n0x7F800000_5;
      v73 = __sub_413900_dword_4456EC;
      v49 = (unsigned __int16 *)(v25 + 4 * (i + v59));
      do
      {
        v31 = v29;
        v32 = v29;
        if ( (unsigned int)n0x7F800000_3 < 0x7F800000 )
        {
          v70 = 0;
        }
        else
        {
          if ( n0x7F800000_3 >= 0 )
          {
            __sub_413900_dword_4456E8 = ++v29;
            goto LABEL_44;
          }
          v70 = 1;
        }
        *(_BYTE *)__sub_413900_Buffer_0 = v70 + __sub_413900_byte_4456F0;
        v33 = ++__sub_413900_Buffer_0;
        if ( v29 )
        {
          n0x7F800000_4 = n0x7F800000_3;
          v34 = 0;
          v35 = (_BYTE *)v33;
          do
          {
            *v35 = v70 - 1;
            v35 = (_BYTE *)++__sub_413900_Buffer_0;
            v29 = v32 - v34++ - 1;
          }
          while ( v34 < v31 );
          n0x7F800000_3 = n0x7F800000_4;
          __sub_413900_dword_4456E8 = v32 - v31;
        }
        __sub_413900_byte_4456F0 = (unsigned int)n0x7F800000_3 >> 23;
LABEL_44:
        ++v73;
        n0x800000_3 <<= 8;
        n0x7F800000_3 = (n0x7F800000_3 << 8) & 0x7FFFFFFF;
      }
      while ( n0x800000_3 <= 0x800000 );
      v27 = (v66 & v56) != 0;
      v26 = v49;
      n0x7F800000_5 = n0x7F800000_3;
      v28 = v53;
      __sub_413900_dword_4456EC = v73;
LABEL_46:
      __sub_413900_n0x88 = v28 + v65;
      n0x800000_4 = n0x800000_3 / (v28 + v65) * v28;
      if ( v27 )
      {
        n0x7F800000_5 += n0x800000_4;
        n0x800000_5 = n0x800000_3 - n0x800000_4;
        n0x800000_3 -= n0x800000_4;
      }
      else
      {
        n0x800000_3 = n0x800000_4;
        n0x800000_5 = n0x800000_4;
      }
      n0x4000 = v26[v27];
      if ( n0x4000 > 0x4000u )
      {
        v38 = v26[1];
        *v26 -= *v26 >> 1;
        v26[1] = v38 - (v38 >> 1);
        n0x4000 = v26[v27];
      }
      v26[v27] = __sub_413900_n8_0 + n0x4000;
      v66 >>= 1;
      v59 = v27 + 2 * v59;
      if ( !v66 )
      {
        ::__sub_413900_n0x7F800000 = n0x7F800000_5;
        ::__sub_413900_n0x800000 = n0x800000_5;
        return n0x800000_5;
      }
    }
  }
  ::__sub_413900_n0x7F800000 = n0x7F800000_6;
  ::__sub_413900_n0x800000 = n0x800000_6;
  return n0x800000_5;
}

