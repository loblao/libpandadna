import argparse
import os
import sys


parser = argparse.ArgumentParser(
    description='This script can be used to produce compiled DNA files.')
parser.add_argument('--output', '-o',
                    help='The compiled output file. Default: FILENAME.pdna')
parser.add_argument('--compress', '-c', action='store_true',
                    help='Compress the output file using ZLib.')
parser.add_argument('--verbose', '-v', action='store_true',
                    help='Describe the build process.')
parser.add_argument('--logfile', '-l',
                    help='Optional file to write the console output to.')
parser.add_argument('filename',
                    help='The raw input file.')
args = parser.parse_args()

if not args.output:
    args.output = os.path.splitext(args.filename)[0] + '.pdna'

print 'Output:', args.output


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

import ply.lex as lex
from tokens import *


lexer = lex.lex(optimize=0)


class DNAError(Exception):
    pass
__builtins__.DNAError = DNAError


import struct

from components import DNAData
import DNAStorage


def loadDNAFile(dnaStore, filename):
    print 'Reading DNA file...', filename
    dnaData = DNAData.DNAData('pdna_compiler')
    dnaData.setDnaStorage(dnaStore)
    dnaData.read(open(filename, 'r'))
    packedData = dnaData.traverse(recursive=True, verbose=args.verbose)
    return packedData


dnaStore = DNAStorage.DNAStorage()
data = loadDNAFile(dnaStore, args.filename)
storeData = dnaStore.dump()

print 'Writing...', args.output

data = struct.pack('<I', len(storeData)) + storeData + data

if args.compress:
    import zlib
    data = zlib.compress(data)

header = 'PDNA\n{0}\n'.format(chr(1 if args.compress else 0))

with open(args.output, 'wb') as f:
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

print 'Done.'
