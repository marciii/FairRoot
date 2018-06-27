/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runFairMQDevice.h"
#include "PrototypeFlpProcessor.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
        ("myId", bpo::value<uint64_t>()->default_value(0), "gives the FLP his id (for the random reply)");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new PrototypeFlpProcessor();
}
