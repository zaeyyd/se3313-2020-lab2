#include <iostream>
#include "thread.h"
#include "SharedObject.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <signal.h>
#include <time.h>
#include <sstream> 
#include "Semaphore.h"

using namespace std;

struct MyShared{
	int threadIdShared;
	int reportIdShared;
	int delayShared;
	bool running;
};


class WriterThread : public Thread{
	public:
		int threadId;
		int reportId = 0;
		int delay;
		bool	flag;
		
		WriterThread(int del, int tID):Thread(8*1000){
			this->delay = del;
			this->threadId = tID;
		}

		virtual long ThreadMain(void) override{
			
			//declare shared memory var so this thread can access it
			Shared<MyShared> sharedMemory ("sharedMemory");

			Semaphore wSem("writerSemaphore");

			Semaphore rSem("readerSemaphore");

			while(true)
			{
				wSem.Wait();

				sharedMemory->threadIdShared = threadId; 
				sharedMemory->reportIdShared = ++reportId; 
				sharedMemory->delayShared = delay;
				
				wSem.Signal();
				rSem.Signal();

				sleep(delay);
				
				if(flag){//Exit loop to end the thread
					break;
				}
			}
		}
};

int main(void)
{

	
	cout << "I am a Writer" << endl;

	string ans;
	string delay;
	int delayInt;
	int tID = 0;

	Semaphore writeSem("writerSemaphore", 1, true); 
	Semaphore readSem("readerSemaphore", 0, true); 

	WriterThread * thread;

	
	
	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMamory
	shared ->running = true;
	
	while(true){
		
		cout << "want a new thread? y or n?" << endl;

		getline(cin, ans);

     	if(ans == "y"){

		cout << "enter the delay for the thread" << endl;
		getline(cin, delay);

		istringstream(delay) >> delayInt; 

		thread = new WriterThread(delayInt,++tID); //add arguments as needed
		cout << "thread "+ to_string(tID) << endl;

	 }
	 else{
		 break;
	 }
		
	}

	thread->flag= true;
	delete thread;

	return 0;
	
}


////////////////////////////////////////////////////////////////////////
// This is a possible starting point for using threads and shared memory. 
// You do not have to start with this
////////////////////////////////////////////////////////////////////////










// by Zayyed Mansoor