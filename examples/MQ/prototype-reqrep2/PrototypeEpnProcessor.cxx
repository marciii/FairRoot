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

#include "PrototypeEpnProcessor.h"
#include "FairMQLogger.h"
#include "FairMQProgOptions.h"
#include "HardwareInformation.h"

using namespace std;

PrototypeEpnProcessor::PrototypeEpnProcessor()
    : fText()
    , fMaxIterations(0)
    , fNumIterations(0)
{
}

void PrototypeEpnProcessor::InitTask()
{
    fText = fConfig->GetValue<string>("text");
    fMaxIterations = fConfig->GetValue<uint64_t>("max-iterations");
}

bool PrototypeEpnProcessor::ConditionalRun()
{

    HardwareInformation* hwr = new HardwareInformation;
    double cpuUsage = hwr->getCpuUsage();
    double ramUsage = hwr->getRamUsage();

    string* text = new string("CPU usage: " + std::to_string(cpuUsage) + "% - RAM usage: " + std::to_string(ramUsage) + "%" + "\"");

    // create message object with a pointer to the data buffer,
    // its size,
    // custom deletion function (called when transfer is done),
    // and pointer to the object managing the data buffer
    FairMQMessagePtr request(NewMessage(const_cast<char*>(text->c_str()), // data
                                                          text->length(), // size
                                                          [](void* /*data*/, void* object) { delete static_cast<string*>(object); }, // deletion callback
                                                          text)); // object that manages the data
    FairMQMessagePtr reply(NewMessage());

    LOG(info) << "Sende an Scheduler:  \"" << *text << "\"";

    if (Send(request, "epndata") > 0)
    {
        if (Receive(reply, "epndata") >= 0)
        {
            LOG(info) << "Received reply from server: \"" << string(static_cast<char*>(reply->GetData()), reply->GetSize()) << "\"";

            if (fMaxIterations > 0 && ++fNumIterations >= fMaxIterations)
            {
                LOG(info) << "Configured maximum number of iterations reached. Leaving RUNNING state.";
                return false;
            }

            this_thread::sleep_for(chrono::seconds(1));

            return true;
        }
    }

    return false;
}

PrototypeEpnProcessor::~PrototypeEpnProcessor()
{
}
