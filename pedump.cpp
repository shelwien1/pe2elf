// Self-contained PE/ELF (32/64-bit) loader and dumper
// Struct definitions derived from LIEF (lief-project/LIEF)
// No external dependencies — C++17 only

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

// ---------------------------------------------------------------------------
// File helper
// ---------------------------------------------------------------------------
struct Buffer {
    std::vector<uint8_t> data;
    bool load(const char* path) {
        FILE* f = fopen(path, "rb");
        if (!f) { fprintf(stderr, "Cannot open: %s\n", path); return false; }
        fseek(f, 0, SEEK_END);
        long sz = ftell(f);
        fseek(f, 0, SEEK_SET);
        if (sz <= 0) { fclose(f); return false; }
        data.resize((size_t)sz);
        size_t r = fread(data.data(), 1, data.size(), f);
        fclose(f);
        return r == data.size();
    }
    template<typename T> const T* at(size_t off) const {
        if (off + sizeof(T) > data.size()) return nullptr;
        return reinterpret_cast<const T*>(data.data() + off);
    }
    const char* str(size_t off) const {
        if (off >= data.size()) return "";
        // scan for null terminator within bounds
        for (size_t i = off; i < data.size(); ++i)
            if (data[i] == 0) return reinterpret_cast<const char*>(data.data() + off);
        return "";
    }
    size_t size() const { return data.size(); }
};

// ---------------------------------------------------------------------------
// PE structures (from LIEF src/PE/structures.inc)
// ---------------------------------------------------------------------------
#pragma pack(push,1)
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
    char     signature[4]; // "PE\0\0"
    uint16_t Machine;
    uint16_t NumberOfSections;
    uint32_t TimeDateStamp;
    uint32_t PointerToSymbolTable;
    uint32_t NumberOfSymbols;
    uint16_t SizeOfOptionalHeader;
    uint16_t Characteristics;
};

struct pe32_optional_header {
    uint16_t Magic;
    uint8_t  MajorLinkerVersion;
    uint8_t  MinorLinkerVersion;
    uint32_t SizeOfCode;
    uint32_t SizeOfInitializedData;
    uint32_t SizeOfUninitializedData;
    uint32_t AddressOfEntryPoint;
    uint32_t BaseOfCode;
    uint32_t BaseOfData;
    uint32_t ImageBase;
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
    uint32_t SizeOfStackReserve;
    uint32_t SizeOfStackCommit;
    uint32_t SizeOfHeapReserve;
    uint32_t SizeOfHeapCommit;
    uint32_t LoaderFlags;
    uint32_t NumberOfRvaAndSize;
};

struct pe64_optional_header {
    uint16_t Magic;
    uint8_t  MajorLinkerVersion;
    uint8_t  MinorLinkerVersion;
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
    char     Name[8];
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

struct pe_export_directory_table {
    uint32_t ExportFlags;
    uint32_t Timestamp;
    uint16_t MajorVersion;
    uint16_t MinorVersion;
    uint32_t NameRVA;
    uint32_t OrdinalBase;
    uint32_t AddressTableEntries;
    uint32_t NumberOfNamePointers;
    uint32_t ExportAddressTableRVA;
    uint32_t NamePointerRVA;
    uint32_t OrdinalTableRVA;
};

struct pe_base_relocation_block {
    uint32_t PageRVA;
    uint32_t BlockSize;
};

struct pe_exception_entry_x64 {
    uint32_t address_start_rva;
    uint32_t address_end_rva;
    uint32_t unwind_info_rva;
};
#pragma pack(pop)

// PE machine types
static const char* pe_machine_str(uint16_t m) {
    switch (m) {
        case 0x0000: return "UNKNOWN";
        case 0x014c: return "I386";
        case 0x0200: return "IA64";
        case 0x8664: return "AMD64";
        case 0x01c0: return "ARM";
        case 0xaa64: return "ARM64";
        case 0x01c4: return "ARMNT";
        default:     return "OTHER";
    }
}

static const char* pe_subsystem_str(uint16_t s) {
    switch (s) {
        case 1:  return "NATIVE";
        case 2:  return "WINDOWS_GUI";
        case 3:  return "WINDOWS_CUI";
        case 7:  return "POSIX_CUI";
        case 9:  return "WINDOWS_CE_GUI";
        case 10: return "EFI_APPLICATION";
        case 14: return "XBOX";
        default: return "OTHER";
    }
}

// Data directory indices
enum {
    PE_DD_EXPORT    = 0,
    PE_DD_IMPORT    = 1,
    PE_DD_RESOURCE  = 2,
    PE_DD_EXCEPTION = 3,
    PE_DD_BASERELOC = 5,
    PE_DD_DEBUG     = 6,
    PE_DD_TLS       = 9,
    PE_DD_LOADCFG   = 10,
    PE_DD_BOUNDIMPORT= 11,
    PE_DD_IAT       = 12,
    PE_DD_DELAYIMPORT= 13,
    PE_DD_CLR       = 14,
};

// Section characteristics flags
static void print_section_flags(uint32_t c) {
    if (c & 0x00000020) printf(" CODE");
    if (c & 0x00000040) printf(" IDATA");
    if (c & 0x00000080) printf(" UDATA");
    if (c & 0x02000000) printf(" DISCARDABLE");
    if (c & 0x04000000) printf(" NO_CACHE");
    if (c & 0x08000000) printf(" NO_PAGE");
    if (c & 0x10000000) printf(" SHARED");
    if (c & 0x20000000) printf(" EXECUTE");
    if (c & 0x40000000) printf(" READ");
    if (c & 0x80000000) printf(" WRITE");
}

// ---------------------------------------------------------------------------
// PE: RVA → file offset using section table
// ---------------------------------------------------------------------------
struct PESectionMap {
    struct Entry { uint32_t va, raw, rawsz, virtsz; };
    std::vector<Entry> secs;

    uint32_t rva_to_offset(uint32_t rva) const {
        for (auto& e : secs) {
            uint32_t end = e.va + std::max(e.virtsz, e.rawsz);
            if (rva >= e.va && rva < end) {
                uint32_t delta = rva - e.va;
                if (delta < e.rawsz) return e.raw + delta;
            }
        }
        return 0;
    }
};

// ---------------------------------------------------------------------------
// PE dumper
// ---------------------------------------------------------------------------
static void dump_pe(const Buffer& buf) {
    printf("=== PE ===\n");

    auto* dos = buf.at<pe_dos_header>(0);
    if (!dos || dos->Magic != 0x5A4D) { printf("Not a valid PE (bad DOS magic)\n"); return; }
    printf("[DOS] e_lfanew=0x%x\n", dos->AddressOfNewExeHeader);

    size_t pe_off = dos->AddressOfNewExeHeader;
    auto* peh = buf.at<pe_header>(pe_off);
    if (!peh || memcmp(peh->signature, "PE\0\0", 4) != 0) { printf("Bad PE signature\n"); return; }

    printf("[PE Header]\n");
    printf("  Machine:          0x%04x (%s)\n", peh->Machine, pe_machine_str(peh->Machine));
    printf("  NumberOfSections: %u\n", peh->NumberOfSections);
    printf("  TimeDateStamp:    0x%08x\n", peh->TimeDateStamp);
    printf("  Characteristics:  0x%04x", peh->Characteristics);
    if (peh->Characteristics & 0x0002) printf(" EXE");
    if (peh->Characteristics & 0x2000) printf(" DLL");
    if (peh->Characteristics & 0x0020) printf(" LARGE_ADDR");
    printf("\n");

    size_t opt_off = pe_off + sizeof(pe_header);
    auto* magic_p = buf.at<uint16_t>(opt_off);
    if (!magic_p) { printf("Cannot read optional header magic\n"); return; }
    uint16_t opt_magic = *magic_p;
    bool is64 = (opt_magic == 0x20B);

    uint64_t image_base = 0;
    uint32_t ep_rva = 0, size_of_image = 0, subsystem = 0;
    uint32_t num_dd = 0;
    size_t dd_off = 0; // file offset of first data directory

    if (is64) {
        auto* oh = buf.at<pe64_optional_header>(opt_off);
        if (!oh) { printf("Cannot read PE64 optional header\n"); return; }
        image_base    = oh->ImageBase;
        ep_rva        = oh->AddressOfEntryPoint;
        size_of_image = oh->SizeOfImage;
        subsystem     = oh->Subsystem;
        num_dd        = oh->NumberOfRvaAndSize;
        dd_off        = opt_off + sizeof(pe64_optional_header);
        printf("[Optional Header PE64]\n");
        printf("  ImageBase:        0x%016llx\n", (unsigned long long)oh->ImageBase);
        printf("  EntryPoint RVA:   0x%08x\n", oh->AddressOfEntryPoint);
        printf("  SizeOfImage:      0x%x\n", oh->SizeOfImage);
        printf("  SizeOfHeaders:    0x%x\n", oh->SizeOfHeaders);
        printf("  Subsystem:        %u (%s)\n", oh->Subsystem, pe_subsystem_str(oh->Subsystem));
        printf("  DLLChar:          0x%04x\n", oh->DLLCharacteristics);
        printf("  SectionAlign:     0x%x\n", oh->SectionAlignment);
        printf("  FileAlign:        0x%x\n", oh->FileAlignment);
        printf("  NumDataDirs:      %u\n", oh->NumberOfRvaAndSize);
    } else {
        auto* oh = buf.at<pe32_optional_header>(opt_off);
        if (!oh) { printf("Cannot read PE32 optional header\n"); return; }
        image_base    = oh->ImageBase;
        ep_rva        = oh->AddressOfEntryPoint;
        size_of_image = oh->SizeOfImage;
        subsystem     = oh->Subsystem;
        num_dd        = oh->NumberOfRvaAndSize;
        dd_off        = opt_off + sizeof(pe32_optional_header);
        printf("[Optional Header PE32]\n");
        printf("  ImageBase:        0x%08x\n", oh->ImageBase);
        printf("  EntryPoint RVA:   0x%08x\n", oh->AddressOfEntryPoint);
        printf("  SizeOfImage:      0x%x\n", oh->SizeOfImage);
        printf("  SizeOfHeaders:    0x%x\n", oh->SizeOfHeaders);
        printf("  Subsystem:        %u (%s)\n", oh->Subsystem, pe_subsystem_str(oh->Subsystem));
        printf("  DLLChar:          0x%04x\n", oh->DLLCharacteristics);
        printf("  SectionAlign:     0x%x\n", oh->SectionAlignment);
        printf("  FileAlign:        0x%x\n", oh->FileAlignment);
        printf("  NumDataDirs:      %u\n", oh->NumberOfRvaAndSize);
    }
    (void)image_base; (void)size_of_image; (void)subsystem;

    // Data directories
    auto get_dd = [&](uint32_t idx) -> const pe_data_directory* {
        if (idx >= num_dd) return nullptr;
        return buf.at<pe_data_directory>(dd_off + idx * sizeof(pe_data_directory));
    };

    // Sections
    size_t sec_off = dd_off + num_dd * sizeof(pe_data_directory);
    PESectionMap secmap;
    printf("\n[Sections] count=%u\n", peh->NumberOfSections);
    printf("  %-8s  %8s  %8s  %8s  %8s  %s\n",
           "Name","VirtAddr","VirtSize","RawOff","RawSize","Flags");
    for (uint32_t i = 0; i < peh->NumberOfSections; ++i) {
        auto* s = buf.at<pe_section>(sec_off + i * sizeof(pe_section));
        if (!s) break;
        char name[9] = {};
        memcpy(name, s->Name, 8);
        printf("  %-8s  %08x  %08x  %08x  %08x ", name,
               s->VirtualAddress, s->VirtualSize,
               s->PointerToRawData, s->SizeOfRawData);
        print_section_flags(s->Characteristics);
        printf("\n");
        PESectionMap::Entry e;
        e.va = s->VirtualAddress; e.raw = s->PointerToRawData;
        e.rawsz = s->SizeOfRawData; e.virtsz = s->VirtualSize;
        secmap.secs.push_back(e);
    }

    // Imports
    auto* imp_dd = get_dd(PE_DD_IMPORT);
    if (imp_dd && imp_dd->RelativeVirtualAddress && imp_dd->Size) {
        printf("\n[Imports]\n");
        uint32_t imp_off = secmap.rva_to_offset(imp_dd->RelativeVirtualAddress);
        for (uint32_t idx = 0; ; ++idx) {
            auto* imp = buf.at<pe_import>(imp_off + idx * sizeof(pe_import));
            if (!imp) break;
            if (!imp->NameRVA && !imp->ImportLookupTableRVA && !imp->ImportAddressTableRVA) break;
            uint32_t name_off = secmap.rva_to_offset(imp->NameRVA);
            printf("  DLL: %s\n", buf.str(name_off));

            uint32_t ilt_rva = imp->ImportLookupTableRVA ? imp->ImportLookupTableRVA
                                                         : imp->ImportAddressTableRVA;
            uint32_t ilt_off = secmap.rva_to_offset(ilt_rva);
            if (!ilt_off) continue;

            for (uint32_t j = 0; ; ++j) {
                if (is64) {
                    auto* entry = buf.at<uint64_t>(ilt_off + j * 8);
                    if (!entry || *entry == 0) break;
                    uint64_t v = *entry;
                    if (v & 0x8000000000000000ULL) {
                        printf("    ordinal #%llu\n", (unsigned long long)(v & 0xFFFF));
                    } else {
                        uint32_t hint_off = secmap.rva_to_offset((uint32_t)(v & 0x7FFFFFFF));
                        if (hint_off + 2 < buf.size()) {
                            uint16_t hint = *buf.at<uint16_t>(hint_off);
                            printf("    [%5u] %s\n", hint, buf.str(hint_off + 2));
                        }
                    }
                } else {
                    auto* entry = buf.at<uint32_t>(ilt_off + j * 4);
                    if (!entry || *entry == 0) break;
                    uint32_t v = *entry;
                    if (v & 0x80000000u) {
                        printf("    ordinal #%u\n", v & 0xFFFF);
                    } else {
                        uint32_t hint_off = secmap.rva_to_offset(v & 0x7FFFFFFF);
                        if (hint_off + 2 < buf.size()) {
                            uint16_t hint = *buf.at<uint16_t>(hint_off);
                            printf("    [%5u] %s\n", hint, buf.str(hint_off + 2));
                        }
                    }
                }
            }
        }
    }

    // Exports
    auto* exp_dd = get_dd(PE_DD_EXPORT);
    if (exp_dd && exp_dd->RelativeVirtualAddress && exp_dd->Size) {
        printf("\n[Exports]\n");
        uint32_t exp_off = secmap.rva_to_offset(exp_dd->RelativeVirtualAddress);
        auto* edt = buf.at<pe_export_directory_table>(exp_off);
        if (edt) {
            uint32_t dllname_off = secmap.rva_to_offset(edt->NameRVA);
            printf("  DLL Name:      %s\n", buf.str(dllname_off));
            printf("  OrdinalBase:   %u\n", edt->OrdinalBase);
            printf("  NumFunctions:  %u\n", edt->AddressTableEntries);
            printf("  NumNames:      %u\n", edt->NumberOfNamePointers);

            uint32_t eat_off  = secmap.rva_to_offset(edt->ExportAddressTableRVA);
            uint32_t enpt_off = secmap.rva_to_offset(edt->NamePointerRVA);
            uint32_t eot_off  = secmap.rva_to_offset(edt->OrdinalTableRVA);

            for (uint32_t i = 0; i < edt->NumberOfNamePointers; ++i) {
                auto* name_rva_p = buf.at<uint32_t>(enpt_off + i * 4);
                auto* ord_p      = buf.at<uint16_t>(eot_off  + i * 2);
                if (!name_rva_p || !ord_p) break;
                uint32_t fn_off = secmap.rva_to_offset(eat_off ? *buf.at<uint32_t>(eat_off + (*ord_p) * 4) : 0);
                uint32_t sym_off = secmap.rva_to_offset(*name_rva_p);
                uint32_t fn_rva  = eat_off ? *buf.at<uint32_t>(eat_off + (*ord_p) * 4) : 0;
                // Check if forwarder (RVA inside export section)
                bool fwd = fn_rva >= exp_dd->RelativeVirtualAddress &&
                           fn_rva <  exp_dd->RelativeVirtualAddress + exp_dd->Size;
                if (fwd) {
                    uint32_t fwd_off = secmap.rva_to_offset(fn_rva);
                    printf("  [%5u] %-40s -> %s (forwarder)\n",
                           *ord_p + edt->OrdinalBase, buf.str(sym_off), buf.str(fwd_off));
                } else {
                    printf("  [%5u] %-40s rva=0x%08x\n",
                           *ord_p + edt->OrdinalBase, buf.str(sym_off), fn_rva);
                }
                (void)fn_off;
            }
        }
    }

    // Base Relocations
    auto* reloc_dd = get_dd(PE_DD_BASERELOC);
    if (reloc_dd && reloc_dd->RelativeVirtualAddress && reloc_dd->Size) {
        printf("\n[Base Relocations]\n");
        uint32_t r_off = secmap.rva_to_offset(reloc_dd->RelativeVirtualAddress);
        uint32_t r_end = r_off + reloc_dd->Size;
        uint32_t total_entries = 0;
        uint32_t cur = r_off;
        while (cur + sizeof(pe_base_relocation_block) <= r_end && cur < buf.size()) {
            auto* blk = buf.at<pe_base_relocation_block>(cur);
            if (!blk || blk->BlockSize < 8) break;
            uint32_t n = (blk->BlockSize - 8) / 2;
            printf("  Block PageRVA=0x%08x  entries=%u\n", blk->PageRVA, n);
            for (uint32_t i = 0; i < n; ++i) {
                auto* e = buf.at<uint16_t>(cur + 8 + i * 2);
                if (!e) break;
                uint16_t type = (*e >> 12) & 0xF;
                uint16_t offs = *e & 0x0FFF;
                if (type == 0) continue; // padding
                static const char* reloc_types[] = {
                    "ABS","HIGH","LOW","HIGHLOW","HIGHADJ","MIPS_JMPADDR",
                    "ARM_MOV32","THUMB_MOV32","","","DIR64"
                };
                const char* tname = (type < 11) ? reloc_types[type] : "UNK";
                printf("    0x%08x  type=%-12s (%u)\n",
                       blk->PageRVA + offs, tname, type);
                ++total_entries;
            }
            cur += blk->BlockSize;
        }
        printf("  Total relocation entries: %u\n", total_entries);
    }

    // Exceptions (.pdata)
    auto* exc_dd = get_dd(PE_DD_EXCEPTION);
    if (exc_dd && exc_dd->RelativeVirtualAddress && exc_dd->Size) {
        printf("\n[Exceptions / .pdata]\n");
        if (peh->Machine == 0x8664 || peh->Machine == 0xaa64) {
            uint32_t e_off = secmap.rva_to_offset(exc_dd->RelativeVirtualAddress);
            uint32_t n = exc_dd->Size / sizeof(pe_exception_entry_x64);
            printf("  %-12s  %-12s  %-12s\n","StartRVA","EndRVA","UnwindRVA");
            for (uint32_t i = 0; i < n; ++i) {
                auto* e = buf.at<pe_exception_entry_x64>(e_off + i * sizeof(pe_exception_entry_x64));
                if (!e) break;
                printf("  0x%08x    0x%08x    0x%08x\n",
                       e->address_start_rva, e->address_end_rva, e->unwind_info_rva);
            }
            printf("  (%u entries)\n", n);
        } else {
            printf("  (ARM/MIPS exception format — not decoded)\n");
        }
    }

    printf("\n");
}

// ---------------------------------------------------------------------------
// ELF structures (from LIEF src/ELF/structures.inc)
// ---------------------------------------------------------------------------
#pragma pack(push,1)
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

struct Elf32_Phdr {
    uint32_t p_type;
    uint32_t p_offset;
    uint32_t p_vaddr;
    uint32_t p_paddr;
    uint32_t p_filesz;
    uint32_t p_memsz;
    uint32_t p_flags;
    uint32_t p_align;
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

struct Elf32_Sym {
    uint32_t st_name;
    uint32_t st_value;
    uint32_t st_size;
    uint8_t  st_info;
    uint8_t  st_other;
    uint16_t st_shndx;
};

struct Elf64_Sym {
    uint32_t st_name;
    uint8_t  st_info;
    uint8_t  st_other;
    uint16_t st_shndx;
    uint64_t st_value;
    uint64_t st_size;
};

struct Elf32_Rel  { uint32_t r_offset; uint32_t r_info; };
struct Elf32_Rela { uint32_t r_offset; uint32_t r_info; int32_t  r_addend; };
struct Elf64_Rel  { uint64_t r_offset; uint64_t r_info; };
struct Elf64_Rela { uint64_t r_offset; uint64_t r_info; int64_t  r_addend; };

struct Elf32_Dyn { int32_t  d_tag; union { uint32_t d_val; uint32_t d_ptr; } d_un; };
struct Elf64_Dyn { int64_t  d_tag; union { uint64_t d_val; uint64_t d_ptr; } d_un; };
#pragma pack(pop)

// ELF constants
static const char* elf_type_str(uint16_t t) {
    switch (t) {
        case 0: return "NONE";  case 1: return "REL";
        case 2: return "EXEC";  case 3: return "DYN";
        case 4: return "CORE";  default: return "OTHER";
    }
}
static const char* elf_machine_str(uint16_t m) {
    switch (m) {
        case 0:   return "NONE";     case 2:  return "SPARC";
        case 3:   return "386";      case 8:  return "MIPS";
        case 20:  return "PPC";      case 21: return "PPC64";
        case 40:  return "ARM";      case 50: return "IA64";
        case 62:  return "AMD64";    case 183: return "AArch64";
        case 243: return "RISC-V";   default: return "OTHER";
    }
}
static const char* elf_sh_type_str(uint32_t t) {
    switch (t) {
        case 0:  return "NULL";      case 1:  return "PROGBITS";
        case 2:  return "SYMTAB";    case 3:  return "STRTAB";
        case 4:  return "RELA";      case 5:  return "HASH";
        case 6:  return "DYNAMIC";   case 7:  return "NOTE";
        case 8:  return "NOBITS";    case 9:  return "REL";
        case 10: return "SHLIB";     case 11: return "DYNSYM";
        case 14: return "INIT_ARRAY";case 15: return "FINI_ARRAY";
        case 16: return "PREINIT_ARRAY"; case 17: return "GROUP";
        case 18: return "SYMTAB_SHNDX";
        case 0x6ffffff6: return "GNU_HASH";
        case 0x6ffffffe: return "VERNEED";
        case 0x6fffffff: return "VERSYM";
        case 0x6ffffff9: return "GNU_RELRO";
        default: return "OTHER";
    }
}
static const char* elf_seg_type_str(uint32_t t) {
    switch (t) {
        case 0: return "NULL";       case 1: return "LOAD";
        case 2: return "DYNAMIC";    case 3: return "INTERP";
        case 4: return "NOTE";       case 5: return "SHLIB";
        case 6: return "PHDR";       case 7: return "TLS";
        case 0x6474e550: return "GNU_EH_FRAME";
        case 0x6474e551: return "GNU_STACK";
        case 0x6474e552: return "GNU_RELRO";
        case 0x6474e553: return "GNU_PROPERTY";
        default: return "OTHER";
    }
}
static const char* elf_dyn_tag_str(int64_t tag) {
    switch (tag) {
        case 0:  return "NULL";      case 1:  return "NEEDED";
        case 2:  return "PLTRELSZ";  case 3:  return "PLTGOT";
        case 4:  return "HASH";      case 5:  return "STRTAB";
        case 6:  return "SYMTAB";    case 7:  return "RELA";
        case 8:  return "RELASZ";    case 9:  return "RELAENT";
        case 10: return "STRSZ";     case 11: return "SYMENT";
        case 12: return "INIT";      case 13: return "FINI";
        case 14: return "SONAME";    case 15: return "RPATH";
        case 16: return "SYMBOLIC";  case 17: return "REL";
        case 18: return "RELSZ";     case 19: return "RELENT";
        case 20: return "PLTREL";    case 21: return "DEBUG";
        case 22: return "TEXTREL";   case 23: return "JMPREL";
        case 24: return "BIND_NOW";  case 25: return "INIT_ARRAY";
        case 26: return "FINI_ARRAY";case 27: return "INIT_ARRAYSZ";
        case 28: return "FINI_ARRAYSZ"; case 29: return "RUNPATH";
        case 30: return "FLAGS";
        case 0x6ffffef5: return "GNU_HASH";
        case 0x6ffffff0: return "VERSYM";
        case 0x6ffffffe: return "VERNEED";
        case 0x6fffffff: return "VERNEEDNUM";
        case 0x6ffffff9: return "RELACOUNT";
        case 0x6ffffffb: return "FLAGS_1";
        default: return nullptr;
    }
}

static const char* elf_sym_binding(uint8_t info) {
    switch (info >> 4) {
        case 0: return "LOCAL";  case 1: return "GLOBAL";
        case 2: return "WEAK";   default: return "OTHER";
    }
}
static const char* elf_sym_type(uint8_t info) {
    switch (info & 0xF) {
        case 0: return "NOTYPE"; case 1: return "OBJECT";
        case 2: return "FUNC";   case 3: return "SECTION";
        case 4: return "FILE";   case 6: return "TLS";
        case 10: return "GNU_IFUNC"; default: return "OTHER";
    }
}

// x86-64 relocation type names
static const char* elf_reloc_x64(uint32_t type) {
    switch (type) {
        case 0:  return "R_X86_64_NONE";
        case 1:  return "R_X86_64_64";
        case 2:  return "R_X86_64_PC32";
        case 3:  return "R_X86_64_GOT32";
        case 4:  return "R_X86_64_PLT32";
        case 5:  return "R_X86_64_COPY";
        case 6:  return "R_X86_64_GLOB_DAT";
        case 7:  return "R_X86_64_JUMP_SLOT";
        case 8:  return "R_X86_64_RELATIVE";
        case 9:  return "R_X86_64_GOTPCREL";
        case 10: return "R_X86_64_32";
        case 11: return "R_X86_64_32S";
        case 24: return "R_X86_64_PC64";
        case 37: return "R_X86_64_TLSDESC";
        case 38: return "R_X86_64_IRELATIVE";
        default: {
            static char buf[32];
            snprintf(buf, sizeof(buf), "R_X86_64_%u", type);
            return buf;
        }
    }
}

// ---------------------------------------------------------------------------
// ELF dumper
// ---------------------------------------------------------------------------
static void dump_elf(const Buffer& buf) {
    printf("=== ELF ===\n");

    if (buf.size() < 16) { printf("Too small\n"); return; }
    const uint8_t* ident = buf.data.data();
    if (ident[0] != 0x7f || ident[1] != 'E' || ident[2] != 'L' || ident[3] != 'F') {
        printf("Not ELF\n"); return;
    }

    uint8_t ei_class = ident[4]; // 1=32bit, 2=64bit
    uint8_t ei_data  = ident[5]; // 1=LE, 2=BE
    uint8_t ei_osabi = ident[7];
    bool is64 = (ei_class == 2);

    static const char* abi_names[] = {
        "SYSV","HP-UX","NetBSD","Linux","GNU/Hurd","","Solaris","AIX",
        "IRIX","FreeBSD","Tru64","Modesto","OpenBSD","OpenVMS","NSK","AROS"
    };

    printf("[ELF Ident]\n");
    printf("  Class:   %s\n", is64 ? "ELF64" : "ELF32");
    printf("  Data:    %s\n", ei_data == 1 ? "LE" : "BE");
    printf("  OSABI:   %s\n", ei_osabi < 16 ? abi_names[ei_osabi] : "OTHER");

    // We only parse LE for simplicity
    if (ei_data != 1) { printf("  Big-endian ELF not supported in this build\n"); return; }

    uint16_t e_type, e_machine, e_shnum, e_shstrndx, e_phnum;
    uint64_t e_entry, e_phoff, e_shoff;
    uint16_t e_phentsize, e_shentsize;

    if (is64) {
        auto* eh = buf.at<Elf64_Ehdr>(0);
        if (!eh) { printf("Cannot read ELF64 header\n"); return; }
        e_type = eh->e_type; e_machine = eh->e_machine;
        e_entry = eh->e_entry; e_phoff = eh->e_phoff; e_shoff = eh->e_shoff;
        e_phnum = eh->e_phnum; e_shnum = eh->e_shnum; e_shstrndx = eh->e_shstrndx;
        e_phentsize = eh->e_phentsize; e_shentsize = eh->e_shentsize;
    } else {
        auto* eh = buf.at<Elf32_Ehdr>(0);
        if (!eh) { printf("Cannot read ELF32 header\n"); return; }
        e_type = eh->e_type; e_machine = eh->e_machine;
        e_entry = eh->e_entry; e_phoff = eh->e_phoff; e_shoff = eh->e_shoff;
        e_phnum = eh->e_phnum; e_shnum = eh->e_shnum; e_shstrndx = eh->e_shstrndx;
        e_phentsize = eh->e_phentsize; e_shentsize = eh->e_shentsize;
    }

    printf("  Type:    %s\n", elf_type_str(e_type));
    printf("  Machine: %s\n", elf_machine_str(e_machine));
    printf("  Entry:   0x%llx\n", (unsigned long long)e_entry);
    printf("  PHoff:   0x%llx  (%u entries, entsize=%u)\n",
           (unsigned long long)e_phoff, e_phnum, e_phentsize);
    printf("  SHoff:   0x%llx  (%u entries, entsize=%u)\n",
           (unsigned long long)e_shoff, e_shnum, e_shentsize);

    // --- Helpers to read section/segment by index ---
    // Section name strtab
    auto get_shdr_offset = [&](uint16_t idx) -> size_t {
        return (size_t)e_shoff + idx * e_shentsize;
    };
    auto get_sh_name_off = [&](uint16_t idx) -> uint64_t {
        if (is64) {
            auto* s = buf.at<Elf64_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_name : 0;
        } else {
            auto* s = buf.at<Elf32_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_name : 0;
        }
    };
    auto get_sh_offset = [&](uint16_t idx) -> uint64_t {
        if (is64) {
            auto* s = buf.at<Elf64_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_offset : 0;
        } else {
            auto* s = buf.at<Elf32_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_offset : 0;
        }
    };
    auto get_sh_size = [&](uint16_t idx) -> uint64_t {
        if (is64) {
            auto* s = buf.at<Elf64_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_size : 0;
        } else {
            auto* s = buf.at<Elf32_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_size : 0;
        }
    };
    auto get_sh_entsize = [&](uint16_t idx) -> uint64_t {
        if (is64) {
            auto* s = buf.at<Elf64_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_entsize : 0;
        } else {
            auto* s = buf.at<Elf32_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_entsize : 0;
        }
    };
    auto get_sh_link = [&](uint16_t idx) -> uint32_t {
        if (is64) {
            auto* s = buf.at<Elf64_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_link : 0;
        } else {
            auto* s = buf.at<Elf32_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_link : 0;
        }
    };
    auto get_sh_info = [&](uint16_t idx) -> uint32_t {
        if (is64) {
            auto* s = buf.at<Elf64_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_info : 0;
        } else {
            auto* s = buf.at<Elf32_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_info : 0;
        }
    };
    auto get_sh_type = [&](uint16_t idx) -> uint32_t {
        if (is64) {
            auto* s = buf.at<Elf64_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_type : 0;
        } else {
            auto* s = buf.at<Elf32_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_type : 0;
        }
    };
    auto get_sh_flags = [&](uint16_t idx) -> uint64_t {
        if (is64) {
            auto* s = buf.at<Elf64_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_flags : 0;
        } else {
            auto* s = buf.at<Elf32_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_flags : 0;
        }
    };
    auto get_sh_addr = [&](uint16_t idx) -> uint64_t {
        if (is64) {
            auto* s = buf.at<Elf64_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_addr : 0;
        } else {
            auto* s = buf.at<Elf32_Shdr>(get_shdr_offset(idx));
            return s ? s->sh_addr : 0;
        }
    };

    // Section name string table
    uint64_t shstrtab_off = (e_shstrndx && e_shstrndx < e_shnum) ? get_sh_offset(e_shstrndx) : 0;
    auto sh_name = [&](uint16_t idx) -> const char* {
        uint64_t name_off = get_sh_name_off(idx);
        if (!shstrtab_off) return "";
        return buf.str((size_t)(shstrtab_off + name_off));
    };

    // Find section by type
    auto find_sec_by_type = [&](uint32_t type) -> uint16_t {
        for (uint16_t i = 0; i < e_shnum; ++i)
            if (get_sh_type(i) == type) return i;
        return 0xFFFF;
    };
    auto find_sec_by_name = [&](const char* name) -> uint16_t {
        for (uint16_t i = 0; i < e_shnum; ++i)
            if (strcmp(sh_name(i), name) == 0) return i;
        return 0xFFFF;
    };

    // --- Program headers (segments) ---
    printf("\n[Program Headers / Segments] count=%u\n", e_phnum);
    printf("  %-18s  %-10s  %-18s  %-18s  %-10s  %-10s  Flags\n",
           "Type","FileOff","VAddr","PAddr","FileSz","MemSz");
    for (uint16_t i = 0; i < e_phnum; ++i) {
        size_t ph_off = (size_t)e_phoff + i * e_phentsize;
        if (is64) {
            auto* ph = buf.at<Elf64_Phdr>(ph_off);
            if (!ph) break;
            printf("  %-18s  0x%08llx  0x%016llx  0x%016llx  0x%08llx  0x%08llx  %c%c%c\n",
                   elf_seg_type_str(ph->p_type),
                   (unsigned long long)ph->p_offset,
                   (unsigned long long)ph->p_vaddr,
                   (unsigned long long)ph->p_paddr,
                   (unsigned long long)ph->p_filesz,
                   (unsigned long long)ph->p_memsz,
                   (ph->p_flags & 4) ? 'R' : '-',
                   (ph->p_flags & 2) ? 'W' : '-',
                   (ph->p_flags & 1) ? 'X' : '-');
            if (ph->p_type == 3 && ph->p_offset < buf.size()) // INTERP
                printf("    Interpreter: %s\n", buf.str((size_t)ph->p_offset));
        } else {
            auto* ph = buf.at<Elf32_Phdr>(ph_off);
            if (!ph) break;
            printf("  %-18s  0x%08x  0x%08x  0x%08x  0x%08x  0x%08x  %c%c%c\n",
                   elf_seg_type_str(ph->p_type),
                   ph->p_offset, ph->p_vaddr, ph->p_paddr,
                   ph->p_filesz, ph->p_memsz,
                   (ph->p_flags & 4) ? 'R' : '-',
                   (ph->p_flags & 2) ? 'W' : '-',
                   (ph->p_flags & 1) ? 'X' : '-');
            if (ph->p_type == 3 && ph->p_offset < buf.size())
                printf("    Interpreter: %s\n", buf.str(ph->p_offset));
        }
    }

    // --- Section headers ---
    printf("\n[Section Headers] count=%u\n", e_shnum);
    printf("  %3s  %-20s  %-14s  %-18s  %-10s  %-10s  Flags\n",
           "Idx","Name","Type","Addr","Offset","Size");
    for (uint16_t i = 0; i < e_shnum; ++i) {
        uint32_t stype = get_sh_type(i);
        uint64_t sflags = get_sh_flags(i);
        uint64_t saddr  = get_sh_addr(i);
        uint64_t soff   = get_sh_offset(i);
        uint64_t ssz    = get_sh_size(i);
        printf("  %3u  %-20s  %-14s  0x%016llx  0x%08llx  0x%08llx  %c%c%c\n",
               i, sh_name(i), elf_sh_type_str(stype),
               (unsigned long long)saddr,
               (unsigned long long)soff,
               (unsigned long long)ssz,
               (sflags & 2) ? 'W' : '-',
               (sflags & 4) ? 'A' : '-',
               (sflags & 8) ? 'X' : '-');
    }

    // --- Dynamic section ---
    uint16_t dyn_idx = find_sec_by_type(6); // SHT_DYNAMIC
    if (dyn_idx != 0xFFFF) {
        printf("\n[Dynamic Section]\n");
        uint64_t doff = get_sh_offset(dyn_idx);
        uint64_t dsz  = get_sh_size(dyn_idx);
        uint16_t strtab_idx = (uint16_t)get_sh_link(dyn_idx);
        uint64_t dynstrtab_off = (strtab_idx < e_shnum) ? get_sh_offset(strtab_idx) : 0;

        if (is64) {
            size_t n = (size_t)dsz / sizeof(Elf64_Dyn);
            for (size_t i = 0; i < n; ++i) {
                auto* d = buf.at<Elf64_Dyn>((size_t)doff + i * sizeof(Elf64_Dyn));
                if (!d || d->d_tag == 0) break;
                const char* tname = elf_dyn_tag_str(d->d_tag);
                if (tname) {
                    if (d->d_tag == 1 || d->d_tag == 14 || d->d_tag == 15 || d->d_tag == 29) {
                        const char* s = dynstrtab_off ? buf.str((size_t)dynstrtab_off + d->d_un.d_val) : "";
                        printf("  %-16s  0x%016llx  \"%s\"\n", tname, (unsigned long long)d->d_un.d_val, s);
                    } else {
                        printf("  %-16s  0x%016llx\n", tname, (unsigned long long)d->d_un.d_val);
                    }
                } else {
                    printf("  0x%016llx  0x%016llx\n", (unsigned long long)d->d_tag, (unsigned long long)d->d_un.d_val);
                }
            }
        } else {
            size_t n = (size_t)dsz / sizeof(Elf32_Dyn);
            for (size_t i = 0; i < n; ++i) {
                auto* d = buf.at<Elf32_Dyn>((size_t)doff + i * sizeof(Elf32_Dyn));
                if (!d || d->d_tag == 0) break;
                const char* tname = elf_dyn_tag_str(d->d_tag);
                if (tname) {
                    if (d->d_tag == 1 || d->d_tag == 14 || d->d_tag == 15 || d->d_tag == 29) {
                        const char* s = dynstrtab_off ? buf.str((size_t)dynstrtab_off + d->d_un.d_val) : "";
                        printf("  %-16s  0x%08x  \"%s\"\n", tname, d->d_un.d_val, s);
                    } else {
                        printf("  %-16s  0x%08x\n", tname, d->d_un.d_val);
                    }
                } else {
                    printf("  0x%08x  0x%08x\n", (uint32_t)d->d_tag, d->d_un.d_val);
                }
            }
        }
    }

    // --- Symbol tables: .dynsym and .symtab ---
    for (int pass = 0; pass < 2; ++pass) {
        const char* secname = (pass == 0) ? ".dynsym" : ".symtab";
        uint16_t sym_idx = find_sec_by_name(secname);
        if (sym_idx == 0xFFFF) continue;

        uint64_t sym_off = get_sh_offset(sym_idx);
        uint64_t sym_sz  = get_sh_size(sym_idx);
        uint16_t str_idx = (uint16_t)get_sh_link(sym_idx);
        uint64_t strtab_off = (str_idx < e_shnum) ? get_sh_offset(str_idx) : 0;

        size_t sym_entsz = is64 ? sizeof(Elf64_Sym) : sizeof(Elf32_Sym);
        size_t n = (size_t)sym_sz / sym_entsz;
        printf("\n[%s] %zu symbols\n", secname, n);
        printf("  %4s  %-8s  %-10s  %-8s  %-7s  %-8s  %s\n",
               "Idx","Value","Size","Binding","Type","SHndx","Name");

        for (size_t i = 0; i < n; ++i) {
            if (is64) {
                auto* sym = buf.at<Elf64_Sym>((size_t)sym_off + i * sizeof(Elf64_Sym));
                if (!sym) break;
                const char* sname = strtab_off ? buf.str((size_t)strtab_off + sym->st_name) : "";
                printf("  %4zu  %016llx  0x%08llx  %-8s  %-7s  %-8u  %s\n",
                       i, (unsigned long long)sym->st_value, (unsigned long long)sym->st_size,
                       elf_sym_binding(sym->st_info), elf_sym_type(sym->st_info),
                       sym->st_shndx, sname);
            } else {
                auto* sym = buf.at<Elf32_Sym>((size_t)sym_off + i * sizeof(Elf32_Sym));
                if (!sym) break;
                const char* sname = strtab_off ? buf.str((size_t)strtab_off + sym->st_name) : "";
                printf("  %4zu  %08x  0x%08x  %-8s  %-7s  %-8u  %s\n",
                       i, sym->st_value, sym->st_size,
                       elf_sym_binding(sym->st_info), elf_sym_type(sym->st_info),
                       sym->st_shndx, sname);
            }
        }
    }

    // --- Relocations (all REL/RELA sections) ---
    printf("\n[Relocations]\n");
    for (uint16_t i = 0; i < e_shnum; ++i) {
        uint32_t stype = get_sh_type(i);
        if (stype != 4 && stype != 9) continue; // RELA=4 REL=9
        bool is_rela = (stype == 4);
        uint64_t roff = get_sh_offset(i);
        uint64_t rsz  = get_sh_size(i);
        uint16_t sym_link = (uint16_t)get_sh_link(i);
        uint16_t target_idx = (uint16_t)get_sh_info(i);
        uint64_t symtab_off = (sym_link < e_shnum) ? get_sh_offset(sym_link) : 0;
        uint16_t stridx = (sym_link < e_shnum) ? (uint16_t)get_sh_link(sym_link) : 0xFFFF;
        uint64_t strtab_off = (stridx < e_shnum) ? get_sh_offset(stridx) : 0;

        printf("  Section: %s -> %s\n", sh_name(i), sh_name(target_idx));
        printf("    %-18s  %-24s  %-10s  %s\n", "Offset","Type","Addend","Symbol");

        if (is64) {
            size_t entsz = is_rela ? sizeof(Elf64_Rela) : sizeof(Elf64_Rel);
            size_t n = (size_t)rsz / entsz;
            for (size_t j = 0; j < n; ++j) {
                uint64_t r_offset, r_info;
                int64_t  r_addend = 0;
                if (is_rela) {
                    auto* r = buf.at<Elf64_Rela>((size_t)roff + j * entsz);
                    if (!r) break;
                    r_offset = r->r_offset; r_info = r->r_info; r_addend = r->r_addend;
                } else {
                    auto* r = buf.at<Elf64_Rel>((size_t)roff + j * entsz);
                    if (!r) break;
                    r_offset = r->r_offset; r_info = r->r_info;
                }
                uint32_t sym_idx2  = (uint32_t)(r_info >> 32);
                uint32_t rel_type = (uint32_t)(r_info & 0xFFFFFFFF);
                std::string sname;
                if (sym_idx2 && symtab_off) {
                    auto* sym = buf.at<Elf64_Sym>((size_t)symtab_off + sym_idx2 * sizeof(Elf64_Sym));
                    if (sym && strtab_off) sname = buf.str((size_t)strtab_off + sym->st_name);
                }
                printf("    0x%016llx  %-24s  %-10lld  %s\n",
                       (unsigned long long)r_offset,
                       elf_reloc_x64(rel_type),
                       (long long)r_addend,
                       sname.c_str());
            }
        } else {
            size_t entsz = is_rela ? sizeof(Elf32_Rela) : sizeof(Elf32_Rel);
            size_t n = (size_t)rsz / entsz;
            for (size_t j = 0; j < n; ++j) {
                uint32_t r_offset, r_info;
                int32_t  r_addend = 0;
                if (is_rela) {
                    auto* r = buf.at<Elf32_Rela>((size_t)roff + j * entsz);
                    if (!r) break;
                    r_offset = r->r_offset; r_info = r->r_info; r_addend = r->r_addend;
                } else {
                    auto* r = buf.at<Elf32_Rel>((size_t)roff + j * entsz);
                    if (!r) break;
                    r_offset = r->r_offset; r_info = r->r_info;
                }
                uint32_t sym_idx2  = r_info >> 8;
                uint32_t rel_type = r_info & 0xFF;
                std::string sname;
                if (sym_idx2 && symtab_off) {
                    auto* sym = buf.at<Elf32_Sym>((size_t)symtab_off + sym_idx2 * sizeof(Elf32_Sym));
                    if (sym && strtab_off) sname = buf.str((size_t)strtab_off + sym->st_name);
                }
                printf("    0x%08x  %-24s  %-10d  %s\n",
                       r_offset, elf_reloc_x64(rel_type), r_addend, sname.c_str());
            }
        }
    }

    printf("\n");
}

// ---------------------------------------------------------------------------
// Entry point
// ---------------------------------------------------------------------------
int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file> [file2 ...]\n", argv[0]);
        fprintf(stderr, "  Dumps PE/ELF (32/64-bit) headers, imports, exports, relocs, exceptions\n");
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        printf("\n======================================================\n");
        printf("File: %s\n", argv[i]);
        printf("======================================================\n");
        Buffer buf;
        if (!buf.load(argv[i])) continue;
        if (buf.size() < 4) { printf("File too small\n"); continue; }

        const uint8_t* magic = buf.data.data();
        if (magic[0] == 'M' && magic[1] == 'Z') {
            dump_pe(buf);
        } else if (magic[0] == 0x7f && magic[1] == 'E' && magic[2] == 'L' && magic[3] == 'F') {
            dump_elf(buf);
        } else {
            printf("Unknown format (magic: %02x %02x %02x %02x)\n",
                   magic[0], magic[1], magic[2], magic[3]);
        }
    }
    return 0;
}
