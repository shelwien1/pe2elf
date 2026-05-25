# `dummy.cpp` refactoring goals

`dummy.cpp` is the PPMII codec lifted out of a PE binary by decompilation
and folded into a single self-contained C++ source: heap suballocator,
context-tree model, SSE/APM cascade, logistic mixer, range coder, CLI
driver. `ppmd.cpp` in the same directory is Shkarin's readable reference
implementation of the same algorithm; use it as the behaviour and naming
oracle.

`RealProcess<f_DEC>` is the largest single function (~950 lines,
templated for encode/decode) and gets the bulk of the remaining
structural work. The other large functions — `MixUpdate` (~635 lines),
`ReduceOrder` (~280 lines), `StartModelRare` (~215 lines),
`CreateSuccessors`, `UpdateModel`, `PPMContextWalk`, the `Sse*`
helpers — read like ordinary if-dense C++: locals are role-named,
byte-offset access goes through `PPM_CONTEXT*`/`STATE*`/`SseCounter*`/
`SseSlot*` member access, and the helpers are factored out. Total
file size: ~4800 lines. Treat the whole file as the refactoring
target.

## The goal

Make `dummy.cpp` **readable, idiomatic and structured** without changing
the algorithm. The compressed output must remain bit-exact; round-trip
on `book1` (via `make && sh t.sh`) must keep passing after every commit.

The structural target is `ppmd.cpp` in this tree — a ~1700-line readable
implementation of the same PPMII algorithm. Both files share the
allocator names (`AllocUnits`, `FreeContext`, `MEM_BLK::link*`,
`UnitsCpy`, `MoveContext`, `ShrinkUnits`, etc.), the on-disk struct
layouts (`PPM_CONTEXT { NStates, Flags, SummFreq, iStates, iSuffix }`,
`STATE { Symbol, Freq, iSuccessor }`), the quantisation table names
(`SSE0QTable`, `SSE1QTable`, `SEEQTable`, `RLQBounds`, `SSE0QBounds`,
`SSE1QBounds`, `SEEQBounds`, `Indx2Units`, `Units2Indx`, `SymType`),
the model-state globals (`MaxContext`, `OrderFall`, `OrderFall0`,
`MaxOrder`, `RunLength`, `RSContext`, `NMasked`, `SymCount`,
`SymMask[]`, `CutOff`, `Interrupted`), and the API entry points
(`PPMIICreateModel`, `PPMIIEncode`, `PPMIIDecode`, `PPMIIDeleteModel`,
`PPMIIGetCurrentModelSize`). What `dummy.cpp` lacks — and what the
remaining refactoring should add — is `ppmd.cpp`'s **per-arm
decomposition** of `PPM_CONTEXT`: the binary / LES1 / multi-state /
escape arms (in ppmd: paired `encode*` + `decode*` methods; in
dummy: extract each pair as **one templated arm function** under the
existing `<f_DEC>` template — see Section K and the Non-goals).
Plus the small direction-independent helpers (`update1`, `update2`,
`makeEsc1Freq`, `makeEsc2Freq`, `PrepareNextStep`) and the already-
factored `auxFindAndUpdate`/`rescale`/`cutOff` equivalents
(`BinEscFreq`, `RescaleCtx`, `UpdateModel`). The full ppmd.cpp ↔
dummy.cpp mapping table is in appendix §A.8.

## What's wrong

The helpers, allocator, range coder, and non-`RealProcess` model
code (ReduceOrder, MixUpdate, CreateSuccessors, UpdateModel,
BinEscFreq, RescaleCtx, StartModelRare, the SSE rescalers) read
like ordinary if-dense C++. What **doesn't** read like idiomatic
C++ is described below, in roughly decreasing order of impact.

### A. `RealProcess` is a 950-line decompilation

The body of `RealProcess<f_DEC>` runs from line ~3490 to ~4441. It has:

- **~75 local declarations** at the top, grouped by C type (one `int`
  line per type per role-group), not by semantic role:

  ```cpp
  // dummy.cpp:3517-3556 (excerpt, ~40 declaration lines total)
  int sortPriorityC;
  int sxNStatesC, mixFreqC;
  int maskFlagPrevC, sumFreqCacheC;
  int descendNStatesP1E, ofallSavedE;
  int descendNStatesP1C, sparseFlags, remCandF, escSymbol;
  ...
  sqword mixIdxA, sseSlot4A;
  sqword sse2IdxA;
  sqword mixIdxC, mixOffsetC, priorFoundStateF, sse3SlotC, sse4SlotC;
  sqword sseSlot3A, sseQTableIdxC;
  sqword sseQTableIdxA, summFreqPtr;
  int *mixSlotA, *mixBaseAStride, *binMixSlotF, *sse1SlotF, *predWAF;
  int *predWBF, *sseMatchSlotF, *sse2SlotF, *sse3SlotF, *mixBaseB, *mixSlotB;
  int *sse1SlotB, *binSseSlotB, *sseMatchSlotA, *sse2SlotA, *sse3SlotA, *bigSlotC;
  ```

- **12 surviving gotos inside the body** (LABEL_14, _18, _58, _59,
  _128, _165, _201, _250, _292, _296, _298, _335) — the structure of
  the textbook PPMd outer loop is invisible.

- **~120 explicit `_A`/`_B`/`_C`/`_E`/`_F`/`_M` suffixed identifiers**
  (`mixIdxA`, `seeIdxF`, `mixFreqC`, `freqSumE`, `sumFreqW0C`,
  `mixWeightInitA`, `flagsSaveA`, …). The suffixes tag which
  region/branch a local belongs to, because they all share function
  scope.

- **Inline copies of the Sse1 → SseMatch → Sse2 → Sse3 cascade** at
  three sites: region A (lines ~3680–3860, multi-state path), region C
  (lines ~4040–4130, the escape mirror), region F (lines ~4200–4290,
  per-candidate). The per-stage helpers (`Sse1Step_` etc.) exist, but
  the surrounding feature-index computation and the q##-slot
  publishing are spelled out three times.

`RealProcess` is the only function in this shape; the other large
functions in the file read like normal C++.

### B. The labels make the textbook structure invisible

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
twelve jump targets:

```
LABEL_14 / LABEL_18      ~ encode1 state-sort body            (2 entries)
LABEL_58 / LABEL_59      ~ shared mixing-loop entry
LABEL_128                ~ escape suffix descent              (back-edge)
LABEL_165 / LABEL_201    ~ trail / deep find-and-bubble paths (in MixUpdate)
LABEL_250                ~ SYMBOL_FOUND tail
LABEL_292 / 296 / 298    ~ encode2 candidate-set build
LABEL_335                ~ freq-bound clamp
```

with multiple `goto LABEL_x` edges entering each. A first-time reader
has no way to recognise that this is the textbook PPMd outer loop until
they map every label by hand.

Goal: **structure the body so each ppmd primitive is a named function
or a clearly-delimited block.** Labels can stay where the control flow
really is irreducible; everywhere else, prefer `if`/`else`/`while`.

Of the twelve labels, the ones that look genuinely irreducible are
LABEL_14/18 (the encode1 sort loop with two re-entry edges), LABEL_58
(shared mixing-loop entry from two predecessors), LABEL_292/296/298
(the candidate-set sort with cross-block back edge), and LABEL_165/201
inside MixUpdate (trail/deep find-and-bubble paths). LABEL_128
(escape descent) and LABEL_250 (SYMBOL_FOUND tail) look structurable.

### C. The Sse cascade is written out three times

Region A (multi-state) and region F (per-candidate escape) run the
same `Sse1 → SseMatch → Sse2 → Sse3` cascade. Region C (escape
mirror after LABEL_298) runs a parallel `PredWeight + d27`-based
cascade. The per-stage step helpers (`Sse1Step_`, `Sse2Step_`,
`Sse3Step_`, `SseMatchStep_`) are extracted, and the per-stage index
constructions are now also extracted:

- `SseMatchIdxBuild_(sym)` — shared by regions A and F
- `Sse2IdxBuild_(sym, prevWeight, prevTot)` — shared by regions A and F
- `Sse3IdxBuild_(sym, tagSymLast2, heapIdx, sseIdx, sse2Counter, histByte)` — shared by A and F
- `OrderCtxSeedBuild_(sym, matchCtxHi, sparseFlag, carriedFrom, freq, hits)` — shared by B and F

Each call-site still publishes the slot pointer to one of the `q##`
globals (now renamed: SseMatchSlotG, Sse{1,2,3}SlotG, BinSseCellG, etc.)
and captures intermediates into `_A`/`_C`/`_F`-suffixed locals. The
remaining duplication is the surrounding "set up neighbour cells →
RescaleAccum1_ stack → predRescale + cumFreq math" between regions A
and C, which use different mix tables (MixWeight2 vs d29/MixWeight2)
and would need parameterisation over the array layout to merge.

### D. `MixUpdate` is one 635-line function with extractable sections

`MixUpdate` (dummy.cpp:2382-3017) is clean per-section but each
section is a 30-60 line stretch of dense arithmetic that would be
clearer as a named helper. Major sections:

```
2508-2538   Section 1: weight-predictor commits (6× wQxx += δ)
2539-2566   Section 2: SymCount-- / SseSlot positioning
2576-2603   Section 3: per-symbol Sse2State/SseState3 updates + hash rotation
2604-2611   Section 4: RecentPos / SseCtx0_1 epoch update
2612-2640   Section 5: Sse2State histogram increment + halve-on-overflow
2641-2680   Section 6: MixScale heuristic (sym==FoundSymbol / dt-based / sseSlot history)
2681-2735   Section 7: m2_prev/m2_h cascade with consensus-arm loop
2738-2756   Section 8: BijectPairUpdate cascade (b32/33, b34/35, b36/37)
2757-2849   Section 9: BijectMap prediction branch (5-level nested if-else on b1/b2/b3)
2855-3015   Section 10: OrderFall suffix walk (deep / trail find-and-bubble)
```

Sections 5, 7, and 9 are obvious extraction candidates:

```cpp
// dummy.cpp:2646-2652 — section 5, histogram halve-on-overflow
if (newHistCnt > 0xA7u) {
  *counter = 0;
  for (sqword j = 0; j < 512; ++j) {
    int halved = sse2Base[j] >>= 1;
    *counter += halved;
  }
}
```
```cpp
// dummy.cpp:2715-2725 — section 7, m2-chain consensus loop
m2_bias = 0;
do {
  m2_bias += 6144;
  m2_h3 = (byte)MatchPosHash[(m2_prev3+3)&0x1FFFF];
  SymLastCtx2[m2_h3] = sc;
  m2_h1 &= m2_h3;
  m2_h2 = m2_h3 | m2_h2;
  m2_prev3 = MatchPosPrev[m2_prev3&0x1FFFF];
} while ((uint)(m2_bias+symEpochN-m2_prev3) < 0x20000);
```

Goal: **extract Section 5/7/9 as `HalveHistogram_`,
`WalkM2Consensus_`, `BijectPrediction_` helpers**, taking the locals
they need as parameters. Each is self-contained — Section 9 in
particular is currently a 60-line block of nested `if/else if/else`
on `(b1,b2,b3)` equality patterns that would read much better as a
small predicate ladder.

### E. The q-globals don't have semantic names

Renamed at file scope so far: q26 → `bijectCellPtr`, q36 →
`BinSseCellG`, q37 → `PredWeightBG`, q39 → `PredWeightAG`. q9 retains
its name because it has a typed file-scope alias `FoundState` AND a
shadowing local `FoundState` inside `RealProcess` that must keep using
`q9 = ...` / `... = q9` to publish between local and global storage.

Still bare `sqword q##` at file scope: q12, q17, q18, q19, q20, q21,
q22, q23, q24, q25, q29..q35. Each is aliased inside `RealProcess` /
`MixUpdate` to a typed pointer with a semantic name, but the
underlying global is the channel between cascade stages and
`MixUpdate` — so the alias has to live at file scope or be
re-established at every call site.

| q##  | What it points to (semantic name where one exists)             |
|------|----------------------------------------------------------------|
| q12  | `sse2Base` (current Sse2State sub-block, byte\*) — overlay     |
| q14  | `CtxChainEnd` (sqword) — already file-scope aliased            |
| q17  | `wQ17` (predictor-pair int\*; binMixDeltaHi target)            |
| q18  | `wQ18` (predictor int\*; predBaseDeltaB target)                |
| q19  | `sseMatchSlot` (int\*; sseMatchNumDelta/sseMatchDenDelta pair) |
| q20  | `wQ20` (predictor int\*; binMixDeltaLo target)                 |
| q21  | `binMixCenter` (word\*; center of a 4-word binary-mix cell)    |
| q22  | `wQ22` (predictor int\*; predBaseDeltaA target)                |
| q23  | `sse1Slot` (int\*; sse2NumDelta/sse2DenDelta pair)             |
| q24  | `sse2Slot` / `wpQ24` (predictor pair int\*)                    |
| q25  | `sse3Slot` / `wpQ25` (predictor pair int\*)                    |
| q29..q35 | d27/d29-indexed mixing-table slots; reassigned per cascade |

Goal: rename each of these at the definition site, the same way
`d51 → sseCum` was done.

### F. The d-arrays expose raw byte-offset arithmetic

```cpp
// dummy.cpp:89-92
int d29[0x2040];      // 8 KB — escape-mirror mix table
int d27[0x70040];     // ~448 KB — primary mix-model heap, keyed by SSE0QTable
int d90[4096];        // 16 KB — predictor metadata + RecentPos ring
```

`d90[]` is well-named: each individual slot has a file-scope `int&`
alias (`q12BaseSel`, `b31Key`, `Order1Ctx`, …), and `RecentPos =
&d90[15]` covers the ring buffer.

`d27` and `d29` are accessed via raw byte-offset arithmetic plus a
small herd of overlay aliases (`MixBound1..6`, `MixFreq1_1`, `b16`,
`b19`, `w11`, `w12`) declared at file scope. Example:

```cpp
// dummy.cpp:4061 — mixOffsetC indexes into d29 via byte arithmetic
mixOffsetC = (sseQTableIdxC<<11)+8*mixIdxC;
mixSlotC   = (char*)d29 + mixOffsetC;
mixWeightC = *((word*)mixSlotC+3);          // word at offset +6
mixFreqC   = *(word*)((char*)&w12+mixOffsetC);
```

There's no struct describing the per-row layout of d27/d29; the
`<< 11` / `2048` / `+ 8` / `+2048` strides are scattered everywhere.

### G. The b##-named hash tables are opaque

Eight 64 KB byte arrays overlaid on `Sse2State`:

```
b27 — order-1 byte predictor (RSContext × prev-symbol → most-likely-sym)
b28, b29, b30 — three byte-pair hash arms feeding HashArmUpdate_
b31 — byte-pair hash with SymLastCtx routing
b32/b33, b34/b35, b36/b37 — three paired byte-hash predictors (BijectPairUpdate_)
```

Plus `b16[0x20000]` overlaid by `MixBound1` and friends. Plus a
small herd of tiny const tables `b11, b17, b18, b20, b21, b22, b23,
b24` used by `PopCountWeighted_` and the prior init.

Renaming these is low value until their roles are pinned down: each
is a hash from some byte-pair feature to a byte symbol or epoch
stamp, but the precise feature engineering isn't documented anywhere
in `dummy.cpp` or `ppmd.cpp`.

### H. Magic constants without explanation

A handful of literals still appear in arithmetic with no comment.
Already named or commented: 133144 (rewritten as MatchPosHash upper-
half offset), 0xA7 (helper docstring), the 0x55 fill of the SSE
tables (4-line comment in StartModelRare).

Still bare:

```cpp
// magic 6144 bias step inside m2-chain consensus (WalkM2Consensus_)
m2_bias += 6144;

// magic 0x2C00 inside SSE3 bitfield .bit<11>  (now in Sse3IdxBuild_)
.bit  <11>   ((uint)matchPosAge < 0x2C00)
```

`0x1FFFF` (the 17-bit MatchPosHash/SseState3 mask) and `0x40000` (the
SSE-clamp ceiling) likewise appear dozens of times without a named
constant. ppmd.cpp's H_BITS/H_SHIFT would conflict (15-bit vs 17-bit),
so they shouldn't be propagated.

### I. Scattered decompiler-shaped expressions

A few patterns remain that no human would write fresh:

```cpp
// RealProcess LABEL_128 rewind — q34 read via word[3] in caller (no captured wDelta34)
RewindPredictor_(q34, ((word*)q34)[3], rewindMult);
```

```cpp
// promote NStates==0 → NStates==1, with foundSym packed into SummFreq
newCtx->NStates  = 0;
newCtx->Flags    = newFlags;
newCtx->SummFreq = newSym;   // SummFreq word doubles as (sym, freq=0) when NStates==0
```

These are technically correct, but each local expression leaks the
binary memory layout — the surrounding code reads each field
through a named pointer, then drops back into byte arithmetic for
the last assignment.

### J. Section-suffix names live on outside `RealProcess` too

`RealProcess` is the worst offender, but the same suffix style appears
inside `MixUpdate` (`m2_h1`, `m2_h2`, `m2_h3`, `m2_prev1..3`,
`m2_bias`) and at file scope (`b31Key` / `b31KeyPrev`, `Order1Ctx` /
`order1CtxSaved`). The `m2_*` cluster is benign — it tags one
algorithm phase, the same way `MatchPos*` tags another. The
`*Saved` / `*Prev` pairs reflect a real "snapshot before update"
pattern. Goal: live with these; they're communicating something
real.

The truly bad ones are the `_A` / `_B` / `_C` / `_E` / `_F` / `_M`
suffixes inside `RealProcess`, which exist only because every local
shares one function scope.

### K. The textbook PPM-arm decomposition is missing

`ppmd.cpp` (the reference implementation) factors the core algorithm
into **~50 lines** of `RealEncode`/`RealDecode` plus eight short
methods on `PPM_CONTEXT`: paired `encode0`/`decode0`,
`encodeLES1`/`decodeLES1`, `encode1`/`decode1`, `encode2`/`decode2`.
Each pair is two copies of the same arm — same SEE-index build,
same probability math, with only the range-coder operation
differing (`rcEncodeSymbol` vs `rcRemoveSubrange`).

The PE variant collapses each ppmd pair into a single templated
arm: `RealProcess<int f_DEC>` handles both directions in one body
with `if (f_DEC) ...` / `if (!f_DEC) ...` arms at the few points
where encoder and decoder diverge. **Keep that template.** A
literal port to `encode0` + `decode0` separate methods would
*re-introduce* the duplication that the template eliminates.

What's missing is the **per-arm extraction** itself. The eight
ppmd `encode*`/`decode*` pairs map to **four templated arms**:

| Algorithm arm (templated)                  | dummy.cpp location (current)                          |
|--------------------------------------------|-------------------------------------------------------|
| `processBinary<f_DEC>(MinContext, c)`      | RealProcess single-state branch, ~3762–3924 (region B); matches ppmd `encode0`/`decode0` |
| `processLES1<f_DEC>(MinContext, c)`        | RealProcess multi-state first arm, ~3568–3603; matches `encodeLES1`/`decodeLES1` |
| `processMulti<f_DEC>(MinContext, c)`       | RealProcess multi-state state-search, ~3604–3760 (region A); matches `encode1`/`decode1` |
| `processEscape<f_DEC>(MinContext, c)`      | RealProcess LABEL_59 per-candidate dispatch, ~4154–4427 (region F); matches `encode2`/`decode2` |
| `update1(STATE*)`                          | LABEL_250 + bubble-up at ~4365–4385 (no encode/decode split) |
| `update2(STATE*)`                          | escape-tail freq bump at ~4400–4425 (ditto)           |
| `makeEsc1Freq()` / `makeEsc2Freq()`        | SEE-index build inside regions A and F                |
| `PrepareNextStep(MinContext, FoundState)`  | RealProcess LABEL_250 tail (inlined)                  |

The ppmd helpers that have direct dummy.cpp counterparts as free
functions (no extraction needed):

| ppmd.cpp                              | dummy.cpp                            |
|---------------------------------------|--------------------------------------|
| `PPM_CONTEXT::auxFindAndUpdate(s, a)` | `BinEscFreq(pc)`                     |
| `PPM_CONTEXT::rescale(STATE*)`        | `RescaleCtx(pc)`                     |
| `PPM_CONTEXT::cutOff(uint)`           | `UpdateModel(pc, order)`             |
| free `RestoreModelRare(pc)`           | inlined in `ReduceOrder` LABEL_73 path |
| free `FinishCutOff()`                 | inlined in `ReduceOrder`'s glue cleanup |

Of the four arms to extract, `processEscape` (region F) is the big
one: ppmd.cpp's `encode2` is ~30 lines; dummy's LABEL_59 candidate
dispatch is ~270 lines because it inlines the full SSE cascade per
candidate.

Goal: **extract these four `process*<f_DEC>` arms** (each templated,
each containing whatever PE-specific SSE/SEE machinery the arm
actually needs) plus the small unchanged helpers (`update1`,
`update2`, `PrepareNextStep`, `makeEsc1Freq`, `makeEsc2Freq`).
`RealProcess<f_DEC>` would then look like ppmd.cpp's `RealEncode`
under a template — ~50 lines of dispatch + four arm calls, mirroring:

```cpp
template <int f_DEC>
int RealProcess(FILE* outFile, FILE* inFile) {
  do {
    PPM_CONTEXT* MinContext = MaxContext;
    int c = f_DEC ? 0 : getc(inFile);
    STATE* FoundState;
    if (MinContext->NStates) {
      FoundState = processLES1<f_DEC>(MinContext, c);
      if (FoundState) goto SYMBOL_FOUND;
      rc.Normalize<f_DEC>(file);
      FoundState = processMulti<f_DEC>(MinContext, c);
      rc.commitOrEncode<f_DEC>();
    } else
      FoundState = processBinary<f_DEC>(MinContext, c);
    while (!FoundState) {
      rc.Normalize<f_DEC>(file);
      /* descend suffix chain ... */
      FoundState = processEscape<f_DEC>(MinContext, c);
      rc.commitOrEncode<f_DEC>();
    }
SYMBOL_FOUND:
    PrepareNextStep(MinContext, FoundState);
    if (f_DEC) putc(FoundState->Symbol, outFile);
    rc.commitRange();
    rc.Normalize<f_DEC>(file);
  } while (--SymCount);
}
```

Even at the granularity of an `if (f_DEC)` inside an arm, the symmetry
is worth preserving. Encoder and decoder diverge only at a handful of
points (range-coder operation, where the input byte comes from, where
the output byte goes), and forcing them to live in *the same function
body* makes drift impossible — change the probability math in one
place and both directions update together.

Achieving this requires threading the PE variant's larger SSE state
(cascade slot pointers, the q##-published intermediates) through arm
parameters instead of file-scope q-globals — Section E.

#### Sub-arm factorings worth pulling out

Independently of the arm extraction, several blocks **inside the
arms** appear three times across regions A / C / F and would
collapse to one helper if the surrounding locals were lifted:

- **The Sse1 → SseMatch → Sse2 → Sse3 cascade** appears in region A
  (~3680–3860), region C (~4040–4130), and region F (~4200–4290).
  The per-stage helpers (`Sse1Step_`, `SseMatchStep_`, `Sse2Step_`,
  `Sse3Step_`) cover the cell math; the duplication is in the
  slot-pointer computation, the SSE-index build, and the
  q##-publish boilerplate surrounding each stage. (Section C.)
- **The SEE-index bitfield build** for `makeEsc1Freq` (region A) and
  `makeEsc2Freq` (region F) — both are 8–10-term SseIdx{} compositions,
  most terms shared.
- **The state-bubble-up after a frequency increment** appears at
  LABEL_250 (~4365–4385) and inside `BinEscFreq` (lines ~1061–1078).
  Both bubble one state up while `Freq > previous` — different
  termination conditions, but the inner SWAP is the same.

These don't require breaking the `<f_DEC>` template — they're
sub-bodies inside one direction.

### L. Named constants from ppmd.cpp to propagate

`ppmd.cpp` has names for several constants and helpers that dummy.cpp
spells as magic numbers or local renames. The mapping:

| ppmd.cpp                          | dummy.cpp form                                       |
|-----------------------------------|------------------------------------------------------|
| `MAX_O = 16`                      | dynamic `MaxOrder` global                            |
| `UNIT_SIZE = 12`                  | bare `12` inline                                     |
| `N_INDEXES = 38`                  | bare `38` / `0x26` inline                            |
| `INT_BITS = 6, PERIOD_BITS = 7`   | not named — implicit in SSE cell math                |
| `TOT_BITS = 13, BIN_SCALE = 8192` | implicit                                             |
| `H_BITS=15, H_SHIFT=5, H_MASK=0x7FFF` | bare `0x1FFFF`/`0xFFF`/`<<6` for sseState3Hash etc. |
| `ROUND0 = 31, ROUND1 = 53`        | bare `0x1F` / `0x35` literals if present             |
| `MAX_FREQ = 123`                  | matches: `PPM_CONTEXT::MAX_FREQ` enum                |
| `O_BOUND = 9`                     | matches: `PPM_CONTEXT::O_BOUND` enum                 |
| `MEM_DIVISOR = 10`                | bare `120` / `108 / 9` arithmetic                    |
| `RLSM[2][12]` (RunLength state machine) | inlined in update1/update2 sites              |
| `RLQTable`, `SSE0QTable`, `SSE1QTable`, `SEEQTable` | same names, larger sizes (PE variant) |
| `RLQBounds`, `SSE0QBounds`, `SSE1QBounds`, `SEEQBounds` | same names (compatible)             |
| `Indx2Units[N_INDEXES]`, `Units2Indx[128]` | same names, plus PE-only `Units2Indx4[128]` |
| `SymType[256]`                    | same name                                            |
| `RecentSymbol[H_SIZE]`            | not present — PE uses `RecentPos[]` / different      |
| `EscList[MAX_O]`                  | not present — PE keeps SSE-cascade deltas instead    |
| `SEE_CONTEXT { Summ, Shift, Count }` | replaced by PE's larger SSE cell layout           |

ppmd's `Range` struct (`SUBRANGE`) maps to dummy's `Rangecoder rc`
with members `Range`, `Low`, `Code`, `Cache`, `ff_count`, `SubRange`.
The arithmetic packing trick in ppmd's range coder
(`(low^(low+range))<TOP` etc.) is spelled in dummy as an explicit
`Cache + ff_count` carry queue — intentional and bit-exact for the
PE stream format, not a target for un-doing.

The ppmd.cpp names that **should** propagate into dummy.cpp where the
mapping is exact: `MAX_O`, `UNIT_SIZE`, `N_INDEXES`, `MAX_FREQ`
(all already in the constants enum), `MEM_DIVISOR` (now propagated to
PPMIIDeleteModel / StartSubAllocator). Skip `H_BITS`/`H_SHIFT` because
dummy's `sseState3Hash` uses a 17-bit mask where ppmd uses 15-bit —
the values aren't interchangeable. `ROUND0`/`ROUND1` would propagate
if the SSE0/SSE1 arithmetic referenced them; dummy's cells use
different rescale math (the SseScale1/SseScale2 helpers) so the
constants don't appear directly.

The names that **should not** propagate: anything starting with
`Sse1` / `SseMatch` / `Sse2` / `Sse3` / `MatchPosTable` /
`MatchPosPrev` / `MatchPosHash` / `SparseBitmap*` / `BijectMap` /
`b28..b37` — those are PE-specific extensions with no analogue in
`ppmd.cpp`. Don't try to rename them after ppmd's `SEE_CONTEXT` —
they're different cells with different update math.

## Non-goals

### Splitting the `<f_DEC>` template into separate encode/decode pairs

`ppmd.cpp` has eight `PPM_CONTEXT::encode*`/`decode*` methods —
four arm pairs, each pair structurally identical except for which
range-coder call it makes. `dummy.cpp` collapses each pair into one
templated `RealProcess<f_DEC>` body with `if (f_DEC)` branches at
the divergence points. **Keep this template.** When extracting the
per-arm functions (`processBinary<f_DEC>`, `processLES1<f_DEC>`,
`processMulti<f_DEC>`, `processEscape<f_DEC>` — see Section K),
each stays as one templated function with `if (f_DEC)` inside, not
as two separate `encode*` / `decode*` methods. Encoder and decoder
diverge only at a handful of operations (range-coder call, where
the input byte comes from / where the output byte goes), and
forcing them to live in the same function body makes drift
impossible.

Factoring out repeated *direction-independent* sub-bodies inside an
arm (the SSE cascade staging, the SEE-index bitfield build, the
state bubble-up, etc.) is a separate goal — those don't require
breaking the template.

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
helper. Region B inside `RealProcess` does the binary-context work
inline. Don't replace the inline body with a call to
`PPMContextWalk` without re-validating round-trip.

### Wrapping all model state in a class

A `Predictor`/`PPMCodec` struct holding `MaxContext`, `OrderFall`, the
SSE tables etc. is the right end state, but it touches every function
in the file at once. Collect related globals into a struct only once
their per-function roles are clear; don't do it before the q##
renames in Section E.

### Reorganising into multiple files

`dummy.cpp` is intentionally single-file. Don't split it out — the
codec fits in one source file with room to spare.

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

In `RealProcess`, `epoch` is a local capture of `SymCount`;
`SymMask[X] = epoch` writes and `epoch == SymMask[X]` reads appear
in both region A (the multi-state path's state scan) and region C
(the masked recoding). The global is named `SymCount`; renaming it
at file scope to `symEpoch` is a candidate cleanup.

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
`UpdateModel` / `CreateSuccessors` / `ReduceOrder`.

### A.8 Function map: ppmd.cpp ↔ dummy.cpp

Both files share the algorithm and the on-disk PPM_CONTEXT / STATE
layout, but the PE variant adds a much larger SSE cascade and the
sparse submodels of §A.6. Mapping the named entry points:

**Allocator (mostly 1:1, same shape):**

| ppmd.cpp                | dummy.cpp                                                |
|-------------------------|----------------------------------------------------------|
| `MEM_BLK` struct        | `MEM_BLK` (same fields, same methods)                    |
| `StartSubAllocator`     | `StartSubAllocator`                                      |
| `InitSubAllocator`      | inlined into the first half of `StartModelRare`          |
| `AllocUnitsRare`        | `AllocUnitsRare`                                         |
| `AllocUnits`            | `AllocUnits_`                                            |
| `AllocContext`          | `AllocContext_`                                          |
| `FreeUnits`             | `FreeUnits_`                                             |
| `FreeUnitsRare`         | `FreeUnitsRare` (PE version takes an `sqword` not `MEM_BLK*`) |
| `FreeContext`           | `FreeContext_`                                           |
| `ShrinkUnits`           | `ShrinkUnits_`                                           |
| `ExpandUnits`           | inlined in dummy's `UpdateModel` even-NStates branch     |
| `MoveUnits`             | `MoveUnits_`                                             |
| `MoveContext`           | `MoveContext_`                                           |
| `UnitsCpy`              | `UnitsCpy_`                                              |
| `GlueFreeBlocks`        | inlined in `AllocUnitsRare`'s `if (!CutOffCount)` arm    |
| `FinishCutOff`          | inlined in `ReduceOrder` LABEL_73 / glue-cleanup path    |

**Model (algorithm core, names already match):**

| ppmd.cpp                            | dummy.cpp                                              |
|-------------------------------------|--------------------------------------------------------|
| `PPMIICreateModel`                  | `StartSubAllocator` + `StartModelRare(initMode)` pair  |
| `PPMIIDeleteModel`                  | `PPMIIDeleteModel`                                     |
| `PPMIIGetCurrentModelSize`          | `PPMIIGetCurrentModelSize`                             |
| `PPMIIEncode` / `PPMIIDecode`       | same (just different stats-callback signatures)        |
| `StartModelRare(Mode)`              | `StartModelRare(mode)` (compatible)                    |
| `RealEncode` / `RealDecode`         | `RealEncode` / `RealDecode` (templated `RealProcess<f_DEC>`) |
| `PrepareNextStep`                   | RealProcess LABEL_250 tail (inlined)                   |
| `UpdateModel(MinContext, FoundState)` | `UpdateModel(ctx, order)` — **different role!**       |
| `CreateSuccessors(skip, p, pc, fs)` | `CreateSuccessors(depth, chain, seedCtx)` — different signature, similar role |
| `ReduceOrder(p, pc, fs)`            | `ReduceOrder()` — covers both `ReduceOrder` and `RestoreModelRare` from ppmd |
| `RestoreModelRare`                  | folded into dummy's `ReduceOrder` LABEL_73 path        |

**PPM-arm methods to extract — see Section K above:**

ppmd.cpp's `encode*`/`decode*` pairs collapse into single templated
arms under dummy.cpp's existing `<f_DEC>` template. Keep the
template; extract one arm function per pair, not eight separate
methods.

| ppmd.cpp pair                        | dummy.cpp templated arm (proposed)                     |
|--------------------------------------|--------------------------------------------------------|
| `encode0(c)` / `decode0()`           | `processBinary<f_DEC>(...)` — single-state branch (region B) |
| `encodeLES1(c)` / `decodeLES1()`     | `processLES1<f_DEC>(...)` — multi-state first arm     |
| `encode1(c)` / `decode1()`           | `processMulti<f_DEC>(...)` — multi-state state-search (region A) |
| `encode2(c)` / `decode2()`           | `processEscape<f_DEC>(...)` — LABEL_59 candidate dispatch (region F) |
| `update1(p)` / `update2(p)`          | direction-independent post-symbol helpers (no f_DEC split) |
| `makeEsc1Freq()` / `makeEsc2Freq()`  | direction-independent SEE-index builders               |
| `auxFindAndUpdate(sym, add)`         | `BinEscFreq(pc)` already factored                      |
| `rescale(STATE*)`                    | `RescaleCtx(pc)` already factored                      |
| `cutOff(Order)`                      | `UpdateModel(pc, order)` already factored              |

**Range coder (compatible, larger interface in dummy):**

| ppmd.cpp free function   | dummy.cpp `Rangecoder` method                              |
|--------------------------|------------------------------------------------------------|
| `rcInitEncoder`          | `rc.initEncoder()`                                         |
| `rcEncodeSymbol`         | `rc.encodeSymbol(subRange)` + `rc.commitRange()`           |
| `rcFlushEncoder`         | `rc.Flush(File)`                                           |
| `rcInitDecoder`          | `rc.initDecoder(file)`                                     |
| `rcGetCurrentCount`      | `rc.getSubRange(freq, totFreq)` (different signature)      |
| `rcRemoveSubrange`       | `rc.DecodeNotMatched(subRange)` / `rc.commitRange()`       |
| `rcBinStart`             | (none — PE variant doesn't use the binary-coder shortcut)  |
| `rcBinDecode`            | (none)                                                     |
| `rcBinCorrect0`/`1`      | (none)                                                     |
| inline `normalize` macro | `rc.EncodeNormalize(file)` / `rc.DecodeNormalize(file)`    |

The range coder is structurally the same (same `low + range/scale * freq`
arithmetic with TOP/BOT thresholds), but dummy.cpp's PE variant uses a
deferred-carry / FF-stuffing emit path (`Cache`, `ff_count`,
`emitOneByte`) rather than ppmd.cpp's "shift while range < BOT" loop
inline. Both produce equivalent byte streams under different framing.

**Tables (sizes diverge dramatically):**

| ppmd.cpp                          | dummy.cpp                                                |
|-----------------------------------|----------------------------------------------------------|
| `SSE0[12][64]` (768 words)        | `BinSse[0x280]` (640 ints; covers SSE0+SSE1 role)        |
| `SSE1[15][16]` (240 words)        | merged into `BinSse[]`                                   |
| `SEE1[12][64]` (3072 bytes of SEE_CONTEXT) | (no direct counterpart; PE uses the larger Sse* tables) |
| `SEE2[12][32]` (1536 bytes)       | (no direct counterpart)                                  |
| `RecentSymbol[H_SIZE]` (32 KB)    | (no direct counterpart; PE uses `RecentPos[4096]` differently) |
| `EscList[MAX_O]`                  | inlined into MixUpdate's `predSseTotDelta`/cascade deltas |
| `RLQTable[12]`                    | `NextBinFreq[128]` (similar role, larger)                |
| `SSE0QTable[72]`                  | `SSE0QTable[256]` (same name, larger)                    |
| `SSE1QTable[64]`                  | `SSE1QTable[128]` (same)                                 |
| `SEEQTable[256]`                  | `SEEQTable[256]` (same)                                  |
| `SymType[256]`                    | `SymType[256]` (same)                                    |
| `Indx2Units[N_INDEXES]`, `Units2Indx[128]` | same, plus PE adds `Units2Indx4[128]`           |
| (none)                            | `Sse1[0x60040]` (PE-only, 1.5 M ints)                    |
| (none)                            | `SseMatch[0x200040]` (PE-only, ~8 M ints — the big one)  |
| (none)                            | `Sse2[0x30040]` (PE-only, ~786 K ints)                   |
| (none)                            | `Sse3[0x2A03E]` (PE-only, ~688 K ints)                   |
| (none)                            | `PredWeight[0xA1C]`, `MixWeight1`/`MixWeight2`           |
| (none)                            | `MatchPosTable[0x10000]`, `MatchPosPrev[131072]`, `MatchPosHash[0x40000]` |
| (none)                            | `BijectMap[0x40000]`, `SparseBitmapA/B`                  |
| (none)                            | `b27..b37` byte-pair hash arms                           |

The bottom block — anything from `Sse1` down — is PE-only machinery
that has no name in `ppmd.cpp`. Don't try to rename these after
ppmd's `SEE_CONTEXT` / `SSE0` / `SSE1`; the semantics are different
even when the role rhymes.

### A.9 References

- D. Shkarin, *PPM: One Step to Practicality* (DCC 2002) and the
  PPMII series — the algorithmic basis.
- `ppmd.cpp` in this tree — Shkarin's reference C++ implementation,
  used as the readability and naming oracle.
- `dummy.cpp` — the PE-binary codec being refactored. Function map:
  `InitTables`, `BinEscFreq`, `RescaleCtx`, `SseScale1`, `SseScale2`,
  `AllocUnitsRare`, `StartModelRare`, `CreateSuccessors`, `UpdateModel`,
  `ReduceOrder`, `PPMContextWalk`, `Rangecoder`, `RealProcess<f_DEC>`.

