// sub_42C090 @ 0x0042C090 — __thiscall
// Extracted from BMF.c:36515-36519 by extract.py per incdec.md.


// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___fclose
#define __PE_DECL___fclose
typedef int t_fclose(FILE1 *);   // _fclose
static t_fclose& __fclose = *(t_fclose*)0x0042CEB4;
#endif
#define fclose __fclose
#ifndef __PE_DECL___fseek
#define __PE_DECL___fseek
typedef int t_fseek(FILE1 *, long, int);   // _fseek
static t_fseek& __fseek = *(t_fseek*)0x0042D0DD;
#endif
#define fseek __fseek
#define FILE FILE1

PROBE_DECL(__sub_42C090)
__attribute__((thiscall)) int __sub_42C090(FILE **_this)
{
  PROBE_HIT(__sub_42C090);
  fseek(*_this, 0, 2);
  return fclose(*_this);
}

#undef FILE
#undef fclose
#undef fseek
