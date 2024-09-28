#ifndef PV_2017_H_
#define PV_2017_H_

/*
 *��2017���⡿һ�����������Է�����ˮ�������׷�ƻ����ĸ�׷����ӣ�Ů��ȡˮ����
 * Ҫ��ֻ��һ���˿��Բ������̣�ֻ�й�����ͬʱ��ƻ��������ʱŮ���ſ���ȡˮ��������ͬʱ������ˮ��ȡ�ߡ�
 * ����P��V����д����ʵ��ͬ�����̣�����д�����ź����ĺ��塣
 */

/*
 * date:2024/9/28
 * �ٽ���Դ������
 * �����ϵ�����ס�ĸ�ס�Ů��������ʹ��̣�����ֻ�и��׺�ĸ�׿���ͬʱ���ʹ��̣���˸��ס�ĸ����Ҫ���ʻ����ź���
 *											Semaphore mutex = 1;
 * ͬ����ϵ��
 *		1������û��ƻ�� ==> ���׷�ƻ��			Semaphore apple = 1;
 *		2������û������ ==> ĸ�׷�����			Semaphore orange = 1;
 *		3��������ƻ�������� ==> Ů��ȡ������ˮ��	Semaphore full = 0;
 * α�������£�
 ���׽��̣�
while (1) {
	P(apple);
	P(mutex);
	Put("ƻ��");
	V(mutex);
	V(full);
}

ĸ�׽��̣�
while (1) {
	P(orange);
	P(mutex);
	Put("����");
	V(mutex);
	V(full);
}

Ů�����̣�
while (1) {
	P(full);
	P(full);
	Get("ƻ��");
	Get("����");
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

