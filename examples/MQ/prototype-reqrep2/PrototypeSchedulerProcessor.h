/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExample5Server.h
 *
 * @since 2014-10-10
 * @author A. Rybalchenko
 */

#ifndef PROTOTYPESCHEDULERPROCESSOR_H_
#define PROTOTYPESCHEDULERPROCESSOR_H_

#include "FairMQDevice.h"

class PrototypeSchedulerProcessor : public FairMQDevice
{
  public:
    PrototypeSchedulerProcessor();
    virtual ~PrototypeSchedulerProcessor();

  protected:
    virtual void InitTask();
    bool HandleData(FairMQMessagePtr&, int);

  private:
    uint64_t fMaxIterations;
    uint64_t fNumIterations;
};

#endif /* PROTOTYPESCHEDULERPROCESSOR_H_ */
