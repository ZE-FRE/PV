#ifndef PV_2021_H_
#define PV_2021_H_

/*
 *【2021真题】有停车区和洗车区，容量分别为m和n，有机器人负责停车和洗车，共有五个机器人A、B、C、D、E。
 * 1、A负责将客户的车停到停车区，停车区若没有位置则A休息。
 * 2、B负责将停车区没洗的车开到洗车区，若停车区没有车或洗车区没有位置，则B休息。
 * 3、C负责清洗洗车区的车，若没有车则C休息。
 * 4、D负责将清洗过的车开到停车区，若没有清洗过的车或停车区没有位置则D休息。
 * 5、E负责将停车区洗过的车开给客户，若无车则E休息。
 * 因为停车区与洗车区空间有限，所以每次均只允许一个机器人访问。
 */

/*
 * date:2024/9/29
 *		  +-------------+				+-------------+
 *	A --> |		停车区	|	--> B -->	|	 洗车区	  |	-->	C洗车
 *	E <-- |		容量m	|	<--	D <--	|	 容量n	  |
 *		  +-------------+				+-------------+
 * 
 * 停车区：
 *		A、D相当于是停车区的生产者，生产两种不同类型的产品，B、E分别是这两种产品的消费者
 * 洗车区：
		B生产 ==> C消费；C生产 ==> D消费
 * 
 * 互斥关系：停车区 Semaphore park_mutex = 1;	洗车区	Semaphore clean_mutex = 1;
 * 同步关系：
 *		1、停车区位置			Semaphore park_empty = m;
 *			停车区脏车数量		Semaphore park_dirty = 0;
 *			停车区靓车数量		Semaphore park_clean = 0;	park_dirty + park_clean <= m
 *		2、洗车区位置			Semaphore clean_empty = n;
 *			洗车区脏车数量		Semaphore clean_dirty = 0;
 *			洗车区靓车数量		Semaphore clean_clean = 0;	clean_dirty + clean_clean <= n;
 * 伪代码如下：
 A：
while (1) {
	P(park_empty);
	P(park_mutex);
	// 将客户的脏车停到停车区
	V(park_mutex);
	V(park_dirty);
}
B：
while (1) {
	P(park_dirty);	// 停车区有脏车
	P(clean_empty); // 占用一个洗车区位置
	P(park_mutex);
	// 将客户的车从停车区开出来
	V(park_mutex);
	V(park_empty);
	P(clean_mutex);
	// 将客户的脏车开到洗车区
	V(clean_mutex);
	V(clean_dirty);
}
C：
while (1) {
	P(clean_dirty);
	P(clean_mutex);
	// 洗车
	V(clean_mutex);
	V(clean_clean);
}
D：
while (1) {
	P(clean_clean);
	P(park_empty);
	P(clean_mutex);
	// 将客户的车从洗车区开出来
	V(clean_mutex);
	V(clean_empty);
	P(park_mutex)
	// 将客户的车开到停车区
	V(park_mutex);
	V(park_clean);
}
E：
while (1) {
	P(park_clean);
	P(park_mutex);
	// 将车开给客户
	V(park_mutex);
	V(park_empty);
}
 */


namespace PV2021 {

	void* A(void* args);
	void* B(void* args);
	void* C(void* args);
	void* D(void* args);
	void* E(void* args);

	void testPV2021();

}

#endif // !PV_2021_H_

