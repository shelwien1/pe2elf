// sub_402EF0 @ 0x00402EF0 — __userpurge
// Extracted from BMF.cpp:2517-2569 by extract.py per incdec.md.

#define exit_402E40 __exit_402E40
static inline char * __fwd_sub_402EF0_sub_403820(int a0, const __m128 &a1, const __m128 &a2, int a3, void *a4) { return __sub_403820(a0, a1, a2, a3, (int *)a4); }
#define sub_403820 __fwd_sub_402EF0_sub_403820

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___feof
#define __PE_DECL___feof
typedef int t_feof(FILE1 *);   // _feof
static t_feof& __feof = *(t_feof*)0x0042D33B;
#endif
#define feof __feof
#ifndef __PE_DECL___fopen
#define __PE_DECL___fopen
typedef FILE1 * t_fopen(const char *, const char *);   // _fopen
static t_fopen& __fopen = *(t_fopen*)0x0042CDB9;
#endif
#define fopen __fopen
#ifndef __PE_DECL___fseek
#define __PE_DECL___fseek
typedef int t_fseek(FILE1 *, long, int);   // _fseek
static t_fseek& __fseek = *(t_fseek*)0x0042D0DD;
#endif
#define fseek __fseek
#define FILE FILE1

PROBE_DECL(__sub_402EF0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) int __sub_402EF0(_DWORD *v2, char *FileName, int a2)
{
  PROBE_HIT(__sub_402EF0);

  __m128 v3; // xmm1
  __m128 v4; // xmm3
  int v5; // edi
  const char *a_b; // edx
  Stream *Stream_v; // eax
  int v8; // eax
  int v9; // edx
  Stream *Stream_1; // ebx

  v5 = (int)v2;
  a_b = "a+b";
  if ( a2 )
    a_b = "rb";
  *v2 = 0;
  Stream_v = fopen(FileName, a_b);
  *(_DWORD *)(v5 + 4) = Stream_v;
  if ( !Stream_v )
    exit_402E40(6, FileName);
  *(_DWORD *)v5 = 0;
  v8 = fseek(Stream_v, 0, 0);
  v9 = *(_DWORD *)(v5 + 4);
  if ( v8 )
  {
LABEL_10:
    if ( !v9 )
LABEL_11:
      exit_402E40(3, FileName);
    return v5;
  }
  if ( !v9 )
    goto LABEL_11;
  if ( !feof(*(FILE **)(v5 + 4)) )
  {
    sub_403820(v5, v3, v4, 1, nullptr);
    Stream_1 = *(FILE **)(v5 + 4);
    if ( !Stream_1 )
      goto LABEL_11;
    if ( !feof(*(FILE **)(v5 + 4)) )
    {
      *(_DWORD *)v5 = 0;
      fseek(Stream_1, 0, 0);
      v9 = *(_DWORD *)(v5 + 4);
      goto LABEL_10;
    }
  }
  return v5;
}

#ifndef BMF_STANDALONE
// __userpurge thunk for sub_402EF0 @ 0x00402EF0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and pops 8 bytes of
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_402EF0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $20, %esp\n"
    "mov %ecx, 4(%esp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "push 12(%esp)\n"
    "call __sub_402EF0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret $8\n"
  );
}
#endif

#undef FILE
#undef feof
#undef fopen
#undef fseek
#undef exit_402E40
#undef sub_403820
