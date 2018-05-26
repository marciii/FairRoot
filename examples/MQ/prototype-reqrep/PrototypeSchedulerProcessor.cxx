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

//times
#include <ctime>


using namespace std::chrono;
using namespace std;

int size = 1;
int sendCounter = 1; //0
int currentMessage = 1;
int flpReceived = 0;

int bestaetigungReceived = 0;

high_resolution_clock::time_point before;
high_resolution_clock::time_point after;

std::string msgSize;
int flpAnswerId;

struct MyMessage {
  uint64_t sendCounter;
  uint64_t replyId;
  bool confirmation;
};


PrototypeSchedulerProcessor::PrototypeSchedulerProcessor()
{
  OnData("epndata", &PrototypeSchedulerProcessor::HandleData);
  OnData("scheduledata", &PrototypeSchedulerProcessor::HandleData2);
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


  this_thread::sleep_for(chrono::seconds(3));
}

bool PrototypeSchedulerProcessor::HandleData(FairMQMessagePtr& request, int /*index*/) //EPN data
{

  //LOG(info) << "Received request from client: \"" << string(static_cast<char*>(request->GetData()), request->GetSize()) << "\"";

  string* text = new string("bestaetigung, dass nachricht ankam");

  //LOG(info) << "Sende EPN Bestaetigung";

  FairMQMessagePtr reply(NewMessage(const_cast<char*>(text->c_str()), // data
  text->length(), // size
  [](void* /*data*/, void* object) { delete static_cast<string*>(object); }, // deletion callback
  text)); // object that manages the data

  if (Send(reply, "epndata") > 0)
  {

    return true;
  }

  return false;
}
bool PrototypeSchedulerProcessor::HandleData2(FairMQMessagePtr& request, int /*index*/) //FLP data, alias Schrit 2)
{

  sendCounter++;
  int len = messageSize;


  //teil fuer message scaling
  if (msgAutoscale == true) {
    len = calculateMessageSize(sendCounter);
  }



  MyMessage receivedMsg;
  // make sure the msg is large enough to hold the data
  assert(request->GetSize() >= sizeof(MyMessage));
  memcpy(&receivedMsg, request->GetData(), sizeof(MyMessage));


  /*
  if (counter > 20) { //50 für plot: mit size und realtime dauer
  LOG(info) << "am ende angelangt";
  return false;
}*/
MyMessage msgToFlp;
msgToFlp.sendCounter = sendCounter;
//generiert zufälligen wert wenn randomReply aktiviert ist, ansonsten 99999
msgToFlp.replyId = getRandomAnswerId(randomReply);


FairMQMessagePtr reply = NewMessage(len);
FairMQMessagePtr reply2 = NewMessage(1);
memcpy(reply->GetData(), &msgToFlp, sizeof(MyMessage));


std::string msgSize = std::to_string(reply->GetSize());

MyMessage conf;

//high_resolution_clock::time_point before = high_resolution_clock::now(); //timer starten
before = high_resolution_clock::now();

if (Send(reply, "scheduledata") > 0) //3)
{
  if (Receive(reply2, "scheduledata") >=0) {//6
    memcpy(&conf, reply2->GetData(), sizeof(MyMessage));
    if (conf.confirmation == true) {
      LOG(info) << "empfange bestätigung: " << bestaetigungReceived;
      bestaetigungReceived++;
      //hier aufpassen, dass alle bestätitungen zur selben nachrichtenwellge gehören
      //dh falls eine antwort nicht empfangen wurde, wird nicht geschrieben
      if (bestaetigungReceived == amountFlp && currentMessage == conf.sendCounter) {
        LOG(info) << "alle bestätigungen erhalten, schreibe";
        after = high_resolution_clock::now();
        duration<double> dur = duration_cast<duration<double>>(after - before);
        if (scalingFlp) {
          write(amountFlp, dur); //für skalierende #flps
        }
        else {
          write(msgSize, dur); //teil für skalierende msg size
        }


        bestaetigungReceived = 0;
        currentMessage++; //wenn alle Bestätigungen erhalten wurde, Nahchrichtenzähler erhöhen
      }
      //hier beginnt dann nächste nachricht, ohne dass alle bestätigungen von der vorherigen gesammelt wurden
      //dh es wird nichts geschrieben
      else if (currentMessage != conf.sendCounter) {
        LOG(info) << "currentMessage " << currentMessage << "     conf.sendcounter " << conf.sendCounter;
        currentMessage = conf.sendCounter; //der aktuelle nachrichtenzähler wird auf diesen hier gesetzt
        bestaetigungReceived = 1;
        LOG(info) << "eine oder mehrere Bestätigungen nicht erhalten, schreibe die letzte Runde nicht mit";
      }
    }
    Send(reply2, "scheduledata"); //7
    return true;
  }


}
return false;
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
