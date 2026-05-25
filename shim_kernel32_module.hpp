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

// Typed pseudo-handles for Windows DLLs we can't load as .so files.  Each
// known Windows DLL gets a unique sentinel above the real-handle range; the
// sentinel encodes which shim-side prefix to use when GetProcAddress is
// called against it (`kernel32_FlsAlloc`, `user32_MessageBoxW`, ...).
// MAIN_IMAGE_MODULE follows the per-DLL sentinels; GetModuleHandleW(NULL)
// returns the real g_image_base so callers inspecting the PE header (CRT
// does "cmp WORD PTR [rax], 'MZ'") see actual MZ bytes.
enum WinModuleId {
  WM_KERNEL32 = 0,
  WM_USER32,
  WM_ADVAPI32,
  WM_SHELL32,
  WM_SHLWAPI,
  WM_WINMM,
  WM_MSVCRT,
  WM_COUNT,
};
static const char* const g_win_module_prefix[WM_COUNT] = {
  "kernel32_", "user32_", "advapi32_", "shell32_",
  "shlwapi_",  "winmm_",  "msvcrt_",
};
#define WIN_MODULE_BASE  ((intptr_t)(MAX_HANDLES+1))
#define WIN_MODULE_HANDLE(idx) ((HANDLE)(WIN_MODULE_BASE + (idx)))
#define IS_WIN_MODULE(h) ((intptr_t)(h) >= WIN_MODULE_BASE \
                       && (intptr_t)(h) < WIN_MODULE_BASE + WM_COUNT)
#define WIN_MODULE_IDX(h) ((int)((intptr_t)(h) - WIN_MODULE_BASE))
// Legacy alias: a generic "unknown Windows DLL" handle routes through the
// kernel32 prefix.  Used for GetModuleHandleW lookups of names we don't
// otherwise classify.
#define FAKE_WIN_MODULE   WIN_MODULE_HANDLE(WM_KERNEL32)
#define MAIN_IMAGE_MODULE ((HANDLE)(intptr_t)(MAX_HANDLES+1+WM_COUNT))
// True when h refers to the main executable image
#define IS_MAIN_IMAGE(h) ((h)==MAIN_IMAGE_MODULE || (h)==(HANDLE)g_image_base)

// Classify a Windows DLL name (already converted to lowercase UTF-8, without
// the optional ".dll" suffix) into one of the WM_* prefixes.  Returns -1
// for api-ms-win-*/ext-ms-win-* virtual DLLs that don't exist on Linux —
// LoadLibrary fails for these so the CRT's try_get_function fallthroughs
// reach the real "kernel32"/"user32"/... entry and pick up our prefix.
static int win_dll_classify(const char* lower) {
  if( !strcmp(lower, "kernel32") ) return WM_KERNEL32;
  if( !strcmp(lower, "user32"  ) ) return WM_USER32;
  if( !strcmp(lower, "advapi32") ) return WM_ADVAPI32;
  if( !strcmp(lower, "shell32" ) ) return WM_SHELL32;
  if( !strcmp(lower, "shlwapi" ) ) return WM_SHLWAPI;
  if( !strcmp(lower, "winmm"   ) ) return WM_WINMM;
  if( !strcmp(lower, "msvcrt"  ) ) return WM_MSVCRT;
  if( !strncmp(lower, "vcruntime", 9) ) return WM_MSVCRT;
  if( !strcmp(lower, "ucrtbase") ) return WM_MSVCRT;
  // api-ms-win-* / ext-ms-win-* are Windows API set forwarders.  They don't
  // exist on Linux; let LoadLibrary fail so the CRT walks through them.
  return -1;
}

// Build a lowercase, suffix-stripped basename ("kernel32.dll" → "kernel32").
static void win_dll_basename(const char* path, char* out, size_t out_sz) {
  const char* base = path;
  for( const char* p = path; *p; ++p )
    if( *p=='/' || *p=='\\' ) base = p+1;
  size_t n = 0;
  for( ; base[n] && n+1 < out_sz; ++n )
    out[n] = (char)tolower((unsigned char)base[n]);
  out[n] = 0;
  if( n>4 && !strcmp(out+n-4, ".dll") )
    out[n-4] = 0;
}

extern "C" EXPORT HANDLE kernel32_GetModuleHandleW(LPCWSTR name) {
  if( !name )
    return (HANDLE)g_image_base;
  char narrow[PATH_MAX], posix[PATH_MAX], base[64];
  wchar_to_utf8(name, narrow, sizeof(narrow));
  win_path_to_posix(narrow, posix, sizeof(posix));
  void* h = dlopen(posix, RTLD_NOLOAD|RTLD_LAZY);
  if( h )
    return h;
  win_dll_basename(narrow, base, sizeof(base));
  int wm = win_dll_classify(base);
  if( wm < 0 ) {
    SET_LAST_ERROR(ERROR_MOD_NOT_FOUND);
    return NULL;
  }
  SET_LAST_ERROR(ERROR_SUCCESS);
  return WIN_MODULE_HANDLE(wm);
}

// Flag bits documented for GetModuleHandleEx{W,A}.  We honor only
// FROM_ADDRESS: PIN/UNCHANGED_REFCOUNT are no-ops because we don't
// refcount module handles anyway.
#define GET_MODULE_HANDLE_EX_FLAG_PIN                 0x1
#define GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT  0x2
#define GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS        0x4

extern "C" EXPORT BOOL kernel32_GetModuleHandleExW(DWORD flags, LPCWSTR name, HANDLE* phModule) {
  if( phModule ) *phModule = NULL;
  if( flags & GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS ) {
    // FROM_ADDRESS: `name` is a code/data pointer inside a module, NOT a
    // string.  Use dladdr to find the containing shared object, then
    // dlopen(..., RTLD_NOLOAD) to get a handle without bumping the
    // refcount.  If the address lies in the main PE image, hand back
    // g_image_base directly.
    if( !name ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }
    Dl_info info;
    if( !dladdr((const void*)name, &info) || !info.dli_fname ) {
      SET_LAST_ERROR(ERROR_MOD_NOT_FOUND);
      return FALSE;
    }
    if( info.dli_fbase == (void*)g_image_base ) {
      if( phModule ) *phModule = (HANDLE)g_image_base;
      return TRUE;
    }
    void* h = dlopen(info.dli_fname, RTLD_NOLOAD|RTLD_LAZY);
    if( !h ) { SET_LAST_ERROR(ERROR_MOD_NOT_FOUND); return FALSE; }
    if( phModule ) *phModule = h;
    return TRUE;
  }
  HANDLE h = kernel32_GetModuleHandleW(name);
  if( phModule )
    *phModule = h;
  return h ? TRUE : FALSE;
}
extern "C" EXPORT BOOL kernel32_GetModuleHandleExA(DWORD flags, LPCSTR name, HANDLE* phModule) {
  // FROM_ADDRESS: `name` is a raw pointer, not a string — don't pass it
  // through utf8_to_wchar.  Cast to LPCWSTR so the W variant's address
  // path receives the original pointer.
  if( flags & GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS )
    return kernel32_GetModuleHandleExW(flags, (LPCWSTR)name, phModule);
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
  char narrow[PATH_MAX], posix[PATH_MAX], base[64];
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
  // dlopen failed.  If the name is a known Windows DLL ("kernel32",
  // "user32", ...), return a sentinel that records which prefix
  // GetProcAddress should use to find the symbol in our shim.  api-ms-win-*
  // and ext-ms-win-* API set forwarders don't exist on Linux: fail the
  // load so the CRT's try_get_function falls through to the real DLL
  // candidate.
  win_dll_basename(narrow, base, sizeof(base));
  int wm = win_dll_classify(base);
  if( wm < 0 ) {
    SET_LAST_ERROR(ERROR_MOD_NOT_FOUND);
    return NULL;
  }
  SET_LAST_ERROR(ERROR_SUCCESS);
  return WIN_MODULE_HANDLE(wm);
}

extern "C" EXPORT BOOL kernel32_FreeLibrary(HANDLE h) {
  if( IS_WIN_MODULE(h)||IS_MAIN_IMAGE(h) )
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
  void* sym = NULL;
  if( IS_WIN_MODULE(h) ) {
    // Stamp the DLL-specific prefix from LoadLibraryExW onto the name and
    // dlsym against our shim's exports.  Each pseudo-handle carries its
    // shim prefix, so `GetProcAddress(kernel32_handle, "FlsAlloc")` looks
    // up "kernel32_FlsAlloc" without trying any other prefix.
    const char* prefix = g_win_module_prefix[WIN_MODULE_IDX(h)];
    char buf[256];
    size_t plen = strlen(prefix);
    size_t nlen = name ? strnlen(name, sizeof(buf)-plen-1) : 0;
    if( name && plen + nlen + 1 <= sizeof(buf) ) {
      memcpy(buf, prefix, plen);
      memcpy(buf + plen, name, nlen + 1);
      sym = dlsym(RTLD_DEFAULT, buf);
    }
  } else {
    void* dlh;
    if( IS_MAIN_IMAGE(h)||h==NULL ) {
      dlh = RTLD_DEFAULT;
    } else {
      int idx = handle_to_idx(h);
      if( idx>=0&&g_handles[idx].kind==H_MODULE )
        dlh = g_handles[idx].dlhandle;
      else
        dlh = RTLD_DEFAULT;
    }
    sym = name ? dlsym(dlh, name) : NULL;
  }
  if( !sym )
    SET_LAST_ERROR(ERROR_PROC_NOT_FOUND);
  return sym;
}
