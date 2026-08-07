// sub_4015C0 @ 0x004015C0 — __usercall
// Extracted from BMF.cpp:1163-1776 by extract.py per incdec.md.

typedef char t_sub_4015C0_Destination_;
static t_sub_4015C0_Destination_& __sub_4015C0_Destination_ = *(t_sub_4015C0_Destination_*)(blob1 + 0x00442960 - BMF_BLOB_BASE);
typedef const WCHAR t_sub_4015C0_SrcStr;
static t_sub_4015C0_SrcStr& __sub_4015C0_SrcStr = *(t_sub_4015C0_SrcStr*)(blob1 + 0x00439D64 - BMF_BLOB_BASE);
typedef int t_sub_4015C0_bmp_;
static t_sub_4015C0_bmp_& __sub_4015C0_bmp_ = *(t_sub_4015C0_bmp_*)(blob1 + 0x00441040 - BMF_BLOB_BASE);
typedef int t_sub_4015C0_bmp__0;
static t_sub_4015C0_bmp__0& __sub_4015C0_bmp__0 = *(t_sub_4015C0_bmp__0*)(blob1 + 0x00441048 - BMF_BLOB_BASE);
typedef int t_sub_4015C0_bmp__1;
static t_sub_4015C0_bmp__1& __sub_4015C0_bmp__1 = *(t_sub_4015C0_bmp__1*)(blob1 + 0x00441044 - BMF_BLOB_BASE);
typedef int t_sub_4015C0_dwLowDateTime;
static t_sub_4015C0_dwLowDateTime& __sub_4015C0_dwLowDateTime = *(t_sub_4015C0_dwLowDateTime*)(blob1 + 0x00442BB0 - BMF_BLOB_BASE);
typedef int t_sub_4015C0_dword_441098;
static t_sub_4015C0_dword_441098& __sub_4015C0_dword_441098 = *(t_sub_4015C0_dword_441098*)(blob1 + 0x00441098 - BMF_BLOB_BASE);
typedef int t_sub_4015C0_dword_442BA0;
static t_sub_4015C0_dword_442BA0& __sub_4015C0_dword_442BA0 = *(t_sub_4015C0_dword_442BA0*)(blob1 + 0x00442BA0 - BMF_BLOB_BASE);
typedef int t_sub_4015C0_dword_442BAC;
static t_sub_4015C0_dword_442BAC& __sub_4015C0_dword_442BAC = *(t_sub_4015C0_dword_442BAC*)(blob1 + 0x00442BAC - BMF_BLOB_BASE);
typedef int t_sub_4015C0_n2_5;
static t_sub_4015C0_n2_5& __sub_4015C0_n2_5 = *(t_sub_4015C0_n2_5*)(blob1 + 0x00442BA4 - BMF_BLOB_BASE);

#define exit_402E40 __exit_402E40
#define sub_4022C0 __sub_4022C0
static inline int * __fwd_sub_4015C0_sub_402590(void *a0) { return __sub_402590((char *)a0); }
#define sub_402590 __fwd_sub_4015C0_sub_402590
static inline int __fwd_sub_4015C0_sub_4028B0(void *a0, int a1, const __m128 &a2, const __m128 &a3) { return __sub_4028B0((char *)a0, a1, a2, a3); }
#define sub_4028B0 __fwd_sub_4015C0_sub_4028B0
static inline FILE1 ** __fwd_sub_4015C0_sub_402DF0(void *a0, char a1) { return __sub_402DF0((FILE1 **)a0, a1); }
#define sub_402DF0 __fwd_sub_4015C0_sub_402DF0
static inline int __fwd_sub_4015C0_sub_402EF0(void *a0, void *a1, int a2) { return __sub_402EF0((_DWORD *)a0, (char *)a1, a2); }
#define sub_402EF0 __fwd_sub_4015C0_sub_402EF0
static inline int __fwd_sub_4015C0_sub_402FE0(int a0, const __m128 &a1, const __m128 &a2, void *a3, void *a4) { return __sub_402FE0(a0, a1, a2, (unsigned __int16 *)a3, (void *)a4); }
#define sub_402FE0 __fwd_sub_4015C0_sub_402FE0
static inline char * __fwd_sub_4015C0_sub_403820(int a0, const __m128 &a1, const __m128 &a2, int a3, void *a4) { return __sub_403820(a0, a1, a2, a3, (int *)a4); }
#define sub_403820 __fwd_sub_4015C0_sub_403820
static inline unsigned __int16 * __fwd_sub_4015C0_sub_428C40(void *a0) { return __sub_428C40((char *)a0); }
#define sub_428C40 __fwd_sub_4015C0_sub_428C40
static inline int __fwd_sub_4015C0_sub_429840(void *a0, void *a1, int a2) { return __sub_429840((unsigned __int16 *)a0, (char *)a1, a2); }
#define sub_429840 __fwd_sub_4015C0_sub_429840
static inline int __fwd_sub_4015C0_sub_429C80(void *a0, int a1, void *a2) { return __sub_429C80((char *)a0, a1, (char *)a2); }
#define sub_429C80 __fwd_sub_4015C0_sub_429C80
static inline unsigned __int16 * __fwd_sub_4015C0_sub_429E80(void *a0) { return __sub_429E80((char *)a0); }
#define sub_429E80 __fwd_sub_4015C0_sub_429E80
static inline int __fwd_sub_4015C0_sub_42A350(void *a0, void *a1) { return __sub_42A350((unsigned __int16 *)a0, (char *)a1); }
#define sub_42A350 __fwd_sub_4015C0_sub_42A350
static inline int * __fwd_sub_4015C0_sub_42A4E0(unsigned int a0, void *a1) { return __sub_42A4E0(a0, (char *)a1); }
#define sub_42A4E0 __fwd_sub_4015C0_sub_42A4E0
static inline int * __fwd_sub_4015C0_sub_42AB20(void *a0) { return __sub_42AB20((char *)a0); }
#define sub_42AB20 __fwd_sub_4015C0_sub_42AB20
static inline int __fwd_sub_4015C0_sub_42B0C0(int a0, void *a1, int a2) { return __sub_42B0C0(a0, (char *)a1, a2); }
#define sub_42B0C0 __fwd_sub_4015C0_sub_42B0C0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL____access
#define __PE_DECL____access
typedef int t__access(const char *, int);   // __access
static t__access& ___access = *(t__access*)0x004314F0;
#endif
#define _access ___access
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
#ifndef __PE_DECL___printf
#define __PE_DECL___printf
typedef int t_printf(const char *, ...);   // _printf
static t_printf& __printf = *(t_printf*)0x0042CBDB;
#endif
#define printf __printf
#ifndef __PE_DECL___remove
#define __PE_DECL___remove
typedef int t_remove(const char *);   // _remove
static t_remove& __remove = *(t_remove*)0x0042CF23;
#endif
#define remove __remove
#ifndef __PE_DECL___sprintf
#define __PE_DECL___sprintf
typedef int t_sprintf(char *, const char *, ...);   // _sprintf
static t_sprintf& __sprintf = *(t_sprintf*)0x0042CF4D;
#endif
#define sprintf __sprintf
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

PROBE_DECL(__sub_4015C0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) void __sub_4015C0(const __m128 &a1__ref, const __m128 &a2__ref, const char *FileName, const char *cFileName)
{
  alignas(16) unsigned char __hexrays_frame[1852];   // original frame, ebp-0x72c..ebp+0x0
  int * &p_i_17 = *(int * *)(__hexrays_frame + 0);
  char &Format = *(char *)(__hexrays_frame + 8);
  char (&FileName_1)[4] = *(char (*)[4])(__hexrays_frame + 24);
  int * &p_i_5 = *(int * *)(__hexrays_frame + 28);
  int * &p_i_12 = *(int * *)(__hexrays_frame + 32);
  unsigned int &_bmp_ = *(unsigned int *)(__hexrays_frame + 36);
  PROBE_HIT(__sub_4015C0);
  __m128 a1 = a1__ref;
  __m128 a2 = a2__ref;
  Stream *Stream_v; // eax
  Stream *Stream_1; // ebp
  char *Buffer_1; // esi
  const char *GIF8; // edi
  int n4; // ecx
  bool v9; // cf
  bool v10; // zf
  unsigned __int16 *p_i_14; // eax
  unsigned __int16 *p_i_3; // esi
  char *Destination_3; // ecx
  int v14; // ebp
  int *p_i_15; // ecx
  char *v16; // edi
  int v17; // edx
  int v18; // eax
  int v19; // ebx
  unsigned int v20; // eax
  unsigned __int16 *p_i_10; // eax
  unsigned __int16 *p_i_1; // esi
  char *Destination_1; // ecx
  int v24; // ebp
  int *p_i_19; // ecx
  char *v26; // edi
  int v27; // edx
  int v28; // eax
  int v29; // ebx
  unsigned int v30; // eax
  int *p_i_18; // eax
  int *p_i_7; // esi
  char *Destination_5; // ecx
  int p_i_6; // ebp
  int v35; // ecx
  int v36; // edi
  char *v37; // edi
  int v38; // edx
  int v39; // ebx
  int v40; // ebp
  unsigned int v41; // eax
  int *p_i_11; // eax
  int *p_i_2; // esi
  char *Destination_2; // ecx
  int p_i_13; // ebp
  int v46; // ecx
  int v47; // edi
  char *v48; // edi
  int v49; // edx
  int v50; // ebx
  int v51; // ebp
  unsigned int v52; // eax
  int *p_i_8; // eax
  int *p_i; // esi
  char *Destination; // ecx
  int v56; // ebp
  int v57; // ecx
  int v58; // edi
  char *v59; // edi
  int v60; // edx
  int v61; // ebx
  int v62; // ebp
  unsigned int v63; // eax
  int v64; // ebp
  int *p_i_4; // esi
  BOOL v66; // ebx
  const char *p_SrcStr; // eax
  char v68; // bl
  char *Destination_4; // eax
  int n2; // ecx
  char *Buffer_2; // ebx
  char *FileName_7; // eax
  int *p_i_16; // edi
  int (__cdecl *sub_42B0C0)(int, char *, int); // [esp+20h] [ebp-704h]
  void *Block; // [esp+24h] [ebp-700h]
  char FileName_3[4]; // [esp+110h] [ebp-614h] BYREF
  int v83; // [esp+114h] [ebp-610h]
  int *p_i_9; // [esp+118h] [ebp-60Ch]
  unsigned int v85; // [esp+11Ch] [ebp-608h]
  char FileName_5[12]; // [esp+210h] [ebp-514h] BYREF
  char FileName_6[256]; // [esp+310h] [ebp-414h] BYREF
  char FileName_4[256]; // [esp+410h] [ebp-314h] BYREF
  char FileName_2[256]; // [esp+510h] [ebp-214h] BYREF
  char FileNamea[256]; // [esp+610h] [ebp-114h] BYREF
  char Buffer[20]; // [esp+710h] [ebp-14h] BYREF

  strcpy(FileNamea, FileName);
  strcat(FileNamea, cFileName);
  Stream_v = fopen(FileNamea, "rb");
  Stream_1 = Stream_v;
  if ( !Stream_v )
    exit_402E40(6, FileNamea);
  Buffer_1 = Buffer;
  if ( !fread(Buffer, 4u, 1u, Stream_v) )
    exit_402E40(3, FileNamea);
  fclose(Stream_1);
  if ( !__sub_4015C0_dword_442BAC )
  {
    GIF8 = "GIF8";
    n4 = 4;
    do
    {
      v9 = (unsigned __int8)*Buffer_1 < (unsigned int)*GIF8;
      v10 = *Buffer_1 == *GIF8;
      if ( *Buffer_1 != *GIF8 )
        break;
      ++Buffer_1;
      ++GIF8;
      v10 = --n4 == 0;
    }
    while ( n4 );
    if ( (!v9 && !v10) == v9 )
    {
      sub_4028B0(FileNamea, (int)FileNamea, a1, a2);
      goto LABEL_70;
    }
    if ( Buffer[0] != -127 )
    {
      if ( Buffer[0] == 66 && Buffer[1] == 77 )
      {
        p_i_8 = sub_42AB20(FileNamea);
        p_i = p_i_8;
        if ( !p_i_8 )
          exit_402E40(4);
        printf(
          "File %16s, image %dx%dx%d, size - %d:",
          FileNamea,
          *(unsigned __int16 *)p_i_8,
          *((unsigned __int16 *)p_i_8 + 1),
          *((_BYTE *)p_i_8 + 10) & 0x3F,
          p_i_8[3]);
        Destination = &__sub_4015C0_Destination_;
        if ( !__sub_4015C0_Destination_ )
          Destination = FileNamea;
        sub_429C80(Destination, (int)FileName_1, "bmf");
        if ( void *__nb = __op_new(8u) )
          v56 = sub_402EF0((_DWORD *)__nb, FileName_1, 0);
        else v56 = 0;
        v57 = *((unsigned __int8 *)p_i + 10);
        if ( (v57 & 0x80) != 0 )
        {
          if ( (v57 & 0x40) != 0 )
          {
            *((_BYTE *)p_i + 10) = v57 ^ 0x80;
          }
          else
          {
            v58 = p_i[3];
            v85 = 0x100u >> (v57 & 31);
            v59 = (char *)p_i + v58;
            if ( 1 << (v57 & 31) <= 0 )
            {
LABEL_117:
              *((_BYTE *)p_i + 10) = (v57 | 0x40) ^ 0x80;
            }
            else
            {
              *(_DWORD *)FileName_3 = v57;
              v83 = 0;
              v60 = 0;
              v61 = 0;
              p_i_9 = p_i;
              while ( 1 )
              {
                v62 = 3 * v61;
                if ( (unsigned __int8)v59[3 * v61 + 16] != v60
                  || (unsigned __int8)v59[v62 + 17] != v60
                  || (unsigned __int8)v59[v62 + 18] != v60 )
                {
                  break;
                }
                ++v61;
                v60 += v85;
                if ( v61 >= 1 << (v57 & 31) )
                {
                  LOBYTE(v57) = FileName_3[0];
                  ;
                  p_i = p_i_9;
                  goto LABEL_117;
                }
              }
              ;
              p_i = p_i_9;
            }
          }
        }
        v63 = sub_402FE0(v56, a1, a2, (unsigned __int16 *)p_i, __sub_4015C0_dwLowDateTime);
        if ( !v63 )
          exit_402E40(5, FileName_1);
        printf(
          "%6.3f bpp%s",
          (double)v63 * 8.0 / (double)(*((unsigned __int16 *)p_i + 1) * *(unsigned __int16 *)p_i),
          "\n");
        __op_delete(p_i);
        goto LABEL_70;
      }
      goto LABEL_10;
    }
    if ( Buffer[1] != -118 && Buffer[1] != -112 )
    {
LABEL_10:
      if ( *(_DWORD *)Buffer == 1504078485 || *(_DWORD *)Buffer == -1788172711 )
      {
        p_i_10 = sub_429E80(FileNamea);
        p_i_1 = p_i_10;
        if ( !p_i_10 )
          exit_402E40(4);
        printf(
          "File %16s, image %dx%dx%d, size - %d:",
          FileNamea,
          *p_i_10,
          p_i_10[1],
          p_i_10[5] & 0x3F,
          *((_DWORD *)p_i_10 + 3));
        Destination_1 = &__sub_4015C0_Destination_;
        if ( !__sub_4015C0_Destination_ )
          Destination_1 = FileNamea;
        sub_429C80(Destination_1, (int)FileName_2, "bmf");
        if ( void *__nb = __op_new(8u) )
          v24 = sub_402EF0((_DWORD *)__nb, FileName_2, 0);
        else v24 = 0;
        p_i_19 = (int *)*((unsigned __int8 *)p_i_1 + 10);
        if ( ((unsigned __int8)p_i_19 & 0x80) != 0 )
        {
          if ( ((unsigned __int8)p_i_19 & 0x40) != 0 )
          {
            *((_BYTE *)p_i_1 + 10) = (unsigned __int8)p_i_19 ^ 0x80;
          }
          else
          {
            _bmp_ = 0x100u >> ((char)p_i_19 & 31);
            v26 = (char *)p_i_1 + *((_DWORD *)p_i_1 + 3);
            if ( 1 << ((char)p_i_19 & 31) <= 0 )
            {
LABEL_47:
              *((_BYTE *)p_i_1 + 10) = ((unsigned __int8)p_i_19 | 0x40) ^ 0x80;
            }
            else
            {
              p_i_12 = p_i_19;
              *(_DWORD *)FileName_1 = 0;
              p_i_5 = (int *)p_i_1;
              v27 = 0;
              v28 = 0;
              while ( 1 )
              {
                v29 = 3 * v28;
                if ( (unsigned __int8)v26[3 * v28 + 16] != v27
                  || (unsigned __int8)v26[v29 + 17] != v27
                  || (unsigned __int8)v26[v29 + 18] != v27 )
                {
                  break;
                }
                ++v28;
                v27 += _bmp_;
                if ( v28 >= 1 << ((char)p_i_19 & 31) )
                {
                  LOBYTE(p_i_19) = (_BYTE)p_i_12;
                  ;
                  p_i_1 = (unsigned __int16 *)p_i_5;
                  goto LABEL_47;
                }
              }
              ;
              p_i_1 = (unsigned __int16 *)p_i_5;
            }
          }
        }
        v30 = sub_402FE0(v24, a1, a2, p_i_1, __sub_4015C0_dwLowDateTime);
        if ( !v30 )
          exit_402E40(5, FileName_2);
        printf("%6.3f bpp%s", (double)v30 * 8.0 / (double)(p_i_1[1] * *p_i_1), "\n");
        __op_delete(p_i_1);
      }
      else if ( Buffer[0] == 80 && Buffer[1] >= 49 && Buffer[1] <= 54 )
      {
        p_i_11 = sub_42A4E0((unsigned int)GIF8, FileNamea);
        p_i_2 = p_i_11;
        if ( !p_i_11 )
          exit_402E40(4);
        printf(
          "File %16s, image %dx%dx%d, size - %d:",
          FileNamea,
          *(unsigned __int16 *)p_i_11,
          *((unsigned __int16 *)p_i_11 + 1),
          *((_BYTE *)p_i_11 + 10) & 0x3F,
          p_i_11[3]);
        Destination_2 = &__sub_4015C0_Destination_;
        if ( !__sub_4015C0_Destination_ )
          Destination_2 = FileNamea;
        sub_429C80(Destination_2, (int)FileName_3, "bmf");
        if ( void *__nb = __op_new(8u) )
          p_i_13 = sub_402EF0((_DWORD *)__nb, FileName_3, 0);
        else p_i_13 = 0;
        v46 = *((unsigned __int8 *)p_i_2 + 10);
        if ( (v46 & 0x80) != 0 )
        {
          if ( (v46 & 0x40) != 0 )
          {
            *((_BYTE *)p_i_2 + 10) = v46 ^ 0x80;
          }
          else
          {
            v47 = p_i_2[3];
            _bmp_ = 0x100u >> (v46 & 31);
            v48 = (char *)p_i_2 + v47;
            if ( 1 << (v46 & 31) <= 0 )
            {
LABEL_93:
              *((_BYTE *)p_i_2 + 10) = (v46 | 0x40) ^ 0x80;
            }
            else
            {
              *(_DWORD *)FileName_1 = v46;
              p_i_5 = nullptr;
              v49 = 0;
              v50 = 0;
              p_i_12 = p_i_2;
              while ( 1 )
              {
                v51 = 3 * v50;
                if ( (unsigned __int8)v48[3 * v50 + 16] != v49
                  || (unsigned __int8)v48[v51 + 17] != v49
                  || (unsigned __int8)v48[v51 + 18] != v49 )
                {
                  break;
                }
                ++v50;
                v49 += _bmp_;
                if ( v50 >= 1 << (v46 & 31) )
                {
                  LOBYTE(v46) = FileName_1[0];
                  ;
                  p_i_2 = p_i_12;
                  goto LABEL_93;
                }
              }
              ;
              p_i_2 = p_i_12;
            }
          }
        }
        v52 = sub_402FE0(p_i_13, a1, a2, (unsigned __int16 *)p_i_2, __sub_4015C0_dwLowDateTime);
        if ( !v52 )
          exit_402E40(5, FileName_3);
        printf(
          "%6.3f bpp%s",
          (double)v52 * 8.0 / (double)(*((unsigned __int16 *)p_i_2 + 1) * *(unsigned __int16 *)p_i_2),
          "\n");
        __op_delete(p_i_2);
      }
      else
      {
        p_i_14 = sub_428C40(FileNamea);
        p_i_3 = p_i_14;
        if ( !p_i_14 )
          exit_402E40(4);
        printf(
          "File %16s, image %dx%dx%d, size - %d:",
          FileNamea,
          *p_i_14,
          p_i_14[1],
          p_i_14[5] & 0x3F,
          *((_DWORD *)p_i_14 + 3));
        Destination_3 = &__sub_4015C0_Destination_;
        if ( !__sub_4015C0_Destination_ )
          Destination_3 = FileNamea;
        sub_429C80(Destination_3, (int)FileName_4, "bmf");
        if ( void *__nb = __op_new(8u) )
          v14 = sub_402EF0((_DWORD *)__nb, FileName_4, 0);
        else v14 = 0;
        p_i_15 = (int *)*((unsigned __int8 *)p_i_3 + 10);
        if ( ((unsigned __int8)p_i_15 & 0x80) != 0 )
        {
          if ( ((unsigned __int8)p_i_15 & 0x40) != 0 )
          {
            *((_BYTE *)p_i_3 + 10) = (unsigned __int8)p_i_15 ^ 0x80;
          }
          else
          {
            _bmp_ = 0x100u >> ((char)p_i_15 & 31);
            v16 = (char *)p_i_3 + *((_DWORD *)p_i_3 + 3);
            if ( 1 << ((char)p_i_15 & 31) <= 0 )
            {
LABEL_28:
              *((_BYTE *)p_i_3 + 10) = ((unsigned __int8)p_i_15 | 0x40) ^ 0x80;
            }
            else
            {
              p_i_12 = p_i_15;
              *(_DWORD *)FileName_1 = 0;
              p_i_5 = (int *)p_i_3;
              v17 = 0;
              v18 = 0;
              while ( 1 )
              {
                v19 = 3 * v18;
                if ( (unsigned __int8)v16[3 * v18 + 16] != v17
                  || (unsigned __int8)v16[v19 + 17] != v17
                  || (unsigned __int8)v16[v19 + 18] != v17 )
                {
                  break;
                }
                ++v18;
                v17 += _bmp_;
                if ( v18 >= 1 << ((char)p_i_15 & 31) )
                {
                  LOBYTE(p_i_15) = (_BYTE)p_i_12;
                  ;
                  p_i_3 = (unsigned __int16 *)p_i_5;
                  goto LABEL_28;
                }
              }
              ;
              p_i_3 = (unsigned __int16 *)p_i_5;
            }
          }
        }
        v20 = sub_402FE0(v14, a1, a2, p_i_3, __sub_4015C0_dwLowDateTime);
        if ( !v20 )
          exit_402E40(5, FileName_4);
        printf("%6.3f bpp%s", (double)v20 * 8.0 / (double)(p_i_3[1] * *p_i_3), "\n");
        __op_delete(p_i_3);
      }
      goto LABEL_70;
    }
    if ( void *__nb = __op_new(8u) )
      Block = (void *)sub_402EF0((_DWORD *)__nb, FileNamea, 1);
    else Block = nullptr; printf("File %16s,\r", FileNamea);
    ;
    p_i_12 = nullptr;
    v64 = 0;
    while ( 1 )
    {
      p_i_4 = (_DWORD *)sub_403820((int)Block, a1, a2, 0, (int *)&__sub_4015C0_dwLowDateTime);
      if ( !p_i_4 )
      {
        printf("\n");
        if ( !*((_DWORD *)Block + 1) )
          exit_402E40(3, FileNamea);
        sub_402DF0((FILE **)Block, 1);
        goto LABEL_70;
      }
      v66 = __sub_4015C0_dwLowDateTime && *(_DWORD *)__sub_4015C0_dwLowDateTime == 256;
      ++v64;
      p_SrcStr = (const char *)&__sub_4015C0_SrcStr;
      if ( v66 )
        p_SrcStr = ", archived";
      printf(
        "File %16s, image %dx%dx%d, size - %d, number: %d%s\r",
        FileNamea,
        *(unsigned __int16 *)p_i_4,
        *((unsigned __int16 *)p_i_4 + 1),
        *((_BYTE *)p_i_4 + 10) & 0x3F,
        p_i_4[3],
        v64,
        p_SrcStr);
      if ( v66 )
      {
        sub_4022C0((int)p_i_4);
        goto LABEL_156;
      }
      v68 = *((_BYTE *)p_i_4 + 10);
      Destination_4 = &__sub_4015C0_Destination_;
      if ( !__sub_4015C0_Destination_ )
        Destination_4 = FileNamea;
      n2 = v68 & 0x3F;
      if ( __sub_4015C0_n2_5 )
        break;
      if ( n2 == 2 || n2 == 15 || n2 == 16 )
        goto LABEL_145;
      _bmp_ = __sub_4015C0_bmp_;                             // "bmp"
      sub_429C80(Destination_4, (int)FileName_5, (char *)__sub_4015C0_bmp_);// "bmp"
      sub_42B0C0 = ::sub_42B0C0;
LABEL_146:
      Buffer_2 = strrchr(FileName_5, 46);
      if ( Buffer_2 - FileName_5 > 4 )
      {
        FileName_7 = strrchr(FileName_5, 92);
        if ( !FileName_7 )
          FileName_7 = FileName_5;
        if ( Buffer_2 - FileName_7 > 4 )
          Buffer_2 = FileName_7 + 4;
      }
      if ( !_access(FileName_5, 0) )
      {
        p_i_16 = p_i_12;
        p_i_5 = p_i_4;
        *(_DWORD *)FileName_1 = v64;
        do
        {
          p_i_17 = p_i_16;
          p_i_16 = (int *)((char *)p_i_16 + 1);
          sprintf(Buffer_2, "%04.4d.%s", p_i_17, (const char *)_bmp_);
        }
        while ( !_access(FileName_5, 0) );
        p_i_4 = p_i_5;
        v64 = *(_DWORD *)FileName_1;
        p_i_12 = p_i_16;
      }
      if ( !sub_42B0C0((int)p_i_4, FileName_5, __sub_4015C0_dword_441098) )
        exit_402E40(5, FileName_5);
LABEL_156:
      __op_delete(__sub_4015C0_dwLowDateTime);
      __sub_4015C0_dwLowDateTime = 0;
      __op_delete(p_i_4);
    }
    if ( __sub_4015C0_n2_5 == 2 && n2 != 2 && n2 != 4 && n2 != 15 && n2 != 16 && n2 != 32 && ((v68 & 0x3Fu) > 8 || (v68 & 0x40) != 0) )
    {
      _bmp_ = __sub_4015C0_bmp__0;                           // "pnm"
      sub_429C80(Destination_4, (int)FileName_5, (char *)__sub_4015C0_bmp__0);// "pnm"
      sub_42B0C0 = (int (__cdecl *)(int, char *, int))sub_42A350;
      goto LABEL_146;
    }
LABEL_145:
    _bmp_ = __sub_4015C0_bmp__1;                             // "tga"
    sub_429C80(Destination_4, (int)FileName_5, (char *)__sub_4015C0_bmp__1);// "tga"
    sub_42B0C0 = (int (__cdecl *)(int, char *, int))sub_429840;
    goto LABEL_146;
  }
  p_i_18 = sub_402590(FileNamea);
  p_i_7 = p_i_18;
  if ( !p_i_18 )
    exit_402E40(4);
  printf(
    "File %16s, image %dx%dx%d, size - %d:",
    FileNamea,
    *(unsigned __int16 *)p_i_18,
    *((unsigned __int16 *)p_i_18 + 1),
    *((_BYTE *)p_i_18 + 10) & 0x3F,
    p_i_18[3]);
  Destination_5 = &__sub_4015C0_Destination_;
  if ( !__sub_4015C0_Destination_ )
    Destination_5 = FileNamea;
  sub_429C80(Destination_5, (int)FileName_6, "bmf");
  if ( void *__nb = __op_new(8u) )
    p_i_6 = sub_402EF0((_DWORD *)__nb, FileName_6, 0);
  else p_i_6 = 0;
  v35 = *((unsigned __int8 *)p_i_7 + 10);
  if ( (v35 & 0x80) != 0 )
  {
    if ( (v35 & 0x40) != 0 )
    {
      *((_BYTE *)p_i_7 + 10) = v35 ^ 0x80;
    }
    else
    {
      v36 = p_i_7[3];
      _bmp_ = 0x100u >> (v35 & 31);
      v37 = (char *)p_i_7 + v36;
      if ( 1 << (v35 & 31) <= 0 )
      {
LABEL_67:
        *((_BYTE *)p_i_7 + 10) = (v35 | 0x40) ^ 0x80;
      }
      else
      {
        *(_DWORD *)FileName_1 = v35;
        p_i_5 = nullptr;
        v38 = 0;
        v39 = 0;
        p_i_12 = p_i_7;
        while ( 1 )
        {
          v40 = 3 * v39;
          if ( (unsigned __int8)v37[3 * v39 + 16] != v38
            || (unsigned __int8)v37[v40 + 17] != v38
            || (unsigned __int8)v37[v40 + 18] != v38 )
          {
            break;
          }
          ++v39;
          v38 += _bmp_;
          if ( v39 >= 1 << (v35 & 31) )
          {
            LOBYTE(v35) = FileName_1[0];
            ;
            p_i_7 = p_i_12;
            goto LABEL_67;
          }
        }
        ;
        p_i_7 = p_i_12;
      }
    }
  }
  v41 = sub_402FE0(p_i_6, a1, a2, (unsigned __int16 *)p_i_7, __sub_4015C0_dwLowDateTime);
  if ( !v41 )
    exit_402E40(5, FileName_6);
  printf(
    "%6.3f bpp%s",
    (double)v41 * 8.0 / (double)(*((unsigned __int16 *)p_i_7 + 1) * *(unsigned __int16 *)p_i_7),
    "\n");
  __op_delete(p_i_7);
  __op_delete(__sub_4015C0_dwLowDateTime);
  __sub_4015C0_dwLowDateTime = 0;
LABEL_70:
  if ( __sub_4015C0_dword_442BA0 )
    remove(FileNamea);
}

#ifndef BMF_STANDALONE
// __usercall thunk for sub_4015C0 @ 0x004015C0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_4015C0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $32, %esp\n"
    "movups %xmm1, 0(%esp)\n"
    "movups %xmm3, 16(%esp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "lea 24(%esp), %eax\n"
    "push %eax\n"
    "lea 12(%esp), %eax\n"
    "push %eax\n"
    "call __sub_4015C0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}
#endif

#undef FILE
#undef _access
#undef fclose
#undef fopen
#undef fread
#undef printf
#undef remove
#undef sprintf
#undef exit_402E40
#undef sub_4022C0
#undef sub_402590
#undef sub_4028B0
#undef sub_402DF0
#undef sub_402EF0
#undef sub_402FE0
#undef sub_403820
#undef sub_428C40
#undef sub_429840
#undef sub_429C80
#undef sub_429E80
#undef sub_42A350
#undef sub_42A4E0
#undef sub_42AB20
#undef sub_42B0C0
