// sub_414800 @ 0x00414800 — __thiscall
// Extracted from BMF.c:18875-18899 by extract.py per incdec.md.


PROBE_DECL(__sub_414800)
__attribute__((thiscall)) unsigned int __sub_414800(unsigned __int16 *_this)
{
  PROBE_HIT(__sub_414800);
  unsigned int n32; // eax
  unsigned int n0x100; // edx

  *(_this + 1) -= *(_this + 1) >> 1;
  *(_this + 2) -= *(_this + 2) >> 1;
  n32 = *(_this + 3) >> 1;
  *(_this + 3) -= n32;
  n0x100 = *_this;
  if ( n0x100 <= 0x100 )
  {
    if ( *_this <= 0x20u )
      n32 = ((16 - n0x100) >> 30) & 0xFFFFFFFE;
    else
      n32 = 32;
    *_this = n0x100 - n32;
  }
  else
  {
    *_this >>= 1;
  }
  return n32;
}

