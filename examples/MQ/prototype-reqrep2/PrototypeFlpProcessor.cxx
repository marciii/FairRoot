/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * PrototypeFlpProcessor.cpp
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

using namespace std;

PrototypeFlpProcessor::PrototypeFlpProcessor()
    : fMaxIterations(0)
    , fNumIterations(0)
{
	OnData("scheduledata", &PrototypeFlpProcessor::HandleData);
}

void PrototypeFlpProcessor::InitTask()
{
    // Get the fMaxIterations value from the command line options (via fConfig)
    fMaxIterations = fConfig->GetValue<uint64_t>("max-iterations");
}

bool PrototypeFlpProcessor::HandleData(FairMQMessagePtr& request, int /*index*/)
{
    LOG(info) << "Empfange Nachricht von scheduler: \"" << string(static_cast<char*>(request->GetData()), request->GetSize()) << "\"";

  string* text = new string("bestaetigung, dass nachricht von scheduler ankam");

    LOG(info) << "Sende EPN Bestaetigung";

    FairMQMessagePtr reply(NewMessage(const_cast<char*>(text->c_str()), // data
                                                        text->length(), // size
                                                        [](void* /*data*/, void* object) { delete static_cast<string*>(object); }, // deletion callback
                                                        text)); // object that manages the data
	Send(reply, "scheduledata");

return true;
}

PrototypeFlpProcessor::~PrototypeFlpProcessor()
{
}
