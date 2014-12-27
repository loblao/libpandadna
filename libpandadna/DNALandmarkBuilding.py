import DNANode

from common import *

class DNALandmarkBuilding(DNANode.DNANode):
    COMPONENT_CODE = 13

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.code = ''
        self.wallColor = (1, 1, 1, 1)
        self.title = ''
        self.article = ''
        self.buildingType = ''

    def makeFromDGI(self, dgi):
        DNANode.DNANode.makeFromDGI(self, dgi)
        
        self.code = dgi_extract_string8(dgi)
        self.wallColor = dgi_extract_color(dgi)
        self.title = dgi_extract_string8(dgi)
        self.article = dgi_extract_string8(dgi)
        self.buildingType = dgi_extract_string8(dgi)
        
    def setupSuitBuildingOrigin(self, a, b):
        if ((self.name[:2] == 'tb') and (self.name[2].isdigit()) and (':' in self.name)):
            name = "s" + self.name[1:]
            node = b.find("**/*suit_building_origin")
            
            if node.isEmpty():
                print "DNALandmarkBuilding(warning): %s couldn't find suit building origin!" % self.name
                node = a.attachNewNode(name)
                node.setPosHprScale(self.pos, self.hpr, self.scale)
                
            else:
                node.wrtReparentTo(a)
                node.setName(name)
        
    def traverse(self, np, store):
        result = store.findNode(self.code)
        if result is None:
            self.raiseCodeNotFound()
            
        _np = result.copyTo(np)
        _np.setName(self.name)
        
        _np.setPosHprScale(self.pos, self.hpr, self.scale)
        
        if store.allowSuitOrigin(_np):
            self.setupSuitBuildingOrigin(np, _np)
        
        self.traverseChildren(_np, store)
        
        if store.allowLandmarkFlatten(_np):
            _np.flattenStrong()
