// sub_429740 @ 0x00429740 — __cdecl
// Extracted from BMF.cpp:33941-34024 by extract.py per incdec.md.


PROBE_DECL(__sub_429740)
BMF_REALIGN unsigned __int8 *__sub_429740(unsigned __int8 *Buffer, _DWORD *a2, int a3)
{
  PROBE_HIT(__sub_429740);
  unsigned __int8 n128; // cl
  unsigned __int8 *Buffer_1; // ebp
  _DWORD *v5; // ebx
  unsigned __int8 *Buffer_3; // eax
  _DWORD *v7; // edx
  _DWORD *v8; // edi
  int n128_2; // ebp
  int n128_1; // edi
  unsigned __int8 *Buffer_4; // ecx
  unsigned __int8 *Buffer_2; // [esp+8h] [ebp-10h]

  n128 = 0;
  Buffer_1 = Buffer;
  v5 = a2;
  Buffer_3 = Buffer + 1;
  v7 = &a2[a3];
  *Buffer = 0;
  if ( a2 < v7 )
  {
    Buffer_2 = Buffer;
    do
    {
      v8 = v5 + 1;
      if ( v7 <= v5 + 1 )
        goto LABEL_15;
      n128_2 = 1;
      do
      {
        if ( *v5 != v5[n128_2] )
          break;
        ++n128_2;
      }
      while ( v7 > &v5[n128_2] );
      v8 = v5 + 1;
      if ( n128_2 <= 1 )
      {
LABEL_15:
        if ( n128 == 128 )
        {
          *Buffer_2 = n128 - 1;
          Buffer_2 = Buffer_3;
          *Buffer_3 = 0;
          n128 = *Buffer_3++;
        }
        *(_DWORD *)Buffer_3 = *v5;
        v5 = v8;
        Buffer_3 += 4;
        *Buffer_2 = ++n128;
      }
      else
      {
        if ( n128 )
          *Buffer_2 = n128 - 1;
        else
          --Buffer_3;
        do
        {
          n128_1 = n128_2;
          if ( n128_2 > 128 )
            n128_1 = 128;
          *Buffer_3 = (n128_1 + 127) | 0x80;
          *(_DWORD *)(Buffer_3 + 1) = *v5;
          Buffer_3 += 5;
          v5 += n128_1;
          n128_2 -= n128_1;
        }
        while ( n128_2 > 1 );
        *Buffer_3 = 0;
        Buffer_4 = Buffer_3++;
        Buffer_2 = Buffer_4;
        n128 = *Buffer_4;
      }
    }
    while ( v5 < v7 );
    Buffer_1 = Buffer_2;
  }
  if ( n128 )
    *Buffer_1 = n128 - 1;
  else
    --Buffer_3;
  return Buffer_3;
}

