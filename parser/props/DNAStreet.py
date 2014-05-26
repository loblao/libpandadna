from DNANode import *
from direct.distributed.PyDatagram import PyDatagram

class DNAStreet(DNANode):
    PROP_CODE = 19
    def __init__(self, name):
        DNANode.__init__(self, name)
        self.code = ''
        self.streetTexture = ''
        self.sideWalkTexture = ''
        self.curbTexture = ''
        self.streetColor = (1,1,1,1)
        self.sidewalkColor = (1,1,1,1)
        self.curbColor = (1,1,1,1)
        self.setTexCnt = 0
        self.setColCnt = 0

    def setCode(self, code):
        self.code = code

    def getCode(self):
        return self.code

    def getStreetTexture(self):
        return self.streetTexture

    def getSidewalkTexture(self):
        return self.sidewalkTexture

    def getCurbTexture(self):
        return self.curbTexture

    def getStreetColor(self):
        return self.streetColor

    def getSidewalkColor(self):
        return self.sidewalkColor

    def getCurbColor(self):
        return self.curbColor

    def setStreetTexture(self, texture):
        self.streetTexture = texture

    def setSidewalkTexture(self, texture):
        self.sidewalkTexture = texture

    def setCurbTexture(self, texture):
        self.curbTexture = texture

    def setStreetColor(self, color):
        self.streetColor = color

    def setSidewalkColor(self, color):
        self.SidewalkColor = color

    def setTextureColor(self, color):
        self.Color = color

    def setTexture(self, texture):
        if self.setTexCnt == 0:
            self.streetTexture = texture
        if self.setTexCnt == 1:
            self.sidewalkTexture = texture
        if self.setTexCnt == 2:
            self.curbTexture = texture
        self.setTexCnt += 1

    def setColor(self, color):
        if self.setColCnt == 0:
            self.streetColor = color
        if self.setColCnt == 1:
            self.sidewalkColor = color
        if self.setColCnt == 2:
            self.curbColor = color
        self.setColCnt += 1

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        dg.addString(self.name)
        for x in self.pos: dg.addInt32(int(x * 100)) # same dc file trick
        for x in self.hpr: dg.addInt16(int(x * 10))
        for x in self.scale: dg.addInt16(int(x * 100))
        
        dg.addString(self.code)
        dg.addString(self.streetTexture)
        dg.addString(self.sideWalkTexture)
        dg.addString(self.curbTexture)
        
        for C in (self.streetColor ,self.sidewalkColor, self.curbColor):
            for x in C:
                dg.addUint8(x * 255)
        
        dg.addUint8(self.setTexCnt)
        dg.addUint8(self.setColCnt)
        
        data += packer(dg.getMessage())
            
        return data