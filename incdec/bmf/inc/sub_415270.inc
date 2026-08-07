// sub_415270 @ 0x00415270 — __thiscall
// Extracted from BMF.c:19568-19642 by extract.py per incdec.md.


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
__attribute__((force_align_arg_pointer)) __attribute__((thiscall)) void **__sub_415270(void **Blocka, char a2)
{
  PROBE_HIT(__sub_415270);
  void **Blocka_1; // esi
  _DWORD *v3; // edx
  int v4; // eax
  void **Blocka_2; // edi
  int v6; // ebp
  _DWORD *v7; // esi
  void **v8; // ebx
  _DWORD *v9; // eax
  int v10; // edx
  void **Blocka_3; // edi
  _DWORD *v12; // esi
  int v13; // ebp
  void **v14; // ebx
  int i; // edi

  Blocka_1 = Blocka;
  __op_delete(*(Blocka + 269560));
  __op_delete(Blocka_1[269559]);
  __op_delete(Blocka_1[269671]);
  __op_delete(Blocka_1[269672]);
  v3 = Blocka_1[269552];
  if ( v3 )
  {
    v4 = *(v3 - 1);
    if ( v4 )
    {
      Blocka_2 = Blocka_1;
      v6 = *(v3 - 1);
      v7 = Blocka_1[269552];
      v8 = (void **)&v3[6 * v4];
      do
      {
        v8 -= 6;
        __op_delete(v8[5]);
        --v6;
      }
      while ( v6 );
      v3 = v7;
      Blocka_1 = Blocka_2;
    }
    __op_delete(v3 - 1);
  }
  v9 = Blocka_1[269553];
  if ( v9 )
  {
    v10 = *(v9 - 1);
    if ( v10 )
    {
      Blocka_3 = Blocka_1;
      v12 = Blocka_1[269553];
      v13 = *(v9 - 1);
      v14 = (void **)&v9[6 * v10];
      do
      {
        v14 -= 6;
        __op_delete(v14[5]);
        --v13;
      }
      while ( v13 );
      v9 = v12;
      Blocka_1 = Blocka_3;
    }
    __op_delete(v9 - 1);
  }
  for ( i = 0; i < 5; ++i )
    __op_delete(Blocka_1[i + 14]);
  __op_delete(Blocka_1[269551]);
  if ( (a2 & 1) != 0 )
    __op_delete(Blocka_1);
  return Blocka_1;
}

#undef FILE
