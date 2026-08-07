// sub_407EF0 @ 0x00407EF0 — __usercall
// Extracted from BMF.c:6443-6621 by extract.py per incdec.md.

typedef unsigned char t_sub_407EF0_byte_44339C[0x10000];
static t_sub_407EF0_byte_44339C& __sub_407EF0_byte_44339C = *(t_sub_407EF0_byte_44339C*)0x0044339C;
typedef unsigned char t_sub_407EF0_byte_44339D[0x10000];
static t_sub_407EF0_byte_44339D& __sub_407EF0_byte_44339D = *(t_sub_407EF0_byte_44339D*)0x0044339D;
typedef unsigned char t_sub_407EF0_byte_44339E[0x10000];
static t_sub_407EF0_byte_44339E& __sub_407EF0_byte_44339E = *(t_sub_407EF0_byte_44339E*)0x0044339E;
typedef unsigned char t_sub_407EF0_byte_44339F[0x10000];
static t_sub_407EF0_byte_44339F& __sub_407EF0_byte_44339F = *(t_sub_407EF0_byte_44339F*)0x0044339F;
typedef unsigned char t_sub_407EF0_byte_4433AD[16];
static t_sub_407EF0_byte_4433AD& __sub_407EF0_byte_4433AD = *(t_sub_407EF0_byte_4433AD*)0x004433AD;
typedef int t_sub_407EF0_dword_4433A0[0x10000];
static t_sub_407EF0_dword_4433A0& __sub_407EF0_dword_4433A0 = *(t_sub_407EF0_dword_4433A0*)0x004433A0;
typedef int t_sub_407EF0_dword_4433A4[0x10000];
static t_sub_407EF0_dword_4433A4& __sub_407EF0_dword_4433A4 = *(t_sub_407EF0_dword_4433A4*)0x004433A4;
typedef int t_sub_407EF0_dword_4433A8[0x10000];
static t_sub_407EF0_dword_4433A8& __sub_407EF0_dword_4433A8 = *(t_sub_407EF0_dword_4433A8*)0x004433A8;
typedef int t_sub_407EF0_n4_5;
static t_sub_407EF0_n4_5& __sub_407EF0_n4_5 = *(t_sub_407EF0_n4_5*)0x00443394;

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980

PROBE_DECL(__sub_407EF0)
extern "C" __attribute__((visibility("hidden"))) char * __sub_407EF0(char *Blockb, char *Src, int a3, char a4)
{
  PROBE_HIT(__sub_407EF0);
  int v4; // ebp
  unsigned int Src_2; // ebp
  int n6_2; // ebp
  int v7; // ebx
  char v8; // cl
  int n6_1; // ebp
  int v10; // ebx
  char v11; // cl
  int Size; // ebx
  int n4; // ebp
  unsigned int Src_1; // esi
  int Size_1; // edi
  int v16; // esi
  int Size_2; // edi
  int v18; // esi
  int v19; // ecx
  unsigned __int8 *Src_5; // ebp
  int v21; // eax
  int v22; // ebx
  int v23; // edi
  int v24; // ecx
  unsigned __int8 *Src_4; // ebp
  int v26; // eax
  unsigned int v27; // ebx
  int n2; // [esp+0h] [ebp-34h]
  char *v29; // [esp+0h] [ebp-34h]
  int v30; // [esp+0h] [ebp-34h]
  int v31; // [esp+0h] [ebp-34h]
  unsigned int Src_3; // [esp+4h] [ebp-30h]
  int v33; // [esp+8h] [ebp-2Ch]
  int v34; // [esp+Ch] [ebp-28h]
  int v35; // [esp+10h] [ebp-24h]
  int v36; // [esp+14h] [ebp-20h]
  int v37; // [esp+18h] [ebp-1Ch]
  int n4_1; // [esp+1Ch] [ebp-18h]
  int n6; // [esp+20h] [ebp-14h]

  if ( (__sub_407EF0_byte_44339E[16 * a3] & 8) == 0 )
  {
    Size = *(unsigned __int16 *)Blockb * *((unsigned __int16 *)Blockb + 1);
    n4 = __sub_407EF0_n4_5;
    Src_1 = (unsigned int)&Blockb[a3 + 16];
    if ( __sub_407EF0_n4_5 == 1 )
      return sub_434980(Src,&Blockb[a3 + 16],Size);
    Blockb += a3;
    if ( Size > 6 && __sub_407EF0_n4_5 > 0 )
    {
      if ( __sub_407EF0_n4_5 > 1 )
        goto LABEL_30;
      if ( (unsigned int)Src > Src_1 && (unsigned int)&Src[-Src_1] >= Size * __sub_407EF0_n4_5 )
        goto LABEL_31;
      if ( __sub_407EF0_n4_5 > 0 )
      {
LABEL_30:
        if ( Src_1 > (unsigned int)Src && Size <= Src_1 - (unsigned int)Src )
        {
LABEL_31:
          Size_1 = 0;
          v16 = 0;
          do
          {
            Src[Size_1] = Blockb[v16 + 16];
            v16 += n4;
            ++Size_1;
          }
          while ( Size_1 < Size );
          return Blockb;
        }
      }
    }
    Size_2 = 0;
    v18 = 0;
    do
    {
      Src[Size_2] = Blockb[v18 + 16];
      v18 += n4;
      ++Size_2;
    }
    while ( Size_2 < Size );
    return Blockb;
  }
  n4_1 = __sub_407EF0_n4_5;
  n6 = *(unsigned __int16 *)Blockb * *((unsigned __int16 *)Blockb + 1);
  v33 = (unsigned __int8)__sub_407EF0_byte_44339D[0] - a3;
  v35 = (unsigned __int8)__sub_407EF0_byte_4433AD[0] - a3;
  n2 = (unsigned __int8)__sub_407EF0_byte_44339C[16 * a3];
  v37 = (unsigned __int8)__sub_407EF0_byte_44339F[16 * a3];
  Src_3 = (unsigned int)&Blockb[a3 + 16];
  v4 = __sub_407EF0_dword_4433A4[4 * a3];
  v36 = __sub_407EF0_dword_4433A0[4 * a3];
  v34 = __sub_407EF0_dword_4433A8[4 * a3];
  if ( n2 == 2 && v36 + v4 == 128 )
  {
    if ( !v4 )
      goto LABEL_4;
    if ( !v36 )
    {
      v33 = (unsigned __int8)__sub_407EF0_byte_4433AD[0] - a3;
      goto LABEL_4;
    }
  }
  if ( __sub_407EF0_byte_44339C[16 * a3] == 1 )
  {
LABEL_4:
    Blockb += a3;
    v29 = &Blockb[v33];
    if ( n6 <= 6
      || (Src_2 = (unsigned int)&Blockb[v33 + 16], __sub_407EF0_n4_5 <= 0)
      || (__sub_407EF0_n4_5 > 1 || (unsigned int)Src <= Src_2 || (unsigned int)&Src[-Src_2] < n6 * __sub_407EF0_n4_5)
      && (Src_2 <= (unsigned int)Src || Src_2 - (unsigned int)Src < n6)
      || (__sub_407EF0_n4_5 > 1 || (unsigned int)Src <= Src_3 || (unsigned int)&Src[-Src_3] < n6 * __sub_407EF0_n4_5)
      && ((unsigned int)Src >= Src_3 || Src_3 - (unsigned int)Src < n6) )
    {
      n6_1 = 0;
      v10 = 0;
      do
      {
        v11 = Blockb[v10 + 16] - v37 - v29[v10 + 16];
        v10 += n4_1;
        Src[n6_1++] = v11;
      }
      while ( n6_1 < n6 );
    }
    else
    {
      n6_2 = 0;
      v7 = 0;
      do
      {
        v8 = Blockb[v7 + 16] - v37 - v29[v7 + 16];
        v7 += n4_1;
        Src[n6_2++] = v8;
      }
      while ( n6_2 < n6 );
    }
    return Blockb;
  }
  if ( n2 == 2 )
  {
    v24 = *(unsigned __int16 *)Blockb * *((unsigned __int16 *)Blockb + 1);
    v31 = v4;
    Src_4 = (unsigned __int8 *)Src_3;
    do
    {
      v26 = *Src_4 - v37;
      v27 = v36 * Src_4[v33] + v31 * Src_4[v35] + 40;
      Src_4 += n4_1;
      Blockb = (char *)(v26 - (v27 >> 7));
      *Src++ = (char)Blockb;
      --v24;
    }
    while ( v24 );
  }
  else if ( n2 == 3 )
  {
    v19 = *(unsigned __int16 *)Blockb * *((unsigned __int16 *)Blockb + 1);
    v30 = v4;
    Src_5 = (unsigned __int8 *)Src_3;
    do
    {
      v21 = *Src_5 - v37;
      v22 = v30 * *(Src_5 - 2) + v36 * *(Src_5 - 3);
      v23 = v34 * *(Src_5 - 1);
      Src_5 += n4_1;
      Blockb = (char *)(v21 - ((unsigned int)(v22 + v23 + 63) >> 7));
      *Src++ = (char)Blockb;
      --v19;
    }
    while ( v19 );
  }
  return Blockb;
}

// __usercall thunk for sub_407EF0 @ 0x00407EF0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_407EF0()
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
    "call __sub_407EF0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef sub_434980
