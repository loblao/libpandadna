import DNAGroup


class DNAVisGroup(DNAGroup.DNAGroup):
    COMPONENT_CODE = 2

    def __init__(self, name):
        DNAGroup.DNAGroup.__init__(self, name)

        self.visibles = []
        self.suitEdges = []
        self.battleCells = []

    def getVisGroup(self):
        return self

    def addVisible(self, visible):
        self.visibles.append(visible)

    def addSuitEdge(self, suitEdge):
        self.suitEdges.append(suitEdge)

    def addBattleCell(self, battleCell):
        self.battleCells.append(battleCell)
