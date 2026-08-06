#pragma once
// 7.3 Memory — included from shim32.cpp.
//
// VirtualAlloc/VirtualFree are mmap-backed with a tracker (so VirtualFree
// can find the original size); Heap* delegate to libc malloc/realloc/free.
//
// References from shim32.cpp: mmap_track_add, mmap_track_remove,
// malloc_usable_size (glibc) / its stub.

static int prot_from_protect(DWORD protect) {
  switch( protect&0xFF ) {
  case PAGE_NOACCESS:
    return PROT_NONE;
  case PAGE_READONLY:
    return PROT_READ;
  case PAGE_READWRITE:
    return PROT_READ|PROT_WRITE;
  case PAGE_EXECUTE:
    return PROT_EXEC;
  case PAGE_EXECUTE_READ:
    return PROT_EXEC|PROT_READ;
  case PAGE_EXECUTE_READWRITE:
    return PROT_EXEC|PROT_READ|PROT_WRITE;
  default:
    log_always("[SHIM] prot_from_protect: unknown protect=0x%x, defaulting to RW\n", protect);
    return PROT_READ|PROT_WRITE;
  }
}

extern "C" EXPORT LPVOID kernel32_VirtualAlloc(LPVOID addr, size_t size, DWORD type, DWORD protect) {
  (void)type;
  int prot = prot_from_protect(protect);
  int flags = MAP_PRIVATE|MAP_ANONYMOUS;
  if( addr ) {
#ifdef MAP_FIXED_NOREPLACE
    flags |= MAP_FIXED_NOREPLACE;
    void* p = mmap(addr, size, prot, flags, -1, 0);
    if( p==MAP_FAILED ) {
      flags = (flags&~MAP_FIXED_NOREPLACE)|MAP_FIXED;
      p = mmap(addr, size, prot, flags, -1, 0);
      // Two distinct failures: mmap itself failed (MAP_FAILED — must not
      // munmap that), or it succeeded at a different address than asked
      // (MAP_FIXED makes that impossible in practice, but guard anyway).
      if( p==MAP_FAILED ) { SET_LAST_ERROR(ERROR_OUTOFMEMORY); return NULL; }
      if( p!=addr ) { munmap(p, size); SET_LAST_ERROR(ERROR_OUTOFMEMORY); return NULL; }
    }
    if( !mmap_track_add(p, size) ) { munmap(p, size); SET_LAST_ERROR(ERROR_OUTOFMEMORY); return NULL; }
    return p;
#else
    flags |= MAP_FIXED;
#endif
  }
  void* p = mmap(addr, size, prot, flags, -1, 0);
  if( p==MAP_FAILED ) {
    SET_LAST_ERROR(ERROR_OUTOFMEMORY);
    return NULL;
  }
  if( !mmap_track_add(p, size) ) { munmap(p, size); SET_LAST_ERROR(ERROR_OUTOFMEMORY); return NULL; }
  return p;
}

extern "C" EXPORT BOOL kernel32_VirtualFree(LPVOID addr, size_t size, DWORD type) {
  if( type&MEM_RELEASE ) {
    if( size!=0 ) {
      SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
      return FALSE;
    }
    size_t tracked = mmap_track_remove(addr);
    if( tracked )
      munmap(addr, tracked);
  } else if( type&MEM_DECOMMIT ) {
    mprotect(addr, size, PROT_NONE);
    madvise(addr, size, MADV_DONTNEED);
  }
  return TRUE;
}

extern "C" EXPORT HANDLE kernel32_HeapCreate(DWORD flags, size_t init, size_t maxsz) {
  (void)flags;
  (void)init;
  (void)maxsz;
  return HEAP_PSEUDO_HANDLE;
}

extern "C" EXPORT HANDLE kernel32_GetProcessHeap(void) {
  return HEAP_PSEUDO_HANDLE;
}

extern "C" EXPORT LPVOID kernel32_HeapAlloc(HANDLE heap, DWORD flags, size_t size) {
  (void)heap;
  void* p = (flags&HEAP_ZERO_MEMORY) ? calloc(1, size) : malloc(size);
  if( !p )
    SET_LAST_ERROR(ERROR_OUTOFMEMORY);
  return p;
}

extern "C" EXPORT BOOL kernel32_HeapFree(HANDLE heap, DWORD flags, LPVOID ptr) {
  (void)heap;
  (void)flags;
  if( (uintptr_t)ptr<0x10000&&ptr!=NULL ) {
    log_always("[SHIM] HeapFree: invalid ptr=%p (caller=%p) — ignoring\n", ptr, __builtin_return_address(0));
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  free(ptr);
  return TRUE;
}

extern "C" EXPORT LPVOID kernel32_HeapReAlloc(HANDLE heap, DWORD flags, LPVOID ptr, size_t size) {
  (void)heap;
  // realloc(ptr, 0) is implementation-defined; clamp to 1 to always get a
  // valid pointer (matches Windows HeapReAlloc(size=0) behavior on glibc)
  size_t alloc_size = size ? size : 1;
  if( flags&HEAP_ZERO_MEMORY ) {
    size_t old_sz = ptr ? malloc_usable_size(ptr) : 0;
    void* p = realloc(ptr, alloc_size);
    // Zero only when we have a reliable old_sz (glibc) or there was no
    // previous allocation (ptr==NULL → fresh block, old_sz is correctly 0).
    // On musl malloc_usable_size stubs to 0; zeroing with old_sz==0 and
    // ptr!=NULL would destroy the existing data, so we skip it.
    if( p&&size>old_sz&&(old_sz>0||!ptr) )
      memset((char*)p+old_sz, 0, size-old_sz);
    if( !p ) SET_LAST_ERROR(ERROR_OUTOFMEMORY);
    return p;
  }
  void* p = realloc(ptr, alloc_size);
  if( !p ) SET_LAST_ERROR(ERROR_OUTOFMEMORY);
  return p;
}

extern "C" EXPORT size_t kernel32_HeapSize(HANDLE heap, DWORD flags, LPCVOID ptr) {
  (void)heap;
  (void)flags;
  return malloc_usable_size((void*)ptr);
}

extern "C" EXPORT BOOL kernel32_HeapSetInformation(HANDLE heap, DWORD cls, LPVOID info, size_t sz) {
  (void)heap;
  (void)cls;
  (void)info;
  (void)sz;
  return TRUE;
}
