from panda3d.core import NodePath
from panda3d.core import Point3
from libpandadna import DNAStorage
from libpandadna import DNAVisGroup
from libpandadna import DNASuitPoint

from panda3d.core import loadPrcFileData
loadPrcFileData('', 'window-type none')

from direct.showbase.ShowBase import ShowBase
base = ShowBase()
import unittest

class TestStorage(unittest.TestCase):
    def test_storage_visgroups(self):
        store = DNAStorage()
        vg = DNAVisGroup("my_vg")

        vg.addVisible("visible1")
        vg.addVisible("visible2")
        vg.addVisible("visible3")

        store.storeDNAVisGroup(vg)
        self.assertEqual(store.getNumDNAVisGroups(), 1)
        self.assertEqual(store.getNumDNAVisGroupsAI(), 1)
        self.assertEqual(store.getDNAVisGroupAI(0), vg)
        self.assertEqual(store.getDNAVisGroupName(0), vg.getName())

        num_visibles = store.getNumVisiblesInDNAVisGroup(0)
        self.assertEqual(num_visibles, 3)

        for i in xrange(num_visibles):
            self.assertEqual(store.getVisibleName(0, i), "visible%d" % (i + 1))

        vg.removeVisible("visible2")
        self.assertEqual(store.getNumVisiblesInDNAVisGroup(0), 2)
        self.assertEqual(store.getVisibleName(0, 0), "visible1")
        self.assertEqual(store.getVisibleName(0, 1), "visible3")

        store.resetDNAVisGroups()
        self.assertEqual(store.getNumDNAVisGroups(), 0)
        self.assertEqual(store.getNumDNAVisGroupsAI(), 0)

    def test_texture(self):
        store = DNAStorage()
        texture1 = loader.loadTexture('files/texture1.png')
        texture2 = loader.loadTexture('files/texture2.png')

        store.storeTexture('texture1', texture1)
        store.storeTexture('texture2', texture2)
        self.assertEqual(store.findTexture('texture1'), texture1)
        self.assertEqual(store.findTexture('texture2'), texture2)
        self.assertEqual(store.findTexture('bad'), None)

        store.resetTextures()

        self.assertEqual(store.findTexture('texture1'), None)
        self.assertEqual(store.findTexture('texture2'), None)

    def test_font(self):
        store = DNAStorage()
        font1 = loader.loadFont('files/arial.ttf')
        font2 = loader.loadFont('files/comic.ttf')

        store.storeFont('font1', font1)
        store.storeFont('font2', font2)
        self.assertEqual(store.findFont('font1'), font1)
        self.assertEqual(store.findFont('font2'), font2)
        self.assertEqual(store.findFont('bad'), None)

        store.resetFonts()

        self.assertEqual(store.findFont('font1'), None)
        self.assertEqual(store.findFont('font2'), None)

    def test_storage_catalog(self):
        store = DNAStorage()
        store.storeCatalogCode('root', 'code1')
        store.storeCatalogCode('root', 'code2')
        store.storeCatalogCode('root', 'code3')

        colors = ('red', 'green', 'blue', 'yellow', 'orange')
        for color in colors:
            store.storeCatalogCode('colors', color)

        self.assertEqual(store.getNumCatalogCodes('colors'), len(colors))

        for i, color in enumerate(colors):
            self.assertEqual(store.getCatalogCode('colors', i), color)

        # 'bad' root must have no codes
        self.assertEqual(store.getNumCatalogCodes('bad'), 0)

    def test_nodes(self):
        store = DNAStorage()
        store.storeNode('files/node.bam', 'dummy', 'node')
        store.storeHoodNode('files/hood_node.bam', 'dummy', 'hood_node')
        store.storePlaceNode('files/place_node.bam', 'dummy', 'place_node')

        self.assertTrue(store.findNode('bad').isEmpty())
        self.assertFalse(store.findNode('node').isEmpty())
        self.assertFalse(store.findNode('hood_node').isEmpty())
        self.assertFalse(store.findNode('place_node').isEmpty())

        store.resetNodes()
        self.assertTrue(store.findNode('node').isEmpty())

        store.resetHoodNodes()
        self.assertTrue(store.findNode('hood_node').isEmpty())

        store.resetPlaceNodes()
        self.assertTrue(store.findNode('place_node').isEmpty())

    def test_blocks(self):
        store = DNAStorage()
        block1 = (
                  4269,                   # block_number
                  "libpandadna",          # title
                  "",                     # article
                  "",                     # bldg_type
                  1337                    # zone_id
        )
        block2 = (
                  1337,                   # block_number
                  "Visual Studio 2010",   # title
                  "",                     # article
                  "",                     # bldg_type
                  4269                    # zone_id
        )
        block3 = (
                  1000,                   # block_number
                  "C++ reader",           # title
                  "",                     # article
                  "",                     # bldg_type
                  4269                    # zone_id
        )

        store.storeBlock(*block1)
        store.storeBlock(*block2)
        store.storeBlock(*block3)

        door1 = NodePath('block-1000')
        door1.setPos(5, 5, 10)
        door1.setH(180)
        store.storeBlockDoor(1000, door1)

        self.assertEqual(store.getNumBlockNumbers(), 3)

        # Test an invalid block number
        self.assertEqual(store.getZoneFromBlockNumber(100), 0)
        self.assertEqual(store.getZoneFromBlockNumber(1000), 4269)
        self.assertEqual(store.getZoneFromBlockNumber(1337), 4269)
        self.assertEqual(store.getZoneFromBlockNumber(4269), 1337)
        self.assertEqual(store.getTitleFromBlockNumber(1000), "C++ reader")
        self.assertEqual(store.getTitleFromBlockNumber(1337), "Visual Studio 2010")
        self.assertEqual(store.getTitleFromBlockNumber(4269), "libpandadna")
        self.assertEqual(store.getBlockNumberAt(0), 4269)
        self.assertEqual(store.getBlockNumberAt(1), 1337)
        self.assertEqual(store.getBlockNumberAt(2), 1000)
        self.assertEqual(store.getDoorPosHprFromBlockNumber(1000), door1)
        self.assertTrue(store.getDoorPosHprFromBlockNumber(1337).isEmpty())

        store.resetBlockNumbers()
        store.resetBlockZones()

        self.assertEqual(store.getTitleFromBlockNumber(1000), "")
        self.assertEqual(store.getTitleFromBlockNumber(1337), "")
        self.assertEqual(store.getTitleFromBlockNumber(4269), "")

    def test_suit_points(self):
        store = DNAStorage()

        point1 = DNASuitPoint(5, DNASuitPoint.STREET_POINT,
                              Point3(100, 20, 0.5))
        point2 = DNASuitPoint(10, DNASuitPoint.STREET_POINT,
                              Point3(100, 0, 0.5))
        point3 = DNASuitPoint(15, DNASuitPoint.FRONT_DOOR_POINT,
                              Point3(100, -20, 0.5), 10)

        store.storeSuitPoint(point1)
        store.storeSuitPoint(point2)
        store.storeSuitPoint(point3)

        self.assertEqual(store.getNumSuitPoints(), 3)
        self.assertEqual(store.getSuitPointAtIndex(0), point1)
        self.assertEqual(store.getSuitPointAtIndex(1), point2)
        self.assertEqual(store.getSuitPointAtIndex(2), point3)
        self.assertEqual(store.getSuitPointWithIndex(5), point1)
        self.assertEqual(store.getSuitPointWithIndex(10), point2)
        self.assertEqual(store.getSuitPointWithIndex(15), point3)

        # Test invalid index
        self.assertEqual(store.getSuitPointWithIndex(1000), None)

        # Test suit edges
        edges = ((5, 10, 2301), (10, 15, 2302), (15, 5, 2303))

        for edge in edges:
            store.storeSuitEdge(*edge)

        for edge in edges:
            dna_edge = store.getSuitEdge(edge[0], edge[1])
            self.assertTrue(dna_edge is not None)
            self.assertEqual(dna_edge.getStartPoint(), store.getSuitPointWithIndex(edge[0]))
            self.assertEqual(dna_edge.getEndPoint(), store.getSuitPointWithIndex(edge[1]))
            self.assertEqual(dna_edge.getZoneId(), edge[2])
            self.assertEqual(store.getSuitEdgeZone(edge[0], edge[1]), edge[2])

        adj_points = store.getAdjacentPoints(point1)
        self.assertEqual(adj_points.getNumPoints(), 1)
        self.assertEqual(adj_points.getPoint(0), point2)
        self.assertEqual(store.getSuitEdgeTravelTime(5, 10, 5), 4)
        self.assertEqual(store.getSuitEdgeTravelTime(10, 15, 5), 4)
        self.assertEqual(store.getSuitEdgeTravelTime(15, 5, 5), 8)

        # Test suit path
        path = store.getSuitPath(point1, point3, 1, 10)
        self.assertEqual(path.getNumPoints(), 3)
        self.assertEqual(path.getPoint(0), point1)
        self.assertEqual(path.getPoint(1), point2)
        self.assertEqual(path.getPoint(2), point3)

        # Test invalid values
        store.storeSuitEdge(1, 2, 2800)
        self.assertEqual(store.getSuitEdge(1, 2), None)
        self.assertEqual(store.getSuitEdge(145, 13442), None)
        self.assertEqual(store.getSuitEdgeTravelTime(1, 2, 5), 0)
        self.assertEqual(repr(store.getSuitEdgeTravelTime(10, 15, 0)), 'inf')  # Division by 0

        point4 = DNASuitPoint(400, DNASuitPoint.STREET_POINT, Point3(0, 0, 0))
        self.assertEqual(store.getSuitPath(point4, point2, 1, 10), None)

        # Reset
        store.resetSuitPoints()
        self.assertEqual(store.getSuitPointWithIndex(5), None)
        self.assertEqual(store.getSuitPointWithIndex(10), None)
        self.assertEqual(store.getSuitPointWithIndex(15), None)
        self.assertTrue(store.discoverContinuity())

if __name__ == '__main__':
    unittest.main()
