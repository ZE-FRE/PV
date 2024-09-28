#include "../include/Semaphore.h"

void P(Semaphore &semaphore)
{
	sem_wait(&semaphore.m_semaphore);
}

void V(Semaphore &semaphore)
{
	sem_post(&semaphore.m_semaphore);
}

Semaphore::Semaphore(int permits) :m_semaphore(nullptr) 
{
	sem_init(&m_semaphore, 0, permits);
}

Semaphore::~Semaphore()
{
	sem_destroy(&m_semaphore);
}
