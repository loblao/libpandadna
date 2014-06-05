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

    def traverse(self, recursive=True, verbose=False):
        data = DNAGroup.DNAGroup.traverse(self, recursive=False, verbose=verbose)

        # Edges...
        data += struct.pack('<H', len(filter(None, self.suitEdges)))  # Count
        for edge in self.suitEdges:
            # Store start and end points
            # It's possible to get the edge
            # object again in the reader
            # using those.
            if edge is None:
                continue
                
            startPoint, endPoint = edge.startPoint, edge.endPoint
            data += struct.pack('<H', startPoint.index)
            data += struct.pack('<H', endPoint.index)
            
        # Visibles
        data += struct.pack('<H', len(self.visibles))  # Count
        for visible in self.visibles:
            data += struct.pack('B', len(visible))
            data += visible
            
        # Battle cells... (copied from DNAStorage.py)
        data += struct.pack('<H', len(self.battleCells))  # Count
        for cell in self.battleCells:
            data += struct.pack('B', cell.width)  # Width
            data += struct.pack('B', cell.height)  # Height
            for component in cell.pos:
                data += struct.pack('<i', int(component * 100))  # Position
    
        if recursive:
            data += self.recurse(verbose)
                
        return data
        