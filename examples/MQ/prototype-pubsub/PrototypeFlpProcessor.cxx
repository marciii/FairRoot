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

using namespace std;

struct MyMessage {
  uint64_t sendCounter;
  uint64_t replyId;
};

PrototypeFlpProcessor::PrototypeFlpProcessor()
{
  OnData("scheduledatatoflp", &PrototypeFlpProcessor::HandleData);
}

void PrototypeFlpProcessor::InitTask()
{
  myId = fConfig->GetValue<uint64_t>("myId");
}


bool PrototypeFlpProcessor::HandleData(FairMQMessagePtr& msg, int /*index*/)
{
  LOG(info) << "Empfange von scheduler, groesse: \"" << std::to_string(msg->GetSize()) << "\"";


  MyMessage receivedMsg;

  // make sure the msg is large enough to hold the data
  assert(msg->GetSize() >= sizeof(MyMessage));

  memcpy(&receivedMsg, msg->GetData(), sizeof(MyMessage));

  
  if (receivedMsg.replyId == myId || receivedMsg.replyId == 99999) { //dieser FLP soll antworten oder jeder FLP soll antworten
  LOG(info) << "sende bestaetigung an scheduler";
  const string text = "answer from FLP";

  FairMQMessagePtr answer(NewMessage(text.length()));

  memcpy(answer->GetData(), text.c_str(), text.length());

  if (Send(answer, "answerfromflp") < 0) {
    LOG(error) << "fail";
    return false;
  }
}

  return true;
}

PrototypeFlpProcessor::~PrototypeFlpProcessor()
{
}
