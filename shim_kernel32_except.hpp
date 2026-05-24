#pragma once
// 7.15 Exception / SEH — included from shim.cpp.
//
// Implements the kernel32 SEH surface: top-level filter set/get, unwind
// stubs (RtlUnwind / RtlUnwindEx — full SEH walk isn't in scope), the
// CONTEXT capture helpers, and `RaiseException` which dispatches through
// the vectored-handler chain (see shim_kernel32_veh.hpp).
//
// References `run_vectored_handlers` defined in shim_kernel32_veh.hpp.
// References `g_unhandled_filter` defined in shim.cpp.

typedef LONG (__attribute__((ms_abi)) *unhandled_filter_t)(void*);
static LONG run_vectored_handlers(void*);   // defined in shim_kernel32_veh.hpp

extern "C" EXPORT LPVOID kernel32_SetUnhandledExceptionFilter(LPVOID filter) {
  log_always("[SHIM] SetUnhandledExceptionFilter(%p)\n", filter);
  // Atomic swap so concurrent set/get can't tear the pointer.
  void* old = __atomic_exchange_n(&g_unhandled_filter, filter, __ATOMIC_ACQ_REL);
  return old;
}

extern "C" EXPORT LONG kernel32_UnhandledExceptionFilter(void* pExcept) {
  if( pExcept ) {
    void** ep = (void**)pExcept;
    void* excRec = ep[0];
    if( excRec ) {
      uint32_t code = *(uint32_t*)excRec;
      void* addr = *(void**)((uint8_t*)excRec+0x10);
      log_always("[SHIM] UnhandledExceptionFilter code=0x%08x addr=%p\n", code, addr);
    } else {
      log_always("[SHIM] UnhandledExceptionFilter(NULL excRec)\n");
    }
  } else {
    log_always("[SHIM] UnhandledExceptionFilter(NULL)\n");
  }
  // Run vectored handlers first (Windows dispatch order: VEH → SEH → TLEF).
  // If any handler returns EXCEPTION_CONTINUE_EXECUTION, propagate so the
  // caller can resume.
  LONG vr = run_vectored_handlers(pExcept);
  if( vr == -1 ) return vr;

  // Invoke the registered top-level filter if one exists.  The filter
  // is itself an ms_abi function (Windows TLEF prototype), so calling
  // it from this ms_abi entrypoint is ABI-safe — the unsafe path is
  // calling it from a POSIX signal handler, which crash_handler avoids.
  // Honour the return:
  //   EXCEPTION_CONTINUE_EXECUTION (-1) → caller may continue; return.
  //   EXCEPTION_EXECUTE_HANDLER     (1) → handled; terminate.
  //   EXCEPTION_CONTINUE_SEARCH     (0) → no other handler; terminate.
  void* fp = __atomic_load_n(&g_unhandled_filter, __ATOMIC_ACQUIRE);
  if( fp ) {
    LONG r = ((unhandled_filter_t)fp)(pExcept);
    log_always("[SHIM] top-level filter returned %ld\n", (long)r);
    if( r == -1 /*EXCEPTION_CONTINUE_EXECUTION*/ ) return r;
  }
  _exit(1);
  return EXCEPTION_EXECUTE_HANDLER;
}

extern "C" EXPORT void kernel32_RtlUnwind(void* frame, void* target, void* except, void* retval) {
  (void)frame; (void)target; (void)except; (void)retval;
  log_always("[SHIM] RtlUnwind called — SEH unwind not implemented, returning\n");
}

extern "C" EXPORT void kernel32_RtlUnwindEx(void* f, void* target, void* except, void* retval, void* ctx, void* histo) {
  (void)f;
  (void)target;
  (void)except;
  (void)retval;
  (void)ctx;
  (void)histo;
  // Full SEH unwind not implemented; log and return so the caller can handle
  // the structured-exception path without a hard abort
  log_always("[SHIM] RtlUnwindEx called — SEH unwind not implemented, returning\n");
}

extern "C" EXPORT LPVOID kernel32_RtlVirtualUnwind(DWORD type, uint64_t base, uint64_t pc, void* entry, void* ctx, void** data, uint64_t* frame, void* transform) {
  (void)type;
  (void)base;
  (void)pc;
  (void)entry;
  (void)ctx;
  (void)data;
  (void)frame;
  (void)transform;
  return NULL;
}

extern "C" EXPORT LPVOID kernel32_RtlLookupFunctionEntry(uint64_t pc, uint64_t* base, void* histo) {
  (void)pc;
  (void)histo;
  if( base )
    *base = 0;
  return NULL;
}

extern "C" EXPORT void kernel32_RtlCaptureContext(void* ctx) {
  if( !ctx )
    return;
  memset(ctx, 0, 1232); // sizeof CONTEXT
  // Fill minimal fields using inline asm
  uint64_t rsp, rbp, rip;
  __asm__ volatile ("mov %%rsp, %0" : "=r" (rsp));
  __asm__ volatile ("mov %%rbp, %0" : "=r" (rbp));
  __asm__ volatile ("lea 0(%%rip), %0" : "=r" (rip));
  // CONTEXT: ContextFlags at +0, Rsp at +152, Rbp at +160, Rip at +248
  *(uint32_t*)((uint8_t*)ctx+0) = 0x10001f;     // CONTEXT_ALL roughly
  *(uint64_t*)((uint8_t*)ctx+152) = rsp;
  *(uint64_t*)((uint8_t*)ctx+160) = rbp;
  *(uint64_t*)((uint8_t*)ctx+248) = rip;
#ifdef WINAPI_LOG_ENABLED
  log_always("[SHIM] RtlCaptureContext: dumping call stack:\n");
  uint64_t* sp = (uint64_t*)(rsp+8);
  for( int i = 0; i<24; i++ )
    log_always("[SHIM]   stack[%02d]=0x%016lx\n", i, (unsigned long)sp[i]);
#endif
}

extern "C" EXPORT LPVOID kernel32_RtlPcToFileHeader(LPVOID pc, LPVOID* pbase) {
  Dl_info info;
  if( dladdr(pc, &info)&&info.dli_fbase ) {
    if( pbase )
      *pbase = info.dli_fbase;
    return pbase ? *pbase : info.dli_fbase;
  }
  if( pbase )
    *pbase = NULL;
  return NULL;
}

extern "C" EXPORT void kernel32_RaiseException(DWORD code, DWORD flags, DWORD nargs, const ULONG_PTR* args) {
  log_always("[SHIM] RaiseException code=0x%08x flags=0x%x nargs=%u\n", code, flags, nargs);

  // Synthesise an EXCEPTION_POINTERS so the VEH chain has something to
  // inspect.  Layout below matches Windows x64 EXCEPTION_RECORD /
  // EXCEPTION_POINTERS so existing handler code can dereference it.
  struct ExceptionRecord {
    uint32_t code;
    uint32_t flags;
    void* record;
    void* addr;
    uint32_t nparams;
    uint32_t pad;
    uint64_t params[15];
  };
  ExceptionRecord rec = {};
  rec.code = code;
  rec.flags = flags;
  rec.addr = __builtin_return_address(0);
  uint32_t n = (nargs > 15) ? 15 : nargs;
  rec.nparams = n;
  for( uint32_t i = 0; i < n && args; i++ ) rec.params[i] = (uint64_t)args[i];
  void* eptr[2] = { &rec, nullptr };  // ContextRecord left NULL

  LONG vr = run_vectored_handlers(eptr);
  if( vr == -1 /*EXCEPTION_CONTINUE_EXECUTION*/ ) return;

  if( flags & EXCEPTION_NONCONTINUABLE ) {
    _exit((int)code);
  }
  // For continuable exceptions with no handler interested: no SEH chain
  // to walk in this shim, so just return — caller's __try/__except
  // scaffolding (if any) will run next on the original control flow.
}
