#include "demo.h"
#include "semaphore_demo.h"
#include "PV2013.h"
#include "PV2014.h"

#pragma comment(lib, "pthreadVC2.lib")


int main(int argc, char* argv[]) {
	
	//testDemo();

	//testSemaphore();

	//PV2013::testPV2013();

	PV2014::testPV2014();

	return 0;
}