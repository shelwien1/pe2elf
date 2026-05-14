#include <cstdio>

__attribute__((constructor)) static void dummy_init() {
  printf("Hello, world!!!\n");
  fflush(stdout);
}
