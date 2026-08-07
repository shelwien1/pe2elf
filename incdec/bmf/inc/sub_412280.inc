// sub_412280 @ 0x00412280 — __cdecl
// Extracted from BMF.c:16271-16310 by extract.py per incdec.md.

typedef int t_sub_412280_Buffer_0;
static t_sub_412280_Buffer_0& __sub_412280_Buffer_0 = *(t_sub_412280_Buffer_0*)0x00443378;
typedef char t_sub_412280_byte_4456F0;
static t_sub_412280_byte_4456F0& __sub_412280_byte_4456F0 = *(t_sub_412280_byte_4456F0*)0x004456F0;
typedef int t_sub_412280_dword_4456E8;
static t_sub_412280_dword_4456E8& __sub_412280_dword_4456E8 = *(t_sub_412280_dword_4456E8*)0x004456E8;
typedef int t_sub_412280_n0x2000;
static t_sub_412280_n0x2000& __sub_412280_n0x2000 = *(t_sub_412280_n0x2000*)0x004456FC;
typedef int t_sub_412280_n0x7F800000;
static t_sub_412280_n0x7F800000& __sub_412280_n0x7F800000 = *(t_sub_412280_n0x7F800000*)0x004456E4;
typedef int t_sub_412280_n0x800000;
static t_sub_412280_n0x800000& __sub_412280_n0x800000 = *(t_sub_412280_n0x800000*)0x004456E0;


PROBE_DECL(__sub_412280)
__attribute__((force_align_arg_pointer)) unsigned int __sub_412280()
{
  PROBE_HIT(__sub_412280);
  unsigned int __sub_412280_n0x800000; // eax
  unsigned int __sub_412280_n0x7F800000; // ecx
  unsigned int v2; // edx
  unsigned __int8 *v3; // esi
  int v4; // ecx
  unsigned int result; // eax

  __sub_412280_n0x800000 = ::__sub_412280_n0x800000;
  __sub_412280_n0x7F800000 = ::__sub_412280_n0x7F800000;
  if ( (unsigned int)::__sub_412280_n0x800000 <= 0x800000 )
  {
    LOBYTE(v2) = __sub_412280_byte_4456F0;
    v3 = (unsigned __int8 *)__sub_412280_Buffer_0;
    do
    {
      v4 = (unsigned __int8)((_BYTE)v2 << 7) | (__sub_412280_n0x7F800000 << 8);
      v2 = *v3++;
      __sub_412280_Buffer_0 = (int)v3;
      __sub_412280_n0x7F800000 = (v2 >> 1) | v4;
      __sub_412280_n0x800000 <<= 8;
    }
    while ( __sub_412280_n0x800000 <= 0x800000 );
    ::__sub_412280_n0x800000 = __sub_412280_n0x800000;
    __sub_412280_byte_4456F0 = v2;
    ::__sub_412280_n0x7F800000 = __sub_412280_n0x7F800000;
  }
  __sub_412280_dword_4456E8 = __sub_412280_n0x800000 / __sub_412280_n0x2000;
  result = __sub_412280_n0x7F800000 / (__sub_412280_n0x800000 / __sub_412280_n0x2000);
  if ( result >= __sub_412280_n0x2000 )
    return __sub_412280_n0x2000 - 1;
  return result;
}

