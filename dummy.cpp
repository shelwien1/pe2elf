#include <sys/syscall.h>
#include <unistd.h>

__attribute__((constructor)) static void dummy_init() {
  static const char msg[] = "Hello, world!!!\n";
  syscall(SYS_write, 1, msg, sizeof(msg)-1);
}
