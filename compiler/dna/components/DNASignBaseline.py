import DNANode
from dna.base.DNAPacker import *
from panda3d.core import *

import math, sys

class DNASignBaseline(DNANode.DNANode):
    COMPONENT_CODE = 6

    def __init__(self):
        DNANode.DNANode.__init__(self, '')

        self.code = ''
        self.color = (1, 1, 1, 1)
        self.font = None
        self.flags = ''
        self.indent = 0.0
        self.kern = 0.0
        self.wiggle = 0.0
        self.stumble = 0.0
        self.stomp = 0.0
        self.width = 0
        self.height = 0

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def setFont(self, font):
        self.font = font

    def setHeight(self, height):
        self.height = height

    def setIndent(self, indent):
        self.indent = indent

    def setKern(self, kern):
        self.kern = kern

    def setStomp(self, stomp):
        self.stomp = stomp

    def setStumble(self, stumble):
        self.stumble = stumble

    def setWiggle(self, wiggle):
        self.wiggle = wiggle

    def setWidth(self, width):
        self.width = width

    def setFlags(self, flags):
        self.flags = flags

    def traverse(self, recursive=True, verbose=False):
        packer = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)
        packer.name = 'DNASignBaseline'  # Override the name for debugging.
        
        traversed_data = ""
        
        text = ""
        
        # Generate the node and pack it
        for child in self.children:
            if child.__class__.__name__ == "DNASignText":
                text += child.letters
                
            else:
                if recursive:
                    traversed_data += child.traverse(recursive=recursive, verbose=verbose)
               
        packer.debug('Generating sign...')
        
        root = NodePath('signroot')

        x = 0.0
        for index, letter in enumerate(text):
            tn = TextNode('text')
            tn.setWtext(unicode(letter, sys.getdefaultencoding()))
            tn.setTextColor(self.color)
            
            font = globalStorage.getFont(self.code)
            tn.setFont(font)

            if (index == 0) and ('b' in self.flags):
                tn.setTextScale(1.5)

            np = root.attachNewNode(tn)
            np.setScale(self.scale)
            np.setDepthWrite(0)
            
            if (index % 2):
                np.setPos(x + self.stumble, 0, self.stomp)
                np.setR(-self.wiggle)
                
            else:
                np.setPos(x - self.stumble, 0, -self.stomp)
                np.setR(self.wiggle)
                
            x += tn.getWidth() * np.getSx() + self.kern
            
        map(lambda c: c.setX(c.getX() - x / 2), root.getChildren())

        if (self.width != 0) and (self.height != 0):
            for node in root.getChildren():
                theta = (node.getX() / (self.height / 2.)) + (self.indent * math.pi / 180)
                d = node.getY()

                x = math.sin(theta) * (self.width / 2.)
                y = (math.cos(theta) - 1) * (self.height / 2.)
                
                radius = math.hypot(x, y)
                
                if radius != 0:
                    j = (radius + d) / radius
                    x *= j
                    y *= j
            
                node.setPos(x, 0, y)
                node.setR(node, theta * 180 / math.pi)

        for np in root.findAllMatches('**/+TextNode'):
            np2 = np.getParent().attachNewNode(np.node().generate())
            np2.setTransform(np.getTransform())
            np.removeNode()
            
        root.flattenStrong()
        
        data = ""
        if root.getNumChildren():
            ss = StringStream()
            root.getChild(0).writeBamStream(ss)
            data = compressString(ss.getData(), 1)
            
        packer.pack('sign node data', data, LONG_STRING)
                    
        if recursive:
            packer += traversed_data + chr(255)

        return packer
