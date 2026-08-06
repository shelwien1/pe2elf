// sub_427F40 @ 0x00427F40 — __cdecl
// Extracted from BMF.c:32391-32409 by extract.py per incdec.md.

#ifndef __PE_DECL___a1
#define __PE_DECL___a1
typedef int t_a1[0x10000];
static t_a1& __a1 = *(t_a1*)0x00439BFC;
#endif
#define a1 __a1

#ifndef __PE_DECL___sub_4280B0
#define __PE_DECL___sub_4280B0
typedef int t_sub_4280B0(...);
static t_sub_4280B0& __sub_4280B0 = *(t_sub_4280B0*)0x004280B0;
#endif
#define sub_4280B0 __sub_4280B0

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
int __sub_427F40(int a1, int a2, int a3)
{
  PROBE_HIT(__sub_427F40);
  const char *_0; // edx
  char Buffer[64]; // [esp+0h] [ebp-8Ch] BYREF
  char String1[76]; // [esp+40h] [ebp-4Ch] BYREF

  _0 = "0";
  if ( a3 )
    _0 = "1";
  sprintf(Buffer, "%s", _0);
  sub_4280B0(a1, a2, (int)Buffer, String1, 64);
  if ( !_strcmpi(String1, "0") || !_strcmpi(String1, "NO") || !_strcmpi(String1, "Off") || !_strcmpi(String1, "FALSE") )
    return 0;
  if ( _strcmpi(String1, "1") && _strcmpi(String1, "YES") && _strcmpi(String1, "On") && _strcmpi(String1, "TRUE") )
    return a3;
  return 1;
}

#undef FILE
#undef _strcmpi
#undef sprintf
#undef a1
#undef sub_4280B0
