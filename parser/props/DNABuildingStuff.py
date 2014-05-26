from DNANode import *
from direct.distributed.PyDatagram import PyDatagram

class DNAFlatBuilding(DNANode):
    PROP_CODE = 9

    def __init__(self, name):
        DNANode.__init__(self, name)
        self.hasDoor = False

    def getWidth(self):
        return self.width

    def setWidth(self, width):
        self.width = width

    def setHasDoor(self, hasDoor):
        self.hasDoor = True

    def getHasDoor(self):
        return self.hasDoor
        
    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        dg.addString(self.name)
        for x in self.pos: dg.addInt32(int(x * 100)) # same dc file trick
        for x in self.hpr: dg.addInt16(int(x * 10))
        for x in self.scale: dg.addInt16(int(x * 100))
        #dg.addString(self.code)
        #for x in self.color: dg.addUint8(x * 255)
        dg.addUint16(self.width * 10) # not sure if decimal is needed here
        dg.addBool(self.hasDoor)
        
        data += packer(dg.getMessage())
        
        for child in self.children:
            data += packer(child.traverse(packer))
            
        return data

class DNAWall(DNANode):
    PROP_CODE = 10
    def __init__(self, name):
        DNANode.__init__(self, name)
        self.code = ''
        self.height = 10
        self.color = (1, 1, 1, 1)

    def getCode(self):
        return self.code

    def getColor(self):
        return self.color

    def getHeight(self):
        return self.height

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def setHeight(self, height):
        self.height = height

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        dg.addString(self.name)
        for x in self.pos: dg.addInt32(int(x * 100)) # same dc file trick
        for x in self.hpr: dg.addInt16(int(x * 10))
        for x in self.scale: dg.addInt16(int(x * 100))
        dg.addString(self.code)
        for x in self.color: dg.addUint8(x * 255)
        dg.addUint16(self.height * 10) # not sure if decimal is needed here
        
        data += packer(dg.getMessage())
        
        for child in self.children:
            data += packer(child.traverse(packer))
            
        return data

class DNAWindows(DNAGroup):
    PROP_CODE = 11
    def __init__(self, name):
        DNAGroup.__init__(self, name)
        self.setCode('')
        self.setColor((1, 1, 1, 1))
        self.setWindowCount(1)

    def getCode(self):
        return self.code

    def getColor(self):
        return self.color

    def getWindowCount(self):
        return self.windowCount

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def setWindowCount(self, count):
        self.windowCount = count

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        dg.addString(self.name)
        dg.addString(self.code)
        for x in self.color: dg.addUint8(x * 255)
        dg.addUint8(self.windowCount)
        
        data += packer(dg.getMessage())
            
        return data

class DNACornice(DNAGroup):
    PROP_CODE = 12
    def __init__(self, name):
        DNAGroup.__init__(self, name)
        self.setCode('')
        self.setColor((1, 1, 1, 1))

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

class DNALandmarkBuilding(DNANode):
    PROP_CODE = 13
    def __init__(self, name):
        DNANode.__init__(self, name)
        self.code = ''
        self.wallColor = (1,1,1,1)
        self.title = ''
        self.article = ''
        self.buildingType = ''
        self.door = None

    def getArticle(self):
        return self.article

    def getBuildingType(self):
        return self.buildingType

    def getTitle(self):
        return self.title

    def setCode(self, code):
        self.code = code

    def setWallColor(self, color):
        self.wallColor = color

    def getCode(self):
        return self.code

    def getWallColor(self):
        return self.wallColor

    def setArticle(self, article):
        self.article = article

    def setBuildingType(self, buildingType):
        self.buildingType = buildingType

    def setTitle(self, title):
        self.title = title

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        dg.addString(self.name)
        for x in self.pos: dg.addInt32(int(x * 100)) # same dc file trick
        for x in self.hpr: dg.addInt16(int(x * 10))
        for x in self.scale: dg.addInt16(int(x * 100))
        dg.addString(self.code)
        #for x in self.color: dg.addUint8(x * 255)
        for x in self.wallColor: dg.addInt8(x * 255)
        dg.addString(self.article)
        dg.addString(self.buildingType)
        dg.addString(self.title)
        
        data += packer(dg.getMessage())
        
        for child in self.children:
            data += packer(child.traverse(packer))
            
        return data

class DNAAnimProp(DNAProp):
    PROP_CODE = 14
    def __init__(self, name):
        DNAProp.__init__(self, name)
        self.animName = ''

    def setAnim(self, anim):
        self.animName = anim

    def getAnim(self):
        return self.animName

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        dg.addString(self.name)
        for x in self.pos: dg.addInt32(int(x * 100)) # same dc file trick
        for x in self.hpr: dg.addInt16(int(x * 10))
        for x in self.scale: dg.addInt16(int(x * 100))
        dg.addString(self.code)
        for x in self.color: dg.addUint8(x * 255)
        dg.addString(self.animName)
        
        data += packer(dg.getMessage())
        
        for child in self.children:
            data += packer(child.traverse(packer))
            
        return data
        
class DNAInteractiveProp(DNAAnimProp):
    PROP_CODE = 15
    def __init__(self, name):
        DNAAnimProp.__init__(self, name)
        self.cellId = -1

    def setCellId(self, id):
        self.cellId = id

    def getCellId(self):
        return cellId

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        dg.addString(self.name)
        for x in self.pos: dg.addInt32(int(x * 100)) # same dc file trick
        for x in self.hpr: dg.addInt16(int(x * 10))
        for x in self.scale: dg.addInt16(int(x * 100))
        dg.addString(self.code)
        for x in self.color: dg.addUint8(x * 255)
        dg.addString(self.animName)
        
        data += packer(dg.getMessage())
        
        for child in self.children:
            data += packer(child.traverse(packer))
            
        return data

class DNAAnimBuilding(DNALandmarkBuilding):
    PROP_CODE = 16
    def __init__(self, name):
        DNALandmarkBuilding.__init__(self, name)
        self.animName = ''

    def setAnim(self, anim):
        self.animName = anim

    def getAnim(self):
        return self.animName

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        
        dg = PyDatagram()
        dg.addString(self.name)
        for x in self.pos: dg.addInt32(int(x * 100)) # same dc file trick
        for x in self.hpr: dg.addInt16(int(x * 10))
        for x in self.scale: dg.addInt16(int(x * 100))
        dg.addString(self.code)
        #for x in self.color: dg.addUint8(x * 255)
        for x in self.wallColor: dg.addInt8(x * 255)
        dg.addString(self.article)
        dg.addString(self.buildingType)
        dg.addString(self.title)
        dg.addString(self.animName)
        
        data += packer(dg.getMessage())
        
        for child in self.children:
            data += packer(child.traverse(packer))
            
        return data
