// sub_402BD0 @ 0x00402BD0 — __usercall
// Extracted from BMF.cpp:2251-2460 by extract.py per incdec.md.

typedef size_t t_sub_402BD0_ElementCount;
static t_sub_402BD0_ElementCount& __sub_402BD0_ElementCount = *(t_sub_402BD0_ElementCount*)0x00441054;
typedef int t_sub_402BD0_dword_441058;
static t_sub_402BD0_dword_441058& __sub_402BD0_dword_441058 = *(t_sub_402BD0_dword_441058*)0x00441058;
typedef int t_sub_402BD0_dword_44105C;
static t_sub_402BD0_dword_44105C& __sub_402BD0_dword_44105C = *(t_sub_402BD0_dword_44105C*)0x0044105C;
typedef int t_sub_402BD0_dword_442BA8;
static t_sub_402BD0_dword_442BA8& __sub_402BD0_dword_442BA8 = *(t_sub_402BD0_dword_442BA8*)0x00442BA8;
typedef int t_sub_402BD0_dword_442BAC;
static t_sub_402BD0_dword_442BAC& __sub_402BD0_dword_442BAC = *(t_sub_402BD0_dword_442BAC*)0x00442BAC;
typedef int t_sub_402BD0_n0xFFFF;
static t_sub_402BD0_n0xFFFF& __sub_402BD0_n0xFFFF = *(t_sub_402BD0_n0xFFFF*)0x00441064;
typedef int t_sub_402BD0_n4_6;
static t_sub_402BD0_n4_6& __sub_402BD0_n4_6 = *(t_sub_402BD0_n4_6*)0x00441060;

#define exit_402E40 __exit_402E40

PROBE_DECL(__sub_402BD0)
extern "C" __attribute__((visibility("hidden"))) int __sub_402BD0(int result)
{
  PROBE_HIT(__sub_402BD0);
  int n45_1; // edx
  int v2; // edi
  int n45; // ebp
  int v4; // ebx
  int v5; // edx
  int v6; // eax
  int v7; // esi
  int v8; // ebx
  int v9; // edx
  int v10; // eax
  int v11; // esi
  int v12; // ebx
  int v13; // edx
  int __sub_402BD0_n0xFFFF; // eax
  int v15; // esi
  int n0xFFFF_1; // ebx
  int v17; // edx
  size_t __sub_402BD0_ElementCount; // eax
  int v19; // esi
  int ElementCount_1; // ebx
  int v21; // edx
  int n4; // eax
  int v23; // esi
  int n4_1; // ebx
  char v25; // al

  n45_1 = *(char *)(result + 1);
  __sub_402BD0_dword_442BAC = 1;
  if ( n45_1 )
  {
    v2 = result;
    n45 = n45_1;
    v4 = result + 1;
    while ( 2 )
    {
      switch ( toupper(n45) )
      {
        case '-':
          __sub_402BD0_dword_442BAC = 0;
          n45 = *(char *)++v4;
          goto LABEL_34;
        case '.':
        case '/':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case ':':
        case ';':
        case '<':
        case '=':
        case '>':
        case '?':
        case '@':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'I':
        case 'J':
        case 'K':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
          v25 = v2;
          goto LABEL_32;
        case 'A':
          n45 = *(char *)++v4;
          if ( n45 == 45 )
          {
            __sub_402BD0_dword_442BA8 = 0;
            n45 = *(char *)++v4;
          }
          else
          {
            __sub_402BD0_dword_442BA8 = 1;
          }
          goto LABEL_34;
        case 'B':
          n45 = *(char *)++v4;
          v21 = isdigit(n45);
          n4 = 0;
          if ( v21 )
          {
            v23 = v4;
            n4_1 = 0;
            do
            {
              n4_1 = n45 + 10 * n4_1 - 48;
              n45 = *(char *)++v23;
            }
            while ( isdigit(n45) );
            n4 = n4_1;
            v4 = v23;
          }
          __sub_402BD0_n4_6 = n4;
          goto LABEL_34;
        case 'H':
          n45 = *(char *)++v4;
          v17 = isdigit(n45);
          __sub_402BD0_ElementCount = 0;
          if ( v17 )
          {
            v19 = v4;
            ElementCount_1 = 0;
            do
            {
              ElementCount_1 = n45 + 10 * ElementCount_1 - 48;
              n45 = *(char *)++v19;
            }
            while ( isdigit(n45) );
            __sub_402BD0_ElementCount = ElementCount_1;
            v4 = v19;
          }
          ::__sub_402BD0_ElementCount = __sub_402BD0_ElementCount;
          goto LABEL_34;
        case 'L':
          n45 = *(char *)++v4;
          v13 = isdigit(n45);
          __sub_402BD0_n0xFFFF = 0;
          if ( v13 )
          {
            v15 = v4;
            n0xFFFF_1 = 0;
            do
            {
              n0xFFFF_1 = n45 + 10 * n0xFFFF_1 - 48;
              n45 = *(char *)++v15;
            }
            while ( isdigit(n45) );
            __sub_402BD0_n0xFFFF = n0xFFFF_1;
            v4 = v15;
          }
          ::__sub_402BD0_n0xFFFF = __sub_402BD0_n0xFFFF;
          goto LABEL_34;
        case 'X':
          n45 = *(char *)++v4;
          v9 = isdigit(n45);
          v10 = 0;
          if ( v9 )
          {
            v11 = v4;
            v12 = 0;
            do
            {
              v12 = n45 + 10 * v12 - 48;
              n45 = *(char *)++v11;
            }
            while ( isdigit(n45) );
            v10 = v12;
            v4 = v11;
          }
          __sub_402BD0_dword_441058 = v10;
          goto LABEL_34;
        case 'Y':
          n45 = *(char *)++v4;
          v5 = isdigit(n45);
          v6 = 0;
          if ( v5 )
          {
            v7 = v4;
            v8 = 0;
            do
            {
              v8 = n45 + 10 * v8 - 48;
              n45 = *(char *)++v7;
            }
            while ( isdigit(n45) );
            v6 = v8;
            v4 = v7;
          }
          __sub_402BD0_dword_44105C = v6;
LABEL_34:
          if ( n45 )
            continue;
          result = v2;
          break;
        default:
          v25 = v2;
LABEL_32:
          exit_402E40(2, (const char *)(v25 - 1));
      }
      break;
    }
  }
  if ( !__sub_402BD0_dword_441058 || !__sub_402BD0_dword_44105C || __sub_402BD0_n4_6 <= 0 || __sub_402BD0_n4_6 > 4 || ::__sub_402BD0_n0xFFFF <= 0 || ::__sub_402BD0_n0xFFFF > 0xFFFF )
    exit_402E40(2, (const char *)(result - 1));
  return result;
}

#ifndef BMF_STANDALONE
// __usercall thunk for sub_402BD0 @ 0x00402BD0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_402BD0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $28, %esp\n"
    "mov %eax, 12(%esp)\n"
    "push 12(%esp)\n"
    "call __sub_402BD0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}
#endif

#undef exit_402E40
