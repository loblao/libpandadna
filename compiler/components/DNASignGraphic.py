import struct

import DNANode


class DNASignGraphic(DNANode.DNANode):
    COMPONENT_CODE = 8

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.code = ''
        self.color = (1, 1, 1, 1)
        self.width = 0
        self.height = 0
        self.bDefaultColor = True

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color
        self.bDefaultColor = False

    def setWidth(self, width):
        self.width = width

    def setHeight(self, height):
        self.height = height

    def debug(self, message):
        if self.verbose:
            print 'DNASignGraphic:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        data += struct.pack('>B', len(self.code))  # Code length
        self.debug('packing... code length: {0}'.format(len(self.code)))
        data += self.code  # Code
        self.debug('packing... code: {0}'.format(self.code))

        for component in self.color:
            data += struct.pack('>f', component)  # Color
            self.debug('packing... color: {0}'.format(component))

        data += struct.pack('f', self.width)  # Width
        self.debug('packing... width: {0}'.format(self.width))

        data += struct.pack('f', self.height)  # Height
        self.debug('packing... height: {0}'.format(self.height))

        data += struct.pack('?', self.bDefaultColor)  # bDefaultColor?
        self.debug('packing... bDefaultColor?: {0}'.format(self.bDefaultColor))

        if recursive:
            for child in self.children:
                data += child.traverse(recursive=True, verbose=verbose)

        return data
