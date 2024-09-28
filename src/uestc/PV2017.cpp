#include <Windows.h>
#include <iostream>
#include "../../include/uestc/PV2017.h"
#include "../../include/Semaphore.h"
#include "../../include/ThreadLauncher.h"

// 定义信号量
namespace PV2017 {
    Semaphore mutex = 1, apple = 1, orange = 1, full = 0;
}

void* PV2017::father(void* args)
{
    while (true) {
        P(apple);
        P(mutex);
        Put("爸爸放入苹果");
        V(mutex);
        V(full);
        Sleep(1500);
    }
    return NULL;
}

void* PV2017::mother(void* args)
{
    while (true) {
        P(orange);
        P(mutex);
        Put("妈妈放入橘子");
        V(mutex);
        V(full);
        Sleep(1500);
    }
    return NULL;
}

void* PV2017::daughter(void* args)
{
    while (true) {
        P(full);
        P(full);
        Get("女儿取走苹果");
        Get("女儿取走橘子");
        V(apple);
        V(orange);
        Sleep(1000);
    }
    return NULL;
}

void PV2017::Put(const char* str)
{
    std::cout << str << std::endl;
}

void PV2017::Get(const char* str)
{
    std::cout << str << std::endl;
}

void PV2017::testPV2017()
{
    StartThread("2017年PV题", { father, mother, daughter });
}
