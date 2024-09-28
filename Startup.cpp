#include "demo.h"
#include "semaphore_demo.h"
#include "PV2013.h"
#include "PV2014.h"
#include "PV2016.h"
#include "PV2017.h"

#pragma comment(lib, "pthreadVC2.lib")


int main(int argc, char* argv[]) {
	
	//testDemo();

	//testSemaphore();

	//PV2013::testPV2013();

	//PV2014::testPV2014();


	PV2017::testPV2017();

	return 0;
}