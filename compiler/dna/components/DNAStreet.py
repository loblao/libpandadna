import DNANode
from dna.base.DNAPacker import *


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

    def traverse(self, recursive=True, verbose=False):
        packer = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)
        packer.name = 'DNAStreet'  # Override the name for debugging.

        packer.pack('code', self.code, SHORT_STRING)
        packer.pack('street texture', self.streetTexture, SHORT_STRING)
        packer.pack('side walk texture', self.sideWalkTexture, SHORT_STRING)
        packer.pack('curb texture', self.curbTexture, SHORT_STRING)
        packer.packColor('street color', *self.streetColor)
        packer.packColor('side walk color', *self.sideWalkColor)
        packer.packColor('curb color', *self.curbColor)

        return packer
