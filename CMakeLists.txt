cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)
project(libpandadna)

### TO DO: Linux and Mac support. Right now, only Windows is supported ###
### and this make list won't work in another OS. ###

### Panda3D dir ###
SET(PANDA_DIR "C:\\Panda3D-1.9.0" CACHE STRING "Panda3D directory.")

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
include_directories(${PANDA_DIR}/python/include)

# TO DO: This is VS specific
add_definitions("/wd4275 -DBUILDING_DNA")

set(PANDA_LIBS
    ${PANDA_DIR}/lib/libp3framework.lib
    ${PANDA_DIR}/lib/libpanda.lib
    ${PANDA_DIR}/lib/libpandafx.lib
    ${PANDA_DIR}/lib/libpandaexpress.lib
    ${PANDA_DIR}/lib/libp3dtool.lib
    ${PANDA_DIR}/lib/libp3dtoolconfig.lib
    ${PANDA_DIR}/lib/libp3direct.lib
    ${PANDA_DIR}/lib/libp3pandatoolbase.lib
)

add_library(libpandadna SHARED
    ${BASE_FILES}
    ${SUIT_FILES}
    ${COMPONENTS_FILES}
    ${IGATE_FILES}
)

SET_TARGET_PROPERTIES(libpandadna PROPERTIES SUFFIX ".pyd")

target_link_libraries(libpandadna ${PANDA_LIBS} ${PANDA_DIR}/python/libs/python27.lib)
link_directories(${PANDA_DIR}/lib)
link_directories(${PANDA_DIR}/python/libs)

add_custom_command(TARGET libpandadna
                   PRE_BUILD
                   COMMAND ${CMAKE_SOURCE_DIR}/src/run_interrogate ARGS "${PANDA_DIR}" "${CMAKE_SOURCE_DIR}/src"
                   COMMENT "Interrogate")

### Setup source groups and defines for configurables ###
source_group("base" FILES ${BASE_FILES})
source_group("suit" FILES ${SUIT_FILES})
source_group("components" FILES ${COMPONENTS_FILES})
source_group("interrogate_files" FILES ${IGATE_FILES})
