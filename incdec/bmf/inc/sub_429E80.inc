// sub_429E80 @ 0x00429E80 — __cdecl
// Extracted from BMF.c:34434-34737 by extract.py per incdec.md.

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980
#define sub_42B830 __sub_42B830

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___fclose
#define __PE_DECL___fclose
typedef int t_fclose(FILE1 *);   // _fclose
static t_fclose& __fclose = *(t_fclose*)0x0042CEB4;
#endif
#define fclose __fclose
#ifndef __PE_DECL___ferror
#define __PE_DECL___ferror
typedef int t_ferror(FILE1 *);   // _ferror
static t_ferror& __ferror = *(t_ferror*)0x0042D346;
#endif
#define ferror __ferror
#ifndef __PE_DECL___fgetc
#define __PE_DECL___fgetc
typedef int t_fgetc(FILE1 *);   // _fgetc
static t_fgetc& __fgetc = *(t_fgetc*)0x00431320;
#endif
#define fgetc __fgetc
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
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#ifndef __PE_DECL___op_delete
#define __PE_DECL___op_delete
typedef void t_op_delete(void *);       // ??3@YAXPAX@Z
static t_op_delete& __op_delete = *(t_op_delete*)0x0042CF18;
#endif
#define FILE FILE1

PROBE_DECL(__sub_429E80)
__attribute__((force_align_arg_pointer)) BMF_SSE unsigned __int16 *__sub_429E80(char *FileName)
{
  alignas(16) unsigned char __hexrays_frame[96];   // original frame, ebp-0x50..ebp+0x0
  signed int &v52 = *(signed int *)(__hexrays_frame + 0);
  char * &v53 = *(char * *)(__hexrays_frame + 0);
  unsigned __int16 * &v54 = *(unsigned __int16 * *)(__hexrays_frame + 4);
  size_t &ElementCount = *(size_t *)(__hexrays_frame + 8);
  char &ElementCounta = *(char *)(__hexrays_frame + 8);
  char * &Src = *(char * *)(__hexrays_frame + 12);
  char * &Srca = *(char * *)(__hexrays_frame + 12);
  int &Srca_2 = *(int *)(__hexrays_frame + 16);
  FILE * &Stream_v = *(FILE * *)(__hexrays_frame + 20);
  FILE * &Streama = *(FILE * *)(__hexrays_frame + 20);
  int &Buffer = *(int *)(__hexrays_frame + 24);
  int &v63 = *(int *)(__hexrays_frame + 28);
  int &v64 = *(int *)(__hexrays_frame + 32);
  int &n5 = *(int *)(__hexrays_frame + 36);
  char &v66 = *(char *)(__hexrays_frame + 40);
  char &v67 = *(char *)(__hexrays_frame + 41);
  char &v68 = *(char *)(__hexrays_frame + 42);
  char &v69 = *(char *)(__hexrays_frame + 43);
  unsigned int &n3 = *(unsigned int *)(__hexrays_frame + 44);
  int &v71 = *(int *)(__hexrays_frame + 48);
  unsigned int &v72 = *(unsigned int *)(__hexrays_frame + 52);
  PROBE_HIT(__sub_429E80);
  Stream *Stream_1; // esi
  int Buffer_1; // eax
  char v3; // dl
  char v4; // bl
  char v5; // dl
  char v6; // bl
  char n5_1; // dl
  char v8; // bl
  char v9; // dl
  char v10; // bl
  char n3_1; // dl
  char v12; // bl
  char v13; // dl
  char v14; // bl
  char v15; // dl
  char v16; // bl
  int *v18; // eax
  int v19; // ebx
  signed int v20; // edi
  char v21; // al
  int v22; // edx
  signed int v23; // edi
  char v24; // al
  int v25; // edx
  signed int v26; // edi
  char v27; // al
  int v28; // edx
  int Srca_1; // edi
  int n128; // eax
  size_t Size; // edi
  char *Src_1; // eax
  char *Src_2; // ecx
  char *v34; // esi
  int v35; // edi
  char v36; // fps
  int v37; // eax
  unsigned int v38; // edx
  char *v39; // eax
  __m128i v40; // xmm0
  __m128i v41; // xmm0
  __m128i v42; // xmm0
  __m128i v43; // xmm0
  __m128i v44; // xmm0
  char *v45; // ecx
  unsigned int v46; // ebx
  int v47; // ecx
  char v48; // dl
  int v49; // edi
  int v50; // esi
  char v51; // al

  Stream_1 = fopen(FileName, "rb");
  if ( !Stream_1 || fread(&Buffer, 0x20u, 1u, Stream_1) != 1 )
    return nullptr;
  Buffer_1 = Buffer;
  if ( Buffer == -1788172711 )
  {
    Buffer = 1504078485;
    v3 = v63;
    v4 = BYTE1(v63);
    LOBYTE(v63) = HIBYTE(v63);
    HIBYTE(v63) = v3;
    v5 = v64;
    BYTE1(v63) = BYTE2(v63);
    BYTE2(v63) = v4;
    v6 = BYTE1(v64);
    LOBYTE(v64) = HIBYTE(v64);
    HIBYTE(v64) = v5;
    n5_1 = n5;
    BYTE1(v64) = BYTE2(v64);
    BYTE2(v64) = v6;
    v8 = BYTE1(n5);
    LOBYTE(n5) = HIBYTE(n5);
    HIBYTE(n5) = n5_1;
    v9 = v66;
    BYTE1(n5) = BYTE2(n5);
    BYTE2(n5) = v8;
    v10 = v67;
    v66 = v69;
    v69 = v9;
    n3_1 = n3;
    v67 = v68;
    v68 = v10;
    v12 = BYTE1(n3);
    LOBYTE(n3) = HIBYTE(n3);
    HIBYTE(n3) = n3_1;
    v13 = v71;
    BYTE1(n3) = BYTE2(n3);
    BYTE2(n3) = v12;
    v14 = BYTE1(v71);
    LOBYTE(v71) = HIBYTE(v71);
    HIBYTE(v71) = v13;
    v15 = v72;
    BYTE1(v71) = BYTE2(v71);
    BYTE2(v71) = v14;
    v16 = BYTE1(v72);
    LOBYTE(v72) = HIBYTE(v72);
    Buffer_1 = 1504078485;
    HIBYTE(v72) = v15;
    BYTE1(v72) = BYTE2(v72);
    BYTE2(v72) = v16;
  }
  if ( Buffer_1 != 1504078485 || n3 > 3 || (unsigned int)v71 > 1 )
    return nullptr;
  v18 = sub_42B830(v63, v64, n5, v71, 1);
  v19 = (int)v18;
  if ( v71 )
  {
    if ( v72 / 3 )
    {
      v52 = v72 / 3;
      v20 = 0;
      do
      {
        v21 = fgetc(Stream_1);
        if ( (*(_BYTE *)(v19 + 10) & 0x80) != 0 )
          v22 = v19 + *(_DWORD *)(v19 + 12) + 16;
        else
          v22 = 0;
        *(_BYTE *)(v22 + 3 * v20++ + 2) = v21;
      }
      while ( v20 < v52 );
      v23 = 0;
      do
      {
        v24 = fgetc(Stream_1);
        if ( (*(_BYTE *)(v19 + 10) & 0x80) != 0 )
          v25 = v19 + *(_DWORD *)(v19 + 12) + 16;
        else
          v25 = 0;
        *(_BYTE *)(v25 + 3 * v23++ + 1) = v24;
      }
      while ( v23 < v52 );
      v26 = 0;
      do
      {
        v27 = fgetc(Stream_1);
        if ( (*(_BYTE *)(v19 + 10) & 0x80) != 0 )
          v28 = v19 + *(_DWORD *)(v19 + 12) + 16;
        else
          v28 = 0;
        *(_BYTE *)(v28 + 3 * v26++) = v27;
      }
      while ( v26 < v52 );
    }
    if ( ferror(Stream_1) )
      return nullptr;
  }
  else if ( (unsigned int)n5 <= 8 )
  {
    *((_BYTE *)v18 + 10) |= 0x40u;
  }
  if ( n3 == 2 )
  {
    if ( *(_DWORD *)(v19 + 12) )
    {
      Srca_1 = 0;
      do
      {
        Srca_2 = Srca_1;
        n128 = fgetc(Stream_1);
        if ( n128 == 128 )
        {
          v37 = fgetc(Stream_1);
          if ( v37 )
          {
            Srca = (char *)(Srca_1 + v37 + 1);
            ElementCounta = fgetc(Stream_1);
            if ( Srca_1 < (int)Srca )
            {
              v38 = (unsigned int)&Srca[-Srca_1];
              if ( (int)&Srca[-Srca_1] < 16 )
              {
                v39 = nullptr;
              }
              else
              {
                v53 = (char *)v19;
                v39 = (char *)(v38 - (v38 & 0xF));
                v40 = _mm_cvtsi32_si128(ElementCounta);
                v41 = _mm_unpacklo_epi8(v40, v40);
                v42 = _mm_unpacklo_epi16(v41, v41);
                v43 = _mm_unpacklo_epi32(v42, v42);
                v44 = _mm_unpacklo_epi64(v43, v43);
                v45 = (char *)(v19 + Srca_1);
                v46 = 0;
                do
                {
                  *(__m128i *)&v45[v46 + 16] = v44;
                  v46 += 16;
                }
                while ( v46 < (unsigned int)v39 );
                Srca_1 += v46;
                v19 = (int)v53;
              }
              for ( ; (unsigned int)v39 < v38; ++v39 )
              {
                v39[v19 + 16 + Srca_2] = ElementCounta;
                Srca_1 = (int)&v39[Srca_2 + 1];
              }
            }
            --Srca_1;
          }
          else
          {
            *(_BYTE *)(Srca_1 + v19 + 16) = 0x80;
          }
        }
        else
        {
          *(_BYTE *)(Srca_1 + v19 + 16) = n128;
        }
        if ( ferror(Stream_1) )
          return nullptr;
      }
      while ( (unsigned int)++Srca_1 < *(_DWORD *)(v19 + 12) );
    }
  }
  else
  {
    Size = (*(unsigned __int16 *)(v19 + 4) + 1) & 0xFFFFFFFE;
    v54 = (unsigned __int16 *)(v19 + 16);
    Src_1 = (char *)__op_new(Size);
    Src_2 = Src_1;
    if ( *(_WORD *)(v19 + 2) )
    {
      Src = Src_1;
      ElementCount = Size;
      Stream_v = Stream_1;
      v34 = (char *)(v19 + 16);
      v35 = 0;
      while ( fread(Src, 1u, ElementCount, Stream_v) == ElementCount )
      {
        sub_434980(v34,Src,*(unsigned __int16 *)(v19 + 4));
        v34 += *(unsigned __int16 *)(v19 + 4);
        if ( ++v35 >= *(unsigned __int16 *)(v19 + 2) )
        {
          Src_2 = Src;
          Stream_1 = Stream_v;
          goto LABEL_43;
        }
      }
      return nullptr;
    }
LABEL_43:
    __op_delete(Src_2);
    if ( n3 == 3 )
    {
      if ( n5 == 24 )
      {
        if ( *(unsigned __int16 *)v19 * *(unsigned __int16 *)(v19 + 2) > 0 )
        {
          Streama = Stream_1;
          v49 = 0;
          do
          {
            v50 = 3 * v49;
            v51 = *((_BYTE *)v54 + 3 * v49 + 2);
            *((_BYTE *)v54 + v50 + 2) = *((_BYTE *)v54 + 3 * v49++);
            *((_BYTE *)v54 + v50) = v51;
          }
          while ( v49 < *(unsigned __int16 *)v19 * *(unsigned __int16 *)(v19 + 2) );
          Stream_1 = Streama;
        }
      }
      else if ( n5 == 32 && *(unsigned __int16 *)v19 * *(unsigned __int16 *)(v19 + 2) > 0 )
      {
        v47 = 0;
        do
        {
          v48 = v54[2 * v47 + 1];
          LOBYTE(v54[2 * v47 + 1]) = v54[2 * v47];
          LOBYTE(v54[2 * v47++]) = v48;
        }
        while ( v47 < *(unsigned __int16 *)v19 * *(unsigned __int16 *)(v19 + 2) );
      }
    }
  }
  fclose(Stream_1);
  return (unsigned __int16 *)v19;
}

#undef FILE
#undef fclose
#undef ferror
#undef fgetc
#undef fopen
#undef fread
#undef sub_42B830
#undef sub_434980
