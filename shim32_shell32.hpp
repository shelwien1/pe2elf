#pragma once
// shell32 surface — included from shim32.cpp.
//
// Mostly stubs.  The non-trivial bit is `SHGetMalloc`, which returns a
// minimal IMalloc COM vtable so callers can safely Alloc/Realloc/Free
// through it without us implementing the full COM machinery.
//
// References from shim32.cpp: malloc_usable_size (glibc) or its stub.

// ---------------------------------------------------------------------------
// shell32 W-variant + neutral
// ---------------------------------------------------------------------------
extern "C" EXPORT int shell32_SHFileOperationW(void* /*op*/) {
  SET_LAST_ERROR(ERROR_CALL_NOT_IMPLEMENTED); return 1;
}
extern "C" EXPORT BOOL shell32_SHGetPathFromIDListW(void* /*pidl*/, uint16_t* /*path*/) { return FALSE; }

// Minimal IMalloc COM vtable so callers can safely call Free(ptr).
// COM methods are __thiscall on x86: `this` arrives in ECX and the callee
// pops the remaining stack arguments.  Slots are 4 bytes apart, not 8.
static uint32_t THISCALL imalloc_AddRef(void*) { return 1; }
static uint32_t THISCALL imalloc_Release(void*) { return 1; }
static int32_t  THISCALL imalloc_QueryInterface(void*, const void*, void** pp) {
  if(pp) *pp = nullptr; return (int32_t)0x80004002; // E_NOINTERFACE
}
static void* THISCALL imalloc_Alloc(void*, size_t cb) { return malloc(cb); }
static void* THISCALL imalloc_Realloc(void*, void* p, size_t cb) { return realloc(p, cb); }
static void  THISCALL imalloc_Free(void*, void* p) { free(p); }
static size_t THISCALL imalloc_GetSize(void*, void* p) { return p ? malloc_usable_size(p) : (size_t)-1; }
static int   THISCALL imalloc_DidAlloc(void*, void*) { return -1; }
static void  THISCALL imalloc_HeapMinimize(void*) {}

static void* g_imalloc_vtable[] = {
  (void*)imalloc_QueryInterface,  // 0x00
  (void*)imalloc_AddRef,          // 0x04
  (void*)imalloc_Release,         // 0x08
  (void*)imalloc_Alloc,           // 0x0C
  (void*)imalloc_Realloc,         // 0x10
  (void*)imalloc_Free,            // 0x14
  (void*)imalloc_GetSize,         // 0x18
  (void*)imalloc_DidAlloc,        // 0x1C
  (void*)imalloc_HeapMinimize,    // 0x20
};
static void* g_imalloc_instance[] = { g_imalloc_vtable };

extern "C" EXPORT LONG shell32_SHGetMalloc(void** pp) {
  if(pp) *pp = g_imalloc_instance;
  return 0; // S_OK
}
extern "C" EXPORT LONG shell32_SHGetSpecialFolderLocation(void* /*hwnd*/, int /*csidl*/, void** pp) {
  if(pp) *pp = nullptr; return (LONG)0x80004005L; // E_FAIL
}

// ---------------------------------------------------------------------------
// shell32 A-variants
// ---------------------------------------------------------------------------
extern "C" EXPORT int shell32_SHFileOperationA(void* /*op*/) {
  SET_LAST_ERROR(ERROR_CALL_NOT_IMPLEMENTED);
  return 1;
}
extern "C" EXPORT BOOL shell32_SHGetPathFromIDListA(void* /*pidl*/, LPSTR /*path*/) {
  return FALSE;
}
