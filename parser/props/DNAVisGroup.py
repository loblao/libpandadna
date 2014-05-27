import DNAGroup


class DNAVisGroup(DNAGroup.DNAGroup):
    PROP_CODE = 2

    def __init__(self, name):
        DNAGroup.DNAGroup.__init__(self, name)

        self.visibles = []
        self.suitEdges = []
        self.battleCells = []

    def getVisGroup(self):
        return self

    def addVisible(self, visible):
        self.visibles.append(visible)

    def removeVisible(self, visible):
        self.visibles.remove(visible)

    def getVisibleName(self, index):
        return self.visibles[index]

    def getNumVisibles(self):
        return len(self.visibles)

    def addSuitEdge(self, suitEdge):
        self.suitEdges.append(suitEdge)

    def removeSuitEdge(self, edge):
        self.suitEdges.remove(edge)

    def getSuitEdge(self, index):
        return self.suitEdges[index]

    def getNumSuitEdges(self):
        return len(self.suitEdges)

    def addBattleCell(self, battleCell):
        self.battleCells.append(battleCell)

    def removeBattleCell(self, cell):
        self.battleCells.remove(cell)

    def getBattleCell(self, i):
        return self.battleCells[i]

    def getNumBattleCells(self):
        return len(self.battleCells)
