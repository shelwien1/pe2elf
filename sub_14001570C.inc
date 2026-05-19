// =====================================================================
// sub_14001570C @ 0x14001570C
// asm: xor ecx,ecx ; jmp cs:__imp_EncodePointer
// =====================================================================

#define FILE FILE1

// IAT slot — §6.4
typedef __attribute__((ms_abi)) void* (*pfn_EncodePointer)(void*);
static pfn_EncodePointer& EncodePointer = *(pfn_EncodePointer*)0x140022118;

PROBE_DECL(__sub_14001570C)
__attribute__((ms_abi)) PVOID __sub_14001570C() {
  PROBE_HIT(__sub_14001570C);
  return EncodePointer(nullptr);
}

#undef FILE
