/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExample1Sampler.cpp
 *
 * @since 2014-10-10
 * @author A. Rybalchenko
 */

#include <thread> // this_thread::sleep_for
#include <chrono>
#include <string>


#include "PrototypeEpnProcessor.h"
#include "FairMQLogger.h"
#include "FairMQProgOptions.h" // device->fConfig
#include "HardwareInformation.h"

using namespace std;

PrototypeEpnProcessor::PrototypeEpnProcessor()
{
	OnData("scheduledatafromepn", &PrototypeEpnProcessor::HandleData);
}

void PrototypeEpnProcessor::InitTask()
{
 
}

bool PrototypeEpnProcessor::HandleData(FairMQMessagePtr& msg, int /*index*/)
{

    LOG(info) << "Empfange Nachricht von FLP";

    return true;
}

PrototypeEpnProcessor::~PrototypeEpnProcessor()
{
}
