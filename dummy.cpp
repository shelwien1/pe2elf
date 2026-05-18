
#include <stdio.h>
#include <stdlib.h>

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

__attribute__((constructor)) static void dummy_init() {
  printf("Hello, world!!! dummy_init @ %p\n", (void*)&dummy_init);
  fflush(stdout);
}
