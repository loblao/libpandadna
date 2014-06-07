import struct

import DNANode


class DNAStreet(DNANode.DNANode):
    COMPONENT_CODE = 19

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.code = ''
        self.streetTexture = ''
        self.sideWalkTexture = ''
        self.curbTexture = ''
        self.streetColor = (1, 1, 1, 1)
        self.sideWalkColor = (1, 1, 1, 1)
        self.curbColor = (1, 1, 1, 1)
        self._setTextureCount = 0
        self._setColorCount = 0

    def setCode(self, code):
        self.code = code

    def setTexture(self, texture):
        if self._setTextureCount == 0:
            self.streetTexture = texture
        elif self._setTextureCount == 1:
            self.sideWalkTexture = texture
        elif self._setTextureCount == 2:
            self.curbTexture = texture
        self._setTextureCount += 1

    def setColor(self, color):
        if self._setColorCount == 0:
            self.streetColor = color
        elif self._setColorCount == 1:
            self.sideWalkColor = color
        elif self._setColorCount == 2:
            self.curbColor = color
        self._setColorCount += 1

    def debug(self, message):
        if self.verbose:
            print 'DNAStreet:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        self.debug('packing... code length: {0}'.format(len(self.code)))
        data += struct.pack('<B', len(self.code))  # Code length
        self.debug('packing... code: {0}'.format(self.code))
        data += self.code  # Code

        self.debug('packing... street texture length: {0}'.format(len(self.streetTexture)))
        data += struct.pack('<B', len(self.streetTexture))  # Street texture length
        self.debug('packing... street texture: {0}'.format(self.streetTexture))
        data += self.streetTexture  # Street texture

        self.debug('packing... side walk texture length: {0}'.format(len(self.sideWalkTexture)))
        data += struct.pack('<B', len(self.sideWalkTexture))  # Side walk texture length
        self.debug('packing... side walk texture: {0}'.format(self.sideWalkTexture))
        data += self.sideWalkTexture  # Side walk texture

        self.debug('packing... curb texture length: {0}'.format(len(self.curbTexture)))
        data += struct.pack('<B', len(self.curbTexture))  # Curb texture length
        self.debug('packing... curb texture: {0}'.format(self.curbTexture))
        data += self.curbTexture  # Curb texture

        for component in self.streetColor:
            self.debug('packing... street color: {0}'.format(component))
            data += struct.pack('B', int(component * 255))  # Street color

        for component in self.sideWalkColor:
            self.debug('packing... side walk color: {0}'.format(component))
            data += struct.pack('B', int(component * 255))  # Side walk color

        for component in self.curbColor:
            self.debug('packing... curb color: {0}'.format(component))
            data += struct.pack('B', int(component * 255))  # Curb color

        return data
