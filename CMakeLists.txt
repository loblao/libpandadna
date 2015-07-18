cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)
project(libpandadna)

find_package(PythonLibs)
if (NOT PYTHONLIBS_FOUND)
    message(FATAL_ERROR "Python not found.")
endif()

### Panda3D dir ###
SET(PANDA_DIR "C:\\Panda3D-1.9.0" CACHE STRING "Panda3D directory.")
execute_process(COMMAND "${CMAKE_SOURCE_DIR}/src/run_interrogate" "${PANDA_DIR}" "${CMAKE_SOURCE_DIR}/src")

### Define core components ###
set(BASE_FILES
    src/base/DNALoader.h
    src/base/DNALoader.cxx
    src/base/DNAStorage.h
    src/base/DNAStorage.cxx
    src/base/dnabase.h
    src/base/config_dna.h
    src/base/config_dna.cxx
)

set(SUIT_FILES
    src/suit/DNASuitPath.h
    src/suit/DNASuitPath.cxx
    src/suit/DNASuitEdge.h
    src/suit/DNASuitEdge.cxx
    src/suit/DNASuitPoint.h
    src/suit/DNASuitPoint.cxx
    src/suit/SuitLeg.h
    src/suit/SuitLeg.cxx
    src/suit/SuitLegList.h
    src/suit/SuitLegList.cxx
)

set(COMPONENTS_FILES
    src/components/DNAAnimBuilding.cxx
    src/components/DNAAnimBuilding.h
    src/components/DNAAnimProp.cxx
    src/components/DNAAnimProp.h
    src/components/DNABattleCell.cxx
    src/components/DNABattleCell.h
    src/components/DNACornice.cxx
    src/components/DNACornice.h
    src/components/DNADoor.cxx
    src/components/DNADoor.h
    src/components/DNAFlatBuilding.cxx
    src/components/DNAFlatBuilding.h
    src/components/DNAFlatDoor.cxx
    src/components/DNAFlatDoor.h
    src/components/DNAGroup.cxx
    src/components/DNAGroup.h
    src/components/DNAInteractiveProp.cxx
    src/components/DNAInteractiveProp.h
    src/components/DNALandmarkBuilding.cxx
    src/components/DNALandmarkBuilding.h
    src/components/DNANode.cxx
    src/components/DNANode.h
    src/components/DNAProp.cxx
    src/components/DNAProp.h
    src/components/DNASign.cxx
    src/components/DNASign.h
    src/components/DNASignBaseline.cxx
    src/components/DNASignBaseline.h
    src/components/DNASignGraphic.cxx
    src/components/DNASignGraphic.h
    src/components/DNAStreet.cxx
    src/components/DNAStreet.h
    src/components/DNAVisGroup.cxx
    src/components/DNAVisGroup.h
    src/components/DNAWall.cxx
    src/components/DNAWall.h
    src/components/DNAWindows.cxx
    src/components/DNAWindows.h
)

set(IGATE_FILES
    src/base_igate.cxx
    src/suit_igate.cxx
    src/components_igate.cxx
    src/libpandadna_module.cxx
)

include_directories(src/base)
include_directories(src/suit)
include_directories(src/components)
include_directories(${PANDA_DIR}/include)
include_directories(${PYTHON_INCLUDE_DIR})
link_directories(${PANDA_DIR}/lib)

set(LIBPFX "")
if(WIN32)
    set(LIBPFX "lib")
    add_definitions(/wd4275)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	execute_process(COMMAND "${CMAKE_C_COMPILER}" -dumpversion OUTPUT_VARIABLE GCC_VERSION)
	message(STATUS "GCC Version: ${GCC_VERSION}")
	if(GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
		add_definitions(-std=c++11) # Enable the new C++ standard
	else()
		add_definitions(-std=c++0x) # Enable the new C++ standard
	endif()
endif()

add_definitions(-DBUILDING_DNA)

set(PANDA_LIBS
    ${LIBPFX}p3framework
    ${LIBPFX}panda
    ${LIBPFX}pandafx
    ${LIBPFX}pandaexpress
    ${LIBPFX}p3dtool
    ${LIBPFX}p3dtoolconfig
    ${LIBPFX}p3direct
    ${LIBPFX}p3pandatoolbase
)

add_library(libpandadna SHARED
    ${BASE_FILES}
    ${SUIT_FILES}
    ${COMPONENTS_FILES}
    ${IGATE_FILES}
)

if(WIN32)
    SET_TARGET_PROPERTIES(libpandadna PROPERTIES SUFFIX ".pyd")
endif()

target_link_libraries(libpandadna ${PANDA_LIBS} ${PYTHON_LIBRARY})

add_custom_command(TARGET libpandadna
                   PRE_BUILD
                   COMMAND ${CMAKE_SOURCE_DIR}/src/run_interrogate ARGS "${PANDA_DIR}" "${CMAKE_SOURCE_DIR}/src"
                   COMMENT "Interrogate")

### Setup source groups and defines for configurables ###
source_group("base" FILES ${BASE_FILES})
source_group("suit" FILES ${SUIT_FILES})
source_group("components" FILES ${COMPONENTS_FILES})
source_group("interrogate_files" FILES ${IGATE_FILES})

