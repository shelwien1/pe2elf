#pragma once
#include <cstdint>

// ---------------------------------------------------------------------------
// ELF structures
// ---------------------------------------------------------------------------
#pragma pack(push, 1)
struct Elf64_Ehdr {
  uint8_t  e_ident[16];
  uint16_t e_type;
  uint16_t e_machine;
  uint32_t e_version;
  uint64_t e_entry;
  uint64_t e_phoff;
  uint64_t e_shoff;
  uint32_t e_flags;
  uint16_t e_ehsize;
  uint16_t e_phentsize;
  uint16_t e_phnum;
  uint16_t e_shentsize;
  uint16_t e_shnum;
  uint16_t e_shstrndx;
};
struct Elf64_Phdr {
  uint32_t p_type;
  uint32_t p_flags;
  uint64_t p_offset;
  uint64_t p_vaddr;
  uint64_t p_paddr;
  uint64_t p_filesz;
  uint64_t p_memsz;
  uint64_t p_align;
};
struct Elf64_Shdr {
  uint32_t sh_name;
  uint32_t sh_type;
  uint64_t sh_flags;
  uint64_t sh_addr;
  uint64_t sh_offset;
  uint64_t sh_size;
  uint32_t sh_link;
  uint32_t sh_info;
  uint64_t sh_addralign;
  uint64_t sh_entsize;
};
struct Elf64_Sym {
  uint32_t st_name;
  uint8_t  st_info;
  uint8_t  st_other;
  uint16_t st_shndx;
  uint64_t st_value;
  uint64_t st_size;
};
struct Elf64_Rela {
  uint64_t r_offset;
  uint64_t r_info;
  int64_t  r_addend;
};
struct Elf64_Dyn {
  int64_t d_tag;
  union {
    uint64_t d_val;
    uint64_t d_ptr;
  } d_un;
};
#pragma pack(pop)

static_assert(sizeof(Elf64_Ehdr) == 64,  "Elf64_Ehdr size mismatch");
static_assert(sizeof(Elf64_Phdr) == 56,  "Elf64_Phdr size mismatch");
static_assert(sizeof(Elf64_Shdr) == 64,  "Elf64_Shdr size mismatch");
static_assert(sizeof(Elf64_Sym)  == 24,  "Elf64_Sym size mismatch");
static_assert(sizeof(Elf64_Rela) == 24,  "Elf64_Rela size mismatch");
static_assert(sizeof(Elf64_Dyn)  == 16,  "Elf64_Dyn size mismatch");

// ELF constants
static const uint16_t ET_EXEC    = 2;
static const uint16_t ET_DYN     = 3;
static const uint16_t EM_X86_64  = 62;
static const uint32_t PT_LOAD    = 1;
static const uint32_t PT_DYNAMIC = 2;
static const uint32_t PT_INTERP  = 3;
static const uint32_t PT_PHDR    = 6;
static const uint32_t PT_GNU_RELRO  = 0x6474e552;
static const uint32_t PT_GNU_STACK  = 0x6474e551;
static const uint32_t PF_X = 1;
static const uint32_t PF_W = 2;
static const uint32_t PF_R = 4;
static const uint32_t SHT_NULL     = 0;
static const uint32_t SHT_PROGBITS = 1;
static const uint32_t SHT_SYMTAB   = 2;
static const uint32_t SHT_STRTAB   = 3;
static const uint32_t SHT_RELA     = 4;
static const uint32_t SHT_DYNAMIC  = 6;
static const uint32_t SHT_NOBITS   = 8;
static const uint32_t SHT_DYNSYM   = 11;
static const uint64_t SHF_ALLOC    = 0x2;
static const uint64_t SHF_EXECINSTR= 0x4;
static const uint64_t SHF_WRITE    = 0x1;
static const uint16_t SHN_UNDEF    = 0;
static const uint16_t SHN_ABS      = 0xfff1;
static const uint8_t  STB_GLOBAL   = 1;
static const uint8_t  STT_OBJECT   = 1;
static const uint8_t  STT_FUNC     = 2;
#define ELF64_R_INFO(sym, type) (((uint64_t)(sym)<<32)|(uint32_t)(type))
static const uint32_t R_X86_64_64       = 1;
static const uint32_t R_X86_64_RELATIVE = 8;

static const int64_t DT_NEEDED   = 1;
static const int64_t DT_STRTAB   = 5;
static const int64_t DT_SYMTAB   = 6;
static const int64_t DT_RELA     = 7;
static const int64_t DT_RELASZ   = 8;
static const int64_t DT_RELAENT  = 9;
static const int64_t DT_STRSZ    = 10;
static const int64_t DT_SYMENT   = 11;
static const int64_t DT_DEBUG    = 21;
static const int64_t DT_RUNPATH  = 29;
static const int64_t DT_FLAGS_1  = 0x6ffffffb;
static const int64_t DT_NULL     = 0;
static const uint64_t DF_1_NOW   = 0x00000001;
