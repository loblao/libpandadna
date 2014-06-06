This is the C++ part of the project. It reads the pdna files.

_How to compile_

First, you *must* use the same Visual Studio version that the Panda3D version you are compiling it against is compiled.
Usually, it's VS 2008. You may use the _.sln_ file provided here to launch the VS 2008 environment.

Go to your Panda3D dir (I'll call it $PANDA from now)/include/parser-inc.
Open windows.h and manually comment out this part (around line 50):

union LARGE_INTEGER {
  __int64 QuadPart;
}

Almost done. Now, in Visual Studio:
- Add all panda3d directories to include/lib path (and python dirs too!)
- Set mode to Release
- Update run_interrogate to match your Panda3D directory. Replace all _C:\Panda3D_1.8.1_ by your path.
- Now you can compile. If it works, you'll have _libpandadna.dll_ in _Release_ dir!
