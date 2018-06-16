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


high_resolution_clock::time_point before;
high_resolution_clock::time_point after;

int sendCounter = 0;
int answerCounter = 0;

std::string msgSize;
int flpAnswerId;

std::stringstream result;

bool minMaxReset = false;

struct MyMessage {
  uint64_t sendCounter;
  uint64_t replyId;
};

PrototypeSchedulerProcessor::PrototypeSchedulerProcessor()
{
  //OnData("scheduledatafromepn", &PrototypeSchedulerProcessor::HandleData);
  //OnData("answerfromflp", &PrototypeSchedulerProcessor::HandleFlpData);
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

  this_thread::sleep_for(chrono::seconds(10));
}


bool PrototypeSchedulerProcessor::ConditionalRun()
{

  sendCounter++;

  if (sendCounter ==  1302) { //
    LOG(info) << "am ende angelangt, schreibe";
    writeToFile(result.str());
    return false;
  }

  if (sendCounter == 100 && scalingFlp == true) { //nur 100 messages pro Versuch
    average = average / 99;
		//double min_abweichung = average - min;
		//double max_abweichung = max - average;

		//result << amountFlp << "\t" << average << "\t" << min_abweichung << "\t" << max_abweichung << std::endl;
    result << amountFlp << "\t" << average << "\t" << min << "\t" << max << std::endl;
		LOG(info) << "am ende angelangt, schreibe";
		writeToFile(result.str());
		return false;
	}

  //kurze Nachricht an EPN, nur um Kommunikation zu überprüfen
  FairMQMessagePtr testMsg(NewSimpleMessage("OK"));
  Send(testMsg, "scheduledatafromepn");


  int len = messageSize;

  //teil fuer message scaling
  if (msgAutoscale == true) {
    if (sendCounter == 101 || sendCounter == 201 || sendCounter == 301 || sendCounter == 401 || sendCounter == 501 ||
      sendCounter == 601 || sendCounter == 701 || sendCounter == 801 || sendCounter == 901 || sendCounter == 1001 ||
      sendCounter == 1101 || sendCounter == 1201 || sendCounter == 1301) {
        average = average / 100;
        //double min_abweichung = average - min;
				//double max_abweichung = max - average;

				//result << msgSize << "\t" << average << "\t" << min_abweichung << "\t" << max_abweichung << std::endl;
        result << msgSize << "\t" << average << "\t" << min << "\t" << max << std::endl;
        minMaxReset = true;
      }
    len = calculateMessageSize(sendCounter);
  }


  MyMessage msgToFlp;
  msgToFlp.sendCounter = sendCounter;
  //generiert zufälligen wert wenn randomReply aktiviert ist, ansonsten 99999
  msgToFlp.replyId = getRandomAnswerId(randomReply);

  FairMQMessagePtr msg2 = NewMessage(len);

  // memset(msg2->GetData(), 'a', msg2->GetSize());
  memcpy(msg2->GetData(), &msgToFlp, sizeof(MyMessage));


  msgSize = std::to_string(msg2->GetSize());


  //Zeit starten
  //high_resolution_clock::time_point before = high_resolution_clock::now();
  FairMQMessagePtr reply(NewMessage());

  before = high_resolution_clock::now();




  if (randomReply == false) {
    int test = Send(msg2, "scheduledatatoflp");
    if (test < 0 ) {
      LOG(error) << "fail";
      return false;
    }


    for (int i = 0; i < amountFlp; i++) {

      if (Receive(reply, "answerfromflp", i) >= 0) {

        LOG(info) << "Empfange von FLP: \"";// << string(static_cast<char*>(reply->GetData()));


        if (i == amountFlp-1) { //alle haben geantwortet, timer stoppen -> gilt für RTT
          after = high_resolution_clock::now();
          duration<double> dur = duration_cast<duration<double>>(after - before);
          LOG(info) << "bestätigung von allen " << amountFlp << " bekommen";

          if (sendCounter==1 || minMaxReset==true) { //erste nachricht, min und max festlegen
            min = dur.count();
            max = dur.count();
            minMaxReset = false;
          }


            average += dur.count();
            if (dur.count() < min) min = dur.count();
            if (dur.count() > max) max = dur.count();

        }
        //return true;
      } else LOG(info) << "hier2";
    }
  }

  else { //randomReply = true
    int test = Send(msg2, "scheduledatatoflp");
    if (test < 0 ) {
      LOG(error) << "fail";
      return false;
    }

    if (Receive(reply, "answerfromflp", flpAnswerId) > 0) {
      LOG(info) << "bestätigung von flp " << flpAnswerId << " erhalten";
      after = high_resolution_clock::now();
      duration<double> dur = duration_cast<duration<double>>(after - before);

      result << flpAnswerId << "\t" << dur.count() << std::endl;
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
bool PrototypeSchedulerProcessor::HandleFlpData(FairMQMessagePtr& msg, int index) //bestätigung von FLP (für RTT)
{
//string* text = new std::string(static_cast<char*>(msg->GetData()));
LOG(info) << "Empfange Antwort von FLP: " << msg->GetData();
answerCounter++;
if (answerCounter == amountFlp) {//Bestätigung von allen erreicht
LOG(info) << "alle " << amountFlp << " antworten erhalten, schreibe";
high_resolution_clock::time_point after = high_resolution_clock::now();
duration<double> dur = duration_cast<duration<double>>(after - before);
answerCounter=0;
write(msgSize, dur);
}
return true;
}
*/


/*
bool PrototypeSchedulerProcessor::HandleData(FairMQMessagePtr& msg, int index)
{
counter++;
LOG(info) << "Empfange Daten von EPN";


if (counter > 50) {
LOG(info) << "am ende angelangt";
return false;
}

//hier liegt das Problem bei hohen werten

FairMQMessagePtr msg2(NewMessage(len));

LOG(info) <<"hier1";
LOG(info) << msg2->GetSize() ;
memset(msg2->GetData(), 'a', msg2->GetSize()) ;
//memcpy(msg2->GetData(), const_cast<char*>(text->c_str()), msg2->GetSize());
LOG(info) <<"hier2";




// Send out the output message
LOG(info) <<"Leite weiter an FLP";

msgSize = std::to_string(msg2->GetSize());
before = high_resolution_clock::now();
if (Send(msg2, "scheduledatatoflp") < 0)
{
return false;
}
//high_resolution_clock::time_point after = high_resolution_clock::now();
//duration<double> dur = duration_cast<duration<double>>(after - before);
//(write(amountFlp, dur);
//write(msgSize, dur);
//counter++;
//delete text;
return true;
}
*/
void PrototypeSchedulerProcessor::writeToFile(std::string text)
{
	std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
	gnudatafile << text;
	return;
}
/*
void PrototypeSchedulerProcessor::write(int amountFlp, duration<double>dur)
{
  std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
  gnudatafile << amountFlp << "\t" << dur.count() << std::endl;
  return;
}

void PrototypeSchedulerProcessor::write(std::string s1, duration<double> dur)
{
  std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
  gnudatafile << s1 << "\t" << dur.count() << std::endl;
  return;
}
*/

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
