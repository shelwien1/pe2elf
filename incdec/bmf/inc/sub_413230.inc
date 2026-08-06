// sub_413230 @ 0x00413230 — __thiscall
// Extracted from BMF.c:17383-17582 by extract.py per incdec.md.


PROBE_DECL(__sub_413230)
__attribute__((thiscall)) int __sub_413230(unsigned int *_this, int a2, unsigned int a3)
{
  PROBE_HIT(__sub_413230);
  int n251; // eax
  unsigned int v4; // edi
  unsigned __int16 *n251_1; // ebp
  unsigned int v6; // ebx
  bool v7; // zf
  int v8; // ebx
  int v9; // ebp
  __int16 v10; // bx
  char v11; // dl
  char v12; // cl
  unsigned __int16 *n251_2; // edx
  unsigned __int16 v14; // di
  char v15; // al
  char *v16; // ebx
  char v17; // dl
  unsigned __int16 v18; // di
  char v19; // al
  char v20; // dl
  unsigned int v21; // ebx
  int v22; // edi
  char *v23; // edx
  char *v24; // ebp
  signed int v25; // eax
  char *v26; // esi
  char *v27; // edi
  signed int v28; // edx
  unsigned int v29; // eax
  int v30; // edx
  unsigned int v31; // ebx
  int v32; // [esp+0h] [ebp-24h]
  char *v33; // [esp+4h] [ebp-20h]
  __int16 v34; // [esp+8h] [ebp-1Ch]
  signed int v35; // [esp+Ch] [ebp-18h]
  BOOL v36; // [esp+10h] [ebp-14h]

  n251 = *(_this + 5);
  v4 = *(_this + 1);
  n251_1 = (unsigned __int16 *)n251;
  v6 = v4;
  if ( v4 )
  {
    while ( *n251_1 != a2 )
    {
      n251_1 = (unsigned __int16 *)((char *)n251_1 + 3);
      if ( !--v6 )
        goto LABEL_4;
    }
    *((_BYTE *)n251_1 + 2) += a3;
    *(_this + 3) += a3;
    n251_2 = (unsigned __int16 *)*(_this + 5);
    if ( n251_1 == n251_2 )
    {
LABEL_16:
      n251 = *((unsigned __int8 *)n251_1 + 2);
    }
    else
    {
      v14 = *n251_1;
      v15 = *((_BYTE *)n251_1 + 2);
      v16 = (char *)n251_1 - 3;
      v17 = *((_BYTE *)n251_1 - 1);
      *n251_1 = *(unsigned __int16 *)((char *)n251_1 - 3);
      *((_BYTE *)n251_1 + 2) = v17;
      *(_WORD *)v16 = v14;
      v16[2] = v15;
      n251_2 = (unsigned __int16 *)*(_this + 5);
      if ( (unsigned __int16 *)((char *)n251_1 - 3) == n251_2 )
      {
        n251 = *((unsigned __int8 *)n251_1 - 1);
      }
      else
      {
        while ( 1 )
        {
          n251 = (unsigned __int8)v16[2];
          n251_1 = (unsigned __int16 *)(v16 - 3);
          if ( n251 <= (unsigned __int8)*(v16 - 1) )
            break;
          v18 = *(_WORD *)v16;
          v19 = v16[2];
          v20 = *(v16 - 1);
          *(_WORD *)v16 = *n251_1;
          v16[2] = v20;
          *n251_1 = v18;
          *(v16 - 1) = v19;
          n251_2 = (unsigned __int16 *)*(_this + 5);
          v16 -= 3;
          if ( n251_1 == n251_2 )
            goto LABEL_16;
        }
      }
    }
    v21 = *(_this + 4);
    if ( n251 > 251 || v21 < *(_this + 3) )
    {
      v22 = *(_this + 1);
      v36 = v21 < 20 * *_this;
      v23 = (char *)n251_2 - 3;
      do
      {
        v24 = v23;
        v23 += 3;
        v25 = (v36 + (unsigned int)(unsigned __int8)v23[2]) >> 1;
        v23[2] = v25;
        if ( v23 != (char *)*(_this + 5) )
        {
          v26 = v23 - 3;
          v35 = (unsigned __int8)*(v23 - 1);
          if ( v25 > v35 )
          {
            v34 = *(_WORD *)v23;
            *(_WORD *)v23 = *(_WORD *)v26;
            v23[2] = v35;
            if ( v26 != (char *)*(_this + 5) )
            {
              v33 = v23;
              v32 = v22;
              do
              {
                v27 = v26 - 3;
                v28 = (unsigned __int8)*(v26 - 1);
                if ( v25 <= v28 )
                  break;
                *(_WORD *)v26 = *(_WORD *)v27;
                v26[2] = v28;
                v26 -= 3;
              }
              while ( v27 != (char *)*(_this + 5) );
              v23 = v33;
              v22 = v32;
            }
            *(_WORD *)v26 = v34;
            v26[2] = v25;
          }
        }
        --v22;
      }
      while ( v22 );
      v29 = *(_this + 2);
      if ( !v23[2] )
      {
        do
        {
          ++v22;
          *(_this + 2) = ++v29;
          v30 = (unsigned __int8)v24[2];
          v24 -= 3;
        }
        while ( !v30 );
        *(_this + 1) -= v22;
      }
      v31 = *(_this + 3);
      *(_this + 2) = v29 - (v29 >> 1);
      *(_this + 3) = v31 - (v31 >> 1);
      return v31 >> 1;
    }
  }
  else
  {
LABEL_4:
    v7 = v4 == *_this;
    if ( v4 >= *_this )
    {
      if ( a3 <= 1 )
        return n251;
      v7 = v4 == *_this;
    }
    if ( v7 )
    {
      *(_this + 1) = --v4;
      v8 = *(unsigned __int8 *)(3 * v4 + n251 + 2);
    }
    else
    {
      v8 = 1;
    }
    v9 = *(_this + 2);
    n251 += 3 * v4;
    *(_this + 1) = v4 + 1;
    *(_this + 2) = v8 + v9 + 1;
    *(_BYTE *)(n251 + 2) = 2;
    *(_WORD *)n251 = a2;
    *(_this + 3) += 4;
    if ( n251 != *(_this + 5) )
    {
      v10 = *(_WORD *)n251;
      v11 = *(_BYTE *)(n251 + 2);
      v12 = *(_BYTE *)(n251 - 1);
      *(_WORD *)n251 = *(_WORD *)(n251 - 3);
      *(_BYTE *)(n251 + 2) = v12;
      *(_WORD *)(n251 - 3) = v10;
      *(_BYTE *)(n251 - 1) = v11;
    }
  }
  return n251;
}

