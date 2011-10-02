// -------------------------------------------------------------------------
// -----                     FairModule source file                    -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------
/* Generated by Together */

#include "FairModule.h"


#include "FairVolume.h"
#include "FairVolumeList.h"
#include "FairBaseParSet.h"
#include "FairRun.h"

#include "FairGeoNode.h"
#include "FairRuntimeDb.h"

#include "FairGeoInterface.h"
#include "FairGeoLoader.h"
#include "FairGeoNode.h"
#include "FairGeoRootBuilder.h"
#include "FairGeoMedia.h"


#include "TString.h"
#include "TObjArray.h"
#include "TGeoVolume.h"
#include "TFile.h"
#include "TList.h"
#include "TKey.h"
#include "TGeoManager.h"
#include "TGeoVoxelFinder.h"
#include "TGeoMatrix.h"
#include "TGDMLParse.h"

#include "TSystem.h"
#include <fstream>
#include <iostream>


using std::cout;
using std::endl;

TArrayI* FairModule::volNumber=0;
Int_t FairModule::fNbOfVolumes=0;
FairVolumeList*  FairModule::vList=0;
TRefArray*    FairModule::svList=0;

std::map<TString, Int_t> FairModule::fixedMats;
Bool_t FairModule::isFirstGDML = kTRUE;


//__________________________________________________________________________
void FairModule::ConstructGeometry()
{
}
//__________________________________________________________________________
void FairModule::ConstructOpGeometry()
{
}
//__________________________________________________________________________
FairModule::~FairModule()
{

}
//__________________________________________________________________________
FairModule::FairModule(const char* Name, const char* title ,Bool_t Active)
  :TNamed(Name, title),
   fgeoVer("Not defined"),
   fgeoName("Not defined"),
   fModId(-1),
   fActive(Active),
   fNbOfSensitiveVol(0),
   fVerboseLevel(0),
   flGeoPar(0),
   kGeoSaved(kFALSE),
   fMotherVolumeName(""),
   fLogger(FairLogger::GetLogger())
{
  if(!svList) { svList=new TRefArray(); }
  if(!vList) { vList=new FairVolumeList(); }

}

//__________________________________________________________________________

FairModule::FairModule()
  : TNamed(),
    fgeoVer("Not defined"),
    fgeoName("Not defined"),
    fModId(-1),
    fActive(kFALSE),
    fNbOfSensitiveVol(0),
    fVerboseLevel(0),
    flGeoPar(0),
    kGeoSaved(kFALSE),
    fMotherVolumeName(""),
    fLogger(FairLogger::GetLogger())
{

}

//__________________________________________________________________________
void FairModule::Streamer(TBuffer& b)
{
  //TNamed::Streamer(b);
  const char* Name= GetName();
  const char* Title= GetTitle();

  if (b.IsReading()) {
    fgeoVer.Streamer(b);
    fgeoName.Streamer(b);
    b >> Name;
    b >> Title;
    b >> fActive;
    b >> fModId;
  } else {
    fgeoVer.Streamer(b);
    fgeoName.Streamer(b);
    b << Name;
    b << Title;
    b << fActive;
    b << fModId;
  }

}
//__________________________________________________________________________
void FairModule::SetGeometryFileName(TString fname, TString geoVer)
{
  fgeoVer=geoVer;
  TString FileName = fname;
  TString work = getenv("VMCWORKDIR");
  TString userwork = getenv("GEOMPATH");
  if(userwork != "") {
    fgeoName=userwork;
    if (!fgeoName.EndsWith("/")) { fgeoName+="/"; }
    //fgeoName+=fname;
    if (TString(gSystem->FindFile(fgeoName.Data(),fname)) != TString("")) {
      fgeoName=fname;
      fLogger->Info(MESSAGE_ORIGIN, "User path for detector geometry : %s ", fgeoName.Data());
    } else {
      fLogger->Warning(MESSAGE_ORIGIN, "Detector geometry was not found in user path : %s ", FileName.Data());
      fgeoName=work+"/geometry/";
      fLogger->Info(MESSAGE_ORIGIN, "Try the standard path : %s ",fgeoName.Data());
      if (TString(gSystem->FindFile(fgeoName.Data(),FileName)) != TString("")) {
        fgeoName=FileName;
        fLogger->Info(MESSAGE_ORIGIN, "Reading detector geometry from : %s ", FileName.Data());
      } else {
        fLogger->Fatal(MESSAGE_ORIGIN,"Detector geometry not found.");
      }
    }
  } else {
    fgeoName=work+"/geometry/";
    fgeoName+=fname;
  }
}
//__________________________________________________________________________
void FairModule::ProcessNodes(TList* aList)
{

  TListIter iter(aList);
  FairGeoNode* node   = NULL;
  FairGeoNode* MotherNode =NULL;
  FairVolume*  volume = NULL;
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  FairBaseParSet* par=(FairBaseParSet*)(rtdb->getContainer("FairBaseParSet"));
  TObjArray* fNodes = par->GetGeoNodes();
  while( (node = (FairGeoNode*)iter.Next()) ) {

    node->calcLabTransform();
//      cout << "-I ProcessNodes() Node: " << node->GetName() << " copyNo: " << node->getCopyNo()
//       << " LabTransform: " << node->getLabTransform() <<  endl;
//      node->Dump();
//   GetListOfGeoPar()->Add( node );
    MotherNode=node->getMotherNode();
    volume = new FairVolume( node->getTruncName(), fNbOfVolumes++);
    volume->setRealName(node->GetName());
    vList->addVolume(volume);
    volume->setGeoNode(node);
    volume->setCopyNo(  node->getCopyNo());

    if(MotherNode!=0) {
      volume->setMotherId(node->getMCid());
      volume->setMotherCopyNo(MotherNode->getCopyNo());
    }
    FairGeoVolume* aVol=NULL;

    if ( node->isSensitive() && fActive ) {
      volume->setModId(fModId);
      volume->SetModule(this);
      svList->Add(volume);
      aVol = dynamic_cast<FairGeoVolume*> ( node );
      fNodes->AddLast( aVol );
      fNbOfSensitiveVol++;
    }

  }
  /*  cout << " FairModule::ProcessNodes "<< endl;
     svList->ls();
    cout << " FairModule::ProcessNodes "<< endl;
  */
}
//__________________________________________________________________________
void  FairModule::AddSensitiveVolume(TGeoVolume* v)
{

//  cout <<"FairModule::AddSensitiveVolume  " << v->GetName() << endl;
  FairVolume*  volume = NULL;
  volume = new FairVolume(v->GetName(), fNbOfVolumes++);
  vList->addVolume(volume);
  volume->setModId(fModId);
  volume->SetModule(this);
  svList->Add(volume);
  fNbOfSensitiveVol++;

}


//__________________________________________________________________________
FairVolume* FairModule::getFairVolume(FairGeoNode* fN)
{
  FairVolume* fv;
  FairVolume*  fvol=0;
//  cout << " FairModule::getFairVolume " << fN <<  endl;
  for(Int_t i=0; i<vList->getEntries(); i++) {
    fv=vList->At(i);
//    cout << "" << fv->getGeoNode() << " " << fN <<endl;
    if((fv->getGeoNode())==fN) {
//      cout << "Inside " << fv->getGeoNode() << "  " << fN <<endl;
      fvol=fv;
      return fvol;
      break;
    }
  }
  return fvol;
}
//__________________________________________________________________________
void FairModule::ConstructRootGeometry()
{

  TGeoManager* OldGeo=gGeoManager;
  TGeoManager* NewGeo=0;
  TGeoVolume* volume=0;;
  TFile* f=new TFile(GetGeometryFileName().Data());
  TList* l= f->GetListOfKeys();
  TKey* key;
  TIter next( l);
  TGeoNode* n=0;
  TGeoVolume* v1=0;
  while ((key = (TKey*)next())) {
    if (strcmp(key->GetClassName(),"TGeoManager") != 0) { continue; }
    gGeoManager=0;
    NewGeo = (TGeoManager*)key->ReadObj();
    break;
  }
  if (NewGeo!=0) {
    NewGeo->cd();
    volume=(TGeoVolume*)NewGeo->GetNode(0)->GetDaughter(0)->GetVolume();
    v1=volume->MakeCopyVolume(volume->GetShape());
    //n=NewGeo->GetTopNode();
    n=v1->GetNode(0);
    //  NewGeo=0;

    delete NewGeo;

  } else {
    key=(TKey*) l->At(0);
    volume=(TGeoVolume*)key->ReadObj();
    n=volume->GetNode(0);
    v1=n->GetVolume();
  }

  if(v1==0) {
    fLogger->Info(MESSAGE_ORIGIN, "\033[5m\033[31mFairModule::ConstructRootGeometry(): could not find any geometry in File!!  \033[0m", GetGeometryFileName().Data());
    exit(0);
  }
  gGeoManager=OldGeo;
  gGeoManager->cd();
  // If AddToVolume is empty add the volume to the top volume Cave
  // If it is defined check i´f the volume exists and if it exists add the volume from the root file
  // to the already existing volume
  TGeoVolume* Cave=NULL;
  if ( 0 == fMotherVolumeName.Length() ) {
    Cave= gGeoManager->GetTopVolume();
  } else {
    Cave = gGeoManager->GetVolume(fMotherVolumeName);
    if ( NULL == Cave ) {
      fLogger->Error(MESSAGE_ORIGIN,"\033[5m\033[31mFairModule::ConstructRootGeometry(): could not find the given mother volume \033[0m   %s \033[5m\033[31m where the geomanger should be added. \033[0m", fMotherVolumeName.Data());
      exit(0);
    }
  }

  gGeoManager->AddVolume(v1);
  TGeoVoxelFinder* voxels = v1->GetVoxels();
  if (voxels) { voxels->SetNeedRebuild(); }
  TGeoMatrix* M = n->GetMatrix();
  // M->SetDefaultName();
  SetDefaultMatrixName(M);
  gGeoManager->GetListOfMatrices()->Remove(M);
  TGeoHMatrix* global = gGeoManager->GetHMatrix();
  gGeoManager->GetListOfMatrices()->Remove(global); //Remove the Identity matrix
  Cave->AddNode(v1,0, M);
  ExpandNode(n);
//  delete NewGeo;
  delete f;
}
//__________________________________________________________________________
void FairModule::ConstructASCIIGeometry()
{
  cout << " FairModule::ConstructASCIIGeometry() : this method has to be implimented in detector class " << endl;
}
//__________________________________________________________________________
Bool_t FairModule::CheckIfSensitive(std::string name)
{

  cout << "\033[5m\033[31m FairModule::CheckIfSensitive(std::string name): this method has to be implimented in detector class  \033[0m\n" << endl;
  return kFALSE;
}
//__________________________________________________________________________
void FairModule::ExpandNode(TGeoNode* fN)
{

  FairGeoLoader* geoLoad = FairGeoLoader::Instance();
  FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  FairGeoMedia* Media =  geoFace->getMedia();
  FairGeoBuilder* geobuild=geoLoad->getGeoBuilder();
  TGeoMatrix* Matrix =fN->GetMatrix();
  if(gGeoManager->GetListOfMatrices()->FindObject(Matrix)) { gGeoManager->GetListOfMatrices()->Remove(Matrix); }
  TGeoVolume* v1=fN->GetVolume();
  TObjArray* NodeList=v1->GetNodes();
  for (Int_t Nod=0; Nod<NodeList->GetEntriesFast(); Nod++) {
    TGeoNode* fNode =(TGeoNode*)NodeList->At(Nod);
    TGeoMatrix* M =fNode->GetMatrix();
    //M->SetDefaultName();
    SetDefaultMatrixName(M);
    if(fNode->GetNdaughters()>0) { ExpandNode(fNode); }
    TGeoVolume* v= fNode->GetVolume();
//      Int_t MatId=0;
    TGeoMedium* med1=v->GetMedium();
    if(med1) {
      TGeoMaterial* mat1=v->GetMaterial();
      TGeoMaterial* newMat = gGeoManager->GetMaterial(mat1->GetName());
      if( newMat==0) {
        //std::cout<< "Material " << mat1->GetName() << " is not defined " << std::endl;
        FairGeoMedium* FairMedium=Media->getMedium(mat1->GetName());
        if (!FairMedium) {
          std::cout << "\033[5m\033[31m Material is not defined in ASCII file nor in Root file  \033[0m\n" << std::endl;
          FairMedium=new FairGeoMedium(mat1->GetName());
          Media->addMedium(FairMedium);
        }
        //std::cout << "Create Medium " << mat1->GetName() << std::endl;
        Int_t nmed=geobuild->createMedium(FairMedium);
        v->SetMedium(gGeoManager->GetMedium(nmed));
        gGeoManager->SetAllIndex();
      } else {
        TGeoMedium* med2= gGeoManager->GetMedium(mat1->GetName());
        v->SetMedium(med2);
      }
    } else {
      if (strcmp(v->ClassName(),"TGeoVolumeAssembly") != 0) {
        ;
        //[R.K.-3.3.08]  // When there is NO material defined, set it to avoid conflicts in Geant
        std::cout<<" -E- Error in FairModule::ExpandNode()!  "
                 <<"\tThe volume "<<v->GetName()<<" Has no medium information."<<std::endl;
        abort();
      }
    }
    if (!gGeoManager->FindVolumeFast(v->GetName())) {
      if (fVerboseLevel>2) { std::cout << "Register Volume : " << v->GetName() << " id "  << std::endl; }
      v->RegisterYourself();
    }
    if (CheckIfSensitive(v->GetName())) {
      if (fVerboseLevel>2) {
        std::cout << "Sensitive Volume : " << v->GetName() << " id "  << std::endl;
      }
      AddSensitiveVolume(v);
    }
  }
}
//__________________________________________________________________________
void FairModule::SetDefaultMatrixName(TGeoMatrix* matrix)
{
  // Copied from root TGeoMatrix::SetDefaultName() and modified (memory leak)
  // If no name was supplied in the ctor, the type of transformation is checked.
  // A letter will be prepended to the name :
  //   t - translation
  //   r - rotation
  //   s - scale
  //   c - combi (translation + rotation)
  //   g - general (tr+rot+scale)
  // The index of the transformation in gGeoManager list of transformations will
  // be appended.
  if (!gGeoManager) { return; }
  if (strlen(matrix->GetName())) { return; }
  char type = 'n';
  if (matrix->IsTranslation()) { type = 't'; }
  if (matrix->IsRotation()) { type = 'r'; }
  if (matrix->IsScale()) { type = 's'; }
  if (matrix->IsCombi()) { type = 'c'; }
  if (matrix->IsGeneral()) { type = 'g'; }
  TObjArray* matrices = gGeoManager->GetListOfMatrices();
  Int_t index = 0;
  if (matrices) { index =matrices->GetEntriesFast() - 1; }
  matrix->SetName(Form("%c%i", type, index));
}


//----------------------------------------------------------------------------------------------------------
void FairModule::ConstructGDMLGeometry(TGeoCombiTrans* posrot)
{
  TGDMLParse parser;
  TGeoVolume* gdmlTop;
  gdmlTop = parser.GDMLReadFile(GetGeometryFileName());
  gGeoManager->GetTopVolume()->AddNode(gdmlTop,1,posrot);
  ExpandNodeForGDML(gGeoManager->GetTopVolume()->GetNode(gGeoManager->GetTopVolume()->GetNdaughters()-1));
  isFirstGDML = 0;

  //! CONTROL_DUMP_OF_MEDIA_STATE_IN_THE_MEMORY_AFTER_EACH_GDML_FILE
  /*
   for (Int_t sdf=0; sdf<gGeoManager->GetTopNode()->GetNdaughters(); sdf++)
   {
   cout << "[CONTROL_DUMP] " << gGeoManager->GetTopNode()->GetDaughter(sdf)->GetVolume()->GetName() << ":\t\t";
   cout << gGeoManager->GetTopNode()->GetDaughter(sdf)->GetVolume()->GetMedium()->GetMaterial()->GetZ() << endl;
   for (Int_t dfg=0; dfg<gGeoManager->GetTopNode()->GetDaughter(sdf)->GetNdaughters(); dfg++)
   {
   cout << "[CONTROL_DUMP] \t\t" <<gGeoManager->GetTopNode()->GetDaughter(sdf)->GetDaughter(dfg)->GetVolume()->GetName() << ":\t\t";
   cout << gGeoManager->GetTopNode()->GetDaughter(sdf)->GetDaughter(dfg)->GetVolume()->GetMedium()->GetMaterial()->GetZ() << endl;
   }
   }
   */
  //! endof CONTROL_DUMP_OF_MEDIA_STATE_IN_THE_MEMORY_AFTER_EACH_GDML_FILE
}

void FairModule::ExpandNodeForGDML(TGeoNode* curNode)
{
  //  cout << "[ExpandNodeForGDML] Expanding node " << curNode->GetName() << endl;
  TGeoVolume* curVol = curNode->GetVolume();
  TString curMedName = curNode->GetMedium()->GetName();
  TGeoMedium* curMedInGeoManager = gGeoManager->GetMedium(curMedName);
  Int_t matIndToDel = gGeoManager->GetMaterialIndex(curMedName);

  if (curMedName.BeginsWith("G4_")) {
    //    cout << "[ExpandNodeForGDML] Material in GDML begins with G4_" << endl;
    curMedName.Remove(0, 3);
  } else {
    //    cout << "[ExpandNodeForGDML] Material in GDML does not start with G4_" << "\t\t" << curNode->GetName() << "\t\t" << curMedName << endl;
    //    return;
  }

  Int_t nmed;

  FairGeoLoader* geoLoad = FairGeoLoader::Instance();
  FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  FairGeoMedia* geoMediaBase =  geoFace->getMedia();
  FairGeoBuilder* geobuild = geoLoad->getGeoBuilder();
  FairGeoMedium* curMedInGeo;

  if (curMedInGeoManager == 0) {
    cout << "[ExpandNodeForGDML] New medium found in gmdl - it is not in gGeoManager list." << endl;
    //! New medium found in gmdl - it is not in gGeoManager list.
    //! This should not happen as GDML parser adds medium into the list
  } else {
    //! Medium is in the list in gGeoManager.
    //! Trying to replace it with the one from the Geo file.
    //    cout << "Medium is in the list in gGeoManager." << endl;

    curMedInGeo = geoMediaBase->getMedium(curMedName);
    if (curMedInGeo == 0) {
      cout << "[ExpandNodeForGDML] Media not found in Geo file." << endl;
    } else {
      if (fixedMats.find(curMedName) == fixedMats.end()) {
        nmed = geobuild->createMedium(curMedInGeo);
        fixedMats[curMedName] = gGeoManager->GetListOfMedia()->GetEntries();
        //        cout << "[ExpandNodeForGDML] " << curMedName << " added to list\t" << fixedMats[curMedName] << "\t" << nmed << endl;
      } else {
        //        cout << "[ExpandNodeForGDML] " << curMedName << " is already in the list.\t\t" << fixedMats[curMedName] << endl;
      }

      curNode->GetVolume()->SetMedium(gGeoManager->GetMedium(curMedName));
      gGeoManager->SetAllIndex();
    }
  }

  //! Making volume sensitive according to the media 0-th flag
  if ((Int_t)(curVol->GetMedium()->GetParam(0)) == 1) {
    //! The volume is sensitive => add it to the list
    //    cout << "\t\t\tAdding sensitive volume: " << curVol->GetName() << endl;
    AddSensitiveVolume(curVol);
  }
  //! endof Making volume sensitive according to the media 0-th flag

  //! Recursevly go down the tree of nodes
  if (curVol->GetNdaughters() != 0) {
    TObjArray* NodeChildList = curVol->GetNodes();
    TGeoNode* curNodeChild;
    for (Int_t j=0; j<NodeChildList->GetEntriesFast(); j++) {
      curNodeChild = (TGeoNode*)NodeChildList->At(j);
      ExpandNodeForGDML(curNodeChild);
    }
  }
}
//----------------------------------------------------------------------------------------------------------

//__________________________________________________________________________
ClassImp(FairModule)



