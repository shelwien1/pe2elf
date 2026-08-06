#pragma once
// msvcrt_ shims — included from shim32.cpp.
// All helpers and exports for msvcrt.dll functions.
//
// Everything here is __cdecl, not __stdcall: that is the convention the
// whole x86 CRT export surface uses.  Declaring these stdcall would make
// both sides pop the arguments and unbalance the stack on the first call.

// ---------------------------------------------------------------------------
// Helpers for msvcrt_ shims (file-scope, not exported)
// ---------------------------------------------------------------------------

static int win_file_to_fd(void* f) {
  uint8_t* fp = (uint8_t*)f;
  if( fp >= g_fake_iob && fp < g_fake_iob + sizeof(g_fake_iob) ) {
    size_t ent = ((size_t)(fp - g_fake_iob) / WIN_IOB_STRIDE) * WIN_IOB_STRIDE;
    return *(int*)(g_fake_iob + ent + WIN_IOB_FILE_OFF);
  }
  return fileno((FILE*)f);
}

// Format-string parser.  i386 has exactly one va_list, so unlike the x86-64
// shim (which hand-rolled an 8-byte-per-argument walk because the MS x64
// va_list differs from the SysV one) this can use plain va_arg.  Stack
// promotion — 4 bytes for int/pointer/long, 8 for long long/double — is
// handled by va_arg itself.
//
// Writes formatted output into buf[bufsz], NUL-terminates, returns byte count.
static int ms_vformat(char* outbuf, int bufsz, const char* fmt, va_list ap) {
  if( !fmt ) return 0;
  int out = 0;
  for( const char* p = fmt; *p && out < bufsz - 512; ) {
    if( *p != '%' ) { outbuf[out++] = *p++; continue; }
    p++;
    if( !*p ) break;
    if( *p == '%' ) { outbuf[out++] = '%'; p++; continue; }
    char fs[64]; int fsi = 0; fs[fsi++] = '%';
    while( *p && (*p=='-'||*p=='+'||*p==' '||*p=='#'||*p=='0') && fsi<(int)sizeof(fs)-1 ) fs[fsi++] = *p++;
    if( *p == '*' ) {
      int w = va_arg(ap, int);
      int n = snprintf(fs + fsi, sizeof(fs) - fsi, "%d", w);
      if( n > 0 ) fsi += n;
      if( fsi >= (int)sizeof(fs) ) fsi = (int)sizeof(fs) - 1;
      p++;
    } else { while( *p >= '0' && *p <= '9' && fsi<(int)sizeof(fs)-1 ) fs[fsi++] = *p++; }
    if( *p == '.' && fsi<(int)sizeof(fs)-1 ) { fs[fsi++] = *p++;
      if( *p == '*' ) {
        int pr = va_arg(ap, int);
        int n = snprintf(fs + fsi, sizeof(fs) - fsi, "%d", pr);
        if( n > 0 ) fsi += n;
        if( fsi >= (int)sizeof(fs) ) fsi = (int)sizeof(fs) - 1;
        p++;
      } else { while( *p >= '0' && *p <= '9' && fsi<(int)sizeof(fs)-1 ) fs[fsi++] = *p++; }
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
    // Leave room for up to 3 conversion chars + null terminator
    if( fsi > (int)sizeof(fs) - 5 ) fsi = (int)sizeof(fs) - 5;
    char conv = *p++; char tmp[512]; tmp[0] = '\0';
    switch( conv ) {
    case 'd': case 'i': {
      // The width matters here: on i386 an int occupies one 4-byte stack
      // slot and a long long occupies two, so va_arg has to be told which.
      if( ll ) { long long v = va_arg(ap, long long);
                 fs[fsi++]='l'; fs[fsi++]='l'; fs[fsi++]='d'; fs[fsi]='\0'; snprintf(tmp,sizeof(tmp),fs,v); }
      else     { int v = va_arg(ap, int);
                 fs[fsi++]='d'; fs[fsi]='\0'; snprintf(tmp,sizeof(tmp),fs,v); }
      break; }
    case 'u': case 'o': case 'x': case 'X': {
      if( ll ) { unsigned long long v = va_arg(ap, unsigned long long);
                 fs[fsi++]='l'; fs[fsi++]='l'; fs[fsi++]=conv; fs[fsi]='\0'; snprintf(tmp,sizeof(tmp),fs,v); }
      else     { unsigned int v = va_arg(ap, unsigned int);
                 fs[fsi++]=conv; fs[fsi]='\0'; snprintf(tmp,sizeof(tmp),fs,v); }
      break; }
    case 'f': case 'F': case 'e': case 'E': case 'g': case 'G': case 'a': case 'A': {
      double v = va_arg(ap, double);
      fs[fsi++] = conv; fs[fsi] = '\0'; snprintf(tmp, sizeof(tmp), fs, v); break; }
    case 's': {
      const char* v = va_arg(ap, const char*);
      fs[fsi++] = 's'; fs[fsi] = '\0'; snprintf(tmp, sizeof(tmp), fs, v ? v : "(null)"); break; }
    case 'S': {
      const uint16_t* v = va_arg(ap, const uint16_t*);
      if( v ) { wchar_to_utf8(v, tmp, sizeof(tmp)); } break; }
    case 'c': {
      int v = va_arg(ap, int); tmp[0] = (char)v; tmp[1] = '\0'; break; }
    case 'p': {
      void* v = va_arg(ap, void*); snprintf(tmp, sizeof(tmp), "%p", v); break; }
    case 'n': {
      int* v = va_arg(ap, int*); if( v ) *v = out; break; }
    default: tmp[0] = conv; tmp[1] = '\0'; break;
    }
    int tlen = (int)strlen(tmp);
    if( out + tlen > bufsz - 1 ) tlen = bufsz - 1 - out;
    if( tlen > 0 ) { memcpy(outbuf + out, tmp, tlen); out += tlen; }
  }
  outbuf[out] = '\0';
  return out;
}

static int ms_vfprintf_fd(int fd, const char* fmt, va_list ap) {
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
// _adjust_fdiv is the Pentium-FDIV-bug workaround flag the x86 CRT startup
// reads.  It is a data export, and 0 means "no workaround needed".
int    msvcrt__adjust_fdiv __attribute__((visibility("default"))) = 0;

// ---------------------------------------------------------------------------
// msvcrt_ function exports
// ---------------------------------------------------------------------------

// CRT init/cleanup
extern "C" EXPORT_CDECL void msvcrt___set_app_type(int /*t*/)      {}
extern "C" EXPORT_CDECL void msvcrt___setusermatherr(void* /*fn*/) {}
extern "C" EXPORT_CDECL void msvcrt__amsg_exit(int /*n*/)          { _exit(255); }
extern "C" EXPORT_CDECL void msvcrt__cexit(void)                   {}

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
extern "C" EXPORT_CDECL void msvcrt__lock(int n) {
  pthread_once(&g_crt_locks_once, crt_locks_init);
  if( n < 0 || n >= CRT_NLOCK ) {
    log_always("[SHIM] msvcrt__lock: ID %d out of range [0,%d)\n", n, CRT_NLOCK);
    return;
  }
  pthread_mutex_lock(&g_crt_locks[n]);
}
extern "C" EXPORT_CDECL void msvcrt__unlock(int n) {
  pthread_once(&g_crt_locks_once, crt_locks_init);
  if( n < 0 || n >= CRT_NLOCK ) {
    log_always("[SHIM] msvcrt__unlock: ID %d out of range [0,%d)\n", n, CRT_NLOCK);
    return;
  }
  pthread_mutex_unlock(&g_crt_locks[n]);
}

// errno
extern "C" EXPORT_CDECL int* msvcrt__errno(void) { return &errno; }

// Locale / codepage
extern "C" EXPORT_CDECL unsigned int msvcrt____lc_codepage_func(void) { return 0; }
extern "C" EXPORT_CDECL int          msvcrt____mb_cur_max_func(void)  { return 1; }

// _initterm: call table of CRT initializer function pointers (cdecl)
typedef void (CDECLAPI *crt_fn_t)(void);
extern "C" EXPORT_CDECL void msvcrt__initterm(crt_fn_t* from, crt_fn_t* to) {
  for( crt_fn_t* fn = from; fn < to; fn++ )
    if( *fn ) (*fn)();
}

// The x86 CRT startup reads _commode/_fmode/__initenv through accessor
// functions rather than importing the variables directly.
extern "C" EXPORT_CDECL int*    msvcrt___p__commode(void)  { return &msvcrt__commode; }
extern "C" EXPORT_CDECL int*    msvcrt___p__fmode(void)    { return &msvcrt__fmode; }
extern "C" EXPORT_CDECL char*** msvcrt___p___initenv(void) { return &msvcrt___initenv; }

// _controlfp / _control87 — x87 control word.  Report the CRT's default
// (_MCW_EM all masked, 53-bit precision, round-to-nearest) and ignore
// changes: the host FPU is already configured the way libc wants it, and no
// converted binary has needed a real control-word poke so far.
#define WIN_CW_DEFAULT 0x0009001Fu
extern "C" EXPORT_CDECL unsigned int msvcrt__controlfp(unsigned int newval, unsigned int mask) {
  (void)newval; (void)mask;
  return WIN_CW_DEFAULT;
}
extern "C" EXPORT_CDECL unsigned int msvcrt__control87(unsigned int newval, unsigned int mask) {
  (void)newval; (void)mask;
  return WIN_CW_DEFAULT;
}
extern "C" EXPORT_CDECL int msvcrt__set_error_mode(int mode) { (void)mode; return 0; }

// __getmainargs
extern "C" EXPORT_CDECL int msvcrt___getmainargs(int* argc, char*** argv, char*** envp,
                                            int /*expand*/, int* newmode) {
  if( argc )    *argc    = g_main_argc;
  if( argv )    *argv    = g_main_argv;
  if( envp )    *envp    = environ;
  if( newmode ) *newmode = 0;
  return 0;
}

// __iob_func: return fake Windows FILE array
extern "C" EXPORT_CDECL void* msvcrt___iob_func(void) { return g_fake_iob; }

// (__C_specific_handler is an x64/IA64-only entry point and has no i386
// equivalent; the x86 SEH surface lives in shim32_kernel32_except.hpp as
// _except_handler3/_except_handler4 + _global_unwind2/_local_unwind2.)

// stdio — variadics are cdecl on i386 and use the native va_list
extern "C" EXPORT_CDECL int msvcrt_fprintf(void* f, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int r = ms_vfprintf_fd(win_file_to_fd(f), fmt, ap);
  va_end(ap);
  return r;
}

extern "C" EXPORT_CDECL int msvcrt_vfprintf(void* f, const char* fmt, va_list ap) {
  return ms_vfprintf_fd(win_file_to_fd(f), fmt, ap);
}

extern "C" EXPORT_CDECL int msvcrt_fputc(int c, void* f) {
  uint8_t b = (uint8_t)c;
  return write(win_file_to_fd(f), &b, 1) == 1 ? c : -1;
}

// libc pass-through wrappers (both sides are cdecl on i386, so these are
// pure forwarding; they exist to give the msvcrt_ names something to bind to)
extern "C" EXPORT_CDECL void*  msvcrt_malloc(size_t n)                          { return malloc(n); }
extern "C" EXPORT_CDECL void   msvcrt_free(void* p)                             { free(p); }
extern "C" EXPORT_CDECL void*  msvcrt_calloc(size_t n, size_t s)               { return calloc(n, s); }
extern "C" EXPORT_CDECL void*  msvcrt_memcpy(void* d, const void* s, size_t n) { return memcpy(d, s, n); }
extern "C" EXPORT_CDECL size_t msvcrt_strlen(const char* s)                     { return strlen(s); }
extern "C" EXPORT_CDECL int    msvcrt_strncmp(const char* a, const char* b, size_t n) { return strncmp(a, b, n); }
extern "C" EXPORT_CDECL char*  msvcrt_strerror(int e)                           { return strerror(e); }
extern "C" EXPORT_CDECL void   msvcrt_abort(void)                               { abort(); }
extern "C" EXPORT_CDECL int    msvcrt_atexit(void (*fn)(void))                  { return atexit(fn); }
extern "C" EXPORT_CDECL void   msvcrt_exit(int code)                            { exit(code); }
extern "C" EXPORT_CDECL void   msvcrt__exit(int code)                           { _exit(code); }
extern "C" EXPORT_CDECL void*  msvcrt_localeconv(void)                          { return (void*)localeconv(); }

// On x86-64 this needed an ABI bridge (the Windows CRT signal handler is
// ms_abi, taking the signal in RCX, while a Linux handler is SysV and takes
// it in EDI).  On i386 both are plain cdecl(int), so the ABI trampoline
// collapses.  What remains is the *signal-number* remap: the handler must see
// the Windows number it registered with (SIGABRT is 22 on Windows, 6 here),
// so keep the per-signal table and the thin dispatcher.
typedef void (CDECLAPI *win_sighandler_t)(int);
static win_sighandler_t g_msvcrt_sighandlers[64] = {};
static int              g_msvcrt_winsig[64]      = {};

static void msvcrt_signal_trampoline(int sig) {
  if( sig<0||sig>=64 ) return;
  win_sighandler_t h = g_msvcrt_sighandlers[sig];
  int winsig = g_msvcrt_winsig[sig];
  if( h ) h(winsig);  // same convention on i386; only the number is remapped
}

extern "C" EXPORT_CDECL void* msvcrt_signal(int sig, void* handler) {
  // Map Windows SIGABRT (22) to Linux SIGABRT (6)
  int lsig = (sig == 22) ? SIGABRT : sig;
  if( lsig<0||lsig>=64 ) return (void*)-1;  // SIG_ERR
  struct sigaction sa = {}, old = {};
  win_sighandler_t prev = g_msvcrt_sighandlers[lsig];
  if( handler == (void*)0 ) {
    sa.sa_handler = SIG_DFL;
    g_msvcrt_sighandlers[lsig] = nullptr;
    g_msvcrt_winsig[lsig] = 0;
  } else if( handler == (void*)1 ) {
    sa.sa_handler = SIG_IGN;
    g_msvcrt_sighandlers[lsig] = nullptr;
    g_msvcrt_winsig[lsig] = 0;
  } else {
    g_msvcrt_sighandlers[lsig] = (win_sighandler_t)handler;
    g_msvcrt_winsig[lsig] = sig;  // remember the caller's (Windows) sig number
    sa.sa_handler = msvcrt_signal_trampoline;
  }
  sigaction(lsig, &sa, &old);
  // Hand back the previously-installed Windows handler if any; otherwise
  // whatever was registered out-of-band (SIG_DFL/SIG_IGN/raw sigaction).
  if( prev ) return (void*)prev;
  return (void*)old.sa_handler;
}

extern "C" EXPORT_CDECL size_t msvcrt_wcslen(const uint16_t* s) {
  if( !s ) return 0;
  const uint16_t* p = s;
  while( *p ) p++;
  return (size_t)(p - s);
}

extern "C" EXPORT_CDECL char* msvcrt_strcpy(char* dst, const char* src) { return strcpy(dst, src); }

extern "C" EXPORT_CDECL uint16_t* msvcrt_wcscpy(uint16_t* dst, const uint16_t* src) {
  uint16_t* d = dst;
  while( (*d++ = *src++) ) {}
  return dst;
}

extern "C" EXPORT_CDECL int msvcrt___wgetmainargs(int* argc, uint16_t*** wargv, uint16_t*** wenvp,
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
extern "C" EXPORT_CDECL void msvcrt___lconv_init(void) {}

// _onexit / __dllonexit: register fn via atexit, return fn on success
extern "C" EXPORT_CDECL void* msvcrt__onexit(void* fn) {
  if( fn ) atexit((void(*)(void))fn);
  return fn;
}
extern "C" EXPORT_CDECL void* msvcrt___dllonexit(void* fn, void** /*pbegin*/, void** /*pend*/) {
  if( fn ) atexit((void(*)(void))fn);
  return fn;
}

// ---------------------------------------------------------------------------
// Time functions (_time64 family — time_t is 64-bit on Linux x86-64)
// ---------------------------------------------------------------------------
extern "C" EXPORT_CDECL int64_t msvcrt__time64(int64_t* t) {
  int64_t now = (int64_t)time(nullptr);
  if( t ) *t = now;
  return now;
}
extern "C" EXPORT_CDECL struct tm* msvcrt__gmtime64(const int64_t* t) {
  time_t tt = t ? (time_t)*t : (time_t)time(nullptr);
  static __thread struct tm buf __attribute__((tls_model("initial-exec")));
  return gmtime_r(&tt, &buf);
}
extern "C" EXPORT_CDECL struct tm* msvcrt__localtime64(const int64_t* t) {
  time_t tt = t ? (time_t)*t : (time_t)time(nullptr);
  static __thread struct tm buf __attribute__((tls_model("initial-exec")));
  return localtime_r(&tt, &buf);
}
extern "C" EXPORT_CDECL int64_t msvcrt__mktime64(struct tm* tm_val) {
  return (int64_t)mktime(tm_val);
}
extern "C" EXPORT_CDECL size_t msvcrt_strftime(char* buf, size_t bufsz, const char* fmt, const struct tm* tm_val) {
  return strftime(buf, bufsz, fmt, tm_val);
}

// ---------------------------------------------------------------------------
// stdio — cdecl variadic wrappers (native i386 va_list)
// ---------------------------------------------------------------------------
extern "C" EXPORT_CDECL int msvcrt_printf(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int r = ms_vfprintf_fd(STDOUT_FILENO, fmt, ap);
  va_end(ap);
  return r;
}
extern "C" EXPORT_CDECL int msvcrt_vprintf(const char* fmt, va_list ap) {
  return ms_vfprintf_fd(STDOUT_FILENO, fmt, ap);
}
extern "C" EXPORT_CDECL int msvcrt_sprintf(char* buf, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  char* tmp = (char*)malloc(65536);
  int n = tmp ? ms_vformat(tmp, 65536, fmt, ap) : 0;
  va_end(ap);
  if( buf ) buf[0] = '\0';
  if( buf && tmp ) { memcpy(buf, tmp, (size_t)n); buf[n] = '\0'; }
  free(tmp);
  return n;
}

// stdio — file I/O using win_file_to_fd
extern "C" EXPORT_CDECL size_t msvcrt_fwrite(const void* buf, size_t sz, size_t count, void* f) {
  if( !buf || sz == 0 || count == 0 ) return 0;
  ssize_t r = write(win_file_to_fd(f), buf, sz * count);
  return r < 0 ? 0 : (size_t)r / sz;
}
extern "C" EXPORT_CDECL char* msvcrt_fgets(char* buf, int n, void* f) {
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
extern "C" EXPORT_CDECL int    msvcrt_puts(const char* s)    { return puts(s); }
extern "C" EXPORT_CDECL int    msvcrt_putchar(int c)          { return putchar(c); }
extern "C" EXPORT_CDECL int    msvcrt_remove(const char* p)   { return remove(p); }
extern "C" EXPORT_CDECL int    msvcrt_fflush(void* /*f*/)     { return 0; }   // shim is unbuffered
extern "C" EXPORT_CDECL void*  msvcrt_realloc(void* p, size_t n) { return realloc(p, n); }
extern "C" EXPORT_CDECL char*  msvcrt__strdup(const char* s)  { return s ? strdup(s) : nullptr; }

// string / memory pass-throughs
extern "C" EXPORT_CDECL void*  msvcrt_memmove(void* d, const void* s, size_t n) { return memmove(d, s, n); }
extern "C" EXPORT_CDECL void*  msvcrt_memset(void* d, int c, size_t n)          { return memset(d, c, n); }
extern "C" EXPORT_CDECL int    msvcrt_strcmp(const char* a, const char* b)       { return strcmp(a, b); }
extern "C" EXPORT_CDECL int    msvcrt_tolower(int c)                             { return tolower(c); }

// ---------------------------------------------------------------------------
// Wide string (uint16_t) functions — Linux wchar_t is 32-bit, can't use libc
// ---------------------------------------------------------------------------
extern "C" EXPORT_CDECL uint16_t* msvcrt_wcscat(uint16_t* dst, const uint16_t* src) {
  uint16_t* d = dst; while(*d) d++;
  while((*d++ = *src++));
  return dst;
}
extern "C" EXPORT_CDECL uint16_t* msvcrt_wcschr(const uint16_t* s, uint16_t c) {
  for(; *s; s++) if(*s == c) return (uint16_t*)s;
  return c == 0 ? (uint16_t*)s : nullptr;
}
extern "C" EXPORT_CDECL int msvcrt_wcscmp(const uint16_t* a, const uint16_t* b) {
  while(*a && *a == *b) { a++; b++; }
  return (int)*a - (int)*b;
}
extern "C" EXPORT_CDECL uint16_t* msvcrt_wcsrchr(const uint16_t* s, uint16_t c) {
  const uint16_t* last = nullptr;
  const uint16_t* start = s;
  for(; *s; s++) if(*s == c) last = s;
  uint16_t* r = c == 0 ? (uint16_t*)s : (uint16_t*)last;
  if( !r && c ) {
    char tmp[512]; int i=0;
    for(const uint16_t* p=start; *p&&i<500; p++,i++) tmp[i]=(char)(uint8_t)*p;
    tmp[i]=0;
    log_always("[SHIM] wcsrchr(U\"%s\", U'%c') -> NULL\n", tmp, (char)c);
  }
  return r;
}
extern "C" EXPORT_CDECL int msvcrt__wcsicmp(const uint16_t* a, const uint16_t* b) {
  while(*a && tolower(*a) == tolower(*b)) { a++; b++; }
  return (int)tolower(*a) - (int)tolower(*b);
}
extern "C" EXPORT_CDECL uint16_t* msvcrt__wcslwr(uint16_t* s) {
  for(uint16_t* p = s; *p; p++) *p = (uint16_t)tolower(*p);
  return s;
}

// ---------------------------------------------------------------------------
// _ultoa — unsigned long to ASCII in given radix
// ---------------------------------------------------------------------------
extern "C" EXPORT_CDECL char* msvcrt__ultoa(unsigned long val, char* buf, int radix) {
  if( radix == 10 ) { sprintf(buf, "%lu", val); return buf; }
  if( radix == 16 ) { sprintf(buf, "%lx", val); return buf; }
  if( val == 0 ) { buf[0]='0'; buf[1]='\0'; return buf; }
  char tmp[66]; int i = 65; tmp[i] = '\0';
  for( unsigned long v = val; v; v /= (unsigned long)radix ) {
    int d = (int)(v % (unsigned long)radix);
    tmp[--i] = d < 10 ? '0'+d : 'a'+d-10;
  }
  strcpy(buf, tmp+i); return buf;
}

// ---------------------------------------------------------------------------
// qsort — CRT comparator wrapper
// ---------------------------------------------------------------------------
// msvcrt_qsort — custom implementation that calls the (cdecl) comparator
// directly, avoiding libc qsort's own comparator-calling conventions.
// ---------------------------------------------------------------------------
typedef int (CDECLAPI *ms_cmp_fn)(const void*, const void*);

static void ms_swap_elems(uint8_t* base, size_t i, size_t j, size_t sz) {
  uint8_t* a = base + i * sz;
  uint8_t* b = base + j * sz;
  for( size_t k = 0; k < sz; k++ ) { uint8_t t = a[k]; a[k] = b[k]; b[k] = t; }
}

static inline int ms_cmp_elems(ms_cmp_fn cmp, uint8_t* base, size_t i, size_t j, size_t sz) {
  return cmp((void*)(base + i * sz), (void*)(base + j * sz));
}

extern "C" EXPORT_CDECL void msvcrt_qsort(void* base0, size_t n, size_t sz, ms_cmp_fn cmp) {
  if( n <= 1 || sz == 0 || !cmp ) return;

  enum { CUTOFF = 8, STKSIZ = 62 };
  uint8_t* base = (uint8_t*)base0;
  size_t lostk[STKSIZ], histk[STKSIZ];
  int stkptr = 0;
  size_t lo = 0, hi = n - 1;

recurse:;
  size_t size = hi - lo + 1;

  if( size <= CUTOFF ) {
    // selection sort for small arrays (matches user's template)
    size_t shi = hi;
    while( shi > lo ) {
      size_t max = lo;
      for( size_t p = lo + 1; p <= shi; p++ )
        if( ms_cmp_elems(cmp, base, p, max, sz) > 0 ) max = p;
      ms_swap_elems(base, max, shi, sz);
      shi--;
    }
  } else {
    size_t mid = lo + (size >> 1);
    if( ms_cmp_elems(cmp, base, lo,  mid, sz) > 0 ) ms_swap_elems(base, lo,  mid, sz);
    if( ms_cmp_elems(cmp, base, lo,  hi,  sz) > 0 ) ms_swap_elems(base, lo,  hi,  sz);
    if( ms_cmp_elems(cmp, base, mid, hi,  sz) > 0 ) ms_swap_elems(base, mid, hi,  sz);

    size_t loguy = lo, higuy = hi;
    while( 1 ) {
      if( mid > loguy )  do loguy++; while( loguy < mid  && ms_cmp_elems(cmp, base, loguy, mid, sz) <= 0 );
      if( mid <= loguy ) do loguy++; while( loguy <= hi  && ms_cmp_elems(cmp, base, loguy, mid, sz) <= 0 );
      do higuy--; while( higuy > mid && ms_cmp_elems(cmp, base, higuy, mid, sz) > 0 );
      if( higuy < loguy ) break;
      ms_swap_elems(base, loguy, higuy, sz);
      if( mid == higuy ) mid = loguy;
    }

    higuy++;
    if( mid < higuy )  do higuy--; while( higuy > mid && ms_cmp_elems(cmp, base, higuy, mid, sz) == 0 );
    if( mid >= higuy ) do higuy--; while( higuy > lo  && ms_cmp_elems(cmp, base, higuy, mid, sz) == 0 );

    if( higuy - lo >= hi - loguy ) {
      if( lo < higuy ) { lostk[stkptr] = lo;     histk[stkptr] = higuy; stkptr++; }
      if( loguy < hi ) { lo = loguy; goto recurse; }
    } else {
      if( loguy < hi ) { lostk[stkptr] = loguy; histk[stkptr] = hi; stkptr++; }
      if( lo < higuy ) { hi = higuy; goto recurse; }
    }
  }

  if( --stkptr >= 0 ) { lo = lostk[stkptr]; hi = histk[stkptr]; goto recurse; }
}

// ---------------------------------------------------------------------------
// scanf — read from stdin, parse common format specs
// ---------------------------------------------------------------------------
extern "C" EXPORT_CDECL int msvcrt_scanf(const char* fmt, ...) {
  char line[4096]; ssize_t n;
  do { n = read(STDIN_FILENO, line, sizeof(line)-1); } while(n<0 && errno==EINTR);
  if( n <= 0 ) return -1;  // EOF
  line[n] = '\0';
  va_list ap; va_start(ap, fmt);
  const char* p = fmt; const char* src = line; int count = 0;
  while( *p ) {
    if( *p != '%' ) { if(*src==*p) src++; p++; continue; }
    p++;
    bool suppress = (*p == '*');
    if( suppress ) p++;
    if( *p == 'd' || *p == 'i' ) {
      while(*src==' '||*src=='\t') src++;
      long v=0; int neg=(*src=='-'); if(neg) src++;
      while(*src>='0'&&*src<='9') v=v*10+(*src++-'0');
      if(!suppress) { int* ptr=va_arg(ap,int*); if(ptr)*ptr=(int)(neg?-v:v); count++; }
    } else if( *p == 's' ) {
      while(*src==' '||*src=='\t') src++;
      if(!suppress) { char* out=va_arg(ap,char*); if(out){ while(*src&&*src!=' '&&*src!='\t'&&*src!='\n') *out++=*src++; *out='\0'; } count++; }
      else           { while(*src&&*src!=' '&&*src!='\t'&&*src!='\n') src++; }
    } else if( *p == 'c' ) {
      if(!suppress) { char* out=va_arg(ap,char*); if(out&&*src)*out=*src++; count++; }
      else if(*src) src++;
    }
    p++;
  }
  va_end(ap);
  return count;
}

// ---------------------------------------------------------------------------
// _beginthreadex / _endthreadex — thin wrappers over our CreateThread shim
// ---------------------------------------------------------------------------
typedef unsigned (__attribute__((stdcall)) *beginthreadex_fn)(void*);

extern "C" EXPORT_CDECL uintptr_t msvcrt__beginthreadex(
    void* sa, unsigned stack, beginthreadex_fn fn, void* arg, unsigned flags, unsigned* tid) {
  DWORD dtid = 0;
  HANDLE h = kernel32_CreateThread(sa, stack, (win_thread_fn)fn, arg, flags, &dtid);
  if( tid ) *tid = (unsigned)dtid;
  return (uintptr_t)h;
}

extern "C" EXPORT_CDECL void msvcrt__endthreadex(unsigned code) {
  kernel32_ExitThread((DWORD)code);
}

// ---------------------------------------------------------------------------
// setjmp / longjmp — MSVC x86 _JUMP_BUFFER layout
//   Ebp@0x00 Ebx@0x04 Edi@0x08 Esi@0x0C Esp@0x10 Eip@0x14
//   Registration@0x18 TryLevel@0x1C Cookie@0x20 UnwindFunc@0x24
// Arguments arrive on the stack (cdecl), not in registers:
//   [esp+0] return address, [esp+4] buf, [esp+8] second arg.
// Registration is the fs:[0] SEH chain head so a longjmp out of a __try
// restores the handler list the target frame was running with.
// ---------------------------------------------------------------------------
extern "C" __attribute__((cdecl, naked, visibility("default"))) int msvcrt__setjmp(void* /*buf*/) {
  asm volatile(
    "movl 4(%%esp),%%ecx\n"      // ecx = buf
    "movl %%ebp, 0x00(%%ecx)\n"
    "movl %%ebx, 0x04(%%ecx)\n"
    "movl %%edi, 0x08(%%ecx)\n"
    "movl %%esi, 0x0C(%%ecx)\n"
    "leal 4(%%esp),%%eax\n"      // esp as it will be after the ret
    "movl %%eax, 0x10(%%ecx)\n"
    "movl (%%esp),%%eax\n"       // return address
    "movl %%eax, 0x14(%%ecx)\n"
    "movl %%fs:0,%%eax\n"        // SEH registration head
    "movl %%eax, 0x18(%%ecx)\n"
    "movl $-1, 0x1C(%%ecx)\n"    // TryLevel
    "movl $0,  0x20(%%ecx)\n"    // Cookie
    "movl $0,  0x24(%%ecx)\n"    // UnwindFunc
    "xorl %%eax,%%eax\n"
    "ret\n" ::: "memory");
}

// _setjmp3(buf, nargs, ...) is what modern MSVC emits; the extra arguments
// describe the unwind context and can be ignored for a plain register save.
extern "C" __attribute__((cdecl, naked, visibility("default"))) int msvcrt__setjmp3(void* /*buf*/, int /*nargs*/, ...) {
  asm volatile(
    "movl 4(%%esp),%%ecx\n"
    "movl %%ebp, 0x00(%%ecx)\n"
    "movl %%ebx, 0x04(%%ecx)\n"
    "movl %%edi, 0x08(%%ecx)\n"
    "movl %%esi, 0x0C(%%ecx)\n"
    "leal 4(%%esp),%%eax\n"
    "movl %%eax, 0x10(%%ecx)\n"
    "movl (%%esp),%%eax\n"
    "movl %%eax, 0x14(%%ecx)\n"
    "movl %%fs:0,%%eax\n"
    "movl %%eax, 0x18(%%ecx)\n"
    "movl $-1, 0x1C(%%ecx)\n"
    "movl $0,  0x20(%%ecx)\n"
    "movl $0,  0x24(%%ecx)\n"
    "xorl %%eax,%%eax\n"
    "ret\n" ::: "memory");
}

extern "C" __attribute__((cdecl, naked, visibility("default"))) void msvcrt_longjmp(void* /*buf*/, int /*val*/) {
  asm volatile(
    "movl 4(%%esp),%%ecx\n"      // ecx = buf
    "movl 8(%%esp),%%eax\n"      // eax = value
    "testl %%eax,%%eax\n"
    "jnz 1f\n"
    "movl $1,%%eax\n"
    "1:\n"
    "movl 0x18(%%ecx),%%edx\n"   // restore SEH chain head
    "movl %%edx,%%fs:0\n"
    "movl 0x00(%%ecx),%%ebp\n"
    "movl 0x04(%%ecx),%%ebx\n"
    "movl 0x08(%%ecx),%%edi\n"
    "movl 0x0C(%%ecx),%%esi\n"
    "movl 0x14(%%ecx),%%edx\n"   // saved Eip
    "movl 0x10(%%ecx),%%esp\n"   // saved Esp
    "jmp *%%edx\n" ::: "memory");
}
