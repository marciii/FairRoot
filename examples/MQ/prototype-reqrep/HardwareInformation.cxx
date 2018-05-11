/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/



#include "HardwareInformation.h"

#include <string>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

using namespace std;

static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;

HardwareInformation::HardwareInformation()
{
}

double HardwareInformation::getCpuUsage()
{
    double percent;
       FILE* file;
       unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

       file = fopen("/proc/stat", "r");
       fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
           &totalSys, &totalIdle);
       fclose(file);

       if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
           totalSys < lastTotalSys || totalIdle < lastTotalIdle){
           //Overflow detection. Just skip this value.
           percent = -1.0;
       }
       else{
           total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
               (totalSys - lastTotalSys);
           percent = total;
           total += (totalIdle - lastTotalIdle);
           percent /= total;
           percent *= 100;
       }

       lastTotalUser = totalUser;
       lastTotalUserLow = totalUserLow;
       lastTotalSys = totalSys;
       lastTotalIdle = totalIdle;

       return percent;
}

double HardwareInformation::getRamUsage()
{
    //collect information about (physical) ram
    struct sysinfo memInfo;


    sysinfo (&memInfo);
    long long totalVirtualMem = memInfo.totalram;

    //total virtual memory
    totalVirtualMem += memInfo.totalswap;
    totalVirtualMem *= memInfo.mem_unit;

    //total physical memory (ram)
    long long totalPhysMem = memInfo.totalram;
    //Multiply in next statement to avoid int overflow on right hand side...
    totalPhysMem *= memInfo.mem_unit;

    //physical memory currently used
    long long physMemUsed = memInfo.totalram - memInfo.freeram;
    //Multiply in next statement to avoid int overflow on right hand side...
    physMemUsed *= memInfo.mem_unit;

    long double memUsed = physMemUsed / 10000000.; //convert to double
    long double total = totalPhysMem / 10000000.;
    long double percentPhysical = (memUsed/total) * 100;


    //virtual memory used
    long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
    //Add other values in next statement to avoid int overflow on right hand side...
    virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
    virtualMemUsed *= memInfo.mem_unit;
    long double virtualTotal = totalVirtualMem / 10000000.;
    long double virtualUsed = virtualMemUsed / 10000000.;
    long double percentVirtual = (virtualUsed/virtualTotal) * 100;

    //return percentPhysical;
    return percentVirtual;
}

HardwareInformation::~HardwareInformation()
{
}
