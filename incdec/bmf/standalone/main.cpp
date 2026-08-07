// main.cpp — the standalone build's entry point and the two definitions that
// had to wait for the moved bodies.  Included last by build.sh.

// sub_402E30, whose declaration crt.cpp put in place of the PE one.  Two
// instructions in the donor:
//
//   00402E30  6A 07              push 7
//   00402E32  E8 09 00 00 00     call exit_402E40
//
// It is the handler main hands to sub_42CBB0 for "allocation failed": message
// 7 in exit_402E40's table, "Out of memory!", which takes no arguments.  The
// `pop ecx` after the call is dead code — exit_402E40 never returns.
void __sub_402E30() { __exit_402E40(7); }

int main(int argc, char **argv) {
  // The data holds absolute pointers into itself — the message table at
  // 0x00441068, the "disabled"/"enabled" pair at 0x0044104C, the filter tables
  // at 0x004410C0 — written for a load address of 0x00400000.  blob1 is
  // wherever the linker put it, so rebase them before anything reads one.
  // Nothing above this line may touch the blob.
  bmf_blob_relocate();

  // MSVC's CRT startup publishes argv at 0x00445954 — IDA even recovered the
  // name — and sub_429DB0 reads argv[0] through it to build the .ini file name
  // next to the executable.  Nothing else in the moved set touches a CRT
  // global, so this one assignment is the whole of the startup BMF lost.
  *(char ***)(blob1 + 0x00445954 - BMF_BLOB_BASE) = argv;

  // BMF's static initialisers.  MSVC puts the C++ constructor pointers in
  // .data between __xc_a and __xc_z, and _cinit walks them before main; here
  // that table is 0x00441000..0x00441008 and holds exactly one entry:
  //
  //   00441004  dd offset sub_419680
  //
  // It fills the SSE constant tables at 0x00439A00 and 0x00445760, which live
  // in the part of .data the PE leaves uninitialised — so skipping it does not
  // crash, it just runs the filters against tables of zeroes.  That was worth
  // 244 bytes on the two 8bpp images and nothing at all on the others, which
  // is exactly the kind of difference that looks like a rounding problem and
  // is not.  The other three entries in that region (__initstdio,
  // __initmbctable, and the _doexit list) belong to the MSVC CRT, which glibc
  // replaces.
  __sub_419680();

  // Not called, deliberately: sub_436BD0, Intel's cache-descriptor probe, runs
  // from __intel_new_proc_init in the PE and writes 0x00446180/0x00446184/
  // 0x004425F4 for __intel_fast_memcpy to size its non-temporal stores by.
  // Those are the two dispatchers crt.cpp replaces with glibc's, and nothing
  // else in the moved set reads the three globals.

  return __main(argc, (const char **)argv, nullptr);
}

#ifdef BMF_PROBES
// -DBMF_PROBES keeps §7.1's counters in the standalone build.  The hybrid
// dumps them from its ExitProcess hook; here an atexit handler does it, so the
// two runs can be compared function by function.
#include <cstdlib>
__attribute__((constructor)) static void bmf_probe_dump_at_exit() {
  atexit([] {
    const char *path = getenv("BMF_PROBE_OUT");
    FILE *out = stderr;
    if (path && *path) { FILE *f = fopen(path, "a"); if (f) out = f; }
    fprintf(out, "[probe] call counts:\n");
    for (Probe *p = g_probes; p; p = p->next)
      fprintf(out, "[probe]   %-24s %llu\n", p->name, p->count);
    fflush(out);
    if (out != stderr) fclose(out);
  });
}
#endif
