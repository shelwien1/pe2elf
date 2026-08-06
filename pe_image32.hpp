#pragma once
#include "util.hpp"
#include "pe_types32.hpp"
#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

// ---------------------------------------------------------------------------
// PE RVA → file offset map
// ---------------------------------------------------------------------------
struct PESectionMap {
  struct Entry {
    uint32_t va, raw, rawsz, virtsz;
    uint32_t characteristics;
    char name[9];
    std::string name_str; // resolved name (handles /N long-name form)
    uint64_t elf_foff;    // filled in by layout pass
  };
  std::vector<Entry> secs;

  // Returns file offset, or empty if RVA not in any section.
  // Returning std::optional avoids confusing "not found" with offset 0.
  std::optional<uint32_t> rva_to_offset(uint32_t rva) const {
    for( auto &e : secs ) {
      uint32_t end = e.va+std::max(e.virtsz, e.rawsz);
      if( rva>=e.va&&rva<end ) {
        uint32_t delta = rva-e.va;
        if( delta<e.rawsz )
          return e.raw+delta;
      }
    }
    return std::nullopt;
  }

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
// Base relocation record.
//
// Unlike the 64-bit tool there is no addend field: i386 relocations are REL,
// so the loader reads the addend straight out of the target.  The PE bytes at
// the site already hold the absolute preferred VA, which is exactly the
// addend R_386_RELATIVE wants, so we leave them alone and only record where
// the site is.
// ---------------------------------------------------------------------------
struct BaseRelocEntry {
  uint64_t va;      // absolute VA of the pointer in the loaded image
};

// ---------------------------------------------------------------------------
// Import record
// ---------------------------------------------------------------------------
struct ImportEntry {
  std::string dll_name;
  std::string func_name;
  uint32_t iat_rva;   // RVA of the IAT slot (4 bytes on PE32)
  uint32_t sym_index; // index into .dynsym (assigned later)
};

// ---------------------------------------------------------------------------
// Ordinal-import resolver: parses a DLL's export table to map an ordinal
// to the function name that DLL would have advertised for that slot.  PE
// files can import either by name or by ordinal; the shim only exposes
// named entries, so every ordinal import has to be translated.  We don't
// ship the real Windows DLLs — the caller drops the relevant ones under
// dll32/<lowercase-name>.dll in the repo and we parse just their exports.
// The directory is separate from the 64-bit tool's dll/ because a 32-bit
// DLL exports a different ordinal→name mapping than its 64-bit sibling.
// ---------------------------------------------------------------------------
struct OrdinalResolver {
  Buffer buf;
  PESectionMap secmap;
  uint32_t ordinal_base = 0;
  // function-index → name; absent entries are ordinal-only exports.
  std::unordered_map<uint32_t, std::string> ord_to_name;
  bool loaded = false;

  bool load(const std::string& dll_name) {
    std::string base;
    for( char c : dll_name )
      base.push_back((char)tolower((unsigned char)c));
    std::string path = "dll32/" + base;
    if( !buf.load(path.c_str()) ) {
      if( base.size()<4 || base.substr(base.size()-4)!=".dll" ) {
        path = "dll32/" + base + ".dll";
        if( !buf.load(path.c_str()) )
          return false;
      } else {
        return false;
      }
    }

    auto* dos = buf.at<pe_dos_header>(0);
    if( !dos || dos->Magic!=0x5A4D ) return false;
    size_t pe_off = dos->AddressOfNewExeHeader;
    auto* peh = buf.at<pe_header>(pe_off);
    if( !peh || memcmp(peh->signature, "PE\0\0", 4)!=0 ) return false;
    size_t opt_off = pe_off+sizeof(pe_header);
    auto* magic_p = buf.at<uint16_t>(opt_off);
    if( !magic_p ) return false;
    // PE32 and PE32+ differ in optional-header layout but both put the
    // section table at peh->SizeOfOptionalHeader.
    size_t dd_off;
    uint32_t num_dd;
    if( *magic_p==0x10B ) {
      auto* oh = buf.at<pe32_optional_header>(opt_off);
      if( !oh ) return false;
      num_dd = oh->NumberOfRvaAndSize;
      dd_off = opt_off+sizeof(pe32_optional_header);
    } else if( *magic_p==0x20B ) {
      auto* oh = buf.at<pe64_optional_header>(opt_off);
      if( !oh ) return false;
      num_dd = oh->NumberOfRvaAndSize;
      dd_off = opt_off+sizeof(pe64_optional_header);
    } else {
      return false;
    }
    if( num_dd<=PE_DD_EXPORT ) return false;

    size_t sec_off = pe_off+sizeof(pe_header)+peh->SizeOfOptionalHeader;
    for( uint32_t i = 0; i<peh->NumberOfSections; ++i ) {
      auto* s = buf.at<pe_section>(sec_off+i*sizeof(pe_section));
      if( !s ) break;
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

    auto* exp_dd = buf.at<pe_data_directory>(dd_off+PE_DD_EXPORT*sizeof(pe_data_directory));
    if( !exp_dd || !exp_dd->RelativeVirtualAddress ) return false;
    auto exp_off = secmap.rva_to_offset(exp_dd->RelativeVirtualAddress);
    if( !exp_off ) return false;
    auto* exp = buf.at<pe_export>(*exp_off);
    if( !exp ) return false;
    ordinal_base = exp->OrdinalBase;

    auto names_off = secmap.rva_to_offset(exp->NamesRVA);
    auto ords_off  = secmap.rva_to_offset(exp->NameOrdinalsRVA);
    if( !names_off || !ords_off ) return false;
    for( uint32_t j = 0; j<exp->NumberOfNames; ++j ) {
      auto* name_rva = buf.at<uint32_t>(*names_off + j*4);
      auto* fn_idx   = buf.at<uint16_t>(*ords_off  + j*2);
      if( !name_rva || !fn_idx ) continue;
      auto name_str_off = secmap.rva_to_offset(*name_rva);
      if( !name_str_off ) continue;
      ord_to_name[*fn_idx] = buf.str(*name_str_off);
    }
    loaded = true;
    return true;
  }

  std::string resolve(uint16_t ordinal) const {
    if( !loaded || ordinal<ordinal_base ) return "";
    auto it = ord_to_name.find(ordinal-ordinal_base);
    return it==ord_to_name.end() ? std::string{} : it->second;
  }
};

inline std::string resolve_ordinal_import(const std::string& dll_name, uint16_t ordinal) {
  // Process-wide cache so we parse each dll32/<x> at most once.
  static std::map<std::string, OrdinalResolver> cache;
  auto it = cache.find(dll_name);
  if( it==cache.end() ) {
    OrdinalResolver r;
    r.load(dll_name);  // ignore failure; resolve() returns "" then
    it = cache.emplace(dll_name, std::move(r)).first;
  }
  return it->second.resolve(ordinal);
}

// ---------------------------------------------------------------------------
// Parsed PE32 image (input data + section map + imports)
// ---------------------------------------------------------------------------
struct PeImage {
  Buffer buf;
  const pe_dos_header*        dos = nullptr;
  const pe_header*            peh = nullptr;
  const pe32_optional_header*  oh = nullptr;
  size_t   dd_off = 0;
  uint32_t num_dd = 0;
  PESectionMap secmap;
  std::vector<ImportEntry>    imports;
  std::vector<BaseRelocEntry> relocs;
  // 32-bit values widened to 64 bits internally so all the layout arithmetic
  // stays in one type and can't wrap silently.
  uint64_t image_base = 0;
  uint32_t ep_rva = 0;
  int rdata_sec_idx = -1; // index of section holding IAT (usually .rdata)

  // TLS directory (IMAGE_TLS_DIRECTORY32), zeros if no TLS directory present
  uint64_t tls_template_va  = 0; // StartAddressOfRawData
  uint64_t tls_template_sz  = 0; // EndAddressOfRawData - Start
  uint64_t tls_zero_fill    = 0; // SizeOfZeroFill
  uint64_t tls_align_chars  = 0; // Characteristics
  uint64_t tls_index_va     = 0; // AddressOfIndex
  uint64_t tls_callbacks_va = 0; // AddressOfCallBacks

  bool parse(const char* path) {
    if( !buf.load(path) )
      return false;

    dos = buf.at<pe_dos_header>(0);
    if( !dos||dos->Magic!=0x5A4D ) {
      fprintf(stderr, "Not a valid PE (bad DOS magic)\n");
      return false;
    }
    size_t pe_off = dos->AddressOfNewExeHeader;
    peh = buf.at<pe_header>(pe_off);
    if( !peh||memcmp(peh->signature, "PE\0\0", 4)!=0 ) {
      fprintf(stderr, "Bad PE signature\n");
      return false;
    }
    if( peh->Machine!=PE_MACHINE_I386 ) {
      fprintf(stderr, "Not i386 PE (machine=0x%04x)\n", peh->Machine);
      return false;
    }
    size_t opt_off = pe_off+sizeof(pe_header);
    auto* magic_p = buf.at<uint16_t>(opt_off);
    if( !magic_p||*magic_p!=0x10B ) {
      fprintf(stderr, "Not PE32 (magic=0x%04x)\n", magic_p ? *magic_p : 0);
      return false;
    }
    oh = buf.at<pe32_optional_header>(opt_off);
    if( !oh ) {
      fprintf(stderr, "Cannot read PE32 optional header\n");
      return false;
    }
    image_base = oh->ImageBase;
    ep_rva = oh->AddressOfEntryPoint;
    num_dd = oh->NumberOfRvaAndSize;
    if( num_dd>96 ) {
      fprintf(stderr, "NumberOfRvaAndSize %u exceeds limit (96)\n", num_dd);
      return false;
    }
    if( peh->NumberOfSections>96 ) {
      fprintf(stderr, "NumberOfSections %u exceeds limit (96)\n", peh->NumberOfSections);
      return false;
    }
    dd_off = opt_off+sizeof(pe32_optional_header);
    if( dd_off+num_dd*sizeof(pe_data_directory)>buf.size() ) {
      fprintf(stderr, "Data directory array extends past end of file\n");
      return false;
    }

    // Use SizeOfOptionalHeader (spec-correct) for section-table base
    size_t sec_off = pe_off+sizeof(pe_header)+peh->SizeOfOptionalHeader;
    for( uint32_t i = 0; i<peh->NumberOfSections; ++i ) {
      auto* s = buf.at<pe_section>(sec_off+i*sizeof(pe_section));
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
      // Resolve /N long-name form via COFF string table
      if( e.name[0]=='/' && e.name[1]>='0' && e.name[1]<='9' ) {
        uint64_t name_off = strtoull(e.name+1, nullptr, 10);
        uint64_t strtab = (uint64_t)peh->PointerToSymbolTable + (uint64_t)peh->NumberOfSymbols * 18;
        uint64_t str_off = strtab + name_off;
        if( peh->PointerToSymbolTable && str_off < buf.size() ) {
          const char* p = (const char*)buf.data.data()+str_off;
          size_t max_len = buf.size()-(size_t)str_off;
          size_t len = strnlen(p, std::min(max_len, (size_t)255));
          e.name_str = std::string(p, len);
        }
      }
      if( e.name_str.empty() ) {
        e.name_str = e.name;
        if( e.name_str.empty() ) e.name_str = ".pe_sec";
      }
      secmap.secs.push_back(e);
    }
    return true;
  }

  bool collect_imports() {
    if( num_dd<=PE_DD_IMPORT )
      return true;
    auto* imp_dd = buf.at<pe_data_directory>(dd_off+PE_DD_IMPORT*sizeof(pe_data_directory));
    if( !imp_dd||!imp_dd->RelativeVirtualAddress )
      return true;

    auto imp_base = secmap.rva_to_offset(imp_dd->RelativeVirtualAddress);
    if( !imp_base ) {
      fprintf(stderr, "Import directory RVA does not map to any section\n");
      return false;
    }
    uint32_t imp_off = *imp_base;

    for( uint32_t idx = 0; idx<4096; ++idx ) {
      auto* imp = buf.at<pe_import>(imp_off+idx*sizeof(pe_import));
      if( !imp )
        break;
      if( !imp->NameRVA&&!imp->ImportLookupTableRVA&&!imp->ImportAddressTableRVA )
        break;

      auto name_off_opt = imp->NameRVA ? secmap.rva_to_offset(imp->NameRVA)
                                        : std::optional<uint32_t>{};
      if( !name_off_opt ) {
        fprintf(stderr, "Warning: import descriptor has invalid NameRVA 0x%x; skipping\n",
                imp->NameRVA);
        continue;
      }
      uint32_t name_off = *name_off_opt;
      std::string dll_name;
      for( size_t k = name_off; k<buf.size()&&k-name_off<256; ++k ) {
        if( buf.data[k]==0 ) break;
        dll_name.push_back((char)buf.data[k]);
      }

      uint32_t iat_rva = imp->ImportAddressTableRVA;
      if( !iat_rva ) {
        fprintf(stderr, "Warning: import descriptor for '%s' has zero IAT RVA; skipping\n",
                dll_name.c_str());
        continue;
      }

      uint32_t ilt_rva = imp->ImportLookupTableRVA ? imp->ImportLookupTableRVA : iat_rva;
      auto ilt_off_opt = secmap.rva_to_offset(ilt_rva);
      if( !ilt_off_opt )
        continue;
      uint32_t ilt_off = *ilt_off_opt;

      // PE32 ILT/IAT entries are 4 bytes; ordinal flag is bit 31.
      for( uint32_t j = 0; j < 65536; ++j ) {
        auto* entry = buf.at<uint32_t>(ilt_off+j*4);
        if( !entry||*entry==0 )
          break;
        uint32_t v = *entry;
        uint32_t slot_rva = iat_rva+j*4;
        if( secmap.section_of(slot_rva)<0 ) {
          fprintf(stderr, "Warning: IAT slot RVA 0x%x not in any section; skipping\n", slot_rva);
          continue;
        }
        if( v&0x80000000u ) {
          // Import by ordinal — translate to the function name that the
          // exporting DLL would have advertised for that slot, so we can
          // route it to our shim like any named import.  The matching
          // 32-bit DLL file has to be present under dll32/.
          uint16_t ordinal = (uint16_t)(v&0xFFFF);
          std::string fname = resolve_ordinal_import(dll_name, ordinal);
          if( fname.empty() ) {
            fprintf(stderr, "Error: cannot resolve ordinal import (DLL '%s' ordinal %u)"
                            " — put a matching dll32/%s file alongside the binary\n",
                    dll_name.c_str(), ordinal, dll_name.c_str());
            return false;
          }
          ImportEntry ie;
          ie.dll_name = dll_name;
          ie.func_name = fname;
          ie.iat_rva = slot_rva;
          ie.sym_index = 0;
          imports.push_back(ie);
        } else {
          auto hint_off_opt = secmap.rva_to_offset(v&0x7FFFFFFFu);
          if( hint_off_opt && *hint_off_opt+2<buf.size() ) {
            uint32_t hint_off = *hint_off_opt;
            std::string fname = buf.str(hint_off+2);
            ImportEntry ie;
            ie.dll_name = dll_name;
            ie.func_name = fname;
            ie.iat_rva = slot_rva;
            ie.sym_index = 0;
            imports.push_back(ie);
          }
        }
      }
    }

    // Identify which section holds the IAT; error on split layout
    if( !imports.empty() ) {
      rdata_sec_idx = secmap.section_of(imports[0].iat_rva);
      for( auto &ie : imports ) {
        if( secmap.section_of(ie.iat_rva)!=rdata_sec_idx ) {
          fprintf(stderr, "Error: split IAT layout (IAT spans multiple sections) is not supported\n");
          return false;
        }
      }
    }

    return true;
  }

  bool collect_relocs() {
    if( num_dd<=PE_DD_BASERELOC )
      return true;
    auto* rel_dd = buf.at<pe_data_directory>(dd_off+PE_DD_BASERELOC*sizeof(pe_data_directory));
    if( !rel_dd||!rel_dd->RelativeVirtualAddress )
      return true;

    auto off_opt = secmap.rva_to_offset(rel_dd->RelativeVirtualAddress);
    if( !off_opt ) {
      fprintf(stderr, "Base reloc directory RVA does not map to any section\n");
      return false;
    }

    // Build set of IAT VAs so we can skip them (handled by R_386_32)
    auto is_iat = [&](uint64_t va) {
      for( auto& ie : imports )
        if( image_base+(uint64_t)ie.iat_rva==va ) return true;
      return false;
    };

    uint32_t cur_off = *off_opt;
    uint64_t end_off_u64 = (uint64_t)cur_off + rel_dd->Size;
    if( end_off_u64 < cur_off ) {
      fprintf(stderr, "Warning: base reloc Size overflows uint32_t; skipping relocations\n");
      return true;
    }
    uint32_t end_off = end_off_u64 > buf.size() ? (uint32_t)buf.size() : (uint32_t)end_off_u64;

    while( cur_off+sizeof(pe_base_reloc)<=end_off ) {
      auto* blk = buf.at<pe_base_reloc>(cur_off);
      if( !blk||blk->SizeOfBlock<8||
          (blk->VirtualAddress==0&&blk->SizeOfBlock==0) )
        break;

      uint32_t n_entries = (blk->SizeOfBlock-8)/2;
      for( uint32_t i = 0; i<n_entries; ++i ) {
        auto* ep = buf.at<uint16_t>(cur_off+8+i*2);
        if( !ep ) break;
        uint16_t entry = *ep;
        uint8_t  type  = entry>>12;
        uint32_t rva   = blk->VirtualAddress+(entry&0xFFF);

        if( type==PE_REL_BASED_HIGHLOW ) {
          auto data_off_opt = secmap.rva_to_offset(rva);
          if( !data_off_opt ) {
            fprintf(stderr,
                    "Warning: base reloc RVA 0x%x not in any section; skipping\n", rva);
            continue;
          }
          // Bounds-check the 4-byte site even though we don't read it: an
          // R_386_RELATIVE against bytes that fall outside the emitted
          // section would have the loader write into nothing.
          if( !buf.at<uint32_t>(*data_off_opt) ) {
            fprintf(stderr,
                    "Warning: base reloc at file offset 0x%x out of bounds; skipping\n",
                    *data_off_opt);
            continue;
          }
          uint64_t va = image_base+rva;
          if( !is_iat(va) ) {
            BaseRelocEntry re;
            re.va = va;
            relocs.push_back(re);
          }
        } else if( type!=PE_REL_BASED_ABSOLUTE ) { // type 0 = padding entry
          fprintf(stderr,
                  "Warning: unsupported base reloc type %u at RVA 0x%x; skipping\n",
                  type, rva);
        }
      }
      cur_off += blk->SizeOfBlock;
    }
    return true;
  }

  bool collect_tls() {
    if( num_dd <= PE_DD_TLS ) return true;
    auto* tls_dd = buf.at<pe_data_directory>(dd_off + PE_DD_TLS * sizeof(pe_data_directory));
    if( !tls_dd || !tls_dd->RelativeVirtualAddress ) return true;
    auto off_opt = secmap.rva_to_offset(tls_dd->RelativeVirtualAddress);
    if( !off_opt ) {
      fprintf(stderr, "Warning: TLS directory RVA does not map to any section; skipping\n");
      return true;
    }
    auto* tls = buf.at<pe_tls32>(*off_opt);
    if( !tls ) {
      fprintf(stderr, "Warning: TLS directory extends past end of file; skipping\n");
      return true;
    }
    tls_template_va  = tls->StartAddressOfRawData;
    tls_template_sz  = (tls->EndAddressOfRawData > tls->StartAddressOfRawData)
                       ? (uint64_t)(tls->EndAddressOfRawData - tls->StartAddressOfRawData) : 0;
    tls_zero_fill    = tls->SizeOfZeroFill;
    tls_align_chars  = tls->Characteristics;
    tls_index_va     = tls->AddressOfIndex;
    tls_callbacks_va = tls->AddressOfCallBacks;
    printf("TLS: template VA=0x%llx sz=%llu zero_fill=%u index_va=0x%llx callbacks_va=0x%llx\n",
           (unsigned long long)tls_template_va, (unsigned long long)tls_template_sz,
           (unsigned)tls_zero_fill,
           (unsigned long long)tls_index_va, (unsigned long long)tls_callbacks_va);
    return true;
  }

  // Apply a new image base in-place: patches every reloc site in buf.data,
  // updates image_base, then clears relocs (applied; no ELF relocs needed).
  // If new_base == image_base the relocs are still cleared (caller asked for
  // a no-ELF-relocs output at the original base).
  bool rebase(uint64_t new_base) {
    if( new_base==image_base ) {
      relocs.clear();
      return true;
    }
    if( new_base > 0xFFFFFFFFULL ) {
      fprintf(stderr, "Error: rebase target 0x%llx does not fit in 32 bits\n",
              (unsigned long long)new_base);
      return false;
    }
    if( relocs.empty() ) {
      fprintf(stderr,
              "Error: cannot rebase 0x%llx → 0x%llx: "
              "no PE base relocations present in input\n",
              (unsigned long long)image_base, (unsigned long long)new_base);
      return false;
    }
    int64_t delta = (int64_t)(new_base-image_base);
    for( auto& re : relocs ) {
      uint32_t rva = (uint32_t)(re.va-image_base);
      auto off_opt = secmap.rva_to_offset(rva);
      if( !off_opt ) {
        fprintf(stderr,
                "Error: rebase: reloc RVA 0x%x maps to no section\n", rva);
        return false;
      }
      uint32_t off = *off_opt;
      if( off+4>(uint32_t)buf.data.size() ) {
        fprintf(stderr,
                "Error: rebase: reloc at file offset 0x%x out of bounds\n", off);
        return false;
      }
      uint32_t val;
      memcpy(&val, buf.data.data()+off, 4);
      val = (uint32_t)((int64_t)val+delta);
      memcpy(buf.data.data()+off, &val, 4);
      re.va = new_base + rva;
    }
    printf("Rebased 0x%llx → 0x%llx (delta %+lld), %u patches applied\n",
           (unsigned long long)image_base, (unsigned long long)new_base,
           (long long)delta, (uint32_t)relocs.size());
    image_base = new_base;
    relocs.clear();
    return true;
  }
};
