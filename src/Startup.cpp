#include "../include/demo.h"
#include "../include/semaphore_demo.h"
#include "../include/uestc/PV2013.h"
#include "../include/uestc/PV2014.h"
#include "../include/uestc/PV2016.h"
#include "../include/uestc/PV2017.h"

#include "../include/uestc/PV2020.h"
#include "../include/uestc/PV2021.h"

#include "../include/uestc/7-5.h"

#include "../include/wangdao/WangdaoPart1.h"

#pragma comment(lib, "pthreadVC2.lib")


int main(int argc, char* argv[]) {
	
	//testDemo();

	//testSemaphore();

	//PV2013::testPV2013();

	//PV2014::testPV2014();


	//PV2017::testPV2017();

	//PV2020::testPV2020();

	//PV2021::testPV2021();


	//X7_5_driver::testX7_5_driver();


	WangdaoPart1_05::testWangdao05();

	return 0;
}