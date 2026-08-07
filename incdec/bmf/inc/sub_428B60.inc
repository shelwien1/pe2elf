// sub_428B60 @ 0x00428B60 — __cdecl
// Extracted from BMF.cpp:33070-33114 by extract.py per incdec.md.


PROBE_DECL(__sub_428B60)
__attribute__((force_align_arg_pointer)) char *__sub_428B60(unsigned int a1, char *a2, int a3)
{
  PROBE_HIT(__sub_428B60);
  unsigned int v3; // edx
  char *result; // eax
  unsigned int v5; // ecx
  char v6; // bl
  int v7; // ebp

  v3 = a1;
  result = a2;
  v5 = a1 + 3 * a3;
  do
  {
    v6 = *result++;
    v7 = (v6 & 0x7F) + 1;
    if ( v6 < 0 )
    {
      do
      {
        *(_WORD *)v3 = *(_WORD *)result;
        *(_BYTE *)(v3 + 2) = result[2];
        v3 += 3;
        --v7;
      }
      while ( (_BYTE)v7 );
      result += 3;
    }
    else
    {
      do
      {
        *(_WORD *)v3 = *(_WORD *)result;
        *(_BYTE *)(v3 + 2) = result[2];
        v3 += 3;
        result += 3;
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

