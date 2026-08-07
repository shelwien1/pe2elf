// crt.cpp — the runtime BMF used to get from the PE, written against POSIX.
//
// Included by build.sh between dummy32_head.cpp and the moved bodies, and only
// in the standalone build.  Every symbol here fills in one of the `#ifndef
// __PE_DECL___x` slots the generated .inc files open: each of those blocks is
// "declare `__x` at its address inside BMF.exe *unless* someone already has",
// so defining the guard plus a real `__x` before the includes replaces the PE
// entry point without touching a single generated line.
//
// Three groups:
//
//   * The statically-linked MSVC CRT (§6.5 routed these into the PE because a
//     glibc FILE* handed to BMF's fread would be read as a Win32 _iobuf; with
//     BMF's code gone there is no second runtime and they are just glibc).
//   * The ten kernel32 imports, reimplemented on POSIX.  These are the ones
//     that were behind IAT slots, so they are named directly rather than
//     through a `#define`.
//   * Three odds and ends: operator new/delete, the two Intel memcpy/memset
//     dispatchers, and sub_402E30, the out-of-memory handler main installs.
//
// What is deliberately *not* here: winapi_shim32's Win32 emulation.  That is
// the right answer when you are running BMF's own code and it expects Windows;
// it is the wrong one when the goal is a program that stands on its own.  Ten
// functions against POSIX is less code than the shim's handle table alone.

#include <dirent.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <limits.h>
#include <stdarg.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// ---------------------------------------------------------------------------
// MSVC CRT
//
// The bodies call these through `#define fopen __fopen`, so the names have to
// be exactly `__` + what CRT_PROTO calls them, and the signatures have to be
// the ones extract.py would have emitted — the call sites were type-checked
// against those.
// ---------------------------------------------------------------------------
#define __PE_DECL___fopen
#define __PE_DECL___fclose
#define __PE_DECL___fread
#define __PE_DECL___fwrite
#define __PE_DECL___fseek
#define __PE_DECL___ftell
#define __PE_DECL___feof
#define __PE_DECL___ferror
#define __PE_DECL___fgetc
#define __PE_DECL___fgets
#define __PE_DECL___fflush
#define __PE_DECL___fputc
#define __PE_DECL___putc
#define __PE_DECL___fputs
#define __PE_DECL___remove
#define __PE_DECL___rename
#define __PE_DECL___printf
#define __PE_DECL___sprintf
#define __PE_DECL___sscanf
#define __PE_DECL___fprintf
#define __PE_DECL___fscanf
#define __PE_DECL___vprintf
#define __PE_DECL___exit
#define __PE_DECL___flsall
#define __PE_DECL___tmpnam
#define __PE_DECL____access
#define __PE_DECL____filelength
#define __PE_DECL____fileno
#define __PE_DECL____getch
#define __PE_DECL____strcmpi
#define __PE_DECL___irc__get_msg
#define __PE_DECL___irc__print

static inline FILE1 *__fopen(const char *p, const char *m) { return fopen(p, m); }
static inline int    __fclose(FILE1 *f)                    { return fclose(f); }
static inline unsigned __fread(void *b, unsigned s, unsigned n, FILE1 *f)
                                                           { return (unsigned)fread(b, s, n, f); }
static inline unsigned __fwrite(const void *b, unsigned s, unsigned n, FILE1 *f)
                                                           { return (unsigned)fwrite(b, s, n, f); }
static inline int    __fseek(FILE1 *f, long o, int w)      { return fseek(f, o, w); }
static inline long   __ftell(FILE1 *f)                     { return ftell(f); }
static inline int    __feof(FILE1 *f)                      { return feof(f); }
static inline int    __ferror(FILE1 *f)                    { return ferror(f); }
static inline int    __fgetc(FILE1 *f)                     { return fgetc(f); }
static inline char  *__fgets(char *s, int n, FILE1 *f)     { return fgets(s, n, f); }
static inline int    __fflush(FILE1 *f)                    { return fflush(f); }
static inline int    __fputc(int c, FILE1 *f)              { return fputc(c, f); }
static inline int    __putc(int c, FILE1 *f)               { return fputc(c, f); }
static inline int    __fputs(const char *s, FILE1 *f)      { return fputs(s, f); }
static inline int    __remove(const char *p)               { return remove(p); }
static inline int    __rename(const char *a, const char *b){ return rename(a, b); }
static inline void   __exit(int c)                         { exit(c); }

// _flsall(1) is MSVC's "flush every stream"; its argument is the commit flag,
// which glibc has no equivalent of and which BMF never varies.
static inline int __flsall(int) { return fflush(nullptr); }

// MSVC's _access takes 0/2/4/6 for exist/write/read/both, which are F_OK/W_OK/
// R_OK and their union — the same numbers POSIX uses.
static inline int  ___access(const char *p, int m)  { return access(p, m); }
static inline int  ___fileno(FILE1 *f)              { return fileno(f); }
static inline int  ___strcmpi(const char *a, const char *b) { return strcasecmp(a, b); }

static inline long ___filelength(int fd) {
  struct stat st;
  return fstat(fd, &st) == 0 ? (long)st.st_size : -1L;
}

// _getch reads one keystroke without waiting for Enter.  BMF uses it for the
// "overwrite? (y/n)" prompt, where line buffering only means the user has to
// press Return as well — not worth putting the terminal in raw mode for.
static inline int ___getch() { return getchar(); }

// Not `#define printf ::printf`: the bodies say `printf(...)` and the .inc
// says `#define printf __printf`, so the name that has to exist is __printf.
// gcc will not check the format string through a wrapper, hence the attribute.
__attribute__((format(printf, 1, 2)))
static int __printf(const char *f, ...) {
  va_list a; va_start(a, f);
  int r = vprintf(f, a);
  va_end(a);
  return r;
}
__attribute__((format(printf, 2, 3)))
static int __sprintf(char *s, const char *f, ...) {
  va_list a; va_start(a, f);
  int r = vsprintf(s, f, a);
  va_end(a);
  return r;
}
__attribute__((format(scanf, 2, 3)))
static int __sscanf(const char *s, const char *f, ...) {
  va_list a; va_start(a, f);
  int r = vsscanf(s, f, a);
  va_end(a);
  return r;
}
__attribute__((format(printf, 2, 3)))
static int __fprintf(FILE1 *s, const char *f, ...) {
  va_list a; va_start(a, f);
  int r = vfprintf(s, f, a);
  va_end(a);
  return r;
}
__attribute__((format(scanf, 2, 3)))
static int __fscanf(FILE1 *s, const char *f, ...) {
  va_list a; va_start(a, f);
  int r = vfscanf(s, f, a);
  va_end(a);
  return r;
}

// exit_402E40 calls this as `vprintf(fmt, &ArgList)`, where ArgList is its own
// last named parameter — so the pointer is into the incoming argument block and
// the remaining arguments follow it.  On i386 SysV a va_list *is* that pointer
// (`typedef char *__builtin_va_list`), which is why the void* form works.
static int __vprintf(const char *f, void *ap) {
  return vprintf(f, (va_list)ap);
}

// MSVC's tmpnam returns a name in the current directory and does not create
// the file; the caller renames the real file onto it and back, so it has to
// land on the same filesystem.  L_tmpnam-style "/tmp/..." would not.
static char *__tmpnam(char *buf) {
  static unsigned seq = 0;
  static char own[64];
  char *out = buf ? buf : own;
  for (;;) {
    sprintf(out, "bmf%05u.tmp", seq++ & 0xFFFFF);
    if (access(out, F_OK) != 0)
      return out;
  }
}

// Intel's runtime error reporter, reached only from sub_4346D0's
// "this CPU has no SSE2" path — which cannot be taken, since the moved bodies
// are full of SSE2 and would have faulted long before.  Kept so that path
// still compiles and says something if it ever runs.
static char *__irc__get_msg(int a, int b, void *) {
  static char msg[64];
  sprintf(msg, "Intel runtime message %d/%d", a, b);
  return msg;
}
__attribute__((format(printf, 1, 2)))
static int __irc__print(const char *f, ...) {
  va_list a; va_start(a, f);
  int r = vfprintf(stderr, f, a);
  va_end(a);
  return r;
}

// ---------------------------------------------------------------------------
// operator new / delete
//
// malloc/free rather than ::operator new: MSVC's returns null when it cannot
// allocate and BMF tests for that (`if ( void *p = operator new(8u) )`), while
// C++'s throws — and there is no handler here to catch it.
// ---------------------------------------------------------------------------
#define __PE_DECL___op_new
#define __PE_DECL___op_delete
static inline void *__op_new(unsigned int n) { return malloc(n ? n : 1); }
static inline void  __op_delete(void *p)     { free(p); }

// ---------------------------------------------------------------------------
// Intel's memcpy/memset dispatchers.
//
// __intel_fast_memcpy and __intel_fast_memset pick an implementation from the
// CPU features they cached at startup.  glibc's do the same thing through an
// IFUNC, so these are memcpy and memset — both return their destination, which
// is what the call sites expect.
// ---------------------------------------------------------------------------
#define __PE_DECL___sub_434980
#define __PE_DECL___sub_4349F0
static inline void *__sub_434980(void *d, const void *s, unsigned int n) { return memcpy(d, s, n); }
static inline void *__sub_4349F0(void *d, int c, unsigned int n)         { return memset(d, c, n); }

// sub_402E30 is `push 7; call exit_402E40` — the out-of-memory handler main
// hands to sub_42CBB0.  IDA's call analysis failed on it (hence "no decompiled
// body" in the generated declaration), but the two instructions are not in
// doubt.  Defined after the bodies, since exit_402E40 is one of them.
#define __PE_DECL___sub_402E30
void __sub_402E30();

// ---------------------------------------------------------------------------
// kernel32
// ---------------------------------------------------------------------------
#define __PE_DECL___VirtualAlloc
#define __PE_DECL___VirtualFree
#define __PE_DECL___CreateFileA
#define __PE_DECL___CloseHandle
#define __PE_DECL___SetFileTime
#define __PE_DECL___SetFileAttributesA
#define __PE_DECL___DosDateTimeToFileTime
#define __PE_DECL___FileTimeToDosDateTime
#define __PE_DECL___FindFirstFileA
#define __PE_DECL___FindNextFileA

// 100ns ticks between 1601-01-01 and the Unix epoch.
#define BMF_FILETIME_EPOCH 116444736000000000ULL

static inline unsigned long long bmf_ft_to_u64(const FILETIME &ft) {
  return ((unsigned long long)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
}

// VirtualAlloc's block is zero-filled and page-aligned, which malloc's is not,
// and BMF asks for a megabyte at a time — so mmap, not calloc.  VirtualFree is
// given only MEM_RELEASE (size 0), so the size has to be remembered; there are
// never more than a couple of these alive at once.
static struct { void *p; size_t n; } bmf_vm[16];

static __attribute__((stdcall))
void *VirtualAlloc(void *addr, unsigned int size, unsigned int type, unsigned int prot) {
  (void)addr; (void)type; (void)prot;
  void *p = mmap(nullptr, size, PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (p == MAP_FAILED)
    return nullptr;
  for (auto &s : bmf_vm)
    if (!s.p) { s.p = p; s.n = size; return p; }
  munmap(p, size);   // table full: fail the allocation rather than leak it
  return nullptr;
}

static __attribute__((stdcall))
int VirtualFree(void *p, unsigned int size, unsigned int type) {
  (void)size; (void)type;
  for (auto &s : bmf_vm)
    if (s.p == p) { munmap(s.p, s.n); s.p = nullptr; return 1; }
  return 0;
}

// A HANDLE is fd+1, so that fd 0 is not mistaken for NULL and no valid handle
// collides with INVALID_HANDLE_VALUE.  Only CreateFileA/SetFileTime/
// CloseHandle use file handles, and BMF holds one at a time.
static __attribute__((stdcall))
void *CreateFileA(const char *name, unsigned int access, unsigned int share,
                  void *sa, unsigned int disp, unsigned int flags, void *tmpl) {
  (void)share; (void)sa; (void)flags; (void)tmpl;
  int oflags = (access & GENERIC_WRITE) ? ((access & GENERIC_READ) ? O_RDWR : O_WRONLY)
                                        : O_RDONLY;
  if (disp == CREATE_ALWAYS)
    oflags |= O_CREAT | O_TRUNC;
  int fd = open(name, oflags, 0666);
  return fd < 0 ? INVALID_HANDLE_VALUE : (void *)(intptr_t)(fd + 1);
}

static __attribute__((stdcall)) int CloseHandle(void *h) {
  intptr_t fd = (intptr_t)h - 1;
  return (h == INVALID_HANDLE_VALUE || fd < 0) ? 0 : close((int)fd) == 0;
}

static __attribute__((stdcall))
int SetFileTime(void *h, const void *ctime, const void *atime, const void *mtime) {
  (void)ctime;
  intptr_t fd = (intptr_t)h - 1;
  if (h == INVALID_HANDLE_VALUE || fd < 0)
    return 0;
  struct timespec ts[2];
  const FILETIME *in[2] = { (const FILETIME *)atime, (const FILETIME *)mtime };
  for (int i = 0; i < 2; i++) {
    if (!in[i]) { ts[i].tv_sec = 0; ts[i].tv_nsec = UTIME_OMIT; continue; }
    unsigned long long v = bmf_ft_to_u64(*in[i]);
    v = v < BMF_FILETIME_EPOCH ? 0 : v - BMF_FILETIME_EPOCH;
    ts[i].tv_sec  = (time_t)(v / 10000000ULL);
    ts[i].tv_nsec = (long)((v % 10000000ULL) * 100);
  }
  return futimens((int)fd, ts) == 0;
}

// The only attribute BMF sets is FILE_ATTRIBUTE_NORMAL, to clear the read-only
// bit it set earlier — so this is a chmod of the write bits and nothing else.
static __attribute__((stdcall))
int SetFileAttributesA(const char *path, unsigned int attrs) {
  struct stat st;
  if (stat(path, &st) != 0)
    return 0;
  mode_t m = st.st_mode;
  if (attrs & 0x01)   // FILE_ATTRIBUTE_READONLY
    m &= ~(mode_t)(S_IWUSR | S_IWGRP | S_IWOTH);
  else
    m |= S_IWUSR;
  return chmod(path, m) == 0;
}

// FAT date/time, which is what BMF stores in the archive header: date is
// (year-1980)<<9 | month<<5 | day, time is hour<<11 | minute<<5 | second/2.
// UTC on both sides, so the pair round-trips exactly.
static __attribute__((stdcall))
int FileTimeToDosDateTime(const void *pft, unsigned short *date, unsigned short *tm_) {
  if (!pft || !date || !tm_)
    return 0;
  unsigned long long v = bmf_ft_to_u64(*(const FILETIME *)pft);
  if (v < BMF_FILETIME_EPOCH) { *date = *tm_ = 0; return 0; }
  time_t t = (time_t)((v - BMF_FILETIME_EPOCH) / 10000000ULL);
  struct tm g;
  gmtime_r(&t, &g);
  if (g.tm_year < 80) { *date = *tm_ = 0; return 0; }
  *date = (unsigned short)(((g.tm_year - 80) << 9) | ((g.tm_mon + 1) << 5) | g.tm_mday);
  *tm_  = (unsigned short)((g.tm_hour << 11) | (g.tm_min << 5) | (g.tm_sec >> 1));
  return 1;
}

static __attribute__((stdcall))
int DosDateTimeToFileTime(unsigned short date, unsigned short tm_, void *pft) {
  if (!pft)
    return 0;
  struct tm g;
  memset(&g, 0, sizeof g);
  g.tm_year = ((date >> 9) & 0x7F) + 80;
  g.tm_mon  = ((date >> 5) & 0x0F) - 1;
  g.tm_mday = date & 0x1F;
  g.tm_hour = (tm_ >> 11) & 0x1F;
  g.tm_min  = (tm_ >> 5) & 0x3F;
  g.tm_sec  = (tm_ & 0x1F) << 1;
  unsigned long long v = (unsigned long long)timegm(&g) * 10000000ULL + BMF_FILETIME_EPOCH;
  ((FILETIME *)pft)->dwLowDateTime  = (DWORD)v;
  ((FILETIME *)pft)->dwHighDateTime = (DWORD)(v >> 32);
  return 1;
}

// FindFirstFileA/FindNextFileA over opendir + fnmatch.  main uses them for one
// enumeration at a time and never calls FindClose, so the context is a single
// static: closing it on exhaustion is what stops the descriptor leaking.
static struct BmfFind {
  DIR *dir;
  char dirpath[PATH_MAX];
  char glob[NAME_MAX + 1];
} bmf_find;

static void bmf_fill_find(WIN32_FIND_DATAA *fd, const char *dirpath, const char *name) {
  memset(fd, 0, sizeof *fd);
  char full[PATH_MAX];
  snprintf(full, sizeof full, "%s/%s", dirpath, name);
  struct stat st;
  if (stat(full, &st) != 0)
    return;
  fd->dwFileAttributes = S_ISDIR(st.st_mode) ? 0x10 /* DIRECTORY */
                                             : 0x20 /* ARCHIVE   */;
  unsigned long long v = (unsigned long long)st.st_mtime * 10000000ULL + BMF_FILETIME_EPOCH;
  fd->ftLastWriteTime.dwLowDateTime  = (DWORD)v;
  fd->ftLastWriteTime.dwHighDateTime = (DWORD)(v >> 32);
  fd->ftCreationTime = fd->ftLastAccessTime = fd->ftLastWriteTime;
  fd->nFileSizeLow  = (DWORD)((unsigned long long)st.st_size & 0xFFFFFFFFu);
  fd->nFileSizeHigh = (DWORD)((unsigned long long)st.st_size >> 32);
  snprintf(fd->cFileName, sizeof fd->cFileName, "%s", name);
}

static __attribute__((stdcall)) int FindNextFileA(void *h, void *pfd) {
  BmfFind *c = (BmfFind *)h;
  if (!c || !c->dir)
    return 0;
  for (struct dirent *e; (e = readdir(c->dir)) != nullptr; ) {
    if (e->d_name[0] == '.' && (!e->d_name[1] || (e->d_name[1] == '.' && !e->d_name[2])))
      continue;
    if (fnmatch(c->glob, e->d_name, FNM_NOESCAPE) != 0)
      continue;
    bmf_fill_find((WIN32_FIND_DATAA *)pfd, c->dirpath, e->d_name);
    return 1;
  }
  closedir(c->dir);
  c->dir = nullptr;
  return 0;
}

static __attribute__((stdcall)) void *FindFirstFileA(const char *pattern, void *pfd) {
  BmfFind *c = &bmf_find;
  if (c->dir)
    closedir(c->dir);
  char tmp[PATH_MAX];
  snprintf(tmp, sizeof tmp, "%s", pattern);
  char *slash = strrchr(tmp, '/');
  if (slash) {
    *slash = '\0';
    snprintf(c->dirpath, sizeof c->dirpath, "%s", tmp[0] ? tmp : "/");
    snprintf(c->glob, sizeof c->glob, "%s", slash + 1);
  } else {
    snprintf(c->dirpath, sizeof c->dirpath, ".");
    snprintf(c->glob, sizeof c->glob, "%s", tmp);
  }
  c->dir = opendir(c->dirpath);
  if (!c->dir)
    return INVALID_HANDLE_VALUE;
  if (!FindNextFileA(c, pfd))
    return INVALID_HANDLE_VALUE;
  return c;
}
