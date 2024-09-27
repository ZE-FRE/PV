#include "demo.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void testDemo()
{
	testPassParams();
}

void* thread_func(void* args)
{
	printf("线程执行，参数1=%d,参数2=%s\n", *((int**)args)[0], ((char**)args)[1]);
	return NULL;
}

void testPassParams()
{
	pthread_t thread_id;

	int arg1 = 1;
	void** args = (void**)malloc(sizeof(void*) * 2);
	if (!args) return;
	args[0] = &arg1;
	args[1] = (void*)"hello multithread!";

	int ret = pthread_create(&thread_id, NULL, &thread_func, (void*)args);
	if (ret) {
		printf("创建线程失败，失败状态码=%d\n", ret);
		return;
	}
	pthread_join(thread_id, NULL);
	free(args);
}
