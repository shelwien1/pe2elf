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
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <time.h>
#include <ctype.h>
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

#ifdef WINAPI_LOG_ENABLED
#define log_always log_write
#define LOG(name, fmt, ...) \
  log_write("[%d] " name "(" fmt ")\n", (int)getpid(), ##__VA_ARGS__)
#else
#define log_always log_write
#define LOG(name, fmt, ...)  ((void)0)
#endif

// ---------------------------------------------------------------------------
// Thread-local last error
// ---------------------------------------------------------------------------
static __thread uint32_t tls_last_error = 0;
static __thread uint8_t fake_teb[0x2000];  // forward; full init in shim_init_teb()

// pthread key whose destructor frees the per-thread tls_slots block on exit
static pthread_key_t  g_tls_slots_key;
static pthread_once_t g_tls_slots_key_once = PTHREAD_ONCE_INIT;
static void tls_slots_key_init(void) { pthread_key_create(&g_tls_slots_key, free); }

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

static void shim_init_teb(void) {
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
  if( !real_fn )
    real_fn = (real_pthread_create_t)dlsym(RTLD_NEXT, "pthread_create");
  if( !real_fn ) return ENOSYS;   // libpthread not reachable via RTLD_NEXT
  ShimThreadArgs* ta = (ShimThreadArgs*)malloc(sizeof(ShimThreadArgs));
  if( !ta ) return ENOMEM;
  ta->fn = fn;
  ta->arg = arg;
  int ret = real_fn(tid, attr, shim_thread_trampoline, ta);
  if( ret!=0 ) free(ta);   // trampoline never runs; we must free
  return ret;
}

// ---------------------------------------------------------------------------
// HANDLE table
// ---------------------------------------------------------------------------
enum HandleKind { H_FREE, H_FILE, H_FIND, H_MODULE };

struct FindCtx {
  int  refcount;     // protected by g_handles_mu; freed when it reaches 0
  DIR* dir;
  char glob[260];
  char dirpath[PATH_MAX];
};

struct HandleSlot {
  HandleKind kind;
  union {
    int fd;
    FindCtx* find;
    void* dlhandle;
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

static void mmap_track_add(void* base, size_t size) {
  pthread_mutex_lock(&g_mmap_mu);
  for( int i = 0; i<MMAP_TRACK_MAX; ++i ) {
    if( !g_mmap_table[i].base ) {
      g_mmap_table[i].base = base;
      g_mmap_table[i].size = size;
      break;
    }
  }
  pthread_mutex_unlock(&g_mmap_mu);
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

static void rebuild_cmdline(void) {
  // Read /proc/self/cmdline
  int fd = open("/proc/self/cmdline", O_RDONLY);
  if( fd<0 ) {
    g_cmdline[0] = '\0';
    return;
  }
  char raw[32768];
  int n = (int)read(fd, raw, sizeof(raw)-1);
  close(fd);
  if( n<=0 ) {
    g_cmdline[0] = '\0';
    return;
  }
  raw[n] = '\0';

  // Convert NUL-separated argv to space-separated cmdline with quoting
  size_t out = 0;
  const char* p = raw;
  const char* end = raw+n;
  int first = 1;
  while( p<end&&out+4<sizeof(g_cmdline) ) {
    if( !first )
      g_cmdline[out++] = ' ';
    first = 0;
    int needs_quote = (strchr(p, ' ')||strchr(p, '\t')||*p=='\0');
    if( needs_quote )
      g_cmdline[out++] = '"';
    while( *p&&p<end&&out+2<sizeof(g_cmdline) )
      g_cmdline[out++] = *p++;
    if( needs_quote )
      g_cmdline[out++] = '"';
    p++; // skip NUL separator
  }
  g_cmdline[out] = '\0';

  // Build UTF-16LE version
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
  _exit(sig+128);
}

static void install_signal_handlers(void) {
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_sigaction = crash_handler;
  sa.sa_flags = SA_SIGINFO;
  sigaction(SIGSEGV, &sa, NULL);
  sigaction(SIGILL, &sa, NULL);
  sigaction(SIGFPE, &sa, NULL);
  sigaction(SIGBUS, &sa, NULL);
}

// ---------------------------------------------------------------------------
// Image base discovery (B13, R26)
// ---------------------------------------------------------------------------
static int find_main_exe_base(struct dl_phdr_info* info, size_t /*sz*/, void* data) {
  // The first call to dl_iterate_phdr is the main executable (empty name).
  if( info->dlpi_name&&info->dlpi_name[0] )
    return 0;
  *(void**)data = (void*)(uintptr_t)info->dlpi_addr;
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
// Constructor
// ---------------------------------------------------------------------------
__attribute__((constructor)) static void shim_init(void) {
  setlocale(LC_ALL, "");
  init_fake_peb();
  discover_image_base();
  handles_init();
  shim_init_teb();
  log_init();
  rebuild_cmdline();
  build_env_block();
  install_signal_handlers();
}

#pragma GCC visibility pop

// ===========================================================================
// WinAPI implementations — all use EXPORT (= visibility("default") + ms_abi)
// ===========================================================================

// ---------------------------------------------------------------------------
// 7.1 Process / Identity
// ---------------------------------------------------------------------------
extern "C" EXPORT HANDLE GetCurrentProcess(void) {
  LOG("GetCurrentProcess", "");
  return PROCESS_PSEUDO_HANDLE;
}

extern "C" EXPORT DWORD GetCurrentProcessId(void) {
  return (DWORD)getpid();
}

extern "C" EXPORT DWORD GetCurrentThreadId(void) {
  return (DWORD)syscall(SYS_gettid);
}

extern "C" EXPORT void ExitProcess(DWORD code) {
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
static void log_backtrace(void) {}
// musl doesn't provide malloc_usable_size; return 0 so HeapSize is a stub
// and HeapReAlloc zero-fills conservatively
static size_t malloc_usable_size(void* /*p*/) { return 0; }
#endif

extern "C" EXPORT BOOL TerminateProcess(HANDLE h, DWORD code) {
  (void)h;
  log_always("[SHIM] TerminateProcess(0x%08x)\n", code);
  log_backtrace();
  _exit((int)code);
  return TRUE;
}

extern "C" EXPORT BOOL IsDebuggerPresent(void) {
  log_always("[SHIM] IsDebuggerPresent()\n");
  return FALSE;
}

#ifdef __x86_64__
static unsigned int cpuid_get_edx(unsigned int leaf) {
  unsigned int eax, ebx, ecx, edx;
  __asm__ volatile ("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                             : "a"(leaf), "c"(0));
  (void)eax; (void)ebx; (void)ecx;
  return edx;
}
#endif

extern "C" EXPORT BOOL IsProcessorFeaturePresent(DWORD feature) {
#ifdef __x86_64__
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

// ---------------------------------------------------------------------------
// 7.2 Error State
// ---------------------------------------------------------------------------
extern "C" EXPORT DWORD GetLastError(void) {
  log_always("[SHIM] GetLastError() -> %u (caller=%p)\n", tls_last_error, __builtin_return_address(0));
  return tls_last_error;
}

extern "C" EXPORT void SetLastError(DWORD e) {
  SET_LAST_ERROR(e);
}

// ---------------------------------------------------------------------------
// 7.3 Memory
// ---------------------------------------------------------------------------
static int prot_from_protect(DWORD protect) {
  switch( protect&0xFF ) {
  case PAGE_NOACCESS:
    return PROT_NONE;
  case PAGE_READONLY:
    return PROT_READ;
  case PAGE_READWRITE:
    return PROT_READ|PROT_WRITE;
  case PAGE_EXECUTE:
    return PROT_EXEC;
  case PAGE_EXECUTE_READ:
    return PROT_EXEC|PROT_READ;
  case PAGE_EXECUTE_READWRITE:
    return PROT_EXEC|PROT_READ|PROT_WRITE;
  default:
    log_always("[SHIM] prot_from_protect: unknown protect=0x%x, defaulting to RW\n", protect);
    return PROT_READ|PROT_WRITE;
  }
}

extern "C" EXPORT LPVOID VirtualAlloc(LPVOID addr, size_t size, DWORD type, DWORD protect) {
  (void)type;
  int prot = prot_from_protect(protect);
  int flags = MAP_PRIVATE|MAP_ANONYMOUS;
  if( addr ) {
#ifdef MAP_FIXED_NOREPLACE
    flags |= MAP_FIXED_NOREPLACE;
    void* p = mmap(addr, size, prot, flags, -1, 0);
    if( p==MAP_FAILED ) {
      flags = (flags&~MAP_FIXED_NOREPLACE)|MAP_FIXED;
      p = mmap(addr, size, prot, flags, -1, 0);
      if( p!=addr ) { munmap(p, size); SET_LAST_ERROR(ERROR_OUTOFMEMORY); return NULL; }
    }
    mmap_track_add(p, size);
    return p;
#else
    flags |= MAP_FIXED;
#endif
  }
  void* p = mmap(addr, size, prot, flags, -1, 0);
  if( p==MAP_FAILED ) {
    SET_LAST_ERROR(ERROR_OUTOFMEMORY);
    return NULL;
  }
  mmap_track_add(p, size);
  return p;
}

extern "C" EXPORT BOOL VirtualFree(LPVOID addr, size_t size, DWORD type) {
  if( type&MEM_RELEASE ) {
    if( size!=0 ) {
      SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
      return FALSE;
    }
    size_t tracked = mmap_track_remove(addr);
    if( tracked )
      munmap(addr, tracked);
  } else if( type&MEM_DECOMMIT ) {
    mprotect(addr, size, PROT_NONE);
    madvise(addr, size, MADV_DONTNEED);
  }
  return TRUE;
}

extern "C" EXPORT HANDLE HeapCreate(DWORD flags, size_t init, size_t maxsz) {
  (void)flags;
  (void)init;
  (void)maxsz;
  return HEAP_PSEUDO_HANDLE;
}

extern "C" EXPORT HANDLE GetProcessHeap(void) {
  return HEAP_PSEUDO_HANDLE;
}

extern "C" EXPORT LPVOID HeapAlloc(HANDLE heap, DWORD flags, size_t size) {
  (void)heap;
  void* p = (flags&HEAP_ZERO_MEMORY) ? calloc(1, size) : malloc(size);
  if( !p )
    SET_LAST_ERROR(ERROR_OUTOFMEMORY);
  return p;
}

extern "C" EXPORT BOOL HeapFree(HANDLE heap, DWORD flags, LPVOID ptr) {
  (void)heap;
  (void)flags;
  if( (uintptr_t)ptr<0x10000&&ptr!=NULL ) {
    log_always("[SHIM] HeapFree: invalid ptr=%p (caller=%p) — ignoring\n", ptr, __builtin_return_address(0));
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  free(ptr);
  return TRUE;
}

extern "C" EXPORT LPVOID HeapReAlloc(HANDLE heap, DWORD flags, LPVOID ptr, size_t size) {
  (void)heap;
  // realloc(ptr, 0) is implementation-defined; clamp to 1 to always get a
  // valid pointer (matches Windows HeapReAlloc(size=0) behavior on glibc)
  size_t alloc_size = size ? size : 1;
  if( flags&HEAP_ZERO_MEMORY ) {
    size_t old_sz = ptr ? malloc_usable_size(ptr) : 0;
    void* p = realloc(ptr, alloc_size);
    // Zero only when we have a reliable old_sz (glibc) or there was no
    // previous allocation (ptr==NULL → fresh block, old_sz is correctly 0).
    // On musl malloc_usable_size stubs to 0; zeroing with old_sz==0 and
    // ptr!=NULL would destroy the existing data, so we skip it.
    if( p&&size>old_sz&&(old_sz>0||!ptr) )
      memset((char*)p+old_sz, 0, size-old_sz);
    if( !p ) SET_LAST_ERROR(ERROR_OUTOFMEMORY);
    return p;
  }
  void* p = realloc(ptr, alloc_size);
  if( !p ) SET_LAST_ERROR(ERROR_OUTOFMEMORY);
  return p;
}

extern "C" EXPORT size_t HeapSize(HANDLE heap, DWORD flags, LPCVOID ptr) {
  (void)heap;
  (void)flags;
  return malloc_usable_size((void*)ptr);
}

extern "C" EXPORT BOOL HeapSetInformation(HANDLE heap, DWORD cls, LPVOID info, size_t sz) {
  (void)heap;
  (void)cls;
  (void)info;
  (void)sz;
  return TRUE;
}

// ---------------------------------------------------------------------------
// 7.4 File I/O
// ---------------------------------------------------------------------------
extern "C" EXPORT HANDLE GetStdHandle(DWORD n) {
  switch( n ) {
  case STD_INPUT_HANDLE:
    return idx_to_handle(0);
  case STD_OUTPUT_HANDLE:
    return idx_to_handle(1);
  case STD_ERROR_HANDLE:
    return idx_to_handle(2);
  default:
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return INVALID_HANDLE_VALUE;
  }
}

extern "C" EXPORT BOOL SetStdHandle(DWORD n, HANDLE h) {
  int new_fd = get_fd(h);
  if( new_fd<0 )
    return FALSE;
  int idx = -1;
  switch( n ) {
  case STD_INPUT_HANDLE:  idx = 0; break;
  case STD_OUTPUT_HANDLE: idx = 1; break;
  case STD_ERROR_HANDLE:  idx = 2; break;
  default:
    return FALSE;
  }
  pthread_mutex_lock(&g_handles_mu);
  g_handles[idx].fd = new_fd;
  pthread_mutex_unlock(&g_handles_mu);
  // Redirect the underlying fd so CRT printf/fwrite follows (B15)
  dup2(new_fd, idx);
  return TRUE;
}

extern "C" EXPORT HANDLE CreateFileW(LPCWSTR name, DWORD access, DWORD share, SECURITY_ATTRIBUTES* sa, DWORD disp, DWORD flags, HANDLE tmpl) {
  (void)share;
  (void)sa;
  (void)flags;
  (void)tmpl;
  char narrow[PATH_MAX];
  wchar_to_utf8(name, narrow, sizeof(narrow));
  char posix[PATH_MAX];
  win_path_to_posix(narrow, posix, sizeof(posix));

  int oflags = make_open_flags(access, disp);
  int fd = open(posix, oflags, 0666);
  log_always("[SHIM] CreateFileW(\"%s\", acc=0x%x, disp=%u) -> fd=%d\n", posix, access, disp, fd);
  if( fd<0 ) {
    set_errno_error();
    return INVALID_HANDLE_VALUE;
  }

  HANDLE hret = handle_alloc_file(fd);
  if( hret==INVALID_HANDLE_VALUE )
    close(fd);
  return hret;
}

extern "C" EXPORT BOOL CloseHandle(HANDLE h) {
  int idx = handle_to_idx(h);
  if( idx<0||idx<=2 )
    return TRUE;   // don't close stdio; pseudo handles are always ok
  pthread_mutex_lock(&g_handles_mu);
  HandleKind k = g_handles[idx].kind;
  int fd = (k==H_FILE) ? g_handles[idx].fd : -1;
  FindCtx* fc = (k==H_FIND) ? g_handles[idx].find : NULL;
  void* dlh = (k==H_MODULE) ? g_handles[idx].dlhandle : NULL;
  if( k!=H_FREE )
    g_handles[idx].kind = H_FREE;
  pthread_mutex_unlock(&g_handles_mu);
  if( k==H_FILE ) {
    close(fd);
  } else if( k==H_FIND ) {
    if( fc ) release_find_ctx(fc);   // drops refcount; frees when it hits 0
  } else if( k==H_MODULE ) {
    if( dlh )
      dlclose(dlh);
  } else {
    SET_LAST_ERROR(ERROR_INVALID_HANDLE);
    return FALSE;
  }
  return TRUE;
}

extern "C" EXPORT BOOL ReadFile(HANDLE h, LPVOID buf, DWORD n, DWORD* pRead, void* ov) {
  (void)ov;
  log_always("[SHIM] ReadFile(h=%p, n=%u, caller=%p)\n", h, n, __builtin_return_address(0));
  int fd = get_fd(h);
  if( fd<0 ) {
    if( pRead )
      *pRead = 0;
    return FALSE;
  }
  ssize_t r = read(fd, buf, n);
  log_always("[SHIM] ReadFile -> r=%zd\n", r);
  if( pRead )
    *pRead = (r>=0) ? (DWORD)r : 0;
  if( r<0 ) {
    set_errno_error();
    return FALSE;
  }
  return TRUE;
}

extern "C" EXPORT BOOL WriteFile(HANDLE h, LPCVOID buf, DWORD n, DWORD* pWritten, void* ov) {
  (void)ov;
  int fd = get_fd(h);
  if( fd<0 ) {
    if( pWritten )
      *pWritten = 0;
    return FALSE;
  }
  ssize_t r = write(fd, buf, n);
  if( pWritten )
    *pWritten = (r>=0) ? (DWORD)r : 0;
  if( r<0 ) {
    set_errno_error();
    return FALSE;
  }
  return TRUE;
}

extern "C" EXPORT BOOL SetFilePointerEx(HANDLE h, LARGE_INTEGER dist, LARGE_INTEGER* pNew, DWORD method) {
  int fd = get_fd(h);
  if( fd<0 )
    return FALSE;
  int whence = (method==FILE_BEGIN) ? SEEK_SET : (method==FILE_CURRENT) ? SEEK_CUR : SEEK_END;
  off_t result = lseek(fd, (off_t)dist.QuadPart, whence);
  if( result==(off_t)-1 ) {
    set_errno_error();
    return FALSE;
  }
  if( pNew )
    pNew->QuadPart = result;
  return TRUE;
}

extern "C" EXPORT BOOL FlushFileBuffers(HANDLE h) {
  int fd = get_fd(h);
  if( fd<0 )
    return FALSE;
  fsync(fd);
  return TRUE;
}

extern "C" EXPORT DWORD GetFileType(HANDLE h) {
  int fd = get_fd(h);
  if( fd<0 )
    return FILE_TYPE_UNKNOWN;
  struct stat st;
  if( fstat(fd, &st)<0 )
    return FILE_TYPE_UNKNOWN;
  if( S_ISREG(st.st_mode) )
    return FILE_TYPE_DISK;
  if( S_ISCHR(st.st_mode) )
    return FILE_TYPE_CHAR;
  if( S_ISFIFO(st.st_mode) )
    return FILE_TYPE_PIPE;
  return FILE_TYPE_UNKNOWN;
}

// ---------------------------------------------------------------------------
// 7.5 File Times
// ---------------------------------------------------------------------------
extern "C" EXPORT void GetSystemTimeAsFileTime(FILETIME* pft) {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  uint64_t v = (uint64_t)ts.tv_sec*10000000ULL+(uint64_t)ts.tv_nsec/100ULL+FILETIME_EPOCH;
  *pft = u64_to_ft(v);
}

// ---------------------------------------------------------------------------
// 7.6 Directory / File Search
// ---------------------------------------------------------------------------
static void fill_find_data_w(WIN32_FIND_DATAW* pfd, const char* fullpath, const char* name) {
  memset(pfd, 0, sizeof(*pfd));
  struct stat st;
  if( stat(fullpath, &st)==0 ) {
    pfd->dwFileAttributes = S_ISDIR(st.st_mode) ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL;
    uint64_t mtime = (uint64_t)st.st_mtime*10000000ULL+FILETIME_EPOCH;
    pfd->ftLastWriteTime = u64_to_ft(mtime);
    pfd->ftCreationTime = pfd->ftLastWriteTime;
    pfd->ftLastAccessTime = pfd->ftLastWriteTime;
    pfd->nFileSizeLow = (DWORD)(st.st_size&0xFFFFFFFF);
    pfd->nFileSizeHigh = (DWORD)(st.st_size>>32);
  }
  utf8_to_wchar(name, pfd->cFileName, 260);
}

static void fill_find_data_a(WIN32_FIND_DATAA* pfd, const char* fullpath, const char* name) {
  memset(pfd, 0, sizeof(*pfd));
  struct stat st;
  if( stat(fullpath, &st)==0 ) {
    pfd->dwFileAttributes = S_ISDIR(st.st_mode) ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL;
    uint64_t mtime = (uint64_t)st.st_mtime*10000000ULL+FILETIME_EPOCH;
    pfd->ftLastWriteTime = u64_to_ft(mtime);
    pfd->ftCreationTime = pfd->ftLastWriteTime;
    pfd->ftLastAccessTime = pfd->ftLastWriteTime;
    pfd->nFileSizeLow = (DWORD)(st.st_size&0xFFFFFFFF);
    pfd->nFileSizeHigh = (DWORD)(st.st_size>>32);
  }
  strncpy(pfd->cFileName, name, 259);
}

// Shared helper: open directory from a POSIX pattern path, scan to first match,
// populate ctx. Returns first matching dirent or NULL.
static struct dirent* find_ctx_open(const char* posix, FindCtx** out_ctx) {
  char dir[PATH_MAX] = ".";
  char glob[260] = "*";
  char tmp[PATH_MAX];
  snprintf(tmp, sizeof(tmp), "%s", posix);
  char* slash = strrchr(tmp, '/');
  if( slash ) {
    *slash = '\0';
    snprintf(dir, sizeof(dir), "%s", tmp);
    snprintf(glob, sizeof(glob), "%s", slash+1);
  } else {
    size_t n = strnlen(tmp, sizeof(glob)-1);
    memcpy(glob, tmp, n);
    glob[n] = '\0';
  }
  DIR* d = opendir(dir[0] ? dir : ".");
  if( !d ) {
    SET_LAST_ERROR(ERROR_PATH_NOT_FOUND);
    return NULL;
  }
  FindCtx* ctx = (FindCtx*)calloc(1, sizeof(FindCtx));
  ctx->dir = d;
  snprintf(ctx->glob, sizeof(ctx->glob), "%s", glob);
  snprintf(ctx->dirpath, sizeof(ctx->dirpath), "%s", dir[0] ? dir : ".");
  *out_ctx = ctx;
  struct dirent* ent;
  while( (ent = readdir(d))!=NULL ) {
    if( strcmp(ent->d_name, ".")==0||strcmp(ent->d_name, "..")==0 )
      continue;
    if( fnmatch(ctx->glob, ent->d_name, FNM_NOESCAPE)==0 )
      return ent;
  }
  closedir(d);
  free(ctx);
  *out_ctx = NULL;
  SET_LAST_ERROR(ERROR_FILE_NOT_FOUND);
  return NULL;
}

extern "C" EXPORT HANDLE FindFirstFileExW(LPCWSTR pattern, int lvl, WIN32_FIND_DATAW* pfd, int srchas, void* filter, DWORD flags) {
  (void)lvl;
  (void)srchas;
  (void)filter;
  (void)flags;
  char narrow[PATH_MAX], posix[PATH_MAX];
  wchar_to_utf8(pattern, narrow, sizeof(narrow));
  win_path_to_posix(narrow, posix, sizeof(posix));

  FindCtx* ctx = NULL;
  struct dirent* ent = find_ctx_open(posix, &ctx);
  if( !ent )
    return INVALID_HANDLE_VALUE;

  char fullpath[PATH_MAX];
  path_join(fullpath, sizeof(fullpath), ctx->dirpath, ent->d_name);
  fill_find_data_w(pfd, fullpath, ent->d_name);

  HANDLE hret = handle_alloc_find(ctx);
  if( hret==INVALID_HANDLE_VALUE ) {
    closedir(ctx->dir);
    free(ctx);
  }
  return hret;
}

extern "C" EXPORT BOOL FindNextFileW(HANDLE h, WIN32_FIND_DATAW* pfd) {
  FindCtx* ctx = get_find_ctx(h);   // retained; safe against concurrent FindClose
  if( !ctx ) return FALSE;
  struct dirent* ent;
  BOOL found = FALSE;
  while( (ent = readdir(ctx->dir))!=NULL ) {
    if( strcmp(ent->d_name, ".")==0||strcmp(ent->d_name, "..")==0 )
      continue;
    if( fnmatch(ctx->glob, ent->d_name, FNM_NOESCAPE)!=0 )
      continue;
    char fullpath[PATH_MAX];
    path_join(fullpath, sizeof(fullpath), ctx->dirpath, ent->d_name);
    fill_find_data_w(pfd, fullpath, ent->d_name);
    found = TRUE;
    break;
  }
  if( !found ) SET_LAST_ERROR(ERROR_NO_MORE_FILES);
  release_find_ctx(ctx);
  return found;
}

extern "C" EXPORT BOOL FindClose(HANDLE h) {
  int idx = handle_to_idx(h);
  pthread_mutex_lock(&g_handles_mu);
  if( idx<0||g_handles[idx].kind!=H_FIND ) {
    pthread_mutex_unlock(&g_handles_mu);
    SET_LAST_ERROR(ERROR_INVALID_HANDLE);
    return FALSE;
  }
  FindCtx* fc = g_handles[idx].find;
  g_handles[idx].kind = H_FREE;
  g_handles[idx].find = NULL;
  pthread_mutex_unlock(&g_handles_mu);
  if( fc ) release_find_ctx(fc);   // drops refcount; frees when it hits 0
  return TRUE;
}

// ---------------------------------------------------------------------------
// 7.7 Console I/O
// ---------------------------------------------------------------------------
extern "C" EXPORT DWORD GetConsoleCP(void) {
  return 65001;
}

extern "C" EXPORT DWORD GetConsoleOutputCP(void) {
  return 65001;
}

extern "C" EXPORT BOOL GetConsoleMode(HANDLE h, DWORD* pMode) {
  log_always("[SHIM] GetConsoleMode(h=%p, caller=%p)\n", h, __builtin_return_address(0));
  if( !pMode ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }
  // Derive fd from handle, fall back to stdin/stdout
  int idx = handle_to_idx(h);
  int fd = (idx>=0 && g_handles[idx].kind==H_FILE) ? g_handles[idx].fd : STDIN_FILENO;
  struct termios ts;
  if( tcgetattr(fd, &ts)!=0 ) {
    // Not a tty — return sensible output defaults
    *pMode = ENABLE_PROCESSED_OUTPUT|ENABLE_WRAP_AT_EOL_OUTPUT;
    return TRUE;
  }
  DWORD mode = 0;
  if( ts.c_lflag&ICANON )  mode |= ENABLE_LINE_INPUT|ENABLE_PROCESSED_INPUT;
  if( ts.c_lflag&ECHO )    mode |= ENABLE_ECHO_INPUT;
  // For output handles always add the processed/wrap flags
  mode |= ENABLE_PROCESSED_OUTPUT|ENABLE_WRAP_AT_EOL_OUTPUT;
  *pMode = mode;
  return TRUE;
}

extern "C" EXPORT BOOL SetConsoleMode(HANDLE h, DWORD mode) {
  log_always("[SHIM] SetConsoleMode(h=%p, mode=0x%x, caller=%p)\n", h, mode, __builtin_return_address(0));
  (void)h;
  (void)mode;
  return TRUE;
}

extern "C" EXPORT BOOL WriteConsoleA(HANDLE h, LPCVOID buf, DWORD nChars, DWORD* pWritten, void* reserved) {
  (void)reserved;
  return WriteFile(h, buf, nChars, pWritten, NULL);
}

extern "C" EXPORT BOOL WriteConsoleW(HANDLE h, LPCVOID wbuf, DWORD nChars, DWORD* pWritten, void* reserved) {
  (void)reserved;
  // Build a bounded, NUL-terminated copy so wchar_to_utf8 doesn't over-read
  uint16_t tmp[65536];
  size_t n = (nChars<65535) ? nChars : 65535;
  memcpy(tmp, wbuf, n*2);
  tmp[n] = 0;
  char utf8[65536*4];
  int nbytes = wchar_to_utf8(tmp, utf8, sizeof(utf8)-1);
  DWORD written = 0;
  BOOL r = WriteFile(h, utf8, (DWORD)nbytes, &written, NULL);
  if( pWritten ) {
    // Approximate written wide chars from written bytes (UTF-8 bytes >= wide chars)
    *pWritten = written>0 ? nChars : 0;
  }
  return r;
}

// ---------------------------------------------------------------------------
// 7.8 Module / Library
// ---------------------------------------------------------------------------
// Typed pseudo-handles (B14/R27): values outside the handle-table range.
// FAKE_WIN_MODULE: any Windows DLL we can't load as a real .so.
// MAIN_IMAGE_MODULE: returned by GetModuleHandleW(NULL).
#define FAKE_WIN_MODULE  ((HANDLE)(intptr_t)(MAX_HANDLES+1))
#define MAIN_IMAGE_MODULE ((HANDLE)(intptr_t)(MAX_HANDLES+2))

extern "C" EXPORT HANDLE GetModuleHandleW(LPCWSTR name) {
  if( !name )
    return MAIN_IMAGE_MODULE;
  char narrow[PATH_MAX], posix[PATH_MAX];
  wchar_to_utf8(name, narrow, sizeof(narrow));
  win_path_to_posix(narrow, posix, sizeof(posix));
  void* h = dlopen(posix, RTLD_NOLOAD|RTLD_LAZY);
  if( h )
    return h;
  // Any Windows DLL name we don't have as a .so — fake it.
  SET_LAST_ERROR(ERROR_SUCCESS);
  return FAKE_WIN_MODULE;
}

extern "C" EXPORT BOOL GetModuleHandleExW(DWORD flags, LPCWSTR name, HANDLE* phModule) {
  (void)flags;
  HANDLE h = GetModuleHandleW(name);
  if( phModule )
    *phModule = h;
  return h ? TRUE : FALSE;
}

extern "C" EXPORT DWORD GetModuleFileNameW(HANDLE h, LPWSTR buf, DWORD size) {
  char tmp[PATH_MAX];
  if( h==NULL||h==MAIN_IMAGE_MODULE ) {
    ssize_t n = readlink("/proc/self/exe", tmp, sizeof(tmp)-1);
    if( n<0 ) { set_errno_error(); return 0; }
    tmp[n] = '\0';
  } else {
    // Resolve loaded .so path via dladdr against a known symbol in the module
    int idx = handle_to_idx(h);
    void* dlh = (idx>=0&&g_handles[idx].kind==H_MODULE) ? g_handles[idx].dlhandle : NULL;
    if( dlh ) {
      void* sym = dlsym(dlh, "_init");
      if( !sym )
        sym = dlh;  // fallback
      Dl_info info;
      if( dladdr(sym, &info)&&info.dli_fname ) {
        strncpy(tmp, info.dli_fname, sizeof(tmp)-1);
        tmp[sizeof(tmp)-1] = '\0';
      } else {
        tmp[0] = '\0';
      }
    } else {
      tmp[0] = '\0';
    }
  }
  return (DWORD)utf8_to_wchar(tmp, buf, size);
}

extern "C" EXPORT HANDLE LoadLibraryExW(LPCWSTR name, HANDLE file, DWORD flags) {
  (void)file;
  char narrow[PATH_MAX], posix[PATH_MAX];
  wchar_to_utf8(name, narrow, sizeof(narrow));
  win_path_to_posix(narrow, posix, sizeof(posix));
  int dlflags = RTLD_LAZY|RTLD_GLOBAL;
  if( flags&LOAD_LIBRARY_AS_DATAFILE )
    dlflags = RTLD_LAZY;
  void* h = dlopen(posix, dlflags);
  if( h ) {
    HANDLE hret = handle_alloc_module(h);
    if( hret!=INVALID_HANDLE_VALUE )
      return hret;
    dlclose(h);
  }
  // For any Windows DLL we can't resolve as a .so, return a sentinel so
  // GetProcAddress can still find symbols exported from our shim.
  SET_LAST_ERROR(ERROR_SUCCESS);
  return FAKE_WIN_MODULE;
}

extern "C" EXPORT BOOL FreeLibrary(HANDLE h) {
  if( h==FAKE_WIN_MODULE||h==MAIN_IMAGE_MODULE )
    return TRUE;
  int idx = handle_to_idx(h);
  pthread_mutex_lock(&g_handles_mu);
  if( idx<0||g_handles[idx].kind!=H_MODULE ) {
    pthread_mutex_unlock(&g_handles_mu);
    return FALSE;
  }
  void* dlh = g_handles[idx].dlhandle;
  g_handles[idx].kind = H_FREE;
  g_handles[idx].dlhandle = NULL;
  pthread_mutex_unlock(&g_handles_mu);
  dlclose(dlh);
  return TRUE;
}

extern "C" EXPORT LPVOID GetProcAddress(HANDLE h, LPCSTR name) {
  void* dlh;
  if( h==FAKE_WIN_MODULE||h==MAIN_IMAGE_MODULE||h==NULL ) {
    dlh = RTLD_DEFAULT;
  } else {
    int idx = handle_to_idx(h);
    if( idx>=0&&g_handles[idx].kind==H_MODULE )
      dlh = g_handles[idx].dlhandle;
    else
      dlh = RTLD_DEFAULT;
  }
  void* sym = dlsym(dlh, name);
  if( !sym )
    SET_LAST_ERROR(ERROR_CALL_NOT_IMPLEMENTED);
  return sym;
}

// ---------------------------------------------------------------------------
// 7.9 Startup / Command Line / Environment
// ---------------------------------------------------------------------------
extern "C" EXPORT LPSTR GetCommandLineA(void) {
  return g_cmdline;
}

extern "C" EXPORT LPWSTR GetCommandLineW(void) {
  return (LPWSTR)g_cmdline_w;
}

extern "C" EXPORT void GetStartupInfoW(STARTUPINFOW* psi) {
  if( !psi )
    return;
  memset(psi, 0, sizeof(*psi));
  psi->cb = sizeof(STARTUPINFOW);
  psi->hStdInput = idx_to_handle(0);
  psi->hStdOutput = idx_to_handle(1);
  psi->hStdError = idx_to_handle(2);
  psi->dwFlags = STARTF_USESTDHANDLES;
}

extern "C" EXPORT void GetStartupInfoA(STARTUPINFOA* psi) {
  if( !psi )
    return;
  memset(psi, 0, sizeof(*psi));
  psi->cb = sizeof(STARTUPINFOA);
  psi->hStdInput = idx_to_handle(0);
  psi->hStdOutput = idx_to_handle(1);
  psi->hStdError = idx_to_handle(2);
  psi->dwFlags = STARTF_USESTDHANDLES;
}

extern "C" EXPORT LPSTR GetEnvironmentStrings(void) {
  if( !g_env_block )
    build_env_block();
  return g_env_block;
}

extern "C" EXPORT LPWSTR GetEnvironmentStringsW(void) {
  // Regenerate on demand if dirty (B23/R34)
  if( !g_env_block_w )
    build_env_block();
  return g_env_block_w;
}

extern "C" EXPORT BOOL FreeEnvironmentStringsA(LPSTR p) {
  if( p!=g_env_block )
    free(p);
  return TRUE;
}

extern "C" EXPORT BOOL FreeEnvironmentStringsW(LPWSTR p) {
  if( p!=(LPWSTR)g_env_block_w )
    free(p);
  return TRUE;
}

extern "C" EXPORT BOOL SetEnvironmentVariableW(LPCWSTR name, LPCWSTR val) {
  char n[512], v[4096];
  wchar_to_utf8(name, n, sizeof(n));
  if( val ) {
    wchar_to_utf8(val, v, sizeof(v));
    setenv(n, v, 1);
  } else {
    unsetenv(n);
  }
  // Invalidate cached wide env block so next GetEnvironmentStringsW regenerates (B23/R34)
  free(g_env_block_w);
  g_env_block_w = NULL;
  free(g_env_block);
  g_env_block = NULL;
  return TRUE;
}

// ---------------------------------------------------------------------------
// 7.10 Time / Performance
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL QueryPerformanceCounter(LARGE_INTEGER* pli) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  pli->QuadPart = (LONGLONG)ts.tv_sec*1000000000LL+ts.tv_nsec;
  return TRUE;
}

extern "C" EXPORT BOOL QueryPerformanceFrequency(LARGE_INTEGER* pli) {
  pli->QuadPart = 1000000000LL;
  return TRUE;
}

extern "C" EXPORT DWORD GetTickCount(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (DWORD)(ts.tv_sec*1000+ts.tv_nsec/1000000);
}

// ---------------------------------------------------------------------------
// 7.11 Synchronization
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL InitializeCriticalSectionAndSpinCount(CRITICAL_SECTION* cs, DWORD spin) {
  (void)spin;
  pthread_mutexattr_t a;
  pthread_mutexattr_init(&a);
  pthread_mutexattr_settype(&a, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init((pthread_mutex_t*)cs, &a);
  pthread_mutexattr_destroy(&a);
  return TRUE;
}

extern "C" EXPORT void InitializeCriticalSection(CRITICAL_SECTION* cs) {
  InitializeCriticalSectionAndSpinCount(cs, 0);
}

extern "C" EXPORT void EnterCriticalSection(CRITICAL_SECTION* cs) {
  log_always("[SHIM] EnterCriticalSection(%p, caller=%p)\n", cs, __builtin_return_address(0));
  pthread_mutex_lock((pthread_mutex_t*)cs);
  log_always("[SHIM] EnterCriticalSection(%p) done\n", cs);
}

extern "C" EXPORT void LeaveCriticalSection(CRITICAL_SECTION* cs) {
  log_always("[SHIM] LeaveCriticalSection(%p)\n", cs);
  pthread_mutex_unlock((pthread_mutex_t*)cs);
}

extern "C" EXPORT void DeleteCriticalSection(CRITICAL_SECTION* cs) {
  pthread_mutex_destroy((pthread_mutex_t*)cs);
}

// TLS / FLS
extern "C" EXPORT DWORD TlsAlloc(void) {
  pthread_key_t key;
  int r = pthread_key_create(&key, NULL);
  log_always("[SHIM] TlsAlloc() -> key=%u (r=%d)\n", (unsigned)key, r);
  if( r!=0 )
    return 0xFFFFFFFF;
  return (DWORD)key;
}

extern "C" EXPORT BOOL TlsFree(DWORD idx) {
  pthread_key_delete((pthread_key_t)idx);
  return TRUE;
}

extern "C" EXPORT LPVOID TlsGetValue(DWORD idx) {
  SET_LAST_ERROR(0);
  void* v = pthread_getspecific((pthread_key_t)idx);
  log_always("[SHIM] TlsGetValue(idx=%u) -> %p\n", idx, v);
  return v;
}

extern "C" EXPORT BOOL TlsSetValue(DWORD idx, LPVOID val) {
  int r = pthread_setspecific((pthread_key_t)idx, val);
  log_always("[SHIM] TlsSetValue(idx=%u, val=%p) -> r=%d\n", idx, val, r);
  return r==0 ? TRUE : FALSE;
}

extern "C" EXPORT void InitializeSListHead(void* h) {
  if( h )
    memset(h, 0, 16); // SLIST_HEADER is 16 bytes
}

// ---------------------------------------------------------------------------
// 7.12 InitializeSListHead / other sync stubs
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// 7.13 String / Code Page
// ---------------------------------------------------------------------------
extern "C" EXPORT DWORD GetACP(void) {
  return 65001;
}

extern "C" EXPORT DWORD GetOEMCP(void) {
  return 437;
}

extern "C" EXPORT BOOL IsValidCodePage(DWORD cp) {
  return (cp==65001||cp==437||cp==1252) ? TRUE : FALSE;
}

extern "C" EXPORT BOOL GetCPInfo(DWORD cp, CPINFO* info) {
  if( !info ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  info->MaxCharSize = (cp==65001) ? 4 : 2;
  info->DefaultChar[0] = '?';
  info->DefaultChar[1] = 0;
  memset(info->LeadByte, 0, sizeof(info->LeadByte));
  return TRUE;
}

extern "C" EXPORT int MultiByteToWideChar(DWORD cp, DWORD flags, LPCSTR src, int srclen, LPWSTR dst, int dstlen) {
  (void)cp;
  (void)flags;
  if( !src ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return 0;
  }
  if( srclen<0 )
    srclen = (int)strlen(src)+1;
  // Treat as UTF-8
  char tmp[65536];
  if( (size_t)srclen<sizeof(tmp) ) {
    memcpy(tmp, src, srclen);
    tmp[srclen] = '\0';
  } else {
    memcpy(tmp, src, sizeof(tmp)-1);
    tmp[sizeof(tmp)-1] = '\0';
  }
  if( dstlen==0 ) {
    // Count only
    uint16_t countbuf[65536];
    return utf8_to_wchar(tmp, countbuf, 65535)+1;
  }
  return utf8_to_wchar(tmp, dst, (size_t)dstlen);
}

extern "C" EXPORT int WideCharToMultiByte(DWORD cp, DWORD flags, LPCWSTR src, int srclen, LPSTR dst, int dstlen, LPCSTR defch, BOOL* useddef) {
  (void)cp;
  (void)flags;
  (void)defch;
  (void)useddef;
  if( !src ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return 0;
  }
  // Build a NUL-terminated copy bounded by srclen when srclen >= 0
  uint16_t tmp_w[65536];
  const uint16_t* wsrc = src;
  if( srclen>=0 ) {
    size_t n = (srclen<(int)(sizeof(tmp_w)/2-1)) ? (size_t)srclen : sizeof(tmp_w)/2-1;
    memcpy(tmp_w, src, n*2);
    tmp_w[n] = 0;
    wsrc = tmp_w;
  }
  if( dstlen==0 ) {
    char tmp[65536];
    return wchar_to_utf8(wsrc, tmp, sizeof(tmp));
  }
  return wchar_to_utf8(wsrc, dst, (size_t)dstlen);
}

extern "C" EXPORT int LCMapStringW(DWORD locale, DWORD flags, LPCWSTR src, int srclen, LPWSTR dst, int dstlen) {
  (void)locale;
  if( srclen<0 ) {
    // find length
    const uint16_t* p = src;
    srclen = 0;
    while( *p++ )
      srclen++;
    srclen++;
  }
  if( flags&LCMAP_UPPERCASE ) {
    if( dst&&dstlen>0 ) {
      int n = (srclen<dstlen) ? srclen : dstlen;
      for( int i = 0; i<n; ++i )
        dst[i] = (src[i]>='a'&&src[i]<='z') ? src[i]-32 : src[i];
    }
    return srclen;
  }
  if( flags&LCMAP_LOWERCASE ) {
    if( dst&&dstlen>0 ) {
      int n = (srclen<dstlen) ? srclen : dstlen;
      for( int i = 0; i<n; ++i )
        dst[i] = (src[i]>='A'&&src[i]<='Z') ? src[i]+32 : src[i];
    }
    return srclen;
  }
  // Unknown mapping — copy as-is
  if( dst&&dstlen>0 ) {
    int n = (srclen<dstlen) ? srclen : dstlen;
    memcpy(dst, src, (size_t)n*2);
  }
  return srclen;
}

static WORD classify_ctype1(unsigned int c) {
  // CT_CTYPE1 classification for the ASCII plane; non-ASCII gets C1_ALPHA
  if( c>127 ) return C1_ALPHA;
  unsigned char u = (unsigned char)c;
  WORD t = 0;
  if( isupper(u) ) t |= C1_UPPER|C1_ALPHA;
  if( islower(u) ) t |= C1_LOWER|C1_ALPHA;
  if( isdigit(u) ) t |= C1_DIGIT;
  if( isspace(u) ) t |= C1_SPACE;
  if( ispunct(u) ) t |= C1_PUNCT;
  if( iscntrl(u) ) t |= C1_CNTRL;
  if( u==' '||u=='\t' ) t |= C1_BLANK;
  if( isxdigit(u) ) t |= C1_XDIGIT;
  return t;
}

extern "C" EXPORT BOOL GetStringTypeW(DWORD type, LPCWSTR src, int count, WORD* types) {
  if( !src||!types||count==0 ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  if( count<0 ) {
    const uint16_t* p = src;
    count = 0;
    while( *p++ )
      count++;
  }
  for( int i = 0; i<count; ++i )
    types[i] = (type==CT_CTYPE1) ? classify_ctype1(src[i]) : 0;
  return TRUE;
}

extern "C" EXPORT int CompareStringW(DWORD locale, DWORD flags, LPCWSTR s1, int n1, LPCWSTR s2, int n2) {
  (void)locale;
  int i = 0;
  for(;; i++) {
    int at1 = (n1>=0) ? (i>=n1) : (!s1[i]);
    int at2 = (n2>=0) ? (i>=n2) : (!s2[i]);
    if( at1&&at2 )
      return CSTR_EQUAL;
    if( at1 )
      return CSTR_LESS_THAN;
    if( at2 )
      return CSTR_GREATER_THAN;
    uint16_t c1 = s1[i], c2 = s2[i];
    if( flags&NORM_IGNORECASE ) {
      if( c1>='A'&&c1<='Z' )
        c1 += 32;
      if( c2>='A'&&c2<='Z' )
        c2 += 32;
    }
    if( c1<c2 )
      return CSTR_LESS_THAN;
    if( c1>c2 )
      return CSTR_GREATER_THAN;
  }
}

// ---------------------------------------------------------------------------
// 7.14 Pointer Encoding
// ---------------------------------------------------------------------------
extern "C" EXPORT LPVOID EncodePointer(LPVOID p) {
  return p;
}

extern "C" EXPORT LPVOID DecodePointer(LPVOID p) {
  return p;
}

// ---------------------------------------------------------------------------
// 7.15 Exception / SEH stubs
// ---------------------------------------------------------------------------
extern "C" EXPORT LPVOID SetUnhandledExceptionFilter(LPVOID filter) {
  log_always("[SHIM] SetUnhandledExceptionFilter(%p)\n", filter);
  void* old = g_unhandled_filter;
  g_unhandled_filter = filter;
  return old;
}

extern "C" EXPORT LONG UnhandledExceptionFilter(void* pExcept) {
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
  // Chain to registered filter if set; otherwise signal fatal error (B36/R36)
  if( g_unhandled_filter ) {
    // Cannot call ms_abi safely here — just log and terminate
    log_always("[SHIM] UnhandledExceptionFilter: filter registered but cannot safely call; terminating\n");
  }
  _exit(1);
  return EXCEPTION_EXECUTE_HANDLER;
}

extern "C" EXPORT void RtlUnwindEx(void* f, void* target, void* except, void* retval, void* ctx, void* histo) {
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

extern "C" EXPORT LPVOID RtlVirtualUnwind(DWORD type, uint64_t base, uint64_t pc, void* entry, void* ctx, void** data, uint64_t* frame, void* transform) {
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

extern "C" EXPORT LPVOID RtlLookupFunctionEntry(uint64_t pc, uint64_t* base, void* histo) {
  (void)pc;
  (void)histo;
  if( base )
    *base = 0;
  return NULL;
}

extern "C" EXPORT void RtlCaptureContext(void* ctx) {
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

extern "C" EXPORT LPVOID RtlPcToFileHeader(LPVOID pc, LPVOID* pbase) {
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

extern "C" EXPORT void RaiseException(DWORD code, DWORD flags, DWORD nargs, const ULONG_PTR* args) {
  (void)args;
  (void)nargs;
  log_always("[SHIM] RaiseException code=0x%08x flags=0x%x\n", code, flags);
  if( flags&EXCEPTION_NONCONTINUABLE ) {
    _exit((int)code);
  }
}

// ---------------------------------------------------------------------------
// Misc stubs
// ---------------------------------------------------------------------------
extern "C" EXPORT DWORD GetStringTypeA(DWORD locale, DWORD type, LPCSTR src, int count, WORD* types) {
  (void)locale;
  if( !src||!types||count==0 ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  if( count<0 )
    count = (int)strlen(src);
  for( int i = 0; i<count; ++i )
    types[i] = (type==CT_CTYPE1) ? classify_ctype1((unsigned char)src[i]) : 0;
  return TRUE;
}

extern "C" EXPORT int LCMapStringA(DWORD locale, DWORD flags, LPCSTR src, int srclen, LPSTR dst, int dstlen) {
  (void)locale;
  if( srclen<0 )
    srclen = (int)strlen(src)+1;
  if( flags&LCMAP_UPPERCASE ) { // uppercase
    if( dst&&dstlen>0 ) {
      int n = srclen<dstlen ? srclen : dstlen;
      for( int i = 0; i<n; ++i )
        dst[i] = (src[i]>='a'&&src[i]<='z') ? src[i]-32 : src[i];
    }
  } else if( dst&&dstlen>0 ) {
    int n = srclen<dstlen ? srclen : dstlen;
    memcpy(dst, src, (size_t)n);
  }
  return srclen;
}

// Not in 1.exe but common; add to avoid link errors if needed
extern "C" EXPORT void Sleep(DWORD ms) {
  struct timespec deadline;
  clock_gettime(CLOCK_MONOTONIC, &deadline);
  deadline.tv_sec  += (time_t)(ms/1000);
  deadline.tv_nsec += (long)((ms%1000)*1000000L);
  if( deadline.tv_nsec>=1000000000L ) {
    deadline.tv_sec++;
    deadline.tv_nsec -= 1000000000L;
  }
  // Use absolute-time sleep so EINTR restarts don't overshoot
  while( clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL)==EINTR )
    ;
}

// ---------------------------------------------------------------------------
// A-variant file/directory functions
// ---------------------------------------------------------------------------
static HANDLE find_first_posix(const char* posix, WIN32_FIND_DATAA* pfd) {
  FindCtx* ctx = NULL;
  struct dirent* ent = find_ctx_open(posix, &ctx);
  if( !ent )
    return INVALID_HANDLE_VALUE;
  char fullpath[PATH_MAX];
  path_join(fullpath, sizeof(fullpath), ctx->dirpath, ent->d_name);
  fill_find_data_a(pfd, fullpath, ent->d_name);
  HANDLE hret = handle_alloc_find(ctx);
  if( hret==INVALID_HANDLE_VALUE ) {
    closedir(ctx->dir);
    free(ctx);
  }
  return hret;
}

extern "C" EXPORT HANDLE FindFirstFileA(LPCSTR pattern, WIN32_FIND_DATAA* pfd) {
  char posix[PATH_MAX];
  win_path_to_posix(pattern, posix, sizeof(posix));
  return find_first_posix(posix, pfd);
}

extern "C" EXPORT BOOL FindNextFileA(HANDLE h, WIN32_FIND_DATAA* pfd) {
  FindCtx* ctx = get_find_ctx(h);   // retained; safe against concurrent FindClose
  if( !ctx ) return FALSE;
  struct dirent* ent;
  BOOL found = FALSE;
  while( (ent = readdir(ctx->dir))!=NULL ) {
    if( ent->d_name[0]=='.'&&(!ent->d_name[1]||ent->d_name[1]=='.') )
      continue;
    if( fnmatch(ctx->glob, ent->d_name, FNM_NOESCAPE)!=0 )
      continue;
    char fullpath[PATH_MAX];
    path_join(fullpath, sizeof(fullpath), ctx->dirpath, ent->d_name);
    fill_find_data_a(pfd, fullpath, ent->d_name);
    found = TRUE;
    break;
  }
  if( !found ) SET_LAST_ERROR(ERROR_NO_MORE_FILES);
  release_find_ctx(ctx);
  return found;
}

extern "C" EXPORT HANDLE CreateFileA(LPCSTR name, DWORD access, DWORD share, SECURITY_ATTRIBUTES* sa, DWORD disp, DWORD flags, HANDLE tmpl) {
  (void)share;
  (void)sa;
  (void)flags;
  (void)tmpl;
  // Map Windows console device names to stdin/stdout
  if( name&&(strcasecmp(name, "CONIN$")==0||strcasecmp(name, "CONOUT$")==0||strcasecmp(name, "CON")==0) ) {
    bool is_out = strcasecmp(name, "CONOUT$")==0;
    int fd = dup(is_out ? 1 : 0);
    log_always("[SHIM] CreateFileA(\"%s\", acc=0x%x, disp=%u) -> fd=%d (caller=%p)\n", name, access, disp, fd, __builtin_return_address(0));
    if( fd<0 ) {
      set_errno_error();
      return INVALID_HANDLE_VALUE;
    }
    HANDLE hret = handle_alloc_file(fd);
    if( hret==INVALID_HANDLE_VALUE )
      close(fd);
    return hret;
  }
  char posix[PATH_MAX];
  win_path_to_posix(name, posix, sizeof(posix));
  int oflags = make_open_flags(access, disp);
  int fd = open(posix, oflags, 0666);
  log_always("[SHIM] CreateFileA(\"%s\", acc=0x%x, disp=%u) -> fd=%d (caller=%p)\n", posix, access, disp, fd, __builtin_return_address(0));
  if( fd<0 ) {
    set_errno_error();
    return INVALID_HANDLE_VALUE;
  }
  HANDLE hret = handle_alloc_file(fd);
  if( hret==INVALID_HANDLE_VALUE )
    close(fd);
  return hret;
}

extern "C" EXPORT BOOL DeleteFileA(LPCSTR path) {
  char posix[PATH_MAX];
  win_path_to_posix(path, posix, sizeof(posix));
  if( unlink(posix)<0 ) {
    set_errno_error();
    return FALSE;
  }
  return TRUE;
}

extern "C" EXPORT BOOL SetFileAttributesA(LPCSTR path, DWORD attrs) {
  char posix[PATH_MAX];
  win_path_to_posix(path, posix, sizeof(posix));
  if( attrs&FILE_ATTRIBUTE_READONLY ) {
    struct stat st;
    if( stat(posix, &st)<0 ) {
      set_errno_error();
      return FALSE;
    }
    chmod(posix, st.st_mode&~(S_IWUSR|S_IWGRP|S_IWOTH));
  }
  return TRUE;
}

extern "C" EXPORT DWORD GetCurrentDirectoryA(DWORD size, LPSTR buf) {
  if( !buf||size==0 ) {
    char* tmp = getcwd(NULL, 0);
    if( !tmp ) return 0;
    DWORD n = (DWORD)(strlen(tmp)+1);
    free(tmp);
    return n;
  }
  if( !getcwd(buf, size) ) {
    set_errno_error();
    return 0;
  }
  return (DWORD)strlen(buf);
}

extern "C" EXPORT DWORD GetModuleFileNameA(HANDLE h, LPSTR buf, DWORD size) {
  if( size==0 ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return 0;
  }
  if( h==NULL||h==MAIN_IMAGE_MODULE ) {
    ssize_t n = readlink("/proc/self/exe", buf, size-1);
    if( n<0 ) { set_errno_error(); return 0; }
    buf[n] = '\0';
    return (DWORD)n;
  }
  // Loaded module: resolve via dladdr
  int idx = handle_to_idx(h);
  void* dlh = (idx>=0&&g_handles[idx].kind==H_MODULE) ? g_handles[idx].dlhandle : NULL;
  if( dlh ) {
    void* sym = dlsym(dlh, "_init");
    if( !sym ) sym = dlh;
    Dl_info info;
    if( dladdr(sym, &info)&&info.dli_fname ) {
      strncpy(buf, info.dli_fname, size-1);
      buf[size-1] = '\0';
      return (DWORD)strlen(buf);
    }
  }
  buf[0] = '\0';
  return 0;
}

extern "C" EXPORT HANDLE LoadLibraryA(LPCSTR name) {
  uint16_t wbuf[PATH_MAX];
  utf8_to_wchar(name, wbuf, PATH_MAX);
  return LoadLibraryExW(wbuf, NULL, 0);
}

// ---------------------------------------------------------------------------
// SetFilePointer (non-Ex), SetFileTime, SetEndOfFile
// ---------------------------------------------------------------------------
extern "C" EXPORT DWORD SetFilePointer(HANDLE h, LONG dist, LONG* disthi, DWORD method) {
  int fd = get_fd(h);
  if( fd<0 )
    return (DWORD)-1;
  int64_t offset = dist;
  if( disthi )
    offset |= ((int64_t)*disthi<<32);
  int whence = (method==FILE_BEGIN) ? SEEK_SET : (method==FILE_CURRENT) ? SEEK_CUR : SEEK_END;
  off_t r = lseek(fd, (off_t)offset, whence);
  if( r<0 ) {
    set_errno_error();
    return (DWORD)-1;
  }
  if( disthi )
    *disthi = (LONG)(r>>32);
  return (DWORD)(r&0xFFFFFFFF);
}

extern "C" EXPORT BOOL SetEndOfFile(HANDLE h) {
  int fd = get_fd(h);
  if( fd<0 )
    return FALSE;
  off_t pos = lseek(fd, 0, SEEK_CUR);
  if( pos<0 ) {
    set_errno_error();
    return FALSE;
  }
  if( ftruncate(fd, pos)<0 ) {
    set_errno_error();
    return FALSE;
  }
  return TRUE;
}

extern "C" EXPORT BOOL SetFileTime(HANDLE h, const FILETIME* ctime, const FILETIME* atime, const FILETIME* mtime) {
  int fd = get_fd(h);
  if( fd<0 )
    return FALSE;
  struct timespec times[2] = {};
  auto ft_to_ts = [](const FILETIME* ft, struct timespec &ts) {
                    if( !ft ) {
                      ts.tv_nsec = UTIME_OMIT;
                      return;
                    }
                    uint64_t v = ft_to_u64(*ft);
                    if( v<FILETIME_EPOCH ) {
                      ts.tv_sec = 0;
                      ts.tv_nsec = 0;
                      return;
                    }
                    v -= FILETIME_EPOCH;
                    ts.tv_sec = (time_t)(v/10000000ULL);
                    ts.tv_nsec = (long)((v%10000000ULL)*100);
                  };
  ft_to_ts(atime, times[0]);
  ft_to_ts(mtime, times[1]);
  futimens(fd, times);
  (void)ctime;
  return TRUE;
}

extern "C" EXPORT BOOL FileTimeToDosDateTime(const FILETIME* ft, WORD* fatdate, WORD* fattime) {
  if( !ft||!fatdate||!fattime )
    return FALSE;
  uint64_t v = ft_to_u64(*ft);
  if( v<FILETIME_EPOCH ) {
    *fatdate = *fattime = 0;
    return FALSE;
  }
  v -= FILETIME_EPOCH;
  time_t t = (time_t)(v/10000000ULL);
  struct tm tm;
  gmtime_r(&t, &tm);
  // DOS epoch starts 1980; clamp pre-1980 dates to avoid WORD wrap
  if( tm.tm_year<80 ) {
    *fatdate = *fattime = 0;
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  *fatdate = (WORD)(((tm.tm_year-80)<<9)|((tm.tm_mon+1)<<5)|tm.tm_mday);
  *fattime = (WORD)((tm.tm_hour<<11)|(tm.tm_min<<5)|(tm.tm_sec>>1));
  return TRUE;
}

extern "C" EXPORT BOOL DosDateTimeToFileTime(WORD fatdate, WORD fattime, FILETIME* ft) {
  if( !ft )
    return FALSE;
  struct tm tm = {};
  tm.tm_year = ((fatdate>>9)&0x7f)+80;
  tm.tm_mon = ((fatdate>>5)&0x0f)-1;
  tm.tm_mday = fatdate&0x1f;
  tm.tm_hour = (fattime>>11)&0x1f;
  tm.tm_min = (fattime>>5)&0x3f;
  tm.tm_sec = (fattime&0x1f)<<1;
  time_t t = timegm(&tm);
  uint64_t v = (uint64_t)t*10000000ULL+FILETIME_EPOCH;
  *ft = u64_to_ft(v);
  return TRUE;
}

// ---------------------------------------------------------------------------
// FLS (Fiber Local Storage) — implemented via per-thread array + free bitset
// ---------------------------------------------------------------------------
#define FLS_MAX_SLOTS 64
static __thread void* g_fls[FLS_MAX_SLOTS];
static uint64_t g_fls_used = 0;           // bitset of allocated slots
static pthread_mutex_t g_fls_mu = PTHREAD_MUTEX_INITIALIZER;

extern "C" EXPORT DWORD FlsAlloc(void* callback) {
  (void)callback;
  pthread_mutex_lock(&g_fls_mu);
  DWORD idx = 0xFFFFFFFF;
  for( DWORD i = 0; i<FLS_MAX_SLOTS; ++i ) {
    if( !(g_fls_used&(1ULL<<i)) ) {
      g_fls_used |= (1ULL<<i);
      idx = i;
      break;
    }
  }
  pthread_mutex_unlock(&g_fls_mu);
  log_always("[SHIM] FlsAlloc() -> idx=%u\n", idx);
  return idx;
}

extern "C" EXPORT BOOL FlsFree(DWORD idx) {
  if( idx>=FLS_MAX_SLOTS ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  pthread_mutex_lock(&g_fls_mu);
  g_fls_used &= ~(1ULL<<idx);
  pthread_mutex_unlock(&g_fls_mu);
  return TRUE;
}

extern "C" EXPORT LPVOID FlsGetValue(DWORD idx) {
  SET_LAST_ERROR(0);
  if( idx>=FLS_MAX_SLOTS ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return NULL;
  }
  void* v = g_fls[idx];
  log_always("[SHIM] FlsGetValue(idx=%u) -> %p\n", idx, v);
  return v;
}

extern "C" EXPORT BOOL FlsSetValue(DWORD idx, LPVOID val) {
  if( idx>=FLS_MAX_SLOTS ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  g_fls[idx] = val;
  log_always("[SHIM] FlsSetValue(idx=%u, val=%p)\n", idx, val);
  return TRUE;
}

// ---------------------------------------------------------------------------
// Locale / GetLocaleInfoA
// ---------------------------------------------------------------------------
extern "C" EXPORT int GetLocaleInfoA(DWORD locale, DWORD lctype, LPSTR buf, int size) {
  (void)locale;
  const char* val = "";
  switch( lctype&0xffff ) {
  case 0x0003: val = "1252";  break; // LOCALE_IDEFAULTANSICODEPAGE
  case 0x0005: val = "437";   break; // LOCALE_IDEFAULTCODEPAGE (OEM)
  case 0x0059: val = "en";    break; // LOCALE_SISO639LANGNAME
  case 0x005A: val = "US";    break; // LOCALE_SISO3166CTRYNAME
  case 0x1004: val = "UTF-8"; break; // LOCALE_IDEFAULTMACCODEPAGE
  default: break;
  }
  if( !buf||size==0 )
    return (int)strlen(val)+1;
  strncpy(buf, val, size-1);
  buf[size-1] = '\0';
  return (int)strlen(buf)+1;
}

// Expand Windows positional escapes (%1!s! %2!d! etc.) from a va_list.
// Supports up to 9 positional args; reads them from args in declaration order.
static DWORD format_message_expand(const char* msg, LPSTR buf, DWORD size, va_list* args) {
  // Pre-fetch up to 9 args as void* — safe for s/d/u on x86-64 ABI
  void* argp[9] = {};
  va_list ap;
  if( args ) {
    va_copy(ap, *args);
    for( int i = 0; i<9; i++ )
      argp[i] = va_arg(ap, void*);
    va_end(ap);
  }
  DWORD out = 0;
  for( const char* p = msg; *p&&out<size-1; p++ ) {
    if( p[0]=='%'&&p[1]>='1'&&p[1]<='9' ) {
      int idx = p[1]-'1';
      p += 2;
      char fmt[16] = "s";
      if( *p=='!' ) {
        p++;
        int fi = 0;
        while( *p&&*p!='!'&&fi<(int)sizeof(fmt)-1 )
          fmt[fi++] = *p++;
        fmt[fi] = '\0';
        if( *p=='!' ) p++;
        p--; // compensate for outer loop increment
      } else {
        p--; // just %N with no !fmt!
      }
      char fmtbuf[20];
      fmtbuf[0] = '%';
      strncpy(fmtbuf+1, fmt, sizeof(fmtbuf)-2);
      fmtbuf[sizeof(fmtbuf)-1] = '\0';
      char sub[256];
      snprintf(sub, sizeof(sub), fmtbuf, argp[idx]);
      for( const char* s = sub; *s&&out<size-1; s++ )
        buf[out++] = *s;
    } else if( p[0]=='%'&&p[1]=='%' ) {
      buf[out++] = '%';
      p++;
    } else {
      buf[out++] = *p;
    }
  }
  buf[out] = '\0';
  return out;
}

extern "C" EXPORT DWORD FormatMessageA(DWORD flags, LPCVOID src, DWORD msgId, DWORD lang, LPSTR buf, DWORD size, va_list* args) {
  (void)flags; (void)src; (void)lang;
  // Look up a few common Win32 codes; fall back to "Error N"
  static const struct { DWORD code; const char* msg; } table[] = {
    {0,   "The operation completed successfully."},
    {2,   "The system cannot find the file specified."},
    {3,   "The system cannot find the path specified."},
    {5,   "Access is denied."},
    {6,   "The handle is invalid."},
    {8,   "Not enough memory resources are available."},
    {87,  "The parameter is incorrect."},
    {183, "Cannot create a file when that file already exists."},
  };
  const char* msg = NULL;
  for( size_t i = 0; i<sizeof(table)/sizeof(table[0]); ++i ) {
    if( table[i].code==msgId ) { msg = table[i].msg; break; }
  }
  char fallback[64];
  if( !msg ) {
    snprintf(fallback, sizeof(fallback), "Error %u", (unsigned)msgId);
    msg = fallback;
  }
  if( !buf||size==0 )
    return 0;
  return format_message_expand(msg, buf, size, args);
}

// ---------------------------------------------------------------------------
// Console misc
// ---------------------------------------------------------------------------
// INPUT_RECORD layout (Windows x64 ABI, sizeof=20):
//  +0  WORD  EventType        (1 = KEY_EVENT)
//  +2  WORD  padding
//  +4  DWORD bKeyDown
//  +8  WORD  wRepeatCount
//  +10 WORD  wVirtualKeyCode
//  +12 WORD  wVirtualScanCode
//  +14 WORD  uChar (AsciiChar in low byte)
//  +16 DWORD dwControlKeyState
#define INPUT_RECORD_SIZE 20

extern "C" EXPORT BOOL ReadConsoleInputA(HANDLE h, void* buf, DWORD count, DWORD* nread) {
  if( nread ) *nread = 0;
  if( !buf||count==0 ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }
  int idx = handle_to_idx(h);
  int fd = (idx>=0 && g_handles[idx].kind==H_FILE) ? g_handles[idx].fd : STDIN_FILENO;
  char ch;
  ssize_t n;
  do {
    n = read(fd, &ch, 1);
  } while( n<0&&errno==EINTR );
  if( n<=0 ) return FALSE;
  uint8_t* rec = (uint8_t*)buf;
  memset(rec, 0, INPUT_RECORD_SIZE);
  *(uint16_t*)(rec+0)  = 0x0001;              // KEY_EVENT
  *(uint32_t*)(rec+4)  = 1;                   // bKeyDown = TRUE
  *(uint16_t*)(rec+8)  = 1;                   // wRepeatCount
  *(uint16_t*)(rec+14) = (uint16_t)(uint8_t)ch; // AsciiChar
  if( nread ) *nread = 1;
  return TRUE;
}

extern "C" EXPORT BOOL SetHandleCount(DWORD n) {
  (void)n;
  return TRUE;
}