#pragma once
// 7.4 File I/O + 7.5 File Times + 7.6 Directory/File Search — included
// from shim.cpp.  Must come before shim_kernel32_file_a.hpp since the
// A-variants reuse `find_ctx_open`, `fill_find_data_a`, `win_fnmatch`,
// and `stat_to_win_attrs` defined here.
//
// References from shim.cpp: handle_alloc_file, handle_alloc_find,
// handle_to_idx, idx_to_handle, get_fd, get_find_ctx, release_find_ctx,
// g_handles, g_handles_mu, FindCtx, HandleKind, H_FILE/H_FIND/H_MODULE/H_FREE,
// H_MUTEX (and >=H_MUTEX for sync), make_open_flags, wchar_to_utf8,
// utf8_to_wchar, win_path_to_posix, path_join, set_errno_error,
// FILETIME_EPOCH, u64_to_ft.

// ---------------------------------------------------------------------------
// 7.4 File I/O
// ---------------------------------------------------------------------------
extern "C" EXPORT HANDLE kernel32_GetStdHandle(DWORD n) {
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

extern "C" EXPORT BOOL kernel32_SetStdHandle(DWORD n, HANDLE h) {
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

extern "C" EXPORT HANDLE kernel32_CreateFileW(LPCWSTR name, DWORD access, DWORD share, SECURITY_ATTRIBUTES* sa, DWORD disp, DWORD flags, HANDLE tmpl) {
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

// Defined in shim_kernel32_sync.hpp (included below); forward-declared here
// so CloseHandle can use it.
static void sync_obj_destroy(HandleKind kind, void* ptr);

extern "C" EXPORT BOOL kernel32_CloseHandle(HANDLE h) {
  int idx = handle_to_idx(h);
  if( idx<0||idx<=2 )
    return TRUE;   // don't close stdio; pseudo handles are always ok
  pthread_mutex_lock(&g_handles_mu);
  HandleKind k = g_handles[idx].kind;
  int fd     = (k==H_FILE)   ? g_handles[idx].fd        : -1;
  FindCtx* fc  = (k==H_FIND)   ? g_handles[idx].find      : NULL;
  void* dlh  = (k==H_MODULE) ? g_handles[idx].dlhandle  : NULL;
  void* ptr  = (k>=H_MUTEX)  ? g_handles[idx].ptr       : NULL;
  if( k!=H_FREE )
    g_handles[idx].kind = H_FREE;
  pthread_mutex_unlock(&g_handles_mu);
  if( k==H_FILE ) {
    close(fd);
  } else if( k==H_FIND ) {
    if( fc ) release_find_ctx(fc);
  } else if( k==H_MODULE ) {
    if( dlh ) dlclose(dlh);
  } else if( k>=H_MUTEX ) {
    // Decrement refcount; only destroy when it reaches 0 (a concurrent
    // WaitForSingleObject may still hold a reference to the object).
    pthread_mutex_lock(&g_handles_mu);
    int new_rc = --(*(int*)ptr);
    pthread_mutex_unlock(&g_handles_mu);
    if( new_rc == 0 ) sync_obj_destroy(k, ptr);
  } else {
    SET_LAST_ERROR(ERROR_INVALID_HANDLE);
    return FALSE;
  }
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_ReadFile(HANDLE h, LPVOID buf, DWORD n, DWORD* pRead, void* ov) {
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

extern "C" EXPORT BOOL kernel32_WriteFile(HANDLE h, LPCVOID buf, DWORD n, DWORD* pWritten, void* ov) {
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

extern "C" EXPORT BOOL kernel32_SetFilePointerEx(HANDLE h, LARGE_INTEGER dist, LARGE_INTEGER* pNew, DWORD method) {
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

extern "C" EXPORT BOOL kernel32_FlushFileBuffers(HANDLE h) {
  int fd = get_fd(h);
  if( fd<0 )
    return FALSE;
  fsync(fd);
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_GetFileSizeEx(HANDLE h, int64_t* size) {
  int fd = get_fd(h);
  if( fd<0 ) { SET_LAST_ERROR(ERROR_INVALID_HANDLE); return FALSE; }
  struct stat st;
  if( fstat(fd, &st)<0 ) { set_errno_error(); return FALSE; }
  if( size ) *size = (int64_t)st.st_size;
  return TRUE;
}

extern "C" EXPORT DWORD kernel32_GetFileType(HANDLE h) {
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
extern "C" EXPORT void kernel32_GetSystemTimeAsFileTime(FILETIME* pft) {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  uint64_t v = (uint64_t)ts.tv_sec*10000000ULL+(uint64_t)ts.tv_nsec/100ULL+FILETIME_EPOCH;
  *pft = u64_to_ft(v);
}

// ---------------------------------------------------------------------------
// 7.6 Directory / File Search
// ---------------------------------------------------------------------------

// Map Linux stat → Windows file attributes.
// Rules:
//   no-write bits  → READONLY
//   any exec bit   → SYSTEM  (closest Linux semantic: executable = "system-managed")
//   S_ISDIR        → DIRECTORY
//   S_ISREG        → ARCHIVE (default for regular files; means "needs backup")
//   nothing above  → NORMAL
// NOTE: we deliberately do NOT map dot-prefixed names to HIDDEN.  Linux dot-names
// are a naming convention, not a stored attribute; Windows HIDDEN is explicit
// metadata.  Setting HIDDEN on all dotfiles causes archivers and other tools to
// silently skip .git, .gitignore, etc. — the wrong behaviour for a compat shim.
static DWORD stat_to_win_attrs(const struct stat* st, const char* /*name*/) {
  DWORD attrs = 0;
  if( !(st->st_mode & (S_IWUSR|S_IWGRP|S_IWOTH)) )
    attrs |= FILE_ATTRIBUTE_READONLY;
  if( st->st_mode & (S_IXUSR|S_IXGRP|S_IXOTH) )
    attrs |= FILE_ATTRIBUTE_SYSTEM;
  if( S_ISDIR(st->st_mode) )
    attrs |= FILE_ATTRIBUTE_DIRECTORY;
  else if( S_ISREG(st->st_mode) )
    attrs |= FILE_ATTRIBUTE_ARCHIVE;
  if( attrs==0 )
    attrs = FILE_ATTRIBUTE_NORMAL;
  return attrs;
}

// Fill common stat-derived fields of WIN32_FIND_DATA* (both A and W share layout
// for everything except cFileName/cAlternateFileName).
template<typename T>
static void fill_find_data_common(T* pfd, const char* fullpath, const char* name) {
  memset(pfd, 0, sizeof(*pfd));
  struct stat st;
  if( stat(fullpath, &st)==0 ) {
    pfd->dwFileAttributes = stat_to_win_attrs(&st, name);
    uint64_t mtime = (uint64_t)st.st_mtime*10000000ULL+FILETIME_EPOCH;
    pfd->ftLastWriteTime  = u64_to_ft(mtime);
    pfd->ftCreationTime   = pfd->ftLastWriteTime;
    pfd->ftLastAccessTime = pfd->ftLastWriteTime;
    pfd->nFileSizeLow  = (DWORD)(st.st_size & 0xFFFFFFFF);
    pfd->nFileSizeHigh = (DWORD)(st.st_size >> 32);
  }
}

static void fill_find_data_w(WIN32_FIND_DATAW* pfd, const char* fullpath, const char* name) {
  fill_find_data_common(pfd, fullpath, name);
  utf8_to_wchar(name, pfd->cFileName, 260);
}

static void fill_find_data_a(WIN32_FIND_DATAA* pfd, const char* fullpath, const char* name) {
  fill_find_data_common(pfd, fullpath, name);
  strncpy(pfd->cFileName, name, 259);
}

// Shared helper: open directory from a POSIX pattern path, scan to first match,
// populate ctx. Returns first matching dirent or NULL.

// Windows FindFirstFile wildcard semantics differ from POSIX fnmatch:
// "*.foo" also matches extensionless names (FAT/NTFS backward-compat).
// Specifically, if the pattern ends with ".*", we also try it without the ".*"
// tail so that "config", "HEAD", "index" etc. match "*.*" or "f*.*".
static bool win_fnmatch(const char* glob, const char* name) {
  if( fnmatch(glob, name, FNM_NOESCAPE)==0 ) return true;
  // Strip trailing ".*" and retry — covers *.*  f*.*  etc.
  const char* dot_star = strrchr(glob, '.');
  if( dot_star && dot_star[1]=='*' && dot_star[2]=='\0' ) {
    size_t prefix_len = (size_t)(dot_star - glob);
    char prefix[NAME_MAX+2];
    if( prefix_len < sizeof(prefix) ) {
      memcpy(prefix, glob, prefix_len);
      prefix[prefix_len] = '\0';
      // Empty prefix (the pattern was just ".*") means match anything.
      const char* p = prefix_len ? prefix : "*";
      if( fnmatch(p, name, FNM_NOESCAPE)==0 ) return true;
    }
  }
  return false;
}

static struct dirent* find_ctx_open(const char* posix, FindCtx** out_ctx) {
  char dir[PATH_MAX] = ".";
  char glob[260] = "*";
  char tmp[PATH_MAX];
  snprintf(tmp, sizeof(tmp), "%s", posix);
  char* slash = strrchr(tmp, '/');
  if( slash ) {
    *slash = '\0';
    const char* g = slash+1;
    if( g[0] ) {
      snprintf(dir, sizeof(dir), "%s", tmp);
      snprintf(glob, sizeof(glob), "%s", g);
    } else {
      // Trailing slash: caller wants the directory entry itself (like "." in dir).
      // We mark glob as "." so find_ctx_open can detect it later.
      snprintf(dir, sizeof(dir), "%s", tmp[0] ? tmp : "/");
      snprintf(glob, sizeof(glob), ".");
    }
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
  if( !ctx ) {
    closedir(d);
    SET_LAST_ERROR(ERROR_OUTOFMEMORY);
    return NULL;
  }
  ctx->dir = d;
  snprintf(ctx->glob, sizeof(ctx->glob), "%s", glob);
  snprintf(ctx->dirpath, sizeof(ctx->dirpath), "%s", dir[0] ? dir : ".");
  *out_ctx = ctx;
  struct dirent* ent;
  bool dot_query = (strcmp(glob, ".")==0);
  while( (ent = readdir(d))!=NULL ) {
    if( dot_query ) {
      if( strcmp(ent->d_name, ".")==0 ) return ent;
      continue;
    }
    if( strcmp(ent->d_name, ".")==0||strcmp(ent->d_name, "..")==0 )
      continue;
    if( win_fnmatch(ctx->glob, ent->d_name) )
      return ent;
  }
  closedir(d);
  free(ctx);
  *out_ctx = NULL;
  SET_LAST_ERROR(ERROR_FILE_NOT_FOUND);
  return NULL;
}

extern "C" EXPORT HANDLE kernel32_FindFirstFileExW(LPCWSTR pattern, int lvl, WIN32_FIND_DATAW* pfd, int srchas, void* filter, DWORD flags) {
  (void)lvl;
  (void)srchas;
  (void)filter;
  (void)flags;
  char narrow[PATH_MAX], posix[PATH_MAX];
  wchar_to_utf8(pattern, narrow, sizeof(narrow));
  win_path_to_posix(narrow, posix, sizeof(posix));
  { size_t wl=0; while(pattern[wl]) wl++;
    log_always("[SHIM] FindFirstFileExW(wlen=%zu \"%s\" -> \"%s\")\n", wl, narrow, posix); }

  FindCtx* ctx = NULL;
  struct dirent* ent = find_ctx_open(posix, &ctx);
  if( !ent ) {
    log_always("[SHIM] FindFirstFileExW -> INVALID (find_ctx_open failed)\n");
    return INVALID_HANDLE_VALUE;
  }

  char fullpath[PATH_MAX];
  path_join(fullpath, sizeof(fullpath), ctx->dirpath, ent->d_name);
  fill_find_data_w(pfd, fullpath, ent->d_name);
  log_always("[SHIM] FindFirstFileExW -> first=\"%s\"\n", ent->d_name);

  HANDLE hret = handle_alloc_find(ctx);
  if( hret==INVALID_HANDLE_VALUE ) {
    closedir(ctx->dir);
    free(ctx);
  }
  return hret;
}

extern "C" EXPORT BOOL kernel32_FindNextFileW(HANDLE h, WIN32_FIND_DATAW* pfd) {
  FindCtx* ctx = get_find_ctx(h);   // retained; safe against concurrent FindClose
  if( !ctx ) return FALSE;
  struct dirent* ent;
  BOOL found = FALSE;
  while( (ent = readdir(ctx->dir))!=NULL ) {
    if( strcmp(ent->d_name, ".")==0||strcmp(ent->d_name, "..")==0 )
      continue;
    if( !win_fnmatch(ctx->glob, ent->d_name) )
      continue;
    char fullpath[PATH_MAX];
    path_join(fullpath, sizeof(fullpath), ctx->dirpath, ent->d_name);
    fill_find_data_w(pfd, fullpath, ent->d_name);
    log_always("[SHIM] FindNextFileW -> \"%s\"\n", ent->d_name);
    found = TRUE;
    break;
  }
  if( !found ) SET_LAST_ERROR(ERROR_NO_MORE_FILES);
  release_find_ctx(ctx);
  return found;
}

extern "C" EXPORT BOOL kernel32_FindClose(HANDLE h) {
  log_always("[SHIM] FindClose(%p)\n", h);
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
