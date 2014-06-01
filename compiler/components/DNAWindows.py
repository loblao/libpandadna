import struct

import DNAGroup


class DNAWindows(DNAGroup.DNAGroup):
    COMPONENT_CODE = 11

    def __init__(self, name):
        DNAGroup.DNAGroup.__init__(self, name)

        self.code = ''
        self.color = (1, 1, 1, 1)
        self.windowCount = 1

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def setWindowCount(self, count):
        self.windowCount = count

    def debug(self, message):
        if self.verbose:
            print 'DNAWindows:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNAGroup.DNAGroup.traverse(self, recursive=False, verbose=verbose)

        data += struct.pack('<B', len(self.code))  # Code length
        self.debug('packing... code length: {0}'.format(len(self.code)))
        data += self.code  # Code
        self.debug('packing... code: {0}'.format(self.code))

        for component in self.color:
            data += struct.pack('B', int(component * 255))  # Color
            self.debug('packing... color: {0}'.format(component))

        data += struct.pack('<B', self.windowCount)  # Window count
        self.debug('packing... window count: {0}'.format(self.windowCount))

        return data
