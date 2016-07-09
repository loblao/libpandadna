from panda3d.core import Point3
from libpandadna import DNAStorage
from libpandadna import DNASuitPoint
from libpandadna import DNASuitEdge
from libpandadna import DNASuitPath
from libpandadna import SuitLeg
from libpandadna import SuitLegList
import unittest


class SuitTimings:
    # Keep these values in sync with SuitTimings (see SuitLeg.cxx)
    ToSky = 6.5
    FromSky = 6.5
    FromSuitBuilding = 2.0
    ToSuitBuilding = 2.5
    ToToonBuilding = 2.5

SUIT_WALK_SPEED = 5


class TestSuit(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.store = DNAStorage()

    def make_suit_point(self, index, type=DNASuitPoint.STREET_POINT, pos=(0, 0, 0), landmark_building_index=-1, test=False):
        point = DNASuitPoint(123, DNASuitPoint.STREET_POINT, Point3(10, -10, 0), 15)

        if test:
            self.assertEqual(point.getIndex(), 123)
            point.setIndex(1)
            self.assertEqual(point.getIndex(), 1)

            self.assertEqual(point.getPointType(), DNASuitPoint.STREET_POINT)
            point.setPointType(DNASuitPoint.FRONT_DOOR_POINT)
            self.assertEqual(point.getPointType(), DNASuitPoint.FRONT_DOOR_POINT)
            point.setPointType('STREET_POINT')
            self.assertEqual(point.getPointType(), DNASuitPoint.STREET_POINT)

            self.assertEqual(point.getPos(), Point3(10, -10, 0))
            point.setPos(Point3(150, 20, 0.5))
            self.assertEqual(point.getPos(), Point3(150, 20, 0.5))

            self.assertEqual(point.getLandmarkBuildingIndex(), 15)
            point.setLandmarkBuildingIndex(-1)
            self.assertEqual(point.getLandmarkBuildingIndex(), -1)

            # Test invalid point type (shouldn't change it all)
            point.setPointType('INVALID')
            self.assertEqual(point.getPointType(), DNASuitPoint.STREET_POINT)

        point.setIndex(index)
        point.setPointType(type)
        point.setPos(pos)
        point.setLandmarkBuildingIndex(landmark_building_index)
        return point

    def test_suit_point(self):
        self.make_suit_point(1, test=True)

    def make_suit_edge(self, start_point=None, end_point=None, zoneId=2000, test=False):
        point1 = start_point or DNASuitPoint(1, DNASuitPoint.STREET_POINT, Point3(0, 0, 0))
        point2 = end_point or DNASuitPoint(2, DNASuitPoint.STREET_POINT, Point3(0, 0, 0))
        edge = DNASuitEdge(point1, point2, 2000)

        if test:
            point3 = DNASuitPoint(3, DNASuitPoint.STREET_POINT, Point3(0, 0, 0))

            self.assertEqual(edge.getStartPoint(), point1)
            edge.setStartPoint(point3)
            self.assertEqual(edge.getStartPoint(), point3)

            self.assertEqual(edge.getEndPoint(), point2)
            edge.setEndPoint(point1)
            self.assertEqual(edge.getEndPoint(), point1)

            self.assertEqual(edge.getZoneId(), 2000)
            edge.setZoneId(3000)
            self.assertEqual(edge.getZoneId(), 3000)

        edge.setStartPoint(point1)
        edge.setEndPoint(point2)
        edge.setZoneId(zoneId)
        return edge

    def test_suit_edge(self):
        self.make_suit_edge(test=True)

    def make_suit_path(self, point_indexes, test=False):
        points = [self.make_suit_point(index) for index in point_indexes]
        path = DNASuitPath()

        for point in points:
            path.addPoint(point)

        if test:
            self.assertEqual(path.getNumPoints(), len(points))

            for i in xrange(len(points)):
                self.assertEqual(path.getPoint(i), points[i])
                self.assertEqual(path.getPointIndex(i), points[i].getIndex())

            path.reversePath()

            for i in xrange(len(points)):
                self.assertEqual(path.getPoint(i), points[-i - 1])
                self.assertEqual(path.getPointIndex(i), points[-i - 1].getIndex())

        return path

    def test_suit_path(self):
        self.make_suit_path(range(10), test=True)

    def test_suit_leg(self):
        point_a = self.make_suit_point(1)
        point_b = self.make_suit_point(2, pos=(0, 10, 0))
        point_c = self.make_suit_point(3, pos=(0, 20, 0))
        point_d = self.make_suit_point(4, pos=(0, 30, 0))

        leg = SuitLeg(5.21, 2000, 11, point_a, point_b, SuitLeg.TToToonBuilding, SUIT_WALK_SPEED)

        self.assertAlmostEqual(leg.getStartTime(), 5.21)
        leg.setStartTime(0)
        self.assertEqual(leg.getStartTime(), 0)

        self.assertEqual(leg.getZoneId(), 2000)
        leg.setZoneId(1000)
        self.assertEqual(leg.getZoneId(), 1000)

        self.assertEqual(leg.getBlockNumber(), 11)
        leg.setBlockNumber(18)
        self.assertEqual(leg.getBlockNumber(), 18)

        self.assertEqual(leg.getPointA(), point_a)
        leg.setPointA(point_c)
        self.assertEqual(leg.getPointA(), point_c)

        self.assertEqual(leg.getPointB(), point_b)
        leg.setPointB(point_d)
        self.assertEqual(leg.getPointB(), point_d)

        self.assertEqual(leg.getType(), SuitLeg.TToToonBuilding)
        leg.setType(SuitLeg.TWalk)
        self.assertEqual(leg.getType(), SuitLeg.TWalk)

        self.assertEqual(leg.getLegTime(), 2)

        # Test getLegTime of the types using SuitTimings
        self.assertEqual(SuitLeg(0, 0, -1, point_a, point_b, SuitLeg.TFromSky).getLegTime(), SuitTimings.FromSky)
        self.assertEqual(SuitLeg(0, 0, -1, point_a, point_b, SuitLeg.TToSky).getLegTime(), SuitTimings.ToSky)
        self.assertEqual(SuitLeg(0, 0, -1, point_a, point_b, SuitLeg.TFromSuitBuilding).getLegTime(), SuitTimings.FromSuitBuilding)
        self.assertEqual(SuitLeg(0, 0, -1, point_a, point_b, SuitLeg.TToSuitBuilding).getLegTime(), SuitTimings.ToSuitBuilding)
        self.assertEqual(SuitLeg(0, 0, -1, point_a, point_b, SuitLeg.TToToonBuilding).getLegTime(), SuitTimings.ToToonBuilding)

        self.assertEqual(leg.getPosA(), Point3(0, 20, 0))
        self.assertEqual(leg.getPosB(), Point3(0, 30, 0))

        self.assertEqual(leg.getPosAtTime(1), Point3(0, 25, 0))

        # Test SuitLeg.getTypeName
        self.assertEqual(SuitLeg.getTypeName(SuitLeg.TWalkFromStreet), 'WalkFromStreet')
        self.assertEqual(SuitLeg.getTypeName(SuitLeg.TWalkToStreet), 'WalkToStreet')
        self.assertEqual(SuitLeg.getTypeName(SuitLeg.TWalk), 'Walk')
        self.assertEqual(SuitLeg.getTypeName(SuitLeg.TFromSky), 'FromSky')
        self.assertEqual(SuitLeg.getTypeName(SuitLeg.TToSky), 'ToSky')
        self.assertEqual(SuitLeg.getTypeName(SuitLeg.TFromSuitBuilding), 'FromSuitBuilding')
        self.assertEqual(SuitLeg.getTypeName(SuitLeg.TToSuitBuilding), 'ToSuitBuilding')
        self.assertEqual(SuitLeg.getTypeName(SuitLeg.TToToonBuilding), 'ToToonBuilding')
        self.assertEqual(SuitLeg.getTypeName(SuitLeg.TFromCogHQ), 'FromCogHQ')
        self.assertEqual(SuitLeg.getTypeName(SuitLeg.TToCogHQ), 'ToCogHQ')
        self.assertEqual(SuitLeg.getTypeName(SuitLeg.TOff), 'Off')
        self.assertEqual(SuitLeg.getTypeName(1337), '**invalid**')

    def test_suit_leg_list(self):
        # Generate and store 6 points
        # STREET_POINT(0, 0, 0) -> STREET_POINT(0, 10, 0) -> STREET_POINT(0, 20, 0) -> STREET_POINT(0, 30, 0) -> STREET_POINT(0, 40, 0)
        # -> FRONT_DOOR_POINT(0, 50, 0)
        points = [self.make_suit_point(i, pos=(0, 10 * i, 0)) for i in xrange(5)]
        for point in points:
            self.store.storeSuitPoint(point)

        for i in xrange(4):
            self.store.storeSuitEdge(i, i + 1, 2000 + i)

        end_point = self.make_suit_point(5, type=DNASuitPoint.FRONT_DOOR_POINT, pos=(0, 50, 0),
                                         landmark_building_index=11)

        self.store.storeSuitPoint(end_point)
        self.store.storeSuitEdge(4, 5, 2004)

        path = DNASuitPath()
        for point in points:
            path.addPoint(point)

        path.addPoint(end_point)

        leg_list = SuitLegList(path, self.store, SUIT_WALK_SPEED)

        # Test types
        self.assertEqual(leg_list.getNumLegs(), 8)
        self.assertEqual(leg_list.getLeg(0).getType(), SuitLeg.TFromSky)
        for i in xrange(1, 5):
            self.assertEqual(leg_list.getLeg(i).getType(), SuitLeg.TWalk)

        self.assertEqual(leg_list.getLeg(5).getType(), SuitLeg.TWalkFromStreet)
        self.assertEqual(leg_list.getLeg(6).getType(), SuitLeg.TToToonBuilding)
        self.assertEqual(leg_list.getLeg(7).getType(), SuitLeg.TOff)

        # Test times
        walk_leg_time = leg_list.getLegTime(1)
        self.assertEqual(walk_leg_time, 10 / SUIT_WALK_SPEED)
        self.assertEqual(leg_list.getStartTime(0), 0)
        self.assertEqual(leg_list.getStartTime(1), SuitTimings.FromSky)
        self.assertEqual(leg_list.getStartTime(2), SuitTimings.FromSky + walk_leg_time)
        self.assertEqual(leg_list.getStartTime(3), SuitTimings.FromSky + walk_leg_time * 2)
        self.assertEqual(leg_list.getStartTime(4), SuitTimings.FromSky + walk_leg_time * 3)
        self.assertEqual(leg_list.getStartTime(5), SuitTimings.FromSky + walk_leg_time * 4)
        self.assertEqual(leg_list.getStartTime(6), SuitTimings.FromSky + walk_leg_time * 5)
        self.assertEqual(leg_list.getStartTime(7), SuitTimings.FromSky + walk_leg_time * 5 + SuitTimings.ToToonBuilding)

if __name__ == '__main__':
    unittest.main()
