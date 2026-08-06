# Minimal PE32 wrapper: takes a flat code blob linked at 0x401000 and emits a
# PE32 with a .text section at RVA 0x1000 and a kernel32 import table at
# RVA 0x2000 (GetStdHandle, WriteFile, ExitProcess).  Used by mkseh32.sh.
import struct, sys
text = open(sys.argv[1],'rb').read()
out  = sys.argv[2]

FA, SA = 0x200, 0x1000
# ---- .idata (RVA 0x2000) --------------------------------------------------
funcs = [b"GetStdHandle", b"WriteFile", b"ExitProcess"]
idata = bytearray(0x200)
def put(off, data): idata[off:off+len(data)] = data
IAT, DESC, ILT, DLLNAME, HINTS = 0x000, 0x010, 0x040, 0x060, 0x070
hint_rvas, o = [], HINTS
for f in funcs:
    hint_rvas.append(0x2000+o)
    put(o, struct.pack('<H', 0) + f + b'\0'); o += 2+len(f)+1
    o = (o+1) & ~1
for i, r in enumerate(hint_rvas):
    put(IAT + i*4, struct.pack('<I', r))
    put(ILT + i*4, struct.pack('<I', r))
put(DESC, struct.pack('<IIIII', 0x2000+ILT, 0, 0, 0x2000+DLLNAME, 0x2000+IAT))
put(DLLNAME, b"KERNEL32.dll\0")

secs = [(b".text", 0x1000, text, 0x60000020), (b".idata", 0x2000, bytes(idata), 0xC0000040)]

dos = bytearray(0x40); dos[0:2] = b'MZ'; struct.pack_into('<I', dos, 0x3c, 0x40)
coff = struct.pack('<4sHHIIIHH', b"PE\0\0", 0x14C, len(secs), 0, 0, 0, 224, 0x0103)
hdr_sz = (0x40 + len(coff) + 224 + 40*len(secs) + FA-1) & ~(FA-1)
img_sz = (0x2000 + SA + SA-1) & ~(SA-1)
opt = struct.pack('<HBBIIIIIIIIIHHHHHHIIIIHHIIIIII',
    0x10B, 1, 0, len(text), len(idata), 0, 0x1000, 0x1000, 0x2000,
    0x400000, SA, FA, 4,0, 0,0, 4,0, 0, img_sz, hdr_sz, 0, 3, 0,
    0x100000, 0x1000, 0x100000, 0x1000, 0, 16)
dd = bytearray(16*8)
struct.pack_into('<II', dd, 1*8, 0x2000+DESC, 40)   # IMPORT
struct.pack_into('<II', dd, 12*8, 0x2000+IAT, 16)   # IAT
sectab, raw, off = b'', b'', hdr_sz
for name, rva, data, ch in secs:
    rsz = (len(data)+FA-1) & ~(FA-1)
    sectab += struct.pack('<8sIIIIIIHHI', name, len(data), rva, rsz, off, 0,0,0,0, ch)
    raw += data + b'\0'*(rsz-len(data)); off += rsz
blob = bytes(dos)+coff+opt+bytes(dd)+sectab
open(out,'wb').write(blob + b'\0'*(hdr_sz-len(blob)) + raw)
print("wrote", out, len(blob + b'\0'*(hdr_sz-len(blob)) + raw), "bytes")
