// sub_412300 @ 0x00412300 — __cdecl
// Extracted from BMF.c:16254-16273 by extract.py per incdec.md.

typedef int t_sub_412300_dword_4456E8;
static t_sub_412300_dword_4456E8& __sub_412300_dword_4456E8 = *(t_sub_412300_dword_4456E8*)0x004456E8;
#define dword_4456E8 __sub_412300_dword_4456E8
typedef int t_sub_412300_dword_4456F4;
static t_sub_412300_dword_4456F4& __sub_412300_dword_4456F4 = *(t_sub_412300_dword_4456F4*)0x004456F4;
#define dword_4456F4 __sub_412300_dword_4456F4
typedef int t_sub_412300_n0x2000;
static t_sub_412300_n0x2000& __sub_412300_n0x2000 = *(t_sub_412300_n0x2000*)0x004456FC;
#define n0x2000 __sub_412300_n0x2000
typedef int t_sub_412300_n0x2000_0;
static t_sub_412300_n0x2000_0& __sub_412300_n0x2000_0 = *(t_sub_412300_n0x2000_0*)0x004456F8;
#define n0x2000_0 __sub_412300_n0x2000_0
typedef int t_sub_412300_n0x7F800000;
static t_sub_412300_n0x7F800000& __sub_412300_n0x7F800000 = *(t_sub_412300_n0x7F800000*)0x004456E4;
#define n0x7F800000 __sub_412300_n0x7F800000
typedef int t_sub_412300_n0x800000;
static t_sub_412300_n0x800000& __sub_412300_n0x800000 = *(t_sub_412300_n0x800000*)0x004456E0;
#define n0x800000 __sub_412300_n0x800000


PROBE_DECL(__sub_412300)
int __sub_412300()
{
  PROBE_HIT(__sub_412300);
  int result; // eax
  int n0x800000; // edi

  result = dword_4456F4 * dword_4456E8;
  n0x7F800000 -= dword_4456F4 * dword_4456E8;
  n0x800000 = ::n0x800000 - dword_4456F4 * dword_4456E8;
  if ( n0x2000_0 < (unsigned int)n0x2000 )
    n0x800000 = (n0x2000_0 - dword_4456F4) * dword_4456E8;
  ::n0x800000 = n0x800000;
  return result;
}

#undef dword_4456E8
#undef dword_4456F4
#undef n0x2000
#undef n0x2000_0
#undef n0x7F800000
#undef n0x800000
