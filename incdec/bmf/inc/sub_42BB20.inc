// sub_42BB20 @ 0x0042BB20 — __usercall
// Extracted from BMF.c:36192-36220 by extract.py per incdec.md.

typedef int t_sub_42BB20_dword_44592C;
static t_sub_42BB20_dword_44592C& __sub_42BB20_dword_44592C = *(t_sub_42BB20_dword_44592C*)0x0044592C;

#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0

PROBE_DECL(__sub_42BB20)
extern "C" __attribute__((visibility("hidden"))) int __sub_42BB20(char a1, int a2, int a3, int a4, int a5)
{
  PROBE_HIT(__sub_42BB20);
  unsigned int v5; // ebp
  char *buf; // ebx
  int i_1; // edx
  int n3; // eax
  int i; // edi

  v5 = ((unsigned int)*(unsigned __int16 *)__sub_42BB20_dword_44592C + 7) >> 3;
  buf = (char *)(*(unsigned __int16 *)(__sub_42BB20_dword_44592C + 4) * a4 + __sub_42BB20_dword_44592C + 16);
  sub_4349F0(buf,0,*(unsigned __int16 *)(__sub_42BB20_dword_44592C + 4));
  i_1 = *(unsigned __int16 *)__sub_42BB20_dword_44592C;
  n3 = 3;
  do
  {
    if ( i_1 > 0 )
    {
      for ( i = 0; i < i_1; ++i )
      {
        if ( (*(unsigned __int8 *)(i + a5) & (1 << (n3 & 7))) != 0 )
          buf[i >> 3] |= 0x80u >> (i & 7);
      }
    }
    buf += v5;
  }
  while ( n3-- >= 1 );
  return n3;
}

// __usercall thunk for sub_42BB20 @ 0x0042BB20: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_42BB20()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $28, %esp\n"
    "fnstsw %ax\n"
    "mov %eax, 12(%esp)\n"
    "push 20(%ebp)\n"
    "push 16(%ebp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "push 28(%esp)\n"
    "call __sub_42BB20\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef sub_4349F0
