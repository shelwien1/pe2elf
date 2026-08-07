// sub_42C0B0 @ 0x0042C0B0 — __thiscall
// Extracted from BMF.c:36522-36630 by extract.py per incdec.md.

typedef int t_sub_42C0B0_dword_445924;
static t_sub_42C0B0_dword_445924& __sub_42C0B0_dword_445924 = *(t_sub_42C0B0_dword_445924*)0x00445924;
#define dword_445924 __sub_42C0B0_dword_445924
typedef int t_sub_42C0B0_dword_445928;
static t_sub_42C0B0_dword_445928& __sub_42C0B0_dword_445928 = *(t_sub_42C0B0_dword_445928*)0x00445928;
#define dword_445928 __sub_42C0B0_dword_445928
typedef int t_sub_42C0B0_dword_44592C;
static t_sub_42C0B0_dword_44592C& __sub_42C0B0_dword_44592C = *(t_sub_42C0B0_dword_44592C*)0x0044592C;
#define dword_44592C __sub_42C0B0_dword_44592C
typedef int t_sub_42C0B0_n256;
static t_sub_42C0B0_n256& __sub_42C0B0_n256 = *(t_sub_42C0B0_n256*)0x0044336C;
#define n256 __sub_42C0B0_n256

#ifndef __PE_DECL___sub_42C220
#define __PE_DECL___sub_42C220
typedef __attribute__((thiscall)) int t_sub_42C220(...);
static t_sub_42C220& __sub_42C220 = *(t_sub_42C220*)0x0042C220;
#endif
#define sub_42C220 __sub_42C220
#ifndef __PE_DECL___sub_434980
#define __PE_DECL___sub_434980
typedef void * t_sub_434980(void *, const void *, unsigned int);   // stack arguments only
static t_sub_434980& __sub_434980 = *(t_sub_434980*)0x00434980;
#endif
#define sub_434980 __sub_434980
#define sub_42B830 __sub_42B830

// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_delete
#define __PE_DECL___op_delete
typedef void t_op_delete(void *);       // ??3@YAXPAX@Z
static t_op_delete& __op_delete = *(t_op_delete*)0x0042CF18;
#endif
#define FILE FILE1

PROBE_DECL(__sub_42C0B0)
__attribute__((thiscall)) int *__sub_42C0B0(int _this, int a2)
{
  PROBE_HIT(__sub_42C0B0);
  char v3; // cl
  char v4; // dl
  int v5; // eax
  int n4; // eax
  bool v7; // cc
  int *result; // eax
  char v9; // fps
  char *v10; // edx
  void (__cdecl *sub_42BB20)(int, int, int, int); // ebx
  int v12; // esi
  int n256; // edi
  int v14; // edx
  __int16 v15; // cx

  v3 = *(_BYTE *)(_this + 25);
  if ( *(_DWORD *)(_this + 1564) )
  {
    v4 = *(_BYTE *)(_this + 14);
    n4 = 0;
  }
  else
  {
    v4 = *(_BYTE *)(_this + 14);
    v5 = v4 & 7;
    if ( (v3 & 7) != 0 )
      v5 = v3 & 7;
    n4 = v5 + 1;
    if ( a2 )
    {
      if ( n4 <= 4 )
      {
        if ( n4 == 3 )
          n4 = 4;
      }
      else
      {
        n4 = 8;
      }
    }
    else
    {
      v7 = n4 <= 4;
      n4 = 8;
      if ( v7 )
        n4 = 4;
    }
  }
  result = sub_42B830(
             *(unsigned __int16 *)(_this + 21),
             *(unsigned __int16 *)(_this + 23),
             n4,
             (unsigned __int8)((v4 | v3) & 0x80) >> 7,
             a2);
  dword_44592C = (int)result;
  if ( result )
  {
    if ( (*((_BYTE *)result + 10) & 0x80) != 0 )
      v10 = (char *)result + result[3] + 16;
    else
      v10 = nullptr;
    if ( (*((_BYTE *)result + 10) & 0x3F) == 8 )
    {
      sub_42BB20 = nullptr;
    }
    else
    {
      sub_42BB20 = (void (__cdecl *)(int, int, int, int))::sub_42BB20;
      if ( a2 )
        sub_42BB20 = (void (__cdecl *)(int, int, int, int))sub_42BBD0;
    }
    if ( !*(_DWORD *)(_this + 1564) )
    {
      dword_445924 = 0;
      dword_445928 = 0;
      if ( v10 )
      {
        if ( (*(_BYTE *)(_this + 25) & 0x80) != 0 )
        {
          v12 = 1 << ((*(_BYTE *)(_this + 25) & 7) + 1);
          n256 = 256;
        }
        else
        {
          v12 = *(_BYTE *)(_this + 14) & 0x80;
          n256 = 0;
          if ( (*(_BYTE *)(_this + 14) & 0x80) != 0 )
            v12 = 1 << ((*(_BYTE *)(_this + 14) & 7) + 1);
        }
        sub_434980(v10,(char *)(_this + 3 * n256 + 26),3 * v12);
      }
      v14 = sub_42C220(_this, sub_42BB20);
      result = (int *)dword_44592C;
      if ( !v14 )
      {
        v15 = *(_WORD *)(_this + 19);
        *(_WORD *)(dword_44592C + 6) = *(_WORD *)(_this + 17);
        *((_WORD *)result + 4) = v15;
        return result;
      }
    }
    __op_delete(result);
  }
  return nullptr;
}

#undef FILE
#undef dword_445924
#undef dword_445928
#undef dword_44592C
#undef n256
#undef sub_42B830
#undef sub_42C220
#undef sub_434980
