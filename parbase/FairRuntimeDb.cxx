//*-- AUTHOR : Ilse Koenig
//*-- Created : 20/10/2004

/////////////////////////////////////////////////////////////
//  FairRuntimeDb
//
//  Administration class for parameter input/output
/////////////////////////////////////////////////////////////

#include "FairRuntimeDb.h"

#include "FairContFact.h"
#include "FairParSet.h"
#include "FairRtdbRun.h"
#include "FairParIo.h"
#include "FairParRootFileIo.h"
#include "FairParAsciiFileIo.h"
#include "FairGenericParRootFileIo.h"
#include "FairGenericParAsciiFileIo.h"

//#include "TKey.h"
#include "TClass.h"


#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::ios;
using std::setw;

ClassImp(FairRuntimeDb)

FairRuntimeDb* FairRuntimeDb::gRtdb=0;

FairRuntimeDb* FairRuntimeDb::instance(void)
{
  // Singleton instance
  if (gRtdb==0) { gRtdb=new FairRuntimeDb; }
  return gRtdb;
}

FairRuntimeDb::FairRuntimeDb(void)
{
  // constructor creates an empty list for parameter containers
  // and an empty list of runs for the version management
  gRtdb=this;
  containerList=new TList();
  runs=new TList();
  firstInput=0;
  secondInput=0;
  output=0;
  versionsChanged=kFALSE;
  currentRun=0;
  isRootFileOutput=kFALSE;
}

FairRuntimeDb::~FairRuntimeDb()
{
  // destructor
  // deletes the list of runs and all containers
  closeFirstInput();
  closeSecondInput();
  closeOutput();
  if (containerList) {
    /*
        TIter next(containerList);
        FairParSet* cont;
        while ((cont=(FairParSet*)next())) {
          Text_t* name=(char*)cont->GetName();
          cout<<"Remove Container: "<<name<<endl;
          removeContainer(name);
        }
    */
    containerList->Delete();
    delete containerList;
  }
  if (runs) {
    runs->Delete();
    delete runs;
  }
  gRtdb=0;
}

void FairRuntimeDb::addContFactory(FairContFact* fact)
{
  // Adds a container factory to the list of factories
  if (!(contFactories.FindObject(fact->GetName()))) {
    printf("- RTDB container factory %s \n",fact->GetName() );
    contFactories.Add(fact);
  }
}

FairContFact* FairRuntimeDb::getContFactory(const Text_t* FactName)
{
  return ((FairContFact*)contFactories.FindObject(FactName));
}

Bool_t FairRuntimeDb::addParamContext(const char* context)
{
  // Sets via the container factories the context of all parameter containers,
  // which accept this context
  Bool_t found=kFALSE;
  TIter next(&contFactories);
  FairContFact* fact;
  while((fact=(FairContFact*)next())) {
    if (fact->addContext(context)) { found=kTRUE; }
  }
  Error("addParamContext(const char*)","Unknown context");
  return found;
}

void FairRuntimeDb::printParamContexts()
{
  // Prints the context of all parameter containers, which can be created by
  // the container factories
  TIter next(&contFactories);
  FairContFact* fact;
  while((fact=(FairContFact*)next())) { fact->print(); }
}

Bool_t FairRuntimeDb::addContainer(FairParSet* container)
{
  // adds a container to the list of containers
  Text_t* name=(char*)container->GetName();
  if (!containerList->FindObject(name)) {
    containerList->Add(container);
    TIter next(runs);
    FairRtdbRun* run;
    FairParVersion* vers;
    while ((run=(FairRtdbRun*)next())) {
      if (!run->getParVersion(name)) {
        vers=new FairParVersion(name);
        run->addParVersion(vers);
      }
    }
    return kTRUE;
  }
  Warning("addContainer(FairParSet*)","Container %s already exists!",name);
  return kFALSE;
}

FairParSet* FairRuntimeDb::getContainer(const Text_t* name)
{
  // The function loops over the container factories to find the corresponding container
  // with the give name and its context.
  // The name is the original name of the parameter container without the concatination
  // with the context.
  // The factory checks, if the container exists already in the runtime database. Otherwise
  // it will be created and added by the factory.
  // The function returns a pointer to the container or NULL, if not created.
  TIter next(&contFactories);
  FairContFact* fact;
  FairParSet* c=0;
  while(!c && (fact=(FairContFact*)next())) {
    c=fact->getContainer(name);
  }
  if (!c) { Error("getContainer(Text_t*)","Container %s not created!",name); }
  return c;
}

FairParSet* FairRuntimeDb::findContainer(const char* name)
{
  // returns a pointer to the container called by name
  // The name is the original name of the parameter container eventually concatinated with
  // a non-default context.
  return (FairParSet*)(containerList->FindObject(name));
}

void FairRuntimeDb::removeContainer(Text_t* name)
{
  // removes the container from the list and deletes it
  TObject* c=containerList->FindObject(name);
  if (c) {
    containerList->Remove(c);
    delete c;
  }
}

void FairRuntimeDb::removeAllContainers(void)
{
  // removes all containers from the list and deletes them
  containerList->Delete();
}

FairRtdbRun* FairRuntimeDb::addRun(Int_t runId,Int_t refId)
{
  // adds a run at the end of the list of runs
  // returns a pointer to the run newly added
  FairRtdbRun* run;
  if (refId!=-1) {
    run=getRun(refId);
    if (!run) { addRun(refId); }
  }
  run=getRun(runId);
  if (!run) {
    run=new FairRtdbRun(runId,refId);
    TIter next(containerList);
    FairParSet* cont;
    FairParVersion* vers;
    while ((cont=(FairParSet*)next())) {
      vers=new FairParVersion(((char*)cont->GetName()));
      run->addParVersion(vers);
    }
    runs->Add(run);
    currentRun=run;
  } else { Warning("addRun(Int_t,Int_t)","Run already exists"); }
  return run;
}

FairRtdbRun* FairRuntimeDb::getRun(Int_t id)
{
  // returns a pointer to the run called by the run id
  char name[255];
  sprintf(name,"%i",id);
  return (FairRtdbRun*)(runs->FindObject(name));
}

FairRtdbRun* FairRuntimeDb::getRun(Text_t* name)
{
  // returns a pointer to the run called by name
  return (FairRtdbRun*)(runs->FindObject(name));
}

void FairRuntimeDb::removeRun(Text_t* name)
{
  // removes the run from the list and deletes it
  TObject* c=runs->FindObject(name);
  if (c) {
    runs->Remove(c);
    delete c;
    if(c==currentRun) { currentRun=0; }
  }
}

void FairRuntimeDb::clearRunList()
{
  runs->Delete();
}

void FairRuntimeDb::writeVersions()
{
  // writes the parameter versions for all runs to the output
  if (getOutput() && output->check()) {
    if (versionsChanged && isRootFileOutput) {
      output->cd();
      if (gFile->IsWritable()) { runs->Write(); }
      versionsChanged=kFALSE;
    }
  }
}

Bool_t FairRuntimeDb::writeContainers()
{
  // writes all containers to the output
  // loops over the list of containers and calls for each the
  // function writeContainer(...)
  TIter next(containerList);
  FairParSet* cont;
  Bool_t rc=kTRUE;
  FairRtdbRun* refRun=0;
  if (currentRun) {
    const char* refRunName=currentRun->getRefRun();
    if (strlen(refRunName)>0) {
      refRun=(FairRtdbRun*)(runs->FindObject(refRunName));
    }
    while ((cont=(FairParSet*)next())) {
      rc=writeContainer(cont,currentRun,refRun) && rc;
    }
  }
  if (!rc) { Error("writeContainers()","Error in write of containers to output"); }
  return rc;
}

Int_t FairRuntimeDb::findOutputVersion(FairParSet* cont)
{
  Int_t in1=cont->getInputVersion(1);
  Int_t in2=cont->getInputVersion(2);
  FairRtdbRun* run;
  FairParVersion* vers;
  Text_t* name=(char*)cont->GetName();
  Int_t v=0;
  if (in1==-1 && in2==-1) {
    if (cont->hasChanged()) { return 0; }
    else {
      Int_t i=runs->IndexOf(currentRun); //FIXME: This can be optimized with a backwards iter.
      while (i>=0) {
        run=(FairRtdbRun*)runs->At(i);
        vers=run->getParVersion(name);
        if (vers->getInputVersion(1)==in1 && vers->getInputVersion(2)==in2) {
          if ((v=vers->getRootVersion())!=0) { return v; }
        }
        --i;
      }
      return 0;
    }
  }
  if ((firstInput==output) && (in1>0 && in2==-1)) { return in1; }
  TIter next(runs);
  v=0;
  while ((run=(FairRtdbRun*)next())) {
    vers=run->getParVersion(name);
    if (vers->getInputVersion(1)==in1 && vers->getInputVersion(2)==in2) {
      if ((v=vers->getRootVersion())!=0) { return v; }
    }
  }
  return 0;
}

Bool_t FairRuntimeDb::writeContainer(FairParSet* cont, FairRtdbRun* run, FairRtdbRun* refRun)
{
  // writes a container to the output if the containers has changed
  // The output might be suppressed if the changes is due an initialisation from a
  //   ROOT file which serves also as output or if it was already written
  Text_t* c=(char*)cont->GetName();
  cout << "RuntimeDb: write container " << cont->GetName() << endl;
  FairParVersion* vers=run->getParVersion(c);
  Bool_t rc=kTRUE;
  Int_t cv=0;
  if (getOutput() && output->check() && output->isAutoWritable()) {
    if (isRootFileOutput) {
      if (cont->hasChanged()) {
        cv=findOutputVersion(cont);
        if (cv==0) {
          cv=cont->write(output);
          if (cv>0) {
            cout<<"***  "<<c<<" written to ROOT file   version: "<<cv<<'\n';
          } else if (cv==-1) { return kFALSE; }
          // -1 indicates and error during write
          // 0 is allowed for all containers which have no write function
        }
        vers->setRootVersion(cv);
      } else {
        if (vers->getRootVersion()==0) {
          cv=findOutputVersion(cont);
          vers->setRootVersion(cv);
        }
      }
    } else {   // might be Ascii I/O
      if (cont->hasChanged()) {
        cv=cont->write(output);
        if (cv<0) { return kFALSE; }
        cout<<"***  "<<c<<" written to output"<<'\n';
        vers->setRootVersion(cv);
      }
    }
  }
  vers->setInputVersion(cont->getInputVersion(1),1);
  vers->setInputVersion(cont->getInputVersion(2),2);
  cont->setChanged(kFALSE);
  if (refRun) {
    FairParVersion* refVers=refRun->getParVersion(c);
    if (refVers) {
      refVers->setInputVersion(cont->getInputVersion(1),1);
      refVers->setInputVersion(cont->getInputVersion(2),2);
      refVers->setRootVersion(cv);
    }
  }
  return rc;
}

Bool_t FairRuntimeDb::initContainers(Int_t runId,Int_t refId,
                                     const Text_t* fileName)
{
  // loops over the list of containers and calls the init() function of each
  // container if it is not static
  // (typically called by Hades::eventLoop(...))
  if (currentRun && currentRun->getRunId()!=runId) { writeContainers(); }
  FairRtdbRun* run=getRun(runId);
  if (!run) { run=addRun(runId,refId); }
  else {
    run->setRefRun(refId);
    if (refId!=-1 && !getRun(refId)) { addRun(refId); }
  }
  currentRun=run;
  currentFileName=fileName;
  return initContainers();
}

Bool_t FairRuntimeDb::readAll()
{
  // reads all containers with all versions for all runs and writes the
  // containers, the setup information and the version table to the output
  if (!(getOutput() && output->check())) {
    cout<<"***********************************************************"<<endl;
    cout<<"*********************  W A R N I N G  *********************"<<endl;
    cout<<"*********************   no output !   *********************"<<endl;
    cout<<"***********************************************************"<<endl;
  }
  currentRun=0;
  Bool_t rc=kTRUE;
  TIter next(runs);
  while ((currentRun=(FairRtdbRun*)next())!=0) {
    rc=initContainers() && rc;
    writeContainers();
  }
  saveOutput();
  currentRun=0;
  return kTRUE;
}

Bool_t FairRuntimeDb::initContainers(void)
{
  // private function
  Text_t* refRunName=(char*)currentRun->getRefRun();
  Int_t len=strlen(refRunName);
  if (len<1) {
    if (firstInput) { firstInput->readVersions(currentRun); }
    if (secondInput) { secondInput->readVersions(currentRun); }
  } else {
    FairRtdbRun* refRun=getRun(refRunName);
    if (firstInput) { firstInput->readVersions(refRun); }
    if (secondInput) { secondInput->readVersions(refRun); }
  }
  TIter next(containerList);
  FairParSet* cont;
  Bool_t rc=kTRUE;
  cout<<'\n'<<"*************************************************************"<<'\n';
  if (currentFileName.IsNull()) {
    cout<<"     initialisation for run id "<<currentRun->GetName();
  } else {
    cout<<"     initialisation for event file "<<currentFileName.Data()<<'\n';
    cout<<"     run id "<<currentRun->GetName();
  }
  if (len>0) { cout << " --> " << refRunName; }
  cout<<'\n'<<"*************************************************************"<<'\n';
  while ((cont=(FairParSet*)next())) {
    if (!cont->isStatic()) { rc=cont->init() && rc; }
  }
  if (!rc) { Error("initContainers()","Error occured during initialization"); }
  return rc;
}

void FairRuntimeDb::setContainersStatic(Bool_t flag)
{
  // sets the status flag in all containers
  // flag kTRUE sets all 'static'
  // flag kFALSE sets all 'not static'
  TIter next(containerList);
  FairParSet* cont;
  while ((cont=(FairParSet*)next())) {
    cont->setStatic(flag);
  }
}

Bool_t FairRuntimeDb::setInputVersion(Int_t run,Text_t* container,
                                      Int_t version,Int_t inp)
{
  // sets the input version of a container defined by its name and a
  // run defined by its id taken from input with inputNumber inp
  // (1 for first input and 2 for second input)
  FairRtdbRun* r=getRun(run);
  if (r) {
    FairParVersion* v=r->getParVersion(container);
    if (v) {
      v->setInputVersion(version,inp);
      return kTRUE;
    } else { Error("setInputVersion","Container not found"); }
  } else { Error("setInputVersion","Run not found"); }
  return kFALSE;
}


Bool_t FairRuntimeDb::setRootOutputVersion(Int_t run,Text_t* container,
    Int_t version)
{
  // sets the Root file output version of a container defined by its name
  // and a run defined by its id
  // should only be used after initialization 'by hand' on the interpreter level
  FairRtdbRun* r=getRun(run);
  if (r) {
    FairParVersion* v=r->getParVersion(container);
    if (v) {
      v->setRootVersion(version);
      return kTRUE;
    } else { Error("setRootOutputVersion","Container not found"); }
  } else { Error("setRootOutputVersion","Run not found"); }
  return kFALSE;
}

void FairRuntimeDb::print()
{
  // prints the list of the actual containers, the list of the
  // runs/versions and information about input/output
  cout<<"--------------------------------------------------------------------------------\n";
  cout<<"--------------  actual containers in runtime database  -------------------------\n";
  TIter nextCont(containerList);
  FairParSet* cont;
  cout.setf(ios::left,ios::adjustfield);
  while((cont=(FairParSet*)nextCont())) {
    cout<<setw(45)<<cont->GetName()<<"  "<<cont->GetTitle()<<'\n';
  }
  TIter next(runs);
  FairRtdbRun* run;
  cout<<"--------------  runs, versions  ------------------------------------------------\n";
  cout<<"run id\n";
  cout<<"  "<<setw(45)<<"container";
  cout.setf(ios::right,ios::adjustfield);
  cout<<setw(11)<<"1st-inp"
      <<setw(11)<<" 2nd-inp"
      <<setw(11)<<" output\n";
  while ((run=(FairRtdbRun*)next())) {
    run->print();
  }
  cout<<"--------------  input/output  --------------------------------------------------\n";
  if (firstInput) {
    cout<<"first Input:\n";
    firstInput->print();
  } else { cout<<"first input: none"<<'\n'; }
  if (secondInput) {
    cout<<"second Input:\n";
    secondInput->print();
  } else { cout<<"second input: none"<<'\n'; }
  if (output) {
    cout<<"output:\n";
    output->print();
  } else { cout<<"output: none"<<'\n'; }
}

void FairRuntimeDb::resetInputVersions()
{
  // resets all input versions in the list of runs and in all containers which are not static
  // is called each time a new input is set
  TIter nextRun(runs);
  FairRtdbRun* run;
  while ((run=(FairRtdbRun*)nextRun())) {
    run->resetInputVersions();
  }
  TIter nextCont(containerList);
  FairParSet* cont;
  while ((cont=(FairParSet*)nextCont())) {
    if (!cont->isStatic()) { cont->resetInputVersions(); }
  }
}

void FairRuntimeDb::resetOutputVersions()
{
  // resets all output versions in the list of runs
  // is called each time a new output is set
  // is called also each time a new input is set which is not identical with the output
  TIter next(runs);
  FairRtdbRun* run;
  while ((run=(FairRtdbRun*)next())) {
    run->resetOutputVersions();
  }
}

void FairRuntimeDb::resetAllVersions()
{
  // resets all input and output versions in the list of runs
  // and in all containers which are not static
  resetInputVersions();
  resetOutputVersions();
}

Bool_t FairRuntimeDb::setFirstInput(FairParIo* inp1)
{
  // sets the first input pointer
  firstInput=inp1;
  if (inp1->check()==kTRUE) {
    inp1->setInputNumber(1);
    resetInputVersions();
    if (output && firstInput!=output) { resetOutputVersions(); }
    return kTRUE;
  } else { Error("setFirstInput(FairParIo*)","no connection to input"); }
  return kFALSE;
}

Bool_t FairRuntimeDb::setSecondInput(FairParIo* inp2)
{
  // sets the second input pointer
  secondInput=inp2;
  if (inp2->check()==kTRUE) {
    inp2->setInputNumber(2);
    resetInputVersions();
    if (output && firstInput!=output) { resetOutputVersions(); }
    return kTRUE;
  } else { Error("setSecondInput(FairParIo*)","no connection to input"); }
  return kFALSE;
}

Bool_t FairRuntimeDb::setOutput(FairParIo* op)
{
  // sets the output pointer
  output=op;
  if (output->check()==kTRUE) {
    resetOutputVersions();
    if (strcmp(output->IsA()->GetName(),"FairParRootFileIo")==0) {
      isRootFileOutput=kTRUE;
    }
    return kTRUE;
  } else { Error("setOutput(FairParIo*)","no connection to output"); }
  return kFALSE;
}

FairParIo* FairRuntimeDb::getFirstInput()
{
  // return a pointer to the first input
  if (firstInput) { firstInput->cd(); }
  return firstInput;
}

FairParIo* FairRuntimeDb::getSecondInput()
{
  // return a pointer to the second input
  if (secondInput) { secondInput->cd(); }
  return secondInput;
}

FairParIo* FairRuntimeDb::getOutput()
{
  // return a pointer to the output
  if (output) { output->cd(); }
  return output;
}

void FairRuntimeDb::closeFirstInput()
{
  if (firstInput) {
    firstInput->cd();
    firstInput->close();
    firstInput=0;
  }
}

void FairRuntimeDb::closeSecondInput()
{
  if (secondInput) {
    secondInput->cd();
    secondInput->close();
    secondInput=0;
  }
}

void FairRuntimeDb::saveOutput()
{
  // writes the versions and the containers (if not yet written out)
  // without the version information the containers cannot be read from a ROOT file!
  Bool_t rc=kTRUE;
  if (currentRun!=0) { rc=writeContainers(); }
  writeVersions();
  if (!rc) { Error("saveOutput()","Error occured during write"); }
}

void FairRuntimeDb::closeOutput()
{
  // calls saveOutput() and deletes then the output
  if (output) {
    if (output->isAutoWritable()) { saveOutput(); }
    output->close();
    resetOutputVersions();
    output=0;
    isRootFileOutput=kFALSE;
  }
}

void FairRuntimeDb::activateParIo(FairParIo* io)
{
  // activates the detector I/O

  const char* ioName=io->IsA()->GetName();
  FairDetParIo* po=io->getDetParIo("FairGenericParIo");
  if (!po) {
    if (strcmp(ioName,"FairParRootFileIo")==0) {
      FairDetParRootFileIo* pn=
        new FairGenericParRootFileIo(((FairParRootFileIo*)io)->getParRootFile());
      io->setDetParIo(pn);
    } else if (strcmp(ioName,"FairParAsciiFileIo")==0) {
      FairDetParAsciiFileIo* pn=
        new FairGenericParAsciiFileIo(((FairParAsciiFileIo*)io)->getFile());
      io->setDetParIo(pn);
    }
  }
  TIter next(&contFactories);
  FairContFact* fact;
  while((fact=(FairContFact*)next())) {
    fact->activateParIo(io);
  }
}
