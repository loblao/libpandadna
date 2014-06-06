import struct

import DNANode


class DNASign(DNANode.DNANode):
    COMPONENT_CODE = 5

    def __init__(self):
        DNANode.DNANode.__init__(self, '')

        self.code = ''
        self.color = (1, 1, 1, 1)

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def debug(self, message):
        if self.verbose:
            print 'DNASign:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        self.debug('packing... code length: {0}'.format(len(self.code)))
        data += struct.pack('<B', len(self.code))  # Code length
        self.debug('packing... code: {0}'.format(self.code))
        data += self.code

        for component in self.color:
            self.debug('packing... color: {0}'.format(component))
            data += struct.pack('B', int(component * 255))  # Color

        if recursive:
            data += self.traverseChildren(verbose=verbose)

        return data
