#include "PV2014.h"
#include <Windows.h>
#include <iostream>
#include <pthread.h>

namespace
{
    unsigned int prev_product = 0;
    // 缓冲区
    unsigned int buf = 0;
    // 定义信号量
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
    // 模拟生产产品消耗时间
    Sleep(1500);
    unsigned int product = ++prev_product;
    return product;
}

void PV2014::put(unsigned int product)
{
    std::cout << "P0放入产品：" << product << std::endl;
    buf = product;
}

unsigned int PV2014::get1()
{
    return buf;
}

void PV2014::compute1(unsigned int product)
{
    // 模拟计算时间
    Sleep(800);
    std::cout << "P1计算平方值=" << product * product << std::endl;
}

unsigned int PV2014::get2()
{
    return buf;
}

void PV2014::compute2(unsigned int product)
{
    // 模拟计算时间
    Sleep(800);
    std::cout << "P2计算的立方值=" << product * product * product << std::endl;
}

void PV2014::testPV2014()
{
    puts("2014年PV题\n");

    pthread_t p0_id, p1_id, p2_id;

    pthread_create(&p0_id, NULL, &P0, NULL);
    pthread_create(&p1_id, NULL, &P1, NULL);
    pthread_create(&p2_id, NULL, &P2, NULL);

    Sleep(10000);

    pthread_cancel(p0_id);
    pthread_cancel(p1_id);
    pthread_cancel(p2_id);

    pthread_join(p0_id, NULL);
    pthread_join(p1_id, NULL);
    pthread_join(p2_id, NULL);

}
