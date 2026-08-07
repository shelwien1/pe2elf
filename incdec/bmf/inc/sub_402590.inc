// sub_402590 @ 0x00402590 — __cdecl
// Extracted from BMF.c:1913-2064 by extract.py per incdec.md.

typedef size_t t_sub_402590_ElementCount;
static t_sub_402590_ElementCount& __sub_402590_ElementCount = *(t_sub_402590_ElementCount*)0x00441054;
typedef WIN32_FIND_DATAA t_sub_402590_FindFileData;
static t_sub_402590_FindFileData& __sub_402590_FindFileData = *(t_sub_402590_FindFileData*)0x00442A60;
typedef int t_sub_402590_dwLowDateTime;
static t_sub_402590_dwLowDateTime& __sub_402590_dwLowDateTime = *(t_sub_402590_dwLowDateTime*)0x00442BB0;
typedef int t_sub_402590_dword_441058;
static t_sub_402590_dword_441058& __sub_402590_dword_441058 = *(t_sub_402590_dword_441058*)0x00441058;
typedef int t_sub_402590_dword_44105C;
static t_sub_402590_dword_44105C& __sub_402590_dword_44105C = *(t_sub_402590_dword_44105C*)0x0044105C;
typedef int t_sub_402590_dword_442BA8;
static t_sub_402590_dword_442BA8& __sub_402590_dword_442BA8 = *(t_sub_402590_dword_442BA8*)0x00442BA8;
typedef int t_sub_402590_n0xFFFF;
static t_sub_402590_n0xFFFF& __sub_402590_n0xFFFF = *(t_sub_402590_n0xFFFF*)0x00441064;
typedef int t_sub_402590_n4_6;
static t_sub_402590_n4_6& __sub_402590_n4_6 = *(t_sub_402590_n4_6*)0x00441060;

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980
#define sub_402EB0 __sub_402EB0
#define sub_42B830 __sub_42B830

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___FileTimeToDosDateTime
#define __PE_DECL___FileTimeToDosDateTime
typedef __attribute__((stdcall)) int (*pfn_FileTimeToDosDateTime)(const void *, unsigned short *, unsigned short *);
static pfn_FileTimeToDosDateTime& FileTimeToDosDateTime = *(pfn_FileTimeToDosDateTime*)0x0043801C;   // IAT slot
#endif
#ifndef __PE_DECL_____intel_sse2_strlen
#define __PE_DECL_____intel_sse2_strlen
typedef __attribute__((fastcall)) int t___intel_sse2_strlen(unsigned int, const void *);   // ___intel_sse2_strlen
static t___intel_sse2_strlen& ____intel_sse2_strlen = *(t___intel_sse2_strlen*)0x00434930;
#endif
#define __intel_sse2_strlen ____intel_sse2_strlen
#ifndef __PE_DECL____filelength
#define __PE_DECL____filelength
typedef long t__filelength(int);   // __filelength
static t__filelength& ___filelength = *(t__filelength*)0x00437A95;
#endif
#define _filelength ___filelength
#ifndef __PE_DECL____fileno
#define __PE_DECL____fileno
typedef int t__fileno(FILE1 *);   // __fileno
static t__fileno& ___fileno = *(t__fileno*)0x00437A8D;
#endif
#define _fileno ___fileno
#ifndef __PE_DECL___fclose
#define __PE_DECL___fclose
typedef int t_fclose(FILE1 *);   // _fclose
static t_fclose& __fclose = *(t_fclose*)0x0042CEB4;
#endif
#define fclose __fclose
#ifndef __PE_DECL___fopen
#define __PE_DECL___fopen
typedef FILE1 * t_fopen(const char *, const char *);   // _fopen
static t_fopen& __fopen = *(t_fopen*)0x0042CDB9;
#endif
#define fopen __fopen
#ifndef __PE_DECL___fread
#define __PE_DECL___fread
typedef unsigned int t_fread(void *, unsigned int, unsigned int, FILE1 *);   // _fread
static t_fread& __fread = *(t_fread*)0x0042CDCC;
#endif
#define fread __fread
#ifndef __PE_DECL___fseek
#define __PE_DECL___fseek
typedef int t_fseek(FILE1 *, long, int);   // _fseek
static t_fseek& __fseek = *(t_fseek*)0x0042D0DD;
#endif
#define fseek __fseek
#define FILE FILE1

PROBE_DECL(__sub_402590)
__attribute__((force_align_arg_pointer)) BMF_SSE int *__sub_402590(char *FileName)
{
  alignas(16) unsigned char __hexrays_frame[56];   // original frame, ebp-0x28..ebp+0x0
  char * &Str = *(char * *)(__hexrays_frame + 0);
  char * &Stra = *(char * *)(__hexrays_frame + 0);
  size_t &__sub_402590_ElementCount = *(size_t *)(__hexrays_frame + 4);
  char * &ElementCounta = *(char * *)(__hexrays_frame + 4);
  size_t &Offset = *(size_t *)(__hexrays_frame + 8);
  char * &Offseta = *(char * *)(__hexrays_frame + 8);
  WORD * &Offsetb = *(WORD * *)(__hexrays_frame + 8);
  size_t &Size = *(size_t *)(__hexrays_frame + 12);
  signed int &ElementCount_4 = *(signed int *)(__hexrays_frame + 16);
  int &v34 = *(int *)(__hexrays_frame + 20);
  PROBE_HIT(__sub_402590);
  Stream *Stream_v; // ebp
  int *v2; // ebx
  int FileHandle; // eax
  int v4; // eax
  int v5; // esi
  int v6; // ecx
  size_t ElementCount_2; // esi
  int v8; // edi
  int v9; // ecx
  int v10; // edi
  size_t ElementCount_3; // edx
  char *Buffer; // esi
  char *i; // eax
  char *v15; // eax
  char *FileName_1; // edx
  char FileName_2; // cl
  __m128i *v18; // edx
  int v19; // ecx
  int Stra_1; // eax
  size_t ElementCount_1; // edx
  char *__sub_402590_dwLowDateTime; // eax
  char v24; // fps

  Stream_v = fopen(FileName, "rb");
  v2 = sub_42B830(__sub_402590_dword_441058, __sub_402590_dword_44105C, 8 * __sub_402590_n4_6, 0, 1);
  FileHandle = _fileno(Stream_v);
  v4 = _filelength(FileHandle);
  v5 = *((unsigned __int16 *)v2 + 2);
  v6 = (__sub_402590_n0xFFFF + v5 - 1) / __sub_402590_n0xFFFF * __sub_402590_n0xFFFF;
  Offset = ::__sub_402590_ElementCount;
  ElementCount_2 = v6 - v5;
  v8 = ElementCount_2 * __sub_402590_dword_44105C;
  ElementCount_4 = v4 - __sub_402590_dword_44105C * v6 - ::__sub_402590_ElementCount;
  if ( ElementCount_4 < 0 )
    return nullptr;
  if ( __sub_402590_n4_6 == 1 )
  {
    *((_BYTE *)v2 + 10) |= 0x40u;
    Offset = ::__sub_402590_ElementCount;
  }
  if ( __sub_402590_dword_442BA8 )
  {
    v15 = strrchr(FileName, 92);
    FileName_1 = v15 + 1;
    if ( !v15 )
      FileName_1 = FileName;
    ElementCounta = FileName_1;
    FileName_2 = (char)FileName_1;
    v18 = (__m128i *)((unsigned int)FileName_1 & 0xFFFFFFF0);
    v19 = FileName_2 & 0xF;
    if ( !_BitScanForward(
            (unsigned int *)&Stra_1,
            (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, *v18)) >> v19) )
      Stra_1 = __intel_sse2_strlen(v19, &v18->m128i_i8[v19]);
    Stra = (char *)Stra_1;
    Size = Stra_1 + 1;
    Offsetb = (WORD *)sub_402EB0(256, Offset + ElementCount_4 + v8 + Stra_1 + 25);
    ::__sub_402590_dwLowDateTime = Offsetb;
    Offsetb[4] = Size;
    Offsetb[5] = __sub_402590_n0xFFFF;
    FileTimeToDosDateTime(&__sub_402590_FindFileData.ftLastWriteTime, Offsetb + 7, Offsetb + 6);
    *((_DWORD *)Offsetb + 4) = __sub_402590_FindFileData.dwFileAttributes;
    ElementCount_1 = ::__sub_402590_ElementCount;
    __sub_402590_dwLowDateTime = (char *)::__sub_402590_dwLowDateTime;
    *((_DWORD *)Offsetb + 7) = 0;
    *((_DWORD *)Offsetb + 5) = ElementCount_1;
    *((_DWORD *)Offsetb + 6) = ElementCount_4;
    sub_434980(__sub_402590_dwLowDateTime + 32,ElementCounta,Size);
    fread(&Stra[(_DWORD)::__sub_402590_dwLowDateTime + 33], 1u, ::__sub_402590_ElementCount, Stream_v);
    Offseta = &Stra[(_DWORD)::__sub_402590_dwLowDateTime + ::__sub_402590_ElementCount + ElementCount_4 + 33];
  }
  else
  {
    fseek(Stream_v, Offset, 0);
    Offseta = nullptr;
    Size = 0;
  }
  if ( !ElementCount_2 )
  {
    if ( fread(v2 + 4, 1u, v2[3], Stream_v) == v2[3] )
    {
      v9 = __sub_402590_dword_442BA8;
      Str = nullptr;
      goto LABEL_17;
    }
    return nullptr;
  }
  v9 = __sub_402590_dword_442BA8;
  v10 = __sub_402590_dword_44105C - 1;
  Str = &Offseta[-ElementCount_2];
  if ( __sub_402590_dword_44105C - 1 >= 0 )
  {
    ElementCount_3 = *((unsigned __int16 *)v2 + 2);
    v34 = __sub_402590_dword_442BA8;
    __sub_402590_ElementCount = ElementCount_2;
    Buffer = (char *)(v2 + 4);
    while ( fread(Buffer, 1u, ElementCount_3, Stream_v) == *((unsigned __int16 *)v2 + 2) )
    {
      if ( v34 )
      {
        Str += __sub_402590_ElementCount;
        fread(Str, 1u, __sub_402590_ElementCount, Stream_v);
      }
      else
      {
        fseek(Stream_v, __sub_402590_ElementCount, 1);
      }
      ElementCount_3 = *((unsigned __int16 *)v2 + 2);
      Buffer += ElementCount_3;
      if ( --v10 < 0 )
      {
        v9 = v34;
        ElementCount_2 = __sub_402590_ElementCount;
        goto LABEL_17;
      }
    }
    return nullptr;
  }
LABEL_17:
  if ( v9 )
  {
    fread((char *)::__sub_402590_dwLowDateTime + ::__sub_402590_ElementCount + Size + 32, 1u, ElementCount_4, Stream_v);
    if ( ElementCount_2 )
    {
      for ( i = &Str[ElementCount_2 - 1]; i >= Offseta; --i )
      {
        if ( *i )
          break;
      }
      if ( i < Offseta )
        *((_DWORD *)::__sub_402590_dwLowDateTime + 1) = (ElementCount_4 + ::__sub_402590_ElementCount + Size + 27) & 0xFFFFFFFC;
    }
  }
  fclose(Stream_v);
  return v2;
}

#undef FILE
#undef __intel_sse2_strlen
#undef _filelength
#undef _fileno
#undef fclose
#undef fopen
#undef fread
#undef fseek
#undef sub_402EB0
#undef sub_42B830
#undef sub_434980
