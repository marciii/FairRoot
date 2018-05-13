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
	("logDir", bpo::value<std::string>()->default_value(""), "Output directory for the txt files")
	("messageSize", bpo::value<uint64_t>()->default_value(100), "message size")
	("randomReply", bpo::value<bool>()->default_value(false), "wether a random FLP answers to get a statistics or not") 
	("msgFreq", bpo::value<uint64_t>()->default_value(1000), "frequency of the messages in ms")
	("amountFlp", bpo::value<uint64_t>()->default_value(1), "amount of FLPs");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new PrototypeSchedulerProcessor();
}
