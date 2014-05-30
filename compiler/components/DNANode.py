import struct

import DNAGroup


class DNANode(DNAGroup.DNAGroup):
    COMPONENT_CODE = 3

    def __init__(self, name):
        DNAGroup.DNAGroup.__init__(self, name)

        self.pos = (0, 0, 0)
        self.hpr = (0, 0, 0)
        self.scale = (1, 1, 1)

    def setPos(self, pos):
        self.pos = pos

    def setHpr(self, hpr):
        self.hpr = hpr

    def setScale(self, scale):
        self.scale = scale

    def debug(self, message):
        if self.verbose:
            print 'DNANode:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNAGroup.DNAGroup.traverse(self, recursive=False, verbose=verbose)

        for component in self.pos:
            data += struct.pack('<f', component)  # Position
            self.debug('packing... position: {0}'.format(component))

        for component in self.hpr:
            data += struct.pack('<f', component)  # Rotation
            self.debug('packing... rotation: {0}'.format(component))

        for component in self.scale:
            data += struct.pack('<f', component)  # Scale
            self.debug('packing... scale: {0}'.format(component))

        if recursive:
            for child in self.children:
                data += child.traverse(recursive=True, verbose=verbose)

        return data
