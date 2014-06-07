import DNANode
from DNAPacker import *


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

    def traverse(self, recursive=True, verbose=False):
        packer = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)
        packer.name = 'DNAStreet'  # Override the name for debugging.

        packer.pack('code', self.code, SHORT_STRING)
        packer.pack('street texture', self.streetTexture, SHORT_STRING)
        packer.pack('side walk texture', self.sideWalkTexture, SHORT_STRING)
        packer.pack('curb texture', self.curbTexture, SHORT_STRING)

        for component in self.streetColor:
            packer.pack('street color', int(component * 255), UINT8)
        for component in self.sidewalkColor:
            packer.pack('side walk color', int(component * 255), UINT8)
        for component in self.curbColor:
            packer.pack('curb color', int(component * 255), UINT8)

        return packer
