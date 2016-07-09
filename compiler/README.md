compiler
========
_compiler_ for _libpandadna_ is a utility designed to convert a raw DNA file into a small, easily readable and understandable binary format. This is more or less what Panda3D does with their **bam** model files. Raw DNA files have a **dna** extension, and binary DNA files have a **pdna** extension. This is, of course, for convenience. The extensions can be changed to whatever is desired.

The thirdparty package _ply_ is required for this script to function. Use this command in order to obtain _ply_ with pip:
```
pip install ply
```

### Usage ###
    python compile.py [-h] [--compress] [--verbose] [--logfile LOGFILE]
                      filenames [filenames ...]

### Example ###
    python compile.py storage.dna

### More info ###
    positional arguments:
      filenames              The raw input file(s). Accepts * and ? as wildcards.

    optional arguments:
      -h, --help            Show this help message and exit.
      --compress, -c        Compress the output file using ZLib.
      --verbose, -v         Describe the build process.
      --logfile LOGFILE, -l LOGFILE
                            Optional file to write the console output to.
