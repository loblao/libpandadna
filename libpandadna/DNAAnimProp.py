import DNAProp

from common import *

from panda3d.core import ModelNode

class DNAAnimProp(DNAProp.DNAProp):
    COMPONENT_CODE = 14

    def __init__(self, name):
        DNAProp.DNAProp.__init__(self, name)

        self.animName = ''

    def makeFromDGI(self, dgi):
        DNAProp.DNAProp.makeFromDGI(self, dgi)
        self.animName = dgi_extract_string8(dgi)
        
    def traverse(self, np, store):
        if self.code == "DCS":
            node = ModelNode(self.name)
            node.setPreserveTransform(ModelNode.PTNet)
            _np = np.attachNewNode(np)
            
        else:
            _np = store.findNode(self.code).copyTo(np)
            _np.setName(self.name)
            
        _np.setTag("DNAAnim", self.animName)
        
        _np.setPosHprScale(self.pos, self.hpr, self.scale)
        _np.setColorScale(self.color)
        
        self.traverseChildren(_np, store)
        