#pragma once
// FLS (Fiber Local Storage) — included from shim.cpp.
//
// Shares the slot namespace and per-thread tls_slots storage with TLS:
// on Windows, TlsAlloc and FlsAlloc draw from the same pool and the same
// per-thread array.  Only FLS adds per-slot destruction callbacks.
//
// `shim_thread_exit` is the single pthread_key destructor for the slots
// array; forward-declared in shim.cpp and registered as g_tls_slots_key's
// destructor up there, but defined here so it can see g_fls_callbacks.
//
// References from shim.cpp: g_tls_alloc_mu, g_tls_alloc_used,
// g_tls_static_idx, tls_get_slots.

#define FLS_MAX_SLOTS 64
// g_tls_alloc_mu and g_tls_alloc_used are shared with TLS (declared in shim.cpp).
static pthread_mutex_t g_fls_mu = PTHREAD_MUTEX_INITIALIZER;  // protects g_fls_callbacks
static void* g_fls_callbacks[FLS_MAX_SLOTS] = {};

typedef void (__attribute__((ms_abi)) *fls_callback_t)(void*);

// Single pthread_key_create destructor for the per-thread slots array
// (registered as g_tls_slots_key's destructor up at the top of shim.cpp).
// Runs FLS callbacks while the slots block is still valid, then frees the
// static-TLS block and the slots array itself.  Uses the explicit slots
// pointer passed in by pthread rather than re-reading GS:[0x58], so it
// works even when the thread's TLS is being torn down.
static void shim_thread_exit(void* p) {
  void** slots = (void**)p;
  if( !slots ) return;
  for( DWORD i = 0; i < FLS_MAX_SLOTS; ++i ) {
    void* val = slots[i];
    if( !val ) continue;
    pthread_mutex_lock(&g_fls_mu);
    void* cb = g_fls_callbacks[i];
    pthread_mutex_unlock(&g_fls_mu);
    if( cb ) {
      slots[i] = NULL;  // zero before callback to prevent re-entry
      ((fls_callback_t)cb)(val);
    }
  }
  if( g_tls_static_idx != 0xFFFFFFFFu )
    free(slots[g_tls_static_idx]);
  free(slots);
}

extern "C" EXPORT DWORD kernel32_FlsAlloc(void* callback) {
  // Allocate from the same bitset as TlsAlloc so indices are shared.
  pthread_mutex_lock(&g_tls_alloc_mu);
  DWORD idx = 0xFFFFFFFF;
  for( DWORD i = 0; i < FLS_MAX_SLOTS; ++i ) {
    if( !(g_tls_alloc_used & (1ULL<<i)) ) {
      g_tls_alloc_used |= (1ULL<<i);
      idx = i;
      break;
    }
  }
  pthread_mutex_unlock(&g_tls_alloc_mu);
  if( idx != 0xFFFFFFFFu ) {
    pthread_mutex_lock(&g_fls_mu);
    g_fls_callbacks[idx] = callback;
    pthread_mutex_unlock(&g_fls_mu);
  }
  log_always("[SHIM] FlsAlloc() -> idx=%u\n", idx);
  return idx;
}

// LIMITATION: Windows FlsFree invokes the slot's destructor on every
// thread that has a non-NULL value in that slot.  Doing that on Linux
// would need (a) a per-(thread,slot) registry maintained from every
// FlsSetValue call, and (b) some way to run the destructor in the owning
// thread's context — typically a signal + cooperative dispatcher.
// Neither matches a single-threaded compression CLI's needs, so we
// invoke the callback only for the calling thread.  Other threads'
// slots are still released via shim_thread_exit when those threads
// terminate (the slots array is a pthread_key with a destructor).
extern "C" EXPORT BOOL kernel32_FlsFree(DWORD idx) {
  log_always("[SHIM] FlsFree(idx=%u) [caller=%p]\n", idx, __builtin_return_address(0));
  if( idx >= FLS_MAX_SLOTS ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  void** slots = tls_get_slots();
  void* val = slots ? slots[idx] : NULL;
  pthread_mutex_lock(&g_fls_mu);
  void* cb = g_fls_callbacks[idx];
  g_fls_callbacks[idx] = NULL;
  pthread_mutex_unlock(&g_fls_mu);
  pthread_mutex_lock(&g_tls_alloc_mu);
  g_tls_alloc_used &= ~(1ULL<<idx);
  pthread_mutex_unlock(&g_tls_alloc_mu);
  if( val && cb ) {
    if( slots ) slots[idx] = NULL;
    ((fls_callback_t)cb)(val);
  }
  return TRUE;
}

extern "C" EXPORT LPVOID kernel32_FlsGetValue(DWORD idx) {
  SET_LAST_ERROR(0);
  if( idx >= FLS_MAX_SLOTS ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return NULL;
  }
  void** slots = tls_get_slots();
  void* v = slots ? slots[idx] : NULL;
  log_always("[SHIM] FlsGetValue(idx=%u) -> %p\n", idx, v);
  return v;
}

extern "C" EXPORT BOOL kernel32_FlsSetValue(DWORD idx, LPVOID val) {
  if( idx >= FLS_MAX_SLOTS ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  void** slots = tls_get_slots();
  if( slots ) slots[idx] = val;
  log_always("[SHIM] FlsSetValue(idx=%u, val=%p)\n", idx, val);
  return TRUE;
}
