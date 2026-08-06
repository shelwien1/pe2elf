#!/usr/bin/env python3
"""mkbmps.py — write the BMF test image set.

Five pixel formats, because BMF takes a different path through the filters and
the context model for each, and a redirect that is wrong for one of them can be
perfectly correct for the others:

    t1.bmp    1bpp bilevel        (2-entry palette)
    t8g.bmp   8bpp grayscale      (256-entry ramp palette)
    t8p.bmp   8bpp palette        (256-entry colour palette)
    t24.bmp   24bpp RGB
    t32.bmp   32bpp RGBA, old-style header

All five carry a 40-byte BITMAPINFOHEADER — the "old-style" form, with
biCompression = BI_RGB — rather than a V4/V5 header, since that is what BMF
writes back and what the round-trip has to match.

The content is deliberately not a flat gradient: BMF's filter selection and
context modelling need real spatial structure to exercise. It must also be
reproducible byte-for-byte across runs, so the "noise" is a fixed LCG rather
than anything random.

Usage: mkbmps.py [outdir] [width] [height]
"""
import os
import struct
import sys


class Rng:
    """Fixed LCG — same sequence every run, on every machine."""

    def __init__(self, seed=0x13579BDF):
        self.s = seed

    def next(self, bits=5):
        self.s = (self.s * 1103515245 + 12345) & 0xFFFFFFFF
        return (self.s >> 16) & ((1 << bits) - 1)


def wrap(w, h, bpp, body, palette=b''):
    """BITMAPFILEHEADER + BITMAPINFOHEADER + optional palette + pixels.

    biXPelsPerMeter/biYPelsPerMeter are left 0 and biClrUsed is set explicitly,
    because BMF does not round-trip every header field and the gate compares
    from bfOffBits — see test.sh.
    """
    off = 14 + 40 + len(palette)
    nclr = len(palette) // 4
    hdr = struct.pack('<2sIHHI', b'BM', off + len(body), 0, 0, off)
    info = struct.pack('<IiiHHIIiiII', 40, w, h, 1, bpp, 0, len(body),
                       0, 0, nclr, nclr)
    return hdr + info + palette + body


def rows_of(w, h, bytes_per_row, fill):
    """Bottom-up rows padded to a 4-byte boundary; `fill(y)` builds one row."""
    stride = (bytes_per_row + 3) & ~3
    out = []
    for y in range(h):
        row = bytearray(fill(y))
        row += b'\0' * (stride - len(row))
        out.append(bytes(row))
    return b''.join(out)


def bmp_1(w, h):
    r = Rng()
    # Diagonal bands plus a dithered disc: large flat runs and hard edges,
    # which is what the bilevel path is for.
    def fill(y):
        row = bytearray((w + 7) // 8)
        for x in range(w):
            dx, dy = x - w // 2, y - h // 2
            disc = dx * dx + dy * dy < (min(w, h) // 3) ** 2
            bit = 1 if (disc ^ (((x + y) // 24) % 2 == 0) ^ (r.next(1) & (x % 7 == 0))) else 0
            if bit:
                row[x >> 3] |= 0x80 >> (x & 7)
        return row
    pal = struct.pack('<4B4B', 0, 0, 0, 0, 255, 255, 255, 0)
    return wrap(w, h, 1, rows_of(w, h, (w + 7) // 8, fill), pal)


def bmp_8(w, h, gray):
    r = Rng()
    if gray:
        pal = b''.join(struct.pack('<4B', i, i, i, 0) for i in range(256))
    else:
        # A 6-7-6-ish colour cube, so neighbouring indices are *not*
        # neighbouring colours — an index-space predictor that happens to work
        # on a grayscale ramp will not on this.
        pal = b''.join(struct.pack('<4B', (i & 7) * 36, ((i >> 3) & 7) * 36,
                                   (i >> 6) * 85, 0) for i in range(256))

    def fill(y):
        row = bytearray(w)
        for x in range(w):
            n = r.next(4)
            v = (x * 160) // max(w - 1, 1) + (y * 64) // max(h - 1, 1)
            if ((x // 20) + (y // 20)) % 2:
                v = 255 - v
            row[x] = (v + n) & 0xFF
        return row
    return wrap(w, h, 8, rows_of(w, h, w, fill), pal)


def bmp_24(w, h):
    r = Rng()

    def fill(y):
        row = bytearray()
        for x in range(w):
            n = r.next()
            rr = (x * 255) // max(w - 1, 1)
            gg = (y * 255) // max(h - 1, 1)
            bb = 255 if ((x + y) // 16) % 2 else 40
            row += bytes(((bb + n) & 0xFF, (gg + n) & 0xFF, (rr + n) & 0xFF))
        return row
    return wrap(w, h, 24, rows_of(w, h, w * 3, fill))


def bmp_32(w, h):
    r = Rng()

    def fill(y):
        row = bytearray()
        for x in range(w):
            n = r.next()
            rr = (x * 255) // max(w - 1, 1)
            gg = (y * 255) // max(h - 1, 1)
            bb = 255 if ((x + y) // 16) % 2 else 40
            # Alpha varies independently of the colour channels, so a fourth
            # channel that is silently dropped or aliased onto one of the
            # others shows up in the comparison.
            aa = (x * 3 + y * 5) & 0xFF
            row += bytes(((bb + n) & 0xFF, (gg + n) & 0xFF, (rr + n) & 0xFF, aa))
        return row
    return wrap(w, h, 32, rows_of(w, h, w * 4, fill))


IMAGES = [
    ('t1.bmp',  lambda w, h: bmp_1(w, h),        '1bpp bilevel'),
    ('t8g.bmp', lambda w, h: bmp_8(w, h, True),  '8bpp grayscale'),
    ('t8p.bmp', lambda w, h: bmp_8(w, h, False), '8bpp palette'),
    ('t24.bmp', lambda w, h: bmp_24(w, h),       '24bpp RGB'),
    ('t32.bmp', lambda w, h: bmp_32(w, h),       '32bpp RGBA'),
]


def main():
    outdir = sys.argv[1] if len(sys.argv) > 1 else os.path.dirname(os.path.abspath(__file__))
    w = int(sys.argv[2]) if len(sys.argv) > 2 else 320
    h = int(sys.argv[3]) if len(sys.argv) > 3 else 240
    for name, build, what in IMAGES:
        data = build(w, h)
        path = os.path.join(outdir, name)
        open(path, 'wb').write(data)
        print("wrote %-9s %-16s %dx%d, %d bytes" % (name, what, w, h, len(data)))


if __name__ == '__main__':
    main()
