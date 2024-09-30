#include <iostream>
#include <Windows.h>
#include "../../include/uestc/PV2020.h"
#include "../../include/Semaphore.h"
#include "../../include/ThreadLauncher.h"

namespace PV2020 {
	// 定义信号量
	Semaphore s12_empty = 1, s13_empty = 1;
	Semaphore s12_full = 0, s13_full = 0;
	Semaphore s2_empty = 1;
	Semaphore s3_empty = 1;
	Semaphore s2_full = 0, s3_full = 0;


	void* process1(void* args)
	{
		while (true) {
			P(s12_empty);
			P(s13_empty);
			std::cout << "工序1向s1放入数据" << std::endl;
			V(s12_full);
			V(s13_full);
			Sleep(1000);
		}
		return NULL;
	}
	void* process2(void* args)
	{
		while (true) {
			P(s12_full);
			std::cout << "工序2从s1取出数据" << std::endl;
			V(s12_empty);
			P(s2_empty);
			std::cout << "工序2向s2放入数据" << std::endl;
			V(s2_full);
			Sleep(1500);
		}
		return NULL;
	}
	void* process3(void* args)
	{
		while (true) {
			P(s13_full);
			std::cout << "工序3从s1取出数据" << std::endl;
			V(s13_empty);
			P(s3_empty);
			std::cout << "工序3向s3放入数据" << std::endl;
			V(s3_full);
			Sleep(1500);
		}
		return NULL;
	}
	void* process4(void* args)
	{
		while (true) {
			P(s2_full);
			std::cout << "工序4从s2取出数据" << std::endl;
			V(s2_empty);
			P(s3_full);
			std::cout << "工序4从s3取出数据" << std::endl;
			V(s3_empty);
			Sleep(2000);
		}
		return NULL;
	}

	void testPV2020()
	{
		StartThread("2020年PV题", { process1,process2,process3,process4 });
	}

}