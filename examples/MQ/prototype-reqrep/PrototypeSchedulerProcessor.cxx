/********************************************************************************
*    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
*                                                                              *
*              This software is distributed under the terms of the             *
*              GNU Lesser General Public Licence (LGPL) version 3,             *
*                  copied verbatim in the file "LICENSE"                       *
********************************************************************************/
/**
* PrototypeSchedulerProcessor.cxx
*
* @since 2014-10-10
* @author A. Rybalchenko
*/

#include "PrototypeSchedulerProcessor.h"
#include "FairMQLogger.h"
#include "FairMQProgOptions.h" // device->fConfig
#include <stdlib.h>
#include <random>

#include <string>
#include <sstream>
//times
#include <ctime>


using namespace std::chrono;
using namespace std;

int size = 1;
int sendCounter = 0; //0
int currentMessage = 1;
int flpReceived = 0;


int bestaetigungReceived = 0;

high_resolution_clock::time_point before;
high_resolution_clock::time_point after;

std::string msgSize;
int flpAnswerId;

std::stringstream result;

bool minMaxReset = false;

struct MyMessage {
  uint64_t sendCounter;
  uint64_t replyId;
  uint64_t flpId;
  uint64_t frequency;
  uint64_t numberFlp;
  uint64_t numberMessages;
  bool confirmation;
};


PrototypeSchedulerProcessor::PrototypeSchedulerProcessor()
{
  //OnData("epndata", &PrototypeSchedulerProcessor::HandleData);
  //OnData("scheduledata", &PrototypeSchedulerProcessor::HandleData2);
}


void PrototypeSchedulerProcessor::InitTask()
{
  logDir = fConfig->GetValue<std::string>("logDir");
  messageSize = fConfig->GetValue<uint64_t>("messageSize");
  randomReply = fConfig->GetValue<bool>("randomReply");
  msgFreq = fConfig->GetValue<uint64_t>("msgFreq");  amountFlp = fConfig->GetValue<uint64_t>("amountFlp");
  msgAutoscale = fConfig->GetValue<bool>("msgAutoscale");
  scalingFlp = fConfig->GetValue<bool>("scalingFlp");

  this_thread::sleep_for(chrono::seconds(3));
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
		double min_abweichung = average - min;
		double max_abweichung = max - average;

		result << amountFlp << "\t" << average << "\t" << min_abweichung << "\t" << max_abweichung << std::endl;
    LOG(info) << "am ende angelangt, schreibe";
    writeToFile(result.str());
    return false;
  }

  //kurze Nachricht an EPN, nur um Kommunikation zu überprüfen
  //  FairMQMessagePtr testMsg(NewSimpleMessage("OK"));
  //Send(testMsg, "scheduledatafromepn");


  int len = messageSize;

  //teil fuer message scaling
  if (msgAutoscale == true) {

    if (sendCounter == 101 || sendCounter == 201 || sendCounter == 301 || sendCounter == 401 || sendCounter == 501 ||
      sendCounter == 601 || sendCounter == 701 || sendCounter == 801 || sendCounter == 901 || sendCounter == 1001 ||
      sendCounter == 1101 || sendCounter == 1201 || sendCounter == 1301) {
        average = average / 100;
        double min_abweichung = average - min;
				double max_abweichung = max - average;

				result << amountFlp << "\t" << average << "\t" << min_abweichung << "\t" << max_abweichung << std::endl;
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
      for (int i=0;i<amountFlp;i++) {
        int test = Send(msg2, "scheduledata", i);
        if (test < 0 ) {
          LOG(error) << "fail";
          return false;
        }

        if (Receive(reply, "scheduledata", i) >= 0) {

          LOG(info) << "Empfange von FLP: " << i;
          bestaetigungReceived++;

          if (bestaetigungReceived == amountFlp) { //alle haben geantwortet, timer stoppen -> gilt für RTT
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


            bestaetigungReceived=0;
            //return true;
          }
        }
      }

    }

    else { //randomReply = true
      for (int i=0;i<amountFlp;i++) {
        int test = Send(msg2, "scheduledatatoflp", i);
        if (test < 0 ) {
          LOG(error) << "fail";
          return false;
        }

        if (Receive(reply, "answerfromflp", i) > 0) {
          LOG(info) << "bestätigung von flp erhalten";
          after = high_resolution_clock::now();
          duration<double> dur = duration_cast<duration<double>>(after - before);

          result << flpAnswerId << "\t" << dur.count() << std::endl;
        }
      }
    }



    this_thread::sleep_for(chrono::milliseconds(msgFreq));

    return true;
  }



  /*
  bool PrototypeSchedulerProcessor::HandleData(FairMQMessagePtr& request, int index) //EPN data
  {

  //LOG(info) << "Received request from client: \"" << string(static_cast<char*>(request->GetData()), request->GetSize()) << "\"";

  string* text = new string("bestaetigung");

  //LOG(info) << "Sende EPN Bestaetigung";

  FairMQMessagePtr reply(NewMessage(const_cast<char*>(text->c_str()), // data
  text->length(), // size
  [](void* data, void* object) { delete static_cast<string*>(object); }, // deletion callback
  text)); // object that manages the data

  if (Send(reply, "epndata") > 0)
  {

  return true;
}

return false;
}
*/

/*
bool PrototypeSchedulerProcessor::HandleData2(FairMQMessagePtr& request, int index) //FLP data, alias Schrit 2)
{



if (sendCounter ==  1500) { //
LOG(info) << "am ende angelangt, schreibe";
writeToFile(result.str());
return false;
}

if (sendCounter == 150 && scalingFlp == true) { //nur 100 messages pro Versuch
LOG(info) << "am ende angelangt, schreibe";
writeToFile(result.str());
return false;
}
int len = messageSize;


//teil fuer message scaling



MyMessage receivedMsg;
// make sure the msg is large enough to hold the data
assert(request->GetSize() >= sizeof(MyMessage));
memcpy(&receivedMsg, request->GetData(), sizeof(MyMessage));


if (receivedMsg.confirmation == false) { // 2) erster request also
requestReceived++;
if (requestReceived == 1) {
before = high_resolution_clock::now(); //timer NUR beim ersten request starten
//damit er nicht bei jedem request neu startet
sendCounter++;//hier die versendeten nachrichten zählen
getRandomAnswerId(randomReply); //auch hier nur einmal die Funktion, damit diese nicht x mal aufgerufen wird
}
if (requestReceived == amountFlp) {
requestReceived = 0; //zaehler zurücksetzen
}

//hier die eigentliche (große) Nachricht
if (msgAutoscale == true) {
len = calculateMessageSize(sendCounter);
}

MyMessage msgToFlp;
msgToFlp.sendCounter = sendCounter;
//generiert zufälligen wert wenn randomReply aktiviert ist, ansonsten 99999
msgToFlp.replyId = flpAnswerId;
msgToFlp.frequency = msgFreq;
msgToFlp.numberFlp = amountFlp;
if (scalingFlp)
msgToFlp.numberMessages = 100;
else
msgToFlp.numberMessages = 1299;

FairMQMessagePtr reply = NewMessage(len);
memcpy(reply->GetData(), &msgToFlp, sizeof(MyMessage));
msgSize = std::to_string(reply->GetSize());
if (Send(reply, "scheduledata") > 0) // 3)
return true;
else
return false;
}
else if (receivedMsg.confirmation == true) { // 6)
bestaetigungReceived++;
LOG(info) << "empfange bestätigung von flp " << receivedMsg.flpId;

if (randomReply == true) {
if (receivedMsg.flpId == flpAnswerId) {
//für randomReply - wenn bestätigung ankam
LOG(info) << "bestätigung von " << flpAnswerId << " erhalten";
after = high_resolution_clock::now();
duration<double> dur = duration_cast<duration<double>>(after - before);
result << flpAnswerId << "\t" << dur.count() << std::endl;
}
FairMQMessagePtr step7 = NewMessage(1);
if (Send(step7, "scheduledata") > 0 ) // 7)
return true;
else
return false;
}
else if (randomReply == false) {
if (bestaetigungReceived == amountFlp) {
LOG(info) << "alle bestätigungen erhalten";
bestaetigungReceived = 0;
after = high_resolution_clock::now();
duration<double> dur = duration_cast<duration<double>>(after - before);
if (scalingFlp) {
//write(amountFlp, dur); //für skalierende #flps
result << amountFlp << "\t" << dur.count() << std::endl;
}
else {
//write(msgSize, dur); //teil für skalierende msg size
result << msgSize << "\t" << dur.count() << std::endl;
}
}
FairMQMessagePtr step7 = NewMessage(1);
if (Send(step7, "scheduledata") > 0 ) // 7)
return true;
else
return false;
}
}
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
