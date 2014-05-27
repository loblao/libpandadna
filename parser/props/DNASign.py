import struct

import DNANode


class DNASign(DNANode.DNANode):
    PROP_CODE = 5

    def __init__(self):
        DNANode.DNANode.__init__(self, '')

        self.code = ''
        self.color = (1, 1, 1, 1)

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def getCode(self):
        return self.code

    def getColor(self):
        return self.color

    def debug(self, message):
        if self.verbose:
            print 'DNASign:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        code = self.getCode()
        data += struct.pack('>B', len(code))  # Code length
        self.debug('packing... code length: {0}'.format(len(code)))
        data += code
        self.debug('packing... code: {0}'.format(code))

        for component in self.getColor():
            data += struct.pack('>f', component)  # Color
            self.debug('packing... color: {0}'.format(component))

        if recursive:
            for child in self.children:
                data += child.traverse(recursive=True, verbose=verbose)

        return data
