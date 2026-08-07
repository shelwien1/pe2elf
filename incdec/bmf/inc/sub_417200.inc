// sub_417200 @ 0x00417200 — __userpurge
// Extracted from BMF.cpp:21323-21825 by extract.py per incdec.md.

typedef int t_sub_417200_n4_4;
static t_sub_417200_n4_4& __sub_417200_n4_4 = *(t_sub_417200_n4_4*)0x00445740;

#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0
#define sub_412110 __sub_412110
static inline int __fwd_sub_417200_sub_412B10(void *a0, int a1) { return __sub_412B10((unsigned int *)a0, a1); }
#define sub_412B10 __fwd_sub_417200_sub_412B10
static inline unsigned int __fwd_sub_417200_sub_414860(void *a0, int a1, int a2, int a3) { return __sub_414860((int *)a0, a1, a2, a3); }
#define sub_414860 __fwd_sub_417200_sub_414860

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

PROBE_DECL(__sub_417200)
extern "C" __attribute__((visibility("hidden"))) void __sub_417200(int Blocka, char a2, unsigned __int8 *a3)
{
  alignas(16) unsigned char __hexrays_frame[66064];   // original frame, ebp-0x10200..ebp+0x0
  _DWORD (&v78)[15] = *(_DWORD (*)[15])(__hexrays_frame + 0);
  void * &v79 = *(void * *)(__hexrays_frame + 60);
  int &n0x2000_5 = *(int *)(__hexrays_frame + 64);
  char (&buf)[4] = *(char (*)[4])(__hexrays_frame + 68);
  _QWORD (&v82)[127] = *(_QWORD (*)[127])(__hexrays_frame + 72);
  int &v83 = *(int *)(__hexrays_frame + 1088);
  int &v84 = *(int *)(__hexrays_frame + 1092);
  int &v85 = *(int *)(__hexrays_frame + 1096);
  _QWORD (&v86)[2] = *(_QWORD (*)[2])(__hexrays_frame + 65604);
  int &v87 = *(int *)(__hexrays_frame + 65620);
  _DWORD (&v88)[91] = *(_DWORD (*)[91])(__hexrays_frame + 65624);
  BOOL &n4_1 = *(BOOL *)(__hexrays_frame + 65988);
  void * &Block = *(void * *)(__hexrays_frame + 65992);
  unsigned __int8 * &v91 = *(unsigned __int8 * *)(__hexrays_frame + 65996);
  unsigned int &v92 = *(unsigned int *)(__hexrays_frame + 66000);
  unsigned int &v93 = *(unsigned int *)(__hexrays_frame + 66004);
  unsigned int &v94 = *(unsigned int *)(__hexrays_frame + 66012);
  int &Blockaa = *(int *)(__hexrays_frame + 66016);
  unsigned __int8 * &v96 = *(unsigned __int8 * *)(__hexrays_frame + 66020);
  unsigned int &k_1 = *(unsigned int *)(__hexrays_frame + 66024);
  int &Blocka_1 = *(int *)(__hexrays_frame + 66032);
  PROBE_HIT(__sub_417200);
  void *v3; // esp
  unsigned __int8 *v4; // esi
  int n8; // edx
  unsigned int k_2; // edi
  unsigned int i; // eax
  int v8; // ecx
  int *Blockaa_1; // ebx
  unsigned __int8 *v10; // ebx
  int v11; // edx
  unsigned int v12; // eax
  void *v13; // esi
  BOOL n4; // ecx
  _QWORD *n0x2000_6; // ebx
  _DWORD *Blockaa_3; // esi
  int n0x2000_2; // eax
  int n0x2000_1; // ecx
  unsigned int v19; // ebx
  int v20; // eax
  unsigned int n0x2000_4; // edx
  unsigned int n0x2000_3; // esi
  int Blockaa_4; // ecx
  unsigned int v24; // ebx
  unsigned int k; // esi
  int v26; // eax
  int n4_2; // edx
  char *v28; // ecx
  unsigned int v29; // edx
  int v30; // ebx
  int v31; // esi
  int v32; // eax
  unsigned __int8 *v33; // edx
  void *v34; // eax
  char v35; // fps
  BOOL *p_n4; // esi
  int n16_2; // ebx
  unsigned int k_3; // eax
  int v39; // edi
  unsigned int j_1; // eax
  unsigned int j; // esi
  unsigned __int8 *v42; // ecx
  _BYTE *v43; // ebx
  int v44; // ecx
  _BYTE *v45; // ebx
  bool v46; // cf
  int n256; // eax
  bool v48; // cc
  int v49; // edx
  int v50; // eax
  int v51; // edx
  int v52; // edi
  unsigned int v53; // eax
  int v54; // esi
  int v55; // ecx
  int v56; // edx
  int v57; // ecx
  int v58; // edx
  bool v59; // zf
  unsigned __int8 *v60; // edx
  unsigned int v61; // eax
  int v62; // edi
  int v63; // ecx
  unsigned int v64; // eax
  BOOL *p_n4_2; // esi
  int n16_1; // ebx
  int Blockaa_2; // esi
  int v68; // edi
  int n0x2000; // edi
  unsigned int v70; // eax
  int v71; // edx
  int v72; // edi
  unsigned int v73; // esi
  int v74; // ecx
  unsigned int v75; // eax
  BOOL *p_n4_1; // esi
  int n16; // ebx

  Blocka_1 = Blocka;
  v3 = alloca(65968);
  v4 = a3;
  n8 = *(_DWORD *)(Blocka + 8);
  v91 = a3;
  Blockaa = Blocka;
  v93 = 0xFFFFFFFF >> (-(char)n8 & 31);
  k_2 = (n8 + 7) >> 3;
  for ( i = 0; i < 8; ++i )
  {
    v8 = 12 * i;
    v88[v8] = 0;
    v88[v8 + 6] = 0;
  }
  Blockaa_1 = (int *)Blockaa;
  if ( n8 <= 8 )
  {
    n256 = 256;
    do
    {
      *(_OWORD *)&v78[n256 + 12] = 0;
      *(_OWORD *)&v78[n256 + 8] = 0;
      *(_OWORD *)&v78[n256 + 4] = 0;
      *(_OWORD *)&v78[n256] = 0;
      n256 -= 16;
    }
    while ( n256 * 4 );
    v48 = Blockaa_1[2] < 8;
    v49 = Blockaa_1[1];
    Blockaa_1[4] = 0;
    if ( v48 )
    {
      v50 = 0;
      if ( v49 )
      {
        v51 = *Blockaa_1;
        v96 = a3 - 1;
        v84 = 0;
        v52 = 0;
        do
        {
          if ( !v51 )
            break;
          v83 = v52;
          v53 = 0;
          v54 = v84;
          v55 = 0;
          do
          {
            v56 = Blockaa_1[2];
            v57 = v55 - v56;
            if ( v57 < 0 )
            {
              ++v96;
              v57 = 8 - v56;
            }
            v58 = v93 & (*v96 >> (v57 & 31));
            v59 = *(_DWORD *)&buf[4 * v58 - 4] == 0;
            v85 = v57;
            ++v53;
            *(_DWORD *)&buf[4 * v58 - 4] = 1;
            v55 = v85;
            Blockaa_1[4] += v59;
            *(_WORD *)(Blockaa_1[269559] + 2 * v54) = v58;
            v51 = *Blockaa_1;
            ++v54;
          }
          while ( v53 < *Blockaa_1 );
          v50 = Blockaa_1[4];
          v84 = v54;
          v52 = v83 + 1;
        }
        while ( v83 + 1 < (unsigned int)Blockaa_1[1] );
      }
    }
    else if ( v49 * *Blockaa_1 )
    {
      v60 = v91;
      v61 = 0;
      do
      {
        Blockaa_1[4] += *(_DWORD *)&buf[4 * *v60 - 4] == 0;
        v62 = Blockaa_1[269559];
        v63 = *v60;
        *(_DWORD *)&buf[4 * v63 - 4] = 1;
        ++v60;
        *(_WORD *)(v62 + 2 * v61++) = v63;
      }
      while ( v61 < Blockaa_1[1] * *Blockaa_1 );
      v50 = Blockaa_1[4];
    }
    else
    {
      v50 = 0;
    }
    sub_412110(v50 - 1, v93 + 1);
    v64 = Blockaa_1[4];
    if ( v64 <= v93 )
    {
      sub_414860((int *)v86, (int)Blockaa_1, v93 - v64 + 2, 1);
      v87 = 19 * LODWORD(v86[0]);
      v70 = Blockaa_1[4];
      if ( v70 )
      {
        v71 = 0;
        v72 = 0;
        v73 = 0;
        do
        {
          if ( *(_DWORD *)&buf[4 * v72 - 4] )
          {
            sub_412B10((unsigned int *)v86, v72 - v71);
            v70 = Blockaa_1[4];
            *(_DWORD *)&buf[4 * v72 - 4] = v73;
            v74 = v72 + 1;
            v71 = v72 + 1;
            ++v73;
          }
          else
          {
            v74 = v72 + 1;
          }
          v72 = v74;
        }
        while ( v73 < v70 );
      }
      if ( Blockaa_1[1] * *Blockaa_1 )
      {
        v75 = 0;
        do
        {
          *(_WORD *)(Blockaa_1[269559] + 2 * v75) = *(_DWORD *)&buf[4
                                                                  * *(unsigned __int16 *)(Blockaa_1[269559] + 2 * v75)
                                                                  - 4];
          ++v75;
        }
        while ( v75 < Blockaa_1[1] * *Blockaa_1 );
      }
      p_n4_1 = &n4_1;
      n16 = 16;
      do
      {
        p_n4_1 -= 6;
        __op_delete((void *)p_n4_1[5]);
        --n16;
      }
      while ( n16 );
    }
    else
    {
      p_n4_2 = &n4_1;
      n16_1 = 16;
      do
      {
        p_n4_2 -= 6;
        __op_delete((void *)p_n4_2[5]);
        --n16_1;
      }
      while ( n16_1 );
    }
  }
  else
  {
    sub_4349F0(buf,0,0x10000);
    Blockaa_1[4] = 1;
    *(_DWORD *)buf = v93 & *(_DWORD *)a3;
    *(_WORD *)Blockaa_1[269559] = 0;
    if ( (unsigned int)(Blockaa_1[1] * *Blockaa_1) > 1 )
    {
      v96 = a3;
      k_1 = k_2;
      Blockaa = (int)Blockaa_1;
      v10 = v91;
      v11 = 0;
      v12 = 1;
      while ( 1 )
      {
        v10 += k_1;
        v13 = (void *)(v93 & *(_DWORD *)v10);
        if ( v13 != *(void **)&buf[8 * v11] )
        {
          v11 = 0;
          if ( v13 != *(void **)buf )
          {
            v92 = v12;
            v91 = v10;
            while ( 1 )
            {
              n4 = *(_DWORD *)&buf[8 * v11] < (unsigned int)v13;
              n0x2000_6 = &v82[v11];
              v11 = *((unsigned __int16 *)n0x2000_6 + n4);
              if ( !*((_WORD *)n0x2000_6 + n4) )
                break;
              if ( v13 == *(void **)&buf[8 * v11] )
              {
                v12 = v92;
                v10 = v91;
                __sub_417200_n4_4 = n4;
                goto LABEL_12;
              }
            }
            n0x2000_5 = (int)n0x2000_6;
            v10 = v91;
            n4_1 = n4;
            Block = v13;
            Blockaa_2 = Blockaa;
            v68 = *(_DWORD *)(Blockaa + 16);
            __sub_417200_n4_4 = n4;
            v11 = (unsigned __int16)v68;
            n0x2000 = v68 + 1;
            *(_WORD *)(n0x2000_5 + 2 * n4) = v11;
            v12 = v92;
            *(_DWORD *)(Blockaa_2 + 16) = n0x2000;
            if ( n0x2000 > 0x2000 )
            {
              v4 = v96;
              n0x2000_2 = n0x2000;
              k_2 = k_1;
              Blockaa_1 = (int *)Blockaa;
              goto LABEL_14;
            }
            *(_DWORD *)&buf[8 * v11] = Block;
          }
        }
LABEL_12:
        Blockaa_3 = (_DWORD *)Blockaa;
        *(_WORD *)(*(_DWORD *)(Blockaa + 1078236) + 2 * v12++) = v11;
        if ( v12 >= Blockaa_3[1] * *Blockaa_3 )
        {
          v4 = v96;
          k_2 = k_1;
          Blockaa_1 = (int *)Blockaa;
          n0x2000_2 = *(_DWORD *)(Blockaa + 16);
          goto LABEL_14;
        }
      }
    }
    n0x2000_2 = Blockaa_1[4];
LABEL_14:
    sub_412110(n0x2000_2 - 1, 0x2001u);
    n0x2000_1 = Blockaa_1[4];
    if ( n0x2000_1 > 0x2000 )
    {
      Block = __op_new(Blockaa_1[1] * k_2 * *Blockaa_1);
      v26 = *Blockaa_1;
      n4_2 = Blockaa_1[1];
      n0x2000_5 = *Blockaa_1;
      n4_1 = n4_2;
      if ( k_2 )
      {
        v94 = n4_1 * v26;
        if ( k_2 >> 1 )
        {
          v28 = (char *)Block + n4_1 * n0x2000_5;
          v96 = v4;
          k_1 = k_2;
          Blockaa = (int)Blockaa_1;
          v29 = 0;
          do
          {
            v30 = 2 * v29;
            v31 = 2 * v29++ * v94;
            (&v91)[v30] = (unsigned __int8 *)Block + v31;
            *(&v92 + v30) = (unsigned int)&v28[v31];
          }
          while ( v29 < k_2 >> 1 );
          v4 = v96;
          k_2 = k_1;
          Blockaa_1 = (int *)Blockaa;
          v32 = 2 * v29 + 1;
        }
        else
        {
          v32 = 1;
        }
        if ( k_2 > v32 - 1 )
          *(&Block + v32) = (char *)Block + n4_1 * -n0x2000_5 + v94 * v32;
      }
      else
      {
        v94 = n4_1 * v26;
      }
      if ( v94 )
      {
        v33 = a3;
        if ( k_2 )
        {
          k_1 = k_2;
          Blockaa = (int)Blockaa_1;
          n0x2000_5 = 0;
          k_3 = k_2;
          v39 = 0;
          j_1 = k_3 >> 1;
          while ( 1 )
          {
            while ( 1 )
            {
              if ( j_1 )
              {
                for ( j = 0; j < j_1; ++j )
                {
                  v42 = (&v91)[2 * j];
                  *v42 = v33[2 * j];
                  v43 = (_BYTE *)*(&v92 + 2 * j);
                  (&v91)[2 * j] = v42 + 1;
                  *v43 = v33[2 * j + 1];
                  *(&v92 + 2 * j) = (unsigned int)(v43 + 1);
                }
                v44 = 2 * j + 1;
                v4 = &v33[2 * j];
              }
              else
              {
                v44 = 1;
              }
              if ( v44 - 1 >= k_1 )
                break;
              v45 = *(&Block + v44);
              v4 = &v33[v44];
              *v45 = v33[v44 - 1];
              v46 = ++v39 < v94;
              *(&Block + v44) = v45 + 1;
              if ( !v46 )
                goto LABEL_71;
              v33 += v44;
            }
            if ( ++v39 >= v94 )
              break;
            v33 = v4;
          }
LABEL_71:
          k_2 = k_1;
          Blockaa_1 = (int *)Blockaa;
        }
      }
      v79 = (void *)Blockaa_1[269559];
      Blockaa_1[1] = k_2 * n4_1;
      Blockaa_1[2] = 8;
      __op_delete(v79);
      v34 = __op_new(2 * Blockaa_1[1] * *Blockaa_1);
      v79 = Block;
      Blockaa_1[269559] = (int)v34;
      __sub_417200((int)Blockaa_1, v35, (unsigned __int8 *)v79);
      __op_delete(Block);
    }
    else
    {
      if ( 4 * k_2 )
      {
        Blockaa = (int)Blockaa_1;
        v19 = 0;
        do
        {
          sub_414860((int *)&v86[3 * v19], v19, 256, 1);
          ++v19;
        }
        while ( v19 < 4 * k_2 );
        Blockaa_1 = (int *)Blockaa;
        n0x2000_1 = *(_DWORD *)(Blockaa + 16);
      }
      if ( n0x2000_1 )
      {
        v20 = 0;
        n0x2000_4 = 0;
        n0x2000_3 = n0x2000_1;
        Blockaa_4 = (int)Blockaa_1;
        do
        {
          v24 = *(_DWORD *)&buf[8 * n0x2000_4];
          if ( k_2 )
          {
            n0x2000_5 = n0x2000_4;
            k_1 = k_2;
            Blockaa = Blockaa_4;
            for ( k = 0; k < k_1; ++k )
            {
              sub_412B10((unsigned int *)&v86[12 * k + 3 * v20], (unsigned __int8)v24);
              v20 = (unsigned __int8)v24 >> 6;
              v24 >>= 8;
            }
            n0x2000_4 = n0x2000_5;
            k_2 = k_1;
            Blockaa_4 = Blockaa;
            v24 = *(_DWORD *)&buf[8 * n0x2000_5];
            n0x2000_3 = *(_DWORD *)(Blockaa + 16);
          }
          v20 = (unsigned __int8)v24 >> 7;
          ++n0x2000_4;
        }
        while ( n0x2000_4 < n0x2000_3 );
      }
    }
    p_n4 = &n4_1;
    n16_2 = 16;
    do
    {
      p_n4 -= 6;
      __op_delete((void *)p_n4[5]);
      --n16_2;
    }
    while ( n16_2 );
  }
}

// __userpurge thunk for sub_417200 @ 0x00417200: reads the register arguments the
// caller passes, calls the moved body as cdecl, and pops 4 bytes of
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_417200()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $20, %esp\n"
    "mov %ecx, 4(%esp)\n"
    "fnstsw %ax\n"
    "mov %eax, 8(%esp)\n"
    "push 8(%ebp)\n"
    "push 12(%esp)\n"
    "push 12(%esp)\n"
    "call __sub_417200\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret $4\n"
  );
}

#undef FILE
#undef sub_412110
#undef sub_412B10
#undef sub_414860
#undef sub_4349F0
