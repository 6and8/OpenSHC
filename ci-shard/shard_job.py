"""Sharded full build (win/cishard.py, ci/ci-shard.yml). Run from the repo root.

  python shard_job.py pch JOM           build the PCH once (cmake_pch.cxx.obj/.pch + its compile PDB) into out/
  python shard_job.py compile K N JOM   take the PCH from pch/, compile every N-th object of OpenSHC.dll (offset K)
  python shard_job.py link JOM          take the PCH and the shards' objects from shards/*/, link OpenSHC.dll

PCH ON, one PCH for all: building with PCH off changes code (2026-11-05: setupBuildingData 91.9 -> 71.6 in a
PCH-off unsharded build, the same as the PCH-off shards), and one PCH per shard cannot be linked together. Each
shard has its own compile-PDB folder (build/pdb/shardK, seeded with a copy of the PCH's PDB, which /Yu needs): the
objects record that absolute path, and every runner checks out to the same path, so the link job puts each shard's
PDB (and the PCH's, build/pdb/pch) exactly there. Verify: same per-function scores as an unsharded build.
"""
import json
import os
import shutil
import subprocess
import sys
import time

ROOT = os.getcwd()
BUILD = os.path.join(ROOT, 'build-RelWithDebInfo')
DLLDIR = os.path.join('CMakeFiles', 'OpenSHC.dll.dir')


def sh(cmd, env=None, cwd=None):
    t = time.time()
    r = subprocess.run(cmd, shell=True, cwd=cwd, env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                       text=True, errors='replace')
    print('[%.0f s] %s -> %d' % (time.time() - t, cmd[:120], r.returncode), flush=True)
    if r.returncode:
        errs = [l for l in r.stdout.splitlines() if ' error ' in l or 'fatal error' in l]
        print('\n'.join(errs) if errs else r.stdout[-6000:])
        sys.exit(r.returncode)
    return r.stdout


def preset_env():
    """The configure preset's environment (MSVC1400 paths), as cmake --build would set it."""
    presets = json.load(open(os.path.join(ROOT, 'CMakePresets.json'), encoding='utf-8-sig'))
    env = dict(os.environ)
    for p in presets['configurePresets']:
        for k, v in p.get('environment', {}).items():
            env[k] = v.replace('${sourceDir}', ROOT.replace('\\', '/'))
    return env


def setup(jom, extra):
    sh(r'python tools\reimplementation-control\enable_reimplemented_data.py')
    sh(r'python tools\reimplementation-helper\batch\enable_local_functions.py')
    sh(r'call .\cmakew.bat --preset RelWithDebInfo "-DCMAKE_MAKE_PROGRAM=%s" %s' % (jom, extra))


PCH = [os.path.join(DLLDIR, 'cmake_pch.cxx.obj'), os.path.join(DLLDIR, 'cmake_pch.cxx.pch')]


def pdbdir(name):
    return os.path.join(BUILD, 'pdb', name).replace(chr(92), '/')


def place(src, now):
    """Copy the tree src/ into BUILD with a fresh mtime (newer than everything the configure wrote)."""
    n = 0
    for r, _, fs in os.walk(src):
        for f in fs:
            rel = os.path.relpath(os.path.join(r, f), src)
            dst = os.path.join(BUILD, rel)
            os.makedirs(os.path.dirname(dst), exist_ok=True)
            shutil.copyfile(os.path.join(r, f), dst)
            os.utime(dst, (now, now))
            n += f.endswith('.obj')
    return n


def jom_env(jom):
    env = preset_env()
    env['PATH'] = os.path.dirname(jom) + ';' + env['PATH']
    return env


def build_pch(jom):
    setup(jom, '"-DCMAKE_COMPILE_PDB_OUTPUT_DIRECTORY=%s"' % pdbdir('pch'))
    # the object rule is the one that runs /Yc (the .pch rule name differs between CMake versions)
    sh('"%s" /nologo -f %s\\build.make %s' % (jom, DLLDIR, PCH[0]), env=jom_env(jom), cwd=BUILD)
    out = os.path.join(ROOT, 'out')
    d = os.path.join(BUILD, DLLDIR)
    for f in os.listdir(d):
        if f.startswith('cmake_pch') and (f.endswith('.pch') or f.endswith('.obj')):
            os.makedirs(os.path.join(out, DLLDIR), exist_ok=True)
            shutil.copy2(os.path.join(d, f), os.path.join(out, DLLDIR, f))
    shutil.copytree(os.path.join(BUILD, 'pdb'), os.path.join(out, 'pdb'))
    for r, _, fs in os.walk(out):
        for f in fs:
            print('  %s %d KB' % (os.path.relpath(os.path.join(r, f), out), os.path.getsize(os.path.join(r, f)) // 1024))


def objects():
    rsp = open(os.path.join(BUILD, DLLDIR, 'objects1.rsp')).read().split()
    return [o for o in rsp if o.endswith('.obj')]


def compile_shard(k, n, jom):
    mine = pdbdir('shard%02d' % k)
    setup(jom, '"-DCMAKE_COMPILE_PDB_OUTPUT_DIRECTORY=%s"' % mine)
    place('pch', time.time())
    # /Yu wants the PDB the PCH was created with: seed this shard's compile PDB with a copy of it
    os.makedirs(mine, exist_ok=True)
    for f in os.listdir(pdbdir('pch')):
        shutil.copyfile(os.path.join(pdbdir('pch'), f), os.path.join(mine, f))
    objs = [o for o in objects() if 'cmake_pch' not in o][k::n]
    print('shard %d/%d: %d of %d objects' % (k, n, len(objs), len(objects())), flush=True)
    targets = ' '.join(o.replace('/', chr(92)) for o in objs)
    # /K: keep going, so one shard reports every compile error it has (the run then doubles as a compile check)
    log = sh('"%s" /nologo /K -j 4 -f %s\\build.make %s' % (jom, DLLDIR, targets), env=jom_env(jom), cwd=BUILD)
    if 'cmake_pch.cxx' in log and 'Building CXX object CMakeFiles/OpenSHC.dll.dir/cmake_pch.cxx.obj' in log:
        sys.exit('the shard rebuilt the PCH: the shared one was not taken')
    out = os.path.join(ROOT, 'out')
    for o in objs:
        dst = os.path.join(out, o)
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        shutil.copy2(os.path.join(BUILD, o), dst)
    shutil.copytree(mine, os.path.join(out, 'pdb', 'shard%02d' % k))
    print('collected %d objects' % len(objs))


def link(jom):
    setup(jom, '')
    now = time.time()
    n = place('pch', now)
    for shard in sorted(os.listdir('shards')):
        n += place(os.path.join('shards', shard), now)
    print('placed %d objects' % n, flush=True)
    missing = [o for o in objects() if not os.path.exists(os.path.join(BUILD, o))]
    if missing:
        sys.exit('missing %d objects, e.g. %s' % (len(missing), missing[:3]))
    log = sh(r'call .\cmakew.bat --build --preset RelWithDebInfo --target OpenSHC.dll')
    rebuilt = [l for l in log.splitlines() if 'Building CXX object' in l]
    print('recompiled in the link job: %d' % len(rebuilt))
    for l in rebuilt[:10]:
        print('  ' + l)


if __name__ == '__main__':
    if sys.argv[1] == 'pch':
        build_pch(sys.argv[2])
    elif sys.argv[1] == 'compile':
        compile_shard(int(sys.argv[2]), int(sys.argv[3]), sys.argv[4])
    else:
        link(sys.argv[2])
