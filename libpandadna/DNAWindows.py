import DNAGroup

from common import *

import random

class DNAWindows(DNAGroup.DNAGroup):
    COMPONENT_CODE = 11

    def __init__(self, name):
        DNAGroup.DNAGroup.__init__(self, name)

        self.windowCount = 1
        
        self.code = ''
        self.color = (1, 1, 1, 1)

    def makeFromDGI(self, dgi):
        DNAGroup.DNAGroup.makeFromDGI(self, dgi)
        
        self.code = dgi_extract_string8(dgi)
        self.color = dgi_extract_color(dgi)
        self.windowCount = dgi.getUint8()
        
    def traverse(self, np, store):
        if self.windowCount == 0:
            return
            
        parentX = np.getParent().getScale().getX()
        scale = random.random() % .0375

        if parentX <= 5.0:
            scale += 1.0
            
        elif parentX <= 10.0:
            scale += 1.15
            
        else:
            scale += 1.3
            
        offset = random.random() % .0375
        
        if self.windowCount == 1:
            self.makeWindows(offset + .5, offset + .5, np, self.color, scale, store)
            
        elif self.windowCount == 2:
            self.makeWindows(offset + .33, offset + .5, np, self.color, scale, store)
            self.makeWindows(offset + .66, offset + .5, np, self.color, scale, store, True)
            
        elif self.windowCount == 3:
            self.makeWindows(offset + .33, offset + .66, np, self.color, scale, store)
            self.makeWindows(offset + .66, offset + .66, np, self.color, scale, store, True)
            self.makeWindows(offset + .5, offset + .33, np, self.color, scale, store) #changed from "offset + .66" to "offset + .33" to fix placement
            
        elif self.windowCount == 4:
            self.makeWindows(offset + .33, offset + .25, np, self.color, scale, store)  #changed to ".25" from ".33" to lower window a touch
            self.makeWindows(offset + .66, offset + .25, np, self.color, scale, store, True)  #changed to ".25" from ".33" to lower window a touch
            self.makeWindows(offset + .33, offset + .66, np, self.color, scale, store)
            self.makeWindows(offset + .66, offset + .66, np, self.color, scale, store, True)

        else:
            raise ValueError("Unexpected window count: %d" % self.windowCount)
            
    def makeWindows(self, x, z, parentNode, color, scale, store, flip = False):
        code = self.code[:-1] + ("l" if flip else "r")
        node = store.findNode(code)
        if node is None:
            self.raiseCodeNotFound(code)
            
        window = node.copyTo(parentNode)
        window.setColor(color)
        window.setScale(NodePath(), scale)
        window.setPos(x, 0, z)
        #Added DecalEffect fixes window decals from not showing up! ~Sean~
        window.setEffect(DecalEffect.make())
        