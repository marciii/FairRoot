/********************************************************************************
*    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
*                                                                              *
*              This software is distributed under the terms of the             *
*              GNU Lesser General Public Licence (LGPL) version 3,             *
*                  copied verbatim in the file "LICENSE"                       *
********************************************************************************/
/**
* FairMQExample1Sink.cxx
*
* @since 2014-10-10
* @author A. Rybalchenko
*/

#include "PrototypeFlpProcessor.h"
#include "FairMQLogger.h"
#include "FairMQProgOptions.h" // device->fConfig
#include <unistd.h>

using namespace std;

struct MyMessage {
  uint64_t sendCounter;
  uint64_t replyId;
};

PrototypeFlpProcessor::PrototypeFlpProcessor()
{
  OnData("sched-flp-chan", &PrototypeFlpProcessor::HandleData);
}

void PrototypeFlpProcessor::InitTask()
{
  myId = fConfig->GetValue<uint64_t>("myId");
}


bool PrototypeFlpProcessor::HandleData(FairMQMessagePtr& msg, int index)
{

  LOG(info) << "habe nachricth empfangen, groesse: " << msg->GetSize();


  MyMessage receivedMsg;

  // make sure the msg is large enough to hold the data
  assert(msg->GetSize() >= sizeof(MyMessage));
  memcpy(&receivedMsg, msg->GetData(), sizeof(MyMessage));


  if (receivedMsg.replyId == myId || receivedMsg.replyId == 99999) { //dieser FLP soll antworten oder jeder FLP soll antworten

    FairMQMessagePtr answer(NewMessage(100));
  


    if (Send(answer, "sched-flp-chan") < 0) {
      LOG(error) << "Bestaetigung konnte nicht gesendet werden";
      return false;
    }

  }



  return true;
}


PrototypeFlpProcessor::~PrototypeFlpProcessor()
{
}
