// sub_402FE0 @ 0x00402FE0 — __userpurge
// Extracted from BMF.cpp:2586-2986 by extract.py per incdec.md.

typedef int t_sub_402FE0_Buffer;
static t_sub_402FE0_Buffer& __sub_402FE0_Buffer = *(t_sub_402FE0_Buffer*)0x0044337C;
typedef int t_sub_402FE0_Buffer_0;
static t_sub_402FE0_Buffer_0& __sub_402FE0_Buffer_0 = *(t_sub_402FE0_Buffer_0*)0x00443378;
typedef int t_sub_402FE0_Buffer_1;
static t_sub_402FE0_Buffer_1& __sub_402FE0_Buffer_1 = *(t_sub_402FE0_Buffer_1*)0x00443374;
typedef int t_sub_402FE0_ElementCount_0;
static t_sub_402FE0_ElementCount_0& __sub_402FE0_ElementCount_0 = *(t_sub_402FE0_ElementCount_0*)0x00443370;
typedef int t_sub_402FE0_buf;
static t_sub_402FE0_buf& __sub_402FE0_buf = *(t_sub_402FE0_buf*)0x00443380;
typedef unsigned char t_sub_402FE0_byte_44339C[0x10000];
static t_sub_402FE0_byte_44339C& __sub_402FE0_byte_44339C = *(t_sub_402FE0_byte_44339C*)0x0044339C;
typedef unsigned char t_sub_402FE0_byte_44339D[0x10000];
static t_sub_402FE0_byte_44339D& __sub_402FE0_byte_44339D = *(t_sub_402FE0_byte_44339D*)0x0044339D;
typedef unsigned char t_sub_402FE0_byte_44339E[0x10000];
static t_sub_402FE0_byte_44339E& __sub_402FE0_byte_44339E = *(t_sub_402FE0_byte_44339E*)0x0044339E;
typedef unsigned char t_sub_402FE0_byte_44339F[0x10000];
static t_sub_402FE0_byte_44339F& __sub_402FE0_byte_44339F = *(t_sub_402FE0_byte_44339F*)0x0044339F;
typedef int t_sub_402FE0_dword_44108C;
static t_sub_402FE0_dword_44108C& __sub_402FE0_dword_44108C = *(t_sub_402FE0_dword_44108C*)0x0044108C;
typedef int t_sub_402FE0_dword_441090;
static t_sub_402FE0_dword_441090& __sub_402FE0_dword_441090 = *(t_sub_402FE0_dword_441090*)0x00441090;
typedef int t_sub_402FE0_dword_441098;
static t_sub_402FE0_dword_441098& __sub_402FE0_dword_441098 = *(t_sub_402FE0_dword_441098*)0x00441098;
typedef int t_sub_402FE0_dword_443364;
static t_sub_402FE0_dword_443364& __sub_402FE0_dword_443364 = *(t_sub_402FE0_dword_443364*)0x00443364;
typedef int t_sub_402FE0_dword_443384;
static t_sub_402FE0_dword_443384& __sub_402FE0_dword_443384 = *(t_sub_402FE0_dword_443384*)0x00443384;
typedef int t_sub_402FE0_dword_443388;
static t_sub_402FE0_dword_443388& __sub_402FE0_dword_443388 = *(t_sub_402FE0_dword_443388*)0x00443388;
typedef int t_sub_402FE0_dword_4433A0[0x10000];
static t_sub_402FE0_dword_4433A0& __sub_402FE0_dword_4433A0 = *(t_sub_402FE0_dword_4433A0*)0x004433A0;
typedef int t_sub_402FE0_dword_4433A4[0x10000];
static t_sub_402FE0_dword_4433A4& __sub_402FE0_dword_4433A4 = *(t_sub_402FE0_dword_4433A4*)0x004433A4;
typedef int t_sub_402FE0_dword_4433A8[0x10000];
static t_sub_402FE0_dword_4433A8& __sub_402FE0_dword_4433A8 = *(t_sub_402FE0_dword_4433A8*)0x004433A8;
typedef int t_sub_402FE0_n2;
static t_sub_402FE0_n2& __sub_402FE0_n2 = *(t_sub_402FE0_n2*)0x00443360;
typedef int t_sub_402FE0_n256;
static t_sub_402FE0_n256& __sub_402FE0_n256 = *(t_sub_402FE0_n256*)0x0044336C;
typedef int t_sub_402FE0_n256_0[0x10000];
static t_sub_402FE0_n256_0& __sub_402FE0_n256_0 = *(t_sub_402FE0_n256_0*)0x00443398;
typedef int t_sub_402FE0_n4_5;
static t_sub_402FE0_n4_5& __sub_402FE0_n4_5 = *(t_sub_402FE0_n4_5*)0x00443394;
typedef int t_sub_402FE0_n512[0x10000];
static t_sub_402FE0_n512& __sub_402FE0_n512 = *(t_sub_402FE0_n512*)0x00443390;
typedef int t_sub_402FE0_n7_1;
static t_sub_402FE0_n7_1& __sub_402FE0_n7_1 = *(t_sub_402FE0_n7_1*)0x004410A0;
typedef int t_sub_402FE0_n8;
static t_sub_402FE0_n8& __sub_402FE0_n8 = *(t_sub_402FE0_n8*)0x00443368;

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980
static inline char * __fwd_sub_402FE0_sub_403820(int a0, const __m128 &a1, const __m128 &a2, int a3, void *a4) { return __sub_403820(a0, a1, a2, a3, (int *)a4); }
#define sub_403820 __fwd_sub_402FE0_sub_403820
static inline unsigned int __fwd_sub_402FE0_sub_4043E0(void *a0, char a1, const __m128 &a2, const __m128 &a3) { return __sub_4043E0((unsigned __int16 *)a0, a1, a2, a3); }
#define sub_4043E0 __fwd_sub_402FE0_sub_4043E0
static inline void __fwd_sub_402FE0_sub_405840(void *a0, void *a1, int a2, char a3, const __m128 &a4, const __m128 &a5) { __sub_405840((char *)a0, (char *)a1, a2, a3, a4, a5); }
#define sub_405840 __fwd_sub_402FE0_sub_405840
static inline void __fwd_sub_402FE0_sub_407B30(void *a0, int a1, char a2, const __m128 &a3, const __m128 &a4) { __sub_407B30((unsigned __int16 *)a0, a1, a2, a3, a4); }
#define sub_407B30 __fwd_sub_402FE0_sub_407B30
#define sub_408510 __sub_408510
static inline void __fwd_sub_402FE0_sub_415380(const __m128 &a0, const __m128 &a1, void *a2, void *a3, void *a4) { __sub_415380(a0, a1, (unsigned __int16 *)a2, (unsigned __int8 *)a3, (_BYTE *)a4); }
#define sub_415380 __fwd_sub_402FE0_sub_415380

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___feof
#define __PE_DECL___feof
typedef int t_feof(FILE1 *);   // _feof
static t_feof& __feof = *(t_feof*)0x0042D33B;
#endif
#define feof __feof
#ifndef __PE_DECL___fflush
#define __PE_DECL___fflush
typedef int t_fflush(FILE1 *);   // _fflush
static t_fflush& __fflush = *(t_fflush*)0x0042D351;
#endif
#define fflush __fflush
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

PROBE_DECL(__sub_402FE0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) int __sub_402FE0(int a1, const __m128 &a2__ref, const __m128 &a3__ref, unsigned __int16 *p_i, void *__sub_402FE0_Buffer)
{
  alignas(16) unsigned char __hexrays_frame[80];   // original frame, ebp-0x40..ebp+0x0
  char * &Buffera_4 = *(char * *)(__hexrays_frame + 0);
  size_t &ElementCount = *(size_t *)(__hexrays_frame + 16);
  int &ElementCounta = *(int *)(__hexrays_frame + 16);
  size_t &ElementCountb = *(size_t *)(__hexrays_frame + 16);
  char * &Buffera = *(char * *)(__hexrays_frame + 20);
  int &n4_2 = *(int *)(__hexrays_frame + 24);
  char * &Buffera_1 = *(char * *)(__hexrays_frame + 28);
  int &v64 = *(int *)(__hexrays_frame + 32);
  int &v65 = *(int *)(__hexrays_frame + 36);
  int &v66 = *(int *)(__hexrays_frame + 40);
  void * &Buffer_2 = *(void * *)(__hexrays_frame + 44);
  PROBE_HIT(__sub_402FE0);
  __m128 a2 = a2__ref;
  __m128 a3 = a3__ref;
  int v5; // ebp
  FILE *i; // ebx
  char __sub_402FE0_Buffer_1; // al
  unsigned __int16 *p_i_1; // ebx
  int __sub_402FE0_n4_5; // ecx
  char *Buffera_5; // edi
  int v11; // eax
  char v12; // dl
  char v13; // fps
  char v15; // cl
  size_t ElementCount_1; // esi
  char v17; // dl
  int v18; // edx
  int n4_6; // ecx
  char *Buffera_6; // eax
  char v21; // fps
  unsigned int n7; // eax
  int __sub_402FE0_n8; // edx
  int n4; // edi
  unsigned int v25; // ebp
  unsigned int v26; // ebp
  int v27; // ebp
  unsigned int v28; // ebp
  int n8_1; // edx
  unsigned int v30; // ebp
  unsigned int v31; // ebp
  unsigned int v32; // eax
  int __sub_402FE0_n256; // eax
  size_t Size; // edx
  char *Srca; // edi
  char v36; // fps
  int n4_1; // ebp
  bool v38; // cf
  unsigned __int8 v39; // di
  int v40; // edi
  int v41; // edx
  char v42; // fps
  int v43; // edx
  int n4_3; // ecx
  char *Buffera_2; // esi
  char *Buffera_3; // edi
  int v47; // eax
  int i_1; // edx
  _BYTE *v49; // ebp
  int v50; // edi
  int n4_4; // ebx
  unsigned __int16 i_2; // ax
  unsigned __int16 v53; // cx
  unsigned __int8 v54; // di
  size_t v55; // eax
  int v56; // ebx

  v5 = a1;
  if ( !*(_DWORD *)(a1 + 4) )
    return 0;
  if ( !feof(*(FILE **)(a1 + 4)) )
  {
    sub_403820(v5, a2, a3, 1, nullptr);
    for ( i = *(FILE **)(v5 + 4); i; i = *(FILE **)(v5 + 4) )
    {
      if ( feof(*(FILE **)(v5 + 4)) )
        break;
      if ( feof(i) )
        break;
      sub_403820(v5, a2, a3, 1, nullptr);
    }
  }
  __sub_402FE0_Buffer_1 = (char)__sub_402FE0_Buffer;
  p_i_1 = p_i;
  __sub_402FE0_n4_5 = *((_DWORD *)p_i + 1);
  if ( __sub_402FE0_Buffer )
    __sub_402FE0_Buffer_1 = 1;
  Buffera = *(char **)p_i;
  *((_BYTE *)p_i + 11) |= __sub_402FE0_Buffer_1 << 7;
  Buffera_5 = *((char **)p_i + 2);
  v11 = *((_DWORD *)p_i + 3);
  n4_2 = __sub_402FE0_n4_5;
  __sub_402FE0_n512[0] = 512;
  v12 = *((_BYTE *)p_i + 10);
  __sub_402FE0_n256_0[0] = 0;
  Buffera_1 = Buffera_5;
  v64 = v11;
  ::__sub_402FE0_n4_5 = ((v12 & 0x3Fu) + 7) >> 3;
  if ( fwrite("\x81\x8A""20\x81\x90""20a+b", 4u, 1u, *(FILE **)(v5 + 4)) != 1 )
    return 0;
  v15 = *((_BYTE *)p_i + 10);
  ++*(_DWORD *)v5;
  ElementCount_1 = v15 & 0x80;
  if ( v15 < 0 )
    ElementCount_1 = 3 << (v15 & 31);
  if ( !__sub_402FE0_dword_441098 || *((_DWORD *)p_i + 3) < 0x10u )
    goto LABEL_76;
  __sub_402FE0_dword_443384 = __sub_402FE0_dword_441090;
  v17 = *((_BYTE *)p_i + 10);
  HIBYTE(Buffera_1) |= (unsigned __int8)(4 * __sub_402FE0_dword_441090) | 0x20;
  if ( (v17 & 0x3Fu) <= 4 || !__sub_402FE0_dword_44108C )
  {
    __sub_402FE0_ElementCount_0 = *((_DWORD *)p_i + 3) + 0x20000;
    ::__sub_402FE0_Buffer = __op_new(__sub_402FE0_ElementCount_0);
    ::__sub_402FE0_n8 = 0;
    ::__sub_402FE0_n256 = 0;
    __sub_402FE0_Buffer_0 = (int)::__sub_402FE0_Buffer;
    ::__sub_402FE0_Buffer_1 = (int)::__sub_402FE0_Buffer;
    __sub_402FE0_buf = (char *)::__sub_402FE0_Buffer + __sub_402FE0_ElementCount_0 - 4096;
    __sub_402FE0_n2 = 0;
    __sub_402FE0_dword_443364 = 0;
    __sub_402FE0_dword_443388 = 0;
    if ( __sub_402FE0_dword_443384 )
      sub_415380(a2, a3, p_i, (unsigned __int8 *)p_i + 16, (_BYTE *)p_i + 16);
    else
      sub_408510((int)(p_i + 8), *((_DWORD *)p_i + 3), p_i[2]);
    goto LABEL_57;
  }
  ElementCount = sub_4043E0(p_i, v13, a2, a3);
  HIBYTE(Buffera_1) |= 0x10u;
  if ( (*((_BYTE *)p_i + 11) & 2) != 0 )
  {
    n4_6 = *((_DWORD *)p_i + 1);
    Buffera_6 = *((char **)p_i + 2);
    Buffera = *(char **)p_i;
    v18 = *((_DWORD *)p_i + 3);
    n4_2 = n4_6;
    Buffera_1 = Buffera_6;
    v64 = v18;
    HIBYTE(Buffera_1) = (4 * __sub_402FE0_dword_443384) | 0x30 | HIBYTE(Buffera_6);
  }
  else
  {
    v18 = *((_DWORD *)p_i + 3);
  }
  __sub_402FE0_ElementCount_0 = v18 + 0x20000;
  ::__sub_402FE0_Buffer = __op_new(v18 + 0x20000);
  __sub_402FE0_Buffer_0 = (int)::__sub_402FE0_Buffer;
  ::__sub_402FE0_n8 = 0;
  ::__sub_402FE0_n256 = 0;
  ::__sub_402FE0_Buffer_1 = (int)::__sub_402FE0_Buffer;
  __sub_402FE0_buf = (char *)::__sub_402FE0_Buffer + __sub_402FE0_ElementCount_0 - 4096;
  if ( ::__sub_402FE0_n4_5 == 1 )
  {
    if ( (p_i[5] & 0x40) != 0 )
    {
LABEL_22:
      n7 = __sub_402FE0_n7_1;
      __sub_402FE0_n256_0[0] = __sub_402FE0_n7_1;
      if ( ::__sub_402FE0_n8 < 4 )
      {
        *(_DWORD *)::__sub_402FE0_Buffer_1 = ::__sub_402FE0_n256 | (2 * (__sub_402FE0_n7_1 << ((31 - ::__sub_402FE0_n8) & 31)));
        ::__sub_402FE0_Buffer_1 = __sub_402FE0_Buffer_0;
        ::__sub_402FE0_n256 = n7 >> (::__sub_402FE0_n8 & 31);
        ::__sub_402FE0_n8 += 28;
        __sub_402FE0_Buffer_0 += 4;
      }
      else
      {
        ::__sub_402FE0_n256 |= __sub_402FE0_n7_1 << (-(char)::__sub_402FE0_n8 & 31);
        ::__sub_402FE0_n8 -= 4;
      }
    }
  }
  else if ( ::__sub_402FE0_n4_5 > 2 )
  {
    goto LABEL_22;
  }
  __sub_402FE0_dword_443388 = 0;
  if ( ::__sub_402FE0_n4_5 > 0 )
  {
    __sub_402FE0_n8 = ::__sub_402FE0_n8;
    v66 = v5;
    n4 = 0;
    do
    {
      v25 = (4 * (unsigned __int8)__sub_402FE0_byte_44339E[16 * n4]) | (unsigned __int8)__sub_402FE0_byte_44339C[16 * n4];
      if ( __sub_402FE0_n8 < 6 )
      {
        *(_DWORD *)::__sub_402FE0_Buffer_1 = ::__sub_402FE0_n256 | (2 * (v25 << ((31 - __sub_402FE0_n8) & 31)));
        ::__sub_402FE0_Buffer_1 = __sub_402FE0_Buffer_0;
        __sub_402FE0_Buffer_0 += 4;
        __sub_402FE0_n8 = ::__sub_402FE0_n8 + 26;
        ::__sub_402FE0_n256 = v25 >> (::__sub_402FE0_n8 & 31);
      }
      else
      {
        ::__sub_402FE0_n256 |= v25 << (-(char)__sub_402FE0_n8 & 31);
        __sub_402FE0_n8 = ::__sub_402FE0_n8 - 6;
      }
      ::__sub_402FE0_n8 = __sub_402FE0_n8;
      if ( (__sub_402FE0_byte_44339E[16 * n4] & 8) != 0 )
      {
        v26 = (unsigned __int8)__sub_402FE0_byte_44339F[16 * n4];
        if ( __sub_402FE0_n8 < 8 )
        {
          *(_DWORD *)::__sub_402FE0_Buffer_1 = ::__sub_402FE0_n256 | (2 * (v26 << ((31 - __sub_402FE0_n8) & 31)));
          ::__sub_402FE0_Buffer_1 = __sub_402FE0_Buffer_0;
          __sub_402FE0_Buffer_0 += 4;
          __sub_402FE0_n8 = ::__sub_402FE0_n8 + 24;
          ::__sub_402FE0_n256 = v26 >> (::__sub_402FE0_n8 & 31);
        }
        else
        {
          v27 = v26 << (-(char)__sub_402FE0_n8 & 31);
          __sub_402FE0_n8 -= 8;
          ::__sub_402FE0_n256 |= v27;
        }
        ::__sub_402FE0_n8 = __sub_402FE0_n8;
        if ( (unsigned __int8)__sub_402FE0_byte_44339C[16 * n4] > 1u )
        {
          v28 = __sub_402FE0_dword_4433A0[4 * n4] + 64;
          if ( __sub_402FE0_n8 < 8 )
          {
            *(_DWORD *)::__sub_402FE0_Buffer_1 = ::__sub_402FE0_n256 | (2 * (v28 << ((31 - __sub_402FE0_n8) & 31)));
            ::__sub_402FE0_Buffer_1 = __sub_402FE0_Buffer_0;
            __sub_402FE0_Buffer_0 += 4;
            n8_1 = ::__sub_402FE0_n8 + 24;
            ::__sub_402FE0_n256 = v28 >> (::__sub_402FE0_n8 & 31);
          }
          else
          {
            ::__sub_402FE0_n256 |= v28 << (-(char)__sub_402FE0_n8 & 31);
            n8_1 = ::__sub_402FE0_n8 - 8;
          }
          ::__sub_402FE0_n8 = n8_1;
          v30 = __sub_402FE0_dword_4433A4[4 * n4] + 64;
          if ( n8_1 < 8 )
          {
            *(_DWORD *)::__sub_402FE0_Buffer_1 = ::__sub_402FE0_n256 | (2 * (v30 << ((31 - n8_1) & 31)));
            ::__sub_402FE0_Buffer_1 = __sub_402FE0_Buffer_0;
            __sub_402FE0_Buffer_0 += 4;
            __sub_402FE0_n8 = ::__sub_402FE0_n8 + 24;
            ::__sub_402FE0_n256 = v30 >> (::__sub_402FE0_n8 & 31);
          }
          else
          {
            v31 = v30 << (-(char)n8_1 & 31);
            __sub_402FE0_n8 = n8_1 - 8;
            ::__sub_402FE0_n256 |= v31;
          }
          ::__sub_402FE0_n8 = __sub_402FE0_n8;
          if ( (unsigned __int8)__sub_402FE0_byte_44339C[16 * n4] > 2u )
          {
            v32 = __sub_402FE0_dword_4433A8[4 * n4] + 64;
            if ( __sub_402FE0_n8 < 8 )
            {
              *(_DWORD *)::__sub_402FE0_Buffer_1 = ::__sub_402FE0_n256 | (2 * (v32 << ((31 - __sub_402FE0_n8) & 31)));
              ::__sub_402FE0_Buffer_1 = __sub_402FE0_Buffer_0;
              __sub_402FE0_Buffer_0 += 4;
              __sub_402FE0_n256 = v32 >> (::__sub_402FE0_n8 & 31);
              __sub_402FE0_n8 = ::__sub_402FE0_n8 + 24;
              ::__sub_402FE0_n8 += 24;
              ::__sub_402FE0_n256 = __sub_402FE0_n256;
            }
            else
            {
              ::__sub_402FE0_n256 |= v32 << (-(char)__sub_402FE0_n8 & 31);
              __sub_402FE0_n8 = ::__sub_402FE0_n8 - 8;
              ::__sub_402FE0_n8 -= 8;
            }
          }
        }
      }
      ++n4;
    }
    while ( n4 < ::__sub_402FE0_n4_5 );
    v5 = v66;
  }
  if ( ElementCount )
  {
    Size = *p_i * p_i[1];
    HIBYTE(Buffera_1) |= 8u;
    Srca = (char *)__op_new(Size);
    if ( ::__sub_402FE0_n4_5 > 0 )
    {
      v66 = v5;
      n4_1 = 0;
      do
        sub_405840((char *)p_i, Srca, (unsigned __int8)__sub_402FE0_byte_44339D[16 * n4_1++], v36, a2, a3);
      while ( n4_1 < ::__sub_402FE0_n4_5 );
      v5 = v66;
    }
    __op_delete(Srca);
  }
  else
  {
    sub_407B30(p_i, (int)p_i, v21, a2, a3);
  }
LABEL_57:
  *(_DWORD *)::__sub_402FE0_Buffer_1 = ::__sub_402FE0_n256;
  v38 = (unsigned int)(__sub_402FE0_Buffer_0 - (_DWORD)::__sub_402FE0_Buffer) < *((_DWORD *)p_i + 3);
  ElementCounta = __sub_402FE0_Buffer_0 - (_DWORD)::__sub_402FE0_Buffer;
  v64 = __sub_402FE0_Buffer_0 - (_DWORD)::__sub_402FE0_Buffer;
  if ( v38 )
  {
    v39 = fwrite(&Buffera, 1u, 0x10u, *(FILE **)(v5 + 4)) == 16;
    if ( __sub_402FE0_Buffer )
      v39 &= fwrite(__sub_402FE0_Buffer, 1u, *((_DWORD *)__sub_402FE0_Buffer + 1) + 8, *(FILE **)(v5 + 4)) == *((_DWORD *)__sub_402FE0_Buffer + 1) + 8;
    v40 = (fwrite(::__sub_402FE0_Buffer, 1u, ElementCounta, *(FILE **)(v5 + 4)) == ElementCounta) & v39;
    __op_delete(::__sub_402FE0_Buffer);
    if ( v40 && (p_i[5] & 0x80) != 0 )
      fwrite((char *)p_i + *((_DWORD *)p_i + 3) + 16, 1u, ElementCount_1, *(FILE **)(v5 + 4));
    fflush(*(FILE **)(v5 + 4));
    if ( v40 )
      return v64;
    return v40;
  }
  __op_delete(::__sub_402FE0_Buffer);
  if ( (*((_BYTE *)p_i + 11) & 2) != 0 )
  {
    Buffera = (char *)__op_new(*((_DWORD *)p_i + 3));
    v41 = p_i[1];
    n4_2 = ::__sub_402FE0_n4_5;
    Buffera_1 = Buffera;
    v64 = ::__sub_402FE0_n4_5 * (v41 - 1);
    Buffer_2 = p_i + 8;
    sub_434980(Buffera,(char *)p_i + 16,*((_DWORD *)p_i + 3));
    LOWORD(v43) = p_i[1];
    if ( (_WORD)v43 )
    {
      n4_3 = n4_2;
      ElementCountb = ElementCount_1;
      Buffera_2 = Buffera_1;
      Buffera_3 = nullptr;
      v47 = 0;
      v66 = v5;
      do
      {
        i_1 = *p_i_1;
        v65 = v47;
        Buffera_1 = Buffera_3;
        v49 = (char *)p_i_1 + v47 + 16;
        v50 = v64;
        do
        {
          n4_4 = n4_3;
          do
          {
            *v49++ = *Buffera_2++;
            --n4_4;
          }
          while ( n4_4 );
          v49 += v50;
          --i_1;
        }
        while ( i_1 );
        p_i_1 = p_i;
        v43 = p_i[1];
        v47 = n4_3 + v65;
        Buffera_3 = Buffera_1 + 1;
      }
      while ( (int)(Buffera_1 + 1) < v43 );
      ElementCount_1 = ElementCountb;
      v5 = v66;
    }
    Buffera_4 = Buffera;
    i_2 = *p_i_1;
    v53 = v43 * n4_2;
    *p_i_1 = v43;
    p_i_1[1] = i_2;
    *((_BYTE *)p_i_1 + 11) ^= 2u;
    p_i_1[2] = v53;
    __op_delete(Buffera_4);
    goto LABEL_77;
  }
LABEL_76:
  Buffer_2 = p_i + 8;
LABEL_77:
  v54 = fwrite(p_i_1, 1u, 0x10u, *(FILE **)(v5 + 4)) == 16;
  if ( __sub_402FE0_Buffer )
    v54 &= fwrite(__sub_402FE0_Buffer, 1u, *((_DWORD *)__sub_402FE0_Buffer + 1) + 8, *(FILE **)(v5 + 4)) == *((_DWORD *)__sub_402FE0_Buffer + 1) + 8;
  v55 = fwrite(Buffer_2, 1u, ElementCount_1 + *((_DWORD *)p_i_1 + 3), *(FILE **)(v5 + 4));
  v56 = *((_DWORD *)p_i_1 + 3);
  if ( (v54 & (v55 == v56 + ElementCount_1)) == 0 )
    return 0;
  return v56;
}

// __userpurge thunk for sub_402FE0 @ 0x00402FE0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and pops 8 bytes of
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_402FE0()
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
    "call __sub_402FE0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret $8\n"
  );
}

#undef FILE
#undef feof
#undef fflush
#undef fwrite
#undef sub_403820
#undef sub_4043E0
#undef sub_405840
#undef sub_407B30
#undef sub_408510
#undef sub_415380
#undef sub_434980
