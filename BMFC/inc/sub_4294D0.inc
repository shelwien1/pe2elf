// sub_4294D0 @ 0x004294D0 — __cdecl
// Extracted from BMF.cpp:33756-33839 by extract.py per incdec.md.


PROBE_DECL(__sub_4294D0)
BMF_REALIGN unsigned __int8 *__sub_4294D0(unsigned __int8 *a1, _WORD *a2, int a3)
{
  PROBE_HIT(__sub_4294D0);
  unsigned __int8 n128; // cl
  unsigned __int8 *v4; // ebp
  _WORD *v5; // ebx
  unsigned __int8 *result; // eax
  unsigned int v7; // edx
  _WORD *v8; // edi
  int n128_2; // ebp
  int n128_1; // edi
  unsigned __int8 *v11; // ecx
  unsigned __int8 *v12; // [esp+8h] [ebp-10h]

  n128 = 0;
  v4 = a1;
  v5 = a2;
  result = a1 + 1;
  v7 = (unsigned int)&a2[a3];
  *a1 = 0;
  if ( (unsigned int)a2 < v7 )
  {
    v12 = a1;
    do
    {
      v8 = v5 + 1;
      if ( v7 <= (unsigned int)(v5 + 1) )
        goto LABEL_15;
      n128_2 = 1;
      do
      {
        if ( *v5 != v5[n128_2] )
          break;
        ++n128_2;
      }
      while ( v7 > (unsigned int)&v5[n128_2] );
      v8 = v5 + 1;
      if ( n128_2 <= 1 )
      {
LABEL_15:
        if ( n128 == 128 )
        {
          *v12 = n128 - 1;
          v12 = result;
          *result = 0;
          n128 = *result++;
        }
        *(_WORD *)result = *v5;
        v5 = v8;
        result += 2;
        *v12 = ++n128;
      }
      else
      {
        if ( n128 )
          *v12 = n128 - 1;
        else
          --result;
        do
        {
          n128_1 = n128_2;
          if ( n128_2 > 128 )
            n128_1 = 128;
          *result = (n128_1 + 127) | 0x80;
          *(_WORD *)(result + 1) = *v5;
          result += 3;
          v5 += n128_1;
          n128_2 -= n128_1;
        }
        while ( n128_2 > 1 );
        *result = 0;
        v11 = result++;
        v12 = v11;
        n128 = *v11;
      }
    }
    while ( (unsigned int)v5 < v7 );
    v4 = v12;
  }
  if ( n128 )
    *v4 = n128 - 1;
  else
    --result;
  return result;
}

