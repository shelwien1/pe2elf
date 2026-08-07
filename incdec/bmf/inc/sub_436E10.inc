// sub_436E10 @ 0x00436E10 — __usercall
// HAND-WRITTEN override.  Not extract.py output; see override/README.md.
//
// Eight instructions, and Hex-Rays got three things wrong about them, so
// there is not much of the decompilation left to keep:
//
//   00436E13  movapd   xmm5, ds:xmmword_43B480     ; {0.5, 0.5}
//   00436E1B  movmskpd eax, xmm1
//   00436E1F  andpd    xmm0, xmm1
//   00436E23  andnpd   xmm1, xmm5
//   00436E27  test     eax, eax
//   00436E29  orpd     xmm0, xmm1                  ; select(mask ? x : 0.5)
//   00436E2D  jz       short loc_436E34
//   00436E2F  call     ___svml_log2_w              ; xmm0 in, xmm0 out
//
// It is the lane-masked wrapper around SVML's log2: lanes the caller marked
// dead are replaced with 0.5 (whose log2 is exact and cannot fault or produce
// a NaN), and the call is skipped entirely when no lane is live.
//
//   1. The `xmm0` argument is missing from the signature — Hex-Rays recovered
//      only `a1@<xmm1>` — so the whole select vanished from the body.
//   2. The result is in `xmm0`, not `eax`.  IDA typed the return `@<eax>`
//      because `movmskpd eax, xmm1` is the last thing to write eax on the
//      `jz` path; on the other path `___svml_log2` clobbers it.  The caller
//      at 0x0041177F settles it: `mulpd xmm1, xmm0` right after the call, and
//      eax is never read.
//   3. `__svml_log2_w()` is printed with no argument, for the same reason as
//      every other call into the SSE-register half of the Intel runtime
//      (incdec.md §8.2.5).
//
// fixups.txt carries the corrected signature so that extract.py builds the
// entry-point thunk from it; this file is the body.

#ifndef __PE_DECL___bmf_half_half
#define __PE_DECL___bmf_half_half
static __m128d &__bmf_half_half = *(__m128d *)0x0043B480;   // {0.5, 0.5}
#endif

PROBE_DECL(__sub_436E10)
extern "C" BMF_SSE __attribute__((visibility("hidden")))
__gnu_m128d __sub_436E10(const __m128d &a0__ref, const __m128d &a1__ref)
{
  PROBE_HIT(__sub_436E10);
  __m128d a0 = a0__ref;
  __m128d a1 = a1__ref;
  __m128d x = _mm_or_pd(_mm_and_pd(a0, a1), _mm_andnot_pd(a1, __bmf_half_half));
  if ( _mm_movemask_pd(a1) )
    return ____svml_log2_w((__m128i)x);   // the moved body, §6.3
  return x;
}

#undef __bmf_half_half

// __usercall thunk for sub_436E10 @ 0x00436E10: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_436E10()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $40, %esp\n"
    "movups %xmm0, 8(%esp)\n"
    "movups %xmm1, 24(%esp)\n"
    "lea 24(%esp), %eax\n"
    "push %eax\n"
    "lea 12(%esp), %eax\n"
    "push %eax\n"
    "call __sub_436E10\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

