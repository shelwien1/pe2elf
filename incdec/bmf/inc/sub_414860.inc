// sub_414860 @ 0x00414860 — __userpurge
// Extracted from BMF.c:18960-19002 by extract.py per incdec.md.

#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#define FILE FILE1

PROBE_DECL(__sub_414860)
extern "C" __attribute__((visibility("hidden"))) unsigned int __sub_414860(int *a1, int a2, int a3, int a4)
{
  PROBE_HIT(__sub_414860);
  char *buf; // eax
  char v6; // fps
  int v7; // ecx
  unsigned int result; // eax
  int v9; // edi
  int v10; // ecx

  *a1 = a3;
  buf = (char *)__op_new(3 * a3);
  a1[5] = (int)buf;
  if ( a4 )
  {
    v7 = *a1;
    a1[2] = 0;
    a1[1] = v7;
    result = 12 * v7;
    a1[3] = 12 * v7;
    a1[4] = 8 * v7;
    if ( v7 )
    {
      result = 0;
      do
      {
        v9 = 3 * result;
        *(_WORD *)(a1[5] + v9) = result++;
        *(_BYTE *)(a1[5] + v9 + 2) = 1;
      }
      while ( result < a1[1] );
    }
  }
  else
  {
    v10 = *a1;
    a1[2] = 2;
    a1[4] = 20 * v10;
    a1[1] = 0;
    a1[3] = 18 * v10;
    return (unsigned int)sub_4349F0(buf,0,3 * v10);
  }
  return result;
}

// __userpurge thunk for sub_414860 @ 0x00414860: reads the register arguments the
// caller passes, calls the moved body as cdecl, and pops 8 bytes of
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_414860()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $16, %esp\n"
    "mov %ecx, 0(%esp)\n"
    "mov %ebx, 4(%esp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "push 12(%esp)\n"
    "push 12(%esp)\n"
    "call __sub_414860\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret $8\n"
  );
}

#undef FILE
#undef sub_4349F0
