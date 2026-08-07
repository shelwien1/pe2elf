// sub_407460 @ 0x00407460 — __usercall
// Extracted from BMF.cpp:5953-6238 by extract.py per incdec.md.

typedef int t_sub_407460_dword_443384;
static t_sub_407460_dword_443384& __sub_407460_dword_443384 = *(t_sub_407460_dword_443384*)0x00443384;
typedef int t_sub_407460_n4_5;
static t_sub_407460_n4_5& __sub_407460_n4_5 = *(t_sub_407460_n4_5*)0x00443394;

#ifndef __PE_DECL___sub_411700
#define __PE_DECL___sub_411700
typedef int t_sub_411700(int a1, int n2);
static t_sub_411700& __sub_411700 = *(t_sub_411700*)0x00411700;
#endif
#define sub_411700 __sub_411700
#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0

PROBE_DECL(__sub_407460)
extern "C" __attribute__((visibility("hidden"))) int __sub_407460(unsigned __int8 *a1, unsigned __int8 *n2, int a3, char a4, int a5, int a6, int a7, int a8)
{
  alignas(16) unsigned char __hexrays_frame[26712];   // original frame, ebp-0x6848..ebp+0x0
  char (&buf)[4096] = *(char (*)[4096])(__hexrays_frame + 0);
  int (&v72)[1024] = *(int (*)[1024])(__hexrays_frame + 4096);
  int (&v73)[1024] = *(int (*)[1024])(__hexrays_frame + 8192);
  int (&v74)[1024] = *(int (*)[1024])(__hexrays_frame + 12288);
  int (&v75)[1024] = *(int (*)[1024])(__hexrays_frame + 16384);
  int (&v76)[1024] = *(int (*)[1024])(__hexrays_frame + 20480);
  char (&buf_1)[4] = *(char (*)[4])(__hexrays_frame + 24576);
  unsigned int &v78 = *(unsigned int *)(__hexrays_frame + 24580);
  int &v79 = *(int *)(__hexrays_frame + 24584);
  int &v80 = *(int *)(__hexrays_frame + 24588);
  int &v81 = *(int *)(__hexrays_frame + 24592);
  int &v82 = *(int *)(__hexrays_frame + 24596);
  int &v83 = *(int *)(__hexrays_frame + 24600);
  int &n4 = *(int *)(__hexrays_frame + 24604);
  int &v85 = *(int *)(__hexrays_frame + 24608);
  int &v86 = *(int *)(__hexrays_frame + 24612);
  unsigned __int8 * &n2_2 = *(unsigned __int8 * *)(__hexrays_frame + 26624);
  int &v88 = *(int *)(__hexrays_frame + 26628);
  unsigned __int8 * &v89 = *(unsigned __int8 * *)(__hexrays_frame + 26632);
  int &v90 = *(int *)(__hexrays_frame + 26636);
  int &v91 = *(int *)(__hexrays_frame + 26640);
  int &v92 = *(int *)(__hexrays_frame + 26644);
  int &v93 = *(int *)(__hexrays_frame + 26648);
  int &v94 = *(int *)(__hexrays_frame + 26652);
  int &v95 = *(int *)(__hexrays_frame + 26656);
  int &n191_5 = *(int *)(__hexrays_frame + 26660);
  int &n191_2 = *(int *)(__hexrays_frame + 26664);
  unsigned __int8 * &v98 = *(unsigned __int8 * *)(__hexrays_frame + 26668);
  unsigned __int8 * &v99 = *(unsigned __int8 * *)(__hexrays_frame + 26672);
  unsigned __int8 * &n2_1 = *(unsigned __int8 * *)(__hexrays_frame + 26676);
  int &v101 = *(int *)(__hexrays_frame + 26680);
  PROBE_HIT(__sub_407460);
  void *v8; // esp
  int v9; // esi
  int v10; // ebx
  char v11; // fps
  int v12; // esi
  unsigned __int8 *n2_3; // eax
  int v14; // ecx
  unsigned __int8 *v15; // edi
  double v16; // xmm5_8
  double v17; // xmm4_8
  double v18; // xmm6_8
  double v19; // xmm3_8
  double v20; // xmm2_8
  unsigned __int8 *v21; // eax
  int v22; // esi
  int v23; // ecx
  int v24; // ebx
  int v25; // edx
  int v26; // esi
  int v27; // edi
  int v28; // esi
  unsigned __int8 *v29; // ebx
  int v30; // edi
  int v31; // edi
  double v32; // xmm1_8
  double n191_1; // xmm4_8
  double n191_4; // xmm1_8
  int n191; // eax
  int n191_3; // ecx
  int v37; // ecx
  int v38; // esi
  int v39; // eax
  int v40; // edx
  int v41; // edi
  unsigned __int8 *v42; // ebx
  unsigned __int8 *n2_4; // ecx
  unsigned __int8 *v44; // edx
  int v45; // esi
  int v46; // ecx
  int v47; // ebx
  int v48; // esi
  int v49; // ebx
  int v50; // ebx
  int v51; // eax
  int v52; // esi
  int v53; // eax
  int v54; // edi
  int v55; // edi
  int v56; // eax
  bool v57; // cc
  int v58; // eax
  int v59; // ecx
  int v60; // edx
  int n191_6; // edi
  int n191_7; // edx
  int v63; // ecx
  int v64; // edi
  unsigned __int8 *v65; // ebx
  unsigned __int8 *v66; // edx
  bool v67; // zf
  unsigned int v69; // edi
  unsigned int v70; // eax

  v101 = a3;
  n2_1 = n2;
  v99 = a1;
  v8 = alloca(26672);
  v88 = a3;
  n4 = __sub_407460_n4_5;
  v9 = *((unsigned __int16 *)a1 + 2);
  n2_2 = n2;
  v89 = a1;
  v92 = (int)(n2_1 + 1) % 3 - (_DWORD)n2_1;
  v95 = (int)(n2_1 + 2) % 3 - (_DWORD)n2_1;
  v78 = (unsigned int)&v99[*((_DWORD *)v99 + 3) + 16];
  v10 = v92;
  *(_DWORD *)buf_1 = v9;
  sub_4349F0(buf,0,24576);
  v12 = *(_DWORD *)buf_1;
  n2_3 = n2_2;
  v14 = v88;
  v15 = v89;
  v16 = 0;
  v17 = 0.0;
  v18 = 0.0;
  v19 = 0.0;
  v20 = 0.0;
  v90 = 16 * (_DWORD)n2_2;
  *(_BYTE *)(16 * (_DWORD)n2_2 + v88) = 2;
  *(_BYTE *)(v14 + 33) = (_BYTE)n2_3;
  v91 = (int)&n2_3[(_DWORD)v15];
  v21 = &n2_3[(_DWORD)v15 + 16 + v12 + n4];
  if ( (unsigned int)v21 < v78 )
  {
    v92 = v10;
    *(_DWORD *)buf_1 = v12;
    v85 = v10 - v12;
    v83 = v10 - v12 - n4;
    v82 = v10 - n4;
    v86 = v95 - v12;
    v81 = v95 - v12 - n4;
    v80 = v95 - n4;
    v79 = v12 + n4;
    do
    {
      v22 = v95;
      v23 = v21[v83] + v21[v92] - (v21[v85] + v21[v82]);
      v24 = v81;
      ++*(_DWORD *)&buf[4 * v23 + 2048];
      v25 = v21[v24] + v21[v22] - (v21[v86] + v21[v80]);
      v26 = v79;
      v20 = v20 + (double)v23 * (double)v23;
      ++v72[v25 + 512];
      v17 = v17 + (double)v25 * (double)v25;
      v19 = v19 + (double)v23 * (double)v25;
      ++v73[((_WORD)v25 - (_WORD)v23 - 512) & 0x3FF];
      v27 = v21[-v26] + *v21;
      v28 = v21[-n4];
      v29 = &v21[-*(_DWORD *)buf_1];
      v21 += n4;
      v30 = v27 - (*v29 + v28);
      v18 = v18 + (double)v23 * (double)v30;
      ++v74[((_WORD)v30 - (_WORD)v23 - 512) & 0x3FF];
      v16 = v16 + (double)v25 * (double)v30;
      ++v75[((_WORD)v30 - (_WORD)v25 - 512) & 0x3FF];
      v31 = ((_WORD)v30 - (unsigned __int16)((unsigned int)(((v23 + v25) << 6) + 40) >> 7) - 512) & 0x3FF;
      ++v76[v31];
    }
    while ( (unsigned int)v21 < v78 );
    v10 = v92;
  }
  v32 = 128.0 / (0.1 - v19 * v19 + v20 * v17);
  n191_1 = (v17 * v18 - v19 * v16) * v32;
  n191_4 = v32 * (v20 * v16 - v19 * v18);
  n191 = (int)n191_1;
  if ( (int)n191_1 >= 191 )
    n191 = 191;
  if ( n191 < -64 )
    n191 = -64;
  n191_2 = n191;
  n191_3 = (int)n191_4;
  if ( (int)n191_4 >= 191 )
    n191_3 = 191;
  if ( n191_3 < -64 )
    n191_3 = -64;
  n191_5 = n191_3;
  sub_4349F0(buf_1,0,2048);
  v37 = *((unsigned __int16 *)v89 + 2);
  v38 = (*((unsigned __int16 *)v89 + 1) - 1) * *(unsigned __int16 *)v89;
  v92 = v10;
  v94 = v38 - 1;
  v93 = -v37;
  v39 = -__sub_407460_n4_5;
  v40 = v91 - (-v37 - __sub_407460_n4_5);
  v101 = -v37 - __sub_407460_n4_5;
  v99 = (unsigned __int8 *)(v40 + 16);
  v41 = v10 + v40 + 16;
  v42 = (unsigned __int8 *)(v40 + 16);
  v98 = (unsigned __int8 *)v41;
  n2_1 = (unsigned __int8 *)(v95 + v40 + 16);
  n2_4 = n2_1;
  v44 = (unsigned __int8 *)v41;
  do
  {
    v45 = v42[v101];
    v98 = v44;
    v99 = v42;
    n2_1 = n2_4;
    v46 = v45 + *v42 - v42[v93] - v42[v39];
    v47 = *v44;
    v91 = v46;
    v48 = v94;
    n2_4 = &n2_1[-v39];
    v49 = ((_WORD)v91
         - (unsigned __int16)((n191_2 * (v44[v101] + v47 - v44[v93] - v44[v39])
                             + n191_5 * (n2_1[v101] + *n2_1 - n2_1[v93] - (unsigned int)n2_1[v39])
                             + 40) >> 7)
         - 256)
        & 0x1FF;
    v44 -= v39;
    ++*(_DWORD *)&buf_1[4 * v49];
    v42 = &v99[-v39];
    v94 = v48 - 1;
  }
  while ( v48 != 1 );
  v50 = v92;
  v51 = sub_411700((int)buf_1, 512);
  v52 = 16 * (_DWORD)n2_2;
  *(_DWORD *)(a8 + 16 * (_DWORD)n2_2) = v51;
  *(_DWORD *)(a8 + v52 + 4) = sub_411700((int)v74, 1024);
  *(_DWORD *)(a8 + v52 + 8) = sub_411700((int)v75, 1024);
  *(_DWORD *)(a8 + v52 + 12) = sub_411700((int)v76, 1024);
  v91 = sub_411700((int)buf, 1024);
  v92 = sub_411700((int)v72, 1024);
  v53 = sub_411700((int)v73, 1024);
  v94 = v53;
  v54 = v53;
  if ( v91 < v53 )
    v54 = v91;
  if ( v92 < v53 )
    v53 = v92;
  v55 = v92 + v54;
  v56 = v91 + v53;
  v57 = v55 < v56;
  v93 = v56;
  v58 = v94;
  if ( v57 )
  {
    v93 = v55;
    v59 = v50;
    v50 = v95;
    v91 = v92;
    v95 = v59;
    v60 = *(_DWORD *)(a8 + v52 + 4);
    *(_DWORD *)(a8 + v52 + 4) = *(_DWORD *)(a8 + v52 + 8);
    n191_6 = n191_5;
    *(_DWORD *)(a8 + v52 + 8) = v60;
    n191_7 = n191_2;
    n191_2 = n191_6;
    n191_5 = n191_7;
  }
  v63 = v90;
  v64 = v88;
  *(_DWORD *)(v90 + v88 + 4) = n191_2;
  *(_DWORD *)(v63 + v64 + 8) = n191_5;
  v65 = &n2_2[v50];
  v66 = &n2_2[v95];
  *(_BYTE *)(16 * (_DWORD)v65 + v64) = 0;
  *(_BYTE *)(v64 + 1) = (_BYTE)v65;
  v67 = __sub_407460_dword_443384 == 0;
  *(_BYTE *)(16 * (_DWORD)v66 + v64) = 1;
  *(_BYTE *)(v64 + 17) = (_BYTE)v66;
  if ( !v67 && *((_DWORD *)v89 + 3) > 0x1000000u )
    return v91 + v58 + *(_DWORD *)(a8 + v52);
  v69 = *(_DWORD *)(a8 + v52);
  v70 = *(_DWORD *)(a8 + v52 + 8);
  if ( v69 >= *(_DWORD *)(a8 + v52 + 4) )
    v69 = *(_DWORD *)(a8 + v52 + 4);
  if ( v70 >= *(_DWORD *)(a8 + v52 + 12) )
    v70 = *(_DWORD *)(a8 + v52 + 12);
  if ( v69 < v70 )
    v70 = v69;
  return v93 + v70;
}

// __usercall thunk for sub_407460 @ 0x00407460: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_407460()
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
    "call __sub_407460\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef sub_411700
#undef sub_4349F0
