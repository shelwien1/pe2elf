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
  if( n < 0 || n >= CRT_NLOCK ) {
    log_always("[SHIM] msvcrt__lock: ID %d out of range [0,%d)\n", n, CRT_NLOCK);
    return;
  }
  pthread_mutex_lock(&g_crt_locks[n]);
}
extern "C" EXPORT void msvcrt__unlock(int n) {
  pthread_once(&g_crt_locks_once, crt_locks_init);
  if( n < 0 || n >= CRT_NLOCK ) {
    log_always("[SHIM] msvcrt__unlock: ID %d out of range [0,%d)\n", n, CRT_NLOCK);
    return;
  }
  pthread_mutex_unlock(&g_crt_locks[n]);
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
extern "C" EXPORT int    msvcrt_fflush(void* /*f*/)     { return 0; }   // shim is unbuffered
extern "C" EXPORT void*  msvcrt_realloc(void* p, size_t n) { return realloc(p, n); }
extern "C" EXPORT char*  msvcrt__strdup(const char* s)  { return s ? strdup(s) : nullptr; }

// string / memory pass-throughs
extern "C" EXPORT void*  msvcrt_memmove(void* d, const void* s, size_t n) { return memmove(d, s, n); }
extern "C" EXPORT void*  msvcrt_memset(void* d, int c, size_t n)          { return memset(d, c, n); }
extern "C" EXPORT int    msvcrt_strcmp(const char* a, const char* b)       { return strcmp(a, b); }
extern "C" EXPORT int    msvcrt_tolower(int c)                             { return tolower(c); }

// ---------------------------------------------------------------------------
// Wide string (uint16_t) functions — Linux wchar_t is 32-bit, can't use libc
// ---------------------------------------------------------------------------
extern "C" EXPORT uint16_t* msvcrt_wcscat(uint16_t* dst, const uint16_t* src) {
  uint16_t* d = dst; while(*d) d++;
  while((*d++ = *src++));
  return dst;
}
extern "C" EXPORT uint16_t* msvcrt_wcschr(const uint16_t* s, uint16_t c) {
  for(; *s; s++) if(*s == c) return (uint16_t*)s;
  return c == 0 ? (uint16_t*)s : nullptr;
}
extern "C" EXPORT int msvcrt_wcscmp(const uint16_t* a, const uint16_t* b) {
  while(*a && *a == *b) { a++; b++; }
  return (int)*a - (int)*b;
}
extern "C" EXPORT uint16_t* msvcrt_wcsrchr(const uint16_t* s, uint16_t c) {
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
extern "C" EXPORT int msvcrt__wcsicmp(const uint16_t* a, const uint16_t* b) {
  while(*a && tolower(*a) == tolower(*b)) { a++; b++; }
  return (int)tolower(*a) - (int)tolower(*b);
}
extern "C" EXPORT uint16_t* msvcrt__wcslwr(uint16_t* s) {
  for(uint16_t* p = s; *p; p++) *p = (uint16_t)tolower(*p);
  return s;
}

// ---------------------------------------------------------------------------
// _ultoa — unsigned long to ASCII in given radix
// ---------------------------------------------------------------------------
extern "C" EXPORT char* msvcrt__ultoa(unsigned long val, char* buf, int radix) {
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
// qsort — ms_abi comparator wrapper
// ---------------------------------------------------------------------------
// msvcrt_qsort — custom implementation that calls the ms_abi comparator
// directly, avoiding the SYSV wrapper + libc qsort ABI complexity.
// ---------------------------------------------------------------------------
typedef int (__attribute__((ms_abi)) *ms_cmp_fn)(const void*, const void*);

static void ms_swap_elems(uint8_t* base, size_t i, size_t j, size_t sz) {
  uint8_t* a = base + i * sz;
  uint8_t* b = base + j * sz;
  for( size_t k = 0; k < sz; k++ ) { uint8_t t = a[k]; a[k] = b[k]; b[k] = t; }
}

static inline int ms_cmp_elems(ms_cmp_fn cmp, uint8_t* base, size_t i, size_t j, size_t sz) {
  return cmp((void*)(base + i * sz), (void*)(base + j * sz));
}

extern "C" EXPORT void msvcrt_qsort(void* base0, size_t n, size_t sz, ms_cmp_fn cmp) {
  log_always("[SHIM] qsort(base=%p, n=%zu, sz=%zu, cmp=%p)\n", base0, n, sz, (void*)(uintptr_t)cmp);
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
extern "C" EXPORT int msvcrt_scanf(const char* fmt, ...) {
  char line[4096]; ssize_t n;
  do { n = read(STDIN_FILENO, line, sizeof(line)-1); } while(n<0 && errno==EINTR);
  if( n <= 0 ) return -1;  // EOF
  line[n] = '\0';
  __builtin_ms_va_list msap; __builtin_ms_va_start(msap, fmt);
  char* ap = (char*)msap;
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
      if(!suppress) { int* ptr=(int*)MSVA_ARG_PTR(ap); if(ptr)*ptr=(int)(neg?-v:v); count++; }
    } else if( *p == 's' ) {
      while(*src==' '||*src=='\t') src++;
      if(!suppress) { char* out=(char*)MSVA_ARG_PTR(ap); if(out){ while(*src&&*src!=' '&&*src!='\t'&&*src!='\n') *out++=*src++; *out='\0'; } count++; }
      else           { while(*src&&*src!=' '&&*src!='\t'&&*src!='\n') src++; }
    } else if( *p == 'c' ) {
      if(!suppress) { char* out=(char*)MSVA_ARG_PTR(ap); if(out&&*src)*out=*src++; count++; }
      else if(*src) src++;
    }
    p++;
  }
  return count;
}

// ---------------------------------------------------------------------------
// _beginthreadex / _endthreadex — thin wrappers over our CreateThread shim
// ---------------------------------------------------------------------------
typedef unsigned (__attribute__((ms_abi)) *beginthreadex_fn)(void*);

extern "C" EXPORT uintptr_t msvcrt__beginthreadex(
    void* sa, unsigned stack, beginthreadex_fn fn, void* arg, unsigned flags, unsigned* tid) {
  DWORD dtid = 0;
  HANDLE h = kernel32_CreateThread(sa, stack, (win_thread_fn)fn, arg, flags, &dtid);
  if( tid ) *tid = (unsigned)dtid;
  return (uintptr_t)h;
}

extern "C" EXPORT void msvcrt__endthreadex(unsigned code) {
  kernel32_ExitThread((DWORD)code);
}

// ---------------------------------------------------------------------------
// setjmp / longjmp — Windows x64 JUMP_BUFFER layout (integer regs only)
// Offsets: Frame=0, Rbx=8, Rsp=16, Rbp=24, Rsi=32, Rdi=40,
//          R12=48, R13=56, R14=64, R15=72, Rip=80
// ---------------------------------------------------------------------------
extern "C" __attribute__((ms_abi, naked, visibility("default"))) int msvcrt__setjmp(void* /*buf*/, void* /*frame*/) {
  asm volatile(
    "movq %%rdx,  0(%%rcx)\n"   // Frame
    "movq %%rbx,  8(%%rcx)\n"   // Rbx
    "leaq 8(%%rsp),%%rax\n"
    "movq %%rax, 16(%%rcx)\n"   // Rsp (after return)
    "movq %%rbp, 24(%%rcx)\n"   // Rbp
    "movq %%rsi, 32(%%rcx)\n"   // Rsi
    "movq %%rdi, 40(%%rcx)\n"   // Rdi
    "movq %%r12, 48(%%rcx)\n"   // R12
    "movq %%r13, 56(%%rcx)\n"   // R13
    "movq %%r14, 64(%%rcx)\n"   // R14
    "movq %%r15, 72(%%rcx)\n"   // R15
    "movq (%%rsp),%%rax\n"
    "movq %%rax, 80(%%rcx)\n"   // Rip (return address)
    "xorl %%eax,%%eax\n"
    "ret\n" ::: "memory");
}

extern "C" __attribute__((ms_abi, naked, visibility("default"))) void msvcrt_longjmp(void* /*buf*/, int /*val*/) {
  asm volatile(
    "movq 16(%%rcx),%%r10\n"    // saved Rsp
    "movq 80(%%rcx),%%r11\n"    // saved Rip
    "movq  8(%%rcx),%%rbx\n"
    "movq 24(%%rcx),%%rbp\n"
    "movq 32(%%rcx),%%rsi\n"
    "movq 40(%%rcx),%%rdi\n"
    "movq 48(%%rcx),%%r12\n"
    "movq 56(%%rcx),%%r13\n"
    "movq 64(%%rcx),%%r14\n"
    "movq 72(%%rcx),%%r15\n"
    "movl %%edx,%%eax\n"
    "testl %%eax,%%eax\n"
    "jnz 1f\n"
    "movl $1,%%eax\n"
    "1:\n"
    "movq %%r10,%%rsp\n"
    "jmpq *%%r11\n" ::: "memory");
}
