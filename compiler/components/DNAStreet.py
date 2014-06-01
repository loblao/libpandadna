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
        self.sidewalkColor = (1, 1, 1, 1)
        self.curbColor = (1, 1, 1, 1)
        self._setTextureCount = 0
        self._setColorCount = 0

    def setCode(self, code):
        self.code = code

    def setStreetTexture(self, texture):
        self.streetTexture = texture

    def setSidewalkTexture(self, texture):
        self.sidewalkTexture = texture

    def setCurbTexture(self, texture):
        self.curbTexture = texture

    def setStreetColor(self, color):
        self.streetColor = color

    def setSidewalkColor(self, color):
        self.sidewalkColor = color

    def setCurbColor(self, color):
        self.curbColor = color

    def setTexture(self, texture):
        if self._setTextureCount == 0:
            self.streetTexture = texture
        elif self._setTextureCount == 1:
            self.sidewalkTexture = texture
        elif self._setTextureCount == 2:
            self.curbTexture = texture
        self._setTextureCount += 1

    def setColor(self, color):
        if self._setColorCount == 0:
            self.streetColor = color
        elif self._setColorCount == 1:
            self.sidewalkColor = color
        elif self._setColorCount == 2:
            self.curbColor = color
        self._setColorCount += 1

    def debug(self, message):
        if self.verbose:
            print 'DNAStreet:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        data += struct.pack('<B', len(self.code))  # Code length
        self.debug('packing... code length: {0}'.format(len(self.code)))
        data += self.code  # Code
        self.debug('packing... code: {0}'.format(self.code))

        data += struct.pack('<B', len(self.streetTexture))  # Street texture length
        self.debug('packing... street texture length: {0}'.format(len(self.streetTexture)))
        data += self.streetTexture  # Street texture
        self.debug('packing... street texture: {0}'.format(self.streetTexture))

        data += struct.pack('<B', len(self.sideWalkTexture))  # Side walk texture length
        self.debug('packing... side walk texture length: {0}'.format(len(self.sideWalkTexture)))
        data += self.sideWalkTexture  # Side walk texture
        self.debug('packing... side walk texture: {0}'.format(self.sideWalkTexture))

        data += struct.pack('<B', len(self.curbTexture))  # Curb texture length
        self.debug('packing... curb texture length: {0}'.format(len(self.curbTexture)))
        data += self.curbTexture  # Curb texture
        self.debug('packing... curbtexture: {0}'.format(self.curbTexture))

        for component in self.streetColor:
            data += struct.pack('B', int(component * 255))  # Street color
            self.debug('packing... street color: {0}'.format(component))

        for component in self.sidewalkColor:
            data += struct.pack('B', int(component * 255))  # Side walk color
            self.debug('packing... side walk color: {0}'.format(component))

        for component in self.curbColor:
            data += struct.pack('B', int(component * 255))  # Curb color
            self.debug('packing... curb color: {0}'.format(component))

        return data
