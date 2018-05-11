/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runFairMQDevice.h"
#include "PrototypeSchedulerProcessor.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
	options.add_options()
	("amountFlp", bpo::value<uint64_t>()->default_value(1), "amount of FLPs");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new PrototypeSchedulerProcessor();
}
