#ifndef PV_2014_H_
#define PV_2014_H_

/*
 *【2014真题】3个进程P0、P1、P2互斥使用一个仅包含1个单元的缓冲区。
 * P0每次用produce()生成1个正整数，并用put()送入缓冲区。
 * 对于缓冲区中的每个数据，P1用get1()取出一次并用compute()1计算其平方值，P2用get2()取出一次并用compute2()计算其立方值。
 * 请用信号量机制实现进程P0、P1、P2之间的同步与互斥关系，并说明所定义信号量的含义，要求用伪代码描述。
 */

/*
 * date:2024/9/27
 * 临界资源：仅包含1个单元的缓冲区
 * 互斥关系：P0、P1、P2互斥访问缓冲区，本题中P0与P1、P2不可能同时访问缓冲区，但P1和P2有可能同时访问缓冲区，
 *			因此还是要设置互斥信号量，但P0中可不去请求互斥信号量，
 *			而P1和P2要请求互斥信号量。			Semaphre mutex = 1;
 * 同步关系：
 *		1、P0放入一个正整数 ==> 通知P1			Semaphore sem01 = 0;
 *						  ==> 通知P2			Semaphore sem02 = 0;
 *		2、P1、P2均从缓冲区取出数据 ==> 通知P0	Semaphore sem0 = 2;
 * 伪代码如下：
 P0进程：
 while (1) 
 {
	produce();
	P(sem0);
	P(sem0);
	put();
	V(sem01);
	V(sem02);
}

P1进程：
while (1) {
	P(sem01);
	P(mutex);
	get1();
	V(mutex);
	V(sem0);
	compute1();
}

P2进程：
while (1) {
	P(sem02);
	P(mutex);
	get2();
	V(mutex);
	V(sem0);
	compute2();
}
 */

#include "Semaphore.h"
namespace PV2014 
{
	void* P0(void* args);
	void* P1(void* args);
	void* P2(void* args);

	unsigned int produce();
	void put(unsigned int);

	unsigned int get1();
	void compute1(unsigned int);

	unsigned int get2();
	void compute2(unsigned int);

	void testPV2014();

}

#endif // !PV_2014_H_

