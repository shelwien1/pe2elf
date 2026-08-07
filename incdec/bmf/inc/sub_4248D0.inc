// sub_4248D0 @ 0x004248D0 — __thiscall
// Extracted from BMF.c:30309-30482 by extract.py per incdec.md.

typedef int t_sub_4248D0_dword_439BD8[8];
static t_sub_4248D0_dword_439BD8& __sub_4248D0_dword_439BD8 = *(t_sub_4248D0_dword_439BD8*)0x00439BD8;


PROBE_DECL(__sub_4248D0)
__attribute__((force_align_arg_pointer)) __attribute__((thiscall)) int __sub_4248D0(unsigned __int8 **_this, _DWORD *a2, int a3)
{
  PROBE_HIT(__sub_4248D0);
  unsigned __int8 *v3; // esi
  unsigned __int8 *v4; // ebx
  int v5; // ebp
  int v6; // edx
  int v7; // eax
  unsigned __int8 *v8; // edi
  bool v9; // cc
  unsigned __int8 *v10; // edi
  int v11; // eax
  int v12; // ebp
  int v13; // ebp
  int v14; // edx
  int v15; // eax
  int v16; // eax
  unsigned __int8 *v17; // edx
  int v18; // edx
  bool v19; // zf
  bool v20; // sf
  BOOL v21; // ebx
  BOOL v22; // esi
  int v23; // ebp
  int v24; // ebx
  BOOL v25; // esi
  BOOL v26; // edi
  BOOL v27; // esi
  BOOL v28; // edi
  int v29; // edi
  int result; // eax
  unsigned __int8 *v31; // [esp+0h] [ebp-34h]
  int v32; // [esp+0h] [ebp-34h]
  unsigned __int8 *v33; // [esp+4h] [ebp-30h]
  int v34; // [esp+4h] [ebp-30h]
  int v35; // [esp+4h] [ebp-30h]
  int v36; // [esp+8h] [ebp-2Ch]
  unsigned int v37; // [esp+Ch] [ebp-28h]
  unsigned int v38; // [esp+10h] [ebp-24h]
  int v39; // [esp+14h] [ebp-20h]
  int v40; // [esp+18h] [ebp-1Ch]
  int v41; // [esp+1Ch] [ebp-18h]
  int v42; // [esp+20h] [ebp-14h]

  v3 = *(_this + 50);
  v4 = (unsigned __int8 *)*v3;
  v5 = (int)*(_this + 49);
  v6 = *(unsigned __int8 *)(v5 - 2);
  v7 = *(v3 - 2);
  if ( v6 < (int)v4 )
  {
    if ( v7 >= v6 )
    {
      v10 = &v4[v6 - v7];
      v9 = v7 < (int)v4;
      v4 = (unsigned __int8 *)*(unsigned __int8 *)(v5 - 2);
      if ( v9 )
        v4 = v10;
    }
  }
  else if ( v7 <= v6 )
  {
    v8 = &v4[v6 - v7];
    v9 = v7 <= (int)v4;
    v4 = (unsigned __int8 *)*(unsigned __int8 *)(v5 - 2);
    if ( !v9 )
      v4 = v8;
  }
  *(_this + 2) = v4;
  v33 = *(_this + 51);
  v11 = *(v3 - 1)
      + *(unsigned __int8 *)(v5 - 5)
      + 3 * (v3[3] + v33[1])
      + 6 * *(unsigned __int8 *)(v5 - 1)
      + 4 * (v3[1] + *(unsigned __int8 *)(v5 - 3))
      + 2 * (v33[5] + v3[5] + *(unsigned __int8 *)(v5 - 7));
  if ( a2 )
  {
    if ( a3 )
    {
      v34 = v5;
      v12 = a2[49];
      v36 = v11 + 2 * (*(unsigned __int8 *)(*(_DWORD *)(a3 + 196) - 1) + *(unsigned __int8 *)(v12 - 1));
      *(_this + 28) = (unsigned __int8 *)(*v3
                                       - (_DWORD)v4
                                       + *(unsigned __int8 *)(v12 - 2)
                                       - *(unsigned __int8 *)(a2[50] - 2));
      v13 = a2[49];
      v14 = *(unsigned __int8 *)(v13 - 2);
      v15 = *(unsigned __int8 *)(v13 - 4);
      v5 = v34;
      *(_this + 32) = (unsigned __int8 *)(*(unsigned __int8 *)(v34 - 2) - (_DWORD)v4 + v14 - v15);
      *(_this + 36) = (unsigned __int8 *)(*(unsigned __int8 *)(v34 - 2)
                                       - (_DWORD)v4
                                       + *(unsigned __int8 *)(*(_DWORD *)(a3 + 196) - 2)
                                       - *(unsigned __int8 *)(*(_DWORD *)(a3 + 196) - 4));
      *(_this + 40) = (unsigned __int8 *)(*(unsigned __int8 *)(*(_DWORD *)(a3 + 196) - 2) - *(_DWORD *)(a3 + 8));
      *(_this + 20) = (unsigned __int8 *)(*(unsigned __int8 *)(a2[49] - 2) - a2[2]);
      v37 = (*(unsigned __int8 *)(*(_DWORD *)(a3 + 196) - 1) + (unsigned int)*(unsigned __int8 *)(a2[49] - 1) - 16) >> 31;
    }
    else
    {
      v36 = v3[7] + v11 + 3 * *(unsigned __int8 *)(a2[49] - 1);
      *(_this + 28) = (unsigned __int8 *)(2 * *(unsigned __int8 *)(v5 - 2) - *(unsigned __int8 *)(v5 - 4) - (_DWORD)v4);
      *(_this + 32) = (unsigned __int8 *)(2 * *(unsigned __int8 *)(v5 - 2) - *(unsigned __int8 *)(v5 - 4) - (_DWORD)v4);
      *(_this + 36) = (unsigned __int8 *)(-(int)v4 - *v3 + v3[2] + *(unsigned __int8 *)(v5 - 2));
      *(_this + 40) = (unsigned __int8 *)(*(unsigned __int8 *)(v5 - 2)
                                       - (_DWORD)v4
                                       + *(unsigned __int8 *)(a2[49] - 2)
                                       - *(unsigned __int8 *)(a2[49] - 4));
      *(_this + 20) = (unsigned __int8 *)(*(unsigned __int8 *)(a2[49] - 2) - a2[2]);
      v37 = ((unsigned int)*(unsigned __int8 *)(a2[49] - 1) - 8) >> 31;
    }
  }
  else
  {
    v32 = (int)*(_this + 53);
    v36 = *(unsigned __int8 *)(v32 + 1) + *(v33 - 3) + v3[7] + v11 + *(unsigned __int8 *)(v32 + 5);
    *(_this + 28) = (unsigned __int8 *)(2 * *(unsigned __int8 *)(v5 - 2) - *(unsigned __int8 *)(v5 - 4) - (_DWORD)v4);
    *(_this + 32) = (unsigned __int8 *)(2 * *v3 - *v33 - (_DWORD)v4);
    *(_this + 36) = (unsigned __int8 *)(-(int)v4 - *v3 + v3[2] + *(unsigned __int8 *)(v5 - 2));
    *(_this + 40) = (unsigned __int8 *)(-3 * (*(unsigned __int8 *)(v5 - 4) - *(unsigned __int8 *)(v5 - 2))
                                     + *(unsigned __int8 *)(v5 - 6)
                                     - (_DWORD)v4);
    *(_this + 20) = (unsigned __int8 *)(v3[4] - (_DWORD)v4);
    v37 = *(unsigned __int8 *)(v5 + 1) + *(unsigned __int8 *)(v32 + 1) + (*(_this + 52))[1] + v33[1] + v3[1] == 0;
  }
  v16 = (v36 + 7) >> 4;
  v17 = (unsigned __int8 *)*((unsigned __int8 *)_this + v16 + 216);
  v31 = v17;
  v35 = __sub_4248D0_dword_439BD8[(_DWORD)v17];
  *(_this + 3) = v17;
  *(_this + 4) = &(*(_this + v16 + 438))[*((unsigned __int8 *)_this + (_DWORD)v4 + 728)];
  *(_this + 8) = (unsigned __int8 *)(((unsigned int)(216 - (_DWORD)v4) >> 31) + ((unsigned int)(22 - (_DWORD)v4) >> 31));
  v38 = ((unsigned int)(216 - (_DWORD)v4) >> 31) + ((unsigned int)(22 - (_DWORD)v4) >> 31);
  v18 = (*(v3 - 2) - *v3 >= 0) + (*(v3 - 2) > (int)*v3);
  *(_this + 12) = (unsigned __int8 *)v18;
  v39 = (*(v3 - 2) - *(unsigned __int8 *)(v5 - 2) >= 0) + (*(v3 - 2) > (int)*(unsigned __int8 *)(v5 - 2));
  *(_this + 16) = (unsigned __int8 *)v39;
  v19 = *(_this + 20) == nullptr;
  v20 = (int)*(_this + 20) < 0;
  v40 = (v3[2] - (int)v4 >= -v35) + (v3[2] - (int)v4 > v35);
  *(_this + 24) = (unsigned __int8 *)v40;
  v21 = v35 < (int)*(_this + 28);
  v22 = -v35 <= (int)*(_this + 28);
  v23 = !v20 + (!v20 && !v19);
  *(_this + 20) = (unsigned __int8 *)v23;
  v24 = v22 + v21;
  v19 = *(_this + 32) == nullptr;
  v20 = (int)*(_this + 32) < 0;
  *(_this + 28) = (unsigned __int8 *)v24;
  v25 = !v20 && !v19;
  v26 = !v20;
  v19 = *(_this + 36) == nullptr;
  v20 = (int)*(_this + 36) < 0;
  v41 = v26 + v25;
  *(_this + 32) = (unsigned __int8 *)(v26 + v25);
  v27 = !v20 && !v19;
  v28 = !v20;
  v19 = *(_this + 40) == nullptr;
  v20 = (int)*(_this + 40) < 0;
  v42 = v28 + v27;
  *(_this + 36) = (unsigned __int8 *)(v28 + v27);
  v29 = !v20 + (!v20 && !v19);
  *(_this + 40) = (unsigned __int8 *)v29;
  result = (int)&(*(_this + v29 + 41))[16 * v37
                                    + 8 * (*(_this + (_DWORD)*(_this + 5) + 6) == nullptr)
                                    + (unsigned int)&(*(_this + v41 + 33))[(_DWORD)*(_this + v42 + 37)
                                                                        + (unsigned int)&(*(_this + v40 + 25))[(_DWORD)*(_this + v24 + 29)]
                                                                        + (unsigned int)&(*(_this + v39 + 17))[(_DWORD)*(_this + v23 + 21) + (unsigned int)&(*(_this + v38 + 9))[(_DWORD)*(_this + v18 + 13)]]]
                                    + (_DWORD)v31];
  *(_this + 3) = (unsigned __int8 *)result;
  return result;
}

