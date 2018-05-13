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
{
    OnData("scheduledatatoflp", &PrototypeFlpProcessor::HandleData);
}

void PrototypeFlpProcessor::InitTask()
{
  myId = fConfig->GetValue<uint64_t>("myId");
}


bool PrototypeFlpProcessor::HandleData(FairMQMessagePtr& msg, int /*index*/)
{
    //LOG(info) << "Empfange von scheduler, groesse: \"" << std::to_string(msg->GetSize()) << "\"";

	LOG(info) << "antworrt erhalten";
    string* text = new string("answer from FLP");

   FairMQMessagePtr answer(NewMessage(const_cast<char*>(text->c_str()),
                                    text->length(),
                                    [](void* /*data*/, void* object) { delete static_cast<string*>(object); },
                                    text));

	if (Send(answer, "answerfromflp") < 0) 
	{
		LOG(error) << "fail";
		return false;
	}

	  
      
  
    return true;
}

PrototypeFlpProcessor::~PrototypeFlpProcessor()
{
}
