// sub_428B00 @ 0x00428B00 — __cdecl
// Extracted from BMF.cpp:33025-33067 by extract.py per incdec.md.


PROBE_DECL(__sub_428B00)
BMF_REALIGN char *__sub_428B00(_WORD *a1, char *a2, int a3)
{
  PROBE_HIT(__sub_428B00);
  _WORD *v3; // ecx
  char *result; // eax
  _WORD *v5; // edx
  char v6; // bp
  int v7; // ebx
  __int16 v8; // bp

  v3 = a1;
  result = a2;
  v5 = &a1[a3];
  do
  {
    v6 = *result++;
    v7 = (v6 & 0x7F) + 1;
    if ( v6 < 0 )
    {
      v8 = *(_WORD *)result;
      do
      {
        *v3++ = v8;
        --v7;
      }
      while ( (_BYTE)v7 );
      result += 2;
    }
    else
    {
      do
      {
        *v3++ = *(_WORD *)result;
        result += 2;
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

