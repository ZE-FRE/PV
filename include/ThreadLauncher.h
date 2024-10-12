#ifndef THREAD_LAUNCHER_H_
#define THREAD_LAUNCHER_H_

#include <string>
#include <initializer_list>
#include <vector>

// 定义线程所运行的函数类型
typedef void* (*thread_func)(void*);

/*
 * 启动线程
 * params:
 * title：标题
 * funcs：线程函数初始化列表
 * date:2024/9/28
 */
void StartThread(const std::string& title, std::initializer_list<thread_func> funcs);

void StartThread(const std::string& title, const std::vector<thread_func>& threads,
	const std::vector<const char*>& thread_names);

#endif // !THREAD_LAUNCHER_H_

