#pragma once
// 7.8 Module / Library — included from shim.cpp.
//
// `LoadLibrary` / `FreeLibrary` / `GetProcAddress`: pe2elf resolves
// imports at conversion time, so these exist mainly to handle runtime
// LoadLibrary calls.  Real Windows DLL loading on Linux is out of scope;
// the `FAKE_WIN_MODULE` sentinel routes `GetProcAddress` against
// `RTLD_DEFAULT` so the shim's own exports satisfy lookups.
//
// References from shim.cpp: g_image_base, handle_alloc_module,
// handle_to_idx, g_handles, g_handles_mu, H_MODULE, H_FREE,
// wchar_to_utf8, utf8_to_wchar, win_path_to_posix, posix_to_win_path,
// set_errno_error, LOAD_LIBRARY_AS_DATAFILE.

// Typed pseudo-handles (B14/R27): values outside the handle-table range.
// FAKE_WIN_MODULE: any Windows DLL we can't load as a real .so.
// MAIN_IMAGE_MODULE: legacy sentinel kept for backward compat; at runtime
//   GetModuleHandleW(NULL) returns the real g_image_base so callers can
//   inspect the PE header (CRT does "cmp WORD PTR [rax], 'MZ'").
#define FAKE_WIN_MODULE  ((HANDLE)(intptr_t)(MAX_HANDLES+1))
#define MAIN_IMAGE_MODULE ((HANDLE)(intptr_t)(MAX_HANDLES+2))
// True when h refers to the main executable image
#define IS_MAIN_IMAGE(h) ((h)==MAIN_IMAGE_MODULE || (h)==(HANDLE)g_image_base)

extern "C" EXPORT HANDLE kernel32_GetModuleHandleW(LPCWSTR name) {
  if( !name )
    return (HANDLE)g_image_base;
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

extern "C" EXPORT BOOL kernel32_GetModuleHandleExW(DWORD flags, LPCWSTR name, HANDLE* phModule) {
  (void)flags;
  HANDLE h = kernel32_GetModuleHandleW(name);
  if( phModule )
    *phModule = h;
  return h ? TRUE : FALSE;
}
extern "C" EXPORT BOOL kernel32_GetModuleHandleExA(DWORD flags, LPCSTR name, HANDLE* phModule) {
  uint16_t wbuf[PATH_MAX];
  if( name ) utf8_to_wchar(name, wbuf, PATH_MAX);
  return kernel32_GetModuleHandleExW(flags, name ? wbuf : nullptr, phModule);
}

extern "C" EXPORT DWORD kernel32_GetModuleFileNameW(HANDLE h, LPWSTR buf, DWORD size) {
  char tmp[PATH_MAX];
  if( h==NULL||IS_MAIN_IMAGE(h) ) {
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
  char win[PATH_MAX]; posix_to_win_path(tmp, win, sizeof(win));
  return (DWORD)utf8_to_wchar(win, buf, size);
}

// LoadLibrary* / FreeLibrary: pe2elf resolves all PE imports at conversion time,
// so these exist only to satisfy explicit runtime LoadLibrary calls.  The result
// is a token for GetProcAddress lookups against the shim's own exports.  Real PE
// DLL loading on Linux is out of scope; TLS state (g_tls_callbacks_va et al.) is
// not extended for dynamically-loaded modules — the converter already flattened
// the import graph.
extern "C" EXPORT HANDLE kernel32_LoadLibraryExW(LPCWSTR name, HANDLE file, DWORD flags) {
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

extern "C" EXPORT BOOL kernel32_FreeLibrary(HANDLE h) {
  if( h==FAKE_WIN_MODULE||IS_MAIN_IMAGE(h) )
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

extern "C" EXPORT LPVOID kernel32_GetProcAddress(HANDLE h, LPCSTR name) {
  void* dlh;
  if( h==FAKE_WIN_MODULE||IS_MAIN_IMAGE(h)||h==NULL ) {
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
