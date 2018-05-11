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
}

// handler is called whenever a message arrives on "data", with a reference to the message and a sub-channel index (here 0)
bool PrototypeFlpProcessor::HandleData(FairMQMessagePtr& msg, int /*index*/)
{
    LOG(info) << "Empfange von scheduler, groesse: \"" << std::to_string(msg->GetSize()) << "\"";

    if (fMaxIterations > 0 && ++fNumIterations >= fMaxIterations)
    {
        LOG(info) << "Configured maximum number of iterations reached. Leaving RUNNING state.";
        return false;
    }
	
    string* text = new string("answer from FLP");

   FairMQMessagePtr answer(NewMessage(const_cast<char*>(text->c_str()),
                                    text->length(),
                                    [](void* /*data*/, void* object) { delete static_cast<string*>(object); },
                                    text));

	Send(answer, "answerfromflp");
	  
      
  
    return true;
}

PrototypeFlpProcessor::~PrototypeFlpProcessor()
{
}
