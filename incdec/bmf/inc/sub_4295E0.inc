// sub_4295E0 @ 0x004295E0 — __cdecl
// Extracted from BMF.cpp:33842-33938 by extract.py per incdec.md.


PROBE_DECL(__sub_4295E0)
BMF_REALIGN unsigned __int8 *__sub_4295E0(unsigned __int8 *a1, unsigned __int8 *a2, int a3)
{
  PROBE_HIT(__sub_4295E0);
  unsigned __int8 *v3; // ebp
  unsigned __int8 *v4; // ecx
  unsigned __int8 *result; // eax
  unsigned int v6; // ebx
  unsigned __int8 n128; // dl
  int n128_2; // ebp
  unsigned __int8 *v9; // esi
  unsigned int v10; // eax
  int n128_1; // edi
  unsigned __int8 *v12; // edx
  unsigned __int8 *v13; // ebp
  unsigned __int8 *v14; // [esp+Ch] [ebp-18h]
  unsigned __int8 *v15; // [esp+18h] [ebp-Ch]

  v3 = a1;
  v4 = a2;
  result = a1 + 1;
  v6 = (unsigned int)&a2[3 * a3];
  *a1 = 0;
  n128 = 0;
  if ( (unsigned int)a2 < v6 )
  {
    v14 = a1;
    do
    {
      if ( v6 <= (unsigned int)(v4 + 3) )
        goto LABEL_17;
      v15 = result;
      n128_2 = 1;
      v9 = v4 + 3;
      do
      {
        v10 = *(unsigned __int16 *)v9;
        if ( v4[2] != v9[2] )
          break;
        if ( v4[1] != v10 >> 8 )
          break;
        if ( *v4 != (unsigned __int8)v10 )
          break;
        ++n128_2;
        v9 = &v4[3 * n128_2];
      }
      while ( v6 > (unsigned int)v9 );
      result = v15;
      if ( n128_2 <= 1 )
      {
LABEL_17:
        if ( n128 == 128 )
        {
          v13 = v14;
          v14 = result;
          *v13 = n128 - 1;
          *result++ = 0;
        }
        *(_WORD *)result = *(_WORD *)v4;
        result[2] = v4[2];
        v4 += 3;
        result += 3;
        n128 = *v14 + 1;
        *v14 = n128;
      }
      else
      {
        if ( n128 )
          *v14 = n128 - 1;
        else
          result = v15 - 1;
        do
        {
          n128_1 = n128_2;
          if ( n128_2 > 128 )
            n128_1 = 128;
          *result = (n128_1 + 127) | 0x80;
          *(_WORD *)(result + 1) = *(_WORD *)v4;
          result[3] = v4[2];
          result += 4;
          v4 += 3 * n128_1;
          n128_2 -= n128_1;
        }
        while ( n128_2 > 1 );
        *result = 0;
        v12 = result++;
        v14 = v12;
        n128 = *v12;
      }
    }
    while ( (unsigned int)v4 < v6 );
    v3 = v14;
  }
  if ( n128 )
    *v3 = n128 - 1;
  else
    --result;
  return result;
}

