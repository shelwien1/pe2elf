// sub_40F450 @ 0x0040F450 — __userpurge
// Extracted from BMF.c:13255-13665 by extract.py per incdec.md.

typedef int t_sub_40F450_buf[0x10000];
static t_sub_40F450_buf& __sub_40F450_buf = *(t_sub_40F450_buf*)0x00443380;
typedef __int128 t_sub_40F450_xmmword_439590;
static t_sub_40F450_xmmword_439590& __sub_40F450_xmmword_439590 = *(t_sub_40F450_xmmword_439590*)0x00439590;
typedef __int128 t_sub_40F450_xmmword_4395A0;
static t_sub_40F450_xmmword_4395A0& __sub_40F450_xmmword_4395A0 = *(t_sub_40F450_xmmword_4395A0*)0x004395A0;
typedef __int128 t_sub_40F450_xmmword_4395B0;
static t_sub_40F450_xmmword_4395B0& __sub_40F450_xmmword_4395B0 = *(t_sub_40F450_xmmword_4395B0*)0x004395B0;
typedef __int128 t_sub_40F450_xmmword_4395C0;
static t_sub_40F450_xmmword_4395C0& __sub_40F450_xmmword_4395C0 = *(t_sub_40F450_xmmword_4395C0*)0x004395C0;

#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980

PROBE_DECL(__sub_40F450)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) char * __sub_40F450(_DWORD *Blockb, char a2, int a3, int a4, int a5)
{
  PROBE_HIT(__sub_40F450);
  unsigned int n7; // eax
  __m128i si128; // xmm1
  __m128i v8; // xmm0
  unsigned int i; // eax
  unsigned int n7_1; // edx
  int v11; // eax
  char v12; // cl
  __m128i v13; // xmm1
  __m128i v14; // xmm0
  unsigned int j; // eax
  _BYTE *v16; // edx
  _BYTE *v17; // esi
  int v18; // ecx
  char v19; // al
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // ecx
  char *__sub_40F450_buf; // eax
  int v25; // ecx
  _BYTE *v26; // esi
  int v27; // eax
  char v28; // dl
  int v29; // edx
  _DWORD *v30; // edi
  int v31; // edi
  int v32; // edx
  int v33; // edi
  int v34; // ecx
  unsigned __int8 *v35; // edx
  int v36; // eax
  int v37; // edi
  unsigned __int8 *v38; // ebx
  int v39; // esi
  int v40; // esi
  int v41; // edi
  int v42; // eax
  _DWORD *v43; // ebx
  int v44; // ecx
  int v45; // edi
  int v46; // ecx
  int v47; // edi
  int v48; // esi
  int v49; // ecx
  int v50; // eax
  int v51; // esi
  _DWORD *v52; // edi
  int v53; // eax
  int v54; // ecx
  int v55; // ecx
  int v56; // esi
  int v57; // ebx
  int v58; // eax
  int v59; // edx
  int v60; // esi
  int v61; // eax
  int v62; // esi
  int v63; // eax
  int v64; // eax
  int v65; // esi
  int v66; // edx
  int v67; // eax
  int v68; // edx
  int v69; // ecx
  int v70; // edx
  int v71; // eax
  unsigned __int8 *v72; // edx
  int v73; // esi
  int v74; // eax
  int v75; // edi
  _DWORD *v76; // esi
  int v77; // edx
  int v78; // ecx
  int v79; // eax
  unsigned __int8 *v80; // ecx
  int v81; // esi
  int v82; // ecx
  int v83; // eax
  int v84; // ecx
  char v85; // al
  int n6; // esi
  int v87; // edi
  int v88; // ecx
  char v89; // dl
  int v90; // esi
  int v91; // esi
  char v92; // di
  int v93; // ecx
  int v94; // esi
  _BYTE *v95; // esi
  char *buf_3; // ecx
  int v97; // edx
  _BYTE v98[256]; // [esp+0h] [ebp-170h]
  int v99; // [esp+100h] [ebp-70h]
  char *buf_1; // [esp+104h] [ebp-6Ch]
  int v101; // [esp+108h] [ebp-68h]
  int v102; // [esp+10Ch] [ebp-64h]
  _DWORD *v103; // [esp+110h] [ebp-60h]
  _DWORD *v104; // [esp+114h] [ebp-5Ch]
  _DWORD *v105; // [esp+118h] [ebp-58h]
  _DWORD *v106; // [esp+11Ch] [ebp-54h]
  int v107; // [esp+120h] [ebp-50h]
  int v108; // [esp+124h] [ebp-4Ch]
  _BYTE *v109; // [esp+128h] [ebp-48h]
  char *buf_2; // [esp+12Ch] [ebp-44h]
  int v111; // [esp+130h] [ebp-40h]
  _DWORD *v112; // [esp+134h] [ebp-3Ch]
  unsigned __int8 *v113; // [esp+138h] [ebp-38h]
  int v114; // [esp+13Ch] [ebp-34h]
  int v115; // [esp+140h] [ebp-30h]
  int v116; // [esp+144h] [ebp-2Ch]
  _DWORD *Blockb_1; // [esp+148h] [ebp-28h]
  int v118; // [esp+14Ch] [ebp-24h]
  int v119; // [esp+150h] [ebp-20h]
  int v120; // [esp+154h] [ebp-1Ch]
  int v121; // [esp+158h] [ebp-18h]

  n7 = 0;
  v109 = (_BYTE *)(a3 + 1);
  v98[0] = 0;
  v98[128] = -1;
  do
  {
    v98[2 * n7 + 1] = 4 * n7 + 2;
    v98[2 * n7 + 2] = 4 * n7 + 4;
    ++n7;
  }
  while ( n7 < 7 );
  si128 = _mm_load_si128((const __m128i *)&__sub_40F450_xmmword_439590);
  v8 = _mm_load_si128((const __m128i *)&__sub_40F450_xmmword_4395A0);
  v98[15] = 30;
  for ( i = 15; i < 0x7F; i += 16 )
  {
    *(__m128i *)&v98[i + 1] = v8;
    v8 = _mm_add_epi8(v8, si128);
  }
  n7_1 = 0;
  v11 = 0;
  do
  {
    v98[2 * n7_1 + 129] = 2 * v11 - 3;
    v12 = 2 * v11 - 5;
    v11 -= 2;
    v98[2 * n7_1++ + 130] = v12;
  }
  while ( n7_1 < 7 );
  v13 = _mm_load_si128((const __m128i *)&__sub_40F450_xmmword_4395B0);
  v14 = _mm_load_si128((const __m128i *)&__sub_40F450_xmmword_4395C0);
  v98[143] = -31;
  for ( j = 15; j < 0x7F; j += 16 )
  {
    *(__m128i *)&v98[j + 129] = v14;
    v14 = _mm_add_epi8(v14, v13);
  }
  v16 = (_BYTE *)Blockb[17];
  if ( a4 > 1 )
  {
    v17 = v109;
    v18 = 1;
    do
    {
      v19 = *v17;
      *v16 = *v17;
      *v17 = v98[(unsigned __int8)(v19 - *(_BYTE *)(Blockb[17] - 1))];
      v20 = Blockb[*(unsigned __int8 *)Blockb[17] - *(unsigned __int8 *)(Blockb[17] - 1) + 2091];
      *(_DWORD *)(Blockb[23] + 4) = v20;
      *(_DWORD *)Blockb[23] = v20;
      v21 = Blockb[17];
      Blockb[23] += 8;
      ++v18;
      ++v17;
      v16 = (_BYTE *)(v21 + 1);
      Blockb[17] = v16;
    }
    while ( v18 < a4 );
    v109 = v17;
  }
  v22 = (unsigned __int8)*(v16 - 1);
  *v16 = v22;
  v23 = Blockb[23];
  Blockb[16] = v22;
  Blockb[21] = *(_DWORD *)(v23 - 8);
  Blockb[22] = *(_DWORD *)(v23 - 4);
  __sub_40F450_buf = sub_434980((char *)Blockb[20],(char *)Blockb[19],a4 + 2);
  v25 = a5 - 1;
  if ( a5 != 1 )
  {
    buf_1 = (char *)(a4 - 1);
    v103 = Blockb + 807;
    v104 = Blockb + 287;
    v105 = Blockb + 27;
    v26 = v109;
    v106 = Blockb + 547;
    do
    {
      while ( 1 )
      {
        v27 = (unsigned __int8)*v26;
        v28 = *((_BYTE *)Blockb + 64);
        *(_BYTE *)(Blockb[17] - 1) = v28;
        *(_BYTE *)Blockb[17] = v28;
        v29 = Blockb[23];
        *(_DWORD *)(v29 - 8) = Blockb[21];
        *(_DWORD *)(v29 - 4) = Blockb[22];
        v30 = (_DWORD *)Blockb[23];
        *v30 = *(v30 - 2);
        v30[1] = *(v30 - 1);
        v31 = Blockb[19];
        v32 = Blockb[20];
        Blockb[19] = v32;
        Blockb[20] = v31;
        v32 += 2;
        Blockb[17] = v32;
        Blockb[18] = v31 + 2;
        Blockb[16] = v27;
        *(_BYTE *)(v32 - 2) = v27;
        Blockb[23] = Blockb[24] + 8;
        v33 = Blockb[18];
        Blockb[21] = -Blockb[v27 - *(unsigned __int8 *)(v33 - 1) + 2091];
        Blockb[22] = 0;
        *v26 = v98[(unsigned __int8)(*v26 - *(_BYTE *)(v33 - 1))];
        __sub_40F450_buf = buf_1;
        ++v26;
        if ( a4 != 1 )
          break;
        if ( !--v25 )
          return __sub_40F450_buf;
      }
      buf_2 = buf_1;
      v99 = v25;
      v109 = v26;
      do
      {
        v34 = Blockb[16];
        v35 = (unsigned __int8 *)Blockb[18];
        v36 = *v35;
        v37 = *(v35 - 1);
        Blockb_1 = Blockb;
        v38 = (unsigned __int8 *)Blockb[17];
        v39 = *v38;
        v114 = v34;
        v40 = v37 + v39;
        v41 = v35[1];
        v118 = v36;
        v113 = v38;
        v42 = v34 + v36;
        v119 = (16 * (v42 + v41) + -3 * (v40 - *(v38 - 2)) + 8 * v42 + 4 * v34 - v118 + 31) >> 6;
        v43 = (_DWORD *)Blockb_1[23];
        v44 = Blockb_1[21];
        v45 = v43[2] + *v43;
        v112 = v43;
        v111 = v44;
        v46 = v45 + *(v43 - 2) + v44;
        Blockb = Blockb_1;
        v47 = v119;
        if ( v46 <= 0 )
        {
          v107 = -v46;
          Blockb_1[25] = v104;
          v49 = v107;
          v48 = v114 + ((*v35 - *(v35 - 1) + 2) >> 2);
        }
        else
        {
          v107 = v46;
          Blockb_1[25] = v105;
          v48 = *v35 + ((v42 - v40 + 4) >> 3);
          v49 = v107;
        }
        v120 = v42;
        Blockb[3] = v47;
        Blockb[7] = v48;
        v50 = (v47 + v48) >> 1;
        Blockb[5] = v50;
        Blockb[4] = (v50 + v47) >> 1;
        v51 = (v50 + v48) >> 1;
        v52 = v112;
        v53 = v120;
        Blockb[6] = v51;
        v54 = *(unsigned __int8 *)(Blockb[25] + v49 + 16);
        *Blockb = v54;
        v55 = Blockb[v54 + 2];
        v56 = Blockb[22] + v52[3] + v52[1];
        if ( v56 < 0 )
        {
          v108 = -v56;
          Blockb[26] = v103;
          v65 = *(v35 - 1);
          v66 = *(v35 - 2);
          v115 = 2 * v55;
          v67 = 2 * v65 - *(v113 - 1) + v53 - 2 * v55 - v66 + 2;
          v62 = v108;
          v63 = v67 >> 2;
        }
        else
        {
          Blockb_1 = Blockb;
          v108 = v56;
          Blockb[26] = v106;
          v57 = *(v35 - 1);
          v58 = v35[1];
          v59 = *v35;
          v115 = 2 * v55;
          v60 = 2 * v58 - 2 * v55 - v113[1] - (v57 - v58);
          Blockb = Blockb_1;
          v61 = v60 + v59 + 4;
          v62 = v108;
          v63 = v61 >> 3;
        }
        v64 = v55 + v63;
        v68 = v115;
        Blockb[10] = v55;
        Blockb[14] = v64;
        v69 = v55 + v64 + 1;
        Blockb[11] = (v69 + v68) >> 2;
        Blockb[12] = v69 >> 1;
        v70 = v69 + 2 * v64;
        v71 = Blockb[26];
        Blockb[13] = v70 >> 2;
        v72 = v109;
        v73 = *(unsigned __int8 *)(v71 + v62 + 16);
        v74 = v111;
        Blockb[1] = v73;
        v75 = Blockb[v73 + 9];
        v76 = v112;
        v77 = *v72;
        *(v112 - 2) = v74;
        v78 = Blockb[22];
        v121 = v75;
        *(v76 - 1) = v78;
        v79 = Blockb[16];
        v80 = (unsigned __int8 *)Blockb[18];
        Blockb[21] = Blockb[v77 - v79 + 2091] - Blockb[v77 - *v80 + 2091];
        v81 = Blockb[v77 - *(v80 - 1) + 2091] - Blockb[v77 - v80[1] + 2091];
        v82 = Blockb[17];
        Blockb[22] = v81;
        *(_BYTE *)(v82 - 1) = v79;
        v83 = Blockb[1];
        Blockb[16] = v77;
        ++Blockb[17];
        v116 = v83;
        ++Blockb[18];
        Blockb[23] += 8;
        v84 = Blockb[v83 + 9];
        v85 = v121;
        n6 = Blockb[v77 - v84 + 2091];
        if ( n6 >= 6 )
        {
          v87 = *Blockb;
          v101 = Blockb[v77 - Blockb[10] + 2091] - 1;
          v102 = v87;
          if ( v101 <= Blockb[v77 - Blockb[v87 + 1] + 2091] )
          {
            if ( v101 <= Blockb[v77 - Blockb[v102 + 3] + 2091] )
            {
              v91 = n6 - 1;
              if ( v91 <= Blockb[v77 - Blockb[v116 + 8] + 2091] )
              {
                if ( v91 > Blockb[v77 - Blockb[v116 + 10] + 2091] )
                {
                  v92 = v116;
                  v93 = Blockb[26];
                  v94 = *(_DWORD *)(v93 + 4 * v116 - 4) - 1;
                  *(_DWORD *)(v93 + 4 * v116 - 4) = v94;
                  *(_BYTE *)(Blockb[26] + v94 + 16) = v92 + 1;
                }
              }
              else
              {
                *(_BYTE *)(*(_DWORD *)(Blockb[26] + 4 * v116 - 8) + Blockb[26] + 16) = v116 - 1;
                ++*(_DWORD *)(Blockb[26] + 4 * Blockb[1] - 8);
              }
            }
            else
            {
              v88 = Blockb[25];
              v89 = v102 + 1;
              v90 = *(_DWORD *)(v88 + 4 * v102 - 4) - 1;
              *(_DWORD *)(v88 + 4 * v102 - 4) = v90;
              *(_BYTE *)(Blockb[25] + v90 + 16) = v89;
            }
          }
          else
          {
            *(_BYTE *)(*(_DWORD *)(Blockb[25] + 4 * v102 - 8) + Blockb[25] + 16) = v102 - 1;
            ++*(_DWORD *)(Blockb[25] + 4 * *Blockb - 8);
          }
        }
        v95 = v109;
        buf_3 = buf_2;
        v97 = (unsigned __int8)v98[(unsigned __int8)(*v109 - v85)];
        *v109 = v97;
        __sub_40F450_buf = (char *)::__sub_40F450_buf;
        v26 = v95 + 1;
        v109 = v26;
        ++*(_DWORD *)&::__sub_40F450_buf[4 * v97];
        buf_2 = buf_3 - 1;
      }
      while ( buf_3 != (char *)1 );
      v25 = v99 - 1;
    }
    while ( v99 != 1 );
  }
  return __sub_40F450_buf;
}

// __userpurge thunk for sub_40F450 @ 0x0040F450: reads the register arguments the
// caller passes, calls the moved body as cdecl, and pops 12 bytes of
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_40F450()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $28, %esp\n"
    "mov %ecx, 12(%esp)\n"
    "fnstsw %ax\n"
    "mov %eax, 16(%esp)\n"
    "push 16(%ebp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "push 28(%esp)\n"
    "push 28(%esp)\n"
    "call __sub_40F450\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret $12\n"
  );
}

#undef sub_434980
