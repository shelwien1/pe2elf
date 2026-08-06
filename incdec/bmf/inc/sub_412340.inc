// sub_412340 @ 0x00412340 — __cdecl
// Extracted from BMF.c:16275-16321 by extract.py per incdec.md.

#ifndef __PE_DECL___Buffer_0
#define __PE_DECL___Buffer_0
typedef int t_Buffer_0;
static t_Buffer_0& __Buffer_0 = *(t_Buffer_0*)0x00443378;
#endif
#define Buffer_0 __Buffer_0
#ifndef __PE_DECL___a1
#define __PE_DECL___a1
typedef int t_a1[0x10000];
static t_a1& __a1 = *(t_a1*)0x00439BFC;
#endif
#define a1 __a1
#ifndef __PE_DECL___byte_4456F0
#define __PE_DECL___byte_4456F0
typedef char t_byte_4456F0;
static t_byte_4456F0& __byte_4456F0 = *(t_byte_4456F0*)0x004456F0;
#endif
#define byte_4456F0 __byte_4456F0
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
#ifndef __PE_DECL___n0x88
#define __PE_DECL___n0x88
typedef int t_n0x88;
static t_n0x88& __n0x88 = *(t_n0x88*)0x00445704;
#endif
#define n0x88 __n0x88


PROBE_DECL(__sub_412340)
BOOL __sub_412340(int a1, int a2)
{
  PROBE_HIT(__sub_412340);
  unsigned int n0x800000; // ecx
  unsigned int n0x7F800000; // esi
  unsigned int v4; // edx
  unsigned __int8 *v5; // edi
  int v6; // esi
  unsigned int n0x7F800000_1; // eax

  n0x800000 = ::n0x800000;
  n0x7F800000 = ::n0x7F800000;
  if ( (unsigned int)::n0x800000 <= 0x800000 )
  {
    LOBYTE(v4) = byte_4456F0;
    v5 = (unsigned __int8 *)Buffer_0;
    do
    {
      v6 = (unsigned __int8)((_BYTE)v4 << 7) | (n0x7F800000 << 8);
      v4 = *v5++;
      Buffer_0 = (int)v5;
      n0x7F800000 = (v4 >> 1) | v6;
      n0x800000 <<= 8;
    }
    while ( n0x800000 <= 0x800000 );
    byte_4456F0 = v4;
    ::n0x7F800000 = n0x7F800000;
  }
  n0x7F800000_1 = a1 * (n0x800000 / (a1 + a2));
  n0x88 = a1 + a2;
  if ( n0x7F800000 >= n0x7F800000_1 )
  {
    ::n0x800000 = n0x800000 - n0x7F800000_1;
    ::n0x7F800000 = n0x7F800000 - n0x7F800000_1;
  }
  else
  {
    ::n0x800000 = a1 * (n0x800000 / (a1 + a2));
  }
  return n0x7F800000 >= n0x7F800000_1;
}

#undef Buffer_0
#undef a1
#undef byte_4456F0
#undef n0x7F800000
#undef n0x800000
#undef n0x88
