// sub_429C80 @ 0x00429C80 — __cdecl
// Extracted from BMF.cpp:34290-34376 by extract.py per incdec.md.


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

PROBE_DECL(__sub_429C80)
__attribute__((force_align_arg_pointer)) BMF_SSE int __sub_429C80(char *Str, int a2, char *a3)
{
  PROBE_HIT(__sub_429C80);
  _BYTE *v3; // ebx
  char *Str_1; // esi
  int v6; // eax
  signed int i_3; // esi
  unsigned int i_1; // ecx
  unsigned int i_2; // eax
  unsigned int i; // esi
  int v11; // eax
  _BYTE *v12; // ebx
  _BYTE *v13; // edx
  signed int i_4; // [esp+0h] [ebp-20h]

  v3 = (_BYTE *)a2;
  Str_1 = strrchr(Str, 46);
  if ( !Str_1 || strrchr(Str, 92) > Str_1 )
  {
    if ( !_BitScanForward(
            (unsigned int *)&v6,
            (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, *(__m128i *)((unsigned int)Str & 0xFFFFFFF0))) >> (((unsigned __int8)Str & 0xF) & 31)) )
      v6 = __intel_sse2_strlen((unsigned __int8)Str & 0xF, Str);
    Str_1 = &Str[v6];
  }
  if ( Str != Str_1 )
  {
    i_3 = Str_1 - Str;
    i_1 = a2 & 0xF;
    if ( (a2 & 0xF) != 0 )
      i_1 = 16 - (a2 & 0xF);
    if ( i_3 < (int)(i_1 + 16) )
    {
      i_2 = 0;
    }
    else
    {
      i_2 = i_3 - (((_BYTE)i_3 - (_BYTE)i_1) & 0xF);
      if ( i_1 )
      {
        i_4 = i_3;
        for ( i = 0; i < i_1; ++i )
          *(_BYTE *)(i + a2) = Str[i];
        i_3 = i_4;
      }
      if ( (((_BYTE)Str + (_BYTE)i_1) & 0xF) != 0 )
      {
        do
        {
          *(__m128i *)(i_1 + a2) = _mm_loadu_si128((const __m128i *)&Str[i_1]);
          i_1 += 16;
        }
        while ( i_1 < i_2 );
      }
      else
      {
        do
        {
          *(__m128i *)(i_1 + a2) = _mm_load_si128((const __m128i *)&Str[i_1]);
          i_1 += 16;
        }
        while ( i_1 < i_2 );
      }
      v3 = (_BYTE *)(i_1 + a2);
    }
    for ( ; i_2 < i_3; ++i_2 )
    {
      *(_BYTE *)(i_2 + a2) = Str[i_2];
      v3 = (_BYTE *)(i_2 + a2 + 1);
    }
  }
  v11 = *a3;
  *v3 = 46;
  v12 = v3 + 1;
  if ( v11 )
  {
    v13 = a3;
    do
    {
      *v12++ = v11;
      LOBYTE(v11) = *++v13;
    }
    while ( *v13 );
  }
  *v12 = 0;
  return a2;
}

#undef FILE
#undef __intel_sse2_strlen
