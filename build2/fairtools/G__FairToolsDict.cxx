// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedImarcidIfair_installdIFairRootdIbuild2dIfairtoolsdIG__FairToolsDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "FairLogger.h"
#include "FairMonitor.h"
#include "FairSystemInfo.h"

// Header files passed via #pragma extra_include

namespace ROOT {

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairLogger*)
   {
      ::FairLogger *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairLogger >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairLogger", ::FairLogger::Class_Version(), "FairLogger.h", 30,
                  typeid(::FairLogger), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairLogger::Dictionary, isa_proxy, 4,
                  sizeof(::FairLogger) );
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairLogger*)
   {
      return GenerateInitInstanceLocal((::FairLogger*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FairLogger*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMonitor*)
   {
      ::FairMonitor *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMonitor >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMonitor", ::FairMonitor::Class_Version(), "FairMonitor.h", 30,
                  typeid(::FairMonitor), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMonitor::Dictionary, isa_proxy, 4,
                  sizeof(::FairMonitor) );
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMonitor*)
   {
      return GenerateInitInstanceLocal((::FairMonitor*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FairMonitor*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairSystemInfo(void *p = 0);
   static void *newArray_FairSystemInfo(Long_t size, void *p);
   static void delete_FairSystemInfo(void *p);
   static void deleteArray_FairSystemInfo(void *p);
   static void destruct_FairSystemInfo(void *p);
   static void streamer_FairSystemInfo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairSystemInfo*)
   {
      ::FairSystemInfo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairSystemInfo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairSystemInfo", ::FairSystemInfo::Class_Version(), "FairSystemInfo.h", 21,
                  typeid(::FairSystemInfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairSystemInfo::Dictionary, isa_proxy, 16,
                  sizeof(::FairSystemInfo) );
      instance.SetNew(&new_FairSystemInfo);
      instance.SetNewArray(&newArray_FairSystemInfo);
      instance.SetDelete(&delete_FairSystemInfo);
      instance.SetDeleteArray(&deleteArray_FairSystemInfo);
      instance.SetDestructor(&destruct_FairSystemInfo);
      instance.SetStreamerFunc(&streamer_FairSystemInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairSystemInfo*)
   {
      return GenerateInitInstanceLocal((::FairSystemInfo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FairSystemInfo*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairLogger::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairLogger::Class_Name()
{
   return "FairLogger";
}

//______________________________________________________________________________
const char *FairLogger::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairLogger*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairLogger::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairLogger*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairLogger::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairLogger*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairLogger::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairLogger*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMonitor::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMonitor::Class_Name()
{
   return "FairMonitor";
}

//______________________________________________________________________________
const char *FairMonitor::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMonitor*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMonitor::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMonitor*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMonitor::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMonitor*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMonitor::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMonitor*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairSystemInfo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairSystemInfo::Class_Name()
{
   return "FairSystemInfo";
}

//______________________________________________________________________________
const char *FairSystemInfo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairSystemInfo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairSystemInfo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairSystemInfo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairSystemInfo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairSystemInfo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairSystemInfo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairSystemInfo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairLogger::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairLogger.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairLogger::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairLogger::Class(),this);
   }
}

namespace ROOT {
} // end of namespace ROOT for class ::FairLogger

//______________________________________________________________________________
void FairMonitor::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMonitor.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMonitor::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMonitor::Class(),this);
   }
}

namespace ROOT {
} // end of namespace ROOT for class ::FairMonitor

//______________________________________________________________________________
void FairSystemInfo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairSystemInfo.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      R__b.CheckByteCount(R__s, R__c, FairSystemInfo::IsA());
   } else {
      R__c = R__b.WriteVersion(FairSystemInfo::IsA(), kTRUE);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairSystemInfo(void *p) {
      return  p ? new(p) ::FairSystemInfo : new ::FairSystemInfo;
   }
   static void *newArray_FairSystemInfo(Long_t nElements, void *p) {
      return p ? new(p) ::FairSystemInfo[nElements] : new ::FairSystemInfo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairSystemInfo(void *p) {
      delete ((::FairSystemInfo*)p);
   }
   static void deleteArray_FairSystemInfo(void *p) {
      delete [] ((::FairSystemInfo*)p);
   }
   static void destruct_FairSystemInfo(void *p) {
      typedef ::FairSystemInfo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairSystemInfo(TBuffer &buf, void *obj) {
      ((::FairSystemInfo*)obj)->::FairSystemInfo::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairSystemInfo

namespace ROOT {
   static TClass *vectorlEchargR_Dictionary();
   static void vectorlEchargR_TClassManip(TClass*);
   static void *new_vectorlEchargR(void *p = 0);
   static void *newArray_vectorlEchargR(Long_t size, void *p);
   static void delete_vectorlEchargR(void *p);
   static void deleteArray_vectorlEchargR(void *p);
   static void destruct_vectorlEchargR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<char>*)
   {
      vector<char> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<char>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<char>", -2, "vector", 216,
                  typeid(vector<char>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEchargR_Dictionary, isa_proxy, 0,
                  sizeof(vector<char>) );
      instance.SetNew(&new_vectorlEchargR);
      instance.SetNewArray(&newArray_vectorlEchargR);
      instance.SetDelete(&delete_vectorlEchargR);
      instance.SetDeleteArray(&deleteArray_vectorlEchargR);
      instance.SetDestructor(&destruct_vectorlEchargR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<char> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<char>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEchargR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<char>*)0x0)->GetClass();
      vectorlEchargR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEchargR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEchargR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<char> : new vector<char>;
   }
   static void *newArray_vectorlEchargR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<char>[nElements] : new vector<char>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEchargR(void *p) {
      delete ((vector<char>*)p);
   }
   static void deleteArray_vectorlEchargR(void *p) {
      delete [] ((vector<char>*)p);
   }
   static void destruct_vectorlEchargR(void *p) {
      typedef vector<char> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<char>

namespace {
  void TriggerDictionaryInitialization_G__FairToolsDict_Impl() {
    static const char* headers[] = {
"FairLogger.h",
"FairMonitor.h",
"FairSystemInfo.h",
0
    };
    static const char* includePaths[] = {
"/home/marci/fair_install/FairRoot/logger",
"/home/marci/fair_install/FairRoot/fairtools",
"/home/marci/fair_install/FairSoftInst/include/root",
"/home/marci/fair_install/FairSoftInst/include/root",
"/home/marci/fair_install/FairRoot/build2/fairtools/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__FairToolsDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$FairLogger.h")))  FairLogger;
class __attribute__((annotate("$clingAutoload$FairMonitor.h")))  FairMonitor;
class __attribute__((annotate("$clingAutoload$FairSystemInfo.h")))  FairSystemInfo;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__FairToolsDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "FairLogger.h"
#include "FairMonitor.h"
#include "FairSystemInfo.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairLogger", payloadCode, "@",
"FairMonitor", payloadCode, "@",
"FairSystemInfo", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__FairToolsDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__FairToolsDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__FairToolsDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__FairToolsDict() {
  TriggerDictionaryInitialization_G__FairToolsDict_Impl();
}
