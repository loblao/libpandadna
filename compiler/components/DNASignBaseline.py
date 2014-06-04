import struct

import DNANode


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

    def debug(self, message):
        if self.verbose:
            print 'DNASignBaseline:', message

    def traverse(self, recursive=True, verbose=False):
        # Sadly, we have to pack this massive object...
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        data += struct.pack('<B', len(self.code))  # Code length
        self.debug('packing... code length: {0}'.format(len(self.code)))
        data += self.code  # Code
        self.debug('packing... code: {0}'.format(self.code))

        for component in self.color:
            data += struct.pack('B', int(component * 255))  # Color
            self.debug('packing... color: {0}'.format(component))

        if self.font is None:
            data += struct.pack('<B', 0)  # Font length
            self.debug('skipping... font length')
            self.debug('skipping... font')
        else:
            data += struct.pack('<B', len(self.font))  # Font length
            self.debug('packing... font length: {0}'.format(len(self.font)))
            data += self.font  # Font
            self.debug('packing... font: {0}'.format(self.font))

        data += struct.pack('<B', len(self.flags))  # Flags length
        self.debug('packing... flags length: {0}'.format(len(self.flags)))
        data += self.flags  # Flags
        self.debug('packing... flags: {0}'.format(self.flags))

        data += struct.pack('<h', int(self.indent * 100))  # Indent
        self.debug('packing... indent: {0}'.format(self.indent))

        data += struct.pack('<h', int(self.kern * 100))  # Kern
        self.debug('packing... kern: {0}'.format(self.kern))

        data += struct.pack('<h', int(self.wiggle * 100))  # Wiggle
        self.debug('packing... wiggle: {0}'.format(self.wiggle))

        data += struct.pack('<h', int(self.stumble * 100))  # Stumble
        self.debug('packing... stumble: {0}'.format(self.stumble))

        data += struct.pack('<h', int(self.stomp * 100))  # Stomp
        self.debug('packing... stomp: {0}'.format(self.stomp))

        data += struct.pack('<h', int(self.width * 100))  # Width
        self.debug('packing... width: {0}'.format(self.width))

        data += struct.pack('<h', int(self.height * 100))  # Height
        self.debug('packing... height: {0}'.format(self.height))

        if recursive:
            data += self.recurse(verbose)

        return data
