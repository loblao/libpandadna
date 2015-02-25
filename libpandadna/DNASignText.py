import DNANode


class DNASignText(DNANode.DNANode):
    COMPONENT_CODE = 7

    def __init__(self):
        DNANode.DNANode.__init__(self, '')
        self.letters = ''
