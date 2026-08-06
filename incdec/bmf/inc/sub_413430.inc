// sub_413430 @ 0x00413430 — __thiscall
// Extracted from BMF.c:17583-17642 by extract.py per incdec.md.

#ifndef __PE_DECL___byte_445714
#define __PE_DECL___byte_445714
typedef unsigned char t_byte_445714[0x10000];
static t_byte_445714& __byte_445714 = *(t_byte_445714*)0x00445714;
#endif
#define byte_445714 __byte_445714
#ifndef __PE_DECL___byte_445715
#define __PE_DECL___byte_445715
typedef unsigned char t_byte_445715[0x10000];
static t_byte_445715& __byte_445715 = *(t_byte_445715*)0x00445715;
#endif
#define byte_445715 __byte_445715
#ifndef __PE_DECL___byte_445716
#define __PE_DECL___byte_445716
typedef unsigned char t_byte_445716[0x10000];
static t_byte_445716& __byte_445716 = *(t_byte_445716*)0x00445716;
#endif
#define byte_445716 __byte_445716
#ifndef __PE_DECL___dword_445660
#define __PE_DECL___dword_445660
typedef int t_dword_445660[32];
static t_dword_445660& __dword_445660 = *(t_dword_445660*)0x00445660;
#endif
#define dword_445660 __dword_445660
#ifndef __PE_DECL___n2
#define __PE_DECL___n2
typedef int t_n2;
static t_n2& __n2 = *(t_n2*)0x00443360;
#endif
#define n2 __n2
#ifndef __PE_DECL___n8_0
#define __PE_DECL___n8_0
typedef int t_n8_0;
static t_n8_0& __n8_0 = *(t_n8_0*)0x00445710;
#endif
#define n8_0 __n8_0


PROBE_DECL(__sub_413430)
__attribute__((thiscall)) int __sub_413430(unsigned __int16 *_this, int n2)
{
  PROBE_HIT(__sub_413430);
  int n0x8000; // eax
  int v3; // esi
  unsigned int v4; // eax
  int v5; // edi
  int v6; // esi
  int v7; // ecx
  _WORD *v8; // ebx
  unsigned int n0x2000; // edi
  unsigned int v10; // edx
  int v11; // [esp+8h] [ebp-14h]
  int v12; // [esp+Ch] [ebp-10h]
  BOOL v13; // [esp+10h] [ebp-Ch]

  n0x8000 = *_this;
  if ( (unsigned int)n0x8000 <= 0x8000 )
  {
    v3 = *((unsigned __int8 *)dword_445660 + n2);
    v4 = (*(_this + 1) >> 2) & 0xFFFFFFE0;
    if ( ::n2 == 2 )
      v4 = 15 * (*(_this + 1) >> 5);
    *(_this + v3 + 2) += v4 + 4;
    n0x8000 = *_this + v4 + 4;
    *_this = n0x8000;
    if ( n2 >= 2 )
    {
      n0x8000 = (unsigned __int8)byte_445715[4 * v3];
      v11 = n2 - (unsigned __int8)byte_445714[4 * v3];
      v5 = (int)(_this + 2 * (unsigned __int8)byte_445716[4 * v3] + 8);
      v6 = 0;
      v12 = v5;
      v7 = 1;
      do
      {
        v8 = (_WORD *)(v12 + 4 * (v6 + v7));
        n0x2000 = (unsigned __int16)v8[(n0x8000 & v11) != 0];
        v13 = (n0x8000 & v11) != 0;
        if ( n0x2000 > 0x2000 )
        {
          v10 = (unsigned __int16)v8[1];
          *v8 -= *v8 >> 1;
          v8[1] = v10 - (v10 >> 1);
          LOWORD(n0x2000) = v8[v13];
        }
        v7 *= 2;
        n0x8000 >>= 1;
        v6 = v13 + 2 * v6;
        v8[v13] = n0x2000 + ((n8_0 * ((unsigned int)(::n2 == 2) + 5)) >> 3);
      }
      while ( n0x8000 );
    }
  }
  return n0x8000;
}

#undef byte_445714
#undef byte_445715
#undef byte_445716
#undef dword_445660
#undef n2
#undef n8_0
