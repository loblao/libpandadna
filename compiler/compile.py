import argparse
import os
import sys
import glob

from dna.base import DNAStorage
from dna.components import DNARoot
from dna.parser.tokens import *
from ply import lex

from panda3d.core import loadPrcFileData, getModelPath
loadPrcFileData("", "window-type none")
import direct.directbase.DirectStart

parser = argparse.ArgumentParser(
    description='This script can be used to produce compiled DNA files.')
parser.add_argument('--compress', '-c', action='store_true',
                    help='Compress the output file using ZLib.')
parser.add_argument('--verbose', '-v', action='store_true',
                    help='Describe the build process.')
parser.add_argument('--logfile', '-l',
                    help='Optional file to write the console output to.')
parser.add_argument('--path', '-p',
                    help='Add this path to search path (font loading only).')
parser.add_argument('filenames', nargs='+',
                    help='The raw input file(s). Accepts * as wildcard.')
args = parser.parse_args()

getModelPath().appendDirectory(args.path)

class LogAndOutput:
    def __init__(self, out, filename):
        self.out = out
        self.file = open(filename, 'w')

    def write(self, string):
        self.file.write(string)
        self.out.write(string)
        self.flush()

    def flush(self):
        self.file.flush()
        self.out.flush()


if args.logfile:
    sys.stdout = LogAndOutput(sys.stdout, args.logfile)
    sys.stderr = LogAndOutput(sys.stderr, args.logfile)


lexer = lex.lex(optimize=0)


class DNAError(Exception):
    pass
__builtins__.DNAError = DNAError


def loadDNAFile(dnaStore, filename):
    print 'Reading DNA file...', filename
    root = DNARoot.DNARoot(name='root', dnaStore=dnaStore)
    with open(filename, 'r') as f:
        root.read(f)
    return str(root.traverse(recursive=True, verbose=args.verbose))

global dnaStore
global globalFontDict
dnaStore = None
globalFontDict = {}

def make_store(filename):
    global dnaStore
    
    if dnaStore:
        fonts = dnaStore.fonts.copy()
    
    else:
        fonts = {}
        
    globalFontDict.update(fonts)
    
    dnaStore = DNAStorage.DNAStorage()
    if not filename.startswith('storage'):
        dnaStore.fonts = globalFontDict.copy()
        
    __builtins__.globalStorage = dnaStore

def process_single_file(filename):
    make_store(filename)
    
    rootData = loadDNAFile(dnaStore, filename)
    
    if not filename.startswith('storage'):
        dnaStore.fonts = {k: v for k, v in dnaStore.fonts.items() if globalFontDict.get(k) != v} # remove global fonts
        
    dnaStoreData = dnaStore.dump(verbose=args.verbose)
    
    output = os.path.splitext(filename)[0] + '.pdna'
    print 'Writing...', output

    data = str(dnaStoreData + rootData)
    if args.compress:
        import zlib
        data = zlib.compress(data)
        
    header = 'PDNA\n{0}\n'.format(chr(1 if args.compress else 0))

    with open(output, 'wb') as f:
        f.write(header + data)

    if args.verbose:
        catalogCodeCount = 0
        for root, codes in dnaStore.catalogCodes.items():
            catalogCodeCount += len(codes)
        print 'Catalog code count:', catalogCodeCount
        print 'Texture count:', len(dnaStore.textures)
        print 'Font count:', len(dnaStore.fonts)
        print 'Node count:', len(dnaStore.nodes)
        print 'Hood node count:', len(dnaStore.hoodNodes)
        print 'Place node count:', len(dnaStore.placeNodes)
        print 'DNAGroup count:', len(dnaStore.DNAGroups)
        print 'DNANode count:', len(dnaStore.DNANodes)
        print 'DNAVisGroup count:', len(dnaStore.DNAVisGroups)
        print 'Block number count:', len(dnaStore.blockNumbers)
        print 'Block zone ID count:', len(dnaStore.blockZones)
        print 'Block title count:', len(dnaStore.blockTitles)
        print 'Block article count:', len(dnaStore.blockArticles)
        print 'Block building type count:', len(dnaStore.blockBuildingTypes)
        print 'DNASuitPoint count:', len(dnaStore.suitPoints)
        print 'DNASuitEdge count:', len(dnaStore.suitEdges)
        print 'DNABattleCell count:', len(dnaStore.battleCells)

    print 'Done processing %s.' % filename

for filename in args.filenames:
    filelist = []
    if '*' in filename:
        filelist = glob.glob(filename)
        
    else:
        filelist.append(filename)
        
    for file in filelist:
        process_single_file(file)

print 'Done.'
