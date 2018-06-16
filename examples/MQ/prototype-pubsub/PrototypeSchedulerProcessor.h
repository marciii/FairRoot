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
using namespace std;

class PrototypeSchedulerProcessor : public FairMQDevice
{
public:
  PrototypeSchedulerProcessor();
  virtual ~PrototypeSchedulerProcessor();

protected:
  bool HandleData(FairMQMessagePtr&, int);
  bool HandleFlpData(FairMQMessagePtr&, int);
  //void write(std::string s1, duration<double> dur);
  //void write(int amountFlp, duration<double>dur);
  void writeToFile(std::string text);

  virtual void InitTask();
  virtual bool ConditionalRun();

  uint64_t getRandomAnswerId(bool randomAnswer);
  int calculateMessageSize(int counter);

  std::string logDir;
  uint64_t messageSize;
  bool randomReply;
  uint64_t msgFreq;
  uint64_t amountFlp;
  bool msgAutoscale;
  bool scalingFlp;

double min;
double max;
double median;
};

#endif /* PROTOTYPESCHEDULERPROCESSOR_H_ */
