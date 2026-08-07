// sub_436BD0 @ 0x00436BD0 — __usercall
// Extracted from BMF.c:41622-41766 by extract.py per incdec.md.

typedef int t_sub_436BD0_Size;
static t_sub_436BD0_Size& __sub_436BD0_Size = *(t_sub_436BD0_Size*)0x00446180;
#define Size __sub_436BD0_Size
typedef int t_sub_436BD0_dword_441DC0[0x10000];
static t_sub_436BD0_dword_441DC0& __sub_436BD0_dword_441DC0 = *(t_sub_436BD0_dword_441DC0*)0x00441DC0;
#define dword_441DC0 __sub_436BD0_dword_441DC0
typedef int t_sub_436BD0_dword_441DC8[0x10000];
static t_sub_436BD0_dword_441DC8& __sub_436BD0_dword_441DC8 = *(t_sub_436BD0_dword_441DC8*)0x00441DC8;
#define dword_441DC8 __sub_436BD0_dword_441DC8
typedef int t_sub_436BD0_dword_441DCC[0x10000];
static t_sub_436BD0_dword_441DCC& __sub_436BD0_dword_441DCC = *(t_sub_436BD0_dword_441DCC*)0x00441DCC;
#define dword_441DCC __sub_436BD0_dword_441DCC
typedef int t_sub_436BD0_dword_441DD0[521];
static t_sub_436BD0_dword_441DD0& __sub_436BD0_dword_441DD0 = *(t_sub_436BD0_dword_441DD0*)0x00441DD0;
#define dword_441DD0 __sub_436BD0_dword_441DD0
typedef int t_sub_436BD0_dword_446184;
static t_sub_436BD0_dword_446184& __sub_436BD0_dword_446184 = *(t_sub_436BD0_dword_446184*)0x00446184;
#define dword_446184 __sub_436BD0_dword_446184
typedef int t_sub_436BD0_n2_2;
static t_sub_436BD0_n2_2& __sub_436BD0_n2_2 = *(t_sub_436BD0_n2_2*)0x004425F4;
#define n2_2 __sub_436BD0_n2_2

PROBE_DECL(__sub_436BD0)
extern "C" __attribute__((visibility("hidden"))) unsigned int __sub_436BD0(int a1)
{
  PROBE_HIT(__sub_436BD0);
  int i; // eax
  unsigned int n2; // ecx
  int j; // eax
  int j_1; // edx
  unsigned int v35; // edx
  int v36; // eax
  int n525; // esi
  int v39; // edi
  _DWORD GenuineIntel[4]; // [esp+10h] [ebp-64h] BYREF
  int _EDX_1; // [esp+20h] [ebp-54h]
  int v42; // [esp+2Ch] [ebp-48h]
  int v43; // [esp+30h] [ebp-44h]
  _DWORD v44[4]; // [esp+34h] [ebp-40h]
  int _EAX_1; // [esp+44h] [ebp-30h]
  int _EBX_1; // [esp+48h] [ebp-2Ch]
  int _ECX_1; // [esp+4Ch] [ebp-28h]
  int _EDX_2; // [esp+50h] [ebp-24h]
  int _EAX_2; // [esp+54h] [ebp-20h]
  int _EBX_2; // [esp+58h] [ebp-1Ch]
  int _ECX_2; // [esp+5Ch] [ebp-18h]
  int _EDX_3; // [esp+60h] [ebp-14h]
  int _EAX_3; // [esp+64h] [ebp-10h]
  int _EBX_3; // [esp+68h] [ebp-Ch]
  int _ECX_3; // [esp+6Ch] [ebp-8h]
  int _EDX_4; // [esp+70h] [ebp-4h]

  v42 = 0;
  strcpy((char *)GenuineIntel, "GenuineIntel");
  for ( i = 0; i < 64; ++i )
    *((_BYTE *)v44 + i) = 0;
  v43 = a1;
  _EAX = 1;
  __asm { cpuid }
  _EDX_1 = _EDX;
  _EAX = 0;
  __asm { cpuid }
  if ( GenuineIntel[0] == _EBX && GenuineIntel[1] == _EDX && GenuineIntel[2] == _ECX )
  {
    v42 = 1;
    if ( (__int16)_EAX >= 2 )
    {
      _EAX = 2;
      __asm { cpuid }
      v44[0] = _EAX;
      v44[1] = _EBX;
      v44[2] = _ECX;
      v44[3] = _EDX;
      if ( (char)_EAX > 1 )
      {
        _EAX = 2;
        __asm { cpuid }
        _EAX_1 = _EAX;
        _EBX_1 = _EBX;
        _ECX_1 = _ECX;
        _EDX_2 = _EDX;
        if ( (char)_EAX > 2 )
        {
          _EAX = 2;
          __asm { cpuid }
          _EAX_2 = _EAX;
          _EBX_2 = _EBX;
          _ECX_2 = _ECX;
          _EDX_3 = _EDX;
          if ( (char)_EAX > 1 )
          {
            _EAX = 2;
            __asm { cpuid }
            if ( (char)_EAX > 1 )
            {
              _EAX_3 = _EAX;
              _EBX_3 = _EBX;
              _ECX_3 = _ECX;
              _EDX_4 = _EDX;
            }
          }
        }
      }
    }
  }
  n2 = 0;
  if ( v42 )
  {
    LOBYTE(v44[0]) = 0;
    LOBYTE(_EAX_1) = 0;
    LOBYTE(_EAX_2) = 0;
    LOBYTE(_EAX_3) = 0;
    for ( j = 3; j < 64; j += 4 )
    {
      if ( (*((_BYTE *)v44 + j) & 0x80) != 0 )
      {
        j_1 = j - 3;
        do
          *((_BYTE *)v44 + j_1++) = 0;
        while ( j_1 <= j );
      }
    }
    v35 = 0;
    v36 = 0;
    while ( *((unsigned __int8 *)v44 + v36) != 255 )
    {
      n525 = 0;
      while ( *((unsigned __int8 *)v44 + v36) != dword_441DC0[n525] )
      {
        n525 += 5;
        if ( n525 >= 525 )
          goto LABEL_24;
      }
      if ( dword_441DC8[n525] > v35 )
      {
        v35 = dword_441DC8[n525];
        v39 = dword_441DCC[n525];
        if ( dword_441DD0[n525] == 1 )
          v39 *= 2;
        dword_446184 = v39;
      }
LABEL_24:
      if ( ++v36 >= 64 )
        goto LABEL_25;
    }
    dword_446184 = 0;
    v35 = 0;
LABEL_25:
    Size = v35 << 10;
    if ( (_EDX_1 & 0x4000000) != 0 )
      n2 = 2;
    else
      n2 = (_EDX_1 & 0x800000u) >> 23;
  }
  else
  {
    Size = 0;
  }
  n2_2 = n2;
  return n2;
}

// __usercall thunk for sub_436BD0 @ 0x00436BD0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_436BD0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $28, %esp\n"
    "mov %ebx, 12(%esp)\n"
    "push 12(%esp)\n"
    "call __sub_436BD0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef Size
#undef dword_441DC0
#undef dword_441DC8
#undef dword_441DCC
#undef dword_441DD0
#undef dword_446184
#undef n2_2
