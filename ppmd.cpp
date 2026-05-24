typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned long QWORD;
typedef unsigned int UINT;
typedef BYTE _BYTE;
typedef WORD _WORD;
typedef DWORD _DWORD;

#include <assert.h>
#include <climits>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <dirent.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <utime.h>

#define stricmp strcmp

typedef UINT (*_PPMII_PRINT_INFO)(FILE* DecodedFile, FILE* EncodedFile, BOOL LastCall);
template <class T> T MIN(T x, T y) {
  return (x<y) ? x : y;
}

template <class T> T MAX(T x, T y) {
  return (x>y) ? x : y;
}

template <class T> void Prefetch(T* Addr) {
  BYTE PrefetchByte = *(volatile BYTE*)Addr;
}

const DWORD PPMdSignature = 0x84ACAF8F;
enum { PROG_VAR = 'J', MAX_O = 16 };
template <class T> T CLAMP(const T &X, const T &LoX, const T &HiX) {
  return (X>=LoX) ? ((X<=HiX) ? (X) : (HiX)) : (LoX);
}

template <class T> void SWAP(T &t1, T &t2) {
  T tmp = t1;
  t1 = t2;
  t2 = tmp;
}

typedef FILE _PPMD_FILE;
extern "C" {
BOOL PPMIICreateModel(UINT ModelSize = 256, int ModelOrder = 5, BOOL CutOff = 0);
UINT PPMIIGetCurrentModelSize();
BOOL PPMIIEncode(FILE* EncodedFile, FILE* DecodedFile, _PPMII_PRINT_INFO PrintInfoFunc = NULL, BOOL SolidMode = 0);
BOOL PPMIIDecode(FILE* DecodedFile, FILE* EncodedFile, _PPMII_PRINT_INFO PrintInfoFunc = NULL, BOOL SolidMode = 0);
UINT PPMIIDeleteModel();
}
#pragma hdrstop
enum { UNIT_SIZE = 12, N1 = 5, N2 = 3, N3 = 3, N4 = (128+3-1*N1-2*N2-3*N3)/4, N_INDEXES = N1+N2+N3+N4, MEM_DIVISOR = 10 };
UINT U2B(UINT NU) {
  return 8*NU+4*NU;
}

BYTE Indx2Units[N_INDEXES], Units2Indx[128];
BYTE RLQTable[12], SSE0QTable[72], NextBinFreq[72], SSE1QTable[64], SEEQTable[256];
BYTE SymType[256];
_BYTE* HeapNull;
_DWORD Ptr2Indx(const void* p) {
  return ((_BYTE*)p)-HeapNull;
}

void*Indx2Ptr(_DWORD indx) {
  return (void*)(HeapNull+indx);
}

#pragma pack(1)
struct MEM_BLK {
  union {
    struct {
      _BYTE NU, Stamp;
    };
    _DWORD QueueSize;
  };
  _DWORD Next;
  _DWORD Prev;
  MEM_BLK*next() const {
    return (MEM_BLK*)Indx2Ptr(Next);
  }

  MEM_BLK*prev() const {
    return (MEM_BLK*)Indx2Ptr(Prev);
  }

  BOOL avail() const {
    return (QueueSize!=0);
  }

  BOOL canMerge() const {
    return (Stamp==_BYTE(-1));
  }

  void linkNext(MEM_BLK* p, UINT NU, _BYTE Stamp = _BYTE(-1));
  void linkPrev(MEM_BLK* p, UINT NU);
  void selfUnlink(MEM_BLK* BList);
  MEM_BLK*unlinkNext();
  MEM_BLK*unlinkPrev();
}* BList;
#pragma pack()
void MEM_BLK::linkNext(MEM_BLK* p, UINT NU, _BYTE Stamp) {
  p->Stamp = Stamp;
  p->NU = NU;
  p->Prev = Ptr2Indx(this);
  p->Next = Next;
  Next = next()->Prev = Ptr2Indx(p);
  QueueSize++;
}

void MEM_BLK::linkPrev(MEM_BLK* p, UINT NU) {
  p->Stamp = _BYTE(-1);
  p->NU = NU;
  p->Next = Ptr2Indx(this);
  p->Prev = Prev;
  Prev = prev()->Next = Ptr2Indx(p);
  QueueSize++;
}

void MEM_BLK::selfUnlink(MEM_BLK* BList) {
  next()->Prev = Prev;
  prev()->Next = Next;
  BList[Units2Indx[NU-1]].QueueSize--;
}

MEM_BLK*MEM_BLK::unlinkNext() {
  MEM_BLK* p = next();
  Next = p->Next;
  p->next()->Prev = Ptr2Indx(this);
  QueueSize--;
  return p;
}

MEM_BLK*MEM_BLK::unlinkPrev() {
  MEM_BLK* p = prev();
  Prev = p->Prev;
  p->prev()->Next = Ptr2Indx(this);
  QueueSize--;
  return p;
}

_BYTE* HeapStart, * pText, * UnitsStart, * LoUnit, * HiUnit;
size_t SubAllocatorSize = 0;
UINT CutOffCount, GlueCount, InitsCount;
UINT PPMIIGetCurrentModelSize() {
  if( !SubAllocatorSize )
    return 0;
  UINT RetVal = SubAllocatorSize-(HiUnit-LoUnit)-(UnitsStart-pText);
  for( UINT i = 0; i<N_INDEXES; i++ )
    RetVal -= U2B(Indx2Units[i]*BList[i].QueueSize);
  return RetVal;
}

size_t GetSizeOfUnitsSection(size_t TotalSize) {
  return U2B(TotalSize/(UNIT_SIZE*MEM_DIVISOR)*(MEM_DIVISOR-1));
}

UINT PPMIIDeleteModel() {
  if( !SubAllocatorSize )
    return 0;
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

BOOL StartSubAllocator(UINT SASize) {
  if( SubAllocatorSize )
    return 0;
  HeapStart = (_BYTE*)malloc(sizeof(_BYTE)*(SASize<<20U));
  if( !HeapStart )
    return 0;
  SubAllocatorSize = SASize<<20U;
  InitsCount = 0;
  return 1;
}

void InitSubAllocator() {
  BList = (MEM_BLK*)HeapStart;
  pText = (_BYTE*)&BList[N_INDEXES];
  HiUnit = HeapStart+SubAllocatorSize;
  InitsCount++;
  size_t USSize = GetSizeOfUnitsSection(SubAllocatorSize);
  LoUnit = UnitsStart = HiUnit-USSize;
  *(_DWORD*)LoUnit = 0;
  HeapNull = HeapStart-1;
  for( UINT i = CutOffCount = GlueCount = 0; i<N_INDEXES; BList[i++].QueueSize = 0 )
    BList[i].Next = BList[i].Prev = Ptr2Indx(BList+i);
}

void FreeUnitsRare(MEM_BLK* p, UINT NU) {
  UINT n, i;
  while( p[NU].canMerge() ) {
    p[NU].selfUnlink(BList);
    NU += p[NU].NU;
  }
  for(; NU>128; p += 128, NU -= 128 )
    BList[N_INDEXES-1].linkNext(p, 128);
  if( NU!=(n = Indx2Units[i = Units2Indx[NU-1]]) ) {
    n = Indx2Units[--i];
    BList[NU-n-1].linkNext(p+n, NU-n);
  }
  BList[i].linkNext(p, n);
}

void FreeUnits(void* ptr, UINT NU) {
  UINT indx = Units2Indx[NU-1];
  NU = Indx2Units[indx];
  MEM_BLK* p = (MEM_BLK*)ptr;
  (!p[NU].canMerge()) ? (BList[indx].linkNext(p, NU)) : (FreeUnitsRare(p, NU));
}

void FreeContext(void* ptr) {
  MEM_BLK* p = (MEM_BLK*)ptr;
  (!p[1].canMerge()) ? (BList->linkPrev(p, 1)) : (FreeUnitsRare(p, 1));
}

void*AllocUnitsRare(UINT indx);
void*AllocUnits(UINT NU) {
  UINT indx = Units2Indx[NU-1];
  if( BList[indx].avail() )
    return BList[indx].unlinkNext();
  void* RetVal = LoUnit;
  LoUnit += (NU = U2B(Indx2Units[indx]));
  if( LoUnit<=HiUnit ) {
    if( LoUnit!=HiUnit )
      *(DWORD*)LoUnit = 0;
    return RetVal;
  }
  LoUnit -= NU;
  return AllocUnitsRare(indx);
}

void GlueFreeBlocks() {
  MEM_BLK* p, * Barrier = ((MEM_BLK*)(HeapStart+SubAllocatorSize))-1, tmp = *Barrier;
  for( UINT i = 0; i<N_INDEXES; i++ )
    for( BList[i].linkNext(Barrier, 1, _BYTE(-2)); (p = BList[i].unlinkPrev())!=Barrier; FreeUnits(p, p->NU) )
      Prefetch(&(BList[i].prev()->prev()->Next));
  *Barrier = tmp;
  GlueCount++;
}

void*AllocUnitsRare(UINT indx) {
  UINT i = indx, NU = Indx2Units[indx];
  do {
    if( ++i==N_INDEXES ) {
      if( !GlueCount ) {
        GlueFreeBlocks();
        return AllocUnits(Indx2Units[indx]);
      } else if( !CutOffCount&&UnitsStart-U2B(NU)>pText )
        return (UnitsStart -= U2B(NU));
      else
        return NULL;
    }
  } while( !BList[i].avail() );
  MEM_BLK* p = BList[i].unlinkNext();
  FreeUnitsRare(p+NU, Indx2Units[i]-NU);
  return p;
}

void*AllocContext() {
  if( HiUnit!=LoUnit )
    return (HiUnit -= UNIT_SIZE);
  return (BList->avail()) ? (BList->unlinkPrev()) : (AllocUnitsRare(0));
}

void UnitsCpy(void* Dest, void* Src, UINT NU) {
  _DWORD* p1 = (_DWORD*)Dest, * p2 = (_DWORD*)Src;
  if( (NU&1)!=0 ) {
    p1[0] = p2[0];
    p1[1] = p2[1];
    p1[2] = p2[2];
    p1 += 3;
    p2 += 3;
  }
  for( NU >>= 1; NU!=0; NU--, p1 += 6, p2 += 6 ) {
    p1[0] = p2[0];
    p1[1] = p2[1];
    p1[2] = p2[2];
    p1[3] = p2[3];
    p1[4] = p2[4];
    p1[5] = p2[5];
  }
}

void*ExpandUnits(void* OldPtr, UINT OldNU) {
  UINT i0 = Units2Indx[OldNU-1], i1 = Units2Indx[OldNU-1+1];
  if( i0==i1 )
    return OldPtr;
  void* p = AllocUnits(OldNU+1);
  if( p ) {
    UnitsCpy(p, OldPtr, OldNU);
    FreeUnits(OldPtr, OldNU);
  }
  return p;
}

void*ShrinkUnits(void* OldPtr, UINT OldNU, UINT NewNU) {
  UINT i0 = Units2Indx[OldNU-1], i1 = Units2Indx[NewNU-1];
  if( i0==i1 )
    return OldPtr;
  if( BList[i1].avail() ) {
    void* ptr = BList[i1].unlinkNext();
    UnitsCpy(ptr, OldPtr, NewNU);
    FreeUnits(OldPtr, OldNU);
    return ptr;
  } else {
    NewNU = Indx2Units[i1];
    FreeUnitsRare(((MEM_BLK*)OldPtr)+NewNU, Indx2Units[i0]-NewNU);
    return OldPtr;
  }
}

void*MoveUnits(void* OldPtr, UINT NU) {
  UINT i = Units2Indx[NU-1], NewNU = Indx2Units[i];
  MEM_BLK* p = (MEM_BLK*)OldPtr;
  if( !p[NewNU].canMerge()||!BList[i].avail() )
    return OldPtr;
  void* NewPtr = BList[i].unlinkNext();
  UnitsCpy(NewPtr, OldPtr, NU);
  FreeUnitsRare(p, NewNU);
  return NewPtr;
}

void*MoveContext(void* OldPtr) {
  MEM_BLK* p = (MEM_BLK*)OldPtr;
  if( !p[1].canMerge()||!BList->avail() )
    return OldPtr;
  void* NewPtr = BList->unlinkPrev();
  UnitsCpy(NewPtr, OldPtr, 1);
  FreeUnitsRare(p, 1);
  return NewPtr;
}

void FinishCutOff() {
  pText = (_BYTE*)&BList[N_INDEXES];
  GlueCount = 0;
  CutOffCount++;
}

struct PPMII_STARTUP {
  PPMII_STARTUP();
} const PPMIIStartUp;
const BYTE RLSM[2][12] = {{0, 1, 1, 1, 2, 2, 6, 6, 6, 7, 10, 11}, {0, 0, 0, 0, 1, 1, 1, 1, 5, 5, 6, 11}};
const BYTE RLQBounds[] = {0, 1, 6, 0};
const BYTE SSE0QBounds[] = {0, 1, 2, 3, 4, 6, 9, 14, 22, 35, 70, 153, 253};
const BYTE SSE1QBounds[] = {0, 2, 4, 7, 10, 13, 16, 20, 25, 30, 35, 41, 46, 51, 63};
const BYTE SEEQBounds[] = {1, 2, 4, 7, 15, 28, 50, 81, 127, 204, 242, 82};
PPMII_STARTUP::PPMII_STARTUP() {
  int i, k;
  for( k = 1, i = 0; i<N1; i++, k += 1 )
    Indx2Units[i] = k;
  for( k++; i<N1+N2; i++, k += 2 )
    Indx2Units[i] = k;
  for( k++; i<N1+N2+N3; i++, k += 3 )
    Indx2Units[i] = k;
  for( k++; i<N1+N2+N3+N4; i++, k += 4 )
    Indx2Units[i] = k;
  for( k = i = 0; k<128; k++ ) {
    i += (Indx2Units[i]<k+1);
    Units2Indx[k] = i;
  }
  memset(SymType, 0x04*0, 64);
  memset(SymType+64, 0x04*1, 256-64);
  for( i = 0; i<72; i++ )
    NextBinFreq[i] = i+1;
  NextBinFreq[0]++;
  NextBinFreq[71]--;
  for( i = k = 0; i<12; i++ )
    RLQTable[i] = 16*k, k += (i==RLQBounds[k]);
  for( i = k = 0; i<72; i++ )
    SSE0QTable[i] = k, k += (i==SSE0QBounds[k]);
  for( i = k = 0; i<64; i++ )
    SSE1QTable[i] = k, k += (i==SSE1QBounds[k]);
  for( i = k = 0; i<256; i++ )
    SEEQTable[i] = k, k += (i==SEEQBounds[k]);
}

enum { TOP = 1<<24, BOT = 1<<15 };
struct SUBRANGE {
  WORD low, high, scale;
} Range;
DWORD low, code, range;
void rcInitEncoder() {
  low = 0;
  range = UINT_MAX;
}

void rcEncodeSymbol() {
  low += Range.low*(range /= Range.scale);
  range *= Range.high-Range.low;
}

void rcFlushEncoder(FILE* stream) {
  for( UINT i = 0; i<4; i++ ) {
    putc(low>>24, stream);
    low <<= 8;
  }
}

void rcInitDecoder(FILE* stream) {
  low = code = 0;
  range = UINT_MAX;
  for( UINT i = 0; i<4; i++ )
    code = (code<<8)|getc(stream);
}

UINT rcGetCurrentCount() {
  return (code-low)/(range /= Range.scale);
}

void rcRemoveSubrange() {
  low += range*Range.low;
  range *= Range.high-Range.low;
}

UINT rcBinStart(UINT f0, UINT Shift) {
  return f0*(range >>= Shift);
}

UINT rcBinDecode(UINT tmp) {
  return (code-low>=tmp);
}

void rcBinCorrect0(UINT tmp) {
  range = tmp;
}

void rcBinCorrect1(UINT tmp, UINT f1) {
  low += tmp;
  range *= f1;
}

enum { INT_BITS = 6, PERIOD_BITS = 7, TOT_BITS = INT_BITS+PERIOD_BITS, INTERVAL = 1<<INT_BITS, BIN_SCALE = 1<<TOT_BITS, ROUND0 = 31, ROUND1 = 53, H_BITS = 15, H_SHIFT = 5, H_SIZE = 1<<H_BITS, H_MASK = H_SIZE-1 };
#pragma pack(1)
struct SEE_CONTEXT {
  enum { MAX_SHIFT = 8 };
  WORD Summ;
  BYTE Shift, Count;
  void init(UINT InitVal) {
    Summ = InitVal<<(Shift = 3);
    Count = 14;
  }

  WORD getMean() {
    if( --Count==0 )
      tune_rare();
    WORD RetVal = (Summ>>Shift);
    Summ -= RetVal;
    return RetVal+!RetVal;
  }

  void tune_rare();
};
struct PPM_CONTEXT;
struct STATE {
  _BYTE Symbol, Freq;
  _DWORD iSuccessor;
  PPM_CONTEXT*getSuccessor() const {
    return (PPM_CONTEXT*)Indx2Ptr(iSuccessor);
  }

  BOOL hasSuccessor() const {
    return ((_BYTE*)Indx2Ptr(iSuccessor)>=UnitsStart);
  }
};
struct PPM_CONTEXT {
  enum { MAX_FREQ = 123, O_BOUND = 9 };
  _BYTE NStates, Flags;
  _WORD SummFreq;
  _DWORD iStates;
  _DWORD iSuffix;
  STATE*encode0(int symbol);
  STATE*encodeLES1(int symbol);
  STATE*encode1(int symbol);
  STATE*encode2(int symbol);
  STATE*decode0();
  STATE*decodeLES1();
  STATE*decode1();
  STATE*decode2();
  STATE*update1(STATE* p);
  STATE*update2(STATE* p);
  SEE_CONTEXT*makeEsc1Freq() const;
  SEE_CONTEXT*makeEsc2Freq() const;
  STATE*auxFindAndUpdate(_BYTE Sym, _BYTE Add);
  STATE*rescale(STATE* p);
  _DWORD cutOff(UINT Order);
  STATE &oneState() const {
    return (STATE &)SummFreq;
  }

  STATE*getStates() const {
    return (STATE*)Indx2Ptr(iStates);
  }

  PPM_CONTEXT*getSuffix() const {
    return (PPM_CONTEXT*)Indx2Ptr(iSuffix);
  }

  void prefetchStates() const {
    int i = NStates+1;
    const _BYTE* pb = (const _BYTE*)getStates();
    Prefetch(pb+i);
    Prefetch(pb += 2*i);
    Prefetch(pb+i);
    Prefetch(pb += 2*i);
    Prefetch(pb+i);
    Prefetch(pb+2*i-1);
  }
};
#pragma pack()
PPM_CONTEXT* MaxContext;
UINT RSContext, OrderFall, OrderFall0, MaxOrder;
BYTE RunLength, NMasked;
WORD EscList[MAX_O];
UINT SymCount, SymMask[256];
WORD SSE0[12][64];
WORD SSE1[15][16];
SEE_CONTEXT SEE1[12][64], SEE2[12][32], DummySEE;
BYTE RecentSymbol[H_SIZE];
BOOL CutOff, Interrupted;
void SWAP(STATE &s1, STATE &s2) {
  _WORD t1 = (_WORD &)s1;
  _DWORD t2 = s1.iSuccessor;
  (_WORD &)s1 = (_WORD &)s2;
  s1.iSuccessor = s2.iSuccessor;
  (_WORD &)s2 = t1;
  s2.iSuccessor = t2;
}

void StateCpy(STATE &s1, const STATE &s2) {
  (_WORD &)s1 = (_WORD &)s2;
  s1.iSuccessor = s2.iSuccessor;
}

void MoveStateUp(STATE* p) {
  ((_WORD*)p)[0+3] = ((_WORD*)p)[0];
  ((_WORD*)p)[1+3] = ((_WORD*)p)[1];
  ((_WORD*)p)[2+3] = ((_WORD*)p)[2];
}

void SEE_CONTEXT::tune_rare() {
  if( Summ>4*1024 ) {
    if( Summ<8*1024 )
      ;
    else if( Shift>5 ) {
      Summ >>= 1;
      Shift--;
    } else if( Summ>32*1024 )
      Summ = 32*1024;
    Count = 1<<Shift;
  } else if( Shift<MAX_SHIFT ) {
    Summ += Summ+32;
    Count = 3<<Shift++;
  } else
    Summ += 32;
}

BOOL PPMIICreateModel(UINT ModelSize, int ModelOrder, BOOL bCutOff) {
  if( !ModelSize||ModelSize>(UINT(-1)>>20)||ModelOrder<2||ModelOrder>MAX_O||!StartSubAllocator(ModelSize) )
    return 0;
  MaxOrder = ModelOrder;
  CutOff = bCutOff;
  Interrupted = 0;
  RunLength = 0xFF;
  return 1;
}

void StartModelRare(int Mode) {
  int i, k, s;
  OrderFall0 = OrderFall = MaxOrder;
  memset(SymMask, 0, sizeof(SymMask));
  SymCount = 1;
  if( Mode==1&&RunLength!=0xFF ) {
    for( PPM_CONTEXT* pc = MaxContext; pc->iSuffix!=0; pc = pc->getSuffix() )
      OrderFall--;
    OrderFall0 = OrderFall;
    return;
  }
  InitSubAllocator();
  MaxContext = (PPM_CONTEXT*)AllocContext();
  MaxContext->NStates = 255;
  MaxContext->SummFreq = 256;
  MaxContext->iStates = Ptr2Indx(AllocUnits(256/2));
  STATE* p = MaxContext->getStates();
  for( MaxContext->Flags = MaxContext->iSuffix = i = 0; i<256; i++, p++ ) {
    p->Symbol = i;
    p->Freq = 1;
    p->iSuccessor = 0;
  }
  if( Mode==2&&RunLength!=0xFF )
    return;
  RunLength = RSContext = 0;
  memset(RecentSymbol, 0, sizeof(RecentSymbol));
  static const signed char Coef0[] = {-28, 29, -50, -59, -36, -52};
  for( k = 0; k<64; k++ ) {
    for( s = i = 0; i<6; i++ )
      s += (2*((k>>i)&1)-1)*Coef0[i];
    s = CLAMP(240+s, 10, 233)<<(TOT_BITS-7);
    for( i = 0; i<12; i++ )
      SSE0[i][k] = BIN_SCALE-s/(SSE0QBounds[i+1]+1);
  }
  for( i = 0; i<15; i++ ) {
    s = MIN(SSE1QBounds[i]+2, 58)<<(TOT_BITS-6);
    for( k = 0; k<16; k++ )
      SSE1[i][k] = s;
  }
  for( i = 0; i<12; i++ ) {
    DummySEE.init(SEEQBounds[i]+8);
    for( k = 0; k<64; k++ )
      SEE1[i][k] = DummySEE;
    for( k = 0; k<32; k++ )
      SEE2[i][k] = DummySEE;
  }
}

void AuxCutOff(STATE* p, UINT Order) {
  if( Order<MaxOrder ) {
    PPM_CONTEXT* pc = p->getSuccessor();
    Prefetch(pc->getStates());
    p->iSuccessor = pc->cutOff(Order+1);
  } else
    p->iSuccessor = 0;
}

_DWORD PPM_CONTEXT::cutOff(UINT Order) {
  int i, k, f, s, NU, Scale;
  STATE* p, * p0, * p1;
  if( !NStates ) {
    if( (p = &oneState())->hasSuccessor() ) {
      AuxCutOff(p, Order);
      if( p->iSuccessor||Order<O_BOUND )
        goto AT_RETURN;
    }
REMOVE:
    FreeContext(this);
    return 0;
  }
  prefetchStates();
  p = p1 = p0 = getStates();
  NU = ((k = i = NStates)+2)>>1;
  do {
    if( p->hasSuccessor() ) {
      if( p!=p1 )
        SWAP(*p1, *p);
      Prefetch(p1->getSuccessor());
      p1++;
    } else {
      p->iSuccessor = 0;
      i--;
    }
    p++;
  } while( --k>=0 );
  if( i!=NStates&&Order ) {
    NStates = i;
    if( i<0 ) {
      FreeUnits(p0, NU);
      goto REMOVE;
    } else if( i==0 ) {
      Flags = (Flags&0x08)+SymType[p0->Symbol];
      s = SummFreq-(f = p0->Freq-1)+11;
      p0->Freq = (2*f<=s) ? (4*f>s) : (2+f/s);
      StateCpy(oneState(), *p0);
      FreeUnits(p0, NU);
      p0 = &oneState();
    } else {
      iStates = Ptr2Indx(p = p0 = (STATE*)ShrinkUnits(p0, NU, (i+2)>>1));
      Scale = (SummFreq>19*i);
      Flags = (Flags&(0x0A+0x10*Scale))+SymType[p->Symbol];
      SummFreq = p->Freq = (p->Freq+Scale)>>Scale;
      do {
        Flags |= SymType[(++p)->Symbol];
        SummFreq += (p->Freq = (p->Freq+Scale)>>Scale);
      } while( --i );
      i = NStates;
    }
  } else
    iStates = Ptr2Indx(p0 = (STATE*)MoveUnits(p0, NU));
  p0 += i;
  do {
    AuxCutOff(p0--, Order);
  } while( --i>=0 );
AT_RETURN:
  if( Order==MaxOrder )
    return Ptr2Indx(MoveContext(this));
  return Ptr2Indx(this);
}

void RestoreModelRare(PPM_CONTEXT* pc) {
  if( !CutOff ) {
    StartModelRare(2);
    return;
  }
  if( MaxContext->NStates==1&&pc->NStates==0 )
    for( PPM_CONTEXT* pc1 = MaxContext; pc1!=pc; pc1 = pc1->getSuffix() ) {
      STATE* p = pc1->getStates();
      int i = (p->Symbol!=pc->oneState().Symbol);
      pc1->Flags = (pc1->Flags&0x08)+SymType[p[i].Symbol];
      p[i].Freq >>= 2;
      StateCpy(pc1->oneState(), p[i]);
      pc1->NStates = 0;
      FreeUnits(p, 1);
    }
  while( MaxContext->iSuffix )
    MaxContext = MaxContext->getSuffix();
  OrderFall0 = OrderFall = MaxOrder;
  MaxContext->cutOff(0);
  FinishCutOff();
}

STATE*PPM_CONTEXT::auxFindAndUpdate(_BYTE Sym, _BYTE Add) {
  _BYTE sym;
  STATE* p;
  if( NStates ) {
    if( (p = getStates())->Symbol!=Sym )
      do {
        sym = p[1].Symbol;
        p++;
      } while( sym!=Sym );
    p->Freq += Add;
    SummFreq += Add;
    if( p->Freq>MAX_FREQ ) {
      OrderFall++;
      p = rescale(p);
      OrderFall--;
    }
  } else {
    p = &oneState();
    p->Freq += (p->Freq<35);
  }
  return p;
}

_DWORD CreateSuccessors(BOOL Skip, STATE* p, PPM_CONTEXT* pc, STATE* FoundState);
_DWORD ReduceOrder(STATE* p, PPM_CONTEXT* pc, STATE* FoundState) {
  PPM_CONTEXT* pc1 = pc;
  _DWORD iUpBranch = FoundState->iSuccessor = Ptr2Indx(pText);
  _BYTE sym = FoundState->Symbol;
  OrderFall++;
  if( p ) {
    pc = pc->getSuffix();
    goto LOOP_ENTRY;
  }
  for(;; ) {
    if( !pc->iSuffix )
      return Ptr2Indx(pc);
    p = (pc = pc->getSuffix())->auxFindAndUpdate(sym, 2);
LOOP_ENTRY:
    if( p->iSuccessor )
      break;
    p->iSuccessor = iUpBranch;
    OrderFall++;
  }
  if( p->iSuccessor<=iUpBranch )
    p->iSuccessor = CreateSuccessors(0, NULL, pc, p);
  if( OrderFall==1&&pc1==MaxContext ) {
    FoundState->iSuccessor = p->iSuccessor;
    pText--;
  }
  return p->iSuccessor;
}

STATE*PPM_CONTEXT::rescale(STATE* p) {
  UINT f0, sf, a = (OrderFall!=0), k = 0, i = NStates;
  STATE tmp, * p1;
  for( p1 = getStates(); p!=p1; p-- )
    SWAP(p[0], p[-1]);
  Flags = (Flags&0x08)+SymType[p->Symbol];
  f0 = p->Freq;
  sf = SummFreq;
  SummFreq = p->Freq = (p->Freq+1)>>1;
  do {
    p++;
    SummFreq += (p->Freq = (p->Freq+a)>>1);
    if( p->Freq )
      Flags |= SymType[p->Symbol];
    else
      k++;
    if( p[0].Freq>p[-1].Freq ) {
      StateCpy(tmp, *(p1 = p));
      do {
        MoveStateUp(--p1);
      } while( tmp.Freq>p1[-1].Freq );
      StateCpy(*p1, tmp);
    }
  } while( --i );
  if( k ) {
    a = (NStates+2)>>1;
    if( (NStates -= k)==0 ) {
      StateCpy(tmp, *getStates());
      tmp.Freq = MAX_FREQ/8;
      FreeUnits(getStates(), a);
      StateCpy(oneState(), tmp);
      return &oneState();
    }
    iStates = Ptr2Indx(ShrinkUnits(getStates(), a, (NStates+2)>>1));
  }
  p = getStates();
  Flags |= 0x10;
  if( OrderFall ) {
    a = sf-f0;
    a = MIN((f0*SummFreq-sf*p->Freq+a-1)/a+2, MAX_FREQ/4U);
  } else
    a = 2;
  p->Freq += a;
  SummFreq += a;
  return p;
}

_DWORD CreateSuccessors(BOOL Skip, STATE* p, PPM_CONTEXT* pc, STATE* FoundState) {
  PPM_CONTEXT ct;
  _DWORD iUpBranch = FoundState->iSuccessor;
  STATE* ps[MAX_O], ** pps = ps;
  UINT cf, sf;
  _BYTE tmp, sym = FoundState->Symbol;
  if( !Skip ) {
    *pps++ = FoundState;
    if( !pc->iSuffix )
      goto NO_LOOP;
  }
  if( p ) {
    pc = pc->getSuffix();
    goto LOOP_ENTRY;
  }
  do {
    Prefetch((pc = pc->getSuffix())->getSuffix());
    p = pc->auxFindAndUpdate(sym, 1+(RunLength<2));
LOOP_ENTRY:
    if( p->iSuccessor!=iUpBranch ) {
      pc = p->getSuccessor();
      break;
    }
    *pps++ = p;
  } while( pc->iSuffix );
NO_LOOP:
  Prefetch(pc);
  if( pps==ps )
    return Ptr2Indx(pc);
  ct.NStates = 0;
  ct.Flags = SymType[sym]<<1;
  ct.oneState().Symbol = sym = *(_BYTE*)Indx2Ptr(iUpBranch);
  ct.oneState().iSuccessor = Ptr2Indx((_BYTE*)Indx2Ptr(iUpBranch)+1);
  Prefetch(pc->getStates());
  ct.Flags |= SymType[sym];
  if( pc->NStates ) {
    if( (p = pc->getStates())->Symbol!=sym )
      do {
        tmp = p[1].Symbol;
        p++;
      } while( tmp!=sym );
    sf = pc->SummFreq-(cf = p->Freq-1)+7;
    ct.oneState().Freq = (2*cf<=sf) ? (8*cf>sf) : (2+cf/sf);
  } else
    ct.oneState().Freq = pc->oneState().Freq;
  do {
    PPM_CONTEXT* pc1 = (PPM_CONTEXT*)AllocContext();
    if( !pc1 )
      return 0;
    ((_DWORD*)pc1)[0] = ((_DWORD*)&ct)[0];
    ((_DWORD*)pc1)[1] = ((_DWORD*)&ct)[1];
    pc1->iSuffix = Ptr2Indx(pc);
    (*--pps)->iSuccessor = Ptr2Indx(pc = pc1);
  } while( pps!=ps );
  return Ptr2Indx(pc);
}

void UpdateModel(PPM_CONTEXT* MinContext, STATE* FoundState) {
  _BYTE FSymbol = FoundState->Symbol;
  UINT i, ns, cf, sf, FFreq = FoundState->Freq;
  _DWORD iSuccessor, iFSuccessor = FoundState->iSuccessor;
  PPM_CONTEXT* pc, * pc1;
  STATE* p = NULL;
  if( RunLength<6&&MinContext->iSuffix )
    p = MinContext->getSuffix()->auxFindAndUpdate(FSymbol, 2+!RunLength);
  pc = MaxContext;
  if( !OrderFall&&iFSuccessor ) {
    FoundState->iSuccessor = CreateSuccessors(1, p, MinContext, FoundState);
    if( !FoundState->iSuccessor )
      goto RESTART_MODEL;
    MaxContext = FoundState->getSuccessor();
    return;
  }
  *pText++ = FSymbol;
  iSuccessor = Ptr2Indx(pText);
  if( pText>=UnitsStart )
    goto RESTART_MODEL;
  if( iFSuccessor ) {
    if( (_BYTE*)Indx2Ptr(iFSuccessor)<UnitsStart )
      iFSuccessor = CreateSuccessors(0, p, MinContext, FoundState);
  } else
    iFSuccessor = ReduceOrder(p, MinContext, FoundState);
  if( !iFSuccessor )
    goto RESTART_MODEL;
  Prefetch((pc1 = (PPM_CONTEXT*)Indx2Ptr(iFSuccessor))->getSuffix());
  if( !--OrderFall ) {
    iSuccessor = iFSuccessor;
    pText -= (MaxContext!=MinContext);
  }
  Prefetch(pc1->getStates());
  for( i = OrderFall0; pc!=MinContext; pc = pc->getSuffix(), i++ ) {
    if( (ns = pc->NStates)!=0 ) {
      p = pc->getStates();
      if( (ns&1)!=0 ) {
        p = (STATE*)ExpandUnits(p, (ns+1)>>1);
        if( !p )
          goto RESTART_MODEL;
        pc->iStates = Ptr2Indx(p);
      }
      StateCpy(p[ns+1], p[1]);
      MoveStateUp(p);
      sf = MAX(int(pc->SummFreq), 22)+EscList[i];
    } else {
      p = (STATE*)AllocUnits(1);
      if( !p )
        goto RESTART_MODEL;
      StateCpy(p[1], pc->oneState());
      pc->iStates = Ptr2Indx(p);
      pc->SummFreq = p[1].Freq = (p[1].Freq<3) ? (3*p[1].Freq+2) : MIN(4*p[1].Freq, 51);
      sf = 26;
    }
    cf = FFreq*sf;
    sf += MinContext->SummFreq-FFreq;
    cf = (cf<=6*sf) ? (1+(cf+(sf>>1))/sf) : (3+(3*cf)/(4*sf));
    pc->SummFreq += (p->Freq = cf);
    p->iSuccessor = iSuccessor;
    p->Symbol = FSymbol;
    pc->Flags |= SymType[FSymbol]|0x02;
    pc->NStates++;
  }
  MaxContext = pc1;
  return;
RESTART_MODEL:
  RestoreModelRare(pc);
}

STATE*PPM_CONTEXT::encode0(int symbol) {
  STATE &s = oneState();
  WORD &sse = SSE0[SSE0QTable[s.Freq]][(s.Symbol==RecentSymbol[RSContext])+2*(getSuffix()->NStates!=0)+Flags+RLQTable[RunLength]];
  UINT tmp = rcBinStart(sse, TOT_BITS);
  if( s.Symbol!=symbol ) {
    Prefetch(getSuffix()->getSuffix());
    rcBinCorrect1(tmp, BIN_SCALE-sse);
    Prefetch(getSuffix()->getStates());
    sse -= ((sse+ROUND0)>>PERIOD_BITS);
    SymMask[s.Symbol] = SymCount;
    NMasked = 0;
    return NULL;
  } else {
    rcBinCorrect0(tmp);
    sse += INTERVAL-((sse+ROUND0)>>PERIOD_BITS);
    RunLength += (RunLength<11);
    s.Freq = NextBinFreq[s.Freq];
    return &s;
  }
}

STATE*PPM_CONTEXT::decode0() {
  STATE &s = oneState();
  WORD &sse = SSE0[SSE0QTable[s.Freq]][(s.Symbol==RecentSymbol[RSContext])+2*(getSuffix()->NStates!=0)+Flags+RLQTable[RunLength]];
  UINT tmp = rcBinStart(sse, TOT_BITS);
  if( rcBinDecode(tmp) ) {
    Prefetch(getSuffix()->getSuffix());
    rcBinCorrect1(tmp, BIN_SCALE-sse);
    Prefetch(getSuffix()->getStates());
    sse -= ((sse+ROUND0)>>PERIOD_BITS);
    SymMask[s.Symbol] = SymCount;
    NMasked = 0;
    return NULL;
  } else {
    rcBinCorrect0(tmp);
    sse += INTERVAL-((sse+ROUND0)>>PERIOD_BITS);
    RunLength += (RunLength<11);
    s.Freq = NextBinFreq[s.Freq];
    return &s;
  }
}

STATE*PPM_CONTEXT::encodeLES1(int symbol) {
  STATE* p = getStates();
  UINT Prob = (64U*p->Freq-31U)/(SummFreq+NStates+10U);
  WORD &sse = SSE1[SSE1QTable[Prob]][(p->Symbol==RecentSymbol[RSContext])+SymType[p->Symbol]+(Flags&0x0A)];
  UINT tmp = rcBinStart(sse, TOT_BITS);
  if( p->Symbol!=symbol ) {
    Prefetch(((_DWORD*)p)+NStates);
    rcBinCorrect1(tmp, BIN_SCALE-sse);
    sse -= ((sse+ROUND1)>>PERIOD_BITS);
    return NULL;
  } else {
    Prefetch(p->getSuccessor());
    rcBinCorrect0(tmp);
    sse += INTERVAL-((sse+ROUND1)>>PERIOD_BITS);
    Flags &= ~0x02;
    p->Freq += 4;
    SummFreq += 4;
    if( p->Freq>MAX_FREQ )
      p = rescale(p);
    RunLength = RLSM[0][RunLength];
    return p;
  }
}

STATE*PPM_CONTEXT::decodeLES1() {
  STATE* p = getStates();
  UINT Prob = (64U*p->Freq-31U)/(SummFreq+NStates+10U);
  WORD &sse = SSE1[SSE1QTable[Prob]][(p->Symbol==RecentSymbol[RSContext])+SymType[p->Symbol]+(Flags&0x0A)];
  UINT tmp = rcBinStart(sse, TOT_BITS);
  if( rcBinDecode(tmp) ) {
    Prefetch(((_DWORD*)p)+NStates);
    rcBinCorrect1(tmp, BIN_SCALE-sse);
    sse -= ((sse+ROUND1)>>PERIOD_BITS);
    return NULL;
  } else {
    Prefetch(p->getSuccessor());
    rcBinCorrect0(tmp);
    sse += INTERVAL-((sse+ROUND1)>>PERIOD_BITS);
    Flags &= ~0x02;
    p->Freq += 4;
    SummFreq += 4;
    if( p->Freq>MAX_FREQ )
      p = rescale(p);
    RunLength = RLSM[0][RunLength];
    return p;
  }
}

SEE_CONTEXT*PPM_CONTEXT::makeEsc1Freq() const {
  SEE_CONTEXT* psee;
  Range.scale = SummFreq-getStates()->Freq;
  if( NStates!=0xFF ) {
    Prefetch(getSuffix()->getStates());
    psee = SEE1[SEEQTable[NStates]]+(SummFreq>8*(NStates+1))+2*(2*NStates<getSuffix()->NStates)+(Flags&0x1C)+32*(getStates()[1].Symbol==RecentSymbol[RSContext]);
    Prefetch(getSuffix()->getSuffix());
    Range.scale += psee->getMean();
  } else {
    psee = &DummySEE;
    Range.scale++;
  }
  return psee;
}

STATE*PPM_CONTEXT::update1(STATE* p) {
  Prefetch(p->getSuccessor());
  SummFreq += 4;
  if( (p->Freq += 4)<=MAX_FREQ ) {
    STATE tmp, * p0 = getStates();
    StateCpy(tmp, p[0]);
    StateCpy(p[0], p0[1]);
    MoveStateUp(p0);
    StateCpy(*(p = p0), tmp);
    Flags &= ~0x02;
  } else
    p = rescale(p);
  RunLength = RLSM[1][RunLength];
  return p;
}

STATE*PPM_CONTEXT::encode1(int symbol) {
  SEE_CONTEXT* psee = makeEsc1Freq();
  STATE* p = getStates();
  UINT i = NStates, LoCnt = 0;
  while( p[1].Symbol!=symbol ) {
    SymMask[p[1].Symbol] = SymCount;
    LoCnt += p[1].Freq;
    p++;
    if( --i==0 ) {
      Range.low = LoCnt;
      NMasked = NStates;
      SymMask[getStates()->Symbol] = SymCount;
      psee->Summ += (Range.high = Range.scale);
      return NULL;
    }
  }
  Range.high = (Range.low = LoCnt)+p[1].Freq;
  return update1(++p);
}

STATE*PPM_CONTEXT::decode1() {
  SEE_CONTEXT* psee = makeEsc1Freq();
  STATE* p = getStates();
  UINT count = rcGetCurrentCount(), i = NStates, HiCnt = 0;
  do {
    HiCnt += p[1].Freq;
    p++;
    if( HiCnt>count ) {
      Range.low = (Range.high = HiCnt)-p->Freq;
      return update1(p);
    }
    SymMask[p->Symbol] = SymCount;
  } while( --i );
  Range.low = HiCnt;
  NMasked = NStates;
  SymMask[getStates()->Symbol] = SymCount;
  psee->Summ += (Range.high = Range.scale);
  return NULL;
}

SEE_CONTEXT*PPM_CONTEXT::makeEsc2Freq() const {
  SEE_CONTEXT* psee;
  prefetchStates();
  if( NStates!=0xFF ) {
    Prefetch(getSuffix()->getStates());
    psee = SEE2[SEEQTable[NStates]]+(SummFreq>8*(NStates+1))+2*(2*NStates<getSuffix()->NStates+UINT(NMasked))+(Flags&0x1C);
    Prefetch(getSuffix()->getSuffix());
    Range.scale = psee->getMean();
  } else {
    psee = &DummySEE;
    Range.scale = 1;
  }
  return psee;
}

STATE*PPM_CONTEXT::update2(STATE* p) {
  p->Freq += 4;
  SummFreq += 4;
  if( p->Freq>MAX_FREQ )
    p = rescale(p);
  RunLength = 0;
  return p;
}

STATE*PPM_CONTEXT::encode2(int symbol) {
  SEE_CONTEXT* psee = makeEsc2Freq();
  UINT Sym, LoCnt = 0, i = NStates-NMasked;
  STATE* p1, * p = getStates()-1;
  do {
    do {
      Sym = p[1].Symbol;
      p++;
    } while( SymMask[Sym]==SymCount );
    SymMask[Sym] = SymCount;
    if( Sym==symbol )
      goto SYMBOL_FOUND;
    LoCnt += p->Freq;
  } while( --i );
  Range.high = (Range.scale += (Range.low = LoCnt));
  psee->Summ += Range.scale;
  NMasked = NStates;
  return NULL;
SYMBOL_FOUND:
  Prefetch(p->getSuccessor());
  Range.low = LoCnt;
  Range.high = (LoCnt += p->Freq);
  for( p1 = p; --i; ) {
    do {
      Sym = p1[1].Symbol;
      p1++;
    } while( SymMask[Sym]==SymCount );
    LoCnt += p1->Freq;
  }
  Range.scale += LoCnt;
  return update2(p);
}

STATE*PPM_CONTEXT::decode2() {
  SEE_CONTEXT* psee = makeEsc2Freq();
  UINT Sym, count, HiCnt = 0, i = NStates-NMasked;
  STATE* ps[256], ** pps = ps, * p = getStates()-1;
  do {
    do {
      Sym = p[1].Symbol;
      p++;
    } while( SymMask[Sym]==SymCount );
    HiCnt += p->Freq;
    *pps++ = p;
  } while( --i );
  Range.scale += HiCnt;
  count = rcGetCurrentCount();
  p = *(pps = ps);
  if( count<HiCnt ) {
    HiCnt = 0;
    while( (HiCnt += p->Freq)<=count )
      p = *++pps;
    Prefetch(p->getSuccessor());
    Range.low = (Range.high = HiCnt)-p->Freq;
    return update2(p);
  } else {
    Range.low = HiCnt;
    Range.high = Range.scale;
    i = NStates-NMasked;
    do {
      SymMask[(*pps)->Symbol] = SymCount;
      pps++;
    } while( --i );
    psee->Summ += Range.scale;
    NMasked = NStates;
    return NULL;
  }
}

void PrepareNextStep(PPM_CONTEXT* MinContext, STATE* FoundState) {
  BYTE c = FoundState->Symbol;
  if( OrderFall||!FoundState->hasSuccessor() )
    UpdateModel(MinContext, FoundState);
  else
    MaxContext = FoundState->getSuccessor();
  Prefetch(MaxContext->getSuffix());
  OrderFall0 = OrderFall;
  RSContext = ((RSContext<<H_SHIFT)+(RecentSymbol[RSContext] = c))&H_MASK;
  Prefetch(MaxContext->getStates());
}

void RealEncode(FILE* EncodedFile, FILE* DecodedFile) {
  STATE* FoundState;
  do {
    PPM_CONTEXT* MinContext = MaxContext;
    int c = getc(DecodedFile);
    if( MinContext->NStates ) {
      FoundState = MinContext->encodeLES1(c);
      if( FoundState )
        goto SYMBOL_FOUND;
      {
        while( (low^(low+range))<TOP||(range<BOT&&((range = -low&(BOT-1)), 1)) ) {
          putc(low>>24, EncodedFile);
          range <<= 8;
          low <<= 8;
        }
      };
      FoundState = MinContext->encode1(c);
      rcEncodeSymbol();
    } else
      FoundState = MinContext->encode0(c);
    while( !FoundState ) {
      {
        while( (low^(low+range))<TOP||(range<BOT&&((range = -low&(BOT-1)), 1)) ) {
          putc(low>>24, EncodedFile);
          range <<= 8;
          low <<= 8;
        }
      };
      do {
        if( !MinContext->iSuffix )
          return;
        MinContext = MinContext->getSuffix();
        EscList[OrderFall++] = Range.high-Range.low;
      } while( MinContext->NStates==NMasked );
      FoundState = MinContext->encode2(c);
      rcEncodeSymbol();
    }
SYMBOL_FOUND:
    PrepareNextStep(MinContext, FoundState);
    {
      while( (low^(low+range))<TOP||(range<BOT&&((range = -low&(BOT-1)), 1)) ) {
        putc(low>>24, EncodedFile);
        range <<= 8;
        low <<= 8;
      }
    };
  } while( --SymCount );
}

void RealDecode(FILE* DecodedFile, FILE* EncodedFile) {
  STATE* FoundState;
  do {
    PPM_CONTEXT* MinContext = MaxContext;
    if( MinContext->NStates ) {
      FoundState = MinContext->decodeLES1();
      if( FoundState )
        goto SYMBOL_FOUND;
      {
        while( (low^(low+range))<TOP||(range<BOT&&((range = -low&(BOT-1)), 1)) ) {
          code = (code<<8)|getc(EncodedFile);
          range <<= 8;
          low <<= 8;
        }
      };
      FoundState = MinContext->decode1();
      rcRemoveSubrange();
    } else
      FoundState = MinContext->decode0();
    while( !FoundState ) {
      {
        while( (low^(low+range))<TOP||(range<BOT&&((range = -low&(BOT-1)), 1)) ) {
          code = (code<<8)|getc(EncodedFile);
          range <<= 8;
          low <<= 8;
        }
      };
      do {
        if( !MinContext->iSuffix )
          return;
        MinContext = MinContext->getSuffix();
        EscList[OrderFall++] = Range.high-Range.low;
      } while( MinContext->NStates==NMasked );
      FoundState = MinContext->decode2();
      rcRemoveSubrange();
    }
SYMBOL_FOUND:
    putc(FoundState->Symbol, DecodedFile);
    PrepareNextStep(MinContext, FoundState);
    {
      while( (low^(low+range))<TOP||(range<BOT&&((range = -low&(BOT-1)), 1)) ) {
        code = (code<<8)|getc(EncodedFile);
        range <<= 8;
        low <<= 8;
      }
    };
  } while( --SymCount );
}

BOOL PPMIIEncode(FILE* EncodedFile, FILE* DecodedFile, _PPMII_PRINT_INFO PrintInfo, BOOL SolidMode) {
  if( !SubAllocatorSize )
    return 0;
  if( !Interrupted ) {
    StartModelRare(SolidMode);
    rcInitEncoder();
  } else {
    Interrupted = 0;
    SymCount = 1;
  }
  do {
    RealEncode(EncodedFile, DecodedFile);
    if( SymCount ) {
      rcFlushEncoder(EncodedFile);
      if( PrintInfo )
        PrintInfo(DecodedFile, EncodedFile, 1);
      return 1;
    }
    SymCount = (PrintInfo) ? PrintInfo(DecodedFile, EncodedFile, 0) : (UINT(-1));
    memset(SymMask, 0, sizeof(SymMask));
  } while( SymCount );
  Interrupted = 1;
  return 0;
}

BOOL PPMIIDecode(FILE* DecodedFile, FILE* EncodedFile, _PPMII_PRINT_INFO PrintInfo, BOOL SolidMode) {
  if( !SubAllocatorSize )
    return 0;
  if( !Interrupted ) {
    StartModelRare(SolidMode);
    rcInitDecoder(EncodedFile);
  } else {
    Interrupted = 0;
    SymCount = 1;
  }
  do {
    RealDecode(DecodedFile, EncodedFile);
    if( SymCount ) {
      if( PrintInfo )
        PrintInfo(DecodedFile, EncodedFile, 1);
      return 1;
    }
    SymCount = (PrintInfo) ? PrintInfo(DecodedFile, EncodedFile, 0) : (UINT(-1));
    memset(SymMask, 0, sizeof(SymMask));
  } while( SymCount );
  Interrupted = 1;
  return 0;
}

const char* pFName;
DWORD StartFilePosition;
BOOL EncodeFlag;
clock_t StartClock, CurrentClock = 0;
#pragma pack(1)
struct ARC_INFO {
  DWORD signature, attrib;
  struct {
    DWORD Variant : 5;
    DWORD ModelSize : 12;
    DWORD ModelOrder : 4;
    DWORD CutOff : 1;
    DWORD SolidMode : 1;
    DWORD FNLen : 9;
  };
  WORD time, date;
} ai;
#pragma pack()
void EnvSetNormAttr(const char* FName) {
  chmod(FName, S_IWUSR|S_IRUSR);
}

int EnvGetCh() {
  return getchar();
}

void EnvGetCWD(char* CurDir) {
  getcwd(CurDir, 260);
}

void EnvSetDateTimeAttr(const char* WrkStr) {
  struct utimbuf t;
  t.actime = t.modtime = (ai.date<<16)+ai.time;
  utime(WrkStr, &t);
  chmod(WrkStr, ai.attrib);
}

struct ENV_FIND_RESULT {
  dirent de;
  struct stat st;
  const char*getFName() const {
    return de.d_name;
  }

  void copyDateTimeAttr() const {
    ai.attrib = st.st_mode;
    ai.time = st.st_mtime&0xFFFF;
    ai.date = st.st_mtime>>16;
  }
};
struct ENV_FILE_FINDER {
  const char* pPattern;
  DIR* dir;
  dirent* de;
  struct stat st;
  ENV_FIND_RESULT getResult() {
    ENV_FIND_RESULT Rslt;
    Rslt.de = *de;
    Rslt.st = st;
    return Rslt;
  }

  BOOL isFileValid() {
    return (fnmatch(pPattern, de->d_name, FNM_NOESCAPE)==0&&stat(de->d_name, &st)==0&&(st.st_mode&S_IRUSR)!=0&&st.st_nlink==1);
  }

  BOOL findFirst(const char* Pattern) {
    pPattern = Pattern;
    return ((dir = opendir("."))&&(de = readdir(dir))!=NULL);
  }

  BOOL findNext() {
    return ((de = readdir(dir))!=NULL);
  }

  void findStop() {
    closedir(dir);
  }
};
const char*const MTxt[] = {"Can`t open file %s\n",
                           "read/write error for files %s/%s\n",
                           "Out of memory!\n",
                           "User break\n",
                           "unknown command: %s\n",
                           "unknown switch: %s\n",
                           "designed and written by Dmitry Shkarin <dmitry.shkarin@mtu-net.ru>\n"
                           "Usage: PPMd <e|d> [switches] <FileName[s] | Wildcard[s]>\n"
                           "Switches (' - for encoding only):\n"
                           "\t-d      - delete file[s] after processing, default: disabled\n"
                           "\t-fName' - set output archive name to Name\n"
                           "\t-mN'    - use N MB memory - [1,4095], default: %d\n"
                           "\t-oN'    - set model order to N - [2,%d], default: %d\n"
                           "\t-rN'    - set method of model reduction at memory insufficiency:\n"
                           "\t\t-r0 - restart model from scratch (default)\n"
                           "\t\t-r1 - cut off model (slow)\n"};
UINT PrintInfo(FILE* DecodedFile, FILE* EncodedFile, BOOL LastCall) {
  clock_t t = clock();
  if( t<CurrentClock+int(CLOCKS_PER_SEC/5)&&!LastCall )
    return 512*1024;
  char WrkStr[512];
  UINT NDec = ftell(DecodedFile);
  NDec += (NDec==0);
  UINT NEnc = ftell(EncodedFile)-StartFilePosition;
  UINT n1 = (8LL*NEnc)/NDec;
  UINT n2 = (1000LL*(8LL*NEnc-NDec*n1)+NDec/2U)/NDec;
  if( n2==1000 ) {
    n1++;
    n2 = 0;
  }
  int RunTime = (((CurrentClock = t)-StartClock)<<10)/int(CLOCKS_PER_SEC);
  UINT Speed = NDec/(RunTime+(RunTime==0));
  UINT UsedMemory = PPMIIGetCurrentModelSize()>>10;
  UINT m1 = UsedMemory>>10;
  UINT m2 = (10*(UsedMemory-(m1<<10))+(1<<9))>>10;
  if( m2==10 ) {
    m1++;
    m2 = 0;
  }
  if( !EncodeFlag )
    SWAP(NDec, NEnc);
  sprintf(WrkStr, "%15s:%7d >%7d, %1d.%03d bpb, used:%3d.%1d MB, speed: %d KB/sec.", pFName, NDec, NEnc, n1, n2, m1, m2, Speed);
  printf("%-79.79s%c", WrkStr, (LastCall) ? ('\n') : ('\r'));
  fflush(stdout);
  return 512*1024;
}

char*ChangeExtRare(const char* In, char* Out, const char* Ext) {
  char* RetVal = Out;
  const char* p = strrchr(In, '.');
  if( !p||!stricmp(p+1, Ext) )
    p = In+strlen(In);
  do {
    *Out++ = *In++;
  } while( In!=p );
  *Out++ = '.';
  while( (*Out++ = *Ext++)!=0 )
    ;
  return RetVal;
}

BOOL RemoveFile(const char* FName) {
  EnvSetNormAttr(FName);
  return (remove(FName)==0);
}

BOOL TestAccessRare(const char* FName) {
  static BOOL YesToAll = 0;
  FILE* fp = fopen(FName, "rb");
  if( !fp )
    return 1;
  fclose(fp);
  if( YesToAll )
    return RemoveFile(FName);
  printf("%s already exists, overwrite?: <Y>es, <N>o, <A>ll, <Q>uit?", FName);
  for(;; )
    switch( toupper(EnvGetCh()) ) {
    case 'A':
      YesToAll = 1;
    case '\r':
    case 'Y':
      return RemoveFile(FName);
    case 0x1B:
    case 'Q':
      printf(MTxt[3]);
      exit(4);
    case 'N':
      return 0;
    }
}

FILE*FOpen(const char* FName, const char* mode) {
  FILE* fp = fopen(FName, mode);
  if( !fp ) {
    printf(MTxt[0], FName);
    exit(1);
  }
  setvbuf(fp, NULL, _IOFBF, 128*1024);
  return fp;
}

void EncodeFile(const ENV_FIND_RESULT &efr, int ModelSize, int ModelOrder, BOOL CutOff, const char* ArcName, BOOL FirstFile) {
  UINT UsedMemory;
  char WrkStr[260];
  strcpy(WrkStr, ArcName);
  pFName = efr.getFName();
  if( !WrkStr[0]&&!TestAccessRare(ChangeExtRare(pFName, WrkStr, "pmd")) )
    return;
  FILE* fpIn = FOpen(pFName, "rb"), * fpOut = FOpen(WrkStr, "a+b");
  fpOut = freopen(WrkStr, "r+b", fpOut);
  fseek(fpOut, 0, SEEK_END);
  efr.copyDateTimeAttr();
  ai.signature = PPMdSignature;
  ai.Variant = PROG_VAR-'A';
  ai.ModelOrder = ModelOrder-2;
  ai.ModelSize = ModelSize-1;
  ai.CutOff = CutOff;
  ai.SolidMode = (ArcName[0]!=0&&!FirstFile);
  ai.FNLen = strlen(pFName);
  fwrite(&ai, sizeof(ai), 1, fpOut);
  fwrite(pFName, ai.FNLen, 1, fpOut);
  if( !ai.SolidMode ) {
    if( !PPMIICreateModel(ModelSize, ModelOrder, CutOff) ) {
      printf(MTxt[2]);
      exit(3);
    }
  }
  StartFilePosition = ftell(fpOut);
  StartClock = clock();
  PPMIIEncode(fpOut, fpIn, PrintInfo, ai.SolidMode);
  if( ferror(fpOut)||ferror(fpIn) ) {
    printf(MTxt[1], efr.getFName(), WrkStr);
    exit(2);
  }
  if( !ArcName[0]&&(UsedMemory = PPMIIDeleteModel())<ModelSize ) {
    fseek(fpOut, StartFilePosition-sizeof(ai)-ai.FNLen, SEEK_SET);
    ai.ModelSize = UsedMemory-1;
    fwrite(&ai, sizeof(ai), 1, fpOut);
  }
  fclose(fpIn);
  fclose(fpOut);
}

BOOL DecodeOneFile(FILE* fpIn) {
  int ModelSize, ModelOrder;
  char WrkStr[260];
  if( !fread(&ai, sizeof(ai), 1, fpIn) )
    return 0;
  if( ai.signature!=PPMdSignature||ai.Variant+'A'!=PROG_VAR ) {
    printf(MTxt[0], WrkStr);
    exit(1);
  }
  ModelSize = ai.ModelSize+1;
  ModelOrder = ai.ModelOrder+2;
  fread(WrkStr, ai.FNLen, 1, fpIn);
  WrkStr[ai.FNLen] = 0;
  if( !TestAccessRare(WrkStr) )
    return 0;
  FILE* fpOut = FOpen(pFName = WrkStr, "wb");
  if( !ai.SolidMode ) {
    PPMIIDeleteModel();
    if( !PPMIICreateModel(ModelSize, ModelOrder, ai.CutOff) ) {
      printf(MTxt[2]);
      exit(3);
    }
  }
  StartFilePosition = ftell(fpIn);
  StartClock = clock();
  PPMIIDecode(fpOut, fpIn, PrintInfo, ai.SolidMode);
  if( ferror(fpOut)||ferror(fpIn)||feof(fpIn) ) {
    printf(MTxt[1], WrkStr, WrkStr);
    exit(2);
  }
  fclose(fpOut);
  EnvSetDateTimeAttr(WrkStr);
  return 1;
}

void DecodeFile(const ENV_FIND_RESULT &efr) {
  FILE* fpIn = FOpen(efr.getFName(), "rb");
  while( DecodeOneFile(fpIn) )
    ;
  fclose(fpIn);
}

void TestArchive(char* ArcName, const char* Pattern) {
  if( !Pattern[0] ) {
    char CurDir[260];
    EnvGetCWD(CurDir);
    const char* p = strrchr(CurDir, '/');
    p = (p&&strlen(p+1)) ? (p+1) : ("PPMdFile");
    ChangeExtRare(p, ArcName, "pmd");
  } else
    strcpy(ArcName, Pattern);
  FILE* fp = fopen(ArcName, "rb");
  if( fp ) {
    if( !fread(&ai, sizeof(ai), 1, fp)||ai.signature!=PPMdSignature||ai.Variant+'A'!=PROG_VAR ) {
      printf(MTxt[0], ArcName);
      exit(1);
    }
    fclose(fp);
  }
}

struct FILE_LIST_NODE {
  FILE_LIST_NODE* next;
  ENV_FIND_RESULT efr;
  FILE_LIST_NODE(const ENV_FIND_RESULT &Data, FILE_LIST_NODE** PrevNode) {
    efr = Data;
    next = *PrevNode;
    *PrevNode = this;
  }

  void destroy(FILE_LIST_NODE** PrevNode) {
    *PrevNode = next;
    delete this;
  }
};
int main(int argc, char* argv[]) {
  // assert(TestCompilation());
  char ArcName[260];
  BOOL DeleteFile = 0, CutOff = 0;
  int i, ModelSize = 256, ModelOrder = 5;
  printf("Fast PPMII compressor for textual data, modified variant %c, "
         "May 20 2026"
         "\n",
         PROG_VAR);
  if( argc<3 ) {
    printf(MTxt[6], ModelSize, MAX_O, ModelOrder);
    return -1;
  }
  switch( toupper(argv[1][0]) ) {
  case 'E':
    EncodeFlag = 1;
    break;
  case 'D':
    EncodeFlag = 0;
    break;
  default:
    printf(MTxt[4], argv[1]);
    return -1;
  }
  for( ArcName[0] = 0, i = 2; i<argc&&(argv[i][0]=='-'||argv[i][0]=='/'); i++ )
    switch( toupper(argv[i][1]) ) {
    case 'D':
      DeleteFile = 1;
      break;
    case 'F':
      TestArchive(ArcName, argv[i]+2);
      break;
    case 'M':
      ModelSize = CLAMP(atoi(argv[i]+2), 1, 4095);
      break;
    case 'O':
      ModelOrder = CLAMP(atoi(argv[i]+2), 2, int(MAX_O));
      break;
    case 'R':
      CutOff = CLAMP(atoi(argv[i]+2), 0, 1);
      break;
    default:
      printf(MTxt[5], argv[i]);
      return -1;
    }
  FILE_LIST_NODE* pNode, * pFirstNode = NULL, ** ppNode = &pFirstNode;
  for( ENV_FILE_FINDER eff; i<argc; i++ ) {
    if( eff.findFirst(argv[i]) )
      do {
        if( eff.isFileValid() ) {
          pNode = new FILE_LIST_NODE(eff.getResult(), ppNode);
          if( !pNode ) {
            printf(MTxt[2]);
            return -1;
          }
          ppNode = &(pNode->next);
        }
      } while( eff.findNext() );
    eff.findStop();
  }
  for( BOOL FirstFile = 1; (pNode = pFirstNode)!=NULL; FirstFile = 0 ) {
    ENV_FIND_RESULT &efr = pNode->efr;
    if( EncodeFlag )
      EncodeFile(efr, ModelSize, ModelOrder, CutOff, ArcName, FirstFile);
    else
      DecodeFile(efr);
    if( DeleteFile )
      remove(efr.getFName());
    pNode->destroy(&pFirstNode);
  }
  return 0;
}
