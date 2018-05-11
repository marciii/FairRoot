/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "PrototypeSchedulerProcessor.h"
#include "FairMQLogger.h"
#include "FairMQProgOptions.h"
#include <stdlib.h>  

#include <random>

#include <string>

//times
#include <ctime>


using namespace std::chrono;
using namespace std;

int receiveCounter = 0;
int answerCounter = 0;

high_resolution_clock::time_point before;
high_resolution_clock::time_point after;

std::string msgSize;

PrototypeSchedulerProcessor::PrototypeSchedulerProcessor()
{
	
	
    OnData("scheduledatafromepn", &PrototypeSchedulerProcessor::HandleData);
	OnData("scheduledatatoflp", &PrototypeSchedulerProcessor::HandleFlpData);
} 


void PrototypeSchedulerProcessor::InitTask()
{
    amountFlp = fConfig->GetValue<uint64_t>("amountFlp");
	LOG(info) << "amount flp: " << amountFlp;
}

bool PrototypeSchedulerProcessor::HandleFlpData(FairMQMessagePtr& msg, int index)
{



	//index ist hier der index der EPN's
    LOG(info) << "Empfange Daten von FLP " <<index << " nachricht: " << string(static_cast<char*>(msg->GetData()));
	answerCounter++;
	
	if (answerCounter == amountFlp) { //alle haben geantwortet, timer stoppen -> gilt für RTT
		after = high_resolution_clock::now();
		duration<double> dur = duration_cast<duration<double>>(after - before);
		LOG(info) << "bestätigung von allen " << amountFlp <<" bekommen, schreibe";
		//write(amountFlp, dur); //für skalierende #flps
		write(msgSize, dur);
		answerCounter=0;
	}
	
	return true;

}

bool PrototypeSchedulerProcessor::HandleData(FairMQMessagePtr& msg, int index)
{

	//index ist hier der index der EPN's
    LOG(info) << "Empfange Daten von EPN " <<index;

	high_resolution_clock::time_point test1 = high_resolution_clock::now();
	


   // string* text = new std::string(static_cast<char*>(msg->GetData()), msg->GetSize());

receiveCounter++;
if (receiveCounter > 50) { //
LOG(info) << "am ende angelangt"; 
return false; }

//genau 1024 chars --> genau 1 kB
string* text = new string("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
int len = 1024;

//4096 bytes -> 4kb
*text = *text + *text + *text + *text;
len = 4096;

//8192 bytes -> 8kb
*text = *text + *text;
len = 8192;

//16384 bytes -> 16kb
*text  = *text + *text;
len = 16384;

//32768 bytes -> 32kb
*text = *text + *text;
len = 32768;

//65536 bytes -> 64kb
*text = *text + *text;
len = 65536;

//131072 bytes -> 128kb
*text = *text + *text;
len = 131072;

//262144 bytes -> 256kb
*text = *text + *text;
len = 262144;


// -- hier schluss bei 20 FLPs

//524288 bytes -> 512kb
//*text = *text + *text;
//len = 524288;

//1048576 bytes -> 1024kb, 1mb
//*text = *text + *text;
//len = 1048576;

//2097152 bytes -> 2048kb, 2mb
//*text = *text + *text;
//len = 2097152;

//4194304 bytes -> 4096kb, 4mb
//*text = *text + *text;
//len = 4194304;

//8388608 bytes -> 8192kb, 8mb
//*text = *text + *text;
//len = 8388608;

//16777216 bytes -> 16384kb, 16mb
//*text = *text + *text;
//len = 16777216;

/*
//teil für random id -> statistik
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distribution(0, amountFlp);
int flpAnswerId = distribution(eng); //creates the random variable in the range of 0 and amountFlp

LOG(info) << "FLP " << flpAnswerId << " soll antworten";
//the first 4 characters will be the ID
if (flpAnswerId <= 9)
	*text = "000" + std::to_string(flpAnswerId) + "|" + *text;
else if (flpAnswerId <= 99)
	*text = "00" + std::to_string(flpAnswerId) + "|" + *text;
else if (flpAnswerId <= 999)
	*text = "0" + std::to_string(flpAnswerId) + "|" + *text;
else
	*text = std::to_string(flpAnswerId) + "|" + *text;
*/





//FairMQMessagePtr reply(NewMessage(len));
FairMQMessagePtr msg2[amountFlp];
for (int i=0;i<amountFlp;i++) {
	msg2[i] = NewMessage(len);
	memcpy(msg2[i]->GetData(), const_cast<char*>(text->c_str()), msg2[i]->GetSize());

}

msgSize = std::to_string(msg2[0]->GetSize());

 //string* text[3];
//text[0] = new std::string(static_cast<char*>("0", msg->GetData()), msg->GetSize());
//text[1] = new std::string(static_cast<char*>(msg->GetData()), msg->GetSize());
//text[2] = new std::string(static_cast<char*>(msg->GetData()), msg->GetSize());




    // Send out the output message
    LOG(info) <<"Empfange von EPN: " << msg->GetSize();

	//Zeit starten
//high_resolution_clock::time_point before = high_resolution_clock::now(); 
before = high_resolution_clock::now(); 

    for (int i=0;i<amountFlp;i++) {
	   	 LOG(info) <<"Leite weiter an FLP " << i;

		int test = Send(msg2[i], "scheduledatatoflp", i);
		if (test < 0 ) 
			{ LOG(error) << "fail index " << i;
			return false; }
		else 
			{ LOG(info) << test; }
	}
	//hier an alle weitergeleitet -> Zeit stoppen
	//high_resolution_clock::time_point after = high_resolution_clock::now();
	
	//duration<double> dur = duration_cast<duration<double>>(after - before);
	//LOG(info) << "an alle 5 gesendet, schreibe";
	//write(5, dur); //für skalierende #flps
	//write(msgSize, dur);
    return true;
}

void PrototypeSchedulerProcessor::write(int amountFlp, duration<double>dur) {
	std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
	gnudatafile << amountFlp << "\t" << dur.count() << std::endl;
	return;
}
void PrototypeSchedulerProcessor::write(std::string msgSize, duration<double>dur) {
	std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
	gnudatafile << msgSize << "\t" << dur.count() << std::endl;
	return;
}


PrototypeSchedulerProcessor::~PrototypeSchedulerProcessor()
{
}
