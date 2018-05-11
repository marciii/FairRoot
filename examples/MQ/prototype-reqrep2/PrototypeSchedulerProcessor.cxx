/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * PrototypeSchedulerProcessor.cxx
 *
 * @since 2014-10-10
 * @author A. Rybalchenko
 */

#include "PrototypeSchedulerProcessor.h"
#include "FairMQLogger.h"
#include "FairMQProgOptions.h" // device->fConfig

using namespace std;

PrototypeSchedulerProcessor::PrototypeSchedulerProcessor()
    : fMaxIterations(0)
    , fNumIterations(0)
{
	OnData("epndata", &PrototypeSchedulerProcessor::HandleData);
}

void PrototypeSchedulerProcessor::InitTask()
{
    // Get the fMaxIterations value from the command line options (via fConfig)
    fMaxIterations = fConfig->GetValue<uint64_t>("max-iterations");
}

bool PrototypeSchedulerProcessor::HandleData(FairMQMessagePtr& request, int /*index*/)
{
   
    LOG(info) << "Received request from client: \"" << string(static_cast<char*>(request->GetData()), request->GetSize()) << "\"";

    string* text = new string("bestaetigung, dass nachricht ankam");

    LOG(info) << "Sende EPN Bestaetigung";

    FairMQMessagePtr reply(NewMessage(const_cast<char*>(text->c_str()), // data
                                                        text->length(), // size
                                                        [](void* /*data*/, void* object) { delete static_cast<string*>(object); }, // deletion callback
                                                        text)); // object that manages the data

    if (Send(reply, "epndata") > 0)
    {
        if (fMaxIterations > 0 && ++fNumIterations >= fMaxIterations)
        {
            LOG(info) << "Configured maximum number of iterations reached. Leaving RUNNING state.";
            return false;
        }

	string* flpinfo = new string(static_cast<char*>(request->GetData()), request->GetSize());
	string* flpinfo2 = new string("flpinfo2");
	string* flpinfo3 = new string("flpinfo3");
FairMQMessagePtr flpMsg[3];

 flpMsg[0] = NewMessage(const_cast<char*>(flpinfo->c_str()), // data
                                                        flpinfo->length(), // size
                                                        [](void* /*data*/, void* object) { delete static_cast<string*>(object); }, // deletion callback
                                                        flpinfo); // object that manages the data
 flpMsg[1] = NewMessage(const_cast<char*>(flpinfo2->c_str()), // data
                                                        flpinfo2->length(), // size
                                                        [](void* /*data*/, void* object) { delete static_cast<string*>(object); }, // deletion callback
                                                        flpinfo2); // object that manages the data
 flpMsg[2] = NewMessage(const_cast<char*>(flpinfo3->c_str()), // data
                                                        flpinfo3->length(), // size
                                                        [](void* /*data*/, void* object) { delete static_cast<string*>(object); }, // deletion callback
                                                        flpinfo3); // object that manages the data

//for (int i=0;i<3;i++) { //den Inhalt jeder Nachricht fuellen
  //  flpMsg[i] = NewMessage(const_cast<char*>(flpinfo->c_str()), // data
    //                                                    flpinfo->length(), // size
      //                                                  [](void* /*data*/, void* object) { delete static_cast<string*>(object); }, // deletion callback
        //                                                flpinfo); // object that manages the data
//}


	FairMQMessagePtr flpReply[3];
	
	flpReply[0] = NewMessage();
	flpReply[1] = NewMessage();
	flpReply[2] = NewMessage(); 

	
	//wieder über alle channel iterieren
	for (int i=0;i<3;i++) {
	LOG(info) << "Leite weiter an FLP"<<i;
		if (Send(flpMsg[i], "scheduledata", i) > 0) {
       			 if (Receive(flpReply[i], "scheduledata", i) >= 0) {
           	 LOG(info) << "Received reply from server: \"" << string(static_cast<char*>(flpReply[i]->GetData()), flpReply[i]->GetSize()) << "\"";
		}
	}
	}

        return true;
    }

    return false;
}

PrototypeSchedulerProcessor::~PrototypeSchedulerProcessor()
{
}
