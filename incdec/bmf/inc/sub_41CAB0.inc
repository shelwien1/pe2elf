// sub_41CAB0 @ 0x0041CAB0 — __userpurge
// Extracted from BMF.c:25681-28011 by extract.py per incdec.md.

typedef int t_sub_41CAB0_dword_439880[4];
static t_sub_41CAB0_dword_439880& __sub_41CAB0_dword_439880 = *(t_sub_41CAB0_dword_439880*)0x00439880;
typedef int t_sub_41CAB0_dword_439B7C;
static t_sub_41CAB0_dword_439B7C& __sub_41CAB0_dword_439B7C = *(t_sub_41CAB0_dword_439B7C*)0x00439B7C;
typedef int t_sub_41CAB0_dword_443388;
static t_sub_41CAB0_dword_443388& __sub_41CAB0_dword_443388 = *(t_sub_41CAB0_dword_443388*)0x00443388;
typedef int t_sub_41CAB0_dword_4458F0;
static t_sub_41CAB0_dword_4458F0& __sub_41CAB0_dword_4458F0 = *(t_sub_41CAB0_dword_4458F0*)0x004458F0;
typedef int t_sub_41CAB0_dword_4458F4;
static t_sub_41CAB0_dword_4458F4& __sub_41CAB0_dword_4458F4 = *(t_sub_41CAB0_dword_4458F4*)0x004458F4;
typedef int t_sub_41CAB0_n256_1;
static t_sub_41CAB0_n256_1& __sub_41CAB0_n256_1 = *(t_sub_41CAB0_n256_1*)0x00445708;
typedef __int128 t_sub_41CAB0_xmmword_439B40;
static t_sub_41CAB0_xmmword_439B40& __sub_41CAB0_xmmword_439B40 = *(t_sub_41CAB0_xmmword_439B40*)0x00439B40;
typedef __int128 t_sub_41CAB0_xmmword_441190;
static t_sub_41CAB0_xmmword_441190& __sub_41CAB0_xmmword_441190 = *(t_sub_41CAB0_xmmword_441190*)0x00441190;
typedef __int128 t_sub_41CAB0_xmmword_4411A0;
static t_sub_41CAB0_xmmword_4411A0& __sub_41CAB0_xmmword_4411A0 = *(t_sub_41CAB0_xmmword_4411A0*)0x004411A0;
typedef __int128 t_sub_41CAB0_xmmword_4411B0;
static t_sub_41CAB0_xmmword_4411B0& __sub_41CAB0_xmmword_4411B0 = *(t_sub_41CAB0_xmmword_4411B0*)0x004411B0;
typedef __int128 t_sub_41CAB0_xmmword_4411C0;
static t_sub_41CAB0_xmmword_4411C0& __sub_41CAB0_xmmword_4411C0 = *(t_sub_41CAB0_xmmword_4411C0*)0x004411C0;
typedef __int128 t_sub_41CAB0_xmmword_4411D0;
static t_sub_41CAB0_xmmword_4411D0& __sub_41CAB0_xmmword_4411D0 = *(t_sub_41CAB0_xmmword_4411D0*)0x004411D0;
typedef __int128 t_sub_41CAB0_xmmword_4411E0;
static t_sub_41CAB0_xmmword_4411E0& __sub_41CAB0_xmmword_4411E0 = *(t_sub_41CAB0_xmmword_4411E0*)0x004411E0;
typedef __int128 t_sub_41CAB0_xmmword_4411F0;
static t_sub_41CAB0_xmmword_4411F0& __sub_41CAB0_xmmword_4411F0 = *(t_sub_41CAB0_xmmword_4411F0*)0x004411F0;

static inline int __fwd_sub_41CAB0_sub_413430(void *a0, int a1) { return __sub_413430((unsigned __int16 *)a0, a1); }
#define sub_413430 __fwd_sub_41CAB0_sub_413430
static inline unsigned int __fwd_sub_41CAB0_sub_414800(void *a0) { return __sub_414800((unsigned __int16 *)a0); }
#define sub_414800 __fwd_sub_41CAB0_sub_414800

PROBE_DECL(__sub_41CAB0)
extern "C" BMF_SSE __attribute__((visibility("hidden"))) unsigned int __sub_41CAB0(int a1, const __m128 &a2__ref, int a3, unsigned __int8 a4, int a5)
{
  alignas(16) unsigned char __hexrays_frame[416];   // original frame, ebp-0x190..ebp+0x0
  int &n2 = *(int *)(__hexrays_frame + 0);
  unsigned __int16 * &n0xF0 = *(unsigned __int16 * *)(__hexrays_frame + 4);
  unsigned int &n0x10_2 = *(unsigned int *)(__hexrays_frame + 8);
  unsigned __int16 * &v508 = *(unsigned __int16 * *)(__hexrays_frame + 12);
  unsigned int &n0x10_1 = *(unsigned int *)(__hexrays_frame + 16);
  int &v510 = *(int *)(__hexrays_frame + 20);
  int &v511 = *(int *)(__hexrays_frame + 24);
  int &v512 = *(int *)(__hexrays_frame + 64);
  int &v513 = *(int *)(__hexrays_frame + 68);
  int &v514 = *(int *)(__hexrays_frame + 72);
  const char * &v515 = *(const char * *)(__hexrays_frame + 80);
  unsigned int &v516 = *(unsigned int *)(__hexrays_frame + 84);
  const char * &v517 = *(const char * *)(__hexrays_frame + 88);
  const char * &v518 = *(const char * *)(__hexrays_frame + 96);
  const char * &v519 = *(const char * *)(__hexrays_frame + 100);
  const char * &v520 = *(const char * *)(__hexrays_frame + 104);
  const char * &v521 = *(const char * *)(__hexrays_frame + 112);
  const char * &v522 = *(const char * *)(__hexrays_frame + 116);
  const char * &v523 = *(const char * *)(__hexrays_frame + 120);
  const char * &v524 = *(const char * *)(__hexrays_frame + 128);
  int &v525 = *(int *)(__hexrays_frame + 132);
  const char * &v526 = *(const char * *)(__hexrays_frame + 136);
  const char * &v527 = *(const char * *)(__hexrays_frame + 144);
  const char * &v528 = *(const char * *)(__hexrays_frame + 148);
  const char * &v529 = *(const char * *)(__hexrays_frame + 152);
  const char * &v530 = *(const char * *)(__hexrays_frame + 160);
  const char * &v531 = *(const char * *)(__hexrays_frame + 164);
  const char * &v532 = *(const char * *)(__hexrays_frame + 168);
  const char * &v533 = *(const char * *)(__hexrays_frame + 176);
  const char * &v534 = *(const char * *)(__hexrays_frame + 180);
  const char * &v535 = *(const char * *)(__hexrays_frame + 184);
  int &v536 = *(int *)(__hexrays_frame + 192);
  const char * &v537 = *(const char * *)(__hexrays_frame + 196);
  int &v538 = *(int *)(__hexrays_frame + 200);
  int &v539 = *(int *)(__hexrays_frame + 208);
  const char * &v540 = *(const char * *)(__hexrays_frame + 212);
  int &v541 = *(int *)(__hexrays_frame + 216);
  int &v542 = *(int *)(__hexrays_frame + 224);
  const char * &v543 = *(const char * *)(__hexrays_frame + 228);
  const char * &v544 = *(const char * *)(__hexrays_frame + 232);
  unsigned int &v545 = *(unsigned int *)(__hexrays_frame + 240);
  int &n3 = *(int *)(__hexrays_frame + 244);
  int &v547 = *(int *)(__hexrays_frame + 248);
  int &v548 = *(int *)(__hexrays_frame + 252);
  int &v549 = *(int *)(__hexrays_frame + 256);
  int &v550 = *(int *)(__hexrays_frame + 260);
  const char * &v551 = *(const char * *)(__hexrays_frame + 264);
  const char * &v552 = *(const char * *)(__hexrays_frame + 268);
  const char * &v553 = *(const char * *)(__hexrays_frame + 272);
  const char * &v554 = *(const char * *)(__hexrays_frame + 276);
  const char * &v555 = *(const char * *)(__hexrays_frame + 280);
  const char * &v556 = *(const char * *)(__hexrays_frame + 284);
  const char * &v557 = *(const char * *)(__hexrays_frame + 288);
  int &v558 = *(int *)(__hexrays_frame + 292);
  const char * &v559 = *(const char * *)(__hexrays_frame + 296);
  const char * &v560 = *(const char * *)(__hexrays_frame + 300);
  const char * &v561 = *(const char * *)(__hexrays_frame + 304);
  const char * &v562 = *(const char * *)(__hexrays_frame + 308);
  const char * &v563 = *(const char * *)(__hexrays_frame + 312);
  const char * &v564 = *(const char * *)(__hexrays_frame + 316);
  const char * &v565 = *(const char * *)(__hexrays_frame + 320);
  unsigned int &v566 = *(unsigned int *)(__hexrays_frame + 324);
  int &v567 = *(int *)(__hexrays_frame + 328);
  int &v568 = *(int *)(__hexrays_frame + 332);
  const char * &v569 = *(const char * *)(__hexrays_frame + 336);
  int &v570 = *(int *)(__hexrays_frame + 340);
  int &v571 = *(int *)(__hexrays_frame + 344);
  int &v572 = *(int *)(__hexrays_frame + 348);
  int &v573 = *(int *)(__hexrays_frame + 352);
  int &v574 = *(int *)(__hexrays_frame + 356);
  int &v575 = *(int *)(__hexrays_frame + 360);
  int &v576 = *(int *)(__hexrays_frame + 364);
  int &v577 = *(int *)(__hexrays_frame + 368);
  _DWORD * &v578 = *(_DWORD * *)(__hexrays_frame + 372);
  unsigned int &n5 = *(unsigned int *)(__hexrays_frame + 376);
  int &v580 = *(int *)(__hexrays_frame + 380);
  _DWORD * &v581 = *(_DWORD * *)(__hexrays_frame + 384);
  PROBE_HIT(__sub_41CAB0);
  __m128 a2 = a2__ref;
  int v6; // ecx
  _WORD *v7; // edx
  int v8; // ebx
  int v9; // ecx
  __int64 v10; // rax
  __int64 v11; // rax
  __int64 v12; // rax
  __int64 v13; // rax
  __int64 v14; // rax
  __m128 *v15; // edx
  float v16; // xmm4_4
  __m128 *v17; // eax
  float v18; // xmm1_4
  __m128 v19; // xmm6
  float v20; // xmm0_4
  float v21; // xmm2_4
  float v22; // xmm1_4
  float v23; // xmm4_4
  float v24; // xmm2_4
  __m128 n0x46D22000; // xmm1
  float v26; // xmm4_4
  __m128 v27; // xmm2
  __m128 n0x459D8800; // xmm5
  __m128 n0x3C54FDF4; // xmm0
  __m128 v30; // xmm2
  __m128 v31; // xmm2
  __m128 v32; // xmm1
  __m128 v33; // xmm1
  __m128 v34; // xmm0
  __m128 v35; // xmm0
  __m128 v36; // xmm6
  __m128 v37; // xmm6
  __m128 v38; // xmm5
  __m128 v39; // xmm5
  __m128 v40; // xmm7
  __m128 v41; // xmm7
  __m128 v42; // xmm7
  __m128 v43; // xmm7
  __m128 v44; // xmm7
  __m128 v45; // xmm7
  __m128 v46; // xmm7
  __m128 v47; // xmm7
  __m128 v48; // xmm7
  __m128 v49; // xmm7
  __m128 v50; // xmm7
  __m128 v51; // xmm7
  __m128 v52; // xmm7
  __m128 v53; // xmm7
  __m128 v54; // xmm7
  __m128 v55; // xmm7
  __m128 v56; // xmm0
  __m128 v57; // xmm1
  __m128 v58; // xmm3
  __m128 v59; // xmm3
  __m128 v60; // xmm3
  __m128 v61; // xmm0
  __m128 v62; // xmm1
  __m128 v63; // xmm1
  __m128 v64; // xmm0
  __m128 v65; // xmm0
  __m128 v66; // xmm6
  __m128 v67; // xmm5
  __m128 v68; // xmm4
  __m128 v69; // xmm3
  __m128 v70; // xmm6
  __m128 v71; // xmm5
  __m128 v72; // xmm3
  __m128 v73; // xmm1
  __m128 v74; // xmm3
  int v75; // edx
  _DWORD *v76; // ebx
  int v77; // eax
  unsigned int v78; // ecx
  int v79; // esi
  int v80; // esi
  int v81; // edx
  _BYTE *v82; // esi
  unsigned __int8 v83; // bl
  int v84; // eax
  int v85; // esi
  int v86; // ebx
  bool v87; // cc
  int v88; // esi
  int v89; // ebx
  char *v90; // ecx
  const char *v91; // eax
  unsigned int v92; // ebx
  const char *v93; // eax
  const char *v94; // edi
  int v95; // eax
  int v96; // edx
  unsigned int v97; // edi
  int v98; // edx
  int n2_1; // ecx
  int v100; // ebx
  int v101; // edx
  int v102; // ebx
  bool v103; // zf
  bool v104; // sf
  bool v105; // of
  int v106; // ecx
  const char *v107; // esi
  int v108; // eax
  unsigned int v109; // ebx
  const char *v110; // ecx
  const char *v111; // edx
  const char *v112; // ebx
  int v113; // edx
  char v114; // bl
  int v115; // edx
  char v116; // bl
  int v117; // ebx
  int v118; // esi
  int v119; // edx
  int v120; // ebx
  int v121; // eax
  int v122; // esi
  int v123; // edi
  int v124; // ebx
  int v125; // eax
  int v126; // eax
  int v127; // esi
  int v128; // ebx
  int v129; // edi
  int v130; // eax
  int v131; // edi
  int v132; // eax
  int v133; // edi
  int v134; // esi
  int v135; // esi
  int v136; // eax
  int v137; // edi
  int v138; // ebx
  int v139; // esi
  int v140; // ebx
  int v141; // esi
  int v142; // esi
  int v143; // eax
  int v144; // eax
  int v145; // esi
  int v146; // ebx
  int v147; // edi
  int v148; // eax
  int v149; // edi
  int v150; // eax
  int v151; // esi
  int v152; // edi
  int v153; // esi
  int v154; // eax
  int v155; // edi
  int v156; // ebx
  int v157; // esi
  int v158; // ebx
  int v159; // edi
  int v160; // ebx
  int v161; // eax
  int v162; // ebx
  int v163; // esi
  int v164; // edi
  int v165; // ebx
  int v166; // esi
  int v167; // ebx
  int v168; // eax
  int v169; // edi
  int v170; // ebx
  int v171; // eax
  int v172; // ebx
  int v173; // edi
  int v174; // eax
  int v175; // esi
  int v176; // edi
  int v177; // esi
  int v178; // edi
  int v179; // ebx
  int v180; // ebx
  int v181; // edi
  int v182; // esi
  int v183; // eax
  int v184; // ebx
  int v185; // eax
  int v186; // ebx
  int v187; // ebx
  int v188; // edi
  int v189; // edi
  int v190; // eax
  int v191; // ebx
  int v192; // edi
  int v193; // esi
  int v194; // edi
  int v195; // esi
  int v196; // eax
  int v197; // esi
  int v198; // esi
  int v199; // eax
  int v200; // edi
  int v201; // ebx
  int v202; // esi
  int v203; // edi
  int v204; // edx
  int v205; // ebx
  int v206; // eax
  int v207; // ebx
  int v208; // eax
  int v209; // edi
  int v210; // ebx
  int v211; // edx
  int v212; // edi
  int v213; // eax
  int v214; // eax
  int v215; // ecx
  int v216; // edi
  int v217; // edx
  int v218; // eax
  int v219; // edx
  int v220; // edi
  int v221; // eax
  int v222; // edi
  int v223; // edx
  int v224; // eax
  int v225; // esi
  int v226; // edx
  int v227; // esi
  int v228; // esi
  int v229; // edi
  int v230; // edi
  int v231; // edx
  int v232; // esi
  int v233; // eax
  int v234; // edi
  int v235; // ebx
  int v236; // eax
  int v237; // ebx
  int v238; // edx
  int v239; // edx
  int v240; // eax
  int v241; // ebx
  int v242; // esi
  int v243; // edx
  int v244; // edi
  int v245; // esi
  int v246; // eax
  int v247; // esi
  int v248; // edi
  int v249; // eax
  int v250; // esi
  int v251; // esi
  int v252; // edx
  int v253; // ebx
  int v254; // esi
  int v255; // edi
  int v256; // edx
  int v257; // ebx
  int v258; // edx
  int v259; // esi
  int v260; // ebx
  int v261; // edi
  int v262; // edx
  int v263; // eax
  int v264; // edi
  int v265; // eax
  int v266; // esi
  int v267; // esi
  int v268; // edi
  int v269; // eax
  int v270; // edx
  int v271; // esi
  int v272; // edx
  int v273; // eax
  int v274; // eax
  int v275; // edi
  int v276; // edi
  int v277; // edx
  int v278; // eax
  int v279; // ebx
  int v280; // edi
  int v281; // ebx
  int v282; // eax
  int v283; // edx
  int v284; // ecx
  int v285; // edx
  int v286; // eax
  int v287; // ebx
  int v288; // esi
  int v289; // ebx
  int v290; // ebx
  int v291; // esi
  int v292; // eax
  int v293; // ebx
  int v294; // esi
  int v295; // eax
  int v296; // esi
  int v297; // ebx
  int v298; // eax
  int v299; // edi
  int v300; // eax
  int v301; // edi
  int v302; // esi
  int v303; // edi
  int v304; // esi
  int v305; // eax
  int v306; // edi
  int v307; // edx
  int v308; // esi
  int v309; // ebx
  int v310; // eax
  int v311; // edi
  char v312; // si
  int v313; // ebx
  int v314; // esi
  int v315; // edi
  int v316; // esi
  int v317; // edx
  int v318; // esi
  int v319; // eax
  int v320; // esi
  int v321; // eax
  int v322; // edx
  int v323; // ebx
  int v324; // edx
  int v325; // edi
  int v326; // ebx
  int v327; // edi
  int v328; // esi
  int v329; // edi
  int v330; // ebx
  int v331; // eax
  int v332; // edi
  int v333; // ebx
  int v334; // eax
  int v335; // ebx
  int v336; // edi
  int v337; // esi
  int v338; // ebx
  int v339; // eax
  int v340; // esi
  int v341; // ebx
  int v342; // eax
  int v343; // eax
  int v344; // ebx
  int v345; // edx
  int v346; // edi
  int v347; // edi
  int v348; // eax
  int v349; // edi
  int v350; // ebx
  int v351; // eax
  int v352; // edi
  int v353; // eax
  int v354; // ebx
  int v355; // edi
  int v356; // edx
  int v357; // eax
  int v358; // edx
  int v359; // ebx
  int v360; // eax
  int v361; // ebx
  int v362; // edx
  int v363; // esi
  int v364; // ebx
  int v365; // eax
  int v366; // esi
  int v367; // ebx
  int v368; // eax
  int v369; // ebx
  int v370; // esi
  int v371; // edx
  int v372; // ebx
  int v373; // eax
  int v374; // edx
  int v375; // eax
  int v376; // ebx
  int v377; // edi
  int v378; // ebx
  int v379; // edi
  int v380; // edx
  int v381; // ebx
  int v382; // ebx
  int v383; // edi
  int v384; // ebx
  _DWORD *v385; // edi
  int v386; // esi
  unsigned __int16 *v387; // ebx
  unsigned int n0x10; // eax
  unsigned __int16 *v389; // edx
  int n15; // esi
  int v391; // eax
  int v392; // edx
  unsigned int v393; // eax
  int v394; // eax
  int v395; // edx
  unsigned int v396; // eax
  int v397; // edx
  int v398; // ebx
  int v399; // ecx
  int v400; // eax
  unsigned __int16 *n0x10_3; // ebx
  unsigned __int16 *n2_2; // ecx
  int v403; // edx
  int v404; // ebx
  unsigned int v405; // ebx
  int v406; // edx
  int v407; // ebx
  unsigned __int16 *v408; // ebx
  int v409; // ecx
  int v410; // edx
  unsigned __int16 *v411; // ebx
  int v412; // ebx
  int v413; // edx
  unsigned int v414; // edx
  int v415; // edx
  int v416; // ebx
  int v417; // edx
  int v418; // ebx
  int v419; // edx
  unsigned __int16 *v420; // ebx
  int v421; // ebx
  int v422; // edx
  int v423; // edx
  int v424; // ebx
  int v425; // edx
  int v426; // ebx
  int v427; // edx
  unsigned __int16 *v428; // ebx
  int v429; // ebx
  int v430; // edx
  int v431; // edx
  int v432; // ebx
  int v433; // edx
  int v434; // ebx
  int v435; // edx
  unsigned __int16 *v436; // ebx
  int v437; // ebx
  int v438; // edx
  int v439; // edx
  int v440; // ebx
  int v441; // edx
  int v442; // ebx
  int v443; // edx
  unsigned __int16 *v444; // ebx
  unsigned __int16 *v445; // ebx
  unsigned __int16 *n2_7; // edx
  int v447; // ebx
  int v448; // eax
  int v449; // ecx
  int v450; // ecx
  unsigned __int16 *n0x10_4; // eax
  unsigned __int16 *v452; // ebx
  int v453; // ebx
  int v454; // eax
  unsigned __int16 *n0xF0_5; // ebx
  unsigned __int16 *v456; // ebx
  unsigned __int16 *v457; // ebx
  unsigned __int16 *n2_6; // ecx
  int v459; // edx
  int v460; // ebx
  int v461; // ecx
  unsigned __int16 *n0xF0_4; // ebx
  unsigned __int16 *v463; // ebx
  int v464; // edx
  int v465; // ebx
  _WORD *v466; // ebx
  int v467; // edx
  int v468; // ebx
  unsigned __int16 *n2_5; // ecx
  int v470; // edx
  int v471; // ebx
  int v472; // ecx
  unsigned __int16 *n0xF0_3; // ebx
  unsigned __int16 *v474; // ebx
  int v475; // edx
  int v476; // ebx
  _WORD *v477; // ebx
  int v478; // edx
  int v479; // ebx
  unsigned __int16 *n2_4; // ecx
  int v481; // edx
  int v482; // ebx
  int v483; // ecx
  unsigned __int16 *n0xF0_2; // ebx
  unsigned __int16 *v485; // ebx
  int v486; // edx
  int v487; // ebx
  _WORD *v488; // ebx
  int v489; // edx
  int v490; // ebx
  unsigned __int16 *v491; // ecx
  int v492; // edx
  int v493; // ebx
  int v494; // ecx
  unsigned __int16 *n0xF0_1; // ebx
  unsigned __int16 *n2_3; // ebx
  int v497; // edx
  int v498; // ecx
  unsigned int v499; // ecx
  int v500; // edx
  int v501; // ebx
  _WORD *v502; // ebx
  int v503; // edx
  int v504; // ebx

  v6 = *(_DWORD *)(a1 + 278704) & 0xF;
  v7 = *(_WORD **)(a1 + 278736);
  v577 = 16 * a3;
  *v7 = 16 * a3;
  *(_WORD *)(*(_DWORD *)(a1 + 278736) + 2) = **(_WORD **)(a1 + 278736) - *(_WORD *)(*(_DWORD *)(a1 + 278736) + 2);
  *(_WORD *)(*(_DWORD *)(a1 + 278736) + 20) = 0;
  *(_BYTE *)(*(_DWORD *)(a1 + 278736) + 16) = (a5 <= (int)(((unsigned int)(6 - v6) >> 31)
                                                         + ((unsigned int)(4 - v6) >> 31)
                                                         + 2 * ((unsigned int)(9 - v6) >> 31)))
                                            + (a5 < (signed int)-(((unsigned int)(6 - v6) >> 31)
                                                                + ((unsigned int)(4 - v6) >> 31)
                                                                + 2 * ((unsigned int)(9 - v6) >> 31)));
  *(_BYTE *)(*(_DWORD *)(a1 + 278736) + 17) = abs32(a5);
  v8 = *(_DWORD *)(a1 + 278736);
  v9 = v577;
  a2.m128_f32[0] = (float)v577;
  v19 = a2;
  v10 = v577 - *(__int16 *)(v8 - 18);
  *(_WORD *)(v8 + 8) = (WORD2(v10) ^ v10) - WORD2(v10);
  v11 = v9 - **(__int16 **)(a1 + 278740);
  *(_WORD *)(*(_DWORD *)(a1 + 278736) + 10) = (WORD2(v11) ^ v11) - WORD2(v11);
  v12 = v9 - *(__int16 *)(*(_DWORD *)(a1 + 278740) - 18);
  *(_WORD *)(*(_DWORD *)(a1 + 278736) + 12) = (WORD2(v12) ^ v12) - WORD2(v12);
  v13 = v9 - *(__int16 *)(*(_DWORD *)(a1 + 278740) + 18);
  *(_WORD *)(*(_DWORD *)(a1 + 278736) + 14) = (WORD2(v13) ^ v13) - WORD2(v13);
  v14 = (__int16)(v9 - *(_WORD *)(a1 + 278700));
  *(_WORD *)(*(_DWORD *)(a1 + 278736) + 4) = v14;
  *(_WORD *)(*(_DWORD *)(a1 + 278736) + 6) = (WORD2(v14) ^ v14) - WORD2(v14);
  v15 = *(__m128 **)(a1 + 278656);
  v16 = v15[14].m128_f32[1] + 0.000099999997f;
  v17 = *(__m128 **)(*(_DWORD *)(a1 + 278668) - 4);
  v18 = *(float *)(a1 + 278648);
  n2 = *(int *)(a1 + 278640);
  v19.m128_f32[0] = a2.m128_f32[0] - v18;
  v20 = *(float *)(a1 + 278644);
  v21 = v20 - v18;
  v22 = (float)((float)((float)((float)(a2.m128_f32[0] - v18) * (float)(v20 - v18)) - v15[14].m128_f32[0]) * 0.001f)
      + v15[14].m128_f32[0];
  v23 = v16 + (float)((float)((float)(v21 * v21) - v15[14].m128_f32[1]) * 0.001f);
  v15[14].m128_f32[1] = v23;
  v24 = 0.1f * v23;
  if ( (float)(0.1f * v23) <= v22 )
    v24 = fminf(v23, v22);
  v15[14].m128_f32[0] = v24;
  n0x46D22000 = (__m128)0x46D22000u;
  n0x46D22000.m128_f32[0] = 26896.0f * v15[14].m128_f32[2];
  v26 = (float)(1.0f - (float)(v24 / (float)(v23 + 576.0f))) * 2.0f;
  v27 = a2;
  v19.m128_f32[0] = v19.m128_f32[0] * v26;
  n0x459D8800 = (__m128)0x459D8800u;
  n0x459D8800.m128_f32[0] = 5041.0f * v17[14].m128_f32[2];
  v27.m128_f32[0] = (float)(a2.m128_f32[0] - v20) * 2.5999999f;
  n0x3C54FDF4 = (__m128)0x3C54FDF4u;
  n0x3C54FDF4.m128_f32[0] = 0.013f * v26;
  v30 = _mm_unpacklo_ps(v27, v27);
  v31 = _mm_movelh_ps(v30, v30);
  v32 = _mm_unpacklo_ps(n0x46D22000, n0x46D22000);
  v33 = _mm_movelh_ps(v32, v32);
  v34 = _mm_unpacklo_ps(n0x3C54FDF4, n0x3C54FDF4);
  v35 = _mm_movelh_ps(v34, v34);
  v36 = _mm_unpacklo_ps(v19, v19);
  v37 = _mm_movelh_ps(v36, v36);
  v38 = _mm_unpacklo_ps(n0x459D8800, n0x459D8800);
  v39 = _mm_movelh_ps(v38, v38);
  v40 = *(__m128 *)(a1 + 278528);
  n0xF0 = (unsigned __int16 *)a2.m128_i32[0];
  v41 = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(_mm_mul_ps(v40, v40), v15[7]), (__m128)__sub_41CAB0_xmmword_439B40), v15[7]);
  v15[7] = v41;
  *v15 = _mm_add_ps(
           _mm_div_ps(
             _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_441190, v31), *(__m128 *)(a1 + 278528)),
             _mm_add_ps(v41, v33)),
           *v15);
  v42 = *(__m128 *)(a1 + 278528);
  n5 = 0;
  v43 = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(_mm_mul_ps(v42, v42), v17[7]), v35), v17[7]);
  v577 = v9;
  v17[7] = v43;
  *v17 = _mm_add_ps(
           _mm_div_ps(
             _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_441190, v37), *(__m128 *)(a1 + 278528)),
             _mm_add_ps(v43, v39)),
           *v17);
  v44 = *(__m128 *)(a1 + 278544);
  v578 = (_DWORD *)a1;
  v45 = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(_mm_mul_ps(v44, v44), v15[8]), (__m128)__sub_41CAB0_xmmword_439B40), v15[8]);
  v15[8] = v45;
  v15[1] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411A0, v31), *(__m128 *)(a1 + 278544)),
               _mm_add_ps(v45, v33)),
             v15[1]);
  v46 = _mm_add_ps(
          _mm_mul_ps(_mm_sub_ps(_mm_mul_ps(*(__m128 *)(a1 + 278544), *(__m128 *)(a1 + 278544)), v17[8]), v35),
          v17[8]);
  v17[8] = v46;
  v17[1] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411A0, v37), *(__m128 *)(a1 + 278544)),
               _mm_add_ps(v46, v39)),
             v17[1]);
  v47 = _mm_add_ps(
          _mm_mul_ps(
            _mm_sub_ps(_mm_mul_ps(*(__m128 *)(a1 + 278560), *(__m128 *)(a1 + 278560)), v15[9]),
            (__m128)__sub_41CAB0_xmmword_439B40),
          v15[9]);
  v15[9] = v47;
  v15[2] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411B0, v31), *(__m128 *)(a1 + 278560)),
               _mm_add_ps(v47, v33)),
             v15[2]);
  v48 = _mm_add_ps(
          _mm_mul_ps(_mm_sub_ps(_mm_mul_ps(*(__m128 *)(a1 + 278560), *(__m128 *)(a1 + 278560)), v17[9]), v35),
          v17[9]);
  v17[9] = v48;
  v17[2] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411B0, v37), *(__m128 *)(a1 + 278560)),
               _mm_add_ps(v48, v39)),
             v17[2]);
  v49 = _mm_add_ps(
          _mm_mul_ps(
            _mm_sub_ps(_mm_mul_ps(*(__m128 *)(a1 + 278576), *(__m128 *)(a1 + 278576)), v15[10]),
            (__m128)__sub_41CAB0_xmmword_439B40),
          v15[10]);
  v15[10] = v49;
  v15[3] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411C0, v31), *(__m128 *)(a1 + 278576)),
               _mm_add_ps(v49, v33)),
             v15[3]);
  v50 = _mm_add_ps(
          _mm_mul_ps(_mm_sub_ps(_mm_mul_ps(*(__m128 *)(a1 + 278576), *(__m128 *)(a1 + 278576)), v17[10]), v35),
          v17[10]);
  v17[10] = v50;
  v17[3] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411C0, v37), *(__m128 *)(a1 + 278576)),
               _mm_add_ps(v50, v39)),
             v17[3]);
  v51 = _mm_add_ps(
          _mm_mul_ps(
            _mm_sub_ps(_mm_mul_ps(*(__m128 *)(a1 + 278592), *(__m128 *)(a1 + 278592)), v15[11]),
            (__m128)__sub_41CAB0_xmmword_439B40),
          v15[11]);
  v15[11] = v51;
  v15[4] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411D0, v31), *(__m128 *)(a1 + 278592)),
               _mm_add_ps(v51, v33)),
             v15[4]);
  v52 = _mm_add_ps(
          _mm_mul_ps(_mm_sub_ps(_mm_mul_ps(*(__m128 *)(a1 + 278592), *(__m128 *)(a1 + 278592)), v17[11]), v35),
          v17[11]);
  v17[11] = v52;
  v17[4] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411D0, v37), *(__m128 *)(a1 + 278592)),
               _mm_add_ps(v52, v39)),
             v17[4]);
  v53 = _mm_add_ps(
          _mm_mul_ps(
            _mm_sub_ps(_mm_mul_ps(*(__m128 *)(a1 + 278608), *(__m128 *)(a1 + 278608)), v15[12]),
            (__m128)__sub_41CAB0_xmmword_439B40),
          v15[12]);
  v15[12] = v53;
  v15[5] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411E0, v31), *(__m128 *)(a1 + 278608)),
               _mm_add_ps(v53, v33)),
             v15[5]);
  v54 = _mm_add_ps(
          _mm_mul_ps(_mm_sub_ps(_mm_mul_ps(*(__m128 *)(a1 + 278608), *(__m128 *)(a1 + 278608)), v17[12]), v35),
          v17[12]);
  v17[12] = v54;
  v17[5] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411E0, v37), *(__m128 *)(a1 + 278608)),
               _mm_add_ps(v54, v39)),
             v17[5]);
  v55 = _mm_add_ps(
          _mm_mul_ps(
            _mm_sub_ps(_mm_mul_ps(*(__m128 *)(a1 + 278624), *(__m128 *)(a1 + 278624)), v15[13]),
            (__m128)__sub_41CAB0_xmmword_439B40),
          v15[13]);
  v15[13] = v55;
  v15[6] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411F0, v31), *(__m128 *)(a1 + 278624)),
               _mm_add_ps(v55, v33)),
             v15[6]);
  v56 = _mm_add_ps(
          _mm_mul_ps(v35, _mm_sub_ps(_mm_mul_ps(*(__m128 *)(a1 + 278624), *(__m128 *)(a1 + 278624)), v17[13])),
          v17[13]);
  v17[13] = v56;
  v17[6] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411F0, v37), *(__m128 *)(a1 + 278624)),
               _mm_add_ps(v56, v39)),
             v17[6]);
  v57 = (__m128)(unsigned int)n0xF0;
  v58 = _mm_add_ps(
          _mm_add_ps(
            _mm_add_ps(
              _mm_add_ps(
                _mm_add_ps(
                  _mm_add_ps(_mm_mul_ps(*v15, *(__m128 *)(a1 + 278528)), _mm_mul_ps(v15[1], *(__m128 *)(a1 + 278544))),
                  _mm_mul_ps(v15[2], *(__m128 *)(a1 + 278560))),
                _mm_mul_ps(v15[3], *(__m128 *)(a1 + 278576))),
              _mm_mul_ps(v15[4], *(__m128 *)(a1 + 278592))),
            _mm_mul_ps(v15[5], *(__m128 *)(a1 + 278608))),
          _mm_mul_ps(v15[6], *(__m128 *)(a1 + 278624)));
  v59 = _mm_add_ps(v58, _mm_movehl_ps(v58, v58));
  v31.m128_f32[0] = *(float *)&n2 + (float)(v59.m128_f32[0] + COERCE_FLOAT(_mm_shuffle_ps(v59, v59, 1)));
  v60 = v15[9];
  v57.m128_f32[0] = *(float *)&n0xF0 - v31.m128_f32[0];
  v31.m128_i32[0] = v15[14].m128_i32[2];
  v61 = (__m128)v31.m128_u32[0];
  v61.m128_f32[0] = v31.m128_f32[0] * 529.0f;
  v62 = _mm_unpacklo_ps(v57, v57);
  v63 = _mm_movelh_ps(v62, v62);
  v64 = _mm_unpacklo_ps(v61, v61);
  v65 = _mm_movelh_ps(v64, v64);
  v66 = _mm_add_ps(v15[8], v65);
  *v15 = _mm_add_ps(
           _mm_div_ps(
             _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_441190, v63), *(__m128 *)(a1 + 278528)),
             _mm_add_ps(v15[7], v65)),
           *v15);
  v67 = v15[10];
  v15[1] = _mm_add_ps(
             _mm_div_ps(_mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411A0, v63), *(__m128 *)(a1 + 278544)), v66),
             v15[1]);
  v68 = _mm_div_ps(_mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411B0, v63), *(__m128 *)(a1 + 278560)), _mm_add_ps(v60, v65));
  v69 = v15[11];
  v15[2] = _mm_add_ps(v68, v15[2]);
  v70 = _mm_div_ps(_mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411C0, v63), *(__m128 *)(a1 + 278576)), _mm_add_ps(v67, v65));
  v71 = v15[12];
  v15[3] = _mm_add_ps(v70, v15[3]);
  v15[4] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411D0, v63), *(__m128 *)(a1 + 278592)),
               _mm_add_ps(v69, v65)),
             v15[4]);
  v15[5] = _mm_add_ps(
             _mm_div_ps(
               _mm_mul_ps(_mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411E0, v63), *(__m128 *)(a1 + 278608)),
               _mm_add_ps(v71, v65)),
             v15[5]);
  v72 = _mm_mul_ps((__m128)__sub_41CAB0_xmmword_4411F0, v63);
  v73 = v15[13];
  v74 = _mm_mul_ps(v72, *(__m128 *)(a1 + 278624));
  ++v15[15].m128_i32[0];
  v15[6] = _mm_add_ps(_mm_div_ps(v74, _mm_add_ps(v73, v65)), v15[6]);
  v15[14].m128_f32[2] = v31.m128_f32[0] + (float)((float)(10.0f - v31.m128_f32[0]) * 0.00019999999f);
  **(_DWORD **)(a1 + 278668) = *(_DWORD *)(a1 + 278656);
  *(_DWORD *)(a1 + 278668) += 4;
  *(_DWORD *)(a1 + 278672) += 4;
  do
  {
    v75 = v578[n5 + 69669];
    v76 = &v578[v75];
    v77 = v577 - v578[2 * n5 + 69726];
    v581 = v76;
    v78 = n5 << 17;
    v79 = v77 + HIWORD(v76[0x8000 * n5 + 71178]);
    *(_WORD *)((char *)v76 + v78 + 284714) = v79;
    v580 = *((unsigned __int8 *)v76 + v78 + 284713);
    if ( v580 )
    {
      v576 = v75;
      v80 = v79 + 4 * ((v77 > __sub_41CAB0_dword_4458F0) - (v77 < __sub_41CAB0_dword_4458F4));
      *(_WORD *)((char *)v581 + v78 + 284714) = v80;
      v575 = v80;
      v81 = v576;
      if ( (int)abs32(v77) < 38 )
      {
        if ( (_BYTE)--v580 )
        {
          *((_BYTE *)v581 + v78 + 284713) = v580;
        }
        else
        {
          v82 = (_BYTE *)v581;
          if ( *((unsigned __int8 *)v581 + v78 + 284712) < 8u )
          {
            v83 = *((_BYTE *)v581 + v78 + 284712) + 1;
            *((_BYTE *)v581 + v78 + 284712) = v83;
            v82[v78 + 284713] = *((_BYTE *)&__sub_41CAB0_dword_439B7C + v83 + 3);
            *(_WORD *)&v82[v78 + 284714] = 2 * v575;
          }
          else
          {
            *((_BYTE *)v581 + v78 + 284713) = v580;
          }
        }
      }
      if ( !__sub_41CAB0_dword_443388 )
      {
        _mm_prefetch((const char *)&n2, 1);
        n2 = (int)&v578[(v81 ^ 0x7FF0) + 71178] + v78;
        v84 = v578[2 * n5 + 69727] + v77;
        n3 = v81 & 3;
        if ( (unsigned int)n3 >= 3
          || (v545 = v78,
              v576 = v81,
              v85 = *(__int16 *)((char *)v581 + v78 + 284718),
              v86 = v84 - ((v85 + (1 << ((*((_BYTE *)v581 + v78 + 284716) + 31) & 31))) >> *((_BYTE *)v581 + v78 + 284716)),
              v87 = n3 <= 0,
              *(_WORD *)((char *)v581 + v78 + 284718) = v85
                                                      + ((32
                                                        * ((v86 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v86 < __sub_41CAB0_dword_4458F4))
                                                        + v86
                                                        + 1) >> 1),
              v81 = v576,
              !v87) )
        {
          v545 = v78;
          v576 = v81;
          v88 = *(__int16 *)((char *)v581 + v78 + 284710);
          v89 = v84 - ((v88 + (1 << ((*((_BYTE *)v581 + v78 + 284708) + 31) & 31))) >> *((_BYTE *)v581 + v78 + 284708));
          *(_WORD *)((char *)v581 + v78 + 284710) = v88
                                                  + ((32 * ((v89 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v89 < __sub_41CAB0_dword_4458F4))
                                                    + v89
                                                    + 2) >> 2);
          v81 = v576;
        }
        v90 = (char *)v578 + v78;
        v550 = v84;
        _mm_prefetch(&v90[4 * (v81 ^ 0x4000) + 284712], 1);
        v542 = (int)&v90[4 * (v81 ^ 0x4000) + 284712];
        v544 = &v90[4 * (v81 ^ 0x3FF0) + 284712];
        _mm_prefetch(v544, 1);
        v543 = &v90[4 * *(int *)((char *)__sub_41CAB0_dword_439880 + ((v81 ^ 0x4000) & 0xC))
                  + 284712
                  + 4 * ((v81 ^ 0x4000) & 0xFFFFFFF3)];
        _mm_prefetch(v543, 1);
        _mm_prefetch(&v90[4 * (v81 ^ 0x2000) + 284712], 1);
        v539 = (int)&v90[4 * (v81 ^ 0x2000) + 284712];
        _mm_prefetch(&v90[4 * (v81 ^ 0x5FF0) + 284712], 1);
        v541 = (int)&v90[4 * (v81 ^ 0x5FF0) + 284712];
        v540 = &v90[4 * *(int *)((char *)__sub_41CAB0_dword_439880 + ((v81 ^ 0x2000) & 0xC))
                  + 284712
                  + 4 * ((v81 ^ 0x2000) & 0xFFFFFFF3)];
        _mm_prefetch(v540, 1);
        _mm_prefetch(&v90[4 * (v81 ^ 0x1000) + 284712], 1);
        v536 = (int)&v90[4 * (v81 ^ 0x1000) + 284712];
        _mm_prefetch(&v90[4 * (v81 ^ 0x6FF0) + 284712], 1);
        v538 = (int)&v90[4 * (v81 ^ 0x6FF0) + 284712];
        v537 = &v90[4 * *(int *)((char *)__sub_41CAB0_dword_439880 + ((v81 ^ 0x1000) & 0xC))
                  + 284712
                  + 4 * ((v81 ^ 0x1000) & 0xFFFFFFF3)];
        _mm_prefetch(v537, 1);
        v551 = &v90[4 * (v81 ^ 0x800) + 284712];
        v533 = v551;
        v535 = &v90[4 * (v81 ^ 0x77F0) + 284712];
        v534 = &v90[4 * *(int *)((char *)__sub_41CAB0_dword_439880 + ((v81 ^ 0x800) & 0xC))
                  + 284712
                  + 4 * ((v81 ^ 0x800) & 0xFFFFFFF3)];
        v552 = &v90[4 * (v81 ^ 0x400) + 284712];
        v530 = v552;
        _mm_prefetch(v551, 1);
        _mm_prefetch(v535, 1);
        _mm_prefetch(v534, 1);
        v553 = &v90[4 * (v81 ^ 0x7BF0) + 284712];
        v532 = v553;
        v531 = &v90[4 * *(int *)((char *)__sub_41CAB0_dword_439880 + ((v81 ^ 0x400) & 0xC))
                  + 284712
                  + 4 * ((v81 ^ 0x400) & 0xFFFFFFF3)];
        v554 = &v90[4 * (v81 ^ 0x200) + 284712];
        v527 = v554;
        _mm_prefetch(v552, 1);
        v555 = &v90[4 * (v81 ^ 0x7DF0) + 284712];
        v529 = v555;
        v91 = &v90[4 * *(int *)((char *)__sub_41CAB0_dword_439880 + ((v81 ^ 0x200) & 0xC))
                 + 284712
                 + 4 * ((v81 ^ 0x200) & 0xFFFFFFF3)];
        _mm_prefetch(v553, 1);
        _mm_prefetch(v531, 1);
        v528 = v91;
        v556 = &v90[4 * (v81 ^ 0x100) + 284712];
        v524 = v556;
        v92 = *(int *)((char *)__sub_41CAB0_dword_439880 + ((v81 ^ 0x100) & 0xC)) + ((v81 ^ 0x100) & 0xFFFFFFF3);
        v557 = &v90[4 * (v81 ^ 0x7EF0) + 284712];
        v526 = v557;
        _mm_prefetch(v554, 1);
        v558 = (int)&v90[4 * v92 + 284712];
        v525 = v558;
        v559 = &v90[4 * (v81 ^ 0x80) + 284712];
        v521 = v559;
        _mm_prefetch(v555, 1);
        _mm_prefetch(v91, 1);
        v523 = &v90[4 * (v81 ^ 0x7F70) + 284712];
        v560 = &v90[4 * *(int *)((char *)__sub_41CAB0_dword_439880 + ((v81 ^ 0x80) & 0xC)) + 284712 + 4 * ((v81 ^ 0x80) & 0xFFFFFFF3)];
        v522 = v560;
        v561 = &v90[4 * (v81 ^ 0x40) + 284712];
        v518 = v561;
        _mm_prefetch(v556, 1);
        v562 = &v90[4 * (v81 ^ 0x7FB0) + 284712];
        v520 = v562;
        v93 = &v90[4 * *(int *)((char *)__sub_41CAB0_dword_439880 + ((v81 ^ 0x40) & 0xC)) + 284712 + 4 * ((v81 ^ 0x40) & 0xFFFFFFF3)];
        v94 = (const char *)v558;
        _mm_prefetch(v557, 1);
        _mm_prefetch(v94, 1);
        v563 = v93;
        v519 = v93;
        v95 = v81 ^ 0x20;
        v96 = v81 ^ 0x10;
        v564 = &v90[4 * v95 + 284712];
        v515 = v564;
        v565 = &v90[4 * (v95 ^ 0x7FF0) + 284712];
        v517 = v565;
        _mm_prefetch(v559, 1);
        _mm_prefetch(v523, 1);
        v566 = (unsigned int)&v90[4 * *(int *)((char *)__sub_41CAB0_dword_439880 + (v95 & 0xC)) + 284712 + 4 * (v95 & 0xFFFFFFF3)];
        v516 = v566;
        v567 = (int)&v90[4 * v96 + 284712];
        v512 = v567;
        v97 = *(int *)((char *)__sub_41CAB0_dword_439880 + (v96 & 0xC)) + (v96 & 0xFFFFFFF3);
        v568 = (int)&v90[4 * (v96 ^ 0x7FF0) + 284712];
        v514 = v568;
        _mm_prefetch(v560, 1);
        v98 = (int)&v90[4 * v97 + 284712];
        n2_1 = n2;
        v569 = (const char *)v98;
        v100 = -v550;
        v513 = v98;
        LOBYTE(v97) = *(_BYTE *)n2;
        _mm_prefetch(v561, 1);
        v101 = *(__int16 *)(n2_1 + 2);
        _mm_prefetch(v562, 1);
        v102 = v100 - ((v101 + (1 << ((v97 + 31) & 31))) >> v97);
        v105 = __OFSUB__(v102, __sub_41CAB0_dword_4458F0);
        v103 = v102 == __sub_41CAB0_dword_4458F0;
        v104 = v102 - __sub_41CAB0_dword_4458F0 < 0;
        _mm_prefetch(v563, 1);
        v106 = 32 * (!(v104 ^ v105 | v103) - (v102 < __sub_41CAB0_dword_4458F4));
        _mm_prefetch(v564, 1);
        _mm_prefetch(v565, 1);
        v107 = v569;
        v108 = v550;
        v109 = v106 + v102 + 2;
        v110 = (const char *)v567;
        LOWORD(v109) = v101 + (v109 >> 2);
        v87 = n3 < 3;
        v111 = (const char *)v566;
        *(_WORD *)(n2 + 2) = v109;
        v112 = (const char *)v568;
        _mm_prefetch(v111, 1);
        _mm_prefetch(v110, 1);
        _mm_prefetch(v112, 1);
        _mm_prefetch(v107, 1);
        if ( v87
          && (v113 = *(__int16 *)(n2 + 6),
              v114 = *(_BYTE *)(n2 + 4),
              v550 = v108,
              v87 = n3 <= 0,
              *(_WORD *)(n2 + 6) = ((unsigned int)(-v108 - ((v113 + (1 << ((v114 + 31) & 31))) >> v114) + 2) >> 2) + v113,
              v87) )
        {
          v311 = *(__int16 *)(v542 + 2);
          v312 = *(_BYTE *)v542;
          v550 = v108;
          v313 = v108 - ((v311 + (1 << ((v312 + 31) & 31))) >> v312);
          *(_WORD *)(v542 + 2) = v311
                               + ((32 * ((v313 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v313 < __sub_41CAB0_dword_4458F4)) + v313 + 2) >> 2);
          v314 = *((__int16 *)v543 + 1);
          v315 = v108 - ((v314 + (1 << ((*v543 + 31) & 31))) >> *v543);
          *((_WORD *)v543 + 1) = v314
                               + ((32 * ((v315 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v315 < __sub_41CAB0_dword_4458F4)) + v315 + 4) >> 3);
          v316 = *(__int16 *)(v542 + 6);
          v317 = (v316 + (1 << ((*(_BYTE *)(v542 + 4) + 31) & 31))) >> *(_BYTE *)(v542 + 4);
          v549 = -v108;
          *(_WORD *)(v542 + 6) = ((unsigned int)(v108 - v317 + 2) >> 2) + v316;
          v318 = *((__int16 *)v544 + 1);
          v319 = -v108 - ((v318 + (1 << ((*v544 + 31) & 31))) >> *v544);
          *((_WORD *)v544 + 1) = v318
                               + ((32 * ((v319 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v319 < __sub_41CAB0_dword_4458F4)) + v319 + 4) >> 3);
          v320 = *(__int16 *)(v539 + 2);
          v321 = v550;
          v322 = v550 - ((v320 + (1 << ((*(_BYTE *)v539 + 31) & 31))) >> *(_BYTE *)v539);
          *(_WORD *)(v539 + 2) = v320
                               + ((32 * ((v322 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v322 < __sub_41CAB0_dword_4458F4)) + v322 + 2) >> 2);
          v323 = *((__int16 *)v540 + 1);
          v324 = v321 - ((v323 + (1 << ((*v540 + 31) & 31))) >> *v540);
          *((_WORD *)v540 + 1) = v323
                               + ((32 * ((v324 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v324 < __sub_41CAB0_dword_4458F4)) + v324 + 4) >> 3);
          *(_WORD *)(v539 + 6) += (unsigned int)(v321
                                               - ((*(__int16 *)(v539 + 6) + (1 << ((*(_BYTE *)(v539 + 4) + 31) & 31))) >> *(_BYTE *)(v539 + 4))
                                               + 2) >> 2;
          v325 = *(__int16 *)(v541 + 2);
          v326 = v549 - ((v325 + (1 << ((*(_BYTE *)v541 + 31) & 31))) >> *(_BYTE *)v541);
          *(_WORD *)(v541 + 2) = v325
                               + ((32 * ((v326 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v326 < __sub_41CAB0_dword_4458F4)) + v326 + 4) >> 3);
          v327 = *(__int16 *)(v536 + 2);
          v328 = v550 - ((v327 + (1 << ((*(_BYTE *)v536 + 31) & 31))) >> *(_BYTE *)v536);
          *(_WORD *)(v536 + 2) = v327
                               + ((32 * ((v328 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v328 < __sub_41CAB0_dword_4458F4)) + v328 + 2) >> 2);
          v329 = *((__int16 *)v537 + 1);
          v330 = v550 - ((v329 + (1 << ((*v537 + 31) & 31))) >> *v537);
          *((_WORD *)v537 + 1) = v329
                               + ((32 * ((v330 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v330 < __sub_41CAB0_dword_4458F4)) + v330 + 4) >> 3);
          *(_WORD *)(v536 + 6) += (unsigned int)(v550
                                               - ((*(__int16 *)(v536 + 6) + (1 << ((*(_BYTE *)(v536 + 4) + 31) & 31))) >> *(_BYTE *)(v536 + 4))
                                               + 2) >> 2;
          v331 = *(__int16 *)(v538 + 2);
          v332 = v549 - ((v331 + (1 << ((*(_BYTE *)v538 + 31) & 31))) >> *(_BYTE *)v538);
          *(_WORD *)(v538 + 2) = v331
                               + ((32 * ((v332 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v332 < __sub_41CAB0_dword_4458F4)) + v332 + 4) >> 3);
          v333 = *((__int16 *)v533 + 1);
          v334 = v550 - ((v333 + (1 << ((*v533 + 31) & 31))) >> *v533);
          *((_WORD *)v533 + 1) = v333
                               + ((32 * ((v334 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v334 < __sub_41CAB0_dword_4458F4)) + v334 + 2) >> 2);
          v335 = *((__int16 *)v534 + 1);
          v336 = v550 - ((v335 + (1 << ((*v534 + 31) & 31))) >> *v534);
          *((_WORD *)v534 + 1) = v335
                               + ((32 * ((v336 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v336 < __sub_41CAB0_dword_4458F4)) + v336 + 4) >> 3);
          *((_WORD *)v533 + 3) += (unsigned int)(v550 - ((*((__int16 *)v533 + 3) + (1 << ((v533[4] + 31) & 31))) >> v533[4]) + 2) >> 2;
          v337 = *((__int16 *)v535 + 1);
          v338 = v549 - ((v337 + (1 << ((*v535 + 31) & 31))) >> *v535);
          *((_WORD *)v535 + 1) = v337
                               + ((32 * ((v338 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v338 < __sub_41CAB0_dword_4458F4)) + v338 + 4) >> 3);
          v339 = *((__int16 *)v530 + 1);
          v340 = v550 - ((v339 + (1 << ((*v530 + 31) & 31))) >> *v530);
          *((_WORD *)v530 + 1) = v339
                               + ((32 * ((v340 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v340 < __sub_41CAB0_dword_4458F4)) + v340 + 2) >> 2);
          v341 = *((__int16 *)v531 + 1);
          v342 = v550 - ((v341 + (1 << ((*v531 + 31) & 31))) >> *v531);
          *((_WORD *)v531 + 1) = v341
                               + ((32 * ((v342 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v342 < __sub_41CAB0_dword_4458F4)) + v342 + 4) >> 3);
          v343 = v550;
          *((_WORD *)v530 + 3) += (unsigned int)(v550 - ((*((__int16 *)v530 + 3) + (1 << ((v530[4] + 31) & 31))) >> v530[4]) + 2) >> 2;
          v344 = *((__int16 *)v532 + 1);
          v549 -= (v344 + (1 << ((*v532 + 31) & 31))) >> *v532;
          v550 = v343;
          *((_WORD *)v532 + 1) = v344
                               + ((32 * ((v549 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v549 < __sub_41CAB0_dword_4458F4)) + v549 + 4) >> 3);
          v345 = *((__int16 *)v527 + 1);
          v346 = v550 - ((v345 + (1 << ((*v527 + 31) & 31))) >> *v527);
          *((_WORD *)v527 + 1) = v345
                               + ((32 * ((v346 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v346 < __sub_41CAB0_dword_4458F4)) + v346 + 2) >> 2);
          v347 = *((__int16 *)v528 + 1);
          v348 = v550 - ((v347 + (1 << ((*v528 + 31) & 31))) >> *v528);
          *((_WORD *)v528 + 1) = v347
                               + ((32 * ((v348 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v348 < __sub_41CAB0_dword_4458F4)) + v348 + 4) >> 3);
          v349 = v550;
          *((_WORD *)v527 + 3) += (unsigned int)(v550 - ((*((__int16 *)v527 + 3) + (1 << ((v527[4] + 31) & 31))) >> v527[4]) + 2) >> 2;
          v350 = *((__int16 *)v529 + 1);
          LOBYTE(v345) = *v529;
          v548 = -v349;
          v351 = -v349 - ((v350 + (1 << ((v345 + 31) & 31))) >> v345);
          *((_WORD *)v529 + 1) = v350
                               + ((32 * ((v351 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v351 < __sub_41CAB0_dword_4458F4)) + v351 + 4) >> 3);
          v352 = *((__int16 *)v524 + 1);
          v353 = v550;
          v354 = v550 - ((v352 + (1 << ((*v524 + 31) & 31))) >> *v524);
          *((_WORD *)v524 + 1) = v352
                               + ((32 * ((v354 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v354 < __sub_41CAB0_dword_4458F4)) + v354 + 2) >> 2);
          v355 = *(__int16 *)(v525 + 2);
          v356 = v353 - ((v355 + (1 << ((*(_BYTE *)v525 + 31) & 31))) >> *(_BYTE *)v525);
          *(_WORD *)(v525 + 2) = v355
                               + ((32 * ((v356 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v356 < __sub_41CAB0_dword_4458F4)) + v356 + 4) >> 3);
          *((_WORD *)v524 + 3) += (unsigned int)(v353 - ((*((__int16 *)v524 + 3) + (1 << ((v524[4] + 31) & 31))) >> v524[4]) + 2) >> 2;
          v357 = *((__int16 *)v526 + 1);
          v358 = v548 - ((v357 + (1 << ((*v526 + 31) & 31))) >> *v526);
          *((_WORD *)v526 + 1) = v357
                               + ((32 * ((v358 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v358 < __sub_41CAB0_dword_4458F4)) + v358 + 4) >> 3);
          v359 = *((__int16 *)v521 + 1);
          v360 = v550 - ((v359 + (1 << ((*v521 + 31) & 31))) >> *v521);
          *((_WORD *)v521 + 1) = v359
                               + ((32 * ((v360 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v360 < __sub_41CAB0_dword_4458F4)) + v360 + 2) >> 2);
          v361 = *((__int16 *)v522 + 1);
          v362 = v550 - ((v361 + (1 << ((*v522 + 31) & 31))) >> *v522);
          *((_WORD *)v522 + 1) = v361
                               + ((32 * ((v362 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v362 < __sub_41CAB0_dword_4458F4)) + v362 + 4) >> 3);
          *((_WORD *)v521 + 3) += (unsigned int)(v550 - ((*((__int16 *)v521 + 3) + (1 << ((v521[4] + 31) & 31))) >> v521[4]) + 2) >> 2;
          v363 = *((__int16 *)v523 + 1);
          v364 = v548 - ((v363 + (1 << ((*v523 + 31) & 31))) >> *v523);
          *((_WORD *)v523 + 1) = v363
                               + ((32 * ((v364 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v364 < __sub_41CAB0_dword_4458F4)) + v364 + 4) >> 3);
          v365 = *((__int16 *)v518 + 1);
          v366 = v550 - ((v365 + (1 << ((*v518 + 31) & 31))) >> *v518);
          *((_WORD *)v518 + 1) = v365
                               + ((32 * ((v366 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v366 < __sub_41CAB0_dword_4458F4)) + v366 + 2) >> 2);
          v367 = *((__int16 *)v519 + 1);
          v368 = v550 - ((v367 + (1 << ((*v519 + 31) & 31))) >> *v519);
          *((_WORD *)v519 + 1) = v367
                               + ((32 * ((v368 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v368 < __sub_41CAB0_dword_4458F4)) + v368 + 4) >> 3);
          *((_WORD *)v518 + 3) += (unsigned int)(v550 - ((*((__int16 *)v518 + 3) + (1 << ((v518[4] + 31) & 31))) >> v518[4]) + 2) >> 2;
          v369 = *((__int16 *)v520 + 1);
          v370 = v548 - ((v369 + (1 << ((*v520 + 31) & 31))) >> *v520);
          *((_WORD *)v520 + 1) = v369
                               + ((32 * ((v370 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v370 < __sub_41CAB0_dword_4458F4)) + v370 + 4) >> 3);
          v371 = *((__int16 *)v515 + 1);
          v372 = v550 - ((v371 + (1 << ((*v515 + 31) & 31))) >> *v515);
          *((_WORD *)v515 + 1) = v371
                               + ((32 * ((v372 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v372 < __sub_41CAB0_dword_4458F4)) + v372 + 2) >> 2);
          v373 = *(__int16 *)(v516 + 2);
          v374 = v550 - ((v373 + (1 << ((*(_BYTE *)v516 + 31) & 31))) >> *(_BYTE *)v516);
          *(_WORD *)(v516 + 2) = v373
                               + ((32 * ((v374 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v374 < __sub_41CAB0_dword_4458F4)) + v374 + 4) >> 3);
          v375 = v550;
          *((_WORD *)v515 + 3) += (unsigned int)(v550 - ((*((__int16 *)v515 + 3) + (1 << ((v515[4] + 31) & 31))) >> v515[4]) + 2) >> 2;
          v376 = *((__int16 *)v517 + 1);
          v377 = (v376 + (1 << ((*v517 + 31) & 31))) >> *v517;
          v550 = v375;
          *((_WORD *)v517 + 1) = v376
                               + ((32 * ((v548 - v377 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v548 - v377 < __sub_41CAB0_dword_4458F4))
                                 + v548
                                 - v377
                                 + 4) >> 3);
          v378 = *(__int16 *)(v512 + 2);
          v379 = v550 - ((v378 + (1 << ((*(_BYTE *)v512 + 31) & 31))) >> *(_BYTE *)v512);
          *(_WORD *)(v512 + 2) = v378
                               + ((32 * ((v379 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v379 < __sub_41CAB0_dword_4458F4)) + v379 + 2) >> 2);
          v380 = *(__int16 *)(v513 + 2);
          v381 = v550 - ((v380 + (1 << ((*(_BYTE *)v513 + 31) & 31))) >> *(_BYTE *)v513);
          *(_WORD *)(v513 + 2) = v380
                               + ((32 * ((v381 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v381 < __sub_41CAB0_dword_4458F4)) + v381 + 4) >> 3);
          v382 = v550;
          *(_WORD *)(v512 + 6) += (unsigned int)(v550
                                               - ((*(__int16 *)(v512 + 6) + (1 << ((*(_BYTE *)(v512 + 4) + 31) & 31))) >> *(_BYTE *)(v512 + 4))
                                               + 2) >> 2;
          v383 = *(__int16 *)(v514 + 2);
          v384 = -v382 - ((v383 + (1 << ((*(_BYTE *)v514 + 31) & 31))) >> *(_BYTE *)v514);
          *(_WORD *)(v514 + 2) = v383
                               + ((32 * ((v384 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v384 < __sub_41CAB0_dword_4458F4)) + v384 + 4) >> 3);
        }
        else
        {
          v115 = *(__int16 *)(n2 - 2);
          v116 = *(_BYTE *)(n2 - 4);
          v550 = v108;
          *(_WORD *)(n2 - 2) = ((unsigned int)(-v108 - ((v115 + (1 << ((v116 + 31) & 31))) >> v116) + 4) >> 3) + v115;
          v117 = *(__int16 *)(v542 + 2);
          v118 = v550 - ((v117 + (1 << ((*(_BYTE *)v542 + 31) & 31))) >> *(_BYTE *)v542);
          *(_WORD *)(v542 + 2) = v117
                               + ((32 * ((v118 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v118 < __sub_41CAB0_dword_4458F4)) + v118 + 2) >> 2);
          v119 = *((__int16 *)v543 + 1);
          v87 = n3 < 3;
          v120 = v550 - ((v119 + (1 << ((*v543 + 31) & 31))) >> *v543);
          *((_WORD *)v543 + 1) = v119
                               + ((32 * ((v120 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v120 < __sub_41CAB0_dword_4458F4)) + v120 + 4) >> 3);
          v121 = v550;
          if ( v87 )
          {
            *(_WORD *)(v542 + 6) += (unsigned int)(v550
                                                 - ((*(__int16 *)(v542 + 6) + (1 << ((*(_BYTE *)(v542 + 4) + 31) & 31))) >> *(_BYTE *)(v542 + 4))
                                                 + 2) >> 2;
            v216 = *(__int16 *)(v542 - 2);
            v217 = v121 - ((v216 + (1 << ((*(_BYTE *)(v542 - 4) + 31) & 31))) >> *(_BYTE *)(v542 - 4));
            v218 = -v121;
            v572 = v218;
            *(_WORD *)(v542 - 2) = v216
                                 + ((32 * ((v217 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v217 < __sub_41CAB0_dword_4458F4)) + v217 + 4) >> 3);
            v219 = *((__int16 *)v544 + 1);
            v220 = v218 - ((v219 + (1 << ((*v544 + 31) & 31))) >> *v544);
            *((_WORD *)v544 + 1) = v219
                                 + ((32 * ((v220 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v220 < __sub_41CAB0_dword_4458F4)) + v220 + 4) >> 3);
            v221 = *(__int16 *)(v539 + 2);
            v222 = v550;
            v223 = v550 - ((v221 + (1 << ((*(_BYTE *)v539 + 31) & 31))) >> *(_BYTE *)v539);
            *(_WORD *)(v539 + 2) = v221
                                 + ((32 * ((v223 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v223 < __sub_41CAB0_dword_4458F4)) + v223 + 2) >> 2);
            v224 = *((__int16 *)v540 + 1);
            v225 = v222 - ((v224 + (1 << ((*v540 + 31) & 31))) >> *v540);
            *((_WORD *)v540 + 1) = v224
                                 + ((32 * ((v225 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v225 < __sub_41CAB0_dword_4458F4)) + v225 + 4) >> 3);
            *(_WORD *)(v539 + 6) += (unsigned int)(v222
                                                 - ((*(__int16 *)(v539 + 6) + (1 << ((*(_BYTE *)(v539 + 4) + 31) & 31))) >> *(_BYTE *)(v539 + 4))
                                                 + 2) >> 2;
            v226 = *(__int16 *)(v539 - 2);
            v227 = v222 - ((v226 + (1 << ((*(_BYTE *)(v539 - 4) + 31) & 31))) >> *(_BYTE *)(v539 - 4));
            *(_WORD *)(v539 - 2) = v226
                                 + ((32 * ((v227 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v227 < __sub_41CAB0_dword_4458F4)) + v227 + 4) >> 3);
            v228 = *(__int16 *)(v541 + 2);
            v229 = v572 - ((v228 + (1 << ((*(_BYTE *)v541 + 31) & 31))) >> *(_BYTE *)v541);
            *(_WORD *)(v541 + 2) = v228
                                 + ((32 * ((v229 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v229 < __sub_41CAB0_dword_4458F4)) + v229 + 4) >> 3);
            v230 = *(__int16 *)(v536 + 2);
            v231 = v550;
            v232 = v550 - ((v230 + (1 << ((*(_BYTE *)v536 + 31) & 31))) >> *(_BYTE *)v536);
            *(_WORD *)(v536 + 2) = v230
                                 + ((32 * ((v232 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v232 < __sub_41CAB0_dword_4458F4)) + v232 + 2) >> 2);
            v233 = *((__int16 *)v537 + 1);
            v234 = v231 - ((v233 + (1 << ((*v537 + 31) & 31))) >> *v537);
            *((_WORD *)v537 + 1) = v233
                                 + ((32 * ((v234 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v234 < __sub_41CAB0_dword_4458F4)) + v234 + 4) >> 3);
            *(_WORD *)(v536 + 6) += (unsigned int)(v231
                                                 - ((*(__int16 *)(v536 + 6) + (1 << ((*(_BYTE *)(v536 + 4) + 31) & 31))) >> *(_BYTE *)(v536 + 4))
                                                 + 2) >> 2;
            v235 = *(__int16 *)(v536 - 2);
            v236 = v231 - ((v235 + (1 << ((*(_BYTE *)(v536 - 4) + 31) & 31))) >> *(_BYTE *)(v536 - 4));
            *(_WORD *)(v536 - 2) = v235
                                 + ((32 * ((v236 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v236 < __sub_41CAB0_dword_4458F4)) + v236 + 4) >> 3);
            v237 = *(__int16 *)(v538 + 2);
            v238 = v572 - ((v237 + (1 << ((*(_BYTE *)v538 + 31) & 31))) >> *(_BYTE *)v538);
            *(_WORD *)(v538 + 2) = v237
                                 + ((32 * ((v238 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v238 < __sub_41CAB0_dword_4458F4)) + v238 + 4) >> 3);
            v239 = *((__int16 *)v533 + 1);
            v240 = v550;
            v241 = v550 - ((v239 + (1 << ((*v533 + 31) & 31))) >> *v533);
            *((_WORD *)v533 + 1) = v239
                                 + ((32 * ((v241 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v241 < __sub_41CAB0_dword_4458F4)) + v241 + 2) >> 2);
            v242 = *((__int16 *)v534 + 1);
            v243 = v240 - ((v242 + (1 << ((*v534 + 31) & 31))) >> *v534);
            *((_WORD *)v534 + 1) = v242
                                 + ((32 * ((v243 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v243 < __sub_41CAB0_dword_4458F4)) + v243 + 4) >> 3);
            *((_WORD *)v533 + 3) += (unsigned int)(v240
                                                 - ((*((__int16 *)v533 + 3) + (1 << ((v533[4] + 31) & 31))) >> v533[4])
                                                 + 2) >> 2;
            v244 = *((__int16 *)v533 - 1);
            v245 = v240 - ((v244 + (1 << ((*(v533 - 4) + 31) & 31))) >> *(v533 - 4));
            *((_WORD *)v533 - 1) = v244
                                 + ((32 * ((v245 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v245 < __sub_41CAB0_dword_4458F4)) + v245 + 4) >> 3);
            v246 = *((__int16 *)v535 + 1);
            v247 = v572 - ((v246 + (1 << ((*v535 + 31) & 31))) >> *v535);
            *((_WORD *)v535 + 1) = v246
                                 + ((32 * ((v247 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v247 < __sub_41CAB0_dword_4458F4)) + v247 + 4) >> 3);
            v248 = *((__int16 *)v530 + 1);
            v249 = v550;
            v250 = v550 - ((v248 + (1 << ((*v530 + 31) & 31))) >> *v530);
            *((_WORD *)v530 + 1) = v248
                                 + ((32 * ((v250 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v250 < __sub_41CAB0_dword_4458F4)) + v250 + 2) >> 2);
            v251 = *((__int16 *)v531 + 1);
            LOBYTE(v248) = *v531;
            v252 = v251 + (1 << ((*v531 + 31) & 31));
            v550 = v249;
            *((_WORD *)v531 + 1) = v251
                                 + ((32
                                   * ((v249 - (v252 >> v248) > __sub_41CAB0_dword_4458F0)
                                    - (unsigned int)(v249 - (v252 >> v248) < __sub_41CAB0_dword_4458F4))
                                   + v249
                                   - (v252 >> v248)
                                   + 4) >> 3);
            v253 = v550;
            *((_WORD *)v530 + 3) += (unsigned int)(v550
                                                 - ((*((__int16 *)v530 + 3) + (1 << ((v530[4] + 31) & 31))) >> v530[4])
                                                 + 2) >> 2;
            v254 = *((__int16 *)v530 - 1);
            v255 = v253 - ((v254 + (1 << ((*(v530 - 4) + 31) & 31))) >> *(v530 - 4));
            *((_WORD *)v530 - 1) = v254
                                 + ((32 * ((v255 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v255 < __sub_41CAB0_dword_4458F4)) + v255 + 4) >> 3);
            v256 = *((__int16 *)v532 + 1);
            LOBYTE(v254) = *v532;
            v573 = -v253;
            v257 = -v253 - ((v256 + (1 << ((v254 + 31) & 31))) >> v254);
            *((_WORD *)v532 + 1) = v256
                                 + ((32 * ((v257 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v257 < __sub_41CAB0_dword_4458F4)) + v257 + 4) >> 3);
            v258 = *((__int16 *)v527 + 1);
            v259 = v550;
            v260 = v550 - ((v258 + (1 << ((*v527 + 31) & 31))) >> *v527);
            *((_WORD *)v527 + 1) = v258
                                 + ((32 * ((v260 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v260 < __sub_41CAB0_dword_4458F4)) + v260 + 2) >> 2);
            v261 = *((__int16 *)v528 + 1);
            v262 = v259 - ((v261 + (1 << ((*v528 + 31) & 31))) >> *v528);
            *((_WORD *)v528 + 1) = v261
                                 + ((32 * ((v262 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v262 < __sub_41CAB0_dword_4458F4)) + v262 + 4) >> 3);
            *((_WORD *)v527 + 3) += (unsigned int)(v259
                                                 - ((*((__int16 *)v527 + 3) + (1 << ((v527[4] + 31) & 31))) >> v527[4])
                                                 + 2) >> 2;
            v263 = *((__int16 *)v527 - 1);
            v264 = v259 - ((v263 + (1 << ((*(v527 - 4) + 31) & 31))) >> *(v527 - 4));
            *((_WORD *)v527 - 1) = v263
                                 + ((32 * ((v264 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v264 < __sub_41CAB0_dword_4458F4)) + v264 + 4) >> 3);
            v265 = *((__int16 *)v529 + 1);
            v266 = v573 - ((v265 + (1 << ((*v529 + 31) & 31))) >> *v529);
            *((_WORD *)v529 + 1) = v265
                                 + ((32 * ((v266 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v266 < __sub_41CAB0_dword_4458F4)) + v266 + 4) >> 3);
            v267 = *((__int16 *)v524 + 1);
            v268 = v550;
            v269 = v550 - ((v267 + (1 << ((*v524 + 31) & 31))) >> *v524);
            *((_WORD *)v524 + 1) = v267
                                 + ((32 * ((v269 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v269 < __sub_41CAB0_dword_4458F4)) + v269 + 2) >> 2);
            v270 = *(__int16 *)(v525 + 2);
            v271 = v268 - ((v270 + (1 << ((*(_BYTE *)v525 + 31) & 31))) >> *(_BYTE *)v525);
            *(_WORD *)(v525 + 2) = v270
                                 + ((32 * ((v271 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v271 < __sub_41CAB0_dword_4458F4)) + v271 + 4) >> 3);
            *((_WORD *)v524 + 3) += (unsigned int)(v268
                                                 - ((*((__int16 *)v524 + 3) + (1 << ((v524[4] + 31) & 31))) >> v524[4])
                                                 + 2) >> 2;
            v272 = *((__int16 *)v524 - 1);
            v273 = v268 - ((v272 + (1 << ((*(v524 - 4) + 31) & 31))) >> *(v524 - 4));
            *((_WORD *)v524 - 1) = v272
                                 + ((32 * ((v273 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v273 < __sub_41CAB0_dword_4458F4)) + v273 + 4) >> 3);
            v274 = *((__int16 *)v526 + 1);
            v275 = v573 - ((v274 + (1 << ((*v526 + 31) & 31))) >> *v526);
            *((_WORD *)v526 + 1) = v274
                                 + ((32 * ((v275 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v275 < __sub_41CAB0_dword_4458F4)) + v275 + 4) >> 3);
            v276 = *((__int16 *)v521 + 1);
            v277 = v550;
            v278 = v550 - ((v276 + (1 << ((*v521 + 31) & 31))) >> *v521);
            *((_WORD *)v521 + 1) = v276
                                 + ((32 * ((v278 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v278 < __sub_41CAB0_dword_4458F4)) + v278 + 2) >> 2);
            v279 = *((__int16 *)v522 + 1);
            v280 = v277 - ((v279 + (1 << ((*v522 + 31) & 31))) >> *v522);
            *((_WORD *)v522 + 1) = v279
                                 + ((32 * ((v280 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v280 < __sub_41CAB0_dword_4458F4)) + v280 + 4) >> 3);
            *((_WORD *)v521 + 3) += (unsigned int)(v277
                                                 - ((*((__int16 *)v521 + 3) + (1 << ((v521[4] + 31) & 31))) >> v521[4])
                                                 + 2) >> 2;
            v281 = *((__int16 *)v521 - 1);
            v282 = v277 - ((v281 + (1 << ((*(v521 - 4) + 31) & 31))) >> *(v521 - 4));
            *((_WORD *)v521 - 1) = v281
                                 + ((32 * ((v282 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v282 < __sub_41CAB0_dword_4458F4)) + v282 + 4) >> 3);
            v283 = *((__int16 *)v523 + 1);
            v284 = v573 - ((v283 + (1 << ((*v523 + 31) & 31))) >> *v523);
            *((_WORD *)v523 + 1) = v283
                                 + ((32 * ((v284 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v284 < __sub_41CAB0_dword_4458F4)) + v284 + 4) >> 3);
            v285 = *((__int16 *)v518 + 1);
            v286 = v550;
            v287 = v550 - ((v285 + (1 << ((*v518 + 31) & 31))) >> *v518);
            *((_WORD *)v518 + 1) = v285
                                 + ((32 * ((v287 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v287 < __sub_41CAB0_dword_4458F4)) + v287 + 2) >> 2);
            v288 = *((__int16 *)v519 + 1);
            v289 = v286 - ((v288 + (1 << ((*v519 + 31) & 31))) >> *v519);
            *((_WORD *)v519 + 1) = v288
                                 + ((32 * ((v289 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v289 < __sub_41CAB0_dword_4458F4)) + v289 + 4) >> 3);
            *((_WORD *)v518 + 3) += (unsigned int)(v286
                                                 - ((*((__int16 *)v518 + 3) + (1 << ((v518[4] + 31) & 31))) >> v518[4])
                                                 + 2) >> 2;
            v290 = *((__int16 *)v518 - 1);
            v291 = v286 - ((v290 + (1 << ((*(v518 - 4) + 31) & 31))) >> *(v518 - 4));
            v292 = -v286;
            v574 = v292;
            *((_WORD *)v518 - 1) = v290
                                 + ((32 * ((v291 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v291 < __sub_41CAB0_dword_4458F4)) + v291 + 4) >> 3);
            v293 = *((__int16 *)v520 + 1);
            v294 = v292 - ((v293 + (1 << ((*v520 + 31) & 31))) >> *v520);
            *((_WORD *)v520 + 1) = v293
                                 + ((32 * ((v294 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v294 < __sub_41CAB0_dword_4458F4)) + v294 + 4) >> 3);
            v295 = *((__int16 *)v515 + 1);
            v296 = v550;
            v297 = v550 - ((v295 + (1 << ((*v515 + 31) & 31))) >> *v515);
            *((_WORD *)v515 + 1) = v295
                                 + ((32 * ((v297 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v297 < __sub_41CAB0_dword_4458F4)) + v297 + 2) >> 2);
            v298 = *(__int16 *)(v516 + 2);
            v299 = v296 - ((v298 + (1 << ((*(_BYTE *)v516 + 31) & 31))) >> *(_BYTE *)v516);
            *(_WORD *)(v516 + 2) = v298
                                 + ((32 * ((v299 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v299 < __sub_41CAB0_dword_4458F4)) + v299 + 4) >> 3);
            *((_WORD *)v515 + 3) += (unsigned int)(v296
                                                 - ((*((__int16 *)v515 + 3) + (1 << ((v515[4] + 31) & 31))) >> v515[4])
                                                 + 2) >> 2;
            v300 = *((__int16 *)v515 - 1);
            v301 = v296 - ((v300 + (1 << ((*(v515 - 4) + 31) & 31))) >> *(v515 - 4));
            *((_WORD *)v515 - 1) = v300
                                 + ((32 * ((v301 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v301 < __sub_41CAB0_dword_4458F4)) + v301 + 4) >> 3);
            v302 = *((__int16 *)v517 + 1);
            v303 = v574 - ((v302 + (1 << ((*v517 + 31) & 31))) >> *v517);
            *((_WORD *)v517 + 1) = v302
                                 + ((32 * ((v303 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v303 < __sub_41CAB0_dword_4458F4)) + v303 + 4) >> 3);
            v304 = *(__int16 *)(v512 + 2);
            v305 = v550;
            v306 = v550 - ((v304 + (1 << ((*(_BYTE *)v512 + 31) & 31))) >> *(_BYTE *)v512);
            *(_WORD *)(v512 + 2) = v304
                                 + ((32 * ((v306 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v306 < __sub_41CAB0_dword_4458F4)) + v306 + 2) >> 2);
            v307 = *(__int16 *)(v513 + 2);
            v308 = v305 - ((v307 + (1 << ((*(_BYTE *)v513 + 31) & 31))) >> *(_BYTE *)v513);
            *(_WORD *)(v513 + 2) = v307
                                 + ((32 * ((v308 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v308 < __sub_41CAB0_dword_4458F4)) + v308 + 4) >> 3);
            *(_WORD *)(v512 + 6) += (unsigned int)(v305
                                                 - ((*(__int16 *)(v512 + 6) + (1 << ((*(_BYTE *)(v512 + 4) + 31) & 31))) >> *(_BYTE *)(v512 + 4))
                                                 + 2) >> 2;
            v309 = *(__int16 *)(v512 - 2);
            v310 = v305 - ((v309 + (1 << ((*(_BYTE *)(v512 - 4) + 31) & 31))) >> *(_BYTE *)(v512 - 4));
            *(_WORD *)(v512 - 2) = v309
                                 + ((32 * ((v310 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v310 < __sub_41CAB0_dword_4458F4)) + v310 + 4) >> 3);
            v214 = *(__int16 *)(v514 + 2);
            v215 = v574 - ((v214 + (1 << ((*(_BYTE *)v514 + 31) & 31))) >> *(_BYTE *)v514);
          }
          else
          {
            v122 = *(__int16 *)(v542 - 2);
            v123 = v550 - ((v122 + (1 << ((*(_BYTE *)(v542 - 4) + 31) & 31))) >> *(_BYTE *)(v542 - 4));
            *(_WORD *)(v542 - 2) = v122
                                 + ((32 * ((v123 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v123 < __sub_41CAB0_dword_4458F4)) + v123 + 4) >> 3);
            v124 = *((__int16 *)v544 + 1);
            LOBYTE(v122) = *v544;
            v547 = -v121;
            v125 = -v121 - ((v124 + (1 << ((v122 + 31) & 31))) >> v122);
            *((_WORD *)v544 + 1) = v124
                                 + ((32 * ((v125 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v125 < __sub_41CAB0_dword_4458F4)) + v125 + 4) >> 3);
            v126 = *(__int16 *)(v539 + 2);
            v127 = v550;
            v128 = v550 - ((v126 + (1 << ((*(_BYTE *)v539 + 31) & 31))) >> *(_BYTE *)v539);
            *(_WORD *)(v539 + 2) = v126
                                 + ((32 * ((v128 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v128 < __sub_41CAB0_dword_4458F4)) + v128 + 2) >> 2);
            v129 = *((__int16 *)v540 + 1);
            v130 = v127 - ((v129 + (1 << ((*v540 + 31) & 31))) >> *v540);
            *((_WORD *)v540 + 1) = v129
                                 + ((32 * ((v130 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v130 < __sub_41CAB0_dword_4458F4)) + v130 + 4) >> 3);
            v131 = *(__int16 *)(v539 - 2);
            v132 = v127 - ((v131 + (1 << ((*(_BYTE *)(v539 - 4) + 31) & 31))) >> *(_BYTE *)(v539 - 4));
            *(_WORD *)(v539 - 2) = v131
                                 + ((32 * ((v132 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v132 < __sub_41CAB0_dword_4458F4)) + v132 + 4) >> 3);
            v133 = *(__int16 *)(v541 + 2);
            v134 = v547 - ((v133 + (1 << ((*(_BYTE *)v541 + 31) & 31))) >> *(_BYTE *)v541);
            *(_WORD *)(v541 + 2) = v133
                                 + ((32 * ((v134 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v134 < __sub_41CAB0_dword_4458F4)) + v134 + 4) >> 3);
            v135 = *(__int16 *)(v536 + 2);
            v136 = v550;
            v137 = v550 - ((v135 + (1 << ((*(_BYTE *)v536 + 31) & 31))) >> *(_BYTE *)v536);
            *(_WORD *)(v536 + 2) = v135
                                 + ((32 * ((v137 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v137 < __sub_41CAB0_dword_4458F4)) + v137 + 2) >> 2);
            v138 = *((__int16 *)v537 + 1);
            v139 = v136 - ((v138 + (1 << ((*v537 + 31) & 31))) >> *v537);
            *((_WORD *)v537 + 1) = v138
                                 + ((32 * ((v139 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v139 < __sub_41CAB0_dword_4458F4)) + v139 + 4) >> 3);
            v140 = *(__int16 *)(v536 - 2);
            v141 = v136 - ((v140 + (1 << ((*(_BYTE *)(v536 - 4) + 31) & 31))) >> *(_BYTE *)(v536 - 4));
            *(_WORD *)(v536 - 2) = v140
                                 + ((32 * ((v141 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v141 < __sub_41CAB0_dword_4458F4)) + v141 + 4) >> 3);
            v142 = *(__int16 *)(v538 + 2);
            v143 = v547 - ((v142 + (1 << ((*(_BYTE *)v538 + 31) & 31))) >> *(_BYTE *)v538);
            *(_WORD *)(v538 + 2) = v142
                                 + ((32 * ((v143 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v143 < __sub_41CAB0_dword_4458F4)) + v143 + 4) >> 3);
            v144 = *((__int16 *)v533 + 1);
            v145 = v550;
            v146 = v550 - ((v144 + (1 << ((*v533 + 31) & 31))) >> *v533);
            *((_WORD *)v533 + 1) = v144
                                 + ((32 * ((v146 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v146 < __sub_41CAB0_dword_4458F4)) + v146 + 2) >> 2);
            v147 = *((__int16 *)v534 + 1);
            v148 = v145 - ((v147 + (1 << ((*v534 + 31) & 31))) >> *v534);
            *((_WORD *)v534 + 1) = v147
                                 + ((32 * ((v148 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v148 < __sub_41CAB0_dword_4458F4)) + v148 + 4) >> 3);
            v149 = *((__int16 *)v533 - 1);
            v150 = v145 - ((v149 + (1 << ((*(v533 - 4) + 31) & 31))) >> *(v533 - 4));
            *((_WORD *)v533 - 1) = v149
                                 + ((32 * ((v150 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v150 < __sub_41CAB0_dword_4458F4)) + v150 + 4) >> 3);
            v151 = *((__int16 *)v535 + 1);
            v152 = v547 - ((v151 + (1 << ((*v535 + 31) & 31))) >> *v535);
            *((_WORD *)v535 + 1) = v151
                                 + ((32 * ((v152 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v152 < __sub_41CAB0_dword_4458F4)) + v152 + 4) >> 3);
            v153 = *((__int16 *)v530 + 1);
            v154 = v550;
            v155 = v550 - ((v153 + (1 << ((*v530 + 31) & 31))) >> *v530);
            *((_WORD *)v530 + 1) = v153
                                 + ((32 * ((v155 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v155 < __sub_41CAB0_dword_4458F4)) + v155 + 2) >> 2);
            v156 = *((__int16 *)v531 + 1);
            v157 = v154 - ((v156 + (1 << ((*v531 + 31) & 31))) >> *v531);
            *((_WORD *)v531 + 1) = v156
                                 + ((32 * ((v157 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v157 < __sub_41CAB0_dword_4458F4)) + v157 + 4) >> 3);
            v158 = *((__int16 *)v530 - 1);
            v159 = v154 - ((v158 + (1 << ((*(v530 - 4) + 31) & 31))) >> *(v530 - 4));
            *((_WORD *)v530 - 1) = v158
                                 + ((32 * ((v159 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v159 < __sub_41CAB0_dword_4458F4)) + v159 + 4) >> 3);
            v160 = *((__int16 *)v532 + 1);
            v547 -= (v160 + (1 << ((*v532 + 31) & 31))) >> *v532;
            v161 = v550;
            *((_WORD *)v532 + 1) = v160
                                 + ((32 * ((v547 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v547 < __sub_41CAB0_dword_4458F4)) + v547 + 4) >> 3);
            v162 = *((__int16 *)v527 + 1);
            v163 = v161 - ((v162 + (1 << ((*v527 + 31) & 31))) >> *v527);
            *((_WORD *)v527 + 1) = v162
                                 + ((32 * ((v163 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v163 < __sub_41CAB0_dword_4458F4)) + v163 + 2) >> 2);
            v164 = *((__int16 *)v528 + 1);
            v165 = v161 - ((v164 + (1 << ((*v528 + 31) & 31))) >> *v528);
            *((_WORD *)v528 + 1) = v164
                                 + ((32 * ((v165 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v165 < __sub_41CAB0_dword_4458F4)) + v165 + 4) >> 3);
            v166 = *((__int16 *)v527 - 1);
            v167 = v161 - ((v166 + (1 << ((*(v527 - 4) + 31) & 31))) >> *(v527 - 4));
            v168 = -v161;
            v570 = v168;
            *((_WORD *)v527 - 1) = v166
                                 + ((32 * ((v167 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v167 < __sub_41CAB0_dword_4458F4)) + v167 + 4) >> 3);
            v169 = *((__int16 *)v529 + 1);
            v170 = v168 - ((v169 + (1 << ((*v529 + 31) & 31))) >> *v529);
            *((_WORD *)v529 + 1) = v169
                                 + ((32 * ((v170 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v170 < __sub_41CAB0_dword_4458F4)) + v170 + 4) >> 3);
            v171 = *((__int16 *)v524 + 1);
            v172 = v550;
            v173 = v550 - ((v171 + (1 << ((*v524 + 31) & 31))) >> *v524);
            *((_WORD *)v524 + 1) = v171
                                 + ((32 * ((v173 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v173 < __sub_41CAB0_dword_4458F4)) + v173 + 2) >> 2);
            v174 = *(__int16 *)(v525 + 2);
            v175 = v172 - ((v174 + (1 << ((*(_BYTE *)v525 + 31) & 31))) >> *(_BYTE *)v525);
            *(_WORD *)(v525 + 2) = v174
                                 + ((32 * ((v175 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v175 < __sub_41CAB0_dword_4458F4)) + v175 + 4) >> 3);
            v176 = *((__int16 *)v524 - 1);
            v177 = v172 - ((v176 + (1 << ((*(v524 - 4) + 31) & 31))) >> *(v524 - 4));
            *((_WORD *)v524 - 1) = v176
                                 + ((32 * ((v177 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v177 < __sub_41CAB0_dword_4458F4)) + v177 + 4) >> 3);
            v178 = *((__int16 *)v526 + 1);
            v179 = v570 - ((v178 + (1 << ((*v526 + 31) & 31))) >> *v526);
            *((_WORD *)v526 + 1) = v178
                                 + ((32 * ((v179 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v179 < __sub_41CAB0_dword_4458F4)) + v179 + 4) >> 3);
            v180 = *((__int16 *)v521 + 1);
            v181 = v550;
            v182 = v550 - ((v180 + (1 << ((*v521 + 31) & 31))) >> *v521);
            *((_WORD *)v521 + 1) = v180
                                 + ((32 * ((v182 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v182 < __sub_41CAB0_dword_4458F4)) + v182 + 2) >> 2);
            v183 = *((__int16 *)v522 + 1);
            v184 = v181 - ((v183 + (1 << ((*v522 + 31) & 31))) >> *v522);
            *((_WORD *)v522 + 1) = v183
                                 + ((32 * ((v184 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v184 < __sub_41CAB0_dword_4458F4)) + v184 + 4) >> 3);
            v185 = *((__int16 *)v521 - 1);
            v186 = v181 - ((v185 + (1 << ((*(v521 - 4) + 31) & 31))) >> *(v521 - 4));
            *((_WORD *)v521 - 1) = v185
                                 + ((32 * ((v186 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v186 < __sub_41CAB0_dword_4458F4)) + v186 + 4) >> 3);
            v187 = *((__int16 *)v523 + 1);
            v188 = v570 - ((v187 + (1 << ((*v523 + 31) & 31))) >> *v523);
            *((_WORD *)v523 + 1) = v187
                                 + ((32 * ((v188 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v188 < __sub_41CAB0_dword_4458F4)) + v188 + 4) >> 3);
            v189 = *((__int16 *)v518 + 1);
            v190 = v550;
            v191 = v550 - ((v189 + (1 << ((*v518 + 31) & 31))) >> *v518);
            *((_WORD *)v518 + 1) = v189
                                 + ((32 * ((v191 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v191 < __sub_41CAB0_dword_4458F4)) + v191 + 2) >> 2);
            v192 = *((__int16 *)v519 + 1);
            v193 = v190 - ((v192 + (1 << ((*v519 + 31) & 31))) >> *v519);
            *((_WORD *)v519 + 1) = v192
                                 + ((32 * ((v193 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v193 < __sub_41CAB0_dword_4458F4)) + v193 + 4) >> 3);
            v194 = *((__int16 *)v518 - 1);
            v195 = v190 - ((v194 + (1 << ((*(v518 - 4) + 31) & 31))) >> *(v518 - 4));
            *((_WORD *)v518 - 1) = v194
                                 + ((32 * ((v195 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v195 < __sub_41CAB0_dword_4458F4)) + v195 + 4) >> 3);
            v196 = *((__int16 *)v520 + 1);
            v197 = v570 - ((v196 + (1 << ((*v520 + 31) & 31))) >> *v520);
            *((_WORD *)v520 + 1) = v196
                                 + ((32 * ((v197 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v197 < __sub_41CAB0_dword_4458F4)) + v197 + 4) >> 3);
            v198 = *((__int16 *)v515 + 1);
            v199 = v550;
            v200 = v550 - ((v198 + (1 << ((*v515 + 31) & 31))) >> *v515);
            *((_WORD *)v515 + 1) = v198
                                 + ((32 * ((v200 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v200 < __sub_41CAB0_dword_4458F4)) + v200 + 2) >> 2);
            v201 = *(__int16 *)(v516 + 2);
            v202 = v199 - ((v201 + (1 << ((*(_BYTE *)v516 + 31) & 31))) >> *(_BYTE *)v516);
            v550 = v199;
            *(_WORD *)(v516 + 2) = v201
                                 + ((32 * ((v202 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v202 < __sub_41CAB0_dword_4458F4)) + v202 + 4) >> 3);
            v203 = *((__int16 *)v515 - 1);
            v204 = v199 - ((v203 + (1 << ((*(v515 - 4) + 31) & 31))) >> *(v515 - 4));
            *((_WORD *)v515 - 1) = v203
                                 + ((32 * ((v204 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v204 < __sub_41CAB0_dword_4458F4)) + v204 + 4) >> 3);
            v205 = *((__int16 *)v517 + 1);
            LOBYTE(v203) = *v517;
            v571 = -v199;
            v206 = -v199 - ((v205 + (1 << ((v203 + 31) & 31))) >> v203);
            *((_WORD *)v517 + 1) = v205
                                 + ((32 * ((v206 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v206 < __sub_41CAB0_dword_4458F4)) + v206 + 4) >> 3);
            v207 = *(__int16 *)(v512 + 2);
            v208 = v550;
            v209 = v550 - ((v207 + (1 << ((*(_BYTE *)v512 + 31) & 31))) >> *(_BYTE *)v512);
            *(_WORD *)(v512 + 2) = v207
                                 + ((32 * ((v209 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v209 < __sub_41CAB0_dword_4458F4)) + v209 + 2) >> 2);
            v210 = *(__int16 *)(v513 + 2);
            v211 = v208 - ((v210 + (1 << ((*(_BYTE *)v513 + 31) & 31))) >> *(_BYTE *)v513);
            *(_WORD *)(v513 + 2) = v210
                                 + ((32 * ((v211 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v211 < __sub_41CAB0_dword_4458F4)) + v211 + 4) >> 3);
            v212 = *(__int16 *)(v512 - 2);
            v213 = v208 - ((v212 + (1 << ((*(_BYTE *)(v512 - 4) + 31) & 31))) >> *(_BYTE *)(v512 - 4));
            *(_WORD *)(v512 - 2) = v212
                                 + ((32 * ((v213 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v213 < __sub_41CAB0_dword_4458F4)) + v213 + 4) >> 3);
            v214 = *(__int16 *)(v514 + 2);
            v215 = v571 - ((v214 + (1 << ((*(_BYTE *)v514 + 31) & 31))) >> *(_BYTE *)v514);
          }
          *(_WORD *)(v514 + 2) = v214
                               + ((32 * ((v215 > __sub_41CAB0_dword_4458F0) - (unsigned int)(v215 < __sub_41CAB0_dword_4458F4)) + v215 + 4) >> 3);
        }
      }
    }
    ++n5;
  }
  while ( n5 < 5 );
  v385 = v578;
  v386 = v578[69676];
  v578[69684] += 18;
  v387 = (unsigned __int16 *)&v385[2 * v386];
  v385[69685] += 18;
  v385[69686] += 18;
  v385[69687] += 18;
  v385[69688] += 18;
  n0x10 = v387[470036];
  if ( n0x10 > 0x10 )
  {
    v389 = (unsigned __int16 *)v385[(a4 & 1) + 69677];
    v511 = a4 & 1;
    n15 = v386 & 0xF;
    v508 = v389;
    if ( n15 < 15 )
    {
      v391 = v387[470041];
      v392 = v387[470042];
      n2 = (int)(v387 + 470040);
      if ( v387[470043] + v392 + v391 > 29696 )
        sub_414800(v387 + 470040);
      v393 = (10 * (unsigned int)v387[470040]) >> 4;
      if ( a4 )
      {
        *(_WORD *)(n2 - 2 * v511 + 6) += v393;
        sub_413430((unsigned __int16 *)__sub_41CAB0_n256_1 + 254 * (_DWORD)v508 + 254, (a4 - 1) >> 1);
      }
      else
      {
        *(_WORD *)(n2 + 2) += v393;
      }
      if ( n15 <= 0 )
      {
LABEL_37:
        n0x10 = v385[69676];
        if ( LOWORD(v385[2 * n0x10 + 235018]) <= 0x1Au )
          return n0x10;
        v397 = v385[69698];
        v398 = 2 - (*((_BYTE *)v385 + (unsigned __int8)-(char)a5 + 279984) & 1);
        if ( !*((_BYTE *)v385 + (unsigned __int8)-(char)a5 + 279984) )
          v398 = *((unsigned __int8 *)v385 + (unsigned __int8)-(char)a5 + 279984);
        v399 = v385[69702];
        v400 = v385[69696] + (v385[69676] & 0x3F);
        v510 = v398;
        n0x10 = v385[-v385[69710] + 69713]
              + v385[-v385[69706] + 69709]
              + v385[-v399 + 69705]
              + v385[-v397 + 69701]
              + v400;
        n0x10_3 = (unsigned __int16 *)&v385[2 * n0x10];
        n0x10_2 = (unsigned int)n0x10_3;
        if ( n15 < 15 )
        {
          n2_2 = n0x10_3 + 470040;
          v403 = n0x10_3[470041];
          v404 = n0x10_3[470042];
          n2 = (int)n2_2;
          if ( n2_2[3] + v404 + v403 > 29696 )
          {
            n0x10_1 = n0x10;
            sub_414800(n2_2);
            n0x10 = n0x10_1;
          }
          v405 = *(_WORD *)(n0x10_2 + 940080) & 0xFFFC;
          v510 *= 2;
          *(_WORD *)(n2 + v510 + 2) += v405 >> 2;
          if ( n15 <= 0 )
            goto LABEL_48;
        }
        else
        {
          v510 *= 2;
        }
        v406 = *(unsigned __int16 *)(n0x10_2 + 940066);
        v407 = *(unsigned __int16 *)(n0x10_2 + 940068);
        n2 = n0x10_2 + 940064;
        if ( *(unsigned __int16 *)(n0x10_2 + 940070) + v407 + v406 > 29696 )
        {
          n0x10_1 = n0x10;
          sub_414800((unsigned __int16 *)(n0x10_2 + 940064));
          n0x10 = n0x10_1;
        }
        *(_WORD *)(n2 + v510 + 2) += (unsigned __int16)(*(_WORD *)(n0x10_2 + 940064) & 0xFFFC) >> 2;
LABEL_48:
        if ( a4 )
        {
          n2 = (a4 - 1) >> 1;
          n0xF0 = (unsigned __int16 *)((unsigned __int8)v508 & 0xF0);
          if ( (unsigned int)n0xF0 >= 0xF0
            || (n0x10_1 = n0x10,
                sub_413430((unsigned __int16 *)__sub_41CAB0_n256_1 + 254 * (_DWORD)v508 + 4064, n2),
                n0x10 = n0x10_1,
                (int)n0xF0 > 0) )
          {
            n0x10_1 = n0x10;
            sub_413430((unsigned __int16 *)__sub_41CAB0_n256_1 + 254 * (_DWORD)v508 - 4064, n2);
            n0x10 = n0x10_1;
          }
        }
        v408 = (unsigned __int16 *)(n0x10_2 + 940072);
        if ( *(unsigned __int16 *)(n0x10_2 + 940078)
           + *(unsigned __int16 *)(n0x10_2 + 940076)
           + *(unsigned __int16 *)(n0x10_2 + 940074) > 29696 )
        {
          n0x10_1 = n0x10;
          sub_414800((unsigned __int16 *)(n0x10_2 + 940072));
          n0x10 = n0x10_1;
        }
        *(unsigned __int16 *)((char *)v408 + v510 + 2) += (6 * (unsigned int)*(unsigned __int16 *)(n0x10_2 + 940072)) >> 4;
        if ( !v385[69682] || LOWORD(v385[2 * v385[69676] + 235018]) > 0x100u )
        {
          v409 = 2 - v511;
          if ( !a4 )
            v409 = 0;
          v410 = v385[69694];
          v511 = v409;
          if ( v410 == 1 )
          {
            v491 = (unsigned __int16 *)&v385[2 * v385[69695] + 235018 + 2 * (n0x10 - v385[69696])];
            v492 = HIWORD(v385[2 * v385[69695] + 235018 + 2 * (n0x10 - v385[69696])]);
            v493 = LOWORD(v385[2 * v385[69695] + 235019 + 2 * (n0x10 - v385[69696])]);
            v508 = v491;
            if ( v491[3] + v493 + v492 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(v491);
              n0x10 = n0x10_1;
            }
            *(unsigned __int16 *)((char *)v508 + v510 + 2) += (unsigned __int16)(*v508 & 0xFFFC) >> 2;
            v494 = v385[69676] - v385[69696];
            n0xF0_1 = (unsigned __int16 *)&v385[2 * v494 + 2 * v385[69695]];
            n0x10_2 = v385[69697] + v494;
            n0xF0 = n0xF0_1;
            n2_3 = n0xF0_1 + 470036;
            v497 = n2_3[2] + n2_3[1];
            v498 = n2_3[3];
            n2 = (int)n2_3;
            if ( v498 + v497 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n2_3);
              n0x10 = n0x10_1;
            }
            v499 = 3 * n0xF0[470036];
            v511 *= 2;
            *(_WORD *)(n2 + v511 + 2) += v499 >> 4;
            if ( n15 >= 15 )
              goto LABEL_180;
            v500 = n0xF0[470041];
            v501 = n0xF0[470042];
            n2 = (int)(n0xF0 + 470040);
            if ( n0xF0[470043] + v501 + v500 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n0xF0 + 470040);
              n0x10 = n0x10_1;
            }
            *(_WORD *)(n2 + v511 + 2) += (unsigned __int16)(n0xF0[470040] & 0xFFFC) >> 2;
            v502 = (_WORD *)&v385[2 * n0x10_2 + 235020];
            if ( HIWORD(v385[2 * n0x10_2 + 235021])
               + LOWORD(v385[2 * n0x10_2 + 235021])
               + HIWORD(v385[2 * n0x10_2 + 235020]) > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800((unsigned __int16 *)&v385[2 * n0x10_2 + 235020]);
              n0x10 = n0x10_1;
            }
            *(_WORD *)((char *)v502 + v511 + 2) += (unsigned __int16)(*v502 & 0xFFF8) >> 3;
            if ( n15 > 2 )
            {
LABEL_180:
              v503 = n0xF0[470033];
              v504 = n0xF0[470034];
              n2 = (int)(n0xF0 + 470032);
              if ( n0xF0[470035] + v504 + v503 > 29696 )
              {
                n0x10_1 = n0x10;
                sub_414800(n0xF0 + 470032);
                n0x10 = n0x10_1;
              }
              *(_WORD *)(n2 + v511 + 2) += (6 * (unsigned int)n0xF0[470032]) >> 4;
            }
          }
          else
          {
            v411 = (unsigned __int16 *)&v385[2 * n0x10 + 235018 + 2 * (v385[69696] - v385[-v410 + 69697])];
            if ( HIWORD(v385[2 * n0x10 + 235019 + 2 * (v385[69696] - v385[-v410 + 69697])])
               + LOWORD(v385[2 * n0x10 + 235019 + 2 * (v385[69696] - v385[-v410 + 69697])])
               + HIWORD(v385[2 * n0x10 + 235018 + 2 * (v385[69696] - v385[-v410 + 69697])]) > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(v411);
              n0x10 = n0x10_1;
            }
            *(unsigned __int16 *)((char *)v411 + v510 + 2) += (7 * (unsigned int)*v411) >> 4;
            n0xF0 = (unsigned __int16 *)&v385[2 * v385[69696] + 2 * (v385[69676] - v385[v385[69694] + 69695])];
            v412 = n0xF0[470037];
            v413 = n0xF0[470038];
            n2 = (int)(n0xF0 + 470036);
            if ( n0xF0[470039] + v413 + v412 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n0xF0 + 470036);
              n0x10 = n0x10_1;
            }
            v414 = 7 * n0xF0[470036];
            v511 *= 2;
            *(_WORD *)(n2 + v511 + 2) += v414 >> 4;
            if ( n15 >= 15 )
              goto LABEL_67;
            v415 = n0xF0[470041];
            v416 = n0xF0[470042];
            n2 = (int)(n0xF0 + 470040);
            if ( n0xF0[470043] + v416 + v415 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n0xF0 + 470040);
              n0x10 = n0x10_1;
            }
            n0x10_1 = n0x10;
            *(_WORD *)(n2 + v511 + 2) = *(_WORD *)(v511 + n2 + 2) + ((5 * (unsigned int)n0xF0[470040]) >> 4);
            n0x10 = n0x10_1;
            if ( n15 > 0 )
            {
LABEL_67:
              v417 = n0xF0[470033];
              v418 = n0xF0[470034];
              n2 = (int)(n0xF0 + 470032);
              if ( n0xF0[470035] + v418 + v417 > 29696 )
              {
                n0x10_1 = n0x10;
                sub_414800(n0xF0 + 470032);
                n0x10 = n0x10_1;
              }
              *(_WORD *)(n2 + v511 + 2) += (6 * (unsigned int)n0xF0[470032]) >> 4;
            }
          }
          v419 = v385[69698];
          if ( v419 == 1 )
          {
            n2_4 = (unsigned __int16 *)&v385[2 * v385[69699] + 235018 + 2 * (n0x10 - v385[69700])];
            v481 = HIWORD(v385[2 * v385[69699] + 235018 + 2 * (n0x10 - v385[69700])]);
            v482 = LOWORD(v385[2 * v385[69699] + 235019 + 2 * (n0x10 - v385[69700])]);
            n2 = (int)n2_4;
            if ( n2_4[3] + v482 + v481 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n2_4);
              n0x10 = n0x10_1;
            }
            *(_WORD *)(n2 + v510 + 2) += (unsigned __int16)(*(_WORD *)n2 & 0xFFFC) >> 2;
            v483 = v385[69676] - v385[69700];
            n0xF0_2 = (unsigned __int16 *)&v385[2 * v483 + 2 * v385[69699]];
            n0x10_2 = v385[69701] + v483;
            n0xF0 = n0xF0_2;
            v485 = n0xF0_2 + 470036;
            if ( v485[3] + v485[2] + v485[1] > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(v485);
              n0x10 = n0x10_1;
            }
            *(unsigned __int16 *)((char *)v485 + v511 + 2) += (3 * (unsigned int)n0xF0[470036]) >> 4;
            if ( n15 >= 15 )
              goto LABEL_167;
            v486 = n0xF0[470041];
            v487 = n0xF0[470042];
            n2 = (int)(n0xF0 + 470040);
            if ( n0xF0[470043] + v487 + v486 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n0xF0 + 470040);
              n0x10 = n0x10_1;
            }
            *(_WORD *)(n2 + v511 + 2) += (unsigned __int16)(n0xF0[470040] & 0xFFFC) >> 2;
            v488 = (_WORD *)&v385[2 * n0x10_2 + 235020];
            if ( HIWORD(v385[2 * n0x10_2 + 235021])
               + LOWORD(v385[2 * n0x10_2 + 235021])
               + HIWORD(v385[2 * n0x10_2 + 235020]) > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800((unsigned __int16 *)&v385[2 * n0x10_2 + 235020]);
              n0x10 = n0x10_1;
            }
            *(_WORD *)((char *)v488 + v511 + 2) += (unsigned __int16)(*v488 & 0xFFF8) >> 3;
            if ( n15 > 2 )
            {
LABEL_167:
              v489 = n0xF0[470033];
              v490 = n0xF0[470034];
              n2 = (int)(n0xF0 + 470032);
              if ( n0xF0[470035] + v490 + v489 > 29696 )
              {
                n0x10_1 = n0x10;
                sub_414800(n0xF0 + 470032);
                n0x10 = n0x10_1;
              }
              *(_WORD *)(n2 + v511 + 2) += (6 * (unsigned int)n0xF0[470032]) >> 4;
            }
          }
          else
          {
            v420 = (unsigned __int16 *)&v385[2 * n0x10 + 235018 + 2 * (v385[69700] - v385[-v419 + 69701])];
            if ( HIWORD(v385[2 * n0x10 + 235019 + 2 * (v385[69700] - v385[-v419 + 69701])])
               + LOWORD(v385[2 * n0x10 + 235019 + 2 * (v385[69700] - v385[-v419 + 69701])])
               + HIWORD(v385[2 * n0x10 + 235018 + 2 * (v385[69700] - v385[-v419 + 69701])]) > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(v420);
              n0x10 = n0x10_1;
            }
            *(unsigned __int16 *)((char *)v420 + v510 + 2) += (7 * (unsigned int)*v420) >> 4;
            n0xF0 = (unsigned __int16 *)&v385[2 * v385[69700] + 2 * (v385[69676] - v385[v385[69698] + 69699])];
            v421 = n0xF0[470037];
            v422 = n0xF0[470038];
            n2 = (int)(n0xF0 + 470036);
            if ( n0xF0[470039] + v422 + v421 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n0xF0 + 470036);
              n0x10 = n0x10_1;
            }
            *(_WORD *)(n2 + v511 + 2) += (7 * (unsigned int)n0xF0[470036]) >> 4;
            if ( n15 >= 15 )
              goto LABEL_79;
            v423 = n0xF0[470041];
            v424 = n0xF0[470042];
            n2 = (int)(n0xF0 + 470040);
            if ( n0xF0[470043] + v424 + v423 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n0xF0 + 470040);
              n0x10 = n0x10_1;
            }
            *(_WORD *)(v511 + n2 + 2) += (5 * (unsigned int)n0xF0[470040]) >> 4;
            if ( n15 > 0 )
            {
LABEL_79:
              v425 = n0xF0[470033];
              v426 = n0xF0[470034];
              n2 = (int)(n0xF0 + 470032);
              if ( n0xF0[470035] + v426 + v425 > 29696 )
              {
                n0x10_1 = n0x10;
                sub_414800(n0xF0 + 470032);
                n0x10 = n0x10_1;
              }
              *(_WORD *)(n2 + v511 + 2) += (6 * (unsigned int)n0xF0[470032]) >> 4;
            }
          }
          v427 = v385[69702];
          if ( v427 == 1 )
          {
            n2_5 = (unsigned __int16 *)&v385[2 * v385[69703] + 235018 + 2 * (n0x10 - v385[69704])];
            v470 = HIWORD(v385[2 * v385[69703] + 235018 + 2 * (n0x10 - v385[69704])]);
            v471 = LOWORD(v385[2 * v385[69703] + 235019 + 2 * (n0x10 - v385[69704])]);
            n2 = (int)n2_5;
            if ( n2_5[3] + v471 + v470 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n2_5);
              n0x10 = n0x10_1;
            }
            *(_WORD *)(n2 + v510 + 2) += (unsigned __int16)(*(_WORD *)n2 & 0xFFFC) >> 2;
            v472 = v385[69676] - v385[69704];
            n0xF0_3 = (unsigned __int16 *)&v385[2 * v472 + 2 * v385[69703]];
            n0x10_2 = v385[69705] + v472;
            n0xF0 = n0xF0_3;
            v474 = n0xF0_3 + 470036;
            if ( v474[3] + v474[2] + v474[1] > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(v474);
              n0x10 = n0x10_1;
            }
            *(unsigned __int16 *)((char *)v474 + v511 + 2) += (3 * (unsigned int)n0xF0[470036]) >> 4;
            if ( n15 >= 15 )
              goto LABEL_154;
            v475 = n0xF0[470041];
            v476 = n0xF0[470042];
            n2 = (int)(n0xF0 + 470040);
            if ( n0xF0[470043] + v476 + v475 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n0xF0 + 470040);
              n0x10 = n0x10_1;
            }
            *(_WORD *)(n2 + v511 + 2) += (unsigned __int16)(n0xF0[470040] & 0xFFFC) >> 2;
            v477 = (_WORD *)&v385[2 * n0x10_2 + 235020];
            if ( HIWORD(v385[2 * n0x10_2 + 235021])
               + LOWORD(v385[2 * n0x10_2 + 235021])
               + HIWORD(v385[2 * n0x10_2 + 235020]) > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800((unsigned __int16 *)&v385[2 * n0x10_2 + 235020]);
              n0x10 = n0x10_1;
            }
            *(_WORD *)((char *)v477 + v511 + 2) += (unsigned __int16)(*v477 & 0xFFF8) >> 3;
            if ( n15 > 2 )
            {
LABEL_154:
              v478 = n0xF0[470033];
              v479 = n0xF0[470034];
              n2 = (int)(n0xF0 + 470032);
              if ( n0xF0[470035] + v479 + v478 > 29696 )
              {
                n0x10_1 = n0x10;
                sub_414800(n0xF0 + 470032);
                n0x10 = n0x10_1;
              }
              *(_WORD *)(n2 + v511 + 2) += (6 * (unsigned int)n0xF0[470032]) >> 4;
            }
          }
          else
          {
            v428 = (unsigned __int16 *)&v385[2 * n0x10 + 235018 + 2 * (v385[69704] - v385[-v427 + 69705])];
            if ( HIWORD(v385[2 * n0x10 + 235019 + 2 * (v385[69704] - v385[-v427 + 69705])])
               + LOWORD(v385[2 * n0x10 + 235019 + 2 * (v385[69704] - v385[-v427 + 69705])])
               + HIWORD(v385[2 * n0x10 + 235018 + 2 * (v385[69704] - v385[-v427 + 69705])]) > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(v428);
              n0x10 = n0x10_1;
            }
            *(unsigned __int16 *)((char *)v428 + v510 + 2) += (7 * (unsigned int)*v428) >> 4;
            n0xF0 = (unsigned __int16 *)&v385[2 * v385[69704] + 2 * (v385[69676] - v385[v385[69702] + 69703])];
            v429 = n0xF0[470037];
            v430 = n0xF0[470038];
            n2 = (int)(n0xF0 + 470036);
            if ( n0xF0[470039] + v430 + v429 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n0xF0 + 470036);
              n0x10 = n0x10_1;
            }
            *(_WORD *)(n2 + v511 + 2) += (7 * (unsigned int)n0xF0[470036]) >> 4;
            if ( n15 >= 15 )
              goto LABEL_91;
            v431 = n0xF0[470041];
            v432 = n0xF0[470042];
            n2 = (int)(n0xF0 + 470040);
            if ( n0xF0[470043] + v432 + v431 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n0xF0 + 470040);
              n0x10 = n0x10_1;
            }
            *(_WORD *)(v511 + n2 + 2) += (5 * (unsigned int)n0xF0[470040]) >> 4;
            if ( n15 > 0 )
            {
LABEL_91:
              v433 = n0xF0[470033];
              v434 = n0xF0[470034];
              n2 = (int)(n0xF0 + 470032);
              if ( n0xF0[470035] + v434 + v433 > 29696 )
              {
                n0x10_1 = n0x10;
                sub_414800(n0xF0 + 470032);
                n0x10 = n0x10_1;
              }
              *(_WORD *)(n2 + v511 + 2) += (6 * (unsigned int)n0xF0[470032]) >> 4;
            }
          }
          v435 = v385[69706];
          if ( v435 == 1 )
          {
            n2_6 = (unsigned __int16 *)&v385[2 * v385[69707] + 235018 + 2 * (n0x10 - v385[69708])];
            v459 = HIWORD(v385[2 * v385[69707] + 235018 + 2 * (n0x10 - v385[69708])]);
            v460 = LOWORD(v385[2 * v385[69707] + 235019 + 2 * (n0x10 - v385[69708])]);
            n2 = (int)n2_6;
            if ( n2_6[3] + v460 + v459 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n2_6);
              n0x10 = n0x10_1;
            }
            *(_WORD *)(n2 + v510 + 2) += (unsigned __int16)(*(_WORD *)n2 & 0xFFFC) >> 2;
            v461 = v385[69676] - v385[69708];
            n0xF0_4 = (unsigned __int16 *)&v385[2 * v461 + 2 * v385[69707]];
            n0x10_2 = v385[69709] + v461;
            n0xF0 = n0xF0_4;
            v463 = n0xF0_4 + 470036;
            if ( v463[3] + v463[2] + v463[1] > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(v463);
              n0x10 = n0x10_1;
            }
            *(unsigned __int16 *)((char *)v463 + v511 + 2) += (3 * (unsigned int)n0xF0[470036]) >> 4;
            if ( n15 >= 15 )
              goto LABEL_141;
            v464 = n0xF0[470041];
            v465 = n0xF0[470042];
            n2 = (int)(n0xF0 + 470040);
            if ( n0xF0[470043] + v465 + v464 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n0xF0 + 470040);
              n0x10 = n0x10_1;
            }
            *(_WORD *)(n2 + v511 + 2) += (unsigned __int16)(n0xF0[470040] & 0xFFFC) >> 2;
            v466 = (_WORD *)&v385[2 * n0x10_2 + 235020];
            if ( HIWORD(v385[2 * n0x10_2 + 235021])
               + LOWORD(v385[2 * n0x10_2 + 235021])
               + HIWORD(v385[2 * n0x10_2 + 235020]) > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800((unsigned __int16 *)&v385[2 * n0x10_2 + 235020]);
              n0x10 = n0x10_1;
            }
            *(_WORD *)((char *)v466 + v511 + 2) += (unsigned __int16)(*v466 & 0xFFF8) >> 3;
            if ( n15 > 2 )
            {
LABEL_141:
              v467 = n0xF0[470033];
              v468 = n0xF0[470034];
              n2 = (int)(n0xF0 + 470032);
              if ( n0xF0[470035] + v468 + v467 > 29696 )
              {
                n0x10_1 = n0x10;
                sub_414800(n0xF0 + 470032);
                n0x10 = n0x10_1;
              }
              *(_WORD *)(n2 + v511 + 2) += (6 * (unsigned int)n0xF0[470032]) >> 4;
            }
          }
          else
          {
            v436 = (unsigned __int16 *)&v385[2 * n0x10 + 235018 + 2 * (v385[69708] - v385[-v435 + 69709])];
            if ( HIWORD(v385[2 * n0x10 + 235019 + 2 * (v385[69708] - v385[-v435 + 69709])])
               + LOWORD(v385[2 * n0x10 + 235019 + 2 * (v385[69708] - v385[-v435 + 69709])])
               + HIWORD(v385[2 * n0x10 + 235018 + 2 * (v385[69708] - v385[-v435 + 69709])]) > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(v436);
              n0x10 = n0x10_1;
            }
            *(unsigned __int16 *)((char *)v436 + v510 + 2) += (7 * (unsigned int)*v436) >> 4;
            n0xF0 = (unsigned __int16 *)&v385[2 * v385[69708] + 2 * (v385[69676] - v385[v385[69706] + 69707])];
            v437 = n0xF0[470037];
            v438 = n0xF0[470038];
            n2 = (int)(n0xF0 + 470036);
            if ( n0xF0[470039] + v438 + v437 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n0xF0 + 470036);
              n0x10 = n0x10_1;
            }
            *(_WORD *)(n2 + v511 + 2) += (7 * (unsigned int)n0xF0[470036]) >> 4;
            if ( n15 >= 15 )
              goto LABEL_103;
            v439 = n0xF0[470041];
            v440 = n0xF0[470042];
            n2 = (int)(n0xF0 + 470040);
            if ( n0xF0[470043] + v440 + v439 > 29696 )
            {
              n0x10_1 = n0x10;
              sub_414800(n0xF0 + 470040);
              n0x10 = n0x10_1;
            }
            *(_WORD *)(v511 + n2 + 2) += (5 * (unsigned int)n0xF0[470040]) >> 4;
            if ( n15 > 0 )
            {
LABEL_103:
              v441 = n0xF0[470033];
              v442 = n0xF0[470034];
              n2 = (int)(n0xF0 + 470032);
              if ( n0xF0[470035] + v442 + v441 > 29696 )
              {
                n0x10_1 = n0x10;
                sub_414800(n0xF0 + 470032);
                n0x10 = n0x10_1;
              }
              *(_WORD *)(n2 + v511 + 2) += (6 * (unsigned int)n0xF0[470032]) >> 4;
            }
          }
          v443 = v385[69710];
          if ( v443 == 1 )
          {
            n2_7 = (unsigned __int16 *)&v385[2 * v385[69711] + 235018 + 2 * (n0x10 - v385[69712])];
            v447 = HIWORD(v385[2 * v385[69711] + 235018 + 2 * (n0x10 - v385[69712])]);
            v448 = LOWORD(v385[2 * v385[69711] + 235019 + 2 * (n0x10 - v385[69712])]);
            v449 = n2_7[3];
            n2 = (int)n2_7;
            if ( v449 + v448 + v447 > 29696 )
              sub_414800(n2_7);
            *(_WORD *)(n2 + v510 + 2) += (unsigned __int16)(*(_WORD *)n2 & 0xFFFC) >> 2;
            v450 = v385[69676] - v385[69712];
            n0x10_4 = (unsigned __int16 *)&v385[2 * v450 + 2 * v385[69711]];
            n0xF0 = (unsigned __int16 *)(v385[69713] + v450);
            n0x10_2 = (unsigned int)n0x10_4;
            v452 = n0x10_4 + 470036;
            if ( n0x10_4[470039] + n0x10_4[470038] + n0x10_4[470037] > 29696 )
              sub_414800(v452);
            *(unsigned __int16 *)((char *)v452 + v511 + 2) += (3 * (unsigned int)*(unsigned __int16 *)(n0x10_2 + 940072)) >> 4;
            if ( n15 >= 15 )
              goto LABEL_128;
            v453 = *(unsigned __int16 *)(n0x10_2 + 940086);
            v454 = *(unsigned __int16 *)(n0x10_2 + 940084) + *(unsigned __int16 *)(n0x10_2 + 940082);
            n2 = n0x10_2 + 940080;
            if ( v453 + v454 > 29696 )
              sub_414800((unsigned __int16 *)(n0x10_2 + 940080));
            n0xF0_5 = n0xF0;
            *(_WORD *)(n2 + v511 + 2) += (unsigned __int16)(*(_WORD *)(n0x10_2 + 940080) & 0xFFFC) >> 2;
            v456 = (unsigned __int16 *)&v385[2 * (_DWORD)n0xF0_5 + 235020];
            if ( v456[3] + v456[2] + v456[1] > 29696 )
              sub_414800(v456);
            n0x10 = (unsigned __int16)(*v456 & 0xFFF8) >> 3;
            *(unsigned __int16 *)((char *)v456 + v511 + 2) += n0x10;
            if ( n15 > 2 )
            {
LABEL_128:
              v457 = (unsigned __int16 *)(n0x10_2 + 940064);
              if ( *(unsigned __int16 *)(n0x10_2 + 940070)
                 + *(unsigned __int16 *)(n0x10_2 + 940068)
                 + *(unsigned __int16 *)(n0x10_2 + 940066) > 29696 )
                sub_414800((unsigned __int16 *)(n0x10_2 + 940064));
              n0x10 = n0x10_2;
              *(unsigned __int16 *)((char *)v457 + v511 + 2) += (6
                                                               * (unsigned int)*(unsigned __int16 *)(n0x10_2 + 940064)) >> 4;
            }
          }
          else
          {
            v444 = (unsigned __int16 *)&v385[2 * n0x10 + 235018 + 2 * (v385[69712] - v385[-v443 + 69713])];
            if ( HIWORD(v385[2 * n0x10 + 235019 + 2 * (v385[69712] - v385[-v443 + 69713])])
               + LOWORD(v385[2 * n0x10 + 235019 + 2 * (v385[69712] - v385[-v443 + 69713])])
               + HIWORD(v385[2 * n0x10 + 235018 + 2 * (v385[69712] - v385[-v443 + 69713])]) > 29696 )
              sub_414800(v444);
            *(unsigned __int16 *)((char *)v444 + v510 + 2) += (7 * (unsigned int)*v444) >> 4;
            v445 = (unsigned __int16 *)&v385[2 * v385[69712] + 2 * (v385[69676] - v385[v385[69710] + 69711])];
            if ( v445[470039] + v445[470038] + v445[470037] > 29696 )
              sub_414800(v445 + 470036);
            *(unsigned __int16 *)((char *)v445 + v511 + 940074) += (7 * (unsigned int)v445[470036]) >> 4;
            if ( n15 >= 15 )
              goto LABEL_115;
            if ( v445[470043] + v445[470042] + v445[470041] > 29696 )
              sub_414800(v445 + 470040);
            n0x10 = v445[470040];
            *(unsigned __int16 *)((char *)v445 + v511 + 940082) += (5 * n0x10) >> 4;
            if ( n15 > 0 )
            {
LABEL_115:
              if ( v445[470035] + v445[470034] + v445[470033] > 29696 )
                sub_414800(v445 + 470032);
              n0x10 = v445[470032];
              *(unsigned __int16 *)((char *)v445 + v511 + 940066) += (6 * n0x10) >> 4;
            }
          }
        }
        return n0x10;
      }
      v387 = (unsigned __int16 *)&v385[2 * v385[69676]];
    }
    v394 = v387[470033];
    v395 = v387[470034];
    n2 = (int)(v387 + 470032);
    if ( v387[470035] + v395 + v394 > 29696 )
      sub_414800(v387 + 470032);
    v396 = (13 * (unsigned int)v387[470032]) >> 4;
    if ( a4 )
    {
      *(_WORD *)(n2 - 2 * v511 + 6) += v396;
      sub_413430((unsigned __int16 *)__sub_41CAB0_n256_1 + 254 * (_DWORD)v508 - 254, (a4 - 1) >> 1);
    }
    else
    {
      *(_WORD *)(n2 + 2) += v396;
    }
    goto LABEL_37;
  }
  return n0x10;
}

// __userpurge thunk for sub_41CAB0 @ 0x0041CAB0: reads the register arguments the
// caller passes, calls the moved body as cdecl, and pops 12 bytes of
// stack on return.
BMF_SSE __attribute__((naked)) static void __thunk_sub_41CAB0()
{
  __asm__ volatile(
    "push %ebp\n"
    "mov %esp, %ebp\n"
    "push %ebx\n"
    "push %esi\n"
    "push %edi\n"
    "and $-16, %esp\n"
    "sub $44, %esp\n"
    "mov %ecx, 12(%esp)\n"
    "movups %xmm3, 28(%esp)\n"
    "push 16(%ebp)\n"
    "push 12(%ebp)\n"
    "push 8(%ebp)\n"
    "lea 40(%esp), %eax\n"
    "push %eax\n"
    "push 28(%esp)\n"
    "call __sub_41CAB0\n"
    "lea -12(%ebp), %esp\n"
    "pop %edi\n"
    "pop %esi\n"
    "pop %ebx\n"
    "leave\n"
    "ret $12\n"
  );
}

#undef sub_413430
#undef sub_414800
