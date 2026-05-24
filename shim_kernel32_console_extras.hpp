#pragma once
// Console extras — GetConsoleTitle / SetConsoleTitle / screen buffer info
// stubs, and OutputDebugStringA/W (forward to log_always).
//
// References from shim.cpp: wchar_to_utf8, log_always.

extern "C" EXPORT BOOL kernel32_GetConsoleTitleA(LPSTR buf, DWORD sz) {
  if( buf && sz ) buf[0] = '\0';
  return TRUE;
}
extern "C" EXPORT DWORD kernel32_GetConsoleTitleW(uint16_t* buf, DWORD sz) {
  if( buf && sz ) buf[0] = 0;
  return 0;
}
extern "C" EXPORT BOOL kernel32_SetConsoleTitleA(LPCSTR /*title*/) { return TRUE; }
extern "C" EXPORT BOOL kernel32_SetConsoleTitleW(const uint16_t* /*title*/) { return TRUE; }

// CONSOLE_SCREEN_BUFFER_INFO layout (22 bytes):
//  COORD dwSize(4), COORD dwCursorPosition(4), WORD wAttributes(2),
//  SMALL_RECT srWindow(8), COORD dwMaximumWindowSize(4)
extern "C" EXPORT BOOL kernel32_GetConsoleScreenBufferInfo(HANDLE /*h*/, void* buf) {
  if( !buf ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }
  uint8_t* b = (uint8_t*)buf;
  memset(b, 0, 22);
  *(uint16_t*)(b+0)  = 80;   // dwSize.X
  *(uint16_t*)(b+2)  = 25;   // dwSize.Y
  *(uint16_t*)(b+8)  = 0x07; // wAttributes (grey on black)
  *(uint16_t*)(b+10) = 0;    // srWindow.Left
  *(uint16_t*)(b+12) = 0;    // srWindow.Top
  *(uint16_t*)(b+14) = 79;   // srWindow.Right
  *(uint16_t*)(b+16) = 24;   // srWindow.Bottom
  *(uint16_t*)(b+18) = 80;   // dwMaximumWindowSize.X
  *(uint16_t*)(b+20) = 25;   // dwMaximumWindowSize.Y
  return TRUE;
}

extern "C" EXPORT void kernel32_OutputDebugStringA(LPCSTR s) {
  if( s ) log_always("[DBG] %s\n", s);
}
extern "C" EXPORT void kernel32_OutputDebugStringW(const uint16_t* s) {
  if( s ) { char buf[1024]; wchar_to_utf8(s, buf, sizeof(buf)); log_always("[DBG] %s\n", buf); }
}
