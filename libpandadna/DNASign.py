import DNAProp

from common import *

class DNASign(DNAProp.DNAProp):
    COMPONENT_CODE = 5

    def __init__(self):
        DNAProp.DNAProp.__init__(self, '')

    def traverse(self, np, store):
        decalNode = np.find('**/sign_decal')
        
        if decalNode.isEmpty():
            decalNode = np.find('**/*_front')
            
        if decalNode.isEmpty() or not decalNode.getNode(0).isGeomNode():
            decalNode = np.find('**/+GeomNode')
            
        if self.code:
            node = store.findNode(self.code)
            node = node.copyTo(decalNode)
            node.setName('sign')
            
        else:
            node = decalNode.attachNewNode(ModelNode('sign'))

        node.setDepthOffset(50)
        
        origin = np.find('**/*sign_origin')
        node.setPosHprScale(origin, self.pos, self.hpr, self.scale)
        node.wrtReparentTo(origin, 0) #added to fix some building signs rotating with door opening
        
        self.traverseChildren(node, store)
        
        node.flattenStrong()
        