#include "PV2013.h"
#include <pthread.h>
#include <iostream>
#include <Windows.h>
#include <time.h>
#include "Semaphore.h"

namespace PV2013 {
	Semaphore plate(2), orange(0), apple(0), plate_mutex(1);
}

void* PV2013::father(void* args)
{
	while (true) {
		P(plate);
		unsigned int fruit = random();
		P(plate_mutex);
		if (fruit == 0) {
			std::cout << "爸爸放入橘子" << std::endl;
			V(orange);
		}
		else {
			std::cout << "爸爸放入苹果" << std::endl;
			V(apple);
		}
		V(plate_mutex);
		Sleep(200);
	}
	return NULL;
}

void* PV2013::son(void* args)
{
	while (true) {
		P(orange);
		P(plate_mutex);
		std::cout << "儿子拿出一个橘子开吃" << std::endl;
		V(plate_mutex);
		V(plate);
		Sleep(200);
	}
	return NULL;
}

void* PV2013::daughter(void* args)
{
	while (true) {
		P(apple);
		P(plate_mutex);
		std::cout << "女儿拿出一个苹果开吃" << std::endl;
		V(plate_mutex);
		V(plate);
		Sleep(3000);
	}
	return NULL;
}

unsigned int PV2013::random()
{
	srand(time(0));
	return rand() % 2 == 0;
}

void PV2013::testPV2013()
{
	puts("2013年PV题\n");

	pthread_t father_id, son_id, daughter_id;
	pthread_create(&father_id, NULL, &father, NULL);
	pthread_create(&son_id, NULL, &son, NULL);
	pthread_create(&daughter_id, NULL, &daughter, NULL);

	Sleep(10000);

	pthread_cancel(father_id);
	pthread_cancel(son_id);
	pthread_cancel(daughter_id);

	pthread_join(father_id, NULL);
	pthread_join(son_id, NULL);
	pthread_join(daughter_id, NULL);
}
