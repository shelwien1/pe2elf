// sub_415380 @ 0x00415380 — __usercall
// Extracted from BMF.cpp:19645-20060 by extract.py per incdec.md.

typedef unsigned char t_sub_415380_byte_439860[32];
static t_sub_415380_byte_439860& __sub_415380_byte_439860 = *(t_sub_415380_byte_439860*)0x00439860;
typedef int t_sub_415380_dword_443364;
static t_sub_415380_dword_443364& __sub_415380_dword_443364 = *(t_sub_415380_dword_443364*)0x00443364;
typedef int t_sub_415380_n2;
static t_sub_415380_n2& __sub_415380_n2 = *(t_sub_415380_n2*)0x00443360;

#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0
static inline unsigned int __fwd_sub_415380_sub_414860(void *a0, int a1, int a2, int a3) { return __sub_414860((int *)a0, a1, a2, a3); }
#define sub_414860 __fwd_sub_415380_sub_414860
#define sub_414CE0 __sub_414CE0
#define sub_414F60 __sub_414F60
static inline void ** __fwd_sub_415380_sub_415270(void *a0, char a1) { return __sub_415270((void **)a0, a1); }
#define sub_415270 __fwd_sub_415380_sub_415270
static inline int __fwd_sub_415380_sub_4159E0(void *a0, int a1) { return __sub_4159E0((int *)a0, a1); }
#define sub_4159E0 __fwd_sub_415380_sub_4159E0
#define sub_416C90 __sub_416C90
static inline void __fwd_sub_415380_sub_417200(int a0, char a1, void *a2) { __sub_417200(a0, a1, (unsigned __int8 *)a2); }
#define sub_417200 __fwd_sub_415380_sub_417200
#define sub_417980 __sub_417980
static inline void __fwd_sub_415380_sub_4197A0(const __m128 &a0, const __m128 &a1, void *a2, int a3, int a4, void *a5) { __sub_4197A0(a0, a1, (_BYTE *)a2, a3, a4, (_BYTE *)a5); }
#define sub_4197A0 __fwd_sub_415380_sub_4197A0
static inline int __fwd_sub_415380_sub_421930(void *a0, void *a1) { return __sub_421930((unsigned __int16 *)a0, (unsigned __int8 *)a1); }
#define sub_421930 __fwd_sub_415380_sub_421930
static inline void __fwd_sub_415380_sub_424500(void *a0, int a1, int a2, void *a3) { __sub_424500((_BYTE *)a0, a1, a2, (_BYTE *)a3); }
#define sub_424500 __fwd_sub_415380_sub_424500
static inline int __fwd_sub_415380_sub_424D90(void *a0, int a1) { return __sub_424D90((unsigned __int16 *)a0, a1); }
#define sub_424D90 __fwd_sub_415380_sub_424D90

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#define FILE FILE1

PROBE_DECL(__sub_415380)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) void __sub_415380(const __m128 &a1__ref, const __m128 &a2__ref, unsigned __int16 *p_i, unsigned __int8 *a4, _BYTE *a5)
{
  alignas(16) unsigned char __hexrays_frame[96];   // original frame, ebp-0x50..ebp+0x0
  int &Size = *(int *)(__hexrays_frame + 0);
  int &v58 = *(int *)(__hexrays_frame + 8);
  int &v59 = *(int *)(__hexrays_frame + 8);
  int &Blocka_5 = *(int *)(__hexrays_frame + 12);
  int &v61 = *(int *)(__hexrays_frame + 12);
  size_t * &Blocka_2 = *(size_t * *)(__hexrays_frame + 16);
  void * &Blocka = *(void * *)(__hexrays_frame + 16);
  int &v64 = *(int *)(__hexrays_frame + 20);
  int &v65 = *(int *)(__hexrays_frame + 24);
  int &v66 = *(int *)(__hexrays_frame + 28);
  int &v67 = *(int *)(__hexrays_frame + 32);
  int &v68 = *(int *)(__hexrays_frame + 36);
  int &v69 = *(int *)(__hexrays_frame + 40);
  int &v70 = *(int *)(__hexrays_frame + 44);
  int &v71 = *(int *)(__hexrays_frame + 48);
  int &v72 = *(int *)(__hexrays_frame + 52);
  int &v73 = *(int *)(__hexrays_frame + 56);
  unsigned int &n5 = *(unsigned int *)(__hexrays_frame + 60);
  PROBE_HIT(__sub_415380);
  __m128 a1 = a1__ref;
  __m128 a2 = a2__ref;
  void *v5; // eax
  int Blocka_3; // ebp
  char v7; // fps
  int v8; // eax
  int Blocka_4; // esi
  int v10; // ebp
  int v11; // edx
  size_t *v12; // ebx
  __int16 __sub_415380_n2; // ax
  int v14; // edx
  int n2_1; // ebp
  int n2_2; // esi
  BOOL v17; // ebp
  BOOL v18; // esi
  int v19; // eax
  int v20; // ecx
  int v21; // eax
  __int16 v22; // dx
  unsigned int n0x10000; // ecx
  size_t *v24; // edx
  int Blocka_1; // ebp
  char *buf; // eax
  char v27; // fps
  size_t v28; // esi
  size_t v29; // edi
  size_t v30; // edx
  unsigned int v31; // esi
  unsigned int *v32; // eax
  _DWORD *v33; // ecx
  unsigned int v34; // edi
  int v35; // ebp
  int v36; // edi
  unsigned int v37; // esi
  unsigned int *v38; // eax
  _DWORD *v39; // edx
  unsigned int v40; // edi
  int v41; // ebp
  int v42; // edi
  bool v43; // cc
  int v44; // esi
  int v45; // esi
  int v46; // edi
  int v47; // esi
  int v48; // ecx
  int v49; // ebx
  int v50; // eax
  _BYTE *v51; // edi
  _BYTE *v52; // ebx
  int v53; // ebx
  int v54; // ecx
  int v55; // ebx
  int v56; // esi

  if ( __sub_415380_dword_443364 )
  {
    if ( ::__sub_415380_n2 == 1 )
    {
      if ( (p_i[5] & 0x3F) == 8 )
        sub_424500(a4, *p_i, p_i[1], a5);
      else
        sub_424D90(p_i, (int)a4);
    }
    else if ( ::__sub_415380_n2 == 2 )
    {
      if ( (p_i[5] & 0x3F) == 8 )
        sub_4197A0(a1, a2, a4, *p_i, p_i[1], a5);
      else
        sub_421930(p_i, a4);
    }
  }
  else
  {
    v5 = __op_new(0x7BA230u);
    if ( v5 )
      Blocka_3 = sub_417980((int)v5, p_i[1], *p_i, p_i[1], p_i[5] & 0x3F);
    else
      Blocka_3 = 0;
    sub_414F60();
    sub_417200(Blocka_3, v7, a4);
    v64 = 0;
    v8 = 0;
    Blocka_2 = (size_t *)Blocka_3;
    Blocka_4 = Blocka_3;
    do
    {
      v10 = (unsigned __int8)__sub_415380_byte_439860[v8];
      *((_BYTE *)Blocka_2 + v10 + 1078244) = v8;
      v11 = 0;
      v58 = v8;
      v69 = v10 & 4;
      v68 = v10 & 2;
      v67 = v10 & 0x10;
      v66 = v10 & 1;
      v65 = v10 & 8;
      v70 = v10 & 0x20;
      do
      {
        v72 = v11;
        n5 = 0;
        Blocka_5 = Blocka_4;
        v71 = Blocka_4 + 15 * v11;
        do
        {
          *(_BYTE *)(v71 + 75 * n5 + 1078308) = v64;
          v73 = Blocka_2[4];
          v12 = &Blocka_2[4 * v64];
          __sub_415380_n2 = 2;
          *((_WORD *)v12 + 48) = 2;
          LOWORD(v14) = 2;
          n2_1 = 2;
          n2_2 = 2;
          if ( v69 )
          {
            n2_1 = 4;
            n2_2 = 0;
          }
          if ( v68 )
          {
            LOWORD(v14) = n2_2 + 2;
            n2_2 = 0;
          }
          if ( v67 )
          {
            LOWORD(v14) = n2_1 + v14;
            n2_1 = 0;
          }
          if ( v66 )
          {
            __sub_415380_n2 = n2_2 + 2;
            n2_2 = 0;
            *((_WORD *)v12 + 52) = 0;
          }
          else
          {
            *((_WORD *)v12 + 52) = n2_2;
          }
          if ( v65 )
          {
            __sub_415380_n2 += n2_1;
            n2_1 = 0;
            *((_WORD *)v12 + 51) = 0;
          }
          else
          {
            *((_WORD *)v12 + 51) = n2_1;
          }
          if ( v70 )
          {
            *((_WORD *)v12 + 49) = v14 + __sub_415380_n2;
            LOWORD(v14) = 0;
            *((_WORD *)v12 + 50) = 0;
          }
          else
          {
            *((_WORD *)v12 + 50) = v14;
            *((_WORD *)v12 + 49) = __sub_415380_n2;
          }
          v17 = n2_1 != 0;
          v18 = n2_2 != 0;
          v14 = (unsigned __int16)v14;
          if ( (_WORD)v14 )
            v14 = 1;
          v19 = v18 + v17 + v14 + 2;
          if ( v19 <= v73 )
          {
            *((_BYTE *)v12 + 110) = v19;
          }
          else
          {
            *((_BYTE *)v12 + 110) = v18 + v17 + v14 + 1;
            *((_WORD *)v12 + 48) = 0;
          }
          if ( *((_WORD *)v12 + v72 + 48)
            && *((_WORD *)v12 + n5 + 48)
            && (v20 = *((unsigned __int8 *)v12 + 110), v20 <= v73) )
          {
            v21 = 1;
            v22 = (unsigned __int8)(1 << (5 - v20));
            *((_BYTE *)v12 + 111) = v22;
            *((_WORD *)v12 + 54) = v22 << 6;
            *((_WORD *)v12 + v72 + 48) += v22;
            *((_WORD *)v12 + n5 + 48) += *((unsigned __int8 *)v12 + 111);
            *((_WORD *)v12 + 53) = *((_WORD *)v12 + 48)
                                 + *((_WORD *)v12 + 52)
                                 + *((_WORD *)v12 + 51)
                                 + *((_WORD *)v12 + 50)
                                 + *((_WORD *)v12 + 49);
          }
          else
          {
            v21 = 0;
          }
          v64 += v21;
          ++n5;
        }
        while ( n5 < 5 );
        Blocka_4 = Blocka_5;
        v11 = v72 + 1;
      }
      while ( (unsigned int)(v72 + 1) < 5 );
      n0x10000 = 0;
      v24 = &Blocka_2[0x10000 * v58];
      do
      {
        LOWORD(v24[n0x10000 + 531818]) = 0x2000;
        HIWORD(v24[n0x10000++ + 531818]) = 0x2000;
      }
      while ( n0x10000 < 0x10000 );
      Blocka_4 = Blocka_5 + 1;
      v8 = v58 + 1;
    }
    while ( (unsigned int)(v58 + 1) < 0xF );
    Blocka_1 = (int)Blocka_2;
    buf = (char *)__op_new(Blocka_2[4]);
    Size = Blocka_2[4];
    Blocka_2[269672] = (size_t)buf;
    sub_4349F0(buf,1,Size);
    v28 = Blocka_2[25];
    v29 = Blocka_2[26];
    Blocka_2[262916] = Blocka_2[24];
    v30 = Blocka_2[27];
    Blocka_2[262917] = v28;
    Blocka_2[262918] = v29;
    Blocka_2[262919] = v30;
    Blocka_2[269556] = (size_t)(Blocka_2 + 269546);
    sub_414860((int *)(Blocka_1 + 1078184), 0, *(_DWORD *)(Blocka_1 + 16), 1);
    Blocka_2[269558] = (size_t)(Blocka_2 + 269554);
    v31 = Blocka_2[4];
    v32 = (unsigned int *)__op_new(24 * v31 + 4);
    if ( v32 )
    {
      *v32 = v31;
      v33 = v32 + 1;
      if ( v31 )
      {
        if ( v31 >> 1 )
        {
          v34 = 0;
          do
          {
            v35 = 12 * v34;
            v32[v35 + 6] = 0;
            ++v34;
            v32[v35 + 12] = 0;
          }
          while ( v34 < v31 >> 1 );
          Blocka_1 = (int)Blocka_2;
          v36 = 2 * v34 + 1;
        }
        else
        {
          v36 = 1;
        }
        if ( v31 > v36 - 1 )
          v32[6 * v36] = 0;
      }
    }
    else
    {
      v33 = nullptr;
    }
    v37 = *(_DWORD *)(Blocka_1 + 16);
    *(_DWORD *)(Blocka_1 + 1078208) = v33;
    v38 = (unsigned int *)__op_new(24 * v37 + 4);
    if ( v38 )
    {
      *v38 = v37;
      v39 = v38 + 1;
      if ( v37 )
      {
        if ( v37 >> 1 )
        {
          Blocka = (void *)Blocka_1;
          v40 = 0;
          do
          {
            v41 = 12 * v40;
            v38[v41 + 6] = 0;
            ++v40;
            v38[v41 + 12] = 0;
          }
          while ( v40 < v37 >> 1 );
          Blocka_1 = (int)Blocka;
          v42 = 2 * v40 + 1;
        }
        else
        {
          v42 = 1;
        }
        if ( v37 > v42 - 1 )
          v38[6 * v42] = 0;
      }
    }
    else
    {
      v39 = nullptr;
    }
    v43 = *(_DWORD *)(Blocka_1 + 16) <= 0;
    *(_DWORD *)(Blocka_1 + 1078212) = v39;
    if ( !v43 )
    {
      v44 = 0;
      do
      {
        sub_414860((int *)(*(_DWORD *)(Blocka_1 + 1078208) + 24 * v44), 0, 99, 0);
        sub_414860((int *)(*(_DWORD *)(Blocka_1 + 1078212) + 24 * v44++), 0, 33, 0);
      }
      while ( v44 < *(_DWORD *)(Blocka_1 + 16) );
    }
    if ( *(int *)(Blocka_1 + 4) > 0 )
    {
      v59 = *(_DWORD *)(Blocka_1 + 1078236);
      v45 = 0;
      do
      {
        v61 = v45 + 1;
        *(_BYTE *)(*(_DWORD *)(Blocka_1 + 76) + 3) = *(_WORD *)(*(_DWORD *)(Blocka_1 + 76) - 8) == 0;
        *(_BYTE *)(*(_DWORD *)(Blocka_1 + 76) + 5) = *(_WORD *)(*(_DWORD *)(Blocka_1 + 80) - 8) == 0;
        v46 = *(_DWORD *)(Blocka_1 + 72);
        v47 = *(_DWORD *)(Blocka_1 + 68);
        v48 = *(_DWORD *)(Blocka_1 + 64);
        v49 = *(_DWORD *)(Blocka_1 + 60);
        v50 = *(_DWORD *)(Blocka_1 + 56);
        *(_DWORD *)(Blocka_1 + 72) = v47;
        *(_DWORD *)(Blocka_1 + 68) = v48;
        *(_DWORD *)(Blocka_1 + 64) = v49;
        *(_DWORD *)(Blocka_1 + 60) = v50;
        *(_DWORD *)(Blocka_1 + 56) = v46;
        v46 += 56;
        *(_DWORD *)(Blocka_1 + 76) = v46;
        v50 += 56;
        *(_DWORD *)(Blocka_1 + 80) = v50;
        *(_DWORD *)(Blocka_1 + 84) = v49 + 56;
        *(_DWORD *)(Blocka_1 + 88) = v48 + 56;
        *(_DWORD *)(Blocka_1 + 92) = v47 + 56;
        LOBYTE(v50) = *(unsigned __int16 *)(v50 + 8) == 0;
        *(_BYTE *)(v46 + 4) = v50;
        *(_BYTE *)(*(_DWORD *)(Blocka_1 + 76) - 2) = v50;
        *(_BYTE *)(*(_DWORD *)(Blocka_1 + 76) - 9) = v50;
        LOBYTE(v50) = *(_WORD *)(*(_DWORD *)(Blocka_1 + 80) + 16) == 0;
        *(_BYTE *)(*(_DWORD *)(Blocka_1 + 76) + 6) = v50;
        *(_BYTE *)(*(_DWORD *)(Blocka_1 + 76) - 1) = v50;
        *(_BYTE *)(*(_DWORD *)(Blocka_1 + 76) + 7) = *(_WORD *)(*(_DWORD *)(Blocka_1 + 80) + 24) == 0;
        v51 = *(_BYTE **)(Blocka_1 + 80);
        v52 = *(_BYTE **)(Blocka_1 + 84);
        *(_DWORD *)(Blocka_1 + 76) += 8;
        v51 += 8;
        *(_DWORD *)(Blocka_1 + 80) = v51;
        *(_DWORD *)(Blocka_1 + 88) += 8;
        v52 += 8;
        *(_DWORD *)(Blocka_1 + 84) = v52;
        *(_DWORD *)(Blocka_1 + 92) += 8;
        *(_BYTE *)(Blocka_1 + 1078692) = v51[26] + v51[18] + v51[10] + v51[2] + v51[34] - 5;
        LOBYTE(v50) = v52[26];
        LOBYTE(v47) = v52[10] + v52[2];
        LOBYTE(v51) = v52[18];
        LOBYTE(v52) = v52[34];
        *(_BYTE *)(Blocka_1 + 1078695) = 0;
        *(_BYTE *)(Blocka_1 + 1078694) = 0;
        LOBYTE(v50) = v50 + (_BYTE)v51 + v47 + (_BYTE)v52 - 5;
        v45 = v61;
        v53 = *(_DWORD *)Blocka_1;
        *(_BYTE *)(Blocka_1 + 1078693) = v50;
        if ( v53 > 0 )
        {
          v54 = 0;
          do
          {
            ++v54;
            *(_WORD *)(*(_DWORD *)(Blocka_1 + 76) + 8 * v54 - 8) = *(_WORD *)(v59 + 2 * v54 - 2);
            v53 = *(_DWORD *)Blocka_1;
          }
          while ( v54 < *(_DWORD *)Blocka_1 );
          v59 += 2 * v54;
        }
        if ( v53 > 0 )
        {
          v55 = 0;
          do
          {
            v56 = sub_4159E0((int *)Blocka_1, v55);
            sub_416C90(Blocka_1);
            v55 += v56;
          }
          while ( v55 < *(_DWORD *)Blocka_1 );
          v45 = v61;
        }
      }
      while ( v45 < *(_DWORD *)(Blocka_1 + 4) );
    }
    sub_414CE0();
    sub_415270((void **)Blocka_1, 1);
  }
}

// __usercall thunk for sub_415380 @ 0x00415380: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_415380()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $44, %esp\n"
    "movups %xmm1, 12(%esp)\n"
    "movups %xmm3, 28(%esp)\n"
    "push 16(%ebp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "lea 40(%esp), %eax\n"
    "push %eax\n"
    "lea 28(%esp), %eax\n"
    "push %eax\n"
    "call __sub_415380\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef FILE
#undef sub_414860
#undef sub_414CE0
#undef sub_414F60
#undef sub_415270
#undef sub_4159E0
#undef sub_416C90
#undef sub_417200
#undef sub_417980
#undef sub_4197A0
#undef sub_421930
#undef sub_424500
#undef sub_424D90
#undef sub_4349F0
