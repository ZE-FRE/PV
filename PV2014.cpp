#include "PV2014.h"
#include <Windows.h>
#include <iostream>
#include "Semaphore.h"
#include "ThreadLauncher.h"

namespace
{
    unsigned int prev_product = 0;
    // ������
    unsigned int buf = 0;
    // �����ź���
    Semaphore mutex = 1, sem01 = 0, sem02 = 0, sem0 = 2;
}

void* PV2014::P0(void* args)
{
    while (true) {
        unsigned int product = produce();
        P(sem0);
        P(sem0);
        put(product);
        V(sem01);
        V(sem02);
    }
    return NULL;
}

void* PV2014::P1(void* args)
{
    unsigned int product;
    while (true) {
        P(sem01);
        P(mutex);
        product = get1();
        V(mutex);
        V(sem0);
        compute1(product);
    }
    return NULL;
}

void* PV2014::P2(void* args)
{
    unsigned int product;
    while (true) {
        P(sem02);
        P(mutex);
        product = get2();
        V(mutex);
        V(sem0);
        compute2(product);
    }
    return NULL;
}

unsigned int PV2014::produce()
{
    // ģ��������Ʒ����ʱ��
    Sleep(1500);
    unsigned int product = ++prev_product;
    return product;
}

void PV2014::put(unsigned int product)
{
    std::cout << "P0�����Ʒ��" << product << std::endl;
    buf = product;
}

unsigned int PV2014::get1()
{
    return buf;
}

void PV2014::compute1(unsigned int product)
{
    // ģ�����ʱ��
    Sleep(800);
    std::cout << "P1����ƽ��ֵ=" << product * product << std::endl;
}

unsigned int PV2014::get2()
{
    return buf;
}

void PV2014::compute2(unsigned int product)
{
    // ģ�����ʱ��
    Sleep(800);
    std::cout << "P2���������ֵ=" << product * product * product << std::endl;
}

void PV2014::testPV2014()
{
    StartThread("2014��PV��", { P0, P1, P2 });
}
