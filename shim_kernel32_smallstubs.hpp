#pragma once
// Small kernel32 sections kept together because they're each <20 lines —
// 7.2 Error State, 7.10 Time / Performance, 7.14 Pointer Encoding.
// Included from shim.cpp.
//
// References from shim.cpp: tls_last_error, SET_LAST_ERROR macro.

// ---------------------------------------------------------------------------
// 7.2 Error State
// ---------------------------------------------------------------------------
extern "C" EXPORT DWORD kernel32_GetLastError(void) {
  log_always("[SHIM] GetLastError() -> %u (caller=%p)\n", tls_last_error, __builtin_return_address(0));
  return tls_last_error;
}

extern "C" EXPORT void kernel32_SetLastError(DWORD e) {
  SET_LAST_ERROR(e);
}

// ---------------------------------------------------------------------------
// 7.10 Time / Performance
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL kernel32_QueryPerformanceCounter(LARGE_INTEGER* pli) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  pli->QuadPart = (LONGLONG)ts.tv_sec*1000000000LL+ts.tv_nsec;
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_QueryPerformanceFrequency(LARGE_INTEGER* pli) {
  pli->QuadPart = 1000000000LL;
  return TRUE;
}

extern "C" EXPORT DWORD kernel32_GetTickCount(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (DWORD)(ts.tv_sec*1000+ts.tv_nsec/1000000);
}

// ---------------------------------------------------------------------------
// 7.14 Pointer Encoding
// ---------------------------------------------------------------------------
extern "C" EXPORT LPVOID kernel32_EncodePointer(LPVOID p) {
  return p;
}

extern "C" EXPORT LPVOID kernel32_DecodePointer(LPVOID p) {
  return p;
}
