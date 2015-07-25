import subprocess
import glob
import sys
import os

srcdir = os.path.abspath(os.path.dirname(__file__))
pandadir = os.path.abspath(sys.argv[1])

def run_command(cmd):
    p = subprocess.Popen(cmd, stdout=sys.stdout, stderr=sys.stderr, shell=True)
    ret = p.wait()

    if ret != 0:
        print
        print 'The following command return a non-zero value (%d): %s' % (ret, cmd)
        sys.exit(ret)

def interrogate(module):
    print 'Interrogating', module
    cmd = os.path.join(pandadir, 'bin', 'interrogate')
    cmd += ' -D__inline -DCPPPARSER -DP3_INTERROGATE=1 -D__cplusplus -fnames -string -refcount -assert'
    cmd += ' -S %(pandadir)s/include/parser-inc -S %(pandadir)s/include -I %(pandadir)s/include -I%(srcdir)s/base -I%(srcdir)s/suit -I%(srcdir)s/components'
    cmd += ' -srcdir %(srcdir)s/%(module)s -oc %(srcdir)s/%(module)s_igate.cxx -od %(srcdir)s/%(module)s.in -python-native -DCPPPARSER -D__STDC__=1'
    cmd += ' -D__cplusplus -D__inline -longlong __int64 -D_X86_ -DWIN32_VC -DWIN32 -module libpandadna -library %(module)s -Dvolatile='

    cmd = cmd % {'pandadir': pandadir, 'module': module, 'srcdir': srcdir}
    files = glob.glob(os.path.join(srcdir, module, '*.h'))
    for file in files:
        cmd += ' %s' % os.path.basename(file)

    run_command(cmd)

for module in ('base', 'suit', 'components'):
    interrogate(module)

os.chdir(srcdir)
cmd = os.path.join(pandadir, 'bin', 'interrogate_module') + ' -python-native -oc libpandadna_module.cxx'
cmd += ' -library libpandadna -module libpandadna base.in suit.in components.in'
run_command(cmd)
