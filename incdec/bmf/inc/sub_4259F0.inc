// sub_4259F0 @ 0x004259F0 — __thiscall
// Extracted from BMF.cpp:31098-31862 by extract.py per incdec.md.

typedef int t_sub_4259F0_n256_1;
static t_sub_4259F0_n256_1& __sub_4259F0_n256_1 = *(t_sub_4259F0_n256_1*)0x00445708;

static inline int __fwd_sub_4259F0_sub_413430(void *a0, int a1) { return __sub_413430((unsigned __int16 *)a0, a1); }
#define sub_413430 __fwd_sub_4259F0_sub_413430

PROBE_DECL(__sub_4259F0)
__attribute__((force_align_arg_pointer)) __attribute__((thiscall)) int __sub_4259F0(int _this)
{
  PROBE_HIT(__sub_4259F0);
  unsigned int n5; // edi
  int v3; // eax
  int n5_1; // ebx
  int v5; // edx
  int n5_2; // ebp
  int n5_3; // ecx
  int v8; // ebx
  int v9; // edx
  int result; // eax
  int v11; // eax
  __int16 v12; // dx
  int v13; // eax
  int v14; // edi
  __int16 v15; // dx
  int v16; // edx
  int v17; // eax
  int v18; // eax
  _WORD *v19; // ecx
  _WORD *v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // edx
  int v24; // edx
  int v25; // ecx
  int v26; // edx
  _WORD *v27; // ecx
  _WORD *v28; // edx
  int v29; // eax
  int v30; // edx
  int v31; // eax
  int v32; // eax
  int v33; // ecx
  int v34; // eax
  _WORD *v35; // ecx
  _WORD *v36; // eax
  int v37; // edx
  int v38; // eax
  int v39; // edx
  int v40; // edx
  int v41; // ecx
  int v42; // edx
  _WORD *v43; // ecx
  _WORD *v44; // edx
  int v45; // eax
  int v46; // edx
  int v47; // eax
  int v48; // eax
  int v49; // ecx
  int v50; // eax
  _WORD *v51; // ecx
  _WORD *v52; // eax
  int v53; // edx
  int v54; // eax
  int v55; // edx
  int v56; // edx
  int v57; // ecx
  int v58; // edx
  _WORD *v59; // ecx
  _WORD *v60; // edx
  int v61; // eax
  int v62; // edx
  int v63; // eax
  int v64; // eax
  int v65; // ecx
  int v66; // eax
  _WORD *v67; // ecx
  _WORD *v68; // eax
  int v69; // edx
  int v70; // eax
  int v71; // edx
  int v72; // edx
  int v73; // ecx
  int v74; // edx
  _WORD *v75; // ecx
  _WORD *v76; // edx
  int v77; // eax
  int v78; // ecx
  int v79; // eax
  int v80; // ecx
  _WORD *v81; // ebx
  int v82; // edx
  int v83; // eax
  _WORD *v84; // edx
  int v85; // ebx
  int v86; // edx
  _WORD *v87; // ecx
  _WORD *v88; // edx
  int v89; // eax
  _WORD *v90; // ecx
  _WORD *v91; // eax
  int v92; // edx
  _WORD *v93; // ecx
  _WORD *v94; // edx
  int v95; // eax
  _WORD *v96; // ecx
  _WORD *v97; // eax
  int v98; // edx
  _WORD *v99; // ecx
  _WORD *v100; // edx
  int v101; // eax
  _WORD *v102; // ecx
  _WORD *v103; // eax
  int v104; // edx
  _WORD *v105; // ecx
  _WORD *v106; // edx
  int v107; // eax
  _WORD *v108; // ecx
  _WORD *v109; // eax
  unsigned int v110; // [esp+0h] [ebp-24h]
  int v111; // [esp+4h] [ebp-20h]
  unsigned int v112; // [esp+8h] [ebp-1Ch]
  int n2; // [esp+Ch] [ebp-18h]
  int n5_4; // [esp+10h] [ebp-14h]

  n5 = *(unsigned __int8 *)((unsigned __int8)(**(_BYTE **)(_this + 196) - *(_BYTE *)(_this + 8)) + _this + 984);
  v3 = *(_DWORD *)(_this + 48);
  n5_1 = *(unsigned __int8 *)((unsigned __int8)(*(_BYTE *)(_this + 8) - **(_BYTE **)(_this + 196)) + _this + 984);
  v5 = *(_DWORD *)(_this + 64);
  n2 = (int)(n5 - 5) >> 1;
  n5_2 = 6 - (n5 & 1);
  if ( n5 < 5 )
    n5_2 = *(unsigned __int8 *)((unsigned __int8)(**(_BYTE **)(_this + 196) - *(_BYTE *)(_this + 8)) + _this + 984);
  n5_3 = 6 - (n5_1 & 1);
  if ( n5_1 < 5 )
    n5_3 = n5_1;
  n5_4 = n5_3;
  v8 = *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 160) + 172)
     + *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 144) + 156)
     + *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 128) + 140)
     + *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 112) + 124)
     + *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 96) + 108)
     + *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 80) + 92)
     + *(_DWORD *)(_this - 4 * v5 + 76)
     + *(_DWORD *)(_this - 4 * v3 + 60)
     + *(_DWORD *)(_this + 40)
     + (*(_DWORD *)(_this + 12) & 0x1F);
  v9 = _this + 16 * v8;
  v111 = v9;
  *(_WORD *)(v9 + 2 * n5_3 + 3802) += 17;
  *(_WORD *)(v9 + 3800) += 17;
  result = *(_DWORD *)(_this + 12);
  if ( (result & 7) != 7 )
  {
    v11 = _this + 16 * result;
    v110 = (((*(_DWORD *)(_this + 16) & 7u) - 7) >> 31) + *(_DWORD *)(_this + 16);
    *(_WORD *)(v11 + 2 * n5_2 + 3818) += 11;
    v12 = *(_WORD *)(v11 + 3816) + 11;
    *(_WORD *)(v11 + 3816) = v12;
    if ( n5_2 >= 5 )
      sub_413430(
        (unsigned __int16 *)__sub_4259F0_n256_1
      + 32512 * (n5_2 & 1)
      + 254 * v110
      + 254
      * ((((v12 & 0x7FFF)
         + *(unsigned __int16 *)(v11 + 3818)
         - 2 * (unsigned int)*(unsigned __int16 *)(v11 + 2 * n5_2 + 3818)) >> 25)
       & 0xFFFFFFC0),
        (int)(n5 - 5) >> 1);
    result = *(_DWORD *)(_this + 12);
  }
  if ( (result & 7) != 0 )
  {
    v13 = _this + 16 * result;
    v14 = *(_DWORD *)(_this + 16) - ((*(_DWORD *)(_this + 16) & 7) != 0);
    *(_WORD *)(v13 + 2 * n5_2 + 3786) += 13;
    v15 = *(_WORD *)(v13 + 3784) + 13;
    *(_WORD *)(v13 + 3784) = v15;
    if ( n5_2 >= 5 )
      sub_413430(
        (unsigned __int16 *)__sub_4259F0_n256_1
      + 32512 * (n5_2 & 1)
      + 254 * v14
      + 254
      * ((((v15 & 0x7FFF)
         + *(unsigned __int16 *)(v13 + 3786)
         - 2 * (unsigned int)*(unsigned __int16 *)(v13 + 2 * n5_2 + 3786)) >> 25)
       & 0xFFFFFFC0),
        n2);
    result = *(_DWORD *)(_this + 12);
  }
  if ( *(unsigned __int16 *)(16 * result + _this + 3800) < 0xCCCu )
  {
    if ( (result & 7u) < 7 )
    {
      *(_WORD *)(v111 + 2 * n5_4 + 3818) += 7;
      *(_WORD *)(v111 + 3816) += 7;
      result = *(_DWORD *)(_this + 12);
    }
    if ( (result & 7) != 0 )
    {
      *(_WORD *)(v111 + 2 * n5_4 + 3786) += 5;
      *(_WORD *)(v111 + 3784) += 5;
      result = *(_DWORD *)(_this + 12);
    }
    if ( n5_2 >= 5 )
    {
      v112 = *(_DWORD *)(_this + 16)
           + (((*(unsigned __int16 *)(_this + 16 * result + 3802)
              + (*(_WORD *)(_this + 16 * result + 3800) & 0x7FFF)
              - 2 * (unsigned int)*(unsigned __int16 *)(_this + 16 * result + 2 * n5_2 + 3802)) >> 25)
            & 0xFFFFFFC0)
           + ((n5_2 & 1) << 7);
      if ( (v112 & 0x38) >= 0x38
        || (sub_413430(
              (unsigned __int16 *)__sub_4259F0_n256_1
            + 32512 * (n5_2 & 1)
            + 254 * *(_DWORD *)(_this + 16)
            + 254
            * (((*(unsigned __int16 *)(_this + 16 * result + 3802)
               + (*(_WORD *)(_this + 16 * result + 3800) & 0x7FFF)
               - 2 * (unsigned int)*(unsigned __int16 *)(_this + 16 * result + 2 * n5_2 + 3802)) >> 25)
             & 0xFFFFFFC0)
            + 2032,
              n2),
            (v112 & 0x38) != 0) )
      {
        sub_413430((unsigned __int16 *)__sub_4259F0_n256_1 + 254 * v112 - 2032, n2);
      }
      result = *(_DWORD *)(_this + 12);
    }
    v16 = *(_DWORD *)(_this + 32);
    if ( v16 == 1 )
    {
      v107 = result - *(_DWORD *)(_this + 40);
      v108 = (_WORD *)(_this + 16 * (v107 + *(_DWORD *)(_this + 36)));
      v109 = (_WORD *)(_this + 16 * (*(_DWORD *)(_this + 44) + v107));
      v108[n5_2 + 1901] += 6;
      v108[1900] += 6;
      v109[n5_2 + 1901] += 6;
      v109[1900] += 6;
      v21 = *(_DWORD *)(_this + 12);
      if ( (v21 & 7) != 7 )
      {
        v108[n5_2 + 1909] += 4;
        v108[1908] += 4;
        v109[n5_2 + 1909] += 4;
        v109[1908] += 4;
        v21 = *(_DWORD *)(_this + 12);
      }
      if ( (v21 & 7) != 0 )
      {
        v108[n5_2 + 1893] += 3;
        v108[1892] += 3;
        v109[n5_2 + 1893] += 3;
        v109[1892] += 3;
        v21 = *(_DWORD *)(_this + 12);
      }
    }
    else
    {
      v17 = _this + 16 * (*(_DWORD *)(_this - 4 * v16 + 44) + result - *(_DWORD *)(_this + 4 * v16 + 36));
      *(_WORD *)(v17 + 2 * n5_2 + 3802) += 7;
      *(_WORD *)(v17 + 3800) += 7;
      v18 = v8 + *(_DWORD *)(_this + 36) - *(_DWORD *)(_this + 40);
      v19 = (_WORD *)(_this
                    + 16
                    * (*(_DWORD *)(_this + 40)
                     + *(_DWORD *)(_this + 12)
                     - *(_DWORD *)(_this + 4 * *(_DWORD *)(_this + 32) + 36)));
      v19[n5_2 + 1901] += 6;
      v19[1900] += 6;
      v20 = (_WORD *)(_this + 16 * v18);
      v20[n5_4 + 1901] += 4;
      v20[1900] += 4;
      v21 = *(_DWORD *)(_this + 12);
      if ( (v21 & 7) != 7 )
      {
        v19[n5_2 + 1909] += 4;
        v19[1908] += 4;
        v20[n5_4 + 1909] += 2;
        v20[1908] += 2;
        v21 = *(_DWORD *)(_this + 12);
      }
      if ( (v21 & 7) != 0 )
      {
        v19[n5_2 + 1893] += 3;
        v19[1892] += 3;
        v20[n5_4 + 1893] += 2;
        v20[1892] += 2;
        v21 = *(_DWORD *)(_this + 12);
      }
    }
    v22 = *(_DWORD *)(_this + 48);
    if ( v22 == 1 )
    {
      v104 = v21 - *(_DWORD *)(_this + 56);
      v105 = (_WORD *)(_this + 16 * (v104 + *(_DWORD *)(_this + 52)));
      v106 = (_WORD *)(_this + 16 * (*(_DWORD *)(_this + 60) + v104));
      v105[n5_2 + 1901] += 6;
      v105[1900] += 6;
      v106[n5_2 + 1901] += 6;
      v106[1900] += 6;
      v29 = *(_DWORD *)(_this + 12);
      if ( (v29 & 7) != 7 )
      {
        v105[n5_2 + 1909] += 4;
        v105[1908] += 4;
        v106[n5_2 + 1909] += 4;
        v106[1908] += 4;
        v29 = *(_DWORD *)(_this + 12);
      }
      if ( (v29 & 7) != 0 )
      {
        v105[n5_2 + 1893] += 3;
        v105[1892] += 3;
        v106[n5_2 + 1893] += 3;
        v106[1892] += 3;
        v29 = *(_DWORD *)(_this + 12);
      }
    }
    else
    {
      v23 = _this + 16 * (*(_DWORD *)(_this - 4 * v22 + 60) + v21 - *(_DWORD *)(_this + 4 * v22 + 52));
      *(_WORD *)(v23 + 2 * n5_2 + 3802) += 7;
      *(_WORD *)(v23 + 3800) += 7;
      v24 = *(_DWORD *)(_this + 56);
      v25 = v24 + *(_DWORD *)(_this + 12) - *(_DWORD *)(_this + 4 * *(_DWORD *)(_this + 48) + 52);
      v26 = v8 + v24 - *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 48) + 60);
      v27 = (_WORD *)(_this + 16 * v25);
      v27[n5_2 + 1901] += 6;
      v27[1900] += 6;
      v28 = (_WORD *)(_this + 16 * v26);
      v28[n5_4 + 1901] += 4;
      v28[1900] += 4;
      v29 = *(_DWORD *)(_this + 12);
      if ( (v29 & 7) != 7 )
      {
        v27[n5_2 + 1909] += 4;
        v27[1908] += 4;
        v28[n5_4 + 1909] += 2;
        v28[1908] += 2;
        v29 = *(_DWORD *)(_this + 12);
      }
      if ( (v29 & 7) != 0 )
      {
        v27[n5_2 + 1893] += 3;
        v27[1892] += 3;
        v28[n5_4 + 1893] += 2;
        v28[1892] += 2;
        v29 = *(_DWORD *)(_this + 12);
      }
    }
    v30 = *(_DWORD *)(_this + 64);
    if ( v30 == 1 )
    {
      v101 = v29 - *(_DWORD *)(_this + 72);
      v102 = (_WORD *)(_this + 16 * (v101 + *(_DWORD *)(_this + 68)));
      v103 = (_WORD *)(_this + 16 * (*(_DWORD *)(_this + 76) + v101));
      v102[n5_2 + 1901] += 6;
      v102[1900] += 6;
      v103[n5_2 + 1901] += 6;
      v103[1900] += 6;
      v37 = *(_DWORD *)(_this + 12);
      if ( (v37 & 7) != 7 )
      {
        v102[n5_2 + 1909] += 4;
        v102[1908] += 4;
        v103[n5_2 + 1909] += 4;
        v103[1908] += 4;
        v37 = *(_DWORD *)(_this + 12);
      }
      if ( (v37 & 7) != 0 )
      {
        v102[n5_2 + 1893] += 3;
        v102[1892] += 3;
        v103[n5_2 + 1893] += 3;
        v103[1892] += 3;
        v37 = *(_DWORD *)(_this + 12);
      }
    }
    else
    {
      v31 = _this + 16 * (*(_DWORD *)(_this - 4 * v30 + 76) + v29 - *(_DWORD *)(_this + 4 * v30 + 68));
      *(_WORD *)(v31 + 2 * n5_2 + 3802) += 7;
      *(_WORD *)(v31 + 3800) += 7;
      v32 = *(_DWORD *)(_this + 72);
      v33 = v32 + *(_DWORD *)(_this + 12) - *(_DWORD *)(_this + 4 * *(_DWORD *)(_this + 64) + 68);
      v34 = v8 + v32 - *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 64) + 76);
      v35 = (_WORD *)(_this + 16 * v33);
      v35[n5_2 + 1901] += 6;
      v35[1900] += 6;
      v36 = (_WORD *)(_this + 16 * v34);
      v36[n5_4 + 1901] += 4;
      v36[1900] += 4;
      v37 = *(_DWORD *)(_this + 12);
      if ( (v37 & 7) != 7 )
      {
        v35[n5_2 + 1909] += 4;
        v35[1908] += 4;
        v36[n5_4 + 1909] += 2;
        v36[1908] += 2;
        v37 = *(_DWORD *)(_this + 12);
      }
      if ( (v37 & 7) != 0 )
      {
        v35[n5_2 + 1893] += 3;
        v35[1892] += 3;
        v36[n5_4 + 1893] += 2;
        v36[1892] += 2;
        v37 = *(_DWORD *)(_this + 12);
      }
    }
    v38 = *(_DWORD *)(_this + 80);
    if ( v38 == 1 )
    {
      v98 = v37 - *(_DWORD *)(_this + 88);
      v99 = (_WORD *)(_this + 16 * (v98 + *(_DWORD *)(_this + 84)));
      v100 = (_WORD *)(_this + 16 * (*(_DWORD *)(_this + 92) + v98));
      v99[n5_2 + 1901] += 6;
      v99[1900] += 6;
      v100[n5_2 + 1901] += 6;
      v100[1900] += 6;
      v45 = *(_DWORD *)(_this + 12);
      if ( (v45 & 7) != 7 )
      {
        v99[n5_2 + 1909] += 4;
        v99[1908] += 4;
        v100[n5_2 + 1909] += 4;
        v100[1908] += 4;
        v45 = *(_DWORD *)(_this + 12);
      }
      if ( (v45 & 7) != 0 )
      {
        v99[n5_2 + 1893] += 3;
        v99[1892] += 3;
        v100[n5_2 + 1893] += 3;
        v100[1892] += 3;
        v45 = *(_DWORD *)(_this + 12);
      }
    }
    else
    {
      v39 = _this + 16 * (*(_DWORD *)(_this - 4 * v38 + 92) + v37 - *(_DWORD *)(_this + 4 * v38 + 84));
      *(_WORD *)(v39 + 2 * n5_2 + 3802) += 7;
      *(_WORD *)(v39 + 3800) += 7;
      v40 = *(_DWORD *)(_this + 88);
      v41 = v40 + *(_DWORD *)(_this + 12) - *(_DWORD *)(_this + 4 * *(_DWORD *)(_this + 80) + 84);
      v42 = v8 + v40 - *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 80) + 92);
      v43 = (_WORD *)(_this + 16 * v41);
      v43[n5_2 + 1901] += 6;
      v43[1900] += 6;
      v44 = (_WORD *)(_this + 16 * v42);
      v44[n5_4 + 1901] += 4;
      v44[1900] += 4;
      v45 = *(_DWORD *)(_this + 12);
      if ( (v45 & 7) != 7 )
      {
        v43[n5_2 + 1909] += 4;
        v43[1908] += 4;
        v44[n5_4 + 1909] += 2;
        v44[1908] += 2;
        v45 = *(_DWORD *)(_this + 12);
      }
      if ( (v45 & 7) != 0 )
      {
        v43[n5_2 + 1893] += 3;
        v43[1892] += 3;
        v44[n5_4 + 1893] += 2;
        v44[1892] += 2;
        v45 = *(_DWORD *)(_this + 12);
      }
    }
    v46 = *(_DWORD *)(_this + 96);
    if ( v46 == 1 )
    {
      v95 = v45 - *(_DWORD *)(_this + 104);
      v96 = (_WORD *)(_this + 16 * (v95 + *(_DWORD *)(_this + 100)));
      v97 = (_WORD *)(_this + 16 * (*(_DWORD *)(_this + 108) + v95));
      v96[n5_2 + 1901] += 6;
      v96[1900] += 6;
      v97[n5_2 + 1901] += 6;
      v97[1900] += 6;
      v53 = *(_DWORD *)(_this + 12);
      if ( (v53 & 7) != 7 )
      {
        v96[n5_2 + 1909] += 4;
        v96[1908] += 4;
        v97[n5_2 + 1909] += 4;
        v97[1908] += 4;
        v53 = *(_DWORD *)(_this + 12);
      }
      if ( (v53 & 7) != 0 )
      {
        v96[n5_2 + 1893] += 3;
        v96[1892] += 3;
        v97[n5_2 + 1893] += 3;
        v97[1892] += 3;
        v53 = *(_DWORD *)(_this + 12);
      }
    }
    else
    {
      v47 = _this + 16 * (*(_DWORD *)(_this - 4 * v46 + 108) + v45 - *(_DWORD *)(_this + 4 * v46 + 100));
      *(_WORD *)(v47 + 2 * n5_2 + 3802) += 7;
      *(_WORD *)(v47 + 3800) += 7;
      v48 = *(_DWORD *)(_this + 104);
      v49 = v48 + *(_DWORD *)(_this + 12) - *(_DWORD *)(_this + 4 * *(_DWORD *)(_this + 96) + 100);
      v50 = v8 + v48 - *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 96) + 108);
      v51 = (_WORD *)(_this + 16 * v49);
      v51[n5_2 + 1901] += 6;
      v51[1900] += 6;
      v52 = (_WORD *)(_this + 16 * v50);
      v52[n5_4 + 1901] += 4;
      v52[1900] += 4;
      v53 = *(_DWORD *)(_this + 12);
      if ( (v53 & 7) != 7 )
      {
        v51[n5_2 + 1909] += 4;
        v51[1908] += 4;
        v52[n5_4 + 1909] += 2;
        v52[1908] += 2;
        v53 = *(_DWORD *)(_this + 12);
      }
      if ( (v53 & 7) != 0 )
      {
        v51[n5_2 + 1893] += 3;
        v51[1892] += 3;
        v52[n5_4 + 1893] += 2;
        v52[1892] += 2;
        v53 = *(_DWORD *)(_this + 12);
      }
    }
    v54 = *(_DWORD *)(_this + 112);
    if ( v54 == 1 )
    {
      v92 = v53 - *(_DWORD *)(_this + 120);
      v93 = (_WORD *)(_this + 16 * (v92 + *(_DWORD *)(_this + 116)));
      v94 = (_WORD *)(_this + 16 * (*(_DWORD *)(_this + 124) + v92));
      v93[n5_2 + 1901] += 6;
      v93[1900] += 6;
      v94[n5_2 + 1901] += 6;
      v94[1900] += 6;
      v61 = *(_DWORD *)(_this + 12);
      if ( (v61 & 7) != 7 )
      {
        v93[n5_2 + 1909] += 4;
        v93[1908] += 4;
        v94[n5_2 + 1909] += 4;
        v94[1908] += 4;
        v61 = *(_DWORD *)(_this + 12);
      }
      if ( (v61 & 7) != 0 )
      {
        v93[n5_2 + 1893] += 3;
        v93[1892] += 3;
        v94[n5_2 + 1893] += 3;
        v94[1892] += 3;
        v61 = *(_DWORD *)(_this + 12);
      }
    }
    else
    {
      v55 = _this + 16 * (*(_DWORD *)(_this - 4 * v54 + 124) + v53 - *(_DWORD *)(_this + 4 * v54 + 116));
      *(_WORD *)(v55 + 2 * n5_2 + 3802) += 7;
      *(_WORD *)(v55 + 3800) += 7;
      v56 = *(_DWORD *)(_this + 120);
      v57 = v56 + *(_DWORD *)(_this + 12) - *(_DWORD *)(_this + 4 * *(_DWORD *)(_this + 112) + 116);
      v58 = v8 + v56 - *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 112) + 124);
      v59 = (_WORD *)(_this + 16 * v57);
      v59[n5_2 + 1901] += 6;
      v59[1900] += 6;
      v60 = (_WORD *)(_this + 16 * v58);
      v60[n5_4 + 1901] += 4;
      v60[1900] += 4;
      v61 = *(_DWORD *)(_this + 12);
      if ( (v61 & 7) != 7 )
      {
        v59[n5_2 + 1909] += 4;
        v59[1908] += 4;
        v60[n5_4 + 1909] += 2;
        v60[1908] += 2;
        v61 = *(_DWORD *)(_this + 12);
      }
      if ( (v61 & 7) != 0 )
      {
        v59[n5_2 + 1893] += 3;
        v59[1892] += 3;
        v60[n5_4 + 1893] += 2;
        v60[1892] += 2;
        v61 = *(_DWORD *)(_this + 12);
      }
    }
    v62 = *(_DWORD *)(_this + 128);
    if ( v62 == 1 )
    {
      v89 = v61 - *(_DWORD *)(_this + 136);
      v90 = (_WORD *)(_this + 16 * (v89 + *(_DWORD *)(_this + 132)));
      v91 = (_WORD *)(_this + 16 * (*(_DWORD *)(_this + 140) + v89));
      v90[n5_2 + 1901] += 6;
      v90[1900] += 6;
      v91[n5_2 + 1901] += 6;
      v91[1900] += 6;
      v69 = *(_DWORD *)(_this + 12);
      if ( (v69 & 7) != 7 )
      {
        v90[n5_2 + 1909] += 4;
        v90[1908] += 4;
        v91[n5_2 + 1909] += 4;
        v91[1908] += 4;
        v69 = *(_DWORD *)(_this + 12);
      }
      if ( (v69 & 7) != 0 )
      {
        v90[n5_2 + 1893] += 3;
        v90[1892] += 3;
        v91[n5_2 + 1893] += 3;
        v91[1892] += 3;
        v69 = *(_DWORD *)(_this + 12);
      }
    }
    else
    {
      v63 = _this + 16 * (*(_DWORD *)(_this - 4 * v62 + 140) + v61 - *(_DWORD *)(_this + 4 * v62 + 132));
      *(_WORD *)(v63 + 2 * n5_2 + 3802) += 7;
      *(_WORD *)(v63 + 3800) += 7;
      v64 = *(_DWORD *)(_this + 136);
      v65 = v64 + *(_DWORD *)(_this + 12) - *(_DWORD *)(_this + 4 * *(_DWORD *)(_this + 128) + 132);
      v66 = v8 + v64 - *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 128) + 140);
      v67 = (_WORD *)(_this + 16 * v65);
      v67[n5_2 + 1901] += 6;
      v67[1900] += 6;
      v68 = (_WORD *)(_this + 16 * v66);
      v68[n5_4 + 1901] += 4;
      v68[1900] += 4;
      v69 = *(_DWORD *)(_this + 12);
      if ( (v69 & 7) != 7 )
      {
        v67[n5_2 + 1909] += 4;
        v67[1908] += 4;
        v68[n5_4 + 1909] += 2;
        v68[1908] += 2;
        v69 = *(_DWORD *)(_this + 12);
      }
      if ( (v69 & 7) != 0 )
      {
        v67[n5_2 + 1893] += 3;
        v67[1892] += 3;
        v68[n5_4 + 1893] += 2;
        v68[1892] += 2;
        v69 = *(_DWORD *)(_this + 12);
      }
    }
    v70 = *(_DWORD *)(_this + 144);
    if ( v70 == 1 )
    {
      v86 = v69 - *(_DWORD *)(_this + 152);
      v87 = (_WORD *)(_this + 16 * (v86 + *(_DWORD *)(_this + 148)));
      v88 = (_WORD *)(_this + 16 * (*(_DWORD *)(_this + 156) + v86));
      v87[n5_2 + 1901] += 6;
      v87[1900] += 6;
      v88[n5_2 + 1901] += 6;
      v88[1900] += 6;
      v77 = *(_DWORD *)(_this + 12);
      if ( (v77 & 7) != 7 )
      {
        v87[n5_2 + 1909] += 4;
        v87[1908] += 4;
        v88[n5_2 + 1909] += 4;
        v88[1908] += 4;
        v77 = *(_DWORD *)(_this + 12);
      }
      if ( (v77 & 7) != 0 )
      {
        v87[n5_2 + 1893] += 3;
        v87[1892] += 3;
        v88[n5_2 + 1893] += 3;
        v88[1892] += 3;
        v77 = *(_DWORD *)(_this + 12);
      }
    }
    else
    {
      v71 = _this + 16 * (*(_DWORD *)(_this - 4 * v70 + 156) + v69 - *(_DWORD *)(_this + 4 * v70 + 148));
      *(_WORD *)(v71 + 2 * n5_2 + 3802) += 7;
      *(_WORD *)(v71 + 3800) += 7;
      v72 = *(_DWORD *)(_this + 152);
      v73 = v72 + *(_DWORD *)(_this + 12) - *(_DWORD *)(_this + 4 * *(_DWORD *)(_this + 144) + 148);
      v74 = v8 + v72 - *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 144) + 156);
      v75 = (_WORD *)(_this + 16 * v73);
      v75[n5_2 + 1901] += 6;
      v75[1900] += 6;
      v76 = (_WORD *)(_this + 16 * v74);
      v76[n5_4 + 1901] += 4;
      v76[1900] += 4;
      v77 = *(_DWORD *)(_this + 12);
      if ( (v77 & 7) != 7 )
      {
        v75[n5_2 + 1909] += 4;
        v75[1908] += 4;
        v76[n5_4 + 1909] += 2;
        v76[1908] += 2;
        v77 = *(_DWORD *)(_this + 12);
      }
      if ( (v77 & 7) != 0 )
      {
        v75[n5_2 + 1893] += 3;
        v75[1892] += 3;
        v76[n5_4 + 1893] += 2;
        v76[1892] += 2;
        v77 = *(_DWORD *)(_this + 12);
      }
    }
    v78 = *(_DWORD *)(_this + 160);
    if ( v78 == 1 )
    {
      v83 = v77 - *(_DWORD *)(_this + 168);
      v84 = (_WORD *)(_this + 16 * (v83 + *(_DWORD *)(_this + 164)));
      result = _this + 16 * (*(_DWORD *)(_this + 172) + v83);
      v84[n5_2 + 1901] += 6;
      v84[1900] += 6;
      *(_WORD *)(result + 2 * n5_2 + 3802) += 6;
      *(_WORD *)(result + 3800) += 6;
      v85 = *(_DWORD *)(_this + 12);
      if ( (v85 & 7) != 7 )
      {
        v84[n5_2 + 1909] += 4;
        v84[1908] += 4;
        *(_WORD *)(result + 2 * n5_2 + 3818) += 4;
        *(_WORD *)(result + 3816) += 4;
        v85 = *(_DWORD *)(_this + 12);
      }
      if ( (v85 & 7) != 0 )
      {
        v84[n5_2 + 1893] += 3;
        v84[1892] += 3;
        *(_WORD *)(result + 2 * n5_2 + 3786) += 3;
        *(_WORD *)(result + 3784) += 3;
      }
    }
    else
    {
      v79 = _this + 16 * (*(_DWORD *)(_this - 4 * v78 + 172) + v77 - *(_DWORD *)(_this + 4 * v78 + 164));
      *(_WORD *)(v79 + 2 * n5_2 + 3802) += 7;
      *(_WORD *)(v79 + 3800) += 7;
      v80 = *(_DWORD *)(_this + 168);
      result = _this + 16 * (v80 + *(_DWORD *)(_this + 12) - *(_DWORD *)(_this + 4 * *(_DWORD *)(_this + 160) + 164));
      v81 = (_WORD *)(_this + 16 * (v80 - *(_DWORD *)(_this - 4 * *(_DWORD *)(_this + 160) + 172) + v8));
      *(_WORD *)(result + 2 * n5_2 + 3802) += 6;
      *(_WORD *)(result + 3800) += 6;
      v81[n5_4 + 1901] += 4;
      v81[1900] += 4;
      v82 = *(_DWORD *)(_this + 12);
      if ( (v82 & 7) != 7 )
      {
        *(_WORD *)(result + 2 * n5_2 + 3818) += 4;
        *(_WORD *)(result + 3816) += 4;
        v81[n5_4 + 1909] += 2;
        v81[1908] += 2;
        v82 = *(_DWORD *)(_this + 12);
      }
      if ( (v82 & 7) != 0 )
      {
        *(_WORD *)(result + 2 * n5_2 + 3786) += 3;
        *(_WORD *)(result + 3784) += 3;
        result = (unsigned __int16)v81[n5_4 + 1893] + 2;
        v81[n5_4 + 1893] = result;
        v81[1892] += 2;
      }
    }
  }
  return result;
}

#undef sub_413430
