#pragma once
// 7.15 Exception / SEH (i386) — included from shim32.cpp.
//
// x86 SEH is a completely different mechanism from the x64 one the 64-bit
// shim faces.  x64 is table-driven (.pdata/.xdata unwind tables), which is
// why the 64-bit shim stubs RtlLookupFunctionEntry/RtlVirtualUnwind.  x86 is
// chain-driven: every `__try` inlines
//
//     push <handler>; push fs:[0]; mov fs:[0], esp
//
// building an EXCEPTION_REGISTRATION_RECORD on the stack and linking it at
// TEB.ExceptionList.  Because our fake TEB provides a writable fs:[0], that
// registration works with zero shim support — the PE code manages the chain
// itself.  What the shim must supply is the *dispatch* half, which on Windows
// lives in KiUserExceptionDispatcher: on a hardware fault, walk the chain and
// call each handler.  Here that walk is driven from the POSIX signal handler
// (see `seh_dispatch_from_signal`, called from crash_handler in shim32.cpp).
//
// Also implements the kernel32 SEH surface — top-level filter set/get, a real
// 4-argument x86 RtlUnwind, i386 RtlCaptureContext, RaiseException — and the
// msvcrt frame handler MSVC-compiled `__try` actually registers
// (`_except_handler3` plus the `_local_unwind2`/`_global_unwind2` pair).
//
// References `run_vectored_handlers` defined in shim32_kernel32_veh.hpp.
// References `g_unhandled_filter` defined in shim32.cpp.

typedef LONG (__attribute__((stdcall)) *unhandled_filter_t)(void*);
static LONG run_vectored_handlers(void*);   // defined in shim32_kernel32_veh.hpp

// ---------------------------------------------------------------------------
// i386 SEH data structures
// ---------------------------------------------------------------------------

// NTSTATUS values raised for CPU faults
#define STATUS_ACCESS_VIOLATION         0xC0000005u
#define STATUS_IN_PAGE_ERROR            0xC0000006u
#define STATUS_ILLEGAL_INSTRUCTION      0xC000001Du
#define STATUS_PRIVILEGED_INSTRUCTION   0xC0000096u
#define STATUS_FLOAT_DIVIDE_BY_ZERO     0xC000008Eu
#define STATUS_INTEGER_DIVIDE_BY_ZERO   0xC0000094u
#define STATUS_INTEGER_OVERFLOW         0xC0000095u
#define STATUS_DATATYPE_MISALIGNMENT    0x80000002u
#define STATUS_UNWIND                   0xC0000027u

// EXCEPTION_RECORD.ExceptionFlags
#define EH_NONCONTINUABLE  0x01
#define EH_UNWINDING       0x02
#define EH_EXIT_UNWIND     0x04

// EXCEPTION_DISPOSITION
#define ExceptionContinueExecution 0
#define ExceptionContinueSearch    1
#define ExceptionNestedException   2
#define ExceptionCollidedUnwind    3

// EXCEPTION_RECORD, i386 layout: 4-byte parameters (the x64 form uses 8, and
// puts ExceptionAddress at +0x10 rather than +0x0C).
struct EXCEPTION_RECORD32 {
  uint32_t ExceptionCode;                 // +0x00
  uint32_t ExceptionFlags;                // +0x04
  EXCEPTION_RECORD32* ExceptionRecord;    // +0x08
  void*    ExceptionAddress;              // +0x0C
  uint32_t NumberParameters;              // +0x10
  uint32_t ExceptionInformation[15];      // +0x14
};
static_assert(sizeof(EXCEPTION_RECORD32) == 0x50, "EXCEPTION_RECORD32 layout");

// CONTEXT, i386 layout (0x2CC bytes)
#define CONTEXT_i386        0x00010000u
#define CONTEXT_CONTROL     (CONTEXT_i386|0x0001u)
#define CONTEXT_INTEGER     (CONTEXT_i386|0x0002u)
#define CONTEXT_SEGMENTS    (CONTEXT_i386|0x0004u)
#define CONTEXT_FULL        (CONTEXT_CONTROL|CONTEXT_INTEGER|CONTEXT_SEGMENTS)

struct FLOATING_SAVE_AREA32 {
  uint32_t ControlWord, StatusWord, TagWord;
  uint32_t ErrorOffset, ErrorSelector, DataOffset, DataSelector;
  uint8_t  RegisterArea[80];
  uint32_t Cr0NpxState;
};
struct CONTEXT32 {
  uint32_t ContextFlags;                 // +0x000
  uint32_t Dr0, Dr1, Dr2, Dr3, Dr6, Dr7; // +0x004
  FLOATING_SAVE_AREA32 FloatSave;        // +0x01C
  uint32_t SegGs, SegFs, SegEs, SegDs;   // +0x08C
  uint32_t Edi, Esi, Ebx, Edx, Ecx, Eax; // +0x09C
  uint32_t Ebp;                          // +0x0B4
  uint32_t Eip;                          // +0x0B8
  uint32_t SegCs;                        // +0x0BC
  uint32_t EFlags;                       // +0x0C0
  uint32_t Esp;                          // +0x0C4
  uint32_t SegSs;                        // +0x0C8
  uint8_t  ExtendedRegisters[512];       // +0x0CC
};
static_assert(sizeof(FLOATING_SAVE_AREA32) == 112, "FLOATING_SAVE_AREA32 layout");
static_assert(sizeof(CONTEXT32) == 0x2CC, "CONTEXT32 layout");

struct EXCEPTION_POINTERS32 {
  EXCEPTION_RECORD32* ExceptionRecord;
  CONTEXT32*          ContextRecord;
};

struct EXCEPTION_REGISTRATION_RECORD;
// Frame handlers are __cdecl and return an EXCEPTION_DISPOSITION.
typedef int (CDECLAPI *seh_handler_fn)(EXCEPTION_RECORD32*,
                                       EXCEPTION_REGISTRATION_RECORD*,
                                       CONTEXT32*, void*);
struct EXCEPTION_REGISTRATION_RECORD {
  EXCEPTION_REGISTRATION_RECORD* prev;
  seh_handler_fn handler;
};

// ---------------------------------------------------------------------------
// Chain access + validation
// ---------------------------------------------------------------------------
// fake_teb is what %fs points at, so reading the field directly and reading
// fs:[0] touch the same memory — use the direct form so the walk still works
// if a thread somehow missed its set_thread_area.
static inline EXCEPTION_REGISTRATION_RECORD** seh_chain_head(void) {
  return (EXCEPTION_REGISTRATION_RECORD**)(fake_teb + TEB_ExceptionList);
}

// A registration record must be a 4-byte-aligned address inside this thread's
// stack.  Windows terminates the list with (void*)-1, not NULL, and a
// corrupted chain is a real possibility in the code we host, so bound the
// walk rather than trusting it.
static bool seh_frame_valid(const EXCEPTION_REGISTRATION_RECORD* f) {
  uintptr_t v = (uintptr_t)f;
  if( v == 0 || v == (uintptr_t)-1 ) return false;
  if( v & 3 ) return false;
  uintptr_t lo = (uintptr_t)*(void**)(fake_teb + TEB_StackLimit);
  uintptr_t hi = (uintptr_t)*(void**)(fake_teb + TEB_StackBase);
  if( lo && hi && (v < lo || v + sizeof(EXCEPTION_REGISTRATION_RECORD) > hi) )
    return false;
  return true;
}

// ---------------------------------------------------------------------------
// ucontext <-> CONTEXT32
// ---------------------------------------------------------------------------
static void seh_context_from_ucontext(CONTEXT32* ctx, const ucontext_t* uc) {
  memset(ctx, 0, sizeof(*ctx));
  ctx->ContextFlags = CONTEXT_FULL;
#ifdef __i386__
  const greg_t* g = uc->uc_mcontext.gregs;
  ctx->Edi    = (uint32_t)g[REG_EDI];
  ctx->Esi    = (uint32_t)g[REG_ESI];
  ctx->Ebx    = (uint32_t)g[REG_EBX];
  ctx->Edx    = (uint32_t)g[REG_EDX];
  ctx->Ecx    = (uint32_t)g[REG_ECX];
  ctx->Eax    = (uint32_t)g[REG_EAX];
  ctx->Ebp    = (uint32_t)g[REG_EBP];
  ctx->Eip    = (uint32_t)g[REG_EIP];
  ctx->Esp    = (uint32_t)g[REG_ESP];
  ctx->EFlags = (uint32_t)g[REG_EFL];
  ctx->SegCs  = (uint32_t)g[REG_CS];
  ctx->SegSs  = (uint32_t)g[REG_SS];
  ctx->SegDs  = (uint32_t)g[REG_DS];
  ctx->SegEs  = (uint32_t)g[REG_ES];
  ctx->SegFs  = (uint32_t)g[REG_FS];
  ctx->SegGs  = (uint32_t)g[REG_GS];
#else
  (void)uc;
#endif
}

static void seh_context_to_ucontext(const CONTEXT32* ctx, ucontext_t* uc) {
#ifdef __i386__
  greg_t* g = uc->uc_mcontext.gregs;
  g[REG_EDI] = (greg_t)ctx->Edi;
  g[REG_ESI] = (greg_t)ctx->Esi;
  g[REG_EBX] = (greg_t)ctx->Ebx;
  g[REG_EDX] = (greg_t)ctx->Edx;
  g[REG_ECX] = (greg_t)ctx->Ecx;
  g[REG_EAX] = (greg_t)ctx->Eax;
  g[REG_EBP] = (greg_t)ctx->Ebp;
  g[REG_EIP] = (greg_t)ctx->Eip;
  g[REG_ESP] = (greg_t)ctx->Esp;
  g[REG_EFL] = (greg_t)ctx->EFlags;
#else
  (void)ctx; (void)uc;
#endif
}

static uint32_t seh_code_from_signal(int sig, const siginfo_t* si) {
  switch( sig ) {
  case SIGSEGV: return STATUS_ACCESS_VIOLATION;
  case SIGBUS:  return (si && si->si_code == BUS_ADRALN)
                       ? STATUS_DATATYPE_MISALIGNMENT : STATUS_IN_PAGE_ERROR;
  case SIGILL:  return (si && si->si_code == ILL_PRVOPC)
                       ? STATUS_PRIVILEGED_INSTRUCTION : STATUS_ILLEGAL_INSTRUCTION;
  case SIGFPE:
    if( si ) {
      switch( si->si_code ) {
      case FPE_INTDIV: return STATUS_INTEGER_DIVIDE_BY_ZERO;
      case FPE_INTOVF: return STATUS_INTEGER_OVERFLOW;
      case FPE_FLTDIV: return STATUS_FLOAT_DIVIDE_BY_ZERO;
      default: break;
      }
    }
    return STATUS_INTEGER_DIVIDE_BY_ZERO;
  default:      return STATUS_ACCESS_VIOLATION;
  }
}

// ---------------------------------------------------------------------------
// The dispatcher: walk TEB.ExceptionList calling each frame handler.
// Returns ExceptionContinueExecution if a handler asked to resume (in which
// case *ctx holds the register state to resume with), ExceptionContinueSearch
// if the chain ran out.  A handler that selects a __except block does not
// return at all — it transfers control straight into the PE's handler body.
// ---------------------------------------------------------------------------
static int seh_walk_chain(EXCEPTION_RECORD32* rec, CONTEXT32* ctx) {
  EXCEPTION_REGISTRATION_RECORD* frame = *seh_chain_head();
  for( int guard = 0; guard < 4096 && seh_frame_valid(frame); ++guard ) {
    EXCEPTION_REGISTRATION_RECORD* next = frame->prev;
    void* dispatcher = nullptr;
    log_always("[SHIM] SEH: frame=%p handler=%p code=0x%08x\n",
               (void*)frame, (void*)frame->handler, rec->ExceptionCode);
    if( !frame->handler ) { frame = next; continue; }
    int disp = frame->handler(rec, frame, ctx, &dispatcher);
    log_always("[SHIM] SEH: handler returned %d\n", disp);
    switch( disp ) {
    case ExceptionContinueExecution:
      if( rec->ExceptionFlags & EH_NONCONTINUABLE ) return ExceptionContinueSearch;
      return ExceptionContinueExecution;
    case ExceptionContinueSearch:
      break;
    default:
      // Nested / collided unwind.  A faithful implementation would restart
      // the walk from the dispatcher context; say so rather than silently
      // mis-dispatching, and keep searching.
      log_always("[SHIM] SEH: disposition %d not implemented; continuing search\n", disp);
      break;
    }
    frame = next;
  }
  return ExceptionContinueSearch;
}

// Called from crash_handler (shim32.cpp) on SIGSEGV/SIGILL/SIGFPE/SIGBUS.
static bool seh_dispatch_from_signal(int sig, siginfo_t* si, ucontext_t* uc) {
#ifdef __i386__
  if( !seh_frame_valid(*seh_chain_head()) ) return false;

  // A handler that picks a __except block never returns here — it jumps
  // straight into the PE code, abandoning this signal frame, so sigreturn
  // never runs and the mask the kernel set on delivery would stay blocked
  // forever.  Restore it up front (the same value sigreturn would restore),
  // which also lets a fault inside a handler be reported instead of turning
  // into an instant kill.
  sigprocmask(SIG_SETMASK, &uc->uc_sigmask, nullptr);

  EXCEPTION_RECORD32 rec;
  memset(&rec, 0, sizeof(rec));
  rec.ExceptionCode    = seh_code_from_signal(sig, si);
  rec.ExceptionAddress = (void*)(uintptr_t)uc->uc_mcontext.gregs[REG_EIP];
  if( rec.ExceptionCode == STATUS_ACCESS_VIOLATION ||
      rec.ExceptionCode == STATUS_IN_PAGE_ERROR ) {
    rec.NumberParameters = 2;
    rec.ExceptionInformation[0] = 0;  // 0 = read, 1 = write (not distinguished)
    rec.ExceptionInformation[1] = (uint32_t)(uintptr_t)(si ? si->si_addr : nullptr);
  }

  CONTEXT32 ctx;
  seh_context_from_ucontext(&ctx, uc);

  if( seh_walk_chain(&rec, &ctx) == ExceptionContinueExecution ) {
    seh_context_to_ucontext(&ctx, uc);
    return true;
  }
  return false;
#else
  (void)sig; (void)si; (void)uc;
  return false;
#endif
}

// ---------------------------------------------------------------------------
// kernel32 exception surface
// ---------------------------------------------------------------------------
extern "C" EXPORT LPVOID kernel32_SetUnhandledExceptionFilter(LPVOID filter) {
  log_always("[SHIM] SetUnhandledExceptionFilter(%p)\n", filter);
  // Atomic swap so concurrent set/get can't tear the pointer.
  void* old = __atomic_exchange_n(&g_unhandled_filter, filter, __ATOMIC_ACQ_REL);
  return old;
}

extern "C" EXPORT LONG kernel32_UnhandledExceptionFilter(void* pExcept) {
  if( pExcept ) {
    EXCEPTION_POINTERS32* ep = (EXCEPTION_POINTERS32*)pExcept;
    if( ep->ExceptionRecord ) {
      log_always("[SHIM] UnhandledExceptionFilter code=0x%08x addr=%p\n",
                 ep->ExceptionRecord->ExceptionCode,
                 ep->ExceptionRecord->ExceptionAddress);
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

  // Invoke the registered top-level filter if one exists.  Honour the return:
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

// RtlUnwind — the 4-argument x86 form.  Walks TEB.ExceptionList from the head
// down to (but not including) TargetFrame, calling each handler with
// EXCEPTION_UNWINDING set so its __finally blocks run, and popping each frame
// off the chain as it goes.
extern "C" EXPORT void kernel32_RtlUnwind(void* target_frame, void* target_ip,
                                          EXCEPTION_RECORD32* rec, void* retval) {
  (void)target_ip; (void)retval;
  EXCEPTION_RECORD32 local;
  if( !rec ) {
    memset(&local, 0, sizeof(local));
    local.ExceptionCode    = STATUS_UNWIND;
    local.ExceptionAddress = __builtin_return_address(0);
    rec = &local;
  }
  rec->ExceptionFlags |= EH_UNWINDING;
  if( !target_frame ) rec->ExceptionFlags |= EH_EXIT_UNWIND;

  CONTEXT32 ctx;
  memset(&ctx, 0, sizeof(ctx));
  ctx.ContextFlags = CONTEXT_FULL;

  EXCEPTION_REGISTRATION_RECORD** head = seh_chain_head();
  for( int guard = 0; guard < 4096; ++guard ) {
    EXCEPTION_REGISTRATION_RECORD* frame = *head;
    if( !seh_frame_valid(frame) ) break;
    if( frame == (EXCEPTION_REGISTRATION_RECORD*)target_frame ) break;
    void* dispatcher = nullptr;
    if( frame->handler ) {
      int disp = frame->handler(rec, frame, &ctx, &dispatcher);
      if( disp != ExceptionContinueSearch )
        log_always("[SHIM] RtlUnwind: frame %p returned %d during unwind\n",
                   (void*)frame, disp);
    }
    // Pop, unless the handler already unlinked itself — re-reading the head
    // keeps a self-unlinking handler from making us skip the next frame.
    if( *head == frame )
      *head = frame->prev;
  }
}

// x64-only entry point; kept so a mislinked import still resolves, and
// forwarded to the x86 form so it does something sensible.
extern "C" EXPORT void kernel32_RtlUnwindEx(void* f, void* target, void* except,
                                            void* retval, void* ctx, void* histo) {
  (void)target; (void)ctx; (void)histo;
  kernel32_RtlUnwind(f, nullptr, (EXCEPTION_RECORD32*)except, retval);
}

// RtlCaptureContext — fill the i386 CONTEXT with the caller's register state.
// Naked so the frame this reports is the caller's, not a prologue's.
extern "C" __attribute__((visibility("default"), stdcall, naked))
void kernel32_RtlCaptureContext(void* /*ctx*/) {
  __asm__ volatile(
    "pushl %%ebx\n"
    "movl  8(%%esp),%%ebx\n"          // ebx = ctx  ([esp+0]=saved ebx, [esp+4]=retaddr)
    "testl %%ebx,%%ebx\n"
    "jz    1f\n"
    "movl  $0x10007,0x000(%%ebx)\n"   // ContextFlags = CONTEXT_FULL
    "movl  %%edi,0x09C(%%ebx)\n"      // Edi
    "movl  %%esi,0x0A0(%%ebx)\n"      // Esi
    "movl  (%%esp),%%eax\n"           // caller's ebx, saved above
    "movl  %%eax,0x0A4(%%ebx)\n"      // Ebx
    "movl  %%edx,0x0A8(%%ebx)\n"      // Edx
    "movl  %%ecx,0x0AC(%%ebx)\n"      // Ecx
    "movl  %%eax,0x0B0(%%ebx)\n"      // Eax (already clobbered by the arg load)
    "movl  %%ebp,0x0B4(%%ebx)\n"      // Ebp
    "movl  4(%%esp),%%eax\n"          // return address
    "movl  %%eax,0x0B8(%%ebx)\n"      // Eip
    "xorl  %%eax,%%eax\n"
    "movw  %%cs,%%ax\n"
    "movl  %%eax,0x0BC(%%ebx)\n"      // SegCs
    "pushfl\n"
    "popl  %%eax\n"
    "movl  %%eax,0x0C0(%%ebx)\n"      // EFlags
    "leal  12(%%esp),%%eax\n"         // esp as the caller sees it after `ret $4`
    "movl  %%eax,0x0C4(%%ebx)\n"      // Esp
    "xorl  %%eax,%%eax\n"
    "movw  %%ss,%%ax\n"
    "movl  %%eax,0x0C8(%%ebx)\n"      // SegSs
    "1:\n"
    "popl  %%ebx\n"
    "ret   $4\n" ::: "memory");
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

extern "C" EXPORT void kernel32_RaiseException(DWORD code, DWORD flags, DWORD nargs,
                                               const ULONG_PTR* args) {
  log_always("[SHIM] RaiseException code=0x%08x flags=0x%x nargs=%u\n", code, flags, nargs);

  EXCEPTION_RECORD32 rec;
  memset(&rec, 0, sizeof(rec));
  rec.ExceptionCode    = code;
  rec.ExceptionFlags   = flags;
  rec.ExceptionAddress = __builtin_return_address(0);
  uint32_t n = (nargs > 15) ? 15 : nargs;
  rec.NumberParameters = n;
  for( uint32_t i = 0; i < n && args; i++ )
    rec.ExceptionInformation[i] = (uint32_t)args[i];

  CONTEXT32 ctx;
  kernel32_RtlCaptureContext(&ctx);

  EXCEPTION_POINTERS32 eptr = { &rec, &ctx };
  LONG vr = run_vectored_handlers(&eptr);
  if( vr == -1 /*EXCEPTION_CONTINUE_EXECUTION*/ ) return;

  // Software exceptions go through the same fs:[0] chain as hardware ones,
  // so a __try/__except around the RaiseException call site catches this.
  // A handler that selects a __except block never comes back.
  if( seh_walk_chain(&rec, &ctx) == ExceptionContinueExecution )
    return;

  if( flags & EXCEPTION_NONCONTINUABLE )
    _exit((int)code);
  // Continuable and nobody claimed it: return to the caller, matching what
  // Windows does once the chain is exhausted without a handler.
}

// ---------------------------------------------------------------------------
// msvcrt frame handlers — what MSVC-compiled `__try` actually registers
// ---------------------------------------------------------------------------
// The registration record an _except_handler3 frame builds is longer than the
// two-word base record.  MSVC's prologue is
//     push ebp; mov ebp,esp
//     push -1                  ; trylevel      → [ebp-0x04]
//     push offset scopetable   ;               → [ebp-0x08]
//     push offset handler      ;               → [ebp-0x0C]
//     push fs:[0]              ; prev          → [ebp-0x10]
//     mov  fs:[0], esp
// so the record starts at ebp-0x10 and `&frame->_ebp` is the function's EBP.
// The filter reads GetExceptionInformation() from [ebp-0x14], i.e. the word
// just below the record.
struct MSVCRT_EXCEPTION_FRAME;
struct SCOPETABLE_ENTRY {
  int   previousTryLevel;
  void* lpfnFilter;
  void* lpfnHandler;
};
struct MSVCRT_EXCEPTION_FRAME {
  EXCEPTION_REGISTRATION_RECORD* prev;
  seh_handler_fn    handler;
  SCOPETABLE_ENTRY* scopetable;
  int               trylevel;
  int               _ebp;
};
#define TRYLEVEL_END (-1)

// Call an MSVC filter/handler funclet with EBP set to the establishing
// frame's EBP — the funclet addresses its enclosing function's locals
// through that register, so it is part of the calling convention here.
static inline int msvcrt_call_filter(void* func, void* ebp) {
  int ret;
  __asm__ __volatile__("pushl %%ebp\n\t"
                       "movl %2,%%ebp\n\t"
                       "call *%1\n\t"
                       "popl %%ebp"
                       : "=a"(ret) : "r"(func), "r"(ebp) : "ecx", "edx", "memory");
  return ret;
}
static inline void msvcrt_call_handler(void* func, void* ebp) {
  __asm__ __volatile__("pushl %%ebp\n\t"
                       "movl %1,%%ebp\n\t"
                       "call *%0\n\t"
                       "popl %%ebp"
                       :: "r"(func), "r"(ebp) : "eax", "ecx", "edx", "memory");
}

// _local_unwind2 — run the __finally blocks (scope entries with no filter)
// from the frame's current trylevel down to `stop`.
extern "C" EXPORT_CDECL void msvcrt__local_unwind2(MSVCRT_EXCEPTION_FRAME* frame, int stop) {
  if( !frame || !frame->scopetable ) return;
  for( int guard = 0; guard < 4096; ++guard ) {
    int level = frame->trylevel;
    if( level == TRYLEVEL_END || level == stop ) break;
    frame->trylevel = frame->scopetable[level].previousTryLevel;
    if( !frame->scopetable[level].lpfnFilter )
      msvcrt_call_handler(frame->scopetable[level].lpfnHandler, &frame->_ebp);
  }
}

extern "C" EXPORT_CDECL void msvcrt__global_unwind2(void* frame) {
  kernel32_RtlUnwind(frame, nullptr, nullptr, nullptr);
}

// _except_handler3 — the scope-table interpreter.  Walks the frame's try
// levels outward, asking each filter what to do; on EXCEPTION_EXECUTE_HANDLER
// it unwinds everything above this frame and transfers into the __except
// block, which never returns here.
extern "C" EXPORT_CDECL int msvcrt__except_handler3(EXCEPTION_RECORD32* rec,
                                                    MSVCRT_EXCEPTION_FRAME* frame,
                                                    CONTEXT32* ctx, void* dispatch) {
  (void)ctx; (void)dispatch;
  if( !rec || !frame ) return ExceptionContinueSearch;

  if( rec->ExceptionFlags & (EH_UNWINDING|EH_EXIT_UNWIND) ) {
    msvcrt__local_unwind2(frame, TRYLEVEL_END);
    return ExceptionContinueSearch;
  }
  if( !frame->scopetable ) return ExceptionContinueSearch;

  EXCEPTION_POINTERS32 eptr = { rec, ctx };
  // Publish EXCEPTION_POINTERS at frame-4, which is [ebp-0x14] of the
  // establishing function — where MSVC compiles GetExceptionInformation()
  // to read from.  Storing the address of a local is deliberate and safe:
  // every filter that can observe it runs below us on the stack, so this
  // frame outlives all of them.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdangling-pointer"
  *((void**)frame - 1) = &eptr;
#pragma GCC diagnostic pop

  for( int trylevel = frame->trylevel, guard = 0;
       trylevel != TRYLEVEL_END && guard < 4096;
       trylevel = frame->scopetable[trylevel].previousTryLevel, ++guard ) {
    void* filter = frame->scopetable[trylevel].lpfnFilter;
    if( !filter ) continue;   // __finally entry: only runs during unwind
    int r = msvcrt_call_filter(filter, &frame->_ebp);
    log_always("[SHIM] _except_handler3: trylevel=%d filter=%p -> %d\n",
               trylevel, filter, r);
    if( r == -1 /*EXCEPTION_CONTINUE_EXECUTION*/ )
      return ExceptionContinueExecution;
    if( r == EXCEPTION_EXECUTE_HANDLER ) {
      // Unwind every frame above this one, then this frame's own __finally
      // blocks, then enter the __except body.  It does not come back.
      msvcrt__global_unwind2(frame);
      msvcrt__local_unwind2(frame, trylevel);
      frame->trylevel = frame->scopetable[trylevel].previousTryLevel;
      msvcrt_call_handler(frame->scopetable[trylevel].lpfnHandler, &frame->_ebp);
      // Unreachable in practice — the __except body ends with the enclosing
      // function's epilogue.
      return ExceptionContinueExecution;
    }
  }
  return ExceptionContinueSearch;
}

// _except_handler4 uses a different, cookie-obfuscated scope table: the
// scopetable pointer is XORed with the image's __security_cookie, which lives
// in the PE and is not reachable from here.  Decoding it wrong would run
// arbitrary addresses as filters, so decline instead and let the exception
// propagate to the next frame (and ultimately the top-level filter).
extern "C" EXPORT_CDECL int msvcrt__except_handler4_common(void* cookie, void* checkfn,
                                                           EXCEPTION_RECORD32* rec,
                                                           void* frame, CONTEXT32* ctx) {
  (void)cookie; (void)checkfn; (void)rec; (void)frame; (void)ctx;
  log_always("[SHIM] _except_handler4_common: cookie-encoded scope tables "
             "are not decoded; continuing search\n");
  return ExceptionContinueSearch;
}
extern "C" EXPORT_CDECL int msvcrt__except_handler4(EXCEPTION_RECORD32* rec, void* frame,
                                                    CONTEXT32* ctx, void* dispatch) {
  (void)rec; (void)frame; (void)ctx; (void)dispatch;
  log_always("[SHIM] _except_handler4: cookie-encoded scope tables are not "
             "decoded; continuing search\n");
  return ExceptionContinueSearch;
}

// _XcptFilter — the CRT's top-level filter, wrapped around main().  Route it
// through UnhandledExceptionFilter so VEH and any user-installed top-level
// filter still get their turn.
extern "C" EXPORT_CDECL int msvcrt__XcptFilter(unsigned long code, EXCEPTION_POINTERS32* ep) {
  log_always("[SHIM] _XcptFilter code=0x%08lx\n", code);
  return (int)kernel32_UnhandledExceptionFilter(ep);
}
