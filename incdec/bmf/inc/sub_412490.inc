// sub_412490 @ 0x00412490 — __thiscall
// Extracted from BMF.cpp:16434-16672 by extract.py per incdec.md.

typedef int t_sub_412490_Buffer_0;
static t_sub_412490_Buffer_0& __sub_412490_Buffer_0 = *(t_sub_412490_Buffer_0*)0x00443378;
typedef char t_sub_412490_byte_4456F0;
static t_sub_412490_byte_4456F0& __sub_412490_byte_4456F0 = *(t_sub_412490_byte_4456F0*)0x004456F0;
typedef int t_sub_412490_dword_4456E8;
static t_sub_412490_dword_4456E8& __sub_412490_dword_4456E8 = *(t_sub_412490_dword_4456E8*)0x004456E8;
typedef int t_sub_412490_dword_4456EC;
static t_sub_412490_dword_4456EC& __sub_412490_dword_4456EC = *(t_sub_412490_dword_4456EC*)0x004456EC;
typedef int t_sub_412490_n0x7F800000;
static t_sub_412490_n0x7F800000& __sub_412490_n0x7F800000 = *(t_sub_412490_n0x7F800000*)0x004456E4;
typedef int t_sub_412490_n0x800000;
static t_sub_412490_n0x800000& __sub_412490_n0x800000 = *(t_sub_412490_n0x800000*)0x004456E0;
typedef int t_sub_412490_n0x88;
static t_sub_412490_n0x88& __sub_412490_n0x88 = *(t_sub_412490_n0x88*)0x00445704;


PROBE_DECL(__sub_412490)
__attribute__((force_align_arg_pointer)) __attribute__((thiscall)) int __sub_412490(unsigned __int16 *_this, unsigned __int16 *a2, int n15)
{
  PROBE_HIT(__sub_412490);
  int v3; // ebx
  int v4; // ebp
  unsigned int __sub_412490_n0x800000; // esi
  int __sub_412490_n0x7F800000; // edi
  int v7; // edx
  unsigned int v8; // ebp
  int v9; // ebx
  int v10; // eax
  unsigned int v11; // ecx
  _BYTE *v12; // esi
  unsigned int __sub_412490_n0x88; // ebp
  int n0x800000_1; // ebx
  int n0x4000; // esi
  int result; // eax
  unsigned int n0x800000_3; // esi
  int v18; // ebx
  int v19; // ebp
  int n0x7F800000_1; // edi
  int v21; // edx
  unsigned int v22; // ebp
  int v23; // ebx
  int v24; // eax
  unsigned int v25; // ecx
  _BYTE *v26; // esi
  unsigned int n0x88_1; // ebp
  int n0x800000_5; // ebx
  int n0x4000_1; // eax
  unsigned int v30; // ebp
  int v31; // edi
  unsigned int v32; // ebp
  int v33; // ebp
  unsigned int v34; // esi
  int v35; // [esp+0h] [ebp-28h]
  int v36; // [esp+0h] [ebp-28h]
  int v37; // [esp+4h] [ebp-24h]
  int v38; // [esp+4h] [ebp-24h]
  unsigned int n0x800000_2; // [esp+8h] [ebp-20h]
  unsigned int n0x800000_4; // [esp+8h] [ebp-20h]
  char v41; // [esp+Ch] [ebp-1Ch]
  char v42; // [esp+Ch] [ebp-1Ch]
  unsigned __int16 *this_1; // [esp+10h] [ebp-18h]
  unsigned __int16 *this_2; // [esp+10h] [ebp-18h]
  int v45; // [esp+14h] [ebp-14h]
  int v46; // [esp+14h] [ebp-14h]

  v3 = *_this;
  if ( *_this )
  {
    v4 = *(_this + 1);
    if ( !*(_this + 1) )
    {
      v31 = *a2;
      v32 = v31 + a2[1];
      *_this = (v32 + (v31 << 6) - 64) / v32;
      *(_this + 1) = ((a2[1] << 6) + v32 - 64) / v32;
      *(_this + v3 - 1) += 4;
      *(_this + 2) = 512;
      v33 = a2[v3 - 1];
      a2[v3 - 1] = -3 * ((unsigned int)(3 - v33) >> 31) + v33;
      v3 = *_this;
      v4 = *(_this + 1);
    }
    __sub_412490_n0x800000 = ::__sub_412490_n0x800000;
    if ( (unsigned int)::__sub_412490_n0x800000 > 0x800000 )
    {
LABEL_18:
      __sub_412490_n0x88 = v3 + v4;
      ::__sub_412490_n0x88 = __sub_412490_n0x88;
      n0x800000_1 = __sub_412490_n0x800000 / __sub_412490_n0x88 * v3;
      if ( n15 )
      {
        ::__sub_412490_n0x7F800000 += n0x800000_1;
        ::__sub_412490_n0x800000 = __sub_412490_n0x800000 - n0x800000_1;
      }
      else
      {
        ::__sub_412490_n0x800000 = n0x800000_1;
      }
      n0x4000 = *(_this + 2);
      if ( __sub_412490_n0x88 > n0x4000 )
      {
        v30 = *(_this + 1);
        *_this -= *_this >> 1;
        *(_this + 1) = v30 - (v30 >> 1);
        if ( n0x4000 < 0x4000 )
          *(_this + 2) = n0x4000 + 64;
      }
      result = *(_this + n15) + 8;
      *(_this + n15) = result;
      a2[n15] += (unsigned int)::__sub_412490_n0x88 < 0x88;
      return result;
    }
    __sub_412490_n0x7F800000 = ::__sub_412490_n0x7F800000;
    v7 = __sub_412490_dword_4456E8;
    v37 = v3;
    v35 = v4;
    v45 = __sub_412490_dword_4456EC;
    this_1 = _this;
    while ( 1 )
    {
      ++v45;
      v8 = v7;
      v9 = v7;
      if ( (unsigned int)__sub_412490_n0x7F800000 < 0x7F800000 )
        break;
      if ( __sub_412490_n0x7F800000 < 0 )
      {
        v41 = 1;
LABEL_11:
        *(_BYTE *)__sub_412490_Buffer_0 = v41 + __sub_412490_byte_4456F0;
        v10 = ++__sub_412490_Buffer_0;
        if ( v7 )
        {
          n0x800000_2 = __sub_412490_n0x800000;
          v11 = 0;
          v12 = (_BYTE *)v10;
          do
          {
            *v12 = v41 - 1;
            v12 = (_BYTE *)++__sub_412490_Buffer_0;
            v7 = v9 - v11++ - 1;
          }
          while ( v11 < v8 );
          __sub_412490_n0x800000 = n0x800000_2;
          __sub_412490_dword_4456E8 = v9 - v8;
        }
        __sub_412490_byte_4456F0 = (unsigned int)__sub_412490_n0x7F800000 >> 23;
        goto LABEL_16;
      }
      __sub_412490_dword_4456E8 = ++v7;
LABEL_16:
      __sub_412490_n0x800000 <<= 8;
      __sub_412490_n0x7F800000 = (__sub_412490_n0x7F800000 << 8) & 0x7FFFFFFF;
      if ( __sub_412490_n0x800000 > 0x800000 )
      {
        v3 = v37;
        v4 = v35;
        _this = this_1;
        __sub_412490_dword_4456EC = v45;
        ::__sub_412490_n0x7F800000 = __sub_412490_n0x7F800000;
        goto LABEL_18;
      }
    }
    v41 = 0;
    goto LABEL_11;
  }
  n0x800000_3 = ::__sub_412490_n0x800000;
  v18 = *a2;
  v19 = a2[1];
  if ( (unsigned int)::__sub_412490_n0x800000 > 0x800000 )
    goto LABEL_37;
  n0x7F800000_1 = ::__sub_412490_n0x7F800000;
  v21 = __sub_412490_dword_4456E8;
  v38 = *a2;
  v36 = a2[1];
  v46 = __sub_412490_dword_4456EC;
  this_2 = _this;
  do
  {
    ++v46;
    v22 = v21;
    v23 = v21;
    if ( (unsigned int)n0x7F800000_1 < 0x7F800000 )
    {
      v42 = 0;
    }
    else
    {
      if ( n0x7F800000_1 >= 0 )
      {
        __sub_412490_dword_4456E8 = ++v21;
        goto LABEL_35;
      }
      v42 = 1;
    }
    *(_BYTE *)__sub_412490_Buffer_0 = v42 + __sub_412490_byte_4456F0;
    v24 = ++__sub_412490_Buffer_0;
    if ( v21 )
    {
      n0x800000_4 = n0x800000_3;
      v25 = 0;
      v26 = (_BYTE *)v24;
      do
      {
        *v26 = v42 - 1;
        v26 = (_BYTE *)++__sub_412490_Buffer_0;
        v21 = v23 - v25++ - 1;
      }
      while ( v25 < v22 );
      n0x800000_3 = n0x800000_4;
      __sub_412490_dword_4456E8 = v23 - v22;
    }
    __sub_412490_byte_4456F0 = (unsigned int)n0x7F800000_1 >> 23;
LABEL_35:
    n0x800000_3 <<= 8;
    n0x7F800000_1 = (n0x7F800000_1 << 8) & 0x7FFFFFFF;
  }
  while ( n0x800000_3 <= 0x800000 );
  v18 = v38;
  v19 = v36;
  _this = this_2;
  __sub_412490_dword_4456EC = v46;
  ::__sub_412490_n0x7F800000 = n0x7F800000_1;
LABEL_37:
  n0x88_1 = v18 + v19;
  ::__sub_412490_n0x88 = n0x88_1;
  n0x800000_5 = n0x800000_3 / n0x88_1 * v18;
  if ( n15 )
  {
    ::__sub_412490_n0x7F800000 += n0x800000_5;
    ::__sub_412490_n0x800000 = n0x800000_3 - n0x800000_5;
  }
  else
  {
    ::__sub_412490_n0x800000 = n0x800000_5;
  }
  n0x4000_1 = a2[2];
  if ( n0x88_1 > n0x4000_1 )
  {
    v34 = a2[1];
    *a2 -= *a2 >> 1;
    a2[1] = v34 - (v34 >> 1);
    if ( n0x4000_1 < 0x4000 )
      a2[2] = n0x4000_1 + 64;
  }
  result = a2[n15] + 8;
  a2[n15] = result;
  *_this = n15 + 1;
  return result;
}

