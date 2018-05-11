/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef HARDWAREINFORMATION_H_
#define HARDWAREINFORMATION_H_

#include <string>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

class HardwareInformation
{
  public:
    HardwareInformation();
    virtual ~HardwareInformation();

    double getCpuUsage();
    double getRamUsage();


};

#endif /* HARDWAREINFORMATION_H_ */
