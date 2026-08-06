// load32.cpp - dlopen a pe2elf32 --so .so and invoke its `_entrypoint` symbol
// with the MSVC WinMain prototype.
//
// Usage: ./load32 <pe.so> [args...]
//
// The remaining argv (after argv[1]) is joined with spaces (and quoted on
// whitespace) and passed as lpCmdLine. hInstance/hPrevInstance are NULL,
// nShowCmd is SW_SHOWNORMAL (1).
//
// Build with -m32; must be linked against winapi_shim32.so (see the Makefile)
// so the shim's initial-exec __thread variables are allocated from the static
// TLS block at program startup rather than arriving late via dlopen.

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

// __cdecl: the convention barely matters here — the generated _entrypoint
// trampoline ignores its arguments entirely and never returns — but cdecl is
// the correct choice because the *caller* then owns argument cleanup.  A
// stdcall declaration would promise a `ret N` the trampoline never performs.
typedef int (*winmain_t)(void* hInstance,
                         void* hPrevInstance,
                         char* lpCmdLine,
                         int   nShowCmd) __attribute__((cdecl));

// Exported by winapi_shim32.so. Forces it to re-read WINAPI_SHIM_CMDLINE
// from the environment (the shim's normal init runs as a constructor,
// before load32's main(), so anything we put in the environment is too
// late without this nudge).
extern "C" void shim_reload_cmdline(void);

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

  // Hand the shim the literal Windows-style command line we want the PE
  // to see (instead of letting it derive one from /proc/self/cmdline,
  // which would include ./load32).  The PE's CRT treats the first
  // whitespace-separated token as argv[0] (program name), so we
  // prepend the .so path with quoting in case it contains spaces.
  std::string shim_cmdline;
  shim_cmdline.reserve(strlen(so_path) + cmdline.size() + 4);
  shim_cmdline += '"';
  shim_cmdline += so_path;
  shim_cmdline += '"';
  if( !cmdline.empty() ) {
    shim_cmdline += ' ';
    shim_cmdline += cmdline;
  }
  setenv("WINAPI_SHIM_CMDLINE", shim_cmdline.c_str(), 1);
  shim_reload_cmdline();

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
