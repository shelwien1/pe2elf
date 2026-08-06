#pragma once
// Global memory, file attributes, FILETIME→SYSTEMTIME, system info —
// included from shim32.cpp after shim32_kernel32_sync.hpp.
//
// References from shim32.cpp: win_path_to_posix, wchar_to_utf8,
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
// SYSTEM_INFO offsets (Win32 ABI, sizeof=36):
//  +0  WORD  wProcessorArchitecture   +2  WORD wReserved
//  +4  DWORD dwPageSize
//  +8  DWORD lpMinimumApplicationAddress
//  +12 DWORD lpMaximumApplicationAddress
//  +16 DWORD dwActiveProcessorMask     (ULONG_PTR — 32-bit here)
//  +20 DWORD dwNumberOfProcessors
//  +24 DWORD dwProcessorType
//  +28 DWORD dwAllocationGranularity
//  +32 WORD  wProcessorLevel   +34 WORD wProcessorRevision
#define PROCESSOR_ARCHITECTURE_INTEL 0u
#define PROCESSOR_INTEL_PENTIUM      586u
extern "C" EXPORT void kernel32_GetSystemInfo(uint8_t* info) {
  if( !info ) return;
  memset(info, 0, 36);
  *(uint16_t*)(info+0)  = PROCESSOR_ARCHITECTURE_INTEL;
  *(uint32_t*)(info+4)  = (uint32_t)sysconf(_SC_PAGESIZE);
  *(uint32_t*)(info+8)  = 0x00010000u;   // lpMinimumApplicationAddress
  *(uint32_t*)(info+12) = 0x7FFEFFFFu;   // lpMaximumApplicationAddress (2 GB user VA)
  int np = get_nprocs();
  // dwActiveProcessorMask is ULONG_PTR, so at most 32 bits of mask on i386.
  *(uint32_t*)(info+16) = (np < 32) ? ((1u << np) - 1u) : ~0u;
  *(uint32_t*)(info+20) = (uint32_t)np;
  *(uint32_t*)(info+24) = PROCESSOR_INTEL_PENTIUM;
  *(uint32_t*)(info+28) = 65536u;        // dwAllocationGranularity
  *(uint16_t*)(info+32) = 6;             // wProcessorLevel
}

// MEMORYSTATUS layout, Win32 (SIZE_T is 4 bytes, sizeof=32):
//  +0  DWORD  dwLength      +4  DWORD  dwMemoryLoad
//  +8  SIZE_T dwTotalPhys   +12 SIZE_T dwAvailPhys
//  +16 SIZE_T dwTotalPageFile  +20 SIZE_T dwAvailPageFile
//  +24 SIZE_T dwTotalVirtual   +28 SIZE_T dwAvailVirtual
// Values are saturated to 4 GB - 1: a 32-bit field cannot report more, and
// Windows itself clamps here (that is why GlobalMemoryStatusEx exists).
extern "C" EXPORT void kernel32_GlobalMemoryStatus(uint8_t* buf) {
  if( !buf ) return;
  memset(buf, 0, 32);
  *(uint32_t*)(buf+0) = 32;
  auto clamp32 = [](uint64_t v) -> uint32_t {
    return v > 0xFFFFFFFFULL ? 0xFFFFFFFFu : (uint32_t)v;
  };
  struct sysinfo si;
  if( sysinfo(&si) == 0 ) {
    uint64_t total = (uint64_t)si.totalram  * si.mem_unit;
    uint64_t avail = (uint64_t)si.freeram   * si.mem_unit;
    uint32_t load  = total ? (uint32_t)(100 - avail * 100 / total) : 0;
    *(uint32_t*)(buf+4)  = load;
    *(uint32_t*)(buf+8)  = clamp32(total);
    *(uint32_t*)(buf+12) = clamp32(avail);
    *(uint32_t*)(buf+16) = clamp32(total);
    *(uint32_t*)(buf+20) = clamp32(avail);
    *(uint32_t*)(buf+24) = 0x7FFE0000u;   // 2 GB user VA
    *(uint32_t*)(buf+28) = clamp32(avail);
  }
}

// (RtlAddFunctionTable is x64-only — i386 has no dynamic function-table
// registration, because x86 SEH is chain-based rather than table-based.)
