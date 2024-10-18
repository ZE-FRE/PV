#include <iostream>
#include <Windows.h>
#include <time.h>
#include "../../include/uestc/PV2018.h"
#include "../../include/Semaphore.h"
#include "../../include/ThreadLauncher.h"

namespace PV2018 {

	using namespace std;

	Semaphore mutex = 1;
	int reader_count = 0;
	Semaphore count_mutex = 1;
	Semaphore rw_lock = 1;

	void* reader(void* args)
	{
		string user = string("【") + (char*)args + "】";
		while (true) {
			P(mutex);
			P(count_mutex);
			if (reader_count == 0) {
				P(rw_lock);
			}
			++reader_count;
			V(count_mutex);
			V(mutex);
			cout << user << "查询车票" << endl;
			Sleep(2000);
			cout << user << "查询完毕" << endl;
			P(count_mutex);
			--reader_count;
			if (reader_count == 0) {
				V(rw_lock);
			}
			V(count_mutex);
		}
		return nullptr;
	}

	void* writer(void* args)
	{
		string user = string("【") + (char*)args + "】";
		while (true) {
			P(mutex);
			P(rw_lock);
			cout << user << "订票" << endl;
			Sleep(1200);
			V(rw_lock);
			V(mutex);
			cout << user << "订票完毕" << endl;
		}
		return nullptr;
	}

	void testPV2018()
	{
		vector<thread_func> funcs = { reader, writer, reader, reader, writer, writer };
		vector<const char*> thread_names = { "查询者1", "订票者1", "查询者2", "查询者3", "订票者2", "订票者3"};
		StartThread("2018PV题", funcs, thread_names);
	}

}