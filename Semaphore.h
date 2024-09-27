#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <semaphore.h>

/*
 * 封装信号量，使得使用方式可以与在纸上作答时的风格一样
 * date:2024/9/27
 */
class Semaphore {

	friend void P(Semaphore &semaphore);
	friend void V(Semaphore &semaphore);

public:
	Semaphore(int permits);

	~Semaphore();

	// 禁用拷贝构造与拷贝赋值
	Semaphore(const Semaphore&) = delete;
	Semaphore& operator=(const Semaphore&) = delete;

private:
	sem_t m_semaphore;
};

void P(Semaphore& semaphore);

void V(Semaphore& semaphore);

#endif // !SEMAPHORE_H_

