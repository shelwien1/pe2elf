// sub_417DB0 @ 0x00417DB0 — __usercall
// Extracted from BMF.cpp:22033-22073 by extract.py per incdec.md.

typedef int t_sub_417DB0_dword_443364;
static t_sub_417DB0_dword_443364& __sub_417DB0_dword_443364 = *(t_sub_417DB0_dword_443364*)0x00443364;
typedef int t_sub_417DB0_n2;
static t_sub_417DB0_n2& __sub_417DB0_n2 = *(t_sub_417DB0_n2*)0x00443360;

static inline void ** __fwd_sub_417DB0_sub_415270(void *a0, char a1) { return __sub_415270((void **)a0, a1); }
#define sub_415270 __fwd_sub_417DB0_sub_415270
#define sub_417980 __sub_417980
static inline void __fwd_sub_417DB0_sub_417E80(void *a0, void *a1) { __sub_417E80((_DWORD *)a0, (char *)a1); }
#define sub_417E80 __fwd_sub_417DB0_sub_417E80
static inline void __fwd_sub_417DB0_sub_422D60(const __m128 &a0, const __m128 &a1, void *a2, int a3, int a4) { __sub_422D60(a0, a1, (_BYTE *)a2, a3, a4); }
#define sub_422D60 __fwd_sub_417DB0_sub_422D60
static inline int __fwd_sub_417DB0_sub_423600(void *a0, void *a1) { return __sub_423600((unsigned __int16 *)a0, (unsigned __int8 *)a1); }
#define sub_423600 __fwd_sub_417DB0_sub_423600
static inline void ** __fwd_sub_417DB0_sub_4273F0(char a0, void *a1, int a2, int a3) { return __sub_4273F0(a0, (_BYTE *)a1, a2, a3); }
#define sub_4273F0 __fwd_sub_417DB0_sub_4273F0
static inline int __fwd_sub_417DB0_sub_427740(void *a0, int a1) { return __sub_427740((unsigned __int16 *)a0, a1); }
#define sub_427740 __fwd_sub_417DB0_sub_427740

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#define FILE FILE1

PROBE_DECL(__sub_417DB0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) void __sub_417DB0(char ArgList, const __m128 &a2__ref, const __m128 &a3__ref, unsigned __int16 *p_i, unsigned __int8 *Src)
{
  PROBE_HIT(__sub_417DB0);
  __m128 a2 = a2__ref;
  __m128 a3 = a3__ref;
  void *v5; // ecx
  void **v6; // ebx

  if ( __sub_417DB0_dword_443364 )
  {
    if ( __sub_417DB0_n2 == 1 )
    {
      if ( (p_i[5] & 0x3F) == 8 )
        sub_4273F0(ArgList, Src, *p_i, p_i[1]);
      else
        sub_427740(p_i, (int)Src);
    }
    else if ( __sub_417DB0_n2 == 2 )
    {
      if ( (p_i[5] & 0x3F) == 8 )
        sub_422D60(a2, a3, Src, *p_i, p_i[1]);
      else
        sub_423600(p_i, Src);
    }
  }
  else
  {
    v5 = __op_new(0x7BA230u);
    if ( v5 )
      v6 = (void **)sub_417980((int)v5, p_i[1], *p_i, p_i[1], p_i[5] & 0x3F);
    else
      v6 = nullptr;
    sub_417E80(v6, Src);
    if ( v6 )
      sub_415270(v6, 1);
  }
}

#ifndef BMF_STANDALONE
// __usercall thunk for sub_417DB0 @ 0x00417DB0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_417DB0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $60, %esp\n"
    "mov %esi, 12(%esp)\n"
    "movups %xmm1, 28(%esp)\n"
    "movups %xmm3, 44(%esp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "lea 52(%esp), %eax\n"
    "push %eax\n"
    "lea 40(%esp), %eax\n"
    "push %eax\n"
    "push 28(%esp)\n"
    "call __sub_417DB0\n"
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
#undef sub_415270
#undef sub_417980
#undef sub_417E80
#undef sub_422D60
#undef sub_423600
#undef sub_4273F0
#undef sub_427740
