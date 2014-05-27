class DNASuitEdge:
    PROP_CODE = 22

    def __init__(self, startPoint, endPoint, zoneId):
        self.startPoint = startPoint
        self.endPoint = endPoint
        self.zoneId = zoneId

    def setStartPoint(self, startPoint):
        self.startPoint = startPoint

    def getStartPoint(self):
        return self.startPoint

    def setEndPoint(self, endPoint):
        self.endPoint = endPoint

    def getEndPoint(self):
        return self.endPoint

    def setZoneId(self, zoneId):
        self.zoneId = zoneId

    def getZoneId(self):
        return self.zoneId
