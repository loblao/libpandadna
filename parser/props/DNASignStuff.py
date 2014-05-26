from DNANode import DNANode
from direct.distributed.PyDatagram import PyDatagram
class DNASignBaseline(DNANode):
    PROP_CODE = 6
    def __init__(self):
        DNANode.__init__(self, '')
        self.code = ''
        self.color = (1, 1, 1, 1)
        self.font = None
        self.flags = ''
        self.indent = 0.0
        self.kern = 0.0
        self.wiggle = 0.0
        self.stumble = 0.0
        self.stomp = 0.0
        self.width = 0
        self.height = 0

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def getCode(self):
        return self.code

    def getColor(self):
        return self.color

    def getFont(self):
        return self.font

    def getHeight(self):
        return self.height

    def getIndent(self):
        return self.indent

    def getKern(self):
        return self.kern

    def getStomp(self):
        return self.stomp

    def getStumble(self):
        return self.stumble

    def getWidth(self):
        return self.width

    def getWiggle(self):
        return self.wiggle

    def setFont(self, font):
        self.font = font

    def setHeight(self, height):
        self.height = height

    def setIndent(self, indent):
        self.indent = indent

    def setKern(self, kern):
        self.kern = kern

    def setStomp(self, stomp):
        self.stomp = stomp

    def setStumble(self, stumble):
        self.stumble = stumble

    def setWidth(self, width):
        self.width = width

    def setWiggle(self, wiggle):
        self.wiggle = wiggle

    def setFlags(self, flags):
        self.flags = flags

    def getFlags(self):
        return self.flags

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        for x in self.pos: dg.addInt32(int(x * 100)) # same dc file trick
        for x in self.hpr: dg.addInt16(int(x * 10))
        
        #dg.addString(self.code) # not sure if its used
        #for x in self.color: dg.addUint8(x * 255) # not sure if its used
        
        data += packer(dg.getMessage())
        
        for child in self.children:
            data += packer(child.traverse(packer))
            
        return data
        # To do (Cody): most vars are not used???

class DNASignText(DNANode):
    PROP_CODE = 7
    def __init__(self):
        DNANode.__init__(self, '')
        self.letters = ''

    def setLetters(self, letters):
        self.letters = letters

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        dg.addString(self.letters)
        
        data += packer(dg.getMessage())
        
        #no children
            
        return data

class DNASignGraphic(DNANode):
    PROP_CODE = 8
    def __init__(self, name):
        DNANode.__init__(self, name)
        self.code = ''
        self.color = (1,1,1,1)
        self.width = 0
        self.height = 0
        self.bDefaultColor = True

    def getWidth(self):
        return self.width

    def getHeight(self):
        return self.height

    def getCode(self):
        return self.code

    def getColor(self):
        return self.Color

    def setWidth(self, width):
        self.width = width

    def setHeight(self, height):
        self.height = height

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color
        self.bDefaultColor = False
        
    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        dg.addString(self.name)
        dg.addString(self.code)
        for x in self.pos: dg.addInt32(int(x * 100))
        for x in self.hpr: dg.addInt16(int(x * 10))
        for x in self.scale: dg.addInt16(x * 100)
        
        data += packer(dg.getMessage())
        
        for child in self.children:
            data += packer(child.traverse(packer))
            
        return data
        