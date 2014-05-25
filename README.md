This is a project of a DNA parser for Disney's DNA files. It's (going to be) able to:
	1. Generate graphical nodes.
	2. Handle logical things (for example, cog paths).
	
Note that it's made primarily for Toontown's already existing DNA files. It may read other files or not.

_How it works_

To read the files, they should be first converted to binary format. This is more or less what Panda3D does for models (egg and bam models).
The raw files have *dna* extension and binary files have *pdna* extension. Of course, this is for convenience, you can name them as you want.

To make binary dna files (convert _.dna_ to _.pdna_ files) so they can be read by the parser you should use the tool provided here (TO DO).
Binary files are usually smaller than raw ones. One of the reasons behind this is that this makes parsing the files easier in C++.