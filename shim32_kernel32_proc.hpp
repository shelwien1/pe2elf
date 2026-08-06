#pragma once
// 7.1 Process / Identity — included from shim32.cpp.
//
// Covers: GetCurrentProcess / GetCurrentProcessId / GetCurrentThreadId
// (reads cached TID from TEB+0x48 on x86-64), ExitProcess, TerminateProcess,
// IsDebuggerPresent, IsProcessorFeaturePresent (CPUID-backed for
// PF_* feature bits on x86-64).
//
// Also defines the file-scope `log_backtrace` helper — the glibc path uses
// <execinfo.h> backtrace(), the musl path uses libgcc's _Unwind_Backtrace.
// musl also gets a `malloc_usable_size` stub here so HeapSize / HeapReAlloc
// can fall back to conservative defaults.

extern "C" EXPORT HANDLE kernel32_GetCurrentProcess(void) {
  log_always("[SHIM] GetCurrentProcess()\n");
  return PROCESS_PSEUDO_HANDLE;
}

extern "C" EXPORT DWORD kernel32_GetCurrentProcessId(void) {
  return (DWORD)getpid();
}

extern "C" EXPORT DWORD kernel32_GetCurrentThreadId(void) {
#ifdef __i386__
  // Read the cached TID from TEB+0x24 — shim_init_teb stores it there.
  uint32_t tid;
  __asm__ volatile ("movl %%fs:0x24, %0" : "=r"(tid));
  return tid;
#else
  return (DWORD)syscall(SYS_gettid);
#endif
}

extern "C" EXPORT void kernel32_ExitProcess(DWORD code) {
  log_always("[SHIM] ExitProcess(0x%08x)\n", code);
  _exit((int)code);
}

#ifdef __GLIBC__
static void log_backtrace(void) {
  void* bt[32];
  int n = backtrace(bt, 32);
  for( int i = 0; i<n; ++i )
    log_always("[SHIM]  bt[%02d]: %p\n", i, bt[i]);
}
#else
// musl path: glibc's <execinfo.h> isn't available, but libgcc's
// _Unwind_Backtrace is, and that's actually how glibc's backtrace() walks
// the stack internally.  Frame symbolication isn't done either way for
// log_backtrace; we just need the IPs.
#include <unwind.h>
struct bt_state { void** bt; int n; int max; };
static _Unwind_Reason_Code log_backtrace_cb(struct _Unwind_Context* ctx, void* arg) {
  bt_state* s = (bt_state*)arg;
  if( s->n >= s->max ) return _URC_END_OF_STACK;
  s->bt[s->n++] = (void*)(uintptr_t)_Unwind_GetIP(ctx);
  return _URC_NO_REASON;
}
static void log_backtrace(void) {
  void* bt[32];
  bt_state s = { bt, 0, 32 };
  _Unwind_Backtrace(log_backtrace_cb, &s);
  for( int i = 0; i < s.n; ++i )
    log_always("[SHIM]  bt[%02d]: %p\n", i, bt[i]);
}
// musl doesn't provide malloc_usable_size; return 0 so HeapSize is a stub
// and HeapReAlloc zero-fills conservatively
static size_t malloc_usable_size(void* /*p*/) { return 0; }
#endif

extern "C" EXPORT BOOL kernel32_TerminateProcess(HANDLE h, DWORD code) {
  (void)h;
  log_always("[SHIM] TerminateProcess(0x%08x)\n", code);
  log_backtrace();
  _exit((int)code);
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_IsDebuggerPresent(void) {
  log_always("[SHIM] IsDebuggerPresent()\n");
  return FALSE;
}

#if defined(__i386__) || defined(__x86_64__)
static unsigned int cpuid_get_edx(unsigned int leaf) {
  unsigned int eax, ebx, ecx, edx;
  __asm__ volatile ("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                             : "a"(leaf), "c"(0));
  (void)eax; (void)ebx; (void)ecx;
  return edx;
}
#endif

extern "C" EXPORT BOOL kernel32_IsProcessorFeaturePresent(DWORD feature) {
#if defined(__i386__) || defined(__x86_64__)
  static unsigned int edx1   = 0, edx_ext = 0;
  static int          inited = 0;
  if( !inited ) {
    edx1   = cpuid_get_edx(1);
    edx_ext = cpuid_get_edx(0x80000001);
    inited = 1;
  }
  switch( feature ) {
  case PF_FLOATING_POINT_EMULATED:      return FALSE;
  case PF_COMPARE_EXCHANGE_DOUBLE:      return (edx1>>8)&1  ? TRUE : FALSE; // CMPXCHG8B
  case PF_MMX_INSTRUCTIONS_AVAILABLE:   return (edx1>>23)&1 ? TRUE : FALSE;
  case PF_XMMI_INSTRUCTIONS_AVAILABLE:  return (edx1>>25)&1 ? TRUE : FALSE; // SSE
  case PF_RDTSC_INSTRUCTION_AVAILABLE:  return (edx1>>4)&1  ? TRUE : FALSE;
  case PF_3DNOW_INSTRUCTIONS_AVAILABLE: return (edx_ext>>31)&1 ? TRUE : FALSE;
  default: return FALSE;
  }
#else
  (void)feature;
  return FALSE;
#endif
}
