// sub_414620 @ 0x00414620 — __thiscall
// Extracted from BMF.cpp:18804-18931 by extract.py per incdec.md.

typedef int t_sub_414620_Buffer_0;
static t_sub_414620_Buffer_0& __sub_414620_Buffer_0 = *(t_sub_414620_Buffer_0*)(blob1 + 0x00443378 - BMF_BLOB_BASE);
typedef char t_sub_414620_byte_4456F0;
static t_sub_414620_byte_4456F0& __sub_414620_byte_4456F0 = *(t_sub_414620_byte_4456F0*)(blob1 + 0x004456F0 - BMF_BLOB_BASE);
typedef int t_sub_414620_dword_4456E8;
static t_sub_414620_dword_4456E8& __sub_414620_dword_4456E8 = *(t_sub_414620_dword_4456E8*)(blob1 + 0x004456E8 - BMF_BLOB_BASE);
typedef int t_sub_414620_n0x2000;
static t_sub_414620_n0x2000& __sub_414620_n0x2000 = *(t_sub_414620_n0x2000*)(blob1 + 0x004456FC - BMF_BLOB_BASE);
typedef int t_sub_414620_n0x2000_0;
static t_sub_414620_n0x2000_0& __sub_414620_n0x2000_0 = *(t_sub_414620_n0x2000_0*)(blob1 + 0x004456F8 - BMF_BLOB_BASE);
typedef int t_sub_414620_n0x2000_1;
static t_sub_414620_n0x2000_1& __sub_414620_n0x2000_1 = *(t_sub_414620_n0x2000_1*)(blob1 + 0x004456F4 - BMF_BLOB_BASE);
typedef int t_sub_414620_n0x7F800000;
static t_sub_414620_n0x7F800000& __sub_414620_n0x7F800000 = *(t_sub_414620_n0x7F800000*)(blob1 + 0x004456E4 - BMF_BLOB_BASE);
typedef int t_sub_414620_n0x800000;
static t_sub_414620_n0x800000& __sub_414620_n0x800000 = *(t_sub_414620_n0x800000*)(blob1 + 0x004456E0 - BMF_BLOB_BASE);
typedef void * t_sub_414620_n256_1;
static t_sub_414620_n256_1& __sub_414620_n256_1 = *(t_sub_414620_n256_1*)(blob1 + 0x00445708 - BMF_BLOB_BASE);

static inline int __fwd_sub_414620_sub_414060(void *a0) { return __sub_414060((unsigned __int16 *)a0); }
#define sub_414060 __fwd_sub_414620_sub_414060

PROBE_DECL(__sub_414620)
BMF_REALIGN __attribute__((thiscall)) int __sub_414620(unsigned __int16 *_this, int a2)
{
  PROBE_HIT(__sub_414620);
  unsigned int __sub_414620_n0x800000; // ebp
  unsigned int __sub_414620_n0x7F800000; // ebx
  unsigned int v4; // edx
  unsigned __int8 *v5; // esi
  int v6; // ebx
  signed int v7; // eax
  signed int v8; // edx
  _WORD *v9; // esi
  int v10; // ecx
  unsigned int v11; // eax
  int v12; // edx
  int n0x800000_1; // ebp
  signed int n0x4000; // eax
  int n32; // edx
  int v16; // esi
  unsigned int v18; // ebp
  unsigned int v19; // eax
  unsigned int v20; // [esp+0h] [ebp-20h]
  int v21; // [esp+4h] [ebp-1Ch]
  int v23; // [esp+8h] [ebp-18h]
  unsigned __int16 *v24; // [esp+8h] [ebp-18h]
  int v25; // [esp+Ch] [ebp-14h]

  __sub_414620_n0x800000 = ::__sub_414620_n0x800000;
  v23 = *(_this + 3);
  v21 = *(_this + 2) + *(_this + 1);
  __sub_414620_n0x7F800000 = ::__sub_414620_n0x7F800000;
  v20 = v23 + v21;
  __sub_414620_n0x2000 = v23 + v21;
  if ( (unsigned int)::__sub_414620_n0x800000 <= 0x800000 )
  {
    LOBYTE(v4) = __sub_414620_byte_4456F0;
    v5 = (unsigned __int8 *)__sub_414620_Buffer_0;
    do
    {
      v6 = (unsigned __int8)((_BYTE)v4 << 7) | (__sub_414620_n0x7F800000 << 8);
      v4 = *v5++;
      __sub_414620_Buffer_0 = (int)v5;
      __sub_414620_n0x7F800000 = (v4 >> 1) | v6;
      __sub_414620_n0x800000 <<= 8;
    }
    while ( __sub_414620_n0x800000 <= 0x800000 );
    __sub_414620_byte_4456F0 = v4;
  }
  v25 = __sub_414620_n0x800000 / v20;
  __sub_414620_dword_4456E8 = __sub_414620_n0x800000 / v20;
  v7 = __sub_414620_n0x7F800000 / (__sub_414620_n0x800000 / v20);
  if ( v7 >= v20 )
    v7 = v23 + v21 - 1;
  v8 = *(_this + 1);
  if ( v7 >= v8 )
  {
    if ( v7 >= v21 )
    {
      v8 = v21;
      __sub_414620_n0x2000_1 = v21;
      v9 = _this + 3;
    }
    else
    {
      __sub_414620_n0x2000_1 = *(_this + 1);
      v9 = _this + 2;
    }
    v24 = _this + 1;
  }
  else
  {
    __sub_414620_n0x2000_1 = 0;
    v9 = _this + 1;
    v8 = 0;
    v24 = _this + 1;
  }
  v10 = (unsigned __int16)*v9;
  v11 = v8 + v10;
  v12 = v25 * v8;
  __sub_414620_n0x2000_0 = v11;
  ::__sub_414620_n0x7F800000 = __sub_414620_n0x7F800000 - v12;
  n0x800000_1 = __sub_414620_n0x800000 - v12;
  if ( v11 < v20 )
    n0x800000_1 = v10 * v25;
  n0x4000 = (unsigned __int16)*v9;
  ::__sub_414620_n0x800000 = n0x800000_1;
  if ( n0x4000 > 0x4000 )
  {
    v18 = *(_this + 2);
    v19 = *(_this + 3);
    *(_this + 1) -= *(_this + 1) >> 1;
    n32 = *_this;
    *(_this + 2) = v18 - (v18 >> 1);
    *(_this + 3) = v19 - (v19 >> 1);
    if ( n32 <= 256 )
    {
      if ( n32 <= 32 )
        n0x4000 = ((unsigned int)(16 - n32) >> 30) & 0xFFFFFFFE;
      else
        LOWORD(n0x4000) = 32;
      LOWORD(n32) = n32 - n0x4000;
      *_this = n32;
      LOWORD(n0x4000) = *v9;
    }
    else
    {
      n32 = (unsigned int)n32 >> 1;
      *_this = n32;
      LOWORD(n0x4000) = *v9;
    }
  }
  else
  {
    LOWORD(n32) = *_this;
  }
  *v9 = n32 + n0x4000;
  v16 = v9 - v24;
  if ( v16 )
    return v16 + 2 * sub_414060((unsigned __int16 *)__sub_414620_n256_1 + 254 * *(_DWORD *)(a2 + 4 * (v16 & 1)));
  else
    return 0;
}

#undef sub_414060
