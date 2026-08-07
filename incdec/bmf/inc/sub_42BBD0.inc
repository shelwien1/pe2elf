// sub_42BBD0 @ 0x0042BBD0 — __cdecl
// Extracted from BMF.cpp:36223-36262 by extract.py per incdec.md.

typedef int t_sub_42BBD0_a1;
static t_sub_42BBD0_a1& __sub_42BBD0_a1 = *(t_sub_42BBD0_a1*)(blob1 + 0x00439BFC - BMF_BLOB_BASE);
typedef int t_sub_42BBD0_dword_44592C;
static t_sub_42BBD0_dword_44592C& __sub_42BBD0_dword_44592C = *(t_sub_42BBD0_dword_44592C*)(blob1 + 0x0044592C - BMF_BLOB_BASE);

#ifndef __PE_DECL___sub_4349F0
#define __PE_DECL___sub_4349F0
typedef void * t_sub_4349F0(void *, int, unsigned int);   // stack arguments only
static t_sub_4349F0& __sub_4349F0 = *(t_sub_4349F0*)0x004349F0;
#endif
#define sub_4349F0 __sub_4349F0

PROBE_DECL(__sub_42BBD0)
BMF_REALIGN void __sub_42BBD0(int a2, int a3, int a4, int a5)
{
  PROBE_HIT(__sub_42BBD0);
  int v5; // esi
  int v6; // ebp
  char *buf; // ebx
  int v8; // ecx
  int v9; // esi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // [esp+0h] [ebp-18h]
  int v14; // [esp+4h] [ebp-14h]

  v5 = *(_BYTE *)(__sub_42BBD0_dword_44592C + 10) & 0x3F;
  v6 = 8 - v5;
  buf = (char *)(*(unsigned __int16 *)(__sub_42BBD0_dword_44592C + 4) * a4 + __sub_42BBD0_dword_44592C + 16);
  sub_4349F0(buf,0,*(unsigned __int16 *)(__sub_42BBD0_dword_44592C + 4));
  if ( *(_WORD *)__sub_42BBD0_dword_44592C )
  {
    v13 = *(unsigned __int16 *)__sub_42BBD0_dword_44592C;
    v8 = 8 - v5;
    v14 = v5;
    v9 = 0;
    do
    {
      v10 = *(unsigned __int8 *)(v9 + a5) << (v8 & 31);
      ++v9;
      *buf |= v10;
      v11 = v8;
      v8 = v6;
      v12 = v11 - v14;
      if ( v12 < 0 )
        ++buf;
      else
        v8 = v12;
    }
    while ( v9 < v13 );
  }
}

#undef sub_4349F0
