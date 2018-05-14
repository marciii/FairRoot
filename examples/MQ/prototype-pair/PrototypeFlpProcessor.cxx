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
std::string content;
};

PrototypeFlpProcessor::PrototypeFlpProcessor()
{
    // register a handler for data arriving on "data" channel
    OnData("scheduledatatoflp", &PrototypeFlpProcessor::HandleData);
}

void PrototypeFlpProcessor::InitTask()
{
    myId = fConfig->GetValue<uint64_t>("myId");
}


bool PrototypeFlpProcessor::HandleData(FairMQMessagePtr& msg, int index)
{
	
	LOG(info) << "habe nachricth empfangen, groesse: " << msg->GetSize();
	
	
	LOG(info) << "hier1";
	MyMessage receivedMsg;
	memcpy(&receivedMsg, msg->GetData(), sizeof(MyMessage)); //hier noch fehler

	LOG(info) << "hier2";

	/*
	if (receivedMsg.replyId == myId || receivedMsg.replyId == -1) { dieser FLP soll antworten oder jeder FLP soll antworten
	


	}

	*/
	

 //den teil dann in die obige if schleife
   string* text = new string("bestätigung von FLP");
    FairMQMessagePtr answer(NewMessage(const_cast<char*>(text->c_str()),
                                    text->length(),
                                    [](void* /*data*/, void* object) { delete static_cast<string*>(object); },
                                    text));
	LOG(info) << "Sende bestaetigung für RTT";
 if (Send(answer, "scheduledatatoflp") < 0)
    {
	LOG(error) << "Bestaetigung konnte nicht gesendet werden";
        return false;
    }


    return true;
}


PrototypeFlpProcessor::~PrototypeFlpProcessor()
{
}
