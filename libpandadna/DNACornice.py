import DNAGroup

from common import *

class DNACornice(DNAGroup.DNAGroup):
    COMPONENT_CODE = 12

    def __init__(self, name):
        DNAGroup.DNAGroup.__init__(self, name)
        
        self.code = ''
        self.color = (1, 1, 1, 1)
        
    def makeFromDGI(self, dgi):
        DNAGroup.DNAGroup.makeFromDGI(self, dgi)
        
        self.code = dgi_extract_string8(dgi)
        self.color = dgi_extract_color(dgi)

    def traverse(self, np, store):
        pParentXScale = np.getParent().getScale().getX()
        parentZScale = np.getScale().getZ()
        
        scaleRatio = pParentXScale/parentZScale
        
        node = store.findNode(self.code)
        if not node:
            self.raiseCodeNotFound()
            
        internalNode = np.attachNewNode('cornice-internal')
        node = node.find('**/*_d')
        
        _np = node.copyTo(internalNode, 0)
        _np.setScale(1, scaleRatio, scaleRatio)
        _np.setEffect(DecalEffect.make())
        
        node = node.getParent().find('**/*_nd')
        np_d = node.copyTo(internalNode, 1)
        np_d.setScale(1, scaleRatio, scaleRatio)
        
        internalNode.setZ(Point3(node.getScale()).getZ())
        internalNode.setColor(self.color)
        
        internalNode.flattenStrong()
        