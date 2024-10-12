#include <Windows.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <stdlib.h>
#include "../include/ThreadLauncher.h"

using namespace std;

void StartThread(const string& title, initializer_list<thread_func> funcs)
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

void StartThread(const string& title, const vector<thread_func>& funcs, const vector<const char*>& thread_names) {
    cout << title << "\n" << endl;

    vector<pthread_t*> thread_ids;

    for (int i = 0; i < funcs.size(); ++i) {
        pthread_t* thread_id = (pthread_t*)malloc(sizeof(pthread_t));
        pthread_create(thread_id, NULL, funcs[i], (void*)thread_names[i]);
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
