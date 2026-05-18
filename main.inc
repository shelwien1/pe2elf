// =====================================================================
// main @ 0x140001000
// All FILE * inside this body refers to MSVC _iobuf (FILE1 from PPMonstr.h),
// not glibc's FILE. The body uses MSVC CRT internals (->_cnt, ->_ptr,
// ->_flag) which only exist on the MSVC iobuf layout.
// =====================================================================

#define FILE FILE1

// ---- _BitScanForward intrinsic (MSVC -> GCC) ----
#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---- Data references --------------------------------------------------
typedef int t_arch_hdr_main[16];
static t_arch_hdr_main& __arch_hdr = *(t_arch_hdr_main*)0x140028E50;
static int& __f_ENC = *(int*)0x140028E48;
static int& __f_LOG = *(int*)0x140028E4C;
typedef void* t_Buffer_main;
static t_Buffer_main& __Buffer = *(t_Buffer_main*)0x140028E40;

#define arch_hdr __arch_hdr
#define f_ENC    __f_ENC
#define f_LOG    __f_LOG

// ---- PE-internal function references (direct entry points) ------------
typedef __attribute__((ms_abi)) int            t_printf_main(const char*, ...);
typedef __attribute__((ms_abi)) int            t_sprintf_main(char*, const char*, ...);
typedef __attribute__((ms_abi)) int            t_fprintf_main(FILE*, const char*, ...);
typedef __attribute__((ms_abi)) int            t_toupper_main(int);
typedef __attribute__((ms_abi)) int            t_atoi_main(const char*);
typedef __attribute__((ms_abi)) FILE*          t_fopen_main(const char*, const char*);
typedef __attribute__((ms_abi)) size_t         t_fread_main(void*, size_t, size_t, FILE*);
typedef __attribute__((ms_abi)) size_t         t_fwrite_main(const void*, size_t, size_t, FILE*);
typedef __attribute__((ms_abi)) int            t_fclose_main(FILE*);
typedef __attribute__((ms_abi)) int            t_ftell_main(FILE*);
typedef __attribute__((ms_abi)) int            t_fseek_main(FILE*, int, int);
typedef __attribute__((ms_abi)) int            t_fflush_main(FILE*);
typedef __attribute__((ms_abi)) int            t_setvbuf_main(FILE*, char*, int, size_t);
typedef __attribute__((ms_abi)) int            t_flsbuf_main(int, FILE*);
typedef __attribute__((ms_abi)) int            t_filbuf_main(FILE*);
typedef __attribute__((ms_abi)) int            t_fileno_main(FILE*);
typedef __attribute__((ms_abi)) int            t_chsize_main(int, int);
typedef __attribute__((ms_abi)) char*          t_strrchr_main(const char*, int);
typedef __attribute__((ms_abi)) void*          t_memmove_main(void*, const void*, size_t);
typedef __attribute__((ms_abi)) long           t_clock_main();
typedef __attribute__((ms_abi)) void           t_exit_main(int);
typedef __attribute__((ms_abi)) int            t_getch_main();
typedef __attribute__((ms_abi)) void*          t_op_new_main(size_t);
typedef __attribute__((ms_abi)) void           t_j_free_main(void*);
typedef __attribute__((ms_abi)) int            t_deletefile_main(wchar_t*);
typedef __attribute__((ms_abi)) char*          t_movemask_loop_main(__int64, __int64);
typedef __attribute__((ms_abi)) __int64        t_intel_new_proc_init_main(int, const char**, const char**);

typedef __attribute__((ms_abi)) __int64        t_PrintStats_main(FILE*, FILE*, int);
typedef __attribute__((ms_abi)) __int64        t_Alloc_PPMblock_main(unsigned int, int, int);
typedef __attribute__((ms_abi)) __int64        t_sub_140003530_main(FILE*, FILE*, __int64(*)(FILE*, FILE*, __int64), int);
typedef __attribute__((ms_abi)) __int64        t_sub_14000C310_main(FILE*, FILE*, __int64(*)(FILE*, FILE*, __int64), int);
typedef __attribute__((ms_abi)) __int64        t_sub_1400032F0_main();
typedef __attribute__((ms_abi)) char (**       t_sub_140012804_main())[4096];

static t_printf_main&            __printf            = *(t_printf_main*)0x140011B20;
static t_sprintf_main&           __sprintf           = *(t_sprintf_main*)0x140013528;
static t_fprintf_main&           __fprintf           = *(t_fprintf_main*)0x1400135C4;
static t_toupper_main&           __toupper           = *(t_toupper_main*)0x140011E14;
static t_atoi_main&              __atoi              = *(t_atoi_main*)0x140011E3C;
static t_fopen_main&             __fopen             = *(t_fopen_main*)0x140011F80;
static t_fread_main&             __fread_nolock      = *(t_fread_main*)0x1400121EC;
static t_fwrite_main&            __fwrite_nolock     = *(t_fwrite_main*)0x140012BEC;
static t_fclose_main&            __fclose_nolock     = *(t_fclose_main*)0x1400125F4;
static t_ftell_main&             __ftell_nolock      = *(t_ftell_main*)0x140012DF8;
static t_fseek_main&             __fseek_nolock      = *(t_fseek_main*)0x140012FC4;
static t_fflush_main&            __fflush_nolock     = *(t_fflush_main*)0x1400130F4;
static t_setvbuf_main&           __setvbuf           = *(t_setvbuf_main*)0x140012A80;
static t_flsbuf_main&            __flsbuf            = *(t_flsbuf_main*)0x14001323C;
static t_filbuf_main&            __filbuf            = *(t_filbuf_main*)0x1400133CC;
static t_fileno_main&            __fileno            = *(t_fileno_main*)0x140017228;
static t_chsize_main&            __chsize            = *(t_chsize_main*)0x14001D2A0;
static t_strrchr_main&           __strrchr           = *(t_strrchr_main*)0x140012A28;
static t_memmove_main&           __memmove           = *(t_memmove_main*)0x140019270;
static t_clock_main&             __clock             = *(t_clock_main*)0x140012D88;
static t_exit_main&              __exit              = *(t_exit_main*)0x140012554;
static t_getch_main&             __getch             = *(t_getch_main*)0x140021A08;
static t_op_new_main&            __op_new            = *(t_op_new_main*)0x140012768;
static t_j_free_main&            __j_free            = *(t_j_free_main*)0x140012FBC;
static t_deletefile_main&        __deletefile        = *(t_deletefile_main*)0x140012A50;
static t_movemask_loop_main&     __movemask_cmpeq_loop = *(t_movemask_loop_main*)0x14001D700;
static t_intel_new_proc_init_main& __intel_new_proc_init = *(t_intel_new_proc_init_main*)0x14001D5F0;

static t_PrintStats_main&        __PrintStats        = *(t_PrintStats_main*)0x1400028D0;
static t_Alloc_PPMblock_main&    __Alloc_PPMblock    = *(t_Alloc_PPMblock_main*)0x140003480;
static t_sub_140003530_main&     __sub_140003530     = *(t_sub_140003530_main*)0x140003530;
static t_sub_14000C310_main&     __sub_14000C310     = *(t_sub_14000C310_main*)0x14000C310;
static t_sub_1400032F0_main&     __sub_1400032F0     = *(t_sub_1400032F0_main*)0x1400032F0;
static t_sub_140012804_main&     __sub_140012804     = *(t_sub_140012804_main*)0x140012804;

#define printf                  __printf
#define sprintf                 __sprintf
#define fprintf                 __fprintf
#define toupper                 __toupper
#define atoi                    __atoi
#define fopen                   __fopen
#define fread_nolock            __fread_nolock
#define fwrite_nolock           __fwrite_nolock
#define fclose_nolock           __fclose_nolock
#define ftell_nolock            __ftell_nolock
#define fseek_nolock            __fseek_nolock
#define fflush_nolock           __fflush_nolock
#define setvbuf                 __setvbuf
#define flsbuf                  __flsbuf
#define filbuf                  __filbuf
#define fileno                  __fileno
#define chsize                  __chsize
#define strrchr                 __strrchr
#define memmove                 __memmove
#define clock                   __clock
#define exit                    __exit
#define getch                   __getch
#define j_free                  __j_free
#define deletefile              __deletefile
#define movemask_cmpeq_loop     __movemask_cmpeq_loop
#define _intel_new_proc_init    __intel_new_proc_init

#define PrintStats              __PrintStats
#define Alloc_PPMblock          __Alloc_PPMblock
#define sub_140003530           __sub_140003530
#define sub_14000C310           __sub_14000C310
#define sub_140003370           __sub_140003370
#define sub_1400032F0           __sub_1400032F0
#define sub_140012804           __sub_140012804

// strcpy: not in PPMonstr.txt (MSVC intrinsic / inlined). Use glibc's; the
// only call here copies bytes within local buffers, so the libc semantic
// is identical to what the PE's inlined copy would do.

// ---- Win pointer typedefs missing from PPMonstr.h --------------------
typedef _WIN32_FIND_DATAA   *LPWIN32_FIND_DATAA;
typedef FILETIME            *LPFILETIME;
typedef _SECURITY_ATTRIBUTES *LPSECURITY_ATTRIBUTES;

// ---- WinAPI imports via IAT slots ------------------------------------
typedef __attribute__((ms_abi)) HANDLE  (*pfn_FindFirstFileA)(LPCSTR, LPWIN32_FIND_DATAA);
typedef __attribute__((ms_abi)) BOOL    (*pfn_FindNextFileA)(HANDLE, LPWIN32_FIND_DATAA);
typedef __attribute__((ms_abi)) BOOL    (*pfn_FindClose)(HANDLE);
typedef __attribute__((ms_abi)) BOOL    (*pfn_SetFileAttributesA)(LPCSTR, DWORD);
typedef __attribute__((ms_abi)) BOOL    (*pfn_FileTimeToDosDateTime)(const FILETIME*, LPWORD, LPWORD);
typedef __attribute__((ms_abi)) DWORD   (*pfn_GetCurrentDirectoryA)(DWORD, LPSTR);
typedef __attribute__((ms_abi)) BOOL    (*pfn_DosDateTimeToFileTime)(WORD, WORD, LPFILETIME);
typedef __attribute__((ms_abi)) HANDLE  (*pfn_CreateFileA)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
typedef __attribute__((ms_abi)) BOOL    (*pfn_SetFileTime)(HANDLE, const FILETIME*, const FILETIME*, const FILETIME*);
typedef __attribute__((ms_abi)) BOOL    (*pfn_CloseHandle)(HANDLE);

static pfn_FindFirstFileA&        FindFirstFileA        = *(pfn_FindFirstFileA*)0x140022000;
static pfn_FindNextFileA&         FindNextFileA         = *(pfn_FindNextFileA*)0x140022008;
static pfn_FindClose&             FindClose             = *(pfn_FindClose*)0x140022010;
static pfn_SetFileAttributesA&    SetFileAttributesA    = *(pfn_SetFileAttributesA*)0x140022018;
static pfn_FileTimeToDosDateTime& FileTimeToDosDateTime = *(pfn_FileTimeToDosDateTime*)0x140022020;
static pfn_GetCurrentDirectoryA&  GetCurrentDirectoryA  = *(pfn_GetCurrentDirectoryA*)0x140022028;
static pfn_DosDateTimeToFileTime& DosDateTimeToFileTime = *(pfn_DosDateTimeToFileTime*)0x140022030;
static pfn_CreateFileA&           CreateFileA           = *(pfn_CreateFileA*)0x140022038;
static pfn_SetFileTime&           SetFileTime           = *(pfn_SetFileTime*)0x140022040;
static pfn_CloseHandle&           CloseHandle           = *(pfn_CloseHandle*)0x140022048;

// ---- Body ------------------------------------------------------------
PROBE_DECL(__main)
__attribute__((ms_abi)) int __main(int argc, const char **argv, const char **envp) {
  PROBE_HIT(__main);
  int reset_type_val;                    // ebp
  int order_val;                         // r12d
  int mem_val;                           // r13d
  const char *v8;                        // r15
  int v9;                                // eax
  __int64 v10;                           // r15
  const char **v11;                      // rbx
  const char *v12;                       // rdi
  int v13;                               // eax
  char *v14;                             // rdi
  char *v15;                             // rsi
  char v16;                              // dl
  FILE *v17;                             // rax
  FILE *v18;                             // rsi
  const char **v19;                      // rdi
  int v21;                               // esi
  const char **v22;                      // rdi
  void **p_Block;                        // rbx
  HANDLE FirstFileA;                     // rax
  void **v25;                            // rax
  __int64 v26;                           // r10
  __int64 v27;                           // r10
  char *v28;                             // r14
  char (**v29)[4096];                    // rax
  int v30;                               // r15d
  int v31;                               // r13d
  __int64 v32;                           // rbp
  char *v33;                             // rbx
  bool v34;                              // zf
  char *v35;                             // rax
  signed __int64 v36;                    // rbx
  char *v37;                             // rax
  CHAR *v38;                             // rdx
  int v39;                               // ecx
  FILE *v40;                             // rax
  int v41;                               // eax
  int v42;                               // eax
  FILE *v43;                             // rax
  FILE *v44;                             // rsi
  FILE *v45;                             // rax
  FILE *v46;                             // rdi
  char *v47;                             // rax
  void *v48;                             // rbx
  int v49;                               // eax
  int v50;                               // ebx
  FILE *v51;                             // rax
  FILE *v52;                             // rbx
  char *v53;                             // rax
  const char *v54;                       // rdi
  char *v55;                             // rsi
  char *v56;                             // rax
  signed __int64 v57;                    // rsi
  char *v58;                             // rax
  char *v59;                             // rdx
  int v60;                               // ecx
  signed __int64 v61;                    // rax
  signed __int64 v62;                    // rax
  int v63;                               // eax
  int v64;                               // eax
  int v65;                               // eax
  char v66;                              // al
  int v67;                               // eax
  int v68;                               // ecx
  FILE *v69;                             // rax
  FILE *v70;                             // rax
  FILE *v71;                             // rdi
  int v72;                               // esi
  int v73;                               // eax
  int v74;                               // eax
  char v75;                              // al
  clock_t v76;                           // esi
  int v77;                               // esi
  int v78;                               // ecx
  __int64 v79;                           // rax
  unsigned int v80;                      // eax
  unsigned int v81;                      // ecx
  unsigned int v82;                      // edx
  unsigned int v83;                      // eax
  unsigned int v84;                      // r10d
  unsigned int v85;                      // r9d
  FILE *v86;                             // rsi
  int flag;                              // edx
  HANDLE FileA;                          // rsi
  FILE *v89;                             // r13
  int v90;                               // eax
  int v91;                               // eax
  FILE *v92;                             // rax
  FILE *v93;                             // rax
  FILE *v94;                             // rbp
  unsigned int v95;                      // esi
  int v96;                               // r14d
  int v97;                               // r15d
  int v98;                               // eax
  int v99;                               // eax
  char v100;                             // al
  clock_t v101;                          // r15d
  int v102;                              // esi
  unsigned int v103;                     // esi
  int v104;                              // eax
  int v105;                              // r14d
  __int64 v106;                          // r12
  int v107;                              // edi
  int v108;                              // r15d
  int v109;                              // ecx
  int v110;                              // r12d
  unsigned int v111;                     // r15d
  unsigned int v112;                     // eax
  unsigned int v113;                     // r11d
  unsigned int v114;                     // eax
  unsigned int v115;                     // r10d
  unsigned int v116;                     // r9d
  FILE *v117;                            // rsi
  int v118;                              // edx
  HANDLE v119;                           // rbp
  int v120;                              // eax
  int v121;                              // eax
  int v122;                              // eax
  int v123;                              // ecx
  int v124;                              // eax
  int v125;                              // ecx
  HANDLE hTemplateFile;                  // [rsp+30h] [rbp-B78h]
  __int64 v127;                          // [rsp+38h] [rbp-B70h]
  __int64 v128;                          // [rsp+40h] [rbp-B68h]
  __int64 v129;                          // [rsp+48h] [rbp-B60h]
  char v130[4];                          // [rsp+50h] [rbp-B58h] BYREF
  char v131[512];                        // [rsp+250h] [rbp-958h] BYREF
  CHAR Buffer[260];                      // [rsp+450h] [rbp-758h] BYREF
  int v133;                              // [rsp+554h] [rbp-654h] BYREF
  unsigned int v134;                     // [rsp+558h] [rbp-650h]
  int v135;                              // [rsp+560h] [rbp-648h]
  unsigned int v136;                     // [rsp+568h] [rbp-640h]
  unsigned int v137;                     // [rsp+570h] [rbp-638h]
  int v138;                              // [rsp+578h] [rbp-630h]
  struct _FILETIME FileTime;             // [rsp+580h] [rbp-628h] BYREF
  unsigned int v140;                     // [rsp+588h] [rbp-620h]
  int v141;                              // [rsp+590h] [rbp-618h]
  CHAR v142[260];                        // [rsp+598h] [rbp-610h] BYREF
  FILETIME LastWriteTime;                // [rsp+69Ch] [rbp-50Ch] BYREF
  CHAR v144[260];                        // [rsp+6A4h] [rbp-504h] BYREF
  int v145;                              // [rsp+7A8h] [rbp-400h] BYREF
  int v146;                              // [rsp+7ACh] [rbp-3FCh] BYREF
  char v147[264];                        // [rsp+7B0h] [rbp-3F8h] BYREF
  int v148;                              // [rsp+8B8h] [rbp-2F0h]
  CHAR FileName[264];                    // [rsp+8C0h] [rbp-2E8h] BYREF
  __int64 v150;                          // [rsp+9C8h] [rbp-1E0h]
  __int64 v151;                          // [rsp+9D0h] [rbp-1D8h]
  HANDLE v152;                           // [rsp+9D8h] [rbp-1D0h]
  HANDLE hFindFile;                      // [rsp+9E0h] [rbp-1C8h]
  struct _WIN32_FIND_DATAA FindFileData; // [rsp+9E8h] [rbp-1C0h] BYREF
  int v155;                              // [rsp+B28h] [rbp-80h]
  char *v156;                            // [rsp+B30h] [rbp-78h]
  char *v157;                            // [rsp+B38h] [rbp-70h]
  int v158;                              // [rsp+B40h] [rbp-68h]
  int v159;                              // [rsp+B48h] [rbp-60h]
  FILE *Stream;                          // [rsp+B50h] [rbp-58h]
  void *Block;                           // [rsp+B58h] [rbp-50h] BYREF

  _intel_new_proc_init(3, argv, envp);
  *(_DWORD *)v130 = _mm_getcsr() | 0x8040;
  _mm_setcsr(*(unsigned int *)v130);
  reset_type_val = 1;
  order_val = 12;
  mem_val = 256;
  printf("Monstrous PPMII compressor based on modified PPMd var.%c, Oct 16 2020\n", 74);
  if(argc < 3) {
    printf("var.J + TSE, CC rate - 1.850bpb,\n"
           "designed and written by Dmitry Shkarin <dmitry.shkarin@mtu-net.ru>\n"
           "Usage: PPMonstr <e|d> [switches] <FileName[s] | Wildcard[s]>\n"
           "Switches (for encoding only):\n"
           "\t-d     - delete file[s] after processing, default: disabled\n"
           "\t-fName - set output file name to Name\n"
           "\t-mN    - use N MB memory - [1,4095], default: 256\n"
           "\t-oN    - set model order to N - [2-12,16,32,64,128], default: 12\n"
           "\t-rN    - set method of model restoration at memory insufficiency:\n"
           "\t\t-r0 - restart model from scratch\n"
           "\t\t-r1 - cut off model (default)\n");
    return -1;
  } else {
    v8 = argv[1];
    v9 = toupper(*v8);
    if(v9 == 'E') {
      f_ENC = 1;
    } else {
      if(v9 != 'D') {
        printf("unknown command: %s\n", v8);
        return -1;
      }
      f_ENC = 0;
    }
    v155 = 0;
    v147[0] = 0;
    v10 = 2;
    v11 = argv;
    while(2) {
      v12 = v11[v10];
      v13 = *v12;
      if(v13 == '-' || v13 == '/') {
        switch(toupper(v12[1])) {
        case 'D':
          v155 = 1;
          goto LABEL_39;
        case 'E':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'N':
        case 'P':
        case 'Q':
          v19 = v11;
          goto LABEL_37;
        case 'F':
          v14 = (char *)(v12 + 2);
          if(*v14) {
            v15 = v147;
            do {
              v16 = *v14++;
              *v15++ = v16;
            } while(v16);
          } else {
            GetCurrentDirectoryA(260u, Buffer);
            v53 = strrchr(Buffer, 92);
            if(v53) {
              v54 = v53 + 1;
              if(!v53[1])
                v54 = "PPMmFile";
            } else {
              v54 = "PPMmFile";
            }
            v55 = strrchr(v54, '.');
            if(!v55 || strrchr(v54, '\\') > v55) {
              v34 = !_BitScanForward((unsigned int *)&v56, (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_setzero_si128(), *(__m128i *)((unsigned __int64)v54 & ~0xFuLL))) >> ((unsigned __int8)v54 & 0xF));
              if(v34)
                v56 = movemask_cmpeq_loop((unsigned __int8)v54 & 0xF, (__int64)v54);
              v55 = &v56[(_QWORD)v54];
            }
            v57 = v55 - v54;
            if(v57 > '`' && (v54 - v147 > v57 || v147 - v54 > v57)) {
              memmove(v147, v54, v57);
            } else {
              v61 = 0;
              do {
                v147[v61] = v54[v61];
                ++v61;
              } while(v61 < v57);
            }
            v147[v57] = '.';
            v58 = (char*)"mm";
            v147[v57 + 1] = 'p';
            v59 = &v147[v57 + 2];
            do {
              v60 = *v58;
              *v59++ = *v58++;
            } while(v60);
          }
          v17 = fopen(v147, "rb");
          v18 = v17;
          if(v17) {
            if(!fread_nolock(arch_hdr, 0x10u, 1u, v17) || arch_hdr[0] != 0x8CACAF8F || (arch_hdr[2] & 0x1F) != 9) {
              printf("Can`t open file %s", v147);
              exit(-1);
            }
            fclose_nolock(v18);
          }
          goto LABEL_39;
        case 'L':
          f_LOG = 1;
          goto LABEL_39;
        case 'M':
          mem_val = atoi(v12 + 2);
          if(mem_val >= 4095)
            mem_val = 4095;
          if(mem_val <= 0)
            mem_val = 1;
          goto LABEL_39;
        case 'O':
          order_val = atoi(v12 + 2);
          if(order_val >= 128)
            order_val = 128;
          if(order_val < 2)
            order_val = 2;
          if(order_val > 12)
            order_val = (order_val > 32) + (order_val > 16) + (order_val > 64) + 13;
          goto LABEL_39;
        case 'R':
          reset_type_val = atoi(v12 + 2);
          if(reset_type_val > 0)
            reset_type_val = 1;
          if(reset_type_val < 0)
            reset_type_val = 0;
        LABEL_39:
          if(++v10 >= argc)
            break;
          continue;
        default:
          v19 = v11;
        LABEL_37:
          printf("unknown switch: %s\n", v19[v10]);
          return -1;
        }
      }
      break;
    }
    v21 = v155;
    v22 = v11;
    Block = nullptr;
    if(v10 < argc) {
      p_Block = &Block;
      do {
        FirstFileA = FindFirstFileA(v22[v10], &FindFileData);
        hFindFile = FirstFileA;
        if(FirstFileA == (HANDLE)-1LL)
          goto LABEL_53;
        do {
          if((FindFileData.dwFileAttributes & 0x10) == 0) {
            v25 = (void **)__op_new(328u);
            if(!v25) {
              printf("Out of memory!");
              return -1;
            }
            // Hex-Rays expanded the original 320-byte block-copy into two
            // nested loops that walk pointer arithmetic across five named
            // locals (hTemplateFile/v127/v128/v129/v130) -- only correct
            // if those locals are laid out contiguously. g++ doesn't honor
            // that, so we use the semantic equivalent directly:
            //   v25[1..40] (= bytes 8..327) <- FindFileData[0..319]
            //   v25[0] is overwritten below with the next-list pointer.
            (void)v26; (void)v27;
            memmove((char*)v25 + 8, &FindFileData, 320);
            *v25 = *p_Block;
            *p_Block = v25;
            p_Block = v25;
          }
        } while(FindNextFileA(hFindFile, &FindFileData));
        FirstFileA = hFindFile;
      LABEL_53:
        FindClose(FirstFileA);
        ++v10;
      } while(v10 < argc);
      v28 = (char *)Block;
      if(Block) {
        v29 = sub_140012804();
        LODWORD(v151) = mem_val;
        LODWORD(v152) = reset_type_val;
        Stream = (FILE *)(v29 + 6);
        v30 = 2 * (((_BYTE)order_val + 14) & 0xF);
        LODWORD(v150) = 32 * (((_WORD)mem_val - 1) & 0xFFF);
        v148 = 32 * (reset_type_val & 1);
        v31 = v21;
        while(1) {
          if(!f_ENC) {
            v32 = (__int64)(v28 + 52);
            v51 = fopen(v28 + 52, "rb");
            v52 = v51;
            if(!v51) {
              printf("Can`t open file %s", v28 + 52);
              exit(-1);
            }
            setvbuf(v51, nullptr, 0, 0x10000u);
            if(fread_nolock(arch_hdr, 0x10u, 1u, v52)) {
              if(arch_hdr[0] != 0x8CACAF8F || (arch_hdr[2] & 0x1F) != 9) {
                printf("Can`t open file %s", v142);
                exit(-1);
              }
              fread_nolock(v142, (unsigned __int16)(HIWORD(arch_hdr[2]) & 0xFF80) >> 7, 1u, v52);
              v142[(unsigned __int16)(HIWORD(arch_hdr[2]) & 0xFF80) >> 7] = 0;
              v69 = fopen(v142, "rb");
              if(!v69)
                goto LABEL_148;
              fclose_nolock(v69);
              if(!arch_hdr[4]) {
                printf("%s already exists, overwrite?: <Y>es, <N>o, <A>ll, <Q>uit?", v142);
                while(1) {
                  v90 = getch();
                  v91 = toupper(v90);
                  if(v91 == 65)
                    break;
                  switch(v91) {
                  case '\r':
                  case 'Y':
                    goto LABEL_147;
                  case '\x1B':
                  case 'Q':
                    printf("User break!\n");
                    exit(-1);
                  case 'N':
                    goto LABEL_96;
                  }
                }
                arch_hdr[4] = 1;
              }
            LABEL_147:
              SetFileAttributesA(v142, 0x80u);
              if(!deletefile((wchar_t *)v142)) {
              LABEL_148:
                ::__Buffer = v142;
                v70 = fopen(v142, "wb");
                v71 = v70;
                if(!v70) {
                  printf("Can`t open file %s", v142);
                  exit(-1);
                }
                setvbuf(v70, nullptr, 0, 0x10000u);
                v140 = ((arch_hdr[2] & 0x1FFE0u) >> 5) + 1;
                v141 = ((unsigned __int8)(BYTE2(arch_hdr[2]) & 0x1E) >> 1) + 2;
                v72 = (unsigned __int8)(BYTE2(arch_hdr[2]) & 0x20) >> 5;
                sub_140003370();
                if(!(unsigned int)Alloc_PPMblock(v140, v141, v72)) {
                  printf("Out of memory!");
                  exit(-1);
                }
                arch_hdr[5] = clock();
                arch_hdr[6] = ftell_nolock(v52);
                if((arch_hdr[2] & 0x400000) != 0) {
                  fread_nolock(&v133, 4u, 1u, v52);
                  for(; v133; --v133) {
                    v73 = v71->_cnt - 1;
                    v71->_cnt = v73;
                    if(v73 < 0) {
                      v124 = v52->_cnt - 1;
                      v52->_cnt = v124;
                      if(v124 < 0)
                        v125 = filbuf(v52);
                      else
                        v125 = *(unsigned __int8 *)v52->_ptr++;
                      flsbuf(v125, v71);
                    } else {
                      v74 = v52->_cnt - 1;
                      v52->_cnt = v74;
                      if(v74 < 0)
                        v75 = filbuf(v52);
                      else
                        v75 = *v52->_ptr++;
                      *v71->_ptr++ = v75;
                    }
                  }
                  v76 = clock();
                  v136 = ftell_nolock(v71);
                  v136 += v136 == 0;
                  v137 = ftell_nolock(v52) - arch_hdr[6];
                  arch_hdr[7] = v76;
                  v77 = (v76 - arch_hdr[5]) << 10;
                  v78 = 8LL * v137 / v136;
                  v79 = (1000 * (8LL * v137 - v78 * v136) + (v136 >> 1)) / v136;
                  if((_DWORD)v79 == 1000)
                    ++v78;
                  v138 = v78;
                  if((_DWORD)v79 == 1000)
                    LODWORD(v79) = 0;
                  v135 = v79;
                  v134 = v136 / ((unsigned int)(v77 / 1000 == 0) + v77 / 1000);
                  v80 = sub_1400032F0();
                  v81 = v137;
                  v82 = v80 >> 10;
                  v83 = v80 >> 20;
                  v84 = (10 * (v82 - (v83 << 10)) + 512) >> 10;
                  if(v84 == 10) {
                    ++v83;
                    v84 = 0;
                  }
                  LODWORD(v127) = v83;
                  LODWORD(v128) = v84;
                  LODWORD(v129) = v134;
                  v85 = v136;
                  if(!f_ENC) {
                    v85 = v137;
                    v81 = v136;
                  }
                  sprintf(v130, "%15s:%7d >%7d, %1d.%03d bpb, used:%3d.%1d MB, speed: %d KB/sec.", (const char *)::__Buffer, v85, v81, v138, v135, v127, v128, v129);
                  printf("%-79.79s%c", v130, 10);
                  fflush_nolock(Stream);
                  if(f_LOG) {
                    v86 = fopen("!ratios.lst", "a+t");
                    fprintf(v86, "%s\n", v130);
                    fclose_nolock(v86);
                  }
                } else {
                  sub_14000C310(v71, v52, (__int64(*)(FILE *, FILE *, __int64))PrintStats, 0);
                }
                flag = v52->_flag;
                if((((unsigned __int8)flag | LOBYTE(v71->_flag)) & 0x20) != 0 || (flag & 0x10) != 0) {
                  printf("read/write error for files %s/%s", v142, v142);
                  exit(-1);
                }
                fclose_nolock(v71);
                DosDateTimeToFileTime(HIWORD(arch_hdr[3]), arch_hdr[3], &FileTime);
                FileA = CreateFileA(v142, 0x40000000u, 0, nullptr, 3u, 0, nullptr);
                SetFileTime(FileA, &FileTime, nullptr, &FileTime);
                CloseHandle(FileA);
                SetFileAttributesA(v142, arch_hdr[1]);
                v156 = v28 + 52;
                v157 = v28;
                v158 = v30;
                v155 = v31;
                v89 = Stream;
                v159 = order_val;
                while(fread_nolock(arch_hdr, 0x10u, 1u, v52)) {
                  if(arch_hdr[0] != 0x8CACAF8F || (arch_hdr[2] & 0x1F) != 9) {
                    printf("Can`t open file %s", v144);
                    exit(-1);
                  }
                  fread_nolock(v144, (unsigned __int16)(HIWORD(arch_hdr[2]) & 0xFF80) >> 7, 1u, v52);
                  v144[(unsigned __int16)(HIWORD(arch_hdr[2]) & 0xFF80) >> 7] = 0;
                  v92 = fopen(v144, "rb");
                  if(v92) {
                    fclose_nolock(v92);
                    if(arch_hdr[4]) {
                      SetFileAttributesA(v144, 0x80u);
                      if(deletefile((wchar_t *)v144))
                        break;
                    } else {
                      printf("%s already exists, overwrite?: <Y>es, <N>o, <A>ll, <Q>uit?", v144);
                      while(1) {
                        v120 = getch();
                        v121 = toupper(v120);
                        if(v121 == 'A')
                          break;
                        switch(v121) {
                        case '\r':
                        case 'Y':
                          goto LABEL_229;
                        case '\x1B':
                        case 'Q':
                          printf("User break!\n");
                          exit(-1);
                        case 'N':
                          goto LABEL_220;
                        }
                      }
                      arch_hdr[4] = 1;
                    LABEL_229:
                      SetFileAttributesA(v144, 0x80u);
                      if(deletefile((wchar_t *)v144))
                        break;
                    }
                  }
                  ::__Buffer = v144;
                  v93 = fopen(v144, "wb");
                  v94 = v93;
                  if(!v93) {
                    printf("Can`t open file %s", v144);
                    exit(-1);
                  }
                  setvbuf(v93, nullptr, 0, 0x10000u);
                  v95 = ((arch_hdr[2] & 0x1FFE0u) >> 5) + 1;
                  v96 = ((unsigned __int8)(BYTE2(arch_hdr[2]) & 0x1E) >> 1) + 2;
                  v97 = (unsigned __int8)(BYTE2(arch_hdr[2]) & 0x20) >> 5;
                  sub_140003370();
                  if(!(unsigned int)Alloc_PPMblock(v95, v96, v97)) {
                    printf("Out of memory!");
                    exit(-1);
                  }
                  arch_hdr[5] = clock();
                  arch_hdr[6] = ftell_nolock(v52);
                  if((arch_hdr[2] & 0x400000) != 0) {
                    fread_nolock(&v145, 4u, 1u, v52);
                    for(; v145; --v145) {
                      v98 = v94->_cnt - 1;
                      v94->_cnt = v98;
                      if(v98 < 0) {
                        v122 = v52->_cnt - 1;
                        v52->_cnt = v122;
                        if(v122 < 0)
                          v123 = filbuf(v52);
                        else
                          v123 = *(unsigned __int8 *)v52->_ptr++;
                        flsbuf(v123, v94);
                      } else {
                        v99 = v52->_cnt - 1;
                        v52->_cnt = v99;
                        if(v99 < 0)
                          v100 = filbuf(v52);
                        else
                          v100 = *v52->_ptr++;
                        *v94->_ptr++ = v100;
                      }
                    }
                    v101 = clock();
                    v102 = ftell_nolock(v94);
                    v103 = (v102 == 0) + v102;
                    v104 = ftell_nolock(v52);
                    arch_hdr[7] = v101;
                    v105 = v104 - arch_hdr[6];
                    v106 = 8LL * (unsigned int)(v104 - arch_hdr[6]);
                    v107 = v106 / v103;
                    v108 = (v101 - arch_hdr[5]) << 10;
                    v109 = 0;
                    v110 = (1000 * (v106 - v107 * v103) + (v103 >> 1)) / v103;
                    if(v110 == 1000) {
                      ++v107;
                      v110 = 0;
                    }
                    if(!(v108 / 1000))
                      v109 = 1;
                    v111 = v103 / (v109 + v108 / 1000);
                    v112 = sub_1400032F0();
                    LODWORD(hTemplateFile) = v110;
                    v113 = v112 >> 10;
                    LODWORD(v129) = v111;
                    v114 = v112 >> 20;
                    v115 = (10 * (v113 - (v114 << 10)) + 512) >> 10;
                    if(v115 == 10) {
                      ++v114;
                      v115 = 0;
                    }
                    LODWORD(v127) = v114;
                    v116 = v103;
                    if(!f_ENC) {
                      v116 = v105;
                      v105 = v103;
                    }
                    sprintf(v131, "%15s:%7d >%7d, %1d.%03d bpb, used:%3d.%1d MB, speed: %d KB/sec.", (const char *)::__Buffer, v116, v105, v107, (_DWORD)hTemplateFile, v127, v115, v129);
                    printf("%-79.79s%c", v131, 10);
                    fflush_nolock(v89);
                    if(f_LOG) {
                      v117 = fopen("!ratios.lst", "a+t");
                      fprintf(v117, "%s\n", v131);
                      fclose_nolock(v117);
                    }
                  } else {
                    sub_14000C310(v94, v52, (__int64(*)(FILE *, FILE *, __int64))PrintStats, 0);
                  }
                  v118 = v52->_flag;
                  if((((unsigned __int8)v118 | LOBYTE(v94->_flag)) & 0x20) != 0 || (v118 & 0x10) != 0) {
                    printf("read/write error for files %s/%s", v144, v144);
                    exit(-1);
                  }
                  fclose_nolock(v94);
                  DosDateTimeToFileTime(HIWORD(arch_hdr[3]), arch_hdr[3], &LastWriteTime);
                  v119 = CreateFileA(v144, 0x40000000u, 0, nullptr, 3u, 0, nullptr);
                  SetFileTime(v119, &LastWriteTime, nullptr, &LastWriteTime);
                  CloseHandle(v119);
                  SetFileAttributesA(v144, arch_hdr[1]);
                }
              LABEL_220:
                v32 = (__int64)v156;
                v28 = v157;
                v30 = v158;
                order_val = v159;
                Stream = v89;
                v31 = v155;
              }
            }
          LABEL_96:
            fclose_nolock(v52);
            goto LABEL_97;
          }
          strcpy(FileName, v147);
          v32 = (__int64)(v28 + 52);
          if(FileName[0])
            goto LABEL_81;
          v33 = strrchr(v28 + 52, '.');
          if(!v33 || strrchr(v28 + 52, '\\') > v33) {
            v34 = !_BitScanForward((unsigned int *)&v35, (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_setzero_si128(), *(__m128i *)(v32 & 0xFFFFFFFFFFFFFFF0uLL))) >> (v32 & 0xF));
            if(v34)
              v35 = movemask_cmpeq_loop(v32 & 0xF, v32);
            v33 = &v28[(_QWORD)v35 + 52];
          }
          v36 = (signed __int64)&v33[-v32];
          if(v36 > 96 && (v32 - (__int64)FileName > v36 || (__int64)&FileName[-v32] > v36)) {
            memmove(FileName, v28 + 52, v36);
          } else {
            v62 = 0;
            do {
              FileName[v62] = *(_BYTE *)(v62 + v32);
              ++v62;
            } while(v62 < v36);
          }
          FileName[v36] = 46;
          v37 = (char*)"mm";
          FileName[v36 + 1] = 112;
          v38 = &FileName[v36 + 2];
          do {
            v39 = *v37;
            *v38++ = *v37++;
          } while(v39);
          v40 = fopen(FileName, "rb");
          if(!v40)
            goto LABEL_81;
          fclose_nolock(v40);
          if(!arch_hdr[4])
            break;
          SetFileAttributesA(FileName, 0x80u);
          if(!deletefile((wchar_t *)FileName))
            goto LABEL_81;
        LABEL_97:
          if(v31)
            deletefile((wchar_t *)v32);
          Block = *(void **)v28;
          j_free(v28);
          v28 = (char *)Block;
          if(!Block)
            goto LABEL_100;
        }
        printf("%s already exists, overwrite?: <Y>es, <N>o, <A>ll, <Q>uit?", FileName);
        while(1) {
          v41 = getch();
          v42 = toupper(v41);
          if(v42 == 'A')
            break;
          switch(v42) {
          case '\r':
          case 'Y':
            goto LABEL_122;
          case '\x1B':
          case 'Q':
            printf("User break!\n");
            exit(-1);
          case 'N':
            goto LABEL_97;
          }
        }
        arch_hdr[4] = 1;
      LABEL_122:
        SetFileAttributesA(FileName, 0x80u);
        if(deletefile((wchar_t *)FileName))
          goto LABEL_97;
      LABEL_81:
        v43 = fopen(v28 + 52, "rb");
        v44 = v43;
        if(!v43) {
          printf("Can`t open file %s", v28 + 52);
          exit(-1);
        }
        setvbuf(v43, nullptr, 0, 0x10000u);
        v45 = fopen(FileName, "a+b");
        v46 = v45;
        if(!v45) {
          printf("Can`t open file %s", FileName);
          exit(-1);
        }
        setvbuf(v45, nullptr, 0, 0x10000u);
        v47 = strrchr(v28 + 52, 92);
        arch_hdr[1] = *((_DWORD *)v28 + 2);
        v48 = v47 + 1;
        if(!v47)
          v48 = v28 + 52;
        ::__Buffer = v48;
        FileTimeToDosDateTime((const FILETIME *)(v28 + 28), (LPWORD)&arch_hdr[3] + 1, (LPWORD)&arch_hdr[3]);
        LOBYTE(arch_hdr[2]) = arch_hdr[2] & 0xE0 | 9;
        arch_hdr[0] = -1934839921;
        BYTE2(arch_hdr[2]) = v30 | BYTE2(arch_hdr[2]) & 0xE1;
        arch_hdr[2] = v150 | arch_hdr[2] & 0xFFFE001F;
        BYTE2(arch_hdr[2]) = v148 & 0xBF | BYTE2(arch_hdr[2]) & 0x9F;
        v34 = !_BitScanForward((unsigned int *)&v49, (unsigned int)_mm_movemask_epi8(_mm_cmpeq_epi8(_mm_setzero_si128(), *(__m128i *)((unsigned __int64)::__Buffer & ~0xFuLL))) >> ((unsigned __int8)::__Buffer & 0xF));
        if(v34)
          LOWORD(v49) = (unsigned __int16)movemask_cmpeq_loop((unsigned __int8)::__Buffer & 0xF, (__int64)::__Buffer);
        HIWORD(arch_hdr[2]) = ((_WORD)v49 << 7) | BYTE2(arch_hdr[2]) & 0x7F;
        fwrite_nolock(arch_hdr, 0x10u, 1u, v46);
        fwrite_nolock(::__Buffer, (unsigned __int16)(HIWORD(arch_hdr[2]) & 0xFF80) >> 7, 1u, v46);
        sub_140003370();
        if(!(unsigned int)Alloc_PPMblock(v151, order_val, (int)v152)) {
          printf("Out of memory!");
          exit(-1);
        }
        arch_hdr[5] = clock();
        arch_hdr[6] = ftell_nolock(v46);
        sub_140003530(v46, v44, (__int64(*)(FILE *, FILE *, __int64))PrintStats, 0);
        if(ftell_nolock(v44) >= 0) {
          v50 = ftell_nolock(v46);
          if((unsigned int)(v50 - arch_hdr[6]) > (unsigned __int64)(ftell_nolock(v44) + 4LL)) {
            v146 = ftell_nolock(v44);
            fseek_nolock(v44, 0, 0);
            fflush_nolock(v46);
            fseek_nolock(v46, arch_hdr[6] - ((unsigned __int16)(HIWORD(arch_hdr[2]) & 0xFF80) >> 7) - 16, 0);
            v63 = fileno(v46);
            chsize(v63, arch_hdr[6] - ((unsigned __int16)(HIWORD(arch_hdr[2]) & 0xFF80) >> 7) - 16);
            BYTE2(arch_hdr[2]) |= 0x40u;
            fwrite_nolock(arch_hdr, 0x10u, 1u, v46);
            fwrite_nolock(::__Buffer, (unsigned __int16)(HIWORD(arch_hdr[2]) & 0xFF80) >> 7, 1u, v46);
            fwrite_nolock(&v146, 4u, 1u, v46);
            for(; v146; --v146) {
              v64 = v46->_cnt - 1;
              v46->_cnt = v64;
              if(v64 < 0) {
                v67 = v44->_cnt - 1;
                v44->_cnt = v67;
                if(v67 < 0)
                  v68 = filbuf(v44);
                else
                  v68 = *(unsigned __int8 *)v44->_ptr++;
                flsbuf(v68, v46);
              } else {
                v65 = v44->_cnt - 1;
                v44->_cnt = v65;
                if(v65 < 0)
                  v66 = filbuf(v44);
                else
                  v66 = *v44->_ptr++;
                *v46->_ptr++ = v66;
              }
            }
          }
        }
        if(((LOBYTE(v44->_flag) | LOBYTE(v46->_flag)) & 0x20) != 0) {
          printf("read/write error for files %s/%s", v28 + 52, FileName);
          exit(-1);
        }
        fclose_nolock(v44);
        fclose_nolock(v46);
        goto LABEL_97;
      }
    }
  LABEL_100:
    sub_140003370();
    return 0;
  }
}

// ---- Cleanup: unmap macros so nothing leaks into following code ------
#undef arch_hdr
#undef f_ENC
#undef f_LOG
#undef printf
#undef sprintf
#undef fprintf
#undef toupper
#undef atoi
#undef fopen
#undef fread_nolock
#undef fwrite_nolock
#undef fclose_nolock
#undef ftell_nolock
#undef fseek_nolock
#undef fflush_nolock
#undef setvbuf
#undef flsbuf
#undef filbuf
#undef fileno
#undef chsize
#undef strrchr
#undef memmove
#undef clock
#undef exit
#undef getch
#undef j_free
#undef deletefile
#undef movemask_cmpeq_loop
#undef _intel_new_proc_init
#undef PrintStats
#undef Alloc_PPMblock
#undef sub_140003530
#undef sub_14000C310
#undef sub_140003370
#undef sub_1400032F0
#undef sub_140012804
#undef _BitScanForward
#undef FILE
