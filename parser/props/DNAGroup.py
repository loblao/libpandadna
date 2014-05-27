import struct


class DNAGroup:
    PROP_CODE = 1

    def __init__(self, name):
        self.name = name
        self.children = []
        self.parent = None
        self.visGroup = None

    def setName(self, name):
        self.name = name

    def getName(self):
        return self.name

    def add(self, child):
        self.children.append(child)

    def remove(self, child):
        self.children.remove(child)

    def getNumChildren(self):
        return len(self.children)

    def at(self, index):
        return self.children[index]

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

    def debug(self, message):
        if self.verbose:
            print 'DNAGroup:', message

    def traverse(self, recursive=True, verbose=False):
        self.verbose = verbose

        self.debug('created... prop code: {0}'.format(self.PROP_CODE))
        data = struct.pack('>B', self.PROP_CODE)  # Prop code

        name = self.getName()
        data += struct.pack('>B', len(name))  # Name length
        self.debug('packing... name length: {0}'.format(len(name)))
        data += name  # Name
        self.debug('packing... name: {0}'.format(name))

        parent = self.getParent()
        if parent:
            parentName = parent.getName()
        else:
            parentName = None
        if parentName is None:
            data += struct.pack('>B', 0)  # Parent name length
            self.debug('skipped... parent name length')
            self.debug('skipped... parent name')
        else:
            data += struct.pack('>B', len(parentName))  # Parent name length
            self.debug('packing... parent name length: {0}'.format(len(parentName)))
            data += parentName  # Parent name
            self.debug('packing... parent name: {0}'.format(parentName))

        visGroup = self.getVisGroup()
        if visGroup:
            visGroupName = visGroup.getName()
        else:
            visGroupName = None
        if visGroupName is None:
            data += struct.pack('>B', 0)  # DNAVisGroup name length
            self.debug('skipped... DNAVisGroup name length')
            self.debug('skipped... DNAVisGroup name')
        else:
            data += struct.pack('>B', len(visGroupName))  # DNAVisGroup name length
            self.debug('packing... DNAVisGroup name length: {0}'.format(len(visGroupName)))
            data += visGroupName  # DNAVisGroup name
            self.debug('packing... DNAVisGroup name: {0}'.format(visGroupName))

        if recursive:
            for child in self.children:
                data += child.traverse(recursive=True, verbose=verbose)

        return data
