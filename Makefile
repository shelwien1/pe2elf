CC  = g++

SHIM_OUT     = winapi_shim.so
SHIM_DBG_OUT = winapi_shim_dbg.so
DUMMY_OUT    = dummy.so
SHIM_SRCS    = shim.cpp
DUMMY_SRCS   = dummy.cpp

SHIM_FLAGS = -O2 -fPIC -shared -m64 -std=c++17 \
             -fvisibility=hidden \
             -Wall -Wextra -Wno-unused-parameter \
             -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 \
             -I.
# Optional: link against mimalloc or jemalloc for better Heap* performance.
# Add -DUSE_MIMALLOC -lmimalloc or -DUSE_JEMALLOC -ljemalloc to SHIM_LDFLAGS.
SHIM_LDFLAGS = -lpthread -ldl \
               -Wl,--version-script=shim.map \
               -Wl,-z,now \
               -Wl,-soname,winapi_shim.so
SHIM_DBG_FLAGS = -g -O0 -fPIC -shared -m64 -std=c++17 \
             -fvisibility=hidden \
             -Wall -Wextra -Wno-unused-parameter \
             -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 \
             -I.
SHIM_DBG_LDFLAGS = -lpthread -ldl \
                   -Wl,--version-script=shim.map \
                   -Wl,-soname,winapi_shim_dbg.so

DUMMY_FLAGS   = -O2 -fPIC -shared -std=c++17 -fpermissive -Wno-narrowing -Wno-write-strings
DUMMY_LDFLAGS = -Wl,-soname,dummy.so \
                -Wl,-Ttext-segment=0xF0000000 \
                -Wl,-z,max-page-size=0x1000

PE2ELF_OUT   = pe2elf
PE2ELF_SRCS  = pe2elf.cpp
PE2ELF_FLAGS = -O2 -std=c++17 -Wall -Wextra -Wno-unused-parameter -static

all: $(SHIM_OUT) $(SHIM_DBG_OUT) $(DUMMY_OUT) $(PE2ELF_OUT)

SHIM_HEADERS = $(wildcard shim_*.hpp)

$(SHIM_OUT): $(SHIM_SRCS) $(SHIM_HEADERS) shim_types.h shim.map
	$(CC) $(SHIM_FLAGS) -o $@ $(SHIM_SRCS) $(SHIM_LDFLAGS)

$(SHIM_DBG_OUT): $(SHIM_SRCS) $(SHIM_HEADERS) shim_types.h shim.map
	$(CC) $(SHIM_DBG_FLAGS) -DWINAPI_LOG_ENABLED -o $@ $(SHIM_SRCS) $(SHIM_DBG_LDFLAGS)

$(DUMMY_OUT): $(DUMMY_SRCS) $(wildcard *.inc) $(wildcard *.h) defs.h
	$(CC) $(DUMMY_FLAGS) -o $@ $(DUMMY_SRCS) $(DUMMY_LDFLAGS)

$(PE2ELF_OUT): $(PE2ELF_SRCS)
	$(CC) $(PE2ELF_FLAGS) -o $@ $(PE2ELF_SRCS)

clean:
	rm -f $(SHIM_OUT) $(SHIM_DBG_OUT) $(DUMMY_OUT) $(PE2ELF_OUT)

.PHONY: all clean
