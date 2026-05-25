#pragma once
// A-variant file/directory functions — included from shim.cpp.
//
// Mostly thin char* → wchar* delegators to the corresponding W-variants,
// except for FindFirstFileA/FindFirstFileExA/FindNextFileA which share
// `find_first_posix` with FindFirstFileExW via the FindCtx machinery
// already in shim.cpp.  CreateFileA also handles the Windows console
// device aliases (CON/CONIN$/CONOUT$).
//
// References from shim.cpp: FindCtx, find_ctx_open, fill_find_data_a,
// path_join, handle_alloc_find, win_path_to_posix, posix_to_win_path,
// utf8_to_wchar, wchar_to_utf8, win_fnmatch, get_find_ctx,
// release_find_ctx, make_open_flags, handle_alloc_file, handle_to_idx,
// g_handles, IS_MAIN_IMAGE, set_errno_error, kernel32_LoadLibraryExW.

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

extern "C" EXPORT HANDLE kernel32_FindFirstFileExA(LPCSTR pattern, int /*lvl*/, WIN32_FIND_DATAA* pfd,
    int /*srchas*/, void* /*filter*/, DWORD /*flags*/) {
  char posix[PATH_MAX];
  win_path_to_posix(pattern, posix, sizeof(posix));
  return find_first_posix(posix, pfd);
}

extern "C" EXPORT HANDLE kernel32_FindFirstFileA(LPCSTR pattern, WIN32_FIND_DATAA* pfd) {
  char posix[PATH_MAX];
  win_path_to_posix(pattern, posix, sizeof(posix));
  return find_first_posix(posix, pfd);
}

extern "C" EXPORT BOOL kernel32_FindNextFileA(HANDLE h, WIN32_FIND_DATAA* pfd) {
  FindCtx* ctx = get_find_ctx(h);   // retained; safe against concurrent FindClose
  if( !ctx ) return FALSE;
  struct dirent* ent;
  BOOL found = FALSE;
  while( (ent = readdir(ctx->dir))!=NULL ) {
    if( ent->d_name[0]=='.'&&(!ent->d_name[1]||ent->d_name[1]=='.') )
      continue;
    if( !win_fnmatch(ctx->glob, ent->d_name) )
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

extern "C" EXPORT HANDLE kernel32_CreateFileA(LPCSTR name, DWORD access, DWORD share, SECURITY_ATTRIBUTES* sa, DWORD disp, DWORD flags, HANDLE tmpl) {
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

extern "C" EXPORT BOOL kernel32_DeleteFileA(LPCSTR path) {
  char posix[PATH_MAX];
  win_path_to_posix(path, posix, sizeof(posix));
  if( unlink(posix)<0 ) {
    set_errno_error();
    return FALSE;
  }
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_SetFileAttributesA(LPCSTR path, DWORD attrs) {
  char posix[PATH_MAX];
  win_path_to_posix(path, posix, sizeof(posix));
  struct stat st;
  if( stat(posix, &st)<0 ) { set_errno_error(); return FALSE; }
  mode_t m = st.st_mode;
  if( attrs & FILE_ATTRIBUTE_READONLY )
    m &= ~(S_IWUSR|S_IWGRP|S_IWOTH);
  else
    m |= S_IWUSR;
  if( attrs & FILE_ATTRIBUTE_SYSTEM )
    m |= S_IXUSR|S_IXGRP|S_IXOTH;
  else if( S_ISREG(m) )   // only strip exec from regular files, not directories
    m &= ~(S_IXUSR|S_IXGRP|S_IXOTH);
  if( chmod(posix, m)<0 ) { set_errno_error(); return FALSE; }
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_SetFileAttributesW(const uint16_t* path, DWORD attrs) {
  char utf8[PATH_MAX];
  wchar_to_utf8(path, utf8, sizeof(utf8));
  return kernel32_SetFileAttributesA(utf8, attrs);
}

extern "C" EXPORT DWORD kernel32_GetCurrentDirectoryA(DWORD size, LPSTR buf) {
  char posix[PATH_MAX];
  if( !getcwd(posix, sizeof(posix)) ) { set_errno_error(); return 0; }
  char win[PATH_MAX];
  posix_to_win_path(posix, win, sizeof(win));
  DWORD n = (DWORD)strlen(win);
  if( !buf || size == 0 ) return n + 1;
  if( size <= n ) { SET_LAST_ERROR(122u); return n + 1; }  // ERROR_INSUFFICIENT_BUFFER=122
  memcpy(buf, win, n + 1);
  return n;
}

extern "C" EXPORT DWORD kernel32_GetCurrentDirectoryW(DWORD size, uint16_t* buf) {
  char posix[PATH_MAX];
  if( !getcwd(posix, sizeof(posix)) ) { set_errno_error(); return 0; }
  char win[PATH_MAX];
  posix_to_win_path(posix, win, sizeof(win));
  if( !buf || size == 0 ) {
    uint16_t tmp[PATH_MAX];
    return (DWORD)utf8_to_wchar(win, tmp, PATH_MAX) + 1;
  }
  return (DWORD)utf8_to_wchar(win, buf, size);
}

extern "C" EXPORT DWORD kernel32_GetModuleFileNameA(HANDLE h, LPSTR buf, DWORD size) {
  if( size==0 ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return 0; }
  char posix[PATH_MAX];
  if( h==NULL||IS_MAIN_IMAGE(h) ) {
    ssize_t n = readlink("/proc/self/exe", posix, sizeof(posix)-1);
    if( n<0 ) { set_errno_error(); return 0; }
    posix[n] = '\0';
  } else {
    int idx = handle_to_idx(h);
    void* dlh = (idx>=0&&g_handles[idx].kind==H_MODULE) ? g_handles[idx].dlhandle : NULL;
    if( dlh ) {
      void* sym = dlsym(dlh, "_init"); if( !sym ) sym = dlh;
      Dl_info info;
      if( dladdr(sym, &info)&&info.dli_fname )
        strncpy(posix, info.dli_fname, sizeof(posix)-1);
      else posix[0] = '\0';
    } else { buf[0]='\0'; return 0; }
  }
  char win[PATH_MAX]; posix_to_win_path(posix, win, sizeof(win));
  strncpy(buf, win, size-1); buf[size-1] = '\0';
  return (DWORD)strlen(buf);
}

extern "C" EXPORT HANDLE kernel32_LoadLibraryA(LPCSTR name) {
  uint16_t wbuf[PATH_MAX];
  utf8_to_wchar(name, wbuf, PATH_MAX);
  return kernel32_LoadLibraryExW(wbuf, NULL, 0);
}
