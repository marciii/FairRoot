/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExample5Client.h
 *
 * @since 2014-10-10
 * @author A. Rybalchenko
 */

#ifndef PROTOTYPEFLPPROESSOR_H_
#define PROTOTYPEFLPPROESSOR_H_

#include <string>
#include <ctime>



#include "FairMQDevice.h"
using namespace std::chrono;
class PrototypeFlpProcessor : public FairMQDevice
{
  public:
    PrototypeFlpProcessor();
    virtual ~PrototypeFlpProcessor();

  protected:

	

    //virtual bool ConditionalRun();
   virtual void InitTask();
	bool HandleData(FairMQMessagePtr& request, int index);
   void write(std::string s1, duration<double> rtt);
	void write(int messageCounter, std::string s1, duration<double> rtt);
};

#endif /* PROTOTYPEEPNPROESSOR_H_ */
