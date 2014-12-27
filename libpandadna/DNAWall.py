import DNANode

from common import *

class DNAWall(DNANode.DNANode):
    COMPONENT_CODE = 10

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.code = ''
        self.height = 10
        self.color = (1, 1, 1, 1)

    def makeFromDGI(self, dgi):
        DNANode.DNANode.makeFromDGI(self, dgi)
        
        self.code = dgi_extract_string8(dgi)
        self.height = dgi.getInt16() / 100.0
        self.color = dgi_extract_color(dgi)
        
    def traverse(self, np, store):
        from DNAFlatBuilding import DNAFlatBuilding
        
        result = store.findNode(self.code)
        if result is None:
            self.raiseCodeNotFound()
            
        _np = result.copyTo(np)

        pos = Point3(self.pos)
        pos.setZ(DNAFlatBuilding.currentWallHeight)
        
        scale = Point3(self.scale)
        scale.setZ(self.height)

        _np.setPosHprScale(pos, self.hpr, scale)
        _np.setColor(self.color);

        self.traverseChildren(_np, store)

        DNAFlatBuilding.currentWallHeight += self.height
        