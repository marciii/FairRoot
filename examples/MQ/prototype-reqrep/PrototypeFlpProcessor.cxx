/********************************************************************************
*    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
*                                                                              *
*              This software is distributed under the terms of the             *
*              GNU Lesser General Public Licence (LGPL) version 3,             *
*                  copied verbatim in the file "LICENSE"                       *
********************************************************************************/
/**
* PrototypeEpnProcessor.cpp
*
* @since 2014-10-10
* @author A. Rybalchenko
*/

#include <memory> // unique_ptr
#include <thread> // this_thread::sleep_for
#include <chrono>

#include "PrototypeFlpProcessor.h"
#include "FairMQLogger.h"
#include "FairMQProgOptions.h"
#include "HardwareInformation.h"

#include <string>
#include <sstream>
//times
#include <ctime>


using namespace std::chrono;
using namespace std;



struct MyMessage {
  uint64_t sendCounter;
  uint64_t replyId;
  uint64_t flpId;
  uint64_t frequency;
  uint64_t numberFlp;
  uint64_t numberMessages;
  bool confirmation;
};

int messageCounter = 0;
uint64_t msgFreq;
uint64_t amountFlp;
uint64_t amountMessages;

PrototypeFlpProcessor::PrototypeFlpProcessor()
{
  OnData("scheduledata", &PrototypeFlpProcessor::HandleData);
}

void PrototypeFlpProcessor::InitTask()
{
  myId = fConfig->GetValue<uint64_t>("myId");
}


bool PrototypeFlpProcessor::HandleData(FairMQMessagePtr& request, int /*index*/)
{
  LOG(info) << "nachricht empfangen, antworte";
  FairMQMessagePtr reply = NewMessage(100);
  if (Send(reply, "scheduledata") > 0)
  {

      return true;
  }

  return false;
}

  void PrototypeFlpProcessor::writeToFile(std::string text)
  {
    std::stringstream filename;
    filename << "gnudatafile" << myId << ".txt";
    std::ofstream gnudatafile(filename.str(), std::ios_base::out | std::ios_base::app );
    gnudatafile << text;
    return;
  }


  PrototypeFlpProcessor::~PrototypeFlpProcessor()
  {
  }
