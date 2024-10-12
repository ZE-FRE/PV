#include <Windows.h>
#include <iostream>
#include "../../include/wangdao/WangdaoPart1.h"
#include "../../include/Semaphore.h"
#include "../../include/ThreadLauncher.h"
#include <vector>

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


namespace WangdaoPart1_08 {
	Semaphore well_mutex = 1, water_bin_mutex = 1;
	Semaphore bucket = 3;
	Semaphore water_bin_empty = 10, water_bin_full = 0;

	using namespace std;

	void* little_monk(void* args)
	{
		string monk_name = "【" + string((const char*)args) + "】";
		while (true) {
			P(water_bin_empty); // 水缸未满
			P(bucket); // 拿一个水桶
			P(well_mutex);
			cout << monk_name << "拿一个水桶从水井打水" << endl;
			Sleep(500);
			V(well_mutex);
			P(water_bin_mutex);
			cout << monk_name << "把水倒进水缸" << endl;
			Sleep(500);
			V(water_bin_mutex);
			V(water_bin_full);
			V(bucket); // 归还水桶
		}
		return nullptr;
	}

	void* senior_monk(void* args)
	{
		string monk_name = "【" + string((const char*)args) + "】";
		while (1) {
			P(water_bin_full);
			P(bucket);
			P(water_bin_mutex);
			cout << monk_name << "从水缸取水" << endl;
			Sleep(500);
			V(water_bin_mutex);
			V(water_bin_empty);
			V(bucket);
		}
		return nullptr;
	}

	void testWangdao08()
	{
		std::vector<thread_func> funcs = { little_monk, little_monk, senior_monk, senior_monk };
		std::vector<const char*> thread_names = { "小和尚1", "小和尚2", "老和尚1", "老和尚2"};
		StartThread("王道08，小和尚挑水给老和尚喝", funcs, thread_names);
	}

}