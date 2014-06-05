import struct

from components.DNABattleCell import DNABattleCell
from components.DNASuitEdge import DNASuitEdge
from components.DNASuitPoint import DNASuitPoint


class DNAStorage:
    def __init__(self):
        self.catalogCodes = {}        # {root: [code]}
        self.textures = {}            # {code: filename}
        self.fonts = {}               # {code: filename}
        self.nodes = {}               # {code: (filename, search)}
        self.hoodNodes = {}           # {code: (filename, search)}
        self.placeNodes = {}          # {code: (filename, search)}
        self.DNAGroups = []           # [DNAGroup]
        self.DNANodes = []            # [DNANode]
        self.DNAVisGroups = []        # [DNAVisGroup]
        self.blockNumbers = []        # [blockNumber]
        self.blockZones = {}          # {blockNumber: zoneId}
        self.blockTitles = {}         # {blockNumber: title}
        self.blockArticles = {}       # {blockNumber: article}
        self.blockBuildingTypes = {}  # {blockNumber: buildingType}
        self.suitPoints = []          # [DNASuitPoint]
        self.suitPointMap = {}        # {DNASuitPoint.index: DNASuitPoint}
        self.suitEdges = {}           # {startPointIndex: [DNASuitEdge]}
        self.battleCells = []         # [DNABattleCell]

    def storeCatalogCode(self, root, code):
        self.catalogCodes.setdefault(root, []).append(code)

    def storeTexture(self, name, texture):
        self.textures[name] = texture

    def storeFont(self, font, code):
        self.fonts[code] = font

    def storeNode(self, filename, search, code):
        self.nodes[code] = (filename, search)

    def storeHoodNode(self, filename, search, code):
        self.hoodNodes[code] = (filename, search)

    def storePlaceNode(self, filename, search, code):
        self.placeNodes[code] = (filename, search)

    def storeDNAGroup(self, group):
        self.DNAGroups.append(group)

    def storeDNANode(self, node):
        self.DNANodes.append(node)

    def storeDNAVisGroup(self, visGroup):
        self.DNAVisGroups.append(visGroup)

    def storeBlockNumber(self, blockNumber):
        self.blockNumbers.append(blockNumber)

    def storeBlockZone(self, blockNumber, zoneId):
        self.blockZones[blockNumber] = zoneId

    def storeBlockTitle(self, blockNumber, title):
        self.blockTitles[blockNumber] = title

    def storeBlockArticle(self, blockNumber, article):
        self.blockArticles[blockNumber] = article

    def storeBlockBuildingType(self, blockNumber, buildingType):
        self.blockBuildingTypes[blockNumber] = buildingType

    def storeSuitPoint(self, suitPoint):
        self.suitPoints.append(suitPoint)
        self.suitPointMap[suitPoint.index] = suitPoint

    def storeSuitEdge(self, startPointIndex, endPointIndex, zoneId):
        startPoint = self.suitPointMap[startPointIndex]
        endPoint = self.suitPointMap[endPointIndex]
        edge = DNASuitEdge(startPoint, endPoint, zoneId)
        self.suitEdges.setdefault(startPointIndex, []).append(edge)
        return edge

    def storeBattleCell(self, cell):
        self.battleCells.append(cell)

    def getBlock(self, name):
        return name[2:name.find(':')]

    def dump(self):
        data = ''

        # Catalog codes...
        data += struct.pack('<H', len(self.catalogCodes))  # Count
        for root, codes in self.catalogCodes.items():
            data += struct.pack('B', len(root))  # Root length
            data += root  # Root
            
            data += struct.pack('B', len(codes))  # Number of codes
            for code in codes:
                data += struct.pack('B', len(code))  # Code length
                data += code  # Code

        # Textures...
        data += struct.pack('<H', len(self.textures))  # Count
        for code, filename in self.textures.items():
            data += struct.pack('B', len(code))  # Code length
            data += code  # Code
            data += struct.pack('B', len(filename))  # Code length
            data += filename  # Filename

        # Fonts...
        data += struct.pack('<H', len(self.fonts))  # Count
        for code, filename in self.fonts.items():
            data += struct.pack('B', len(code))  # Code length
            data += code  # Code
            data += struct.pack('B', len(filename))  # Filename length
            data += filename  # Filename

        # Nodes...
        data += struct.pack('<H', len(self.nodes))  # Count
        for code, (filename, search) in self.nodes.items():
            data += struct.pack('B', len(code))  # Code length
            data += code  # Code
            data += struct.pack('B', len(filename))  # Filename length
            data += filename  # Filename
            data += struct.pack('B', len(search))  # Search length
            data += search  # Search

        # Hood nodes...
        data += struct.pack('<H', len(self.hoodNodes))  # Count
        for code, (filename, search) in self.hoodNodes.items():
            data += struct.pack('B', len(code))  # Code length
            data += code  # Code
            data += struct.pack('B', len(filename))  # Filename length
            data += filename  # Filename
            data += struct.pack('B', len(search))  # Search length
            data += search  # Search

        # Place nodes...
        data += struct.pack('<H', len(self.placeNodes))  # Count
        for code, (filename, search) in self.placeNodes.items():
            data += struct.pack('B', len(code))  # Code length
            data += code  # Code
            data += struct.pack('B', len(filename))  # Filename length
            data += filename  # Filename
            data += struct.pack('B', len(search))  # Search length
            data += search  # Search

        # Blocks...
        data += struct.pack('<H', len(self.blockNumbers))  # Count
        for blockNumber in self.blockNumbers:
            data += struct.pack('B', blockNumber)  # Number
            data += struct.pack('<H', self.blockZones[blockNumber])  # Zone ID
                        
            title = self.blockTitles.get(blockNumber, '')
            data += struct.pack('B', len(title)) # Title length
            data += title # Title
            
            article = self.blockArticles.get(blockNumber, '')
            data += struct.pack('B', len(article)) # Article length
            data += article # Article
            
            bldgType = self.blockBuildingTypes.get(blockNumber, '')
            data += struct.pack('B', len(bldgType)) # Type length
            data += bldgType # Type

        # Suit points...
        data += struct.pack('<H', len(self.suitPoints))  # Count
        for point in self.suitPoints:
            data += struct.pack('<H', point.index)  # Index
            data += struct.pack('B', point.pointType)  # Point type
            for component in point.pos:
                data += struct.pack('<i', int(component * 100))  # Position
            data += struct.pack('B', point.graphId)  # Graph ID
            data += struct.pack('<b', point.landmarkBuildingIndex)  # Landmark building index

        # Suit edges...
        data += struct.pack('<H', len(self.suitEdges))  # Count
        for startPointIndex, edges in self.suitEdges.items():
            data += struct.pack('<H', startPointIndex)  # Start DNASuitPoint index
            data += struct.pack('<H', len(edges))  # Count
            for edge in edges:
                data += struct.pack('<H', edge.startPoint.index)  # Start DNASuitPoint index
                data += struct.pack('<H', edge.endPoint.index)  # End DNASuitPoint index
                data += struct.pack('<H', edge.zoneId)  # Zone ID

        # Battle cells...
        data += struct.pack('<H', len(self.battleCells))  # Count
        for cell in self.battleCells:
            data += struct.pack('B', cell.width)  # Width
            data += struct.pack('B', cell.height)  # Height
            for component in cell.pos:
                data += struct.pack('<i', int(component * 100))  # Position

        return data
