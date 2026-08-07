// calltrace32.cpp — repeating per-call tracer for one BMF function, injected
// via `pe2elf32 --inject=calltrace32.so`.
//
// trace32.cpp answers "was this function called at all?" and disarms itself on
// the first hit.  This one answers the question that comes up when a moved
// function runs, returns, and produces a *slightly different* compressed
// stream: **which call is the first one to go wrong, and what state did it get
// wrong?**
//
// It logs, for every call to one chosen VA, the incoming register and stack
// arguments plus an FNV-1a hash of a caller-designated state block.  The same
// binary works on both sides of the comparison, because the hook is at the
// function's first byte — ahead of the `E9` that `patch_jmp` writes there —
// so a build with the function moved and a build without it trace the same
// point.  Call N's *entry* state is call N-1's output, so the first entry
// whose hash differs names the first call whose side effects were wrong.
//
//   BMF_CT_VA     hex VA to hook              (required, e.g. 0041CAB0)
//   BMF_CT_STATE  hex offset of the state pointer within ecx's block, or the
//                 word `ecx` to hash the block ecx points at directly
//   BMF_CT_OFF    hex byte offset to start hashing at (default 0)
//   BMF_CT_LEN    hex byte count to hash      (default 0x44000)
//   BMF_CT_OUT    output path                 (default calltrace.out)
//   BMF_CT_MAX    unhook after N calls        (default 0 = unlimited)
//   BMF_CT_FROM   skip hashing/logging before call N (default 0)
//   BMF_CT_STRIDE hash every Nth byte         (default 16)
//   BMF_CT_DUMP   write the whole state block to $BMF_CT_OUT.bin at call N
//   BMF_CT_RET    hex VA of the instruction after the call; when set, %eax is
//                 logged there, which is how the *return* value gets compared
//
// Re-arming uses the textbook breakpoint dance: restore the original byte,
// rewind EIP, set TF so the instruction single-steps, and put the 0xCC back on
// the trap that step produces.  SA_NODEFER matters — the single-step trap is
// delivered from inside the handler for the breakpoint trap.

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <csignal>
#include <sys/mman.h>
#include <ucontext.h>
#include <unistd.h>

static uint32_t g_va;
static uint32_t g_ret_va;
static uint8_t  g_ret_orig;
static uint32_t g_from;
static uint32_t g_dump = 0xFFFFFFFFu;
static uint32_t g_state_off;      // 0xFFFFFFFF => hash the block at ecx itself
static uint32_t g_len = 0x44000;
static uint32_t g_off;
static uint32_t g_max;
static uint8_t  g_orig;
static uint64_t g_calls;
static FILE*    g_out;
static int      g_stepping;

static void make_writable(void* addr, size_t len) {
  uintptr_t pg = (uintptr_t)sysconf(_SC_PAGESIZE);
  uintptr_t lo = (uintptr_t)addr & ~(pg - 1);
  uintptr_t hi = ((uintptr_t)addr + len + pg - 1) & ~(pg - 1);
  if (mprotect((void*)lo, hi - lo, PROT_READ | PROT_WRITE | PROT_EXEC) != 0) {
    perror("[ct] mprotect");
    abort();
  }
}

static uint32_t g_stride = 16;

// Sampled, not exhaustive: the state block is a quarter of a megabyte and the
// hook fires per call, so hashing every byte costs more wall clock than the
// whole run.  Every 16th byte is plenty to notice that two runs have diverged,
// which is all this is for.
static uint64_t fnv1a(const uint8_t* p, uint32_t n, uint32_t stride) {
  uint64_t h = 1469598103934665603ULL;
  for (uint32_t i = 0; i < n; i += stride) { h ^= p[i]; h *= 1099511628211ULL; }
  return h;
}

#define TF 0x100

static void trap_handler(int sig, siginfo_t* si, void* ctx) {
  (void)sig; (void)si;
  ucontext_t* uc = (ucontext_t*)ctx;
  greg_t* r = uc->uc_mcontext.gregs;
  uint32_t eip = (uint32_t)r[REG_EIP];

  if (g_stepping) {                    // the single step that re-arms us
    uint32_t va = (g_stepping == 2) ? g_ret_va : g_va;
    g_stepping = 0;
    r[REG_EFL] &= ~TF;
    *(uint8_t*)(uintptr_t)va = 0xCC;
    __builtin___clear_cache((char*)(uintptr_t)va, (char*)(uintptr_t)va + 1);
    return;
  }
  if (g_ret_va && eip - 1 == g_ret_va) {
    if (g_out && g_calls > g_from)
      fprintf(g_out, "  ret[%llu] eax=%08x\n",
              (unsigned long long)(g_calls - 1), (uint32_t)r[REG_EAX]);
    *(uint8_t*)(uintptr_t)g_ret_va = g_ret_orig;
    __builtin___clear_cache((char*)(uintptr_t)g_ret_va, (char*)(uintptr_t)g_ret_va + 1);
    r[REG_EIP] = (greg_t)g_ret_va;
    r[REG_EFL] |= TF;
    g_stepping = 2;
    return;
  }
  if (eip - 1 != g_va) return;

  uint32_t ecx = (uint32_t)r[REG_ECX];
  uint32_t esp = (uint32_t)r[REG_ESP];
  const uint32_t* stk = (const uint32_t*)(uintptr_t)esp;   // [0]=retaddr
  uint64_t h = 0;
  const uint8_t* base = nullptr;
  if (g_state_off == 0xFFFFFFFFu) base = (const uint8_t*)(uintptr_t)ecx;
  else if (ecx) base = *(const uint8_t* const*)(uintptr_t)(ecx + g_state_off);
  if (base && g_calls >= g_from) h = fnv1a(base + g_off, g_len, g_stride);
  if (base && g_calls == g_dump) {
    char nm[512];
    const char* op = getenv("BMF_CT_OUT");
    snprintf(nm, sizeof nm, "%s.bin", op && *op ? op : "calltrace.out");
    FILE* d = fopen(nm, "wb");
    if (d) { fwrite(base + g_off, 1, g_len, d); fclose(d); }
  }

  if (g_out && g_calls >= g_from)
    fprintf(g_out, "%llu ecx=%08x a=%08x,%08x,%08x ret=%08x st=%016llx\n",
            (unsigned long long)g_calls, ecx, stk[1], stk[2], stk[3], stk[0],
            (unsigned long long)h);
  g_calls++;

  *(uint8_t*)(uintptr_t)g_va = g_orig;
  __builtin___clear_cache((char*)(uintptr_t)g_va, (char*)(uintptr_t)g_va + 1);
  r[REG_EIP] = (greg_t)g_va;
  if (g_max && g_calls >= g_max) {      // cap reached: leave the code as found
    if (g_out) { fflush(g_out); }
    return;
  }
  r[REG_EFL] |= TF;
  g_stepping = 1;
}

#define IAT_ExitProcess 0x00438030

static void finish(void) {
  if (g_out) { fprintf(g_out, "# calls=%llu\n", (unsigned long long)g_calls); fclose(g_out); g_out = nullptr; }
}

static __attribute__((stdcall)) void my_ExitProcess(unsigned int code) {
  finish();
  _exit((int)code);
}

static uint32_t envhex(const char* n, uint32_t d) {
  const char* v = getenv(n);
  return (v && *v) ? (uint32_t)strtoul(v, nullptr, 16) : d;
}

__attribute__((constructor)) static void ct_init() {
  g_va = envhex("BMF_CT_VA", 0);
  if (!g_va) { fprintf(stderr, "[ct] BMF_CT_VA not set\n"); return; }
  const char* s = getenv("BMF_CT_STATE");
  g_state_off = (s && !strcmp(s, "ecx")) ? 0xFFFFFFFFu : envhex("BMF_CT_STATE", 0xFFFFFFFFu);
  g_len = envhex("BMF_CT_LEN", 0x44000);
  g_off = envhex("BMF_CT_OFF", 0);
  g_max = envhex("BMF_CT_MAX", 0);
  g_stride = envhex("BMF_CT_STRIDE", 16);
  if (!g_stride) g_stride = 1;
  g_from = envhex("BMF_CT_FROM", 0);
  g_ret_va = envhex("BMF_CT_RET", 0);
  g_dump = envhex("BMF_CT_DUMP", 0xFFFFFFFFu);

  const char* path = getenv("BMF_CT_OUT");
  g_out = fopen(path && *path ? path : "calltrace.out", "a");
  if (g_out) setvbuf(g_out, nullptr, _IOFBF, 1 << 20);

  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_sigaction = trap_handler;
  sa.sa_flags = SA_SIGINFO | SA_NODEFER;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGTRAP, &sa, nullptr);

  make_writable((void*)(uintptr_t)g_va, 1);
  g_orig = *(uint8_t*)(uintptr_t)g_va;
  *(uint8_t*)(uintptr_t)g_va = 0xCC;
  __builtin___clear_cache((char*)(uintptr_t)g_va, (char*)(uintptr_t)g_va + 1);
  if (g_ret_va) {
    make_writable((void*)(uintptr_t)g_ret_va, 1);
    g_ret_orig = *(uint8_t*)(uintptr_t)g_ret_va;
    *(uint8_t*)(uintptr_t)g_ret_va = 0xCC;
    __builtin___clear_cache((char*)(uintptr_t)g_ret_va, (char*)(uintptr_t)g_ret_va + 1);
  }

  make_writable((void*)IAT_ExitProcess, 4);
  *(void**)IAT_ExitProcess = (void*)&my_ExitProcess;
  fprintf(stderr, "[ct] hooked %08X\n", g_va);
}
