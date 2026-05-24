#pragma once
// Console misc — ReadConsoleW, ReadConsoleInput{A,W}, SetHandleCount.
//
// References from shim.cpp: handle_to_idx, g_handles, H_FILE.

// INPUT_RECORD layout (Windows x64 ABI, sizeof=20):
//  +0  WORD  EventType        (1 = KEY_EVENT)
//  +2  WORD  padding
//  +4  DWORD bKeyDown
//  +8  WORD  wRepeatCount
//  +10 WORD  wVirtualKeyCode
//  +12 WORD  wVirtualScanCode
//  +14 WORD  uChar (AsciiChar in low byte)
//  +16 DWORD dwControlKeyState
#define INPUT_RECORD_SIZE 20

extern "C" EXPORT BOOL kernel32_ReadConsoleW(HANDLE h, uint16_t* buf, DWORD nchars, DWORD* nread, void* /*ctrl*/) {
  if( !buf || nchars==0 ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }
  int idx = handle_to_idx(h);
  int fd = (idx>=0 && g_handles[idx].kind==H_FILE) ? g_handles[idx].fd : STDIN_FILENO;
  // Read up to nchars bytes of UTF-8 then widen one char at a time.
  char tmp[4096];
  DWORD cap = nchars < (DWORD)sizeof(tmp) ? nchars : (DWORD)(sizeof(tmp)-1);
  ssize_t n;
  do { n = read(fd, tmp, cap); } while( n<0 && errno==EINTR );
  if( n<=0 ) { if(nread) *nread=0; return n==0 ? TRUE : FALSE; }
  tmp[n] = '\0';
  DWORD out = 0;
  for( ssize_t i=0; i<n && out<nchars; i++, out++ )
    buf[out] = (uint16_t)(uint8_t)tmp[i];
  if( nread ) *nread = out;
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_ReadConsoleInputA(HANDLE h, void* buf, DWORD count, DWORD* nread) {
  if( nread ) *nread = 0;
  if( !buf||count==0 ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }
  int idx = handle_to_idx(h);
  int fd = (idx>=0 && g_handles[idx].kind==H_FILE) ? g_handles[idx].fd : STDIN_FILENO;
  char ch;
  ssize_t n;
  do {
    n = read(fd, &ch, 1);
  } while( n<0&&errno==EINTR );
  if( n<=0 ) return FALSE;
  uint8_t* rec = (uint8_t*)buf;
  memset(rec, 0, INPUT_RECORD_SIZE);
  *(uint16_t*)(rec+0)  = 0x0001;              // KEY_EVENT
  *(uint32_t*)(rec+4)  = 1;                   // bKeyDown = TRUE
  *(uint16_t*)(rec+8)  = 1;                   // wRepeatCount
  *(uint16_t*)(rec+14) = (uint16_t)(uint8_t)ch; // AsciiChar
  if( nread ) *nread = 1;
  return TRUE;
}
extern "C" EXPORT BOOL kernel32_ReadConsoleInputW(HANDLE h, void* buf, DWORD count, DWORD* nread) {
  // Same as A; UnicodeChar overlaps AsciiChar at offset 14 in INPUT_RECORD
  return kernel32_ReadConsoleInputA(h, buf, count, nread);
}

extern "C" EXPORT BOOL kernel32_SetHandleCount(DWORD n) {
  (void)n;
  return TRUE;
}
