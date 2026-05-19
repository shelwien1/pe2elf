// =====================================================================
// PrintStats @ 0x1400028D0
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___Buffer
#define __PE_DECL___Buffer
static void *& __Buffer = *(void **)0x140028E40;
#endif
#define Buffer __Buffer
#ifndef __PE_DECL___arch_hdr
#define __PE_DECL___arch_hdr
typedef int t_arch_hdr[16];
static t_arch_hdr& __arch_hdr = *(t_arch_hdr*)0x140028E50;
#endif
#define arch_hdr __arch_hdr
#ifndef __PE_DECL___f_ENC
#define __PE_DECL___f_ENC
static int& __f_ENC = *(int*)0x140028E48;
#endif
#define f_ENC __f_ENC
#ifndef __PE_DECL___f_LOG
#define __PE_DECL___f_LOG
static int& __f_LOG = *(int*)0x140028E4C;
#endif
#define f_LOG __f_LOG

// ---- PE-internal function references --------------------------------
#ifndef __PE_DECL___clock
#define __PE_DECL___clock
typedef __attribute__((ms_abi)) clock_t t_clock();
static t_clock& __clock = *(t_clock*)0x140012D88;
#endif
#define clock __clock
#ifndef __PE_DECL___fclose_nolock
#define __PE_DECL___fclose_nolock
typedef __attribute__((ms_abi)) int t_fclose_nolock(FILE *Stream);
static t_fclose_nolock& __fclose_nolock = *(t_fclose_nolock*)0x1400125F4;
#endif
#define fclose_nolock __fclose_nolock
#ifndef __PE_DECL___fflush_nolock
#define __PE_DECL___fflush_nolock
typedef __attribute__((ms_abi)) int t_fflush_nolock(FILE *Stream);
static t_fflush_nolock& __fflush_nolock = *(t_fflush_nolock*)0x1400130F4;
#endif
#define fflush_nolock __fflush_nolock
#ifndef __PE_DECL___fopen
#define __PE_DECL___fopen
typedef __attribute__((ms_abi)) FILE * t_fopen(const char *FileName, const char *Mode);
static t_fopen& __fopen = *(t_fopen*)0x140011F80;
#endif
#define fopen __fopen
#ifndef __PE_DECL___fprintf
#define __PE_DECL___fprintf
typedef __attribute__((ms_abi)) int t_fprintf(FILE *const Stream, const char *const Format, ...);
static t_fprintf& __fprintf = *(t_fprintf*)0x1400135C4;
#endif
#define fprintf __fprintf
#ifndef __PE_DECL___ftell_nolock
#define __PE_DECL___ftell_nolock
typedef __attribute__((ms_abi)) int t_ftell_nolock(FILE *Stream);
static t_ftell_nolock& __ftell_nolock = *(t_ftell_nolock*)0x140012DF8;
#endif
#define ftell_nolock __ftell_nolock
#ifndef __PE_DECL___printf
#define __PE_DECL___printf
typedef __attribute__((ms_abi)) int t_printf(const char *const Format, ...);
static t_printf& __printf = *(t_printf*)0x140011B20;
#endif
#define printf __printf
#ifndef __PE_DECL___sprintf
#define __PE_DECL___sprintf
typedef __attribute__((ms_abi)) int t_sprintf(char *const Buffer, const char *const Format, ...);
static t_sprintf& __sprintf = *(t_sprintf*)0x140013528;
#endif
#define sprintf __sprintf
#define sub_1400032F0 __sub_1400032F0
#define sub_140012804 __sub_140012804

PROBE_DECL(__PrintStats)
__attribute__((ms_abi)) __int64 __PrintStats(FILE *Stream, FILE *a2, int a3) {

  PROBE_HIT(__PrintStats);
  clock_t v6;         // ebx
  int v8;             // edi
  unsigned int v9;    // edi
  __int64 v10;        // r15
  int v11;            // esi
  int v12;            // r10d
  int v13;            // ebx
  int v14;            // ebp
  __int64 v15;        // kr00_8
  int v16;            // r10d
  unsigned int v17;   // ebx
  unsigned int v18;   // eax
  unsigned int v19;   // r11d
  unsigned int v20;   // eax
  unsigned int v21;   // ecx
  unsigned int v22;   // r9d
  __int64 v23;        // r8
  char (**v24)[4096]; // rax
  FILE *v25;          // rbx
  char Buffer[568];   // [rsp+50h] [rbp-238h] BYREF

  v6 = clock();
  if(v6 < arch_hdr[7] + 500 && !a3)
    return 0x10000;
  v8 = ftell_nolock(Stream);
  v9 = (v8 == 0) + v8;
  v10 = (unsigned int)(ftell_nolock(a2) - arch_hdr[6]);
  arch_hdr[7] = v6;
  v11 = 8 * v10 / v9;
  v12 = (v6 - arch_hdr[5]) << 10;
  v13 = 1;
  v14 = (1000 * (8 * v10 - v11 * v9) + (v9 >> 1)) / v9;
  v15 = 274877907LL * v12;
  if(v14 == 1000) {
    ++v11;
    v14 = 0;
  }
  v16 = v12 >> 31;
  if(SHIDWORD(v15) >> 6 != v16)
    v13 = 0;
  v17 = v9 / (v13 + (SHIDWORD(v15) >> 6) - v16);
  v18 = sub_1400032F0();
  v19 = v18 >> 10;
  v20 = v18 >> 20;
  v21 = (10 * (v19 - (v20 << 10)) + 512) >> 10;
  if(v21 == 10) {
    ++v20;
    v21 = 0;
  }
  v22 = v9;
  if(!f_ENC) {
    v22 = v10;
    LODWORD(v10) = v9;
  }
  sprintf(Buffer, "%15s:%7d >%7d, %1d.%03d bpb, used:%3d.%1d MB, speed: %d KB/sec.", (const char *)::Buffer, v22, v10, v11, v14, v20, v21, v17);
  v23 = 13;
  if(a3)
    v23 = 10;
  printf("%-79.79s%c", Buffer, v23);
  v24 = sub_140012804();
  fflush_nolock((FILE *)v24 + 1);
  if(a3) {
    if(f_LOG) {
      v25 = fopen("!ratios.lst", "a+t");
      fprintf(v25, "%s\n", Buffer);
      fclose_nolock(v25);
    }
  }
  return 0x10000;
}
// 140028E48: using guessed type int f_ENC;
// 140028E4C: using guessed type int f_LOG;
// 140028E50: using guessed type int arch_hdr[16];

// ---- Cleanup --------------------------------------------------------
#undef Buffer
#undef arch_hdr
#undef f_ENC
#undef f_LOG
#undef clock
#undef fclose_nolock
#undef fflush_nolock
#undef fopen
#undef fprintf
#undef ftell_nolock
#undef printf
#undef sprintf
#undef sub_1400032F0
#undef sub_140012804
#undef FILE
