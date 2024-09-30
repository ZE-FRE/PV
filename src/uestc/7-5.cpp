#include <Windows.h>
#include <iostream>
#include "../../include/uestc/7-5.h"
#include "../../include/Semaphore.h"
#include "../../include/ThreadLauncher.h"

namespace X7_5_driver {

	Semaphore gate1 = 1, gate2 = 1;
	Semaphore stop1 = 0, stop2 = 0;

	using namespace std;

	void* driver(void* args)
	{
		while (true) {
			P(gate1);
			P(gate2);
			cout << "司机开车行驶2秒钟" << endl;
			Sleep(2000);
			V(stop1);
			V(stop2);
		}
		return nullptr;
	}

	void* saleswoman1(void* args)
	{
		while (true) {
			P(stop1);
			cout << "售票员1开门售票" << endl;
			Sleep(1000);
			V(gate1);
		}
		return nullptr;
	}

	void* saleswoman2(void* args)
	{
		while (true) {
			P(stop2);
			cout << "售票员2开门售票" << endl;
			Sleep(2000);
			V(gate2);
		}
		return nullptr;
	}

	void testX7_5_driver()
	{
		StartThread("司机与售票员", { driver, saleswoman1, saleswoman2 });
	}

}