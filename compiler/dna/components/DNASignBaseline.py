import DNANode
from dna.base.DNAPacker import *


class DNASignBaseline(DNANode.DNANode):
    COMPONENT_CODE = 6

    def __init__(self):
        DNANode.DNANode.__init__(self, '')

        self.code = ''
        self.color = (1, 1, 1, 1)
        self.font = None
        self.flags = ''
        self.indent = 0.0
        self.kern = 0.0
        self.wiggle = 0.0
        self.stumble = 0.0
        self.stomp = 0.0
        self.width = 0
        self.height = 0

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def setFont(self, font):
        self.font = font

    def setHeight(self, height):
        self.height = height

    def setIndent(self, indent):
        self.indent = indent

    def setKern(self, kern):
        self.kern = kern

    def setStomp(self, stomp):
        self.stomp = stomp

    def setStumble(self, stumble):
        self.stumble = stumble

    def setWiggle(self, wiggle):
        self.wiggle = wiggle

    def setWidth(self, width):
        self.width = width

    def setFlags(self, flags):
        self.flags = flags

    def traverse(self, recursive=True, verbose=False):
        packer = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)
        packer.name = 'DNASignBaseline'  # Override the name for debugging.

        packer.pack('code', self.code, SHORT_STRING)
        packer.packColor('color', *self.color)
        packer.pack('font', self.font or '', SHORT_STRING)
        packer.pack('flags', self.flags, SHORT_STRING)
        packer.pack('indent', self.indent, FLOAT64)
        packer.pack('kern', self.kern, FLOAT64)
        packer.pack('wiggle', self.wiggle, FLOAT64)
        packer.pack('stumble', self.stumble, FLOAT64)
        packer.pack('stomp', self.stomp, FLOAT64)
        packer.pack('width', self.width, FLOAT64)
        packer.pack('height', self.height, FLOAT64)

        if recursive:
            packer += self.traverseChildren(verbose=verbose)
        return packer
