// sub_414390 @ 0x00414390 — __thiscall
// Extracted from BMF.cpp:18634-18801 by extract.py per incdec.md.

typedef int t_sub_414390_Buffer_0;
static t_sub_414390_Buffer_0& __sub_414390_Buffer_0 = *(t_sub_414390_Buffer_0*)(blob1 + 0x00443378 - BMF_BLOB_BASE);
typedef char t_sub_414390_byte_4456F0;
static t_sub_414390_byte_4456F0& __sub_414390_byte_4456F0 = *(t_sub_414390_byte_4456F0*)(blob1 + 0x004456F0 - BMF_BLOB_BASE);
typedef int t_sub_414390_dword_4456E8;
static t_sub_414390_dword_4456E8& __sub_414390_dword_4456E8 = *(t_sub_414390_dword_4456E8*)(blob1 + 0x004456E8 - BMF_BLOB_BASE);
typedef int t_sub_414390_dword_4456EC;
static t_sub_414390_dword_4456EC& __sub_414390_dword_4456EC = *(t_sub_414390_dword_4456EC*)(blob1 + 0x004456EC - BMF_BLOB_BASE);
typedef int t_sub_414390_n0x2000;
static t_sub_414390_n0x2000& __sub_414390_n0x2000 = *(t_sub_414390_n0x2000*)(blob1 + 0x004456FC - BMF_BLOB_BASE);
typedef int t_sub_414390_n0x2000_0;
static t_sub_414390_n0x2000_0& __sub_414390_n0x2000_0 = *(t_sub_414390_n0x2000_0*)(blob1 + 0x004456F8 - BMF_BLOB_BASE);
typedef int t_sub_414390_n0x2000_1;
static t_sub_414390_n0x2000_1& __sub_414390_n0x2000_1 = *(t_sub_414390_n0x2000_1*)(blob1 + 0x004456F4 - BMF_BLOB_BASE);
typedef int t_sub_414390_n0x7F800000;
static t_sub_414390_n0x7F800000& __sub_414390_n0x7F800000 = *(t_sub_414390_n0x7F800000*)(blob1 + 0x004456E4 - BMF_BLOB_BASE);
typedef int t_sub_414390_n0x800000;
static t_sub_414390_n0x800000& __sub_414390_n0x800000 = *(t_sub_414390_n0x800000*)(blob1 + 0x004456E0 - BMF_BLOB_BASE);
typedef int t_sub_414390_n256_1;
static t_sub_414390_n256_1& __sub_414390_n256_1 = *(t_sub_414390_n256_1*)(blob1 + 0x00445708 - BMF_BLOB_BASE);

static inline int __fwd_sub_414390_sub_413900(void *a0, int a1) { return __sub_413900((unsigned __int16 *)a0, a1); }
#define sub_413900 __fwd_sub_414390_sub_413900

PROBE_DECL(__sub_414390)
BMF_REALIGN __attribute__((thiscall)) int __sub_414390(unsigned __int16 *_this, int a2, int a3)
{
  PROBE_HIT(__sub_414390);
  int v3; // esi
  unsigned int __sub_414390_n0x2000; // ebp
  unsigned __int16 *v5; // edx
  unsigned int __sub_414390_n0x800000; // ecx
  unsigned int __sub_414390_n0x2000_1; // ebx
  int v8; // ebx
  int n0x7F800000_1; // esi
  unsigned int v10; // edi
  int v11; // ebp
  int v12; // eax
  unsigned int v13; // edx
  _BYTE *v14; // ecx
  int v15; // edx
  int n0x800000_3; // eax
  int n0x800000_2; // ecx
  __int16 v18; // dx
  int n32; // ecx
  int result; // eax
  unsigned int v21; // ebx
  unsigned int v22; // esi
  unsigned int v23; // eax
  unsigned __int16 *v25; // [esp+4h] [ebp-24h]
  int __sub_414390_n0x7F800000; // [esp+8h] [ebp-20h]
  unsigned int n0x2000_2; // [esp+Ch] [ebp-1Ch]
  unsigned int n0x800000_1; // [esp+Ch] [ebp-1Ch]
  char v29; // [esp+10h] [ebp-18h]
  int v30; // [esp+14h] [ebp-14h]

  v3 = *(_this + 2) + *(_this + 1);
  __sub_414390_n0x2000 = v3 + *(_this + 3);
  ::__sub_414390_n0x2000 = __sub_414390_n0x2000;
  if ( a3 )
  {
    if ( (a3 & 1) != 0 )
    {
      v3 = *(_this + 1);
      ::__sub_414390_n0x2000_1 = v3;
      v5 = _this + 2;
      v25 = _this + 2;
    }
    else
    {
      ::__sub_414390_n0x2000_1 = v3;
      v5 = _this + 3;
      v25 = _this + 3;
    }
  }
  else
  {
    ::__sub_414390_n0x2000_1 = 0;
    v5 = _this + 1;
    v3 = 0;
    v25 = _this + 1;
  }
  __sub_414390_n0x800000 = ::__sub_414390_n0x800000;
  __sub_414390_n0x7F800000 = ::__sub_414390_n0x7F800000;
  __sub_414390_n0x2000_1 = v3 + *v5;
  __sub_414390_n0x2000_0 = __sub_414390_n0x2000_1;
  if ( (unsigned int)::__sub_414390_n0x800000 > 0x800000 )
  {
    n0x2000_2 = ::__sub_414390_n0x2000;
    goto LABEL_21;
  }
  v8 = __sub_414390_dword_4456E8;
  n0x7F800000_1 = ::__sub_414390_n0x7F800000;
  v30 = __sub_414390_dword_4456EC;
  do
  {
    ++v30;
    v10 = v8;
    v11 = v8;
    if ( (unsigned int)n0x7F800000_1 < 0x7F800000 )
    {
      v29 = 0;
    }
    else
    {
      if ( n0x7F800000_1 >= 0 )
      {
        __sub_414390_dword_4456E8 = ++v8;
        goto LABEL_19;
      }
      v29 = 1;
    }
    *(_BYTE *)__sub_414390_Buffer_0 = v29 + __sub_414390_byte_4456F0;
    v12 = ++__sub_414390_Buffer_0;
    if ( v8 )
    {
      n0x800000_1 = __sub_414390_n0x800000;
      v13 = 0;
      v14 = (_BYTE *)v12;
      do
      {
        *v14 = v29 - 1;
        v14 = (_BYTE *)++__sub_414390_Buffer_0;
        v8 = v11 - v13++ - 1;
      }
      while ( v13 < v10 );
      __sub_414390_n0x800000 = n0x800000_1;
      __sub_414390_dword_4456E8 = v11 - v10;
    }
    __sub_414390_byte_4456F0 = (unsigned int)n0x7F800000_1 >> 23;
LABEL_19:
    __sub_414390_n0x800000 <<= 8;
    n0x7F800000_1 = (n0x7F800000_1 << 8) & 0x7FFFFFFF;
  }
  while ( __sub_414390_n0x800000 <= 0x800000 );
  __sub_414390_n0x2000 = ::__sub_414390_n0x2000;
  __sub_414390_n0x2000_1 = __sub_414390_n0x2000_0;
  __sub_414390_n0x7F800000 = n0x7F800000_1;
  v3 = ::__sub_414390_n0x2000_1;
  __sub_414390_dword_4456EC = v30;
  n0x2000_2 = ::__sub_414390_n0x2000;
LABEL_21:
  v15 = __sub_414390_n0x800000 / n0x2000_2 * v3;
  n0x800000_3 = (__sub_414390_n0x2000_1 - v3) * (__sub_414390_n0x800000 / n0x2000_2);
  n0x800000_2 = __sub_414390_n0x800000 - v15;
  if ( __sub_414390_n0x2000_1 < __sub_414390_n0x2000 )
    n0x800000_2 = n0x800000_3;
  ::__sub_414390_n0x7F800000 = __sub_414390_n0x7F800000 + v15;
  ::__sub_414390_n0x800000 = n0x800000_2;
  v18 = *v25;
  if ( *v25 > 0x4000u )
  {
    v21 = *(_this + 2);
    v22 = *(_this + 3);
    *(_this + 1) -= *(_this + 1) >> 1;
    n32 = *_this;
    *(_this + 2) = v21 - (v21 >> 1);
    *(_this + 3) = v22 - (v22 >> 1);
    if ( n32 <= 256 )
    {
      if ( n32 <= 32 )
        v23 = ((unsigned int)(16 - n32) >> 30) & 0xFFFFFFFE;
      else
        LOWORD(v23) = 32;
      LOWORD(n32) = n32 - v23;
      *_this = n32;
      v18 = *v25;
    }
    else
    {
      n32 = (unsigned int)n32 >> 1;
      *_this = n32;
      v18 = *v25;
    }
  }
  else
  {
    LOWORD(n32) = *_this;
  }
  result = (int)v25;
  *v25 = n32 + v18;
  if ( a3 > 0 )
    return sub_413900((unsigned __int16 *)__sub_414390_n256_1 + 254 * *(_DWORD *)(a2 + 4 * (a3 & 1)), (a3 - 1) >> 1);
  return result;
}

#undef sub_413900
