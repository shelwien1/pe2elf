#pragma once
// Vectored Exception Handler — included from shim.cpp.
//
// Maintains a real doubly-linked list of `PVECTORED_EXCEPTION_HANDLER`
// callbacks and dispatches them in registration order from the ms_abi
// entrypoints (`UnhandledExceptionFilter`, `RaiseException`).  Never
// invoked from `crash_handler`: calling user ms_abi code from a POSIX
// signal context isn't AS-safe.

typedef LONG (__attribute__((ms_abi)) *vectored_handler_t)(void*);

struct VEHEntry {
  VEHEntry* prev;
  VEHEntry* next;
  vectored_handler_t fn;
};

static pthread_mutex_t g_veh_mu = PTHREAD_MUTEX_INITIALIZER;
static VEHEntry* g_veh_head = nullptr;
static VEHEntry* g_veh_tail = nullptr;

extern "C" EXPORT void* kernel32_AddVectoredExceptionHandler(DWORD first, void* handler) {
  if( !handler ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return nullptr; }
  VEHEntry* e = (VEHEntry*)malloc(sizeof(VEHEntry));
  if( !e ) { SET_LAST_ERROR(ERROR_OUTOFMEMORY); return nullptr; }
  e->fn = (vectored_handler_t)handler;
  pthread_mutex_lock(&g_veh_mu);
  if( first ) {
    e->prev = nullptr;
    e->next = g_veh_head;
    if( g_veh_head ) g_veh_head->prev = e;
    g_veh_head = e;
    if( !g_veh_tail ) g_veh_tail = e;
  } else {
    e->next = nullptr;
    e->prev = g_veh_tail;
    if( g_veh_tail ) g_veh_tail->next = e;
    g_veh_tail = e;
    if( !g_veh_head ) g_veh_head = e;
  }
  pthread_mutex_unlock(&g_veh_mu);
  return e;   // entry pointer doubles as the opaque handle
}

extern "C" EXPORT DWORD kernel32_RemoveVectoredExceptionHandler(void* handle) {
  if( !handle ) return 0;
  VEHEntry* e = (VEHEntry*)handle;
  pthread_mutex_lock(&g_veh_mu);
  bool found = false;
  for( VEHEntry* p = g_veh_head; p; p = p->next ) {
    if( p == e ) { found = true; break; }
  }
  if( found ) {
    if( e->prev ) e->prev->next = e->next; else g_veh_head = e->next;
    if( e->next ) e->next->prev = e->prev; else g_veh_tail = e->prev;
  }
  pthread_mutex_unlock(&g_veh_mu);
  if( !found ) return 0;
  free(e);
  return 1;
}

// Snapshot the handler list and call each in order.  Returns -1 if any
// handler said EXCEPTION_CONTINUE_EXECUTION, 0 otherwise.  Releases the
// mutex before dispatch so handlers may add/remove without deadlock.
#define MAX_VEH_SNAPSHOT 32
static LONG run_vectored_handlers(void* pExcept) {
  vectored_handler_t snap[MAX_VEH_SNAPSHOT];
  size_t n = 0;
  pthread_mutex_lock(&g_veh_mu);
  for( VEHEntry* p = g_veh_head; p && n < MAX_VEH_SNAPSHOT; p = p->next )
    snap[n++] = p->fn;
  pthread_mutex_unlock(&g_veh_mu);
  for( size_t i = 0; i < n; i++ ) {
    LONG r = snap[i](pExcept);
    if( r == -1 /*EXCEPTION_CONTINUE_EXECUTION*/ ) return r;
  }
  return 0;
}
