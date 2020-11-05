#include <iostream>
#include "SharedObject.h"
#include "Semaphore.h"

using namespace std;

struct MyShared{
	int threadIdShared;
	int reportIdShared;
	int delayShared;
	bool running;
};




int main(void)
{
	cout << "I am a reader" << endl;

	Shared<MyShared> sharedMemory ("sharedMemory");

	Semaphore readSem("readerSemaphore");


	while (true)
	{


		if(sharedMemory->running == true){
			readSem.Wait();
			cout << "Thread ID: " << sharedMemory->threadIdShared <<" Report ID: "<<sharedMemory->reportIdShared <<" Delay: " <<sharedMemory->delayShared << endl;
			sleep(1);
		}
		else{
			break;
		}
	}
	
	return 0;
}