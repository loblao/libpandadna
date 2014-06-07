import DNAGroup
import struct


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

    def debug(self, message):
        if self.verbose:
            print 'DNAVisGroup:', message

    def traverse(self, recursive=True, verbose=False):
        data = DNAGroup.DNAGroup.traverse(self, recursive=False, verbose=verbose)

        self.debug('packing... suit edge count: {0}'.format(len(self.suitEdges)))
        data += struct.pack('<H', len(self.suitEdges))  # Count
        for edge in self.suitEdges:
            startPointIndex = edge.startPoint.index
            self.debug('packing... start DNASuitPoint index: {0}'.format(startPointIndex))
            data += struct.pack('<H', startPointIndex)  # Start DNASuitPoint index
            endPointIndex = edge.endPoint.index
            self.debug('packing... end DNASuitPoint index: {0}'.format(endPointIndex))
            data += struct.pack('<H', endPointIndex)  # End DNASuitPoint index

        self.debug('packing... visible count: {0}'.format(len(self.visibles)))
        data += struct.pack('<H', len(self.visibles))  # Count
        for visible in self.visibles:
            self.debug('packing... visible length: {0}'.format(len(visible)))
            data += struct.pack('B', len(visible))  # Visible length
            self.debug('packing... visible: {0}'.format(visible))
            data += visible  # Visible

        self.debug('packing... battle cell count: {0}'.format(len(self.battleCells)))
        data += struct.pack('<H', len(self.battleCells))  # Count
        for cell in self.battleCells:
            self.debug('packing... width: {0}'.format(cell.width))
            data += struct.pack('B', cell.width)  # Width
            self.debug('packing... height: {0}'.format(cell.height))
            data += struct.pack('B', cell.height)  # Height
            for component in cell.pos:
                self.debug('packing... position: {0}'.format(component))
                data += struct.pack('<i', int(component * 100))  # Position

        if recursive:
            data += self.traverseChildren(verbose=verbose)

        return data
