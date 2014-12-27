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
        
    def __repr__(self):
        s = "DNASuitPath:\n"
        for index, point in enumerate(self.suitPoints):
            if (index + 1) < len(self.suitPoints):
                nextPoint = self.getPoint(index + 1)
            
            else:
                nextPoint = "**END**"
                
            s += "%s -> %s\n" % (point, nextPoint)
        
        return s
        
    def __len__(self):
        return self.getNumPoints()
        