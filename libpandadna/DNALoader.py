import sys
sys.setrecursionlimit(10000)

from panda3d.core import *
from direct.stdpy.file import *

from direct.distributed.PyDatagram import PyDatagram
from direct.distributed.PyDatagramIterator import PyDatagramIterator

from common import *
import DNAError

import DNAAnimBuilding
import DNAAnimProp
import DNACornice
import DNADoor
import DNAFlatBuilding
import DNAFlatDoor
import DNAGroup
import DNAInteractiveProp
import DNALandmarkBuilding
import DNANode
import DNAProp
import DNASign
import DNASignBaseline
import DNASignGraphic
import DNASignText
import DNAStreet
import DNAVisGroup
import DNAWall
import DNAWindows

import DNABattleCell
import DNASuitPoint

from DNAStorage import LOAD_ON_DEMAND

compClassTable = {

1: DNAGroup.DNAGroup,
2: DNAVisGroup.DNAVisGroup,
3: DNANode.DNANode,
4: DNAProp.DNAProp,
5: DNASign.DNASign,
6: DNASignBaseline.DNASignBaseline,
7: DNASignText.DNASignText,
8: DNASignGraphic.DNASignGraphic,
9: DNAFlatBuilding.DNAFlatBuilding,
10: DNAWall.DNAWall,
11: DNAWindows.DNAWindows,
12: DNACornice.DNACornice,
13: DNALandmarkBuilding.DNALandmarkBuilding,
14: DNAAnimProp.DNAAnimProp,
15: DNAInteractiveProp.DNAInteractiveProp,
16: DNAAnimBuilding.DNAAnimBuilding,
17: DNADoor.DNADoor,
18: DNAFlatDoor.DNAFlatDoor,
19: DNAStreet.DNAStreet

}

# these components don't have children
CHILDLESS_COMPS = (
                   7, # DNASignText
                   11, # DNAWindows
                   12, # DNACornice
                   17, # DNADoor
                   18, # DNAFlatDoor
                   19 # DNAStreet
                  )

class DNALoader:
    def __init__(self):
        self.curStore = None
        self.curProp = None
                
    def handleStorageData(self, dgi):
        # catalog codes
        numRoots = dgi.getUint16()
        for i in xrange(numRoots):
            root = dgi_extract_string8(dgi)
            
            numCodes = dgi.getUint8()
            for j in xrange(numCodes):
                code = dgi_extract_string8(dgi)
                self.curStore.storeCatalogCode(root, code)
                
        # textures
        numTextures = dgi.getUint16()
        for i in xrange(numTextures):
            code = dgi_extract_string8(dgi)
            filename = dgi_extract_string8(dgi)
            
            self.curStore.storeTexture(code, TexturePool.loadTexture(filename))
            
        # fonts
        numFonts = dgi.getUint16()
        for i in xrange(numFonts):
            code = dgi_extract_string8(dgi)
            filename = dgi_extract_string8(dgi)
            
            if config.GetBool('libpandadna-load-fonts', False):
                self.curStore.storeFont(code, FontPool.loadFont(filename))
        
        # nodes
        self.__handleNode(dgi, self.curStore.storeNode)
        self.__handleNode(dgi, self.curStore.storeHoodNode)
        self.__handleNode(dgi, self.curStore.storePlaceNode)
        
        # blocks
        numBlocks = dgi.getUint16()
        for i in xrange(numBlocks):
            number = dgi.getUint8()
            zone = dgi.getUint16()
            title = dgi_extract_string8(dgi)
            article = dgi_extract_string8(dgi)
            bldgType = dgi_extract_string8(dgi)
            
            self.curStore.storeBlock(number, title, article, bldgType, zone)
            
        # suit points
        numPoints = dgi.getUint16()
        for i in xrange(numPoints):
            index = dgi.getUint16()
            pointType = dgi.getUint8()
            
            x, y, z = [dgi.getInt32() / 100.0 for _ in xrange(3)]
            
            graph = dgi.getUint8()
            landmarkBuildingIndex = dgi.getInt8()
            
            self.curStore.storeSuitPoint(DNASuitPoint.DNASuitPoint(index, pointType, (x, y, z), landmarkBuildingIndex))
            
        # suit edges
        numEdges = dgi.getUint16()
        for i in xrange(numEdges):
            index = dgi.getUint16()
            numPoints = dgi.getUint16()
            
            for j in xrange(numPoints):
                endPoint = dgi.getUint16()
                zoneId = dgi.getUint16()
                self.curStore.storeSuitEdge(index, endPoint, zoneId)
                
        # battle cells
        numCells = dgi.getUint16()
        for i in xrange(numCells):
            w = dgi.getUint8()
            h = dgi.getUint8()
            
            x, y, z = [dgi.getInt32() / 100.0 for _ in xrange(3)]
            
            self.curStore.storeBattleCell(DNABattleCell.DNABattleCell(w, h, (x, y, z)))
            
    def __handleNode(self, dgi, target):            
        numNodes = dgi.getUint16()
        for i in xrange(numNodes):
            code = dgi_extract_string8(dgi)
            filename = dgi_extract_string8(dgi)
            search = dgi_extract_string8(dgi)
            
            if LOAD_ON_DEMAND:
                target((filename, search), code)
                continue
            
            np = loader.loadModel(filename)
            np.setTag('DNACode', code)
            
            if search:
                np = np.find('**/' + search)
                assert not np.isEmpty()
                
            target(np, code)
            
    def handleCompData(self, dgi):
        propCode = dgi.getUint8()
        
        if propCode == 255:
            if self.curProp == None:
                raise DNAError.DNAError('Unexpected 255 found.')
                
            p = self.curProp.getParent()
            if p is not None:
                self.curProp = p
                
            else:
                # if we don't have a parent, be sure we are root
                assert self.curProp.getName() == 'root'
                
        elif propCode in compClassTable:
            klass = compClassTable[propCode]
            
            if klass.__init__.func_code.co_argcount > 1:
                newComp = klass('unnamed_comp')
                
            else:
                newComp = klass()
                
            if propCode == 2: # vis group takes the store as arg
                newComp.makeFromDGI(dgi, self.curStore)
                self.curStore.storeDNAVisGroup(newComp)
                
            else:
                newComp.makeFromDGI(dgi)
            
        else:
            raise DNAError.DNAError('Invalid prop code: %d' % propCode)
            
        if dgi.getRemainingSize():
            if propCode != 255:
                if self.curProp is not None:
                    newComp.setParent(self.curProp)
                    self.curProp.add(newComp)
            
                if propCode not in CHILDLESS_COMPS:
                    self.curProp = newComp
             
            self.handleCompData(dgi)
            # recursive
        
    def __loadDNAFileBase(self, store, file):
        f = open(file, 'rb')
       
        self.curStore = store
        self.curProp = None
        self.hadError = False
        
        data = f.read()
        dg = PyDatagram(data)
        dgi = PyDatagramIterator(dg)
        
        f.close()
        
        header = dgi.extractBytes(5)
        if header != 'PDNA\n':
            raise DNAError.DNAError('Invalid header')
            
        compressed = dgi.getBool()
        dgi.skipBytes(1)
        
        if compressed:
            # Decompress the dgi
            # Sadly we have to extract everything
            # And make another dgi
            import zlib
            
            data = dgi.getRemainingBytes()
            data = zlib.decompress(data)
            
            dg = PyDatagram(data)
            dgi = PyDatagramIterator(dg)

        self.handleStorageData(dgi)
        self.handleCompData(dgi)
            
    def loadDNAFile(self, store, file):
        self.__loadDNAFileBase(store, file)
        
        np = NodePath('dna')
        self.curProp.traverse(np, self.curStore)
        
        self.curStore = None
        self.curProp = None
        
        return np
          
    def loadDNAFileAI(self, store, file):        
        self.__loadDNAFileBase(store, str(file))

        self.curStore = None
        
        assert self.curProp.getName() == 'root'
        
        return self.curProp
    