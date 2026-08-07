// sub_424550 @ 0x00424550 — __thiscall
// Extracted from BMF.c:30127-30306 by extract.py per incdec.md.

#ifndef __PE_DECL___sub_414F60
#define __PE_DECL___sub_414F60
typedef char * t_sub_414F60();
static t_sub_414F60& __sub_414F60 = *(t_sub_414F60*)0x00414F60;
#endif
#define sub_414F60 __sub_414F60
static inline int __fwd_sub_424550_sub_4135A0(void *a0, int a1, int a2, int a3) { return __sub_4135A0((unsigned __int16 *)a0, a1, a2, a3); }
#define sub_4135A0 __fwd_sub_424550_sub_4135A0
#define sub_414CE0 __sub_414CE0
static inline int __fwd_sub_424550_sub_4248D0(void *a0, void *a1, int a2) { return __sub_4248D0((unsigned __int8 **)a0, (_DWORD *)a1, a2); }
#define sub_4248D0 __fwd_sub_424550_sub_4248D0
#define sub_4259F0 __sub_4259F0

PROBE_DECL(__sub_424550)
__attribute__((thiscall)) void __sub_424550(int _this, _BYTE *a2, _BYTE *a3)
{
  PROBE_HIT(__sub_424550);
  int v4; // eax
  int v5; // esi
  int v6; // ecx
  int v7; // ebp
  int v8; // edi
  int v9; // edx
  unsigned __int8 *v10; // ecx
  unsigned __int8 *v11; // ebp
  int v12; // edi
  int v13; // esi
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
  int v27; // edx
  int v28; // esi
  int v29; // edi
  int v30; // esi
  bool v31; // cc
  _BYTE *v32; // ebp
  char v33; // dl
  int v34; // esi
  char v35; // dl
  int n5; // eax
  int n16; // ecx
  int v38; // ecx
  __int64 v39; // rax
  int v40; // [esp+4h] [ebp-24h]
  int v42; // [esp+Ch] [ebp-1Ch]

  sub_414F60();
  if ( *(int *)(_this + 4) > 0 )
  {
    v4 = 0;
    do
    {
      ++v4;
      **(_WORD **)(_this + 196) = *(_WORD *)(*(_DWORD *)(_this + 196) - 2);
      *(_WORD *)(*(_DWORD *)(_this + 196) + 2) = *(_WORD *)(*(_DWORD *)(_this + 196) - 4);
      *(_WORD *)(*(_DWORD *)(_this + 196) + 4) = *(_WORD *)(*(_DWORD *)(_this + 196) - 6);
      *(_WORD *)(*(_DWORD *)(_this + 196) + 6) = *(_WORD *)(*(_DWORD *)(_this + 196) - 8);
      *(_WORD *)(*(_DWORD *)(_this + 196) + 8) = *(_WORD *)(*(_DWORD *)(_this + 196) - 10);
      *(_WORD *)(*(_DWORD *)(_this + 196) + 10) = *(_WORD *)(*(_DWORD *)(_this + 196) - 12);
      v5 = *(_DWORD *)(_this + 192);
      v6 = *(_DWORD *)(_this + 188);
      v7 = *(_DWORD *)(_this + 184);
      v8 = *(_DWORD *)(_this + 180);
      v9 = *(_DWORD *)(_this + 176);
      *(_DWORD *)(_this + 192) = v6;
      *(_DWORD *)(_this + 188) = v7;
      *(_DWORD *)(_this + 184) = v8;
      *(_DWORD *)(_this + 180) = v9;
      *(_DWORD *)(_this + 176) = v5;
      v5 += 8;
      *(_DWORD *)(_this + 196) = v5;
      v9 += 8;
      *(_DWORD *)(_this + 200) = v9;
      *(_DWORD *)(_this + 204) = v8 + 8;
      *(_DWORD *)(_this + 208) = v7 + 8;
      *(_DWORD *)(_this + 212) = v6 + 8;
      *(_WORD *)(v5 - 8) = *(_WORD *)(v9 + 6);
      *(_WORD *)(*(_DWORD *)(_this + 196) - 6) = *(_WORD *)(*(_DWORD *)(_this + 200) + 4);
      *(_WORD *)(*(_DWORD *)(_this + 196) - 4) = *(_WORD *)(*(_DWORD *)(_this + 200) + 2);
      *(_WORD *)(*(_DWORD *)(_this + 196) - 2) = **(_WORD **)(_this + 200);
      v10 = *(unsigned __int8 **)(_this + 204);
      v11 = *(unsigned __int8 **)(_this + 212);
      *(_DWORD *)(_this + 20) = 0;
      *(_DWORD *)(_this + 24) = 0;
      *(_DWORD *)(_this + 28) = 0;
      v12 = *(v10 - 3);
      *(_DWORD *)(_this + 24) = v12;
      v13 = *(v10 - 1);
      *(_DWORD *)(_this + 28) = v13;
      v14 = *(v11 - 3) + v12;
      *(_DWORD *)(_this + 24) = v14;
      v15 = *(v11 - 1) + v13;
      *(_DWORD *)(_this + 28) = v15;
      v16 = v10[1] + v14;
      *(_DWORD *)(_this + 24) = v16;
      v17 = v10[3] + v15;
      *(_DWORD *)(_this + 28) = v17;
      v18 = v11[1] + v16;
      *(_DWORD *)(_this + 24) = v18;
      v19 = v11[3] + v17;
      *(_DWORD *)(_this + 28) = v19;
      v20 = v10[5] + v18;
      *(_DWORD *)(_this + 24) = v20;
      v21 = v10[7] + v19;
      *(_DWORD *)(_this + 28) = v21;
      v22 = v11[5] + v20;
      *(_DWORD *)(_this + 24) = v22;
      v23 = v11[7] + v21;
      *(_DWORD *)(_this + 28) = v23;
      v24 = v10[9] + v22;
      *(_DWORD *)(_this + 24) = v24;
      v25 = v10[11] + v23;
      *(_DWORD *)(_this + 28) = v25;
      v26 = v11[9] + v24;
      v27 = *(_DWORD *)(_this + 196);
      *(_DWORD *)(_this + 24) = v26;
      v28 = v11[11] + v25;
      *(_DWORD *)(_this + 28) = v28;
      v29 = *(unsigned __int8 *)(v27 - 7) + v26;
      *(_DWORD *)(_this + 24) = v29;
      v30 = *(unsigned __int8 *)(v27 - 5) + v28;
      *(_DWORD *)(_this + 28) = v30;
      *(_DWORD *)(_this + 24) = *(unsigned __int8 *)(v27 - 3) + v29;
      v31 = *(_DWORD *)_this <= 0;
      *(_DWORD *)(_this + 28) = *(unsigned __int8 *)(v27 - 1) + v30;
      if ( !v31 )
      {
        v32 = a3;
        v40 = v4;
        v42 = 0;
        do
        {
          ++v42;
          sub_4248D0((unsigned __int8 **)_this, nullptr, 0);
          v33 = *(_BYTE *)(_this + 8);
          v34 = (unsigned __int8)(*a2 - v33);
          v35 = *(_BYTE *)(*(unsigned __int8 *)(_this + v34 + 984) + _this + 1496) + v33;
          n5 = *(unsigned __int8 *)(_this + v34 + 984);
          n16 = (unsigned __int8)*v32 - (unsigned __int8)(v35 + *v32 - *a2);
          if ( n16 < -16 || n16 > 16 )
          {
            *v32 = *a2;
            n5 = *(unsigned __int8 *)(_this + v34 + 1240);
          }
          else
          {
            *v32 = v35;
          }
          sub_4135A0(
            (unsigned __int16 *)(_this + 16 * *(_DWORD *)(_this + 12) + 3800),
            16 * *(_DWORD *)(_this + 12),
            *(_DWORD *)(_this + 16),
            n5);
          v38 = (unsigned __int8)*v32;
          v39 = v38 - *(_DWORD *)(_this + 8);
          **(_BYTE **)(_this + 196) = v38;
          *(_BYTE *)(*(_DWORD *)(_this + 196) + 1) = (BYTE4(v39) ^ v39) - BYTE4(v39);
          *(_DWORD *)(_this + 4 * *(_DWORD *)(_this + 20) + 24) = *(_DWORD *)(_this + 4 * *(_DWORD *)(_this + 20) + 24)
                                                              + *(unsigned __int8 *)(*(_DWORD *)(_this + 196) + 1)
                                                              - *(unsigned __int8 *)(*(_DWORD *)(_this + 196) - 7)
                                                              - (*(unsigned __int8 *)(*(_DWORD *)(_this + 212) - 3)
                                                               - *(unsigned __int8 *)(*(_DWORD *)(_this + 212) + 13)
                                                               + *(unsigned __int8 *)(*(_DWORD *)(_this + 204) - 3)
                                                               - *(unsigned __int8 *)(*(_DWORD *)(_this + 204) + 13));
          LODWORD(v39) = 16 * *(_DWORD *)(_this + 12);
          *(_DWORD *)(_this + 20) = *(_DWORD *)(_this + 20) == 0;
          if ( *(unsigned __int16 *)(v39 + _this + 3800) < 0x4000u )
            sub_4259F0(_this);
          *(_DWORD *)(_this + 196) += 2;
          ++v32;
          *(_DWORD *)(_this + 200) += 2;
          *(_DWORD *)(_this + 204) += 2;
          *(_DWORD *)(_this + 208) += 2;
          *(_DWORD *)(_this + 212) += 2;
          ++a2;
        }
        while ( v42 < *(_DWORD *)_this );
        v4 = v40;
        a3 = v32;
      }
    }
    while ( v4 < *(_DWORD *)(_this + 4) );
  }
  sub_414CE0();
}

#undef sub_4135A0
#undef sub_414CE0
#undef sub_414F60
#undef sub_4248D0
#undef sub_4259F0
