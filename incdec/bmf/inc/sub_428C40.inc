// sub_428C40 @ 0x00428C40 — __cdecl
// Extracted from BMF.c:33162-33667 by extract.py per incdec.md.

#ifndef __PE_DECL___sub_428AA0
#define __PE_DECL___sub_428AA0
typedef int t_sub_428AA0(...);
static t_sub_428AA0& __sub_428AA0 = *(t_sub_428AA0*)0x00428AA0;
#endif
#define sub_428AA0 __sub_428AA0
#ifndef __PE_DECL___sub_428B00
#define __PE_DECL___sub_428B00
typedef int t_sub_428B00(...);
static t_sub_428B00& __sub_428B00 = *(t_sub_428B00*)0x00428B00;
#endif
#define sub_428B00 __sub_428B00
#ifndef __PE_DECL___sub_428B60
#define __PE_DECL___sub_428B60
typedef int t_sub_428B60(...);
static t_sub_428B60& __sub_428B60 = *(t_sub_428B60*)0x00428B60;
#endif
#define sub_428B60 __sub_428B60
#ifndef __PE_DECL___sub_428BE0
#define __PE_DECL___sub_428BE0
typedef int t_sub_428BE0(...);
static t_sub_428BE0& __sub_428BE0 = *(t_sub_428BE0*)0x00428BE0;
#endif
#define sub_428BE0 __sub_428BE0
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
#define sub_42B990 __sub_42B990
static inline unsigned int __fwd_sub_428C40_sub_42BA40(void *a0, int a1, int a2, int a3, int a4) { return __sub_42BA40((_WORD *)a0, a1, a2, a3, a4); }
#define sub_42BA40 __fwd_sub_428C40_sub_42BA40

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
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
#ifndef __PE_DECL___ftell
#define __PE_DECL___ftell
typedef long t_ftell(FILE1 *);   // _ftell
static t_ftell& __ftell = *(t_ftell*)0x0042DD8C;
#endif
#define ftell __ftell
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

PROBE_DECL(__sub_428C40)
unsigned __int16 *__sub_428C40(char *FileName)
{
  PROBE_HIT(__sub_428C40);
  Stream *Stream_v; // esi
  unsigned __int8 n3_1; // al
  int n5; // ebx
  char *buf; // ebp
  int Size_1; // edi
  char v6; // fps
  int FileHandle; // eax
  int v8; // edi
  size_t Size_2; // edi
  char v11; // fps
  char *v12; // ebx
  char *Src_4; // ebp
  int sub_428BE0_3; // esi
  void *sub_428BE0; // edx
  size_t Size_3; // edx
  char *v17; // ecx
  char *v18; // ebp
  char *Src_3; // esi
  int sub_428BE0_4; // ebx
  size_t Size_5; // edi
  void *Src_1; // edx
  unsigned int Src_2; // eax
  int buf_2; // edx
  int *Buffer_8; // eax
  char v26; // fps
  unsigned __int16 *Buffer_4; // esi
  char *v28; // ecx
  void *Buffer_2; // edx
  char *v30; // ebp
  int Buffer_5; // ecx
  int Buffer_3; // edx
  size_t v33; // ecx
  size_t v34; // eax
  char *v35; // edx
  int v36; // edi
  char *v37; // ebx
  int v38; // esi
  int v39; // edi
  int v40; // edx
  char *v41; // eax
  int v42; // edi
  unsigned int v43; // eax
  int v44; // edi
  __int16 v45; // si
  char v46; // dl
  char *v47; // ebx
  size_t v48; // ecx
  size_t v49; // edx
  char *v50; // eax
  char *v51; // ebx
  __int16 v52; // si
  __int16 v53; // di
  __int16 v54; // si
  int v55; // edx
  char *v56; // eax
  __int16 v57; // di
  size_t v58; // eax
  int v59; // esi
  char *v60; // edi
  char v61; // bl
  char v62; // cl
  char v63; // dl
  int v64; // edi
  char v65; // al
  char *v66; // ebx
  char *v67; // edi
  int Buffer_12; // eax
  _BYTE *v69; // edx
  int Buffer_6; // ecx
  int Buffer_7; // ebp
  int Buffer_11; // ecx
  int Buffer_10; // eax
  size_t v74; // ecx
  int i; // ebx
  bool v76; // sf
  size_t v77; // ebp
  int v78; // eax
  char v79; // fps
  int sub_428BE0_1; // [esp+0h] [ebp-6Ch] BYREF
  void *Src; // [esp+4h] [ebp-68h]
  size_t Size_6; // [esp+Ch] [ebp-60h]
  void *Buffer_1; // [esp+10h] [ebp-5Ch]
  int Buffer_9; // [esp+14h] [ebp-58h]
  size_t v85; // [esp+18h] [ebp-54h]
  size_t Size_4; // [esp+1Ch] [ebp-50h]
  char *buf_1; // [esp+20h] [ebp-4Ch]
  size_t v88; // [esp+24h] [ebp-48h]
  char *v89; // [esp+28h] [ebp-44h]
  char *v90; // [esp+2Ch] [ebp-40h]
  int v91; // [esp+30h] [ebp-3Ch]
  signed int v92; // [esp+34h] [ebp-38h]
  char *v93; // [esp+38h] [ebp-34h]
  char *v94; // [esp+3Ch] [ebp-30h]
  size_t Size; // [esp+40h] [ebp-2Ch]
  char Buffer[2]; // [esp+44h] [ebp-28h] BYREF
  unsigned __int8 n3; // [esp+46h] [ebp-26h]
  unsigned __int16 v98; // [esp+47h] [ebp-25h]
  unsigned __int16 ElementCount; // [esp+49h] [ebp-23h]
  char n24; // [esp+4Bh] [ebp-21h]
  unsigned __int16 v101; // [esp+50h] [ebp-1Ch]
  unsigned __int16 sub_428BE0_2; // [esp+52h] [ebp-1Ah]
  unsigned __int8 n0x20; // [esp+54h] [ebp-18h]
  char v104; // [esp+55h] [ebp-17h]
  int n5_1; // [esp+58h] [ebp-14h]

  Stream_v = fopen(FileName, "rb");
  fread(Buffer, 0x12u, 1u, Stream_v);
  if ( !Stream_v )
    return nullptr;
  n3_1 = n3;
  if ( !n3 || n3 > 3u && (n3 < 9u || n3 > 0xBu) )
    return nullptr;
  n5 = n0x20;
  if ( n0x20 > 0x20u || (v104 & 0xC0) != 0 || n24 && n24 != 24 )
    return nullptr;
  if ( ElementCount && n0x20 > 8u )
    return nullptr;
  if ( Buffer[0] )
  {
    fseek(Stream_v, (unsigned __int8)Buffer[0], 1);
    n3_1 = n3;
  }
  if ( (n3_1 & 3) == 3 && (n5 >= 5 && n5 <= 7 || n5 == 3) )
  {
    n3 = n3_1 - 2;
    buf = (char *)__op_new(3 * (1 << n5));
    sub_42B990(n5, (int)buf);
    ElementCount = 1 << n5;
  }
  else if ( ElementCount )
  {
    buf = (char *)__op_new(3 * (1 << n5));
    Size_1 = 3 * v98;
    sub_4349F0(buf,0,Size_1);
    fread(&buf[Size_1], 3u, ElementCount, Stream_v);
    ElementCount += v98;
  }
  else
  {
    buf = nullptr;
  }
  Size = ((unsigned int)(n5 + 7) >> 3) * v101;
  v94 = (char *)__op_new(Size * sub_428BE0_2);
  FileHandle = _fileno(Stream_v);
  v8 = _filelength(FileHandle);
  Size_2 = v8 - ftell(Stream_v);
  Buffer_1 = __op_new(Size_2);
  if ( fread(Buffer_1, 1u, Size_2, Stream_v) != Size_2 )
    return nullptr;
  fclose(Stream_v);
  Src = Buffer_1;
  if ( n3 > 3u )
  {
    if ( n5 > 8 )
    {
      if ( n5 > 16 )
      {
        sub_428BE0 = ::sub_428BE0;
        if ( n5 == 24 )
          sub_428BE0 = sub_428B60;
        sub_428BE0_1 = (int)sub_428BE0;
      }
      else
      {
        sub_428BE0_1 = (int)sub_428B00;
      }
    }
    else
    {
      sub_428BE0_1 = (int)sub_428AA0;
    }
    buf_1 = buf;
    n5_1 = n5;
    Size_3 = -Size;
    v17 = &v94[Size * (sub_428BE0_2 - 1)];
    if ( (v104 & 0x20) != 0 )
    {
      v17 = v94;
      Size_3 = Size;
    }
    n5 = n5_1;
    buf = buf_1;
    if ( sub_428BE0_2 )
    {
      v18 = v17;
      Size_4 = Size_2;
      Src_3 = (char *)Buffer_1 + Size_2;
      sub_428BE0_4 = 0;
      Size_5 = Size_3;
      Src_1 = Src;
      while ( 1 )
      {
        Src_2 = ((int (__cdecl *)(char *, void *, _DWORD))sub_428BE0_1)(v18, Src_1, v101);
        Src_1 = (void *)Src_2;
        if ( !Src_2 || Src_2 > (unsigned int)Src_3 )
          return nullptr;
        ++sub_428BE0_4;
        v18 += Size_5;
        if ( sub_428BE0_4 >= sub_428BE0_2 )
          goto LABEL_40;
      }
    }
  }
  else if ( (v104 & 0x20) != 0 )
  {
    sub_42BA40(&sub_428BE0_1, v101, sub_428BE0_2, n5, 1);
    if ( Size_2 < Size_6 )
      return nullptr;
    sub_434980(v94,(char *)Buffer_1,Size_2);
  }
  else if ( sub_428BE0_2 )
  {
    n5_1 = n5;
    v12 = &v94[Size * (sub_428BE0_2 - 1)];
    buf_1 = buf;
    Src_4 = (char *)Src;
    sub_428BE0_3 = 0;
    sub_428BE0_1 = sub_428BE0_2;
    Size_4 = Size_2;
    do
    {
      sub_434980(v12,Src_4,Size);
      v12 -= Size;
      Src_4 += Size;
      ++sub_428BE0_3;
    }
    while ( sub_428BE0_3 < sub_428BE0_1 );
LABEL_40:
    n5 = n5_1;
    buf = buf_1;
    Size_2 = Size_4;
  }
  __op_delete(Buffer_1);
  buf_2 = (int)buf;
  if ( buf )
    buf_2 = 1;
  Buffer_8 = sub_42B830(v101, sub_428BE0_2, n5, buf_2, 1);
  Buffer_4 = (unsigned __int16 *)Buffer_8;
  if ( buf )
  {
    if ( (*((_BYTE *)Buffer_8 + 10) & 0x80) != 0 )
      v28 = (char *)Buffer_8 + Buffer_8[3] + 16;
    else
      v28 = nullptr;
    sub_434980(v28,buf,3 * ElementCount);
  }
  else if ( (n3 & 3) == 3 )
  {
    *((_BYTE *)Buffer_8 + 10) |= 0x40u;
  }
  if ( (v104 & 0x10) != 0 )
  {
    Buffer_2 = (void *)Buffer_4[1];
    v89 = v94;
    Buffer_1 = Buffer_2;
    if ( Buffer_2 )
    {
      v92 = Size >> 1;
      buf_1 = buf;
      v30 = v89;
      Buffer_9 = 0;
      Size_4 = Size_2;
      v88 = Size >> 2;
      Buffer_5 = 0;
      v85 = 3 * Size;
      Buffer_3 = (int)Buffer_1;
      while ( 1 )
      {
        ++Buffer_5;
        if ( n5 == 32 )
        {
          if ( v92 > 0 )
          {
            if ( v88 )
            {
              n5_1 = 32;
              Buffer_9 = Buffer_5;
              v33 = v88;
              Buffer_1 = Buffer_4;
              v34 = 0;
              v35 = &v30[4 * Size];
              do
              {
                v36 = *(_DWORD *)&v30[8 * v34];
                v37 = &v35[-8 * v34];
                *(_DWORD *)&v30[8 * v34] = *((_DWORD *)v37 - 1);
                v38 = *((_DWORD *)v37 - 2);
                *((_DWORD *)v37 - 1) = v36;
                v39 = *(_DWORD *)&v30[8 * v34 + 4];
                *(_DWORD *)&v30[8 * v34 + 4] = v38;
                *((_DWORD *)v37 - 2) = v39;
                ++v34;
              }
              while ( v34 < v33 );
              n5 = n5_1;
              Buffer_5 = Buffer_9;
              Buffer_4 = (unsigned __int16 *)Buffer_1;
              v40 = 2 * v34 + 1;
            }
            else
            {
              v40 = 1;
            }
            if ( v40 - 1 < (unsigned int)v92 )
            {
              n5_1 = n5;
              v41 = &v30[4 * Size + -4 * v40];
              v42 = *(_DWORD *)&v30[4 * v40 - 4];
              *(_DWORD *)&v30[4 * v40 - 4] = *(_DWORD *)v41;
              n5 = n5_1;
              *(_DWORD *)v41 = v42;
            }
LABEL_81:
            Buffer_3 = Buffer_4[1];
          }
        }
        else
        {
          if ( n5 == 24 )
          {
            if ( v92 > 0 )
            {
              n5_1 = 24;
              Buffer_9 = Buffer_5;
              v43 = 0;
              Buffer_1 = Buffer_4;
              v93 = &v30[v85];
              do
              {
                v44 = 3 * v43;
                v45 = *(_WORD *)&v30[3 * v43];
                v46 = v30[3 * v43 + 2];
                v47 = &v93[-3 * v43];
                *(_WORD *)&v30[v44] = *(_WORD *)(v47 - 3);
                v30[v44 + 2] = *(v47 - 1);
                *(_WORD *)(v47 - 3) = v45;
                *(v47 - 1) = v46;
                ++v43;
              }
              while ( v43 < v92 );
              n5 = n5_1;
              Buffer_5 = Buffer_9;
              Buffer_4 = (unsigned __int16 *)Buffer_1;
              Buffer_3 = *((unsigned __int16 *)Buffer_1 + 1);
            }
            goto LABEL_82;
          }
          if ( n5 < 15 )
          {
            if ( v92 > 0 )
            {
              if ( v88 )
              {
                n5_1 = n5;
                Buffer_9 = Buffer_5;
                v58 = 0;
                v89 = v30;
                Buffer_1 = Buffer_4;
                v90 = &v30[Size];
                do
                {
                  v30 = v89;
                  v59 = 2 * v58;
                  v60 = &v90[-2 * v58];
                  v61 = *(v60 - 2);
                  v91 = (unsigned __int8)v89[2 * v58];
                  v89[v59] = *(v60 - 1);
                  v62 = v30[2 * v58 + 1];
                  v63 = v91;
                  v30[v59 + 1] = v61;
                  *(v60 - 1) = v63;
                  *(v60 - 2) = v62;
                  ++v58;
                }
                while ( v58 < v88 );
                n5 = n5_1;
                Buffer_5 = Buffer_9;
                Buffer_4 = (unsigned __int16 *)Buffer_1;
                v64 = 2 * v58 + 1;
              }
              else
              {
                v64 = 1;
              }
              if ( v64 - 1 < (unsigned int)v92 )
              {
                v65 = v30[v64 - 1];
                n5_1 = n5;
                v66 = &v30[Size - v64];
                v30[v64 - 1] = *v66;
                *v66 = v65;
                n5 = n5_1;
              }
              goto LABEL_81;
            }
          }
          else if ( v92 > 0 )
          {
            if ( v88 )
            {
              n5_1 = n5;
              Buffer_9 = Buffer_5;
              v48 = v88;
              Buffer_1 = Buffer_4;
              v49 = 0;
              v50 = &v30[2 * Size];
              do
              {
                v51 = &v50[-4 * v49];
                v52 = *((_WORD *)v51 - 1);
                *((_WORD *)v51 - 1) = *(_WORD *)&v30[4 * v49];
                v53 = *(_WORD *)&v30[4 * v49 + 2];
                *(_WORD *)&v30[4 * v49] = v52;
                v54 = *((_WORD *)v51 - 2);
                *((_WORD *)v51 - 2) = v53;
                *(_WORD *)&v30[4 * v49++ + 2] = v54;
              }
              while ( v49 < v48 );
              n5 = n5_1;
              Buffer_5 = Buffer_9;
              Buffer_4 = (unsigned __int16 *)Buffer_1;
              v55 = 2 * v49 + 1;
            }
            else
            {
              v55 = 1;
            }
            if ( v55 - 1 < (unsigned int)v92 )
            {
              n5_1 = n5;
              v56 = &v30[2 * Size + -2 * v55];
              v57 = *(_WORD *)&v30[2 * v55 - 2];
              *(_WORD *)&v30[2 * v55 - 2] = *(_WORD *)v56;
              n5 = n5_1;
              *(_WORD *)v56 = v57;
            }
            goto LABEL_81;
          }
        }
LABEL_82:
        v30 += Buffer_4[2];
        if ( Buffer_5 >= Buffer_3 )
        {
          buf = buf_1;
          Size_2 = Size_4;
          break;
        }
      }
    }
  }
  if ( n5 > 4 || *((_DWORD *)Buffer_4 + 3) <= Size_2 )
  {
    sub_434980((char *)Buffer_4 + 16,v94,*((_DWORD *)Buffer_4 + 3));
  }
  else
  {
    v67 = v94;
    if ( n5 == 3 )
      n5 = 4;
    Buffer_12 = Buffer_4[1];
    v69 = (char *)Buffer_4 + 15;
    if ( Buffer_4[1] )
    {
      Buffer_6 = *Buffer_4;
      Buffer_9 = 0;
      Buffer_1 = (void *)Buffer_6;
      n5_1 = n5;
      buf_1 = buf;
      Buffer_7 = Buffer_6;
      v85 = 8 - n5;
      Buffer_11 = Buffer_12;
      Buffer_10 = 0;
      do
      {
        if ( Buffer_7 > 0 )
        {
          Buffer_9 = Buffer_10;
          v74 = 0;
          for ( i = 0; i < Buffer_7; ++i )
          {
            v77 = v74 - n5_1;
            v76 = (int)(v74 - n5_1) < 0;
            v74 = v85;
            if ( v76 )
              ++v69;
            else
              v74 = v77;
            v78 = (unsigned __int8)*v67++ << v74;
            *v69 |= v78;
            Buffer_7 = *Buffer_4;
          }
          Buffer_10 = Buffer_9;
          Buffer_11 = Buffer_4[1];
        }
        ++Buffer_10;
      }
      while ( Buffer_10 < Buffer_11 );
      buf = buf_1;
    }
  }
  __op_delete(v94);
  __op_delete(buf);
  return Buffer_4;
}

#undef FILE
#undef _filelength
#undef _fileno
#undef fclose
#undef fopen
#undef fread
#undef fseek
#undef ftell
#undef sub_428AA0
#undef sub_428B00
#undef sub_428B60
#undef sub_428BE0
#undef sub_42B830
#undef sub_42B990
#undef sub_42BA40
#undef sub_434980
#undef sub_4349F0
