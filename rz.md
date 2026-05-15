# rz.exe conversion

rz.exe — RZip archiver, PE32+ x64, 9 sections, no base relocs.

Test: `./rz.elf a -y archive 3.exe`

## Missing symbols (44 total)

### kernel32 — functional
- [x] `AddVectoredExceptionHandler` — stub (return non-NULL)
- [x] `RemoveVectoredExceptionHandler` — stub
- [x] `DuplicateHandle` — dup() for file handles, ref-bump for others
- [x] `FileTimeToLocalFileTime` — subtract local UTC offset
- [x] `GetConsoleScreenBufferInfo` — fake 80×25 terminal
- [x] `GetConsoleTitleA` — return empty string
- [x] `GetCurrentThread` — pseudo-handle (HANDLE)-2
- [x] `GetHandleInformation` — flags=0, return TRUE
- [x] `GetProcessAffinityMask` — all CPUs via sched_getaffinity
- [x] `GetProcessTimes` — getrusage for user/kernel time
- [x] `GetTempPathW` — /tmp\ (from $TEMP or /tmp)
- [x] `GetTempFileNameW` — mkstemp-style unique name
- [x] `GetThreadContext` — stub FALSE
- [x] `GetThreadPriority` — return THREAD_PRIORITY_NORMAL
- [x] `GlobalMemoryStatusEx` — sysinfo, extended MEMORYSTATUSEX
- [x] `OutputDebugStringA` — log_always
- [x] `ResumeThread` — stub (return 1)
- [x] `SetConsoleTitleA` — stub
- [x] `SetCurrentDirectoryW` — chdir
- [x] `SetProcessAffinityMask` — stub TRUE
- [x] `SetThreadContext` — stub FALSE
- [x] `SetThreadPriority` — stub TRUE
- [x] `SuspendThread` — stub (return 0)
- [x] `TryEnterCriticalSection` — pthread_mutex_trylock
- [x] `WaitForMultipleObjects` — poll loop over WaitForSingleObject

### msvcrt
- [x] `_beginthreadex` — reuse ThreadObj / pthread_create
- [x] `_endthreadex` — ExitThread
- [x] `_setjmp` — naked asm, Windows JUMP_BUFFER layout
- [x] `longjmp` — naked asm, restores callee-save regs + rsp + jmp
- [x] `_strdup` — malloc + memcpy
- [x] `_ultoa` — sprintf radix conversion
- [x] `_wcsicmp` — towlower loop on uint16_t
- [x] `_wcslwr` — in-place towlower on uint16_t
- [x] `fflush` — no-op (shim does not buffer)
- [x] `qsort` — ms_abi comparator wrapper + libc qsort
- [x] `realloc` — libc realloc
- [x] `scanf` — fgets from stdin + manual format parsing
- [x] `wcscat` — uint16_t string append
- [x] `wcschr` — uint16_t search
- [x] `wcscmp` — uint16_t compare
- [x] `wcsrchr` — uint16_t reverse search

### other DLLs
- [x] `shell32_CommandLineToArgvW` — parse cmdline into wide argv heap array
- [x] `shlwapi_PathMatchSpecW` — win_fnmatch on wide path
- [x] `winmm_timeGetTime` — clock_gettime MONOTONIC ms
