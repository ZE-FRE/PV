#include <Windows.h>
#include <iostream>
#include "../../include/uestc/PV2017.h"
#include "../../include/Semaphore.h"
#include "../../include/ThreadLauncher.h"

// �����ź���
namespace PV2017 {
    Semaphore mutex = 1, apple = 1, orange = 1, full = 0;
}

void* PV2017::father(void* args)
{
    while (true) {
        P(apple);
        P(mutex);
        Put("�ְַ���ƻ��");
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
        Put("�����������");
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
        Get("Ů��ȡ��ƻ��");
        Get("Ů��ȡ������");
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
    StartThread("2017��PV��", { father, mother, daughter });
}
