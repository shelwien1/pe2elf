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

LOAD_OUT     = load
LOAD_SRCS    = load.cpp
LOAD_FLAGS   = -O2 -std=c++17 -Wall -Wextra -Wno-unused-parameter
# Link directly against winapi_shim.so so it's pulled in via DT_NEEDED at
# load time, otherwise its initial-exec __thread variables can't fit in
# the static TLS block when loaded later via dlopen.
LOAD_LDFLAGS = -ldl -L. -Wl,--no-as-needed,-l:winapi_shim.so,--as-needed \
               '-Wl,-rpath,$$ORIGIN'

# ---------------------------------------------------------------------------
# 32-bit pipeline: pe2elf32 (PE32/i386 -> ELF32) + winapi_shim32.so + load32.
# Requires the 32-bit dev headers/libs: gcc-multilib g++-multilib
# libc6-dev-i386 (Debian/Ubuntu) or glibc-devel.i686 libstdc++-devel.i686
# (Fedora).  32-bit codegen alone is not enough — the shim includes system
# headers.
# ---------------------------------------------------------------------------
SHIM32_OUT     = winapi_shim32.so
SHIM32_DBG_OUT = winapi_shim32_dbg.so
DUMMY32_OUT    = dummy32.so
SHIM32_SRCS    = shim32.cpp

# -D_FILE_OFFSET_BITS=64 is load-bearing here, not cosmetic: on x86-64 off_t
# is already 64-bit, but on i386 this is what makes it so and redirects
# lseek/stat/open to their *64 variants.  Without it file sizes silently cap
# at 2 GB.
SHIM32_FLAGS = -O2 -fPIC -shared -m32 -std=c++17 \
               -fvisibility=hidden \
               -Wall -Wextra -Wno-unused-parameter \
               -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 \
               -I.
SHIM32_LDFLAGS = -lpthread -ldl \
                 -Wl,--version-script=shim32.map \
                 -Wl,-z,now \
                 -Wl,-soname,winapi_shim32.so
SHIM32_DBG_FLAGS = -g -O0 -fPIC -shared -m32 -std=c++17 \
               -fvisibility=hidden \
               -Wall -Wextra -Wno-unused-parameter \
               -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 \
               -I.
SHIM32_DBG_LDFLAGS = -lpthread -ldl \
                     -Wl,--version-script=shim32.map \
                     -Wl,-soname,winapi_shim32_dbg.so

# 0x30000000 keeps the injected .so inside the 3 GB i386 user range and well
# clear of both the PE image at 0x400000 and the usual mmap region.
DUMMY32_FLAGS   = -O2 -fPIC -shared -m32 -std=c++17 -fpermissive -Wno-narrowing -Wno-write-strings
DUMMY32_LDFLAGS = -Wl,-soname,dummy32.so \
                  -Wl,-Ttext-segment=0x30000000 \
                  -Wl,-z,max-page-size=0x1000

# Host tool — native build, just emits ELF32 bytes. No -m32 needed.
PE2ELF32_OUT   = pe2elf32
PE2ELF32_SRCS  = pe2elf32.cpp
PE2ELF32_FLAGS = -O2 -std=c++17 -Wall -Wextra -Wno-unused-parameter -static

LOAD32_OUT     = load32
LOAD32_SRCS    = load32.cpp
LOAD32_FLAGS   = -O2 -m32 -std=c++17 -Wall -Wextra -Wno-unused-parameter
LOAD32_LDFLAGS = -ldl -L. -Wl,--no-as-needed,-l:winapi_shim32.so,--as-needed \
                 '-Wl,-rpath,$$ORIGIN'

all: $(SHIM_OUT) $(SHIM_DBG_OUT) $(DUMMY_OUT) $(PE2ELF_OUT) $(LOAD_OUT)

all32: $(SHIM32_OUT) $(SHIM32_DBG_OUT) $(PE2ELF32_OUT) $(LOAD32_OUT)

SHIM_HEADERS   = $(wildcard shim_*.hpp)
SHIM32_HEADERS = $(wildcard shim32_*.hpp)

$(SHIM_OUT): $(SHIM_SRCS) $(SHIM_HEADERS) shim_types.h shim.map
	$(CC) $(SHIM_FLAGS) -o $@ $(SHIM_SRCS) $(SHIM_LDFLAGS)

$(SHIM_DBG_OUT): $(SHIM_SRCS) $(SHIM_HEADERS) shim_types.h shim.map
	$(CC) $(SHIM_DBG_FLAGS) -DWINAPI_LOG_ENABLED -o $@ $(SHIM_SRCS) $(SHIM_DBG_LDFLAGS)

$(DUMMY_OUT): $(DUMMY_SRCS) $(wildcard *.inc) $(wildcard *.h) defs.h
	$(CC) $(DUMMY_FLAGS) -o $@ $(DUMMY_SRCS) $(DUMMY_LDFLAGS)

$(PE2ELF_OUT): $(PE2ELF_SRCS)
	$(CC) $(PE2ELF_FLAGS) -o $@ $(PE2ELF_SRCS)

$(LOAD_OUT): $(LOAD_SRCS) $(SHIM_OUT)
	$(CC) $(LOAD_FLAGS) -o $@ $(LOAD_SRCS) $(LOAD_LDFLAGS)

$(SHIM32_OUT): $(SHIM32_SRCS) $(SHIM32_HEADERS) shim32_types.h shim32.map
	$(CC) $(SHIM32_FLAGS) -o $@ $(SHIM32_SRCS) $(SHIM32_LDFLAGS)

$(SHIM32_DBG_OUT): $(SHIM32_SRCS) $(SHIM32_HEADERS) shim32_types.h shim32.map
	$(CC) $(SHIM32_DBG_FLAGS) -DWINAPI_LOG_ENABLED -o $@ $(SHIM32_SRCS) $(SHIM32_DBG_LDFLAGS)

$(DUMMY32_OUT): $(DUMMY_SRCS) $(wildcard *.inc) $(wildcard *.h) defs.h
	$(CC) $(DUMMY32_FLAGS) -o $@ $(DUMMY_SRCS) $(DUMMY32_LDFLAGS)

$(PE2ELF32_OUT): $(PE2ELF32_SRCS) pe_types32.hpp elf_types32.hpp pe_image32.hpp \
                 elf_plan32.hpp elf_build32.hpp elf_write32.hpp util.hpp
	$(CC) $(PE2ELF32_FLAGS) -o $@ $(PE2ELF32_SRCS)

$(LOAD32_OUT): $(LOAD32_SRCS) $(SHIM32_OUT)
	$(CC) $(LOAD32_FLAGS) -o $@ $(LOAD32_SRCS) $(LOAD32_LDFLAGS)

clean:
	rm -f $(SHIM_OUT) $(SHIM_DBG_OUT) $(DUMMY_OUT) $(PE2ELF_OUT) $(LOAD_OUT)

clean32:
	rm -f $(SHIM32_OUT) $(SHIM32_DBG_OUT) $(DUMMY32_OUT) $(PE2ELF32_OUT) $(LOAD32_OUT)

.PHONY: all all32 clean clean32
