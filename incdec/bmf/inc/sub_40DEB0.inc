// sub_40DEB0 @ 0x0040DEB0 — __cdecl
// Extracted from BMF.cpp:11830-12284 by extract.py per incdec.md.

typedef int t_sub_40DEB0_Buffer_0;
static t_sub_40DEB0_Buffer_0& __sub_40DEB0_Buffer_0 = *(t_sub_40DEB0_Buffer_0*)0x00443378;
typedef unsigned char t_sub_40DEB0_byte_43945C[0x10000];
static t_sub_40DEB0_byte_43945C& __sub_40DEB0_byte_43945C = *(t_sub_40DEB0_byte_43945C*)0x0043945C;
typedef unsigned char t_sub_40DEB0_byte_439470[0x10000];
static t_sub_40DEB0_byte_439470& __sub_40DEB0_byte_439470 = *(t_sub_40DEB0_byte_439470*)0x00439470;
typedef int t_sub_40DEB0_dword_438B00[0x10000];
static t_sub_40DEB0_dword_438B00& __sub_40DEB0_dword_438B00 = *(t_sub_40DEB0_dword_438B00*)0x00438B00;
typedef int t_sub_40DEB0_dword_439360[32];
static t_sub_40DEB0_dword_439360& __sub_40DEB0_dword_439360 = *(t_sub_40DEB0_dword_439360*)0x00439360;
typedef int t_sub_40DEB0_dword_442EE0[0x10000];
static t_sub_40DEB0_dword_442EE0& __sub_40DEB0_dword_442EE0 = *(t_sub_40DEB0_dword_442EE0*)0x00442EE0;
typedef int t_sub_40DEB0_dword_443300[0x10000];
static t_sub_40DEB0_dword_443300& __sub_40DEB0_dword_443300 = *(t_sub_40DEB0_dword_443300*)0x00443300;
typedef int t_sub_40DEB0_dword_443348;
static t_sub_40DEB0_dword_443348& __sub_40DEB0_dword_443348 = *(t_sub_40DEB0_dword_443348*)0x00443348;
typedef int t_sub_40DEB0_dword_44342C;
static t_sub_40DEB0_dword_44342C& __sub_40DEB0_dword_44342C = *(t_sub_40DEB0_dword_44342C*)0x0044342C;
typedef int t_sub_40DEB0_dword_443434;
static t_sub_40DEB0_dword_443434& __sub_40DEB0_dword_443434 = *(t_sub_40DEB0_dword_443434*)0x00443434;
typedef int t_sub_40DEB0_dword_443438;
static t_sub_40DEB0_dword_443438& __sub_40DEB0_dword_443438 = *(t_sub_40DEB0_dword_443438*)0x00443438;
typedef int t_sub_40DEB0_n2;
static t_sub_40DEB0_n2& __sub_40DEB0_n2 = *(t_sub_40DEB0_n2*)0x00443360;
typedef int t_sub_40DEB0_n256;
static t_sub_40DEB0_n256& __sub_40DEB0_n256 = *(t_sub_40DEB0_n256*)0x0044336C;
typedef int t_sub_40DEB0_n8;
static t_sub_40DEB0_n8& __sub_40DEB0_n8 = *(t_sub_40DEB0_n8*)0x00443368;
typedef void * t_sub_40DEB0_off_4410C0[0x10000];
static t_sub_40DEB0_off_4410C0& __sub_40DEB0_off_4410C0 = *(t_sub_40DEB0_off_4410C0*)0x004410C0;
typedef __int128 t_sub_40DEB0_xmmword_442EA0;
static t_sub_40DEB0_xmmword_442EA0& __sub_40DEB0_xmmword_442EA0 = *(t_sub_40DEB0_xmmword_442EA0*)0x00442EA0;
typedef __int128 t_sub_40DEB0_xmmword_442EB0;
static t_sub_40DEB0_xmmword_442EB0& __sub_40DEB0_xmmword_442EB0 = *(t_sub_40DEB0_xmmword_442EB0*)0x00442EB0;
typedef __int128 t_sub_40DEB0_xmmword_442EC0;
static t_sub_40DEB0_xmmword_442EC0& __sub_40DEB0_xmmword_442EC0 = *(t_sub_40DEB0_xmmword_442EC0*)0x00442EC0;
typedef __int128 t_sub_40DEB0_xmmword_442ED0;
static t_sub_40DEB0_xmmword_442ED0& __sub_40DEB0_xmmword_442ED0 = *(t_sub_40DEB0_xmmword_442ED0*)0x00442ED0;

#define sub_40E4D0 __sub_40E4D0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#define FILE FILE1

PROBE_DECL(__sub_40DEB0)
BMF_REALIGN int *__sub_40DEB0()
{
  alignas(16) unsigned char __hexrays_frame[112];   // original frame, ebp-0x60..ebp+0x0
  char * &v61 = *(char * *)(__hexrays_frame + 0);
  int * &v62 = *(int * *)(__hexrays_frame + 4);
  int * &v63 = *(int * *)(__hexrays_frame + 4);
  int &v64 = *(int *)(__hexrays_frame + 8);
  int &v65 = *(int *)(__hexrays_frame + 8);
  _DWORD * &v66 = *(_DWORD * *)(__hexrays_frame + 8);
  int &v67 = *(int *)(__hexrays_frame + 12);
  int &v68 = *(int *)(__hexrays_frame + 12);
  int &v69 = *(int *)(__hexrays_frame + 12);
  int &v70 = *(int *)(__hexrays_frame + 12);
  unsigned int &v71 = *(unsigned int *)(__hexrays_frame + 16);
  unsigned int &v72 = *(unsigned int *)(__hexrays_frame + 16);
  unsigned int &v73 = *(unsigned int *)(__hexrays_frame + 16);
  int &v74 = *(int *)(__hexrays_frame + 20);
  int &n11_1 = *(int *)(__hexrays_frame + 24);
  unsigned int &v76 = *(unsigned int *)(__hexrays_frame + 28);
  unsigned int &k_3 = *(unsigned int *)(__hexrays_frame + 32);
  _DWORD * &v78 = *(_DWORD * *)(__hexrays_frame + 36);
  int &v79 = *(int *)(__hexrays_frame + 40);
  int &n8_2 = *(int *)(__hexrays_frame + 44);
  int &v81 = *(int *)(__hexrays_frame + 48);
  char * &v82 = *(char * *)(__hexrays_frame + 52);
  int &v83 = *(int *)(__hexrays_frame + 56);
  int &n256_1 = *(int *)(__hexrays_frame + 60);
  int &v85 = *(int *)(__hexrays_frame + 64);
  char &v86 = *(char *)(__hexrays_frame + 68);
  int &v87 = *(int *)(__hexrays_frame + 72);
  int &v88 = *(int *)(__hexrays_frame + 72);
  PROBE_HIT(__sub_40DEB0);
  int *v0; // esi
  int __sub_40DEB0_n8; // edi
  bool v2; // sf
  char v3; // dl
  int v4; // ebx
  __int128 v5; // xmm0
  int n8_1; // edi
  unsigned int __sub_40DEB0_n256; // edx
  unsigned int i; // eax
  int v9; // ebx
  int v10; // eax
  int n4; // edx
  int *v12; // edx
  int v13; // edi
  int *v14; // eax
  int v15; // edi
  int v16; // ecx
  int v17; // ecx
  int n11; // eax
  unsigned int v19; // edi
  int v20; // eax
  _DWORD *v21; // edx
  int v22; // esi
  char *v23; // eax
  int v24; // ecx
  int v25; // edi
  int v26; // ebx
  int v27; // ecx
  int v28; // ecx
  int v29; // esi
  int *v30; // eax
  int *v31; // ecx
  int k_1; // esi
  int k; // ebx
  int v34; // esi
  int v35; // edi
  int v36; // eax
  int v38; // eax
  _DWORD *v39; // ebx
  int v40; // edx
  int n8_3; // esi
  unsigned int j; // eax
  int v43; // edi
  int k_2; // edi
  int v45; // esi
  int v46; // ebx
  int v47; // edi
  int k_4; // eax
  int v49; // ecx
  int v50; // edx
  int v51; // ebx
  int v52; // esi
  int v53; // ebx
  int v54; // ecx
  int v55; // edx
  unsigned int v56; // ebx
  unsigned int v57; // edx
  int n256_2; // edx
  unsigned int v59; // esi
  unsigned int v60; // eax

  v0 = (int *)__op_new(0x8ED0u);
  if ( v0 )
  {
    __sub_40DEB0_n8 = ::__sub_40DEB0_n8;
    v2 = ::__sub_40DEB0_n8 - 18 < 0;
    v3 = ::__sub_40DEB0_n8 - 18;
    ::__sub_40DEB0_n8 -= 18;
    if ( v2 )
    {
      v60 = *(_DWORD *)__sub_40DEB0_Buffer_0;
      __sub_40DEB0_Buffer_0 += 4;
      v4 = ::__sub_40DEB0_n256 | (v60 << (__sub_40DEB0_n8 & 31)) & 0x3FFFF;
      ::__sub_40DEB0_n256 = v60 >> (-v3 & 31);
      ::__sub_40DEB0_n8 = __sub_40DEB0_n8 + 14;
    }
    else
    {
      v4 = ::__sub_40DEB0_n256 & 0x3FFFF;
      ::__sub_40DEB0_n256 = (unsigned int)::__sub_40DEB0_n256 >> 18;
    }
    if ( v4 )
    {
      n8_1 = ::__sub_40DEB0_n8;
      __sub_40DEB0_n256 = ::__sub_40DEB0_n256;
      v67 = v4;
      v61 = (char *)(v0 + 2);
      v62 = v0;
      v5 = -1;
      __sub_40DEB0_xmmword_442EA0 = -1;
      __sub_40DEB0_xmmword_442EB0 = -1;
      __sub_40DEB0_xmmword_442EC0 = -1;
      __sub_40DEB0_xmmword_442ED0 = -1;
      for ( i = 0; i < 0x15; ++i )
      {
        n8_1 -= 4;
        if ( n8_1 < 0 )
        {
          ::__sub_40DEB0_n8 = n8_1;
          v59 = *(_DWORD *)__sub_40DEB0_Buffer_0;
          __sub_40DEB0_Buffer_0 += 4;
          v9 = __sub_40DEB0_n256 | (v59 << ((n8_1 + 4) & 31)) & 0xF;
          __sub_40DEB0_n256 = v59 >> (-(char)n8_1 & 31);
          n8_1 += 32;
        }
        else
        {
          v9 = __sub_40DEB0_n256 & 0xF;
          __sub_40DEB0_n256 >>= 4;
        }
        ::__sub_40DEB0_n256 = __sub_40DEB0_n256;
        __sub_40DEB0_dword_442EE0[i] = *((_DWORD *)&__sub_40DEB0_xmmword_442EA0 + v9);
        *((_DWORD *)&__sub_40DEB0_xmmword_442EA0 + v9) = i;
      }
      v10 = 1;
      v4 = v67;
      v0 = v62;
      ::__sub_40DEB0_n8 = n8_1;
      __sub_40DEB0_dword_443348 = (int)v62;
      if ( SDWORD1(__sub_40DEB0_xmmword_442EA0) < 0 )
      {
        do
        {
          ++v10;
          n4 = 4 * v10;
        }
        while ( *((int *)&__sub_40DEB0_xmmword_442EA0 + v10) < 0 );
      }
      else
      {
        n4 = 4;
      }
      v12 = (int *)((char *)&__sub_40DEB0_xmmword_442EA0 + n4);
      v62[1] = v10;
      *v62 = (v61 - (char *)v62) >> 3;
      v13 = 1 << (v10 & 31);
      __sub_40DEB0_dword_443438 = (int)&v62[2 * (1 << (v10 & 31)) + 2];
      v14 = &v62[2 * (1 << (v10 & 31))];
      v15 = v13 - 1;
      if ( v15 >= 0 )
      {
        __sub_40DEB0_dword_44342C = (int)v12;
        do
        {
          v16 = *v12;
          v14[1] = 0;
          *v14 = v16;
          v17 = __sub_40DEB0_dword_442EE0[v16];
          *v12 = v17;
          if ( v17 < 0 )
          {
            v14 -= 2;
            if ( --v15 >= 0 )
            {
              do
              {
                __sub_40DEB0_dword_443434 = (int)v14;
                sub_40E4D0();
                v14 = (int *)(__sub_40DEB0_dword_443434 - 8);
                --v15;
              }
              while ( v15 >= 0 );
              v12 = (int *)__sub_40DEB0_dword_44342C;
              v5 = -1;
            }
          }
          v14 -= 2;
          --v15;
        }
        while ( v15 >= 0 );
      }
    }
    else
    {
      __sub_40DEB0_dword_443438 = (int)(v0 + 2);
      v5 = -1;
    }
    v63 = v0;
    if ( __sub_40DEB0_n2 == 2 )
      v4 >>= 11;
    n11 = 11;
    if ( __sub_40DEB0_n2 != 2 )
      n11 = 0;
    v19 = 0;
    v86 = 0;
    n11_1 = n11;
    v76 = 18 - n11;
    do
    {
      v20 = __sub_40DEB0_dword_438B00[v19 + n11_1];
      __sub_40DEB0_xmmword_442EA0 = v5;
      __sub_40DEB0_xmmword_442EB0 = v5;
      __sub_40DEB0_xmmword_442EC0 = v5;
      __sub_40DEB0_xmmword_442ED0 = v5;
      if ( (v4 & 1) != 0 )
      {
        v21 = (_DWORD *)__sub_40DEB0_dword_443438;
        if ( v20 > 0 )
        {
          n8_2 = ::__sub_40DEB0_n8;
          n256_1 = ::__sub_40DEB0_n256;
          v85 = __sub_40DEB0_dword_443348;
          v83 = __sub_40DEB0_dword_438B00[v19 + n11_1];
          v82 = (char *)(&__sub_40DEB0_off_4410C0[v19])[n11_1];
          v81 = *(_DWORD *)(__sub_40DEB0_dword_443348 + 4);
          v38 = 0;
          v65 = __sub_40DEB0_dword_443438;
          v73 = v19;
          v70 = v4;
          do
          {
            v39 = (_DWORD *)v85;
            v40 = v81;
            n8_3 = n8_2;
            v79 = v38;
            for ( j = n256_1; ; ::__sub_40DEB0_n256 = j )
            {
              n8_3 -= v40;
              if ( n8_3 < 0 )
              {
                v78 = v39;
                ::__sub_40DEB0_n8 = n8_3;
                v56 = *(_DWORD *)__sub_40DEB0_Buffer_0;
                __sub_40DEB0_Buffer_0 += 4;
                v43 = j | __sub_40DEB0_dword_439360[v40] & (v56 << ((v40 + n8_3) & 31));
                j = v56 >> (-(char)n8_3 & 31);
                n8_3 += 32;
                v39 = v78;
              }
              else
              {
                v43 = j & __sub_40DEB0_dword_439360[v40];
                j >>= (v40 & 31);
              }
              v39 += 2 * *v39 + 2 * v43;
              v40 = v39[1];
              if ( !v40 )
                break;
            }
            v49 = *v39;
            n256_1 = j;
            n8_2 = n8_3;
            if ( (int)*v39 < 16 )
            {
              ::__sub_40DEB0_n256 = j;
              v86 = v49;
              v50 = 1;
            }
            else
            {
              v50 = *(_DWORD *)&__sub_40DEB0_byte_43945C[4 * v49];
              v51 = *(_DWORD *)&__sub_40DEB0_byte_439470[4 * v49];
              if ( v51 )
              {
                n8_2 = n8_3 - v51;
                if ( n8_3 - v51 < 0 )
                {
                  v88 = *(_DWORD *)&__sub_40DEB0_byte_43945C[4 * v49];
                  ::__sub_40DEB0_n256 = j;
                  ::__sub_40DEB0_n8 = n8_3 - v51;
                  v57 = *(_DWORD *)__sub_40DEB0_Buffer_0;
                  __sub_40DEB0_Buffer_0 += 4;
                  v52 = j | __sub_40DEB0_dword_439360[v51] & (v57 << (n8_3 & 31));
                  n256_2 = v57 >> (-(char)n8_2 & 31);
                  n8_2 += 32;
                  n256_1 = n256_2;
                  ::__sub_40DEB0_n256 = n256_2;
                  v50 = v88;
                }
                else
                {
                  v52 = j & __sub_40DEB0_dword_439360[v51];
                  n256_1 = j >> (v51 & 31);
                  ::__sub_40DEB0_n256 = j >> (v51 & 31);
                }
                v50 += v52;
              }
              else
              {
                ::__sub_40DEB0_n256 = j;
              }
            }
            v87 = v50;
            v53 = 0;
            v54 = v79;
            do
            {
              v55 = (v82[v79 + v53] - v86) & 0xF;
              __sub_40DEB0_dword_442EE0[v79 + v53++] = *((_DWORD *)&__sub_40DEB0_xmmword_442EA0 + v55);
              *((_DWORD *)&__sub_40DEB0_xmmword_442EA0 + v55) = v54++;
            }
            while ( v53 < v87 );
            v38 = v53 + v79;
          }
          while ( v53 + v79 < v83 );
          v21 = (_DWORD *)v65;
          v19 = v73;
          v4 = v70;
          ::__sub_40DEB0_n8 = n8_2;
        }
      }
      else
      {
        v21 = (_DWORD *)__sub_40DEB0_dword_443438;
        if ( v20 > 0 )
        {
          v22 = __sub_40DEB0_dword_438B00[v19 + n11_1];
          v23 = (char *)(&__sub_40DEB0_off_4410C0[v19])[n11_1];
          v64 = __sub_40DEB0_dword_443438;
          v24 = 0;
          v71 = v19;
          v25 = -1;
          v68 = v4;
          do
          {
            ++v25;
            v26 = (unsigned __int8)v23[v24++];
            *((_DWORD *)&__sub_40DEB0_xmmword_442ED0 + v24 + 3) = *((_DWORD *)&__sub_40DEB0_xmmword_442EA0 + v26);
            *((_DWORD *)&__sub_40DEB0_xmmword_442EA0 + v26) = v25;
          }
          while ( v24 < v22 );
          v21 = (_DWORD *)v64;
          v19 = v71;
          v4 = v68;
        }
      }
      v2 = SDWORD1(__sub_40DEB0_xmmword_442EA0) < 0;
      __sub_40DEB0_dword_443300[v19 + n11_1] = (int)v21;
      if ( v2 )
      {
        v28 = 0;
        do
          ++v28;
        while ( *((int *)&__sub_40DEB0_xmmword_442EA0 + v28 + 1) < 0 );
        v27 = v28 + 1;
      }
      else
      {
        v27 = 1;
      }
      v21[1] = v27;
      *v21 = 1;
      v29 = 1 << (v27 & 31);
      v74 = 4 * v27;
      v30 = (int *)(4 * v27 + 4468384);
      __sub_40DEB0_dword_443438 = (int)&v21[2 * (1 << (v27 & 31)) + 2];
      v31 = &v21[2 * (1 << (v27 & 31))];
      k_1 = v29 - 1;
      if ( k_1 >= 0 )
      {
        __sub_40DEB0_dword_44342C = (int)v30;
        v72 = v19;
        v69 = v4;
        for ( k = k_1; k >= 0; --k )
        {
          v34 = *v30;
          v35 = __sub_40DEB0_dword_442EE0[*v30];
          v31[1] = 0;
          *v31 = v34;
          *v30 = v35;
          if ( v35 < 0 )
          {
            v31 -= 2;
            k_2 = k;
            v45 = --k;
            if ( k >= 0 )
            {
              __sub_40DEB0_dword_443434 = (int)v31;
              k_3 = k_2;
              v66 = v21;
              v46 = 0;
              v47 = 0;
              while ( 1 )
              {
                sub_40E4D0();
                v31 = (int *)(__sub_40DEB0_dword_443434 - 8);
                k_4 = v46 + v45 - 1;
                --v46;
                if ( ++v47 >= k_3 )
                  break;
                __sub_40DEB0_dword_443434 -= 8;
              }
              v21 = v66;
              k = k_4;
              v30 = (int *)__sub_40DEB0_dword_44342C;
              v5 = -1;
            }
          }
          v31 -= 2;
        }
        v19 = v72;
        v4 = v69;
      }
      v36 = (int)&v30[v74 / 0xFFFFFFFC];
      v4 >>= 1;
      ++v19;
    }
    while ( v19 < v76 );
    __sub_40DEB0_dword_44342C = v36;
    __sub_40DEB0_dword_443434 = (int)v21;
    return v63;
  }
  else
  {
    __sub_40DEB0_dword_443434 = 0;
    return nullptr;
  }
}

#undef FILE
#undef sub_40E4D0
