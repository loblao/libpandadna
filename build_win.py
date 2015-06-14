import subprocess
import argparse
import glob
import sys
import os

parser = argparse.ArgumentParser()
parser.add_argument('--panda3d-dir', '-p',
                    help='Panda3D directory.', required=True)
parser.add_argument('--python-dir', '-y',
                    help='Python directory.')
parser.add_argument('--output', '-o',
                    help='Output directory.', required=True)
parser.add_argument('--no-link', '-l', action='store_true',
                    help='Do not link the dynamic library. Use this if \
                    you intend to build a static library.')
args = parser.parse_args()

def getOutputPath(*path):
    return os.path.join(args.output, *path)

obj_dir = getOutputPath('obj')
if not os.path.isdir(obj_dir):
    os.makedirs(obj_dir)

panda3d_dir = args.panda3d_dir
python_dir = args.python_dir
if not python_dir:
    python_dir = os.path.join(panda3d_dir, 'python')
    
objects = set()

def run_command(cmd):
    p = subprocess.Popen(cmd, stdout=sys.stdout, stderr=sys.stderr)
    ret = p.wait()
    
    if ret != 0:
        print
        print 'The following command return a non-zero value (%d): %s' % (ret, cmd)
        sys.exit(ret)
        
def compile(filename):
    output = getOutputPath('obj', os.path.basename(filename))
    output = os.path.splitext(output)[0] + '.obj'
    
    cmd = 'cl /nologo /c /EHsc /MD /GS /fp:precise /D "WIN32" /D "_WINDOWS" /D "BUILDING_DNA"'
    cmd += " /I" + os.path.join(panda3d_dir, 'include')
    cmd += " /I" + os.path.join(python_dir, 'include')
    cmd += ' /Isrc/base'
    cmd += ' /Isrc/suit'
    cmd += ' /Isrc/components'
    cmd += ' /Fo%s %s' % (output, filename)
    
    run_command(cmd)
    
    obj = os.path.basename(filename)
    obj = os.path.splitext(obj)[0]
    objects.add(obj + '.obj')
    
def interrogate(module):
    print 'Interrogating', module
    cmd = os.path.join(panda3d_dir, 'bin', 'interrogate')
    cmd += ' -D__inline -DCPPPARSER -DP3_INTERROGATE=1 -D__cplusplus -fnames -string -refcount -assert'
    cmd += ' -S %(pandadir)s\include\parser-inc -S %(pandadir)s\include -I %(pandadir)s\include -Isrc/base -Isrc/suit -Isrc/components'
    cmd += ' -srcdir src/%(module)s -oc %(output)s/%(module)s_igate.cxx -od %(output)s/%(module)s.in -python-native -DCPPPARSER -D__STDC__=1'
    cmd += ' -D__cplusplus -D__inline -longlong __int64 -D_X86_ -DWIN32_VC -DWIN32 -module libpandadna -library %(module)s -Dvolatile='
    
    cmd = cmd % {'pandadir': panda3d_dir, 'module': module, 'output': getOutputPath()}
    files = glob.glob(os.path.join('src', module, '*.h'))
    for file in files:
        cmd += " %s" % os.path.basename(file)

    run_command(cmd)
    compile(getOutputPath(module + '_igate.cxx'))
    
for module in ('base', 'suit', 'components'):
    files = glob.glob(os.path.join('src', module, '*.cxx'))
    for file in files:
        compile(file)
        
    interrogate(module)
        
cmd = os.path.join(panda3d_dir, 'bin', 'interrogate_module') + ' -python-native -oc %(output)s/libpandadna_module.cxx'
cmd += ' -library libpandadna -module libpandadna %(output)s/base.in %(output)s/suit.in %(output)s/components.in'
run_command(cmd % {'output': getOutputPath()})
compile(getOutputPath('libpandadna_module.cxx'))

if not args.no_link:
    print 'Linking...'
    
    cmd = 'link /DLL /nologo /ignore:4217 /ignore:4049 /out:%s' % getOutputPath('libpandadna.pyd')
    cmd += ' /LIBPATH:' + os.path.join(panda3d_dir, 'lib')
    cmd += ' /LIBPATH:' + os.path.join(python_dir, 'libs')
    
    for obj in objects:
        cmd += ' ' + getOutputPath('obj', obj)
        
    libs = ('libp3framework', 'libpanda', 'libpandafx', 'libpandaexpress', 'libp3dtool', 'libp3dtoolconfig', 'libp3direct', 'python27',
            'ws2_32', 'shell32', 'advapi32', 'gdi32', 'user32', 'oleaut32', 'ole32', 'shell32', 'wsock32', 'imm32')
    for lib in libs:
        cmd += ' %s.lib' % lib
        
    run_command(cmd)
    