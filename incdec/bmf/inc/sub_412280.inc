// sub_412280 @ 0x00412280 — __cdecl
// Extracted from BMF.c:16212-16253 by extract.py per incdec.md.

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
#ifndef __PE_DECL___n0x2000
#define __PE_DECL___n0x2000
typedef int t_n0x2000;
static t_n0x2000& __n0x2000 = *(t_n0x2000*)0x004456FC;
#endif
#define n0x2000 __n0x2000
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
