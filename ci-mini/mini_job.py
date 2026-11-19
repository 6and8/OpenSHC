"""CI side of win/cimini.py: build one job's minimal closure, then every variant of it, keep each DLL/PDB.

Run from the repo root on a Windows runner: python ci-mini/mini_job.py JOB JOM
Job folder ci-mini/jobs/JOB/: list.txt (closure source list), vars.json ([[id, repo_path], ...] in build order),
vars/<id>/<repo_path> (the variant file). Output out/<id>/OpenSHC.{dll,pdb} (id "base" = unmodified), or
out/<id>/SAME.txt when the variant's DLL equals the base's apart from build stamps (no upload: scored as base),
or out/<id>/FAIL.txt with the error lines, plus out/times.txt. At the end all out/<id>/ folders are packed into
out/mini.tar.xz (win/cimini.py unpacks it after the download).
"""
import json
import lzma
import os
import re
import shutil
import struct
import subprocess
import sys
import tarfile
import time

job, jom = sys.argv[1], sys.argv[2]
jd = os.path.join('ci-mini', 'jobs', job)
shutil.copyfile(os.path.join(jd, 'list.txt'), os.path.join('cmake', 'openshc-sources.txt.local'))
DLL = os.path.join('build-RelWithDebInfo', 'DLL')
times = []


def sh(cmd):
    # shell=True passes the string to cmd as is (a list would backslash-escape the inner quotes)
    r = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
                       errors='replace')
    return r.returncode, r.stdout


def image(path):
    """DLL bytes with the build-unique fields zeroed (header timestamp, checksum, debug directory timestamps,
    CodeView GUID/age): equal images = equal code and data = equal scores."""
    b = bytearray(open(path, 'rb').read())
    u32 = lambda o: struct.unpack_from('<I', b, o)[0]
    pe = u32(0x3c)
    nsec, opt = struct.unpack_from('<H', b, pe + 6)[0], pe + 24
    b[pe + 8:pe + 12] = bytes(4)
    b[opt + 64:opt + 68] = bytes(4)
    sec = opt + struct.unpack_from('<H', b, pe + 20)[0]
    secs = [struct.unpack_from('<IIII', b, sec + 40 * k + 8) for k in range(nsec)]  # vsize, rva, rawsize, rawptr

    def off(rva):
        for vs, va, rs, rp in secs:
            if va <= rva < va + max(vs, rs):
                return rva - va + rp
        return None
    erva = struct.unpack_from('<I', b, opt + 96)[0]  # export directory: TimeDateStamp at +4
    eo = off(erva) if erva else None
    if eo is not None:
        b[eo + 4:eo + 8] = bytes(4)
    drva, dsize = struct.unpack_from('<II', b, opt + 96 + 6 * 8)
    o = off(drva) if drva else None
    for k in range(dsize // 28 if o is not None else 0):
        e = o + 28 * k
        b[e + 4:e + 8] = bytes(4)
        typ, size, ptr = u32(e + 12), u32(e + 16), u32(e + 24)
        if typ == 2 and b[ptr:ptr + 4] == b'RSDS':
            b[ptr + 4:ptr + 24] = bytes(20)
    return bytes(b)


BASE_IMAGE = []


def build(tag):
    t = time.time()
    rc, out = sh(r'call .\cmakew.bat --build --preset RelWithDebInfo --target OpenSHC.dll')
    errs = [l for l in out.splitlines() if re.search(r' error (C|LNK)\d+', l)]
    dst = os.path.join('out', tag)
    os.makedirs(dst, exist_ok=True)
    dt = time.time() - t
    times.append('%s %.0f' % (tag, dt))
    print('%s: rc %d, %.0f s' % (tag, rc, dt), flush=True)
    if rc or errs:
        open(os.path.join(dst, 'FAIL.txt'), 'w').write('\n'.join(errs or out.splitlines()[-40:]) + '\n')
        return False
    # identical image to the base: upload a marker instead of ~25 MB of DLL+PDB (artifact egress, 2026-11-18)
    try:
        img = image(os.path.join(DLL, 'OpenSHC.dll'))
    except Exception as e:  # never lose a build to the shortcut
        print('image compare skipped: %s' % e, flush=True)
        img = None
    if tag == 'base':
        BASE_IMAGE.append(img)
    elif img is not None and BASE_IMAGE and img == BASE_IMAGE[0]:
        open(os.path.join(dst, 'SAME.txt'), 'w').write('image identical to base\n')
        print('%s: same image as base' % tag, flush=True)
        return True
    for f in ('OpenSHC.dll', 'OpenSHC.pdb'):
        shutil.copyfile(os.path.join(DLL, f), os.path.join(dst, f))
    return True


t0 = time.time()
for cmd in (r'python tools\reimplementation-control\enable_reimplemented_data.py',
            r'python tools\reimplementation-helper\batch\enable_local_functions.py',
            r'call .\cmakew.bat --preset RelWithDebInfo "-DCMAKE_MAKE_PROGRAM=%s"' % jom):
    rc, out = sh(cmd)
    if rc:
        sys.exit('%s failed:\n%s' % (cmd, out[-3000:]))
times.append('setup %.0f' % (time.time() - t0))
if not build('base'):
    print(open(os.path.join('out', 'base', 'FAIL.txt')).read())
    sys.exit(1)

current = None  # repo path whose variant is in place
backup = {}
for vid, path in json.load(open(os.path.join(jd, 'vars.json'))):
    if current and current != path:  # restore the previous target; it recompiles alongside this variant (jom -j)
        shutil.copyfile(backup[current], current)
        os.utime(current, None)
    if path not in backup:
        backup[path] = path + '.mini.bak'
        shutil.copyfile(path, backup[path])
    shutil.copyfile(os.path.join(jd, 'vars', vid, path), path)
    os.utime(path, None)
    current = path
    build(vid)
open(os.path.join('out', 'times.txt'), 'w').write('\n'.join(times) + '\n')

# One solid xz of all builds with a 64 MB window: each PDB compresses against the previous one (they differ by a
# few functions but MSF moves most blocks): ~0.5 MB per build instead of ~4 MB zipped (2026-11-18, artifact egress).
t = time.time()
ids = sorted(d for d in os.listdir('out') if os.path.isdir(os.path.join('out', d)))
with lzma.open(os.path.join('out', 'mini.tar.xz'), 'wb',
               filters=[{'id': lzma.FILTER_LZMA2, 'preset': 1, 'dict_size': 64 << 20}]) as xz:
    with tarfile.open(fileobj=xz, mode='w|') as tar:
        for d in ids:
            tar.add(os.path.join('out', d), arcname=d)
for d in ids:
    shutil.rmtree(os.path.join('out', d))
print('packed %d builds into %.1f MB in %.0f s' % (len(ids), os.path.getsize(os.path.join('out', 'mini.tar.xz')) / 1e6,
                                                  time.time() - t), flush=True)
