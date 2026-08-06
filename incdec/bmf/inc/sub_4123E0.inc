// sub_4123E0 @ 0x004123E0 — __cdecl
// Extracted from BMF.c:16322-16374 by extract.py per incdec.md.

#ifndef __PE_DECL___Buffer_0
#define __PE_DECL___Buffer_0
typedef int t_Buffer_0;
static t_Buffer_0& __Buffer_0 = *(t_Buffer_0*)0x00443378;
#endif
#define Buffer_0 __Buffer_0
#ifndef __PE_DECL___byte_4456F0
#define __PE_DECL___byte_4456F0
typedef char t_byte_4456F0;
static t_byte_4456F0& __byte_4456F0 = *(t_byte_4456F0*)0x004456F0;
#endif
#define byte_4456F0 __byte_4456F0
#ifndef __PE_DECL___dword_4456E8
#define __PE_DECL___dword_4456E8
typedef int t_dword_4456E8;
static t_dword_4456E8& __dword_4456E8 = *(t_dword_4456E8*)0x004456E8;
#endif
#define dword_4456E8 __dword_4456E8
#ifndef __PE_DECL___dword_4456F4
#define __PE_DECL___dword_4456F4
typedef int t_dword_4456F4;
static t_dword_4456F4& __dword_4456F4 = *(t_dword_4456F4*)0x004456F4;
#endif
#define dword_4456F4 __dword_4456F4
#ifndef __PE_DECL___n0x2000
#define __PE_DECL___n0x2000
typedef int t_n0x2000;
static t_n0x2000& __n0x2000 = *(t_n0x2000*)0x004456FC;
#endif
#define n0x2000 __n0x2000
#ifndef __PE_DECL___n0x2000_0
#define __PE_DECL___n0x2000_0
typedef int t_n0x2000_0;
static t_n0x2000_0& __n0x2000_0 = *(t_n0x2000_0*)0x004456F8;
#endif
#define n0x2000_0 __n0x2000_0
#ifndef __PE_DECL___n0x7F800000
#define __PE_DECL___n0x7F800000
typedef int t_n0x7F800000;
static t_n0x7F800000& __n0x7F800000 = *(t_n0x7F800000*)0x004456E4;
#endif
#define n0x7F800000 __n0x7F800000
#ifndef __PE_DECL___n0x800000
#define __PE_DECL___n0x800000
typedef int t_n0x800000;
static t_n0x800000& __n0x800000 = *(t_n0x800000*)0x004456E0;
#endif
#define n0x800000 __n0x800000


PROBE_DECL(__sub_4123E0)
unsigned int __sub_4123E0(unsigned int n8193)
{
  PROBE_HIT(__sub_4123E0);
  unsigned int n0x800000; // ebx
  unsigned int n0x7F800000; // ecx
  unsigned int v3; // edx
  unsigned __int8 *Buffer; // ebp
  int v5; // ecx
  unsigned int n0x800000_2; // ebp
  unsigned int result; // eax
  int n0x800000_1; // ebx

  n0x800000 = ::n0x800000;
  n0x7F800000 = ::n0x7F800000;
  n0x2000 = n8193;
  if ( (unsigned int)::n0x800000 <= 0x800000 )
  {
    LOBYTE(v3) = byte_4456F0;
    Buffer = (unsigned __int8 *)Buffer_0;
    do
    {
      v5 = (unsigned __int8)((_BYTE)v3 << 7) | (n0x7F800000 << 8);
      v3 = *Buffer++;
      Buffer_0 = (int)Buffer;
      n0x7F800000 = (v3 >> 1) | v5;
      n0x800000 <<= 8;
    }
    while ( n0x800000 <= 0x800000 );
    byte_4456F0 = v3;
  }
  n0x800000_2 = n0x800000 / n8193;
  dword_4456E8 = n0x800000 / n8193;
  result = n8193 - 1;
  if ( n0x7F800000 / (n0x800000 / n8193) < n8193 )
    result = n0x7F800000 / (n0x800000 / n8193);
  dword_4456F4 = result;
  n0x2000_0 = result + 1;
  n0x800000_1 = n0x800000 - n0x800000_2 * result;
  ::n0x7F800000 = n0x7F800000 - n0x800000_2 * result;
  if ( result + 1 < n8193 )
    n0x800000_1 = n0x800000_2;
  ::n0x800000 = n0x800000_1;
  return result;
}

#undef Buffer_0
#undef byte_4456F0
#undef dword_4456E8
#undef dword_4456F4
#undef n0x2000
#undef n0x2000_0
#undef n0x7F800000
#undef n0x800000
