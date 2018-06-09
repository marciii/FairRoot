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
#include <ctime>


using namespace std::chrono;

class PrototypeSchedulerProcessor : public FairMQDevice
{
  public:
    PrototypeSchedulerProcessor();
    virtual ~PrototypeSchedulerProcessor();

  protected:
    bool HandleData(FairMQMessagePtr&, int);
	bool HandleFlpData(FairMQMessagePtr&, int);
void write(int amountFlp, duration<double>dur);
void write(std::string msgSize, duration<double>dur);

virtual void InitTask();
virtual bool ConditionalRun();

std::string logDir;
uint64_t messageSize;
bool randomReply;
uint64_t msgFreq;
uint64_t amountFlp;
bool msgAutoscale;
bool scalingFlp;
bool rtt;
int calculateMessageSize(int counter);
uint64_t getRandomAnswerId(bool randomAnswer);

};

#endif /* PROTOTYPESCHEDULERPROCESSOR_H_ */
