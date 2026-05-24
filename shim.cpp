// winapi_shim.cpp — WinAPI shim for PE→ELF converted binaries
// Exports Windows API functions using __attribute__((ms_abi)) (Windows x64 ABI).
// All functions callable from MSVC-compiled PE code.

#include "shim_types.h"

#include <asm/prctl.h>
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
static __thread uint32_t tls_last_error = 0;
static __thread uint8_t fake_teb[0x2000];  // forward; full init in shim_init_teb()

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

// Mirror last error to TEB+0x68 as inlined MSVC code reads gs:[0x68] (B16/R29)
#define SET_LAST_ERROR(e) do { \
  tls_last_error = (e); \
  *(uint32_t*)(fake_teb+0x68) = (e); \
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

static void init_fake_peb(void) {
  memset(fake_peb, 0, sizeof(fake_peb));

  // PEB+0x10: ImageBaseAddress
  *(void**)(fake_peb+0x10) = (void*)0x400000;

  // PEB+0x18: Ldr -> PEB_LDR_DATA
  // Layout: +0x00 Length, +0x04 Initialized, +0x10/0x18 InLoadOrder list,
  //         +0x20/0x28 InMemoryOrder, +0x30/0x38 InInitializationOrder
  memset(fake_ldr_data, 0, sizeof(fake_ldr_data));
  *(uint32_t*)(fake_ldr_data+0x00) = (uint32_t)sizeof(fake_ldr_data);
  *(uint8_t*)(fake_ldr_data+0x04) = 1;    // Initialized = TRUE
  // Self-referencing empty lists (Flink = Blink = head)
  *(void**)(fake_ldr_data+0x10) = fake_ldr_data+0x10;
  *(void**)(fake_ldr_data+0x18) = fake_ldr_data+0x10;
  *(void**)(fake_ldr_data+0x20) = fake_ldr_data+0x20;
  *(void**)(fake_ldr_data+0x28) = fake_ldr_data+0x20;
  *(void**)(fake_ldr_data+0x30) = fake_ldr_data+0x30;
  *(void**)(fake_ldr_data+0x38) = fake_ldr_data+0x30;
  *(void**)(fake_peb+0x18) = fake_ldr_data;

  // PEB+0x20: ProcessParameters -> RTL_USER_PROCESS_PARAMETERS (64-bit layout)
  // +0x000 MaximumLength   ULONG
  // +0x004 Length          ULONG
  // +0x008 Flags           ULONG  (1 = normalized)
  // +0x018 ConsoleHandle   HANDLE
  // +0x028 StandardInput   HANDLE
  // +0x030 StandardOutput  HANDLE
  // +0x038 StandardError   HANDLE
  // +0x040 CurrentDirectory.DosPath UNICODE_STRING (len,maxlen,[pad4],buf)
  // +0x050 CurrentDirectory.Handle  HANDLE
  // +0x058 DllPath         UNICODE_STRING (+0x058 len, +0x05a maxlen, +0x060 buf)
  // +0x068 ImagePathName   UNICODE_STRING (+0x068 len, +0x06a maxlen, +0x070 buf)
  // +0x078 CommandLine     UNICODE_STRING (+0x078 len, +0x07a maxlen, +0x080 buf)
  // +0x088 Environment     PVOID
  memset(fake_proc_params, 0, sizeof(fake_proc_params));
  uint8_t* pp = fake_proc_params;
  *(uint32_t*)(pp+0x000) = (uint32_t)sizeof(fake_proc_params);    // MaximumLength
  *(uint32_t*)(pp+0x004) = (uint32_t)sizeof(fake_proc_params);    // Length
  *(uint32_t*)(pp+0x008) = 1;                                     // Flags: normalized
  // ConsoleHandle: INVALID so CRT doesn't try to init console
  *(void**)(pp+0x018) = (void*)(intptr_t)-1;
  // Standard handles
  *(void**)(pp+0x028) = (void*)(intptr_t)0;     // stdin fd 0
  *(void**)(pp+0x030) = (void*)(intptr_t)1;     // stdout fd 1
  *(void**)(pp+0x038) = (void*)(intptr_t)2;     // stderr fd 2
  // ImagePathName: empty string
  *(uint16_t*)(pp+0x068) = 0;    // Length
  *(uint16_t*)(pp+0x06a) = 2;    // MaximumLength
  *(void**)(pp+0x070) = fake_empty_wstr;
  // CommandLine: empty string
  *(uint16_t*)(pp+0x078) = 0;    // Length
  *(uint16_t*)(pp+0x07a) = 2;    // MaximumLength
  *(void**)(pp+0x080) = fake_empty_wstr;
  *(void**)(fake_peb+0x20) = fake_proc_params;

  // PEB+0x30: ProcessHeap (fake — heap allocs go through shim malloc anyway)
  static uint8_t fake_heap_hdr[0x100] = {};
  *(void**)(fake_peb+0x30) = fake_heap_hdr;

  // PEB+0x02: BeingDebugged = 0
  fake_peb[2] = 0;
}

void shim_init_teb(void) {
  // Idempotent: self-pointer at +0x30 is set on first call; skip on re-entry.
  if( *(void**)(fake_teb+0x30) == (void*)fake_teb ) return;
  memset(fake_teb, 0, sizeof(fake_teb));
  // TEB self-pointer at +0x30
  *(void**)(fake_teb+0x30) = fake_teb;
  // PEB pointer at +0x60
  *(void**)(fake_teb+0x60) = fake_peb;
  // ProcessId at +0x40, ThreadId at +0x48
  *(uint32_t*)(fake_teb+0x40) = (uint32_t)getpid();
  *(uint32_t*)(fake_teb+0x48) = (uint32_t)syscall(SYS_gettid);
  // ThreadLocalStoragePointer at +0x58 — per-thread allocation so each
  // thread gets its own slot array; registered with a pthread key so it
  // is freed automatically (via free()) when the thread exits
  pthread_once(&g_tls_slots_key_once, tls_slots_key_init);
  void** tls_slots = (void**)calloc(64, sizeof(void*));
  *(void**)(fake_teb+0x58) = tls_slots;
  pthread_setspecific(g_tls_slots_key, tls_slots);

  // TEB+0x08 StackBase (top/high address) and TEB+0x10 StackLimit (low address).
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
        *(void**)(fake_teb+0x10) = stack_addr;                          // StackLimit (low)
        *(void**)(fake_teb+0x08) = (uint8_t*)stack_addr + stack_size;  // StackBase  (high)
      }
    }
  }

  // LastErrorValue at +0x68 (B16/R29)
  *(uint32_t*)(fake_teb+0x68) = 0;

  // Install segment register / reserved register to point at fake_teb so
  // inlined __readgsqword / __readgsword accesses work as Windows expects.
#ifdef __x86_64__
  syscall(SYS_arch_prctl, ARCH_SET_GS, (unsigned long)fake_teb);
#elif defined(__aarch64__)
  // On AArch64, x18 is the "platform register" reserved for OS/runtime use.
  // MSVC PE code accessing TEB via NtCurrentTeb() would need a separate port;
  // for now, stash the pointer in x18 so future __asm__ helpers can load it.
  __asm__ volatile ("mov x18, %0" :: "r"(fake_teb) : "x18");
#endif
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
#ifdef __x86_64__
  void* p;
  __asm__ volatile("movq %%gs:0x58, %0" : "=r"(p));
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

static void rebuild_cmdline(void) {
  size_t raw_len;
  char* raw = read_cmdline_raw(&raw_len);
  if( !raw || raw_len == 0 ) { g_cmdline[0] = '\0'; free(raw); return; }

  // Convert NUL-separated argv to space-separated cmdline with quoting
  size_t out = 0;
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
  g_cmdline[out] = '\0';
  free(raw);
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

// Fake Windows FILE IOB array: 3 entries × 48 bytes each.
// Layout mirrors Windows x64 _iobuf: ptr[8] cnt[4] pad[4] base[8]
//   flag[4] file[4] charbuf[4] bufsiz[4] tmpfname[8]
static uint8_t g_fake_iob[144];

static void build_argv(void) {
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

static void init_fake_iob(void) {
  memset(g_fake_iob, 0, sizeof(g_fake_iob));
  // stdin  (_IOREAD=1, fd=0)
  *(int*)(g_fake_iob+0*48+24) = 1;  *(int*)(g_fake_iob+0*48+28) = 0;
  // stdout (_IOWRT=2, fd=1)
  *(int*)(g_fake_iob+1*48+24) = 2;  *(int*)(g_fake_iob+1*48+28) = 1;
  // stderr (_IOWRT=2, fd=2)
  *(int*)(g_fake_iob+2*48+24) = 2;  *(int*)(g_fake_iob+2*48+28) = 2;
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

static void crash_write_hex(uint64_t v) {
  static const char hx[] = "0123456789abcdef";
  char buf[17];
  for( int i = 15; i>=0; i-- ) { buf[i] = hx[v&0xf]; v >>= 4; }
  buf[16] = ' ';
  crash_sys_write(buf, 17);
}

static void crash_handler(int sig, siginfo_t* si, void* ctx) {
  crash_write_lit("CRASH: signal ");
  crash_write_int(sig);
  crash_write_lit("CRASH: fault addr ");
  crash_write_hex((uint64_t)(uintptr_t)(si ? si->si_addr : NULL));
  crash_write_lit("\n");
#ifdef __x86_64__
  ucontext_t* uc = (ucontext_t*)ctx;
  if( uc ) {
    mcontext_t* mc = &uc->uc_mcontext;
    crash_write_lit("RIP="); crash_write_hex((uint64_t)mc->gregs[REG_RIP]);
    crash_write_lit("RSP="); crash_write_hex((uint64_t)mc->gregs[REG_RSP]);
    crash_write_lit("RBP="); crash_write_hex((uint64_t)mc->gregs[REG_RBP]);
    crash_write_lit("\n");
    crash_write_lit("RAX="); crash_write_hex((uint64_t)mc->gregs[REG_RAX]);
    crash_write_lit("RBX="); crash_write_hex((uint64_t)mc->gregs[REG_RBX]);
    crash_write_lit("RCX="); crash_write_hex((uint64_t)mc->gregs[REG_RCX]);
    crash_write_lit("RDX="); crash_write_hex((uint64_t)mc->gregs[REG_RDX]);
    crash_write_lit("\n");
  }
#else
  (void)ctx;
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

// forward declaration — defined in shim_kernel32_sync.hpp (included below)
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
static int find_main_exe_base(struct dl_phdr_info* info, size_t /*sz*/, void* data) {
  // Skip any entry that has a name — the main executable has an empty name.
  if( info->dlpi_name&&info->dlpi_name[0] )
    return 0;
  // dlpi_addr is the load *bias* (0 for non-PIE binaries that load at their
  // preferred address).  Walk PT_LOAD segments to find the lowest mapped VA,
  // which gives the true image base regardless of PIE/non-PIE.
  uintptr_t lowest = (uintptr_t)-1;
  for( int i = 0; i<info->dlpi_phnum; ++i ) {
    if( info->dlpi_phdr[i].p_type==PT_LOAD ) {
      uintptr_t va = (uintptr_t)info->dlpi_addr + info->dlpi_phdr[i].p_vaddr;
      if( va<lowest ) lowest = va;
      // Also look for the PE header (MZ signature) in any segment
      if( !g_pe_base && info->dlpi_phdr[i].p_filesz >= 64 ) {
        const uint8_t* seg = (const uint8_t*)va;
        if( seg[0]=='M' && seg[1]=='Z' ) {
          g_pe_base = (void*)va;
        }
      }
    }
  }
  if( lowest!=(uintptr_t)-1 )
    *(void**)data = (void*)lowest;
  return 1;
}

static void discover_image_base(void) {
  void* base = NULL;
  dl_iterate_phdr(find_main_exe_base, &base);
  if( base ) {
    g_image_base = base;
    // Update PEB+0x10 ImageBaseAddress
    *(void**)(fake_peb+0x10) = base;
  }
}

// ---------------------------------------------------------------------------
// PE TLS directory — static TLS + callbacks
static void tls_static_init_thread(void);
void run_tls_callbacks(uint32_t reason);
// ---------------------------------------------------------------------------
static uint64_t*  g_tls_callbacks_va = nullptr;
static uint32_t*  g_tls_index_addr   = nullptr; // *AddressOfIndex: DWORD TLS slot index
static uintptr_t  g_tls_template_va  = 0;       // StartAddressOfRawData
static size_t     g_tls_template_sz  = 0;       // EndAddressOfRawData - Start
static size_t     g_tls_zero_fill    = 0;        // SizeOfZeroFill
static size_t     g_tls_align        = 16;       // required alignment for static-TLS block
// g_tls_static_idx declared earlier (needed by tls_slots_dtor before this point)

// Layout of the ShimTlsInfo struct embedded in pe2elf's startup trampoline.
// Must match the push64 sequence in elf_build.hpp build_trampoline().
struct ShimTlsInfo {
  uint64_t template_va;   // StartAddressOfRawData (0 if no TLS)
  uint64_t template_sz;   // EndAddressOfRawData - Start
  uint64_t zero_fill;     // SizeOfZeroFill
  uint64_t align_chars;   // Characteristics
  uint64_t index_va;      // AddressOfIndex (0 if none)
  uint64_t callbacks_va;  // AddressOfCallBacks (0 if none)
};

// Called from pe2elf's startup thunk (lea rdi,[rip+struct]; call [rip+slot])
// before PE_ENTRY. Registers TLS directory info, allocates the static TLS slot,
// initialises main-thread TLS, and fires DLL_PROCESS_ATTACH callbacks.
extern "C" __attribute__((visibility("default")))
void shim_register_tls(const ShimTlsInfo* info) {
  if( !info ) return;
  g_tls_template_va  = (uintptr_t)info->template_va;
  g_tls_template_sz  = (size_t)info->template_sz;
  g_tls_zero_fill    = (size_t)info->zero_fill;
  g_tls_index_addr   = info->index_va  ? (uint32_t*)(uintptr_t)info->index_va  : nullptr;
  g_tls_callbacks_va = info->callbacks_va ? (uint64_t*)(uintptr_t)info->callbacks_va : nullptr;
  // Characteristics bits 20-23 encode alignment as 2^(N-1) bytes (N=1..15).
  // calloc/malloc guarantee 16-byte alignment on glibc x86-64; only use
  // posix_memalign when a larger alignment is requested.
  {
    uint32_t n = (uint32_t)(info->align_chars >> 20) & 0xF;
    g_tls_align = (n >= 1) ? ((size_t)1 << (n - 1)) : 1;
    if( g_tls_align < 16 ) g_tls_align = 16;
  }
  log_always("[SHIM] shim_register_tls: template=0x%llx sz=%zu callbacks=0x%llx\n",
             (unsigned long long)g_tls_template_va, g_tls_template_sz,
             (unsigned long long)info->callbacks_va);
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

typedef void (__attribute__((ms_abi)) *tls_callback_fn)(void*, uint32_t, void*);

void run_tls_callbacks(uint32_t reason) {
  uint64_t* cbs = g_tls_callbacks_va;
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
// WinAPI implementations — all use EXPORT (= visibility("default") + ms_abi)
// ===========================================================================

// ---------------------------------------------------------------------------
// 7.1 Process / Identity
#include "shim_kernel32_proc.hpp"

// ---------------------------------------------------------------------------
// 7.2 Error State, 7.10 Time / Performance, 7.14 Pointer Encoding
// ---------------------------------------------------------------------------
#include "shim_kernel32_smallstubs.hpp"

// ---------------------------------------------------------------------------
// 7.3 Memory
// ---------------------------------------------------------------------------
#include "shim_kernel32_mem.hpp"

// ---------------------------------------------------------------------------
// 7.4 File I/O + 7.5 File Times + 7.6 Directory / File Search
// ---------------------------------------------------------------------------
#include "shim_kernel32_file.hpp"


// ---------------------------------------------------------------------------
// 7.7 Console I/O
#include "shim_kernel32_console.hpp"

// ---------------------------------------------------------------------------
// 7.8 Module / Library
#include "shim_kernel32_module.hpp"

// ---------------------------------------------------------------------------
// 7.9 Startup / Command Line / Environment
#include "shim_kernel32_startup.hpp"

// 7.10 covered in shim_kernel32_smallstubs.hpp (included up at 7.2).

// ---------------------------------------------------------------------------
// 7.11 Synchronization
// ---------------------------------------------------------------------------
#include "shim_kernel32_critsec.hpp"

// ---------------------------------------------------------------------------
// 7.12 InitializeSListHead / other sync stubs
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// 7.13 String / Code Page
#include "shim_kernel32_string.hpp"

// 7.14 covered in shim_kernel32_smallstubs.hpp (included up at 7.2).

// ---------------------------------------------------------------------------
// 7.15 Exception / SEH stubs
// ---------------------------------------------------------------------------
#include "shim_kernel32_except.hpp"

// ---------------------------------------------------------------------------
// Misc stubs (GetStringTypeA, LCMapStringA, Sleep)
// ---------------------------------------------------------------------------
#include "shim_kernel32_miscstubs.hpp"

// ---------------------------------------------------------------------------
// A-variant file/directory functions
// ---------------------------------------------------------------------------
#include "shim_kernel32_file_a.hpp"

// ---------------------------------------------------------------------------
// SetFilePointer (non-Ex), SetFileTime, SetEndOfFile, FILETIME ↔ DOS
// ---------------------------------------------------------------------------
#include "shim_kernel32_filetime.hpp"

// ---------------------------------------------------------------------------
// FLS (Fiber Local Storage)
// ---------------------------------------------------------------------------
#include "shim_kernel32_fls.hpp"

// ---------------------------------------------------------------------------
// Locale / GetLocaleInfoA, FormatMessageA
// ---------------------------------------------------------------------------
#include "shim_kernel32_locale.hpp"

// ---------------------------------------------------------------------------
// Console misc
// ---------------------------------------------------------------------------
#include "shim_kernel32_console_misc.hpp"
// ---------------------------------------------------------------------------
// Additional KERNEL32 functions
// ---------------------------------------------------------------------------
#include "shim_kernel32_misc.hpp"

#include "shim_kernel32_sync.hpp"

// ---------------------------------------------------------------------------
// Global memory, file attributes, FILETIME→SYSTEMTIME, system info
// ---------------------------------------------------------------------------
#include "shim_kernel32_sysinfo.hpp"

// ---------------------------------------------------------------------------
// Thread pseudo-handle, suspend/resume, context, affinity, duplication,
// TryEnterCriticalSection, WaitForMultipleObjects
// ---------------------------------------------------------------------------
#include "shim_kernel32_thread.hpp"

// ---------------------------------------------------------------------------
// Console extras
// ---------------------------------------------------------------------------
#include "shim_kernel32_console_extras.hpp"

// ---------------------------------------------------------------------------
// Vectored Exception Handler
// ---------------------------------------------------------------------------
#include "shim_kernel32_veh.hpp"

// ---------------------------------------------------------------------------
// kernel32 tail — Temp, SetCurrentDirectoryW, time/locale conversion,
// memory status, shell32/shlwapi/winmm, SetConsoleCtrlHandler, file ops,
// system info, paths, string ops, sync wrappers, and stubs
// ---------------------------------------------------------------------------
#include "shim_kernel32_tail.hpp"

// ---------------------------------------------------------------------------
// advapi32
// ---------------------------------------------------------------------------
#include "shim_advapi32.hpp"

// ---------------------------------------------------------------------------
// shell32
// ---------------------------------------------------------------------------
#include "shim_shell32.hpp"

// ---------------------------------------------------------------------------
// user32
// ---------------------------------------------------------------------------
#include "shim_user32.hpp"

// ---------------------------------------------------------------------------
// kernel32 A-variant wrappers
// ---------------------------------------------------------------------------
#include "shim_kernel32_a.hpp"

#include "shim_msvcrt.hpp"
