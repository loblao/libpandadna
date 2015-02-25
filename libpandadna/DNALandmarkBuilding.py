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
        self.code = dgi.getString()
        self.wallColor = dgi_extract_color(dgi)

    def setupSuitBuildingOrigin(self, a, b):
        _nametb = self.name[:2] == 'tb'
        _isdigit = self.name[2].isdigit()
        _namec = ':' in self.name
        if (_nametb and _isdigit and _namec):
            name = 's' + self.name[1:]
            node = b.find('**/*suit_building_origin')
            if node.isEmpty():
                _emptypr = "%s couldn't find suit building origin!"
                print("DNALandmarkBuilding(warning):" + _emptypr % self.name)
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
