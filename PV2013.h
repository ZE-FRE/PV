#ifndef PV_2013_H_
#define PV_2013_H_
/*
 *【2013真题】桌上有一空盘，允许存放最多两个水果。爸爸可向盘中放苹果或橘子，儿子专等吃盘中的橘子，女儿专等吃盘中的苹果。
 * 规定当盘子不满时，一次只能放一只水果；当盘子不空时，一次只能取一只水果；
 * 父亲放水果时，儿子女儿不能取；儿子女儿取水果时，父亲不能放。
 */

/*
 * date:2024/9/27
 * 临界资源：盘子
 * 同步关系：
 *		1、盘不空 ==> 通知父亲放水果；		Semaphore plate = 2
 *		2、盘中有橘子 ==> 通知儿子取橘子	Semaphore orange = 0;
 *		3、盘中有苹果 ==> 通知女儿取苹果	Semaphore apple = 0;
 * 互斥关系：父亲、儿子、女儿互斥访问盘子		Semaphore plate_mutex = 1;
 * 
 * 伪代码如下：
 父亲线程：
 while (1) {
	P(plate);
	// 随机函数，0表示放橘子，1表示放苹果
	int fruit = Random(); 
	// 互斥访问盘子
	P(plate_mutex);
	if (fruit == 0) {
		Put("橘子");
		V(orange);
	}
	else {
		Put("苹果");
		V(apple);
	}
	V(plate_mutex);
}

儿子线程：
while (1) {
	P(orange);
	P(plate_mutex);
	GetAndConsume("橘子");
	V(plate_mutex);
	V(plate);
}

女儿线程：
while (1) {
	P(apple);
	P(plate_mutex);
	GetAndConsume("苹果");
	V(plate_mutex);
	V(plate);
}
 */

namespace PV2013 
{

	// 父亲线程
	void* father(void* args);
	// 儿子线程
	void* son(void* args);
	// 女儿线程
	void* daughter(void* args);

	unsigned int random();

	void testPV2013();

}


#endif // !PV_2013_H_

