#include <iostream>
#include "SharedObject.h"

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


	while (true)
	{
		// cout << sharedMemory->threadIdShared << endl;

		if(sharedMemory->running == true){
			cout << "Thread ID: " << sharedMemory->threadIdShared <<" Report ID: "<<sharedMemory->reportIdShared <<" Delay: " <<sharedMemory->delayShared << endl;
			sleep(1);
		}
		else{
			break;
		}
	}
	
}
