#pragma once
#include <cstdint>

// ---------------------------------------------------------------------------
// PE structures — 32-bit (PE32, IMAGE_FILE_MACHINE_I386) variant
//
// The DOS header and the COFF file header are width-independent, so they are
// byte-for-byte identical to the ones in pe_types.hpp.  Everything that
// carries a pointer or a size_t-ish field changes width, and PE32 keeps the
// `BaseOfData` field that PE32+ dropped (which shifts every later field by 4).
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
// IMAGE_OPTIONAL_HEADER32.  Magic == 0x10B.  Note BaseOfData (absent in
// PE32+) and the four 32-bit stack/heap fields; the data directory array
// therefore starts at opt_off + 96, not opt_off + 112.
struct pe32_optional_header {
  uint16_t Magic;
  uint8_t  MajorLinkerVersion;
  uint8_t  MinorLinkerVersion;
  uint32_t SizeOfCode;
  uint32_t SizeOfInitializedData;
  uint32_t SizeOfUninitializedData;
  uint32_t AddressOfEntryPoint;
  uint32_t BaseOfCode;
  uint32_t BaseOfData;              // PE32-only
  uint32_t ImageBase;               // 32-bit (default 0x400000)
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
// PE32+ optional header — only needed so OrdinalResolver can read the export
// table of a 64-bit side DLL if one is dropped in by mistake.
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
// IMAGE_EXPORT_DIRECTORY — used to resolve ordinal imports against a side
// copy of the matching DLL kept under dll32/<name>.dll.
struct pe_export {
  uint32_t Characteristics;
  uint32_t TimeDateStamp;
  uint16_t MajorVersion;
  uint16_t MinorVersion;
  uint32_t NameRVA;
  uint32_t OrdinalBase;
  uint32_t NumberOfFunctions;
  uint32_t NumberOfNames;
  uint32_t FunctionsRVA;        // array of NumberOfFunctions function RVAs
  uint32_t NamesRVA;            // array of NumberOfNames name string RVAs
  uint32_t NameOrdinalsRVA;     // array of NumberOfNames WORD indexes into FunctionsRVA
};
#pragma pack(pop)

static_assert(sizeof(pe32_optional_header) == 96, "pe32_optional_header size");

// PE machine types
static const uint16_t PE_MACHINE_I386 = 0x14C;

// PE section characteristics
static const uint32_t PE_SCN_MEM_EXECUTE = 0x20000000;
static const uint32_t PE_SCN_MEM_READ    = 0x40000000;
static const uint32_t PE_SCN_MEM_WRITE   = 0x80000000;

// Data directory indices
static const uint32_t PE_DD_EXPORT    = 0;
static const uint32_t PE_DD_IMPORT    = 1;
static const uint32_t PE_DD_BASERELOC = 5;
static const uint32_t PE_DD_TLS       = 9;

// Base relocation types.  32-bit images use HIGHLOW (a whole 32-bit fixup);
// DIR64 is the x64 equivalent and never appears in a PE32 image.
static const uint8_t PE_REL_BASED_ABSOLUTE = 0;
static const uint8_t PE_REL_BASED_HIGHLOW  = 3;

#pragma pack(push, 1)
// IMAGE_TLS_DIRECTORY32 — 24 bytes (the 64-bit form is 40).
struct pe_tls32 {
  uint32_t StartAddressOfRawData;
  uint32_t EndAddressOfRawData;
  uint32_t AddressOfIndex;
  uint32_t AddressOfCallBacks;
  uint32_t SizeOfZeroFill;
  uint32_t Characteristics;
};
#pragma pack(pop)

static_assert(sizeof(pe_tls32) == 24, "pe_tls32 size");

#pragma pack(push, 1)
struct pe_base_reloc {
  uint32_t VirtualAddress;
  uint32_t SizeOfBlock;
};
#pragma pack(pop)
