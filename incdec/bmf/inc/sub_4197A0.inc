// sub_4197A0 @ 0x004197A0 — __usercall
// Extracted from BMF.c:23790-23803 by extract.py per incdec.md.

static inline void ** __fwd_sub_4197A0_sub_419610(void *a0, char a1) { return __sub_419610((void **)a0, a1); }
#define sub_419610 __fwd_sub_4197A0_sub_419610
static inline void __fwd_sub_4197A0_sub_419800(void *a0, const __m128 &a1, const __m128 &a2, void *a3, int a4, int a5, void *a6) { __sub_419800((__m128 *)a0, a1, a2, (_BYTE *)a3, a4, a5, (_BYTE *)a6); }
#define sub_419800 __fwd_sub_4197A0_sub_419800
#define sub_4229E0 __sub_4229E0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___VirtualAlloc
#define __PE_DECL___VirtualAlloc
typedef __attribute__((stdcall)) void * (*pfn_VirtualAlloc)(void *, unsigned int, unsigned int, unsigned int);
static pfn_VirtualAlloc& VirtualAlloc = *(pfn_VirtualAlloc*)0x00438024;   // IAT slot
#endif
PROBE_DECL(__sub_4197A0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) void __sub_4197A0(const __m128 &a1__ref, const __m128 &a2__ref, _BYTE *a3, int i, int a5, _BYTE *a6)
{
  PROBE_HIT(__sub_4197A0);
  __m128 a1 = a1__ref;
  __m128 a2 = a2__ref;
  LPVOID v6; // eax
  __m128 *lpAddress; // edi

  v6 = VirtualAlloc(nullptr, 0x103E30u, MEM_COMMIT, PAGE_READWRITE);
  if ( v6 )
    lpAddress = (__m128 *)sub_4229E0((int)v6, i, 0);
  else
    lpAddress = nullptr;
  sub_419800(lpAddress, a1, a2, a3, i, a5, a6);
  if ( lpAddress )
    sub_419610((void **)lpAddress, 1);
}

// __usercall thunk for sub_4197A0 @ 0x004197A0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_4197A0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $40, %esp\n"
    "movups %xmm1, 8(%esp)\n"
    "movups %xmm3, 24(%esp)\n"
    "push 20(%ebp)\n"
    "push 16(%ebp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "lea 40(%esp), %eax\n"
    "push %eax\n"
    "lea 28(%esp), %eax\n"
    "push %eax\n"
    "call __sub_4197A0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef sub_419610
#undef sub_419800
#undef sub_4229E0
