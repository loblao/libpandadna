from DNAGroupStuff import DNAGroup
    
from direct.distributed.PyDatagram import PyDatagram
    
class DNANode(DNAGroup):
    PROP_CODE = 3
    def __init__(self, name):
        DNAGroup.__init__(self, name)
        self.pos = (0, 0, 0)
        self.hpr = (0, 0, 0)
        self.scale = (1, 1, 1)

    def getPos(self):
        return self.pos

    def getHpr(self):
        return self.hpr

    def getScale(self):
        return self.scale

    def setPos(self, pos):
        self.pos = pos

    def setHpr(self, hpr):
        self.hpr = hpr

    def setScale(self, scale):
        self.scale = scale

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        for x in self.pos: dg.addInt32(int(x * 100)) # same dc file trick
        for x in self.hpr: dg.addInt16(int(x * 10))
        for x in self.scale: dg.addInt16(int(x * 10))
        dg.addString(self.name)
        
        data += packer(dg.getMessage())
        
        for child in self.children:
            data += packer(child.traverse(packer))
            
        return data

class DNAProp(DNANode):
    PROP_CODE = 4
    def __init__(self, name):
        DNANode.__init__(self, name)
        self.code = ''
        self.color = (1, 1, 1, 1)

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def getCode(self):
        return self.code

    def getColor(self):
        return self.color

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        for x in self.pos: dg.addInt32(int(x * 100)) # same dc file trick
        for x in self.hpr: dg.addInt16(int(x * 10))
        for x in self.scale: dg.addInt16(int(x * 100))
        dg.addString(self.code)
        dg.addString(self.name)
        for x in self.color: dg.addUint8(int(x * 255))
        
        data += packer(dg.getMessage())
        
        for child in self.children:
            data += packer(child.traverse(packer))
            
        return data
        
class DNASign(DNANode):
    PROP_CODE = 5
    def __init__(self):
        DNANode.__init__(self, '')
        self.code = ''
        self.color = (1, 1, 1, 1)

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def getCode(self):
        return self.code

    def getColor(self):
        return self.color

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        for x in self.pos: dg.addInt32(int(x * 100)) # same dc file trick
        for x in self.hpr: dg.addInt16(int(x * 10))
        for x in self.scale: dg.addInt16(int(x * 10))
        dg.addString(self.code)
        for x in self.color: dg.addUint8(x * 255)
        
        data += packer(dg.getMessage())
        
        for child in self.children:
            data += packer(child.traverse(packer))
            
        return data
        