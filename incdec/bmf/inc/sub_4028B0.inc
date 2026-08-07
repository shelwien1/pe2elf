// sub_4028B0 @ 0x004028B0 — __usercall
// Extracted from BMF.cpp:2067-2248 by extract.py per incdec.md.

typedef char t_sub_4028B0_Destination_;
static t_sub_4028B0_Destination_& __sub_4028B0_Destination_ = *(t_sub_4028B0_Destination_*)0x00442960;
typedef int t_sub_4028B0_dwLowDateTime;
static t_sub_4028B0_dwLowDateTime& __sub_4028B0_dwLowDateTime = *(t_sub_4028B0_dwLowDateTime*)0x00442BB0;

#ifndef __PE_DECL___sub_42C0B0
#define __PE_DECL___sub_42C0B0
typedef __attribute__((thiscall)) int * t_sub_42C0B0(int _this, int a2);
static t_sub_42C0B0& __sub_42C0B0 = *(t_sub_42C0B0*)0x0042C0B0;
#endif
#define sub_42C0B0 __sub_42C0B0
#define exit_402E40 __exit_402E40
static inline FILE1 ** __fwd_sub_4028B0_sub_402DF0(void *a0, char a1) { return __sub_402DF0((FILE1 **)a0, a1); }
#define sub_402DF0 __fwd_sub_4028B0_sub_402DF0
static inline FILE1 ** __fwd_sub_4028B0_sub_402E10(void *a0, char a1) { return __sub_402E10((FILE1 **)a0, a1); }
#define sub_402E10 __fwd_sub_4028B0_sub_402E10
static inline int __fwd_sub_4028B0_sub_402EF0(void *a0, void *a1, int a2) { return __sub_402EF0((_DWORD *)a0, (char *)a1, a2); }
#define sub_402EF0 __fwd_sub_4028B0_sub_402EF0
static inline int __fwd_sub_4028B0_sub_402FE0(int a0, const __m128 &a1, const __m128 &a2, void *a3, void *a4) { return __sub_402FE0(a0, a1, a2, (unsigned __int16 *)a3, (void *)a4); }
#define sub_402FE0 __fwd_sub_4028B0_sub_402FE0
static inline int __fwd_sub_4028B0_sub_429C80(void *a0, int a1, void *a2) { return __sub_429C80((char *)a0, a1, (char *)a2); }
#define sub_429C80 __fwd_sub_4028B0_sub_429C80
static inline int __fwd_sub_4028B0_sub_42BC50(int a0, int a1, char a2, void *a3) { return __sub_42BC50(a0, a1, a2, (char *)a3); }
#define sub_42BC50 __fwd_sub_4028B0_sub_42BC50

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___printf
#define __PE_DECL___printf
typedef int t_printf(const char *, ...);   // _printf
static t_printf& __printf = *(t_printf*)0x0042CBDB;
#endif
#define printf __printf
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

PROBE_DECL(__sub_4028B0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) int __sub_4028B0(char *FileName, int a2, const __m128 &a3__ref, const __m128 &a4__ref)
{
  alignas(16) unsigned char __hexrays_frame[332];   // original frame, ebp-0x13c..ebp+0x0
  char &Format = *(char *)(__hexrays_frame + 0);
  char (&FileNamea)[256] = *(char (*)[256])(__hexrays_frame + 16);
  int &v33 = *(int *)(__hexrays_frame + 272);
  unsigned __int16 * &p_i_2 = *(unsigned __int16 * *)(__hexrays_frame + 276);
  int &v35 = *(int *)(__hexrays_frame + 280);
  int &v36 = *(int *)(__hexrays_frame + 284);
  char * &v37 = *(char * *)(__hexrays_frame + 288);
  int &v38 = *(int *)(__hexrays_frame + 292);
  const char * &FileName_1 = *(const char * *)(__hexrays_frame + 296);
  PROBE_HIT(__sub_4028B0);
  __m128 a3 = a3__ref;
  __m128 a4 = a4__ref;
  void *v5; // eax
  char v6; // fps
  int v7; // eax
  int v8; // ebx
  unsigned __int16 *p_i_3; // edx
  int v10; // esi
  char v11; // al
  const char *v12; // esi
  const char *GIF8; // edi
  int n4; // ecx
  bool v15; // cf
  bool v16; // zf
  char *Destination; // eax
  FILE **v18; // ecx
  char v19; // dl
  int v20; // esi
  int v21; // edi
  int *p_i_1; // eax
  unsigned __int16 *p_i; // ebp
  char v24; // al
  int v25; // ecx
  int v26; // edi
  int v27; // ebx
  int v28; // ebp
  unsigned int v29; // eax

  v5 = __op_new(0x620u);
  if ( !v5 )
    goto LABEL_41;
  v7 = sub_42BC50((int)v5, a2, v6, FileName);
  v8 = v7;
  if ( !v7 )
    goto LABEL_41;
  p_i_3 = *(unsigned __int16 **)(v7 + 8);
  v10 = *(_DWORD *)(v7 + 12);
  v33 = *(_DWORD *)(v7 + 4);
  v11 = *(_BYTE *)(v7 + 16);
  p_i_2 = p_i_3;
  v35 = v10;
  LOBYTE(v36) = v11;
  v12 = (const char *)&v33;
  GIF8 = "GIF8";
  n4 = 4;
  do
  {
    v15 = *v12 < (unsigned int)*GIF8;
    v16 = *v12 == *GIF8;
    if ( *v12 != *GIF8 )
      break;
    ++v12;
    ++GIF8;
    v16 = --n4 == 0;
  }
  while ( n4 );
  if ( (!v15 && !v16) != v15 )
LABEL_41:
    exit_402E40(3, (char)FileName);
  Destination = &__sub_4028B0_Destination_;
  if ( !__sub_4028B0_Destination_ )
    Destination = FileName;
  sub_429C80(Destination, (int)FileNamea, "bmf");
  if ( void *__nb = __op_new(8u) )
    sub_402EF0((_DWORD *)__nb, FileNamea, 0);
  v18 = nullptr;
  if ( !*(_DWORD *)(v8 + 1564) )
  {
    v19 = *(_BYTE *)(v8 + 25);
    v20 = 0;
    if ( (v35 & 0x800000) != 0 )
    {
      v38 = 0;
      FileName_1 = FileName;
      goto LABEL_15;
    }
    v38 = 0;
    FileName_1 = FileName;
    while ( 1 )
    {
      if ( v19 < 0 )
LABEL_15:
        v21 = 1;
      else
        v21 = 0;
      p_i_1 = sub_42C0B0(v8, 1);
      p_i = (unsigned __int16 *)p_i_1;
      if ( !p_i_1 )
        exit_402E40(4, Format);
      if ( v21 )
      {
        v24 = *((_BYTE *)p_i_1 + 10);
      }
      else
      {
        v24 = *((_BYTE *)p_i_1 + 10) ^ 0x80;
        *((_BYTE *)p_i + 10) = v24;
      }
      printf(
        "File %16s, image %dx%dx%d, size - %d, number - %d:",
        FileName_1,
        *p_i,
        p_i[1],
        v24 & 0x3F,
        *((_DWORD *)p_i + 3),
        ++v20);
      v25 = *((unsigned __int8 *)p_i + 10);
      if ( (v25 & 0x80) != 0 )
      {
        if ( (v25 & 0x40) != 0 )
        {
          *((_BYTE *)p_i + 10) = v25 ^ 0x80;
        }
        else
        {
          v37 = (char *)p_i + *((_DWORD *)p_i + 3);
          if ( 1 << (v25 & 31) <= 0 )
          {
LABEL_30:
            *((_BYTE *)p_i + 10) = (v25 | 0x40) ^ 0x80;
          }
          else
          {
            v36 = v25;
            v33 = v20;
            v26 = 0;
            p_i_2 = p_i;
            v35 = v8;
            v27 = 0;
            while ( 1 )
            {
              v28 = 3 * v27;
              if ( (unsigned __int8)v37[3 * v27 + 16] != v26
                || (unsigned __int8)v37[v28 + 17] != v26
                || (unsigned __int8)v37[v28 + 18] != v26 )
              {
                break;
              }
              ++v27;
              v26 += 0x100u >> (v25 & 31);
              if ( v27 >= 1 << (v25 & 31) )
              {
                LOBYTE(v25) = v36;
                v20 = v33;
                p_i = p_i_2;
                v8 = v35;
                goto LABEL_30;
              }
            }
            v20 = v33;
            p_i = p_i_2;
            v8 = v35;
          }
        }
      }
      v29 = sub_402FE0(v38, a3, a4, p_i, __sub_4028B0_dwLowDateTime);
      if ( !v29 )
        exit_402E40(5, (char)FileNamea);
      *(double *)a3.m128_u64 = (double)v29 * 8.0 / (double)(p_i[1] * *p_i);
      printf("%6.3f bpp%s", *(double *)a3.m128_u64, "\r");
      __op_delete(p_i);
      if ( *(_DWORD *)(v8 + 1564) )
        break;
      v19 = *(_BYTE *)(v8 + 25);
    }
    v18 = (FILE **)v38;
  }
  if ( v18 )
    sub_402DF0(v18, 1);
  sub_402E10((FILE **)v8, 1);
  return printf("\n");
}

// __usercall thunk for sub_4028B0 @ 0x004028B0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_4028B0()
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
    "mov %ebx, 4(%esp)\n"
    "movups %xmm1, 16(%esp)\n"
    "movups %xmm3, 32(%esp)\n"
    "lea 32(%esp), %eax\n"
    "push %eax\n"
    "lea 20(%esp), %eax\n"
    "push %eax\n"
    "push 12(%esp)\n"
    "push 12(%esp)\n"
    "call __sub_4028B0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef FILE
#undef printf
#undef exit_402E40
#undef sub_402DF0
#undef sub_402E10
#undef sub_402EF0
#undef sub_402FE0
#undef sub_429C80
#undef sub_42BC50
#undef sub_42C0B0
