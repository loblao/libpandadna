from DNAPacker import *
import DNANode


class DNASign(DNANode.DNANode):
    COMPONENT_CODE = 5

    def __init__(self):
        DNANode.DNANode.__init__(self, '')

        self.code = ''
        self.color = (1, 1, 1, 1)

    def setCode(self, code):
        self.code = code

    def setColor(self, color):
        self.color = color

    def traverse(self, recursive=True, verbose=False):
        packer = DNANode.DNANode.traverse(self, recursive=False, verbose=verbose)
        packer.name = 'DNASign'  # Override the name for debugging.

        packer.pack('code', self.code, SHORT_STRING)

        for component in self.color:
            packer.pack('color', int(component * 255), UINT16)

        if recursive:
            packer += self.traverseChildren(verbose=verbose)
        return packer
