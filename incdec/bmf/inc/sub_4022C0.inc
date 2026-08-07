// sub_4022C0 @ 0x004022C0 — __usercall
// Extracted from BMF.c:1779-1910 by extract.py per incdec.md.

typedef int t_sub_4022C0_dwLowDateTime;
static t_sub_4022C0_dwLowDateTime& __sub_4022C0_dwLowDateTime = *(t_sub_4022C0_dwLowDateTime*)0x00442BB0;
#define dwLowDateTime __sub_4022C0_dwLowDateTime

#ifndef __PE_DECL___exit_402E40
#define __PE_DECL___exit_402E40
typedef __attribute__((stdcall)) void t_exit_402E40(int Code, char ArgList);
static t_exit_402E40& __exit_402E40 = *(t_exit_402E40*)0x00402E40;
#endif
#define exit_402E40 __exit_402E40

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___CloseHandle
#define __PE_DECL___CloseHandle
typedef __attribute__((stdcall)) int (*pfn_CloseHandle)(void *);
static pfn_CloseHandle& CloseHandle = *(pfn_CloseHandle*)0x00438014;   // IAT slot
#endif
#ifndef __PE_DECL___CreateFileA
#define __PE_DECL___CreateFileA
typedef __attribute__((stdcall)) void * (*pfn_CreateFileA)(const char *, unsigned int, unsigned int, void *, unsigned int, unsigned int, void *);
static pfn_CreateFileA& CreateFileA = *(pfn_CreateFileA*)0x0043800C;   // IAT slot
#endif
#ifndef __PE_DECL___DosDateTimeToFileTime
#define __PE_DECL___DosDateTimeToFileTime
typedef __attribute__((stdcall)) int (*pfn_DosDateTimeToFileTime)(unsigned short, unsigned short, void *);
static pfn_DosDateTimeToFileTime& DosDateTimeToFileTime = *(pfn_DosDateTimeToFileTime*)0x00438008;   // IAT slot
#endif
#ifndef __PE_DECL___SetFileAttributesA
#define __PE_DECL___SetFileAttributesA
typedef __attribute__((stdcall)) int (*pfn_SetFileAttributesA)(const char *, unsigned int);
static pfn_SetFileAttributesA& SetFileAttributesA = *(pfn_SetFileAttributesA*)0x00438018;   // IAT slot
#endif
#ifndef __PE_DECL___SetFileTime
#define __PE_DECL___SetFileTime
typedef __attribute__((stdcall)) int (*pfn_SetFileTime)(void *, const void *, const void *, const void *);
static pfn_SetFileTime& SetFileTime = *(pfn_SetFileTime*)0x00438010;   // IAT slot
#endif
#ifndef __PE_DECL____access
#define __PE_DECL____access
typedef int t__access(const char *, int);   // __access
static t__access& ___access = *(t__access*)0x004314F0;
#endif
#define _access ___access
#ifndef __PE_DECL___fclose
#define __PE_DECL___fclose
typedef int t_fclose(FILE1 *);   // _fclose
static t_fclose& __fclose = *(t_fclose*)0x0042CEB4;
#endif
#define fclose __fclose
#ifndef __PE_DECL___fputc
#define __PE_DECL___fputc
typedef int t_fputc(int, FILE1 *);   // _fputc
static t_fputc& __fputc = *(t_fputc*)0x0042D0A9;
#endif
#define fputc __fputc
#ifndef __PE_DECL___fwrite
#define __PE_DECL___fwrite
typedef unsigned int t_fwrite(const void *, unsigned int, unsigned int, FILE1 *);   // _fwrite
static t_fwrite& __fwrite = *(t_fwrite*)0x0042CF9F;
#endif
#define fwrite __fwrite
#ifndef __PE_DECL___printf
#define __PE_DECL___printf
typedef int t_printf(const char *, ...);   // _printf
static t_printf& __printf = *(t_printf*)0x0042CBDB;
#endif
#define printf __printf
#define FILE FILE1

PROBE_DECL(__sub_4022C0)
extern "C" __attribute__((visibility("hidden"))) int __sub_4022C0(int p_i)
{
  PROBE_HIT(__sub_4022C0);
  unsigned __int16 *dwLowDateTime; // esi
  const char *lpFileName_1; // ebp
  DWORD dwHighDateTime_1; // ebx
  int v5; // ecx
  int v6; // ebp
  int v7; // edx
  size_t ElementCount_2; // eax
  char *Buffer_2; // ebx
  size_t ElementCount_1; // edx
  const CHAR *lpFileName_2; // ebp
  bool v12; // cc
  DWORD v13; // ecx
  size_t dwHighDateTime; // edx
  char *Buffer_1; // ebp
  int v16; // esi
  size_t dwHighDateTime_2; // eax
  signed int i; // ebx
  HANDLE FileA; // edi
  int n13; // eax
  int C; // eax
  struct _FILETIME FileTime; // [esp+0h] [ebp-34h] BYREF
  LPCSTR lpFileName; // [esp+8h] [ebp-2Ch]
  int v24; // [esp+Ch] [ebp-28h]
  void *Buffer; // [esp+10h] [ebp-24h]
  FILE *Stream_v; // [esp+14h] [ebp-20h]
  char *dwLowDateTime_1; // [esp+18h] [ebp-1Ch]
  size_t ElementCount; // [esp+1Ch] [ebp-18h]
  int p_i_1; // [esp+20h] [ebp-14h]

  dwLowDateTime = (unsigned __int16 *)::dwLowDateTime;
  lpFileName_1 = (char *)::dwLowDateTime + 32;
  if ( !_access((const char *)::dwLowDateTime + 32, 0) )
  {
    printf("\n%s already exists: (O)verwrite, (S)kip, (Q)uit?", lpFileName_1);
    while ( 1 )
    {
      C = _getch();
      n13 = toupper(C);
      if ( n13 == 13 || n13 == 79 )
        break;
      if ( n13 == 27 || n13 == 81 )
        exit_402E40(8, FileTime.dwLowDateTime);
      if ( n13 == 83 )
        return n13;
    }
    SetFileAttributesA(lpFileName_1, FILE_READ_ATTRIBUTES);
  }
  Stream_v = fopen(lpFileName_1, "wb");
  if ( !Stream_v
    || fwrite((char *)::dwLowDateTime + dwLowDateTime[4] + 32, *((_DWORD *)dwLowDateTime + 5), 1u, Stream_v) != 1 )
  {
    exit_402E40(5, (char)lpFileName_1);
  }
  dwHighDateTime_1 = *(unsigned __int16 *)(p_i + 4);
  v5 = dwLowDateTime[5];
  lpFileName = lpFileName_1;
  v6 = *((_DWORD *)dwLowDateTime + 5) + dwLowDateTime[4];
  FileTime.dwHighDateTime = dwHighDateTime_1;
  v7 = v6 + *((_DWORD *)dwLowDateTime + 6) + 24;
  ElementCount = *((_DWORD *)dwLowDateTime + 6);
  v24 = v7;
  ElementCount_2 = v5 * ((int)(dwHighDateTime_1 + v5 - 1) / v5) - dwHighDateTime_1;
  FileTime.dwLowDateTime = *(unsigned __int16 *)(p_i + 2);
  dwLowDateTime_1 = (char *)::dwLowDateTime;
  Buffer_2 = (char *)::dwLowDateTime + v7 - ElementCount_2 + 8;
  if ( ((v7 + ElementCount_2 * FileTime.dwLowDateTime + 3) & 0xFFFFFFFC) != *((_DWORD *)::dwLowDateTime + 1) )
    Buffer_2 = nullptr;
  ElementCount_1 = ElementCount;
  Buffer = (void *)(p_i + 16);
  lpFileName_2 = lpFileName;
  if ( ElementCount_2 )
  {
    v12 = (signed int)FileTime.dwLowDateTime < 1;
    v13 = --FileTime.dwLowDateTime;
    if ( !v12 )
    {
      dwHighDateTime = FileTime.dwHighDateTime;
      ElementCount = ElementCount_2;
      Buffer_1 = (char *)Buffer;
      FileTime.dwLowDateTime = (DWORD)dwLowDateTime;
      v16 = v13;
      p_i_1 = p_i;
      do
      {
        dwHighDateTime_2 = fwrite(Buffer_1, 1u, dwHighDateTime, Stream_v);
        dwHighDateTime = *(unsigned __int16 *)(p_i_1 + 4);
        if ( dwHighDateTime_2 != dwHighDateTime )
          exit_402E40(5, (char)lpFileName);
        if ( Buffer_2 )
        {
          Buffer_2 += ElementCount;
          fwrite(Buffer_2, 1u, ElementCount, Stream_v);
          dwHighDateTime = *(unsigned __int16 *)(p_i_1 + 4);
        }
        else if ( (int)ElementCount > 0 )
        {
          Buffer = Buffer_1;
          FileTime.dwHighDateTime = 0;
          for ( i = 0; i < (int)ElementCount; ++i )
            fputc(0, Stream_v);
          Buffer_1 = (char *)Buffer;
          Buffer_2 = (char *)FileTime.dwHighDateTime;
          dwHighDateTime = *(unsigned __int16 *)(p_i_1 + 4);
        }
        Buffer_1 += dwHighDateTime;
        --v16;
      }
      while ( v16 >= 0 );
      lpFileName_2 = lpFileName;
      dwLowDateTime = (unsigned __int16 *)FileTime.dwLowDateTime;
      ElementCount_1 = *(_DWORD *)(FileTime.dwLowDateTime + 24);
      dwLowDateTime_1 = (char *)::dwLowDateTime;
    }
  }
  else
  {
    if ( fwrite(Buffer, 1u, *(_DWORD *)(p_i + 12), Stream_v) != *(_DWORD *)(p_i + 12) )
      exit_402E40(5, (char)lpFileName);
    ElementCount_1 = *((_DWORD *)dwLowDateTime + 6);
    dwLowDateTime_1 = (char *)::dwLowDateTime;
  }
  if ( fwrite(&dwLowDateTime_1[v24 - ElementCount_1 + 8], ElementCount_1, 1u, Stream_v) != 1 )
    exit_402E40(5, (char)lpFileName_2);
  fclose(Stream_v);
  DosDateTimeToFileTime(dwLowDateTime[7], dwLowDateTime[6], &FileTime);
  FileA = CreateFileA(lpFileName_2, GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
  SetFileTime(FileA, &FileTime, nullptr, &FileTime);
  CloseHandle(FileA);
  return SetFileAttributesA(lpFileName_2, *((_DWORD *)dwLowDateTime + 4));
}

// __usercall thunk for sub_4022C0 @ 0x004022C0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_4022C0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $28, %esp\n"
    "mov %eax, 12(%esp)\n"
    "push 12(%esp)\n"
    "call __sub_4022C0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef FILE
#undef _access
#undef fclose
#undef fputc
#undef fwrite
#undef printf
#undef dwLowDateTime
#undef exit_402E40
