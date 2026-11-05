"""CI side of win/cimini.py: build one job's minimal closure, then every variant of it, keep each DLL/PDB.

Run from the repo root on a Windows runner: python ci-mini/mini_job.py JOB JOM
Job folder ci-mini/jobs/JOB/: list.txt (closure source list), vars.json ([[id, repo_path], ...] in build order),
vars/<id>/<repo_path> (the variant file). Output out/<id>/OpenSHC.{dll,pdb} (id "base" = unmodified), or
out/<id>/FAIL.txt with the error lines, plus out/times.txt.
"""
import json
import os
import re
import shutil
import subprocess
import sys
import time

job, jom = sys.argv[1], sys.argv[2]
jd = os.path.join('ci-mini', 'jobs', job)
shutil.copyfile(os.path.join(jd, 'list.txt'), os.path.join('cmake', 'openshc-sources.txt.local'))
DLL = os.path.join('build-RelWithDebInfo', 'DLL')
times = []


def sh(cmd):
    r = subprocess.run(['cmd', '/c', cmd], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
                       errors='replace')
    return r.returncode, r.stdout


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
