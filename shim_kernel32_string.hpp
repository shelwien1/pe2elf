#pragma once
// 7.13 String / Code Page — included from shim.cpp.
//
// References from shim.cpp: utf8_to_wchar, wchar_to_utf8.

// `GetACP()` reports the ANSI code page.  The MSVC CRT explicitly rejects
// UTF-7 (65000) and UTF-8 (65001) as "system" code pages in `setmbcp_nolock`
// (the `SystemCP - 65000 > 1` guard), so even though the shim handles UTF-8
// throughout, returning 65001 here crashes rar550a's startup multibyte
// init.  Return 1252 (Windows-1252, the standard Windows-x86-64 default).
extern "C" EXPORT DWORD kernel32_GetACP(void) {
  return 1252;
}

extern "C" EXPORT DWORD kernel32_GetOEMCP(void) {
  return 437;
}

extern "C" EXPORT BOOL kernel32_IsValidCodePage(DWORD cp) {
  return (cp==65001||cp==437||cp==1252) ? TRUE : FALSE;
}

extern "C" EXPORT BOOL kernel32_GetCPInfo(DWORD cp, CPINFO* info) {
  if( !info ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  info->MaxCharSize = (cp==65001) ? 4 : 2;
  info->DefaultChar[0] = '?';
  info->DefaultChar[1] = 0;
  memset(info->LeadByte, 0, sizeof(info->LeadByte));
  return TRUE;
}

// MultiByteToWideChar / WideCharToMultiByte, as Windows does them, with every
// code page taken as UTF-8 (the shim's narrow strings are UTF-8 throughout):
// - srclen -1: the string and its NUL, which the returned count includes;
//   srclen >= 0: exactly that much, nothing added;
// - dstlen 0: only the count; else the whole result has to fit
//   (ERROR_INSUFFICIENT_BUFFER, 0, if not);
// - what is not valid (bad UTF-8, a lone surrogate) becomes U+FFFD, or with
//   MB_ERR_INVALID_CHARS / WC_ERR_INVALID_CHARS fails, as for UTF-8 there.
extern "C" EXPORT int kernel32_MultiByteToWideChar(DWORD cp, DWORD flags, LPCSTR src, int srclen, LPWSTR dst, int dstlen) {
  (void)cp;
  if( !src || srclen==0 || dstlen<0 || (dstlen>0 && !dst) ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return 0;
  }
  const unsigned char* s = (const unsigned char*)src;
  const unsigned char* e = s+((srclen<0) ? strlen(src)+1 : (size_t)srclen);
  int n = 0;
  bool bad = false;
  while( s<e ) {
    uint32_t c;
    s += utf8_next(s, e, &c, &bad);
    if( bad && (flags&MB_ERR_INVALID_CHARS) ) { SET_LAST_ERROR(ERROR_NO_UNICODE_TRANSLATION); return 0; }
    int k = (c>=0x10000) ? 2 : 1;
    if( dstlen ) {
      if( n+k>dstlen ) { SET_LAST_ERROR(ERROR_INSUFFICIENT_BUFFER); return 0; }
      if( k==2 ) {
        c -= 0x10000;
        dst[n] = (uint16_t)(0xD800|(c>>10));
        dst[n+1] = (uint16_t)(0xDC00|(c&0x3FF));
      } else dst[n] = (uint16_t)c;
    }
    n += k;
  }
  return n;
}

extern "C" EXPORT int kernel32_WideCharToMultiByte(DWORD cp, DWORD flags, LPCWSTR src, int srclen, LPSTR dst, int dstlen, LPCSTR defch, BOOL* useddef) {
  (void)cp;
  (void)defch;
  if( useddef ) *useddef = FALSE;
  if( !src || srclen==0 || dstlen<0 || (dstlen>0 && !dst) ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return 0;
  }
  const uint16_t* s = src;
  const uint16_t* e = s;
  if( srclen<0 ) { while( *e ) ++e; ++e; } else e += srclen;
  int n = 0;
  while( s<e ) {
    uint32_t c = *s++;
    if( c>=0xD800 && c<=0xDBFF && s<e && *s>=0xDC00 && *s<=0xDFFF ) c = 0x10000+((c-0xD800)<<10)+(*s++-0xDC00);
    else if( c>=0xD800 && c<=0xDFFF ) {
      if( flags&WC_ERR_INVALID_CHARS ) { SET_LAST_ERROR(ERROR_NO_UNICODE_TRANSLATION); return 0; }
      c = 0xFFFD;
    }
    char b[4];
    int k;
    if( c<0x80 )         { b[0] = (char)c; k = 1; }
    else if( c<0x800 )   { b[0] = (char)(0xC0|(c>>6)); b[1] = (char)(0x80|(c&0x3F)); k = 2; }
    else if( c<0x10000 ) { b[0] = (char)(0xE0|(c>>12)); b[1] = (char)(0x80|((c>>6)&0x3F)); b[2] = (char)(0x80|(c&0x3F)); k = 3; }
    else { b[0] = (char)(0xF0|(c>>18)); b[1] = (char)(0x80|((c>>12)&0x3F)); b[2] = (char)(0x80|((c>>6)&0x3F)); b[3] = (char)(0x80|(c&0x3F)); k = 4; }
    if( dstlen ) {
      if( n+k>dstlen ) { SET_LAST_ERROR(ERROR_INSUFFICIENT_BUFFER); return 0; }
      memcpy(dst+n, b, (size_t)k);
    }
    n += k;
  }
  return n;
}

extern "C" EXPORT int kernel32_LCMapStringW(DWORD locale, DWORD flags, LPCWSTR src, int srclen, LPWSTR dst, int dstlen) {
  (void)locale;
  if( srclen<0 ) {
    // find length
    const uint16_t* p = src;
    srclen = 0;
    while( *p++ )
      srclen++;
    srclen++;
  }
  if( flags&LCMAP_UPPERCASE ) {
    if( dst&&dstlen>0 ) {
      int n = (srclen<dstlen) ? srclen : dstlen;
      for( int i = 0; i<n; ++i )
        dst[i] = (src[i]>='a'&&src[i]<='z') ? src[i]-32 : src[i];
    }
    return srclen;
  }
  if( flags&LCMAP_LOWERCASE ) {
    if( dst&&dstlen>0 ) {
      int n = (srclen<dstlen) ? srclen : dstlen;
      for( int i = 0; i<n; ++i )
        dst[i] = (src[i]>='A'&&src[i]<='Z') ? src[i]+32 : src[i];
    }
    return srclen;
  }
  // Unknown mapping — copy as-is
  if( dst&&dstlen>0 ) {
    int n = (srclen<dstlen) ? srclen : dstlen;
    memcpy(dst, src, (size_t)n*2);
  }
  return srclen;
}

static WORD classify_ctype1(unsigned int c) {
  // CT_CTYPE1 classification for the ASCII plane; non-ASCII gets C1_ALPHA
  if( c>127 ) return C1_ALPHA;
  unsigned char u = (unsigned char)c;
  WORD t = 0;
  if( isupper(u) ) t |= C1_UPPER|C1_ALPHA;
  if( islower(u) ) t |= C1_LOWER|C1_ALPHA;
  if( isdigit(u) ) t |= C1_DIGIT;
  if( isspace(u) ) t |= C1_SPACE;
  if( ispunct(u) ) t |= C1_PUNCT;
  if( iscntrl(u) ) t |= C1_CNTRL;
  if( u==' '||u=='\t' ) t |= C1_BLANK;
  if( isxdigit(u) ) t |= C1_XDIGIT;
  return t;
}

extern "C" EXPORT BOOL kernel32_GetStringTypeW(DWORD type, LPCWSTR src, int count, WORD* types) {
  if( !src||!types||count==0 ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return FALSE;
  }
  if( count<0 ) {
    const uint16_t* p = src;
    count = 0;
    while( *p++ )
      count++;
  }
  for( int i = 0; i<count; ++i )
    types[i] = (type==CT_CTYPE1) ? classify_ctype1(src[i]) : 0;
  return TRUE;
}

extern "C" EXPORT int kernel32_CompareStringW(DWORD locale, DWORD flags, LPCWSTR s1, int n1, LPCWSTR s2, int n2) {
  (void)locale;
  int i = 0;
  for(;; i++) {
    int at1 = (n1>=0) ? (i>=n1) : (!s1[i]);
    int at2 = (n2>=0) ? (i>=n2) : (!s2[i]);
    if( at1&&at2 )
      return CSTR_EQUAL;
    if( at1 )
      return CSTR_LESS_THAN;
    if( at2 )
      return CSTR_GREATER_THAN;
    uint16_t c1 = s1[i], c2 = s2[i];
    if( flags&NORM_IGNORECASE ) {
      if( c1>='A'&&c1<='Z' )
        c1 += 32;
      if( c2>='A'&&c2<='Z' )
        c2 += 32;
    }
    if( c1<c2 )
      return CSTR_LESS_THAN;
    if( c1>c2 )
      return CSTR_GREATER_THAN;
  }
}
