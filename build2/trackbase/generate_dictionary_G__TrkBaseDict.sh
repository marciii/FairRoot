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

/home/marci/fair_install/FairSoftInst/bin/rootcint -f /home/marci/fair_install/FairRoot/build2/trackbase/G__TrkBaseDict.cxx -rmf /home/marci/fair_install/FairRoot/build2/lib/libTrkBase.rootmap -rml TrkBase.so -c   -I/home/marci/fair_install/FairRoot/fairtools -I/home/marci/fair_install/FairRoot/geobase -I/home/marci/fair_install/FairRoot/parbase -I/home/marci/fair_install/FairRoot/base -I/home/marci/fair_install/FairRoot/base/steer -I/home/marci/fair_install/FairRoot/base/event -I/home/marci/fair_install/FairRoot/base/field -I/home/marci/fair_install/FairRoot/base/sim -I/home/marci/fair_install/FairRoot/base/source -I/home/marci/fair_install/FairRoot/field -I/home/marci/fair_install/FairRoot/passive -I/home/marci/fair_install/FairRoot/trackbase -I/home/marci/fair_install/FairSoftInst/include/root -I/home/marci/fair_install/FairSoftInst/include FairTrackPar.h FairTrackParP.h FairTrackParH.h FairGeaneUtil.h TrackBaseLinkDef.h
