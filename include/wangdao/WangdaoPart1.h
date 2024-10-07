#ifndef WANGDAO_PART1_H_
#define WANGDAO_PART1_H_

/*
 * 05.在一个仓库中可以存放A和B两种产品，要求：
 * ①每次只能存入一种产品。
 * ②A产品数量-B产品数量 < M。
 * ③B产品数量-A产品数量 < N。
 * 其中，M,N是正整数，试用P操作、V操作描述产品A与产品B的入库过程。
 */

/*
 * date:2024/9/29
 * 本题并没有限定仓库的容量，因此就不管它了。
 * 互斥关系：向仓库放产品的线程必须互斥访问仓库		Semaphore mutex = 1;
 * 同步关系：
 *		1、定义信号量——可放入A产品的数量：Semaphore A_IN = M-1;
 *		2、定义信号量——可放入B产品的数量：Semaphore B_IN = N-1;
 * 伪代码如下：
 放A产品的线程：
 void A() {
	while (1) {
		P(A_IN);
		P(mutex);
		// 放入A产品
		V(mutex);
		V(B_IN); // 放了一个A产品进去后，就可以多放一个B产品了
	}
 }

 放B产品的线程：
 void B() {
	while (1) {
		P(B_IN);
		P(mutex);
		// 放入B产品
		V(mutex);
		V(A_IN);
	}
 }
 */
namespace WangdaoPart1_05 {
	void* Put_A(void* args);
	void* Put_B(void* args);
	void testWangdao05();
}

/*
 * 06.面包师有很多面包，由n名销售人员推销。每名顾客进店后取一个号，并且等待叫号，当一名销售人员空闲时，就叫下一个号。
 * 试设计一个使销售人员和顾客同步的算法。
 */

/*
 * 07.某工厂有两个生产车间和一个装配车间，两个生产车间分别生产A,B两种零件，装配车间的任务是把A,B两种零件组装成产品。
 * 两个生产车间每生产一个零件后，都要分别把它们送到专配车间的货架F1,F2上。F1存放零件A，F2存放零件B，F1和F2的容量均可存放10个零件。
 * 装配工人每次从货架上取一个零件A和一个零件B后组装成产品。请用P,V操作进行正确管理。
 */

/*
 * 临界资源：货架F1，F2	Semaphore F1_mutex = 1, F2_mutex = 1;
 * 同步关系：
 *		1、F1货架未满	==> 车间1将产品A放到F1货架		Semaphore F1_empty = 10;
 *		2、F2货架未满	==> 车间2将产品B放到F2货架		Semaphore F2_empty = 10;
 *		3、F1和F2货架都有产品 ==> 装配工人从F1和F2货架取下零件，组装成产品
 *						Semaphore F1_full = 0;	Semaphore F2_full = 0;
 * 伪代码如下：
 生产车间1：
 void producer1() {
	while (1) {
		生产零件A;
		P(F1_empty);
		P(F1_mutex);
		将零件A放入车间F1;
		V(F1_mutex);
		V(F1_full);
	}
 }

 生产车间2：
 void producer2() {
	while (1) {
		生产零件B;
		P(F2_empty);
		P(F2_mutex);
		将零件B放入车间F2;
		V(F2_mutex);
		V(F2_full);
	}
 }

 组装车间：
 void assemble() {
	while (1) {
		P(F1_full);
		P(F1_mutex);
		从车间F1取出零件A;
		V(F1_mutex);
		V(F1_empty);
		P(F2_full);
		P(F2_mutex);
		从车间F2取出零件B;
		V(F2_mutex);
		V(F2_empty);
	}
 }
 */

/*
 * 08.某寺庙有小和尚、老和尚若干，有一水缸，由小和尚提水入缸供老和尚饮用。水缸可容10桶水，水取自同一井中。水井径窄，
 * 每次只能容一个桶取水。水桶总数为3个。每次入缸取水仅为1桶水，且不可同时进行。试给出有关从缸取水、入水的算法描述。
 */

/*
 * 临界资源：水井、水缸	Semaphore well_mutex = 1, water_bin_mutex = 1;
 * 资源：   水桶			Semaphore bucket = 3;
 * 同步关系：
 *		1、水缸未满	==> 小和尚拿水桶取水倒入水缸	Semaphore water_bin_empty = 10;
 *		2、水缸不空	==> 老和尚拿水桶从水缸取水引用	Semaphore water_bin_full = 0;
 * 伪代码如下：
 小和尚：
 void little_monk() {
	while (1) {
		P(water_bin_empty); // 水缸未满
		P(bucket); // 拿一个水桶
		P(well_mutex);
		从水井取水;
		V(well_mutex);
		P(water_bin_mutex);
		把水倒进水缸;
		V(water_bin_mutex);
		V(water_bin_full);
		V(bucket); // 归还水桶
	}
 }

 老和尚：
 void senior_monk() {
	while (1) {
		P(water_bin_full);
		P(bucket);
		P(water_bin_mutex);
		从水缸取水;
		V(water_bin_mutex);
		V(water_bin_empty);
		V(bucket);
	}
 }
 */
namespace WangdaoPart1_08 {
	void* little_monk(void* args);
	void* senior_monk(void* args);
	void testWangdao08();
}

/*
 * 09.如下图所示，三个合作进程P1,P2,P3，它们都需要通过同一设备输入各自的数据a,b,c，该输入设备必须互斥地使用，
 * 而且其第一个数据必须由P1进程读取，第二个数据必须由P2进程读取，第三个数据必须由P3进程读取。
 * 然后，三个进程分别对输入数据进行下列计算：
 * P1:x = a + b;
 * P2:y = a*b;
 * P3:z = y + c - a;
 * 最后，P1进程通过所连接地打印机将计算结果x,y,z的值打印出来。请用信号量实现它们的同步
 * 
 *		+-------+		+-------+
 *		| 打印机 |<------|	P1	|<--+
 *		+-------+		+-------+	|
 *						+-------+	|			+----------------+
 *						|	P2	|<--------------| 非抢占式输入设备	 |
 *						+-------+	|			+----------------+
 *						+-------+	|
 *						|	P3	|<--+
 *						+-------+
 */



#endif // !WANGDAO_PART1_H_
