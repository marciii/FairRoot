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
// std::string content; // cannot be here; Not a POD type: http://en.cppreference.com/w/cpp/concept/PODType
};

PrototypeFlpProcessor::PrototypeFlpProcessor()
{
  OnData("scheduledatatoflp", &PrototypeFlpProcessor::HandleData);
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

  LOG(info) << "meine id: " << myId;

  
  if (receivedMsg.replyId == myId || receivedMsg.replyId == 99999) { //dieser FLP soll antworten oder jeder FLP soll antworten

 //den teil dann in die obige if schleife
  const string text = "bestätigung von FLP";
  FairMQMessagePtr answer(NewMessage(text.length()));
  memcpy(answer->GetData(), text.c_str(), text.length());

  LOG(info) << "Sende bestaetigung für RTT";
  if (Send(answer, "scheduledatatoflp") < 0) {
    LOG(error) << "Bestaetigung konnte nicht gesendet werden";
    return false;
  }

  }

  

  return true;
}


PrototypeFlpProcessor::~PrototypeFlpProcessor()
{
}
