#pragma once
// Thread-related kernel32 surface — included from shim.cpp AFTER
// shim_kernel32_sync.hpp so it can rely on the sync types & helpers
// (ThreadObj, sync_obj_destroy, undo_wait_acquire, deadline_from_ms,
// g_thread_obj_key / g_thread_key_once / thread_key_init,
// kernel32_WaitForSingleObject).
//
// Covers:
//   - GetCurrentThread pseudo-handle (-2)
//   - SuspendThread / ResumeThread (SIGUSR1 + per-ThreadObj sem_t)
//   - GetThreadPriority / SetThreadPriority stubs
//   - GetThreadContext (current-thread delegates to RtlCaptureContext)
//   - SetThreadContext stub
//   - GetProcessAffinityMask / SetProcessAffinityMask
//   - GetProcessTimes (via getrusage)
//   - GetHandleInformation, DuplicateHandle (with pseudo-handle -2 → real
//     H_THREAD slot)
//   - TryEnterCriticalSection
//   - WaitForMultipleObjects (poll loop with rollback on partial acquire)

extern "C" EXPORT HANDLE kernel32_GetCurrentThread(void) {
  return (HANDLE)(intptr_t)-2;   // Windows pseudo-handle convention
}

extern "C" EXPORT DWORD kernel32_SuspendThread(HANDLE h) {
  pthread_mutex_lock(&g_handles_mu);
  int idx = handle_to_idx(h);
  if( idx < 0 || g_handles[idx].kind != H_THREAD ) {
    pthread_mutex_unlock(&g_handles_mu);
    SET_LAST_ERROR(ERROR_INVALID_HANDLE); return (DWORD)-1;
  }
  ThreadObj* obj = (ThreadObj*)g_handles[idx].ptr;
  ++obj->refcount;
  pthread_mutex_unlock(&g_handles_mu);

  DWORD prev = (DWORD)__atomic_fetch_add(&obj->suspend_count, 1, __ATOMIC_SEQ_CST);
  if( prev == 0 ) pthread_kill(obj->tid, SIGUSR1);  // only signal when transitioning 0→1

  pthread_mutex_lock(&g_handles_mu);
  int new_rc = --obj->refcount;
  pthread_mutex_unlock(&g_handles_mu);
  if( new_rc == 0 ) sync_obj_destroy(H_THREAD, obj);
  return prev;
}

extern "C" EXPORT DWORD kernel32_ResumeThread(HANDLE h) {
  if( h == (HANDLE)(intptr_t)-2 ) return 0;  // GetCurrentThread() pseudo-handle

  pthread_mutex_lock(&g_handles_mu);
  int idx = handle_to_idx(h);
  if( idx < 0 || g_handles[idx].kind != H_THREAD ) {
    pthread_mutex_unlock(&g_handles_mu);
    SET_LAST_ERROR(ERROR_INVALID_HANDLE); return (DWORD)-1;
  }
  ThreadObj* obj = (ThreadObj*)g_handles[idx].ptr;
  ++obj->refcount;
  pthread_mutex_unlock(&g_handles_mu);

  int prev_i = __atomic_fetch_sub(&obj->suspend_count, 1, __ATOMIC_SEQ_CST);
  DWORD prev = (DWORD)(prev_i < 0 ? 0 : prev_i);
  if( prev_i <= 0 ) {
    __atomic_fetch_add(&obj->suspend_count, 1, __ATOMIC_SEQ_CST);  // undo: wasn't suspended
  } else if( prev_i == 1 ) {
    sem_post(&obj->suspend_sem);  // only post when transitioning 1→0
  }

  pthread_mutex_lock(&g_handles_mu);
  int new_rc = --obj->refcount;
  pthread_mutex_unlock(&g_handles_mu);
  if( new_rc == 0 ) sync_obj_destroy(H_THREAD, obj);
  return prev;
}

extern "C" EXPORT int  kernel32_GetThreadPriority(HANDLE /*h*/)              { return 0; }  // THREAD_PRIORITY_NORMAL
extern "C" EXPORT BOOL kernel32_SetThreadPriority(HANDLE /*h*/, int /*pri*/) { return TRUE; }

extern "C" EXPORT BOOL kernel32_GetThreadContext(HANDLE h, void* ctx) {
  if( !ctx ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }
  // Current-thread pseudo-handle: same fill RtlCaptureContext does.
  // Cross-thread context capture would need SIGUSR1 + ucontext save from
  // the target's signal handler — not implemented.
  if( h == (HANDLE)(intptr_t)-2 ) {
    kernel32_RtlCaptureContext(ctx);
    return TRUE;
  }
  SET_LAST_ERROR(1); return FALSE;   // ERROR_INVALID_FUNCTION
}
extern "C" EXPORT BOOL kernel32_SetThreadContext(HANDLE /*h*/, const void* /*ctx*/) {
  // Setting another thread's RIP/RSP requires either ptrace or a
  // signal-handler hand-off neither of which is in scope.
  SET_LAST_ERROR(1); return FALSE;   // ERROR_INVALID_FUNCTION
}

extern "C" EXPORT BOOL kernel32_GetProcessAffinityMask(HANDLE /*h*/, uint64_t* proc_mask, uint64_t* sys_mask) {
  cpu_set_t cs; CPU_ZERO(&cs);
  sched_getaffinity(0, sizeof(cs), &cs);
  uint64_t mask = 0;
  for( int i = 0; i < 64; ++i ) if( CPU_ISSET(i, &cs) ) mask |= (1ULL << i);
  if( proc_mask ) *proc_mask = mask;
  if( sys_mask  ) *sys_mask  = mask;
  return TRUE;
}
extern "C" EXPORT BOOL kernel32_SetProcessAffinityMask(HANDLE /*h*/, uint64_t /*mask*/) { return TRUE; }

// ---------------------------------------------------------------------------
// Process times
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL kernel32_GetProcessTimes(HANDLE /*h*/,
    FILETIME* created, FILETIME* exited, FILETIME* kernel_t, FILETIME* user_t) {
  struct rusage ru;
  getrusage(RUSAGE_SELF, &ru);
  auto tv_to_ft = [](const struct timeval& tv) -> uint64_t {
    return (uint64_t)tv.tv_sec * 10000000ULL + (uint64_t)tv.tv_usec * 10ULL;
  };
  if( kernel_t ) { uint64_t v = tv_to_ft(ru.ru_stime); *kernel_t = u64_to_ft(v); }
  if( user_t   ) { uint64_t v = tv_to_ft(ru.ru_utime); *user_t   = u64_to_ft(v); }
  if( created  ) memset(created, 0, sizeof(*created));
  if( exited   ) memset(exited,  0, sizeof(*exited));
  return TRUE;
}

// ---------------------------------------------------------------------------
// Handle info / duplication
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL kernel32_GetHandleInformation(HANDLE /*h*/, DWORD* flags) {
  if( flags ) *flags = 0;
  return TRUE;
}

extern "C" EXPORT BOOL kernel32_DuplicateHandle(
    HANDLE /*src_proc*/, HANDLE src, HANDLE /*dst_proc*/, HANDLE* dst,
    DWORD /*access*/, BOOL /*inherit*/, DWORD options) {
  if( !dst ) { SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return FALSE; }

  // Windows GetCurrentThread() returns the pseudo-handle -2. Translate it to
  // a real H_THREAD handle so pthreads-win32 implicit thread creation works.
  if( src == (HANDLE)(intptr_t)-2 ) {
    pthread_once(&g_thread_key_once, thread_key_init);
    ThreadObj* obj = (ThreadObj*)pthread_getspecific(g_thread_obj_key);
    if( !obj ) {
      // Not a managed thread (main thread / external thread): create a minimal
      // wrapper. tid=0 tells sync_obj_destroy to skip join/detach.
      // Cache it in g_thread_obj_key so repeated DuplicateHandle calls from
      // the same thread share one ThreadObj rather than allocating a new one
      // each time.
      obj = (ThreadObj*)calloc(1, sizeof(ThreadObj));
      if( !obj ) { SET_LAST_ERROR(ERROR_OUTOFMEMORY); return FALSE; }
      pthread_mutex_init(&obj->mu, nullptr);
      pthread_cond_init(&obj->cv, nullptr);
      sem_init(&obj->suspend_sem, 0, 0);
      obj->refcount = 0; // bumped below under lock
      obj->done     = true;
      // obj->tid stays 0; cache so further DuplicateHandle calls reuse this obj
      pthread_setspecific(g_thread_obj_key, obj);
    }
    pthread_mutex_lock(&g_handles_mu);
    ++(obj->refcount);
    for( int i = 3; i < MAX_HANDLES; ++i ) {
      if( g_handles[i].kind == H_FREE ) {
        g_handles[i].kind = H_THREAD;
        g_handles[i].ptr  = obj;
        *dst = idx_to_handle(i);
        pthread_mutex_unlock(&g_handles_mu);
        return TRUE;
      }
    }
    // Handle table full — undo the refcount bump and clean up if new obj.
    if( --(obj->refcount) == 0 ) {
      pthread_mutex_unlock(&g_handles_mu);
      pthread_mutex_destroy(&obj->mu); pthread_cond_destroy(&obj->cv); free(obj);
    } else {
      pthread_mutex_unlock(&g_handles_mu);
    }
    SET_LAST_ERROR(ERROR_TOO_MANY_OPEN_FILES); return FALSE;
  }

  int idx = handle_to_idx(src);
  if( idx < 0 ) { SET_LAST_ERROR(ERROR_INVALID_HANDLE); return FALSE; }
  HandleKind kind = g_handles[idx].kind;
  if( kind == H_FILE ) {
    int fd = dup(g_handles[idx].fd);
    if( fd < 0 ) { set_errno_error(); return FALSE; }
    *dst = handle_alloc_file(fd);
    if( *dst == INVALID_HANDLE_VALUE ) { close(fd); return FALSE; }
  } else {
    // For non-file handles, share the same slot (bump refcount on sync objects).
    pthread_mutex_lock(&g_handles_mu);
    for( int i = 3; i < MAX_HANDLES; ++i ) {
      if( g_handles[i].kind == H_FREE ) {
        g_handles[i] = g_handles[idx];
        if( kind >= H_MUTEX ) ++(*(int*)g_handles[i].ptr);
        *dst = idx_to_handle(i);
        pthread_mutex_unlock(&g_handles_mu);
        goto done;
      }
    }
    pthread_mutex_unlock(&g_handles_mu);
    SET_LAST_ERROR(ERROR_TOO_MANY_OPEN_FILES); return FALSE;
  }
done:
  if( options & 1 /*DUPLICATE_CLOSE_SOURCE*/ ) kernel32_CloseHandle(src);
  return TRUE;
}

// ---------------------------------------------------------------------------
// TryEnterCriticalSection
// ---------------------------------------------------------------------------
extern "C" EXPORT BOOL kernel32_TryEnterCriticalSection(CRITICAL_SECTION* cs) {
  return pthread_mutex_trylock((pthread_mutex_t*)cs) == 0 ? TRUE : FALSE;
}

// ---------------------------------------------------------------------------
// WaitForMultipleObjects — sequential poll with back-off
// ---------------------------------------------------------------------------
#define MAXIMUM_WAIT_OBJECTS 64
extern "C" EXPORT DWORD kernel32_WaitForMultipleObjects(
    DWORD count, const HANDLE* handles, BOOL wait_all, DWORD ms) {
  if( !handles || count == 0 || count > MAXIMUM_WAIT_OBJECTS ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER); return WAIT_FAILED;
  }
  bool inf = (ms == INFINITE);
  struct timespec deadline;
  if( !inf ) deadline_from_ms(ms, &deadline);

  auto time_left_ms = [&]() -> DWORD {
    if( inf ) return INFINITE;
    struct timespec now; clock_gettime(CLOCK_REALTIME, &now);
    long diff = (long)(deadline.tv_sec - now.tv_sec) * 1000
              + (long)(deadline.tv_nsec - now.tv_nsec) / 1000000;
    return diff <= 0 ? 0u : (DWORD)diff;
  };

  if( !wait_all ) {
    // Wait for any: poll with 1 ms slices until timeout.
    while( true ) {
      for( DWORD i = 0; i < count; ++i ) {
        DWORD r = kernel32_WaitForSingleObject(handles[i], 0);
        if( r == WAIT_OBJECT_0 ) return WAIT_OBJECT_0 + i;
      }
      DWORD left = time_left_ms();
      if( left == 0 ) return WAIT_TIMEOUT;
      DWORD slice = (left == INFINITE || left > 1) ? 1 : left;
      struct timespec ts = { 0, (long)slice * 1000000L };
      nanosleep(&ts, nullptr);
    }
  } else {
    // Wait for all: poll each handle with 0 timeout each round.  If one
    // fails, roll back the handles acquired so far before sleeping so no
    // handle (e.g. a mutex) stays locked while we wait for the rest.
    while( true ) {
      DWORD n_acq = 0;
      DWORD fail  = WAIT_OBJECT_0;
      for( DWORD i = 0; i < count; ++i ) {
        DWORD r = kernel32_WaitForSingleObject(handles[i], 0);
        if( r == WAIT_OBJECT_0 ) { ++n_acq; }
        else { fail = (r == WAIT_FAILED) ? WAIT_FAILED : WAIT_TIMEOUT; break; }
      }
      if( fail == WAIT_OBJECT_0 ) return WAIT_OBJECT_0;
      for( DWORD j = 0; j < n_acq; ++j ) undo_wait_acquire(handles[j]);
      if( fail == WAIT_FAILED ) return WAIT_FAILED;
      DWORD left = time_left_ms();
      if( left == 0 ) return WAIT_TIMEOUT;
      DWORD slice = (left == INFINITE || left > 1) ? 1 : left;
      struct timespec ts = { 0, (long)slice * 1000000L };
      nanosleep(&ts, nullptr);
    }
  }
}
