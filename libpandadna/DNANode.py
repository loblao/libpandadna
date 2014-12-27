import DNAGroup

class DNANode(DNAGroup.DNAGroup):
    COMPONENT_CODE = 3

    def __init__(self, name):
        DNAGroup.DNAGroup.__init__(self, name)

        self.pos = (0, 0, 0)
        self.hpr = (0, 0, 0)
        self.scale = (1, 1, 1)

    def makeFromDGI(self, dgi):
        DNAGroup.DNAGroup.makeFromDGI(self, dgi)
        
        self.pos = tuple(dgi.getInt32() / 100.0 for _ in xrange(3))
        self.hpr = tuple(dgi.getInt32() / 100.0 for _ in xrange(3))
        self.scale = tuple(dgi.getInt16() / 100.0 for _ in xrange(3))
        
    def getPos(self):
        return self.pos
        
    def getHpr(self):
        return self.hpr
        
    def getScale(self):
        return self.scale
        
    def traverse(self, np, store):
        _np = np.attachNewNode(self.name)
        _np.setPosHprScale(self.pos, self.hpr, self.scale)
        self.traverseChildren(_np, store)