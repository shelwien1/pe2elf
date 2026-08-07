// sub_4273F0 @ 0x004273F0 — __usercall
// Extracted from BMF.c:31865-32031 by extract.py per incdec.md.

#define sub_413E60 __sub_413E60
#define sub_414920 __sub_414920
#define sub_4149C0 __sub_4149C0
#define sub_4244A0 __sub_4244A0
#define sub_4248D0 __sub_4248D0
#define sub_4256F0 __sub_4256F0
#define sub_4259F0 __sub_4259F0

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_new
#define __PE_DECL___op_new
typedef void *t_op_new(unsigned int);   // ??2@YAPAXI@Z
static t_op_new& __op_new = *(t_op_new*)0x0042CF0A;
#endif
#define FILE FILE1

PROBE_DECL(__sub_4273F0)
extern "C" __attribute__((visibility("hidden"))) void ** __sub_4273F0(char ArgList, _BYTE *Src, int i, int a4)
{
  PROBE_HIT(__sub_4273F0);
  int *v4; // eax
  int *v5; // ebx
  int v6; // eax
  int v7; // esi
  int v8; // ebp
  int v9; // ecx
  int v10; // edi
  int v11; // edx
  unsigned __int8 *v12; // ebp
  unsigned __int8 *v13; // ecx
  int v14; // edi
  int v15; // esi
  int v16; // edi
  int v17; // esi
  int v18; // edi
  int v19; // esi
  int v20; // edi
  int v21; // esi
  int v22; // edi
  int v23; // esi
  int v24; // edi
  int v25; // esi
  int v26; // edi
  int v27; // esi
  int v28; // edi
  int v29; // edx
  int v30; // esi
  int v31; // edi
  int v32; // esi
  bool v33; // cc
  _BYTE *Src_1; // ebp
  int v35; // edx
  int v36; // ecx
  __int64 v37; // rax
  int v39; // [esp+8h] [ebp-14h]
  int v41; // [esp+10h] [ebp-Ch]

  v4 = (int *)__op_new(0x99D4D8u);
  if ( v4 )
    v5 = sub_4256F0(v4, i, a4, 0);
  else
    v5 = nullptr;
  sub_4149C0(ArgList);
  if ( v5[1] > 0 )
  {
    v6 = 0;
    do
    {
      ++v6;
      *(_WORD *)v5[49] = *(_WORD *)(v5[49] - 2);
      *(_WORD *)(v5[49] + 2) = *(_WORD *)(v5[49] - 4);
      *(_WORD *)(v5[49] + 4) = *(_WORD *)(v5[49] - 6);
      *(_WORD *)(v5[49] + 6) = *(_WORD *)(v5[49] - 8);
      *(_WORD *)(v5[49] + 8) = *(_WORD *)(v5[49] - 10);
      *(_WORD *)(v5[49] + 10) = *(_WORD *)(v5[49] - 12);
      v7 = v5[48];
      v8 = v5[47];
      v9 = v5[46];
      v10 = v5[45];
      v11 = v5[44];
      v5[48] = v8;
      v5[47] = v9;
      v5[46] = v10;
      v5[45] = v11;
      v5[44] = v7;
      v7 += 8;
      v5[49] = v7;
      v11 += 8;
      v5[50] = v11;
      v5[51] = v10 + 8;
      v5[52] = v9 + 8;
      v5[53] = v8 + 8;
      *(_WORD *)(v7 - 8) = *(_WORD *)(v11 + 6);
      *(_WORD *)(v5[49] - 6) = *(_WORD *)(v5[50] + 4);
      *(_WORD *)(v5[49] - 4) = *(_WORD *)(v5[50] + 2);
      *(_WORD *)(v5[49] - 2) = *(_WORD *)v5[50];
      v12 = (unsigned __int8 *)v5[51];
      v13 = (unsigned __int8 *)v5[53];
      v5[5] = 0;
      v5[6] = 0;
      v5[7] = 0;
      v14 = *(v12 - 3);
      v5[6] = v14;
      v15 = *(v12 - 1);
      v5[7] = v15;
      v16 = *(v13 - 3) + v14;
      v5[6] = v16;
      v17 = *(v13 - 1) + v15;
      v5[7] = v17;
      v18 = v12[1] + v16;
      v5[6] = v18;
      v19 = v12[3] + v17;
      v5[7] = v19;
      v20 = v13[1] + v18;
      v5[6] = v20;
      v21 = v13[3] + v19;
      v5[7] = v21;
      v22 = v12[5] + v20;
      v5[6] = v22;
      v23 = v12[7] + v21;
      v5[7] = v23;
      v24 = v13[5] + v22;
      v5[6] = v24;
      v25 = v13[7] + v23;
      v5[7] = v25;
      v26 = v12[9] + v24;
      v5[6] = v26;
      v27 = v12[11] + v25;
      v5[7] = v27;
      v28 = v13[9] + v26;
      v29 = v5[49];
      v5[6] = v28;
      v30 = v13[11] + v27;
      v5[7] = v30;
      v31 = *(unsigned __int8 *)(v29 - 7) + v28;
      v5[6] = v31;
      v32 = *(unsigned __int8 *)(v29 - 5) + v30;
      v5[7] = v32;
      v5[6] = *(unsigned __int8 *)(v29 - 3) + v31;
      v33 = *v5 <= 0;
      v5[7] = *(unsigned __int8 *)(v29 - 1) + v32;
      if ( !v33 )
      {
        Src_1 = Src;
        v39 = v6;
        v41 = 0;
        do
        {
          ++v41;
          sub_4248D0((_DWORD *)v5, nullptr, 0);
          v36 = (unsigned __int8)(*((_BYTE *)v5 + 8)
                                + *((_BYTE *)v5 + (unsigned __int8)sub_413E60(&v5[4 * v5[3] + 950], v35, v5[4]) + 1496));
          *Src_1 = v36;
          v37 = v36 - v5[2];
          *(_BYTE *)v5[49] = v36;
          *(_BYTE *)(v5[49] + 1) = (BYTE4(v37) ^ v37) - BYTE4(v37);
          v5[v5[5] + 6] = v5[v5[5] + 6]
                        + *(unsigned __int8 *)(v5[49] + 1)
                        - *(unsigned __int8 *)(v5[49] - 7)
                        - (*(unsigned __int8 *)(v5[53] - 3)
                         - *(unsigned __int8 *)(v5[53] + 13)
                         + *(unsigned __int8 *)(v5[51] - 3)
                         - *(unsigned __int8 *)(v5[51] + 13));
          LODWORD(v37) = 16 * v5[3];
          v5[5] = v5[5] == 0;
          if ( *(unsigned __int16 *)((char *)v5 + v37 + 3800) < 0x4000u )
            sub_4259F0((int)v5);
          v5[49] += 2;
          ++Src_1;
          v5[50] += 2;
          v5[51] += 2;
          v5[52] += 2;
          v5[53] += 2;
        }
        while ( v41 < *v5 );
        v6 = v39;
        Src = Src_1;
      }
    }
    while ( v6 < v5[1] );
  }
  sub_414920();
  return sub_4244A0((void **)v5, 1);
}

// __usercall thunk for sub_4273F0 @ 0x004273F0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and lets the caller clean the
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_4273F0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $16, %esp\n"
    "mov %esi, 0(%esp)\n"
    "push 16(%ebp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "push 12(%esp)\n"
    "call __sub_4273F0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret\n"
  );
}

#undef FILE
#undef sub_413E60
#undef sub_414920
#undef sub_4149C0
#undef sub_4244A0
#undef sub_4248D0
#undef sub_4256F0
#undef sub_4259F0
