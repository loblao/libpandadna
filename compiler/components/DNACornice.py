import struct

import DNAGroup


class DNACornice(DNAGroup.DNAGroup):
    COMPONENT_CODE = 12

    def __init__(self, name):
        DNAGroup.DNAGroup.__init__(self, name)

        self.code = ''
        self.color = (1, 1, 1, 1)

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def debug(self, message):
        if self.verbose:
            print 'DNACornice:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNAGroup.DNAGroup.traverse(self, recursive=False, verbose=verbose)

        self.debug('packing... code length: {0}'.format(len(self.code)))
        data += struct.pack('<B', len(self.code))  # Code length
        self.debug('packing... code: {0}'.format(self.code))
        data += self.code  # Code

        for component in self.color:
            self.debug('packing... color: {0}'.format(component))
            data += struct.pack('B', int(component * 255))  # Color

        return data
