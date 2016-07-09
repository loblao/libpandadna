from panda3d.core import NodePath
from panda3d.core import Point3
from panda3d.core import Vec3
from panda3d.core import Vec4
from libpandadna import DNAAnimBuilding
from libpandadna import DNAAnimProp
from libpandadna import DNABattleCell
from libpandadna import DNACornice
from libpandadna import DNADoor
from libpandadna import DNAFlatBuilding
from libpandadna import DNAFlatDoor
from libpandadna import DNAGroup
from libpandadna import DNAInteractiveProp
from libpandadna import DNALandmarkBuilding
from libpandadna import DNANode
from libpandadna import DNAProp
from libpandadna import DNASignGraphic
from libpandadna import DNAStorage
from libpandadna import DNAStreet
from libpandadna import DNASuitEdge
from libpandadna import DNASuitPoint
from libpandadna import DNAVisGroup
from libpandadna import DNAWall
from libpandadna import DNAWindows
import unittest


class TestComponents(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.store = DNAStorage()
        cls.defaultColor = Vec4(1)

    def _test_color_and_code(self, comp):
        self.assertEqual(comp.getColor(), self.defaultColor)
        color = Vec4(1, .5, .3, .1)
        comp.setColor(color)
        self.assertEqual(comp.getColor(), color)

        self.assertEqual(comp.getCode(), '')
        comp.setCode('test_code')
        self.assertEqual(comp.getCode(), 'test_code')

    def test_anim_building(self):
        bldg = DNAAnimBuilding('anim_bldg')

        self.assertEqual(bldg.getAnimName(), '')
        bldg.setAnimName('test_anim')
        self.assertEqual(bldg.getAnimName(), 'test_anim')

    def test_anim_prop(self):
        prop = DNAAnimProp('anim_prop')

        self.assertEqual(prop.getAnimName(), '')
        prop.setAnimName('test_anim')
        self.assertEqual(prop.getAnimName(), 'test_anim')

    def test_battle_cell(self):
        cell = DNABattleCell(20, 20, Point3(10, 10, 3))

        self.assertEqual(cell.getPos(), Point3(10, 10, 3))
        cell.setPos(Point3(25, -40, 0))
        self.assertEqual(cell.getPos(), Point3(25, -40, 0))

        self.assertEqual(cell.getWidth(), 20)
        cell.setWidth(30)
        self.assertEqual(cell.getWidth(), 30)

        self.assertEqual(cell.getHeight(), 20)
        cell.setHeight(30)
        self.assertEqual(cell.getHeight(), 30)

        cell.setWidthHeight(55, 60)
        self.assertEqual(cell.getWidth(), 55)
        self.assertEqual(cell.getHeight(), 60)

    def test_cornice(self):
        cornice = DNACornice('cornice')
        self._test_color_and_code(cornice)

    def test_door(self):
        door = DNACornice('door')
        self._test_color_and_code(door)

    def test_flat_building(self):
        bldg = DNAFlatBuilding('flat_bldg')

        self.assertEqual(bldg.getWidth(), 0)
        bldg.setWidth(15.82)
        self.assertAlmostEqual(bldg.getWidth() - 15.82, 0, places=6)

        self.assertEqual(bldg.getHasDoor(), False)
        bldg.setHasDoor(True)
        self.assertEqual(bldg.getHasDoor(), True)

    def test_group(self):
        group1 = DNAGroup('groupA')
        group2 = DNAGroup('group2')
        group3 = DNAGroup('group3')

        self.assertEqual(group1.getName(), 'groupA')
        group1.setName('group1')
        self.assertEqual(group1.getName(), 'group1')

        self.assertEqual(group1.getNumChildren(), 0)
        group1.add(group2)
        self.assertEqual(group1.getNumChildren(), 1)
        self.assertEqual(group1.at(0), group2)

        visgroup = DNAVisGroup('vg')

        self.assertEqual(group1.getVisGroup(), None)
        group1.setVisGroup(visgroup)
        self.assertEqual(group1.getVisGroup(), visgroup)

        self.assertEqual(group1.getParent(), None)
        group1.setParent(group3)
        self.assertEqual(group1.getParent(), group3)
        group1.clearParent()
        self.assertEqual(group1.getParent(), None)
        self.assertEqual(group1.getVisGroup(), None)

        # Now let's test if interrogates casts the object types correctly
        # For this we use a DNAFlatDoor, but anything inheriting from DNAGroup
        # must do
        flatdoor = DNAFlatDoor('flatdoor')

        # 1. Visgroup
        group1.setVisGroup(flatdoor)
        self.assertEqual(group1.getVisGroup(), flatdoor)

        # 2. At
        group1.add(flatdoor)
        self.assertEqual(group1.at(1), flatdoor)  # N.B. at(0) is the DNAGroup we added above

    def test_interactive_prop(self):
        prop = DNAInteractiveProp('interactive_prop')

        self.assertEqual(prop.getAnimName(), '')
        prop.setAnimName('test_anim')
        self.assertEqual(prop.getAnimName(), 'test_anim')

        self.assertEqual(prop.getCellId(), -1)
        prop.setCellId(18)
        self.assertEqual(prop.getCellId(), 18)

    def test_landmark_building(self):
        bldg = DNALandmarkBuilding('landmark_bldg')

        self.assertEqual(bldg.getWallColor(), self.defaultColor)
        bldg.setWallColor(Vec4(.52, .24, .13, .71))
        self.assertEqual(bldg.getWallColor(), Vec4(.52, .24, .13, .71))

        self.assertEqual(bldg.getCode(), '')
        bldg.setCode('test_code')
        self.assertEqual(bldg.getCode(), 'test_code')

    def test_node(self):
        node = DNANode('node')

        # N.B. DNANode default pos, hpr and scale are uninitialized values
        # Therefore, testing them is unreliable

        node.setPos(Vec3(5.3, 8.2, 15.9))
        self.assertEqual(node.getPos(), Vec3(5.3, 8.2, 15.9))

        node.setHpr(Vec3(1, 2, 3))
        self.assertEqual(node.getHpr(), Vec3(1, 2, 3))

        node.setScale(Vec3(2, 4.7, 6.9))
        self.assertEqual(node.getScale(), Vec3(2, 4.7, 6.9))

    def test_prop(self):
        prop = DNAProp('prop')
        self._test_color_and_code(prop)

    def test_sign_graphic(self):
        sign = DNASignGraphic('sign')

        self.assertEqual(sign.getWidth(), 0)
        sign.setWidth(10)
        self.assertEqual(sign.getWidth(), 10)

        self.assertEqual(sign.getHeight(), 0)
        sign.setHeight(15)
        self.assertEqual(sign.getHeight(), 15)

    def test_street(self):
        street = DNAStreet('street')

        self.assertEqual(street.getCode(), '')
        street.setCode('streetcode')
        self.assertEqual(street.getCode(), 'streetcode')

        self.assertEqual(street.getStreetTexture(), '')
        street.setStreetTexture('streettexture')
        self.assertEqual(street.getStreetTexture(), 'streettexture')

        self.assertEqual(street.getSidewalkTexture(), '')
        street.setSidewalkTexture('sidewalktexture')
        self.assertEqual(street.getSidewalkTexture(), 'sidewalktexture')

        self.assertEqual(street.getCurbTexture(), '')
        street.setCurbTexture('curbtexture')
        self.assertEqual(street.getCurbTexture(), 'curbtexture')

        self.assertEqual(street.getStreetColor(), self.defaultColor)
        street.setStreetColor(Vec4(.3, .5, .5, 1))
        self.assertEqual(street.getStreetColor(), Vec4(.3, .5, .5, 1))

        self.assertEqual(street.getSidewalkColor(), self.defaultColor)
        street.setSidewalkColor(Vec4(.3, .5, .5, 1))
        self.assertEqual(street.getSidewalkColor(), Vec4(.3, .5, .5, 1))

        self.assertEqual(street.getCurbColor(), self.defaultColor)
        street.setCurbColor(Vec4(.3, .5, .5, 1))
        self.assertEqual(street.getCurbColor(), Vec4(.3, .5, .5, 1))

    def test_vis_group(self):
        visgroup = DNAVisGroup('vg')

        # Test visibles
        self.assertEqual(visgroup.getNumVisibles(), 0)
        visgroup.addVisible('test1')
        visgroup.addVisible('test2')
        visgroup.addVisible('test3')
        self.assertEqual(visgroup.getNumVisibles(), 3)
        for i in xrange(1, 4):
            self.assertEqual(visgroup.getVisible(i - 1), 'test%d' % i)

        self.assertTrue(visgroup.removeVisible('test1'))
        self.assertTrue(visgroup.removeVisible('test2'))

        # Removing a visible which doesn't exist must return False
        self.assertFalse(visgroup.removeVisible('bad'))
        self.assertEqual(visgroup.getNumVisibles(), 1)
        self.assertEqual(visgroup.getVisible(0), 'test3')

        # Test suit edges
        edge1 = DNASuitEdge(DNASuitPoint(1, DNASuitPoint.STREET_POINT, Point3(0, 0, 0)),
                            DNASuitPoint(2, DNASuitPoint.STREET_POINT, Point3(0, 0, 0)),
                            1000)

        edge2 = DNASuitEdge(DNASuitPoint(1, DNASuitPoint.STREET_POINT, Point3(0, 0, 0)),
                            DNASuitPoint(2, DNASuitPoint.STREET_POINT, Point3(0, 0, 0)),
                            1000)

        edge3 = DNASuitEdge(DNASuitPoint(1, DNASuitPoint.STREET_POINT, Point3(0, 0, 0)),
                            DNASuitPoint(2, DNASuitPoint.STREET_POINT, Point3(0, 0, 0)),
                            1000)

        self.assertEqual(visgroup.getNumSuitEdges(), 0)
        visgroup.addSuitEdge(edge1)
        visgroup.addSuitEdge(edge2)
        self.assertEqual(visgroup.getNumSuitEdges(), 2)

        self.assertEqual(visgroup.getSuitEdge(0), edge1)
        self.assertEqual(visgroup.getSuitEdge(1), edge2)

        self.assertTrue(visgroup.removeSuitEdge(edge1))
        self.assertEqual(visgroup.getNumSuitEdges(), 1)
        self.assertEqual(visgroup.getSuitEdge(0), edge2)

        # Removing an edge which doesn't exist must return False
        self.assertFalse(visgroup.removeSuitEdge(edge3))

        # Test battle cells
        cell1 = DNABattleCell(20, 20, Point3(0, 0, 0))
        cell2 = DNABattleCell(20, 20, Point3(0, 0, 0))
        cell3 = DNABattleCell(20, 20, Point3(0, 0, 0))

        self.assertEqual(visgroup.getNumBattleCells(), 0)
        visgroup.addBattleCell(cell1)
        visgroup.addBattleCell(cell2)
        self.assertEqual(visgroup.getNumBattleCells(), 2)

        self.assertEqual(visgroup.getBattleCell(0), cell1)
        self.assertEqual(visgroup.getBattleCell(1), cell2)

        self.assertTrue(visgroup.removeBattleCell(cell1))
        self.assertEqual(visgroup.getNumBattleCells(), 1)
        self.assertEqual(visgroup.getBattleCell(0), cell2)

        # Removing a battle cell which doesn't exist must return False
        self.assertFalse(visgroup.removeBattleCell(cell3))

    def test_wall(self):
        wall = DNAWall('wall')
        self._test_color_and_code(wall)

        self.assertEqual(wall.getHeight(), 0)
        wall.setHeight(11.19)
        self.assertAlmostEqual(wall.getHeight() - 11.19, 0, places=6)

    def test_windows(self):
        windows = DNAWindows('windows')
        self._test_color_and_code(windows)

        self.assertEqual(windows.getWindowCount(), 1)
        windows.setWindowCount(3)
        self.assertEqual(windows.getWindowCount(), 3)

    def test_windows_setup(self):
        self.store.storeNode('files/node.bam', '', 'window_r')
        self.store.storeNode('files/hood_node.bam', '', 'window_l')

        windows = DNAWindows('windows')

        x = .1
        y = .4
        np = NodePath('window_root')
        code = 'window_l'
        scale = 1.25
        color = Vec4(.842, .167, .361, 1)

        windows.makeWindows(x, y, np, code, scale, color, self.store, False)

        # Check if the nodes attributes are correct
        model = np.find('**/node')
        self.assertFalse(model.isEmpty())
        self.assertEqual(model.getPos(np), Point3(x, 0, y))
        self.assertEqual(model.getScale(np), Vec3(scale))

        # Now test with flip = True
        np.removeNode()
        np = NodePath('window_root')

        windows.makeWindows(x, y, np, code, scale, color, self.store, True)
        # Check if the nodes attributes are correct
        model = np.find('**/hood_node')
        self.assertFalse(model.isEmpty())
        self.assertEqual(model.getPos(np), Point3(x, 0, y))
        self.assertEqual(model.getScale(np), Vec3(scale))

    def test_door_setup(self):
        parent_np = NodePath('parent_np')
        parent_np.setPosHpr(0, 10, .5, 180, 0, 0)

        door_origin = parent_np.attachNewNode('door_origin')
        door_origin.setPos(10, -25, .5)

        block = 4
        color = Vec4(.842, .167, .361, 1)

        # Set up door_np nodes
        door_np = NodePath('door_np')

        left_hole = door_np.attachNewNode('door_0_hole_left')
        right_hole = door_np.attachNewNode('door_0_hole_right')

        left_door = door_np.attachNewNode('door_0_left')
        right_door = door_np.attachNewNode('door_0_right')

        door_flat = door_np.attachNewNode('door_0_flat')
        door_trigger = door_np.attachNewNode('door_0_trigger')

        DNADoor.setupDoor(door_np, parent_np, door_origin, self.store, block, color)

        # Check if the nodes attributes and parents are correct
        self.assertEqual(door_np.getPos(door_origin), Point3(0, 0, 0))
        self.assertEqual(door_np.getHpr(door_origin), Point3(0, 0, 0))
        self.assertEqual(door_np.getScale(door_origin), Point3(1, 1, 1))

        def verify_color(color1, color2):
            self.assertAlmostEqual(color1.getX(), color2.getX(), places=4)
            self.assertAlmostEqual(color1.getY(), color2.getY(), places=4)
            self.assertAlmostEqual(color1.getZ(), color2.getZ(), places=4)
            self.assertAlmostEqual(color1.getW(), color2.getW(), places=4)

        verify_color(color, door_np.getColor())

        self.assertEqual(left_hole.getParent(), door_flat)
        self.assertEqual(left_hole.getName(), 'doorFrameHoleLeft')

        self.assertEqual(right_hole.getParent(), door_flat)
        self.assertEqual(right_hole.getName(), 'doorFrameHoleRight')

        self.assertEqual(left_door.getParent(), parent_np)
        self.assertEqual(left_door.getName(), 'leftDoor')
        verify_color(color, right_door.getColor())

        self.assertEqual(right_door.getParent(), parent_np)
        self.assertEqual(right_door.getName(), 'rightDoor')
        verify_color(color, right_door.getColor())

        self.assertEqual(door_trigger.getParent(), parent_np)
        self.assertEqual(door_trigger.getName(), 'door_trigger_%d' % block)

        store_np = self.store.getDoorPosHprFromBlockNumber(block)
        self.assertFalse(store_np.isEmpty())

        # Testing the pos is a pain because of decimal precision
        pos = store_np.getPos()
        self.assertAlmostEqual(pos.getX(), -10, places=2)
        self.assertAlmostEqual(pos.getY(), 35, places=2)
        self.assertAlmostEqual(pos.getZ(), 1, places=2)

        # Sometimes getH() returns -180 and others 180
        # Test the modulus (better than abs I guess)
        self.assertEqual(store_np.getH() % 180, 0)

if __name__ == '__main__':
    unittest.main()
