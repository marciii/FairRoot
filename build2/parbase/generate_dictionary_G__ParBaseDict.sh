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

/home/marci/fair_install/FairSoftInst/bin/rootcint -f /home/marci/fair_install/FairRoot/build2/parbase/G__ParBaseDict.cxx -rmf /home/marci/fair_install/FairRoot/build2/lib/libParBase.rootmap -rml ParBase.so -c   -I/home/marci/fair_install/FairRoot/fairtools -I/home/marci/fair_install/FairRoot/base -I/home/marci/fair_install/FairRoot/base/steer -I/home/marci/fair_install/FairRoot/base/event -I/home/marci/fair_install/FairRoot/base/field -I/home/marci/fair_install/FairRoot/base/sim -I/home/marci/fair_install/FairRoot/geobase -I/home/marci/fair_install/FairRoot/parbase -I/home/marci/fair_install/FairSoftInst/include/root FairContFact.h FairDetParAsciiFileIo.h FairDetParIo.h FairDetParRootFileIo.h FairGenericParAsciiFileIo.h FairGenericParRootFileIo.h FairParAsciiFileIo.h FairParGenericSet.h FairParIo.h FairParRootFileIo.h FairParSet.h FairParamList.h FairRtdbRun.h FairRuntimeDb.h ParBaseLinkDef.h
