// =====================================================================
// sub_1400037A0 @ 0x1400037A0
// Auto-extracted scaffold. REVIEW: see TODO comments below.
// =====================================================================

#define FILE FILE1

#define _BitScanForward(idx_ptr, mask_val) \
  ((mask_val) ? ((*(idx_ptr) = __builtin_ctz((unsigned int)(mask_val))), 1u) : 0u)

// ---- TODO: unresolved identifiers (locals, intrinsics, or typos) ----
//   call:  abs32

// ---- WARNING: patterns that need manual rewrite ----
//   `(char*)&<local> + v<N>` -- Hex-Rays expanded a memcpy into pointer arithmetic across adjacent locals. g++ does NOT preserve that layout. Rewrite as memmove against the conceptual source struct.

// ---- Data references ------------------------------------------------
#ifndef __PE_DECL___algn_141136BC4
#define __PE_DECL___algn_141136BC4
typedef _BYTE t_algn_141136BC4[1084];
static t_algn_141136BC4& __algn_141136BC4 = *(t_algn_141136BC4*)0x141136BC4;
#endif
#define algn_141136BC4 __algn_141136BC4
#ifndef __PE_DECL___byte_140022930
#define __PE_DECL___byte_140022930
typedef char t_byte_140022930[1];
static t_byte_140022930& __byte_140022930 = *(t_byte_140022930*)0x140022930;
#endif
#define byte_140022930 __byte_140022930
#ifndef __PE_DECL___byte_140022931
#define __PE_DECL___byte_140022931
typedef char t_byte_140022931[31];
static t_byte_140022931& __byte_140022931 = *(t_byte_140022931*)0x140022931;
#endif
#define byte_140022931 __byte_140022931
#ifndef __PE_DECL___byte_140029000
#define __PE_DECL___byte_140029000
typedef char t_byte_140029000[1];
static t_byte_140029000& __byte_140029000 = *(t_byte_140029000*)0x140029000;
#endif
#define byte_140029000 __byte_140029000
#ifndef __PE_DECL___byte_140029240
#define __PE_DECL___byte_140029240
typedef char t_byte_140029240[126];
static t_byte_140029240& __byte_140029240 = *(t_byte_140029240*)0x140029240;
#endif
#define byte_140029240 __byte_140029240
#ifndef __PE_DECL___byte_1400292BE
#define __PE_DECL___byte_1400292BE
typedef char t_byte_1400292BE[1];
static t_byte_1400292BE& __byte_1400292BE = *(t_byte_1400292BE*)0x1400292BE;
#endif
#define byte_1400292BE __byte_1400292BE
#ifndef __PE_DECL___byte_1400293C0
#define __PE_DECL___byte_1400293C0
typedef char t_byte_1400293C0[128];
static t_byte_1400293C0& __byte_1400293C0 = *(t_byte_1400293C0*)0x1400293C0;
#endif
#define byte_1400293C0 __byte_1400293C0
#ifndef __PE_DECL___byte_140029440
#define __PE_DECL___byte_140029440
typedef char t_byte_140029440[1];
static t_byte_140029440& __byte_140029440 = *(t_byte_140029440*)0x140029440;
#endif
#define byte_140029440 __byte_140029440
#ifndef __PE_DECL___byte_14002A158
#define __PE_DECL___byte_14002A158
typedef char t_byte_14002A158[262144];
static t_byte_14002A158& __byte_14002A158 = *(t_byte_14002A158*)0x14002A158;
#endif
#define byte_14002A158 __byte_14002A158
#ifndef __PE_DECL___byte_1400DA158
#define __PE_DECL___byte_1400DA158
typedef char t_byte_1400DA158[65536];
static t_byte_1400DA158& __byte_1400DA158 = *(t_byte_1400DA158*)0x1400DA158;
#endif
#define byte_1400DA158 __byte_1400DA158
#ifndef __PE_DECL___byte_1400EA158
#define __PE_DECL___byte_1400EA158
typedef char t_byte_1400EA158[131072];
static t_byte_1400EA158& __byte_1400EA158 = *(t_byte_1400EA158*)0x1400EA158;
#endif
#define byte_1400EA158 __byte_1400EA158
#ifndef __PE_DECL___byte_14014AD5C
#define __PE_DECL___byte_14014AD5C
static char& __byte_14014AD5C = *(char*)0x14014AD5C;
#endif
#define byte_14014AD5C __byte_14014AD5C
#ifndef __PE_DECL___byte_141108A20
#define __PE_DECL___byte_141108A20
typedef char t_byte_141108A20[256];
static t_byte_141108A20& __byte_141108A20 = *(t_byte_141108A20*)0x141108A20;
#endif
#define byte_141108A20 __byte_141108A20
#ifndef __PE_DECL___dword_140029540
#define __PE_DECL___dword_140029540
typedef int t_dword_140029540[256];
static t_dword_140029540& __dword_140029540 = *(t_dword_140029540*)0x140029540;
#endif
#define dword_140029540 __dword_140029540
#ifndef __PE_DECL___dword_14010A158
#define __PE_DECL___dword_14010A158
typedef int t_dword_14010A158[256];
static t_dword_14010A158& __dword_14010A158 = *(t_dword_14010A158*)0x14010A158;
#endif
#define dword_14010A158 __dword_14010A158
#ifndef __PE_DECL___dword_14010A558
#define __PE_DECL___dword_14010A558
typedef int t_dword_14010A558[256];
static t_dword_14010A558& __dword_14010A558 = *(t_dword_14010A558*)0x14010A558;
#endif
#define dword_14010A558 __dword_14010A558
#ifndef __PE_DECL___dword_14010A958
#define __PE_DECL___dword_14010A958
typedef int t_dword_14010A958[256];
static t_dword_14010A958& __dword_14010A958 = *(t_dword_14010A958*)0x14010A958;
#endif
#define dword_14010A958 __dword_14010A958
#ifndef __PE_DECL___dword_14014AD68
#define __PE_DECL___dword_14014AD68
static int& __dword_14014AD68 = *(int*)0x14014AD68;
#endif
#define dword_14014AD68 __dword_14014AD68
#ifndef __PE_DECL___dword_14014AD6C
#define __PE_DECL___dword_14014AD6C
static int& __dword_14014AD6C = *(int*)0x14014AD6C;
#endif
#define dword_14014AD6C __dword_14014AD6C
#ifndef __PE_DECL___dword_14014AD70
#define __PE_DECL___dword_14014AD70
static int& __dword_14014AD70 = *(int*)0x14014AD70;
#endif
#define dword_14014AD70 __dword_14014AD70
#ifndef __PE_DECL___dword_14014AD7C
#define __PE_DECL___dword_14014AD7C
static int& __dword_14014AD7C = *(int*)0x14014AD7C;
#endif
#define dword_14014AD7C __dword_14014AD7C
#ifndef __PE_DECL___dword_14014AD80
#define __PE_DECL___dword_14014AD80
static int& __dword_14014AD80 = *(int*)0x14014AD80;
#endif
#define dword_14014AD80 __dword_14014AD80
#ifndef __PE_DECL___dword_14014AD84
#define __PE_DECL___dword_14014AD84
static int& __dword_14014AD84 = *(int*)0x14014AD84;
#endif
#define dword_14014AD84 __dword_14014AD84
#ifndef __PE_DECL___dword_14014AD88
#define __PE_DECL___dword_14014AD88
static int& __dword_14014AD88 = *(int*)0x14014AD88;
#endif
#define dword_14014AD88 __dword_14014AD88
#ifndef __PE_DECL___dword_14014AD8C
#define __PE_DECL___dword_14014AD8C
static int& __dword_14014AD8C = *(int*)0x14014AD8C;
#endif
#define dword_14014AD8C __dword_14014AD8C
#ifndef __PE_DECL___dword_14014AD90
#define __PE_DECL___dword_14014AD90
static int& __dword_14014AD90 = *(int*)0x14014AD90;
#endif
#define dword_14014AD90 __dword_14014AD90
#ifndef __PE_DECL___dword_14014AD94
#define __PE_DECL___dword_14014AD94
static int& __dword_14014AD94 = *(int*)0x14014AD94;
#endif
#define dword_14014AD94 __dword_14014AD94
#ifndef __PE_DECL___dword_14014AD98
#define __PE_DECL___dword_14014AD98
static int& __dword_14014AD98 = *(int*)0x14014AD98;
#endif
#define dword_14014AD98 __dword_14014AD98
#ifndef __PE_DECL___dword_14014AD9C
#define __PE_DECL___dword_14014AD9C
static int& __dword_14014AD9C = *(int*)0x14014AD9C;
#endif
#define dword_14014AD9C __dword_14014AD9C
#ifndef __PE_DECL___dword_14014ADA0
#define __PE_DECL___dword_14014ADA0
static int& __dword_14014ADA0 = *(int*)0x14014ADA0;
#endif
#define dword_14014ADA0 __dword_14014ADA0
#ifndef __PE_DECL___dword_14014ADA4
#define __PE_DECL___dword_14014ADA4
static int& __dword_14014ADA4 = *(int*)0x14014ADA4;
#endif
#define dword_14014ADA4 __dword_14014ADA4
#ifndef __PE_DECL___dword_14014ADA8
#define __PE_DECL___dword_14014ADA8
static int& __dword_14014ADA8 = *(int*)0x14014ADA8;
#endif
#define dword_14014ADA8 __dword_14014ADA8
#ifndef __PE_DECL___dword_14014ADAC
#define __PE_DECL___dword_14014ADAC
static int& __dword_14014ADAC = *(int*)0x14014ADAC;
#endif
#define dword_14014ADAC __dword_14014ADAC
#ifndef __PE_DECL___dword_14014ADB0
#define __PE_DECL___dword_14014ADB0
static int& __dword_14014ADB0 = *(int*)0x14014ADB0;
#endif
#define dword_14014ADB0 __dword_14014ADB0
#ifndef __PE_DECL___dword_14014ADB4
#define __PE_DECL___dword_14014ADB4
static int& __dword_14014ADB4 = *(int*)0x14014ADB4;
#endif
#define dword_14014ADB4 __dword_14014ADB4
#ifndef __PE_DECL___dword_14014ADB8
#define __PE_DECL___dword_14014ADB8
static int& __dword_14014ADB8 = *(int*)0x14014ADB8;
#endif
#define dword_14014ADB8 __dword_14014ADB8
#ifndef __PE_DECL___dword_14014ADCC
#define __PE_DECL___dword_14014ADCC
static int& __dword_14014ADCC = *(int*)0x14014ADCC;
#endif
#define dword_14014ADCC __dword_14014ADCC
#ifndef __PE_DECL___dword_14014ADD0
#define __PE_DECL___dword_14014ADD0
static int& __dword_14014ADD0 = *(int*)0x14014ADD0;
#endif
#define dword_14014ADD0 __dword_14014ADD0
#ifndef __PE_DECL___dword_14014ADDC
#define __PE_DECL___dword_14014ADDC
static int& __dword_14014ADDC = *(int*)0x14014ADDC;
#endif
#define dword_14014ADDC __dword_14014ADDC
#ifndef __PE_DECL___dword_14014ADE8
#define __PE_DECL___dword_14014ADE8
static int& __dword_14014ADE8 = *(int*)0x14014ADE8;
#endif
#define dword_14014ADE8 __dword_14014ADE8
#ifndef __PE_DECL___dword_14014ADEC
#define __PE_DECL___dword_14014ADEC
static int& __dword_14014ADEC = *(int*)0x14014ADEC;
#endif
#define dword_14014ADEC __dword_14014ADEC
#ifndef __PE_DECL___dword_14014ADF0
#define __PE_DECL___dword_14014ADF0
static int& __dword_14014ADF0 = *(int*)0x14014ADF0;
#endif
#define dword_14014ADF0 __dword_14014ADF0
#ifndef __PE_DECL___dword_14014ADF8
#define __PE_DECL___dword_14014ADF8
static int& __dword_14014ADF8 = *(int*)0x14014ADF8;
#endif
#define dword_14014ADF8 __dword_14014ADF8
#ifndef __PE_DECL___dword_1401CF1FC
#define __PE_DECL___dword_1401CF1FC
typedef int t_dword_1401CF1FC[65536];
static t_dword_1401CF1FC& __dword_1401CF1FC = *(t_dword_1401CF1FC*)0x1401CF1FC;
#endif
#define dword_1401CF1FC __dword_1401CF1FC
#ifndef __PE_DECL___dword_14020F1FC
#define __PE_DECL___dword_14020F1FC
typedef int t_dword_14020F1FC[16384];
static t_dword_14020F1FC& __dword_14020F1FC = *(t_dword_14020F1FC*)0x14020F1FC;
#endif
#define dword_14020F1FC __dword_14020F1FC
#ifndef __PE_DECL___dword_14021F1FC
#define __PE_DECL___dword_14021F1FC
typedef int t_dword_14021F1FC[65536];
static t_dword_14021F1FC& __dword_14021F1FC = *(t_dword_14021F1FC*)0x14021F1FC;
#endif
#define dword_14021F1FC __dword_14021F1FC
#ifndef __PE_DECL___dword_14025F1FC
#define __PE_DECL___dword_14025F1FC
static int& __dword_14025F1FC = *(int*)0x14025F1FC;
#endif
#define dword_14025F1FC __dword_14025F1FC
#ifndef __PE_DECL___dword_14025F200
#define __PE_DECL___dword_14025F200
static int& __dword_14025F200 = *(int*)0x14025F200;
#endif
#define dword_14025F200 __dword_14025F200
#ifndef __PE_DECL___dword_14025F204
#define __PE_DECL___dword_14025F204
static int& __dword_14025F204 = *(int*)0x14025F204;
#endif
#define dword_14025F204 __dword_14025F204
#ifndef __PE_DECL___dword_14025F208
#define __PE_DECL___dword_14025F208
static int& __dword_14025F208 = *(int*)0x14025F208;
#endif
#define dword_14025F208 __dword_14025F208
#ifndef __PE_DECL___dword_14025F20C
#define __PE_DECL___dword_14025F20C
static int& __dword_14025F20C = *(int*)0x14025F20C;
#endif
#define dword_14025F20C __dword_14025F20C
#ifndef __PE_DECL___dword_14025FA20
#define __PE_DECL___dword_14025FA20
typedef int t_dword_14025FA20[1];
static t_dword_14025FA20& __dword_14025FA20 = *(t_dword_14025FA20*)0x14025FA20;
#endif
#define dword_14025FA20 __dword_14025FA20
#ifndef __PE_DECL___dword_14045FB20
#define __PE_DECL___dword_14045FB20
typedef int t_dword_14045FB20[1];
static t_dword_14045FB20& __dword_14045FB20 = *(t_dword_14045FB20*)0x14045FB20;
#endif
#define dword_14045FB20 __dword_14045FB20
#ifndef __PE_DECL___dword_1405DFC20
#define __PE_DECL___dword_1405DFC20
typedef int t_dword_1405DFC20[1];
static t_dword_1405DFC20& __dword_1405DFC20 = *(t_dword_1405DFC20*)0x1405DFC20;
#endif
#define dword_1405DFC20 __dword_1405DFC20
#ifndef __PE_DECL___dword_14079FD20
#define __PE_DECL___dword_14079FD20
typedef int t_dword_14079FD20[640];
static t_dword_14079FD20& __dword_14079FD20 = *(t_dword_14079FD20*)0x14079FD20;
#endif
#define dword_14079FD20 __dword_14079FD20
#ifndef __PE_DECL___dword_1407A0720
#define __PE_DECL___dword_1407A0720
typedef int t_dword_1407A0720[1];
static t_dword_1407A0720& __dword_1407A0720 = *(t_dword_1407A0720*)0x1407A0720;
#endif
#define dword_1407A0720 __dword_1407A0720
#ifndef __PE_DECL___dword_140FA0820
#define __PE_DECL___dword_140FA0820
typedef int t_dword_140FA0820[1];
static t_dword_140FA0820& __dword_140FA0820 = *(t_dword_140FA0820*)0x140FA0820;
#endif
#define dword_140FA0820 __dword_140FA0820
#ifndef __PE_DECL___dword_140FA0824
#define __PE_DECL___dword_140FA0824
typedef int t_dword_140FA0824[196671];
static t_dword_140FA0824& __dword_140FA0824 = *(t_dword_140FA0824*)0x140FA0824;
#endif
#define dword_140FA0824 __dword_140FA0824
#ifndef __PE_DECL___dword_141060920
#define __PE_DECL___dword_141060920
typedef int t_dword_141060920[1];
static t_dword_141060920& __dword_141060920 = *(t_dword_141060920*)0x141060920;
#endif
#define dword_141060920 __dword_141060920
#ifndef __PE_DECL___dword_141060924
#define __PE_DECL___dword_141060924
typedef int t_dword_141060924[172095];
static t_dword_141060924& __dword_141060924 = *(t_dword_141060924*)0x141060924;
#endif
#define dword_141060924 __dword_141060924
#ifndef __PE_DECL___dword_141108B20
#define __PE_DECL___dword_141108B20
typedef int t_dword_141108B20[1];
static t_dword_141108B20& __dword_141108B20 = *(t_dword_141108B20*)0x141108B20;
#endif
#define dword_141108B20 __dword_141108B20
#ifndef __PE_DECL___dword_141128C20
#define __PE_DECL___dword_141128C20
typedef int t_dword_141128C20[1];
static t_dword_141128C20& __dword_141128C20 = *(t_dword_141128C20*)0x141128C20;
#endif
#define dword_141128C20 __dword_141128C20
#ifndef __PE_DECL___dword_141130D20
#define __PE_DECL___dword_141130D20
typedef int t_dword_141130D20[1];
static t_dword_141130D20& __dword_141130D20 = *(t_dword_141130D20*)0x141130D20;
#endif
#define dword_141130D20 __dword_141130D20
#ifndef __PE_DECL___dword_141133660
#define __PE_DECL___dword_141133660
static int& __dword_141133660 = *(int*)0x141133660;
#endif
#define dword_141133660 __dword_141133660
#ifndef __PE_DECL___dword_141133664
#define __PE_DECL___dword_141133664
static int& __dword_141133664 = *(int*)0x141133664;
#endif
#define dword_141133664 __dword_141133664
#ifndef __PE_DECL___dword_141133668
#define __PE_DECL___dword_141133668
static int& __dword_141133668 = *(int*)0x141133668;
#endif
#define dword_141133668 __dword_141133668
#ifndef __PE_DECL___dword_14113366C
#define __PE_DECL___dword_14113366C
static int& __dword_14113366C = *(int*)0x14113366C;
#endif
#define dword_14113366C __dword_14113366C
#ifndef __PE_DECL___dword_141133670
#define __PE_DECL___dword_141133670
static int& __dword_141133670 = *(int*)0x141133670;
#endif
#define dword_141133670 __dword_141133670
#ifndef __PE_DECL___dword_141133674
#define __PE_DECL___dword_141133674
static int& __dword_141133674 = *(int*)0x141133674;
#endif
#define dword_141133674 __dword_141133674
#ifndef __PE_DECL___dword_141133678
#define __PE_DECL___dword_141133678
static int& __dword_141133678 = *(int*)0x141133678;
#endif
#define dword_141133678 __dword_141133678
#ifndef __PE_DECL___dword_14113367C
#define __PE_DECL___dword_14113367C
static int& __dword_14113367C = *(int*)0x14113367C;
#endif
#define dword_14113367C __dword_14113367C
#ifndef __PE_DECL___dword_141133680
#define __PE_DECL___dword_141133680
static int& __dword_141133680 = *(int*)0x141133680;
#endif
#define dword_141133680 __dword_141133680
#ifndef __PE_DECL___dword_141133684
#define __PE_DECL___dword_141133684
static int& __dword_141133684 = *(int*)0x141133684;
#endif
#define dword_141133684 __dword_141133684
#ifndef __PE_DECL___dword_141133688
#define __PE_DECL___dword_141133688
static int& __dword_141133688 = *(int*)0x141133688;
#endif
#define dword_141133688 __dword_141133688
#ifndef __PE_DECL___dword_14113368C
#define __PE_DECL___dword_14113368C
static int& __dword_14113368C = *(int*)0x14113368C;
#endif
#define dword_14113368C __dword_14113368C
#ifndef __PE_DECL___dword_141133690
#define __PE_DECL___dword_141133690
static int& __dword_141133690 = *(int*)0x141133690;
#endif
#define dword_141133690 __dword_141133690
#ifndef __PE_DECL___dword_141133694
#define __PE_DECL___dword_141133694
static int& __dword_141133694 = *(int*)0x141133694;
#endif
#define dword_141133694 __dword_141133694
#ifndef __PE_DECL___dword_141133698
#define __PE_DECL___dword_141133698
static int& __dword_141133698 = *(int*)0x141133698;
#endif
#define dword_141133698 __dword_141133698
#ifndef __PE_DECL___dword_14113369C
#define __PE_DECL___dword_14113369C
static int& __dword_14113369C = *(int*)0x14113369C;
#endif
#define dword_14113369C __dword_14113369C
#ifndef __PE_DECL___dword_1411336A0
#define __PE_DECL___dword_1411336A0
static int& __dword_1411336A0 = *(int*)0x1411336A0;
#endif
#define dword_1411336A0 __dword_1411336A0
#ifndef __PE_DECL___dword_1411336A4
#define __PE_DECL___dword_1411336A4
static int& __dword_1411336A4 = *(int*)0x1411336A4;
#endif
#define dword_1411336A4 __dword_1411336A4
#ifndef __PE_DECL___dword_1411336A8
#define __PE_DECL___dword_1411336A8
static int& __dword_1411336A8 = *(int*)0x1411336A8;
#endif
#define dword_1411336A8 __dword_1411336A8
#ifndef __PE_DECL___dword_1411336AC
#define __PE_DECL___dword_1411336AC
static int& __dword_1411336AC = *(int*)0x1411336AC;
#endif
#define dword_1411336AC __dword_1411336AC
#ifndef __PE_DECL___dword_1411336B0
#define __PE_DECL___dword_1411336B0
static int& __dword_1411336B0 = *(int*)0x1411336B0;
#endif
#define dword_1411336B0 __dword_1411336B0
#ifndef __PE_DECL___dword_1411336B4
#define __PE_DECL___dword_1411336B4
static int& __dword_1411336B4 = *(int*)0x1411336B4;
#endif
#define dword_1411336B4 __dword_1411336B4
#ifndef __PE_DECL___dword_1411336B8
#define __PE_DECL___dword_1411336B8
static int& __dword_1411336B8 = *(int*)0x1411336B8;
#endif
#define dword_1411336B8 __dword_1411336B8
#ifndef __PE_DECL___dword_1411336BC
#define __PE_DECL___dword_1411336BC
static int& __dword_1411336BC = *(int*)0x1411336BC;
#endif
#define dword_1411336BC __dword_1411336BC
#ifndef __PE_DECL___dword_1411336C0
#define __PE_DECL___dword_1411336C0
static int& __dword_1411336C0 = *(int*)0x1411336C0;
#endif
#define dword_1411336C0 __dword_1411336C0
#ifndef __PE_DECL___dword_1411336C4
#define __PE_DECL___dword_1411336C4
static int& __dword_1411336C4 = *(int*)0x1411336C4;
#endif
#define dword_1411336C4 __dword_1411336C4
#ifndef __PE_DECL___dword_1411336C8
#define __PE_DECL___dword_1411336C8
static int& __dword_1411336C8 = *(int*)0x1411336C8;
#endif
#define dword_1411336C8 __dword_1411336C8
#ifndef __PE_DECL___dword_1411336CC
#define __PE_DECL___dword_1411336CC
static int& __dword_1411336CC = *(int*)0x1411336CC;
#endif
#define dword_1411336CC __dword_1411336CC
#ifndef __PE_DECL___dword_1411336D0
#define __PE_DECL___dword_1411336D0
static int& __dword_1411336D0 = *(int*)0x1411336D0;
#endif
#define dword_1411336D0 __dword_1411336D0
#ifndef __PE_DECL___dword_1411336D4
#define __PE_DECL___dword_1411336D4
static int& __dword_1411336D4 = *(int*)0x1411336D4;
#endif
#define dword_1411336D4 __dword_1411336D4
#ifndef __PE_DECL___dword_1411336D8
#define __PE_DECL___dword_1411336D8
static int& __dword_1411336D8 = *(int*)0x1411336D8;
#endif
#define dword_1411336D8 __dword_1411336D8
#ifndef __PE_DECL___dword_1411336DC
#define __PE_DECL___dword_1411336DC
static int& __dword_1411336DC = *(int*)0x1411336DC;
#endif
#define dword_1411336DC __dword_1411336DC
#ifndef __PE_DECL___dword_1411336E0
#define __PE_DECL___dword_1411336E0
static int& __dword_1411336E0 = *(int*)0x1411336E0;
#endif
#define dword_1411336E0 __dword_1411336E0
#ifndef __PE_DECL___dword_1411336E4
#define __PE_DECL___dword_1411336E4
static int& __dword_1411336E4 = *(int*)0x1411336E4;
#endif
#define dword_1411336E4 __dword_1411336E4
#ifndef __PE_DECL___dword_1411336E8
#define __PE_DECL___dword_1411336E8
static int& __dword_1411336E8 = *(int*)0x1411336E8;
#endif
#define dword_1411336E8 __dword_1411336E8
#ifndef __PE_DECL___dword_1411336EC
#define __PE_DECL___dword_1411336EC
static int& __dword_1411336EC = *(int*)0x1411336EC;
#endif
#define dword_1411336EC __dword_1411336EC
#ifndef __PE_DECL___dword_1411336F0
#define __PE_DECL___dword_1411336F0
static int& __dword_1411336F0 = *(int*)0x1411336F0;
#endif
#define dword_1411336F0 __dword_1411336F0
#ifndef __PE_DECL___dword_1411336F4
#define __PE_DECL___dword_1411336F4
static int& __dword_1411336F4 = *(int*)0x1411336F4;
#endif
#define dword_1411336F4 __dword_1411336F4
#ifndef __PE_DECL___dword_141133700
#define __PE_DECL___dword_141133700
static int& __dword_141133700 = *(int*)0x141133700;
#endif
#define dword_141133700 __dword_141133700
#ifndef __PE_DECL___dword_141133704
#define __PE_DECL___dword_141133704
static int& __dword_141133704 = *(int*)0x141133704;
#endif
#define dword_141133704 __dword_141133704
#ifndef __PE_DECL___dword_141133708
#define __PE_DECL___dword_141133708
static int& __dword_141133708 = *(int*)0x141133708;
#endif
#define dword_141133708 __dword_141133708
#ifndef __PE_DECL___dword_14113370C
#define __PE_DECL___dword_14113370C
static int& __dword_14113370C = *(int*)0x14113370C;
#endif
#define dword_14113370C __dword_14113370C
#ifndef __PE_DECL___qword_14002A150
#define __PE_DECL___qword_14002A150
static __int64& __qword_14002A150 = *(__int64*)0x14002A150;
#endif
#define qword_14002A150 __qword_14002A150
#ifndef __PE_DECL___qword_14025F220
#define __PE_DECL___qword_14025F220
typedef __int64 t_qword_14025F220[1];
static t_qword_14025F220& __qword_14025F220 = *(t_qword_14025F220*)0x14025F220;
#endif
#define qword_14025F220 __qword_14025F220
#ifndef __PE_DECL___qword_14025F228
#define __PE_DECL___qword_14025F228
static __int64& __qword_14025F228 = *(__int64*)0x14025F228;
#endif
#define qword_14025F228 __qword_14025F228
#ifndef __PE_DECL___qword_141133560
#define __PE_DECL___qword_141133560
static __int64& __qword_141133560 = *(__int64*)0x141133560;
#endif
#define qword_141133560 __qword_141133560
#ifndef __PE_DECL___qword_141133580
#define __PE_DECL___qword_141133580
static __int64& __qword_141133580 = *(__int64*)0x141133580;
#endif
#define qword_141133580 __qword_141133580
#ifndef __PE_DECL___qword_141133588
#define __PE_DECL___qword_141133588
static __int64& __qword_141133588 = *(__int64*)0x141133588;
#endif
#define qword_141133588 __qword_141133588
#ifndef __PE_DECL___qword_141133590
#define __PE_DECL___qword_141133590
static __int64& __qword_141133590 = *(__int64*)0x141133590;
#endif
#define qword_141133590 __qword_141133590
#ifndef __PE_DECL___qword_141133598
#define __PE_DECL___qword_141133598
static __int64& __qword_141133598 = *(__int64*)0x141133598;
#endif
#define qword_141133598 __qword_141133598
#ifndef __PE_DECL___qword_1411335A0
#define __PE_DECL___qword_1411335A0
static __int64& __qword_1411335A0 = *(__int64*)0x1411335A0;
#endif
#define qword_1411335A0 __qword_1411335A0
#ifndef __PE_DECL___qword_1411335A8
#define __PE_DECL___qword_1411335A8
static __int64& __qword_1411335A8 = *(__int64*)0x1411335A8;
#endif
#define qword_1411335A8 __qword_1411335A8
#ifndef __PE_DECL___qword_1411335B0
#define __PE_DECL___qword_1411335B0
static __int64& __qword_1411335B0 = *(__int64*)0x1411335B0;
#endif
#define qword_1411335B0 __qword_1411335B0
#ifndef __PE_DECL___qword_1411335B8
#define __PE_DECL___qword_1411335B8
static __int64& __qword_1411335B8 = *(__int64*)0x1411335B8;
#endif
#define qword_1411335B8 __qword_1411335B8
#ifndef __PE_DECL___qword_1411335C0
#define __PE_DECL___qword_1411335C0
static __int64& __qword_1411335C0 = *(__int64*)0x1411335C0;
#endif
#define qword_1411335C0 __qword_1411335C0
#ifndef __PE_DECL___qword_1411335C8
#define __PE_DECL___qword_1411335C8
static __int64& __qword_1411335C8 = *(__int64*)0x1411335C8;
#endif
#define qword_1411335C8 __qword_1411335C8
#ifndef __PE_DECL___qword_1411335D0
#define __PE_DECL___qword_1411335D0
static __int64& __qword_1411335D0 = *(__int64*)0x1411335D0;
#endif
#define qword_1411335D0 __qword_1411335D0
#ifndef __PE_DECL___qword_1411335D8
#define __PE_DECL___qword_1411335D8
static __int64& __qword_1411335D8 = *(__int64*)0x1411335D8;
#endif
#define qword_1411335D8 __qword_1411335D8
#ifndef __PE_DECL___qword_1411335E0
#define __PE_DECL___qword_1411335E0
static __int64& __qword_1411335E0 = *(__int64*)0x1411335E0;
#endif
#define qword_1411335E0 __qword_1411335E0
#ifndef __PE_DECL___qword_1411335E8
#define __PE_DECL___qword_1411335E8
static __int64& __qword_1411335E8 = *(__int64*)0x1411335E8;
#endif
#define qword_1411335E8 __qword_1411335E8
#ifndef __PE_DECL___qword_1411335F0
#define __PE_DECL___qword_1411335F0
static __int64& __qword_1411335F0 = *(__int64*)0x1411335F0;
#endif
#define qword_1411335F0 __qword_1411335F0
#ifndef __PE_DECL___qword_1411335F8
#define __PE_DECL___qword_1411335F8
static __int64& __qword_1411335F8 = *(__int64*)0x1411335F8;
#endif
#define qword_1411335F8 __qword_1411335F8
#ifndef __PE_DECL___qword_141133600
#define __PE_DECL___qword_141133600
static __int64& __qword_141133600 = *(__int64*)0x141133600;
#endif
#define qword_141133600 __qword_141133600
#ifndef __PE_DECL___qword_141133608
#define __PE_DECL___qword_141133608
static __int64& __qword_141133608 = *(__int64*)0x141133608;
#endif
#define qword_141133608 __qword_141133608
#ifndef __PE_DECL___qword_141133610
#define __PE_DECL___qword_141133610
static __int64& __qword_141133610 = *(__int64*)0x141133610;
#endif
#define qword_141133610 __qword_141133610
#ifndef __PE_DECL___qword_141133618
#define __PE_DECL___qword_141133618
static __int64& __qword_141133618 = *(__int64*)0x141133618;
#endif
#define qword_141133618 __qword_141133618
#ifndef __PE_DECL___qword_141133620
#define __PE_DECL___qword_141133620
static __int64& __qword_141133620 = *(__int64*)0x141133620;
#endif
#define qword_141133620 __qword_141133620
#ifndef __PE_DECL___qword_141133628
#define __PE_DECL___qword_141133628
static __int64& __qword_141133628 = *(__int64*)0x141133628;
#endif
#define qword_141133628 __qword_141133628
#ifndef __PE_DECL___qword_141133630
#define __PE_DECL___qword_141133630
static __int64& __qword_141133630 = *(__int64*)0x141133630;
#endif
#define qword_141133630 __qword_141133630
#ifndef __PE_DECL___qword_141133638
#define __PE_DECL___qword_141133638
static __int64& __qword_141133638 = *(__int64*)0x141133638;
#endif
#define qword_141133638 __qword_141133638
#ifndef __PE_DECL___qword_141133640
#define __PE_DECL___qword_141133640
static __int64& __qword_141133640 = *(__int64*)0x141133640;
#endif
#define qword_141133640 __qword_141133640
#ifndef __PE_DECL___qword_1411336F8
#define __PE_DECL___qword_1411336F8
static __int64& __qword_1411336F8 = *(__int64*)0x1411336F8;
#endif
#define qword_1411336F8 __qword_1411336F8
#ifndef __PE_DECL___word_1405DFC24
#define __PE_DECL___word_1405DFC24
typedef __int16 t_word_1405DFC24[1];
static t_word_1405DFC24& __word_1405DFC24 = *(t_word_1405DFC24*)0x1405DFC24;
#endif
#define word_1405DFC24 __word_1405DFC24
#ifndef __PE_DECL___word_141108B24
#define __PE_DECL___word_141108B24
typedef __int16 t_word_141108B24[1];
static t_word_141108B24& __word_141108B24 = *(t_word_141108B24*)0x141108B24;
#endif
#define word_141108B24 __word_141108B24
#ifndef __PE_DECL___word_141128C24
#define __PE_DECL___word_141128C24
static __int16& __word_141128C24 = *(__int16*)0x141128C24;
#endif
#define word_141128C24 __word_141128C24
#ifndef __PE_DECL___xmmword_140028F00
#define __PE_DECL___xmmword_140028F00
typedef __int128 t_xmmword_140028F00[1];
static t_xmmword_140028F00& __xmmword_140028F00 = *(t_xmmword_140028F00*)0x140028F00;
#endif
#define xmmword_140028F00 __xmmword_140028F00
#ifndef __PE_DECL___xmmword_140029100
#define __PE_DECL___xmmword_140029100
typedef __int128 t_xmmword_140029100[1];
static t_xmmword_140029100& __xmmword_140029100 = *(t_xmmword_140029100*)0x140029100;
#endif
#define xmmword_140029100 __xmmword_140029100

// ---- PE-internal function references --------------------------------
#ifndef __PE_DECL___filbuf
#define __PE_DECL___filbuf
typedef __attribute__((ms_abi)) int t_filbuf(FILE *File);
static t_filbuf& __filbuf = *(t_filbuf*)0x1400133CC;
#endif
#define filbuf __filbuf
#ifndef __PE_DECL___flsbuf
#define __PE_DECL___flsbuf
typedef __attribute__((ms_abi)) int t_flsbuf(int Ch, FILE *File);
static t_flsbuf& __flsbuf = *(t_flsbuf*)0x14001323C;
#endif
#define flsbuf __flsbuf
#ifndef __PE_DECL___sub_140007B80
#define __PE_DECL___sub_140007B80
typedef __attribute__((ms_abi)) unsigned __int64 t_sub_140007B80(unsigned __int8 *a1);
static t_sub_140007B80& __sub_140007B80 = *(t_sub_140007B80*)0x140007B80;
#endif
#define sub_140007B80 __sub_140007B80
#define sub_14000B750 __sub_14000B750
#define sub_14000C0E0 __sub_14000C0E0
#define sub_140010730 __sub_140010730
#define sub_140010850 __sub_140010850

PROBE_DECL(__sub_1400037A0)
__attribute__((ms_abi)) int __sub_1400037A0(FILE *a1, FILE *a2) {

  PROBE_HIT(__sub_1400037A0);
  int v2;                 // r12d
  unsigned __int8 *v3;    // rbx
  int v4;                 // ebp
  int v5;                 // edx
  __int64 v6;             // r15
  __int64 v7;             // rdx
  unsigned __int8 v8;     // r8
  int v9;                 // r10d
  __int64 v10;            // r11
  __int64 *v11;           // rcx
  __int64 *v12;           // r8
  unsigned __int8 *v13;   // rdx
  int v14;                // ebx
  int v15;                // eax
  __int64 *v16;           // rbp
  __int64 *i;             // rbx
  __int64 v18;            // r15
  int v19;                // r9d
  int v20;                // r13d
  int v21;                // r14d
  int v22;                // eax
  unsigned __int8 *v23;   // rbx
  __int64 v24;            // r8
  int v25;                // ecx
  int v26;                // r11d
  int v27;                // edx
  unsigned __int8 v28;    // r10
  int v29;                // r10d
  int v30;                // r12d
  unsigned __int8 *v31;   // rdx
  unsigned __int8 *v32;   // r8
  int v33;                // r11d
  int v34;                // eax
  int v35;                // r12d
  int v36;                // edx
  int v37;                // edi
  int v38;                // r10d
  unsigned int v39;       // eax
  unsigned __int8 *v40;   // r8
  int v41;                // edx
  int v42;                // r10d
  int v43;                // r11d
  int v44;                // r10d
  int v45;                // r11d
  char v46;               // r15
  __int64 v47;            // rdx
  int *v48;               // rax
  int v49;                // r9d
  int v50;                // r9d
  unsigned int v51;       // r8d
  int v52;                // r8d
  int v53;                // r11d
  int v54;                // r8d
  unsigned int v55;       // r9d
  int v56;                // r9d
  int *v57;               // rax
  int v58;                // r8d
  __int64 v59;            // rdx
  int v60;                // r9d
  unsigned __int16 v61;   // ax
  unsigned int v62;       // r9d
  unsigned int v63;       // edx
  int v64;                // r9d
  int v65;                // r8d
  int v66;                // eax
  __int64 *v67;           // r15
  unsigned __int8 *v68;   // r14
  unsigned int v69;       // r15d
  unsigned int v70;       // ebp
  __int64 v71;            // r13
  BOOL v72;               // r15d
  bool v73;               // zf
  int v74;                // r10d
  int v75;                // r8d
  __int16 v76;            // dx
  int v77;                // r12d
  unsigned int v78;       // ecx
  __int64 v79;            // r15
  __int64 v80;            // r8
  unsigned __int16 *v81;  // r12
  int v82;                // ecx
  int v83;                // eax
  unsigned __int16 v84;   // r11
  int v85;                // r11d
  int *v86;               // r8
  int v87;                // edx
  int v88;                // eax
  int v89;                // r12d
  int v90;                // r9d
  int v91;                // eax
  int v92;                // edx
  int v93;                // eax
  int v94;                // edx
  int v95;                // r8d
  int v96;                // r12d
  unsigned int v97;       // r9d
  int *v98;               // r14
  int *v99;               // rdx
  int v100;               // ebx
  int *v101;              // r15
  char v102;              // al
  bool v103;              // cf
  int v104;               // r9d
  bool v105;              // di
  unsigned int v106;      // r13d
  unsigned int v107;      // ebx
  unsigned int v108;      // r9d
  unsigned int v109;      // r13d
  unsigned int v110;      // r14d
  __int64 v111;           // r10
  unsigned int v112;      // ebx
  int v113;               // ecx
  int v114;               // ebp
  int v115;               // r10d
  unsigned int v116;      // r12d
  char v117;              // si
  unsigned int v118;      // r8d
  char v119;              // al
  unsigned int v120;      // r14d
  unsigned __int16 *v121; // rax
  __int64 v122;           // r10
  int v123;               // r9d
  int v124;               // r13d
  __int64 v125;           // r11
  int v126;               // edx
  unsigned int v127;      // edx
  int v128;               // r9d
  char v129;              // dl
  unsigned __int16 v130;  // r11
  unsigned int v131;      // edx
  char v132;              // dl
  unsigned __int16 v133;  // r9
  unsigned __int16 v134;  // r9
  int *v135;              // r10
  int v136;               // edx
  int v137;               // eax
  int v138;               // r8d
  int v139;               // r9d
  int v140;               // eax
  int v141;               // edx
  int v142;               // edx
  int v143;               // eax
  int v144;               // edx
  int v145;               // r15d
  int v146;               // r8d
  __int64 v147;           // r11
  int *v148;              // r10
  int v149;               // r9d
  int v150;               // eax
  int v151;               // r12d
  int v152;               // edx
  int v153;               // eax
  int v154;               // r9d
  int v155;               // edx
  __int64 v156;           // r13
  int v157;               // eax
  unsigned int v158;      // edx
  int v159;               // r10d
  int v160;               // r8d
  __int64 v161;           // r10
  int *v162;              // rbp
  int v163;               // edx
  int v164;               // eax
  int v165;               // r8d
  int v166;               // edx
  int v167;               // eax
  unsigned int v168;      // r9d
  int v169;               // edx
  unsigned int v170;      // r13d
  int v171;               // ebp
  unsigned int v172;      // eax
  __int64 v173;           // rdx
  int v174;               // ebp
  int v175;               // r10d
  _DWORD *v176;           // r11
  unsigned int v177;      // r15d
  unsigned __int8 v178;   // dl
  __int16 v179;           // ax
  __int16 v180;           // bp
  unsigned __int64 v181;  // rbp
  int v182;               // edx
  int v183;               // r8d
  int v184;               // edx
  unsigned int v185;      // eax
  _DWORD *v186;           // r10
  __int64 v187;           // r14
  int v188;               // r12d
  int v189;               // ebp
  int v190;               // r9d
  unsigned int v191;      // eax
  __int64 v192;           // rbp
  int v193;               // edx
  __int64 v194;           // r8
  __int64 v195;           // r15
  int v196;               // edx
  _DWORD *v197;           // r8
  int v198;               // edx
  __int64 v199;           // rbp
  int result;             // eax
  int v201;               // r14d
  unsigned int v202;      // ebx
  int v203;               // esi
  int v204;               // r12d
  int v205;               // ebp
  int v206;               // ebp
  int v207;               // r10d
  __int64 v208;           // r9
  int v209;               // r14d
  int v210;               // r10d
  char v211;              // al
  int v212;               // ebp
  __int64 *v213;          // rcx
  __int64 *v214;          // rdx
  __int64 v215;           // r11
  unsigned __int8 *v216;  // r9
  __int64 *v217;          // r14
  int v218;               // r11d
  __int64 v219;           // r15
  __int64 v220;           // r14
  int v221;               // r15d
  unsigned __int8 *v222;  // r13
  __int64 *v223;          // r10
  unsigned __int8 *v224;  // rdx
  __int64 v225;           // r13
  __int64 v226;           // rbp
  __int64 v227;           // rdx
  unsigned __int8 *v228;  // r9
  unsigned int v229;      // eax
  unsigned __int8 v230;   // al
  int v231;               // r9d
  unsigned __int8 *v232;  // rdx
  unsigned __int8 *v233;  // r11
  int v234;               // r9d
  unsigned int v235;      // r8d
  unsigned int v236;      // edx
  __int64 v237;           // rdx
  int v238;               // ebp
  unsigned __int8 *j;     // rdx
  unsigned int v240;      // eax
  int v241;               // edx
  __int16 v242;           // r8
  unsigned int v243;      // eax
  unsigned int v244;      // r9d
  unsigned int v245;      // r8d
  unsigned int v246;      // ebp
  __int64 v247;           // rax
  int v248;               // r10d
  __int64 v249;           // r10
  unsigned int v250;      // eax
  int v251;               // edx
  int v252;               // r11d
  int v253;               // r12d
  int v254;               // ecx
  unsigned int v255;      // ecx
  BOOL v256;              // edx
  int v257;               // r8d
  __int64 v258;           // r10
  unsigned int v259;      // edx
  BOOL v260;              // edx
  __int64 v261;           // r12
  int *v262;              // r13
  __int64 v263;           // rdx
  int *v264;              // r13
  int v265;               // eax
  int v266;               // edx
  unsigned __int16 v267;  // r8
  int v268;               // r10d
  int v269;               // r9d
  int v270;               // r15d
  int v271;               // r10d
  int *v272;              // r10
  int v273;               // r8d
  int v274;               // eax
  int v275;               // r15d
  int v276;               // r8d
  int v277;               // eax
  int v278;               // edx
  int v279;               // eax
  int v280;               // edx
  int v281;               // r14d
  int v282;               // r15d
  unsigned __int16 *v283; // r8
  unsigned int v284;      // edx
  int v285;               // r13d
  int *v286;              // r12
  unsigned int v287;      // r9d
  int v288;               // r15d
  int v289;               // r14d
  __int64 v290;           // r9
  unsigned __int16 v291;  // dx
  char v292;              // bp
  __int64 v293;           // r9
  unsigned __int16 v294;  // dx
  unsigned __int16 *v295; // rax
  int v296;               // r11d
  int v297;               // r9d
  int v298;               // r12d
  unsigned int v299;      // r11d
  int v300;               // r9d
  unsigned __int16 v301;  // r9
  __int64 v302;           // r12
  unsigned __int16 v303;  // dx
  char v304;              // bp
  __int64 v305;           // r12
  unsigned __int16 v306;  // dx
  __int64 v307;           // r12
  unsigned __int16 v308;  // dx
  __int64 v309;           // r12
  unsigned __int16 v310;  // dx
  __int64 v311;           // r12
  unsigned __int16 v312;  // dx
  __int64 v313;           // r12
  unsigned __int16 v314;  // dx
  int *v315;              // r10
  int v316;               // edx
  int v317;               // eax
  int v318;               // ebp
  int v319;               // r8d
  int v320;               // eax
  int v321;               // edx
  int v322;               // edx
  int v323;               // eax
  int v324;               // edx
  int v325;               // ebp
  __int64 v326;           // r8
  int *v327;              // r11
  int v328;               // r9d
  int v329;               // eax
  int v330;               // r10d
  int v331;               // edx
  int v332;               // eax
  int v333;               // r9d
  int v334;               // edx
  __int64 v335;           // r12
  unsigned int v336;      // ecx
  BOOL v337;              // ebp
  int v338;               // edx
  int v339;               // r11d
  int v340;               // edx
  int *v341;              // r11
  int v342;               // ebp
  int v343;               // eax
  int v344;               // ebp
  int v345;               // edx
  int v346;               // eax
  unsigned int v347;      // r8d
  int v348;               // edx
  unsigned int v349;      // r13d
  int v350;               // r9d
  unsigned int v351;      // eax
  int v352;               // edx
  bool v353;              // bp
  _DWORD *v354;           // r9
  int v355;               // r8d
  _DWORD *v356;           // r11
  int v357;               // r10d
  _DWORD *v358;           // r13
  int v359;               // r12d
  _DWORD *v360;           // r15
  int v361;               // r14d
  unsigned __int8 v362;   // bp
  __int64 v363;           // rdx
  _DWORD *v364;           // rbp
  int v365;               // ebx
  _DWORD *v366;           // rbx
  unsigned int v367;      // r14d
  __int64 v368;           // rcx
  int v369;               // r12d
  bool v370;              // sf
  __int64 v371;           // rbx
  int v372;               // ebx
  int v373;               // edx
  __int64 v374;           // rcx
  int v375;               // r14d
  int v376;               // ebp
  int v377;               // esi
  unsigned int v378;      // edi
  __int64 v379;           // r12
  int v380;               // r12d
  int v381;               // edx
  int v382;               // ebx
  int v383;               // r11d
  __int64 *v384;          // rbx
  __int64 *k;             // r8
  __int64 v386;           // r15
  __int64 v387;           // rax
  __int64 v388;           // r11
  int v389;               // esi
  unsigned __int8 *v390;  // r12
  unsigned __int8 v391;   // r9
  int v392;               // eax
  unsigned __int8 *v393;  // r10
  int v394;               // edx
  int v395;               // r10d
  int v396;               // r12d
  int v397;               // r9d
  unsigned int v398;      // r11d
  __int64 v399;           // r8
  int v400;               // edx
  int v401;               // edi
  int v402;               // r13d
  unsigned int v403;      // eax
  int v404;               // r10d
  int v405;               // ecx
  __int64 v406;           // rax
  __int64 v407;           // r10
  char *v408;             // r14
  unsigned int v409;      // r15d
  int v410;               // r9d
  unsigned int v411;      // edx
  unsigned int v412;      // r11d
  unsigned int v413;      // r10d
  int v414;               // r11d
  int v415;               // r10d
  int v416;               // r9d
  int v417;               // r10d
  unsigned int v418;      // r10d
  char *v419;             // r14
  int v420;               // r9d
  unsigned __int16 v421;  // r9
  unsigned int v422;      // r9d
  int v423;               // r14d
  BOOL v424;              // r11d
  __int64 v425;           // r11
  int v426;               // edx
  __int64 v427;           // r12
  int v428;               // r11d
  __int64 v429;           // r10
  signed int v430;        // r9d
  int v431;               // edx
  unsigned __int16 *v432; // [rsp+20h] [rbp-4C8h]
  unsigned __int16 *v433; // [rsp+20h] [rbp-4C8h]
  unsigned __int16 *v434; // [rsp+20h] [rbp-4C8h]
  unsigned __int16 *v435; // [rsp+20h] [rbp-4C8h]
  unsigned __int16 *v436; // [rsp+28h] [rbp-4C0h]
  __int64 v437;           // [rsp+30h] [rbp-4B8h]
  __int64 v438;           // [rsp+38h] [rbp-4B0h]
  char v439;              // [rsp+40h] [rbp-4A8h]
  char v440;              // [rsp+40h] [rbp-4A8h]
  int v441;               // [rsp+48h] [rbp-4A0h]
  int v442;               // [rsp+50h] [rbp-498h]
  int v443;               // [rsp+50h] [rbp-498h]
  int v444;               // [rsp+50h] [rbp-498h]
  int v445;               // [rsp+50h] [rbp-498h]
  int v446;               // [rsp+50h] [rbp-498h]
  int v447;               // [rsp+58h] [rbp-490h]
  int v448;               // [rsp+58h] [rbp-490h]
  int v449;               // [rsp+58h] [rbp-490h]
  int v450;               // [rsp+58h] [rbp-490h]
  char v451;              // [rsp+60h] [rbp-488h]
  __int64 v452;           // [rsp+68h] [rbp-480h]
  int v453;               // [rsp+78h] [rbp-470h]
  int v454;               // [rsp+78h] [rbp-470h]
  int v455;               // [rsp+78h] [rbp-470h]
  int v456;               // [rsp+78h] [rbp-470h]
  int v457;               // [rsp+78h] [rbp-470h]
  int v458;               // [rsp+78h] [rbp-470h]
  int *v459;              // [rsp+80h] [rbp-468h]
  int *v460;              // [rsp+80h] [rbp-468h]
  int *v461;              // [rsp+80h] [rbp-468h]
  int *v462;              // [rsp+80h] [rbp-468h]
  int v463;               // [rsp+88h] [rbp-460h]
  int v464;               // [rsp+88h] [rbp-460h]
  int v465;               // [rsp+88h] [rbp-460h]
  int v466;               // [rsp+88h] [rbp-460h]
  bool v467;              // [rsp+90h] [rbp-458h]
  char v468;              // [rsp+98h] [rbp-450h]
  char v469;              // [rsp+A0h] [rbp-448h]
  char v470;              // [rsp+B0h] [rbp-438h]
  unsigned int v471;      // [rsp+B8h] [rbp-430h]
  int *v472;              // [rsp+C0h] [rbp-428h]
  __int64 v473;           // [rsp+C8h] [rbp-420h]
  __int64 v474;           // [rsp+D0h] [rbp-418h]
  unsigned __int8 *v475;  // [rsp+D8h] [rbp-410h]
  int v476;               // [rsp+E0h] [rbp-408h]
  int v477;               // [rsp+E0h] [rbp-408h]
  int v478;               // [rsp+E8h] [rbp-400h]
  __int64 v479;           // [rsp+F0h] [rbp-3F8h]
  char v480;              // [rsp+F8h] [rbp-3F0h]
  bool v481;              // [rsp+100h] [rbp-3E8h]
  int *v482;              // [rsp+108h] [rbp-3E0h]
  char v483;              // [rsp+118h] [rbp-3D0h]
  unsigned int v484;      // [rsp+120h] [rbp-3C8h]
  int *v485;              // [rsp+130h] [rbp-3B8h]
  __int64 v486;           // [rsp+138h] [rbp-3B0h]
  __int64 v487;           // [rsp+140h] [rbp-3A8h]
  int v488;               // [rsp+148h] [rbp-3A0h]
  int v489;               // [rsp+148h] [rbp-3A0h]
  int v490;               // [rsp+148h] [rbp-3A0h]
  int v491;               // [rsp+148h] [rbp-3A0h]
  int v492;               // [rsp+148h] [rbp-3A0h]
  int v493;               // [rsp+148h] [rbp-3A0h]
  __int64 *v494;          // [rsp+150h] [rbp-398h]
  __int64 *v495;          // [rsp+150h] [rbp-398h]
  int v496;               // [rsp+158h] [rbp-390h]
  __int64 v497;           // [rsp+160h] [rbp-388h]
  int v498;               // [rsp+168h] [rbp-380h]
  int v499;               // [rsp+170h] [rbp-378h]
  __int64 v500;           // [rsp+178h] [rbp-370h]
  unsigned __int8 *v501;  // [rsp+180h] [rbp-368h]
  int v502;               // [rsp+188h] [rbp-360h]
  __int64 v503;           // [rsp+190h] [rbp-358h]
  unsigned int v504;      // [rsp+198h] [rbp-350h]
  int v505;               // [rsp+1A0h] [rbp-348h]
  __int64 v506;           // [rsp+1A8h] [rbp-340h]
  BOOL v507;              // [rsp+1B0h] [rbp-338h]
  unsigned int v508;      // [rsp+1B8h] [rbp-330h]
  __int64 v509;           // [rsp+1C0h] [rbp-328h]
  int v510;               // [rsp+1C8h] [rbp-320h]
  __int64 v511;           // [rsp+1D0h] [rbp-318h]
  int v512;               // [rsp+1D8h] [rbp-310h]
  unsigned __int8 v513;   // [rsp+1E0h] [rbp-308h]
  unsigned int v514;      // [rsp+1E8h] [rbp-300h]
  unsigned int v515;      // [rsp+1F0h] [rbp-2F8h]
  int v516;               // [rsp+200h] [rbp-2E8h]
  int v517;               // [rsp+200h] [rbp-2E8h]
  int v518;               // [rsp+200h] [rbp-2E8h]
  int v519;               // [rsp+200h] [rbp-2E8h]
  int v520;               // [rsp+208h] [rbp-2E0h]
  __int64 v521;           // [rsp+210h] [rbp-2D8h]
  unsigned int v522;      // [rsp+218h] [rbp-2D0h]
  int v523;               // [rsp+220h] [rbp-2C8h]
  int v524;               // [rsp+220h] [rbp-2C8h]
  int v525;               // [rsp+220h] [rbp-2C8h]
  int v526;               // [rsp+220h] [rbp-2C8h]
  int v527;               // [rsp+220h] [rbp-2C8h]
  int v528;               // [rsp+220h] [rbp-2C8h]
  int v529;               // [rsp+220h] [rbp-2C8h]
  int v530;               // [rsp+220h] [rbp-2C8h]
  int v531;               // [rsp+228h] [rbp-2C0h]
  int v532;               // [rsp+230h] [rbp-2B8h]
  int v533;               // [rsp+238h] [rbp-2B0h]
  int v534;               // [rsp+240h] [rbp-2A8h]
  int v535;               // [rsp+248h] [rbp-2A0h]
  int v536;               // [rsp+250h] [rbp-298h]
  char v537;              // [rsp+258h] [rbp-290h]
  unsigned __int8 *v538;  // [rsp+270h] [rbp-278h]
  unsigned int v539;      // [rsp+288h] [rbp-260h]
  int v540;               // [rsp+290h] [rbp-258h]
  __int64 v541;           // [rsp+298h] [rbp-250h]
  unsigned __int8 *v542;  // [rsp+2A8h] [rbp-240h]
  int v543;               // [rsp+2B0h] [rbp-238h]
  unsigned int v544;      // [rsp+2B8h] [rbp-230h]
  unsigned int v545;      // [rsp+2C0h] [rbp-228h]
  unsigned int v546;      // [rsp+2C8h] [rbp-220h]
  __int64 v547;           // [rsp+2D0h] [rbp-218h]
  unsigned int v548;      // [rsp+2E0h] [rbp-208h]
  int v549;               // [rsp+2E8h] [rbp-200h]
  unsigned __int8 *v550;  // [rsp+2F8h] [rbp-1F0h]
  unsigned __int8 *v551;  // [rsp+2F8h] [rbp-1F0h]
  unsigned __int8 *v552;  // [rsp+2F8h] [rbp-1F0h]
  __int64 v553;           // [rsp+300h] [rbp-1E8h]
  unsigned __int16 *v554; // [rsp+300h] [rbp-1E8h]
  unsigned __int16 *v555; // [rsp+300h] [rbp-1E8h]
  unsigned __int16 *v556; // [rsp+300h] [rbp-1E8h]
  unsigned int v557;      // [rsp+308h] [rbp-1E0h]
  unsigned __int8 *v558;  // [rsp+310h] [rbp-1D8h]
  unsigned int v559;      // [rsp+318h] [rbp-1D0h]
  __int64 v560;           // [rsp+320h] [rbp-1C8h]
  int v563;               // [rsp+3B8h] [rbp-130h]
  int v564;               // [rsp+3B8h] [rbp-130h]
  __int16 v565;           // [rsp+3C0h] [rbp-128h]
  int v566;               // [rsp+3C8h] [rbp-120h]
  int v567;               // [rsp+3D0h] [rbp-118h]
  int v568;               // [rsp+3D8h] [rbp-110h]
  unsigned __int8 *v569;  // [rsp+3E0h] [rbp-108h]
  __int64 v570;           // [rsp+3E8h] [rbp-100h]
  __int16 v571;           // [rsp+3F0h] [rbp-F8h]
  int v572;               // [rsp+3F8h] [rbp-F0h]
  int v573;               // [rsp+400h] [rbp-E8h]
  unsigned int v574;      // [rsp+408h] [rbp-E0h]
  int v575;               // [rsp+418h] [rbp-D0h]
  __int64 v576;           // [rsp+420h] [rbp-C8h]

  v2 = dword_141133664;
  do {
    v3 = (unsigned __int8 *)qword_141133580;
    v4 = *(unsigned __int8 *)qword_141133580;
    v5 = a2->_cnt - 1;
    a2->_cnt = v5;
    if(v5 < 0)
      v566 = filbuf(a2);
    else
      v566 = *(unsigned __int8 *)a2->_ptr++;
    if(v4) {
      v6 = qword_141133588;
      v7 = *((unsigned int *)v3 + 1);
      v8 = v3[1];
      if(!*(_BYTE *)(qword_141133588 + v7 + 6LL * (v8 & 0xF) + 1)) {
        sub_14000C0E0(v3);
        v7 = *((unsigned int *)v3 + 1);
        v8 = v3[1];
      }
      v563 = v4;
      v540 = *v3;
      v539 = v540 + 1;
      v9 = v540 + 1;
      v541 = v6;
      v550 = v3;
      qword_14025F220[0] = v6 + v7 + 6LL * (v8 & 0xF);
      v10 = *(unsigned __int8 *)qword_14025F220[0];
      v11 = &qword_14025F228;
      v12 = &qword_14025F228;
      v567 = *(unsigned __int8 *)qword_14025F220[0];
      dword_141133674 = v567;
      v13 = (unsigned __int8 *)(v6 + v7 - 6);
      dword_140029540[v10] = v2;
      while(1) {
        v13 += 6;
        v14 = *v13;
        if((_DWORD)v10 != v14) {
          dword_140029540[*v13] = v2;
          *v11++ = (__int64)v13;
          if(v14 == dword_14014AD70) {
            v15 = 22;
            v16 = &qword_14025F220[(byte_14014AD5C & 7) == 0];
          LABEL_14:
            for(i = v11 - 1; i > v16; --i) {
              v18 = *(i - 1);
              if(v15 * *(unsigned __int8 *)(*i + 1) <= *(unsigned __int8 *)(v18 + 1))
                break;
              *(i - 1) = *i;
              *i = v18;
            }
            ++v12;
            goto LABEL_18;
          }
          if(v2 == dword_14010A958[v14] || v2 == dword_14010A558[v14]) {
            v16 = v12;
            v15 = 11 * (v2 == dword_14010A958[v14]) + 7;
            goto LABEL_14;
          }
        }
      LABEL_18:
        if(!--v9) {
          v19 = v540 + 1;
          v20 = v540 + 1;
          v21 = v540 + 1;
          v22 = v540;
          v23 = v550;
          dword_14014AD7C = *(unsigned __int8 *)qword_14025F220[0];
          dword_14010A158[(unsigned __int8)byte_1400DA158[dword_14014AD7C + (dword_14014ADD0 << 8)]] = v2;
          qword_1411335A8 = (__int64)&dword_1405DFC20;
          qword_1411335A0 = (__int64)&dword_1405DFC20;
          qword_141133598 = (__int64)&dword_1405DFC20;
          qword_141133590 = (__int64)&dword_1405DFC20;
          qword_141133618 = (__int64)&dword_1405DFC20;
          if(v540 == 255) {
            v44 = dword_141133690;
            v46 = dword_141133698;
            v45 = dword_1411336E0;
            v64 = *((unsigned __int16 *)v550 + 1);
            qword_1411335B0 = (__int64)&dword_1405DFC20;
            v568 = -1;
            dword_141133678 = -1;
            dword_1411336E4 = v64;
            v62 = v64 + 1;
            dword_1411336E8 = v62;
          } else {
            v24 = *((unsigned int *)v550 + 2);
            v25 = *(unsigned __int8 *)(v24 + v541);
            v26 = *((unsigned __int16 *)v550 + 1);
            v27 = *(unsigned __int16 *)(v24 + v541 + 2);
            v28 = v550[1];
            qword_141133620 = (__int64)qword_14025F220;
            v20 = v25 + 1;
            v505 = v27;
            v513 = v28;
            v29 = v26;
            if((v25 + 1) * v26 > (int)(v27 * v539) || (v479 = *((unsigned int *)v550 + 1), *(unsigned __int8 *)(v479 + v541 + 1) >= 0x6Au)) {
              v510 = v26;
              v21 = v540 + 1;
              v506 = v539;
            } else if((v513 & 0x40) != 0) {
              v510 = v26;
              v21 = v540 + 1;
              v506 = v539;
            } else {
              v516 = v2;
              v30 = v25 + 1;
              v31 = (unsigned __int8 *)(v541 + *(unsigned int *)(v24 + v541 + 4) - 6);
              do {
                v31 += 6;
                --v30;
                byte_141108A20[*v31] = v31[1];
              } while(v30);
              v506 = v539;
              v32 = (unsigned __int8 *)(v479 + v541 + 6LL * v539);
              v33 = 9 * v540 + 9 + 2 * v540 + 2;
              v34 = v29;
              v35 = v20 * (((unsigned int)(v33 - v29) >> 28) | 7) + v505;
              do {
                v32 -= 6;
                v37 = v32[1];
                if(v37 * v35 < (v33 + v34) * (unsigned __int8)byte_141108A20[*v32] && v32[1] <= 0xE4u) {
                  v38 = v29 - v37;
                  v36 = (unsigned __int8)byte_141108A20[*v32];
                  v39 = ((v33 + v34 - v37) * (3 * v37 + v36) + 3 * (v33 + v34 - v37) + v35 - v36 - 4) / (unsigned int)(3 * (v33 + v34 - v37) + v35 - v36);
                  if(v39 > v37 + 11)
                    v39 = v37 + 11;
                  v29 = v39 + v38;
                  *((_WORD *)v550 + 1) = v29;
                  v32[1] = v39;
                  v34 = (unsigned __int16)v29;
                }
                --v19;
              } while(v19);
              v21 = v540 + 1;
              v2 = v516;
              v24 = *((unsigned int *)v550 + 2);
              v510 = v34;
              v22 = v540;
              v513 = v550[1];
            }
            v512 = *v550;
            v40 = (unsigned __int8 *)(v541 + v24);
            v41 = *(unsigned __int8 *)(v541 + *((unsigned int *)v40 + 1) + 6LL * (v40[1] & 0xF));
            v42 = v41;
            v568 = v41;
            if(v41 == v567) {
              v43 = *(unsigned __int8 *)(v541 + *((unsigned int *)v40 + 1) + 6LL * (v40[1] & 0xF));
              do {
                if(*v40 != v512)
                  break;
                v40 = (unsigned __int8 *)(v541 + *((unsigned int *)v40 + 2));
                v42 = *(unsigned __int8 *)(v541 + *((unsigned int *)v40 + 1) + 6LL * (v40[1] & 0xF));
                v43 = v42;
              } while(v42 == v567);
              v568 = v43;
              dword_141133678 = v42;
            } else {
              dword_141133678 = *(unsigned __int8 *)(v541 + *((unsigned int *)v40 + 1) + 6LL * (v40[1] & 0xF));
            }
            v508 = v2 != dword_140029540[dword_14113369C];
            v507 = v2 != dword_140029540[v41];
            v44 = dword_141133690;
            v45 = dword_1411336E0;
            v46 = dword_141133698;
            v511 = (unsigned __int8)byte_1400292BE[v506];
            v47 = (int)(8 * (v512 + 2 * v25 + 2 > dword_1411336E0) + (dword_141133698 & 3) + 4 * (dword_141133690 < 10) + ((v2 != dword_140029540[v568]) << 9) + (v508 << 8) + (((unsigned int)(8 * v22 + 8 + 4 * v22 + 4 - v510) >> 26) & 0xFFFFFFE0) + (v513 & 0xC0) + (((unsigned int)(3 * v25 + 3 - (4 * v22 + 4)) >> 27) & 0xFFFFFFF0));
            v509 = v47;
            v48 = &dword_141108B20[2048 * v511 + 2 * v47];
            v49 = *v48;
            qword_1411335B0 = (__int64)v48;
            v515 = v49;
            dword_141133680 = v49;
            v50 = (unsigned __int16)word_141108B24[4096 * v511 + 4 * v47];
            v514 = v50;
            dword_14113367C = v50;
            if(v50 > 0x8000 || v515 > 0x80000) {
              v462 = &dword_141108B20[2048 * v511 + 2 * v47];
              v466 = v47;
              v493 = dword_1411336E0;
              v458 = dword_141133690;
              sub_140010730(v462);
              v44 = v458;
              v45 = v493;
              LODWORD(v47) = v466;
              v48 = v462;
              LOWORD(v50) = *((_WORD *)v462 + 2);
            }
            v51 = *((unsigned __int16 *)v48 + 3);
            *((_WORD *)v48 + 2) = v51 + v50;
            if(v51 > 0x80) {
              v488 = v45;
              v485 = &dword_141128C20[512 * v511 + 16 * (v507 | v508) + 2 * ((unsigned __int8)v47 & 0xF3)];
              qword_1411335A8 = (__int64)v485;
              v483 = v51 < 0x200;
              qword_141133618 = (__int64)(v48 + 2048);
              v52 = *(v48 - 2048);
              v482 = v48 - 2048;
              qword_141133590 = (__int64)(v48 - 2048);
              v484 = v48[2048];
              v53 = ((v484 + v52) >> (v483 + 1)) + v515;
              v54 = *((unsigned __int16 *)v48 + 4098);
              v515 = v53;
              v55 = (v54 + (unsigned int)*((unsigned __int16 *)v48 - 4094)) >> (v483 + 1);
              dword_141133680 = v53;
              v45 = v488;
              v514 += v55;
              dword_14113367C = v514;
              if(v54 > 0x8000 || v484 > 0x80000) {
                v461 = v48;
                v465 = v47;
                v457 = v44;
                sub_140010730(v48 + 2048);
                v44 = v457;
                v45 = v488;
                LODWORD(v47) = v465;
                v48 = v461;
                LOWORD(v54) = *((_WORD *)v461 + 4098);
              }
              dword_1411336EC = *((unsigned __int16 *)v48 + 4099) >> v483;
              v56 = *((unsigned __int16 *)v48 - 4094);
              *((_WORD *)v48 + 4098) = dword_1411336EC + v54;
              if(v56 > 0x8000 || (unsigned int)*(v48 - 2048) > 0x80000) {
                v460 = v48;
                v464 = v47;
                v492 = v45;
                v456 = v44;
                sub_140010730(v482);
                v44 = v456;
                v45 = v492;
                LODWORD(v47) = v464;
                v48 = v460;
                LOWORD(v56) = *((_WORD *)v460 - 4094);
              }
              dword_1411336B8 = *((unsigned __int16 *)v48 - 4093) >> v483;
              *((_WORD *)v48 - 4094) = dword_1411336B8 + v56;
              v481 = *((unsigned __int16 *)v48 + 3) < 0x400u;
              v480 = v483 + v481;
              v57 = &v48[-2 * v509];
              v58 = LOWORD(v57[2 * (int)(v47 ^ 0x100) + 1]);
              v486 = (__int64)&v57[2 * (int)(v47 ^ 0x100)];
              qword_141133598 = v486;
              if(v58 > 0x8000 || *(_DWORD *)v486 > 0x80000u) {
                v459 = v57;
                v463 = v47;
                v491 = v45;
                v455 = v44;
                sub_140010730(v486);
                v44 = v455;
                v45 = v491;
                LODWORD(v47) = v463;
                v57 = v459;
                LOWORD(v58) = *(_WORD *)(v486 + 4);
              }
              dword_1411336BC = *(unsigned __int16 *)(v486 + 6) >> v480;
              *(_WORD *)(v486 + 4) = dword_1411336BC + v58;
              v59 = (__int64)&v57[2 * (int)(v47 ^ 0x200)];
              v60 = *(unsigned __int16 *)(v59 + 4);
              v487 = v59;
              qword_1411335A0 = v59;
              if(v60 > 0x8000 || *(_DWORD *)v59 > 0x80000u) {
                v490 = v45;
                v454 = v44;
                sub_140010730(v59);
                v44 = v454;
                v45 = v490;
                LOWORD(v60) = *(_WORD *)(v487 + 4);
              }
              dword_1411336C0 = *(unsigned __int16 *)(v487 + 6) >> v480;
              *(_WORD *)(v487 + 4) = dword_1411336C0 + v60;
              v61 = *((_WORD *)v485 + 2);
              if(v61 > 0x8000u || (unsigned int)*v485 > 0x80000) {
                v489 = v45;
                v453 = v44;
                sub_140010730(v485);
                v44 = v453;
                v45 = v489;
                v61 = *((_WORD *)v485 + 2);
              }
              dword_1411336C4 = *((unsigned __int16 *)v485 + 3) >> (v483 + v481 + 1);
              *((_WORD *)v485 + 2) = dword_1411336C4 + v61;
            }
            dword_1411336E4 = *((unsigned __int16 *)v550 + 1);
            v62 = dword_1411336E4 + ((v514 >> 1) + v21 * v515) / v514 + 2;
            dword_1411336E8 = v62;
            if(v21 < 24) {
              dword_1411336F0 = 0;
              v63 = 0;
            LABEL_58:
              dword_1411336CC = 171;
              v574 = v63;
              v65 = 0;
              dword_1411336C8 = 0;
              v66 = 171;
              dword_1411336F4 = 1032 * (*((_DWORD *)v550 + 2) == 0) + 32 * (v46 & 3) + 2 * (v44 < 3);
              v575 = dword_1411336F4;
              v564 = v563 + 1;
              v67 = qword_14025F220;
              dword_14113368C += (((unsigned int)(v20 - v21 - 4) >> 24) & 0xFFFFFF80) + 28672 * ((unsigned int)(40 - v21) >> 31) + 32 * (*v550 > v45) + 28672;
              v571 = dword_1411336A0;
              goto LABEL_59;
            }
          }
          v63 = v62 >> 1;
          dword_1411336F0 = v62 >> 1;
          goto LABEL_58;
        }
      }
    }
    v220 = qword_141133588;
    v221 = v3[2];
    dword_141133674 = v221;
    v222 = v3;
    v223 = qword_14025F220;
    dword_14014AD7C = v221;
    dword_14010A158[(unsigned __int8)byte_1400DA158[v221 + (dword_14014ADD0 << 8)]] = v2;
    do {
      v224 = v222 + 2;
      v225 = *((unsigned int *)v222 + 2);
      *v223++ = (__int64)v224;
      v222 = (unsigned __int8 *)(v220 + v225);
      LODWORD(v226) = *v222;
    } while(!*v222);
    v227 = *((unsigned int *)v222 + 1);
    v546 = v223 - qword_14025F220;
    v545 = v546;
    v228 = (unsigned __int8 *)(v220 + v227 + 6LL * *v222);
    if(!v228[1]) {
      v229 = v223 - qword_14025F220;
      do {
        if(*v228 != v221)
          break;
        v222 = (unsigned __int8 *)(v220 + *((unsigned int *)v222 + 2));
        v227 = *((unsigned int *)v222 + 1);
        v226 = *v222;
        ++v229;
        v228 = (unsigned __int8 *)(v220 + v227 + 6 * v226);
      } while(!v228[1]);
      v545 = v229;
    }
    v230 = v222[1];
    v544 = v226 + 1;
    if(!*(_BYTE *)(v227 + v220 + 6LL * (v230 & 0xF) + 1)) {
      v494 = v223;
      sub_14000C0E0(v222);
      v223 = v494;
      v227 = *((unsigned int *)v222 + 1);
      v230 = v222[1];
    }
    v231 = *(unsigned __int8 *)(v227 + v220 + 6LL * (v230 & 0xF));
    v232 = (unsigned __int8 *)(v220 + v227);
    v543 = v231;
    dword_141133678 = v231;
    v542 = v232;
    if(v221 != *v232) {
      v233 = v232;
      do
        v233 += 6;
      while(v221 != *v233);
      v542 = v233;
    }
    v234 = v542[1];
    v235 = *((unsigned __int16 *)v222 + 1);
    if(2 * v234 + 23 > v232[7] + v232[1]) {
      v236 = *((_DWORD *)v222 + 2);
      if(v236) {
        v475 = (unsigned __int8 *)(v220 + v236);
        v478 = *((unsigned __int16 *)v475 + 1);
        v476 = *v475;
        if(v235 + v235 * v476 < v544 * (v478 + 15)) {
          v237 = *((unsigned int *)v475 + 1);
          v477 = v476 + 1;
          if(!*(_BYTE *)(v220 + v237 + 6LL * (v475[1] & 0xF) + 1)) {
            v495 = v223;
            sub_14000C0E0(v475);
            v223 = v495;
            v234 = v542[1];
            v235 = *((unsigned __int16 *)v222 + 1);
            v237 = *((unsigned int *)v475 + 1);
            v478 = *((unsigned __int16 *)v475 + 1);
          }
          v238 = 5 * v226 + 5;
          for(j = (unsigned __int8 *)(v220 + v237); v221 != *j; j += 6)
            ;
          v441 = j[1];
          v240 = v235 + 2 * v238;
          v241 = (2 * (2 * v238 < v235) + 5) * v477 + v478;
          if(v241 * v234 < (int)(v240 * v441)) {
            if(v234 > 228)
              goto LABEL_164;
            v242 = v235 - v234;
            v243 = ((v240 - v234) * (v441 + 3 * v234) + 3 * (v240 - v234) + v241 - v441 - 4) / (3 * (v240 - v234) + v241 - v441);
            if(v243 > v234 + 11)
              LOWORD(v243) = v234 + 11;
            LOWORD(v235) = v243 + v242;
            *((_WORD *)v222 + 1) = v235;
            v542[1] = v243;
            v234 = (unsigned __int8)v243;
            v235 = (unsigned __int16)v235;
          }
        }
      }
    }
    if(v234 <= 9) {
      v244 = (unsigned __int8)algn_141136BC4[v234 + 1083];
      goto LABEL_166;
    }
  LABEL_164:
    v244 = v234 - 6;
  LABEL_166:
    v245 = v235 - v244;
    v246 = (6 * v245 < v244) + (15 * v245 < 4 * v244) + (9 * v245 < 4 * v244) + (13 * v245 < 8 * v244) + (v245 < v244) + (v245 < 2 * v244) + (v245 < 6 * v244) + (35 * v245 < 4 * v244) + 1;
    do {
      v247 = *--v223;
      if(v246 > *(unsigned __int8 *)(*v223 + 1))
        *(_BYTE *)(v247 + 1) = v246;
      else
        v246 = *(unsigned __int8 *)(*v223 + 1);
    } while(v223 != qword_14025F220);
    v547 = v247;
    dword_141133684 = v246 - ((6 * v245 < v244) + (15 * v245 < 4 * v244) + (9 * v245 < 4 * v244) + (13 * v245 < 8 * v244) + (v245 < v244) + (v245 < 2 * v244) + (v245 < 6 * v244) + (35 * v245 < 4 * v244) + 1);
    dword_14025F20C = 1 << v221;
    dword_14025F200 = (unsigned int)(v221 + dword_14025F1FC) >> 5;
    dword_14025F208 = (unsigned int)(v221 + dword_14025F204) >> 5;
    v549 = (((1 << v221) & dword_14020F1FC[(unsigned int)(v221 + dword_14025F1FC) >> 5]) != 0) + 2 * (((1 << v221) & dword_14021F1FC[(unsigned int)(v221 + dword_14025F204) >> 5]) != 0);
    v248 = dword_1401CF1FC[v221 + (dword_14014ADB0 << 8)];
    if((unsigned int)(dword_141133688 - v248) >= 0x20000) {
      dword_14014ADF0 = 0x20000;
      dword_14014ADEC = 0x20000;
      dword_14014ADE8 = 0x20000;
    } else {
      dword_14014ADEC = dword_1401CF1FC[v221 + (dword_14014ADB0 << 8)];
      dword_14014ADE8 = (unsigned __int8)byte_14002A158[(v248 + 2) & 0x1FFFF];
      dword_14014ADEC = dword_141133688 - v248;
      dword_14014ADF0 = dword_141133688 - dword_1401CF1FC[dword_14014ADE8 + (v221 << 8)];
    }
    v249 = *((unsigned int *)v3 + 2);
    v250 = *(unsigned __int8 *)(v249 + v220);
    v251 = 32 * (dword_141133660 > 0) + (v3[1] & 0x80);
    dword_14113368C += (v250 == 0) << 7;
    v548 = dword_141133690 - v545;
    v252 = dword_141133694 + ((4 * (dword_141133690 - v545 > 3) + 8 * (v221 == v543) + (v221 == dword_14014AD70) + 2 * (v2 == dword_14010A158[v221])) << 9) + v251 + ((v549 == 3 || v2 == dword_14010A958[v221]) << 13);
    v253 = (((dword_141133698 & 6) == 6) << 8) + ((dword_141133698 & 1) << 6);
    v254 = v252 + v253;
    if(v250) {
      v255 = v254 & 0xFFFFFFDE;
      v256 = v246 != (6 * v245 < v244) + (15 * v245 < 4 * v244) + (9 * v245 < 4 * v244) + (13 * v245 < 8 * v244) + (v245 < v244) + (v245 < 2 * v244) + (v245 < 6 * v244) + (35 * v245 < 4 * v244) + 1 || v245 <= 10 * v244;
      v257 = 32 * v256 + v255 + (v221 == dword_14113369C);
    } else {
      v258 = *(unsigned int *)(v249 + v220 + 8);
      v250 = *(unsigned __int8 *)(v258 + v220);
      if(*(_BYTE *)(v258 + v220) || v548 < 4 || v548 < 5 && v544 < 4 && *((unsigned __int16 *)v222 + 1) - v542[1] < 36) {
        v259 = *(_DWORD *)(v258 + v220 + 8);
        if(v259)
          v260 = 2 * v250 < *(unsigned __int8 *)(v259 + v220);
        else
          v260 = 0;
        v257 = v254 + 8 * v260 + 16;
      } else if(v546 >= 6) {
        if(v546 >= 0xE) {
          v257 = v252 + v253 + 14;
          if(v546 < 0x20)
            v257 = v252 + v253 + 12;
        } else {
          v257 = v252 + v253 + 10;
        }
      } else {
        v257 = v252 + v253 + 8;
      }
    }
    v261 = v257 + (unsigned int)*((unsigned __int8 *)xmmword_140029100 + v250);
    v262 = &dword_14025FA20[0x8000 * (unsigned __int64)(unsigned __int8)byte_140029240[v246]];
    qword_141133590 = (__int64)&v262[2 * (v261 ^ 0x1000)];
    qword_141133598 = (__int64)&v262[2 * (v261 ^ 1)];
    qword_1411335A0 = (__int64)&v262[2 * (v261 ^ 0x2000)];
    qword_1411335A8 = (__int64)&v262[2 * (v261 ^ 0x20)];
    qword_1411335B0 = (__int64)&v262[2 * (v261 ^ 0x200)];
    v263 = (__int64)&v262[2 * (v261 ^ 0x400)];
    v264 = &v262[2 * v261];
    v265 = *((unsigned __int16 *)v264 + 2);
    qword_1411335B8 = v263;
    qword_1411335C0 = (__int64)v264;
    qword_1411335C8 = (__int64)(v264 - 4);
    qword_1411335D0 = (__int64)(v264 + 4);
    if(v265 > 0x8000) {
      sub_140010850(v264);
      v265 = *((unsigned __int16 *)v264 + 2);
    }
    v266 = *(unsigned __int16 *)v264;
    v267 = *((_WORD *)v264 + 3);
    dword_141133680 = v266;
    *((_WORD *)v264 + 2) = v265 + v267;
    dword_14113367C = v265;
    dword_14014AD98 = v266;
    dword_14014AD9C = v265;
    v268 = (v221 & 0xE0) + 16 * (v221 == dword_14014ADD0) + 8 * (v221 == dword_14014ADCC) + 4 * (v221 == dword_14014AD8C) + (v221 == dword_14014AD80) + (dword_1411336A0 & 0xE200) + 2 * (v221 == dword_14014AD88);
    v269 = (((_WORD)v221 - (_WORD)dword_14014ADB0) & 0x800) + (((_WORD)dword_14014ADB4 - (_WORD)v221) & 0x400) + ((v221 == dword_14014ADDC) << 8);
    v270 = v549;
    v271 = v269 + v268;
    if(v549)
      v270 = 1;
    dword_1411336A0 = (v270 << 12) + v271 + (((v265 < (unsigned int)(56 * v266)) + (v265 < (unsigned int)(6 * v266))) << 16);
    v272 = &dword_14045FB20[2 * dword_1411336A0];
    v273 = *v272;
    qword_1411335D8 = (__int64)v272;
    v274 = v266 * (__int64)v273 / v272[1];
    v275 = dword_141133680;
    v276 = 1 - dword_141133680;
    if(v274 >= 1 - dword_141133680) {
      v276 = 0x40000;
      if(v274 < 0x40000)
        v276 = v274;
    }
    v277 = *v272;
    v278 = v272[1];
    if((int)abs32(*v272) > 0x40000) {
      v277 >>= 1;
      *v272 = v277;
      v278 >>= v278 > 4096;
    }
    v279 = v277 - v275;
    *v272 = v279;
    v280 = v275 + v278 + 2;
    if(v280 > 0x40000000) {
      *v272 = v279 >> 1;
      v280 >>= 1;
    }
    v272[1] = v280;
    v281 = v276 + dword_14113367C;
    v282 = v276 + v275;
    v283 = (unsigned __int16 *)qword_1411335C0;
    v284 = *(unsigned __int16 *)(qword_1411335C0 + 6);
    if(v284 <= 0x20) {
      v285 = dword_141133674;
      dword_14113367C = v281;
      dword_141133680 = v282;
      qword_1411335B8 = (__int64)&dword_1405DFC20;
      qword_1411335B0 = (__int64)&dword_1405DFC20;
      qword_1411335A8 = (__int64)&dword_1405DFC20;
      qword_1411335A0 = (__int64)&dword_1405DFC20;
      qword_141133598 = (__int64)&dword_1405DFC20;
      qword_141133590 = (__int64)&dword_1405DFC20;
      qword_1411335D0 = (__int64)&dword_1405DFC20;
      qword_1411335C8 = (__int64)&dword_1405DFC20;
      qword_1411335E0 = (__int64)&dword_1405DFC20;
      qword_1411335E8 = (__int64)&dword_1405DFC20;
      qword_1411335F0 = (__int64)&dword_1411336A4;
    } else {
      v285 = dword_141133674;
      v286 = &dword_14079FD20[128 * (unsigned __int64)(unsigned __int8)byte_1400293C0[v246] + 64 * (dword_141133660 > -9) + 4 * (unsigned int)(dword_14010A558[dword_141133674] == dword_141133664) + (((unsigned int)v261 >> 6) & 0xBLL) + (unsigned int)(16 * v549)];
      v287 = *v286;
      qword_1411335F0 = (__int64)v286;
      v288 = (v287 >> (v284 < 0x230)) + v282;
      dword_141133680 = v288;
      v289 = (0x3100u >> (v284 < 0x230)) + v281;
      dword_14113367C = v289;
      *v286 = v287 - ((v287 + 2) >> 3);
      v290 = qword_1411335C8;
      v103 = v284 < 0x220;
      v291 = *(_WORD *)(qword_1411335C8 + 4);
      v292 = v103;
      if(v291 > 0x8000u) {
        v438 = qword_1411335C8;
        v435 = v283;
        sub_140010850(qword_1411335C8);
        v283 = v435;
        v290 = v438;
        v291 = *(_WORD *)(v438 + 4);
      }
      dword_1411336A8 = *(unsigned __int16 *)(v290 + 6) >> v292;
      *(_WORD *)(v290 + 4) = dword_1411336A8 + v291;
      v293 = qword_1411335D0;
      v294 = *(_WORD *)(qword_1411335D0 + 4);
      if(v294 > 0x8000u) {
        v437 = qword_1411335D0;
        v434 = v283;
        sub_140010850(qword_1411335D0);
        v283 = v434;
        v293 = v437;
        v294 = *(_WORD *)(v437 + 4);
      }
      dword_1411336AC = *(unsigned __int16 *)(v293 + 6) >> v292;
      v295 = v283 - 0x10000;
      qword_1411335E0 = (__int64)(v283 - 0x10000);
      *(_WORD *)(v293 + 4) = dword_1411336AC + v294;
      v296 = *(v283 - 0x10000);
      v297 = v283[0x10000];
      v298 = *(v283 - 65534);
      qword_1411335E8 = (__int64)(v283 + 0x10000);
      v299 = v297 + v296;
      v300 = v283[65538];
      v282 = (v299 >> (v292 + 1)) + v288;
      dword_141133680 = v282;
      v281 = ((unsigned int)(v300 + v298) >> (v292 + 1)) + v289;
      dword_14113367C = v281;
      if(v300 > 0x8000) {
        v436 = v283 - 0x10000;
        v433 = v283;
        sub_140010850(v283 + 0x10000);
        v283 = v433;
        v295 = v436;
        LOWORD(v300) = v433[65538];
      }
      dword_1411336B0 = v283[65539] >> v292;
      v283[65538] = dword_1411336B0 + v300;
      v301 = *(v283 - 65534);
      if(v301 > 0x8000u) {
        v432 = v283;
        sub_140010850(v295);
        v283 = v432;
        v301 = *(v432 - 65534);
      }
      v302 = qword_141133590;
      dword_1411336B4 = *(v283 - 65533) >> v292;
      *(v283 - 65534) = dword_1411336B4 + v301;
      v303 = *(_WORD *)(v302 + 4);
      v304 = (v283[3] < 0x398u) + v292;
      if(v303 > 0x8000u) {
        sub_140010850(v302);
        v303 = *(_WORD *)(v302 + 4);
      }
      dword_1411336B8 = *(unsigned __int16 *)(v302 + 6) >> v304;
      *(_WORD *)(v302 + 4) = dword_1411336B8 + v303;
      v305 = qword_141133598;
      v306 = *(_WORD *)(qword_141133598 + 4);
      if(v306 > 0x8000u) {
        sub_140010850(qword_141133598);
        v306 = *(_WORD *)(v305 + 4);
      }
      dword_1411336BC = *(unsigned __int16 *)(v305 + 6) >> v304;
      *(_WORD *)(v305 + 4) = dword_1411336BC + v306;
      v307 = qword_1411335A0;
      v308 = *(_WORD *)(qword_1411335A0 + 4);
      if(v308 > 0x8000u) {
        sub_140010850(qword_1411335A0);
        v308 = *(_WORD *)(v307 + 4);
      }
      dword_1411336C0 = *(unsigned __int16 *)(v307 + 6) >> v304;
      *(_WORD *)(v307 + 4) = dword_1411336C0 + v308;
      v309 = qword_1411335A8;
      v310 = *(_WORD *)(qword_1411335A8 + 4);
      if(v310 > 0x8000u) {
        sub_140010850(qword_1411335A8);
        v310 = *(_WORD *)(v309 + 4);
      }
      dword_1411336C4 = *(unsigned __int16 *)(v309 + 6) >> v304;
      *(_WORD *)(v309 + 4) = dword_1411336C4 + v310;
      v311 = qword_1411335B0;
      v312 = *(_WORD *)(qword_1411335B0 + 4);
      if(v312 > 0x8000u) {
        sub_140010850(qword_1411335B0);
        v312 = *(_WORD *)(v311 + 4);
      }
      dword_1411336C8 = *(unsigned __int16 *)(v311 + 6) >> v304;
      *(_WORD *)(v311 + 4) = dword_1411336C8 + v312;
      v313 = qword_1411335B8;
      v314 = *(_WORD *)(qword_1411335B8 + 4);
      if(v314 > 0x8000u) {
        sub_140010850(qword_1411335B8);
        v314 = *(_WORD *)(v313 + 4);
      }
      dword_1411336CC = *(unsigned __int16 *)(v313 + 6) >> v304;
      *(_WORD *)(v313 + 4) = dword_1411336CC + v314;
    }
    dword_141133680 = 60416LL * v282 / v281;
    dword_14113367C = 60416;
    dword_14014ADA0 = dword_141133680;
    dword_14014ADA4 = 60416;
    v315 = &dword_1407A0720[0x100000 * (dword_14014AD68 < (unsigned int)dword_14014ADB8) + 0x80000 * (v285 == dword_14014AD70) + 0x20000 * dword_141133694 + 512 * dword_14014ADB4 + 2 * v285 + 2 * (unsigned __int64)((unsigned __int8)((unsigned int)dword_14014ADEC < 0x78) << 17)];
    v316 = *v315;
    qword_1411335F8 = (__int64)v315;
    v317 = dword_141133680 * (__int64)v316 / v315[1];
    v318 = dword_141133680;
    v319 = 1 - dword_141133680;
    if(v317 >= 1 - dword_141133680) {
      v319 = 0x40000;
      if(v317 < 0x40000)
        v319 = (int)(60416LL * v282 / v281) * (__int64)v316 / v315[1];
    }
    v320 = *v315;
    if((int)abs32(*v315) > 0x80000) {
      v321 = v315[1];
      v320 >>= 1;
      *v315 = v320;
      v315[1] = v321 >> (v321 > 0x2000);
    }
    v322 = v315[1];
    v323 = v320 - v318;
    *v315 = v323;
    v324 = v318 + v322 + 1120;
    v315[1] = v324;
    if(v324 > 0x40000000) {
      *v315 = v323 >> 1;
      v315[1] = v324 >> 1;
    }
    dword_14113367C += v319;
    dword_14014ADA8 = dword_14113367C;
    v325 = v319 + v318;
    dword_141133680 = v325;
    v326 = ((17 * v325 < (unsigned int)dword_14113367C) << 13) + (((unsigned __int16)dword_14014ADE8 - (unsigned __int16)v285) & 0x1000) + 16 * (v285 == dword_14113369C) + 8 * (v285 == dword_14014AD70) + 4 * (v285 == dword_14014AD94) + (v285 == dword_14014AD84) + (((unsigned int)dword_14014ADF0 < 0x29) << 7) + dword_1411336D0 + (dword_1411336A0 & 0x800) + 2 * (*((unsigned __int8 *)xmmword_140028F00 + v285) + (v285 == dword_14014AD90)) + 32 * (((unsigned int)dword_14014ADEC < 0xA800) + ((unsigned int)dword_14014ADEC < 0x600) + ((unsigned int)dword_14014ADEC < 0xD));
    v327 = &dword_140FA0820[2 * v326];
    v328 = *v327;
    qword_141133600 = (__int64)v327;
    v329 = (dword_14113367C - v325) * (__int64)v328 / dword_140FA0824[2 * v326];
    v330 = v325;
    v331 = v325 - dword_14113367C + 1;
    if(v329 >= v331) {
      v331 = 0x40000;
      if(v329 < 0x40000)
        v331 = (dword_14113367C - v325) * (__int64)v328 / dword_140FA0824[2 * v326];
    }
    v332 = *v327;
    v333 = v331 + dword_14113367C;
    dword_14113367C += v331;
    v334 = dword_140FA0824[2 * v326];
    if((int)abs32(v332) > 0x100000) {
      v332 >>= 1;
      *v327 = v332;
      v334 >>= v334 > 0x2000;
    }
    *v327 = v332 + 2 * v325;
    v335 = qword_14002A150;
    dword_140FA0824[2 * v326] = v334 + 1;
    v336 = qword_141133588 + *(_DWORD *)(v547 + 2) - qword_141133560;
    v337 = dword_14010A558[v285] == dword_141133664;
    v338 = *(unsigned __int8 *)(v335 + (((_WORD)v285 - (_WORD)dword_14014AD7C) & 0x1FF));
    v339 = (*(_DWORD *)(v335 + 512) < (unsigned int)(384 * v338)) + (*(_DWORD *)(v335 + 512) < (unsigned int)(58 * v338)) + (*(_DWORD *)(v335 + 512) < (unsigned int)(22 * v338));
    v340 = (unsigned __int8)byte_1400EA158[dword_14014ADF8];
    dword_14014ADAC = v333;
    v341 = &dword_141060920[2 * (int)(4 * (v336 >= 0xFFFFFD20) + v337 + (v326 & 0x700) + dword_14113368C + (((unsigned int)dword_14014ADEC < 0x2C00) << 11) + 2 * (v285 == v340) + 8 * v339)];
    v342 = *v341;
    qword_141133608 = (__int64)v341;
    v343 = (v333 - v330) * (__int64)v342 / v341[1];
    v344 = dword_141133680;
    v345 = dword_141133680 - dword_14113367C + 1;
    if(v343 >= v345) {
      v345 = 0x80000;
      if(v343 < 0x80000)
        v345 = v343;
    }
    v346 = *v341;
    v347 = v345 + dword_14113367C;
    dword_14113367C += v345;
    v348 = v341[1];
    if((int)abs32(v346) > 0x100000) {
      v346 >>= 1;
      *v341 = v346;
      v348 >>= v348 > 0x2000;
    }
    v349 = dword_141133670;
    *v341 = v346 + v330;
    v341[1] = v348 + 2;
    v350 = v3[2];
    v351 = v344 * (v349 / v347);
    dword_1411336D4 = v351;
    if(v350 != v566) {
      v427 = (unsigned int)dword_14025F200;
      v170 = v349 - v351;
      v428 = ~dword_14025F20C;
      qword_141133640 += v351;
      v429 = v3[2];
      dword_141133670 = v170;
      dword_140029540[v429] = dword_141133664;
      v430 = v347 + v347 * v3[3];
      dword_14020F1FC[v427] &= v428;
      qword_141133610 = 0;
      dword_14021F1FC[dword_14025F208] &= ~dword_14025F20C;
      v195 = qword_141133588;
      v431 = v3[3];
      v23 = (unsigned __int8 *)qword_141133580;
      v201 = *(unsigned __int8 *)qword_141133580;
      dword_141133694 = 0;
      dword_1411336DC = v201;
      result = (int)(16 * (v431 * v344 + v344 - v431 * v347)) / v430;
      dword_1411336D8 = result;
      do {
      LABEL_128:
        v202 = *((_DWORD *)v23 + 2);
        if(!v202)
          return result;
        v203 = dword_141133690;
        v204 = --dword_141133690;
        v23 = (unsigned __int8 *)(v195 + v202);
        v205 = *v23;
        qword_141133580 = (__int64)v23;
        if(v205 && !*(_BYTE *)(v195 + *((unsigned int *)v23 + 1) + 6LL * (v23[1] & 0xF) + 1))
          result = sub_14000C0E0(v23);
        v206 = v205 - v201;
      } while(!v206);
      v207 = *v23;
      v208 = *((unsigned int *)v23 + 1);
      v533 = v204;
      v534 = v203;
      v209 = v207 - v201;
      v564 = v206;
      v532 = v207;
      v531 = v207 + 1;
      v210 = v209;
      v535 = v531;
      v65 = 0x8000;
      v211 = 0;
      v212 = 0;
      v213 = qword_14025F220;
      v214 = qword_14025F220;
      v215 = *(unsigned __int8 *)(v195 + v208 + 6LL * (v23[1] & 0xF));
      v538 = (unsigned __int8 *)(v195 + v208 + 6LL * (v23[1] & 0xF));
      v2 = dword_141133664;
      v567 = *v538;
      dword_141133674 = v567;
      if(dword_141133664 == dword_140029540[v215]) {
        dword_1411336C8 = 0x8000;
      } else {
        dword_140029540[v215] = dword_141133664;
        v211 = 1;
        v213 = &qword_14025F228;
        qword_14025F220[0] = (__int64)v538;
        v212 = v538[1];
        v214 = &qword_14025F228;
        v65 = 0;
        v210 = v209 - 1;
        dword_1411336C8 = 0;
      }
      v216 = (unsigned __int8 *)(v195 + v208 - 6);
      if(v210) {
        v520 = v209;
        v217 = v213;
        v521 = v195;
        v523 = v65;
        v552 = v23;
        while(1) {
          do {
            v216 += 6;
            v218 = *v216;
            v219 = *v216;
          } while(v2 == dword_140029540[v219]);
          v382 = v216[1];
          dword_140029540[v219] = v2;
          *v213++ = (__int64)v216;
          v214 = v213;
          v212 += v382;
          if(v218 == dword_14014AD70)
            break;
          if(v2 == dword_14010A958[v219] || v2 == dword_14010A558[v219]) {
            v384 = v217;
            v383 = 4 * (v2 == dword_14010A958[v219]) + 12;
            goto LABEL_292;
          }
        LABEL_296:
          if(!--v210) {
            v209 = v520;
            v195 = v521;
            v65 = v523;
            v23 = v552;
            goto LABEL_298;
          }
        }
        v383 = 22;
        v384 = &qword_14025F220[(unsigned __int8)v211 & ((byte_14014AD5C & 7) == 0)];
      LABEL_292:
        for(k = v213 - 1; k > v384; --k) {
          v386 = *(k - 1);
          if(v383 * *(unsigned __int8 *)(*k + 1) <= *(unsigned __int8 *)(v386 + 1))
            break;
          *(k - 1) = *k;
          *k = v386;
        }
        ++v217;
        goto LABEL_296;
      }
    LABEL_298:
      qword_1411335A8 = (__int64)&dword_1405DFC20;
      qword_1411335A0 = (__int64)&dword_1405DFC20;
      qword_141133598 = (__int64)&dword_1405DFC20;
      qword_141133590 = (__int64)&dword_1405DFC20;
      qword_141133618 = (__int64)&dword_1405DFC20;
      if(v531 == 256) {
        v568 = -1;
        dword_141133678 = -1;
        qword_1411335B0 = (__int64)&dword_1405DFC20;
        v422 = 1;
        v537 = dword_141133698;
        v536 = dword_1411336E0;
      } else {
        v387 = *((unsigned int *)v23 + 2);
        v501 = (unsigned __int8 *)(v195 + v387);
        v503 = *(unsigned int *)(v195 + v387 + 4);
        v568 = *(unsigned __int8 *)(v195 + v503 + 6LL * (*(_BYTE *)(v195 + v387 + 1) & 0xF));
        if(v568 == v567) {
          v388 = *(unsigned int *)(v195 + v387 + 4);
          v389 = *(unsigned __int8 *)(v195 + v388 + 6LL * (*(_BYTE *)(v195 + v387 + 1) & 0xF));
          v518 = v2;
          v390 = (unsigned __int8 *)(v195 + v387);
          do {
            if(*v390 != *v23)
              break;
            v390 = (unsigned __int8 *)(v195 + *((unsigned int *)v390 + 2));
            v388 = *((unsigned int *)v390 + 1);
            v389 = *(unsigned __int8 *)(v195 + v388 + 6LL * (v390[1] & 0xF));
          } while(v389 == v567);
          v503 = v388;
          v501 = v390;
          v2 = v518;
          v568 = v389;
          dword_141133678 = v389;
        } else {
          dword_141133678 = *(unsigned __int8 *)(v195 + *(unsigned int *)(v195 + v387 + 4) + 6LL * (*(_BYTE *)(v195 + v387 + 1) & 0xF));
        }
        v391 = v23[1];
        if(v212 >= 16 * v209 || (v23[1] & 0x40) != 0) {
          qword_141133620 = (__int64)v214;
          v502 = *((unsigned __int16 *)v23 + 1);
        } else {
          v392 = *v501 + 1;
          v393 = (unsigned __int8 *)(v195 + v503);
          v394 = v392;
          do {
            byte_141108A20[*v393] = v393[1];
            v393 += 6;
            --v394;
          } while(v394);
          v395 = *((unsigned __int16 *)v23 + 1);
          v522 = v170;
          v212 = 0;
          v524 = v65;
          v519 = v2;
          v396 = v395;
          v397 = 5 * v532 + 5;
          v398 = (5 * ((unsigned int)(2 * v397 - v395) >> 31) + 8) * v392 + *((unsigned __int16 *)v501 + 1);
          do {
            v399 = *--v213;
            v401 = *(unsigned __int8 *)(*v213 + 1);
            v402 = v396 + 2 * v397;
            LOBYTE(v403) = *(_BYTE *)(*v213 + 1);
            if((int)(v401 * v398) < v402 * (unsigned __int8)byte_141108A20[*(unsigned __int8 *)*v213] && *(unsigned __int8 *)(*v213 + 1) <= 0xE4u) {
              v404 = v395 - v401;
              v400 = (unsigned __int8)byte_141108A20[*(unsigned __int8 *)*v213];
              v403 = ((v402 - v401) * (3 * v401 + v400) + 3 * (v402 - v401) + v398 - v400 - 4) / (3 * (v402 - v401) + v398 - v400);
              if(v403 > v401 + 11)
                v403 = v401 + 11;
              v395 = v403 + v404;
              *((_WORD *)v23 + 1) = v395;
              *(_BYTE *)(v399 + 1) = v403;
              v396 = (unsigned __int16)v395;
            }
            v212 += (unsigned __int8)v403;
          } while(v213 != qword_14025F220);
          v170 = v522;
          v65 = v524;
          v391 = v23[1];
          v387 = *((unsigned int *)v23 + 2);
          v502 = v396;
          v2 = v519;
          qword_141133620 = (__int64)v213;
        }
        v405 = *(unsigned __int8 *)(v387 + v195);
        v535 = v405 + 1;
        v499 = v2 != dword_140029540[dword_14113369C];
        v496 = v2 != dword_140029540[v568];
        v537 = dword_141133698;
        v498 = 2 * v405 + 2;
        v500 = (unsigned __int8)byte_1400292BE[v531];
        v406 = (int)((((16 * (unsigned int)*v23 - v502) >> 26) & 0xFFFFFFE0) + (dword_141133698 & 3) + 8 * (v499 | (v2 != dword_140029540[*(unsigned __int8 *)(v195 + *(unsigned int *)(v387 + v195 + 4) + 6LL * (*(_BYTE *)(v387 + v195 + 1) & 0xF))])) + 4 * (v531 * v212 > v502 * v209) + (v391 & 0xC0) + 16 * (v209 >= 2 * v405 - 2 * v532));
        v497 = v406;
        v407 = (v500 << 11) + 8LL * (int)v406;
        v408 = (char *)dword_141128C20 + v407;
        v409 = *(int *)((char *)dword_141128C20 + v407);
        v410 = *(unsigned __int16 *)((char *)&word_141128C24 + v407);
        qword_1411335B0 = (__int64)dword_141128C20 + v407;
        dword_141133680 = v409;
        v504 = v410;
        dword_14113367C = v410;
        if(v410 > 0x8000 || v409 > 0x80000) {
          v446 = v406;
          v530 = v65;
          sub_140010730((char *)dword_141128C20 + v407);
          v65 = v530;
          LODWORD(v406) = v446;
          LOWORD(v410) = *((_WORD *)v408 + 2);
        }
        v411 = *((unsigned __int16 *)v408 + 3);
        *((_WORD *)v408 + 2) = v411 + v410;
        v536 = dword_1411336E0;
        if(v411 > 0x78) {
          v472 = &dword_141108B20[2048 * v500 + 16 * (unsigned int)(*v23 + v498 > dword_1411336E0) + 2 * ((unsigned __int8)v406 & 0xF3) + 2 * (unsigned int)(v496 << 9) + 2 * (unsigned int)(v499 << 8) + 2 * (unsigned __int64)(4 * (unsigned int)(v533 < 10))];
          qword_1411335A8 = (__int64)v472;
          v467 = v411 < 0x100;
          v470 = (v411 < 0x100) + 1;
          v412 = *((_DWORD *)v408 + 512);
          qword_141133618 = (__int64)(v408 + 2048);
          v413 = (v412 + *((_DWORD *)v408 - 512)) >> v470;
          qword_141133590 = (__int64)(v408 - 2048);
          v471 = v412;
          v414 = *((unsigned __int16 *)v408 - 1022);
          v409 += v413;
          v415 = *((unsigned __int16 *)v408 + 1026);
          dword_141133680 = v409;
          v504 += (unsigned int)(v415 + v414) >> v470;
          dword_14113367C = v504;
          if(v415 > 0x8000 || v471 > 0x80000) {
            v445 = v406;
            v529 = v65;
            sub_140010730(v408 + 2048);
            v65 = v529;
            LODWORD(v406) = v445;
            v415 = *((unsigned __int16 *)v408 + 1026);
          }
          v416 = *((unsigned __int16 *)v408 - 1022);
          v417 = (*((unsigned __int16 *)v408 + 1027) >> v470) + v415;
          dword_1411336EC = *((unsigned __int16 *)v408 + 1027) >> v470;
          *((_WORD *)v408 + 1026) = v417;
          if(v416 > 0x8000 || *((_DWORD *)v408 - 512) > 0x80000u) {
            v444 = v406;
            v528 = v65;
            sub_140010730(v408 - 2048);
            v65 = v528;
            LODWORD(v406) = v444;
            LOWORD(v416) = *((_WORD *)v408 - 1022);
          }
          dword_1411336B8 = *((unsigned __int16 *)v408 - 1021) >> v470;
          *((_WORD *)v408 - 1022) = dword_1411336B8 + v416;
          v469 = *((unsigned __int16 *)v408 + 3) < 0x200u;
          v418 = *((unsigned __int16 *)v472 + 2);
          if(v418 > 0x8000 || (unsigned int)*v472 > 0x80000) {
            v443 = v406;
            v527 = v65;
            sub_140010730(v472);
            v65 = v527;
            LODWORD(v406) = v443;
            LOWORD(v418) = *((_WORD *)v472 + 2);
          }
          dword_1411336C4 = *((unsigned __int16 *)v472 + 3) >> v469;
          *((_WORD *)v472 + 2) = dword_1411336C4 + v418;
          v468 = (*((unsigned __int16 *)v408 + 3) < 0x400u) + v467 + 1;
          v419 = &v408[-8 * v497];
          v420 = *(unsigned __int16 *)&v419[8 * (int)(v406 ^ 2) + 4];
          v473 = (__int64)&v419[8 * (int)(v406 ^ 2)];
          qword_141133598 = v473;
          if(v420 > 0x8000 || *(_DWORD *)v473 > 0x80000u) {
            v442 = v406;
            v526 = v65;
            sub_140010730(v473);
            v65 = v526;
            LODWORD(v406) = v442;
            LOWORD(v420) = *(_WORD *)(v473 + 4);
          }
          dword_1411336BC = *(unsigned __int16 *)(v473 + 6) >> v468;
          *(_WORD *)(v473 + 4) = dword_1411336BC + v420;
          v474 = (__int64)&v419[8 * (int)(v406 ^ 8)];
          qword_1411335A0 = v474;
          v421 = *(_WORD *)(v474 + 4);
          if(v421 > 0x8000u || *(_DWORD *)v474 > 0x80000u) {
            v525 = v65;
            sub_140010730(v474);
            v65 = v525;
            v421 = *(_WORD *)(v474 + 4);
          }
          dword_1411336C0 = *(unsigned __int16 *)(v474 + 6) >> v468;
          *(_WORD *)(v474 + 4) = dword_1411336C0 + v421;
        }
        v422 = ((v504 >> 1) + v531 * v409) / v504 + 2;
        if(v531 < 24) {
          v574 = 0;
          goto LABEL_335;
        }
      }
      v574 = (int)(v422 + *((unsigned __int16 *)v23 + 1)) >> 1;
    LABEL_335:
      dword_1411336F0 = v574;
      v62 = v212 + v422;
      dword_1411336E8 = v62;
      dword_141133660 = dword_141133708;
      dword_1411336E4 = v212 + v532 + 1;
      v66 = 0;
      v67 = qword_14025F220;
      dword_1411336CC = 0;
      qword_141133620 = (__int64)qword_14025F220;
      v423 = (v533 > 1) << 15;
      v571 = v423 + (dword_1411336A0 & 0x7FFF);
      dword_1411336A0 = v423 + (dword_1411336A0 & 0xFFFF7FFF);
      dword_1411336D0 = ((v533 > 3) << 15) + v423 + (dword_1411336D0 & 0x4600);
      v424 = v533 < 3 || dword_14113370C > v534 + 22;
      v575 = 1032 * (*((_DWORD *)v23 + 2) == 0) + 32 * (v537 & 3) + 2 * v424;
      dword_1411336F4 = v575;
      dword_14113368C = 32 * (*v23 + 28 > 2 * v536) + (((unsigned int)(v535 - v531 - 3) >> 24) & 0xFFFFFF80) + ((v533 > 2) << 13) + (((dword_14113370C > 7) + (dword_14113370C > 2) + 7 * (((unsigned int)(74 - v531) >> 31) + ((unsigned int)(2 - v531) >> 31)) + (v533 > 16)) << 12);
      while(1) {
        if(v170 < 0x1000000) {
          v374 = qword_141133640;
          v375 = dword_14113366C;
          v517 = v2;
          v376 = v66;
          v377 = v65;
          v378 = v62;
          do {
            if((v374 ^ 0xFF000000LL) <= 0xFFFFFF) {
              dword_14113366C = ++v375;
            } else {
              v370 = --a1->_cnt < 0;
              if(v370) {
                flsbuf(dword_141133668 + HIDWORD(v374), a1);
                LODWORD(v374) = qword_141133640;
                v379 = qword_141133640 >> 32;
              } else {
                v379 = v374 >> 32;
                *a1->_ptr++ = BYTE4(v374) + dword_141133668;
              }
              v380 = v379 + 255;
              if(v375) {
                do {
                  v381 = a1->_cnt - 1;
                  a1->_cnt = v381;
                  if(v381 < 0)
                    flsbuf(v380, a1);
                  else
                    *a1->_ptr++ = v380;
                  dword_14113366C = --v375;
                } while(v375);
                LODWORD(v374) = qword_141133640;
              }
              dword_141133668 = BYTE3(v374);
            }
            v374 = (unsigned int)((_DWORD)v374 << 8);
            qword_141133640 = v374;
            v170 <<= 8;
            dword_141133670 = v170;
          } while(v170 < 0x1000000);
          v2 = v517;
          v66 = v376;
          v65 = v377;
          v62 = v378;
        }
      LABEL_59:
        v68 = (unsigned __int8 *)*v67;
        v569 = v23;
        qword_141133620 = (__int64)(v67 + 1);
        v69 = (v68[1] << 8) - v66;
        qword_1411335D0 = (__int64)&dword_1405DFC20;
        qword_1411335C8 = (__int64)&dword_1405DFC20;
        qword_1411335E0 = (__int64)&dword_1405DFC20;
        qword_1411335E8 = (__int64)&dword_1405DFC20;
        v573 = v69 / v62;
        v570 = v69 / v62;
        v576 = (unsigned int)(unsigned __int8)byte_140029000[v570] + 1;
        v70 = *v68;
        dword_14025F20C = 1 << *v68;
        dword_14025F200 = ((v70 + dword_14025F1FC) >> 5) + 0x2000;
        dword_14025F208 = v65 + ((v70 + dword_14025F204) >> 5);
        v71 = v70;
        v72 = v2 == dword_14010A558[v70];
        v73 = v2 == dword_14010A958[v70];
        v572 = ((dword_14025F20C & dword_14020F1FC[((v70 + dword_14025F1FC) >> 5) + 0x2000]) != 0) + 2 * ((dword_14025F20C & dword_14021F1FC[v65 + ((v70 + dword_14025F204) >> 5)]) != 0);
        qword_141133628 = (__int64)&qword_1411336F8;
        qword_141133630 = (__int64)&qword_1411336F8;
        v74 = v2 == dword_14010A158[v70];
        v75 = v70 == dword_14014AD6C || *(_DWORD *)(qword_14002A150 + 512) < *(unsigned __int8 *)(qword_14002A150 + (((_WORD)v70 - (_WORD)dword_14014AD7C) & 0x1FF)) << 7;
        v76 = dword_14014ADB0;
        v77 = dword_1401CF1FC[256 * dword_14014ADB0 + v70];
        if((unsigned int)(dword_141133688 - v77) >= 0x20000) {
          v78 = 0x20000;
          dword_14014ADF0 = 0x20000;
          dword_14014ADEC = 0x20000;
          dword_14014ADE8 = 0x20000;
        } else {
          dword_14014ADEC = dword_1401CF1FC[256 * dword_14014ADB0 + v70];
          dword_14014ADE8 = (unsigned __int8)byte_14002A158[(v77 + 2) & 0x1FFFF];
          dword_14014ADEC = dword_141133688 - v77;
          v78 = dword_141133688 - dword_1401CF1FC[256 * v70 + dword_14014ADE8];
          dword_14014ADF0 = v78;
        }
        v79 = v575 | (((v78 < 0x220) << 12) + (v75 << 9) + ((v62 < v574) << 11) + 8 * (v70 == v568) + ((v70 == v567) << 10) + *((unsigned __int8 *)xmmword_140028F00 + v70) + (v74 << 8) + 16 * (v70 == dword_14014AD70) + 4 * (unsigned int)v73 + v72);
        v80 = (v576 << 16) + 8 * v79;
        v81 = (unsigned __int16 *)((char *)&dword_1405DFC20 + v80);
        v82 = *(unsigned __int16 *)((char *)&word_1405DFC24 + v80);
        qword_1411335C0 = (__int64)&dword_1405DFC20 + v80;
        if(v82 > 0x8000) {
          sub_140010850((char *)&dword_1405DFC20 + v80);
          v76 = dword_14014ADB0;
          v82 = v81[2];
        }
        v83 = *v81;
        v84 = v81[3];
        dword_141133680 = v83;
        v81[2] = v82 + v84;
        dword_14113367C = v82;
        dword_14014AD98 = v83;
        dword_14014AD9C = v82;
        v85 = v572;
        if(v572)
          v85 = 1;
        dword_1411336A0 = (((_WORD)v70 - v76) & 0x800) + (v85 << 12) + (v571 & 0xE200) + (((_WORD)dword_14014ADB4 - (_WORD)v70) & 0x400) + ((v70 == dword_14014ADDC) << 8) + (v70 & 0xE0) + 16 * (v70 == dword_14014ADD0) + 8 * (v70 == dword_14014ADCC) + 4 * (v70 == dword_14014AD8C) + (v70 == dword_14014AD80) + 2 * (v70 == dword_14014AD88) + (((v82 < (unsigned int)(56 * v83)) + (v82 < (unsigned int)(6 * v83))) << 16);
        v86 = &dword_14045FB20[2 * dword_1411336A0];
        v87 = *v86;
        qword_1411335D8 = (__int64)v86;
        v88 = v83 * (__int64)v87 / v86[1];
        v89 = dword_141133680;
        v90 = 1 - dword_141133680;
        if(v88 >= 1 - dword_141133680) {
          v90 = 0x40000;
          if(v88 < 0x40000)
            v90 = v88;
        }
        v91 = *v86;
        v92 = v86[1];
        if((int)abs32(*v86) > 0x40000) {
          v91 >>= 1;
          *v86 = v91;
          v92 >>= v92 > 4096;
        }
        v93 = v91 - v89;
        *v86 = v93;
        v94 = v89 + v92 + 2;
        if(v94 > 0x40000000) {
          *v86 = v93 >> 1;
          v94 >>= 1;
        }
        v86[1] = v94;
        v95 = v90 + dword_14113367C;
        v96 = v90 + v89;
        v97 = *(unsigned __int16 *)(qword_1411335C0 + 6);
        if(v97 <= 8) {
          dword_14113367C = v95;
          dword_141133680 = v96;
        } else {
          v553 = qword_1411335C0;
          v557 = *(unsigned __int16 *)(qword_1411335C0 + 6);
          v551 = v23;
          v558 = v68;
          v559 = v70;
          v560 = v70;
          v98 = &dword_141130D20[512 * (unsigned __int64)(unsigned __int8)byte_140029440[v570] + 2 * (unsigned int)(v572 << 6)];
          v99 = &v98[2 * (v79 & 0x1F)];
          v100 = v99[1];
          qword_141133630 = (__int64)v99;
          v101 = &v98[2 * (((unsigned int)v79 >> 4) & 0x1F) + 64];
          qword_141133628 = (__int64)v101;
          v102 = v97 < 0x150;
          v103 = v97 < 0x48;
          v104 = v101[1];
          v105 = v103;
          v106 = v100 * (v573 + 2);
          LODWORD(v98) = v104 * (v573 + 2);
          v107 = v104 + v100;
          v108 = *v101;
          v109 = v106 >> 8;
          v110 = (unsigned int)v98 >> 8;
          v111 = (v107 >> 11) & 0xFFFFFFFE;
          v103 = v107 < 0xC000;
          v112 = *v99;
          if(!v103)
            v111 = 24;
          v113 = v109 + v110;
          v114 = (unsigned __int8)byte_140022930[v111];
          v115 = (unsigned __int8)byte_140022931[v111];
          if(v109 + v110 >= 0x6000)
            v113 = 24576;
          v116 = ((unsigned int)(v114 * v113 + v115 * (*v101 + *v99)) >> (v102 + 7)) + v96;
          v117 = v102 + v105 + 3;
          v118 = ((unsigned int)(192 * (v114 + v115)) >> v102) + v95;
          dword_141133700 = 0x3000u >> v117;
          v119 = v102 + 4;
          dword_141133704 = 0x3000u >> v119;
          v70 = v559;
          *v99 = v112 - (v112 >> v117);
          v23 = v551;
          v99[1] -= (v109 + 7) >> v119;
          *v101 = v108 - (v108 >> v117);
          v120 = (v110 + 7) >> v119;
          v121 = (unsigned __int16 *)v553;
          v122 = v553 - 0x10000;
          v101[1] -= v120;
          v68 = v558;
          v123 = *(unsigned __int16 *)(v553 - 0x10000);
          v124 = *(unsigned __int16 *)(v553 - 0x10000 + 4);
          v125 = v553 + 0x10000;
          v126 = *(unsigned __int16 *)(v553 + 0x10000);
          qword_1411335E8 = v553 + 0x10000;
          v127 = v123 + v126;
          v128 = *(unsigned __int16 *)(v553 + 65540);
          qword_1411335E0 = v553 - 0x10000;
          v96 = (v127 >> 3) + v116;
          dword_141133680 = v96;
          v95 = ((unsigned int)(v128 + v124) >> 3) + v118;
          v71 = v560;
          v129 = (v557 < 0x30) + 1;
          dword_14113367C = v95;
          if(v128 > 0x8000) {
            v450 = v95;
            sub_140010850(v553 + 0x10000);
            v95 = v450;
            v121 = (unsigned __int16 *)v553;
            v122 = v553 - 0x10000;
            v129 = (v557 < 0x30) + 1;
            v125 = v553 + 0x10000;
            LOWORD(v128) = *(_WORD *)(v553 + 65540);
          }
          dword_1411336B0 = *(unsigned __int16 *)(v125 + 6) >> v129;
          *(_WORD *)(v125 + 4) = dword_1411336B0 + v128;
          v130 = *(_WORD *)(v122 + 4);
          if(v130 > 0x8000u) {
            v451 = v129;
            v452 = v122;
            v556 = v121;
            v449 = v95;
            sub_140010850(v122);
            v95 = v449;
            v121 = v556;
            v122 = v452;
            v129 = v451;
            v130 = *(_WORD *)(v452 + 4);
          }
          dword_1411336B4 = *(unsigned __int16 *)(v122 + 6) >> v129;
          *(_WORD *)(v122 + 4) = dword_1411336B4 + v130;
          v131 = v121[3];
          if(v131 > 0x48) {
            qword_1411335C8 = (__int64)(v121 + 0x10000);
            v132 = (v131 < 0x1E0) + (v131 < 0x3D0) + 1;
            v133 = v121[65538];
            if(v133 > 0x8000u) {
              v440 = v132;
              v555 = v121;
              v448 = v95;
              sub_140010850(v121 + 0x10000);
              v95 = v448;
              v121 = v555;
              v132 = v440;
              v133 = v555[65538];
            }
            dword_1411336A8 = v121[65539] >> v132;
            qword_1411335D0 = (__int64)(v121 - 0x10000);
            v121[65538] = dword_1411336A8 + v133;
            v134 = *(v121 - 65534);
            if(v134 > 0x8000u) {
              v439 = v132;
              v554 = v121;
              v447 = v95;
              sub_140010850(v121 - 0x10000);
              v95 = v447;
              v121 = v554;
              v132 = v439;
              v134 = *(v554 - 65534);
            }
            dword_1411336AC = *(v121 - 65533) >> v132;
            *(v121 - 65534) = dword_1411336AC + v134;
          }
        }
        dword_141133680 = 60416LL * v96 / v95;
        dword_14113367C = 60416;
        dword_14014ADA0 = dword_141133680;
        dword_14014ADA4 = 60416;
        v135 = &dword_1407A0720[0x100000 * (dword_14014AD68 < (unsigned int)dword_14014ADB8) + 0x80000 * (v70 == dword_14014AD70) + 0x20000 * dword_141133694 + 512 * dword_14014ADB4 + 2 * v71 + 2 * (unsigned __int64)((unsigned __int8)((unsigned int)dword_14014ADEC < 0x78) << 17)];
        v136 = *v135;
        qword_1411335F8 = (__int64)v135;
        v137 = dword_141133680 * (__int64)v136 / v135[1];
        v138 = dword_141133680;
        v139 = 1 - dword_141133680;
        if(v137 >= 1 - dword_141133680) {
          v139 = 0x40000;
          if(v137 < 0x40000)
            v139 = dword_141133680 * (__int64)v136 / v135[1];
        }
        v140 = *v135;
        if((int)abs32(*v135) > 0x80000) {
          v141 = v135[1];
          v140 >>= 1;
          *v135 = v140;
          v135[1] = v141 >> (v141 > 0x2000);
        }
        v142 = v135[1];
        v143 = v140 - v138;
        *v135 = v143;
        v144 = v138 + v142 + 1120;
        v135[1] = v144;
        if(v144 > 0x40000000) {
          *v135 = v143 >> 1;
          v135[1] = v144 >> 1;
        }
        v145 = *((unsigned __int8 *)xmmword_140028F00 + v71);
        dword_14113367C += v139;
        v146 = v139 + v138;
        dword_141133680 = v146;
        dword_14014ADA8 = dword_14113367C;
        v147 = ((17 * v146 < (unsigned int)dword_14113367C) << 13) + (((unsigned __int16)dword_14014ADE8 - (unsigned __int16)v70) & 0x1000) + 16 * (v70 == dword_14113369C) + 8 * (v70 == dword_14014AD70) + 4 * (v70 == dword_14014AD94) + (v70 == dword_14014AD84) + (((unsigned int)dword_14014ADF0 < 0x29) << 7) + dword_1411336D0 + (dword_1411336A0 & 0x800) + 2 * (v145 + (v70 == dword_14014AD90)) + 32 * (((unsigned int)dword_14014ADEC < 0xA800) + ((unsigned int)dword_14014ADEC < 0x600) + ((unsigned int)dword_14014ADEC < 0xD));
        v148 = &dword_140FA0820[2 * v147];
        v149 = *v148;
        qword_141133600 = (__int64)v148;
        v150 = (dword_14113367C - v146) * (__int64)v149 / dword_140FA0824[2 * v147];
        v151 = v146;
        v152 = v146 - dword_14113367C + 1;
        if(v150 >= v152) {
          v152 = 0x40000;
          if(v150 < 0x40000)
            v152 = (dword_14113367C - v146) * (__int64)v149 / dword_140FA0824[2 * v147];
        }
        v153 = *v148;
        v154 = v152 + dword_14113367C;
        dword_14113367C += v152;
        v155 = dword_140FA0824[2 * v147];
        if((int)abs32(v153) > 0x100000) {
          v153 >>= 1;
          *v148 = v153;
          v155 >>= v155 > 0x2000;
        }
        v73 = dword_14010A558[v71] == dword_141133664;
        v156 = qword_14002A150;
        *v148 = v153 + 2 * v146;
        dword_140FA0824[2 * v147] = v155 + 1;
        v157 = *(unsigned __int8 *)(v156 + (((_WORD)v70 - (_WORD)dword_14014AD7C) & 0x1FF));
        v158 = qword_141133588 + *(_DWORD *)(v68 + 2) - qword_141133560 + 736;
        v159 = (*(_DWORD *)(v156 + 512) < (unsigned int)(384 * v157)) + (*(_DWORD *)(v156 + 512) < (unsigned int)(58 * v157)) + (*(_DWORD *)(v156 + 512) < (unsigned int)(22 * v157));
        v160 = (unsigned __int8)byte_1400EA158[dword_14014ADF8];
        dword_14014ADAC = v154;
        v161 = (int)(4 * (v158 < 0x2E0) + v73 + (v147 & 0x700) + dword_14113368C + (((unsigned int)dword_14014ADEC < 0x2C00) << 11) + 2 * (v70 == v160) + 8 * v159);
        v162 = &dword_141060920[2 * v161];
        v163 = *v162;
        qword_141133608 = (__int64)v162;
        v164 = (v154 - v151) * (__int64)v163 / dword_141060924[2 * v161];
        v165 = dword_141133680;
        v166 = dword_141133680 - dword_14113367C + 1;
        if(v164 >= v166) {
          v166 = 0x80000;
          if(v164 < 0x80000)
            v166 = v164;
        }
        v167 = *v162;
        v168 = v166 + dword_14113367C;
        dword_14113367C += v166;
        v169 = v162[1];
        if((int)abs32(v167) > 0x100000) {
          v167 >>= 1;
          *v162 = v167;
          v169 >>= v169 > 0x2000;
        }
        v170 = dword_141133670;
        *v162 = v167 + v151;
        v162[1] = v169 + 2;
        v171 = *v68;
        v172 = v165 * (v170 / v168);
        dword_1411336D4 = v172;
        if(v171 == v566) {
          v173 = qword_141133630;
          v174 = dword_141133700;
          v175 = dword_141133704;
          v176 = (_DWORD *)qword_141133628;
          v177 = dword_14014ADEC;
          *(_DWORD *)qword_141133630 += dword_141133700;
          *(_DWORD *)(v173 + 4) += v175;
          v178 = v23[1];
          *v176 += v174;
          v176[1] += v175;
          v179 = (v178 & 0x40) == 0 || v177 > 0xE00;
          v180 = (v177 > 0x4800) + (v177 > 0x380) + (v177 > 0x80) + v179 + 4;
          v23[1] = v178 & 0xF0;
          *((_WORD *)v23 + 1) += v180;
          v68[1] += v180;
          v181 = qword_141133588 + *((unsigned int *)v23 + 1);
          if(v68 == (unsigned __int8 *)v181) {
            v23 = (unsigned __int8 *)qword_141133580;
            if(qword_141133580 == qword_141133638)
              dword_141133694 = v168 < 2 * v165;
          } else {
            v565 = *(_WORD *)v68;
            v182 = *(_DWORD *)(v68 + 2);
            do {
              v183 = *((_DWORD *)v68 - 1);
              *(_WORD *)v68 = *((_WORD *)v68 - 3);
              *(_DWORD *)(v68 + 2) = v183;
              v68 -= 6;
            } while((unsigned __int64)v68 > v181);
            *(_WORD *)v68 = v565;
            v23 = (unsigned __int8 *)qword_141133580;
            *(_DWORD *)(v68 + 2) = v182;
          }
          v184 = v68[1];
          qword_141133610 = (__int64)v68;
          if(v184 > 244) {
            sub_14000B750(v569);
            v68 = (unsigned __int8 *)qword_141133610;
          }
          if(v68)
            goto LABEL_250;
        } else {
          v425 = qword_141133610;
          v170 -= v172;
          qword_141133640 += v172;
          v426 = v68[1];
          dword_141133670 = v170;
          dword_1411336E8 -= v426;
          dword_14020F1FC[dword_14025F200] &= ~dword_14025F20C;
          dword_14021F1FC[dword_14025F208] &= ~dword_14025F20C;
          if(v425) {
            v23 = (unsigned __int8 *)qword_141133580;
            qword_141133610 = 0;
            dword_141133694 = 0;
          } else if((unsigned __int64)v68 <= qword_141133588 + (unsigned __int64)*((unsigned int *)v23 + 1)) {
            v23 = (unsigned __int8 *)qword_141133580;
          } else {
            v23 = (unsigned __int8 *)qword_141133580;
            dword_1411336C8 = 0x8000;
          }
        }
        if(!--v564) {
          v185 = dword_1411336E4;
          v186 = (_DWORD *)qword_1411335B0;
          v187 = qword_141133618;
          v188 = dword_1411336EC;
          v189 = *v23;
          v190 = *(unsigned __int16 *)(qword_1411335B0 + 6);
          *(_WORD *)(qword_1411335B0 + 4) -= v190;
          v191 = v185 / (v189 + 1);
          v192 = qword_141133590;
          v193 = dword_1411336B8;
          *v186 += v191 * v190;
          v194 = qword_141133598;
          *(_WORD *)(v187 + 4) -= v188;
          *(_DWORD *)v187 += v188 * v191;
          *(_WORD *)(v192 + 4) -= v193;
          *(_DWORD *)v192 += v193 * v191;
          LODWORD(v192) = dword_1411336BC;
          v195 = qword_141133588;
          *(_WORD *)(v194 + 4) -= dword_1411336BC;
          v196 = v192 * v191;
          LODWORD(v192) = dword_1411336C0;
          *(_DWORD *)v194 += v196;
          v197 = (_DWORD *)qword_1411335A0;
          v198 = v192 * v191;
          *(_WORD *)(qword_1411335A0 + 4) -= v192;
          v199 = qword_1411335A8;
          *v197 += v198;
          result = dword_1411336C4 * v191;
          *(_WORD *)(v199 + 4) -= dword_1411336C4;
          *(_DWORD *)v199 += result;
          v201 = *v23;
          dword_1411336DC = v201;
          goto LABEL_128;
        }
        v65 = dword_1411336C8;
        v66 = dword_1411336CC;
        v567 = dword_141133674;
        v2 = dword_141133664;
        v568 = dword_141133678;
        v67 = (__int64 *)qword_141133620;
        v571 = dword_1411336A0;
        v62 = dword_1411336E8;
        v574 = dword_1411336F0;
        v575 = dword_1411336F4;
      }
    }
    qword_141133610 = (__int64)(v3 + 2);
    v352 = v3[3];
    v353 = v352 == 1 && v347 < 4 * v344;
    v354 = (_DWORD *)qword_141133598;
    v355 = dword_1411336BC;
    v356 = (_DWORD *)qword_1411335A0;
    v357 = dword_1411336C0;
    v358 = (_DWORD *)qword_1411335A8;
    v359 = dword_1411336C4;
    v360 = (_DWORD *)qword_1411335B0;
    v361 = dword_1411336C8;
    dword_141133694 = 1;
    v362 = (v352 - 127 < 0) + v352 + v353;
    v363 = qword_1411335F0;
    v3[3] = v362;
    v364 = (_DWORD *)qword_141133590;
    v365 = dword_1411336B8;
    *(_DWORD *)v363 += 1568;
    LODWORD(v363) = dword_1411336CC;
    *v364 += v365;
    v366 = (_DWORD *)qword_1411335B8;
    *v354 += v355;
    *v356 += v357;
    *v358 += v359;
    *v360 += v361;
    *v366 += v363;
    v23 = (unsigned __int8 *)qword_141133580;
  LABEL_250:
    result = sub_140007B80(v23);
    v367 = dword_141133670;
    if((unsigned int)dword_141133670 < 0x1000000) {
      v368 = qword_141133640;
      v369 = dword_14113366C;
      do {
        if((v368 ^ 0xFF000000LL) <= 0xFFFFFF) {
          dword_14113366C = ++v369;
        } else {
          v370 = --a1->_cnt < 0;
          if(v370) {
            result = flsbuf(dword_141133668 + HIDWORD(v368), a1);
            LODWORD(v368) = qword_141133640;
            v371 = qword_141133640 >> 32;
          } else {
            v371 = v368 >> 32;
            *a1->_ptr++ = BYTE4(v368) + dword_141133668;
          }
          v372 = v371 + 255;
          if(v369) {
            do {
              v373 = a1->_cnt - 1;
              a1->_cnt = v373;
              if(v373 < 0)
                result = flsbuf(v372, a1);
              else
                *a1->_ptr++ = v372;
              dword_14113366C = --v369;
            } while(v369);
            LODWORD(v368) = qword_141133640;
          }
          dword_141133668 = BYTE3(v368);
        }
        v368 = (unsigned int)((_DWORD)v368 << 8);
        qword_141133640 = v368;
        v367 <<= 8;
        dword_141133670 = v367;
      } while(v367 < 0x1000000);
    }
    v2 = dword_141133664;
  } while(dword_141133664);
  return result;
}
// 140007B80: using guessed type __int64 sub_140007B80(_QWORD);
// 14000B750: using guessed type __int64 sub_14000B750(_QWORD);
// 14000C0E0: using guessed type __int64 sub_14000C0E0(_QWORD);
// 140010730: using guessed type __int64 sub_140010730(_QWORD);
// 140010850: using guessed type __int64 sub_140010850(_QWORD);
// 140028F00: using guessed type __int128 xmmword_140028F00[];
// 140029100: using guessed type __int128 xmmword_140029100[];
// 140029540: using guessed type int dword_140029540[256];
// 14002A150: using guessed type __int64 qword_14002A150;
// 14010A158: using guessed type int dword_14010A158[256];
// 14010A558: using guessed type int dword_14010A558[256];
// 14010A958: using guessed type int dword_14010A958[256];
// 14014AD5C: using guessed type char byte_14014AD5C;
// 14014AD68: using guessed type int dword_14014AD68;
// 14014AD6C: using guessed type int dword_14014AD6C;
// 14014AD70: using guessed type int dword_14014AD70;
// 14014AD7C: using guessed type int dword_14014AD7C;
// 14014AD80: using guessed type int dword_14014AD80;
// 14014AD84: using guessed type int dword_14014AD84;
// 14014AD88: using guessed type int dword_14014AD88;
// 14014AD8C: using guessed type int dword_14014AD8C;
// 14014AD90: using guessed type int dword_14014AD90;
// 14014AD94: using guessed type int dword_14014AD94;
// 14014AD98: using guessed type int dword_14014AD98;
// 14014AD9C: using guessed type int dword_14014AD9C;
// 14014ADA0: using guessed type int dword_14014ADA0;
// 14014ADA4: using guessed type int dword_14014ADA4;
// 14014ADA8: using guessed type int dword_14014ADA8;
// 14014ADAC: using guessed type int dword_14014ADAC;
// 14014ADB0: using guessed type int dword_14014ADB0;
// 14014ADB4: using guessed type int dword_14014ADB4;
// 14014ADB8: using guessed type int dword_14014ADB8;
// 14014ADCC: using guessed type int dword_14014ADCC;
// 14014ADD0: using guessed type int dword_14014ADD0;
// 14014ADDC: using guessed type int dword_14014ADDC;
// 14014ADE8: using guessed type int dword_14014ADE8;
// 14014ADEC: using guessed type int dword_14014ADEC;
// 14014ADF0: using guessed type int dword_14014ADF0;
// 14014ADF8: using guessed type int dword_14014ADF8;
// 1401CF1FC: using guessed type int dword_1401CF1FC[65536];
// 14020F1FC: using guessed type int dword_14020F1FC[16384];
// 14021F1FC: using guessed type int dword_14021F1FC[65536];
// 14025F1FC: using guessed type int dword_14025F1FC;
// 14025F200: using guessed type int dword_14025F200;
// 14025F204: using guessed type int dword_14025F204;
// 14025F208: using guessed type int dword_14025F208;
// 14025F20C: using guessed type int dword_14025F20C;
// 14025F220: using guessed type __int64 qword_14025F220[];
// 14025F228: using guessed type __int64 qword_14025F228;
// 14025FA20: using guessed type int dword_14025FA20[];
// 14045FB20: using guessed type int dword_14045FB20[];
// 1405DFC20: using guessed type int dword_1405DFC20;
// 1405DFC24: using guessed type __int16 word_1405DFC24;
// 14079FD20: using guessed type int dword_14079FD20[640];
// 1407A0720: using guessed type int dword_1407A0720[];
// 140FA0820: using guessed type int dword_140FA0820[];
// 140FA0824: using guessed type int dword_140FA0824[196671];
// 141060920: using guessed type int dword_141060920[];
// 141060924: using guessed type int dword_141060924[172095];
// 141108B20: using guessed type int dword_141108B20[];
// 141108B24: using guessed type __int16 word_141108B24[];
// 141128C20: using guessed type int dword_141128C20[];
// 141128C24: using guessed type __int16 word_141128C24;
// 141130D20: using guessed type int dword_141130D20[];
// 141133560: using guessed type __int64 qword_141133560;
// 141133580: using guessed type __int64 qword_141133580;
// 141133588: using guessed type __int64 qword_141133588;
// 141133590: using guessed type __int64 qword_141133590;
// 141133598: using guessed type __int64 qword_141133598;
// 1411335A0: using guessed type __int64 qword_1411335A0;
// 1411335A8: using guessed type __int64 qword_1411335A8;
// 1411335B0: using guessed type __int64 qword_1411335B0;
// 1411335B8: using guessed type __int64 qword_1411335B8;
// 1411335C0: using guessed type __int64 qword_1411335C0;
// 1411335C8: using guessed type __int64 qword_1411335C8;
// 1411335D0: using guessed type __int64 qword_1411335D0;
// 1411335D8: using guessed type __int64 qword_1411335D8;
// 1411335E0: using guessed type __int64 qword_1411335E0;
// 1411335E8: using guessed type __int64 qword_1411335E8;
// 1411335F0: using guessed type __int64 qword_1411335F0;
// 1411335F8: using guessed type __int64 qword_1411335F8;
// 141133600: using guessed type __int64 qword_141133600;
// 141133608: using guessed type __int64 qword_141133608;
// 141133610: using guessed type __int64 qword_141133610;
// 141133618: using guessed type __int64 qword_141133618;
// 141133620: using guessed type __int64 qword_141133620;
// 141133628: using guessed type __int64 qword_141133628;
// 141133630: using guessed type __int64 qword_141133630;
// 141133638: using guessed type __int64 qword_141133638;
// 141133640: using guessed type __int64 qword_141133640;
// 141133660: using guessed type int dword_141133660;
// 141133664: using guessed type int dword_141133664;
// 141133668: using guessed type int dword_141133668;
// 14113366C: using guessed type int dword_14113366C;
// 141133670: using guessed type int dword_141133670;
// 141133674: using guessed type int dword_141133674;
// 141133678: using guessed type int dword_141133678;
// 14113367C: using guessed type int dword_14113367C;
// 141133680: using guessed type int dword_141133680;
// 141133684: using guessed type int dword_141133684;
// 141133688: using guessed type int dword_141133688;
// 14113368C: using guessed type int dword_14113368C;
// 141133690: using guessed type int dword_141133690;
// 141133694: using guessed type int dword_141133694;
// 141133698: using guessed type int dword_141133698;
// 14113369C: using guessed type int dword_14113369C;
// 1411336A0: using guessed type int dword_1411336A0;
// 1411336A8: using guessed type int dword_1411336A8;
// 1411336AC: using guessed type int dword_1411336AC;
// 1411336B0: using guessed type int dword_1411336B0;
// 1411336B4: using guessed type int dword_1411336B4;
// 1411336B8: using guessed type int dword_1411336B8;
// 1411336BC: using guessed type int dword_1411336BC;
// 1411336C0: using guessed type int dword_1411336C0;
// 1411336C4: using guessed type int dword_1411336C4;
// 1411336C8: using guessed type int dword_1411336C8;
// 1411336CC: using guessed type int dword_1411336CC;
// 1411336D0: using guessed type int dword_1411336D0;
// 1411336D4: using guessed type int dword_1411336D4;
// 1411336D8: using guessed type int dword_1411336D8;
// 1411336DC: using guessed type int dword_1411336DC;
// 1411336E0: using guessed type int dword_1411336E0;
// 1411336E4: using guessed type int dword_1411336E4;
// 1411336E8: using guessed type int dword_1411336E8;
// 1411336EC: using guessed type int dword_1411336EC;
// 1411336F0: using guessed type int dword_1411336F0;
// 1411336F4: using guessed type int dword_1411336F4;
// 141133700: using guessed type int dword_141133700;
// 141133704: using guessed type int dword_141133704;
// 141133708: using guessed type int dword_141133708;
// 14113370C: using guessed type int dword_14113370C;
// 141136BC4: using guessed type _BYTE[1084];

// ---- Cleanup --------------------------------------------------------
#undef algn_141136BC4
#undef byte_140022930
#undef byte_140022931
#undef byte_140029000
#undef byte_140029240
#undef byte_1400292BE
#undef byte_1400293C0
#undef byte_140029440
#undef byte_14002A158
#undef byte_1400DA158
#undef byte_1400EA158
#undef byte_14014AD5C
#undef byte_141108A20
#undef dword_140029540
#undef dword_14010A158
#undef dword_14010A558
#undef dword_14010A958
#undef dword_14014AD68
#undef dword_14014AD6C
#undef dword_14014AD70
#undef dword_14014AD7C
#undef dword_14014AD80
#undef dword_14014AD84
#undef dword_14014AD88
#undef dword_14014AD8C
#undef dword_14014AD90
#undef dword_14014AD94
#undef dword_14014AD98
#undef dword_14014AD9C
#undef dword_14014ADA0
#undef dword_14014ADA4
#undef dword_14014ADA8
#undef dword_14014ADAC
#undef dword_14014ADB0
#undef dword_14014ADB4
#undef dword_14014ADB8
#undef dword_14014ADCC
#undef dword_14014ADD0
#undef dword_14014ADDC
#undef dword_14014ADE8
#undef dword_14014ADEC
#undef dword_14014ADF0
#undef dword_14014ADF8
#undef dword_1401CF1FC
#undef dword_14020F1FC
#undef dword_14021F1FC
#undef dword_14025F1FC
#undef dword_14025F200
#undef dword_14025F204
#undef dword_14025F208
#undef dword_14025F20C
#undef dword_14025FA20
#undef dword_14045FB20
#undef dword_1405DFC20
#undef dword_14079FD20
#undef dword_1407A0720
#undef dword_140FA0820
#undef dword_140FA0824
#undef dword_141060920
#undef dword_141060924
#undef dword_141108B20
#undef dword_141128C20
#undef dword_141130D20
#undef dword_141133660
#undef dword_141133664
#undef dword_141133668
#undef dword_14113366C
#undef dword_141133670
#undef dword_141133674
#undef dword_141133678
#undef dword_14113367C
#undef dword_141133680
#undef dword_141133684
#undef dword_141133688
#undef dword_14113368C
#undef dword_141133690
#undef dword_141133694
#undef dword_141133698
#undef dword_14113369C
#undef dword_1411336A0
#undef dword_1411336A4
#undef dword_1411336A8
#undef dword_1411336AC
#undef dword_1411336B0
#undef dword_1411336B4
#undef dword_1411336B8
#undef dword_1411336BC
#undef dword_1411336C0
#undef dword_1411336C4
#undef dword_1411336C8
#undef dword_1411336CC
#undef dword_1411336D0
#undef dword_1411336D4
#undef dword_1411336D8
#undef dword_1411336DC
#undef dword_1411336E0
#undef dword_1411336E4
#undef dword_1411336E8
#undef dword_1411336EC
#undef dword_1411336F0
#undef dword_1411336F4
#undef dword_141133700
#undef dword_141133704
#undef dword_141133708
#undef dword_14113370C
#undef qword_14002A150
#undef qword_14025F220
#undef qword_14025F228
#undef qword_141133560
#undef qword_141133580
#undef qword_141133588
#undef qword_141133590
#undef qword_141133598
#undef qword_1411335A0
#undef qword_1411335A8
#undef qword_1411335B0
#undef qword_1411335B8
#undef qword_1411335C0
#undef qword_1411335C8
#undef qword_1411335D0
#undef qword_1411335D8
#undef qword_1411335E0
#undef qword_1411335E8
#undef qword_1411335F0
#undef qword_1411335F8
#undef qword_141133600
#undef qword_141133608
#undef qword_141133610
#undef qword_141133618
#undef qword_141133620
#undef qword_141133628
#undef qword_141133630
#undef qword_141133638
#undef qword_141133640
#undef qword_1411336F8
#undef word_1405DFC24
#undef word_141108B24
#undef word_141128C24
#undef xmmword_140028F00
#undef xmmword_140029100
#undef filbuf
#undef flsbuf
#undef sub_140007B80
#undef sub_14000B750
#undef sub_14000C0E0
#undef sub_140010730
#undef sub_140010850
#undef _BitScanForward
#undef FILE
