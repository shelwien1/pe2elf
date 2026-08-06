// sub_412280 @ 0x00412280 — __cdecl
// Extracted from BMF.c:16271-16310 by extract.py per incdec.md.

typedef int t_sub_412280_Buffer_0;
static t_sub_412280_Buffer_0& __sub_412280_Buffer_0 = *(t_sub_412280_Buffer_0*)0x00443378;
#define Buffer_0 __sub_412280_Buffer_0
typedef char t_sub_412280_byte_4456F0;
static t_sub_412280_byte_4456F0& __sub_412280_byte_4456F0 = *(t_sub_412280_byte_4456F0*)0x004456F0;
#define byte_4456F0 __sub_412280_byte_4456F0
typedef int t_sub_412280_dword_4456E8;
static t_sub_412280_dword_4456E8& __sub_412280_dword_4456E8 = *(t_sub_412280_dword_4456E8*)0x004456E8;
#define dword_4456E8 __sub_412280_dword_4456E8
typedef int t_sub_412280_n0x2000;
static t_sub_412280_n0x2000& __sub_412280_n0x2000 = *(t_sub_412280_n0x2000*)0x004456FC;
#define n0x2000 __sub_412280_n0x2000
typedef int t_sub_412280_n0x7F800000;
static t_sub_412280_n0x7F800000& __sub_412280_n0x7F800000 = *(t_sub_412280_n0x7F800000*)0x004456E4;
#define n0x7F800000 __sub_412280_n0x7F800000
typedef int t_sub_412280_n0x800000;
static t_sub_412280_n0x800000& __sub_412280_n0x800000 = *(t_sub_412280_n0x800000*)0x004456E0;
#define n0x800000 __sub_412280_n0x800000


PROBE_DECL(__sub_412280)
unsigned int __sub_412280()
{
  PROBE_HIT(__sub_412280);
  unsigned int n0x800000; // eax
  unsigned int n0x7F800000; // ecx
  unsigned int v2; // edx
  unsigned __int8 *v3; // esi
  int v4; // ecx
  unsigned int result; // eax

  n0x800000 = ::n0x800000;
  n0x7F800000 = ::n0x7F800000;
  if ( (unsigned int)::n0x800000 <= 0x800000 )
  {
    LOBYTE(v2) = byte_4456F0;
    v3 = (unsigned __int8 *)Buffer_0;
    do
    {
      v4 = (unsigned __int8)((_BYTE)v2 << 7) | (n0x7F800000 << 8);
      v2 = *v3++;
      Buffer_0 = (int)v3;
      n0x7F800000 = (v2 >> 1) | v4;
      n0x800000 <<= 8;
    }
    while ( n0x800000 <= 0x800000 );
    ::n0x800000 = n0x800000;
    byte_4456F0 = v2;
    ::n0x7F800000 = n0x7F800000;
  }
  dword_4456E8 = n0x800000 / n0x2000;
  result = n0x7F800000 / (n0x800000 / n0x2000);
  if ( result >= n0x2000 )
    return n0x2000 - 1;
  return result;
}

#undef Buffer_0
#undef byte_4456F0
#undef dword_4456E8
#undef n0x2000
#undef n0x7F800000
#undef n0x800000
