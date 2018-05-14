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


high_resolution_clock::time_point before;
high_resolution_clock::time_point after;

int sendCounter = 0;
int answerCounter = 0;
std::string msgSize;

struct MyMessage {
uint64_t sendCounter;
uint64_t replyId;
std::string content;
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
}





bool PrototypeSchedulerProcessor::ConditionalRun()
{

	sendCounter++;
	if (sendCounter > 50) { //
		LOG(info) << "am ende angelangt"; 
		return false; 
	}


int len = messageSize;
//string* text;

   //0 means that the message size will scale

//genau 1024 chars --> genau 1 kB
string* text = new string("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
if (messageSize == 0) {
len = 1024;

//4096 bytes -> 4kb
//*text = *text + *text + *text + *text;
//len = 4096;

//8192 bytes -> 8kb
//*text = *text + *text;
//len = 8192;

//16384 bytes -> 16kb
//*text  = *text + *text;
//len = 16384;

//32768 bytes -> 32kb
//*text = *text + *text;
//len = 32768;

//65536 bytes -> 64kb
//*text = *text + *text;
//len = 65536;

//131072 bytes -> 128kb
//*text = *text + *text;
//len = 131072;

//262144 bytes -> 256kb
//*text = *text + *text;
//len = 262144;


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
	
}


MyMessage msgToFlp;
	msgToFlp.sendCounter = sendCounter;
	//wenn alle antworten sollen -> -1
	//msgToFlp.content = *text;
	msgToFlp.content = "asdf";

if (randomReply == true) { //eine reply in MyMessage ID zwischen 1.. #FLPs auswählen

//teil für random id -> statistik
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distribution(0, amountFlp);
int flpAnswerId = distribution(eng); //creates the random variable in the range of 0 and amountFlp

LOG(info) << "FLP " << flpAnswerId << " soll antworten";
	msgToFlp.replyId = flpAnswerId; 

}
else { // keine random ID -> in MyMessage reply ID auf -1 setzen
	msgToFlp.replyId = -1; 
}






FairMQMessagePtr msg2;
msg2 = NewMessage(len);

LOG(info) << "hier1";
	memcpy(msg2->GetData(), const_cast<char*>(text->c_str()), msg2->GetSize()); //bugged bei grosser message
	//memset(msg2->GetData(), 'a', msg2->GetSize()) ;

	//memcpy(msg2->GetData(), &msgToFlp, sizeof(MyMessage)) ;
LOG(info) << "hier2";


msgSize = std::to_string(msg2->GetSize());



	//Zeit starten
//high_resolution_clock::time_point before = high_resolution_clock::now(); 
FairMQMessagePtr reply(NewMessage());

before = high_resolution_clock::now(); 
			



  LOG(info) << "sende";
		int test = Send(msg2, "scheduledatatoflp");
		if (test < 0 ) 
			{ LOG(error) << "fail";
			return false; }
		LOG(info) << "hier3";

 for (int i=0;i<amountFlp;i++) {
		
		if (Receive(reply, "answerfromflp", i) >= 0)
       		 {
		
          	  LOG(info) << "Empfange von FLP: \"";// << string(static_cast<char*>(reply->GetData()));
		answerCounter++;
	
		if (answerCounter == amountFlp) { //alle haben geantwortet, timer stoppen -> gilt für RTT
			after = high_resolution_clock::now();
			duration<double> dur = duration_cast<duration<double>>(after - before);
			LOG(info) << "bestätigung von allen " << amountFlp <<" bekommen, schreibe";
			//write(amountFlp, dur); //für skalierende #flps
			write(msgSize, dur);
			answerCounter=0;
			}
		//return true;
		}
		else LOG(info)<<"hier2"; 
}

		LOG(info) << "hier4";
	
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

    // Modify the received string
    //string* text = new std::string(static_cast<char*>(msg->GetData()), msg->GetSize());
    //*text += " (modified by " + fId + ")";


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

//524288 bytes -> 512kb
*text = *text + *text;
len = 524288;

//1048576 bytes -> 1024kb, 1mb
*text = *text + *text;
len = 1048576;

//2097152 bytes -> 2048kb, 2mb
*text = *text + *text;
len = 2097152;

//4194304 bytes -> 4096kb, 4mb
*text = *text + *text;
len = 4194304;

//8388608 bytes -> 8192kb, 8mb
*text = *text + *text;
len = 8388608;

//16777216 bytes -> 16384kb, 16mb
*text = *text + *text;
len = 16777216;




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


    // create message object with a pointer to the data buffer,
    // its size,
    // custom deletion function (called when transfer is done),
    // and pointer to the object managing the data buffer
  

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

void PrototypeSchedulerProcessor::write(int amountFlp, duration<double>dur) {
	std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
	gnudatafile << amountFlp << "\t" << dur.count() << std::endl;
	return;
}

void PrototypeSchedulerProcessor::write(std::string s1, duration<double> dur) {
	std::ofstream gnudatafile("gnudatafile.txt", std::ios_base::out | std::ios_base::app );
	gnudatafile << s1 << "\t" << dur.count() << std::endl;
	return;
}

PrototypeSchedulerProcessor::~PrototypeSchedulerProcessor()
{
}
