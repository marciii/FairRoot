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
#include <ctime>


using namespace std::chrono;


class PrototypeSchedulerProcessor : public FairMQDevice
{
  public:
    PrototypeSchedulerProcessor();
    virtual ~PrototypeSchedulerProcessor();

  protected:
    virtual void InitTask();
    bool HandleData(FairMQMessagePtr&, int);
bool HandleData2(FairMQMessagePtr&, int);
void write(int amountFlp, duration<double>dur);
void write(std::string msgSize, duration<double>dur);



  private:
  std::string logDir;
uint64_t messageSize;
bool randomReply;
uint64_t msgFreq;
uint64_t amountFlp;
bool msgAutoscale;
};

#endif /* PROTOTYPESCHEDULERPROCESSOR_H_ */
