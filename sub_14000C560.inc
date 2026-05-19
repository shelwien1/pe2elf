// =====================================================================
// sub_14000C560 @ 0x14000C560
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
#ifndef __PE_DECL___dword_141133710
#define __PE_DECL___dword_141133710
static int& __dword_141133710 = *(int*)0x141133710;
#endif
#define dword_141133710 __dword_141133710
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
#define sub_140007B80 __sub_140007B80
#define sub_14000B750 __sub_14000B750
#define sub_14000C0E0 __sub_14000C0E0
#define sub_140010730 __sub_140010730
#ifndef __PE_DECL___sub_140010850
#define __PE_DECL___sub_140010850
typedef __attribute__((ms_abi)) __int64 t_sub_140010850(__int64 a1);
static t_sub_140010850& __sub_140010850 = *(t_sub_140010850*)0x140010850;
#endif
#define sub_140010850 __sub_140010850

PROBE_DECL(__sub_14000C560)
__attribute__((ms_abi)) int __sub_14000C560(FILE *a1, FILE *a2) {

  PROBE_HIT(__sub_14000C560);
  int v2;                 // esi
  unsigned __int8 *v3;    // rdi
  int v4;                 // eax
  int v5;                 // ebx
  __int64 v6;             // r15
  __int64 v7;             // r11
  unsigned __int8 v8;     // dl
  int v9;                 // r10d
  __int64 *v10;           // rcx
  __int64 v11;            // rdx
  __int64 *v12;           // r8
  unsigned __int8 *v13;   // rdx
  int v14;                // ebx
  int v15;                // eax
  __int64 *v16;           // rbp
  __int64 *i;             // rbx
  __int64 v18;            // r15
  int v19;                // ebx
  int v20;                // r9d
  int v21;                // ebp
  int v22;                // r14d
  int v23;                // eax
  __int64 v24;            // r8
  int v25;                // ecx
  int v26;                // r11d
  int v27;                // edx
  unsigned __int8 v28;    // r10
  int v29;                // r10d
  int v30;                // r11d
  unsigned __int8 *v31;   // rdx
  unsigned __int8 *v32;   // r8
  int v33;                // r11d
  int v34;                // eax
  int v35;                // esi
  int v36;                // edx
  int v37;                // ebp
  int v38;                // r10d
  unsigned int v39;       // eax
  unsigned __int8 *v40;   // r8
  int v41;                // edx
  int v42;                // r9d
  int v43;                // r13d
  int v44;                // r9d
  int v45;                // r10d
  char v46;               // r15
  __int64 v47;            // rdx
  int *v48;               // rax
  int v49;                // r11d
  int v50;                // r11d
  unsigned int v51;       // r8d
  int v52;                // r8d
  unsigned int v53;       // r11d
  int v54;                // r11d
  int v55;                // r8d
  int v56;                // r10d
  int v57;                // ebx
  int v58;                // r11d
  int *v59;               // rax
  int v60;                // r8d
  __int64 v61;            // rdx
  int v62;                // r11d
  unsigned __int16 v63;   // ax
  unsigned int v64;       // eax
  unsigned int v65;       // edx
  int v66;                // eax
  int v67;                // r8d
  int v68;                // ecx
  __int64 *v69;           // r15
  unsigned int v70;       // r9d
  unsigned __int8 *v71;   // r14
  int v72;                // eax
  unsigned int v73;       // ebx
  __int64 v74;            // rax
  __int64 v75;            // r15
  bool v76;               // zf
  int v77;                // r8d
  int v78;                // esi
  __int16 v79;            // dx
  unsigned int v80;       // ecx
  __int64 v81;            // rbp
  int *v82;               // rsi
  int v83;                // ecx
  int v84;                // eax
  __int16 v85;            // r11
  int v86;                // r8d
  int *v87;               // rsi
  int v88;                // edx
  int v89;                // eax
  int v90;                // r8d
  int v91;                // r9d
  int v92;                // eax
  int v93;                // edx
  int v94;                // eax
  int v95;                // edx
  int v96;                // edx
  int v97;                // r8d
  unsigned int v98;       // r9d
  int *v99;               // r15
  int *v100;              // rax
  int v101;               // edi
  int *v102;              // rsi
  unsigned int v103;      // ebx
  char v104;              // bp
  bool v105;              // cf
  int v106;               // r9d
  bool v107;              // r12
  unsigned int v108;      // r14d
  unsigned int v109;      // edi
  unsigned int v110;      // r14d
  unsigned int v111;      // r15d
  __int64 v112;           // r9
  unsigned int v113;      // edi
  unsigned int v114;      // ecx
  int v115;               // r11d
  int v116;               // r9d
  unsigned int v117;      // r8d
  char v118;              // r13
  unsigned int v119;      // edx
  char v120;              // bp
  __int64 v121;           // r9
  int v122;               // ebp
  int v123;               // ebx
  unsigned __int16 *v124; // r10
  int v125;               // eax
  unsigned int v126;      // eax
  int v127;               // ebp
  char v128;              // al
  unsigned __int16 v129;  // r10
  unsigned int v130;      // ebp
  char v131;              // al
  unsigned __int16 v132;  // bp
  unsigned __int16 v133;  // bp
  int v134;               // eax
  int *v135;              // r8
  int v136;               // edx
  int v137;               // eax
  int v138;               // esi
  int v139;               // ebp
  int v140;               // eax
  int v141;               // edx
  int v142;               // edx
  int v143;               // eax
  int v144;               // edx
  int v145;               // r11d
  int v146;               // esi
  __int64 v147;           // r10
  int *v148;              // r8
  int v149;               // ebp
  int v150;               // eax
  int v151;               // ebp
  int v152;               // edx
  int v153;               // eax
  int v154;               // r9d
  int v155;               // edx
  __int64 v156;           // r15
  int v157;               // eax
  unsigned int v158;      // edx
  int v159;               // esi
  int v160;               // r8d
  int v161;               // esi
  int v162;               // ecx
  int *v163;              // rbx
  int v164;               // edx
  int v165;               // eax
  int v166;               // r8d
  int v167;               // edx
  int v168;               // eax
  unsigned int v169;      // esi
  int v170;               // edx
  unsigned int v171;      // ebp
  int v172;               // ebx
  unsigned int v173;      // eax
  __int64 v174;           // rdx
  int v175;               // r9d
  int v176;               // r10d
  _DWORD *v177;           // r11
  unsigned int v178;      // ecx
  unsigned __int8 v179;   // r9
  __int16 v180;           // dx
  __int16 v181;           // dx
  unsigned __int64 v182;  // rdx
  int v183;               // esi
  int v184;               // r8d
  int v185;               // edx
  unsigned int v186;      // eax
  _DWORD *v187;           // r10
  __int64 v188;           // r15
  int v189;               // r14d
  int v190;               // esi
  int v191;               // r9d
  unsigned int v192;      // eax
  int v193;               // esi
  __int64 v194;           // r8
  __int64 v195;           // r15
  _DWORD *v196;           // r8
  int v197;               // edx
  int v198;               // esi
  _DWORD *v199;           // r8
  int v200;               // edx
  __int64 v201;           // rsi
  __int64 v202;           // rax
  int v203;               // r14d
  unsigned int v204;      // edi
  int v205;               // r12d
  int v206;               // r13d
  int v207;               // esi
  int v208;               // esi
  __int64 v209;           // r9
  int v210;               // r14d
  int v211;               // r10d
  char v212;              // al
  __int64 *v213;          // rcx
  __int64 *v214;          // rdx
  __int64 v215;           // r11
  int v216;               // r11d
  unsigned __int8 *v217;  // r9
  __int64 *v218;          // r11
  int v219;               // r14d
  int v220;               // ebp
  __int64 v221;           // r15
  __int64 v222;           // r14
  int v223;               // r15d
  unsigned __int8 *v224;  // rbp
  __int64 *v225;          // r10
  unsigned __int8 *v226;  // rdx
  __int64 v227;           // rbp
  __int64 v228;           // rbx
  __int64 v229;           // rdx
  unsigned __int8 *v230;  // r9
  unsigned int v231;      // eax
  unsigned __int8 v232;   // al
  int v233;               // r9d
  unsigned __int8 *v234;  // rdx
  unsigned __int8 *v235;  // r11
  int v236;               // r9d
  unsigned int v237;      // r8d
  unsigned int v238;      // edx
  __int64 v239;           // rdx
  int v240;               // ebx
  unsigned __int8 *j;     // rdx
  unsigned int v242;      // eax
  int v243;               // edx
  __int16 v244;           // r8
  unsigned int v245;      // eax
  unsigned int v246;      // r9d
  unsigned int v247;      // r8d
  unsigned int v248;      // ebx
  __int64 v249;           // rax
  int v250;               // r10d
  __int64 v251;           // r10
  unsigned int v252;      // eax
  int v253;               // edx
  int v254;               // esi
  int v255;               // r11d
  int v256;               // ecx
  unsigned int v257;      // ecx
  BOOL v258;              // edx
  int v259;               // esi
  __int64 v260;           // r9
  unsigned int v261;      // edx
  BOOL v262;              // edx
  int v263;               // edx
  __int64 v264;           // rbp
  int *v265;              // rsi
  __int64 v266;           // rdx
  int *v267;              // rsi
  int v268;               // eax
  int v269;               // edx
  unsigned __int16 v270;  // r9
  int v271;               // r9d
  BOOL v272;              // r8d
  int v273;               // r11d
  int v274;               // r10d
  int v275;               // r15d
  int v276;               // r8d
  int *v277;              // r8
  int v278;               // esi
  int v279;               // eax
  int v280;               // r15d
  int v281;               // esi
  int v282;               // eax
  int v283;               // edx
  int v284;               // eax
  int v285;               // edx
  unsigned __int16 *v286; // r8
  unsigned int v287;      // edx
  int v288;               // r14d
  int v289;               // r15d
  int v290;               // esi
  int *v291;              // r9
  unsigned int v292;      // ebp
  int v293;               // r15d
  int v294;               // r14d
  __int64 v295;           // rbp
  unsigned __int16 v296;  // dx
  char v297;              // bl
  __int64 v298;           // rbp
  unsigned __int16 v299;  // dx
  __int64 v300;           // rax
  int v301;               // r10d
  int v302;               // ebp
  int v303;               // r11d
  unsigned int v304;      // r10d
  int v305;               // ebp
  unsigned __int16 v306;  // bp
  __int64 v307;           // rbp
  unsigned __int16 v308;  // dx
  char v309;              // bl
  __int64 v310;           // rbp
  unsigned __int16 v311;  // dx
  __int64 v312;           // rbp
  unsigned __int16 v313;  // dx
  __int64 v314;           // rbp
  unsigned __int16 v315;  // dx
  __int64 v316;           // rbp
  unsigned __int16 v317;  // dx
  __int64 v318;           // rbp
  unsigned __int16 v319;  // dx
  int *v320;              // r8
  int v321;               // edx
  int v322;               // eax
  int v323;               // ebx
  int v324;               // ebp
  int v325;               // eax
  int v326;               // edx
  int v327;               // edx
  int v328;               // eax
  int v329;               // edx
  int v330;               // ebx
  __int64 v331;           // rbp
  int *v332;              // r11
  int v333;               // r8d
  int v334;               // eax
  int v335;               // r10d
  int v336;               // edx
  int v337;               // eax
  int v338;               // r8d
  int v339;               // edx
  int v340;               // r14d
  __int16 v341;           // bx
  unsigned int v342;      // ecx
  BOOL v343;              // r9d
  int v344;               // edx
  int v345;               // ebx
  int v346;               // edx
  int *v347;              // rbx
  int v348;               // ebp
  int v349;               // eax
  int v350;               // esi
  int v351;               // edx
  int v352;               // eax
  unsigned int v353;      // r8d
  int v354;               // edx
  unsigned int v355;      // ebp
  unsigned int v356;      // eax
  int v357;               // edx
  bool v358;              // bp
  _DWORD *v359;           // rsi
  _DWORD *v360;           // r8
  _DWORD *v361;           // r10
  int v362;               // r9d
  _DWORD *v363;           // r15
  int v364;               // r11d
  unsigned __int8 v365;   // bp
  __int64 v366;           // rdx
  int v367;               // ebp
  int v368;               // edi
  _DWORD *v369;           // rbp
  int v370;               // edx
  unsigned int m;         // edi
  int v372;               // edx
  int v373;               // r12d
  int v374;               // r13d
  unsigned int v375;      // esi
  int v376;               // edx
  int v377;               // eax
  int v378;               // ebx
  int v379;               // edi
  __int64 *v380;          // rbx
  __int64 *k;             // rbp
  __int64 v382;           // r8
  __int64 v383;           // rax
  __int64 v384;           // r11
  unsigned __int8 *v385;  // r12
  int v386;               // r13d
  unsigned __int8 v387;   // r9
  int v388;               // eax
  unsigned __int8 *v389;  // r11
  int v390;               // edx
  int v391;               // r11d
  int v392;               // r10d
  int v393;               // r8d
  int v394;               // esi
  unsigned int v395;      // r9d
  __int64 v396;           // rbp
  int v397;               // edx
  int v398;               // ebx
  int v399;               // r12d
  unsigned int v400;      // eax
  int v401;               // r11d
  int v402;               // ecx
  __int64 v403;           // rax
  __int64 v404;           // r10
  char *v405;             // r14
  unsigned int v406;      // r15d
  int v407;               // r9d
  unsigned int v408;      // edx
  unsigned int v409;      // r11d
  unsigned int v410;      // r10d
  int v411;               // r11d
  int v412;               // r10d
  int v413;               // r9d
  int v414;               // r10d
  unsigned int v415;      // r10d
  char *v416;             // r14
  int v417;               // r9d
  unsigned __int16 v418;  // r9
  unsigned int v419;      // r9d
  int v420;               // r11d
  BOOL v421;              // r10d
  __int64 v422;           // r11
  __int64 v423;           // r14
  int v424;               // r11d
  __int64 v425;           // r10
  int v426;               // ecx
  int v427;               // edx
  unsigned __int16 *v429; // [rsp+20h] [rbp-4E8h]
  unsigned __int16 *v430; // [rsp+20h] [rbp-4E8h]
  unsigned __int16 *v431; // [rsp+20h] [rbp-4E8h]
  unsigned __int16 *v432; // [rsp+20h] [rbp-4E8h]
  unsigned __int16 *v433; // [rsp+28h] [rbp-4E0h]
  __int64 v434;           // [rsp+30h] [rbp-4D8h]
  __int64 v435;           // [rsp+38h] [rbp-4D0h]
  char v436;              // [rsp+40h] [rbp-4C8h]
  char v437;              // [rsp+40h] [rbp-4C8h]
  int v438;               // [rsp+48h] [rbp-4C0h]
  int v439;               // [rsp+50h] [rbp-4B8h]
  int v440;               // [rsp+50h] [rbp-4B8h]
  int v441;               // [rsp+50h] [rbp-4B8h]
  int v442;               // [rsp+50h] [rbp-4B8h]
  int v443;               // [rsp+50h] [rbp-4B8h]
  int v444;               // [rsp+58h] [rbp-4B0h]
  int v445;               // [rsp+58h] [rbp-4B0h]
  int v446;               // [rsp+58h] [rbp-4B0h]
  int v447;               // [rsp+58h] [rbp-4B0h]
  int v448;               // [rsp+60h] [rbp-4A8h]
  int v449;               // [rsp+60h] [rbp-4A8h]
  int v450;               // [rsp+60h] [rbp-4A8h]
  int v451;               // [rsp+60h] [rbp-4A8h]
  char v452;              // [rsp+68h] [rbp-4A0h]
  __int64 v453;           // [rsp+70h] [rbp-498h]
  int v454;               // [rsp+80h] [rbp-488h]
  int v455;               // [rsp+80h] [rbp-488h]
  int v456;               // [rsp+80h] [rbp-488h]
  int v457;               // [rsp+80h] [rbp-488h]
  int v458;               // [rsp+80h] [rbp-488h]
  int v459;               // [rsp+80h] [rbp-488h]
  int *v460;              // [rsp+88h] [rbp-480h]
  int *v461;              // [rsp+88h] [rbp-480h]
  int *v462;              // [rsp+88h] [rbp-480h]
  int *v463;              // [rsp+88h] [rbp-480h]
  int v464;               // [rsp+90h] [rbp-478h]
  int v465;               // [rsp+90h] [rbp-478h]
  int v466;               // [rsp+90h] [rbp-478h]
  int v467;               // [rsp+90h] [rbp-478h]
  bool v468;              // [rsp+98h] [rbp-470h]
  char v469;              // [rsp+A0h] [rbp-468h]
  char v470;              // [rsp+A8h] [rbp-460h]
  char v471;              // [rsp+B8h] [rbp-450h]
  unsigned int v472;      // [rsp+C0h] [rbp-448h]
  int *v473;              // [rsp+C8h] [rbp-440h]
  __int64 v474;           // [rsp+D0h] [rbp-438h]
  __int64 v475;           // [rsp+D8h] [rbp-430h]
  unsigned __int8 *v476;  // [rsp+E0h] [rbp-428h]
  int v477;               // [rsp+E8h] [rbp-420h]
  int v478;               // [rsp+E8h] [rbp-420h]
  int v479;               // [rsp+F0h] [rbp-418h]
  __int64 v480;           // [rsp+F8h] [rbp-410h]
  char v481;              // [rsp+100h] [rbp-408h]
  bool v482;              // [rsp+108h] [rbp-400h]
  __int64 v483;           // [rsp+110h] [rbp-3F8h]
  char v484;              // [rsp+120h] [rbp-3E8h]
  unsigned int v485;      // [rsp+128h] [rbp-3E0h]
  int *v486;              // [rsp+138h] [rbp-3D0h]
  __int64 v487;           // [rsp+140h] [rbp-3C8h]
  __int64 v488;           // [rsp+148h] [rbp-3C0h]
  int v489;               // [rsp+150h] [rbp-3B8h]
  int v490;               // [rsp+150h] [rbp-3B8h]
  int v491;               // [rsp+150h] [rbp-3B8h]
  int v492;               // [rsp+150h] [rbp-3B8h]
  int v493;               // [rsp+150h] [rbp-3B8h]
  int v494;               // [rsp+150h] [rbp-3B8h]
  __int64 *v495;          // [rsp+158h] [rbp-3B0h]
  __int64 *v496;          // [rsp+158h] [rbp-3B0h]
  unsigned __int8 *v497;  // [rsp+160h] [rbp-3A8h]
  int v498;               // [rsp+168h] [rbp-3A0h]
  __int64 v499;           // [rsp+170h] [rbp-398h]
  int v500;               // [rsp+178h] [rbp-390h]
  int v501;               // [rsp+180h] [rbp-388h]
  __int64 v502;           // [rsp+188h] [rbp-380h]
  int v503;               // [rsp+190h] [rbp-378h]
  __int64 v504;           // [rsp+198h] [rbp-370h]
  unsigned int v505;      // [rsp+1A0h] [rbp-368h]
  int v506;               // [rsp+1A8h] [rbp-360h]
  __int64 v507;           // [rsp+1B0h] [rbp-358h]
  BOOL v508;              // [rsp+1B8h] [rbp-350h]
  unsigned int v509;      // [rsp+1C0h] [rbp-348h]
  __int64 v510;           // [rsp+1C8h] [rbp-340h]
  int v511;               // [rsp+1D0h] [rbp-338h]
  __int64 v512;           // [rsp+1D8h] [rbp-330h]
  int v513;               // [rsp+1E0h] [rbp-328h]
  unsigned __int8 v514;   // [rsp+1E8h] [rbp-320h]
  unsigned int v515;      // [rsp+1F0h] [rbp-318h]
  unsigned int v516;      // [rsp+1F8h] [rbp-310h]
  int v517;               // [rsp+208h] [rbp-300h]
  int v518;               // [rsp+208h] [rbp-300h]
  int v519;               // [rsp+208h] [rbp-300h]
  int v520;               // [rsp+210h] [rbp-2F8h]
  __int64 v521;           // [rsp+218h] [rbp-2F0h]
  int v522;               // [rsp+220h] [rbp-2E8h]
  int v523;               // [rsp+220h] [rbp-2E8h]
  unsigned int v524;      // [rsp+228h] [rbp-2E0h]
  unsigned int v525;      // [rsp+228h] [rbp-2E0h]
  int v526;               // [rsp+230h] [rbp-2D8h]
  int v527;               // [rsp+230h] [rbp-2D8h]
  int v528;               // [rsp+230h] [rbp-2D8h]
  int v529;               // [rsp+230h] [rbp-2D8h]
  int v530;               // [rsp+230h] [rbp-2D8h]
  int v531;               // [rsp+230h] [rbp-2D8h]
  int v532;               // [rsp+230h] [rbp-2D8h]
  int v533;               // [rsp+230h] [rbp-2D8h]
  int v534;               // [rsp+238h] [rbp-2D0h]
  int v535;               // [rsp+240h] [rbp-2C8h]
  int v536;               // [rsp+248h] [rbp-2C0h]
  int v537;               // [rsp+250h] [rbp-2B8h]
  int v538;               // [rsp+258h] [rbp-2B0h]
  int v539;               // [rsp+260h] [rbp-2A8h]
  char v540;              // [rsp+268h] [rbp-2A0h]
  int v541;               // [rsp+270h] [rbp-298h]
  __int64 v542;           // [rsp+280h] [rbp-288h]
  unsigned __int8 *v543;  // [rsp+290h] [rbp-278h]
  int v544;               // [rsp+2A0h] [rbp-268h]
  unsigned int v545;      // [rsp+2A8h] [rbp-260h]
  __int64 v546;           // [rsp+2B0h] [rbp-258h]
  int v547;               // [rsp+2B8h] [rbp-250h]
  int v548;               // [rsp+2C0h] [rbp-248h]
  unsigned __int8 *v549;  // [rsp+2C8h] [rbp-240h]
  int v550;               // [rsp+2D0h] [rbp-238h]
  unsigned int v551;      // [rsp+2D8h] [rbp-230h]
  unsigned int v552;      // [rsp+2E0h] [rbp-228h]
  unsigned int v553;      // [rsp+2E8h] [rbp-220h]
  __int64 v554;           // [rsp+2F0h] [rbp-218h]
  unsigned int v555;      // [rsp+300h] [rbp-208h]
  int v556;               // [rsp+308h] [rbp-200h]
  unsigned __int8 *v557;  // [rsp+318h] [rbp-1F0h]
  unsigned __int8 *v558;  // [rsp+318h] [rbp-1F0h]
  unsigned __int16 *v559; // [rsp+320h] [rbp-1E8h]
  unsigned int v560;      // [rsp+328h] [rbp-1E0h]
  unsigned __int8 *v561;  // [rsp+330h] [rbp-1D8h]
  unsigned int v562;      // [rsp+338h] [rbp-1D0h]
  __int64 v563;           // [rsp+340h] [rbp-1C8h]
  int v566;               // [rsp+3D8h] [rbp-130h]
  int v567;               // [rsp+3D8h] [rbp-130h]
  __int16 v568;           // [rsp+3E0h] [rbp-128h]
  int v569;               // [rsp+3E8h] [rbp-120h]
  int v570;               // [rsp+3F0h] [rbp-118h]
  unsigned int v571;      // [rsp+3F8h] [rbp-110h]
  __int16 v572;           // [rsp+400h] [rbp-108h]
  int v573;               // [rsp+408h] [rbp-100h]
  unsigned __int8 *v574;  // [rsp+410h] [rbp-F8h]
  __int64 v575;           // [rsp+418h] [rbp-F0h]
  int v576;               // [rsp+420h] [rbp-E8h]
  int v577;               // [rsp+428h] [rbp-E0h]
  __int64 v578;           // [rsp+438h] [rbp-D0h]
  int v579;               // [rsp+440h] [rbp-C8h]
  BOOL v580;              // [rsp+448h] [rbp-C0h]

  v2 = dword_141133664;
  do {
    v3 = (unsigned __int8 *)qword_141133580;
    v4 = *(unsigned __int8 *)qword_141133580;
    v5 = v4;
    if(*(_BYTE *)qword_141133580) {
      v6 = qword_141133588;
      v7 = *(unsigned int *)(qword_141133580 + 4);
      v8 = *(_BYTE *)(qword_141133580 + 1);
      if(!*(_BYTE *)(v7 + qword_141133588 + 6LL * (v8 & 0xF) + 1)) {
        sub_14000C0E0((unsigned __int8 *)qword_141133580);
        v4 = *v3;
        v7 = *((unsigned int *)v3 + 1);
        v8 = v3[1];
      }
      v566 = v5;
      v546 = v6;
      v547 = v4;
      v545 = v4 + 1;
      v9 = v4 + 1;
      v544 = v4 + 1;
      v548 = v4 + 1;
      v10 = &qword_14025F228;
      qword_14025F220[0] = v7 + v6 + 6LL * (v8 & 0xF);
      v11 = *(unsigned __int8 *)qword_14025F220[0];
      v569 = *(unsigned __int8 *)qword_14025F220[0];
      dword_141133674 = v569;
      v12 = &qword_14025F228;
      dword_140029540[v11] = v2;
      v13 = (unsigned __int8 *)(v6 + v7 - 6);
      while(1) {
        v13 += 6;
        v14 = *v13;
        if(v569 != v14) {
          dword_140029540[*v13] = v2;
          *v10++ = (__int64)v13;
          if(v14 == dword_14014AD70) {
            v15 = 22;
            v16 = &qword_14025F220[(byte_14014AD5C & 7) == 0];
          LABEL_12:
            for(i = v10 - 1; i > v16; --i) {
              v18 = *(i - 1);
              if(v15 * *(unsigned __int8 *)(*i + 1) <= *(unsigned __int8 *)(v18 + 1))
                break;
              *(i - 1) = *i;
              *i = v18;
            }
            ++v12;
            goto LABEL_16;
          }
          if(v2 == dword_14010A958[v14] || v2 == dword_14010A558[v14]) {
            v16 = v12;
            v15 = 11 * (v2 == dword_14010A958[v14]) + 7;
            goto LABEL_12;
          }
        }
      LABEL_16:
        if(!--v9) {
          v19 = v566;
          v20 = v548;
          v21 = v544;
          v22 = v545;
          v23 = v547;
          dword_14014AD7C = *(unsigned __int8 *)qword_14025F220[0];
          dword_14010A158[(unsigned __int8)byte_1400DA158[dword_14014AD7C + (dword_14014ADD0 << 8)]] = v2;
          qword_1411335A8 = (__int64)dword_1405DFC20;
          qword_1411335A0 = (__int64)dword_1405DFC20;
          qword_141133598 = (__int64)dword_1405DFC20;
          qword_141133590 = (__int64)dword_1405DFC20;
          qword_141133618 = (__int64)dword_1405DFC20;
          if(v545 == 256) {
            v44 = dword_141133690;
            v46 = dword_141133698;
            v45 = dword_1411336E0;
            v66 = *((unsigned __int16 *)v3 + 1);
            qword_1411335B0 = (__int64)dword_1405DFC20;
            v570 = -1;
            dword_141133678 = -1;
            dword_1411336E4 = v66;
            v64 = v66 + 1;
            dword_1411336E8 = v64;
          } else {
            v24 = *((unsigned int *)v3 + 2);
            v25 = *(unsigned __int8 *)(v24 + v546);
            v26 = *((unsigned __int16 *)v3 + 1);
            v27 = *(unsigned __int16 *)(v24 + v546 + 2);
            v28 = v3[1];
            qword_141133620 = (__int64)qword_14025F220;
            v21 = v25 + 1;
            v506 = v27;
            v514 = v28;
            v29 = v26;
            if((v25 + 1) * v26 > (int)(v27 * v545) || (v480 = *((unsigned int *)v3 + 1), *(unsigned __int8 *)(v480 + v546 + 1) >= 0x6Au)) {
              v511 = v26;
              v507 = v545;
            } else if((v514 & 0x40) != 0) {
              v511 = v26;
              v507 = v545;
            } else {
              v30 = v25 + 1;
              v517 = v2;
              v31 = (unsigned __int8 *)(v546 + *(unsigned int *)(v24 + v546 + 4) - 6);
              do {
                v31 += 6;
                --v30;
                byte_141108A20[*v31] = v31[1];
              } while(v30);
              v507 = v545;
              v32 = (unsigned __int8 *)(v480 + v546 + 6LL * v545);
              v33 = 9 * v547 + 9 + 2 * v547 + 2;
              v34 = v29;
              v35 = v21 * (((unsigned int)(v33 - v29) >> 28) | 7) + v506;
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
                  *((_WORD *)v3 + 1) = v29;
                  v32[1] = v39;
                  v34 = (unsigned __int16)v29;
                }
                --v20;
              } while(v20);
              v21 = v25 + 1;
              v22 = v545;
              v2 = v517;
              v24 = *((unsigned int *)v3 + 2);
              v511 = v34;
              v23 = v547;
              v514 = v3[1];
            }
            v513 = *v3;
            v40 = (unsigned __int8 *)(v546 + v24);
            v41 = *(unsigned __int8 *)(v546 + *((unsigned int *)v40 + 1) + 6LL * (v40[1] & 0xF));
            v42 = v41;
            v570 = v41;
            if(v41 == v569) {
              v43 = *(unsigned __int8 *)(v546 + *((unsigned int *)v40 + 1) + 6LL * (v40[1] & 0xF));
              do {
                if(*v40 != *v3)
                  break;
                v40 = (unsigned __int8 *)(v546 + *((unsigned int *)v40 + 2));
                v42 = *(unsigned __int8 *)(v546 + *((unsigned int *)v40 + 1) + 6LL * (v40[1] & 0xF));
                v43 = v42;
              } while(v42 == v569);
              v570 = v43;
              dword_141133678 = v42;
            } else {
              dword_141133678 = *(unsigned __int8 *)(v546 + *((unsigned int *)v40 + 1) + 6LL * (v40[1] & 0xF));
            }
            v509 = v2 != dword_140029540[dword_14113369C];
            v508 = v2 != dword_140029540[v41];
            v44 = dword_141133690;
            v45 = dword_1411336E0;
            v46 = dword_141133698;
            v512 = (unsigned __int8)byte_1400292BE[v507];
            v47 = (int)(8 * (v513 + 2 * v25 + 2 > dword_1411336E0) + (dword_141133698 & 3) + 4 * (dword_141133690 < 10) + ((v2 != dword_140029540[v570]) << 9) + (v509 << 8) + (((unsigned int)(8 * v23 + 8 + 4 * v23 + 4 - v511) >> 26) & 0xFFFFFFE0) + (v514 & 0xC0) + (((unsigned int)(3 * v25 + 3 - (4 * v23 + 4)) >> 27) & 0xFFFFFFF0));
            v510 = v47;
            v48 = &dword_141108B20[2048 * v512 + 2 * v47];
            v49 = *v48;
            qword_1411335B0 = (__int64)v48;
            v516 = v49;
            dword_141133680 = v49;
            v50 = (unsigned __int16)word_141108B24[4096 * v512 + 4 * v47];
            v515 = v50;
            dword_14113367C = v50;
            if(v50 > 0x8000 || v516 > 0x80000) {
              v463 = &dword_141108B20[2048 * v512 + 2 * v47];
              v467 = v47;
              v494 = dword_1411336E0;
              v459 = dword_141133690;
              sub_140010730((__int64)v463);
              v44 = v459;
              v45 = v494;
              LODWORD(v47) = v467;
              v48 = v463;
              LOWORD(v50) = *((_WORD *)v463 + 2);
            }
            v51 = *((unsigned __int16 *)v48 + 3);
            *((_WORD *)v48 + 2) = v51 + v50;
            if(v51 > 0x80) {
              v489 = v45;
              v486 = &dword_141128C20[512 * v512 + 16 * (v508 | v509) + 2 * ((unsigned __int8)v47 & 0xF3)];
              qword_1411335A8 = (__int64)v486;
              v484 = v51 < 0x200;
              qword_141133618 = (__int64)(v48 + 2048);
              v52 = *(v48 - 2048);
              v483 = (__int64)(v48 - 2048);
              v53 = v48[2048];
              qword_141133590 = (__int64)(v48 - 2048);
              v485 = v53;
              v54 = ((v53 + v52) >> (v484 + 1)) + v516;
              v55 = *((unsigned __int16 *)v48 + 4098);
              v56 = *((unsigned __int16 *)v48 - 4094);
              v516 = v54;
              dword_141133680 = v54;
              v57 = ((unsigned int)(v55 + v56) >> (v484 + 1)) + v515;
              v45 = v489;
              v515 = v57;
              dword_14113367C = v57;
              v19 = v566;
              if(v55 > 0x8000 || v485 > 0x80000) {
                v462 = v48;
                v466 = v47;
                v458 = v44;
                sub_140010730((__int64)(v48 + 2048));
                v44 = v458;
                v45 = v489;
                LODWORD(v47) = v466;
                v48 = v462;
                LOWORD(v55) = *((_WORD *)v462 + 4098);
              }
              dword_1411336EC = *((unsigned __int16 *)v48 + 4099) >> v484;
              v58 = *((unsigned __int16 *)v48 - 4094);
              *((_WORD *)v48 + 4098) = dword_1411336EC + v55;
              if(v58 > 0x8000 || (unsigned int)*(v48 - 2048) > 0x80000) {
                v461 = v48;
                v465 = v47;
                v493 = v45;
                v457 = v44;
                sub_140010730(v483);
                v44 = v457;
                v45 = v493;
                LODWORD(v47) = v465;
                v48 = v461;
                LOWORD(v58) = *((_WORD *)v461 - 4094);
              }
              dword_1411336B8 = *((unsigned __int16 *)v48 - 4093) >> v484;
              *((_WORD *)v48 - 4094) = dword_1411336B8 + v58;
              v482 = *((unsigned __int16 *)v48 + 3) < 0x400u;
              v481 = v484 + v482;
              v59 = &v48[-2 * v510];
              v60 = LOWORD(v59[2 * (int)(v47 ^ 0x100) + 1]);
              v487 = (__int64)&v59[2 * (int)(v47 ^ 0x100)];
              qword_141133598 = v487;
              if(v60 > 0x8000 || *(_DWORD *)v487 > 0x80000u) {
                v460 = v59;
                v464 = v47;
                v492 = v45;
                v456 = v44;
                sub_140010730(v487);
                v44 = v456;
                v45 = v492;
                LODWORD(v47) = v464;
                v59 = v460;
                LOWORD(v60) = *(_WORD *)(v487 + 4);
              }
              dword_1411336BC = *(unsigned __int16 *)(v487 + 6) >> v481;
              *(_WORD *)(v487 + 4) = dword_1411336BC + v60;
              v61 = (__int64)&v59[2 * (int)(v47 ^ 0x200)];
              v62 = *(unsigned __int16 *)(v61 + 4);
              v488 = v61;
              qword_1411335A0 = v61;
              if(v62 > 0x8000 || *(_DWORD *)v61 > 0x80000u) {
                v491 = v45;
                v455 = v44;
                sub_140010730(v61);
                v44 = v455;
                v45 = v491;
                LOWORD(v62) = *(_WORD *)(v488 + 4);
              }
              dword_1411336C0 = *(unsigned __int16 *)(v488 + 6) >> v481;
              *(_WORD *)(v488 + 4) = dword_1411336C0 + v62;
              v63 = *((_WORD *)v486 + 2);
              if(v63 > 0x8000u || (unsigned int)*v486 > 0x80000) {
                v490 = v45;
                v454 = v44;
                sub_140010730((__int64)v486);
                v44 = v454;
                v45 = v490;
                v63 = *((_WORD *)v486 + 2);
              }
              dword_1411336C4 = *((unsigned __int16 *)v486 + 3) >> (v484 + v482 + 1);
              *((_WORD *)v486 + 2) = dword_1411336C4 + v63;
            }
            dword_1411336E4 = *((unsigned __int16 *)v3 + 1);
            v64 = dword_1411336E4 + ((v515 >> 1) + v22 * v516) / v515 + 2;
            dword_1411336E8 = v64;
            if(v22 < 24) {
              dword_1411336F0 = 0;
              v65 = 0;
            LABEL_56:
              dword_1411336CC = 171;
              v571 = v65;
              v67 = 0;
              dword_1411336C8 = 0;
              v68 = 171;
              dword_1411336F4 = 1032 * (*((_DWORD *)v3 + 2) == 0) + 32 * (v46 & 3) + 2 * (v44 < 3);
              v573 = dword_1411336F4;
              v567 = v19 + 1;
              v69 = qword_14025F220;
              dword_14113368C += (((unsigned int)(v21 - v22 - 4) >> 24) & 0xFFFFFF80) + 28672 * ((unsigned int)(40 - v22) >> 31) + 32 * (*v3 > v45) + 28672;
              v70 = v64;
              v572 = dword_1411336A0;
              goto LABEL_57;
            }
          }
          v65 = v64 >> 1;
          dword_1411336F0 = v64 >> 1;
          goto LABEL_56;
        }
      }
    }
    v222 = qword_141133588;
    v223 = *(unsigned __int8 *)(qword_141133580 + 2);
    dword_141133674 = v223;
    v224 = (unsigned __int8 *)qword_141133580;
    v225 = qword_14025F220;
    dword_14014AD7C = v223;
    dword_14010A158[(unsigned __int8)byte_1400DA158[v223 + (dword_14014ADD0 << 8)]] = v2;
    do {
      v226 = v224 + 2;
      v227 = *((unsigned int *)v224 + 2);
      *v225++ = (__int64)v226;
      v224 = (unsigned __int8 *)(v222 + v227);
      LODWORD(v228) = *v224;
    } while(!*v224);
    v229 = *((unsigned int *)v224 + 1);
    v553 = v225 - qword_14025F220;
    v552 = v553;
    v230 = (unsigned __int8 *)(v222 + v229 + 6LL * *v224);
    if(!v230[1]) {
      v231 = v225 - qword_14025F220;
      do {
        if(*v230 != v223)
          break;
        v224 = (unsigned __int8 *)(v222 + *((unsigned int *)v224 + 2));
        v229 = *((unsigned int *)v224 + 1);
        v228 = *v224;
        ++v231;
        v230 = (unsigned __int8 *)(v222 + v229 + 6 * v228);
      } while(!v230[1]);
      v552 = v231;
    }
    v232 = v224[1];
    v551 = v228 + 1;
    if(!*(_BYTE *)(v229 + v222 + 6LL * (v232 & 0xF) + 1)) {
      v495 = v225;
      sub_14000C0E0(v224);
      v225 = v495;
      v229 = *((unsigned int *)v224 + 1);
      v232 = v224[1];
    }
    v233 = *(unsigned __int8 *)(v229 + v222 + 6LL * (v232 & 0xF));
    v234 = (unsigned __int8 *)(v222 + v229);
    v550 = v233;
    dword_141133678 = v233;
    v549 = v234;
    if(v223 != *v234) {
      v235 = v234;
      do
        v235 += 6;
      while(v223 != *v235);
      v549 = v235;
    }
    v236 = v549[1];
    v237 = *((unsigned __int16 *)v224 + 1);
    if(2 * v236 + 23 > v234[7] + v234[1]) {
      v238 = *((_DWORD *)v224 + 2);
      if(v238) {
        v476 = (unsigned __int8 *)(v222 + v238);
        v479 = *((unsigned __int16 *)v476 + 1);
        v477 = *v476;
        if(v237 + v237 * v477 < v551 * (v479 + 15)) {
          v239 = *((unsigned int *)v476 + 1);
          v478 = v477 + 1;
          if(!*(_BYTE *)(v222 + v239 + 6LL * (v476[1] & 0xF) + 1)) {
            v496 = v225;
            sub_14000C0E0(v476);
            v225 = v496;
            v236 = v549[1];
            v237 = *((unsigned __int16 *)v224 + 1);
            v239 = *((unsigned int *)v476 + 1);
            v479 = *((unsigned __int16 *)v476 + 1);
          }
          v240 = 5 * v228 + 5;
          for(j = (unsigned __int8 *)(v222 + v239); v223 != *j; j += 6)
            ;
          v438 = j[1];
          v242 = v237 + 2 * v240;
          v243 = (2 * (2 * v240 < v237) + 5) * v478 + v479;
          if(v243 * v236 < (int)(v242 * v438)) {
            if(v236 > 228)
              goto LABEL_162;
            v244 = v237 - v236;
            v245 = ((v242 - v236) * (v438 + 3 * v236) + 3 * (v242 - v236) + v243 - v438 - 4) / (3 * (v242 - v236) + v243 - v438);
            if(v245 > v236 + 11)
              LOWORD(v245) = v236 + 11;
            LOWORD(v237) = v245 + v244;
            *((_WORD *)v224 + 1) = v237;
            v549[1] = v245;
            v236 = (unsigned __int8)v245;
            v237 = (unsigned __int16)v237;
          }
        }
      }
    }
    if(v236 <= 9) {
      v246 = (unsigned __int8)algn_141136BC4[v236 + 1083];
      goto LABEL_164;
    }
  LABEL_162:
    v246 = v236 - 6;
  LABEL_164:
    v247 = v237 - v246;
    v248 = (6 * v247 < v246) + (15 * v247 < 4 * v246) + (9 * v247 < 4 * v246) + (13 * v247 < 8 * v246) + (v247 < v246) + (v247 < 2 * v246) + (v247 < 6 * v246) + (35 * v247 < 4 * v246) + 1;
    do {
      v249 = *--v225;
      if(v248 > *(unsigned __int8 *)(*v225 + 1))
        *(_BYTE *)(v249 + 1) = v248;
      else
        v248 = *(unsigned __int8 *)(*v225 + 1);
    } while(v225 != qword_14025F220);
    v554 = v249;
    dword_141133684 = v248 - ((6 * v247 < v246) + (15 * v247 < 4 * v246) + (9 * v247 < 4 * v246) + (13 * v247 < 8 * v246) + (v247 < v246) + (v247 < 2 * v246) + (v247 < 6 * v246) + (35 * v247 < 4 * v246) + 1);
    dword_14025F20C = 1 << v223;
    dword_14025F200 = (unsigned int)(v223 + dword_14025F1FC) >> 5;
    dword_14025F208 = (unsigned int)(v223 + dword_14025F204) >> 5;
    v556 = (((1 << v223) & dword_14020F1FC[(unsigned int)(v223 + dword_14025F1FC) >> 5]) != 0) + 2 * (((1 << v223) & dword_14021F1FC[(unsigned int)(v223 + dword_14025F204) >> 5]) != 0);
    v250 = dword_1401CF1FC[v223 + (dword_14014ADB0 << 8)];
    if((unsigned int)(dword_141133688 - v250) >= 0x20000) {
      dword_14014ADF0 = 0x20000;
      dword_14014ADEC = 0x20000;
      dword_14014ADE8 = 0x20000;
    } else {
      dword_14014ADEC = dword_1401CF1FC[v223 + (dword_14014ADB0 << 8)];
      dword_14014ADE8 = (unsigned __int8)byte_14002A158[(v250 + 2) & 0x1FFFF];
      dword_14014ADEC = dword_141133688 - v250;
      dword_14014ADF0 = dword_141133688 - dword_1401CF1FC[dword_14014ADE8 + (v223 << 8)];
    }
    v251 = *((unsigned int *)v3 + 2);
    v252 = *(unsigned __int8 *)(v251 + v222);
    v253 = 32 * (dword_141133660 > 0) + (v3[1] & 0x80);
    dword_14113368C += (v252 == 0) << 7;
    v555 = dword_141133690 - v552;
    v254 = dword_141133694 + ((4 * (dword_141133690 - v552 > 3) + 8 * (v223 == v550) + (v223 == dword_14014AD70) + 2 * (v2 == dword_14010A158[v223])) << 9) + v253 + ((v556 == 3 || v2 == dword_14010A958[v223]) << 13);
    v255 = (((dword_141133698 & 6) == 6) << 8) + ((dword_141133698 & 1) << 6);
    v256 = v254 + v255;
    if(v252) {
      v257 = v256 & 0xFFFFFFDE;
      v258 = v248 != (6 * v247 < v246) + (15 * v247 < 4 * v246) + (9 * v247 < 4 * v246) + (13 * v247 < 8 * v246) + (v247 < v246) + (v247 < 2 * v246) + (v247 < 6 * v246) + (35 * v247 < 4 * v246) + 1 || v247 <= 10 * v246;
      v259 = 32 * v258 + v257 + (v223 == dword_14113369C);
    } else {
      v260 = *(unsigned int *)(v251 + v222 + 8);
      v252 = *(unsigned __int8 *)(v260 + v222);
      if(*(_BYTE *)(v260 + v222) || v555 < 4 || v555 < 5 && v551 < 4 && *((unsigned __int16 *)v224 + 1) - v549[1] < 36) {
        v261 = *(_DWORD *)(v260 + v222 + 8);
        if(v261)
          v262 = 2 * v252 < *(unsigned __int8 *)(v261 + v222);
        else
          v262 = 0;
        v259 = v256 + 8 * v262 + 16;
      } else if(v553 >= 6) {
        if(v553 >= 0xE) {
          v263 = v254 + v255 + 12;
          v259 = v254 + v255 + 14;
          if(v553 < 0x20)
            v259 = v263;
        } else {
          v259 = v254 + v255 + 10;
        }
      } else {
        v259 = v254 + v255 + 8;
      }
    }
    v264 = v259 + (unsigned int)*((unsigned __int8 *)xmmword_140029100 + v252);
    v265 = &dword_14025FA20[0x8000 * (unsigned __int64)(unsigned __int8)byte_140029240[v248]];
    qword_141133590 = (__int64)&v265[2 * (v264 ^ 0x1000)];
    qword_141133598 = (__int64)&v265[2 * (v264 ^ 1)];
    qword_1411335A0 = (__int64)&v265[2 * (v264 ^ 0x2000)];
    qword_1411335A8 = (__int64)&v265[2 * (v264 ^ 0x20)];
    qword_1411335B0 = (__int64)&v265[2 * (v264 ^ 0x200)];
    v266 = (__int64)&v265[2 * (v264 ^ 0x400)];
    v267 = &v265[2 * v264];
    v268 = *((unsigned __int16 *)v267 + 2);
    qword_1411335B8 = v266;
    qword_1411335C0 = (__int64)v267;
    qword_1411335C8 = (__int64)(v267 - 4);
    qword_1411335D0 = (__int64)(v267 + 4);
    if(v268 > 0x8000) {
      sub_140010850((__int64)v267);
      v268 = *((unsigned __int16 *)v267 + 2);
    }
    v269 = *(unsigned __int16 *)v267;
    v270 = *((_WORD *)v267 + 3);
    dword_141133680 = v269;
    *((_WORD *)v267 + 2) = v268 + v270;
    dword_14113367C = v268;
    dword_14014AD98 = v269;
    dword_14014AD9C = v268;
    v271 = (v223 == dword_14014AD80) + (dword_1411336A0 & 0xE200);
    v272 = v223 == dword_14014AD88;
    v273 = (v223 & 0xE0) + 16 * (v223 == dword_14014ADD0) + 8 * (v223 == dword_14014ADCC) + 4 * (v223 == dword_14014AD8C);
    v274 = (((_WORD)v223 - (_WORD)dword_14014ADB0) & 0x800) + (((_WORD)dword_14014ADB4 - (_WORD)v223) & 0x400) + ((v223 == dword_14014ADDC) << 8);
    v275 = v556;
    v276 = v274 + v273 + v271 + 2 * v272;
    if(v556)
      v275 = 1;
    dword_1411336A0 = (v275 << 12) + v276 + (((v268 < (unsigned int)(56 * v269)) + (v268 < (unsigned int)(6 * v269))) << 16);
    v277 = &dword_14045FB20[2 * dword_1411336A0];
    v278 = *v277;
    qword_1411335D8 = (__int64)v277;
    v279 = v269 * (__int64)v278 / v277[1];
    v280 = dword_141133680;
    v281 = 1 - dword_141133680;
    if(v279 >= 1 - dword_141133680) {
      v281 = 0x40000;
      if(v279 < 0x40000)
        v281 = v279;
    }
    v282 = *v277;
    v283 = v277[1];
    if((int)abs32(*v277) > 0x40000) {
      v282 >>= 1;
      *v277 = v282;
      v283 >>= v283 > 4096;
    }
    v284 = v282 - v280;
    *v277 = v284;
    v285 = v280 + v283 + 2;
    if(v285 > 0x40000000) {
      *v277 = v284 >> 1;
      v285 >>= 1;
    }
    v277[1] = v285;
    v286 = (unsigned __int16 *)qword_1411335C0;
    v287 = *(unsigned __int16 *)(qword_1411335C0 + 6);
    v288 = v281 + dword_14113367C;
    v289 = v281 + v280;
    if(v287 <= 0x20) {
      v290 = dword_141133674;
      dword_14113367C = v288;
      dword_141133680 = v289;
      qword_1411335B8 = (__int64)dword_1405DFC20;
      qword_1411335B0 = (__int64)dword_1405DFC20;
      qword_1411335A8 = (__int64)dword_1405DFC20;
      qword_1411335A0 = (__int64)dword_1405DFC20;
      qword_141133598 = (__int64)dword_1405DFC20;
      qword_141133590 = (__int64)dword_1405DFC20;
      qword_1411335D0 = (__int64)dword_1405DFC20;
      qword_1411335C8 = (__int64)dword_1405DFC20;
      qword_1411335E0 = (__int64)dword_1405DFC20;
      qword_1411335E8 = (__int64)dword_1405DFC20;
      qword_1411335F0 = (__int64)&dword_1411336A4;
    } else {
      v290 = dword_141133674;
      v291 = &dword_14079FD20[128 * (unsigned __int64)(unsigned __int8)byte_1400293C0[v248] + 64 * (dword_141133660 > -9) + 4 * (unsigned int)(dword_14010A558[dword_141133674] == dword_141133664) + (((unsigned int)v264 >> 6) & 0xBLL) + (unsigned int)(16 * v556)];
      v292 = *v291;
      qword_1411335F0 = (__int64)v291;
      v293 = (v292 >> (v287 < 0x230)) + v289;
      dword_141133680 = v293;
      v294 = (0x3100u >> (v287 < 0x230)) + v288;
      dword_14113367C = v294;
      *v291 = v292 - ((v292 + 2) >> 3);
      v295 = qword_1411335C8;
      v105 = v287 < 0x220;
      v296 = *(_WORD *)(qword_1411335C8 + 4);
      v297 = v105;
      if(v296 > 0x8000u) {
        v435 = qword_1411335C8;
        v432 = v286;
        sub_140010850(qword_1411335C8);
        v286 = v432;
        v295 = v435;
        v296 = *(_WORD *)(v435 + 4);
      }
      dword_1411336A8 = *(unsigned __int16 *)(v295 + 6) >> v297;
      *(_WORD *)(v295 + 4) = dword_1411336A8 + v296;
      v298 = qword_1411335D0;
      v299 = *(_WORD *)(qword_1411335D0 + 4);
      if(v299 > 0x8000u) {
        v434 = qword_1411335D0;
        v431 = v286;
        sub_140010850(qword_1411335D0);
        v286 = v431;
        v298 = v434;
        v299 = *(_WORD *)(v434 + 4);
      }
      dword_1411336AC = *(unsigned __int16 *)(v298 + 6) >> v297;
      v300 = (__int64)(v286 - 0x10000);
      qword_1411335E0 = (__int64)(v286 - 0x10000);
      *(_WORD *)(v298 + 4) = dword_1411336AC + v299;
      v301 = *(v286 - 0x10000);
      v302 = v286[0x10000];
      v303 = *(v286 - 65534);
      qword_1411335E8 = (__int64)(v286 + 0x10000);
      v304 = v302 + v301;
      v305 = v286[65538];
      v289 = (v304 >> (v297 + 1)) + v293;
      dword_141133680 = v289;
      v288 = ((unsigned int)(v305 + v303) >> (v297 + 1)) + v294;
      dword_14113367C = v288;
      if(v305 > 0x8000) {
        v433 = v286 - 0x10000;
        v430 = v286;
        sub_140010850((__int64)(v286 + 0x10000));
        v286 = v430;
        v300 = (__int64)v433;
        LOWORD(v305) = v430[65538];
      }
      dword_1411336B0 = v286[65539] >> v297;
      v286[65538] = dword_1411336B0 + v305;
      v306 = *(v286 - 65534);
      if(v306 > 0x8000u) {
        v429 = v286;
        sub_140010850(v300);
        v286 = v429;
        v306 = *(v429 - 65534);
      }
      dword_1411336B4 = *(v286 - 65533) >> v297;
      *(v286 - 65534) = dword_1411336B4 + v306;
      v307 = qword_141133590;
      v308 = *(_WORD *)(qword_141133590 + 4);
      v309 = (v286[3] < 0x398u) + v297;
      if(v308 > 0x8000u) {
        sub_140010850(qword_141133590);
        v308 = *(_WORD *)(v307 + 4);
      }
      dword_1411336B8 = *(unsigned __int16 *)(v307 + 6) >> v309;
      *(_WORD *)(v307 + 4) = dword_1411336B8 + v308;
      v310 = qword_141133598;
      v311 = *(_WORD *)(qword_141133598 + 4);
      if(v311 > 0x8000u) {
        sub_140010850(qword_141133598);
        v311 = *(_WORD *)(v310 + 4);
      }
      dword_1411336BC = *(unsigned __int16 *)(v310 + 6) >> v309;
      *(_WORD *)(v310 + 4) = dword_1411336BC + v311;
      v312 = qword_1411335A0;
      v313 = *(_WORD *)(qword_1411335A0 + 4);
      if(v313 > 0x8000u) {
        sub_140010850(qword_1411335A0);
        v313 = *(_WORD *)(v312 + 4);
      }
      dword_1411336C0 = *(unsigned __int16 *)(v312 + 6) >> v309;
      *(_WORD *)(v312 + 4) = dword_1411336C0 + v313;
      v314 = qword_1411335A8;
      v315 = *(_WORD *)(qword_1411335A8 + 4);
      if(v315 > 0x8000u) {
        sub_140010850(qword_1411335A8);
        v315 = *(_WORD *)(v314 + 4);
      }
      dword_1411336C4 = *(unsigned __int16 *)(v314 + 6) >> v309;
      *(_WORD *)(v314 + 4) = dword_1411336C4 + v315;
      v316 = qword_1411335B0;
      v317 = *(_WORD *)(qword_1411335B0 + 4);
      if(v317 > 0x8000u) {
        sub_140010850(qword_1411335B0);
        v317 = *(_WORD *)(v316 + 4);
      }
      dword_1411336C8 = *(unsigned __int16 *)(v316 + 6) >> v309;
      *(_WORD *)(v316 + 4) = dword_1411336C8 + v317;
      v318 = qword_1411335B8;
      v319 = *(_WORD *)(qword_1411335B8 + 4);
      if(v319 > 0x8000u) {
        sub_140010850(qword_1411335B8);
        v319 = *(_WORD *)(v318 + 4);
      }
      dword_1411336CC = *(unsigned __int16 *)(v318 + 6) >> v309;
      *(_WORD *)(v318 + 4) = dword_1411336CC + v319;
    }
    dword_141133680 = 60416LL * v289 / v288;
    dword_14113367C = 60416;
    dword_14014ADA0 = dword_141133680;
    dword_14014ADA4 = 60416;
    v320 = &dword_1407A0720[0x100000 * (dword_14014AD68 < (unsigned int)dword_14014ADB8) + 0x80000 * (v290 == dword_14014AD70) + 0x20000 * dword_141133694 + 512 * dword_14014ADB4 + 2 * v290 + 2 * (unsigned __int64)((unsigned __int8)((unsigned int)dword_14014ADEC < 0x78) << 17)];
    v321 = *v320;
    qword_1411335F8 = (__int64)v320;
    v322 = dword_141133680 * (__int64)v321 / v320[1];
    v323 = dword_141133680;
    v324 = 1 - dword_141133680;
    if(v322 >= 1 - dword_141133680) {
      v324 = 0x40000;
      if(v322 < 0x40000)
        v324 = (int)(60416LL * v289 / v288) * (__int64)v321 / v320[1];
    }
    v325 = *v320;
    if((int)abs32(*v320) > 0x80000) {
      v326 = v320[1];
      v325 >>= 1;
      *v320 = v325;
      v320[1] = v326 >> (v326 > 0x2000);
    }
    v327 = v320[1];
    v328 = v325 - v323;
    *v320 = v328;
    v329 = v323 + v327 + 1120;
    v320[1] = v329;
    if(v329 > 0x40000000) {
      *v320 = v328 >> 1;
      v320[1] = v329 >> 1;
    }
    dword_14113367C += v324;
    dword_14014ADA8 = dword_14113367C;
    v330 = v324 + v323;
    dword_141133680 = v330;
    v331 = ((17 * v330 < (unsigned int)dword_14113367C) << 13) + (((unsigned __int16)dword_14014ADE8 - (unsigned __int16)v290) & 0x1000) + 16 * (v290 == dword_14113369C) + 8 * (v290 == dword_14014AD70) + 4 * (v290 == dword_14014AD94) + (v290 == dword_14014AD84) + (((unsigned int)dword_14014ADF0 < 0x29) << 7) + dword_1411336D0 + (dword_1411336A0 & 0x800) + 2 * (*((unsigned __int8 *)xmmword_140028F00 + v290) + (v290 == dword_14014AD90)) + 32 * (((unsigned int)dword_14014ADEC < 0xA800) + ((unsigned int)dword_14014ADEC < 0x600) + ((unsigned int)dword_14014ADEC < 0xD));
    v332 = &dword_140FA0820[2 * v331];
    v333 = *v332;
    qword_141133600 = (__int64)v332;
    v334 = (dword_14113367C - v330) * (__int64)v333 / dword_140FA0824[2 * v331];
    v335 = v330;
    v336 = v330 - dword_14113367C + 1;
    if(v334 >= v336) {
      v336 = 0x40000;
      if(v334 < 0x40000)
        v336 = (dword_14113367C - v330) * (__int64)v333 / dword_140FA0824[2 * v331];
    }
    v337 = *v332;
    v338 = v336 + dword_14113367C;
    dword_14113367C += v336;
    v339 = dword_140FA0824[2 * v331];
    if((int)abs32(v337) > 0x100000) {
      v337 >>= 1;
      *v332 = v337;
      v339 >>= v339 > 0x2000;
    }
    v340 = v337 + 2 * v330;
    v341 = dword_14014AD7C;
    *v332 = v340;
    dword_140FA0824[2 * v331] = v339 + 1;
    v342 = qword_141133588 + *(_DWORD *)(v554 + 2) - qword_141133560;
    v343 = dword_14010A558[v290] == dword_141133664;
    v344 = *(unsigned __int8 *)(qword_14002A150 + (((_WORD)v290 - v341) & 0x1FF));
    v345 = (*(_DWORD *)(qword_14002A150 + 512) < (unsigned int)(384 * v344)) + (*(_DWORD *)(qword_14002A150 + 512) < (unsigned int)(58 * v344)) + (*(_DWORD *)(qword_14002A150 + 512) < (unsigned int)(22 * v344));
    v346 = (unsigned __int8)byte_1400EA158[dword_14014ADF8];
    dword_14014ADAC = v338;
    v347 = &dword_141060920[2 * (int)(4 * (v342 >= 0xFFFFFD20) + v343 + (v331 & 0x700) + dword_14113368C + (((unsigned int)dword_14014ADEC < 0x2C00) << 11) + 2 * (v290 == v346) + 8 * v345)];
    v348 = *v347;
    qword_141133608 = (__int64)v347;
    v349 = (v338 - v335) * (__int64)v348 / v347[1];
    v350 = dword_141133680;
    v351 = dword_141133680 - dword_14113367C + 1;
    if(v349 >= v351) {
      v351 = 0x80000;
      if(v349 < 0x80000)
        v351 = (v338 - v335) * (__int64)v348 / v347[1];
    }
    v352 = *v347;
    v353 = v351 + dword_14113367C;
    dword_14113367C += v351;
    v354 = v347[1];
    if((int)abs32(v352) > 0x100000) {
      v352 >>= 1;
      *v347 = v352;
      v354 >>= v354 > 0x2000;
    }
    v355 = dword_141133670;
    *v347 = v352 + v335;
    v347[1] = v354 + 2;
    v172 = dword_141133710;
    v356 = v350 * (v355 / v353);
    dword_1411336D4 = v356;
    if(dword_141133710 >= v356) {
      v423 = (unsigned int)dword_14025F200;
      v424 = dword_14025F20C;
      v425 = v3[2];
      v426 = v353 * v3[3];
      v172 = dword_141133710 - v356;
      v171 = v355 - v356;
      dword_141133710 -= v356;
      dword_141133670 = v171;
      dword_140029540[v425] = dword_141133664;
      dword_14020F1FC[v423] &= ~v424;
      qword_141133610 = 0;
      dword_14021F1FC[dword_14025F208] &= ~dword_14025F20C;
      v195 = qword_141133588;
      v427 = v3[3];
      v3 = (unsigned __int8 *)qword_141133580;
      v203 = *(unsigned __int8 *)qword_141133580;
      dword_141133694 = 0;
      dword_1411336DC = v203;
      LODWORD(v202) = (int)(16 * (v427 * v350 + v350 - v427 * v353)) / (int)(v353 + v426);
      dword_1411336D8 = v202;
      do {
      LABEL_126:
        v204 = *((_DWORD *)v3 + 2);
        if(!v204)
          return v202;
        v205 = dword_141133690;
        v206 = --dword_141133690;
        v3 = (unsigned __int8 *)(v195 + v204);
        v207 = *v3;
        qword_141133580 = (__int64)v3;
        if(v207) {
          v202 = v3[1] & 0xF;
          if(!*(_BYTE *)(v195 + *((unsigned int *)v3 + 1) + 6 * v202 + 1))
            LODWORD(v202) = sub_14000C0E0(v3);
        }
        v208 = v207 - v203;
      } while(!v208);
      v209 = *((unsigned int *)v3 + 1);
      v536 = v206;
      v537 = v205;
      v567 = v208;
      v535 = *v3;
      v67 = 0x8000;
      v534 = v535 + 1;
      v210 = v535 - v203;
      v538 = v535 + 1;
      v211 = v210;
      v212 = 0;
      v213 = qword_14025F220;
      v541 = 0;
      v214 = qword_14025F220;
      v215 = *(unsigned __int8 *)(v195 + v209 + 6LL * (v3[1] & 0xF));
      v543 = (unsigned __int8 *)(v195 + v209 + 6LL * (v3[1] & 0xF));
      v2 = dword_141133664;
      v569 = *v543;
      dword_141133674 = v569;
      v542 = v215;
      if(dword_141133664 == dword_140029540[v215]) {
        dword_1411336C8 = 0x8000;
      } else {
        v216 = v543[1];
        qword_14025F220[0] = (__int64)v543;
        v212 = 1;
        v213 = &qword_14025F228;
        dword_140029540[v542] = dword_141133664;
        v214 = &qword_14025F228;
        v541 = v216;
        v67 = 0;
        v211 = v210 - 1;
        dword_1411336C8 = 0;
      }
      v217 = (unsigned __int8 *)(v195 + v209 - 6);
      if(v211) {
        v218 = v213;
        v520 = v210;
        v219 = v541;
        v521 = v195;
        v522 = v172;
        v524 = v171;
        v526 = v67;
        v558 = v3;
        while(1) {
          do {
            v217 += 6;
            v220 = *v217;
            v221 = *v217;
          } while(v2 == dword_140029540[v221]);
          v378 = v217[1];
          dword_140029540[v221] = v2;
          *v213++ = (__int64)v217;
          v214 = v213;
          v219 += v378;
          if(v220 == dword_14014AD70)
            break;
          if(v2 == dword_14010A958[v221] || v2 == dword_14010A558[v221]) {
            v380 = v218;
            v379 = 4 * (v2 == dword_14010A958[v221]) + 12;
            goto LABEL_274;
          }
        LABEL_278:
          if(!--v211) {
            v195 = v521;
            v172 = v522;
            v171 = v524;
            v67 = v526;
            v3 = v558;
            v541 = v219;
            v210 = v520;
            goto LABEL_280;
          }
        }
        v379 = 22;
        v380 = &qword_14025F220[(unsigned __int8)v212 & ((byte_14014AD5C & 7) == 0)];
      LABEL_274:
        for(k = v213 - 1; k > v380; --k) {
          v382 = *(k - 1);
          if(v379 * *(unsigned __int8 *)(*k + 1) <= *(unsigned __int8 *)(v382 + 1))
            break;
          *(k - 1) = *k;
          *k = v382;
        }
        ++v218;
        goto LABEL_278;
      }
    LABEL_280:
      qword_1411335A8 = (__int64)dword_1405DFC20;
      qword_1411335A0 = (__int64)dword_1405DFC20;
      qword_141133598 = (__int64)dword_1405DFC20;
      qword_141133590 = (__int64)dword_1405DFC20;
      qword_141133618 = (__int64)dword_1405DFC20;
      if(v535 == 255) {
        v570 = -1;
        dword_141133678 = -1;
        qword_1411335B0 = (__int64)dword_1405DFC20;
        v419 = 1;
        v540 = dword_141133698;
        v539 = dword_1411336E0;
      } else {
        v383 = *((unsigned int *)v3 + 2);
        v497 = (unsigned __int8 *)(v195 + v383);
        v504 = *(unsigned int *)(v195 + v383 + 4);
        v570 = *(unsigned __int8 *)(v195 + v504 + 6LL * (*(_BYTE *)(v195 + v383 + 1) & 0xF));
        if(v570 == v569) {
          v384 = *(unsigned int *)(v195 + v383 + 4);
          v385 = (unsigned __int8 *)(v195 + v383);
          v386 = *(unsigned __int8 *)(v195 + v384 + 6LL * (*(_BYTE *)(v195 + v383 + 1) & 0xF));
          do {
            if(*v385 != *v3)
              break;
            v385 = (unsigned __int8 *)(v195 + *((unsigned int *)v385 + 2));
            v384 = *((unsigned int *)v385 + 1);
            v386 = *(unsigned __int8 *)(v195 + v384 + 6LL * (v385[1] & 0xF));
          } while(v386 == v569);
          v504 = v384;
          v497 = v385;
          v570 = v386;
          dword_141133678 = v386;
        } else {
          dword_141133678 = *(unsigned __int8 *)(v195 + *(unsigned int *)(v195 + v383 + 4) + 6LL * (*(_BYTE *)(v195 + v383 + 1) & 0xF));
        }
        v387 = v3[1];
        if(16 * v210 <= v541 || (v3[1] & 0x40) != 0) {
          qword_141133620 = (__int64)v214;
          v503 = *((unsigned __int16 *)v3 + 1);
        } else {
          v388 = *v497 + 1;
          v389 = (unsigned __int8 *)(v195 + v504);
          v390 = v388;
          do {
            byte_141108A20[*v389] = v389[1];
            v389 += 6;
            --v390;
          } while(v390);
          v391 = *((unsigned __int16 *)v3 + 1);
          v392 = 5 * v535 + 5;
          v523 = v172;
          v525 = v171;
          v527 = v67;
          v393 = v391;
          v519 = v2;
          v394 = 0;
          v395 = (5 * ((unsigned int)(2 * v392 - v391) >> 31) + 8) * v388 + *((unsigned __int16 *)v497 + 1);
          do {
            v396 = *--v213;
            v398 = *(unsigned __int8 *)(*v213 + 1);
            v399 = v393 + 2 * v392;
            LOBYTE(v400) = *(_BYTE *)(*v213 + 1);
            if((int)(v398 * v395) < v399 * (unsigned __int8)byte_141108A20[*(unsigned __int8 *)*v213] && *(unsigned __int8 *)(*v213 + 1) <= 0xE4u) {
              v401 = v391 - v398;
              v397 = (unsigned __int8)byte_141108A20[*(unsigned __int8 *)*v213];
              v400 = ((v399 - v398) * (3 * v398 + v397) + 3 * (v399 - v398) + v395 - v397 - 4) / (3 * (v399 - v398) + v395 - v397);
              if(v400 > v398 + 11)
                v400 = v398 + 11;
              v391 = v400 + v401;
              *((_WORD *)v3 + 1) = v391;
              *(_BYTE *)(v396 + 1) = v400;
              v393 = (unsigned __int16)v391;
            }
            v394 += (unsigned __int8)v400;
          } while(v213 != qword_14025F220);
          v172 = v523;
          v171 = v525;
          v387 = v3[1];
          v383 = *((unsigned int *)v3 + 2);
          v503 = v393;
          v67 = v527;
          v541 = v394;
          v2 = v519;
          qword_141133620 = (__int64)v213;
        }
        v402 = *(unsigned __int8 *)(v383 + v195);
        v538 = v402 + 1;
        v501 = v2 != dword_140029540[dword_14113369C];
        v498 = v2 != dword_140029540[v570];
        v540 = dword_141133698;
        v500 = 2 * v402 + 2;
        v403 = (int)((((16 * (unsigned int)*v3 - v503) >> 26) & 0xFFFFFFE0) + (dword_141133698 & 3) + 8 * (v501 | (v2 != dword_140029540[*(unsigned __int8 *)(v195 + *(unsigned int *)(v383 + v195 + 4) + 6LL * (*(_BYTE *)(v383 + v195 + 1) & 0xF))])) + 4 * (v534 * v541 > v503 * v210) + (v387 & 0xC0) + 16 * (v210 >= 2 * v402 - 2 * v535));
        v502 = (unsigned __int8)byte_1400292BE[v534];
        v404 = (v502 << 11) + 8 * v403;
        v499 = v403;
        v405 = (char *)dword_141128C20 + v404;
        v406 = *(int *)((char *)dword_141128C20 + v404);
        v407 = *(unsigned __int16 *)((char *)&word_141128C24 + v404);
        qword_1411335B0 = (__int64)dword_141128C20 + v404;
        dword_141133680 = v406;
        v505 = v407;
        dword_14113367C = v407;
        if(v407 > 0x8000 || v406 > 0x80000) {
          v443 = v403;
          v533 = v67;
          sub_140010730((__int64)dword_141128C20 + v404);
          v67 = v533;
          LODWORD(v403) = v443;
          LOWORD(v407) = *((_WORD *)v405 + 2);
        }
        v408 = *((unsigned __int16 *)v405 + 3);
        *((_WORD *)v405 + 2) = v408 + v407;
        v539 = dword_1411336E0;
        if(v408 > 0x78) {
          v473 = &dword_141108B20[2048 * v502 + 16 * (unsigned int)(*v3 + v500 > dword_1411336E0) + 2 * ((unsigned __int8)v403 & 0xF3) + 2 * (unsigned int)(v498 << 9) + 2 * (unsigned int)(v501 << 8) + 2 * (unsigned __int64)(4 * (unsigned int)(v536 < 10))];
          qword_1411335A8 = (__int64)v473;
          v468 = v408 < 0x100;
          v471 = (v408 < 0x100) + 1;
          v409 = *((_DWORD *)v405 + 512);
          qword_141133618 = (__int64)(v405 + 2048);
          v410 = (v409 + *((_DWORD *)v405 - 512)) >> v471;
          qword_141133590 = (__int64)(v405 - 2048);
          v472 = v409;
          v411 = *((unsigned __int16 *)v405 - 1022);
          v406 += v410;
          v412 = *((unsigned __int16 *)v405 + 1026);
          dword_141133680 = v406;
          v505 += (unsigned int)(v412 + v411) >> v471;
          dword_14113367C = v505;
          if(v412 > 0x8000 || v472 > 0x80000) {
            v442 = v403;
            v532 = v67;
            sub_140010730((__int64)(v405 + 2048));
            v67 = v532;
            LODWORD(v403) = v442;
            v412 = *((unsigned __int16 *)v405 + 1026);
          }
          v413 = *((unsigned __int16 *)v405 - 1022);
          v414 = (*((unsigned __int16 *)v405 + 1027) >> v471) + v412;
          dword_1411336EC = *((unsigned __int16 *)v405 + 1027) >> v471;
          *((_WORD *)v405 + 1026) = v414;
          if(v413 > 0x8000 || *((_DWORD *)v405 - 512) > 0x80000u) {
            v441 = v403;
            v531 = v67;
            sub_140010730((__int64)(v405 - 2048));
            v67 = v531;
            LODWORD(v403) = v441;
            LOWORD(v413) = *((_WORD *)v405 - 1022);
          }
          dword_1411336B8 = *((unsigned __int16 *)v405 - 1021) >> v471;
          *((_WORD *)v405 - 1022) = dword_1411336B8 + v413;
          v470 = *((unsigned __int16 *)v405 + 3) < 0x200u;
          v415 = *((unsigned __int16 *)v473 + 2);
          if(v415 > 0x8000 || (unsigned int)*v473 > 0x80000) {
            v440 = v403;
            v530 = v67;
            sub_140010730((__int64)v473);
            v67 = v530;
            LODWORD(v403) = v440;
            LOWORD(v415) = *((_WORD *)v473 + 2);
          }
          dword_1411336C4 = *((unsigned __int16 *)v473 + 3) >> v470;
          *((_WORD *)v473 + 2) = dword_1411336C4 + v415;
          v469 = (*((unsigned __int16 *)v405 + 3) < 0x400u) + v468 + 1;
          v416 = &v405[-8 * v499];
          v417 = *(unsigned __int16 *)&v416[8 * (int)(v403 ^ 2) + 4];
          v474 = (__int64)&v416[8 * (int)(v403 ^ 2)];
          qword_141133598 = v474;
          if(v417 > 0x8000 || *(_DWORD *)v474 > 0x80000u) {
            v439 = v403;
            v529 = v67;
            sub_140010730(v474);
            v67 = v529;
            LODWORD(v403) = v439;
            LOWORD(v417) = *(_WORD *)(v474 + 4);
          }
          dword_1411336BC = *(unsigned __int16 *)(v474 + 6) >> v469;
          *(_WORD *)(v474 + 4) = dword_1411336BC + v417;
          v475 = (__int64)&v416[8 * (int)(v403 ^ 8)];
          qword_1411335A0 = v475;
          v418 = *(_WORD *)(v475 + 4);
          if(v418 > 0x8000u || *(_DWORD *)v475 > 0x80000u) {
            v528 = v67;
            sub_140010730(v475);
            v67 = v528;
            v418 = *(_WORD *)(v475 + 4);
          }
          dword_1411336C0 = *(unsigned __int16 *)(v475 + 6) >> v469;
          *(_WORD *)(v475 + 4) = dword_1411336C0 + v418;
        }
        v419 = ((v505 >> 1) + v534 * v406) / v505 + 2;
        if(v534 < 24) {
          v571 = 0;
          goto LABEL_317;
        }
      }
      v571 = (int)(v419 + *((unsigned __int16 *)v3 + 1)) >> 1;
    LABEL_317:
      dword_1411336F0 = v571;
      v70 = v541 + v419;
      dword_1411336E8 = v70;
      dword_141133660 = dword_141133708;
      dword_1411336E4 = v541 + v535 + 1;
      v68 = 0;
      v69 = qword_14025F220;
      dword_1411336CC = 0;
      qword_141133620 = (__int64)qword_14025F220;
      v420 = (v536 > 1) << 15;
      v572 = v420 + (dword_1411336A0 & 0x7FFF);
      dword_1411336A0 = v420 + (dword_1411336A0 & 0xFFFF7FFF);
      dword_1411336D0 = ((v536 > 3) << 15) + v420 + (dword_1411336D0 & 0x4600);
      v421 = v536 < 3 || v537 + 22 < dword_14113370C;
      v573 = 1032 * (*((_DWORD *)v3 + 2) == 0) + 32 * (v540 & 3) + 2 * v421;
      dword_1411336F4 = v573;
      dword_14113368C = 32 * (*v3 + 28 > 2 * v539) + (((unsigned int)(v538 - v534 - 3) >> 24) & 0xFFFFFF80) + ((v536 > 2) << 13) + (((dword_14113370C > 7) + (dword_14113370C > 2) + 7 * (((unsigned int)(74 - v534) >> 31) + ((unsigned int)(2 - v534) >> 31)) + (v536 > 16)) << 12);
      while(1) {
        if(v171 < 0x1000000) {
          v518 = v2;
          v373 = v68;
          v374 = v67;
          v375 = v70;
          do {
            v376 = a2->_cnt - 1;
            a2->_cnt = v376;
            if(v376 < 0)
              v377 = filbuf(a2);
            else
              v377 = *(unsigned __int8 *)a2->_ptr++;
            v172 = v377 | (v172 << 8);
            dword_141133710 = v172;
            v171 <<= 8;
            dword_141133670 = v171;
          } while(v171 < 0x1000000);
          v70 = v375;
          v2 = v518;
          v68 = v373;
          v67 = v374;
        }
      LABEL_57:
        v71 = (unsigned __int8 *)*v69;
        v72 = *(unsigned __int8 *)(*v69 + 1);
        v574 = v3;
        qword_141133620 = (__int64)(v69 + 1);
        qword_1411335D0 = (__int64)dword_1405DFC20;
        qword_1411335C8 = (__int64)dword_1405DFC20;
        qword_1411335E0 = (__int64)dword_1405DFC20;
        qword_1411335E8 = (__int64)dword_1405DFC20;
        v73 = *v71;
        v74 = ((v72 << 8) - v68) / v70;
        dword_14025F20C = 1 << *v71;
        v577 = v74;
        v575 = v74;
        v578 = (unsigned int)(unsigned __int8)byte_140029000[v74] + 1;
        dword_14025F200 = ((v73 + dword_14025F1FC) >> 5) + 0x2000;
        dword_14025F208 = v67 + ((v73 + dword_14025F204) >> 5);
        v75 = v73;
        v76 = v2 == dword_14010A558[v73];
        v576 = ((dword_14025F20C & dword_14020F1FC[((v73 + dword_14025F1FC) >> 5) + 0x2000]) != 0) + 2 * ((dword_14025F20C & dword_14021F1FC[v67 + ((v73 + dword_14025F204) >> 5)]) != 0);
        qword_141133628 = (__int64)&qword_1411336F8;
        qword_141133630 = (__int64)&qword_1411336F8;
        v77 = v2 == dword_14010A158[v73];
        v580 = v2 == dword_14010A958[v73];
        v78 = v73 == dword_14014AD6C || *(_DWORD *)(qword_14002A150 + 512) < *(unsigned __int8 *)(qword_14002A150 + (((_WORD)v73 - (_WORD)dword_14014AD7C) & 0x1FF)) << 7;
        v79 = dword_14014ADB0;
        v579 = dword_1401CF1FC[256 * dword_14014ADB0 + v73];
        if((unsigned int)(dword_141133688 - v579) >= 0x20000) {
          v80 = 0x20000;
          dword_14014ADF0 = 0x20000;
          dword_14014ADEC = 0x20000;
          dword_14014ADE8 = 0x20000;
        } else {
          dword_14014ADEC = dword_1401CF1FC[256 * dword_14014ADB0 + v73];
          dword_14014ADE8 = (unsigned __int8)byte_14002A158[(v579 + 2) & 0x1FFFF];
          dword_14014ADEC = dword_141133688 - v579;
          v80 = dword_141133688 - dword_1401CF1FC[256 * v73 + dword_14014ADE8];
          dword_14014ADF0 = v80;
        }
        v81 = v573 | (((v80 < 0x220) << 12) + (v78 << 9) + ((v70 < v571) << 11) + 8 * (v73 == v570) + ((v73 == v569) << 10) + *((unsigned __int8 *)xmmword_140028F00 + v73) + (v77 << 8) + 16 * (v73 == dword_14014AD70) + 4 * v580 + (unsigned int)v76);
        v82 = &dword_1405DFC20[0x4000 * v578 + 2 * v81];
        v83 = (unsigned __int16)word_1405DFC24[0x8000 * v578 + 4 * v81];
        qword_1411335C0 = (__int64)v82;
        if(v83 > 0x8000) {
          sub_140010850((__int64)&dword_1405DFC20[0x4000 * v578 + 2 * v81]);
          v79 = dword_14014ADB0;
          v83 = *((unsigned __int16 *)v82 + 2);
        }
        v84 = *(unsigned __int16 *)v82;
        v85 = *((_WORD *)v82 + 3);
        dword_141133680 = v84;
        *((_WORD *)v82 + 2) = v83 + v85;
        dword_14113367C = v83;
        dword_14014AD98 = v84;
        dword_14014AD9C = v83;
        v86 = v576;
        if(v576)
          v86 = 1;
        dword_1411336A0 = (((_WORD)v73 - v79) & 0x800) + (v86 << 12) + (v572 & 0xE200) + (((_WORD)dword_14014ADB4 - (_WORD)v73) & 0x400) + ((v73 == dword_14014ADDC) << 8) + (v73 & 0xE0) + 16 * (v73 == dword_14014ADD0) + 8 * (v73 == dword_14014ADCC) + 4 * (v73 == dword_14014AD8C) + (v73 == dword_14014AD80) + 2 * (v73 == dword_14014AD88) + (((v83 < (unsigned int)(56 * v84)) + (v83 < (unsigned int)(6 * v84))) << 16);
        v87 = &dword_14045FB20[2 * dword_1411336A0];
        v88 = *v87;
        qword_1411335D8 = (__int64)v87;
        v89 = v84 * (__int64)v88 / v87[1];
        v90 = dword_141133680;
        v91 = 1 - dword_141133680;
        if(v89 >= 1 - dword_141133680) {
          v91 = 0x40000;
          if(v89 < 0x40000)
            v91 = v89;
        }
        v92 = *v87;
        v93 = v87[1];
        if((int)abs32(*v87) > 0x40000) {
          v92 >>= 1;
          *v87 = v92;
          v93 >>= v93 > 4096;
        }
        v94 = v92 - v90;
        *v87 = v94;
        v95 = v90 + v93 + 2;
        if(v95 > 0x40000000) {
          *v87 = v94 >> 1;
          v95 >>= 1;
        }
        v87[1] = v95;
        v96 = v91 + dword_14113367C;
        v97 = v91 + v90;
        v98 = *(unsigned __int16 *)(qword_1411335C0 + 6);
        if(v98 <= 8) {
          dword_14113367C = v96;
          dword_141133680 = v97;
        } else {
          v559 = (unsigned __int16 *)qword_1411335C0;
          v560 = *(unsigned __int16 *)(qword_1411335C0 + 6);
          v557 = v3;
          v561 = v71;
          v562 = v73;
          v563 = v73;
          v99 = &dword_141130D20[512 * (unsigned __int64)(unsigned __int8)byte_140029440[v575] + 2 * (unsigned int)(v576 << 6)];
          v100 = &v99[2 * (v81 & 0x1F)];
          v101 = v100[1];
          qword_141133630 = (__int64)v100;
          v102 = &v99[2 * (((unsigned int)v81 >> 4) & 0x1F) + 64];
          v103 = *v102;
          qword_141133628 = (__int64)v102;
          v104 = v98 < 0x150;
          v105 = v98 < 0x48;
          v106 = v102[1];
          v107 = v105;
          v108 = v101 * (v577 + 2);
          v109 = v106 + v101;
          v110 = v108 >> 8;
          v111 = (unsigned int)(v106 * (v577 + 2)) >> 8;
          v112 = (v109 >> 11) & 0xFFFFFFFE;
          v105 = v109 < 0xC000;
          v113 = *v100;
          v114 = v110 + v111;
          if(!v105)
            v112 = 24;
          v115 = (unsigned __int8)byte_140022930[v112];
          v116 = (unsigned __int8)byte_140022931[v112];
          if(v114 >= 0x6000)
            v114 = 24576;
          v117 = ((v115 * v114 + v116 * (v103 + *v100)) >> (v104 + 7)) + v97;
          v118 = v104 + v107 + 3;
          v119 = ((unsigned int)(192 * (v115 + v116)) >> v104) + v96;
          dword_141133700 = 0x3000u >> v118;
          v120 = v104 + 4;
          dword_141133704 = 0x3000u >> v120;
          *v100 = v113 - (v113 >> v118);
          v3 = v557;
          v100[1] -= (v110 + 7) >> v120;
          v71 = v561;
          *v102 = v103 - (v103 >> v118);
          v102[1] -= (v111 + 7) >> v120;
          v121 = (__int64)(v559 - 0x8000);
          v122 = *(v559 - 0x8000);
          v75 = v563;
          v123 = *(v559 - 32766);
          v124 = v559 + 0x8000;
          v125 = v559[0x8000];
          qword_1411335E8 = (__int64)(v559 + 0x8000);
          v126 = v122 + v125;
          v127 = v559[32770];
          qword_1411335E0 = (__int64)(v559 - 0x8000);
          v97 = (v126 >> 3) + v117;
          dword_141133680 = v97;
          v96 = ((unsigned int)(v127 + v123) >> 3) + v119;
          v73 = v562;
          dword_14113367C = v96;
          v128 = (v560 < 0x30) + 1;
          if(v127 > 0x8000) {
            v447 = v97;
            v451 = v96;
            sub_140010850((__int64)(v559 + 0x8000));
            v96 = v451;
            v97 = v447;
            v121 = (__int64)(v559 - 0x8000);
            v128 = (v560 < 0x30) + 1;
            v124 = v559 + 0x8000;
            LOWORD(v127) = v559[32770];
          }
          dword_1411336B0 = v124[3] >> v128;
          v124[2] = dword_1411336B0 + v127;
          v129 = *(_WORD *)(v121 + 4);
          if(v129 > 0x8000u) {
            v452 = v128;
            v453 = v121;
            v446 = v97;
            v450 = v96;
            sub_140010850(v121);
            v96 = v450;
            v97 = v446;
            v121 = v453;
            v128 = v452;
            v129 = *(_WORD *)(v453 + 4);
          }
          dword_1411336B4 = *(unsigned __int16 *)(v121 + 6) >> v128;
          *(_WORD *)(v121 + 4) = dword_1411336B4 + v129;
          v130 = v559[3];
          if(v130 > 0x48) {
            qword_1411335C8 = (__int64)(v559 + 0x10000);
            v131 = (v130 < 0x1E0) + (v130 < 0x3D0) + 1;
            v132 = v559[65538];
            if(v132 > 0x8000u) {
              v437 = v131;
              v445 = v97;
              v449 = v96;
              sub_140010850((__int64)(v559 + 0x10000));
              v96 = v449;
              v97 = v445;
              v131 = v437;
              v132 = v559[65538];
            }
            dword_1411336A8 = v559[65539] >> v131;
            qword_1411335D0 = (__int64)(v559 - 0x10000);
            v559[65538] = dword_1411336A8 + v132;
            v133 = *(v559 - 65534);
            if(v133 > 0x8000u) {
              v436 = v131;
              v444 = v97;
              v448 = v96;
              sub_140010850((__int64)(v559 - 0x10000));
              v96 = v448;
              v97 = v444;
              v131 = v436;
              v133 = *(v559 - 65534);
            }
            dword_1411336AC = *(v559 - 65533) >> v131;
            *(v559 - 65534) = dword_1411336AC + v133;
          }
        }
        v134 = 60416LL * v97 / v96;
        dword_141133680 = v134;
        dword_14113367C = 60416;
        dword_14014ADA0 = v134;
        dword_14014ADA4 = 60416;
        v135 = &dword_1407A0720[0x100000 * (dword_14014AD68 < (unsigned int)dword_14014ADB8) + 0x80000 * (v73 == dword_14014AD70) + 0x20000 * dword_141133694 + 512 * dword_14014ADB4 + 2 * v75 + 2 * (unsigned __int64)((unsigned __int8)((unsigned int)dword_14014ADEC < 0x78) << 17)];
        v136 = *v135;
        qword_1411335F8 = (__int64)v135;
        v137 = v134 * (__int64)v136 / v135[1];
        v138 = dword_141133680;
        v139 = 1 - dword_141133680;
        if(v137 >= 1 - dword_141133680) {
          v139 = 0x40000;
          if(v137 < 0x40000)
            v139 = v137;
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
        v145 = *((unsigned __int8 *)xmmword_140028F00 + v75);
        dword_14113367C += v139;
        v146 = v139 + v138;
        dword_141133680 = v146;
        dword_14014ADA8 = dword_14113367C;
        v147 = ((17 * v146 < (unsigned int)dword_14113367C) << 13) + (((unsigned __int16)dword_14014ADE8 - (unsigned __int16)v73) & 0x1000) + 16 * (v73 == dword_14113369C) + 8 * (v73 == dword_14014AD70) + 4 * (v73 == dword_14014AD94) + (v73 == dword_14014AD84) + (((unsigned int)dword_14014ADF0 < 0x29) << 7) + dword_1411336D0 + (dword_1411336A0 & 0x800) + 2 * (v145 + (v73 == dword_14014AD90)) + 32 * (((unsigned int)dword_14014ADEC < 0xA800) + ((unsigned int)dword_14014ADEC < 0x600) + ((unsigned int)dword_14014ADEC < 0xD));
        v148 = &dword_140FA0820[2 * v147];
        v149 = *v148;
        qword_141133600 = (__int64)v148;
        v150 = (dword_14113367C - v146) * (__int64)v149 / dword_140FA0824[2 * v147];
        v151 = v146;
        v152 = v146 - dword_14113367C + 1;
        if(v150 >= v152) {
          v152 = 0x40000;
          if(v150 < 0x40000)
            v152 = v150;
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
        v76 = dword_14010A558[v75] == dword_141133664;
        v156 = qword_14002A150;
        *v148 = v153 + 2 * v146;
        dword_140FA0824[2 * v147] = v155 + 1;
        v157 = *(unsigned __int8 *)(v156 + (((_WORD)v73 - (_WORD)dword_14014AD7C) & 0x1FF));
        LODWORD(v156) = *(_DWORD *)(v156 + 512);
        v158 = qword_141133588 + *(_DWORD *)(v71 + 2) - qword_141133560 + 736;
        v159 = (unsigned __int8)byte_1400EA158[dword_14014ADF8];
        dword_14014ADAC = v154;
        v160 = 8 * (((unsigned int)v156 < 384 * v157) + ((unsigned int)v156 < 58 * v157) + ((unsigned int)v156 < 22 * v157));
        v161 = (v147 & 0x700) + dword_14113368C + (((unsigned int)dword_14014ADEC < 0x2C00) << 11) + 2 * (v73 == v159);
        v162 = 4 * (v158 < 0x2E0) + v76;
        v163 = &dword_141060920[2 * v162 + 2 * v161 + 2 * v160];
        v164 = *v163;
        qword_141133608 = (__int64)v163;
        v165 = (v154 - v151) * (__int64)v164 / dword_141060924[2 * v162 + 2 * v161 + 2 * v160];
        v166 = dword_141133680;
        v167 = dword_141133680 - dword_14113367C + 1;
        if(v165 >= v167) {
          v167 = 0x80000;
          if(v165 < 0x80000)
            v167 = v165;
        }
        v168 = *v163;
        v169 = v167 + dword_14113367C;
        dword_14113367C += v167;
        v170 = v163[1];
        if((int)abs32(v168) > 0x100000) {
          v168 >>= 1;
          *v163 = v168;
          v170 >>= v170 > 0x2000;
        }
        *v163 = v168 + v151;
        v171 = dword_141133670;
        v163[1] = v170 + 2;
        v172 = dword_141133710;
        v173 = v166 * (v171 / v169);
        dword_1411336D4 = v173;
        if(dword_141133710 >= v173) {
          v422 = qword_141133610;
          v172 = dword_141133710 - v173;
          v171 -= v173;
          dword_1411336E8 -= v71[1];
          dword_141133710 -= v173;
          dword_141133670 = v171;
          dword_14020F1FC[dword_14025F200] &= ~dword_14025F20C;
          dword_14021F1FC[dword_14025F208] &= ~dword_14025F20C;
          if(v422) {
            v3 = (unsigned __int8 *)qword_141133580;
            qword_141133610 = 0;
            dword_141133694 = 0;
          } else if((unsigned __int64)v71 <= qword_141133588 + (unsigned __int64)*((unsigned int *)v3 + 1)) {
            v3 = (unsigned __int8 *)qword_141133580;
          } else {
            v3 = (unsigned __int8 *)qword_141133580;
            dword_1411336C8 = 0x8000;
          }
        } else {
          v174 = qword_141133630;
          v175 = dword_141133700;
          v176 = dword_141133704;
          v177 = (_DWORD *)qword_141133628;
          v178 = dword_14014ADEC;
          *(_DWORD *)qword_141133630 += dword_141133700;
          *(_DWORD *)(v174 + 4) += v176;
          *v177 += v175;
          v179 = v3[1];
          v177[1] += v176;
          v180 = (v179 & 0x40) == 0 || v178 > 0xE00;
          v181 = (v178 > 0x4800) + (v178 > 0x380) + (v178 > 0x80) + v180 + 4;
          v3[1] = v179 & 0xF0;
          *((_WORD *)v3 + 1) += v181;
          v71[1] += v181;
          v182 = qword_141133588 + *((unsigned int *)v3 + 1);
          if(v71 == (unsigned __int8 *)v182) {
            v3 = (unsigned __int8 *)qword_141133580;
            if(qword_141133580 == qword_141133638)
              dword_141133694 = v169 < 2 * v166;
          } else {
            v568 = *(_WORD *)v71;
            v183 = *(_DWORD *)(v71 + 2);
            do {
              v184 = *((_DWORD *)v71 - 1);
              *(_WORD *)v71 = *((_WORD *)v71 - 3);
              *(_DWORD *)(v71 + 2) = v184;
              v71 -= 6;
            } while((unsigned __int64)v71 > v182);
            v3 = (unsigned __int8 *)qword_141133580;
            *(_WORD *)v71 = v568;
            *(_DWORD *)(v71 + 2) = v183;
          }
          v185 = v71[1];
          qword_141133610 = (__int64)v71;
          if(v185 > 244) {
            sub_14000B750(v574);
            v71 = (unsigned __int8 *)qword_141133610;
          }
          if(v71)
            goto LABEL_248;
        }
        if(!--v567) {
          v186 = dword_1411336E4;
          v187 = (_DWORD *)qword_1411335B0;
          v188 = qword_141133618;
          v189 = dword_1411336EC;
          v190 = *v3;
          v191 = *(unsigned __int16 *)(qword_1411335B0 + 6);
          *(_WORD *)(qword_1411335B0 + 4) -= v191;
          v192 = v186 / (v190 + 1);
          v193 = dword_1411336B8;
          *v187 += v192 * v191;
          v194 = qword_141133590;
          *(_DWORD *)v188 += v189 * v192;
          *(_WORD *)(v188 + 4) -= v189;
          v195 = qword_141133588;
          *(_DWORD *)v194 += v193 * v192;
          *(_WORD *)(v194 + 4) -= v193;
          v196 = (_DWORD *)qword_141133598;
          v197 = dword_1411336BC * v192;
          *(_WORD *)(qword_141133598 + 4) -= dword_1411336BC;
          v198 = dword_1411336C0;
          *v196 += v197;
          v199 = (_DWORD *)qword_1411335A0;
          v200 = v198 * v192;
          *(_WORD *)(qword_1411335A0 + 4) -= v198;
          v201 = qword_1411335A8;
          *v199 += v200;
          LODWORD(v202) = dword_1411336C4 * v192;
          *(_WORD *)(v201 + 4) -= dword_1411336C4;
          *(_DWORD *)v201 += v202;
          v203 = *v3;
          dword_1411336DC = v203;
          goto LABEL_126;
        }
        v67 = dword_1411336C8;
        v68 = dword_1411336CC;
        v569 = dword_141133674;
        v2 = dword_141133664;
        v570 = dword_141133678;
        v69 = (__int64 *)qword_141133620;
        v572 = dword_1411336A0;
        v70 = dword_1411336E8;
        v571 = dword_1411336F0;
        v573 = dword_1411336F4;
      }
    }
    v71 = v3 + 2;
    v357 = v3[3];
    qword_141133610 = (__int64)(v3 + 2);
    v358 = v357 == 1 && v353 < 4 * v350;
    v359 = (_DWORD *)qword_141133590;
    v360 = (_DWORD *)qword_141133598;
    v361 = (_DWORD *)qword_1411335A0;
    v362 = dword_1411336C0;
    v363 = (_DWORD *)qword_1411335A8;
    v364 = dword_1411336C4;
    dword_141133694 = 1;
    v365 = (v357 - 127 < 0) + v357 + v358;
    v366 = qword_1411335F0;
    v3[3] = v365;
    v367 = dword_1411336B8;
    v368 = dword_1411336BC;
    *(_DWORD *)v366 += 1568;
    LODWORD(v366) = dword_1411336C8;
    *v359 += v367;
    v369 = (_DWORD *)qword_1411335B0;
    *v360 += v368;
    v3 = (unsigned __int8 *)qword_141133580;
    *v361 += v362;
    *v363 += v364;
    *v369 += v366;
    *(_DWORD *)qword_1411335B8 += dword_1411336CC;
  LABEL_248:
    v370 = a1->_cnt - 1;
    a1->_cnt = v370;
    if(v370 < 0)
      flsbuf(*v71, a1);
    else
      *a1->_ptr++ = *v71;
    LODWORD(v202) = sub_140007B80(v3);
    for(m = dword_141133670; m < 0x1000000; dword_141133670 = m) {
      v372 = a2->_cnt - 1;
      a2->_cnt = v372;
      if(v372 < 0)
        LODWORD(v202) = filbuf(a2);
      else
        LODWORD(v202) = *(unsigned __int8 *)a2->_ptr++;
      v172 = v202 | (v172 << 8);
      dword_141133710 = v172;
      m <<= 8;
    }
    v2 = dword_141133664;
  } while(dword_141133664);
  return v202;
}
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
// 1405DFC20: using guessed type int dword_1405DFC20[];
// 1405DFC24: using guessed type __int16 word_1405DFC24[];
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
// 141133660: using guessed type int dword_141133660;
// 141133664: using guessed type int dword_141133664;
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
// 1411336A4: using guessed type int dword_1411336A4;
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
// 1411336F8: using guessed type __int64 qword_1411336F8;
// 141133700: using guessed type int dword_141133700;
// 141133704: using guessed type int dword_141133704;
// 141133708: using guessed type int dword_141133708;
// 14113370C: using guessed type int dword_14113370C;
// 141133710: using guessed type int dword_141133710;
// 141136BC4: using guessed type _BYTE algn_141136BC4[1084];

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
#undef dword_141133710
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
