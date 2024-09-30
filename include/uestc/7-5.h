#ifndef X_7_5_H_
#define X_7_5_H_

/*
 * 三个进程A、B、C，共享两个缓冲区B1和B2。缓冲区B1中可放n件产品，缓冲区B2中可存放m件产品。进程A每次生产一件产品并将其存入缓冲区B1中；
 * 进程B每次从缓冲区B1中取出一件产品再把它送到缓冲区B2中；进程C每次从缓冲区B2中取出一件产品去消费。为防止把产品存入已满的缓冲区、
 * 从空的缓冲区取产品、或重复产品，试用PV操作实现它们之间的制约。
 */

/*
 * date:2024/9/29
 *		  +-------+			  +-------+
 *	A --> |	 B1	  |	--> B --> |	 B2	  |  --> C消费
 *		  |  容量n |			  |	 容量m |
 *		  +-------+			  +-------+
 * 
 * 互斥访问B1、B2：Semaphore B1_mutex = 1, B2_mutex = 1;
 * 同步关系：
 *		1、A往B1放产品	Semaphore B1_empty = n;
 *		2、B从B1取产品	Semaphore B1_full = 0;
 *		3、B往B2放产品	Semaphore B2_empty = m;
 *		4、C从B2取产品	Semaphore B2_full = 0;
 * 伪代码如下：
 A:
 while (1) {
	P(B1_empty);
	P(B1_mutex);
	// A往B1放产品
	V(B1_mutex);
	V(B1_full);
 }
 B:
 while (1) {
	P(B1_full);
	P(B1_mutex);
	// B从B1取产品
	V(B1_mutex);
	P(B2_empty);
	P(B2_mutex);
	// B往B2放产品
	V(B2_mutex);
	V(B2_full);
 }
 C:
 while (1) {
	P(B2_full);
	P(B2_mutex);
	// C从B2取产品
	V(B2_mutex);
	V(B2_empty);
 }
 */

/*
 * 在公共汽车上，司机负责开车、停车和驾驶，售票员负责门的开门、关门和售票。基本操作规则是只有停车后，售票员才能开门，
 * 只有售票员关门后，司机才能开车。汽车初始状态处于行驶之中。当只有1个司机、2个售票员、2个门、每个售票员负责一个门时的协调操作。
 * 请试用P、V原语实现售票员与司机之间的协调操作，说明每个信号量的含义、初值和值的范围。
 */

/*
 * date:2024/9/29
 * 同步关系：
 *		1、两扇门都关上了 ==> 司机启动车辆	Semaphore gate1 = 1, gate2 = 1;
 *		2、司机停车	   ==> 售票员开门售票	Semaphore stop1 = 0, stop2 = 0;
 * 伪代码如下：
 司机：
 while (1) {
	P(gate1);
	P(gate2);
	// 行驶2秒钟
	V(stop1); // 停车
	V(stop2);
 }

 售票员1：
 while (1) {
	P(stop1);
	// 售票
	V(gate1); // 关上第一扇门
 }

 售票员2：
 while (1) {
	P(stop2);
	// 售票
	V(gate2); // 关上第二扇门
 }
 */

namespace X7_5_driver {
	
	void* driver(void* args);
	void* saleswoman1(void* args);
	void* saleswoman2(void* args);

	void testX7_5_driver();

}

/*
 * 有一阅览室，读者进入时必须先在一张登记表上登记该表中每个表项代表阅览室中的一个座位。读者离开时要销掉其登记信息。
 * 阅览室共有50个座位。登记表每次仅允许一位读者进行登记或注销读者登记，登记时，发现登记表满，他在阅览室外等待，直至有空位再登记进入。
 * 试用P、V操作，描述进去和读者离开行为。
 */

/*
 * date:2024/9/29
 * Semaphore mutex = 1, seats = 50;
 * 伪代码如下：
void reader() {
	while (1) {
		P(seats);
		P(mutex);
		// 登记
		V(mutex);
		// 阅览
		P(mutex);
		//注销登记
		V(mutex);
		V(seats);
	}
}
 */



#endif // !7_5_H_
