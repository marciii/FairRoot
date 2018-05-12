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

/home/marci/fair_install/FairSoftInst/bin/rootcint -f /home/marci/fair_install/FairRoot/build2/eventdisplay/G__EventDisplayDict.cxx -rmf /home/marci/fair_install/FairRoot/build2/lib/libEventDisplay.rootmap -rml EventDisplay.so -c   -I/home/marci/fair_install/FairRoot/fairtools -I/home/marci/fair_install/FairRoot/geobase -I/home/marci/fair_install/FairRoot/parbase -I/home/marci/fair_install/FairRoot/base -I/home/marci/fair_install/FairRoot/base/steer -I/home/marci/fair_install/FairRoot/base/event -I/home/marci/fair_install/FairRoot/base/field -I/home/marci/fair_install/FairRoot/base/sim -I/home/marci/fair_install/FairRoot/base/source -I/home/marci/fair_install/FairRoot/trackbase -I/home/marci/fair_install/FairRoot/geane -I/home/marci/fair_install/FairRoot/eventdisplay -I/home/marci/fair_install/FairSoftInst/include/root -I/home/marci/fair_install/FairSoftInst/include -I/home/marci/fair_install/FairSoftInst/include/TGeant3 FairEventManager.h FairMCTracks.h FairEventManagerEditor.h FairMCTracksEditor.h FairBoxSet.h FairBoxSetDraw.h FairBoxSetEditor.h FairPointSetDraw.h FairMCPointDraw.h FairHitDraw.h FairHitPointSetDraw.h FairTimeStampPointDraw.h FairXMLNode.h EventDisplayLinkDef.h
