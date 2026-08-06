#pragma once
#include <cstdint>

// ---------------------------------------------------------------------------
// ELF structures — ELFCLASS32 / EM_386
//
// Two traps versus the 64-bit definitions in elf_types.hpp:
//   * Elf32_Sym orders its fields differently: st_value/st_size come BEFORE
//     st_info/st_other/st_shndx.
//   * Elf32_Phdr puts p_flags LAST (after p_memsz), not second.
// The i386 psABI also uses REL (implicit, in-place addends) rather than RELA,
// so there is no r_addend field anywhere.
// ---------------------------------------------------------------------------
#pragma pack(push, 1)
struct Elf32_Ehdr {
  uint8_t  e_ident[16];
  uint16_t e_type;
  uint16_t e_machine;
  uint32_t e_version;
  uint32_t e_entry;
  uint32_t e_phoff;
  uint32_t e_shoff;
  uint32_t e_flags;
  uint16_t e_ehsize;
  uint16_t e_phentsize;
  uint16_t e_phnum;
  uint16_t e_shentsize;
  uint16_t e_shnum;
  uint16_t e_shstrndx;
};
struct Elf32_Phdr {
  uint32_t p_type;
  uint32_t p_offset;
  uint32_t p_vaddr;
  uint32_t p_paddr;
  uint32_t p_filesz;
  uint32_t p_memsz;
  uint32_t p_flags;   // note: last, unlike Elf64_Phdr
  uint32_t p_align;
};
struct Elf32_Shdr {
  uint32_t sh_name;
  uint32_t sh_type;
  uint32_t sh_flags;
  uint32_t sh_addr;
  uint32_t sh_offset;
  uint32_t sh_size;
  uint32_t sh_link;
  uint32_t sh_info;
  uint32_t sh_addralign;
  uint32_t sh_entsize;
};
struct Elf32_Sym {
  uint32_t st_name;
  uint32_t st_value;  // note: before st_info, unlike Elf64_Sym
  uint32_t st_size;
  uint8_t  st_info;
  uint8_t  st_other;
  uint16_t st_shndx;
};
// i386 uses REL: the addend lives in the 4 bytes at r_offset.
struct Elf32_Rel {
  uint32_t r_offset;
  uint32_t r_info;
};
struct Elf32_Dyn {
  int32_t d_tag;
  union {
    uint32_t d_val;
    uint32_t d_ptr;
  } d_un;
};
#pragma pack(pop)

static_assert(sizeof(Elf32_Ehdr) == 52, "Elf32_Ehdr size mismatch");
static_assert(sizeof(Elf32_Phdr) == 32, "Elf32_Phdr size mismatch");
static_assert(sizeof(Elf32_Shdr) == 40, "Elf32_Shdr size mismatch");
static_assert(sizeof(Elf32_Sym)  == 16, "Elf32_Sym size mismatch");
static_assert(sizeof(Elf32_Rel)  ==  8, "Elf32_Rel size mismatch");
static_assert(sizeof(Elf32_Dyn)  ==  8, "Elf32_Dyn size mismatch");

// ELF constants
static const uint16_t ET_EXEC    = 2;
static const uint16_t ET_DYN     = 3;
static const uint16_t EM_386     = 3;
static const uint8_t  ELFCLASS32 = 1;
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
static const uint32_t SHT_HASH     = 5;
static const uint32_t SHT_DYNAMIC  = 6;
static const uint32_t SHT_NOBITS   = 8;
static const uint32_t SHT_REL      = 9;
static const uint32_t SHT_DYNSYM   = 11;
static const uint32_t SHF_ALLOC    = 0x2;
static const uint32_t SHF_EXECINSTR= 0x4;
static const uint32_t SHF_WRITE    = 0x1;
static const uint16_t SHN_UNDEF    = 0;
static const uint16_t SHN_ABS      = 0xfff1;
static const uint8_t  STB_GLOBAL   = 1;
static const uint8_t  STT_OBJECT   = 1;
static const uint8_t  STT_FUNC     = 2;
// 24-bit symbol index, 8-bit relocation type
#define ELF32_R_INFO(sym, type) (((uint32_t)(sym)<<8)|((uint32_t)(type)&0xff))
static const uint32_t R_386_32       = 1;  // S + A
static const uint32_t R_386_RELATIVE = 8;  // B + A

static const int32_t DT_NEEDED   = 1;
static const int32_t DT_HASH     = 4;
static const int32_t DT_STRTAB   = 5;
static const int32_t DT_SYMTAB   = 6;
static const int32_t DT_STRSZ    = 10;
static const int32_t DT_SYMENT   = 11;
static const int32_t DT_REL      = 17;
static const int32_t DT_RELSZ    = 18;
static const int32_t DT_RELENT   = 19;
static const int32_t DT_TEXTREL  = 22;
static const int32_t DT_DEBUG    = 21;
static const int32_t DT_RUNPATH  = 29;
static const int32_t DT_FLAGS_1  = (int32_t)0x6ffffffb;
static const int32_t DT_NULL     = 0;
static const uint32_t DF_1_NOW   = 0x00000001;
