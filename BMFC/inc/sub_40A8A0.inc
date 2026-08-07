// sub_40A8A0 @ 0x0040A8A0 — __thiscall
// Extracted from BMF.cpp:8703-8913 by extract.py per incdec.md.

typedef void * t_sub_40A8A0_buf_2;
static t_sub_40A8A0_buf_2& __sub_40A8A0_buf_2 = *(t_sub_40A8A0_buf_2*)(blob1 + 0x004433FC - BMF_BLOB_BASE);
typedef int t_sub_40A8A0_dword_442E3C[0x10000];
static t_sub_40A8A0_dword_442E3C& __sub_40A8A0_dword_442E3C = *(t_sub_40A8A0_dword_442E3C*)(blob1 + 0x00442E3C - BMF_BLOB_BASE);
typedef int t_sub_40A8A0_dword_442E54[5];
static t_sub_40A8A0_dword_442E54& __sub_40A8A0_dword_442E54 = *(t_sub_40A8A0_dword_442E54*)(blob1 + 0x00442E54 - BMF_BLOB_BASE);
typedef int t_sub_40A8A0_dword_442E68;
static t_sub_40A8A0_dword_442E68& __sub_40A8A0_dword_442E68 = *(t_sub_40A8A0_dword_442E68*)(blob1 + 0x00442E68 - BMF_BLOB_BASE);
typedef int t_sub_40A8A0_dword_442E6C;
static t_sub_40A8A0_dword_442E6C& __sub_40A8A0_dword_442E6C = *(t_sub_40A8A0_dword_442E6C*)(blob1 + 0x00442E6C - BMF_BLOB_BASE);
typedef int t_sub_40A8A0_dword_443364;
static t_sub_40A8A0_dword_443364& __sub_40A8A0_dword_443364 = *(t_sub_40A8A0_dword_443364*)(blob1 + 0x00443364 - BMF_BLOB_BASE);
typedef int t_sub_40A8A0_n2;
static t_sub_40A8A0_n2& __sub_40A8A0_n2 = *(t_sub_40A8A0_n2*)(blob1 + 0x00443360 - BMF_BLOB_BASE);
typedef int t_sub_40A8A0_n4_1;
static t_sub_40A8A0_n4_1& __sub_40A8A0_n4_1 = *(t_sub_40A8A0_n4_1*)(blob1 + 0x004433DC - BMF_BLOB_BASE);


PROBE_DECL(__sub_40A8A0)
BMF_REALIGN __attribute__((thiscall)) int __sub_40A8A0(_DWORD *_this, int Src, unsigned int *p_Src, int n6, int n24, int __sub_40A8A0_n2)
{
  PROBE_HIT(__sub_40A8A0);
  double v6; // xmm0_8
  float v7; // xmm0_4
  float n6_1; // xmm2_4
  double v9; // xmm0_8
  float v10; // xmm2_4
  double v11; // xmm5_8
  float v12; // xmm0_4
  float v13; // xmm2_4
  float v14; // xmm6_4
  double v15; // xmm0_8
  float v16; // xmm0_4
  int Src_1; // esi
  int v18; // ebx
  int v19; // ecx
  signed int v20; // eax
  int v21; // edx
  _DWORD *v22; // edx
  int v23; // edi
  _DWORD *v24; // eax
  double v25; // xmm0_8
  double v26; // xmm0_8
  float v27; // xmm0_4
  int v28; // eax
  double v29; // xmm0_8
  float v30; // xmm0_4
  double v32; // xmm0_8
  float v33; // xmm2_4
  int v34; // ecx
  int v35; // ecx
  _DWORD *v36; // [esp+0h] [ebp-68h]
  int v37; // [esp+Ch] [ebp-5Ch]
  int v38; // [esp+10h] [ebp-58h]
  int v39; // [esp+18h] [ebp-50h]
  int v40; // [esp+20h] [ebp-48h]
  int v41; // [esp+24h] [ebp-44h]
  int v42; // [esp+28h] [ebp-40h]
  int v43; // [esp+2Ch] [ebp-3Ch]
  int n2_1; // [esp+38h] [ebp-30h]
  unsigned int Src_2; // [esp+3Ch] [ebp-2Ch]
  int v46; // [esp+44h] [ebp-24h]
  int v47; // [esp+48h] [ebp-20h]
  int n4; // [esp+4Ch] [ebp-1Ch]
  unsigned int v49; // [esp+50h] [ebp-18h]
  int v50; // [esp+54h] [ebp-14h]

  n4 = __sub_40A8A0_n4_1;
  if ( n6 == __sub_40A8A0_n4_1 )
  {
    if ( *(_DWORD *)(__sub_40A8A0_dword_442E3C[__sub_40A8A0_n2] + 4) )
      v9 = __libm_sse2_log((double)*(int *)((char *)__sub_40A8A0_buf_2 + 4 * __sub_40A8A0_n2 + 0x342B8) / (double)*(_DWORD *)(__sub_40A8A0_dword_442E3C[__sub_40A8A0_n2] + 4)) * 1.442695040888963;
    else
      v9 = 0;
    v10 = v9;
    v11 = (double)__sub_40A8A0_n2 + 1.1;
    v12 = v10;
    v13 = v11;
    v14 = v12 + 0.08;
    if ( v14 <= v11 )
      v13 = v12 + 0.08;
    if ( *(_DWORD *)(__sub_40A8A0_dword_442E68 + 4 * n24) )
      v15 = __libm_sse2_log((double)*(int *)((char *)__sub_40A8A0_buf_2 + 0x342E4) / (double)*(_DWORD *)(__sub_40A8A0_dword_442E68 + 4 * n24)) * 1.442695040888963;
    else
      v15 = 0;
    v16 = v15;
    n6_1 = v13 + v16;
  }
  else if ( n24 < 0 )
  {
    if ( *(_DWORD *)(__sub_40A8A0_dword_442E6C + 4 * *((unsigned __int8 *)__sub_40A8A0_buf_2 + n6 + 213056)) )
      v32 = __libm_sse2_log((double)*(int *)((char *)__sub_40A8A0_buf_2 + 0x342E8) / (double)*(_DWORD *)(__sub_40A8A0_dword_442E6C + 4 * *((unsigned __int8 *)__sub_40A8A0_buf_2 + n6 + 213056))) * 1.442695040888963;
    else
      v32 = 0;
    v33 = v32;
    n6_1 = v33 + 0.5;
  }
  else
  {
    if ( *(_DWORD *)(__sub_40A8A0_dword_442E54[0] + 4 * ((2 * n24) | (n6 - 5))) )
      v6 = __libm_sse2_log((double)*(int *)((char *)__sub_40A8A0_buf_2 + 0x342D0) / (double)*(_DWORD *)(__sub_40A8A0_dword_442E54[0] + 4 * ((2 * n24) | (n6 - 5)))) * 1.442695040888963;
    else
      v6 = 0;
    v7 = v6;
    n6_1 = v7 + 0.14;
  }
  if ( n6 <= 0 )
    return 0;
  Src_1 = Src;
  v50 = __sub_40A8A0_dword_443364;
  v49 = p_Src[1];
  Src_2 = *p_Src;
  n2_1 = ::__sub_40A8A0_n2;
  v46 = Src + p_Src[2];
  v18 = 0;
  v47 = Src + p_Src[3];
  while ( 1 )
  {
    if ( v50 )
    {
      if ( Src_1 + v18 <= v49 )
      {
        v21 = *(unsigned __int8 *)(v18 + Src_1 - 1);
        if ( Src_1 + v18 <= Src_2 )
        {
          v20 = v21 & 1 | p_Src[v21 + 5] | (2 * (v21 & 1));
        }
        else
        {
          v37 = *(unsigned __int8 *)(v18 + v46 - 1);
          v38 = *(unsigned __int8 *)(v18 + v46 + 1);
          v20 = *(_BYTE *)(v18 + v46) & 1
              | *(unsigned int *)((char *)p_Src + ((*(unsigned __int8 *)(v18 + v46) + v38 + v21 + v37) & 0xFFFFFFFC)
                                                + 20)
              | (2 * (v21 & 1));
          if ( n2_1 == 1 )
          {
            v35 = v20 < (int)p_Src[v21 + 5] || v20 < (int)p_Src[v38 + 5] || v20 < (int)p_Src[v37 + 5];
            v20 |= (v35 << 7) | (8 * (v37 & 1)) | (4 * (v38 & 1));
          }
        }
      }
      else
      {
        v43 = *(unsigned __int8 *)(v18 + v46);
        v42 = *(unsigned __int8 *)(v18 + Src_1 - 1);
        v40 = *(unsigned __int8 *)(v18 + v46 - 1);
        v41 = *(unsigned __int8 *)(v18 + v46 + 1);
        v19 = *(unsigned __int8 *)(v18 + v47)
            + *(unsigned __int8 *)(v18 + v46 + 2)
            + *(unsigned __int8 *)(v18 + v47 + 1)
            + *(unsigned __int8 *)(v18 + Src_1 - 2);
        Src_1 = Src;
        v20 = v43 & 1
            | p_Src[((*(unsigned __int8 *)(v18 + v47 + 3)
                    + *(unsigned __int8 *)(v18 + v47 + 2)
                    + *(unsigned __int8 *)(v18 + v47 - 2)
                    + *(unsigned __int8 *)(v18 + v46 - 3)
                    + *(unsigned __int8 *)(v18 + v46 + 4)
                    + *(unsigned __int8 *)(v18 + v47 - 1)
                    + *(unsigned __int8 *)(v18 + v46 + 3)
                    + *(unsigned __int8 *)(v18 + v46 - 2)
                    + 3 * (v41 + v40)
                    + *(unsigned __int8 *)(v18 + Src - 4)
                    + *(unsigned __int8 *)(v18 + Src - 3)
                    + 4 * (v42 + v43)
                    + 2 * v19) >> 5)
                  + 5]
            | (2 * (v42 & 1));
        if ( n2_1 == 1 )
        {
          v34 = v20 < (int)p_Src[v42 + 5] || v20 < (int)p_Src[v41 + 5] || v20 < (int)p_Src[v40 + 5];
          v20 |= (v34 << 7) | (8 * (v40 & 1)) | (4 * (v41 & 1));
        }
      }
    }
    else
    {
      v20 = *(unsigned __int8 *)(v18 + Src_1 - 1);
    }
    v22 = _this + 194 * v20;
    v23 = *v22;
    if ( v18 )
    {
      v24 = _this + 257 * v23;
      goto LABEL_35;
    }
    v24 = _this + 257 * v23;
    if ( n6 != n4 )
    {
      v39 = v24[49728];
      if ( !v39 )
        return 1;
      if ( *(_this + v23 + 49664) <= 2 * v39 )
      {
        v26 = 1.0;
      }
      else
      {
        v36 = v22;
        v25 = __libm_sse2_log((double)*(_this + v23 + 49664) / (double)v39);
        v22 = v36;
        v24 = _this + 257 * v23;
        v26 = v25 * 1.442695040888963;
      }
      v27 = v26;
      n6_1 = n6_1 + v27;
      if ( (float)n6 >= n6_1 )
        return 1;
    }
LABEL_35:
    v28 = v24[*((unsigned __int8 *)v22 + *(unsigned __int8 *)(v18 + Src_1) + 520) + 49729];
    if ( !v28 )
      return 1;
    v29 = *(_this + v23 + 49664) <= 2 * v28 ? 1.0 : __libm_sse2_log((double)*(_this + v23 + 49664) / (double)v28) * 1.442695040888963;
    v30 = v29;
    n6_1 = n6_1 - v30;
    if ( n6_1 <= 0.0 )
      return 1;
    if ( ++v18 >= n6 )
      return 0;
  }
}

