// sub_412B10 @ 0x00412B10 — __thiscall
// Extracted from BMF.c:16773-17063 by extract.py per incdec.md.

#ifndef __PE_DECL___Buffer_0
#define __PE_DECL___Buffer_0
typedef int t_Buffer_0;
static t_Buffer_0& __Buffer_0 = *(t_Buffer_0*)0x00443378;
#endif
#define Buffer_0 __Buffer_0
#ifndef __PE_DECL___buf_0
#define __PE_DECL___buf_0
typedef char t_buf_0[0x10000];
static t_buf_0& __buf_0 = *(t_buf_0*)0x00443440;
#endif
#define buf_0 __buf_0
#ifndef __PE_DECL___byte_4456F0
#define __PE_DECL___byte_4456F0
typedef char t_byte_4456F0;
static t_byte_4456F0& __byte_4456F0 = *(t_byte_4456F0*)0x004456F0;
#endif
#define byte_4456F0 __byte_4456F0
#ifndef __PE_DECL___byte_445700
#define __PE_DECL___byte_445700
typedef char t_byte_445700;
static t_byte_445700& __byte_445700 = *(t_byte_445700*)0x00445700;
#endif
#define byte_445700 __byte_445700
#ifndef __PE_DECL___dword_4456E8
#define __PE_DECL___dword_4456E8
typedef int t_dword_4456E8;
static t_dword_4456E8& __dword_4456E8 = *(t_dword_4456E8*)0x004456E8;
#endif
#define dword_4456E8 __dword_4456E8
#ifndef __PE_DECL___dword_4456EC
#define __PE_DECL___dword_4456EC
typedef int t_dword_4456EC;
static t_dword_4456EC& __dword_4456EC = *(t_dword_4456EC*)0x004456EC;
#endif
#define dword_4456EC __dword_4456EC
#ifndef __PE_DECL___dword_4456F4
#define __PE_DECL___dword_4456F4
typedef int t_dword_4456F4;
static t_dword_4456F4& __dword_4456F4 = *(t_dword_4456F4*)0x004456F4;
#endif
#define dword_4456F4 __dword_4456F4
#ifndef __PE_DECL___n0x2000
#define __PE_DECL___n0x2000
typedef int t_n0x2000;
static t_n0x2000& __n0x2000 = *(t_n0x2000*)0x004456FC;
#endif
#define n0x2000 __n0x2000
#ifndef __PE_DECL___n0x2000_0
#define __PE_DECL___n0x2000_0
typedef int t_n0x2000_0;
static t_n0x2000_0& __n0x2000_0 = *(t_n0x2000_0*)0x004456F8;
#endif
#define n0x2000_0 __n0x2000_0
#ifndef __PE_DECL___n0x7F800000
#define __PE_DECL___n0x7F800000
typedef int t_n0x7F800000;
static t_n0x7F800000& __n0x7F800000 = *(t_n0x7F800000*)0x004456E4;
#endif
#define n0x7F800000 __n0x7F800000
#ifndef __PE_DECL___n0x800000
#define __PE_DECL___n0x800000
typedef int t_n0x800000;
static t_n0x800000& __n0x800000 = *(t_n0x800000*)0x004456E0;
#endif
#define n0x800000 __n0x800000


PROBE_DECL(__sub_412B10)
__attribute__((thiscall)) int __sub_412B10(unsigned int *_this, int a2)
{
  PROBE_HIT(__sub_412B10);
  char v2; // al
  int v3; // ebx
  unsigned __int16 *v4; // ebp
  int v5; // edx
  int v6; // esi
  int v7; // edi
  int v8; // esi
  unsigned int n0x800000; // ecx
  int n0x7F800000; // ebx
  int v11; // ebp
  unsigned int v12; // edi
  int v13; // esi
  int v14; // eax
  unsigned int v15; // edx
  _BYTE *v16; // ecx
  unsigned int v17; // eax
  unsigned int v18; // ebp
  int n0x800000_2; // ecx
  int n0x800000_3; // eax
  unsigned int i_1; // ebx
  unsigned int i; // esi
  int v24; // ecx
  unsigned __int16 *v25; // edx
  unsigned __int16 v26; // di
  char v27; // al
  char *v28; // ebx
  char v29; // dl
  int n251; // eax
  unsigned __int16 v31; // di
  char v32; // al
  char v33; // dl
  unsigned int v34; // ebx
  int v35; // edi
  char *v36; // edx
  char *v37; // ebp
  signed int v38; // eax
  char *v39; // esi
  char *v40; // edi
  signed int v41; // edx
  unsigned int v42; // eax
  int v43; // edx
  unsigned int v44; // ebx
  int v45; // [esp+0h] [ebp-24h]
  unsigned int *this_1; // [esp+0h] [ebp-24h]
  int v47; // [esp+0h] [ebp-24h]
  unsigned int n0x800000_1; // [esp+4h] [ebp-20h]
  char *v49; // [esp+4h] [ebp-20h]
  char v50; // [esp+8h] [ebp-1Ch]
  __int16 v51; // [esp+8h] [ebp-1Ch]
  int v52; // [esp+Ch] [ebp-18h]
  signed int v53; // [esp+Ch] [ebp-18h]
  BOOL v54; // [esp+10h] [ebp-14h]

  v2 = byte_445700;
  v3 = *(_this + 1);
  v4 = (unsigned __int16 *)(*(_this + 5) - 3);
  v5 = 0;
  while ( 1 )
  {
    v4 = (unsigned __int16 *)((char *)v4 + 3);
    v6 = *v4;
    if ( buf_0[v6] != byte_445700 )
    {
      v7 = *((unsigned __int8 *)v4 + 2);
      v5 += v7;
      if ( v6 == a2 )
        break;
    }
    if ( !--v3 )
    {
      if ( !v5 )
        return 0;
      dword_4456F4 = v5;
      n0x2000 = *(_this + 2) + v5;
      n0x2000_0 = n0x2000;
      do
      {
        buf_0[*v4] = v2;
        v4 = (unsigned __int16 *)((char *)v4 - 3);
      }
      while ( (unsigned int)v4 >= *(_this + 5) );
      v8 = 0;
      goto LABEL_9;
    }
  }
  n0x2000_0 = v5;
  i_1 = v3 - 1;
  dword_4456F4 = v5 - v7;
  if ( i_1 )
  {
    this_1 = _this;
    for ( i = 0; i < i_1; ++i )
    {
      if ( buf_0[*(unsigned __int16 *)((char *)v4 + 3 * i + 3)] == byte_445700 )
        v24 = 0;
      else
        v24 = *((unsigned __int8 *)v4 + 3 * i + 5);
      v5 += v24;
    }
    _this = this_1;
  }
  n0x2000 = *(_this + 2) + v5;
  *((_BYTE *)v4 + 2) += 4;
  v25 = (unsigned __int16 *)*(_this + 5);
  *(_this + 3) += 4;
  if ( v4 == v25 )
  {
LABEL_37:
    n251 = *((unsigned __int8 *)v4 + 2);
  }
  else
  {
    v26 = *v4;
    v27 = *((_BYTE *)v4 + 2);
    v28 = (char *)v4 - 3;
    v29 = *((_BYTE *)v4 - 1);
    *v4 = *(unsigned __int16 *)((char *)v4 - 3);
    *((_BYTE *)v4 + 2) = v29;
    *(_WORD *)v28 = v26;
    v28[2] = v27;
    v25 = (unsigned __int16 *)*(_this + 5);
    if ( (unsigned __int16 *)((char *)v4 - 3) == v25 )
    {
      n251 = *((unsigned __int8 *)v4 - 1);
    }
    else
    {
      while ( 1 )
      {
        n251 = (unsigned __int8)v28[2];
        v4 = (unsigned __int16 *)(v28 - 3);
        if ( n251 <= (unsigned __int8)*(v28 - 1) )
          break;
        v31 = *(_WORD *)v28;
        v32 = v28[2];
        v33 = *(v28 - 1);
        *(_WORD *)v28 = *v4;
        v28[2] = v33;
        *v4 = v31;
        *(v28 - 1) = v32;
        v25 = (unsigned __int16 *)*(_this + 5);
        v28 -= 3;
        if ( v4 == v25 )
          goto LABEL_37;
      }
    }
  }
  v34 = *(_this + 4);
  if ( n251 > 251 || v34 < *(_this + 3) )
  {
    v35 = *(_this + 1);
    v54 = v34 < 20 * *_this;
    v36 = (char *)v25 - 3;
    do
    {
      v37 = v36;
      v36 += 3;
      v38 = (v54 + (unsigned int)(unsigned __int8)v36[2]) >> 1;
      v36[2] = v38;
      if ( v36 != (char *)*(_this + 5) )
      {
        v39 = v36 - 3;
        v53 = (unsigned __int8)*(v36 - 1);
        if ( v38 > v53 )
        {
          v51 = *(_WORD *)v36;
          *(_WORD *)v36 = *(_WORD *)v39;
          v36[2] = v53;
          if ( v39 != (char *)*(_this + 5) )
          {
            v49 = v36;
            v47 = v35;
            do
            {
              v40 = v39 - 3;
              v41 = (unsigned __int8)*(v39 - 1);
              if ( v38 <= v41 )
                break;
              *(_WORD *)v39 = *(_WORD *)v40;
              v39[2] = v41;
              v39 -= 3;
            }
            while ( v40 != (char *)*(_this + 5) );
            v36 = v49;
            v35 = v47;
          }
          *(_WORD *)v39 = v51;
          v39[2] = v38;
        }
      }
      --v35;
    }
    while ( v35 );
    v42 = *(_this + 2);
    if ( !v36[2] )
    {
      do
      {
        ++v35;
        *(_this + 2) = ++v42;
        v43 = (unsigned __int8)v37[2];
        v37 -= 3;
      }
      while ( !v43 );
      *(_this + 1) -= v35;
    }
    v44 = *(_this + 3);
    *(_this + 2) = v42 - (v42 >> 1);
    *(_this + 3) = v44 - (v44 >> 1);
    v8 = 1;
  }
  else
  {
    v8 = 1;
  }
LABEL_9:
  n0x800000 = ::n0x800000;
  n0x7F800000 = ::n0x7F800000;
  if ( (unsigned int)::n0x800000 > 0x800000 )
    goto LABEL_23;
  v11 = dword_4456E8;
  v45 = v8;
  v52 = dword_4456EC;
  do
  {
    ++v52;
    v12 = v11;
    v13 = v11;
    if ( (unsigned int)n0x7F800000 < 0x7F800000 )
    {
      v50 = 0;
    }
    else
    {
      if ( n0x7F800000 >= 0 )
      {
        dword_4456E8 = ++v11;
        goto LABEL_21;
      }
      v50 = 1;
    }
    *(_BYTE *)Buffer_0 = v50 + byte_4456F0;
    v14 = ++Buffer_0;
    if ( v11 )
    {
      n0x800000_1 = n0x800000;
      v15 = 0;
      v16 = (_BYTE *)v14;
      do
      {
        *v16 = v50 - 1;
        v16 = (_BYTE *)++Buffer_0;
        v11 = v13 - v15++ - 1;
      }
      while ( v15 < v12 );
      n0x800000 = n0x800000_1;
      dword_4456E8 = v13 - v12;
    }
    byte_4456F0 = (unsigned int)n0x7F800000 >> 23;
LABEL_21:
    n0x800000 <<= 8;
    n0x7F800000 = (n0x7F800000 << 8) & 0x7FFFFFFF;
  }
  while ( n0x800000 <= 0x800000 );
  v8 = v45;
  dword_4456EC = v52;
LABEL_23:
  v17 = n0x800000 / n0x2000;
  v18 = dword_4456F4 * (n0x800000 / n0x2000);
  n0x800000_2 = n0x800000 - v18;
  n0x800000_3 = (n0x2000_0 - dword_4456F4) * v17;
  if ( n0x2000_0 < (unsigned int)n0x2000 )
    n0x800000_2 = n0x800000_3;
  ::n0x800000 = n0x800000_2;
  ::n0x7F800000 = n0x7F800000 + v18;
  return v8;
}

#undef Buffer_0
#undef buf_0
#undef byte_4456F0
#undef byte_445700
#undef dword_4456E8
#undef dword_4456EC
#undef dword_4456F4
#undef n0x2000
#undef n0x2000_0
#undef n0x7F800000
#undef n0x800000
