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

/home/marci/fair_install/FairSoftInst/bin/rootcint -f /home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial4/src/G__Tutorial4Dict.cxx -rmf /home/marci/fair_install/FairRoot/build2/lib/libTutorial4.rootmap -rml Tutorial4.so -c   -I/home/marci/fair_install/FairRoot/logger -I/home/marci/fair_install/FairRoot/fairtools -I/home/marci/fair_install/FairRoot/geobase -I/home/marci/fair_install/FairRoot/parbase -I/home/marci/fair_install/FairRoot/base -I/home/marci/fair_install/FairRoot/base/steer -I/home/marci/fair_install/FairRoot/base/event -I/home/marci/fair_install/FairRoot/base/field -I/home/marci/fair_install/FairRoot/base/sim -I/home/marci/fair_install/FairRoot/base/source -I/home/marci/fair_install/FairRoot/dbase -I/home/marci/fair_install/FairRoot/dbase/dbInterface -I/home/marci/fair_install/FairRoot/dbase/dbValidation -I/home/marci/fair_install/FairRoot/dbase/dbUtils -I/home/marci/fair_install/FairRoot/input/db -I/home/marci/fair_install/FairRoot/dbase/dbInput -I/home/marci/fair_install/FairRoot/dbase/dbIO -I/home/marci/fair_install/FairRoot/eventdisplay -I/home/marci/fair_install/FairRoot/examples/simulation/Tutorial4/src -I/home/marci/fair_install/FairRoot/examples/simulation/Tutorial4/src/mc -I/home/marci/fair_install/FairRoot/examples/simulation/Tutorial4/src/param -I/home/marci/fair_install/FairRoot/examples/simulation/Tutorial4/src/data -I/home/marci/fair_install/FairRoot/examples/simulation/Tutorial4/src/reco -I/home/marci/fair_install/FairRoot/examples/simulation/Tutorial4/src/tools -I/home/marci/fair_install/FairRoot/examples/common/mcstack -I/home/marci/fair_install/FairSoftInst/include/root -I/home/marci/fair_install/FairSoftInst/include mc/FairTutorialDet4.h mc/FairTutorialDet4Geo.h param/FairTutorialDet4ContFact.h param/FairTutorialDet4GeoPar.h param/FairTutorialDet4MisalignPar.h data/FairTutorialDet4Point.h data/FairTutorialDet4Hit.h reco/FairTutorialDet4HitProducerIdealMisalign.h reco/FairTutorialDet4StraightLineFitter.h reco/FairTutorialDet4MilleWriter.h tools/FairTutorialDet4GeoHandler.h display/FairTutorialDet4PointDraw.h Tutorial4LinkDef.h
