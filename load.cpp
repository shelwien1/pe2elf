// load.cpp - dlopen a pe2elf --so .so and invoke its `_entrypoint` symbol
// with the MSVC WinMain prototype (ms_abi).
//
// Usage: ./load <pe.so> [args...]
//
// The remaining argv (after argv[1]) is joined with spaces (and quoted on
// whitespace) and passed as lpCmdLine. hInstance/hPrevInstance are NULL,
// nShowCmd is SW_SHOWNORMAL (1).

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

typedef int (*winmain_t)(void* hInstance,
                         void* hPrevInstance,
                         char* lpCmdLine,
                         int   nShowCmd) __attribute__((ms_abi));

int main(int argc, char** argv) {
  if( argc < 2 ) {
    fprintf(stderr, "Usage: %s <pe.so> [args...]\n", argv[0]);
    return 1;
  }
  const char* so_path = argv[1];

  // Join argv[2..argc] into a Windows-style command line.
  std::string cmdline;
  for( int i = 2; i < argc; ++i ) {
    if( i > 2 ) cmdline += ' ';
    const char* a = argv[i];
    bool quote = (a[0] == '\0') || strchr(a, ' ') || strchr(a, '\t');
    if( quote ) cmdline += '"';
    cmdline += a;
    if( quote ) cmdline += '"';
  }

  void* handle = dlopen(so_path, RTLD_NOW);
  if( !handle ) {
    fprintf(stderr, "dlopen(%s) failed: %s\n", so_path, dlerror());
    return 1;
  }

  winmain_t entry = (winmain_t)dlsym(handle, "_entrypoint");
  if( !entry ) {
    fprintf(stderr, "dlsym(_entrypoint) failed: %s\n", dlerror());
    dlclose(handle);
    return 1;
  }

  return entry(nullptr, nullptr, const_cast<char*>(cmdline.c_str()), 1 /*SW_SHOWNORMAL*/);
}
