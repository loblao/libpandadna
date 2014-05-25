import DNAProp

#fonts have syntax:
#store_font [ "font" "suit"
#             "phase_3/models/fonts/vtRemingtonPortable.ttf" ]

# so we take one command as the file
# that's also why it behaves like a prop
# although it isn't

class DNAFont(DNAProp.DNAProp):
    def __init__(self, storage, name):
        DNAProp.DNAProp.__init__(self, storage)
            
        self.name = name
        self.file = None
        
    def doCommand(self, x):
        self.file = x