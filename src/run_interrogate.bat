@echo off

set PANDA_DIR=%1
set SRC_DIR=%2
echo %PANDA_DIR%

set MODULE=base

echo Interrogating %MODULE%

set CMD=%PANDA_DIR%\bin\interrogate.exe -D__inline -DCPPPARSER -DP3_INTERROGATE=1 -D__cplusplus -fnames -string -refcount -assert
set CMD=%CMD% -S %PANDA_DIR%\include\parser-inc -S %PANDA_DIR%\include -I %PANDA_DIR%\include -I%SRC_DIR%\suit -I%SRC_DIR%\base -I%SRC_DIR%\components
set CMD=%CMD% -srcdir %SRC_DIR%\%MODULE% -oc %SRC_DIR%\%MODULE%_igate.cxx -od %SRC_DIR%\%MODULE%.in -python-native -DCPPPARSER -D__STDC__=1 -D__cplusplus
set CMD=%CMD% -D__inline -longlong __int64 -D_X86_ -DWIN32_VC -DWIN32 -D_WIN32 -module libpandadna -library %MODULE% -Dvolatile=
set CMD=%CMD% DNAStorage.h DNALoader.h
%CMD%

set MODULE=suit

echo Interrogating %MODULE%

set CMD=%PANDA_DIR%\bin\interrogate.exe -D__inline -DCPPPARSER -DP3_INTERROGATE=1 -D__cplusplus -fnames -string -refcount -assert
set CMD=%CMD% -S %PANDA_DIR%\include\parser-inc -S %PANDA_DIR%\include -I %PANDA_DIR%\include -I%SRC_DIR%\suit -I%SRC_DIR%\base -I%SRC_DIR%\components
set CMD=%CMD% -srcdir %SRC_DIR%\%MODULE% -oc %SRC_DIR%\%MODULE%_igate.cxx -od %SRC_DIR%\%MODULE%.in -python-native -DCPPPARSER -D__STDC__=1 -D__cplusplus
set CMD=%CMD%  -D__inline -longlong __int64 -D_X86_ -DWIN32_VC -DWIN32 -D_WIN32 -module libpandadna -library %MODULE% -Dvolatile=
set CMD=%CMD% DNASuitPoint.h DNASuitPath.h DNASuitEdge.h SuitLeg.h SuitLegList.h
%CMD%

set MODULE=components

echo Interrogating %MODULE%

set CMD=%PANDA_DIR%\bin\interrogate.exe -D__inline -DCPPPARSER -DP3_INTERROGATE=1 -D__cplusplus -fnames -string -refcount -assert
set CMD=%CMD% -S %PANDA_DIR%\include\parser-inc -S %PANDA_DIR%\include -I %PANDA_DIR%\include -I%SRC_DIR%\suit -I%SRC_DIR%\base -I%SRC_DIR%\components
set CMD=%CMD% -srcdir %SRC_DIR%\%MODULE% -oc %SRC_DIR%\%MODULE%_igate.cxx -od %SRC_DIR%\%MODULE%.in -python-native -DCPPPARSER -D__STDC__=1 -D__cplusplus
set CMD=%CMD%  -D__inline -longlong __int64 -D_X86_ -DWIN32_VC -DWIN32 -D_WIN32 -module libpandadna -library %MODULE% -Dvolatile=
set CMD=%CMD% DNAGroup.h DNAVisGroup.h DNANode.h DNAProp.h DNASign.h DNASignBaseline.h DNASignGraphic.h DNAFlatBuilding.h
set CMD=%CMD% DNAWall.h DNAWindows.h DNACornice.h DNALandmarkBuilding.h DNAAnimProp.h DNAInteractiveProp.h DNAAnimBuilding.h
set CMD=%CMD% DNADoor.h DNAFlatDoor.h DNAStreet.h DNABattleCell.h
%CMD%
