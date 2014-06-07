import struct

import DNANode


class DNALandmarkBuilding(DNANode.DNANode):
    COMPONENT_CODE = 13

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.code = ''
        self.wallColor = (1, 1, 1, 1)
        self.title = ''
        self.article = ''
        self.buildingType = ''

    def setCode(self, code):
        self.code = code

    def setWallColor(self, color):
        self.wallColor = color

    def setTitle(self, title):
        self.title = title

    def setArticle(self, article):
        self.article = article

    def setBuildingType(self, buildingType):
        self.buildingType = buildingType

    def debug(self, message):
        if self.verbose:
            print 'DNALandmarkBuilding:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        self.debug('packing... code length: {0}'.format(len(self.code)))
        data += struct.pack('<B', len(self.code))  # Code length
        self.debug('packing... code: {0}'.format(self.code))
        data += self.code

        for component in self.wallColor:
            self.debug('packing... wall color: {0}'.format(component))
            data += struct.pack('B', int(component * 255))  # Wall color

        if not self.title:
            self.debug('skipping... title length')
            self.debug('skipping... title')
            data += struct.pack('<B', 0)  # Title length
        else:
            self.debug('packing... title length: {0}'.format(len(self.title)))
            data += struct.pack('<B', len(self.title))  # Title length
            self.debug('packing... title: {0}'.format(self.title))
            data += self.title  # Title

        if not self.article:
            self.debug('skipping... article length')
            self.debug('skipping... article')
            data += struct.pack('<B', 0)  # Article length
        else:
            self.debug('packing... article length: {0}'.format(len(self.article)))
            data += struct.pack('<B', len(self.article))  # Article length
            self.debug('packing... article: {0}'.format(self.article))
            data += self.article  # Article

        if not self.buildingType:
            self.debug('skipping... building type length')
            self.debug('skipping... building type')
            data += struct.pack('<B', 0)  # Building type length
        else:
            self.debug('packing... building type length: {0}'.format(len(self.buildingType)))
            data += struct.pack('<B', len(self.buildingType))  # Building type length
            self.debug('packing... building type: {0}'.format(self.buildingType))
            data += self.buildingType  # Building type

        if recursive:
            data += self.traverseChildren(verbose=verbose)

        return data
