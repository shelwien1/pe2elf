// shim32.cpp — WinAPI shim for PE32→ELF32 converted binaries (i386)
// Exports Windows API functions using __attribute__((stdcall)) — plus cdecl
// for variadics/CRT and thiscall for COM vtables (see shim32_types.h).
// All functions callable from MSVC-compiled 32-bit PE code.

#include "shim32_types.h"

#include <asm/ldt.h>
#include <dirent.h>
#include <dlfcn.h>
#include <link.h>
#include <errno.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <limits.h>
#include <locale.h>
#ifdef __GLIBC__
#include <execinfo.h>
#include <malloc.h>
#endif
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <sys/resource.h>
#include <time.h>
#include <ctype.h>
#include <wctype.h>
#include <sys/statvfs.h>
#include <termios.h>
#include <ucontext.h>
#include <unistd.h>

// ---------------------------------------------------------------------------
// Visibility
// ---------------------------------------------------------------------------
#define EXPORT __attribute__((visibility("default"))) WINAPI
// Variadic Win32/CRT entry points and CRT callbacks must be cdecl: a stdcall
// callee cannot know how many argument bytes to pop.
#define EXPORT_CDECL __attribute__((visibility("default"))) CDECLAPI
#pragma GCC visibility push(hidden)

// ---------------------------------------------------------------------------
// Logging
// ---------------------------------------------------------------------------
static int g_log_fd = -1;

static void log_init(void) {
  // Runtime-configurable: WINAPI_SHIM_LOG=/path/to/file or "stderr"
  const char* env = getenv("WINAPI_SHIM_LOG");
  if( env ) {
    if( strcmp(env, "stderr")==0 )
      g_log_fd = 2;
    else
      g_log_fd = open(env, O_WRONLY|O_CREAT|O_TRUNC|O_SYNC, 0644);
  }
#ifdef WINAPI_LOG_ENABLED
  if( g_log_fd<0 )
    g_log_fd = open("/tmp/shimlog.txt", O_WRONLY|O_CREAT|O_TRUNC|O_SYNC, 0644);
#endif
}

__attribute__((format(printf, 1, 2))) static void log_write(const char* fmt, ...) {
  if( g_log_fd<0 )
    return;
  char buf[512];
  va_list ap;
  va_start(ap, fmt);
  int n = vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);
  if( n<=0 ) return;
  size_t sz = (size_t)n<sizeof(buf) ? (size_t)n : sizeof(buf)-1;
  ssize_t _wr = write(g_log_fd, buf, sz);
  (void)_wr;
}

// Single logging entrypoint.  log_write itself runtime-gates on g_log_fd,
// so this is cheap when WINAPI_SHIM_LOG isn't set.  WINAPI_LOG_ENABLED
// (the debug build) only forces the file open in log_init and switches on
// the extra stack dump inside RtlCaptureContext.
#define log_always log_write

// ---------------------------------------------------------------------------
// Thread-local last error
// ---------------------------------------------------------------------------
// initial-exec TLS model.  On i386 the register-clobber argument that
// motivates it on x86-64 (__tls_get_addr's call sequence trashing RDI, which
// is callee-saved under the MS x64 ABI) does not apply — the argument register is
// EAX, caller-saved under both stdcall and cdecl.  What *does* still apply is
// the load-order requirement: initial-exec variables are carved out of the
// static TLS block at program startup, which only works if the .so is a
// load-time dependency (true for winapi_shim32.so, DT_NEEDED of the converted
// ELF and of load32).
static __thread uint32_t tls_last_error __attribute__((tls_model("initial-exec"))) = 0;
// The fake TEB is what %fs points at, so it must be 4-byte aligned at least;
// give it 16 for the CONTEXT/FP save areas that live inside on real Windows.
static __thread uint8_t  fake_teb[0x2000] __attribute__((tls_model("initial-exec"), aligned(16)));

// pthread key whose destructor runs FLS callbacks and frees the per-thread
// tls_slots block on thread exit.  Single destructor (rather than separate
// keys for FLS callbacks and slot free) so the order is well-defined —
// POSIX leaves ordering between pthread_key_create destructors unspecified,
// and freeing the slots before running the callbacks turned the callback
// pass into a use-after-free.
static pthread_key_t  g_tls_slots_key;
static pthread_once_t g_tls_slots_key_once = PTHREAD_ONCE_INIT;

static DWORD g_tls_static_idx = 0xFFFFFFFFu; // pre-allocated static TLS slot; defined below

static void shim_thread_exit(void*);  // defined alongside the FLS section below

static void tls_slots_key_init(void) { pthread_key_create(&g_tls_slots_key, shim_thread_exit); }

// ---------------------------------------------------------------------------
// Win32 TEB layout, 32-bit.  Every offset differs from the x64 one, so they
// are named here rather than scattered as literals.
// ---------------------------------------------------------------------------
#define TEB_ExceptionList   0x00   // SEH chain head — fs:[0]
#define TEB_StackBase       0x04
#define TEB_StackLimit      0x08
#define TEB_Self            0x18
#define TEB_ProcessId       0x20
#define TEB_ThreadId        0x24
#define TEB_TlsPointer      0x2C   // ThreadLocalStoragePointer
#define TEB_Peb             0x30
#define TEB_LastError       0x34
#define TEB_TlsSlots        0xE10  // TlsSlots[64]
#define TEB_TlsExpansion    0xF94

// Mirror last error to TEB+0x34; inlined MSVC code reads fs:[0x34] directly.
#define SET_LAST_ERROR(e) do { \
  tls_last_error = (e); \
  *(uint32_t*)(fake_teb+TEB_LastError) = (e); \
} while(0)

static uint32_t errno_to_win32(int e) {
  switch( e ) {
  case ENOENT:   return ERROR_FILE_NOT_FOUND;
  case ENOTDIR:  return ERROR_PATH_NOT_FOUND;
  case EACCES:   return ERROR_ACCESS_DENIED;
  case EPERM:    return ERROR_ACCESS_DENIED;
  case EISDIR:   return ERROR_ACCESS_DENIED;
  case EBADF:    return ERROR_INVALID_HANDLE;
  case ENOMEM:   return ERROR_OUTOFMEMORY;
  case EEXIST:   return 80;  // ERROR_FILE_EXISTS
  case EINVAL:   return ERROR_INVALID_PARAMETER;
  case EMFILE:   return ERROR_TOO_MANY_OPEN_FILES;
  case ENOSPC:   return 112; // ERROR_DISK_FULL
  case ENOTEMPTY: return 145; // ERROR_DIR_NOT_EMPTY
  case EAGAIN:   return 258; // ERROR_TIMEOUT (or ERROR_IO_INCOMPLETE)
  case EBUSY:    return 32;  // ERROR_SHARING_VIOLATION
  case ETIMEDOUT: return 258; // ERROR_TIMEOUT
  case EINTR:    return 995; // ERROR_OPERATION_ABORTED
  case ENAMETOOLONG: return 206; // ERROR_FILENAME_EXCED_RANGE
  case ENOSYS:   return ERROR_CALL_NOT_IMPLEMENTED;
  case ENOTSUP:  return ERROR_CALL_NOT_IMPLEMENTED;
  default:       return ERROR_INVALID_PARAMETER;
  }
}

static void set_errno_error(void) {
  SET_LAST_ERROR(errno_to_win32(errno));
}

// Compile-time size assertions (I7)
static_assert(sizeof(pthread_mutex_t)<=sizeof(CRITICAL_SECTION),
              "CRITICAL_SECTION too small for pthread_mutex_t");
static_assert(sizeof(FILETIME)==8, "FILETIME size");
static_assert(sizeof(LARGE_INTEGER)==8, "LARGE_INTEGER size");
static_assert(sizeof(WIN32_FIND_DATAA)==320, "WIN32_FIND_DATAA size");

// ---------------------------------------------------------------------------
// Fake TEB/PEB
// ---------------------------------------------------------------------------
// fake_teb declared earlier (near SET_LAST_ERROR macro)
static uint8_t fake_peb[0x1000];

// PEB_LDR_DATA (self-consistent empty module list)
static uint8_t fake_ldr_data[0x60];
// RTL_USER_PROCESS_PARAMETERS (minimal, with empty strings)
static uint8_t fake_proc_params[0x200];
// Empty wide string for UNICODE_STRING buffers
static uint16_t fake_empty_wstr[2] = {0, 0};

// Win32 PEB layout, 32-bit
#define PEB_BeingDebugged     0x02
#define PEB_ImageBaseAddress  0x08
#define PEB_Ldr               0x0C
#define PEB_ProcessParameters 0x10
#define PEB_ProcessHeap       0x18

static void init_fake_peb(void) {
  memset(fake_peb, 0, sizeof(fake_peb));

  // PEB+0x08: ImageBaseAddress
  *(void**)(fake_peb+PEB_ImageBaseAddress) = (void*)0x400000;

  // PEB+0x0C: Ldr -> PEB_LDR_DATA (32-bit layout; each LIST_ENTRY is 8 bytes)
  // +0x00 Length, +0x04 Initialized, +0x0C/0x10 InLoadOrder list,
  // +0x14/0x18 InMemoryOrder, +0x1C/0x20 InInitializationOrder
  memset(fake_ldr_data, 0, sizeof(fake_ldr_data));
  *(uint32_t*)(fake_ldr_data+0x00) = (uint32_t)sizeof(fake_ldr_data);
  *(uint8_t*)(fake_ldr_data+0x04) = 1;    // Initialized = TRUE
  // Self-referencing empty lists (Flink = Blink = head)
  *(void**)(fake_ldr_data+0x0C) = fake_ldr_data+0x0C;
  *(void**)(fake_ldr_data+0x10) = fake_ldr_data+0x0C;
  *(void**)(fake_ldr_data+0x14) = fake_ldr_data+0x14;
  *(void**)(fake_ldr_data+0x18) = fake_ldr_data+0x14;
  *(void**)(fake_ldr_data+0x1C) = fake_ldr_data+0x1C;
  *(void**)(fake_ldr_data+0x20) = fake_ldr_data+0x1C;
  *(void**)(fake_peb+PEB_Ldr) = fake_ldr_data;

  // PEB+0x10: ProcessParameters -> RTL_USER_PROCESS_PARAMETERS (32-bit layout)
  // +0x000 MaximumLength   ULONG
  // +0x004 Length          ULONG
  // +0x008 Flags           ULONG  (1 = normalized)
  // +0x010 ConsoleHandle   HANDLE
  // +0x018 StandardInput   HANDLE
  // +0x01C StandardOutput  HANDLE
  // +0x020 StandardError   HANDLE
  // +0x024 CurrentDirectory.DosPath UNICODE_STRING, +0x02C Handle
  // +0x030 DllPath         UNICODE_STRING (+0x030 len, +0x032 maxlen, +0x034 buf)
  // +0x038 ImagePathName   UNICODE_STRING (+0x038 len, +0x03a maxlen, +0x03c buf)
  // +0x040 CommandLine     UNICODE_STRING (+0x040 len, +0x042 maxlen, +0x044 buf)
  // +0x048 Environment     PVOID
  memset(fake_proc_params, 0, sizeof(fake_proc_params));
  uint8_t* pp = fake_proc_params;
  *(uint32_t*)(pp+0x000) = (uint32_t)sizeof(fake_proc_params);    // MaximumLength
  *(uint32_t*)(pp+0x004) = (uint32_t)sizeof(fake_proc_params);    // Length
  *(uint32_t*)(pp+0x008) = 1;                                     // Flags: normalized
  // ConsoleHandle: INVALID so CRT doesn't try to init console
  *(void**)(pp+0x010) = (void*)(intptr_t)-1;
  // Standard handles
  *(void**)(pp+0x018) = (void*)(intptr_t)0;     // stdin fd 0
  *(void**)(pp+0x01C) = (void*)(intptr_t)1;     // stdout fd 1
  *(void**)(pp+0x020) = (void*)(intptr_t)2;     // stderr fd 2
  // ImagePathName: empty string
  *(uint16_t*)(pp+0x038) = 0;    // Length
  *(uint16_t*)(pp+0x03a) = 2;    // MaximumLength
  *(void**)(pp+0x03c) = fake_empty_wstr;
  // CommandLine: empty string
  *(uint16_t*)(pp+0x040) = 0;    // Length
  *(uint16_t*)(pp+0x042) = 2;    // MaximumLength
  *(void**)(pp+0x044) = fake_empty_wstr;
  *(void**)(fake_peb+PEB_ProcessParameters) = fake_proc_params;

  // PEB+0x18: ProcessHeap (fake — heap allocs go through shim malloc anyway)
  static uint8_t fake_heap_hdr[0x100] = {};
  *(void**)(fake_peb+PEB_ProcessHeap) = fake_heap_hdr;

  // PEB+0x02: BeingDebugged = 0
  fake_peb[PEB_BeingDebugged] = 0;
}

// Point %fs at this thread's fake TEB.
//
// x86-64 needs one arch_prctl(ARCH_SET_GS).  i386 has no flat-model segment
// base register to set directly: a GDT/LDT descriptor has to be built and the
// selector loaded into the segment register.  glibc already owns %gs for its
// own TLS on i386, so %fs is free — which is exactly where Windows x86 code
// expects the TEB anyway.  The kernel reloads %fs from the per-thread TLS
// entry on every context switch, so the mapping survives scheduling; each
// thread must do this for itself with its own fake_teb.
static bool install_fs_teb(void* teb) {
  struct user_desc desc;
  memset(&desc, 0, sizeof(desc));
  desc.entry_number    = (unsigned int)-1;   // let the kernel pick a free slot
  desc.base_addr       = (unsigned long)(uintptr_t)teb;
  desc.limit           = 0xfffff;
  desc.seg_32bit       = 1;
  desc.contents        = 0;                  // data segment
  desc.read_exec_only  = 0;
  desc.limit_in_pages  = 1;
  desc.seg_not_present = 0;
  desc.useable         = 1;
  if( syscall(SYS_set_thread_area, &desc) != 0 )
    return false;
  uint16_t sel = (uint16_t)((desc.entry_number << 3) | 3); // GDT, RPL 3
  __asm__ volatile("movw %0, %%fs" :: "r"(sel));
  return true;
}

void shim_init_teb(void) {
  // Idempotent: self-pointer at +0x18 is set on first call; skip on re-entry.
  if( *(void**)(fake_teb+TEB_Self) == (void*)fake_teb ) return;
  memset(fake_teb, 0, sizeof(fake_teb));
  *(void**)(fake_teb+TEB_Self) = fake_teb;
  *(void**)(fake_teb+TEB_Peb)  = fake_peb;
  *(uint32_t*)(fake_teb+TEB_ProcessId) = (uint32_t)getpid();
  *(uint32_t*)(fake_teb+TEB_ThreadId)  = (uint32_t)syscall(SYS_gettid);
  // ExceptionList: 0xFFFFFFFF terminates the SEH chain (Windows uses -1, not
  // NULL, as the end-of-list marker; MSVC prologues compare against it).
  *(void**)(fake_teb+TEB_ExceptionList) = (void*)(uintptr_t)-1;
  // ThreadLocalStoragePointer at +0x2C — per-thread allocation so each
  // thread gets its own slot array; registered with a pthread key so it
  // is freed automatically (via free()) when the thread exits
  pthread_once(&g_tls_slots_key_once, tls_slots_key_init);
  void** tls_slots = (void**)calloc(64, sizeof(void*));
  *(void**)(fake_teb+TEB_TlsPointer) = tls_slots;
  pthread_setspecific(g_tls_slots_key, tls_slots);

  // TEB+0x04 StackBase (top/high address) and TEB+0x08 StackLimit (low address).
  // CRT stack-overflow probes and SEH unwind code read these; leaving them zero
  // produces degenerate bounds.  Use pthread_getattr_np to get the real values.
  {
    pthread_attr_t attr;
    if( pthread_getattr_np(pthread_self(), &attr) == 0 ) {
      void* stack_addr = NULL;
      size_t stack_size = 0;
      pthread_attr_getstack(&attr, &stack_addr, &stack_size);
      pthread_attr_destroy(&attr);
      if( stack_addr && stack_size ) {
        *(void**)(fake_teb+TEB_StackLimit) = stack_addr;                        // low
        *(void**)(fake_teb+TEB_StackBase)  = (uint8_t*)stack_addr + stack_size; // high
      }
    }
  }

  *(uint32_t*)(fake_teb+TEB_LastError) = 0;

  if( !install_fs_teb(fake_teb) )
    fprintf(stderr, "[SHIM] set_thread_area failed; fs:[] TEB access unavailable\n");

  // FLS / TLS cleanup is armed via g_tls_slots_key above (pthread_setspecific
  // of tls_slots) — the key's destructor (shim_thread_exit) runs FLS
  // callbacks then frees the slots block on thread exit.
}

// Called at the start of every new thread (including the main thread via
// shim_init) to give each thread its own fake TEB and GS register value.
static void shim_thread_attach(void) {
  shim_init_teb();
}

// ---------------------------------------------------------------------------
// pthread_create interceptor (I8)
// Wrap every thread function so it gets a fake TEB before running.
// ---------------------------------------------------------------------------
struct ShimThreadArgs {
  void* (*fn)(void*);
  void* arg;
};

static void* shim_thread_trampoline(void* p) {
  ShimThreadArgs* ta = (ShimThreadArgs*)p;
  void* (*fn)(void*) = ta->fn;
  void* arg = ta->arg;
  free(ta);
  shim_thread_attach();
  return fn(arg);
}

typedef int (*real_pthread_create_t)(pthread_t*, const pthread_attr_t*, void*(*)(void*), void*);

// Override pthread_create with default visibility so PE-binary threads get TEB.
// dlsym(RTLD_NEXT,...) finds libpthread's real version past our shim.
extern "C" __attribute__((visibility("default")))
int pthread_create(pthread_t* tid, const pthread_attr_t* attr,
                   void* (*fn)(void*), void* arg) {
  static real_pthread_create_t real_fn = NULL;
  real_pthread_create_t p = __atomic_load_n(&real_fn, __ATOMIC_ACQUIRE);
  if( !p ) {
    p = (real_pthread_create_t)dlsym(RTLD_NEXT, "pthread_create");
    __atomic_store_n(&real_fn, p, __ATOMIC_RELEASE);
  }
  if( !p ) return ENOSYS;   // libpthread not reachable via RTLD_NEXT
  ShimThreadArgs* ta = (ShimThreadArgs*)malloc(sizeof(ShimThreadArgs));
  if( !ta ) return ENOMEM;
  ta->fn = fn;
  ta->arg = arg;
  int ret = p(tid, attr, shim_thread_trampoline, ta);
  if( ret!=0 ) free(ta);   // trampoline never runs; we must free
  return ret;
}

// ---------------------------------------------------------------------------
// HANDLE table
// ---------------------------------------------------------------------------
enum HandleKind { H_FREE, H_FILE, H_FIND, H_MODULE,
                   H_MUTEX, H_EVENT, H_SEMAPHORE, H_THREAD };

struct FindCtx {
  int  refcount;     // protected by g_handles_mu; freed when it reaches 0
  DIR* dir;
  char glob[260];
  char dirpath[PATH_MAX];
};

// Sync object structs (defined here so CloseHandle can destroy them)
// refcount is the first field in every sync struct so it can be accessed
// generically via (int*)ptr. Protected by g_handles_mu.
struct MutexObj {
  int             refcount;
  pthread_mutex_t mu;
};
struct EventObj {
  int             refcount;
  pthread_mutex_t mu;
  pthread_cond_t  cv;
  bool            signaled;
  bool            manual_reset;
};
struct SemaphoreObj {
  int   refcount;
  sem_t sem;
};
struct ThreadObj {
  int             refcount;
  pthread_t       tid;
  pthread_mutex_t mu;
  pthread_cond_t  cv;
  int64_t         exit_code;
  bool            done;
  sem_t           suspend_sem;   // posted by ResumeThread; waited by trampoline/signal-handler
  int             suspend_count; // 1 when CREATE_SUSPENDED, bumped by SuspendThread
};

struct HandleSlot {
  HandleKind kind;
  union {
    int      fd;
    FindCtx* find;
    void*    dlhandle;
    void*    ptr;        // H_MUTEX / H_EVENT / H_SEMAPHORE / H_THREAD
  };
};

#define MAX_HANDLES 4096
static HandleSlot g_handles[MAX_HANDLES];
static pthread_mutex_t g_handles_mu = PTHREAD_MUTEX_INITIALIZER;

static void handles_init(void) {
  memset(g_handles, 0, sizeof(g_handles));
  // Slots 0,1,2 = stdin, stdout, stderr
  g_handles[0].kind = H_FILE;
  g_handles[0].fd = 0;
  g_handles[1].kind = H_FILE;
  g_handles[1].fd = 1;
  g_handles[2].kind = H_FILE;
  g_handles[2].fd = 2;
}

// Map HANDLE → slot index (handles are (index+1) as pointer, so 0 maps to fd 0)
static int handle_to_idx(HANDLE h) {
  intptr_t v = (intptr_t)h;
  if( v<0||v>=MAX_HANDLES )
    return -1;
  return (int)v;
}

static HANDLE idx_to_handle(int idx) {
  return (HANDLE)(intptr_t)idx;
}

static HANDLE handle_alloc_file(int fd) {
  pthread_mutex_lock(&g_handles_mu);
  for( int i = 3; i<MAX_HANDLES; ++i ) {
    if( g_handles[i].kind==H_FREE ) {
      g_handles[i].kind = H_FILE;
      g_handles[i].fd = fd;
      pthread_mutex_unlock(&g_handles_mu);
      return idx_to_handle(i);
    }
  }
  pthread_mutex_unlock(&g_handles_mu);
  SET_LAST_ERROR(ERROR_TOO_MANY_OPEN_FILES);
  return INVALID_HANDLE_VALUE;
}

static HANDLE handle_alloc_find(FindCtx* ctx) {
  ctx->refcount = 1;  // caller holds one reference
  pthread_mutex_lock(&g_handles_mu);
  for( int i = 3; i<MAX_HANDLES; ++i ) {
    if( g_handles[i].kind==H_FREE ) {
      g_handles[i].kind = H_FIND;
      g_handles[i].find = ctx;
      pthread_mutex_unlock(&g_handles_mu);
      return idx_to_handle(i);
    }
  }
  pthread_mutex_unlock(&g_handles_mu);
  SET_LAST_ERROR(ERROR_TOO_MANY_OPEN_FILES);
  return INVALID_HANDLE_VALUE;
}

static HANDLE handle_alloc_module(void* dlh) {
  pthread_mutex_lock(&g_handles_mu);
  for( int i = 3; i<MAX_HANDLES; ++i ) {
    if( g_handles[i].kind==H_FREE ) {
      g_handles[i].kind = H_MODULE;
      g_handles[i].dlhandle = dlh;
      pthread_mutex_unlock(&g_handles_mu);
      return idx_to_handle(i);
    }
  }
  pthread_mutex_unlock(&g_handles_mu);
  SET_LAST_ERROR(ERROR_TOO_MANY_OPEN_FILES);
  return INVALID_HANDLE_VALUE;
}

static int get_fd(HANDLE h) {
  int idx = handle_to_idx(h);
  pthread_mutex_lock(&g_handles_mu);
  if( idx<0||g_handles[idx].kind!=H_FILE ) {
    pthread_mutex_unlock(&g_handles_mu);
    SET_LAST_ERROR(ERROR_INVALID_HANDLE);
    return -1;
  }
  int fd = g_handles[idx].fd;
  pthread_mutex_unlock(&g_handles_mu);
  return fd;
}

// Retain a FindCtx for use outside the mutex.  Must be called with
// g_handles_mu held; pairs with release_find_ctx().
static void find_ctx_retain(FindCtx* fc) {
  fc->refcount++;
}

// Release a FindCtx reference.  Safe to call without g_handles_mu.
// Frees when the last reference is dropped.
static void release_find_ctx(FindCtx* fc) {
  pthread_mutex_lock(&g_handles_mu);
  int gone = (--fc->refcount == 0);
  pthread_mutex_unlock(&g_handles_mu);
  if( gone ) {
    if( fc->dir ) closedir(fc->dir);
    free(fc);
  }
}

// Returns a retained FindCtx* for h; caller must call release_find_ctx().
static FindCtx* get_find_ctx(HANDLE h) {
  int idx = handle_to_idx(h);
  pthread_mutex_lock(&g_handles_mu);
  if( idx<0||g_handles[idx].kind!=H_FIND ) {
    pthread_mutex_unlock(&g_handles_mu);
    SET_LAST_ERROR(ERROR_INVALID_HANDLE);
    return NULL;
  }
  FindCtx* fc = g_handles[idx].find;
  find_ctx_retain(fc);
  pthread_mutex_unlock(&g_handles_mu);
  return fc;
}

// ---------------------------------------------------------------------------
// Path translation and utilities
// ---------------------------------------------------------------------------
static void path_join(char* dst, size_t dst_sz, const char* dir, const char* name) {
  size_t a = strnlen(dir, dst_sz-2);
  size_t b = strnlen(name, dst_sz-a-2);
  memcpy(dst, dir, a);
  dst[a] = '/';
  memcpy(dst+a+1, name, b);
  dst[a+1+b] = '\0';
}

static void win_path_to_posix(const char* in, char* out, size_t outsz) {
  if( !in||!out||outsz==0 )
    return;

  // Skip extended-path and device prefixes (\\?\ and \\.\)
  if( in[0]=='\\'&&in[1]=='\\'&&(in[2]=='?'||in[2]=='.')&&in[3]=='\\' ) {
    in += 4;
  }

  // Strip drive letter "X:"
  if( ((in[0]>='A'&&in[0]<='Z')||(in[0]>='a'&&in[0]<='z'))&&in[1]==':' ) {
    in += 2;
  }

  size_t i = 0;
  for(; *in&&i+1<outsz; ++in, ++i ) {
    out[i] = (*in=='\\') ? '/' : *in;
  }
  out[i] = '\0';

  // If empty after stripping, treat as root
  if( out[0]=='\0' ) {
    out[0] = '/';
    out[1] = '\0';
  }
}

// Convert a POSIX path to a Windows-style path (backslashes, C: prefix).
// Windows programs that return paths (GetCurrentDirectory, GetFullPathName, etc.)
// must use this so that rz.exe and similar tools can do wcsrchr(path, '\\').
// Our win_path_to_posix() will convert them back when files are opened.
static void posix_to_win_path(const char* posix, char* win, size_t wsz) {
  if( !posix || !win || wsz < 4 ) return;
  size_t i = 0;
  // Add "C:" prefix for absolute paths so wcsrchr finds a separator.
  if( posix[0] == '/' ) {
    win[i++] = 'C'; win[i++] = ':';
  }
  for( ; *posix && i+1 < wsz; posix++, i++ )
    win[i] = (*posix == '/') ? '\\' : *posix;
  win[i] = '\0';
}

static int wchar_to_utf8(const uint16_t* src, char* dst, size_t dstsz) {
  if( !src||!dst||dstsz==0 )
    return 0;
  size_t i = 0;
  for(; *src&&i+4<dstsz; ++src ) {
    uint32_t cp = *src;
    // Handle surrogate pairs (simplified)
    if( cp>=0xD800&&cp<=0xDBFF&&*(src+1)>=0xDC00&&*(src+1)<=0xDFFF ) {
      cp = 0x10000+((cp-0xD800)<<10)+(*(++src)-0xDC00);
    }
    if( cp<0x80 ) {
      dst[i++] = (char)cp;
    } else if( cp<0x800 ) {
      dst[i++] = (char)(0xC0|(cp>>6));
      dst[i++] = (char)(0x80|(cp&0x3F));
    } else if( cp<0x10000 ) {
      dst[i++] = (char)(0xE0|(cp>>12));
      dst[i++] = (char)(0x80|((cp>>6)&0x3F));
      dst[i++] = (char)(0x80|(cp&0x3F));
    } else {
      dst[i++] = (char)(0xF0|(cp>>18));
      dst[i++] = (char)(0x80|((cp>>12)&0x3F));
      dst[i++] = (char)(0x80|((cp>>6)&0x3F));
      dst[i++] = (char)(0x80|(cp&0x3F));
    }
  }
  dst[i] = '\0';
  return (int)i;
}

static int utf8_to_wchar(const char* src, uint16_t* dst, size_t dstsz) {
  if( !src||!dst||dstsz==0 )
    return 0;
  size_t i = 0;
  const unsigned char* s = (const unsigned char*)src;
  while( *s&&i+1<dstsz ) {
    uint32_t cp;
    if( *s<0x80 ) {
      cp = *s++;
    } else if( (*s&0xE0)==0xC0 ) {
      cp = (*s++&0x1F)<<6;
      cp |= (*s++&0x3F);
    } else if( (*s&0xF0)==0xE0 ) {
      cp = (*s++&0x0F)<<12;
      cp |= (*s++&0x3F)<<6;
      cp |= (*s++&0x3F);
    } else {
      cp = '?';
      s++;
      while( (*s&0xC0)==0x80 )
        s++;
    }
    if( cp<0x10000 ) {
      dst[i++] = (uint16_t)cp;
    } else {
      cp -= 0x10000;
      if( i+2<dstsz ) {
        dst[i++] = (uint16_t)(0xD800|(cp>>10));
        dst[i++] = (uint16_t)(0xDC00|(cp&0x3FF));
      }
    }
  }
  dst[i] = 0;
  return (int)i;
}

// ---------------------------------------------------------------------------
// File-open flag helper (I2)
// ---------------------------------------------------------------------------
static int make_open_flags(DWORD access, DWORD disp) {
  int oflags = 0;
  if( (access&GENERIC_READ)&&(access&GENERIC_WRITE) )
    oflags = O_RDWR;
  else if( access&GENERIC_WRITE )
    oflags = O_WRONLY;
  else
    oflags = O_RDONLY;
  switch( disp ) {
  case CREATE_NEW:
    oflags |= O_CREAT|O_EXCL;
    break;
  case CREATE_ALWAYS:
    oflags |= O_CREAT|O_TRUNC;
    break;
  case OPEN_EXISTING:
    break;
  case OPEN_ALWAYS:
    oflags |= O_CREAT;
    break;
  case TRUNCATE_EXISTING:
    // O_RDONLY|O_TRUNC rejected by Linux; resolve to O_RDWR|O_TRUNC
    oflags = O_RDWR|O_TRUNC;
    break;
  }
  return oflags;
}

// ---------------------------------------------------------------------------
// mmap tracker for VirtualAlloc/VirtualFree
// ---------------------------------------------------------------------------
#include <sys/mman.h>
#define MMAP_TRACK_MAX 4096
struct MmapEntry { void* base; size_t size; };
static MmapEntry g_mmap_table[MMAP_TRACK_MAX];
static pthread_mutex_t g_mmap_mu = PTHREAD_MUTEX_INITIALIZER;

static bool mmap_track_add(void* base, size_t size) {
  pthread_mutex_lock(&g_mmap_mu);
  for( int i = 0; i<MMAP_TRACK_MAX; ++i ) {
    if( !g_mmap_table[i].base ) {
      g_mmap_table[i].base = base;
      g_mmap_table[i].size = size;
      pthread_mutex_unlock(&g_mmap_mu);
      return true;
    }
  }
  pthread_mutex_unlock(&g_mmap_mu);
  return false;
}

static size_t mmap_track_remove(void* base) {
  pthread_mutex_lock(&g_mmap_mu);
  size_t sz = 0;
  for( int i = 0; i<MMAP_TRACK_MAX; ++i ) {
    if( g_mmap_table[i].base==base ) {
      sz = g_mmap_table[i].size;
      g_mmap_table[i].base = NULL;
      g_mmap_table[i].size = 0;
      break;
    }
  }
  pthread_mutex_unlock(&g_mmap_mu);
  return sz;
}

// ---------------------------------------------------------------------------
// Process state
// ---------------------------------------------------------------------------
static char g_cmdline[32768];
static char g_cmdline_w[65536]; // UTF-16LE
static char* g_env_block = NULL;
static uint16_t* g_env_block_w = NULL;
static void* g_image_base = (void*)0x400000;  // default; overridden if needed
static void* g_pe_base    = nullptr;          // PE header (MZ) base, for resource lookup

// TLS slot allocator — used by PE TLS callbacks section and kernel32_Tls* below
static pthread_mutex_t g_tls_alloc_mu = PTHREAD_MUTEX_INITIALIZER;
static uint64_t g_tls_alloc_used = 0;

static inline void** tls_get_slots(void) {
#ifdef __i386__
  void* p;
  __asm__ volatile("movl %%fs:0x2C, %0" : "=r"(p));
  return (void**)p;
#else
  return (void**)pthread_getspecific(g_tls_slots_key);
#endif
}

// Read /proc/self/cmdline into a heap buffer (caller must free).
// Returns byte count (including embedded NULs); 0 and nullptr on error.
static char* read_cmdline_raw(size_t* out_len) {
  int fd = open("/proc/self/cmdline", O_RDONLY);
  if( fd < 0 ) { *out_len = 0; return nullptr; }
  size_t cap = 65536, used = 0;
  char* buf = (char*)malloc(cap + 1);
  if( !buf ) { close(fd); *out_len = 0; return nullptr; }
  while( true ) {
    ssize_t n = read(fd, buf + used, cap - used);
    if( n <= 0 ) break;
    used += (size_t)n;
    if( used == cap ) {
      cap *= 2;
      char* tmp = (char*)realloc(buf, cap + 1);
      if( !tmp ) { free(buf); close(fd); *out_len = 0; return nullptr; }
      buf = tmp;
    }
  }
  close(fd);
  buf[used] = '\0';
  *out_len = used;
  return buf;
}

// WINAPI_SHIM_CMDLINE lets a loader (e.g. ./load <pe.so> ...) hand the
// shim an explicit Windows-style command line, used verbatim as the
// source for GetCommandLineA/W (and as the basis for argv via simple
// quote-aware splitting).  When unset, /proc/self/cmdline is used.
static const char* shim_cmdline_override(void) {
  const char* s = getenv("WINAPI_SHIM_CMDLINE");
  return (s && *s) ? s : nullptr;
}

static void rebuild_cmdline(void) {
  size_t out = 0;
  if( const char* ovr = shim_cmdline_override() ) {
    size_t lim = sizeof(g_cmdline) - 1;
    size_t n   = strlen(ovr);
    if( n > lim ) n = lim;
    memcpy(g_cmdline, ovr, n);
    out = n;
  } else {
    size_t raw_len;
    char* raw = read_cmdline_raw(&raw_len);
    if( !raw || raw_len == 0 ) { g_cmdline[0] = '\0'; free(raw); return; }
    // Convert NUL-separated argv to space-separated cmdline with quoting
    const char* p = raw, *end = raw + raw_len;
    int first = 1;
    while( p<end && out+4<sizeof(g_cmdline) ) {
      if( !first ) g_cmdline[out++] = ' ';
      first = 0;
      int needs_quote = (strchr(p, ' ')||strchr(p, '\t')||*p=='\0');
      if( needs_quote ) g_cmdline[out++] = '"';
      while( *p && p<end && out+2<sizeof(g_cmdline) ) g_cmdline[out++] = *p++;
      if( needs_quote ) g_cmdline[out++] = '"';
      p++;
    }
    free(raw);
  }
  g_cmdline[out] = '\0';
  utf8_to_wchar(g_cmdline, (uint16_t*)g_cmdline_w, sizeof(g_cmdline_w)/2);
}

static void build_env_block(void) {
  // Build Windows-style env block: KEY=VAL\0KEY=VAL\0\0
  size_t total = 0;
  for( char** e = environ; *e; ++e )
    total += strlen(*e)+1;
  total += 1; // final \0\0
  g_env_block = (char*)malloc(total);
  if( !g_env_block )
    return;
  char* p = g_env_block;
  for( char** e = environ; *e; ++e ) {
    size_t l = strlen(*e);
    memcpy(p, *e, l+1);
    p += l+1;
  }
  *p = '\0';

  // Build UTF-16LE version
  size_t wsize = total*2;
  g_env_block_w = (uint16_t*)malloc(wsize);
  if( !g_env_block_w ) {
    free(g_env_block);
    g_env_block = NULL;
    return;
  }
  uint16_t* wp = g_env_block_w;
  for( char** e = environ; *e; ++e ) {
    size_t remaining = wsize/2 - (size_t)(wp - g_env_block_w);
    int len = utf8_to_wchar(*e, wp, remaining);
    wp += len+1;
  }
  *wp = 0;
}

// ---------------------------------------------------------------------------
// msvcrt CRT state (used by msvcrt_ shims below)
// ---------------------------------------------------------------------------
static int    g_main_argc = 0;
static char** g_main_argv = nullptr;

// Fake Windows FILE IOB array: 3 entries × 32 bytes each.
// Layout mirrors Windows x86 _iobuf:
//   _ptr[4]@0 _cnt[4]@4 _base[4]@8 _flag[4]@0x0C
//   _file[4]@0x10 _charbuf[4]@0x14 _bufsiz[4]@0x18 _tmpfname[4]@0x1C
#define WIN_IOB_STRIDE    32
#define WIN_IOB_FLAG_OFF  0x0C
#define WIN_IOB_FILE_OFF  0x10
static uint8_t g_fake_iob[3*WIN_IOB_STRIDE];

// Split a Windows-style command-line string into argv with simple
// quote-aware tokenisation (whitespace separates, double-quotes group).
// Returns malloc'd argv (NULL-terminated); each entry is strdup'd.
static char** split_cmdline(const char* s, int* out_argc) {
  size_t cap = 16;
  char** out = (char**)malloc(cap * sizeof(char*));
  if( !out ) { *out_argc = 0; return nullptr; }
  int ac = 0;
  std::string tok;
  bool in_quote = false;
  auto flush = [&]() {
    if( tok.empty() && !in_quote ) return;
    if( (size_t)ac+1 >= cap ) {
      cap *= 2;
      char** n = (char**)realloc(out, cap*sizeof(char*));
      if( !n ) return;
      out = n;
    }
    out[ac++] = strdup(tok.c_str());
    tok.clear();
  };
  for( const char* p = s; *p; ++p ) {
    char c = *p;
    if( c == '"' ) { in_quote = !in_quote; continue; }
    if( !in_quote && (c==' '||c=='\t') ) { flush(); continue; }
    tok.push_back(c);
  }
  flush();
  out[ac] = nullptr;
  *out_argc = ac;
  return out;
}

static void build_argv(void) {
  if( const char* ovr = shim_cmdline_override() ) {
    int argc = 0;
    char** argv = split_cmdline(ovr, &argc);
    if( !argv ) return;
    g_main_argc = argc;
    g_main_argv = argv;
    return;
  }
  size_t n;
  char* raw = read_cmdline_raw(&n);
  if( !raw || n == 0 ) { free(raw); return; }
  int argc = 0;
  for( size_t i = 0; i < n; i++ )
    if( i==0 || (raw[i-1]=='\0' && raw[i]!='\0') ) argc++;
  char** argv = (char**)malloc((size_t)(argc+1)*sizeof(char*));
  if( !argv ) { free(raw); return; }
  int ai = 0;
  const char* p = raw, *end = raw+n;
  while( p<end && ai<argc ) {
    argv[ai] = strdup(p);
    if( !argv[ai] ) {
      for( int j = 0; j < ai; ++j ) free(argv[j]);
      free(argv); free(raw); return;
    }
    ++ai; p += strlen(p)+1;
  }
  argv[ai] = nullptr;
  free(raw);
  g_main_argc = argc;
  g_main_argv = argv;
}

// Loader entry point: re-derive g_cmdline / g_main_argv after the caller
// has had a chance to set WINAPI_SHIM_CMDLINE.  Needed because the
// shim's normal init runs as a constructor (before main of the loader
// process), so anything main() puts in the environment is too late
// otherwise.
extern "C" __attribute__((visibility("default")))
void shim_reload_cmdline(void) {
  if( g_main_argv ) {
    for( int i = 0; i < g_main_argc; i++ ) free(g_main_argv[i]);
    free(g_main_argv);
    g_main_argv = nullptr;
    g_main_argc = 0;
  }
  rebuild_cmdline();
  build_argv();
}

static void init_fake_iob(void) {
  memset(g_fake_iob, 0, sizeof(g_fake_iob));
  for( int i = 0; i < 3; ++i ) {
    // stdin _IOREAD=1, stdout/stderr _IOWRT=2
    *(int*)(g_fake_iob+i*WIN_IOB_STRIDE+WIN_IOB_FLAG_OFF) = (i==0) ? 1 : 2;
    *(int*)(g_fake_iob+i*WIN_IOB_STRIDE+WIN_IOB_FILE_OFF) = i;
  }
}

// ---------------------------------------------------------------------------
// Signal / crash handler — all helpers must be async-signal-safe (POSIX)
// ---------------------------------------------------------------------------
static void* g_unhandled_filter = NULL;

// AS-safe write helpers — use raw syscall to avoid glibc warn_unused_result
#define crash_sys_write(s, n) syscall(SYS_write, STDERR_FILENO, (s), (size_t)(n))

static void crash_write_lit(const char* s) {
  size_t n = 0;
  while( s[n] ) n++;
  crash_sys_write(s, n);
}

static void crash_write_int(int v) {
  char buf[12];
  int neg = (v<0);
  if( neg ) v = -v;
  int i = sizeof(buf)-1;
  buf[i--] = '\n';
  do { buf[i--] = '0'+(v%10); v /= 10; } while( v );
  if( neg ) buf[i--] = '-';
  crash_sys_write(buf+i+1, sizeof(buf)-i-1);
}

static void crash_write_hex32(uint32_t v) {
  static const char hx[] = "0123456789abcdef";
  char buf[9];
  for( int i = 7; i>=0; i-- ) { buf[i] = hx[v&0xf]; v >>= 4; }
  buf[8] = ' ';
  crash_sys_write(buf, 9);
}

// Defined in shim32_kernel32_except.hpp.  Walks the fs:[0] SEH chain the PE
// code built with its inline `push handler; push fs:[0]; mov fs:[0],esp`
// prologues, exactly as Windows' KiUserExceptionDispatcher would.  Returns
// true when a handler asked to continue execution, in which case the
// (possibly handler-modified) register state has been written back into the
// ucontext and the signal handler must simply return to resume.
static bool seh_dispatch_from_signal(int sig, siginfo_t* si, ucontext_t* uc);

static void crash_handler(int sig, siginfo_t* si, void* ctx) {
  ucontext_t* uc = (ucontext_t*)ctx;
  // Give the PE image's own __try/__except frames the first chance, the way
  // Windows does — this is the whole point of having a writable fs:[0].
  if( uc && seh_dispatch_from_signal(sig, si, uc) )
    return;

  crash_write_lit("CRASH: signal ");
  crash_write_int(sig);
  crash_write_lit("CRASH: fault addr ");
  crash_write_hex32((uint32_t)(uintptr_t)(si ? si->si_addr : NULL));
  crash_write_lit("\n");
#ifdef __i386__
  if( uc ) {
    mcontext_t* mc = &uc->uc_mcontext;
    crash_write_lit("EIP="); crash_write_hex32((uint32_t)mc->gregs[REG_EIP]);
    crash_write_lit("ESP="); crash_write_hex32((uint32_t)mc->gregs[REG_ESP]);
    crash_write_lit("EBP="); crash_write_hex32((uint32_t)mc->gregs[REG_EBP]);
    crash_write_lit("EFL="); crash_write_hex32((uint32_t)mc->gregs[REG_EFL]);
    crash_write_lit("\n");
    crash_write_lit("EAX="); crash_write_hex32((uint32_t)mc->gregs[REG_EAX]);
    crash_write_lit("EBX="); crash_write_hex32((uint32_t)mc->gregs[REG_EBX]);
    crash_write_lit("ECX="); crash_write_hex32((uint32_t)mc->gregs[REG_ECX]);
    crash_write_lit("EDX="); crash_write_hex32((uint32_t)mc->gregs[REG_EDX]);
    crash_write_lit("\n");
    crash_write_lit("ESI="); crash_write_hex32((uint32_t)mc->gregs[REG_ESI]);
    crash_write_lit("EDI="); crash_write_hex32((uint32_t)mc->gregs[REG_EDI]);
    crash_write_lit("\n");
  }
#endif
#ifdef __GLIBC__
  {
    void* bt[40];
    int n = backtrace(bt, 40);
    crash_write_lit("BACKTRACE:\n");
    backtrace_symbols_fd(bt, n, STDERR_FILENO);
  }
#endif
  _exit(sig+128);
}

// forward declaration — defined in shim32_kernel32_sync.hpp (included below)
static void suspend_signal_handler(int);

static void install_signal_handlers(void) {
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_sigaction = crash_handler;
  sa.sa_flags = SA_SIGINFO;
  sigaction(SIGSEGV, &sa, NULL);
  sigaction(SIGILL,  &sa, NULL);
  sigaction(SIGFPE,  &sa, NULL);
  sigaction(SIGBUS,  &sa, NULL);
  sigaction(SIGABRT, &sa, NULL);
  // Install SIGUSR1 handler process-wide so all threads (including freshly
  // created ones) handle SuspendThread signals before the trampoline runs.
  struct sigaction sa2 = {};
  sa2.sa_handler = suspend_signal_handler;
  sigemptyset(&sa2.sa_mask);
  sa2.sa_flags = 0;  // no SA_RESTART so the signal can interrupt sem_wait
  sigaction(SIGUSR1, &sa2, NULL);
}

// ---------------------------------------------------------------------------
// Image base discovery (B13, R26)
// ---------------------------------------------------------------------------
// Walked once per phdr entry: tracks the lowest VA of the main executable
// (empty dlpi_name) for g_image_base, and the lowest VA of *any* segment
// whose first two bytes are "MZ" for g_pe_base.  In the ET_EXEC pe2elf
// case both are the same converted PE; in the --so / load case the main
// exe is `load` (no MZ) and the PE lives in a separately-mapped .so, so
// the two have to be discovered independently.
static int find_main_exe_base(struct dl_phdr_info* info, size_t /*sz*/, void* data) {
  bool is_main = !(info->dlpi_name && info->dlpi_name[0]);
  uintptr_t lowest = (uintptr_t)-1;
  for( int i = 0; i<info->dlpi_phnum; ++i ) {
    if( info->dlpi_phdr[i].p_type==PT_LOAD ) {
      uintptr_t va = (uintptr_t)info->dlpi_addr + info->dlpi_phdr[i].p_vaddr;
      if( va<lowest ) lowest = va;
      if( !g_pe_base && info->dlpi_phdr[i].p_filesz >= 64 ) {
        const uint8_t* seg = (const uint8_t*)va;
        if( seg[0]=='M' && seg[1]=='Z' )
          g_pe_base = (void*)va;
      }
    }
  }
  if( is_main && lowest!=(uintptr_t)-1 )
    *(void**)data = (void*)lowest;
  return 0; // keep iterating so non-main modules are scanned for MZ too
}

static void discover_image_base(void) {
  void* base = NULL;
  dl_iterate_phdr(find_main_exe_base, &base);
  // For --so loaders the main exe has no MZ; fall back to the PE base we
  // found in some other loaded module so TLS callbacks and resource
  // lookups get a real PE image rather than the loader's binary.
  // If the main exe has an MZ at `base` we keep using that; otherwise
  // (the --so loader case) prefer the PE-bearing module we discovered.
  if( base && ((const uint8_t*)base)[0]=='M' && ((const uint8_t*)base)[1]=='Z' ) {
    g_image_base = base;
  } else if( g_pe_base ) {
    g_image_base = g_pe_base;
  } else if( base ) {
    g_image_base = base;
  }
  // Update PEB ImageBaseAddress with whatever we settled on.
  *(void**)(fake_peb+PEB_ImageBaseAddress) = g_image_base;
}

// ---------------------------------------------------------------------------
// PE TLS directory — static TLS + callbacks
static void tls_static_init_thread(void);
void run_tls_callbacks(uint32_t reason);
// ---------------------------------------------------------------------------
static uint32_t*  g_tls_callbacks_va = nullptr; // array of 32-bit callback VAs
static uint32_t*  g_tls_index_addr   = nullptr; // *AddressOfIndex: DWORD TLS slot index
static uintptr_t  g_tls_template_va  = 0;       // StartAddressOfRawData
static size_t     g_tls_template_sz  = 0;       // EndAddressOfRawData - Start
static size_t     g_tls_zero_fill    = 0;        // SizeOfZeroFill
static size_t     g_tls_align        = 16;       // required alignment for static-TLS block
// g_tls_static_idx declared earlier (needed by tls_slots_dtor before this point)

// Layout of the ShimTlsInfo struct embedded in pe2elf32's startup trampoline.
// Must match the push32 sequence in elf_build32.hpp build_trampoline() —
// 6 x uint32 = 24 bytes, at trampoline+40.
struct ShimTlsInfo {
  uint32_t template_va;   // StartAddressOfRawData (0 if no TLS)
  uint32_t template_sz;   // EndAddressOfRawData - Start
  uint32_t zero_fill;     // SizeOfZeroFill
  uint32_t align_chars;   // Characteristics
  uint32_t index_va;      // AddressOfIndex (0 if none)
  uint32_t callbacks_va;  // AddressOfCallBacks (0 if none)
};
static_assert(sizeof(ShimTlsInfo) == 24, "ShimTlsInfo must match the trampoline layout");

// Called from pe2elf32's startup thunk (push &info; call [slot]) before
// PE_ENTRY.  Declared stdcall so the callee pops the argument and the
// trampoline needs no `add esp,4`.  Registers TLS directory info, allocates
// the static TLS slot, initialises main-thread TLS, and fires
// DLL_PROCESS_ATTACH callbacks.
extern "C" __attribute__((visibility("default"), stdcall))
void shim_register_tls(const ShimTlsInfo* info) {
  if( !info ) return;
  // When a loader (./load <pe.so>) is in play the PE wasn't yet mapped
  // when the shim's constructor ran, so g_image_base was set to the
  // loader's binary. Re-discover now that the PE is loaded, otherwise
  // hInstance-driven lookups (LoadString from the PE's resource table,
  // FindResource, …) all fall back to the wrong module.
  if( !g_pe_base || g_image_base != g_pe_base )
    discover_image_base();
  g_tls_template_va  = (uintptr_t)info->template_va;
  g_tls_template_sz  = (size_t)info->template_sz;
  g_tls_zero_fill    = (size_t)info->zero_fill;
  g_tls_index_addr   = info->index_va  ? (uint32_t*)(uintptr_t)info->index_va  : nullptr;
  g_tls_callbacks_va = info->callbacks_va ? (uint32_t*)(uintptr_t)info->callbacks_va : nullptr;
  // Characteristics bits 20-23 encode alignment as 2^(N-1) bytes (N=1..15).
  // glibc malloc/calloc guarantee 8-byte alignment on i386; ask for 16 as a
  // floor (SSE locals in TLS data are common) and fall back to
  // posix_memalign when more is requested.
  {
    uint32_t n = (uint32_t)(info->align_chars >> 20) & 0xF;
    g_tls_align = (n >= 1) ? ((size_t)1 << (n - 1)) : 1;
    if( g_tls_align < 16 ) g_tls_align = 16;
  }
  log_always("[SHIM] shim_register_tls: template=0x%08x sz=%zu callbacks=0x%08x\n",
             (unsigned)g_tls_template_va, g_tls_template_sz,
             (unsigned)info->callbacks_va);
  if( g_tls_index_addr ) {
    pthread_mutex_lock(&g_tls_alloc_mu);
    for( DWORD i = 0; i < 64; i++ ) {
      if( !(g_tls_alloc_used & (1ULL<<i)) ) {
        g_tls_alloc_used |= (1ULL<<i);
        g_tls_static_idx = i;
        break;
      }
    }
    pthread_mutex_unlock(&g_tls_alloc_mu);
    if( g_tls_static_idx == 0xFFFFFFFFu ) {
      fprintf(stderr, "[SHIM] shim_register_tls: no free TLS slot; static TLS disabled\n");
    } else {
      *g_tls_index_addr = g_tls_static_idx;
      log_always("[SHIM] static TLS: slot=%u\n", g_tls_static_idx);
      tls_static_init_thread();
    }
  }
  run_tls_callbacks(1);   // DLL_PROCESS_ATTACH
}

typedef void (__attribute__((stdcall)) *tls_callback_fn)(void*, uint32_t, void*);

void run_tls_callbacks(uint32_t reason) {
  uint32_t* cbs = g_tls_callbacks_va;
  log_always("[SHIM] run_tls_callbacks(reason=%u) cbs=%p\n", reason, (void*)cbs);
  if( !cbs ) return;
  for( ; *cbs; cbs++ ) {
    log_always("[SHIM]   calling tls_cb %p\n", (void*)(uintptr_t)(*cbs));
    tls_callback_fn fn = (tls_callback_fn)(uintptr_t)(*cbs);
    fn(g_image_base, reason, nullptr);
    log_always("[SHIM]   tls_cb done\n");
  }
}

// Initialize the static TLS data block for the calling thread.
// The Windows PE loader does this for every thread (main + created) before
// the thread's user function runs.  We replicate it here.
void tls_static_init_thread(void) {
  if( g_tls_static_idx == 0xFFFFFFFFu ) return;
  void** slots = tls_get_slots();
  if( !slots ) return;
  if( slots[g_tls_static_idx] ) return;  // already initialized
  size_t sz = g_tls_template_sz + g_tls_zero_fill;
  if( sz == 0 ) sz = 64;
  void* buf = nullptr;
  if( g_tls_align > 16 ) {
    if( posix_memalign(&buf, g_tls_align, sz) != 0 ) buf = nullptr;
    if( buf ) memset(buf, 0, sz);
  } else {
    buf = calloc(1, sz); // calloc zeros; zero_fill portion requires no explicit memset
  }
  if( !buf ) return;
  if( g_tls_template_va && g_tls_template_sz )
    memcpy(buf, (void*)g_tls_template_va, g_tls_template_sz);
  slots[g_tls_static_idx] = buf;
  log_always("[SHIM] tls_static_init_thread: slot=%u buf=%p sz=%zu\n",
             g_tls_static_idx, buf, sz);
}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
__attribute__((destructor)) static void shim_fini(void) {
  run_tls_callbacks(0);  // DLL_PROCESS_DETACH
}

__attribute__((constructor)) static void shim_init(void) {
  setlocale(LC_ALL, "");
  init_fake_peb();
  discover_image_base();
  handles_init();
  shim_init_teb();
  log_init();
  rebuild_cmdline();
  build_env_block();
  build_argv();
  init_fake_iob();
  install_signal_handlers();
  // TLS registration, slot allocation, and DLL_PROCESS_ATTACH callbacks are
  // handled by shim_register_tls(), called from the pe2elf startup thunk.
}

#pragma GCC visibility pop

// ===========================================================================
// WinAPI implementations — all use EXPORT (= visibility("default") + stdcall),
// except the msvcrt CRT surface and variadics, which use EXPORT_CDECL.
// ===========================================================================

// ---------------------------------------------------------------------------
// 7.1 Process / Identity
#include "shim32_kernel32_proc.hpp"

// ---------------------------------------------------------------------------
// 7.2 Error State, 7.10 Time / Performance, 7.14 Pointer Encoding
// ---------------------------------------------------------------------------
#include "shim32_kernel32_smallstubs.hpp"

// ---------------------------------------------------------------------------
// 7.3 Memory
// ---------------------------------------------------------------------------
#include "shim32_kernel32_mem.hpp"

// ---------------------------------------------------------------------------
// 7.4 File I/O + 7.5 File Times + 7.6 Directory / File Search
// ---------------------------------------------------------------------------
#include "shim32_kernel32_file.hpp"


// ---------------------------------------------------------------------------
// 7.7 Console I/O
#include "shim32_kernel32_console.hpp"

// ---------------------------------------------------------------------------
// 7.8 Module / Library
#include "shim32_kernel32_module.hpp"

// ---------------------------------------------------------------------------
// 7.9 Startup / Command Line / Environment
#include "shim32_kernel32_startup.hpp"

// 7.10 covered in shim32_kernel32_smallstubs.hpp (included up at 7.2).

// ---------------------------------------------------------------------------
// 7.11 Synchronization
// ---------------------------------------------------------------------------
#include "shim32_kernel32_critsec.hpp"

// ---------------------------------------------------------------------------
// 7.12 InitializeSListHead / other sync stubs
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// 7.13 String / Code Page
#include "shim32_kernel32_string.hpp"

// 7.14 covered in shim32_kernel32_smallstubs.hpp (included up at 7.2).

// ---------------------------------------------------------------------------
// 7.15 Exception / SEH stubs
// ---------------------------------------------------------------------------
#include "shim32_kernel32_except.hpp"

// ---------------------------------------------------------------------------
// Misc stubs (GetStringTypeA, LCMapStringA, Sleep)
// ---------------------------------------------------------------------------
#include "shim32_kernel32_miscstubs.hpp"

// ---------------------------------------------------------------------------
// A-variant file/directory functions
// ---------------------------------------------------------------------------
#include "shim32_kernel32_file_a.hpp"

// ---------------------------------------------------------------------------
// SetFilePointer (non-Ex), SetFileTime, SetEndOfFile, FILETIME ↔ DOS
// ---------------------------------------------------------------------------
#include "shim32_kernel32_filetime.hpp"

// ---------------------------------------------------------------------------
// FLS (Fiber Local Storage)
// ---------------------------------------------------------------------------
#include "shim32_kernel32_fls.hpp"

// ---------------------------------------------------------------------------
// Locale / GetLocaleInfoA, FormatMessageA
// ---------------------------------------------------------------------------
#include "shim32_kernel32_locale.hpp"

// ---------------------------------------------------------------------------
// Console misc
// ---------------------------------------------------------------------------
#include "shim32_kernel32_console_misc.hpp"
// ---------------------------------------------------------------------------
// Additional KERNEL32 functions
// ---------------------------------------------------------------------------
#include "shim32_kernel32_misc.hpp"

#include "shim32_kernel32_sync.hpp"

// ---------------------------------------------------------------------------
// Global memory, file attributes, FILETIME→SYSTEMTIME, system info
// ---------------------------------------------------------------------------
#include "shim32_kernel32_sysinfo.hpp"

// ---------------------------------------------------------------------------
// Thread pseudo-handle, suspend/resume, context, affinity, duplication,
// TryEnterCriticalSection, WaitForMultipleObjects
// ---------------------------------------------------------------------------
#include "shim32_kernel32_thread.hpp"

// ---------------------------------------------------------------------------
// Console extras
// ---------------------------------------------------------------------------
#include "shim32_kernel32_console_extras.hpp"

// ---------------------------------------------------------------------------
// Vectored Exception Handler
// ---------------------------------------------------------------------------
#include "shim32_kernel32_veh.hpp"

// ---------------------------------------------------------------------------
// kernel32 tail — Temp, SetCurrentDirectoryW, time/locale conversion,
// memory status, shell32/shlwapi/winmm, SetConsoleCtrlHandler, file ops,
// system info, paths, string ops, sync wrappers, and stubs
// ---------------------------------------------------------------------------
#include "shim32_kernel32_tail.hpp"

// ---------------------------------------------------------------------------
// advapi32
// ---------------------------------------------------------------------------
#include "shim32_advapi32.hpp"

// ---------------------------------------------------------------------------
// shell32
// ---------------------------------------------------------------------------
#include "shim32_shell32.hpp"

// ---------------------------------------------------------------------------
// user32
// ---------------------------------------------------------------------------
#include "shim32_user32.hpp"

// ---------------------------------------------------------------------------
// kernel32 A-variant wrappers
// ---------------------------------------------------------------------------
#include "shim32_kernel32_a.hpp"

#include "shim32_msvcrt.hpp"

// ---------------------------------------------------------------------------
// ole32 / oleaut32 / powrprof
// ---------------------------------------------------------------------------
#include "shim32_misc_dlls.hpp"
