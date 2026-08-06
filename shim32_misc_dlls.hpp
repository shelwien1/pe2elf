#pragma once
// ole32 / oleaut32 / powrprof — included from shim32.cpp.
//
// rar701a imports a handful of COM and shutdown functions by ordinal from
// oleaut32 and by name from ole32 / powrprof.  None of these are reached
// on the golden "create archive" path, so stub bodies are sufficient — we
// just have to satisfy the dynamic linker.

// ole32 ---------------------------------------------------------------------
extern "C" EXPORT LONG ole32_CoCreateInstance(const void* /*rclsid*/,
                                              void* /*outer*/,
                                              DWORD /*clsctx*/,
                                              const void* /*riid*/,
                                              void** ppv) {
  if( ppv ) *ppv = nullptr;
  return (LONG)0x80004001L;  // E_NOTIMPL
}
extern "C" EXPORT LONG ole32_CoSetProxyBlanket(void* /*proxy*/,
                                               DWORD /*authn_svc*/,
                                               DWORD /*authz_svc*/,
                                               uint16_t* /*princ_name*/,
                                               DWORD /*authn_level*/,
                                               DWORD /*imp_level*/,
                                               void* /*auth_info*/,
                                               DWORD /*capabilities*/) {
  return 0;  // S_OK — callers usually don't check
}

// oleaut32 ------------------------------------------------------------------
// BSTR layout: the pointer points at the start of the wide string; the
// 4 bytes immediately preceding hold the byte length (excluding the
// trailing L'\0').  Allocate one block, write the length prefix, return
// a pointer past it.  SysFreeString backs up to free the original block.
extern "C" EXPORT uint16_t* oleaut32_SysAllocString(const uint16_t* src) {
  if( !src ) return nullptr;
  size_t n = 0;
  while( src[n] ) ++n;
  size_t bytes = n*2;
  uint8_t* blk = (uint8_t*)malloc(4 + bytes + 2);
  if( !blk ) return nullptr;
  *(uint32_t*)blk = (uint32_t)bytes;
  memcpy(blk+4, src, bytes);
  blk[4+bytes] = 0;
  blk[4+bytes+1] = 0;
  return (uint16_t*)(blk+4);
}
extern "C" EXPORT void oleaut32_SysFreeString(uint16_t* s) {
  if( s ) free((uint8_t*)s - 4);
}
// VARIANT is 24 bytes; clearing it to zero is good enough when we never
// store a BSTR / IDispatch in it (the cases where freeing referenced
// resources would matter).
extern "C" EXPORT LONG oleaut32_VariantClear(void* v) {
  if( v ) memset(v, 0, 24);
  return 0;
}

// powrprof ------------------------------------------------------------------
extern "C" EXPORT BOOL powrprof_SetSuspendState(BOOL /*hibernate*/,
                                                BOOL /*force*/,
                                                BOOL /*disable_wake*/) {
  // No-op on Linux.  rar uses this when invoked with -ioff to power down
  // after archiving; we just decline.
  SET_LAST_ERROR(ERROR_CALL_NOT_IMPLEMENTED);
  return FALSE;
}
