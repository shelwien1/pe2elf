// sub_434A30 @ 0x00434A30 — __cdecl
// HAND-WRITTEN override.  Not extract.py output; see override/README.md.
//
// This is the Intel C++ runtime's CPU dispatch initialiser: it classifies the
// host CPU and stores a single level code into the global at 0x00445B5C
// (Hex-Rays calls it `n1024`, after the largest constant it assigns), which
// the rest of the image then tests to pick between scalar / MMX / SSE / SSE2 /
// … implementations of the same routine.
//
// The decompilation cannot be used verbatim.  It is built from `__asm { cpuid
// }` / `__asm { xgetbv }` statements with the results read back out of
// Hex-Rays' `_EAX` / `_ECX` / `_EDX` pseudo-registers — which are not
// variables g++ has any notion of — and it mis-attributes the XGETBV result to
// a variable it had already used for the CPUID EDX (`_EDX_2`, declared `// al`).
// So this rewrites the routine from its expected results instead: same inputs,
// same level code, ordinary C++.
//
// The classification, decoded from the original:
//
//   no CPUID, or CPUID leaf 0 reports max leaf 0     ->        1
//   family 5   (Pentium)          base 2, MMX -> 8
//   family 15  (Pentium 4)        SSE2 -> 512 else 1;  SSE3 -> 2048
//   family 6   (P6 and later)     base 4, MMX -> 16
//     + FXSR                      base 32,      SSE  -> 128
//         SSE2                    ->     1024
//         SSE3                    ->     2048
//         SSSE3                   ->     4096
//         SSE4.1                  ->   0x2000
//         MOVBE                   ->   0x4000
//         SSE4.2 + POPCNT         ->   0x8000
//         PCLMULQDQ + AES         ->  0x10000
//     + OSXSAVE, AVX, XCR0[2:1]=11 ->  0x20000
//
// Order matters: the original assigns unconditionally down the list, so a
// later hit overwrites an earlier one even when it is numerically lower —
// MOVBE (0x4000) is tested before SSE4.1 (0x2000) and therefore loses to it.
// This keeps that exact sequence.

#ifndef __PE_DECL___n1024
#define __PE_DECL___n1024
typedef int t_n1024;
static t_n1024& __n1024 = *(t_n1024*)0x00445B5C;
#endif
#define n1024 __n1024

// EFLAGS.ID (bit 21) is writable iff the CPU implements CPUID.
static int bmf_has_cpuid()
{
  unsigned before, after;
  __asm__ volatile("pushfl\n\t"
                   "popl %0\n\t"
                   "movl %0, %1\n\t"
                   "xorl $0x200000, %1\n\t"
                   "pushl %1\n\t"
                   "popfl\n\t"
                   "pushfl\n\t"
                   "popl %1\n\t"
                   : "=&r"(before), "=&r"(after) : : "cc");
  if (before == after)
    return 0;
  __asm__ volatile("pushl %0\n\t popfl" : : "r"(before) : "cc");
  return 1;
}

static void bmf_cpuid(unsigned leaf, unsigned *a, unsigned *b, unsigned *c, unsigned *d)
{
  // -fPIC on i386 reserves EBX, so it has to be saved around CPUID by hand.
  __asm__ volatile("xchgl %%ebx, %1\n\t"
                   "cpuid\n\t"
                   "xchgl %%ebx, %1"
                   : "=a"(*a), "=&r"(*b), "=c"(*c), "=d"(*d)
                   : "0"(leaf), "2"(0));
}

// XGETBV encoded by hand: the mnemonic needs -mxsave, which the rest of this
// translation unit is not built with.
static unsigned bmf_xgetbv0()
{
  unsigned lo, hi;
  __asm__ volatile(".byte 0x0f, 0x01, 0xd0" : "=a"(lo), "=d"(hi) : "c"(0));
  (void)hi;
  return lo;
}

PROBE_DECL(__sub_434A30)
void __sub_434A30()
{
  PROBE_HIT(__sub_434A30);

  unsigned max_leaf = 0, feat_ecx = 0, feat_edx = 0, family = 0;

  if (bmf_has_cpuid()) {
    unsigned a, b, c, d;
    bmf_cpuid(0, &a, &b, &c, &d);
    max_leaf = a;
    bmf_cpuid(1, &a, &b, &c, &d);
    family   = (a >> 8) & 0xF;      // BYTE1(eax) & 0xF
    feat_ecx = c;
    feat_edx = d;
  }

  // CPUID.1 EDX
  const unsigned MMX  = 0x00800000, FXSR = 0x01000000;
  const unsigned SSE  = 0x02000000, SSE2 = 0x04000000;
  // CPUID.1 ECX
  const unsigned SSE3      = 0x00000001, PCLMULQDQ = 0x00000002;
  const unsigned SSSE3     = 0x00000200, SSE41     = 0x00080000;
  const unsigned SSE42     = 0x00100000, MOVBE     = 0x00400000;
  const unsigned POPCNT    = 0x00800000, AES       = 0x02000000;
  const unsigned OSXSAVE   = 0x08000000, AVX       = 0x10000000;

  int level;

  if (max_leaf == 0) {
    level = 1;
  } else if (family == 5) {
    level = (feat_edx & MMX) ? 8 : 2;
  } else if (family == 6) {
    level = (feat_edx & MMX) ? 16 : 4;
    if (feat_edx & FXSR) {
      level = (feat_edx & SSE) ? 128 : 32;
      if (feat_edx & SSE2)                                level = 1024;
      if (feat_ecx & SSE3)                                level = 2048;
      if (feat_ecx & SSSE3)                               level = 4096;
      if (feat_ecx & MOVBE)                               level = 0x4000;
      if (feat_ecx & SSE41)                               level = 0x2000;
      if ((feat_ecx & (SSE42 | POPCNT)) == (SSE42 | POPCNT)) level = 0x8000;
      if ((feat_ecx & (PCLMULQDQ | AES)) == (PCLMULQDQ | AES)) level = 0x10000;
    }
    if (feat_ecx & OSXSAVE) {
      unsigned xcr0 = bmf_xgetbv0();
      if ((feat_ecx & AVX) && (xcr0 & 6) == 6)            level = 0x20000;
    }
  } else if (family == 15) {
    level = (feat_edx & SSE2) ? 512 : 1;
    if (feat_ecx & SSE3)                                  level = 2048;
  } else {
    level = 1;
  }

  n1024 = level;
}

#undef n1024
