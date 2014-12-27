from panda3d.core import Point3

class DNASuitPoint:
    COMPONENT_CODE = 20

    pointTypeMap = {
        'STREET_POINT': 0,
        'FRONT_DOOR_POINT': 1,
        'SIDE_DOOR_POINT': 2,
        'COGHQ_IN_POINT': 3,
        'COGHQ_OUT_POINT': 4
    }
    ivPointTypeMap = {v: k for k, v in pointTypeMap.items()}

    def __init__(self, index, pointType, pos, landmarkBuildingIndex=-1):
        self.index = index
        self.pointType = pointType
        self.pos = pos
        self.landmarkBuildingIndex = landmarkBuildingIndex
        self.graphId = 0

    def setIndex(self, index):
        self.index = index

    def setGraphId(self, graphId):
        self.graphId = graphId

    def setLandmarkBuildingIndex(self, index):
        self.landmarkBuildingIndex = index

    def setPos(self, pos):
        self.pos = Point3(pos)

    def setPointType(self, pointType):
        if isinstance(pointType, int):
            if pointType in DNASuitPoint.ivPointTypeMap:
                self.pointType = pointType
                return
        elif isinstance(pointType, str):
            if pointType in DNASuitPoint.pointTypeMap:
                self.pointType = DNASuitPoint.pointTypeMap[pointType]
                return
        raise TypeError('{0} is not a valid DNASuitPointType'.format(pointType))

    def getPos(self):
        return Point3(self.pos)
        
    def getLandmarkBuildingIndex(self):
        return self.landmarkBuildingIndex
        
    def getPointType(self):
        return self.pointType
        
    def getIndex(self):
        return self.index
        
    def __repr__(self):
        return "DNASuitPoint %s (%s)" % (self.index, self.ivPointTypeMap[self.pointType])
        