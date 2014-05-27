import struct

import DNANode


class DNAFlatBuilding(DNANode.DNANode):
    PROP_CODE = 9

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.width = 0
        self.hasDoor = False

    def setWidth(self, width):
        self.width = width

    def getWidth(self):
        return self.width

    def setHasDoor(self, hasDoor):
        self.hasDoor = True

    def getHasDoor(self):
        return self.hasDoor

    def debug(self, message):
        if self.verbose:
            print 'DNAFlatBuilding:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        data += struct.pack('>B', self.getWidth())  # Width
        self.debug('packing... width: {0}'.format(self.getWidth()))

        data += struct.pack('>?', self.getHasDoor())  # Has door?
        self.debug('packing... has door?: {0}'.format(self.getHasDoor()))

        if recursive:
            for child in self.children:
                data += child.traverse(recursive=True, verbose=verbose)

        return data
