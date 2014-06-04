import struct

import DNALandmarkBuilding


class DNAAnimBuilding(DNALandmarkBuilding.DNALandmarkBuilding):
    COMPONENT_CODE = 16

    def __init__(self, name):
        DNALandmarkBuilding.DNALandmarkBuilding.__init__(self, name)

        self.animName = ''

    def setAnim(self, anim):
        self.animName = anim

    def debug(self, message):
        if self.verbose:
            print 'DNAAnimBuilding:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNALandmarkBuilding.DNALandmarkBuilding.traverse(self, recursive=False, verbose=verbose)

        if not self.animName:
            data += struct.pack('<B', 0)  # Anim name length
            self.debug('skipping... anim name length')
            self.debug('skipping... anim name')
        else:
            data += struct.pack('<B', len(self.animName))  # Anim name length
            self.debug('packing... anim name length: {0}'.format(len(self.animName)))
            data += self.animName  # Anim name
            self.debug('packing... anim name: {0}'.format(self.animName))

        if recursive:
            data += self.recurse(verbose)

        return data
