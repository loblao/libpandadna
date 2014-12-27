from SuitLeg import *
from DNASuitPoint import DNASuitPoint

class SuitLegList:
    def __init__(self, path, dnaStore, suitWalkSpeed, fromSky, toSky,
            fromSuitBuilding, toSuitBuilding, toToonBuilding):
        self.path = path
        self.dnaStore = dnaStore
        self.suitWalkSpeed = suitWalkSpeed
        self.fromSky = fromSky
        self.toSky = toSky
        self.fromSuitBuilding = fromSuitBuilding
        self.toSuitBuilding = toSuitBuilding
        self.toToonBuilding = toToonBuilding

        self.legs = []

        startPoint = self.path.getPoint(0)
        headingPoint = self.path.getPoint(1)
        zoneId = self.dnaStore.getSuitEdgeZone(startPoint.getIndex(),
                                               headingPoint.getIndex())
        startLeg = SuitLeg(self.getStartTime(0), zoneId, -1, startPoint,
                           headingPoint, self.getFirstLegType())
        self.legs.append(startLeg)

        for i in xrange(1, self.path.getNumPoints()):
            pointA = self.path.getPoint(i - 1)
            pointB = self.path.getPoint(i)
            zoneId = self.dnaStore.getSuitEdgeZone(pointA.getIndex(),
                                                   pointB.getIndex())
            landmarkBuildingIndex = pointA.getLandmarkBuildingIndex()
            
            if landmarkBuildingIndex == -1:
                landmarkBuildingIndex = pointB.getLandmarkBuildingIndex()
                
            leg = SuitLeg(self.getStartTime(i), zoneId, landmarkBuildingIndex,
                          pointA, pointB, self.getNextLegType(i - 1))
            self.legs.append(leg)

        endIndex = self.path.getNumPoints() - 1
        endPoint = self.path.getPoint(endIndex)
        endEdge = self.dnaStore.suitEdges[endPoint.getIndex()][0]
        zoneId = endEdge.getZoneId()
        endLeg = SuitLeg(self.getStartTime(endIndex), zoneId, -1, endPoint,
                         endPoint, self.getLastLegType())
        self.legs.append(endLeg)

    def getSuitLegType(self, pointTypeA, pointTypeB):
        if pointTypeA == DNASuitPoint.pointTypeMap['STREET_POINT']:
        
            if pointTypeB == DNASuitPoint.pointTypeMap['STREET_POINT']:
                return SuitLeg.TWalk
                
            elif pointTypeB == DNASuitPoint.pointTypeMap['FRONT_DOOR_POINT']:
                return SuitLeg.TToToonBuilding
                
            elif pointTypeB == DNASuitPoint.pointTypeMap['SIDE_DOOR_POINT']:
                return SuitLeg.TToSuitBuilding
                
        elif pointTypeA == DNASuitPoint.pointTypeMap['SIDE_DOOR_POINT']:
            return SuitLeg.TFromSuitBuilding
        
        elif pointTypeA == DNASuitPoint.pointTypeMap['COGHQ_IN_POINT']:
            return SuitLeg.TToCogHQ
        
        elif pointTypeA == DNASuitPoint.pointTypeMap['COGHQ_OUT_POINT']:
            return SuitLeg.TFromCogHQ
        
        return SuitLeg.TWalk

    def getNumLegs(self):
        return len(self.legs)

    def getLeg(self, index):
        return self.legs[index]

    def getType(self, index):
        return self.legs[index].getType()

    def getLegTime(self, index):
        return self.legs[index].getLegTime()

    def getZoneId(self, index):
        return self.legs[index].getZoneId()

    def getBlockNumber(self, index):
        return self.legs[index].getBlockNumber()

    def getPointA(self, index):
        return self.legs[index].getPointA()

    def getPointB(self, index):
        return self.legs[index].getPointB()

    def getStartTime(self, index):
        if index < self.getNumLegs():
            return self.legs[index].getStartTime()
            
        startTime = 0.0
        
        for legIndex in xrange(self.getNumLegs()):
            if legIndex == index:
                break
            startTime += self.getLegTime(legIndex)
            
        return startTime

    def getLegIndexAtTime(self, time, startLeg):
        endTime = 0.0
        
        for legIndex in xrange(self.getNumLegs()):
            endTime += self.getLegTime(legIndex)
            
            if endTime > time:
                break
                
        return legIndex

    def isPointInRange(self, point, lowTime, highTime):
        pointIndex = point.getIndex()
        startLegIndex = self.getLegIndexAtTime(lowTime, 0)
        endLegIndex = self.getLegIndexAtTime(highTime, pointIndex)
        
        for leg in self.legs[startLegIndex:endLegIndex + 1]:
            if leg.getPointA().getIndex() == pointIndex:
                return 1
            
            elif leg.getPointB().getIndex() == pointIndex:
                return 1
                
        return 0

    def getFirstLegType(self):
        pointTypeA = self.path.getPoint(0).getPointType()
        
        if pointTypeA == DNASuitPoint.pointTypeMap['STREET_POINT']:
            return SuitLeg.TFromSky
            
        elif pointTypeA == DNASuitPoint.pointTypeMap['COGHQ_OUT_POINT']:
            return SuitLeg.TFromCogHQ
            
        pointTypeB = self.path.getPoint(1).getPointType()
        
        return self.getSuitLegType(pointTypeA, pointTypeB)

    def getNextLegType(self, index):
        pointTypeA = self.path.getPoint(index).getPointType()
        pointTypeB = self.path.getPoint(index + 1).getPointType()
        return self.getSuitLegType(pointTypeA, pointTypeB)

    def getLastLegType(self):
        return SuitLeg.TToSky

    def __getitem__(self, key):
        return self.legs[key]
        