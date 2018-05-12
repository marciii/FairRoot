#!/bin/bash

export Linux_Flavour_="Ubuntu 17.10"
export System_="x86_64"
. /home/marci/fair_install/FairRoot/build2/check_system.sh
if [ $same_system -eq 1 ]; then
	export SIMPATH="/home/marci/fair_install/FairSoftInst"
	export ROOTSYS="/home/marci/fair_install/FairSoftInst"
	export FAIRROOTPATH=""
	if (true); then
		export GEANT4_LIBRARY_DIR="/home/marci/fair_install/FairSoftInst/lib"
		export GEANT4_INCLUDE_DIR="/home/marci/fair_install/FairSoftInst/include/Geant4:/home/marci/fair_install/FairSoftInst/transport/geant4/source/interfaces/common/include:/home/marci/fair_install/FairSoftInst/transport/geant4/physics_lists/hadronic/Packaging/include:/home/marci/fair_install/FairSoftInst/transport/geant4/physics_lists/hadronic/QGSP/include"
		export GEANT4VMC_INCLUDE_DIR="/home/marci/fair_install/FairSoftInst/include/geant4vmc"
		export GEANT4VMC_LIBRARY_DIR="/home/marci/fair_install/FairSoftInst/lib"
		export GEANT4VMC_MACRO_DIR="/home/marci/fair_install/FairSoftInst/share/geant4_vmc/macro"
		export CLHEP_INCLUDE_DIR="/home/marci/fair_install/FairSoftInst/include/Geant4"
		export CLHEP_LIBRARY_DIR="/home/marci/fair_install/FairSoftInst/lib"
		export CLHEP_BASE_DIR=""
		export PLUTO_LIBRARY_DIR=""
		export PLUTO_INCLUDE_DIR=""
		export PYTHIA6_LIBRARY_DIR="/home/marci/fair_install/FairSoftInst/lib"
		export G3SYS="/home/marci/fair_install/FairSoftInst/share/geant3"
		export GEANT3_INCLUDE_DIR="/home/marci/fair_install/FairSoftInst/include/TGeant3"
		export GEANT3_LIBRARY_DIR="/home/marci/fair_install/FairSoftInst/lib"
		export GEANT3_LIBRARIES="/home/marci/fair_install/FairSoftInst/lib/libgeant321.so"
		export USE_VGM="1"
		export PYTHIA8DATA="/home/marci/fair_install/FairSoftInst/share/pythia8/xmldoc"
		export CLASSPATH=""

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
	fi
	export ROOT_LIBRARY_DIR="/home/marci/fair_install/FairSoftInst/lib/root"
	export ROOT_LIBRARIES="-L/home/marci/fair_install/FairSoftInst/lib/root -lGui -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -pthread -lm -ldl -rdynamic"
	export ROOT_INCLUDE_DIR="/home/marci/fair_install/FairSoftInst/include/root"
	export ROOT_INCLUDE_PATH="/home/marci/fair_install/FairRoot/logger:/home/marci/fair_install/FairRoot/fairtools:/home/marci/fair_install/FairRoot/geobase:/home/marci/fair_install/FairRoot/parbase:/home/marci/fair_install/FairRoot/base:/home/marci/fair_install/FairRoot/base/steer:/home/marci/fair_install/FairRoot/base/event:/home/marci/fair_install/FairRoot/base/field:/home/marci/fair_install/FairRoot/base/sim:/home/marci/fair_install/FairRoot/base/source:/home/marci/fair_install/FairRoot/dbase:/home/marci/fair_install/FairRoot/dbase/dbInterface:/home/marci/fair_install/FairRoot/dbase/dbValidation:/home/marci/fair_install/FairRoot/dbase/dbUtils:/home/marci/fair_install/FairRoot/input/db:/home/marci/fair_install/FairRoot/dbase/dbInput:/home/marci/fair_install/FairRoot/dbase/dbIO"
	export VMCWORKDIR="/home/marci/fair_install/FairRoot/examples"
	export FAIRLIBDIR="/home/marci/fair_install/FairRoot/build2/lib"
	export PYTHONPATH="/home/marci/fair_install/FairRoot/python:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib/root:/home/marci/fair_install/FairSoftInst/lib/Geant4:/home/marci/fair_install/FairSoftInst/lib/g4py"
	case $1 in
		-a | --append )
			export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:""
			export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:"/home/marci/fair_install/FairRoot/build2/lib:/home/marci/fair_install/FairSoftInst/lib/root:/home/marci/fair_install/FairSoftInst/lib"
			export PATH=$PATH:"/home/marci/fair_install/FairSoftInst/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"
			;;
		-p | --prepend )
			export DYLD_LIBRARY_PATH="":$DYLD_LIBRARY_PATH
			export LD_LIBRARY_PATH="/home/marci/fair_install/FairRoot/build2/lib:/home/marci/fair_install/FairSoftInst/lib/root:/home/marci/fair_install/FairSoftInst/lib":$LD_LIBRARY_PATH
			export PATH="/home/marci/fair_install/FairSoftInst/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin":$PATH
			;;
		* )
			export DYLD_LIBRARY_PATH=""
			export LD_LIBRARY_PATH="/home/marci/fair_install/FairRoot/build2/lib:/home/marci/fair_install/FairSoftInst/lib/root:/home/marci/fair_install/FairSoftInst/lib"
			export PATH="/home/marci/fair_install/FairSoftInst/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"
			;;
	esac
fi
