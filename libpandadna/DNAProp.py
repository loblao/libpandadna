import DNANode

from common import *

class DNAProp(DNANode.DNANode):
    COMPONENT_CODE = 4

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.code = ''
        self.color = (1, 1, 1, 1)

    def makeFromDGI(self, dgi):
        DNANode.DNANode.makeFromDGI(self, dgi)
        
        self.code = dgi_extract_string8(dgi)
        self.color = dgi_extract_color(dgi)
        
    def traverse(self, np, store):
        if self.code == "DCS":
            node = ModelNode(self.name)
            node.setPreserveTransform(ModelNode.PTNet)
            _np = np.attachNewNode(node)
            
        else:
            result = store.findNode(self.code)
            if not result:
                return
                
            _np = result.copyTo(np)
        
        _np.setName(self.name)
        
        _np.setPosHprScale(self.pos, self.hpr, self.scale)
        _np.setColorScale(self.color)
        
        self.traverseChildren(_np, store)
        