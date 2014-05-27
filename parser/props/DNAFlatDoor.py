import struct

import DNADoor


class DNAFlatDoor(DNADoor.DNADoor):
    PROP_CODE = 18

    def debug(self, message):
        if self.verbose:
            print 'DNAFlatDoor:', message
