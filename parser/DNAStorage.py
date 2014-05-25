from props import DNAProp, DNAModel, DNAError, DNAFont
from direct.distributed.PyDatagram import PyDatagram

class DNAStorage(DNAProp.DNAProp):
    PROP_CODE = -1
    def __init__(self):
        DNAProp.DNAProp.__init__(self, None)
        
        self.nodes = {'hood': [], 'place': [], 'global': []}
        self.fonts = {}
        
    def doCommand(self, propType, *a):
        #handle actual commands
        if propType == "store_font":
            return self.doStoreFont(a[1])
        
        #not a command, treat as prop
        propClass = None
        args = []
        if propType.endswith('model'):
            propClass = DNAModel.DNAModel
            args = [self, propType, a[0]]
            
        if propClass is None:
            raise DNAError.DNAError('Unknown propType %s' % propType)
            
        p = propClass(self, *args)
        self.addChild(p)
        
        return p
        
    def doStoreNode(self, nodeType, node):
        self.nodes[nodeType].append(node)
        
    def doStoreFont(self, name):
        f = DNAFont.DNAFont(self, name)
        
        if name in self.fonts:
            print 'WARNING: font %s redefined!' % name
            
        self.fonts[name] = f
        return f

    def dumpFonts(self):
        #write binary data for fonts
        dg = PyDatagram()
        numFonts = len(self.fonts)
        dg.addUint8(numFonts)
        
        for name, font in self.fonts.items():
            dg.addString(name)
            dg.addString(font.file)
            
        return dg.getMessage()
        
    def dumpNodes(self):
        dg = PyDatagram()
        
        numNodesHood = len(self.nodes['hood'])
        numNodesPlace = len(self.nodes['place'])
        numNodesGlobal = len(self.nodes['global'])
        
        dg.addUint16(numNodesHood)
        dg.addUint16(numNodesPlace)
        dg.addUint16(numNodesGlobal)
        
        def _addNodes(nodes):
            for n in nodes:
                dg.addString(n.code)
                dg.addString(n.search)
                dg.addString(n.root)
                
        _addNodes(self.nodes['hood'])
        _addNodes(self.nodes['place'])
        _addNodes(self.nodes['global'])
        
        return dg.getMessage()
        
    def getDumpData(self):
        return ""