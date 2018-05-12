#!/bin/csh

setenv Linux_Flavour_ "Ubuntu 17.10"
setenv System_ "x86_64"
. /home/marci/fair_install/FairRoot/build2/check_system.csh
if ( "$same_system" == "1" ) then 
	setenv SIMPATH "/home/marci/fair_install/FairSoftInst"
	setenv ROOTSYS "/home/marci/fair_install/FairSoftInst"
	setenv FAIRROOTPATH ""
	if ( true == true ) then
		setenv GEANT4_LIBRARY_DIR "/home/marci/fair_install/FairSoftInst/lib"
		setenv GEANT4_INCLUDE_DIR "/home/marci/fair_install/FairSoftInst/include/Geant4:/home/marci/fair_install/FairSoftInst/transport/geant4/source/interfaces/common/include:/home/marci/fair_install/FairSoftInst/transport/geant4/physics_lists/hadronic/Packaging/include:/home/marci/fair_install/FairSoftInst/transport/geant4/physics_lists/hadronic/QGSP/include"
		setenv GEANT4VMC_INCLUDE_DIR "/home/marci/fair_install/FairSoftInst/include/geant4vmc"
		setenv GEANT4VMC_LIBRARY_DIR "/home/marci/fair_install/FairSoftInst/lib"
		setenv GEANT4VMC_MACRO_DIR "/home/marci/fair_install/FairSoftInst/share/geant4_vmc/macro"
		setenv CLHEP_INCLUDE_DIR "/home/marci/fair_install/FairSoftInst/include/Geant4"
		setenv CLHEP_LIBRARY_DIR "/home/marci/fair_install/FairSoftInst/lib"
		setenv CLHEP_BASE_DIR ""
		setenv PLUTO_LIBRARY_DIR ""
		setenv PLUTO_INCLUDE_DIR ""
		setenv PYTHIA6_LIBRARY_DIR "/home/marci/fair_install/FairSoftInst/lib"
		setenv G3SYS "/home/marci/fair_install/FairSoftInst/share/geant3"
		setenv GEANT3_INCLUDE_DIR "/home/marci/fair_install/FairSoftInst/include/TGeant3"
		setenv GEANT3_LIBRARY_DIR "/home/marci/fair_install/FairSoftInst/lib"
		setenv GEANT3_LIBRARIES "/home/marci/fair_install/FairSoftInst/lib/libgeant321.so"
		setenv USE_VGM "1"
		setenv PYTHIA8DATA "/home/marci/fair_install/FairSoftInst/share/pythia8/xmldoc"
		setenv CLASSPATH ""

		setenv G4LEDATA "/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4EMLOW"
		setenv G4LEVELGAMMADATA "/home/marci/fair_install/FairSoftInst/share/Geant4/data/PhotonEvaporation"
		setenv G4NeutronHPCrossSections "/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4NDL"
		setenv G4NEUTRONHPDATA "/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4NDL"
		setenv G4NEUTRONXSDATA "/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4NEUTRONXS"
		setenv G4PIIDATA "/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4PII"
		setenv G4RADIOACTIVEDATA "/home/marci/fair_install/FairSoftInst/share/Geant4/data/RadioactiveDecay"
		setenv G4REALSURFACEDATA "/home/marci/fair_install/FairSoftInst/share/Geant4/data/RealSurface"
		setenv G4SAIDXSDATA "/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4SAIDDATA"
		setenv G4ENSDFSTATEDATA "/home/marci/fair_install/FairSoftInst/share/Geant4/data/G4ENSDFSTATE"
	endif
	setenv ROOT_LIBRARY_DIR "/home/marci/fair_install/FairSoftInst/lib/root"
	setenv ROOT_LIBRARIES "-L/home/marci/fair_install/FairSoftInst/lib/root -lGui -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -pthread -lm -ldl -rdynamic"
	setenv ROOT_INCLUDE_DIR "/home/marci/fair_install/FairSoftInst/include/root"
	setenv ROOT_INCLUDE_PATH "/home/marci/fair_install/FairRoot/logger:/home/marci/fair_install/FairRoot/fairtools:/home/marci/fair_install/FairRoot/geobase:/home/marci/fair_install/FairRoot/parbase:/home/marci/fair_install/FairRoot/base:/home/marci/fair_install/FairRoot/base/steer:/home/marci/fair_install/FairRoot/base/event:/home/marci/fair_install/FairRoot/base/field:/home/marci/fair_install/FairRoot/base/sim:/home/marci/fair_install/FairRoot/base/source:/home/marci/fair_install/FairRoot/dbase:/home/marci/fair_install/FairRoot/dbase/dbInterface:/home/marci/fair_install/FairRoot/dbase/dbValidation:/home/marci/fair_install/FairRoot/dbase/dbUtils:/home/marci/fair_install/FairRoot/input/db:/home/marci/fair_install/FairRoot/dbase/dbInput:/home/marci/fair_install/FairRoot/dbase/dbIO"
	setenv VMCWORKDIR "/home/marci/fair_install/FairRoot/examples"
	setenv FAIRLIBDIR "/home/marci/fair_install/FairRoot/build2/lib"
	setenv PYTHONPATH "/home/marci/fair_install/FairRoot/python:/home/marci/fair_install/FairSoftInst/lib:/home/marci/fair_install/FairSoftInst/lib/root:/home/marci/fair_install/FairSoftInst/lib/Geant4:/home/marci/fair_install/FairSoftInst/lib/g4py"
	switch( $1 )
		case '-a' :
			setenv DYLD_LIBRARY_PATH $DYLD_LIBRARY_PATH:""
			setenv LD_LIBRARY_PATH $LD_LIBRARY_PATH:"/home/marci/fair_install/FairRoot/build2/lib:/home/marci/fair_install/FairSoftInst/lib/root:/home/marci/fair_install/FairSoftInst/lib"
			setenv PATH $PATH:"/home/marci/fair_install/FairSoftInst/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"
			breaksw
		case '-p' :
			setenv DYLD_LIBRARY_PATH="":$DYLD_LIBRARY_PATH
			setenv LD_LIBRARY_PATH="/home/marci/fair_install/FairRoot/build2/lib:/home/marci/fair_install/FairSoftInst/lib/root:/home/marci/fair_install/FairSoftInst/lib":$LD_LIBRARY_PATH
			setenv PATH="/home/marci/fair_install/FairSoftInst/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin":$PATH
			echo "hello"
			breaksw
		case * :
			setenv DYLD_LIBRARY_PATH=""
			setenv LD_LIBRARY_PATH="/home/marci/fair_install/FairRoot/build2/lib:/home/marci/fair_install/FairSoftInst/lib/root:/home/marci/fair_install/FairSoftInst/lib"
			setenv PATH="/home/marci/fair_install/FairSoftInst/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"
			breaksw
	endsw
endif
