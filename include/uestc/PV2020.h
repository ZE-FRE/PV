#ifndef PV_2020_H_
#define PV_2020_H_

/*
 *【2020真题】某生产线有4个工序。
 * 工序1：测量参数之后将数据输入缓冲区s1；
 * 工序2：从缓冲区s1中读取数据然后进行计算，将计算结果输入缓冲区s2中。
 * 工序3：从缓冲区s1中读取数据然后进行综合分析，将分析参数输入缓冲区s3。
 * 工序4：从缓冲区s2，s3中读取数据，判断是否合格。
 * 要求流水线一次检查一个产品，各缓冲区只有一个。
 */

/*
 * date:2024/9/29
 * 同步关系：
 *		1、缓冲区s1数据被工序2和工序3取走 ==> 唤醒工序1	Semaphore s12_empty = 1, s13_empty = 1;
 *		2、缓冲区s1存入数据 ==> 唤醒工序2和工序3		Semaphore s12_full = 0, s13_full = 0;				
 *		3、缓冲区s2无数据   ==> 唤醒工序2				Semaphore s2_empty = 1;
 *		4、缓冲区s3无数据   ==> 唤醒工序3				Semaphore s3_empty = 1;
 *		5、缓冲区s2和s3都有数据 ==> 唤醒工序4			Semaphore s2_full = 0, s3_full = 0;
 * 伪代码如下：
 工序1：
while (1) {
	测量参数;
	P(s12_empty);
	P(s13_empty);
	将数据放入缓冲区s1;
	V(s12_full);
	V(s13_full);
}

工序2：
while (1) {
	P(s12_full);
	从s1取出数据并计算;
	V(s12_empty);
	P(s2_empty);
	将数据放入缓冲区s2;
	V(s2_full);
}

工序3：
while (1) {
	P(s13_full);
	从s1取出数据进行综合分析;
	V(s13_empty);
	P(s3_empty);
	将数据放入缓冲区s3;
	V(s3_full);
}

工序4：
while (1) {
	P(s2_full);
	从s2取出数据
	V(s2_empty);
	P(s3_full);
	从s3取出数据
	V(s3_empty);
	判断数据是否合格;
}
 */

namespace PV2020 {

	// 工序1、2、3、4
	void* process1(void* args);
	void* process2(void* args);
	void* process3(void* args);
	void* process4(void* args);

	void testPV2020();

}

#endif // !PV_2020_H_

