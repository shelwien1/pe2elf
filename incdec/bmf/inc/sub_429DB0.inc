// sub_429DB0 @ 0x00429DB0 — __cdecl
// Extracted from BMF.cpp:34379-34431 by extract.py per incdec.md.

typedef int t_sub_429DB0_argv;
static t_sub_429DB0_argv& __sub_429DB0_argv = *(t_sub_429DB0_argv*)0x00445954;


PROBE_DECL(__sub_429DB0)
BMF_REALIGN BMF_SSE _BYTE *__sub_429DB0(_BYTE *OldFilename, char *ini)
{
  alignas(16) unsigned char __hexrays_frame[160];   // original frame, ebp-0x90..ebp+0x0
  __m128i (&Str)[8] = *(__m128i (*)[8])(__hexrays_frame + 0);
  char * &v12 = *(char * *)(__hexrays_frame + 128);
  PROBE_HIT(__sub_429DB0);
  _BYTE *OldFilename_1; // edi
  __m128i *Str_1; // ebx
  __m128i *Str_2; // esi
  int v6; // eax
  int v7; // eax
  _BYTE *v8; // edi
  char *v9; // edx

  strcpy(Str[0].m128i_i8, *(char **)__sub_429DB0_argv);
  OldFilename_1 = OldFilename;
  Str_1 = Str;
  v12 = ini + 1;
  Str_2 = (__m128i *)strrchr(Str[0].m128i_i8, 46);
  if ( !Str_2 || strrchr(Str[0].m128i_i8, 92) > (char *)Str_2 )
  {
    if ( !_BitScanForward(
            (unsigned int *)&v6,
            (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, Str[0])) >> (((unsigned int)Str & 0xF) & 31)) )
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

