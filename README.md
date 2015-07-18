libpandadna
===========
_libpandadna_ is a library made for Panda3D that creates a common format for storing entire 3D worlds containing many groups, models, and textures in a tree-like form. It also handles some logical aspects of games, such as creating groups of models, textures, and nodes that can be hidden or shown on the fly, and enemy pathing.

__NOTE__ - This project is inspired, and based off of Disney's DNA file format created for the now-closed MMORPG - _Toontown Online_, and therefore will be geared towards supporting it.

### Usage ###
In order for the _parser_ to understand a raw DNA file, the DNA file must first be converted into a small, easily readable and understandable binary format. This is to more or less what Panda3D does with their **bam** model files, and is done to speed up the process of reading and processing the files. Raw DNA files have a **dna** extension, and binary DNA files have a **pdna** extension. This is, of course, for convenience. The extensions can be changed to whatever is desired.

To convert a raw DNA file to binary format, the _compiler_ utility included with this project can be used.

### Features ###
> * _compiler_ utility converts raw DNA files into a small, easily readable and understandable binary format.
> * **pdna** compression.
> * **pdna** reader written in C++ extended for use in Python and Panda3D.
> * Logical aspects, such as visible groups and enemy pathing.

### The Team ###
The main people behind _libpandadna_ are listed below:
* **loblao** - The lead developer of the project, and coordinator who writes most of the graphical parts of the project.
* **xPythonic** - Keeps the project clean, and writes most of the logical/lexical parts of the project.

### Contributing ###
We welcome all potential contributors.
