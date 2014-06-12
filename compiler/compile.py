#!/usr/bin/env python2
import argparse
import os
import sys

from dna.base import DNAStorage
from dna.components import DNARoot
from dna.parser.tokens import *
from ply import lex


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


lexer = lex.lex(optimize=0)


class DNAError(Exception):
    pass
__builtins__.DNAError = DNAError


def loadDNAFile(dnaStore, filename):
    print 'Reading DNA file...', filename
    root = DNARoot.DNARoot(name='root', dnaStore=dnaStore)
    with open(filename, 'r') as f:
        root.read(f)
    return root.traverse(recursive=True, verbose=args.verbose)


dnaStore = DNAStorage.DNAStorage()
rootData = loadDNAFile(dnaStore, args.filename)
dnaStoreData = dnaStore.dump(verbose=args.verbose)

print 'Writing...', args.output

data = str(dnaStoreData + rootData)
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
    print 'Block number count:', len(dnaStore.blockNumbers)
    print 'Block zone ID count:', len(dnaStore.blockZones)
    print 'Block title count:', len(dnaStore.blockTitles)
    print 'Block article count:', len(dnaStore.blockArticles)
    print 'Block building type count:', len(dnaStore.blockBuildingTypes)
    print 'DNASuitPoint count:', len(dnaStore.suitPoints)
    print 'DNASuitEdge count:', len(dnaStore.suitEdges)
    print 'DNABattleCell count:', len(dnaStore.battleCells)

print 'Done.'
