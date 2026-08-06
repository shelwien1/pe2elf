#pragma once
// SetFilePointer (non-Ex), SetFileTime, SetEndOfFile, FILETIME ↔ FAT
// DOS date/time conversion — included from shim32.cpp.
//
// References from shim32.cpp: get_fd, set_errno_error, ft_to_u64,
// u64_to_ft, FILETIME_EPOCH.

extern "C" EXPORT DWORD kernel32_SetFilePointer(HANDLE h, LONG dist, LONG* disthi, DWORD method) {
  int fd = get_fd(h);
  if( fd<0 )
    return (DWORD)-1;
  int64_t offset = dist;
  if( disthi )
    offset |= ((int64_t)*disthi<<32);
  int whence = (method==FILE_BEGIN) ? SEEK_SET : (method==FILE_CURRENT) ? SEEK_CUR : SEEK_END;
  off_t r = lseek(fd, (off_t)offset, whence);
  if( r<0 ) {
    set_errno_error();
    return (DWORD)-1;
  }
  if( disthi )
    *disthi = (LONG)(r>>32);
  return (DWORD)(r&0xFFFFFFFF);
}

extern "C" EXPORT BOOL kernel32_SetEndOfFile(HANDLE h) {
  int fd = get_fd(h);
  if( fd<0 )
    return FALSE;
  off_t pos = lseek(fd, 0, SEEK_CUR);
  if( pos<0 ) {
    set_errno_error();
    return FALSE;
  }
  if( ftruncate(fd, pos)<0 ) {
    set_errno_error();
    return FALSE;
  }
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_SetFileTime(HANDLE h, const FILETIME* ctime, const FILETIME* atime, const FILETIME* mtime) {
  int fd = get_fd(h);
  if( fd<0 )
    return FALSE;
  struct timespec times[2] = {};
  auto ft_to_ts = [](const FILETIME* ft, struct timespec &ts) {
                    if( !ft ) {
                      ts.tv_nsec = UTIME_OMIT;
                      return;
                    }
                    uint64_t v = ft_to_u64(*ft);
                    if( v<FILETIME_EPOCH ) {
                      ts.tv_sec = 0;
                      ts.tv_nsec = 0;
                      return;
                    }
                    v -= FILETIME_EPOCH;
                    ts.tv_sec = (time_t)(v/10000000ULL);
                    ts.tv_nsec = (long)((v%10000000ULL)*100);
                  };
  ft_to_ts(atime, times[0]);
  ft_to_ts(mtime, times[1]);
  futimens(fd, times);
  (void)ctime;
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_FileTimeToDosDateTime(const FILETIME* ft, WORD* fatdate, WORD* fattime) {
  if( !ft||!fatdate||!fattime )
    return FALSE;
  uint64_t v = ft_to_u64(*ft);
  if( v<FILETIME_EPOCH ) {
    *fatdate = *fattime = 0;
    return FALSE;
  }
  v -= FILETIME_EPOCH;
  time_t t = (time_t)(v/10000000ULL);
  struct tm tm;
  gmtime_r(&t, &tm);
  // DOS epoch starts 1980; clamp pre-1980 dates to avoid WORD wrap
  if( tm.tm_year<80 ) {
    *fatdate = *fattime = 0;
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  *fatdate = (WORD)(((tm.tm_year-80)<<9)|((tm.tm_mon+1)<<5)|tm.tm_mday);
  *fattime = (WORD)((tm.tm_hour<<11)|(tm.tm_min<<5)|(tm.tm_sec>>1));
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_DosDateTimeToFileTime(WORD fatdate, WORD fattime, FILETIME* ft) {
  if( !ft )
    return FALSE;
  struct tm tm = {};
  tm.tm_year = ((fatdate>>9)&0x7f)+80;
  tm.tm_mon = ((fatdate>>5)&0x0f)-1;
  tm.tm_mday = fatdate&0x1f;
  tm.tm_hour = (fattime>>11)&0x1f;
  tm.tm_min = (fattime>>5)&0x3f;
  tm.tm_sec = (fattime&0x1f)<<1;
  time_t t = timegm(&tm);
  uint64_t v = (uint64_t)t*10000000ULL+FILETIME_EPOCH;
  *ft = u64_to_ft(v);
  return TRUE;
}
