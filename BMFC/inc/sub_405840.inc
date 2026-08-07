// sub_405840 @ 0x00405840 — __usercall
// Extracted from BMF.cpp:4723-4983 by extract.py per incdec.md.

typedef int t_sub_405840_Buffer_0;
static t_sub_405840_Buffer_0& __sub_405840_Buffer_0 = *(t_sub_405840_Buffer_0*)(blob1 + 0x00443378 - BMF_BLOB_BASE);
typedef char * t_sub_405840_buf;
static t_sub_405840_buf& __sub_405840_buf = *(t_sub_405840_buf*)(blob1 + 0x00443380 - BMF_BLOB_BASE);
typedef unsigned char t_sub_405840_byte_44339C[0x10000];
static t_sub_405840_byte_44339C& __sub_405840_byte_44339C = *(t_sub_405840_byte_44339C*)(blob1 + 0x0044339C - BMF_BLOB_BASE);
typedef unsigned char t_sub_405840_byte_44339E[0x10000];
static t_sub_405840_byte_44339E& __sub_405840_byte_44339E = *(t_sub_405840_byte_44339E*)(blob1 + 0x0044339E - BMF_BLOB_BASE);
typedef int t_sub_405840_dword_443364;
static t_sub_405840_dword_443364& __sub_405840_dword_443364 = *(t_sub_405840_dword_443364*)(blob1 + 0x00443364 - BMF_BLOB_BASE);
typedef int t_sub_405840_dword_443384;
static t_sub_405840_dword_443384& __sub_405840_dword_443384 = *(t_sub_405840_dword_443384*)(blob1 + 0x00443384 - BMF_BLOB_BASE);
typedef int t_sub_405840_n2;
static t_sub_405840_n2& __sub_405840_n2 = *(t_sub_405840_n2*)(blob1 + 0x00443360 - BMF_BLOB_BASE);
typedef int t_sub_405840_n256_0[0x10000];
static t_sub_405840_n256_0& __sub_405840_n256_0 = *(t_sub_405840_n256_0*)(blob1 + 0x00443398 - BMF_BLOB_BASE);
typedef int t_sub_405840_n4_5;
static t_sub_405840_n4_5& __sub_405840_n4_5 = *(t_sub_405840_n4_5*)(blob1 + 0x00443394 - BMF_BLOB_BASE);

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980
static inline void ** __fwd_sub_405840_sub_402E70(void *a0, char a1) { return __sub_402E70((void **)a0, a1); }
#define sub_402E70 __fwd_sub_405840_sub_402E70
static inline char * __fwd_sub_405840_sub_407EF0(void *a0, void *a1, int a2, char a3) { return __sub_407EF0((char *)a0, (char *)a1, a2, a3); }
#define sub_407EF0 __fwd_sub_405840_sub_407EF0
static inline char * __fwd_sub_405840_sub_4081E0(void *a0, void *a1, int a2, char a3) { return __sub_4081E0((char *)a0, (char *)a1, a2, a3); }
#define sub_4081E0 __fwd_sub_405840_sub_4081E0
#define sub_408510 __sub_408510
static inline _DWORD * __fwd_sub_405840_sub_40E590(void *a0, int a1, char a2) { return __sub_40E590((_DWORD *)a0, a1, a2); }
#define sub_40E590 __fwd_sub_405840_sub_40E590
static inline char * __fwd_sub_405840_sub_40E860(int a0, char a1, void *a2, int a3, int a4, void *a5) { return __sub_40E860(a0, a1, (char *)a2, a3, a4, (_BYTE *)a5); }
#define sub_40E860 __fwd_sub_405840_sub_40E860
static inline char * __fwd_sub_405840_sub_40F450(void *a0, char a1, int a2, int a3, int a4) { return __sub_40F450((_DWORD *)a0, a1, a2, a3, a4); }
#define sub_40F450 __fwd_sub_405840_sub_40F450
#define sub_4108C0 __sub_4108C0
static inline _BYTE * __fwd_sub_405840_sub_410AC0(void *a0, int a1, int a2, void *a3) { return __sub_410AC0((_BYTE *)a0, a1, a2, (_BYTE *)a3); }
#define sub_410AC0 __fwd_sub_405840_sub_410AC0
static inline unsigned int __fwd_sub_405840_sub_4111B0(void *a0, int a1, int a2, void *a3) { return __sub_4111B0((_BYTE *)a0, a1, a2, (_BYTE *)a3); }
#define sub_4111B0 __fwd_sub_405840_sub_4111B0
static inline void __fwd_sub_405840_sub_415380(const __m128 &a0, const __m128 &a1, void *a2, void *a3, void *a4) { __sub_415380(a0, a1, (unsigned __int16 *)a2, (unsigned __int8 *)a3, (_BYTE *)a4); }
#define sub_415380 __fwd_sub_405840_sub_415380

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

PROBE_DECL(__sub_405840)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) void __sub_405840(char *Blockb, char *Srca_3, int a3, char a4, const __m128 &a5__ref, const __m128 &a6__ref)
{
  alignas(16) unsigned char __hexrays_frame[76];   // original frame, ebp-0x3c..ebp+0x0
  char * &Blockb_1 = *(char * *)(__hexrays_frame + 0);
  void ** &Blocka = *(void ** *)(__hexrays_frame + 0);
  char * &Blockc = *(char * *)(__hexrays_frame + 0);
  char * &Src = *(char * *)(__hexrays_frame + 4);
  char * &Srca = *(char * *)(__hexrays_frame + 4);
  char * &v42 = *(char * *)(__hexrays_frame + 8);
  char * &v43 = *(char * *)(__hexrays_frame + 8);
  signed int &Size = *(signed int *)(__hexrays_frame + 12);
  signed int &Sizea = *(signed int *)(__hexrays_frame + 12);
  int &n4_1 = *(int *)(__hexrays_frame + 16);
  int &n4 = *(int *)(__hexrays_frame + 16);
  unsigned __int16 (&p_i)[2] = *(unsigned __int16 (*)[2])(__hexrays_frame + 20);
  int &v49 = *(int *)(__hexrays_frame + 24);
  int &v50 = *(int *)(__hexrays_frame + 28);
  int &v51 = *(int *)(__hexrays_frame + 32);
  int &v52 = *(int *)(__hexrays_frame + 36);
  int &v53 = *(int *)(__hexrays_frame + 40);
  PROBE_HIT(__sub_405840);
  __m128 a5 = a5__ref;
  __m128 a6 = a6__ref;
  char *Srca_1; // esi
  char v8; // al
  char *Srca_2; // ebx
  char v10; // fps
  char *__sub_405840_buf; // edx
  unsigned int v12; // ecx
  int n1008; // eax
  _DWORD *v14; // eax
  char v15; // fps
  void **Blockb_2; // ebx
  int v17; // edx
  int v18; // ecx
  int v19; // edi
  char v20; // fps
  char *Srca_5; // ebx
  char *Srca_6; // eax
  signed int Size_2; // edx
  int v24; // eax
  signed int Size_1; // edx
  int v26; // eax
  char v27; // fps
  _DWORD *v28; // eax
  char v29; // fps
  char v30; // fps
  char v31; // fps
  char *Srca_4; // eax
  signed int Sizea_2; // edx
  int v34; // eax
  signed int Sizea_1; // edx
  int v36; // eax

  v53 = a3;
  Srca_1 = Srca_3;
  v8 = __sub_405840_byte_44339E[16 * a3];
  v52 = 16 * a3;
  __sub_405840_n2 = v8 & 3;
  __sub_405840_dword_443364 = (unsigned __int8)(__sub_405840_byte_44339E[16 * a3] & 4) >> 2;
  Srca_2 = Srca_3;
  sub_407EF0(Blockb, Srca_3, a3, a4);
  __sub_405840_buf = ::__sub_405840_buf;
  v12 = (unsigned int)(::__sub_405840_buf + 15) & 0xFFFFFFF0;
  *(_QWORD *)::__sub_405840_buf = 0;
  *((_DWORD *)__sub_405840_buf + 2) = 0;
  *((_WORD *)__sub_405840_buf + 6) = 0;
  __sub_405840_buf[14] = 0;
  *((_QWORD *)__sub_405840_buf + 126) = 0;
  *((_QWORD *)__sub_405840_buf + 127) = 0;
  n1008 = 1008;
  do
  {
    *(_OWORD *)(v12 + n1008 - 16) = 0;
    *(_OWORD *)(v12 + n1008 - 32) = 0;
    *(_OWORD *)(v12 + n1008 - 48) = 0;
    *(_OWORD *)(v12 + n1008 - 64) = 0;
    *(_OWORD *)(v12 + n1008 - 80) = 0;
    *(_OWORD *)(v12 + n1008 - 96) = 0;
    *(_OWORD *)(v12 + n1008 - 112) = 0;
    n1008 -= 112;
  }
  while ( n1008 );
  if ( __sub_405840_dword_443384 )
  {
    v17 = *((_DWORD *)Blockb + 1);
    v18 = *((_DWORD *)Blockb + 2);
    v19 = *((_DWORD *)Blockb + 3);
    *(_DWORD *)p_i = *(_DWORD *)Blockb;
    v49 = v17;
    v50 = v18;
    BYTE2(v50) = 72;
    v51 = v19;
    if ( __sub_405840_n256_0[0] )
    {
      Srca_2 = (char *)__op_new(p_i[1] * p_i[0]);
      Srca_4 = &Blockb[v53 + 16];
      Sizea = *(unsigned __int16 *)Blockb * *((unsigned __int16 *)Blockb + 1);
      n4 = __sub_405840_n4_5;
      if ( __sub_405840_n4_5 == 1 )
      {
        sub_434980(Srca_2,&Blockb[v53 + 16],Sizea);
      }
      else
      {
        if ( (v43 = &Blockb[v53], Sizea <= 6)
          || __sub_405840_n4_5 <= 0
          || (__sub_405840_n4_5 > 1 || Srca_2 <= Srca_4 || Srca_2 - Srca_4 < (unsigned int)(Sizea * __sub_405840_n4_5))
          && (Srca_4 <= Srca_2 || Srca_4 - Srca_2 < (unsigned int)Sizea) )
        {
          Blockc = Blockb;
          Sizea_1 = 0;
          v36 = 0;
          Srca = Srca_1;
          do
          {
            Srca_2[Sizea_1] = v43[v36 + 16];
            v36 += n4;
            ++Sizea_1;
          }
          while ( Sizea_1 < Sizea );
        }
        else
        {
          Blockc = Blockb;
          Sizea_2 = 0;
          v34 = 0;
          Srca = Srca_1;
          do
          {
            Srca_2[Sizea_2] = v43[v34 + 16];
            v34 += n4;
            ++Sizea_2;
          }
          while ( Sizea_2 < Sizea );
        }
        Blockb = Blockc;
        Srca_1 = Srca;
      }
      if ( !__sub_405840_dword_443364 )
        sub_4111B0(Srca_1, *(unsigned __int16 *)Blockb, *((unsigned __int16 *)Blockb + 1), Srca_2);
    }
    if ( __sub_405840_n2 == 1 && !__sub_405840_dword_443364 )
      sub_4108C0((int)Srca_1, *(unsigned __int16 *)Blockb, *((unsigned __int16 *)Blockb + 1));
    sub_415380(a5, a6, p_i, (unsigned __int8 *)Srca_1, Srca_2);
    if ( Srca_2 != Srca_1 )
    {
      if ( (unsigned __int8)__sub_405840_byte_44339C[v52] != __sub_405840_n4_5 - 1 )
        sub_4081E0(Blockb, Srca_2, v53, v20);
      __op_delete(Srca_2);
    }
  }
  else
  {
    if ( __sub_405840_n256_0[0] )
    {
      Srca_5 = (char *)(__sub_405840_Buffer_0 + 32);
      Srca_6 = &Blockb[v53 + 16];
      Size = *(unsigned __int16 *)Blockb * *((unsigned __int16 *)Blockb + 1);
      n4_1 = __sub_405840_n4_5;
      if ( __sub_405840_n4_5 == 1 )
      {
        sub_434980((char *)(__sub_405840_Buffer_0 + 32),&Blockb[v53 + 16],Size);
      }
      else
      {
        v42 = &Blockb[v53];
        if ( Size <= 6
          || __sub_405840_n4_5 <= 0
          || (__sub_405840_n4_5 > 1 || Srca_5 <= Srca_6 || Srca_5 - Srca_6 < (unsigned int)(Size * __sub_405840_n4_5))
          && (Srca_6 <= Srca_5 || Srca_6 - Srca_5 < (unsigned int)Size) )
        {
          Blockb_1 = Blockb;
          Size_1 = 0;
          v26 = 0;
          Src = Srca_1;
          do
          {
            Srca_5[Size_1] = v42[v26 + 16];
            v26 += n4_1;
            ++Size_1;
          }
          while ( Size_1 < Size );
        }
        else
        {
          Blockb_1 = Blockb;
          Size_2 = 0;
          v24 = 0;
          Src = Srca_1;
          do
          {
            Srca_5[Size_2] = v42[v24 + 16];
            v24 += n4_1;
            ++Size_2;
          }
          while ( Size_2 < Size );
        }
        Blockb = Blockb_1;
        Srca_1 = Src;
      }
      if ( __sub_405840_n2 )
      {
        if ( __sub_405840_n2 == 1 )
        {
          sub_410AC0(Srca_1, *(unsigned __int16 *)Blockb, *((unsigned __int16 *)Blockb + 1), Srca_5);
        }
        else
        {
          v28 = __op_new(0x30ACu);
          if ( v28 )
          {
            Blocka = (void **)sub_40E590(v28, *(unsigned __int16 *)Blockb, *Srca_1);
            sub_40E860((int)Blocka, v30, Srca_1, *(unsigned __int16 *)Blockb, *((unsigned __int16 *)Blockb + 1), Srca_5);
          }
          else
          {
            Blocka = nullptr;
            sub_40E860(0, v29, Srca_1, *(unsigned __int16 *)Blockb, *((unsigned __int16 *)Blockb + 1), Srca_5);
          }
          if ( Blocka )
            sub_402E70(Blocka, 1);
        }
      }
      else
      {
        sub_4111B0(Srca_1, *(unsigned __int16 *)Blockb, *((unsigned __int16 *)Blockb + 1), Srca_5);
      }
      if ( (unsigned __int8)__sub_405840_byte_44339C[v52] != __sub_405840_n4_5 - 1 )
        sub_4081E0(Blockb, Srca_5, v53, v27);
    }
    else if ( __sub_405840_n2 == 1 )
    {
      sub_4108C0((int)Srca_1, *(unsigned __int16 *)Blockb, *((unsigned __int16 *)Blockb + 1));
    }
    else if ( __sub_405840_n2 == 2 )
    {
      v14 = __op_new(0x30ACu);
      if ( v14 )
        Blockb_2 = (void **)sub_40E590(v14, *(unsigned __int16 *)Blockb, *Srca_1);
      else
        Blockb_2 = nullptr;
      sub_40F450(Blockb_2, v15, (int)Srca_1, *(unsigned __int16 *)Blockb, *((unsigned __int16 *)Blockb + 1));
      if ( Blockb_2 )
        sub_402E70(Blockb_2, 1);
    }
    sub_408510(
      (int)Srca_1,
      *(unsigned __int16 *)Blockb * *((unsigned __int16 *)Blockb + 1),
      *(unsigned __int16 *)Blockb);
  }
}

#ifndef BMF_STANDALONE
// __usercall thunk for sub_405840 @ 0x00405840: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_405840()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $56, %esp\n"
    "mov %eax, 8(%esp)\n"
    "mov %edx, 12(%esp)\n"
    "mov %ecx, 16(%esp)\n"
    "fnstsw %ax\n"
    "mov %eax, 20(%esp)\n"
    "movups %xmm1, 24(%esp)\n"
    "movups %xmm3, 40(%esp)\n"
    "lea 40(%esp), %eax\n"
    "push %eax\n"
    "lea 28(%esp), %eax\n"
    "push %eax\n"
    "push 28(%esp)\n"
    "push 28(%esp)\n"
    "push 28(%esp)\n"
    "push 28(%esp)\n"
    "call __sub_405840\n"
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
#undef sub_402E70
#undef sub_407EF0
#undef sub_4081E0
#undef sub_408510
#undef sub_40E590
#undef sub_40E860
#undef sub_40F450
#undef sub_4108C0
#undef sub_410AC0
#undef sub_4111B0
#undef sub_415380
#undef sub_434980
