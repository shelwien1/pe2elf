// sub_428AA0 @ 0x00428AA0 — __cdecl
// Extracted from BMF.cpp:32981-33022 by extract.py per incdec.md.


PROBE_DECL(__sub_428AA0)
BMF_REALIGN char *__sub_428AA0(_BYTE *a1, char *a2, int a3)
{
  PROBE_HIT(__sub_428AA0);
  _BYTE *v3; // ecx
  char *result; // eax
  _BYTE *v5; // edx
  char v6; // bl
  int v7; // ebp
  char v8; // bl

  v3 = a1;
  result = a2;
  v5 = &a1[a3];
  do
  {
    v6 = *result++;
    v7 = (v6 & 0x7F) + 1;
    if ( v6 < 0 )
    {
      v8 = *result;
      do
      {
        *v3++ = v8;
        --v7;
      }
      while ( (_BYTE)v7 );
      ++result;
    }
    else
    {
      do
      {
        *v3++ = *result++;
        --v7;
      }
      while ( (_BYTE)v7 );
    }
  }
  while ( v3 < v5 );
  if ( v3 != v5 )
    return nullptr;
  return result;
}

