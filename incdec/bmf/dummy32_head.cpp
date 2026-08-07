// dummy32.cpp head — incdec infrastructure for BMF.exe (incdec.md §7).
//
// The full dummy32.cpp is assembled by build.sh: this head, then one
// #include per accepted .inc, then the generated dummy_init() tail.

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cmath>
#include <cctype>
#include <csignal>
#include <ucontext.h>
#include <dlfcn.h>   // isspace/isdigit/toupper — §6.5 lets these fall through to glibc
#include <sys/mman.h>
#include <unistd.h>
#include <immintrin.h>

// ---------------------------------------------------------------------------
// Hex-Rays type vocabulary.
//
// This is Hex-Rays' own defs.h, verbatim — the same header BMF.cpp's `#include
// <defs.h>` refers to — rather than a hand-rolled subset.  It brings LOBYTE /
// BYTEn / WORDn / SBYTEn / __ROLn__ / __RORn__ / __PAIRn__ / abs32 / qmemcpy /
// COERCE_* / _UNKNOWN and the __intN aliases, all with the exact semantics the
// decompiler assumed when it emitted them.
//
// BMF.cpp's other include, <windows.h>, is not wanted here (it would drag in a
// Win32 SDK that does not exist on this host), but defs.h keys several
// typedefs off it: `#ifndef _WINDOWS_` it defines BYTE/WORD/DWORD/LONG/BOOL
// itself, and as *signed* types (`typedef int8 BYTE`, int8 being plain char).
// BMF was compiled against the real windows.h, where they are unsigned.  So
// declare _WINDOWS_ and supply the windows.h spellings ourselves; letting
// defs.h win would silently sign-extend every BYTE the bodies touch.
// ---------------------------------------------------------------------------
#define _WINDOWS_
typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef long           LONG;
typedef int            BOOL;

#include "defs.h"

typedef void*         HANDLE;
typedef unsigned int  UINT;

// Win32 manifest constants the bodies spell out; windows.h is not available
// here (see above) and these are the only ones referenced.
#define MEM_COMMIT      0x00001000
#define MEM_RESERVE     0x00002000
#define MEM_DECOMMIT    0x00004000
#define MEM_RELEASE     0x00008000
#define MEM_TOP_DOWN    0x00100000
#define PAGE_NOACCESS         0x01
#define PAGE_READONLY         0x02
#define PAGE_READWRITE        0x04
#define PAGE_EXECUTE_READWRITE 0x40
#define INVALID_HANDLE_VALUE ((HANDLE)(long)-1)
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#define GENERIC_READ          0x80000000
#define GENERIC_WRITE         0x40000000
#define FILE_SHARE_READ              0x01
#define FILE_READ_ATTRIBUTES         0x80
#define FILE_ATTRIBUTE_NORMAL        0x80
#define FILE_ATTRIBUTE_DIRECTORY     0x10
#define FILE_WRITE_EA                0x10   // IDA's name for the same bit
#define CREATE_ALWAYS                   2
#define OPEN_EXISTING                   3
#define MAX_PATH                      260

// The handful of Win32 types the file-handling bodies name, with the layouts
// windows.h gives them — the structs are read and written by real Win32 calls
// through the shim, so the field offsets have to match.
typedef char           CHAR;
typedef char *         LPSTR;
typedef const char *   LPCSTR;
typedef void *         LPVOID;
typedef struct _FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} FILETIME;
typedef struct _WIN32_FIND_DATAA {
  DWORD    dwFileAttributes;      // +0x00
  FILETIME ftCreationTime;        // +0x04
  FILETIME ftLastAccessTime;      // +0x0C
  FILETIME ftLastWriteTime;       // +0x14
  DWORD    nFileSizeHigh;         // +0x1C
  DWORD    nFileSizeLow;          // +0x20
  DWORD    dwReserved0;           // +0x24
  DWORD    dwReserved1;           // +0x28
  CHAR     cFileName[MAX_PATH];   // +0x2C
  CHAR     cAlternateFileName[14];// +0x130
} WIN32_FIND_DATAA;
static_assert(sizeof(WIN32_FIND_DATAA) == 320, "Win32 WIN32_FIND_DATAA is 320 bytes");

// incdec.md §8.3 — MSVC's _iobuf, which is what BMF's statically-linked CRT
// hands out.  32 bytes on Win32 (the Win64 form is 48), and nothing like
// glibc's FILE.  Bodies that touch stdio are compiled with `#define FILE
// FILE1` so their FILE* is this, and every stdio call is routed to the PE's
// own implementation (§6.5) — a glibc FILE* reaching BMF's fread would be
// read with this layout.
struct FILE1 {
  char* _ptr;      // +0x00
  int   _cnt;      // +0x04
  char* _base;     // +0x08
  int   _flag;     // +0x0C
  int   _file;     // +0x10
  int   _charbuf;  // +0x14
  int   _bufsiz;   // +0x18
  char* _tmpfname; // +0x1C
};
static_assert(sizeof(FILE1) == 32, "Win32 _iobuf is 32 bytes");

// Hex-Rays invented a struct type named `Stream` for the thing fopen returns
// (`Stream *Stream; ... Stream = fopen(...)`), so bodies use it as a type
// name.  It is FILE.  extract.py renames any *variable* called Stream out of
// the way, since a body that declares one would otherwise shadow this.
typedef FILE1 Stream;

// defs.h stops at SLODWORD/SHIDWORD; the bodies also index DWORD lanes
// directly.  Same DWORDn/SDWORDn machinery, just the names it left out.
#define DWORD1(x)  DWORDn(x, 1)
#define DWORD2(x)  DWORDn(x, 2)
#define DWORD3(x)  DWORDn(x, 3)
#define SDWORD1(x) SDWORDn(x, 1)
#define SDWORD2(x) SDWORDn(x, 2)
#define SDWORD3(x) SDWORDn(x, 3)

// Calling-convention keywords survive inside *casts* — Hex-Rays writes
// `(void (__cdecl *)(int, int))f` — where extract.py's signature rewriting
// does not reach.  cdecl is gcc's i386 default, so it maps to nothing.
#define __cdecl
#define __stdcall  __attribute__((stdcall))
#define __fastcall __attribute__((fastcall))
#define __thiscall __attribute__((thiscall))

// incdec.md §8.2
#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---------------------------------------------------------------------------
// SSE register types.
//
// Hex-Rays writes MSVC's spelling for the halves of an SSE register —
// `v.m128i_i32[1]`, `q.m128_f32[0]`, `w.m64_u64` — because on Windows __m128i,
// __m128, __m128d and __m64 are *unions* with those members.  That union is
// MSVC's; GCC's __m128i is a bare vector type (`long long
// __attribute__((vector_size(16)))`) with no members at all, and nothing in
// immintrin.h / x86intrin.h adds them.  <intrin.h> does not help either — on
// GCC that header is just an x86intrin.h alias, so the Intel-compiler spelling
// it provides on Windows is not what arrives here.
//
// So wrap them.  Each M* below is the MSVC union plus conversions in both
// directions, and the __m128* / __m64 names are redirected onto the wrappers
// *after* the intrinsic headers are done with the originals.  The conversions
// carry a wrapper through the intrinsics unchanged: `_mm_mul_ps(a, b)` takes
// its arguments via `operator __gnu_m128&`, and its `__m128` result lands back
// in an M128F through the converting constructor.  Reinterpreting casts between
// the four (`(__m128)xmmword_441120`, which Hex-Rays emits freely) go through
// the cross-type constructors, which copy the bits.
//
// The unions are layout-compatible with the vector types — same size, same
// alignment, vector first — so a pointer cast to one of them still addresses a
// real SSE register image, which is what makes `*(__m128i *)ptr` work.
// ---------------------------------------------------------------------------
typedef __m128i __gnu_m128i;
typedef __m128  __gnu_m128;
typedef __m128d __gnu_m128d;
typedef __m64   __gnu_m64;

union M128I;
union M128F;
union M128D;

union M128I {
  __gnu_m128i v;
  // m128i_i8 is `char`, not `signed char`: MSVC's __int8 is plain char (so is
  // Hex-Rays' — see defs.h), and the bodies hand `x.m128i_i8` straight to
  // strcpy/strrchr, which take char*.
  char               m128i_i8[16];
  short              m128i_i16[8];
  int                m128i_i32[4];
  long long          m128i_i64[2];
  unsigned char      m128i_u8[16];
  unsigned short     m128i_u16[8];
  unsigned int       m128i_u32[4];
  unsigned long long m128i_u64[2];
  M128I() = default;
  M128I(__gnu_m128i a) : v(a) {}
  // Hex-Rays writes "zero the register" as `x = 0` / `(__m128i)0LL` even for a
  // 16-byte object; a non-zero scalar zero-extends, which is what the
  // corresponding MOVD/MOVQ does.
  M128I(long long z) { __builtin_memset(this, 0, 16); m128i_i64[0] = z; }
  inline M128I(const M128F &o);
  inline M128I(const M128D &o);
  operator __gnu_m128i&() { return v; }
  operator const __gnu_m128i&() const { return v; }
};

union M128F {
  __gnu_m128         v;
  float              m128_f32[4];
  char               m128_i8[16];
  short              m128_i16[8];
  int                m128_i32[4];
  long long          m128_i64[2];
  unsigned char      m128_u8[16];
  unsigned short     m128_u16[8];
  unsigned int       m128_u32[4];
  unsigned long long m128_u64[2];
  M128F() = default;
  M128F(__gnu_m128 a) : v(a) {}
  M128F(long long z) { __builtin_memset(this, 0, 16); m128_i64[0] = z; }
  inline M128F(const M128I &o);
  inline M128F(const M128D &o);
  operator __gnu_m128&() { return v; }
  operator const __gnu_m128&() const { return v; }
};

union M128D {
  __gnu_m128d        v;
  double             m128d_f64[2];
  float              m128d_f32[4];
  long long          m128d_i64[2];
  unsigned long long m128d_u64[2];
  M128D() = default;
  M128D(__gnu_m128d a) : v(a) {}
  M128D(long long z) { __builtin_memset(this, 0, 16); m128d_i64[0] = z; }
  inline M128D(const M128I &o);
  inline M128D(const M128F &o);
  operator __gnu_m128d&() { return v; }
  operator const __gnu_m128d&() const { return v; }
};

inline M128I::M128I(const M128F &o) { __builtin_memcpy(this, &o, 16); }
inline M128I::M128I(const M128D &o) { __builtin_memcpy(this, &o, 16); }
inline M128F::M128F(const M128I &o) { __builtin_memcpy(this, &o, 16); }
inline M128F::M128F(const M128D &o) { __builtin_memcpy(this, &o, 16); }
inline M128D::M128D(const M128I &o) { __builtin_memcpy(this, &o, 16); }
inline M128D::M128D(const M128F &o) { __builtin_memcpy(this, &o, 16); }

union M64 {
  __gnu_m64          v;
  char               m64_i8[8];
  short              m64_i16[4];
  int                m64_i32[2];
  long long          m64_i64;
  unsigned char      m64_u8[8];
  unsigned short     m64_u16[4];
  unsigned int       m64_u32[2];
  unsigned long long m64_u64;
  M64() = default;
  M64(__gnu_m64 a) : v(a) {}
  M64(long long z) : m64_i64(z) {}
  operator __gnu_m64&() { return v; }
  operator const __gnu_m64&() const { return v; }
};

static_assert(sizeof(M128I) == 16 && alignof(M128I) == alignof(__gnu_m128i), "M128I layout");
static_assert(sizeof(M128F) == 16 && alignof(M128F) == alignof(__gnu_m128),  "M128F layout");
static_assert(sizeof(M128D) == 16 && alignof(M128D) == alignof(__gnu_m128d), "M128D layout");
static_assert(sizeof(M64)   ==  8, "M64 layout");

// The memory-operand intrinsics take a pointer to the *vector* type, and the
// bodies cast to the wrapper (`(__m128i *)p` expands to `(M128I *)p`).  These
// overloads accept that.  They are the only place the head itself touches SSE,
// hence the explicit target attribute: build.sh deliberately does not turn SSE
// on for the whole translation unit — extract.py puts the same attribute on
// each body that needs it, so nothing else in the file has its code generation
// changed by intrinsics appearing in one function.
#define BMF_SSE __attribute__((target("mmx,sse4.2,fxsr")))
BMF_SSE static inline __gnu_m128i _mm_load_si128 (const M128I *p) { __gnu_m128i r; __builtin_memcpy(&r, p, 16); return r; }
BMF_SSE static inline __gnu_m128i _mm_loadu_si128(const M128I *p) { __gnu_m128i r; __builtin_memcpy(&r, p, 16); return r; }
BMF_SSE static inline __gnu_m128i _mm_loadl_epi64(const M128I *p) { __gnu_m128i r = __extension__ (__gnu_m128i){0, 0}; __builtin_memcpy(&r, p, 8); return r; }
BMF_SSE static inline void _mm_store_si128 (M128I *p, __gnu_m128i a) { __builtin_memcpy(p, &a, 16); }
BMF_SSE static inline void _mm_storeu_si128(M128I *p, __gnu_m128i a) { __builtin_memcpy(p, &a, 16); }
BMF_SSE static inline void _mm_stream_si128(M128I *p, __gnu_m128i a) { _mm_stream_si128((__gnu_m128i *)p, a); }
BMF_SSE static inline void _mm_stream_pi   (M64   *p, __gnu_m64   a) { _mm_stream_pi((__gnu_m64 *)p, a); }

#define __m128i M128I
#define __m128  M128F
#define __m128d M128D
#define __m64   M64

// i386 g++ has no __int128 (verified: "expected primary-expression").  The
// only things typed that way here are 16-byte xmmword globals, so give them
// the same 16-byte SSE type.
typedef M128I _OWORD;
#define __int128 M128I

// ---------------------------------------------------------------------------
// CPUID, for the routines that override/ rewrites from their expected
// results (Hex-Rays renders them as `__asm { cpuid }` plus reads of its
// _EAX/_ECX/_EDX pseudo-registers, which have no C form).
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// §7.1 probe registry
// ---------------------------------------------------------------------------
struct Probe {
  Probe* next;
  const char* name;
  unsigned long long count;
  Probe(const char* n);
};
static Probe* g_probes = nullptr;
Probe::Probe(const char* n) : next(g_probes), name(n), count(0) { g_probes = this; }

#define PROBE_DECL(sym) static Probe sym##_probe(#sym);

// ---------------------------------------------------------------------------
// Fault locator (build with -DBMF_TRAP_SEGV).
//
// A moved function that corrupts something usually does not fault where the
// mistake is — it faults later, often inside PE code that was never touched,
// and the shim's SEH turns that into a bare exit(1) with no output.  This
// prints the faulting address and the EIP with the module it belongs to, which
// is enough to point at the instruction in BMF.asm.
//
// It installs on the first probe hit rather than from a constructor, because
// the shim installs its own SIGSEGV handler when it loads and would otherwise
// win.
// ---------------------------------------------------------------------------
#ifdef BMF_TRAP_SEGV
#include <csignal>
#include <ucontext.h>
#include <dlfcn.h>
static void bmf_segv(int sig, siginfo_t *si, void *uc) {
  (void)sig;
  unsigned eip = (unsigned)((ucontext_t *)uc)->uc_mcontext.gregs[REG_EIP];
  Dl_info di; const char *who = "?"; unsigned off = 0;
  if (dladdr((void *)eip, &di) && di.dli_fbase) {
    who = di.dli_fname; off = eip - (unsigned)di.dli_fbase;
  }
  unsigned esp = (unsigned)((ucontext_t *)uc)->uc_mcontext.gregs[REG_ESP];
  fprintf(stderr, "[fault] sig=%d addr=%p eip=%08x esp=%08x  %s+0x%x\n",
          si->si_signo, si->si_addr, eip, esp, who, off);
  fflush(stderr);
  _exit(9);
}
static char bmf_sigstack[65536];
static void bmf_trap_arm() {
  static int armed = 0;
  if (armed) return;
  armed = 1;
  // On an alternate stack, so a fault that leaves %esp unusable — a stack
  // overflow, or a moved function returning with the stack unbalanced — still
  // gets reported instead of killing the process a second time inside the
  // handler, silently and with stdout unflushed.
  stack_t ss;
  memset(&ss, 0, sizeof ss);
  ss.ss_sp = bmf_sigstack;
  ss.ss_size = sizeof bmf_sigstack;
  sigaltstack(&ss, nullptr);
  struct sigaction sa;
  memset(&sa, 0, sizeof sa);
  sa.sa_sigaction = bmf_segv;
  sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
  sigaction(SIGSEGV, &sa, nullptr);
  sigaction(SIGBUS, &sa, nullptr);
  sigaction(SIGFPE, &sa, nullptr);   // integer divide by zero lands here too
  sigaction(SIGILL, &sa, nullptr);   // a wild jump usually lands on garbage
}
#define PROBE_TRAP() bmf_trap_arm()
#else
#define PROBE_TRAP() ((void)0)
#endif

#define PROBE_HIT(sym)  (PROBE_TRAP(), __sync_fetch_and_add(&sym##_probe.count, 1ULL))

// ---------------------------------------------------------------------------
// §5 patch helpers
// ---------------------------------------------------------------------------
static void make_writable(void* addr, size_t len) {
  uintptr_t pg = (uintptr_t)sysconf(_SC_PAGESIZE);
  uintptr_t lo = (uintptr_t)addr & ~(pg - 1);
  uintptr_t hi = ((uintptr_t)addr + len + pg - 1) & ~(pg - 1);
  if (mprotect((void*)lo, hi - lo, PROT_READ | PROT_WRITE | PROT_EXEC) != 0) {
    perror("[incdec] mprotect");
    abort();
  }
}

// On i386 the address space is 32 bits and the CPU computes EIP+rel32 mod
// 2^32, so any target is reachable from any origin — no range check (§5).
static void patch_jmp(void* orig, void* repl) {
  uint32_t disp = (uint32_t)((uintptr_t)repl - ((uintptr_t)orig + 5));
  make_writable(orig, 5);
  uint8_t* p = (uint8_t*)orig;
  p[0] = 0xE9;
  memcpy(p + 1, &disp, 4);
  __builtin___clear_cache((char*)orig, (char*)orig + 5);
}

static void patch_iat_slot(void* slot, void* repl) {
  make_writable(slot, 4);
  *(void**)slot = repl;   // 4-byte slot on PE32 (§6.4)
}

// ---------------------------------------------------------------------------
// §7.2 ExitProcess IAT hook — the shim's ExitProcess ends in _exit(), which
// bypasses both DT_FINI and atexit, so the counters have to be dumped here.
// ---------------------------------------------------------------------------
#define IAT_ExitProcess 0x00438030

static __attribute__((stdcall)) void my_ExitProcess(unsigned int code) {
  const char* path = getenv("BMF_PROBE_OUT");
  FILE* out = stderr;
  if (path && *path) { FILE* f = fopen(path, "a"); if (f) out = f; }
  fprintf(out, "[probe] ExitProcess(%u), call counts:\n", code);
  for (Probe* p = g_probes; p; p = p->next)
    fprintf(out, "[probe]   %-24s %llu\n", p->name, p->count);
  fflush(out);
  if (out != stderr) fclose(out);
  _exit((int)code);
}
