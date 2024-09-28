#ifndef THREAD_LAUNCHER_H_
#define THREAD_LAUNCHER_H_

#include <string>
#include <initializer_list>

// 定义线程所运行的函数类型
typedef void* (*thread_func)(void*);

/*
 * 启动线程
 * params:
 * title：标题
 * funcs：线程函数初始化列表
 */
void StartThread(const std::string& title, std::initializer_list<thread_func> funcs);

#endif // !THREAD_LAUNCHER_H_

