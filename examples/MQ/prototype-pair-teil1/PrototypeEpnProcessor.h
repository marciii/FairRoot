/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExample1Sampler.h
 *
 * @since 2014-10-10
 * @author A. Rybalchenko
 */

#ifndef PROTOTYPEEPNPROCESSOR_H_
#define PROTOTYPEEPNPROCESSOR_H_

#include <string>

#include "FairMQDevice.h"

class PrototypeEpnProcessor : public FairMQDevice
{
  public:
    PrototypeEpnProcessor();
    virtual ~PrototypeEpnProcessor();

  protected:
    std::string fText;
    uint64_t fMaxIterations;
    uint64_t fNumIterations;

    virtual void InitTask();
    virtual bool ConditionalRun();
};

#endif /* PROTOTYPEEPNPROCESSOR_H_ */
