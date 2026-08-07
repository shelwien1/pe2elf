// sub_411E90 @ 0x00411E90 — __cdecl
// Extracted from BMF.cpp:15988-16075 by extract.py per incdec.md.

typedef int t_sub_411E90_Buffer_0;
static t_sub_411E90_Buffer_0& __sub_411E90_Buffer_0 = *(t_sub_411E90_Buffer_0*)(blob1 + 0x00443378 - BMF_BLOB_BASE);
typedef char t_sub_411E90_byte_4456F0;
static t_sub_411E90_byte_4456F0& __sub_411E90_byte_4456F0 = *(t_sub_411E90_byte_4456F0*)(blob1 + 0x004456F0 - BMF_BLOB_BASE);
typedef int t_sub_411E90_dword_4456E8;
static t_sub_411E90_dword_4456E8& __sub_411E90_dword_4456E8 = *(t_sub_411E90_dword_4456E8*)(blob1 + 0x004456E8 - BMF_BLOB_BASE);
typedef int t_sub_411E90_dword_4456EC;
static t_sub_411E90_dword_4456EC& __sub_411E90_dword_4456EC = *(t_sub_411E90_dword_4456EC*)(blob1 + 0x004456EC - BMF_BLOB_BASE);
typedef int t_sub_411E90_n0x2000;
static t_sub_411E90_n0x2000& __sub_411E90_n0x2000 = *(t_sub_411E90_n0x2000*)(blob1 + 0x004456FC - BMF_BLOB_BASE);
typedef int t_sub_411E90_n0x2000_0;
static t_sub_411E90_n0x2000_0& __sub_411E90_n0x2000_0 = *(t_sub_411E90_n0x2000_0*)(blob1 + 0x004456F8 - BMF_BLOB_BASE);
typedef int t_sub_411E90_n0x2000_1;
static t_sub_411E90_n0x2000_1& __sub_411E90_n0x2000_1 = *(t_sub_411E90_n0x2000_1*)(blob1 + 0x004456F4 - BMF_BLOB_BASE);
typedef int t_sub_411E90_n0x7F800000;
static t_sub_411E90_n0x7F800000& __sub_411E90_n0x7F800000 = *(t_sub_411E90_n0x7F800000*)(blob1 + 0x004456E4 - BMF_BLOB_BASE);
typedef int t_sub_411E90_n0x800000;
static t_sub_411E90_n0x800000& __sub_411E90_n0x800000 = *(t_sub_411E90_n0x800000*)(blob1 + 0x004456E0 - BMF_BLOB_BASE);


PROBE_DECL(__sub_411E90)
BMF_REALIGN int __sub_411E90()
{
  PROBE_HIT(__sub_411E90);
  unsigned int __sub_411E90_n0x800000; // ebp
  int __sub_411E90_n0x7F800000; // ecx
  int v2; // edx
  unsigned int v3; // edi
  int v4; // esi
  int v5; // eax
  unsigned int v6; // ebx
  _BYTE *v7; // ebp
  unsigned int v8; // eax
  unsigned int v9; // ebx
  int n0x800000_1; // ebp
  int n0x800000_3; // eax
  unsigned int n0x800000_2; // [esp+4h] [ebp-18h]
  char v13; // [esp+8h] [ebp-14h]
  int v14; // [esp+Ch] [ebp-10h]

  __sub_411E90_n0x800000 = ::__sub_411E90_n0x800000;
  __sub_411E90_n0x7F800000 = ::__sub_411E90_n0x7F800000;
  if ( (unsigned int)::__sub_411E90_n0x800000 <= 0x800000 )
  {
    v2 = __sub_411E90_dword_4456E8;
    v14 = __sub_411E90_dword_4456EC;
    while ( 1 )
    {
      ++v14;
      v3 = v2;
      v4 = v2;
      if ( (unsigned int)__sub_411E90_n0x7F800000 < 0x7F800000 )
        break;
      if ( __sub_411E90_n0x7F800000 < 0 )
      {
        v13 = 1;
LABEL_8:
        *(_BYTE *)__sub_411E90_Buffer_0 = v13 + __sub_411E90_byte_4456F0;
        v5 = ++__sub_411E90_Buffer_0;
        if ( v2 )
        {
          n0x800000_2 = __sub_411E90_n0x800000;
          v6 = 0;
          v7 = (_BYTE *)v5;
          do
          {
            *v7 = v13 - 1;
            v7 = (_BYTE *)++__sub_411E90_Buffer_0;
            v2 = v4 - v6++ - 1;
          }
          while ( v6 < v3 );
          __sub_411E90_n0x800000 = n0x800000_2;
          __sub_411E90_dword_4456E8 = v4 - v3;
        }
        __sub_411E90_byte_4456F0 = (unsigned int)__sub_411E90_n0x7F800000 >> 23;
        goto LABEL_13;
      }
      __sub_411E90_dword_4456E8 = ++v2;
LABEL_13:
      __sub_411E90_n0x800000 <<= 8;
      __sub_411E90_n0x7F800000 = (__sub_411E90_n0x7F800000 << 8) & 0x7FFFFFFF;
      if ( __sub_411E90_n0x800000 > 0x800000 )
      {
        __sub_411E90_dword_4456EC = v14;
        goto LABEL_15;
      }
    }
    v13 = 0;
    goto LABEL_8;
  }
LABEL_15:
  v8 = __sub_411E90_n0x800000 / __sub_411E90_n0x2000;
  v9 = __sub_411E90_n0x2000_1 * (__sub_411E90_n0x800000 / __sub_411E90_n0x2000);
  n0x800000_1 = __sub_411E90_n0x800000 - v9;
  n0x800000_3 = (__sub_411E90_n0x2000_0 - __sub_411E90_n0x2000_1) * v8;
  if ( __sub_411E90_n0x2000_0 < (unsigned int)__sub_411E90_n0x2000 )
    n0x800000_1 = n0x800000_3;
  ::__sub_411E90_n0x800000 = n0x800000_1;
  ::__sub_411E90_n0x7F800000 = __sub_411E90_n0x7F800000 + v9;
  return n0x800000_3;
}

