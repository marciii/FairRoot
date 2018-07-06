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

bool minMaxReset = true;

double* flpTimes;
double* flpRandomCounter;

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
  msgFreq = fConfig->GetValue<uint64_t>("msgFreq");
  amountFlp = fConfig->GetValue<uint64_t>("amountFlp");
  msgAutoscale = fConfig->GetValue<bool>("msgAutoscale");
  scalingFlp = fConfig->GetValue<bool>("scalingFlp");

  flpTimes = new double[amountFlp];
  flpRandomCounter = new double[amountFlp];

  this_thread::sleep_for(chrono::seconds(3));
}




void PrototypeSchedulerProcessor::Run()
{
  FairMQPollerPtr poller(NewPoller("scheduledata"));

  while (CheckCurrentState(RUNNING))
  {
    sendCounter++;

    if (sendCounter ==  1302) { //

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
      //return false;
      break;
    }

    if (sendCounter == 100 && scalingFlp == true) { //nur 100 messages pro Versuch
      average = average / 99;

      //	result << amountFlp << "\t" << average << "\t" << min_abweichung << "\t" << max_abweichung << std::endl;
      result << amountFlp << "\t" << average << "\t" << min << "\t" << max << std::endl;
      LOG(info) << "am ende angelangt, schreibe";
      writeToFile(result.str());
      //return false;
      break;
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


      /*
      FairMQMessagePtr msg2 = NewMessage(len);

      // memset(msg2->GetData(), 'a', msg2->GetSize());
      memcpy(msg2->GetData(), &msgToFlp, sizeof(MyMessage));


      msgSize = std::to_string(msg2->GetSize());
      */


      FairMQMessagePtr msg2[amountFlp];
      for (int i = 0; i < amountFlp; i++) {
        msg2[i] = NewMessage(len);

        //memcpy(msg2[i]->GetData(), const_cast<char*>(text->c_str()), msg2[i]->GetSize()); //bugged bei grosser message
        //memset(msg2[i]->GetData(), 'a', msg2[i]->GetSize()) ;

        memcpy(msg2[i]->GetData(), &msgToFlp, sizeof(MyMessage)) ;
      }
      msgSize = std::to_string(msg2[0]->GetSize());

      //Zeit starten
      //high_resolution_clock::time_point before = high_resolution_clock::now();

      FairMQMessagePtr reply(NewMessage());
      before = high_resolution_clock::now();



      if (randomReply == false) {
        for (int i=0;i<amountFlp;i++) {
          int test = Send(msg2[i], "scheduledata", i);
          if (test < 0 ) {
            LOG(error) << "fail bei index " << i;
            //return false;
            //break;
          }

        //  while (true) {
          //  poller->Poll(1000);
            //if (poller->CheckInput("scheduledata", i)) {

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
                }
                //break;
              }
              else LOG(error) << "failed to receive message";
            //}
          //}
        }
      }
      else { //randomReply = true
        for (int i=0;i<amountFlp;i++) {
          int test = Send(msg2[i], "scheduledatatoflp", i);
          if (test < 0 ) {
            LOG(error) << "fail";
            //return false;
            break;
          }

          if (Receive(reply, "answerfromflp", i) > 0) {
            after = high_resolution_clock::now();
            duration<double> dur = duration_cast<duration<double>>(after - before);
            //result << flpAnswerId << "\t" << dur.count() << std::endl;
            flpTimes[flpAnswerId] += dur.count();
            flpRandomCounter[flpAnswerId]++;
          }
        }
      }



      this_thread::sleep_for(chrono::milliseconds(msgFreq));

      //return true;
    }
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
