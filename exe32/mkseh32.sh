#!/usr/bin/env bash
# Regenerate exe32/seh.exe from seh.s.
#
# seh.exe is a hand-built PE32 with no CRT: it links an
# EXCEPTION_REGISTRATION_RECORD into fs:[0] the way an MSVC __try prologue
# does, faults through a null pointer, and its handler rewrites CONTEXT.Eip
# and returns ExceptionContinueExecution.  That exercises the whole x86 SEH
# path in winapi_shim32.so — signal → EXCEPTION_RECORD/CONTEXT → chain walk →
# handler → resume — which nothing in the msvcrt fixtures reaches.
set -eu
cd "$(dirname "$0")"
as --32 -o seh.o seh.s
# --oformat binary gives a flat blob with absolute addresses already resolved
# against the PE's load address, which is what mkpe32.py wraps.
ld -m elf_i386 -Ttext=0x401000 -e _start --oformat binary -o seh.bin seh.o
python3 mkpe32.py seh.bin seh.exe
rm -f seh.o seh.bin
