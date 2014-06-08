import DNANode
from DNAPacker import *


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
        packer.pack('indent', int(self.indent * 100), INT32)
        packer.pack('kern', int(self.kern * 100), INT32)
        packer.pack('wiggle', int(self.wiggle * 100), INT32)
        packer.pack('stumble', int(self.stumble * 100), INT32)
        packer.pack('stomp', int(self.stomp * 100), INT32)
        packer.pack('width', int(self.width * 100), INT32)
        packer.pack('height', int(self.height * 100), INT32)

        if recursive:
            packer += self.traverseChildren(verbose=verbose)
        return packer
