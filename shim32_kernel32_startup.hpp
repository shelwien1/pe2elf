#pragma once
// 7.9 Startup / Command Line / Environment — included from shim32.cpp.
//
// References from shim32.cpp: g_cmdline, g_cmdline_w, g_env_block,
// g_env_block_w, build_env_block, idx_to_handle, wchar_to_utf8.

extern "C" EXPORT LPSTR kernel32_GetCommandLineA(void) {
  return g_cmdline;
}

extern "C" EXPORT LPWSTR kernel32_GetCommandLineW(void) {
  return (LPWSTR)g_cmdline_w;
}

extern "C" EXPORT void kernel32_GetStartupInfoW(STARTUPINFOW* psi) {
  if( !psi )
    return;
  memset(psi, 0, sizeof(*psi));
  psi->cb = sizeof(STARTUPINFOW);
  psi->hStdInput = idx_to_handle(0);
  psi->hStdOutput = idx_to_handle(1);
  psi->hStdError = idx_to_handle(2);
  psi->dwFlags = STARTF_USESTDHANDLES;
}

extern "C" EXPORT void kernel32_GetStartupInfoA(STARTUPINFOA* psi) {
  if( !psi )
    return;
  memset(psi, 0, sizeof(*psi));
  psi->cb = sizeof(STARTUPINFOA);
  psi->hStdInput = idx_to_handle(0);
  psi->hStdOutput = idx_to_handle(1);
  psi->hStdError = idx_to_handle(2);
  psi->dwFlags = STARTF_USESTDHANDLES;
}

extern "C" EXPORT LPSTR kernel32_GetEnvironmentStrings(void) {
  if( !g_env_block )
    build_env_block();
  return g_env_block;
}

extern "C" EXPORT LPWSTR kernel32_GetEnvironmentStringsW(void) {
  // Regenerate on demand if dirty (B23/R34)
  if( !g_env_block_w )
    build_env_block();
  return g_env_block_w;
}
extern "C" EXPORT LPSTR kernel32_GetEnvironmentStringsA(void) {
  return kernel32_GetEnvironmentStrings();
}

extern "C" EXPORT BOOL kernel32_FreeEnvironmentStringsA(LPSTR p) {
  if( p!=g_env_block )
    free(p);
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_FreeEnvironmentStringsW(LPWSTR p) {
  if( p!=(LPWSTR)g_env_block_w )
    free(p);
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_SetEnvironmentVariableW(LPCWSTR name, LPCWSTR val) {
  char n[512], v[4096];
  wchar_to_utf8(name, n, sizeof(n));
  if( val ) {
    wchar_to_utf8(val, v, sizeof(v));
    setenv(n, v, 1);
  } else {
    unsetenv(n);
  }
  // Invalidate cached wide env block so next GetEnvironmentStringsW regenerates (B23/R34)
  free(g_env_block_w);
  g_env_block_w = NULL;
  free(g_env_block);
  g_env_block = NULL;
  return TRUE;
}
