// sub_42AB20 @ 0x0042AB20 — __cdecl
// Extracted from BMF.cpp:35126-35473 by extract.py per incdec.md.

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980
#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0
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
#ifndef __PE_DECL___fseek
#define __PE_DECL___fseek
typedef int t_fseek(FILE1 *, long, int);   // _fseek
static t_fseek& __fseek = *(t_fseek*)0x0042D0DD;
#endif
#define fseek __fseek
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

PROBE_DECL(__sub_42AB20)
__attribute__((force_align_arg_pointer)) BMF_SSE int *__sub_42AB20(char *FileName)
{
  alignas(16) unsigned char __hexrays_frame[128];   // original frame, ebp-0x70..ebp+0x0
  unsigned int &Size_4 = *(unsigned int *)(__hexrays_frame + 0);
  int &v46 = *(int *)(__hexrays_frame + 0);
  int &v47 = *(int *)(__hexrays_frame + 0);
  int &Offset_1 = *(int *)(__hexrays_frame + 0);
  signed int &Size = *(signed int *)(__hexrays_frame + 4);
  size_t &Sizea = *(size_t *)(__hexrays_frame + 4);
  char &Sizeb = *(char *)(__hexrays_frame + 4);
  int * &v52 = *(int * *)(__hexrays_frame + 8);
  int &Src_2 = *(int *)(__hexrays_frame + 12);
  int &v54 = *(int *)(__hexrays_frame + 12);
  void * &Buffer_3 = *(void * *)(__hexrays_frame + 16);
  char * &Src = *(char * *)(__hexrays_frame + 24);
  _BYTE (&Buffer_2)[4] = *(_BYTE (*)[4])(__hexrays_frame + 32);
  _DWORD (&Buffer_1)[2] = *(_DWORD (*)[2])(__hexrays_frame + 36);
  int &v59 = *(int *)(__hexrays_frame + 44);
  __int16 &v60 = *(__int16 *)(__hexrays_frame + 48);
  unsigned __int16 &n5 = *(unsigned __int16 *)(__hexrays_frame + 50);
  int &n2 = *(int *)(__hexrays_frame + 52);
  int &Size_3 = *(int *)(__hexrays_frame + 68);
  __int16 (&Buffer)[5] = *(__int16 (*)[5])(__hexrays_frame + 76);
  int &Offset = *(int *)(__hexrays_frame + 86);
  PROBE_HIT(__sub_42AB20);
  Stream *Stream_v; // esi
  int *v3; // ebx
  size_t Size_2; // edi
  int Size_1; // edx
  signed int i; // edi
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  char v10; // fps
  int Src_1; // edi
  int j_3; // ebx
  int Sizea_1; // eax
  unsigned int j_1; // eax
  unsigned int j_2; // edx
  unsigned int j; // ecx
  __m128i v17; // xmm0
  __m128i v18; // xmm0
  __m128i v19; // xmm0
  __m128i v20; // xmm0
  __m128i v21; // xmm0
  BOOL v22; // edi
  int n2_1; // eax
  unsigned int n2_2; // ebx
  char v25; // al
  int v26; // ecx
  char *Src_4; // edi
  char v28; // dl
  unsigned int v29; // ebx
  char v30; // al
  int v31; // edx
  char *Src_3; // ecx
  size_t ElementCount; // edx
  int Offset_2; // edi
  int v35; // edi
  char *Src_6; // ebx
  size_t ElementCount_1; // eax
  int v38; // ebx
  char v39; // fps
  int v40; // ebx
  int v41; // edx
  char *Buffer_4; // edx
  char *Src_5; // ecx
  unsigned int v44; // ebx

  Stream_v = fopen(FileName, "rb");
  if ( !Stream_v
    || fread(Buffer, 0xEu, 1u, Stream_v) != 1
    || Buffer[0] != 19778
    || fread(Buffer_1, 0x28u, 1u, Stream_v) != 1
    || Buffer_1[0] != 40
    || v60 != 1 )
  {
    return nullptr;
  }
  v3 = sub_42B830(Buffer_1[1], v59, n5, n5 <= 8u, 1);
  Size_2 = (*((unsigned __int16 *)v3 + 2) + 3) & 0xFFFFFFFC;
  if ( n5 <= 8u )
  {
    Size_1 = 1 << (n5 & 31);
    if ( Size_3 )
      Size_1 = Size_3;
    if ( Size_1 > 0 )
    {
      Size_4 = (*((unsigned __int16 *)v3 + 2) + 3) & 0xFFFFFFFC;
      Size = Size_1;
      for ( i = 0; i < Size; ++i )
      {
        fread(Buffer_2, 4u, 1u, Stream_v);
        if ( (*((_BYTE *)v3 + 10) & 0x80) != 0 )
          v7 = (int)v3 + v3[3] + 16;
        else
          v7 = 0;
        *(_BYTE *)(v7 + 3 * i + 2) = Buffer_2[2];
        if ( (*((_BYTE *)v3 + 10) & 0x80) != 0 )
          v8 = (int)v3 + v3[3] + 16;
        else
          v8 = 0;
        *(_BYTE *)(v8 + 3 * i + 1) = Buffer_2[1];
        if ( (*((_BYTE *)v3 + 10) & 0x80) != 0 )
          v9 = (int)v3 + v3[3] + 16;
        else
          v9 = 0;
        *(_BYTE *)(v9 + 3 * i) = Buffer_2[0];
      }
      Size_2 = Size_4;
    }
  }
  Buffer_3 = __op_new(Size_2);
  Src = (char *)v3 + v3[3] - *((unsigned __int16 *)v3 + 2) + 16;
  fseek(Stream_v, Offset, 0);
  if ( n2 )
  {
    if ( n2 == 1 )
    {
      sub_4349F0((char *)v3 + 16,0,v3[3]);
      Src_1 = (int)Src;
      v52 = v3;
      v46 = *((unsigned __int16 *)v3 + 1) - 1;
      while ( 1 )
      {
        Src_2 = Src_1;
        if ( ferror(Stream_v) )
          return nullptr;
        j_3 = fgetc(Stream_v);
        Sizea_1 = fgetc(Stream_v);
        Sizea = Sizea_1;
        if ( j_3 )
        {
          j_1 = Src_1 & 0xF;
          if ( (Src_1 & 0xF) != 0 )
            j_1 = 16 - (Src_1 & 0xF);
          if ( j_3 < (int)(j_1 + 16) )
          {
            j_2 = 0;
          }
          else
          {
            j_2 = j_3 - (((_BYTE)j_3 - (_BYTE)j_1) & 0xF);
            if ( j_1 )
            {
              for ( j = 0; j < j_1; ++j )
                *(_BYTE *)(j + Src_1) = Sizea;
            }
            v17 = _mm_cvtsi32_si128((char)Sizea);
            v18 = _mm_unpacklo_epi8(v17, v17);
            v19 = _mm_unpacklo_epi16(v18, v18);
            v20 = _mm_unpacklo_epi32(v19, v19);
            v21 = _mm_unpacklo_epi64(v20, v20);
            do
            {
              *(__m128i *)(Src_1 + j_1) = v21;
              j_1 += 16;
            }
            while ( j_1 < j_2 );
            Src_1 += j_1;
          }
          for ( ; j_2 < j_3; ++j_2 )
          {
            *(_BYTE *)(Src_2 + j_2) = Sizea;
            Src_1 = j_2 + Src_2 + 1;
          }
        }
        else if ( Sizea_1 )
        {
          if ( Sizea_1 == 1 )
            goto LABEL_61;
          if ( Sizea_1 == 2 )
          {
            v38 = fgetc(Stream_v);
            Src_1 = v38 + Src_1 - fgetc(Stream_v) * *((unsigned __int16 *)v52 + 2);
          }
          else
          {
            fread(Buffer_3, (Sizea_1 + 1) & 0xFFFFFFFE, 1u, Stream_v);
            sub_434980((char *)Src_1,(char *)Buffer_3,Sizea);
            Src_1 += Sizea;
          }
        }
        else
        {
          if ( --v46 < 0 )
            goto LABEL_61;
          Src_1 = (int)v52 + v46 * *((unsigned __int16 *)v52 + 2) + 16;
        }
      }
    }
    if ( n2 != 2 )
      return nullptr;
    sub_4349F0((char *)v3 + 16,0,v3[3]);
    v52 = v3;
    v22 = 1;
    v47 = *((unsigned __int16 *)v3 + 1) - 1;
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
LABEL_44:
          if ( ferror(Stream_v) )
            return nullptr;
          v54 = fgetc(Stream_v);
          n2_1 = fgetc(Stream_v);
          n2_2 = n2_1;
          if ( !v54 )
            break;
          v25 = n2_1 & 0xF;
          if ( v22 )
          {
            v31 = v54;
            Src_3 = Src;
            while ( v31 != 1 )
            {
              *Src_3++ = n2_2;
              v31 -= 2;
              if ( !v31 )
              {
                Src = Src_3;
                v22 = 1;
                goto LABEL_44;
              }
            }
            Src = Src_3;
            *Src_3 = n2_2 & 0xF0;
            v22 = 0;
          }
          else
          {
            v26 = v54;
            Src_4 = Src;
            v28 = *Src;
            v29 = n2_2 >> 4;
            v30 = 16 * v25;
            while ( 1 )
            {
              *Src_4++ = v29 | v28;
              if ( v26 == 1 )
                break;
              v28 = v30;
              v26 -= 2;
              if ( !v26 )
              {
                Src = Src_4;
                *Src_4 = v30;
                v22 = 0;
                goto LABEL_44;
              }
            }
            Src = Src_4;
            v22 = 1;
          }
        }
        if ( n2_1 )
          break;
        if ( --v47 < 0 )
          goto LABEL_61;
        Src = (char *)v52 + v47 * *((unsigned __int16 *)v52 + 2) + 16;
      }
      if ( n2_1 == 1 )
        goto LABEL_61;
      if ( n2_1 != 2 )
        break;
      v40 = fgetc(Stream_v);
      v41 = (v40 >> 1) - fgetc(Stream_v) * *((unsigned __int16 *)v52 + 2);
      if ( (v40 & 1) == 1 )
      {
        if ( !v22 )
          ++v41;
        v22 = !v22;
      }
      Src += v41;
    }
    fread(Buffer_3, (((n2_1 + 1) >> 1) + 1) & 0xFFFFFFFE, 1u, Stream_v);
    Buffer_4 = (char *)Buffer_3;
    Src_5 = Src;
    while ( 1 )
    {
      Sizeb = *Buffer_4;
      if ( v22 )
      {
        v44 = n2_2 - 1;
        if ( !v44 )
        {
          Src = Src_5;
          *Src_5 = *Buffer_4 & 0xF0;
          v22 = 0;
          goto LABEL_44;
        }
        *Src_5++ = Sizeb;
        v22 = 1;
      }
      else
      {
        *Src_5++ |= (unsigned __int8)*Buffer_4 >> 4;
        v44 = n2_2 - 1;
        if ( !v44 )
        {
          Src = Src_5;
          v22 = 1;
          goto LABEL_44;
        }
        *Src_5 = 16 * (Sizeb & 0xF);
        v22 = 0;
      }
      ++Buffer_4;
      n2_2 = v44 - 1;
      if ( !n2_2 )
      {
        Src = Src_5;
        goto LABEL_44;
      }
    }
  }
  ElementCount = *((unsigned __int16 *)v3 + 2);
  Offset_2 = Size_2 - ElementCount;
  if ( v59 - 1 >= 0 )
  {
    Offset_1 = Offset_2;
    v35 = v59 - 1;
    v52 = v3;
    Src_6 = Src;
    while ( 1 )
    {
      ElementCount_1 = fread(Src_6, 1u, ElementCount, Stream_v);
      ElementCount = *((unsigned __int16 *)v52 + 2);
      if ( ElementCount_1 != ElementCount )
        return nullptr;
      if ( Offset_1 )
      {
        fseek(Stream_v, Offset_1, 1);
        ElementCount = *((unsigned __int16 *)v52 + 2);
      }
      Src_6 -= ElementCount;
      if ( --v35 < 0 )
      {
LABEL_61:
        v3 = v52;
        break;
      }
    }
  }
  fclose(Stream_v);
  __op_delete(Buffer_3);
  return v3;
}

#undef FILE
#undef fclose
#undef ferror
#undef fgetc
#undef fopen
#undef fread
#undef fseek
#undef sub_42B830
#undef sub_434980
#undef sub_4349F0
