import DNAAnimProp

class DNAInteractiveProp(DNAAnimProp.DNAAnimProp):
    COMPONENT_CODE = 15

    def __init__(self, name):
        DNAAnimProp.DNAAnimProp.__init__(self, name)

        self.cellId = -1
        
    def getCellId(self):
        return self.cellId
        
    def makeFromDGI(self, dgi):
        DNAAnimProp.DNAAnimProp.makeFromDGI(self, dgi)
        self.cellId = dgi.getInt16()
        
    def traverse(self, np, store):
        if self.code == "DCS":
            node = ModelNode(self.name)
            node.setPreserveTransform(ModelNode.PTNet)
            _np = np.attachNewNode(np)
            
        else:
            _np = store.findNode(self.code).copyTo(np)
            _np.setName(self.name)
            
        _np.setTag("DNAAnim", self.animName)
        _np.setTag("DNACellIndex", str(self.cellId))
        
        _np.setPosHprScale(self.pos, self.hpr, self.scale)
        _np.setColorScale(self.color)
        
        self.traverseChildren(_np, store)