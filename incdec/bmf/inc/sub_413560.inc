// sub_413560 @ 0x00413560 — __thiscall
// Extracted from BMF.cpp:17702-17713 by extract.py per incdec.md.


PROBE_DECL(__sub_413560)
__attribute__((force_align_arg_pointer)) __attribute__((thiscall)) _WORD *__sub_413560(_WORD *_this)
{
  PROBE_HIT(__sub_413560);
  *(_this + 1) = 8;
  *(_this + 2) = 2;
  *(_this + 3) = 2;
  *(_this + 4) = 2;
  *(_this + 5) = 2;
  *(_this + 6) = 3;
  *(_this + 7) = 3;
  *_this = 22;
  return _this;
}

