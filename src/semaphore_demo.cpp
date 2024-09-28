#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <Windows.h>

#include "../../include/semaphore_demo.h"
#include "../../include/Semaphore.h"

static Semaphore semaphore = 0;

void testSemaphore() {

	pthread_t thread1_id;
	pthread_create(&thread1_id, NULL, &print_hello, NULL);

	pthread_t thread2_id;
	pthread_create(&thread2_id, NULL, &print_world, NULL);

	pthread_join(thread2_id, NULL);

}

void* print_hello(void* args)
{
	Sleep(300);
	printf("hello ");
	Sleep(1000);
	V(semaphore);
	return NULL;
}

void* print_world(void* args)
{
	P(semaphore);
	printf("world");
	return NULL;
}
