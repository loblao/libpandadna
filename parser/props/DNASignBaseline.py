import struct

import DNANode


class DNASignBaseline(DNANode.DNANode):
    PROP_CODE = 6

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

    def getCode(self):
        return self.code

    def setColor(self, color):
        self.color = color

    def getColor(self):
        return self.color

    def getFont(self):
        return self.font

    def setFont(self, font):
        self.font = font

    def getHeight(self):
        return self.height

    def setHeight(self, height):
        self.height = height

    def getIndent(self):
        return self.indent

    def setIndent(self, indent):
        self.indent = indent

    def setKern(self, kern):
        self.kern = kern

    def getKern(self):
        return self.kern

    def setStomp(self, stomp):
        self.stomp = stomp

    def getStomp(self):
        return self.stomp

    def setStumble(self, stumble):
        self.stumble = stumble

    def getStumble(self):
        return self.stumble

    def setWiggle(self, wiggle):
        self.wiggle = wiggle

    def getWiggle(self):
        return self.wiggle

    def setWidth(self, width):
        self.width = width

    def getWidth(self):
        return self.width

    def setFlags(self, flags):
        self.flags = flags

    def getFlags(self):
        return self.flags

    def debug(self, message):
        if self.verbose:
            print 'DNASignBaseline:', message

    def traverse(self, recursive=True, verbose=False):
        # Sadly, we have to pack this massive object...
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        code = self.getCode()
        data += struct.pack('>B', len(code))  # Code length
        self.debug('packing... code length: {0}'.format(len(code)))
        data += code  # Code
        self.debug('packing... code: {0}'.format(code))

        for component in self.getColor():
            data += struct.pack('>f', component)  # Color
            self.debug('packing... color: {0}'.format(component))

        font = self.getFont()
        if font is None:
            data += struct.pack('>B', 0)  # Font length
            self.debug('skipping... font length')
            self.debug('skipping... font')
        else:
            data += struct.pack('>B', len(font))  # Font length
            self.debug('packing... font length: {0}'.format(len(font)))
            data += font  # Font
            self.debug('packing... font: {0}'.format(font))

        flags = self.getFlags()
        data += struct.pack('>B', len(flags))  # Flags length
        self.debug('packing... flags length: {0}'.format(len(flags)))
        data += flags  # Flags
        self.debug('packing... flags: {0}'.format(flags))

        data += struct.pack('f', self.getIndent())  # Indent
        self.debug('packing... indent: {0}'.format(self.getIndent()))

        data += struct.pack('f', self.getKern())  # Kern
        self.debug('packing... kern: {0}'.format(self.getKern()))

        data += struct.pack('f', self.getWiggle())  # Wiggle
        self.debug('packing... wiggle: {0}'.format(self.getWiggle()))

        data += struct.pack('f', self.getStumble())  # Stumble
        self.debug('packing... stumble: {0}'.format(self.getStumble))

        data += struct.pack('f', self.getStomp())  # Stomp
        self.debug('packing... stomp: {0}'.format(self.getStomp()))

        data += struct.pack('f', self.getWidth())  # Width
        self.debug('packing... width: {0}'.format(self.getWidth()))

        data += struct.pack('f', self.getHeight())  # Height
        self.debug('packing... height: {0}'.format(self.getHeight()))

        if recursive:
            for child in self.children:
                data += child.traverse(recursive=True, verbose=verbose)

        return data
