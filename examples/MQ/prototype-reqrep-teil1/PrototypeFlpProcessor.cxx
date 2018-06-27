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

/*
bool PrototypeFlpProcessor::ConditionalRun()
{


  messageCounter++;
  if (messageCounter == amountMessages) {
    LOG(info) << "am ende angelangt, schreibe";
    writeToFile(result.str());
    return false;
  }


  MyMessage requ;
  requ.confirmation = false;
  FairMQMessagePtr request = NewMessage(100);
  memcpy(request->GetData(), &requ, sizeof(MyMessage));



  FairMQMessagePtr reply(NewMessage());
  FairMQMessagePtr reply2(NewMessage());

  MyMessage conf;
  conf.confirmation = true;
  conf.sendCounter = messageCounter;
  conf.flpId = myId;

  FairMQMessagePtr confirmation = NewMessage(100);
  memcpy(confirmation->GetData(), &conf, sizeof(MyMessage));


  LOG(info) << "Sende an Scheduler:  \"" << *text << "\"";

  before = high_resolution_clock::now();


  if (Send(request, "scheduledata") > 0) //1)
  {
    if (Receive(reply, "scheduledata") >= 0) {//4)

      MyMessage replyMsg;
      memcpy(&replyMsg, reply->GetData(), sizeof(MyMessage));
      //msgSize = string(static_cast<char*>(reply->GetSize()));
      msgSize = std::to_string(reply->GetSize());
    //  msgSize = string(static_cast<char*>(reply->GetSize()));
      msgFreq = replyMsg.frequency;
      amountFlp = replyMsg.numberFlp;
      amountMessages = replyMsg.numberMessages;

      after = high_resolution_clock::now();
      duration<double> dur = duration_cast<duration<double>>(after - before);

      result << myId << "\t" << msgSize << "\t" << amountFlp << "\t" << dur.count() << std::endl;

        LOG(info) << "sende bestätigung";
        Send(confirmation, "scheduledata");//5)

        if (Receive(reply2, "scheduledata") > 0 ) {//8)


          this_thread::sleep_for(chrono::milliseconds(msgFreq));

          return true; }
          else
          return false;
        }

    }

    this_thread::sleep_for(chrono::milliseconds(msgFreq));
    return false;
  }
*/
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
