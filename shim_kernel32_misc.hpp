#pragma once
// Additional KERNEL32 routines that don't fit cleanly elsewhere — included
// from shim.cpp before shim_kernel32_sync.hpp.
//
// Covers: GetModuleHandleA, IsDBCSLeadByteEx, VirtualProtect, VirtualQuery
// (parses /proc/self/maps), CreateDirectoryW, FindFirstFileW (delegates to
// FindFirstFileExW), FormatMessageW (wraps FormatMessageA), GetFullPathNameW,
// LocalFree.
//
// References from shim.cpp: g_image_base, FAKE_WIN_MODULE,
// win_path_to_posix, posix_to_win_path, utf8_to_wchar, wchar_to_utf8,
// prot_from_protect, set_errno_error, kernel32_FindFirstFileExW,
// kernel32_FormatMessageA, win_dll_basename, win_dll_classify,
// WIN_MODULE_HANDLE.

extern "C" EXPORT HANDLE kernel32_GetModuleHandleA(LPCSTR name) {
  if( !name ) return (HANDLE)g_image_base;
  char posix[4096];
  win_path_to_posix(name, posix, sizeof(posix));
  void* h = dlopen(posix, RTLD_NOLOAD|RTLD_LAZY);
  if( h ) return h;
  // Mirror the W variant: classify the name and return a per-DLL
  // sentinel; anything we don't recognise must report not-found, not a
  // generic kernel32 handle (which would mis-route subsequent
  // GetProcAddress lookups).
  char base[64];
  win_dll_basename(name, base, sizeof(base));
  int wm = win_dll_classify(base);
  if( wm < 0 ) {
    SET_LAST_ERROR(ERROR_MOD_NOT_FOUND);
    return NULL;
  }
  SET_LAST_ERROR(ERROR_SUCCESS);
  return WIN_MODULE_HANDLE(wm);
}
extern "C" EXPORT BOOL kernel32_IsDBCSLeadByteEx(UINT /*cp*/, BYTE /*b*/) { return FALSE; }
extern "C" EXPORT BOOL kernel32_VirtualProtect(LPVOID addr, size_t size, DWORD np, DWORD* op) {
  if( op ) *op = PAGE_READWRITE;
  uintptr_t pa = (uintptr_t)addr & ~(uintptr_t)4095;
  size_t ps = (((uintptr_t)addr + size - pa + 4095) & ~(size_t)4095);
  if( mprotect((void*)pa, ps, prot_from_protect(np)) != 0 ) { set_errno_error(); return FALSE; }
  return TRUE;
}
#ifndef MEM_FREE
#define MEM_FREE    0x10000u
#define MEM_PRIVATE 0x20000u
#endif
extern "C" EXPORT size_t kernel32_VirtualQuery(LPCVOID addr, void* buf, size_t buflen) {
  if( !buf || buflen < 28 ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return 0; }
  uint8_t* mbi = (uint8_t*)buf;
  size_t outsz = buflen < 48 ? buflen : 48;
  memset(mbi, 0, outsz);
  uintptr_t target = (uintptr_t)addr;
  FILE* f = fopen("/proc/self/maps", "r");
  if( f ) {
    char line[256];
    while( fgets(line, sizeof(line), f) ) {
      uintptr_t s, e; char perms[8];
      if( sscanf(line, "%lx-%lx %7s", &s, &e, perms) < 3 ) continue;
      if( s <= target && target < e ) {
        DWORD prot = PAGE_NOACCESS;
        if( perms[0]=='r' && perms[1]=='w' && perms[2]=='x' ) prot = PAGE_EXECUTE_READWRITE;
        else if( perms[0]=='r' && perms[1]=='w' ) prot = PAGE_READWRITE;
        else if( perms[0]=='r' && perms[2]=='x' ) prot = PAGE_EXECUTE_READ;
        else if( perms[0]=='r' ) prot = PAGE_READONLY;
        else if( perms[2]=='x' ) prot = PAGE_EXECUTE;
        if( buflen >= 8  ) *(uintptr_t*)(mbi+0)  = s;
        if( buflen >= 16 ) *(uintptr_t*)(mbi+8)  = s;
        if( buflen >= 20 ) *(uint32_t*) (mbi+16) = prot;
        if( buflen >= 32 ) *(uintptr_t*)(mbi+24) = e - s;
        if( buflen >= 36 ) *(uint32_t*) (mbi+32) = MEM_COMMIT;
        if( buflen >= 40 ) *(uint32_t*) (mbi+36) = prot;
        if( buflen >= 44 ) *(uint32_t*) (mbi+40) = MEM_PRIVATE;
        fclose(f); return outsz;
      }
    }
    fclose(f);
  }
  if( buflen >= 8  ) *(uintptr_t*)(mbi+0)  = target & ~(uintptr_t)0xFFF;
  if( buflen >= 32 ) *(uintptr_t*)(mbi+24) = 0x1000;
  if( buflen >= 36 ) *(uint32_t*) (mbi+32) = MEM_FREE;
  return buflen < 28 ? buflen : 28;
}

extern "C" EXPORT BOOL kernel32_CreateDirectoryW(LPCWSTR path, SECURITY_ATTRIBUTES* sa) {
  (void)sa;
  char narrow[PATH_MAX], posix[PATH_MAX];
  wchar_to_utf8((const uint16_t*)path, narrow, sizeof(narrow));
  win_path_to_posix(narrow, posix, sizeof(posix));
  if( mkdir(posix, 0777) != 0 ) { set_errno_error(); return FALSE; }
  return TRUE;
}

extern "C" EXPORT HANDLE kernel32_FindFirstFileW(LPCWSTR pattern, WIN32_FIND_DATAW* pfd) {
  return kernel32_FindFirstFileExW(pattern, 0, pfd, 0, nullptr, 0);
}

extern "C" EXPORT DWORD kernel32_FormatMessageW(DWORD flags, LPCVOID src, DWORD msgId, DWORD lang, LPWSTR buf, DWORD size, va_list* args) {
  char narrow[4096];
  DWORD n = kernel32_FormatMessageA(flags & ~0x100u, src, msgId, lang, narrow, sizeof(narrow), args);
  if( n == 0 )
    n = (DWORD)snprintf(narrow, sizeof(narrow), "Error %u", (unsigned)msgId);
  if( flags & 0x100u ) {
    // FORMAT_MESSAGE_ALLOCATE_BUFFER: buf is LPWSTR* — allocate and store pointer
    uint16_t* out = (uint16_t*)malloc((n + 1) * sizeof(uint16_t));
    if( !out ) return 0;
    for( DWORD i = 0; i < n; i++ ) out[i] = (uint16_t)(uint8_t)narrow[i];
    out[n] = 0;
    *(uint16_t**)buf = out;
    return n;
  }
  if( !buf || size == 0 ) return n;
  uint16_t* out = (uint16_t*)buf;
  DWORD i;
  for( i = 0; i < n && i < size - 1; i++ )
    out[i] = (uint16_t)(uint8_t)narrow[i];
  out[i] = 0;
  return i;
}

extern "C" EXPORT DWORD kernel32_GetFullPathNameW(LPCWSTR path, DWORD size, LPWSTR buf, LPWSTR* filepart) {
  char narrow[PATH_MAX], posix[PATH_MAX], resolved[PATH_MAX], win[PATH_MAX];
  wchar_to_utf8((const uint16_t*)path, narrow, sizeof(narrow));
  win_path_to_posix(narrow, posix, sizeof(posix));
  if( !realpath(posix, resolved) ) strncpy(resolved, posix, sizeof(resolved)-1);
  posix_to_win_path(resolved, win, sizeof(win));
  log_always("[SHIM] GetFullPathNameW(\"%s\" -> \"%s\")\n", narrow, win);
  DWORD needed = (DWORD)utf8_to_wchar(win, (uint16_t*)buf, size ? size : 0);
  if( buf && size > 0 && filepart ) {
    uint16_t* p = (uint16_t*)buf + needed;
    uint16_t* slash = (uint16_t*)buf;
    for( uint16_t* q = (uint16_t*)buf; q < p; q++ )
      if( *q == '\\' ) slash = q + 1;
    *filepart = slash < p ? slash : nullptr;
  }
  return needed;
}

extern "C" EXPORT void* kernel32_LocalFree(void* p) {
  free(p);
  return nullptr;
}
