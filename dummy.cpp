
#include <stdio.h>
#include <stdlib.h>

#define _WINDOWS_
#include "defs.h"
#undef _WINDOWS_

#define FILE FILE1
#include "PPMonstr.h"
#undef FILE

__attribute__((constructor)) static void dummy_init() {
  printf("Hello, world!!!\n");
  fflush(stdout);
}
