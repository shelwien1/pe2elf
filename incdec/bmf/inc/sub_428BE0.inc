// sub_428BE0 @ 0x00428BE0 — __cdecl
// Extracted from BMF.cpp:33117-33159 by extract.py per incdec.md.


PROBE_DECL(__sub_428BE0)
__attribute__((force_align_arg_pointer)) char *__sub_428BE0(_DWORD *a1, char *Src, int a3)
{
  PROBE_HIT(__sub_428BE0);
  _DWORD *v3; // ecx
  char *Src_1; // eax
  _DWORD *v5; // edx
  char v6; // bp
  int v7; // ebx
  int v8; // ebp

  v3 = a1;
  Src_1 = Src;
  v5 = &a1[a3];
  do
  {
    v6 = *Src_1++;
    v7 = (v6 & 0x7F) + 1;
    if ( v6 < 0 )
    {
      v8 = *(_DWORD *)Src_1;
      do
      {
        *v3++ = v8;
        --v7;
      }
      while ( (_BYTE)v7 );
      Src_1 += 4;
    }
    else
    {
      do
      {
        *v3++ = *(_DWORD *)Src_1;
        Src_1 += 4;
        --v7;
      }
      while ( (_BYTE)v7 );
    }
  }
  while ( v3 < v5 );
  if ( v3 != v5 )
    return nullptr;
  return Src_1;
}

