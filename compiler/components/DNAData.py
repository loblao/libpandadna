from DNAGroup import DNAGroup
from parse import *
import ply.yacc as yacc
from tokens import *


class DNAData(DNAGroup):
    def __init__(self, name):
        DNAGroup.__init__(self, name)

        self.coordSystem = 0
        self.dnaFilename = ''
        self.dnaStorage = None

    def getCoordSystem(self):
        return self.coordSystem

    def getDnaFilename(self):
        return self.dnaFilename

    def getDnaStorage(self):
        return self.dnaStorage

    def setCoordSystem(self, system):
        self.coordSystem = system

    def setDnaFilename(self, filename):
        self.dnaFilename = filename

    def setDnaStorage(self, storage):
        self.dnaStorage = storage

    def read(self, stream):
        parser = yacc.yacc(debug=0, optimize=0)
        parser.dnaData = self
        parser.parentGroup = parser.dnaData
        parser.dnaStore = self.getDnaStorage()
        parser.modelName = None
        parser.modelType = None
        parser.parse(stream.read())
