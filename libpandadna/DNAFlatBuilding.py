import DNANode
import random

from DNAWall import DNAWall

from common import *

class DNAFlatBuilding(DNANode.DNANode):
    COMPONENT_CODE = 9
    currentWallHeight = 0

    def __init__(self, name):
        DNANode.DNANode.__init__(self, name)

        self.width = 0
        self.hasDoor = False

    def makeFromDGI(self, dgi):
        DNANode.DNANode.makeFromDGI(self, dgi)
        self.width = dgi.getUint8()
        self.hasDoor = dgi.getBool()
        
    def __setupFlat(self, np, store, char, wallCode):
        name = self.name
        
        if name[:2] != 'tb':
            return
            
        name = char + 'b' + name[2:]
        
        node = np.attachNewNode(name)
        
        scale = Point3(self.scale)
        scale.setX(self.width)
        scale.setZ(DNAFlatBuilding.currentWallHeight)
        
        node.setZ(DNAFlatBuilding.currentWallHeight)
        node.setScale(scale)
        node.setPosHpr(self.pos, self.hpr)
        
        numCodes = store.getNumCatalogCodes(wallCode)
        if numCodes < 1:
            return
        
        wallNode = store.findNode(store.getCatalogCode(wallCode, random.randint(0, numCodes - 1)))
        if not wallNode:
            return
            
        wallNode.copyTo(node)
        
        if self.hasDoor:
            wallNodePath = node.find('wall_*')
            doorNode = store.findNode('suit_door')
            doorNode = doorNode.copyTo(wallNodePath)
            doorNode.setPosHprScale(0.5, 0, 0, 0, 0, 0, 1.0 / self.width, 0,
                                    1.0 / DNAFlatBuilding.currentWallHeight)
            wallNodePath.setEffect(DecalEffect.make())
            
        node.flattenMedium()
        node.stash()    
        
    def setupSuitFlatBuilding(self, np, store):
        self.__setupFlat(np, store, "s", "suit_wall")
        
    def setupCogdoFlatBuilding(self, np, store):
        self.__setupFlat(np, store, "c", "cogdo_wall")
        
    def traverse(self, np, store):
        DNAFlatBuilding.currentWallHeight = 0
        node = np.attachNewNode(self.name)
        
        internalNode = node.attachNewNode(self.name + '-internal')
        
        scale = Point3(self.getScale())
        scale.setX(self.width)
        internalNode.setScale(scale)
        
        node.setPosHpr(self.pos, self.hpr)
        
        for child in self.children:
            if isinstance(child, DNAWall):
                child.traverse(internalNode, store)
                
            else:
                child.traverse(node, store)
                
        if DNAFlatBuilding.currentWallHeight != 0:
            cameraBarrier = store.findNode('wall_camera_barrier')
            
            if cameraBarrier is None:
                self.raiseCodeNotFound('wall_camera_barrier')
                
            cameraBarrier = cameraBarrier.copyTo(internalNode)
            cameraBarrier.setScale((1, 1, DNAFlatBuilding.currentWallHeight))
                    
            self.setupSuitFlatBuilding(np, store)
            self.setupCogdoFlatBuilding(np, store)
            
            internalNode.flattenStrong()
            
            collisionNode = node.find('**/door_*/+CollisionNode')
            if not collisionNode.isEmpty():
                collisionNode.setName('KnockKnockDoorSphere_' + store.getBlock(self.name))
                
            cameraBarrier.wrtReparentTo(np)
            
            wallCollection = internalNode.findAllMatches('wall*')
            wallHolder = node.attachNewNode('wall_holder')
            wallDecal = node.attachNewNode('wall_decal')
            
            windowCollection = internalNode.findAllMatches('**/window*')
            doorCollection = internalNode.findAllMatches('**/door*')
            corniceCollection = internalNode.findAllMatches('**/cornice*_d')
            
            wallCollection.reparentTo(wallHolder)
            windowCollection.reparentTo(wallDecal)
            
            doorCollection.reparentTo(wallDecal)
            corniceCollection.reparentTo(wallDecal)
            
            for i in xrange(wallHolder.getNumChildren()):
                iNode = wallHolder.getChild(i)
                iNode.clearTag('DNACode')
                iNode.clearTag('DNARoot')
                
            wallHolder.flattenStrong()
            wallDecal.flattenStrong()
            
            holderChild0 = wallHolder.getChild(0)
            wallDecal.getChildren().reparentTo(holderChild0)
            
            holderChild0.reparentTo(internalNode)
            holderChild0.setEffect(DecalEffect.make())
            
            wallHolder.removeNode()
            wallDecal.removeNode()
        