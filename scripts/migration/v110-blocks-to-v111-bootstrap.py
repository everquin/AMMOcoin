#!/usr/bin/env python3
"""Rewrite a v1.0/v1.1.0 blk*.dat (magic 76637af3) into a v1.1.1 bootstrap file (magic c79ae3b5).
Usage: remagic.py <in blk*.dat> <out bootstrap.dat>   (load with ammocoind -loadblock=<out>)"""
import sys, struct, hashlib
OLD, NEW = bytes.fromhex('76637af3'), bytes.fromhex('c79ae3b5')
data = open(sys.argv[1], 'rb').read()
out, i, n = bytearray(), 0, 0
while i + 8 <= len(data) and data[i:i+4] == OLD:
    size = struct.unpack('<I', data[i+4:i+8])[0]
    out += NEW + data[i+4:i+8+size]
    i += 8 + size; n += 1
rest = data[i:].strip(b'\0')
assert not rest, 'unexpected data after %d blocks at offset %d' % (n, i)
open(sys.argv[2], 'wb').write(out)
print('%d blocks, %d bytes, sha256 %s' % (n, len(out), hashlib.sha256(out).hexdigest()))
