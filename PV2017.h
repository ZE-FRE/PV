#ifndef PV_2017_H_
#define PV_2017_H_

/*
 *【2017真题】一个果盘最多可以放两个水果，父亲放苹果，母亲放橘子，女儿取水果。
 * 要求：只有一个人可以操作果盘，只有果盘里同时有苹果和橘子时女儿才可以取水果，并且同时把两个水果取走。
 * 请用P、V操作写出其实现同步过程，并且写出其信号量的含义。
 */

/*
 * date:2024/9/28
 * 临界资源：果盘
 * 互斥关系：父亲、母亲、女儿互斥访问果盘，本题只有父亲和母亲可能同时访问果盘，因此父亲、母亲需要访问互斥信号量
 *											Semaphore mutex = 1;
 * 同步关系：
 *		1、盘中没有苹果 ==> 父亲放苹果			Semaphore apple = 1;
 *		2、盘中没有橘子 ==> 母亲放橘子			Semaphore orange = 1;
 *		3、盘中有苹果和橘子 ==> 女儿取走两个水果	Semaphore full = 0;
 * 伪代码如下：
 父亲进程：
while (1) {
	P(apple);
	P(mutex);
	Put("苹果");
	V(mutex);
	V(full);
}

母亲进程：
while (1) {
	P(orange);
	P(mutex);
	Put("橘子");
	V(mutex);
	V(full);
}

女儿进程：
while (1) {
	P(full);
	P(full);
	Get("苹果");
	Get("橘子");
	V(apple);
	V(orange);
}
 */

namespace PV2017 {

	void* father(void* args);
	void* mother(void* args);
	void* daughter(void* args);

	void Put(const char*);
	void Get(const char*);

	void testPV2017();
}

#endif // !PV_2017_H_

