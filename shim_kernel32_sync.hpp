#pragma once
// kernel32 threading/sync shims — included from shim.cpp.

#ifndef WAIT_OBJECT_0
#define WAIT_OBJECT_0   0u
#define WAIT_TIMEOUT    258u
#define WAIT_FAILED     0xFFFFFFFFu
#define STILL_ACTIVE    0x00000103u
#define INFINITE        0xFFFFFFFFu
#endif
#ifndef ERROR_SEM_TIMEOUT
#define ERROR_SEM_TIMEOUT 121u
#endif

// ---------------------------------------------------------------------------
// Generic sync handle allocator
// ---------------------------------------------------------------------------
static HANDLE handle_alloc_sync(HandleKind kind, void* ptr) {
  pthread_mutex_lock(&g_handles_mu);
  for( int i = 3; i < MAX_HANDLES; ++i ) {
    if( g_handles[i].kind == H_FREE ) {
      g_handles[i].kind = kind;
      g_handles[i].ptr  = ptr;
      pthread_mutex_unlock(&g_handles_mu);
      return idx_to_handle(i);
    }
  }
  pthread_mutex_unlock(&g_handles_mu);
  SET_LAST_ERROR(ERROR_TOO_MANY_OPEN_FILES);
  return INVALID_HANDLE_VALUE;
}

// ---------------------------------------------------------------------------
// Destroy + free a sync object (called only when refcount reaches 0)
// ---------------------------------------------------------------------------
static void sync_obj_destroy(HandleKind kind, void* ptr) {
  switch( kind ) {
  case H_MUTEX: {
    MutexObj* m = (MutexObj*)ptr;
    pthread_mutex_destroy(&m->mu); free(m); break;
  }
  case H_EVENT: {
    EventObj* ev = (EventObj*)ptr;
    pthread_mutex_destroy(&ev->mu); pthread_cond_destroy(&ev->cv); free(ev); break;
  }
  case H_SEMAPHORE: {
    SemaphoreObj* s = (SemaphoreObj*)ptr;
    sem_destroy(&s->sem); free(s); break;
  }
  case H_THREAD: {
    ThreadObj* t = (ThreadObj*)ptr;
    pthread_mutex_lock(&t->mu);
    bool done = t->done;
    pthread_mutex_unlock(&t->mu);
    // tid==0 marks an implicit handle (not backed by a managed thread);
    // skip join/detach to avoid EDEADLK or double-detach.
    if( t->tid ) {
      if( done ) pthread_join(t->tid, nullptr);
      else        pthread_detach(t->tid);
    }
    sem_destroy(&t->suspend_sem);
    pthread_mutex_destroy(&t->mu); pthread_cond_destroy(&t->cv); free(t); break;
  }
  default: break;
  }
}

// ---------------------------------------------------------------------------
// Timeout: Windows ms → absolute CLOCK_REALTIME timespec
// ---------------------------------------------------------------------------
static void deadline_from_ms(DWORD ms, struct timespec* ts) {
  clock_gettime(CLOCK_REALTIME, ts);
  ts->tv_sec  += (long)(ms / 1000);
  ts->tv_nsec += (long)(ms % 1000) * 1000000L;
  if( ts->tv_nsec >= 1000000000L ) { ts->tv_sec++; ts->tv_nsec -= 1000000000L; }
}

// ---------------------------------------------------------------------------
// WaitForSingleObject — dispatches on handle kind
// Bumps the object's refcount before releasing g_handles_mu so a concurrent
// CloseHandle cannot free the object while we are blocked inside the wait.
// ---------------------------------------------------------------------------
extern "C" EXPORT DWORD kernel32_WaitForSingleObject(HANDLE h, DWORD ms) {
  // Pseudo-handle -2 (GetCurrentThread): a thread cannot wait on itself.
  // Return WAIT_TIMEOUT to avoid deadlock (matches Windows behaviour for ms=0;
  // waiting indefinitely on oneself would deadlock on Windows too).
  if( h == (HANDLE)(intptr_t)-2 ) {
    (void)ms;
    SET_LAST_ERROR(ERROR_SEM_TIMEOUT); return WAIT_TIMEOUT;
  }
  // Read kind+ptr and bump refcount atomically under the handle lock.
  pthread_mutex_lock(&g_handles_mu);
  int idx = handle_to_idx(h);
  if( idx < 0 ) {
    pthread_mutex_unlock(&g_handles_mu);
    SET_LAST_ERROR(ERROR_INVALID_HANDLE); return WAIT_FAILED;
  }
  HandleKind kind = g_handles[idx].kind;
  void* ptr = g_handles[idx].ptr;
  if( kind < H_MUTEX ) {   // H_FREE / H_FILE / H_FIND / H_MODULE — not waitable
    pthread_mutex_unlock(&g_handles_mu);
    SET_LAST_ERROR(ERROR_INVALID_HANDLE); return WAIT_FAILED;
  }
  ++(*(int*)ptr);   // refcount; first field of every sync struct
  pthread_mutex_unlock(&g_handles_mu);

  bool inf = (ms == INFINITE);
  struct timespec ts;
  if( !inf ) deadline_from_ms(ms, &ts);

  DWORD ret = WAIT_FAILED;
  switch( kind ) {
  case H_MUTEX: {
    MutexObj* m = (MutexObj*)ptr;
    int r = inf ? pthread_mutex_lock(&m->mu)
                : pthread_mutex_timedlock(&m->mu, &ts);
    if( r == 0 ) ret = WAIT_OBJECT_0;
    else if( r == ETIMEDOUT ) { SET_LAST_ERROR(ERROR_SEM_TIMEOUT); ret = WAIT_TIMEOUT; }
    else { SET_LAST_ERROR(ERROR_INVALID_HANDLE); }
    break;
  }
  case H_EVENT: {
    EventObj* ev = (EventObj*)ptr;
    pthread_mutex_lock(&ev->mu);
    int r = 0;
    while( !ev->signaled && r == 0 ) {
      r = inf ? pthread_cond_wait(&ev->cv, &ev->mu)
              : pthread_cond_timedwait(&ev->cv, &ev->mu, &ts);
    }
    if( ev->signaled ) {
      if( !ev->manual_reset ) ev->signaled = false;
      ret = WAIT_OBJECT_0;
    } else {
      if( r == ETIMEDOUT ) { SET_LAST_ERROR(ERROR_SEM_TIMEOUT); ret = WAIT_TIMEOUT; }
    }
    pthread_mutex_unlock(&ev->mu);
    break;
  }
  case H_SEMAPHORE: {
    SemaphoreObj* s = (SemaphoreObj*)ptr;
    int r = inf ? sem_wait(&s->sem) : sem_timedwait(&s->sem, &ts);
    if( r == 0 ) ret = WAIT_OBJECT_0;
    else if( errno == ETIMEDOUT ) { SET_LAST_ERROR(ERROR_SEM_TIMEOUT); ret = WAIT_TIMEOUT; }
    else { SET_LAST_ERROR(ERROR_INVALID_HANDLE); }
    break;
  }
  case H_THREAD: {
    ThreadObj* t = (ThreadObj*)ptr;
    pthread_mutex_lock(&t->mu);
    int r = 0;
    while( !t->done && r == 0 ) {
      r = inf ? pthread_cond_wait(&t->cv, &t->mu)
              : pthread_cond_timedwait(&t->cv, &t->mu, &ts);
    }
    if( t->done ) ret = WAIT_OBJECT_0;
    else if( r == ETIMEDOUT ) { SET_LAST_ERROR(ERROR_SEM_TIMEOUT); ret = WAIT_TIMEOUT; }
    pthread_mutex_unlock(&t->mu);
    break;
  }
  default: SET_LAST_ERROR(ERROR_INVALID_HANDLE); break;
  }

  // Release our reference; free the object if CloseHandle already ran.
  // For H_MUTEX with WAIT_OBJECT_0 the mutex is held by this thread; unlock
  // it before destroying so pthread_mutex_destroy does not see a locked mutex
  // (POSIX UB).  The application has already closed the handle so it cannot
  // call ReleaseMutex anyway.
  pthread_mutex_lock(&g_handles_mu);
  int new_rc = --(*(int*)ptr);
  pthread_mutex_unlock(&g_handles_mu);
  if( new_rc == 0 ) {
    if( kind == H_MUTEX && ret == WAIT_OBJECT_0 )
      pthread_mutex_unlock(&((MutexObj*)ptr)->mu);
    sync_obj_destroy(kind, ptr);
  }

  return ret;
}

// ---------------------------------------------------------------------------
// Mutex
// ---------------------------------------------------------------------------
extern "C" EXPORT HANDLE kernel32_CreateMutexA(void* sa, BOOL initial_owner, LPCSTR name) {
  (void)sa; (void)name;
  MutexObj* m = (MutexObj*)malloc(sizeof(MutexObj));
  if( !m ) return INVALID_HANDLE_VALUE;
  m->refcount = 1;
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&m->mu, &attr);
  pthread_mutexattr_destroy(&attr);
  if( initial_owner ) pthread_mutex_lock(&m->mu);
  HANDLE h = handle_alloc_sync(H_MUTEX, m);
  if( h == INVALID_HANDLE_VALUE ) { pthread_mutex_destroy(&m->mu); free(m); }
  return h;
}
extern "C" EXPORT HANDLE kernel32_CreateMutexW(void* sa, BOOL initial_owner, const uint16_t* /*name*/) {
  return kernel32_CreateMutexA(sa, initial_owner, nullptr);
}

extern "C" EXPORT BOOL kernel32_ReleaseMutex(HANDLE h) {
  pthread_mutex_lock(&g_handles_mu);
  int idx = handle_to_idx(h);
  if( idx < 0 || g_handles[idx].kind != H_MUTEX ) {
    pthread_mutex_unlock(&g_handles_mu);
    SET_LAST_ERROR(ERROR_INVALID_HANDLE); return FALSE;
  }
  MutexObj* m = (MutexObj*)g_handles[idx].ptr;
  ++m->refcount;
  pthread_mutex_unlock(&g_handles_mu);

  pthread_mutex_unlock(&m->mu);

  pthread_mutex_lock(&g_handles_mu);
  int new_rc = --m->refcount;
  pthread_mutex_unlock(&g_handles_mu);
  if( new_rc == 0 ) sync_obj_destroy(H_MUTEX, m);
  return TRUE;
}

// ---------------------------------------------------------------------------
// Event
// ---------------------------------------------------------------------------
static void event_signal(EventObj* ev) {
  pthread_mutex_lock(&ev->mu);
  ev->signaled = true;
  if( ev->manual_reset ) pthread_cond_broadcast(&ev->cv);
  else                   pthread_cond_signal(&ev->cv);
  pthread_mutex_unlock(&ev->mu);
}

extern "C" EXPORT HANDLE kernel32_CreateEventA(void* sa, BOOL manual_reset, BOOL initial_state, LPCSTR name) {
  (void)sa; (void)name;
  EventObj* ev = (EventObj*)calloc(1, sizeof(EventObj));
  if( !ev ) return INVALID_HANDLE_VALUE;
  ev->refcount = 1;
  pthread_mutex_init(&ev->mu, nullptr);
  pthread_cond_init(&ev->cv, nullptr);
  ev->manual_reset = (manual_reset != 0);
  ev->signaled     = (initial_state != 0);
  HANDLE h = handle_alloc_sync(H_EVENT, ev);
  if( h == INVALID_HANDLE_VALUE ) {
    pthread_mutex_destroy(&ev->mu); pthread_cond_destroy(&ev->cv); free(ev);
  }
  return h;
}

extern "C" EXPORT BOOL kernel32_SetEvent(HANDLE h) {
  pthread_mutex_lock(&g_handles_mu);
  int idx = handle_to_idx(h);
  if( idx < 0 || g_handles[idx].kind != H_EVENT ) {
    pthread_mutex_unlock(&g_handles_mu);
    SET_LAST_ERROR(ERROR_INVALID_HANDLE); return FALSE;
  }
  EventObj* ev = (EventObj*)g_handles[idx].ptr;
  ++ev->refcount;
  pthread_mutex_unlock(&g_handles_mu);

  event_signal(ev);

  pthread_mutex_lock(&g_handles_mu);
  int new_rc = --ev->refcount;
  pthread_mutex_unlock(&g_handles_mu);
  if( new_rc == 0 ) sync_obj_destroy(H_EVENT, ev);
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_ResetEvent(HANDLE h) {
  pthread_mutex_lock(&g_handles_mu);
  int idx = handle_to_idx(h);
  if( idx < 0 || g_handles[idx].kind != H_EVENT ) {
    pthread_mutex_unlock(&g_handles_mu);
    SET_LAST_ERROR(ERROR_INVALID_HANDLE); return FALSE;
  }
  EventObj* ev = (EventObj*)g_handles[idx].ptr;
  ++ev->refcount;
  pthread_mutex_unlock(&g_handles_mu);

  pthread_mutex_lock(&ev->mu);
  ev->signaled = false;
  pthread_mutex_unlock(&ev->mu);

  pthread_mutex_lock(&g_handles_mu);
  int new_rc = --ev->refcount;
  pthread_mutex_unlock(&g_handles_mu);
  if( new_rc == 0 ) sync_obj_destroy(H_EVENT, ev);
  return TRUE;
}

// ---------------------------------------------------------------------------
// Semaphore
// ---------------------------------------------------------------------------
extern "C" EXPORT HANDLE kernel32_CreateSemaphoreA(void* sa, LONG initial, LONG /*max_count*/, LPCSTR name) {
  (void)sa; (void)name;
  SemaphoreObj* s = (SemaphoreObj*)malloc(sizeof(SemaphoreObj));
  if( !s ) return INVALID_HANDLE_VALUE;
  s->refcount = 1;
  if( sem_init(&s->sem, 0, (unsigned)initial) != 0 ) { free(s); return INVALID_HANDLE_VALUE; }
  HANDLE h = handle_alloc_sync(H_SEMAPHORE, s);
  if( h == INVALID_HANDLE_VALUE ) { sem_destroy(&s->sem); free(s); }
  return h;
}

extern "C" EXPORT BOOL kernel32_ReleaseSemaphore(HANDLE h, LONG count, LONG* prev) {
  pthread_mutex_lock(&g_handles_mu);
  int idx = handle_to_idx(h);
  if( idx < 0 || g_handles[idx].kind != H_SEMAPHORE ) {
    pthread_mutex_unlock(&g_handles_mu);
    SET_LAST_ERROR(ERROR_INVALID_HANDLE); return FALSE;
  }
  SemaphoreObj* s = (SemaphoreObj*)g_handles[idx].ptr;
  ++s->refcount;
  pthread_mutex_unlock(&g_handles_mu);

  if( prev ) { int v = 0; sem_getvalue(&s->sem, &v); *prev = (LONG)v; }
  for( LONG i = 0; i < count; ++i ) sem_post(&s->sem);

  pthread_mutex_lock(&g_handles_mu);
  int new_rc = --s->refcount;
  pthread_mutex_unlock(&g_handles_mu);
  if( new_rc == 0 ) sync_obj_destroy(H_SEMAPHORE, s);
  return TRUE;
}

// ---------------------------------------------------------------------------
// Thread
// ---------------------------------------------------------------------------
typedef uint32_t (__attribute__((ms_abi)) *win_thread_fn)(void*);

struct ThreadStart { win_thread_fn fn; void* param; ThreadObj* obj; bool create_suspended; };

static pthread_key_t  g_thread_obj_key;
static pthread_once_t g_thread_key_once = PTHREAD_ONCE_INIT;
static void thread_key_init(void) { pthread_key_create(&g_thread_obj_key, nullptr); }

static void thread_finish(ThreadObj* obj, int64_t code) {
  if( !obj ) return;
  pthread_mutex_lock(&obj->mu);
  obj->exit_code = code;
  obj->done      = true;
  pthread_cond_broadcast(&obj->cv);
  pthread_mutex_unlock(&obj->mu);
}

extern void shim_init_teb(void);         // defined in shim.cpp
extern void run_tls_callbacks(uint32_t); // defined in shim.cpp
extern void tls_static_init_thread(void);// defined in shim.cpp

// SIGUSR1 handler: called by SuspendThread; blocks in suspend_sem until ResumeThread.
static void suspend_signal_handler(int /*sig*/) {
  pthread_once(&g_thread_key_once, thread_key_init);
  ThreadObj* obj = (ThreadObj*)pthread_getspecific(g_thread_obj_key);
  if( !obj ) return;
  while( sem_wait(&obj->suspend_sem) == -1 && errno == EINTR );
}

static void* thread_trampoline(void* arg) {
  ThreadStart ts = *(ThreadStart*)arg;
  free(arg);
  shim_init_teb();
  run_tls_callbacks(2);     // DLL_THREAD_ATTACH
  tls_static_init_thread(); // populate static TLS block (like Windows loader)
  pthread_once(&g_thread_key_once, thread_key_init);
  pthread_setspecific(g_thread_obj_key, ts.obj);

  // If created with CREATE_SUSPENDED, block here until the first ResumeThread.
  // Use the snapshot flag rather than re-reading mutable suspend_count: if
  // ResumeThread posts the semaphore before we reach sem_wait, the wait
  // returns immediately (correct); reading suspend_count would be racy and
  // could leave a stale token that prematurely unblocks a future SuspendThread.
  if( ts.create_suspended )
    while( sem_wait(&ts.obj->suspend_sem) == -1 && errno == EINTR );

  uint32_t ret = ts.fn(ts.param);
  run_tls_callbacks(3);  // DLL_THREAD_DETACH — mirrors what Windows loader does
  thread_finish(ts.obj, (int64_t)(uint32_t)ret);
  return nullptr;
}

extern "C" EXPORT HANDLE kernel32_CreateThread(void* sa, size_t /*stack*/, win_thread_fn fn,
                                                void* param, DWORD flags, DWORD* tid_out) {
  (void)sa;
#define CREATE_SUSPENDED 0x00000004
  ThreadObj* obj = (ThreadObj*)calloc(1, sizeof(ThreadObj));
  if( !obj ) { SET_LAST_ERROR(ERROR_OUTOFMEMORY); return NULL; }
  obj->refcount = 1;
  pthread_mutex_init(&obj->mu, nullptr);
  pthread_cond_init(&obj->cv, nullptr);
  sem_init(&obj->suspend_sem, 0, 0);
  if( flags & 0x4 /* CREATE_SUSPENDED */ ) obj->suspend_count = 1;

  ThreadStart* ts = (ThreadStart*)malloc(sizeof(ThreadStart));
  if( !ts ) {
    pthread_mutex_destroy(&obj->mu); pthread_cond_destroy(&obj->cv); free(obj);
    SET_LAST_ERROR(ERROR_OUTOFMEMORY); return NULL;
  }
  ts->fn = fn; ts->param = param; ts->obj = obj;
  ts->create_suspended = (flags & CREATE_SUSPENDED) != 0;

  HANDLE h = handle_alloc_sync(H_THREAD, obj);
  if( h == INVALID_HANDLE_VALUE ) {
    free(ts); sem_destroy(&obj->suspend_sem);
    pthread_mutex_destroy(&obj->mu); pthread_cond_destroy(&obj->cv); free(obj);
    SET_LAST_ERROR(ERROR_TOO_MANY_OPEN_FILES); return NULL;
  }
  if( pthread_create(&obj->tid, nullptr, thread_trampoline, ts) != 0 ) {
    free(ts);
    int idx2 = handle_to_idx(h);
    if( idx2 >= 0 ) { pthread_mutex_lock(&g_handles_mu); g_handles[idx2].kind = H_FREE; pthread_mutex_unlock(&g_handles_mu); }
    sem_destroy(&obj->suspend_sem);
    pthread_mutex_destroy(&obj->mu); pthread_cond_destroy(&obj->cv); free(obj);
    SET_LAST_ERROR(ERROR_OUTOFMEMORY);
    return NULL;
  }
  if( tid_out ) *tid_out = (DWORD)(uintptr_t)obj->tid;
  return h;
}

extern "C" EXPORT void kernel32_ExitThread(DWORD code) {
  pthread_once(&g_thread_key_once, thread_key_init);
  run_tls_callbacks(3);  // DLL_THREAD_DETACH
  thread_finish((ThreadObj*)pthread_getspecific(g_thread_obj_key), (int64_t)(uint32_t)code);
  pthread_exit(nullptr);
}

extern "C" EXPORT BOOL kernel32_GetExitCodeThread(HANDLE h, DWORD* code) {
  // Pseudo-handle -2 (GetCurrentThread): the thread is always running.
  if( h == (HANDLE)(intptr_t)-2 ) {
    if( code ) *code = STILL_ACTIVE;
    return TRUE;
  }
  pthread_mutex_lock(&g_handles_mu);
  int idx = handle_to_idx(h);
  if( idx < 0 || g_handles[idx].kind != H_THREAD ) {
    pthread_mutex_unlock(&g_handles_mu);
    SET_LAST_ERROR(ERROR_INVALID_HANDLE); return FALSE;
  }
  ThreadObj* t = (ThreadObj*)g_handles[idx].ptr;
  ++t->refcount;
  pthread_mutex_unlock(&g_handles_mu);

  pthread_mutex_lock(&t->mu);
  DWORD v = t->done ? (DWORD)(uint32_t)t->exit_code : (DWORD)STILL_ACTIVE;
  pthread_mutex_unlock(&t->mu);
  if( code ) *code = v;

  pthread_mutex_lock(&g_handles_mu);
  int new_rc = --t->refcount;
  pthread_mutex_unlock(&g_handles_mu);
  if( new_rc == 0 ) sync_obj_destroy(H_THREAD, t);
  return TRUE;
}

// ---------------------------------------------------------------------------
// undo_wait_acquire — reverse a WaitForSingleObject(h,0)==WAIT_OBJECT_0
// Used by WaitForMultipleObjects wait-all rollback.
// Must hold no locks on entry.  Bumps refcount inside g_handles_mu so the
// object cannot be freed between the kind read and the release operation.
// ---------------------------------------------------------------------------
static void undo_wait_acquire(HANDLE h) {
  pthread_mutex_lock(&g_handles_mu);
  int idx = handle_to_idx(h);
  if( idx < 0 ) { pthread_mutex_unlock(&g_handles_mu); return; }
  HandleKind kind = g_handles[idx].kind;
  void* ptr = g_handles[idx].ptr;
  if( kind < H_MUTEX ) { pthread_mutex_unlock(&g_handles_mu); return; }
  ++(*(int*)ptr);
  pthread_mutex_unlock(&g_handles_mu);

  switch( kind ) {
  case H_MUTEX:
    pthread_mutex_unlock(&((MutexObj*)ptr)->mu);
    break;
  case H_SEMAPHORE:
    sem_post(&((SemaphoreObj*)ptr)->sem);
    break;
  case H_EVENT: {
    EventObj* ev = (EventObj*)ptr;
    pthread_mutex_lock(&ev->mu);
    ev->signaled = true;
    if( ev->manual_reset ) pthread_cond_broadcast(&ev->cv);
    else                   pthread_cond_signal(&ev->cv);
    pthread_mutex_unlock(&ev->mu);
    break;
  }
  default: break;
  }

  pthread_mutex_lock(&g_handles_mu);
  int new_rc = --(*(int*)ptr);
  pthread_mutex_unlock(&g_handles_mu);
  if( new_rc == 0 ) sync_obj_destroy(kind, ptr);
}

// ---------------------------------------------------------------------------
// SignalObjectAndWait — signal one object then wait on another
// ---------------------------------------------------------------------------
static BOOL signal_handle(HANDLE h) {
  pthread_mutex_lock(&g_handles_mu);
  int idx = handle_to_idx(h);
  if( idx < 0 ) { pthread_mutex_unlock(&g_handles_mu); SET_LAST_ERROR(ERROR_INVALID_HANDLE); return FALSE; }
  HandleKind kind = g_handles[idx].kind;
  pthread_mutex_unlock(&g_handles_mu);
  switch( kind ) {
  case H_MUTEX:     return kernel32_ReleaseMutex(h);
  case H_EVENT:     return kernel32_SetEvent(h);
  case H_SEMAPHORE: return kernel32_ReleaseSemaphore(h, 1, nullptr);
  default: SET_LAST_ERROR(ERROR_INVALID_HANDLE); return FALSE;
  }
}

extern "C" EXPORT DWORD kernel32_SignalObjectAndWait(HANDLE signal, HANDLE wait, DWORD ms, BOOL /*alertable*/) {
  signal_handle(signal);
  return kernel32_WaitForSingleObject(wait, ms);
}


