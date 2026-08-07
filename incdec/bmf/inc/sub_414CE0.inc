// sub_414CE0 @ 0x00414CE0 — __cdecl
// Extracted from BMF.cpp:19253-19394 by extract.py per incdec.md.

typedef int t_sub_414CE0_Buffer;
static t_sub_414CE0_Buffer& __sub_414CE0_Buffer = *(t_sub_414CE0_Buffer*)(blob1 + 0x0044337C - BMF_BLOB_BASE);
typedef int t_sub_414CE0_Buffer_0;
static t_sub_414CE0_Buffer_0& __sub_414CE0_Buffer_0 = *(t_sub_414CE0_Buffer_0*)(blob1 + 0x00443378 - BMF_BLOB_BASE);
typedef int t_sub_414CE0_Buffer_1;
static t_sub_414CE0_Buffer_1& __sub_414CE0_Buffer_1 = *(t_sub_414CE0_Buffer_1*)(blob1 + 0x00443374 - BMF_BLOB_BASE);
typedef char t_sub_414CE0_byte_4456F0;
static t_sub_414CE0_byte_4456F0& __sub_414CE0_byte_4456F0 = *(t_sub_414CE0_byte_4456F0*)(blob1 + 0x004456F0 - BMF_BLOB_BASE);
typedef int t_sub_414CE0_dword_443364;
static t_sub_414CE0_dword_443364& __sub_414CE0_dword_443364 = *(t_sub_414CE0_dword_443364*)(blob1 + 0x00443364 - BMF_BLOB_BASE);
typedef int t_sub_414CE0_dword_4456E8;
static t_sub_414CE0_dword_4456E8& __sub_414CE0_dword_4456E8 = *(t_sub_414CE0_dword_4456E8*)(blob1 + 0x004456E8 - BMF_BLOB_BASE);
typedef int t_sub_414CE0_dword_4456EC;
static t_sub_414CE0_dword_4456EC& __sub_414CE0_dword_4456EC = *(t_sub_414CE0_dword_4456EC*)(blob1 + 0x004456EC - BMF_BLOB_BASE);
typedef int t_sub_414CE0_n0x7F800000;
static t_sub_414CE0_n0x7F800000& __sub_414CE0_n0x7F800000 = *(t_sub_414CE0_n0x7F800000*)(blob1 + 0x004456E4 - BMF_BLOB_BASE);
typedef int t_sub_414CE0_n0x800000;
static t_sub_414CE0_n0x800000& __sub_414CE0_n0x800000 = *(t_sub_414CE0_n0x800000*)(blob1 + 0x004456E0 - BMF_BLOB_BASE);
typedef int t_sub_414CE0_n256;
static t_sub_414CE0_n256& __sub_414CE0_n256 = *(t_sub_414CE0_n256*)(blob1 + 0x0044336C - BMF_BLOB_BASE);
typedef int t_sub_414CE0_n256_1;
static t_sub_414CE0_n256_1& __sub_414CE0_n256_1 = *(t_sub_414CE0_n256_1*)(blob1 + 0x00445708 - BMF_BLOB_BASE);
typedef int t_sub_414CE0_n8;
static t_sub_414CE0_n8& __sub_414CE0_n8 = *(t_sub_414CE0_n8*)(blob1 + 0x00443368 - BMF_BLOB_BASE);


// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_delete
#define __PE_DECL___op_delete
typedef void t_op_delete(void *);       // ??3@YAXPAX@Z
static t_op_delete& __op_delete = *(t_op_delete*)0x0042CF18;
#endif
#define FILE FILE1

PROBE_DECL(__sub_414CE0)
BMF_REALIGN void __sub_414CE0()
{
  PROBE_HIT(__sub_414CE0);
  unsigned int __sub_414CE0_n0x7F800000; // edi
  _BYTE *v1; // esi
  char v2; // dl
  unsigned int v3; // ebp
  int v4; // ebx
  unsigned int v5; // ebx
  unsigned int v6; // ecx
  char v7; // al
  unsigned int v8; // edx
  char v9; // al
  unsigned int n0x800000_1; // eax
  int v11; // ebx
  unsigned int n0xFF; // ecx
  _BYTE *v13; // edx
  unsigned int v14; // esi
  char v15; // al
  int v16; // eax
  _BYTE *v17; // eax
  char v18; // [esp+4h] [ebp-1Ch]
  int __sub_414CE0_n0x800000; // [esp+8h] [ebp-18h]
  int v20; // [esp+Ch] [ebp-14h]

  __sub_414CE0_n0x7F800000 = ::__sub_414CE0_n0x7F800000;
  v1 = (_BYTE *)__sub_414CE0_Buffer_0;
  v2 = __sub_414CE0_byte_4456F0;
  v3 = __sub_414CE0_dword_4456E8;
  v4 = __sub_414CE0_dword_4456EC;
  if ( (unsigned int)::__sub_414CE0_n0x800000 <= 0x800000 )
  {
    v20 = __sub_414CE0_dword_4456EC;
    v18 = __sub_414CE0_byte_4456F0;
    __sub_414CE0_n0x800000 = ::__sub_414CE0_n0x800000;
    while ( 1 )
    {
      ++v20;
      v5 = v3;
      v6 = v3;
      if ( __sub_414CE0_n0x7F800000 < 0x7F800000 )
        break;
      if ( (__sub_414CE0_n0x7F800000 & 0x80000000) != 0 )
      {
        v7 = 1;
LABEL_8:
        *v1 = v7 + v18;
        v1 = (_BYTE *)++__sub_414CE0_Buffer_0;
        if ( v3 )
        {
          v8 = 0;
          v9 = v7 - 1;
          do
          {
            *v1 = v9;
            v1 = (_BYTE *)++__sub_414CE0_Buffer_0;
            v3 = v6 - v8++ - 1;
          }
          while ( v8 < v5 );
          __sub_414CE0_dword_4456E8 = v6 - v5;
        }
        v18 = __sub_414CE0_n0x7F800000 >> 23;
        __sub_414CE0_byte_4456F0 = v18;
        goto LABEL_13;
      }
      __sub_414CE0_dword_4456E8 = ++v3;
LABEL_13:
      n0x800000_1 = __sub_414CE0_n0x800000 << 8;
      __sub_414CE0_n0x800000 = n0x800000_1;
      __sub_414CE0_n0x7F800000 = (__sub_414CE0_n0x7F800000 << 8) & 0x7FFFFFFF;
      if ( n0x800000_1 > 0x800000 )
      {
        v4 = v20;
        v2 = v18;
        ::__sub_414CE0_n0x7F800000 = __sub_414CE0_n0x7F800000;
        ::__sub_414CE0_n0x800000 = n0x800000_1;
        goto LABEL_15;
      }
    }
    v7 = 0;
    goto LABEL_8;
  }
LABEL_15:
  v11 = v4 + 5;
  __sub_414CE0_dword_4456EC = v11;
  n0xFF = ((__sub_414CE0_n0x7F800000 & 0x7FFFFF) >= (v11 & 0xFFFFFFu) >> 1) + (__sub_414CE0_n0x7F800000 >> 23);
  *v1 = v2 + (n0xFF > 0xFF);
  v13 = (_BYTE *)++__sub_414CE0_Buffer_0;
  if ( v3 )
  {
    if ( v3 >> 1 )
    {
      v14 = 0;
      v15 = (n0xFF > 0xFF) - 1;
      do
      {
        *v13 = v15;
        *(_BYTE *)++__sub_414CE0_Buffer_0 = v15;
        ++v14;
        v13 = (_BYTE *)++__sub_414CE0_Buffer_0;
      }
      while ( v14 < v3 >> 1 );
      v16 = 2 * v14 + 1;
    }
    else
    {
      v16 = 1;
    }
    if ( v3 > v16 - 1 )
    {
      *v13 = (n0xFF > 0xFF) - 1;
      v13 = (_BYTE *)++__sub_414CE0_Buffer_0;
    }
    __sub_414CE0_dword_4456E8 = 0;
  }
  *v13 = n0xFF;
  *(_BYTE *)++__sub_414CE0_Buffer_0 = BYTE2(v11);
  *(_BYTE *)++__sub_414CE0_Buffer_0 = BYTE1(v11);
  *(_BYTE *)++__sub_414CE0_Buffer_0 = v11;
  v17 = (_BYTE *)(__sub_414CE0_Buffer_0 + 1);
  for ( __sub_414CE0_Buffer_0 = (int)v17; (((_BYTE)v17 - (_BYTE)__sub_414CE0_Buffer) & 3) != 3; __sub_414CE0_Buffer_0 = (int)v17 )
  {
    *v17 = 0;
    v17 = (_BYTE *)(__sub_414CE0_Buffer_0 + 1);
  }
  *v17 = -105;
  ++__sub_414CE0_Buffer_0;
  __sub_414CE0_n8 = 0;
  __sub_414CE0_n256 = 0;
  __sub_414CE0_Buffer_1 = __sub_414CE0_Buffer_0;
  if ( __sub_414CE0_dword_443364 )
    __op_delete(__sub_414CE0_n256_1);
}

#undef FILE
