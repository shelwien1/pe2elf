// sub_40AE10 @ 0x0040AE10 — __thiscall
// Extracted from BMF.c:8916-8961 by extract.py per incdec.md.

typedef int t_sub_40AE10_n2;
static t_sub_40AE10_n2& __sub_40AE10_n2 = *(t_sub_40AE10_n2*)0x00443360;
#define n2 __sub_40AE10_n2


PROBE_DECL(__sub_40AE10)
__attribute__((thiscall)) int __sub_40AE10(_DWORD *_this, int Src)
{
  PROBE_HIT(__sub_40AE10);
  int v2; // eax
  int v3; // edx
  int result; // eax
  int v5; // ecx
  int v6; // [esp+0h] [ebp-28h]
  int v7; // [esp+4h] [ebp-24h]
  int v8; // [esp+Ch] [ebp-1Ch]
  int v9; // [esp+10h] [ebp-18h]

  v2 = *(_this + 2);
  v3 = *(_this + 3);
  v8 = *(unsigned __int8 *)(Src - 1);
  v9 = *(unsigned __int8 *)(Src + v2);
  v6 = *(unsigned __int8 *)(Src + v2 - 1);
  v7 = *(unsigned __int8 *)(Src + v2 + 1);
  result = v9 & 1
         | *(_this
           + ((*(unsigned __int8 *)(Src + v3 + 3)
             + *(unsigned __int8 *)(Src + v3 + 2)
             + *(unsigned __int8 *)(Src + v3 - 2)
             + *(unsigned __int8 *)(Src + v3 - 1)
             + *(unsigned __int8 *)(Src + v2 - 3)
             + *(unsigned __int8 *)(Src + v2 + 4)
             + *(unsigned __int8 *)(Src + v2 + 3)
             + *(unsigned __int8 *)(Src + v2 - 2)
             + 3 * (v7 + v6)
             + *(unsigned __int8 *)(Src - 4)
             + *(unsigned __int8 *)(Src - 3)
             + 4 * (v9 + v8)
             + 2
             * (*(unsigned __int8 *)(Src + v2 + 2)
              + *(unsigned __int8 *)(Src + v3 + 1)
              + *(unsigned __int8 *)(Src + v3)
              + *(unsigned __int8 *)(Src - 2))) >> 5)
           + 5)
         | (2 * (v8 & 1));
  if ( n2 == 1 )
  {
    v5 = result < *(_this + v8 + 5) || result < *(_this + v7 + 5) || result < *(_this + v6 + 5);
    return (v5 << 7) | (8 * (v6 & 1)) | (4 * (v7 & 1)) | result;
  }
  return result;
}

#undef n2
