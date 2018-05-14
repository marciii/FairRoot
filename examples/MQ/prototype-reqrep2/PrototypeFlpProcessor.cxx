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

int messageCounter = 0;

PrototypeFlpProcessor::PrototypeFlpProcessor()
{
	OnData("scheduledata", &PrototypeFlpProcessor::HandleData);
}

void PrototypeFlpProcessor::InitTask()
{
}

//bool PrototypeFlpProcessor::ConditionalRun()
bool PrototypeFlpProcessor::HandleData(FairMQMessagePtr& request, int index)
{
	LOG(info) << "empfange von scheduler";
   
 	messageCounter++;

	string* bestaetigungtext = new string("bestätigung von flp");

    // create message object with a pointer to the data buffer,
    // its size,
    // custom deletion function (called when transfer is done),
    // and pointer to the object managing the data buffer

	
 FairMQMessagePtr bestaetigung(NewMessage(const_cast<char*>(bestaetigungtext->c_str()), // data
                                                          bestaetigungtext->length(), // size
                                                          [](void* /*data*/, void* object) { delete static_cast<string*>(object); }, // deletion callback
                                                          bestaetigungtext)); // object that manages the data
    FairMQMessagePtr reply(NewMessage());

    LOG(info) << "Sende an Scheduler:  \"" << *bestaetigungtext << "\"";



    if (Send(bestaetigung, "scheduledata") > 0)
    {
      
            return true;
        
    }

    return false;
}

void PrototypeFlpProcessor::write(std::string s1, duration<double> rtt) {
	std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
	gnudatafile << s1 << "\t" << rtt.count() << std::endl;
	return;
}
void PrototypeFlpProcessor::write(int messageCounter, std::string s1, duration<double> rtt) {
	std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
	gnudatafile << messageCounter << "\t"<< s1 << "\t" << rtt.count() << std::endl;
	return;
}

PrototypeFlpProcessor::~PrototypeFlpProcessor()
{
}
