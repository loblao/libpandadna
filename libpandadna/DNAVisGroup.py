import DNAGroup, DNASuitEdge, DNABattleCell

from common import *

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

    def makeFromDGI(self, dgi, store):
        DNAGroup.DNAGroup.makeFromDGI(self, dgi)
        
        numEdges = dgi.getUint16()
        for i in xrange(numEdges):
            index = dgi.getUint16()
            endPoint = dgi.getUint16()
            self.addSuitEdge(store.getSuitEdge(index, endPoint))
                
        numVisibles = dgi.getUint16()
        for i in xrange(numVisibles):
            self.addVisible(dgi_extract_string8(dgi))
                
        numCells = dgi.getUint16()
        for i in xrange(numCells):
            w = dgi.getUint8()
            h = dgi.getUint8()
            
            x, y, z = [dgi.getInt32() / 100.0 for _ in xrange(3)]
            
            self.addBattleCell(DNABattleCell.DNABattleCell(w, h, (x, y, z)))
            