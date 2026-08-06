// sub_4148F0 @ 0x004148F0 — __thiscall
// Extracted from BMF.c:19005-19018 by extract.py per incdec.md.


PROBE_DECL(__sub_4148F0)
__attribute__((thiscall)) int __sub_4148F0(_WORD *_this)
{
  PROBE_HIT(__sub_4148F0);
  int n0x4000; // eax

  *_this -= *_this >> 1;
  n0x4000 = (unsigned __int16)*(_this + 2);
  *(_this + 1) -= *(_this + 1) >> 1;
  if ( n0x4000 < 0x4000 )
  {
    n0x4000 += 64;
    *(_this + 2) = n0x4000;
  }
  return n0x4000;
}

