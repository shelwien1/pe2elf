// sub_42A4E0 @ 0x0042A4E0 — __usercall
// Extracted from BMF.cpp:34812-35123 by extract.py per incdec.md.

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
#ifndef __PE_DECL___fscanf
#define __PE_DECL___fscanf
typedef int t_fscanf(FILE1 *, const char *, ...);   // _fscanf
static t_fscanf& __fscanf = *(t_fscanf*)0x0042DEE4;
#endif
#define fscanf __fscanf
#define FILE FILE1

PROBE_DECL(__sub_42A4E0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) int * __sub_42A4E0(unsigned int GIF8, char *FileName)
{
  alignas(16) unsigned char __hexrays_frame[320];   // original frame, ebp-0x130..ebp+0x0
  unsigned int &n0x100_2 = *(unsigned int *)(__hexrays_frame + 0);
  FILE * &Stream_v = *(FILE * *)(__hexrays_frame + 4);
  int * &v47 = *(int * *)(__hexrays_frame + 8);
  int &n255 = *(int *)(__hexrays_frame + 16);
  unsigned int &n0x100 = *(unsigned int *)(__hexrays_frame + 20);
  unsigned int &n0x100_1 = *(unsigned int *)(__hexrays_frame + 24);
  __m128i (&v51)[16] = *(__m128i (*)[16])(__hexrays_frame + 28);
  int &n255_7 = *(int *)(__hexrays_frame + 284);
  int &v53 = *(int *)(__hexrays_frame + 288);
  PROBE_HIT(__sub_42A4E0);
  Stream *Stream_1; // ebp
  bool v4; // zf
  int n2; // eax
  int C; // eax
  int *n0x100_4; // ebx
  int C_2; // eax
  int *n0x100_7; // eax
  char n0x100_8; // al
  int n255_1; // edx
  int v12; // ecx
  int n0x100_3; // edi
  int n255_2; // edx
  unsigned int v15; // edi
  unsigned int v16; // eax
  int v17; // ebp
  char v18; // dl
  int v19; // ebp
  char v20; // dl
  int n255_3; // ecx
  int v22; // edi
  char v23; // al
  int C_1; // eax
  int *n0x100_6; // eax
  int n255_8; // edx
  _BYTE *v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int *v33; // ecx
  int n255_9; // edx
  int v35; // ebx
  int *v36; // ebp
  unsigned int n0x100_5; // edi
  int n255_4; // ecx
  Stream *Stream_2; // ebp
  char v40; // al
  int n255_5; // esi
  int *v42; // edx
  int n255_6; // esi
  int v44; // eax

  Stream_1 = fopen(FileName, "rb");
  if ( !Stream_1 || fscanf(Stream_1, "%s%d%d", v51, &n255_7, &v53) != 3 )
    return nullptr;
  v4 = !_BitScanForward(
          (unsigned int *)&n2,
          (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8((__m128i)0LL, v51[0])) >> (((unsigned int)v51 & 0xF) & 31));
  if ( v4 )
    n2 = __intel_sse2_strlen((unsigned int)v51 & 0xF, (char *)v51 + ((unsigned int)v51 & 0xF));
  if ( n2 != 2 )
    return nullptr;
  if ( v51[0].m128i_i8[0] != 80 )
    return nullptr;
  if ( v51[0].m128i_i8[1] < 49 )
    return nullptr;
  if ( v51[0].m128i_i8[1] > 54 )
    return nullptr;
  if ( n255_7 <= 0 )
    return nullptr;
  if ( v53 <= 0 )
    return nullptr;
  C = fgetc(Stream_1);
  if ( !isspace(C) )
    return nullptr;
  switch ( v51[0].m128i_i8[1] )
  {
    case '1':
    case '4':
      n0x100_4 = sub_42B830(n255_7, v53, 1, 1, 1);
      if ( (*((_BYTE *)n0x100_4 + 10) & 0x80) != 0 )
        v27 = (char *)n0x100_4 + n0x100_4[3] + 16;
      else
        v27 = nullptr;
      *v27 = -1;
      if ( (*((_BYTE *)n0x100_4 + 10) & 0x80) != 0 )
        v28 = (int)n0x100_4 + n0x100_4[3] + 16;
      else
        v28 = 0;
      *(_BYTE *)(v28 + 1) = -1;
      if ( (*((_BYTE *)n0x100_4 + 10) & 0x80) != 0 )
        v29 = (int)n0x100_4 + n0x100_4[3] + 16;
      else
        v29 = 0;
      *(_BYTE *)(v29 + 2) = -1;
      if ( (*((_BYTE *)n0x100_4 + 10) & 0x80) != 0 )
        v30 = (int)n0x100_4 + n0x100_4[3] + 16;
      else
        v30 = 0;
      *(_BYTE *)(v30 + 3) = 0;
      if ( (*((_BYTE *)n0x100_4 + 10) & 0x80) != 0 )
        v31 = (int)n0x100_4 + n0x100_4[3] + 16;
      else
        v31 = 0;
      *(_BYTE *)(v31 + 4) = 0;
      if ( (*((_BYTE *)n0x100_4 + 10) & 0x80) != 0 )
        v32 = (int)n0x100_4 + n0x100_4[3] + 16;
      else
        v32 = 0;
      v4 = v51[0].m128i_i8[1] == 49;
      *(_BYTE *)(v32 + 5) = 0;
      if ( v4 )
      {
        v33 = n0x100_4 + 4;
        if ( v53 - 1 < 0 )
        {
          --v53;
          goto LABEL_20;
        }
        n255_9 = n255_7;
        n0x100_2 = (unsigned int)n0x100_4;
        v35 = v53 - 1;
        Stream_v = Stream_1;
        v36 = v33;
        while ( 1 )
        {
          n0x100_5 = 0;
          n255_4 = 0;
          if ( n255_9 > 0 )
            break;
          v40 = 0;
          LOBYTE(n255_6) = 0;
LABEL_90:
          if ( (n255_6 & 7) != 0 )
          {
            *(_BYTE *)v36 = v40;
            v36 = (int *)((char *)v36 + 1);
          }
          if ( --v35 < 0 )
          {
            Stream_1 = Stream_v;
            n0x100 = n0x100_5;
            v44 = v35;
            n0x100_4 = (int *)n0x100_2;
            v53 = v44;
            n255 = n255_4;
            goto LABEL_20;
          }
        }
        v53 = v35;
        v47 = v36;
        Stream_2 = Stream_v;
        n0x100 = 0;
        n255 = 0;
        while ( fscanf(Stream_2, "%d", &n0x100_1) == 1 && n0x100_1 <= 1 )
        {
          v40 = n0x100 + n0x100 + n0x100_1;
          n255_5 = n255;
          n0x100_5 = n0x100 + n0x100 + n0x100_1;
          if ( (n255 & 7) == 7 )
          {
            v42 = v47;
            *(_BYTE *)v47 = v40;
            v47 = (int *)((char *)v42 + 1);
            n0x100_5 = 0;
            v40 = 0;
          }
          n255_9 = n255_7;
          n255_6 = n255_5 + 1;
          n255_4 = n255_6;
          if ( n255_6 >= n255_7 )
          {
            v36 = v47;
            v35 = v53;
            goto LABEL_90;
          }
          n0x100 = n0x100_5;
          n255 = n255_6;
        }
        return nullptr;
      }
      else
      {
        if ( fread(n0x100_4 + 4, 1u, n0x100_4[3], Stream_1) == n0x100_4[3] )
          goto LABEL_20;
        return nullptr;
      }
    case '2':
    case '5':
      if ( fscanf(Stream_1, "%d", &n255) == 1 && n255 == 255 && (C_1 = fgetc(Stream_1), isspace(C_1)) )
      {
        n0x100_6 = sub_42B830(n255_7, v53, 8, 0, 0);
        n0x100_4 = n0x100_6;
        *((_BYTE *)n0x100_6 + 10) |= 0x40u;
        if ( v51[0].m128i_i8[1] == 50 )
        {
          n255 = 0;
          if ( v53 * n255_7 <= 0 )
            goto LABEL_20;
          while ( fscanf(Stream_1, "%d", &n0x100) == 1 && n0x100 < 0x100 )
          {
            n255_8 = n255;
            *((_BYTE *)n0x100_4 + n255 + 16) = n0x100;
            n255 = n255_8 + 1;
            if ( n255_8 + 1 >= v53 * n255_7 )
              goto LABEL_20;
          }
          return nullptr;
        }
        if ( fread(n0x100_6 + 4, 1u, n0x100_6[3], Stream_1) == n0x100_6[3] )
          goto LABEL_20;
        return nullptr;
      }
      else
      {
        return nullptr;
      }
    case '3':
    case '6':
      if ( fscanf(Stream_1, "%d", &n255) == 1 && n255 == 255 && (C_2 = fgetc(Stream_1), isspace(C_2)) )
      {
        n0x100_7 = sub_42B830(n255_7, v53, 24, 0, 0);
        n0x100_4 = n0x100_7;
        if ( v51[0].m128i_i8[1] == 51 )
        {
          n255 = 0;
          if ( v53 * n255_7 <= 0 )
            goto LABEL_20;
          while ( fscanf(Stream_1, "%d%d%d", &n0x100_1, &n0x100_2, &Stream_v) == 3 )
          {
            n0x100_8 = n0x100_1;
            if ( n0x100_1 >= 0x100 || n0x100_2 >= 0x100 || (unsigned int)Stream_v >= 0x100 )
              break;
            GIF8 = ((unsigned __int8)n0x100_2 << 8) | (unsigned __int8)Stream_v | GIF8 & 0xFFFF0000;
            n255_1 = n255;
            v12 = 3 * n255;
            *(_WORD *)((char *)n0x100_4 + v12 + 16) = GIF8;
            *((_BYTE *)n0x100_4 + v12 + 18) = n0x100_8;
            n255 = n255_1 + 1;
            if ( n255_1 + 1 >= v53 * n255_7 )
              goto LABEL_20;
          }
          return nullptr;
        }
        if ( fread(n0x100_7 + 4, 1u, n0x100_7[3], Stream_1) == n0x100_7[3] )
        {
          n0x100_3 = v53 * n255_7;
          n255_2 = 0;
          if ( v53 * n255_7 <= 0 )
          {
            n255 = 0;
          }
          else
          {
            if ( n0x100_3 / 2 )
            {
              n0x100_2 = v53 * n255_7;
              v15 = n0x100_3 / 2;
              Stream_v = Stream_1;
              v16 = 0;
              do
              {
                v17 = 3 * n255_2;
                v18 = *((_BYTE *)n0x100_4 + 3 * n255_2 + 18);
                *((_BYTE *)n0x100_4 + v17 + 18) = *((_BYTE *)n0x100_4 + v17 + 16);
                *((_BYTE *)n0x100_4 + v17 + 16) = v18;
                v19 = 6 * v16;
                v20 = *((_BYTE *)n0x100_4 + 6 * v16 + 21);
                *((_BYTE *)n0x100_4 + v19 + 21) = *((_BYTE *)n0x100_4 + 6 * v16 + 19);
                *((_BYTE *)n0x100_4 + v19 + 19) = v20;
                n255_2 = 2 * v16++ + 2;
              }
              while ( v16 < v15 );
              n0x100_3 = n0x100_2;
              Stream_1 = Stream_v;
              n255_3 = 2 * v16 + 1;
            }
            else
            {
              n255_3 = 1;
            }
            if ( n0x100_3 <= (unsigned int)(n255_3 - 1) )
            {
              n255 = n255_2;
            }
            else
            {
              n255 = n255_3;
              v22 = 3 * n255_2;
              v23 = *((_BYTE *)n0x100_4 + 3 * n255_2 + 18);
              *((_BYTE *)n0x100_4 + v22 + 18) = *((_BYTE *)n0x100_4 + 3 * n255_2 + 16);
              *((_BYTE *)n0x100_4 + v22 + 16) = v23;
            }
          }
          goto LABEL_20;
        }
        return nullptr;
      }
      else
      {
        return nullptr;
      }
    default:
      n0x100_4 = nullptr;
LABEL_20:
      fclose(Stream_1);
      return n0x100_4;
  }
}

// __usercall thunk for sub_42A4E0 @ 0x0042A4E0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_42A4E0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $24, %esp\n"
    "mov %edi, 8(%esp)\n"
    "push 8(%ebp)\n"
    "push 12(%esp)\n"
    "call __sub_42A4E0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef FILE
#undef fclose
#undef fgetc
#undef fopen
#undef fread
#undef fscanf
#undef sub_42B830
