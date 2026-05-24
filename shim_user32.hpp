#pragma once
// user32 surface — included from shim.cpp.
//
// Char case conversion, OEM ↔ ANSI translation (UTF-8 pass-through here),
// `LoadString{A,W}` backed by PE resource directory parsing, plus the
// small remainder (MessageBeep, ExitWindowsEx).
//
// References from shim.cpp: utf8_to_wchar, wchar_to_utf8, g_image_base,
// g_pe_base.

extern "C" EXPORT LPSTR user32_CharLowerA(LPSTR s) {
  if( (uintptr_t)s < 0x10000u ) return (LPSTR)(uintptr_t)tolower((unsigned char)(uintptr_t)s);
  for(char* p=s; *p; p++) *p=(char)tolower((unsigned char)*p);
  return s;
}
extern "C" EXPORT LPWSTR user32_CharLowerW(LPWSTR s) {
  if( (uintptr_t)s < 0x10000u ) return (LPWSTR)(uintptr_t)towlower((wchar_t)(uintptr_t)s);
  for(uint16_t* p=(uint16_t*)s; *p; p++) *p=(uint16_t)towlower(*p);
  return s;
}
extern "C" EXPORT LPSTR user32_CharUpperA(LPSTR s) {
  if( (uintptr_t)s <= 0xFFFF ) return (LPSTR)(uintptr_t)toupper((int)(uintptr_t)s);
  for( LPSTR p = s; *p; ++p ) *p = (char)toupper((unsigned char)*p);
  return s;
}
extern "C" EXPORT LPWSTR user32_CharUpperW(LPWSTR s) {
  if( (uintptr_t)s < 0x10000u ) return (LPWSTR)(uintptr_t)towupper((wchar_t)(uintptr_t)s);
  for(uint16_t* p=(uint16_t*)s; *p; p++) *p=(uint16_t)towupper(*p);
  return s;
}
extern "C" EXPORT BOOL user32_CharToOemA(LPCSTR src, LPSTR dst) {
  if(src&&dst) { size_t n=strlen(src)+1; memmove(dst,src,n); } return TRUE;
}
extern "C" EXPORT BOOL user32_CharToOemBuffA(LPCSTR src, LPSTR dst, DWORD len) {
  if(src&&dst) memmove(dst,src,len); return TRUE;
}
extern "C" EXPORT BOOL user32_CharToOemBuffW(const uint16_t* src, LPSTR dst, DWORD len) {
  if(!src||!dst) return FALSE;
  char utf8[65536]; wchar_to_utf8(src, utf8, sizeof(utf8));
  size_t n=strlen(utf8); if(n>len)n=len; memcpy(dst,utf8,n); return TRUE;
}
extern "C" EXPORT BOOL user32_CharToOemW(const uint16_t* src, LPSTR dst) {
  if(!src||!dst) return TRUE;
  char utf8[65536]; wchar_to_utf8(src, utf8, sizeof(utf8));
  strcpy(dst, utf8); return TRUE;
}
extern "C" EXPORT BOOL user32_OemToCharA(LPCSTR src, LPSTR dst) {
  return user32_CharToOemA(src, dst);
}
extern "C" EXPORT BOOL user32_OemToCharW(LPCSTR src, uint16_t* dst) {
  if(!src||!dst) return TRUE;
  utf8_to_wchar(src, dst, 65536); return TRUE;
}
extern "C" EXPORT BOOL user32_OemToCharBuffA(LPCSTR src, LPSTR dst, DWORD len) {
  return user32_CharToOemBuffA(src, dst, len);
}
extern "C" EXPORT BOOL user32_OemToCharBuffW(LPCSTR src, uint16_t* dst, DWORD len) {
  if(!src||!dst) return TRUE;
  utf8_to_wchar(src, dst, (size_t)len); return TRUE;
}
extern "C" EXPORT BOOL user32_ExitWindowsEx(UINT /*flags*/, DWORD /*reason*/) {
  _exit(0); return TRUE;
}

// ---------------------------------------------------------------------------
// Resource directory parsing for LoadStringA/W
// ---------------------------------------------------------------------------
struct ResDir    { uint32_t Chars,TS; uint16_t Maj,Min,Named,Id; };
struct ResDirEnt { uint32_t Name, Offset; };
struct ResData   { uint32_t RVA,Size,CodePage,Res; };

static const uint8_t* res_find_id(const uint8_t* rsrc, uint32_t rsrc_size,
                                   uint32_t dir_off, uint16_t id) {
  if( dir_off + sizeof(ResDir) > rsrc_size ) return nullptr;
  const ResDir*    dir = (const ResDir*)(rsrc + dir_off);
  uint32_t n = dir->Named + dir->Id;
  uint32_t ent_off = dir_off + (uint32_t)sizeof(ResDir);
  if( ent_off + n * (uint32_t)sizeof(ResDirEnt) > rsrc_size ) return nullptr;
  const ResDirEnt* ent = (const ResDirEnt*)(rsrc + ent_off);
  for( uint32_t i = 0; i < n; ++i ) {
    if( !(ent[i].Name >> 31) && (uint16_t)ent[i].Name == id ) {
      uint32_t off = ent[i].Offset & 0x7FFFFFFFu;
      if( off >= rsrc_size ) return nullptr;
      return rsrc + off;
    }
  }
  return nullptr;
}


static int load_string_impl(const void* hmod, UINT id, char* bufA, uint16_t* bufW, int bufmax) {
  const uint8_t* base = (const uint8_t*)hmod;
  // Treat NULL or sentinel values (< 64 KiB, e.g. FAKE_WIN_MODULE) as "current image"
  if( !base || (uintptr_t)base < 0x10000u ) base = (const uint8_t*)g_image_base;
  if( !base ) return 0;
  // If base doesn't point to a PE header, try the known PE base
  if( *(uint16_t*)base != 0x5A4D ) {
    if( g_pe_base ) base = (const uint8_t*)g_pe_base;
    else return 0;
  }
  // Parse PE header to get resource RVA
  if( *(uint16_t*)base != 0x5A4D ) return 0;
  uint32_t pe_off = *(uint32_t*)(base + 60);
  if( *(uint32_t*)(base + pe_off) != 0x00004550u ) return 0;
  const uint8_t* opt = base + pe_off + 24;
  if( *(uint16_t*)opt != 0x020B ) return 0;
  uint32_t rsrc_rva  = *(uint32_t*)(opt + 112 + 16);
  uint32_t rsrc_size = *(uint32_t*)(opt + 112 + 20);
  if( !rsrc_rva || !rsrc_size ) return 0;
  const uint8_t* rsrc     = base + rsrc_rva;
  const uint8_t* rsrc_end = rsrc + rsrc_size;
  // Level 1: RT_STRING = 6
  const uint8_t* l2ptr = res_find_id(rsrc, rsrc_size, 0, 6);
  if( !l2ptr ) return 0;
  uint16_t block = (uint16_t)(id / 16 + 1);
  const uint8_t* l3ptr = res_find_id(rsrc, rsrc_size, (uint32_t)(l2ptr - rsrc), block);
  if( !l3ptr ) return 0;
  // Level 3: take first language
  if( l3ptr + sizeof(ResDir) + sizeof(ResDirEnt) > rsrc_end ) return 0;
  const ResDir*    ld  = (const ResDir*)l3ptr;
  if( ld->Named + ld->Id == 0 ) return 0;
  const ResDirEnt* le  = (const ResDirEnt*)(ld + 1);
  uint32_t data_off = le[0].Offset & 0x7FFFFFFFu;
  if( data_off + sizeof(ResData) > rsrc_size ) return 0;
  const ResData*   rd  = (const ResData*)(rsrc + data_off);
  if( rd->RVA < rsrc_rva || rd->RVA - rsrc_rva + rd->Size > rsrc_size ) return 0;
  const uint8_t* blk     = base + rd->RVA;
  const uint8_t* blk_end = blk + rd->Size;
  // Walk 16-entry block to find string at index (id % 16)
  int idx = id % 16;
  for( int i = 0; i < idx; ++i ) {
    if( blk + 2 > blk_end ) return 0;
    uint16_t slen = *(uint16_t*)blk;
    blk += 2 + slen * 2;
  }
  if( blk + 2 > blk_end ) return 0;
  uint16_t slen = *(uint16_t*)blk;
  blk += 2;
  if( blk + slen * 2 > blk_end ) slen = (uint16_t)((blk_end - blk) / 2);
  if( bufmax <= 0 ) return slen;
  int out = (slen < (uint16_t)(bufmax - 1)) ? slen : (bufmax - 1);
  if( bufW ) {
    const uint16_t* src = (const uint16_t*)blk;
    for( int i = 0; i < out; ++i ) bufW[i] = src[i];
    bufW[out] = 0;
  } else if( bufA ) {
    const uint16_t* src = (const uint16_t*)blk;
    for( int i = 0; i < out; ++i ) bufA[i] = (char)(src[i] < 256 ? src[i] : '?');
    bufA[out] = '\0';
  }
  return out;
}

extern "C" EXPORT int user32_LoadStringW(HANDLE hinst, UINT id, uint16_t* buf, int sz) {
  return load_string_impl(hinst, id, nullptr, buf, sz);
}
extern "C" EXPORT int user32_LoadStringA(HANDLE hinst, UINT id, LPSTR buf, int sz) {
  return load_string_impl(hinst, id, buf, nullptr, sz);
}
extern "C" EXPORT BOOL user32_MessageBeep(UINT /*type*/) { return TRUE; }
