// sub_414920 @ 0x00414920 — __cdecl
// Extracted from BMF.c:19021-19068 by extract.py per incdec.md.

typedef int t_sub_414920_Buffer_0;
static t_sub_414920_Buffer_0& __sub_414920_Buffer_0 = *(t_sub_414920_Buffer_0*)0x00443378;
#define Buffer_0 __sub_414920_Buffer_0
typedef int t_sub_414920_Buffer_1;
static t_sub_414920_Buffer_1& __sub_414920_Buffer_1 = *(t_sub_414920_Buffer_1*)0x00443374;
#define Buffer_1 __sub_414920_Buffer_1
typedef char t_sub_414920_byte_4456F0;
static t_sub_414920_byte_4456F0& __sub_414920_byte_4456F0 = *(t_sub_414920_byte_4456F0*)0x004456F0;
#define byte_4456F0 __sub_414920_byte_4456F0
typedef int t_sub_414920_dword_443364;
static t_sub_414920_dword_443364& __sub_414920_dword_443364 = *(t_sub_414920_dword_443364*)0x00443364;
#define dword_443364 __sub_414920_dword_443364
typedef int t_sub_414920_n0x7F800000;
static t_sub_414920_n0x7F800000& __sub_414920_n0x7F800000 = *(t_sub_414920_n0x7F800000*)0x004456E4;
#define n0x7F800000 __sub_414920_n0x7F800000
typedef int t_sub_414920_n0x800000;
static t_sub_414920_n0x800000& __sub_414920_n0x800000 = *(t_sub_414920_n0x800000*)0x004456E0;
#define n0x800000 __sub_414920_n0x800000
typedef int t_sub_414920_n256;
static t_sub_414920_n256& __sub_414920_n256 = *(t_sub_414920_n256*)0x0044336C;
#define n256 __sub_414920_n256
typedef int t_sub_414920_n256_1;
static t_sub_414920_n256_1& __sub_414920_n256_1 = *(t_sub_414920_n256_1*)0x00445708;
#define n256_1 __sub_414920_n256_1
typedef int t_sub_414920_n8;
static t_sub_414920_n8& __sub_414920_n8 = *(t_sub_414920_n8*)0x00443368;
#define n8 __sub_414920_n8


// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___op_delete
#define __PE_DECL___op_delete
typedef void t_op_delete(void *);       // ??3@YAXPAX@Z
static t_op_delete& __op_delete = *(t_op_delete*)0x0042CF18;
#endif
#define FILE FILE1

PROBE_DECL(__sub_414920)
void __sub_414920()
{
  PROBE_HIT(__sub_414920);
  unsigned int n0x800000; // ecx
  unsigned __int8 *v1; // edx
  int n0x7F800000; // ebx
  unsigned int v3; // eax
  int v4; // ebx
  int n151; // eax

  n0x800000 = ::n0x800000;
  v1 = (unsigned __int8 *)Buffer_0;
  if ( (unsigned int)::n0x800000 <= 0x800000 )
  {
    n0x7F800000 = ::n0x7F800000;
    LOBYTE(v3) = byte_4456F0;
    do
    {
      v4 = (unsigned __int8)((_BYTE)v3 << 7) | (n0x7F800000 << 8);
      v3 = *v1++;
      Buffer_0 = (int)v1;
      n0x7F800000 = (v3 >> 1) | v4;
      n0x800000 <<= 8;
    }
    while ( n0x800000 <= 0x800000 );
    ::n0x800000 = n0x800000;
    byte_4456F0 = v3;
    ::n0x7F800000 = n0x7F800000;
  }
  do
  {
    n151 = *v1++;
    Buffer_0 = (int)v1;
  }
  while ( n151 != 151 );
  Buffer_1 = (int)v1;
  n8 = 0;
  n256 = 0;
  if ( dword_443364 )
    __op_delete(n256_1);
}

#undef FILE
#undef Buffer_0
#undef Buffer_1
#undef byte_4456F0
#undef dword_443364
#undef n0x7F800000
#undef n0x800000
#undef n256
#undef n256_1
#undef n8
