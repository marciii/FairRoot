/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef PROTOTYPESCHEDULERPROCESSOR_H_
#define PROTOTYPESCHEDULERPROCESSOR_H_

#include "FairMQDevice.h"

class PrototypeSchedulerProcessor : public FairMQDevice
{
  public:
    PrototypeSchedulerProcessor();
    virtual ~PrototypeSchedulerProcessor();

  protected:
    bool HandleData(FairMQMessagePtr&, int);
};

#endif /* PROTOTYPESCHEDULERPROCESSOR_H_ */
