from direct.distributed.PyDatagram import PyDatagram

class DNASuitPath:
    def __init__(self):
        self.suitPoints = []

    def getNumPoints(self):
        return len(self.suitPoints)

    def getPointIndex(self, pointIndex):
        return self.suitPoints[pointIndex].getIndex()

    def addPoint(self, point):
        self.suitPoints.append(point)

    def getPoint(self, pointIndex):
        return self.suitPoints[pointIndex]

    def reversePath(self):
        self.suitPoints.reverse()

class DNASuitPoint:
    pointTypeMap = {
      'STREET_POINT' : 0,
      'FRONT_DOOR_POINT' : 1,
      'SIDE_DOOR_POINT' : 2,
      'COGHQ_IN_POINT' : 3,
      'COGHQ_OUT_POINT' : 4
    }
    ivPointTypeMap = {v: k for k, v in pointTypeMap.items()}

    def __init__(self, index, pointType, pos, landmarkBuildingIndex=-1):
        self.index = index
        self.pointType = pointType
        self.pos = pos
        self.graphId = 0
        self.landmarkBuildingIndex = landmarkBuildingIndex

    def __str__(self):
        pointTypeStr = DNASuitPoint.ivPointTypeMap[self.getPointType()]
        return 'DNASuitPoint index: {0}, pointType: {1}, pos: {2}'.format(
            self.getIndex(), pointTypeStr, self.getPos())

    def setIndex(self, index):
        self.index = index

    def getIndex(self):
        return self.index

    def getGraphId(self):
        return self.graphId

    def getLandmarkBuildingIndex(self):
        return self.landmarkBuildingIndex

    def getPos(self):
        return self.pos

    def isTerminal(self):
        return self.pointType <= 2

    def setGraphId(self, id):
        self.graphId = id

    def setLandmarkBuildingIndex(self, index):
        self.landmarkBuildingIndex = index

    def setPointType(self, type):
        if isinstance(type, int):
            if type in DNASuitPoint.ivPointTypeMap:
                self.pointType = type
            else:
                raise TypeError('%i is not a valid DNASuitPointType' % type)
        elif isinstance(type, str):
            if type in DNASuitPoint.pointTypeMap:
                self.pointType = DNASuitPoint.pointTypeMap[type]
            else:
                raise TypeError('%s is not a valid DNASuitPointType' % type)

    def getPointType(self):
        return self.pointType

    def setPos(self, pos):
        self.pos = pos

class DNABattleCell:
    def __init__(self, width, height, pos):
        self.width = width
        self.height = height
        self.pos = pos

    def __str__(self):
        return 'DNABattleCell width: ' + str(self.width) + ' height: ' + str(self.height) + ' pos: ' + str(self.pos)

    def getWidth(self):
        return self.width

    def getHeight(self):
        return self.height

    def getPos(self):
        return self.pos

    def setWidthHeight(self, width, height):
        self.width = width
        self.height = height

class DNASuitEdge:
    def __init__(self, startpt, endpt, zoneId):
        self.startpt = startpt
        self.endpt = endpt
        self.zoneId = zoneId

    def getEndPoint(self):
        return self.endpt

    def getStartPoint(self):
        return self.startpt

    def getZoneId(self):
        return self.zoneId

    def setZoneId(self, zoneId):
        self.zoneId = zoneId