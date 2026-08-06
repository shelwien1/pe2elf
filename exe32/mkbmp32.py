#!/usr/bin/env python3
"""Write a small deterministic 24-bit BMP for the BMF round-trip test.

Deliberately not a flat gradient: BMF's filter selection and context modelling
need real spatial structure to exercise, but the image must stay reproducible
byte-for-byte across runs, so the "noise" is a fixed LCG rather than random.

Usage: mkbmp32.py <out.bmp> [width] [height]
"""
import struct
import sys


def build(w: int, h: int) -> bytes:
    # Bottom-up 24-bit BGR, rows padded to a 4-byte boundary.
    stride = (w * 3 + 3) & ~3
    rows = []
    seed = 0x13579BDF
    for y in range(h):
        row = bytearray()
        for x in range(w):
            seed = (seed * 1103515245 + 12345) & 0xFFFFFFFF
            n = (seed >> 16) & 0x1F              # low-amplitude dither
            # Smooth ramps in two directions plus a diagonal band, so the
            # image has both flat areas and edges for the filters to work on.
            r = (x * 255) // max(w - 1, 1)
            g = (y * 255) // max(h - 1, 1)
            b = 255 if ((x + y) // 16) % 2 else 40
            row += bytes(((b + n) & 0xFF, (g + n) & 0xFF, (r + n) & 0xFF))
        row += b"\0" * (stride - len(row))
        rows.append(bytes(row))
    body = b"".join(rows)
    # BITMAPFILEHEADER (14) + BITMAPINFOHEADER (40); DPI fields left 0 because
    # BMF does not store them and would otherwise make the round-trip differ.
    hdr = struct.pack("<2sIHHI", b"BM", 14 + 40 + len(body), 0, 0, 14 + 40)
    info = struct.pack("<IiiHHIIiiII", 40, w, h, 1, 24, 0, len(body), 0, 0, 0, 0)
    return hdr + info + body


def main() -> int:
    if len(sys.argv) < 2:
        sys.stderr.write(__doc__)
        return 1
    out = sys.argv[1]
    w = int(sys.argv[2]) if len(sys.argv) > 2 else 256
    h = int(sys.argv[3]) if len(sys.argv) > 3 else 192
    data = build(w, h)
    with open(out, "wb") as f:
        f.write(data)
    print("wrote %s (%dx%d, %d bytes)" % (out, w, h, len(data)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
