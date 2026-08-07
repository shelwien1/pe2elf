// sub_42B0C0 @ 0x0042B0C0 — __cdecl
// Extracted from BMF.cpp:35476-35973 by extract.py per incdec.md.

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

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
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
#ifndef __PE_DECL___fwrite
#define __PE_DECL___fwrite
typedef unsigned int t_fwrite(const void *, unsigned int, unsigned int, FILE1 *);   // _fwrite
static t_fwrite& __fwrite = *(t_fwrite*)0x0042CF9F;
#endif
#define fwrite __fwrite
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

PROBE_DECL(__sub_42B0C0)
BMF_REALIGN int __sub_42B0C0(int p_i, char *FileName, int a3)
{
  alignas(16) unsigned char __hexrays_frame[96];   // original frame, ebp-0x50..ebp+0x0
  char &Buffer = *(char *)(__hexrays_frame + 0);
  unsigned int &Buffera = *(unsigned int *)(__hexrays_frame + 0);
  char * &Bufferb = *(char * *)(__hexrays_frame + 0);
  char * &Bufferd = *(char * *)(__hexrays_frame + 0);
  char * &Bufferc = *(char * *)(__hexrays_frame + 0);
  size_t &v62 = *(size_t *)(__hexrays_frame + 4);
  size_t &v63 = *(size_t *)(__hexrays_frame + 4);
  size_t &Size_2 = *(size_t *)(__hexrays_frame + 4);
  char * &v65 = *(char * *)(__hexrays_frame + 8);
  int &v66 = *(int *)(__hexrays_frame + 12);
  int &v67 = *(int *)(__hexrays_frame + 12);
  _BYTE * &v68 = *(_BYTE * *)(__hexrays_frame + 12);
  FILE * &Stream_v = *(FILE * *)(__hexrays_frame + 16);
  int &Buffer_2 = *(int *)(__hexrays_frame + 20);
  char * &buf = *(char * *)(__hexrays_frame + 24);
  _BYTE * &v72 = *(_BYTE * *)(__hexrays_frame + 28);
  int &Buffer_5 = *(int *)(__hexrays_frame + 36);
  signed int &n2_2 = *(signed int *)(__hexrays_frame + 44);
  int &v75 = *(int *)(__hexrays_frame + 48);
  char * &buf_2 = *(char * *)(__hexrays_frame + 52);
  unsigned int &v77 = *(unsigned int *)(__hexrays_frame + 60);
  PROBE_HIT(__sub_42B0C0);
  int v3; // ebx
  Stream *Stream_1; // edi
  char *Bufferc_3; // eax
  char v7; // fps
  int p_i_1; // edx
  char *Bufferc_1; // ebp
  int i; // esi
  int Buffer_1; // ecx
  int n8; // ecx
  char *Bufferb_1; // ecx
  int v14; // eax
  unsigned int v15; // eax
  int v16; // esi
  int v17; // eax
  size_t v18; // eax
  char *v19; // esi
  int v20; // ecx
  int v21; // ebx
  int v22; // edx
  int v23; // esi
  char *v24; // ecx
  int v25; // edx
  int v26; // eax
  unsigned __int16 *p_i_2; // ebp
  int v28; // edx
  unsigned int Bufferb_2; // eax
  char *buf_1; // esi
  char *v31; // ebx
  int n4; // edi
  bool v33; // zf
  int n2; // ecx
  int Buffer_3; // edi
  size_t Size_3; // ebp
  int Buffer_4; // edx
  int Size; // ebp
  char *v39; // edi
  int v40; // eax
  int n2_1; // esi
  char v42; // al
  char v43; // al
  char v44; // al
  char v45; // al
  char v46; // al
  char v47; // al
  char *buf_3; // edi
  int v49; // ebx
  char *Bufferc_2; // ebp
  Stream *Stream_2; // edi
  size_t ElementCount; // esi
  size_t v53; // ebp
  int Size_1; // ecx
  int v55; // edi
  char v56; // al

  v3 = a3;
  Stream_1 = fopen(FileName, "wb");
  if ( !Stream_1 )
    return 0;
  Bufferc_3 = (char *)__op_new(*(_DWORD *)(p_i + 12)
                                 + 8 * *(unsigned __int16 *)(p_i + 2)
                                 + (*(_DWORD *)(p_i + 12) >> 5) + 2048);
  p_i_1 = p_i;
  Bufferc_1 = Bufferc_3;
  i = *(unsigned __int16 *)p_i;
  *(_DWORD *)(Bufferc_3 + 14) = 40;
  *(_WORD *)Bufferc_3 = 19778;
  Buffer_1 = *(unsigned __int16 *)(p_i + 2);
  Buffer_2 = Buffer_1;
  *((_WORD *)Bufferc_3 + 4) = 0;
  *((_WORD *)Bufferc_3 + 3) = 0;
  *(_DWORD *)(Bufferc_3 + 18) = i;
  *(_DWORD *)(Bufferc_3 + 22) = Buffer_1;
  LOBYTE(Buffer_1) = *(_BYTE *)(p_i + 10);
  Buffer = Buffer_1;
  *((_WORD *)Bufferc_3 + 13) = 1;
  n8 = Buffer_1 & 0x3F;
  *((_WORD *)Bufferc_3 + 14) = n8;
  *(_DWORD *)(Bufferc_3 + 50) = 0;
  *(_DWORD *)(Bufferc_3 + 46) = 0;
  *(_DWORD *)(Bufferc_3 + 42) = 0;
  *(_DWORD *)(Bufferc_3 + 38) = 0;
  buf = Bufferc_3 + 54;
  if ( n8 <= 8 )
  {
    v14 = 1 << (n8 & 31);
    v66 = 1 << (n8 & 31);
    if ( (Buffer & 0x40) != 0 )
    {
      Buffera = 0x100u >> (n8 & 31);
      if ( v66 > 0 )
      {
        if ( v66 / 2 )
        {
          v15 = 0;
          v16 = 0;
          do
          {
            *(_DWORD *)&Bufferc_1[8 * v15 + 54] = ((unsigned __int8)v16 << 16)
                                                | (unsigned __int8)v16
                                                | ((unsigned __int8)v16 << 8);
            *(_DWORD *)&Bufferc_1[8 * v15 + 58] = ((unsigned __int8)(v16 - Buffera + 2 * Buffera) << 16)
                                                | (unsigned __int8)(v16 - Buffera + 2 * Buffera)
                                                | ((unsigned __int8)(v16 - Buffera + 2 * Buffera) << 8);
            v16 += 2 * Buffera;
            ++v15;
          }
          while ( v15 < v66 / 2 );
          p_i_1 = p_i;
          v17 = 2 * v15 + 1;
        }
        else
        {
          v17 = 1;
        }
        if ( v17 - 1 < (unsigned int)v66 )
          *(_DWORD *)&Bufferc_1[4 * v17 + 50] = ((unsigned __int8)(Buffera * (v17 - 1)) << 16)
                                              | (unsigned __int8)(Buffera * (v17 - 1))
                                              | ((unsigned __int8)(Buffera * (v17 - 1)) << 8);
      }
      Bufferb_1 = *(char **)(p_i_1 + 12);
      v67 = 4 * v66;
    }
    else if ( Buffer < 0 )
    {
      Bufferb_1 = *(char **)(p_i + 12);
      if ( v66 <= 0 )
      {
        v67 = 4 * v14;
      }
      else
      {
        v62 = v14 / 2;
        if ( v14 / 2 )
        {
          Bufferb = *(char **)(p_i + 12);
          v18 = 0;
          v19 = &Bufferb_1[p_i];
          do
          {
            v20 = 2 * v18;
            v21 = *(unsigned __int16 *)&v19[6 * v18 + 19];
            v22 = (unsigned __int8)v19[6 * v18 + 21];
            *(_DWORD *)&Bufferc_1[4 * v20 + 54] = ((unsigned __int8)v19[6 * v18 + 18] << 16)
                                                | *(unsigned __int16 *)&v19[6 * v18 + 16];
            *(_DWORD *)&Bufferc_1[4 * v20 + 58] = (v22 << 16) | v21;
            ++v18;
          }
          while ( v18 < v62 );
          Bufferb_1 = Bufferb;
          p_i_1 = p_i;
          v3 = a3;
          v23 = 2 * v18 + 1;
          v63 = v23;
        }
        else
        {
          v23 = 1;
          v63 = 1;
        }
        if ( v23 - 1 < (unsigned int)v66 )
        {
          Bufferd = Bufferb_1;
          v24 = &Bufferb_1[p_i_1];
          v25 = *(unsigned __int16 *)&v24[3 * v63 + 13];
          v26 = (unsigned __int8)v24[3 * v63 + 15];
          Bufferb_1 = Bufferd;
          *(_DWORD *)&Bufferc_1[4 * v63 + 50] = (v26 << 16) | v25;
          p_i_1 = p_i;
        }
        v67 = 4 * v66;
      }
    }
    else
    {
      v67 = 4 * v14;
      sub_4349F0(buf,0,4 * v14);
      p_i_1 = p_i;
      Bufferb_1 = *(char **)(p_i + 12);
      Buffer_2 = *(unsigned __int16 *)(p_i + 2);
    }
    buf = &Bufferc_1[v67 + 54];
  }
  else
  {
    Bufferb_1 = *(char **)(p_i + 12);
  }
  Size_2 = *(unsigned __int16 *)(p_i_1 + 4);
  Bufferc = Bufferc_1;
  v65 = (char *)(buf - Bufferc_1);
  Stream_v = Stream_1;
  p_i_2 = (unsigned __int16 *)p_i_1;
  v28 = v3;
  Bufferb_2 = (unsigned int)Bufferb_1;
  while ( 1 )
  {
    buf_1 = buf;
    v31 = (char *)p_i_2 + Bufferb_2 - Size_2 + 16;
    *(_DWORD *)(Bufferc + 10) = v65;
    if ( !v28 )
      break;
    n4 = p_i_2[5] & 0x3F;
    v33 = n4 == 4;
    if ( n4 != 4 )
    {
      if ( n4 != 8 )
        break;
      v33 = 0;
    }
    n2 = 2;
    if ( !v33 )
      n2 = 1;
    *(_DWORD *)(Bufferc + 30) = n2;
    v75 = n2 - 1;
    n2_2 = (0x100u >> ((n2 - 1) & 31)) - 1;
    if ( Buffer_2 > 0 )
    {
      Buffer_3 = Buffer_2;
      Size_3 = Size_2;
      Buffer_4 = 0;
      while ( 1 )
      {
        if ( v31 >= &v31[Size_3] )
          goto LABEL_72;
        buf_2 = buf_1;
        v77 = (unsigned int)&v31[Size_3];
        Buffer_5 = Buffer_4;
        Size = 0;
        do
        {
          while ( 1 )
          {
            while ( 1 )
            {
              v39 = v31 + 1;
              if ( (unsigned int)(v31 + 1) >= v77 )
                break;
              v40 = (unsigned __int8)*v31;
              n2_1 = 1;
              do
              {
                if ( v40 != (unsigned __int8)v31[n2_1] )
                  break;
                ++n2_1;
              }
              while ( v77 > (unsigned int)&v31[n2_1] );
              if ( n2_1 <= 2 && (n2_1 != 2 || Size) )
                break;
              if ( n2_2 < n2_1 )
                n2_1 = n2_2;
              if ( !Size )
                goto LABEL_70;
              if ( v75 )
              {
                if ( Size != 1 )
                {
LABEL_67:
                  *buf_2 = 0;
                  v72 = buf_2 + 2;
                  buf_2[1] = Size << (v75 & 31);
                  sub_434980(buf_2 + 2,&v31[-Size],Size);
                  buf_2 += Size + 2;
                  if ( (Size & 1) != 0 )
                  {
                    v72[Size] = 0;
                    ++buf_2;
                  }
                  goto LABEL_69;
                }
                v47 = *(v31 - 1);
                *buf_2 = 2;
                buf_2[1] = v47;
                buf_2 += 2;
              }
              else
              {
                if ( Size >= 3 )
                  goto LABEL_67;
                if ( Size == 2 )
                {
                  v45 = *(v31 - 2);
                  *buf_2 = 1;
                  buf_2[1] = v45;
                  buf_2 += 2;
                }
                v46 = *(v31 - 1);
                *buf_2 = 1;
                buf_2[1] = v46;
                buf_2 += 2;
              }
LABEL_69:
              Size = 0;
              LOBYTE(v40) = *v31;
LABEL_70:
              buf_2[1] = v40;
              v31 += n2_1;
              *buf_2 = n2_1 << (v75 & 31);
              buf_3 = buf_2 + 2;
              buf_2 += 2;
              if ( (unsigned int)v31 >= v77 )
              {
                buf_1 = buf_3;
                Buffer_4 = Buffer_5;
                Buffer_3 = *(unsigned __int16 *)(p_i + 2);
                Size_3 = *(unsigned __int16 *)(p_i + 4);
                goto LABEL_72;
              }
            }
            ++v31;
            if ( ++Size != n2_2 )
              break;
            if ( v75 )
            {
              if ( Size == 1 )
              {
                v44 = *(v39 - 1);
                *buf_2 = 2;
                buf_2[1] = v44;
                buf_2 += 2;
                goto LABEL_55;
              }
            }
            else if ( Size < 3 )
            {
              if ( Size == 2 )
              {
                v42 = *(v39 - 2);
                *buf_2 = 1;
                buf_2[1] = v42;
                buf_2 += 2;
              }
              v43 = *(v39 - 1);
              *buf_2 = 1;
              buf_2[1] = v43;
              buf_2 += 2;
              goto LABEL_55;
            }
            *buf_2 = 0;
            v68 = buf_2 + 2;
            buf_2[1] = Size << (v75 & 31);
            sub_434980(buf_2 + 2,&v39[-Size],Size);
            buf_2 += Size + 2;
            if ( (Size & 1) != 0 )
            {
              v68[Size] = 0;
              ++buf_2;
            }
LABEL_55:
            if ( (unsigned int)v39 >= v77 )
            {
              buf_1 = buf_2;
              Buffer_4 = Buffer_5;
              Buffer_3 = *(unsigned __int16 *)(p_i + 2);
              Size_3 = *(unsigned __int16 *)(p_i + 4);
              goto LABEL_72;
            }
            Size = 0;
          }
        }
        while ( (unsigned int)v39 < v77 );
        buf_1 = buf_2;
        Buffer_4 = Buffer_5;
        if ( !Size )
          goto LABEL_89;
        if ( v75 )
        {
          if ( Size == 1 )
          {
            buf_2[1] = *(v39 - 1);
            *buf_2 = 2;
            Buffer_3 = *(unsigned __int16 *)(p_i + 2);
            Size_3 = *(unsigned __int16 *)(p_i + 4);
            buf_1 = buf_2 + 2;
            goto LABEL_72;
          }
LABEL_97:
          *buf_2 = 0;
          buf_2[1] = Size << (v75 & 31);
          sub_434980(buf_2 + 2,&v39[-Size],Size);
          Buffer_4 = Buffer_5;
          buf_1 = &buf_2[Size + 2];
          if ( (Size & 1) != 0 )
          {
            buf_2[Size + 2] = 0;
            Buffer_3 = *(unsigned __int16 *)(p_i + 2);
            Size_3 = *(unsigned __int16 *)(p_i + 4);
            ++buf_1;
            goto LABEL_72;
          }
LABEL_89:
          Buffer_3 = *(unsigned __int16 *)(p_i + 2);
          Size_3 = *(unsigned __int16 *)(p_i + 4);
          goto LABEL_72;
        }
        if ( Size >= 3 )
          goto LABEL_97;
        if ( Size == 2 )
        {
          v56 = *(v39 - 2);
          *buf_2 = 1;
          buf_2[1] = v56;
          buf_1 = buf_2 + 2;
        }
        buf_1[1] = *(v39 - 1);
        *buf_1 = 1;
        Buffer_3 = *(unsigned __int16 *)(p_i + 2);
        Size_3 = *(unsigned __int16 *)(p_i + 4);
        buf_1 += 2;
LABEL_72:
        *buf_1 = 0;
        buf_1[1] = 0;
        buf_1 += 2;
        ++Buffer_4;
        v31 -= 2 * Size_3;
        if ( Buffer_4 >= Buffer_3 )
        {
          Buffer_2 = Buffer_3;
          Size_2 = Size_3;
          p_i_2 = (unsigned __int16 *)p_i;
          Bufferb_2 = *(_DWORD *)(p_i + 12);
          break;
        }
      }
    }
    *buf_1 = 0;
    buf_1[1] = 1;
    buf_1 += 2;
    v49 = buf_1 - buf;
    if ( Bufferb_2 > buf_1 - buf )
    {
      Bufferc_2 = Bufferc;
      Stream_2 = Stream_v;
      goto LABEL_76;
    }
    v28 = 0;
  }
  Stream_2 = Stream_v;
  Bufferc_2 = Bufferc;
  *(_DWORD *)(Bufferc + 30) = 0;
  if ( Buffer_2 <= 0 )
  {
    v49 = 0;
  }
  else
  {
    v53 = ((Size_2 + 3) & 0xFFFFFFFC) - Size_2;
    Size_1 = Size_2;
    v55 = 0;
    do
    {
      sub_434980(buf_1,v31,Size_1);
      Size_1 = *(unsigned __int16 *)(p_i + 4);
      buf_1 += Size_1;
      v31 -= Size_1;
      if ( v53 )
      {
        *(_DWORD *)buf_1 = 0;
        buf_1 += v53;
      }
      ++v55;
    }
    while ( v55 < *(unsigned __int16 *)(p_i + 2) );
    Bufferc_2 = Bufferc;
    Stream_2 = Stream_v;
    v49 = buf_1 - buf;
  }
LABEL_76:
  *(_DWORD *)(Bufferc_2 + 34) = v49;
  ElementCount = buf_1 - Bufferc_2;
  *(_DWORD *)(Bufferc_2 + 2) = ElementCount;
  if ( fwrite(Bufferc_2, 1u, ElementCount, Stream_2) != *(_DWORD *)(Bufferc_2 + 2) )
    return 0;
  __op_delete(Bufferc_2);
  fclose(Stream_2);
  return 1;
}

#undef FILE
#undef fclose
#undef fopen
#undef fwrite
#undef sub_434980
#undef sub_4349F0
