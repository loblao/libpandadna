import struct

import DNANode


class DNAWall(DNANode.DNANode):
    COMPONENT_CODE = 10

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.code = ''
        self.height = 10
        self.color = (1, 1, 1, 1)

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def setHeight(self, height):
        self.height = height

    def debug(self, message):
        if self.verbose:
            print 'DNAWall:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        data += struct.pack('<B', len(self.code))  # Code length
        self.debug('packing... code length: {0}'.format(len(self.code)))
        data += self.code  # Code
        self.debug('packing... code: {0}'.format(self.code))

        data += struct.pack('<h', int(self.height * 100))  # Height
        self.debug('packing... height: {0}'.format(self.height))

        for component in self.color:
            data += struct.pack('B', int(component * 255))  # Color
            self.debug('packing... color: {0}'.format(component))

        if recursive:
            data += self.recurse(verbose)

        return data
