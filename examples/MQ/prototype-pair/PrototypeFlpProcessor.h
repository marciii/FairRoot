/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/


#ifndef PROTOTYPEFLPPROCESSOR_H_
#define PROTOTYPEFLPPROCESSOR_H_

#include "FairMQDevice.h"
#include <unistd.h>

class PrototypeFlpProcessor : public FairMQDevice
{
  public:
    PrototypeFlpProcessor();
    virtual ~PrototypeFlpProcessor();

  protected:
    virtual void InitTask();
    bool HandleData(FairMQMessagePtr&, int);
    void write(std::string s1, std::string s2, pid_t s3);

  private:
    uint64_t fMaxIterations;
    uint64_t fNumIterations;
};

#endif /* PROTOTYPEFLPPROCESSOR_H_ */
