// sub_407B30 @ 0x00407B30 — __usercall
// Extracted from BMF.c:6241-6440 by extract.py per incdec.md.

typedef int t_sub_407B30_Buffer;
static t_sub_407B30_Buffer& __sub_407B30_Buffer = *(t_sub_407B30_Buffer*)0x0044337C;
typedef int t_sub_407B30_buf;
static t_sub_407B30_buf& __sub_407B30_buf = *(t_sub_407B30_buf*)0x00443380;
typedef unsigned char t_sub_407B30_byte_44339E[0x10000];
static t_sub_407B30_byte_44339E& __sub_407B30_byte_44339E = *(t_sub_407B30_byte_44339E*)0x0044339E;
typedef int t_sub_407B30_dword_443364;
static t_sub_407B30_dword_443364& __sub_407B30_dword_443364 = *(t_sub_407B30_dword_443364*)0x00443364;
typedef int t_sub_407B30_dword_443384;
static t_sub_407B30_dword_443384& __sub_407B30_dword_443384 = *(t_sub_407B30_dword_443384*)0x00443384;
typedef int t_sub_407B30_n2;
static t_sub_407B30_n2& __sub_407B30_n2 = *(t_sub_407B30_n2*)0x00443360;
typedef int t_sub_407B30_n256_0[0x10000];
static t_sub_407B30_n256_0& __sub_407B30_n256_0 = *(t_sub_407B30_n256_0*)0x00443398;
typedef int t_sub_407B30_n256_2[0x10000];
static t_sub_407B30_n256_2& __sub_407B30_n256_2 = *(t_sub_407B30_n256_2*)0x0044338C;
typedef int t_sub_407B30_n4_5;
static t_sub_407B30_n4_5& __sub_407B30_n4_5 = *(t_sub_407B30_n4_5*)0x00443394;

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
static inline char * __fwd_sub_407B30_sub_407EF0(void *a0, void *a1, int a2, char a3) { return __sub_407EF0((char *)a0, (char *)a1, a2, a3); }
#define sub_407EF0 __fwd_sub_407B30_sub_407EF0
static inline char * __fwd_sub_407B30_sub_4081E0(void *a0, void *a1, int a2, char a3) { return __sub_4081E0((char *)a0, (char *)a1, a2, a3); }
#define sub_4081E0 __fwd_sub_407B30_sub_4081E0
#define sub_408510 __sub_408510
#define sub_4108C0 __sub_4108C0
static inline _BYTE * __fwd_sub_407B30_sub_410AC0(void *a0, int a1, int a2, void *a3) { return __sub_410AC0((_BYTE *)a0, a1, a2, (_BYTE *)a3); }
#define sub_410AC0 __fwd_sub_407B30_sub_410AC0
static inline unsigned int __fwd_sub_407B30_sub_4111B0(void *a0, int a1, int a2, void *a3) { return __sub_4111B0((_BYTE *)a0, a1, a2, (_BYTE *)a3); }
#define sub_4111B0 __fwd_sub_407B30_sub_4111B0
static inline void __fwd_sub_407B30_sub_415380(const __m128 &a0, const __m128 &a1, void *a2, void *a3, void *a4) { __sub_415380(a0, a1, (unsigned __int16 *)a2, (unsigned __int8 *)a3, (_BYTE *)a4); }
#define sub_415380 __fwd_sub_407B30_sub_415380

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

PROBE_DECL(__sub_407B30)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) void __sub_407B30(unsigned __int16 *p_i, int a2, char a3, const __m128 &a4__ref, const __m128 &a5__ref)
{
  alignas(16) unsigned char __hexrays_frame[76];   // original frame, ebp-0x3c..ebp+0x0
  int &v32 = *(int *)(__hexrays_frame + 0);
  int &v33 = *(int *)(__hexrays_frame + 4);
  signed int &Size = *(signed int *)(__hexrays_frame + 8);
  int &n4 = *(int *)(__hexrays_frame + 12);
  char * &Srca = *(char * *)(__hexrays_frame + 16);
  int &n4_3 = *(int *)(__hexrays_frame + 20);
  int &n4_4 = *(int *)(__hexrays_frame + 20);
  unsigned __int16 * &p_i_1 = *(unsigned __int16 * *)(__hexrays_frame + 24);
  char * &Src = *(char * *)(__hexrays_frame + 28);
  unsigned __int16 * &Srca_3 = *(unsigned __int16 * *)(__hexrays_frame + 32);
  char * &p_ia = *(char * *)(__hexrays_frame + 36);
  char * &Buffer_1 = *(char * *)(__hexrays_frame + 40);
  PROBE_HIT(__sub_407B30);
  __m128 a4 = a4__ref;
  __m128 a5 = a5__ref;
  char *__sub_407B30_Buffer; // ebx
  char *p_ia_1; // edi
  unsigned __int8 *Srca_1; // esi
  char v9; // fps
  char *Src_1; // eax
  char v11; // fps
  char *Src_3; // edx
  int n4_1; // ebx
  int v14; // esi
  int __sub_407B30_n2; // ecx
  int v16; // edi
  int Size_3; // eax
  int n4_2; // edx
  char *Src_2; // ecx
  char *v20; // esi
  int v21; // edi
  int i; // ebx
  int Size_4; // ecx
  int v24; // edi
  char v25; // fps
  unsigned int Srca_2; // edi
  signed int Size_2; // ecx
  int v28; // eax
  signed int Size_1; // ecx
  int v30; // eax
  char v31; // fps

  sub_4349F0(__sub_407B30_buf,0,4096);
  __sub_407B30_Buffer = (char *)::__sub_407B30_Buffer;
  p_ia_1 = (char *)::__sub_407B30_Buffer + 16;
  *((_DWORD *)::__sub_407B30_Buffer + 4) = *(_DWORD *)p_i;
  *((_DWORD *)p_ia_1 + 1) = *((_DWORD *)p_i + 1);
  *((_DWORD *)p_ia_1 + 2) = *((_DWORD *)p_i + 2);
  *((_DWORD *)p_ia_1 + 3) = *((_DWORD *)p_i + 3);
  Srca_1 = (unsigned __int8 *)(p_i + 8);
  sub_434980(__sub_407B30_Buffer + 32,(char *)p_i + 16,*((_DWORD *)p_i + 3));
  Src_1 = (char *)__op_new(*p_i * p_i[1]);
  Src_3 = Src_1;
  if ( __sub_407B30_n4_5 > 0 )
  {
    Src = Src_1;
    Srca_3 = p_i + 8;
    p_ia = p_ia_1;
    Buffer_1 = __sub_407B30_Buffer;
    n4_1 = 0;
    do
    {
      ++n4_1;
      v14 = BYTE1(__sub_407B30_n256_2[4 * n4_1]);
      __sub_407B30_n2 = __sub_407B30_byte_44339E[16 * v14] & 3;
      ::__sub_407B30_n2 = __sub_407B30_n2;
      v16 = (unsigned __int8)(__sub_407B30_byte_44339E[16 * v14] & 4) >> 2;
      __sub_407B30_dword_443364 = v16;
      if ( ((__sub_407B30_byte_44339E[16 * v14] & 8) != 0 || __sub_407B30_n2 || __sub_407B30_n256_0[0]) && (!v16 || !__sub_407B30_dword_443384) )
      {
        sub_407EF0(p_ia, Src, v14, v11);
        if ( ::__sub_407B30_n2 != 2 )
        {
          if ( __sub_407B30_n256_0[0] )
          {
            Srca = (char *)__op_new(p_i[1] * *p_i);
            n4 = __sub_407B30_n4_5;
            Size = *(unsigned __int16 *)p_ia * *((unsigned __int16 *)p_ia + 1);
            if ( __sub_407B30_n4_5 == 1 )
            {
              sub_434980(Srca,&Buffer_1[v14 + 32],Size);
            }
            else
            {
              v33 = (int)&Buffer_1[v14 + 16];
              if ( Size <= 6
                || (Srca_2 = (unsigned int)&Buffer_1[v14 + 32], __sub_407B30_n4_5 <= 0)
                || (__sub_407B30_n4_5 > 1 || Srca_2 >= (unsigned int)Srca || (unsigned int)&Srca[-Srca_2] < Size * __sub_407B30_n4_5)
                && (Srca_2 <= (unsigned int)Srca || Srca_2 - (unsigned int)Srca < Size) )
              {
                v32 = v14;
                Size_1 = 0;
                v30 = 0;
                n4_4 = n4_1;
                p_i_1 = p_i;
                do
                {
                  Srca[Size_1] = *(_BYTE *)(v30 + v33 + 16);
                  v30 += n4;
                  ++Size_1;
                }
                while ( Size_1 < Size );
              }
              else
              {
                v32 = v14;
                Size_2 = 0;
                v28 = 0;
                n4_4 = n4_1;
                p_i_1 = p_i;
                do
                {
                  Srca[Size_2] = *(_BYTE *)(v28 + v33 + 16);
                  v28 += n4;
                  ++Size_2;
                }
                while ( Size_2 < Size );
              }
              v14 = v32;
              n4_1 = n4_4;
              p_i = p_i_1;
            }
            if ( ::__sub_407B30_n2 )
              sub_410AC0(Src, *p_i, p_i[1], Srca);
            else
              sub_4111B0(Src, *p_i, p_i[1], Srca);
            if ( n4_1 != __sub_407B30_n4_5 )
              sub_4081E0(p_ia, Srca, v14, v31);
            __op_delete(Srca);
          }
          else if ( ::__sub_407B30_n2 == 1 )
          {
            sub_4108C0((int)Src, *p_i, p_i[1]);
          }
        }
        Size_3 = *p_i * p_i[1];
        n4_2 = __sub_407B30_n4_5;
        Src_2 = (char *)p_i + v14 + 16;
        if ( __sub_407B30_n4_5 == 1 )
        {
          sub_434980((char *)p_i + v14 + 16,Src,Size_3);
        }
        else
        {
          v20 = (char *)p_i + v14;
          if ( Size_3 <= 6
            || __sub_407B30_n4_5 <= 0
            || (Src_2 <= Src || Size_3 > (unsigned int)(Src_2 - Src))
            && (__sub_407B30_n4_5 > 1 || Src_2 >= Src || Src - Src_2 < (unsigned int)(Size_3 * __sub_407B30_n4_5)) )
          {
            Size_4 = 0;
            v24 = 0;
            do
            {
              v20[v24 + 16] = Src[Size_4];
              v24 += n4_2;
              ++Size_4;
            }
            while ( Size_4 < Size_3 );
          }
          else
          {
            n4_3 = n4_1;
            v21 = 0;
            for ( i = 0; i < Size_3; ++i )
            {
              v20[v21 + 16] = Src[i];
              v21 += n4_2;
            }
            n4_1 = n4_3;
          }
        }
      }
    }
    while ( n4_1 < __sub_407B30_n4_5 );
    Src_3 = Src;
    Srca_1 = (unsigned __int8 *)Srca_3;
  }
  __op_delete(Src_3);
  if ( __sub_407B30_dword_443384 )
  {
    sub_415380(a4, a5, p_i, Srca_1, Srca_1);
  }
  else
  {
    __sub_407B30_dword_443364 = 0;
    ::__sub_407B30_n2 = 0;
    sub_408510((int)Srca_1, *((_DWORD *)p_i + 3), p_i[2]);
  }
}

// __usercall thunk for sub_407B30 @ 0x00407B30: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_407B30()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $60, %esp\n"
    "mov %eax, 12(%esp)\n"
    "mov %ebx, 16(%esp)\n"
    "fnstsw %ax\n"
    "mov %eax, 20(%esp)\n"
    "movups %xmm1, 28(%esp)\n"
    "movups %xmm3, 44(%esp)\n"
    "lea 44(%esp), %eax\n"
    "push %eax\n"
    "lea 32(%esp), %eax\n"
    "push %eax\n"
    "push 28(%esp)\n"
    "push 28(%esp)\n"
    "push 28(%esp)\n"
    "call __sub_407B30\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef FILE
#undef sub_407EF0
#undef sub_4081E0
#undef sub_408510
#undef sub_4108C0
#undef sub_410AC0
#undef sub_4111B0
#undef sub_415380
#undef sub_434980
#undef sub_4349F0
