import struct

import DNANode


class DNASignText(DNANode.DNANode):
    PROP_CODE = 7

    def __init__(self):
        DNANode.DNANode.__init__(self, '')

        self.letters = ''

    def setLetters(self, letters):
        self.letters = letters

    def getLetters(self):
        return self.letters

    def debug(self, message):
        if self.verbose:
            print 'DNASignText:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        letters = self.getLetters()
        data += struct.pack('>B', len(letters))  # Letters length
        self.debug('packing... letters length: {0}'.format(len(letters)))
        data += letters  # Letters
        self.debug('packing... letters: {0}'.format(letters))

        return data
