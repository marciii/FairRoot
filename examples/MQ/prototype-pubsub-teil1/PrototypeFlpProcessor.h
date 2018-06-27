/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExample1Sink.h
 *
 * @since 2014-10-10
 * @author A. Rybalchenko
 */

#ifndef PROTOTYPEFLPPROCESSOR_H_
#define PROTOTYPEFLPPROCESSOR_H_

#include "FairMQDevice.h"

class PrototypeFlpProcessor : public FairMQDevice
{
  public:
    PrototypeFlpProcessor();
    virtual ~PrototypeFlpProcessor();

  protected:
    virtual void InitTask();
    bool HandleData(FairMQMessagePtr&, int);
    // bool ConditionalRun();

  private:
    uint64_t myId;
};

#endif /* PROTOTYPEFLPPROCESSOR_H_ */
