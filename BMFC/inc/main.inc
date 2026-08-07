// main @ 0x00401000 — __cdecl
// Extracted from BMF.cpp:984-1160 by extract.py per incdec.md.

typedef char t_main_Destination_;
static t_main_Destination_& __main_Destination_ = *(t_main_Destination_*)(blob1 + 0x00442960 - BMF_BLOB_BASE);
typedef size_t t_main_ElementCount;
static t_main_ElementCount& __main_ElementCount = *(t_main_ElementCount*)(blob1 + 0x00441054 - BMF_BLOB_BASE);
typedef WIN32_FIND_DATAA t_main_FindFileData;
static t_main_FindFileData& __main_FindFileData = *(t_main_FindFileData*)(blob1 + 0x00442A60 - BMF_BLOB_BASE);
typedef int t_main_bmp_;
static t_main_bmp_& __main_bmp_ = *(t_main_bmp_*)(blob1 + 0x00441040 - BMF_BLOB_BASE);
typedef int t_main_dword_441058;
static t_main_dword_441058& __main_dword_441058 = *(t_main_dword_441058*)(blob1 + 0x00441058 - BMF_BLOB_BASE);
typedef int t_main_dword_44105C;
static t_main_dword_44105C& __main_dword_44105C = *(t_main_dword_44105C*)(blob1 + 0x0044105C - BMF_BLOB_BASE);
typedef int t_main_dword_44108C;
static t_main_dword_44108C& __main_dword_44108C = *(t_main_dword_44108C*)(blob1 + 0x0044108C - BMF_BLOB_BASE);
typedef int t_main_dword_441090;
static t_main_dword_441090& __main_dword_441090 = *(t_main_dword_441090*)(blob1 + 0x00441090 - BMF_BLOB_BASE);
typedef int t_main_dword_441098;
static t_main_dword_441098& __main_dword_441098 = *(t_main_dword_441098*)(blob1 + 0x00441098 - BMF_BLOB_BASE);
typedef int t_main_dword_4410A4[6];
static t_main_dword_4410A4& __main_dword_4410A4 = *(t_main_dword_4410A4*)(blob1 + 0x004410A4 - BMF_BLOB_BASE);
typedef int t_main_dword_442BA0;
static t_main_dword_442BA0& __main_dword_442BA0 = *(t_main_dword_442BA0*)(blob1 + 0x00442BA0 - BMF_BLOB_BASE);
typedef int t_main_dword_442BA8;
static t_main_dword_442BA8& __main_dword_442BA8 = *(t_main_dword_442BA8*)(blob1 + 0x00442BA8 - BMF_BLOB_BASE);
typedef int t_main_dword_442BAC;
static t_main_dword_442BAC& __main_dword_442BAC = *(t_main_dword_442BAC*)(blob1 + 0x00442BAC - BMF_BLOB_BASE);
typedef int t_main_n0xFFFF;
static t_main_n0xFFFF& __main_n0xFFFF = *(t_main_n0xFFFF*)(blob1 + 0x00441064 - BMF_BLOB_BASE);
typedef int t_main_n2_4;
static t_main_n2_4& __main_n2_4 = *(t_main_n2_4*)(blob1 + 0x00441094 - BMF_BLOB_BASE);
typedef int t_main_n2_5;
static t_main_n2_5& __main_n2_5 = *(t_main_n2_5*)(blob1 + 0x00442BA4 - BMF_BLOB_BASE);
typedef int t_main_n4_6;
static t_main_n4_6& __main_n4_6 = *(t_main_n4_6*)(blob1 + 0x00441060 - BMF_BLOB_BASE);
typedef int t_main_n7_0;
static t_main_n7_0& __main_n7_0 = *(t_main_n7_0*)(blob1 + 0x0044109C - BMF_BLOB_BASE);
typedef int t_main_n7_1;
static t_main_n7_1& __main_n7_1 = *(t_main_n7_1*)(blob1 + 0x004410A0 - BMF_BLOB_BASE);
typedef void * t_main_off_44104C[2];
static t_main_off_44104C& __main_off_44104C = *(t_main_off_44104C*)(blob1 + 0x0044104C - BMF_BLOB_BASE);

#ifndef __PE_DECL___sub_402E30
#define __PE_DECL___sub_402E30
// No decompiled body — IDA's call analysis failed on it. Only its address is used.
typedef void t_sub_402E30();
static t_sub_402E30& __sub_402E30 = *(t_sub_402E30*)0x00402E30;
#endif
#define sub_402E30 __sub_402E30
#define exit_402E40 __exit_402E40
static inline void __fwd_main_sub_4015C0(const __m128 &a0, const __m128 &a1, void *a2, void *a3) { __sub_4015C0(a0, a1, (const char *)a2, (const char *)a3); }
#define sub_4015C0 __fwd_main_sub_4015C0
#define sub_402BD0 __sub_402BD0
#define sub_427F40 __sub_427F40
#define sub_428050 __sub_428050
static inline size_t __fwd_main_sub_4280B0(int a0, int a1, int a2, void *a3, signed int a4) { return __sub_4280B0(a0, a1, a2, (char *)a3, a4); }
#define sub_4280B0 __fwd_main_sub_4280B0
static inline int __fwd_main_sub_4284E0(int a0, void *a1, int a2) { return __sub_4284E0(a0, (char *)a1, a2); }
#define sub_4284E0 __fwd_main_sub_4284E0
#define sub_42CBB0 __sub_42CBB0
#define sub_4346D0 __sub_4346D0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___FindFirstFileA
#define __PE_DECL___FindFirstFileA
typedef __attribute__((stdcall)) void * (*pfn_FindFirstFileA)(const char *, void *);
static pfn_FindFirstFileA& FindFirstFileA = *(pfn_FindFirstFileA*)(blob1 + 0x00438000 - BMF_BLOB_BASE);   // IAT slot
#endif
#ifndef __PE_DECL___FindNextFileA
#define __PE_DECL___FindNextFileA
typedef __attribute__((stdcall)) int (*pfn_FindNextFileA)(void *, void *);
static pfn_FindNextFileA& FindNextFileA = *(pfn_FindNextFileA*)(blob1 + 0x00438004 - BMF_BLOB_BASE);   // IAT slot
#endif
#ifndef __PE_DECL____strcmpi
#define __PE_DECL____strcmpi
typedef int t__strcmpi(const char *, const char *);   // __strcmpi
static t__strcmpi& ___strcmpi = *(t__strcmpi*)0x00437870;
#endif
#define _strcmpi ___strcmpi
#ifndef __PE_DECL___printf
#define __PE_DECL___printf
typedef int t_printf(const char *, ...);   // _printf
static t_printf& __printf = *(t_printf*)0x0042CBDB;
#endif
#define printf __printf
#define FILE FILE1

PROBE_DECL(__main)
BMF_REALIGN BMF_SSE int __main(int argc, const char **argv, const char **envp)
{
  alignas(16) unsigned char __hexrays_frame[400];   // original frame, ebp-0x180..ebp+0x0
  char (&String1)[4] = *(char (*)[4])(__hexrays_frame + 0);
  char (&Str)[256] = *(char (*)[256])(__hexrays_frame + 64);
  int &n45 = *(int *)(__hexrays_frame + 320);
  PROBE_HIT(__main);
  __m128 v3; // xmm1
  __m128 v4; // xmm3
  int argc_1; // ebx
  const char *ArgList; // edi
  int n45_1; // eax
  HANDLE FirstFileA; // esi
  __m128i *v10; // edx
  int v11; // ecx
  int v13; // eax
  int n2; // eax
  int n9; // edx
  int n15; // eax

  sub_4346D0(3);
  *(_DWORD *)String1 = _mm_getcsr() | 0x8000;
  _mm_setcsr(*(unsigned int *)String1);
  sub_42CBB0((int)sub_402E30);
  printf("BMF lossless image compressor, v.2.01 (C) 1998-1999, 2009 by Dmitry Shkarin\n");
  __main_dword_4410A4[0] = 0;
  __main_dword_44108C = sub_427F40((int)"BMF_Options", (int)"UseFilters", __main_dword_44108C);
  __main_n7_0 = sub_428050((int)"BMF_Options", (int)"FSQ", __main_n7_0);
  __main_dword_441090 = sub_427F40((int)"BMF_Options", (int)"SleepyWork", __main_dword_441090);
  __main_n7_1 = sub_428050((int)"BMF_Options", (int)"MaxError", __main_n7_1);
  __main_n2_4 = sub_428050((int)"BMF_Options", (int)"TemplateUsage", __main_n2_4);
  argc_1 = 1;
  __main_dword_4410A4[0] = sub_428050((int)"BMF_Options", (int)"Template", __main_dword_4410A4[0]);
  __main_dword_441098 = sub_427F40((int)"BMF_Options", (int)"NotPack", __main_dword_441098 == 0) == 0;
  __main_dword_442BA0 = sub_427F40((int)"BMF_Options", (int)"DeleteFile", __main_dword_442BA0);
  sub_4280B0((int)"BMF_Options", (int)"OutFileType", *(&__main_bmp_ + __main_n2_5), String1, 64);// "bmp"
  if ( !_strcmpi(String1, "bmp") )
    __main_n2_5 = 0;
  if ( !_strcmpi(String1, "tga") )
    __main_n2_5 = 1;
  if ( !_strcmpi(String1, "pnm") )
    __main_n2_5 = 2;
  sub_4280B0((int)"BMF_Options", (int)"OutFName", (int)&__main_Destination_, &__main_Destination_, 256);
  qmemcpy(String1, "-r", 2);
  sub_4280B0((int)"BMF_Options", (int)"RawFileInfo", (int)"-", &String1[2], 62);
  sub_402BD0((int)&String1[1]);
  if ( argc < 2 )
    exit_402E40(0, (const char *)__main_off_44104C[__main_dword_44108C], __main_n7_0, (const char *)__main_off_44104C[__main_dword_441090], __main_n7_1, __main_n2_4, (const char *)__main_off_44104C[__main_dword_441098 == 0], (const char *)*(&__main_bmp_ + __main_n2_5), (const char *)__main_off_44104C[__main_dword_442BA0], __main_Destination_ ? &__main_Destination_ : "none", (const char *)__main_off_44104C[__main_dword_442BAC], __main_ElementCount, __main_dword_441058, __main_dword_44105C, __main_n4_6, __main_n0xFFFF, (const char *)__main_off_44104C[__main_dword_442BA8]);// "disabled"
  do
  {
    ArgList = argv[argc_1];
    n45_1 = *ArgList;
    if ( n45_1 == 45 || n45_1 == 47 )
    {
      v10 = (__m128i *)((unsigned int)(ArgList + 1) & 0xFFFFFFF0);
      v11 = ((_BYTE)ArgList + 1) & 0xF;
      if ( !_BitScanForward(
              (unsigned int *)&v13,
              (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, *v10)) >> (v11 & 31)) )
        v13 = __intel_sse2_strlen(v11, &v10->m128i_i8[v11]);
      n45 = ArgList[v13];
      if ( _strcmpi(ArgList + 1, "bmp") )
      {
        if ( _strcmpi(ArgList + 1, "tga") )
        {
          if ( _strcmpi(ArgList + 1, "pnm") )
          {
            switch ( toupper(ArgList[1]) )
            {
              case 'D':
                __main_dword_442BA0 = n45 != 45;
                break;
              case 'E':
                n15 = atoi(ArgList + 2);
                if ( n15 > 15 )
                  n15 = 15;
                if ( n15 < 0 )
                  n15 = 0;
                __main_n7_1 = n15;
                break;
              case 'F':
                __main_dword_44108C = n45 != 45;
                break;
              case 'N':
                __main_dword_441098 = n45 == 45;
                break;
              case 'O':
                strcpy(&__main_Destination_, ArgList + 2);
                break;
              case 'Q':
                n9 = n45 - 48;
                if ( n45 - 48 > 9 )
                  n9 = 9;
                if ( n9 < 0 )
                  n9 = 0;
                __main_n7_0 = n9;
                break;
              case 'R':
                sub_402BD0((int)(ArgList + 1));
                break;
              case 'S':
                __main_dword_441090 = n45 != 45;
                break;
              case 'T':
                n2 = atoi(ArgList + 2);
                if ( n2 > 2 )
                  n2 = 2;
                if ( n2 < 0 )
                  n2 = 0;
                __main_n2_4 = n2;
                break;
              default:
                exit_402E40(2, ArgList);
            }
          }
          else
          {
            __main_n2_5 = 2;
          }
        }
        else
        {
          __main_n2_5 = 1;
        }
      }
      else
      {
        __main_n2_5 = 0;
      }
    }
    else
    {
      if ( bmf_path_sep(ArgList) )
      {
        strcpy(Str, ArgList);
        bmf_path_sep(Str)[1] = 0;
        ArgList = argv[argc_1];
      }
      else
      {
        Str[0] = 0;
      }
      FirstFileA = FindFirstFileA(ArgList, &__main_FindFileData);
      if ( FirstFileA == (HANDLE)-1 )
        exit_402E40(1, argv[argc_1]);
      do
      {
        if ( (__main_FindFileData.dwFileAttributes & FILE_WRITE_EA) == 0 )
        {
          sub_4015C0(v3, v4, Str, __main_FindFileData.cFileName);
          if ( __main_n2_4 == 1 )
            sub_4284E0((int)"BMF_Options", "Template", __main_dword_4410A4[0]);
        }
      }
      while ( FindNextFileA(FirstFileA, &__main_FindFileData) );
    }
    ++argc_1;
  }
  while ( argc_1 < argc );
  return 0;
}

#undef FILE
#undef _strcmpi
#undef printf
#undef exit_402E40
#undef sub_4015C0
#undef sub_402BD0
#undef sub_402E30
#undef sub_427F40
#undef sub_428050
#undef sub_4280B0
#undef sub_4284E0
#undef sub_42CBB0
#undef sub_4346D0
