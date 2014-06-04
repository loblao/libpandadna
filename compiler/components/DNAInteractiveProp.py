import struct

import DNAAnimProp


class DNAInteractiveProp(DNAAnimProp.DNAAnimProp):
    COMPONENT_CODE = 15

    def __init__(self, name):
        DNAAnimProp.DNAAnimProp.__init__(self, name)

        self.cellId = -1

    def setCellId(self, cellId):
        self.cellId = cellId

    def debug(self, message):
        if self.verbose:
            print 'DNAAnimProp:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNAAnimProp.DNAAnimProp.traverse(self, recursive=False, verbose=verbose)

        data += struct.pack('h', self.cellId)  # Cell ID
        self.debug('packing... cell ID: {0}'.format(self.cellId))

        if recursive:
            data += self.recurse(verbose)

        return data
