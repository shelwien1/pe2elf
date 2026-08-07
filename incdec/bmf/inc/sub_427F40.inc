// sub_427F40 @ 0x00427F40 — __cdecl
// Extracted from BMF.c:32448-32464 by extract.py per incdec.md.

static inline size_t __fwd_sub_427F40_sub_4280B0(int a0, int a1, int a2, void *a3, signed int a4) { return __sub_4280B0(a0, a1, a2, (char *)a3, a4); }
#define sub_4280B0 __fwd_sub_427F40_sub_4280B0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL____strcmpi
#define __PE_DECL____strcmpi
typedef int t__strcmpi(const char *, const char *);   // __strcmpi
static t__strcmpi& ___strcmpi = *(t__strcmpi*)0x00437870;
#endif
#define _strcmpi ___strcmpi
#ifndef __PE_DECL___sprintf
#define __PE_DECL___sprintf
typedef int t_sprintf(char *, const char *, ...);   // _sprintf
static t_sprintf& __sprintf = *(t_sprintf*)0x0042CF4D;
#endif
#define sprintf __sprintf
#define FILE FILE1

PROBE_DECL(__sub_427F40)
int __sub_427F40(int BMF_Options, int UseFilters, int a3)
{
  alignas(16) unsigned char __hexrays_frame[156];   // original frame, ebp-0x8c..ebp+0x0
  char (&Buffer)[64] = *(char (*)[64])(__hexrays_frame + 0);
  char (&String1)[76] = *(char (*)[76])(__hexrays_frame + 64);
  PROBE_HIT(__sub_427F40);
  const char *_0; // edx

  _0 = "0";
  if ( a3 )
    _0 = "1";
  sprintf(Buffer, "%s", _0);
  sub_4280B0(BMF_Options, UseFilters, (int)Buffer, String1, 64);
  if ( !_strcmpi(String1, "0") || !_strcmpi(String1, "NO") || !_strcmpi(String1, "Off") || !_strcmpi(String1, "FALSE") )
    return 0;
  if ( _strcmpi(String1, "1") && _strcmpi(String1, "YES") && _strcmpi(String1, "On") && _strcmpi(String1, "TRUE") )
    return a3;
  return 1;
}

#undef FILE
#undef _strcmpi
#undef sprintf
#undef sub_4280B0
