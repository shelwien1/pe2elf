// sub_428050 @ 0x00428050 — __cdecl
// Extracted from BMF.c:32410-32421 by extract.py per incdec.md.

#ifndef __PE_DECL___sub_4280B0
#define __PE_DECL___sub_4280B0
typedef int t_sub_4280B0(...);
static t_sub_4280B0& __sub_4280B0 = *(t_sub_4280B0*)0x004280B0;
#endif
#define sub_4280B0 __sub_4280B0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___sprintf
#define __PE_DECL___sprintf
typedef int t_sprintf(char *, const char *, ...);   // _sprintf
static t_sprintf& __sprintf = *(t_sprintf*)0x0042CF4D;
#endif
#define sprintf __sprintf
#ifndef __PE_DECL___sscanf
#define __PE_DECL___sscanf
typedef int t_sscanf(const char *, const char *, ...);   // _sscanf
static t_sscanf& __sscanf = *(t_sscanf*)0x0042D662;
#endif
#define sscanf __sscanf
#define FILE FILE1

PROBE_DECL(__sub_428050)
int __sub_428050(int a1, int a2, int a3)
{
  PROBE_HIT(__sub_428050);
  char Buffer[64]; // [esp+0h] [ebp-8Ch] BYREF
  char Destination[64]; // [esp+40h] [ebp-4Ch] BYREF
  int v6; // [esp+80h] [ebp-Ch] BYREF

  sprintf(Buffer, "%d", a3);
  sub_4280B0(a1, a2, (int)Buffer, Destination, 64);
  sscanf(Destination, "%d", &v6);
  return v6;
}

#undef FILE
#undef sprintf
#undef sscanf
#undef sub_4280B0
