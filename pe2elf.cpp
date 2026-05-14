// pe2elf.cpp - PE32+ (x64) to ELF64 (x86-64) converter
// Standalone, no external dependencies. C++17.
// See pe2elf_design.txt for full design rationale.

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <vector>

// ---------------------------------------------------------------------------
// File buffer
// ---------------------------------------------------------------------------
struct Buffer {
  std::vector<uint8_t> data;
  bool load(const char* path) {
    FILE* f = fopen(path, "rb");
    if( !f ) {
      fprintf(stderr, "Cannot open: %s\n", path);
      return false;
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if( sz<=0 ) {
      fclose(f);
      return false;
    }
    data.resize((size_t)sz);
    size_t r = fread(data.data(), 1, data.size(), f);
    fclose(f);
    return r==data.size();
  }

  template <typename T> const T*at(size_t off) const {
    if( off+sizeof(T)>data.size() )
      return nullptr;
    return reinterpret_cast<const T*>(data.data()+off);
  }

  const char*str(size_t off) const {
    if( off>=data.size() )
      return "";
    for( size_t i = off; i<data.size(); ++i )
      if( data[i]==0 )
        return reinterpret_cast<const char*>(data.data()+off);
    return "";
  }

  size_t size() const {
    return data.size();
  }
};

// ---------------------------------------------------------------------------
// PE structures
// ---------------------------------------------------------------------------
#pragma pack(push, 1)
struct pe_dos_header {
  uint16_t Magic;
  uint16_t UsedBytesInTheLastPage;
  uint16_t FileSizeInPages;
  uint16_t NumberOfRelocationItems;
  uint16_t HeaderSizeInParagraphs;
  uint16_t MinimumExtraParagraphs;
  uint16_t MaximumExtraParagraphs;
  uint16_t InitialRelativeSS;
  uint16_t InitialSP;
  uint16_t Checksum;
  uint16_t InitialIP;
  uint16_t InitialRelativeCS;
  uint16_t AddressOfRelocationTable;
  uint16_t OverlayNumber;
  uint16_t Reserved[4];
  uint16_t OEMid;
  uint16_t OEMinfo;
  uint16_t Reserved2[10];
  uint32_t AddressOfNewExeHeader;
};
struct pe_header {
  char signature[4];
  uint16_t Machine;
  uint16_t NumberOfSections;
  uint32_t TimeDateStamp;
  uint32_t PointerToSymbolTable;
  uint32_t NumberOfSymbols;
  uint16_t SizeOfOptionalHeader;
  uint16_t Characteristics;
};
struct pe64_optional_header {
  uint16_t Magic;
  uint8_t MajorLinkerVersion;
  uint8_t MinorLinkerVersion;
  uint32_t SizeOfCode;
  uint32_t SizeOfInitializedData;
  uint32_t SizeOfUninitializedData;
  uint32_t AddressOfEntryPoint;
  uint32_t BaseOfCode;
  uint64_t ImageBase;
  uint32_t SectionAlignment;
  uint32_t FileAlignment;
  uint16_t MajorOperatingSystemVersion;
  uint16_t MinorOperatingSystemVersion;
  uint16_t MajorImageVersion;
  uint16_t MinorImageVersion;
  uint16_t MajorSubsystemVersion;
  uint16_t MinorSubsystemVersion;
  uint32_t Win32VersionValue;
  uint32_t SizeOfImage;
  uint32_t SizeOfHeaders;
  uint32_t CheckSum;
  uint16_t Subsystem;
  uint16_t DLLCharacteristics;
  uint64_t SizeOfStackReserve;
  uint64_t SizeOfStackCommit;
  uint64_t SizeOfHeapReserve;
  uint64_t SizeOfHeapCommit;
  uint32_t LoaderFlags;
  uint32_t NumberOfRvaAndSize;
};
struct pe_data_directory {
  uint32_t RelativeVirtualAddress;
  uint32_t Size;
};
struct pe_section {
  char Name[8];
  uint32_t VirtualSize;
  uint32_t VirtualAddress;
  uint32_t SizeOfRawData;
  uint32_t PointerToRawData;
  uint32_t PointerToRelocations;
  uint32_t PointerToLineNumbers;
  uint16_t NumberOfRelocations;
  uint16_t NumberOfLineNumbers;
  uint32_t Characteristics;
};
struct pe_import {
  uint32_t ImportLookupTableRVA;
  uint32_t TimeDateStamp;
  uint32_t ForwarderChain;
  uint32_t NameRVA;
  uint32_t ImportAddressTableRVA;
};
#pragma pack(pop)

// PE section characteristics
static const uint32_t PE_SCN_MEM_EXECUTE = 0x20000000;
static const uint32_t PE_SCN_MEM_READ = 0x40000000;
static const uint32_t PE_SCN_MEM_WRITE = 0x80000000;

// Data directory indices
static const uint32_t PE_DD_IMPORT = 1;

// ---------------------------------------------------------------------------
// PE RVA → file offset
// ---------------------------------------------------------------------------
struct PESectionMap {
  struct Entry {
    uint32_t va, raw, rawsz, virtsz;
    uint32_t characteristics;
    char name[9];
    uint64_t elf_foff; // file offset in output ELF (assigned in compute_layout)
  };
  std::vector<Entry> secs;

  uint32_t rva_to_offset(uint32_t rva) const {
    for( auto &e : secs ) {
      uint32_t end = e.va+std::max(e.virtsz, e.rawsz);
      if( rva>=e.va&&rva<end ) {
        uint32_t delta = rva-e.va;
        if( delta<e.rawsz )
          return e.raw+delta;
      }
    }
    return 0;
  }

  // Which section index contains this RVA?
  int section_of(uint32_t rva) const {
    for( int i = 0; i<(int)secs.size(); ++i ) {
      uint32_t end = secs[i].va+std::max(secs[i].virtsz, secs[i].rawsz);
      if( rva>=secs[i].va&&rva<end )
        return i;
    }
    return -1;
  }
};

// ---------------------------------------------------------------------------
// ELF structures
// ---------------------------------------------------------------------------
#pragma pack(push, 1)
struct Elf64_Ehdr {
  uint8_t e_ident[16];
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
  uint8_t st_info;
  uint8_t st_other;
  uint16_t st_shndx;
  uint64_t st_value;
  uint64_t st_size;
};
struct Elf64_Rela {
  uint64_t r_offset;
  uint64_t r_info;
  int64_t r_addend;
};
struct Elf64_Dyn {
  int64_t d_tag;
  union {
    uint64_t d_val;
    uint64_t d_ptr;
  } d_un;
};
#pragma pack(pop)

// ELF constants
static const uint16_t ET_EXEC = 2;
static const uint16_t EM_X86_64 = 62;
static const uint32_t PT_LOAD = 1;
static const uint32_t PT_DYNAMIC = 2;
static const uint32_t PT_INTERP = 3;
static const uint32_t PT_PHDR = 6;
static const uint32_t PT_GNU_RELRO = 0x6474e552;
static const uint32_t PT_GNU_STACK = 0x6474e551;
static const uint32_t PF_X = 1;
static const uint32_t PF_W = 2;
static const uint32_t PF_R = 4;
static const uint32_t SHT_NULL = 0;
static const uint32_t SHT_PROGBITS = 1;
static const uint32_t SHT_SYMTAB = 2;
static const uint32_t SHT_STRTAB = 3;
static const uint32_t SHT_RELA = 4;
static const uint32_t SHT_DYNAMIC = 6;
static const uint32_t SHT_NOBITS = 8;
static const uint32_t SHT_DYNSYM = 11;
static const uint64_t SHF_ALLOC = 0x2;
static const uint64_t SHF_EXECINSTR = 0x4;
static const uint64_t SHF_WRITE = 0x1;
static const uint16_t SHN_UNDEF = 0;
static const uint8_t STB_GLOBAL = 1;
static const uint8_t STT_FUNC = 2;
#define ELF64_R_INFO(sym, type) (((uint64_t)(sym)<<32)|(uint32_t)(type))
static const uint32_t R_X86_64_64 = 1;

static const int64_t DT_NEEDED = 1;
static const int64_t DT_STRTAB = 5;
static const int64_t DT_SYMTAB = 6;
static const int64_t DT_RELA = 7;
static const int64_t DT_RELASZ = 8;
static const int64_t DT_RELAENT = 9;
static const int64_t DT_STRSZ = 10;
static const int64_t DT_SYMENT = 11;
static const int64_t DT_DEBUG = 21;
static const int64_t DT_RUNPATH = 29;
static const int64_t DT_FLAGS_1 = 0x6ffffffb;
static const int64_t DT_NULL = 0;
static const uint64_t DF_1_NOW = 0x00000001;

// ---------------------------------------------------------------------------
// Import record
// ---------------------------------------------------------------------------
struct ImportEntry {
  std::string dll_name;
  std::string func_name;
  uint32_t iat_rva;   // RVA of the IAT slot (8 bytes)
  uint32_t sym_index; // index into .dynsym (assigned later)
};

// ---------------------------------------------------------------------------
// Simple output buffer builder
// ---------------------------------------------------------------------------
struct OutBuf {
  std::vector<uint8_t> data;

  size_t size() const {
    return data.size();
  }

  void append(const void* p, size_t n) {
    const uint8_t* b = (const uint8_t*)p;
    data.insert(data.end(), b, b+n);
  }

  template <typename T> void append_val(T v) {
    append(&v, sizeof(v));
  }

  void pad_to(size_t alignment) {
    while( data.size()%alignment )
      data.push_back(0);
  }

  void pad_to_size(size_t target) {
    while( data.size()<target )
      data.push_back(0);
  }

  // Overwrite at offset (must already be within bounds)
  template <typename T> void patch(size_t off, T v) {
    assert(off+sizeof(T)<=data.size());
    memcpy(data.data()+off, &v, sizeof(v));
  }
};

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------
static uint64_t align_up(uint64_t v, uint64_t a) {
  return (v+a-1)&~(a-1);
}

// ---------------------------------------------------------------------------
// Main converter
// ---------------------------------------------------------------------------
struct Converter {
  // Input
  Buffer pe;
  const pe_dos_header* dos = nullptr;
  const pe_header* peh = nullptr;
  const pe64_optional_header* oh = nullptr;
  size_t dd_off = 0;
  uint32_t num_dd = 0;
  PESectionMap secmap;
  std::vector<ImportEntry> imports; // all IAT entries

  // Configuration
  std::string interp = "/lib64/ld-linux-x86-64.so.2";
  std::string shim_name = "winapi_shim.so";
  bool keep_shdr = true;
  bool strip_pdata = false;

  // Derived
  uint64_t image_base = 0;
  uint32_t ep_rva = 0;

  // ELF layout - virtual addresses
  uint64_t synth_va = 0; // base VA of synthetic LOAD segment
  uint64_t interp_va = 0;
  uint64_t dynamic_va = 0;
  uint64_t dynsym_va = 0;
  uint64_t dynstr_va = 0;
  uint64_t rela_va = 0;
  uint64_t synth_end_va = 0; // end of synthetic segment

  // Trampoline: sub rsp,8 ; jmp pe_entry  (needed because ld.so JMPs to e_entry
  // with RSP≡0 mod 16, but MSVC PE code expects RSP≡8 mod 16 as if CALLed)
  uint64_t trampoline_va = 0;
  uint64_t trampoline_foff = 0;
  std::vector<uint8_t> trampoline_data; // 9 bytes: 48 83 ec 08 e9 xx xx xx xx

  // ELF layout - file offsets
  uint64_t interp_foff = 0;
  uint64_t dynamic_foff = 0;
  uint64_t dynsym_foff = 0;
  uint64_t dynstr_foff = 0;
  uint64_t rela_foff = 0;
  uint64_t synth_foff = 0;   // file offset where synthetic LOAD begins
  uint64_t pe_data_foff = 0; // file offset where PE section data begins
  uint64_t pe_hdr_foff = 0;  // file offset where PE header copy is written

  // Section content
  std::vector<uint8_t> interp_data;
  std::vector<uint8_t> dynstr_data;
  std::vector<Elf64_Sym> dynsym_data;
  std::vector<Elf64_Rela> rela_data;
  std::vector<Elf64_Dyn> dynamic_data;

  // Index of .rdata section (the one containing IAT)
  int rdata_sec_idx = -1;
  // Copy of .rdata with IAT slots zeroed (for ld.so to fill)
  std::vector<uint8_t> rdata_patched;

  // Program headers (assembled later)
  std::vector<Elf64_Phdr> phdrs;

  // Section headers (for --keep-shdr)
  // shstrtab built inline
  std::vector<uint8_t> shstrtab_data;
  std::vector<Elf64_Shdr> shdrs;

  // -----------------------------------------------------------------------
  bool parse_pe() {
    dos = pe.at<pe_dos_header>(0);
    if( !dos||dos->Magic!=0x5A4D ) {
      fprintf(stderr, "Not a valid PE (bad DOS magic)\n");
      return false;
    }
    size_t pe_off = dos->AddressOfNewExeHeader;
    peh = pe.at<pe_header>(pe_off);
    if( !peh||memcmp(peh->signature, "PE\0\0", 4)!=0 ) {
      fprintf(stderr, "Bad PE signature\n");
      return false;
    }
    if( peh->Machine!=0x8664 ) {
      fprintf(stderr, "Not AMD64 PE (machine=0x%04x)\n", peh->Machine);
      return false;
    }
    size_t opt_off = pe_off+sizeof(pe_header);
    auto* magic_p = pe.at<uint16_t>(opt_off);
    if( !magic_p||*magic_p!=0x20B ) {
      fprintf(stderr, "Not PE32+ (magic=0x%04x)\n", magic_p ? *magic_p : 0);
      return false;
    }
    oh = pe.at<pe64_optional_header>(opt_off);
    if( !oh ) {
      fprintf(stderr, "Cannot read PE64 optional header\n");
      return false;
    }
    image_base = oh->ImageBase;
    ep_rva = oh->AddressOfEntryPoint;
    num_dd = oh->NumberOfRvaAndSize;
    dd_off = opt_off+sizeof(pe64_optional_header);

    // Build section map
    size_t sec_off = dd_off+num_dd*sizeof(pe_data_directory);
    for( uint32_t i = 0; i<peh->NumberOfSections; ++i ) {
      auto* s = pe.at<pe_section>(sec_off+i*sizeof(pe_section));
      if( !s )
        break;
      PESectionMap::Entry e{};
      e.va = s->VirtualAddress;
      e.raw = s->PointerToRawData;
      e.rawsz = s->SizeOfRawData;
      e.virtsz = s->VirtualSize;
      e.characteristics = s->Characteristics;
      memcpy(e.name, s->Name, 8);
      e.name[8] = 0;
      secmap.secs.push_back(e);
    }
    return true;
  }

  // -----------------------------------------------------------------------
  bool collect_imports() {
    if( num_dd<=PE_DD_IMPORT )
      return true; // no imports
    auto* imp_dd = pe.at<pe_data_directory>(dd_off+PE_DD_IMPORT*sizeof(pe_data_directory));
    if( !imp_dd||!imp_dd->RelativeVirtualAddress )
      return true;

    uint32_t imp_off = secmap.rva_to_offset(imp_dd->RelativeVirtualAddress);
    for( uint32_t idx = 0;; ++idx ) {
      auto* imp = pe.at<pe_import>(imp_off+idx*sizeof(pe_import));
      if( !imp )
        break;
      if( !imp->NameRVA&&!imp->ImportLookupTableRVA&&!imp->ImportAddressTableRVA )
        break;

      uint32_t name_off = secmap.rva_to_offset(imp->NameRVA);
      std::string dll_name = pe.str(name_off);

      uint32_t ilt_rva = imp->ImportLookupTableRVA ? imp->ImportLookupTableRVA : imp->ImportAddressTableRVA;
      uint32_t iat_rva = imp->ImportAddressTableRVA;
      uint32_t ilt_off = secmap.rva_to_offset(ilt_rva);
      if( !ilt_off )
        continue;

      for( uint32_t j = 0;; ++j ) {
        auto* entry = pe.at<uint64_t>(ilt_off+j*8);
        if( !entry||*entry==0 )
          break;
        uint64_t v = *entry;
        if( v&0x8000000000000000ULL ) {
          // ordinal import - use ordinal as name
          char ordname[32];
          snprintf(ordname, sizeof(ordname), "_ord%llu", (unsigned long long)(v&0xFFFF));
          ImportEntry ie;
          ie.dll_name = dll_name;
          ie.func_name = ordname;
          ie.iat_rva = iat_rva+j*8;
          ie.sym_index = 0;
          imports.push_back(ie);
        } else {
          uint32_t hint_off = secmap.rva_to_offset((uint32_t)(v&0x7FFFFFFF));
          if( hint_off+2<pe.size() ) {
            std::string fname = pe.str(hint_off+2);
            ImportEntry ie;
            ie.dll_name = dll_name;
            ie.func_name = fname;
            ie.iat_rva = iat_rva+j*8;
            ie.sym_index = 0;
            imports.push_back(ie);
          }
        }
      }
    }

    // Identify which section contains the IAT (usually .rdata)
    if( !imports.empty() ) {
      rdata_sec_idx = secmap.section_of(imports[0].iat_rva);
    }

    return true;
  }

  // -----------------------------------------------------------------------
  // Build synthetic section content (.interp .dynstr .dynsym .rela.dyn .dynamic)
  void build_synthetic_sections() {
    // .interp
    interp_data.assign(interp.begin(), interp.end());
    interp_data.push_back(0);

    // .dynstr: \0 | shim_name\0 | $ORIGIN\0 | func1\0 | func2\0 ...
    dynstr_data.push_back(0); // index 0 = empty string
    uint32_t shim_name_off = (uint32_t)dynstr_data.size();
    for( char c : shim_name )
      dynstr_data.push_back((uint8_t)c);
    dynstr_data.push_back(0);
    dynstr_rpath_off = (uint32_t)dynstr_data.size();
    for( char c : std::string("$ORIGIN") )
      dynstr_data.push_back((uint8_t)c);
    dynstr_data.push_back(0);

    // Deduplicate function names (preserve order, first occurrence wins)
    // Build unique list; assign sym_index
    std::vector<std::string> unique_names;
    for( auto &ie : imports ) {
      bool found = false;
      for( size_t k = 0; k<unique_names.size(); ++k ) {
        if( unique_names[k]==ie.func_name ) {
          ie.sym_index = (uint32_t)(k+1);   // +1 for null sym at [0]
          found = true;
          break;
        }
      }
      if( !found ) {
        ie.sym_index = (uint32_t)(unique_names.size()+1);
        unique_names.push_back(ie.func_name);
      }
    }

    // .dynsym: [0] null sym, then one per unique name
    {
      Elf64_Sym null_sym{};
      dynsym_data.push_back(null_sym);
    }
    for( auto &name : unique_names ) {
      uint32_t str_off = (uint32_t)dynstr_data.size();
      for( char c : name )
        dynstr_data.push_back((uint8_t)c);
      dynstr_data.push_back(0);

      Elf64_Sym sym{};
      sym.st_name = str_off;
      sym.st_info = (uint8_t)((STB_GLOBAL<<4)|STT_FUNC);
      sym.st_other = 0;
      sym.st_shndx = SHN_UNDEF;
      sym.st_value = 0;
      sym.st_size = 0;
      dynsym_data.push_back(sym);
    }

    // .rela.dyn: one entry per IAT slot
    for( auto &ie : imports ) {
      Elf64_Rela r{};
      r.r_offset = image_base+ie.iat_rva;
      r.r_info = ELF64_R_INFO(ie.sym_index, R_X86_64_64);
      r.r_addend = 0;
      rela_data.push_back(r);
    }

    // .dynamic: built after VAs are known (call build_dynamic after layout)
    // .dynamic uses shim_name_off in dynstr
    (void)shim_name_off; // stored in position: dynstr[1..]
    // We'll store the shim_name_off for use in build_dynamic
    dynstr_shim_off = shim_name_off;
  }

  // -----------------------------------------------------------------------
  // Build trampoline: sub rsp,8 ; jmp pe_entry
  // Compensates for ld.so JMPing to e_entry with RSP≡0 mod 16,
  // whereas MSVC PE code expects RSP≡8 mod 16 (as if called by OS loader).
  void build_trampoline() {
    uint64_t pe_entry = image_base+ep_rva;
    // sub rsp, 8
    trampoline_data = {0x48, 0x83, 0xec, 0x08};
    // jmp rel32  (e9 xx xx xx xx)
    uint64_t jmp_target = pe_entry;
    uint64_t jmp_instr_end = trampoline_va+4+5;     // after jmp instruction
    int32_t rel32 = (int32_t)(jmp_target-jmp_instr_end);
    trampoline_data.push_back(0xe9);
    trampoline_data.push_back((uint8_t)(rel32));
    trampoline_data.push_back((uint8_t)(rel32>>8));
    trampoline_data.push_back((uint8_t)(rel32>>16));
    trampoline_data.push_back((uint8_t)(rel32>>24));
    // Pad to 16 bytes
    while( trampoline_data.size()<16 )
      trampoline_data.push_back(0x90);
  }

  uint32_t dynstr_shim_off = 0;
  uint32_t dynstr_rpath_off = 0;

  void build_dynamic() {
    auto dyn = [&](int64_t tag, uint64_t val) {
                 Elf64_Dyn d{};
                 d.d_tag = tag;
                 d.d_un.d_val = val;
                 dynamic_data.push_back(d);
               };
    dyn(DT_NEEDED, dynstr_shim_off);
    dyn(DT_RUNPATH, dynstr_rpath_off);
    dyn(DT_STRTAB, dynstr_va);
    dyn(DT_STRSZ, dynstr_data.size());
    dyn(DT_SYMTAB, dynsym_va);
    dyn(DT_SYMENT, sizeof(Elf64_Sym));
    dyn(DT_RELA, rela_va);
    dyn(DT_RELASZ, rela_data.size()*sizeof(Elf64_Rela));
    dyn(DT_RELAENT, sizeof(Elf64_Rela));
    dyn(DT_DEBUG, 0);
    dyn(DT_FLAGS_1, DF_1_NOW);
    dyn(DT_NULL, 0);
  }

  // -----------------------------------------------------------------------
  // Patch IAT slots in a copy of the .rdata section to zero
  // (ld.so will overwrite with symbol address via .rela.dyn)
  void patch_rdata() {
    if( rdata_sec_idx<0 )
      return;
    auto &sec = secmap.secs[rdata_sec_idx];
    size_t raw_size = sec.rawsz;
    rdata_patched.assign(pe.data.data()+sec.raw, pe.data.data()+sec.raw+raw_size);
    for( auto &ie : imports ) {
      // Check if this IAT slot is in .rdata
      if( secmap.section_of(ie.iat_rva)!=rdata_sec_idx )
        continue;
      uint32_t slot_off_in_sec = ie.iat_rva-sec.va;
      if( slot_off_in_sec+8<=raw_size ) {
        memset(rdata_patched.data()+slot_off_in_sec, 0, 8);
      }
    }
  }

  // -----------------------------------------------------------------------
  // Compute ELF layout (VAs and file offsets)
  // Returns false on error.
  bool compute_layout() {
    // Synthetic segment VA: image_base - 0x10000 (one page gap below PE code)
    // But we need at least enough room; compute actual size first.
    uint64_t syn_size_needed = align_up(interp_data.size(), 8)+align_up(dynamic_data.size()*sizeof(Elf64_Dyn), 8)+align_up(dynsym_data.size()*sizeof(Elf64_Sym), 8)+align_up(dynstr_data.size(), 8)+align_up(rela_data.size()*sizeof(Elf64_Rela), 8);
    // dynamic not yet built; add estimate
    syn_size_needed += 12*sizeof(Elf64_Dyn);   // DT entries

    // Keep synthetic base at a nice page-aligned address below image_base
    // Allow room for ELF headers + phdrs at the very start of the synth segment
    uint64_t hdrs_size = sizeof(Elf64_Ehdr)+20*sizeof(Elf64_Phdr);     // generous upper bound
    syn_size_needed += hdrs_size;
    syn_size_needed = align_up(syn_size_needed, 0x1000);

    // Try to put synthetic just below image_base
    // Round synth_va to page boundary
    if( image_base<syn_size_needed+0x10000 ) {
      // Very low ImageBase - put synthetic data at 0x200000
      synth_va = 0x200000;
    } else {
      synth_va = (image_base-syn_size_needed-0x1000)&~0xFFFULL;
    }

    // File layout:
    // [0..ehdr+phdrs] = ELF header + program headers (part of synth LOAD)
    // [interp] [dynsym] [dynstr] [rela.dyn] [.dynamic]
    // [PE sections raw data]
    // [Section headers] (optional)

    // The ELF header and phdrs live at file offset 0 which maps to synth_va
    // Number of phdrs:
    //   PT_PHDR, PT_INTERP, PT_LOAD(synth), PT_DYNAMIC,
    //   PT_LOAD per PE section, PT_GNU_RELRO (for .rdata), PT_GNU_STACK
    uint32_t n_pe_secs = (uint32_t)secmap.secs.size();
    uint32_t n_phdrs = 4+n_pe_secs+2+1;       // +2 RELRO+STACK, +1 PE-hdr LOAD

    uint64_t hdr_file_end = sizeof(Elf64_Ehdr)+n_phdrs*sizeof(Elf64_Phdr);
    hdr_file_end = align_up(hdr_file_end, 8);

    // Assign VAs and file offsets for synthetic sections
    // VAs are relative to synth_va which maps to file offset 0
    interp_va = synth_va+hdr_file_end;
    interp_foff = hdr_file_end;

    uint64_t cur_va = interp_va+align_up(interp_data.size(), 8);
    uint64_t cur_foff = interp_foff+align_up(interp_data.size(), 8);

    dynsym_va = cur_va;
    dynsym_foff = cur_foff;
    cur_va += align_up(dynsym_data.size()*sizeof(Elf64_Sym), 8);
    cur_foff += align_up(dynsym_data.size()*sizeof(Elf64_Sym), 8);

    dynstr_va = cur_va;
    dynstr_foff = cur_foff;
    cur_va += align_up(dynstr_data.size(), 8);
    cur_foff += align_up(dynstr_data.size(), 8);

    rela_va = cur_va;
    rela_foff = cur_foff;
    cur_va += align_up(rela_data.size()*sizeof(Elf64_Rela), 8);
    cur_foff += align_up(rela_data.size()*sizeof(Elf64_Rela), 8);

    dynamic_va = cur_va;
    dynamic_foff = cur_foff;
    // dynamic_data not yet built; will be sized after build_dynamic()
    // reserve space: 12 entries max
    uint64_t dynamic_size_max = 12*sizeof(Elf64_Dyn);
    cur_va += align_up(dynamic_size_max, 8);
    cur_foff += align_up(dynamic_size_max, 8);

    // Trampoline: sub rsp,8 ; jmp pe_entry  (16 bytes reserved)
    trampoline_va = cur_va;
    trampoline_foff = cur_foff;
    cur_va += 16;
    cur_foff += 16;

    // Synthetic segment ends here (page aligned)
    synth_end_va = align_up(cur_va, 0x1000);
    synth_foff = 0; // synthetic segment starts at file offset 0

    // Now that VAs are known, build trampoline and .dynamic
    build_trampoline();
    build_dynamic();

    // PE section data: each section must satisfy
    //   p_offset % p_align == p_vaddr % p_align
    // Since VirtualAddress is page-aligned (SectionAlignment=0x1000),
    // p_vaddr % 0x1000 == 0, so each section's file offset must also be
    // a multiple of 0x1000.  We page-pad between sections.
    pe_data_foff = align_up(cur_foff, 0x1000);
    uint64_t sec_cur = pe_data_foff;
    for( auto &sec : secmap.secs ) {
      sec.elf_foff = sec_cur;
      sec_cur = align_up(sec_cur+sec.rawsz, 0x1000);
    }

    // PE headers (DOS hdr + PE hdr + section table) at ImageBase.
    // Placed after all PE sections; file offset must be page-aligned since
    // the mapped VA (image_base) is page-aligned.
    pe_hdr_foff = sec_cur; // sec_cur is already page-aligned after last section

    return true;
  }

  // -----------------------------------------------------------------------
  // Build program headers
  void build_phdrs(uint64_t shoff) {
    phdrs.clear();

    uint32_t n_pe_secs = (uint32_t)secmap.secs.size();
    // +1 for PE headers PT_LOAD at ImageBase
    uint32_t n_phdrs_total = 4+n_pe_secs+2+1;

    // PT_PHDR
    {
      Elf64_Phdr p{};
      p.p_type = PT_PHDR;
      p.p_flags = PF_R;
      p.p_offset = sizeof(Elf64_Ehdr);
      p.p_vaddr = synth_va+sizeof(Elf64_Ehdr);
      p.p_paddr = p.p_vaddr;
      p.p_filesz = n_phdrs_total*sizeof(Elf64_Phdr);
      p.p_memsz = p.p_filesz;
      p.p_align = 8;
      phdrs.push_back(p);
    }

    // PT_INTERP
    {
      Elf64_Phdr p{};
      p.p_type = PT_INTERP;
      p.p_flags = PF_R;
      p.p_offset = interp_foff;
      p.p_vaddr = interp_va;
      p.p_paddr = interp_va;
      p.p_filesz = interp_data.size();
      p.p_memsz = interp_data.size();
      p.p_align = 1;
      phdrs.push_back(p);
    }

    // PT_LOAD for synthetic segment (RWX: .dynamic writable, trampoline executable)
    {
      uint64_t syn_filesz = trampoline_foff+trampoline_data.size();
      Elf64_Phdr p{};
      p.p_type = PT_LOAD;
      p.p_flags = PF_R|PF_W|PF_X;
      p.p_offset = synth_foff; // 0
      p.p_vaddr = synth_va;
      p.p_paddr = synth_va;
      p.p_filesz = syn_filesz;
      p.p_memsz = syn_filesz;
      p.p_align = 0x1000;
      phdrs.push_back(p);
    }

    // PT_DYNAMIC
    {
      Elf64_Phdr p{};
      p.p_type = PT_DYNAMIC;
      p.p_flags = PF_R|PF_W;
      p.p_offset = dynamic_foff;
      p.p_vaddr = dynamic_va;
      p.p_paddr = dynamic_va;
      p.p_filesz = dynamic_data.size()*sizeof(Elf64_Dyn);
      p.p_memsz = p.p_filesz;
      p.p_align = 8;
      phdrs.push_back(p);
    }

    // PT_LOAD for each PE section
    // elf_foff was pre-computed (page-aligned) in compute_layout()
    int relro_sec_idx = -1;

    for( uint32_t i = 0; i<n_pe_secs; ++i ) {
      auto &sec = secmap.secs[i];
      uint32_t ch = sec.characteristics;

      if( strip_pdata&&memcmp(sec.name, ".pdata", 6)==0 )
        continue;

      uint32_t flags = 0;
      if( ch&PE_SCN_MEM_READ )
        flags |= PF_R;
      if( ch&PE_SCN_MEM_WRITE )
        flags |= PF_W;
      if( ch&PE_SCN_MEM_EXECUTE )
        flags |= PF_X;

      if( (int)i==rdata_sec_idx ) {
        flags |= PF_W;
        relro_sec_idx = (int)i;
      }

      Elf64_Phdr p{};
      p.p_type = PT_LOAD;
      p.p_flags = flags;
      p.p_offset = sec.elf_foff;
      p.p_vaddr = image_base+sec.va;
      p.p_paddr = image_base+sec.va;
      p.p_filesz = sec.rawsz;
      p.p_memsz = std::max((uint64_t)sec.virtsz, (uint64_t)sec.rawsz);
      p.p_align = 0x1000;
      phdrs.push_back(p);
    }

    // PT_GNU_RELRO covering the .rdata-containing segment
    if( relro_sec_idx>=0 ) {
      auto &sec = secmap.secs[relro_sec_idx];
      Elf64_Phdr p{};
      p.p_type = PT_GNU_RELRO;
      p.p_flags = PF_R;
      p.p_offset = sec.elf_foff;
      p.p_vaddr = image_base+sec.va;
      p.p_paddr = image_base+sec.va;
      p.p_filesz = sec.rawsz;
      p.p_memsz = sec.rawsz;
      p.p_align = 1;
      phdrs.push_back(p);
    }

    // PT_GNU_STACK (no exec stack)
    {
      Elf64_Phdr p{};
      p.p_type = PT_GNU_STACK;
      p.p_flags = PF_R|PF_W;
      p.p_offset = 0;
      p.p_vaddr = 0;
      p.p_paddr = 0;
      p.p_filesz = 0;
      p.p_memsz = 0;
      p.p_align = 0x10;
      phdrs.push_back(p);
    }

    // PT_LOAD for PE headers at ImageBase (needed by MSVC CRT which reads PE
    // header data directory at PEB.ImageBaseAddress).
    {
      Elf64_Phdr p{};
      p.p_type = PT_LOAD;
      p.p_flags = PF_R;
      p.p_offset = pe_hdr_foff;
      p.p_vaddr = image_base;
      p.p_paddr = image_base;
      p.p_filesz = oh->SizeOfHeaders;
      p.p_memsz = 0x1000; // one page - covers all PE headers
      p.p_align = 0x1000;
      phdrs.push_back(p);
    }

    (void)shoff;
  }

  // -----------------------------------------------------------------------
  // Build section headers (for debuggability)
  uint32_t add_shstrtab(const char* name) {
    uint32_t off = (uint32_t)shstrtab_data.size();
    while( *name )
      shstrtab_data.push_back((uint8_t)*name++);
    shstrtab_data.push_back(0);
    return off;
  }

  void build_shdrs(uint64_t shstrtab_foff, uint64_t shstrtab_va) {
    shdrs.clear();
    shstrtab_data.clear();
    shstrtab_data.push_back(0); // index 0 = empty

    // [0] NULL
    {
      Elf64_Shdr s{};
      s.sh_type = SHT_NULL;
      shdrs.push_back(s);
    }

    auto add = [&](const char* name, uint32_t type, uint64_t flags, uint64_t addr, uint64_t off, uint64_t size, uint32_t link, uint32_t info, uint64_t align, uint64_t entsize) {
                 Elf64_Shdr s{};
                 s.sh_name = add_shstrtab(name);
                 s.sh_type = type;
                 s.sh_flags = flags;
                 s.sh_addr = addr;
                 s.sh_offset = off;
                 s.sh_size = size;
                 s.sh_link = link;
                 s.sh_info = info;
                 s.sh_addralign = align;
                 s.sh_entsize = entsize;
                 shdrs.push_back(s);
               };

    uint32_t dynsym_shidx = (uint32_t)shdrs.size();
    add(".dynsym", SHT_DYNSYM, SHF_ALLOC, dynsym_va, dynsym_foff, dynsym_data.size()*sizeof(Elf64_Sym),
        dynsym_shidx+1,   // link = .dynstr index
        1, 8, sizeof(Elf64_Sym));

    add(".dynstr", SHT_STRTAB, SHF_ALLOC, dynstr_va, dynstr_foff, dynstr_data.size(), 0, 0, 1, 0);

    // Fix .dynsym sh_link to point to .dynstr (index dynsym_shidx+1)
    shdrs[dynsym_shidx].sh_link = dynsym_shidx+1;

    add(".rela.dyn", SHT_RELA, SHF_ALLOC, rela_va, rela_foff, rela_data.size()*sizeof(Elf64_Rela), dynsym_shidx, 0, 8, sizeof(Elf64_Rela));

    add(".dynamic", SHT_DYNAMIC, SHF_ALLOC|SHF_WRITE, dynamic_va, dynamic_foff, dynamic_data.size()*sizeof(Elf64_Dyn),
        dynsym_shidx+1,   // link = .dynstr
        0, 8, sizeof(Elf64_Dyn));

    add(".interp", SHT_PROGBITS, SHF_ALLOC, interp_va, interp_foff, interp_data.size(), 0, 0, 1, 0);

    // PE sections - use pre-computed elf_foff (page-aligned)
    for( uint32_t i = 0; i<secmap.secs.size(); ++i ) {
      auto &sec = secmap.secs[i];
      uint32_t ch = sec.characteristics;
      uint64_t sh_flags = SHF_ALLOC;
      if( ch&PE_SCN_MEM_WRITE )
        sh_flags |= SHF_WRITE;
      if( ch&PE_SCN_MEM_EXECUTE )
        sh_flags |= SHF_EXECINSTR;

      // Only pure-BSS sections (rawsz==0) use SHT_NOBITS.
      // Sections with a BSS tail (virtsz>rawsz but rawsz>0) keep SHT_PROGBITS
      // with sh_size=rawsz; the zero-fill tail is expressed in the PT_LOAD
      // p_memsz > p_filesz, not in the section header.
      bool all_bss = (sec.rawsz==0);
      uint32_t sh_type = all_bss ? SHT_NOBITS : SHT_PROGBITS;
      uint64_t sh_offset = all_bss ? 0 : sec.elf_foff;
      uint64_t sh_size   = all_bss ? sec.virtsz : sec.rawsz;

      char trimmed[9] = {};
      memcpy(trimmed, sec.name, 8);
      std::string sname = trimmed;
      if( sname.empty()||sname[0]==0 )
        sname = ".pe_sec";

      add(sname.c_str(), sh_type, sh_flags, image_base+sec.va, sh_offset, sh_size, 0, 0, 0x1000, 0);
    }

    // .shstrtab
    uint32_t shstr_idx = (uint32_t)shdrs.size();
    add(".shstrtab", SHT_STRTAB, 0, shstrtab_va, shstrtab_foff,
        0, // size patched after building
        0, 0, 1, 0);
    (void)shstr_idx;
  }

  // -----------------------------------------------------------------------
  bool convert(const char* in_path, const char* out_path) {
    if( !pe.load(in_path) )
      return false;
    if( !parse_pe() )
      return false;

    printf("PE32+ ImageBase=0x%llx EP_RVA=0x%x sections=%u\n", (unsigned long long)image_base, ep_rva, (uint32_t)secmap.secs.size());

    if( !collect_imports() )
      return false;
    printf("Imports: %u IAT entries\n", (uint32_t)imports.size());

    build_synthetic_sections();
    if( !compute_layout() )
      return false;

    patch_rdata();

    // Now we can build program headers
    // compute shoff: end = after PE headers (which follow all PE sections)
    uint64_t last_end = pe_data_foff;
    for( auto &sec : secmap.secs )
      last_end = std::max(last_end, sec.elf_foff+sec.rawsz);
    // PE headers follow at pe_hdr_foff (page-aligned after last section)
    last_end = std::max(last_end, pe_hdr_foff+oh->SizeOfHeaders);
    uint64_t shstrtab_foff = align_up(last_end, 8);
    // shstrtab size unknown yet; build shdrs first (shstrtab built inside)
    uint64_t shoff = 0;
    if( keep_shdr ) {
      // rough: shstrtab_foff + 256 bytes for shstrtab, then shdrs
      // We'll fix after building
      shoff = shstrtab_foff; // placeholder; fixed below
    }

    build_phdrs(shoff);

    // Build section headers (also fills shstrtab_data)
    if( keep_shdr ) {
      build_shdrs(shstrtab_foff, synth_va+shstrtab_foff);   // VA unused for non-alloc
      // Patch size in .shstrtab shdr
      shdrs.back().sh_size = shstrtab_data.size();
      shoff = align_up(shstrtab_foff+shstrtab_data.size(), 8);
    }

    // Build ELF header
    Elf64_Ehdr ehdr{};
    ehdr.e_ident[0] = 0x7f;
    ehdr.e_ident[1] = 'E';
    ehdr.e_ident[2] = 'L';
    ehdr.e_ident[3] = 'F';
    ehdr.e_ident[4] = 2; // ELFCLASS64
    ehdr.e_ident[5] = 1; // ELFDATA2LSB
    ehdr.e_ident[6] = 1; // EV_CURRENT
    ehdr.e_ident[7] = 0; // ELFOSABI_NONE
    ehdr.e_type = ET_EXEC;
    ehdr.e_machine = EM_X86_64;
    ehdr.e_version = 1;
    ehdr.e_entry = trampoline_va; // trampoline: sub rsp,8; jmp pe_entry
    ehdr.e_phoff = sizeof(Elf64_Ehdr);
    ehdr.e_shoff = keep_shdr ? shoff : 0;
    ehdr.e_flags = 0;
    ehdr.e_ehsize = sizeof(Elf64_Ehdr);
    ehdr.e_phentsize = sizeof(Elf64_Phdr);
    ehdr.e_phnum = (uint16_t)phdrs.size();
    ehdr.e_shentsize = sizeof(Elf64_Shdr);
    ehdr.e_shnum = keep_shdr ? (uint16_t)shdrs.size() : 0;
    ehdr.e_shstrndx = keep_shdr ? (uint16_t)(shdrs.size()-1) : 0;

    // ---- Write output ----
    OutBuf out;

    // ELF header
    out.append(&ehdr, sizeof(ehdr));

    // Program headers
    for( auto &p : phdrs )
      out.append(&p, sizeof(p));

    // Pad to interp_foff
    out.pad_to_size(interp_foff);
    out.append(interp_data.data(), interp_data.size());
    out.pad_to_size(dynsym_foff);
    out.append(dynsym_data.data(), dynsym_data.size()*sizeof(Elf64_Sym));
    out.pad_to_size(dynstr_foff);
    out.append(dynstr_data.data(), dynstr_data.size());
    out.pad_to_size(rela_foff);
    out.append(rela_data.data(), rela_data.size()*sizeof(Elf64_Rela));
    out.pad_to_size(dynamic_foff);
    out.append(dynamic_data.data(), dynamic_data.size()*sizeof(Elf64_Dyn));
    out.pad_to_size(trampoline_foff);
    out.append(trampoline_data.data(), trampoline_data.size());

    // PE section raw data - each section at its page-aligned elf_foff
    for( uint32_t i = 0; i<secmap.secs.size(); ++i ) {
      auto &sec = secmap.secs[i];
      out.pad_to_size(sec.elf_foff); // page-pad gap between sections
      if( (int)i==rdata_sec_idx&&!rdata_patched.empty() ) {
        out.append(rdata_patched.data(), rdata_patched.size());
      } else {
        if( sec.raw+sec.rawsz<=pe.size() ) {
          out.append(pe.data.data()+sec.raw, sec.rawsz);
        } else {
          size_t avail = (sec.raw<pe.size()) ? pe.size()-sec.raw : 0;
          if( avail>0 )
            out.append(pe.data.data()+sec.raw, avail);
          for( size_t z = avail; z<sec.rawsz; ++z )
            out.append_val<uint8_t>(0);
        }
      }
    }

    // PE headers copy - mapped at ImageBase so MSVC CRT can walk data dirs
    out.pad_to_size(pe_hdr_foff);
    {
      uint32_t hdr_size = oh->SizeOfHeaders;
      if( hdr_size>pe.size() )
        hdr_size = (uint32_t)pe.size();
      out.append(pe.data.data(), hdr_size);
    }

    // Section headers
    if( keep_shdr ) {
      out.pad_to_size(shstrtab_foff);
      out.append(shstrtab_data.data(), shstrtab_data.size());
      out.pad_to_size(shoff);
      for( auto &s : shdrs )
        out.append(&s, sizeof(s));
    }

    // Write to file
    FILE* f = fopen(out_path, "wb");
    if( !f ) {
      fprintf(stderr, "Cannot create: %s\n", out_path);
      return false;
    }
    size_t written = fwrite(out.data.data(), 1, out.data.size(), f);
    fclose(f);
    if( written!=out.data.size() ) {
      fprintf(stderr, "Write error\n");
      return false;
    }
    chmod(out_path, 0755);

    printf("Written %zu bytes to %s\n", out.data.size(), out_path);
    printf("Entry point: 0x%llx\n", (unsigned long long)(image_base+ep_rva));
    printf("Synthetic segment VA: 0x%llx\n", (unsigned long long)synth_va);
    printf("Program headers: %u\n", (uint32_t)phdrs.size());
    if( keep_shdr )
      printf("Section headers: %u\n", (uint32_t)shdrs.size());
    return true;
  }
};

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------
static void usage(const char* prog) {
  fprintf(stderr,
          "Usage: %s <input.exe> <output.elf>\n"
          "  [--interp <path>]       (default: /lib64/ld-linux-x86-64.so.2)\n"
          "  [--shim-soname <name>]  (default: winapi_shim.so)\n"
          "  [--strip-pdata]         drop .pdata section\n"
          "  [--no-shdr]             omit section headers\n",
          prog);
}

int main(int argc, char** argv) {
  if( argc<3 ) {
    usage(argv[0]);
    return 1;
  }

  Converter conv;
  const char* in_path = nullptr;
  const char* out_path = nullptr;

  for( int i = 1; i<argc; ++i ) {
    if( !strcmp(argv[i], "--interp")&&i+1<argc ) {
      conv.interp = argv[++i];
    } else if( !strcmp(argv[i], "--shim-soname")&&i+1<argc ) {
      conv.shim_name = argv[++i];
    } else if( !strcmp(argv[i], "--strip-pdata") ) {
      conv.strip_pdata = true;
    } else if( !strcmp(argv[i], "--no-shdr") ) {
      conv.keep_shdr = false;
    } else if( !in_path ) {
      in_path = argv[i];
    } else if( !out_path ) {
      out_path = argv[i];
    } else {
      fprintf(stderr, "Unknown argument: %s\n", argv[i]);
      usage(argv[0]);
      return 1;
    }
  }

  if( !in_path||!out_path ) {
    usage(argv[0]);
    return 1;
  }

  return conv.convert(in_path, out_path) ? 0 : 1;
}
