// sub_41C4B0 @ 0x0041C4B0 — __thiscall
// Extracted from BMF.cpp:25451-25678 by extract.py per incdec.md.

typedef __int128 t_sub_41C4B0_xmmword_439B20;
static t_sub_41C4B0_xmmword_439B20& __sub_41C4B0_xmmword_439B20 = *(t_sub_41C4B0_xmmword_439B20*)0x00439B20;
typedef __int128 t_sub_41C4B0_xmmword_439B30;
static t_sub_41C4B0_xmmword_439B30& __sub_41C4B0_xmmword_439B30 = *(t_sub_41C4B0_xmmword_439B30*)0x00439B30;
typedef __int128 t_sub_41C4B0_xmmword_441120;
static t_sub_41C4B0_xmmword_441120& __sub_41C4B0_xmmword_441120 = *(t_sub_41C4B0_xmmword_441120*)0x00441120;
typedef __int128 t_sub_41C4B0_xmmword_441130;
static t_sub_41C4B0_xmmword_441130& __sub_41C4B0_xmmword_441130 = *(t_sub_41C4B0_xmmword_441130*)0x00441130;
typedef __int128 t_sub_41C4B0_xmmword_441140;
static t_sub_41C4B0_xmmword_441140& __sub_41C4B0_xmmword_441140 = *(t_sub_41C4B0_xmmword_441140*)0x00441140;
typedef __int128 t_sub_41C4B0_xmmword_441150;
static t_sub_41C4B0_xmmword_441150& __sub_41C4B0_xmmword_441150 = *(t_sub_41C4B0_xmmword_441150*)0x00441150;
typedef __int128 t_sub_41C4B0_xmmword_441160;
static t_sub_41C4B0_xmmword_441160& __sub_41C4B0_xmmword_441160 = *(t_sub_41C4B0_xmmword_441160*)0x00441160;
typedef __int128 t_sub_41C4B0_xmmword_441170;
static t_sub_41C4B0_xmmword_441170& __sub_41C4B0_xmmword_441170 = *(t_sub_41C4B0_xmmword_441170*)0x00441170;
typedef __int128 t_sub_41C4B0_xmmword_441180;
static t_sub_41C4B0_xmmword_441180& __sub_41C4B0_xmmword_441180 = *(t_sub_41C4B0_xmmword_441180*)0x00441180;
typedef __int128 t_sub_41C4B0_xmmword_445760[0x10000];
static t_sub_41C4B0_xmmword_445760& __sub_41C4B0_xmmword_445760 = *(t_sub_41C4B0_xmmword_445760*)0x00445760;
typedef __int128 t_sub_41C4B0_xmmword_445770[0x10000];
static t_sub_41C4B0_xmmword_445770& __sub_41C4B0_xmmword_445770 = *(t_sub_41C4B0_xmmword_445770*)0x00445770;
typedef __int128 t_sub_41C4B0_xmmword_445780[0x10000];
static t_sub_41C4B0_xmmword_445780& __sub_41C4B0_xmmword_445780 = *(t_sub_41C4B0_xmmword_445780*)0x00445780;
typedef __int128 t_sub_41C4B0_xmmword_445790[0x10000];
static t_sub_41C4B0_xmmword_445790& __sub_41C4B0_xmmword_445790 = *(t_sub_41C4B0_xmmword_445790*)0x00445790;
typedef __int128 t_sub_41C4B0_xmmword_4457A0[0x10000];
static t_sub_41C4B0_xmmword_4457A0& __sub_41C4B0_xmmword_4457A0 = *(t_sub_41C4B0_xmmword_4457A0*)0x004457A0;
typedef __int128 t_sub_41C4B0_xmmword_4457B0[0x10000];
static t_sub_41C4B0_xmmword_4457B0& __sub_41C4B0_xmmword_4457B0 = *(t_sub_41C4B0_xmmword_4457B0*)0x004457B0;


PROBE_DECL(__sub_41C4B0)
__attribute__((force_align_arg_pointer)) BMF_SSE __attribute__((thiscall)) int __sub_41C4B0(__m128 *_this, __m128 *a2, __m128 **a3, int n2)
{
  PROBE_HIT(__sub_41C4B0);
  __m128 v4; // xmm1
  __m128 v5; // xmm4
  __m128 v6; // xmm4
  __m128 v7; // xmm4
  __m128 v8; // xmm4
  __m128 v9; // xmm1
  __m128 v10; // xmm2
  __m128 v11; // xmm6
  __m128 v12; // xmm2
  __m128 v13; // xmm3
  __m128 v14; // xmm6
  __m128 v15; // xmm0
  __m128 v16; // xmm7
  __m128 v17; // xmm3
  __m128 v18; // xmm0
  __m128 v19; // xmm0
  __m128 v20; // xmm5
  __m128 v21; // xmm5
  float v22; // xmm5_4
  __m128 v23; // xmm7
  __m128 v24; // xmm7
  __m128 v25; // xmm2
  __m128 v26; // xmm6
  __m128 v27; // xmm4
  __m128 v29; // xmm3
  __m128 v30; // xmm0
  __m128 v31; // xmm0
  float v32; // xmm4_4
  __m128 v33; // [esp+0h] [ebp-B0h]
  __m128 v34; // [esp+10h] [ebp-A0h]
  __m128 v35; // [esp+20h] [ebp-90h]
  __m128 v36; // [esp+30h] [ebp-80h]
  __m128 v37; // [esp+40h] [ebp-70h]
  __m128 v38; // [esp+50h] [ebp-60h]
  __m128 v39; // [esp+60h] [ebp-50h]
  __m128 v40; // [esp+70h] [ebp-40h]
  __m128 v41; // [esp+80h] [ebp-30h]
  float v42; // [esp+A0h] [ebp-10h]

  v4 = *a2;
  v5 = _mm_add_ps(
         _mm_add_ps(
           _mm_add_ps(
             _mm_add_ps(
               _mm_add_ps(
                 _mm_add_ps(_mm_mul_ps((__m128)__sub_41C4B0_xmmword_441120, *a2), _mm_mul_ps((__m128)__sub_41C4B0_xmmword_441130, a2[1])),
                 _mm_mul_ps((__m128)__sub_41C4B0_xmmword_441140, a2[2])),
               _mm_mul_ps((__m128)__sub_41C4B0_xmmword_441150, a2[3])),
             _mm_mul_ps((__m128)__sub_41C4B0_xmmword_441160, a2[4])),
           _mm_mul_ps((__m128)__sub_41C4B0_xmmword_441170, a2[5])),
         _mm_mul_ps((__m128)__sub_41C4B0_xmmword_441180, a2[6]));
  v6 = _mm_add_ps(v5, _mm_movehl_ps(v5, v5));
  v6.m128_f32[0] = v6.m128_f32[0] + M128F(_mm_shuffle_ps(v6, v6, 1)).m128_f32[0];
  a2[7].m128_i32[0] = v6.m128_i32[0];
  v42 = v6.m128_f32[0];
  v7 = _mm_unpacklo_ps(v6, v6);
  v8 = _mm_movelh_ps(v7, v7);
  v9 = _mm_sub_ps(v4, v8);
  *a2 = v9;
  v40 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_add_ps(
                _mm_add_ps(
                  _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445760[6 * n2], **a3),
                  _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445770[6 * n2], *a3[1])),
                _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445780[6 * n2], *a3[2])),
              _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445790[6 * n2], *a3[3])),
            _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457A0[6 * n2], *a3[4])),
          _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457B0[6 * n2], *a3[5]));
  v34 = _mm_sub_ps(a2[1], v8);
  a2[1] = v34;
  v10 = _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457B0[6 * n2], a3[5][1]);
  v11 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_add_ps(
                _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445760[6 * n2], (*a3)[1]),
                _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445770[6 * n2], a3[1][1])),
              _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445780[6 * n2], a3[2][1])),
            _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445790[6 * n2], a3[3][1])),
          _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457A0[6 * n2], a3[4][1]));
  v33 = _mm_sub_ps(a2[2], v8);
  a2[2] = v33;
  v38 = _mm_add_ps(v11, v10);
  v12 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_add_ps(
                _mm_add_ps(
                  _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445760[6 * n2], (*a3)[2]),
                  _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445770[6 * n2], a3[1][2])),
                _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445780[6 * n2], a3[2][2])),
              _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445790[6 * n2], a3[3][2])),
            _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457A0[6 * n2], a3[4][2])),
          _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457B0[6 * n2], a3[5][2]));
  v13 = _mm_sub_ps(a2[3], v8);
  a2[3] = v13;
  v35 = v13;
  v14 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_add_ps(
                _mm_add_ps(
                  _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445760[6 * n2], (*a3)[3]),
                  _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445770[6 * n2], a3[1][3])),
                _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445780[6 * n2], a3[2][3])),
              _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445790[6 * n2], a3[3][3])),
            _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457A0[6 * n2], a3[4][3])),
          _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457B0[6 * n2], a3[5][3]));
  v15 = _mm_sub_ps(a2[4], v8);
  a2[4] = v15;
  v36 = v15;
  v41 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_add_ps(
                _mm_add_ps(
                  _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445760[6 * n2], (*a3)[4]),
                  _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445770[6 * n2], a3[1][4])),
                _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445780[6 * n2], a3[2][4])),
              _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445790[6 * n2], a3[3][4])),
            _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457A0[6 * n2], a3[4][4])),
          _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457B0[6 * n2], a3[5][4]));
  v16 = _mm_mul_ps(v41, v15);
  v37 = _mm_sub_ps(a2[5], v8);
  a2[5] = v37;
  v17 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_add_ps(
                _mm_add_ps(
                  _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445760[6 * n2], (*a3)[5]),
                  _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445770[6 * n2], a3[1][5])),
                _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445780[6 * n2], a3[2][5])),
              _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445790[6 * n2], a3[3][5])),
            _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457A0[6 * n2], a3[4][5])),
          _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457B0[6 * n2], a3[5][5]));
  v18 = _mm_sub_ps(a2[6], v8);
  a2[6] = v18;
  v39 = v18;
  v19 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_add_ps(
                _mm_add_ps(
                  _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445760[6 * n2], (*a3)[6]),
                  _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445770[6 * n2], a3[1][6])),
                _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445780[6 * n2], a3[2][6])),
              _mm_mul_ps((__m128)__sub_41C4B0_xmmword_445790[6 * n2], a3[3][6])),
            _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457A0[6 * n2], a3[4][6])),
          _mm_mul_ps((__m128)__sub_41C4B0_xmmword_4457B0[6 * n2], a3[5][6]));
  v20 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_add_ps(
                _mm_add_ps(_mm_add_ps(_mm_mul_ps(v40, v9), _mm_mul_ps(v38, v34)), _mm_mul_ps(v12, v33)),
                _mm_mul_ps(v14, v35)),
              v16),
            _mm_mul_ps(v17, v37)),
          _mm_mul_ps(v19, v39));
  v21 = _mm_add_ps(v20, _mm_movehl_ps(v20, v20));
  v22 = (float)(v21.m128_f32[0] + M128F(_mm_shuffle_ps(v21, v21, 1)).m128_f32[0]) + v42;
  a2[7].m128_f32[2] = v22;
  if ( *((_DWORD *)_this + 60) )
  {
    v30 = _mm_add_ps(
            _mm_add_ps(
              _mm_add_ps(
                _mm_add_ps(
                  _mm_add_ps(
                    _mm_add_ps(_mm_mul_ps(*_this, v9), _mm_mul_ps(*(_this + 1), v34)),
                    _mm_mul_ps(*(_this + 2), v33)),
                  _mm_mul_ps(*(_this + 3), v35)),
                _mm_mul_ps(*(_this + 4), v36)),
              _mm_mul_ps(*(_this + 5), v37)),
            _mm_mul_ps(*(_this + 6), v39));
    v31 = _mm_add_ps(v30, _mm_movehl_ps(v30, v30));
    v32 = v42 + (float)(v31.m128_f32[0] + M128F(_mm_shuffle_ps(v31, v31, 1)).m128_f32[0]);
    a2[7].m128_f32[1] = v32;
    return (int)(float)(v22 + (float)((float)((float)(v32 - v22) * *((float *)_this + 56)) / *((float *)_this + 57)));
  }
  else
  {
    *_this = _mm_mul_ps(v40, (__m128)__sub_41C4B0_xmmword_439B20);
    v23 = _mm_mul_ps((*a3)[7], (__m128)__sub_41C4B0_xmmword_439B30);
    *(_this + 1) = _mm_mul_ps(v38, (__m128)__sub_41C4B0_xmmword_439B20);
    *(_this + 7) = v23;
    v24 = _mm_mul_ps((*a3)[8], (__m128)__sub_41C4B0_xmmword_439B30);
    *(_this + 2) = _mm_mul_ps(v12, (__m128)__sub_41C4B0_xmmword_439B20);
    *(_this + 8) = v24;
    v25 = _mm_mul_ps((*a3)[9], (__m128)__sub_41C4B0_xmmword_439B30);
    *(_this + 3) = _mm_mul_ps(v14, (__m128)__sub_41C4B0_xmmword_439B20);
    *(_this + 9) = v25;
    v26 = _mm_mul_ps((*a3)[10], (__m128)__sub_41C4B0_xmmword_439B30);
    *(_this + 4) = _mm_mul_ps(v41, (__m128)__sub_41C4B0_xmmword_439B20);
    *(_this + 10) = v26;
    v27 = _mm_mul_ps((*a3)[11], (__m128)__sub_41C4B0_xmmword_439B30);
    *(_this + 5) = _mm_mul_ps(v17, (__m128)__sub_41C4B0_xmmword_439B20);
    *(_this + 11) = v27;
    v29 = _mm_mul_ps((*a3)[12], (__m128)__sub_41C4B0_xmmword_439B30);
    *(_this + 6) = _mm_mul_ps(v19, (__m128)__sub_41C4B0_xmmword_439B20);
    *(_this + 12) = v29;
    *(_this + 13) = _mm_mul_ps((__m128)__sub_41C4B0_xmmword_439B30, (*a3)[13]);
    *((_DWORD *)_this + 56) = 1111228416;
    *((_DWORD *)_this + 57) = 1126773555;
    *((_DWORD *)_this + 58) = 1065353216;
    a2[7].m128_f32[1] = v22;
    return (int)v22;
  }
}

