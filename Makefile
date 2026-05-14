CC  = g++

SHIM_OUT   = winapi_shim.so
SHIM_SRCS  = shim.cpp
SHIM_FLAGS = -O2 -fPIC -shared -m64 -std=c++17 \
             -fvisibility=hidden \
             -Wall -Wextra -Wno-unused-parameter \
             -I.
SHIM_LDFLAGS = -lpthread -ldl \
               -Wl,--version-script=shim.map \
               -Wl,-z,now \
               -Wl,-soname,winapi_shim.so

PE2ELF_OUT   = pe2elf
PE2ELF_SRCS  = pe2elf.cpp
PE2ELF_FLAGS = -O2 -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wl,-rpath,'$ORIGIN'

all: $(SHIM_OUT) $(PE2ELF_OUT)

$(SHIM_OUT): $(SHIM_SRCS) shim_types.h shim.map
	$(CC) $(SHIM_FLAGS) -o $@ $(SHIM_SRCS) $(SHIM_LDFLAGS)

$(PE2ELF_OUT): $(PE2ELF_SRCS)
	$(CC) $(PE2ELF_FLAGS) -o $@ $(PE2ELF_SRCS)

clean:
	rm -f $(SHIM_OUT) $(PE2ELF_OUT)

.PHONY: all clean
