# `dummy.cpp` refactoring goals

`dummy.cpp` is the PPMII codec lifted out of a PE binary by decompilation
and folded into a single self-contained C++ source: heap suballocator,
context-tree model, SSE/APM cascade, logistic mixer, range coder, CLI
driver. `ppmd.cpp` in the same directory is Shkarin's readable reference
implementation of the same algorithm; use it as the behaviour and naming
oracle.

`RealProcess<f_DEC>` is still the largest single function (~1000 lines,
templated for encode/decode) and gets the bulk of the structural work,
but the same decompiler-output problems appear throughout the file:
`ReduceOrder`, the `Sse*` helpers, `PPMContextWalk`, `CreateSuccessors`,
and `UpdateModel` all carry varying amounts of `v0`/`v1`/… locals,
unstructured control flow, and references to the file-scope `d##`/`q##`
globals. Treat the whole file as the refactoring target.

## The goal

Make `dummy.cpp` **readable, idiomatic and structured** without changing
the algorithm. The compressed output must remain bit-exact; round-trip
on `book1` (via `make && sh t.sh`) must keep passing after every commit.

## What's still wrong

Even after several cleanup passes the file still reads like decompiler
output in many places. The following concrete examples — drawn mostly
from `RealProcess` because it's where the work is currently focused —
illustrate the categories of problem that remain throughout `dummy.cpp`.

### A. The codec still depends on a sea of file-scope globals

The decompiler treated register spills and intermediate scratch as
file-scope globals. Many turned out to be **per-symbol scratch**, but
they still live as anonymous numeric globals:

```cpp
// near the top of dummy.cpp
sqword q9, q12, q14, q17, q18, q19, q20, q21, q22, q23,
       q24, q25, q26, q29, q30, q31, q32, q33, q34, q35,
       q36, q37, q38, q39;     // 24 "register" slots
int d45, d46, d47, d48, /* ... */, d113;     // ~46 d-globals referenced by RealProcess
```

Inside `RealProcess`, the q-slots get assigned in pairs alongside the
real algorithm state, and the only way to follow the data flow is to
grep for who reads each q:

```cpp
// in the multi-state SSE-mix block
bigSlotA = &d29[512*sseQTableIdxA + 16*(maskFlagEsc|maskFlagPrev) + 2*((byte)mixIdxA & 0xF3)];
q29 = (sqword)bigSlotA;
q33 = (sqword)(mixSlotA + 2048);
q32 = (sqword)(mixSlotA - 2048);
```

A reader can't tell which writes are "real outputs of this function"
versus dead spills until they grep every other function for matching
reads.

Goal: **classify each global** as either real persistent state (give
it a semantic name; eventually move into a `Predictor`-like struct in a
follow-up pass) or per-iteration scratch (make local, or drop entirely
once proven dead).

**Preferred technique now that the codebase is single-file:** rename the
global *at its definition site* and update every reader in one commit.
The cross-file ABI rationale that previously forced typed `int&` aliases
is gone — `d51 → sseCum` can be a flat rename.

A small carve-out remains: some d-globals are `int&` aliases into
`d90[]` (e.g. `int& d108 = d90[108];` -style declarations are not
present today, but the same codegen sensitivity exists for any
reference into a large array). For those, leave the storage as an
array element and rename only the reference identifier; turning a
file-scope reference into a function-local one can perturb `-Ofast`
register-allocation enough to change the encoded stream.

Examples already done as in-function aliases (these can now be
converted to direct renames of the underlying global, one at a time,
each verified by `sh t.sh`):

```cpp
int&   sseCum = d51;       // running cumulative freq in the SSE cascade
int&   sseTot = d97;       // running total freq      in the SSE cascade
int&   predRescaleDiv = d95;  // total weight / (NStates+1) in the rewind path
int&   cumFreqAcc     = d96;  // running cum-freq accumulator
int*&  sse1Slot     = (int*&)q23;
int*&  sseMatchSlot = (int*&)q19;
int*&  sse2Slot     = (int*&)q24;
int*&  sse3Slot     = (int*&)q25;
word*& binMixCenter = (word*&)q21;
uint*& binSseCell   = (uint*&)q36;
uint*& predWeightA  = (uint*&)q39;
uint*& predWeightB  = (uint*&)q37;
byte*& sse2Base     = (byte*&)q12;
```

Examples already at file scope (likewise candidates for direct rename):

```cpp
int&   matchPosAge   = d108;  // epoch delta to most-recent matching position
int&   matchEpoch2   = d107;  // second epoch delta in the per-candidate match block
int&   matchHashSy   = d109;  // MatchPosHash byte snapshot
int&   recentSym     = d64;   // just-encoded symbol byte
int&   sseState3Hash = d63;   // 17-bit rolling sym-context hash, indexes SseState3
sqword& CtxChainEnd  = q14;
int&    EscIndexSeed = d45;
```

…plus `STATE*& FoundState = (STATE*&)q9;` used both in `ReduceOrder`
and inlined into `RealProcess`.

Same memory, same layout, just self-documenting. The remaining q/d
globals are candidates for the same treatment as their semantics become
clear — and most can now be renamed at the definition rather than via
an alias layer.

### B. The locals are still numerous and section-suffixed

`RealProcess`'s declaration block holds about 145 locals organised by
C type rather than by role:

```cpp
// top of RealProcess
int inputByte, epoch, nStates, remStates, walkSym, sortPriority;
int nStatesCnt, nStatesP1Save, sxNStates, minSumFreqA, sxSumFreqA0, sumFreqM;
int mixConstM, sumFreqWM, mixWeightM;
int escInitialSym, savedOrderFall, savedNMasked, mixWeightInitA;
int mixFreqA3;
/* ... ~60 more lines just like this, grouped by type ... */
```

Two things wrong here:

1. **Every local has function scope** even though most are used in a
   single ~20-line block. They have function scope because the goto
   structure forces declarations to the top (a mid-function declaration
   would be skipped by a goto into a later block).

2. **Names still carry suffix tags** (`_A`, `_M`, `_F`, etc.) so the
   reader can tell which section of the function the variable belongs
   to. That's a workaround for the goto structure: when every block
   shares the same scope, you need section tags to disambiguate. With
   structured code, `sumFreq` in two functions is fine.

`ReduceOrder` (line 2247) is the other end of the spectrum: ~70 locals
named `v0, v1, v2, …, v68` straight from the decompiler. None of those
names survive past a reading pass; they need to be classified and
renamed the same way `StartModelRare` already has been (compare lines
1679+ — that function reads cleanly).

Goal: **let the goto-eliminated structure shrink the scopes**, then
drop the suffix tags. Names like `mixWeightM`, `cumFreqMixA`,
`sumFreqW0C` are tolerable in the current code but should be plain
`mixWeight`, `cumFreq`, `sumFreqW` once they live in separate
functions. `v0…v68` are never tolerable.

### C. The labels make the textbook structure invisible

The original ppmd.cpp `RealEncode` reads as:

```cpp
do {
    PPM_CONTEXT* MinContext = MaxContext;
    int c = getc(DecodedFile);
    if (MinContext->NStates) {
        FoundState = MinContext->encodeLES1(c);   // multi-state binary
        if (FoundState) goto SYMBOL_FOUND;
        FoundState = MinContext->encode1(c);      // full state search
    } else
        FoundState = MinContext->encode0(c);      // single-state binary
    while (!FoundState) {
        do { /* walk suffix chain */ } while (MinContext->NStates == NMasked);
        FoundState = MinContext->encode2(c);      // escape
    }
SYMBOL_FOUND:
    PrepareNextStep(MinContext, FoundState);
} while (--SymCount);
```

The PE version implements the same algorithm but spreads it across
seven jump targets:

```cpp
//  LABEL_14 / LABEL_18         ~  encode1 state-sort body
//  LABEL_58 / LABEL_59         ~  shared mixing-loop entry
//  LABEL_128                   ~  escape suffix descent
//  LABEL_292 / 296 / 298       ~  encode2 candidate-set build
//  LABEL_335                   ~  freq-bound clamp
//  LABEL_250                   ~  SYMBOL_FOUND tail
```

with `goto LABEL_x` from multiple sources entering each. A first-time
reader has no way to recognise that this is the textbook PPMd outer
loop until they map every label by hand.

Goal: **structure the body so each ppmd primitive is a named function
or a clearly-delimited block.** The labels can stay only where the
underlying control flow really is irreducible; everywhere else, prefer
a regular `if`/`else` and `while`.

### D. The Sse cascade is written out twice inside `RealProcess`

The four-stage cascade `Sse1 → SseMatch → Sse2 → Sse3` runs in two
places inside `RealProcess`: once in the single-state binary branch
(`B`-suffix locals, running once per symbol) and once in the LABEL_59
per-candidate loop (`F`-suffix locals, running once per candidate
symbol during an escape). The body shape is identical aside from which
locals it reads:

```cpp
// LABEL_59 per-candidate, around line 993
sse1SlotF      = &Sse1[2 * OrderCtxSeed];
q23            = (sqword)sse1SlotF;
sse1D51        = d51;
sse1Clamp      = SseClampMean_(sse1SlotF, hitsF, 1 - d51, 0x40000);
SseDeltaUpdate_(sse1SlotF, sse1D51, 0x40000, 4096, 2);
mixCumWeightF  = sse1Clamp + d97;
mixCumFreqF    = sse1Clamp + sse1D51;
```

```cpp
// Single-state binary branch, around line 528
sse1SlotB      = &Sse1[2 * OrderCtxSeed];
q23            = (sqword)sse1SlotB;
sse1D51B       = d51;
sse1ClampB     = SseClampMean_(sse1SlotB, mixHitsB, 1 - d51, 0x40000);
SseDeltaUpdate_(sse1SlotB, sse1D51B, 0x40000, 4096, 2);
cumWeightB     = sse1ClampB + d97;
cumFreqB       = sse1ClampB + sse1D51B;
```

The same parallel exists for the `SseMatch`, `Sse2`, and `Sse3`
stages — eight near-identical blocks total. Today they are held in
parallel only by the `_B` / `_F` suffix convention and a hope that
they don't drift. The right form is a single `sseStage(...)` function
called from both sites.

Goal: **collapse the mirrored cascade** once the surrounding locals
that feed each stage are passed by reference instead of read out of
file scope.

### E. The `sseCum = X; sseTot = Y` pattern still has redundant writes

Each stage of the SSE cascade publishes its result to the
`sseCum`/`sseTot` running pair (which the next stage reads). The
locals that get copied to those names are usually throwaway, but the
publish lines stay in the source because:

  * `sseCum` aliases `d51`, which `MixUpdate` reads on the way out;
  * the next stage reads `sseCum`/`sseTot` to start its own cell update.

```cpp
// inside the if(mixDeltaA>0x80) block, after the neighbour-cell blend
mixWeightA = ((mixWeightSavedA + *(mixSlotA-2048))       >> (mixShiftA+1)) + mixWeightA;
mixFreqA   = ((uint)(*((word*)mixSlotA+4098)
                   + *((word*)mixSlotA-4094))            >> (mixShiftA+1)) + mixFreqA;
sseCum = mixWeightA;                    // alias of d51 — read by MixUpdate
sseTot = mixFreqA;                      // alias of d97 — read by the next cascade stage
d98    = RescaleAccum1_(mixSlotA + 2048, mixWeightSavedA, mixShiftA);
```

The reader still has to track that `sseCum`/`sseTot` are an in-band
"probability accumulator" pair passed forward through the stages,
both inside this function and into `MixUpdate` afterwards.

Goal: **make the (cumFreq, totFreq) pair an explicit value** that
flows through the helpers (a small `struct ProbEstimate { uint cum;
uint tot; }` or two named locals), so the intra-cascade publishes can
fall away — at minimum the ones that have no MixUpdate consumer.
Done so far: the d51/d97 globals have been renamed to sseCum/sseTot
via function-local references (Section A). Sse1Step_/Sse2Step_/
Sse3Step_/SseMatchStep_ helpers now collapse the four cascade stages
into one body each, used by both region A (single-state binary) and
region F (per-candidate). The remaining `predSseTotDelta = sseTot;`
and similar intra-cascade publishes inside the helpers preserve the
ABI to MixUpdate; the next step is to prove which are dead and delete
them.

### F. The non-`RealProcess` functions

Status: largely cleaned up. Every function outside `RealProcess` has
had its `v##` locals renamed by role and its `a#` parameters renamed.

Several inlined-function patterns have been factored out into shared
helpers:
- `FreeUnitsRare` body (coalesce + chunk + split + insert) used to be
  inlined in 4 places (AllocUnitsRare leftover-split, AllocUnitsRare
  GlueFreeBlocks inner loop, ReduceOrder binary-context restore,
  ReduceOrder PrepareNextStep). All now call `FreeUnitsRare` directly.
- `AllocUnits_` (try freelist queue, else bump LoUnit, else
  AllocUnitsRare) factored out and used at 4 sites (AllocUnitsRare
  bottom, two PrepareNextStep sites, StartModelRare init).
- `AllocContext_` (HiUnit-bump or BList[0].unlinkPrev or
  AllocUnitsRare(0)) factored out for CreateSuccessors's per-context
  alloc loop.
- `UnitsCpy_` replaces the inline 6-uint-per-iter state-copy in
  PrepareNextStep.
- `emitOneByte` factored out as the shared body of Rangecoder's
  EncodeShift and Flush.
- `Sse1Step_`/`Sse2Step_`/`Sse3Step_`/`SseMatchStep_` collapse the
  four-stage cascade between RealProcess regions A and F.
- `SseIdx` was moved to file scope (was anonymous-namespace before
  RealProcess only) and is now used by PPMContextWalk and MixUpdate
  to build composite bitfield indices (mixCtxComposite, matchScore,
  OrderCtxSeed, SseSeed, MixCtxExtra, bmComposite, sparseFlags).
- `MEM_BLK::unlink()` method added; the FreeUnitsRare coalesce loop and
  the AllocUnitsRare GlueFreeBlocks sentinel walk now use it.
- `PopCountWeighted_`, `ClampMixWeight_`, `InitMixCell_` factor the
  two mix-model init loops in StartModelRare; an `initSseCells` lambda
  collapses four parallel SSE-cell init loops.
- Byte-offset PPM_CONTEXT / STATE access (`*(uint*)(p + 4)` etc.) is
  largely converted to typed `ctx->iStates` / `state->iSuccessor` etc.
  across ReduceOrder, CreateSuccessors, MixUpdate, StartModelRare,
  PPMContextWalk.
- Function signatures retyped: `BinEscFreq`, `RescaleCtx`, `UpdateModel`,
  `MixUpdate`, `FreeContext_`, `MoveContext_`, `AllocContext_`,
  `FindAndBubble7_` all now take/return their natural PPM_CONTEXT*/STATE*
  type instead of byte*/void*/sqword. ReduceOrder/MixUpdate locals
  `ctxBW`/`walkCtx`/`foundState`/`stateBW`/`chainStatePtr`/`onestatePtr`/
  `foundStateB`/`tailState`/`deepFound`/`trailFound`/`deepStates`/
  `trailStates` likewise retyped.
- CreateSuccessors's chain pointer threaded as `STATE**` end-to-end
  (caller passes `(STATE**)CtxChain`); the per-chain `*(sqword*)chainPtr`
  / `*chainPtr = (qword)i` access pattern is now a direct
  `(*chainPtr)->iSuccessor` / `*chainPtr = state`.
- Several Hex-Rays macro residues (`LODWORD` on sqword args, `LOWORD`
  on int reads, `((byte*)SSE0)` no-op casts, dead "prefetch hints"
  `(void)(x+heapNull)`) removed.
- Dead writes proven by data-flow inspection have been deleted:
  `succAddrSaved`/`succAddr=succAddrSaved`, two `newByteIdx =
  pTextEntry+1-heapNull` refreshes, `matchHi = (int)matchHi` self-assign,
  `ctxSuffixIdx` (only fed the removed prefetch hint), `deepStatesPtr`
  (only assigned, never read), `predGuessSym = Order1Ctx` (both equal
  the same value).
- Single-use locals folded into their callers: `oldIStates`, `stateIdxU`,
  `unitsStart`, `rsCtx`, `symEpochS`, `sseRowOff`, `scale`, `heapNullOffset`,
  `runLengthVal`, `param1/2/3`, `maxOrderArg`, `memsize_b`. Counter locals
  `j`/`halved` moved into their loop bodies; `sseHistOff`/`newHistCnt`
  scoped to the owning if-block; `binMixCenter` ditto.
- Repeated computations consolidated: `Order1Ctx = predGuessSym = ...`
  and `FoundSymbol = predGuessSym = ...` chained; `pTextEntry+1`,
  `descendNStates`/`walkNStates`, `matchDelta` reuse; `FoundSymbol=-1`
  hoisted above its two-branch initialisation.
- BinEscFreq / SseScale1 / SseScale2 / RescaleAccum1_/2_ /
  MaybeRescale1_/2_ now use typed `SseCounter*` / `SseSlot*` member
  access instead of `*((word*)slot + n)` offsets.
- AllocUnitsRare bootstrap unlink folded into `bList[0].unlinkPrev()`;
  `(uint)(uintptr_t)x - heapNull` patterns folded into `Ptr2Indx(x)`.
- FreeUnitsRare made `void` (no caller consumed its char* return).
- RescaleCtx / SseScale1 / SseScale2 / InitTables / BinEscFreq all
  made `void` (return values were discarded by every caller).
- `b39` renamed to `SymFreqs` (per-symbol frequency cache populated by
  `FillFreqMap_`).
- RealProcess's per-candidate `chainPtr` retyped from `sqword*` to
  `STATE**` so the LABEL_59 entry `FoundState = (STATE*)*chainPtr;`
  reduces to `FoundState = *chainPtr;`. ReduceOrder's `chainPtrW` /
  `chainPtrSave` likewise retyped (drops 3 inline casts plus the
  `(STATE**)(chainPtrSave-1)` cast at the CreateSuccessors call).

Remaining work in this category:
- **`RealProcess` itself** — the only function still carrying the
  decompiler-output shape (sections B, C, D, E below). Locals are
  semantically named but section-suffixed (`_A`/`_B`/`_C`/`_E`/`_F`/`_M`);
  control flow is still goto-driven.
- **d27 / d29 arrays** — large mix-model heaps. Renaming the array
  identifier is mechanical but each has 4-7 sibling `auto&` byte-offset
  aliases (MixBound2..6, b19, w11, w12) that would need to update in
  lockstep. Defer until a clear naming scheme emerges.
- **b##-named hash tables** (b25, b27, b29, b31, b32..b37) — these are
  hash-table views overlaid on `Sse2State` at specific byte offsets,
  with semantic roles (SymLastCtx routing, byte-hash arm predictors,
  paired byte-hash predictors). The bN names are short enough that
  renaming is low value until their roles are fully understood.

## Non-goals

### Eliminating the gotos completely

`LABEL_14`/`LABEL_18`, `LABEL_292`/`LABEL_296`/`LABEL_298`, and
`LABEL_58`/`LABEL_59` form irreducible cycles: multiple edges enter
shared bodies and backward edges cross block boundaries. Don't try to
rewrite these as `for`/`while`. Where the control flow is naturally a
loop (the escape descent at `LABEL_128`, the per-state walk inside
`LABEL_335`), structuring is fine.

### Fixing the annotated bugs in `PPMContextWalk`

`PPMContextWalk` carries `FIX BUG` annotations for the escape-symbol
writeback and the `d93` variance-tracker sync. The inline ancestor in
`RealProcess` may have the un-fixed form. **Preserve the original
behaviour.** Any fix is a separate intentional change with its own
before/after stream comparison.

### Re-routing region B through `PPMContextWalk`

`PPMContextWalk` is a partial extraction, not a behaviour-identical
helper. Region B inside `RealProcess` still does the binary-context
work inline. Don't replace the inline body with a call to
`PPMContextWalk` without re-validating round-trip.

### Wrapping all model state in a class

A `Predictor`/`PPMCodec` struct holding `MaxContext`, `OrderFall`, the
SSE tables etc. is the right end state but it touches every function in
the file at once. Do the per-function rename/clean-up passes first;
collect related globals into a struct only once their names and lifetimes
are clear.

### Reorganising into multiple files

`dummy.cpp` is intentionally single-file. Don't split it back out into
the `subs_*.inc` layout it came from — that structure was an artefact
of decompilation, not a design.

## Critical preservation rules

1. **Integer width and signedness.** Every `(word)`, `(byte)`,
   `(uint)`, `(sqword)` cast controls overflow, shifts, and `abs32`
   behaviour. Preserve them in the same place.
2. **Struct packing and array strides.** `#pragma pack(1)`,
   `sizeof(STATE) == 6`, every `2*idx` / `6*idx` / `12*idx` stride is
   semantics.
3. **Pointer aliasing.** The `q##` globals point into the same arrays
   as other globals; helpers take `void*` to preserve the alias set
   the compiler sees.
4. **Range-coder promotions.** 32-bit values that are promoted to
   64-bit in shift/flush paths must stay that way.
5. **Global mutation order.** `MixCtxExtra`, `OrderCtxSeed`, `SseSeed`
   and `d51`/`d97`/`d95`/`d96` are mutated interleaved with
   probability math. Do not cache and delay a write unless you have
   proven no downstream read aliases it.
6. **Division paths.** Numerator and denominator of every division
   must be identical to the original.

## Working discipline

- One semantic-neutral change per commit. `sh t.sh` green before the
  next.
- Refactoring and bug-fixing never share a commit.
- When a step turns red, revert. The last green state plus a diff is
  faster than tracing what changed.
- Name only what is verified.

## Files

- `dummy.cpp` — refactoring target. Self-contained: heap suballocator,
  context tree, SSE cascade, range coder, `RealProcess<f_DEC>`, CLI driver.
- `ppmd.cpp` — Shkarin's reference PPMII implementation. Used as the
  readability and naming oracle; do not edit.
- `t.sh` — round-trip regression test. Encodes `book1`, decodes,
  compares md5s.
- `book1`, `book1.ppm` — test inputs / expected outputs for `t.sh`.
- `Makefile` — `make` builds `dummy` from `dummy.cpp` with
  `clang++ -Ofast`.

---

## Appendix: the PPMII algorithm

This appendix is reference material for someone reading or refactoring
`dummy.cpp` who needs to recognise *what* the dense arithmetic is
computing. It documents the model at the level of "data structures and
algorithms", not at the level of every magic constant. Authoritative
source: Shkarin's PPMII papers and the textbook implementation in
`ppmd.cpp`; the PE variant in `dummy.cpp` adds the SSE cascade and the
sparse submodels described in the later sections.

### A.1 Data structures

#### `PPM_CONTEXT` — one node of the context tree

```cpp
#pragma pack(1)
struct PPM_CONTEXT {              // sizeof == 12 bytes
  byte  NStates;                  // 0:    state count - 1  (0 means a single oneState)
  byte  Flags;                    // 1:    bitfield used for SSE-context construction (§A.5)
  word  SummFreq;                 // 2-3:  sum of all state Freqs in this context
  uint  iStates;                  // 4-7:  heap index of the STATE[] array
  uint  iSuffix;                  // 8-11: heap index of the order-(n-1) suffix context
};
```

A PPM model is a tree (well, a DAG): every context of order `n` has a
single `iSuffix` link pointing to its order-`(n-1)` suffix context.
Following `iSuffix` repeatedly walks down the context tree toward the
order-`-1` uniform model. The root order-`0` context has
`iSuffix == 0`.

All "pointers" inside the model are 32-bit `uint` indices relative to a
fixed `HeapNull` base. `Indx2Ptr(idx) = (void*)(HeapNull + idx)`. This
halves the size of every node compared to a 64-bit pointer model and
lets a single live allocation backing-store contain the whole model.

#### `STATE` — one (symbol, frequency, child-context) triple

```cpp
struct STATE {                    // sizeof == 6 bytes
  byte  Symbol;                   // 0:    the predicted byte
  byte  Freq;                     // 1:    frequency, scaled up to MAX_FREQ (123)
  uint  iSuccessor;               // 2-5:  heap index of the higher-order PPM_CONTEXT
                                  //       reached by appending Symbol to this context
};
```

`STATE.iSuccessor` is the "go to order `n+1`" link, the dual of
`PPM_CONTEXT.iSuffix`. A state whose `iSuccessor` is below `UnitsStart`
points into the raw text buffer instead of into the model; that signals
"this context has been seen once, the next byte is sitting in the text
verbatim, no higher-order context node has been built yet." That's what
`STATE::hasSuccessor()` tests.

#### The "oneState" trick

A context with `NStates == 0` has a *single* state. To avoid a separate
allocation for one 6-byte record, the embedded `SummFreq` word and the
`iStates` field together overlay one `STATE`:

```cpp
STATE& oneState() const {         // an alias onto SummFreq..iStates
  return (STATE&)SummFreq;        // Symbol = SummFreq lo byte
                                  // Freq   = SummFreq hi byte
                                  // iSuccessor = iStates
}
```

So a binary context (the most common kind, since most contexts are seen
only once) takes the same 12 bytes as a multi-state context; the
difference is the `NStates == 0` flag deciding whether to read the
inline `oneState()` or follow `iStates` to a separate `STATE[]` array
of length `NStates + 1`.

The PE binary's region B (the `NStates == 0` branch in `RealProcess`)
is exactly the binary-context code path: a single Symbol, a binary
"matched / escape" decision via `BinSse`, no insertion sort.

#### The `STATE[]` array

For `NStates > 0`, `iStates` points to a flat `STATE[NStates + 1]`
array. The states are kept **sorted by `Freq` descending**: the
most-frequent symbol is at index 0, the least-frequent at index
`NStates`. The encoder/decoder walks this array linearly; keeping the
hot states near the front turns `encode1` / `decode1` into a small
expected-case scan instead of a hash lookup.

The Flags field's low nibble caches the **rank of the most-recently-
used state** within the array; the helpers `MinContext->getStates()[
ctxFlags & 0xF]` jump straight to that state.

### A.2 The suffix walk

Two opposite walks happen, often in the same per-symbol step:

```
order-N context  ──iSuffix──▶  order-(N-1) ──iSuffix──▶  order-1  ──iSuffix──▶  order-0
       ▲                              ▲                        ▲
       │ iSuccessor                   │ iSuccessor              │ iSuccessor
   STATE[ ]                       STATE[ ]                  STATE[ ]
```

**Down the suffix chain (escape):** if the current order-`N` context
does *not* have a state for the current symbol, the encoder emits an
"escape" and asks the order-`(N-1)` context. That repeats — possibly
all the way to order-0, which is guaranteed to know every symbol — and
each escape costs additional bits in the compressed stream.

In `RealProcess`, this is the `LABEL_128` loop:

```cpp
do {                                  // ~ ppmd's "while(!FoundState)"
LABEL_128:
  walkSuffix = MinContext->iSuffix;
  if (!walkSuffix) return result;     // hit order-(-1); end of input
  --OrderFall;
  MinContext = (PPM_CONTEXT*)(HeapNull + walkSuffix);
  // ... NStates check; if 0 we already know, otherwise stay in the loop
} while (!walkDelta);
```

**Up the successor chain (model update):** once a symbol is coded, the
model is updated by *creating* successor contexts at orders above the
matched one (`CreateSuccessors`), filling them in lazily as the text
proceeds. That's where new `STATE`s get allocated and `iSuccessor`
links written.

### A.3 Symbol masking and the SymMask trick

When the encoder escapes from order `N` to order `N-1`, the symbols
that order `N` *already considered* must be excluded from order
`N-1`'s distribution — otherwise the escape probability gets paid
twice. The textbook trick is a global `SymMask[256]` array of "epoch
stamps":

```cpp
// from ppmd.cpp encode1
while (p[1].Symbol != symbol) {
  SymMask[p[1].Symbol] = SymCount;   // "this symbol was seen at this epoch"
  LoCnt += p[1].Freq;
  p++;
  if (--i == 0) {
    /* escape */
    NMasked = NStates;
    SymMask[getStates()->Symbol] = SymCount;
    return NULL;
  }
}
```

`SymCount` is the per-symbol epoch counter (the outer-loop iteration
number). To check "was this symbol masked in the current epoch?", do
`SymMask[sym] == SymCount`. No clearing pass — the next iteration
bumps `SymCount` and the old marks expire automatically.

`encode2` / `decode2` (escape recoding) then walks the lower-order
context's `STATE[]` skipping any entry whose Symbol is currently
masked:

```cpp
do {                              // find next un-masked state
  Sym = p[1].Symbol;
  p++;
} while (SymMask[Sym] == SymCount);
```

In `RealProcess`, `epoch` is the renamed `SymCount`; `SymMask[X] =
epoch` writes and `epoch == SymMask[X]` reads appear in both region A
(the multi-state path's state scan) and region C (the masked recoding).
`SymCount` is still the global name; renaming it at file scope to
`symEpoch` is a candidate cleanup.

### A.4 Per-symbol reordering of the STATE[] array

After a symbol is coded, the matched state's `Freq` is bumped and the
array re-sorted to keep "frequent states up front" invariant.
`PPM_CONTEXT::update1` does this with a *one-position* exchange:

```cpp
STATE *PPM_CONTEXT::update1(STATE* p) {
  SummFreq += 4;
  if ((p->Freq += 4) <= MAX_FREQ) {
    STATE tmp, *p0 = getStates();
    StateCpy(tmp, p[0]);          // swap matched state with states[1],
    StateCpy(p[0], p0[1]);        // then move states[0] up to states[1].
    MoveStateUp(p0);
    StateCpy(*(p = p0), tmp);     // matched state now lives at index 0.
  } else {
    p = rescale(p);               // overflow: halve everyone and re-sort.
  }
  return p;
}
```

This isn't a full sort — just bubble the matched state one position
toward the front. Over many symbols the array stays close to
sorted-by-frequency. When `Freq > MAX_FREQ` (`MAX_FREQ == 123`),
`rescale()` halves every freq and does a real sort.

The PE binary's region A and region C both run a similar bubble-up
inside `BubbleSortChain_`, with a multiplier-based priority instead of
plain freq:

```cpp
inline void BubbleSortChain_(sqword* chainEnd, sqword* sortLimit,
                             int sortPriority) {
  for (sqword* p = chainEnd - 1; p > sortLimit; --p) {
    sqword tmp = *(p - 1);
    if (sortPriority * ((STATE*)*p)->Freq <= ((STATE*)tmp)->Freq) break;
    *(p - 1) = *p;
    *p = tmp;
  }
}
```

`sortPriority` is 22 for a matched symbol, smaller for a state that
just hit one of the sparse-submodel signals (next section).

### A.5 SEE/SSE — secondary escape/symbol estimation

PPMII's main contribution over plain PPMd is the **SEE** (Secondary
Escape Estimation) layer: instead of computing the escape probability
from a fixed formula, look it up in a small table keyed by a
**context bitfield** that summarises the current state.

```cpp
struct SEE_CONTEXT {              // sizeof == 4 bytes
  word Summ;                      // running probability * (1 << Shift)
  byte Shift, Count;              // adaptive scale; Count is the until-retune counter
  word getMean();                 // returns Summ >> Shift, with adaptive tune_rare()
};
```

The bitfield construction is the same idea each time: pick a handful
of features that distinguish "easy" from "hard" prediction situations,
quantise each into 1-2 bits, and concatenate them into an index into a
small (2D) `SEE_CONTEXT` table:

```cpp
// from ppmd.cpp encode1's escape estimator
psee = SEE1[ SEEQTable[NStates] ]                       //  - context "size class"
            + (SummFreq > 8*(NStates+1))                //  - is this context dense?
            + 2 * (2*NStates < getSuffix()->NStates)    //  - did NStates just shrink?
            + (Flags & 0x1C)                             //  - per-symbol class bits
            + 32 * (getStates()[1].Symbol ==
                    RecentSymbol[RSContext]);            //  - is the runner-up the recent symbol?
```

Each bitfield term is a single test on model state; the sum is an
index into a 2D table of pre-trained / adaptively-tuned estimates.
`Flags & 0x1C` packs the rank of the most-frequent-symbol's character
class (alphabetic / digit / punctuation / control) — that's the
`SymType[]` table populated in `subs_inittables.inc`.

In `RealProcess`, every "composite index" mega-expression
(`mixIdxA`, `mixIdxC`, `seeIdxF`, `OrderCtxSeed`) is a bitfield of the
same shape: a sum of quantised feature bits at fixed bit positions.
That's why the formatted versions read as columns of terms — each
column is one feature.

#### SSE — Secondary Symbol Estimation cascade

The PE variant extends SEE into a **cascade of SSE stages**, each one
re-estimating the symbol probability given progressively richer
context. The stages, in order:

```
[ BinSse ]            binary-context primary estimate     (region B only)
   ↓
[ Sse1 ]              first secondary stage, per OrderCtxSeed
   ↓
[ SseMatch ]          mixes in match-distance features
   ↓
[ Sse2 ]              third secondary stage
   ↓
[ Sse3 ]              fourth
   ↓
[ PredWeight ]        weighted mix of A/B sub-estimates    (region C only)
```

Each stage holds a `{numerator, denominator}` 2-int cell. The current
estimate `(cumFreq, totFreq)` is mixed with the cell:

```cpp
mean   = scale * slot[0] / slot[1];        // current cell estimate
clamp  = clamp(mean, lo, hi);              // bounded re-estimate
// commit a Bayesian-style update back to (slot[0], slot[1])
SseDeltaUpdate_(slot, delta, absThresh, denThresh, adder);
// or the abbreviated:
SseMixUpdate_(slot, delta, adder);
```

The constants `(absThresh, denThresh, adder)` are tuned per stage
(0x40000/4096/2 for the Sse1 stage, 0x80000/0x2000/1120 for SseMatch,
0x100000/0x2000/1 or 2 for Sse2 and Sse3). The cascade output flows
to the range coder as `(cumFreq, totFreq) → rc.getSubRange(...)`.

### A.6 Sparse submodels attached via SSE contexts

"Sparse" submodels are bitfield-indexed side-tables that the encoder
*also* updates and queries each step, in parallel with the main PPM
model:

- `MatchPosTable[0x10000]` (= 65536 ints, a 256x256 table) — indexed
  by `(MatchCtxHi-byte << 8) | symbol`. Stores the most-recent text
  epoch at which that (high-byte-context, symbol) pair occurred. Looked
  up to compute the match-distance features feeding `SseMatch` and the
  `d107` / `d108` / `d109` fields.

- `MatchPosHash[0x40000]` — byte array; the first half is addressed
  by `(prev_pos + small_offset) & 0x1FFFF`. Each byte is treated as
  a symbol value when read (used as an index into `SymLastCtx`). The
  "hash chain" walked by `WalkEscapeChain_` (in `subs_mixupdate1.inc`)
  and by the `MatchPosPrev`-driven hint chains.

- `MatchPosPrev[131072]` (= `0x20000` ints) — per-epoch back-pointers
  to the previous position with a similar context, forming a linked
  list of recent occurrences. Walked in `MatchPosHint_` to harvest
  "this candidate symbol has appeared here recently" hints.

- `SparseBitmapA[0x4000]` / `SparseBitmapB[0x10000]` — int arrays
  used as bitmaps. The bit position is `Symbol & 31`
  (via `SparseBit = 1 << Symbol` with the implicit shift-mod-32);
  the int index is `(Symbol + SparseHash) >> 5`. A set bit at
  `bitmap[idx] & (1<<symbol)` means "this symbol has been seen in
  this hash bucket recently"; cleared by `&= ~SparseBit` after the
  symbol is encoded.

- `SymLastCtx[1024]` (`SymLastCtx2 = &SymLastCtx[256]`,
  `MatchPosBySym = &SymLastCtx[512]`) — three banks of "epoch when
  this symbol last appeared in this *kind* of context", written by
  `HashArmUpdate_` and similar hint emitters. The encoder uses them
  to favour candidates that match recent patterns.

All of these are **bitfield-keyed** the same way as SSE: each query
packs (symbol, recent-context-hash, sparse-bit) into an index and
either updates the cell or reads it to bias the symbol probability.
That's the entire "sparse submodel" pattern: bitfield index, small
cell, adaptive update.

### A.7 How a single symbol is processed

For orientation, here's the per-symbol skeleton that `RealProcess`
implements (with the PE-specific names as they appear in `dummy.cpp`):

```
1. MinContext = MaxContext                                # current highest-order context
2. if MinContext->NStates:                                # multi-state context
3.     scan STATE[]; build CtxChain[] of non-masked candidates  (LABEL_14 / 18)
4.     if found:    code via Sse1/Match/Sse2/Sse3 cascade      (region A)
5.     else:        emit escape, descend suffix chain          (LABEL_128)
6. else:                                                  # binary context
7.     PPMContextWalk(...) sets up the binary mix index    (region B)
8.     code via BinSse + the same Sse cascade
9. while not found:                                       # escape recoding
10.    walk suffix chain until NStates != NMasked         (LABEL_128 → 298)
11.    build masked candidate set, code via the cascade   (region C)
12. PrepareNextStep:                                      # update the model
13.    bubble the matched STATE up in the array           (BubbleSortChain_)
14.    update SymMask / SparseBitmap / MatchPos*          (sparse submodels)
15.    update every SSE cell along the cascade path        (SseDeltaUpdate_)
16.    create new successor contexts at orders > MaxOrder  (CreateSuccessors)
17. rc.normalize; loop
```

Steps 4, 8 and 11 all run the *same* SSE cascade (and that's why
`dummy.cpp` carries the helpers `MaybeRescale1_` / `RescaleAccum2_` /
`SseClampMean_` / `SseDeltaUpdate_` etc. — they implement one stage of
the cascade and get reused across regions). Steps 12-16 happen
inside the `LABEL_250` tail (`commitSymbol()` in spirit) and in
`UpdateModel` / `CreateSuccessors` / `ReduceOrder`, which are the next
refactoring targets after `RealProcess` itself.

### A.8 References

- D. Shkarin, *PPM: One Step to Practicality* (DCC 2002) and the
  PPMII series — the algorithmic basis.
- `ppmd.cpp` in this tree — Shkarin's reference C++ implementation,
  used as the readability oracle.
- `dummy.cpp` — the PE-binary codec being refactored. Function map:
  `InitTables`, `BinEscFreq`, `RescaleCtx`, `SseScale1`, `SseScale2`,
  `AllocUnitsRare`, `StartModelRare`, `CreateSuccessors`, `UpdateModel`,
  `ReduceOrder`, `PPMContextWalk`, `Rangecoder`, `RealProcess<f_DEC>`.

