import struct

import DNANode


class DNAProp(DNANode.DNANode):
    COMPONENT_CODE = 4

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.code = ''
        self.color = (1, 1, 1, 1)

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def debug(self, message):
        if self.verbose:
            print 'DNAProp:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        self.debug('packing... code length: {0}'.format(len(self.code)))
        data += struct.pack('<B', len(self.code))  # Code length
        self.debug('packing... code: {0}'.format(self.code))
        data += self.code  # Code

        for component in self.color:
            self.debug('packing... color: {0}'.format(component))
            data += struct.pack('B', int(component * 255))  # Color

        if recursive:
            data += self.traverseChildren(verbose=verbose)

        return data
