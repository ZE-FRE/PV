#include <Windows.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <stdlib.h>
#include "../include/ThreadLauncher.h"

using namespace std;

void ThreadLauncher::StartThread(const string& title, initializer_list<thread_func> funcs)
{
    cout << title << "\n" << endl;

    vector<pthread_t*> thread_ids;

    for (const thread_func& func : funcs) {
        pthread_t* thread_id = (pthread_t*)malloc(sizeof(pthread_t));
        pthread_create(thread_id, NULL, func, NULL);
        thread_ids.push_back(thread_id);
    }

    Sleep(10000);

    for (pthread_t* thread_id : thread_ids) 
        pthread_cancel(*thread_id);
    for (pthread_t* thread_id : thread_ids)
        pthread_join(*thread_id, NULL);
    for (pthread_t* thread_id : thread_ids)
        free(thread_id);
}

void ThreadLauncher::StartThread(const std::string& title, std::initializer_list<Thread*> threads) {
    cout << title << "\n" << endl;

    vector<pthread_t*> thread_ids;

    for (auto beg = threads.begin(); beg != threads.end(); ++beg) {
        pthread_t* thread_id = (pthread_t*)malloc(sizeof(pthread_t));
        pthread_create(thread_id, NULL, (*beg).run, beg->name);
        thread_ids.push_back(thread_id);
    }


    Sleep(10000);

    for (pthread_t* thread_id : thread_ids)
        pthread_cancel(*thread_id);
    for (pthread_t* thread_id : thread_ids)
        pthread_join(*thread_id, NULL);
    for (pthread_t* thread_id : thread_ids)
        free(thread_id);
}
