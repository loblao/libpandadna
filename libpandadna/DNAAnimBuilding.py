import DNALandmarkBuilding

from common import *

class DNAAnimBuilding(DNALandmarkBuilding.DNALandmarkBuilding):
    COMPONENT_CODE = 16

    def __init__(self, name):
        DNALandmarkBuilding.DNALandmarkBuilding.__init__(self, name)

        self.animName = ''

    def makeFromDGI(self, dgi):
        DNALandmarkBuilding.DNALandmarkBuilding.makeFromDGI(self, dgi)
        self.animName = dgi_extract_string8(dgi)
        
    def traverse(self, np, store):
        result = store.findNode(self.code)
        if not result:
            self.raiseCodeNotFound()
            
        _np = result.copyTo(np)
        _np.setName(self.name)
        _np.setPosHprScale(self.pos, self.hpr, self.scale)
        _np.setTag("DNAAnim", self.animName)
        
        self.setupSuitBuildingOrigin(np, _np)
        
        self.traverseChildren(_np, store)
        
        _np.flattenStrong()
        