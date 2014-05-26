class DNAGroup:
    PROP_CODE = 1
    def __init__(self, name):
        self.name = name
        self.children = []
        self.parent = None
        self.visGroup = None

    def add(self, child):
        self.children += [child]

    def at(self, index):
        return self.children[index]

    def clearParent(self):
        self.parent = None
        self.visGroup = None

    def getVisGroup(self):
        return self.visGroup

    def getNumChildren(self):
        return len(self.children)

    def getParent(self):
        return self.parent

    def remove(self, child):
        self.children.remove(child)

    def setParent(self, parent):
        self.parent = parent
        self.visGroup = parent.getVisGroup()

    def getName(self):
        return self.name

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        data += packer(self.name)
        for child in self.children:
            data += packer(child.traverse(packer))
            
        return data

class DNAVisGroup(DNAGroup):
    PROP_CODE = 2
    def __init__(self, name):
        DNAGroup.__init__(self,name)
        self.visibles = []
        self.suitEdges = []
        self.battleCells = []

    def getVisGroup(self):
        return self

    def addBattleCell(self, battleCell):
        self.battleCells.append(battleCell)

    def addSuitEdge(self, suitEdge):
        self.suitEdges.append(suitEdge)

    def addVisible(self, visible):
        self.visibles.append(visible)

    def getBattleCell(self, i):
        return self.battleCells[i]

    def getNumBattleCells(self):
        return len(self.battleCells)

    def getNumSuitEdges(self):
        return len(self.suitEdges)

    def getNumVisibles(self):
        return len(self.visibles)

    def getSuitEdge(self, i):
        return self.suitEdges[i]

    def getVisibleName(self, i):
        return self.visibles[i]

    def removeBattleCell(self, cell):
        self.battleCells.remove(cell)

    def removeSuitEdge(self, edge):
        self.suitEdges.remove(edge)

    def removeVisible(self, visible):
        self.visibles.remove(visible)

    def traverse(self, packer):
        data = __import__('struct').pack('>H', self.PROP_CODE)
        data += packer(DNAGroup.traverse(self, packer))
        return data