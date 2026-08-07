// sub_416860 @ 0x00416860 — __thiscall
// Extracted from BMF.cpp:20974-21078 by extract.py per incdec.md.

typedef char t_sub_416860_buf_0[0x10000];
static t_sub_416860_buf_0& __sub_416860_buf_0 = *(t_sub_416860_buf_0*)0x00443440;
typedef char t_sub_416860_byte_445700;
static t_sub_416860_byte_445700& __sub_416860_byte_445700 = *(t_sub_416860_byte_445700*)0x00445700;
typedef int t_sub_416860_n15;
static t_sub_416860_n15& __sub_416860_n15 = *(t_sub_416860_n15*)0x00445748;
typedef int t_sub_416860_n4_3;
static t_sub_416860_n4_3& __sub_416860_n4_3 = *(t_sub_416860_n4_3*)0x00445744;
typedef int t_sub_416860_n4_4;
static t_sub_416860_n4_4& __sub_416860_n4_4 = *(t_sub_416860_n4_4*)0x00445740;


PROBE_DECL(__sub_416860)
BMF_REALIGN __attribute__((thiscall)) int __sub_416860(int *_this, _DWORD *p_n15)
{
  PROBE_HIT(__sub_416860);
  int result; // eax
  int v3; // esi
  int v4; // edx
  bool v5; // zf
  int v6; // esi
  int v7; // edx
  unsigned __int16 *v8; // ecx
  int v9; // esi
  unsigned __int16 *v10; // ecx
  unsigned __int16 *v11; // edx
  unsigned __int16 *v12; // edi
  int v13; // edx
  int v14; // esi
  int v16; // [esp+8h] [ebp-6Ch]
  int n6; // [esp+60h] [ebp-14h]

  n6 = *(_this + 11);
  result = p_n15[n6];
  if ( __sub_416860_buf_0[result] == __sub_416860_byte_445700 )
    return -1;
  v3 = 32
     * (result == p_n15[15] || result == p_n15[14] || result == p_n15[13] || result == p_n15[12] || result == p_n15[11])
     + ((result == p_n15[10]) << 6);
  v4 = 16
     * (result == p_n15[31]
     || result == p_n15[30]
     || result == p_n15[29]
     || result == p_n15[28]
     || result == p_n15[27]
     || result == p_n15[26]
     || result == p_n15[25]
     || result == p_n15[24]
     || result == p_n15[23]
     || result == p_n15[22]
     || result == p_n15[21]
     || result == p_n15[20]
     || result == p_n15[19]
     || result == p_n15[18]
     || result == p_n15[17]
     || result == p_n15[16]);
  v5 = v4 + v3 == 0;
  v6 = v4 + v3;
  *(_this + 13) = v6;
  if ( v5 && n6 > 6 )
    return -1;
  v7 = *(_this + 269553);
  v16 = v7;
  v8 = *(unsigned __int16 **)(v7 + 24 * __sub_416860_n4_4 + 20);
  v9 = v6
     + 8
     * (result == *(unsigned __int16 *)((char *)v8 + 27)
     || result == v8[12]
     || result == *(unsigned __int16 *)((char *)v8 + 21)
     || result == v8[9]
     || result == *(unsigned __int16 *)((char *)v8 + 15)
     || result == v8[6]
     || result == *(unsigned __int16 *)((char *)v8 + 9)
     || result == v8[3]
     || result == *(unsigned __int16 *)((char *)v8 + 3)
     || result == *v8);
  *(_this + 13) = v9;
  v10 = *(unsigned __int16 **)(v7 + 24 * __sub_416860_n4_3 + 20);
  v11 = *(unsigned __int16 **)(v7 + 24 * result + 20);
  v12 = *(unsigned __int16 **)(v16 + 24 * __sub_416860_n15 + 20);
  v13 = (result == *(unsigned __int16 *)((char *)v12 + 15)
      || result == v12[6]
      || result == *(unsigned __int16 *)((char *)v12 + 9)
      || result == v12[3]
      || result == *(unsigned __int16 *)((char *)v12 + 3)
      || result == *v12)
      + 2
      * (__sub_416860_n4_3 == *(unsigned __int16 *)((char *)v11 + 27)
      || __sub_416860_n4_3 == v11[12]
      || __sub_416860_n4_3 == *(unsigned __int16 *)((char *)v11 + 21)
      || __sub_416860_n4_3 == v11[9]
      || __sub_416860_n4_3 == *(unsigned __int16 *)((char *)v11 + 15)
      || __sub_416860_n4_3 == v11[6]
      || __sub_416860_n4_3 == *(unsigned __int16 *)((char *)v11 + 9)
      || __sub_416860_n4_3 == v11[3]
      || __sub_416860_n4_3 == *(unsigned __int16 *)((char *)v11 + 3)
      || __sub_416860_n4_3 == *v11)
      + 4
      * (result == *(unsigned __int16 *)((char *)v10 + 9)
      || result == v10[3]
      || result == *(unsigned __int16 *)((char *)v10 + 3)
      || result == *v10);
  v14 = v13 + v9;
  if ( n6 <= 14 || (v14 & 0xB) != 0 )
  {
    *(_this + 13) = (n6 << 7) + v14;
    *(_this + 12) = v13 + 8 * (n6 > 9);
  }
  else
  {
    *(_this + 12) = v13;
    return -1;
  }
  return result;
}

