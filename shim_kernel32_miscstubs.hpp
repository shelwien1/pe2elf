#pragma once
// Misc stubs (`GetStringTypeA`, `LCMapStringA`, `Sleep`) — included from shim.cpp.
//
// References from shim.cpp: classify_ctype1.

extern "C" EXPORT DWORD kernel32_GetStringTypeA(DWORD locale, DWORD type, LPCSTR src, int count, WORD* types) {
  (void)locale;
  if( !src||!types||count==0 ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  if( count<0 )
    count = (int)strlen(src);
  for( int i = 0; i<count; ++i )
    types[i] = (type==CT_CTYPE1) ? classify_ctype1((unsigned char)src[i]) : 0;
  return TRUE;
}

extern "C" EXPORT int kernel32_LCMapStringA(DWORD locale, DWORD flags, LPCSTR src, int srclen, LPSTR dst, int dstlen) {
  (void)locale;
  if( srclen<0 )
    srclen = (int)strlen(src)+1;
  if( flags&LCMAP_UPPERCASE ) { // uppercase
    if( dst&&dstlen>0 ) {
      int n = srclen<dstlen ? srclen : dstlen;
      for( int i = 0; i<n; ++i )
        dst[i] = (src[i]>='a'&&src[i]<='z') ? src[i]-32 : src[i];
    }
  } else if( dst&&dstlen>0 ) {
    int n = srclen<dstlen ? srclen : dstlen;
    memcpy(dst, src, (size_t)n);
  }
  return srclen;
}

// Not in 1.exe but common; add to avoid link errors if needed
extern "C" EXPORT void kernel32_Sleep(DWORD ms) {
  struct timespec deadline;
  clock_gettime(CLOCK_MONOTONIC, &deadline);
  deadline.tv_sec  += (time_t)(ms/1000);
  deadline.tv_nsec += (long)((ms%1000)*1000000L);
  if( deadline.tv_nsec>=1000000000L ) {
    deadline.tv_sec++;
    deadline.tv_nsec -= 1000000000L;
  }
  // Use absolute-time sleep so EINTR restarts don't overshoot
  while( clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL)==EINTR )
    ;
}
