// sub_411FD0 @ 0x00411FD0 — __cdecl
// Extracted from BMF.c:16019-16105 by extract.py per incdec.md.

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
#ifndef __PE_DECL___dword_4456E8
#define __PE_DECL___dword_4456E8
typedef int t_dword_4456E8;
static t_dword_4456E8& __dword_4456E8 = *(t_dword_4456E8*)0x004456E8;
#endif
#define dword_4456E8 __dword_4456E8
#ifndef __PE_DECL___dword_4456EC
#define __PE_DECL___dword_4456EC
typedef int t_dword_4456EC;
static t_dword_4456EC& __dword_4456EC = *(t_dword_4456EC*)0x004456EC;
#endif
#define dword_4456EC __dword_4456EC
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


PROBE_DECL(__sub_411FD0)
unsigned int __sub_411FD0(int a1, int a2, int a3)
{
  PROBE_HIT(__sub_411FD0);
  unsigned int n0x800000; // ecx
  int n0x7F800000; // ebp
  int v5; // edx
  unsigned int v6; // edi
  int v7; // esi
  int v8; // eax
  unsigned int v9; // ebx
  _BYTE *v10; // ecx
  unsigned int result; // eax
  unsigned int n0x800000_1; // [esp+Ch] [ebp-10h]
  char v13; // [esp+10h] [ebp-Ch]
  int v14; // [esp+14h] [ebp-8h]

  n0x800000 = ::n0x800000;
  if ( (unsigned int)::n0x800000 > 0x800000 )
    goto LABEL_15;
  n0x7F800000 = ::n0x7F800000;
  v5 = dword_4456E8;
  v14 = dword_4456EC;
  do
  {
    ++v14;
    v6 = v5;
    v7 = v5;
    if ( (unsigned int)n0x7F800000 < 0x7F800000 )
    {
      v13 = 0;
    }
    else
    {
      if ( n0x7F800000 >= 0 )
      {
        dword_4456E8 = ++v5;
        goto LABEL_13;
      }
      v13 = 1;
    }
    *(_BYTE *)Buffer_0 = v13 + byte_4456F0;
    v8 = ++Buffer_0;
    if ( v5 )
    {
      n0x800000_1 = n0x800000;
      v9 = 0;
      v10 = (_BYTE *)v8;
      do
      {
        *v10 = v13 - 1;
        v10 = (_BYTE *)++Buffer_0;
        v5 = v7 - v9++ - 1;
      }
      while ( v9 < v6 );
      n0x800000 = n0x800000_1;
      dword_4456E8 = v7 - v6;
    }
    byte_4456F0 = (unsigned int)n0x7F800000 >> 23;
LABEL_13:
    n0x800000 <<= 8;
    n0x7F800000 = (n0x7F800000 << 8) & 0x7FFFFFFF;
  }
  while ( n0x800000 <= 0x800000 );
  dword_4456EC = v14;
  ::n0x7F800000 = n0x7F800000;
LABEL_15:
  result = a1 * (n0x800000 / (a1 + a2));
  n0x88 = a1 + a2;
  if ( a3 )
  {
    ::n0x7F800000 += result;
    ::n0x800000 = n0x800000 - result;
  }
  else
  {
    ::n0x800000 = a1 * (n0x800000 / (a1 + a2));
  }
  return result;
}

#undef Buffer_0
#undef a1
#undef byte_4456F0
#undef dword_4456E8
#undef dword_4456EC
#undef n0x7F800000
#undef n0x800000
#undef n0x88
