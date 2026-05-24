#pragma once
// 7.13 String / Code Page — included from shim.cpp.
//
// References from shim.cpp: utf8_to_wchar, wchar_to_utf8.

extern "C" EXPORT DWORD kernel32_GetACP(void) {
  return 65001;
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

extern "C" EXPORT int kernel32_MultiByteToWideChar(DWORD cp, DWORD flags, LPCSTR src, int srclen, LPWSTR dst, int dstlen) {
  (void)cp;
  (void)flags;
  if( !src ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return 0;
  }
  if( srclen<0 )
    srclen = (int)strlen(src)+1;
  // Treat as UTF-8
  char tmp[65536];
  if( (size_t)srclen<sizeof(tmp) ) {
    memcpy(tmp, src, srclen);
    tmp[srclen] = '\0';
  } else {
    memcpy(tmp, src, sizeof(tmp)-1);
    tmp[sizeof(tmp)-1] = '\0';
  }
  if( dstlen==0 ) {
    // Count only
    uint16_t countbuf[65536];
    return utf8_to_wchar(tmp, countbuf, 65535)+1;
  }
  return utf8_to_wchar(tmp, dst, (size_t)dstlen);
}

extern "C" EXPORT int kernel32_WideCharToMultiByte(DWORD cp, DWORD flags, LPCWSTR src, int srclen, LPSTR dst, int dstlen, LPCSTR defch, BOOL* useddef) {
  (void)cp;
  (void)flags;
  (void)defch;
  (void)useddef;
  if( !src ) {
    SET_LAST_ERROR(ERROR_INVALID_PARAMETER);
    return 0;
  }
  // Build a NUL-terminated copy bounded by srclen when srclen >= 0
  uint16_t tmp_w[65536];
  const uint16_t* wsrc = src;
  if( srclen>=0 ) {
    size_t n = (srclen<(int)(sizeof(tmp_w)/2-1)) ? (size_t)srclen : sizeof(tmp_w)/2-1;
    memcpy(tmp_w, src, n*2);
    tmp_w[n] = 0;
    wsrc = tmp_w;
  }
  if( dstlen==0 ) {
    char tmp[65536];
    return wchar_to_utf8(wsrc, tmp, sizeof(tmp));
  }
  return wchar_to_utf8(wsrc, dst, (size_t)dstlen);
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
