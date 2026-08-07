// sub_4284E0 @ 0x004284E0 — __cdecl
// Extracted from BMF.c:32724-32730 by extract.py per incdec.md.

#define sub_42851C __sub_42851C

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___sprintf
#define __PE_DECL___sprintf
typedef int t_sprintf(char *, const char *, ...);   // _sprintf
static t_sprintf& __sprintf = *(t_sprintf*)0x0042CF4D;
#endif
#define sprintf __sprintf
#define FILE FILE1

PROBE_DECL(__sub_4284E0)
int __sub_4284E0(int BMF_Options, char *Template, int a3)
{
  alignas(16) unsigned char __hexrays_frame[48];   // original frame, ebp-0x20..ebp+0x0
  char (&Buffer)[32] = *(char (*)[32])(__hexrays_frame + 0);
  PROBE_HIT(__sub_4284E0);

  sprintf(Buffer, "%d", a3);
  return sub_42851C(BMF_Options, Template, Buffer);
}

#undef FILE
#undef sprintf
#undef sub_42851C
