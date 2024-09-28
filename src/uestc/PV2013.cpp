#include <iostream>
#include <Windows.h>
#include <time.h>
#include "../../include/uestc/PV2013.h"
#include "../../include/Semaphore.h"
#include "../../include/ThreadLauncher.h"

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
		Sleep(1000);
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
	StartThread("2013年PV题", { father, son, daughter });
}
