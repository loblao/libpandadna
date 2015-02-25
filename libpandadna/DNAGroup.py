from common import *
from DNAError import DNAError


class DNAGroup:
    COMPONENT_CODE = 1

    def __init__(self, name):
        self.name = name
        self.children = []
        self.parent = None
        self.visGroup = None

    def setName(self, name):
        self.name = name

    def getName(self):
        return self.name

    def getCode(self):
        return self.code

    def add(self, child):
        self.children.append(child)

    def setVisGroup(self, visGroup):
        self.visGroup = visGroup

    def getVisGroup(self):
        return self.visGroup

    def setParent(self, parent):
        self.parent = parent
        self.visGroup = parent.getVisGroup()

    def getParent(self):
        return self.parent

    def clearParent(self):
        self.parent = None
        self.visGroup = None

    def at(self, index):
        return self.children[index]

    def getNumChildren(self):
        return len(self.children)

    def makeFromDGI(self, dgi):
        self.name = dgi.getString()
        dgi.getString()
        dgi.getString()

    def traverse(self, np, store):
        _np = np.attachNewNode(self.name)
        self.traverseChildren(_np, store)

    # convenience functions
    def raiseCodeNotFound(self, code=None):
        if code is None:
            code = self.code
        _error = '%s code (%s) not found in storage!'
        raise DNAError(_error % (self.__class__.__name__, code))

    def traverseChildren(self, np, store):
        for child in self.children:
            child.traverse(np, store)
