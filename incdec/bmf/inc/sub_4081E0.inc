// sub_4081E0 @ 0x004081E0 — __usercall
// Extracted from BMF.c:6624-6812 by extract.py per incdec.md.

typedef unsigned char t_sub_4081E0_byte_44339C[0x10000];
static t_sub_4081E0_byte_44339C& __sub_4081E0_byte_44339C = *(t_sub_4081E0_byte_44339C*)0x0044339C;
typedef unsigned char t_sub_4081E0_byte_44339D[0x10000];
static t_sub_4081E0_byte_44339D& __sub_4081E0_byte_44339D = *(t_sub_4081E0_byte_44339D*)0x0044339D;
typedef unsigned char t_sub_4081E0_byte_44339E[0x10000];
static t_sub_4081E0_byte_44339E& __sub_4081E0_byte_44339E = *(t_sub_4081E0_byte_44339E*)0x0044339E;
typedef unsigned char t_sub_4081E0_byte_44339F[0x10000];
static t_sub_4081E0_byte_44339F& __sub_4081E0_byte_44339F = *(t_sub_4081E0_byte_44339F*)0x0044339F;
typedef unsigned char t_sub_4081E0_byte_4433AD[16];
static t_sub_4081E0_byte_4433AD& __sub_4081E0_byte_4433AD = *(t_sub_4081E0_byte_4433AD*)0x004433AD;
typedef int t_sub_4081E0_dword_4433A0[0x10000];
static t_sub_4081E0_dword_4433A0& __sub_4081E0_dword_4433A0 = *(t_sub_4081E0_dword_4433A0*)0x004433A0;
typedef int t_sub_4081E0_dword_4433A4[0x10000];
static t_sub_4081E0_dword_4433A4& __sub_4081E0_dword_4433A4 = *(t_sub_4081E0_dword_4433A4*)0x004433A4;
typedef int t_sub_4081E0_dword_4433A8[0x10000];
static t_sub_4081E0_dword_4433A8& __sub_4081E0_dword_4433A8 = *(t_sub_4081E0_dword_4433A8*)0x004433A8;
typedef int t_sub_4081E0_n4_5;
static t_sub_4081E0_n4_5& __sub_4081E0_n4_5 = *(t_sub_4081E0_n4_5*)0x00443394;

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980

PROBE_DECL(__sub_4081E0)
extern "C" __attribute__((visibility("hidden"))) char * __sub_4081E0(char *p_i, char *Src, int a3, char a4)
{
  PROBE_HIT(__sub_4081E0);
  int v4; // ebp
  char *Src_5; // ebx
  unsigned int v6; // ecx
  int n6_2; // ebp
  int v8; // ebx
  int n6_1; // ebp
  int v10; // ebx
  int Size; // ebx
  int n4; // ebp
  unsigned int Src_1; // esi
  int Size_2; // edi
  int v15; // esi
  int Size_1; // edi
  int v17; // esi
  int v18; // ecx
  _BYTE *Src_4; // ebp
  int v20; // eax
  int v21; // ecx
  _BYTE *Src_3; // ebp
  int v23; // eax
  int n2; // [esp+0h] [ebp-34h]
  char *v25; // [esp+0h] [ebp-34h]
  int v26; // [esp+0h] [ebp-34h]
  int v27; // [esp+0h] [ebp-34h]
  unsigned int Src_2; // [esp+4h] [ebp-30h]
  int v29; // [esp+8h] [ebp-2Ch]
  int v30; // [esp+Ch] [ebp-28h]
  int v31; // [esp+10h] [ebp-24h]
  int v32; // [esp+14h] [ebp-20h]
  int n4_1; // [esp+18h] [ebp-1Ch]
  int v34; // [esp+1Ch] [ebp-18h]
  int n6; // [esp+20h] [ebp-14h]

  if ( (__sub_4081E0_byte_44339E[16 * a3] & 8) == 0 )
  {
    Size = *(unsigned __int16 *)p_i * *((unsigned __int16 *)p_i + 1);
    n4 = __sub_4081E0_n4_5;
    Src_1 = (unsigned int)&p_i[a3 + 16];
    if ( __sub_4081E0_n4_5 == 1 )
      return sub_434980(&p_i[a3 + 16],Src,Size);
    p_i += a3;
    if ( Size <= 6
      || __sub_4081E0_n4_5 <= 0
      || (Src_1 <= (unsigned int)Src || Size > Src_1 - (unsigned int)Src)
      && (__sub_4081E0_n4_5 > 1 || (unsigned int)Src <= Src_1 || (unsigned int)&Src[-Src_1] < Size * __sub_4081E0_n4_5) )
    {
      Size_1 = 0;
      v17 = 0;
      do
      {
        p_i[v17 + 16] = Src[Size_1];
        v17 += n4;
        ++Size_1;
      }
      while ( Size_1 < Size );
    }
    else
    {
      Size_2 = 0;
      v15 = 0;
      do
      {
        p_i[v15 + 16] = Src[Size_2];
        v15 += n4;
        ++Size_2;
      }
      while ( Size_2 < Size );
    }
    return p_i;
  }
  n4_1 = __sub_4081E0_n4_5;
  n6 = *(unsigned __int16 *)p_i * *((unsigned __int16 *)p_i + 1);
  v29 = (unsigned __int8)__sub_4081E0_byte_44339D[0] - a3;
  v31 = (unsigned __int8)__sub_4081E0_byte_4433AD[0] - a3;
  n2 = (unsigned __int8)__sub_4081E0_byte_44339C[16 * a3];
  v34 = (unsigned __int8)__sub_4081E0_byte_44339F[16 * a3];
  Src_2 = (unsigned int)&p_i[a3 + 16];
  v4 = __sub_4081E0_dword_4433A4[4 * a3];
  v32 = __sub_4081E0_dword_4433A0[4 * a3];
  v30 = __sub_4081E0_dword_4433A8[4 * a3];
  if ( n2 != 2 || v32 + v4 != 128 )
    goto LABEL_3;
  if ( !v4 )
    goto LABEL_4;
  if ( v32 )
  {
LABEL_3:
    if ( __sub_4081E0_byte_44339C[16 * a3] != 1 )
    {
      if ( n2 == 2 )
      {
        v21 = *(unsigned __int16 *)p_i * *((unsigned __int16 *)p_i + 1);
        v27 = v4;
        Src_3 = (_BYTE *)Src_2;
        do
        {
          v23 = v34 + (unsigned __int8)*Src++;
          p_i = (char *)(((v32 * (unsigned __int8)Src_3[v29] + v27 * (unsigned int)(unsigned __int8)Src_3[v31] + 40) >> 7)
                       + v23);
          *Src_3 = (_BYTE)p_i;
          Src_3 += n4_1;
          --v21;
        }
        while ( v21 );
      }
      else if ( n2 == 3 )
      {
        v18 = *(unsigned __int16 *)p_i * *((unsigned __int16 *)p_i + 1);
        v26 = v4;
        Src_4 = (_BYTE *)Src_2;
        do
        {
          v20 = v34 + (unsigned __int8)*Src++;
          p_i = (char *)(((v26 * (unsigned __int8)*(Src_4 - 2)
                         + v32 * (unsigned __int8)*(Src_4 - 3)
                         + v30 * (unsigned int)(unsigned __int8)*(Src_4 - 1)
                         + 63) >> 7)
                       + v20);
          *Src_4 = (_BYTE)p_i;
          Src_4 += n4_1;
          --v18;
        }
        while ( v18 );
      }
      return p_i;
    }
    goto LABEL_4;
  }
  v29 = (unsigned __int8)__sub_4081E0_byte_4433AD[0] - a3;
LABEL_4:
  p_i += a3;
  v25 = &p_i[v29];
  if ( n6 <= 6 )
    goto LABEL_25;
  Src_5 = &p_i[v29 + 16];
  if ( __sub_4081E0_n4_5 <= 0 )
  {
    if ( __sub_4081E0_n4_5 >= 0 )
      goto LABEL_25;
    if ( (unsigned int)Src_5 >= Src_2 || (v6 = n6 * __sub_4081E0_n4_5, Src_2 - (unsigned int)Src_5 <= -(n6 * __sub_4081E0_n4_5)) )
    {
      if ( (unsigned int)Src_5 <= Src_2 )
        goto LABEL_25;
      v6 = n6 * __sub_4081E0_n4_5;
      if ( (unsigned int)&Src_5[-Src_2] <= -(n6 * __sub_4081E0_n4_5) )
        goto LABEL_25;
    }
  }
  else if ( (unsigned int)Src_5 >= Src_2 || (v6 = n6 * __sub_4081E0_n4_5, n6 * __sub_4081E0_n4_5 > Src_2 - (unsigned int)Src_5) )
  {
    if ( (unsigned int)Src_5 <= Src_2 )
      goto LABEL_25;
    v6 = n6 * __sub_4081E0_n4_5;
    if ( (unsigned int)&Src_5[-Src_2] < n6 * __sub_4081E0_n4_5 )
      goto LABEL_25;
  }
  if ( __sub_4081E0_n4_5 <= 0
    || ((unsigned int)Src >= Src_2 || Src_2 - (unsigned int)Src < n6)
    && (__sub_4081E0_n4_5 > 1 || (unsigned int)Src <= Src_2 || (unsigned int)&Src[-Src_2] < v6) )
  {
LABEL_25:
    n6_1 = 0;
    v10 = 0;
    do
    {
      p_i[v10 + 16] = v25[v10 + 16] + v34 + Src[n6_1];
      v10 += n4_1;
      ++n6_1;
    }
    while ( n6_1 < n6 );
    return p_i;
  }
  n6_2 = 0;
  v8 = 0;
  do
  {
    p_i[v8 + 16] = v25[v8 + 16] + v34 + Src[n6_2];
    v8 += n4_1;
    ++n6_2;
  }
  while ( n6_2 < n6 );
  return p_i;
}

// __usercall thunk for sub_4081E0 @ 0x004081E0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_4081E0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $16, %esp\n"
    "mov %eax, 0(%esp)\n"
    "mov %edx, 4(%esp)\n"
    "mov %ecx, 8(%esp)\n"
    "fnstsw %ax\n"
    "mov %eax, 12(%esp)\n"
    "push 12(%esp)\n"
    "push 12(%esp)\n"
    "push 12(%esp)\n"
    "push 12(%esp)\n"
    "call __sub_4081E0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef sub_434980
