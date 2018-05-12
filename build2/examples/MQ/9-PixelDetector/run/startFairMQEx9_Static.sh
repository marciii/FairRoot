#!/bin/bash

# Setup the needed environment
export LD_LIBRARY_PATH=/home/marci/fair_install/FairRoot/build2/lib:/home/marci/fair_install/FairSoftInst/lib/root:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib
export DYLD_LIBRARY_PATH=/home/marci/fair_install/FairRoot/build2/lib:/home/marci/fair_install/FairSoftInst/lib/root:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib
export PATH=/home/marci/fair_install/FairSoftInst/bin:$PATH:
export ROOTSYS=/home/marci/fair_install/FairSoftInst
export ROOTEXE=/home/marci/fair_install/FairSoftInst/bin/root.exe
export ROOT_INCLUDE_PATH=
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

cd /home/marci/fair_install/FairRoot/build2/examples/MQ/9-PixelDetector/run

source  /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/startFairMQEx9_Static.sh
