// sub_412110 @ 0x00412110 — __cdecl
// Extracted from BMF.c:16106-16211 by extract.py per incdec.md.

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


PROBE_DECL(__sub_412110)
int __sub_412110(int a1, int a2)
{
  PROBE_HIT(__sub_412110);
  int v2; // esi
  unsigned int v3; // ebp
  unsigned int n0x800000; // ecx
  unsigned int v5; // ebx
  int v6; // ebx
  int n0x7F800000_1; // esi
  unsigned int v8; // edi
  int v9; // ebp
  int v10; // eax
  unsigned int v11; // edx
  _BYTE *v12; // ecx
  int v13; // edx
  int n0x800000_3; // eax
  int n0x800000_2; // ecx
  int n0x7F800000; // [esp+0h] [ebp-20h]
  unsigned int v17; // [esp+4h] [ebp-1Ch]
  unsigned int n0x800000_1; // [esp+4h] [ebp-1Ch]
  char v19; // [esp+8h] [ebp-18h]
  int v20; // [esp+Ch] [ebp-14h]

  v2 = a1;
  v3 = a2;
  n0x800000 = ::n0x800000;
  n0x2000 = a2;
  dword_4456F4 = a1;
  n0x7F800000 = ::n0x7F800000;
  v5 = a1 + 1;
  n0x2000_0 = a1 + 1;
  if ( (unsigned int)::n0x800000 > 0x800000 )
  {
    v17 = n0x2000;
    goto LABEL_16;
  }
  v6 = dword_4456E8;
  n0x7F800000_1 = ::n0x7F800000;
  v20 = dword_4456EC;
  do
  {
    ++v20;
    v8 = v6;
    v9 = v6;
    if ( (unsigned int)n0x7F800000_1 < 0x7F800000 )
    {
      v19 = 0;
    }
    else
    {
      if ( n0x7F800000_1 >= 0 )
      {
        dword_4456E8 = ++v6;
        goto LABEL_14;
      }
      v19 = 1;
    }
    *(_BYTE *)Buffer_0 = v19 + byte_4456F0;
    v10 = ++Buffer_0;
    if ( v6 )
    {
      n0x800000_1 = n0x800000;
      v11 = 0;
      v12 = (_BYTE *)v10;
      do
      {
        *v12 = v19 - 1;
        v12 = (_BYTE *)++Buffer_0;
        v6 = v9 - v11++ - 1;
      }
      while ( v11 < v8 );
      n0x800000 = n0x800000_1;
      dword_4456E8 = v9 - v8;
    }
    byte_4456F0 = (unsigned int)n0x7F800000_1 >> 23;
LABEL_14:
    n0x800000 <<= 8;
    n0x7F800000_1 = (n0x7F800000_1 << 8) & 0x7FFFFFFF;
  }
  while ( n0x800000 <= 0x800000 );
  v3 = n0x2000;
  v5 = n0x2000_0;
  n0x7F800000 = n0x7F800000_1;
  v2 = dword_4456F4;
  dword_4456EC = v20;
  v17 = n0x2000;
LABEL_16:
  v13 = n0x800000 / v17 * v2;
  n0x800000_3 = (v5 - v2) * (n0x800000 / v17);
  n0x800000_2 = n0x800000 - v13;
  if ( v5 < v3 )
    n0x800000_2 = n0x800000_3;
  ::n0x7F800000 = n0x7F800000 + v13;
  ::n0x800000 = n0x800000_2;
  return n0x800000_3;
}

#undef Buffer_0
#undef a1
#undef byte_4456F0
#undef dword_4456E8
#undef dword_4456EC
#undef dword_4456F4
#undef n0x2000
#undef n0x2000_0
#undef n0x7F800000
#undef n0x800000
