#pragma once
// kernel32 A-variant wrappers and a couple of tail-end miscellaneous
// kernel32 entries — included from shim.cpp.
//
// Most of these are thin char* → wchar* conversions that delegate to the
// W-variant defined in shim.cpp, plus tiny stubs (GetDriveTypeA,
// GetDiskFreeSpace, GetVersionEx, RtlFillMemory, RtlCompareMemory) that
// don't fit anywhere else.
//
// References from shim.cpp: win_path_to_posix, utf8_to_wchar,
// errno_to_win32, kernel32_LoadLibraryExW, kernel32_ReadFile.

extern "C" EXPORT BOOL kernel32_MoveFileA(LPCSTR from, LPCSTR to) {
  char pf[PATH_MAX], pt[PATH_MAX];
  win_path_to_posix(from, pf, sizeof(pf));
  win_path_to_posix(to,   pt, sizeof(pt));
  if( rename(pf, pt) == 0 ) return TRUE;
  SET_LAST_ERROR(errno_to_win32(errno)); return FALSE;
}
extern "C" EXPORT BOOL kernel32_RemoveDirectoryA(LPCSTR path) {
  char p[PATH_MAX]; win_path_to_posix(path, p, sizeof(p));
  if( rmdir(p) == 0 ) return TRUE;
  SET_LAST_ERROR(errno_to_win32(errno)); return FALSE;
}
extern "C" EXPORT BOOL kernel32_SetCurrentDirectoryA(LPCSTR path) {
  char p[PATH_MAX]; win_path_to_posix(path, p, sizeof(p));
  if( chdir(p) == 0 ) return TRUE;
  SET_LAST_ERROR(errno_to_win32(errno)); return FALSE;
}
extern "C" EXPORT DWORD kernel32_ExpandEnvironmentStringsA(LPCSTR src, LPSTR dst, DWORD size) {
  if( !src ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return 0; }
  // Simple: expand %VAR% patterns using getenv
  char out[PATH_MAX*2]; size_t pos = 0;
  for( const char* p = src; *p && pos+2<sizeof(out); ) {
    if( *p == '%' ) {
      const char* e = strchr(p+1,'%');
      if( e ) {
        char var[256]; int vl = (int)(e-p-1); if(vl>=256) vl=255;
        memcpy(var,p+1,vl); var[vl]='\0';
        const char* val = getenv(var);
        if( val ) { size_t vlen=strlen(val); if(pos+vlen<sizeof(out)){memcpy(out+pos,val,vlen);pos+=vlen;} }
        else { if(pos+vl+2<sizeof(out)){out[pos++]='%';memcpy(out+pos,var,vl);pos+=vl;out[pos++]='%';} }
        p = e+1; continue;
      }
    }
    out[pos++] = *p++;
  }
  out[pos] = '\0';
  DWORD need = (DWORD)(pos+1);
  if( dst && size >= need ) { memcpy(dst, out, need); return need; }
  if( dst && size > 0 ) { memcpy(dst, out, size-1); dst[size-1]='\0'; }
  return need;
}
extern "C" EXPORT HANDLE kernel32_LoadLibraryExA(LPCSTR name, HANDLE /*reserved*/, DWORD flags) {
  if( !name ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return NULL_HANDLE; }
  uint16_t wname[PATH_MAX];
  utf8_to_wchar(name, wname, PATH_MAX);
  return kernel32_LoadLibraryExW(wname, NULL_HANDLE, flags);
}
extern "C" EXPORT DWORD kernel32_GetDriveTypeA(LPCSTR /*path*/) { return 3; } // DRIVE_FIXED
extern "C" EXPORT BOOL kernel32_GetDiskFreeSpaceA(LPCSTR /*root*/,
    DWORD* sectors_per_cluster, DWORD* bytes_per_sector,
    DWORD* free_clusters, DWORD* total_clusters) {
  struct statvfs vfs;
  if( statvfs("/", &vfs) != 0 ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }
  DWORD bps  = (DWORD)(vfs.f_frsize ? vfs.f_frsize : vfs.f_bsize);
  DWORD spc  = 1;
  // Clamp to 32-bit friendly values
  while( bps > 4096 && spc < 64 ) { bps /= 2; spc *= 2; }
  if( sectors_per_cluster ) *sectors_per_cluster = spc;
  if( bytes_per_sector    ) *bytes_per_sector    = bps;
  if( free_clusters       ) *free_clusters       = (DWORD)vfs.f_bavail;
  if( total_clusters      ) *total_clusters      = (DWORD)vfs.f_blocks;
  return TRUE;
}
extern "C" EXPORT BOOL kernel32_GetDiskFreeSpaceW(const uint16_t* /*root*/,
    DWORD* sectors_per_cluster, DWORD* bytes_per_sector,
    DWORD* free_clusters, DWORD* total_clusters) {
  return kernel32_GetDiskFreeSpaceA(nullptr, sectors_per_cluster, bytes_per_sector,
                                    free_clusters, total_clusters);
}
extern "C" EXPORT BOOL kernel32_GetVersionExA(void* buf) {
  if( !buf ) return FALSE;
  uint32_t sz = *(uint32_t*)buf; uint8_t* b = (uint8_t*)buf;
  if( sz < 148 ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }
  memset(b+4, 0, sz-4);
  *(uint32_t*)(b+4)  = 6;    // dwMajorVersion
  *(uint32_t*)(b+8)  = 1;    // dwMinorVersion
  *(uint32_t*)(b+12) = 7601; // dwBuildNumber
  *(uint32_t*)(b+16) = 2;    // dwPlatformId = VER_PLATFORM_WIN32_NT
  memcpy(b+20, "Service Pack 1\0", 15); // szCSDVersion[128]
  if( sz >= 156 ) {
    *(uint16_t*)(b+148) = 1; // wServicePackMajor
    *(uint16_t*)(b+150) = 0; // wServicePackMinor
    *(uint16_t*)(b+152) = 0; // wSuiteMask
    *(uint8_t*) (b+154) = 1; // wProductType = VER_NT_WORKSTATION
  }
  return TRUE;
}
extern "C" EXPORT DWORD kernel32_GetVersion(void) {
  // LOBYTE(LOWORD)=major=6, HIBYTE(LOWORD)=minor=1, HIWORD=build=7601
  return (7601u << 16) | (1u << 8) | 6u;
}
extern "C" EXPORT DWORD kernel32_ReadConsoleA(HANDLE h, LPVOID buf, DWORD toread,
    LPDWORD read_out, void* /*input_control*/) {
  // Delegate to ReadFile on stdin handle
  return kernel32_ReadFile(h, buf, toread, read_out, nullptr);
}
extern "C" EXPORT void kernel32_RtlFillMemory(void* dest, size_t len, uint8_t fill) {
  if(dest && len) memset(dest, fill, len);
}
extern "C" EXPORT size_t kernel32_RtlCompareMemory(const void* s1, const void* s2, size_t len) {
  const uint8_t* a = (const uint8_t*)s1;
  const uint8_t* b = (const uint8_t*)s2;
  size_t i = 0;
  for(; i < len && a[i] == b[i]; ++i) {}
  return i;
}
