libpandadna
===========
_libpandadna_ is library made for Panda3D that creates a common format for storing entire 3D worlds containing many groups, models, and textures in a very hierarchal form. It also handles some logical aspects of games, such as dividing specific groups of models or textures into visible chunks that can be hidden or shown on the fly, and enemy pathing.

__NOTE__ - This project is inspired, and based off of Disney's DNA file format created for the now-closed MMORPG - _Toontown Online_, and therefore will be geared towards supporting it.

### Usage ###
In order for the _parser_ to understand raw DNA files, they must first be converted to a smaller, easier to read binary format. This is to more or less what Panda3D does with their **bam** model files, and is done to speed up the process of reading and processing the files. Raw DNA files have a **dna** extension, and binary DNA files have a **pdna** extension. This is, of course, for convenience. The extensions can be changed to whatever is desired.

To convert raw DNA files to their binary format, the _compiler_ utility included with this project can be used.

### Features ###
> * Convert **dna** files to **pdna** through the _compiler_ utility.
> * Optional compression of **pdna** files.
> * Parser written in C++ extended for use in Python.
> * Quick construction of the graph.
> * Logical aspects.
> * Construction of model and texture groups that can be hidden or shown on the fly.

### The Team ###
The main people behind _libpandadna_ are listed below:
* **loblao** - The lead developer of the project, and coordinator who writes most of the graphical parts of the project.
* **xPythonic** - The Python genius who keeps the project clean, and writes most of the logical/lexical parts of the project.

### Contributing ###
We welcome all potential contributors.
