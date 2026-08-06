// sub_4346D0 @ 0x004346D0 — __cdecl
// Extracted from BMF.c:37231-37316 by extract.py per incdec.md.

typedef int t_sub_4346D0_n1024;
static t_sub_4346D0_n1024& __sub_4346D0_n1024 = *(t_sub_4346D0_n1024*)0x00445B5C;
#define n1024 __sub_4346D0_n1024

#define sub_434A30 __sub_434A30

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___exit
#define __PE_DECL___exit
typedef void t_exit(int);   // _exit
static t_exit& __exit = *(t_exit*)0x0042D216;
#endif
#define exit __exit
#ifndef __PE_DECL___irc__get_msg
#define __PE_DECL___irc__get_msg
typedef char * t_irc__get_msg(int, int, void *);   // _irc__get_msg
static t_irc__get_msg& __irc__get_msg = *(t_irc__get_msg*)0x00434C00;
#endif
#define irc__get_msg __irc__get_msg
#ifndef __PE_DECL___irc__print
#define __PE_DECL___irc__print
typedef int t_irc__print(const char *, ...);   // _irc__print
static t_irc__print& __irc__print = *(t_irc__print*)0x00434D40;
#endif
#define irc__print __irc__print
#define FILE FILE1

PROBE_DECL(__sub_4346D0)
BMF_SSE void __sub_4346D0(char n3)
{
  PROBE_HIT(__sub_4346D0);
  int v1; // esi
  int v2; // ebx
  int v3; // esi
  int v4; // ebx
  const char *msg; // eax
  char ArgList_1; // [esp-28h] [ebp-23Ch]
  char ArgList; // [esp-4h] [ebp-218h]
  _DWORD v8[128]; // [esp+0h] [ebp-214h] BYREF
  unsigned int v9; // [esp+200h] [ebp-14h]

  while ( (n1024 & 0xFFFFF800) == 0 && (n1024 & 0x400) == 0 )
  {
    if ( (n1024 & 0xFFFFFE00) != 0 )
    {
      v3 = n3 & 2;
      v4 = n3 & 4;
      if ( (n3 & 2) != 0 || (n3 & 4) != 0 )
      {
        memset(v8, 0, sizeof(v8));
        _fxsave(v8);
        if ( (v8[7] & 0x40) == 0 )
          v3 = 0;
        if ( (v8[7] & 0x20000) == 0 )
          v4 = 0;
      }
      if ( (n3 & 1) != 0 )
      {
        v9 = _mm_getcsr() | 0x8000;
        _mm_setcsr(v9);
      }
      if ( v3 )
      {
        v9 = _mm_getcsr() | 0x40;
        _mm_setcsr(v9);
      }
      if ( v4 )
      {
        v9 = _mm_getcsr() | 0x20000;
        _mm_setcsr(v9);
      }
      return;
    }
    if ( n1024 )
    {
      irc__print(1, 0, 0, v8[5]);
      irc__print(1, 23, 0, v8[2]);
      msg = (const char *)irc__get_msg(45, 0, ArgList);
      strncpy((char *)&v8[5], msg, 0x200u);
      irc__print(1, 24, 1, (char)&v8[5]);
      irc__print(1, 0, 0, ArgList_1);
      exit(1);
    }
    sub_434A30();
  }
  v1 = n3 & 2;
  v2 = n3 & 4;
  if ( (n3 & 4) != 0 )
  {
    memset(v8, 0, sizeof(v8));
    _fxsave(v8);
    if ( (v8[7] & 0x40) == 0 )
      v1 = 0;
    if ( (v8[7] & 0x20000) == 0 )
      v2 = 0;
  }
  if ( (n3 & 1) != 0 )
  {
    v9 = _mm_getcsr() | 0x8000;
    _mm_setcsr(v9);
  }
  if ( v1 )
  {
    v9 = _mm_getcsr() | 0x40;
    _mm_setcsr(v9);
  }
  if ( v2 )
  {
    v9 = _mm_getcsr() | 0x20000;
    _mm_setcsr(v9);
  }
}

#undef FILE
#undef exit
#undef irc__get_msg
#undef irc__print
#undef n1024
#undef sub_434A30
