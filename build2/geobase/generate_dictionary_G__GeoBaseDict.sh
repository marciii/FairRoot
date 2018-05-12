#!/bin/bash

# This macro is used to generate the ROOT dictionaries
# To use the ctest launchers one needs some environment variables which
# are only present when running CMake. To have the same environment at
# the time the dictionary is build this script is used which is build
# at the time cmake runs.

# Setup the needed environment
export LD_LIBRARY_PATH=/home/marci/fair_install/FairSoftInst/lib/root::
export DYLD_LIBRARY_PATH=/home/marci/fair_install/FairSoftInst/lib/root::
export ROOTSYS=/home/marci/fair_install/FairSoftInst

/home/marci/fair_install/FairSoftInst/bin/rootcint -f /home/marci/fair_install/FairRoot/build2/geobase/G__GeoBaseDict.cxx -rmf /home/marci/fair_install/FairRoot/build2/lib/libGeoBase.rootmap -rml GeoBase.so -c   -I/home/marci/fair_install/FairRoot/fairtools -I/home/marci/fair_install/FairRoot/geobase -I/home/marci/fair_install/FairSoftInst/include/root FairGeoAssembly.h FairGeoCone.h FairGeoCons.h FairGeoEltu.h FairGeoBuilder.h FairGeoInterface.h FairGeoIo.h FairGeoLoader.h FairGeoMatrix.h FairGeoMedia.h FairGeoMedium.h FairGeoNode.h FairGeoOldAsciiIo.h FairGeoPcon.h FairGeoPgon.h FairGeoRootBuilder.h FairGeoRotation.h FairGeoSet.h FairGeoShapes.h FairGeoSphe.h FairGeoTransform.h FairGeoTrap.h FairGeoTrd1.h FairGeoTube.h FairGeoTubs.h FairGeoTorus.h FairGeoVector.h FairGeoVolume.h FairGeoCompositeVolume.h FairGeoAsciiIo.h FairGeoBrik.h FairGeoBasicShape.h GeoBaseLinkDef.h
