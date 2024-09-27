#ifndef PV_2014_H_
#define PV_2014_H_

/*
 *��2014���⡿3������P0��P1��P2����ʹ��һ��������1����Ԫ�Ļ�������
 * P0ÿ����produce()����1��������������put()���뻺������
 * ���ڻ������е�ÿ�����ݣ�P1��get1()ȡ��һ�β���compute()1������ƽ��ֵ��P2��get2()ȡ��һ�β���compute2()����������ֵ��
 * �����ź�������ʵ�ֽ���P0��P1��P2֮���ͬ���뻥���ϵ����˵���������ź����ĺ��壬Ҫ����α����������
 */

/*
 * date:2024/9/27
 * �ٽ���Դ��������1����Ԫ�Ļ�����
 * �����ϵ��P0��P1��P2������ʻ�������������P0��P1��P2������ͬʱ���ʻ���������P1��P2�п���ͬʱ���ʻ�������
 *			��˻���Ҫ���û����ź�������P0�пɲ�ȥ���󻥳��ź�����
 *			��P1��P2Ҫ���󻥳��ź�����			Semaphre mutex = 1;
 * ͬ����ϵ��
 *		1��P0����һ�������� ==> ֪ͨP1			Semaphore sem01 = 0;
 *						  ==> ֪ͨP2			Semaphore sem02 = 0;
 *		2��P1��P2���ӻ�����ȡ������ ==> ֪ͨP0	Semaphore sem0 = 2;
 * α�������£�
 P0���̣�
 while (1) 
 {
	produce();
	P(sem0);
	P(sem0);
	put();
	V(sem01);
	V(sem02);
}

P1���̣�
while (1) {
	P(sem01);
	P(mutex);
	get1();
	V(mutex);
	V(sem0);
	compute1();
}

P2���̣�
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

