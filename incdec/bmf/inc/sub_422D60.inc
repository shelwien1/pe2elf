// sub_422D60 @ 0x00422D60 — __usercall
// Extracted from BMF.cpp:28942-28955 by extract.py per incdec.md.

static inline void ** __fwd_sub_422D60_sub_419610(void *a0, char a1) { return __sub_419610((void **)a0, a1); }
#define sub_419610 __fwd_sub_422D60_sub_419610
#define sub_4229E0 __sub_4229E0
static inline void __fwd_sub_422D60_sub_422DB0(int a0, char a1, const __m128 &a2, const __m128 &a3, void *a4, int a5, int a6) { __sub_422DB0(a0, a1, a2, a3, (_BYTE *)a4, a5, a6); }
#define sub_422DB0 __fwd_sub_422D60_sub_422DB0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___VirtualAlloc
#define __PE_DECL___VirtualAlloc
typedef __attribute__((stdcall)) void * (*pfn_VirtualAlloc)(void *, unsigned int, unsigned int, unsigned int);
static pfn_VirtualAlloc& VirtualAlloc = *(pfn_VirtualAlloc*)0x00438024;   // IAT slot
#endif
PROBE_DECL(__sub_422D60)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) void __sub_422D60(const __m128 &a1__ref, const __m128 &a2__ref, _BYTE *Src, int i, int a5)
{
  PROBE_HIT(__sub_422D60);
  __m128 a1 = a1__ref;
  __m128 a2 = a2__ref;
  LPVOID v5; // eax
  void **lpAddress; // edi

  v5 = VirtualAlloc(nullptr, 0x103E30u, MEM_COMMIT, PAGE_READWRITE);
  if ( v5 )
    lpAddress = (void **)sub_4229E0((int)v5, i, 0);
  else
    lpAddress = nullptr;
  sub_422DB0((int)lpAddress, i, a1, a2, Src, i, a5);
  if ( lpAddress )
    sub_419610(lpAddress, 1);
}

// __usercall thunk for sub_422D60 @ 0x00422D60: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_422D60()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $44, %esp\n"
    "movups %xmm1, 12(%esp)\n"
    "movups %xmm3, 28(%esp)\n"
    "push 16(%ebp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "lea 40(%esp), %eax\n"
    "push %eax\n"
    "lea 28(%esp), %eax\n"
    "push %eax\n"
    "call __sub_422D60\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef sub_419610
#undef sub_4229E0
#undef sub_422DB0
