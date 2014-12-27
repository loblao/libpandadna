import DNAProp

class DNASignGraphic(DNAProp.DNAProp):
    COMPONENT_CODE = 8

    def __init__(self, name):
        DNAProp.DNAProp.__init__(self, name)

        self.width = 0
        self.height = 0
        self.bDefaultColor = True

    def makeFromDGI(self, dgi):
        DNAProp.DNAProp.makeFromDGI(self, dgi)
        
        self.width = dgi.getInt16() / 100.0
        self.height = dgi.getInt16() / 100.0
        self.bDefaultColor = dgi.getBool()
        
    def traverse(self, np, store):
        result = store.findNode(self.code)
        if result is None:
            self.raiseCodeNotFound()
            
        _np = result.copyTo(np)
        _np.setScale(self.scale)
        _np.setScale(_np, self.getParent().scale)
        _np.setPosHpr(self.pos, self.hpr)
        
        self.traverseChildren(_np, store)
        