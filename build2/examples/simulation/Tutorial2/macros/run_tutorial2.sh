#!/bin/bash

# This macro is needed to start the Root macros used for automatic testing
# from inside CMake using the add_test functionality. Since the tests 
# starts with a fresh environment on has to set first the correct environment
# needed to run FairRoot.
# Also parameters defined in add_test will be converted in the correct format
# to be passed to root.

# Setup the needed environment
export LD_LIBRARY_PATH=/home/marci/fair_install/FairRoot/build2/lib:/home/marci/fair_install/FairSoftInst/lib/root:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib
export DYLD_LIBRARY_PATH=/home/marci/fair_install/FairRoot/build2/lib:/home/marci/fair_install/FairSoftInst/lib/root:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib
export PATH=/home/marci/fair_install/FairSoftInst/bin:$PATH:
export ROOTSYS=/home/marci/fair_install/FairSoftInst
export ROOTEXE=/home/marci/fair_install/FairSoftInst/bin/root.exe
export ROOT_INCLUDE_PATH=/home/marci/fair_install/FairRoot/logger:/home/marci/fair_install/FairRoot/fairtools:/home/marci/fair_install/FairRoot/geobase:/home/marci/fair_install/FairRoot/parbase:/home/marci/fair_install/FairRoot/base:/home/marci/fair_install/FairRoot/base/steer:/home/marci/fair_install/FairRoot/base/event:/home/marci/fair_install/FairRoot/base/field:/home/marci/fair_install/FairRoot/base/sim:/home/marci/fair_install/FairRoot/base/source:/home/marci/fair_install/FairRoot/dbase:/home/marci/fair_install/FairRoot/dbase/dbInterface:/home/marci/fair_install/FairRoot/dbase/dbValidation:/home/marci/fair_install/FairRoot/dbase/dbUtils:/home/marci/fair_install/FairRoot/input/db:/home/marci/fair_install/FairRoot/dbase/dbInput:/home/marci/fair_install/FairRoot/dbase/dbIO
export VMCWORKDIR=/home/marci/fair_install/FairRoot/examples
export GEANT4VMC_MACRO_DIR=/home/marci/fair_install/FairSoftInst/share/geant4_vmc/macro
export USE_VGM=1
export BOOST=1
export G4LEDATA="/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4EMLOW"
export G4LEVELGAMMADATA="/home/marci/fair_install/FairSoftInst/share/Geant4/data/PhotonEvaporation"
export G4NeutronHPCrossSections="/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4NDL"
export G4NEUTRONHPDATA="/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4NDL"
export G4NEUTRONXSDATA="/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4NEUTRONXS"
export G4PIIDATA="/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4PII"
export G4RADIOACTIVEDATA="/home/marci/fair_install/FairSoftInst/share/Geant4/data/RadioactiveDecay"
export G4REALSURFACEDATA="/home/marci/fair_install/FairSoftInst/share/Geant4/data/RealSurface"
export G4SAIDXSDATA="/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4SAIDDATA"
export G4ENSDFSTATEDATA="/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4ENSDFSTATE"
export G3SYS="/home/marci/fair_install/FairSoftInst/share/geant3"
export PYTHIA8DATA="/home/marci/fair_install/FairSoftInst/share/pythia8/xmldoc"
if [ -e /env.sh ]; then
  . /env.sh
fi

# Concatenate all parameters given on the command line to one 
# comma separated string 
parameters=""
for i in $*; do 
  if [ -z $parameters ]; then
    parameters=$i
  else
    parameters=$(echo "$parameters,$i")
  fi 
done

cd /home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial2/macros

# execute root with the defined macro and the command line parameters
$ROOTEXE -q -b /home/marci/fair_install/FairRoot/examples/simulation/Tutorial2/macros/run_tutorial2.C\($parameters\)
