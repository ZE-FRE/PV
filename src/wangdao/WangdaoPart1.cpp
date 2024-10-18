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

namespace WangdaoPart1_06 {

	using namespace std;

	Semaphore ticket = 0;
	Semaphore customer_count = 0;

	void* salesperson(void* args)
	{
		string salesperson_name = string("【") + (char*)args + "】";
		while (true) {
			P(customer_count);
			V(ticket);
			cout << salesperson_name << "向顾客推销面包" << endl;
			Sleep(1200);
		}
		return nullptr;
	}
	void* customer(void* args)
	{
		string customer_name = string("【") + (char*)args + "】";
		while (true) {
			cout << customer_name << "进店" << endl;
			V(customer_count);
			P(ticket);
			cout << customer_name << "接受推销" << endl;
			Sleep(1500);
		}
		return nullptr;
	}

	void testWangdao06()
	{
		std::vector<thread_func> funcs = { salesperson, salesperson, salesperson, customer, customer };
		std::vector<const char*> thread_names = { "销售1", "销售2", "销售3", "顾客1", "顾客2"};
		StartThread("王道06，面包店，销售人员与顾客", funcs, thread_names);
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

namespace WangdaoPart1_09 {

	using namespace std;

	Semaphore device_mutex = 1;
	Semaphore P2_read = 0;
	Semaphore P1_read = 0;
	Semaphore P2_y_finished = 0;
	Semaphore P3_z_finished = 0;

	int a, b, c, x, y, z;

	void* P1(void* args)
	{
		while (true) {
			P(device_mutex);
			a = 10; // P1读取第一个数据
			V(device_mutex);
			V(P1_read);
			P(P2_read); // 等待P2进程读取b
			cout << "P1进程计算x的值" << endl;
			x = a + b; // 计算x
			P(P2_y_finished); // 等待P2进程计算出y的值
			P(P3_z_finished); // 等待P3进程计算出z的值
			// 打印x、y、z
			cout << "P1进程打印x、y、z的值。" << "x=" << x << ",y=" << y << ",z=" << z << endl;
			Sleep(1000);
		}
		return nullptr;
	}

	void* P2(void* args)
	{
		while (true) {
			P(device_mutex);
			b = 5;
			V(device_mutex);
			V(P2_read);
			P(P1_read); // 等待P1进程读取a
			cout << "P2进程计算y的值" << endl;
			y = a * b;	// 计算y
			V(P2_y_finished);
			V(P2_y_finished);
			Sleep(1000);
		}
		return nullptr;
	}

	void* P3(void* args)
	{
		while (1) {
			P(device_mutex);
			c = 4;
			V(device_mutex);
			P(P2_y_finished);
			cout << "P3进程计算z的值" << endl;
			z = y + c - a;
			V(P3_z_finished);
			Sleep(1000);
		}
		return nullptr;
	}

	void testWangdao09()
	{
		StartThread("王道09", { P1, P2, P3 });
	}

}