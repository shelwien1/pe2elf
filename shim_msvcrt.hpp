#pragma once
// msvcrt_ shims — included from shim.cpp.
// All helpers and exports for msvcrt.dll functions.

// ---------------------------------------------------------------------------
// Helpers for msvcrt_ shims (file-scope, not exported)
// ---------------------------------------------------------------------------

static int win_file_to_fd(void* f) {
  uint8_t* fp = (uint8_t*)f;
  if( fp >= g_fake_iob && fp < g_fake_iob + 144 ) {
    size_t ent = ((size_t)(fp - g_fake_iob) / 48) * 48;
    return *(int*)(g_fake_iob + ent + 28);
  }
  return fileno((FILE*)f);
}

// MS ABI va_list is char* on x86-64; each arg is 8-byte aligned.
// Advance by 8 to consume one argument.
#define MSVA_ARG_LL(ap)  (*(long long*)((ap) += 8, (ap) - 8))
#define MSVA_ARG_ULL(ap) (*(unsigned long long*)((ap) += 8, (ap) - 8))
#define MSVA_ARG_DBL(ap) (*(double*)((ap) += 8, (ap) - 8))
#define MSVA_ARG_PTR(ap) (*(void**)((ap) += 8, (ap) - 8))

// Format string parser for MS ABI variadic args passed as char*.
// Caller must have done __builtin_ms_va_start before passing (char*)ap.
// Writes formatted output into buf[bufsz], NUL-terminates, returns byte count.
static int ms_vformat(char* outbuf, int bufsz, const char* fmt, char* ap) {
  if( !fmt ) return 0;
  int out = 0;
  for( const char* p = fmt; *p && out < bufsz - 512; ) {
    if( *p != '%' ) { outbuf[out++] = *p++; continue; }
    p++;
    if( !*p ) break;
    if( *p == '%' ) { outbuf[out++] = '%'; p++; continue; }
    char fs[64]; int fsi = 0; fs[fsi++] = '%';
    while( *p && (*p=='-'||*p=='+'||*p==' '||*p=='#'||*p=='0') ) fs[fsi++] = *p++;
    if( *p == '*' ) {
      int w = (int)MSVA_ARG_LL(ap);
      fsi += snprintf(fs + fsi, sizeof(fs) - fsi, "%d", w); p++;
    } else { while( *p >= '0' && *p <= '9' ) fs[fsi++] = *p++; }
    if( *p == '.' ) { fs[fsi++] = *p++;
      if( *p == '*' ) {
        int pr = (int)MSVA_ARG_LL(ap);
        fsi += snprintf(fs + fsi, sizeof(fs) - fsi, "%d", pr); p++;
      } else { while( *p >= '0' && *p <= '9' ) fs[fsi++] = *p++; }
    }
    int ll = 0;
    if( p[0]=='l' && p[1]=='l' ) { ll = 1; p += 2; }
    else if( p[0]=='l' ) { p++; }
    else if( p[0]=='h' && p[1]=='h' ) { p += 2; }
    else if( p[0]=='h' ) { p++; }
    else if( p[0]=='z' || p[0]=='j' || p[0]=='t' ) { ll = 1; p++; }
    else if( p[0]=='I' && p[1]=='6' && p[2]=='4' ) { ll = 1; p += 3; }
    else if( p[0]=='I' && p[1]=='3' && p[2]=='2' ) { p += 3; }
    else if( p[0]=='I' ) { ll = 1; p++; }
    char conv = *p++; char tmp[512]; tmp[0] = '\0';
    switch( conv ) {
    case 'd': case 'i': {
      long long v = MSVA_ARG_LL(ap);
      if( ll ) { fs[fsi++]='l'; fs[fsi++]='l'; fs[fsi++]='d'; fs[fsi]='\0'; snprintf(tmp,sizeof(tmp),fs,v); }
      else { fs[fsi++]='d'; fs[fsi]='\0'; snprintf(tmp,sizeof(tmp),fs,(int)v); }
      break; }
    case 'u': case 'o': case 'x': case 'X': {
      unsigned long long v = MSVA_ARG_ULL(ap);
      if( ll ) { fs[fsi++]='l'; fs[fsi++]='l'; fs[fsi++]=conv; fs[fsi]='\0'; snprintf(tmp,sizeof(tmp),fs,v); }
      else { fs[fsi++]=conv; fs[fsi]='\0'; snprintf(tmp,sizeof(tmp),fs,(unsigned int)v); }
      break; }
    case 'f': case 'F': case 'e': case 'E': case 'g': case 'G': case 'a': case 'A': {
      double v = MSVA_ARG_DBL(ap);
      fs[fsi++] = conv; fs[fsi] = '\0'; snprintf(tmp, sizeof(tmp), fs, v); break; }
    case 's': {
      const char* v = (const char*)MSVA_ARG_PTR(ap);
      fs[fsi++] = 's'; fs[fsi] = '\0'; snprintf(tmp, sizeof(tmp), fs, v ? v : "(null)"); break; }
    case 'S': {
      const uint16_t* v = (const uint16_t*)MSVA_ARG_PTR(ap);
      if( v ) { wchar_to_utf8(v, tmp, sizeof(tmp)); } break; }
    case 'c': {
      int v = (int)MSVA_ARG_LL(ap); tmp[0] = (char)v; tmp[1] = '\0'; break; }
    case 'p': {
      void* v = MSVA_ARG_PTR(ap); snprintf(tmp, sizeof(tmp), "%p", v); break; }
    case 'n': {
      int* v = (int*)MSVA_ARG_PTR(ap); if( v ) *v = out; break; }
    default: tmp[0] = conv; tmp[1] = '\0'; break;
    }
    int tlen = (int)strlen(tmp);
    if( out + tlen > bufsz - 1 ) tlen = bufsz - 1 - out;
    if( tlen > 0 ) { memcpy(outbuf + out, tmp, tlen); out += tlen; }
  }
  outbuf[out] = '\0';
  return out;
}

static int ms_vfprintf_fd(int fd, const char* fmt, char* ap) {
  char outbuf[65536];
  int out = ms_vformat(outbuf, (int)sizeof(outbuf), fmt, ap);
  ssize_t r = write(fd, outbuf, out);
  return r < 0 ? -1 : (int)r;
}

// ---------------------------------------------------------------------------
// msvcrt_ data variable exports
// ---------------------------------------------------------------------------
int    msvcrt__commode  __attribute__((visibility("default"))) = 0;
int    msvcrt__fmode    __attribute__((visibility("default"))) = 0;
char** msvcrt___initenv __attribute__((visibility("default"))) = nullptr;

// ---------------------------------------------------------------------------
// msvcrt_ function exports
// ---------------------------------------------------------------------------

// CRT init/cleanup
extern "C" EXPORT void msvcrt___set_app_type(int /*t*/)      {}
extern "C" EXPORT void msvcrt___setusermatherr(void* /*fn*/) {}
extern "C" EXPORT void msvcrt__amsg_exit(int /*n*/)          { _exit(255); }
extern "C" EXPORT void msvcrt__cexit(void)                   {}

// CRT locking — one recursive mutex per lock ID (Windows CRT has per-ID locks
// and the same thread can acquire different IDs in a nested call chain).
#define CRT_NLOCK 32
static pthread_mutex_t g_crt_locks[CRT_NLOCK];
static pthread_once_t  g_crt_locks_once = PTHREAD_ONCE_INIT;
static void crt_locks_init(void) {
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  for( int i = 0; i < CRT_NLOCK; i++ )
    pthread_mutex_init(&g_crt_locks[i], &attr);
  pthread_mutexattr_destroy(&attr);
}
extern "C" EXPORT void msvcrt__lock(int n) {
  pthread_once(&g_crt_locks_once, crt_locks_init);
  if( n >= 0 && n < CRT_NLOCK ) pthread_mutex_lock(&g_crt_locks[n]);
}
extern "C" EXPORT void msvcrt__unlock(int n) {
  pthread_once(&g_crt_locks_once, crt_locks_init);
  if( n >= 0 && n < CRT_NLOCK ) pthread_mutex_unlock(&g_crt_locks[n]);
}

// errno
extern "C" EXPORT int* msvcrt__errno(void) { return &errno; }

// Locale / codepage
extern "C" EXPORT unsigned int msvcrt____lc_codepage_func(void) { return 0; }
extern "C" EXPORT int          msvcrt____mb_cur_max_func(void)  { return 1; }

// _initterm: call table of ms_abi function pointers
typedef void (WINAPI *crt_fn_t)(void);
extern "C" EXPORT void msvcrt__initterm(crt_fn_t* from, crt_fn_t* to) {
  for( crt_fn_t* fn = from; fn < to; fn++ )
    if( *fn ) (*fn)();
}

// __getmainargs
extern "C" EXPORT int msvcrt___getmainargs(int* argc, char*** argv, char*** envp,
                                            int /*expand*/, int* newmode) {
  if( argc )    *argc    = g_main_argc;
  if( argv )    *argv    = g_main_argv;
  if( envp )    *envp    = environ;
  if( newmode ) *newmode = 0;
  return 0;
}

// __iob_func: return fake Windows FILE array
extern "C" EXPORT void* msvcrt___iob_func(void) { return g_fake_iob; }

// SEH handler stub
extern "C" EXPORT int msvcrt___C_specific_handler(void*, void*, void*, void*) {
  return 1; // ExceptionContinueSearch
}

// stdio — cast ms_va_list (char*) to our helper
extern "C" EXPORT int msvcrt_fprintf(void* f, const char* fmt, ...) {
  __builtin_ms_va_list ap;
  __builtin_ms_va_start(ap, fmt);
  int r = ms_vfprintf_fd(win_file_to_fd(f), fmt, (char*)ap);
  __builtin_ms_va_end(ap);
  return r;
}

extern "C" EXPORT int msvcrt_vfprintf(void* f, const char* fmt, __builtin_ms_va_list ap) {
  return ms_vfprintf_fd(win_file_to_fd(f), fmt, (char*)ap);
}

extern "C" EXPORT int msvcrt_fputc(int c, void* f) {
  uint8_t b = (uint8_t)c;
  return write(win_file_to_fd(f), &b, 1) == 1 ? c : -1;
}

// libc pass-through wrappers (ABI conversion: ms_abi caller → sysv libc)
extern "C" EXPORT void*  msvcrt_malloc(size_t n)                          { return malloc(n); }
extern "C" EXPORT void   msvcrt_free(void* p)                             { free(p); }
extern "C" EXPORT void*  msvcrt_calloc(size_t n, size_t s)               { return calloc(n, s); }
extern "C" EXPORT void*  msvcrt_memcpy(void* d, const void* s, size_t n) { return memcpy(d, s, n); }
extern "C" EXPORT size_t msvcrt_strlen(const char* s)                     { return strlen(s); }
extern "C" EXPORT int    msvcrt_strncmp(const char* a, const char* b, size_t n) { return strncmp(a, b, n); }
extern "C" EXPORT char*  msvcrt_strerror(int e)                           { return strerror(e); }
extern "C" EXPORT void   msvcrt_abort(void)                               { abort(); }
extern "C" EXPORT int    msvcrt_atexit(void (*fn)(void))                  { return atexit(fn); }
extern "C" EXPORT void   msvcrt_exit(int code)                            { exit(code); }
extern "C" EXPORT void*  msvcrt_localeconv(void)                          { return (void*)localeconv(); }

extern "C" EXPORT void* msvcrt_signal(int sig, void* handler) {
  // Map Windows SIGABRT (22) to Linux SIGABRT (6)
  int lsig = (sig == 22) ? SIGABRT : sig;
  struct sigaction sa = {}, old = {};
  if( handler == (void*)0 )      sa.sa_handler = SIG_DFL;
  else if( handler == (void*)1 ) sa.sa_handler = SIG_IGN;
  else                            sa.sa_handler = (void(*)(int))handler;
  sigaction(lsig, &sa, &old);
  return (void*)old.sa_handler;
}

extern "C" EXPORT size_t msvcrt_wcslen(const uint16_t* s) {
  if( !s ) return 0;
  const uint16_t* p = s;
  while( *p ) p++;
  return (size_t)(p - s);
}

extern "C" EXPORT char* msvcrt_strcpy(char* dst, const char* src) { return strcpy(dst, src); }

extern "C" EXPORT uint16_t* msvcrt_wcscpy(uint16_t* dst, const uint16_t* src) {
  uint16_t* d = dst;
  while( (*d++ = *src++) ) {}
  return dst;
}

extern "C" EXPORT int msvcrt___wgetmainargs(int* argc, uint16_t*** wargv, uint16_t*** wenvp,
                                             int /*expand*/, int* newmode) {
  static uint16_t** s_wargv = nullptr;
  static uint16_t** s_wenvp = nullptr;
  if( !s_wargv && g_main_argc > 0 ) {
    s_wargv = (uint16_t**)calloc(g_main_argc + 1, sizeof(uint16_t*));
    for( int i = 0; i < g_main_argc; i++ ) {
      size_t len = strlen(g_main_argv[i]) + 1;
      s_wargv[i] = (uint16_t*)malloc(len * 2);
      for( size_t j = 0; j < len; j++ )
        s_wargv[i][j] = (uint16_t)(uint8_t)g_main_argv[i][j];
    }
  }
  if( !s_wenvp ) {
    int nenv = 0;
    while( environ[nenv] ) nenv++;
    s_wenvp = (uint16_t**)calloc(nenv + 1, sizeof(uint16_t*));
    for( int i = 0; i < nenv; i++ ) {
      size_t len = strlen(environ[i]) + 1;
      s_wenvp[i] = (uint16_t*)malloc(len * 2);
      for( size_t j = 0; j < len; j++ )
        s_wenvp[i][j] = (uint16_t)(uint8_t)environ[i][j];
    }
  }
  if( argc )   *argc   = g_main_argc;
  if( wargv )  *wargv  = s_wargv;
  if( wenvp )  *wenvp  = s_wenvp;
  if( newmode ) *newmode = 0;
  return 0;
}

// ---------------------------------------------------------------------------
// msvcrt data variables
// ---------------------------------------------------------------------------
// _acmdln mirrors GetCommandLineA (g_cmdline is the same static buffer)
char* msvcrt__acmdln __attribute__((visibility("default"))) = g_cmdline;

// ---------------------------------------------------------------------------
// CRT lifecycle extras
// ---------------------------------------------------------------------------
extern "C" EXPORT void msvcrt___lconv_init(void) {}

// _onexit / __dllonexit: register fn via atexit, return fn on success
extern "C" EXPORT void* msvcrt__onexit(void* fn) {
  if( fn ) atexit((void(*)(void))fn);
  return fn;
}
extern "C" EXPORT void* msvcrt___dllonexit(void* fn, void** /*pbegin*/, void** /*pend*/) {
  if( fn ) atexit((void(*)(void))fn);
  return fn;
}

// ---------------------------------------------------------------------------
// Time functions (_time64 family — time_t is 64-bit on Linux x86-64)
// ---------------------------------------------------------------------------
extern "C" EXPORT int64_t msvcrt__time64(int64_t* t) {
  int64_t now = (int64_t)time(nullptr);
  if( t ) *t = now;
  return now;
}
extern "C" EXPORT struct tm* msvcrt__gmtime64(const int64_t* t) {
  time_t tt = t ? (time_t)*t : (time_t)time(nullptr);
  static __thread struct tm buf;
  return gmtime_r(&tt, &buf);
}
extern "C" EXPORT struct tm* msvcrt__localtime64(const int64_t* t) {
  time_t tt = t ? (time_t)*t : (time_t)time(nullptr);
  static __thread struct tm buf;
  return localtime_r(&tt, &buf);
}
extern "C" EXPORT int64_t msvcrt__mktime64(struct tm* tm_val) {
  return (int64_t)mktime(tm_val);
}
extern "C" EXPORT size_t msvcrt_strftime(char* buf, size_t bufsz, const char* fmt, const struct tm* tm_val) {
  return strftime(buf, bufsz, fmt, tm_val);
}

// ---------------------------------------------------------------------------
// stdio — MS ABI variadic wrappers
// ---------------------------------------------------------------------------
extern "C" EXPORT int msvcrt_printf(const char* fmt, ...) {
  __builtin_ms_va_list ap;
  __builtin_ms_va_start(ap, fmt);
  int r = ms_vfprintf_fd(STDOUT_FILENO, fmt, (char*)ap);
  __builtin_ms_va_end(ap);
  return r;
}
extern "C" EXPORT int msvcrt_sprintf(char* buf, const char* fmt, ...) {
  __builtin_ms_va_list ap;
  __builtin_ms_va_start(ap, fmt);
  char tmp[65536];
  int n = ms_vformat(tmp, (int)sizeof(tmp), fmt, (char*)ap);
  __builtin_ms_va_end(ap);
  if( buf ) { memcpy(buf, tmp, (size_t)n); buf[n] = '\0'; }
  return n;
}

// stdio — file I/O using win_file_to_fd
extern "C" EXPORT size_t msvcrt_fwrite(const void* buf, size_t sz, size_t count, void* f) {
  if( !buf || sz == 0 || count == 0 ) return 0;
  ssize_t r = write(win_file_to_fd(f), buf, sz * count);
  return r < 0 ? 0 : (size_t)r / sz;
}
extern "C" EXPORT char* msvcrt_fgets(char* buf, int n, void* f) {
  if( !buf || n <= 0 ) return nullptr;
  int fd = win_file_to_fd(f);
  int i = 0;
  while( i < n - 1 ) {
    char c; ssize_t r;
    do { r = read(fd, &c, 1); } while( r < 0 && errno == EINTR );
    if( r <= 0 ) break;
    buf[i++] = c;
    if( c == '\n' ) break;
  }
  if( i == 0 ) return nullptr;
  buf[i] = '\0';
  return buf;
}

// stdio — simple pass-throughs
extern "C" EXPORT int    msvcrt_puts(const char* s)    { return puts(s); }
extern "C" EXPORT int    msvcrt_putchar(int c)          { return putchar(c); }
extern "C" EXPORT int    msvcrt_remove(const char* p)   { return remove(p); }

// string / memory pass-throughs
extern "C" EXPORT void*  msvcrt_memmove(void* d, const void* s, size_t n) { return memmove(d, s, n); }
extern "C" EXPORT void*  msvcrt_memset(void* d, int c, size_t n)          { return memset(d, c, n); }
extern "C" EXPORT int    msvcrt_strcmp(const char* a, const char* b)       { return strcmp(a, b); }
extern "C" EXPORT int    msvcrt_tolower(int c)                             { return tolower(c); }
