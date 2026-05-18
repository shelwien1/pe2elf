
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

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

#include "sub_140014894.inc"

extern unsigned long long __sub_140014894_calls;

static __attribute__((ms_abi)) void my_ExitProcess(unsigned int code) {
  fprintf(stderr, "[probe] ExitProcess(%u): __sub_140014894 called %llu times\n",
          code, __sub_140014894_calls);
  fflush(stderr);
  _exit((int)code);
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

  patch_iat_slot((void*)0x140022068, (void*)&my_ExitProcess);
}
