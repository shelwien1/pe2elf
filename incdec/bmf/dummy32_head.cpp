// dummy32.cpp head — incdec infrastructure for BMF.exe (incdec.md §7).
//
// The full dummy32.cpp is assembled by build.sh: this head, then one
// #include per accepted .inc, then the generated dummy_init() tail.

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cmath>
#include <sys/mman.h>
#include <unistd.h>
#include <x86intrin.h>

// ---------------------------------------------------------------------------
// Hex-Rays type vocabulary (the subset the BMF bodies actually use).
// BMF.c includes <defs.h> and <windows.h>, neither of which we want here —
// the decompiled bodies only need the integer aliases and a few helpers.
// ---------------------------------------------------------------------------
typedef uint8_t  _BYTE;
typedef uint16_t _WORD;
typedef uint32_t _DWORD;
typedef uint64_t _QWORD;
// Macros, not typedefs: Hex-Rays writes "unsigned __int8", and
// `unsigned signed char` is not a type.  MSVC's __intN are macros in spirit.
#define __int8  char
#define __int16 short
#define __int32 int
#define __int64 long long
// i386 g++ has no __int128 (verified: "expected primary-expression").  The
// only things typed that way here are 16-byte xmmword globals, so give them
// a 16-byte SSE-compatible type.
typedef __m128i  _OWORD;
#define __int128 __m128i
typedef unsigned char _UNKNOWN;
typedef uint8_t  BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int      BOOL;
typedef bool     _BOOL1;
typedef uint16_t _BOOL2;
typedef uint32_t _BOOL4;
typedef void*    HANDLE;
typedef unsigned int  UINT;
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

#define LOBYTE(x)   (*((uint8_t*)&(x)))
#define LOWORD(x)   (*((uint16_t*)&(x)))
#define HIWORD(x)   (*((uint16_t*)&(x) + 1))
#define BYTE1(x)    (*((uint8_t*)&(x) + 1))
#define BYTE2(x)    (*((uint8_t*)&(x) + 2))
#define BYTE3(x)    (*((uint8_t*)&(x) + 3))
#define WORD1(x)    (*((uint16_t*)&(x) + 1))
#define SLOBYTE(x)  (*((int8_t*)&(x)))
#define SLOWORD(x)  (*((int16_t*)&(x)))
#define HIBYTE(x)   (*((uint8_t*)&(x) + sizeof(x) - 1))
#define qmemcpy     memcpy

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

// incdec.md §8.2
#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

static inline int __ROL4__(unsigned int v, int n) { return (v << n) | (v >> (32 - n)); }
static inline int __ROR4__(unsigned int v, int n) { return (v >> n) | (v << (32 - n)); }

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
#define PROBE_HIT(sym)  __sync_fetch_and_add(&sym##_probe.count, 1ULL)

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
