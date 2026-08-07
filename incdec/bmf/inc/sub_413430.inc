// sub_413430 @ 0x00413430 — __thiscall
// Extracted from BMF.cpp:17642-17699 by extract.py per incdec.md.

typedef unsigned char t_sub_413430_byte_445714[0x10000];
static t_sub_413430_byte_445714& __sub_413430_byte_445714 = *(t_sub_413430_byte_445714*)(blob1 + 0x00445714 - BMF_BLOB_BASE);
typedef unsigned char t_sub_413430_byte_445715[0x10000];
static t_sub_413430_byte_445715& __sub_413430_byte_445715 = *(t_sub_413430_byte_445715*)(blob1 + 0x00445715 - BMF_BLOB_BASE);
typedef unsigned char t_sub_413430_byte_445716[0x10000];
static t_sub_413430_byte_445716& __sub_413430_byte_445716 = *(t_sub_413430_byte_445716*)(blob1 + 0x00445716 - BMF_BLOB_BASE);
typedef int t_sub_413430_dword_445660[32];
static t_sub_413430_dword_445660& __sub_413430_dword_445660 = *(t_sub_413430_dword_445660*)(blob1 + 0x00445660 - BMF_BLOB_BASE);
typedef int t_sub_413430_n2;
static t_sub_413430_n2& __sub_413430_n2 = *(t_sub_413430_n2*)(blob1 + 0x00443360 - BMF_BLOB_BASE);
typedef int t_sub_413430_n8_0;
static t_sub_413430_n8_0& __sub_413430_n8_0 = *(t_sub_413430_n8_0*)(blob1 + 0x00445710 - BMF_BLOB_BASE);


PROBE_DECL(__sub_413430)
BMF_REALIGN __attribute__((thiscall)) int __sub_413430(unsigned __int16 *_this, int __sub_413430_n2)
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
    v3 = *((unsigned __int8 *)__sub_413430_dword_445660 + __sub_413430_n2);
    v4 = (*(_this + 1) >> 2) & 0xFFFFFFE0;
    if ( ::__sub_413430_n2 == 2 )
      v4 = 15 * (*(_this + 1) >> 5);
    *(_this + v3 + 2) += v4 + 4;
    n0x8000 = *_this + v4 + 4;
    *_this = n0x8000;
    if ( __sub_413430_n2 >= 2 )
    {
      n0x8000 = (unsigned __int8)__sub_413430_byte_445715[4 * v3];
      v11 = __sub_413430_n2 - (unsigned __int8)__sub_413430_byte_445714[4 * v3];
      v5 = (int)(_this + 2 * (unsigned __int8)__sub_413430_byte_445716[4 * v3] + 8);
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
        v8[v13] = n0x2000 + ((__sub_413430_n8_0 * ((unsigned int)(::__sub_413430_n2 == 2) + 5)) >> 3);
      }
      while ( n0x8000 );
    }
  }
  return n0x8000;
}

