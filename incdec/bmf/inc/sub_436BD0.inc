// sub_436BD0 @ 0x00436BD0 — __usercall
// HAND-WRITTEN override.  Not extract.py output; see override/README.md.
//
// Intel's cache-descriptor detection: CPUID leaf 2 returns up to four 16-byte
// blocks of one-byte descriptors, each naming a cache; the routine collects
// them, looks each up in a 105-entry table at 0x00441DC0, and keeps the
// largest.  It writes three globals — the cache size in bytes (0x00446180),
// the line size (0x00446184) and an MMX/SSE2 level (0x004425F4) — and returns
// the level.
//
// Same reason as sub_434A30 for not using the decompilation: the body is
// `__asm { cpuid }` plus reads of Hex-Rays' `_EAX`/`_EBX`/`_ECX`/`_EDX`
// pseudo-registers, which are not variables g++ has any notion of.  The
// control flow below is otherwise a literal transcription, including the
// `> 2` in the third block-count test where every other one is `> 1`.
//
// The four result blocks are one 64-byte buffer: Hex-Rays split it into
// `_DWORD v44[4]` plus three groups of four ints, but their frame slots are
// contiguous (ebp-40h, ebp-30h, ebp-20h, ebp-10h) and the loops below walk all
// 64 bytes, which is what gives that away.
//
// Verified against the un-injected binary on this host: Size = 0,
// line size = 0, level = 2 — leaf 2 reports descriptor 0xFF here ("no cache
// info, use leaf 4"), so the walk stops on the first byte and only the SSE2
// level survives.
//
// __usercall: the `@<ebx>` argument is written to a local that is never read,
// so nothing depends on its value; extract.py appends the entry-point thunk.

#ifndef __PE_DECL___cachetbl
#define __PE_DECL___cachetbl
// One 5-dword record per entry, indexed with a stride of 5 (the original
// spells that as four separate arrays 4 bytes apart, indexed by the same
// counter): descriptor byte, unused, size in KB, line size, and a flag that
// doubles the line size.
static int *const __bmf_cache_desc = (int *)(blob1 + 0x00441DC0 - BMF_BLOB_BASE);
static int *const __bmf_cache_size = (int *)(blob1 + 0x00441DC8 - BMF_BLOB_BASE);
static int *const __bmf_cache_line = (int *)(blob1 + 0x00441DCC - BMF_BLOB_BASE);
static int *const __bmf_cache_flag = (int *)(blob1 + 0x00441DD0 - BMF_BLOB_BASE);
static int &__bmf_cache_bytes = *(int *)(blob1 + 0x00446180 - BMF_BLOB_BASE);   // "Size"
static int &__bmf_line_bytes  = *(int *)(blob1 + 0x00446184 - BMF_BLOB_BASE);   // dword_446184
static int &__bmf_sse_level   = *(int *)(blob1 + 0x004425F4 - BMF_BLOB_BASE);   // "n2_2"
#endif

PROBE_DECL(__sub_436BD0)
extern "C" __attribute__((visibility("hidden")))
unsigned int __sub_436BD0(int a1)
{
  PROBE_HIT(__sub_436BD0);
  (void)a1;                       // the original's `v43 = a1` is a dead store

  unsigned char buf[64];
  __builtin_memset(buf, 0, sizeof buf);

  unsigned a, b, c, d, feat_edx;
  bmf_cpuid(1, &a, &b, &c, &d);
  feat_edx = d;

  int is_intel = 0;
  bmf_cpuid(0, &a, &b, &c, &d);
  if (b == 0x756E6547 && d == 0x49656E69 && c == 0x6C65746E) {   // "GenuineIntel"
    is_intel = 1;
    if ((short)a >= 2) {
      unsigned r[4];
      bmf_cpuid(2, &r[0], &r[1], &r[2], &r[3]);
      __builtin_memcpy(buf + 0, r, 16);
      if ((char)r[0] > 1) {
        bmf_cpuid(2, &r[0], &r[1], &r[2], &r[3]);
        __builtin_memcpy(buf + 16, r, 16);
        if ((char)r[0] > 2) {                  // yes, 2 — the original's test
          bmf_cpuid(2, &r[0], &r[1], &r[2], &r[3]);
          __builtin_memcpy(buf + 32, r, 16);
          if ((char)r[0] > 1) {
            bmf_cpuid(2, &r[0], &r[1], &r[2], &r[3]);
            if ((char)r[0] > 1)
              __builtin_memcpy(buf + 48, r, 16);
          }
        }
      }
    }
  }

  unsigned level = 0;
  if (is_intel) {
    // The low byte of each block's EAX is the repeat count, not a descriptor.
    buf[0] = buf[16] = buf[32] = buf[48] = 0;
    // A register with bit 31 set carries no descriptors.
    for (int j = 3; j < 64; j += 4)
      if (buf[j] & 0x80)
        for (int k = j - 3; k <= j; ++k)
          buf[k] = 0;

    unsigned best = 0;
    int i = 0;
    for (; buf[i] != 255; ) {
      for (int t = 0; ; t += 5) {
        if (t >= 525)
          goto next;                       // descriptor not in the table
        if ((int)buf[i] != __bmf_cache_desc[t])
          continue;
        if (__bmf_cache_size[t] > (int)best) {
          best = __bmf_cache_size[t];
          int line = __bmf_cache_line[t];
          if (__bmf_cache_flag[t] == 1)
            line *= 2;
          __bmf_line_bytes = line;
        }
        break;
      }
    next:
      if (++i >= 64)
        goto done;
    }
    // Fell out on a 0xFF descriptor: nothing usable was found.
    __bmf_line_bytes = 0;
    best = 0;
  done:
    __bmf_cache_bytes = best << 10;
    level = (feat_edx & 0x4000000) ? 2                    // SSE2
                                   : ((feat_edx & 0x800000u) >> 23);  // MMX
  } else {
    __bmf_cache_bytes = 0;
  }

  __bmf_sse_level = level;
  return level;
}

#ifndef BMF_STANDALONE
// __usercall thunk for sub_436BD0 @ 0x00436BD0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_436BD0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $28, %esp\n"
    "mov %ebx, 12(%esp)\n"
    "push 12(%esp)\n"
    "call __sub_436BD0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}
#endif

