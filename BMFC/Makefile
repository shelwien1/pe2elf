# BMFC — decompiled BMF as a standalone program.
#
#   make            native 32-bit ELF        -> bmf
#   make bmf.exe    Windows, via mingw       -> bmf.exe
#   make test       round-trip gate, native
#   make test-wine  round-trip gate, Windows binary under wine
#   make all test-all
#
# The build scripts carry the reasoning for the compiler flags; this is a
# convenience wrapper over them.
.PHONY: all test test-wine test-all clean

all: bmf

bmf: bmf.cpp crt.cpp main.cpp bmfhead.h bmfdefs.h blob.inc $(wildcard inc/*.inc)
	./build.sh

bmf.exe: bmf.cpp crt.cpp main.cpp bmfhead.h bmfdefs.h blob.inc $(wildcard inc/*.inc)
	./build-mingw.sh

test: bmf
	./test.sh ./bmf

test-wine: bmf.exe
	./test.sh --wine ./bmf.exe

test-all: test test-wine

clean:
	rm -f bmf bmf.exe
	rm -rf run
