#pragma once
// 7.11 Synchronization (+ 7.12 SListHead placeholder) — included from
// shim.cpp.  Distinct from shim_kernel32_sync.hpp, which owns the
// CreateMutex/Event/Semaphore/Thread + Wait* surface; this one is for the
// in-process primitives: CRITICAL_SECTION (recursive pthread_mutex), the
// TlsAlloc/Free/Get/Set array (per-thread slots at GS:[0x58], shared
// with the FLS layer), and the InitializeSListHead stub.
//
// References from shim.cpp: g_tls_alloc_mu, g_tls_alloc_used, tls_get_slots.

extern "C" EXPORT BOOL kernel32_InitializeCriticalSectionAndSpinCount(CRITICAL_SECTION* cs, DWORD spin) {
  (void)spin;
  pthread_mutexattr_t a;
  pthread_mutexattr_init(&a);
  pthread_mutexattr_settype(&a, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init((pthread_mutex_t*)cs, &a);
  pthread_mutexattr_destroy(&a);
  return TRUE;
}

extern "C" EXPORT void kernel32_InitializeCriticalSection(CRITICAL_SECTION* cs) {
  kernel32_InitializeCriticalSectionAndSpinCount(cs, 0);
}

extern "C" EXPORT BOOL kernel32_InitializeCriticalSectionEx(CRITICAL_SECTION* cs, DWORD spin, DWORD /*flags*/) {
  return kernel32_InitializeCriticalSectionAndSpinCount(cs, spin);
}

extern "C" EXPORT void kernel32_EnterCriticalSection(CRITICAL_SECTION* cs) {
  log_always("[SHIM] EnterCriticalSection(%p, caller=%p)\n", cs, __builtin_return_address(0));
  pthread_mutex_lock((pthread_mutex_t*)cs);
  log_always("[SHIM] EnterCriticalSection(%p) done\n", cs);
}

extern "C" EXPORT void kernel32_LeaveCriticalSection(CRITICAL_SECTION* cs) {
  log_always("[SHIM] LeaveCriticalSection(%p)\n", cs);
  pthread_mutex_unlock((pthread_mutex_t*)cs);
}

extern "C" EXPORT void kernel32_DeleteCriticalSection(CRITICAL_SECTION* cs) {
  pthread_mutex_destroy((pthread_mutex_t*)cs);
}

// TLS / FLS
// TLS implemented via the per-thread tls_slots array stored at GS:[0x58]
// (same layout as Windows uses), bypassing pthread_setspecific entirely.
// g_tls_alloc_mu, g_tls_alloc_used, tls_get_slots are declared earlier.

extern "C" EXPORT DWORD kernel32_TlsAlloc(void) {
  pthread_mutex_lock(&g_tls_alloc_mu);
  DWORD idx = 0xFFFFFFFF;
  for( DWORD i = 0; i < 64; i++ ) {
    if( !(g_tls_alloc_used & (1ULL<<i)) ) {
      g_tls_alloc_used |= (1ULL<<i);
      idx = i;
      break;
    }
  }
  pthread_mutex_unlock(&g_tls_alloc_mu);
  log_always("[SHIM] TlsAlloc() -> idx=%u\n", (unsigned)idx);
  return idx;
}

extern "C" EXPORT BOOL kernel32_TlsFree(DWORD idx) {
  if( idx >= 64 ) return FALSE;
  // Zero the calling thread's slot so a subsequent TlsAlloc on the same
  // index doesn't expose stale data to the new owner.  Full per-thread
  // zeroing (Windows guarantee) would require iterating all threads; this
  // handles the most common single-threaded free path.
  void** slots = tls_get_slots();
  if( slots ) slots[idx] = NULL;
  pthread_mutex_lock(&g_tls_alloc_mu);
  g_tls_alloc_used &= ~(1ULL<<idx);
  pthread_mutex_unlock(&g_tls_alloc_mu);
  return TRUE;
}

extern "C" EXPORT LPVOID kernel32_TlsGetValue(DWORD idx) {
  SET_LAST_ERROR(0);
  if( idx >= 64 ) return NULL;
  // Return NULL (with no error) for a freed index, matching Windows behaviour.
  pthread_mutex_lock(&g_tls_alloc_mu);
  bool allocated = (g_tls_alloc_used >> idx) & 1;
  pthread_mutex_unlock(&g_tls_alloc_mu);
  if( !allocated ) {
    log_always("[SHIM] TlsGetValue(idx=%u, tid=%lu) -> NULL (not-allocated) [caller=%p]\n",
               idx, (unsigned long)pthread_self(), __builtin_return_address(0));
    return NULL;
  }
  void** slots = tls_get_slots();
  void* v = slots ? slots[idx] : NULL;
  log_always("[SHIM] TlsGetValue(idx=%u, tid=%lu) -> %p [caller=%p]\n",
             idx, (unsigned long)pthread_self(), v, __builtin_return_address(0));
  return v;
}

extern "C" EXPORT BOOL kernel32_TlsSetValue(DWORD idx, LPVOID val) {
  if( idx >= 64 ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }
  void** slots = tls_get_slots();
  if( !slots ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }
  slots[idx] = val;
  log_always("[SHIM] TlsSetValue(idx=%u, tid=%lu, val=%p)\n", idx, (unsigned long)pthread_self(), val);
  return TRUE;
}

extern "C" EXPORT void kernel32_InitializeSListHead(void* h) {
  if( h )
    memset(h, 0, 16); // SLIST_HEADER is 16 bytes
}
