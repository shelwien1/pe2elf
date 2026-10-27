#pragma once
// Global memory, file attributes, FILETIME→SYSTEMTIME, system info —
// included from shim.cpp after shim_kernel32_sync.hpp.
//
// References from shim.cpp: win_path_to_posix, wchar_to_utf8,
// stat_to_win_attrs, set_errno_error, kernel32_GetFileAttributesA.

// ---------------------------------------------------------------------------
// Global memory / heap
// ---------------------------------------------------------------------------
#define GMEM_ZEROINIT 0x0040u
extern "C" EXPORT void* kernel32_GlobalAlloc(UINT flags, size_t size) {
  return (flags & GMEM_ZEROINIT) ? calloc(1, size) : malloc(size);
}
extern "C" EXPORT void* kernel32_GlobalFree(void* p) { free(p); return nullptr; }

// ---------------------------------------------------------------------------
// File / directory attributes
// ---------------------------------------------------------------------------
#ifndef INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES    0xFFFFFFFFu
#endif
extern "C" EXPORT DWORD kernel32_GetFileAttributesA(LPCSTR path) {
  char posix[PATH_MAX];
  win_path_to_posix(path, posix, sizeof(posix));
  struct stat st;
  if( stat(posix, &st) != 0 ) { set_errno_error(); return INVALID_FILE_ATTRIBUTES; }
  // Use the basename of the posix path for dot-hidden detection.
  const char* base = strrchr(posix, '/');
  base = base ? base+1 : posix;
  return stat_to_win_attrs(&st, base);
}

extern "C" EXPORT DWORD kernel32_GetFileAttributesW(const uint16_t* path) {
  char utf8[PATH_MAX];
  wchar_to_utf8(path, utf8, sizeof(utf8));
  return kernel32_GetFileAttributesA(utf8);
}

extern "C" EXPORT BOOL kernel32_CreateDirectoryA(LPCSTR path, SECURITY_ATTRIBUTES* sa) {
  (void)sa;
  char posix[PATH_MAX];
  win_path_to_posix(path, posix, sizeof(posix));
  if( mkdir(posix, 0777) != 0 ) { set_errno_error(); return FALSE; }
  return TRUE;
}

// ---------------------------------------------------------------------------
// FILETIME → SYSTEMTIME conversion
// SYSTEMTIME: wYear wMonth wDayOfWeek wDay wHour wMinute wSecond wMilliseconds
// ---------------------------------------------------------------------------
#define FILETIME_EPOCH_DIFF 116444736000000000ULL  // 100-ns ticks 1601→1970
extern "C" EXPORT BOOL kernel32_FileTimeToSystemTime(const uint64_t* ft, uint16_t* st) {
  if( !ft || !st ) return FALSE;
  uint64_t t = *ft;
  if( t < FILETIME_EPOCH_DIFF ) return FALSE;
  uint64_t t100 = t - FILETIME_EPOCH_DIFF;
  time_t secs = (time_t)(t100 / 10000000ULL);
  uint32_t ms  = (uint32_t)((t100 / 10000ULL) % 1000ULL);
  struct tm tm_val;
  gmtime_r(&secs, &tm_val);
  st[0] = (uint16_t)(tm_val.tm_year + 1900);
  st[1] = (uint16_t)(tm_val.tm_mon  + 1);
  st[2] = (uint16_t)tm_val.tm_wday;
  st[3] = (uint16_t)tm_val.tm_mday;
  st[4] = (uint16_t)tm_val.tm_hour;
  st[5] = (uint16_t)tm_val.tm_min;
  st[6] = (uint16_t)tm_val.tm_sec;
  st[7] = (uint16_t)ms;
  return TRUE;
}

// ---------------------------------------------------------------------------
// System information
// ---------------------------------------------------------------------------
// SYSTEM_INFO offsets (x64 ABI, sizeof=48):
//  +0  WORD  wProcessorArchitecture   +2  WORD pad
//  +4  DWORD dwPageSize
//  +8  QWORD lpMinimumApplicationAddress
//  +16 QWORD lpMaximumApplicationAddress
//  +24 QWORD dwActiveProcessorMask
//  +32 DWORD dwNumberOfProcessors
//  +36 DWORD dwProcessorType
//  +40 DWORD dwAllocationGranularity
//  +44 WORD  wProcessorLevel   +46 WORD wProcessorRevision
#define PROCESSOR_ARCHITECTURE_AMD64 9u
extern "C" EXPORT void kernel32_GetSystemInfo(uint8_t* info) {
  if( !info ) return;
  memset(info, 0, 48);
  *(uint16_t*)(info+0)  = PROCESSOR_ARCHITECTURE_AMD64;
  *(uint32_t*)(info+4)  = (uint32_t)sysconf(_SC_PAGESIZE);
  *(uint64_t*)(info+8)  = 0x10000ULL;
  *(uint64_t*)(info+16) = 0x7fffffffefff0000ULL;
  int np = get_nprocs();
  *(uint32_t*)(info+32) = (uint32_t)np;
  *(uint64_t*)(info+24) = (np < 64) ? ((1ULL << np) - 1ULL) : ~0ULL;
  *(uint32_t*)(info+36) = 8664u;   // PROCESSOR_AMD_X8664
  *(uint32_t*)(info+40) = 65536u;  // dwAllocationGranularity
}

// MEMORYSTATUS layout (sizeof=32):
//  +0  DWORD dwLength   +4 DWORD dwMemoryLoad
//  +8  SIZE_T dwTotalPhys   +16 SIZE_T dwAvailPhys
//  +24 SIZE_T dwTotalPageFile (set same as total phys)
extern "C" EXPORT void kernel32_GlobalMemoryStatus(uint8_t* buf) {
  if( !buf ) return;
  memset(buf, 0, 32);
  *(uint32_t*)(buf+0) = 32;
  struct sysinfo si;
  if( sysinfo(&si) == 0 ) {
    uint64_t total = (uint64_t)si.totalram  * si.mem_unit;
    uint64_t avail = (uint64_t)si.freeram   * si.mem_unit;
    uint32_t load  = total ? (uint32_t)(100 - avail * 100 / total) : 0;
    *(uint32_t*)(buf+4)  = load;
    *(uint64_t*)(buf+8)  = total;
    *(uint64_t*)(buf+16) = avail;
    *(uint64_t*)(buf+24) = total;
  }
}

// K32GetProcessMemoryInfo (psapi's GetProcessMemoryInfo): this process's
// memory, from /proc/self/status; the process handle is not looked at (only
// GetCurrentProcess's makes sense here). PROCESS_MEMORY_COUNTERS (x64,
// sizeof=72; the _EX form, 80, adds PrivateUsage):
//  +0  DWORD cb                 +4  DWORD PageFaultCount
//  +8  SIZE_T PeakWorkingSetSize    (VmHWM)
//  +16 SIZE_T WorkingSetSize        (VmRSS)
//  +24..+48 SIZE_T quota pool usages (0)
//  +56 SIZE_T PagefileUsage         (RssAnon+VmSwap: private memory in use)
//  +64 SIZE_T PeakPagefileUsage     (no peak of that is kept: the larger of it and VmHWM)
//  +72 SIZE_T PrivateUsage          (as PagefileUsage)
extern "C" EXPORT BOOL kernel32_K32GetProcessMemoryInfo(HANDLE /*proc*/, uint8_t* pmc, DWORD cb) {
  if( !pmc || cb < 72 ) { SET_LAST_ERROR(ERROR_INSUFFICIENT_BUFFER); return FALSE; }
  uint64_t hwm = 0, rss = 0, anon = 0, swap = 0;
  if( FILE* f = fopen("/proc/self/status", "r") ) {
    char line[256];
    while( fgets(line, sizeof(line), f) ) {
      unsigned long long v;
      if( sscanf(line, "VmHWM: %llu", &v) == 1 ) hwm = (uint64_t)v << 10;
      else if( sscanf(line, "VmRSS: %llu", &v) == 1 ) rss = (uint64_t)v << 10;
      else if( sscanf(line, "RssAnon: %llu", &v) == 1 ) anon = (uint64_t)v << 10;
      else if( sscanf(line, "VmSwap: %llu", &v) == 1 ) swap = (uint64_t)v << 10;
    }
    fclose(f);
  }
  struct rusage ru;
  if( getrusage(RUSAGE_SELF, &ru) != 0 ) memset(&ru, 0, sizeof(ru));
  DWORD n = (cb >= 80) ? 80 : 72;
  memset(pmc, 0, n);
  *(uint32_t*)(pmc+0)  = n;
  *(uint32_t*)(pmc+4)  = (uint32_t)(ru.ru_minflt + ru.ru_majflt);
  *(uint64_t*)(pmc+8)  = hwm;
  *(uint64_t*)(pmc+16) = rss;
  *(uint64_t*)(pmc+56) = anon + swap;
  *(uint64_t*)(pmc+64) = (hwm > anon + swap) ? hwm : anon + swap;
  if( n >= 80 ) *(uint64_t*)(pmc+72) = anon + swap;
  return TRUE;
}
extern "C" EXPORT BOOL psapi_GetProcessMemoryInfo(HANDLE proc, uint8_t* pmc, DWORD cb) {
  return kernel32_K32GetProcessMemoryInfo(proc, pmc, cb);
}

// RtlAddFunctionTable — stub (no JIT SEH unwind needed)
extern "C" EXPORT BOOL kernel32_RtlAddFunctionTable(void* /*table*/, DWORD /*count*/, uint64_t /*base*/) {
  return TRUE;
}
