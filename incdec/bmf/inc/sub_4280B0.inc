// sub_4280B0 @ 0x004280B0 — __cdecl
// Extracted from BMF.c:32480-32721 by extract.py per incdec.md.

static inline _BYTE * __fwd_sub_4280B0_sub_429DB0(void *a0, void *a1) { return __sub_429DB0((_BYTE *)a0, (char *)a1); }
#define sub_429DB0 __fwd_sub_4280B0_sub_429DB0
static inline int __fwd_sub_4280B0_sub_42CAD0(void *a0, int a1) { return __sub_42CAD0((_BYTE *)a0, a1); }
#define sub_42CAD0 __fwd_sub_4280B0_sub_42CAD0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL_____intel_sse2_strlen
#define __PE_DECL_____intel_sse2_strlen
typedef __attribute__((fastcall)) int t___intel_sse2_strlen(unsigned int, const void *);   // ___intel_sse2_strlen
static t___intel_sse2_strlen& ____intel_sse2_strlen = *(t___intel_sse2_strlen*)0x00434930;
#endif
#define __intel_sse2_strlen ____intel_sse2_strlen
#ifndef __PE_DECL___fclose
#define __PE_DECL___fclose
typedef int t_fclose(FILE1 *);   // _fclose
static t_fclose& __fclose = *(t_fclose*)0x0042CEB4;
#endif
#define fclose __fclose
#ifndef __PE_DECL___feof
#define __PE_DECL___feof
typedef int t_feof(FILE1 *);   // _feof
static t_feof& __feof = *(t_feof*)0x0042D33B;
#endif
#define feof __feof
#ifndef __PE_DECL___fgets
#define __PE_DECL___fgets
typedef char * t_fgets(char *, int, FILE1 *);   // _fgets
static t_fgets& __fgets = *(t_fgets*)0x0042D696;
#endif
#define fgets __fgets
#ifndef __PE_DECL___fopen
#define __PE_DECL___fopen
typedef FILE1 * t_fopen(const char *, const char *);   // _fopen
static t_fopen& __fopen = *(t_fopen*)0x0042CDB9;
#endif
#define fopen __fopen
#define FILE FILE1

PROBE_DECL(__sub_4280B0)
BMF_SSE size_t __sub_4280B0(int BMF_Options, int OutFileType, int Destination, char *Destinationa, signed int Count)
{
  PROBE_HIT(__sub_4280B0);
  const char *FileName; // eax
  Stream *Stream_v; // ebp
  char *Destinationa_1; // esi
  bool v8; // zf
  int v9; // eax
  int v10; // ebx
  int v11; // esi
  int v12; // ecx
  __m128i *i; // ebx
  unsigned int n0x20; // ecx
  int v15; // eax
  __int8 *v16; // eax
  __int8 *v17; // ebx
  int k_1; // edx
  int k; // ecx
  unsigned int n0x20_3; // ecx
  int v21; // ebx
  int n10; // eax
  __m128i *n; // ebx
  int ii; // ebp
  int v25; // eax
  unsigned __int8 *v27; // eax
  __int8 *i_1; // ebx
  int v29; // ecx
  unsigned int n0x20_1; // ecx
  int v31; // eax
  int j_1; // eax
  __int8 *v33; // edx
  int j; // ecx
  unsigned int n0x20_2; // ecx
  int v36; // eax
  char v37; // sp
  int v38; // ecx
  int v39; // eax
  size_t Count_1; // ebx
  int v41; // eax
  char *v42; // eax
  unsigned int v43; // ebx
  int m_1; // edx
  int m; // ecx
  unsigned int n0x20_4; // ecx
  int v47; // eax
  int v48; // eax
  char OldFilename[128]; // [esp+0h] [ebp-194h] BYREF
  __m128i Buffer[16]; // [esp+80h] [ebp-114h] BYREF
  int v51; // [esp+180h] [ebp-14h]

  FileName = sub_429DB0(OldFilename, "ini");
  Stream_v = fopen(FileName, "rt");
  Destinationa_1 = Destinationa;
  if ( !Stream_v )
  {
    if ( Destinationa != (char *)Destination )
      strcpy(Destinationa, (const char *)Destination);
    v8 = !_BitScanForward(
            (unsigned int *)&v48,
            (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, *(__m128i *)(Destination & 0xFFFFFFF0))) >> (Destination & 0xF));
    if ( v8 )
      v48 = __intel_sse2_strlen(Destination & 0xF, Destination);
    return v48 + 1;
  }
  v8 = !_BitScanForward(
          (unsigned int *)&v9,
          (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, *(__m128i *)(BMF_Options & 0xFFFFFFF0))) >> (BMF_Options & 0xF));
  if ( v8 )
    v9 = __intel_sse2_strlen(BMF_Options & 0xF, BMF_Options);
  v10 = v9;
  if ( feof(Stream_v) )
  {
    v21 = 0;
    goto LABEL_22;
  }
  v51 = v10;
  v11 = 0;
  while ( 1 )
  {
    fgets(Buffer[0].m128i_i8, 256, Stream_v);
    v12 = Buffer[0].m128i_u8[0];
    for ( i = Buffer; ; v12 = i->m128i_u8[0] )
    {
      n0x20 = v12 - 9;
      if ( n0x20 >= 0x20 || ((1 << n0x20) & 0x800011) == 0 )
        break;
      i = (__m128i *)((char *)i + 1);
    }
    if ( !v11 )
    {
      if ( i->m128i_i8[0] == 91 )
      {
        v27 = &i->m128i_u8[2];
        i_1 = &i->m128i_i8[1];
        v29 = (unsigned __int8)*i_1;
        while ( 1 )
        {
          n0x20_1 = v29 - 9;
          if ( n0x20_1 >= 0x20 || ((1 << n0x20_1) & 0x800011) == 0 )
            break;
          v29 = *v27;
          ++i_1;
          ++v27;
        }
        v31 = sub_42CAD0(i_1, BMF_Options);
        if ( v31 == v51 )
        {
          j_1 = i_1[v51];
          v33 = &i_1[v51 + 1];
          for ( j = (unsigned __int8)j_1; ; j = (unsigned __int8)j_1 )
          {
            n0x20_2 = j - 9;
            if ( n0x20_2 >= 0x20 || ((1 << n0x20_2) & 0x800011) == 0 )
              break;
            j_1 = *v33++;
          }
          if ( j_1 == 93 )
          {
            v8 = !_BitScanForward(
                    (unsigned int *)&v36,
                    (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, *(__m128i *)(OutFileType & 0xFFFFFFF0))) >> (OutFileType & 0xF));
            if ( v8 )
              v36 = __intel_sse2_strlen(OutFileType & 0xF, OutFileType);
            v51 = v36;
            v11 = 1;
          }
        }
      }
      goto LABEL_20;
    }
    if ( i->m128i_i8[0] == 91 )
      goto LABEL_21;
    v15 = sub_42CAD0(i, OutFileType);
    if ( v15 == v51 )
    {
      v16 = &i->m128i_i8[v51 + 1];
      v17 = &i->m128i_i8[v51];
      k_1 = *v17;
      for ( k = (unsigned __int8)k_1; ; k = (unsigned __int8)k_1 )
      {
        n0x20_3 = k - 9;
        if ( n0x20_3 >= 0x20 || ((1 << n0x20_3) & 0x800011) == 0 )
          break;
        k_1 = *v16;
        ++v17;
        ++v16;
      }
      if ( k_1 == 61 )
      {
        v42 = v17 + 2;
        v43 = (unsigned int)(v17 + 1);
        m_1 = *(char *)v43;
        for ( m = (unsigned __int8)m_1; ; m = (unsigned __int8)m_1 )
        {
          n0x20_4 = m - 9;
          if ( n0x20_4 >= 0x20 || ((1 << n0x20_4) & 0x800011) == 0 )
            break;
          m_1 = *v42;
          ++v43;
          ++v42;
        }
        if ( m_1 )
          break;
      }
    }
LABEL_20:
    if ( feof(Stream_v) )
    {
LABEL_21:
      Destinationa_1 = Destinationa;
      v21 = 0;
      goto LABEL_22;
    }
  }
  Destinationa_1 = Destinationa;
  v8 = !_BitScanForward(
          (unsigned int *)&v47,
          (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, *(__m128i *)(v43 & 0xFFFFFFF0))) >> (v43 & 0xF));
  if ( v8 )
    v47 = __intel_sse2_strlen(v43 & 0xF, v43);
  memcpy(Buffer, (const void *)v43, v47 + 1);
  v21 = 1;
LABEL_22:
  fclose(Stream_v);
  if ( v21 )
  {
    n10 = Buffer[0].m128i_i8[0];
    for ( n = Buffer; n10 != 59; n10 = n->m128i_i8[0] )
    {
      if ( n10 == 10 )
        break;
      if ( n10 == 13 )
        break;
      if ( !n10 )
        break;
      n = (__m128i *)((char *)n + 1);
    }
    n->m128i_i8[0] = 0;
    for ( ii = 0; isspace(ii) || !ii; ii = n->m128i_i8[0] )
    {
      n->m128i_i8[0] = 0;
      n = (__m128i *)((char *)n - 1);
    }
    v38 = (v37 + 0x80) & 0xF;
    v8 = !_BitScanForward(
            (unsigned int *)&v39,
            (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, Buffer[0])) >> v38);
    if ( v8 )
      v39 = __intel_sse2_strlen(v38, (char *)Buffer + v38);
    if ( v39 )
    {
      Count_1 = v39 + 1;
      if ( v39 + 1 >= Count )
        Count_1 = Count;
      strncpy(Destinationa_1, Buffer[0].m128i_i8, Count_1);
      return Count_1;
    }
    else
    {
      if ( Destinationa_1 != (char *)Destination )
        strcpy(Destinationa_1, (const char *)Destination);
      v8 = !_BitScanForward(
              (unsigned int *)&v41,
              (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, *(__m128i *)(Destination & 0xFFFFFFF0))) >> (Destination & 0xF));
      if ( v8 )
        v41 = __intel_sse2_strlen(Destination & 0xF, Destination);
      return v41 + 1;
    }
  }
  else
  {
    if ( Destinationa_1 != (char *)Destination )
      strcpy(Destinationa_1, (const char *)Destination);
    v8 = !_BitScanForward(
            (unsigned int *)&v25,
            (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, *(__m128i *)(Destination & 0xFFFFFFF0))) >> (Destination & 0xF));
    if ( v8 )
      v25 = __intel_sse2_strlen(Destination & 0xF, Destination);
    return v25 + 1;
  }
}

#undef FILE
#undef __intel_sse2_strlen
#undef fclose
#undef feof
#undef fgets
#undef fopen
#undef sub_429DB0
#undef sub_42CAD0
