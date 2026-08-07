// sub_412340 @ 0x00412340 — __cdecl
// Extracted from BMF.c:16334-16378 by extract.py per incdec.md.

typedef int t_sub_412340_Buffer_0;
static t_sub_412340_Buffer_0& __sub_412340_Buffer_0 = *(t_sub_412340_Buffer_0*)0x00443378;
typedef char t_sub_412340_byte_4456F0;
static t_sub_412340_byte_4456F0& __sub_412340_byte_4456F0 = *(t_sub_412340_byte_4456F0*)0x004456F0;
typedef int t_sub_412340_n0x7F800000;
static t_sub_412340_n0x7F800000& __sub_412340_n0x7F800000 = *(t_sub_412340_n0x7F800000*)0x004456E4;
typedef int t_sub_412340_n0x800000;
static t_sub_412340_n0x800000& __sub_412340_n0x800000 = *(t_sub_412340_n0x800000*)0x004456E0;
typedef int t_sub_412340_n0x88;
static t_sub_412340_n0x88& __sub_412340_n0x88 = *(t_sub_412340_n0x88*)0x00445704;


PROBE_DECL(__sub_412340)
BOOL __sub_412340(int a1, int a2)
{
  PROBE_HIT(__sub_412340);
  unsigned int __sub_412340_n0x800000; // ecx
  unsigned int __sub_412340_n0x7F800000; // esi
  unsigned int v4; // edx
  unsigned __int8 *v5; // edi
  int v6; // esi
  unsigned int n0x7F800000_1; // eax

  __sub_412340_n0x800000 = ::__sub_412340_n0x800000;
  __sub_412340_n0x7F800000 = ::__sub_412340_n0x7F800000;
  if ( (unsigned int)::__sub_412340_n0x800000 <= 0x800000 )
  {
    LOBYTE(v4) = __sub_412340_byte_4456F0;
    v5 = (unsigned __int8 *)__sub_412340_Buffer_0;
    do
    {
      v6 = (unsigned __int8)((_BYTE)v4 << 7) | (__sub_412340_n0x7F800000 << 8);
      v4 = *v5++;
      __sub_412340_Buffer_0 = (int)v5;
      __sub_412340_n0x7F800000 = (v4 >> 1) | v6;
      __sub_412340_n0x800000 <<= 8;
    }
    while ( __sub_412340_n0x800000 <= 0x800000 );
    __sub_412340_byte_4456F0 = v4;
    ::__sub_412340_n0x7F800000 = __sub_412340_n0x7F800000;
  }
  n0x7F800000_1 = a1 * (__sub_412340_n0x800000 / (a1 + a2));
  __sub_412340_n0x88 = a1 + a2;
  if ( __sub_412340_n0x7F800000 >= n0x7F800000_1 )
  {
    ::__sub_412340_n0x800000 = __sub_412340_n0x800000 - n0x7F800000_1;
    ::__sub_412340_n0x7F800000 = __sub_412340_n0x7F800000 - n0x7F800000_1;
  }
  else
  {
    ::__sub_412340_n0x800000 = a1 * (__sub_412340_n0x800000 / (a1 + a2));
  }
  return __sub_412340_n0x7F800000 >= n0x7F800000_1;
}

