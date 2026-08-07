// sub_403820 @ 0x00403820 — __userpurge
// Extracted from BMF.cpp:2989-3571 by extract.py per incdec.md.

typedef int t_sub_403820_Buffer;
static t_sub_403820_Buffer& __sub_403820_Buffer = *(t_sub_403820_Buffer*)0x0044337C;
typedef int t_sub_403820_Buffer_0;
static t_sub_403820_Buffer_0& __sub_403820_Buffer_0 = *(t_sub_403820_Buffer_0*)0x00443378;
typedef int t_sub_403820_Buffer_1;
static t_sub_403820_Buffer_1& __sub_403820_Buffer_1 = *(t_sub_403820_Buffer_1*)0x00443374;
typedef int t_sub_403820_ElementCount_0;
static t_sub_403820_ElementCount_0& __sub_403820_ElementCount_0 = *(t_sub_403820_ElementCount_0*)0x00443370;
typedef int t_sub_403820_buf;
static t_sub_403820_buf& __sub_403820_buf = *(t_sub_403820_buf*)0x00443380;
typedef unsigned char t_sub_403820_byte_44339C[0x10000];
static t_sub_403820_byte_44339C& __sub_403820_byte_44339C = *(t_sub_403820_byte_44339C*)0x0044339C;
typedef unsigned char t_sub_403820_byte_44339D[0x10000];
static t_sub_403820_byte_44339D& __sub_403820_byte_44339D = *(t_sub_403820_byte_44339D*)0x0044339D;
typedef unsigned char t_sub_403820_byte_44339E[0x10000];
static t_sub_403820_byte_44339E& __sub_403820_byte_44339E = *(t_sub_403820_byte_44339E*)0x0044339E;
typedef unsigned char t_sub_403820_byte_44339F[0x10000];
static t_sub_403820_byte_44339F& __sub_403820_byte_44339F = *(t_sub_403820_byte_44339F*)0x0044339F;
typedef int t_sub_403820_dword_443364;
static t_sub_403820_dword_443364& __sub_403820_dword_443364 = *(t_sub_403820_dword_443364*)0x00443364;
typedef int t_sub_403820_dword_443384;
static t_sub_403820_dword_443384& __sub_403820_dword_443384 = *(t_sub_403820_dword_443384*)0x00443384;
typedef int t_sub_403820_dword_443388;
static t_sub_403820_dword_443388& __sub_403820_dword_443388 = *(t_sub_403820_dword_443388*)0x00443388;
typedef int t_sub_403820_dword_4433A0[0x10000];
static t_sub_403820_dword_4433A0& __sub_403820_dword_4433A0 = *(t_sub_403820_dword_4433A0*)0x004433A0;
typedef int t_sub_403820_dword_4433A4[0x10000];
static t_sub_403820_dword_4433A4& __sub_403820_dword_4433A4 = *(t_sub_403820_dword_4433A4*)0x004433A4;
typedef int t_sub_403820_dword_4433A8[0x10000];
static t_sub_403820_dword_4433A8& __sub_403820_dword_4433A8 = *(t_sub_403820_dword_4433A8*)0x004433A8;
typedef int t_sub_403820_n2;
static t_sub_403820_n2& __sub_403820_n2 = *(t_sub_403820_n2*)0x00443360;
typedef int t_sub_403820_n256;
static t_sub_403820_n256& __sub_403820_n256 = *(t_sub_403820_n256*)0x0044336C;
typedef int t_sub_403820_n256_0[0x10000];
static t_sub_403820_n256_0& __sub_403820_n256_0 = *(t_sub_403820_n256_0*)0x00443398;
typedef int t_sub_403820_n256_2[0x10000];
static t_sub_403820_n256_2& __sub_403820_n256_2 = *(t_sub_403820_n256_2*)0x0044338C;
typedef int t_sub_403820_n4_5;
static t_sub_403820_n4_5& __sub_403820_n4_5 = *(t_sub_403820_n4_5*)0x00443394;
typedef int t_sub_403820_n512[0x10000];
static t_sub_403820_n512& __sub_403820_n512 = *(t_sub_403820_n512*)0x00443390;
typedef int t_sub_403820_n8;
static t_sub_403820_n8& __sub_403820_n8 = *(t_sub_403820_n8*)0x00443368;

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980
static inline void ** __fwd_sub_403820_sub_402E70(void *a0, char a1) { return __sub_402E70((void **)a0, a1); }
#define sub_402E70 __fwd_sub_403820_sub_402E70
static inline char * __fwd_sub_403820_sub_4081E0(void *a0, void *a1, int a2, char a3) { return __sub_4081E0((char *)a0, (char *)a1, a2, a3); }
#define sub_4081E0 __fwd_sub_403820_sub_4081E0
static inline void __fwd_sub_403820_sub_40CF80(int a0, void *a1, int a2) { __sub_40CF80(a0, (_BYTE *)a1, a2); }
#define sub_40CF80 __fwd_sub_403820_sub_40CF80
static inline _DWORD * __fwd_sub_403820_sub_40E590(void *a0, int a1, char a2) { return __sub_40E590((_DWORD *)a0, a1, a2); }
#define sub_40E590 __fwd_sub_403820_sub_40E590
static inline char * __fwd_sub_403820_sub_40FAC0(void *a0, char a1, int a2, int a3, int a4) { return __sub_40FAC0((int *)a0, a1, a2, a3, a4); }
#define sub_40FAC0 __fwd_sub_403820_sub_40FAC0
#define sub_410310 __sub_410310
#define sub_410650 __sub_410650
static inline void __fwd_sub_403820_sub_417DB0(char a0, const __m128 &a1, const __m128 &a2, void *a3, void *a4) { __sub_417DB0(a0, a1, a2, (unsigned __int16 *)a3, (unsigned __int8 *)a4); }
#define sub_417DB0 __fwd_sub_403820_sub_417DB0
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
#ifndef __PE_DECL___feof
#define __PE_DECL___feof
typedef int t_feof(FILE1 *);   // _feof
static t_feof& __feof = *(t_feof*)0x0042D33B;
#endif
#define feof __feof
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

PROBE_DECL(__sub_403820)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) char * __sub_403820(int a1, const __m128 &a2__ref, const __m128 &a3__ref, int a4, int *p_dwLowDateTime)
{
  alignas(16) unsigned char __hexrays_frame[104];   // original frame, ebp-0x58..ebp+0x0
  char * &Block = *(char * *)(__hexrays_frame + 0);
  char * &Blocka = *(char * *)(__hexrays_frame + 0);
  void ** &Blockb = *(void ** *)(__hexrays_frame + 0);
  unsigned __int16 (&p_i)[2] = *(unsigned __int16 (*)[2])(__hexrays_frame + 4);
  int &v81 = *(int *)(__hexrays_frame + 8);
  int &n4_10 = *(int *)(__hexrays_frame + 12);
  size_t &Size = *(size_t *)(__hexrays_frame + 16);
  int &n4_1 = *(int *)(__hexrays_frame + 20);
  void * &Src = *(void * *)(__hexrays_frame + 24);
  int &v86 = *(int *)(__hexrays_frame + 28);
  char * &p_i_2 = *(char * *)(__hexrays_frame + 32);
  int &v88 = *(int *)(__hexrays_frame + 36);
  size_t &ElementCount_3 = *(size_t *)(__hexrays_frame + 40);
  _WORD (&Buffer_2)[5] = *(_WORD (*)[5])(__hexrays_frame + 44);
  unsigned __int8 &v91 = *(unsigned __int8 *)(__hexrays_frame + 54);
  char &v92 = *(char *)(__hexrays_frame + 55);
  size_t &ElementCount = *(size_t *)(__hexrays_frame + 56);
  int &Buffer_ = *(int *)(__hexrays_frame + 60);
  size_t &ElementSize = *(size_t *)(__hexrays_frame + 64);
  unsigned int &__sub_403820_Buffer = *(unsigned int *)(__hexrays_frame + 68);
  PROBE_HIT(__sub_403820);
  __m128 a2 = a2__ref;
  __m128 a3 = a3__ref;
  int v5; // ebx
  Stream *Stream_1; // eax
  Stream *Stream_v; // ebp
  unsigned int __sub_403820_Buffer_1; // ebp
  char v10; // al
  int Buffer__1; // edi
  size_t v12; // ebp
  _DWORD *v13; // eax
  size_t ElementCount_5; // edx
  char *p_i_1; // ebp
  int dwLowDateTime; // edx
  char v17; // al
  char v18; // cl
  size_t ElementCount_2; // esi
  char v20; // dl
  int v21; // edx
  int n4; // eax
  unsigned int v23; // ebx
  int v24; // ebp
  unsigned int v25; // edx
  int __sub_403820_n2; // ebx
  int v27; // edx
  int v28; // edx
  int v29; // edx
  int v30; // edx
  unsigned __int8 *Src_1; // edi
  int ArgList; // esi
  int v33; // ebx
  char v34; // fps
  char v35; // fps
  int n4_4; // esi
  int v37; // ebx
  int n2_1; // eax
  int i; // ecx
  size_t Size_1; // edx
  signed int Size_4; // esi
  signed int Size_5; // ecx
  int n4_3; // ebp
  int v44; // edx
  signed int Size_2; // esi
  signed int Size_3; // ecx
  int n4_2; // ebp
  int v48; // edx
  int n2_2; // eax
  size_t ElementCount_1; // esi
  char *Buffer_3; // eax
  size_t ElementCount_4; // eax
  char *n4_6; // edi
  int __sub_403820_n4_5; // ebx
  int v55; // esi
  int Src_2; // esi
  char v57; // fps
  int v58; // edx
  char *n4_7; // esi
  int n4_8; // eax
  int v61; // edi
  int i_1; // edx
  void *Src_3; // edi
  char *v64; // ecx
  int n4_9; // ebp
  unsigned __int16 i_2; // ax
  unsigned int v67; // edi
  unsigned int v68; // edi
  unsigned int v69; // edi
  unsigned int v70; // edi
  _DWORD *v71; // ecx
  char v72; // fps
  int *Blockb_1; // ecx
  unsigned int v74; // ebp
  unsigned int v75; // esi
  int v76; // edx

  v5 = a1;
  if ( p_dwLowDateTime )
    *p_dwLowDateTime = 0;
  Stream_1 = *(FILE **)(a1 + 4);
  if ( !Stream_1 )
    return nullptr;
  while ( 1 )
  {
    if ( fread(&__sub_403820_Buffer, 4u, 1u, Stream_1) != 1 )
    {
      Stream_v = *(FILE **)(v5 + 4);
      if ( feof(Stream_v) )
        return nullptr;
      goto LABEL_15;
    }
    __sub_403820_Buffer_1 = __sub_403820_Buffer;
    if ( (_WORD)__sub_403820_Buffer != 0x9081 )
      break;
    __sub_403820_n512[0] = ((BYTE2(__sub_403820_Buffer) << 8) - 12288) | (HIBYTE(__sub_403820_Buffer) - 48);
    if ( __sub_403820_n512[0] != 512 || fread(&Buffer_, 8u, 1u, *(FILE **)(v5 + 4)) != 1 )
      break;
    fseek(*(FILE **)(v5 + 4), ElementSize, 1);
    Stream_1 = *(FILE **)(v5 + 4);
  }
  if ( (_WORD)__sub_403820_Buffer_1 != 0x8A81
    || (__sub_403820_n512[0] = ((BYTE2(__sub_403820_Buffer_1) << 8) - 12288) | (HIBYTE(__sub_403820_Buffer_1) - 48), __sub_403820_n512[0] != 512)
    || fread(Buffer_2, 0x10u, 1u, *(FILE **)(v5 + 4)) != 1 )
  {
    Stream_v = *(FILE **)(v5 + 4);
LABEL_15:
    fclose(Stream_v);
    *(_DWORD *)(v5 + 4) = 0;
    return nullptr;
  }
  v10 = v92;
  ++*(_DWORD *)v5;
  if ( v10 < 0 )
  {
    fread(&Buffer_, 8u, 1u, *(FILE **)(v5 + 4));
    if ( p_dwLowDateTime )
    {
      Buffer__1 = Buffer_;
      v12 = (ElementSize + (ElementSize == 0) + 3) & 0xFFFFFFFC;
      v13 = __op_new(v12 + 8);
      *v13 = Buffer__1;
      v13[1] = v12;
      *(_DWORD *)((char *)v13 + v12 + 4) = 0;
      *p_dwLowDateTime = (int)v13;
      fread(v13 + 2, ElementSize, 1u, *(FILE **)(v5 + 4));
    }
    else
    {
      fseek(*(FILE **)(v5 + 4), ElementSize, 1);
    }
  }
  ElementCount_5 = 3 << (v91 & 31);
  if ( (v91 & 0x80) == 0 )
    ElementCount_5 = v91 & 0x80;
  ElementCount_3 = ElementCount_5;
  if ( a4 )
  {
    fseek(*(FILE **)(v5 + 4), ElementCount_3 + ElementCount, 1);
    return nullptr;
  }
  p_i_1 = (char *)sub_42B830(Buffer_2[0], Buffer_2[1], v91 & 0x3F, (unsigned __int8)(v91 & 0x80) >> 7, 1);
  v88 = v91;
  p_i_1[10] = v91;
  if ( p_dwLowDateTime )
  {
    dwLowDateTime = *p_dwLowDateTime;
    if ( *p_dwLowDateTime )
      LOBYTE(dwLowDateTime) = 1;
  }
  else
  {
    LOBYTE(dwLowDateTime) = 0;
  }
  v17 = v92;
  v18 = v88;
  p_i_1[11] |= v92 & 2 | ((_BYTE)dwLowDateTime << 7);
  ::__sub_403820_n4_5 = ((v18 & 0x3Fu) + 7) >> 3;
  if ( (v17 & 0x20) == 0 )
  {
    ElementCount_1 = ElementCount;
    if ( fread(p_i_1 + 16, 1u, ElementCount, *(FILE **)(v5 + 4)) != ElementCount_1 )
      goto LABEL_31;
    goto LABEL_109;
  }
  __sub_403820_n256_0[0] = 0;
  __sub_403820_dword_443388 = 0;
  __sub_403820_dword_443384 = (unsigned __int8)(v17 & 4) >> 2;
  __sub_403820_ElementCount_0 = ElementCount;
  ::__sub_403820_Buffer = __op_new(ElementCount);
  __sub_403820_Buffer_0 = (int)::__sub_403820_Buffer;
  __sub_403820_n8 = 0;
  __sub_403820_n256 = 0;
  ::__sub_403820_Buffer_1 = (int)::__sub_403820_Buffer;
  __sub_403820_buf = (char *)::__sub_403820_Buffer + __sub_403820_ElementCount_0 - 4096;
  ElementCount_2 = ElementCount;
  if ( fread(::__sub_403820_Buffer, 1u, ElementCount, *(FILE **)(v5 + 4)) != ElementCount_2 )
  {
LABEL_31:
    fclose(*(FILE **)(v5 + 4));
    *(_DWORD *)(v5 + 4) = 0;
    return nullptr;
  }
  v20 = p_i_1[10];
  if ( (v20 & 0x3Fu) <= 4 || (v92 & 0x10) == 0 )
  {
    ::__sub_403820_n2 = 0;
    __sub_403820_dword_443364 = 0;
    if ( __sub_403820_dword_443384 )
      sub_417DB0(ElementCount_2, a2, a3, (unsigned __int16 *)p_i_1, (unsigned __int8 *)p_i_1 + 16);
    else
      sub_40CF80(*((unsigned __int16 *)p_i_1 + 2), p_i_1 + 16, *((_DWORD *)p_i_1 + 3));
    goto LABEL_106;
  }
  if ( ::__sub_403820_n4_5 == 1 )
  {
    if ( (v20 & 0x40) == 0 )
      goto LABEL_42;
  }
  else if ( ::__sub_403820_n4_5 <= 2 )
  {
    goto LABEL_42;
  }
  __sub_403820_n8 -= 4;
  if ( __sub_403820_n8 < 0 )
  {
    v75 = *(_DWORD *)__sub_403820_Buffer_0;
    __sub_403820_Buffer_0 += 4;
    v76 = v75 << ((__sub_403820_n8 + 4) & 31);
    ElementCount_2 = v75 >> (-(char)__sub_403820_n8 & 31);
    v21 = __sub_403820_n256 | v76 & 0xF;
    __sub_403820_n256 = ElementCount_2;
    __sub_403820_n8 += 32;
  }
  else
  {
    v21 = __sub_403820_n256 & 0xF;
    __sub_403820_n256 = (unsigned int)__sub_403820_n256 >> 4;
  }
  __sub_403820_n256_0[0] = v21;
LABEL_42:
  if ( ::__sub_403820_n4_5 > 0 )
  {
    LOBYTE(ElementCount_2) = 63;
    *(_DWORD *)p_i = 255;
    p_i_2 = p_i_1;
    v86 = v5;
    n4 = 0;
    do
    {
      __sub_403820_n8 -= 6;
      if ( __sub_403820_n8 < 0 )
      {
        v74 = *(_DWORD *)__sub_403820_Buffer_0;
        __sub_403820_Buffer_0 += 4;
        v23 = __sub_403820_n256 | (v74 << ((__sub_403820_n8 + 6) & 31)) & 0x3F;
        __sub_403820_n256 = v74 >> (-(char)__sub_403820_n8 & 31);
        __sub_403820_n8 += 32;
      }
      else
      {
        v23 = __sub_403820_n256 & 0x3F;
        __sub_403820_n256 = (unsigned int)__sub_403820_n256 >> 6;
      }
      v24 = 16 * n4;
      v25 = v23 >> 2;
      __sub_403820_n2 = v23 & 3;
      __sub_403820_byte_44339E[v24] = v25;
      __sub_403820_byte_44339C[v24] = __sub_403820_n2;
      __sub_403820_byte_44339D[16 * __sub_403820_n2] = n4;
      if ( (__sub_403820_byte_44339E[16 * n4] & 8) != 0 )
      {
        __sub_403820_n8 -= 8;
        if ( __sub_403820_n8 < 0 )
        {
          v70 = *(_DWORD *)__sub_403820_Buffer_0;
          __sub_403820_Buffer_0 += 4;
          v27 = __sub_403820_n256 | *(_DWORD *)p_i & (v70 << ((__sub_403820_n8 + 8) & 31));
          __sub_403820_n256 = v70 >> (-(char)__sub_403820_n8 & 31);
          __sub_403820_n8 += 32;
        }
        else
        {
          LOBYTE(v27) = __sub_403820_n256 & LOBYTE(p_i[0]);
          __sub_403820_n256 = (unsigned int)__sub_403820_n256 >> 8;
        }
        __sub_403820_byte_44339F[16 * n4] = v27;
        if ( __sub_403820_n2 > 1 )
        {
          __sub_403820_n8 -= 8;
          if ( __sub_403820_n8 < 0 )
          {
            v69 = *(_DWORD *)__sub_403820_Buffer_0;
            __sub_403820_Buffer_0 += 4;
            v28 = __sub_403820_n256 | *(_DWORD *)p_i & (v69 << ((__sub_403820_n8 + 8) & 31));
            __sub_403820_n256 = v69 >> (-(char)__sub_403820_n8 & 31);
            __sub_403820_n8 += 32;
          }
          else
          {
            v28 = __sub_403820_n256 & *(_DWORD *)p_i;
            __sub_403820_n256 = (unsigned int)__sub_403820_n256 >> 8;
          }
          __sub_403820_dword_4433A0[4 * n4] = v28 - 64;
          __sub_403820_n8 -= 8;
          if ( __sub_403820_n8 < 0 )
          {
            v68 = *(_DWORD *)__sub_403820_Buffer_0;
            __sub_403820_Buffer_0 += 4;
            v29 = __sub_403820_n256 | *(_DWORD *)p_i & (v68 << ((__sub_403820_n8 + 8) & 31));
            __sub_403820_n256 = v68 >> (-(char)__sub_403820_n8 & 31);
            __sub_403820_n8 += 32;
          }
          else
          {
            v29 = __sub_403820_n256 & *(_DWORD *)p_i;
            __sub_403820_n256 = (unsigned int)__sub_403820_n256 >> 8;
          }
          __sub_403820_dword_4433A4[4 * n4] = v29 - 64;
          if ( __sub_403820_n2 > 2 )
          {
            __sub_403820_n8 -= 8;
            if ( __sub_403820_n8 < 0 )
            {
              v67 = *(_DWORD *)__sub_403820_Buffer_0;
              __sub_403820_Buffer_0 += 4;
              v30 = __sub_403820_n256 | *(_DWORD *)p_i & (v67 << ((__sub_403820_n8 + 8) & 31));
              __sub_403820_n256 = v67 >> (-(char)__sub_403820_n8 & 31);
              __sub_403820_n8 += 32;
            }
            else
            {
              v30 = __sub_403820_n256 & *(_DWORD *)p_i;
              __sub_403820_n256 = (unsigned int)__sub_403820_n256 >> 8;
            }
            __sub_403820_dword_4433A8[4 * n4] = v30 - 64;
          }
        }
      }
      ++n4;
    }
    while ( n4 < ::__sub_403820_n4_5 );
    p_i_1 = p_i_2;
    v5 = v86;
  }
  Src_1 = (unsigned __int8 *)__op_new(*(unsigned __int16 *)p_i_1 * *((unsigned __int16 *)p_i_1 + 1));
  if ( (v92 & 8) != 0 )
  {
    *(_DWORD *)p_i = *(_DWORD *)p_i_1;
    v81 = *((_DWORD *)p_i_1 + 1);
    n4_10 = *((_DWORD *)p_i_1 + 2);
    Size = *((_DWORD *)p_i_1 + 3);
    BYTE2(n4_10) = 72;
    if ( ::__sub_403820_n4_5 > 0 )
    {
      v86 = v5;
      ArgList = 0;
      do
      {
        v33 = (unsigned __int8)__sub_403820_byte_44339D[16 * ArgList];
        ::__sub_403820_n2 = __sub_403820_byte_44339E[16 * v33] & 3;
        __sub_403820_dword_443364 = (unsigned __int8)(__sub_403820_byte_44339E[16 * v33] & 4) >> 2;
        if ( __sub_403820_dword_443384 )
          sub_417DB0(ArgList, a2, a3, p_i, Src_1);
        else
          sub_40CF80(*(unsigned __int16 *)p_i_1, Src_1, *(unsigned __int16 *)p_i_1 * *((unsigned __int16 *)p_i_1 + 1));
        if ( ::__sub_403820_n2 )
        {
          if ( ::__sub_403820_n2 == 1 )
          {
            if ( !__sub_403820_dword_443384 || !__sub_403820_dword_443364 )
              sub_410310((int)Src_1, *(unsigned __int16 *)p_i_1, *((unsigned __int16 *)p_i_1 + 1));
          }
          else if ( !__sub_403820_dword_443384 && ::__sub_403820_n2 == 2 )
          {
            v71 = __op_new(0x30ACu);
            Blockb_1 = v71 ? sub_40E590(v71, *(unsigned __int16 *)p_i_1, *Src_1) : nullptr;
            Blockb = (void **)Blockb_1;
            sub_40FAC0(Blockb_1, v72, (int)Src_1, *(unsigned __int16 *)p_i_1, *((unsigned __int16 *)p_i_1 + 1));
            if ( Blockb )
              sub_402E70(Blockb, 1);
          }
        }
        else
        {
          sub_410650((unsigned int)Src_1, *(unsigned __int16 *)p_i_1, *((unsigned __int16 *)p_i_1 + 1));
        }
        sub_4081E0(p_i_1, (char *)Src_1, v33, v34);
        ++ArgList;
      }
      while ( ArgList < ::__sub_403820_n4_5 );
LABEL_104:
      v5 = v86;
    }
  }
  else
  {
    ::__sub_403820_n2 = __sub_403820_byte_44339E[0] & 3;
    __sub_403820_dword_443364 = (unsigned __int8)(__sub_403820_byte_44339E[0] & 4) >> 2;
    if ( __sub_403820_dword_443384 )
    {
      sub_417DB0(ElementCount_2, a2, a3, (unsigned __int16 *)p_i_1, (unsigned __int8 *)p_i_1 + 16);
      if ( __sub_403820_dword_443364 )
        goto LABEL_105;
    }
    else
    {
      __sub_403820_dword_443364 = 0;
      ::__sub_403820_n2 = 0;
      sub_40CF80(*((unsigned __int16 *)p_i_1 + 2), p_i_1 + 16, *((_DWORD *)p_i_1 + 3));
    }
    if ( ::__sub_403820_n4_5 > 0 )
    {
      v86 = v5;
      n4_4 = 0;
      do
      {
        ++n4_4;
        v37 = BYTE1(__sub_403820_n256_2[4 * n4_4]);
        n2_1 = __sub_403820_byte_44339E[16 * v37] & 3;
        ::__sub_403820_n2 = n2_1;
        if ( (__sub_403820_byte_44339E[16 * v37] & 8) != 0 || n2_1 || __sub_403820_n256_0[0] )
        {
          i = *(unsigned __int16 *)p_i_1;
          Src = &p_i_1[v37 + 16];
          Size_1 = i * *((unsigned __int16 *)p_i_1 + 1);
          n4_1 = ::__sub_403820_n4_5;
          Size = Size_1;
          if ( ::__sub_403820_n4_5 == 1 )
          {
            sub_434980((char *)Src_1,(char *)Src,Size);
            n2_2 = ::__sub_403820_n2;
          }
          else
          {
            Block = &p_i_1[v37];
            if ( (int)Size <= 6
              || n4_1 <= 0
              || (n4_1 > 1 || Src_1 <= Src || Src_1 - (_BYTE *)Src < Size * ::__sub_403820_n4_5)
              && (Src_1 >= Src || (_BYTE *)Src - Src_1 < Size) )
            {
              *(_DWORD *)p_i = n2_1;
              v81 = v37;
              n4_10 = n4_4;
              Size_2 = Size;
              p_i_2 = p_i_1;
              Size_3 = 0;
              n4_2 = n4_1;
              v48 = 0;
              do
              {
                Src_1[Size_3] = Block[v48 + 16];
                v48 += n4_2;
                ++Size_3;
              }
              while ( Size_3 < Size_2 );
            }
            else
            {
              *(_DWORD *)p_i = n2_1;
              v81 = v37;
              n4_10 = n4_4;
              Size_4 = Size;
              p_i_2 = p_i_1;
              Size_5 = 0;
              n4_3 = n4_1;
              v44 = 0;
              do
              {
                Src_1[Size_5] = Block[v44 + 16];
                v44 += n4_3;
                ++Size_5;
              }
              while ( Size_5 < Size_4 );
            }
            n2_2 = *(_DWORD *)p_i;
            v37 = v81;
            n4_4 = n4_10;
            p_i_1 = p_i_2;
          }
          if ( n2_2 )
          {
            if ( n2_2 == 1 )
              sub_410310((int)Src_1, *(unsigned __int16 *)p_i_1, *((unsigned __int16 *)p_i_1 + 1));
          }
          else
          {
            sub_410650((unsigned int)Src_1, *(unsigned __int16 *)p_i_1, *((unsigned __int16 *)p_i_1 + 1));
          }
          sub_4081E0(p_i_1, (char *)Src_1, v37, v35);
        }
      }
      while ( n4_4 < ::__sub_403820_n4_5 );
      goto LABEL_104;
    }
  }
LABEL_105:
  __op_delete(Src_1);
LABEL_106:
  if ( (char *)::__sub_403820_Buffer + ElementCount != (void *)__sub_403820_Buffer_0 )
  {
LABEL_107:
    fclose(*(FILE **)(v5 + 4));
    *(_DWORD *)(v5 + 4) = 0;
    return nullptr;
  }
  __op_delete(::__sub_403820_Buffer);
  v88 = v91;
LABEL_109:
  if ( (v88 & 0x80) != 0 )
  {
    Buffer_3 = p_i_1[10] < 0 ? &p_i_1[*((_DWORD *)p_i_1 + 3) + 16] : nullptr;
    ElementCount_4 = fread(Buffer_3, 1u, ElementCount_3, *(FILE **)(v5 + 4));
    if ( ElementCount_4 != ElementCount_3 )
      goto LABEL_107;
  }
  if ( (p_i_1[11] & 2) != 0 )
  {
    n4_6 = (char *)__op_new(*((_DWORD *)p_i_1 + 3));
    __sub_403820_n4_5 = ::__sub_403820_n4_5;
    v55 = *((unsigned __int16 *)p_i_1 + 1);
    n4_1 = (int)n4_6;
    Src_2 = ::__sub_403820_n4_5 * (v55 - 1);
    sub_434980(n4_6,p_i_1 + 16,*((_DWORD *)p_i_1 + 3));
    LOWORD(v58) = *((_WORD *)p_i_1 + 1);
    if ( (_WORD)v58 )
    {
      Src = (void *)Src_2;
      n4_7 = (char *)n4_1;
      Blocka = n4_6;
      n4_8 = 0;
      v61 = 0;
      do
      {
        i_1 = *(unsigned __int16 *)p_i_1;
        n4_1 = n4_8;
        v86 = v61;
        Src_3 = Src;
        p_i_2 = p_i_1;
        v64 = &p_i_1[n4_8 + 16];
        do
        {
          n4_9 = __sub_403820_n4_5;
          do
          {
            *v64++ = *n4_7++;
            --n4_9;
          }
          while ( n4_9 );
          v64 = &v64[(_DWORD)Src_3];
          --i_1;
        }
        while ( i_1 );
        p_i_1 = p_i_2;
        v58 = *((unsigned __int16 *)p_i_2 + 1);
        n4_8 = __sub_403820_n4_5 + n4_1;
        v61 = v86 + 1;
      }
      while ( v86 + 1 < v58 );
      n4_6 = Blocka;
    }
    i_2 = *(_WORD *)p_i_1;
    *(_WORD *)p_i_1 = v58;
    p_i_1[11] ^= 2u;
    *((_WORD *)p_i_1 + 1) = i_2;
    *((_WORD *)p_i_1 + 2) = v58 * __sub_403820_n4_5;
    __op_delete(n4_6);
  }
  return p_i_1;
}

// __userpurge thunk for sub_403820 @ 0x00403820: reads the register arguments the
// caller passes, calls the moved body as cdecl, and pops 8 bytes of
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_403820()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $60, %esp\n"
    "mov %ecx, 12(%esp)\n"
    "movups %xmm1, 28(%esp)\n"
    "movups %xmm3, 44(%esp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "lea 52(%esp), %eax\n"
    "push %eax\n"
    "lea 40(%esp), %eax\n"
    "push %eax\n"
    "push 28(%esp)\n"
    "call __sub_403820\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret $8\n"
  );
}

#undef FILE
#undef fclose
#undef feof
#undef fread
#undef fseek
#undef sub_402E70
#undef sub_4081E0
#undef sub_40CF80
#undef sub_40E590
#undef sub_40FAC0
#undef sub_410310
#undef sub_410650
#undef sub_417DB0
#undef sub_42B830
#undef sub_434980
