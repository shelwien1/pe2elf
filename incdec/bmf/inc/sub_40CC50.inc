// sub_40CC50 @ 0x0040CC50 — __usercall
// Extracted from BMF.cpp:10648-10896 by extract.py per incdec.md.

typedef int t_sub_40CC50_dword_443408;
static t_sub_40CC50_dword_443408& __sub_40CC50_dword_443408 = *(t_sub_40CC50_dword_443408*)0x00443408;

#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0

PROBE_DECL(__sub_40CC50)
extern "C" __attribute__((visibility("hidden"))) int __sub_40CC50(int j, _DWORD *a2, char *buf, char a4)
{
  alignas(16) unsigned char __hexrays_frame[192];   // original frame, ebp-0xb0..ebp+0x0
  _BYTE (&v44)[128] = *(_BYTE (*)[128])(__hexrays_frame + 0);
  char * &bufa = *(char * *)(__hexrays_frame + 128);
  int &k_2 = *(int *)(__hexrays_frame + 132);
  _DWORD * &i_1 = *(_DWORD * *)(__hexrays_frame + 136);
  int &v48 = *(int *)(__hexrays_frame + 140);
  int &i_7 = *(int *)(__hexrays_frame + 144);
  unsigned int &j_1 = *(unsigned int *)(__hexrays_frame + 148);
  int &n15_1 = *(int *)(__hexrays_frame + 152);
  int &v52 = *(int *)(__hexrays_frame + 156);
  PROBE_HIT(__sub_40CC50);
  int v5; // ebx
  int v6; // esi
  int result; // eax
  unsigned int j_2; // edi
  int v9; // edx
  int v10; // ecx
  unsigned int k_4; // edx
  int i_3; // ebx
  _DWORD *i_5; // ecx
  unsigned int j_3; // esi
  unsigned int j_4; // ebp
  _DWORD *i_9; // edi
  bool v17; // zf
  _DWORD *i; // edi
  int v19; // ebp
  _DWORD *i_2; // esi
  _DWORD *i_4; // edx
  _DWORD *i_6; // eax
  int v23; // edx
  _BYTE *v24; // edi
  int n15_2; // esi
  int n15; // ebp
  _DWORD *i_8; // ebx
  _BYTE *v28; // edx
  int v29; // eax
  unsigned int k_1; // esi
  unsigned int k; // ecx
  int v32; // ebp
  int v33; // ecx
  int v34; // ecx
  unsigned int k_3; // ebp
  int v36; // ecx
  char *bufa_2; // esi
  int v38; // edi
  char v39; // bl
  char v40; // cl
  int v41; // esi
  char *bufa_1; // ebx
  BOOL v43; // ebp

  bufa = buf;
  j_1 = j;
  v5 = 0;
  v6 = 0;
  if ( j <= 0 )
    goto LABEL_50;
  result = (int)__sub_40CC50_dword_443408;
  j_2 = 0;
  do
  {
    v9 = a2[j_2];
    v10 = 3 * j_2;
    *(_DWORD *)(result + 8 * v10 + 4) = 0;
    *(_DWORD *)(result + 8 * v10) = v9;
    if ( v9 )
    {
      v6 = result + 24 * j_2;
      v9 = 1;
    }
    ++j_2;
    v5 += v9;
  }
  while ( j_2 < j_1 );
  k_4 = 0;
  if ( v5 <= 1 )
  {
LABEL_50:
    result = (int)sub_4349F0(bufa,0,4 * j_1);
    if ( v5 == 1 )
    {
      v41 = v6 - (_DWORD)__sub_40CC50_dword_443408;
      bufa_1 = bufa;
      v43 = *a2 != 0;
      bufa[4 * (v41 / 24) + 2] = 1;
      bufa_1[4 * v43 + 2] = 1;
      return 715827883 * v41;
    }
  }
  else
  {
    i_3 = result + 12336;
    k_2 = (int)j_1 / 2;
    i_1 = (_DWORD *)(result + 12336);
    v52 = result + 24 * j_1;
    while ( 1 )
    {
      i_5 = i_1;
      j_3 = j_1;
      j_4 = 0;
      do
      {
        if ( *(_DWORD *)(result + 24 * j_4) )
        {
          i_9 = (_DWORD *)(result + 24 * j_4);
          i_5[5] = i_9;
          i_9[4] = i_5;
          i_5 = i_9;
          i_9[3] = 0;
          i_9[2] = 0;
        }
        ++j_4;
      }
      while ( j_4 < j_3 );
      i_5[5] = i_3;
      v17 = i_5 == *(_DWORD **)(i_3 + 20);
      *(_DWORD *)(result + 12336) = 0x7FFFFFFF;
      *(_DWORD *)(i_3 + 16) = i_5;
      if ( !v17 )
      {
        i = i_1;
        v48 = result;
        v19 = 0;
        do
        {
          ++v19;
          i_2 = i;
          i_4 = (_DWORD *)i_3;
          for ( i = (_DWORD *)i_3; i_5 != (_DWORD *)i_3; i_5 = (_DWORD *)i_5[4] )
          {
            if ( *i_5 < *i_2 )
            {
              i_2 = i_4;
              if ( *i_5 >= *i_4 )
                i_2 = i_5;
              else
                i_4 = i_5;
            }
          }
          *(_DWORD *)(i_4[5] + 16) = i_4[4];
          *(_DWORD *)(i_4[4] + 20) = i_4[5];
          *(_DWORD *)(i_2[5] + 16) = i_2[4];
          *(_DWORD *)(i_2[4] + 20) = i_2[5];
          i_6 = (_DWORD *)(v52 + 24 * v19);
          *(i_6 - 6) = *i_4 + *i_2;
          i_6 -= 6;
          i_6[2] = i_4;
          i_6[3] = i_2;
          v23 = *(_DWORD *)(i_3 + 20);
          i_6[5] = v23;
          i_6[4] = i_3;
          *(_DWORD *)(v23 + 16) = i_6;
          i_5 = *(_DWORD **)(i_3 + 16);
          *(_DWORD *)(i_3 + 20) = i_6;
        }
        while ( i_5 != i_6 );
        result = v48;
        i_1 = (_DWORD *)i_3;
        k_4 = 0;
      }
      v24 = v44;
      i_7 = i_3;
      n15_2 = 0;
      v48 = result;
      n15 = 0;
      while ( 1 )
      {
        i_8 = (_DWORD *)i_5[2];
        if ( i_8 )
        {
          n15_1 = n15;
          v28 = v24;
          v29 = 0;
          do
          {
            ++n15_2;
            ++v29;
            v24 = &v28[4 * v29];
            *((_DWORD *)v24 - 1) = i_5;
            i_5[1] = n15_2 - 1;
            i_5 = i_8;
            i_8 = (_DWORD *)i_8[2];
          }
          while ( i_8 );
          n15 = n15_1;
          k_4 = 0;
        }
        i_5[1] = n15_2;
        if ( n15_2 >= n15 )
          n15 = n15_2;
        v24 -= 4;
        if ( v24 < v44 )
          break;
        i_5 = *(_DWORD **)(*(_DWORD *)v24 + 12);
        n15_2 = *(_DWORD *)(*(_DWORD *)v24 + 4) + 1;
      }
      i_3 = i_7;
      result = v48;
      if ( n15 <= 15 )
        break;
      if ( k_2 )
      {
        k_1 = k_2;
        for ( k = 0; k < k_1; ++k )
        {
          v32 = 48 * k;
          if ( *(int *)(result + 48 * k + 4) > 15 )
            ++*(_DWORD *)(result + 48 * k);
          if ( *(int *)(result + v32 + 28) > 15 )
            ++*(_DWORD *)(result + v32 + 24);
        }
        k_2 = k_1;
        v33 = 2 * k + 1;
      }
      else
      {
        v33 = 1;
      }
      if ( v33 - 1 < j_1 )
      {
        v34 = 3 * v33;
        if ( *(int *)(result + 8 * v34 - 20) > 15 )
          ++*(_DWORD *)(result + 8 * v34 - 24);
      }
    }
    k_3 = k_2;
    v36 = 1;
    if ( k_2 )
    {
      bufa_2 = bufa;
      do
      {
        v38 = 2 * k_4;
        v39 = *(_BYTE *)(result + 48 * k_4 + 4);
        v40 = *(_BYTE *)(result + 48 * k_4++ + 28);
        bufa_2[4 * v38 + 2] = v39;
        bufa_2[4 * v38 + 6] = v40;
      }
      while ( k_4 < k_3 );
      v36 = 2 * k_4 + 1;
    }
    if ( v36 - 1 < j_1 )
    {
      result = *(unsigned __int8 *)(result + 24 * v36 - 20);
      bufa[4 * v36 - 2] = result;
    }
  }
  return result;
}

#ifndef BMF_STANDALONE
// __usercall thunk for sub_40CC50 @ 0x0040CC50: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_40CC50()
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
    "call __sub_40CC50\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}
#endif

#undef sub_4349F0
