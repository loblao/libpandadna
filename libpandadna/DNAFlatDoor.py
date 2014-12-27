import DNADoor

from common import *

class DNAFlatDoor(DNADoor.DNADoor):
    COMPONENT_CODE = 18

    def traverse(self, np, store):
        result = store.findNode(self.code)
        if result is None:
            self.raiseCodeNotFound()

        _np = result.copyTo(np)
        
        _np.setScale(NodePath(), 1)
        _np.setX(.5)
        _np.iHpr()
        
        _np.setColor(self.color)
        _np.node().setEffect(DecalEffect.make())