import struct

import DNANode


class DNALandmarkBuilding(DNANode.DNANode):
    PROP_CODE = 13

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.code = ''
        self.wallColor = (1, 1, 1, 1)
        self.title = ''
        self.article = ''
        self.buildingType = ''

    def setCode(self, code):
        self.code = code

    def getCode(self):
        return self.code

    def setWallColor(self, color):
        self.wallColor = color

    def getWallColor(self):
        return self.wallColor

    def setTitle(self, title):
        self.title = title

    def getTitle(self):
        return self.title

    def setArticle(self, article):
        self.article = article

    def getArticle(self):
        return self.article

    def setBuildingType(self, buildingType):
        self.buildingType = buildingType

    def getBuildingType(self):
        return self.buildingType

    def debug(self, message):
        if self.verbose:
            print 'DNALandmarkBuilding:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)

        code = self.getCode()
        data += struct.pack('>B', len(code))  # Code length
        self.debug('packing... code length: {0}'.format(len(code)))
        data += code
        self.debug('packing... code: {0}'.format(code))

        for component in self.getWallColor():
            data += struct.pack('f', component)  # Wall color
            self.debug('packing... wall color: {0}'.format(component))

        title = self.getTitle()
        if not title:
            data += struct.pack('>B', 0)  # Title length
            self.debug('skipping... title length')
            self.debug('skipping... title')
        else:
            data += struct.pack('>B', len(title))  # Title length
            self.debug('packing... title length: {0}'.format(len(title)))
            data += title  # Title
            self.debug('packing... title: {0}'.format(title))

        article = self.getArticle()
        if not article:
            data += struct.pack('>B', 0)  # Article length
            self.debug('skipping... article length')
            self.debug('skipping... article')
        else:
            data += struct.pack('>B', len(article))  # Article length
            self.debug('packing... article length: {0}'.format(len(article)))
            data += article  # Article
            self.debug('packing... article: {0}'.format(article))

        buildingType = self.getBuildingType()
        if self.getBuildingType():
            data += struct.pack('>B', 0)  # Building type length
            self.debug('skipping... building type length: {0}'.format(len(buildingType)))
            self.debug('skipping... building type: {0}'.format(buildingType))
        else:
            data += struct.pack('>B', len(buildingType))  # Building type length
            self.debug('packing... building type length: {0}'.format(len(buildingType)))
            data += buildingType  # Building type
            self.debug('packing... building type: {0}'.format(buildingType))

        if recursive:
            for child in self.children:
                data += child.traverse(recursive=True, verbose=verbose)

        return data
