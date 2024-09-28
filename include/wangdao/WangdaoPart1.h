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
 * 06.面包师有很多面包，由n名销售人员推销。每名顾客进店后取一个号，并且等待叫号，当一名销售人员空闲时，就叫下一个号。
 * 试设计一个使销售人员和顾客同步的算法。
 */

/*
 * 07.某工厂有两个生产车间和一个装配车间，两个生产车间分别生产A,B两种零件，装配车间的任务是把A,B两种零件组装成产品。
 * 两个生产车间每生产一个零件后，都要分别把它们送到专配车间的货架F1,F2上。F1存放零件A，F2存放零件B，F1和F2的容量均可存放10个零件。
 * 装配工人每次从货架上取一个零件A和一个零件B后组装成产品。请用P,V操作进行正确管理。
 */

/*
 * 08.某寺庙有小和尚、老和尚若干，有一水缸，由小和尚提水入缸供老和尚饮用。水缸可容10桶水，水取自同一井中。水井径窄，
 * 每次只能容一个桶取水。水桶总数为3个。每次入缸取水仅为1桶水，且不可同时进行。试给出有关从缸取水、入水的算法描述。
 */

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
