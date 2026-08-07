// sub_42A350 @ 0x0042A350 — __cdecl
// Extracted from BMF.cpp:34740-34809 by extract.py per incdec.md.


// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___fclose
#define __PE_DECL___fclose
typedef int t_fclose(FILE1 *);   // _fclose
static t_fclose& __fclose = *(t_fclose*)0x0042CEB4;
#endif
#define fclose __fclose
#ifndef __PE_DECL___fopen
#define __PE_DECL___fopen
typedef FILE1 * t_fopen(const char *, const char *);   // _fopen
static t_fopen& __fopen = *(t_fopen*)0x0042CDB9;
#endif
#define fopen __fopen
#ifndef __PE_DECL___fprintf
#define __PE_DECL___fprintf
typedef int t_fprintf(FILE1 *, const char *, ...);   // _fprintf
static t_fprintf& __fprintf = *(t_fprintf*)0x0042DC8C;
#endif
#define fprintf __fprintf
#ifndef __PE_DECL___fputs
#define __PE_DECL___fputs
typedef int t_fputs(const char *, FILE1 *);   // _fputs
static t_fputs& __fputs = *(t_fputs*)0x0042DC49;
#endif
#define fputs __fputs
#ifndef __PE_DECL___fwrite
#define __PE_DECL___fwrite
typedef unsigned int t_fwrite(const void *, unsigned int, unsigned int, FILE1 *);   // _fwrite
static t_fwrite& __fwrite = *(t_fwrite*)0x0042CF9F;
#endif
#define fwrite __fwrite
#ifndef __PE_DECL___putc
#define __PE_DECL___putc
typedef int t_putc(int, FILE1 *);   // _putc
static t_putc& __putc = *(t_putc*)0x0042D0CD;
#endif
#define putc __putc
#define FILE FILE1

PROBE_DECL(__sub_42A350)
BMF_REALIGN int __sub_42A350(unsigned __int16 *a1, char *FileName)
{
  PROBE_HIT(__sub_42A350);
  int n24; // eax
  Stream *Stream_v; // ebp
  int n8; // eax
  int n52; // eax
  bool v7; // zf
  char v8; // dl
  unsigned __int8 *p_Character; // ebx
  int v10; // edi

  n24 = a1[5] & 0x3F;
  if ( n24 == 1 || n24 == 8 )
  {
    if ( (a1[5] & 0x40) == 0 )
      return 0;
  }
  else if ( n24 != 24 )
  {
    return 0;
  }
  Stream_v = fopen(FileName, "wb");
  if ( Stream_v )
  {
    n8 = a1[5] & 0x3F;
    if ( n8 == 1 )
    {
      n52 = 52;
    }
    else
    {
      v7 = n8 == 8;
      n52 = 54;
      if ( v7 )
        n52 = 53;
    }
    if ( !fprintf(Stream_v, "P%c\n%d %d\n", n52, *a1, a1[1]) )
      return 0;
    v8 = *((_BYTE *)a1 + 10);
    if ( (v8 & 0x3F) != 1 )
    {
      fputs("255\n", Stream_v);
      v8 = *((_BYTE *)a1 + 10);
    }
    if ( (v8 & 0x3F) != 0x18 )
    {
      if ( fwrite(a1 + 8, 1u, *((_DWORD *)a1 + 3), Stream_v) != *((_DWORD *)a1 + 3) )
        return 0;
      goto LABEL_17;
    }
    if ( a1[1] * *a1 <= 0 )
    {
LABEL_17:
      fclose(Stream_v);
      return 1;
    }
    p_Character = (unsigned __int8 *)(a1 + 8);
    v10 = 0;
    while ( putc(p_Character[2], Stream_v) == p_Character[2]
         && putc(p_Character[1], Stream_v) == p_Character[1]
         && putc(*p_Character, Stream_v) == *p_Character )
    {
      ++v10;
      p_Character += 3;
      if ( v10 >= a1[1] * *a1 )
        goto LABEL_17;
    }
  }
  return 0;
}

#undef FILE
#undef fclose
#undef fopen
#undef fprintf
#undef fputs
#undef fwrite
#undef putc
