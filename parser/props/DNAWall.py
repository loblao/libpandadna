import struct

import DNANode


class DNAWall(DNANode.DNANode):
    PROP_CODE = 10

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.code = ''
        self.height = 10
        self.color = (1, 1, 1, 1)

    def setCode(self, code):
        self.code = code

    def getCode(self):
        return self.code

    def setColor(self, color):
        self.color = color

    def getColor(self):
        return self.color

    def setHeight(self, height):
        self.height = height

    def getHeight(self):
        return self.height

    def debug(self, message):
        if self.verbose:
            print 'DNAWall:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=True, verbose=verbose)

        code = self.getCode()
        data += struct.pack('>B', len(code))  # Code length
        self.debug('packing... code length: {0}'.format(len(code)))
        data += code  # Code
        self.debug('packing... code: {0}'.format(code))

        data += struct.pack('>f', self.getHeight())  # Height
        self.debug('packing... height: {0}'.format(self.getHeight()))

        for component in self.getColor():
            data += struct.pack('>f', component)  # Color
            self.debug('packing... color: {0}'.format(component))

        if recursive:
            for child in self.children:
                data += child.traverse(recursive=True, verbose=verbose)

        return data
