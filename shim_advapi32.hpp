#pragma once
// advapi32 surface — included from shim.cpp.
//
// Token / SID / security-descriptor / registry / crypto routines.  Most
// are tight stubs (return success with empty/zero output) except for
// CryptGenRandom which actually reads /dev/urandom.

// ---------------------------------------------------------------------------
// advapi32 W-variant + neutral
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL advapi32_AdjustTokenPrivileges(HANDLE /*tok*/, BOOL /*da*/,
    void* /*ns*/, DWORD /*bl*/, void* /*ps*/, DWORD* /*rl*/) { return TRUE; }
extern "C" EXPORT BOOL advapi32_AllocateAndInitializeSid(void* /*auth*/, BYTE /*cnt*/,
    DWORD r0, DWORD r1, DWORD r2, DWORD r3, DWORD r4, DWORD r5, DWORD r6, DWORD r7,
    void** sid) {
  (void)r0;(void)r1;(void)r2;(void)r3;(void)r4;(void)r5;(void)r6;(void)r7;
  if(sid){ *sid=calloc(1,64); return *sid!=nullptr; } return FALSE;
}
extern "C" EXPORT BOOL advapi32_CheckTokenMembership(HANDLE /*tok*/, void* /*sid*/, BOOL* member) {
  if(member) *member=FALSE; return TRUE;
}
extern "C" EXPORT void advapi32_FreeSid(void* sid) { free(sid); }
extern "C" EXPORT BOOL advapi32_GetFileSecurityW(const uint16_t* /*path*/, DWORD /*info*/,
    void* sd, DWORD len, DWORD* needed) {
  if(needed)*needed=20; if(!sd||len<20) return FALSE; memset(sd,0,20); return TRUE;
}
extern "C" EXPORT DWORD advapi32_GetSecurityDescriptorLength(void* /*sd*/) { return 20; }
extern "C" EXPORT BOOL advapi32_LookupPrivilegeValueW(const uint16_t* /*sys*/,
    const uint16_t* /*name*/, uint64_t* luid) {
  if(luid)*luid=1; return TRUE;
}
extern "C" EXPORT BOOL advapi32_OpenProcessToken(HANDLE /*proc*/, DWORD /*access*/, HANDLE* tok) {
  if(tok)*tok=(HANDLE)(intptr_t)1; return TRUE;
}
extern "C" EXPORT LONG advapi32_RegCloseKey(HANDLE /*key*/) { return 0; }
extern "C" EXPORT LONG advapi32_RegOpenKeyExW(HANDLE /*key*/, const uint16_t* /*sub*/,
    DWORD /*opt*/, DWORD /*acc*/, HANDLE* res) {
  if(res)*res=INVALID_HANDLE_VALUE; return 2; // ERROR_FILE_NOT_FOUND
}
extern "C" EXPORT LONG advapi32_RegQueryValueExW(HANDLE /*key*/, const uint16_t* /*name*/,
    DWORD* /*res*/, DWORD* type, BYTE* /*data*/, DWORD* size) {
  if(type)*type=1; if(size)*size=0; return 2; // ERROR_FILE_NOT_FOUND
}
extern "C" EXPORT BOOL advapi32_SetFileSecurityW(const uint16_t* /*path*/, DWORD /*info*/, void* /*sd*/) {
  return TRUE;
}
extern "C" EXPORT BOOL advapi32_CryptAcquireContextW(uintptr_t* phProv,
    const uint16_t* /*cont*/, const uint16_t* /*prov*/, DWORD /*type*/, DWORD /*flags*/) {
  if(phProv)*phProv=1; return TRUE;
}
extern "C" EXPORT BOOL advapi32_CryptAcquireContextA(uintptr_t* phProv,
    LPCSTR /*cont*/, LPCSTR /*prov*/, DWORD /*type*/, DWORD /*flags*/) {
  if(phProv)*phProv=1; return TRUE;
}
extern "C" EXPORT BOOL advapi32_CryptGenRandom(uintptr_t /*prov*/, DWORD len, BYTE* buf) {
  if(!buf) return FALSE;
  int fd=open("/dev/urandom",O_RDONLY); if(fd<0) return FALSE;
  ssize_t r=read(fd,buf,len); close(fd); return r==(ssize_t)len;
}
extern "C" EXPORT BOOL advapi32_CryptReleaseContext(uintptr_t /*prov*/, DWORD /*flags*/) { return TRUE; }

// ---------------------------------------------------------------------------
// advapi32 A-variants
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL advapi32_GetFileSecurityA(LPCSTR /*path*/, DWORD /*info*/,
    void* sd, DWORD len, DWORD* needed) {
  const DWORD SD_SIZE = 20;
  if(needed) *needed = SD_SIZE;
  if(!sd || len < SD_SIZE) { SET_LAST_ERROR(122/*ERROR_INSUFFICIENT_BUFFER*/); return FALSE; }
  memset(sd, 0, SD_SIZE);
  *(uint8_t*)sd = 1; // Revision=1
  return TRUE;
}
extern "C" EXPORT BOOL advapi32_SetFileSecurityA(LPCSTR /*path*/, DWORD /*info*/, void* /*sd*/) {
  return TRUE;
}
extern "C" EXPORT BOOL advapi32_LookupPrivilegeValueA(LPCSTR /*sys*/, LPCSTR /*name*/, void* luid) {
  if(luid) *(uint64_t*)luid = 1;
  return TRUE;
}
extern "C" EXPORT LONG advapi32_RegOpenKeyExA(void* /*key*/, LPCSTR /*subkey*/,
    DWORD /*opts*/, DWORD /*access*/, void** result) {
  if(result) *result = nullptr;
  return 2; // ERROR_FILE_NOT_FOUND
}
extern "C" EXPORT LONG advapi32_RegQueryValueExA(void* /*key*/, LPCSTR /*name*/,
    DWORD* /*reserved*/, DWORD* type, void* /*data*/, DWORD* size) {
  if(type) *type = 1; if(size) *size = 0;
  return 2; // ERROR_FILE_NOT_FOUND
}
