// sub_42B990 @ 0x0042B990 — __cdecl
// Extracted from BMF.cpp:36072-36120 by extract.py per incdec.md.


PROBE_DECL(__sub_42B990)
__attribute__((force_align_arg_pointer)) void __sub_42B990(char n5, int buf)
{
  PROBE_HIT(__sub_42B990);
  unsigned int v2; // ebx
  unsigned int v3; // ecx
  unsigned int v4; // eax
  char v5; // dl
  int v6; // edi
  char v7; // dl
  int v8; // ebp
  unsigned int v9; // ecx
  int v10; // ebx

  v2 = 1 << (n5 & 31);
  if ( 1 << (n5 & 31) )
  {
    if ( v2 >> 1 )
    {
      v3 = 0;
      v4 = 0x100 / v2;
      do
      {
        v5 = 2 * v3 * v4;
        v6 = 6 * v3;
        *(_BYTE *)(buf + v6) = v5;
        *(_BYTE *)(buf + v6 + 1) = v5;
        ++v3;
        *(_BYTE *)(buf + v6 + 2) = v5;
        v7 = v4 + v5;
        *(_BYTE *)(buf + v6 + 3) = v7;
        *(_BYTE *)(buf + v6 + 4) = v7;
        *(_BYTE *)(buf + v6 + 5) = v7;
      }
      while ( v3 < v2 >> 1 );
      v8 = 2 * v3 + 1;
    }
    else
    {
      v8 = 1;
    }
    if ( v2 > v8 - 1 )
    {
      v9 = 0x100 / v2 * (v8 - 1);
      v10 = 3 * v8;
      *(_BYTE *)(v10 + buf - 3) = v9;
      *(_BYTE *)(v10 + buf - 2) = v9;
      *(_BYTE *)(v10 + buf - 1) = v9;
    }
  }
}

