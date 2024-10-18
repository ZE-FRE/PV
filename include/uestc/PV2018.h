#ifndef PV_2018_H_
#define PV_2018_H_

/*
 *【2018真题】有一个车票订票查询系统，需实现如下需求：
 *（1）允许多个查询者同时查询车票信息；
 *（2）订票者与查询者不可同时访问系统；
 *（3）订票者之间不可同时访问系统；
 *（4）按用户请求顺序依次提供服务。
 * 请用P、V操作实现订票者与查询者之间的同步互斥关系。
 */

/*
 * date:2024/10/14
 * 读者、写者问题变种
 * 第4条为变种约束，当当前访问者的要求得不到满足，让它排队，用一个互斥信号量来实现排队	Semaphore mutex = 1;
 * 
 * 伪代码如下：
 * int reader_count = 0;
 * Semaphore count_mutex = 1;
 * Semaphore rw_lock = 1;
 * 
 查询者：
 void reader() {
	while (1) {
		P(mutex);
		P(count_mutex);
		if (reader_count == 0) {
			P(rw_lock);
		}
		++reader_count;
		V(count_mutex);
		V(mutex);
		查询车票;
		P(count_mutex);
		--reader_count;
		if (reader_count == 0) {
			V(rw_lock);
		}
		V(count_mutex);
		
	}
 }

 订票者：
 void writer() {
	while (1) {
		P(mutex);
		P(rw_lock);
		订票;
		V(rw_lock);
		V(mutex);
	}
 }
 */

namespace PV2018 {
	void* reader(void* args);
	void* writer(void* args);
	void testPV2018();
}

#endif // !PV_2018_H_

