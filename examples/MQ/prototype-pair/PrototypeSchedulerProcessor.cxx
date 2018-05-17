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

int sendCounter = 0;
int answerCounter = 0;

high_resolution_clock::time_point before;
high_resolution_clock::time_point after;

std::string msgSize;
int flpAnswerId;

struct MyMessage {
	uint64_t sendCounter;
	uint64_t replyId;
	// std::string content;
};


PrototypeSchedulerProcessor::PrototypeSchedulerProcessor()
{


	//OnData("scheduledatafromepn", &PrototypeSchedulerProcessor::HandleData);
	//OnData("scheduledatatoflp", &PrototypeSchedulerProcessor::HandleFlpData);
}


void PrototypeSchedulerProcessor::InitTask()
{
	logDir = fConfig->GetValue<std::string>("logDir");
	messageSize = fConfig->GetValue<uint64_t>("messageSize");
	randomReply = fConfig->GetValue<bool>("randomReply");
	msgFreq = fConfig->GetValue<uint64_t>("msgFreq");
	amountFlp = fConfig->GetValue<uint64_t>("amountFlp");

}

bool PrototypeSchedulerProcessor::ConditionalRun()
{

	sendCounter++;
	if (sendCounter > 50) { //
		LOG(info) << "am ende angelangt";
		return false;
	}


	int len = messageSize;


	MyMessage msgToFlp;
	msgToFlp.sendCounter = sendCounter;
	//wenn alle antworten sollen -> -1
	//msgToFlp.content = *text;
	// msgToFlp.content = "asdf";


	if (randomReply == true) { //eine reply in MyMessage ID zwischen 1.. #FLPs auswählen

//teil für random id -> statistik
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distribution(1, amountFlp);
		flpAnswerId = distribution(eng); //creates the random variable in the range of 1 and amountFlp

		LOG(info) << "FLP " << flpAnswerId << " soll antworten";
		msgToFlp.replyId = flpAnswerId;

	} else { // keine random ID -> in MyMessage reply ID auf -1 setzen
		msgToFlp.replyId = 99999;
	}







	FairMQMessagePtr msg2[amountFlp];
	for (int i = 0; i < amountFlp; i++) {

		msg2[i] = NewMessage(len);



		//memcpy(msg2[i]->GetData(), const_cast<char*>(text->c_str()), msg2[i]->GetSize()); //bugged bei grosser message
		//memset(msg2[i]->GetData(), 'a', msg2[i]->GetSize()) ;

		memcpy(msg2[i]->GetData(), &msgToFlp, sizeof(MyMessage)) ;

	}

	msgSize = std::to_string(msg2[0]->GetSize());



	//Zeit starten
	before = high_resolution_clock::now();

	answerCounter	= 0;

if (randomReply == false) { //Antwort von allen FLPs sammeln
	for (int i = 0; i < amountFlp; i++) {

		int test = Send(msg2[i], "scheduledatatoflp", i);
		if (test < 0 ) {
			LOG(error) << "fail index " << i;
			return false;
		}

		FairMQMessagePtr reply(NewMessage());

		if (Receive(reply, "scheduledatatoflp", i) > 0) {

			LOG(info) << "Empfange von FLP: \"";// << string(static_cast<char*>(reply->GetData()));
			answerCounter++;

			if (answerCounter == amountFlp) { //alle haben geantwortet, timer stoppen -> gilt für RTT
				after = high_resolution_clock::now();
				duration<double> dur = duration_cast<duration<double>>(after - before);
				LOG(info) << "bestätigung von allen " << amountFlp << " bekommen, schreibe";
				//write(amountFlp, dur); //für skalierende #flps
				write(msgSize, dur);
			}
		} else LOG(error) << "fail";

	}
}
else { //randomReply = true

	for (int i = 0; i < amountFlp; i++) {

		int test = Send(msg2[i], "scheduledatatoflp", i);
		if (test < 0 ) {
			LOG(error) << "fail index " << i;
			return false;
		}
	}

	FairMQMessagePtr reply(NewMessage());

	if (Receive(reply, "scheduledatatoflp", flpAnswerId -1) > 0) {
		LOG(info) << "bestätigung von flp " << flpAnswerId - 1  << " erhalten, schreibe";
		after = high_resolution_clock::now();
		duration<double> dur = duration_cast<duration<double>>(after - before);
		//write(amountFlp, dur); //für skalierende #flps
		write(msgSize, dur);
	}
}




	//hier an alle weitergeleitet -> Zeit stoppen
	//high_resolution_clock::time_point after = high_resolution_clock::now();

	//duration<double> dur = duration_cast<duration<double>>(after - before);
	//LOG(info) << "an alle 5 gesendet, schreibe";
	//write(5, dur); //für skalierende #flps
	//write(msgSize, dur);

	this_thread::sleep_for(chrono::milliseconds(msgFreq));

	return true;
}


/*
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

} */

bool PrototypeSchedulerProcessor::HandleData(FairMQMessagePtr& msg, int index)
{

	//index ist hier der index der EPN's
	LOG(info) << "Empfange Daten von EPN " << index;



	return true;
}


void PrototypeSchedulerProcessor::write(int amountFlp, duration<double>dur)
{
	std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
	gnudatafile << amountFlp << "\t" << dur.count() << std::endl;
	return;
}
void PrototypeSchedulerProcessor::write(std::string msgSize, duration<double>dur)
{
	std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
	gnudatafile << msgSize << "\t" << dur.count() << std::endl;
	return;
}


PrototypeSchedulerProcessor::~PrototypeSchedulerProcessor()
{
}
