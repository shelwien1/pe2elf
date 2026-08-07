// sub_40BBC0 @ 0x0040BBC0 — __usercall
// Extracted from BMF.c:9677-9816 by extract.py per incdec.md.

typedef int t_sub_40BBC0_Src;
static t_sub_40BBC0_Src& __sub_40BBC0_Src = *(t_sub_40BBC0_Src*)0x00442E70;
typedef int t_sub_40BBC0_dword_442E74;
static t_sub_40BBC0_dword_442E74& __sub_40BBC0_dword_442E74 = *(t_sub_40BBC0_dword_442E74*)0x00442E74;
typedef int t_sub_40BBC0_n14;
static t_sub_40BBC0_n14& __sub_40BBC0_n14 = *(t_sub_40BBC0_n14*)0x00443414;
typedef int t_sub_40BBC0_n24;
static t_sub_40BBC0_n24& __sub_40BBC0_n24 = *(t_sub_40BBC0_n24*)0x00443410;

#ifndef __PE_DECL___sub_411700
#define __PE_DECL___sub_411700
typedef int t_sub_411700(...);
static t_sub_411700& __sub_411700 = *(t_sub_411700*)0x00411700;
#endif
#define sub_411700 __sub_411700
#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980

PROBE_DECL(__sub_40BBC0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) int __sub_40BBC0(int n2, int a2, int a3, char a4, int a5, int a6, int a7, int a8)
{
  PROBE_HIT(__sub_40BBC0);
  int v9; // ebx
  int v10; // edi
  char v11; // fps
  int v12; // edi
  int v13; // edx
  int v14; // ebx
  int v15; // eax
  unsigned int n0x100; // edx
  int v18; // ecx
  __m128i v19; // xmm1
  __m128i v20; // xmm4
  __m128i v21; // xmm5
  __m128i v22; // xmm7
  __m128i si128; // xmm0
  __m128i v24; // xmm3
  __m128i v25; // xmm6
  __m128i v26; // xmm2
  __m128i v27; // xmm0
  __m128i v28; // xmm1
  __m128i v29; // xmm0
  __m128i v30; // xmm3
  int v31; // edx
  int v32; // eax
  char v33; // fps
  char v34; // fps
  int v35; // eax
  int n2_2; // ecx
  _OWORD __sub_40BBC0_Src[64]; // [esp+0h] [ebp-840h] BYREF
  int v38; // [esp+400h] [ebp-440h]
  char v39[16]; // [esp+404h] [ebp-43Ch] BYREF
  _OWORD v40[63]; // [esp+414h] [ebp-42Ch] BYREF
  int v41; // [esp+804h] [ebp-3Ch]
  int v42; // [esp+808h] [ebp-38h]
  int v43; // [esp+80Ch] [ebp-34h]
  int v44; // [esp+810h] [ebp-30h]
  int n2_1; // [esp+814h] [ebp-2Ch]
  int v46; // [esp+818h] [ebp-28h]
  int v47; // [esp+81Ch] [ebp-24h]
  int v48; // [esp+820h] [ebp-20h]
  int v49; // [esp+824h] [ebp-1Ch]
  int v50; // [esp+828h] [ebp-18h]

  v49 = a3;
  v48 = a2;
  v9 = *(&__sub_40BBC0_n14 + n2);
  v50 = *(&__sub_40BBC0_n24 + n2);
  v10 = v50 - 1;
  if ( v50 - 1 == v9 )
    return 0;
  sub_434980((char *)__sub_40BBC0_Src,(&::__sub_40BBC0_Src)[n2],1028);
  sub_434980(v39,(&__sub_40BBC0_dword_442E74)[n2],1028);
  v46 = *(_DWORD *)(v48 + 4 * n2 + 4) + *(_DWORD *)(v48 + 4 * n2);
  v47 = 0;
  if ( v10 > v9 )
  {
    n2_1 = n2;
    v12 = a8 + 4 * v50 - 4;
    v49 += 257 * (4 * v50 - 4);
    v13 = v9;
    v14 = 0;
    do
    {
      ++v14;
      if ( *(_DWORD *)(-4 * v14 + v12 + 4) )
      {
        n0x100 = 0;
        v18 = v49 - 1028 * v14;
        do
        {
          v19 = _mm_loadu_si128((const __m128i *)(v18 + 4 * n0x100 + 1028));
          v20 = _mm_loadu_si128((const __m128i *)(v18 + 4 * n0x100 + 1044));
          v21 = _mm_loadu_si128((const __m128i *)&v40[n0x100 / 4]);
          v22 = _mm_loadu_si128((const __m128i *)(v18 + 4 * n0x100 + 1060));
          si128 = _mm_load_si128((const __m128i *)&__sub_40BBC0_Src[n0x100 / 4]);
          v24 = _mm_load_si128((const __m128i *)&__sub_40BBC0_Src[n0x100 / 4 + 1]);
          v25 = _mm_load_si128((const __m128i *)&__sub_40BBC0_Src[n0x100 / 4 + 2]);
          *(__m128i *)&v39[4 * n0x100] = _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&v39[4 * n0x100]), v19);
          v26 = _mm_loadu_si128((const __m128i *)(v18 + 4 * n0x100 + 1076));
          v27 = _mm_add_epi32(si128, v19);
          v28 = _mm_load_si128((const __m128i *)&__sub_40BBC0_Src[n0x100 / 4 + 3]);
          __sub_40BBC0_Src[n0x100 / 4] = v27;
          v29 = _mm_loadu_si128((const __m128i *)&v40[n0x100 / 4 + 1]);
          __sub_40BBC0_Src[n0x100 / 4 + 1] = _mm_add_epi32(v24, v20);
          v30 = _mm_loadu_si128((const __m128i *)&v40[n0x100 / 4 + 2]);
          v40[n0x100 / 4] = _mm_sub_epi32(v21, v20);
          __sub_40BBC0_Src[n0x100 / 4 + 2] = _mm_add_epi32(v25, v22);
          v40[n0x100 / 4 + 1] = _mm_sub_epi32(v29, v22);
          __sub_40BBC0_Src[n0x100 / 4 + 3] = _mm_add_epi32(v28, v26);
          v40[n0x100 / 4 + 2] = _mm_sub_epi32(v30, v26);
          n0x100 += 16;
        }
        while ( n0x100 < 0x100 );
        v31 = *(_DWORD *)(v18 + 2052);
        v41 -= v31;
        v38 += v31;
        v44 = sub_411700((int)__sub_40BBC0_Src, 257);
        v32 = sub_411700((int)v39, 257);
        v43 = v32;
        v42 = v44 + v32;
        if ( v44 + v32 > v46 + 512 )
          return v47;
        if ( v44 + v32 < v46 )
        {
          sub_434980((&::__sub_40BBC0_Src)[n2_1],(char *)__sub_40BBC0_Src,1028);
          sub_434980((&__sub_40BBC0_dword_442E74)[n2_1],v39,1028);
          v35 = v48;
          n2_2 = n2_1;
          v47 = 1;
          *(_DWORD *)(v48 + 4 * n2_1) = v44;
          *(_DWORD *)(v35 + 4 * n2_2 + 4) = v43;
          v46 = v42;
          v15 = v50 - v14 - 1;
          *(&__sub_40BBC0_n24 + n2_2) = v50 - v14;
          v13 = *(&__sub_40BBC0_n14 + n2_2);
        }
        else
        {
          v13 = *(&__sub_40BBC0_n14 + n2_1);
          v15 = v50 - v14 - 1;
        }
      }
      else
      {
        v15 = v50 - v14 - 1;
      }
    }
    while ( v15 > v13 );
  }
  return v47;
}

// __usercall thunk for sub_40BBC0 @ 0x0040BBC0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_40BBC0()
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
    "push 20(%ebp)\n"
    "push 16(%ebp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "push 28(%esp)\n"
    "push 28(%esp)\n"
    "push 28(%esp)\n"
    "push 28(%esp)\n"
    "call __sub_40BBC0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef sub_411700
#undef sub_434980
