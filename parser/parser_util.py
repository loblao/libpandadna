import os
def check_if_files_exist(filelist, vfs = None):
    func = vfs.exists if vfs else os.path.isfile

    for file in filelist:
        if not func(file):
            return False
            
    return True
    
def make_p3d_path(p):
    from panda3d.core import Filename
    p = Filename(p).toOsGeneric()
    if p[1] == ":":
        p = '/%s/%s' % (p[0].lower(), p[3:])
        
    return p
    
def open_file(filename, vfs = None):
    from cStringIO import StringIO
    def _open(x):
        f = open(x, 'rb')
        data = f.read()
        f.close()
        return data
        
    func = lambda x: vfs.readFile(x, 1) if vfs else _open
    return StringIO(func(filename))