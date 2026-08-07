// exit_402E40 @ 0x00402E40 — __stdcall
// Extracted from BMF.c:2484-2489 by extract.py per incdec.md.

typedef int t_exit_402E40_off_441068;
static t_exit_402E40_off_441068& __exit_402E40_off_441068 = *(t_exit_402E40_off_441068*)0x00441068;
#define off_441068 __exit_402E40_off_441068


// BMF links the MSVC CRT into the image, so these route to the PE's
// own implementations — its FILE* objects and heap blocks belong to
// that private runtime, not to glibc (§6.5).
#ifndef __PE_DECL___exit
#define __PE_DECL___exit
typedef void t_exit(int);   // _exit
static t_exit& __exit = *(t_exit*)0x0042D216;
#endif
#define exit __exit
#ifndef __PE_DECL___printf
#define __PE_DECL___printf
typedef int t_printf(const char *, ...);   // _printf
static t_printf& __printf = *(t_printf*)0x0042CBDB;
#endif
#define printf __printf
#ifndef __PE_DECL___vprintf
#define __PE_DECL___vprintf
typedef int t_vprintf(const char *, void *);   // _vprintf
static t_vprintf& __vprintf = *(t_vprintf*)0x0042D1B9;
#endif
#define vprintf __vprintf
#define FILE FILE1

PROBE_DECL(__exit_402E40)
__attribute__((stdcall)) void __exit_402E40(int Code, char ArgList)
{
  PROBE_HIT(__exit_402E40);
  vprintf((&off_441068)[Code], &ArgList);       // "e-mail: <dmitry.shkarin@mtu-net.ru>;  web: http://compression.graphicon.ru/ds/\nInput formats: BMP,TGA,PNM,RAS,GIF,RAW;       Output formats: BMP,TGA,PNM,RAW;\nUsage: BMF [switches] FName[s] [[switches] FName[s]]\nStandalone switch can be turned off by '-' symbol appending\n\t-F     - use image Filters: %s\n\t-Q<N>  - filter selection Quality - [0,9]: %d\n\t-S     - use Slow, but efficient compression: %s\n\t-E<N>  - set maximal allowed Error for near-lossless mode - [0,15]: %d\n\t-T<N>  - filters Template usage - [0: disable, 1: store, 2: use]: %d\n\t-N     - do Not pack output files: %s\n\t-<ext> - set output file type for decompression - [bmp,tga,pnm]: %s\n\t-D     - Delete file after processing: %s\n\t-O<FName> - set Output file name to FName: %s\n-R[-][H<N1>][X<N2>][Y<N3>][B<N4>][L<N5>][A[-]] - read Raw image file: %s\nwith Header size N1(%d), X size N2(%d), Y size N3(%d), Bytes per pixel\nN4(%d), scanline aLignment N5(%d) and Archiving mode(%s)"
  printf("\n");
  exit(Code);
}

#undef FILE
#undef exit
#undef printf
#undef vprintf
#undef off_441068
