#pragma once
// Tail of the kernel32 surface — included from shim.cpp.
//
// Covers, in order: Temp file/path, SetCurrentDirectoryW,
// FileTimeToLocalFileTime, GlobalMemoryStatusEx, shell32 /
// shlwapi / winmm leftovers (CommandLineToArgvW, PathMatchSpec{A,W},
// timeGetTime), SetConsoleCtrlHandler, DeleteFileW / RemoveDirectoryW /
// MoveFileW / CreateHardLink{A,W}, GetFileInformationByHandle, GetFileTime,
// GetSystemTime / SystemTimeToFileTime / tz conversions, LocalFileTimeToFileTime,
// GetVersionExW, GetSystemDirectory{A,W} / GetVolumeInformation{A,W} /
// GetDiskFreeSpaceEx{A,W} / GetDriveTypeW, GetFullPathNameA,
// GetLongPathName{A,W} / GetShortPathName{A,W} identity stubs,
// ExpandEnvironmentStringsW, FoldString{A,W}, CompareStringA,
// CreateEventW / CreateSemaphoreW / WaitForSingleObjectEx / LoadLibraryW
// wrappers, SetEnvironmentVariableA, IsDBCSLeadByte, SetErrorMode,
// SetPriorityClass, SetThreadExecutionState, BackupRead, BackupSeek,
// DeviceIoControl.
//
// References from shim.cpp: utf8_to_wchar, wchar_to_utf8,
// posix_to_win_path, win_path_to_posix, win_fnmatch, get_fd,
// set_errno_error, stat_to_win_attrs, ft_to_u64, u64_to_ft,
// kernel32_DeleteFileA, kernel32_CreateEventA, kernel32_CreateSemaphoreA,
// kernel32_WaitForSingleObject, kernel32_LoadLibraryExW,
// kernel32_GetFullPathNameW, FILETIME_EPOCH.

// ---------------------------------------------------------------------------
// Temp file/path
// ---------------------------------------------------------------------------
extern "C" EXPORT DWORD kernel32_GetTempPathW(DWORD sz, uint16_t* buf) {
  const char* tmp = getenv("TEMP");
  if( !tmp ) tmp = "/tmp";
  char posix[PATH_MAX], win[PATH_MAX];
  snprintf(posix, sizeof(posix), "%s/", tmp);
  posix_to_win_path(posix, win, sizeof(win));
  // Ensure trailing backslash.
  size_t n = strlen(win);
  if( n == 0 || win[n-1] != '\\' ) { win[n++] = '\\'; win[n] = '\0'; }
  if( buf && sz ) utf8_to_wchar(win, buf, sz);
  return (DWORD)n;
}

extern "C" EXPORT UINT kernel32_GetTempFileNameW(const uint16_t* path, const uint16_t* prefix,
                                                   UINT unique, uint16_t* out) {
  char dir[PATH_MAX], pfx[16], result[PATH_MAX];
  wchar_to_utf8(path, dir, sizeof(dir));
  wchar_to_utf8(prefix, pfx, sizeof(pfx));
  pfx[3] = '\0';   // Windows uses first 3 chars of prefix
  if( unique ) {
    snprintf(result, sizeof(result), "%s/%s%04X.tmp", dir, pfx, unique & 0xFFFF);
    int fd = open(result, O_CREAT|O_EXCL|O_WRONLY, 0600);
    if( fd >= 0 ) close(fd);
  } else {
    snprintf(result, sizeof(result), "%s/%sXXXXXX.tmp", dir, pfx);
    int fd = mkstemps(result, 4);
    if( fd >= 0 ) close(fd);
    unique = (UINT)(uintptr_t)strrchr(result, '/');  // use addr as pseudo-unique
  }
  if( out ) utf8_to_wchar(result, out, 260);
  return unique;
}
extern "C" EXPORT DWORD kernel32_GetTempPathA(DWORD sz, LPSTR buf) {
  uint16_t wbuf[PATH_MAX];
  DWORD n = kernel32_GetTempPathW((DWORD)(PATH_MAX), wbuf);
  if( buf && sz ) wchar_to_utf8(wbuf, buf, sz);
  return n;
}
extern "C" EXPORT UINT kernel32_GetTempFileNameA(LPCSTR path, LPCSTR prefix, UINT unique, LPSTR out) {
  uint16_t wpath[PATH_MAX], wpfx[16], wout[PATH_MAX];
  utf8_to_wchar(path,   wpath, PATH_MAX);
  utf8_to_wchar(prefix, wpfx,  16);
  UINT r = kernel32_GetTempFileNameW(wpath, wpfx, unique, wout);
  if( out ) wchar_to_utf8(wout, out, PATH_MAX);
  return r;
}

// ---------------------------------------------------------------------------
// SetCurrentDirectoryW
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL kernel32_SetCurrentDirectoryW(const uint16_t* path) {
  char utf8[PATH_MAX];
  wchar_to_utf8(path, utf8, sizeof(utf8));
  char posix[PATH_MAX];
  win_path_to_posix(utf8, posix, sizeof(posix));
  if( chdir(posix) != 0 ) { set_errno_error(); return FALSE; }
  return TRUE;
}

// ---------------------------------------------------------------------------
// FileTimeToLocalFileTime — apply local UTC offset
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL kernel32_FileTimeToLocalFileTime(const FILETIME* utc, FILETIME* local) {
  if( !utc || !local ) return FALSE;
  time_t now = time(nullptr);
  struct tm loc; localtime_r(&now, &loc);
  int64_t off_100ns = (int64_t)loc.tm_gmtoff * 10000000LL;
  uint64_t v = ft_to_u64(*utc);
  *local = u64_to_ft(v + (uint64_t)off_100ns);
  return TRUE;
}

// ---------------------------------------------------------------------------
// GlobalMemoryStatusEx — MEMORYSTATUSEX (64 bytes, dwLength must match)
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL kernel32_GlobalMemoryStatusEx(uint8_t* buf) {
  if( !buf ) return FALSE;
  uint32_t caller_len = *(uint32_t*)(buf+0);
  uint32_t sz = (caller_len >= 64) ? caller_len : 64;
  memset(buf, 0, sz);
  *(uint32_t*)(buf+0) = sz;                     // dwLength (echo caller's value)
  struct sysinfo si;
  if( sysinfo(&si) == 0 ) {
    uint64_t total = (uint64_t)si.totalram  * si.mem_unit;
    uint64_t avail = (uint64_t)si.freeram   * si.mem_unit;
    uint32_t load  = total ? (uint32_t)(100 - avail * 100 / total) : 0;
    *(uint32_t*)(buf+4)  = load;                 // dwMemoryLoad
    *(uint64_t*)(buf+8)  = total;                // ullTotalPhys
    *(uint64_t*)(buf+16) = avail;                // ullAvailPhys
    *(uint64_t*)(buf+24) = total;                // ullTotalPageFile
    *(uint64_t*)(buf+32) = avail;                // ullAvailPageFile
    *(uint64_t*)(buf+40) = (uint64_t)2 << 40;   // ullTotalVirtual (2 TB)
    *(uint64_t*)(buf+48) = (uint64_t)2 << 40;   // ullAvailVirtual
    if( sz >= 64 )
      *(uint64_t*)(buf+56) = 0;                 // ullAvailExtendedVirtual
  }
  return TRUE;
}

// ---------------------------------------------------------------------------
// shell32 / shlwapi / winmm
// ---------------------------------------------------------------------------

// CommandLineToArgvW: parse a Windows command line into wide argv array.
// Returns pointer to LPWSTR[] allocated with one LocalAlloc block;
// the caller frees with LocalFree on the returned pointer.
extern "C" EXPORT uint16_t** shell32_CommandLineToArgvW(const uint16_t* cmdline, int* argc_out) {
  // Convert to UTF-8, split, then convert each arg back to wide.
  char narrow[32768];
  wchar_to_utf8(cmdline, narrow, sizeof(narrow));

  // Count args and split on whitespace (handling quoted strings).
  // Two-pass: count then fill.
  int argc = 0;
  const char* p = narrow;
  while( *p ) {
    while( *p == ' ' || *p == '\t' ) p++;
    if( !*p ) break;
    argc++;
    if( *p == '"' ) { p++; while( *p && *p != '"' ) p++; if(*p) p++; }
    else            { while( *p && *p != ' ' && *p != '\t' ) p++; }
  }

  // Allocate: argc pointers + storage for each wide string.
  // We allocate a flat block: argv[] + string data.
  size_t ptrs_sz  = (size_t)(argc + 1) * sizeof(uint16_t*);
  size_t data_sz  = (strlen(narrow) + 1) * sizeof(uint16_t) * 2;
  uint8_t* block  = (uint8_t*)malloc(ptrs_sz + data_sz);
  if( !block ) { if(argc_out) *argc_out=0; return nullptr; }
  uint16_t** argv = (uint16_t**)block;
  uint16_t*  data = (uint16_t*)(block + ptrs_sz);

  int i = 0; p = narrow;
  uint16_t* wp = data;
  while( *p && i < argc ) {
    while( *p == ' ' || *p == '\t' ) p++;
    if( !*p ) break;
    argv[i++] = wp;
    if( *p == '"' ) {
      p++;
      while( *p && *p != '"' ) *wp++ = (uint16_t)(uint8_t)*p++;
      if( *p ) p++;
    } else {
      while( *p && *p != ' ' && *p != '\t' ) *wp++ = (uint16_t)(uint8_t)*p++;
    }
    *wp++ = 0;
  }
  argv[i] = nullptr;
  if( argc_out ) *argc_out = argc;
  return argv;
}

// PathMatchSpecW: match a wide path against a wildcard spec.
extern "C" EXPORT BOOL shlwapi_PathMatchSpecW(const uint16_t* path, const uint16_t* spec) {
  char path_u[PATH_MAX], spec_u[260];
  wchar_to_utf8(path, path_u, sizeof(path_u));
  wchar_to_utf8(spec, spec_u, sizeof(spec_u));
  // Use basename for matching (PathMatchSpec matches the filename portion).
  const char* base = strrchr(path_u, '\\');
  if( !base ) base = strrchr(path_u, '/');
  base = base ? base+1 : path_u;
  return win_fnmatch(spec_u, base) ? TRUE : FALSE;
}
extern "C" EXPORT BOOL shlwapi_PathMatchSpecA(LPCSTR path, LPCSTR spec) {
  uint16_t wpath[PATH_MAX], wspec[260];
  utf8_to_wchar(path, wpath, PATH_MAX);
  utf8_to_wchar(spec, wspec, 260);
  return shlwapi_PathMatchSpecW(wpath, wspec);
}

// timeGetTime: milliseconds since system boot (same as GetTickCount).
extern "C" EXPORT DWORD winmm_timeGetTime(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (DWORD)((uint64_t)ts.tv_sec * 1000ULL + (uint64_t)ts.tv_nsec / 1000000ULL);
}

// ---------------------------------------------------------------------------
// SetConsoleCtrlHandler
// ---------------------------------------------------------------------------
typedef BOOL (__attribute__((ms_abi)) *PHANDLER_ROUTINE)(DWORD);
#define CTRL_C_EVENT     0
#define CTRL_BREAK_EVENT 1

#define CTRL_HANDLER_MAX 8
static PHANDLER_ROUTINE g_ctrl_handlers[CTRL_HANDLER_MAX];
static int              g_ctrl_handler_count = 0;

static void posix_sigint_handler(int /*sig*/) {
  for( int i = g_ctrl_handler_count - 1; i >= 0; --i )
    if( g_ctrl_handlers[i](CTRL_C_EVENT) ) return;
}
extern "C" EXPORT BOOL kernel32_SetConsoleCtrlHandler(PHANDLER_ROUTINE handler, BOOL add) {
  if( !handler ) { signal(SIGINT, add ? SIG_IGN : SIG_DFL); return TRUE; }
  if( add ) {
    if( g_ctrl_handler_count < CTRL_HANDLER_MAX )
      g_ctrl_handlers[g_ctrl_handler_count++] = handler;
    signal(SIGINT, posix_sigint_handler);
  } else {
    for( int i = 0; i < g_ctrl_handler_count; ++i ) {
      if( g_ctrl_handlers[i] == handler ) {
        g_ctrl_handlers[i] = g_ctrl_handlers[--g_ctrl_handler_count];
        break;
      }
    }
    if( g_ctrl_handler_count == 0 ) signal(SIGINT, SIG_DFL);
  }
  return TRUE;
}

// ---------------------------------------------------------------------------
// DeleteFileW, RemoveDirectoryW, MoveFileW, CreateHardLinkW
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL kernel32_DeleteFileW(const uint16_t* path) {
  char utf8[PATH_MAX]; wchar_to_utf8(path, utf8, sizeof(utf8));
  return kernel32_DeleteFileA(utf8);
}
extern "C" EXPORT BOOL kernel32_RemoveDirectoryW(const uint16_t* path) {
  char utf8[PATH_MAX], posix[PATH_MAX];
  wchar_to_utf8(path, utf8, sizeof(utf8));
  win_path_to_posix(utf8, posix, sizeof(posix));
  if( rmdir(posix) != 0 ) { set_errno_error(); return FALSE; }
  return TRUE;
}
extern "C" EXPORT BOOL kernel32_MoveFileW(const uint16_t* from, const uint16_t* to) {
  char f8[PATH_MAX], t8[PATH_MAX], fp[PATH_MAX], tp[PATH_MAX];
  wchar_to_utf8(from, f8, sizeof(f8)); wchar_to_utf8(to, t8, sizeof(t8));
  win_path_to_posix(f8, fp, sizeof(fp)); win_path_to_posix(t8, tp, sizeof(tp));
  if( rename(fp, tp) != 0 ) { set_errno_error(); return FALSE; }
  return TRUE;
}
extern "C" EXPORT BOOL kernel32_CreateHardLinkW(const uint16_t* lnk, const uint16_t* tgt, void* /*sa*/) {
  char l8[PATH_MAX], t8[PATH_MAX], lp[PATH_MAX], tp[PATH_MAX];
  wchar_to_utf8(lnk, l8, sizeof(l8)); wchar_to_utf8(tgt, t8, sizeof(t8));
  win_path_to_posix(l8, lp, sizeof(lp)); win_path_to_posix(t8, tp, sizeof(tp));
  if( ::link(tp, lp) != 0 ) { set_errno_error(); return FALSE; }
  return TRUE;
}
extern "C" EXPORT BOOL kernel32_CreateHardLinkA(LPCSTR lnk, LPCSTR tgt, void* sa) {
  uint16_t wlnk[PATH_MAX], wtgt[PATH_MAX];
  utf8_to_wchar(lnk, wlnk, PATH_MAX); utf8_to_wchar(tgt, wtgt, PATH_MAX);
  return kernel32_CreateHardLinkW(wlnk, wtgt, sa);
}

// ---------------------------------------------------------------------------
// GetFileInformationByHandle
// ---------------------------------------------------------------------------
struct BY_HANDLE_FILE_INFORMATION {
  DWORD    dwFileAttributes;
  FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;
  DWORD    dwVolumeSerialNumber, nFileSizeHigh, nFileSizeLow, nNumberOfLinks;
  DWORD    nFileIndexHigh, nFileIndexLow;
};
extern "C" EXPORT BOOL kernel32_GetFileInformationByHandle(HANDLE h, BY_HANDLE_FILE_INFORMATION* info) {
  int fd = get_fd(h);
  if( fd < 0 || !info ) return FALSE;
  struct stat st;
  if( fstat(fd, &st) != 0 ) { set_errno_error(); return FALSE; }
  memset(info, 0, sizeof(*info));
  info->dwFileAttributes   = stat_to_win_attrs(&st, "");
  info->ftCreationTime     = u64_to_ft((uint64_t)st.st_mtime * 10000000ULL + FILETIME_EPOCH);
  info->ftLastAccessTime   = u64_to_ft((uint64_t)st.st_atime * 10000000ULL + FILETIME_EPOCH);
  info->ftLastWriteTime    = u64_to_ft((uint64_t)st.st_mtime * 10000000ULL + FILETIME_EPOCH);
  info->dwVolumeSerialNumber = (DWORD)(st.st_dev & 0xFFFFFFFFu);
  info->nFileSizeHigh      = (DWORD)(st.st_size >> 32);
  info->nFileSizeLow       = (DWORD)(st.st_size & 0xFFFFFFFFu);
  info->nNumberOfLinks     = (DWORD)st.st_nlink;
  info->nFileIndexHigh     = (DWORD)(st.st_ino >> 32);
  info->nFileIndexLow      = (DWORD)(st.st_ino & 0xFFFFFFFFu);
  return TRUE;
}

// ---------------------------------------------------------------------------
// GetFileTime
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL kernel32_GetFileTime(HANDLE h, FILETIME* ctime, FILETIME* atime, FILETIME* mtime) {
  int fd = get_fd(h);
  if( fd < 0 ) return FALSE;
  struct stat st;
  if( fstat(fd, &st) != 0 ) { set_errno_error(); return FALSE; }
  FILETIME mt = u64_to_ft((uint64_t)st.st_mtime * 10000000ULL + FILETIME_EPOCH);
  if( ctime ) *ctime = mt;
  if( atime ) *atime = u64_to_ft((uint64_t)st.st_atime * 10000000ULL + FILETIME_EPOCH);
  if( mtime ) *mtime = mt;
  return TRUE;
}

// ---------------------------------------------------------------------------
// GetSystemTime, SystemTimeToFileTime, SystemTimeToTzSpecificLocalTime, TzSpecificLocalTimeToSystemTime
// ---------------------------------------------------------------------------
static void posix_time_to_systemtime(time_t t, DWORD ms, SYSTEMTIME* st) {
  struct tm tm; gmtime_r(&t, &tm);
  st->wYear = (WORD)(tm.tm_year + 1900); st->wMonth = (WORD)(tm.tm_mon + 1);
  st->wDayOfWeek = (WORD)tm.tm_wday;     st->wDay   = (WORD)tm.tm_mday;
  st->wHour      = (WORD)tm.tm_hour;     st->wMinute = (WORD)tm.tm_min;
  st->wSecond    = (WORD)tm.tm_sec;      st->wMilliseconds = (WORD)ms;
}
static time_t systemtime_to_posix(const SYSTEMTIME* st) {
  struct tm tm = {};
  tm.tm_year = st->wYear - 1900; tm.tm_mon = st->wMonth - 1;
  tm.tm_mday = st->wDay;         tm.tm_hour = st->wHour;
  tm.tm_min  = st->wMinute;      tm.tm_sec  = st->wSecond;
  return timegm(&tm);
}
extern "C" EXPORT void kernel32_GetSystemTime(SYSTEMTIME* st) {
  if( !st ) return;
  struct timespec ts; clock_gettime(CLOCK_REALTIME, &ts);
  posix_time_to_systemtime(ts.tv_sec, (DWORD)(ts.tv_nsec / 1000000), st);
}
extern "C" EXPORT BOOL kernel32_SystemTimeToFileTime(const SYSTEMTIME* st, FILETIME* ft) {
  if( !st || !ft ) return FALSE;
  time_t t = systemtime_to_posix(st);
  if( t == (time_t)-1 ) return FALSE;
  uint64_t v = (uint64_t)t * 10000000ULL + FILETIME_EPOCH + (uint64_t)st->wMilliseconds * 10000ULL;
  *ft = u64_to_ft(v); return TRUE;
}
extern "C" EXPORT BOOL kernel32_SystemTimeToTzSpecificLocalTime(void* /*tz*/, const SYSTEMTIME* utc, SYSTEMTIME* local) {
  if( !utc || !local ) return FALSE;
  time_t t = systemtime_to_posix(utc);
  struct tm loc; localtime_r(&t, &loc);
  local->wYear = (WORD)(loc.tm_year + 1900); local->wMonth = (WORD)(loc.tm_mon + 1);
  local->wDayOfWeek = (WORD)loc.tm_wday;     local->wDay   = (WORD)loc.tm_mday;
  local->wHour      = (WORD)loc.tm_hour;     local->wMinute = (WORD)loc.tm_min;
  local->wSecond    = (WORD)loc.tm_sec;      local->wMilliseconds = utc->wMilliseconds;
  return TRUE;
}
extern "C" EXPORT BOOL kernel32_TzSpecificLocalTimeToSystemTime(void* /*tz*/, const SYSTEMTIME* local, SYSTEMTIME* utc) {
  if( !local || !utc ) return FALSE;
  struct tm tm = {};
  tm.tm_year = local->wYear - 1900; tm.tm_mon = local->wMonth - 1;
  tm.tm_mday = local->wDay;         tm.tm_hour = local->wHour;
  tm.tm_min  = local->wMinute;      tm.tm_sec  = local->wSecond;
  tm.tm_isdst = -1;
  time_t t = mktime(&tm);
  posix_time_to_systemtime(t, local->wMilliseconds, utc);
  return TRUE;
}

// ---------------------------------------------------------------------------
// LocalFileTimeToFileTime
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL kernel32_LocalFileTimeToFileTime(const FILETIME* local, FILETIME* utc) {
  if( !local || !utc ) return FALSE;
  time_t now = time(nullptr); struct tm loc; localtime_r(&now, &loc);
  int64_t off = (int64_t)loc.tm_gmtoff * 10000000LL;
  *utc = u64_to_ft(ft_to_u64(*local) - (uint64_t)off);
  return TRUE;
}

// ---------------------------------------------------------------------------
// GetVersionExW — reports Windows 7 SP1 x64
// OSVERSIONINFOW:  size 276 (4+4+4+4+4 + WCHAR[128]=256)
// OSVERSIONINFOEXW: size 284 (+ WORD[3] + BYTE[2])
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL kernel32_GetVersionExW(void* buf) {
  if( !buf ) return FALSE;
  uint32_t sz = *(uint32_t*)buf;
  if( sz < 276 ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }
  uint8_t* b = (uint8_t*)buf;
  memset(b + 4, 0, sz - 4);
  *(uint32_t*)(b+4)  = 6;    // dwMajorVersion
  *(uint32_t*)(b+8)  = 1;    // dwMinorVersion
  *(uint32_t*)(b+12) = 7601; // dwBuildNumber
  *(uint32_t*)(b+16) = 2;    // dwPlatformId = VER_PLATFORM_WIN32_NT
  // szCSDVersion[128] at offset 20 — already zero (L"")
  if( sz >= 284 ) {
    *(uint16_t*)(b+276) = 1; // wServicePackMajor
    *(uint16_t*)(b+278) = 0; // wServicePackMinor
    *(uint16_t*)(b+280) = 0; // wSuiteMask
    *(uint8_t*) (b+282) = 1; // wProductType = VER_NT_WORKSTATION
  }
  return TRUE;
}

// ---------------------------------------------------------------------------
// GetSystemDirectoryW, GetVolumeInformationW, GetDiskFreeSpaceExW, GetDriveTypeW
// ---------------------------------------------------------------------------
extern "C" EXPORT UINT kernel32_GetSystemDirectoryW(uint16_t* buf, UINT size) {
  const char* dir = "C:\\Windows\\System32";
  UINT n = (UINT)strlen(dir);
  if( buf && size > n ) utf8_to_wchar(dir, buf, size);
  return n;
}
extern "C" EXPORT UINT kernel32_GetSystemDirectoryA(LPSTR buf, UINT size) {
  const char* dir = "C:\\Windows\\System32";
  UINT n = (UINT)strlen(dir);
  if( buf && size > n ) { strncpy(buf, dir, size-1); buf[size-1] = '\0'; }
  return n;
}
extern "C" EXPORT BOOL kernel32_GetVolumeInformationW(const uint16_t* /*root*/,
    uint16_t* volname, DWORD vsz, DWORD* serial, DWORD* max_comp, DWORD* flags,
    uint16_t* fsname, DWORD fssz) {
  if( volname && vsz ) utf8_to_wchar("Volume", volname, vsz);
  if( serial    ) *serial   = 0x12345678u;
  if( max_comp  ) *max_comp = 255;
  if( flags     ) *flags    = 3u; // FILE_CASE_PRESERVED_NAMES | FILE_CASE_SENSITIVE_SEARCH
  if( fsname && fssz ) utf8_to_wchar("NTFS", fsname, fssz);
  return TRUE;
}
extern "C" EXPORT BOOL kernel32_GetVolumeInformationA(LPCSTR /*root*/,
    LPSTR volname, DWORD vsz, DWORD* serial, DWORD* max_comp, DWORD* flags,
    LPSTR fsname, DWORD fssz) {
  if( volname && vsz ) { strncpy(volname, "Volume", vsz-1); volname[vsz-1] = '\0'; }
  if( serial    ) *serial   = 0x12345678u;
  if( max_comp  ) *max_comp = 255;
  if( flags     ) *flags    = 3u;
  if( fsname && fssz ) { strncpy(fsname, "NTFS", fssz-1); fsname[fssz-1] = '\0'; }
  return TRUE;
}
extern "C" EXPORT BOOL kernel32_GetDiskFreeSpaceExW(const uint16_t* /*path*/,
    uint64_t* avail, uint64_t* total, uint64_t* totalfree) {
  struct statvfs vfs;
  if( statvfs("/", &vfs) != 0 ) {
    if(avail)*avail=0; if(total)*total=0; if(totalfree)*totalfree=0; return FALSE;
  }
  uint64_t blk = vfs.f_frsize ? vfs.f_frsize : vfs.f_bsize;
  if( avail     ) *avail     = blk * vfs.f_bavail;
  if( total     ) *total     = blk * vfs.f_blocks;
  if( totalfree ) *totalfree = blk * vfs.f_bfree;
  return TRUE;
}
extern "C" EXPORT BOOL kernel32_GetDiskFreeSpaceExA(LPCSTR /*path*/,
    uint64_t* avail, uint64_t* total, uint64_t* totalfree) {
  return kernel32_GetDiskFreeSpaceExW(nullptr, avail, total, totalfree);
}
extern "C" EXPORT DWORD kernel32_GetDriveTypeW(const uint16_t* /*path*/) { return 3; } // DRIVE_FIXED

// ---------------------------------------------------------------------------
// GetFullPathNameA
// ---------------------------------------------------------------------------
extern "C" EXPORT DWORD kernel32_GetFullPathNameA(LPCSTR path, DWORD size, LPSTR buf, LPSTR* filepart) {
  uint16_t wpath[PATH_MAX], wbuf[PATH_MAX]; LPWSTR wfp = nullptr;
  utf8_to_wchar(path, wpath, PATH_MAX);
  DWORD r = kernel32_GetFullPathNameW(wpath, PATH_MAX, wbuf, &wfp);
  char narrow[PATH_MAX]; wchar_to_utf8(wbuf, narrow, sizeof(narrow));
  DWORD n = (DWORD)strlen(narrow);
  if( buf && size > 0 ) {
    strncpy(buf, narrow, size - 1); buf[size - 1] = '\0';
    if( filepart ) {
      char* s = strrchr(buf, '\\'); if(!s) s = strrchr(buf, '/');
      *filepart = s ? s + 1 : buf;
    }
  }
  (void)r; return n;
}

// ---------------------------------------------------------------------------
// GetLongPathNameW / GetShortPathNameW — identity stubs
// ---------------------------------------------------------------------------
extern "C" EXPORT DWORD kernel32_GetLongPathNameW(const uint16_t* path, uint16_t* buf, DWORD sz) {
  if( !path ) return 0;
  DWORD n = 0; while( path[n] ) n++;
  if( buf && sz > n ) { for(DWORD i=0;i<=n;i++) buf[i]=path[i]; }
  return n;
}
extern "C" EXPORT DWORD kernel32_GetShortPathNameW(const uint16_t* path, uint16_t* buf, DWORD sz) {
  return kernel32_GetLongPathNameW(path, buf, sz);
}
extern "C" EXPORT DWORD kernel32_GetLongPathNameA(LPCSTR path, LPSTR buf, DWORD sz) {
  uint16_t wpath[PATH_MAX], wbuf[PATH_MAX];
  utf8_to_wchar(path, wpath, PATH_MAX);
  DWORD n = kernel32_GetLongPathNameW(wpath, wbuf, PATH_MAX);
  if( buf && sz ) wchar_to_utf8(wbuf, buf, sz);
  return n;
}
extern "C" EXPORT DWORD kernel32_GetShortPathNameA(LPCSTR path, LPSTR buf, DWORD sz) {
  return kernel32_GetLongPathNameA(path, buf, sz);
}

// ---------------------------------------------------------------------------
// ExpandEnvironmentStringsW
// ---------------------------------------------------------------------------
extern "C" EXPORT DWORD kernel32_ExpandEnvironmentStringsW(const uint16_t* src, uint16_t* dst, DWORD size) {
  char narrow[32768], out[32768];
  wchar_to_utf8(src, narrow, sizeof(narrow));
  const char* p = narrow; char* q = out; char* end = out + sizeof(out) - 1;
  while( *p && q < end ) {
    if( *p == '%' ) {
      const char* ns = p + 1; const char* ne = strchr(ns, '%');
      if( ne ) {
        char name[256]; size_t nl = (size_t)(ne - ns);
        if( nl < sizeof(name) ) {
          memcpy(name, ns, nl); name[nl] = '\0';
          const char* val = getenv(name);
          if( val ) {
            size_t vl = strlen(val);
            if( q + vl < end ) { memcpy(q, val, vl); q += vl; }
            p = ne + 1; continue;
          }
        }
      }
    }
    *q++ = *p++;
  }
  *q = '\0';
  if( !dst || size == 0 ) return (DWORD)(strlen(out) + 1);
  return (DWORD)utf8_to_wchar(out, dst, size) + 1;
}

// ---------------------------------------------------------------------------
// FoldStringW — best-effort case fold
// ---------------------------------------------------------------------------
extern "C" EXPORT int kernel32_FoldStringW(DWORD flags, const uint16_t* src, int src_len,
                                            uint16_t* dst, int dst_size) {
  if( !src ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return 0; }
  int n = (src_len < 0) ? 0 : src_len;
  if( src_len < 0 ) { while(src[n]) n++; n++; } // include NUL
  if( !dst || dst_size == 0 ) return n;
  int w = (n < dst_size) ? n : dst_size;
  for( int i = 0; i < w; i++ ) {
    uint16_t c = src[i];
    if( flags & LCMAP_LOWERCASE ) c = (uint16_t)towlower(c);
    else if( flags & LCMAP_UPPERCASE ) c = (uint16_t)towupper(c);
    dst[i] = c;
  }
  return w;
}
extern "C" EXPORT int kernel32_FoldStringA(DWORD flags, LPCSTR src, int src_len, LPSTR dst, int dst_size) {
  if( !src ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return 0; }
  uint16_t wsrc[PATH_MAX], wdst[PATH_MAX];
  int n = src_len < 0 ? (int)strlen(src)+1 : src_len;
  utf8_to_wchar(src, wsrc, PATH_MAX);
  int r = kernel32_FoldStringW(flags, wsrc, n, wdst, PATH_MAX);
  if( dst && dst_size ) wchar_to_utf8(wdst, dst, (size_t)dst_size);
  return r;
}

// ---------------------------------------------------------------------------
// CompareStringA
// ---------------------------------------------------------------------------
extern "C" EXPORT int kernel32_CompareStringA(DWORD /*locale*/, DWORD flags,
                                               LPCSTR s1, int n1, LPCSTR s2, int n2) {
  if( !s1 || !s2 ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return 0; }
  int r;
  if( n1 < 0 && n2 < 0 ) {
    r = (flags & NORM_IGNORECASE) ? strcasecmp(s1, s2) : strcmp(s1, s2);
  } else {
    size_t c1 = (n1<0) ? strlen(s1) : (size_t)n1;
    size_t c2 = (n2<0) ? strlen(s2) : (size_t)n2;
    r = (flags & NORM_IGNORECASE) ? strncasecmp(s1, s2, c1<c2?c1:c2) : strncmp(s1, s2, c1<c2?c1:c2);
    if( r == 0 ) r = (int)c1 - (int)c2;
  }
  return (r<0) ? CSTR_LESS_THAN : (r>0) ? CSTR_GREATER_THAN : CSTR_EQUAL;
}

// ---------------------------------------------------------------------------
// CreateEventW, CreateSemaphoreW, WaitForSingleObjectEx, LoadLibraryW
// ---------------------------------------------------------------------------
extern "C" EXPORT HANDLE kernel32_CreateEventW(void* sa, BOOL manual_reset, BOOL initial, const uint16_t* /*name*/) {
  return kernel32_CreateEventA(sa, manual_reset, initial, nullptr);
}
extern "C" EXPORT HANDLE kernel32_CreateSemaphoreW(void* sa, LONG initial, LONG max_count, const uint16_t* /*name*/) {
  return kernel32_CreateSemaphoreA(sa, initial, max_count, nullptr);
}
extern "C" EXPORT DWORD kernel32_WaitForSingleObjectEx(HANDLE h, DWORD ms, BOOL /*alertable*/) {
  return kernel32_WaitForSingleObject(h, ms);
}
extern "C" EXPORT HANDLE kernel32_LoadLibraryW(const uint16_t* name) {
  return kernel32_LoadLibraryExW(name, NULL, 0);
}

// ---------------------------------------------------------------------------
// SetEnvironmentVariableA, IsDBCSLeadByte, SetErrorMode, SetPriorityClass,
// SetThreadExecutionState, BackupRead, BackupSeek, DeviceIoControl
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL kernel32_SetEnvironmentVariableA(LPCSTR name, LPCSTR value) {
  if( !value ) { unsetenv(name); return TRUE; }
  return setenv(name, value, 1) == 0 ? TRUE : FALSE;
}
extern "C" EXPORT BOOL kernel32_IsDBCSLeadByte(BYTE /*c*/) { return FALSE; }
extern "C" EXPORT UINT kernel32_SetErrorMode(UINT /*mode*/) { return 0; }
extern "C" EXPORT BOOL kernel32_SetPriorityClass(HANDLE /*h*/, DWORD /*cls*/) { return TRUE; }
extern "C" EXPORT DWORD kernel32_SetThreadExecutionState(DWORD /*flags*/) { return 1; }
extern "C" EXPORT BOOL kernel32_BackupRead(HANDLE /*h*/, BYTE* /*buf*/, DWORD /*n*/,
    DWORD* nRead, BOOL /*abort*/, BOOL /*sec*/, void** /*ctx*/) {
  if(nRead) *nRead=0; return FALSE;
}
extern "C" EXPORT BOOL kernel32_BackupSeek(HANDLE /*h*/, DWORD /*lo*/, DWORD /*hi*/,
    DWORD* sl, DWORD* sh, void** /*ctx*/) {
  if(sl)*sl=0; if(sh)*sh=0; return FALSE;
}
extern "C" EXPORT BOOL kernel32_DeviceIoControl(HANDLE /*h*/, DWORD /*code*/,
    void* /*in*/, DWORD /*isz*/, void* /*out*/, DWORD /*osz*/,
    DWORD* returned, void* /*ovl*/) {
  if(returned)*returned=0; SET_LAST_ERROR(ERROR_CALL_NOT_IMPLEMENTED); return FALSE;
}
