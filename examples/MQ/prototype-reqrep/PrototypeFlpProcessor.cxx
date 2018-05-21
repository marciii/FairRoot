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
  bool confirmation;
};

int messageCounter = 0;

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

	MyMessage conf;
	conf.confirmation = true;

	FairMQMessagePtr confirmation = NewMessage(100);
	memcpy(confirmation->GetData(), &conf, sizeof(MyMessage));


    LOG(info) << "Sende an Scheduler:  \"" << *text << "\"";

    high_resolution_clock::time_point rttBefore = high_resolution_clock::now();


    if (Send(request, "scheduledata") > 0) //1)
    {
        if (Receive(reply, "scheduledata") >= 0) {//4)
		
		
		LOG(info) << "hier";

		//Send(confirmation, "scheduledata"); //hier ist der Fehler
		
	
            this_thread::sleep_for(chrono::seconds(10));

            return true;
        }
    }

    return false;
}


PrototypeFlpProcessor::~PrototypeFlpProcessor()
{
}
