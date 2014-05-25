import DNAError, DNAProp, DNANode

class DNAModel(DNAProp.DNAProp):
    def __init__(self, parent, dnaStore, modelType, modelName):
        DNAProp.DNAProp.__init__(self, parent)
        if self.getParent().__class__.__name__ != "DNAStorage":
            raise DNAError.DNAError("model inside prop")
            
        self.dnaStore = dnaStore
        self.modelType = modelType
        
    def _handle_store_node(self, *args):
            search = ''
            code = ''
            root = ''
            
            if len(args) == 2:
                root, search = args
                root = search
                
            else:
                root, code, search = args
                
            t = {'hood_model': 'hood', 'place_model': 'place', 'model': 'global'}[self.modelType]
            self.dnaStore.doStoreNode(t, DNANode.DNANode(code, search, root))
        
    def doCommand(self, command, *a):
        if command == "store_node":
            self._handle_store_node(*a)