
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <x86intrin.h>

#define _WINDOWS_
#include "defs.h"
#undef _WINDOWS_

#ifndef _MSC_VER
#define __declspec(x) __attribute__((x))
#define align(n) aligned(n)
#endif

#define FILE FILE1
#include "PPMonstr.h"
#undef FILE

#ifndef _MSC_VER
#undef align
#undef __declspec
#endif

// ---------------------------------------------------------------------------
// Probe registry. Each decompiled function declares a Probe via PROBE_DECL
// and bumps its counter on entry via PROBE_HIT. The ExitProcess hook walks
// the linked list and prints all counters before the process dies.

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
// Patching helpers.

static void patch_jmp(void *orig, void *repl) {
  long long disp = (long long)(uintptr_t)repl - (long long)((uintptr_t)orig + 5);
  if (disp < -0x80000000LL || disp > 0x7FFFFFFFLL) {
    fprintf(stderr, "patch_jmp: rel32 overflow %p -> %p (disp=%lld)\n",
            orig, repl, disp);
    abort();
  }
  long ps = sysconf(_SC_PAGESIZE);
  uintptr_t a = (uintptr_t)orig;
  uintptr_t page = a & ~(uintptr_t)(ps - 1);
  size_t len = (a + 5) - page;
  if (mprotect((void*)page, len, PROT_READ|PROT_WRITE|PROT_EXEC) != 0) {
    perror("patch_jmp: mprotect rw");
    abort();
  }
  unsigned char *p = (unsigned char*)orig;
  p[0] = 0xE9;
  int d32 = (int)disp;
  memcpy(p + 1, &d32, 4);
  mprotect((void*)page, len, PROT_READ|PROT_EXEC);
  __builtin___clear_cache((char*)orig, (char*)orig + 5);
}

static void patch_iat_slot(void *slot, void *repl) {
  long ps = sysconf(_SC_PAGESIZE);
  uintptr_t a = (uintptr_t)slot;
  uintptr_t page = a & ~(uintptr_t)(ps - 1);
  size_t len = (a + sizeof(void*)) - page;
  if (mprotect((void*)page, len, PROT_READ|PROT_WRITE) != 0) {
    perror("patch_iat_slot: mprotect rw");
    abort();
  }
  *(void**)slot = repl;
  mprotect((void*)page, len, PROT_READ);
}

// ---------------------------------------------------------------------------
// Decompiled function bodies.

#include "sub_140014894.inc"
#include "sub_14001A5C0.inc"
#include "sub_140003370.inc"
#include "sub_1400032F0.inc"
#include "sub_140012804.inc"
#include "main.inc"

// ---------------------------------------------------------------------------
// ExitProcess IAT hook. The shim's kernel32_ExitProcess ends in _exit(),
// which bypasses both DT_FINI and atexit, so we hook the IAT slot directly.
// The wrapper must be ms_abi: PPMonstr calls through the IAT using Win64.

static __attribute__((ms_abi)) void my_ExitProcess(unsigned int code) {
  fprintf(stderr, "[probe] ExitProcess(%u), call counts:\n", code);
  for (Probe* p = g_probes; p; p = p->next)
    fprintf(stderr, "[probe]   %-32s %llu\n", p->name, p->count);
  fflush(stderr);
  _exit((int)code);
}

__attribute__((constructor)) static void dummy_init() {
  printf("Hello, world!!! dummy_init @ %p\n", (void*)&dummy_init);
  fflush(stdout);

  uintptr_t self = (uintptr_t)&dummy_init;
  if (self < 0xF0000000ULL || self >= 0x100000000ULL) {
    fprintf(stderr, "dummy.so loaded outside preferred 0xF0000000 window "
                    "(dummy_init=%p) -- rel32 patching unsafe, aborting.\n",
            (void*)&dummy_init);
    abort();
  }

  patch_jmp((void*)0x140014894, (void*)&__sub_140014894);
  patch_jmp((void*)0x14001A5C0, (void*)&__sub_14001A5C0);
  patch_jmp((void*)0x140003370, (void*)&__sub_140003370);
  patch_jmp((void*)0x1400032F0, (void*)&__sub_1400032F0);
  patch_jmp((void*)0x140012804, (void*)&__sub_140012804);
  patch_jmp((void*)0x140001000, (void*)&__main);

  patch_iat_slot((void*)0x140022068, (void*)&my_ExitProcess);
}
