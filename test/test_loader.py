from panda3d.core import Filename
from panda3d.core import Point3
from panda3d.core import StringStream
from panda3d.core import loadPrcFileData
from libpandadna import DNAStorage
from libpandadna import DNALoader
from libpandadna import DNAGroup
from libpandadna import DNAVisGroup
from libpandadna import DNAProp
from libpandadna import DNAVisGroup
from libpandadna import DNALandmarkBuilding
import unittest
import subprocess
import sys
import os

# Make sure DNALoader can find test.pdna in model path
loadPrcFileData('', 'model-path files')


class TestLoader(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.loader = DNALoader()
        print('Compiling test.dna')
        command = "python %s files/test.dna" % os.path.join("..", "compiler", "compile.py")
        subprocess.check_call(command, stdout=sys.stdout, stderr=sys.stderr, shell=True)

    def check_store(self, store):
        self.assertFalse(store.findTexture("texture1") is None)
        self.assertFalse(store.findTexture("texture2") is None)
        self.assertTrue(store.findTexture("texture3") is None)

        self.assertEqual(store.getNumCatalogCodes("nodes"), 3)
        self.assertEqual(store.getNumDNAVisGroups(), 1)
        self.assertEqual(store.getDNAVisGroupName(0), "1000")
        self.assertEqual(store.getNumSuitPoints(), 4)

        for i in xrange(store.getNumSuitPoints()):
            point = store.getSuitPointAtIndex(i)
            self.assertEqual(point.getIndex(), i)
            self.assertEqual(store.getAdjacentPoints(point).getNumPoints(), 1)

    def test_loader(self):
        store = DNAStorage()
        np = self.loader.loadDNAFile(store, Filename('test.pdna'))

        self.check_store(store)

        expected_repr = '''PandaNode dna
  PandaNode root
    PandaNode test
      PandaNode 1000
        PandaNode subgroup
          ModelNode prop_test T:(pos -12 5 7 hpr 180 15 0) S:(ColorScaleAttrib)
          PandaNode tb3:test_block [DNACode]
          PandaNode sb3:test_block'''
        ss = StringStream()
        np.ls(ss)
        self.assertEqual(ss.getData().strip(), expected_repr)

    def test_loader_ai(self):
        store = DNAStorage()
        root = self.loader.loadDNAFileAI(store, Filename('test.pdna'))

        self.check_store(store)

        def check_name_class_and_children_count(comp, klass, name, num_children=1):
            self.assertEqual(comp.getName(), name)
            self.assertEqual(comp.__class__, klass)
            self.assertEqual(comp.getNumChildren(), num_children)

        check_name_class_and_children_count(root, DNAGroup, "root")

        test_group = root.at(0)
        check_name_class_and_children_count(test_group, DNAGroup, "test")

        test_visgroup = test_group.at(0)
        self.assertEqual(store.getDNAVisGroupAI(0), test_visgroup)
        check_name_class_and_children_count(test_visgroup, DNAVisGroup, "1000")

        test_subgroup = test_visgroup.at(0)
        check_name_class_and_children_count(test_subgroup, DNAGroup, "subgroup",
                                            num_children=2)

        test_prop = test_subgroup.at(0)
        check_name_class_and_children_count(test_prop, DNAProp, "prop_test",
                                            num_children=0)

        test_building = test_subgroup.at(1)
        check_name_class_and_children_count(test_building, DNALandmarkBuilding,
                                            "tb3:test_block", num_children=0)

    def test_load_invalid_file(self):
        store = DNAStorage()
        root = self.loader.loadDNAFile(store, Filename('invalid.pdna'))
        self.assertTrue(root.isEmpty())

        root = self.loader.loadDNAFileAI(store, Filename('invalid.pdna'))
        self.assertTrue(root is None)

if __name__ == '__main__':
    unittest.main()
