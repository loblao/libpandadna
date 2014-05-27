import struct

import DNALandmarkBuilding


class DNAAnimBuilding(DNALandmarkBuilding.DNALandmarkBuilding):
    PROP_CODE = 16

    def __init__(self, name):
        DNALandmarkBuilding.DNALandmarkBuilding.__init__(self, name)

        self.animName = ''

    def setAnim(self, anim):
        self.animName = anim

    def getAnim(self):
        return self.animName

    def debug(self, message):
        if self.verbose:
            print 'DNAAnimBuilding:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNALandmarkBuilding.DNALandmarkBuilding.traverse(self, recursive=False, verbose=verbose)

        animName = self.getAnim()
        if not animName:
            data += struct.pack('>B', 0)  # Anim name length
            self.debug('skipping... anim name length')
            self.debug('skipping... anim name')
        else:
            data += struct.pack('>B', len(animName))  # Anim name length
            self.debug('packing... anim name length: {0}'.format(len(animName)))
            data += animName  # Anim name
            self.debug('packing... anim name: {0}'.format(animName))

        if recursive:
            for child in self.children:
                data += child.traverse(recursive=True, verbose=verbose)

        return data
