// sub_412300 @ 0x00412300 — __cdecl
// Extracted from BMF.cpp:16313-16331 by extract.py per incdec.md.

typedef int t_sub_412300_dword_4456E8;
static t_sub_412300_dword_4456E8& __sub_412300_dword_4456E8 = *(t_sub_412300_dword_4456E8*)(blob1 + 0x004456E8 - BMF_BLOB_BASE);
typedef int t_sub_412300_n0x2000;
static t_sub_412300_n0x2000& __sub_412300_n0x2000 = *(t_sub_412300_n0x2000*)(blob1 + 0x004456FC - BMF_BLOB_BASE);
typedef int t_sub_412300_n0x2000_0;
static t_sub_412300_n0x2000_0& __sub_412300_n0x2000_0 = *(t_sub_412300_n0x2000_0*)(blob1 + 0x004456F8 - BMF_BLOB_BASE);
typedef int t_sub_412300_n0x2000_1;
static t_sub_412300_n0x2000_1& __sub_412300_n0x2000_1 = *(t_sub_412300_n0x2000_1*)(blob1 + 0x004456F4 - BMF_BLOB_BASE);
typedef int t_sub_412300_n0x7F800000;
static t_sub_412300_n0x7F800000& __sub_412300_n0x7F800000 = *(t_sub_412300_n0x7F800000*)(blob1 + 0x004456E4 - BMF_BLOB_BASE);
typedef int t_sub_412300_n0x800000;
static t_sub_412300_n0x800000& __sub_412300_n0x800000 = *(t_sub_412300_n0x800000*)(blob1 + 0x004456E0 - BMF_BLOB_BASE);


PROBE_DECL(__sub_412300)
BMF_REALIGN int __sub_412300()
{
  PROBE_HIT(__sub_412300);
  int result; // eax
  int __sub_412300_n0x800000; // edi

  result = __sub_412300_n0x2000_1 * __sub_412300_dword_4456E8;
  __sub_412300_n0x7F800000 -= __sub_412300_n0x2000_1 * __sub_412300_dword_4456E8;
  __sub_412300_n0x800000 = ::__sub_412300_n0x800000 - __sub_412300_n0x2000_1 * __sub_412300_dword_4456E8;
  if ( __sub_412300_n0x2000_0 < (unsigned int)__sub_412300_n0x2000 )
    __sub_412300_n0x800000 = (__sub_412300_n0x2000_0 - __sub_412300_n0x2000_1) * __sub_412300_dword_4456E8;
  ::__sub_412300_n0x800000 = __sub_412300_n0x800000;
  return result;
}

