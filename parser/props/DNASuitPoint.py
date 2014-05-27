class DNASuitPoint:
    PROP_CODE = 20
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

    def setGraphId(self, graphId):
        self.graphId = graphId

    def getGraphId(self):
        return self.graphId

    def setLandmarkBuildingIndex(self, index):
        self.landmarkBuildingIndex = index

    def getLandmarkBuildingIndex(self):
        return self.landmarkBuildingIndex

    def setPos(self, pos):
        self.pos = pos

    def getPos(self):
        return self.pos

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

    def isTerminal(self):
        return self.pointType <= 2
