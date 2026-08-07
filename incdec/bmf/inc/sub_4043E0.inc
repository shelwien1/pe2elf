// sub_4043E0 @ 0x004043E0 — __usercall
// Extracted from BMF.cpp:3574-4720 by extract.py per incdec.md.

typedef int t_sub_4043E0_Buffer;
static t_sub_4043E0_Buffer& __sub_4043E0_Buffer = *(t_sub_4043E0_Buffer*)(blob1 + 0x0044337C - BMF_BLOB_BASE);
typedef int t_sub_4043E0_Buffer_0;
static t_sub_4043E0_Buffer_0& __sub_4043E0_Buffer_0 = *(t_sub_4043E0_Buffer_0*)(blob1 + 0x00443378 - BMF_BLOB_BASE);
typedef int t_sub_4043E0_Buffer_1;
static t_sub_4043E0_Buffer_1& __sub_4043E0_Buffer_1 = *(t_sub_4043E0_Buffer_1*)(blob1 + 0x00443374 - BMF_BLOB_BASE);
typedef int t_sub_4043E0_ElementCount_0;
static t_sub_4043E0_ElementCount_0& __sub_4043E0_ElementCount_0 = *(t_sub_4043E0_ElementCount_0*)(blob1 + 0x00443370 - BMF_BLOB_BASE);
typedef int t_sub_4043E0_buf;
static t_sub_4043E0_buf& __sub_4043E0_buf = *(t_sub_4043E0_buf*)(blob1 + 0x00443380 - BMF_BLOB_BASE);
typedef unsigned char t_sub_4043E0_byte_44339C[0x10000];
static t_sub_4043E0_byte_44339C& __sub_4043E0_byte_44339C = *(t_sub_4043E0_byte_44339C*)(blob1 + 0x0044339C - BMF_BLOB_BASE);
typedef unsigned char t_sub_4043E0_byte_44339D[0x10000];
static t_sub_4043E0_byte_44339D& __sub_4043E0_byte_44339D = *(t_sub_4043E0_byte_44339D*)(blob1 + 0x0044339D - BMF_BLOB_BASE);
typedef unsigned char t_sub_4043E0_byte_44339E[0x10000];
static t_sub_4043E0_byte_44339E& __sub_4043E0_byte_44339E = *(t_sub_4043E0_byte_44339E*)(blob1 + 0x0044339E - BMF_BLOB_BASE);
typedef unsigned char t_sub_4043E0_byte_4433AD[16];
static t_sub_4043E0_byte_4433AD& __sub_4043E0_byte_4433AD = *(t_sub_4043E0_byte_4433AD*)(blob1 + 0x004433AD - BMF_BLOB_BASE);
typedef int t_sub_4043E0_dword_4410A4;
static t_sub_4043E0_dword_4410A4& __sub_4043E0_dword_4410A4 = *(t_sub_4043E0_dword_4410A4*)(blob1 + 0x004410A4 - BMF_BLOB_BASE);
typedef int t_sub_4043E0_dword_443384;
static t_sub_4043E0_dword_443384& __sub_4043E0_dword_443384 = *(t_sub_4043E0_dword_443384*)(blob1 + 0x00443384 - BMF_BLOB_BASE);
typedef int t_sub_4043E0_n256;
static t_sub_4043E0_n256& __sub_4043E0_n256 = *(t_sub_4043E0_n256*)(blob1 + 0x0044336C - BMF_BLOB_BASE);
typedef int t_sub_4043E0_n256_0[0x10000];
static t_sub_4043E0_n256_0& __sub_4043E0_n256_0 = *(t_sub_4043E0_n256_0*)(blob1 + 0x00443398 - BMF_BLOB_BASE);
typedef int t_sub_4043E0_n256_2[0x10000];
static t_sub_4043E0_n256_2& __sub_4043E0_n256_2 = *(t_sub_4043E0_n256_2*)(blob1 + 0x0044338C - BMF_BLOB_BASE);
typedef int t_sub_4043E0_n2_4;
static t_sub_4043E0_n2_4& __sub_4043E0_n2_4 = *(t_sub_4043E0_n2_4*)(blob1 + 0x00441094 - BMF_BLOB_BASE);
typedef int t_sub_4043E0_n4_5;
static t_sub_4043E0_n4_5& __sub_4043E0_n4_5 = *(t_sub_4043E0_n4_5*)(blob1 + 0x00443394 - BMF_BLOB_BASE);
typedef int t_sub_4043E0_n512[0x10000];
static t_sub_4043E0_n512& __sub_4043E0_n512 = *(t_sub_4043E0_n512*)(blob1 + 0x00443390 - BMF_BLOB_BASE);
typedef int t_sub_4043E0_n7_0;
static t_sub_4043E0_n7_0& __sub_4043E0_n7_0 = *(t_sub_4043E0_n7_0*)(blob1 + 0x0044109C - BMF_BLOB_BASE);
typedef int t_sub_4043E0_n8;
static t_sub_4043E0_n8& __sub_4043E0_n8 = *(t_sub_4043E0_n8*)(blob1 + 0x00443368 - BMF_BLOB_BASE);

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980
static inline void __fwd_sub_4043E0_sub_405840(void *a0, void *a1, int a2, char a3, const __m128 &a4, const __m128 &a5) { __sub_405840((char *)a0, (char *)a1, a2, a3, a4, a5); }
#define sub_405840 __fwd_sub_4043E0_sub_405840
#define sub_405CF0 __sub_405CF0
static inline void __fwd_sub_4043E0_sub_407B30(void *a0, int a1, char a2, const __m128 &a3, const __m128 &a4) { __sub_407B30((unsigned __int16 *)a0, a1, a2, a3, a4); }
#define sub_407B30 __fwd_sub_4043E0_sub_407B30
#define sub_42B830 __sub_42B830

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
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

PROBE_DECL(__sub_4043E0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) unsigned int __sub_4043E0(unsigned __int16 *p_i, char a2, const __m128 &a3__ref, const __m128 &a4__ref)
{
  alignas(16) unsigned char __hexrays_frame[164];   // original frame, ebp-0x94..ebp+0x0
  char * &v175 = *(char * *)(__hexrays_frame + 0);
  char * &v176 = *(char * *)(__hexrays_frame + 0);
  _QWORD (&v177)[2] = *(_QWORD (*)[2])(__hexrays_frame + 4);
  char * (&v178)[2] = *(char * (*)[2])(__hexrays_frame + 20);
  int (&v179)[2] = *(int (*)[2])(__hexrays_frame + 28);
  int &v180 = *(int *)(__hexrays_frame + 36);
  _DWORD (&v181)[4] = *(_DWORD (*)[4])(__hexrays_frame + 40);
  int &v182 = *(int *)(__hexrays_frame + 56);
  void * &Srca_7 = *(void * *)(__hexrays_frame + 60);
  int &v184 = *(int *)(__hexrays_frame + 64);
  char * &n5_1 = *(char * *)(__hexrays_frame + 68);
  void * &Src = *(void * *)(__hexrays_frame + 100);
  char * &n4_10 = *(char * *)(__hexrays_frame + 104);
  int &v188 = *(int *)(__hexrays_frame + 108);
  int &v189 = *(int *)(__hexrays_frame + 112);
  char * &n4_15 = *(char * *)(__hexrays_frame + 116);
  unsigned __int16 * &p_i_2 = *(unsigned __int16 * *)(__hexrays_frame + 120);
  char * &Blockb = *(char * *)(__hexrays_frame + 124);
  PROBE_HIT(__sub_4043E0);
  __m128 a3 = a3__ref;
  __m128 a4 = a4__ref;
  unsigned __int16 *p_i_1; // esi
  int i; // edi
  int i_2; // ebx
  int i_1; // eax
  signed int i_3; // eax
  int n4; // eax
  int v10; // edx
  char *n4_1; // edx
  unsigned int v13; // eax
  int v14; // ecx
  unsigned int v15; // ebx
  int v16; // edi
  int v17; // esi
  int v18; // edi
  char v19; // fps
  int n4_4; // edx
  int v21; // eax
  int v22; // ecx
  int v23; // edi
  char *v24; // edi
  int Size; // eax
  char *v26; // ebx
  char *v27; // esi
  char *n4_13; // esi
  int n0x7FFFFFFF; // ebx
  char *Blockb_2; // eax
  char *Srca_1; // edx
  int v32; // ecx
  int n0x7FFFFFFF_8; // eax
  int n0x7FFFFFFF_2; // edx
  bool v35; // zf
  int n5; // eax
  int n2; // edi
  char *Srca_6; // edx
  int n0x7FFFFFFF_7; // eax
  int v40; // ecx
  int v41; // edx
  int v42; // edi
  int v43; // ebx
  char v44; // fps
  int v45; // ebx
  char *v46; // edi
  int n4_2; // ebx
  int v48; // eax
  char v49; // fps
  int v50; // ecx
  int v51; // edx
  int v52; // eax
  int i_4; // ecx
  char *v54; // edx
  _BYTE *v55; // edi
  int n4_3; // esi
  unsigned __int16 i_5; // ax
  int n16_1; // eax
  int n4_7; // eax
  int n4_8; // edx
  int v61; // ecx
  char v62; // al
  char v63; // fps
  char *n4_14; // eax
  unsigned int n64_2; // eax
  int n16_2; // edi
  char *v67; // ebx
  int n4_9; // edx
  int v69; // ecx
  char v70; // al
  int v71; // eax
  unsigned int n64_1; // eax
  int n16; // edi
  char *v74; // ebx
  int __sub_4043E0_n4_5; // eax
  int v76; // ecx
  char v77; // dl
  int n4_20; // eax
  int n4_6; // eax
  unsigned int n64; // eax
  char v81; // fps
  char v82; // fps
  int n16_3; // eax
  int n4_11; // edx
  int v85; // ecx
  char v86; // al
  char v87; // fps
  char *n4_17; // edx
  int n4_16; // eax
  unsigned int n64_3; // edx
  int n16_4; // eax
  int n4_12; // eax
  char v93; // fps
  int n4_18; // eax
  unsigned int n64_4; // eax
  int v96; // edx
  unsigned int v97; // edi
  int v98; // esi
  int v99; // ebx
  int v100; // edi
  char *v101; // ebx
  int v102; // edx
  char v103; // fps
  int v104; // ecx
  char *v105; // ebx
  int v106; // edx
  char *Blockb_6; // esi
  int v108; // eax
  int v109; // ecx
  char *v110; // edi
  char *v111; // edx
  char *v112; // esi
  char *Blockb_7; // edi
  __int16 v114; // ax
  __int16 v115; // dx
  char v116; // fps
  int n4_19; // edi
  int v118; // ebx
  int v119; // ecx
  int v120; // eax
  int v121; // edx
  char v122; // fps
  int v123; // eax
  char *v124; // edx
  int v125; // edi
  int v126; // ebx
  int i_6; // eax
  _BYTE *v128; // ecx
  _BYTE *v129; // esi
  char *v130; // edi
  unsigned __int16 i_7; // dx
  unsigned __int16 v132; // cx
  int v133; // ebx
  char v134; // fps
  int v135; // ecx
  char *v136; // ebx
  int v137; // edx
  char *Blockb_8; // esi
  int v139; // eax
  int v140; // ecx
  char *v141; // edi
  char *v142; // edx
  char *v143; // esi
  char *Blockb_9; // ebx
  __int16 v145; // ax
  __int16 v146; // dx
  char *Blockb_4; // eax
  char *Srca_3; // edx
  int v149; // ecx
  int n0x7FFFFFFF_10; // ecx
  int n0x7FFFFFFF_4; // edi
  int n5_3; // eax
  char *Blockb_5; // eax
  char *Srca_4; // edx
  int v155; // ecx
  int n0x7FFFFFFF_11; // ecx
  char *n0x7FFFFFFF_5; // edi
  int n5_4; // edx
  char *Srca_5; // edx
  int v160; // ecx
  int n0x7FFFFFFF_6; // edx
  bool v162; // cc
  int n5_5; // eax
  char *Blockb_3; // eax
  char *Srca_2; // edx
  int v166; // ecx
  int n0x7FFFFFFF_9; // ecx
  int n0x7FFFFFFF_3; // edi
  int n5_2; // eax
  char *Blockb_1; // eax
  char *Srca; // edx
  int v172; // ecx
  int n0x7FFFFFFF_1; // edx
  char *n5_6; // eax

  p_i_1 = p_i;
  i = *p_i;
  i_2 = p_i[1];
  if ( (unsigned int)__sub_4043E0_n7_0 < 9 )
  {
    i_1 = p_i[1];
    if ( i >= i_2 )
      i_1 = i;
    i_3 = (((i_1 * (__sub_4043E0_dword_443384 + __sub_4043E0_n7_0 + 1) + i_1) >> 4) + 3) & 0xFFFFFFFC;
    if ( i_3 < (__sub_4043E0_dword_443384 + __sub_4043E0_n7_0 + 1) << 6 )
      i_3 = (__sub_4043E0_dword_443384 + __sub_4043E0_n7_0 + 1) << 6;
    if ( i_3 < i )
      i = i_3;
    if ( i_3 < i_2 )
      i_2 = i_3;
  }
  if ( i < 4 || i_2 < 3 )
  {
    if ( ::__sub_4043E0_n4_5 > 0 )
    {
      n4 = 0;
      do
      {
        v10 = 16 * n4;
        __sub_4043E0_byte_44339E[v10] = 0;
        __sub_4043E0_byte_44339D[v10] = n4;
        __sub_4043E0_byte_44339C[v10] = n4++;
      }
      while ( n4 < ::__sub_4043E0_n4_5 );
    }
    return 0;
  }
  sub_405CF0((int)p_i_1, i_2, a2);
  if ( __sub_4043E0_n2_4 == 2 )
  {
    n4_1 = (char *)::__sub_4043E0_n4_5;
    v13 = __sub_4043E0_dword_4410A4;
    if ( (HIWORD(__sub_4043E0_dword_4410A4) & 0xF) == ::__sub_4043E0_n4_5 + 8 * __sub_4043E0_dword_443384 )
    {
      v14 = __sub_4043E0_dword_4410A4;
      if ( ::__sub_4043E0_n4_5 - 1 >= 0 )
      {
        v179[0] = ::__sub_4043E0_n4_5 / 2;
        if ( ::__sub_4043E0_n4_5 / 2 )
        {
          v178[0] = (char *)::__sub_4043E0_n4_5;
          v178[1] = (char *)__sub_4043E0_dword_4410A4;
          p_i_2 = p_i_1;
          v15 = 0;
          v16 = 4 * ::__sub_4043E0_n4_5;
          v17 = 0;
          do
          {
            ++v15;
            __sub_4043E0_byte_44339E[16 * BYTE1(__sub_4043E0_n256_2[v17 + v16])] = v14 & 0xF;
            __sub_4043E0_byte_44339E[16 * *(unsigned __int8 *)(v17 * 4 + v16 * 4 + BMF_BLOB(0x0044337D))] = (unsigned __int8)v14 >> 4;
            v14 >>= 8;
            v17 -= 8;
          }
          while ( v15 < v179[0] );
          n4_1 = v178[0];
          v13 = (unsigned int)v178[1];
          p_i_1 = p_i_2;
          v18 = 2 * v15 + 1;
        }
        else
        {
          v18 = 1;
        }
        if ( (unsigned int)n4_1 > v18 - 1 )
          __sub_4043E0_byte_44339E[16 * (unsigned __int8)__sub_4043E0_byte_44339D[16 * (_DWORD)&n4_1[-v18]]] = v14 & 0xF;
      }
      if ( (v13 & 0x200000) != 0 )
      {
        v46 = (char *)__op_new(*((_DWORD *)p_i_1 + 3));
        n4_2 = ::__sub_4043E0_n4_5;
        v48 = p_i_1[1];
        v178[1] = v46;
        v180 = ::__sub_4043E0_n4_5 * (v48 - 1);
        sub_434980(v46,(char *)p_i_1 + 16,*((_DWORD *)p_i_1 + 3));
        LOWORD(v50) = p_i_1[1];
        if ( (_WORD)v50 )
        {
          v178[0] = v46;
          v51 = 0;
          v52 = 0;
          do
          {
            i_4 = *p_i_1;
            v179[1] = v52;
            v179[0] = v51;
            v54 = v178[1];
            p_i_2 = p_i_1;
            v55 = (char *)p_i_1 + v52 + 16;
            do
            {
              n4_3 = n4_2;
              do
              {
                *v55++ = *v54++;
                --n4_3;
              }
              while ( n4_3 );
              v55 += v180;
              --i_4;
            }
            while ( i_4 );
            p_i_1 = p_i_2;
            v50 = p_i_2[1];
            v178[1] = v54;
            v52 = n4_2 + v179[1];
            v51 = v179[0] + 1;
          }
          while ( v179[0] + 1 < v50 );
          v46 = v178[0];
        }
        i_5 = *p_i_1;
        *p_i_1 = v50;
        *((_BYTE *)p_i_1 + 11) ^= 2u;
        p_i_1[1] = i_5;
        p_i_1[2] = v50 * n4_2;
        __op_delete(v46);
        v13 = __sub_4043E0_dword_4410A4;
      }
      return (v13 & 0x100000) >> 20;
    }
  }
  Blockb = (char *)sub_42B830(i, i_2, p_i_1[5] & 0x3F, 0, 0);
  __sub_4043E0_ElementCount_0 = *((_DWORD *)Blockb + 3) + 0x20000;
  __sub_4043E0_Buffer = __op_new(__sub_4043E0_ElementCount_0);
  __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
  __sub_4043E0_n8 = 0;
  __sub_4043E0_n256 = 0;
  __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
  v179[0] = i_2 * i;
  __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
  Srca_7 = __op_new(i_2 * i);
  n4_4 = ::__sub_4043E0_n4_5;
  v21 = (p_i_1[1] - i_2) >> 1;
  v22 = *p_i_1 - i;
  v23 = v21 * p_i_1[2];
  v178[1] = (char *)v21;
  v24 = (char *)p_i_1 + ::__sub_4043E0_n4_5 * (v22 >> 1) + v23 + 16;
  Src = Blockb + 16;
  v178[0] = Blockb + 16;
  if ( v21 < i_2 + v21 )
  {
    Size = *((unsigned __int16 *)Blockb + 2);
    v179[1] = i_2;
    v26 = v178[1];
    p_i_2 = p_i_1;
    v27 = v178[0];
    do
    {
      sub_434980(v27,v24,Size);
      Size = *((unsigned __int16 *)Blockb + 2);
      v27 += Size;
      v24 += p_i_2[2];
      ++v26;
    }
    while ( (int)v26 < v179[1] + ((p_i_2[1] - v179[1]) >> 1) );
    p_i_1 = p_i_2;
    n4_4 = ::__sub_4043E0_n4_5;
  }
  n4_10 = nullptr;
  v188 = 0;
  v189 = 0;
  n4_15 = nullptr;
  if ( n4_4 > 0 )
  {
    p_i_2 = p_i_1;
    n4_13 = n4_10;
    n5_1 = nullptr;
    v182 = 0;
    v179[0] *= 8;
    while ( 1 )
    {
      v179[1] = (unsigned __int8)__sub_4043E0_byte_44339D[16 * v182];
      v180 = 16 * v179[1];
      if ( n4_13 )
      {
        n0x7FFFFFFF = 0x7FFFFFFF;
      }
      else
      {
        Blockb_1 = Blockb;
        Srca = (char *)Srca_7;
        v172 = v179[1];
        __sub_4043E0_byte_44339E[16 * v179[1]] = 0;
        sub_405840(Blockb_1, Srca, v172, v19, a3, a4);
        n0x7FFFFFFF_1 = 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer);
        n0x7FFFFFFF = __sub_4043E0_n256_2[0] - __sub_4043E0_n8 + n0x7FFFFFFF_1 + 32;
        v35 = __sub_4043E0_dword_443384 == 0;
        *(_DWORD *)__sub_4043E0_Buffer_1 = __sub_4043E0_n256;
        if ( !v35 )
          n0x7FFFFFFF = n0x7FFFFFFF_1;
        __sub_4043E0_n8 = 0;
        __sub_4043E0_n256 = 0;
        __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
        __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
        n5_6 = n5_1;
        __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
        if ( n0x7FFFFFFF == 0x7FFFFFFF )
          n0x7FFFFFFF = 0x7FFFFFFF;
        else
          n5_6 = nullptr;
        n5_1 = n5_6;
      }
      Blockb_2 = Blockb;
      Srca_1 = (char *)Srca_7;
      v32 = v179[1];
      __sub_4043E0_byte_44339E[v180] = 5;
      sub_405840(Blockb_2, Srca_1, v32, v19, a3, a4);
      n0x7FFFFFFF_8 = 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer);
      n0x7FFFFFFF_2 = __sub_4043E0_n256_2[0] - __sub_4043E0_n8 + n0x7FFFFFFF_8 + 32;
      v35 = __sub_4043E0_dword_443384 == 0;
      *(_DWORD *)__sub_4043E0_Buffer_1 = __sub_4043E0_n256;
      __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
      __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
      if ( !v35 )
        n0x7FFFFFFF_2 = n0x7FFFFFFF_8;
      __sub_4043E0_n8 = 0;
      __sub_4043E0_n256 = 0;
      __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
      n5 = (int)n5_1;
      if ( n0x7FFFFFFF_2 < n0x7FFFFFFF )
      {
        n0x7FFFFFFF = n0x7FFFFFFF_2;
        n5 = 5;
      }
      n5_1 = (char *)n5;
      if ( n0x7FFFFFFF_2 < n0x7FFFFFFF + (n0x7FFFFFFF >> 5) || n4_13 )
      {
        Blockb_3 = Blockb;
        Srca_2 = (char *)Srca_7;
        v166 = v179[1];
        __sub_4043E0_byte_44339E[v180] = 6;
        sub_405840(Blockb_3, Srca_2, v166, v19, a3, a4);
        n0x7FFFFFFF_9 = 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer);
        n0x7FFFFFFF_3 = __sub_4043E0_n256_2[0] - __sub_4043E0_n8 + n0x7FFFFFFF_9 + 32;
        v35 = __sub_4043E0_dword_443384 == 0;
        *(_DWORD *)__sub_4043E0_Buffer_1 = __sub_4043E0_n256;
        __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
        __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
        if ( !v35 )
          n0x7FFFFFFF_3 = n0x7FFFFFFF_9;
        __sub_4043E0_n8 = 0;
        __sub_4043E0_n256 = 0;
        n5_2 = (int)n5_1;
        __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
        if ( n0x7FFFFFFF_3 < n0x7FFFFFFF )
        {
          n0x7FFFFFFF = n0x7FFFFFFF_3;
          n5_2 = 6;
        }
        n5_1 = (char *)n5_2;
        if ( v182 )
        {
          if ( !n4_13 || (unsigned int)__sub_4043E0_n7_0 > 5 )
          {
LABEL_191:
            Blockb_4 = Blockb;
            Srca_3 = (char *)Srca_7;
            v149 = v179[1];
            __sub_4043E0_byte_44339E[v180] = 8;
            sub_405840(Blockb_4, Srca_3, v149, v19, a3, a4);
            n0x7FFFFFFF_10 = 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer);
            n0x7FFFFFFF_4 = __sub_4043E0_n256_2[0] - __sub_4043E0_n8 + n0x7FFFFFFF_10 + 32;
            v35 = __sub_4043E0_dword_443384 == 0;
            *(_DWORD *)__sub_4043E0_Buffer_1 = __sub_4043E0_n256;
            __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
            __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
            if ( !v35 )
              n0x7FFFFFFF_4 = n0x7FFFFFFF_10;
            __sub_4043E0_n8 = 0;
            __sub_4043E0_n256 = 0;
            n5_3 = (int)n5_1;
            __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
            if ( n0x7FFFFFFF_4 < n0x7FFFFFFF )
            {
              n0x7FFFFFFF = n0x7FFFFFFF_4;
              n5_3 = 8;
            }
            n5_1 = (char *)n5_3;
          }
          Blockb_5 = Blockb;
          Srca_4 = (char *)Srca_7;
          v155 = v179[1];
          __sub_4043E0_byte_44339E[v180] = 13;
          sub_405840(Blockb_5, Srca_4, v155, v19, a3, a4);
          n0x7FFFFFFF_11 = 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer);
          n0x7FFFFFFF_5 = (char *)(__sub_4043E0_n256_2[0] - __sub_4043E0_n8 + n0x7FFFFFFF_11 + 32);
          v35 = __sub_4043E0_dword_443384 == 0;
          *(_DWORD *)__sub_4043E0_Buffer_1 = __sub_4043E0_n256;
          __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
          __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
          if ( !v35 )
            n0x7FFFFFFF_5 = (char *)n0x7FFFFFFF_11;
          v178[0] = n0x7FFFFFFF_5;
          __sub_4043E0_n8 = 0;
          __sub_4043E0_n256 = 0;
          n5_4 = (int)n5_1;
          __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
          if ( (int)n0x7FFFFFFF_5 < n0x7FFFFFFF )
          {
            n0x7FFFFFFF = (int)n0x7FFFFFFF_5;
            n5_4 = 13;
          }
          n5_1 = (char *)n5_4;
          n2 = n5_4 & 3;
          if ( n2 == 2 || n0x7FFFFFFF + (n0x7FFFFFFF >> 5) > (int)v178[0] )
          {
            Srca_5 = (char *)Srca_7;
            v160 = v179[1];
            __sub_4043E0_byte_44339E[v180] = 14;
            sub_405840(Blockb, Srca_5, v160, v19, a3, a4);
            n0x7FFFFFFF_6 = __sub_4043E0_n256_2[0] - __sub_4043E0_n8 + 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer) + 32;
            if ( __sub_4043E0_dword_443384 )
              n0x7FFFFFFF_6 = 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer);
            v162 = n0x7FFFFFFF_6 < n0x7FFFFFFF;
            if ( n0x7FFFFFFF_6 < n0x7FFFFFFF )
              n0x7FFFFFFF = n0x7FFFFFFF_6;
            *(_DWORD *)__sub_4043E0_Buffer_1 = __sub_4043E0_n256;
            __sub_4043E0_n8 = 0;
            __sub_4043E0_n256 = 0;
            __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
            __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
            __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
            n5_5 = (int)n5_1;
            if ( v162 )
              n5_5 = 14;
            n5_1 = (char *)n5_5;
            if ( v162 )
              n2 = 2;
          }
          goto LABEL_43;
        }
        n2 = n5_2 & 3;
      }
      else
      {
        if ( v182 )
          goto LABEL_191;
        n2 = (unsigned __int8)n5_1 & 3;
      }
LABEL_43:
      if ( __sub_4043E0_dword_443384 || 3 * n0x7FFFFFFF >= v179[0] )
      {
        v184 = (unsigned __int8)n5_1 & 8;
      }
      else
      {
        v184 = (unsigned __int8)n5_1 & 8;
        if ( n2 != 2 )
        {
          Srca_6 = (char *)Srca_7;
          v178[1] = (char *)((unsigned __int8)n5_1 & 8 | 1);
          __sub_4043E0_byte_44339E[v180] = (char)v178[1];
          sub_405840(Blockb, Srca_6, v179[1], v19, a3, a4);
          n0x7FFFFFFF_7 = 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer);
          if ( !__sub_4043E0_dword_443384 )
            n0x7FFFFFFF_7 = __sub_4043E0_n256_2[0] - __sub_4043E0_n8 + 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer) + 32;
          *(_DWORD *)__sub_4043E0_Buffer_1 = __sub_4043E0_n256;
          __sub_4043E0_n8 = 0;
          __sub_4043E0_n256 = 0;
          __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
          __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
          __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
          if ( n0x7FFFFFFF_7 < n0x7FFFFFFF )
          {
            n0x7FFFFFFF = n0x7FFFFFFF_7;
            n5_1 = v178[1];
            n2 = (int)v178[1] & 3;
            v184 = (int)v178[1] & 8;
          }
        }
      }
      n4_15 += n0x7FFFFFFF;
      v40 = n2 == 2;
      if ( n2 != 1 )
        n2 = 0;
      v41 = v180;
      n4_13 = (char *)((uintptr_t)n4_13 + (v40));
      v188 += n2;
      v42 = v184;
      v181[v179[1]] = n0x7FFFFFFF;
      v43 = v182;
      v189 += v42 != 0;
      __sub_4043E0_byte_44339E[v41] = (char)n5_1;
      v182 = v43 + 1;
      if ( v43 + 1 >= ::__sub_4043E0_n4_5 )
      {
        n4_10 = n4_13;
        p_i_1 = p_i_2;
        break;
      }
    }
  }
  if ( (unsigned int)__sub_4043E0_n7_0 > 6 )
  {
    v101 = (char *)__op_new(*((_DWORD *)Blockb + 3));
    v102 = *((unsigned __int16 *)Blockb + 1);
    v178[1] = (char *)::__sub_4043E0_n4_5;
    v180 = (int)v101;
    v182 = ::__sub_4043E0_n4_5 * (v102 - 1);
    sub_434980(v101,(char *)Src,*((_DWORD *)Blockb + 3));
    LOWORD(v104) = *((_WORD *)Blockb + 1);
    if ( (_WORD)v104 )
    {
      v178[0] = v101;
      v105 = v178[1];
      p_i_2 = p_i_1;
      v106 = 0;
      Blockb_6 = Blockb;
      v108 = 0;
      do
      {
        v109 = *(unsigned __int16 *)Blockb_6;
        v179[1] = v108;
        v179[0] = v106;
        v110 = &Blockb_6[v108 + 16];
        v111 = (char *)v180;
        do
        {
          v112 = v105;
          do
          {
            *v110++ = *v111++;
            v112 = (char *)((uintptr_t)v112 - 1);
          }
          while ( v112 );
          v110 += v182;
          --v109;
        }
        while ( v109 );
        Blockb_6 = Blockb;
        v104 = *((unsigned __int16 *)Blockb + 1);
        v180 = (int)v111;
        v108 = (int)&v105[v179[1]];
        v106 = v179[0] + 1;
      }
      while ( v179[0] + 1 < v104 );
      v101 = v178[0];
      p_i_1 = p_i_2;
    }
    Blockb_7 = Blockb;
    v114 = *(_WORD *)Blockb;
    v115 = v104 * LOWORD(v178[1]);
    *(_WORD *)Blockb = v104;
    *((_WORD *)Blockb_7 + 1) = v114;
    Blockb_7[11] ^= 2u;
    *((_WORD *)Blockb_7 + 2) = v115;
    __op_delete(v101);
    n4_19 = 0;
    if ( ::__sub_4043E0_n4_5 > 0 )
    {
      p_i_2 = p_i_1;
      v118 = 0;
      while ( 1 )
      {
        v119 = (unsigned __int8)__sub_4043E0_byte_44339D[16 * v118];
        v178[0] = (char *)v119;
        sub_405840(Blockb, (char *)Srca_7, v119, v116, a3, a4);
        v120 = 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer);
        if ( !__sub_4043E0_dword_443384 )
          v120 = __sub_4043E0_n256_2[0] - __sub_4043E0_n8 + 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer) + 32;
        *(_DWORD *)__sub_4043E0_Buffer_1 = __sub_4043E0_n256;
        __sub_4043E0_n8 = 0;
        n4_19 += v120;
        __sub_4043E0_n256 = 0;
        __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
        __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
        __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
        if ( v120 - (v120 >> 8) > v181[(int)v178[0]] )
          break;
        if ( ++v118 >= ::__sub_4043E0_n4_5 )
        {
          p_i_1 = p_i_2;
          goto LABEL_172;
        }
      }
      p_i_1 = p_i_2;
      n4_19 += (int)(n4_15 + 1);
    }
LABEL_172:
    if ( n4_19 + (n4_19 >> 12) >= (int)n4_15 )
    {
      v178[0] = (char *)__op_new(*((_DWORD *)Blockb + 3));
      v133 = ::__sub_4043E0_n4_5 * (*((unsigned __int16 *)Blockb + 1) - 1);
      v178[1] = (char *)::__sub_4043E0_n4_5;
      v180 = (int)v178[0];
      sub_434980(v178[0],(char *)Src,*((_DWORD *)Blockb + 3));
      LOWORD(v135) = *((_WORD *)Blockb + 1);
      if ( (_WORD)v135 )
      {
        v181[0] = v133;
        v136 = v178[1];
        p_i_2 = p_i_1;
        v137 = 0;
        Blockb_8 = Blockb;
        v139 = 0;
        do
        {
          v140 = *(unsigned __int16 *)Blockb_8;
          v179[1] = v139;
          v179[0] = v137;
          v141 = &Blockb_8[v139 + 16];
          v142 = (char *)v180;
          do
          {
            v143 = v136;
            do
            {
              *v141++ = *v142++;
              v143 = (char *)((uintptr_t)v143 - 1);
            }
            while ( v143 );
            v141 += v181[0];
            --v140;
          }
          while ( v140 );
          Blockb_8 = Blockb;
          v135 = *((unsigned __int16 *)Blockb + 1);
          v180 = (int)v142;
          v139 = (int)&v136[v179[1]];
          v137 = v179[0] + 1;
        }
        while ( v179[0] + 1 < v135 );
        p_i_1 = p_i_2;
      }
      Blockb_9 = Blockb;
      v176 = v178[0];
      v145 = *(_WORD *)Blockb;
      v146 = v135 * LOWORD(v178[1]);
      *(_WORD *)Blockb = v135;
      *((_WORD *)Blockb_9 + 1) = v145;
      Blockb_9[11] ^= 2u;
      *((_WORD *)Blockb_9 + 2) = v146;
      __op_delete(v176);
    }
    else
    {
      n4_15 = (char *)n4_19;
      v178[0] = (char *)__op_new(*((_DWORD *)p_i_1 + 3));
      v121 = p_i_1[1];
      v178[1] = (char *)::__sub_4043E0_n4_5;
      v179[0] = (int)v178[0];
      v181[0] = ::__sub_4043E0_n4_5 * (v121 - 1);
      sub_434980(v178[0],(char *)p_i_1 + 16,*((_DWORD *)p_i_1 + 3));
      LOWORD(v123) = p_i_1[1];
      if ( (_WORD)v123 )
      {
        v124 = v178[1];
        v125 = 0;
        v126 = 0;
        do
        {
          i_6 = *p_i_1;
          v179[1] = v126;
          v180 = v125;
          v128 = (char *)p_i_1 + v126 + 16;
          p_i_2 = p_i_1;
          v129 = (_BYTE *)v179[0];
          do
          {
            v130 = v124;
            do
            {
              *v128++ = *v129++;
              v130 = (char *)((uintptr_t)v130 - 1);
            }
            while ( v130 );
            v128 += v181[0];
            --i_6;
          }
          while ( i_6 );
          v179[0] = (int)v129;
          p_i_1 = p_i_2;
          v123 = p_i_2[1];
          v126 = (int)&v124[v179[1]];
          v125 = v180 + 1;
        }
        while ( v180 + 1 < v123 );
      }
      v175 = v178[0];
      i_7 = *p_i_1;
      v132 = v123 * LOWORD(v178[1]);
      *p_i_1 = v123;
      p_i_1[1] = i_7;
      *((_BYTE *)p_i_1 + 11) ^= 2u;
      p_i_1[2] = v132;
      __op_delete(v175);
    }
  }
  __op_delete(Srca_7);
  if ( ::__sub_4043E0_n4_5 > 2 && __sub_4043E0_dword_443384 )
  {
    if ( v188 )
    {
      n16 = 16;
      do
      {
        v179[n16 + 1] = __sub_4043E0_n256_0[n16];
        v179[n16] = *(int *)((char *)&::__sub_4043E0_n4_5 + n16 * 4);
        v178[n16 + 1] = (char *)__sub_4043E0_n512[n16];
        v74 = (char *)__sub_4043E0_n256_2[n16];
        v178[n16] = v74;
        n16 -= 4;
      }
      while ( n16 * 4 );
      if ( ::__sub_4043E0_n4_5 > 0 )
      {
        __sub_4043E0_n4_5 = 0;
        do
        {
          v76 = 16 * __sub_4043E0_n4_5;
          v77 = __sub_4043E0_byte_44339E[16 * __sub_4043E0_n4_5++] & 8 | 5;
          __sub_4043E0_byte_44339E[v76] = v77;
        }
        while ( __sub_4043E0_n4_5 < ::__sub_4043E0_n4_5 );
      }
      sub_407B30((unsigned __int16 *)Blockb, (int)v74, v44, a3, a4);
      n4_20 = 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer);
      if ( !__sub_4043E0_dword_443384 )
        n4_20 = __sub_4043E0_n256_2[0] - __sub_4043E0_n8 + 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer) + 32;
      v162 = n4_20 <= (int)n4_15;
      *(_DWORD *)__sub_4043E0_Buffer_1 = __sub_4043E0_n256;
      __sub_4043E0_n8 = 0;
      __sub_4043E0_n256 = 0;
      __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
      __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
      __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
      if ( v162 )
      {
        n4_15 = (char *)n4_20;
        n4_6 = ::__sub_4043E0_n4_5;
        v45 = 0;
      }
      else
      {
        n64 = 64;
        do
        {
          *(_QWORD *)(n64 + BMF_BLOB(0x00443394)) = *(_QWORD *)&v179[n64 / 4];
          a3 = (__m128)*(unsigned __int64 *)&v178[n64 / 4];
          *(_QWORD *)(n64 + BMF_BLOB(0x0044338C)) = a3.m128_u64[0];
          *(_QWORD *)(n64 + BMF_BLOB(0x00443384)) = v177[n64 / 8 + 1];
          a4 = (__m128)(unsigned __int64)v177[n64 / 8];
          *(_QWORD *)(n64 + BMF_BLOB(0x0044337C)) = a4.m128_u64[0];
          n64 -= 32;
        }
        while ( n64 );
        n4_6 = ::__sub_4043E0_n4_5;
        v45 = 1;
      }
      if ( n4_6 <= 2 || !__sub_4043E0_dword_443384 )
        goto LABEL_63;
    }
    else
    {
      v45 = 1;
    }
    if ( &n4_10[v45 == 0] )
    {
      n16_1 = 16;
      do
      {
        v179[n16_1 + 1] = __sub_4043E0_n256_0[n16_1];
        v179[n16_1] = *(int *)((char *)&::__sub_4043E0_n4_5 + n16_1 * 4);
        v178[n16_1 + 1] = (char *)__sub_4043E0_n512[n16_1];
        v178[n16_1] = (char *)__sub_4043E0_n256_2[n16_1];
        n16_1 -= 4;
      }
      while ( n16_1 * 4 );
      n4_7 = ::__sub_4043E0_n4_5;
      if ( ::__sub_4043E0_n4_5 > 0 )
      {
        n4_8 = 0;
        do
        {
          v61 = 16 * n4_8;
          v62 = __sub_4043E0_byte_44339E[16 * n4_8++] & 8 | 6;
          __sub_4043E0_byte_44339E[v61] = v62;
          n4_7 = ::__sub_4043E0_n4_5;
        }
        while ( n4_8 < ::__sub_4043E0_n4_5 );
      }
      if ( (char *)n4_7 == n4_10 && n4_7 - 1 == v189 )
      {
        v45 = 0;
      }
      else
      {
        sub_407B30((unsigned __int16 *)Blockb, v45, v44, a3, a4);
        n4_14 = (char *)(8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer));
        if ( !__sub_4043E0_dword_443384 )
          n4_14 = (char *)(__sub_4043E0_n256_2[0] - __sub_4043E0_n8 + 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer) + 32);
        v162 = (int)n4_14 <= (int)n4_15;
        v178[0] = n4_14;
        *(_DWORD *)__sub_4043E0_Buffer_1 = __sub_4043E0_n256;
        __sub_4043E0_n8 = 0;
        __sub_4043E0_n256 = 0;
        __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
        __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
        __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
        if ( v162 )
        {
          n4_15 = n4_14;
          n4_10 = n4_14;
          if ( ::__sub_4043E0_n4_5 - 1 == v189 )
          {
            v45 = 0;
          }
          else
          {
            n16_2 = 16;
            do
            {
              v179[n16_2 + 1] = __sub_4043E0_n256_0[n16_2];
              v179[n16_2] = *(int *)((char *)&::__sub_4043E0_n4_5 + n16_2 * 4);
              v178[n16_2 + 1] = (char *)__sub_4043E0_n512[n16_2];
              v67 = (char *)__sub_4043E0_n256_2[n16_2];
              v178[n16_2] = v67;
              n16_2 -= 4;
            }
            while ( n16_2 * 4 );
            if ( ::__sub_4043E0_n4_5 > 0 )
            {
              n4_9 = 0;
              do
              {
                v69 = 16 * n4_9;
                v70 = __sub_4043E0_byte_44339C[16 * n4_9++];
                __sub_4043E0_byte_44339E[v69] |= 8 * (v70 != 0);
              }
              while ( n4_9 < ::__sub_4043E0_n4_5 );
            }
            sub_407B30((unsigned __int16 *)Blockb, (int)v67, v63, a3, a4);
            v71 = 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer);
            if ( !__sub_4043E0_dword_443384 )
              v71 = __sub_4043E0_n256_2[0] - __sub_4043E0_n8 + 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer) + 32;
            v162 = v71 <= (int)v178[0];
            *(_DWORD *)__sub_4043E0_Buffer_1 = __sub_4043E0_n256;
            __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
            __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
            __sub_4043E0_n8 = 0;
            __sub_4043E0_n256 = 0;
            __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
            if ( v162 )
            {
              v45 = 0;
            }
            else
            {
              n64_1 = 64;
              do
              {
                *(_QWORD *)(n64_1 + BMF_BLOB(0x00443394)) = *(_QWORD *)&v179[n64_1 / 4];
                a3 = (__m128)*(unsigned __int64 *)&v178[n64_1 / 4];
                *(_QWORD *)(n64_1 + BMF_BLOB(0x0044338C)) = a3.m128_u64[0];
                *(_QWORD *)(n64_1 + BMF_BLOB(0x00443384)) = v177[n64_1 / 8 + 1];
                a4 = (__m128)(unsigned __int64)v177[n64_1 / 8];
                *(_QWORD *)(n64_1 + BMF_BLOB(0x0044337C)) = a4.m128_u64[0];
                n64_1 -= 32;
              }
              while ( n64_1 );
              v45 = 0;
            }
          }
        }
        else
        {
          n64_2 = 64;
          do
          {
            *(_QWORD *)(n64_2 + BMF_BLOB(0x00443394)) = *(_QWORD *)&v179[n64_2 / 4];
            a3 = (__m128)*(unsigned __int64 *)&v178[n64_2 / 4];
            *(_QWORD *)(n64_2 + BMF_BLOB(0x0044338C)) = a3.m128_u64[0];
            *(_QWORD *)(n64_2 + BMF_BLOB(0x00443384)) = v177[n64_2 / 8 + 1];
            a4 = (__m128)(unsigned __int64)v177[n64_2 / 8];
            *(_QWORD *)(n64_2 + BMF_BLOB(0x0044337C)) = a4.m128_u64[0];
            n64_2 -= 32;
          }
          while ( n64_2 );
        }
      }
    }
  }
  else
  {
    v45 = 1;
  }
LABEL_63:
  if ( !n4_10 && ::__sub_4043E0_n4_5 > 1 )
  {
    v178[0] = (char *)__op_new(*((_DWORD *)Blockb + 3));
    sub_434980(v178[0],(char *)Src,*((_DWORD *)Blockb + 3));
    n16_3 = 16;
    do
    {
      v179[n16_3 + 1] = __sub_4043E0_n256_0[n16_3];
      v179[n16_3] = *(int *)((char *)&::__sub_4043E0_n4_5 + n16_3 * 4);
      v178[n16_3 + 1] = (char *)__sub_4043E0_n512[n16_3];
      v178[n16_3] = (char *)__sub_4043E0_n256_2[n16_3];
      n16_3 -= 4;
    }
    while ( n16_3 * 4 );
    if ( ::__sub_4043E0_n4_5 > 0 )
    {
      n4_11 = 0;
      do
      {
        v85 = 16 * n4_11;
        v86 = __sub_4043E0_byte_44339E[16 * n4_11++] & 0xFB;
        __sub_4043E0_byte_44339E[v85] = v86;
      }
      while ( n4_11 < ::__sub_4043E0_n4_5 );
    }
    sub_407B30((unsigned __int16 *)Blockb, v45, v82, a3, a4);
    n4_17 = (char *)(8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer));
    if ( !__sub_4043E0_dword_443384 )
      n4_17 = (char *)(__sub_4043E0_n256_2[0] - __sub_4043E0_n8 + 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer) + 32);
    v178[1] = n4_17;
    *(_DWORD *)__sub_4043E0_Buffer_1 = __sub_4043E0_n256;
    __sub_4043E0_n8 = 0;
    __sub_4043E0_n256 = 0;
    __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
    __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
    n4_16 = (int)n4_15;
    __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
    if ( (int)n4_17 > (int)n4_15 )
    {
      n64_3 = 64;
      do
      {
        *(_QWORD *)(n64_3 + BMF_BLOB(0x00443394)) = *(_QWORD *)&v179[n64_3 / 4];
        a3 = (__m128)*(unsigned __int64 *)&v178[n64_3 / 4];
        *(_QWORD *)(n64_3 + BMF_BLOB(0x0044338C)) = a3.m128_u64[0];
        *(_QWORD *)(n64_3 + BMF_BLOB(0x00443384)) = v177[n64_3 / 8 + 1];
        a4 = (__m128)(unsigned __int64)v177[n64_3 / 8];
        *(_QWORD *)(n64_3 + BMF_BLOB(0x0044337C)) = a4.m128_u64[0];
        n64_3 -= 32;
      }
      while ( n64_3 );
    }
    else
    {
      n4_15 = n4_17;
      v45 = 0;
    }
    if ( ((n4_16 >> 3) + n4_16 > (int)v178[1] || __sub_4043E0_dword_443384) && v189 + v188 )
    {
      n16_4 = 16;
      do
      {
        v179[n16_4 + 1] = __sub_4043E0_n256_0[n16_4];
        v179[n16_4] = *(int *)((char *)&::__sub_4043E0_n4_5 + n16_4 * 4);
        v178[n16_4 + 1] = (char *)__sub_4043E0_n512[n16_4];
        v178[n16_4] = (char *)__sub_4043E0_n256_2[n16_4];
        n16_4 -= 4;
      }
      while ( n16_4 * 4 );
      if ( ::__sub_4043E0_n4_5 > 0 )
      {
        n4_12 = 0;
        do
          __sub_4043E0_byte_44339E[16 * n4_12++] = 0;
        while ( n4_12 < ::__sub_4043E0_n4_5 );
      }
      sub_434980((char *)Src,v178[0],*((_DWORD *)Blockb + 3));
      sub_407B30((unsigned __int16 *)Blockb, v45, v93, a3, a4);
      n4_18 = 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer);
      if ( !__sub_4043E0_dword_443384 )
        n4_18 = __sub_4043E0_n256_2[0] - __sub_4043E0_n8 + 8 * (__sub_4043E0_Buffer_0 - (_DWORD)__sub_4043E0_Buffer) + 32;
      v162 = n4_18 <= (int)n4_15;
      *(_DWORD *)__sub_4043E0_Buffer_1 = __sub_4043E0_n256;
      __sub_4043E0_n8 = 0;
      __sub_4043E0_n256 = 0;
      __sub_4043E0_Buffer_0 = (int)__sub_4043E0_Buffer;
      __sub_4043E0_Buffer_1 = (int)__sub_4043E0_Buffer;
      __sub_4043E0_buf = (char *)__sub_4043E0_Buffer + __sub_4043E0_ElementCount_0 - 4096;
      if ( v162 )
      {
        v45 = 0;
      }
      else
      {
        n64_4 = 64;
        do
        {
          *(_QWORD *)(n64_4 + BMF_BLOB(0x00443394)) = *(_QWORD *)&v179[n64_4 / 4];
          *(_QWORD *)(n64_4 + BMF_BLOB(0x0044338C)) = *(_QWORD *)&v178[n64_4 / 4];
          *(_QWORD *)(n64_4 + BMF_BLOB(0x00443384)) = v177[n64_4 / 8 + 1];
          *(_QWORD *)(n64_4 + BMF_BLOB(0x0044337C)) = v177[n64_4 / 8];
          n64_4 -= 32;
        }
        while ( n64_4 );
      }
    }
    __op_delete(v178[0]);
  }
  __op_delete(__sub_4043E0_Buffer);
  __op_delete(Blockb);
  if ( __sub_4043E0_n2_4 == 1 )
  {
    if ( ::__sub_4043E0_n4_5 <= 0 )
    {
      v96 = 0;
    }
    else
    {
      v96 = 0;
      if ( ::__sub_4043E0_n4_5 / 2 )
      {
        v178[0] = (char *)v45;
        p_i_2 = p_i_1;
        v97 = 0;
        do
        {
          v98 = (unsigned __int8)__sub_4043E0_byte_44339E[16 * (unsigned __int8)__sub_4043E0_byte_44339D[32 * v97]];
          v99 = 16 * (unsigned __int8)__sub_4043E0_byte_4433AD[32 * v97++];
          v96 = (unsigned __int8)__sub_4043E0_byte_44339E[v99] | (16 * (v98 | (16 * v96)));
        }
        while ( v97 < ::__sub_4043E0_n4_5 / 2 );
        v45 = (int)v178[0];
        p_i_1 = p_i_2;
        v100 = 2 * v97 + 1;
      }
      else
      {
        v100 = 1;
      }
      if ( ::__sub_4043E0_n4_5 > (unsigned int)(v100 - 1) )
        v96 = (unsigned __int8)__sub_4043E0_byte_44339E[16 * BYTE1(__sub_4043E0_n256_2[4 * v100])] | (16 * v96);
    }
    __sub_4043E0_dword_4410A4 = (::__sub_4043E0_n4_5 << 16)
                 | (__sub_4043E0_dword_443384 << 19)
                 | (v45 << 20)
                 | ((unsigned __int8)(*((_BYTE *)p_i_1 + 11) & 2) >> 1 << 21)
                 | v96;
  }
  return v45;
}

#ifndef BMF_STANDALONE
// __usercall thunk for sub_4043E0 @ 0x004043E0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_4043E0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $48, %esp\n"
    "mov %eax, 0(%esp)\n"
    "fnstsw %ax\n"
    "mov %eax, 4(%esp)\n"
    "movups %xmm1, 16(%esp)\n"
    "movups %xmm3, 32(%esp)\n"
    "lea 32(%esp), %eax\n"
    "push %eax\n"
    "lea 20(%esp), %eax\n"
    "push %eax\n"
    "push 12(%esp)\n"
    "push 12(%esp)\n"
    "call __sub_4043E0\n"
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
#undef sub_405840
#undef sub_405CF0
#undef sub_407B30
#undef sub_42B830
#undef sub_434980
