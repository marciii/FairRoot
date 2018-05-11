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
//#include "GnuPlot.h"
//#include "Plot.h"
using namespace std;



PrototypeFlpProcessor::PrototypeFlpProcessor()
    : fMaxIterations(0)
    , fNumIterations(0)
{
    // register a handler for data arriving on "data" channel
    OnData("scheduledatatoflp", &PrototypeFlpProcessor::HandleData);
}

void PrototypeFlpProcessor::InitTask()
{
    // Get the fMaxIterations value from the command line options (via fConfig)
    fMaxIterations = fConfig->GetValue<uint64_t>("max-iterations");
	LOG(info) << "max iterations: " << std::to_string(fMaxIterations);
}


bool PrototypeFlpProcessor::HandleData(FairMQMessagePtr& msg, int index)
{
	
	LOG(info) << "index: " <<index;

 	
    //LOG(info) << "Empfange von scheduler: \"" << string(static_cast<char*>(msg->GetData()), msg->GetSize()) << "\"";
	LOG(info) << "habe nachricth empfangen, groesse: " << msg->GetSize();
	

	//teil für random ID -> statistik
	//std::string msgText = string(static_cast<char*>(msg->GetData()));
	//std::string ID = msgText.substr(0,4);
	



   string* text = new string("bestätigung von FLP");
    FairMQMessagePtr answer(NewMessage(const_cast<char*>(text->c_str()),
                                    text->length(),
                                    [](void* /*data*/, void* object) { delete static_cast<string*>(object); },
                                    text));
	LOG(info) << "sende bestätigung für RTT";
 if (Send(answer, "scheduledatatoflp") < 0)
    {
        return false;
    }


    //this_thread::sleep_for(chrono::seconds(10));

    // return true if want to be called again (otherwise return false go to IDLE state)
    return true;
}

void PrototypeFlpProcessor::write(std::string s1, std::string s2, pid_t s3) {
	std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
	gnudatafile << s1 << "\t" << s2 << "\t" << s3 << std::endl;
	return;
}


PrototypeFlpProcessor::~PrototypeFlpProcessor()
{
}
