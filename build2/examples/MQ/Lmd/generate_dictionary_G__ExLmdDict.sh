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

/home/marci/fair_install/FairSoftInst/bin/rootcint -f /home/marci/fair_install/FairRoot/build2/examples/MQ/Lmd/G__ExLmdDict.cxx -rmf /home/marci/fair_install/FairRoot/build2/lib/libExLmd.rootmap -rml ExLmd.so -c   -I/home/marci/fair_install/FairRoot/logger -I/home/marci/fair_install/FairRoot/fairtools -I/home/marci/fair_install/FairRoot/geobase -I/home/marci/fair_install/FairRoot/parbase -I/home/marci/fair_install/FairRoot/base -I/home/marci/fair_install/FairRoot/base/steer -I/home/marci/fair_install/FairRoot/base/event -I/home/marci/fair_install/FairRoot/base/field -I/home/marci/fair_install/FairRoot/base/sim -I/home/marci/fair_install/FairRoot/base/source -I/home/marci/fair_install/FairRoot/dbase -I/home/marci/fair_install/FairRoot/dbase/dbInterface -I/home/marci/fair_install/FairRoot/dbase/dbValidation -I/home/marci/fair_install/FairRoot/dbase/dbUtils -I/home/marci/fair_install/FairRoot/input/db -I/home/marci/fair_install/FairRoot/dbase/dbInput -I/home/marci/fair_install/FairRoot/dbase/dbIO -I/home/marci/fair_install/FairRoot/fairmq -I/home/marci/fair_install/FairRoot/fairmq/options -I/home/marci/fair_install/FairRoot/fairmq/tools -I/home/marci/fair_install/FairRoot/base/MQ/devices -I/home/marci/fair_install/FairRoot/base/MQ/policies/Serialization -I/home/marci/fair_install/FairRoot/base/MQ/policies/Storage -I/home/marci/fair_install/FairRoot/base/MQ/baseMQtools -I/home/marci/fair_install/FairRoot/examples/MQ/Lmd -I/home/marci/fair_install/FairRoot/examples/MQ/Lmd/unpacker -I/home/marci/fair_install/FairRoot/MbsAPI -I/home/marci/fair_install/FairRoot/examples/advanced/MbsTutorial/src -I/home/marci/fair_install/FairSoftInst/include/root -I/home/marci/fair_install/FairSoftInst/include -I/home/marci/fair_install/FairSoftInst/include unpacker/FairMBSUnpacker.h LmdLinkDef.h
