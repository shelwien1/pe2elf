// sub_42D3E8 @ 0x0042D3E8 — __cdecl
// Extracted from BMF.c:37135-37141 by extract.py per incdec.md.


// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___flsall
#define __PE_DECL___flsall
typedef int t_flsall(int);   // _flsall
static t_flsall& __flsall = *(t_flsall*)0x0042D3F1;
#endif
#define flsall __flsall
#define FILE FILE1

PROBE_DECL(__sub_42D3E8)
int __sub_42D3E8()
{
  PROBE_HIT(__sub_42D3E8);
  return flsall(1);
}

#undef FILE
#undef flsall
