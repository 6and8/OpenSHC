"""Sharded full build (win/cishard.py, ci/ci-shard.yml). Run from the repo root.

  python shard_job.py compile K N JOM   compile every N-th object of OpenSHC.dll (offset K) into out/
  python shard_job.py link JOM          take the shards' objects from shards/*/ and link OpenSHC.dll

Both configure with precompiled headers OFF (one PCH per shard could not be linked together); compile
force-includes src/precomp/pch.h through the CL environment variable instead, which is all the PCH held. And, for compile, a compile-PDB folder per shard (build/pdb/shardK): the objects record that absolute
path, and every runner checks out to the same path, so the link job puts each shard's PDB exactly there. Neither
changes code generation (verify: same per-function scores as an unsharded build).
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
        print(r.stdout[-6000:])
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
    sh(r'call .\cmakew.bat --preset RelWithDebInfo "-DCMAKE_MAKE_PROGRAM=%s" -DCMAKE_DISABLE_PRECOMPILE_HEADERS=ON %s'
       % (jom, extra))


def objects():
    rsp = open(os.path.join(BUILD, DLLDIR, 'objects1.rsp')).read().split()
    return [o for o in rsp if o.endswith('.obj')]


def compile_shard(k, n, jom):
    pdbdir = os.path.join(BUILD, 'pdb', 'shard%02d' % k).replace('\\', '/')
    setup(jom, '"-DCMAKE_COMPILE_PDB_OUTPUT_DIRECTORY=%s"' % pdbdir)
    objs = objects()[k::n]
    print('shard %d/%d: %d of %d objects' % (k, n, len(objs), len(objects())), flush=True)
    env = preset_env()
    env['PATH'] = os.path.dirname(jom) + ';' + env['PATH']
    # PCH off: force-include what the PCH held (cmake_pch.hxx only includes src/precomp/pch.h); same code
    env['CL'] = '/FI"%s"' % os.path.join(ROOT, 'src', 'precomp', 'pch.h')
    targets = ' '.join(o.replace('/', '\\') for o in objs)
    sh('"%s" /nologo -j 4 -f %s\\build.make %s' % (jom, DLLDIR, targets), env=env, cwd=BUILD)
    out = os.path.join(ROOT, 'out')
    for o in objs:
        dst = os.path.join(out, o)
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        shutil.copy2(os.path.join(BUILD, o), dst)
    shutil.copytree(os.path.join(BUILD, 'pdb'), os.path.join(out, 'pdb'))
    print('collected %d objects' % len(objs))


def link(jom):
    setup(jom, '')
    now = time.time()
    n = 0
    for shard in sorted(os.listdir('shards')):
        src = os.path.join('shards', shard)
        for r, _, fs in os.walk(src):
            for f in fs:
                rel = os.path.relpath(os.path.join(r, f), src)
                dst = os.path.join(BUILD, rel)
                os.makedirs(os.path.dirname(dst), exist_ok=True)
                shutil.copyfile(os.path.join(r, f), dst)
                os.utime(dst, (now, now))  # newer than everything the fresh configure wrote
                n += f.endswith('.obj')
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
    if sys.argv[1] == 'compile':
        compile_shard(int(sys.argv[2]), int(sys.argv[3]), sys.argv[4])
    else:
        link(sys.argv[2])
