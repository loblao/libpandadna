compiler
========
_compiler_ for _libpandadna_ is a utility designed to convert a raw DNA file into a small, easily readable and understandable binary format. This is to more or less what Panda3D does with their **bam** model files. Raw DNA files have a **dna** extension, and binary DNA files have a **pdna** extension. This is, of course, for convenience. The extensions can be changed to whatever is desired.

### Usage ###
    python compile.py [-h] [--output OUTPUT] [--compress] [--verbose]
                      [--logfile LOGFILE]
                      filename

### Example ###
    python compile.py --output storage.pdna storage.dna

### More info ###
    positional arguments:
      filename              The raw input file.

    optional arguments:
      -h, --help            show this help message and exit
      --output OUTPUT, -o OUTPUT
                            The compiled output file. Default: FILENAME.pdna
      --compress, -c        Compress the output file using ZLib.
      --verbose, -v         Describe the build process.
      --logfile LOGFILE, -l LOGFILE
                            Optional file to write the console output to.
