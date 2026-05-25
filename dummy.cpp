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

#define LOWORD(x)  WORDn(x,LOW_IND(x,word))
#define HIBYTE(x)  BYTEn(x,HIGH_IND(x,byte))

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
short& MixFreq1 = (short&)MixWeight1[1];
auto& MixFreq1_1 = *(short(*)[0xF0000-3])(((char*)MixWeight1)+6);

int d29[0x2040];
short& w12 = *(short*)((char*)&d29 + 0x4);
auto& w11 = (short(&)[0x407D])((char*)&d29)[0x6];

int PredWeight[0xA1C];
int* PredWeight_1 = &PredWeight[1];

int d27[0x70040];
// Six short-typed overlays on d27 at fixed byte offsets:
//   MixBound2 @ 0x00004, MixBound3 @ 0x00006, MixBound6 @ 0x10006,
//   b19       @ 0x1A0000, MixBound5 @ 0x1A0006, MixBound4 @ 0x1B0006
auto& MixBound2 = (short(&)[0x70040*2-0x00002])((char*)&d27)[0x00004];
auto& MixBound3 = (short(&)[0x70040*2-0x00003])((char*)&d27)[0x00006];
auto& MixBound6 = (short(&)[0x70040*2-0x08003])((char*)&d27)[0x10006];
auto& b19       = (short(&)[0x70040*2-0xD0000])((char*)&d27)[0x1A0000];
auto& MixBound5 = (short(&)[0x70040*2-0xD0003])((char*)&d27)[0x1A0006];
auto& MixBound4 = (short(&)[0x70040*2-0xD8003])((char*)&d27)[0x1B0006];

char SymType[256];

int SymMask[256];

int SymLastCtx[1024];
int* SymLastCtx2 = &SymLastCtx[256];
int* MatchPosBySym = &SymLastCtx[512];
char BijectMap[0x40000];
// Discard sink for the BijectMap cell pointer when the MixScale predictor
// path isn't active (mixScaleCntr==0). 4 bytes — bijectCellPtr is a byte*
// that writes a 4-byte cell on every step.
int bijectCellSink;
char foundSymHist;
// Pointer to a 4-byte BijectMap cell: byte[0]=sym, [1]=prev1, [2]=prev2,
// [3]=count. Set per-step by MixUpdate; reads through this pointer happen
// later in the same call.
sqword bijectCellPtr;
int MixScale;
int hintSymRecent;
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

char SymFreqs[256];

int MixWeight2[0x8040];
auto& MixFreq2_1 = (short(&)[0x803F*2])MixWeight2[1];
short* MixFreq2 = &MixFreq2_1[1];


int d90[4096];
int& q12BaseSel = d90[2];
int& b31Key = d90[3];
int& Order1Ctx = d90[4];
int& b31KeyPrev = d90[5];
int& order1CtxSaved = d90[6];
int& matchHintByte = d90[7];
int& bdiffSaved = d90[8];
int& bdiffStickyCnt = d90[9];
int& matchHashSy = d90[10];
int& matchPosAge = d90[11];
int& matchEpoch2 = d90[12];
// d90[13] is unused (was matchDeltaSaved, a write-only spill)
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

sqword PredWeightBG;             // predWeightB storage (aliased in RealProcess)
sqword PredWeightAG;             // predWeightA storage (aliased in RealProcess)
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
int unusedD111;
int NMasked;

sqword predWeightSink2;
int predDeltaNum;
int predDeltaDen;
int runLengthInit;
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
int orderBumpVariance;
int predWeightSink;
int predBaseDeltaA;
int predBaseDeltaB;
int binMixDeltaHi;
int binMixDeltaLo;
int wDelta32;
int wDelta31;
int wDelta30;
int wDelta29;
int wDelta34;
int wDelta35;
int predRescaleDiv;
int cumFreqAcc;
int wDelta33;
int cumFreqMixSave;
int sseIdxStorage;

sqword q32;
sqword q31;
sqword q30;
sqword q29;
sqword q34;
sqword q35;
sqword BinMixCenterG;
sqword PredBaseAG;
sqword PredBaseBG;
sqword Sse1SlotG;
sqword BinMixLoG;
sqword BinMixHiG;
sqword BinSseCellG;
sqword SseMatchSlotG;
sqword Sse2SlotG;
sqword Sse3SlotG;
sqword q9;
sqword q33;
sqword CtxChainEnd;

int hintSymB31;
int hintSymM2;
int hintSymB29;
int hintSymBiject;
int hintSymMatch3;
int hintSymBmCell;
int sse2DenDelta;
int sse2NumDelta;
int sseMatchDenDelta;
int sseMatchNumDelta;
int predSseTotDelta;
int predWeightDelta;
int MatchCtxHi;
int recentSym;
int mixScaleCntr;
int symHalfHistory;
int SparseHashA;
int SparseIdxA;
int SparseHashB;
int SparseIdxB;
int SparseBit;


//typedef byte t_byte_140029940[0x2358D0]; t_byte_140029940& Sse2State = *(t_byte_140029940*)(blob1+ 0x140029940 -0x1400227B0);
//byte Sse2State[0x2358D0];
byte Sse2State[0xC0818];
// Overlays on Sse2State at fixed byte offsets (the decompiler emitted
// the offsets as differences from the original module base address).
sqword& Sse2BaseG          = *(sqword*)((byte*)&Sse2State + 0x00810);
typedef byte t_byte_14002A158[0x40000]; t_byte_14002A158& MatchPosHash = *(t_byte_14002A158*)((byte*)&Sse2State + 0x00818);
typedef byte t_byte_14006A158[0x80000]; t_byte_14006A158& SseState2    = *(t_byte_14006A158*)((byte*)&Sse2State + 0x40818);
typedef byte t_byte_14007A158[0x10000]; t_byte_14007A158& b28          = *(t_byte_14007A158*)((byte*)&Sse2State + 0x50818);
typedef byte t_byte_14008A158[0x10000]; t_byte_14008A158& b29          = *(t_byte_14008A158*)((byte*)&Sse2State + 0x60818);
typedef byte t_byte_14009A158[0x10000]; t_byte_14009A158& b30          = *(t_byte_14009A158*)((byte*)&Sse2State + 0x70818);
typedef byte t_byte_1400AA158[0x10000]; t_byte_1400AA158& b31          = *(t_byte_1400AA158*)((byte*)&Sse2State + 0x80818);

typedef byte t_byte_1400BA158[0x10000]; t_byte_1400BA158& b34          = *(t_byte_1400BA158*)((byte*)&Sse2State + 0x90818);
byte* b35 = &b34[1];

typedef byte t_byte_1400CA158[0x10000]; t_byte_1400CA158& b36          = *(t_byte_1400CA158*)((byte*)&Sse2State + 0xA0818);
byte* b37 = &b36[1];
byte* b33 = &b36[2];
byte* b32 = &b36[3];

typedef byte t_byte_1400DA158[0x10000]; t_byte_1400DA158& b27          = *(t_byte_1400DA158*)((byte*)&Sse2State + 0xB0818);
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
  UNIT_SIZE   = 12,
  N_INDEXES   = 38,
  MAX_O       = 16,  // max PPM model order accepted by StartSubAllocator
  MEM_DIVISOR = 10   // suballocator: text/units split is (1/MEM_DIVISOR)/(rest)
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

// Sum weights[bit] over each set bit of v. Used by the mix-model init
// loops in StartModelRare: each context-index outerIdx is a bitset over a
// small fixed alphabet (b17, b20 etc.), and bitSum is the weighted population
// count of those bits.
inline int PopCountWeighted_(uint v, const char* weights) {
  int sum = 0;
  for (int j = 0; v > 0; v >>= 1, ++j) {
    sum += weights[j] * (int)(v & 1);
  }
  return sum;
}

// Initialize a MixModel cell with the constant (freq0=18432, freq1=5120) used
// by both primary and secondary mix init loops, and encode `w` into weight.
inline void InitMixCell_(MixModel& cell, int w) {
  cell.freq0 = 18432;
  cell.freq1 = 5120;
  cell.weight = (w << 23) | (72 * w);
}

// Clamp a mix-init weight scalar to the PE-specific safe band [9, 241].
inline int ClampMixWeight_(int w) {
  if (w >= 241) return 241;
  if (w <    9) return   9;
  return w;
}

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
// Typed alias of q9: FoundState pointer. Used throughout RealProcess,
// MixUpdate, RescaleCtx, ReduceOrder, etc. Defined here once STATE is known.
STATE*& FoundState = (STATE*&)q9;
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

  // unlink(): remove this block from its doubly-linked list. The caller is
  // responsible for adjusting any QueueSize counter; this only fixes the
  // forward/back pointers of the immediate neighbours.
  void unlink() {
    next()->Prev = Prev;
    prev()->Next = Next;
  }

  uint canMerge() const {
    return (Stamp==byte(-1));
  }

};
#pragma pack()

//MEM_BLK* BList;

// Typed alias of BList: the suballocator's free-list array, indexed by
// size-class. Used by FreeUnits_/FreeContext_/MoveUnits_/ShrinkUnits_/
// MoveContext_ to walk the doubly-linked free queues.
MEM_BLK*& BListPtr = (MEM_BLK*&)BList;

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

void FreeUnitsRare(sqword blockAddr, uint sizeClass);   // defined in subs_freeunitsrare1.inc
sqword AllocUnitsRare(uint unitsIdx);      // defined in subs_allocunitsrare.inc

// Fast-path allocator for 1-context (12-byte) blocks. Mirrors textbook
// ppmd.cpp PPM_CONTEXT::AllocContext: prefer the HiUnit downward bump, else
// pop from the size-class-0 freelist, else fall back to AllocUnitsRare(0).
inline PPM_CONTEXT* AllocContext_() {
  if (::HiUnit != ::LoUnit) {
    ::HiUnit -= UNIT_SIZE;
    return (PPM_CONTEXT*)::HiUnit;
  }
  if (BListPtr->avail()) {
    return (PPM_CONTEXT*)BListPtr->unlinkPrev();
  }
  return (PPM_CONTEXT*)AllocUnitsRare(0);
}

// Fast-path allocator counterpart of AllocUnitsRare: pop the head of the
// size-class queue if non-empty; else bump LoUnit toward HiUnit; if that
// would collide, fall back to AllocUnitsRare. Returns 0 on out-of-memory.
inline sqword AllocUnits_(uint sizeClass) {
  MEM_BLK* queue = &BListPtr[sizeClass];
  if (queue->avail()) {
    return (sqword)queue->unlinkNext();
  }
  uint byteOff = UNIT_SIZE * (uint)Indx2Units[sizeClass];
  if (::LoUnit + byteOff > (sqword)::HiUnit) {
    return AllocUnitsRare(sizeClass);
  }
  sqword result = ::LoUnit;
  bool isExact = (::LoUnit + byteOff == ::HiUnit);
  ::LoUnit += byteOff;
  if (!isExact) {
    *(uint*)(byteOff + result) = 0;
  }
  return result;
}

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
  uint indx = Units2Indx4[NU - 1];
  NU = Indx2Units[indx];
  MEM_BLK* p = (MEM_BLK*)ptr;
  if (!p[NU].canMerge())
    BListPtr[indx].linkNext(p, NU);
  else
    FreeUnitsRare((sqword)p, NU);
}

inline void FreeContext_(PPM_CONTEXT* ptr) {
  MEM_BLK* p = (MEM_BLK*)ptr;
  if (!p[1].canMerge())
    BListPtr[0].linkPrev(p, 1);
  else
    FreeUnitsRare((sqword)p, 1);
}

inline void* MoveUnits_(void* OldPtr, uint NU) {
  uint indx = Units2Indx4[NU - 1];
  uint NewNU = Indx2Units[indx];
  MEM_BLK* p = (MEM_BLK*)OldPtr;
  if (!p[NewNU].canMerge() || !BListPtr[indx].avail()) return OldPtr;
  void* NewPtr = BListPtr[indx].unlinkNext();
  UnitsCpy_(NewPtr, OldPtr, NU);
  FreeUnitsRare((sqword)p, NewNU);
  return NewPtr;
}

inline void* ShrinkUnits_(void* OldPtr, uint OldNU, uint NewNU) {
  uint i0 = Units2Indx4[OldNU - 1];
  uint i1 = Units2Indx4[NewNU - 1];
  if (i0 == i1) return OldPtr;
  if (BListPtr[i1].avail()) {
    void* ptr = BListPtr[i1].unlinkNext();
    UnitsCpy_(ptr, OldPtr, NewNU);
    FreeUnits_(OldPtr, Indx2Units[i0]);
    return ptr;
  }
  NewNU = Indx2Units[i1];
  FreeUnitsRare((sqword)((MEM_BLK*)OldPtr + NewNU), Indx2Units[i0] - NewNU);
  return OldPtr;
}

inline PPM_CONTEXT* MoveContext_(PPM_CONTEXT* OldPtr) {
  MEM_BLK* p = (MEM_BLK*)OldPtr;
  if (!p[1].canMerge() || !BListPtr[0].avail()) return OldPtr;
  PPM_CONTEXT* NewPtr = (PPM_CONTEXT*)BListPtr[0].unlinkPrev();
  UnitsCpy_(NewPtr, OldPtr, 1);
  FreeUnitsRare((sqword)p, 1);
  return NewPtr;
}
//--- #return

//--- #include "subs_contextwalk.inc"

// =============================================================================
//  Constexpr builder for SSE / mix context composite indices.
// -----------------------------------------------------------------------------
//  Many places in the codec build "bitfield" indices (mixIdxA, mixIdxC,
//  seeIdxF, OrderCtxSeed, sse2IdxA/F, matchScore, mixCtx, etc.) as sums of
//  small per-feature terms each contributing at a fixed bit position.
//  Written verbatim as
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

// Upper bound on PPMContextWalk's path[] buffer. Deduced from the path-depth
// condition checks (`if (path_depth >= 32)` etc.) — the buffer needs only
// to be larger than the deepest path the walk can produce. Distinct from
// ppmd.cpp's MAX_O = 16 (max model order), which here is the dynamic
// MaxOrder global instead.
constexpr int PATH_BUF_MAX = 128;

// 2. MaxContext definition implemented via an lvalue reference mapping to MaxContext0
// #define MaxContext (*(PPM_CONTEXT**)&MaxContext0)
// Alternatively, using a explicit C++ reference variable:
PPM_CONTEXT*&MaxContext = *(PPM_CONTEXT**)&MaxContext0;

void BinEscFreq(PPM_CONTEXT* pc);
inline void ComputeMatchHints_(int matchTblHit, uint sym);

// Walks the context suffix chain to update local frequency statistics, perform inertia
// scaling adjustments, and calculate state metrics for context-mixing/predictive modeling.
static void PPMContextWalk(int epoch, int sym, uint* outSeeIndex, uint* outSuffixNStates, int* outMixCtx, sqword* outSummFreqPtr, int* outSparseFlags) {
  // Collect path context history down from the current maximum context
  PPM_CONTEXT* path[PATH_BUF_MAX];
  int path_depth = 0;

  PPM_CONTEXT* curr = MaxContext;
  RSContext = sym;
  SymLastCtx[(byte)b27[sym+(Order1Ctx<<8)]] = epoch;

  // Step 1: Climb suffixes until a context with non-zero states is encountered
  do {
    path[path_depth++] = curr;
    curr = curr->getSuffix();
  } while (!curr->NStates);

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
      ctx = ctx->getSuffix();
      last_nstates = ctx->NStates;
      ++temp_depth;
      last_state = ctx->getStates()+last_nstates;
    } while( last_state->Freq==0 );

    total_depth = temp_depth;
  }

  // Capture pre-rescale NStates tracking metric
  uint verification_nstates = ctx->NStates;

  // Step 3: Check escape condition and handle low-frequency model rescaling
  if( ctx->getStates()[ctx->Flags&0x0F].Freq==0 ) {
    BinEscFreq(ctx);
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
      PPM_CONTEXT* suffix_ctx = ctx->getSuffix();
      word suffix_summ_freq = suffix_ctx->SummFreq;
      byte suffix_nstates = suffix_ctx->NStates;

      // Uses pre-rescale context state metrics (verification_nstates + 1)
      if( summ_freq+summ_freq*suffix_nstates<(verification_nstates+1)*(suffix_summ_freq+15) ) {
        if( suffix_ctx->getStates()[suffix_ctx->Flags&0x0F].Freq==0 ) {
          BinEscFreq(suffix_ctx);
          suffix_summ_freq = suffix_ctx->SummFreq;
          summ_freq = ctx->SummFreq; // Synchronize just in case
        }

        STATE* suffix_state;
        for( suffix_state = suffix_ctx->getStates(); sym!=suffix_state->Symbol; suffix_state++ )
          ;
        int suffix_found_freq = suffix_state->Freq;
        int base_weight = 5*verification_nstates+5;
        uint tunedSumm = summ_freq+2*base_weight;
        // suffix scale = 5 or 7 depending on whether the summ_freq exceeded
        // 2*base_weight (the "high-density" indicator).
        int suffixScale = (2*base_weight < summ_freq) ? 7 : 5;
        int tunedSuffix = suffixScale*(suffix_nstates+1)+suffix_summ_freq;
        if( tunedSuffix*found_state->Freq<(int)(tunedSumm*suffix_found_freq) ) {
          if( found_state->Freq>228 )
            goto TARGET_SCALE_FALLBACK;
          word delta_freq = summ_freq-found_state->Freq;
          uint deltaSum  = tunedSumm - found_state->Freq;
          uint denomAdj  = 3*deltaSum + tunedSuffix - suffix_found_freq;
          uint adjusted_freq = (deltaSum*(suffix_found_freq + 3*found_state->Freq) + denomAdj - 4) / denomAdj;
          if (adjusted_freq > found_state->Freq + 11) {
            adjusted_freq = found_state->Freq + 11;
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
  // Count how many of these 8 "scale_diff under k * freq_bound" thresholds
  // pass, then bias by +1. Each pass adds 1, giving a path_threshold in [1, 9].
  uint path_threshold = 1
    + (35*scale_diff <  4*freq_bound)   // <  ~1/9
    + (15*scale_diff <  4*freq_bound)   // <  ~4/15
    + (13*scale_diff <  8*freq_bound)   // <  ~8/13
    + ( 9*scale_diff <  4*freq_bound)   // <  ~4/9
    + ( 6*scale_diff <    freq_bound)   // <  ~1/6
    + (   scale_diff <    freq_bound)   // <  1
    + (   scale_diff <  2*freq_bound)   // <  2
    + (   scale_diff <  6*freq_bound);  // <  6

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
  orderBumpVariance = path_threshold-initial_threshold;

  // Set the low-level pointer output to the updated context summary tracking byte
  *outSummFreqPtr = (sqword)((byte*)&path_ctx->SummFreq);

  // Step 8: Calculate context metrics and model hash indicators for the Mixer/LSTM stage
  SparseBit  = 1<<sym;
  SparseIdxA = (uint)(sym+SparseHashA)>>5;
  SparseIdxB = (uint)(sym+SparseHashB)>>5;
  // 2-bit composite: bit 0 says "sym seen in SparseBitmapA bucket",
  // bit 1 says "sym seen in SparseBitmapB bucket".
  int sparseFlags = (int)SseIdx{}
    .bit<0>(SparseBit & SparseBitmapA[SparseIdxA])
    .bit<1>(SparseBit & SparseBitmapB[SparseIdxB]);
  int matchTableEntry = MatchPosTable[sym+(MatchCtxHi<<8)];
  ComputeMatchHints_(matchTableEntry, sym);

  PPM_CONTEXT* max_suffix_ctx = MaxContext->getSuffix();
  uint suffixNStates = max_suffix_ctx->NStates;
  MixCtxExtra += SseIdx{}.bit<7>(suffixNStates == 0);

  uint orderShortfall = OrderFall-total_depth;
  byte ctxFoundSym    = ctx->getStates()[ctx->Flags&0x0F].Symbol;

  // mixCtxComposite packs ~10 features into a bitfield over MixCtx:
  //   .raw MixCtx       : the running mix-ctx state
  //   bit  5            : RunLength > 0
  //   .raw Flags & 0x80 : Flags high bit (bit 7)
  //   bit  6            : MixCtx2 & 1
  //   bit  8            : (MixCtx2 & 6) == 6
  //   bit  9            : sym matches the rank-0 FoundSymbol
  //   bit 10            : epoch matches the SymLastCtx slot
  //   bit 11            : OrderFall - total_depth > 3
  //   bit 12            : sym matches the rank-(Flags&0xF) symbol
  //   bit 13            : sparseFlags==3 || epoch matches MatchPosBySym
  uint mixCtxComposite = SseIdx{}
    .raw  (MixCtx)
    .bit  <5> (RunLength > 0)
    .raw  (MaxContext->Flags & 0x80)
    .bit  <6> (MixCtx2 & 1)
    .bit  <8> ((MixCtx2 & 6) == 6)
    .bit  <9> (sym == FoundSymbol)
    .bit  <10>(epoch == SymLastCtx[sym])
    .bit  <11>(orderShortfall > 3)
    .bit  <12>(sym == ctxFoundSym)
    .bit  <13>(sparseFlags == 3 || epoch == MatchPosBySym[sym]);

  int mixCtx;
  if( suffixNStates ) {
    uint mixCtxMasked = mixCtxComposite&0xFFFFFFDE;
    uint boostBit = (path_threshold!=initial_threshold)||(scale_diff<=10*freq_bound);

    mixCtx = 32*boostBit+mixCtxMasked+(sym==PrevSymbol);
  } else {
    PPM_CONTEXT* deep_suffix_ctx = max_suffix_ctx->getSuffix();
    suffixNStates = deep_suffix_ctx->NStates;
    if( deep_suffix_ctx->NStates||orderShortfall<4||(orderShortfall<5&&(verification_nstates+1)<4&&ctx->SummFreq-found_state->Freq<36) ) {

      uint suffix_chain_idx = deep_suffix_ctx->iSuffix;
      uint deeperBit = 0;
      if( suffix_chain_idx ) {
        PPM_CONTEXT* deeper_suffix_ctx = (PPM_CONTEXT*)Indx2Ptr(suffix_chain_idx);
        deeperBit = (2*suffixNStates<deeper_suffix_ctx->NStates);
      }
      mixCtx = mixCtxComposite+8*deeperBit+16;
    } else {
      // path_depth-based boost: +8 / +10 / +12 / +14 at thresholds 0, 6, 14, 32.
      int depthBoost = 8
                     + (path_depth >= 6)  * 2
                     + (path_depth >= 14) * 2
                     + (path_depth >= 32) * 2;
      mixCtx = mixCtxComposite + depthBoost;
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
void InitTables() {
  uint i,j,k;

  memset(SymFreqs,0,256);
  //memset(b19,0,0x20100);
  //memset(ddd,0,4*31);
  // SSE/mix accumulators and per-step deltas
  sseTot = sseCum = orderBumpVariance = 0;
  predWeightSink = predBaseDeltaA = predBaseDeltaB = 0;
  binMixDeltaHi = binMixDeltaLo = 0;
  wDelta29 = wDelta30 = wDelta31 = wDelta32 = wDelta33 = wDelta34 = wDelta35 = 0;
  predRescaleDiv = cumFreqAcc = cumFreqMixSave = sseIdxStorage = 0;

  // SSE/predictor slot pointers (typed aliases of q-globals)
  q29 = q30 = q31 = q32 = q33 = q34 = q35 = 0;          // mix-table slot cluster
  q9 = CtxChainEnd = 0;                                  // FoundState global + chain-end
  BinMixCenterG = BinMixHiG = BinMixLoG = 0;            // binMix neighbour pair
  PredBaseAG = PredBaseBG = 0;                          // predBase expansion pair
  Sse1SlotG = Sse2SlotG = Sse3SlotG = SseMatchSlotG = BinSseCellG = 0; // SSE/BinSse slots
  // Zero-init grouped by role.
  hintSymB31    = hintSymM2  = hintSymB29 = hintSymBiject =
    hintSymMatch3 = hintSymBmCell = 0;                              // per-step hint chains
  sse2DenDelta  = sse2NumDelta = sseMatchDenDelta = sseMatchNumDelta = 0; // SSE delta accumulators
  predSseTotDelta = predWeightDelta = 0;                            // predictor accumulators
  MatchCtxHi  = recentSym = mixScaleCntr = symHalfHistory = 0;      // per-symbol carry state
  SparseHashA = SparseIdxA = SparseHashB = SparseIdxB = SparseBit = 0; // sparse bitmap state
  memset( SseState3, 0, 0x20000 );
  //memset( b27, 0, 0x10000 );
  //memset( MatchPosHash, 0, 0x40000 );
  //memset( SseState2, 0, 0x80000 );
  memset( b28, 0, 0x10000 );

  byte freqtmp[] = {0,0,0,1,1,2,3,3,4,0,0,0};
  memset( freqmap, 0, sizeof(freqmap) );
  memcpy( freqmap, freqtmp, sizeof(freqtmp) );

  for( i=0; i < 5; ++i ) Indx2Units[0 + i] = 1 + i;
  for( i=0; i < 3; ++i ) Indx2Units[5 + i] = 7 + 2*i;
  for( i=0; i < 3; ++i ) Indx2Units[8 + i] = 14 + 3 * i;
  for( i=0; i < 27; ++i) Indx2Units[11 + i] = 24 + 4 * i;

  for( i=0,j=0; i < 0x80; ++i ) {
    if( Indx2Units[j] < i+1 ) j++;
    Units2Indx4[i] = j;
  }

  // some quantization table
  // 0.220238 + 2.05508*i^0.444477
  // 2.0661 + 1.4084*Sqrt[0.4681+i] also fits, and is a better fit for algorithm below
  int quantStepSize=1, stepRemaining=1;
  SymType[0] = 1; SymType[1] = 2;
  for( i=2,j=2,k=2; i < 0x100; ++i ) {
    SymType[j] = k + 1;
    if( --stepRemaining==0 ) { ++k; stepRemaining = ++quantStepSize; }
    j = i + 1;
  }
  SymType[0xFF] = 24;

  // SSE0: sym-class bit (0 for ASCII 0..63, 0x80 for high bytes). PE-variant
  // equivalent of ppmd.cpp's SymType[256] = { 0 x64, 4 x192 } — different
  // value, same role.
  memset(SSE0,      0,    64);    // 64 ASCII bytes
  memset(SSE0 + 64, 0x80, 192);   // remaining 192 bytes

  // SSE1: 4-band size-class table — first 3 entries are small, [3..37]
  // medium, [38..] large.
  SSE1[0] = 0;  SSE1[1] = 2;  SSE1[2] = 2;
  memset(SSE1 + 3,  4,    35);    // 38 - 3
  memset(SSE1 + 38, 6,    218);   // 256 - 38

  // BinMapTable: 16-entry uint table, indexed by (mixCtx2New & 0xF) in
  // SseSeed assembly. Rows [0..3]*4 + [0..2] are 0; only the +3 lane of each
  // row carries the (1, 2, 1, 3) << 9 weight.
  memset(BinMapTable, 0, sizeof(BinMapTable));
  BinMapTable[3]  = 1u << 9; // 0x200, row 0 lane +3
  BinMapTable[7]  = 2u << 9; // 0x400, row 1 lane +3
  BinMapTable[11] = 1u << 9; // 0x200, row 2 lane +3
  BinMapTable[15] = 3u << 9; // 0x600, row 3 lane +3

  for( i=0,j=0; i < 0x80; i++)  { NextBinFreq[i] = j+1; if( i==RLQBounds[j]) j++; }
  for( i=0,j=0; i < 0x100; i++) { SSE0QTable[i] = j+1;  if( i==SSE0QBounds[j] ) j++; }
  for( i=0,j=0; i < 0x80; i++)  { SSE1QTable[i] = j;    if( i==SSE1QBounds[j] ) j++; }
  for( i=0,j=0; i < 0x100; i++) { SEEQTable[i] = j;     if( i==SEEQBounds[j] ) j++; }
}
//--- #return
//--- #include "subs_binescfreq2.inc"

void BinEscFreq(PPM_CONTEXT* pc) {
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
    BinEscFreq(suffix);
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

void RescaleCtx(PPM_CONTEXT* ctx) {
  int          NStates0   = ctx->NStates;             // original NStates (= last index)
  int          totalCount = NStates0 + 1;             // # states to iterate (incl. found)
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
    STATE* fp = FoundState;
    while (fp != states) {
      // SWAP(fp[0], fp[-1])
      STATE tmp = *fp;
      *fp = *(fp - 1);
      *(fp - 1) = tmp;
      fp--;
    }
  }

  // ---- step 2: top-down rescale + compact zero-freq slots to the top ------
  STATE* endState  = states + totalCount;    // one past last
  STATE* lastState = endState - 1;           // last state
  ctx->Flags    = 0;
  ctx->SummFreq = 0;
  int remaining = totalCount;
  do {
    --endState;
    int newFreq = (bias + mask * endState->Freq) >> shift;
    endState->Freq = (byte)newFreq;
    ctx->SummFreq += (byte)newFreq;
    if (endState->Freq) {
      ctx->Flags |= SSE0[endState->Symbol];
    } else {
      // Shift STATEs (k+1..N) down to (k..N-1); mark last as removed.
      for (STATE* p = endState; p < lastState; ++p) {
        *p = p[1];
      }
      lastState->Freq = 0;
    }
    --remaining;
  } while (remaining);

  // ---- step 3a: top slot survived -> just record Flags|=0x40 and return ---
  if (lastState->Freq) {
    ctx->Flags |= 0x40;
    FoundState = (STATE*)Indx2Ptr(ctx->iStates);
    return;
  }

  // ---- step 3b: count trailing zero-freq slots ----------------------------
  int dropped = 0;
  do {
    ++dropped;
    --lastState;
  } while (!lastState->Freq);

  int newNStates = (byte)(NStates0 - dropped);
  ctx->NStates = (byte)newNStates;

  if (newNStates) {
    // ---- step 3b-i: survivors > 0 -> ShrinkUnits -------------------------
    uint oldNU = (uint)((NStates0 + 2) >> 1);
    uint newNU = (uint)((newNStates + 2) >> 1);
    STATE* newStates = (STATE*)ShrinkUnits_(states, oldNU, newNU);
    ctx->iStates = Ptr2Indx(newStates);
    ctx->Flags  |= 0x40;
    FoundState = newStates;
    return;
  }

  // ---- step 3b-ii: collapse to oneState -----------------------------------
  word firstSF   = *(word*)states;
  uint firstSucc = states[0].iSuccessor;
  uint newFreq2  = (NStates0 + ((firstSF >> 7) & 0xFFFFFFFE)) / (uint)(NStates0 + 1);
  if (newFreq2 >= 0x2Cu) newFreq2 = 44;
  HIBYTE(firstSF) = (byte)newFreq2;       // fold new freq back into the word

  FreeUnits_(states, (uint)((NStates0 + 2) >> 1));

  FoundState                  = &ctx->oneState();
  ctx->oneState().Symbol      = (byte)firstSF;
  ctx->oneState().Freq        = (byte)(firstSF >> 8);
  ctx->oneState().iSuccessor  = firstSucc;
  ctx->Flags                  = SSE0[(byte)firstSF];
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

void SseScale1(SseCounter* cnt) {
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
    return;
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

void SseScale2(SseSlot* s) {

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
  s->hits   = (word)newPredHi;
  s->predHi = (word)q;
}
//--- #return
//--- #include "subs_allocunitsrare.inc"
sqword AllocUnitsRare(uint unitsIdx) {
  sqword result;
  sqword textBufBytes;
  int sentinelField2;
  sqword sentinelField1;
  uint reqSizeIdx = unitsIdx;
  uint reqUnits = Indx2Units[unitsIdx];
  while (++unitsIdx != N_INDEXES) {
    MEM_BLK* freeQueue = &BListPtr[unitsIdx];
    if (freeQueue->avail()) {
      // Pop the queue's head block and return the leftover via FreeUnitsRare.
      sqword result = (sqword)freeQueue->unlinkNext();
      uint biggerUnits = Indx2Units[unitsIdx];
      FreeUnitsRare(result + (sqword)UNIT_SIZE*reqUnits, biggerUnits - reqUnits);
      return result;
    }
  }
  if( CutOffCount ) {
    if( GlueCount )
      return 0;
    textBufBytes = UNIT_SIZE*reqUnits;
    if( UnitsStart-textBufBytes<=(qword)pText ) {
      return 0;
    } else {
      result = UnitsStart-textBufBytes;
      UnitsStart -= textBufBytes;
    }
  } else {
    // GlueFreeBlocks: walk every BList[0..37] queue, draining it into
    // FreeUnitsRare so coalesce/split decisions get re-evaluated. The
    // sentinel block (a dummy at the end of the heap) serves as the loop
    // terminator: we insert it at each queue's head, then walk backward
    // (via Prev) from the queue's original tail until we loop back to it.
    MEM_BLK* sentinel = (MEM_BLK*)((char*)HeapStart + SubAllocatorSize - UNIT_SIZE);
    sentinelField2 = sentinel->Prev;
    sentinelField1 = *(qword*)sentinel;
    for (uint queueIdxOuter = 0; queueIdxOuter < N_INDEXES; ++queueIdxOuter) {
      MEM_BLK* queue = &BListPtr[queueIdxOuter];
      // Push sentinel at the head; pop the (original) tail as our starting
      // walk position.
      queue->linkNext(sentinel, 1, /*Stamp=*/(byte)-2);
      MEM_BLK* blockWalker = queue->unlinkPrev();
      // QueueSize was just incremented by linkNext and decremented by
      // unlinkPrev; the for-loop's iteration step keeps it dropping as we
      // consume entries.
      for (; blockWalker != sentinel; --queue->QueueSize) {
        // Re-classify this block: free it via the shared coalesce/chunk/split
        // path. FreeUnitsRare will reinsert into whatever queue ends up right
        // (possibly different from the current size class after coalescing).
        FreeUnitsRare((sqword)blockWalker, Indx2Units[Units2Indx[blockWalker->NU + 3]]);
        // Walk to next entry (= the new tail of queue); manual inlined
        // unlinkPrev minus the QueueSize-- (the for-step does that).
        MEM_BLK* prevBlk = queue->prev();
        queue->Prev = prevBlk->Prev;
        prevBlk->prev()->Next = Ptr2Indx(queue);
        blockWalker = prevBlk;
      }
    }
    *(qword*)sentinel = sentinelField1;
    sentinel->Prev = sentinelField2;
    CutOffCount = 1;
    result = AllocUnits_(Units2Indx4[Indx2Units[reqSizeIdx] - 1]);
  }
  return result;
}
//--- #return
//--- #include "subs_freeunitsrare.inc"
void FreeUnitsRare(sqword blockAddr, uint sizeClass) {
  sqword biggerSizeClass;
  sqword biggerUnits;
  int deltaUnits;
  // Coalesce: walk trailing blocks whose Stamp is 0xFF, unlinking each from
  // its size-class queue and absorbing its units into our running size.
  while (true) {
    MEM_BLK* probe = (MEM_BLK*)(blockAddr + (sqword)UNIT_SIZE*sizeClass);
    if (probe->Stamp != (byte)-1) break;
    probe->unlink();
    --BListPtr[Units2Indx[probe->NU + 3]].QueueSize;
    sizeClass += probe->NU;
  }
  // Chunks-over-128: when sizeClass exceeds 128 units (one 1536-byte block),
  // split the head off into chunks of exactly 128 units each and link them
  // onto BList[37] (the dedicated 1536-byte-chunk queue). What remains is
  // (sizeClass - 128 * chunksOver128) units.
  if (sizeClass > 0x80) {
    uint chunksOver128 = (sizeClass - 1) >> 7;   // == ceil(sizeClass/128) - 1
    for (uint k = 0; k < chunksOver128; ++k) {
      BListPtr[37].linkNext((MEM_BLK*)blockAddr, 0x80);
      blockAddr += 1536;
    }
    sizeClass -= 128 * chunksOver128;
  }
  // Tail-split + insert: figure out the right size-class queue for the
  // remaining block, optionally split off any leftover into a separate
  // freelist entry, then push the block onto its queue.
  biggerSizeClass = Units2Indx[sizeClass+3];
  biggerUnits = Indx2Units[biggerSizeClass];
  if (sizeClass != (uint)biggerUnits) {
    --biggerSizeClass;
    biggerUnits = Indx2Units[biggerSizeClass];
    deltaUnits = sizeClass - biggerUnits;
    BListPtr[deltaUnits - 1].linkNext((MEM_BLK*)(blockAddr + UNIT_SIZE*biggerUnits), deltaUnits);
  }
  BListPtr[biggerSizeClass].linkNext((MEM_BLK*)blockAddr, biggerUnits);
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

    // Context tracking begins immediately past the N_INDEXES allocator
    // free-list queues (N_INDEXES * UNIT_SIZE = 456 bytes).
    pText = (sqword)HeapStart + N_INDEXES*UNIT_SIZE;
    byte* heapEnd = (byte*)HeapStart + SubAllocatorSize;
    CutOffCount = 0;
    GlueCount = 0;

    // Dedicate a specific segment for unit state storage based on allocator metrics
    byte* unitsSegment = (byte*)HeapStart + SubAllocatorSize
                       - UNIT_SIZE * (MEM_DIVISOR-1) * (int)(SubAllocatorSize / (UNIT_SIZE*MEM_DIVISOR));
    UnitsStart = (sqword)unitsSegment;
    LoUnit = (sqword)unitsSegment;
    *(uint*)unitsSegment = 0;

    HeapNull = (sqword)heapBlocks - 1;

    // Initialize all 38 allocation queues to point to themselves symmetrically
    // (each queue starts empty: Next == Prev == Ptr2Indx(queue), QueueSize == 0).
    for (uint i = 0; i < N_INDEXES; ++i) {
      BListPtr[i].QueueSize = 0;
      BListPtr[i].Next = BListPtr[i].Prev = UNIT_SIZE * i + 1;
    }

    sqword allocatedContextAddr;
    if (heapEnd == unitsSegment) {
      if (!BListPtr[0].avail()) {
        allocatedContextAddr = AllocUnitsRare(0);
      } else {
        allocatedContextAddr = (sqword)BListPtr[0].unlinkPrev();
      }
    } else {
      heapEnd = (byte*)heapBlocks + allocatorSize - UNIT_SIZE;
      HiUnit = (sqword)heapEnd;
      allocatedContextAddr = (sqword)heapEnd;
    }

    // Establish structural properties for the Root Context block
    PPM_CONTEXT* rootCtxP = (PPM_CONTEXT*)allocatedContextAddr;
    rootCtxP->iSuffix = 0;                  // root has no suffix
    RootContext = allocatedContextAddr;
    rootCtxP->Flags = 0xC7;                 // -57 as byte
    MaxContext0 = allocatedContextAddr;
    rootCtxP->SummFreq = 256;

    sqword preferredIndex = (byte)b11;
    NMasked = 255;
    rootCtxP->NStates = 255;                // NStates+1 = 256 (all symbols)
    // Allocate the root context's STATE[] storage. HiUnit was just set to
    // heapEnd above, so AllocUnits_ uses the same boundary the inlined code
    // would have used.
    sqword stateStorageAddr = AllocUnits_((uint)preferredIndex);

    FoundState = (STATE*)stateStorageAddr;
    rootCtxP->iStates = Ptr2Indx(stateStorageAddr);
    MixCtx = 0;
    MixCtx2 = 0;
    MixCtx3 = 0;
    EscapeSymbol = 0;
    PrevSymbol = 0;

    // Initialize state fields across all 256 unique symbols
    STATE* states = (STATE*)((byte*)heapBlocks + rootCtxP->iStates - 1);
    for (int i = 0; i < 256; ++i) {
      states[i].Symbol     = (byte)i;
      states[i].Freq       = 1;
      states[i].iSuccessor = 0;
    }
    result = 1536;

    // Mode 2 triggers contextual tables updates bypassing the secondary SSE table clears
    if (mode != 2 || RunLength == -100) {
      runLengthInit = (MaxOrder >= 11) ? -11 : -MaxOrder;
      RunLength     = runLengthInit;

      memset(Sse2State, 0, sizeof(Sse2State));

      MixScale = 1024;
      Sse2BaseG = (sqword)Sse2State;
      FoundSymbol = -1;
      HashSeed1 = -1;
      HashSeed2 = -1;
      // 0x55 fill (not 0x00) gives the SSE/match cells a flat-prior shape:
      // most are subsequently read via small arithmetic that would produce
      // useless 0-probabilities at 0; 0x55... seeds them at the middle of
      // the dynamic range so the first Bayesian update is well-conditioned.
      memset(SseState2, 0x55u, 0x80000);
      memset(SseState3, 0x55u, 0x20000);

      memset((byte*)SEE2_5 + 112, 0x55, 1008);
      SseCtx0[3] = 0x55555555;

      memset(MatchPosTable, 0x55u, 0x40000);

      // BijectMap cells are 4 bytes each: (sym, prev1, prev2, count). Seed
      // sym/prev1/prev2 to (byte)i so every cell starts as a self-trigram
      // (the count, byte 3, stays at 0 from the global zero-init).
      for (int i = 0; i < 0x10000; ++i) {
        BijectMap[4 * i]     = i;
        BijectMap[4 * i + 1] = i;
        BijectMap[4 * i + 2] = i;
      }

      SymEpoch = 1;
      memset(MixWeight1, 0, 0x20000);
      memset(b16, 0, 0x20000);

      // Calculate predictor distributions for primary mix model spaces
      MixModel* mix1 = (MixModel*)MixWeight1;
      for (int outerIdx = 0; outerIdx < 0x4000; ++outerIdx) {
        int bitSum = PopCountWeighted_((uint)outerIdx, b17);
        for (int mixDimIdx = 0; mixDimIdx < 14; ++mixDimIdx) {
          int idx = (mixDimIdx + 1) * 0x4000 + outerIdx;
          InitMixCell_(mix1[idx], ClampMixWeight_(bitSum + (byte)b18[mixDimIdx]));
        }
        MixBound1[4 * outerIdx] = 1024;
        MixFreq1_1[4 * outerIdx] = 1024;
      }

      memset(d27, 0, 0x20000);
      memset(b19, 0, 0x20000);

      // Calculate distributions for secondary mix model spaces
      MixModel* mix2 = (MixModel*)&d27;
      for (int outerIdx2 = 0; outerIdx2 < 0x2000; ++outerIdx2) {
        int bitSum = PopCountWeighted_((uint)outerIdx2, b20);
        for (int mixDim2Idx = 0; mixDim2Idx < 24; ++mixDim2Idx) {
          int idx = 0x4000 + mixDim2Idx * 0x2000 + outerIdx2;
          InitMixCell_(mix2[idx], ClampMixWeight_(bitSum + (byte)b21[mixDim2Idx]));
        }
        MixBound4[4 * outerIdx2] = 1024;
        MixBound5[4 * outerIdx2] = 1024;
        MixBound6[4 * outerIdx2] = 1024;
        MixBound3[4 * outerIdx2] = 1024;
      }

      // Initialize the (mix3, mix4) wide-context mix tables with neutral
      // 50/50 prior (freq0 = freq1 = 2048, weight = 20480 = 5*4096).
      auto initFlatMixCell = [](MixModel& c) {
        c.weight = 20480;
        c.freq0  = 2048;
        c.freq1  = 2048;
      };
      MixModel* mix3 = (MixModel*)&MixWeight2;
      MixModel* mix4 = (MixModel*)&d29;
      for (int ctxBucket = 0; ctxBucket < 16; ++ctxBucket) {
        for (int mixCellIdx = 0; mixCellIdx < 1024; ++mixCellIdx)
          initFlatMixCell(mix3[ctxBucket * 0x400 + mixCellIdx]);
        for (int mixCellIdx2 = 0; mixCellIdx2 < 256; ++mixCellIdx2)
          initFlatMixCell(mix4[ctxBucket * 256 + mixCellIdx2]);
      }

      for (int contextSize = 0; contextSize < 5; ++contextSize) {
        int initialSseValue = 49 * (byte)b22[contextSize];
        for (int sseInitIdx = 0; sseInitIdx < 128; ++sseInitIdx) {
          BinSse[contextSize * 128 + sseInitIdx] = initialSseValue;
        }
      }

      // PredWeight init: 5 context-size buckets, 256 (num=baseWeight, den=15104)
      // pred-weight cells each.
      for (int contextSize2 = 0; contextSize2 < 5; ++contextSize2) {
        int baseWeight = 48 * (byte)b23[contextSize2];
        for (int predIdx = 0; predIdx < 256; ++predIdx) {
          int* cell = &PredWeight[contextSize2 * 512 + predIdx * 2];
          cell[0] = baseWeight;
          cell[1] = 15104;
        }
      }

      // Initialize each SSE cell-array (Sse1, SseMatch, Sse2, Sse3) to its
      // neutral starting prior: every 2-int cell becomes (num0, denInit).
      auto initSseCells = [](int* cells, sqword nCells, int num0, int denInit) {
        for (sqword i = 0; i < nCells; ++i) {
          cells[2 * i]     = num0;
          cells[2 * i + 1] = denInit;
        }
      };
      OrderCtxSeed = 0;
      initSseCells(Sse1,     196608,  0x2000, 24576);
      initSseCells(SseMatch, 0x100000, 0,     0x40000);
      SseSeed = 0;
      initSseCells(Sse2,     98304,   0,      0x40000);
      MixCtxExtra = 0;
      initSseCells(Sse3,     86016,   0,      0x80000);
      result = 86016;
    }
  } else { // Traversal fallback configuration for persistent run instances [cite: 147]
    result = RootContext;
    PPM_CONTEXT* rootP = (PPM_CONTEXT*)RootContext;
    if (rootP->iSuffix) {
      result = HeapNull;
      // Count the suffix chain depth (each ->getSuffix() step adds 1).
      for (PPM_CONTEXT* w = rootP->getSuffix(); ; w = w->getSuffix()) {
        ++suffixCount;
        if (!w->iSuffix) break;
      }
      OrderFall = suffixCount;
    }
    OrderFall0 = suffixCount;
  }
  return result;
}
//--- #return
//--- #include "subs_createsuccessors.inc"
sqword CreateSuccessors(int depth, STATE** chainStart, sqword seedCtx) {
  sqword heapNull = HeapNull;
  // Walk the CtxChain[] entries; each entry is a STATE*. We're looking for the
  // first entry whose state->iSuccessor differs from the head's, or the end of
  // the chain (suffix == 0).
  uint seedSuccIdx = (*chainStart)->iSuccessor;
  STATE** chainPtr = chainStart;
  while (1) {
    int curSuccIdx = (*chainPtr)->iSuccessor;
    if (curSuccIdx != seedSuccIdx) {
      seedCtx = HeapNull + curSuccIdx;
      goto LABEL_15;
    }
    uint ctxSuffixIdx = ((PPM_CONTEXT*)seedCtx)->iSuffix;
    ++chainPtr;
    if (!ctxSuffixIdx) goto LABEL_15;
    if ((qword)chainPtr >= CtxChainEnd) break;
    seedCtx = HeapNull + ctxSuffixIdx;
  }
  {
    STATE* foundStateB = FoundState;
    uint suffixIdx0 = ((PPM_CONTEXT*)seedCtx)->iSuffix;
    while (1) {
      sqword ctxAddr = heapNull + suffixIdx0;
      // Find the STATE for sym=FoundState->Symbol in this suffix context.
      PPM_CONTEXT* pc = (PPM_CONTEXT*)ctxAddr;
      STATE* state;
      if (pc->NStates) {
        int sym = foundStateB->Symbol;
        state = pc->getStates();
        while (state->Symbol != sym) state++;
      } else {
        state = &pc->oneState();
      }
      int stateSuccIdx = state->iSuccessor;
      if (stateSuccIdx != seedSuccIdx) { seedCtx = heapNull+stateSuccIdx; goto LABEL_15; }
      suffixIdx0 = pc->iSuffix;
      *chainPtr = state;
      ++chainPtr;
      if (!suffixIdx0) {
        seedCtx = ctxAddr;
        goto LABEL_15;
      }
    }
  }
LABEL_15:
  STATE** chainEnd = chainStart + depth;
  if( chainPtr==chainEnd )
    return (uint)(seedCtx-heapNull);
  int newCtxAddr = seedCtx;
  byte* baseCtxAddr = (byte*)(heapNull+seedSuccIdx);
  byte newSym   = *baseCtxAddr;
  byte newFlags = SSE0[newSym];
  int newCtxBytePos = Ptr2Indx(baseCtxAddr) + 1;
  STATE** chainPtrEnd = chainPtr;
  while (true) {
    PPM_CONTEXT* newCtx = AllocContext_();
    if (!newCtx) break;
    // Fresh binary context: NStates=0, SummFreq packs (Symbol=newSym, Freq=0).
    newCtx->NStates  = 0;
    newCtx->Flags    = newFlags;
    newCtx->SummFreq = newSym;
    newCtx->iStates = newCtxBytePos;
    newCtx->iSuffix = newCtxAddr - heapNull;
    newCtxAddr = (int)(uintptr_t)newCtx;
    sqword result = Ptr2Indx(newCtx);
    --chainPtrEnd;
    // Hook the new context into the chain entry above us: that entry's
    // STATE.iSuccessor now points at the freshly allocated context.
    (*chainPtrEnd)->iSuccessor = result;
    if (chainPtrEnd == chainEnd) return result;
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
sqword UpdateModel(PPM_CONTEXT* ctx, uint order) {
  uint         Order = order;

  // ---------------------------------------------------------------------------
  //  Single-state (NStates == 0) path
  // ---------------------------------------------------------------------------
  if (ctx->NStates == 0) {
    PPM_CONTEXT* succPtr = (PPM_CONTEXT*)Indx2Ptr(ctx->oneState().iSuccessor);
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
          STATE tmp = *p1;
          *p1 = *p;
          *p  = tmp;
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
          newFreq = (s < 3*f - 3);    // 1 if s < 3*f-3, else 0
        states[0].Freq = (byte)(newFreq + 1);

        p0 = &ctx->oneState();
        *p0 = states[0];
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
        PPM_CONTEXT* succPtr = (PPM_CONTEXT*)Indx2Ptr(sLast->iSuccessor);
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
    ctx = MoveContext_(ctx);
  return (sqword)(uint)Ptr2Indx(ctx);
}
//--- #return
//--- #include "subs_reduceorder.inc"

sqword ReduceOrder() {
  sqword rootCtxW, result, pTextEntry, heapNull, pTextNewSlot, maxCtxStart;
  sqword succIdx, succAddr, newStatesIdx2, allocedUnit, curCtx;
  sqword rootCtxSaveLab99, rootCtxSaveCS, rootCtxSaved;
  uint succIdxW, newByteIdx, curCtxSuffix;
  int orderFall, maxOrder, sym;
  STATE *foundStateB, *stateBW, *chainStatePtr;
  STATE **chainPtrW, **chainPtrSave;
  qword newStateEnd, ctxChainEndS;
  PPM_CONTEXT* ctxBW;
  char sse0Bit;
  byte foundSym;
  rootCtxW = RootContext;
  foundStateB = FoundState;
  orderFall = OrderFall;
  maxOrder = MaxOrder;
  succIdxW = foundStateB->iSuccessor;
  foundSym = foundStateB->Symbol;
  ctxBW = (PPM_CONTEXT*)RootContext;
  rootCtxSaved = RootContext;
  sse0Bit = SSE0[foundStateB->Symbol];
  if( OrderFall==MaxOrder&&succIdxW ) {
    uint succCreatedTop = CreateSuccessors(1, (STATE**)CtxChain, MaxContext0);
    foundStateB->iSuccessor = succCreatedTop;
    if( succCreatedTop ) {
      result = HeapNull+succCreatedTop;
      RootContext = result;
      MaxContext0 = result;
      return result;
    }
    goto LABEL_73;
  }
  pTextEntry = pText;
  heapNull = HeapNull;
  *(byte*)pText = foundStateB->Symbol;        // emit the symbol byte into the text buffer
  pTextNewSlot = pTextEntry+1;
  pText = pTextEntry+1;
  newByteIdx = pTextEntry+1-heapNull;
  if( pTextEntry+1>=(qword)UnitsStart )
    goto LABEL_73;
  *(byte*)(pTextEntry+1) = 0;
  if( !succIdxW ) {
    maxCtxStart = MaxContext0;
    ctxChainEndS = CtxChainEnd;
    sym = foundStateB->Symbol;
    rootCtxSaveCS = rootCtxW;
    curCtx = MaxContext0;
    chainPtrW = (STATE**)CtxChain;
    while( 1 ) {
      PPM_CONTEXT* pc = (PPM_CONTEXT*)curCtx;
      if( (qword)chainPtrW>=ctxChainEndS ) {
        // Find the STATE for sym in curCtx (or take its oneState if NStates==0).
        STATE* state;
        if (pc->NStates) {
          state = pc->getStates();
          while (state->Symbol != sym) state++;
        } else {
          state = &pc->oneState();
        }
        stateBW = state;
        *chainPtrW++ = stateBW;
      } else {
        stateBW = *chainPtrW++;
      }
      succIdxW = stateBW->iSuccessor;
      if( succIdxW )
        break;
      stateBW->iSuccessor = newByteIdx;
      curCtxSuffix = pc->iSuffix;
      OrderFall = --orderFall;
      if (!curCtxSuffix) {
        succIdxW = curCtx - heapNull;
        goto LABEL_9;
      }
      curCtx = heapNull+curCtxSuffix;
    }
    chainStatePtr = stateBW;
    chainPtrSave = chainPtrW;
    if( succIdxW<=newByteIdx ) {
      // newByteIdx is already pTextEntry+1-heapNull from function entry and
      // hasn't been clobbered; just call CreateSuccessors with the chain.
      succIdxW = CreateSuccessors(0, chainPtrSave-1, curCtx);
      chainStatePtr->iSuccessor = succIdxW;
    }
    if( orderFall==maxOrder-1&&maxCtxStart==rootCtxSaveCS ) {
      foundStateB->iSuccessor = succIdxW;
      succIdxW = chainStatePtr->iSuccessor;
      pTextNewSlot = pTextEntry;
      pText = pTextEntry;
    }
LABEL_9:
    if( succIdxW ) {
      succIdx = succIdxW;
      goto LABEL_11;
    }
LABEL_73:
    if( !CutOff )
      return StartModelRare(2);
    PPM_CONTEXT* rootCtxP1 = (PPM_CONTEXT*)rootCtxW;
    if (rootCtxP1->NStates == 1) {
      PPM_CONTEXT* parentCtx = ctxBW;
      if (parentCtx->NStates == 0 && rootCtxP1 != ctxBW) {
        // Walk every PPM_CONTEXT from rootCtxSaved up to ctxBW, collapsing
        // each one's 2-STATE[] block down to a single oneState. The kept state
        // is the one whose Symbol matches the parent's oneState.Symbol -- if
        // states[0] mismatches, take states[1] instead.
        sqword ctxSaved = rootCtxW;
        byte parentSym = parentCtx->oneState().Symbol;
        PPM_CONTEXT* walker = (PPM_CONTEXT*)rootCtxSaved;
        do {
          STATE* states = walker->getStates();
          STATE* kept   = &states[states[0].Symbol != parentSym];
          walker->Flags = SSE0[kept->Symbol];
          kept->Freq = (byte)(((uint)kept->Freq + 3) >> 2);
          walker->oneState().Symbol      = kept->Symbol;
          walker->oneState().Freq        = kept->Freq;
          walker->oneState().iSuccessor  = kept->iSuccessor;
          walker->NStates                = 0;
          FreeUnitsRare((sqword)states, 1);
          walker = walker->getSuffix();
        } while (walker != ctxBW);
        rootCtxW = ctxSaved;
      }
    }
    // Walk the suffix chain down to the order-(-1) context (iSuffix == 0).
    PPM_CONTEXT* rootCtxP = (PPM_CONTEXT*)rootCtxW;
    if (rootCtxP->iSuffix) {
      while (rootCtxP->iSuffix) rootCtxP = rootCtxP->getSuffix();
      rootCtxW = (sqword)rootCtxP;
      RootContext = rootCtxW;
    }
    result = UpdateModel(rootCtxP, 0);
    ++GlueCount;
    CutOffCount = 0;
    pText = BList + N_INDEXES*UNIT_SIZE;
    MaxContext0 = rootCtxW;
    OrderFall = 0;
    return result;
  }
  maxCtxStart = MaxContext0;
  succIdx = succIdxW;
  if( (qword)UnitsStart > heapNull+(qword)succIdxW ) {
    succIdxW = CreateSuccessors(0, (STATE**)CtxChain, MaxContext0);
    goto LABEL_9;
  }
LABEL_11:
  succAddr = heapNull + succIdx;
  {
    PPM_CONTEXT* succCtx = (PPM_CONTEXT*)succAddr;
    OrderFall = orderFall + 1;
    if (OrderFall == maxOrder) {
      newByteIdx = succIdxW;
      pText = pTextNewSlot - (rootCtxW != maxCtxStart);
    }
    result = succCtx->iStates;
  }
  if( rootCtxW!=maxCtxStart ) {
    int escIdx = EscIndexSeed+8;
    rootCtxSaveLab99 = rootCtxW;
    if (escIdx >= 14) escIdx = 14;
    if (escIdx <  0) escIdx = 0;
    char sse0BitSaved = sse0Bit;
    sqword escIdxClipped = escIdx;
    uint succIdxSaved = newByteIdx;
    while( 1 ) {
      PPM_CONTEXT* curCtxP = ctxBW;
      uint nStatesP1 = curCtxP->NStates + 1;
      if (curCtxP->NStates) {
        if ((nStatesP1 & 1) != 0) {
          newStatesIdx2 = curCtxP->iStates;
        } else {
          uint* statesPtr = (uint*)(heapNull + curCtxP->iStates);
          uint halfNStatesP1 = nStatesP1 >> 1;
          uint sizeClassP = Units2Indx[halfNStatesP1 + 3];
          if (sizeClassP != Units2Indx4[halfNStatesP1]) {
            sqword sizeClass4P = Units2Indx4[halfNStatesP1];
            uint* newStatesPtr = (uint*)AllocUnits_((uint)sizeClass4P);
            // AllocUnits_ may have called AllocUnitsRare which clobbers sizeClassP;
            // recompute (matches the inlined pattern's restoration).
            sizeClassP = Units2Indx[halfNStatesP1 + 3];
            if (newStatesPtr) {
              // Copy nStatesP1/2 units (each = 2 STATEs) from the old block to
              // the new one, then free the old block.
              UnitsCpy_(newStatesPtr, statesPtr, nStatesP1 >> 1);
              FreeUnitsRare((sqword)statesPtr, (uint)Indx2Units[sizeClassP]);
            }
            statesPtr = newStatesPtr;
          }
          if (!statesPtr) goto LABEL_99;
          newStatesIdx2 = Ptr2Indx(statesPtr);
          curCtxP->iStates = newStatesIdx2;
        }
        newStateEnd = newStatesIdx2 + heapNull + 6LL*nStatesP1;
        if (newStateEnd > heapNull + newStatesIdx2 + 42) {
          // Shift STATEs back by one slot to make room for the new tail STATE.
          STATE* dst = (STATE*)newStateEnd;
          do {
            *dst = dst[-1];
            --dst;
          } while ((qword)dst > heapNull + (qword)curCtxP->iStates + 42);
          newStateEnd = (qword)dst;
        }
      } else {
        allocedUnit = AllocUnits_(Units2Indx4[0]);
        if( !allocedUnit ) {
LABEL_99:
          rootCtxW = rootCtxSaveLab99;
          goto LABEL_73;
        }
        // Promote NStates==0 binary context to NStates==1: copy the existing
        // oneState into allocedUnit (becomes STATE[0]), then bump its Freq.
        STATE* newStates = (STATE*)allocedUnit;
        *newStates = curCtxP->oneState();
        int freqBoost = b24[escIdxClipped];
        curCtxP->iStates = Ptr2Indx(allocedUnit);
        int newStateFreq = 4 * (int)newStates->Freq + freqBoost;
        if (newStateFreq >= 238) newStateFreq = 238;
        if (newStateFreq <   2)  newStateFreq = 2;
        newStates->Freq = (byte)newStateFreq;
        newStateEnd = allocedUnit + 6;
        curCtxP->SummFreq = (byte)newStateFreq;
      }
      // Initialize the new tail STATE: Symbol=foundSym, Freq=0,
      // iSuccessor=succIdxSaved.
      STATE* tailState = (STATE*)newStateEnd;
      tailState->Symbol     = foundSym;
      tailState->Freq       = 0;
      tailState->iSuccessor = succIdxSaved;
      char upperFlagBits = curCtxP->Flags & 0xF0;
      sqword statesBaseAddr = heapNull + curCtxP->iStates;
      ++curCtxP->NStates;
      sqword stateByteOff = newStateEnd - statesBaseAddr;
      result = 0x2AAAAAAAAAAAAAABLL * stateByteOff;
      curCtxP->Flags = sse0BitSaved | (stateByteOff / 6) | upperFlagBits;
      ctxBW = curCtxP->getSuffix();
      if (ctxBW == (PPM_CONTEXT*)maxCtxStart) {
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

// helper 3aa: 4-byte BijectMap cell shift-insert.
//   bm = { byte sym, byte prev1, byte prev2, byte count }
// If newSym matches the head, bump count (saturating at 255). Otherwise
// shift prev1->prev2, sym->prev1, and write newSym to head with count=0.
inline void BijectCellInsert_(byte* bm, byte newSym) {
  if (newSym == bm[0]) {
    bm[3] += (bm[3] < 255);   // saturating +1 on the count byte
  } else {
    bm[2] = bm[1];
    bm[1] = bm[0];
    bm[0] = newSym;
    bm[3] = 0;
  }
}

// helper 3a: when any Sse2State histogram cell hits the saturation
// threshold (0xA7 = 167), halve every entry in the 512-byte block and
// rebuild the counter at byte offset 512 as the sum of all halves.
inline void HalveSse2Histogram_(byte* sse2Base, uint* counter) {
  *counter = 0;
  for (sqword j = 0; j < 512; ++j) {
    int halved = sse2Base[j] >>= 1;
    *counter += halved;
  }
}

// helper 3b: walk MatchPosPrev chain backwards from (symEpoch-2), pulling
// consensus hints out of MatchPosHash at fixed offsets. Up to three "ticks"
// are read directly (h1, h2, h3); subsequent ticks are folded into the same
// (h1 &=, h2 |=) accumulators inside the m2_bias loop until age > 0x20000.
// Writes:
//   hintSymM2  := first-tick hash byte (used in MixUpdate's later sse2 lookup)
//   SymLastCtx2[tick]  := sc at every visited tick
//   MatchPosBySym[h1]  := sc if h1 and h2 agree (consensus)
//   HashSeed1/HashSeed2 := promoted if consensus reaches 3+ ticks
inline void WalkM2Consensus_(int symEpoch, uint symEpochN, int sc) {
  int m2_prev1 = MatchPosPrev[(symEpoch-2) & 0x1FFFF];
  if ((uint)(symEpochN-m2_prev1) >= 0x20000) return;
  int    m2_h1 = (byte)MatchPosHash[(m2_prev1+3) & 0x1FFFF];
  hintSymM2 = m2_h1;
  SymLastCtx2[m2_h1] = sc;
  int m2_prev2 = MatchPosPrev[m2_prev1 & 0x1FFFF];
  if ((uint)(symEpochN-m2_prev2) >= 0x20000) return;
  int m2_h2 = (byte)MatchPosHash[(m2_prev2+3) & 0x1FFFF];
  SymLastCtx2[m2_h2] = sc;
  if (m2_h1 == m2_h2)
    MatchPosBySym[m2_h1] = sc;
  int m2_h3 = -1;
  int    m2_prev3 = MatchPosPrev[m2_prev2 & 0x1FFFF];
  if ((uint)(symEpochN-m2_prev3) < 0x20000) {
    int m2_bias = 0;
    do {
      m2_bias += 6144;
      m2_h3 = (byte)MatchPosHash[(m2_prev3+3) & 0x1FFFF];
      SymLastCtx2[m2_h3] = sc;
      m2_h1 &= m2_h3;
      m2_h2 = m2_h3 | m2_h2;
      m2_prev3 = MatchPosPrev[m2_prev3 & 0x1FFFF];
    } while ((uint)(m2_bias+symEpochN-m2_prev3) < 0x20000);
  }
  if (m2_h1 == m2_h2 && m2_h3 >= 0) {
    if (HashSeed2 < 0)
      HashSeed2 = m2_h1;
    else if (HashSeed2 == m2_h1)
      HashSeed1 = m2_h1;
  }
}

// helper 4ba: walk the RecentPos chain backwards starting at `recentEpoch`
// and stamp SymLastCtx2 with MatchPosHash bytes at each hop. Walk stops
// after at most 192 hops or once the chain age (symEpoch - rp) exceeds
// the running counter.
inline void WalkRecentPosChain_(int recentEpoch, int symEpoch, int sc) {
  int rp = RecentPos[recentEpoch & 0xFFF];
  if ((uint)(symEpoch - rp) >= 0xC0) return;
  uint cnt = 192;
  do {
    --cnt;
    SymLastCtx2[(byte)MatchPosHash[(rp+1) & 0x1FFFF]] = sc;
    rp = RecentPos[rp & 0xFFF];
  } while (cnt > symEpoch - rp);
}

// helper 4c: emit hint stamps around two predicted bytes (predA, predB).
// Used by MixUpdate's b1/b2/b3 prediction ladder when the third-difference
// (b1+b3-2*b2) is non-zero — the two surrounding bytes get +/-1, +/-2
// stamps in the appropriate SymLastCtx / MatchPosBySym banks.
inline void EmitDeltaPredictionHints_(byte predA, byte predB, int sc) {
  SymLastCtx[(byte)(predB+2)]    = sc;
  SymLastCtx[(byte)(predB-2)]    = sc;
  SymLastCtx[(byte)(predB+1)]    = sc;
  SymLastCtx[predB]              = sc;
  SymLastCtx2[(byte)(predA+2)]   = sc;
  MatchPosBySym[(byte)(predA-2)] = sc;
  MatchPosBySym[(byte)(predA+1)] = sc;
  MatchPosBySym[(byte)(predA-1)] = sc;
  MatchPosBySym[predA]           = sc;
}

// helper 4d: emit hint stamps around a single predicted byte. Used by
// MixUpdate's b1/b2/b3 ladder when the third-difference is zero (the
// predictor agrees on a single byte: pred = 2*b1 - b2).
inline void EmitFlatPredictionHints_(byte pred, int sc) {
  SymLastCtx[(byte)(pred+1)] = sc;
  SymLastCtx[(byte)(pred-1)] = sc;
  SymLastCtx[(byte)(pred+2)] = sc;
  SymLastCtx[(byte)(pred-2)] = sc;
  MatchPosBySym[(byte)(pred+1)] = sc;
  MatchPosBySym[(byte)(pred-1)] = sc;
  MatchPosBySym[pred]           = sc;
}

// helper 3ab: BijectMap trigram-consensus prediction.
//
// Inspects the three recent symbols at MixScale strides (b1/b2/b3 = newest .. older)
// plus a 5-stride history window via bmPtr, and bmCell (the 4-byte BijectMap row).
// May resolve FoundSymbol; in all branches sets PrevSymbol = predGuessSym.
// Mutates globals PrevSymbol, FoundSymbol, MatchPosBySym, SymLastCtx2.
inline void BijectTriPrediction_(uint b1, uint b2, int b3,
                                 char* bmPtr, int mixScale,
                                 const byte* bmCell, int sc, int predGuessSym) {
  if (b1 == b2 && b2 == b3) {
    PrevSymbol = predGuessSym;
    FoundSymbol = b1;
    MatchPosBySym[(byte)(b1+1)] = sc;
    SymLastCtx2 [(byte)(b1-1)] = sc;
  } else if (FoundSymbol < 0) {
    if (b1 == b2 || b2 == b3) {
      PrevSymbol = predGuessSym;
      FoundSymbol = b1;
      SymLastCtx2 [(byte)(b3+1)] = sc;
      MatchPosBySym[(byte)(b1+1)] = sc;
      SymLastCtx2 [(byte)(b1-1)] = sc;
      MatchPosBySym[b3]          = sc;
    } else if (b1 == b3) {
      PrevSymbol = predGuessSym;
      if (b2 == (byte)bmPtr[-4*mixScale] && (byte)bmPtr[-5*mixScale] == b3)
        b1 = b2;
      FoundSymbol = b1;
      MatchPosBySym[b2] = sc;
    } else {
      char predDelta = b1 + b3 - 2*b2;
      if (predDelta) {
        PrevSymbol = predGuessSym;
        if (bmCell[3] <= 0x10u) {
          if ((byte)(predDelta+19) <= 0x26u) {
            byte predA = 2*b1 - b2;
            byte predB = predA - predDelta;
            EmitDeltaPredictionHints_(predA, predB, sc);
          }
        } else {
          FoundSymbol = bmCell[0];
        }
      } else {
        FoundSymbol = (byte)(2*b1 - b2);
        PrevSymbol  = FoundSymbol;
        EmitFlatPredictionHints_(FoundSymbol, sc);
      }
    }
  } else {
    PrevSymbol = predGuessSym;
  }
}

// helper 4b: derive the (matchHashSy, matchPosAge, matchEpoch2) triple from
// a MatchPosTable hit. If the entry is older than 0x20000 epochs, all three
// outputs saturate to 0x20000. Otherwise we hash through MatchPosHash and
// follow one MatchPosTable indirection to the second epoch.
inline void ComputeMatchHints_(int matchTblHit, uint sym) {
  if ((uint)(SymEpoch-matchTblHit) >= 0x20000) {
    matchEpoch2 = 0x20000;
    matchPosAge = 0x20000;
    matchHashSy = 0x20000;
  } else {
    matchHashSy = (byte)MatchPosHash[(matchTblHit+2) & 0x1FFFF];
    matchPosAge = SymEpoch - matchTblHit;
    matchEpoch2 = SymEpoch - MatchPosTable[256*sym + matchHashSy];
  }
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
//   Find `sym` in `states`; bubble it up while its saved freq + `margin` <=
//   prev.freq, stopping at/above rank 7. Record resulting rank in the low
//   nibble of *flagsByte. Returns the STATE* of the new slot.
inline STATE* FindAndBubble7_(STATE* states, byte sym, byte* flagsByte, int margin) {
  STATE* p = states;
  if (p->Symbol == sym) return p;
  do { ++p; } while (p->Symbol != sym);
  STATE saved = *p;
  STATE* stopAt7 = states + 7;
  while (true) {
    bool stable = (p <= states) || ((int)saved.Freq + margin <= (int)(p - 1)->Freq);
    if (stable && p <= stopAt7) {
      *p = saved;
      *flagsByte |= (byte)(p - states);
      return p;
    }
    *p = *(p - 1);
    --p;
  }
}

// Both the deep and trail walks in MixUpdate's suffix loop need to refresh
// a context's STATE[] view if rank-0 is empty: stash chainEnd into the
// global CtxChainEnd, call BinEscFreq, re-read iStates/Flags. Pulls the
// 7-line pattern into a single inline.
inline void RefreshIfRank0Empty_(PPM_CONTEXT* ctx, sqword& idx, byte& flags,
                                  STATE*& states, sqword chainEnd) {
  if (states[flags & 0xF].Freq == 0) {
    CtxChainEnd = chainEnd;
    BinEscFreq(ctx);
    idx    = ctx->iStates;
    flags  = ctx->Flags;
    states = (STATE*)Indx2Ptr(idx);
  }
}

qword MixUpdate(PPM_CONTEXT* minCtx) {
  // ---- per-step state ------------------------------------------------------
  // ---- symbol-derived state -----------------------------------------------
  int    mixCtxOld;        // MixCtx (saved before being used in SseSeed)
  int    recentEpoch;      // SseCtx0_1[sym] before update
  int    dt;               // symEpoch - recentEpoch

  // ---- MatchPosTable update ------------------------------------------------
  int    matchScore;       // 3-bit composite folded into OrderCtxSeed

  // ---- context-suffix walk -------------------------------------------------
  int      ofall;          // tracks OrderFall through the function
  qword    result;

  byte   newFoundFreq;     // do-while loop output, read in loop guard

  // shallow (trailing) find-and-bubble path
  sqword trailStatesIdx;
  byte   trailFlags;
  STATE* trailStates;
  int    trailBound;       // gating cutoff in trailing loop

  int prevSymCount = SymCount;
  int sc           = SymCount - 1;
  SymCount         = sc;
  // Commit binMixCenter's predExpand counter (word[3]) into its uint accumulator.
  {
    word* binMixCenter = (word*)BinMixCenterG;
    *(uint*)binMixCenter += binMixCenter[3];
  }
  // ---- Section 1: simple additive predictor-weight updates -----------------
  // Each pair-target gets a numerator/denominator pair-update; the singles
  // get a single += of the captured per-step delta.
  uint* wBinMixHi  = (uint*)BinMixHiG;
  uint* wBinMixLo  = (uint*)BinMixLoG;
  uint* wPredBaseA = (uint*)PredBaseAG;
  uint* wPredBaseB = (uint*)PredBaseBG;
  uint* wSseMatch  = (uint*)SseMatchSlotG;
  uint* wSse1      = (uint*)Sse1SlotG;
  *wBinMixHi  += binMixDeltaHi;
  *wBinMixLo  += binMixDeltaLo;
  *wPredBaseA += predBaseDeltaA;
  *wPredBaseB += predBaseDeltaB;
  *wSse1      += sse2NumDelta;       wSse1[1]     -= sse2DenDelta;
  *wSseMatch  += sseMatchNumDelta;   wSseMatch[1] -= sseMatchDenDelta;

  int   symEpoch = SymEpoch;
  // 0x20000 + (symEpoch & 0x1FFFF) selects a byte in MatchPosHash's upper half.
  char* sseSlot  = (char*)&MatchPosHash[0x20000 + (symEpoch & 0x1FFFF)];

  // ---- Section 2: weight-pair updates with overflow-driven halving --------
  UpdateWeightPair_((int*)Sse2SlotG, predWeightDelta + predSseTotDelta, 2 * sseCum);
  UpdateWeightPair_((int*)Sse3SlotG, predWeightDelta,                   sseCum);

  STATE* foundState = FoundState;
  SparseBitmapA[SparseIdxA] |= SparseBit;
  SparseBitmapB[SparseIdxB] |= SparseBit;
  uint   sym     = foundState->Symbol;
  sqword matchHi = (qword)MatchCtxHi;
  SseState3[sseState3Hash] = sym;
  // Write sym at both halves of MatchPosHash. sseSlot points to the upper
  // half at (0x20000 + (symEpoch & 0x1FFFF)); -0x20000 wraps to the lower
  // half at the same modular offset.
  MatchPosHash[symEpoch & 0x1FFFF] = sym;        // lower half (= sseSlot-0x20000)
  *sseSlot                         = sym;        // upper half
  recentSym = sym;
  MatchCtxHi = sym;
  sseState3Hash = (sym+(sseState3Hash<<6))&0x1FFFF;
  if (FoundSymbol >= 0 && FoundSymbol != MixCtx3)
    // shift-left-1 and push the (sym==FoundSymbol) consensus bit at bit 0
    foundSymHist = (foundSymHist << 1) | (sym == FoundSymbol);
  b31KeyPrev = b31Key;
  order1CtxSaved = Order1Ctx;
  // SparseHashA folds (matchHi, sym) into a 14-bit hash for SparseBitmapA[].
  // Both inputs are masked to ~7 (top 5 bits of each octet) and shifted into
  // disjoint windows: matchHi at bit 13 (= 10+3), sym at bit 5 (= 5+0).
  SparseHashA = ((matchHi & ~7u) << 10) + ((sym & ~7u) << 5);
  mixCtxOld = MixCtx;
  uint sse0sym = SSE0[sym];
  RunLength += MixCtx;
  SparseHashB = (8*(sym+SparseHashB))&0xFFF00;
  recentEpoch = SseCtx0_1[sym];
  int mixCtx2New = MixCtx2+MixCtx2+(sse0sym>>7);
  MixCtx2 = mixCtx2New;
  RecentPos[symEpoch & 0xFFF] = recentEpoch;
  SseCtx0_1[sym] = symEpoch;
  dt = symEpoch-recentEpoch;
  if ((uint)dt >= 0x104) {
    b31Key = 0;
    hintSymRecent = -1;
  } else {
    int hashByte = (byte)MatchPosHash[(recentEpoch+1)&0x1FFFF];
    hintSymRecent = hashByte;
    if (dt >= 50) hashByte = 0;
    b31Key = hashByte;
    WalkRecentPosChain_(recentEpoch, symEpoch, sc);
  }
  sqword matchKey = sym + (matchHi << 8);
  int    matchPrev = MatchPosTable[matchKey];
  MatchPosPrev[(symEpoch-1)&0x1FFFF] = matchPrev;
  MatchPosTable[matchKey] = symEpoch-1;
  uint   matchDelta = symEpoch-matchPrev;
  // 3-bit composite at bit 13: counts how many of these proximity tests pass.
  matchScore = SseIdx{}
    .bits<13, 2>((matchDelta < 0xE800)
               + (matchDelta < 0xF0)
               + (matchDelta < 7));
  int predGuessSym = 0;
  if( matchDelta>=0x1000 ) {
    Order1Ctx = 0;
    matchHintByte = -1;
  } else {
    Order1Ctx = predGuessSym = (byte)MatchPosHash[(matchPrev+2)&0x1FFFF];
    matchHintByte = (byte)MatchPosHash[(MatchPosPrev[matchPrev&0x1FFFF]+2)&0x1FFFF];
    if (predGuessSym == matchHintByte) {
      MatchPosBySym[predGuessSym] = sc;
    }
    if( matchDelta>=0x240 )
      predGuessSym = 0;
  }
  q12BaseSel *= 2;
  char newQ12Sel = q12BaseSel;
  if (sym != RSContext) {
    byte* sse2Base = (byte*)Sse2BaseG;
    uint* counter = (uint*)(sse2Base + 512);
    *counter += 2;
    sqword sseHistOff = ((word)sym - (word)RSContext) & 0x1FF;
    byte newHistCnt = sse2Base[sseHistOff] + 2;
    sse2Base[sseHistOff] = newHistCnt;
    if (newHistCnt > 0xA7u)
      HalveSse2Histogram_(sse2Base, counter);
    newQ12Sel = ++q12BaseSel;
    if( sym!=order1CtxSaved ) {
      b27[RSContext+(order1CtxSaved<<8)] = sym;
      newQ12Sel = q12BaseSel;
    }
  }
  Sse2BaseG = (sqword)&Sse2State[516*(newQ12Sel&3)];
  int recentForHi = SseCtx0_1[matchHi];
  if (sym == FoundSymbol && MixScale <= 256) {
    mixScaleCntr = 4 * MixScale;
  } else if (mixScaleCntr > (uint)(3 * MixScale)
          && (prevSymCount == SymLastCtx[sym]
           || prevSymCount == SymLastCtx2[sym]
           || (uint)mixScaleCntr > 4 * MixScale - 9)) {
    mixScaleCntr -= MixScale > 13;
  } else if (dt > 1) {
    int rp1 = RecentPos[recentEpoch&0xFFF];
    // First test: does RecentPos[sym] form a dt-stride progression, with dt small?
    if (dt == recentEpoch - rp1 && dt == rp1 - RecentPos[rp1&0xFFF] && dt <= 256) {
      // Second test: sym repeats at 4*dt stride in the history, OR the matchHi
      // RecentPos chain also forms a dt-stride progression AND matchHi appears
      // at the -3*dt-1 offset.
      int rp2 = RecentPos[recentForHi & 0xFFF];
      bool symAt4Dt = (sym == (byte)sseSlot[-4*dt]);
      bool hiTriad  = (dt == recentForHi - rp2)
                   && (dt == rp2 - RecentPos[rp2 & 0xFFF])
                   && ((uint)matchHi == (byte)sseSlot[-3*dt - 1]);
      if (symAt4Dt || hiTriad) {
        MixScale = dt;
        mixScaleCntr = dt;
        bijectCellPtr = (sqword)&bijectCellSink;
      }
    }
  }
  hintSymB31 = -1;
  hintSymM2 = -1;
  hintSymB29 = -1;
  hintSymMatch3 = -1;
  hintSymBmCell = -1;
  HashSeed1 = -1;
  int bdiff = (byte)(sym-matchHi);
  HashSeed2 = -1;
  int symEpochN = symEpoch + 1;
  SymEpoch      = symEpochN;
  FoundSymbol = -1;
  if( bdiff==bdiffSaved ) {
    if( (uint)++ bdiffStickyCnt>1 ) {
      FoundSymbol = predGuessSym = (byte)(2*sym-matchHi);
      goto LABEL_94;
    }
  } else {
    bdiffStickyCnt = 0;
    // Save bdiff but turn 0 into -1 so the next "bdiff == bdiffSaved"
    // comparison can never spuriously match a fresh zero start.
    bdiffSaved = (bdiff == 0) ? -1 : bdiff;
  }
  {
  int  ssem3  = (byte)*(sseSlot-3);
  int  ssem7  = (byte)*(sseSlot-7);
  char ssem11 = *(sseSlot-11);
  // Run the hint cascade when the recent-symbol history fails the
  // "arithmetic progression" test: either the period-4 step matches
  // (ssem3==ssem7), or the period-4 differencing at offsets {-11,-7,-3}
  // or {-15,-11,-7} has a non-zero byte residue.
  byte progResid1 = (byte)(ssem11 + ssem3 - 2*ssem7);
  byte progResid2 = (byte)(*(sseSlot-15) + ssem7 - 2*ssem11);
  if (ssem3==ssem7 || progResid1 || progResid2) {
    if( 4*MixScale-1>(uint)mixScaleCntr ) {
      // SIX MatchPosPrev hash-chain hint computations (offsets 3,4,5,8 wide
      // window; 6,10 short window with compact second arm).
      hintSymMatch3 = MatchPosHint_  (3, symEpoch, symEpochN, sc);
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
      hintSymB29 = HashArmUpdate_(b29, 256*sm0 + sm7, 256*sm1 + sm8, sym, sc);
      HashArmUpdate_(b30,       256*sm1 + sm7, 256*sm2 + sm8, sym, sc);

      // b31 arm uses a different routing (no collision branch, SymLastCtx only)
      uint b31_ri = (uint)(Order1Ctx + (b31Key << 8));
      hintSymB31 = (byte)b31[b31_ri];
      SymLastCtx[hintSymB31] = sc;
      if (sym != b31KeyPrev && sym != order1CtxSaved) b31[order1CtxSaved + (b31KeyPrev << 8)] = sym;

      // final independent hint from RecentPos chain: stamp vh at sc in
      // SymLastCtx, then (if it was already in SymLastCtx) escalate to
      // SymLastCtx2 too.
      byte vh = MatchPosHash[(RecentPos[SseCtx0_1[matchHi] & 0xFFF] + 2) & 0x1FFFF];
      if (sc == SymLastCtx[vh]) SymLastCtx2[vh] = sc;
      else                      SymLastCtx [vh] = sc;
    }
  } else {
    FoundSymbol = predGuessSym = (byte)(2*ssem3-ssem7);
  }
  }
LABEL_94:
  WalkM2Consensus_(symEpoch, symEpochN, sc);
  // three paired byte-hash predictor updates (b32/b33, b34/b35, b36/b37).
  // Each reads at a "new" index and writes back at a different "old" index.
  qword  epochBit    = (symEpochN&1)==0;
  int    savedD90Idx = d90[epochBit];                                       // saved idx (current parity)
  sqword newD90Idx   = (word)(16*(word)d90[epochBit]+((sym>>2)&0xFFFC))&0xFFFC;
  d90[epochBit] = newD90Idx;
  uint oldD90Idx = (uint)d90[!epochBit];     // BijectPairUpdate_ doesn't touch d90, so this is reused below
  hintSymBiject = (byte)b33[newD90Idx];      // capture before BijectPairUpdate_ writes
  BijectPairUpdate_(b32, b33, /*read*/newD90Idx, /*write*/oldD90Idx, sym, sc);

  {
    uint   savedD91 = (uint)symHalfHistory;
    sqword newD91   = (word)(((sym>>4)&0xFFFE)+8*symHalfHistory)&0xFFFE;
    BijectPairUpdate_(b35, b34, /*read*/newD91, /*write*/savedD91, sym, sc);
    symHalfHistory = newD91;
  }

  BijectPairUpdate_(b36, b37, /*read*/oldD90Idx, /*write*/savedD90Idx, sym, sc);
  if (mixScaleCntr) {
    BijectCellInsert_((byte*)bijectCellPtr, sym);
    char* bmPtr = sseSlot + 1;
    uint b1 = (byte)bmPtr[-MixScale];
    uint b2 = (byte)bmPtr[-2*MixScale];
    int  b3 = (byte)bmPtr[-3*MixScale];
    if( --mixScaleCntr>(uint)MixScale )
      recentSym = b1;
    char* b1Ptr = &bmPtr[-MixScale];     // history at -1 stride
    char* b2Ptr = &bmPtr[-2*MixScale];   // history at -2 strides
    int   bm1 = (byte)*(b1Ptr-1);
    // bmComposite indexes the 4-uint BijectMap row; the bitfield mixes:
    //   bits  8-13 : raw   (b2 & 0x2E) plus a same-direction prediction bit
    //   bit  12    : history-match flag (same 3rd byte at the two offsets)
    //   bits 14-16 : 3-bit count of "sym near bm1" comparisons
    sqword bmComposite = SseIdx{}
      .bits <8, 6>((b2 & 0x2E) + ((byte)b2Ptr[1] < (uint)(byte)b1Ptr[1]))
      .bit  <12>  (b1Ptr[2] == b2Ptr[2])
      // 0..3 score by sym's position relative to bm1: 0 (sym<bm1),
      // 1 (sym==bm1), 2 (bm1<sym≤bm1+32), 3 (sym>bm1+32).
      .bits <14, 3>((sym > (uint)(bm1 + 32)) + (sym > (uint)bm1) + ((int)sym >= bm1));
    bijectCellPtr = (sqword)&BijectMap[4*bmComposite + 4*b1];
    byte* bmCell = (byte*)bijectCellPtr;       // 4-byte cell: sym/prev1/prev2/count
    SymLastCtx[(byte)bmCell[2]] = sc;
    SymLastCtx[bmCell[1]]       = sc;
    SymLastCtx[bmCell[0]]       = sc;
    hintSymBmCell = bmCell[0];
    if (bmCell[3]) {
      if (bmCell[3] > 1u || hintSymRecent <= 0)
        hintSymRecent = bmCell[0];
      MatchPosBySym[bmCell[0]] = sc;
    }
    BijectTriPrediction_(b1, b2, b3, bmPtr, MixScale, bmCell, sc, predGuessSym);
  } else {
    PrevSymbol = predGuessSym;
    MixScale = 1024;
    if( FoundSymbol<0 )
      FoundSymbol = HashSeed1;
  }
  ofall = OrderFall;
  CtxChain[0] = (sqword)foundState;
  // OrderCtxSeed bitfield:
  //   bit  9     : recentSym's bit-7 (sym was in the >= 0x80 char class)
  //   bits 13-14 : matchScore (proximity-test count, already shifted)
  //   bit  15    : OrderFall > 0
  OrderCtxSeed = SseIdx{}
    .bit  <9> (recentSym & 0x80)
    .raw  ((uint)matchScore)
    .bit  <15>(OrderFall > 0);
  int minNStates = minCtx->NStates;
  NMasked = minNStates;
  int searchSym = foundState->Symbol;
  uint minISuffix = minCtx->iSuffix;
  // SseSeed bitfield:
  //   raw   : BinMapTable[mixCtx2New & 0xF]  (low-order bits feed the binary
  //           mix-cell address)
  //   bit 14+: mixCtxOld at bit 14
  //   bit 15 : OrderFall > 0
  //   bit 15 : OrderFall > 2  (additional contribution; carries into bit 16)
  SseSeed = SseIdx{}
    .raw  (BinMapTable[mixCtx2New & 0xF])
    .raw  ((uint)mixCtxOld << 14)
    .bit  <15>(OrderFall > 0)
    .bit  <15>(OrderFall > 2);
  sqword* chain = &CtxChain_1;
  // MixCtxExtra: constant bit 6, plus a 3-bit count of OrderFall thresholds
  // at bits 12-14.
  MixCtxExtra = SseIdx{}
    .bit  <6> (true)
    .bits <12, 3>((OrderFall>32) + (OrderFall>8) + (OrderFall>4)
                + (OrderFall>3)  + (OrderFall>2) + (OrderFall>1));
  if (minISuffix) {
    PPM_CONTEXT* walkCtx = (PPM_CONTEXT*)Indx2Ptr(minISuffix);
    int depthLeft = OrderFall;
    if (walkCtx->NStates == 0) {
      do {
        if (chain > &CtxChain_2[1]) {
          STATE* prevSt = (STATE*)*(chain - 2);
          prevSt->Freq += (prevSt->Freq < 2);   // +1 if Freq is 0 or 1
        }
        STATE* onestatePtr = &walkCtx->oneState();
        sqword fastSuffix  = walkCtx->iSuffix;
        *chain++ = (sqword)onestatePtr;
        --depthLeft;
        walkCtx = (PPM_CONTEXT*)Indx2Ptr(fastSuffix);
      } while (walkCtx->NStates == 0);
      if (ofall < MaxOrder) {
        STATE* head0 = (STATE*)CtxChain[0];
        if (head0->Freq < 7u) {
          if (chain <= &CtxChain_2[1]) {
            ++((STATE*)CtxChain_1)->Freq;
          } else {
            ++((STATE*)CtxChain_2[0])->Freq;
            if (chain > CtxChain_4) {
              head0->Freq += (head0->Freq < 4);   // +1 if Freq is below 4
            }
          }
        }
      }
      trailStatesIdx = walkCtx->iStates;
      trailFlags = walkCtx->Flags;
      trailStates = (STATE*)Indx2Ptr(trailStatesIdx);
      goto LABEL_165;
    }
    {
    int mixWeight = 2;
    int depth5 = 5 * OrderFall;
    uint mixFlag;
    if( minNStates )
      // sign-bit-extract idiom: 1 if SummFreq < 45*minNStates, else 0.
      mixFlag = ((uint)minCtx->SummFreq < (uint)(45*minNStates));
    else
      mixFlag = orderBumpVariance==0;
    int ofallSaved = OrderFall;
    int ofallP3 = OrderFall+3;
    int ofallP1 = OrderFall+1;
    int depth3 = 3*OrderFall;
    do {
      sqword deepStatesIdx = walkCtx->iStates;
      byte deepFlags = walkCtx->Flags;
      STATE* deepStates = (STATE*)Indx2Ptr(deepStatesIdx);
      RefreshIfRank0Empty_(walkCtx, deepStatesIdx, deepFlags, deepStates, (sqword)chain);
      walkCtx->Flags = deepFlags & 0xF0;
      // deep find-and-bubble (freq margin 13)
      STATE* deepFound = FindAndBubble7_(deepStates, searchSym, &walkCtx->Flags, 13);
      int foundFreq = foundState->Freq;
      *chain++ = (sqword)deepFound;
      depth5 -= 5;
      depth3 -= 3;
      --depthLeft;
      if (foundFreq > 130 || deepFound->Freq >= 0xE4u) {
        trailBound = ofallP1;
        ofall = ofallSaved;
        walkCtx = walkCtx->getSuffix();
        goto LABEL_201;
      }
      int deepSumFreq = walkCtx->SummFreq;
      short mixBoostA = mixWeight + (depth5 > ofallP3);
      mixWeight >>= 1;
      // mixBoostB sums three contributions:
      //   1. 7*SummFreq < 4*Freq*(NStates+1)  (frequency-dominance test)
      //   2. 2*depthLeft > OrderFall+1          (still climbing)
      //   3. mixBoostA                         (mixWeight + threshold bit)
      short mixBoostB = (7*deepSumFreq < 4u*(uint)deepFound->Freq*(walkCtx->NStates + 1u))
                      + (2*depthLeft > ofallP1)
                      + mixBoostA;
      walkCtx->SummFreq = (word)(mixBoostB + deepSumFreq);
      newFoundFreq = mixBoostB + deepFound->Freq;
      deepFound->Freq = newFoundFreq;
      walkCtx = walkCtx->getSuffix();
    } while (newFoundFreq < 0x45u && depth3 > ofallP3 && mixFlag);
    trailBound = ofallP1;
    ofall = ofallSaved;
    }
LABEL_201:
    while (trailBound < 4*depthLeft) {
      trailStatesIdx = walkCtx->iStates;
      trailFlags = walkCtx->Flags;
      trailStates = (STATE*)Indx2Ptr(trailStatesIdx);
      if (trailStates[trailFlags & 0xF].Symbol == (byte)searchSym)
        break;
LABEL_165:
      RefreshIfRank0Empty_(walkCtx, trailStatesIdx, trailFlags, trailStates, (sqword)chain);
      walkCtx->Flags = trailFlags & 0xF0;
      // shallow find-and-bubble (freq margin 1 == strict less)
      STATE* trailFound = FindAndBubble7_(trailStates, searchSym, &walkCtx->Flags, 1);
      *chain++ = (sqword)trailFound;
      if ((uint)(trailStates[0].Freq + trailStates[1].Freq) > 0x5F)
        break;
      walkCtx = walkCtx->getSuffix();
      --depthLeft;
      trailBound = ofall + 1;
    }
    CtxChainEnd = (sqword)chain;
  } else {
    CtxChainEnd = (sqword)&CtxChain_1;
  }
  result = HeapNull + foundState->iSuccessor;
  if (ofall == MaxOrder && result >= UnitsStart) {
    RootContext = result;
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
  if (!SubAllocatorSize) return 0;
  sqword result = pText - UnitsStart + LoUnit + SubAllocatorSize - HiUnit;
  for (uint i = 0; i < N_INDEXES; ++i) {
    // Each entry: QueueSize * UNIT_SIZE bytes/unit * Indx2Units[i] units/block
    int bytesUsed = BListPtr[i].QueueSize * UNIT_SIZE * Indx2Units[i];
    result = (uint)(result - bytesUsed);
  }
  return result;
}

sqword StartSubAllocator(uint memsize_mb, int order, int cutOff) {
  if( !memsize_mb ) return 0;
  if( memsize_mb>0xFFF ) return 0;
  if( order<2 ) return 0;
  if( order>MAX_O ) return 0;
  if( SubAllocatorSize ) return 0;
  size_t memsize_b = memsize_mb<<20;
  HeapStart = new char[memsize_b]; // malloc(memsize_b);
  //  HeapStart = VAlloc<char>(memsize_b);
  // printf( "!p=%I64X size=%I64X!\n", memsize_b, qword(memsize_b) );
  if( !HeapStart ) return 0;
  RunLength = -100;
  SubAllocatorSize = memsize_b;
  InitsCount = 0;
  CutOff = cutOff;
  Interrupted = 0;
  if (order > 12) order = 16 << ((order + 19) & 31);
  MaxOrder = order;
  return 1;
}

sqword PPMIIDeleteModel() {

  if( SubAllocatorSize==0) return 0;

  qword finalSize = SubAllocatorSize;

  if( (InitsCount==1) && (CutOffCount+GlueCount==0) ) {
    qword textSize = ((char*)pText) - ((char*)HeapStart);

    // Mirrors ppmd's GetSizeOfUnitsSection() = (size/(UNIT_SIZE*MEM_DIVISOR))
    // * (MEM_DIVISOR-1) * UNIT_SIZE = (9/10)-ish of the heap, rounded.
    qword USSize = UNIT_SIZE * (MEM_DIVISOR-1) * (SubAllocatorSize / (UNIT_SIZE*MEM_DIVISOR));
    qword scaledUnits = (USSize - (HiUnit-LoUnit)) / (MEM_DIVISOR-1);

    qword maxMetric = (scaledUnits > textSize) ? scaledUnits : textSize;
    qword sizeLimit = MEM_DIVISOR * maxMetric + UNIT_SIZE;

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
    // Read 5 bytes; b0 is consumed but shifted out of the 32-bit Code result
    // (PPMII's leading marker byte).
    int b0 = getc(f);
    int b1 = getc(f);
    int b2 = getc(f);
    int b3 = getc(f);
    int b4 = getc(f);
    int pack1 = b1 | (b0    << 8);
    int pack2 = b2 | (pack1 << 8);
    int pack3 = b3 | (pack2 << 8);
    Code = b4 | (pack3 << 8);
  }

  // Shared body of EncodeShift / Flush: either bump the FF-run counter if the
  // top byte of Low is right on the carry boundary (0xFF000000..0xFFFFFFFF),
  // or flush Cache + a carry byte + any deferred FFs to the stream and refresh
  // Cache. Then shift Low up by 8 to consume that top byte.
  void emitOneByte(FILE *f) {
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

  void EncodeShift(FILE *f) {
    emitOneByte(f);
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
    for (int i = 0; i < 5; ++i)
      emitOneByte(f);
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
//  File-local helpers (declared in the anonymous namespace below) factor
//  repeated SSE-cell and CtxChain idioms shared across the cascade arms:
//
//      MaybeRescale1_/2_  SseScaleN_ + freq0 refresh
//      RescaleAccum1_/2_  MaybeRescaleN_ + commit slot.freq0 += weight>>n
//      SseClampMean_      mean = scale*slot[0]/slot[1], clamped
//      SseDeltaUpdate_    Bayesian (num,den) update + overflow halve
//      SseMixUpdate_      abbreviated SSE accumulator update
//      ClampToBand_       asymmetric clamp [lo, hi] for SSE gain
//      BubbleSortChain_   CtxChain[] insertion sort by priority
//      FillFreqMap_       SymFreqs[Sym] = Freq prologue
//      WalkEscapeChain_   walk suffix chain past escape symbol
//      RewindPredictor_   LABEL_128 "undo this round's deltas"
//      FreqMixStep_       freq-mixing inner-loop body
//
//  The body's goto layout is preserved -- it's irreducible at the source
//  level.
// =============================================================================

namespace {

// SseScale1 rescales the (sum, freq0, freq1) slot if freq0 or weight overflow.
// After the call, freq0 is refreshed from the slot. The caller's local copy
// of freq0 is updated; the weight value is captured by value (not refreshed).
template<typename T>
inline void MaybeRescale1_(void* slot, T& freq0Local, uint weight) {
  if ((uint)freq0Local > 0x8000u || weight > 0x80000u) {
    SseScale1((SseCounter*)slot);
    freq0Local = (T)((SseCounter*)slot)->freq0;
  }
}

// SseScale2 variant: no weight check, just freq0 > 0x8000.
template<typename T>
inline void MaybeRescale2_(void* slot, T& freq0Local) {
  if ((uint)freq0Local > 0x8000u) {
    SseScale2((SseSlot*)slot);
    freq0Local = (T)((SseCounter*)slot)->freq0;
  }
}

// MaybeRescale1_ + commit "slot.freq0 += (slot.freq1 >> shift)" pattern.
// Returns the accumulated delta so callers can stash it in a d-global.
inline int RescaleAccum1_(void* slot, uint weight, int shift) {
  SseCounter* cnt = (SseCounter*)slot;
  word freq0 = cnt->freq0;
  MaybeRescale1_(slot, freq0, weight);
  int  delta = (int)((uint)cnt->freq1 >> shift);
  cnt->freq0 = (word)(freq0 + delta);
  return delta;
}

// MaybeRescale2_ variant of the above.
inline int RescaleAccum2_(void* slot, int shift) {
  SseCounter* cnt = (SseCounter*)slot;
  word freq0 = cnt->freq0;
  MaybeRescale2_(slot, freq0);
  int  delta = (int)((uint)cnt->freq1 >> shift);
  cnt->freq0 = (word)(freq0 + delta);
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
// suffix-context's freq for this symbol (SymFreqs[sym]), the running (sumFreq,
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
  uint denom     = 3*cm + mixWeight - sxFreq;
  uint newFreq   = (cm*(3*curFreq + sxFreq) + denom - 4) / denom;
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

// Populate the SymFreqs[] frequency lookup table from a PPM context's states.
// SymFreqs[state.Symbol] = state.Freq, for each of NStates+1 states. Used 2x as
// the prologue to the freq-mixing loops below.
inline void FillFreqMap_(PPM_CONTEXT* ctx) {
  int   n = ctx->NStates + 1;
  STATE* s = ctx->getStates();
  do {
    SymFreqs[s->Symbol] = s->Freq;
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
    w = w->getSuffix();
    sym = w->getStates()[w->Flags & 0xF].Symbol;
  }
  outFinalSym  = sym;
  EscapeSymbol = sym;
  return w;
}

// Sse1 stage shared between the binary-context branch (region B) and the
// per-candidate loop (region F). Both call this with the same (slot, hits)
// arguments and the same (sseCum, sseTot) globals as accumulators.
// On exit, sseCum is unchanged; sseTot is unchanged; cumWeight is
// (clamp + sseTot) and cumFreq is (clamp + sseCum).
inline void Sse1Step_(int* slot, uint hits, int& cumWeight, int& cumFreq) {
  int cumIn = sseCum;
  int clamp = SseClampMean_(slot, hits, 1 - sseCum, 0x40000);
  SseDeltaUpdate_(slot, cumIn, 0x40000, 4096, 2);
  cumWeight = clamp + sseTot;
  cumFreq   = clamp + cumIn;
}

// SseMatch stage shared between region A and region F. Resets the running
// (sseCum, sseTot) pair to the boosted (boost, 60416) probability, stashes
// it into the sseMatch delta globals, clamps the cell into [1-boost,
// 0x40000], Bayesian-updates the cell, and accumulates the clamp result
// into sseTot. On exit: sseCum holds the post-stage cumFreq (clamp + boost).
inline void SseMatchStep_(int* slot, int boost) {
  sseCum = boost;
  sseTot = 60416;
  sseMatchDenDelta = boost;
  sseMatchNumDelta = 60416;
  int clamp = (int)SseClampMean_(slot, boost, 1 - boost, 0x40000);
  SseDeltaUpdate_(slot, boost, 0x80000, 0x2000, 1120);
  sseTot += clamp;
  predSseTotDelta = sseTot;
  sseCum = clamp + boost;
}

// Sse2 stage shared between regions A and F: clamp the cell against the
// current (sseCum, sseTot) probability gap, accumulate, and commit a
// MixUpdate. Returns the clamp value so callers can capture intermediates.
// On exit: sseTot += clamp; sseCum unchanged. The captured totFreq value
// (clamp + sseTot_old) equals sseTot_new, so callers should read sseTot.
inline int Sse2Step_(int* slot) {
  int cumIn = sseCum;
  int clamp = SseClampMean_(slot, sseTot - cumIn, cumIn - sseTot + 1, 0x40000);
  sseTot += clamp;
  SseMixUpdate_(slot, 2 * cumIn, 1);
  return clamp;
}

// Sse3 stage shared between regions A and F: similar to Sse2Step_ but uses a
// different scale (totFreq - sse2CumIn) and a different absThresh.
// On exit: sseTot += clamp; sseCum unchanged. Caller passes the captured
// pre-Sse2 cumFreq (sse2CumIn) since Sse3 wants to scale by that.
inline int Sse3Step_(int* slot, int sse2CumIn, int totFreqPreSse3) {
  int clamp = SseClampMean_(slot, totFreqPreSse3 - sse2CumIn, sseCum - sseTot + 1, 0x80000);
  sseTot += clamp;
  SseMixUpdate_(slot, sse2CumIn, 2);
  return clamp;
}

// Combined "weighted-average cumulative frequency" helper shared by region A
// (main mix block) and region C (escape mirror). Computes the running
// cumulative-freq increment as (freq/2 + nStatesP1 * weight) / freq + 2.
inline uint MixCumFreq_(uint mixFreq, uint mixWeight, uint nStatesP1) {
  return ((mixFreq >> 1) + nStatesP1 * mixWeight) / mixFreq + 2;
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

// Build OrderCtxSeed in both region B (binary coder) and region F
// (per-candidate loop). Both use the same 14-bit predicate ladder over a
// candidate symbol plus carried bits. The diverging inputs:
//   sym          : currentSymbol (B) or candSymbol (F)
//   matchCtxHi   : MatchCtxHi (B, live)  or matchCtxHiSave (F, snapshot)
//   sparseFlag   : sparseFlags (B, from PPMContextWalk)  or sparseHitsF (F)
//   carriedFrom  : OrderCtxSeed itself (B) or orderCtxSeedSave (F snapshot)
//   freq, hits   : (mixFreqB, mixHitsB) (B) or (freq0F, hitsF) (F)
inline uint OrderCtxSeedBuild_(int sym, int matchCtxHi, int sparseFlag,
                               int carriedFrom, uint freq, uint hits) {
  return SseIdx{}
    .bit  <0>    (sym == hintSymB31)
    .bit  <1>    (sym == hintSymB29)
    .bit  <2>    (sym == hintSymBiject)
    .bit  <3>    (sym == b31Key)
    .bit  <4>    (sym == Order1Ctx)
    .field<5, 3> (sym)                                   // bits 5-7 of the sym
    .bit  <8>    (sym == matchHintByte)
    .field<9, 1> (carriedFrom)                           // bit  9    carried
    .field<10,1> ((word)recentSym - (word)sym)           // bit 10    sign trick
    .field<11,1> ((word)sym - (word)matchCtxHi)          // bit 11    sign trick
    .bit  <12>   (sparseFlag)
    .field<13,3> (carriedFrom)                           // bits 13-15 carried
    .bits <16,2> ((freq < (uint)(56*hits))
                + (freq < (uint)( 6*hits)))              // bits 16-17 hits/freq band
    .val;
}

// Build the sse3 cascade index used in both region A (binary coder) and
// region F (per-candidate loop). Inputs that vary:
//   sym         : escSymB (A) or candSymbol (F)
//   tagSymLast2 : SymLastCtx2[sym]==SymCount  (A computes inline)
//                 or pre-captured tagSymLastCtx2F (F)
//   heapIdx     : context->iStates via summFreqPtr (A) or localFoundState->iSuccessor (F)
//   sseIdx      : sse2IdxA (A) or sse2IdxF (F)
//   sse2Counter : sse2Base[512] read (uint) at the call site
//   histByte    : sse2Base[(sym-RSContext)&0x1FF] (passed in)
// Reads globals: sseState3Hash, SseState3, HeapNull, pText, matchPosAge,
// MixCtxExtra.
inline uint Sse3IdxBuild_(int sym, bool tagSymLast2, uint heapIdx,
                          uint sseIdx, uint sse2Counter, uint histByte) {
  // The bit<2> predicate tests "heapIdx lands in the last 736 bytes
  // before pText" (i.e., HeapNull + heapIdx - pText in [-736, 0)).
  return SseIdx{}
    .bit  <0>    (tagSymLast2)
    .bit  <1>    (sym == (byte)SseState3[sseState3Hash])
    .bit  <2>    ((uint)(HeapNull + heapIdx - pText + 736) < 0x2E0)
    .bits <3, 2> ((sse2Counter < 384*histByte)
                + (sse2Counter <  58*histByte)
                + (sse2Counter <  22*histByte))         // 0..3 at bits 3-4
    .field<8, 3> (sseIdx)                               // carried bits 8-10
    .bit  <11>   ((uint)matchPosAge < 0x2C00)
    .raw         (MixCtxExtra)                          // pre-positioned multi-bit accumulator
    .val;
}

// Build the sseMatch cascade index used in both region A (binary coder) and
// region F (per-candidate loop). The only varying input is the symbol; the
// remaining inputs (recentSym, MixCtx, matchPosAge, FoundSymbol, MixScale,
// mixScaleCntr) are file-scope globals.
inline int SseMatchIdxBuild_(int sym) {
  return (int)SseIdx{}
    .bits <1, 8>  (sym)                              // bits 1-8: candidate sym
    .bits <9, 8>  (recentSym)                        // bits 9-16: recent matched sym
    .bit  <17>    (MixCtx)                           // MixCtx is 0/1
    .bit  <18>    ((uint)matchPosAge < 0x78)
    .bit  <19>    (sym == FoundSymbol)
    .bit  <20>    (MixScale < (uint)mixScaleCntr)
    .val;
}

// Build the sse2 cascade index used in both region A (binary coder) and
// region F (per-candidate loop). Same indexing rule; the only varying
// inputs are the symbol and the (prevWeight, prevTot) for the bit<13>
// "weight scarcity" predicate. Reads several globals (hint*, matchPosAge,
// matchEpoch2, matchHashSy, FoundSymbol, PrevSymbol, OrderCtxSeed, SseSeed,
// SSE0).
inline uint Sse2IdxBuild_(int sym, uint prevWeight, uint prevTot) {
  return SseIdx{}
    .bit  <0>    (sym == hintSymM2)
    .bit  <1>    (sym == hintSymMatch3)                     // overlaid with SSE0 byte below
    .bit  <2>    (sym == hintSymBmCell)
    .bit  <3>    (sym == FoundSymbol)
    .bit  <4>    (sym == PrevSymbol)
    .bits <5, 2> (((uint)matchPosAge < 0xA800)
                + ((uint)matchPosAge < 0x600)
                + ((uint)matchPosAge < 0xD))                // 0..3 at bits 5-6
    .bit  <7>    ((uint)matchEpoch2 < 0x29)
    .bits <1, 8> (SSE0[sym])                                // SSE0 byte at bits 1-8 (overlaps boolean bits)
    .field<11,1> (OrderCtxSeed)
    .field<12,1> ((word)matchHashSy - (word)sym)            // sign-trick bit 12 of word subtraction
    .bit  <13>   (17*prevWeight < prevTot)
    .raw         (SseSeed)
    .val;
}

} // namespace

template< int f_DEC > int RealProcess(FILE* outFile, FILE* inFile) {
  int inputByte, epoch;
  int nStatesP1Save, cumFreqC, entryNStates, sseSum2A;
  int predShiftFlags, predBinFlags;
  int walkNStates, walkDelta, descendNStates, freqDeltaE, remStatesE, freqSumE;
  int walkFreqSumE, walkSymE, currentSymbol, mixCtx, mixFreqB, mixHitsB;
  int cumWeightB, cumFreqB, escSymB;
  int sse2CumInA, totFreqA;
  int cumFreq, oneStateFreqCachedF;
  int sortPriorityC, sxNStatesC, sumFreqCacheC;
  int descendNStatesP1E, ofallSavedE;
  int descendNStatesP1C, sparseFlags, remCandF, escSymbol;
  int escCandidate, seeIdxBase;
  byte flagsSaveA;
  STATE  **chainPtr;
  sqword *chainEndE, *chainEndF, *sortRangeE, *sortLimitC;
  STATE *localFoundState, *walkStateIterE, *firstStateE;
  PPM_CONTEXT *MinContext, *sx_p, *suffixCtxC, *preCommitMinCtx;
  uint mixDeltaA, cumFreqMixA, cumFreqDivA, sumFreqF;
  uint totFreqC, subRangeC;
  uint seeIndex, suffixNStates;
  uint centerExpandB, binSseVal;
  uint totFreq, subRange, mixWeightC, mixWeightDeltaC;
  uint sumFreqDivC, sumFreqLimit;
  uint mixFreqCacheC, maskFlagEsc, maskFlagPrev, mixFreqA, mixWeightA;
  char descendFlags, mixShiftA, mixShiftB, mixShiftC, predShiftIncC;
  sqword mixIdxA, mixIdxB, mixIdxC, sse2IdxA;
  sqword mixOffsetC, priorFoundStateF, result;
  sqword sseQTableIdxA, sseQTableIdxC, summFreqPtr;
  int *mixSlotA;
  int *mixBaseB, *mixSlotB;
  int *sse1SlotB, *sseMatchSlotA, *sse2SlotA, *sse3SlotA;
  short orderCtxSeedSave;
  char *mixSlotC;
  // sseCum/sseTot are the per-cascade-stage accumulator pair, file-scope
  // because MixUpdate also reads sseCum on its way out.
  // Each SSE cascade stage publishes its slot pointer through one q-global so
  // MixUpdate can update that same cell on the way back out.
  int*& sse1Slot     = (int*&)Sse1SlotG;
  int*& sseMatchSlot = (int*&)SseMatchSlotG;
  int*& sse2Slot     = (int*&)Sse2SlotG;
  int*& sse3Slot     = (int*&)Sse3SlotG;
  // The center pointer of the current binary-mix cell (4-word layout). Set
  // once per branch, then re-read by the deeper sub-stage to grab the weight.
  word*& binMixCenter = (word*&)BinMixCenterG;
  // BinSse cell and the PredWeight A/B cells. Each is a 2-uint cell; the
  // commit-tail reads/writes them as `slot[0] += d##; slot[1] += d##;`. The
  // three globals BinSseCellG / PredWeightAG / PredWeightBG are only ever
  // referenced from this file; they got hoisted to file scope by the
  // decompiler but are really per-symbol scratch.
  uint*& binSseCell  = (uint*&)BinSseCellG;
  uint*& predWeightA = (uint*&)PredWeightAG;
  uint*& predWeightB = (uint*&)PredWeightBG;
  // Sse2BaseG holds the base of the current Sse2State sub-block (a 516-byte chunk;
  // the histogram occupies bytes 0..511, the running counter sits at +512).
  byte*& sse2Base = (byte*&)Sse2BaseG;
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
        BinEscFreq(MinContext);
        nStates = MinContext->NStates;
        ctxFlags = MinContext->Flags;
      }
      uint nStatesPlus1 = nStates+1;
      int  remStates = nStates+1;
      STATE* escState = &MinContext->getStates()[ctxFlags&0xF];
      CtxChain[0] = (sqword)escState;
      sqword* chainEnd = &CtxChain_1;
      sqword* chainStart = &CtxChain_1;
      escSymbol = escState->Symbol;
      MixCtx3 = escSymbol;
      STATE* stateIter = MinContext->getStates() - 1;
      SymMask[escState->Symbol] = epoch;
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
            sortLimit = &CtxChain[(foundSymHist&7)==0];
LABEL_14:
            BubbleSortChain_(chainEnd, sortLimit, sortPriority);
            ++chainStart;
            goto LABEL_18;
          }
          if( epoch==MatchPosBySym[walkSym]||epoch==SymLastCtx2[walkSym] ) {
            sortLimit = chainStart;
            // priority 18 if MatchPosBySym hit (the stronger signal), else 7
            sortPriority = (epoch==MatchPosBySym[walkSym]) ? 18 : 7;
            goto LABEL_14;
          }
        }
LABEL_18:
        // After scanning all states in MinContext: enter the SSE-mix block.
        if( !--remStates ) {
          // These are written only in the else branch but read inside the
          // if(nStatesPlus1<24) ... LABEL_58 path; declare at this scope so
          // the goto LABEL_58 below doesn't bypass init.
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
            sx_p = MinContext->getSuffix();
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
              int  nStatesCnt = nStates+1;
              STATE* stateBackM = &MinContext->getStates()[nStatesPlus1];
              int  mixConstM  = 11*(nStates+1);
              int  sumFreqM   = minSumFreqA;          // mutated by FreqMixStep_ via reference
              int  sumFreqWM  = sumFreqM;             // ditto
              // (mixConstM-sumFreqM)>>28 | 7  -- sign-bit-extract idiom:
              // produces 15 if sumFreqM > mixConstM, else 7. So the weight
              // scale is 15 when SummFreq exceeds 11*(NStates+1), else 7.
              int  mixWeightScale = (sumFreqM > mixConstM) ? 15 : 7;
              int  mixWeightM = nStatesP1Save*mixWeightScale + sxSumFreqA0;
              do {
                stateBackM -= 1;
                FreqMixStep_(stateBackM, SymFreqs[stateBackM->Symbol], mixWeightM,
                             mixConstM, sumFreqM, sumFreqWM, MinContext);
              } while( --nStatesCnt );
              sumFreqSaveA = sumFreqWM;
              // (flagsSaveA stays as-set at the if-entry; FreqMixStep_
              //  doesn't mutate MinContext->Flags.)
            }
            {
              // maskFlagEsc captures the suffix context's rank-0 symbol;
              // WalkEscapeChain_ then rewrites it (via outFinalSym/EscapeSymbol).
              PPM_CONTEXT* escWalkCtx = MinContext->getSuffix();
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
              int* bigSlotA = &d29[512*sseQTableIdxA + 2 * (int)(SseIdx{}
                .field<0, 2> ((byte)mixIdxA)                  // mixIdxA bits 0-1
                .bit  <3>    (maskFlagEsc | maskFlagPrev)
                .field<4, 4> ((byte)mixIdxA))];                // mixIdxA bits 4-7
              q29 = (sqword)bigSlotA;
              mixShiftA = mixDeltaA<0x200;
              // blend the two neighbour cells (mixSlotA ± 2048 ints, where
              // each cell is 2 ints = weight + freq) into (mixWeightA,
              // mixFreqA). Freq is read as word at byte offset +4 inside
              // each int-cell, i.e. ((word*)cell)[2].
              int* mixUpA = mixSlotA + 2048;
              int* mixDnA = mixSlotA - 2048;
              q33 = (sqword)mixUpA;
              q32 = (sqword)mixDnA;
              uint mixWeightSavedA = (uint)mixUpA[0];
              mixWeightA = ((mixWeightSavedA + mixDnA[0])           >> (mixShiftA+1)) + mixWeightA;
              mixFreqA   = ((uint)(((word*)mixUpA)[2]
                                 + ((word*)mixDnA)[2])              >> (mixShiftA+1)) + mixFreqA;
              sseCum = mixWeightA;
              sseTot = mixFreqA;
              wDelta33 = RescaleAccum1_(mixUpA, mixWeightSavedA, mixShiftA);
              wDelta32 = RescaleAccum1_(mixDnA, (uint)mixDnA[0],   mixShiftA);
              uint centerExpandA = *((word*)mixSlotA+3);  // central cell predExpand counter
              bool mixShiftLowA = centerExpandA<0x400u;
              char mixShiftBSel = mixShiftA+mixShiftLowA;
              int* mixBaseAStride = &mixSlotA[-2*mixIdxA];
              // Two more neighbour cells along XOR-stretch dimensions 0x100, 0x200
              int* sse3Nbr = &mixBaseAStride[2*(int)(mixIdxA^0x100)];
              int* sse4Nbr = &mixBaseAStride[2*(int)(mixIdxA^0x200)];
              q31 = (sqword)sse3Nbr;
              q30 = (sqword)sse4Nbr;
              wDelta31 = RescaleAccum1_(sse3Nbr, *(uint*)sse3Nbr, mixShiftBSel);
              wDelta30 = RescaleAccum1_(sse4Nbr, *(uint*)sse4Nbr, mixShiftBSel);
              wDelta29 = RescaleAccum1_(bigSlotA, (uint)*bigSlotA, mixShiftA+mixShiftLowA+1);
            }
            predRescaleDiv = MinContext->SummFreq;
            cumFreqMixA = predRescaleDiv + MixCumFreq_(mixFreqA, mixWeightA, nStatesPlus1);
            cumFreqAcc = cumFreqMixA;
            if( nStatesPlus1<24 ) {
              cumFreqMixSave = 0;
              cumFreqDivA = 0;
LABEL_58:
              // SSE-mix preamble: zero out the per-step predictor accumulators
              // and seed the LABEL_59 escape walk.
              wDelta35 = 171;
              sumFreqLimit = cumFreqDivA;
              predShiftFlags = 0;
              wDelta34 = 0;
              predBinFlags = 171;
              sseIdxStorage = SseIdx{}
                .bit  <1>    (OrderFall < 3)
                .raw         (1032u * (MinContext->iSuffix == 0))   // 1032 = bit 3 + bit 10, both set together
                .bits <5, 2> (MixCtx2 & 3);
              seeIdxBase = sseIdxStorage;
              remCandF = nStates+1;
              chainPtr = (STATE**)CtxChain;
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
          cumFreqMixSave = cumFreqMixA>>1;
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
    // 6 neighbour-cell pointers along disjoint XOR dimensions of mixIdxB
    // (each dim flips a different feature bit; the slot is the cell at the
    // flipped index). q34/q35 are the "next" dimensions; q29..q32 are the
    // "current" dimensions. Used by the per-step RescaleAccum2_ stack and
    // the commit-tail `*(uint*)q## += wDelta##` writes.
    q32 = (sqword)&mixBaseB[2*(mixIdxB^0x1000)];
    q31 = (sqword)&mixBaseB[2*(mixIdxB^1)];
    q30 = (sqword)&mixBaseB[2*(mixIdxB^0x2000)];
    q29 = (sqword)&mixBaseB[2*(mixIdxB^0x20)];
    q34 = (sqword)&mixBaseB[2*(mixIdxB^0x200)];
    q35 = (sqword)&mixBaseB[2*(mixIdxB^0x400)];
    mixSlotB = &mixBaseB[2*mixIdxB];
    mixFreqB = *((word*)mixSlotB+2);
    binMixCenter = (word*)mixSlotB;
    PredBaseAG = (sqword)(mixSlotB-4);
    PredBaseBG = (sqword)(mixSlotB+4);
    MaybeRescale2_(mixSlotB, mixFreqB);
    mixHitsB = *(word*)mixSlotB;
    sseCum = mixHitsB;
    *((word*)mixSlotB+2) = mixFreqB + *((word*)mixSlotB+3);
    sseTot = mixFreqB;
    sse2DenDelta = mixHitsB;
    sse2NumDelta = mixFreqB;
    OrderCtxSeed = OrderCtxSeedBuild_(currentSymbol, (int)MatchCtxHi,
                                      sparseFlags, OrderCtxSeed,
                                      (uint)mixFreqB, (uint)mixHitsB);
    sse1SlotB = &Sse1[2*OrderCtxSeed];
    sse1Slot = sse1SlotB;
    Sse1Step_(sse1SlotB, mixHitsB, cumWeightB, cumFreqB);
    centerExpandB = binMixCenter[3];
    escSymB = MixCtx3;                  // both arms below want this snapshot
    if( centerExpandB<=0x20 ) {
      sseTot = cumWeightB;
      sseCum = cumFreqB;
      // Cheap-path: skip the deeper BinSse sub-stage. Reset all 10 SSE/mix
      // slot pointers to (sqword)d27 (dummy sink) so the commit-tail's
      // '*(uint*)slot += wDelta##' writes have no effect.
      q35 = q34 = q29 = q30 = q31 = q32 = PredBaseBG = PredBaseAG = BinMixLoG = BinMixHiG = (sqword)d27;
      binSseCell = (uint*)&predWeightSink;        // dummy sink: deeper sub-stage not taken
    } else {
      // Deeper sub-stage: take the BinSse path and run ~6 more SSE-mix
      // accumulators before joining the range coder dispatch below.
      int* binSseSlotB = &BinSse[(int)(SseIdx{}
          .bits <0, 2> ((uint)mixIdxB >> 6)                   // mixIdxB bits 6-7 -> result bits 0-1
          .bit  <2>    (SymLastCtx2[MixCtx3] == SymCount)
          .bit  <3>    ((uint)mixIdxB & 0x200)                // mixIdxB bit 9   -> result bit 3
          .bits <4, 2> (sparseFlags)                          // sparseFlags is 0..3 (2 bits at 4-5)
          .bit  <6>    (RunLength > -9)
          .bits <7, 8> ((byte)SSE1QTable[seeIndex]))];        // SSE1QTable byte at bits 7-14

      binSseVal = *binSseSlotB;
      binSseCell = (uint*)binSseSlotB;
      int mixSseMeanB = (binSseVal>>(centerExpandB<0x230))+cumFreqB;
      int mixSseFreqB = (0x3100u>>(centerExpandB<0x230))+cumWeightB;
      sseCum = mixSseMeanB;
      sseTot = mixSseFreqB;
      *binSseSlotB = binSseVal-((binSseVal+2)>>3);
      mixShiftB = centerExpandB<0x220;
      predBaseDeltaA = RescaleAccum2_((void*)PredBaseAG, mixShiftB);
      predBaseDeltaB = RescaleAccum2_((void*)PredBaseBG, mixShiftB);
      // blend the two neighbour cells (binMixCenter ± 0x10000 words) into
      // the (cumFreqB, cumWeightB) accumulators. binUpCell[0]/binDnCell[0]
      // are the hits slot of each neighbour; [2] is the freq slot.
      word* binUpCell = binMixCenter + 0x10000;
      word* binDnCell = binMixCenter - 0x10000;
      BinMixLoG = (sqword)binDnCell;
      BinMixHiG = (sqword)binUpCell;
      cumFreqB   = ((binUpCell[0] + binDnCell[0])                >> (mixShiftB+1)) + mixSseMeanB;
      cumWeightB = ((uint)(binUpCell[2] + binDnCell[2])          >> (mixShiftB+1)) + mixSseFreqB;
      sseCum = cumFreqB;
      sseTot = cumWeightB;
      binMixDeltaHi = RescaleAccum2_(binMixCenter+0x10000, mixShiftB);
      binMixDeltaLo = RescaleAccum2_(binMixCenter-0x10000, mixShiftB);
      mixShiftC = (binMixCenter[3]<0x398u) + mixShiftB;
      wDelta32  = RescaleAccum2_((void*)q32, mixShiftC);
      wDelta31 = RescaleAccum2_((void*)q31, mixShiftC);
      wDelta30 = RescaleAccum2_((void*)q30, mixShiftC);
      wDelta29 = RescaleAccum2_((void*)q29, mixShiftC);
      wDelta34 = RescaleAccum2_((void*)q34, mixShiftC);
      wDelta35 = RescaleAccum2_((void*)q35, mixShiftC);
    }
    sseMatchSlotA = &SseMatch[SseMatchIdxBuild_(escSymB)];
    sseMatchSlot = sseMatchSlotA;
    SseMatchStep_(sseMatchSlotA, (int)(60416LL*cumFreqB/cumWeightB));
    sseSum2A = sseCum;
    sse2IdxA = Sse2IdxBuild_(escSymB, sseSum2A, (uint)sseTot);
    sse2SlotA = &Sse2[2*sse2IdxA];
    sse2Slot = sse2SlotA;
    sse2CumInA = sseSum2A;
    Sse2Step_(sse2SlotA);
    totFreqA = sseTot;
    predWeightDelta = totFreqA;
    {
      // Scope-locals so the goto-into-LABEL_59 path doesn't trip
      // "jump bypasses initialization".
      int  sse2HistByte = sse2Base[((word)escSymB-(word)RSContext)&0x1FF];
      uint sse2CounterA = *(uint*)(sse2Base+512);
      sse3SlotA = &Sse3[2 * (int)Sse3IdxBuild_(escSymB,
                                                SymLastCtx2[escSymB]==SymCount,
                                                *(uint*)(summFreqPtr+2),
                                                (uint)sse2IdxA, sse2CounterA,
                                                (uint)sse2HistByte)];
    }
    sse3Slot = sse3SlotA;
    cumFreq = sseCum;
    Sse3Step_(sse3SlotA, sse2CumInA, totFreqA);
    totFreq = sseTot;

    subRange = rc.getSubRange(cumFreq, totFreq);
    if( f_DEC ? !rc.IsDecodeMatched(subRange) : (inputByte != MinContext->oneState().Symbol) ) {
      // Snapshot the single-state context's Freq before MinContext gets
      // reassigned to MaxContext below; the escape-probability formula
      // (a few lines later) needs the OLD MinContext.
      oneStateFreqCachedF = MinContext->oneState().Freq;
      if( f_DEC ) rc.DecodeNotMatched(subRange); else rc.encodeEscape(subRange);
      SymMask[MinContext->oneState().Symbol] = SymCount;
      SparseBitmapA[SparseIdxA] &= ~SparseBit;
      q9 = 0;
      SparseBitmapB[SparseIdxB] &= ~SparseBit;
      MinContext = MaxContext;
      entryNStates = MinContext->NStates;
      MixCtx = 0;
      // Escape probability in PE's 16-scaled integer form. Factored:
      //   result = 16 * (cumFreq*(f+1) - f*totFreq) / (totFreq*(f+1))
      //          = 16 * (cumFreq/totFreq - f/(f+1))     where f = oneStateFreqCachedF.
      // Block-scoped so the LABEL_128 goto doesn't bypass the initializer.
      {
        int oneStateFreqP1 = oneStateFreqCachedF + 1;
        result = (int)(16 * (oneStateFreqP1*cumFreq - oneStateFreqCachedF*totFreq))
               / (int)(totFreq * oneStateFreqP1);
      }
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
          if (!MinContext->getStates()[result].Freq) {
            BinEscFreq(MinContext);
            result = 2 * (MinContext->Flags & 0xF);   // matches BinEscFreq's old return
          }
        }
        walkDelta = walkNStates-entryNStates;
      } while( !walkDelta );
      descendNStates = walkNStates;
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
        wDelta34 = 0x8000;
      } else {
        descendFlags = 1;
        chainEndE = &CtxChain_1;
        CtxChain[0] = (sqword)firstStateE;
        SymMask[escSymbol] = SymCount;
        chainEndF = &CtxChain_1;
        freqSumE = firstStateE->Freq;
        predShiftFlags = 0;
        remStatesE = freqDeltaE-1;
        wDelta34 = 0;
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
            // priority 16 if MatchPosBySym hit (stronger signal), else 12
            sortPriorityC = (epoch==MatchPosBySym[walkSymE]) ? 16 : 12;
            goto LABEL_292;
          }
LABEL_296:
          if( !--remStatesE ) {
            freqSumE = walkFreqSumE;
            goto LABEL_298;
          }
        }
        sortPriorityC = 22;
        sortLimitC = &CtxChain[(byte)descendFlags&((foundSymHist&7)==0)];
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
        suffixCtxC = MinContext->getSuffix();
        suffixCtxC = WalkEscapeChain_(suffixCtxC, MinContext, escSymbol, escCandidate);
        // FreqMixStep_ doesn't touch MinContext->Flags, so one read suffices.
        byte minCtxFlagsC = MinContext->Flags;
        if( 16*freqDeltaE<=freqSumE||(MinContext->Flags&0x40)!=0 ) {
          CtxChainEnd = (sqword)chainEndF;
          sumFreqCacheC = MinContext->SummFreq;
        } else {
          FillFreqMap_(suffixCtxC);
          int  walkFreqSumC   = 0;
          int  sumFreqC       = MinContext->SummFreq;
          int  mixFiveC       = 5*descendNStates+5;
          // sumFreqC > 2*mixFiveC predicate weights at 5; constant 8 base.
          // suffixCtxC's (NStates+1)*weight + SummFreq seeds mixWeightCfull.
          uint mixWeightCfull = (5*(2*mixFiveC < sumFreqC) + 8)*(suffixCtxC->NStates+1)
                              + suffixCtxC->SummFreq;
          int  sumFreqW0C     = (word)sumFreqC;
          do {
            STATE* st = (STATE*)*--chainEndE;
            FreqMixStep_(st, SymFreqs[st->Symbol], mixWeightCfull,
                         2*mixFiveC, sumFreqC, sumFreqW0C, MinContext);
            walkFreqSumC += st->Freq;
          } while( chainEndE!=CtxChain );
          freqSumE = walkFreqSumC;
          sumFreqCacheC = sumFreqW0C;
          CtxChainEnd = (sqword)chainEndE;
        }
        sx_p = MinContext->getSuffix();
        sxNStatesC = sx_p->NStates;
        descendNStatesP1C = sxNStatesC+1;
        int maskFlagPrevC = epoch!=SymMask[PrevSymbol];
        // mixIdxC: composite index for the escape mirror's mix table.
        // Same shape as mixIdxA but with different inputs at each predicate.
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
        // mixSlotC and the matching freq slot (w12 is d29 offset by +4 bytes).
        mixSlotC        = (char*)d29 + mixOffsetC;
        mixWeightC      = *(int*) mixSlotC;
        mixFreqCacheC   = *(word*)((char*)&w12 + mixOffsetC);
        q34             = (sqword)mixSlotC;
        sseCum          = mixWeightC;
        sseTot          = mixFreqCacheC;
        mixWeightDeltaC = RescaleAccum1_(mixSlotC, (uint)mixWeightC, 0);
        if( mixWeightDeltaC>0x78 ) {
          // d29[]/MixWeight2[] index in 2-int-stride units.
          int* bigSlotC = &MixWeight2[2048 * sseQTableIdxC + 2 * (int)(SseIdx{}
              .field<0, 2> ((byte)mixIdxC)                                       // mixIdxC bits 0-1, in place
              .bit  <2>    (ofallSavedE < 10)                                    // OrderFall band
              .bit  <3>    (MinContext->NStates + 2*sxNStatesC + 2 > NMasked)  // parent context dense
              .field<4, 4> ((byte)mixIdxC)                                       // mixIdxC bits 4-7, in place
              .bit  <8>    (maskFlagPrevC)
              .bit  <9>    (epoch != SymMask[escCandidate]))];
          q29 = (sqword)bigSlotC;
          bool predLoBeyondC = mixWeightDeltaC<0x100;
          char shiftSelC = predLoBeyondC+1;
          // blend the two neighbour cells (mixSlotC ± 2048 bytes; cell layout:
          // uint weight at byte 0, word freq at byte 4) into (mixWeightC,
          // mixFreqCacheC). Same pattern as mixUpA/mixDnA above.
          char* mixUpC = mixSlotC + 2048;
          char* mixDnC = mixSlotC - 2048;
          q33 = (sqword)mixUpC;
          q32 = (sqword)mixDnC;
          mixWeightC    += (*(uint*)mixUpC + *(uint*)mixDnC)            >> shiftSelC;
          mixFreqCacheC += (uint)(((word*)mixUpC)[2]
                                + ((word*)mixDnC)[2])                   >> shiftSelC;
          sseCum = mixWeightC;
          sseTot = mixFreqCacheC;
          wDelta33 = RescaleAccum1_(mixUpC, *(uint*)mixUpC, shiftSelC);
          wDelta32 = RescaleAccum1_(mixDnC, *(uint*)mixDnC, shiftSelC);
          uint centerExpandC = *((word*)mixSlotC+3);    // central cell predExpand counter
          wDelta29 = RescaleAccum1_(bigSlotC, (uint)*bigSlotC, centerExpandC<0x200u);
          predShiftIncC = (centerExpandC<0x400u)+predLoBeyondC+1;
          char* mixStrideC = &mixSlotC[-8*mixIdxC];
          // Two more neighbour cells along XOR-stretch dimensions 2, 8
          char* sse3Nbr = &mixStrideC[8*(int)(mixIdxC^2)];
          char* sse4Nbr = &mixStrideC[8*(int)(mixIdxC^8)];
          q31 = (sqword)sse3Nbr;
          q30 = (sqword)sse4Nbr;
          wDelta31 = RescaleAccum1_(sse3Nbr, *(uint*)sse3Nbr, predShiftIncC);
          wDelta30 = RescaleAccum1_(sse4Nbr, *(uint*)sse4Nbr, predShiftIncC);
        }
        sumFreqDivC = MixCumFreq_(mixFreqCacheC, mixWeightC, descendNStatesP1E);
        if( descendNStatesP1E<24 ) {
          sumFreqLimit = 0;
          goto LABEL_335;
        }
      }
      sumFreqLimit = (int)(sumFreqDivC+MinContext->SummFreq)>>1;
LABEL_335:
      // Per-state walk through CtxChain[] inside the escape:  each iteration
      // is the body of ppmd's "FoundState = MinContext->encode2(c)" search.
      cumFreqMixSave = sumFreqLimit;
      sumFreqF = freqSumE+sumFreqDivC;
      cumFreqAcc = sumFreqF;
      RunLength = runLengthInit;
      predRescaleDiv = freqSumE+descendNStates+1;
      predBinFlags = 0;
      chainPtr = (STATE**)CtxChain;
      wDelta35 = 0;
      CtxChainEnd = (sqword)CtxChain;
      {
        uint orderShift15C = (ofallSavedE>1)<<15;
        orderCtxSeedSave = orderShift15C + (OrderCtxSeed & 0x7FFF);
        OrderCtxSeed    = orderShift15C + (OrderCtxSeed & 0xFFFF7FFF);
        SseSeed = ((ofallSavedE>3)<<15) + orderShift15C + (SseSeed & 0x4600);
      }
      // seeIdxBase: starting bitfield for the escape-mirror SSE seed.
      seeIdxBase = SseIdx{}
        .bit  <1>    (ofallSavedE < 3 || ofallSavedE+23 < OrderFall0)
        .raw         (1032u * (MinContext->iSuffix == 0))   // 1032 = bit 3 + bit 10, both set together
        .bits <5, 2> (MixCtx2 & 3);
      sseIdxStorage = seeIdxBase;
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
        localFoundState = *chainPtr;
        preCommitMinCtx = MinContext;
        CtxChainEnd = (sqword)(chainPtr+1);
        // Reset the PredBase{A,B}G and BinMix{Hi,Lo}G slots to d27 (the
        // dummy/zero sink) so subsequent RescaleAccum2_ stack writes either
        // see a real cell (set during the PredWeight stage below) or quietly
        // write into d27 and have no effect.
        PredBaseBG = PredBaseAG = BinMixLoG = BinMixHiG = (sqword)d27;
        uint candSymbol = localFoundState->Symbol;
        sqword candProbBF = ((localFoundState->Freq<<8)-predBinFlags)/sumFreqF;
        SparseBit = 1<<localFoundState->Symbol;
        int sseEntryC2F = candProbBF;
        sqword mixSseSizeF = (uint)(byte)SymType[candProbBF]+1;
        SparseIdxA = ((candSymbol+SparseHashA)>>5)+0x2000;
        SparseIdxB = predShiftFlags+((candSymbol+SparseHashB)>>5);
        bool tagSymLastCtx2F = epoch==SymLastCtx2[candSymbol];
        int sparseHitsF = (int)SseIdx{}
          .bit<0>(SparseBit & SparseBitmapA[SparseIdxA])
          .bit<1>(SparseBit & SparseBitmapB[SparseIdxB]);
        predWeightB = (uint*)&predWeightSink2;      // dummy sink: PredWeight stage not taken
        predWeightA = (uint*)&predWeightSink2;
        short matchCtxHiSave = MatchCtxHi;
        int matchTblHitF = MatchPosTable[256*MatchCtxHi+candSymbol];
        ComputeMatchHints_(matchTblHitF, candSymbol);
        // seeIdxF: composite index for the per-candidate mix table d27[].
        // Outer OR with seeIdxBase (the prior-section accumulator) preserves
        // the bit-merge semantics where seeIdxBase and the inner sum may
        // share bit positions. The inner sum itself uses +-with-carry — the
        // SSE0[sym] byte can overlap the boolean bits 0..7.
        sqword seeIdxF = seeIdxBase | (uint)(SseIdx{}
          .bit  <0>    (tagSymLastCtx2F)                  // SymLastCtx2 hit on candidate
          .bit  <2>    (epoch == MatchPosBySym[candSymbol])// MatchPosBySym hit on candidate
          .bit  <3>    (candSymbol == escCandidate)       // candidate is the escape candidate
          .bit  <4>    (candSymbol == FoundSymbol)        // candidate is the previous FoundSymbol
          .bits <0, 8> (SSE0[candSymbol])      // SSE0[sym] sym-type byte at bits 0-7 (may overlap above)
          .bit  <8>    (epoch == SymLastCtx[candSymbol])  // SymLastCtx hit on this candidate
          .bit  <9>    (candSymbol == hintSymRecent                                              // strong position-bias hint
                       || *(uint*)(sse2Base+512) < (uint)(sse2Base[((word)candSymbol-(word)RSContext)&0x1FF]<<7))
          .bit  <10>   (candSymbol == escSymbol)          // candidate is the entry escape symbol
          .bit  <11>   (sumFreqF      < sumFreqLimit)        // freq summary below threshold
          .bit  <12>   ((uint)matchEpoch2 < 0x220));      // recent match
        int* binMixSlotF = &d27[0x4000*mixSseSizeF+2*seeIdxF];
        int freq0F = (word)MixBound2[0x8000*mixSseSizeF+4*seeIdxF];
        binMixCenter = (word*)binMixSlotF;
        // Refresh matchCtxHiSave before the rescale path runs: behaviour-
        // identical to the original (which reloaded matchCtxHiSave inside
        // the same branch that triggers MaybeRescale2_).
        if (freq0F > 0x8000) matchCtxHiSave = MatchCtxHi;
        MaybeRescale2_(binMixSlotF, freq0F);
        int hitsF = *(word*)binMixSlotF;
        sseCum = hitsF;
        *((word*)binMixSlotF+2) = freq0F + *((word*)binMixSlotF+3);
        sseTot = freq0F;
        sse2DenDelta = hitsF;
        sse2NumDelta = freq0F;
        // OrderCtxSeed composite for the per-candidate Sse1 table lookup.
        OrderCtxSeed = OrderCtxSeedBuild_(candSymbol, matchCtxHiSave,
                                          sparseHitsF, orderCtxSeedSave,
                                          (uint)freq0F, (uint)hitsF);
        int* sse1SlotF = &Sse1[2*OrderCtxSeed];
        sse1Slot = sse1SlotF;
        int mixCumWeightF, mixCumFreqF;
        Sse1Step_(sse1SlotF, hitsF, mixCumWeightF, mixCumFreqF);
        uint centerExpandF = binMixCenter[3];
        if( centerExpandF<=8 ) {
          sseTot = mixCumWeightF;
          sseCum = mixCumFreqF;
        } else {
          int* predWBase = &PredWeight[512*(qword)(byte)SEEQTable[candProbBF]+2*(uint)(sparseHitsF<<6)];
          int* predWAF = &predWBase[2*(seeIdxF&0x1F)];
          int  predWAVal = predWAF[1];
          predWeightA = (uint*)predWAF;
          int* predWBF = &predWBase[2*(((uint)seeIdxF>>4)&0x1F)+64];
          predWeightB = (uint*)predWBF;
          char predBoostShiftF = centerExpandF<0x150;
          int  predWBVal = predWBF[1];
          uint predScaleAF = predWBVal+predWAVal;
          uint predScaledAF = (uint)(predWAVal*(sseEntryC2F+2))>>8;
          uint predScaledBF = (uint)(predWBVal*(sseEntryC2F+2))>>8;
          // predBoostF: even index 0..22 derived from predScaleAF's bits 12+,
          // saturated to 24. Used to index a pair of bytes from b41[].
          sqword predBoostF = (predScaleAF >= 0xC000) ? 24
                            : ((predScaleAF >> 12) << 1);
          uint predTotEarlyF = (predScaledAF+predScaledBF >= 0x6000u) ? 24576u : (predScaledAF+predScaledBF);
          int predConstAF = (byte)b41[predBoostF];
          int predConstBF = (byte)b41[predBoostF+1];
          // predWPostF mixes both cells' num-slots (predWBF[0] + predWAF[0])
          // into the running mixCumFreqF accumulator.
          uint predWPostF = ((predConstAF*predTotEarlyF+predConstBF*(*predWBF+*predWAF))>>(predBoostShiftF+7))+mixCumFreqF;
          char predShiftF = predBoostShiftF + (centerExpandF<0x48) + 3;
          uint predDenIncF = ((uint)(192*(predConstAF+predConstBF))>>predBoostShiftF)+mixCumWeightF;
          predDeltaNum = 0x3000u>>predShiftF;
          char predDenShiftF = predBoostShiftF+4;
          predDeltaDen = 0x3000u>>predDenShiftF;
          // each cell's num slot decays by (val >> predShiftF); den slot
          // accumulates the cross-scaled residue. (The original cross-saved
          // predWAOldA/predWBOldA temporaries weren't needed -- the two slots
          // are independent.)
          *predWAF   -= (*predWAF >> predShiftF);
          predWAF[1] -= (predScaledAF+7)>>predDenShiftF;
          *predWBF   -= (*predWBF >> predShiftF);
          predWBF[1] -= (predScaledBF+7)>>predDenShiftF;
          // blend the two neighbour cells (binMixCenter ± 0x8000 words; cell
          // layout: hits at [0], freq at [2]) into (mixCumFreqF,
          // mixCumWeightF) for the PredWeight stage output.
          word* binUp8F = binMixCenter + 0x8000;
          word* binDn8F = binMixCenter - 0x8000;
          BinMixHiG = (sqword)binUp8F;
          BinMixLoG = (sqword)binDn8F;
          mixCumFreqF   = ((binUp8F[0] + binDn8F[0])               >> 3) + predWPostF;
          mixCumWeightF = ((uint)(binUp8F[2] + binDn8F[2])         >> 3) + predDenIncF;
          sseCum = mixCumFreqF;
          sseTot = mixCumWeightF;
          {
            char predDoExpandF = (centerExpandF<0x30)+1;
            binMixDeltaHi = RescaleAccum2_(binUp8F, predDoExpandF);
            binMixDeltaLo = RescaleAccum2_(binDn8F, predDoExpandF);
          }
          // (centerExpandF was read into the outer block; binMixCenter[3]
          // hasn't been touched since, so re-use it here.)
          if( centerExpandF>0x48 ) {
            // Outer cells (binMixCenter ± 0x10000 words) accumulate the
            // expansion delta when the central freq's predExpand counter is
            // beyond the threshold.
            word* binUp16F = binMixCenter + 0x10000;
            word* binDn16F = binMixCenter - 0x10000;
            PredBaseAG = (sqword)binUp16F;
            PredBaseBG = (sqword)binDn16F;
            char predExpShiftF = (centerExpandF<0x1E0)+(centerExpandF<0x3D0)+1;
            predBaseDeltaA = RescaleAccum2_(binUp16F, predExpShiftF);
            predBaseDeltaB = RescaleAccum2_(binDn16F, predExpShiftF);
          }
        }
        int* sseMatchSlotF = &SseMatch[SseMatchIdxBuild_(candSymbol)];
        sseMatchSlot = sseMatchSlotF;
        SseMatchStep_(sseMatchSlotF, (int)(60416LL*mixCumFreqF/mixCumWeightF));
        int cumWeightF = sseCum;
        sqword sse2IdxF = Sse2IdxBuild_(candSymbol, cumWeightF, (uint)sseTot);
        int* sse2SlotF = &Sse2[2*sse2IdxF];
        sse2Slot = sse2SlotF;
        int sse2CumInF  = cumWeightF;
        Sse2Step_(sse2SlotF);
        int sse2CumTotF = sseTot;
        int  sse2HistByteF = sse2Base[((word)candSymbol-(word)RSContext)&0x1FF];
        uint sse2Counter   = *(uint*)(sse2Base+512);
        predWeightDelta = sse2CumTotF;
        int* sse3SlotF = &Sse3[2 * (int)Sse3IdxBuild_(candSymbol, tagSymLastCtx2F,
                                                       localFoundState->iSuccessor,
                                                       (uint)sse2IdxF, sse2Counter,
                                                       (uint)sse2HistByteF)];
        sse3Slot = sse3SlotF;
        cumFreqC = sseCum;
        Sse3Step_(sse3SlotF, sse2CumInF, sse2CumTotF);
        totFreqC = sseTot;
        subRangeC = rc.getSubRange(cumFreqC, totFreqC);
        if( f_DEC ? !rc.IsDecodeMatched(subRangeC) : (inputByte != candSymbol) ) {
          priorFoundStateF = q9;
          cumFreqAcc -= localFoundState->Freq;
          if( f_DEC ) rc.DecodeNotMatched(subRangeC); else rc.encodeEscape(subRangeC);
          SparseBitmapA[SparseIdxA] &= ~SparseBit;
          SparseBitmapB[SparseIdxB] &= ~SparseBit;
          if( priorFoundStateF ) {
            MinContext = MaxContext;
            q9 = 0;
            MixCtx = 0;
          } else if( localFoundState<=MinContext->getStates() ) {
            MinContext = MaxContext;
          } else {
            MinContext = MaxContext;
            wDelta34 = 0x8000;
          }
        } else {
          if( !f_DEC ) rc.encodeSymbol(subRangeC);
          // commit two PredWeight pairs (predDeltaNum, predDeltaDen) at the A and B cells
          predWeightA[0] += predDeltaNum;
          predWeightA[1] += predDeltaDen;
          predWeightB[0] += predDeltaNum;
          predWeightB[1] += predDeltaDen;
          byte flagsCtxFC = MinContext->Flags;
          short freqBoostFC = (matchPosAge>0x4800) + (matchPosAge>0x380) + (matchPosAge>0x80)
                            + ((flagsCtxFC&0x40)==0 || matchPosAge>0xE00) + 4;
          MinContext->Flags = flagsCtxFC&0xF0;
          MinContext->SummFreq += freqBoostFC;
          localFoundState->Freq += freqBoostFC;
          STATE* statesBaseFC = MinContext->getStates();
          if( localFoundState==statesBaseFC ) {
            MinContext = MaxContext;
            if( (sqword)MaxContext==RootContext )
              MixCtx = totFreqC<2*cumFreqC;
          } else {
            // Bubble the matched STATE up toward index 0 (cf. ppmd update1).
            STATE saved = *localFoundState;
            do {
              *localFoundState = *(localFoundState-1);
              localFoundState -= 1;
            } while( localFoundState>statesBaseFC );
            *localFoundState = saved;
            MinContext = MaxContext;
          }
          // localFoundState (RealProcess local) and the global FoundState
          // (q9) are distinct here: RescaleCtx mutates the global FoundState
          // as it compacts the STATE[]. Save into q9 first so RescaleCtx
          // sees us, then copy back into the local for the LABEL_250 read.
          q9 = (sqword)localFoundState;
          if( localFoundState->Freq > 244 ) {
            RescaleCtx(preCommitMinCtx);
            localFoundState = (STATE*)q9;
          }
          if( localFoundState )
            goto LABEL_250;
        }
        if( !--remCandF ) {
          uint rewindMult = predRescaleDiv / (MinContext->NStates + 1);
          // q34 has no captured wDelta; read it back from the slot (word index 3).
          RewindPredictor_(q34, ((word*)q34)[3], rewindMult);
          RewindPredictor_(q33, wDelta33,             rewindMult);
          RewindPredictor_(q32, wDelta32,             rewindMult);
          RewindPredictor_(q31, wDelta31,            rewindMult);
          RewindPredictor_(q30, wDelta30,            rewindMult);
          RewindPredictor_(q29, wDelta29,            rewindMult);
          entryNStates = MinContext->NStates;
          goto LABEL_128;
        }
        predShiftFlags = wDelta34;
        predBinFlags = wDelta35;
        escSymbol = MixCtx3;
        epoch = SymCount;
        escCandidate = EscapeSymbol;
        chainPtr = (STATE**)CtxChainEnd;
        orderCtxSeedSave = OrderCtxSeed;
        sumFreqF = cumFreqAcc;
        sumFreqLimit = cumFreqMixSave;
        seeIdxBase = sseIdxStorage;
      }
    }
    if( !f_DEC ) rc.encodeSymbol(subRange);
    localFoundState = &MinContext->oneState();
    q9 = (sqword)localFoundState;       // publish to global FoundState (alias of q9)
    MixCtx = 1;
    // PE's variant of ppmd's "Freq += (Freq < MAX_FREQ-3)" cap, plus an
    // extra bump on the very first hit (Freq==1) when the candidate is
    // well-predicted in context (totFreq < 4*cumFreq). Block-scoped so
    // the goto LABEL_250 elsewhere doesn't bypass the initializers.
    {
      int oneStateFreqF = localFoundState->Freq;
      byte freqIncCap   = (oneStateFreqF < 127);
      byte firstHitBump = (oneStateFreqF == 1 && totFreq < 4u*(uint)cumFreq);
      localFoundState->Freq  = oneStateFreqF + freqIncCap + firstHitBump;
    }
    // commit the per-step predictor deltas (no freq0 rewind in this path)
    binSseCell[0] += 1568;
    *(uint*)q32 += wDelta32;
    *(uint*)q31 += wDelta31;
    *(uint*)q30 += wDelta30;
    *(uint*)q29 += wDelta29;
    *(uint*)q34 += wDelta34;
    *(uint*)q35 += wDelta35;
    MinContext = MaxContext;
LABEL_250:
    // -----------------------------------------------------------------------
    //  SYMBOL_FOUND tail (~ ppmd PrepareNextStep): emit the decoded byte,
    //  commit the range, run MixUpdate to advance the SSE / mixing state,
    //  and normalize the range coder for the next iteration.
    // -----------------------------------------------------------------------
    if( f_DEC ) putc(localFoundState->Symbol, outFile);
    rc.commitRange();
    result = MixUpdate(MinContext);
    if( f_DEC ) rc.DecodeNormalize(inFile); else rc.EncodeNormalize(outFile);
    epoch = SymCount;
  } while( SymCount );
  return result;
}

int RealDecode(FILE* outFile, FILE* inFile) { return RealProcess<1>(outFile, inFile); }

int RealEncode(FILE* outFile, FILE* inFile) {
  return RealProcess<0>(outFile, inFile);
}
//--- #return
//--- #include "stats.inc"

sqword PPMIIEncode(FILE* File, FILE* outFile, sqword (*statsCB)(FILE*, FILE*, sqword), int initMode) {
  int statsResult;

  if( !SubAllocatorSize ) return 0;

  if( Interrupted ) {
    Interrupted = 0;
    SymCount = 1;
  } else {
    rc.initEncoder();
    StartModelRare(initMode);
  }

  while( 1 ) {
    RealEncode(File, outFile);
    if( SymCount ) break;
    if( statsCB ) statsResult = statsCB(outFile, File, 0); else statsResult = -1;
    SymCount = statsResult;
    memset(SymMask, 0, sizeof(SymMask));
    // Clear SymLastCtx + SymLastCtx2 + MatchPosBySym (the three aliased
    // 256-int sub-arrays at the start of the 1024-int SymLastCtx[] block;
    // 768 ints = 0xC00 bytes).
    memset(SymLastCtx, 0, 3*256*sizeof(int));
    if( !statsResult ) {
      Interrupted = 1;
      return 0;
    }
  }
  rc.Flush(File);

  if( statsCB ) statsCB(outFile, File, 1);

  return 1;
}

sqword PPMIIDecode(FILE* inFile, FILE* outFile, sqword (*statsCB)(FILE*, FILE*, sqword), int initMode) {
  int statsResult;

  if( !SubAllocatorSize ) return 0;

  if( Interrupted ) {
    Interrupted = 0;
    SymCount = 1;
  } else {
    rc.initDecoder(outFile);
    StartModelRare(initMode);
  }

  while(1) {
    RealDecode(inFile, outFile);

    if( SymCount ) break;

    if( statsCB ) statsResult = statsCB(inFile, outFile, 0); else statsResult = -1;

    SymCount = statsResult;

    memset(SymMask, 0, sizeof(SymMask) );
    // SymLastCtx + SymLastCtx2 + MatchPosBySym (see PPMIIEncode for layout)
    memset(SymLastCtx, 0, 3*256*sizeof(int));

    if( !statsResult ) {
      Interrupted = 1;
      return 0;
    }
  }

  if( statsCB ) statsCB(inFile, outFile, 1);

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

      uint memoryMB    = arch_hdr.ModelSize  + 1;
      uint modelOrder  = arch_hdr.ModelOrder + 2;
      int  resetMethod = arch_hdr.CutOff;

      PPMIIDeleteModel();
      if( !StartSubAllocator(memoryMB, modelOrder, resetMethod) ) {
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
