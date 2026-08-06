// sub_402FB0 @ 0x00402FB0 — __thiscall
// Extracted from BMF.c:2572-2583 by extract.py per incdec.md.


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

PROBE_DECL(__sub_402FB0)
__attribute__((thiscall)) Stream *__sub_402FB0(FILE **_this)
{
  PROBE_HIT(__sub_402FB0);
  Stream *Stream_v; // eax

  Stream_v = *(_this + 1);
  if ( Stream_v )
  {
    fseek(Stream_v, 0, 2);
    return (FILE *)fclose(*(_this + 1));
  }
  return Stream_v;
}

#undef FILE
#undef fclose
#undef fseek
