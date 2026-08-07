// sub_429840 @ 0x00429840 — __cdecl
// Extracted from BMF.cpp:34027-34287 by extract.py per incdec.md.

static inline unsigned __int8 * __fwd_sub_429840_sub_4293B0(void *a0, unsigned int a1, int a2) { return __sub_4293B0((unsigned __int8 *)a0, a1, a2); }
#define sub_4293B0 __fwd_sub_429840_sub_4293B0
static inline unsigned __int8 * __fwd_sub_429840_sub_4294D0(void *a0, void *a1, int a2) { return __sub_4294D0((unsigned __int8 *)a0, (_WORD *)a1, a2); }
#define sub_4294D0 __fwd_sub_429840_sub_4294D0
static inline unsigned __int8 * __fwd_sub_429840_sub_4295E0(void *a0, void *a1, int a2) { return __sub_4295E0((unsigned __int8 *)a0, (unsigned __int8 *)a1, a2); }
#define sub_4295E0 __fwd_sub_429840_sub_4295E0
static inline unsigned __int8 * __fwd_sub_429840_sub_429740(void *a0, void *a1, int a2) { return __sub_429740((unsigned __int8 *)a0, (_DWORD *)a1, a2); }
#define sub_429740 __fwd_sub_429840_sub_429740
#define sub_42B990 __sub_42B990

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

PROBE_DECL(__sub_429840)
BMF_REALIGN int __sub_429840(unsigned __int16 *a1, char *FileName, int a3)
{
  alignas(16) unsigned char __hexrays_frame[112];   // original frame, ebp-0x60..ebp+0x0
  void * &sub_429740_1 = *(void * *)(__hexrays_frame + 0);
  char * &Buffer_8 = *(char * *)(__hexrays_frame + 0);
  _BYTE * &Buffer_1 = *(_BYTE * *)(__hexrays_frame + 4);
  int &v37 = *(int *)(__hexrays_frame + 8);
  unsigned int &v38 = *(unsigned int *)(__hexrays_frame + 12);
  unsigned int &v39 = *(unsigned int *)(__hexrays_frame + 16);
  Stream * &Stream_2 = *(Stream * *)(__hexrays_frame + 20);
  Stream * &Stream_1 = *(Stream * *)(__hexrays_frame + 20);
  char * &buf_1 = *(char * *)(__hexrays_frame + 24);
  int &v43 = *(int *)(__hexrays_frame + 28);
  __int128 &Buffer = *(__int128 *)(__hexrays_frame + 32);
  __int16 &n5 = *(__int16 *)(__hexrays_frame + 48);
  int &n8_1 = *(int *)(__hexrays_frame + 52);
  unsigned int &i_1 = *(unsigned int *)(__hexrays_frame + 56);
  int &v48 = *(int *)(__hexrays_frame + 60);
  unsigned int &v49 = *(unsigned int *)(__hexrays_frame + 64);
  size_t &Size = *(size_t *)(__hexrays_frame + 68);
  _BYTE * &Buffer_2 = *(_BYTE * *)(__hexrays_frame + 72);
  void * &Buffer_5 = *(void * *)(__hexrays_frame + 76);
  unsigned int &v53 = *(unsigned int *)(__hexrays_frame + 80);
  PROBE_HIT(__sub_429840);
  int n8; // ebx
  Stream *Stream_v; // edi
  int v6; // edx
  size_t Size_1; // ecx
  unsigned __int16 v8; // ax
  int v9; // eax
  __int16 v10; // cx
  char v11; // al
  char *buf; // esi
  void *sub_429740; // edx
  _BYTE *Buffer_3; // eax
  _BYTE *Buffer_4; // ebx
  char *Buffer_9; // ebx
  int v17; // edi
  size_t Size_2; // ebx
  int buf_2; // edx
  char *Buffer_6; // eax
  char *Buffer_7; // edi
  unsigned __int8 *v22; // ebx
  int v23; // edx
  unsigned int i; // esi
  int n8_2; // eax
  int v26; // ecx
  int v27; // edx
  bool v28; // sf
  unsigned int v29; // eax
  unsigned int i_2; // ecx
  int v31; // esi
  int v32; // edx
  char v33; // cl

  n8 = a1[5] & 0x3F;
  Stream_v = fopen(FileName, "wb");
  if ( !Stream_v )
    return 0;
  Buffer = 0;
  n5 = 0;
  v6 = *a1;
  Size_1 = a1[1];
  v8 = a1[3];
  WORD6(Buffer) = *a1;
  BYTE7(Buffer) = 24;
  Size = Size_1;
  HIBYTE(n5) = 32;
  HIWORD(Buffer) = Size_1;
  WORD4(Buffer) = v8;
  v9 = (__int16)a1[4];
  LOBYTE(n5) = n8;
  v10 = v9 + Size_1 - 1;
  if ( v9 )
    LOWORD(v9) = v10;
  WORD5(Buffer) = v9;
  v11 = *((_BYTE *)a1 + 10);
  if ( (v11 & 0x40) != 0 )
  {
    if ( n8 == 8 )
    {
      BYTE2(Buffer) = 11;
      buf = nullptr;
    }
    else
    {
      *(_WORD *)((char *)&Buffer + 1) = 2305;
      *(_WORD *)((char *)&Buffer + 5) = 1 << (n8 & 31);
      buf = (char *)__op_new(3 * *(unsigned __int16 *)((char *)&Buffer + 5));
      sub_42B990(n5, (int)buf);
      v6 = WORD6(Buffer);
      Size = HIWORD(Buffer);
    }
  }
  else if ( n8 <= 8 )
  {
    BYTE2(Buffer) = 9;
    if ( v11 < 0 )
    {
      BYTE1(Buffer) = 1;
      *(_WORD *)((char *)&Buffer + 5) = 1 << (n8 & 31);
      buf = (char *)a1 + *((_DWORD *)a1 + 3) + 16;
    }
    else
    {
      buf = nullptr;
    }
  }
  else
  {
    BYTE2(Buffer) = 10;
    buf = nullptr;
  }
  v53 = v6 * ((unsigned int)(n8 + 7) >> 3);
  Size *= v53;
  Buffer_2 = (_BYTE *)(a1 + 8);
  Buffer_5 = (void *)(a1 + 8);
  if ( n8 <= 4 )
  {
    Buffer_6 = (char *)__op_new(Size);
    Buffer_5 = Buffer_6;
    v48 = (1 << (n8 & 31)) - 1;
    v38 = a1[1];
    if ( a1[1] )
    {
      v39 = *a1;
      v37 = 0;
      i_1 = v39 >> 1;
      if ( v39 )
      {
        v43 = 8 - n8;
        buf_1 = buf;
        Stream_1 = Stream_v;
        Buffer_7 = Buffer_6;
        n8_1 = n8;
        v22 = (unsigned __int8 *)a1 + 15;
        while ( 1 )
        {
          while ( 1 )
          {
            v23 = 0;
            if ( i_1 )
            {
              Buffer_8 = Buffer_6;
              for ( i = 0; i < i_1; ++i )
              {
                n8_2 = n8_1;
                v26 = v43;
                v27 = v23 - n8_1;
                if ( v27 < 0 )
                  ++v22;
                else
                  v26 = v27;
                v49 = *v22;
                Buffer_8[2 * i] = v48 & (v49 >> (v26 & 31));
                v23 = v26 - n8_2;
                v28 = v26 - n8_2 < 0;
                v29 = v49;
                if ( v28 )
                {
                  v23 = v43;
                  v29 = *++v22;
                }
                Buffer_8[2 * i + 1] = v48 & (v29 >> (v23 & 31));
              }
              i_2 = i;
              v31 = 2 * i + 1;
              Buffer_6 = &Buffer_8[2 * i_2];
            }
            else
            {
              v31 = 1;
            }
            if ( v31 - 1 < v39 )
              break;
            if ( ++v37 >= v38 )
              goto LABEL_63;
            Buffer_7 = Buffer_6;
          }
          v32 = v23 - n8_1;
          v33 = v43;
          if ( v32 < 0 )
            ++v22;
          else
            v33 = v32;
          Buffer_6 = &Buffer_7[v31];
          Buffer_7[v31 - 1] = v48 & (*v22 >> (v33 & 31));
          if ( ++v37 >= v38 )
            break;
          Buffer_7 += v31;
        }
LABEL_63:
        buf = buf_1;
        Stream_v = Stream_1;
        n8 = n8_1;
      }
    }
    LOBYTE(n5) = 8;
  }
  if ( a3 )
  {
    if ( n8 > 8 )
    {
      if ( n8 > 16 )
      {
        sub_429740 = ::sub_429740;
        if ( n8 == 24 )
          sub_429740 = sub_4295E0;
        sub_429740_1 = sub_429740;
      }
      else
      {
        sub_429740_1 = sub_4294D0;
      }
    }
    else
    {
      sub_429740_1 = sub_4293B0;
    }
    Buffer_3 = __op_new(Size + ((v53 >> 7) + 1) * a1[1]);
    Buffer_1 = Buffer_3;
    Buffer_4 = Buffer_3;
    if ( HIWORD(Buffer) )
    {
      Stream_2 = Stream_v;
      Buffer_9 = (char *)Buffer_5;
      v17 = 0;
      do
      {
        Buffer_3 = (_BYTE *)((int (__cdecl *)(_BYTE *, char *, _DWORD))sub_429740_1)(Buffer_3, Buffer_9, *a1);
        Buffer_9 += v53;
        ++v17;
      }
      while ( v17 < HIWORD(Buffer) );
      Stream_v = Stream_2;
      Buffer_4 = Buffer_3;
    }
    Size_2 = Buffer_4 - Buffer_1;
    if ( (int)(9 * Size_2) < (int)(8 * Size) )
      goto LABEL_30;
    __op_delete(Buffer_1);
  }
  Size_2 = Size;
  BYTE2(Buffer) -= 8;
  Buffer_1 = Buffer_5;
LABEL_30:
  if ( Buffer_5 != Buffer_2 && Buffer_5 != Buffer_1 )
    __op_delete(Buffer_5);
  fwrite(&Buffer, 0x12u, 1u, Stream_v);
  if ( buf )
  {
    fwrite(buf, 3u, *(unsigned __int16 *)((char *)&Buffer + 5), Stream_v);
    buf_2 = (a1[5] & 0x80) != 0 ? (int)a1 + *((_DWORD *)a1 + 3) + 16 : 0;
    if ( buf != (char *)buf_2 )
      __op_delete(buf);
  }
  if ( fwrite(Buffer_1, 1u, Size_2, Stream_v) != Size_2 )
    return 0;
  fclose(Stream_v);
  if ( Buffer_1 != Buffer_2 )
    __op_delete(Buffer_1);
  return 1;
}

#undef FILE
#undef fclose
#undef fopen
#undef fwrite
#undef sub_4293B0
#undef sub_4294D0
#undef sub_4295E0
#undef sub_429740
#undef sub_42B990
