// sub_416C90 @ 0x00416C90 — __thiscall
// Extracted from BMF.c:21081-21320 by extract.py per incdec.md.

typedef char t_sub_416C90_buf_0[0x10000];
static t_sub_416C90_buf_0& __sub_416C90_buf_0 = *(t_sub_416C90_buf_0*)0x00443440;
#define buf_0 __sub_416C90_buf_0
typedef char t_sub_416C90_byte_445700;
static t_sub_416C90_byte_445700& __sub_416C90_byte_445700 = *(t_sub_416C90_byte_445700*)0x00445700;
#define byte_445700 __sub_416C90_byte_445700
typedef int t_sub_416C90_n15;
static t_sub_416C90_n15& __sub_416C90_n15 = *(t_sub_416C90_n15*)0x00445748;
#define n15 __sub_416C90_n15
typedef int t_sub_416C90_n15_0;
static t_sub_416C90_n15_0& __sub_416C90_n15_0 = *(t_sub_416C90_n15_0*)0x0044574C;
#define n15_0 __sub_416C90_n15_0
typedef int t_sub_416C90_n4_3;
static t_sub_416C90_n4_3& __sub_416C90_n4_3 = *(t_sub_416C90_n4_3*)0x00445744;
#define n4_3 __sub_416C90_n4_3
typedef int t_sub_416C90_n4_4;
static t_sub_416C90_n4_4& __sub_416C90_n4_4 = *(t_sub_416C90_n4_4*)0x00445740;
#define n4_4 __sub_416C90_n4_4

#define sub_413230 __sub_413230

PROBE_DECL(__sub_416C90)
__attribute__((thiscall)) int __sub_416C90(int _this)
{
  PROBE_HIT(__sub_416C90);
  int n2_1; // eax
  int v3; // eax
  _DWORD **v4; // eax
  _DWORD *v5; // ebp
  __int16 v6; // ax
  int v7; // edx
  int v8; // ecx
  int v9; // esi
  int v10; // edi
  __int16 *v11; // ecx
  __int16 v12; // si
  char v13; // dl
  char v14; // al
  int v15; // eax
  char *buf; // edx
  int v17; // eax
  int n2; // eax
  int v19; // edx
  unsigned __int16 *v20; // eax
  int v21; // esi
  int v22; // ecx
  int v23; // esi
  int v24; // ecx
  int v25; // esi
  int v26; // ecx
  int v27; // esi
  int v28; // ecx
  int v29; // ebp
  int v30; // esi
  int result; // eax
  int v32; // [esp+8h] [ebp-10h]

  n2_1 = *(_DWORD *)(_this + 32);
  if ( !n2_1 )
  {
    if ( _this + 1078216 == *(_DWORD *)(_this + 1078232) )
    {
      if ( *(_DWORD *)(_this + 1078216) )
      {
        sub_413230((unsigned int *)(*(_DWORD *)(_this + 1078212) + 24 * n4_4), **(unsigned __int16 **)(_this + 76), 3u);
        sub_413230((unsigned int *)(*(_DWORD *)(_this + 1078212) + 24 * **(unsigned __int16 **)(_this + 76)), n4_3, 2u);
        sub_413230((unsigned int *)(*(_DWORD *)(_this + 1078208) + 24 * n4_4), **(unsigned __int16 **)(_this + 76), 4u);
        sub_413230((unsigned int *)(*(_DWORD *)(_this + 1078208) + 24 * **(unsigned __int16 **)(_this + 76)), n4_4, 2u);
      }
      else
      {
        sub_413230(
          (unsigned int *)(*(_DWORD *)(_this + 1078212) + 24 * n4_3),
          **(unsigned __int16 **)(_this + 76),
          (*(_DWORD *)(_this + 44) > 3) + 2);
      }
    }
    else
    {
      sub_413230((unsigned int *)(*(_DWORD *)(_this + 1078212) + 24 * n4_4), **(unsigned __int16 **)(_this + 76), 3u);
      sub_413230((unsigned int *)(*(_DWORD *)(_this + 1078212) + 24 * **(unsigned __int16 **)(_this + 76)), n4_3, 2u);
      sub_413230((unsigned int *)(*(_DWORD *)(_this + 1078212) + 24 * **(unsigned __int16 **)(_this + 76)), n4_4, 1u);
      sub_413230((unsigned int *)(*(_DWORD *)(_this + 1078208) + 24 * **(unsigned __int16 **)(_this + 76)), n4_4, 2u);
      v3 = *(_DWORD *)(_this + 1078232);
      do
      {
        v4 = (_DWORD **)(v3 - 4);
        *(_DWORD *)(_this + 1078232) = v4;
        v5 = *v4;
        v6 = **(_WORD **)(_this + 76);
        v7 = v5[1];
        v32 = v5[5];
        if ( v7 == *v5 )
        {
          v8 = v5[5];
          v5[1] = --v7;
          v9 = *(unsigned __int8 *)(v8 + 3 * v7 + 2);
        }
        else
        {
          v9 = 1;
        }
        v10 = v5[2];
        v11 = (__int16 *)(v32 + 3 * v7);
        v5[1] = v7 + 1;
        v5[2] = v9 + v10 + 1;
        *v11 = v6;
        *((_BYTE *)v11 + 2) = 2;
        v5[3] += 4;
        if ( v11 != (__int16 *)v5[5] )
        {
          v12 = *v11;
          v13 = *((_BYTE *)v11 + 2);
          v14 = *((_BYTE *)v11 - 1);
          *v11 = *(__int16 *)((char *)v11 - 3);
          *((_BYTE *)v11 + 2) = v14;
          *(__int16 *)((char *)v11 - 3) = v12;
          *((_BYTE *)v11 - 1) = v13;
        }
        v3 = *(_DWORD *)(_this + 1078232);
      }
      while ( v3 != _this + 1078216 );
    }
    if ( byte_445700 == -1 )
    {
      v15 = *(_DWORD *)(_this + 16);
      byte_445700 = 1;
      buf = buf_0;
      v17 = (v15 + 15) >> 4;
      do
      {
        *((_DWORD *)buf + 3) = 0;
        *((_DWORD *)buf + 2) = 0;
        *((_DWORD *)buf + 1) = 0;
        *(_DWORD *)buf = 0;
        buf += 16;
        --v17;
      }
      while ( v17 );
      n2 = *(_DWORD *)(_this + 32);
    }
    else
    {
      ++byte_445700;
      n2 = *(_DWORD *)(_this + 32);
    }
LABEL_19:
    if ( n2 && n2 <= 2 )
      goto LABEL_37;
    goto LABEL_21;
  }
  if ( n2_1 <= 2 )
    goto LABEL_37;
  if ( n15 != n15_0 )
  {
    sub_413230((unsigned int *)(*(_DWORD *)(_this + 1078212) + 24 * n4_3), **(unsigned __int16 **)(_this + 76), 1u);
    n2 = *(_DWORD *)(_this + 32);
    goto LABEL_19;
  }
LABEL_21:
  v19 = **(unsigned __int16 **)(_this + 76);
  v20 = *(unsigned __int16 **)(_this + 6059432);
  v21 = *v20;
  if ( v19 != v21 )
  {
    v22 = v20[1];
    if ( v19 == v22 )
    {
      v20[1] = v21;
    }
    else
    {
      v23 = v20[2];
      if ( v19 == v23 )
      {
        v20[2] = v22;
        *(_WORD *)(*(_DWORD *)(_this + 6059432) + 2) = **(_WORD **)(_this + 6059432);
      }
      else
      {
        v24 = v20[3];
        if ( v19 == v24 )
        {
          v20[3] = v23;
          *(_WORD *)(*(_DWORD *)(_this + 6059432) + 4) = *(_WORD *)(*(_DWORD *)(_this + 6059432) + 2);
          *(_WORD *)(*(_DWORD *)(_this + 6059432) + 2) = **(_WORD **)(_this + 6059432);
        }
        else
        {
          v25 = v20[4];
          if ( v19 == v25 )
          {
            v20[4] = v24;
            *(_WORD *)(*(_DWORD *)(_this + 6059432) + 6) = *(_WORD *)(*(_DWORD *)(_this + 6059432) + 4);
            *(_WORD *)(*(_DWORD *)(_this + 6059432) + 4) = *(_WORD *)(*(_DWORD *)(_this + 6059432) + 2);
            *(_WORD *)(*(_DWORD *)(_this + 6059432) + 2) = **(_WORD **)(_this + 6059432);
          }
          else
          {
            v26 = v20[5];
            if ( v19 == v26 )
            {
              v20[5] = v25;
              *(_WORD *)(*(_DWORD *)(_this + 6059432) + 8) = *(_WORD *)(*(_DWORD *)(_this + 6059432) + 6);
              *(_WORD *)(*(_DWORD *)(_this + 6059432) + 6) = *(_WORD *)(*(_DWORD *)(_this + 6059432) + 4);
              *(_WORD *)(*(_DWORD *)(_this + 6059432) + 4) = *(_WORD *)(*(_DWORD *)(_this + 6059432) + 2);
              *(_WORD *)(*(_DWORD *)(_this + 6059432) + 2) = **(_WORD **)(_this + 6059432);
            }
            else
            {
              v27 = v20[6];
              if ( v19 == v27 )
              {
                v20[6] = v26;
              }
              else
              {
                v20[7] = v27;
                *(_WORD *)(*(_DWORD *)(_this + 6059432) + 12) = *(_WORD *)(*(_DWORD *)(_this + 6059432) + 10);
              }
              *(_WORD *)(*(_DWORD *)(_this + 6059432) + 10) = *(_WORD *)(*(_DWORD *)(_this + 6059432) + 8);
              *(_WORD *)(*(_DWORD *)(_this + 6059432) + 8) = *(_WORD *)(*(_DWORD *)(_this + 6059432) + 6);
              *(_WORD *)(*(_DWORD *)(_this + 6059432) + 6) = *(_WORD *)(*(_DWORD *)(_this + 6059432) + 4);
              *(_WORD *)(*(_DWORD *)(_this + 6059432) + 4) = *(_WORD *)(*(_DWORD *)(_this + 6059432) + 2);
              *(_WORD *)(*(_DWORD *)(_this + 6059432) + 2) = **(_WORD **)(_this + 6059432);
            }
          }
        }
      }
    }
    **(_WORD **)(_this + 6059432) = v19;
  }
LABEL_37:
  *(_WORD *)(*(_DWORD *)(_this + 6059436) + 2) = **(_WORD **)(_this + 6059436);
  **(_WORD **)(_this + 6059436) = **(_WORD **)(_this + 76);
  *(_BYTE *)(*(_DWORD *)(_this + 76) + 2) = **(unsigned __int16 **)(_this + 76) == **(unsigned __int16 **)(_this + 80);
  *(_BYTE *)(*(_DWORD *)(_this + 76) + 3) = **(unsigned __int16 **)(_this + 76) == *(unsigned __int16 *)(*(_DWORD *)(_this + 76) - 8);
  *(_BYTE *)(*(_DWORD *)(_this + 76) + 4) = **(unsigned __int16 **)(_this + 76) == *(unsigned __int16 *)(*(_DWORD *)(_this + 80) + 8);
  *(_BYTE *)(*(_DWORD *)(_this + 76) + 5) = **(unsigned __int16 **)(_this + 76) == *(unsigned __int16 *)(*(_DWORD *)(_this + 80) - 8);
  *(_BYTE *)(*(_DWORD *)(_this + 76) + 6) = **(unsigned __int16 **)(_this + 76) == *(unsigned __int16 *)(*(_DWORD *)(_this + 80) + 16);
  *(_BYTE *)(*(_DWORD *)(_this + 76) + 7) = **(unsigned __int16 **)(_this + 76) == *(unsigned __int16 *)(*(_DWORD *)(_this + 80) + 24);
  v28 = *(_DWORD *)(_this + 80);
  v29 = *(_DWORD *)(_this + 84);
  v30 = *(_DWORD *)(_this + 76) + 8;
  *(_DWORD *)(_this + 76) = v30;
  *(_DWORD *)(_this + 88) += 8;
  v28 += 8;
  *(_DWORD *)(_this + 80) = v28;
  v29 += 8;
  *(_DWORD *)(_this + 92) += 8;
  *(_DWORD *)(_this + 84) = v29;
  *(_BYTE *)(_this + 1078692) += *(_BYTE *)(v28 + 34) - *(_BYTE *)(v28 - 30);
  *(_BYTE *)(_this + 1078693) += *(_BYTE *)(v29 + 34) - *(_BYTE *)(v29 - 30);
  *(_BYTE *)(_this + 1078694) += *(_BYTE *)(v30 - 5) - *(_BYTE *)(v30 - 37);
  result = *(unsigned __int8 *)(v30 - 6) - *(unsigned __int8 *)(v30 - 62);
  *(_BYTE *)(_this + 1078695) += result;
  return result;
}

#undef buf_0
#undef byte_445700
#undef n15
#undef n15_0
#undef n4_3
#undef n4_4
#undef sub_413230
