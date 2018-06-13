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

//times
#include <ctime>


using namespace std::chrono;
using namespace std;

struct MyMessage {
  uint64_t sendCounter;
  uint64_t replyId;
  uint64_t flpId;
  uint64_t frequency;
  bool confirmation;
};

int messageCounter = 0;
uint64_t msgFreq;

PrototypeFlpProcessor::PrototypeFlpProcessor()
{
}

void PrototypeFlpProcessor::InitTask()
{
  myId = fConfig->GetValue<uint64_t>("myId");
  this_thread::sleep_for(chrono::seconds(10));
}

bool PrototypeFlpProcessor::ConditionalRun()
{


  messageCounter++;


  string* text = new string(std::to_string(messageCounter) + ". Nachricht");
  string* bestaetigungtext = new string("bestätigung von flp");

  //FairMQMessagePtr request(NewMessage(const_cast<char*>(text->c_str()), // data
  //                                                    text->length(), // size
  //                                                  [](void* /*data*/, void* object) { delete static_cast<string*>(object); }, // deletion callback
  //                                                text)); // object that manages the data

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

  high_resolution_clock::time_point rttBefore = high_resolution_clock::now();


  if (Send(request, "scheduledata") > 0) //1)
  {
    if (Receive(reply, "scheduledata") >= 0) {//4)
      MyMessage replyMsg;
      memcpy(&replyMsg, reply->GetData(), sizeof(MyMessage));
      msgFreq = replyMsg.frequency;


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


  PrototypeFlpProcessor::~PrototypeFlpProcessor()
  {
  }
