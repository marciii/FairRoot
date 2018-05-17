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

    // create message object with a pointer to the data buffer,
    // its size,
    // custom deletion function (called when transfer is done),
    // and pointer to the object managing the data buffer
    FairMQMessagePtr request(NewMessage(const_cast<char*>(text->c_str()), // data
                                                          text->length(), // size
                                                          [](void* /*data*/, void* object) { delete static_cast<string*>(object); }, // deletion callback
                                                          text)); // object that manages the data
	
 FairMQMessagePtr bestaetigung(NewMessage(const_cast<char*>(bestaetigungtext->c_str()), // data
                                                          bestaetigungtext->length(), // size
                                                          [](void* /*data*/, void* object) { delete static_cast<string*>(object); }, // deletion callback
                                                          bestaetigungtext)); // object that manages the data
    FairMQMessagePtr reply(NewMessage());

    LOG(info) << "Sende an Scheduler:  \"" << *text << "\"";

    high_resolution_clock::time_point rttBefore = high_resolution_clock::now();


    if (Send(request, "scheduledata") > 0) //1)
    {
        if (Receive(reply, "scheduledata") >= 0) //4)
        {
		MyMessage receivedMsg;

 		 // make sure the msg is large enough to hold the data
  		assert(reply->GetSize() >= sizeof(MyMessage));

  		memcpy(&receivedMsg, reply->GetData(), sizeof(MyMessage));

            LOG(info) << "Received reply from server: \"" << reply->GetSize();

	
		Send(bestaetigung, "scheduledata"); //5), bestätigung für scheduler, um RTT zu berechnen
	LOG(info) << "letzte bestätigung an scheduler gesendet";
	/*
	high_resolution_clock::time_point rttAfter = high_resolution_clock::now();
	duration<double> rtt = duration_cast<duration<double>>(rttAfter - rttBefore);
	LOG(info) << "dauer : " << rtt.count() << " seconds"<<std::endl;
	//write(std::to_string(reply->GetSize()), rtt);
	//write(messageCounter, std::to_string(reply->GetSize()), rtt);
	*/
            this_thread::sleep_for(chrono::seconds(10));

            return true;
        }
    }

    return false;
}


PrototypeFlpProcessor::~PrototypeFlpProcessor()
{
}
