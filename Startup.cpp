#include "demo.h"
#include "semaphore_demo.h"
#include "PV2013.h"

#pragma comment(lib, "pthreadVC2.lib")


int main(int argc, char* argv[]) {
	
	//testDemo();

	//testSemaphore();

	PV2013::testPV2013();

	return 0;
}