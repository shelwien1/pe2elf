// sub_428050 @ 0x00428050 — __cdecl
// Extracted from BMF.cpp:32467-32477 by extract.py per incdec.md.

static inline size_t __fwd_sub_428050_sub_4280B0(int a0, int a1, int a2, void *a3, signed int a4) { return __sub_4280B0(a0, a1, a2, (char *)a3, a4); }
#define sub_4280B0 __fwd_sub_428050_sub_4280B0

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
BMF_REALIGN int __sub_428050(int BMF_Options, int FSQ, int n7)
{
  alignas(16) unsigned char __hexrays_frame[156];   // original frame, ebp-0x8c..ebp+0x0
  char (&Buffer)[64] = *(char (*)[64])(__hexrays_frame + 0);
  char (&Destination)[64] = *(char (*)[64])(__hexrays_frame + 64);
  int &v6 = *(int *)(__hexrays_frame + 128);
  PROBE_HIT(__sub_428050);

  sprintf(Buffer, "%d", n7);
  sub_4280B0(BMF_Options, FSQ, (int)Buffer, Destination, 64);
  sscanf(Destination, "%d", &v6);
  return v6;
}

#undef FILE
#undef sprintf
#undef sscanf
#undef sub_4280B0
