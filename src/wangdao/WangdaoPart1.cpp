#include <Windows.h>
#include <iostream>
#include "../../include/wangdao/WangdaoPart1.h"
#include "../../include/Semaphore.h"
#include "../../include/ThreadLauncher.h"

namespace WangdaoPart1_05 {

	unsigned int M = 3;
	unsigned int N = 2;

	Semaphore mutex = 1;
	Semaphore A_IN = M - 1;
	Semaphore B_IN = N - 1;

	using namespace std;

	void* Put_A(void* args)
	{
		while (true) {
			P(A_IN);
			P(mutex);
			cout << "放入A产品" << endl;
			V(mutex);
			V(B_IN);
			Sleep(1200);
		}
		return nullptr;
	}
	void* Put_B(void* args)
	{
		while (true) {
			P(B_IN);
			P(mutex);
			cout << "放入B产品" << endl;
			V(mutex);
			V(A_IN);
			Sleep(2000);
		}
		return nullptr;
	}
	void testWangdao05()
	{
		StartThread("王道05", { Put_A,Put_A,Put_B,Put_B,Put_B });
	}

}