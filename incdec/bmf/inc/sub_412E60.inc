// sub_412E60 @ 0x00412E60 — __fastcall
// Extracted from BMF.cpp:17123-17439 by extract.py per incdec.md.

typedef int t_sub_412E60_Buffer_0;
static t_sub_412E60_Buffer_0& __sub_412E60_Buffer_0 = *(t_sub_412E60_Buffer_0*)0x00443378;
typedef char t_sub_412E60_buf_0[0x10000];
static t_sub_412E60_buf_0& __sub_412E60_buf_0 = *(t_sub_412E60_buf_0*)0x00443440;
typedef char t_sub_412E60_byte_4456F0;
static t_sub_412E60_byte_4456F0& __sub_412E60_byte_4456F0 = *(t_sub_412E60_byte_4456F0*)0x004456F0;
typedef char t_sub_412E60_byte_445700;
static t_sub_412E60_byte_445700& __sub_412E60_byte_445700 = *(t_sub_412E60_byte_445700*)0x00445700;
typedef int t_sub_412E60_dword_4456E8;
static t_sub_412E60_dword_4456E8& __sub_412E60_dword_4456E8 = *(t_sub_412E60_dword_4456E8*)0x004456E8;
typedef int t_sub_412E60_n0x2000;
static t_sub_412E60_n0x2000& __sub_412E60_n0x2000 = *(t_sub_412E60_n0x2000*)0x004456FC;
typedef int t_sub_412E60_n0x2000_0;
static t_sub_412E60_n0x2000_0& __sub_412E60_n0x2000_0 = *(t_sub_412E60_n0x2000_0*)0x004456F8;
typedef int t_sub_412E60_n0x2000_1;
static t_sub_412E60_n0x2000_1& __sub_412E60_n0x2000_1 = *(t_sub_412E60_n0x2000_1*)0x004456F4;
typedef int t_sub_412E60_n0x7F800000;
static t_sub_412E60_n0x7F800000& __sub_412E60_n0x7F800000 = *(t_sub_412E60_n0x7F800000*)0x004456E4;
typedef int t_sub_412E60_n0x800000;
static t_sub_412E60_n0x800000& __sub_412E60_n0x800000 = *(t_sub_412E60_n0x800000*)0x004456E0;


PROBE_DECL(__sub_412E60)
BMF_REALIGN __attribute__((fastcall)) int __sub_412E60(_DWORD *a1)
{
  alignas(16) unsigned char __hexrays_frame[32824];   // original frame, ebp-0x8028..ebp+0x0
  unsigned __int16 * &v55 = *(unsigned __int16 * *)(__hexrays_frame + 0);
  unsigned __int16 * &v56 = *(unsigned __int16 * *)(__hexrays_frame + 4);
  int &v57 = *(int *)(__hexrays_frame + 8);
  signed int &v58 = *(signed int *)(__hexrays_frame + 12);
  BOOL &v59 = *(BOOL *)(__hexrays_frame + 16);
  unsigned int &n0x800000_1 = *(unsigned int *)(__hexrays_frame + 20);
  int &v61 = *(int *)(__hexrays_frame + 24);
  int &v62 = *(int *)(__hexrays_frame + 28);
  unsigned int &n0x7F800000_1 = *(unsigned int *)(__hexrays_frame + 32768);
  int &__sub_412E60_n0x2000 = *(int *)(__hexrays_frame + 32772);
  int &v65 = *(int *)(__hexrays_frame + 32776);
  unsigned __int16 * &v66 = *(unsigned __int16 * *)(__hexrays_frame + 32780);
  _DWORD * &v67 = *(_DWORD * *)(__hexrays_frame + 32784);
  _DWORD * &v68 = *(_DWORD * *)(__hexrays_frame + 32788);
  PROBE_HIT(__sub_412E60);
  void *v1; // esp
  int v2; // esi
  int v3; // edx
  unsigned __int16 **v4; // ebx
  int v5; // ebp
  int v6; // edi
  int v7; // eax
  int v8; // ecx
  _DWORD *v9; // ecx
  unsigned int __sub_412E60_n0x800000; // esi
  int __sub_412E60_n0x7F800000; // edx
  unsigned int n0x2000_6; // ebx
  unsigned int v13; // edx
  unsigned __int8 *Buffer; // edi
  int n0x7F800000_2; // ecx
  int v16; // ecx
  int v17; // edi
  unsigned int n0x2000_4; // eax
  int n0x2000_5; // ebp
  unsigned __int16 *v20; // ebp
  unsigned __int16 **v21; // ebx
  int n0x2000_2; // edx
  char v23; // cl
  unsigned int n0x2000_3; // eax
  unsigned __int16 *v25; // ebx
  unsigned __int16 **v26; // ebp
  unsigned int __sub_412E60_n0x2000_1; // ebx
  int v28; // ebp
  int n0x800000_3; // edi
  int n0x800000_2; // esi
  _DWORD *v32; // ecx
  unsigned __int16 *v33; // edx
  char v34; // dl
  unsigned __int16 v35; // di
  char *v36; // eax
  int n251; // ebx
  char *v38; // ebp
  __int16 v39; // si
  char v40; // dl
  unsigned int v41; // ebp
  unsigned int v42; // ebx
  unsigned __int16 *v43; // edi
  unsigned __int16 *v44; // edx
  unsigned __int16 *v45; // ebp
  signed int v46; // eax
  unsigned __int16 *v47; // esi
  unsigned __int16 *v48; // edi
  signed int v49; // edx
  unsigned int v50; // ebx
  int v51; // edx
  unsigned __int16 *v52; // eax
  int v53; // edx
  unsigned int v54; // ebp

  v68 = a1;
  v1 = alloca(32788);
  v2 = a1[1];
  v3 = a1[5];
  v4 = &v55;
  v68 = (_DWORD *)(unsigned __int8)__sub_412E60_byte_445700;
  v67 = a1;
  v5 = 0;
  v6 = 0;
  do
  {
    if ( (_DWORD *)(unsigned __int8)__sub_412E60_buf_0[*(unsigned __int16 *)(v3 + 3 * v6)] == v68 )
    {
      v8 = 0;
    }
    else
    {
      v7 = v3 + 3 * v6;
      v8 = *(unsigned __int8 *)(v7 + 2);
      *v4++ = (unsigned __int16 *)v7;
    }
    v5 += v8;
    ++v6;
  }
  while ( v6 < v2 );
  v9 = v67;
  if ( !v5 )
    return -1;
  __sub_412E60_n0x800000 = ::__sub_412E60_n0x800000;
  __sub_412E60_n0x7F800000 = ::__sub_412E60_n0x7F800000;
  *v4 = nullptr;
  v65 = v9[2];
  n0x7F800000_1 = __sub_412E60_n0x7F800000;
  n0x2000_6 = v5 + v65;
  ::__sub_412E60_n0x2000 = v5 + v65;
  if ( __sub_412E60_n0x800000 <= 0x800000 )
  {
    LOBYTE(v13) = __sub_412E60_byte_4456F0;
    Buffer = (unsigned __int8 *)__sub_412E60_Buffer_0;
    v67 = v9;
    n0x7F800000_2 = n0x7F800000_1;
    do
    {
      v16 = (unsigned __int8)((_BYTE)v13 << 7) | (n0x7F800000_2 << 8);
      v13 = *Buffer++;
      __sub_412E60_Buffer_0 = (int)Buffer;
      n0x7F800000_2 = (v13 >> 1) | v16;
      __sub_412E60_n0x800000 <<= 8;
    }
    while ( __sub_412E60_n0x800000 <= 0x800000 );
    n0x7F800000_1 = n0x7F800000_2;
    v9 = v67;
    __sub_412E60_byte_4456F0 = v13;
  }
  __sub_412E60_n0x2000 = v5 + v65;
  v67 = v9;
  v17 = __sub_412E60_n0x800000 / n0x2000_6;
  n0x2000_4 = n0x7F800000_1 / (__sub_412E60_n0x800000 / n0x2000_6);
  __sub_412E60_dword_4456E8 = __sub_412E60_n0x800000 / n0x2000_6;
  n0x2000_5 = v5 + v65 - 1;
  if ( n0x2000_4 >= n0x2000_6 )
    n0x2000_4 = n0x2000_5;
  v20 = v55;
  v21 = &v56;
  v66 = v55;
  n0x2000_2 = 0;
  while ( 1 )
  {
    n0x2000_2 += *((unsigned __int8 *)v20 + 2);
    if ( n0x2000_2 > (int)n0x2000_4 )
      break;
    v20 = *v21++;
    if ( !v20 )
    {
      v23 = (char)v68;
      ::__sub_412E60_n0x2000_1 = n0x2000_2;
      n0x2000_3 = __sub_412E60_n0x2000;
      __sub_412E60_n0x2000_0 = __sub_412E60_n0x2000;
      v25 = v66;
      v26 = &v56;
      do
      {
        __sub_412E60_buf_0[*v25] = v23;
        v25 = *v26++;
      }
      while ( v25 );
      __sub_412E60_n0x2000_1 = __sub_412E60_n0x2000;
      v62 = -1;
      goto LABEL_19;
    }
  }
  v32 = v67;
  __sub_412E60_n0x2000_0 = n0x2000_2;
  ::__sub_412E60_n0x2000_1 = n0x2000_2 - *((unsigned __int8 *)v20 + 2);
  v62 = *v20;
  *((_BYTE *)v20 + 2) += 4;
  v33 = (unsigned __int16 *)v32[5];
  v32[3] += 4;
  if ( v20 == v33 )
  {
    n251 = *((unsigned __int8 *)v20 + 2);
  }
  else
  {
    v34 = *((_BYTE *)v20 + 2);
    v61 = v17;
    v35 = *v20;
    v36 = (char *)v20 - 3;
    *v20 = *(unsigned __int16 *)((char *)v20 - 3);
    *((_BYTE *)v20 + 2) = *((_BYTE *)v20 - 1);
    *(_WORD *)v36 = v35;
    v17 = v61;
    v36[2] = v34;
    v33 = (unsigned __int16 *)v32[5];
    if ( (unsigned __int16 *)((char *)v20 - 3) == v33 )
    {
      n251 = *((unsigned __int8 *)v20 - 1);
    }
    else
    {
      n0x800000_1 = __sub_412E60_n0x800000;
      while ( 1 )
      {
        n251 = (unsigned __int8)v36[2];
        v38 = v36 - 3;
        if ( n251 <= (unsigned __int8)*(v36 - 1) )
          break;
        v39 = *(_WORD *)v36;
        v40 = v36[2];
        *(_WORD *)v36 = *(_WORD *)v38;
        v36[2] = *(v36 - 1);
        *(_WORD *)v38 = v39;
        *(v36 - 1) = v40;
        v33 = (unsigned __int16 *)v32[5];
        v36 -= 3;
        if ( v38 == (char *)v33 )
        {
          __sub_412E60_n0x800000 = n0x800000_1;
          n251 = (unsigned __int8)v38[2];
          goto LABEL_30;
        }
      }
      __sub_412E60_n0x800000 = n0x800000_1;
    }
  }
LABEL_30:
  v41 = v32[4];
  if ( n251 > 251 || v41 < v32[3] )
  {
    v55 = (unsigned __int16 *)v32[1];
    v42 = 20 * *v32;
    v61 = v17;
    v43 = v55;
    n0x800000_1 = __sub_412E60_n0x800000;
    v59 = v41 < v42;
    v44 = (unsigned __int16 *)((char *)v33 - 3);
    do
    {
      v45 = v44;
      v44 = (unsigned __int16 *)((char *)v44 + 3);
      v46 = (v59 + (unsigned int)*((unsigned __int8 *)v44 + 2)) >> 1;
      *((_BYTE *)v44 + 2) = v46;
      if ( v44 != (unsigned __int16 *)v32[5] )
      {
        v47 = (unsigned __int16 *)((char *)v44 - 3);
        v58 = *((unsigned __int8 *)v44 - 1);
        if ( v46 > v58 )
        {
          v57 = *v44;
          *v44 = *v47;
          *((_BYTE *)v44 + 2) = v58;
          if ( v47 != (unsigned __int16 *)v32[5] )
          {
            v56 = v44;
            v55 = v43;
            do
            {
              v48 = (unsigned __int16 *)((char *)v47 - 3);
              v49 = *((unsigned __int8 *)v47 - 1);
              if ( v46 <= v49 )
                break;
              *v47 = *v48;
              *((_BYTE *)v47 + 2) = v49;
              v47 = (unsigned __int16 *)((char *)v47 - 3);
            }
            while ( v48 != (unsigned __int16 *)v32[5] );
            v44 = v56;
            v43 = v55;
          }
          *v47 = v57;
          *((_BYTE *)v47 + 2) = v46;
        }
      }
      v43 = (unsigned __int16 *)((uintptr_t)v43 - (1));
    }
    while ( v43 );
    __sub_412E60_n0x800000 = n0x800000_1;
    v50 = v32[2];
    v51 = *((unsigned __int8 *)v44 + 2);
    v55 = nullptr;
    v17 = v61;
    if ( !v51 )
    {
      v52 = v55;
      do
      {
        v52 = (unsigned __int16 *)((char *)v52 + 1);
        v32[2] = ++v50;
        v53 = *((unsigned __int8 *)v45 + 2);
        v45 = (unsigned __int16 *)((char *)v45 - 3);
      }
      while ( !v53 );
      v55 = v52;
      v32[1] -= (unsigned int)v52;
    }
    v54 = v32[3];
    v32[2] = v50 - (v50 >> 1);
    n0x2000_2 = ::__sub_412E60_n0x2000_1;
    n0x2000_3 = __sub_412E60_n0x2000_0;
    __sub_412E60_n0x2000_1 = ::__sub_412E60_n0x2000;
    v32[3] = v54 - (v54 >> 1);
  }
  else
  {
    __sub_412E60_n0x2000_1 = ::__sub_412E60_n0x2000;
    n0x2000_2 = ::__sub_412E60_n0x2000_1;
    n0x2000_3 = __sub_412E60_n0x2000_0;
  }
LABEL_19:
  v28 = n0x2000_2 * v17;
  n0x800000_3 = (n0x2000_3 - n0x2000_2) * v17;
  ::__sub_412E60_n0x7F800000 = n0x7F800000_1 - v28;
  n0x800000_2 = __sub_412E60_n0x800000 - v28;
  if ( n0x2000_3 < __sub_412E60_n0x2000_1 )
    n0x800000_2 = n0x800000_3;
  ::__sub_412E60_n0x800000 = n0x800000_2;
  return v62;
}

