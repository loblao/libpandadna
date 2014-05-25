"""

This script can be used to produce pdna files.
Usage: parser.py [options] filename
The options are:
    -v
        Run verbosely.
        
    -o output
        Specify output file. Default is basename(filename) + .pdna
    
    -h
        Display this and exit.
        
    -m mf
        Specify a multifile that should be mounted before parsing the files (this requires Panda3D).
        
    -M path
        Prepend this path to all multifiles.
        
Disclaimer: This program is meant to work with TT DNA files. It assumes the files are correctly indented.

"""

import getopt, sys, os
from parser_util import *

def error(code, msg = ''):
    print >> sys.stderr, __doc__
    print >> sys.stderr, msg
    sys.exit(code)
    
def print_help():
    #this is like error, but outputs to stdout, not stderr
    print __doc__
    sys.exit(0)

try:
    opts, args = getopt.getopt(sys.argv[1:], 'vo:s:hm:M:')
    
except getopt.error as msg:
    error(1, msg)
    
filename = ""
output = ""
verbose = False

multifiles = []
mf_path = ""
    
for opt, arg in opts:
    if opt == '-o':
        output = arg
        
    elif opt == '-h':
        print_help()
        
    elif opt == '-v':
        verbose = True
        
    elif opt == '-m':
        multifiles.append(arg)
        
    elif opt == '-M':
        mf_path = arg
        
    else:
        error(1, "Unknown option %s." % opt)
        
if len(args) != 1:
    error(2, "Too many or too few filenames!")

filename = args[0]
    
try:
    from panda3d.core import *
    loadPrcFileData('', 'window-type none')
    import direct.directbase.DirectStart
      
except:
    error(4, "Unable to import panda3d.")
    
vfs = None
if multifiles:     
    multifiles = [make_p3d_path(os.path.join(mf_path, x)) for x in multifiles]
     
    vfs = VirtualFileSystem.getGlobalPtr()
    for mf in multifiles:
        r = vfs.mount(mf, ".", 0)
        if not r:
            error(5, "Unable to mount multifile %s (%s)." % (mf, r))
    
if not check_if_files_exist([filename], vfs):
    error(3, "One of the files does not exist!")
    
if not output:
    output = os.path.splitext(os.path.basename(filename))[0] + ".pdna"
    
print 'Output:', output

from props.DNAProp import DNAProp
import shlex

def read_dna_file(f, store):
    lastIndent = 0
    currentProp = store
    for line in f:
        line = line.rstrip().replace('[', '').replace(']', '') #they dont matter at all (assuming that this a well-indented TT file!) 
        line = line.replace('\t', ' ' * 4)
        line = line.split('//', 1)[0] #handle comments
        
        if not line.strip():
            continue
            
        indent = 0
        
        #I wonder if there's a better way to calc this
        p = 0
        while 1:
            if len(line) <= p:
                break
                
            if line[p] != " ":
                break
                
            p += 1
            indent += 1
        
        if indent < lastIndent:
            currentProp = currentProp.getParent()
            
        #print [line[:20], indent, lastIndent, currentProp.__class__.__name__, id(currentProp)]
            
        #do the command
        #it may return a new prop
        x = currentProp.doCommand(*shlex.split(line))
        if isinstance(x, DNAProp):
            currentProp = x
                
        lastIndent = indent

import DNAStorage
store = DNAStorage.DNAStorage()

read_dna_file(open_file(filename, vfs), store)

import struct

def packObject(o):
    size = len(o)
    size_s = struct.pack('>Q', size) # little endian, up to 2^64
    return size_s + o
    
data = ""
data += packObject(store.dumpFonts())
data += packObject(store.dumpNodes())

dump_data = data + store.dumpRecursive(data, packObject)
with open(output, 'wb') as f: f.write(dump_data)
