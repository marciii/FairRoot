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
#include <sstream>

//times
#include <ctime>


using namespace std::chrono;
using namespace std;

long int sendCounter = 0;
int answerCounter = 0;
int flpAnswerId;


high_resolution_clock::time_point before;
high_resolution_clock::time_point after;

std::string msgSize;

std::stringstream result;

bool minMaxReset = true;

double* flpTimes;
double* flpRandomCounter;

// map <bin, count>
std::map<std::uint64_t, std::uint64_t> hist;
const std::uint64_t binSize = 5; // 100 micro secconds bin size; you can tune this
const double divSize = 1000; //1000 für cluster, 10000 für localhost

const int iterations = 20000;

struct MyMessage {
	uint64_t sendCounter;
	uint64_t replyId;
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
	msgAutoscale = fConfig->GetValue<bool>("msgAutoscale");
	scalingFlp = fConfig->GetValue<bool>("scalingFlp");

	flpTimes = new double[amountFlp];
	flpRandomCounter = new double[amountFlp];

}

void PrototypeSchedulerProcessor::Run()
{
	FairMQPollerPtr poller(NewPoller("sched-flp-chan"));
	while (CheckCurrentState(RUNNING))
  {


	sendCounter++;
	LOG(info) << "send counter " << sendCounter;

	if (sendCounter == 1302 && msgAutoscale == true) { // msg msgAutoscale

		if (randomReply == false) {

			LOG(info) << "am ende angelangt, schreibe";
			writeToFile(result.str());
		}
		else { //random reply = true
			for (int i=0; i<amountFlp; i++) {
				flpTimes[i] = flpTimes[i] / flpRandomCounter[i]; //durchschnitt berechnen
				result << i << "\t" << flpTimes[i] << std::endl;
			}
			LOG(info) << "am ende angelangt, schreibe";
			writeToFile(result.str());
		}
		delete [] flpTimes;
		delete [] flpRandomCounter;
		break;
		//return false;
	}

	if (sendCounter == iterations && scalingFlp == true) { //nur 100 messages pro Versuch
		average = average / (iterations - 1);
		result << amountFlp << "\t" << average << "\t" << min << "\t" << max << std::endl;
		result << std::endl;

		for (auto &h : hist) {
			//if (h.second/1000 > 0) {
			double tmp = ((h.first)*binSize + binSize/2.0)/divSize;
				result << tmp << "\t" << h.second << std::endl;
			//}
		}
		LOG(info) << "am ende angelangt, schreibe";
		writeToFile(result.str());

		delete [] flpTimes;
		delete [] flpRandomCounter;
		break;
		//return false;
	}

	int len = messageSize;

	//teil fuer message scaling
	if (msgAutoscale == true) {

		if (sendCounter == 101 || sendCounter == 201 || sendCounter == 301 || sendCounter == 401 || sendCounter == 501 ||
			sendCounter == 601 || sendCounter == 701 || sendCounter == 801 || sendCounter == 901 || sendCounter == 1001 ||
			sendCounter == 1101 || sendCounter == 1201 || sendCounter == 1301) {
				average = average / 100;
				result << msgSize << "\t" << average << "\t" << min << "\t" << max << std::endl;
				minMaxReset = true;
				average = 0;
			}
			len = calculateMessageSize(sendCounter);
		}



		MyMessage msgToFlp;
		msgToFlp.sendCounter = sendCounter;
		//generiert zufälligen wert wenn randomReply aktiviert ist, ansonsten 99999
		msgToFlp.replyId = getRandomAnswerId(randomReply);


		FairMQMessagePtr msg2[amountFlp];
		for (int i = 0; i < amountFlp; i++) {
			msg2[i] = NewMessage(len);

			//memcpy(msg2[i]->GetData(), const_cast<char*>(text->c_str()), msg2[i]->GetSize()); //bugged bei grosser message
			//memset(msg2[i]->GetData(), 'a', msg2[i]->GetSize()) ;

			memcpy(msg2[i]->GetData(), &msgToFlp, sizeof(MyMessage)) ;
		}

		msgSize = std::to_string(msg2[0]->GetSize());

		FairMQMessagePtr reply(NewMessage());



		LOG(info) << "starte zeitmessung";
		//Zeit starten
		before = high_resolution_clock::now();


		if (randomReply == false) {//Antwort von allen FLPs sammeln

			for (int i = 0; i < amountFlp; i++) {
				int test = Send(msg2[i], "sched-flp-chan", i);
				if (test < 0 ) {
					LOG(error) << "fail index " << i;
					//return false;
					break;
				}
			}

			for (int i = 0; i < amountFlp; i++) {

				//while (true) {
					//poller->Poll(1000);
					//if (poller->CheckInput("sched-flp-chan", i)) {


						if (Receive(reply, "sched-flp-chan", i) > 0) {

							LOG(info) << "Empfange von FLP: " << i;
							answerCounter++;

							if (answerCounter == amountFlp) { //alle haben geantwortet, timer stoppen -> gilt für RTT
								after = high_resolution_clock::now();
								duration<double> dur = duration_cast<duration<double>>(after - before);


								LOG(info) << "bestätigung von allen " << amountFlp << " bekommen, dauer insgesamt: " << dur.count();
								LOG(info) << "bin: " << (dur.count() * 1000) / binSize;


								hist[(dur.count() * divSize) / binSize]++; //10000 für localhost, 1000 für cluster

								answerCounter	= 0;

								if (sendCounter==1 || minMaxReset==true) { //erste nachricht, min und max festlegen
									min = dur.count();
									max = dur.count();
									minMaxReset = false;
								}


								average += dur.count();
								if (dur.count() < min) min = dur.count();
								if (dur.count() > max) max = dur.count();

							}
							//break;
						}
						else LOG(error) << "fail";
					//} //ende if poller
				//} //ende while

			} //ende for

		}
		else { //randomReply = true

			for (int i = 0; i < amountFlp; i++) {

				int test = Send(msg2[i], "sched-flp-chan", i);
				if (test < 0 ) {
					LOG(error) << "fail index " << i;
					//return false;
					break;
				}

			}


			if (Receive(reply, "sched-flp-chan", flpAnswerId) > 0) {
				LOG(info) << "bestätigung von flp " << flpAnswerId << " erhalten";
				after = high_resolution_clock::now();
				duration<double> dur = duration_cast<duration<double>>(after - before);
				//average+= dur.count();
				flpTimes[flpAnswerId] += dur.count();
				flpRandomCounter[flpAnswerId]++;

			}
		}

		this_thread::sleep_for(chrono::milliseconds(msgFreq));

		//return true;
	}
	}


	bool PrototypeSchedulerProcessor::HandleData(FairMQMessagePtr& msg, int index)
	{

		//index ist hier der index der EPN's
		LOG(info) << "Empfange Daten von EPN " << index;



		return true;
	}

	void PrototypeSchedulerProcessor::writeToFile(std::string text)
	{
		std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
		gnudatafile << text;
		return;
	}


	int PrototypeSchedulerProcessor::calculateMessageSize(int counter) {
		int len;

		if (counter <= 100) len = 4096; //4kb
		else if (counter <= 200) len = 8192; //8kb
		else if (counter <= 300) len = 16384; //16kb
		else if (counter <= 400) len = 32768; //32kb
		else if (counter <= 500) len = 65536; //64kb
		else if (counter <= 600) len = 131072; //128kb
		else if (counter <= 700) len = 262144; //256kb
		else if (counter <= 800) len = 524288; //512kb
		else if (counter <= 900) len = 1048576; //1024kb, 1mb
		else if (counter <= 1000) len = 2097152; //2048kb, 2mb
		else if (counter <= 1100) len = 4194304; //4096kb, 4mb
		else if (counter <= 1200) len = 8388608; //8192kb, 8mb
		else if (counter <= 1300) len = 16777216; //16384kb, 16mb
		return len;
	}

	uint64_t PrototypeSchedulerProcessor::getRandomAnswerId(bool randomAnswer) {
		if (randomAnswer == true) { //eine reply in MyMessage ID zwischen 1.. #FLPs auswählen
			//teil für random id -> statistik
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_int_distribution<> distribution(0, amountFlp-1);
			flpAnswerId = distribution(eng); //creates the random variable in the range of 1 and amountFlp

			LOG(info) << "FLP " << flpAnswerId << " soll antworten";
			return flpAnswerId;

		} else { // keine random ID -> in MyMessage reply ID auf -1 setzen
			//wenn alle antworten sollen -> -1
			return 99999;
		}
	}

	PrototypeSchedulerProcessor::~PrototypeSchedulerProcessor()
	{
	}
