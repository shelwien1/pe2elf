// __svml_log2_w @ 0x00436DC0 — __usercall
// Extracted from BMF.cpp:41770-41773 by extract.py per incdec.md.

PROBE_DECL(____svml_log2_w)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) __gnu_m128d ____svml_log2_w(const __m128i &a1__ref)
{
  PROBE_HIT(____svml_log2_w);
  __m128i a1 = a1__ref;
  return __svml_log2(a1);
}

#ifndef BMF_STANDALONE
// __usercall thunk for __svml_log2_w @ 0x00436DC0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk___svml_log2_w()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $28, %esp\n"
    "movups %xmm0, 12(%esp)\n"
    "lea 12(%esp), %eax\n"
    "push %eax\n"
    "call ____svml_log2_w\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}
#endif

