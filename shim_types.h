#pragma once
#include <stdint.h>
#include <stddef.h>

// Windows calling convention for all shim exports
#define WINAPI __attribute__((ms_abi))

// Windows primitive types
typedef void*       HANDLE;
typedef uint32_t    DWORD;
typedef int32_t     LONG;
typedef int32_t     BOOL;
typedef uint16_t    WORD;
typedef uint8_t     BYTE;
typedef uint64_t    ULONGLONG;
typedef int64_t     LONGLONG;
typedef uintptr_t   ULONG_PTR;
typedef const char*    LPCSTR;
typedef char*          LPSTR;
typedef const uint16_t* LPCWSTR;
typedef uint16_t*      LPWSTR;
typedef void*          LPVOID;
typedef const void*    LPCVOID;
typedef DWORD*         LPDWORD;

#define TRUE  1
#define FALSE 0
#define INVALID_HANDLE_VALUE  ((HANDLE)(intptr_t)-1)
#define PROCESS_PSEUDO_HANDLE ((HANDLE)(intptr_t)-1)
#define HEAP_PSEUDO_HANDLE    ((HANDLE)(intptr_t)1)
#define NULL_HANDLE           ((HANDLE)NULL)

// FILETIME: 100-ns ticks since 1601-01-01 UTC
struct FILETIME { DWORD dwLowDateTime; DWORD dwHighDateTime; };
static inline uint64_t ft_to_u64(FILETIME f) {
    return ((uint64_t)f.dwHighDateTime << 32) | f.dwLowDateTime;
}
static inline FILETIME u64_to_ft(uint64_t v) {
    FILETIME f; f.dwLowDateTime = (DWORD)v; f.dwHighDateTime = (DWORD)(v >> 32);
    return f;
}
#define FILETIME_EPOCH 116444736000000000ULL

// SYSTEMTIME
struct SYSTEMTIME {
    WORD wYear, wMonth, wDayOfWeek, wDay;
    WORD wHour, wMinute, wSecond, wMilliseconds;
};

// LARGE_INTEGER
union LARGE_INTEGER {
    struct { DWORD LowPart; LONG HighPart; };
    LONGLONG QuadPart;
};

// SECURITY_ATTRIBUTES
struct SECURITY_ATTRIBUTES { DWORD nLength; LPVOID lpSecurityDescriptor; BOOL bInheritHandle; };

// CRITICAL_SECTION — opaque 40-byte block (pthread_mutex_t overlaid in first 24 bytes)
struct CRITICAL_SECTION { uint8_t opaque[40]; };

// WIN32_FIND_DATAA (320 bytes on Linux x86-64)
struct WIN32_FIND_DATAA {
    DWORD    dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD    nFileSizeHigh;
    DWORD    nFileSizeLow;
    DWORD    dwReserved0;
    DWORD    dwReserved1;
    char     cFileName[260];
    char     cAlternateFileName[14];
};

// WIN32_FIND_DATAW — same layout, wide filename
struct WIN32_FIND_DATAW {
    DWORD    dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD    nFileSizeHigh;
    DWORD    nFileSizeLow;
    DWORD    dwReserved0;
    DWORD    dwReserved1;
    uint16_t cFileName[260];
    uint16_t cAlternateFileName[14];
};

// STARTUPINFOA
struct STARTUPINFOA {
    DWORD   cb;
    LPSTR   lpReserved;
    LPSTR   lpDesktop;
    LPSTR   lpTitle;
    DWORD   dwX, dwY, dwXSize, dwYSize;
    DWORD   dwXCountChars, dwYCountChars;
    DWORD   dwFillAttribute;
    DWORD   dwFlags;
    WORD    wShowWindow;
    WORD    cbReserved2;
    BYTE*   lpReserved2;
    HANDLE  hStdInput, hStdOutput, hStdError;
};
#define STARTF_USESTDHANDLES 0x100

// STARTUPINFOW (same layout, wchar_t* fields)
struct STARTUPINFOW {
    DWORD    cb;
    LPWSTR   lpReserved;
    LPWSTR   lpDesktop;
    LPWSTR   lpTitle;
    DWORD    dwX, dwY, dwXSize, dwYSize;
    DWORD    dwXCountChars, dwYCountChars;
    DWORD    dwFillAttribute;
    DWORD    dwFlags;
    WORD     wShowWindow;
    WORD     cbReserved2;
    BYTE*    lpReserved2;
    HANDLE   hStdInput, hStdOutput, hStdError;
};

// CPINFO
typedef unsigned int UINT;
struct CPINFO { UINT MaxCharSize; BYTE DefaultChar[2]; BYTE LeadByte[12]; };

// Error codes
#define ERROR_SUCCESS            0
#define ERROR_FILE_NOT_FOUND     2
#define ERROR_PATH_NOT_FOUND     3
#define ERROR_TOO_MANY_OPEN_FILES 4
#define ERROR_ACCESS_DENIED      5
#define ERROR_INVALID_HANDLE     6
#define ERROR_OUTOFMEMORY        8
#define ERROR_INVALID_PARAMETER  87
#define ERROR_CALL_NOT_IMPLEMENTED 120
#define ERROR_INVALID_FLAGS      1004
#define ERROR_NO_MORE_FILES      18

// File creation dispositions
#define CREATE_NEW        1
#define CREATE_ALWAYS     2
#define OPEN_EXISTING     3
#define OPEN_ALWAYS       4
#define TRUNCATE_EXISTING 5

// File access
#define GENERIC_READ    0x80000000u
#define GENERIC_WRITE   0x40000000u

// File type
#define FILE_TYPE_UNKNOWN 0
#define FILE_TYPE_DISK    1
#define FILE_TYPE_CHAR    2
#define FILE_TYPE_PIPE    3

// File pointer methods
#define FILE_BEGIN   0
#define FILE_CURRENT 1
#define FILE_END     2

// File attributes
#define FILE_ATTRIBUTE_READONLY  0x1
#define FILE_ATTRIBUTE_HIDDEN    0x2
#define FILE_ATTRIBUTE_SYSTEM    0x4
#define FILE_ATTRIBUTE_DIRECTORY 0x10
#define FILE_ATTRIBUTE_ARCHIVE   0x20
#define FILE_ATTRIBUTE_NORMAL    0x80

// Standard handles
#define STD_INPUT_HANDLE  ((DWORD)-10)
#define STD_OUTPUT_HANDLE ((DWORD)-11)
#define STD_ERROR_HANDLE  ((DWORD)-12)

// Console mode flags
#define ENABLE_PROCESSED_INPUT  0x0001
#define ENABLE_LINE_INPUT       0x0002
#define ENABLE_ECHO_INPUT       0x0004
#define ENABLE_PROCESSED_OUTPUT 0x0001
#define ENABLE_WRAP_AT_EOL_OUTPUT 0x0002

// Heap flags
#define HEAP_ZERO_MEMORY   0x8
#define HEAP_NO_SERIALIZE  0x1

// Memory allocation types
#define MEM_COMMIT   0x1000
#define MEM_RESERVE  0x2000
#define MEM_RELEASE  0x8000
#define MEM_DECOMMIT 0x4000

// Page protection
#define PAGE_NOACCESS          0x01
#define PAGE_READONLY          0x02
#define PAGE_READWRITE         0x04
#define PAGE_EXECUTE           0x10
#define PAGE_EXECUTE_READ      0x20
#define PAGE_EXECUTE_READWRITE 0x40

// Exception handling
#define EXCEPTION_EXECUTE_HANDLER  1
#define EXCEPTION_CONTINUE_SEARCH  0
#define EXCEPTION_NONCONTINUABLE   1

// IsProcessorFeature
#define PF_FLOATING_POINT_EMULATED          0
#define PF_COMPARE_EXCHANGE_DOUBLE          2
#define PF_MMX_INSTRUCTIONS_AVAILABLE       3
#define PF_XMMI_INSTRUCTIONS_AVAILABLE      6
#define PF_RDTSC_INSTRUCTION_AVAILABLE      8
#define PF_3DNOW_INSTRUCTIONS_AVAILABLE     7

// LoadLibrary flags
#define LOAD_LIBRARY_AS_DATAFILE  2

// String mapping / comparison flags
#define LCMAP_LOWERCASE   0x00000100
#define LCMAP_UPPERCASE   0x00000200
#define NORM_IGNORECASE   0x00000001
#define CSTR_LESS_THAN    1
#define CSTR_EQUAL        2
#define CSTR_GREATER_THAN 3

// GetStringTypeW/A character category flags (CT_CTYPE1)
#define CT_CTYPE1         1
#define CT_CTYPE2         2
#define CT_CTYPE3         4
#define C1_UPPER          0x0001
#define C1_LOWER          0x0002
#define C1_DIGIT          0x0004
#define C1_SPACE          0x0008
#define C1_PUNCT          0x0010
#define C1_CNTRL          0x0020
#define C1_BLANK          0x0040
#define C1_XDIGIT         0x0080
#define C1_ALPHA          0x0100
