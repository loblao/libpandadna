import struct

import DNANode


class DNAStreet(DNANode.DNANode):
    PROP_CODE = 19

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

    def getCode(self):
        return self.code

    def getStreetTexture(self):
        return self.streetTexture

    def getSidewalkTexture(self):
        return self.sidewalkTexture

    def getCurbTexture(self):
        return self.curbTexture

    def getStreetColor(self):
        return self.streetColor

    def getSidewalkColor(self):
        return self.sidewalkColor

    def getCurbColor(self):
        return self.curbColor

    def setStreetTexture(self, texture):
        self.streetTexture = texture

    def setSidewalkTexture(self, texture):
        self.sidewalkTexture = texture

    def setCurbTexture(self, texture):
        self.curbTexture = texture

    def setStreetColor(self, color):
        self.streetColor = color

    def setSidewalkColor(self, color):
        self.SidewalkColor = color

    def setTextureColor(self, color):
        self.Color = color

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
            self._setColorCount = color
        elif self._setColorCount == 1:
            self._setColorCount = color
        elif self._setColorCount == 2:
            self.curbColor = color
        self._setColorCount += 1

    def debug(self, message):
        if self.verbose:
            print 'DNAStreet:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        code = self.getCode()
        data += struct.pack('>B', len(code))  # Code length
        self.debug('packing... code length: {0}'.format(len(code)))
        data += code  # Code
        self.debug('packing... code: {0}'.format(code))

        streetTexture = self.getStreetTexture()
        data += struct.pack('>B', len(streetTexture))  # Street texture length
        self.debug('packing... street texture length: {0}'.format(len(streetTexture)))
        data += streetTexture  # Street texture
        self.debug('packing... street texture: {0}'.format(streetTexture))

        sideWalkTexture = self.getSidewalkTexture()
        data += struct.pack('>B', len(sideWalkTexture))  # Side walk texture length
        self.debug('packing... side walk texture length: {0}'.format(len(sideWalkTexture)))
        data += sideWalkTexture  # Side walk texture
        self.debug('packing... side walk texture: {0}'.format(sideWalkTexture))

        curbTexture = self.getCurbTexture()
        data += struct.pack('>B', len(curbTexture))  # Curb texture length
        self.debug('packing... curb texture length: {0}'.format(len(curbTexture)))
        data += curbTexture  # Curb texture
        self.debug('packing... curbtexture: {0}'.format(curbTexture))

        for component in self.getStreetColor():
            data += struct.pack('>f', component)  # Street color
            self.debug('packing... street color: {0}'.format(component))

        for component in self.getSidewalkColor():
            data += struct.pack('>f', component)  # Side walk color
            self.debug('packing... side walk color: {0}'.format(component))

        for component in self.getCurbColor():
            data += struct.pack('>f', component)  # Curb color
            self.debug('packing... curb color: {0}'.format(component))

        return data
