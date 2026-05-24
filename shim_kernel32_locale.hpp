#pragma once
// Locale and FormatMessage — included from shim.cpp.
//
// `GetLocaleInfo{A,W}` reports a tiny synthesised locale.
// `FormatMessageA` covers a fixed table of common Win32 error codes and
// supports Windows-style positional escapes (`%N!fmt!`).
//
// References from shim.cpp: utf8_to_wchar.

extern "C" EXPORT int kernel32_GetLocaleInfoA(DWORD locale, DWORD lctype, LPSTR buf, int size) {
  (void)locale;
  const char* val = "";
  switch( lctype&0xffff ) {
  case 0x0003: val = "1252";  break; // LOCALE_IDEFAULTANSICODEPAGE
  case 0x0005: val = "437";   break; // LOCALE_IDEFAULTCODEPAGE (OEM)
  case 0x0059: val = "en";    break; // LOCALE_SISO639LANGNAME
  case 0x005A: val = "US";    break; // LOCALE_SISO3166CTRYNAME
  case 0x1004: val = "UTF-8"; break; // LOCALE_IDEFAULTMACCODEPAGE
  default: break;
  }
  if( !buf||size==0 )
    return (int)strlen(val)+1;
  strncpy(buf, val, size-1);
  buf[size-1] = '\0';
  return (int)strlen(buf)+1;
}
extern "C" EXPORT int kernel32_GetLocaleInfoW(DWORD locale, DWORD lctype, uint16_t* buf, int size) {
  char tmp[64];
  int n = kernel32_GetLocaleInfoA(locale, lctype, tmp, sizeof(tmp));
  if( !buf || size == 0 ) return n;
  utf8_to_wchar(tmp, buf, (size_t)size);
  return n;
}

// Expand Windows positional escapes (%1!s! %2!d! etc.) from a va_list.
// Supports up to 9 positional args; reads them from args in declaration order.
static DWORD format_message_expand(const char* msg, LPSTR buf, DWORD size, va_list* args) {
  // Pre-fetch up to 9 args as void* — safe for s/d/u on x86-64 ABI
  void* argp[9] = {};
  va_list ap;
  if( args ) {
    va_copy(ap, *args);
    for( int i = 0; i<9; i++ )
      argp[i] = va_arg(ap, void*);
    va_end(ap);
  }
  DWORD out = 0;
  for( const char* p = msg; *p&&out<size-1; p++ ) {
    if( p[0]=='%'&&p[1]>='1'&&p[1]<='9' ) {
      int idx = p[1]-'1';
      p += 2;
      char fmt[16] = "s";
      if( *p=='!' ) {
        p++;
        int fi = 0;
        while( *p&&*p!='!'&&fi<(int)sizeof(fmt)-1 )
          fmt[fi++] = *p++;
        fmt[fi] = '\0';
        if( *p=='!' ) p++;
        p--; // compensate for outer loop increment
      } else {
        p--; // just %N with no !fmt!
      }
      char fmtbuf[20];
      fmtbuf[0] = '%';
      strncpy(fmtbuf+1, fmt, sizeof(fmtbuf)-2);
      fmtbuf[sizeof(fmtbuf)-1] = '\0';
      char sub[256];
      snprintf(sub, sizeof(sub), fmtbuf, argp[idx]);
      for( const char* s = sub; *s&&out<size-1; s++ )
        buf[out++] = *s;
    } else if( p[0]=='%'&&p[1]=='%' ) {
      buf[out++] = '%';
      p++;
    } else {
      buf[out++] = *p;
    }
  }
  buf[out] = '\0';
  return out;
}

extern "C" EXPORT DWORD kernel32_FormatMessageA(DWORD flags, LPCVOID src, DWORD msgId, DWORD lang, LPSTR buf, DWORD size, va_list* args) {
  (void)flags; (void)src; (void)lang;
  // Look up a few common Win32 codes; fall back to "Error N"
  static const struct { DWORD code; const char* msg; } table[] = {
    {0,   "The operation completed successfully."},
    {2,   "The system cannot find the file specified."},
    {3,   "The system cannot find the path specified."},
    {5,   "Access is denied."},
    {6,   "The handle is invalid."},
    {8,   "Not enough memory resources are available."},
    {18,  "There are no more files."},
    {87,  "The parameter is incorrect."},
    {183, "Cannot create a file when that file already exists."},
  };
  const char* msg = NULL;
  for( size_t i = 0; i<sizeof(table)/sizeof(table[0]); ++i ) {
    if( table[i].code==msgId ) { msg = table[i].msg; break; }
  }
  char fallback[64];
  if( !msg ) {
    snprintf(fallback, sizeof(fallback), "Error %u", (unsigned)msgId);
    msg = fallback;
  }
  if( !buf||size==0 )
    return 0;
  return format_message_expand(msg, buf, size, args);
}
