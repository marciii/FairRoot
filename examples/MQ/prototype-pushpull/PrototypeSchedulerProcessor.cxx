/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "PrototypeSchedulerProcessor.h"
#include "FairMQLogger.h"

#include <string>

using namespace std;

PrototypeSchedulerProcessor::PrototypeSchedulerProcessor()
{
    OnData("scheduledatafromepn", &PrototypeSchedulerProcessor::HandleData);
}

bool PrototypeSchedulerProcessor::HandleData(FairMQMessagePtr& msg, int /*index*/)
{
    LOG(info) << "Empfange Daten von EPN";

    // Modify the received string
    string* text = new std::string(static_cast<char*>(msg->GetData()), msg->GetSize());
    //*text += " (modified by " + fId + ")";

    // create message object with a pointer to the data buffer,
    // its size,
    // custom deletion function (called when transfer is done),
    // and pointer to the object managing the data buffer
    FairMQMessagePtr msg2(NewMessage(const_cast<char*>(text->c_str()),
                                     text->length(),
                                     [](void* /*data*/, void* object) { delete static_cast<string*>(object); },
                                     text));

    // Send out the output message
    LOG(info) <<"Empfange von EPN: " + *text;
    LOG(info) <<"Leite weiter an FLP";
    if (Send(msg2, "scheduledatatoflp") < 0)
    {
        return false;
    }

    return true;
}

PrototypeSchedulerProcessor::~PrototypeSchedulerProcessor()
{
}
