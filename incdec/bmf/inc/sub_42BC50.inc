// sub_42BC50 @ 0x0042BC50 — __userpurge
// Extracted from BMF.c:36265-36512 by extract.py per incdec.md.

#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL____access
#define __PE_DECL____access
typedef int t__access(const char *, int);   // __access
static t__access& ___access = *(t__access*)0x004314F0;
#endif
#define _access ___access
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
#ifndef __PE_DECL___fputc
#define __PE_DECL___fputc
typedef int t_fputc(int, FILE1 *);   // _fputc
static t_fputc& __fputc = *(t_fputc*)0x0042D0A9;
#endif
#define fputc __fputc
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
#ifndef __PE_DECL___fwrite
#define __PE_DECL___fwrite
typedef unsigned int t_fwrite(const void *, unsigned int, unsigned int, FILE1 *);   // _fwrite
static t_fwrite& __fwrite = *(t_fwrite*)0x0042CF9F;
#endif
#define fwrite __fwrite
#define FILE FILE1

PROBE_DECL(__sub_42BC50)
extern "C" __attribute__((visibility("hidden"))) int __sub_42BC50(int a1, int a2, char a3, char *FileName)
{
  alignas(16) unsigned char __hexrays_frame[344];   // original frame, ebp-0x148..ebp+0x0
  Stream * &Stream_v = *(Stream * *)(__hexrays_frame + 0);
  unsigned int &Buffer_ = *(unsigned int *)(__hexrays_frame + 4);
  void * &Buffer_2 = *(void * *)(__hexrays_frame + 8);
  unsigned int &v45 = *(unsigned int *)(__hexrays_frame + 12);
  unsigned int &ElementCount_8 = *(unsigned int *)(__hexrays_frame + 260);
  int &n44_1 = *(int *)(__hexrays_frame + 264);
  char (&Buffer_4)[16] = *(char (*)[16])(__hexrays_frame + 268);
  char (&Buffer)[12] = *(char (*)[12])(__hexrays_frame + 284);
  size_t &v50 = *(size_t *)(__hexrays_frame + 296);
  char (&Buffer_3)[8] = *(char (*)[8])(__hexrays_frame + 300);
  int &v52 = *(int *)(__hexrays_frame + 308);
  PROBE_HIT(__sub_42BC50);
  int v4; // edi
  void *Buffer_1; // ebp
  Stream *Stream_1; // eax
  unsigned __int8 n44; // al
  int n44_2; // ebp
  int v9; // eax
  size_t ElementCount_1; // eax
  int ElementCount_6; // ebx
  int v12; // eax
  size_t ElementCount_2; // eax
  size_t ElementCount; // eax
  int ElementCount_5; // ebx
  char v16; // cl
  size_t ElementCount_3; // eax
  int ElementCount_7; // ebx
  size_t ElementCount_4; // ebx
  int v21; // esi
  size_t v22; // ebp
  int v23; // eax
  int v24; // edi
  char v25; // dl
  int v26; // ebx
  char v27; // cl
  bool v28; // cf
  size_t v29; // edx
  int v30; // ebx
  char v31; // al
  unsigned int Buffer__1; // esi
  unsigned int v33; // edx
  int v34; // eax
  int v35; // ebp
  char v36; // bl
  char v37; // cl
  char v38; // bl
  int v39; // edx
  int v40; // ecx
  char v41; // al

  v4 = a1;
  Buffer_1 = (void *)(a1 + 26);
  sub_4349F0((char *)(a1 + 26),0,1536);
  if ( _access(FileName, 0) == -1 )
  {
    *(_DWORD *)v4 = fopen(FileName, "w+b");
    *(_QWORD *)(v4 + 4) = 0;
    *(_DWORD *)(v4 + 12) = 0;
    *(_BYTE *)(v4 + 16) = 0;
    *(_WORD *)(v4 + 8) = 24887;
    *(_DWORD *)(v4 + 4) = 944130375;
    Stream_v = *(FILE **)v4;
    *(_BYTE *)(v4 + 14) = 119;
    *(_BYTE *)(v4 + 16) = 0;
    *(_DWORD *)(v4 + 10) = 50332672;
    *(_BYTE *)(v4 + 15) = 0;
    fwrite((const void *)(v4 + 4), 1u, 0xDu, Stream_v);
    fputc(59, *(FILE **)v4);
    *(_DWORD *)(v4 + 1564) = 1;
    return v4;
  }
  Stream_1 = fopen(FileName, "r+b");
  *(_DWORD *)v4 = Stream_1;
  fseek(Stream_1, 0, 0);
  fread((void *)(v4 + 4), 0xDu, 1u, *(FILE **)v4);
  if ( (*(_BYTE *)(v4 + 14) & 0x80) != 0 )
  {
    Buffer__1 = 1 << ((*(_BYTE *)(v4 + 14) & 7) + 1);
    fread(Buffer_1, 1u, 3 * Buffer__1, *(FILE **)v4);
    if ( Buffer__1 >> 1 )
    {
      v45 = Buffer__1 >> 1;
      Buffer_ = Buffer__1;
      Buffer_2 = Buffer_1;
      v52 = v4;
      v33 = 0;
      v34 = 0;
      v35 = 3 * Buffer__1 + v4 + 26;
      do
      {
        v36 = *(_BYTE *)(v34 + v35 - 1);
        *(_BYTE *)(v34 + v35 - 1) = *(_BYTE *)(v34 + v35 - 3);
        v37 = *(_BYTE *)(v34 + v35 - 6);
        ++v33;
        *(_BYTE *)(v34 + v35 - 3) = v36;
        v38 = *(_BYTE *)(v34 + v35 - 4);
        *(_BYTE *)(v34 + v35 - 4) = v37;
        *(_BYTE *)(v34 + v35 - 6) = v38;
        v34 -= 6;
      }
      while ( v33 < v45 );
      Buffer__1 = Buffer_;
      Buffer_1 = Buffer_2;
      v4 = v52;
      v39 = 2 * v33 + 1;
    }
    else
    {
      v39 = 1;
    }
    if ( Buffer__1 > v39 - 1 )
    {
      v40 = 3 * (Buffer__1 - v39);
      v41 = *((_BYTE *)Buffer_1 + v40 + 2);
      *((_BYTE *)Buffer_1 + v40 + 2) = *((_BYTE *)Buffer_1 + v40);
      *((_BYTE *)Buffer_1 + v40) = v41;
    }
  }
  *(_DWORD *)(v4 + 1564) = 0;
  while ( 1 )
  {
    n44 = fgetc(*(FILE **)v4);
    n44_2 = n44;
    if ( n44 == 44 )
      break;
    if ( !n44 )
      goto LABEL_14;
    if ( n44 != 33 )
      goto LABEL_24;
    v9 = fgetc(*(FILE **)v4);
    if ( v9 != 1 )
    {
      switch ( v9 )
      {
        case 249:
          if ( fread(Buffer_3, 6u, 1u, *(FILE **)v4) != 1 )
            goto LABEL_20;
          break;
        case 254:
          do
          {
            ElementCount = fgetc(*(FILE **)v4);
            ElementCount_5 = ElementCount;
            if ( ElementCount == -1 )
              break;
            fread(&Buffer_, 1u, ElementCount, *(FILE **)v4);
          }
          while ( ElementCount_5 > 0 );
          v12 = *(_DWORD *)(v4 + 1564);
          goto LABEL_26;
        case 255:
          if ( fread(Buffer, 0xCu, 1u, *(FILE **)v4) != 1 )
            goto LABEL_20;
          do
          {
            ElementCount_1 = fgetc(*(FILE **)v4);
            ElementCount_6 = ElementCount_1;
            if ( ElementCount_1 == -1 )
              break;
            fread(&Buffer_, 1u, ElementCount_1, *(FILE **)v4);
          }
          while ( ElementCount_6 > 0 );
          break;
        default:
          ElementCount_2 = fgetc(*(FILE **)v4);
          fread(&Buffer_, 1u, ElementCount_2, *(FILE **)v4);
          v12 = *(_DWORD *)(v4 + 1564);
          goto LABEL_26;
      }
LABEL_14:
      v12 = *(_DWORD *)(v4 + 1564);
      goto LABEL_26;
    }
    if ( fread(Buffer_4, 0xDu, 1u, *(FILE **)v4) != 1 )
      goto LABEL_20;
    do
    {
      ElementCount_3 = fgetc(*(FILE **)v4);
      ElementCount_7 = ElementCount_3;
      if ( ElementCount_3 == -1 )
        break;
      fread(&Buffer_, 1u, ElementCount_3, *(FILE **)v4);
    }
    while ( ElementCount_7 > 0 );
    v12 = *(_DWORD *)(v4 + 1564);
LABEL_26:
    if ( v12 )
      return v4;
  }
  if ( fread((void *)(v4 + 17), 9u, 1u, *(FILE **)v4) != 1 )
  {
LABEL_20:
    *(_DWORD *)(v4 + 1564) = 1;
    return v4;
  }
  v16 = *(_BYTE *)(v4 + 25);
  if ( v16 < 0 )
  {
    ElementCount_4 = 1 << ((v16 & 7) + 1);
    v21 = v4 + 794;
    if ( fread((void *)(v4 + 794), 3u, ElementCount_4, *(FILE **)v4) == ElementCount_4 )
    {
      v50 = ElementCount_4 >> 1;
      ElementCount_8 = ElementCount_4;
      n44_1 = 44;
      v22 = ElementCount_4 - 1;
      v52 = v4;
      v23 = 0;
      do
      {
        v24 = 3 * v22;
        v25 = *(_BYTE *)(3 * v22 + v21 + 2);
        *(_BYTE *)(v24 + v21 + 2) = *(_BYTE *)(3 * v22 + v21);
        v26 = 3 * v22 - 3;
        v27 = *(_BYTE *)(v26 + v21 + 2);
        *(_BYTE *)(v24 + v21) = v25;
        v22 -= 2;
        v28 = ++v23 < v50;
        *(_BYTE *)(v26 + v21 + 2) = *(_BYTE *)(v26 + v21);
        *(_BYTE *)(v26 + v21) = v27;
      }
      while ( v28 );
      v4 = v52;
      v29 = v22;
      n44_2 = n44_1;
      if ( ElementCount_8 > 2 * v23 )
      {
        v30 = 3 * v29;
        v31 = *(_BYTE *)(3 * v29 + v21 + 2);
        *(_BYTE *)(v30 + v21 + 2) = *(_BYTE *)(3 * v29 + v21);
        *(_BYTE *)(v30 + v21) = v31;
      }
      goto LABEL_23;
    }
    *(_DWORD *)(v4 + 1564) = 1;
  }
  else
  {
LABEL_23:
    if ( n44_2 == 44 )
      *(_DWORD *)(v4 + 1564) = 0;
    else
LABEL_24:
      *(_DWORD *)(v4 + 1564) = 1;
  }
  return v4;
}

// __userpurge thunk for sub_42BC50 @ 0x0042BC50: reads the register arguments the
// caller passes, calls the moved body as cdecl, and pops 4 bytes of
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_42BC50()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $16, %esp\n"
    "mov %ecx, 0(%esp)\n"
    "mov %ebx, 4(%esp)\n"
    "fnstsw %ax\n"
    "mov %eax, 8(%esp)\n"
    "push 8(%ebp)\n"
    "push 12(%esp)\n"
    "push 12(%esp)\n"
    "push 12(%esp)\n"
    "call __sub_42BC50\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret $4\n"
  );
}

#undef FILE
#undef _access
#undef fgetc
#undef fopen
#undef fputc
#undef fread
#undef fseek
#undef fwrite
#undef sub_4349F0
