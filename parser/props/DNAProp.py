import struct
RECURSIVE_DUMP_EXCLUDE = ['DNAModel']

class DNAProp:
    def __init__(self, parent):
        self.__children = []
        self.__parent = parent
        
    def getChildren(self):
        return self.__children
        
    def addChild(self, c):
        self.__children.append(c)
        
    def getParent(self):
        return self.__parent
        
    def dumpRecursive(self, data, packer):
        # subclasses should avoid at most cost
        # overwriting this
        d = self.getDumpData()
        data += struct.pack('>h', self.PROP_CODE)
        data += packer(d)
        for child in self.getChildren():
            if child.__class__.__name__ not in RECURSIVE_DUMP_EXCLUDE:
                data += child.dumpRecursive(data, packer)
                
        return data