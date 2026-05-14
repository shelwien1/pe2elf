#pragma once
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

  template <typename T> const T* at(size_t off) const {
    if( off+sizeof(T)>data.size() )
      return nullptr;
    return reinterpret_cast<const T*>(data.data()+off);
  }

  const char* str(size_t off) const {
    if( off>=data.size() )
      return "";
    for( size_t i = off; i<data.size(); ++i )
      if( data[i]==0 )
        return reinterpret_cast<const char*>(data.data()+off);
    return "";
  }

  size_t size() const { return data.size(); }
};

// ---------------------------------------------------------------------------
// Simple output buffer builder
// ---------------------------------------------------------------------------
struct OutBuf {
  std::vector<uint8_t> data;

  size_t size() const { return data.size(); }

  void append(const void* p, size_t n) {
    const uint8_t* b = (const uint8_t*)p;
    data.insert(data.end(), b, b+n);
  }

  template <typename T> void append_val(T v) { append(&v, sizeof(v)); }

  void pad_to(size_t alignment) {
    while( data.size()%alignment )
      data.push_back(0);
  }

  void pad_to_size(size_t target) {
    while( data.size()<target )
      data.push_back(0);
  }

  template <typename T> void patch(size_t off, T v) {
    assert(off+sizeof(T)<=data.size());
    memcpy(data.data()+off, &v, sizeof(v));
  }
};

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------
static inline uint64_t align_up(uint64_t v, uint64_t a) {
  return (v+a-1)&~(a-1);
}

static constexpr uint64_t kPageSize = 0x1000;
