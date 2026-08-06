// sub_415270 @ 0x00415270 — __thiscall
// Extracted from BMF.c:19509-19585 by extract.py per incdec.md.

#ifndef __PE_DECL___Block
#define __PE_DECL___Block
typedef int t_Block[0x10000];
static t_Block& __Block = *(t_Block*)0x00445988;
#endif
#define Block __Block


// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_delete
#define __PE_DECL___op_delete
typedef void t_op_delete(void *);       // ??3@YAXPAX@Z
static t_op_delete& __op_delete = *(t_op_delete*)0x0042CF18;
#endif
#define FILE FILE1

PROBE_DECL(__sub_415270)
__attribute__((thiscall)) void **__sub_415270(void **Block, char a2)
{
  PROBE_HIT(__sub_415270);
  void **v2; // esi
  _DWORD *v3; // edx
  int v4; // eax
  void **v5; // edi
  int v6; // ebp
  _DWORD *v7; // esi
  _DWORD *v8; // ebx
  _DWORD *v9; // eax
  int v10; // edx
  void **v11; // edi
  _DWORD *v12; // esi
  int v13; // ebp
  _DWORD *v14; // ebx
  int i; // edi

  v2 = Block;
  __op_delete(*(Block + 269560));
  __op_delete(v2[269559]);
  __op_delete(v2[269671]);
  __op_delete(v2[269672]);
  v3 = v2[269552];
  if ( v3 )
  {
    v4 = *(v3 - 1);
    if ( v4 )
    {
      v5 = v2;
      v6 = *(v3 - 1);
      v7 = v2[269552];
      v8 = &v3[6 * v4];
      do
      {
        v8 -= 6;
        __op_delete((void *)v8[5]);
        --v6;
      }
      while ( v6 );
      v3 = v7;
      v2 = v5;
    }
    __op_delete(v3 - 1);
  }
  v9 = v2[269553];
  if ( v9 )
  {
    v10 = *(v9 - 1);
    if ( v10 )
    {
      v11 = v2;
      v12 = v2[269553];
      v13 = *(v9 - 1);
      v14 = &v9[6 * v10];
      do
      {
        v14 -= 6;
        __op_delete((void *)v14[5]);
        --v13;
      }
      while ( v13 );
      v9 = v12;
      v2 = v11;
    }
    __op_delete(v9 - 1);
  }
  for ( i = 0; i < 5; ++i )
    __op_delete(v2[i + 14]);
  __op_delete(v2[269551]);
  if ( (a2 & 1) != 0 )
    __op_delete(v2);
  return v2;
}

#undef FILE
#undef Block
