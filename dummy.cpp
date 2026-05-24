#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include <stdint.h>
#include <ctype.h>

#ifdef _MSC_VER
#include <process.h>   // _exit
#include <io.h>        // _chsize, _fileno
#else
#include <unistd.h>    // _exit, ftruncate
#define _chsize(fd, sz) ftruncate(fd, sz)
#endif

#ifdef __GNUC__
#define _fileno fileno
#endif

//--- #include "defs1.h"

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned short word;
typedef unsigned long long qword;
typedef long long sqword;
typedef unsigned __int128 hword;
typedef __int128 shword;

// Some convenience macros to make partial accesses nicer
#define LAST_IND(x,part_type)    (sizeof(x)/sizeof(part_type) - 1)
#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN
#  define LOW_IND(x,part_type)   LAST_IND(x,part_type)
#  define HIGH_IND(x,part_type)  0
#else
#  define HIGH_IND(x,part_type)  LAST_IND(x,part_type)
#  define LOW_IND(x,part_type)   0
#endif

#define BYTEn(x, n)   (*((byte*)&(x)+n))
#define WORDn(x, n)   (*((word*)&(x)+n))
#define DWORDn(x, n)  (*((uint*)&(x)+n))

#define LOBYTE(x)  BYTEn(x,LOW_IND(x,byte))
#define LOWORD(x)  WORDn(x,LOW_IND(x,word))
#define LODWORD(x) ((qword&)x)
#define HIBYTE(x)  BYTEn(x,HIGH_IND(x,byte))
#define HIWORD(x)  WORDn(x,HIGH_IND(x,word))
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE4(x)   BYTEn(x,  4)
#define WORD2(x)   WORDn(x,  2)         // third word of the object

uint abs32( int x ) { return x >= 0 ? x : -x; }
//--- #return

namespace {

//--- #include "defs3g.h"

//constexpr uint blob1_len = 0x141137200-0x1400227B0;
//byte blob1[blob1_len];

char b24[16] = {-3,-2,-1,-1,-1,0,0,0,0,0,0,0,2,3,4,0};
char FreqRescaleTab[36] = {2,3,3,3,4,4,4,5,5,6,6,6,7,7,7,7,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10};
char b17[16] = {10,-19,-24,17,34,27,2,5,2,31,20,-16,17,30,0,0};
char b18[16] = {45,73,84,90,116,122,121,126,-106,-109,-100,-75,-96,-38,0,0};
char b20[16] = {5,-4,12,7,47,0,-3,1,16,25,5,11,-2,0,0,0};
char b21[24] = {1,2,5,1,2,5,0,5,20,18,24,24,39,44,64,65,77,90,99,99,124,-119,-82,-53};
char b22[8] = {-128,-64,-56,-32,-40,0,0,0};
char b23[28] = {76,-118,-122,-95,-70,0,0,0,0,0,0,0,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32};

byte RLQBounds[16] = {1,2,3,4,5,6,8,11,13,20,50,68,117,0,0,0};
byte SSE0QBounds[16] = {0,1,3,10,14,27,44,65,88,125,byte(-87),byte(-42),byte(-15),0,0,0};
byte SSE1QBounds[8] = {1,2,7,17,0,0,0,0};
byte SEEQBounds[8] = {1,13,43,byte(-74),0,0,0,0};

char b41[32]= {17,63,68,26,110,20,119,24,110,20,-85,10,-84,25,-126,22,105,74,60,84,44,92,23,100,44,121,0,0,0,0,0,0};

byte Units2Indx[132];
auto& Units2Indx4 = (byte(&)[128])Units2Indx[4];
char& b11 = (char&)Units2Indx4[127];

uint BinMapTable[16];
char SSE1QTable[128];
char SEEQTable[256];
byte SSE0[256];
byte SSE1[256];
char NextBinFreq[128];
byte SSE0QTable[256];
int BinSse[0x280];

int MixWeight1[0xF0000/2]; // memset(MixWeight1, 0, 0x20000);
short& MixFreq1 = (short&)MixWeight1[2/2];
auto& MixFreq1_1 = *(short(*)[0xF0000-3])(((char*)MixWeight1)+6);

int d29[0x2040];
short& w12 = *(short*)((char*)&d29 + (0x141128C24-0x141128C20));
auto& w11 = (short(&)[0x407D])((char*)&d29)[0x141128C26-0x141128C20];

int PredWeight[0xA1C];
int* PredWeight_1 = &PredWeight[1];

int d27[0x70040];
auto& MixBound2 = (short(&)[0x70040*2-0x00002])((char*)&d27)[0x1405DFC24-0x1405DFC20];
auto& MixBound3 = (short(&)[0x70040*2-0x00003])((char*)&d27)[0x1405DFC26-0x1405DFC20];
auto& MixBound6 = (short(&)[0x70040*2-0x08003])((char*)&d27)[0x1405EFC26-0x1405DFC20];
auto& b19       = (short(&)[0x70040*2-0xD0000])((char*)&d27)[0x14077FC20-0x1405DFC20];
auto& MixBound5 = (short(&)[0x70040*2-0xD0003])((char*)&d27)[0x14077FC26-0x1405DFC20];
auto& MixBound4 = (short(&)[0x70040*2-0xD8003])((char*)&d27)[0x14078FC26-0x1405DFC20];

char SymType[256];

int SymMask[256];

int SymLastCtx[1024];
int* SymLastCtx2 = &SymLastCtx[256];
int* MatchPosBySym = &SymLastCtx[512];
char BijectMap[0x40000];
int d82;
char b25;
sqword q26;
int MixScale;
int d72;
int FoundSymbol;
int HashSeed2;
int HashSeed1;
int RSContext;

sqword CtxChain[0x100];
sqword& CtxChain_1 = CtxChain[1];
sqword* CtxChain_2 = &CtxChain[2];
sqword* CtxChain_4 = &CtxChain[4];

char b16[0x20000];
short* const MixBound1 = (short*)&b16[6];

int Sse1[0x60040];
int* Sse1_1 = &Sse1[1];

int Sse2[0x30040];
int* Sse2_1 = &Sse2[1];

int Sse3[0x2A03E];
int* Sse3_1 = &Sse3[1];

char b39[256];

int MixWeight2[0x8040];
auto& MixFreq2_1 = (short(&)[0x803F*2])MixWeight2[1];
short* MixFreq2 = &MixFreq2_1[1];


int d90[4096];
int& d79 = d90[2];
int& d66 = d90[3];
int& Order1Ctx = d90[4];
int& d65 = d90[5];
int& d67 = d90[6];
int& d76 = d90[7];
int& d88 = d90[8];
int& d89 = d90[9];
int& matchHashSy = d90[10];
int& matchPosAge = d90[11];
int& matchEpoch2 = d90[12];
int& d75 = d90[13];
int& sseState3Hash = d90[14];
int* RecentPos = &d90[15];

shword SEE2_5[70];
shword* SEE2_4 = &SEE2_5[1];
shword* SEE2_3 = &SEE2_5[2];
shword* SEE2_2 = &SEE2_5[3];
shword* SEE2_1 = &SEE2_5[4];
shword* SEE2 = &SEE2_5[5];
int* SseCtx0 = (int*)&SEE2_5[6];
int* SseCtx0_1 = &SseCtx0[3];

int SseMatch[0x200040];
int* SseMatch_1 = &SseMatch[1];

int MatchPosPrev[131072];
int MatchPosTable[0x10000];
int SparseBitmapA[0x4000];
int SparseBitmapB[0x10000];

byte Indx2Units[48];
sqword HiUnit;
sqword LoUnit;
sqword pText;
sqword UnitsStart;
sqword BList;
sqword MaxContext0;
sqword HeapNull;

sqword q37;
sqword q39;
sqword RootContext;

int InitsCount;
int GlueCount;
int CutOffCount;
int MaxOrder;
int CutOff;
int Interrupted;
int RunLength;
int SymCount;
int MixCtx3;
int EscapeSymbol;
int SymEpoch;
int MixCtxExtra;
int OrderFall;
int MixCtx;
int MixCtx2;
int PrevSymbol;
int OrderCtxSeed;
int SseSeed;
int EscIndexSeed;
int d111;
int NMasked;

sqword q38;
int d112;
int d113;
int d16;
int OrderFall0;
int SolidInterrupt = 0;
byte freqmap[0x100];
void* FileName = 0;
void* HeapStart = 0;
sqword SubAllocatorSize = 0;
int f_ENC = 0;
int f_LOG = 0;

int sseTot;
int sseCum;
int d93;
int d110;
int d48;
int d49;
int d46;
int d47;
int d99;
int d100;
int d101;
int d102;
int d105;
int d104;
int predRescaleDiv;
int cumFreqAcc;
int d98;
int d103;
int d106;

sqword q32;
sqword q31;
sqword q30;
sqword q29;
sqword q34;
sqword q35;
sqword q21;
sqword q22;
sqword q18;
sqword q23;
sqword q20;
sqword q17;
sqword q36;
sqword q19;
sqword q24;
sqword q25;
sqword q9;
sqword q33;
sqword CtxChainEnd;

int d83;
int d84;
int d85;
int d92;
int d86;
int d87;
int d52;
int d50;
int d54;
int d53;
int d56;
int d55;
int MatchCtxHi;
int recentSym;
int d80;
int d91;
int SparseHashA;
int SparseIdxA;
int SparseHashB;
int SparseIdxB;
int SparseBit;


//typedef byte t_byte_140029940[0x2358D0]; t_byte_140029940& Sse2State = *(t_byte_140029940*)(blob1+ 0x140029940 -0x1400227B0);
//byte Sse2State[0x2358D0];
byte Sse2State[0xC0818];
sqword& q12 = *(sqword*)((byte*)&Sse2State + (0x14002A150-0x140029940));
typedef byte t_byte_14002A158[0x40000]; t_byte_14002A158& MatchPosHash = *(t_byte_14002A158*)((byte*)&Sse2State + (0x14002A158-0x140029940));
typedef byte t_byte_14006A158[0x80000]; t_byte_14006A158& SseState2 = *(t_byte_14006A158*)((byte*)&Sse2State + (0x14006A158-0x140029940));
typedef byte t_byte_14007A158[0x10000]; t_byte_14007A158& b28 = *(t_byte_14007A158*)((byte*)&Sse2State + (0x14007A158-0x140029940));
typedef byte t_byte_14008A158[0x10000]; t_byte_14008A158& b29 = *(t_byte_14008A158*)((byte*)&Sse2State + (0x14008A158-0x140029940));
typedef byte t_byte_14009A158[0x10000]; t_byte_14009A158& b30 = *(t_byte_14009A158*)((byte*)&Sse2State + (0x14009A158-0x140029940));
typedef byte t_byte_1400AA158[0x10000]; t_byte_1400AA158& b31 = *(t_byte_1400AA158*)((byte*)&Sse2State + (0x1400AA158-0x140029940));

typedef byte t_byte_1400BA158[0x10000]; t_byte_1400BA158& b34 = *(t_byte_1400BA158*)((byte*)&Sse2State + (0x1400BA158-0x140029940));
byte* b35 = &b34[1];

typedef byte t_byte_1400CA158[0x10000]; t_byte_1400CA158& b36 = *(t_byte_1400CA158*)((byte*)&Sse2State + (0x1400CA158-0x140029940));
byte* b37 = &b36[1];
byte* b33 = &b36[2];
byte* b32 = &b36[3];

typedef byte t_byte_1400DA158[0x10000]; t_byte_1400DA158& b27 = *(t_byte_1400DA158*)((byte*)&Sse2State + (0x1400DA158-0x140029940));
//typedef byte t_byte_1400EA158[0x20000]; t_byte_1400EA158& SseState3 = *(t_byte_1400EA158*)((byte*)&Sse2State + (0x1400EA158-0x140029940));



// Sse2State ends at 14025F210
// cur size = 0xC0008

byte SseState3[0x20000];

//byte MatchPosHash[0x40000];

//byte SseState2[0x80000];

//byte b28[0x10000];

//--- #return
//--- #include "context.h"

enum { 
  UNIT_SIZE = 12, N_INDEXES = 38
};

// Reconstructs an absolute pointer from a 32-bit field like iStates of iSuffix or iSuccessor
void* Indx2Ptr(uint indx) {
  return (void*)(HeapNull+indx);
}

uint Ptr2Indx( const void* p ) {
  return ((byte*)p) - ((byte*)HeapNull);
}

uint Ptr2Indx( sqword p ) {
  return ((byte*)p) - ((byte*)HeapNull);
}

struct MixModel {
  int weight;
  short freq0;
  short freq1;
};

#pragma pack(1)
struct SEE_CONTEXT {
  enum { MAX_SHIFT = 8 };

  word Summ;
  byte Shift, Count;

  void init(uint InitVal) {
    Summ = InitVal<<(Shift = 3);
    Count = 14;
  }
};

struct STATE {
  byte Symbol, Freq;
  uint iSuccessor;
};
struct PPM_CONTEXT {
  enum { MAX_FREQ = 123, O_BOUND = 9 };
  byte NStates, Flags;
  word SummFreq;
  uint iStates;
  uint iSuffix;

  STATE &oneState() const {
    return (STATE &)SummFreq;
  }

  STATE*getStates() const {
    return (STATE*)Indx2Ptr(iStates);
  }

  PPM_CONTEXT*getSuffix() const {
    return (PPM_CONTEXT*)Indx2Ptr(iSuffix);
  }
};
#pragma pack()

#pragma pack(1)
struct MEM_BLK {
  union {
    struct {
      byte NU, Stamp;
    };
    uint QueueSize;
  };
  uint Next;
  uint Prev;

  MEM_BLK* next() const { return (MEM_BLK*)Indx2Ptr(Next); }
  MEM_BLK* prev() const { return (MEM_BLK*)Indx2Ptr(Prev); }

  uint avail() const { return (QueueSize!=0); }

  MEM_BLK* unlinkPrev() {
    MEM_BLK* p = prev();
    Prev = p->Prev;
    p->prev()->Next = Ptr2Indx(this);
    QueueSize--;
    return p;
  }

  void linkNext( MEM_BLK* p, uint NU, byte Stamp=0xFF ) {
    p->Stamp = Stamp;
    p->NU = NU;
    p->Prev = Ptr2Indx(this);
    p->Next = Next;
    Next = next()->Prev = Ptr2Indx(p);
    QueueSize++;
  }

  // linkPrev(): queue-tail insert (counterpart to linkNext).
  void linkPrev( MEM_BLK* p, uint NU, byte Stamp=0xFF ) {
    p->Stamp = Stamp;
    p->NU = NU;
    p->Next = Ptr2Indx(this);
    p->Prev = Prev;
    Prev = prev()->Next = Ptr2Indx(p);
    QueueSize++;
  }

  // unlinkNext(): pop the block following this queue head.
  MEM_BLK* unlinkNext() {
    MEM_BLK* p = next();
    Next = p->Next;
    p->next()->Prev = Ptr2Indx(this);
    QueueSize--;
    return p;
  }

  uint canMerge() const {
    return (Stamp==byte(-1));
  }

};
#pragma pack()

//MEM_BLK* BList;

STATE* GetStatesPtr(uint iStates) {
  return (STATE*)Indx2Ptr(iStates);
}

PPM_CONTEXT* GetSuffixPtr(uint iSuffix) {
  return (PPM_CONTEXT*)Indx2Ptr(iSuffix);
}

// ===========================================================================
//  Sub-allocator inline helpers, modelled on the textbook ppmd.cpp
//  primitives. Multiple subs_*.inc files inline these manually; using these
//  named wrappers makes the cleaned-up versions of those files readable.
//
//  They depend on FreeUnitsRare() which is defined in subs_freeunitsrare1.inc;
//  it is forward-declared here so the inline bodies can call it.
// ===========================================================================

char* FreeUnitsRare(sqword a1, uint a2);   // defined in subs_freeunitsrare1.inc

inline void UnitsCpy_(void* Dest, const void* Src, uint NU) {
  uint* p1 = (uint*)Dest;
  const uint* p2 = (const uint*)Src;
  if (NU & 1) {
    p1[0] = p2[0]; p1[1] = p2[1]; p1[2] = p2[2];
    p1 += 3; p2 += 3;
  }
  for (NU >>= 1; NU != 0; --NU, p1 += 6, p2 += 6) {
    p1[0] = p2[0]; p1[1] = p2[1]; p1[2] = p2[2];
    p1[3] = p2[3]; p1[4] = p2[4]; p1[5] = p2[5];
  }
}

inline void FreeUnits_(void* ptr, uint NU) {
  MEM_BLK*& BList_ = (MEM_BLK*&)::BList;
  uint indx = Units2Indx4[NU - 1];
  NU = Indx2Units[indx];
  MEM_BLK* p = (MEM_BLK*)ptr;
  if (!p[NU].canMerge())
    BList_[indx].linkNext(p, NU);
  else
    FreeUnitsRare((sqword)p, NU);
}

inline void FreeContext_(void* ptr) {
  MEM_BLK*& BList_ = (MEM_BLK*&)::BList;
  MEM_BLK* p = (MEM_BLK*)ptr;
  if (!p[1].canMerge())
    BList_[0].linkPrev(p, 1);
  else
    FreeUnitsRare((sqword)p, 1);
}

inline void* MoveUnits_(void* OldPtr, uint NU) {
  MEM_BLK*& BList_ = (MEM_BLK*&)::BList;
  uint indx = Units2Indx4[NU - 1];
  uint NewNU = Indx2Units[indx];
  MEM_BLK* p = (MEM_BLK*)OldPtr;
  if (!p[NewNU].canMerge() || !BList_[indx].avail()) return OldPtr;
  void* NewPtr = BList_[indx].unlinkNext();
  UnitsCpy_(NewPtr, OldPtr, NU);
  FreeUnitsRare((sqword)p, NewNU);
  return NewPtr;
}

inline void* ShrinkUnits_(void* OldPtr, uint OldNU, uint NewNU) {
  MEM_BLK*& BList_ = (MEM_BLK*&)::BList;
  uint i0 = Units2Indx4[OldNU - 1];
  uint i1 = Units2Indx4[NewNU - 1];
  if (i0 == i1) return OldPtr;
  if (BList_[i1].avail()) {
    void* ptr = BList_[i1].unlinkNext();
    UnitsCpy_(ptr, OldPtr, NewNU);
    FreeUnits_(OldPtr, Indx2Units[i0]);
    return ptr;
  }
  NewNU = Indx2Units[i1];
  FreeUnitsRare((sqword)((MEM_BLK*)OldPtr + NewNU), Indx2Units[i0] - NewNU);
  return OldPtr;
}

inline void* MoveContext_(void* OldPtr) {
  MEM_BLK*& BList_ = (MEM_BLK*&)::BList;
  MEM_BLK* p = (MEM_BLK*)OldPtr;
  if (!p[1].canMerge() || !BList_[0].avail()) return OldPtr;
  void* NewPtr = BList_[0].unlinkPrev();
  UnitsCpy_(NewPtr, OldPtr, 1);
  FreeUnitsRare((sqword)p, 1);
  return NewPtr;
}
//--- #return

//--- #include "subs_contextwalk.inc"

// 1. Maximum Order boundary definition
// Deduced from the maximum path depth condition check: `if (path_depth < 32)`
constexpr int MAX_O = 128;

// 2. MaxContext definition implemented via an lvalue reference mapping to MaxContext0
// #define MaxContext (*(PPM_CONTEXT**)&MaxContext0)
// Alternatively, using a explicit C++ reference variable:
PPM_CONTEXT*&MaxContext = *(PPM_CONTEXT**)&MaxContext0;

sqword BinEscFreq(byte* a1);

// Walks the context suffix chain to update local frequency statistics, perform inertia
// scaling adjustments, and calculate state metrics for context-mixing/predictive modeling.
static void PPMContextWalk(int epoch, int sym, uint* outSeeIndex, uint* outSuffixNStates, int* outMixCtx, sqword* outSummFreqPtr, int* outSparseFlags) {
  // Collect path context history down from the current maximum context
  PPM_CONTEXT* path[MAX_O];
  int path_depth = 0;

  PPM_CONTEXT* curr = MaxContext;
  RSContext = sym;
  SymLastCtx[(byte)b27[sym+(Order1Ctx<<8)]] = epoch;

  // Step 1: Climb suffixes until a context with non-zero states is encountered
  do {
    path[path_depth++] = curr;
    curr = (PPM_CONTEXT*)Indx2Ptr(curr->iSuffix);
  } while( !curr->NStates );

  PPM_CONTEXT* ctx = curr;
  uint last_nstates = ctx->NStates;
  uint total_depth = path_depth;

  // Step 2: Suffix frequency verification chain
  STATE* last_state = ctx->getStates()+ctx->NStates;
  if( last_state->Freq==0 ) {
    uint temp_depth = path_depth;
    do {
      if( last_state->Symbol!=sym )
        break;
      ctx = (PPM_CONTEXT*)Indx2Ptr(ctx->iSuffix);
      last_nstates = ctx->NStates;
      ++temp_depth;
      last_state = ctx->getStates()+last_nstates;
    } while( last_state->Freq==0 );

    total_depth = temp_depth;
  }

  // Capture pre-rescale NStates tracking metric (v226)
  uint verification_nstates = ctx->NStates;

  // Step 3: Check escape condition and handle low-frequency model rescaling
  if( ctx->getStates()[ctx->Flags&0x0F].Freq==0 ) {
    BinEscFreq((byte*)ctx);
  }

  // FIX BUG 1: Track the updated primary escape symbol back out to global context state
  EscapeSymbol = ctx->getStates()[ctx->Flags&0x0F].Symbol;

  // Step 4: Locate the target symbol in the current states array
  STATE* states = ctx->getStates();
  STATE* found_state = states;
  if( sym!=states->Symbol ) {
    do {
      found_state++;
    } while( sym!=found_state->Symbol );
  }

  // Step 5: Advanced local frequency scaling optimization (Inertia Tuning)
  word summ_freq = ctx->SummFreq;
  if( 2*found_state->Freq+23>states[0].Freq+states[1].Freq ) {
    if( ctx->iSuffix ) {
      PPM_CONTEXT* suffix_ctx = (PPM_CONTEXT*)Indx2Ptr(ctx->iSuffix);
      word suffix_summ_freq = suffix_ctx->SummFreq;
      byte suffix_nstates = suffix_ctx->NStates;

      // Uses pre-rescale context state metrics (v544 -> verification_nstates + 1)
      if( summ_freq+summ_freq*suffix_nstates<(verification_nstates+1)*(suffix_summ_freq+15) ) {
        if( suffix_ctx->getStates()[suffix_ctx->Flags&0x0F].Freq==0 ) {
          BinEscFreq((byte*)suffix_ctx);
          suffix_summ_freq = suffix_ctx->SummFreq;
          summ_freq = ctx->SummFreq; // Synchronize just in case
        }

        STATE* suffix_state;
        for( suffix_state = suffix_ctx->getStates(); sym!=suffix_state->Symbol; suffix_state++ )
          ;
        int suffix_found_freq = suffix_state->Freq;
        int base_weight = 5*verification_nstates+5;
        uint tunedSumm = summ_freq+2*base_weight;
        int tunedSuffix = (2*(2*base_weight<summ_freq)+5)*(suffix_nstates+1)+suffix_summ_freq;
        if( tunedSuffix*found_state->Freq<(int)(tunedSumm*suffix_found_freq) ) {
          if( found_state->Freq>228 )
            goto TARGET_SCALE_FALLBACK;
          word delta_freq = summ_freq-found_state->Freq;
          uint adjusted_freq = ((tunedSumm-found_state->Freq)*(suffix_found_freq+3*found_state->Freq)+3*(tunedSumm-found_state->Freq)+tunedSuffix-suffix_found_freq-4)/(3*(tunedSumm-found_state->Freq)+tunedSuffix-suffix_found_freq);
          if( adjusted_freq>found_state->Freq+11 ) {
            adjusted_freq = found_state->Freq+11;
          }

          summ_freq = adjusted_freq+delta_freq;
          ctx->SummFreq = summ_freq;
          found_state->Freq = adjusted_freq;
        }
      }
    }
  }

TARGET_SCALE_FALLBACK:
  // Step 6: Quantize frequency threshold mappings
  uint freq_bound;
  if( found_state->Freq<=9 ) {
    freq_bound = freqmap[found_state->Freq-1];
  } else {
    freq_bound = found_state->Freq-6;
  }

  uint scale_diff = summ_freq-freq_bound;
  uint path_threshold = (6*scale_diff<freq_bound)+(15*scale_diff<4*freq_bound)+(9*scale_diff<4*freq_bound)+(13*scale_diff<8*freq_bound)+(scale_diff<freq_bound)+(scale_diff<2*freq_bound)+(scale_diff<6*freq_bound)+(35*scale_diff<4*freq_bound)+1;

  // Save initial path threshold expression result for global metrics
  uint initial_threshold = path_threshold;

  // Step 7: Update upper frequency byte on all walked paths
  PPM_CONTEXT* path_ctx = nullptr;
  for( int i = path_depth-1; i>=0; i-- ) {
    path_ctx = path[i];
    byte* high_byte_ptr = ((byte*)&path_ctx->SummFreq)+1;
    if( path_threshold>*high_byte_ptr ) {
      *high_byte_ptr = path_threshold;
    } else {
      path_threshold = *high_byte_ptr;
    }
  }

  // FIX BUG 2: Synchronize variance tracking value to the context mixing stage
  d93 = path_threshold-initial_threshold;

  // Set the low-level pointer output to the updated context summary tracking byte
  *outSummFreqPtr = (sqword)((byte*)&path_ctx->SummFreq);

  // Step 8: Calculate context metrics and model hash indicators for the Mixer/LSTM stage
  SparseBit = 1<<sym;
  SparseIdxA = (uint)(sym+SparseHashA)>>5;
  SparseIdxB = (uint)(sym+SparseHashB)>>5;
  int sparseFlags = (((1<<sym)&SparseBitmapA[(uint)(sym+SparseHashA)>>5])!=0)+2*(((1<<sym)&SparseBitmapB[(uint)(sym+SparseHashB)>>5])!=0);
  int matchTableEntry = MatchPosTable[sym+(MatchCtxHi<<8)];
  if( (uint)(SymEpoch-matchTableEntry)>=0x20000 ) {
    matchEpoch2 = 0x20000;
    matchPosAge = 0x20000;
    matchHashSy = 0x20000;
  } else {
    matchPosAge = MatchPosTable[sym+(MatchCtxHi<<8)];
    matchHashSy = (byte)MatchPosHash[(matchTableEntry+2)&0x1FFFF];
    matchPosAge = SymEpoch-matchTableEntry;
    matchEpoch2 = SymEpoch-MatchPosTable[matchHashSy+(sym<<8)];
  }

  PPM_CONTEXT* max_suffix_ctx = (PPM_CONTEXT*)Indx2Ptr(MaxContext->iSuffix);
  uint suffixNStates = max_suffix_ctx->NStates;
  int mixCtxBoost = 32*(RunLength>0)+(MaxContext->Flags&0x80);
  MixCtxExtra += (suffixNStates==0)<<7;

  uint v548_val = OrderFall-total_depth;
  int mixCtxBase = MixCtx+((4*(OrderFall-total_depth>3)+8*(sym==ctx->getStates()[ctx->Flags&0x0F].Symbol)+(sym==FoundSymbol)+2*(epoch==SymLastCtx[sym]))<<9)+mixCtxBoost+((sparseFlags==3||epoch==MatchPosBySym[sym])<<13);
  int mixCtx2Bits = (((MixCtx2&6)==6)<<8)+((MixCtx2&1)<<6);
  int mixCtxComposite = mixCtxBase+mixCtx2Bits;

  int mixCtx;
  if( suffixNStates ) {
    uint mixCtxMasked = mixCtxComposite&0xFFFFFFDE;
    uint boostBit = (path_threshold!=initial_threshold)||(scale_diff<=10*freq_bound);

    mixCtx = 32*boostBit+mixCtxMasked+(sym==PrevSymbol);
  } else {
    PPM_CONTEXT* deep_suffix_ctx = (PPM_CONTEXT*)Indx2Ptr(max_suffix_ctx->iSuffix);
    suffixNStates = deep_suffix_ctx->NStates;
    if( deep_suffix_ctx->NStates||v548_val<4||(v548_val<5&&(verification_nstates+1)<4&&ctx->SummFreq-found_state->Freq<36) ) {

      uint suffix_chain_idx = deep_suffix_ctx->iSuffix;
      uint deeperBit = 0;
      if( suffix_chain_idx ) {
        PPM_CONTEXT* deeper_suffix_ctx = (PPM_CONTEXT*)Indx2Ptr(suffix_chain_idx);
        deeperBit = (2*suffixNStates<deeper_suffix_ctx->NStates);
      }
      mixCtx = mixCtxComposite+8*deeperBit+16;
    } else if( path_depth>=6 ) {
      if( path_depth>=14 ) {
        mixCtx = mixCtxBase+mixCtx2Bits+14;
        if( path_depth<32 )
          mixCtx = mixCtxBase+mixCtx2Bits+12;
      } else {
        mixCtx = mixCtxBase+mixCtx2Bits+10;
      }
    } else {
      mixCtx = mixCtxBase+mixCtx2Bits+8;
    }
  }

  *outSeeIndex = path_threshold;
  *outSuffixNStates = suffixNStates;
  *outMixCtx = mixCtx;
  *outSparseFlags = sparseFlags;
}
//--- #return
//--- #include "subs_inittables.inc"

// PPMII_STARTUP actually
sqword InitTables() {
  uint i,j,k;

  memset(b39,0,256);
  //memset(b19,0,0x20100);
  //memset(ddd,0,4*31);
  sseTot=sseCum=d93=d110=d48=d49=d46=d47=d99=d100=d101=d102=d105=d104=predRescaleDiv=cumFreqAcc=d98=d103=d106=0;
  q32=q31=q30=q29=q34=q35=q21=q22=q18=q23=q20=q17=q36=q19=q24=q25=q9=q33=CtxChainEnd=0;
  d83=d84=d85=d92=d86=d87=d52=d50=d54=d53=d56=d55=MatchCtxHi=recentSym=d80=d91=SparseHashA=SparseIdxA=SparseHashB=SparseIdxB=SparseBit=0;
  memset( SseState3, 0, 0x20000 );
  //memset( b27, 0, 0x10000 );
  //memset( MatchPosHash, 0, 0x40000 );
  //memset( SseState2, 0, 0x80000 );
  memset( b28, 0, 0x10000 );

  byte freqtmp[] = {0,0,0,1,1,2,3,3,4,0,0,0};
  memset( freqmap, 0, sizeof(freqmap) );
  memcpy( freqmap, freqtmp, sizeof(freqtmp) );

  byte* indx2units = (byte*)&Indx2Units;
  for( i=0; i < 5; ++i ) indx2units[0 + i] = 1 + i;
  for( i=0; i < 3; ++i ) indx2units[5 + i] = 7 + 2*i;
  for( i=0; i < 3; ++i ) indx2units[8 + i] = 14 + 3 * i;
  for( i=0; i < 27; ++i) indx2units[11 + i] = 24 + 4 * i;

  for( i=0,j=0; i < 0x80; ++i ) {
    if( indx2units[j] < i+1 ) j++;
    Units2Indx4[i] = j;
  }

  // some quantization table
  // 0.220238 + 2.05508*i^0.444477
  // 2.0661 + 1.4084*Sqrt[0.4681+i] also fits, and is a better fit for algorithm below
  int v76=1, v78=1;
  SymType[0] = 1; SymType[1] = 2;
  for( i=2,j=2,k=2; i < 0x100; ++i ) {
    SymType[j] = k + 1;
    if( --v78==0 ) { ++k; v78 = ++v76; }
    j = i + 1;
  }
  SymType[0xFF] = 24;

  // this one is the actual SymType probably
  for( i = 0; i < 64; ++i)   ((byte*)SSE0)[i] = 0;
  for( i = 64; i < 256; ++i) ((byte*)SSE0)[i] = 0x80;

  // or this one
  byte* _SSE1 = (byte*)SSE1;
  _SSE1[0] = 0; _SSE1[1] = 2; _SSE1[2] = 2;
  for( i = 3; i <= 37; ++i) _SSE1[i] = 4;
  for( i = 38; i < 256; ++i) _SSE1[i] = 6;

  // SseSeed = ((OrderFall>2)<<15)+v114+*((uint*)BinMapTable+(v164&0xF))+(v29<<14);
  for( i = 0; i < 4; ++i ) {
    BinMapTable[i*4+0] = 0<<9;
    BinMapTable[i*4+1] = 0<<9;
    BinMapTable[i*4+2] = 0<<9;
  }
  BinMapTable[0*4+3] = 1<<9; //0x200;
  BinMapTable[1*4+3] = 2<<9; //0x400;
  BinMapTable[2*4+3] = 1<<9; //0x200;
  BinMapTable[3*4+3] = 3<<9; //0x600;

  for( i=0,j=0; i < 0x80; i++)  { NextBinFreq[i] = j+1; if( i==RLQBounds[j]) j++; }
  for( i=0,j=0; i < 0x100; i++) { SSE0QTable[i] = j+1;  if( i==SSE0QBounds[j] ) j++; }
  for( i=0,j=0; i < 0x80; i++)  { SSE1QTable[i] = j;    if( i==SSE1QBounds[j] ) j++; }
  for( i=0,j=0; i < 0x100; i++) { SEEQTable[i] = j;     if( i==SEEQBounds[j] ) j++; }

  return 1;
}
//--- #return
//--- #include "subs_binescfreq2.inc"

sqword BinEscFreq(byte* a1) {
  PPM_CONTEXT* pc = (PPM_CONTEXT*)a1;
  int nStates = pc->NStates;
  int numStates = nStates + 1;
  
  // Locate the state corresponding to the index in the lower 4 bits of pc->Flags
  STATE* baseStates = pc->getStates();
  int currIdx = pc->Flags & 0x0F;
  STATE* currState = &baseStates[currIdx];
  
  PPM_CONTEXT* suffix = pc->getSuffix();
  
  // Climb the suffix chain until finding a valid state frequency or matching symbol
  while (true) {
    STATE* suffixMaxState = suffix->getStates() + suffix->NStates;
    if (suffixMaxState->Freq != 0 || suffixMaxState->Symbol != currState->Symbol) {
      break;
    }
    suffix = suffix->getSuffix();
  }
  
  // Recursively process the suffix context if its current state frequency is zero
  STATE* suffixCurrState = suffix->getStates() + (suffix->Flags & 0x0F);
  if (suffixCurrState->Freq == 0) {
    BinEscFreq((byte*)suffix);
  }
  
  // Search for the state in the suffix context that matches the current symbol
  STATE* suffixStates = suffix->getStates();
  STATE* matchingSuffixState = nullptr;
  for (int idx = 0; ; ++idx) {
    if (suffixStates[idx].Symbol == currState->Symbol) {
      matchingSuffixState = &suffixStates[idx];
      break;
    }
  }
  
  uint suffixFreq = matchingSuffixState->Freq;
  uint summFreq = pc->SummFreq;
  uint totalFreqBound = summFreq - suffixFreq + 2 * suffix->NStates + 2 + suffix->SummFreq;
  
  // Rescale the suffix frequency multiplier
  uint freqMultiplier;
  if (suffixFreq >= 6) {
    freqMultiplier = suffixFreq - 1;
  } else if (suffixFreq >= 4) {
    freqMultiplier = 3;
  } else {
    freqMultiplier = 1;
  }
  
  // Calculate context state difference metrics clamped to safe bounds
  int stateOffsetBase = 4 * nStates + 4;
  int clampedDiff = suffix->NStates + 1 - 4 * nStates;
  if (clampedDiff < 0) {
    clampedDiff = 0;
  } else if (clampedDiff > 16 * numStates) {
    clampedDiff = 16 * numStates;
  }
  
  uint rescaleIndex = 3 * (clampedDiff + summFreq + stateOffsetBase) * freqMultiplier / totalFreqBound;
  
  // Determine the baseline new frequency via the frequency rescaling table
  byte newFreq;
  if (rescaleIndex >= 36) {
    newFreq = 11;
  } else {
    newFreq = FreqRescaleTab[rescaleIndex];
  }
  
  // Conditional adaptation based on model density thresholds
  if (rescaleIndex <= 33 || summFreq >= 32 * numStates) {
    currState->Freq = newFreq;
  } else {
    int frequencyBonus = (summFreq >= 6 * nStates + 6) ? 7 : 23;
    int scaleDelta = (int)rescaleIndex / 6 - 4;
    if (scaleDelta < frequencyBonus) {
      frequencyBonus = scaleDelta;
    }
    newFreq += frequencyBonus;
    currState->Freq = newFreq;
  }
  
  // Update the cumulative summary frequency of the context
  pc->SummFreq = currState->Freq + summFreq;
  
  // Bubble sort insertion step to maintain states sorted by frequency descending
  while (currIdx > 0) {
    STATE* curr = &baseStates[currIdx];
    STATE* prev = &baseStates[currIdx - 1];
    
    if (curr->Freq <= prev->Freq + 1) {
      break;
    }
    
    // Swap the records
    STATE temp = *curr;
    *curr = *prev;
    *prev = temp;
    
    currIdx--;
  }
  
  // Store the updated state index back into the context flags
  pc->Flags = currIdx | (pc->Flags & 0xF0);
  
  // Return equivalent to (byte_offset / 3) -> 2 * final_state_index
  return 2 * currIdx;
}
//--- #return
//--- #include "subs_rescalectx1.inc"
// =============================================================================
//  RescaleCtx() - cleaned up / refactored
// -----------------------------------------------------------------------------
//  PE binary's analog of PPM_CONTEXT::rescale(STATE* p) from ppmd.cpp.
//  Called from auxFindAndUpdate when a state's freq overflows MAX_FREQ.
//  Steps:
//     1. SWAP the just-incremented state up to states[0] (FoundState bubble).
//     2. Rescale every state's freq with the PE-specific formula; states whose
//        new freq is 0 are removed by shifting the higher slots down (so the
//        zero-freq slots end up at the top of the array).
//     3. If the topmost slot survived: commit Flags|=0x40 and return.
//        Otherwise count the trailing dropped slots and either:
//          a) survivors > 0  -> ShrinkUnits down to the new size
//          b) survivors == 0 -> collapse to oneState (free the whole block,
//             move the surviving state into ctx->oneState()).
//
//  The two big inlined sub-allocator blocks (the ShrinkUnits coalesce and the
//  FreeUnits coalesce) are replaced with the shared helpers from context.h.
//
//  PE-specific quirks preserved verbatim:
//     * Rescale formula has two modes selected by Flags bit 6: shift-1 with
//       multiplier 1 (textbook (Freq+a)/2) vs shift-2 with multiplier 3.
//     * Saturated freq bias depends on (OrderFall != MaxOrder), not OrderFall.
//     * Collapse-to-oneState recomputes Freq via (NStates+2*Freq)/(NStates+1)
//       clamped to 44, then folds that back into the Symbol|Freq word.
//     * SSE0[] replaces SymType[] (0 / 0x80 vs textbook 0 / 4).
// =============================================================================

sqword RescaleCtx(byte* a1) {
  PPM_CONTEXT* ctx        = (PPM_CONTEXT*)a1;
  int          NStates0   = ctx->NStates;             // original NStates (= last index)
  int          totalCount = NStates0 + 1;             // # states to iterate (incl. found)
  uint         oldIStates = ctx->iStates;
  STATE*       states     = ctx->getStates();

  // Rescale-mode parameters selected by Flags bit 6:
  //   bit clear -> shift=1, mult=1  (textbook (Freq+a)/2)
  //   bit set   -> shift=2, mult=3  ((Freq*3+a)/4 — slower decay)
  int  modeBit = (ctx->Flags & 0x40) >> 6;            // 0 or 1
  int  shift   = modeBit + 1;                          // 1 or 2
  int  multA   = 2 * modeBit + 2;                      // 2 or 4
  int  mask    = (1 << shift) - 1;                     // 1 or 3
  int  bias    = (OrderFall != MaxOrder) ? multA : -modeBit;

  // ---- step 1: SWAP the found state up to states[0] -----------------------
  {
    STATE* fp = (STATE*)q9;
    while (fp != states) {
      // SWAP(fp[0], fp[-1])
      word tw  = *(word*)fp;
      uint ts  = fp->iSuccessor;
      *(word*)fp     = *(word*)(fp - 1);
      fp->iSuccessor = (fp - 1)->iSuccessor;
      *(word*)(fp - 1)     = tw;
      (fp - 1)->iSuccessor = ts;
      fp--;
    }
  }

  // ---- step 2: top-down rescale + compact zero-freq slots to the top ------
  byte* endPtr     = (byte*)states + 6 * totalCount;  // one past last
  byte* lastSlot   = endPtr - 6;                       // last state ptr
  ctx->Flags    = 0;
  ctx->SummFreq = 0;
  int remaining = totalCount;
  do {
    endPtr -= 6;
    int newFreq = (bias + mask * endPtr[1]) >> shift;
    endPtr[1] = (byte)newFreq;
    ctx->SummFreq += (byte)newFreq;
    if (endPtr[1]) {
      ctx->Flags |= SSE0[*endPtr];
    } else {
      // shift states (k+1..N) down to (k..N-1); mark last as removed
      for (byte* p = endPtr; p < lastSlot; p += 6) {
        uint succ = *((uint*)p + 2);
        *(word*)p       = *((word*)p + 3);
        *(uint*)(p + 2) = succ;
      }
      lastSlot[1] = 0;
    }
    --remaining;
  } while (remaining);

  // ---- step 3a: top slot survived -> just record Flags|=0x40 and return ---
  if (lastSlot[1]) {
    sqword resultFast = lastSlot[1];
    ctx->Flags |= 0x40;
    q9 = (sqword)Indx2Ptr(ctx->iStates);
    return resultFast;
  }

  // ---- step 3b: count trailing zero-freq slots ----------------------------
  int dropped = 0;
  do {
    ++dropped;
    lastSlot -= 6;
  } while (!lastSlot[1]);

  int newNStates = (byte)(NStates0 - dropped);
  ctx->NStates = (byte)newNStates;

  if (newNStates) {
    // ---- step 3b-i: survivors > 0 -> ShrinkUnits -------------------------
    uint oldNU = (uint)((NStates0 + 2) >> 1);
    uint newNU = (uint)((newNStates + 2) >> 1);
    STATE* newStates = (STATE*)ShrinkUnits_(states, oldNU, newNU);
    ctx->iStates = Ptr2Indx(newStates);
    ctx->Flags  |= 0x40;
    q9 = (sqword)newStates;
    return (sqword)((((newNStates + 2) >> 1) - 1));   // matches PE's leaked intermediate
  }

  // ---- step 3b-ii: collapse to oneState -----------------------------------
  word firstSF   = *(word*)states;
  uint firstSucc = states[0].iSuccessor;
  uint newFreq2  = (NStates0 + ((firstSF >> 7) & 0xFFFFFFFE)) / (uint)(NStates0 + 1);
  if (newFreq2 >= 0x2Cu) newFreq2 = 44;
  HIBYTE(firstSF) = (byte)newFreq2;       // fold new freq back into the word

  FreeUnits_(states, (uint)((NStates0 + 2) >> 1));

  q9                          = (sqword)(a1 + 2);     // FoundState = &oneState
  ctx->oneState().Symbol      = (byte)firstSF;
  ctx->oneState().Freq        = (byte)(firstSF >> 8);
  ctx->oneState().iSuccessor  = firstSucc;
  ctx->Flags                  = SSE0[(byte)firstSF];
  return firstSF;
}
//--- #return
//--- #include "subs_ssescale1a.inc"
// =============================================================================
//  SseScale1() - cleaned up / refactored
// -----------------------------------------------------------------------------
//  PE-specific SSE counter rescaler. Operates on an 8-byte triplet:
//      uint  sum    (offset 0)
//      word  freq0  (offset 4)
//      word  freq1  (offset 6)
//
//  Given a (sum, freq0, freq1) counter and the current top-context's NStates /
//  SummFreq, this routine:
//      1. Forms a weight = freq1 * (sum / (11*freq0) + 1), clamped to 2048.
//      2. Computes a target sum bound from the PPM context (model expectation).
//      3. Half-rounds the sum and freq0 toward zero.
//      4. Branches on the weight:
//           weight > 1024   -> aggressively halve everything (factor-4 decay)
//           weight in (0x200..0x400] -> commit halved sum/freq0; freq1 = w - 128
//           weight in (0x40 ..0x200] -> commit halved sum/freq0; freq1 = w - 32
//           weight <= 0x40           -> freq1 = w - (1 if w > 32 else 0)
//
//  The freq1 = w - 32 / w - 128 / w - (~0) ladder behaves like a piecewise
//  decay where the subtraction step grows with the magnitude. The exact
//  thresholds are PE-specific and reproduced verbatim.
//
//  Helpers used:
//      * halfRoundUp_() :  x - (x >> 1) == (x + 1) / 2 for non-negative x
//        (used 4x in this function)
// =============================================================================

namespace {

inline uint halfRoundUp_(uint x) { return x - (x >> 1); }

struct SseCounter {     // matches the 8-byte (sum, freq0, freq1) layout
  uint sum;
  word freq0;
  word freq1;
};

} // namespace

sqword SseScale1(sqword a1) {
  SseCounter*  cnt    = (SseCounter*)a1;
  PPM_CONTEXT* topCtx = (PPM_CONTEXT*)MaxContext0;

  // ---- step 1: compose the weight (and clamp the low 16 bits to 2048) -----
  uint freq0Old = cnt->freq0;
  uint weight   = cnt->freq1 * (cnt->sum / (11 * freq0Old) + 1);
  if (weight >= 0x800) LOWORD(weight) = 2048;   // forces (word)weight > 0x400 below

  // ---- step 2: target sum bound from the top context's distribution -------
  uint nStatesP1   = topCtx->NStates + 1;
  uint perStateF0  = cnt->freq0 / nStatesP1;
  uint complement  = (256 - nStatesP1) * topCtx->SummFreq / nStatesP1;
  uint targetSum   = perStateF0 * complement;
  if (cnt->sum < targetSum) targetSum = cnt->sum;

  // ---- step 3: freq0 floor (16*nStatesP1) ---------------------------------
  uint freq0Bound = (freq0Old > 16 * nStatesP1) ? cnt->freq0 : 16 * nStatesP1;

  sqword halfSum   = halfRoundUp_(targetSum);
  uint   halfFreq0 = halfRoundUp_(freq0Bound);

  // ---- step 4: branch on weight magnitude ---------------------------------
  if ((word)weight > 0x400u) {
    // aggressive: halve everything (sum and freq0 halved twice, freq1 once)
    cnt->sum   = halfRoundUp_((uint)halfSum);
    cnt->freq0 = (word)halfRoundUp_(halfFreq0);
    cnt->freq1 = (word)weight >> 1;
    return (word)halfFreq0 >> 1;
  }

  // moderate: commit the half-rounded sum/freq0
  cnt->freq0 = (word)halfFreq0;
  cnt->sum   = (uint)halfSum;

  short newFreq1;
  if ((word)weight > 0x200u) {
    newFreq1 = (short)(weight - 128);
  } else if ((word)weight > 0x40u) {
    newFreq1 = (short)(weight - 32);
  } else {
    // (32 - weight) >> 31 == 1 if weight > 32 else 0  (unsigned wrap trick)
    uint dec = (32 - (uint)(word)weight) >> 31;
    newFreq1 = (short)(weight - dec);
  }
  cnt->freq1 = (word)newFreq1;
  return halfSum;
}
//--- #return
//--- #include "subs_ssescale2a.inc"
// =============================================================================
//  SseScale2() - cleaned up / refactored
// -----------------------------------------------------------------------------
//  PE-specific SSE counter rescaler operating on a 4-word (8-byte) layout:
//      word  hits        (offset 0)
//      word  predHi      (offset 2)   running Q15-scaled probability estimate
//      word  scale       (offset 4)
//      word  weight      (offset 6)   the adaptation gain
//
//  Algorithm:
//      1. Compute observed Q15 probability  q = round(hits * 32768 / scale),
//         clamped to [1, 0x7FFF].
//      2. Two variance-like quantities:
//             squareErr   = (predHi - q)^2
//             uncertainty = (0x10000 - (q + predHi)) * (q + predHi)
//      3. Form a "gain" from those plus the existing weight (bounded by 4096;
//         with a shift bump near the boundary).
//      4. Decay the weight (writes back at offset 6) via a piecewise ladder.
//      5. Update (hits, predHi, scale) based on the new weight: if the new
//         weight is small (<= 2) do an aggressive 2/3 decay; otherwise a
//         gentler half decay.
//
//  Return value is the intermediate "gain"; every caller discards it. It is
//  preserved verbatim only so the function signature stays the same.
//
//  PE-specific quirks preserved verbatim:
//      * The "(c - x) >> 31" unsigned-wrap trick used to encode "1 if x > c
//        else 0" without a branch.
//      * The magic 1431655766 multiplication for the /3 path; the result is
//        truncated to 32 bits (the decompiler appears to have dropped the
//        upper-half shift). Since callers discard it, reproduced as-is.
// =============================================================================

namespace {

struct SseSlot {       // 8-byte (hits, predHi, scale, weight) counter
  word hits;
  word predHi;
  word scale;
  word weight;
};

} // namespace

sqword SseScale2(sqword a1) {
  SseSlot* s = (SseSlot*)a1;

  // ---- step 1: observed Q15 probability, clamped to [1, 0x7FFF] -----------
  uint scale = s->scale;
  uint q = ((scale >> 1) + ((uint)s->hits << 15)) / scale;
  if (q >= 0x7FFF) q = 0x7FFF;
  if (q <= 1)      q = 1;

  // ---- step 2: variance-like quantities -----------------------------------
  uint predHi      = s->predHi;
  int  squareErr   = (int)(predHi - q) * (int)(predHi - q);
  uint uncertainty = (0x10000 - (q + predHi)) * (q + predHi);

  // ---- step 3: compose the gain -------------------------------------------
  uint weight   = s->weight;
  uint gainCap  = (weight < 4096) ? weight : 4096;
  uint partial  = (weight * (uncertainty >> 11)) >> 4;
  char gainShift = (gainCap <= 24 || gainCap == 4096) ? 14 : 1;

  sqword gain;
  if (2 * squareErr <= 3 * (int)partial) {
    gain = (sqword)gainCap *
           ((((int)partial >> gainShift) + 5 * squareErr) / (int)partial + 1);
    if ((uint)gain >= 0x2000) gain = 0x2000;
  } else {
    gain = 0x2000;
  }

  // ---- step 4: decay weight via piecewise ladder --------------------------
  short newWeight;
  if ((word)gain <= 0x40u && (word)gain <= (uint)s->weight) {
    if ((word)gain <= 0x20u) {
      // (c - x) >> 31 == 1 if x > c else 0  (unsigned-wrap trick)
      uint gt1  = ((uint)1  - (uint)(word)gain) >> 31;
      uint gt24 = ((uint)24 - (uint)(word)gain) >> 31;
      newWeight = (short)((uint)gain - gt1 - gt24);
    } else {
      newWeight = (short)((uint)gain - 8);
    }
  } else {
    newWeight = (short)((word)gain >> 1);
  }
  s->weight = (word)newWeight;

  // ---- step 5: update (hits, predHi, scale) -------------------------------
  uint hits  = s->hits;
  uint newPredHi;
  if ((word)newWeight <= 2u) {
    // aggressive: 2/3 decay path
    int  bumpHi = 17 * (8 * hits < scale);       // 17 if hits < scale/8
    int  bumpLo = (8 * (scale - hits) < scale);  // 1 if hits > 7/8 scale
    uint twoScale = 2 * scale;
    // PE-specific magic-multiply; result is discarded by callers.
    gain = (uint)(1431655766u * twoScale);
    newPredHi = (uint)(-6 * bumpLo + bumpHi + 2 * (int)hits) / 3u;
    s->scale  = (word)(twoScale / 3u);
  } else {
    // gentle: half decay with two small corrections
    s->scale = (word)(scale >> 1);
    int  bumpDown = -12 * (6 * (scale - hits) < scale);  // -12 if hits > 5/6 scale
    int  bumpUp   =  16 * (4 * hits < scale);            // +16 if hits < scale/4
    newPredHi = (uint)((int)hits + bumpDown + bumpUp) >> 1;
  }
  *(uint*)a1 = (q << 16) | (newPredHi & 0xFFFF);
  return gain;
}
//--- #return
//--- #include "subs_allocunitsrare.inc"
sqword AllocUnitsRare(uint a1) {
  sqword v1;
  sqword v2;
  uint v3;
  uint* v4;
  sqword v5;
  sqword result;
  int v7;
  sqword v8;
  sqword v9;
  uint v10;
  sqword v11;
  sqword v12;
  byte* i;
  sqword v14;
  uint v15;
  uint v16;
  int v17;
  sqword v18;
  int v19;
  uint v20;
  sqword v21;
  sqword v22;
  int v23;
  uint* v24;
  int v25;
  sqword v26;
  uint* v27;
  int v28;
  int v29;
  sqword v30;
  char* v31;
  sqword v32;
  int v33;
  sqword v34;
  uint v35;
  int v36;
  uint* v37;
  int v38;
  int v39;
  sqword v40;
  char* v41;
  sqword v42;
  uint v43;
  sqword v44;
  uint* v45;
  int v46;
  int v47;
  byte* v48;
  sqword v49;
  sqword v50;
  uint v51;
  uint v52;
  int v53;
  sqword v54;
  int v55;
  uint v56;
  sqword v57;
  sqword v58;
  int v59;
  uint* v60;
  byte* v61;
  uint* v62;
  int v63;
  int v64;
  int v65;
  sqword v66;
  uint* v67;
  sqword v68;
  bool v69;
  int v70;
  sqword v71;
  sqword v72;
  v1 = BList;
  v2 = a1;
  v3 = *((byte*)&Indx2Units+a1);
  while( ++a1!=38 ) {
    v4 = (uint*)(BList+12LL*a1);
    if( *v4 ) {
      v5 = HeapNull;
      result = HeapNull+(uint)v4[1];
      v4[1] = *(uint*)(result+4);
      *(uint*)(v5+*(uint*)(result+4)+8) = (uint)(uintptr_t)v4-v5;
      v7 = *((byte*)&Indx2Units+a1);
      --*v4;
      v8 = result+12LL*v3;
      v9 = v8-v5;
      v10 = v7-v3;
      v11 = v10;
      v12 = 12LL*v10;
      for( i = (byte*)(v8+v12); *(byte*)(v8+v12+1)==255; i = (byte*)(v8+v12) ) {
        *(uint*)(*((uint*)i+1)+v5+8) = *((uint*)i+2);
        *(uint*)(*((uint*)i+2)+v5+4) = *((uint*)i+1);
        v14 = 12LL**(Units2Indx+*i+3);
        --*(uint*)(v14+v1);
        v10 += *(byte*)(v8+v12);
        v11 = v10;
        v12 = 12LL*v10;
      }
      v15 = v10;
      if( v10>0x80 ) {
        v16 = 0;
        v17 = 0;
        v18 = -((sqword)(((qword)((1-v11)>>6)>>57)-v11+1)>>7);
        do {
          v10 = v17+v15-128;
          v17 -= 128;
          ++v16;
        } while( v16<(uint)v18 );
        v19 = *(uint*)(v1+448);
        v20 = 0;
        do {
          *(byte*)(v8+1) = -1;
          *(uint*)(v8+8) = v1-v5+444;
          *(uint*)(v8+4) = v19;
          v19 = v9;
          *(byte*)v8 = 0x80;
          v9 += 1536;
          v8 += 1536;
          *(uint*)(v5+*(uint*)(v1+448)+8) = v19;
          ++*(uint*)(v1+444);
          *(uint*)(v1+448) = v19;
          ++v20;
        } while( v20<(uint)v18 );
      }
      v21 = *(Units2Indx+v10+3);
      LODWORD(v22) = *((byte*)&Indx2Units+v21);
      if( v10!=(uint)v22 ) {
        v21 = (uint)(v21-1);
        v22 = *((byte*)&Indx2Units+v21);
        v23 = v10-v22;
        v24 = (uint*)(v1+12LL*(uint)(v23-1));
        v25 = v24[1];
        v26 = v8+12*v22;
        *(byte*)v26 = v23;
        *(byte*)(v26+1) = -1;
        *(uint*)(v26+8) = (uint)(uintptr_t)v24-v5;
        *(uint*)(v26+4) = v25;
        LODWORD(v26) = v26-v5;
        *(uint*)((uint)v24[1]+v5+8) = v26;
        v24[1] = v26;
        ++*v24;
      }
      *(byte*)(v8+1) = -1;
      v27 = (uint*)(12*v21+v1);
      v28 = v27[1];
      *(byte*)v8 = v22;
      *(uint*)(v8+8) = (uint)(uintptr_t)v27-v5;
      *(uint*)(v8+4) = v28;
      v29 = v8-v5;
      *(uint*)((uint)v27[1]+v5+8) = v29;
      v27[1] = v29;
      ++*v27;
      return result;
    }
  }
  if( CutOffCount ) {
    if( GlueCount )
      return 0;
    v30 = 12*v3;
    if( UnitsStart-v30<=(qword)pText ) {
      return 0;
    } else {
      result = UnitsStart-v30;
      UnitsStart -= v30;
    }
  } else {
    v31 = (char*)HeapStart+SubAllocatorSize-12;
    v32 = HeapNull;
    v70 = *((uint*)v31+2);
    v71 = *(qword*)v31;
    v33 = (uint)(uintptr_t)HeapStart+SubAllocatorSize-12-HeapNull;
    v72 = v2;
    v34 = 0;
    v35 = 0;
    v36 = BList-HeapNull+444;
    do {
      v31[1] = -2;
      v37 = (uint*)(v1+12*v34);
      v38 = v37[1];
      *v31 = 1;
      v39 = v1+12*v34-v32;
      *((uint*)v31+2) = v39;
      *((uint*)v31+1) = v38;
      *(uint*)((uint)v37[1]+v32+8) = v33;
      v40 = (uint)v37[2];
      ++*v37;
      v37[1] = v33;
      v41 = (char*)(v32+v40);
      v37[2] = *((uint*)v41+2);
      *(uint*)(*((uint*)v41+2)+v32+4) = v39;
      --*v37;
      for(; v41!=v31; --*v37 ) {
        v42 = *(Units2Indx+(uint)(byte)*v41+3);
        (void)(*(uint*)((uint)v37[2]+v32+8)+v32+4); // prefetch hint removed
        v43 = *((byte*)&Indx2Units+v42);
        v44 = *((byte*)&Indx2Units+v42);
        if( (byte)v41[12*v44+1]==255 ) {
          v48 = (byte*)&v41[-v32];
          v49 = 12*v44;
          do {
            *(uint*)(*(uint*)&v41[v49+4]+v32+8) = *(uint*)&v41[v49+8];
            *(uint*)(*(uint*)&v41[v49+8]+v32+4) = *(uint*)&v41[v49+4];
            v50 = 12LL**(Units2Indx+(byte)v41[v49]+3);
            --*(uint*)(v50+v1);
            v43 += (byte)v41[v49];
            v49 = 12LL*v43;
          } while( (byte)v41[v49+1]==255 );
          if( v43>0x80 ) {
            v51 = v43;
            v52 = 0;
            v53 = 0;
            v54 = -((sqword)(((qword)((1LL-v43)>>6)>>57)-v43+1)>>7);
            do {
              v43 = v53+v51-128;
              v53 -= 128;
              ++v52;
            } while( v52<(uint)v54 );
            v55 = *(uint*)(v1+448);
            v56 = 0;
            do {
              v41[1] = -1;
              *((uint*)v41+2) = v36;
              *((uint*)v41+1) = v55;
              v55 = (int)(uintptr_t)v48;
              *v41 = 0x80;
              v48 += 1536;
              v41 += 1536;
              *(uint*)(v32+*(uint*)(v1+448)+8) = v55;
              ++*(uint*)(v1+444);
              *(uint*)(v1+448) = v55;
              ++v56;
            } while( v56<(uint)v54 );
          }
          v57 = *(Units2Indx+v43+3);
          LODWORD(v58) = *((byte*)&Indx2Units+v57);
          if( v43!=(uint)v58 ) {
            v57 = (uint)(v57-1);
            v58 = *((byte*)&Indx2Units+v57);
            v59 = v43-v58;
            v60 = (uint*)(v1+12LL*(uint)(v59-1));
            v61 = (byte*)&v41[12*v58];
            v61[1] = -1;
            *v61 = v59;
            *((uint*)v61+2) = v1+12*(v59-1)-v32;
            *((uint*)v61+1) = v60[1];
            LODWORD(v61) = (uint)(uintptr_t)v61-v32;
            *(uint*)((uint)v60[1]+v32+8) = (uint)(uintptr_t)v61;
            v60[1] = (uint)(uintptr_t)v61;
            ++*v60;
          }
          v41[1] = -1;
          v62 = (uint*)(v1+12*v57);
          v63 = v62[1];
          *v41 = v58;
          *((uint*)v41+2) = (uint)(uintptr_t)v62-v32;
          *((uint*)v41+1) = v63;
          v64 = (uint)(uintptr_t)v41-v32;
          *(uint*)((uint)v62[1]+v32+8) = v64;
          v62[1] = v64;
          ++*v62;
        } else {
          v41[1] = -1;
          v45 = (uint*)(v1+12*v42);
          v46 = v45[1];
          *v41 = v43;
          *((uint*)v41+2) = (uint)(uintptr_t)v45-v32;
          *((uint*)v41+1) = v46;
          v47 = (uint)(uintptr_t)v41-v32;
          *(uint*)((uint)v45[1]+v32+8) = v47;
          v45[1] = v47;
          ++*v45;
        }
        v41 = (char*)(v32+(uint)v37[2]);
        v37[2] = *((uint*)v41+2);
        *(uint*)(*((uint*)v41+2)+v32+4) = v39;
      }
      v34 = ++v35;
    } while( v35<0x26 );
    *(qword*)v31 = v71;
    *((uint*)v31+2) = v70;
    v65 = *((byte*)&Indx2Units+v72);
    CutOffCount = 1;
    v66 = *(Units2Indx4+(uint)(v65-1));
    v67 = (uint*)(12*v66+v1);
    if( *v67 ) {
      result = v32+(uint)v67[1];
      v67[1] = *(uint*)(result+4);
      *(uint*)(*(uint*)(result+4)+v32+8) = (uint)(uintptr_t)v67-v32;
      --*v67;
    } else {
      result = LoUnit;
      v68 = 12*(uint)*((byte*)&Indx2Units+v66);
      v69 = LoUnit+v68==HiUnit;
      if( LoUnit+v68>(qword)HiUnit ) {
        return AllocUnitsRare((uint)v66);
      } else {
        LoUnit += v68;
        if( !v69 )
          *(uint*)(v68+result) = 0;
      }
    }
  }
  return result;
}
//--- #return
//--- #include "subs_freeunitsrare.inc"
char* FreeUnitsRare(sqword a1, uint a2) {
  sqword v2;
  sqword v3;
  sqword v4;
  sqword v5;
  sqword v6;
  byte* i;
  sqword v8;
  uint v9;
  uint v10;
  int v11;
  sqword v12;
  int v13;
  uint v14;
  sqword v15;
  sqword v16;
  int v17;
  uint* v18;
  sqword v19;
  uint* v20;
  int v21;
  int v23;
  v2 = BList;
  v3 = HeapNull;
  v4 = a1-HeapNull;
  v5 = a2;
  v6 = 12LL*a2;
  for( i = (byte*)(a1+v6); *(byte*)(a1+v6+1)==255; i = (byte*)(a1+v6) ) {
    *(uint*)(*((uint*)i+1)+v3+8) = *((uint*)i+2);
    *(uint*)(*((uint*)i+2)+v3+4) = *((uint*)i+1);
    v8 = 12LL**(Units2Indx+*i+3);
    --*(uint*)(v8+v2);
    a2 += *(byte*)(a1+v6);
    v5 = a2;
    v6 = 12LL*a2;
  }
  v9 = a2;
  if( a2>0x80 ) {
    v10 = 0;
    v11 = 0;
    v12 = -((sqword)(((qword)((1-v5)>>6)>>57)-v5+1)>>7);
    do {
      a2 = v11+v9-128;
      v11 -= 128;
      ++v10;
    } while( v10<(uint)v12 );
    v13 = *(uint*)(v2+448);
    v14 = 0;
    do {
      *(byte*)(a1+1) = -1;
      *(uint*)(a1+8) = v2-v3+444;
      *(uint*)(a1+4) = v13;
      v13 = v4;
      *(byte*)a1 = 0x80;
      v4 += 1536;
      a1 += 1536;
      *(uint*)(v3+*(uint*)(v2+448)+8) = v13;
      ++*(uint*)(v2+444);
      *(uint*)(v2+448) = v13;
      ++v14;
    } while( v14<(uint)v12 );
  }
  v15 = *(Units2Indx+a2+3);
  LODWORD(v16) = *((byte*)&Indx2Units+v15);
  if( a2!=(uint)v16 ) {
    v15 = (uint)(v15-1);
    v16 = *((byte*)&Indx2Units+v15);
    v17 = a2-v16;
    v18 = (uint*)(v2+12LL*(uint)(v17-1));
    v19 = a1+12*v16;
    *(byte*)(v19+1) = -1;
    *(byte*)v19 = v17;
    *(uint*)(v19+8) = v2+12*(v17-1)-v3;
    *(uint*)(v19+4) = v18[1];
    LODWORD(v19) = v19-v3;
    *(uint*)((uint)v18[1]+v3+8) = v19;
    v18[1] = v19;
    ++*v18;
  }
  *(byte*)(a1+1) = -1;
  v20 = (uint*)(12*v15+v2);
  v21 = v20[1];
  *(byte*)a1 = v16;
  *(uint*)(a1+8) = (uint)(uintptr_t)v20-v3;
  *(uint*)(a1+4) = v21;
  v23 = a1-v3;
  *(uint*)((uint)v20[1]+v3+8) = v23;
  v20[1] = v23;
  ++*v20;
  return (char*)v20-v3;
}
//--- #return
//--- #include "subs_startmodel1.inc"

sqword StartModelRare(int mode) {
  int suffixCount = 0;
  OrderFall = 0;
  OrderFall0 = 0;

  // Clear symbol masking structure to track processed states
  memset(SymMask, 0, sizeof(SymMask));

  SymCount = 1;
  sqword result = 0;

  // Mode 1 indicates an incremental update bypass unless a reset state condition matches
  if (mode != 1 || RunLength == -100) {
    uint* heapBlocks = (uint*)HeapStart;
    sqword allocatorSize = SubAllocatorSize;
    
    BList = (sqword)HeapStart;
    ++InitsCount;
    
    // Context tracking begins immediately past the 38 allocator free-list queues (38 * 12 = 456 bytes)
    pText = (sqword)HeapStart + 456;
    byte* heapEnd = (byte*)HeapStart + SubAllocatorSize;
    CutOffCount = 0;
    GlueCount = 0;
    
    // Dedicate a specific segment for unit state storage based on allocator metrics
    byte* unitsSegment = (byte*)HeapStart + SubAllocatorSize - 108 * (int)(SubAllocatorSize / 120);
    UnitsStart = (sqword)unitsSegment;
    LoUnit = (sqword)unitsSegment;
    *(uint*)unitsSegment = 0;
    
    byte* heapNullOffset = (byte*)heapBlocks - 1;
    HeapNull = (sqword)heapBlocks - 1;
    
    // Initialize all 38 allocation queues to point to themselves symmetrically
    for (uint i = 0; i < 0x26; ++i) {
      heapBlocks[3 * i + 2] = 12 * i + 1; // Next pointer index [cite: 83]
      heapBlocks[3 * i + 1] = 12 * i + 1; // Prev pointer index [cite: 84]
      heapBlocks[3 * i + 0] = 0;      // Queue size count [cite: 84]
    }

    sqword allocatedContextAddr;
    if (heapEnd == unitsSegment) {
      if (*heapBlocks == 0) {
        allocatedContextAddr = AllocUnitsRare(0);
      } else {
        allocatedContextAddr = (sqword)heapBlocks + (uint)heapBlocks[2] - 1;
        heapBlocks[2] = *(uint*)(allocatedContextAddr + 8);
        *(uint*)&heapNullOffset[*(uint*)(allocatedContextAddr + 8) + 4] = 1;
        --*heapBlocks;
      }
    } else {
      heapEnd = (byte*)heapBlocks + allocatorSize - 12;
      HiUnit = (sqword)heapEnd;
      allocatedContextAddr = (sqword)heapEnd;
    }

    // Establish structural properties for the Root Context block
    byte* rootCtx = (byte*)allocatedContextAddr;
    *(uint*)(rootCtx + 8) = 0; // Clear suffix references [cite: 90]
    RootContext = allocatedContextAddr;
    rootCtx[1] = (byte)-57; // Flags [cite: 91]
    MaxContext0 = allocatedContextAddr;
    *(word*)(rootCtx + 2) = 256; // SummFreq base [cite: 91]
    
    sqword preferredIndex = (byte)b11;
    NMasked = 255;
    rootCtx[0] = (byte)-1; // NStates initialized [cite: 92]
    uint* targetQueue = &heapBlocks[3 * preferredIndex];

    sqword stateStorageAddr;
    if (*targetQueue) {
      stateStorageAddr = (sqword)heapBlocks + (uint)targetQueue[1] - 1;
      byte* pStateStorage = (byte*)stateStorageAddr;
      targetQueue[1] = *(uint*)(pStateStorage + 4);
      *(uint*)&heapNullOffset[*(uint*)(pStateStorage + 4) + 8] = (uint)(uintptr_t)targetQueue - (uint)(uintptr_t)heapNullOffset;
      --*targetQueue;
    } else {
      stateStorageAddr = LoUnit;
      sqword sizeInBytes = 12 * (uint)*((byte*)&Indx2Units + preferredIndex);
      bool isAtBoundary = LoUnit + sizeInBytes == (qword)heapEnd;
      if (LoUnit + sizeInBytes > (qword)heapEnd) {
        stateStorageAddr = AllocUnitsRare(preferredIndex);
      } else {
        LoUnit += sizeInBytes;
        if (!isAtBoundary)
          *(uint*)(sizeInBytes + stateStorageAddr) = 0;
      }
    }

    q9 = stateStorageAddr;
    *(uint*)(rootCtx + 4) = stateStorageAddr - (uint)(uintptr_t)heapNullOffset; // Link states to context [cite: 99]
    MixCtx = 0;
    MixCtx2 = 0;
    MixCtx3 = 0;
    EscapeSymbol = 0;
    PrevSymbol = 0;
    
    // Initialize state fields across all 256 unique symbols
    byte* statePtr = (byte*)heapBlocks + *(uint*)(rootCtx + 4) - 1;
    for (int i = 0; i < 256; ++i) {
      statePtr[6 * i + 0] = i; // Symbol [cite: 102]
      statePtr[6 * i + 1] = 1; // Freq [cite: 103]
      statePtr[6 * i + 2] = 0; // Successor low bounds [cite: 103]
      statePtr[6 * i + 3] = 0;
      statePtr[6 * i + 4] = 0;
      statePtr[6 * i + 5] = 0;
    }
    result = 1536;

    // Mode 2 triggers contextual tables updates bypassing the secondary SSE table clears
    if (mode != 2 || RunLength == -100) {
      int runLengthVal;
      if (MaxOrder >= 11) {
        d16 = -11;
        runLengthVal = -11;
      } else {
        runLengthVal = -MaxOrder;
        d16 = -MaxOrder;
      }
      RunLength = runLengthVal;

      memset(Sse2State, 0, sizeof(Sse2State));

      MixScale = 1024;
      q12 = (sqword)Sse2State;
      FoundSymbol = -1;
      HashSeed1 = -1;
      HashSeed2 = -1;
      memset((int*)SseState2, 0x55u, 0x80000);
      memset((int*)SseState3, 0x55u, 0x20000);
      
      // Continuous initialization across secondary state arrays
      memset((byte*)SEE2_5 + 112, 0x55, 1008);
      SseCtx0[3] = 0x55555555;

      memset(MatchPosTable, 0x55u, 0x40000);

      for (int i = 0; i < 0x10000; ++i) {
        BijectMap[4 * i] = i;
        BijectMap[4 * i + 1] = i;
        BijectMap[4 * i + 2] = i;
      }

      SymEpoch = 1;
      memset(MixWeight1, 0, 0x20000);
      memset((int*)b16, 0, 0x20000);

      // Calculate predictor distributions for primary mix model spaces
      MixModel* mix1 = (MixModel*)MixWeight1;
      for (int v28 = 0; v28 < 0x4000; ++v28) {
        int bitSum = 0;
        if (v28 > 0) {
          int trackingBits = v28;
          int tableIdx = 0;
          while (trackingBits > 0) {
            bitSum += b17[tableIdx++] * (trackingBits & 1);
            trackingBits >>= 1;
          }
        }

        for (int v35 = 0; v35 < 14; ++v35) {
          int scaleFactor = (byte)b18[v35];
          int weightScalar = bitSum + scaleFactor;
          if (weightScalar >= 241) weightScalar = 241;
          if (weightScalar < 9) weightScalar = 9;
          
          int idx = (v35 + 1) * 0x4000 + v28;
          mix1[idx].freq0 = 18432;
          mix1[idx].freq1 = 5120;
          mix1[idx].weight = (weightScalar << 23) | (72 * weightScalar);
        }
        MixBound1[4 * v28] = 1024;
        MixFreq1_1[4 * v28] = 1024;
      }

      memset((int*)d27, 0, 0x20000);
      memset((int*)b19, 0, 0x20000);
      
      // Calculate distributions for secondary mix model spaces
      MixModel* mix2 = (MixModel*)&d27;
      for (int v38 = 0; v38 < 0x2000; ++v38) {
        int secondaryBitSum = 0;
        if (v38 > 0) {
          int secondaryTrackingBits = v38;
          int secondaryTableIdx = 0;
          while (secondaryTrackingBits > 0) {
            secondaryBitSum += b20[secondaryTableIdx++] * (secondaryTrackingBits & 1);
            secondaryTrackingBits >>= 1;
          }
        }

        for (int v45 = 0; v45 < 24; ++v45) {
          int scaleOffset = (byte)b21[v45];
          int weightValue = secondaryBitSum + scaleOffset;
          if (weightValue >= 241) weightValue = 241;
          if (weightValue < 9) weightValue = 9;
          
          int idx = 0x4000 + v45 * 0x2000 + v38;
          mix2[idx].freq0 = 18432;
          mix2[idx].freq1 = 5120;
          mix2[idx].weight = (weightValue << 23) | (72 * weightValue);
        }
        MixBound4[4 * v38] = 1024;
        MixBound5[4 * v38] = 1024;
        MixBound6[4 * v38] = 1024;
        MixBound3[4 * v38] = 1024;
      }

      MixModel* mix3 = (MixModel*)&MixWeight2;
      MixModel* mix4 = (MixModel*)&d29;
      for (int v48 = 0; v48 < 16; ++v48) {
        for (int v51 = 0; v51 < 1024; ++v51) {
          int idx = v48 * 0x400 + v51;
          mix3[idx].weight = 20480;
          mix3[idx].freq0 = 2048;
          mix3[idx].freq1 = 2048;
        }
        for (int v53 = 0; v53 < 256; ++v53) {
          int idx = v48 * 256 + v53;
          mix4[idx].weight = 20480;
          mix4[idx].freq0 = 2048;
          mix4[idx].freq1 = 2048;
        }
      }

      for (int v55 = 0; v55 < 5; ++v55) {
        int initialSseValue = 49 * (byte)b22[v55];
        for (int v58 = 0; v58 < 128; ++v58) {
          BinSse[v55 * 128 + v58] = initialSseValue;
        }
      }

      for (int v60 = 0; v60 < 5; ++v60) {
        int baseWeight = 48 * (byte)b23[v60];
        for (int v62 = 0; v62 < 256; ++v62) {
          PredWeight[v60 * 512 + v62 * 2] = baseWeight;
          PredWeight[v60 * 512 + v62 * 2 + 1] = 15104;
        }
      }

      OrderCtxSeed = 0;
      for (sqword i = 0; i < 196608; ++i) {
        Sse1[2 * i] = 0x2000;
        Sse1[2 * i + 1] = 24576;
      }
      for (sqword j = 0; j < 0x100000; ++j) {
        SseMatch[2 * j] = 0;
        SseMatch[2 * j + 1] = 0x40000;
      }
      SseSeed = 0;
      for (sqword k = 0; k < 98304; ++k) {
        Sse2[2 * k] = 0;
        Sse2[2 * k + 1] = 0x40000;
      }
      MixCtxExtra = 0;
      for (sqword result_idx = 0; result_idx < 86016; ++result_idx) {
        Sse3[2 * result_idx] = 0;
        Sse3[2 * result_idx + 1] = 0x80000;
      }
      result = 86016;
    }
  } else { // Traversal fallback configuration for persistent run instances [cite: 147]
    result = RootContext;
    uint suffixIndex = *(uint*)(RootContext + 8);
    if (suffixIndex) {
      result = HeapNull;
      do { // Loop to calculate suffix depth fallback heights [cite: 148]
        ++suffixCount;
        suffixIndex = *(uint*)(suffixIndex + HeapNull + 8);
      } while (suffixIndex);
      OrderFall = suffixCount;
    }
    OrderFall0 = suffixCount;
  }
  return result;
}
//--- #return
//--- #include "subs_createsuccessors.inc"
sqword CreateSuccessors(int depth, qword chainStart, sqword seedCtx) {
  sqword heapNull;
  uint seedSuccIdx;
  qword chainPtr;
  int curSuccIdx;
  uint ctxSuffixIdx;
  byte* foundStateB;
  uint suffixIdx0;
  sqword ctxAddr;
  int sym;
  byte* i;
  int stateSuccIdx;
  qword chainEnd;
  qword chainEndSaved;
  int newCtxAddr;
  byte* baseCtxAddr;
  qword chainPtrEnd;
  int bListIdx;
  uint* freelistHead;
  sqword hiUnit;
  sqword heapNullDup;
  uint* newCtxPtr;
  sqword result;
  int newCtxPacked;
  int newCtxBytePos;
  heapNull = HeapNull;
  seedSuccIdx = *(uint*)(*(qword*)chainStart+2LL);
  chainPtr = chainStart;
  while( 1 ) {
    curSuccIdx = *(uint*)(*(qword*)chainPtr+2LL);
    if( curSuccIdx!=seedSuccIdx ) {
      LODWORD(seedCtx) = HeapNull+curSuccIdx;
      goto LABEL_15;
    }
    ctxSuffixIdx = *(uint*)(seedCtx+8);
    chainPtr += 8LL;
    if( !ctxSuffixIdx )
      goto LABEL_15;
    if( chainPtr>=CtxChainEnd )
      break;
    seedCtx = HeapNull+ctxSuffixIdx;
  }
  foundStateB = (byte*)q9;
  suffixIdx0 = *(uint*)(seedCtx+8);
  while( 1 ) {
    ctxAddr = heapNull+suffixIdx0;
    if( *(byte*)ctxAddr ) {
      sym = *foundStateB;
      for( i = (byte*)(heapNull+*(uint*)(ctxAddr+4)); *i!=sym; i += 6 )
        ;
    } else {
      i = (byte*)(heapNull+suffixIdx0+2);
    }
    stateSuccIdx = *(uint*)(i+2);
    if( stateSuccIdx!=seedSuccIdx )
      break;
    suffixIdx0 = *(uint*)(ctxAddr+8);
    *(qword*)chainPtr = (qword)(uintptr_t)i;
    chainPtr += 8LL;
    if( !suffixIdx0 ) {
      LODWORD(seedCtx) = ctxAddr;
      goto LABEL_15;
    }
  }
  LODWORD(seedCtx) = heapNull+stateSuccIdx;
LABEL_15:
  chainEnd = chainStart+8LL*depth;
  if( chainPtr==chainEnd )
    return (uint)(seedCtx-heapNull);
  chainEndSaved = chainEnd;
  newCtxAddr = seedCtx;
  LOBYTE(newCtxPacked) = 0;
  baseCtxAddr = (byte*)(heapNull+seedSuccIdx);
  HIWORD(newCtxPacked) = *baseCtxAddr;
  newCtxBytePos = (uint)(uintptr_t)baseCtxAddr-heapNull+1;
  chainPtrEnd = chainPtr;
  BYTE1(newCtxPacked) = *((byte*)SSE0+*baseCtxAddr);
  bListIdx = BList-heapNull;
  freelistHead = (uint*)BList;
  hiUnit = HiUnit;
  heapNullDup = heapNull;
  while( 1 ) {
    if( hiUnit==LoUnit ) {
      if( *freelistHead ) {
        newCtxPtr = (uint*)(heapNullDup+(uint)freelistHead[2]);
        freelistHead[2] = newCtxPtr[2];
        *(uint*)((uint)newCtxPtr[2]+heapNullDup+4) = bListIdx;
        --*freelistHead;
      } else {
        newCtxPtr = (uint*)AllocUnitsRare(0);
      }
    } else {
      hiUnit -= 12;
      HiUnit = hiUnit;
      newCtxPtr = (uint*)hiUnit;
    }
    if( !newCtxPtr )
      break;
    *newCtxPtr = newCtxPacked;
    newCtxPtr[1] = newCtxBytePos;
    newCtxPtr[2] = newCtxAddr-heapNullDup;
    newCtxAddr = (int)(uintptr_t)newCtxPtr;
    result = (uint)((uint)(uintptr_t)newCtxPtr-heapNullDup);
    chainPtrEnd -= 8LL;
    *(uint*)(*(qword*)chainPtrEnd+2LL) = result;
    if( chainPtrEnd==chainEndSaved )
      return result;
  }
  return 0;
}
//--- #return
//--- #include "subs_updatemodel1.inc"
// =============================================================================
//  UpdateModel() - cleaned up / refactored
// -----------------------------------------------------------------------------
//  This is the PE binary's analog of ppmd.cpp PPM_CONTEXT::cutOff(UINT Order),
//  with AuxCutOff inlined. It recursively prunes contexts whose states have no
//  surviving successor, collapses single-child contexts, and rescales freqs
//  on the way up. Called from the restore_model path of ReduceOrder.
//
//  Behaviour is preserved from the decompiled blob; only presentation changed.
//  The inlined sub-allocator primitives (FreeUnits, FreeContext, MoveUnits,
//  ShrinkUnits, MoveContext, UnitsCpy) are factored out as small file-local
//  helpers so the UpdateModel body matches the textbook cutOff structure.
//
//  Differences from textbook ppmd.cpp::cutOff that are PE-specific and are
//  reproduced verbatim:
//      * leading "bump zero-freq state at rank (Flags & 0xF)" fix-up
//      * Scale threshold uses 16*i (textbook uses 19*i)
//      * rescale Flags mask is ((Scale<<6) & oldFlags) (textbook uses 0x0A|0x10*Scale)
//      * collapse uses (SummFreq - (f-1) + 19) (textbook uses + 11) and a
//        different ternary branch for newFreq
//      * SSE0[] replaces SymType[] (and produces 0 / 0x80 instead of 0 / 4)
// =============================================================================

// Sub-allocator helpers (UnitsCpy_, FreeUnits_, FreeContext_, MoveUnits_,
// ShrinkUnits_, MoveContext_) now live in context.h so other refactored
// subs_*.inc files can share them.

// =============================================================================
//  UpdateModel == PPM_CONTEXT::cutOff(Order)  +  AuxCutOff inlined
// =============================================================================
sqword UpdateModel(byte* ctxBytes, uint order) {
  PPM_CONTEXT* ctx   = (PPM_CONTEXT*)ctxBytes;
  uint         Order = order;

  // ---------------------------------------------------------------------------
  //  Single-state (NStates == 0) path
  // ---------------------------------------------------------------------------
  if (ctx->NStates == 0) {
    byte* succPtr = (byte*)Indx2Ptr(ctx->oneState().iSuccessor);
    if ((sqword)succPtr >= UnitsStart) {                 // hasSuccessor
      if (Order < (uint)MaxOrder) {
        uint res = (uint)UpdateModel(succPtr, Order + 1);
        ctx->oneState().iSuccessor = res;
        if (res) goto at_return;
      } else {
        ctx->oneState().iSuccessor = 0;
      }
      if (Order < PPM_CONTEXT::O_BOUND) goto at_return;
    }
    FreeContext_(ctx);
    return 0;
  }

  // ---------------------------------------------------------------------------
  //  Multi-state path: prune states with no successor, then possibly Shrink /
  //  Move / Collapse / Remove the context.
  // ---------------------------------------------------------------------------
  {
    int   NStates0   = ctx->NStates;
    byte  oldFlags   = ctx->Flags;
    STATE* states    = ctx->getStates();
    int   NU         = (NStates0 + 2) >> 1;

    // PE-specific: bump zero-freq state at rank (Flags & 0xF) before the scan.
    byte bumpIdx = oldFlags & 0xF;
    if (states[bumpIdx].Freq == 0) {
      states[bumpIdx].Freq = 8;
      ctx->SummFreq += 8;
    }

    // Pack states with a real successor to the front; drop the rest.
    int i = NStates0, k = NStates0;
    STATE* p  = states;
    STATE* p1 = states;
    do {
      byte* succPtr = (byte*)Indx2Ptr(p->iSuccessor);
      if ((sqword)succPtr < UnitsStart) {                // !hasSuccessor
        p->iSuccessor = 0;
        --i;
      } else {
        if (p != p1) {                                   // SWAP(*p1, *p)
          word tw = *(word*)p1;
          uint ts = p1->iSuccessor;
          *(word*)p1     = *(word*)p;
          p1->iSuccessor = p->iSuccessor;
          *(word*)p      = tw;
          p->iSuccessor  = ts;
        }
        p1++;
      }
      p++;
      --k;
    } while (k >= 0);

    STATE* p0;

    if (i == NStates0 || Order == 0) {
      // No state was dropped (or we're at root): just try to MoveUnits.
      p0 = (STATE*)MoveUnits_(states, NU);
      ctx->iStates = Ptr2Indx(p0);
    } else {
      ctx->NStates = (byte)i;
      if (i < 0) {
        FreeUnits_(states, NU);
        FreeContext_(ctx);
        return 0;
      }
      if (i == 0) {
        // Exactly one survivor -> collapse this context to its oneState.
        ctx->Flags = SSE0[states[0].Symbol];
        int f = states[0].Freq;
        int s = (int)ctx->SummFreq - (f - 1) + 19;
        int newFreq;
        if (s < 2*f - 2)
          newFreq = (byte)((f - 1) / s + 2);
        else
          newFreq = (int)(((uint)(s - (3*f - 3))) >> 31);
        states[0].Freq = (byte)(newFreq + 1);

        p0 = &ctx->oneState();
        *(word*)p0     = *(word*)states;                 // copy Symbol/Freq
        p0->iSuccessor = states[0].iSuccessor;
        FreeUnits_(states, NU);
      } else {
        // i > 0: shrink the states block and rescale freqs.
        int newNU = (i + 2) >> 1;
        states = (STATE*)ShrinkUnits_(states, NU, newNU);
        ctx->iStates = Ptr2Indx(states);

        int Scale = (ctx->SummFreq > 16 * (uint)i);
        ctx->Flags = (byte)((((byte)Scale << 6) & oldFlags) + SSE0[states[0].Symbol]);
        states[0].Freq = (byte)(((uint)states[0].Freq + Scale) >> Scale);
        ctx->SummFreq  = (byte)states[0].Freq;
        p = states;
        for (int j = i; j != 0; --j) {
          p++;
          ctx->Flags |= SSE0[p->Symbol];
          p->Freq = (byte)(((uint)p->Freq + Scale) >> Scale);
          ctx->SummFreq += (byte)p->Freq;
        }
        p0 = states;
        i  = ctx->NStates;
      }
    }

    // Recurse on each surviving state (i+1 of them), from p0+i down to p0.
    STATE* sLast = p0 + i;
    if (Order < (uint)MaxOrder) {
      do {
        byte* succPtr = (byte*)Indx2Ptr(sLast->iSuccessor);
        sLast->iSuccessor = (uint)UpdateModel(succPtr, Order + 1);
        sLast--;
      } while (--i >= 0);
    } else {
      do {
        sLast->iSuccessor = 0;
        sLast--;
      } while (--i >= 0);
    }
  }

  // ---------------------------------------------------------------------------
  //  AT_RETURN: relocate this context to a free 1-unit slot if we're at depth
  //  MaxOrder and the trailing block can be merged (== ppmd's MoveContext).
  // ---------------------------------------------------------------------------
at_return:
  if (Order == (uint)MaxOrder)
    ctx = (PPM_CONTEXT*)MoveContext_(ctx);
  return (sqword)(uint)Ptr2Indx(ctx);
}
//--- #return
//--- #include "subs_reduceorder.inc"

STATE*& FoundState = (STATE*&)q9;

sqword ReduceOrder() {
  sqword v0;
  byte* foundStateB;
  int orderFall;
  int maxOrder;
  uint v4;
  byte* v5;
  char sse0Bit;
  uint succCreatedTop;
  sqword result;
  sqword v9;
  sqword heapNull;
  qword unitsStart;
  sqword v12;
  uint v13;
  sqword maxCtxStart;
  sqword succIdx;
  sqword succAddr;
  sqword ctxSuffixIdx;
  int escIdx;
  char sse0BitSaved;
  uint v20;
  uint nStatesP1;
  sqword v22;
  uint* v23;
  uint v24;
  uint v25;
  sqword v26;
  sqword v27;
  uint* v28;
  uint* v29;
  qword v30;
  bool v31;
  uint* v32;
  sqword v33;
  uint v34;
  uint v35;
  uint v36;
  sqword v37;
  uint* v38;
  sqword v39;
  sqword v40;
  uint v41;
  uint v42;
  int v43;
  uint v44;
  sqword v45;
  sqword v46;
  int v47;
  uint* v48;
  uint* v49;
  uint* v50;
  int v51;
  uint v52;
  sqword v53;
  qword v54;
  int v55;
  uint* v56;
  sqword v57;
  sqword v58;
  bool v59;
  int v60;
  int v61;
  char v62;
  sqword v63;
  sqword v64;
  qword v65;
  int sym;
  sqword v67;
  sqword* v68;
  byte* v69;
  uint v70;
  sqword v71;
  uint v72;
  sqword v73;
  sqword v74;
  uint* v75;
  int v76;
  sqword v77;
  sqword v78;
  sqword v79;
  qword v80;
  uint v81;
  sqword v82;
  sqword v83;
  uint v84;
  uint v85;
  int v86;
  sqword v87;
  uint v88;
  sqword v89;
  sqword v90;
  int v91;
  uint* v92;
  sqword v93;
  uint* v94;
  int v95;
  sqword v96;
  int symPeek;
  int v98;
  uint v99;
  sqword v100;
  uint v101;
  byte* v102;
  byte v103;
  sqword* v104;
  char v105;
  char v106;
  uint v107;
  uint v108;
  uint v109;
  uint v110;
  byte* v111;
  byte* v112;
  byte* v113;
  sqword v114;
  sqword v115;
  sqword v116;
  int bListCountIdx;
  sqword escIdxClipped;
  qword hiUnitSaved;
  sqword bListSaved;
  sqword succAddrSaved;
  sqword rootCtxSaved;
  short foundSymFreq;
  v0 = RootContext;
  foundStateB = (byte*)q9;
  orderFall = OrderFall;
  maxOrder = MaxOrder;
  v4 = *(uint*)(q9+2);
  foundSymFreq = *(word*)q9;
  v5 = (byte*)RootContext;
  rootCtxSaved = RootContext;
  sse0Bit = *((byte*)SSE0+(byte)*(word*)q9);
  if( OrderFall==MaxOrder&&v4 ) {
    succCreatedTop = CreateSuccessors(1, (qword)CtxChain, MaxContext0);
    *(uint*)(foundStateB+2) = succCreatedTop;
    if( succCreatedTop ) {
      result = HeapNull+succCreatedTop;
      RootContext = result;
      MaxContext0 = result;
      return result;
    }
    goto LABEL_73;
  }
  v9 = pText;
  heapNull = HeapNull;
  *(byte*)pText = *(word*)q9;
  unitsStart = UnitsStart;
  v12 = v9+1;
  pText = v9+1;
  v13 = v9+1-heapNull;
  if( v9+1>=(qword)UnitsStart )
    goto LABEL_73;
  *(byte*)(v9+1) = 0;
  if( !v4 ) {
    maxCtxStart = MaxContext0;
    v65 = CtxChainEnd;
    sym = *foundStateB;
    v112 = v5;
    v67 = MaxContext0;
    v115 = v0;
    v68 = CtxChain;
    while( 1 ) {
      if( (qword)v68>=v65 ) {
        if( *(byte*)v67 ) {
          v69 = (byte*)(heapNull+*(uint*)(v67+4));
          if( *v69!=sym ) {
            do {
              symPeek = v69[6];
              v69 += 6;
            } while( sym!=symPeek );
          }
        } else {
          v69 = (byte*)(v67+2);
        }
        *v68++ = (sqword)v69;
      } else {
        v69 = (byte*)*v68++;
      }
      v4 = *(uint*)(v69+2);
      if( v4 )
        break;
      *(uint*)(v69+2) = v13;
      v70 = *(uint*)(v67+8);
      OrderFall = --orderFall;
      if( !v70 ) {
        v5 = v112;
        v0 = v115;
        v4 = v67-heapNull;
        goto LABEL_9;
      }
      v67 = heapNull+v70;
    }
    v102 = v69;
    v5 = v112;
    v104 = v68;
    v0 = v115;
    if( v4<=v13 ) {
      v100 = v9;
      v110 = v9+1-heapNull;
      v106 = sse0Bit;
      v4 = CreateSuccessors(0, (qword)(v104-1), v67);
      sse0Bit = v106;
      v13 = v110;
      v9 = v100;
      *(uint*)(v102+2) = v4;
    }
    if( orderFall==maxOrder-1&&maxCtxStart==v115 ) {
      *(uint*)(foundStateB+2) = v4;
      v4 = *(uint*)(v102+2);
      v12 = v9;
      pText = v9;
    }
LABEL_9:
    if( v4 ) {
      succIdx = v4;
      goto LABEL_11;
    }
LABEL_73:
    if( !CutOff )
      return StartModelRare(2);
    if( *(byte*)v0==1 ) {
      v71 = BList;
      if( !*v5&&(byte*)v0!=v5 ) {
        v73 = HeapNull;
        v74 = Units2Indx4[0];
        v116 = v0;
        v75 = (uint*)(BList+12LL*Units2Indx4[0]);
        v76 = BList+12*Units2Indx4[0]-HeapNull;
        v98 = BList-HeapNull+444;
        v77 = rootCtxSaved;
        do {
          v78 = *(uint*)(v77+4);
          v79 = v73+v78;
          v80 = *(byte*)(v73+v78)!=v5[2];
          *(byte*)(v77+1) = *((byte*)SSE0+*(byte*)(v73+v78+6*v80));
          *(byte*)(v73+v78+6*v80+1) = ((uint)*(byte*)(v73+v78+6*v80+1)+3)>>2;
          *(word*)(v77+2) = *(word*)(v73+v78+6*v80);
          *(uint*)(v77+4) = *(uint*)(v73+v78+6*v80+2);
          v81 = *((byte*)&Indx2Units+v74);
          *(byte*)v77 = 0;
          if( *(byte*)(12LL*v81+v73+v78+1)==255 ) {
            v82 = 12LL*v81;
            do {
              *(uint*)(*(uint*)(v82+v79+4)+v73+8) = *(uint*)(v82+v79+8);
              *(uint*)(*(uint*)(v82+v79+8)+v73+4) = *(uint*)(v82+v79+4);
              v83 = 12LL**(Units2Indx+*(byte*)(v82+v79)+3);
              --*(uint*)(v83+v71);
              v81 += *(byte*)(v79+v82);
              v82 = 12LL*v81;
            } while( *(byte*)(v82+v79+1)==255 );
            if( v81>0x80 ) {
              v113 = v5;
              v84 = v81;
              v85 = 0;
              v86 = 0;
              v87 = -((sqword)(((qword)((1LL-v81)>>6)>>57)-v81+1)>>7);
              do {
                v81 = v86+v84-128;
                v86 -= 128;
                ++v85;
              } while( v85<(uint)v87 );
              v88 = 0;
              do {
                *(byte*)(v79+1) = -1;
                *(uint*)(v79+8) = v98;
                ++v88;
                *(byte*)v79 = 0x80;
                *(uint*)(v79+4) = *(uint*)(v71+448);
                *(uint*)(v73+*(uint*)(v71+448)+8) = v78;
                ++*(uint*)(v71+444);
                *(uint*)(v71+448) = v78;
                v78 += 1536;
                v79 += 1536;
              } while( v88<(uint)v87 );
              v5 = v113;
            }
            v89 = *(Units2Indx+v81+3);
            LODWORD(v90) = *((byte*)&Indx2Units+v89);
            if( v81!=(uint)v90 ) {
              v89 = (uint)(v89-1);
              v90 = *((byte*)&Indx2Units+v89);
              v91 = v81-v90;
              v92 = (uint*)(v71+12LL*(uint)(v91-1));
              v93 = v79+12*v90;
              *(byte*)(v93+1) = -1;
              *(byte*)v93 = v91;
              *(uint*)(v93+8) = v71+12*(v91-1)-v73;
              *(uint*)(v93+4) = v92[1];
              LODWORD(v93) = v93-v73;
              *(uint*)((uint)v92[1]+v73+8) = v93;
              v92[1] = v93;
              ++*v92;
            }
            *(byte*)(v79+1) = -1;
            v94 = (uint*)(v71+12*v89);
            *(byte*)v79 = v90;
            *(uint*)(v79+8) = (uint)(uintptr_t)v94-v73;
            *(uint*)(v79+4) = v94[1];
            v95 = v79-v73;
            *(uint*)((uint)v94[1]+v73+8) = v95;
            v94[1] = v95;
            ++*v94;
          } else {
            *(byte*)(v79+1) = -1;
            *(byte*)v79 = v81;
            *(uint*)(v79+8) = v76;
            *(uint*)(v79+4) = v75[1];
            *(uint*)((uint)v75[1]+v73+8) = v78;
            v75[1] = v78;
            ++*v75;
          }
          v77 = v73+*(uint*)(v77+8);
        } while( (byte*)v77!=v5 );
        v0 = v116;
      }
    } else {
      v71 = BList;
    }
    v72 = *(uint*)(v0+8);
    if( v72 ) {
      do {
        v0 = HeapNull+v72;
        v72 = *(uint*)(v0+8);
      } while( v72 );
      RootContext = v0;
    }
    result = UpdateModel((byte*)v0, 0);
    ++GlueCount;
    CutOffCount = 0;
    pText = v71+456;
    MaxContext0 = v0;
    OrderFall = 0;
    return result;
  }
  maxCtxStart = MaxContext0;
  succIdx = v4;
  if( unitsStart>heapNull+(qword)v4 ) {
    v107 = v9+1-heapNull;
    v105 = sse0Bit;
    v4 = CreateSuccessors(0, (qword)CtxChain, MaxContext0);
    sse0Bit = v105;
    v13 = v107;
    goto LABEL_9;
  }
LABEL_11:
  succAddr = heapNull+succIdx;
  ctxSuffixIdx = *(uint*)(heapNull+succIdx+8);
  OrderFall = orderFall+1;
  (void)(ctxSuffixIdx+heapNull); // prefetch hint removed
  if( OrderFall==maxOrder ) {
    v13 = v4;
    pText = v12-(v0!=maxCtxStart);
  }
  result = *(uint*)(succIdx+heapNull+4);
  (void)(result+heapNull); // prefetch hint removed
  if( v0!=maxCtxStart ) {
    hiUnitSaved = HiUnit;
    escIdx = EscIndexSeed+8;
    bListSaved = BList;
    succAddrSaved = heapNull+succIdx;
    v114 = v0;
    if( EscIndexSeed+8>=14 )
      escIdx = 14;
    if( escIdx<0 )
      escIdx = 0;
    sse0BitSaved = sse0Bit;
    bListCountIdx = BList-heapNull+444;
    escIdxClipped = escIdx;
    v20 = v13;
    while( 1 ) {
      nStatesP1 = *v5+1;
      if( *v5 ) {
        if( (nStatesP1&1)!=0 ) {
          v53 = *((uint*)v5+1);
        } else {
          v22 = *((uint*)v5+1);
          v23 = (uint*)(heapNull+v22);
          v24 = nStatesP1>>1;
          v25 = *(Units2Indx+(nStatesP1>>1)+3);
          v26 = nStatesP1>>1;
          if( v25!=*(Units2Indx4+v26) ) {
            v27 = *(Units2Indx4+v26);
            v28 = (uint*)(bListSaved+12*v27);
            if( *v28 ) {
              v29 = (uint*)(heapNull+(uint)v28[1]);
              v28[1] = v29[1];
              *(uint*)((uint)v29[1]+heapNull+8) = (uint)(uintptr_t)v28-heapNull;
              --*v28;
            } else {
              v29 = (uint*)LoUnit;
              v30 = 12*(uint)*((byte*)&Indx2Units+v27);
              v31 = LoUnit+v30==hiUnitSaved;
              if( LoUnit+v30>hiUnitSaved ) {
                v99 = *(Units2Indx+v24+3);
                v108 = v20;
                v29 = (uint*)AllocUnitsRare(v27);
                v20 = v108;
                v25 = v99;
              } else {
                LoUnit += v30;
                if( !v31 )
                  v29[v30/4] = 0;
              }
            }
            if( v29 ) {
              v32 = v29;
              v33 = heapNull+v22;
              if( (nStatesP1&2)!=0 ) {
                *v29 = *v23;
                v29[1] = v23[1];
                v29[2] = v23[2];
                v32 = v29+3;
                v33 = heapNull+v22+12;
              }
              if( (v24&0xFFFFFFFE)!=0 ) {
                v111 = v5;
                v34 = 0;
                v35 = 0;
                do {
                  v32[v35] = *(uint*)(v33+v35*4);
                  ++v34;
                  v32[v35+1] = *(uint*)(v33+v35*4+4);
                  v32[v35+2] = *(uint*)(v33+v35*4+8);
                  v32[v35+3] = *(uint*)(v33+v35*4+12);
                  v32[v35+4] = *(uint*)(v33+v35*4+16);
                  v32[v35+5] = *(uint*)(v33+v35*4+20);
                  v35 += 6;
                } while( v34<nStatesP1>>2 );
                v5 = v111;
              }
              v36 = *((byte*)&Indx2Units+v25);
              v37 = *((byte*)&Indx2Units+v25);
              if( BYTE1(v23[3*v37])==255 ) {
                v39 = 3*v37;
                do {
                  *(uint*)((uint)v23[v39+1]+heapNull+8) = v23[v39+2];
                  *(uint*)((uint)v23[v39+2]+heapNull+4) = v23[v39+1];
                  v40 = 12LL**(Units2Indx+LOBYTE(v23[v39])+3);
                  --*(uint*)(v40+bListSaved);
                  v36 += LOBYTE(v23[v39]);
                  v39 = 3LL*v36;
                } while( BYTE1(v23[v39])==255 );
                v41 = v36;
                if( v36>0x80 ) {
                  v42 = 0;
                  v101 = -(int)((sqword)(((qword)((1LL-v36)>>6)>>57)-v36+1)>>7);
                  v43 = 0;
                  do {
                    v36 = v43+v41-128;
                    v43 -= 128;
                    ++v42;
                  } while( v42<v101 );
                  v44 = 0;
                  do {
                    *((byte*)v23+1) = -1;
                    v23[2] = bListCountIdx;
                    ++v44;
                    *(byte*)v23 = 0x80;
                    v23[1] = *(uint*)(bListSaved+448);
                    *(uint*)(*(uint*)(bListSaved+448)+heapNull+8) = v22;
                    ++*(uint*)(bListSaved+444);
                    *(uint*)(bListSaved+448) = v22;
                    v22 += 1536;
                    v23 += 384;
                  } while( v44<v101 );
                }
                v45 = *(Units2Indx+v36+3);
                v103 = *((byte*)&Indx2Units+v45);
                if( v36!=v103 ) {
                  v45 = (uint)(v45-1);
                  v46 = *((byte*)&Indx2Units+v45);
                  v103 = *((byte*)&Indx2Units+v45);
                  v47 = v36-v46;
                  v48 = (uint*)(bListSaved+12LL*(uint)(v47-1));
                  v49 = &v23[3*v46];
                  *((byte*)v49+1) = -1;
                  *(byte*)v49 = v47;
                  v49[2] = (uint)(uintptr_t)v48-heapNull;
                  v49[1] = v48[1];
                  LODWORD(v49) = (uint)(uintptr_t)v49-heapNull;
                  *(uint*)((uint)v48[1]+heapNull+8) = (uint)(uintptr_t)v49;
                  ++*v48;
                  v48[1] = (uint)(uintptr_t)v49;
                }
                *((byte*)v23+1) = -1;
                v50 = (uint*)(bListSaved+12*v45);
                *(byte*)v23 = v103;
                v23[2] = (uint)(uintptr_t)v50-heapNull;
                v23[1] = v50[1];
                v51 = (uint)(uintptr_t)v23-heapNull;
                *(uint*)((uint)v50[1]+heapNull+8) = v51;
                ++*v50;
                v50[1] = v51;
              } else {
                *((byte*)v23+1) = -1;
                v38 = (uint*)(bListSaved+12LL*v25);
                *(byte*)v23 = v36;
                v23[2] = (uint)(uintptr_t)v38-heapNull;
                v23[1] = v38[1];
                *(uint*)((uint)v38[1]+heapNull+8) = v22;
                ++*v38;
                v38[1] = v22;
              }
            }
            v23 = v29;
          }
          if( !v23 )
            goto LABEL_99;
          v52 = (uint)(uintptr_t)v23-heapNull;
          v53 = v52;
          *((uint*)v5+1) = v52;
        }
        v54 = v53+heapNull+6LL*nStatesP1;
        if( v54>heapNull+v53+42 ) {
          do {
            v55 = *(uint*)(v54-4);
            *(word*)v54 = *(word*)(v54-6);
            *(uint*)(v54+2) = v55;
            v54 -= 6LL;
          } while( v54>heapNull+(qword)*((uint*)v5+1)+42 );
        }
      } else {
        v56 = (uint*)(bListSaved+12LL*Units2Indx4[0]);
        if( *v56 ) {
          v57 = heapNull+(uint)v56[1];
          v56[1] = *(uint*)(v57+4);
          *(uint*)(*(uint*)(v57+4)+heapNull+8) = (uint)(uintptr_t)v56-heapNull;
          --*v56;
        } else {
          v57 = LoUnit;
          v58 = 12*(uint)*((byte*)&Indx2Units+Units2Indx4[0]);
          v59 = LoUnit+v58==hiUnitSaved;
          if( LoUnit+v58>hiUnitSaved ) {
            v109 = v20;
            v96 = AllocUnitsRare(Units2Indx4[0]);
            v20 = v109;
            v57 = v96;
          } else {
            LoUnit += v58;
            if( !v59 )
              *(uint*)(v58+v57) = 0;
          }
        }
        if( !v57 ) {
LABEL_99:
          v0 = v114;
          goto LABEL_73;
        }
        *(word*)v57 = *((word*)v5+1);
        v60 = b24[escIdxClipped];
        *(uint*)(v57+2) = *((uint*)v5+1);
        *((uint*)v5+1) = v57-heapNull;
        v61 = 4**(byte*)(v57+1)+v60;
        if( v61>=238 )
          v61 = 238;
        if( v61<2 )
          LOBYTE(v61) = 2;
        *(byte*)(v57+1) = v61;
        v54 = v57+6;
        *((word*)v5+1) = (byte)v61;
      }
      *(byte*)(v54+1) = 0;
      *(uint*)(v54+2) = v20;
      *(byte*)v54 = foundSymFreq;
      v62 = v5[1]&0xF0;
      v63 = heapNull+*((uint*)v5+1);
      ++*v5;
      v64 = v54-v63;
      result = 0x2AAAAAAAAAAAAAABLL*v64;
      v5[1] = sse0BitSaved|(v64/6)|v62;
      v5 = (byte*)(heapNull+*((uint*)v5+2));
      if( v5==(byte*)maxCtxStart ) {
        succAddr = succAddrSaved;
        break;
      }
    }
  }
  MaxContext0 = succAddr;
  RootContext = succAddr;
  return result;
}
//--- #return
//--- #include "subs_mixupdate1.inc"
// =============================================================================
//  MixUpdate() - cleaned up / refactored
// -----------------------------------------------------------------------------
//  PE binary's per-symbol update routine. After encoding/decoding a symbol it
//  commits every predictor's side-effect update and then walks the context-
//  suffix chain to set up CtxChain[] for the next prediction (the tail call
//  to ReduceOrder() happens at the very end).
//
//  Behaviour preserved 1:1 from the decompiled blob. Cleanup performed:
//
//    * obviously shared idioms factored into file-local helpers:
//
//        UpdateWeightPair_   pred-pair update with overflow halving       x2
//        MatchPosHint_       MatchPosPrev hash-chain hint (0x20000 win)   x4
//        MatchPosHint16_     same with 0x10000 outer window               x2
//        BijectPairUpdate_   paired byte-hash predictor (b32/b33 etc.)    x3
//        FindAndBubble7_     symbol search + rank-7 bubble-up             x2
//        HashArmUpdate_      8-arm byte-pair hash arm (SseState2/b28..30) x4
//
//    * v1..v175 temporaries replaced with meaningful names whose comments
//      describe what each value represents (see the declaration block).
//    * function body sectioned by comment headers along the natural phases
//      (weight updates, sym-derived state, MatchPosTable, RSContext / SSE2
//      histogram, MixScale tracking, hint chains, BijectMap predictor, and
//      finally the context-suffix walk that builds CtxChain[]).
//    * irreducible goto layout (LABEL_94 / LABEL_165 / LABEL_201) is left
//      intact since rewriting it carries a high risk of behaviour drift.
// =============================================================================

// helper 1: pred-pair update with overflow-driven halving
//   p0 -= delta;  p1 += delta - decay;  if p1 overflows, halve both.
//   The two call sites use different decay magnitudes (2*scale and scale).
inline void UpdateWeightPair_(int* w, int delta, int decay) {
  int p0 = w[0] - delta;
  int p1 = w[1] + delta - decay;
  if (p1 > 0x40000000) { p0 >>= 1; p1 >>= 1; }
  w[0] = p0;
  w[1] = p1;
}

// helper 2: MatchPosPrev hash-chain hint (outer 0x20000 threshold)
inline int MatchPosHint_(int hist_off, int symEpoch, int symEpochN, int sc) {
  int prev1 = MatchPosPrev[(symEpoch - hist_off) & 0x1FFFF];
  if ((uint)(symEpochN - prev1) >= 0x20000) return -1;
  byte h1 = MatchPosHash[(prev1 + hist_off + 1) & 0x1FFFF];
  SymLastCtx[h1] = sc;
  int prev2 = MatchPosPrev[prev1 & 0x1FFFF];
  if ((uint)(symEpochN - prev2) < 0x20000) {
    byte h2 = MatchPosHash[(prev2 + hist_off + 1) & 0x1FFFF];
    SymLastCtx[h2] = sc;
    if ((uint)h1 == (uint)h2) {
      if (HashSeed2 < 0)            HashSeed2 = h1;
      else if (HashSeed2 == (uint)h1) HashSeed1 = h1;
      MatchPosBySym[h1] = sc;
    }
  }
  return h1;
}

// helper 2b: shorter-window (0x10000) variant with compact second arm
inline void MatchPosHint16_(int hist_off, int symEpoch, int symEpochN, int sc) {
  int prev1 = MatchPosPrev[(symEpoch - hist_off) & 0x1FFFF];
  if ((uint)(symEpochN - prev1) >= 0x10000) return;
  byte h1 = MatchPosHash[(prev1 + hist_off + 1) & 0x1FFFF];
  SymLastCtx[h1] = sc;
  int prev2 = MatchPosPrev[prev1 & 0x1FFFF];
  if ((uint)(symEpochN - prev2) < 0x20000) {
    byte h2 = MatchPosHash[(prev2 + hist_off + 1) & 0x1FFFF];
    // if (h2==h1) record into MatchPosBySym (= &SymLastCtx[512]); else SymLastCtx
    SymLastCtx[512 * (h2 == h1) + h2] = sc;
  }
}

// helper 3: paired byte-hash predictor update
inline void BijectPairUpdate_(byte* arrA, byte* arrB, uint readIdx, uint writeIdx,
                              byte sym, int sc) {
  byte a = arrA[readIdx];
  byte b = arrB[readIdx];
  SymLastCtx2[a] = sc;
  SymLastCtx2[b] = sc;
  if ((uint)b == (uint)a) {
    if (b == HashSeed2) HashSeed1 = b;
    MatchPosBySym[b] = sc;
  }
  arrA[writeIdx] = arrB[writeIdx];
  arrB[writeIdx] = sym;
}

// helper 5: 8-arm-style byte-hash predictor (used 4x with SseState2/b28/b29/b30)
//   Read arr[readKey]; if it just got hit by us, also mark SymLastCtx2 at the
//   same byte; otherwise mark SymLastCtx. Then store the new symbol at writeKey.
//   Returns the byte that was read (some callers stash it in a d* hint).
inline byte HashArmUpdate_(byte* arr, uint readKey, uint writeKey,
                           byte sym, int sc) {
  byte h = arr[readKey];
  SymLastCtx[256 * (sc == SymLastCtx[h]) + h] = sc;
  arr[writeKey] = sym;
  return h;
}

// helper 4: linear symbol search + rank-7 bubble-up
//   Find `sym` in `statesByte`'s STATE array; bubble it up while its saved
//   freq + `margin` <= prev.freq, stopping at/above rank 7. Record resulting
//   rank in the low nibble of *flagsByte. Returns the byte* of the new slot.
inline byte* FindAndBubble7_(byte* statesByte, byte sym, byte* flagsByte, int margin) {
  byte* p = statesByte;
  if (*p == sym) return p;
  do { p += 6; } while (*p != sym);
  word savedSF   = *(word*)p;
  uint savedSucc = *(uint*)(p + 2);
  byte* stopAt7  = statesByte + 42;     // 6 * 7
  while (true) {
    bool stable = ((sqword)p <= (sqword)statesByte) ||
                  (HIBYTE(savedSF) + margin <= (int)*(p - 5));
    if (stable && (sqword)p <= (sqword)stopAt7) {
      *(word*)p          = savedSF;
      *(uint*)(p + 2)    = savedSucc;
      *flagsByte        |= (sqword)(p - statesByte) / 6;
      return p;
    }
    word w = *(word*)(p - 6);
    uint s = *(uint*)(p - 4);
    *(word*)p       = w;
    *(uint*)(p + 2) = s;
    p -= 6;
  }
}

qword MixUpdate(byte* a1) {
  // ---- mixing-predictor weight pointers (q17..q25 hold heap addresses) -----
  uint* wQ17;     // single  += d46
  uint* wQ18;     // single  += d49
  uint* wQ19;     // pair    += d53 / -= d54
  uint* wQ20;     // single  += d47
  uint* wQ22;     // single  += d48
  uint* wQ23;     // pair    += d50 / -= d52
  int*  wpQ24;    // pred-pair (overflow halving)
  int*  wpQ25;    // pred-pair (overflow halving)
  int   scale;    // sseCum (decay for the pred-pair updates)

  // ---- per-step state ------------------------------------------------------
  byte*  foundState;       // == FoundState (alias of q9)
  int    sc;               // = SymCount - 1, the new SymCount
  int    prevSymCount;     // SymCount before --
  int    symEpoch;         // current SymEpoch (epoch counter)
  int    symEpochN;        // = symEpoch + 1 (next epoch)
  short  symEpochS;        // (short)symEpoch (used for &0xFFF index)
  sqword sseRowOff;        // symEpoch & 0x1FFFF (Sse2State row offset)
  char*  sseSlot;          // &Sse2State[ sseRowOff + 133144 ]  (recent-history byte buffer)

  // ---- symbol-derived state -----------------------------------------------
  uint   sym;              // FoundState->Symbol
  sqword matchHi;          // MatchCtxHi (high-byte context)
  sqword matchHi2;         // duplicate of matchHi (kept as int)
  int    mixCtxOld;        // MixCtx (saved before being used in SseSeed)
  uint   sse0sym;          // SSE0[sym]   (0 or 0x80 sym-type bit)
  int    mixCtx2New;       // new MixCtx2
  int    recentEpoch;      // SseCtx0_1[sym] before update
  int    recentForHi;      // SseCtx0_1[(int)matchHi]
  int    dt;               // symEpoch - recentEpoch
  int    bdiff;            // (byte)(sym - matchHi)
  int    predV38;          // running guess for FoundSymbol

  // ---- recent-pos chain walk (rp = walker, hashByte = MatchPosHash lookup)
  int    rp, rp1, rp2;
  int    hashByte;
  uint   cnt;              // 192-counter

  // ---- MatchPosTable update ------------------------------------------------
  sqword matchKey;
  int    matchPrev;
  uint   matchDelta;
  int    matchScore;       // 3-bit composite folded into OrderCtxSeed

  // ---- RSContext / Sse2State histogram rotation ---------------------------
  short  rsCtx;
  char   newQ12Sel;        // 2*d79 or ++d79 (selects new q12 base)
  sqword sse2Base;         // q12 (current Sse2State sub-block base)
  sqword sse2Saved;        // duplicate of sse2Base used in the halving loop
  sqword sseHistOff;
  byte   newHistCnt;
  sqword j;                // halving-loop index
  int    halved;

  // ---- sseSlot-relative history bytes used by MixScale heuristics ---------
  int    ssem3, ssem7;
  char   ssem11;

  // ---- offset-2 MatchPosPrev hint chain -----------------------------------
  int    m2_prev1;
  int    m2_h1;
  int    m2_prev2;
  sqword m2_h2;
  sqword m2_h3;
  int    m2_prev3;
  int    m2_bias;

  // ---- three paired byte-hash predictors (b32/b33, b34/b35, b36/b37) ------
  qword  epochBit;
  int    savedD90Idx;      // d90[epochBit] before update
  sqword newD90Idx;        // new value committed to d90[epochBit]
  bool   otherPar;         // !epochBit
  sqword oldD90IdxA;       // d90[!epochBit]
  sqword oldD90IdxB;       // d90[!epochBit] (re-read)
  sqword savedD91;
  sqword newD91;
  int    v94_b33;          // captured b33[newD90Idx] before BijectPairUpdate_

  // ---- MixScale BijectMap predictor ---------------------------------------
  char*  bmPtr;            // = sseSlot + 1
  uint   b1, b2;
  int    b3;
  char*  b1Ptr;            // &bmPtr[-MixScale]
  int    bm1;              // (byte)*(b1Ptr-1)
  sqword bmComposite;      // BijectMap row index
  sqword bmByte;
  char   predDelta;
  byte   predA, predB;

  // ---- context-suffix walk -------------------------------------------------
  int      ofall;          // tracks OrderFall through the function
  int      ofallSaved;     // OrderFall captured at the start of the walk
  int      ofallP1;        // OrderFall + 1
  int      ofallP3;        // OrderFall + 3
  int      orderShift15;   // (OrderFall > 0) << 15
  int      minNStates;     // MinContext->NStates
  int      searchSym;      // foundState->Symbol (for FindAndBubble7_)
  uint     minISuffix;     // MinContext->iSuffix
  sqword*  chain;          // = &CtxChain[1], grows as we walk suffixes
  int      maxOrd;         // MaxOrder
  qword    result;

  sqword heap;             // HeapNull
  byte*  walkCtx;          // current PPM_CONTEXT (as byte*) being walked
  int    depthLeft;        // counts down from OrderFall
  int    depth5;           // 5*OrderFall counter (decreasing)
  int    depth3;           // 3*OrderFall counter (decreasing)
  int    mixWeight;        // 2, halved each step
  uint   mixFlag1;         // computed from NStates / SummFreq
  uint   mixFlag2;         // copy of mixFlag1 (the loop guard)

  // deep find-and-bubble path
  sqword deepStatesIdx;    // walkCtx->iStates
  byte   deepFlags;        // walkCtx->Flags
  qword  deepStatesPtr;    // heap + deepStatesIdx
  byte*  deepFound;        // result of FindAndBubble7_(states, sym, ...)

  // shallow (trailing) find-and-bubble path
  sqword trailStatesIdx;
  byte   trailFlags;
  qword  trailStatesPtr;
  byte*  trailFound;

  byte*  onestatePtr;      // walkCtx + 2 (oneState when NStates == 0)
  sqword fastSuffix;       // walkCtx->iSuffix in NStates==0 fast-path
  sqword chain0;           // CtxChain[0]

  int    foundFreq;        // foundState->Freq
  int    deepSumFreq;      // walkCtx->SummFreq
  short  mixBoostA, mixBoostB;
  byte   newFoundFreq;

  int    trailBound;       // gating cutoff in trailing loop
  int    trailState0Freq;
  int    trailState1Freq;

  // ---- Section 1: simple additive predictor-weight updates ----------------
  wQ17 = (uint*)q17;
  wQ18 = (uint*)q18;
  wQ19 = (uint*)q19;
  wQ20 = (uint*)q20;
  wQ22 = (uint*)q22;
  wQ23 = (uint*)q23;
  wpQ24 = (int*)q24;
  wpQ25 = (int*)q25;
  prevSymCount = SymCount;
  sc           = SymCount - 1;
  SymCount     = sc;
  *(uint*)q21 += *(word*)(q21 + 6);
  *wQ17       += d46;
  *wQ20       += d47;
  *wQ22       += d48;
  *wQ18       += d49;
  *wQ23       += d50;  wQ23[1] -= d52;
  *wQ19       += d53;  wQ19[1] -= d54;

  symEpoch    = SymEpoch;
  symEpochS   = (short)SymEpoch;
  sseRowOff   = SymEpoch & 0x1FFFF;
  scale       = sseCum;
  sseSlot     = (char*)&Sse2State[sseRowOff + 133144];

  // ---- Section 2: weight-pair updates with overflow-driven halving --------
  UpdateWeightPair_(wpQ24, d55 + d56, 2 * scale);
  UpdateWeightPair_(wpQ25, d55,           scale);

  foundState = (byte*)q9;
  SparseBitmapA[SparseIdxA] |= SparseBit;
  SparseBitmapB[SparseIdxB] |= SparseBit;
  sym = *foundState;
  LODWORD(matchHi) = MatchCtxHi;
  SseState3[sseState3Hash] = sym;
  *(sseSlot-0x20000) = sym;
  *sseSlot = sym;
  recentSym = sym;
  MatchCtxHi = sym;
  sseState3Hash = (sym+(sseState3Hash<<6))&0x1FFFF;
  if( FoundSymbol>=0&&FoundSymbol!=MixCtx3 )
    b25 += b25+(sym==FoundSymbol);
  d65 = d66;
  d67 = Order1Ctx;
  SparseHashA = ((matchHi&0xFFFFFFF8)<<10)+32*(sym&0xFFFFFFF8);
  mixCtxOld = MixCtx;
  sse0sym = *((byte*)SSE0+sym);
  RunLength += MixCtx;
  SparseHashB = (8*(sym+SparseHashB))&0xFFF00;
  recentEpoch = SseCtx0_1[sym];
  mixCtx2New = MixCtx2+MixCtx2+(sse0sym>>7);
  MixCtx2 = mixCtx2New;
  RecentPos[symEpochS&0xFFF] = recentEpoch;
  SseCtx0_1[sym] = symEpoch;
  dt = symEpoch-recentEpoch;
  if( (uint)(symEpoch-recentEpoch)>=0x104 ) {
    d66 = 0;
    d72 = -1;
  } else {
    hashByte = (byte)MatchPosHash[(recentEpoch+1)&0x1FFFF];
    d72 = hashByte;
    if( dt>=50 )
      hashByte = 0;
    cnt = 192;
    d66 = hashByte;
    rp = RecentPos[recentEpoch&0xFFF];
    if( (uint)(symEpoch-rp)<0xC0 ) {
      do {
        --cnt;
        SymLastCtx2[(byte)MatchPosHash[(rp+1)&0x1FFFF]] = sc;
        rp = RecentPos[rp&0xFFF];
      } while( cnt>symEpoch-rp );
    }
  }
  matchKey = sym+(sqword)(int)((uint)matchHi<<8);
  matchPrev = MatchPosTable[matchKey];
  MatchPosPrev[(symEpoch-1)&0x1FFFF] = matchPrev;
  MatchPosTable[matchKey] = symEpoch-1;
  matchDelta = symEpoch-matchPrev;
  d75 = matchDelta;
  matchScore = (((uint)(symEpoch-matchPrev)<0xE800)+(matchDelta<0xF0)+(matchDelta<7))<<13;
  if( (uint)(symEpoch-matchPrev)>=0x1000 ) {
    Order1Ctx = 0;
    predV38 = 0;
    d76 = -1;
  } else {
    predV38 = (byte)MatchPosHash[(matchPrev+2)&0x1FFFF];
    Order1Ctx = predV38;
    d76 = (byte)MatchPosHash[(MatchPosPrev[matchPrev&0x1FFFF]+2)&0x1FFFF];
    if( predV38==d76 ) {
      MatchPosBySym[predV38] = sc;
      predV38 = Order1Ctx;
    }
    if( matchDelta>=0x240 )
      predV38 = 0;
  }
  rsCtx = RSContext;
  newQ12Sel = 2*d79;
  d79 *= 2;
  if( sym!=RSContext ) {
    sse2Base = q12;
    *(uint*)(q12+512) += 2;
    sse2Saved = sse2Base;
    sseHistOff = ((word)sym-rsCtx)&0x1FF;
    newHistCnt = *(byte*)(sseHistOff+sse2Base)+2;
    *(byte*)(sseHistOff+sse2Base) = newHistCnt;
    if( newHistCnt>0xA7u ) {
      *(uint*)(sse2Base+512) = 0;
      for( j = 0; j<512; ++j ) {
        halved = *(byte*)(j+sse2Saved)>>1;
        *(byte*)(j+sse2Saved) >>= 1;
        *(uint*)(sse2Saved+512) += halved;
      }
    }
    newQ12Sel = ++d79;
    if( sym!=d67 ) {
      b27[RSContext+(d67<<8)] = sym;
      newQ12Sel = d79;
    }
  }
  matchHi = (int)matchHi;
  matchHi2 = matchHi;
  q12 = (sqword)&Sse2State[516*(newQ12Sel&3)];
  recentForHi = SseCtx0_1[(int)matchHi];
  if( sym==FoundSymbol&&MixScale<=256 ) {
    d80 = 4*MixScale;
  } else if( d80>(uint)(3*MixScale)&&(prevSymCount==SymLastCtx[sym]||prevSymCount==SymLastCtx2[sym]||4*MixScale-9<(uint)d80) ) {
    d80 -= MixScale>13;
  } else if( dt>1 ) {
    rp1 = RecentPos[recentEpoch&0xFFF];
    if( dt==recentEpoch-rp1&&dt==rp1-RecentPos[rp1&0xFFF]&&dt<=256 ) {
      if( sym==(byte)sseSlot[-4*dt]||(rp2 = RecentPos[recentForHi&0xFFF], dt==recentForHi-rp2)&&dt==rp2-RecentPos[rp2&0xFFF]&&(uint)matchHi==(byte)sseSlot[-3*dt-1] ) {
        MixScale = dt;
        d80 = dt;
        q26 = (sqword)&d82;
      }
    }
  }
  d83 = -1;
  d84 = -1;
  d85 = -1;
  d86 = -1;
  d87 = -1;
  HashSeed1 = -1;
  bdiff = (byte)(sym-matchHi);
  HashSeed2 = -1;
  symEpochN = symEpoch+1;
  SymEpoch = symEpoch+1;
  if( bdiff==d88 ) {
    if( (uint)++ d89>1 ) {
      predV38 = (byte)(2*sym-matchHi);
      FoundSymbol = predV38;
      goto LABEL_94;
    }
    FoundSymbol = -1;
  } else {
    FoundSymbol = -1;
    d89 = 0;
    d88 = bdiff-(bdiff==0);
  }
  ssem3 = (byte)*(sseSlot-3);
  ssem7 = (byte)*(sseSlot-7);
  if( ssem3==ssem7||(ssem11 = *(sseSlot-11), (byte)(ssem11+(byte)ssem3-2*(byte)ssem7))||(byte)(*(sseSlot-15)+(byte)ssem7-2*ssem11) ) {
    if( 4*MixScale-1>(uint)d80 ) {
      // SIX MatchPosPrev hash-chain hint computations (offsets 3,4,5,8 wide
      // window; 6,10 short window with compact second arm).
      d86 = MatchPosHint_  (3, symEpoch, symEpochN, sc);
            MatchPosHint_  (4, symEpoch, symEpochN, sc);
            MatchPosHint_  (5, symEpoch, symEpochN, sc);
            MatchPosHint_  (8, symEpoch, symEpochN, sc);
            MatchPosHint16_(6, symEpoch, symEpochN, sc);
            MatchPosHint16_(10, symEpoch, symEpochN, sc);
      // four byte-pair-hash arms, all with the same arm-update pattern.
      byte sm0 = (byte)*sseSlot,    sm1 = (byte)*(sseSlot-1);
      byte sm2 = (byte)*(sseSlot-2), sm3 = (byte)*(sseSlot-3);
      byte sm4 = (byte)*(sseSlot-4), sm6 = (byte)*(sseSlot-6);
      byte sm7 = (byte)*(sseSlot-7), sm8 = (byte)*(sseSlot-8);
      HashArmUpdate_(SseState2, 256*sm1 + sm3, 256*sm2 + sm4, sym, sc);
      HashArmUpdate_(b28,       256*sm2 + sm6, 256*sm3 + sm7, sym, sc);
      d85 = HashArmUpdate_(b29, 256*sm0 + sm7, 256*sm1 + sm8, sym, sc);
      HashArmUpdate_(b30,       256*sm1 + sm7, 256*sm2 + sm8, sym, sc);

      // b31 arm uses a different routing (no collision branch, SymLastCtx only)
      uint b31_ri = (uint)(Order1Ctx + (d66 << 8));
      d83 = (byte)b31[b31_ri];
      SymLastCtx[(byte)b31[b31_ri]] = sc;
      if (sym != d65 && sym != d67) b31[d67 + (d65 << 8)] = sym;

      // final independent hint from RecentPos chain
      byte vh = MatchPosHash[(RecentPos[SseCtx0_1[matchHi2] & 0xFFFLL] + 2) & 0x1FFFF];
      SymLastCtx[256 * (sc == SymLastCtx[vh]) + vh] = sc;
    }
  } else {
    predV38 = (byte)(2*ssem3-ssem7);
    FoundSymbol = predV38;
  }
LABEL_94:
  m2_prev1 = MatchPosPrev[(symEpoch-2)&0x1FFFF];
  if( (uint)(symEpochN-m2_prev1)<0x20000 ) {
    m2_h1 = (byte)MatchPosHash[(m2_prev1+3)&0x1FFFF];
    d84 = m2_h1;
    SymLastCtx2[m2_h1] = sc;
    m2_prev2 = MatchPosPrev[m2_prev1&0x1FFFF];
    if( (uint)(symEpochN-m2_prev2)<0x20000 ) {
      m2_h2 = (byte)MatchPosHash[(m2_prev2+3)&0x1FFFF];
      SymLastCtx2[m2_h2] = sc;
      if( m2_h1==(uint)m2_h2 )
        MatchPosBySym[m2_h1] = sc;
      LODWORD(m2_h3) = -1;
      m2_prev3 = MatchPosPrev[m2_prev2&0x1FFFF];
      if( (uint)(symEpochN-m2_prev3)<0x20000 ) {
        m2_bias = 0;
        do {
          m2_bias += 6144;
          m2_h3 = (byte)MatchPosHash[(m2_prev3+3)&0x1FFFF];
          SymLastCtx2[m2_h3] = sc;
          m2_h1 &= m2_h3;
          LODWORD(m2_h2) = m2_h3|m2_h2;
          m2_prev3 = MatchPosPrev[m2_prev3&0x1FFFF];
        } while( (uint)(m2_bias+symEpochN-m2_prev3)<0x20000 );
      }
      if( m2_h1==(uint)m2_h2&&(int)m2_h3>=0 ) {
        if( HashSeed2<0 ) {
          HashSeed2 = m2_h1;
        } else if( HashSeed2==m2_h1 ) {
          HashSeed1 = m2_h1;
        }
      }
    }
  }
  // three paired byte-hash predictor updates (b32/b33, b34/b35, b36/b37).
  // Each reads at a "new" index and writes back at a different "old" index.
  epochBit = (symEpochN&1)==0;
  savedD90Idx = d90[epochBit];                                           // saved idx (current parity)
  newD90Idx = (word)(16*LOWORD(d90[epochBit])+((sym>>2)&0xFFFC))&0xFFFC;
  d90[epochBit] = newD90Idx;
  otherPar = !epochBit;
  oldD90IdxA = (uint)d90[otherPar];
  v94_b33 = (byte)b33[newD90Idx];                                     // capture before helper write
  BijectPairUpdate_(b32, b33, /*read*/newD90Idx, /*write*/oldD90IdxA, sym, sc);
  d92 = v94_b33;

  savedD91 = (uint)d91;
  newD91 = (word)(((sym>>4)&0xFFFE)+8*d91)&0xFFFE;
  BijectPairUpdate_(b35, b34, /*read*/newD91, /*write*/savedD91, sym, sc);
  d91 = newD91;

  oldD90IdxB = (uint)d90[otherPar];
  BijectPairUpdate_(b36, b37, /*read*/oldD90IdxB, /*write*/savedD90Idx, sym, sc);
  if( d80 ) {
    if( sym==*(byte*)q26 ) {
      *(byte*)(q26+3) += *(byte*)(q26+3)-255<0;
    } else {
      *(byte*)(q26+2) = *(byte*)(q26+1);
      *(byte*)(q26+1) = *(byte*)q26;
      *(byte*)q26 = sym;
      *(byte*)(q26+3) = 0;
    }
    bmPtr = sseSlot+1;
    b1 = (byte)bmPtr[-MixScale];
    b2 = (byte)bmPtr[-2*MixScale];
    b3 = (byte)bmPtr[-3*MixScale];
    if( --d80>(uint)MixScale )
      recentSym = b1;
    b1Ptr = &bmPtr[-MixScale];
    bm1 = (byte)*(b1Ptr-1);
    bmComposite = ((b1Ptr[2]==bmPtr[-2*MixScale+2])<<12)+(((b2&0x2E)+((byte)bmPtr[-2*MixScale+1]<(uint)(byte)b1Ptr[1]))<<8)+((((bm1+32-sym)>>31)+((bm1-sym)>>31)+((int)sym>=bm1))<<14);
    q26 = (sqword)&BijectMap[4*bmComposite+4*b1];
    SymLastCtx[(byte)BijectMap[4*bmComposite+2+4*b1]] = sc;
    SymLastCtx[*(byte*)(q26+1)] = sc;
    bmByte = *(byte*)q26;
    d87 = *(byte*)q26;
    SymLastCtx[bmByte] = sc;
    if( *(byte*)(q26+3) ) {
      if( *(byte*)(q26+3)>1u||d72<=0 )
        d72 = *(byte*)q26;
      MatchPosBySym[*(byte*)q26] = sc;
    }
    if( b1==b2&&b2==b3 ) {
      PrevSymbol = predV38;
      FoundSymbol = b1;
      MatchPosBySym[(byte)(b1+1)] = sc;
      SymLastCtx2[(byte)(b1-1)] = sc;
    } else if( FoundSymbol<0 ) {
      if( b1==b2||b2==b3 ) {
        PrevSymbol = predV38;
        FoundSymbol = b1;
        SymLastCtx2[(byte)(b3+1)] = sc;
        MatchPosBySym[(byte)(b1+1)] = sc;
        SymLastCtx2[(byte)(b1-1)] = sc;
        MatchPosBySym[b3] = sc;
      } else if( b1==b3 ) {
        PrevSymbol = predV38;
        if( b2==(byte)bmPtr[-4*MixScale]&&(byte)bmPtr[-5*MixScale]==b3 )
          b1 = b2;
        FoundSymbol = b1;
        MatchPosBySym[b2] = sc;
      } else {
        predDelta = b1+b3-2*b2;
        if( predDelta ) {
          PrevSymbol = predV38;
          if( *(byte*)(q26+3)<=0x10u ) {
            if( (byte)(predDelta+19)<=0x26u ) {
              predA = 2*b1-b2;
              predB = predA-predDelta;
              SymLastCtx[(byte)(predB+2)] = sc;
              SymLastCtx[(byte)(predB-2)] = sc;
              SymLastCtx[(byte)(predB+1)] = sc;
              SymLastCtx[predB] = sc;
              SymLastCtx2[(byte)(predA+2)] = sc;
              MatchPosBySym[(byte)(predA-2)] = sc;
              MatchPosBySym[(byte)(predA+1)] = sc;
              MatchPosBySym[(byte)(predA-1)] = sc;
              MatchPosBySym[predA] = sc;
            }
          } else {
            FoundSymbol = *(byte*)q26;
          }
        } else {
          FoundSymbol = (byte)(2*b1-b2);
          PrevSymbol = (byte)(2*b1-b2);
          SymLastCtx[(byte)(FoundSymbol+1)] = sc;
          SymLastCtx[(byte)(FoundSymbol-1)] = sc;
          SymLastCtx[(byte)(FoundSymbol+2)] = sc;
          SymLastCtx[(byte)(FoundSymbol-2)] = sc;
          MatchPosBySym[(byte)(FoundSymbol+1)] = sc;
          MatchPosBySym[(byte)(FoundSymbol-1)] = sc;
          MatchPosBySym[FoundSymbol] = sc;
        }
      }
    } else {
      PrevSymbol = predV38;
    }
  } else {
    PrevSymbol = predV38;
    MixScale = 1024;
    if( FoundSymbol<0 )
      FoundSymbol = HashSeed1;
  }
  ofall = OrderFall;
  CtxChain[0] = (sqword)foundState;
  orderShift15 = (OrderFall>0)<<15;
  OrderCtxSeed = orderShift15+matchScore+4*(recentSym&0x80);
  minNStates = *a1;
  NMasked = minNStates;
  searchSym = *foundState;
  minISuffix = *((uint*)a1+2);
  SseSeed = ((OrderFall>2)<<15)+orderShift15+*((uint*)BinMapTable+(mixCtx2New&0xF))+(mixCtxOld<<14);
  chain = &CtxChain_1;
  MixCtxExtra = (((OrderFall>32)+(OrderFall>8)+(OrderFall>4)+(OrderFall>3)+(OrderFall>2)+(OrderFall>1))<<12)+64;
  if( minISuffix ) {
    heap = HeapNull;
    walkCtx = (byte*)(HeapNull+minISuffix);
    depthLeft = OrderFall;
    depth5 = 5*OrderFall;
    if( !*walkCtx ) {
      do {
        if( chain>&CtxChain_2[1] )
          *(byte*)(*(chain-2)+1) += *(byte*)(*(chain-2)+1)-2<0;
        onestatePtr = walkCtx+2;
        fastSuffix = *((uint*)walkCtx+2);
        *chain++ = (sqword)onestatePtr;
        --depthLeft;
        walkCtx = (byte*)(heap+fastSuffix);
      } while( !*walkCtx );
      maxOrd = MaxOrder;
      if( ofall<MaxOrder ) {
        chain0 = CtxChain[0];
        if( *(byte*)(CtxChain[0]+1)<7u ) {
          if( chain<=&CtxChain_2[1] ) {
            ++*(byte*)(CtxChain_1+1);
          } else {
            ++*(byte*)(CtxChain_2[0]+1);
            if( chain>CtxChain_4 )
              *(byte*)(chain0+1) += *(byte*)(chain0+1)-4<0;
          }
        }
      }
      trailStatesIdx = *((uint*)walkCtx+1);
      trailFlags = walkCtx[1];
      goto LABEL_165;
    }
    mixWeight = 2;
    if( minNStates )
      mixFlag1 = (-45*minNStates+(uint)*((word*)a1+1))>>31;
    else
      mixFlag1 = d93==0;
    mixFlag2 = mixFlag1;
    ofallSaved = OrderFall;
    ofallP3 = OrderFall+3;
    ofallP1 = OrderFall+1;
    depth3 = 3*OrderFall;
    do {
      deepStatesIdx = *((uint*)walkCtx+1);
      deepFlags = walkCtx[1];
      if( !*(byte*)(heap+deepStatesIdx+6LL*(deepFlags&0xF)+1) ) {
        CtxChainEnd = (sqword)chain;
        BinEscFreq(walkCtx);
        deepStatesIdx = *((uint*)walkCtx+1);
        deepFlags = walkCtx[1];
      }
      walkCtx[1] = deepFlags&0xF0;
      deepStatesPtr = heap+deepStatesIdx;
      // deep find-and-bubble (freq margin 13)
      deepFound = FindAndBubble7_((byte*)(heap+deepStatesIdx), searchSym, &walkCtx[1], 13);
      foundFreq = foundState[1];
      *chain++ = (sqword)deepFound;
      depth5 -= 5;
      depth3 -= 3;
      --depthLeft;
      if( foundFreq>130||deepFound[1]>=0xE4u ) {
        trailBound = ofallP1;
        ofall = ofallSaved;
        maxOrd = MaxOrder;
        walkCtx = (byte*)(heap+*((uint*)walkCtx+2));
        goto LABEL_201;
      }
      deepSumFreq = *((word*)walkCtx+1);
      mixBoostA = mixWeight+(depth5>ofallP3);
      mixWeight >>= 1;
      mixBoostB = (7*deepSumFreq<4*deepFound[1]**walkCtx+4*(uint)deepFound[1])+(2*depthLeft>ofallP1)+mixBoostA;
      *((word*)walkCtx+1) = mixBoostB+deepSumFreq;
      newFoundFreq = mixBoostB+deepFound[1];
      deepFound[1] = newFoundFreq;
      walkCtx = (byte*)(heap+*((uint*)walkCtx+2));
    } while( newFoundFreq<0x45u&&depth3>ofallP3&&mixFlag2 );
    trailBound = ofallP1;
    ofall = ofallSaved;
    maxOrd = MaxOrder;
LABEL_201:
    while( trailBound<4*depthLeft ) {
      trailStatesIdx = *((uint*)walkCtx+1);
      trailFlags = walkCtx[1];
      if( *(byte*)(heap+trailStatesIdx+6LL*(trailFlags&0xF))==searchSym )
        break;
LABEL_165:
      trailStatesPtr = heap+trailStatesIdx;
      if( !*(byte*)(heap+trailStatesIdx+6LL*(trailFlags&0xF)+1) ) {
        CtxChainEnd = (sqword)chain;
        BinEscFreq(walkCtx);
        trailStatesIdx = *((uint*)walkCtx+1);
        trailFlags = walkCtx[1];
        trailStatesPtr = heap+trailStatesIdx;
      }
      walkCtx[1] = trailFlags&0xF0;
      // shallow find-and-bubble (freq margin 1 == strict less)
      trailFound = FindAndBubble7_((byte*)trailStatesPtr, searchSym, &walkCtx[1], 1);
      trailState0Freq = *(byte*)(trailStatesIdx+heap+1);
      trailState1Freq = *(byte*)(trailStatesIdx+heap+7);
      *chain++ = (sqword)trailFound;
      if( (uint)(trailState1Freq+trailState0Freq)>0x5F )
        break;
      walkCtx = (byte*)(heap+*((uint*)walkCtx+2));
      --depthLeft;
      trailBound = ofall+1;
    }
    CtxChainEnd = (sqword)chain;
  } else {
    maxOrd = MaxOrder;
    CtxChainEnd = (sqword)&CtxChain_1;
  }
  if( ofall==maxOrd&&(result = HeapNull+*(uint*)(foundState+2), result>=UnitsStart) ) {
    RootContext = HeapNull+*(uint*)(foundState+2);
    MaxContext0 = result;
  } else {
    result = ReduceOrder();
    ofall = OrderFall;
  }
  OrderFall0 = ofall;
  return result;
}
//--- #return
//--- #include "subs_block.inc"

sqword PPMIIGetCurrentModelSize() {
  sqword result;
  sqword v1;
  uint i;
  int v3;
  if( !SubAllocatorSize )
    return 0;
  v1 = 0;
  LODWORD(result) = pText-UnitsStart+LoUnit+SubAllocatorSize-HiUnit;
  for( i = 0; i<0x26; ++i ) {
    v3 = *(uint*)(BList+12*v1)*12**((byte*)&Indx2Units+v1);
    v1 = i+1;
    result = (uint)(result-v3);
  }
  return result;
}

sqword StartSubAllocator(uint memsize_mb, int a2_order, int a3) {
  int v4;
  size_t memsize_b;
  v4 = a2_order;
  if( !memsize_mb ) return 0;
  if( memsize_mb>0xFFF ) return 0;
  if( a2_order<2 ) return 0;
  if( a2_order>16 ) return 0;
  if( SubAllocatorSize ) return 0;
  memsize_b = memsize_mb<<20;
  HeapStart = new char[memsize_b]; // malloc(memsize_b);
  //  HeapStart = VAlloc<char>(memsize_b);
  // printf( "!p=%I64X size=%I64X!\n", memsize_b, qword(memsize_b) );
  if( !HeapStart ) return 0;
  RunLength = -100;
  SubAllocatorSize = memsize_b;
  InitsCount = 0;
  CutOff = a3;
  Interrupted = 0;
  if( v4>12 )v4 = 16<<((v4+19)&31);
  MaxOrder = v4;
  return 1;
}

sqword PPMIIDeleteModel() {

  if( SubAllocatorSize==0) return 0;

  qword finalSize = SubAllocatorSize;

  if( (InitsCount==1) && (CutOffCount+GlueCount==0) ) {
    qword textSize = ((char*)pText) - ((char*)HeapStart);
    
    qword scaledUnits = ((108 * (SubAllocatorSize / 120)) - (HiUnit-LoUnit)) / 9; // 108/120=0.9  /9=0.1?
    
    // Find the maximum of the two metrics
    qword maxMetric = (scaledUnits > textSize) ? scaledUnits : textSize;
    qword sizeLimit = (10 * maxMetric) + 12;

    // Cap finalSize at the calculated limit
    if( SubAllocatorSize > sizeLimit ) finalSize = sizeLimit;
  }

  // Free memory and reset state
  SubAllocatorSize = 0;
  free( HeapStart );

  // Return the calculated size rounded UP to the nearest Megabyte (2^20 bytes)
  return (finalSize + 0xFFFFF) >> 20;
}

#if 0
//MEM_DIVISOR=10;
UINT PPMIIDeleteModel() {
  if( !SubAllocatorSize ) return 0;
  size_t MemTouched = SubAllocatorSize;
  if( InitsCount==1&&CutOffCount+GlueCount==0 ) {
    size_t USSize = GetSizeOfUnitsSection(SubAllocatorSize);
    MemTouched = MEM_DIVISOR*MAX(size_t(pText-HeapStart), (USSize-(HiUnit-LoUnit))/(MEM_DIVISOR-1));
    MemTouched = MIN(MemTouched+UNIT_SIZE, SubAllocatorSize);
  }
  SubAllocatorSize = 0;
  free(HeapStart);
  return (MemTouched+(1<<20)-1)>>20;
}
#endif
//--- #return

//--- #include "rc.inc"

struct Rangecoder {
  uint Range;
  uint Code;
  uint Cache;
  uint ff_count;
  qword Low;

  uint SubRange;

  uint getSubRange(uint freq, uint totFreq) {
    return freq * (Range / totFreq);
  }

  void encodeSymbol(uint subRange) {
    SubRange = subRange;
  }

  void encodeEscape(uint subRange) {
    Low += subRange;
    Range -= subRange;
  }

  bool IsDecodeMatched(uint subRange) {
    if (Code < subRange) {
      SubRange = subRange;
      return true;
    }
    return false;
  }

  void DecodeNotMatched(uint subRange) {
    Code -= subRange;
    Range -= subRange;
  }

  void commitRange() {
    Range = SubRange;
  }

  void initEncoder() {
    Low = 0;
    Cache = 0;
    Range = -1;
    ff_count = 0;
  }

  void initDecoder(FILE *f) {
    Range = -1;
    int v13 = getc(f);
    int v15 = getc(f);
    int v18 = getc(f);
    int v21 = getc(f);
    int v24 = getc(f);
    int v16 = v15 | (v13 << 8);
    int v19 = v18 | (v16 << 8);
    int v22 = v21 | (v19 << 8);
    Code = v24 | (v22 << 8);
  }

  void EncodeShift(FILE *f) {
    if ((Low ^ 0xFF000000LL) <= 0xFFFFFF) {
      ++ff_count;
    } else {
      putc(Cache + (int)(Low >> 32), f);
      int carry = (int)(Low >> 32) + 255;
      if (ff_count) {
        do {
          putc(carry, f);
        } while (--ff_count);
        Low = (uint)Low;
      }
      Cache = (Low >> 24) & 0xFF;
    }
    Low = (uint)(Low << 8);
    Range <<= 8;
  }

  void EncodeNormalize(FILE *f) {
    while (Range < 0x1000000) {
      EncodeShift(f);
    }
  }

  void DecodeNormalize(FILE *f) {
    while (Range < 0x1000000) {
      Code = getc(f) | (Code << 8);
      Range <<= 8;
    }
  }

  void Flush(FILE *f) {
    for (int i = 0; i < 5; ++i) {
      if ((Low ^ 0xFF000000LL) <= 0xFFFFFF) {
        ++ff_count;
      } else {
        putc(Cache + (int)(Low >> 32), f);
        int carry = (int)(Low >> 32) + 255;
        if (ff_count) {
          do {
            putc(carry, f);
          } while (--ff_count);
          Low = (uint)Low;
        }
        Cache = (Low >> 24) & 0xFF;
      }
      Low = (uint)(Low << 8);
    }
  }
};
//--- #return
Rangecoder rc;

//--- #include "subs_process1.inc"

// =============================================================================
//  RealProcess<f_DEC>() - templated encode/decode driver
// -----------------------------------------------------------------------------
//  PE binary's analog of RealEncode() / RealDecode() in ppmd.cpp (lines
//  1217-1313 there), folded into one template with f_DEC = 0 (encode) or 1
//  (decode). Heavily SSE-augmented compared to textbook PPMd.
//
//  Mapping of PE goto labels to ppmd primitives:
//      first block under "if (MinContext->NStates)"   ~  decodeLES1 / encodeLES1
//      block from LABEL_18 onward                       ~  decode1 / encode1
//      block under the "else" of NStates check          ~  decode0 / encode0
//      block from LABEL_59 (the escape walk)            ~  decode2 / encode2 escape
//      LABEL_128 / LABEL_250                            ~  SYMBOL_FOUND + PrepareNextStep
//      LABEL_335 / LABEL_298 / LABEL_296 / LABEL_292    ~  inner SSE-mix sub-steps
//
//  Naming conventions for locals (suffix tags the section):
//      _A   multi-state initial mix block (NStates > 0)
//      _B   single-state binary coder (NStates == 0)
//      _C   LABEL_298 escape mirror (parallels _A)
//      _E   escape walk (LABEL_128 area)
//      _F   LABEL_59 per-candidate loop
//      _M   freq-mixing loop inside the initial multi-state block
//
//  File-local helpers (declared in the anonymous namespace below) replace
//  13 distinct repeated idioms covering ~80 inlined call sites:
//
//      MaybeRescale1_     SseScale1 + freq0 refresh                       9x
//      MaybeRescale2_     SseScale2 + freq0 refresh                       1x
//      RescaleAccum1_     MaybeRescale1 + commit slot.freq0 += weight>>n  9x
//      RescaleAccum2_     MaybeRescale2 variant                          13x
//      SseClampMean_      mean = scale*slot[0]/slot[1], clamped           5x
//      SseDeltaUpdate_    Bayesian (num,den) update + overflow halve      8x
//      SseMixUpdate_      Abbreviated SSE accumulator update              4x
//      ClampToBand_       Asymmetric clamp [lo, hi] for SSE gain          6x
//      BubbleSortChain_   CtxChain[] insertion sort by priority           2x
//      FillFreqMap_       b39[Sym] = Freq prologue                        2x
//      WalkEscapeChain_   Walk suffix chain past escape symbol            2x
//      RewindPredictor_   LABEL_128 "undo this round's deltas"            6x
//      FreqMixStep_       Freq-mixing inner-loop body                     2x
//
//  Also performed: 110+64 dead-variable declarations removed; declaration
//  block compacted into 70 grouped lines; every v* identifier given a
//  semantic name; long index/seed mega-expressions formatted vertically
//  with column-aligned weights; section header comments at every label.
//
//  The body's goto layout is preserved exactly -- it's irreducible at the
//  source level.
// =============================================================================

namespace {

// SseScale1 rescales the (sum, freq0, freq1) slot if freq0 or weight overflow.
// After the call, freq0 is refreshed from the slot. The caller's local copy
// of freq0 is updated; the weight value is captured by value (not refreshed).
template<typename T>
inline void MaybeRescale1_(void* slot, T& freq0Local, uint weight) {
  if ((uint)freq0Local > 0x8000u || weight > 0x80000u) {
    SseScale1((sqword)slot);
    freq0Local = (T)*((word*)slot + 2);     // slot->freq0 (offset 4 bytes)
  }
}

// SseScale2 variant: no weight check, just freq0 > 0x8000.
template<typename T>
inline void MaybeRescale2_(void* slot, T& freq0Local) {
  if ((uint)freq0Local > 0x8000u) {
    SseScale2((sqword)slot);
    freq0Local = (T)*((word*)slot + 2);     // slot->freq0 (offset 4 bytes)
  }
}

// MaybeRescale1_ + commit "slot.freq0 += (slot.weight >> shift)" pattern.
// Returns the accumulated delta so callers can stash it in a d-global.
inline int RescaleAccum1_(void* slot, uint weight, int shift) {
  word freq0 = *((word*)slot + 2);
  MaybeRescale1_(slot, freq0, weight);
  int  delta = (int)((uint)*((word*)slot + 3) >> shift);
  *((word*)slot + 2) = (word)(freq0 + delta);
  return delta;
}

// MaybeRescale2_ variant of the above.
inline int RescaleAccum2_(void* slot, int shift) {
  word freq0 = *((word*)slot + 2);
  MaybeRescale2_(slot, freq0);
  int  delta = (int)((uint)*((word*)slot + 3) >> shift);
  *((word*)slot + 2) = (word)(freq0 + delta);
  return delta;
}


// Bayesian-style SSE pair (num, den) update with overflow halving on both
// the pre-update absolute-value test and the post-update sum test.
//   p[0] -= delta;   p[1] += delta + adder;   halve both if either overflows.
// Used 4x with parameter triples (0x40000, 4096, 2) and (0x80000, 0x2000, 1120).
inline void SseDeltaUpdate_(int* p, int delta,
                            int absThresh, int denThresh, int adder) {
  int num = p[0];
  int den = p[1];
  if ((int)abs32(p[0]) > absThresh) {
    num >>= 1;
    p[0] = num;
    den >>= (den > denThresh);
  }
  int newNum = num - delta;
  p[0] = newNum;
  int newDen = delta + den + adder;
  if (newDen > 0x40000000) {
    p[0] = newNum >> 1;
    newDen >>= 1;
  }
  p[1] = newDen;
}

// Abbreviated SSE accumulator update (positive delta, no post-overflow check).
//   p[0] += delta;   p[1] += adder;   halve both if pre-update test trips.
// Used 4x with the same absThresh=0x100000 / denThresh=0x2000 thresholds.
inline void SseMixUpdate_(int* p, int delta, int adder) {
  int num = p[0];
  int den = p[1];
  if ((int)abs32(p[0]) > 0x100000) {
    num >>= 1;
    p[0] = num;
    den >>= (den > 0x2000);
  }
  p[0] = num + delta;
  p[1] = den + adder;
}

// "If val is in band [lo, infinity), clamp to [lo, hi]" pattern used to keep
// SSE gain estimates in range. val_default starts at lo; if val >= lo, set to
// hi; if val < hi, set to val. Used 4x with different (lo, hi) pairs.
inline sqword ClampToBand_(sqword val, sqword lo, sqword hi) {
  sqword r = lo;
  if (val >= lo) {
    r = hi;
    if (val < hi) r = val;
  }
  return r;
}

// Common SSE-stage prologue: compute mean = scale * slot[0] / slot[1], then
// clamp into [lo, hi]. Used 5x as the first half of each Sse1/SseMatch/Sse2/
// Sse3 stage in both mirrored mix sections.
inline sqword SseClampMean_(int* slot, sqword scale, sqword lo, sqword hi) {
  sqword mean = scale * (sqword)slot[0] / slot[1];
  return ClampToBand_(mean, lo, hi);
}

// One step of the freq-mixing loop: given the current state's freq, the
// suffix-context's freq for this symbol (b39[sym]), the running (sumFreq,
// sumFreqW) state and the constant term `constMix`, conditionally rescale
// the state's freq and accumulate the new value back into the parent
// context's SummFreq. Used 2x (initial mix loop + LABEL_298 mirror).
inline void FreqMixStep_(STATE* st, byte sxFreq, uint mixWeight,
                         uint constMix, int& sumFreq, int& sumFreqW,
                         PPM_CONTEXT* ctx) {
  uint curFreq = st->Freq;
  uint comb    = constMix + (uint)sumFreqW;
  if (curFreq * mixWeight >= comb * sxFreq || curFreq > 0xE4u) return;
  int  freqDelta = sumFreq - (int)curFreq;
  uint cm        = comb - curFreq;
  uint newFreq   = (cm*(3*curFreq + sxFreq) + 3*cm + mixWeight - sxFreq - 4)
                   / (3*cm + mixWeight - sxFreq);
  if (newFreq > curFreq + 11) newFreq = curFreq + 11;
  sumFreq      = (int)(newFreq + freqDelta);
  ctx->SummFreq = (word)sumFreq;
  st->Freq     = (byte)newFreq;
  sumFreqW     = (int)(word)sumFreq;
}

// Bubble-sort-insert idiom for the CtxChain[] array. Walks from chainEnd-1
// downward, swapping adjacent entries as long as the higher one's freq is
// dominated by `sortPriority * lower.Freq`. Used 2x in mirrored state-search
// loops (the original LABEL_14 and LABEL_292 sort entries by priority).
inline void BubbleSortChain_(sqword* chainEnd, sqword* sortLimit, int sortPriority) {
  for (sqword* p = chainEnd - 1; p > sortLimit; --p) {
    sqword tmp = *(p - 1);
    if (sortPriority * ((STATE*)*p)->Freq <= ((STATE*)tmp)->Freq) break;
    *(p - 1) = *p;
    *p = tmp;
  }
}

// Populate the b39[] frequency lookup table from a PPM context's states.
// b39[state.Symbol] = state.Freq, for each of NStates+1 states. Used 2x as
// the prologue to the freq-mixing loops below.
inline void FillFreqMap_(PPM_CONTEXT* ctx) {
  int   n = ctx->NStates + 1;
  STATE* s = ctx->getStates();
  do {
    b39[s->Symbol] = s->Freq;
    ++s;
  } while (--n);
}

// Walk the suffix chain from `startCtx`, while its rank-0 symbol equals
// `escSym` AND its NStates matches `refCtx`. Returns the walked-to context;
// writes the final symbol to `outFinalSym` and to the global EscapeSymbol.
// Used 2x (initial section + LABEL_298 mirror).
inline PPM_CONTEXT* WalkEscapeChain_(PPM_CONTEXT* startCtx, PPM_CONTEXT* refCtx,
                                     int escSym, int& outFinalSym) {
  PPM_CONTEXT* w = startCtx;
  byte sym = w->getStates()[w->Flags & 0xF].Symbol;
  while (sym == (byte)escSym && w->NStates == refCtx->NStates) {
    w = (PPM_CONTEXT*)Indx2Ptr(w->iSuffix);
    sym = w->getStates()[w->Flags & 0xF].Symbol;
  }
  outFinalSym  = sym;
  EscapeSymbol = sym;
  return w;
}

// "Rewind" a predictor slot in the LABEL_128 escape path:
//   freq0 (offset 4, word) -= delta
//   sum   (offset 0, uint) += delta * mult
// Used 6x in the remCandF == 0 branch (LABEL_128 fallback) to undo this round's
// predictor contributions, scaled by mult = predRescaleDiv / (NStates+1).
inline void RewindPredictor_(sqword slotAddr, int delta, int mult) {
  *(word*)(slotAddr + 4) -= (word)delta;
  *(uint*)slotAddr       += (uint)(delta * mult);
}

// =============================================================================
//  Constexpr builder for SSE / mix context composite indices.
// -----------------------------------------------------------------------------
//  The PE binary builds several "bitfield" indices (mixIdxA, mixIdxC, seeIdxF,
//  OrderCtxSeed, sse2IdxA/F, etc.) as sums of small per-feature terms each
//  contributing at a fixed bit position. Written verbatim as
//      idx = 8*(cond1) + (val2 & 3) + 16*(cond3) + ...;
//  the bit positions are invisible. This builder makes them explicit:
//
//      .bit<P>(b)        adds (b ? 1 : 0) << P
//      .bits<P, W>(v)    adds (v & ((1<<W)-1)) << P
//      .field<P, W>(v)   adds v & (((1<<W)-1) << P)    (v already pre-positioned)
//      .raw(v)           adds v unmasked                (escape hatch for
//                                                       non-contiguous masks)
//
//  All methods are constexpr; the template parameters are compile-time
//  constants, so -O2 folds the chain into the same imm-shift / imm-or
//  sequence as the hand-written sum.
// =============================================================================
struct SseIdx {
  uint val = 0;

  template <int Pos>
  constexpr SseIdx& bit(bool b)        { val += (uint)b << Pos;             return *this; }

  template <int Pos, int W>
  constexpr SseIdx& bits(uint v)       { val += (v & ((1u<<W)-1)) << Pos;   return *this; }

  template <int Pos, int W>
  constexpr SseIdx& field(uint v) {
    constexpr uint M = ((1u<<W) - 1) << Pos;
    val += v & M;
    return *this;
  }

  constexpr SseIdx& raw(uint v)        { val += v;                          return *this; }

  constexpr operator uint() const      { return val; }
};

} // namespace

template< int f_DEC > int RealProcess(FILE* outFile, FILE* inFile) {
  int inputByte, epoch;
  int nStatesP1Save;
  int predShiftFlags, predBinFlags;
  int cumFreqC;
  int entryNStates;
  int walkNStates, walkDelta, descendNStates, freqDeltaE, remStatesE, freqSumE;
  int walkFreqSumE, walkSymE, currentSymbol, mixCtx, mixFreqB, mixHitsB;
  int sse1CumInB, sse1ClampB, cumWeightB, cumFreqB, escSymB;
  int matchCumInA, sseMatchClampA, sseSum2A;
  int sse2CumInA, sse2ClampA, totFreqA;
  int cumFreq, sse3ClampA, oneStateFreqF;
  int sortPriorityC;
  int sxNStatesC, mixFreqC;
  int oneStateFreqCachedF;
  int maskFlagPrevC, sumFreqCacheC;
  int descendNStatesP1E, ofallSavedE;
  int descendNStatesP1C, sparseFlags, remCandF, escSymbol;
  int escCandidate, d106Cache;
  byte flagsCtxFC, minCtxFlagsC, flagsSaveA;
  sqword *chainPtr, *chainEndE;
  sqword *chainEndF, *sortRangeE, *sortLimitC;
  STATE *FoundState, *walkStateIterE, *firstStateE;
  PPM_CONTEXT *MinContext, *sx_p, *suffixCtxC, *preCommitMinCtx;
  uint mixDeltaA, cumFreqMixA, cumFreqDivA, sumFreqF;
  uint totFreqC, subRangeC;
  uint seeIndex, suffixNStates;
  uint mixShiftSelB, binSseVal;
  uint totFreq, subRange, mixWeightC, mixWeightDeltaC;
  uint sumFreqDivC;
  uint mixWeightSavedA, mixFreqCacheC, maskFlagEsc, maskFlagPrev, mixFreqA, mixWeightA;
  uint d103Cache;
  char descendFlags, mixShiftB, mixShiftC, predShiftIncC, shiftSelC;
  char mixShiftBSel, mixShiftA;
  sqword mixIdxA, sseSlot4A;
  sqword result, mixIdxB;
  sqword sse2IdxA;
  sqword mixIdxC, mixOffsetC, priorFoundStateF, sse3SlotC, sse4SlotC;
  sqword sseSlot3A, sseQTableIdxC;
  sqword sseQTableIdxA, summFreqPtr;
  int *mixSlotA, *mixBaseAStride, *binMixSlotF, *sse1SlotF, *predWAF;
  int *predWBF, *sseMatchSlotF, *sse2SlotF, *sse3SlotF, *mixBaseB, *mixSlotB;
  int *sse1SlotB, *binSseSlotB, *sseMatchSlotA, *sse2SlotA, *sse3SlotA, *bigSlotC;
  int *bigSlotA;
  bool predLoBeyondC, mixShiftLowA;
  short matchCtxHiSave, freqBoostFC, orderCtxSeedSave;
  char *mixSlotC, *mixStrideC;
  // sseCum/sseTot are the per-cascade-stage accumulator pair, file-scope
  // because MixUpdate also reads sseCum on its way out.
  // Each SSE cascade stage publishes its slot pointer through one q-global so
  // MixUpdate can update that same cell on the way back out.
  int*& sse1Slot     = (int*&)q23;
  int*& sseMatchSlot = (int*&)q19;
  int*& sse2Slot     = (int*&)q24;
  int*& sse3Slot     = (int*&)q25;
  // The center pointer of the current binary-mix cell (4-word layout). Set
  // once per branch, then re-read by the deeper sub-stage to grab the weight.
  word*& binMixCenter = (word*&)q21;
  // BinSse cell and the PredWeight A/B cells. Each is a 2-uint cell; the
  // commit-tail reads/writes them as `slot[0] += d##; slot[1] += d##;`.
  // (q36, q37, q39 are only ever referenced from this file; they got hoisted
  // to file scope by the decompiler but are really per-symbol scratch.)
  uint*& binSseCell  = (uint*&)q36;
  uint*& predWeightA = (uint*&)q39;
  uint*& predWeightB = (uint*&)q37;
  // q12 holds the base of the current Sse2State sub-block (a 516-byte chunk;
  // the histogram occupies bytes 0..511, the running counter sits at +512).
  byte*& sse2Base = (byte*&)q12;
  epoch = SymCount;
  do {
    // -----------------------------------------------------------------------
    //  Per-symbol outer loop: read input byte (encode), pick context, dispatch
    //  on the multi-state / single-state branch.
    // -----------------------------------------------------------------------
    if( !f_DEC ) inputByte = getc(inFile);
    MinContext = MaxContext;
    if( MinContext->NStates ) {
      // ---------------------------------------------------------------------
      //  Multi-state branch  (~ ppmd::decodeLES1 / encodeLES1 + decode1 / encode1)
      // ---------------------------------------------------------------------
      int  nStates = MinContext->NStates;
      byte ctxFlags = MinContext->Flags;
      if( !MinContext->getStates()[ctxFlags&0xF].Freq ) {
        BinEscFreq((byte*)MinContext);
        nStates = MinContext->NStates;
        ctxFlags = MinContext->Flags;
      }
      uint nStatesPlus1 = nStates+1;
      int  remStates = nStates+1;
      CtxChain[0] = (sqword)&MinContext->getStates()[ctxFlags&0xF];
      sqword* chainEnd = &CtxChain_1;
      sqword* chainStart = &CtxChain_1;
      escSymbol = ((STATE*)CtxChain[0])->Symbol;
      MixCtx3 = escSymbol;
      STATE* stateIter = MinContext->getStates() - 1;
      SymMask[((STATE*)CtxChain[0])->Symbol] = epoch;
      while( 1 ) {
        stateIter += 1;
        int walkSym = stateIter->Symbol;
        int sortPriority;
        sqword* sortLimit;
        if( escSymbol!=walkSym ) {
          SymMask[stateIter->Symbol] = epoch;
          *chainEnd++ = (sqword)stateIter;
          if( walkSym==FoundSymbol ) {
            sortPriority = 22;
            sortLimit = &CtxChain[(b25&7)==0];
LABEL_14:
            BubbleSortChain_(chainEnd, sortLimit, sortPriority);
            ++chainStart;
            goto LABEL_18;
          }
          if( epoch==MatchPosBySym[walkSym]||epoch==SymLastCtx2[walkSym] ) {
            sortLimit = chainStart;
            sortPriority = 11*(epoch==MatchPosBySym[walkSym])+7;
            goto LABEL_14;
          }
        }
LABEL_18:
        // After scanning all states in MinContext: enter the SSE-mix block.
        if( !--remStates ) {
          int nStatesCnt = nStates+1;
          // These are written only in the else branch but read inside the
          // if(nStatesPlus1<24) ... LABEL_58 path; declare at this scope so
          // the goto LABEL_58 from line ~549 doesn't bypass init.
          int  sxNStates    = 0;
          int  minSumFreqA  = 0;
          int  sxSumFreqA0  = 0;
          int  sumFreqSaveA = 0;
          nStatesP1Save = nStates+1;
          RSContext = ((STATE*)CtxChain[0])->Symbol;
          SymLastCtx[(byte)b27[RSContext+(Order1Ctx<<8)]] = epoch;
          q29 = q30 = q31 = q32 = q33 = (sqword)d27;
          if( nStatesPlus1==256 ) {
            predRescaleDiv = MinContext->SummFreq;
            q34 = (sqword)d27;
            escCandidate = -1;
            EscapeSymbol = -1;
            cumFreqMixA = predRescaleDiv+1;
            cumFreqAcc = cumFreqMixA;
        } else {
            sx_p = (PPM_CONTEXT*)Indx2Ptr(MinContext->iSuffix);
            sxNStates = sx_p->NStates;
            minSumFreqA = MinContext->SummFreq;
            sxSumFreqA0 = sx_p->SummFreq;
            CtxChainEnd = (sqword)CtxChain;
            nStatesP1Save = sxNStates+1;
            flagsSaveA = MinContext->Flags;
            sumFreqSaveA = minSumFreqA;     // default; the FreqMix branch below overrides
            if(   (sxNStates+1)*minSumFreqA <= (int)(sxSumFreqA0*nStatesPlus1)
               && MinContext->getStates()[0].Freq < 0x6Au
               && (flagsSaveA & 0x40) == 0 ) {
              FillFreqMap_(sx_p);
              STATE* stateBackM = &MinContext->getStates()[nStatesPlus1];
              int  mixConstM  = 11*(nStates+1);
              int  sumFreqM   = minSumFreqA;          // mutated by FreqMixStep_ via reference
              int  sumFreqWM  = sumFreqM;             // ditto
              int  mixWeightM = nStatesP1Save*(((uint)(mixConstM-sumFreqM)>>28)|7)+sxSumFreqA0;
              do {
                stateBackM -= 1;
                FreqMixStep_(stateBackM, b39[stateBackM->Symbol], mixWeightM,
                             mixConstM, sumFreqM, sumFreqWM, MinContext);
              } while( --nStatesCnt );
              sumFreqSaveA = sumFreqWM;
              flagsSaveA   = MinContext->Flags;
            }
            {
              // maskFlagEsc captures the suffix context's rank-0 symbol;
              // WalkEscapeChain_ then rewrites it (via outFinalSym/EscapeSymbol).
              PPM_CONTEXT* escWalkCtx = (PPM_CONTEXT*)Indx2Ptr(MinContext->iSuffix);
              maskFlagEsc = epoch != SymMask[escWalkCtx->getStates()[escWalkCtx->Flags&0xF].Symbol];
              WalkEscapeChain_(escWalkCtx, MinContext, escSymbol, escCandidate);
            }
            maskFlagPrev = epoch!=SymMask[PrevSymbol];
            sseQTableIdxA = SSE0QTable[nStatesPlus1-2];
            // mixIdxA: composite index into MixWeight2. The two former
            // ">> 26 & mask" / ">> 27 & mask" terms in the decompilation are
            // 1-bit predicates dressed up: each extracts the sign bit of an
            // int subtraction and places it at a specific position. Rewritten
            // as the underlying predicates.
            mixIdxA = SseIdx{}
              .bits <0, 2> (MixCtx2)                                 // low 2 bits of the rolling mix counter
              .bit  <2>    (OrderFall < 10)                          // still near the highest order?
              .bit  <3>    (nStates + 2*sxNStates + 2 > NMasked)     // parent context very full?
              .bit  <4>    (4*nStates + 4         > 3*sxNStates + 3) // suffix-NStates shrank a lot? (was >>27 sign trick)
              .bit  <5>    (sumFreqSaveA          > 12*nStates + 12) // SummFreq above 12*(NStates+1)? (was >>26 sign trick)
              .field<6, 2> (flagsSaveA)                              // Flags bits 6-7 (sym-class hi bits)
              .bit  <8>    (maskFlagPrev)                            // previous symbol not seen this iter
              .bit  <9>    (epoch != SymMask[escCandidate]);         // escape candidate not seen this iter
            mixSlotA = &MixWeight2[2048*sseQTableIdxA+2*mixIdxA];
            q34 = (sqword)mixSlotA;
            mixWeightA = *mixSlotA;
            sseCum = mixWeightA;
            mixFreqA = (word)MixFreq2_1[4096*sseQTableIdxA+4*mixIdxA];
            sseTot = mixFreqA;
            mixDeltaA = RescaleAccum1_(mixSlotA, mixWeightA, 0);
            if( mixDeltaA>0x80 ) {
              bigSlotA = &d29[512*sseQTableIdxA + 2 * (int)(SseIdx{}
                .field<0, 2> ((byte)mixIdxA)                  // mixIdxA bits 0-1
                .bit  <3>    (maskFlagEsc | maskFlagPrev)
                .field<4, 4> ((byte)mixIdxA))];                // mixIdxA bits 4-7
              q29 = (sqword)bigSlotA;
              mixShiftA = mixDeltaA<0x200;
              q33 = (sqword)(mixSlotA+2048);
              // blend the two neighbour cells (mixSlotA - 2048 and + 2048)
              // into the running (mixWeightA, mixFreqA) accumulators.
              q32             = (sqword)(mixSlotA-2048);
              mixWeightSavedA = mixSlotA[2048];
              mixWeightA = ((mixWeightSavedA + *(mixSlotA-2048))            >> (mixShiftA+1)) + mixWeightA;
              mixFreqA   = ((uint)(*((word*)mixSlotA+4098)
                                 + *((word*)mixSlotA-4094))                 >> (mixShiftA+1)) + mixFreqA;
              sseCum = mixWeightA;
              sseTot = mixFreqA;
              d98 = RescaleAccum1_(mixSlotA + 2048, mixWeightSavedA, mixShiftA);
              d99 = RescaleAccum1_(mixSlotA - 2048, (uint)*(mixSlotA-2048), mixShiftA);
              mixShiftLowA = *((word*)mixSlotA+3)<0x400u;
              mixShiftBSel = mixShiftA+mixShiftLowA;
              mixBaseAStride = &mixSlotA[-2*mixIdxA];
              sseSlot3A = (sqword)&mixBaseAStride[2*(int)(mixIdxA^0x100)];
              q31 = sseSlot3A;
              d100 = RescaleAccum1_((void*)sseSlot3A, *(uint*)sseSlot3A, mixShiftBSel);
              sseSlot4A = (sqword)&mixBaseAStride[2*(int)(mixIdxA^0x200)];
              q30 = sseSlot4A;
              d101 = RescaleAccum1_((void*)sseSlot4A, *(uint*)sseSlot4A, mixShiftBSel);
              d102 = RescaleAccum1_(bigSlotA, (uint)*bigSlotA, mixShiftA+mixShiftLowA+1);
            }
            predRescaleDiv = MinContext->SummFreq;
            cumFreqMixA = predRescaleDiv+((mixFreqA>>1)+nStatesPlus1*mixWeightA)/mixFreqA+2;
            cumFreqAcc = cumFreqMixA;
            if( nStatesPlus1<24 ) {
              d103 = 0;
              cumFreqDivA = 0;
LABEL_58:
              // SSE-mix preamble: zero out the per-step predictor accumulators
              // and seed the LABEL_59 escape walk.
              d104 = 171;
              d103Cache = cumFreqDivA;
              predShiftFlags = 0;
              d105 = 0;
              predBinFlags = 171;
              d106 = SseIdx{}
                .bit  <1>    (OrderFall < 3)
                .raw         (1032u * (MinContext->iSuffix == 0))   // 1032 = bit 3 + bit 10, both set together
                .bits <5, 2> (MixCtx2 & 3);
              d106Cache = d106;
              remCandF = nStates+1;
              chainPtr = CtxChain;
              // MixCtxExtra accumulator update: a few bits at fixed positions
              // plus a "sliding edge": bits 13-14 are always set when this
              // branch fires, and a single 1-bit edge moves from bit 12 to
              // bit 15 depending on the (nStatesPlus1 > 40) predicate (the
              // decompilation's +28672 / +28672*pred carry pair).
              MixCtxExtra += SseIdx{}
                .bit <5> (MinContext->NStates > NMasked)
                .bit <7> (nStatesP1Save < nStatesPlus1 + 4)    // was >>24 sign trick
                .bit <12>(!(nStatesPlus1 > 40))                // bit 12 only when predicate is false
                .bits<13, 2>(3)                                // bits 13-14 always set
                .bit <15>(nStatesPlus1 > 40);                  // bit 15 only when predicate is true
              sumFreqF = cumFreqMixA;
              orderCtxSeedSave = OrderCtxSeed;
              goto LABEL_59;
            }
          }
          cumFreqDivA = cumFreqMixA>>1;
          d103 = cumFreqMixA>>1;
          goto LABEL_58;
        }
      }
    }
    // -----------------------------------------------------------------------
    //  Single-state binary coder  (~ ppmd::decode0 / encode0). Reached when
    //  MinContext->NStates == 0 (the implicit else of the if above). Walks a
    //  short SSE chain, optionally takes a deeper BinSse-based sub-stage,
    //  then dispatches to the range coder's binary match/escape decision.
    // -----------------------------------------------------------------------
    currentSymbol = MinContext->oneState().Symbol;
    MixCtx3 = currentSymbol;
    PPMContextWalk(epoch, currentSymbol, &seeIndex, &suffixNStates, &mixCtx, &summFreqPtr, &sparseFlags);
    mixIdxB = mixCtx+(uint)SSE1[suffixNStates];
    mixBaseB = &MixWeight1[0x8000*(qword)(byte)NextBinFreq[seeIndex]];
    q32 = (sqword)&mixBaseB[2*(mixIdxB^0x1000)];
    q31 = (sqword)&mixBaseB[2*(mixIdxB^1)];
    q30 = (sqword)&mixBaseB[2*(mixIdxB^0x2000)];
    q29 = (sqword)&mixBaseB[2*(mixIdxB^0x20)];
    q34 = (sqword)&mixBaseB[2*(mixIdxB^0x200)];
    q35 = (sqword)&mixBaseB[2*(mixIdxB^0x400)];
    mixSlotB = &mixBaseB[2*mixIdxB];
    mixFreqB = *((word*)mixSlotB+2);
    binMixCenter = (word*)mixSlotB;
    q22 = (sqword)(mixSlotB-4);
    q18 = (sqword)(mixSlotB+4);
    MaybeRescale2_(mixSlotB, mixFreqB);
    mixHitsB = *(word*)mixSlotB;
    sseCum = mixHitsB;
    *((word*)mixSlotB+2) = mixFreqB + *((word*)mixSlotB+3);
    sseTot = mixFreqB;
    d52 = mixHitsB;
    d50 = mixFreqB;
    OrderCtxSeed = SseIdx{}
      .bit  <0>    (currentSymbol == d83)
      .bit  <1>    (currentSymbol == d85)
      .bit  <2>    (currentSymbol == d92)
      .bit  <3>    (currentSymbol == d66)
      .bit  <4>    (currentSymbol == Order1Ctx)
      .field<5, 3> (currentSymbol)                              // bits 5-7 of the symbol
      .bit  <8>    (currentSymbol == d76)
      .field<9, 1> (OrderCtxSeed)                               // bit  9     carried
      .field<10,1> ((word)recentSym - (word)currentSymbol)            // bit 10    sign trick (subtraction underflow)
      .field<11,1> ((word)currentSymbol - (word)MatchCtxHi)     // bit 11    sign trick
      .bit  <12>   (sparseFlags)
      .field<13,3> (OrderCtxSeed)                               // bits 13-15 carried
      .bits <16,2> ((mixFreqB < (uint)(56*mixHitsB))
                  + (mixFreqB < (uint)( 6*mixHitsB)));          // bits 16-17 hits/freq ratio band
    sse1SlotB = &Sse1[2*OrderCtxSeed];
    sse1Slot = sse1SlotB;
    sse1CumInB = sseCum;
    sse1ClampB = SseClampMean_(sse1SlotB, mixHitsB, 1-sseCum, 0x40000);
    SseDeltaUpdate_(sse1SlotB, sse1CumInB, 0x40000, 4096, 2);
    cumWeightB = sse1ClampB+sseTot;
    cumFreqB = sse1ClampB+sse1CumInB;
    mixShiftSelB = binMixCenter[3];
    escSymB = MixCtx3;                  // both arms below want this snapshot
    if( mixShiftSelB<=0x20 ) {
      sseTot = cumWeightB;
      sseCum = cumFreqB;
      q35 = q34 = q29 = q30 = q31 = q32 = q18 = q22 = q20 = q17 = (sqword)d27;
      binSseCell = (uint*)&d110;        // dummy sink: deeper sub-stage not taken
    } else {
      // Deeper sub-stage: take the BinSse path and run ~6 more SSE-mix
      // accumulators before joining the range coder dispatch below.
      binSseSlotB = &BinSse[(int)(SseIdx{}
          .bits <0, 2> ((uint)mixIdxB >> 6)                   // mixIdxB bits 6-7 -> result bits 0-1
          .bit  <2>    (SymLastCtx2[MixCtx3] == SymCount)
          .bit  <3>    ((uint)mixIdxB & 0x200)                // mixIdxB bit 9   -> result bit 3
          .bits <4, 2> (sparseFlags)                          // sparseFlags is 0..3 (2 bits at 4-5)
          .bit  <6>    (RunLength > -9)
          .bits <7, 8> ((byte)SSE1QTable[seeIndex]))];        // SSE1QTable byte at bits 7-14

      binSseVal = *binSseSlotB;
      binSseCell = (uint*)binSseSlotB;
      int mixSseMeanB = (binSseVal>>(mixShiftSelB<0x230))+cumFreqB;
      int mixSseFreqB = (0x3100u>>(mixShiftSelB<0x230))+cumWeightB;
      sseCum = mixSseMeanB;
      sseTot = mixSseFreqB;
      *binSseSlotB = binSseVal-((binSseVal+2)>>3);
      mixShiftB = mixShiftSelB<0x220;
      d48 = RescaleAccum2_((void*)q22, mixShiftB);
      d49 = RescaleAccum2_((void*)q18, mixShiftB);
      // blend the two neighbour cells (binMixCenter ± 0x10000) into the
      // (cumFreqB, cumWeightB) accumulators.
      q20 = (sqword)(binMixCenter-0x10000);
      q17 = (sqword)(binMixCenter+0x10000);
      cumFreqB   = ((binMixCenter[0x10000] + *(binMixCenter-0x10000))    >> (mixShiftB+1)) + mixSseMeanB;
      cumWeightB = ((uint)(binMixCenter[65538] + *(binMixCenter-65534))  >> (mixShiftB+1)) + mixSseFreqB;
      sseCum = cumFreqB;
      sseTot = cumWeightB;
      d46 = RescaleAccum2_(binMixCenter+0x10000, mixShiftB);
      d47 = RescaleAccum2_(binMixCenter-0x10000, mixShiftB);
      mixShiftC = (binMixCenter[3]<0x398u) + mixShiftB;
      d99  = RescaleAccum2_((void*)q32, mixShiftC);
      d100 = RescaleAccum2_((void*)q31, mixShiftC);
      d101 = RescaleAccum2_((void*)q30, mixShiftC);
      d102 = RescaleAccum2_((void*)q29, mixShiftC);
      d105 = RescaleAccum2_((void*)q34, mixShiftC);
      d104 = RescaleAccum2_((void*)q35, mixShiftC);
    }
    sseCum = 60416LL*cumFreqB/cumWeightB;
    sseTot = 60416;
    d54 = sseCum;
    d53 = 60416;
    sseMatchSlotA = &SseMatch[(int)(SseIdx{}
        .bits <1, 8>  (escSymB)                          // bits 1-8: candidate sym
        .bits <9, 8>  (recentSym)                              // bits 9-16: recent matched sym (recentSym)
        .bit  <17>    (MixCtx)                           // MixCtx is 0/1
        .bit  <18>    ((uint)matchPosAge < 0x78)
        .bit  <19>    (escSymB == FoundSymbol)
        .bit  <20>    (MixScale < (uint)d80))];
    sseMatchSlot = sseMatchSlotA;
    // SSE-match stage: probe with sseCum first; if in-band, recompute with the
    // boosted 60416/sumWeight scale (preserved verbatim from the original).
    matchCumInA = sseCum;
    {
      sqword probeMean = (sqword)sseCum * (sqword)*sseMatchSlotA / sseMatchSlotA[1];
      sseMatchClampA = 1 - sseCum;
      if (probeMean >= 1 - sseCum) {
        sseMatchClampA = 0x40000;
        if (probeMean < 0x40000)
          sseMatchClampA = (int)(60416LL*cumFreqB/cumWeightB) * (sqword)*sseMatchSlotA / sseMatchSlotA[1];
      }
    }
    SseDeltaUpdate_(sseMatchSlotA, matchCumInA, 0x80000, 0x2000, 1120);
    sseTot += sseMatchClampA;
    d56 = sseTot;
    sseSum2A = sseMatchClampA+matchCumInA;
    sseCum = sseSum2A;
    sse2IdxA = SseIdx{}
      .bit  <0>    (escSymB == d84)
      .bit  <1>    (escSymB == d86)                              // overlaid with SSE0 byte below
      .bit  <2>    (escSymB == d87)
      .bit  <3>    (escSymB == FoundSymbol)
      .bit  <4>    (escSymB == PrevSymbol)
      .bits <5, 2> (((uint)matchPosAge < 0xA800)
                  + ((uint)matchPosAge < 0x600)
                  + ((uint)matchPosAge < 0xD))                          // sum of 3 matchPosAge thresholds (0..3) at bits 5-6
      .bit  <7>    ((uint)matchEpoch2 < 0x29)
      .bits <1, 8> (SSE0[escSymB])                    // SSE0 byte at bits 1-8 (overlaps boolean bits)
      .field<11,1> (OrderCtxSeed)
      .field<12,1> ((word)matchHashSy - (word)escSymB)                  // sign-trick bit 12 of word subtraction
      .bit  <13>   (17*sseSum2A < (uint)sseTot)
      .raw         (SseSeed);                                    // pre-positioned multi-bit accumulator
    sse2SlotA = &Sse2[2*sse2IdxA];
    sse2Slot = sse2SlotA;
    sse2CumInA = sseSum2A;
    sse2ClampA = SseClampMean_(sse2SlotA, sseTot-sseSum2A, sseSum2A-sseTot+1, 0x40000);
    totFreqA = sse2ClampA+sseTot;
    sseTot += sse2ClampA;
    SseMixUpdate_(sse2SlotA, 2*sseSum2A, 1);
    d55 = totFreqA;
    {
      // Scope-locals so the goto-into-LABEL_59 path doesn't trip
      // "jump bypasses initialization".
      int  sse2HistByte = sse2Base[((word)escSymB-(word)RSContext)&0x1FF];
      uint sse2CounterA = *(uint*)(sse2Base+512);
      sse3SlotA = &Sse3[2 * (int)(SseIdx{}
        .bit  <0>    (SymLastCtx2[escSymB]==SymCount)
        .bit  <1>    (escSymB == (byte)SseState3[sseState3Hash])
        .bit  <2>    ((uint)(HeapNull + *(uint*)(summFreqPtr+2) - pText) >= 0xFFFFFD20)
        .bits <3, 2> ((sse2CounterA < 384*sse2HistByte)
                    + (sse2CounterA <  58*sse2HistByte)
                    + (sse2CounterA <  22*sse2HistByte))    // 0..3 at bits 3-4 (mirrors region F)
        .field<8, 3> (sse2IdxA)                             // carried bits 8-10 of sse2IdxA
        .bit  <11>   ((uint)matchPosAge < 0x2C00)
        .raw         (MixCtxExtra))];                       // pre-positioned multi-bit accumulator
    }
    sse3Slot = sse3SlotA;
    cumFreq = sseCum;
    sse3ClampA = SseClampMean_(sse3SlotA, totFreqA-sse2CumInA, sseCum-sseTot+1, 0x80000);
    totFreq = sse3ClampA+sseTot;
    sseTot += sse3ClampA;
    SseMixUpdate_(sse3SlotA, sse2CumInA, 2);

    subRange = rc.getSubRange(cumFreq, totFreq);
    if( f_DEC ? !rc.IsDecodeMatched(subRange) : (inputByte != MinContext->oneState().Symbol) ) {
      // Snapshot the single-state context before MinContext gets reassigned
      // to MaxContext below; both the freq*totFreq product and the line-745
      // probability calc need the OLD MinContext.
      oneStateFreqCachedF = MinContext->oneState().Freq;
      if( f_DEC ) rc.DecodeNotMatched(subRange); else rc.encodeEscape(subRange);
      SymMask[MinContext->oneState().Symbol] = SymCount;
      SparseBitmapA[SparseIdxA] &= ~SparseBit;
      q9 = 0;
      SparseBitmapB[SparseIdxB] &= ~SparseBit;
      MinContext = MaxContext;
      entryNStates = MinContext->NStates;
      MixCtx = 0;
      result = (int)(16*(oneStateFreqCachedF*cumFreq+cumFreq-oneStateFreqCachedF*totFreq))
             / (int)(totFreq + totFreq*oneStateFreqCachedF);
      EscIndexSeed = result;
      // ---------------------------------------------------------------------
      //  Escape walk (~ ppmd RealEncode's "while (!FoundState)" loop): keep
      //  walking the suffix chain until a context with NStates != entryNStates
      //  is reached, then drop into the multi-state escape body below.
      // ---------------------------------------------------------------------
      do {
LABEL_128:
        uint walkSuffix = MinContext->iSuffix;
        if( !walkSuffix )
          return result;
        --OrderFall;
        MinContext = (PPM_CONTEXT*)Indx2Ptr(walkSuffix);
        walkNStates = MinContext->NStates;
        MaxContext = MinContext;
        if( walkNStates ) {
          result = MinContext->Flags&0xF;
          if( !MinContext->getStates()[result].Freq )
          result = BinEscFreq((byte*)MinContext);
        }
        walkDelta = walkNStates-entryNStates;
      } while( !walkDelta );
      descendNStates = MinContext->NStates;
      ofallSavedE = OrderFall;
      freqDeltaE = descendNStates-entryNStates;
      remCandF = walkDelta;
      descendNStatesP1C = descendNStates+1;
      descendNStatesP1E = descendNStates+1;
      remStatesE = freqDeltaE;
      predShiftFlags = 0x8000;
      descendFlags = 0;
      freqSumE = 0;
      chainEndE = CtxChain;
      chainEndF = CtxChain;
      firstStateE = &MinContext->getStates()[MinContext->Flags&0xF];
      epoch = SymCount;
      escSymbol = firstStateE->Symbol;
      MixCtx3 = escSymbol;
      if( SymCount==SymMask[escSymbol] ) {
        d105 = 0x8000;
      } else {
        descendFlags = 1;
        chainEndE = &CtxChain_1;
        CtxChain[0] = (sqword)firstStateE;
        SymMask[escSymbol] = SymCount;
        chainEndF = &CtxChain_1;
        freqSumE = firstStateE->Freq;
        predShiftFlags = 0;
        remStatesE = freqDeltaE-1;
        d105 = 0;
      }
      walkStateIterE = MinContext->getStates() - 1;
      if( remStatesE ) {
        sortRangeE = chainEndE;
        walkFreqSumE = freqSumE;
        while( 1 ) {
          do {
            walkStateIterE += 1;
            walkSymE = walkStateIterE->Symbol;
          } while( epoch==SymMask[walkSymE] );
          SymMask[walkSymE] = epoch;
          *chainEndE++ = (sqword)walkStateIterE;
          chainEndF = chainEndE;
          walkFreqSumE += walkStateIterE->Freq;
          if( walkSymE==FoundSymbol )
            break;
          if( epoch==MatchPosBySym[walkSymE]||epoch==SymLastCtx2[walkSymE] ) {
            sortLimitC = sortRangeE;
            sortPriorityC = 4*(epoch==MatchPosBySym[walkSymE])+12;
            goto LABEL_292;
          }
LABEL_296:
          if( !--remStatesE ) {
            freqSumE = walkFreqSumE;
            goto LABEL_298;
          }
        }
        sortPriorityC = 22;
        sortLimitC = &CtxChain[(byte)descendFlags&((b25&7)==0)];
LABEL_292:
        BubbleSortChain_(chainEndE, sortLimitC, sortPriorityC);
        ++sortRangeE;
        goto LABEL_296;
      }
LABEL_298:
      // ---------------------------------------------------------------------
      //  Multi-state escape mirror: same shape as the initial multi-state
      //  block above, but uses CtxChain[] populated by the walk for which
      //  symbols to mix into the escape distribution.
      // ---------------------------------------------------------------------
      q29 = q30 = q31 = q32 = q33 = (sqword)d27;
      if( descendNStates==255 ) {
        escCandidate = -1;
        EscapeSymbol = -1;
        q34 = (sqword)d27;
        sumFreqDivC = 1;
      } else {
        suffixCtxC = (PPM_CONTEXT*)Indx2Ptr(MinContext->iSuffix);
        suffixCtxC = WalkEscapeChain_(suffixCtxC, MinContext, escSymbol, escCandidate);
        minCtxFlagsC = MinContext->Flags;
        if( 16*freqDeltaE<=freqSumE||(MinContext->Flags&0x40)!=0 ) {
          CtxChainEnd = (sqword)chainEndF;
          sumFreqCacheC = MinContext->SummFreq;
      } else {
          FillFreqMap_(suffixCtxC);
          int  walkFreqSumC   = 0;
          int  sumFreqC       = MinContext->SummFreq;
          int  mixFiveC       = 5*descendNStates+5;
          uint mixWeightCfull = (5*((uint)(2*mixFiveC-sumFreqC)>>31)+8)*(suffixCtxC->NStates+1) + suffixCtxC->SummFreq;
          int  sumFreqW0C     = (word)sumFreqC;
          do {
            STATE* st = (STATE*)*--chainEndE;
            FreqMixStep_(st, b39[st->Symbol], mixWeightCfull,
                         2*mixFiveC, sumFreqC, sumFreqW0C, MinContext);
            walkFreqSumC += st->Freq;
          } while( chainEndE!=CtxChain );
          freqSumE = walkFreqSumC;
          minCtxFlagsC = MinContext->Flags;
          sumFreqCacheC = sumFreqW0C;
          CtxChainEnd = (sqword)chainEndE;
        }
        sx_p = (PPM_CONTEXT*)Indx2Ptr(MinContext->iSuffix);
        sxNStatesC = sx_p->NStates;
        descendNStatesP1C = sxNStatesC+1;
        maskFlagPrevC = epoch!=SymMask[PrevSymbol];
        // mixIdxC: composite index for the escape mirror's mix table.
        // Same construction as mixIdxA; the ">> 26 & 0xFFFFFFE0" term is the
        // same sign-bit-extract idiom (1-bit predicate at position 5).
        mixIdxC = SseIdx{}
          .bits <0, 2> (MixCtx2)                                       // low 2 bits of mix counter
          .bit  <2>    (descendNStatesP1E*freqSumE > sumFreqCacheC*freqDeltaE) // freq-sum cross-product comparison
          .bit  <3>    (maskFlagPrevC                                  // either prev sym OR sx-rank-0 sym
                       | (epoch != SymMask[sx_p->getStates()[sx_p->Flags&0xF].Symbol]))
          .bit  <4>    (freqDeltaE >= 2*sxNStatesC - 2*descendNStates) // did NStates shrink a lot?
          .bit  <5>    (sumFreqCacheC > 16*(uint)MinContext->NStates)  // was sign-trick: NStates vs SummFreq
          .field<6, 2> (minCtxFlagsC);                                 // Flags bits 6-7
        sseQTableIdxC = SSE0QTable[descendNStatesP1E-2];
        mixOffsetC = (sseQTableIdxC<<11)+8*mixIdxC;
        mixSlotC = (char*)d29+mixOffsetC;
        mixWeightC      = *(int*)((char*)d29+mixOffsetC);
        mixFreqC        = *(word*)((char*)&w12+mixOffsetC);
        q34             = (sqword)d29+mixOffsetC;
        sseCum             = mixWeightC;
        mixFreqCacheC   = mixFreqC;
        sseTot             = mixFreqC;
        mixWeightDeltaC = RescaleAccum1_((void*)((sqword)d29+mixOffsetC), (uint)mixWeightC, 0);
        if( mixWeightDeltaC>0x78 ) {
          // d29[]/MixWeight2[] index in 2-int-stride units.
          bigSlotC = &MixWeight2[2048 * sseQTableIdxC + 2 * (int)(SseIdx{}
              .field<0, 2> ((byte)mixIdxC)                                       // mixIdxC bits 0-1, in place
              .bit  <2>    (ofallSavedE < 10)                                    // OrderFall band
              .bit  <3>    (MinContext->NStates + 2*sxNStatesC + 2 > NMasked)  // parent context dense
              .field<4, 4> ((byte)mixIdxC)                                       // mixIdxC bits 4-7, in place
              .bit  <8>    (maskFlagPrevC)
              .bit  <9>    (epoch != SymMask[escCandidate]))];
          q29 = (sqword)bigSlotC;
          predLoBeyondC = mixWeightDeltaC<0x100;
          shiftSelC = predLoBeyondC+1;
          q33 = (sqword)(mixSlotC+2048);
          q32 = (sqword)(mixSlotC-2048);
          // blend the two neighbour cells (mixSlotC ± 2048) into the running
          // (mixWeightC, mixFreqCacheC) accumulators.
          mixWeightC    += (*((uint*)mixSlotC+512) + *((uint*)mixSlotC-512))   >> shiftSelC;
          mixFreqCacheC += (uint)(*((word*)mixSlotC+1026)
                                + *((word*)mixSlotC-1022))                    >> shiftSelC;
          sseCum = mixWeightC;
          sseTot = mixFreqCacheC;
          d98 = RescaleAccum1_((void*)(mixSlotC+2048), *((uint*)mixSlotC+512), shiftSelC);
          d99 = RescaleAccum1_((void*)(mixSlotC-2048), *((uint*)mixSlotC-512), shiftSelC);
          d102 = RescaleAccum1_(bigSlotC, (uint)*bigSlotC, *((word*)mixSlotC+3)<0x200u);
          predShiftIncC = (*((word*)mixSlotC+3)<0x400u)+predLoBeyondC+1;
          mixStrideC = &mixSlotC[-8*mixIdxC];
          sse3SlotC = (sqword)&mixStrideC[8*(int)(mixIdxC^2)];
          q31 = sse3SlotC;
          d100 = RescaleAccum1_((void*)sse3SlotC, *(uint*)sse3SlotC, predShiftIncC);
          sse4SlotC = (sqword)&mixStrideC[8*(int)(mixIdxC^8)];
          q30 = sse4SlotC;
          d101 = RescaleAccum1_((void*)sse4SlotC, *(uint*)sse4SlotC, predShiftIncC);
        }
        sumFreqDivC = ((mixFreqCacheC>>1)+descendNStatesP1E*mixWeightC)/mixFreqCacheC+2;
        if( descendNStatesP1E<24 ) {
          d103Cache = 0;
          goto LABEL_335;
        }
      }
      d103Cache = (int)(sumFreqDivC+MinContext->SummFreq)>>1;
LABEL_335:
      // Per-state walk through CtxChain[] inside the escape:  each iteration
      // is the body of ppmd's "FoundState = MinContext->encode2(c)" search.
      d103 = d103Cache;
      sumFreqF = freqSumE+sumFreqDivC;
      cumFreqAcc = sumFreqF;
      RunLength = d16;
      predRescaleDiv = freqSumE+descendNStates+1;
      predBinFlags = 0;
      chainPtr = CtxChain;
      d104 = 0;
      CtxChainEnd = (sqword)CtxChain;
      {
        uint orderShift15C = (ofallSavedE>1)<<15;
        orderCtxSeedSave = orderShift15C + (OrderCtxSeed & 0x7FFF);
        OrderCtxSeed    = orderShift15C + (OrderCtxSeed & 0xFFFF7FFF);
        SseSeed = ((ofallSavedE>3)<<15) + orderShift15C + (SseSeed & 0x4600);
      }
      // d106Cache: starting bitfield for the escape-mirror SSE seed.
      d106Cache = SseIdx{}
        .bit  <1>    (ofallSavedE < 3 || ofallSavedE+23 < OrderFall0)
        .raw         (1032u * (MinContext->iSuffix == 0))   // 1032 = bit 3 + bit 10, both set together
        .bits <5, 2> (MixCtx2 & 3);
      d106 = d106Cache;
      // MixCtxExtra: outer-loop accumulator seeding the SSE-mix tables for
      // the upcoming per-candidate iterations. Bits 12-16 form a 5-bit
      // weighted-predicate score (weights 1/1/2/7/7/1, max sum 19), packed
      // with carry into the [12, 17) window.
      MixCtxExtra = SseIdx{}
        .bit  <5>    (MinContext->NStates + 28 > 2*NMasked)              // NStates well above NMasked
        .bit  <7>    (descendNStatesP1C < descendNStatesP1E + 3)         // was >>24 sign trick
        .bits <12, 5>((OrderFall0          > 7)                          // weight 1
                    + (OrderFall0          > 2)                          // weight 1
                    + 2 * (ofallSavedE     > 2)                          // weight 2 (was .bit<13>)
                    + 7 * (descendNStatesP1E > 74)                       // weight 7 (was >>31 sign trick)
                    + 7 * (descendNStatesP1E > 2)                        // weight 7 (was >>31 sign trick)
                    + (ofallSavedE         > 16));                       // weight 1
      while( 1 ) {
        // -------------------------------------------------------------------
        //  One candidate symbol per iteration. The original LABEL_59 is the
        //  entry from the NStates == 0 fall-through (binary case) into this
        //  generic per-candidate range-code dispatch.
        // -------------------------------------------------------------------
        if( f_DEC ) rc.DecodeNormalize(inFile); else rc.EncodeNormalize(outFile);
LABEL_59:
        FoundState = (STATE*)*chainPtr;
        preCommitMinCtx = MinContext;
        CtxChainEnd = (sqword)(chainPtr+1);
        q18 = q22 = q20 = q17 = (sqword)d27;
        uint candSymbol = FoundState->Symbol;
        sqword candProbBF = ((FoundState->Freq<<8)-predBinFlags)/sumFreqF;
        SparseBit = 1<<FoundState->Symbol;
        int sseEntryC2F = candProbBF;
        sqword mixSseSizeF = (uint)(byte)SymType[candProbBF]+1;
        SparseIdxA = ((candSymbol+SparseHashA)>>5)+0x2000;
        SparseIdxB = predShiftFlags+((candSymbol+SparseHashB)>>5);
        bool tagSymLastCtx2F = epoch==SymLastCtx2[candSymbol];
        int sparseHitsF =
              ((SparseBit & SparseBitmapA[((candSymbol+SparseHashA) >> 5) + 0x2000]) != 0)
          + 2*((SparseBit & SparseBitmapB[predShiftFlags + ((candSymbol+SparseHashB) >> 5)]) != 0);
        predWeightB = (uint*)&q38;      // dummy sink: PredWeight stage not taken
        predWeightA = (uint*)&q38;
          matchCtxHiSave = MatchCtxHi;
        int matchTblHitF = MatchPosTable[256*MatchCtxHi+candSymbol];
        if( (uint)(SymEpoch-matchTblHitF)>=0x20000 ) {
          matchEpoch2 = 0x20000;
          matchPosAge = 0x20000;
          matchHashSy = 0x20000;
      } else {
          matchHashSy = (byte)MatchPosHash[(matchTblHitF+2)&0x1FFFF];
          matchPosAge = SymEpoch-matchTblHitF;
          matchEpoch2 = SymEpoch-MatchPosTable[256*candSymbol+matchHashSy];
        }
        // seeIdxF: composite index for the per-candidate mix table d27[].
        // Outer OR with d106Cache (the prior-section accumulator) preserves
        // the bit-merge semantics where d106Cache and the inner sum may
        // share bit positions. The inner sum itself uses +-with-carry — the
        // SSE0[sym] byte can overlap the boolean bits 0..7.
        sqword seeIdxF = d106Cache | (uint)(SseIdx{}
          .bit  <0>    (tagSymLastCtx2F)                  // SymLastCtx2 hit on candidate
          .bit  <2>    (epoch == MatchPosBySym[candSymbol])// MatchPosBySym hit on candidate
          .bit  <3>    (candSymbol == escCandidate)       // candidate is the escape candidate
          .bit  <4>    (candSymbol == FoundSymbol)        // candidate is the previous FoundSymbol
          .bits <0, 8> (SSE0[candSymbol])      // SSE0[sym] sym-type byte at bits 0-7 (may overlap above)
          .bit  <8>    (epoch == SymLastCtx[candSymbol])  // SymLastCtx hit on this candidate
          .bit  <9>    (candSymbol == d72                                              // strong position-bias hint
                       || *(uint*)(sse2Base+512) < (uint)(sse2Base[((word)candSymbol-(word)RSContext)&0x1FF]<<7))
          .bit  <10>   (candSymbol == escSymbol)          // candidate is the entry escape symbol
          .bit  <11>   (sumFreqF      < d103Cache)        // freq summary below threshold
          .bit  <12>   ((uint)matchEpoch2 < 0x220));      // recent match
        binMixSlotF = &d27[0x4000*mixSseSizeF+2*seeIdxF];
        int freq0F = (word)MixBound2[0x8000*mixSseSizeF+4*seeIdxF];
        binMixCenter = (word*)binMixSlotF;
        if (freq0F > 0x8000) matchCtxHiSave = MatchCtxHi;     // preserved side-effect: original
                                                 // reloads matchCtxHiSave from MatchCtxHi when
                                                 // it rescales
        MaybeRescale2_(binMixSlotF, freq0F);
        int hitsF = *(word*)binMixSlotF;
        sseCum = hitsF;
        *((word*)binMixSlotF+2) = freq0F + *((word*)binMixSlotF+3);
        sseTot = freq0F;
        d52 = hitsF;
        d50 = freq0F;
        // OrderCtxSeed composite for the per-candidate Sse1 table lookup.
        OrderCtxSeed = SseIdx{}
          .bit  <0>    (candSymbol == d83)              // matches b31 hint
          .bit  <1>    (candSymbol == d85)              // matches b29 hint
          .bit  <2>    (candSymbol == d92)              // matches BijectMap hint
          .bit  <3>    (candSymbol == d66)              // matches MatchPosHash hint
          .bit  <4>    (candSymbol == Order1Ctx)        // matches order-1 context
          .field<5, 3> (candSymbol)                     // high 3 bits of the candidate sym
          .bit  <8>    (candSymbol == d76)              // matches sparse-submodel hint
          .field<9, 1> (orderCtxSeedSave)               // carried from outer
          .field<10,1> ((word)recentSym - (word)candSymbol)   // delta-from-recentSym sign trick
          .field<11,1> ((word)candSymbol - matchCtxHiSave) // delta-from-prev sign trick
          .bit  <12>   (sparseHitsF)                    // sparse-submodel hint
          .field<13,3> (orderCtxSeedSave)               // carried from outer
          .bits <16,2> ((freq0F < (uint)(56*hitsF))
                      + (freq0F < (uint)( 6*hitsF)));   // hits/freq ratio band
        sse1SlotF = &Sse1[2*OrderCtxSeed];
        sse1Slot = sse1SlotF;
        int sse1CumIn = sseCum;
        int sse1Clamp = SseClampMean_(sse1SlotF, hitsF, 1-sseCum, 0x40000);
        SseDeltaUpdate_(sse1SlotF, sse1CumIn, 0x40000, 4096, 2);
        int mixCumWeightF = sse1Clamp+sseTot;
        int mixCumFreqF   = sse1Clamp+sse1CumIn;
        uint centerWeightF = binMixCenter[3];
        if( centerWeightF<=8 ) {
          sseTot = mixCumWeightF;
          sseCum = mixCumFreqF;
      } else {
          int* predWBase = &PredWeight[512*(qword)(byte)SEEQTable[candProbBF]+2*(uint)(sparseHitsF<<6)];
          predWAF = &predWBase[2*(seeIdxF&0x1F)];
          int  predWAVal = predWAF[1];
          predWeightA = (uint*)predWAF;
          predWBF = &predWBase[2*(((uint)seeIdxF>>4)&0x1F)+64];
          predWeightB = (uint*)predWBF;
          char predBoostShiftF = centerWeightF<0x150;
          int  predWBVal = predWBF[1];
          uint predScaleAF = predWBVal+predWAVal;
          uint predWAOldA = *predWBF;
          uint predScaledAF = (uint)(predWAVal*(sseEntryC2F+2))>>8;
          uint predScaledBF = (uint)(predWBVal*(sseEntryC2F+2))>>8;
          sqword predBoostF = (predScaleAF >= 0xC000) ? 24 : ((predScaleAF >> 11) & 0xFFFFFFFE);
          uint predWBOldA = *predWAF;
          uint predTotEarlyF = (predScaledAF+predScaledBF >= 0x6000u) ? 24576u : (predScaledAF+predScaledBF);
          int predConstAF = (byte)b41[predBoostF];
          int predConstBF = (byte)b41[predBoostF+1];
          uint predWPostF = ((predConstAF*predTotEarlyF+predConstBF*(predWAOldA+*predWAF))>>(predBoostShiftF+7))+mixCumFreqF;
          char predShiftF = predBoostShiftF + (centerWeightF<0x48) + 3;
          uint predDenIncF = ((uint)(192*(predConstAF+predConstBF))>>predBoostShiftF)+mixCumWeightF;
          d112 = 0x3000u>>predShiftF;
          char predDenShiftF = predBoostShiftF+4;
          d113 = 0x3000u>>predDenShiftF;
          *predWAF = predWBOldA-(predWBOldA>>predShiftF);
          predWAF[1] -= (predScaledAF+7)>>predDenShiftF;
          *predWBF = predWAOldA-(predWAOldA>>predShiftF);
          predWBF[1] -= (predScaledBF+7)>>predDenShiftF;
          // blend the two neighbour cells (binMixCenter ± 0x8000) into
          // (mixCumFreqF, mixCumWeightF) for the PredWeight stage output.
          q17 = (sqword)(binMixCenter+0x8000);
          q20 = (sqword)(binMixCenter-0x8000);
          mixCumFreqF   = ((*(binMixCenter-0x8000) + binMixCenter[0x8000])     >> 3) + predWPostF;
          mixCumWeightF = ((uint)(binMixCenter[32770] + *(binMixCenter-32766)) >> 3) + predDenIncF;
          sseCum = mixCumFreqF;
          sseTot = mixCumWeightF;
          {
            char predDoExpandF = (centerWeightF<0x30)+1;
            d46 = RescaleAccum2_(binMixCenter + 0x8000, predDoExpandF);
            d47 = RescaleAccum2_(binMixCenter - 0x8000, predDoExpandF);
          }
          uint predExpA = binMixCenter[3];
          if( predExpA>0x48 ) {
            q22 = (sqword)(binMixCenter+0x10000);
            q18 = (sqword)(binMixCenter-0x10000);
            char predExpShiftF = (predExpA<0x1E0)+(predExpA<0x3D0)+1;
            d48 = RescaleAccum2_(binMixCenter + 0x10000, predExpShiftF);
            d49 = RescaleAccum2_(binMixCenter - 0x10000, predExpShiftF);
          }
        }
        int sseMatchBoostedF = 60416LL*mixCumFreqF/mixCumWeightF;
        sseCum = sseMatchBoostedF;
        sseTot = 60416;
        d54 = sseMatchBoostedF;
        d53 = 60416;
        sseMatchSlotF = &SseMatch[(int)(SseIdx{}
            .bits <1, 8>  (candSymbol)                       // bits 1-8: candidate sym
            .bits <9, 8>  (recentSym)                              // bits 9-16: recent matched sym (recentSym)
            .bit  <17>    (MixCtx)                           // MixCtx is 0/1
            .bit  <18>    ((uint)matchPosAge < 0x78)
            .bit  <19>    (candSymbol == FoundSymbol)
            .bit  <20>    (MixScale < (uint)d80))];
        sseMatchSlot = sseMatchSlotF;
        int matchCumInF = sseCum;
        int sseMatchClampF = SseClampMean_(sseMatchSlotF, sseMatchBoostedF, 1-sseCum, 0x40000);
        SseDeltaUpdate_(sseMatchSlotF, matchCumInF, 0x80000, 0x2000, 1120);
        sseTot += sseMatchClampF;
        int cumWeightF = sseMatchClampF+matchCumInF;
        sseCum = cumWeightF;
        d56 = sseTot;
        sqword sse2IdxF = SseIdx{}
          .bit  <0>    (candSymbol == d84)
          .bit  <1>    (candSymbol == d86)                          // overlaid with SSE0 byte below
          .bit  <2>    (candSymbol == d87)
          .bit  <3>    (candSymbol == FoundSymbol)
          .bit  <4>    (candSymbol == PrevSymbol)
          .bits <5, 2> (((uint)matchPosAge < 0xA800)
                      + ((uint)matchPosAge < 0x600)
                      + ((uint)matchPosAge < 0xD))                         // sum of 3 matchPosAge thresholds (0..3) at bits 5-6
          .bit  <7>    ((uint)matchEpoch2 < 0x29)
          .bits <1, 8> (SSE0[candSymbol])                  // SSE0 byte at bits 1-8 (overlaps boolean bits)
          .field<11,1> (OrderCtxSeed)
          .field<12,1> ((word)matchHashSy - (word)candSymbol)              // sign-trick bit 12 of word subtraction
          .bit  <13>   (17*cumWeightF < (uint)sseTot)
          .raw         (SseSeed);                                   // pre-positioned multi-bit accumulator
        sse2SlotF = &Sse2[2*sse2IdxF];
        sse2Slot = sse2SlotF;
        int sse2CumInF  = cumWeightF;
        int sse2ClampF  = SseClampMean_(sse2SlotF, sseTot-cumWeightF, cumWeightF-sseTot+1, 0x40000);
        int sse2CumTotF = sse2ClampF+sseTot;
        sseTot += sse2ClampF;
        SseMixUpdate_(sse2SlotF, 2*cumWeightF, 1);
        int  sse2HistByteF = sse2Base[((word)candSymbol-(word)RSContext)&0x1FF];
        uint sse2Counter   = *(uint*)(sse2Base+512);
        d55 = sse2CumTotF;
        sse3SlotF = &Sse3[2 * (int)(SseIdx{}
          .bit  <0>    (tagSymLastCtx2F)
          .bit  <1>    (candSymbol == (byte)SseState3[sseState3Hash])
          .bit  <2>    ((uint)(HeapNull + FoundState->iSuccessor - pText + 736) < 0x2E0)
          .bits <3, 2> ((sse2Counter < 384*sse2HistByteF)
                      + (sse2Counter <  58*sse2HistByteF)
                      + (sse2Counter <  22*sse2HistByteF))     // 0..3 at bits 3-4
          .field<8, 3> (sse2IdxF)                              // carried bits 8-10 of sse2IdxF
          .bit  <11>   ((uint)matchPosAge < 0x2C00)
          .raw         (MixCtxExtra))];                        // pre-positioned multi-bit accumulator
        sse3Slot = sse3SlotF;
        cumFreqC = sseCum;
        int sse3ClampF = SseClampMean_(sse3SlotF, sse2CumTotF-sse2CumInF, sseCum-sseTot+1, 0x80000);
        totFreqC = sse3ClampF+sseTot;
        sseTot += sse3ClampF;
        SseMixUpdate_(sse3SlotF, sse2CumInF, 2);
        subRangeC = rc.getSubRange(cumFreqC, totFreqC);
        if( f_DEC ? !rc.IsDecodeMatched(subRangeC) : (inputByte != candSymbol) ) {
          priorFoundStateF = q9;
          cumFreqAcc -= FoundState->Freq;
          if( f_DEC ) rc.DecodeNotMatched(subRangeC); else rc.encodeEscape(subRangeC);
          SparseBitmapA[SparseIdxA] &= ~SparseBit;
          SparseBitmapB[SparseIdxB] &= ~SparseBit;
          if( priorFoundStateF ) {
            MinContext = MaxContext;
            q9 = 0;
            MixCtx = 0;
          } else if( FoundState<=MinContext->getStates() ) {
            MinContext = MaxContext;
        } else {
            MinContext = MaxContext;
            d105 = 0x8000;
          }
        } else {
          if( !f_DEC ) rc.encodeSymbol(subRangeC);
          // commit two PredWeight pairs (d112, d113) at the A and B cells
          predWeightA[0] += d112;
          predWeightA[1] += d113;
          predWeightB[0] += d112;
          predWeightB[1] += d113;
          flagsCtxFC = MinContext->Flags;
          freqBoostFC = (matchPosAge>0x4800) + (matchPosAge>0x380) + (matchPosAge>0x80)
                      + ((flagsCtxFC&0x40)==0 || matchPosAge>0xE00) + 4;
          MinContext->Flags = flagsCtxFC&0xF0;
          MinContext->SummFreq += freqBoostFC;
          FoundState->Freq += freqBoostFC;
          STATE* statesBaseFC = MinContext->getStates();
          if( FoundState==statesBaseFC ) {
            MinContext = MaxContext;
            if( (sqword)MaxContext==RootContext )
              MixCtx = totFreqC<2*cumFreqC;
      } else {
            // Bubble the matched STATE up toward index 0 (cf. ppmd update1).
            STATE saved = *FoundState;
            do {
              *FoundState = *(FoundState-1);
              FoundState -= 1;
            } while( FoundState>statesBaseFC );
            *FoundState = saved;
            MinContext = MaxContext;
          }
          q9 = (sqword)FoundState;
          if( FoundState->Freq > 244 ) {
            RescaleCtx((byte*)preCommitMinCtx);
            FoundState = (STATE*)q9;
          }
          if( FoundState )
            goto LABEL_250;
        }
        if( !--remCandF ) {
          uint rewindMult = predRescaleDiv / (MinContext->NStates + 1);
          RewindPredictor_(q34, *(word*)(q34+6), rewindMult);
          RewindPredictor_(q33, d98,             rewindMult);
          RewindPredictor_(q32, d99,             rewindMult);
          RewindPredictor_(q31, d100,            rewindMult);
          RewindPredictor_(q30, d101,            rewindMult);
          RewindPredictor_(q29, d102,            rewindMult);
          entryNStates = MinContext->NStates;
          goto LABEL_128;
        }
        predShiftFlags = d105;
        predBinFlags = d104;
        escSymbol = MixCtx3;
        epoch = SymCount;
        escCandidate = EscapeSymbol;
        chainPtr = (sqword*)CtxChainEnd;
        orderCtxSeedSave = OrderCtxSeed;
        sumFreqF = cumFreqAcc;
        d103Cache = d103;
        d106Cache = d106;
      }
    }
    if( !f_DEC ) rc.encodeSymbol(subRange);
    FoundState = &MinContext->oneState();
    oneStateFreqF = MinContext->oneState().Freq;
    q9 = (sqword)&MinContext->oneState();
    MixCtx = 1;
    MinContext->oneState().Freq = (oneStateFreqF-127<0)
                                + oneStateFreqF
                                + (oneStateFreqF==1 && totFreq < 4*cumFreq);
    // commit the per-step predictor deltas (no freq0 rewind in this path)
    binSseCell[0] += 1568;
    *(uint*)q32 += d99;
    *(uint*)q31 += d100;
    *(uint*)q30 += d101;
    *(uint*)q29 += d102;
    *(uint*)q34 += d105;
    *(uint*)q35 += d104;
    MinContext = MaxContext;
LABEL_250:
    // -----------------------------------------------------------------------
    //  SYMBOL_FOUND tail (~ ppmd PrepareNextStep): emit the decoded byte,
    //  commit the range, run MixUpdate to advance the SSE / mixing state,
    //  and normalize the range coder for the next iteration.
    // -----------------------------------------------------------------------
    if( f_DEC ) putc(FoundState->Symbol, outFile);
    rc.commitRange();
    result = MixUpdate((byte*)MinContext);
    if( f_DEC ) rc.DecodeNormalize(inFile); else rc.EncodeNormalize(outFile);
    epoch = SymCount;
  } while( SymCount );
  return result;
}

int RealDecode(FILE* a1, FILE* a2) { return RealProcess<1>(a1,a2); }

int RealEncode(FILE* a1, FILE* a2) { 
  //printf( "!q32=%I64X!\n", q32);
  return RealProcess<0>(a1,a2); 
}
//--- #return
//--- #include "stats.inc"

sqword PPMIIEncode(FILE* File, FILE* a2, sqword (*a3)(FILE*, FILE*, sqword), int a4) {
  int v8; sqword v10; int v11; int v12; sqword v14; int v15; int v16;

  if( !SubAllocatorSize ) return 0;

  if( Interrupted ) {
    Interrupted = 0;
    SymCount = 1;
  } else {
    rc.initEncoder();
    StartModelRare(a4);
  }

  while( 1 ) {
    RealEncode(File, a2);
    if( SymCount ) break;
    if( a3 ) v8 = a3(a2, File, 0); else v8 = -1;
    SymCount = v8;
    //memset( &blob1[0x140029540-0x1400227B0], 0, 0x400);
    memset( SymMask, 0, 0x400 );
    memset( SymLastCtx, 0, 0xC00 );
    if( !v8 ) {
      Interrupted = 1;
      return 0;
    }
  }
  rc.Flush(File);

  if( a3 ) a3(a2, File, 1);

  return 1;
}

sqword PPMIIDecode(FILE* a1, FILE* a2, sqword (*a3_printstats)(FILE*, FILE*, sqword), int a4) {
  int v9; sqword v10; int cnt; int v12; int v13; int v14; int v15; int v16; int v17; int v18; int v19; int v20; int v21; int v22; int v23; int v24;

  if( !SubAllocatorSize ) return 0;

  if( Interrupted ) {
    Interrupted = 0;
    SymCount = 1;
  } else {
    rc.initDecoder(a2);
    StartModelRare(a4);
  }

  while(1) {
    RealDecode(a1, a2);

    if( SymCount ) break;

    if( a3_printstats ) v9 = a3_printstats(a1, a2, 0); else v9 = -1;

    SymCount = v9;

#if 0
    v10 = 64;
    do {
      SEE1[v10] = 0;
      SEE1_1[v10] = 0;
      SEE1_2[v10] = 0;
      SEE1_3[v10] = 0;
      v10 -= 4;
    } while( v10*16 );
#endif
    memset(SymMask, 0, sizeof(SymMask) );

    memset(SymLastCtx, 0, 0xC00);

    if( !v9 ) {
      Interrupted = 1;
      return 0;
    }
  }

  if( a3_printstats ) a3_printstats(a1, a2, 1);

  return 1;
}


//--- #return
//--- #include "main2.inc"

#pragma pack(1)
struct ARC_INFO {
  uint signature;      // 0x8CACAF8F  [verified]
  uint origSize;       // HeaderData[1]
  struct {              // packed into HeaderData[2]
    uint Variant   : 5; // must read back as 9   [verified]
    uint ModelSize : 12;// (val>>5)+1 on read
    uint ModelOrder: 4; // (val>>1 of byte2)+2 on read
    uint CutOff  : 1; // bit 5 of byte2
    uint Stored  : 1; // bit 0x400000 > uncompressed-fallback flag [verified]
    uint FNLen   : 9; // HIWORD>>7 on read
  };
  word _time;
  word _date;

  // Runtime tracking fields corresponding to __arch_hdr[4..7]
  uint _reserved_runtime; // __arch_hdr[4]
  uint startTime;         // __arch_hdr[5]
  uint initialFilePos;    // __arch_hdr[6]
  uint lastUiTime;        // __arch_hdr[7]
};
#pragma pack()

ARC_INFO arch_hdr;

sqword __PrintStats(FILE* outFile, FILE* inFile, sqword isFinal) {
  clock_t currentTime = clock();
  // Throttle UI updates to every 500ms, unless this is the final flush
  if( (currentTime < arch_hdr.lastUiTime + 500) && !isFinal ) return 0x10000;
  long outSize = ftell(outFile);
  uint outSizeSafe = (outSize<=0) ? 1 : (uint)outSize;
  // Prevent division by zero
  uint inSize = ftell(inFile) - arch_hdr.initialFilePos;

  arch_hdr.lastUiTime = currentTime;
  // Calculate compression ratio in Bits Per Byte (BPB) with rounding
  int bpbInt = (8*inSize)/outSizeSafe;
  int bpbFrac = (1000*(8*inSize-bpbInt*outSizeSafe)+(outSizeSafe>>1))/outSizeSafe;
  if( bpbFrac==1000 ) {
    ++bpbInt;
    bpbFrac = 0;
  }

  // Calculate processing speed in KB/sec
  // elapsedScaled effectively resolves to (elapsedMs * 1.024) / 1000,
  // scaling bytes/ms directly to KB/sec.
  int elapsedMs = currentTime - arch_hdr.startTime;
  int elapsedScaled = (elapsedMs*1024)/1000;
  int timeDivisor = (elapsedScaled==0) ? 1 : elapsedScaled;
  uint speedKBs = outSizeSafe/timeDivisor;
  // Calculate memory usage (from internal allocator)
  uint memUsedBytes = PPMIIGetCurrentModelSize();
  uint memUsedKB = memUsedBytes>>10;
  uint memUsedMBInt = memUsedBytes>>20;
  uint memUsedMBFrac = (10*(memUsedKB-(memUsedMBInt<<10))+512)>>10;           // Round to 0.1 MB

  if( memUsedMBFrac==10 ) {
    ++memUsedMBInt;
    memUsedMBFrac = 0;
  }

  // Determine display order (Original Size > Compressed Size)
  uint displayLeft = outSizeSafe;
  uint displayRight = inSize;
  if( !f_ENC ) { // If decoding, swap the variables for the display
    displayLeft = inSize;
    displayRight = outSizeSafe;
  }

  char printBuffer[568];
  snprintf(printBuffer, sizeof(printBuffer), "%15s:%7u >%7u, %1d.%03d bpb, used:%3u.%1u MB, speed: %u KB/sec.", (const char*)::FileName, displayLeft, displayRight, bpbInt, bpbFrac, memUsedMBInt, memUsedMBFrac, speedKBs);
  // '\r' (13) continuously overwrites the line during progress.
  // '\n' (10) finalizes the line when the file finishes.
  char endChar = isFinal ? '\n' : '\r';
  printf("%-79.79s%c", printBuffer, endChar);

  // Log to ratios file if finalized and logging is enabled
  if( isFinal && f_LOG ) {
    FILE* logFile = fopen("!ratios.lst", "a+t");
    if( logFile ) {
      fprintf(logFile, "%s\n", printBuffer);
      fclose(logFile);
    }
  }

  return 0x10000;
}

int __main(int argc, const char** argv) {
  InitTables();

  // (MXCSR flush-to-zero / denormals-are-zero setup removed: no SSE code present)

  int resetMethod = 1;
  int modelOrder = 12;
  int memoryMB = 1;//256;

  // Map modelOrder values >12 to internal codes [13,16], matching original logic:
  // 13-16->13, 17-32->14, 33-64->15, 65-128->16
  if( modelOrder>12 ) modelOrder = (modelOrder>32)+(modelOrder>16)+(modelOrder>64)+13;
  if( argc != 4 ) {
    printf("Usage: coder c input archive | coder d archive input\n");
    return -1;
  }

  // Parse Mode (Encode / Decode)
  char mode = toupper(argv[1][0]);
  if( mode == 'C' ) {
    f_ENC = 1;
  } else if( mode == 'D' ) {
    f_ENC = 0;
  } else {
    printf("unknown command: %s\n", argv[1]);
    return -1;
  }

  int mb = atoi(&argv[1][1]);
  if( mb>0 ) memoryMB=mb;

//  char (**streamBlock)[4096] = GetStreamBuf();
//  FILE* internalStream = (FILE*)(streamBlock+6);

  if( !f_ENC ) {
    // --- DECOMPRESSION MODE ---
    const char* archiveName = argv[2];
    const char* outputName = argv[3];

    FILE* inFile = fopen(archiveName, "rb");
    if( !inFile ) {
      printf("Can`t open file %s", archiveName);
      exit(-1);
    }

    if( fread(&arch_hdr, 0x10, 1, inFile) ) {
      if( arch_hdr.signature != 0x8CACAF8F || arch_hdr.Variant != 9 ) {
        printf("Can`t open file %s", archiveName);
        exit(-1);
      }

      char decodedFileName[512];
      size_t nameLen = arch_hdr.FNLen;
      fread(decodedFileName, nameLen, 1, inFile);
      decodedFileName[nameLen] = '\0';
      // Ignore the decodedFileName from archive, extract to requested output
      ::FileName = (void*)outputName;
      FILE* outFile = fopen(outputName, "wb");
      if( !outFile ) {
        printf("Can`t open file %s", outputName);
        exit(-1);
      }

      uint param1 = arch_hdr.ModelSize + 1;
      uint param2 = arch_hdr.ModelOrder + 2;
      int param3  = arch_hdr.CutOff;

      PPMIIDeleteModel();
      if( !StartSubAllocator(param1, param2, param3) ) {
        printf("Out of memory!");
        exit(-1);
      }

      arch_hdr.startTime = clock();
      arch_hdr.initialFilePos = ftell(inFile);
      if( arch_hdr.Stored ) {
        // Stored without compression
        uint rawBytesCount;
        if( fread(&rawBytesCount, 4, 1, inFile) != 1 ) {
          printf("Unexpected end of archive\n");
          exit(-1);
        }
        for(; rawBytesCount; --rawBytesCount ) {
          putc(getc(inFile), outFile);
        }
        clock_t endTime = clock();
        arch_hdr.lastUiTime = endTime;
        printf("%15s:%7ld >%7ld extracted.\n", (const char*)::FileName, ftell(outFile), ftell(inFile) - arch_hdr.initialFilePos);
      } else {
        PPMIIDecode(outFile, inFile, __PrintStats, 0);
      }

      fclose(outFile);
    }
    fclose(inFile);
  } else {
    // --- COMPRESSION MODE ---
    const char* inputName = argv[2];
    const char* archiveName = argv[3];

    FILE* inFile = fopen(inputName, "rb");
    if( !inFile ) {
      printf("Can`t open file %s", inputName);
      exit(-1);
    }

    FILE* outFile = fopen(archiveName, "wb");
    if( !outFile ) {
      printf("Can`t open file %s", archiveName);
      exit(-1);
    }

    const char* strippedName = strrchr(inputName, '/');
    if (!strippedName) strippedName = strrchr(inputName, '\\');
    strippedName = strippedName ? strippedName+1 : inputName;
    ::FileName = (void*)strippedName;

    fseek(inFile, 0, SEEK_END);
    arch_hdr.origSize = ftell(inFile);
    fseek(inFile, 0, SEEK_SET);
    arch_hdr.signature = 0x8CACAF8F;

    // Header flag packing using explicit bitfield assignments
    arch_hdr.Variant    = 9;
    arch_hdr.ModelSize  = ((short)memoryMB - 1) & 0xFFF;
    arch_hdr.ModelOrder = ((char)modelOrder + 14) & 0xF;
    arch_hdr.CutOff     = resetMethod & 1;
    arch_hdr.Stored     = 0;

    size_t bufferLen = strlen((const char*)::FileName);
    arch_hdr.FNLen = bufferLen;

    fwrite(&arch_hdr, 0x10, 1, outFile);
    fwrite(::FileName, arch_hdr.FNLen, 1, outFile);

    PPMIIDeleteModel();
    if( !StartSubAllocator(memoryMB, modelOrder, resetMethod) ) {
      printf("Out of memory!");
      exit(-1);
    }

    arch_hdr.startTime = clock();
    arch_hdr.initialFilePos = ftell(outFile);

    PPMIIEncode(outFile, inFile, __PrintStats, 0);
    // Re-packing uncompressible data if size exploded
    long inPos = ftell(inFile);
    long outPos = ftell(outFile);
    if( inPos != -1L && outPos != -1L ) {
      uint outSize = (uint)outPos;
      if( (uint)(outSize - arch_hdr.initialFilePos) > (qword)(inPos+4LL) ) {
        uint rawSize = (uint)inPos;
        fseek(inFile, 0, SEEK_SET);
        int headerOffset = arch_hdr.initialFilePos - arch_hdr.FNLen - 16;
        fseek(outFile, headerOffset, SEEK_SET);
        _chsize(_fileno(outFile), headerOffset);

        arch_hdr.Stored = 1; // Set uncompressed flag

        fwrite(&arch_hdr, 0x10, 1, outFile);
        fwrite(::FileName, arch_hdr.FNLen, 1, outFile);
        fwrite(&rawSize, 4, 1, outFile);

        for(; rawSize; --rawSize ) {
          putc(getc(inFile), outFile);
        }
      }
    }

    fclose(inFile);
    fclose(outFile);
  }

  PPMIIDeleteModel();
  return 0;
}
//--- #return

}

int main( int argc, const char **argv ) {
  int r = __main( argc, argv );
  return r;
}
