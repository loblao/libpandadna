from props.DNASuitStuff import *
from direct.distributed.PyDatagram import PyDatagram
class DNAStorage:
    def __init__(self):
        self.suitPoints = []
        self.suitPointMap = {}
        self.DNAGroups = {}
        self.DNAVisGroups = []
        self.suitEdges = {}
        self.battleCells = []
        self.nodes = {}
        self.hoodNodes = {}
        self.placeNodes = {}
        self.fonts = {}
        self.blockTitles = {}
        self.blockArticles = {}
        self.blockBuildingTypes = {}
        self.blockDoors = {}
        self.blockNumbers = []
        self.blockZones = {}
        self.textures = {}
        self.catalogCodes = {}

    def getSuitPath(self, startPoint, endPoint, minPathLen=40, maxPathLen=300):
        points = [startPoint]
        while len(points) < maxPathLen:
            startPointIndex = startPoint.getIndex()
            if startPointIndex == endPoint.getIndex():
                if len(points) >= minPathLen:
                    break
            if startPointIndex not in self.suitEdges:
                raise DNAError('Could not find DNASuitPath.')
            edges = self.suitEdges[startPointIndex]
            for edge in edges:
                startPoint = edge.getEndPoint()
                startPointType = startPoint.getPointType()
                if startPointType != DNASuitPoint.pointTypeMap['FRONT_DOOR_POINT']:
                    if startPointType != DNASuitPoint.pointTypeMap['SIDE_DOOR_POINT']:
                        break
            else:
                raise DNAError('Could not find DNASuitPath.')
            points.append(startPoint)
        path = DNASuitPath()
        for point in points:
            path.addPoint(point)
        return path

    def getSuitEdgeTravelTime(self, startIndex, endIndex, suitWalkSpeed):
        startPoint = self.suitPointMap.get(startIndex)
        endPoint = self.suitPointMap.get(endIndex)
        if (not startPoint) or (not endPoint):
            return 0.0
        distance = (endPoint.getPos()-startPoint.getPos()).length()
        return distance / suitWalkSpeed

    def getSuitEdgeZone(self, startIndex, endIndex):
        return self.getSuitEdge(startIndex, endIndex).getZoneId()

    def getAdjacentPoints(self, point):
        path = DNASuitPath()
        startIndex = point.getIndex()
        if startIndex not in self.suitEdges:
            return path
        for edge in self.suitEdges[startIndex]:
            path.addPoint(edge.getEndPoint())
        return path

    def storeSuitPoint(self, suitPoint):
        if not isinstance(suitPoint, DNASuitPoint):
            raise TypeError('suitPoint must be an instance of DNASuitPoint')
        self.suitPoints.append(suitPoint)
        self.suitPointMap[suitPoint.getIndex()] = suitPoint

    def getSuitPointAtIndex(self, index):
        return self.suitPoints[index]

    def getSuitPointWithIndex(self, index):
        return self.suitPointMap.get(index)

    def resetSuitPoints(self):
        self.suitPoints = []
        self.suitPointMap = {}
        self.suitEdges = {}

    def resetTextures(self):
        self.textures = {}

    def resetHood(self):
        self.resetBlockNumbers()

    def findDNAGroup(self, node):
        return self.DNAGroups[node]

    def removeDNAGroup(self, dnagroup):
        for node, group in self.DNAGroups.items():
            if group == dnagroup:
                del self.DNAGroups[node]

    def resetDNAGroups(self):
        self.DNAGroups = {}

    def getNumDNAVisGroups(self):
        return len(self.DNAVisGroups)

    def getDNAVisGroupName(self, i):
        return self.DNAVisGroups[i].getName()

    def storeDNAVisGroup(self, group):
        self.DNAVisGroups.append(group)

    def storeSuitEdge(self, startIndex, endIndex, zoneId):
        startPoint = self.getSuitPointWithIndex(startIndex)
        endPoint = self.getSuitPointWithIndex(endIndex)
        edge = DNASuitEdge(startPoint, endPoint, zoneId)
        self.suitEdges.setdefault(startIndex, []).append(edge)
        return edge

    def getSuitEdge(self, startIndex, endIndex):
        edges = self.suitEdges[startIndex]
        for edge in edges:
            if edge.getEndPoint().getIndex() == endIndex:
                return edge

    def removeBattleCell(self, cell):
        self.battleCells.remove(cell)

    def storeBattleCell(self, cell):
        self.battleCells.append(cell)

    def resetBattleCells(self):
        self.battleCells = []

    def findNode(self, code):
        if code in self.nodes:
            return self.nodes[code]
        if code in self.hoodNodes:
            return self.hoodNodes[code]
        if code in self.placeNodes:
            return self.placeNodes[code]

    def resetNodes(self):
        self.nodes = {}

    def resetHoodNodes(self):
        self.hoodNodes = {}

    def resetPlaceNodes(self):
        self.placeNodes = {}

    def storeNode(self, node, code):
        self.nodes[code] = node

    def storeHoodNode(self, node, code):
        self.hoodNodes[code] = node

    def storePlaceNode(self, node, code):
        self.placeNodes[code] = node

    def findFont(self, code):
        if code in self.fonts:
            return self.fonts[code]

    def resetFonts(self):
        self.fonts = {}

    def storeFont(self, font, code):
        self.fonts[code] = font

    def getBlock(self, name):
        block = name[name.find(':')-2:name.find(':')]
        if not block[0].isdigit():
            block = block[1:]
        return block

    def getBlockBuildingType(self, blockNumber):
        if blockNumber in self.blockBuildingTypes:
            return self.blockBuildingTypes[blockNumber]

    def getTitleFromBlockNumber(self, blockNumber):
        return self.blockTitles[blockNumber]

    def getDoorPosHprFromBlockNumber(self, blockNumber):
        key = str(blockNumber)
        if key in self.blockDoors:
            return self.blockDoors[key]

    def storeBlockDoor(self, blockNumber, door):
        self.blockDoors[str(blockNumber)] = door

    def storeBlockTitle(self, blockNumber, title):
        self.blockTitles[blockNumber] = title

    def storeBlockArticle(self, blockNumber, article):
        self.blockArticles[blockNumber] = article

    def storeBlockBuildingType(self, blockNumber, buildingType):
        self.blockBuildingTypes[blockNumber] = buildingType

    def storeTexture(self, name, texture):
        self.textures[name] = texture

    def resetDNAVisGroups(self):
        self.DNAVisGroups = []

    def resetDNAVisGroupsAI(self):
        self.resetDNAVisGroups()

    def getNumDNAVisGroupsAI(self):
        return self.getNumDNAVisGroups()

    def getNumSuitPoints(self):
        return len(self.suitPoints)

    def getNumVisiblesInDNAVisGroup(self, i):
        return self.DNAVisGroups[i].getNumVisibles()

    def getVisibleName(self, i, j):
        return self.DNAVisGroups[i].getVisibleName(j)

    def getDNAVisGroupAI(self, i):
        return self.DNAVisGroups[i]

    def storeCatalogCode(self, category, code):
        if not category in self.catalogCodes:
            self.catalogCodes[category] = []
        self.catalogCodes[category].append(code)

    def getNumCatalogCodes(self, category):
        if category not in self.catalogCodes:
            return -1
        return len(self.catalogCodes[category])

    def getCatalogCode(self, category, index):
        return self.catalogCodes[category][index]

    def findTexture(self, name):
        if name in self.textures:
            return self.textures[name]

    def discoverContinuity(self):
        return 1  # TODO

    def resetBlockNumbers(self):
        self.blockNumbers = []
        self.blockZones = {}
        self.blockArticles = {}
        self.blockDoors = {}
        self.blockTitles = {}
        self.blockBuildingTypes = {}

    def getNumBlockNumbers(self):
        return len(self.blockNumbers)

    def storeBlockNumber(self, blockNumber):
        self.blockNumbers.append(blockNumber)

    def getBlockNumberAt(self, index):
        return self.blockNumbers[index]

    def getZoneFromBlockNumber(self, blockNumber):
        if blockNumber in self.blockZones:
            return self.blockZones[blockNumber]

    def storeBlockZone(self, blockNumber, zoneId):
        self.blockZones[blockNumber] = zoneId

    def resetBlockZones(self):
        self.blockZones = {}

    def ls(self):
        print 'DNASuitPoints:'
        for suitPoint in self.suitPoints:
            print '\t', suitPoint
        print 'DNABattleCells:'
        for cell in self.battleCells:
            print '\t', cell
            
    def dump(self, packer):
        data = ""
        
        #dump suit points
        dg = PyDatagram()
        for point in self.suitPoints:
            dg.addUint16(point.index)
            dg.addUint8(point.pointType)
            for x in point.pos: dg.addInt32(int(x * 10))
            dg.addUint8(point.graphId)
            dg.addInt8(point.landmarkBuildingIndex)
        
        data += packer(dg.getMessage())
        
        #dump suit edges
        def __doDumpEdge(dg, edge):
            dg.addUint16(edge.startpt.index)
            dg.addUint16(edge.endpt.index)
            dg.addUint32(edge.zoneId)
            
        dg = PyDatagram()
        for index, edges in self.suitEdges.items():
            dg.addUint8(index)
            numEdges = len(edges)
            dg.addUint8(numEdges)
            for edge in edges:
                __doDumpEdge(dg, edge)

        data += packer(dg.getMessage())
            
        #dump cells
        dg = PyDatagram()
        for cell in self.battleCells:
            dg.addUint8(cell.width)
            dg.addUint8(cell.height)
            for x in cell.pos: dg.addInt32(int(x * 10))

        data += packer(dg.getMessage())
        
        #dump nodes
        dg = PyDatagram()
        for code, model in self.nodes.items():
            dg.addString(code)
            dg.addString(model.cStr())
            
        data += packer(dg.getMessage())
        
        dg = PyDatagram()
        for code, model in self.hoodNodes.items():
            dg.addString(code)
            dg.addString(model.cStr())
            
        data += packer(dg.getMessage())

        dg = PyDatagram()
        for code, model in self.placeNodes.items():
            dg.addString(code)
            dg.addString(model.cStr())
            
        data += packer(dg.getMessage())
        
        #dump fonts
        dg = PyDatagram()
        for name, path in self.fonts.items():
            dg.addString(name)
            dg.addString(path)

        data += packer(dg.getMessage())
        
        #dump titles
        dg = PyDatagram()
        for index, s in self.blockTitles.items():
            dg.addUint8(index)
            dg.addString(s)

        data += packer(dg.getMessage())
        
        #dump articles
        dg = PyDatagram()
        for index, s in self.blockArticles.items():
            dg.addUint8(index)
            dg.addString(s)

        data += packer(dg.getMessage())
        
        #dump bldg types
        dg = PyDatagram()
        for index, s in self.blockBuildingTypes.items():
            dg.addUint8(index)
            dg.addString(s)

        data += packer(dg.getMessage())
        
        #dump block numbers
        dg = PyDatagram()
        for n in self.blockNumbers:
            dg.addUint8(n)

        data += packer(dg.getMessage())
        
        #dump block zones
        dg = PyDatagram()
        for index, zone in self.blockZones.items():
            dg.addUint8(index)
            dg.addUint32(zone)

        data += packer(dg.getMessage())
        
        #dump textures
        dg = PyDatagram()
        for name, path in self.textures.items():
            dg.addString(name)
            dg.addString(path)

        data += packer(dg.getMessage())
        
        #dumping catalogCodes is not needed, it can be built on the fly
        return data
        