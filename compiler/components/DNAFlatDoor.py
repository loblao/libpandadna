import DNADoor


class DNAFlatDoor(DNADoor.DNADoor):
    COMPONENT_CODE = 18

    def debug(self, message):
        if self.verbose:
            print 'DNAFlatDoor:', message
