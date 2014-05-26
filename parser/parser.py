"""

This script can be used to produce pdna files.
Usage: parser.py [options] filename
The options are:        
    -o output
        Specify output file. Default is basename(filename) + .pdna
    
    -h
        Display this and exit.
        
    -m mf
        Specify a multifile that should be mounted before parsing the files (this requires Panda3D).
        
    -M path
        Prepend this path to all multifiles.
        
    -c
        Enable compression of pdna. Requires zlib.
        
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
    opts, args = getopt.getopt(sys.argv[1:], 'co:s:hm:M:')
    
except getopt.error as msg:
    error(1, msg)
    
filename = ""
output = ""

multifiles = []
mf_path = ""

compress = False
    
for opt, arg in opts:
    if opt == '-o':
        output = arg
        
    elif opt == '-h':
        print_help()
        
    elif opt == '-m':
        multifiles.append(arg)
        
    elif opt == '-M':
        mf_path = arg
        
    elif opt == '-c':
        compress = True
        
    else:
        error(1, "Unknown option %s." % opt)
        
if len(args) != 1:
    error(2, "Too many or too few filenames!")

filename = args[0]
    
try:
    from panda3d.core import *
    #loadPrcFileData('', 'window-type none')
    #import direct.directbase.DirectStart
      
except Exception as e:
    raise
    
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

import ply.lex as lex
import sys, math, random, __builtin__

from tokens import *
lexer = lex.lex(optimize=0)

def wl(file, ilevel, string):
    file.write('\t'*ilevel + string + '\n')

class DNAError(Exception): pass
__builtin__.DNAError = DNAError

from props.DNAData import *

class DNALoader:
    def __init__(self):
        self.data = DNAData("")

    def buildDataDump(self, packer):
        return self.data.traverse(packer)

    def getData(self):
        return self.data

import struct

def packObject(o):
    size = len(o)
    size_s = struct.pack('>I', size) # little endian, up to 2^32
    return size_s + o
        
def loadDNAFile(f, dnaStore):
    print 'Reading DNA file...'
    dnaloader = DNALoader()
    dnaloader.getData().setDnaStorage(dnaStore)
    dnaloader.getData().read(f)
    return dnaloader.buildDataDump(packObject)

import DNAStorage
store = DNAStorage.DNAStorage()

data = loadDNAFile(open_file(filename, vfs), store)
    
'''
data = ""
data += packObject(store.dumpFonts())
data += packObject(store.dumpNodes())
'''

dump_data = packObject(store.dump(packObject)) + data #+ store.dumpRecursive(data, packObject)

if compress:
    import zlib
    dump_data = zlib.compress(dump_data)
    
header = 'pDNA\0\ntt_rul3s%s\n' % chr(1 if compress else 0)

with open(output, 'wb') as f: f.write(header + dump_data)

print 'points', len(store.suitPoints)
print 'point map', len(store.suitPointMap)
print 'dna groups', len(store.DNAGroups)
print 'visgroups', len(store.DNAVisGroups)
print 'edges', len(store.suitEdges)
print 'bt cells', len(store.battleCells)
print 'nodes', len(store.nodes)
print 'hoodNodes', len(store.hoodNodes)
print 'placeNodes', len(store.placeNodes)
print 'fonts', len(store.fonts)
print 'titles', len(store.blockTitles)
print 'articles', len(store.blockArticles)
print 'bldgTypes', len(store.blockBuildingTypes)
print 'doors', len(store.blockDoors)
print 'numbers', len(store.blockNumbers)
print 'zones', len(store.blockZones)
print 'textures', len(store.textures)
print 'catalogCodes', len(store.catalogCodes)
