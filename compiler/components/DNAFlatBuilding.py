import struct

import DNANode


class DNAFlatBuilding(DNANode.DNANode):
    COMPONENT_CODE = 9

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.width = 0
        self.hasDoor = False

    def setWidth(self, width):
        self.width = width

    def setHasDoor(self, hasDoor):
        self.hasDoor = True

    def debug(self, message):
        if self.verbose:
            print 'DNAFlatBuilding:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        self.debug('packing... width: {0}'.format(self.width))
        data += struct.pack('<B', self.width)  # Width

        self.debug('packing... has door?: {0}'.format(self.hasDoor))
        data += struct.pack('>?', self.hasDoor)  # Has door?

        if recursive:
            data += self.traverseChildren(verbose=verbose)

        return data
