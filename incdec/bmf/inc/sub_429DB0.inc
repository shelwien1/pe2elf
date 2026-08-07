// sub_429DB0 @ 0x00429DB0 — __cdecl
// Extracted from BMF.c:34379-34431 by extract.py per incdec.md.

typedef int t_sub_429DB0_argv;
static t_sub_429DB0_argv& __sub_429DB0_argv = *(t_sub_429DB0_argv*)0x00445954;


// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL_____intel_sse2_strlen
#define __PE_DECL_____intel_sse2_strlen
typedef __attribute__((fastcall)) int t___intel_sse2_strlen(unsigned int, const void *);   // ___intel_sse2_strlen
static t___intel_sse2_strlen& ____intel_sse2_strlen = *(t___intel_sse2_strlen*)0x00434930;
#endif
#define __intel_sse2_strlen ____intel_sse2_strlen
#define FILE FILE1

PROBE_DECL(__sub_429DB0)
BMF_SSE _BYTE *__sub_429DB0(_BYTE *OldFilename, char *ini)
{
  PROBE_HIT(__sub_429DB0);
  _BYTE *OldFilename_1; // edi
  __m128i *Str_1; // ebx
  __m128i *Str_2; // esi
  int v6; // eax
  int v7; // eax
  _BYTE *v8; // edi
  char *v9; // edx
  __m128i Str[8]; // [esp+0h] [ebp-90h] BYREF
  char *v12; // [esp+80h] [ebp-10h]

  strcpy(Str[0].m128i_i8, *(char **)__sub_429DB0_argv);
  OldFilename_1 = OldFilename;
  Str_1 = Str;
  v12 = ini + 1;
  Str_2 = (__m128i *)strrchr(Str[0].m128i_i8, 46);
  if ( !Str_2 || strrchr(Str[0].m128i_i8, 92) > (char *)Str_2 )
  {
    if ( !_BitScanForward(
            (unsigned int *)&v6,
            (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, Str[0])) >> ((unsigned int)Str & 0xF)) )
      v6 = __intel_sse2_strlen((unsigned int)Str & 0xF, (char *)Str + ((unsigned int)Str & 0xF));
    Str_2 = (__m128i *)((char *)Str + v6);
  }
  if ( Str != Str_2 )
  {
    do
    {
      *OldFilename_1++ = Str_1->m128i_i8[0];
      Str_1 = (__m128i *)((char *)Str_1 + 1);
    }
    while ( Str_1 != Str_2 );
  }
  v7 = *ini;
  *OldFilename_1 = 46;
  v8 = OldFilename_1 + 1;
  if ( v7 )
  {
    v9 = v12;
    do
    {
      *v8 = v7;
      v7 = *v9;
      ++v8;
      ++v9;
    }
    while ( v7 );
  }
  *v8 = 0;
  return OldFilename;
}

#undef FILE
#undef __intel_sse2_strlen
