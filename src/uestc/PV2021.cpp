#include <iostream>
#include <Windows.h>
#include "../../include/uestc/PV2021.h"
#include "../../include/Semaphore.h"
#include "../../include/ThreadLauncher.h"


namespace PV2021 {

    unsigned int m = 5;
    unsigned int n = 4;

    Semaphore park_mutex = 1, clean_mutex = 1;

    Semaphore park_empty = m;
    Semaphore park_dirty = 0;
    Semaphore park_clean = 0;
    Semaphore clean_empty = n;
    Semaphore clean_dirty = 0;
    Semaphore clean_clean = 0;

    using namespace std;

    void* A(void* args)
    {
        while (true) {
            P(park_empty);
            P(park_mutex);
            cout << "A将客户的脏车停到停车区" << endl;
            V(park_mutex);
            V(park_dirty);
            Sleep(500);
        }
        return nullptr;
    }
    void* B(void* args)
    {
        while (true) {
            P(park_dirty);
            P(clean_empty);
            P(park_mutex);
            cout << "B将客户的车从停车区开出来" << endl;
            V(park_mutex);
            V(park_empty);
            P(clean_mutex);
            cout << "B将客户的脏车开到洗车区" << endl;
            V(clean_mutex);
            V(clean_dirty);
            Sleep(600);
        }
        return nullptr;
    }
    void* C(void* args)
    {
        while (true) {
            P(clean_dirty);
            P(clean_mutex);
            cout << "C花费1秒钟洗车" << endl;
            Sleep(1000);
            V(clean_mutex);
            V(clean_clean);
        }
        return nullptr;
    }
    void* D(void* args)
    {
        while (true) {
            P(clean_clean);
            P(park_empty);
            P(clean_mutex);
            cout << "D将客户的车从洗车区开出来" << endl;
            V(clean_mutex);
            V(clean_empty);
            P(park_mutex);
            cout << "D将客户的车开到停车区" << endl;
            V(park_mutex);
            V(park_clean);
            Sleep(700);
        }
        return nullptr;
    }
    void* E(void* args)
    {
        while (true) {
            P(park_clean);
            P(park_mutex);
            cout << "E把一辆车开给客户" << endl;
            V(park_mutex);
            V(park_empty);
            Sleep(800);
        }
        return nullptr;
    }
    void testPV2021()
    {
        StartThread("2021年PV题", { A,B,C,D,E });
    }

}
