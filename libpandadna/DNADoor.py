import DNAGroup

from common import *

class DNADoor(DNAGroup.DNAGroup):
    COMPONENT_CODE = 17

    def __init__(self, name):
        DNAGroup.DNAGroup.__init__(self, name)
        
        self.code = ''
        self.color = (1, 1, 1,1)

    def makeFromDGI(self, dgi):
        DNAGroup.DNAGroup.makeFromDGI(self, dgi)
        
        self.code = dgi_extract_string8(dgi)
        self.color = dgi_extract_color(dgi)
        
    @staticmethod
    def setupDoor(doorNodePath, parentNode, doorOrigin, dnaStore, block, color):
        doorNodePath.iPosHprScale(doorOrigin)
        doorNodePath.setColor(color)
        
        leftHole = doorNodePath.find('door_*_hole_left')
        leftHole.setName('doorFrameHoleLeft')
        
        rightHole = doorNodePath.find('door_*_hole_right')
        rightHole.setName('doorFrameHoleRight')
        
        leftDoor = doorNodePath.find('door_*_left')
        leftDoor.setName('leftDoor')
        
        rightDoor = doorNodePath.find('door_*_right')
        rightDoor.setName('rightDoor')
        doorFlat = doorNodePath.find('door_*_flat')
        leftHole.wrtReparentTo(doorFlat, 0)
        rightHole.wrtReparentTo(doorFlat, 0)
        doorFlat.setEffect(DecalEffect.make())
        rightDoor.wrtReparentTo(parentNode, 0)
        leftDoor.wrtReparentTo(parentNode, 0)

        rightDoor.setColor(color, 0)
        leftDoor.setColor(color, 0)
        leftHole.setColor((0, 0, 0, 1), 0)
        rightHole.setColor((0, 0, 0, 1), 0)

        doorTrigger = doorNodePath.find('door_*_trigger')
        doorTrigger.setScale(2, 2, 2)
        doorTrigger.wrtReparentTo(parentNode, 0)
        doorTrigger.setName('door_trigger_' + block)

        store = NodePath('door-%s' % block)
        store.setPosHprScale(doorNodePath, (0, 0, 0), (0, 0, 0), (1, 1, 1))
        dnaStore.storeBlockDoor(block, store)

    def traverse(self, np, store):
        frontNode = np.find('**/*_front')
        
        if not frontNode.getNode(0).isGeomNode():
            frontNode = frontNode.find('**/+GeomNode')
            
        frontNode.setEffect(DecalEffect.make())
        
        node = store.findNode(self.code)
        if node is None:
            self.raiseCodeNotFound()
            
        doorNode = node.copyTo(frontNode)
        block = store.getBlock(np.getName())
        DNADoor.setupDoor(doorNode, np, np.find('**/*door_origin'), store, block, self.color)
        