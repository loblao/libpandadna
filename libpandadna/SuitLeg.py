__all__ = ["SuitLeg"]

class SuitTimings:
    fromSky = 6.5
    toSky = 6.5
    fromSuitBuilding = 2.0
    toSuitBuilding = 2.5
    toToonBuilding = 2.5
    
class SuitLeg:
    TWalkFromStreet = 0
    TWalkToStreet = 1
    TWalk = 2
    TFromSky = 3
    TToSky = 4
    TFromSuitBuilding = 5
    TToSuitBuilding = 6
    TToToonBuilding = 7
    TFromCogHQ = 8
    TToCogHQ = 9
    TOff = 10
    TypeToName = {
        TWalkFromStreet: 'WalkFromStreet',
        TWalkToStreet: 'WalkToStreet',
        TWalk: 'Walk',
        TFromSky: 'FromSky',
        TToSky: 'ToSky',
        TFromSuitBuilding: 'FromSuitBuilding',
        TToSuitBuilding: 'ToSuitBuilding',
        TToToonBuilding: 'ToToonBuilding',
        TFromCogHQ: 'FromCogHQ',
        TToCogHQ: 'ToCogHQ',
        TOff: 'Off'
    }

    def __init__(self, startTime, zoneId, blockNumber, pointA, pointB, type, suitWalkSpeed = 4.8):
        self.startTime = startTime
        self.zoneId = zoneId
        self.blockNumber = blockNumber
        self.pointA = pointA
        self.pointB = pointB
        self.type = type
        distance = (self.getPosB() - self.getPosA()).length()
        self.legTime = distance / suitWalkSpeed

    def getZoneId(self):
        return self.zoneId

    def getStartTime(self):
        return self.startTime

    def getLegTime(self):
        if self.getType() == SuitLeg.TFromSky:
            return SuitTimings.fromSky
            
        elif self.getType() == SuitLeg.TToSky:
            return SuitTimings.toSky
            
        if self.getType() == SuitLeg.TFromSuitBuilding:
            return SuitTimings.fromSuitBuilding
            
        if self.getType() == SuitLeg.TToSuitBuilding:
            return SuitTimings.toSuitBuilding
            
        if self.getType() == SuitLeg.TToToonBuilding:
            return SuitTimings.toToonBuilding
            
        return self.legTime

    def getBlockNumber(self):
        return self.blockNumber

    def getPointA(self):
        return self.pointA

    def getPointB(self):
        return self.pointB

    def getPosA(self):
        return self.pointA.getPos()

    def getPosB(self):
        return self.pointB.getPos()

    def getPosAtTime(self, time):
        posA = self.getPosA()
        posB = self.getPosB()
        return posA + ((posB-posA) * (time/self.getLegTime()))

    def getType(self):
        return self.type

    @staticmethod
    def getTypeName(legType):
        if legType in SuitLeg.TypeToName:
            return SuitLeg.TypeToName[legType]
            
        return '**invalid**'
        