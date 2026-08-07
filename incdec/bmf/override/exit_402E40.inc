// exit_402E40 @ 0x00402E40 — __cdecl, variadic
// HAND-WRITTEN override.  Not extract.py output; see override/README.md.
//
// This is BMF's "print message N and quit".  Eight instructions:
//
//   00402E40  mov   edx, [esp+4]              ; Code
//   00402E44  lea   eax, [esp+8]              ; &first vararg
//   00402E48  push  eax
//   00402E49  push  off_441068[edx*4]         ; Format
//   00402E50  call  _vprintf
//   00402E55  push  offset asc_438744         ; "\n"
//   00402E5A  call  _printf
//   00402E5F  push  [esp+0Ch+Code]
//   00402E63  call  _exit
//
// `lea eax, [esp+8]` is a va_list: the function is `__cdecl exit_402E40(int
// Code, ...)`, and it forwards everything after Code to vprintf against
// off_441068[Code].  IDA typed it `__stdcall exit_402E40(int Code, char
// ArgList)` — one `char` — and that is wrong in both halves.  It never cleans
// the stack (it never returns; the callers' `add esp, N` is dead code), and
// the argument is a whole variable-length list, not a byte.
//
// The consequence was invisible for a long time because the gate never runs an
// error path.  Every call site had its arguments truncated to `(char)ptr`, so
// every message printed garbage, and the usage screen — sixteen conversions
// against one pushed byte — walked off the end of the argument block.  Under
// the shim, BMF's own vprintf read wild pointers and survived; standalone,
// glibc's %s dereferenced one and the process died.  fixups.txt restores the
// arguments at all thirty call sites (§8.2.5, the same class of loss as
// __libm_sse2_log's missing xmm0).
//
// Nine messages, from the table at 0x00441068: 0 is the usage screen and takes
// sixteen arguments, 1/2/3/5/6 take one `%s`, and 4 ("Read error!"),
// 7 ("Out of memory!") and 8 ("User break!") take none.

// The CRT entries, spelled the way a generated .inc spells them, so that the
// standalone build's crt.cpp can pre-empt them through the same guards and the
// hybrid still reaches the PE's own stdout — mixing glibc's buffered stdout
// with the PE CRT's would reorder the output (§6.5).
#ifndef __PE_DECL___exit
#define __PE_DECL___exit
typedef void t_exit(int);   // _exit
static t_exit& __exit = *(t_exit*)0x0042D216;
#endif
#ifndef __PE_DECL___printf
#define __PE_DECL___printf
typedef int t_printf(const char *, ...);   // _printf
static t_printf& __printf = *(t_printf*)0x0042CBDB;
#endif
#ifndef __PE_DECL___vprintf
#define __PE_DECL___vprintf
typedef int t_vprintf(const char *, void *);   // _vprintf
static t_vprintf& __vprintf = *(t_vprintf*)0x0042D1B9;
#endif

#ifndef __PE_DECL___exit_402E40_off_441068
#define __PE_DECL___exit_402E40_off_441068
typedef const char *t_exit_402E40_off_441068;
static t_exit_402E40_off_441068& __exit_402E40_off_441068 = *(t_exit_402E40_off_441068*)0x00441068;
#endif

PROBE_DECL(__exit_402E40)
__attribute__((noreturn)) void __exit_402E40(int Code, ...)
{
  PROBE_HIT(__exit_402E40);
  va_list ap;
  va_start(ap, Code);
  // i386 SysV makes va_list a plain `char *` into the argument block, which is
  // exactly the pointer the donor computes with `lea eax, [esp+8]` — so the
  // PE's vprintf, typed `int (const char *, void *)`, takes it unchanged.
  __vprintf((&__exit_402E40_off_441068)[Code], (void *)ap);
  va_end(ap);
  __printf("\n");
  __exit(Code);
  __builtin_unreachable();
}
