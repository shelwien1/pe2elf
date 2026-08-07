// sub_4123E0 @ 0x004123E0 — __cdecl
// Extracted from BMF.c:16381-16431 by extract.py per incdec.md.

typedef int t_sub_4123E0_Buffer_0;
static t_sub_4123E0_Buffer_0& __sub_4123E0_Buffer_0 = *(t_sub_4123E0_Buffer_0*)0x00443378;
typedef char t_sub_4123E0_byte_4456F0;
static t_sub_4123E0_byte_4456F0& __sub_4123E0_byte_4456F0 = *(t_sub_4123E0_byte_4456F0*)0x004456F0;
typedef int t_sub_4123E0_dword_4456E8;
static t_sub_4123E0_dword_4456E8& __sub_4123E0_dword_4456E8 = *(t_sub_4123E0_dword_4456E8*)0x004456E8;
typedef int t_sub_4123E0_n0x2000;
static t_sub_4123E0_n0x2000& __sub_4123E0_n0x2000 = *(t_sub_4123E0_n0x2000*)0x004456FC;
typedef int t_sub_4123E0_n0x2000_0;
static t_sub_4123E0_n0x2000_0& __sub_4123E0_n0x2000_0 = *(t_sub_4123E0_n0x2000_0*)0x004456F8;
typedef int t_sub_4123E0_n0x2000_1;
static t_sub_4123E0_n0x2000_1& __sub_4123E0_n0x2000_1 = *(t_sub_4123E0_n0x2000_1*)0x004456F4;
typedef int t_sub_4123E0_n0x7F800000;
static t_sub_4123E0_n0x7F800000& __sub_4123E0_n0x7F800000 = *(t_sub_4123E0_n0x7F800000*)0x004456E4;
typedef int t_sub_4123E0_n0x800000;
static t_sub_4123E0_n0x800000& __sub_4123E0_n0x800000 = *(t_sub_4123E0_n0x800000*)0x004456E0;


PROBE_DECL(__sub_4123E0)
unsigned int __sub_4123E0(unsigned int n8193)
{
  PROBE_HIT(__sub_4123E0);
  unsigned int __sub_4123E0_n0x800000; // ebx
  unsigned int __sub_4123E0_n0x7F800000; // ecx
  unsigned int v3; // edx
  unsigned __int8 *Buffer; // ebp
  int v5; // ecx
  unsigned int n0x800000_2; // ebp
  unsigned int result; // eax
  int n0x800000_1; // ebx

  __sub_4123E0_n0x800000 = ::__sub_4123E0_n0x800000;
  __sub_4123E0_n0x7F800000 = ::__sub_4123E0_n0x7F800000;
  __sub_4123E0_n0x2000 = n8193;
  if ( (unsigned int)::__sub_4123E0_n0x800000 <= 0x800000 )
  {
    LOBYTE(v3) = __sub_4123E0_byte_4456F0;
    Buffer = (unsigned __int8 *)__sub_4123E0_Buffer_0;
    do
    {
      v5 = (unsigned __int8)((_BYTE)v3 << 7) | (__sub_4123E0_n0x7F800000 << 8);
      v3 = *Buffer++;
      __sub_4123E0_Buffer_0 = (int)Buffer;
      __sub_4123E0_n0x7F800000 = (v3 >> 1) | v5;
      __sub_4123E0_n0x800000 <<= 8;
    }
    while ( __sub_4123E0_n0x800000 <= 0x800000 );
    __sub_4123E0_byte_4456F0 = v3;
  }
  n0x800000_2 = __sub_4123E0_n0x800000 / n8193;
  __sub_4123E0_dword_4456E8 = __sub_4123E0_n0x800000 / n8193;
  result = n8193 - 1;
  if ( __sub_4123E0_n0x7F800000 / (__sub_4123E0_n0x800000 / n8193) < n8193 )
    result = __sub_4123E0_n0x7F800000 / (__sub_4123E0_n0x800000 / n8193);
  __sub_4123E0_n0x2000_1 = result;
  __sub_4123E0_n0x2000_0 = result + 1;
  n0x800000_1 = __sub_4123E0_n0x800000 - n0x800000_2 * result;
  ::__sub_4123E0_n0x7F800000 = __sub_4123E0_n0x7F800000 - n0x800000_2 * result;
  if ( result + 1 < n8193 )
    n0x800000_1 = n0x800000_2;
  ::__sub_4123E0_n0x800000 = n0x800000_1;
  return result;
}

