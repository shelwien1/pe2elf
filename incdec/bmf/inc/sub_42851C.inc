// sub_42851C @ 0x0042851C — __usercall
// Extracted from BMF.cpp:32733-32978 by extract.py per incdec.md.

static inline _BYTE * __fwd_sub_42851C_sub_429DB0(void *a0, void *a1) { return __sub_429DB0((_BYTE *)a0, (char *)a1); }
#define sub_429DB0 __fwd_sub_42851C_sub_429DB0
static inline int __fwd_sub_42851C_sub_42CAD0(void *a0, int a1) { return __sub_42CAD0((_BYTE *)a0, a1); }
#define sub_42CAD0 __fwd_sub_42851C_sub_42CAD0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL____access
#define __PE_DECL____access
typedef int t__access(const char *, int);   // __access
static t__access& ___access = *(t__access*)0x004314F0;
#endif
#define _access ___access
#ifndef __PE_DECL___fclose
#define __PE_DECL___fclose
typedef int t_fclose(FILE1 *);   // _fclose
static t_fclose& __fclose = *(t_fclose*)0x0042CEB4;
#endif
#define fclose __fclose
#ifndef __PE_DECL___feof
#define __PE_DECL___feof
typedef int t_feof(FILE1 *);   // _feof
static t_feof& __feof = *(t_feof*)0x0042D33B;
#endif
#define feof __feof
#ifndef __PE_DECL___fgets
#define __PE_DECL___fgets
typedef char * t_fgets(char *, int, FILE1 *);   // _fgets
static t_fgets& __fgets = *(t_fgets*)0x0042D696;
#endif
#define fgets __fgets
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
#ifndef __PE_DECL___remove
#define __PE_DECL___remove
typedef int t_remove(const char *);   // _remove
static t_remove& __remove = *(t_remove*)0x0042CF23;
#endif
#define remove __remove
#ifndef __PE_DECL___rename
#define __PE_DECL___rename
typedef int t_rename(const char *, const char *);   // _rename
static t_rename& __rename = *(t_rename*)0x0042DC1B;
#endif
#define rename __rename
#ifndef __PE_DECL___tmpnam
#define __PE_DECL___tmpnam
typedef char * t_tmpnam(char *);   // _tmpnam
static t_tmpnam& __tmpnam = *(t_tmpnam*)0x0042DB25;
#endif
#define tmpnam __tmpnam
#define FILE FILE1

PROBE_DECL(__sub_42851C)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) int __sub_42851C(int BMF_Options_3, const char *BMF_Options_1, const char *Buffer)
{
  alignas(16) unsigned char __hexrays_frame[556];   // original frame, ebp-0x180..ebp+0x9c
  char (&Buffera)[256] = *(char (*)[256])(__hexrays_frame + 0);
  char (&FileName)[128] = *(char (*)[128])(__hexrays_frame + 256);
  char (&OldFilename)[128] = *(char (*)[128])(__hexrays_frame + 384);
  char * &i_1 = *(char * *)(__hexrays_frame + 512);
  const char * &Buffer_1 = *(const char * *)(__hexrays_frame + 516);
  int &BMF_Options_2 = *(int *)(__hexrays_frame + 520);
  int &BMF_Options = *(int *)(__hexrays_frame + 524);
  FILE * &Stream_v = *(FILE * *)(__hexrays_frame + 528);
  int &v48 = *(int *)(__hexrays_frame + 532);
  Stream * &Stream_4 = *(Stream * *)(__hexrays_frame + 536);
  PROBE_HIT(__sub_42851C);
  const char *FileName_1; // eax
  char *NewFilename; // eax
  bool v9; // zf
  int i_2; // eax
  Stream *Stream_3; // ebp
  int i_3; // esi
  int v13; // ecx
  char *i; // ebx
  unsigned int n0x20; // ecx
  char *v16; // eax
  int j_1; // edx
  int j; // ecx
  unsigned int n0x20_1; // ecx
  Stream *Stream_5; // esi
  Stream *Stream_6; // ebx
  Stream *Stream_1; // eax
  Stream *Stream_2; // ebp
  unsigned __int8 *v24; // eax
  int v25; // ecx
  unsigned int n0x20_3; // ecx
  char *v27; // eax
  int n_1; // edx
  int n; // ecx
  unsigned int n0x20_4; // ecx
  int i_4; // eax
  const char *Buffer_2; // ebx
  unsigned __int8 *v33; // eax
  int v34; // ecx
  char *k; // esi
  unsigned int n0x20_2; // ecx
  const char *Buffer_3; // esi
  int C; // ebx
  int m; // eax

  FileName_1 = sub_429DB0(OldFilename, "ini");
  if ( _access(FileName_1, 0) )
  {
    Stream_1 = fopen(OldFilename, "wt");
    Stream_2 = Stream_1;
    if ( Stream_1 )
    {
      fprintf(Stream_1, "\n[ %s ]\n", (const char *)BMF_Options_3);
      fprintf(Stream_2, "%s = %s  ; Added by program\n", BMF_Options_1, Buffer);
      fclose(Stream_2);
      return 1;
    }
    return 0;
  }
  if ( _access(OldFilename, 2) )
    return 0;
  NewFilename = tmpnam(FileName);
  if ( rename(OldFilename, NewFilename) )
    return 0;
  Stream_4 = fopen(OldFilename, "wt");
  if ( !Stream_4 )
    return 0;
  Stream_v = fopen(FileName, "rt");
  if ( !Stream_v )
    return 0;
  v9 = !_BitScanForward(
          (unsigned int *)&i_2,
          (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, *(__m128i *)(BMF_Options_3 & 0xFFFFFFF0))) >> ((BMF_Options_3 & 0xF) & 31));
  if ( v9 )
    i_2 = __intel_sse2_strlen(BMF_Options_3 & 0xF, BMF_Options_3);
  i_1 = (char *)i_2;
  if ( feof(Stream_v) )
  {
    i_1 = nullptr;
  }
  else
  {
    Stream_3 = Stream_v;
    BMF_Options_2 = BMF_Options_3;
    i_3 = (int)i_1;
    v48 = 0;
    BMF_Options = (int)BMF_Options_1;
    Buffer_1 = Buffer;
    do
    {
      fgets(Buffera, 256, Stream_3);
      v13 = (unsigned __int8)Buffera[0];
      for ( i = Buffera; ; v13 = (unsigned __int8)*i )
      {
        n0x20 = v13 - 9;
        if ( n0x20 >= 0x20 || ((1 << (n0x20 & 31)) & 0x800011) == 0 )
          break;
        ++i;
      }
      if ( v48 )
      {
        if ( *i == 91 )
        {
          BMF_Options_1 = (const char *)BMF_Options;
          i_1 = i;
          Buffer = Buffer_1;
          goto LABEL_30;
        }
        if ( sub_42CAD0(i, BMF_Options) == i_3 )
        {
          v16 = &i[i_3 + 1];
          i += i_3;
          j_1 = *i;
          for ( j = (unsigned __int8)j_1; ; j = (unsigned __int8)j_1 )
          {
            n0x20_1 = j - 9;
            if ( n0x20_1 >= 0x20 || ((1 << (n0x20_1 & 31)) & 0x800011) == 0 )
              break;
            j_1 = *v16;
            ++i;
            ++v16;
          }
          if ( j_1 == 61 )
          {
            i_1 = i;
            Buffer_2 = Buffer_1;
            v33 = (unsigned __int8 *)(i_1 + 2);
            v34 = (unsigned __int8)*++i_1;
            for ( k = i_1; ; ++k )
            {
              n0x20_2 = v34 - 9;
              if ( n0x20_2 >= 0x20 || ((1 << (n0x20_2 & 31)) & 0x800011) == 0 )
                break;
              v34 = *v33++;
            }
            i_1 = k;
            *k = 0;
            Buffer_3 = k + 1;
            fprintf(Stream_4, "%s%s", Buffera, Buffer_2);
            if ( strchr(Buffer_3, 59) )
            {
              C = i_1[1];
              for ( m = isspace(C); !m; m = isspace(C) )
              {
                ++Buffer_3;
                if ( C == 59 )
                  break;
                C = *Buffer_3;
              }
              fputs(Buffer_3, Stream_4);
            }
            else
            {
              fputs("  ; Changed by program\n", Stream_4);
            }
            goto LABEL_32;
          }
        }
      }
      else if ( *i == 91 )
      {
        v24 = (unsigned __int8 *)(i + 2);
        v25 = (unsigned __int8)*++i;
        while ( 1 )
        {
          n0x20_3 = v25 - 9;
          if ( n0x20_3 >= 0x20 || ((1 << (n0x20_3 & 31)) & 0x800011) == 0 )
            break;
          v25 = *v24;
          ++i;
          ++v24;
        }
        if ( sub_42CAD0(i, BMF_Options_2) == i_3 )
        {
          v27 = &i[i_3 + 1];
          i += i_3;
          n_1 = *i;
          for ( n = (unsigned __int8)n_1; ; n = (unsigned __int8)n_1 )
          {
            n0x20_4 = n - 9;
            if ( n0x20_4 >= 0x20 || ((1 << (n0x20_4 & 31)) & 0x800011) == 0 )
              break;
            n_1 = *v27;
            ++i;
            ++v27;
          }
          if ( n_1 == 93 )
          {
            v9 = !_BitScanForward(
                    (unsigned int *)&i_4,
                    (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, *(__m128i *)(BMF_Options & 0xFFFFFFF0))) >> ((BMF_Options & 0xF) & 31));
            if ( v9 )
              i_4 = __intel_sse2_strlen(BMF_Options & 0xF, BMF_Options);
            v48 = 1;
            i_3 = i_4;
          }
        }
      }
      if ( fputs(Buffera, Stream_4) == -1 )
      {
        fclose(Stream_v);
        fclose(Stream_4);
        remove(OldFilename);
        rename(FileName, OldFilename);
        return 0;
      }
    }
    while ( !feof(Stream_3) );
    BMF_Options_3 = BMF_Options_2;
    BMF_Options_1 = (const char *)BMF_Options;
    i_1 = i;
    Buffer = Buffer_1;
    if ( v48 )
      goto LABEL_30;
  }
  fprintf(Stream_4, "\n[ %s ]\n", (const char *)BMF_Options_3);
LABEL_30:
  fprintf(Stream_4, "%s = %s  ; Added by program\n", BMF_Options_1, Buffer);
  if ( *i_1 == 91 )
    fputs(Buffera, Stream_4);
LABEL_32:
  if ( !feof(Stream_v) )
  {
    Stream_5 = Stream_v;
    Stream_6 = Stream_4;
    while ( fgets(Buffera, 256, Stream_5) )
    {
      if ( fputs(Buffera, Stream_6) == -1 )
      {
        fclose(Stream_v);
        fclose(Stream_4);
        remove(OldFilename);
        rename(FileName, OldFilename);
        return 0;
      }
      if ( feof(Stream_5) )
        break;
    }
  }
  fclose(Stream_v);
  fclose(Stream_4);
  remove(FileName);
  return 1;
}

#ifndef BMF_STANDALONE
// __usercall thunk for sub_42851C @ 0x0042851C: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_42851C()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $20, %esp\n"
    "mov %eax, 4(%esp)\n"
    "mov %edx, 8(%esp)\n"
    "mov %ecx, 12(%esp)\n"
    "push 12(%esp)\n"
    "push 12(%esp)\n"
    "push 12(%esp)\n"
    "call __sub_42851C\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}
#endif

#undef FILE
#undef _access
#undef fclose
#undef feof
#undef fgets
#undef fopen
#undef fprintf
#undef fputs
#undef remove
#undef rename
#undef tmpnam
#undef sub_429DB0
#undef sub_42CAD0
