import DNANode

from common import *

class DNASignBaseline(DNANode.DNANode):
    COMPONENT_CODE = 6

    def __init__(self):
        DNANode.DNANode.__init__(self, '')

        self.data = ""
        
    def makeFromDGI(self, dgi):
        DNANode.DNANode.makeFromDGI(self, dgi)
        
        self.data = dgi.getString()
        if len(self.data):
            self.data = decompressString(self.data)
            
    def traverse(self, np, store):
        _np = np.attachNewNode("baseline")
        _np.setPos(self.pos)
        _np.setHpr(self.hpr)
        _np.setDepthOffset(50)

        if self.data:
            bf = BamFile()
            ss = StringStream()
            ss.setData(self.data)
            bf.openRead(ss)
            
            node = NodePath(bf.readNode())
            node.reparentTo(_np)

        self.traverseChildren(_np, store)
        