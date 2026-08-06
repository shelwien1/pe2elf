#pragma once
// 7.7 Console I/O — included from shim32.cpp.
//
// `GetConsoleMode` derives flags from `tcgetattr`; `WriteConsoleW`
// converts to UTF-8 and forwards to `WriteFile`.
//
// References from shim32.cpp: handle_to_idx, g_handles, H_FILE,
// wchar_to_utf8, kernel32_WriteFile.

extern "C" EXPORT DWORD kernel32_GetConsoleCP(void) {
  return 65001;
}

extern "C" EXPORT DWORD kernel32_GetConsoleOutputCP(void) {
  return 65001;
}

extern "C" EXPORT BOOL kernel32_GetConsoleMode(HANDLE h, DWORD* pMode) {
  log_always("[SHIM] GetConsoleMode(h=%p, caller=%p)\n", h, __builtin_return_address(0));
  if( !pMode ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }
  // Derive fd from handle, fall back to stdin/stdout
  int idx = handle_to_idx(h);
  int fd = (idx>=0 && g_handles[idx].kind==H_FILE) ? g_handles[idx].fd : STDIN_FILENO;
  struct termios ts;
  if( tcgetattr(fd, &ts)!=0 ) {
    // Not a tty — return sensible output defaults
    *pMode = ENABLE_PROCESSED_OUTPUT|ENABLE_WRAP_AT_EOL_OUTPUT;
    return TRUE;
  }
  DWORD mode = 0;
  if( ts.c_lflag&ICANON )  mode |= ENABLE_LINE_INPUT|ENABLE_PROCESSED_INPUT;
  if( ts.c_lflag&ECHO )    mode |= ENABLE_ECHO_INPUT;
  // For output handles always add the processed/wrap flags
  mode |= ENABLE_PROCESSED_OUTPUT|ENABLE_WRAP_AT_EOL_OUTPUT;
  *pMode = mode;
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_SetConsoleMode(HANDLE h, DWORD mode) {
  log_always("[SHIM] SetConsoleMode(h=%p, mode=0x%x, caller=%p)\n", h, mode, __builtin_return_address(0));
  (void)h;
  (void)mode;
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_WriteConsoleA(HANDLE h, LPCVOID buf, DWORD nChars, DWORD* pWritten, void* reserved) {
  (void)reserved;
  return kernel32_WriteFile(h, buf, nChars, pWritten, NULL);
}

extern "C" EXPORT BOOL kernel32_WriteConsoleW(HANDLE h, LPCVOID wbuf, DWORD nChars, DWORD* pWritten, void* reserved) {
  (void)reserved;
  // Build a bounded, NUL-terminated copy so wchar_to_utf8 doesn't over-read
  uint16_t tmp[65536];
  size_t n = (nChars<65535) ? nChars : 65535;
  memcpy(tmp, wbuf, n*2);
  tmp[n] = 0;
  char utf8[65536*4];
  int nbytes = wchar_to_utf8(tmp, utf8, sizeof(utf8)-1);
  DWORD written = 0;
  BOOL r = kernel32_WriteFile(h, utf8, (DWORD)nbytes, &written, NULL);
  if( pWritten ) {
    // Approximate written wide chars from written bytes (UTF-8 bytes >= wide chars)
    *pWritten = written>0 ? nChars : 0;
  }
  return r;
}
