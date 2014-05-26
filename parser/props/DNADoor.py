from DNAGroupStuff import *
from direct.distributed.PyDatagram import PyDatagram

class DNADoor(DNAGroup):
    PROP_CODE = 17
    def __init__(self, name):
        DNAGroup.__init__(self, name)
        self.code = ''
        self.color = (1,1,1,1)

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
        dg.addString(self.name)
        dg.addString(self.code)
        for x in self.color: dg.addUint8(x * 255)
        
        data += packer(dg.getMessage())
            
        return data
       
class DNAFlatDoor(DNADoor):
    PROP_CODE = 18
