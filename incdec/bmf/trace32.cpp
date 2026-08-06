// trace32.cpp — first-call tracer for BMF.exe, injected via
// `pe2elf32 --inject=trace32.so`.
//
// Answers "which of the 113 Hex-Rays-identified functions does a given run
// actually execute?", which is the gate the incdec protocol needs before any
// function is worth decompiling (incdec.md §3 step 1: a function with probe
// count 0 passes the test trivially and proves nothing).
//
// Method: write 0xCC (INT3) over the first byte of every candidate entry and
// catch SIGTRAP.  On the first hit for a site we record it, restore the
// original byte, and rewind EIP so the real instruction executes — so each
// function traps exactly once and the run proceeds at full speed afterwards.
// One byte means no instruction-length decoding, unlike a JMP-based hook.
//
// Results are appended to $BMF_TRACE_OUT (default "trace.out") from the
// ExitProcess hook, so a multi-invocation test (compress then decompress)
// accumulates into one file.

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <csignal>
#include <sys/mman.h>
#include <ucontext.h>
#include <unistd.h>
#include <fcntl.h>

struct Site { uint32_t va; const char* name; const char* conv; uint8_t orig; volatile uint8_t hit; };
static Site g_sites[] = {
#include "sites.inc"
};
static const int kNSites = (int)(sizeof(g_sites) / sizeof(g_sites[0]));

static void make_writable(void* addr, size_t len) {
  uintptr_t pg = (uintptr_t)sysconf(_SC_PAGESIZE);
  uintptr_t lo = (uintptr_t)addr & ~(pg - 1);
  uintptr_t hi = ((uintptr_t)addr + len + pg - 1) & ~(pg - 1);
  if (mprotect((void*)lo, hi - lo, PROT_READ | PROT_WRITE | PROT_EXEC) != 0) {
    perror("[trace] mprotect");
    abort();
  }
}

// Binary search — the table is emitted in ascending VA order.
static Site* find_site(uint32_t va) {
  int lo = 0, hi = kNSites - 1;
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (g_sites[mid].va == va) return &g_sites[mid];
    if (g_sites[mid].va < va) lo = mid + 1; else hi = mid - 1;
  }
  return nullptr;
}

static struct sigaction g_old_trap;

static void trap_handler(int sig, siginfo_t* si, void* ctx) {
  ucontext_t* uc = (ucontext_t*)ctx;
  uint32_t eip = (uint32_t)uc->uc_mcontext.gregs[REG_EIP];
  Site* s = find_site(eip - 1);          // INT3 already advanced EIP past it
  if (!s) {
    if (g_old_trap.sa_sigaction) g_old_trap.sa_sigaction(sig, si, ctx);
    return;
  }
  *(uint8_t*)(uintptr_t)s->va = s->orig; // undo the trap: one hit is enough
  __builtin___clear_cache((char*)(uintptr_t)s->va, (char*)(uintptr_t)s->va + 1);
  s->hit = 1;
  uc->uc_mcontext.gregs[REG_EIP] = (greg_t)s->va;  // re-execute for real
}

// ExitProcess IAT slot (incdec.md §6.4)
#define IAT_ExitProcess 0x00438030

static void dump_results(void) {
  const char* path = getenv("BMF_TRACE_OUT");
  if (!path || !*path) path = "trace.out";
  FILE* f = fopen(path, "a");
  if (!f) return;
  for (int i = 0; i < kNSites; i++)
    if (g_sites[i].hit)
      fprintf(f, "%08X\t%s\t%s\n", g_sites[i].va, g_sites[i].name, g_sites[i].conv);
  fclose(f);
  int n = 0;
  for (int i = 0; i < kNSites; i++) n += g_sites[i].hit;
  fprintf(stderr, "[trace] %d/%d functions called\n", n, kNSites);
  fflush(stderr);
}

static __attribute__((stdcall)) void my_ExitProcess(unsigned int code) {
  dump_results();
  _exit((int)code);
}

static void patch_iat_slot(void* slot, void* repl) {
  make_writable(slot, 4);
  *(void**)slot = repl;
}

__attribute__((constructor)) static void trace_init() {
  // One mprotect over the whole span rather than per site.
  uint32_t lo = g_sites[0].va, hi = g_sites[kNSites - 1].va;
  make_writable((void*)(uintptr_t)lo, (size_t)(hi - lo) + 1);

  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_sigaction = trap_handler;
  sa.sa_flags = SA_SIGINFO | SA_NODEFER;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGTRAP, &sa, &g_old_trap);

  for (int i = 0; i < kNSites; i++) {
    uint8_t* p = (uint8_t*)(uintptr_t)g_sites[i].va;
    g_sites[i].orig = *p;
    *p = 0xCC;
  }
  __builtin___clear_cache((char*)(uintptr_t)lo, (char*)(uintptr_t)hi + 1);
  patch_iat_slot((void*)IAT_ExitProcess, (void*)&my_ExitProcess);
  fprintf(stderr, "[trace] armed %d sites\n", kNSites);
}
