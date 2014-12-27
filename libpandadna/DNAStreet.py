import DNANode

from common import *

class DNAStreet(DNANode.DNANode):
    COMPONENT_CODE = 19

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.code = ''
        self.streetTexture = ''
        self.sideWalkTexture = ''
        self.curbTexture = ''
        self.streetColor = (1, 1, 1, 1)
        self.sideWalkColor = (1, 1, 1, 1)
        self.curbColor = (1, 1, 1, 1)

    def makeFromDGI(self, dgi):
        DNANode.DNANode.makeFromDGI(self, dgi)
        
        self.code = dgi_extract_string8(dgi)
        self.streetTexture = dgi_extract_string8(dgi)
        self.sidewalkTexture = dgi_extract_string8(dgi)
        self.curbTexture = dgi_extract_string8(dgi)

        self.streetColor = dgi_extract_color(dgi)
        self.sideWalkColor = dgi_extract_color(dgi)
        self.curbColor = dgi_extract_color(dgi)
        
    def getTexture(self, texture, store):
        if not texture:
            return
            
        tex = store.findTexture(texture)
        if tex is None:
            self.raiseCodeNotFound('texture: ' + texture)
            
        return tex
        
    def traverse(self, np, store):
        node = store.findNode(self.code)
        if node is None:
            self.raiseCodeNotFound()
            
        _np = node.copyTo(np)
        
        node.setName(self.name)
        
        streetTexture = self.getTexture(self.streetTexture, store)
        sidewalkTexture = self.getTexture(self.sidewalkTexture, store)
        curbTexture = self.getTexture(self.curbTexture, store)

        streetNode = _np.find('**/*_street')
        sidewalkNode = _np.find('**/*_sidewalk')
        curbNode = _np.find('**/*_curb')

        if not streetNode.isEmpty() and streetTexture:
            streetNode.setTexture(streetTexture, 1)
            streetNode.setColorScale(self.streetColor)
            
        if not sidewalkNode.isEmpty() and sidewalkTexture:
            sidewalkNode.setTexture(sidewalkTexture, 1)
            sidewalkNode.setColorScale(self.sideWalkColor)
            
        if not curbNode.isEmpty() and curbTexture:
            curbNode.setTexture(curbTexture, 1)
            curbNode.setColorScale(self.curbColor)

        _np.setPosHprScale(self.pos, self.hpr, self.scale)
