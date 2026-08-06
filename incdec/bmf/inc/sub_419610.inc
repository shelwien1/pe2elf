// sub_419610 @ 0x00419610 — __thiscall
// Extracted from BMF.c:23705-23717 by extract.py per incdec.md.


// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___VirtualFree
#define __PE_DECL___VirtualFree
typedef __attribute__((stdcall)) int (*pfn_VirtualFree)(void *, unsigned int, unsigned int);
static pfn_VirtualFree& VirtualFree = *(pfn_VirtualFree*)0x00438020;   // IAT slot
#endif
#ifndef __PE_DECL___op_delete
#define __PE_DECL___op_delete
typedef void t_op_delete(void *);       // ??3@YAXPAX@Z
static t_op_delete& __op_delete = *(t_op_delete*)0x0042CF18;
#endif
#define FILE FILE1

PROBE_DECL(__sub_419610)
__attribute__((thiscall)) void **__sub_419610(void **lpAddress, char a2)
{
  PROBE_HIT(__sub_419610);
  __op_delete(*(lpAddress + 69689));
  __op_delete(*(lpAddress + 69690));
  __op_delete(*(lpAddress + 69691));
  __op_delete(*(lpAddress + 69692));
  __op_delete(*(lpAddress + 69693));
  __op_delete(*(lpAddress + 69665));
  __op_delete(*(lpAddress + 69666));
  if ( (a2 & 1) != 0 )
    VirtualFree(lpAddress, 0, MEM_RELEASE);
  return lpAddress;
}

#undef FILE
